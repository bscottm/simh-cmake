## Lincoln Labs' TX-0 simulator:

if (BUILD_WITH_DISPLAY)
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
else (BUILD_WITH_DISPLAY)
    message(STATUS "SDL2 video support unavailable: skipping TX-0")
endif (BUILD_WITH_DISPLAY)
