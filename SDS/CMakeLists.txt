## SDS simulator:

set(SDSD "${CMAKE_SOURCE_DIR}/SDS")

set(SDS_SOURCES
    sds_cpu.c
    sds_drm.c
    sds_dsk.c
    sds_io.c
    sds_lp.c
    sds_mt.c
    sds_mux.c
    sds_rad.c
    sds_stddev.c
    sds_sys.c)

set(SDS_DEFINES "")
set(SDS_INCLUDES "${SDSD}")
add_simulator(sds "${SDS_SOURCES}" "${SDS_DEFINES}" "${SDS_INCLUDES}")
