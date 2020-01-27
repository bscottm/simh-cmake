## Intel-Systems/imds-220 simulator
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

add_simulator(imds-220
    SOURCES
        ${IMDS220C}/i8080.c
        imds-220_sys.c
        ${IMDS220C}/i8251.c
        ${IMDS220C}/i8255.c
        ${IMDS220C}/i8259.c
        ${IMDS220C}/i8253.c
        ${IMDS220C}/ieprom.c
        ${IMDS220C}/iram8.c
        ${IMDS220C}/multibus.c
        ${IMDS220C}/ipb.c
        ${IMDS220C}/ipc-cont.c
        ${IMDS220C}/ioc-cont.c
        ${IMDS220C}/isbc202.c
        ${IMDS220C}/isbc201.c
        ${IMDS220C}/isbc206.c
        ${IMDS210C}/isbc208.c
        ${IMDS220C}/isbc464.c
        ${IMDS220C}/zx200a.c
        ${IMDS220C}/isbc064.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST imds-220)
