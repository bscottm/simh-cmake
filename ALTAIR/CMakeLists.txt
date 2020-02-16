## ALTAIR simulator
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

add_simulator(altair
    SOURCES
        altair_sio.c
        altair_cpu.c
        altair_dsk.c
        altair_sys.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST altair)
