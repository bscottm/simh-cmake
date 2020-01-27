## TX-0 simulator
##
## This is an automagically generated file. Do NOT EDIT.
## Any changes you make will be overwritten!!
##
## Make changes to the SIMH top-level makefile and then run the
## "cmake/generate.py" script to regenerate these files.
##
##     python -m cmake/generate --help
##
## ------------------------------------------------------------

if (BUILD_WITH_VIDEO)
    add_simulator(tx-0
        SOURCES
            tx0_cpu.c
            tx0_dpy.c
            tx0_stddev.c
            tx0_sys.c
            tx0_sys_orig.c
        INCLUDES
            ${CMAKE_CURRENT_SOURCE_DIR}
        VIDEO
        TEST tx-0)
endif (BUILD_WITH_VIDEO)
