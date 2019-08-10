## IBM 7094:

set(I7094_SOURCES
    i7094_cpu.c
    i7094_cpu1.c
    i7094_io.c
    i7094_cd.c
    i7094_clk.c
    i7094_com.c
    i7094_drm.c
    i7094_dsk.c
    i7094_sys.c
    i7094_lp.c
    i7094_mt.c
    i7094_binloader.c)

set(I7094_DEFINES DUSE_INT64)
set(I7094_INCLUDES "${I7094D}")
add_simulator(i7094 "${I7094_SOURCES}" "${I7094_DEFINES}" "${I7094_INCLUDES}")
