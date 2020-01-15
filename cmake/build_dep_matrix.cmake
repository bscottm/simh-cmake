#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
# build_dep_matrix.cmake
#
# This is a minor hack to build all of the various library compile
# configurations. Might take a bit more time upfront to build the
# dependencies, but the user doesn't have to go backward and attempt
# to build the dependencies themselves.
#
# Author: B. Scott Michel
# "scooter me fecit"
#~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=


function(BuildDepMatrix dep pretty)
    cmake_parse_arguments(_BDM "" "RELEASE_BUILD;DEBUG_BUILD" "CMAKE_ARGS" ${ARGN})

    set(cmake_cfg_args "-G${CMAKE_GENERATOR}")
    if (CMAKE_GENERATOR_PLATFORM)
        list(APPEND cmake_cfg_args "-A${CMAKE_GENERATOR_PLATFORM}")
    endif ()
    list(APPEND cmake_cfg_args ${DEP_CMAKE_ARGS})
    list(APPEND cmake_cfg_args "-DCMAKE_PREFIX_PATH=${SIMH_PREFIX_PATH_LIST}"
                               "-DCMAKE_INCLUDE_PATH=${SIMH_INCLUDE_PATH_LIST}"
                               "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
                               ${_BDM_CMAKE_ARGS}
                               "<SOURCE_DIR>"
    )

    if (NOT _BDM_RELEASE_BUILD)
        set(_BDM_RELEASE_BUILD "Release")
    endif (NOT _BDM_RELEASE_BUILD)

    if (NOT _BDM_DEBUG_BUILD)
        set(_BDM_DEBUG_BUILD "Debug")
    endif (NOT _BDM_DEBUG_BUILD)

    if (NOT CMAKE_CONFIGURATION_TYPES)
        ExternalProject_Add_Step(${dep} build-Release
            COMMENT "Building Release ${pretty}"
            DEPENDEES configure
            WORKING_DIRECTORY <BINARY_DIR>
            COMMAND ${CMAKE_COMMAND} -E remove -f CMakeCache.txt
            COMMAND ${CMAKE_COMMAND} -E remove_directory CMakeFiles
            COMMAND ${CMAKE_COMMAND} ${cmake_cfg_args} -DCMAKE_BUILD_TYPE=${_BDM_RELEASE_BUILD} -DCMAKE_INSTALL_PREFIX=${SIMH_DEP_TOPDIR}
            COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${_BDM_RELEASE_BUILD} --clean-first
            COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config ${_BDM_RELEASE_BUILD}
        )
        ExternalProject_Add_Step(${dep} build-Debug
            COMMENT "Building Debug ${pretty}"
            DEPENDEES configure
            WORKING_DIRECTORY <BINARY_DIR>
            COMMAND ${CMAKE_COMMAND} -E remove -f CMakeCache.txt
            COMMAND ${CMAKE_COMMAND} -E remove_directory CMakeFiles
            COMMAND ${CMAKE_COMMAND} ${cmake_cfg_args} -DCMAKE_BUILD_TYPE=${_BDM_DEBUG_BUILD} -DCMAKE_INSTALL_PREFIX=${SIMH_DEP_TOPDIR}
            COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${_BDM_DEBUG_BUILD} --clean-first
            COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config ${_BDM_DEBUG_BUILD}
        )
    else (NOT CMAKE_CONFIGURATION_TYPES)
        ## foreach (cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
        foreach (cfg IN ITEMS Release Debug)
            ExternalProject_Add_Step(${dep} build-${cfg}
                COMMENT "-- Building ${pretty} '${cfg}' configuration"
                DEPENDEES configure
                WORKING_DIRECTORY <BINARY_DIR>
                COMMAND ${CMAKE_COMMAND} -E remove -f CMakeCache.txt
                COMMAND ${CMAKE_COMMAND} -E remove_directory CMakeFiles
                COMMAND ${CMAKE_COMMAND} ${cmake_cfg_args} -DCMAKE_INSTALL_PREFIX=${SIMH_DEP_TOPDIR}
                COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config "${cfg}" --clean-first
                COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config "${cfg}"
            )
        endforeach ()
    endif (NOT CMAKE_CONFIGURATION_TYPES)
endfunction ()
