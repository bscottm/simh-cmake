# Locate the PCRE library
#
# This module defines:
#
# ::
#
#   PCRE_LIBRARIES, the name of the library to link against
#   PCRE_INCLUDE_DIRS, where to find the headers
#   PCRE_FOUND, if false, do not try to link against
#   PCRE_VERSION_STRING - human-readable string containing the version of SDL_ttf
#
# Tweaks:
# 1. PCRE_PATH: A list of directories in which to search
# 2. PCRE_DIR: An environment variable to the directory where you've unpacked or installed PCRE.
#
# "scooter me fecit"

find_path(PCRE_INCLUDE_DIR pcre.h
        HINTS
	  ENV PCRE_DIR
	# path suffixes to search inside ENV{PCRE_DIR}
	include/pcre include/PCRE include
	PATHS ${PCRE_PATH}
        )

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIB_PATH_SUFFIXES lib64 lib/x64 lib/amd64 lib)
else ()
  set(LIB_PATH_SUFFIXES lib/x86 lib)
endif ()

find_library(PCRE_LIBRARY
        NAMES pcre pcre_static
        HINTS
	  ENV PCRE_DIR
	PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
        PATHS ${PCRE_PATH}
        )

find_library(PCREPOSIX_LIBRARY
	NAMES pcreposix
	HINTS
	  ENV PCRE_DIR
	PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
	PATHS ${PCRE_PATH}
	)

if (PCRE_INCLUDE_DIR AND EXISTS "${PCRE_INCLUDE_DIR}/pcre.h")
  file(STRINGS "${PCRE_INCLUDE_DIR}/pcre.h" PCRE_VERSION_MAJOR_LINE REGEX "^#define[ \t]+PCRE_MAJOR[ \t]+[0-9]+$")
  file(STRINGS "${PCRE_INCLUDE_DIR}/pcre.h" PCRE_VERSION_MINOR_LINE REGEX "^#define[ \t]+PCRE_MINOR[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+PCRE_MAJOR[ \t]+([0-9]+)$" "\\1" PCRE_VERSION_MAJOR "${PCRE_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+PCRE_MINOR[ \t]+([0-9]+)$" "\\1" PCRE_VERSION_MINOR "${PCRE_VERSION_MINOR_LINE}")
  set(PCRE_VERSION_STRING ${PCRE_VERSION_MAJOR}.${PCRE_VERSION_MINOR})
  unset(PCRE_VERSION_MAJOR_LINE)
  unset(PCRE_VERSION_MINOR_LINE)
  unset(PCRE_VERSION_MAJOR)
  unset(PCRE_VERSION_MINOR)
endif ()

set(PCRE_LIBRARIES ${PCRE_LIBRARY})
set(PCRE_INCLUDE_DIRS ${PCRE_INCLUDE_DIR})
set(PCREPOSIX_LIBRARIES ${PCREPOSIX_LIBRARY})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCRE
        REQUIRED_VARS PCRE_LIBRARIES PCRE_INCLUDE_DIRS
        VERSION_VAR PCRE_VERSION_STRING)
