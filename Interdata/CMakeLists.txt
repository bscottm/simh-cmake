## Interdata simulators:

set(ID16_SOURCES
    id16_cpu.c
    id16_sys.c
    id_dp.c
    id_fd.c
    id_fp.c
    id_idc.c
    id_io.c
    id_lp.c
    id_mt.c
    id_pas.c
    id_pt.c
    id_tt.c
    id_uvc.c
    id16_dboot.c
    id_ttp.c)

set(ID16_DEFINES "")
set(ID16_INCLUDES "${ID16D}")
add_simulator(id16 "${ID16_SOURCES}" "${ID16_DEFINES}" "${ID16_INCLUDES}")


set(ID32_SOURCES
    id32_cpu.c
    id32_sys.c
    id_dp.c
    id_fd.c
    id_fp.c
    id_idc.c
    id_io.c
    id_lp.c
    id_mt.c
    id_pas.c
    id_pt.c
    id_tt.c
    id_uvc.c
    id32_dboot.c
    id_ttp.c)

set(ID32_DEFINES "")
set(ID32_INCLUDES "${ID32D}")
add_simulator(id32 "${ID32_SOURCES}" "${ID32_DEFINES}" "${ID32_INCLUDES}")
