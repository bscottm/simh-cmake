## PDP-10 simulator family

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

set(PDP10_DEFINES VM_PDP10)
set(PDP10_INCLUDES "${PDP10D}" "${PDP11D}")

add_simulator(pdp10 "${PDP10_SOURCES}" "${PDP10_DEFINES}" "${PDP10_INCLUDES}" USEI64)


set(KA10_SOURCES
    kx10_cpu.c 
    kx10_sys.c 
    kx10_df.c
    kx10_dp.c 
    kx10_mt.c 
    kx10_cty.c
    kx10_lp.c 
    kx10_pt.c 
    kx10_dc.c
    kx10_rp.c 
    kx10_rc.c 
    kx10_dt.c
    kx10_dk.c 
    kx10_cr.c 
    kx10_cp.c
    kx10_tu.c 
    kx10_rs.c 
    ka10_pd.c
    kx10_imp.c 
    ka10_tk10.c 
    ka10_mty.c
    ka10_imx.c 
    ka10_ch10.c 
    ka10_stk.c
    ka10_ten11.c 
    ka10_auxcpu.c
    ka10_pmp.c
    ka10_dkb.c 
    pdp6_dct.c 
    pdp6_dtc.c
    pdp6_mtc.c 
    pdp6_dsk.c 
    pdp6_dcs.c
    ka10_dpk.c 
    kx10_dpy.c 
    ${DISPLAYL} 
    ${DISPLAY340})

set(KA10_DEFINES KA=1 USE_SIM_CARD USE_DISPLAY)
set(KA10_INCLUDES "${PDP10_INCLUDES}")
add_simulator(pdp10-ka "${KA10_SOURCES}" "${KA10_DEFINES}" "${KA10_INCLUDES}" USEI64)

if (NOT WIN32 AND PANDA_LIGHTS)
    # ONLY for Panda display.
    target_sources(pdp10-ka PUBLIC ka10_lights.c)
    target_compile_definitions(pdp10-ka PUBLIC PANDA_LIGHTS)
    target_link_libraries(pdp10-ka "usb-1.0")
endif ()


set(KI10_SOURCES
    kx10_cpu.c 
    kx10_sys.c 
    kx10_df.c
	kx10_dp.c 
    kx10_mt.c 
    kx10_cty.c
	kx10_lp.c 
    kx10_pt.c 
    kx10_dc.c
	kx10_rp.c 
    kx10_rc.c 
    kx10_dt.c
	kx10_dk.c 
    kx10_cr.c 
    kx10_cp.c
	kx10_tu.c 
    kx10_rs.c 
    kx10_imp.c
	kx10_dpy.c
    ${DISPLAYL} 
    ${DISPLAY340})

set(KI10_DEFINES KI=1 USE_SIM_CARD USE_DISPLAY)
add_simulator(pdp10-ki "${KI10_SOURCES}" "${KI10_DEFINES}" "${PDP10_INCLUDES}" USEI64)

if (NOT WIN32 AND PANDA_LIGHTS)
    # ONLY for Panda display.
    target_sources(pdp10-ki PUBLIC ka10_lights.c)
    target_compile_definitions(pdp10-ki PUBLIC PANDA_LIGHTS)
    target_link_libraries(pdp10-ki "usb-1.0")
endif ()

set(PDP6_SOURCES
    kx10_cpu.c 
    kx10_sys.c 
    kx10_cty.c
	kx10_lp.c 
    kx10_pt.c 
    kx10_cr.c
	kx10_cp.c 
    pdp6_dct.c 
    pdp6_dtc.c
	pdp6_mtc.c 
    pdp6_dsk.c 
    pdp6_dcs.c
	kx10_dpy.c
    ${DISPLAYL} 
    ${DISPLAY340})

set(PDP6_DEFINES PDP6=1 USE_SIM_CARD USE_DISPLAY)
add_simulator(pdp6 "${PDP6_SOURCES}" "${PDP6_DEFINES}" "${PDP10_INCLUDES}" USEI64)
