## 3B2 simulator
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

add_simulator(3b2
    SOURCES
        3b2_400_cpu.c
        3b2_400_sys.c
        3b2_400_stddev.c
        3b2_400_mmu.c
        3b2_400_mau.c
        3b2_iu.c
        3b2_if.c
        3b2_id.c
        3b2_dmac.c
        3b2_io.c
        3b2_ports.c
        3b2_ctc.c
        3b2_ni.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    FULL64
    TEST 3b2)
