#ifndef ONCE_FILEIO_DIRENT_H
#define ONCE_FILEIO_DIRENT_H
////////////////////////////////////////////////////////////////////////////////
///@file fileio_dirent.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_isoinfra.h>
#include <sys_types.h>
#include <limits.h>
#include <fileio_limits.h>

//======================================================================

#ifdef __cplusplus
extern "C" {
#endif

//======================================================================
// dirent structure.

#ifndef UTF16
#define UTF16 unsigned short
#endif


// mode uasgeb is as below....
// so file with bit 0 "zero" aand dir with bit 0 "1"
	//if(DENTRY_IS_DIR( &raw_dentry ))
    //{
    //	current_dir->mode = ( 0x1 |( DENTRY_IS_HIDDEN(&raw_dentry)<<1)|(DENTRY_IS_RDONLY(&raw_dentry)<<3)|(DENTRY_IS_SYSTEM(&raw_dentry)<<2)|(DENTRY_IS_VOLUME(&raw_dentry)<<2)|(DENTRY_IS_ARCHIVE(&raw_dentry)<<1 ));
    //}

struct dirent
{
    char        d_name[(EFAT_NAME_MAX+4)*sizeof(UTF16)];
    char        short_name[12+1];
    char        short_name_only;
    char        mode;   //bit 0:1 -->dir,1=file
    unsigned long   st_size;     /* File size (regular files only) */
    unsigned int    st_ctime;    /* Create time */
    unsigned int    st_mtime;    /* Last access time */
/* ++ Port V107MMP ++ */
    unsigned int    cluster;//bbbrian
/* -- Port V107MMP -- */

#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT
    unsigned long long fileid;
    unsigned char    attr;    /* attribute */    //Partial LS
#endif
};

//======================================================================
// DIR pointer object.
// move to pub
//typedef void *DIR;

//======================================================================

#ifdef __cplusplus
}   /* extern "C" */
#endif

//======================================================================
#endif /* ONCE_FILEIO_DIRENT_H multiple inclusion protection */
/* EOF dirent.h */
