## SAGE simulator:
## Experimental. Has compilation issues.

add_simulator(sage
    SOURCES
	sage_cpu.c
	sage_sys.c
	sage_stddev.c
	sage_cons.c
	sage_fd.c
	sage_lp.c
	m68k_cpu.c
	m68k_mem.c
	m68k_scp.c
	m68k_parse.tab.c
	m68k_sys.c
	i8251.c
	i8253.c
	i8255.c
	i8259.c
	i8272.c 
    INCLUDES
	SAGE
    ## This is totally unnecessary.
    DEFINES
	HAVE_INT64
	USE_SIM_IMD
    INT64
)

