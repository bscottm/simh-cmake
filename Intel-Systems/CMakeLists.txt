## The Intel simulator family:


add_simulator(isys8010
    SOURCES
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
	common/zx200a.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/isys8010
    BUILDROMS)


add_simulator(isys8020
    SOURCES
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
	common/zx200a.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/isys8020
    BUILDROMS)


add_simulator(isys8024
    SOURCES
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
	common/zx200a.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/isys8024
    BUILDROMS)


add_simulator(isys8030
    SOURCES
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
	common/zx200a.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/isys8030
    BUILDROMS)


add_simulator(imds-225
    SOURCES
        common/i8080.c
        imds-225/imds-225_sys.c
        common/i8251.c
        common/i8255.c
        common/i8259.c
        common/i8253.c
        common/ieprom.c
        common/iram8.c
        common/ipcmultibus.c
        common/ipc.c
        common/ipc-cont.c
        common/ioc-cont.c
        common/isbc202.c
        common/isbc201.c
        common/zx200a.c
        common/isbc464.c
        common/isbc206.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/imds-225
    BUILDROMS)


add_simulator(ibmpc
    SOURCES
	common/i8255.c
	ibmpc/ibmpc.c
	common/i8088.c
	ibmpc/ibmpc_sys.c
	common/i8253.c
	common/i8259.c
	common/pceprom.c
	common/pcram8.c
	common/i8237.c
	common/pcbus.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/ibmpc
    BUILDROMS)

add_simulator(ibmpcxt
    SOURCES
	common/i8088.c
	ibmpcxt/ibmpcxt_sys.c
	common/i8253.c
	common/i8259.c
	common/i8255.c
	ibmpcxt/ibmpcxt.c
	common/pceprom.c
	common/pcram8.c
	common/pcbus.c
	common/i8237.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/ibmpcxt
    BUILDROMS)

add_simulator(scelbi
    SOURCES
	common/i8008.c
	scelbi/scelbi_sys.c
	scelbi/scelbi_io.c
    INCLUDES
	${CMAKE_SOURCE_DIR}/Intel-Systems/scelbi)
