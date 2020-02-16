/* sim_os_renames.h
 *
 * Provide renames for deprecated POSIX function names on the MSVC/Win32/Win64 platform. If needed
 * by other platforms, here's the place where you'd want to do that.
 * 
 * USE_ISO_NAMES: Selects whether to use the ISO-compliant names for system functions on MS platforms.
 *
 * Author: B. Scott Michel
 * "scooter me fecit"
 */
#if !defined(SIM_OS_RENAMES_H)

#if !defined(USE_ISO_NAMES)
/* Version identification as to when these ISO-compliant names showed up is an educated guess. */
#  if (defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN7)) || (defined(_MSC_VER) && (_MSC_VER >= 1900))
#    define USE_ISO_NAMES
#  endif
#endif /* USE_ISO_NAMES */

#if defined(USE_ISO_NAMES)
#define host_os_chdir _chdir
#define host_os_fileno _fileno
#define host_os_getpid _getpid
#define host_os_mkdir _mkdir
#define host_os_mktemp _mktemp
#define host_os_rmdir _rmdir
#define host_os_strcasecmp _stricmp
#define host_os_strcmpi _stricmp
#define host_os_strdup _strdup
#define host_os_strnicmp _strnicmp
#define host_os_unlink _unlink
#else
#define host_os_chdir chdir
#define host_os_fileno fileno
#define host_os_getpid getpid
#define host_os_mkdir mkdir
#define host_os_mktemp mktemp
#define host_os_rmdir rmdir
#define host_os_strcasecmp strcasecmp
#define host_os_strcmpi strcmpi
#define host_os_strdup strdup
#define host_os_strnicmp strnicmp
#define host_os_unlink unlink
#endif

#define SIM_OS_RENAMES_H
#endif /* SIM_OS_RENAMES_H */
