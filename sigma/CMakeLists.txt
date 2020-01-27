## sigma simulator
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

add_simulator(sigma
    SOURCES
        sigma_cpu.c
        sigma_sys.c
        sigma_cis.c
        sigma_coc.c
        sigma_dk.c
        sigma_dp.c
        sigma_fp.c
        sigma_io.c
        sigma_lp.c
        sigma_map.c
        sigma_mt.c
        sigma_pt.c
        sigma_rad.c
        sigma_rtc.c
        sigma_tt.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST sigma)
