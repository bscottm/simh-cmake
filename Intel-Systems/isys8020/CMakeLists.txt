## Intel-Systems/isys8020 simulator
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

add_simulator(isys8020
    SOURCES
        ${ISYS8020C}/i8080.c
        isys8020_sys.c
        ${ISYS8020C}/i8251.c
        ${ISYS8020C}/i8255.c
        ${ISYS8020C}/ieprom.c
        ${ISYS8020C}/iram8.c
        ${ISYS8020C}/multibus.c
        isbc8020.c
        ${ISYS8020C}/isbc064.c
        ${ISYS8020C}/i8259.c
        ${ISYS8020C}/isbc202.c
        ${ISYS8020C}/isbc201.c
        ${ISYS8020C}/isbc206.c
        ${ISYS8020C}/isbc464.c
        ${ISYS8020C}/zx200a.c
        ${ISYS8020C}/i8253.c
        ${ISYS8020C}/isbc208.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST isys8020)
