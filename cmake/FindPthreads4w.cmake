# Locate the pthreads4w library and pthreads.h header
#
# This module defines:
#
# ::
#
#   PTW_LIBRARIES, the name of the library to link against
#   PTW_INCLUDE_DIRS, where to find the headers
#   PTW_FOUND, if false, do not try to link against
#
# Tweaks:
# 1. PTW_PATH: A list of directories in which to search
# 2. PTW_DIR: An environment variable to the directory where you've unpacked or installed PCRE.
#
# "scooter me fecit"

find_path(PTW_INCLUDE_DIR pthread.h
        HINTS
	  ENV PTW_DIR
	# path suffixes to search inside ENV{PTW_DIR}
	PATH_SUFFIXES include include/pthreads4w
	PATHS ${PTW_PATH}
        )

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIB_PATH_SUFFIXES lib64 lib/x64 lib/amd64 lib)
else ()
  set(LIB_PATH_SUFFIXES lib/x86 lib)
endif ()

find_library(PTW_LIBRARY
  NAMES libpthreadVC3 pthreadVC3 libpthreadGC3 pthreadGC3
        HINTS
	  ENV PTW_ DIR
	PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
        PATHS ${PTW_PATH}
        )

set(PTW_LIBRARIES ${PTW_LIBRARY})
set(PTW_INCLUDE_DIRS ${PTW_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
  PTW
  REQUIRED_VARS PTW_LIBRARIES PTW_INCLUDE_DIRS
  )
       
