/*******************************************************************************
**
**  File        : mmpf_fs_api.h
**  Description : Main hif_fs_api header file
**  Author      : Sunny Sun
**  Revision    : 1.0
**
*******************************************************************************/

#ifndef __MMPF_FS_API_H__
#define __MMPF_FS_API_H__

#include "FAT_Intern.h"
#include "fs_cfg.h" //for use of (FS_Init) FS_NEWBUFFER

/** @addtogroup MMPF_FS
@{
*/
#if (FS_LIB == FS_UFS)
#define MMP_FS_MAX_OPEN_FILE_NUM    FS_MAXOPEN
#define MMP_FS_MAX_OPEN_DIR_NUM     FS_DIR_MAXOPEN
#else
#define MMP_FS_MAX_OPEN_FILE_NUM    FM_FILE_OPEN_MAX
#define MMP_FS_MAX_OPEN_DIR_NUM     FM_DIR_OPEN_MAX
#endif

typedef void *FS_DIRNETRY;

/*******************************************************************************
**      Constant Definition
*******************************************************************************/
#if (FORMAT_FREE_ENABLE)
#define MMP_FILEFOLDER_SUMNO   0x1000 //0x0400
#define MMPF_FS_DIRENTRY_SET_CLUSTERLOCATION (1 << 3)
#define FORMATFREEBUFSIZE (16*1024)

#define FORMATFREEMEDIA0   "SD:0:\\" 
#define FORMATFREEMEDIA1   "SD:1:\\" 
#endif

#define MMP_FILE_NAME    0x01
#define MMP_ATTRIBUTE    0x02
#define MMP_FILE_TIME    0x04
#define MMP_ENTRY_SIZE   0x08
#define MMP_ENTRY_FIRST_CLUSTER   0x10

#define MMP_FS_MAX_FILE_NAME        256

#define MMP_FS_INUSE            1
#define MMP_FS_NOUSE            0

#define MMP_FS_DIR          FS_DIR
#define MMP_FS_DIRENT       FS_DIRENT
#define MMP_FS_FORMAT_INFO  FS_FORMAT_INFO
#define MMP_FS_DISK_INOF    FS_DISK_INFO
#define MMP_FS_FILE         FS_FILE
#define MMP_FS_FILE_OBJ     FS_FILE_OBJ
#define MMP_FS_FAT_INFO     FS_FAT_INFO
#define MMP_FS_VOLUME       FS_VOLUME
#define MMP_FS_SB           FS_SB
#define MMP_FS_CACHETYPE_DATA     FS_SECTOR_TYPE_DATA
#define MMP_FS_RESET_SM 1
#define MMP_FS_RESET_SD 2
#define MMP_FS_EOF          FS_ERR_EOF
#define MMP_FS_DEVICE       FS_DEVICE
#define MMP_FS_DEVICE_TYPE  FS_DEVICE_TYPE
#define MMP_FS_DEV_INFO     FS_DEV_INFO
//==============================================================================
//  FS_FILETIME structure has following format
//  struct FS_FILETIME{
//  FS_U16 Day;
//  FS_U16 Hour;
//  FS_U16 Minute;
//  FS_U16 Second;
//  } FS_FILETIME;
//  Members Meaning
//  Year Represents the year. The year must be greater than 1980.
//  Month Represents the month, where January = 1; February = 2 etc..
//  Day Represents the day of the month (1-31)
//  Hour Represents the hour of the day (0-23)
//  Minute Represents the minute of the day (0-59)
//  Second Represents the second (0-59).
//==============================================================================
#define MMP_FS_FILETIME     FS_FILETIME


#define MMP_FS_FILE_CURRENT           FS_SEEK_CUR
#define MMP_FS_FILE_END               FS_SEEK_END
#define MMP_FS_FILE_BEGIN             FS_SEEK_SET

#define MMP_FS_ATTR_READ_ONLY    FS_ATTR_READ_ONLY
#define MMP_FS_ATTR_HIDDEN       FS_ATTR_HIDDEN
#define MMP_FS_ATTR_SYSTEM       FS_ATTR_SYSTEM
#define MMP_FS_ATTR_VOLUME_ID    0x08
#define MMP_FS_ATTR_ARCHIVE      FS_ATTR_ARCHIVE
#define MMP_FS_ATTR_DIRECTORY    FS_ATTR_DIRECTORY
#define MMP_FS_ATTR_LONGNAME     FS_FAT_ATTR_READ_ONLY | \
                                 FS_FAT_ATTR_HIDDEN |    \
                                 FS_FAT_ATTR_SYSTEM |    \
                                 FS_FAT_ATTR_VOLUME_ID

//==============================================================================
//  Struct Define
//==============================================================================

typedef enum _MMP_FS_IOCTL_CMD {
    MMP_FS_CMD_RESET_STORAGE = 0,
    MMP_FS_CMD_GETSIZE,
    MMP_FS_CMD_READ_SECTOR,
    MMP_FS_CMD_WRITE_SECTOR,
    MMP_FS_CMD_WRITE_PROTECT,
    MMP_FS_CMD_CARD_DETECT,
    MMP_FS_CMD_FINISH_WRITE,
    MMP_FS_CMD_PWR_DISABLE,
    MMP_FS_CMD_GET_CARDSTATUS,
    MMP_FS_CMD_RESET_MEDIUM,
    MMP_FS_CMD_UNMOUNT_MEDIUM,
    MMP_FS_CMD_MOUNT_MEDIUM
}MMP_FS_IOCTL_CMD;

typedef struct _MMP_FS_IOCTL_PARA {
    MMP_ULONG   Para[2];
} MMP_FS_IOCTL_PARA;

#if (FORMAT_FREE_ENABLE)
/// FileSystem Event
typedef enum _MMPF_FileSystem_EVENT {
    MMPF_FileSystem_EVENT_NONE = 0,
    MMPF_FileSystem_EVENT_FileName_Require,
    MMPF_FileSystem_EVENT_MAX
} MMPF_FileSystem_EVENT;

typedef   void   (MMPF_FileSystem_Callback) (MMP_ULONG FolderIndex, MMP_ULONG FileIndex, MMP_BYTE * pFileName);
#endif

//==============================================================================
//  prototype
//==============================================================================

#if defined (ALL_FW)
int  MMPF_FS_SetCacheStartAddrSize( struct _FS_CACHE_INFO *pthis , U32 ulStartAddr, U32 ulTotalSize);
int  MMPF_FS_SetCacheNumSize( struct _FS_CACHE_INFO *pthis  , U8 ubCacheNum, U32 ulCacheSize);
int  MMPF_FS_SetCacheSectorSize( struct _FS_CACHE_INFO *pthis  , U32 ulCacheSectorSize );
int  MMPF_FS_SetFatNumSectors( struct _FS_CACHE_INFO *pthis  , U32 ulFatNumSectors );
int  MMPF_FS_SetFirstDataSector( struct _FS_CACHE_INFO *pthis  , U32 ulFirstDataSector );
int  MMPF_FS_SetHiddenSector( struct _FS_CACHE_INFO *pthis  , U32 ulHiddenSector );
int  MMPF_FS_RegCacheMedia( struct _FS_CACHE_INFO *pthis  , const FS_DEVICE_TYPE *pDeviceType);
int  MMPF_FS_RegCacheSelf ( struct _FS_CACHE_INFO *pthis  , const FS_DEVICE_TYPE *pDeviceType);
int  MMPF_FS_RegCacheObject ( struct _FS_CACHE_INFO *pthis  , struct _FS_CACHE_INFO *pObject); 
#endif

#if (FORMAT_FREE_ENABLE)
MMP_ERR MMPF_FS_MakeFileDirEntry(FS_VOLUME * pVolume, const MMP_BYTE *pFileName,MMP_ULONG FileNUM ,MMP_ULONG FileSize, U64 FolderClusterNumber, U64 FileClusterNumber, MMP_ULONG ParentClusterID);
MMP_ERR MMPF_FS_FormatFreeFATTable(FS_VOLUME  * pVolume, MMP_ULONG FileNoSUM);
MMP_ERR MMPF_FS_FormatFreeFATCheck(FS_VOLUME * pVolume);
MMP_ERR MMPF_FORMATFREE_RegisterCallback(MMPF_FileSystem_EVENT  ulEvent, void *pCallback);
MMP_ERR MMPF_FORMATFREE_CheckMedia(MMP_BYTE bMedia);
MMP_ERR MMPF_FORMATFREE_Format(MMP_BYTE bMedia);
MMP_ULONG MMPF_FORMATFREE_GetIdealFileNumInFolder( MMP_BYTE byFolderIndex );
#endif

MMP_ERR MMPF_FS_Initialize(void);
MMP_ERR MMPF_FS_Exit(void);
void MMPF_FS_Unmount(const MMP_BYTE *sVolume);
MMP_ERR MMPF_FS_FOpen(const MMP_BYTE *pFileName, const MMP_BYTE *pMode, MMP_ULONG *ulFileID);
MMP_ERR MMPF_FS_FClose(MMP_ULONG ulFileID);
MMP_ERR MMPF_FS_FRead(MMP_ULONG ulFileID, void *pData, MMP_ULONG NumBytes, MMP_ULONG *read_count);
MMP_ERR MMPF_FS_FWrite(MMP_ULONG ulFileID, void *pData, MMP_ULONG NumBytes, MMP_ULONG *write_count);
MMP_ERR MMPF_FS_FSeek(MMP_ULONG ulFileID, MMP_LONG64 llOffset, MMP_LONG lOrigin);
MMP_ERR MMPF_FS_FTell(MMP_ULONG ulFileID, MMP_LONG64 *llFilePos);
MMP_ERR MMPF_FS_FCopy(const MMP_BYTE * sSource, const MMP_BYTE * sDest);
MMP_ERR MMPF_FS_GetFileAttributes(const MMP_BYTE * pName, MMP_UBYTE *attributes);
MMP_ERR MMPF_FS_GetFileTime(const MMP_BYTE *pName, MMP_U_LONG *TimeStamp);
MMP_ERR MMPF_FS_Move(const MMP_BYTE * sExistingName, const MMP_BYTE * sNewName);
MMP_ERR MMPF_FS_Remove(const MMP_BYTE *pFileName);
MMP_ERR MMPF_FS_Rename(const MMP_BYTE * sOldName, const MMP_BYTE * sNewName);
MMP_ERR MMPF_FS_SetFileAttributes(const MMP_BYTE * pName, MMP_UBYTE Attributes);
MMP_ERR MMPF_FS_SetFileTime(const MMP_BYTE * pName, const MMP_U_LONG TimeStamp);
MMP_ERR MMPF_FS_GetFileSize(MMP_ULONG ulFileID, MMP_ULONG64 *ulFileSize);

MMP_ERR MMPF_FS_GetFilePhyFirstSector(MMP_ULONG ulFileID, MMP_U_LONG *ulPHYFirstSector);

MMP_ERR MMPF_FS_GetFileInfo(const MMP_BYTE *pName, MMP_UBYTE *attributes, 
                            MMP_U_LONG *TimeStamp, MMP_U_LONG *filesize);
MMP_ERR MMPF_FS_Truncate(MMP_ULONG ulFileID, MMP_ULONG ulNewSize);

MMP_ERR MMPF_FS_GetPBROffset(MMP_BYTE *sVolume, MMP_ULONG *ulPRBOffset);

MMP_ERR MMPF_FS_CloseDir(MMP_ULONG ulDirID);
void MMPF_FS_DirEnt2Attr(FS_DIRNETRY dirEnt, MMP_UBYTE* pAttr);
MMP_ERR MMPF_FS_DirEnt2Name(FS_DIRNETRY dirEnt, MMP_BYTE* pBuffer);
MMP_ERR MMPF_FS_DirEnt2Size(FS_DIRNETRY dirEnt, MMP_ULONG64 *entry_size);
MMP_ERR MMPF_FS_DirEnt2Time(FS_DIRNETRY dirEnt, MMP_FS_FILETIME *pFileTime);
MMP_ERR MMPF_FS_GetNumFiles(MMP_ULONG ulDirID, MMP_ULONG *ulFileCount);
MMP_ERR MMPF_FS_MkDir(const MMP_BYTE *pDirName);
MMP_ERR MMPF_FS_OpenDir(const MMP_BYTE *pDirName, MMP_ULONG *ulDirID);
MMP_ERR MMPF_FS_ReadDir(MMP_ULONG ulDirID, FS_DIRNETRY* pDirEnt);
MMP_ERR MMPF_FS_RewindDir(MMP_ULONG ulDirID);
MMP_ERR MMPF_FS_RmDir(const MMP_BYTE *pDirName);
MMP_ERR MMPF_FS_DirEnt2Info(MMP_ULONG ulDirID, MMP_UBYTE info_mode, MMP_BYTE* pBuffer, 
                        MMP_UBYTE* bAttribute, MMP_FS_FILETIME *filetime, MMP_ULONG64 *ulEntrySize);
MMP_ERR MMPF_FS_Format(const MMP_BYTE *pDevice);

#if (FS_NEW_GET_FREE_SPACE == 0)
MMP_ERR MMPF_FS_GetVolumeFreeSpace(const MMP_BYTE * sVolume, MMP_ULONG64 *free_bytes);
#else
MMP_ERR MMPF_FS_GetVolumeFreeSpace(const MMP_BYTE * sVolume, MMP_ULONG64 *free_bytes, MMP_BOOL bForceRefind);
#endif

MMP_LONG MMPF_FS_GetNumVolumes(void);
MMP_ERR MMPF_FS_GetVolumeSize(const MMP_BYTE * sVolume, MMP_ULONG64 *total_space);
MMP_ERR MMPF_FS_GetVolumeName(MMP_LONG Index, MMP_BYTE * pBuffer, MMP_LONG buffer_size, MMP_LONG *vol_name_length);
MMP_ERR MMPF_FS_GetVolumeInfo(const MMP_BYTE *sVolume, MMP_FS_DISK_INOF *pInfo);
MMP_ERR MMPF_FS_IsVolumeMounted(const MMP_BYTE * sVolumeName);
MMP_UBYTE MMPF_FS_CheckMediumPresent(const MMP_BYTE * sVolume);
MMP_ERR MMPF_FS_ProcessCmd(void);
void FS_Task(void);
MMP_ERR MMPF_FS_Format(const MMP_BYTE *pDevice);
MMP_BYTE *MMPF_FS_TranferUCS2toUTF8(MMP_BYTE *sName);

MMP_ERR MMPF_FS_ClusterId2SectorNo(MMP_ULONG ulFileID, MMP_ULONG ulClusterNo, 
                        MMP_ULONG ulOffset, MMP_ULONG *ulSectorAddr);
MMP_ERR MMPF_FS_FindFreeCluster(MMP_ULONG ulFileID, MMP_ULONG *ulCluster);
MMP_ERR MMPF_FS_GetSecCntPerCluster(MMP_ULONG ulFileID, MMP_USHORT *usSectorCount);
MMP_ERR MMPF_FS_GetLastFATEntry(MMP_ULONG ulFileID, MMP_ULONG *ulLastCluster);
MMP_ERR MMPF_FS_WriteSector(MMP_ULONG ulFileID, MMP_ULONG ulSectorNo, void * writeBuf);
MMP_ERR MMPF_FS_ReadSector(MMP_ULONG ulFileID, MMP_ULONG ulSectorNo, void * readBuf);
MMP_ERR MMPF_FS_ClearCache(void);

void MMPF_FS_InvalidateCache(void);
MMP_ERR   MMPF_FS_SetFileNameDmaAddr(MMP_ULONG ulNameAddr, MMP_ULONG ulNameSize,
                             MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);
MMP_ERR MMPF_FS_FileWriteTest(const MMP_BYTE *pFileName, const MMP_BYTE *pMode,
                                        MMP_ULONG write_size, MMP_ULONG file_size);
MMP_ERR     MMPF_FS_ResetStorage(MMP_UBYTE storage_type);
MMP_USHORT  MMPF_SM_LowLevelFormat(void);
MMP_ERR MMPF_FS_GetNumDirs(MMP_ULONG ulDirID, MMP_ULONG *ulDirCount);
MMP_USHORT  MMPF_FS_IOCtl(const char *pDevName, MMP_FS_IOCTL_CMD Cmd, MMP_FS_IOCTL_PARA Aux, void *pBuffer);
void    MMPF_FS_SetDRMIVAddr(MMP_ULONG ulStartAddr, MMP_ULONG ulSize);
MMP_ERR MMPF_FS_ReadMultiSector(MMP_ULONG ulFileID, MMP_ULONG ulSectorNo, void * readBuf, MMP_ULONG ulSectorCnt);
MMP_ERR MMPF_FS_GetSizePerSector(MMP_ULONG ulFileID, MMP_USHORT *usSectorSize);
MMP_ERR MMPF_FS_Mount(const MMP_BYTE *sVolume);
void MMPF_FS_Unmount(const MMP_BYTE *sVolume);
MMP_ERR MMPF_FS_Format(const MMP_BYTE *pDevice);
MMP_ULONG MMPF_FS_GetLastErrCode(void);
MMP_ERR MMPF_FS_GetSDCID(MMP_ULONG SD_ID,MMP_BYTE *CID);

/// @}

#endif  //__MMPF_FS_API_H__
