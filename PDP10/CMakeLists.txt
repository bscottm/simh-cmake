## PDP-10 simulator


set(PDP10_SOURCES
    pdp10_fe.c
    ${PDP11D}/pdp11_dz.c
    pdp10_cpu.c
    pdp10_ksio.c
    pdp10_lp20.c
    pdp10_mdfp.c
    pdp10_pag.c
    pdp10_rp.c
    pdp10_sys.c
    pdp10_tim.c
    pdp10_tu.c
    pdp10_xtnd.c
    ${PDP11D}/pdp11_pt.c
    ${PDP11D}/pdp11_ry.c
    ${PDP11D}/pdp11_cr.c
    ${PDP11D}/pdp11_dup.c
    ${PDP11D}/pdp11_dmc.c
    ${PDP11D}/pdp11_kmc.c
    ${PDP11D}/pdp11_xu.c
    ${PDP11D}/pdp11_ch.c)

set(PDP10_DEFINES VM_PDP10 USE_INT64)
set(PDP10_INCLUDES "${PDP10D}" "${PDP11D}")

add_simulator(pdp10 "${PDP10_SOURCES}" "${PDP10_DEFINES}" "${PDP10_INCLUDES}")

