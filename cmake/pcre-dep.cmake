#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the PCRE dependency
#
# (a) Try to locate the system's installed pcre/pcre2 librariy.
# (b) If system they aren't available, build pcre as an external project.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

add_library(regexp_lib INTERFACE)

include (FindPCRE)
include (FindPCRE2)

if (NOT (PCRE_FOUND OR PCRE2_FOUND) AND PKG_CONFIG_FOUND)
    pkg_check_modules(PCRE2 IMPORTED_TARGET libpcre2-8)
    pkg_check_modules(PCRE IMPORTED_TARGET libpcre)
endif (NOT (PCRE_FOUND OR PCRE2_FOUND) AND PKG_CONFIG_FOUND)

## Prefer PCRE2 over older PCRE
if (PCRE2_FOUND)
    target_compile_definitions(regexp_lib INTERFACE HAVE_PCRE2_H PCRE_STATIC)
    target_include_directories(regexp_lib INTERFACE ${PCRE2_INCLUDE_DIRS})
    target_link_libraries(regexp_lib INTERFACE ${PCRE2_LIBRARY})

    set(PCRE_PKG_STATUS "installed pcre2")
elseif (PCRE_FOUND)
    target_compile_definitions(regexp_lib INTERFACE HAVE_PCRE_H PCRE_STATIC)
    target_include_directories(regexp_lib INTERFACE ${PCRE_INCLUDE_DIRS})
    target_link_libraries(regexp_lib INTERFACE ${PCRE_LIBRARY})

    set(PCRE_PKG_STATUS "installed pcre")
else ()
    set(PCRE_DEPS)
    if (NOT ZLIB_FOUND)
        list(APPEND PCRE_DEPS zlib-dep)
    endif (NOT ZLIB_FOUND)

    ExternalProject_Add(pcre-ext
        URL https://ftp.pcre.org/pub/pcre/pcre2-10.33.zip
        CMAKE_ARGS 
            -DCMAKE_INSTALL_PREFIX=${SIMH_DEP_TOPDIR}
            -DCMAKE_PREFIX_PATH=${SIMH_PREFIX_PATH_LIST}
            -DCMAKE_INCLUDE_PATH=${SIMH_INCLUDE_PATH_LIST}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        DEPENDS
            ${PCRE_DEPS}
    )

    list(APPEND SIMH_BUILD_DEPS pcre)
    list(APPEND SIMH_DEP_TARGETS pcre-ext)
    message(STATUS "Building PCRE from https://ftp.pcre.org/pub/pcre/pcre2-10.33.zip")
    set(PCRE_PKG_STATUS "pcre2 dependent build")
endif ()
