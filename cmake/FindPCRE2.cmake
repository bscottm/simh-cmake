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

find_library(PCRE2_POSIX_LIBRARY_RELEASE
	NAMES pcre2-posix
	HINTS
	  ENV PCRE_DIR
	PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
	PATHS ${PCRE_PATH}
	)

find_library(PCRE2_POSIX_LIBRARY_DEBUG
	NAMES pcre2-posixd
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

## libpcre2posix on Ubuntu (and Debian) are broken -- test this:
set(PCRE2POSIX_BROKEN FALSE)

if (PCRE2_INCLUDE_DIR)
    set(PCRE2POSIX_BROKEN_TEST "
#include <string.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2posix.h>
#include <pcre2.h>
#define USE_REGEX 1

int main(void)
{
    int res;
    regex_t re;

    memset (&re, 0, sizeof(re));
    res = regcomp (&re, \"Some RE\", REG_EXTENDED | REG_ICASE);

    return res;
}
")

    file(WRITE
	"${CMAKE_BINARY_DIR}/pcre2posix_test.c"
	"${PCRE2POSIX_BROKEN_TEST}")

    try_run(
	run_result compile_result
	"${CMAKE_BINARY_DIR}" "${CMAKE_BINARY_DIR}/pcre2posix_test.c"
	LINK_LIBRARIES ${PCRE2_POSIX} ${PCRE2_LIBRARY}
	COMPILE_OUTPUT_VARIABLE pcre2posix_broken_compile
	RUN_OUTPUT_VARIABLE pcre2posix_broken_run)

    if (compile_result AND run_result STREQUAL "FAILED_TO_RUN")
	set(PCRE2POSIX_BROKEN TRUE)
    endif (compile_result AND run_result STREQUAL "FAILED_TO_RUN")
endif ()

include(SelectLibraryConfigurations)

if (NOT PCRE2POSIX_BROKEN)
    select_library_configurations(PCRE2)
    select_library_configurations(PCRE2_POSIX)

    set(PCRE2_INCLUDE_DIRS ${PCRE2_INCLUDE_DIR})
    set(PCRE2_LIBRARIES ${PCRE2_LIBRARY})
    set(PCRE2_POSIX_LIBRARIES ${PCRE2_POSIX})

    include(FindPackageHandleStandardArgs)

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	PCRE2
	REQUIRED PCRE2_LIBRARY PCRE2_POSIX_LIBRARY PCRE2_INCLUDE_DIR
	# VERSION_VAR PCRE2_VERSION_STRING
    )
else (NOT PCRE2POSIX_BROKEN)
    message(STATUS "Broken pcre2posix library.")
    unset(PCRE2_INCLUDE_DIR)
    unset(PCRE2_LIBRARY)
    unset(PCRE2_POSIX)
    unset(PCRE2_FOUND)
    unset(PCRE2_VERSION_STRING)
endif (NOT PCRE2POSIX_BROKEN)
