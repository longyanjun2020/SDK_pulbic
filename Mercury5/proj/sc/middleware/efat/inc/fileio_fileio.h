#ifndef ONCE_FILEIO_H
#define ONCE_FILEIO_H
////////////////////////////////////////////////////////////////////////////////
///@file fileio_fileio.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_hal.h>
#include <pkgconf_io_fileio.h>
#include <pkgconf_fs_fat.h>
#include <infra_type.h>
#include <hal_hal_tables.h>
#include <hal_drv_api.h>
#include <sys_types.h>
#include <sys_stat.h>

#if defined(__SUPPORT_CHECKDISK__)
#if !defined(ENABLE_CHECK_DISK_RECOVER)
#define ENABLE_CHECK_DISK_RECOVER
#endif
#endif


//=============================================================================
// forward definitions

struct mtabEntry;
typedef struct mtabEntry mtabEntry;

struct  fstabEntry;
typedef struct  fstabEntry  fstabEntry;

struct FILEOPS_TAG;
typedef struct FILEOPS_TAG efat_fileops;

struct FILE_TAG;
typedef struct FILE_TAG efat_file;

struct IOVEC_TAG;
typedef struct IOVEC_TAG efat_iovec;

struct UIO_TAG;
typedef struct UIO_TAG efat_uio;

struct SELINFO_TAG;
typedef struct SELINFO_TAG efat_selinfo;

//=============================================================================
// Directory pointer

typedef EFAT_ADDRWORD efat_dir;

#define EFAT_DIR_NULL 0

//=============================================================================
// Filesystem table entry

typedef int     efat_fsop_mount    ( fstabEntry *fste, mtabEntry *mte );
typedef int     efat_fsop_umount   ( mtabEntry *mte , efat_uint8 force_umount);
typedef int     efat_fsop_open     ( mtabEntry *mte, efat_dir dir, const char *name, int mode,  efat_file *fte );
typedef int     efat_fsop_unlink   ( mtabEntry *mte, efat_dir dir, const char *name );
typedef int     efat_fsop_mkdir    ( mtabEntry *mte, efat_dir dir, const char *name );
typedef int     efat_fsop_rmdir    ( mtabEntry *mte, efat_dir dir, const char *name );
typedef int     efat_fsop_rename   ( mtabEntry *mte, efat_dir dir1, const char *name1, efat_dir dir2, const char *name2 );
typedef int     efat_fsop_link     ( mtabEntry *mte, efat_dir dir1, const char *name1, efat_dir dir2, const char *name2, int type );
typedef int     efat_fsop_opendir  ( mtabEntry *mte, efat_dir dir, const char *name, efat_file *fte );
typedef int     efat_fsop_chdir    ( mtabEntry *mte, efat_dir dir, const char *name, efat_dir *dir_out );
typedef int     efat_fsop_stat     ( mtabEntry *mte, efat_dir dir, const char *name, struct efat_stat *buf);
typedef int     efat_fsop_getinfo  ( mtabEntry *mte, efat_dir dir, const char *name, int key, void *buf, int len );
typedef int     efat_fsop_setinfo  ( mtabEntry *mte, efat_dir dir, const char *name, int key, void *buf, int len );

typedef int     efat_fsop_wopen    ( mtabEntry *mte, efat_dir dir, const utf16 *wname, int mode,  efat_file *fte );
typedef int     efat_fsop_wunlink  ( mtabEntry *mte, efat_dir dir, const utf16 *name );
typedef int     efat_fsop_wmkdir   ( mtabEntry *mte, efat_dir dir, const utf16 *name );
typedef int     efat_fsop_wrmdir   ( mtabEntry *mte, efat_dir dir, const utf16 *name );
typedef int     efat_fsop_wrename  ( mtabEntry *mte, efat_dir dir1, const utf16 *name1, efat_dir dir2, const utf16 *name2 );
typedef int     efat_fsop_wlink    ( mtabEntry *mte, efat_dir dir1, const utf16 *name1, efat_dir dir2, const utf16 *name2, int type );
typedef int     efat_fsop_wopendir ( mtabEntry *mte, efat_dir dir, const utf16 *name, efat_file *fte );
typedef int     efat_fsop_wchdir   ( mtabEntry *mte, efat_dir dir, const utf16 *name, efat_dir *dir_out );
typedef int     efat_fsop_wstat    ( mtabEntry *mte, efat_dir dir, const utf16 *name, struct efat_stat *buf);
typedef int     efat_fsop_wgetinfo ( mtabEntry *mte, efat_dir dir, const utf16 *name, int key, void *buf, int len );
typedef int     efat_fsop_wsetinfo ( mtabEntry *mte, efat_dir dir, const utf16 *name, int key, void *buf, int len );


struct fstabEntry
{
    const char          *name;          // filesystem name
    EFAT_ADDRWORD        data;           // private data value
    efat_uint32          syncmode;       // synchronization mode

    efat_fsop_mount      *mount;
    efat_fsop_umount     *umount;
    efat_fsop_open       *open;
    efat_fsop_unlink     *unlink;
    efat_fsop_mkdir      *mkdir;
    efat_fsop_rmdir      *rmdir;
    efat_fsop_rename     *rename;
    efat_fsop_link       *link;
    efat_fsop_opendir    *opendir;
    efat_fsop_chdir      *chdir;
    efat_fsop_stat       *stat;
    efat_fsop_getinfo    *getinfo;
    efat_fsop_setinfo    *setinfo;

    efat_fsop_wopen      *wopen;
    efat_fsop_wunlink    *wunlink;
    efat_fsop_wmkdir     *wmkdir;
    efat_fsop_wrmdir     *wrmdir;
    efat_fsop_wrename    *wrename;
    efat_fsop_wlink      *wlink;
    efat_fsop_wopendir   *wopendir;
    efat_fsop_wchdir     *wchdir;
    efat_fsop_wstat      *wstat;
    efat_fsop_wgetinfo   *wgetinfo;
    efat_fsop_wsetinfo   *wsetinfo;

};// EFAT_HAL_TABLE_TYPE;

//-----------------------------------------------------------------------------
// Keys for getinfo() and setinfo()

#define FS_INFO_CONF            1       // pathconf() 
#define FS_INFO_ACCESS          2       // access() 
#define FS_INFO_GETCWD          3       // getcwd() 
#define FS_INFO_SYNC            4       // sync() 
#define FS_INFO_ATTRIB          5       // efat_fs_(get|set)_attrib() 
#define FS_INFO_BLOCK_USAGE     6 		// get the disk usage information 
#define FS_INFO_DISK_CHANGE     7 		// get the disk change information 
#define FS_INFO_FREE_CAPACITY_RESET 8   // reset free cluster 
// ++ Port V107MMP ++ 
#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT
#define FS_INFO_FILEID          9       // get dir entry from fileid 
#endif
#define FS_INFO_CLUSTERSIZE     10 	// get the disk cluster size 
#if defined(ENABLE_CHECK_DISK)
#define FS_FAT_COMPARE          11
#define FS_INVALIDATE_FSCACHE   12
#define FS_INFO_NEXT_ENTRY      13
#define FS_INFO_ENTRY_TYPE      14
#define FS_CHECKFAT1            15
#define FS_CHECKDISK            16
#define FS_INFO_FAT             17 	/* get the disk cluster size */
#define FS_INFO_FILE_SIZE       18
#define FS_INFO_DISK_DIRTY      19
#define FS_INFO_DISK_WRITE      21
#define FS_INFO_DISK_READ       22
#define FS_DISABLE_FAT2         24
#endif
#define FS_INFO_FREE_POOL       25
#define FS_INFO_RESCAN_POOL     26
#define FS_INFO_LIVE_NODE_CNT   27
#define FS_DELETE_PAUSE         28
#define FS_INFO_STORAGE_FLUSH   29
#define FS_INFO_STORAGE_INFO    30
#define FS_INFO_DEVICE_STATUS    31
#define FS_INFO_DIRTYDISK_STATUS    32
// -- Port V107MMP -- 
//-----------------------------------------------------------------------------
// Types for link()

#define EFAT_FSLINK_HARD         1       // form a hard link 
#define EFAT_FSLINK_SOFT         2       // form a soft link 
#define EFAT_FS_FILECOMBINATION  3       /* combine 2 file   */


#if defined(ENABLE_CHECK_DISK)
//-----------------------------------------------------------------------------
// Types for entry_types
#define ENTRY_REGULAR       0//TENTRY_REGULAR   Used when entry points to next file cluster
#define ENTRY_FREE          1//TENTRY_FREE      Free cluster    
#define ENTRY_LAST          2//TENTRY_LAST      Last cluster of file
#define ENTRY_RESERVED      3//TENTRY_RESERVED  Reserved cluster
#define ENTRY_BAD           4//TENTRY_BAD       Bad cluster
#endif        
//-----------------------------------------------------------------------------
// getinfo() and setinfo() buffers structures.

struct efat_fs_block_usage
{
	efat_uint32 total_blocks;
    efat_uint32 free_blocks;
    efat_uint32 block_size;
    efat_bool   bResetChangeFlag;
    efat_bool   bStatus;
};
#if defined(ENABLE_CHECK_DISK)
struct efat_fs_entryinfo 
{
	efat_uint32 cluster; 
	efat_uint32 next_cluster;
	efat_uint32 bytes_per_cluster;
	efat_int32  entry_types;
	efat_uint32 entry_size;
	efat_uint32 end_cluster;
};
struct efat_fs_disk_access
{
	efat_uint32 start_pos;
	efat_uint32 len;
	efat_uint32 buf_addr;
};
struct efat_fs_fatinfo
{
	efat_uint32 bytes_per_tbl; 
	efat_uint32 fat2_start_pos;
	efat_uint32 cluster_size;	
};
struct efat_fs_fatchk
{
	efat_uint32 start_cluster; 
	efat_uint32 cluster_cnt; 
	efat_uint32 buf_addr;
	efat_uint32 buf_len;
};
struct efat_fs_fat2cache
{
    efat_bool   fgfat2_dis;
    efat_uint32 u32buf_addr;
    efat_uint32 u32buf_len;
    efat_uint32 u32block_size;
};
#endif        
struct efat_getcwd_info
{
    char        *buf;           // buffer for cwd string 
    size_t      size;           // size of buffer 
};

typedef efat_uint32 efat_fs_attrib_t;

//-----------------------------------------------------------------------------
// Macro to define an initialized fstab entry

__externC int efat_fsop_no_wopen    ( mtabEntry *mte, efat_dir dir, const utf16 *wname, int mode,  efat_file *fte );
__externC int efat_fsop_no_wunlink  ( mtabEntry *mte, efat_dir dir, const utf16 *name );
__externC int efat_fsop_no_wmkdir   ( mtabEntry *mte, efat_dir dir, const utf16 *name );
__externC int efat_fsop_no_wrmdir   ( mtabEntry *mte, efat_dir dir, const utf16 *name );
__externC int efat_fsop_no_wrename  ( mtabEntry *mte, efat_dir dir1, const utf16 *name1, efat_dir dir2, const utf16 *name2 );
__externC int efat_fsop_no_wlink    ( mtabEntry *mte, efat_dir dir1, const utf16 *name1, efat_dir dir2, const utf16 *name2, int type );
__externC int efat_fsop_no_wopendir ( mtabEntry *mte, efat_dir dir, const utf16 *name, efat_file *fte );
__externC int efat_fsop_no_wchdir   ( mtabEntry *mte, efat_dir dir, const utf16 *name, efat_dir *dir_out );
__externC int efat_fsop_no_wstat    ( mtabEntry *mte, efat_dir dir, const utf16 *name, struct efat_stat *buf);
__externC int efat_fsop_no_wgetinfo ( mtabEntry *mte, efat_dir dir, const utf16 *name, int key, void *buf, int len );
__externC int efat_fsop_no_wsetinfo ( mtabEntry *mte, efat_dir dir, const utf16 *name, int key, void *buf, int len );

#define FSOP_WCHAR_UNSUPPORT \
    efat_fsop_no_wopen    ,   \
    efat_fsop_no_wunlink  ,   \
    efat_fsop_no_wmkdir   ,   \
    efat_fsop_no_wrmdir   ,   \
    efat_fsop_no_wrename  ,   \
    efat_fsop_no_wlink    ,   \
    efat_fsop_no_wopendir ,   \
    efat_fsop_no_wchdir   ,   \
    efat_fsop_no_wstat    ,   \
    efat_fsop_no_wgetinfo ,   \
    efat_fsop_no_wsetinfo

// File system that does not support wide character functions
#define FSTAB_ENTRY( _l, _name, _data, _syncmode, _mount, _umount,      \
                     _open, _unlink,  _mkdir, _rmdir, _rename, _link,   \
                     _opendir, _chdir, _stat, _getinfo, _setinfo )      \
struct fstabEntry _l EFAT_HAL_TABLE_ENTRY(fstab) =                  \
{                                                                       \
    _name,                                                              \
    _data,                                                              \
    _syncmode,                                                          \
    _mount,                                                             \
    _umount,                                                            \
    _open,                                                              \
    _unlink,                                                            \
    _mkdir,                                                             \
    _rmdir,                                                             \
    _rename,                                                            \
    _link,                                                              \
    _opendir,                                                           \
    _chdir,                                                             \
    _stat,                                                              \
    _getinfo,                                                           \
    _setinfo,                                                           \
    FSOP_WCHAR_UNSUPPORT                                                \
};

// File system that support wide character functions
#define FSTAB_WENTRY( _l, _name, _data, _syncmode, _mount, _umount,          \
                      _open, _unlink,  _mkdir, _rmdir, _rename, _link,       \
                      _opendir, _chdir, _stat, _getinfo, _setinfo,           \
                      _wopen, _wunlink,  _wmkdir, _wrmdir, _wrename, _wlink, \
                      _wopendir, _wchdir, _wstat, _wgetinfo, _wsetinfo )     \
struct fstabEntry _l EFAT_HAL_TABLE_ENTRY(fstab) =                       \
{                                                                            \
    _name,                                                                   \
    _data,                                                                   \
    _syncmode,                                                               \
    _mount,                                                                  \
    _umount,                                                                 \
    _open,                                                                   \
    _unlink,                                                                 \
    _mkdir,                                                                  \
    _rmdir,                                                                  \
    _rename,                                                                 \
    _link,                                                                   \
    _opendir,                                                                \
    _chdir,                                                                  \
    _stat,                                                                   \
    _getinfo,                                                                \
    _setinfo,                                                                \
    _wopen,                                                                  \
    _wunlink,                                                                \
    _wmkdir,                                                                 \
    _wrmdir,                                                                 \
    _wrename,                                                                \
    _wlink,                                                                  \
    _wopendir,                                                               \
    _wchdir,                                                                 \
    _wstat,                                                                  \
    _wgetinfo,                                                               \
    _wsetinfo                                                                \
};



//=============================================================================
// Mount table entry

struct mtabEntry
{
    const char          *name;          // name of mount point
    const char          *aliasname;     // alias name of mount point
    const char          *fsname;        // name of implementing filesystem
    const char          *devname;       // name of hardware device
    EFAT_ADDRWORD        data;           // private data value

    // The following are filled in after a successful mount operation
    efat_bool            valid;          // Valid entry?
    fstabEntry     *fs;            // pointer to fstab entry
    efat_dir             root;           // root directory pointer
    efat_int8             id;
    efat_int32            refcnt;  //refernce count
    efat_int32            accmode;          //access mode
};// EFAT_HAL_TABLE_TYPE;


// This macro defines an initialized mtab entry

#define MTAB_ENTRY( _l, _name, _fsname, _devname, _data )       \
struct mtabEntry _l EFAT_HAL_TABLE_ENTRY(mtab) =            \
{                                                               \
    _name,                                                      \
    _fsname,                                                    \
    _devname,                                                   \
    _data,                                                      \
    false,                                                      \
    NULL,                                                       \
    EFAT_DIR_NULL                                                \
};

//=============================================================================
// IO vector descriptors

struct IOVEC_TAG
{
    void           *iov_base;           // Base address.
    ssize_t        iov_len;             // Length. 
};

enum efat_uio_rw 
{ 
    UIO_READ,
    UIO_WRITE 
};

// Segment flag values. 
enum efat_uio_seg
{
    UIO_USERSPACE,		        // from user data space 
    UIO_SYSSPACE		        // from system space 
};

// Limits
#define UIO_SMALLIOV	8		// 8 on stack, else malloc 

struct UIO_TAG
{
    struct IOVEC_TAG *uio_iov;	// pointer to array of iovecs 
    int	                 uio_iovcnt;	// number of iovecs in array 
    ssize_t     	 uio_resid;	// residual i/o count 
    ll_off_t       	 uio_offset;	// offset into file this uio corresponds to 
    enum efat_uio_seg     uio_segflg;    // see above 
    enum efat_uio_rw      uio_rw;        // see above 
};



//=============================================================================
// Description of open file

typedef int efat_fileop_readwrite (struct FILE_TAG *fp, struct UIO_TAG *uio);
typedef efat_fileop_readwrite efat_fileop_read;
typedef efat_fileop_readwrite efat_fileop_write;
typedef int efat_fileop_lseek   (struct FILE_TAG *fp, ll_off_t *pos, int whence );
typedef int efat_fileop_ioctl   (struct FILE_TAG *fp, EFAT_ADDRWORD com, EFAT_ADDRWORD data);
typedef efat_bool efat_fileop_select  (struct FILE_TAG *fp, int which, EFAT_ADDRWORD info);
typedef int efat_fileop_fsync   (struct FILE_TAG *fp, int mode );
typedef int efat_fileop_close   (struct FILE_TAG *fp);
typedef int efat_fileop_fstat   (struct FILE_TAG *fp, struct efat_stat *buf );
typedef int efat_fileop_getinfo (struct FILE_TAG *fp, int key, void *buf, int len );
typedef int efat_fileop_setinfo (struct FILE_TAG *fp, int key, void *buf, int len );
typedef int efat_fileop_trunc   (struct FILE_TAG *fp, efat_uint32 size );

struct FILEOPS_TAG
{
    efat_fileop_read     *fo_read;
    efat_fileop_write    *fo_write;
    efat_fileop_lseek    *fo_lseek;
    efat_fileop_ioctl    *fo_ioctl;
    efat_fileop_select   *fo_select;
    efat_fileop_fsync    *fo_fsync;
    efat_fileop_close    *fo_close;
    efat_fileop_fstat    *fo_fstat;
    efat_fileop_getinfo  *fo_getinfo;
    efat_fileop_setinfo  *fo_setinfo;
    efat_fileop_trunc    *fo_trunc;
};

#if defined(EFAT_FS_FAT_USE_CLUSTER_CHAIN)
typedef struct CLUSTER_LIST
{
    efat_uint32  start_cluster;
    efat_uint32  cont_num_cluster;
    efat_uint32  cont_num_cluster_withskip;
}cluster_list;
#if defined(EFAT_DYNAMIC_MEMORY_MODE_CC)
#ifndef USE_GENERAL_FCC
extern efat_uint32 fragment_num;
extern efat_uint32 start_addr;
extern efat_uint32 fragment_size;
#endif
#endif
#endif

#ifdef USE_GENERAL_FCC
#define NUM_FS_FAT_FRAGMENT_NUM 2
#endif

struct FILE_TAG
{
    efat_uint32	                f_flag;		// file state                   
    efat_uint16                  f_ucount;       // use count                    
    efat_uint16                  f_type;		// descriptor type              
    efat_uint32                  f_syncmode;     // synchronization protocol     
    struct FILEOPS_TAG      *f_ops;         // file operations              
    ll_off_t       	        f_offset;       // current offset               
    EFAT_ADDRWORD	        f_data;		// file or socket               
    EFAT_ADDRWORD                f_xops;         // extra type specific ops      
    mtabEntry              *f_mte;         // mount table entry            
#if defined(EFAT_FS_FAT_USE_CLUSTER_CHAIN)
#if defined(CFG_NORMAL_MODE_CC)
    cluster_list                clist[NUM_FS_FAT_FRAGMENT_NUM];
#else
    cluster_list                *clist;
#ifdef USE_GENERAL_FCC
        cluster_list                clist_t[NUM_FS_FAT_FRAGMENT_NUM];
        efat_uint32                 fragment_num;
#endif
#endif
    efat_uint32                  total_file_fragment;
    efat_uint32                  total_cluster;
    efat_uint8                   clist_check;
    efat_uint8                   end;
    efat_uint8                   need_init;
    ll_off_t                       last_updatesize;
#endif
};

//-----------------------------------------------------------------------------
// Type of file

#define	EFAT_TYPE_FILE      1	// file 
#define	EFAT_TYPE_SOCKET	2	// communications endpoint 
#define	EFAT_TYPE_DEVICE	3	// device 
#define	EFAT_TYPE_DIR       4	// dir 


//-----------------------------------------------------------------------------
#define EFAT_FREAD       EFAT_O_RDONLY
#define EFAT_FWRITE      EFAT_O_WRONLY
#define EFAT_FNONBLOCK   EFAT_O_NONBLOCK
#define EFAT_FAPPEND     EFAT_O_APPEND

#define EFAT_FASYNC      0x00010000
#define EFAT_FDIR        0x00020000
#define EFAT_FLOCKED     0x01000000
#define EFAT_FLOCK       0x02000000
#define EFAT_FALLOC      0x80000000

// Mask for open mode bits stored in file object
#define efat_file_MODE_MASK (EFAT_FREAD|        \
                             EFAT_FWRITE|       \
                             EFAT_FNONBLOCK|    \
                             EFAT_FAPPEND)

//-----------------------------------------------------------------------------
// Keys for getinfo() and setinfo()
// fpathconf() 

#define FILE_INFO_CONF          1       


//-----------------------------------------------------------------------------
// Modes for fsync()

#define EFAT_FSYNC              1
#define EFAT_FDATASYNC          2

//-----------------------------------------------------------------------------
// Get/set info buffer structures

// This is used for pathconf() and fpathconf()
struct efat_pathconf_info
{
    int         name;           // POSIX defined variable name
    long        value;          // Returned variable value
};

//=============================================================================

#define SYNCMODE_NONE               0   
// no locking required
#define SYNCMODE_FILE_FILESYSTEM    0x0002  
// lock fs during file ops
#define SYNCMODE_FILE_MOUNTPOINT    0x0004  
// lock mte during file ops
#define SYNCMODE_IO_FILE            0x0010  
// lock file during io ops
#define SYNCMODE_IO_FILESYSTEM      0x0020  
// lock fs during io ops
#define SYNCMODE_IO_MOUNTPOINT      0x0040  
// lock mte during io ops
#define SYNCMODE_SOCK_FILE          0x0100  
// lock socket during socket ops
#define SYNCMODE_SOCK_NETSTACK      0x0800  
// lock netstack during socket ops
#define SYNCMODE_IO_SHIFT           4    
// shift for IO to file bits
#define SYNCMODE_SOCK_SHIFT         8    
// shift for sock to file bits

// Return mutex used for serializing the filesystem
#if 1
__externC efat_drv_mutex_t *efat_fs_get_lock( fstabEntry *fste, mtabEntry *mte );
#endif
//=============================================================================
// Mount and umount functions

__externC int mount( const char *devname, const char *dir, const char *fsname);
__externC int mount_ex( const char *devname, const char *dir, const char *fsname);

__externC int umount( const char *name, unsigned char force_umount);
__externC int umount_ex( const char *name, unsigned char force_umount);

//=============================================================================
// Get/Set info functions

__externC int efat_fs_getinfo( const char *path, int key, void *buf, int len );
__externC int efat_fs_setinfo( const char *path, int key, void *buf, int len );
__externC int efat_fs_fgetinfo( int fd, int key, void *buf, int len );
__externC int efat_fs_fsetinfo( int fd, int key, void *buf, int len );
__externC int efat_fs_wgetinfo( const utf16 *path, int key, void *buf, int len );
__externC int efat_fs_wsetinfo( const utf16 *path, int key, void *buf, int len );
#if defined(ENABLE_CHECK_DISK)
#if defined(ENABLE_CHECK_DISK)
__externC int efat_fs_wgetinfo_ex( const utf16 *path, int key, void *buf, int len );
#endif
__externC int efat_fs_wsetinfo_ex( const utf16 *path, int key, void *buf, int len );
#endif        

__externC int efat_fs_checkeof( int fd );
//=============================================================================
// Select support

struct SELINFO_TAG
{
    EFAT_ADDRWORD        si_info;        // info passed through from fo_select()
    EFAT_ADDRESS         si_thread;      // selecting thread pointer
};

//-----------------------------------------------------------------------------
// Select support functions.

__externC void efat_selinit( struct SELINFO_TAG *sip );
__externC void efat_selrecord( EFAT_ADDRWORD info, struct SELINFO_TAG *sip );
__externC void efat_selwakeup( struct SELINFO_TAG *sip );

//=============================================================================
// Miscellaneous functions.

// Provide a function to synchronize an individual file system. (ie write file and directory information to disk)
__externC int efat_fs_fssync(const char *path);
// Functions to set and get attributes of a file, eg FAT attributes like hidden and system.
__externC int efat_fs_get_attrib( const char *fname, efat_fs_attrib_t * const file_attrib );
__externC int efat_fs_set_attrib( const char *fname, const efat_fs_attrib_t new_attrib );

// Functions to lock and unlock a filesystem. These are normally used internally by the fileio layer, but the file system might need to
// use them when it needs to lock itself, eg when performing garbage collect.
__externC void efat_fs_unlock( mtabEntry *mte, efat_uint32 syncmode );
__externC void efat_fs_lock( mtabEntry *mte, efat_uint32 syncmode );


// To be able to lock the filesystem you need the mte. This function allows the table of mounted filesystems to be searched to find an
// mte which uses the give filesystem root.
__externC mtabEntry * efat_fs_root_lookup( efat_dir *root );


__externC void * efat_fd2name(int fd);


//=============================================================================
// Default functions.

__externC int efat_fileio_enosys(void);
__externC int efat_fileio_erofs(void);
__externC int efat_fileio_enoerr(void);
__externC int efat_fileio_enotdir(void);
__externC efat_fileop_select efat_fileio_seltrue;



#if defined(ENABLE_CHECK_DISK)
//=============================================================================
// Default functions.
// Cast to the appropriate type, these functions can be put into any of
// the operation table slots to provide the defined error code.
__externC void efat_LockDevice(const char *devname, efat_bool bLockState);
#endif        

//-----------------------------------------------------------------------------
#endif // ifndef ONCE_FILEIO_H
// End of fileio.h
