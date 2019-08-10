## Lincoln Labs' TX-0 simulator:

set(TX0D "${CMAKE_SOURCE_DIR}/TX-0")

set(TX0_SOURCES
    tx0_cpu.c
    tx0_dpy.c
    tx0_stddev.c
    tx0_sys.c
    tx0_sys_orig.c
    ${DISPLAYL})

set(TX0_DEFINES "USE_DISPLAY")
set(TX0_INCLUDES "${TX0D}")
add_simulator(tx-0 "${TX0_SOURCES}" "${TX0_DEFINES}" "${TX0_INCLUDES}")
