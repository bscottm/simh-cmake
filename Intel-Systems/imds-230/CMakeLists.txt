## Intel-Systems/imds-230 simulator
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

add_simulator(imds-230
    SOURCES
        ${IMDS230C}/i8080.c
        imds-230_sys.c
        ${IMDS230C}/i8251.c
        ${IMDS230C}/i8255.c
        ${IMDS230C}/i8259.c
        ${IMDS230C}/i8253.c
        ${IMDS230C}/ieprom.c
        ${IMDS230C}/iram8.c
        ${IMDS230C}/multibus.c
        ${IMDS230C}/ipb.c
        ${IMDS230C}/ipc-cont.c
        ${IMDS230C}/ioc-cont.c
        ${IMDS230C}/isbc202.c
        ${IMDS230C}/isbc201.c
        ${IMDS230C}/isbc206.c
        ${IMDS230C}/isbc208.c
        ${IMDS230C}/isbc464.c
        ${IMDS230C}/zx200a.c
        ${IMDS230C}/isbc064.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST imds-230)
