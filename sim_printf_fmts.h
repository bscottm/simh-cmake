/*~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
 * sim_printf_fmts.h
 * 
 * Cross-platform printf() formats for simh data types. Refactored out to
 * this header so that these formats are avaiable to more than SCP.
 * 
 * Author: B. Scott Michel
 * 
 * "scooter me fecit"
 *~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/

#pragma once
#if !defined(SIM_PRINTF_H)

#if defined (_WIN32) /* Actually, a GCC issue */
#  define LL_FMT "I64"
#else
#  if defined (__VAX) /* No 64 bit ints on VAX */
#    define LL_FMT "l"
#  else
#    define LL_FMT "ll"
#  endif
#endif

#if defined (USE_INT64)
#  define T_VALUE_FMT     LL_FMT
#  define T_SVALUE_FMT    LL_FMT
#else
#  define T_VALUE_FMT     ""
#  define T_SVALUE_FMT    ""
#endif

#if defined (USE_INT64) && defined (USE_ADDR64)
#  define T_ADDR_FMT      LL_FMT
#else
#  define T_ADDR_FMT      ""
#endif

/* cross-platform printf() format specifiers: 
 *
 * Note: MS apparently does recognize "ll" as "l" in its printf() routines, but "I64" is
 * preferred for 64-bit types. And tamps down on MinGW's "-Wformat" diagnostics.
 */
#if defined(_WIN32)
#  if defined(_WIN64)
#    define SIZE_T_FMT   "I64"
#    define SOCKET_FMT   "I64"
#  else
#    define SIZE_T_FMT   ""
#    define SOCKET_FMT   ""
#  endif
#  define T_UINT64_FMT   "I64"
#  define T_INT64_FMT    "I64"
#  define NTOHL_FMT      "lu"
#  define IP_SADDR_FMT   "l"
#  define POINTER_FMT    "p"
#elif defined(__GNU_LIBRARY__) || defined(__GLIBC__) || defined(__GLIBC_MINOR__)
/* glibc (basically, most Linuxen) */
#  define SIZE_T_FMT     "z"
#  define T_UINT64_FMT   "ll"
#  define T_INT64_FMT    "ll"
#  define NTOHL_FMT      "l"
#  define IP_SADDR_FMT   "l"
#  define SOCKET_FMT     "l"
#  define POINTER_FMT    "p"
#else
/* punt. */
#  define SIZE_T_FMT     LL_FMT
#  define T_UINT64_FMT   LL_FMT
#  define T_INT64_FMT    LL_FMT
#  define NTOHL_FMT      "l"
#  define IP_SADDR_FMT   "l"
#  define SOCKET_FMT     "l"
#  define POINTER_FMT    LL_FMT
#endif

#define SIM_PRINTF_H
#endif
