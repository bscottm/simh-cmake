## IBM 1620 simulator

set(I1620_SOURCES
    i1620_cd.c
    i1620_dp.c
    i1620_pt.c
    i1620_tty.c
    i1620_cpu.c
    i1620_lp.c
    i1620_fp.c
    i1620_sys.c)

set(I1602_DEFINES "")
set(I1620_INCLUDES "${I1620D}")
add_simulator(i1620 "${I1620_SOURCES}" "${I1602_DEFINES}" "${I1620_INCLUDES}")
