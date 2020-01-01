////////////////////////////////////////////////////////////////////////////////
/// @file   mdl_efat_pub.h
/// @author MStar Semiconductor Inc.
/// @brief  Shell command parser state machine
////////////////////////////////////////////////////////////////////////////////
#ifndef MDL_EFAT_PUB_H
#define MDL_EFAT_PUB_H


#include "vm_types.ht"
#include "mdl_vfs_fat.ho"
#include "mdl_efat_error_codes.h"
#include "mdl_vfs_struct.h"
#include "sys_sys_sem_def.h"
#include "sys_MsWrapper_cus_os_type.h"
#define EFAT_FS_DATA_CACHE_DISABLE 1 
#define EFAT_FSDISK_SIZE  18200
#define EFAT_CACHE_TSIZE  8400
#define EFAT_CACHE_DSIZE  8400
#define EFAT_CACHE_SIZE   8400

#define FS_AT_CMDTEST (0)

#if defined(__DUAL_CARD__)// phone + SD1 + SD2
#if defined(__SUPPORT_HIDDEN_PARTITION__)
#define NUM_FILEIO_MTAB_EXTRA 4 
#else
#define NUM_FILEIO_MTAB_EXTRA 3 
#endif
#else   // phoe + SD1
#if defined(__SUPPORT_HIDDEN_PARTITION__)
#define NUM_FILEIO_MTAB_EXTRA 3
#else
#define NUM_FILEIO_MTAB_EXTRA 2
#endif
#endif

#define USE_RTK_CV
#if defined(USE_RTK_CV)
#define pthread_t                efat_thread
#define sem_t                    efat_sem_t
#define sem_init(a, b, c)       MsInitSem(a,c)//efat_semaphore_init(a, c)
#define sem_post                MsProduceSem//efat_semaphore_post
#define sem_wait                MsConsumeSem //efat_semaphore_wait
#define sem_destroy              efat_semaphore_destroy
#define pthread_create           efat_thread_create

typedef struct RTK_COND2{
    MsSemId_e  cm;
    MsSemId_e sem_sum;
    MsSemId_e sem_handshake;
    int waiters;
    MsSemId_e ext_sema;
} rtk_cond2_t;

void rtk_cond_init2(rtk_cond2_t *cond);
//int rtk_cond_wait2(rtk_cond2_t *cond, sem_t *sema, fatfs_disk_t *disk);
void rtk_cond_broadcast2(rtk_cond2_t *cond);
#endif

#ifndef ARM_DCACHE_LINE_SIZE
#define ARM_DCACHE_LINE_SIZE            32
#endif

#if defined(__G1__)
#define EFAT_BUFFER_CACHE_ALIGN         __attribute__ ((aligned (ARM_DCACHE_LINE_SIZE)))
#else
#define EFAT_BUFFER_CACHE_ALIGN         __align(ARM_DCACHE_LINE_SIZE)     
#endif

#if defined(EFAT_FS_DATA_CACHE_DISABLE)
#define SMALL_BUF_SIZE (4096)
#define SMALL_BUF_NUM  (2)
typedef enum rw_buffer_stat
{
    CLEAN = 0x00000000,
    DIRTY = 0x00000001
}RW_BUFFER_STAT;

typedef struct rw_buffer
{
    unsigned  char    buffer[SMALL_BUF_NUM][SMALL_BUF_SIZE];
    unsigned    int     start_sector[SMALL_BUF_NUM];
    RW_BUFFER_STAT      stat[SMALL_BUF_NUM];
    unsigned    int     d_sector[SMALL_BUF_NUM];
    unsigned    int     use_count[SMALL_BUF_NUM];
    unsigned long long    timestamp[SMALL_BUF_NUM];
    unsigned    int     sector_cnt;
    u8           sem;
    int diff;       //sector counts of buffer size
    int diff_log;   //log of diff
} fatfs_rw_buffer;
extern EFAT_BUFFER_CACHE_ALIGN fatfs_rw_buffer   rw_buffer[NUM_FILEIO_MTAB_EXTRA];
#endif
extern U8 efat_mtab_free_ebtry[NUM_FILEIO_MTAB_EXTRA];
extern EFAT_BUFFER_CACHE_ALIGN U8 efat_fatfsdisk[NUM_FILEIO_MTAB_EXTRA][EFAT_FSDISK_SIZE];
#if defined(FS_USING_SB)
extern U8 *cachebuffer_t;
extern U8 *cachebuffer_d;
extern U8 *cachebuffer_c;
#else
extern U8 cachebuffer_t[NUM_FILEIO_MTAB_EXTRA][EFAT_CACHE_TSIZE];
extern U8 cachebuffer_d[NUM_FILEIO_MTAB_EXTRA][EFAT_CACHE_DSIZE];
#endif
extern int SizeOfFreeMtab(void);
void init_fatfs_fds(void);
void efat_fd_init(void);
//------------------------------------------------------------------------------
// fatfs.h typedef
//------------------------------------------------------------------------------
#define EFAT_DBG26      _CUS1|LEVEL_26
//======================================================================
// DIR pointer object.
typedef void *DIR;


// -------------------------------------------------------------------------
// Unicode data type definition
typedef unsigned char  utf8;
typedef unsigned short utf16;
typedef unsigned int   utf32;

#define UTF8  utf8
#define UTF16 utf16
#define UTF32 utf32

typedef struct _fileinfo {
    long long   st_size;  /* File size (regular files only) */
}efat_fileinfo;

typedef enum {
  EFAT_PRT_NULL = 0,
  EFAT_PRT_SUCCESS,
  EFAT_PRT_NO_DEVICE,
  EFAT_PRT_SYNC_FAIL,
  EFAT_PRT_MOUNT_FAIL,
} Efat_PrtCode_e;

#if defined(__UNIT_TEST_APP__)
typedef struct _fsvirtualerr
{
    S8 u8EnterFSDLM;
    S8 u8VolumeFullErr;
    S8 u8MntErr;
    S8 u8NotMntErr;
    S8 u8ReadErr;
    S8 u8WriteErr;
    S8 u8PhysicalErr;
    S8 u8ManyFileOpenedErr;

}FS_VIRTUAL_ERR;

typedef enum
{
    VIRTUAL_ERROR_OPEN = 0,
    VIRTUAL_ERROR_READ,
    VIRTUAL_ERROR_WRITE,
    VIRTUAL_ERROR_CLOSE,
    VIRTUAL_ERROR_CARDFULL,
}VIRTUAL_ERROR_OPERATION;
#endif

//------------------------------------------------------------------------------
// device status
//------------------------------------------------------------------------------
typedef enum
{
  EFAT_ACC_NORMAL,     /* support read/write access */
  EFAT_ACC_READONLY,   /* support read-only access */
  EFAT_ACC_EIO_2_RO,   /* support read-only access, casued by io error */
} EFAT_ACC_e;
//------------------------------------------------------------------------------
// fatfs.h define
//------------------------------------------------------------------------------

//#define CHECK_DISK_NULL 1
#define FS_FORCE_MOUNT          0x01
#define FS_NO_SYNC_CACHE_DATA   0x02
#define FS_CLEAR_ALIAS          0x04

#define VOL_ID_MASK         (0x0F)
#define CHKDSK_PHASE_SHIFT   (0x4)
#define CHKDSK_PHASE0       (1<<0)
#define CHKDSK_PHASE1       (1<<1)
#define CHKDSK_PHASE2       (1<<2)
#define CHKDSK_PHASE3       (1<<3)
//------------------------------------------------------------------------------
// Extern Global Variabls
//------------------------------------------------------------------------------
extern S32 efat_errno;

extern const u16 *efat_RT16_NOR;
extern const u16 *efat_RT16_NAND;
extern const u16 *efat_RT16_SD;
extern const u16 *efat_RT16_SD1;
extern const u16 *efat_RT16_SD2;
extern const u16 *efat_RT16_HIDN;

extern const char efat_ND_StorageDir[];
extern const char efat_CARD_StorageDir[];

extern const char efat_SD1_DevName[];
extern const char efat_SD1_StorageDir[];
extern const char efat_ND_DevName[];
extern const char efat_ND_StorageDir[];
extern const char efat_NOR_DevName[];
extern const char efat_NOR_StorageDir[];
extern const char efat_SD2_DevName[];
extern const char efat_SD2_StorageDir[];
extern const char efat_HIDN_DevName[];
extern const char efat_HIDN_StorageDir[];


//------------------------------------------------------------------------------
// dirent.h Extern Functions
//------------------------------------------------------------------------------
//DIR *wopendir( const utf16 *dirname );
//struct dirent *readdir_t( DIR *dirp ,struct dirent *ent);  //Partial LS
//extern int closedir( DIR *dirp );
//u16 * _return_volname(u32 vol);

//------------------------------------------------------------------------------
// fileio_fileio.h Extern Functions
//------------------------------------------------------------------------------
int mount( const char *devname, const char *dir, const char *fsname);
int umount( const char *name, unsigned char force_umount);

//------------------------------------------------------------------------------
// file handle operations
//------------------------------------------------------------------------------
//extern long long 	lseek(int fd, long long offset, int whence);
//------------------------------------------------------------------------------
// fatfs_wrapper.h Extern Functions
//------------------------------------------------------------------------------
int Efat_error_get_errno_p(void);
void ls_static_var_init(void);
S32 Efat_mapping_error_code(S32 err);
void Efat_CheckNotCloseFile(U8 devType);


int Efat_open(const utf16 * const wpath, const int oflag);
int Efat_open_with_size(const utf16 * const wpath, const int mode, const U32 size);
int Efat_open_fcc(const utf16 * const wpath, const int mode, const U32 * addr, const U32 size);
int Efat_read(U32 file_ref, void *buf, U32 nb_data);
int Efat_write(const U32 file_ref, const void * const buf, const U32 nb_data);
S32 Efat_lseek(U32 file_ref, S32  offset, int position );
S32 Efat_lseek_4G(U32 file_ref, S64  offset, int position );
int Efat_close(const U32 file_ref);
int Efat_unlink( const utf16 *path );
//int Efat_sync(void);
int Efat_getinfo(U32 fileNum, VFS_File_Info_t *pFileInfo, U32 listLen, U32* pList);
int Efat_setinfo_by_name( const utf16 *path, VFS_File_Info_t *pFileInfo);
int Efat_get_info_by_name ( const utf16 *wpath,  File_Simple_Info_t* vfs_file_info_ptr);
int Efat_mkdir(const utf16 * const wpath);
int Efat_rename(const utf16 *woldname, const utf16 *wnewname);
int Efat_rmdir(const utf16 *wpath, U32 flag);

int Efat_truncate(U32 file_ref, U32 size);
S32 Efat_tell(U32 file_ref);
S32 Efat_tell_4G(U32 file_ref, U32 * pPosition);
int Efat_checkeof(U32 file_ref);
int Efat_exist(const utf16 * const wpath);
int Efat_set_attrib( const utf16 * const wfname, const U32 new_attrib );
int Efat_get_attrib( const utf16 * const wfname,  U32 * const file_attrib );
int Efat_get_opened_file_info(U32 file_num, VFS_File_Info_t* vfs_file_info_ptr);
int Efat_chdir(const utf16 *wdirname, U32 *listLen, U32 ** listBuf);
int Efat_nof_dir(const utf16 *wdirname);
int Efat_nof_openeddir(U32 listLen, U32 * listBuf);
int Efat_free_list(U8 * listBuf);
int Efat_size_dir(const utf16 *wdirname, U32 flag);
int Efat_get_volume_space(u32 vol, u32 * totalSize, u32 * freeSize);
int Efat_truncate_by_name(U16 *wpath, U32 size);
int Efat_rename_length(const U16 * name, U32 * length);
int Efat_delete_all( U16 * pathName, U32 listLen, U8 * listBuf);
int Efat_async_delete_req(U16* pPath, bool isFolder, VFS_PartialListFilter_t * pFilter, bool isRecursive, bool isForceDelete);
void Efat_async_delete_abort(void);
int Efat_SD_GetSerial(VFS_DevSerial_t * pDevSerial);
bool Efat_EmQueryCardStatus(VFS_DevType_e dev, VFS_CardMode_e *pMode);
int Efat_FileCombine(const utf16 * existfile, const utf16 * removefile);
int Efat_GetClusterSize (const utf16 * DiskName, U32 *infobuf);
//int Efat_get_vol_info(u32 vol, VFS_Vol_Info_t * pInfo);
int Efat_async_filter_get_file_num(U16 * pPathName, VFS_PartialListFilter_t * pFilter, U32 startFileNum, U32 * pStartFileNum, VFS_PartialListFileInfo_t * pFileInfoArray);
void Efat_async_filter_get_file_num_abort(void);
int Efat_partial_list(U16* pPathName, VFS_PartialListFilter_t   * pFilter, U32 offset, U32 requestNumEntry, U32 * pResultNumEntry, VFS_PartialListFileInfo_t * pFileInfoArray);
int Efat_get_full_info_by_name (const utf16 *wpath, VFS_PartialListFileInfo_t * vfs_file_info_ptr);
int Efat_id_to_info(U16 * pPathName, U32 numFileId, VFS_FileID_t * pFileIdArray, VFS_PartialListFileInfo_t * pFileInfoArray);

void fnDiskFreeCapacityReset(char *path);
int Efat_async_CheckDisk_req(U8 vol, U8 op);
int Efat_async_CheckDisk_abort(void);
S32 Efat_async_CheckDisk_pause(void);
S32 Efat_async_CheckDisk_resume(void);
int Efat_CheckDisk(U32 * size, U8 u8volume, U8 operation);

S32 Efat_async_Format_req(U8 vol);
void Efat_async_Format_pause(void);
void Efat_async_Format_resume(void);
void Efat_async_Format_abort(void);

S32 Efat_async_FreePoolScan_req(U8 vol);

int Efat_format(U32 volId);
#if defined(__UNIT_TEST_APP__)
void ut_EfatCheckVirtualErrorInit(void);
int ut_EfatCheckVirtualError(VIRTUAL_ERROR_OPERATION op, FS_VIRTUAL_ERR virerror);
void ut_EfatSetVirtualError(VIRTUAL_ERROR_OPERATION op);
#endif

U16* Efat_fd_to_lastname(U32 fd);
void Efat_InitFileOpenedStatus(void);
bool Efat_TryRootDirList(VFS_VOL_TYPE vol);
int Efat_GetFileInfo( const utf16 *wpath, efat_fileinfo *infobuf );
//int Efat_TriggerFreePoolRescan (const utf16 * DiskName);
int Efat_ResetFreeCapacityFlag (const utf16 * DiskName);
void Efat_RamdumpBufSet(u32 buf, u32 len);
int Efat_FsProtect(void);
S32 Efat_fsAccState(VFS_VOL_TYPE vol,  VFS_ACC_e *acc);
S32 Efat_fsDiskState (VFS_VOL_TYPE vol, VFS_DiskStatus_e *diskstatus);
S32 Efat_SetDiskAttr(const char *dev, U32 accmode);
#if FS_AT_CMDTEST
void sendchkdskcmd(u8 runmode, u8 rundevice);
#endif

//#ifdef __NEW_AUTO_TESTING__ 
int FSStorageDummyWrite(int mode);
//#endif

#endif // end of mdl_efat_pub.h

