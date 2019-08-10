## VAX simulators:

set(VAXD   "${CMAKE_SOURCE_DIR}/VAX")
set(PDP11D "${CMAKE_SOURCE_DIR}/PDP11")

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
