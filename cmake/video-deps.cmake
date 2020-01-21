#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the freetype, SDL2, SDL2_ttf dependencies
#
# (a) Try to locate the system's installed libraries.
# (b) Build dependent libraries, if not found.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

add_library(simh_video INTERFACE)

if (WITH_VIDEO)
    set(VIDEO_PKG_STATUS)

    find_package(SDL2 CONFIG)
    if (NOT SDL2_FOUND AND PKG_CONFIG_FOUND)
        pkg_check_modules(SDL2 IMPORTED_TARGET SDL2)
    endif (NOT SDL2_FOUND AND PKG_CONFIG_FOUND)

    find_package(SDL2_ttf CONFIG)
    IF (NOT SDL2_ttf_FOUND AND PKG_CONFIG_FOUND)
        pkg_check_modules(SDL2_ttf IMPORTED_TARGET SDL2_ttf)
    ENDIF (NOT SDL2_ttf_FOUND AND PKG_CONFIG_FOUND)
    
    IF (SDL2_FOUND AND SDL2_ttf_FOUND)
        target_compile_definitions(simh_video INTERFACE USE_SIM_VIDEO HAVE_LIBSDL)

        IF (TARGET SDL2_ttf::SDL2_ttf)
            target_link_libraries(simh_video INTERFACE SDL2_ttf::SDL2_ttf)
        ELSEIF (TARGET PkgConfig::SDL2_ttf)
            target_link_libraries(simh_video INTERFACE PkgConfig::SDL2_ttf)
        ELSEIF (DEFINED SDL2_ttf_LIBRARIES AND DEFINED SDL2_ttf_INCLUDE_DIRS)
            ## target_link_directories(simh_video INTERFACE ${SDL2_ttf_LIBDIR})
            target_link_libraries(simh_video INTERFACE ${SDL2_ttf_LIBRARIES})
            target_include_directories(simh_video INTERFACE ${SDL2_ttf_INCLUDE_DIRS})
        ELSE ()
            message(FATAL_ERROR "SDL2_ttf_FOUND set but no SDL2_ttf::SDL2_ttf import library or SDL2_ttf_LIBRARIES/SDL2_ttf_INCLUDE_DIRS? ")
        ENDIF ()

        IF (TARGET SDL2::SDL2)
            target_link_libraries(simh_video INTERFACE SDL2::SDL2)
        ELSEIF (TARGET PkgConfig::SDL2)
            target_link_libraries(simh_video INTERFACE PkgConfig::SDL2)
        ELSEIF (DEFINED SDL2_LIBRARIES AND DEFINED SDL2_INCLUDE_DIRS)
            ## target_link_directories(simh_video INTERFACE ${SDL2_LIBDIR})
            target_link_libraries(simh_video INTERFACE ${SDL2_LIBRARIES})
            target_include_directories(simh_video INTERFACE ${SDL2_INCLUDE_DIRS})
        ELSE ()
            message(FATAL_ERROR "SDL2_FOUND set but no SDL2::SDL2 import library or SDL2_LIBRARIES/SDL2_INCLUDE_DIRS? ")
        ENDIF ()

        list(APPEND VIDEO_PKG_STATUS "installed SDL2 and SDL2_ttf")
    ELSE (SDL2_FOUND AND SDL2_ttf_FOUND)
        IF (NOT SDL2_FOUND)
            ExternalProject_Add(sdl2-dep
                URL https://www.libsdl.org/release/SDL2-2.0.10.zip
                CONFIGURE_COMMAND ""
                BUILD_COMMAND ""
                INSTALL_COMMAND ""
            )

            BuildDepMatrix(sdl2-dep SDL2)

            list(APPEND SIMH_BUILD_DEPS "SDL2")
            list(APPEND SIMH_DEP_TARGETS "sdl2-dep")
            message(STATUS "Building SDL2 from https://www.libsdl.org/release/SDL2-2.0.10.zip.")
            list(APPEND VIDEO_PKG_STATUS "SDL2 source build")
        ELSE (NOT SDL2_FOUND)
            list(APPEND VIDEO_PKG_STATUS "installed SDL2")
        ENDIF (NOT SDL2_FOUND)

        IF (NOT SDL2_ttf_FOUND)
            set(SDL2_ttf_depdir ${CMAKE_BINARY_DIR}/sdl2-ttf-dep-prefix/src/sdl2-ttf-dep/)
            set(SDL2_ttf_DEPS)

            if (NOT SDL2_FOUND)
                list(APPEND SDL2_ttf_DEPS sdl2-dep)
            endif (NOT SDL2_FOUND)

            ExternalProject_Add(sdl2-ttf-dep
                URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.zip
                CONFIGURE_COMMAND ""
                BUILD_COMMAND ""
                INSTALL_COMMAND ""
                UPDATE_COMMAND
                    ${CMAKE_COMMAND} -E copy ${SIMH_DEP_PATCHES}/SDL2_ttf/SDL2_ttfConfig.cmake ${SDL2_ttf_depdir}
                DEPENDS
                    ${SDL2_ttf_DEPS}
            )

            BuildDepMatrix(sdl2-ttf-dep SDL2_ttf)

            list(APPEND SIMH_BUILD_DEPS "SDL2_ttf")
            list(APPEND SIMH_DEP_TARGETS "sdl2-ttf-dep")
            message(STATUS "Building SDL2_ttf from https://www.libsdl.org/release/SDL2_ttf-2.0.15.zip.")
            list(APPEND VIDEO_PKG_STATUS "SDL2_ttf source build")
        ELSE (NOT SDL2_ttf_FOUND)
            list(APPEND VIDEO_PKG_STATUS "installed SDL2_ttf")
        ENDIF (NOT SDL2_ttf_FOUND)
    ENDIF (SDL2_FOUND AND SDL2_ttf_FOUND)

    find_package(freetype CONFIG)
    if (NOT FREETYPE_FOUND)
        find_package(Freetype)
        if (NOT FREETYPE_FOUND AND PKG_CONFIG_FOUND)
            pkg_check_modules(FREETYPE IMPORTED_TARGET freetype2)
        endif (NOT FREETYPE_FOUND AND PKG_CONFIG_FOUND)
    endif (NOT FREETYPE_FOUND)

    if (FREETYPE_FOUND)
        if (TARGET Freetype::Freetype)
            target_link_libraries(simh_video INTERFACE Freetype::Freetype)
        elseif (TARGET PkgConfig::FREETYPE)
            target_link_libraries(simh_video INTERFACE PkgConfig::FREETYPE)
        endif (TARGET Freetype::Freetype)

        list(APPEND VIDEO_PKG_STATUS "installed Freetype")
    else (FREETYPE_FOUND)
        ExternalProject_Add(freetype-dep
            GIT_REPOSITORY https://git.sv.nongnu.org/r/freetype/freetype2.git
            GIT_TAG VER-2-10-1
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )

        if (NOT SDL2_ttf_FOUND)
            add_dependencies(sdl2-ttf-dep freetype-dep)
        endif (NOT SDL2_ttf_FOUND)

        BuildDepMatrix(freetype-dep FreeType)

        list(APPEND SIMH_BUILD_DEPS "freetype")
        list(APPEND SIMH_DEP_TARGETS "freetype-dep")
        message(STATUS "Building Freetype from github repository.")
        list(APPEND VIDEO_PKG_STATUS "Freetype source build")
    endif (FREETYPE_FOUND)

    find_package(libpng CONFIG NAMES libpng libpng16)
    if (TARGET png)
        message(STATUS "libpng16 configuration found")
    endif()

    find_package (PNG)
    if (NOT PNG_FOUND AND PKG_CONFIG_FOUND)
        pkg_check_modules(PNG IMPORTED_TARGET libpng)
    endif (NOT PNG_FOUND AND PKG_CONFIG_FOUND)

    if (PNG_FOUND)
        if (TARGET PkgConfig::PNG)
            target_link_libraries(simh_video INTERFACE PkgConfig::PNG)
        else (TARGET PkgConfig::PNG)
            target_include_directories(simh_video INTERFACE ${PNG_INCLUDE_DIRS})
            target_link_libraries(simh_video INTERFACE ${PNG_LIBRARIES})
        endif (TARGET PkgConfig::PNG)

        target_compile_definitions(simh_video INTERFACE ${PNG_DEFINITIONS} HAVE_LIBPNG)

        list(APPEND VIDEO_PKG_STATUS "installed PNG")
    else ()
        set(PNG_DEPS)
        if (NOT ZLIB_FOUND)
            list(APPEND PNG_DEPS zlib-dep)
        endif (NOT ZLIB_FOUND)

        set(PNG_SOURCE_URL "https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.xz/download")

        ExternalProject_Add(png-dep
            URL ${PNG_SOURCE_URL}
            DEPENDS
                ${PNG_DEPS}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )

        ## Work around the GCC 8.1.0 SEH index regression.
        set(PNG_CMAKE_BUILD_TYPE_RELEASE "Release")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU" AND
            CMAKE_C_COMPILER_VERSION VERSION_EQUAL "8.1" AND
            NOT CMAKE_BUILD_VERSION)
            message(STATUS "PNG: Build using MinSizeRel CMAKE_BUILD_TYPE with GCC 8.1")
            set(PNG_CMAKE_BUILD_TYPE_RELEASE "MinSizeRel")
        endif()

        BuildDepMatrix(png-dep libpng RELEASE_BUILD ${PNG_CMAKE_BUILD_TYPE_RELEASE})
        
        if (NOT FREETYPE_FOUND)
            add_dependencies(freetype-dep png-dep)
        endif (NOT FREETYPE_FOUND)

        list(APPEND SIMH_BUILD_DEPS "png")
        list(APPEND SIMH_DEP_TARGETS "png-dep")
        message(STATUS "Building PNG from ${PNG_SOURCE_URL}")
        list(APPEND VIDEO_PKG_STATUS "PNG source build")
    endif ()
endif ()

string(REPLACE ";" ", " VIDEO_PKG_STATUS "${VIDEO_PKG_STATUS}")