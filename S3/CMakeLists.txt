## S3 simulator:

set(S3D "${CMAKE_SOURCE_DIR}/S3")

set(S3_SOURCES
    s3_cd.c
    s3_cpu.c
    s3_disk.c
    s3_lp.c
    s3_pkb.c
    s3_sys.c)

set(S3_DEFINES "")
set(S3_INCLUDES "${S3D}")
add_simulator(s3 "${S3_SOURCES}" "${S3_DEFINES}" "${S3_INCLUDES}")
