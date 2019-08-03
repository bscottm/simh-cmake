## Compile SLirp as its own standalone library

set(SLIRP_SOURCES
  "${CMAKE_SOURCE_DIR}/slirp/arp_table.c"
  "${CMAKE_SOURCE_DIR}/slirp/bootp.c"
  "${CMAKE_SOURCE_DIR}/slirp/bootp.h"
  "${CMAKE_SOURCE_DIR}/slirp/cksum.c"
  "${CMAKE_SOURCE_DIR}/slirp/dnssearch.c"
  "${CMAKE_SOURCE_DIR}/slirp/if.c"
  "${CMAKE_SOURCE_DIR}/slirp/ip_icmp.c"
  "${CMAKE_SOURCE_DIR}/slirp/ip_input.c"
  "${CMAKE_SOURCE_DIR}/slirp/ip_output.c"
  "${CMAKE_SOURCE_DIR}/slirp/mbuf.c"
  "${CMAKE_SOURCE_DIR}/slirp/misc.c"
  "${CMAKE_SOURCE_DIR}/slirp/sbuf.c"
  "${CMAKE_SOURCE_DIR}/slirp/slirp.c"
  "${CMAKE_SOURCE_DIR}/slirp/socket.c"
  "${CMAKE_SOURCE_DIR}/slirp/tcp_input.c"
  "${CMAKE_SOURCE_DIR}/slirp/tcp_output.c"
  "${CMAKE_SOURCE_DIR}/slirp/tcp_subr.c"
  "${CMAKE_SOURCE_DIR}/slirp/tcp_timer.c"
  "${CMAKE_SOURCE_DIR}/slirp/tftp.c"
  "${CMAKE_SOURCE_DIR}/slirp/udp.c"
  "${CMAKE_SOURCE_DIR}/slirp_glue/glib_qemu_stubs.c"
  "${CMAKE_SOURCE_DIR}/slirp_glue/sim_slirp.c")

add_library(slirp STATIC "${SLIRP_SOURCES}")
target_compile_definitions(slirp PRIVATE HAVE_SLIRP_NETWORK USE_SIMH_SLIRP_DEBUG _WINSOCK_DEPRECATED_NO_WARNINGS)

target_include_directories(slirp PRIVATE
  "${CMAKE_SOURCE_DIR}/slirp"
  "${CMAKE_SOURCE_DIR}/slirp_glue"
  "${CMAKE_SOURCE_DIR}/slirp_glue/qemu"
  "${CMAKE_SOURCE_DIR}/slirp_glue/qemu/win32/include")
