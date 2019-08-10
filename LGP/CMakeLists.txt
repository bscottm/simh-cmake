## LGP simulator:

set(LGPD "${CMAKE_SOURCE_DIR}/LGP")

set(LGP_SOURCES lgp_cpu.c lgp_stddev.c lgp_sys.c)
set(LGP_DEFINES "")
set(LGP_INCLUDES "${LGPD}")
add_simulator(lgp "${LGP_SOURCES}" "${LGP_DEFINES}" "${LGP_INCLUDES}")
