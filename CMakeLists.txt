if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message("")
  message("*** Do NOT build or generate CMake artifacts in the SIMH source directory! ***")
  message("")
  message("Create a subdirectory and build in that subdirectory, e.g.:")
  message("")
  message("  $ mkdir cmake-build")
  message("  $ cd cmake-build")
  message("  $ cmake -G \"your generator here\" ..")
  message("")
  message(FATAL_ERROR "Preventing in-tree source build.")
endif ()

cmake_minimum_required(VERSION 3.14)

set(SIMH_VERSION "4.0.0")
project(simh VERSION ${SIMH_VERSION} LANGUAGES C)

option(NETWORK_USEFUL "Enable/disable simulator networking support." TRUE)
option(VIDEO_USEFUL   "Enable/disable simulator display and graphics support" TRUE)

# SIMH_WINDOWS_BUILD: This is the top-level directory storing the Windows runtime support
# artifacts.
get_filename_component(SIMH_WINDOWS_BUILD "${CMAKE_SOURCE_DIR}/../windows-build/build-stage" ABSOLUTE)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake")

if (WIN32)
  # Places where CMake should look for the various package configuration fragments:
  set(CMAKE_MODULE_PATH
    "${CMAKE_MODULE_PATH}"
    "${SIMH_WINDOWS_BUILD}/cmake"
    "${SIMH_WINDOWS_BUILD}/lib/cmake"
    "${SIMH_WINDOWS_BUILD}/lib/libpng")

  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

include (CheckIncludeFile)
include (CheckFunctionExists)
include (CheckSymbolExists)
include (CheckTypeSize)

# Make sure we can include from the top level source...
include_directories("${CMAKE_SOURCE_DIR}")

# Add a rule to ensure that the BIN directory exists:
if (NOT WIN32)
  set(COPY_CMD "cp")

  add_custom_target("bin_directory" ALL
    COMMAND "$ENV{SHELL}" "-c" "\
[ ! -d \"${CMAKE_SOURCE_DIR}/BIN\" ] && { \
  rm -rf \"${CMAKE_SOURCE_DIR}/BIN\"; \
  mkdir \"${CMAKE_SOURCE_DIR}/BIN\"; \
}")
else (NOT WIN32)
  set(COPY_CMD "copy")

  add_custom_target("bin_directory" ALL
    COMMAND "powershell" "-NoProfile" "${CMAKE_SOURCE_DIR}\\cmake\\BINdir.ps1" "${CMAKE_SOURCE_DIR}")
endif (NOT WIN32)

# A bunch of Windows customizations
if (WIN32)
  set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}" "${SIMH_WINDOWS_BUILD}/lib")
  set(CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH}" "${SIMH_WINDOWS_BUILD}/include")
  # Assistance variables for the "Find<Package>" packages we use:
  set(SDL2_PATH "${SIMH_WINDOWS_BUILD}")
  set(SDL2_TTF_PATH "${SIMH_WINDOWS_BUILD}")
  set(PCRE_PATH "${SIMH_WINDOWS_BUILD}")
  set(PTW_PATH "${SIMH_WINDOWS_BUILD}")
  set(PCAP_PATH "${SIMH_WINDOWS_BUILD}")

  include_directories("${SIMH_WINDOWS_BUILD}/include")
  link_directories("${SIMH_WINDOWS_BUILD}/lib")
  
  if ("${MSVC_VERSION}" GREATER_EQUAL 1920)
    add_compile_definitions(USE_ISO_C99_NAMES)
  endif ()
 
  # Pthreads4w: pthreads for windows
  include (FindPthreads4w)
endif (WIN32)

# Perl-Compatible Regular Expressions (PCRE). PCRE depends on zlib...
include (FindZLIB)

if (ZLIB_FOUND)
  include (FindPCRE)
else (ZLIB_FOUND)
  set(PCRE_FOUND FALSE)
endif (ZLIB_FOUND)

# Look for SDL and SDL_ttf: They install CMake scripts that set compiler and linker
# flags. Assume that the packages are available. (Which depends on Freetype.)

include (FindFreetype)
if (FREETYPE_FOUND)
  find_package(SDL2)
  find_package(SDL2_ttf)

  if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  # ifeq (Darwin,$(OSTYPE))
  #   VIDEO_CCDEFS += -DSDL_MAIN_AVAILABLE
  # endif
  endif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
else ()
  set(SDL2_FOUND FALSE)
  set(SDL2_TTF_FOUND FALSE)
endif ()

include (FindPNG)
include (FindPCAP)

message(STATUS "")
if (WIN32)
  message(STATUS "Pthreads4w ................. ${PTW_FOUND}")
endif ()
message(STATUS "zlib ....................... ${ZLIB_FOUND}")
message(STATUS "Perl-Compatible RegExps..... ${PCRE_FOUND}")
message(STATUS "SDL2 ....................... ${SDL2_FOUND}")
message(STATUS "SDL2_ttf ................... ${SDL2_TTF_FOUND}")
message(STATUS "Portable Network Graphics .. ${PNG_FOUND}")
message(STATUS "Packet Capture (PCAP) ...... ${PCAP_FOUND}")
message(STATUS "")

## Simulator sources:
set(SIM_SOURCES
  ${CMAKE_SOURCE_DIR}/scp.c
  ${CMAKE_SOURCE_DIR}/sim_console.c
  ${CMAKE_SOURCE_DIR}/sim_fio.c
  ${CMAKE_SOURCE_DIR}/sim_timer.c
  ${CMAKE_SOURCE_DIR}/sim_sock.c
  ${CMAKE_SOURCE_DIR}/sim_tmxr.c
  ${CMAKE_SOURCE_DIR}/sim_ether.c
  ${CMAKE_SOURCE_DIR}/sim_tape.c
  ${CMAKE_SOURCE_DIR}/sim_disk.c
  ${CMAKE_SOURCE_DIR}/sim_serial.c
  ${CMAKE_SOURCE_DIR}/sim_video.c
  ${CMAKE_SOURCE_DIR}/sim_imd.c
  ${CMAKE_SOURCE_DIR}/sim_card.c)

## Helpers:
## Put everything together into one nice function.

set(DISPLAYL "display/display.c display/sim_ws.c")
set(DISPLAYVT "display/vt11.c")
set(DISPLAY340 "display/type340.c")
set(DISPLAYNG "display/ng.c")

## The actual simulators:

include (add_simulator)

add_subdirectory(slirp)
add_subdirectory(VAX)
