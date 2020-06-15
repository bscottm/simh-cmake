## Intel-Systems/imds-800 simulator
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

add_simulator(imds-800
    SOURCES
        ${IMDS800C}/i8080.c
        imds-800_sys.c
        cpu.c
        front_panel.c
        monitor.c
        ${IMDS800C}/ieprom1.c
        ${IMDS800C}/i8251.c
        ${IMDS800C}/ieprom.c
        ${IMDS800C}/multibus.c
        ${IMDS800C}/isbc064.c
        ${IMDS800C}/isbc202.c
        ${IMDS800C}/isbc201.c
        ${IMDS800C}/zx200a.c
        ${IMDS800C}/isbc464.c
        ${IMDS800C}/isbc206.c
        ${IMDS800C}/i3214.c
        ${IMDS225C}/isbc208.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST imds-800)
