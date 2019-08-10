## SWTP 6800 simulators:

set(SWTP6800D "${CMAKE_SOURCE_DIR}/swtp6800/swtp6800")
set(SWTP6800C "${CMAKE_SOURCE_DIR}/swtp6800/common")

set(SWTP6800MP_A_SOURCES
    common/mp-a.c
    common/m6800.c
    common/m6810.c
    common/bootrom.c
    common/dc-4.c
    common/mp-s.c
    swtp6800/mp-a_sys.c
    common/mp-b2.c
    common/mp-8m.c)

set(SWTP6800MP_A2_SOURCES
    common/mp-a2.c
    common/m6800.c
    common/m6810.c
    common/bootrom.c
    common/dc-4.c
    common/mp-s.c
    swtp6800/mp-a2_sys.c
    common/mp-b2.c
    common/mp-8m.c
    common/i2716.c)

set(SWTP6800_DEFINES "")
set(SWTP6800_INCLUDES "${SWTP6800D}")

add_simulator(swtp6800mp-a "${SWTP6800MP_A_SOURCES}" "${SWTP6800_DEFINES}" "${SWTP6800_INCLUDES}")
add_simulator(swtp6800mp-a2 "${SWTP6800MP_A2_SOURCES}" "${SWTP6800_DEFINES}" "${SWTP6800_INCLUDES}")
