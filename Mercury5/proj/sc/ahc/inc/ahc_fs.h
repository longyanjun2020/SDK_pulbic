//==============================================================================
//
//  File        : ahc_fs.h
//  Description : INCLUDE File for the AHC DCF function porting.
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file ahc_fs.h
 *  @brief Header File for the Host File System API.
 *  @author Ricky Yeh, Sunny
 *  @version 1.0
 */

#ifndef _AHC_FS_H_
#define _AHC_FS_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "AHC_Config_SDK.h"

/** @addtogroup AHC_FS
@{
*/
/*===========================================================================
 * Macro define
 *===========================================================================*/
 
/**@brief ID for NAND flash reset
*/
#define	AHC_FS_RESET_SM 	1

/**@brief ID for SD card reset
*/
#define	AHC_FS_RESET_SD 	2

//  for AHC_FS_FileSeek()
/**@brief seek from begin define for AHC_FS_FileSeek()
*/
#define  AHC_FS_SEEK_SET	0

/**@brief seek from current define for AHC_FS_FileSeek()
*/
#define  AHC_FS_SEEK_CUR	1

/**@brief seek from end define for AHC_FS_FileSeek()
*/
#define  AHC_FS_SEEK_END	2

// for  AHC_FS_GetFileList()
/**@brief filter option for AHC_FS_GetFileList()
    set bit of infomation user want to get file name from AHC_FS_GetFileList
*/
#define AHC_FILE_NAME		0x01

/**@brief filter option for AHC_FS_GetFileList()
    set bit of infomation user want to get file attribute from AHC_FS_GetFileList
*/
#define AHC_ATTRIBUTE		0x02

/**@brief filter option for AHC_FS_GetFileList()
    set bit of infomation user want to get file time from AHC_FS_GetFileList
*/
#define AHC_FILE_TIME		0x04

/**@brief filter option for AHC_FS_GetFileList()
    set bit of infomation user want to get file size from AHC_FS_GetFileList
*/
#define AHC_ENTRY_SIZE		0x08

/*===========================================================================
 * Structure define
 *===========================================================================*/

/**
 * ( Host Application Layer) directory entry time structure.
 */
typedef struct _AHC_FS_FILETIME {
	UINT16 		usYear;      	///< Represents the year. The year must be greater than 1980.
	UINT16 		usMonth;     	///< Represents the month, where January = 1, February = 2, ...
	UINT16 		usDay;       	///< Represents the day of the month(1-31).
	UINT16 		usHour;      	///< Represents the hour of the day(0-23).
	UINT16 		usMinute;    	///< Represents the minute of the day(0-59).
	UINT16 		usSecond;    	///< Represents the second(0-59)
} AHC_FS_FILETIME;

typedef struct _AHC_FS_CONFIG {
	AHC_BOOL	bUseSD;			///< SD/MMC is used in the file system
	AHC_BOOL	bUseNAND;		///< NAND is used in the file system
	UINT32		ulNANDMemory;	///< NAND temperory used memory. depend on NAND type
} AHC_FS_CONFIG;

typedef struct _AHC_FS_IOCTL_PARA {
    UINT32   	ulPara[2];
} AHC_FS_IOCTL_PARA;

typedef struct _AHC_FS_DISK_INFO {
    UINT32  	ulTotalClusters; ///< Total number of clusters
    UINT32  	ulFreeClusters;  ///< Number of free clusters
    UINT16 		usSecPerCluster; ///< Number of sectors per cluster
    UINT16 		usBytesPerSector;///< Number of bytes per sector
} AHC_FS_DISK_INFO;

/*===========================================================================
 * Enum define
 *===========================================================================*/

// for MMPD_FS_FileDirGetAttributes() & MMPD_FS_FileDirSetAttributes()
typedef enum _AHC_FS_ATTRIBUTE
{
    AHC_FS_ATTR_READ_ONLY 	= 0x1,	///< The file or directory is read-only. Applications can read the file but can not write
                                    ///<            to it or delete it. In the case of a directory, applications can not delete it.
    AHC_FS_ATTR_HIDDEN 		= 0x02,	///< The file or directory is hidden. It is not included in an ordinary directory listing.
    AHC_FS_ATTR_SYSTEM 		= 0x04,	///< The file or directory is part of, or is used exclusively by, the operating system.
    AHC_FS_ATTR_DIRECTORY 	= 0x10,	///< The given bpName is a directory.
    AHC_FS_ATTR_ARCHIVE 	= 0x20	///< The file or directory is an archive file or directory.
                                    ///<            Applications can use this attribute to mark files for backup or removal.
} AHC_FS_ATTRIBUTE;

typedef enum _AHC_FS_IOCTL_CMD {
    AHC_FS_CMD_RESET_STORAGE = 0,
    AHC_FS_CMD_GET_DEVINFO,
    AHC_FS_CMD_READ_SECTOR,
    AHC_FS_CMD_WRITE_SECTOR,
    AHC_FS_CMD_WRITE_PROTECT,
    AHC_FS_CMD_CARD_DETECT,
    AHC_FS_CMD_FINISH_WRITE,
    AHC_FS_CMD_PWR_DISABLE,
    AHC_FS_CMD_GET_CARDSTATUS,
    AHC_FS_CMD_RESET_MEDIUM,
    AHC_FS_CMD_UNMOUNT_MEDIUM,
    AHC_FS_CMD_MOUNT_MEDIUM
} AHC_FS_IOCTL_CMD;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_ERR	AHC_FS_FileOpen(INT8 *bFileName, UINT32 ulNameSize, INT8 *bMode, UINT32 ulModeSize, UINT32 *ulFileId);
AHC_ERR	AHC_FS_FileClose(UINT32 ulFileId);
AHC_ERR AHC_FS_FileRead(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulReadCount);
AHC_ERR AHC_FS_FileWrite(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulWriteCount);
AHC_ERR AHC_FS_FileSeek(UINT32 ulFileId, INT64 llOffset, UINT32 ulOrigin);
AHC_ERR AHC_FS_FileTell(UINT32 ulFileId, INT64 *llFilePos);
AHC_ERR AHC_FS_FileCopy(INT8 *bSrc, UINT32 ulSrcSize, INT8 *bDest,UINT32 ulDestSize);
AHC_ERR AHC_FS_FileTruncate(UINT32 ulFileId, UINT32 ulNewSize);

AHC_ERR	AHC_FS_FileGetSize(UINT32 ulFileId, UINT32 *ulFileSize);
AHC_ERR	AHC_FS_FileRemove(INT8 *bpFileName, UINT32 ulNameSize);
AHC_ERR	AHC_FS_FileDirGetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute);
AHC_ERR	AHC_FS_FileDirGetInfo(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME *timestructure, UINT32 *ulpFileSize);
AHC_ERR	AHC_FS_FileDirGetTime(INT8 *bpName, UINT32 ulNameSize, AHC_FS_FILETIME *timestructure);
AHC_ERR	AHC_FS_FileDirMove(INT8 *bpNameSrc, UINT32 ulSrcSize, INT8 *bpNameDest, UINT32 ulDestSize);
AHC_ERR	AHC_FS_FileDirRename(INT8 *bpOldName, UINT32 ulOldNameSize, INT8 *bpNewName, UINT32 ulNewNameSize);
AHC_ERR	AHC_FS_FileDirSetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE attribute);
AHC_ERR	AHC_FS_FileDirSetTime(INT8 *bpName, UINT32 ulNameSize, AHC_FS_FILETIME* pTimeStru);

AHC_ERR AHC_FS_DirClose(UINT32 ulDirID);
AHC_ERR	AHC_FS_DirGetNumFiles(UINT32 ulDirID, UINT32 *ulFileCount);
AHC_ERR	AHC_FS_DirCreate(INT8 *bDirName, UINT32 ulNameSize);
AHC_ERR	AHC_FS_DirOpen(INT8 *bDirName, UINT32 ulNameSize, UINT32 *ulDirID);
AHC_ERR	AHC_FS_DirRewind(UINT32 ulDirID);
AHC_ERR	AHC_FS_DirRemove(INT8 *bpDirName, UINT32 ulNameSize);

AHC_ERR	AHC_FS_HighLevelFormat(INT8 *bpDevice, UINT32 ulNameSize);
AHC_ERR AHC_FS_GetStorageFreeSpace(UINT8 byMediaID, UINT64 *ulpFreeBytes);
AHC_ERR	AHC_FS_GetFreeSpace(INT8 *bpVolume, UINT32 ulNameSize, UINT64 *ulpFreeBytes);
AHC_ERR	AHC_FS_GetTotalSpace(INT8 *bpVolume, UINT32 ulNameSize, UINT64 *ulpTotal);
AHC_ERR	AHC_FS_GetNumVolumes(INT32 *lpNumVols);
AHC_ERR	AHC_FS_GetVolumeName(INT32 lIndex, INT8 *bpBuffer, INT32 lBufferSize, INT32 *lpVolNamLen);
AHC_ERR	AHC_FS_IsVolumeMounted(INT8 *bpVolume, UINT32 ulNameSize);
AHC_ERR	AHC_FS_CheckMediumPresent(INT8 *bpVolume, UINT32 ulNameSize, UINT8 *ubpValue);
AHC_ERR AHC_FS_GetVolumeInfo(INT8 *bpVolume, UINT32 ulNameSize, AHC_FS_DISK_INFO *pInfo);
AHC_ERR AHC_FS_GetFileList(UINT32 ulDirId, UINT8 ubInfoMode, INT8* bBuffer,
                           AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME* filetime, UINT32* ulEntrySize);
AHC_ERR AHC_FS_GetDBFileList(UINT32 ulDirId, INT8* bBuffer, AHC_FS_ATTRIBUTE *attribute, UINT32* ulFileID);
AHC_ERR AHC_FS_SetCreationTime(void);
AHC_ERR AHC_FS_DirGetNumDirs(UINT32 ulDirID, UINT32 *ulDirCount);
AHC_ERR AHC_FS_IOCtl(INT8 *bpDeviceName, UINT32 ulNameSize
                     ,AHC_FS_IOCTL_CMD Cmd, AHC_FS_IOCTL_PARA *Aux, void *pBuffer);
AHC_ERR AHC_FS_Initialize(void);
AHC_ERR AHC_FS_MountVolume(INT8 *bpVolume, UINT32 ulNameSize);
AHC_ERR AHC_FS_UnmountVolume(INT8 *bpVolume, UINT32 ulNameSize);

void AHC_TimeStamp2FileTime(UINT32 ulTimeStamp, AHC_FS_FILETIME * pFileTime);
void AHC_FileTime2TimeStamp(const AHC_FS_FILETIME * pFileTime, UINT32 * ulpTimeStamp);

/// @}

#endif // _AHC_FS_H_
