## burroughs 5500 CPU simulator:

set(B5500D "${CMAKE_SOURCE_DIR}/B5500")

set(B5500_SOURCES
    b5500_cpu.c
    b5500_io.c
    b5500_sys.c
    b5500_dk.c
    b5500_mt.c
    b5500_urec.c
    b5500_dr.c
    b5500_dtc.c)

set(B5500_DEFINES USE_INT64 B5500)
set(B5500_INCLUDES "")
add_simulator(b5500 "${B5500_SOURCES}" "${B5500_DEFINES}" "${B5500_INCLUDES}")
