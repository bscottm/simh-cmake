## Locate the VDE2/VDE4 libvdeplug headers and library.
##
## :::
##
## Author: B. Scott Michel
## "scooter me fecit"

if (WITH_VDE)
    find_path(VDEPLUG_INCLUDE_DIR libvdeplug.h
            HINTS
                ENV VDEPLUG_DIR
            # path suffixes to search inside ENV{VDEPLUG_DIR}
            PATHS
                ${VDEPLUG_PATH}
            PATH_SUFFIXES
                include/libvdeplug
                include/vde2
                include/VDE2
                include
            )

    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(LIB_PATH_SUFFIXES lib64 lib/x64 lib/amd64 lib/x86_64-linux-gnu lib)
    else ()
      set(LIB_PATH_SUFFIXES lib/x86 lib)
    endif ()

    find_library(VDEPLUG_LIBRARY_RELEASE
            NAMES vdeplug
            HINTS
                ENV VDEPLUG_DIR
            PATH_SUFFIXES
                ${LIB_PATH_SUFFIXES}
            PATHS
                ${VDEPLUG_PATH}
    )

    if (VDEPLUG_INCLUDE_DIR)
        ## TBD: Get version info. The header file doesn't provide a way to grep
        ## for it. vde_switch will output a version number, but can't really
        ## depend on the user having installed the whole VDE package.
    endif ()

    include(SelectLibraryConfigurations)

    select_library_configurations(VDEPLUG)

    set(VDEPLUG_LIBRARIES ${VDEPLUG_LIBRARY})
    set(VDEPLUG_INCLUDE_DIRS ${VDEPLUG_INCLUDE_DIR})

    include(FindPackageHandleStandardArgs)

    ### Note: If the libpcre.cmake configuration file isn't installed,
    ### asking for a version is going to fail.
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(VDE
        REQUIRED VDEPLUG_LIBRARY VDEPLUG_INCLUDE_DIR
        # VERSION_VAR VDEPLUG_VERSION_STRING
    )
endif (WITH_VDE)
