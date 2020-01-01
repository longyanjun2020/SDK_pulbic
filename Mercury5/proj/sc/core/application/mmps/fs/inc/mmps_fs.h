//==============================================================================
//
//  File        : mmps_fs.h
//  Description : INCLUDE File for the file system (Host Application Interface).
//  Author      : Ricky Yeh
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_fs.h
 *  @brief Header File for the Host File System API.
 *  @author Ricky Yeh, Sunny
 *  @version 1.0
 */

#ifndef _MMPS_FS_H_
#define _MMPS_FS_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpd_fs.h"

/** @addtogroup MMPS_FS
@{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#if (FORMAT_FREE_ENABLE)
#define    NameLenghLimit             (128)
#define    FormatFreeFolderNumMAX      (20) //10
#endif

// For MMPS_FS_FileSeek()
#define  MMPS_FS_SEEK_SET                  0
#define  MMPS_FS_SEEK_CUR                  1
#define  MMPS_FS_SEEK_END                  2

// For  MMPS_FS_GetFileList()
/**@brief filter option for MMPS_FS_GetFileList()
    set bit of infomation user want to get file name from MMPS_FS_GetFileList
*/
#define MMPS_FILE_NAME                  0x01
/**@brief filter option for MMPS_FS_GetFileList()
    set bit of infomation user want to get file attribute from MMPS_FS_GetFileList
*/
#define MMPS_ATTRIBUTE                  0x02
/**@brief filter option for MMPS_FS_GetFileList()
    set bit of infomation user want to get file time from MMPS_FS_GetFileList
*/
#define MMPS_FILE_TIME                  0x04
/**@brief filter option for MMPS_FS_GetFileList()
    set bit of infomation user want to get file size from MMPS_FS_GetFileList
*/
#define MMPS_ENTRY_SIZE                 0x08

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//  For MMPD_FS_FileDirGetAttributes()
//    & MMPD_FS_FileDirSetAttributes()
typedef enum _MMPS_FS_ATTRIBUTE
{
    MMPS_FS_ATTR_READ_ONLY = 0x1,	///< The file or directory is read-only. Applications can read the file but can not write
                                    ///<     to it or delete it. In the case of a directory, applications can not delete it.
    MMPS_FS_ATTR_HIDDEN = 0x02,		///< The file or directory is hidden. It is not included in an ordinary directory listing.
    MMPS_FS_ATTR_SYSTEM = 0x04,		///< The file or directory is part of, or is used exclusively by, the operating system.
    MMPS_FS_ATTR_DIRECTORY = 0x10,	///< The given bpName is a directory.
    MMPS_FS_ATTR_ARCHIVE = 0x20		///< The file or directory is an archive file or directory.
                                    ///< Applications can use this attribute to mark files for backup or removal.
} MMPS_FS_ATTRIBUTE;

typedef enum _MMPS_FS_IOCTL_CMD {
    MMPS_FS_CMD_RESET_STORAGE = 0,
    MMPS_FS_CMD_GET_DEVINFO,
    MMPS_FS_CMD_READ_SECTOR,
    MMPS_FS_CMD_WRITE_SECTOR,
    MMPS_FS_CMD_WRITE_PROTECT,
    MMPS_FS_CMD_CARD_DETECT,
    MMPS_FS_CMD_FINISH_WRITE,
    MMPS_FS_CMD_PWR_DISABLE,
    MMPS_FS_CMD_GET_CARDSTATUS,
    MMPS_FS_CMD_RESET_MEDIUM,
    MMPS_FS_CMD_UNMOUNT_MEDIUM,
    MMPS_FS_CMD_MOUNT_MEDIUM
}MMPS_FS_IOCTL_CMD;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/**
 * ( Host Application Layer) directory entry time structure.
 */
typedef struct _MMPS_FS_FILETIME {
	MMP_USHORT usYear;      ///< Represents the year. The year must be greater than 1980.
	MMP_USHORT usMonth;     ///< Represents the month, where January = 1, February = 2, ...
	MMP_USHORT usDay;       ///< Represents the day of the month(1-31).
	MMP_USHORT usHour;      ///< Represents the hour of the day(0-23).
	MMP_USHORT usMinute;    ///< Represents the minute of the day(0-59).
	MMP_USHORT usSecond;    ///< Represents the second(0-59)
} MMPS_FS_FILETIME;

typedef struct _MMPS_FS_CONFIG {
	MMP_BOOL	bUseSD;		// SD/MMC is used in the file system
	MMP_BOOL	bUseNAND;	// NAND is used in the file system
	MMP_ULONG	ulNANDMemory;	// NAND temperory used memory. depend on NAND type
} MMPS_FS_CONFIG;

typedef struct _MMPS_FS_DISK_INFO {
    MMP_ULONG  ulTotalClusters;  ///< Total number of clusters
    MMP_ULONG  ulFreeClusters;   ///< Number of free clusters
    MMP_USHORT usSecPerCluster; ///< Number of sectors per cluster
    MMP_USHORT usBytesPerSector;///< Number of bytes per sector
} MMPS_FS_DISK_INFO;

typedef struct _MMPS_FS_IOCTL_PARA {
    MMP_ULONG   ulPara[2];
} MMPS_FS_IOCTL_PARA;

#if (FORMAT_FREE_ENABLE)
typedef struct  {
    MMP_BYTE    FileNameInside[NameLenghLimit];
	MMP_ULONG   FileNumber; //Numbers of File under the Folder
	MMP_ULONG   FileSizeMB; //scale is MB
    MMP_BYTE    SpacePercentage; //such as 5/25/40 integer format_space percentage of the media	
    //if it's child folder,need to know the parent folder cluster ID
	MMP_ULONG   ParentFolderClusterID; 
} FormatFreeFolderConfig ;

/// FileSystem Event
typedef enum _MMPS_FileSystem_EVENT {
    MMPS_FileSystem_EVENT_NONE = 0,
    MMPS_FileSystem_EVENT_FileName_Require,
    MMPS_FileSystem_EVENT_MAX
} MMPS_FileSystem_EVENT;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR	MMPS_FS_FileOpen(MMP_BYTE *bFileName, MMP_ULONG ulNameSize, MMP_BYTE *bMode, MMP_ULONG ulModeSize, MMP_ULONG *ulFileId);
MMP_ERR	MMPS_FS_FileClose(MMP_ULONG ulFileId);
MMP_ERR MMPS_FS_FileRead(MMP_ULONG ulFileId, MMP_UBYTE *ubData, MMP_ULONG ulNumBytes, MMP_ULONG *ulReadCount);
MMP_ERR MMPS_FS_FileWrite(MMP_ULONG ulFileId, MMP_UBYTE *ubData, MMP_ULONG ulNumBytes, MMP_ULONG *ulWriteCount);
MMP_ERR MMPS_FS_FileSeek(MMP_ULONG ulFileId, MMP_LONG64 llOffset, MMP_ULONG ulOrigin);
MMP_ERR MMPS_FS_FileTell(MMP_ULONG ulFileId, MMP_LONG64 *llFilePos);
MMP_ERR MMPS_FS_FileCopy(MMP_BYTE *bSrc, MMP_ULONG ulSrcSize, MMP_BYTE *bDest,MMP_ULONG ulDestSize);
MMP_ERR MMPS_FS_FileTruncate(MMP_ULONG ulFileId, MMP_ULONG ulNewSize);

MMP_ERR	MMPS_FS_FileGetSize(MMP_ULONG ulFileId, MMP_ULONG64 *ulFileSize);
MMP_ERR	MMPS_FS_FileRemove(MMP_BYTE *bpFileName, MMP_ULONG ulNameSize);
MMP_ERR	MMPS_FS_FileDirGetAttribute(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_ATTRIBUTE *attribute);
MMP_ERR	MMPS_FS_FileDirGetInfo(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_ATTRIBUTE *attribute, MMPS_FS_FILETIME *timestructure, MMP_ULONG *ulpFileSize);
MMP_ERR	MMPS_FS_FileDirGetTime(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_FILETIME *timestructure);
MMP_ERR	MMPS_FS_FileDirMove(MMP_BYTE *bpNameSrc, MMP_ULONG ulSrcSize, MMP_BYTE *bpNameDest, MMP_ULONG ulDestSize);
MMP_ERR	MMPS_FS_FileDirRename(MMP_BYTE *bpOldName, MMP_ULONG ulOldNameSize, MMP_BYTE *bpNewName, MMP_ULONG ulNewNameSize);
MMP_ERR	MMPS_FS_FileDirSetAttribute(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_ATTRIBUTE attribute);
MMP_ERR	MMPS_FS_FileDirSetTime(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_FILETIME* pTimeStru);

MMP_ERR MMPS_FS_DirClose(MMP_ULONG ulDirID);
MMP_ERR	MMPS_FS_DirGetNumFiles(MMP_ULONG ulDirID, MMP_ULONG *ulFileCount);
MMP_ERR	MMPS_FS_DirCreate(MMP_BYTE *bDirName, MMP_ULONG ulNameSize);

MMP_ERR MMPS_FS_GetSDClass(MMP_ULONG id, MMP_UBYTE *bClass);

MMP_ERR	MMPS_FS_DirOpen(MMP_BYTE *bDirName, MMP_ULONG ulNameSize, MMP_ULONG *ulDirID);
MMP_ERR	MMPS_FS_DirRewind(MMP_ULONG ulDirID);
MMP_ERR	MMPS_FS_DirRemove(MMP_BYTE *bpDirName, MMP_ULONG ulNameSize);
MMP_ERR	MMPS_FS_HighLevelFormat(MMP_BYTE *bpDevice, MMP_ULONG ulNameSize);
MMP_ERR	MMPS_FS_GetFreeSpace(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpFreeBytes);
MMP_ERR	MMPS_FS_GetTotalSpace(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpTotal);
MMP_ERR	MMPS_FS_GetNumVolumes(MMP_LONG *lpNumVols);
MMP_ERR	MMPS_FS_GetVolumeName(MMP_LONG lIndex, MMP_BYTE *bpBuffer, MMP_LONG lBufferSize, MMP_LONG *lpVolNamLen);
MMP_ERR MMPS_FS_GetVolumeInfo(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMPS_FS_DISK_INFO *pInfo);
MMP_ERR	MMPS_FS_IsVolumeMounted(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize);
MMP_ERR	MMPS_FS_CheckMediumPresent(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_UBYTE *ubpValue);
MMP_ERR MMPS_FS_GetFileList(MMP_ULONG ulDirId, MMP_UBYTE ubInfoMode, MMP_BYTE* bBuffer,
                           MMPS_FS_ATTRIBUTE *attribute, MMPS_FS_FILETIME* filetime, MMP_ULONG* ulEntrySize);
MMP_ERR MMPS_FS_GetDBFileList(MMP_ULONG ulDirId, MMP_BYTE* bBuffer, MMPS_FS_ATTRIBUTE *attribute, MMP_ULONG* ulFileID);
MMP_ERR MMPS_FS_SetCreationTime(void);
MMP_ERR MMPS_FS_DirGetNumDirs(MMP_ULONG ulDirID, MMP_ULONG *ulDirCount);
MMP_ERR MMPS_FS_IOCtl(MMP_BYTE *bpDeviceName, MMP_ULONG ulNameSize
                        ,MMPS_FS_IOCTL_CMD Cmd, MMPS_FS_IOCTL_PARA *Aux
                        , void *pBuffer);
#if (FORMAT_FREE_ENABLE)
MMP_ERR MMPS_FORMATFREE_ConfigInfo( FormatFreeFolderConfig * pFolderConfig, MMP_BYTE RootFolder, MMP_BYTE FolderIndex, MMP_BYTE * FolderName, MMP_BYTE * FileNameInFolder );
MMP_ERR MMPS_FORMATFREE_CheckMedia(MMP_BYTE bMedia);
MMP_ERR MMPS_FORMATFREE_Format(MMP_BYTE bMedia);
void MMPS_FORMATFREE_Enable(MMP_BYTE EnableStatus);
void MMPS_FORMATFREE_EnableWrite(MMP_BYTE EnableStatus);
void MMPS_FORMATFREE_GetWriteEnable(MMP_UBYTE* WriteDataOnly);
MMP_ERR MMPS_FORMATFREE_RegisterCallback(MMPS_FileSystem_EVENT Event, void *CallBack);
MMP_ULONG MMPS_FORMATFREE_GetIdealFileNumInFolder(MMP_BYTE byFolderIndex);
#endif
MMP_ERR MMPS_FS_Initialize(void);
MMP_ERR MMPS_FS_MountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize);
MMP_ERR MMPS_FS_UnmountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize);

void _TimeStamp2FileTime(MMP_ULONG ulTimeStamp, MMPS_FS_FILETIME * pFileTime);
void _FileTime2TimeStamp(const MMPS_FS_FILETIME * pFileTime, MMP_ULONG * ulpTimeStamp);

/// @}

//Remove them later...
void MMPC_FS_BBGetRTC(MMPS_FS_FILETIME *pTimeStru);

MMP_USHORT MMPC_FS_FileOpen(MMP_BYTE *bFileName, MMP_BYTE *bMode, void **FileHandle);
MMP_USHORT MMPC_FS_FileClose(void *FileHandle);
MMP_USHORT MMPC_FS_FileSeek(void *FileHandle, MMP_LONG64 file_offset, MMP_ULONG file_orign);
MMP_USHORT MMPC_FS_FileWrite(void *FileHandle, MMP_UBYTE *uData, MMP_ULONG ulNumBytes, MMP_ULONG *ulWriteCount);
MMP_USHORT MMPC_FS_FileRead(void *FileHandle, MMP_UBYTE *uData, MMP_ULONG ulNumBytes, MMP_ULONG *ulReadCount);
MMP_USHORT MMPC_FS_FileGetSize(void *FileHandle, MMP_ULONG64 *ulFileSize);
MMP_USHORT MMPC_FS_FileTell(void *FileHandle, MMP_LONG64 *llFilePos);
MMP_ERR MMPS_FS_GetSDCID(MMP_ULONG SD_ID,MMP_BYTE *CID);

#endif // _MMPS_FS_H_
