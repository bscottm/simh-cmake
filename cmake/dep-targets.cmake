include (ExternalProject)

add_library(zlib_lib INTERFACE)
add_library(regexp_lib INTERFACE)
add_library(simh_video INTERFACE)
add_library(simh_network INTERFACE)

if (ZLIB_FOUND)
    if (TARGET ZLIB::ZLIB)
        target_link_libraries(zlib_lib INTERFACE ZLIB::ZLIB)
    else (TARGET ZLIB::ZLIB)
        target_compile_definitions(zlib_lib INTERFACE ${ZLIB_INCLUDE_DIRS})
        target_link_libraries(zlib_lib INTERFACE ${ZLIB_LIBRARIES})
    endif (TARGET ZLIB::ZLIB)

    set(ZLIB_PKG_STATUS "installed ZLIB")
else (ZLIB_FOUND)
    set(ZLIB_REPO_URL https://github.com/madler/zlib/archive/v1.2.11.zip)

    ExternalProject_Add(zlib-dep
        URL ${ZLIB_REPO_URL}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    BuildDepMatrix(zlib-dep zlib)

    list(APPEND SIMH_BUILD_DEPS zlib)
    list(APPEND SIMH_DEP_TARGETS zlib-dep)
    message(STATUS "Building ZLIB from ${ZLIB_REPO_URL}.")
    set(ZLIB_PKG_STATUS "ZLIB source build")
endif (ZLIB_FOUND)

## Freetype will sometimes find BZip2 in AppVeyor's image, which means that we
## need to bring it along as a dependency for AppVeyor builds. Ordinarily, though,
## it's not a dependency for SIMH.

if (BZIP2_FOUND)
    if (TARGET BZip2::BZip2)
        target_link_libraries(zlib_lib INTERFACE BZip2::BZip2)
    else (TARGET BZip2::BZip2)
        target_compile_definitions(zlib_lib INTERFACE ${BZIP2_INCLUDE_DIR})
        target_link_libraries(zlib_lib INTERFACE ${BZIP2_LIBRARIES})
    endif (TARGET BZip2::BZip2)
endif (BZIP2_FOUND)

## Prefer PCRE2 over older PCRE
if (PCRE2_FOUND)
    target_compile_definitions(regexp_lib INTERFACE HAVE_PCRE2_H PCRE_STATIC)
    target_include_directories(regexp_lib INTERFACE ${PCRE2_INCLUDE_DIRS})
    target_link_libraries(regexp_lib INTERFACE ${PCRE2_LIBRARY})

    set(PCRE_PKG_STATUS "installed pcre2")
elseif (PCRE_FOUND)
    target_compile_definitions(regexp_lib INTERFACE HAVE_PCRE_H PCRE_STATIC)
    target_include_directories(regexp_lib INTERFACE ${PCRE_INCLUDE_DIRS})
    target_link_libraries(regexp_lib INTERFACE ${PCRE_LIBRARY})

    set(PCRE_PKG_STATUS "installed pcre")
else (PCRE2_FOUND)
    set(PCRE_DEPS)
    if (TARGET zlib-dep)
        list(APPEND PCRE_DEPS zlib-dep)
    endif (TARGET zlib-dep)

    ## set(PCRE2_URL "https://ftp.pcre.org/pub/pcre/pcre2-10.35.zip")
    set(PCRE2_URL "https://gitlab.com/scooter-phd/pcre2/-/archive/pcre2-10.35-patch/pcre2-pcre2-10.35-patch.zip")

    ExternalProject_Add(pcre-ext
        URL ${PCRE2_URL}
        DEPENDS
            ${PCRE_DEPS}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    BuildDepMatrix(pcre-ext pcre
        CMAKE_ARGS
            -DBUILD_SHARED_LIBS:Bool=On
            -DPCRE2_BUILD_PCRE2GREP:Bool=Off
    )

    list(APPEND SIMH_BUILD_DEPS pcre)
    list(APPEND SIMH_DEP_TARGETS pcre-ext)
    message(STATUS "Building PCRE from ${PCRE2_URL}")
    set(PCRE_PKG_STATUS "pcre2 source build")
endif (PCRE2_FOUND)

set(BUILD_WITH_VIDEO FALSE)
IF (WITH_VIDEO)
    IF (NOT PNG_FOUND)
        set(PNG_DEPS)
        if (NOT ZLIB_FOUND)
            list(APPEND PNG_DEPS zlib-dep)
        endif (NOT ZLIB_FOUND)

        set(PNG_SOURCE_URL "https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.xz/download")

        ExternalProject_Add(png-dep
            URL ${PNG_SOURCE_URL}
            DEPENDS
                ${PNG_DEPS}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )

        ## Work around the GCC 8.1.0 SEH index regression.
        set(PNG_CMAKE_BUILD_TYPE_RELEASE "Release")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU" AND
            CMAKE_C_COMPILER_VERSION VERSION_EQUAL "8.1" AND
            NOT CMAKE_BUILD_VERSION)
            message(STATUS "PNG: Build using MinSizeRel CMAKE_BUILD_TYPE with GCC 8.1")
            set(PNG_CMAKE_BUILD_TYPE_RELEASE "MinSizeRel")
        endif()

        BuildDepMatrix(png-dep libpng RELEASE_BUILD ${PNG_CMAKE_BUILD_TYPE_RELEASE})

        list(APPEND SIMH_BUILD_DEPS "png")
        list(APPEND SIMH_DEP_TARGETS "png-dep")
        message(STATUS "Building PNG from ${PNG_SOURCE_URL}")
        list(APPEND VIDEO_PKG_STATUS "PNG source build")
    ENDIF (NOT PNG_FOUND)

    IF (NOT FREETYPE_FOUND)
        set(FREETYPE_DEPS)
        if (TARGET png-dep)
            list(APPEND FREETYPE_DEPS "png-dep")
        endif (TARGET png-dep)

        set(FREETYPE_SOURCE_URL "http://download.savannah.nongnu.org/releases/freetype/freetype-2.10.2.tar.gz")

        ExternalProject_Add(freetype-dep
            URL ${FREETYPE_SOURCE_URL}
            DEPENDS
                ${FREETYPE_DEPS}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )

        BuildDepMatrix(freetype-dep FreeType)

        list(APPEND SIMH_BUILD_DEPS "freetype")
        list(APPEND SIMH_DEP_TARGETS "freetype-dep")
        message(STATUS "Building Freetype from ${FREETYPE_SOURCE_URL}.")
        list(APPEND VIDEO_PKG_STATUS "Freetype source build")
    endif (NOT FREETYPE_FOUND)

    IF (NOT SDL2_FOUND)
        set(SDL2_SOURCE_URL "https://www.libsdl.org/release/SDL2-2.0.12.zip")

        ExternalProject_Add(sdl2-dep
            URL ${SDL2_SOURCE_URL}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )

        BuildDepMatrix(sdl2-dep SDL2)

        list(APPEND SIMH_BUILD_DEPS "SDL2")
        list(APPEND SIMH_DEP_TARGETS "sdl2-dep")
        message(STATUS "Building SDL2 from ${SDL2_SOURCE_URL}.")
        list(APPEND VIDEO_PKG_STATUS "SDL2 source build")
    ENDIF (NOT SDL2_FOUND)

    IF (NOT SDL2_ttf_FOUND)
        set(SDL2_ttf_depdir ${CMAKE_BINARY_DIR}/sdl2-ttf-dep-prefix/src/sdl2-ttf-dep/)
        set(SDL2_ttf_DEPS)

        if (TARGET sdl2-dep)
            list(APPEND SDL2_ttf_DEPS sdl2-dep)
        endif (TARGET sdl2-dep)
        if (TARGET freetype-dep)
            list(APPEND SDL2_ttf_DEPS freetype-dep)
        endif (TARGET freetype-dep)

        ExternalProject_Add(sdl2-ttf-dep
            URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.zip
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
            UPDATE_COMMAND
                ${CMAKE_COMMAND} -E copy ${SIMH_DEP_PATCHES}/SDL2_ttf/SDL2_ttfConfig.cmake ${SDL2_ttf_depdir}
            DEPENDS
                ${SDL2_ttf_DEPS}
        )

        BuildDepMatrix(sdl2-ttf-dep SDL2_ttf)

        list(APPEND SIMH_BUILD_DEPS "SDL2_ttf")
        list(APPEND SIMH_DEP_TARGETS "sdl2-ttf-dep")
        message(STATUS "Building SDL2_ttf from https://www.libsdl.org/release/SDL2_ttf-2.0.15.zip.")
        list(APPEND VIDEO_PKG_STATUS "SDL2_ttf source build")
    ENDIF (NOT SDL2_ttf_FOUND)

    IF (SDL2_ttf_FOUND)
        IF (TARGET SDL2_ttf::SDL2_ttf)
            target_link_libraries(simh_video INTERFACE SDL2_ttf::SDL2_ttf)
        ELSEIF (TARGET PkgConfig::SDL2_ttf)
            target_link_libraries(simh_video INTERFACE PkgConfig::SDL2_ttf)
        ELSEIF (DEFINED SDL_ttf_LIBRARIES AND DEFINED SDL_ttf_INCLUDE_DIRS)
            ## target_link_directories(simh_video INTERFACE ${SDL2_ttf_LIBDIR})
            target_link_libraries(simh_video INTERFACE ${SDL_ttf_LIBRARIES})
            target_include_directories(simh_video INTERFACE ${SDL_ttf_INCLUDE_DIRS})
        ELSE ()
            message(FATAL_ERROR "SDL2_ttf_FOUND set but no SDL2_ttf::SDL2_ttf import library or SDL_ttf_LIBRARIES/SDL_ttf_INCLUDE_DIRS? ")
        ENDIF ()

        list(APPEND VIDEO_PKG_STATUS "installed SDL2_ttf")
    ENDIF (SDL2_ttf_FOUND)

    IF (SDL2_FOUND)
        target_compile_definitions(simh_video INTERFACE USE_SIM_VIDEO HAVE_LIBSDL)

        IF (TARGET SDL2::SDL2)
            target_link_libraries(simh_video INTERFACE SDL2::SDL2)
        ELSEIF (TARGET PkgConfig::SDL2)
            target_link_libraries(simh_video INTERFACE PkgConfig::SDL2)
        ELSEIF (DEFINED SDL2_LIBRARIES AND DEFINED SDL2_INCLUDE_DIRS)
            ## target_link_directories(simh_video INTERFACE ${SDL2_LIBDIR})
            target_link_libraries(simh_video INTERFACE ${SDL2_LIBRARIES})
            target_include_directories(simh_video INTERFACE ${SDL2_INCLUDE_DIRS})
        ELSE ()
            message(FATAL_ERROR "SDL2_FOUND set but no SDL2::SDL2 import library or SDL2_LIBRARIES/SDL2_INCLUDE_DIRS?")
        ENDIF ()

        list(APPEND VIDEO_PKG_STATUS "installed SDL2")
    ENDIF (SDL2_FOUND)

    IF (FREETYPE_FOUND)
        target_link_libraries(simh_video INTERFACE Freetype::Freetype)

        if (HARFBUZZ_FOUND)
            target_link_libraries(simh_video INTERFACE Harfbuzz::Harfbuzz)
        endif (HARFBUZZ_FOUND)

        if (BROTLIDEC_FOUND)
          target_include_directories(simh_video INTERFACE ${BROTLIDEC_INCLUDE_DIRS})
          target_link_libraries(simh_video INTERFACE ${BROTLIDEC_LIBRARIES})
        endif (BROTLIDEC_FOUND)

        list(APPEND VIDEO_PKG_STATUS "installed Freetype")
    ENDIF (FREETYPE_FOUND)

    IF (PNG_FOUND)
        target_include_directories(simh_video INTERFACE ${PNG_INCLUDE_DIRS})
        target_link_libraries(simh_video INTERFACE ${PNG_LIBRARIES})

        target_compile_definitions(simh_video INTERFACE ${PNG_DEFINITIONS} HAVE_LIBPNG)

        list(APPEND VIDEO_PKG_STATUS "installed PNG")
    ENDIF (PNG_FOUND)

    set(BUILD_WITH_VIDEO TRUE)
ELSE ()
    set(VIDEO_PKG_STATUS "skipped")
ENDIF(WITH_VIDEO)

if (WITH_NETWORK)
    ## By default, use the static network runtime (bad choice of manifest constant,
    ## but what can one do?)
    set(network_runtime)

    if (PCAP_FOUND)
        if (NOT WIN32)
            set(network_runtime USE_NETWORK)

            target_include_directories(simh_network INTERFACE "${PCAP_INCLUDE_DIRS}")
            target_compile_definitions(simh_network INTERFACE HAVE_PCAP_NETWORK)
            target_link_libraries(simh_network INTERFACE "${PCAP_LIBRARIES}")

            ## HAVE_PCAP_COMPILE is set in dep-locate.
            if (HAVE_PCAP_COMPILE)
                target_compile_definitions(simh_network INTERFACE BPF_CONST_STRING)
            endif (HAVE_PCAP_COMPILE)
        else (NOT WIN32)
            ## USE_SHARED for Windows.
            set(network_runtime USE_SHARED)
        endif (NOT WIN32)

        set(NETWORK_PKG_STATUS "installed PCAP")
    else (PCAP_FOUND)
        # Extract the npcap headers and libraries
        set(NPCAP_ARCHIVE ${SIMH_DEP_PATCHES}/libpcap/npcap-sdk-1.05.zip)

        if (WIN32)
            execute_process(
                    COMMAND ${CMAKE_COMMAND} -E tar xzf ${NPCAP_ARCHIVE} Include/ Lib/
                    WORKING_DIRECTORY ${SIMH_DEP_TOPDIR}
            )
        endif (WIN32)

        ## set(LIBPCAP_SOURCE_URL "https://github.com/the-tcpdump-group/libpcap/archive/libpcap-1.9.1.tar.gz")
        set(LIBPCAP_SOURCE_URL "https://gitlab.com/scooter-phd/libpcap/-/archive/chksym_exists/libpcap-chksym_exists.zip")
        ExternalProject_Add(pcap-dep
            URL ${LIBPCAP_SOURCE_URL}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )

        BuildDepMatrix(pcap-dep libpcap)

        list(APPEND SIMH_BUILD_DEPS "pcap")
        list(APPEND SIMH_DEP_TARGETS "pcap-dep")
        message(STATUS "Building PCAP from ${LIBPCAP_SOURCE_URL}")
        set(NETWORK_PKG_STATUS "PCAP source build")
    endif (PCAP_FOUND)

    ## TAP/TUN devices
    if (WITH_TAP)
        target_compile_definitions(simh_network INTERFACE ${NETWORK_TUN_DEFS})
    endif (WITH_TAP)

    if (VDE_FOUND)
        target_compile_definitions(simh_network INTERFACE HAVE_VDE_NETWORK)
        target_include_directories(simh_network INTERFACE "${VDEPLUG_INCLUDE_DIRS}")
        target_link_libraries(simh_network INTERFACE "${VDEPLUG_LIBRARY}")

        list(APPEND NETWORK_PKG_STATUS "VDE")
    endif (VDE_FOUND)

    ## Finally, set the network runtime
    if (NOT network_runtime)
        ## Default to USE_NETWORK...
        set(network_runtime USE_NETWORK)
    endif (NOT network_runtime)

    target_compile_definitions(simh_network INTERFACE ${network_runtime})
    set(BUILD_WITH_NETWORK TRUE)
else (WITH_NETWORK)
    set(NETWORK_STATUS "networking disabled")
    set(NETWORK_PKG_STATUS "skipped")
    set(BUILD_WITH_NETWORK FALSE)
endif (WITH_NETWORK)

## Add needed platform runtime/libraries.
##
## Windows: socket libs (even with networking disabled), winmm (for ms timer functions)
## Linux: large file support
if (WIN32)
    target_link_libraries(os_features INTERFACE "winmm")
    target_link_libraries(simh_network INTERFACE ws2_32 wsock32)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_compile_definitions(os_features INTERFACE _LARGEFILE64_SOURCE _FILE_OFFSET_BITS=64)
endif ()
