## Honeywell 316/516 simulator:

set(H316D "${CMAKE_SOURCE_DIR}/H316")

set(H316_SOURCES
    h316_stddev.c
    h316_lp.c
    h316_cpu.c
    h316_sys.c
    h316_mt.c
    h316_fhd.c
    h316_dp.c
    h316_rtc.c
    h316_imp.c
    h316_hi.c
    h316_mi.c
    h316_udp.c)

set(H316_DEFINES VM_IMPTIP)
set(H316_INCLUDES "${H316D}")
add_simulator(h316 "${H316_SOURCES}" "${H316_DEFINES}" "${NOVA_INCLUDES}")
