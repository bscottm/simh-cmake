## Intel-Systems/isys8030 simulator
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

add_simulator(isys8030
    SOURCES
        ${ISYS8030C}/i8080.c
        isys8030_sys.c
        ${ISYS8030C}/i8251.c
        ${ISYS8030C}/i8255.c
        ${ISYS8030C}/i8259.c
        ${ISYS8030C}/i8253.c
        ${ISYS8030C}/ieprom.c
        ${ISYS8030C}/iram8.c
        ${ISYS8030C}/multibus.c
        isbc8030.c
        ${ISYS8030C}/isbc202.c
        ${ISYS8030C}/isbc201.c
        ${ISYS8030C}/isbc206.c
        ${ISYS8030C}/isbc464.c
        ${ISYS8030C}/isbc064.c
        ${ISYS8030C}/zx200a.c
        ${ISYS8010C}/isbc208.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST isys8030)
