#ifndef ONCE_ISO_DIRENT_H
#define ONCE_ISO_DIRENT_H
////////////////////////////////////////////////////////////////////////////////
///@file dirent.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


/* INCLUDES */

#include <pkgconf_system.h>
#include <pkgconf_isoinfra.h>
#include <sys_types.h>
#include <limits.h>
#include <fileio_dirent.h>
#ifdef __cplusplus
extern "C" {
#endif

#if INT_ISO_DIRENT
#ifdef BLD_ISO_DIRENT_HEADER
//# include BLD_ISO_DIRENT_HEADER
#include <error_errno.h>
#endif

/* PROTOTYPES */

extern DIR *opendir( const char *dirname );

extern DIR *wopendir( const utf16 *dirname );
#if defined(ENABLE_CHECK_DISK)
extern DIR *wopendir_ex( const utf16 *dirname );
#endif
extern struct dirent *readdir_t( DIR *dirp ,struct dirent *ent);  //Partial LS


extern struct dirent *readdir( DIR *dirp );

extern int readdir_r( DIR *dirp, struct dirent *entry, struct dirent **result );

extern void rewinddir( DIR *dirp );

extern int closedir( DIR *dirp );

#endif

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* ONCE_ISO_DIRENT_H multiple inclusion protection */

/* EOF dirent.h */
