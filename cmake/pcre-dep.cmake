#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the PCRE dependency
#
# (a) Try to locate the system's installed pcre/pcre2 librariy.
# (b) If system they aren't available, build pcre as an external project.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=


add_library(regexp_lib INTERFACE)

include (FindPCRE)
if (PCRE_FOUND OR PCRE2_FOUND)
    if (PCRE_FOUND)
	target_compile_definitions(regexp_lib INTERFACE HAVE_PCREPOSIX_H PCRE_STATIC)
	target_include_directories(regexp_lib INTERFACE ${PCRE_INCLUDE_DIRS})
	target_link_libraries(regexp_lib INTERFACE ${PCREPOSIX_LIBRARY} ${PCRE_LIBRARY})

	set(PCRE_PKG_STATUS "installed pcre")
    elseif (PCRE2_FOUND)
	target_compile_definitions(regexp_lib INTERFACE HAVE_PCRE2_POSIX_H)
	target_include_directories(regexp_lib INTERFACE ${PCRE2_INCLUDE_DIRS})
	target_link_libraries(regexp_lib INTERFACE ${PCRE2_POSIX_LIBARY} ${PCRE2_LIBRARY})

	set(PCRE_PKG_STATUS "installed pcre2")
    endif (PCRE_FOUND)
else (PCRE_FOUND OR PCRE2_FOUND)
    include(ExternalProject)

    set(PCRE_INSTALL_DIR ${CMAKE_BINARY_DIR}/build-stage)
    set(PCRE_DEPS)
    if (NOT ZLIB_FOUND)
	list(APPEND PCRE_DEPS zlib-dep)
    endif (NOT ZLIB_FOUND)

    ExternalProject_Add(pcre-ext
	URL https://ftp.pcre.org/pub/pcre/pcre2-10.33.zip
	CMAKE_ARGS 
	    -DCMAKE_INSTALL_PREFIX=${PCRE_INSTALL_DIR}
	DEPENDS ${PCRE_DEPS}
    )

    list(APPEND SIMH_BUILD_DEPS pcre)
    message(STATUS "Building PCRE from https://ftp.pcre.org/pub/pcre/pcre2-10.33.zip")
    set(PCRE_PKG_STATUS "pcre2 dependent build")
endif (PCRE_FOUND OR PCRE2_FOUND)
