#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the ZLIB dependency
#
# (a) Try to locate the system's installed zlib.
# (b) If system zlib isn't available, build it as an external project.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

include (FindZLIB)
if (NOT ZLIB_FOUND AND PKG_CONFIG_FOUND)
    pkg_check_modules(ZLIB IMPORTED_TARGET zlib)
endif (NOT ZLIB_FOUND AND PKG_CONFIG_FOUND)

add_library(zlib_lib INTERFACE)

if (ZLIB_FOUND)
    if (TARGET ZLIB::ZLIB)
        target_link_libraries(zlib_lib INTERFACE ZLIB::ZLIB)
    elseif (TARGET PkgConfig::ZLIB)
        target_link_libraries(zlib_lib INTERFACE PkgConfig::ZLIB)
    else (TARGET ZLIB::ZLIB)
        target_compile_definitions(zlib_lib INTERFACE ${ZLIB_INCLUDE_DIRS})
        target_link_libraries(zlib_lib INTERFACE ${ZLIB_LIBRARIES})
    endif (TARGET ZLIB::ZLIB)

    set(ZLIB_PKG_STATUS "installed ZLIB")
else (ZLIB_FOUND)
    include (ExternalProject)
    set(ZLIB_REPO_URL https://github.com/madler/zlib.git)

    ExternalProject_Add(zlib-dep
        GIT_REPOSITORY ${ZLIB_REPO_URL}
        GIT_TAG v1.2.11
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    BuildDepMatrix(zlib-dep zlib)

    list(APPEND SIMH_BUILD_DEPS zlib)
    list(APPEND SIMH_DEP_TARGETS zlib-dep)
    message(STATUS "Building ZLIB from ${ZLIB_REPO_URL}.")
    set(ZLIB_PKG_STATUS "ZLIB source build")
endif (ZLIB_FOUND)
