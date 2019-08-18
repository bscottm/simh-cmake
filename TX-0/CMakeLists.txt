## Lincoln Labs' TX-0 simulator:

add_simulator(tx-0
    SOURCES
	tx0_cpu.c
	tx0_dpy.c
	tx0_stddev.c
	tx0_sys.c
	tx0_sys_orig.c
	${DISPLAYL}
    DEFINES
	USE_DISPLAY
    INCLUDES
	TX-0)
