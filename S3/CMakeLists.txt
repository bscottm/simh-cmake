## S3 simulator
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

add_simulator(s3
    SOURCES
        s3_cd.c
        s3_cpu.c
        s3_disk.c
        s3_lp.c
        s3_pkb.c
        s3_sys.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST s3)
