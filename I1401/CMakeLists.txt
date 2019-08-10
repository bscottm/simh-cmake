## IBM 1401 simulator

set(I1401_SOURCES
    i1401_lp.c
    i1401_cpu.c
    i1401_iq.c
    i1401_cd.c
    i1401_mt.c
    i1401_dp.c
    i1401_sys.c)

set(I1401_DEFINES "")
set(I1401_INCLUDES "${I1401D}")
add_simulator(i1401 "${I1401_SOURCES}" "${I1401_DEFINES}" "${I1401_INCLUDES}")
