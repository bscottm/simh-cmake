#
function(add_simulator _targ _sources _defines _includes)
  add_executable("${_targ}" "${_sources}")

  # This is a quick cheat to make sure that 
  set(_normalized_includes)
  foreach (inc IN LISTS _includes)
    if (NOT IS_ABSOLUTE "${inc}")
      get_filename_component(inc "${CMAKE_SOURCE_DIR}/${inc}" ABSOLUTE)
    endif ()
    list(APPEND _normalized_includes "${inc}")
  endforeach ()

  target_sources("${_targ}" PRIVATE "${SIM_SOURCES}")
  target_compile_definitions("${_targ}" PRIVATE "${_defines}")
  target_include_directories("${_targ}" PRIVATE "${_normalized_includes}")

  if (${PCRE_FOUND})
    target_compile_definitions("${_targ}" PRIVATE HAVE_PCREPOSIX_H PCRE_STATIC)
    target_include_directories("${_targ}" PRIVATE "${PCRE_INCLUDE_DIRS}")

    target_link_libraries("${_targ}" pcreposix "${PCRE_LIBRARIES}")
  endif (${PCRE_FOUND})

  if (${PNG_FOUND})
    target_compile_definitions("${_targ}" PRIVATE ${PNG_DEFINITIONS})
    target_include_directories("${_targ}" PRIVATE "${PNG_INCLUDE_DIRS}")
    target_link_libraries("${_targ}" "${PNG_LIBRARIES}")
  endif ()

  if (${PCAP_FOUND})
    target_compile_definitions("${_targ}" PRIVATE USE_SHARED HAVE_PCAP_NETWORK)
    target_include_directories("${_targ}" PRIVATE "${PCAP_INCLUDE_DIRS}")
    target_link_libraries("${_targ}" "${PCAP_LIBRARIES}")
  endif ()

  if (${PCAP_FOUND}) # more to come with SLirP
    target_compile_definitions("${_targ}" PRIVATE USE_NETWORK HAVE_SLIRP_NETWORK)
    target_include_directories("${_targ}" PRIVATE
      "${CMAKE_SOURCE_DIR}/slirp"
      "${CMAKE_SOURCE_DIR}/slirp_glue"
      "${CMAKE_SOURCE_DIR}/slirp_glue/qemu"
      "${CMAKE_SOURCE_DIR}/slirp_glue/qemu/win32/include")
    add_dependencies("${_targ}" slirp)
    target_link_libraries("${_targ}" slirp Iphlpapi)
  endif ()

  if (ZLIB_FOUND)
    # Add zlib, just in case. PCRE depends on it, and PNG might also (although, PNG
    # probably adds it to the link libraries anyway, but it doesn't hurt to add it
    # twice.
    target_link_libraries("${_targ}" "${ZLIB_LIBRARIES}")
  endif (ZLIB_FOUND)

  if (WIN32)
    # Have pthreads... go with async I/O
    if (PTW_FOUND)
      # Remember to remove SIM_ASYNCH_IO if the TODO option is False.
      target_compile_definitions("${_targ}" PRIVATE USE_READER_THREAD PTW32_STATIC_LIB _POSIX_C_SOURCE SIM_ASYNCH_IO)
      target_include_directories("${_targ}" PRIVATE "${PTW_INCLUDE_DIRS}")
      target_link_libraries("${_targ}" "${PTW_LIBRARIES}")
    endif ()

    if (NOT MSVC)
      # Need the math library...
      target_link_libraries("${_targ}" m)
    endif ()

    target_link_libraries("${_targ}" wsock32 winmm)

    if ("${MSVC_VERSION}" GREATER_EQUAL 1920)
      # MSVCRT conflicts with the new ucrt C runtime:
      # target_link_options("${_targ}" PRIVATE "/NODEFAULTLIB:MSVCRT")
    endif ()

    add_dependencies("${_targ}" "bin_directory")

    if (MSVC)
      add_custom_command(TARGET "${_targ}" POST_BUILD
	COMMAND ${COPY_CMD} "$<SHELL_PATH:$<TARGET_FILE:${_targ}>>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/BIN/Win32/$<CONFIG>>")
    else ()
      add_custom_command(TARGET "${_targ}" POST_BUILD
	COMMAND ${COPY_CMD} "$<SHELL_PATH:$<TARGET_FILE:${_targ}>>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/BIN>")
    endif ()
  endif ()

  set(_current_incs)
  set(_current_defs)
endfunction ()

