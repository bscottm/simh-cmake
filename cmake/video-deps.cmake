#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# Manage the freetype, SDL2, SDL2_ttf dependencies
#
# (a) Try to locate the system's installed libraries.
# (b) Build a dependent libraries, if not found.
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

include (ExternalProject)

add_library(simh_video INTERFACE)

set(VIDEO_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/build-stage)

if (WITH_VIDEO)
    find_package (PNG)

    if (PNG_FOUND)
	target_compile_definitions(simh_video INTERFACE ${PNG_DEFINITIONS} HAVE_LIBPNG)
	target_include_directories(simh_video INTERFACE "${PNG_INCLUDE_DIRS}")
	target_link_libraries(simh_video INTERFACE "${PNG_LIBRARIES}")

	set(VIDEO_PKG_STATUS "installed PNG")
    else ()
	set(PNG_DEPS)
	if (NOT ZLIB_FOUND)
	    list(APPEND PNG_DEPS zlib-dep)
	endif (NOT ZLIB_FOUND)

	ExternalProject_Add(png-dep
	    URL https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.xz/download
	    CMAKE_ARGS 
		-DCMAKE_INSTALL_PREFIX=${VIDEO_INSTALL_PREFIX}
	    DEPENDS ${PNG_DEPS}
	)

	list(APPEND SIMH_BUILD_DEPS "png")
	message(STATUS "Building PNG from https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.xz/download")
	set(VIDEO_PKG_STATUS "PNG dependent build")
    endif ()

    find_package(Freetype)

    if (FREETYPE_FOUND)
	target_link_libraries(simh_video INTERFACE Freetype::Freetype)
	set(VIDEO_PKG_STATUS "${VIDEO_PKG_STATUS}, installed Freetype")
    else (FREETYPE_FOUND)
	if (NOT ZLIB_FOUND)
	    list(APPEND FREETYPE_DEPS "zlib-dep")
	endif (NOT ZLIB_FOUND)
	if (NOT PNG_FOUND)
	    list(APPEND FREETYPE_DEPS "png-dep")
	endif ()

	ExternalProject_Add(freetype-dep
	    GIT_REPOSITORY https://git.sv.nongnu.org/r/freetype/freetype2.git
	    GIT_TAG VER-2-10-1
	    CMAKE_ARGS 
		-DCMAKE_INSTALL_PREFIX=${VIDEO_INSTALL_PREFIX}
	    DEPENDS ${FREETYPE_DEPS}
	)

	list(APPEND SIMH_BUILD_DEPS "freetype")
	message(STATUS "Building Freetype from github repository.")
	set(VIDEO_PKG_STATUS "F${VIDEO_PKG_STATUS}, Freetype dependent build")
    endif (FREETYPE_FOUND)

    find_package(SDL2 CONFIG)
    find_package(SDL2_ttf CONFIG)

    IF (SDL2_FOUND AND SDL2_ttf_FOUND)
        target_compile_definitions(simh_video INTERFACE USE_SIM_VIDEO HAVE_LIBSDL)
	target_link_libraries(simh_video INTERFACE SDL2_ttf::SDL2_ttf SDL2::SDL2)
	set(VIDEO_PKG_STATUS "${VIDEO_PKG_STATUS}, installed SDL2 and SDL2_ttf")
    ELSE (SDL2_FOUND AND SDL2_ttf_FOUND)
	IF (NOT SDL2_FOUND)
	    ExternalProject_Add(sdl2-dep
		URL https://www.libsdl.org/release/SDL2-2.0.10.zip
		CMAKE_ARGS 
		    -DCMAKE_INSTALL_PREFIX=${VIDEO_INSTALL_PREFIX}
	    )

	    list(APPEND SIMH_BUILD_DEPS "SDL2")
	    message(STATUS "Building SDL2 from https://www.libsdl.org/release/SDL2-2.0.10.zip.")
	    set(VIDEO_PKG_STATUS "${VIDEO_PKG_STATUS}, SDL2 dependent build")
	ELSE (NOT SDL2_FOUND)
	    set(VIDEO_PKG_STATUS "${VIDEO_PKG_STATUS}, installed SDL2")
	ENDIF (NOT SDL2_FOUND)

	IF (NOT SDL2_ttf_FOUND)
	    set(SDL2_ttf_depdir ${CMAKE_BINARY_DIR}/sdl2-ttf-dep-prefix/src/sdl2-ttf-dep/)
	    set(SDL2_ttf_DEPS "")
	    if (NOT SDL2_FOUND)
		list(APPEND SDL2_ttf_DEPS sdl2-dep)
	    endif (NOT SDL2_FOUND)
	    if (NOT FREETYPE_FOUND)
		list(APPEND SDL2_ttf_DEPS freetype-dep)
	    endif (NOT FREETYPE_FOUND)

	    ExternalProject_Add(sdl2-ttf-dep
		URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.zip
		CMAKE_ARGS 
		    -DCMAKE_INSTALL_PREFIX=${VIDEO_INSTALL_PREFIX}
		UPDATE_COMMAND
		    ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/dep-patches/SDL2_ttf/SDL2_ttfConfig.cmake ${SDL2_ttf_depdir}
		DEPENDS ${SDL2_ttf_DEPS}
	    )

	    list(APPEND SIMH_BUILD_DEPS "SDL2_ttf")
	    message(STATUS "Building SDL2_ttf from https://www.libsdl.org/release/SDL2_ttf-2.0.15.zip.")
	    set(VIDEO_PKG_STATUS "${VIDEO_PKG_STATUS}, SDL2_ttf dependent build")
	ELSE (NOT SDL2_ttf_FOUND)
	    set(VIDEO_PKG_STATUS "${VIDEO_PKG_STATUS}, installed SDL2_ttf")
	ENDIF (NOT SDL2_ttf_FOUND)
    ENDIF (SDL2_FOUND AND SDL2_ttf_FOUND)
endif ()
