## HP 3000 series simulators:

set(HP3000_SOURCES
    hp_disclib.c
    hp_tapelib.c
    hp3000_atc.c
    hp3000_clk.c
    hp3000_cpu.c
    hp3000_cpu_base.c
    hp3000_cpu_fp.c
    hp3000_cpu_cis.c
    hp3000_ds.c
    hp3000_iop.c
    hp3000_lp.c
    hp3000_mem.c
    hp3000_mpx.c
    hp3000_ms.c
    hp3000_scmb.c
    hp3000_sel.c
    hp3000_sys.c)

set(HP3000_DEFINES "")
set(HP3000_INCLUDES "${HP3000D}")
add_simulator(hp3000 "${HP3000_SOURCES}" "${HP3000_DEFINES}" "${HP3000_INCLUDES}")
