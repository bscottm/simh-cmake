#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the networking dependencies
#
# (a) Try to locate the system's installed libraries.
# (b) Build source libraries, if not found.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

include (ExternalProject)

# simh networking interface library (slirp is handled in its own directory):
add_library(simh_network INTERFACE)

if (WITH_NETWORK)
    ## By default, use the static network runtime (bad choice of manifest constant,
    ## but what can one do?)
    set(network_runtime)

    if (WITH_PCAP)
        include (FindPCAP)

        if (PCAP_FOUND)
            target_include_directories(simh_network INTERFACE "${PCAP_INCLUDE_DIRS}")
            if (NOT WIN32)
                ## On Windows, libpcap is dynamically loaded.
                set(network_runtime USE_NETWORK)
                target_compile_definitions(simh_network INTERFACE HAVE_PCAP_NETWORK)
                target_link_libraries(simh_network INTERFACE "${PCAP_LIBRARIES}")

                ## See if pcap_compile() is present:
                set(saved_cmake_required_incs ${CMAKE_REQUIRED_INCLUDES})
                set(saved_cmake_required_libs ${CMAKE_REQUIRED_LIBRARIES})

                set(CMAKE_REQUIRED_INCLUDES ${PCAP_INCLUDE_DIRS})
                set(CMAKE_REQUIRED_LIBRARIES ${PCAP_LIBRARIES})

                check_symbol_exists(pcap_compile pcap.h have_pcap_compile)

                set(CMAKE_REQUIRED_INCLUDES ${saved_cmake_required_incs})
                set(CMAKE_REQUIRED_LIBRARIES ${saved_cmake_required_libs})

                if (have_pcap_compile)
                    target_compile_definitions(simh_network INTERFACE BPF_CONST_STRING)
                endif (have_pcap_compile)
            else (NOT WIN32)
                ## USE_SHARED for Windows.
                set(network_runtime USE_SHARED)
            endif (NOT WIN32)

            set(NETWORK_PKG_STATUS "installed PCAP")
        else (PCAP_FOUND)
            # Extract the npcap headers and libraries
            set(NPCAP_ARCHIVE ${SIMH_DEP_PATCHES}/libpcap/npcap-sdk-1.04.zip)

            if (WIN32)
                execute_process(
                        COMMAND ${CMAKE_COMMAND} -E tar xzf ${NPCAP_ARCHIVE} Include/ Lib/
                        WORKING_DIRECTORY ${SIMH_DEP_TOPDIR}
                )
            endif (WIN32)

            ExternalProject_Add(pcap-dep
                # GIT_REPOSITORY https://github.com/the-tcpdump-group/libpcap.git
                # GIT_TAG libpcap-1.9.0
                GIT_REPOSITORY https://github.com/bscottm/libpcap.git
                GIT_TAG cmake_library_architecture
                CONFIGURE_COMMAND ""
                BUILD_COMMAND ""
                INSTALL_COMMAND ""
            )

            BuildDepMatrix(pcap-dep libpcap)

            list(APPEND SIMH_BUILD_DEPS "pcap")
            list(APPEND SIMH_DEP_TARGETS "pcap-dep")
            message(STATUS "Building PCAP from github repository")
            set(NETWORK_PKG_STATUS "PCAP source build")
        endif (PCAP_FOUND)
    endif ()

    ## TAP/TUN devices
    if (WITH_TAP)
        check_include_file(linux/if_tun.h if_tun_found)
        set(tun_defs)

        if (NOT if_tun_found)
            check_include_file(net/if_tun.h net_if_tun_found)
            if (net_if_tun_found OR EXISTS /Library/Extensions/tap.kext)
                list(APPEND tun_defs HAVE_BSDTUNTAP)
            endif (net_if_tun_found OR EXISTS /Library/Extensions/tap.kext)
        endif (NOT if_tun_found)

        if (if_tun_found OR net_if_tun_found)
            list(APPEND NETWORK_PKG_STATUS "TAP/TUN interface")
        endif (if_tun_found OR net_if_tun_found)

        target_compile_definitions(simh_network INTERFACE ${tun_defs})
    endif (WITH_TAP)

    find_package(VDE)
    if (NOT VDE_FOUND)
        pkg_check_modules(VDE IMPORTED_TARGET VDEPLUG)
    endif (NOT VDE_FOUND)

    if (VDE_FOUND)
        target_compile_definitions(simh_network INTERFACE HAVE_VDE_NETWORK)
        target_include_directories(simh_network INTERFACE "${VDEPLUG_INCLUDE_DIRS}")
        target_link_libraries(simh_network INTERFACE "${VDEPLUG_LIBRARIES}")

        list(APPEND NETWORK_PKG_STATUS "VDE")
    endif (VDE_FOUND)

    ## Finally, set the network runtime
    if (NOT network_runtime)
        ## Not set -- default to USE_NETWORK...
        set(network_runtime USE_NETWORK)
    endif (NOT network_runtime)

    target_compile_definitions(simh_network INTERFACE ${network_runtime})

    ## Make the package status pretty.
    string(REPLACE ";" ", " NETWORK_PKG_STATUS "${NETWORK_PKG_STATUS}")
    set(BUILD_WITH_NETWORK TRUE)
else ()
    set(NETWORK_STATUS "networking disabled")
    set(NETWORK_PKG_STATUS "skipped")
    set(BUILD_WITH_NETWORK FALSE)
endif ()

## Add needed platform runtime/libraries, even with networking disabled,
## Windows needs these:
if (WIN32)
    target_link_libraries(simh_network INTERFACE ws2_32 wsock32)
endif (WIN32)
