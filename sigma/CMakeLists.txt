## Xerox XDS Sigma 9 simulator

set(SIGMAD "${CMAKE_SOURCE_DIR}/sigma")

set(SIGMA_SOURCES
    sigma_cpu.c
    sigma_sys.c
    sigma_cis.c
	sigma_coc.c
    sigma_dk.c
    sigma_dp.c
	sigma_fp.c
    sigma_io.c
    sigma_lp.c
	sigma_map.c
    sigma_mt.c
    sigma_pt.c
    sigma_rad.c
    sigma_rtc.c
    sigma_tt.c)

set(SIGMA_DEFINES "")
set(SIGMA_INCLUDES "${SIGMAD}")
add_simulator(sigma "${SIGMA_SOURCES}" "${SIGMA_DEFINES}" "${SIGMA_INCLUDES}")