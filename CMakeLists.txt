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

## Note: pthreads4w requires 3.14 or better.
cmake_minimum_required(VERSION 3.10)

set(SIMH_VERSION "4.0.0")
project(simh VERSION "${SIMH_VERSION}" LANGUAGES C)

## Provide a default CMAKE_BUILD_TYPE if CMAKE_CONFIGURATION_TYPES is empty or not defined.
if (NOT CMAKE_CONFIGURATION_TYPES)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
        message(STATUS "CMAKE_BUILD_TYPE defaulted to ${CMAKE_BUILD_TYPE}")
    else (NOT CMAKE_BUILD_TYPE)
        message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
    endif (NOT CMAKE_BUILD_TYPE)
else ()
    message(STATUS "Available build configurations: ${CMAKE_CONFIGURATION_TYPES}")
endif ()

# SIMH_DEP_TOPDIR: This is the top-level directory where dependencies live:
set(SIMH_DEP_TOPDIR ${CMAKE_SOURCE_DIR}/cmake-dependencies/${CMAKE_C_COMPILER_ID}-${CMAKE_C_COMPILER_VERSION}
        CACHE STRING "Top-level directory for SIMH library dependencies")

# Places to look for CMake modules/includes
set(SIMH_INCLUDE_PATH_LIST ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_INCLUDE_PATH ${SIMH_INCLUDE_PATH_LIST})
list(APPEND CMAKE_MODULE_PATH ${SIMH_INCLUDE_PATH_LIST})

# Places where CMake should look for dependent package configuration fragments and artifacts:
set(SIMH_PREFIX_PATH_LIST)
list(APPEND SIMH_PREFIX_PATH_LIST ${SIMH_DEP_TOPDIR})
list(APPEND CMAKE_PREFIX_PATH ${SIMH_PREFIX_PATH_LIST})

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckCCompilerFlag)
include(ExternalProject)
include(build_dep_matrix)

## pkg-config is our fallback when find_package() can't find a package.
find_package(PkgConfig)

##-- Options --##
option(WITH_NETWORK
       "Enable (=1)/disable (=0) simulator networking support. (def: enabled)"
       TRUE)
option(WITH_PCAP
       "Enable (=1)/disable (=0) libpcap (packet capture) support. (def: enabled)"
       TRUE)
option(WITH_SLIRP
       "Enable (=1)/disable (=0) SLIRP network support. (def: disabled)"
       FALSE)
option(WITH_VIDEO
       "Enable (=1)/disable (=0) simulator display and graphics support (def: enabled)"
       TRUE)
option(WITH_ASYNC
       "Enable (=1)/disable (=0) simulator asynchronous I/O (def: enabled)"
       TRUE)
option(PANDA_LIGHTS
       "Enable (=1)/disable (=0) KA-10/KI-11 simulator's Panda display. (def: disabled)"
       FALSE)
option(DONT_USE_ROMS
       "Enable (=1)/disable (=0) building support ROMs. (def: disabled)"
       FALSE)
option(ENABLE_CPPCHECK
       "Enable (=1)/disable (=0) 'cppcheck' static code analysis. (def: disabled.)"
       FALSE)

# For 64-bit builds (and this is especially true for MSVC), set the library
# architecture.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # For the WinPcap and Npcap SDKs, the Lib subdirectory of the top-level
    # directory contains 32-bit libraries; the 64-bit libraries are in the
    # Lib/x64 directory.
    #
    # The only way to *FORCE* CMake to look in the Lib/x64 directory
    # without searching in the Lib directory first appears to be to set
    # CMAKE_LIBRARY_ARCHITECTURE to "x64".
    #
    if (MSVC OR MINGW)
        set(CMAKE_C_LIBRARY_ARCHITECTURE "x64")
        set(CMAKE_LIBRARY_ARCHITECTURE "x64")
    else (EXISTS /usr/lib/x86_64-linux-gnu)
        # Linux-ism
        set(CMAKE_C_LIBRARY_ARCHITECTURE "x86_64-linux-gnu")
        set(CMAKE_LIBRARY_ARCHITECTURE "x86_64-linux-gnu")
    endif ()
endif()

## Additional command line arguments for dependencies. Need this because Powershell will report
## an error if anything is sent to stderr and $ErrorDefaultAction is set to "Stop".
set(DEP_CMAKE_ARGS "-Wno-dev" "--no-warn-unused-cli")

## build-stage directory hierarchy for dependency installs:
if (NOT EXISTS ${SIMH_DEP_TOPDIR})
    message(STATUS "Creating dependency library directory hierarchy")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SIMH_DEP_TOPDIR} ${SIMH_DEP_TOPDIR}/include ${SIMH_DEP_TOPDIR}/lib 
                    ${SIMH_DEP_TOPDIR}/bin
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif ()

## Default install location is ${CMAKE_SOURCE_DIR}/BIN if not otherwise set
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/" CACHE PATH "${CMAKE_SOURCE_DIR} default install prefix" FORCE)
  set(CMAKE_INSTALL_BINDIR BIN CACHE PATH "BIN default binary install directory" FORCE)

  if (CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_INSTALL_BINDIR "BIN/Win32/$<CONFIG>" CACHE PATH "BIN/Win32/<config> default binary install directory" FORCE)
  endif ()
endif()

# Make sure we can include and link from the top level source...
include_directories(${CMAKE_SOURCE_DIR} ${SIMH_DEP_TOPDIR}/include)
link_directories(${SIMH_DEP_TOPDIR}/lib)

# A bunch of Windows customizations
if (WIN32)
    list(APPEND CMAKE_LIBRARY_PATH ${SIMH_DEP_TOPDIR}/lib)
    list(APPEND CMAKE_INCLUDE_PATH ${SIMH_DEP_TOPDIR}/include)

    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

    if (MSVC_VERSION GREATER_EQUAL 1920)
        add_compile_definitions(USE_ISO_C99_NAMES)
    endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # For some reason, the MSVC solution builds as 32-bit, but none of the
    # *nix platforms do.
    #
    # If 32-bit compiles have to be added back, uncomment the following 2 lines:
    #
    # add_compile_options("-m32")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
endif (WIN32)

# Tweak GNU's flags
set(EXTRA_CFLAGS "")
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    include(fpintrin)
    # Turn on warnings about strict overflow/potential overflows.
    ## LIST(APPEND EXTRA_CFLAGS "-Wall" "-fno-inline" "-fstrict-overflow" "-Wstrict-overflow=3")
    LIST(APPEND EXTRA_CFLAGS "-Wformat")

    # 'O3' optimization and strict overflow cause all kinds of simulator issues, especially inside
    # the VAX simulators. Reduce optimization and ensure strict overflow is turned off.
    string(REGEX REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    string(REGEX REPLACE "-fstrict-overflow[ \t\r\n]*" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    string(APPEND CMAKE_C_FLAGS_RELEASE " -fno-strict-overflow")

    string(REGEX REPLACE "-O3" "-O2" CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}")
    string(REGEX REPLACE "-fstrict-overflow[ \t\r\n]*" "" CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}")
    string(APPEND CMAKE_C_FLAGS_MINSIZEREL " -fno-strict-overflow")
endif (CMAKE_C_COMPILER_ID STREQUAL "GNU")

# Find packages, arrange for dependency download/compile/install:
#
# SIMH_BUILD_DEPS is the list of the dependecies' names, for pretty-printing.
# SIMH_DEP_TARGETS is the list of dependency targets' names that we'll actually build.

set(SIMH_BUILD_DEPS)
set(SIMH_DEP_TARGETS)

set(THREADING_PKG_STATUS "unknown")
set(ZLIB_PKG_STATUS "unknown")
set(PCRE_PKG_STATUS "unknown")
set(VIDEO_PKG_STATUS "unknown")
set(NETWORK_PKG_STATUS "unknown")

if (WITH_ASYNC)
    include(pthreads-dep)
else (WITH_ASYNC)
    set(THREADING_PKG_STATUS "skipped")
endif (WITH_ASYNC)

include(zlib-dep)
include(pcre-dep)

if (WITH_VIDEO)
    include(video-deps)
    set(BUILD_WITH_VIDEO TRUE)
else (WITH_VIDEO)
    set(VIDEO_PKG_STATUS "skipped")
    set(BUILD_WITH_VIDEO FALSE)
endif (WITH_VIDEO)

if (WITH_NETWORK)
    include(network-deps)
    set(BUILD_WITH_NETWORK TRUE)
else (WITH_NETWORK)
    set(NETWORK_PKG_STATUS "skipped")
    set(BUILD_WITH_NETWORK FALSE)
endif (WITH_NETWORK)

set(CPPCHECK_STATUS "disabled.")

find_program(cppcheck_cmd NAMES cppcheck)
if (cppcheck_cmd)
    list(APPEND cppcheck_cmd
         "--language=c"
         "--enable=warning,style,performance,portability,information,missingInclude"
         "--suppress=missingIncludeSystem"
         "--inline-suppr"
         "--std=c99"
         "--force")
    set(CPPCHECK_STATUS "enabled.")
    if (WIN32)
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            list(APPEND cppcheck_cmd
                 "--platform=win64")
            set(CPPCHECK_STATUS "enabled, Win64 platform.")
        else ()
            list(APPEND cppcheck_cmd
                 "--platform=win32A")
            set(CPPCHECK_STATUS "enabled, Win32 ASCII platform.")
        endif ()
    endif ()
else (cppcheck_cmd)
    set(CPPCHECK_STATUS "'cppcheck' not installed.")
endif ()

message(STATUS "")
message(STATUS "Libraries and features:")
message(STATUS "  Thread support .................. ${THREADING_PKG_STATUS}")
message(STATUS "  zlib ............................ ${ZLIB_PKG_STATUS}")
message(STATUS "  Perl-Compatible RegExps.......... ${PCRE_PKG_STATUS}")
message(STATUS "  PNG, Freetype, SDL2, SDL2_ttf ... ${VIDEO_PKG_STATUS}")
message(STATUS "  Packet Capture (PCAP) ........... ${NETWORK_PKG_STATUS}")
message(STATUS "")
message(STATUS "Build options:")
message(STATUS "  Video/graphics support ....... ${BUILD_WITH_VIDEO}")
message(STATUS "  Networking ................... ${BUILD_WITH_NETWORK}")
if (DONT_SET_ROMS)
    set(ROM_STATUS "No")
else ()
    set(ROM_STATUS "Yes")
endif ()
message(STATUS "  Build internal ROMS .......... ${ROM_STATUS}")
message(STATUS "  'cppcheck' ................... ${CPPCHECK_STATUS}")
message(STATUS "")

unset(ROM_STATUS)

if (NOT DEFINED DO_DEPENDENCY_BUILD OR SIMH_BUILD_DEPS)
    if (DEFINED DO_DEPENDENCY_BUILD AND NOT DO_DEPENDENCY_BUILD AND SIMH_BUILD_DEPS)
        message(FATAL_ERROR "Dependency libraries did not build successfully!!??")
    endif()

    if (SIMH_BUILD_DEPS)
        message(STATUS "Building dependency libraries as a superbuild")
        set(DO_DEPENDENCY_BUILD ON CACHE BOOL "Superbuild flag" FORCE)
    else ()
        set(DO_DEPENDENCY_BUILD OFF CACHE BOOL "Superbuild flag" FORCE)
    endif ()
else ()
    set(DO_DEPENDENCY_BUILD ${DO_DEPENDENCY_BUILD} CACHE BOOL "Superbuild flag" FORCE)
endif ()

if (NOT DO_DEPENDENCY_BUILD)
    message(STATUS "Adding simulators")
    include (add_simulator)

    ## The actual simulators:
    ## The various video outputs for simulators:
    set(DISPLAYL   "${CMAKE_SOURCE_DIR}/display/display.c" "${CMAKE_SOURCE_DIR}/display/sim_ws.c")
    set(DISPLAYVT  "${CMAKE_SOURCE_DIR}/display/vt11.c")
    set(DISPLAY340 "${CMAKE_SOURCE_DIR}/display/type340.c")
    set(DISPLAYNG  "${CMAKE_SOURCE_DIR}/display/ng.c")

    ## Source/include directories:
    set(ALTAIRD    "${CMAKE_SOURCE_DIR}/ALTAIR")
    set(ALTAIRZ80D "${CMAKE_SOURCE_DIR}/AltairZ80")
    set(HP2100D    "${CMAKE_SOURCE_DIR}/HP2100")
    set(HP3000D    "${CMAKE_SOURCE_DIR}/HP3000")
    set(I1401D     "${CMAKE_SOURCE_DIR}/I1401")
    set(I1620D     "${CMAKE_SOURCE_DIR}/I1620")
    set(I7094D     "${CMAKE_SOURCE_DIR}/I7094")
    set(ID16D      "${CMAKE_SOURCE_DIR}/Interdata")
    set(ID32D      "${CMAKE_SOURCE_DIR}/Interdata")
    set(NOVAD      "${CMAKE_SOURCE_DIR}/NOVA")
    set(PDP1D      "${CMAKE_SOURCE_DIR}/PDP1")
    set(PDP10D     "${CMAKE_SOURCE_DIR}/PDP10")
    set(PDP11D     "${CMAKE_SOURCE_DIR}/PDP11")
    set(PDP18BD    "${CMAKE_SOURCE_DIR}/PDP18B")
    set(VAXD       "${CMAKE_SOURCE_DIR}/VAX")

    ## And here's where the actual work gets done:
    if (WITH_SLIRP)
      add_subdirectory(slirp)
    endif (WITH_SLIRP)
    add_subdirectory(3B2)
    add_subdirectory(ALTAIR)
    add_subdirectory(AltairZ80)
    add_subdirectory(B5500)
    add_subdirectory(BESM6)
    add_subdirectory(GRI)
    add_subdirectory(H316)
    add_subdirectory(HP2100)
    add_subdirectory(HP3000)
    add_subdirectory(I1401)
    add_subdirectory(I1620)
    add_subdirectory(I7000)
    add_subdirectory(I7094)
    add_subdirectory(Ibm1130)
    add_subdirectory(Intel-Systems)
    add_subdirectory(Interdata)
    add_subdirectory(LGP)
    add_subdirectory(NOVA)
    add_subdirectory(PDP1)
    add_subdirectory(PDP10)
    add_subdirectory(PDP11)
    add_subdirectory(PDP18B)
    add_subdirectory(PDP8)
    add_subdirectory(S3)
    add_subdirectory(SDS)
    add_subdirectory(SSEM)
    add_subdirectory(TX-0)
    add_subdirectory(VAX)
    add_subdirectory(sigma)
    add_subdirectory(swtp6800)

    # Experimental simulators:
    add_subdirectory(CDC1700)
    ## Nope. Doesn't compile cleanly.
    ## add_subdirectory(SAGE)

    # Install the DLLs... including Packet.DLL
    if (WIN32 AND EXISTS ${SIMH_DEP_TOPDIR}/bin)
        file(GLOB SIMH_DLLS ${SIMH_DEP_TOPDIR}/bin/*.dll)

        install(
            FILES ${SIMH_DLLS}
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
        )
    endif (WIN32 AND EXISTS ${SIMH_DEP_TOPDIR}/bin)
else (NOT DO_DEPENDENCY_BUILD)
    message(STATUS "")
    message(STATUS "The following dependencies need to be built:")
    message(STATUS "")
    message(STATUS "  ${SIMH_BUILD_DEPS}")
    message(STATUS "")

    ExternalProject_Add (simh_superbuild
        DEPENDS
            ${SIMH_DEP_TARGETS}
        SOURCE_DIR
            ${CMAKE_SOURCE_DIR}
        CMAKE_ARGS
            -DDO_DEPENDENCY_BUILD:BOOL=OFF
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        INSTALL_COMMAND ""
        BINARY_DIR
            ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL_CONFIGURE TRUE
        USES_TERMINAL_BUILD     TRUE
    )

    ## Ensure that the next build rechecks the dependency
    ## libraries that were just built and finds them.
    unset(FREETYPE_FOUND CACHE)
    unset(PCAP_FOUND CACHE)
    unset(PCRE_FOUND CACHE)
    unset(PCRE2_FOUND CACHE)
    unset(PNG_FOUND CACHE)
    unset(PTW_FOUND CACHE)
    unset(SDL2_FOUND CACHE)
    unset(SDL2_ttf_FOUND CACHE)
    unset(ZLIB_FOUND CACHE)
endif (NOT DO_DEPENDENCY_BUILD)
