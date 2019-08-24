# Locate the pthreads4w library and pthreads.h header
#
# This module defines:
#
# ::
#
#   PTW_LIBRARY_PATH, the library directory
#   PTW_LIBRARY_FLAVORS the available libraries (VCE3, VSE3, VC3, GCE3, GS3, GC3, ...)
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

find_library(PTW_LIBRARY_RELEASE
  NAMES 
    libpthreadVC3  pthreadVC3  libpthreadGC3  pthreadGC3
    libpthreadVCE3 pthreadVCE3 libpthreadGCE3 pthreadGCE3
    libpthreadVSE3 pthreadVSE3 libpthreadGSE3 pthreadGSE3
  HINTS
      ENV PTW_ DIR
  PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
  PATHS ${PTW_PATH}
  )

find_library(PTW_LIBRARY_DEBUG
  NAMES 
    libpthreadVC3d  pthreadVC3d  libpthreadGC3d  pthreadGC3d
    libpthreadVCE3d pthreadVCE3d libpthreadGCE3d pthreadGCE3d
    libpthreadVSE3d pthreadVSE3d libpthreadGSE3d pthreadGSE3d
  HINTS
    ENV PTW_ DIR
  PATH_SUFFIXES ${LIB_PATH_SUFFIXES}
  PATHS ${PTW_PATH}
  )

include(SelectLibraryConfigurations)

select_library_configurations(PTW)

set(PTW_LIBRARY_PATH "")
if (PTW_LIBRARY)
  get_filename_component(PTW_LIBRARY_PATH "${PTW_LIBRARY}" DIRECTORY)
endif ()
set(PTW_INCLUDE_DIRS ${PTW_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
  PTW
  REQUIRED_VARS PTW_LIBRARY_PATH PTW_INCLUDE_DIRS
  )

set(PTW_LIBRARY)
set(PTW_INCLUDE_DIR)
