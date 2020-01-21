#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the ZLIB dependency
#
# (a) Try to locate the system's installed zlib.
# (b) If system zlib isn't available, build it as an external project.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

add_library(zlib_lib INTERFACE)

find_package(ZLIB)
if (NOT ZLIB_FOUND AND PKG_CONFIG_FOUND)
    pkg_check_modules(ZLIB IMPORTED_TARGET zlib)
endif (NOT ZLIB_FOUND AND PKG_CONFIG_FOUND)

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

## Freetype will sometimes find BZip2 in AppVeyor's image, which means that we
## need to bring it along as a dependency for AppVeyor builds. Ordinarily, though,
## it's not a dependency for SIMH.
find_package(BZip2)
if (BZIP2_FOUND)
    if (TARGET BZip2::BZip2)
	target_link_libraries(zlib_lib INTERFACE BZip2::BZip2)
    else (TARGET BZip2::BZip2)
	target_compile_definitions(zlib_lib INTERFACE ${BZIP2_INCLUDE_DIR})
	target_link_libraries(zlib_lib INTERFACE ${BZIP2_LIBRARIES})
    endif (TARGET BZip2::BZip2)
endif (BZIP2_FOUND)
