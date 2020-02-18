## SDS simulator
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

add_simulator(sds
    SOURCES
        sds_cpu.c
        sds_drm.c
        sds_dsk.c
        sds_io.c
        sds_lp.c
        sds_mt.c
        sds_mux.c
        sds_rad.c
        sds_stddev.c
        sds_sys.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST sds)
