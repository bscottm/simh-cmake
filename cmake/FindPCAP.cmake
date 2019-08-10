# Locate the PCAP library
#
# This module defines:
#
# ::
#
#   PCAP_LIBRARIES, the name of the library to link against
#   PCAP_INCLUDE_DIRS, where to find the headers
#   PCAP_FOUND, if false, do not try to link against
#   PCAP_VERSION_STRING - human-readable string containing the version of SDL_ttf
#
# Tweaks:
# 1. PCAP_PATH: A list of directories in which to search
# 2. PCAP_DIR: An environment variable to the directory where you've unpacked or installed PCAP.
#
# "scooter me fecit"

find_path(PCAP_INCLUDE_DIR pcap.h
        HINTS
	  ENV PCAP_DIR
	# path suffixes to search inside ENV{PCAP_DIR}
	include/pcap include/PCAP include
	PATHS ${PCAP_PATH}
        )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  #
  # For the WinPcap and Npcap SDKs, the Lib subdirectory of the top-level
  # directory contains 32-bit libraries; the 64-bit libraries are in the
  # Lib/x64 directory.
  #
  # The only way to *FORCE* CMake to look in the Lib/x64 directory
  # without searching in the Lib directory first appears to be to set
  # CMAKE_LIBRARY_ARCHITECTURE to "x64".
  #
  set(CMAKE_C_LIBRARY_ARCHITECTURE "x64")
  set(CMAKE_LIBRARY_ARCHITECTURE "x64")
endif()

find_library(PCAP_LIBRARY
        NAMES pcap pcap_static libpcap libpcap_static
        HINTS
	  ENV PCAP_DIR
	PATH_SUFFIXES lib
        PATHS ${PCAP_PATH}
        )

find_library(PACKET_LIBRARY
        NAMES packet Packet
        HINTS
	  ENV PCAP_DIR
	PATH_SUFFIXES lib
        PATHS ${PCAP_PATH}
        )

set(PCAP_LIBRARIES ${PCAP_LIBRARY} ${PACKET_LIBRARY})
set(PCAP_INCLUDE_DIRS ${PCAP_INCLUDE_DIR})
set(PCAP_LIBRARY)
set(PCAP_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCAP
        REQUIRED_VARS PCAP_LIBRARIES PCAP_INCLUDE_DIRS)
