## GRI:

set(GRID "${CMAKE_SOURCE_DIR}/GRI")

set(GRI_SOURCES gri_cpu.c gri_stddev.c gri_sys.c)
set(GRI_DEFINES "")
set(GRI_INCLUDES "${GRID}")
add_simulator(gri "${GRI_SOURCES}" "${GRI_DEFINES}" "${GRI_INCLUDES}")
