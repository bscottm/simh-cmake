## PDP-18B-based simulators

set(PDP18B_SOURCES
    pdp18b_dt.c
    pdp18b_drm.c
    pdp18b_cpu.c
    pdp18b_lp.c
    pdp18b_mt.c
    pdp18b_rf.c
    pdp18b_rp.c
    pdp18b_stddev.c
    pdp18b_sys.c
    pdp18b_rb.c
    pdp18b_tt1.c
    pdp18b_fpp.c
    pdp18b_g2tty.c
    pdp18b_dr15.c)

set(PDP4_DEFINES PDP4)
set(PDP4_INCLUDES "${PDP18BD}")
add_simulator(pdp4 "${PDP18B_SOURCES}" "${PDP4_DEFINES}" "${PDP4_INCLUDES}")

set(PDP7_DEFINES PDP7)
set(PDP7_INCLUDES "${PDP18BD}")
add_simulator(pdp7 "${PDP18B_SOURCES}" "${PDP7_DEFINES}" "${PDP7_INCLUDES}")

set(PDP9_DEFINES PDP9)
set(PDP9_INCLUDES "${PDP18BD}")
add_simulator(pdp9 "${PDP18B_SOURCES}" "${PDP9_DEFINES}" "${PDP9_INCLUDES}")

set(PDP15_DEFINES PDP15)
set(PDP15_INCLUDES "${PDP18BD}")
add_simulator(pdp15 "${PDP18B_SOURCES}" "${PDP15_DEFINES}" "${PDP15_INCLUDES}")
