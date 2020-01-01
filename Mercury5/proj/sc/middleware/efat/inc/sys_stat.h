#ifndef ONCE_ISO_STAT_H
#define ONCE_ISO_STAT_H
///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   sys_stat.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_isoinfra.h>          /* Configuration header */
#include <pkgconf_system.h>
#include <infra_type.h>       /* __externC */
#include <sys_types.h>

#if defined(__GNUC__)
#ifndef _TIME_T
#define _TIME_T
typedef signed long   time_t;
#endif
#else  //__GNUC__
#include <time.h>
#endif //__GNUC__

struct efat_stat {
    mode_t  st_mode;     /* File mode */
    ino_t   st_ino;      /* File serial number */
    dev_t   st_dev;      /* ID of device containing file */
    nlink_t st_nlink;    /* Number of hard links */
    uid_t   st_uid;      /* User ID of the file owner */
    gid_t   st_gid;      /* Group ID of the file's group */
    ll_off_t   st_size;     /* File size (regular files only) */
    time_t  st_atime;    /* Last access time */
    time_t  st_mtime;    /* Last data modification time */
    time_t  st_ctime;    /* Last file status change time */
#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT
    unsigned long long st_fileid;
#endif
};

#define S_IRUSR  (1<<16)
#define S_IWUSR  (1<<17)
#define S_IXUSR  (1<<18)
#define S_IRWXU  (S_IRUSR|S_IWUSR|S_IXUSR)

#define __stat_mode_DIR    (1<<0)
#define __stat_mode_CHR    (1<<1)
#define __stat_mode_BLK    (1<<2)
#define __stat_mode_REG    (1<<3)
#define __stat_mode_FIFO   (1<<4)
#define __stat_mode_MQ     (1<<5)
#define __stat_mode_SEM    (1<<6)
#define __stat_mode_SHM    (1<<7)
#define __stat_mode_LNK    (1<<8)
#define __stat_mode_SOCK   (1<<9)

/* PROTOTYPES */
__externC int mkdir(const char *path, mode_t mode);

__externC int stat( const char *path, struct efat_stat *buf );

__externC int fstat( int fd, struct efat_stat *buf );

#define S_IRGRP  (1<<19)
#define S_IWGRP  (1<<20)
#define S_IXGRP  (1<<21)
#define S_IRWXG  (S_IRGRP|S_IWGRP|S_IXGRP)



__externC int wmkdir(const utf16 *path, mode_t mode);

#define S_IROTH  (1<<22)
#define S_IWOTH  (1<<23)
#define S_IXOTH  (1<<24)
#define S_IRWXO  (S_IROTH|S_IWOTH|S_IXOTH)

__externC int wstat( const utf16 *path, struct efat_stat *buf );


#if !defined(_POSIX_C_SOURCE) || (_POSIX_C_SOURCE >= 200112L)
//is link?
#define S_ISLNK(__mode)  ((__mode) & __stat_mode_LNK )
//is sock?
#define S_ISSOCK(__mode)  ((__mode) & __stat_mode_SOCK )
#endif


//is dir?
#define S_ISDIR(__mode)  ((__mode) & __stat_mode_DIR )
//is chr?
#define S_ISCHR(__mode)  ((__mode) & __stat_mode_CHR )
//is blk?
#define S_ISBLK(__mode)  ((__mode) & __stat_mode_BLK )
//is reg?
#define S_ISREG(__mode)  ((__mode) & __stat_mode_REG )
//is info?
#define S_ISFIFO(__mode) ((__mode) & __stat_mode_FIFO )

//separate
#define S_TYPEISMQ(__buf)   ((__buf)->st_mode & __stat_mode_MQ )
//separate
#define S_TYPEISSEM(__buf)  ((__buf)->st_mode & __stat_mode_SEM )
//separate
#define S_TYPEISSHM(__buf)  ((__buf)->st_mode & __stat_mode_SHM )

#define S_ISUID  (1<<25)
#define S_ISGID  (1<<26)



#endif /* ONCE_ISO_STAT_H multiple inclusion protection */

/* EOF stat.h */
