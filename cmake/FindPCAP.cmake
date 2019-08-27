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

find_library(PCAP_LIBRARY
        NAMES pcap pcap_static libpcap libpcap_static
        HINTS
	  ENV PCAP_DIR
	PATH_SUFFIXES lib
        PATHS ${PCAP_PATH}
        )

if (WIN32 AND PCAP_LIBRARY)
    ## Only worry about the packet library on Windows.
    find_library(PACKET_LIBRARY
	    NAMES packet Packet
	    HINTS
	      ENV PCAP_DIR
	    PATH_SUFFIXES lib
	    PATHS ${PCAP_PATH}
	    )
else (WIN32 AND PCAP_LIBRARY)
    set(PACKET_LIBRARY)
endif (WIN32 AND PCAP_LIBRARY)

set(PCAP_LIBRARIES ${PCAP_LIBRARY} ${PACKET_LIBRARY})
set(PCAP_INCLUDE_DIRS ${PCAP_INCLUDE_DIR})
set(PCAP_LIBRARY)
set(PCAP_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCAP
        REQUIRED_VARS PCAP_LIBRARIES PCAP_INCLUDE_DIRS)
