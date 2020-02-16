## PDP10 simulators
##
## This is an automagically generated file. Do NOT EDIT.
## Any changes you make will be overwritten!!
##
## Make changes to the SIMH top-level makefile and then run the
## "cmake/generate.py" script to regenerate these files.
##
##     python -m cmake/generate --help
##
## ------------------------------------------------------------

add_simulator(pdp10
    SOURCES
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
        ${PDP11D}/pdp11_ch.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PDP11D}
    DEFINES
        VM_PDP10
    INT64
    TEST pdp10)

if (BUILD_WITH_VIDEO)
    add_simulator(pdp10-ka
        SOURCES
            ${KA10D}/kx10_cpu.c
            ${KA10D}/kx10_sys.c
            ${KA10D}/kx10_df.c
            ${KA10D}/kx10_dp.c
            ${KA10D}/kx10_mt.c
            ${KA10D}/kx10_cty.c
            ${KA10D}/kx10_lp.c
            ${KA10D}/kx10_pt.c
            ${KA10D}/kx10_dc.c
            ${KA10D}/kx10_rp.c
            ${KA10D}/kx10_rc.c
            ${KA10D}/kx10_dt.c
            ${KA10D}/kx10_dk.c
            ${KA10D}/kx10_cr.c
            ${KA10D}/kx10_cp.c
            ${KA10D}/kx10_tu.c
            ${KA10D}/kx10_rs.c
            ${KA10D}/ka10_pd.c
            ${KA10D}/kx10_imp.c
            ${KA10D}/ka10_tk10.c
            ${KA10D}/ka10_mty.c
            ${KA10D}/ka10_imx.c
            ${KA10D}/ka10_ch10.c
            ${KA10D}/ka10_stk.c
            ${KA10D}/ka10_ten11.c
            ${KA10D}/ka10_auxcpu.c
            ${KA10D}/ka10_pmp.c
            ${KA10D}/ka10_dkb.c
            ${KA10D}/pdp6_dct.c
            ${KA10D}/pdp6_dtc.c
            ${KA10D}/pdp6_mtc.c
            ${KA10D}/pdp6_dsk.c
            ${KA10D}/pdp6_dcs.c
            ${KA10D}/ka10_dpk.c
            ${KA10D}/kx10_dpy.c
            ka10_ai.c
            ${DISPLAY340}
        INCLUDES
            ${KA10D}
        DEFINES
            KA=1
        INT64
        VIDEO
        TEST ka10)
endif (BUILD_WITH_VIDEO)

if (PANDA_LIGHTS)
  target_sources(pdp10-ka PUBLIC ${KA10D}/ka10_lights.c)
  target_compile_definitions(pdp10-ka PUBLIC PANDA_LIGHTS)
  target_link_libraries(pdp10-ka PUBLIC usb-1.0)
endif (PANDA_LIGHTS)

if (BUILD_WITH_VIDEO)
    add_simulator(pdp10-ki
        SOURCES
            ${KI10D}/kx10_cpu.c
            ${KI10D}/kx10_sys.c
            ${KI10D}/kx10_df.c
            ${KI10D}/kx10_dp.c
            ${KI10D}/kx10_mt.c
            ${KI10D}/kx10_cty.c
            ${KI10D}/kx10_lp.c
            ${KI10D}/kx10_pt.c
            ${KI10D}/kx10_dc.c
            ${KI10D}/kx10_rp.c
            ${KI10D}/kx10_rc.c
            ${KI10D}/kx10_dt.c
            ${KI10D}/kx10_dk.c
            ${KI10D}/kx10_cr.c
            ${KI10D}/kx10_cp.c
            ${KI10D}/kx10_tu.c
            ${KI10D}/kx10_rs.c
            ${KI10D}/kx10_imp.c
            ${KI10D}/kx10_dpy.c
            ${DISPLAY340}
        INCLUDES
            ${KI10D}
        DEFINES
            KI=1
        INT64
        VIDEO
        TEST ki10)
endif (BUILD_WITH_VIDEO)

if (BUILD_WITH_VIDEO)
    add_simulator(pdp6
        SOURCES
            ${PDP6D}/kx10_cpu.c
            ${PDP6D}/kx10_sys.c
            ${PDP6D}/kx10_cty.c
            ${PDP6D}/kx10_lp.c
            ${PDP6D}/kx10_pt.c
            ${PDP6D}/kx10_cr.c
            ${PDP6D}/kx10_cp.c
            ${PDP6D}/pdp6_dct.c
            ${PDP6D}/pdp6_dtc.c
            ${PDP6D}/pdp6_mtc.c
            ${PDP6D}/pdp6_dsk.c
            ${PDP6D}/pdp6_dcs.c
            ${PDP6D}/kx10_dpy.c
            ${DISPLAY340}
        INCLUDES
            ${PDP6D}
        DEFINES
            PDP6=1
        INT64
        VIDEO
        TEST pdp6)
endif (BUILD_WITH_VIDEO)
