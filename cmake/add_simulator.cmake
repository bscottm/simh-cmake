## Put everything together into one nice function.

include (CTest)

set(SIMH_BINDIR "${CMAKE_SOURCE_DIR}/BIN")
if (MSVC)
  set(SIMH_BINDIR "${SIMH_BINDIR}/Win32/$<CONFIG>")
endif ()

## INTERFACE libraries: Interface libraries let us refer to the libraries,
## set includes and defines, flags in a consistent way.
##
## Here's the way it works:
##
## 1. Add the library as INTERFACE. The name isn't particularly important,
##    but it should be meaningful, like "thread_lib".
## 2. If specific features are enabled, add target attributes and properties,
##    such as defines, include directories to the interface library.
## 3. "Link" with the interface library. All of the flags, defines, includes
##    get picked up in the dependent.
##

if (PCRE_FOUND)
    add_library(pcreposix INTERFACE)
    add_library(pcre INTERFACE)
    target_compile_definitions(pcreposix INTERFACE HAVE_PCREPOSIX_H PCRE_STATIC)
    target_include_directories(pcreposix INTERFACE "${PCRE_INCLUDE_DIRS}")
    target_link_libraries(pcreposix INTERFACE "${PCREPOSIX_LIBRARIES}")
    target_link_libraries(pcre INTERFACE "${PCRE_LIBRARIES}")
endif (PCRE_FOUND)

## Threading support:
add_library(thread_lib INTERFACE)

if (WIN32)
    # Have pthreads... go with async I/O (TODO: Disable async I/O if option present.)
    if (MINGW)
        # Use MinGW's threads instead
	target_compile_definitions(thread_lib INTERFACE USE_READER_THREAD SIM_ASYNCH_IO)
        target_compile_options(thread_lib INTERFACE "-pthread")
	target_link_libraries(thread_lib INTERFACE pthread)
    elseif (PTW_FOUND)
        target_compile_definitions(thread_lib INTERFACE USE_READER_THREAD SIM_ASYNCH_IO PTW32_STATIC_LIB)
        target_include_directories(thread_lib INTERFACE ${PTW_INCLUDE_DIRS})
        target_link_libraries(thread_lib INTERFACE pthreadVC3)
        target_link_directories(thread_lib INTERFACE ${PTW_LIBRARY_PATH})
    endif ()
endif ()

# pcap networking (slirp is always included):
add_library(pcap INTERFACE)

if (WITH_NETWORK)
    if (WITH_PCAP AND PCAP_FOUND)
        target_compile_definitions(pcap INTERFACE USE_SHARED HAVE_PCAP_NETWORK)
        target_include_directories(pcap INTERFACE "${PCAP_INCLUDE_DIRS}")
        target_link_libraries(pcap INTERFACE "${PCAP_LIBRARIES}")
    endif ()
endif ()

## Simple Direct Media Layer (v2) support:
add_library(simh_video INTERFACE)

if (WITH_VIDEO)
    if (SDL2_FOUND AND SDL2_TTF_FOUND)
        target_compile_definitions(simh_video INTERFACE USE_SIM_VIDEO HAVE_LIBSDL)
        target_include_directories(simh_video INTERFACE "${SDL2_INCLUDE_DIR}" "${SDL2_TTF_INCLUDE_DIRS}")
        target_link_libraries(simh_video INTERFACE "${SDL2_TTF_LIBRARIES}")
        if (SDL2_STATIC_LIBRARY)
            target_link_libraries(simh_video INTERFACE "${SDL2_STATIC_LIBRARY}")
            if (WIN32)
                target_link_libraries(simh_video INTERFACE "imm32" "version")
            endif (WIN32)
        else ()
            target_link_libraries(simh_video INTERFACE "${SDL2_LIBRARY}")
        endif ()
    endif ()

    if (PNG_FOUND)
        target_compile_definitions(simh_video INTERFACE ${PNG_DEFINITIONS})
        target_include_directories(simh_video INTERFACE "${PNG_INCLUDE_DIRS}")
        target_link_libraries(simh_video INTERFACE "${PNG_LIBRARIES}")
    endif ()
endif ()

## Simulator sources and library:
set(SIM_SOURCES
    ${CMAKE_SOURCE_DIR}/scp.c
    ${CMAKE_SOURCE_DIR}/sim_card.c
    ${CMAKE_SOURCE_DIR}/sim_console.c
    ${CMAKE_SOURCE_DIR}/sim_disk.c
    ${CMAKE_SOURCE_DIR}/sim_ether.c
    ${CMAKE_SOURCE_DIR}/sim_fio.c
    ${CMAKE_SOURCE_DIR}/sim_frontpanel.c
    ${CMAKE_SOURCE_DIR}/sim_imd.c
    ${CMAKE_SOURCE_DIR}/sim_scsi.c
    ${CMAKE_SOURCE_DIR}/sim_serial.c
    ${CMAKE_SOURCE_DIR}/sim_sock.c
    ${CMAKE_SOURCE_DIR}/sim_tape.c
    ${CMAKE_SOURCE_DIR}/sim_timer.c
    ${CMAKE_SOURCE_DIR}/sim_tmxr.c
    ${CMAKE_SOURCE_DIR}/sim_video.c)

function(build_simcore _targ)
    cmake_parse_arguments(SIMH "" "" "DEFINES" ${ARGN})

    add_library(${_targ} STATIC ${SIM_SOURCES})

    # Components that need to be turned on while building the library, but
    # don't export out to the dependencies (hence PRIVATE.)
    target_compile_definitions(${_targ} PRIVATE USE_SIM_CARD USE_SIM_IMD)

    if (DEFINED SIMH_DEFINES)
        target_compile_definitions(${_targ} PUBLIC ${SIMH_DEFINES})
    endif (DEFINED SIMH_DEFINES)

    target_link_libraries(${_targ} PUBLIC pcreposix pcre thread_lib simh_video slirp pcap)

    if (WITH_NETWORK)
        target_compile_definitions(${_targ} PUBLIC USE_NETWORK)
    endif (WITH_NETWORK)

    if (WIN32)
        if (NOT MSVC)
          # Need the math library...
          target_link_libraries(${_targ} PUBLIC m)
        endif ()

        if (MINGW)
          target_compile_options(${_targ} PUBLIC "-fms-extensions" "-mwindows")
        endif ()

        if (WITH_NETWORK)
            target_link_libraries(${_targ} PUBLIC wsock32 winmm)
        endif (WITH_NETWORK)
    endif ()
endfunction(build_simcore _targ)


## INT64: Use the simhi64 library (USE_INT64)
## FULL64: Use the simhz64 library (USE_INT64, USE_ADDR64)

function (add_simulator _targ) ## _sources _defines _includes)
    cmake_parse_arguments(SIMH "INT64;FULL64;BUILDROMS" "TEST" "DEFINES;INCLUDES;SOURCES" ${ARGN})

    if (NOT DEFINED SIMH_SOURCES)
        message(FATAL_ERROR "${_targ}: No source files?")
    endif (NOT DEFINED SIMH_SOURCES)

    add_executable("${_targ}" "${SIMH_SOURCES}")

    if (DEFINED SIMH_DEFINES)
        target_compile_definitions("${_targ}" PRIVATE "${SIMH_DEFINES}")
    endif (DEFINED SIMH_DEFINES)

    # This is a quick cheat to make sure that all of the include paths are
    # absolute paths.
    if (DEFINED SIMH_INCLUDES)
        set(_normalized_includes)
        foreach (inc IN LISTS SIMH_INCLUDES)
            if (NOT IS_ABSOLUTE "${inc}")
                get_filename_component(inc "${CMAKE_SOURCE_DIR}/${inc}" ABSOLUTE)
            endif ()
            list(APPEND _normalized_includes "${inc}")
        endforeach (inc IN LISTS ${SIMH_INCLUDES})

        target_include_directories("${_targ}" PRIVATE "${_normalized_includes}")
    endif (DEFINED SIMH_INCLUDES)

    if (SIMH_INT64)
        target_link_libraries("${_targ}" PRIVATE simhi64)
    elseif (SIMH_FULL64)
        target_link_libraries("${_targ}" PRIVATE simhz64)
    else ()
        target_link_libraries("${_targ}" PRIVATE simhcore)
    endif ()

    # Remember to add the install rule, which defaults to ${CMAKE_SOURCE_DIR}/BIN.
    # Installs the executables.
    install(TARGETS "${_targ}" RUNTIME)

    set(test_fname "${CMAKE_CURRENT_SOURCE_DIR}/tests/${SIMH_TEST}_test.ini")
    if (DEFINED SIMH_TEST AND EXISTS "${test_fname}")
	add_test(NAME "test-${_targ}" COMMAND "${_targ}" "${test_fname}")
    endif (DEFINED SIMH_TEST AND EXISTS "${test_fname}")

    if (NOT DONT_USE_ROMS AND SIMH_BUILDROMS)
	add_dependencies(${_targ} BuildROMs)
    endif (NOT DONT_USE_ROMS AND SIMH_BUILDROMS)
endfunction ()

##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
## Now build things!
##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

build_simcore(simhcore)
build_simcore(simhi64 DEFINES USE_INT64)
build_simcore(simhz64 DEFINES USE_INT64 USE_ADDR64)

if (NOT DONT_USE_ROMS)
    add_executable(BuildROMs sim_BuildROMs.c)
    add_custom_command(
	OUTPUT
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka655x_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka620_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka630_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka610_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka410_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka411_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka412_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka41a_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka41d_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka42a_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka42b_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka43a_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka46a_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka47a_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka48a_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_is1000_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka410_xs_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka420_rdrz_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka420_rzrz_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka4xx_4pln_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka4xx_8pln_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka4xx_dz_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka4xx_spx_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka750_bin_new.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_ka750_bin_old.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_vcb02_bin.h
	    ${CMAKE_SOURCE_DIR}/VAX/vax_vmb_exe.h
	    ${CMAKE_SOURCE_DIR}/PDP11/pdp11_vt_lunar_rom.h
	    ${CMAKE_SOURCE_DIR}/PDP11/pdp11_dazzle_dart_rom.h
	    ${CMAKE_SOURCE_DIR}/PDP11/pdp11_11logo_rom.h
	    ${CMAKE_SOURCE_DIR}/swtp6800/swtp6800/swtp_swtbug_bin.h
	    ${CMAKE_SOURCE_DIR}/3B2/rom_400_bin.h
	MAIN_DEPENDENCY BuildROMs
	COMMAND BuildROMS
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif ()
