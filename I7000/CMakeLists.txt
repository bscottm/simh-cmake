## IBM I700 simulators:

set(I7000D "${CMAKE_SOURCE_DIR}/I7000")
set(I7000_INCLUDES "$(I7000D)")

set(I7090_SOURCES
    i7090_cpu.c
    i7090_sys.c
    i7090_chan.c
	i7090_cdr.c
    i7090_cdp.c
    i7090_lpr.c
	i7000_chan.c
    i7000_mt.c
    i7090_drum.c
	i7090_hdrum.c
    i7000_chron.c
    i7000_dsk.c
	i7000_com.c
    i7000_ht.c)

set(I7090_DEFINES USE_INT64 I7090 USE_SIM_CARD)
add_simulator(i7090 "${I7090_SOURCES}" "${I7090_DEFINES}" "${I7000_INCLUDES}")

set(I7080_SOURCES
	i7080_cpu.c 
	i7080_sys.c 
	i7080_chan.c
	i7080_drum.c 
	i7000_cdp.c 
	i7000_cdr.c
	i7000_con.c 
	i7000_chan.c 
	i7000_lpr.c
	i7000_mt.c 
	i7000_chron.c 
	i7000_dsk.c
	i7000_com.c 
	i7000_ht.c)

set(I7080_DEFINES USE_INT64 I7080 USE_SIM_CARD)
add_simulator(i7080 "${I7080_SOURCES}" "${I7080_DEFINES}" "${I7000_INCLUDES}")

set(I7070_SOURCES
	i7070_cpu.c
	i7070_sys.c 
	i7070_chan.c
	i7000_cdp.c 
	i7000_cdr.c 
	i7000_con.c
	i7000_chan.c 
	i7000_lpr.c 
	i7000_mt.c
	i7000_chron.c 
	i7000_dsk.c 
	i7000_com.c
	i7000_ht.c)

set(I7070_DEFINES USE_INT64 I7070 USE_SIM_CARD)
add_simulator(i7070 "${I7070_SOURCES}" "${I7070_DEFINES}" "${I7000_INCLUDES}")

set(I7010_SOURCES
	i7010_cpu.c 
	i7010_sys.c 
	i7010_chan.c
	i7000_cdp.c 
	i7000_cdr.c 
	i7000_con.c
	i7000_chan.c 
	i7000_lpr.c 
	i7000_mt.c
	i7000_chron.c 
	i7000_dsk.c 
	i7000_com.c
	i7000_ht.c)

set(I7010_DEFINES USE_INT64 I7010 USE_SIM_CARD)
add_simulator(i7010 "${I7010_SOURCES}" "${I7010_DEFINES}" "${I7000_INCLUDES}")


set(I704_SOURCES
	i7090_cpu.c 
	i7090_sys.c 
	i7090_chan.c
	i7090_cdr.c 
	i7090_cdp.c 
	i7090_lpr.c
	i7000_mt.c 
	i7090_drum.c 
	i7000_chan.c)

set(I704_DEFINES USE_INT64 I704 USE_SIM_CARD)
add_simulator(i704 "${I704_SOURCES}" "${I704_DEFINES}" "${I7000_INCLUDES}")

set(I701_SOURCES
	i701_cpu.c 
	i701_sys.c 
	i701_chan.c
	i7090_cdr.c 
	i7090_cdp.c 
	i7090_lpr.c
	i7000_mt.c 
	i7090_drum.c 
	i7000_chan.c)

set(I701_DEFINES USE_INT64 I701 USE_SIM_CARD)
add_simulator(i701 "${I701_SOURCES}" "${I701_DEFINES}" "${I7000_INCLUDES}")
