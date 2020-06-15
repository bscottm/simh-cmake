## Intel-Systems/imds-810 simulator
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

add_simulator(imds-810
    SOURCES
        ${IMDS800C}/i8080.c
        imds-810_sys.c
        cpu.c
        front_panel.c
        monitor.c
        ${IMDS810C}/ieprom1.c
        ${IMDS810C}/i8251.c
        ${IMDS810C}/ieprom.c
        ${IMDS810C}/multibus.c
        ${IMDS810C}/isbc064.c
        ${IMDS810C}/isbc202.c
        ${IMDS810C}/isbc201.c
        ${IMDS810C}/zx200a.c
        ${IMDS810C}/isbc464.c
        ${IMDS810C}/isbc206.c
        ${IMDS800C}/i3214.c
        ${IMDS225C}/isbc208.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TEST imds-810)
