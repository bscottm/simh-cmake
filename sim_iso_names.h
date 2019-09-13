/*
 *
 */

#if !defined(SIMH_ISO_NAMES_H)

#if defined(__MINGW__)
#define	NO_OLDNAMES
#endif

/* 0x0502 -> Windows Server 2003. This is apparently when the ISO names came into
 * existance. MinGW defines _WIN32_WINNT at this value. */
#  if defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0502
#    define simh_chdir  _chdir
#    define simh_unlink _unlink
#    define simh_mkdir  _mkdir
#    define simh_rmdir  _rmdir
#    define simh_fileno _fileno
#    define simh_getpid _getpid
#    define simh_getcwd _getcwd
#  else
#    define simh_chdir  chdir
#    define simh_unlink unlink
#    define simh_mkdir  mkdir
#    define simh_rmdir  rmdir
#    define simh_fileno fileno
#    define simh_getpid getpid
#    define simh_getcwd getcwd
#  endif

#  if defined(_WIN32)
#    define simh_putenv _putenv
#  elif defined(__hpux)
#    define simh_putenv putenv
#  endif

#define SIMH_ISO_NAMES_H
#endif
