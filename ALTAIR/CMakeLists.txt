## The venerable Altair

set(ALTAIR_SOURCES
    altair_sio.c
    altair_cpu.c
    altair_dsk.c
    altair_sys.c)

set(ALTAIR_DEFINES "")
set(ALTAIR_INCLUDES "${ALTAIRD}")
add_simulator(altair "${ALTAIR_SOURCES}" "${ALTAIR_DEFINES}" "${ALTAIR_INCLUDES}")
