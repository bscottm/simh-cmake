## Put everything together into one nice function.

set(SIMH_BINDIR "${CMAKE_SOURCE_DIR}/BIN")
if (MSVC)
  set(SIMH_BINDIR "${SIMH_BINDIR}/Win32/$<CONFIG>")
endif ()

## Threading flags:
set(SIMH_THREADS_CFLAGS "")
set(SIMH_THREADS_DEFINES "")
set(SIMH_THREADS_INCLUDES "")
set(SIMH_THREADS_LIBS "")

if (WIN32)
    # Have pthreads... go with async I/O
    if (PTW_FOUND OR MINGW)
      set(SIMH_THREADS_DEFINES "${SIMH_THREADS_DEFINES}" USE_READER_THREAD)
      # Remember to remove SIM_ASYNCH_IO if the TODO option is False.
      set(SIMH_THREADS_DEFINES "${SIMH_THREADS_DEFINES}" SIM_ASYNCH_IO)

      if (PTW_FOUND)
          set(SIMH_THREADS_DEFINES "${SIMH_THREADS_DEFINES}" PTW32_STATIC_LIB _POSIX_C_SOURCE)
          set(SIMH_THREADS_INCLUDES "${SIMH_THREADS_INCLUDES}" "${PTW_INCLUDE_DIRS}")
	  set(vclib_flavor "VC3")
	  if ("VC3d" IN_LIST PTW_LIBRARY_FLAVORS)
	    set(vclib_flavor "VC3d")
	  endif()
	  if (EXISTS "${PTW_LIBRARY_PATH}/libpthread${vclib_flavor}.lib")
	    set(SIMH_THREADS_LIBS "${SIMH_THREADS_LIBS}" "libpthread${vclib_flavor}")
	  elseif (EXISTS "${PTW_LIBRARY_PATH}/pthread${vclib_flavor}.lib")
	    set(SIMH_THREADS_LIBS "${SIMH_THREADS_LIBS}" "pthread${vclib_flavor}")
	  else ()
	    message(FATAL_ERROR "Did not find libpthread${vclib_flavor}.lib or pthread${vclib_flavor}.lib library.")
	  endif ()
      elseif (MINGW)
          # Use MinGW's threads instead
          set(SIMH_THREADS_CFLAGS "${SIMH_THREADS_CFLAGS}" "-pthread")
          set(SIMH_THREADS_LIBS "${SIMH_THREADS_LIBS}" pthread)
      endif ()
  endif ()
endif ()

##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
## target_network_config: Configure target's compile and link for networking, if
## WITH_NETWORK is enabled.
##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

function(target_network_config _targ)
  if (WITH_NETWORK)
    if (WITH_PCAP AND PCAP_FOUND)
      target_compile_definitions("${_targ}" PUBLIC
        USE_SHARED
        HAVE_PCAP_NETWORK)

      target_include_directories("${_targ}" PUBLIC "${PCAP_INCLUDE_DIRS}")
      target_link_libraries("${_targ}" "${PCAP_LIBRARIES}")
    endif ()

    target_compile_definitions("${_targ}" PUBLIC
      USE_NETWORK
      HAVE_SLIRP_NETWORK
	  USE_SIMH_SLIRP_DEBUG)

    target_include_directories("${_targ}" PUBLIC
      "${CMAKE_SOURCE_DIR}/slirp"
      "${CMAKE_SOURCE_DIR}/slirp_glue"
      "${CMAKE_SOURCE_DIR}/slirp_glue/qemu")

    if (WIN32)
      target_include_directories("${_targ}" PUBLIC "${CMAKE_SOURCE_DIR}/slirp_glue/qemu/win32/include")
    endif ()

    target_link_libraries("${_targ}" slirp Iphlpapi)
  endif ()
endfunction ()

##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
## target_video_config: Configure for SDL and png...
##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

function(target_video_config _targ)
  if (WITH_VIDEO)
    target_compile_definitions("${_targ}" PUBLIC USE_SIM_VIDEO)

    if (SDL2_FOUND AND SDL2_TTF_FOUND)
      target_compile_definitions("${_targ}" PUBLIC HAVE_LIBSDL)
      target_include_directories("${_targ}" PUBLIC "${SDL2_INCLUDE_DIR}" "${SDL2_TTF_INCLUDE_DIRS}")
      target_link_libraries("${_targ}" "${SDL2_TTF_LIBRARIES}")
      if (SDL2_STATIC_LIBRARY)
	target_link_libraries("${_targ}" "${SDL2_STATIC_LIBRARY}")
	target_link_libraries("${_targ}" "imm32" "version")
      else ()
	target_link_libraries("${_targ}" "${SDL2_LIBRARY}")
      endif ()
    endif ()

    if (PNG_FOUND)
      target_compile_definitions("${_targ}" PUBLIC ${PNG_DEFINITIONS})
      target_include_directories("${_targ}" PUBLIC "${PNG_INCLUDE_DIRS}")
      target_link_libraries("${_targ}" "${PNG_LIBRARIES}")
    endif ()
  endif ()
endfunction ()

##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
## target_thread_config: Configure target's compile and linking for threads and
## async I/O.
##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

function(target_thread_config _targ)
  target_compile_options("${_targ}" PUBLIC "${SIMH_THREADS_CFLAGS}")
  target_compile_definitions("${_targ}" PUBLIC "${SIMH_THREADS_DEFINES}")
  target_include_directories("${_targ}" PUBLIC "${SIMH_THREADS_INCLUDES}")
  target_link_libraries("${_targ}" "${SIMH_THREADS_LIBS}")
  if (PTW_FOUND)
    target_link_directories("${_targ}" PUBLIC "${PTW_LIBRARY_PATH}")
  endif ()
endfunction ()

##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
## add_simulator: Does all of the hard work to set up a new simulation target's
## compile and link flags.
##~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

function(add_simulator _targ _sources _defines _includes)
  add_executable("${_targ}" "${_sources}")

  # This is a quick cheat to make sure that 
  set(_normalized_includes)
  foreach (inc IN LISTS _includes)
    if (NOT IS_ABSOLUTE "${inc}")
      get_filename_component(inc "${CMAKE_SOURCE_DIR}/${inc}" ABSOLUTE)
    endif ()
    list(APPEND _normalized_includes "${inc}")
  endforeach ()

  target_compile_definitions("${_targ}" PUBLIC "${_defines}" "${SIMH_THREADS_DEFINES}")
  target_include_directories("${_targ}" PUBLIC "${_normalized_includes}" "${SIMH_THREADS_INCLUDES}")
  target_link_libraries("${_targ}" simhcore)

  if (${PCRE_FOUND})
    target_compile_definitions("${_targ}" PUBLIC HAVE_PCREPOSIX_H PCRE_STATIC)
    target_include_directories("${_targ}" PUBLIC "${PCRE_INCLUDE_DIRS}")
    target_link_libraries("${_targ}" "${PCREPOSIX_LIBRARIES}" "${PCRE_LIBRARIES}")
  endif (${PCRE_FOUND})

  target_video_config("${_targ}")
  target_network_config("${_targ}")

  if (ZLIB_FOUND)
    # Add zlib, just in case. PCRE depends on it, and PNG might also (although, PNG
    # probably adds it to the link libraries anyway, but it doesn't hurt to add it
    # twice.
    target_link_libraries("${_targ}" "${ZLIB_LIBRARIES}")
  endif (ZLIB_FOUND)

  if (WIN32)
    if (NOT MSVC)
      # Need the math library...
      target_link_libraries("${_targ}" m)
    endif ()
    if (MINGW)
      target_compile_options("${_targ}" PUBLIC "-fms-extensions" "-mwindows")
    endif ()

    target_link_libraries("${_targ}" wsock32 winmm)

    if ("${MSVC_VERSION}" GREATER_EQUAL 1920)
      # MSVCRT conflicts with the new ucrt C runtime:
      # target_link_options("${_targ}" PUBLIC "/NODEFAULTLIB:MSVCRT")
      # target_link_libraries("${_targ}" ucrt)
    endif ()
  endif ()

  # And, lastly, add the thread libraries...
  target_thread_config("${_targ}")

  # Remember to add the install rule, which defaults to ${CMAKE_SOURCE_DIR}/BIN.
  # Installs the executables.
  install(TARGETS "${_targ}" RUNTIME)
endfunction ()

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

add_library(simhcore STATIC "${SIM_SOURCES}")
target_network_config(simhcore)
target_thread_config(simhcore)
target_video_config(simhcore)

target_compile_definitions(simhcore PRIVATE
  # Make sure that the conditionally compiled code is really compiled in
  # the simulation core library...
  #
  # (Note: This is just an interoperability issue with the makefile, which
  # insists on compiling the simulator core from scratch with each simulator.)
  USE_SIM_IMD
  USE_SIM_CARD
  # And, when we need to know that we're building the simhcore library...
  BUILDING_SIMHCORE)
