## B5500 simulator
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

add_simulator(b5500
    SOURCES
        b5500_cpu.c
        b5500_io.c
        b5500_sys.c
        b5500_dk.c
        b5500_mt.c
        b5500_urec.c
        b5500_dr.c
        b5500_dtc.c
    INCLUDES
        ..
    DEFINES
        B5500
    INT64
    TEST b5500)
