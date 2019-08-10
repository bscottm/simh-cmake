## The NOVA simulator:

set(NOVA_SOURCES
    nova_sys.c
    nova_cpu.c
    nova_dkp.c
    nova_dsk.c
    nova_lp.c
    nova_mta.c
    nova_plt.c
    nova_pt.c
    nova_clk.c
    nova_tt.c
    nova_tt1.c
    nova_qty.c)

set(NOVA_DEFINES "")
set(NOVA_INCLUDES "${NOVAD}")
add_simulator(nova "${NOVA_SOURCES}" "${NOVA_DEFINES}" "${NOVA_INCLUDES}")

set(ECLIPSE_SOURCES
    eclipse_cpu.c
    eclipse_tt.c
    nova_sys.c
    nova_dkp.c
    nova_dsk.c
    nova_lp.c
    nova_mta.c
    nova_plt.c
    nova_pt.c
    nova_clk.c
    nova_tt1.c
    nova_qty.c)

set(ECLIPSE_DEFINES ECLIPSE)
add_simulator(eclipse "${ECLIPSE_SOURCES}" "${ECLIPSE_DEFINES}" "${NOVA_INCLUDES}")
