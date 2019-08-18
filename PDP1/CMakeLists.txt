# PDP-1 simulator:

set(PDP1_DEFINES "")
if (WITH_VIDEO)
    set(PDP1_DEFINES "${PDP1_DEFINES}" USE_DISPLAY DISPLAY_TYPE=DIS_TYPE30 PIX_SCALE=RES_HALF)
endif ()

add_simulator(pdp1 "${PDP1_SOURCES}" "${PDP1_DEFINES}" "${PDP1_INCLUDES}"
    SOURCES
	pdp1_lp.c
	pdp1_cpu.c
	pdp1_stddev.c
	pdp1_sys.c
	pdp1_dt.c
	pdp1_drm.c
	pdp1_clk.c
	pdp1_dcs.c
	pdp1_dpy.c
	${DISPLAYL}
    DEFINES
	${PDP1_DEFINES}
    INCLUDES
	${PDP1D}
    TEST pdp1)
