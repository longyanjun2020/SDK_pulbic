/// @ait_only
//==============================================================================
//
//  File        : mmpd_fs.h
//  Description : INCLUDE File for the file system (Host Device Driver Interface).
//  Author      : Ricky Yeh
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_FS_H_
#define _MMPD_FS_H_

#include "config_fw.h"       // adding for use "FORMAT_FREE_ENABLE" 
#include "includes_fw.h"

#if (FORMAT_FREE_ENABLE)
#include "fs_int.h"          // adding for use "FS_VOLUME" 
#endif

/** @addtogroup MMPD_FS
 *  @{
 */

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================


//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================


/**
 * ( Host Device Driver Layer) directory entry time structure.
 */
typedef struct _MMPD_FS_FILETIME {
    MMP_USHORT usYear;      ///< Represents the year. The year must be greater than 1980.
    MMP_USHORT usMonth;     ///< Represents the month, where January = 1, February = 2, ...
    MMP_USHORT usDay;       ///< Represents the day of the month(1-31).
    MMP_USHORT usHour;      ///< Represents the hour of the day(0-23).
    MMP_USHORT usMinute;    ///< Represents the minute of the day(0-59).
    MMP_USHORT usSecond;    ///< Represents the second(0-59)
} MMPD_FS_FILETIME;

typedef struct _MMPD_FS_DISK_INFO {
    MMP_ULONG  ulTotalClusters;  ///< Total number of clusters
    MMP_ULONG  ulFreeClusters;   ///< Number of free clusters
    MMP_USHORT usSecPerCluster; ///< Number of sectors per cluster
    MMP_USHORT usBytesPerSector;///< Number of bytes per sector
} MMPD_FS_DISK_INFO;

//
// Defines for MMPD_FS_FileSeek().
//
#define  MMPD_FS_SEEK_SET                  0
#define  MMPD_FS_SEEK_CUR                  1
#define  MMPD_FS_SEEK_END                  2


// Defines for
//      MMPD_FS_FileDirGetAttributes()
//    & MMPD_FS_FileDirSetAttributes()
typedef enum _MMPD_FS_ATTRIBUTE
{
    MMPD_FS_ATTR_READ_ONLY = 0x1,	///< The file or directory is read-only. Applications can read the file but can not write
                                    ///<            to it or delete it. In the case of a directory, applications can not delete it.
    MMPD_FS_ATTR_HIDDEN = 0x02,		///< The file or directory is hidden. It is not included in an ordinary directory listing.
    MMPD_FS_ATTR_SYSTEM = 0x04,		///< The file or directory is part of, or is used exclusively by, the operating system.
    MMPD_FS_ATTR_DIRECTORY = 0x10,	///< The given bpName is a directory.
    MMPD_FS_ATTR_ARCHIVE = 0x20		///< The file or directory is an archive file or directory.
                                    ///<            Applications can use this attribute to mark files for backup or removal.
} MMPD_FS_ATTRIBUTE;


//
// Defines for MMPD_FS_GetFileList()
//
#define MMPD_FILE_NAME                  0x01
#define MMPD_ATTRIBUTE                  0x02
#define MMPD_FILE_TIME                  0x04
#define MMPD_ENTRY_SIZE                 0x08


typedef enum _MMPD_FS_IOCTL_CMD {
    MMPD_FS_CMD_RESET_STORAGE = 0,
    MMPD_FS_CMD_GET_DEVINFO,
    MMPD_FS_CMD_READ_SECTOR,
    MMPD_FS_CMD_WRITE_SECTOR,
    MMPD_FS_CMD_WRITE_PROTECT,
    MMPD_FS_CMD_CARD_DETECT,
    MMPD_FS_CMD_FINISH_WRITE,
    MMPD_FS_CMD_PWR_DISABLE,
    MMPD_FS_CMD_GET_CARDSTATUS,
    MMPD_FS_CMD_RESET_MEDIUM,
    MMPD_FS_CMD_UNMOUNT_MEDIUM,
    MMPD_FS_CMD_MOUNT_MEDIUM
}MMPD_FS_IOCTL_CMD;

typedef struct _MMPD_FS_IOCTL_PARA {
    MMP_ULONG   ulPara[2];
} MMPD_FS_IOCTL_PARA;

#if (FORMAT_FREE_ENABLE)
/// FileSystem Event
typedef enum _MMPD_FileSystem_EVENT {
    MMPD_FileSystem_EVENT_NONE = 0,
    MMPD_FileSystem_EVENT_FileName_Require,
    MMPD_FileSystem_EVENT_MAX
} MMPD_FileSystem_EVENT;
#endif

//==============================================================================
//
//                               FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR	MMPD_FS_FileOpen(MMP_BYTE *bFileName, MMP_ULONG ulNameSize, MMP_BYTE *bMode, MMP_ULONG ulModeSize, MMP_ULONG *ulFileId);
MMP_ERR MMPD_FS_FileClose(MMP_ULONG ulFileId);
MMP_ERR MMPD_FS_FileRead(MMP_ULONG ulFileId, MMP_UBYTE *ubData, MMP_ULONG ulNumBytes, MMP_ULONG *ulReadCount);
MMP_ERR MMPD_FS_FileWrite(MMP_ULONG ulFileId,  MMP_UBYTE *ubData,  MMP_ULONG ulNumBytes, MMP_ULONG *ulWriteCount);
MMP_ERR MMPD_FS_FileSeek(MMP_ULONG ulFileId,  MMP_LONG64 llOffset,  MMP_ULONG ulOrigin);
MMP_ERR MMPD_FS_FileTell(MMP_ULONG ulFileId, MMP_LONG64 *llFilePos);
MMP_ERR MMPD_FS_FileCopy(MMP_BYTE *bSrc, MMP_ULONG ulSrcSize, MMP_BYTE *bDest,MMP_ULONG ulDestSize);

MMP_ERR	MMPD_FS_FileTruncate(MMP_ULONG ulFileId, MMP_ULONG ulNewSize);
MMP_ERR	MMPD_FS_FileGetSize(MMP_ULONG ulFileId, MMP_ULONG64 *ulFileSize);
MMP_ERR	MMPD_FS_FileRemove(MMP_BYTE *bpFileName,  MMP_ULONG ulNameSize);
MMP_ERR	MMPD_FS_FileDirGetAttribute(MMP_BYTE *bpName,  MMP_ULONG ulNameSize, MMPD_FS_ATTRIBUTE *attribute);
MMP_ERR	MMPD_FS_FileDirGetTime(MMP_BYTE *bpName,  MMP_ULONG ulNameSize, MMP_ULONG *ulpTimeStamp);
MMP_ERR	MMPD_FS_FileDirGetInfo(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPD_FS_ATTRIBUTE *attribute, MMP_ULONG *ulpTimeStamp, MMP_ULONG *ulpFileSize);
MMP_ERR	MMPD_FS_FileDirMove(MMP_BYTE *bpNameSrc,  MMP_ULONG ulSrcSize,  MMP_BYTE *bpNameDest,  MMP_ULONG ulDestSize);
MMP_ERR	MMPD_FS_FileDirRename(MMP_BYTE *bpOldName,  MMP_ULONG ulOldNameSiz,  MMP_BYTE *bpNewName, MMP_ULONG ulNewNameSiz);
MMP_ERR	MMPD_FS_FileDirSetAttribute( MMP_BYTE *bpName,  MMP_ULONG ulNameSize,  MMPD_FS_ATTRIBUTE attribute);
MMP_ERR	MMPD_FS_FileDirSetTime(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMP_ULONG ulTimeStamp );

MMP_ERR MMPD_FS_DirClose(MMP_ULONG ulDirID);
MMP_ERR MMPD_FS_DirGetNumFiles(MMP_ULONG ulDirID, MMP_ULONG *ulFileCount);
MMP_ERR MMPD_FS_DirCreate( MMP_BYTE *bpDirName,  MMP_ULONG ulNameSize);
MMP_ERR MMPD_FS_DirOpen(MMP_BYTE *bDirName, MMP_ULONG ulNameSize, MMP_ULONG *ulDirID);
MMP_ERR MMPD_FS_DirRewind(MMP_ULONG ulDirID);
MMP_ERR MMPD_FS_DirRemove( MMP_BYTE *bpDirName,  MMP_ULONG ulNameSize);
MMP_ERR MMPD_FS_HighLevelFormat( MMP_BYTE *bpDevice,  MMP_ULONG ulNameSize);
MMP_ERR MMPD_FS_GetFreeSpace( MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpFreeBytes);
MMP_ERR MMPD_FS_GetTotalSpace( MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpTotal);
MMP_ERR MMPD_FS_GetNumVolumes(MMP_LONG *lpNumVols);
MMP_ERR MMPD_FS_GetVolumeName( MMP_LONG lIndex, MMP_BYTE *bpBuffer,  MMP_LONG lBufferSize, MMP_LONG *lpVolNamLen);
MMP_ERR MMPD_FS_GetVolumeInfo(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMPD_FS_DISK_INFO *pInfo);
MMP_ERR MMPD_FS_IsVolumeMounted( MMP_BYTE *bpVolume,  MMP_ULONG ulNameSize);
MMP_ERR MMPD_FS_CheckMediumPresent( MMP_BYTE *bpVolume,  MMP_ULONG ulNameSize, MMP_UBYTE *ubpValue);
MMP_ERR MMPD_FS_GetFileList(MMP_ULONG ulDirId, MMP_UBYTE uInfoMode, MMP_BYTE* bBuffer,
                           MMPD_FS_ATTRIBUTE* attribute, MMP_ULONG* ulTimeStamp, MMP_ULONG* ulEntrySize);

MMP_ERR MMPD_FS_GetSDClass(MMP_ULONG id, MMP_UBYTE *bClass);

MMP_ERR MMPD_FS_GetDBFileList(MMP_ULONG ulDirId, MMP_BYTE* bBuffer, MMPD_FS_ATTRIBUTE *attribute, MMP_ULONG *ulFileID);
MMP_ERR MMPD_FS_SetCreationTime(MMP_ULONG ulTimeStamp);
MMP_ERR MMPD_FS_DirGetNumDirs(MMP_ULONG ulDirID, MMP_ULONG *ulDirCount);
MMP_ERR MMPD_FS_SetSDTmpMemory(MMP_ULONG ulStartAddr, MMP_ULONG ulSize);
MMP_ERR MMPD_FS_GetSMMEMAlloc(MMP_ULONG *ulBufferRequired);
MMP_ERR MMPD_FS_SetSMMemory(MMP_ULONG ulStartAddr, MMP_SHORT sSize);
MMP_ERR MMPD_FS_GetSNMEMAlloc(MMP_ULONG *ulBufferRequired);
MMP_ERR MMPD_FS_SetSNMemory(MMP_ULONG ulStartAddr, MMP_SHORT sSize);
MMP_ERR MMPD_FS_GetMaxFileOpenSupport(MMP_ULONG *ulMaxDirCounts);
MMP_ERR MMPD_FS_GetMaxDirOpenSupport(MMP_ULONG *ulMaxFileCounts);

MMP_ERR MMPD_FS_SetFileNameDmaAddr(MMP_ULONG ulNameAddr, MMP_ULONG ulNameSize,
                             MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);
MMP_ERR MMPD_FS_IOCtl(MMP_BYTE *bpDeviceName, MMP_ULONG ulNameSize,
                        MMPD_FS_IOCTL_CMD Cmd, MMPD_FS_IOCTL_PARA *Aux,
                        void *bpBuffer);
MMP_ERR MMPD_FS_Initialize(void);
MMP_ERR MMPD_FS_MountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize);
MMP_ERR MMPD_FS_UnmountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize);
MMP_ULONG MMPD_FS_SetFATGlobalBufAddr(MMP_ULONG ulBufStart, MMP_ULONG ulFATCacheLen);
MMP_ERR  MMPD_FS_SetDRMIVMemory(MMP_ULONG ulStartAddr, MMP_ULONG ulSize);
MMP_ERR  MMPD_FS_GetSFMEMAlloc(MMP_ULONG ulIdBufAddr, MMP_ULONG *ulBufferRequired);
MMP_ERR  MMPD_FS_SetSFMemory(MMP_ULONG ulStartAddr, MMP_SHORT sSize);
void MMPD_FS_CacheClear(void);
void MMPD_FS_CacheInvalidate(void);
MMP_ERR MMPD_FS_GetSDCID(MMP_ULONG SD_ID,MMP_BYTE *CID);

#if (FORMAT_FREE_ENABLE) 
MMP_ERR MMPD_FS_MakeFileDirEntry(FS_VOLUME * pVolume, const MMP_BYTE *pFileName,MMP_ULONG FileNUM, MMP_ULONG FileSize, U64 FolderClusterNumber, U64 FileClusterNumber, MMP_ULONG ParentClusterID);
MMP_ERR MMPD_FS_FormatFreeFATTable(FS_VOLUME  * pVolume, MMP_ULONG FileNoSUM);
MMP_ERR MMPD_FS_FormatFreeFATCheck(FS_VOLUME * pVolume);
MMP_ERR MMPD_FORMATFREE_RegisterCallback(MMPD_FileSystem_EVENT Event, void *CallBack);
MMP_ERR MMPD_FORMATFREE_CheckMedia(MMP_BYTE bMedia);
MMP_ERR MMPD_FORMATFREE_Format(MMP_BYTE bMedia);
MMP_ULONG MMPD_FORMATFREE_GetIdealFileNumInFolder(MMP_BYTE byFolderIndex);
#endif

/// @}
#endif // _MMPD_FS_H_

/// @end_ait_only

