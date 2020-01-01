#ifndef ONCE_FATFS_FATFS_H
#define ONCE_FATFS_FATFS_H
////////////////////////////////////////////////////////////////////////////////
///@file fatfs.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////
#include <pkgconf_system.h>
#include <pkgconf_fs_fat.h>
#include <infra_type.h>
#include <io_io.h>
#include <fileio_fileio.h>
#include <efat_tree.h>
#include <efat_list.h>
#include <sys_types.h>
#include <sys_stat.h>
#include <dirent.h>
#include <fileio_fileio.h>
#include "sys_sys_isw_cli.h"
#include <string.h>
//for RTK
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_traces.ho"
#include "cus_os.hc"
#include "sys_MsWrapper_cus_os_msg.h"
#include "hal_drv_api.h"
#include "newLS.h"

#define efat_dialog(fmt, args...)  //_TRACE((EFAT_DBG26, fmt, ##args))

#ifdef USE_RTK_CV
#define pthread_t                efat_thread
#define sem_t                    efat_sem_t
#define sem_init(a, b, c)       MsInitSem(a,c)//efat_semaphore_init(a, c)
#define sem_post                MsProduceSem//efat_semaphore_post
#define sem_wait                MsConsumeSem //efat_semaphore_wait
#define sem_destroy              efat_semaphore_destroy
#define pthread_create           efat_thread_create
#endif

/* ++ Port V107MMP ++ */
// undefine semaphore for test
#define efat_semaphore_init(a, b)       MsInitSem(*a, b)
#define efat_semaphore_wait(a)          MsConsumeSem(*a)
#define efat_semaphore_post(a)          MsProduceSem(*a)
/* -- Port V107MMP -- */
#define efat_thread_create           //MsCreateTask
#define efat_thread_resume           MsStartTask
#define efat_current_time            MsGetOsTick
#define efat_mutex_init(x)           MsInitSem(*x, 1)
#define efat_mutex_lock(x)           MsConsumeSem(*x)
#define efat_mutex_unlock(x)         MsProduceSem(*x)
#define efat_current_time            MsGetOsTick
#define efat_thread_delay            MsSleep
#define efat_thread_yield            MsSleep
#define efat_cond_init               rtk_cond_init2
#define efat_cond_wait               rtk_cond_wait2
#define efat_cond_broadcast          rtk_cond_broadcast2

//code size reduce
//#define ENABLE_FAST_ALLOCATE_MODE
//#define MERGE_FS_FUNCTIONS


#define printf    //UartSendTrace

#define EFAT_DBG26      _CUS1|LEVEL_26
#define EFAT_DBG27      _CUS1|LEVEL_27


/* constants for lseek */
#ifndef SEEK_SET
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2


#endif
#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT
#define SEEK_ID	3
#endif

/* File access modes used for open() and fnctl() */
#define EFAT_O_RDONLY     (1<<0)   /* Open for reading only */
#define EFAT_O_WRONLY     (1<<1)   /* Open for writing only */
#define EFAT_O_RDWR       (EFAT_O_RDONLY|EFAT_O_WRONLY) /* Open for reading and writing */
/* File access mode mask */
#define EFAT_O_ACCMODE    (EFAT_O_RDONLY|EFAT_O_RDWR|EFAT_O_WRONLY)
/* open() mode flags */
#define EFAT_O_CREAT      (1<<3)    /* Create file if it does not exist */
#define EFAT_O_EXCL       (1<<4)    /* Exclusive use */
#define EFAT_O_NOCTTY     (1<<5)    /* Do not assign a controlling terminal */
#define EFAT_O_TRUNC      (1<<6)    /* Truncate */
/* File status flags used for open() and fcntl() */
#define EFAT_O_APPEND     (1<<7)    /* Set append mode */
#define EFAT_O_DSYNC      (1<<8)    /* Synchronized I/O data integrity writes */
#define EFAT_O_NONBLOCK   (1<<9)    /* No delay */
#define EFAT_O_RSYNC      (1<<10)   /* Synchronized read I/O */
#define EFAT_O_SYNC       (1<<11)   /* Synchronized I/O file integrity writes */
// Peter Test for exist mode
#define EFAT_O_EXIST      (1<<24)   /* Synchronized I/O file integrity writes */

#define O_FAST_BLOCKALIGN (1<<12)	/* Bits 12~15 is for FAST MODE */
#define O_FAST_512K       (1<<13)   	/* Fast Access Mode with 0.5 MB */
#define O_FAST_1M         (2<<13)   	/* Fast Access Mode with 1 MB */
#define O_FAST_2M         (3<<13)   	/* Fast Access Mode with 2 MB */
#define O_FAST_4M         (4<<13)   	/* Fast Access Mode with 4 MB */
#if defined(FS_FAT_MERGE_CONTINUOUS_CLUSTERS)
#define O_CCW          (1<<16)   	/* Fast write mode for continuous clusters */
#define O_CCR          (1<<23)   	/* Fast write mode for continuous clusters */
#endif
#if defined(EFAT_DYNAMIC_MEMORY_MODE_CC)
#define O_FCC          (1<<17)      /* file cluster chain */
#endif
#define O_FAST_MODE  (O_FAST_512K | O_FAST_1M | O_FAST_2M | O_FAST_4M)   /* Fast Access Mode */
#define O_ALLOC_MODE_SHIFT 	18
#define O_ALLOC_1M         	(1<<O_ALLOC_MODE_SHIFT)   	/* Alloc 1 MB */
#define O_ALLOC_2M         	(2<<O_ALLOC_MODE_SHIFT)   	/* Alloc 2 MB */
#define O_ALLOC_4M         	(3<<O_ALLOC_MODE_SHIFT)   	/* Alloc 4 MB */
#define O_ALLOC_8M         	(4<<O_ALLOC_MODE_SHIFT)   	/* Alloc 8 MB */
#define O_ALLOC_16M        	(5<<O_ALLOC_MODE_SHIFT)   	/* Alloc 16 MB */
#define O_ALLOC_32M        	(6<<O_ALLOC_MODE_SHIFT)   	/* Alloc 32 MB */
#define O_ALLOC_MODE  (O_ALLOC_1M | O_ALLOC_2M | O_ALLOC_4M| O_ALLOC_8M| O_ALLOC_16M| O_ALLOC_32M)   /* ALLOC Mode */
// FAT filesystem dir entry attributes

#define S_FATFS_RDONLY  (0x01) // Read only
#define S_FATFS_HIDDEN  (0x02) // Hidden
#define S_FATFS_SYSTEM  (0x04) // System
#define S_FATFS_VOLUME  (0x08) // Volume label
#define S_FATFS_DIR     (0x10) // Subdirectory
#define S_FATFS_ARCHIVE (0x20) // Needs archiving

// Mode bits which are allowed to be changed by attrib
#define S_FATFS_ATTRIB   (S_FATFS_RDONLY | S_FATFS_HIDDEN | S_FATFS_SYSTEM | \
                          S_FATFS_ARCHIVE)

// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
// FAT table entries types

#define TENTRY_REGULAR  0 // Used when entry points to next file cluster
#define TENTRY_FREE     1 // Free cluster
#define TENTRY_LAST     2 // Last cluster of file
#define TENTRY_RESERVED 3 // Reserved cluster
#define TENTRY_BAD      4 // Bad cluster

// mode FAT dir entry attributes macros

#define S_FATFS_ISRDONLY(__mode)  ((__mode) & S_FATFS_RDONLY)
#define S_FATFS_ISHIDDEN(__mode)  ((__mode) & S_FATFS_HIDDEN)
#define S_FATFS_ISSYSTEM(__mode)  ((__mode) & S_FATFS_SYSTEM)
#define S_FATFS_ISVOLUME(__mode)  ((__mode) & S_FATFS_VOLUME)
#define S_FATFS_ISDIR(__mode)     ((__mode) & S_FATFS_DIR)
#define S_FATFS_ISARCHIVE(__mode) ((__mode) & S_FATFS_ARCHIVE)

// -------------------------------------------------------------------------
//Compatibility with windows
//Support Resver Bit
#define S_FATFS_LOWCASE_EXTNAME    (0x10) //the extname is low case
#define S_FATFS_LOWCASE_FILENAME   (0x8)  //the file tname is low case

#define S_FATFS_ISLOWCASEEXTNAME(__rsv) (((__rsv))&S_FATFS_LOWCASE_EXTNAME)
#define S_FATFS_ISLOWCASEFILENAME(__rsv)(((__rsv))&S_FATFS_LOWCASE_FILENAME)



#if defined(FS_FAT_MERGE_CONTINUOUS_CLUSTERS)
typedef struct fatfs_rbffer
{
    efat_uint32 sector;          // start sector
    efat_uint32 sector_snum;     // the numer of toal sector
    efat_uint32 rbuffer_index;   // Position inside buffer
    efat_uint32 rbuffer_datalen; // size of buffer
    efat_uint32 rbuffer_size;    // data size
    efat_uint32 remnant_size;
    efat_int32  rbuffer_status;
    efat_uint8 * data;
} fatfs_rbffer;


extern fatfs_rbffer rbuffer[1];
#endif


#ifndef O_UNICODE
#define O_UNICODE         (1u <<31)
#endif

#define SEEK_EARSE_CLUSER_CL    (1u <<15)

//#define FATFS_MERGE_CONTINUOUS_CLUSTERS     1
#define FOR_MMI_REQUIRE 1



/* for FAT_COPY_BUFER in SRAM case */
#define SRAM_BSS    //__attribute__((section(".bss_sram")))
#if defined(HWR_HAL_MIPS_MSTAR_SDRAM_ENABLE)
#define SDRAM_FSBUF     //__attribute__((section(".fsbuf_sdram")))
/*It is temporary solution for M2's FileSystem to use SDRAM*/
#endif

//align to cache line (16 bytes)
#if defined(HWR_HAL_MIPS_MSTAR_PLATFORM_MONTAGE3)
#include <hal_var_cache.h>
#define ALIGN_CACHE_LINE(_x_) (((_x_) + (ARM_DCACHE_LINE_SIZE-1)) & ~(ARM_DCACHE_LINE_SIZE-1))
#endif


#if defined(HWR_HAL_MIPS_MSTAR_PLATFORM_MONTAGE3)
#define ALIGN_(p) ALIGN_CACHE_LINE(p)
#else
// Add at least one list header size.
#define ALIGNBYTES      (ARC_ALIGNMENT - 1)
#define ALIGN_(p)        (((unsigned)(p) + ALIGNBYTES) &~ ALIGNBYTES)
#endif
#define CACHE_BLOCK_SIZE     (4096)
#define CACHE_BLOCK_SIZE_TAB (4096)
#define CACHE_BLOCK_SIZE_DIR (4096)



#if defined(HWR_HAL_MIPS_MSTAR_PLATFORM_MONTAGE3)
//extern unsigned int FAT_COPY_BUFER[4][1024];
#endif
// --------------------------------------------------------------------------

#define FATFS_HASH_TABLE_SIZE NUM_FS_FAT_NODE_HASH_TABLE_SIZE

#define FATFS_NODE_POOL_SIZE  NUM_FS_FAT_NODE_POOL_SIZE

#ifdef DBG_FS_FAT_NODE_CACHE_EXTRA_CHECKS
# define FATFS_NODE_CACHE_EXTRA_CHECKS 1
#endif

#ifdef CFG_FS_FAT_LONG_FILE_NAMES
#define FAT_FILE_NAME_MAX   (NUM_FS_FAT_LONG_FILE_NAME_MAX+1)
#else
#define FAT_FILE_NAME_MAX   13
#endif



#if defined(FS_FAT_MERGE_CONTINUOUS_CLUSTERS)
#define BUF0_SIZE           (rbuffer[0].rbuffer_datalen)
#define BUF0_DATA_SIZE      (rbuffer[0].rbuffer_size)
#define BUF0_START_SECTOR   (rbuffer[0].sector)
#define BUF0_SECTOR_LEN     (rbuffer[0].sector_snum)
#define BUF0_INDEX          (rbuffer[0].rbuffer_index)
#define BUF0_REMNANT_SIZE   (rbuffer[0].remnant_size)
#define BUF0_DATA           (rbuffer[0].data)
#define BUF0_END_SECTOR     (BUF0_START_SECTOR + BUF0_SECTOR_LEN)
#define BUF0_OFFSET         (BUF0_DATA + BUF0_INDEX)
#define BUF0_STATUS         (rbuffer[0].rbuffer_status)
#endif

extern int efat_errno;
extern efat_uint8 gu8_chk_croslnk;
extern int 	unlink(const char *path);
extern int 	rmdir(const char *path);
extern int 	access(const char *path, int amode);
extern int 	chown(const char *path, uid_t owner, uid_t group);
extern long 	pathconf(const char *path, int name);
extern long 	fpathconf(int fd, int name);
extern int 	pipe(int fildes[2]);
extern int 	dup(int fd);
extern int 	dup2(int fd,int fd2);
extern int 	close(int fd);
extern ssize_t 	read(int fd, void *buf, size_t nbyte);
extern ssize_t 	write(int fd, const void *buf, size_t nbyte);
extern int  ftruncate( int fd, unsigned int size );
extern ll_off_t 	lseek(int fd, ll_off_t offset, int whence);
extern int      fsync( int fd );
extern int     syncall(void);
char * fdToMntName(int fd);
extern int syncByName(const utf16 *wpath);
extern int	wunlink(const utf16* path);
extern int	wopen( const utf16* /* path */, int /* oflag */, ... );
#if defined(ENABLE_CHECK_DISK)
int wopen_ex( const utf16 *wpath, int oflag, ... );
#endif
extern int	wrmdir(const utf16* path);
__externC int	wopen_fcc( const utf16 *wpath, int oflag,unsigned int * addr, unsigned int size, ... );
// --------------------------------------------------------------------------

#define PARTIAL_SYNC    1
#ifndef CFG_REDUCE_MEM_USAGE
#define AUTO_ALIGN 1
#endif
// --------------------------------------------------------------------------

struct fatfs_disk_s;
typedef struct fatfs_disk_s fatfs_disk_t;

// --------------------------------------------------------------------------
typedef enum {
    EXNAME_FIRST,
    EXNAME,
    DIRENT,
    DIREND,
    DELENTRY,
    VOLUME,

    SEARCHING = 0x10,
    MATCHING = 0x20,
    SHORTMATCH = 0x30

} fatfs_entry_type;

typedef enum fatfs_type_e
{
    FATFS_FAT12 = 0,
    FATFS_FAT16,
    FATFS_FAT32
} fatfs_type_t;


typedef enum rw_type_e
{
    TENTRY = 0,    //for FAT Table
    RAW_ENTRY,     //for Dir entry
    DENTRY,
#if defined(ENABLE_CHECK_DISK)
    T2ENTRY,
#endif
    DEFAULT_ENTRY
} rw_type_t;


typedef struct fatfs_data_pos_s
{
    efat_uint32 cluster;      // Cluster number
    efat_uint32 cluster_snum; // Cluster file seq number
                             // (0 - first cluster of file,
                             //  1 - second cluster of file, ...)
    efat_uint32 cluster_pos;  // Position inside cluster
} fatfs_data_pos_t;

typedef struct {
    struct efat_list_head  list_node; // list node
    struct ms_efat_node    ms_efat_node;   // red-black tree node
    efat_uint32        num;       // block number
/* ++ Port V107MMP ++ */
    efat_uint32        d_sector;  // only support 16K cache block
/* -- Port V107MMP -- */
    efat_uint32        flags;     // Flag word
    efat_bool          modified;  // is this block data modified (needs write)
    efat_uint8         *data;   // block data
} blib_block_t;

typedef struct {
    efat_uint32  n_gets;     // number of block gets
    efat_uint32  n_reads;    // number of block reads
    efat_uint32  n_writes;   // number of block writes
} efat_blib_stat_t;

typedef struct {
    struct efat_list_head      efat_list_head;       // head of block list
    struct ms_efat_root        ms_efat_root;         // block red-black tree root
    fatfs_disk_t          *disk;           // Pointer to disk object
    efat_uint32            block_size;      // block size
    efat_uint32            block_size_log2; // block size log2
    efat_uint8            *mem_base;        // memory base
    efat_uint32            mem_size;        // memory size
    struct efat_list_head      free_efat_list_head;  // list of free blocks
#ifdef IMP_BLOCK_LIB_STATISTICS
    efat_blib_stat_t       stat;            // statistics
#endif
#ifdef EFAT_FS_FAT_ENTRY_WRITE_RETRY
    efat_uint32            retry_cnt;       // write retry count
#endif
    efat_uint8             fat_table;
    efat_uint8             dir_table;
} efat_blib_t;

// -------------------------------------------------------------------------
// FAT dir entry structure

typedef struct fat_raw_dir_entry_s
{
    char       name[8+1];   // 00h : Name
    char       ext[3+1];    // 08h : Extension
    efat_uint8  attr;        // 0Bh : Attribute
    efat_uint8  nt_reserved; // 0Ch : Win NT Reserved field
    efat_uint8  crt_sec_100; // 0Dh : Creation time ms stamp 0 - 199
    efat_uint16 crt_time;    // 0Eh : Creation time
    efat_uint16 crt_date;    // 10h : Creation date
    efat_uint16 acc_date;    // 12h : Last access date
    efat_uint16 cluster_HI;  // 14h : Starting cluster HI WORD (FAT32)
    efat_uint16 wrt_time;    // 16h : Time
    efat_uint16 wrt_date;    // 18h : Date
    efat_uint16 cluster;     // 1Ah : Starting cluster
    efat_uint32 size;        // 1Ch : Size of the file

#ifdef CFG_FS_FAT_LONG_FILE_NAMES
    efat_uint8  id;          // 00h : Entry sequence number
    efat_uint16 extname[13]; // 01h : Extended file name fragment
    efat_uint8  alias_csum;  // 0Dh : Checksum of main dirent
#endif

} fat_raw_dir_entry_t;

typedef struct fatfs_dir_entry_s
 {
    char              filename[12+1]; // name of file
    mode_t            mode;           // Mode type
    size_t            size;           // Size of file (bytes)
    time_t            ctime;          // Create times
    time_t            atime;          // Last access times
    time_t            mtime;          // Last modify times
    efat_uint8         rsvd;           // Reserved
    efat_uint8         priv_data;      // Private data
    efat_uint32        cluster;        // 1st cluster number
    efat_uint32        parent_cluster; // 1st cluster of parent dentry
    fatfs_data_pos_t  disk_pos;       // Position of dir entry on disk
#ifdef CFG_FS_FAT_LONG_FILE_NAMES
    fatfs_data_pos_t  start_pos;      // Position of start of dir entry on disk
     int              extras;         // Number of extra dir entries
#endif
#ifdef CFG_FS_FAT_USE_ATTRIBUTES
    efat_fs_attrib_t   attrib;         // Attribute bits for DOS compatability
#endif
#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT//fileid_stat
    unsigned long long fileid;
#endif
#if 1 // Peter new file info
    efat_uint8           format83;
    char                *longfilename;
#endif
} fatfs_dir_entry_t;

typedef struct fatfs_node_s
{
    fatfs_dir_entry_t    dentry;     // Dir entry data
    efat_ucount32         refcnt;     // Open file/current dir references

    struct fatfs_node_s *hash_next;  // Next node in hash
    struct fatfs_node_s *list_prev;  // Next node in list
    struct fatfs_node_s *list_next;  // Prev node in list
    struct fatfs_node_list_s *list;  // Pointer to current list
    char                 filename[FAT_FILE_NAME_MAX * sizeof(utf16)];
    efat_bool             is_wide;
} fatfs_node_t;

typedef struct fatfs_node_list_s
{
    efat_uint32    size;          // Number of nodes in list
    fatfs_node_t *first;         // First node in list
    fatfs_node_t *last;          // Last node in list
} fatfs_node_list_t;

#ifdef  EFAT_FS_FAT_USE_CLUSTER_CHAIN
typedef struct fatfs_fcluster_pool_s
{
    cluster_list     clist[NUM_FS_FAT_FCLUSTER_POOL_SIZE];
    efat_uint32      max_count;      // Max free clist count
    efat_uint32      cur_count;      // Curent free clist count
    efat_uint32      cur_idx;        // Current index in clist
} fatfs_fcluster_pool_t;
#endif

typedef struct fatfs_hash_table_s
{
    efat_uint32     size;                         // Number of slots
    efat_uint32     n;                            // Number of nodes
    fatfs_node_t  *nodes[FATFS_HASH_TABLE_SIZE]; // Nodes slots
} fatfs_hash_table_t;

struct fatfs_disk_s
{
    efat_uint32    sector_size;          // Sector size in bytes
    efat_uint32    sector_size_log2;     // Sector size log2
    efat_uint32    cluster_size;         // Cluster size in bytes
    efat_uint32    cluster_size_log2;    // Cluster size log2
    efat_uint32    fat_tbl_pos;          // Position of the first FAT table
#if defined(ENABLE_CHECK_DISK)
    efat_uint32    fat_tbl_pos2;          // Position of the second FAT table
#endif
    efat_uint32    fat_tbl_size;         // FAT table size in bytes
    efat_uint32    fat_tbl_nents;        // Number of entries in FAT table
    efat_uint32    fat_tbls_num;         // Number of FAT tables
    efat_uint32    fat_root_dir_pos;     // Position of the root dir
    efat_uint32    fat_root_dir_size;    // Root dir size in bytes
    efat_uint32    fat_root_dir_nents;   // Max number of entries in root dir
    efat_uint32    fat_root_dir_cluster; // Cluster number of root dir (FAT32)
    efat_uint32    fat_data_pos;         // Position of data area
    efat_uint32    fat_sector_num;       // Total number of sector
    fatfs_type_t  fat_type;             // Type of FAT - 12, 16 or 32

    efat_io_handle_t  dev_h;             // Disk device handle
    fatfs_node_t    *root;              // Root dir node

    mtabEntry  *mte;               // Mount table entry
#ifdef PKG_KERNEL
        efat_drv_mutex_t *lock;              // Filesystem lock
    #if defined(USE_RTK_CV)
        rtk_cond2_t rtk_cond2;
	    sem_t sema;
    #else
        efat_drv_cond_t  pending;            // cond var for pending IO threads
    #endif
#endif

    efat_uint8       *bcache_mem;        // Block cache memory base
    efat_blib_t       blib;              // Block cache and access library instance
    efat_uint8       *tcache_mem;        // Block cache memory base for FAT table
    efat_uint8       *dcache_mem;        // Block cache memory base for DIR
    efat_blib_t       tlib;              // Block cache and access library instance for FAT table
    efat_blib_t       dlib;              // Block cache and access library instance for DIR
#if defined(ENABLE_CHECK_DISK)
    efat_uint8       *ccache_mem;        // Block cache memory base for chkdsk
    efat_blib_t       clib;              // Block cache and access library instance for fat2 table
#endif
    fatfs_node_t  node_pool_base[FATFS_NODE_POOL_SIZE]; // Node pool base
    fatfs_node_t *node_pool[FATFS_NODE_POOL_SIZE];      // Node pool
    efat_uint32    node_pool_free_cnt;                   // Node pool free cnt

    fatfs_node_list_t  live_nlist;      // List of nodes with refcnt > 0
    fatfs_node_list_t  dead_nlist;      // List of nodes with refcnt == 0
    fatfs_hash_table_t node_hash;       // Hash of nodes in live and dead lists

//	Add by DZ, for speed up get capacity
#if defined(CFG_FS_FAST_GET_CAPACITY)
	efat_uint32    Disk_Free_Cluster;
#endif

#if defined(EFAT_FS_FAT_USE_CLUSTER_CHAIN)
    fatfs_fcluster_pool_t   fcluster_pool;  // free cluster pool
    efat_uint32              fcluster_start; // next fcluster search start
#endif
    volatile efat_bool  disk_contents_change;
    fatfs_rw_buffer               * rw_buffer;
    efat_uint32    last_cluster_sec;       // sector of last cluster

#if defined(CFG_FS_WRITE_WITH_SYNC)
    efat_uint8           fat_update;
#endif
#if defined(ENABLE_CHECK_DISK)
    efat_bool   fgChkDsk;
    efat_bool   fgDirtyBit;
    efat_bool   fgNeedChkdsk;
    efat_bool   fgClrDirty;
#endif
};


// --------------------------------------------------------------------------

typedef enum cluster_opts_e
{
    CO_NONE       = 0x00, // NULL option
    CO_EXTEND     = 0x01, // Extend cluster chain if one cluster too short
    CO_ERASE_NEW  = 0x02, // Erase newly allocated cluster
    CO_MARK_LAST  = 0x04  // Mark  newly allocated cluster as last
} cluster_opts_t;

void dentry_to_raw(fatfs_dir_entry_t *dentry, fat_raw_dir_entry_t *raw_dentry);
#ifdef ENABLE_FAST_ALLOCATE_MODE
int dz_find_next_free_cluster(fatfs_disk_t   *disk,
                       efat_uint32      start_cluster,
                       efat_uint32     *free_cluster,
                       cluster_opts_t  opts,
                       efat_uint32      requiredsize,
                       efat_uint32      alignment);
#endif


#ifdef __I_SW__
#define efat_timestamp()            (time_t)(MsGetOsTick()/1000)
#else
extern U32 time_stamp(void);
#define efat_timestamp()            (U32)time_stamp()
#endif


int  fatfs_init(fatfs_disk_t *disk);

void fatfs_get_root_dir_entry(fatfs_disk_t *disk, fatfs_dir_entry_t *dentry);

efat_bool fatfs_is_root_dir_dentry(fatfs_dir_entry_t *dentry);

bool fatfs_fetch_disk_usage(fatfs_disk_t *disk,
                     efat_uint32   *total_clusters,
                     efat_uint32   *free_clusters);


int  fatfs_get_disk_usage(fatfs_disk_t *disk,
                          efat_uint32   *total_clusters,
                          efat_uint32   *free_clusters,
                          bool          bg);

int  fatfs_initpos(fatfs_disk_t      *disk,
                   fatfs_dir_entry_t *file,
                   fatfs_data_pos_t  *pos);

int  fatfs_setpos(fatfs_disk_t      *disk,
                  fatfs_dir_entry_t *file,
                  fatfs_data_pos_t  *pos,
                  efat_uint32         offset);

int  fatfs_setpos_extend(fatfs_disk_t      *disk,
                  fatfs_dir_entry_t *file,
                  fatfs_data_pos_t  *pos,
                  efat_uint32         offset,
                  efat_bool       cluster_erase);



efat_uint32 fatfs_getpos(fatfs_disk_t      *disk,
                        fatfs_dir_entry_t *file,
                        fatfs_data_pos_t  *pos);

#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT
int is_valid_fileid(fatfs_disk_t      *disk,
             fatfs_dir_entry_t *file,
             efat_uint64         fileid,
             fatfs_data_pos_t *pos);

int fatfs_setpos_fileid(fatfs_disk_t      *disk,
             fatfs_dir_entry_t *file,
             fatfs_data_pos_t  *pos,
             efat_uint64         fileid);
#endif

#ifdef CFG_FS_FAT_LONG_FILE_NAMES

int fatfs_make_shortname( const char         *name,
                          int                 namelen,
                          char               *shortname,
                          char               *extname);

void make_shortname      (  const char     *name,
                           int            namelen,
                           char           *shortname);
#endif

#ifndef CFG_FS_FAT_LONG_FILE_NAMES
int fatfs_delete_dir_entry( fatfs_disk_t        *disk,
                        fatfs_data_pos_t    *pos,
                        fat_raw_dir_entry_t *raw_dentry );
#else
int fatfs_delete_dir_entry( fatfs_disk_t        *disk,
                        fatfs_data_pos_t    *spos,
                        int                  count,
                        fat_raw_dir_entry_t *raw_dentry );
#endif


int  fatfs_read_dir_entry(fatfs_disk_t      *disk,
                          fatfs_dir_entry_t *dir,
                          fatfs_data_pos_t  *pos,
                          fatfs_dir_entry_t *dentry);

int  fatfs_read_dir_entry_name(fatfs_disk_t      *disk,
                               fatfs_dir_entry_t *dir,
                               fatfs_data_pos_t  *pos,
                               char              *name,
                               int                len);

#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT
#ifdef CFG_FS_FAT_LONG_FILE_NAMES
int fatfs_get_dir_entry_name(fatfs_disk_t *disk, struct dirent *ent, fatfs_data_pos_t  pos);
#else
int fatfs_get_dir_entry(fatfs_disk_t *disk, fatfs_data_pos_t  *pos, fatfs_dir_entry_t *dentry);
#endif
#endif

int  fatfs_write_dir_entry(fatfs_disk_t *disk, fatfs_dir_entry_t *dentry);

int  fatfs_find_dir_entry(fatfs_disk_t      *disk,
                          fatfs_dir_entry_t *dir,
                          fatfs_data_pos_t  *pos,
                          const char        *name,
                          int                namelen,
                          fatfs_dir_entry_t *dentry);

int  fatfs_init_short_name(fatfs_disk_t      *disk,
                     fatfs_dir_entry_t *dir,
                     fatfs_data_pos_t  *pos,
                     char               *name,
                     char               *extname,
                     int                namelen);

int  fatfs_delete_file(fatfs_disk_t         *disk,
                       fatfs_dir_entry_t    *dir,
                       fatfs_dir_entry_t    *file,
                       const char           *name,
                       int                   namelen);

int  fatfs_create_file(fatfs_disk_t      *disk,
                       fatfs_dir_entry_t *dir,
                       const char        *name,
                       int                namelen,
                       fatfs_dir_entry_t *dentry);

int  fatfs_create_dir(fatfs_disk_t      *disk,
                      fatfs_dir_entry_t *dir,
                      const char        *name,
                      int                namelen,
                      fatfs_dir_entry_t *dentry);

int  fatfs_trunc_file(fatfs_disk_t *disk, fatfs_dir_entry_t *file);

int  fatfs_rename_file(fatfs_disk_t      *disk,
                       fatfs_dir_entry_t *dir1,
                       fatfs_dir_entry_t *target,
                       fatfs_dir_entry_t *dir2,
                       const char        *name,
                       int                namelen);

int  fatfs_read_data(fatfs_disk_t      *disk,
                     fatfs_dir_entry_t *file,
                     fatfs_data_pos_t  *pos,
                     void              *data,
                     efat_uint32        *len
#if defined(FS_FAT_MERGE_CONTINUOUS_CLUSTERS)
                    ,efat_uint32 ccr_enable
                    ,size_t     file_size
#endif
                     );

int  fatfs_write_data(fatfs_disk_t      *disk,
                      fatfs_dir_entry_t *file,
                      fatfs_data_pos_t  *pos,
                      void              *data,
                      efat_uint32        *len
#if defined(FS_FAT_MERGE_CONTINUOUS_CLUSTERS)
                     ,efat_uint32   ccw_enable
#endif
                     );
void fatfs_contents_status(fatfs_disk_t *disk, efat_bool bResetFlag, efat_bool *bStatus);
void disk_contents_status(fatfs_disk_t *disk, efat_bool bResetFlag, efat_bool *bStatus);
void disk_contents_change(fatfs_disk_t *disk);
void fatfs_free_cluster_reset(fatfs_disk_t *disk);
#if defined(ENABLE_CHECK_DISK)
void fatfs_lockdevice(efat_bool bLockState);
efat_int32 fatfs_fatcompare(fatfs_disk_t *disk, efat_uint32 *pu32Buf, efat_uint32 u32BufLen);
efat_bool fatfs_chk_empty_fat_sector(fatfs_disk_t *disk, efat_uint32 cluster);
void fatfs_use_fat1(fatfs_disk_t *disk, efat_bool fgFAT1, efat_bool fgSync);
efat_bool fatfs_recoveryfat(fatfs_disk_t *disk, efat_uint32 cluster);
void fatfs_backuppos(fatfs_data_pos_t *backuppos, fatfs_data_pos_t *srcpos);
efat_int32 fatfs_nextentry(fatfs_disk_t *disk, efat_uint32 cluster, efat_uint32 *tentry);
efat_int32 fatfs_getentrytype(fatfs_disk_t *disk, efat_uint32 cluster, efat_int32 *type);
int read_tentry(fatfs_disk_t *disk, efat_uint32 num, efat_uint32 *entry);
int get_tentry_type(fatfs_disk_t *disk, efat_uint32 entry);
efat_int32 fatfs_check_fat1(fatfs_disk_t *disk, struct efat_fs_fatchk *pfatchk);
int write_tentry(fatfs_disk_t *disk, efat_uint32 num, efat_uint32 *entry);
int
fatfs_set_size(mtabEntry        *mte,
                 efat_dir                dir,
                 const char            *name,
                 const efat_fs_attrib_t  new_size
                 ,int is_wide
                );
int get_tentry_type(fatfs_disk_t *disk, efat_uint32 entry);
efat_uint32 fatfs_set_dirtybit(fatfs_disk_t *disk);
efat_uint32 fatfs_clr_dirtybit(fatfs_disk_t *disk);
efat_uint32 fatfs_get_dirtybit(fatfs_disk_t *disk, efat_uint32 * Isdirty);

int
efat_disk_write(fatfs_disk_t *disk,
           void         *buf,
           efat_uint32   *len,
           efat_uint32    pos,
           rw_type_t      read_type);
int
efat_disk_read(fatfs_disk_t *disk,
          void         *buf,
          efat_uint32   *len,
          efat_uint32    pos,
          rw_type_t      read_type);
#endif
void fatfs_free_pool_query(fatfs_disk_t *disk, efat_uint32 * u32total_c, efat_uint32 *u32total_chain);
void fatfs_trigger_freepool_rescan(fatfs_disk_t *disk);
int strFilePathCheck(efat_uint16 *pPath, efat_uint16 IsDir);
u32 strPatternCnt(u16 *pStr, u16 checkword);

void init_fatfs_fds(void);
void delete_file_pause_set(efat_uint8 pause_flag);
void fatfs_PrintWStr(const efat_uint16 *pStr);

// --------------------------------------------------------------------------

fatfs_node_t *fatfs_node_alloc(fatfs_disk_t      *disk, fatfs_dir_entry_t *dentry, const char *name, int namelen);
int fatfs_get_live_node_count(fatfs_disk_t *disk);


void fatfs_node_touch(fatfs_disk_t *disk, fatfs_node_t *node);
void fatfs_node_rehash(fatfs_disk_t *disk, fatfs_node_t *node);
void fatfs_node_free(fatfs_disk_t *disk, fatfs_node_t *node);
void fatfs_PrintNodeName(fatfs_disk_t *disk);


#ifndef PKG_LIBC_I18N

__externC int toupper( int c );

#endif

int fatfs_get_dead_node_count(fatfs_disk_t *disk);
fatfs_node_t* fatfs_node_find(fatfs_disk_t *disk, const char   *name, unsigned int  namelen, unsigned int  parent_cluster);



__externC unsigned towupper( unsigned c );
__externC int wbytencasecmp( const utf16 *s1, const utf16 *s2, size_t n );
__externC int wbytencasecmp2( const char *s1, const utf16 *s2, size_t n );
__externC efat_uint32 wbytestrlen(efat_uint16 * pStr);
void fatfs_node_ref(fatfs_disk_t *disk, fatfs_node_t *node);
void fatfs_node_unref(fatfs_disk_t *disk, fatfs_node_t *node);

void MSTAR_FS_PrintWStr(const utf16 *str);
void MSTAR_FS_PrintStr(const char *str);
void MSTAR_FS_SEMAID_INIT(void *pSema, U8 u8StartID, U8 u8ReservedID, U8 u8AllocSemaCnt, char *SemaString);

U32 wstrlen(const char *pStr);
char *wstrcat(char *pStr1, const char *pStr2);
S32 wstrcmp(const char *pStr1, const char *pStr2 );
char * wstrcpy(char *pStr1, const char *pStr2);

#ifndef FUN_LIBC_STRING_BSD_FUNCS

__externC int strcasecmp( const char *s1, const char *s2 );

__externC int bytencasecmp( const char *s1, const char *s2, size_t n );

#endif
void fatfs_ResetDataRWBuf(fatfs_disk_t *disk);

// --------------------------------------------------------------------
// Writes data
//
//   bl   - block lib instance
//   buf  - data buffer ptr
//   len  - number of bytes to write
//   bnum - starting block number
//   pos  - starting position inside starting block
//
//   returns EFAT_ENOERR if write succeded
//
//   The block number is automatically adjusted if
//   position is greater than block size
//

int efat_blib_write(efat_blib_t *bl,
                   const void *buf,
                   efat_uint32 *len,
                   efat_uint32  bnum,
                   efat_uint32  pos);


void fatfs_node_cache_init(fatfs_disk_t *disk);
void fatfs_node_cache_flush(fatfs_disk_t *disk);

// --------------------------------------------------------------------
// Flushes block cache
//
//   bl  - block lib instance
//
//   returns EFAT_ENOERR if flush succeded
//
//   The block cache is synced before
//

int efat_blib_flush(efat_blib_t *bl);

// --------------------------------------------------------------------
// Gets block cache statistics
//
//   bl - block lib instance
//
//   returns EFAT_ENOERR if get succeded
//

int efat_blib_get_stat(efat_blib_t *bl, efat_blib_stat_t *stat);
#if defined(ENABLE_CHECK_DISK)
void efat_blib_invalidate_allcache(fatfs_disk_t *disk);
void efat_blib_syncall(fatfs_disk_t *disk);
void efat_blib_recreate_allcache(fatfs_disk_t *disk);
#endif

// --------------------------------------------------------------------
// Deletes a block lib instance
//
//   bl - block lib instance
//
//   The block cache is synced before
//
//   returns EFAT_ENOERR if delete succeded
//

int efat_blib_delete(efat_blib_t *bl);

// --------------------------------------------------------------------
// Syncs block cache - ie write modified blocks
//
//   bl - block lib instance
//
//   returns EFAT_ENOERR if sync succeded
//

int efat_blib_sync(efat_blib_t *bl);

// --------------------------------------------------------------------
// Reads data
//
//   bl   - block lib instance
//   buf  - data buffer ptr
//   len  - number of bytes to read
//   bnum - starting block number
//   pos  - starting position inside starting block
//
//   returns EFAT_ENOERR if read succeded
//
//   The block number is automatically adjusted if
//   position is greater than block size
//

int efat_blib_read(efat_blib_t *bl,
                  void       *buf,
                  efat_uint32 *len,
                  efat_uint32  bnum,
                  efat_uint32  pos);


// --------------------------------------------------------------------
// Syncs block - ie write if modified
//
//   bl  - block lib instance
//   num - block number to sync
//
//   returns EFAT_ENOERR if sync succeded
//

int efat_blib_sync_block(efat_blib_t *bl, efat_uint32 num);


// --------------------------------------------------------------------
// Creates a block lib instance
//
//   mem_base   - block cache memory base
//   mem_size   - block cache memory size
//   block_size - block size
//   bl         - block lib instance space holder
//
//   returns EFAT_ENOERR if create succeded
//

int efat_blib_create(fatfs_disk_t       *disk,
                    void               *mem_base,
                    efat_uint32          mem_size,
                    efat_uint32          block_size,
                    efat_blib_t         *bl);

// --------------------------------------------------------------------
// Sets block size
//
//   bl         - block lib instance
//   block_size - new block size
//
//   returns EFAT_ENOERR if set succeded
//
//   The block cache is synced before
//

int efat_blib_set_block_size(efat_blib_t *bl, efat_uint32 block_size);


// --------------------------------------------------------------------
// Creates a block lib instance on top of IO system
//   (efat_io_bread and efat_io_bwrite)
//
//   handle     - efat_io_handle_t
//   mem_base   - block cache memory base
//   mem_size   - block cache memory size
//   block_size - block size
//   bl         - block lib instance space holder
//
//   returns EFAT_ENOERR if create succeded
//

int efat_blib_io_create(fatfs_disk_t       *disk,
                       void               *mem_base,
                       efat_uint32          mem_size,
                       efat_uint32          block_size,
#ifdef  EFAT_FS_FAT_ENTRY_WRITE_RETRY
                       efat_uint32          retry_cnt,
#endif
                       efat_blib_t         *bl);

// --------------------------------------------------------------------
// Gets block size
//
//   bl  - block lib instance
//
//   returns the current block size

static inline efat_uint32 efat_blib_get_block_size(efat_blib_t *bl)
{
    return bl->block_size;
}


// --------------------------------------------------------------------

// Check block cache - ie check dirty cache
//
//   bl - block lib instance
//
//   returns 1 if cache dirty
//
int efat_blib_check(efat_blib_t *bl);

// --------------------------------------------------------------------
// Gets log2 of block size
//
//   bl  - block lib instance
//
//   returns log2 of the current block size

static inline efat_uint32 efat_blib_get_block_size_log2(efat_blib_t *bl)
{
    return bl->block_size_log2;
}




// --------------------------------------------------------------------
// Get number of sector
//
//   cluster - current cluster
//
//   cluster_pos -- current pos of cluster
//
//   returns number of sector
//

int sector_to_cluster_start_sector(fatfs_disk_t *disk, int sector);

int cluster_to_sector(fatfs_disk_t *disk, int cluster, int cluster_pos);

efat_uint32 get_val_log2(efat_uint32 val);

// -------------------------------------------------------------------------
// link_cluster()
// Links two clusters.
int link_cluster(fatfs_disk_t *disk, efat_uint32 cluster1, efat_uint32 cluster2);

// -------------------------------------------------------------------------
// find_next_free_cluster()
// Finds first free cluster starting from given cluster.
// If none is available free_cluster is set to 0.
// If mark_as_last is set the found cluster is marked as LAST.
int
find_next_free_cluster(fatfs_disk_t   *disk,
                       efat_uint32      start_cluster,
                       efat_uint32     *free_cluster,
                       cluster_opts_t  opts,
                       rw_type_t        read_type);
#ifdef  EFAT_FS_FAT_USE_CLUSTER_CHAIN
// -------------------------------------------------------------------------
// file_cluster_chain()
int file_cluster_chain(fatfs_disk_t *disk, efat_uint32 start_cluster, efat_uint32 filesize, struct FILE_TAG *fp);
int fatfs_setpos_seek(fatfs_disk_t *disk, fatfs_dir_entry_t *file,
                      fatfs_data_pos_t *pos, efat_uint32 offset,
                      struct FILE_TAG *fp);
// --------------------------------------------------------------------
// Get/put free cluster from/to cluster pool
int get_free_cluster(fatfs_disk_t *disk, efat_uint32 start_cluster, efat_uint32 *free_cluster);
void record_free_cluster(fatfs_disk_t *disk, efat_uint32 num);
#endif

// -------------------------------------------------------------------------
// mark_cluster()
// Marks cluster (sets the cluster's FAT table entry to given type).
int mark_cluster(fatfs_disk_t *disk, efat_uint32 cluster, efat_uint32 type);


//#if defined(USE_RTK_CV)
//void rtk_cond_init2(rtk_cond2_t *cond);
//void rtk_cond_wait2(rtk_cond2_t * pCond, sem_t * pSem, efat_drv_mutex_t *lock);
//void rtk_cond_broadcast2(rtk_cond2_t *cond);
//#endif
// --------------------------------------------------------------------------
#if defined(ENABLE_CHECK_DISK)
bool fs_Disk_IsLock(const char * volname);
#endif

Efat_ErrNo dirty_buffer(fatfs_disk_t *disk, efat_uint32 block);



extern efat_bool
fatfs_is_short_filename( const char         *name_t,
                          int                 namelen,
                          int mode);


#define CACHEBUFFER_T_SIZE  NUM_FS_FAT_TABLE_BLOCK_CACHE_MEMSIZE
#define ACTUAL_CACHEBUFFER_T_SIZE (CACHEBUFFER_T_SIZE + (ALIGN_(sizeof(blib_block_t))*(CACHEBUFFER_T_SIZE/CACHE_BLOCK_SIZE_TAB)))

#define CACHEBUFFER_T_SIZE_NAND (NUM_FS_FAT_TABLE_BLOCK_CACHE_MEMSIZE/2)
#define ACTUAL_CACHEBUFFER_T_SIZE_NAND (CACHEBUFFER_T_SIZE_NAND + (ALIGN_(sizeof(blib_block_t))*(CACHEBUFFER_T_SIZE_NAND/(CACHE_BLOCK_SIZE_TAB/2))))

#define CACHEBUFFER_T_SIZE_NOR (NUM_FS_FAT_TABLE_BLOCK_CACHE_MEMSIZE/4)
#define ACTUAL_CACHEBUFFER_T_SIZE_NOR (CACHEBUFFER_T_SIZE_NOR + (ALIGN_(sizeof(blib_block_t))*(CACHEBUFFER_T_SIZE_NOR/(CACHE_BLOCK_SIZE_TAB/4))))


#define CACHEBUFFER_D_SIZE  NUM_FS_FAT_DIR_BLOCK_CACHE_MEMSIZE
#define ACTUAL_CACHEBUFFER_D_SIZE (CACHEBUFFER_D_SIZE + (ALIGN_(sizeof(blib_block_t))*(CACHEBUFFER_D_SIZE/CACHE_BLOCK_SIZE_DIR)))

#define CACHEBUFFER_D_SIZE_NAND (NUM_FS_FAT_TABLE_BLOCK_CACHE_MEMSIZE/2)
#define ACTUAL_CACHEBUFFER_D_SIZE_NAND (CACHEBUFFER_D_SIZE_NAND + (ALIGN_(sizeof(blib_block_t))*(CACHEBUFFER_D_SIZE_NAND/(CACHE_BLOCK_SIZE_TAB/2))))

#define CACHEBUFFER_D_SIZE_NOR (NUM_FS_FAT_TABLE_BLOCK_CACHE_MEMSIZE/4)
#define ACTUAL_CACHEBUFFER_D_SIZE_NOR (CACHEBUFFER_D_SIZE_NOR + (ALIGN_(sizeof(blib_block_t))*(CACHEBUFFER_D_SIZE_NOR/(CACHE_BLOCK_SIZE_TAB/4))))


extern struct fatfs_disk_s *fatfsdisk[NUM_FILEIO_MTAB_EXTRA];

#if !defined(FS_USING_SB)
extern SDRAM_FSBUF efat_uint8 cachebuffer_t[NUM_FILEIO_MTAB_EXTRA][ACTUAL_CACHEBUFFER_T_SIZE];
extern SDRAM_FSBUF efat_uint8 cachebuffer_d[NUM_FILEIO_MTAB_EXTRA][ACTUAL_CACHEBUFFER_D_SIZE];
#else
extern SDRAM_FSBUF efat_uint8 cachebuffer_ex_t[NUM_FILEIO_MTAB_EXTRA][ACTUAL_CACHEBUFFER_T_SIZE];
extern SDRAM_FSBUF efat_uint8 cachebuffer_ex_d[NUM_FILEIO_MTAB_EXTRA][ACTUAL_CACHEBUFFER_D_SIZE];
#endif

#ifdef PKG_IO_FILEIO_FILE_ID_SUPPORT
extern void check_clean_lscache(const char * disk, const char * path);
extern void check_clean_lscache_with_mentry(mtabEntry  *mte, const char * path);


enum
{
    DEV_ID_CARD,
    DEV_ID_SD_2,
    DEV_ID_NAND,
	DEV_ID_SD_1,
    DEV_ID_NOR,
    DEV_ID_HIDN,
    DEV_ID_UNDEF,
};

#endif
int efat_set_disk_attribute( const char *dev, efat_uint32 accmode);

#if defined(ENABLE_CHECK_DISK)
extern volatile efat_bool gfgLockDevice;
#endif
#if defined(FS_USING_SB)
//extern efat_uint8 *cachebuffer_t;
//extern efat_uint8 *cachebuffer_d;
//extern efat_uint8 *cachebuffer_c;
extern efat_uint32 cachebuff_t_size;
extern efat_uint32 cachebuff_d_size;
extern efat_uint32 cachebuff_c_size;
extern efat_uint32 cache_t_blocksize;
extern efat_uint32 cache_d_blocksize;
extern efat_uint32 cache_c_blocksize;
#endif
#if defined(ENABLE_CHECK_DISK)
extern volatile efat_bool gfgLockSD_1;
extern volatile efat_bool gfgLockSD_2;
extern volatile efat_bool gfgLockNAND;
extern volatile efat_bool gfgLockNOR;
extern volatile efat_bool gfgLockHIDN;

#endif

extern efat_uint32 efat_ramdump_tmp_buf;
extern efat_uint32 efat_ramdump_tmp_bufsize;

extern U8 EfatNotCloseFileName[MAX_FILE_NAME_LENGTH+NULL_LENGTH];
extern U16 EfatNotCloseFileNameIdx;


#endif // ONCE_FATFS_FATFS_H
// --------------------------------------------------------------------------
// EOF fatfs.h

