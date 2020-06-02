## Locate the VDE2/VDE4 libvdeplug headers and library.
##
## :::
##
## Author: B. Scott Michel
## "scooter me fecit"

if (WITH_VDE)
    pkg_check_modules(PC_VDE QUIET VDEPLUG)

    if (PC_VDE_VERSION)
        set(VDEPLUG_VERSION "${PC_VDE_VERSION}")
    endif (PC_VDE_VERSION)

    find_path(VDEPLUG_INCLUDE_DIR libvdeplug.h
            HINTS
                ${PC_VDE_INCLUDE_DIRS}
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
            NAMES
                vdeplug
            HINTS
                ${PC_VDE_LIBRARY_DIRS}
            PATH_SUFFIXES
                ${LIB_PATH_SUFFIXES}
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

    find_package(PackageHandleStandardArgs)

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(VDE
        REQUIRED
            VDEPLUG_LIBRARY
            VDEPLUG_INCLUDE_DIR
        # VERSION_VAR VDEPLUG_VERSION_STRING
    )
endif (WITH_VDE)
