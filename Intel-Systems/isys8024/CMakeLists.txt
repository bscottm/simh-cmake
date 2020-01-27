## Intel-Systems/isys8024 simulator
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

add_simulator(isys8024
    SOURCES
        ${ISYS8024C}/i8080.c
        isys8024_sys.c
        ${ISYS8024C}/i8251.c
        ${ISYS8024C}/i8253.c
        ${ISYS8024C}/i8255.c
        ${ISYS8024C}/i8259.c
        ${ISYS8024C}/ieprom.c
        ${ISYS8024C}/iram8.c
        ${ISYS8024C}/multibus.c
        isbc8024.c
        ${ISYS8024C}/isbc064.c
        ${ISYS8024C}/isbc208.c
        ${ISYS8024C}/isbc202.c
        ${ISYS8024C}/isbc201.c
        ${ISYS8024C}/isbc206.c
        ${ISYS8024C}/isbc464.c
        ${ISYS8024C}/zx200a.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST isys8024)
