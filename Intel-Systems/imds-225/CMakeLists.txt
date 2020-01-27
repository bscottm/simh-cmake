## Intel-Systems/imds-225 simulator
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

add_simulator(imds-225
    SOURCES
        ${IMDS225C}/i8080.c
        imds-225_sys.c
        ${IMDS225C}/i8251.c
        ${IMDS225C}/i8255.c
        ${IMDS225C}/i8259.c
        ${IMDS225C}/i8253.c
        ${IMDS225C}/ieprom.c
        ${IMDS225C}/iram8.c
        ${IMDS225C}/multibus.c
        ${IMDS225C}/ipc.c
        ${IMDS225C}/ipc-cont.c
        ${IMDS225C}/ioc-cont.c
        ${IMDS225C}/isbc202.c
        ${IMDS225C}/isbc201.c
        ${IMDS225C}/zx200a.c
        ${IMDS225C}/isbc464.c
        ${IMDS225C}/isbc206.c
        ${IMDS225C}/isbc208.c
        ${IMDS220C}/isbc064.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST imds-225)
