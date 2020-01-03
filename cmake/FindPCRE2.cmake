# Locate the PCRE library
#
# This module defines:
#
# ::
#
#   PCRE2_LIBRARIES, the name of the pcre2 library to link against
#   PCRE2_INCLUDE_DIRS, where to find the pcre2 headers
#   PCRE2_FOUND, if false, do not try to compile or link with pcre2
#   PCRE2_VERSION_STRING - human-readable string containing the version of pcre or pcre2
#
# Tweaks:
# 1. PCRE_PATH: A list of directories in which to search
# 2. PCRE_DIR: An environment variable to the directory where you've unpacked or installed PCRE.
#
# "scooter me fecit"

find_path(PCRE2_INCLUDE_DIR pcre2.h
        HINTS
	  ENV PCRE_DIR
	# path suffixes to search inside ENV{PCRE_DIR}
	PATHS ${PCRE_PATH}
	PATH_SUFFIXES
	    include/pcre
	    include/PCRE
	    include
        )

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIB_PATH_SUFFIXES lib64 lib/x64 lib/amd64 lib/x86_64-linux-gnu lib)
else ()
  set(LIB_PATH_SUFFIXES lib/x86 lib)
endif ()

find_library(PCRE2_LIBRARY_RELEASE
        NAMES pcre2-8
        HINTS
	  ENV PCRE_DIR
	PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
        PATHS ${PCRE_PATH}
        )

find_library(PCRE2_LIBRARY_DEBUG
        NAMES pcre2-8d
        HINTS
	  ENV PCRE_DIR
	PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
        PATHS ${PCRE_PATH}
        )

if (PCRE2_INCLUDE_DIR)
    if (EXISTS "${PCRE_INCLUDE_DIR}/pcre.h")
	file(STRINGS "${PCRE_INCLUDE_DIR}/pcre.h" PCRE2_VERSION_MAJOR_LINE REGEX "^#define[ \t]+PCRE_MAJOR[ \t]+[0-9]+$")
	file(STRINGS "${PCRE_INCLUDE_DIR}/pcre.h" PCRE2_VERSION_MINOR_LINE REGEX "^#define[ \t]+PCRE_MINOR[ \t]+[0-9]+$")
    elseif (EXISTS "${PCRE2_INCLUDE_DIR}/pcre2.h")
	file(STRINGS "${PCRE2_INCLUDE_DIR}/pcre2.h" PCRE2_VERSION_MAJOR_LINE REGEX "^#define[ \t]+PCRE2_MAJOR[ \t]+[0-9]+$")
	file(STRINGS "${PCRE2_INCLUDE_DIR}/pcre2.h" PCRE2_VERSION_MINOR_LINE REGEX "^#define[ \t]+PCRE2_MINOR[ \t]+[0-9]+$")
    endif ()

    string(REGEX REPLACE "^#define[ \t]+PCRE2?_MAJOR[ \t]+([0-9]+)$" "\\1" PCRE2_VERSION_MAJOR "${PCRE2_VERSION_MAJOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+PCRE2?_MINOR[ \t]+([0-9]+)$" "\\1" PCRE2_VERSION_MINOR "${PCRE2_VERSION_MINOR_LINE}")

    set(PCRE2_VERSION_STRING ${PCRE2_VERSION_MAJOR}.${PCRE2_VERSION_MINOR})
    set(PCRE2_VERSION_TWEAK "")
    if (PCRE2_VERSION_STRING MATCHES "[0-9]+\.[0-9]+")
	set(PCRE2_VERSION_TWEAK "${CMAKE_MATCH_1}")
	string(APPEND PCRE2_VERSION_STRING ".${PCRE2_VERSION_TWEAK}")
    endif ()
    unset(PCRE2_VERSION_MAJOR_LINE)
    unset(PCRE2_VERSION_MINOR_LINE)
    unset(PCRE2_VERSION_MAJOR)
    unset(PCRE2_VERSION_MINOR)
endif ()

include(SelectLibraryConfigurations)

select_library_configurations(PCRE2)

set(PCRE2_INCLUDE_DIRS ${PCRE2_INCLUDE_DIR})
set(PCRE2_LIBRARIES ${PCRE2_LIBRARY})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    PCRE2
    REQUIRED PCRE2_LIBRARY PCRE2_INCLUDE_DIR
    # VERSION_VAR PCRE2_VERSION_STRING
)
