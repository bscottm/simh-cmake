## The Intel simulator family:

set(ISYS8010D "${CMAKE_SOURCE_DIR}/Intel-Systems/isys8010")
set(ISYS8010_SOURCES
    common/i8080.c
    isys8010/isys8010_sys.c
    common/i8251.c
    common/i8255.c
    common/ieprom.c
    common/iram8.c
    common/multibus.c
    isys8010/isbc8010.c
    common/isbc064.c
    common/isbc202.c
    common/isbc201.c
    common/zx200a.c)

set(ISYS8010_DEFINES "")
set(ISYS8010_INCLUDES "${ISYS8010D}")
add_simulator(isys8010 "${ISYS8010_SOURCES}" "${ISYS8010_DEFINES}" "${ISYS8010_INCLUDES}")


set(ISYS8020D "${CMAKE_SOURCE_DIR}/Intel-Systems/isys8020")
set(ISYS8020_SOURCES
    common/i8080.c
    isys8020/isys8020_sys.c
    common/i8251.c
    common/i8255.c
    common/ieprom.c
    common/iram8.c
    common/multibus.c
    isys8020/isbc8020.c
    common/isbc064.c
    common/i8259.c
    common/isbc202.c
    common/isbc201.c
    common/zx200a.c)

set(ISYS8020_DEFINES "")
set(ISYS8020_INCLUDES "${ISYS8020D}")
add_simulator(isys8020 "${ISYS8020_SOURCES}" "${ISYS8020_DEFINES}" "${ISYS8020_INCLUDES}")


set(ISYS8024D "${CMAKE_SOURCE_DIR}/Intel-Systems/isys8024")

set(ISYS8024_SOURCES
    common/i8080.c
    isys8024/isys8024_sys.c
    common/i8251.c
    common/i8253.c
    common/i8255.c
    common/i8259.c
    common/ieprom.c
    common/iram8.c
    common/multibus.c
    isys8024/isbc8024.c
    common/isbc064.c
    common/isbc208.c
    common/isbc202.c
    common/isbc201.c
    common/zx200a.c)

set(ISYS8024_DEFINES "")
set(ISYS8024_INCLUDES "${ISYS8024D}")
add_simulator(isys8024 "${ISYS8024_SOURCES}" "${ISYS8024_DEFINES}" "${ISYS8024_INCLUDES}")


set(ISYS8030D "${CMAKE_SOURCE_DIR}/Intel-Systems/isys8030")
set(ISYS8030_SOURCES
    common/i8080.c
    isys8030/isys8030_sys.c
    common/i8251.c
    common/i8255.c
    common/i8259.c
    common/i8253.c
    common/ieprom.c
    common/iram8.c
    common/multibus.c
    isys8030/isbc8030.c
    common/isbc202.c
    common/isbc201.c
    common/isbc064.c
    common/zx200a.c)

set(ISYS8030_DEFINES "")
set(ISYS8030_INCLUDES "${ISYS8030D}")
add_simulator(isys8030 "${ISYS8030_SOURCES}" "${ISYS8030_DEFINES}" "${ISYS8030_INCLUDES}")


set(IMDS_225D "${CMAKE_SOURCE_DIR}/Intel-Systems/imds-225")
set(IMDS_225_SOURCES
    common/i8080.c
    imds-225/imds-225_sys.c
    common/i8251.c
    common/i8255.c
    common/i8259.c
    common/i8253.c
    common/ieprom.c
    common/iram8.c
    common/ipcmultibus.c
    imds-225/ipc.c
    common/ipc-cont.c
    common/ioc-cont.c
    common/isbc202.c
    common/isbc201.c
    common/zx200a.c)

set(IMDS_225_DEFINES "")
set(IMDS_225_INCLUDES "${IMDS_225D}")
add_simulator(imds-225 "${IMDS_225_SOURCES}" "${IMDS_225_DEFINES}" "${IMDS_225_INCLUDES}")


set(IBMPCD "${CMAKE_SOURCE_DIR}/Intel-Systems/ibmpc")
set(IBMPC_SOURCES
    common/i8255.c
    ibmpc/ibmpc.c
    common/i8088.c
    ibmpc/ibmpc_sys.c
    common/i8253.c
    common/i8259.c
    common/pceprom.c
    common/pcram8.c
    common/i8237.c
    common/pcbus.c)

set(IBMPC_DEFINES "")
set(IBMPC_INCLUDES "${IBMPCD}")


set(IBMPCXTD "${CMAKE_SOURCE_DIR}/Intel-Systems/ibmpcxt")
set(IBMPCXT_SOURCES
    common/i8088.c
    ibmpcxt/ibmpcxt_sys.c
    common/i8253.c
    common/i8259.c
    common/i8255.c
    ibmpcxt/ibmpcxt.c
    common/pceprom.c
    common/pcram8.c
    common/pcbus.c
    common/i8237.c)

set(IBMPCXT_DEFINES "")
set(IBMPCXT_INCLUDES "${IBMPCXTD}")


set(SCELBID "${CMAKE_SOURCE_DIR}/Intel-Systems/scelbi")
set(SCELBI_SOURCES common/i8008.c scelbi/scelbi_sys.c scelbi/scelbi_io.c)
set(SCELBI_DEFINES "")
set(SCELBI_INCLUDES "${SCELBID}")
add_simulator(scelbi "${SCELBI_SOURCES}" "${SCELBI_DEFINES}" "${SCELBI_INCLUDES}")
