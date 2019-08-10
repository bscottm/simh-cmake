## IBM 1130:

set(IBM1130D Ibm1130)

set(IBM1130_SOURCES
    ibm1130_cpu.c
    ibm1130_cr.c
    ibm1130_disk.c
    ibm1130_stddev.c
    ibm1130_sys.c
    ibm1130_gdu.c
    ibm1130_gui.c
    ibm1130_prt.c
    ibm1130_fmt.c
    ibm1130_ptrp.c
    ibm1130_plot.c
    ibm1130_sca.c
    ibm1130_t2741.c)

set(IBM1130_DEFINES "")
if (WIN32)
    set(IBM1130_DEFINES "${IBM1130_DEFINES}"  GUI_SUPPORT)
endif ()

set(IBM1130_INCLUDES "${IBM1130D}")
add_simulator(ibm1130 "${IBM1130_SOURCES}" "${IBM1130_DEFINES}" "${IBM1130_INCLUDES}")
