## I650 simulator
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

add_simulator(i650
    SOURCES
        i650_cpu.c
        i650_cdr.c
        i650_cdp.c
        i650_dsk.c
        i650_mt.c
        i650_sys.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    INT64
    TEST i650)
