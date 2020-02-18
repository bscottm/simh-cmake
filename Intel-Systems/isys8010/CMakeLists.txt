## Intel-Systems/isys8010 simulator
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

add_simulator(isys8010
    SOURCES
        ${ISYS8010C}/i8080.c
        isys8010_sys.c
        ${ISYS8010C}/i8251.c
        ${ISYS8010C}/i8255.c
        ${ISYS8010C}/ieprom.c
        ${ISYS8010C}/iram8.c
        ${ISYS8010C}/multibus.c
        isbc8010.c
        ${ISYS8010C}/isbc064.c
        ${ISYS8010C}/isbc202.c
        ${ISYS8010C}/isbc201.c
        ${ISYS8010C}/zx200a.c
        ${ISYS8010C}/isbc206.c
        ${ISYS8010C}/isbc464.c
        ${ISYS8010C}/isbc208.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST isys8010)
