/*
**********************************************************************
*                          Micrium, Inc.
*                      949 Crestview Circle
*                     Weston,  FL 33327-1848
*
*                            uC/FS
*
*             (c) Copyright 2001 - 2006, Micrium, Inc.
*                      All rights reserved.
*
***********************************************************************

----------------------------------------------------------------------
File        : fs_api.h
Purpose     : Define global functions and types to be used by an
              application using the file system.

              This file needs to be included by any modul using the
              file system.
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FS_API_H_
#define _FS_API_H_


/*********************************************************************
*
*             #include Section
*
**********************************************************************
*/

#include "FS_ConfDefaults.h"        /* FS Configuration */
#include "gui_global.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*             #define constants
*
**********************************************************************
*/

/* File system version */
#define FS_VERSION                26030UL

/* Global error codes */
#define FS_ERR_OK                 0
#define FS_ERR_EOF                -1
#define FS_ERR_DISKFULL           -2
#define FS_ERR_INVALIDPAR         -3
#define FS_ERR_CMDNOTSUPPORTED    -4
#define FS_ERR_WRITEONLY          -5
#define FS_ERR_READONLY           -6
#define FS_ERR_READERROR          -7
#define FS_ERR_WRITEERROR         -8
#define FS_ERR_DISKCHANGED        -128
#define FS_ERR_CLOSE              -144
#define FS_ERR_INVALIDDESC        -160 /* Invalid media descriptor, media corrupt */
#define FS_ERR_DEVICETIMEOUT      -176 /* Device did not respond or timed out */
#define FS_ERR_NOMEDIAPRESENT     -192 /* No media in device present */
// [AIT define]
#define FS_ERR_PATH_NOT_FOUND    		-193
#define FS_ERR_FILE_NOT_FOUND    		-194
#define FS_ERR_DIR_EXIST                -195

#define FS_ERR_OLD_PATH_NOT_FOUND       -196
#define FS_ERR_NEW_PATH_NOT_FOUND       -197
#define FS_ERR_NEW_ENTRY_EXIST       	-198
#define FS_ERR_OLD_ENTRY_NOT_FOUND		-199

#define FS_ERR_BURST_WRITEERROR         -201

/* Global constants*/
/* File Positions */
#define FS_SEEK_CUR               1
#define FS_SEEK_END               2
#define FS_SEEK_SET               0

#define FS_FILE_CURRENT           FS_SEEK_CUR
#define FS_FILE_END               FS_SEEK_END
#define FS_FILE_BEGIN             FS_SEEK_SET

/*********************************************************************
*
*       I/O commands for logical block layer (LBL)
*/
#define FS_CMD_READ_SECTOR        1000
#define FS_CMD_WRITE_SECTOR       1001

/*********************************************************************
*
*       I/O commands for driver
*/
#define FS_CMD_CHK_DSKCHANGE      1002    /* Obsolete */
#define FS_CMD_REQUIRES_FORMAT    1003
#define FS_CMD_GET_DEVINFO        1004
#define FS_CMD_FORMAT_LOW_LEVEL   1005     /* Used internally by FS_FormatLow() to command the driver to perform low-level format */
#define FS_CMD_FREE_SECTORS       1006     /* Used internally: Allows the FS layer to inform driver about free sectors */
#define FS_CMD_SET_DELAY          1007     /* Used in the simulation to simulate a slow device with RAM driver */
#define FS_CMD_UNMOUNT_VOLUME     1008     /* Used internally by FS__Unmount() to inform the driver */
// [sunny20070209] add for support host usb api
#define FS_CMD_WRITE_PROTECT      1009
#define FS_CMD_CARD_DETECT        1010
#define FS_CMD_FINISH_WRITE       1011
#define FS_CMD_PWR_DISABLE        1012
#define FS_CMD_SWITCH_BOOT_AREA    1013
#define FS_CMD_CONFIG_MOVINAND_BOOTSIZE 1014
#define FS_CMD_SET_SDMMC_BUFFER         1015
#define FS_CMD_GET_SDMMC_BUFFER         1016
#define FS_CMD_SET_SDMMC_PARTITION      1017
#define FS_CMD_GET_PARTITION_NUM        1018
#define FS_CMD_RESET_STORAGE            1019

#define FS_CMD_UNMOUNT_DEVICE           1020
#define FS_CMD_MOUNT_DEVICE             1021
#define FS_CMD_SF_USERCOPY              1022

#define FS_USERCOPYSF2TOSF3            (0x02)
#define FS_USERCOPYSF3TOSF2            (0x03)
// [sunny20070209]
/*********************************************************************
*
*       File system commands
*/
#define FS_CMD_GET_DISKFREE       4000L     /* Obsolete, do no use any more ! */
#define FS_CMD_GET_TOTAL_SPACE    4001L     /* Obsolete, do no use any more ! */

/*********************************************************************
*
*       CACHE Commands (internal)
*/
#define FS_CMD_CACHE_SET_MODE     6000L
#define FS_CMD_CACHE_CLEAN        6001L   /* Write out all dirty sectors */
#define FS_CMD_CACHE_SET_QUOTA    6002L
#define FS_CMD_CACHE_FREE_SECTORS 6003L
#define FS_CMD_CACHE_INVALIDATE   6004L   /* Invalidate all sectors in cache */

#define FS_CMD_CACHE_CLEANBYSECTOR 		6005L
#define FS_CMD_CACHE_GETCACHEMODE  		6006L
#define FS_CMD_CACHE_UPDATEWRITESIZE 	6007L
#define FS_CMD_CACHE_SETMAXWRITESIZE 	6008L

/*********************************************************************
*
*       Directory entry attribute definitions
*/
#define FS_ATTR_READ_ONLY    0x01
#define FS_ATTR_HIDDEN       0x02
#define FS_ATTR_SYSTEM       0x04
#define FS_ATTR_ARCHIVE      0x20
#define FS_ATTR_DIRECTORY    0x10

/*********************************************************************
*
*       Sector type defines
*/
#define FS_SECTOR_TYPE_DATA    0
#define FS_SECTOR_TYPE_DIR     1
#define FS_SECTOR_TYPE_MAN     2
#define FS_SECTOR_TYPE_COUNT   3   /* Number of sector types */

/*********************************************************************
*
*       Sector type defines
*/
#define FS_SECTOR_TYPE_MASK_DATA    (1 << FS_SECTOR_TYPE_DATA)
#define FS_SECTOR_TYPE_MASK_DIR     (1 << FS_SECTOR_TYPE_DIR)
#define FS_SECTOR_TYPE_MASK_MAN     (1 << FS_SECTOR_TYPE_MAN)
#define FS_SECTOR_TYPE_MASK_ALL     (FS_SECTOR_TYPE_MASK_DATA | FS_SECTOR_TYPE_MASK_DIR | FS_SECTOR_TYPE_MASK_MAN)

/*********************************************************************
*
*       CheckDisk error codes
*/
enum {
  FS_ERRCODE_0FILE = 0x100,
  FS_ERRCODE_SHORTEN_CLUSTER,
  FS_ERRCODE_CROSSLINKED_CLUSTER,
  FS_ERRCODE_FEW_CLUSTER,
  FS_ERRCODE_CLUSTER_UNUSED,
  FS_ERRCODE_CLUSTER_NOT_EOC
};

/*********************************************************************
*
*       Internal data types, used as opaque types for pointers
*
**********************************************************************
*/
typedef struct FS_CACHE_API   FS_CACHE_API;
typedef struct FS_DEVICE      FS_DEVICE;
typedef struct FS_DIR         FS_DIR;
typedef struct FS_FILE        FS_FILE;
typedef struct FS_PARTITION   FS_PARTITION;
typedef struct FS_VOLUME      FS_VOLUME;
typedef struct FS_DEVICE_TYPE FS_DEVICE_TYPE;

/*********************************************************************
*
*       Global data types
*
**********************************************************************
*/

typedef int FS_QUERY_F_TYPE(int ErrCode, ...);
typedef void FS_BUSY_LED_CALLBACK(U8 OnOff);

typedef struct {
  U32 total_clusters;
  U32 avail_clusters;
  U16 sectors_per_cluster;
  U16 bytes_per_sector;
} FS_DISKFREE_T;

typedef struct {
  U32 NumTotalClusters;
  U32 NumFreeClusters;
  U16 SectorsPerCluster;
  U16 BytesPerSector;
} FS_DISK_INFO;

typedef struct {
  U16 NumHeads;          /* Relevant only for mechanical drives   */
  U16 SectorsPerTrack;   /* Relevant only for mechanical drives   */
  U32 NumSectors;        /* Total number of sectors on the medium */
  U16 BytesPerSector;    /* Number of bytes per sector            */
} FS_DEV_INFO;

typedef struct {
  U16        SectorsPerCluster;
  U16        NumRootDirEntries;    /* Proposed, actual value depends on FATType */
  FS_DEV_INFO * pDevInfo;
} FS_FORMAT_INFO;


typedef struct _FS_FILETIME{
  U16 Year;
  U16 Month;
  U16 Day;
  U16 Hour;
  U16 Minute;
  U16 Second;
} FS_FILETIME;

/*********************************************************************
*
*             Non blocking (backgrounded) file I/O functions
*/
/* Information for background data */
typedef struct FS_BG_DATA {
  struct FS_BG_DATA * pNext;
  U32                 NumBytes;
  U32                 NumBytesRem;         /* Remaining bytes to transfer */
  void              * pData;
  FS_FILE           * pFile;
  U8                  Operation;
  void (*pfOnCompletion) (void * pData);   /* Optional completion routine */
  void              * pCompletionData;     /* Optional data for completion routine */
  char                IsCompleted;
} FS_BG_DATA;

void FS_Daemon(void);
void FS_FReadNonBlock (void       * pData,
                       U32          NumBytes,
                       FS_FILE    * pFile,
                       FS_BG_DATA * pBGData,                    /* User supplied management block */
                       void (*pfOnCompletion) (void * pData),   /* Optional completion routine */
                       void * pCompletionData                   /* Optional data for completion routine */
                      );
void FS_FWriteNonBlock(const void * pData,
                       U32          NumBytes,
                       FS_FILE    * pFile,
                       FS_BG_DATA * pBGData,                    /* User supplied management block */
                       void (*pfOnCompletion) (void * pData),   /* Optional completion routine */
                       void * pCompletionData                   /* Optional data for completion routine */
                       );
char FS_IsCompleted(FS_BG_DATA * pBGData);

/*********************************************************************
*
*       Directory types
*/
typedef struct FS_DIRENT {
  char  DirName[FS_DIRNAME_MAX * 3];
  U8    Attributes;
  U32   Size;
  U32   TimeStamp;
  U32	FirstCluster;
} FS_DIRENT;


/*********************************************************************
*
*       Global function prototypes
*
**********************************************************************
*/

/*********************************************************************
*
*       "Standard" file I/O functions
*/
FS_FILE *        FS_FOpen (const char * pFileName, const char * pMode);
int              FS_FClose(FS_FILE    * pFile);
FS_SIZE_T        FS_FRead (      void * pData, FS_SIZE_T Size, FS_SIZE_T N, FS_FILE * pFile);
FS_SIZE_T        FS_FWrite(const void * pData, FS_SIZE_T Size, FS_SIZE_T N, FS_FILE * pFile);

/*********************************************************************
*
*       Non-standard file I/O functions
*/
U32           FS_Read (FS_FILE * pFile,       void * pData, U32 NumBytes);
U32           FS_Write(FS_FILE * pFile, const void * pData, U32 NumBytes);

/*********************************************************************
*
*       file pointer handling
*/
int              FS_FSeek       (FS_FILE * pFile, I32 Offset,         int Origin);
int              FS_SetEndOfFile(FS_FILE * pFile);
int              FS_SetFilePos  (FS_FILE * pFile, I32 DistanceToMove, int MoveMethod);
I32              FS_GetFilePos  (FS_FILE * pFile);
I32              FS_FTell       (FS_FILE * pFile);

/*********************************************************************
*
*       I/O error handling
*/
int              FS_FEof        (FS_FILE * pFile);
I16              FS_FError      (FS_FILE * pFile);
void             FS_ClearErr    (FS_FILE * pFile);
const char *     FS_ErrorNo2Text(int       ErrCode);

/*********************************************************************
*
*       file protect
*/

int FS_SetMaxWriteSize(FS_FILE * pFile, unsigned int Size);

/*********************************************************************
*
*       file functions
*/

int              FS_CopyFile   (const char * sSource,       const char * sDest);
U32              FS_GetFileSize(FS_FILE    * pFile);
U32				 FS_GetFilePhyFirstSector(FS_FILE * ulFileID);	
int              FS_Move       (const char * sExistingName, const char * sNewName);
int              FS_Remove     (const char * pFileName);
int              FS_Rename     (const char * sOldName,      const char * sNewName);
int              FS_Truncate   (FS_FILE    * pFile,         U32          NewSize);
int              FS_Verify     (FS_FILE    * pFile,         const void * pData, U32 NumBytes);

/*********************************************************************
*
*       IOCTL
*/
int              FS_IoCtl(const char *pDevName, I32 Cmd, I32 Aux, void *pBuffer);

/*********************************************************************
*
*       FS_Volume
*/
int              FS_GetVolumeName     (int Index, char * pBuffer, int MaxSize);
U64              FS_GetVolumeSize     (const char * sVolume);
U64              FS_GetVolumeFreeSpace(const char * sVolume);
int              FS_GetNumVolumes     (void);
FS_VOLUME *      FS_AddDevice         (const FS_DEVICE_TYPE * pDevType);
void             FS_Unmount           (const char * sVolume);
int              FS_Mount             (const char * sVolume);
int              FS_GetVolumeInfo     (const char * sVolume, FS_DISK_INFO * pInfo);
int              FS_IsVolumeMounted   (const char * sVolumeName);
U8               FS_CheckMediumPresent(const char * sVolume);
int              FS_GetVolumeLabel    (const char * sVolume, char * pVolumeLabel, unsigned VolumeLabelSize);
int              FS_SetVolumeLabel    (const char * sVolume, const char * pVolumeLabel);
void 			 FS_ConnectFCTable(const char * sVolumeName, U8 bEnable, U8 *pTable, U32 ulTableSize);

/*********************************************************************
*
*       FS_Attrib
*/
int              FS_SetFileAttributes(const char * pName, U8 Attributes);
U8               FS_GetFileAttributes(const char * pName);
int 			 FS_GetFileInfo(const char * pName, U8 * pAttributes, U32 * pTimeStamp, U32 * pFileSize);

/*********************************************************************
*
*       FS_Time
*/
int              FS_SetFileTime        (const char *        pName,     U32            TimeStamp);
int              FS_GetFileTime        (const char *        pName,     U32 *         pTimeStamp);
void             FS_TimeStampToFileTime(U32                 TimeStamp, FS_FILETIME * pFileTime);
void             FS_FileTimeToTimeStamp(const FS_FILETIME * pFileTime, U32 *         pTimeStamp);


/*********************************************************************
*
*       FS_GetNumFilesOpen
*/
int              FS_GetNumFilesOpen(void);


/*********************************************************************
*
*       directory functions
*/
#if FS_POSIX_DIR_SUPPORT
void             FS_DirEnt2Attr(FS_DIRENT * pDirEnt, U8   * pAttr);
void             FS_DirEnt2Name(FS_DIRENT * pDirEnt, char * pBuffer);
U32              FS_DirEnt2Size(FS_DIRENT * pDirEnt);
U32              FS_DirEnt2Time(FS_DIRENT * pDirEnt);
U32              FS_DirEnt2FirstCluster(FS_DIRENT * pDirEnt);
U32              FS_GetNumFiles(FS_DIR * pDir);
// [sunny@061020]
U32              FS_GetNumDirs(FS_DIR *pDir);
FS_DIR    *      FS_OpenDir(const char * pDirName);
int              FS_CloseDir(FS_DIR    * pDir);
FS_DIRENT *      FS_ReadDir(FS_DIR     * pDir);
void             FS_RewindDir(FS_DIR   * pDir);
int              FS_MkDir(const char   * pDirName);
int              FS_RmDir(const char   * pDirName);
#endif  /* FS_POSIX_DIR_SUPPORT */


/*********************************************************************
*
*       File system standard application
*/
void FSTask(void);
/*********************************************************************
*
*       File system control functions
*/
//int              FS_Init          (void); //FS_NEWBUFFER
int              FS_Exit          (void);

/*********************************************************************
*
*       Formatting
*/
int              FS_Format   (const char *pDevice, FS_FORMAT_INFO * pFormatInfo);
int              FS_FormatLow(const char *pDevice);


/*********************************************************************
*
*       CheckDisk functionality
*/
const char * FS_FAT_CheckDisk_ErrCode2Text(int ErrCode);
int          FS_FAT_CheckDisk(const char * sVolumeName, void *pBuffer, U32 BufferSize, int MaxRecursionLevel, FS_QUERY_F_TYPE * pfOnError);


/*********************************************************************
*
*       Space information functions
*/
U32           FS_GetFreeSpace (const char *pDevName, U8 DevIndex);
U32           FS_GetTotalSpace(const char *pDevName, U8 DevIndex);

/*********************************************************************
*
*       Debug support
*/
void             FS_X_Log     (const char *s);
void             FS_X_Warn    (const char *s);
void             FS_X_ErrorOut(const char *s);

/*********************************************************************
*
*       BusyLED support
*/
void FS_SetBusyLEDCallback(const char * sVolumeName, FS_BUSY_LED_CALLBACK * pfBusyLEDCallback);

/*********************************************************************
*
*       Device Drivers
*
*/
extern const FS_DEVICE_TYPE    FS_RAMDISK_Driver;       /* RAMDISK_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_WINDRIVE_Driver;      /* WINDRIVE_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_SMC_Driver;           /* SMC_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_MMC_CardMode_Driver;  /* MMC_DRIVER SPI function table */
extern const FS_DEVICE_TYPE    FS_MMC1_CardMode_Driver; /* MMC_DRIVER SPI function table */
extern const FS_DEVICE_TYPE    FS_MMC_SPI_Driver;       /* MMC_DRIVER CardMode function table */
extern const FS_DEVICE_TYPE    FS_IDE_Driver;           /* IDE_CF_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_FLASH_Driver;         /* FLASH_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_SFLASH_Driver;        /* Serial FLASH_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_GENERIC_Driver;       /* GENERIC_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_NAND2K_Driver;        /* Nand2k driver function table */
extern const FS_DEVICE_TYPE    FS_MEMORY_Driver;        /* Memory driver function table */
extern const FS_DEVICE_TYPE    FS_SFNAND_Driver;        /* SFNAND_DRIVER function table <SPI Nand Flash><SFNAND> */

/*********************************************************************
*
*             FLASH driver specific
*/

/*********************************************************************
*
*             FLASH driver types
*/
typedef struct {
  U32 Off;
  U32 Size;
  U32 EraseCnt;
  U16 NumUsedSectors;
  U16 NumFreeSectors;
  U16 NumEraseableSectors;
} FS_FLASH_SECTOR_INFO;

typedef struct {
  U32 NumPhysSectors;
  U32 NumLogSectors;
  U32 NumUsedSectors;   /* Number of used logical sectors */
} FS_FLASH_DISK_INFO;

/*********************************************************************
*
*       FLASH driver
*/
void FS_FLASH_GetDiskInfo  (U8 Unit, FS_FLASH_DISK_INFO * pDiskInfo);
void FS_FLASH_GetSectorInfo(U8 Unit, U32 PhysSectorIndex, FS_FLASH_SECTOR_INFO * pSectorInfo);

/*********************************************************************
*
*       RAMDISK driver
*/
void FS_RAMDISK_Configure(U8 Unit, void * pData, U16 BytesPerSector, U32 NumSectors);

/*********************************************************************
*
*       MMC/SD driver
*/
void FS_MMC_ActivateCRC(void);
void FS_MMC_DeactivateCRC(void);
/*********************************************************************
*
*       Cache handling
*/
#if FS_SUPPORT_CACHE

/*********************************************************************
*
*       Cache mode defines
*/
#define FS_CACHE_MODE_R         0x01
#define FS_CACHE_MODE_W         0x02
#define FS_CACHE_MODE_D         0x04
#define FS_CACHE_MODE_FULL      (FS_CACHE_MODE_R | FS_CACHE_MODE_W | FS_CACHE_MODE_D)


/*********************************************************************
*
*       Cache specific defines
*/
#define FS_CACHE_NONE      NULL
#define FS_CACHE_MAN       FS_CacheMan_Init
#define FS_CACHE_RW        FS_CacheRW_Init 
#define FS_CACHE_RW_QUOTA  FS_CacheRWQuota_Init
#define FS_CACHE_ALL       FS_CacheAll_Init
#define FS_CACHEALL_API    FS_CacheAll_Init    /* For compatibility with older version */
#define FS_CACHEMAN_API    FS_CacheMan_Init    /* For compatibility with older version */
/*********************************************************************
*
*       Cache specific types
*/
typedef U32 FS_INIT_CACHE (FS_DEVICE * pDevice, void * pData,   I32 NumBytes);

/*********************************************************************
*
*       Cache specific prototypes
*/
U32    FS_AssignCache   (const char * pName, void * pData, I32 NumBytes, FS_INIT_CACHE * pfInit);

int    FS_CACHE_Clean   (const char * pName);

void   FS_CACHE_Invalidate (const char * pName);
int    FS_CACHE_Command (const char * pName, int Cmd,      void * pData);
int    FS_CACHE_SetMode (const char * pName, int TypeMask, int    ModeMask);
int    FS_CACHE_SetQuota(const char * pName, int TypeMask, U32    NumSectors);

/*********************************************************************
*
*       Cache initialization prototypes
*/
U32 FS_CacheAll_Init    (FS_DEVICE * pDev, void * pData, I32 NumBytes);
U32 FS_CacheMan_Init    (FS_DEVICE * pDev, void * pData, I32 NumBytes);
U32 FS_CacheRW_Init     (FS_DEVICE * pDev, void * pData, I32 NumBytes);
U32 FS_CacheRWQuota_Init(FS_DEVICE * pDev, void * pData, I32 NumBytes);

#endif

#if defined(__cplusplus)
  }              /* Make sure we have C-declarations in C++ programs */
#endif

#endif  /* _FS_API_H_ */

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	   		 		      		       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
