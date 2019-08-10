## Manchester University SSEM (Small Scale Experimental Machine):

set(SSEMD "${CMAKE_SOURCE_DIR}/SSEM")

set(SSEM_SOURCES ssem_cpu.c ssem_sys.c)
set(SSEM_DEFINES "")
set(SSEM_INCLUDES "${SSEMD}")
add_simulator(ssem "${SSEM_SOURCES}" "${SSEM_DEFINES}" "${SSEM_INCLUDES}")
