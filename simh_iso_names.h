#if !defined(SIMH_ISO_NAMES_H)

#  ifdef USE_ISO_C99_NAMES
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

#define SIMH_ISO_NAMES_H
#endif