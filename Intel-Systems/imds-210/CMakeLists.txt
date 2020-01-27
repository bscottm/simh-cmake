## Intel-Systems/imds-210 simulator
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

add_simulator(imds-210
    SOURCES
        ${IMDS210C}/i8080.c
        imds-210_sys.c
        ${IMDS210C}/i8251.c
        ${IMDS210C}/i8255.c
        ${IMDS210C}/i8259.c
        ${IMDS210C}/i8253.c
        ${IMDS210C}/ieprom.c
        ${IMDS210C}/iram8.c
        ${IMDS210C}/multibus.c
        ${IMDS210C}/ipb.c
        ${IMDS210C}/ipc-cont.c
        ${IMDS210C}/ioc-cont.c
        ${IMDS210C}/isbc202.c
        ${IMDS210C}/isbc201.c
        ${IMDS210C}/isbc206.c
        ${IMDS210C}/isbc208.c
        ${IMDS210C}/isbc464.c
        ${IMDS210C}/zx200a.c
        ${IMDS210C}/isbc064.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST imds-210)
