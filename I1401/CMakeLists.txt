## I1401 simulator
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

add_simulator(i1401
    SOURCES
        i1401_lp.c
        i1401_cpu.c
        i1401_iq.c
        i1401_cd.c
        i1401_mt.c
        i1401_dp.c
        i1401_sys.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST i1401)
