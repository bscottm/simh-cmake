## VAX simulators:

## Default VAX simulator (aka MicroVAX 3900):
set(VAX_SOURCES
      vax_cpu.c
      vax_cpu1.c
      vax_fpa.c
      vax_io.c
      vax_cis.c
      vax_octa.c
      vax_cmode.c
      vax_mmu.c
      vax_stddev.c
      vax_sysdev.c
      vax_sys.c
      vax_syscm.c
      vax_syslist.c
      vax_vc.c
      vax_lk.c
      vax_vs.c
      vax_2681.c
      ${PDP11D}/pdp11_rl.c
      ${PDP11D}/pdp11_rq.c
      ${PDP11D}/pdp11_ts.c
      ${PDP11D}/pdp11_dz.c
      ${PDP11D}/pdp11_lp.c
      ${PDP11D}/pdp11_tq.c
      ${PDP11D}/pdp11_xq.c
      ${PDP11D}/pdp11_vh.c
      ${PDP11D}/pdp11_cr.c
      ${PDP11D}/pdp11_td.c
      ${PDP11D}/pdp11_io_lib.c)

set(VAX_DEFINES VM_VAX USE_INT64 USE_ADDR64 USE_SIM_VIDEO)
set(VAX_INCLUDES "${VAXD}" "${PDP11D}")
add_simulator(microvax3900 "${VAX_SOURCES}" "${VAX_DEFINES}" "${VAX_INCLUDES}")

set(VAX610_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax610_stddev.c
    vax610_sysdev.c
    vax610_io.c
    vax610_syslist.c
    vax610_mem.c
    vax_vc.c
    vax_lk.c
    vax_vs.c
    vax_2681.c
    ${PDP11D}/pdp11_rl.c
    ${PDP11D}/pdp11_rq.c
    ${PDP11D}/pdp11_ts.c
    ${PDP11D}/pdp11_dz.c
    ${PDP11D}/pdp11_lp.c
    ${PDP11D}/pdp11_tq.c
    ${PDP11D}/pdp11_xq.c
    ${PDP11D}/pdp11_vh.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_td.c
    ${PDP11D}/pdp11_io_lib.c)

set(VAX610_DEFINES VM_VAX VAX_610 USE_INT64 USE_ADDR64 USE_DISPLAY)
add_simulator(microvax1 "${VAX610_SOURCES}" "${VAX610_DEFINES}" "${VAX_INCLUDES}")

set(VAX630_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax_watch.c
    vax630_stddev.c
    vax630_sysdev.c
    vax630_io.c
    vax630_syslist.c
    vax_va.c
    vax_vc.c
    vax_lk.c
    vax_vs.c
    vax_2681.c
    vax_gpx.c
    ${PDP11D}/pdp11_rl.c
    ${PDP11D}/pdp11_rq.c
    ${PDP11D}/pdp11_ts.c
    ${PDP11D}/pdp11_dz.c
    ${PDP11D}/pdp11_lp.c
    ${PDP11D}/pdp11_tq.c
    ${PDP11D}/pdp11_xq.c
    ${PDP11D}/pdp11_vh.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_td.c
    ${PDP11D}/pdp11_io_lib.c)

set(VAX620_DEFINES VM_VAX VAX_620 USE_INT64 USE_ADDR64)

set(VAX630_DEFINES VM_VAX VAX_630 USE_INT64 USE_ADDR64 USE_SIM_VIDEO USE_DISPLAY)

add_simulator(rtvax1000 "${VAX630_SOURCES}" "${VAX620_DEFINES}" "${VAX_INCLUDES}")
add_simulator(microvax2 "${VAX630_SOURCES}" "${VAX630_DEFINES}" "${VAX_INCLUDES}")

set(VAX730_SOURCES
    ${VAXD}/vax_cpu.c
    ${VAXD}/vax_cpu1.c
    ${VAXD}/vax_fpa.c
    ${VAXD}/vax_cis.c
    ${VAXD}/vax_octa.c
    ${VAXD}/vax_cmode.c
    ${VAXD}/vax_mmu.c
    ${VAXD}/vax_sys.c
    ${VAXD}/vax_syscm.c
    ${VAXD}/vax730_stddev.c
    ${VAXD}/vax730_sys.c
    ${VAXD}/vax730_mem.c
    ${VAXD}/vax730_uba.c
    ${VAXD}/vax730_rb.c
    ${VAXD}/vax730_syslist.c
    ${PDP11D}/pdp11_rl.c
    ${PDP11D}/pdp11_rq.c
    ${PDP11D}/pdp11_ts.c
    ${PDP11D}/pdp11_dz.c
    ${PDP11D}/pdp11_lp.c
    ${PDP11D}/pdp11_tq.c
    ${PDP11D}/pdp11_xu.c
    ${PDP11D}/pdp11_ry.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_hk.c
    ${PDP11D}/pdp11_vh.c
    ${PDP11D}/pdp11_dmc.c
    ${PDP11D}/pdp11_td.c
    ${PDP11D}/pdp11_tc.c
    ${PDP11D}/pdp11_rk.c
    ${PDP11D}/pdp11_io_lib.c
    ${PDP11D}/pdp11_ch.c)

set(VAX730_DEFINES VM_VAX VAX_730 USE_INT64 USE_ADDR64)
add_simulator(vax730 "${VAX730_SOURCES}" "${VAX730_DEFINES}" "${VAX_INCLUDES}")

set(VAX750_SOURCES
    ${VAXD}/vax_cpu.c
    ${VAXD}/vax_cpu1.c
    ${VAXD}/vax_fpa.c
    ${VAXD}/vax_cis.c
    ${VAXD}/vax_octa.c
    ${VAXD}/vax_cmode.c
    ${VAXD}/vax_mmu.c
    ${VAXD}/vax_sys.c
    ${VAXD}/vax_syscm.c
    ${VAXD}/vax750_stddev.c
    ${VAXD}/vax750_cmi.c
    ${VAXD}/vax750_mem.c
    ${VAXD}/vax750_uba.c
    ${VAXD}/vax7x0_mba.c
    ${VAXD}/vax750_syslist.c
    ${PDP11D}/pdp11_rl.c
    ${PDP11D}/pdp11_rq.c
    ${PDP11D}/pdp11_ts.c
    ${PDP11D}/pdp11_dz.c
    ${PDP11D}/pdp11_lp.c
    ${PDP11D}/pdp11_tq.c
    ${PDP11D}/pdp11_xu.c
    ${PDP11D}/pdp11_ry.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_hk.c
    ${PDP11D}/pdp11_rp.c
    ${PDP11D}/pdp11_tu.c
    ${PDP11D}/pdp11_vh.c
    ${PDP11D}/pdp11_dmc.c
    ${PDP11D}/pdp11_dup.c
    ${PDP11D}/pdp11_td.c
    ${PDP11D}/pdp11_tc.c
    ${PDP11D}/pdp11_rk.c
    ${PDP11D}/pdp11_io_lib.c
    ${PDP11D}/pdp11_ch.c)

set(VAX750_DEFINES VM_VAX VAX_750 USE_INT64 USE_ADDR64)
add_simulator(vax750 "${VAX750_SOURCES}" "${VAX750_DEFINES}" "${VAX_INCLUDES}")

set(VAX780_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax780_stddev.c
    vax780_sbi.c
    vax780_mem.c
    vax780_uba.c
    vax7x0_mba.c
    vax780_fload.c
    vax780_syslist.c
    ${PDP11D}/pdp11_rl.c
    ${PDP11D}/pdp11_rq.c
    ${PDP11D}/pdp11_ts.c
    ${PDP11D}/pdp11_dz.c
    ${PDP11D}/pdp11_lp.c
    ${PDP11D}/pdp11_tq.c
    ${PDP11D}/pdp11_xu.c
    ${PDP11D}/pdp11_ry.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_rp.c
    ${PDP11D}/pdp11_tu.c
    ${PDP11D}/pdp11_hk.c
    ${PDP11D}/pdp11_vh.c
    ${PDP11D}/pdp11_dmc.c
    ${PDP11D}/pdp11_dup.c
    ${PDP11D}/pdp11_td.c
    ${PDP11D}/pdp11_tc.c
    ${PDP11D}/pdp11_rk.c
    ${PDP11D}/pdp11_io_lib.c
    ${PDP11D}/pdp11_ch.c)

set(VAX780_DEFINES VM_VAX VAX_780 USE_INT64 USE_ADDR64)
add_simulator(vax780 "${VAX780_SOURCES}" "${VAX780_DEFINES}" "${VAX_INCLUDES}")

set(VAX8200_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax_watch.c
    vax820_stddev.c
    vax820_bi.c
    vax820_mem.c
    vax820_uba.c
    vax820_ka.c
    vax820_syslist.c
    ${PDP11D}/pdp11_rl.c
    ${PDP11D}/pdp11_rq.c
    ${PDP11D}/pdp11_ts.c
    ${PDP11D}/pdp11_dz.c
    ${PDP11D}/pdp11_lp.c
    ${PDP11D}/pdp11_tq.c
    ${PDP11D}/pdp11_xu.c
    ${PDP11D}/pdp11_ry.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_hk.c
    ${PDP11D}/pdp11_vh.c
    ${PDP11D}/pdp11_dmc.c
    ${PDP11D}/pdp11_td.c
    ${PDP11D}/pdp11_tc.c
    ${PDP11D}/pdp11_rk.c
    ${PDP11D}/pdp11_io_lib.c
    ${PDP11D}/pdp11_ch.c)

set(VAX8200_DEFINES VM_VAX VAX_820 USE_INT64 USE_ADDR64)
add_simulator(vax8200 "${VAX8200_SOURCES}" "${VAX8200_DEFINES}" "${VAX_INCLUDES}")

set(VAX8600_SOURCES 
    ${VAXD}/vax_cpu.c
    ${VAXD}/vax_cpu1.c
    ${VAXD}/vax_fpa.c
    ${VAXD}/vax_cis.c
    ${VAXD}/vax_octa.c
    ${VAXD}/vax_cmode.c
    ${VAXD}/vax_mmu.c
    ${VAXD}/vax_sys.c
    ${VAXD}/vax_syscm.c
    ${VAXD}/vax860_stddev.c
    ${VAXD}/vax860_sbia.c
    ${VAXD}/vax860_abus.c
    ${VAXD}/vax780_uba.c
    ${VAXD}/vax7x0_mba.c
    ${VAXD}/vax860_syslist.c
    ${PDP11D}/pdp11_rl.c
    ${PDP11D}/pdp11_rq.c
    ${PDP11D}/pdp11_ts.c
    ${PDP11D}/pdp11_dz.c
    ${PDP11D}/pdp11_lp.c
    ${PDP11D}/pdp11_tq.c
    ${PDP11D}/pdp11_xu.c
    ${PDP11D}/pdp11_ry.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_rp.c
    ${PDP11D}/pdp11_tu.c
    ${PDP11D}/pdp11_hk.c
    ${PDP11D}/pdp11_vh.c
    ${PDP11D}/pdp11_dmc.c
    ${PDP11D}/pdp11_dup.c
    ${PDP11D}/pdp11_td.c
    ${PDP11D}/pdp11_tc.c
    ${PDP11D}/pdp11_rk.c
    ${PDP11D}/pdp11_io_lib.c
    ${PDP11D}/pdp11_ch.c)

set(VAX8600_DEFINES VM_VAX VAX_860 USE_INT64 USE_ADDR64)
add_simulator(vax8600 "${VAX8600_SOURCES}" "${VAX8600_DEFINES}" "${VAX_INCLUDES}")

set(VAX410_SOURCES 
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax_watch.c
    vax_nar.c
    vax4xx_stddev.c
    vax410_sysdev.c
    vax410_syslist.c
    vax4xx_dz.c
    vax4xx_rd.c
    vax4xx_rz80.c
    vax_xs.c
    vax4xx_va.c
    vax4xx_vc.c
    vax_lk.c
    vax_vs.c
    vax_gpx.c)

set(VAX410_DEFINES VM_VAX VAX_410 USE_INT64 USE_ADDR64 USE_SIM_VIDEO)
add_simulator(microvax2000 "${VAX8600_SOURCES}" "${VAX8600_DEFINES}" "${VAX_INCLUDES}")

set(VAX420_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax_watch.c
    vax_nar.c
    vax4xx_stddev.c
    vax420_sysdev.c
    vax420_syslist.c
    vax4xx_dz.c
    vax4xx_rd.c
    vax4xx_rz80.c
    vax_xs.c
    vax4xx_va.c
    vax4xx_vc.c
    vax4xx_ve.c
    vax_lk.c
    vax_vs.c
    vax_gpx.c)

set(VAX420_DEFINES VM_VAX VAX_420 USE_INT64 USE_ADDR64 USE_SIM_VIDEO)
set(VAX411_DEFINES "${VAX420_DEFINES}" VAX_411)
set(VAX412_DEFINES "${VAX420_DEFINES}" VAX_412)
set(VAX41A_DEFINES "${VAX420_DEFINES}" VAX_41A)
set(VAX41D_DEFINES "${VAX420_DEFINES}" VAX_41D)
set(VAX42A_DEFINES "${VAX420_DEFINES}" VAX_42A)
set(VAX42B_DEFINES "${VAX420_DEFINES}" VAX_42B)

add_simulator(infoserver100     "${VAX420_SOURCES}" "${VAX411_DEFINES}" "${VAX_INCLUDES}")
add_simulator(infoserver150vxt  "${VAX420_SOURCES}" "${VAX412_DEFINES}" "${VAX_INCLUDES}")
add_simulator(microvax3100      "${VAX420_SOURCES}" "${VAX41A_DEFINES}" "${VAX_INCLUDES}")
add_simulator(microvax3100e     "${VAX420_SOURCES}" "${VAX41D_DEFINES}" "${VAX_INCLUDES}")
add_simulator(vaxstation3100m30 "${VAX420_SOURCES}" "${VAX42A_DEFINES}" "${VAX_INCLUDES}")
add_simulator(vaxstation3100m38 "${VAX420_SOURCES}" "${VAX42B_DEFINES}" "${VAX_INCLUDES}")

set(VAX43_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax_watch.c
    vax_nar.c
    vax4xx_stddev.c
    vax43_sysdev.c
    vax43_syslist.c
    vax4xx_dz.c
    vax4xx_rz80.c
    vax_xs.c
    vax4xx_vc.c
    vax4xx_ve.c
    vax_lk.c vax_vs.c)

set(VAX43_DEFINES VM_VAX VAX_43 USE_INT64 USE_ADDR64 USE_SIM_VIDEO)
add_simulator(vaxstation3100m76 "${VAX43_SOURCES}" "${VAX43_DEFINES}" "${VAX_INCLUDES}")

set(VAX440_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax_watch.c
    vax_nar.c
    vax4xx_stddev.c
    vax440_sysdev.c
    vax440_syslist.c
    vax4xx_dz.c
    vax_xs.c
    vax_lk.c
    vax_vs.c
    vax4xx_rz94.c)

set(VAX440_DEFINES VM_VAX VAX_440 USE_INT64 USE_ADDR64)
set(VAX46_DEFINES "${VAX440_DEFINES}" VAX_46)
set(VAX47_DEFINES "${VAX440_DEFINES}" VAX_47)
set(VAX48_DEFINES "${VAX440_DEFINES}" VAX_48)

add_simulator(vaxstation4000m60 "${VAX440_SOURCES}" "${VAX46_DEFINES}" "${VAX_INCLUDES}")
add_simulator(vaxstation3100m80 "${VAX440_SOURCES}" "${VAX47_DEFINES}" "${VAX_INCLUDES}")
add_simulator(vaxstation4100lvc "${VAX440_SOURCES}" "${VAX48_DEFINES}" "${VAX_INCLUDES}")

set(IS1000_SOURCES
    vax_cpu.c
    vax_cpu1.c
    vax_fpa.c
    vax_cis.c
    vax_octa.c
    vax_cmode.c
    vax_mmu.c
    vax_sys.c
    vax_syscm.c
    vax_watch.c
    vax_nar.c
    vax_xs.c
    vax4xx_rz94.c
    vax4nn_stddev.c
    is1000_sysdev.c
    is1000_syslist.c)

set(IS1000_DEFINES VM_VAX IS_1000 USE_INT64 USE_ADDR64)
add_simulator(infoserver1000 "${IS1000_SOURCES}" "${IS1000_DEFINES}" "${VAX_INCLUDES}")
