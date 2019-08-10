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
set(VAX610_INCLUDES "${VAXD}" "${PDP11D}")
add_simulator(microvax1 "${VAX610_SOURCES}" "${VAX610_DEFINES}" "${VAX610_INCLUDES}")

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
set(VAX620_INCLUDES "${VAXD}" "${PDP11D}")

set(VAX630_DEFINES VM_VAX VAX_630 USE_INT64 USE_ADDR64 USE_SIM_VIDEO USE_DISPLAY)
set(VAX630_INCLUDES "${VAXD}" "${PDP11D}")

add_simulator(rtvax1000 "${VAX630_SOURCES}" "${VAX620_DEFINES}" "${VAX620_INCLUDES}")
add_simulator(microvax2 "${VAX630_SOURCES}" "${VAX630_DEFINES}" "${VAX630_INCLUDES}")

