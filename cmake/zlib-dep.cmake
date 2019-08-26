#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the ZLIB dependency
#
# (a) Try to locate the system's installed zlib.
# (b) If system zlib isn't available, build it as an external project.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

include (FindZLIB)

add_library(zlib_lib INTERFACE)

if (ZLIB_FOUND)
    target_compile_definitions(zlib_lib INTERFACE ${ZLIB_INCLUDE_DIRS})
    target_link_libraries(zlib_lib INTERFACE ${ZLIB_LIBRARIES})

    set(ZLIB_PKG_STATUS "installed ZLIB")
else (ZLIB_FOUND)
    include (ExternalProject)

    set(ZLIB_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/build-stage)

    ExternalProject_Add(zlib-dep
	GIT_REPOSITORY https://github.com/madler/zlib.git
	GIT_TAG v1.2.11
	CMAKE_ARGS 
	    -DCMAKE_INSTALL_PREFIX=${ZLIB_INSTALL_PREFIX}
    )

    list(APPEND SIMH_BUILD_DEPS zlib)
    message(STATUS "Building ZLIB from github repository.")
    set(ZLIB_PKG_STATUS "ZLIB dependent build")
endif (ZLIB_FOUND)
