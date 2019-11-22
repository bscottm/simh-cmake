#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the freetype, SDL2, SDL2_ttf dependencies
#
# (a) Try to locate the system's installed libraries.
# (b) Build source libraries, if not found.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

include (ExternalProject)

# pcap networking (slirp is handled in its own directory):
add_library(pcap INTERFACE)
set(NETWORK_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/build-stage)

if (WITH_NETWORK)
    if (WITH_PCAP)
		include (FindPCAP)

		if (PCAP_FOUND)
			target_compile_definitions(pcap INTERFACE USE_SHARED HAVE_PCAP_NETWORK)
			target_include_directories(pcap INTERFACE "${PCAP_INCLUDE_DIRS}")
			target_link_libraries(pcap INTERFACE "${PCAP_LIBRARIES}")

			set(NETWORK_PKG_STATUS "installed PCAP")
		else (PCAP_FOUND)
			# Extract the npcap headers and libraries
			set(NPCAP_ARCHIVE ${CMAKE_SOURCE_DIR}/dep-patches/libpcap/npcap-sdk-1.03.zip)

			if(CMAKE_SIZEOF_VOID_P EQUAL 8)
				set(NPCAP_PACKET_DLL C:/Windows/System32/Npcap/Packet.DLL)
			else(CMAKE_SIZEOF_VOID_P EQUAL 8)
				set(NPCAP_PACKET_DLL C:/Windows/SysWOW64/Npcap/Packet.DLL)
			endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

			# execute_process(
			# 	COMMAND ${CMAKE_COMMAND} -E copy ${NPCAP_PACKET_DLL} build-stage/bin
			# 	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
			# )

			execute_process(
				COMMAND ${CMAKE_COMMAND} -E tar xzf ${NPCAP_ARCHIVE} Include/ Lib/
				WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/build-stage/
			)

			ExternalProject_Add(pcap-dep
				# GIT_REPOSITORY https://github.com/the-tcpdump-group/libpcap.git
				# GIT_TAG libpcap-1.9.0
				GIT_REPOSITORY https://github.com/bscottm/libpcap.git
				GIT_TAG cmake_library_architecture
				CMAKE_ARGS 
					-DCMAKE_INSTALL_PREFIX=${NETWORK_INSTALL_PREFIX}
			)

			list(APPEND SIMH_BUILD_DEPS "pcap")
			message(STATUS "Building PCAP from github repository")
			set(NETWORK_PKG_STATUS "PCAP source build")
		endif (PCAP_FOUND)
	endif ()
else ()
    set(NETWORK_STATUS "networking disabled")
endif ()
