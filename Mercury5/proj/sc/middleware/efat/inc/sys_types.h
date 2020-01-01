#ifndef ONCE_ISO_SYS_TYPES_H
#define ONCE_ISO_SYS_TYPES_H
///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   sys_types.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_isoinfra.h>          /* Configuration header */
#define __need_size_t
#include <stddef.h>

#if defined(__GNUC__)&&defined(__i686__)
#define BLD_ISO_SSIZET_HEADER "sys/types.h"
#define BLD_ISO_FSTYPES_HEADER "sys/types.h"
#define BLD_ISO_SCHEDTYPES_HEADER "sys/types.h"
typedef long long ll_off_t;
#endif //defined(__GNUC__)&&defined(__i686__)

#ifdef BLD_ISO_SSIZET_HEADER
# include BLD_ISO_SSIZET_HEADER
#else
typedef long ssize_t;
#endif

#ifdef BLD_ISO_FSTYPES_HEADER
# include BLD_ISO_FSTYPES_HEADER
#else
typedef short dev_t;
typedef unsigned int ino_t;
typedef unsigned int mode_t;
typedef unsigned short nlink_t;
#ifndef ll_off_t
typedef long long ll_off_t;
#endif
#endif

#ifdef BLD_ISO_SCHEDTYPES_HEADER
# include BLD_ISO_SCHEDTYPES_HEADER
#else
typedef unsigned short gid_t;
typedef unsigned short uid_t;
typedef int pid_t;
#endif

#if INT_ISO_PMUTEXTYPES
# include BLD_ISO_PMUTEXTYPES_HEADER
#endif

#if INT_ISO_PTHREADTYPES
# include BLD_ISO_PTHREADTYPES_HEADER
#endif

/* Include <sys/select.h> for backward compatibility for now */
#define __NEED_FD_SETS_ONLY
#include <sys_select.h>
#undef __NEED_FD_SETS_ONLY

#if !defined(_POSIX_SOURCE)
# if INT_ISO_BSDTYPES
#  ifdef BLD_ISO_BSDTYPES_HEADER
#   include BLD_ISO_BSDTYPES_HEADER
#  endif
# endif
#endif // !defined(_POSIX_SOURCE)

#endif /* ONCE_ISO_SYS_TYPES_H multiple inclusion protection */

/* EOF sys/types.h */
