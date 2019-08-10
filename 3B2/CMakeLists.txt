## AT&T 3b2 simulator:

set(ATT3B2D "${CMAKE_SOURCE_DIR}/3B2")

set(ATT3B2_SOURCES
	3b2_cpu.c 
    3b2_mmu.c
	3b2_iu.c 
    3b2_if.c
	3b2_id.c 
    3b2_dmac.c
	3b2_sys.c 
    3b2_io.c
	3b2_ports.c
    3b2_ctc.c
	3b2_ni.c 
    3b2_mau.c
	3b2_sysdev.c)

set(ATT3B2_DEFINES USE_INT64 USE_ADDR64)
set(ATT3B2_INCLUDES "${ATT3B2D}")
add_simulator(3b2 "${ATT3B2_SOURCES}" "${ATT3B2_DEFINES}" "${ATT3B2_INCLUDES}")
