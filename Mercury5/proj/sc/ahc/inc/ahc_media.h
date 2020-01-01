//==============================================================================
//
//  File        : ahc_media.h
//  Description : INCLUDE File for the AHC Media function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MEDIA_H_
#define _AHC_MEDIA_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_fs.h"
#include "MenuSetting.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

//For SD Card
#define SLOW_MEDIA_CLASS				(4)//Class4
#define SLOW_MEDIA_CB_THD				(3)
/*===========================================================================
 * Enum define
 *===========================================================================*/ 
 
typedef enum _AHC_MEDIA_ATTR {
	AHC_MEDIA_ATTR_WP = 0,
	AHC_MEDIA_ATTR_VOL_ID,
	AHC_MEDIA_ATTR_TYPE,
	AHC_MEDIA_ATTR_STATUS
} AHC_MEDIA_ATTR;

typedef enum _AHC_MEDIA_ID {
    AHC_MEDIA_MMC = 0,
    AHC_MEDIA_MMC1,
    AHC_MEDIA_SMC,
    AHC_MEDIA_MEMDISK,
    AHC_MEDIA_RESOURCE_FAT,
    AHC_MEDIA_FACTORY_FAT,
    AHC_MEDIA_USER_FAT,
    AHC_MEDIA_MAX_ID
} AHC_MEDIA_ID;

// Definition of Flash Storage
typedef enum _AHC_FLASH_ID {
    AHC_MEDIA_SERIAL_FLASH = 0,
    AHC_MEDIA_SDMMC,
    AHC_MEDIA_SDMMC1,
    AHC_MEDIA_NAND
} AHC_FLASH_ID;

typedef enum _MEDIA_CMD {
    MEDIA_CMD_FORMAT = 0,
   	MEDIA_CMD_GET_ATTRIBUTE,
   	MEDIA_CMD_MAX
} MEDIA_CMD;

typedef enum _AHC_SD_ID {
    AHC_SD_0 = 0,
    AHC_SD_1,
    AHC_SD_2,
    AHC_SD_3,
    AHC_SD_DEV_NUM
} AHC_SD_ID;

//MMOUNT:	Mount as Master
//NMOUNT:	Not Inserted
//SMOUNT:	Mount as Slave
typedef enum _AHC_SD_MOUNT_STATUS_ {
	AHC_SD1_NO_MOUNT_SD2_NO_MOUNT = 0,//No Card
	AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT,//Only SD1 inserted
	AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT,//SD1 acts as Master, SD2 acts as Slave
	AHC_SD1_NO_MOUNT_SD2_MASTER_MOUNT,//Only SD2 inserted
	AHC_SD1_SLAVE_MOUNT_SD2_MASTER_MOUNT//SD1 acts as Slave, SD2 acts as Master
	
}AHC_SD_MOUNT_STATUS;

#if 1
typedef enum{
	#if(defined(DEVICE_GPIO_2NDSD_PLUG))
    SDMMC_1STOUT_2NDOUT = 0,
    SDMMC_1STIN_2NDOUT,
    SDMMC_1STOUT_2NDIN,
    SDMMC_1STIN_2NDIN
    #else
    SDMMC_OUT = 0,
    SDMMC_IN
    #endif
}SDMMC_STATE;
#endif

typedef enum _AHC_CHECK_STORAGE_ALLOCATION
{
	STORATE_CHECK_FILE_NUM,
	STORATE_CHECK_FOLDER_SIZE,
	STORATE_CHECK_NUM
}AHC_CHECK_STORAGE_ALLOCATION;

/*===========================================================================
 * Struct define
 *===========================================================================*/ 

#if (SUPPORT_LONGSYS_SMART_CARD)
typedef struct _SMART_CARD_STATUS
{
	UINT32 dwDevSMARTTag;				//off:0,L:4, SMART结构体标记固定值0x96325870
	UINT32 dwDevSMARTVersions;		//off:4,L:4, 版本号
	UINT32 dwXorValue;					//off:8,L:4, 异或校验值
	UINT32 dwSizeOfDevSMART;			//off:12,L:4，本结构体的大小
	UINT32 dwOriginalBadBlock;		//off:16,L:4, 原始坏块数
	UINT32 dwIncreaseBadBlock;		//off:20,L:4, 新增坏块数
	UINT64 lwWriteAllSectNum;			//0ff:24,L:8, data written, in sector(512Byte)
	UINT32 dwReplaceBlockLeft;		//off:32,L:4, blocks for replacing
	UINT32 dwDegreOfWear;				//off:36,L:4, 平均磨损度
	UINT32 dwSectorTotal;				//off:40,L:4, 总共的扇区数
	UINT32 dwRemainLifeTime;			//off:44,L:4, 剩余寿命百分比
	UINT32 dwRemainWrGBNum;			//off:48,L:4, 剩余可写入的最大数据量
	UINT32 dwLifeTimeTotal;			//off:52,L:4, 总的擦写寿命	
}SMART_CARD_STATUS, *PSMART_CARD_STATUS;
#endif

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
 
AHC_BOOL AHC_GetImageDateTime(UINT16 *puwYear, UINT8 *puwMonth, UINT8 *puwDay, UINT8 *puwHour, UINT8 *puwMin, UINT8 *puwSec);
AHC_BOOL AHC_FormatStorageMedia(UINT8 byMediaID);
#if (FS_FORMAT_FREE_ENABLE)
AHC_BOOL AHC_FormatStorageMedia_FormatFree( UINT8 byMediaID );
AHC_BOOL AHC_CheckMedia_FormatFree( UINT8 byMediaID );
#endif
AHC_BOOL AHC_MountStorageMedia(UINT8 byMediaID);
AHC_BOOL AHC_MountStorageMediaWithoutDCF(UINT8 byMediaID);
AHC_BOOL AHC_DisMountStorageMedia(UINT8 byMediaID);
AHC_BOOL AHC_DisMountStorageMediaOnlyPhysical(UINT8 byMediaID);
AHC_BOOL AHC_GetMountStorageMediaStatus(void);
AHC_BOOL AHC_GetStorageOtherMediaStatus(UINT8 byMediaID, UINT64 *pullFreeSize);
AHC_BOOL AHC_GetStorageMediaGeometry(UINT16 *pwBytesPerSec, UINT16 *pwSecPerCluster, UINT32 *pwTotalCluster, UINT32 *pwFreelCluster);
AHC_BOOL AHC_GetStorageMediaInfo(AHC_FS_DISK_INFO* sMediaInfo);
AHC_BOOL AHC_SetMediaAttr(UINT8 byMediaID, AHC_MEDIA_ATTR bMediaAttr, UINT32 uiParam);
AHC_BOOL AHC_GetMediaAttr(UINT8 byMediaID, AHC_MEDIA_ATTR bMediaAttr, UINT32 *puiParam);
AHC_BOOL AHC_SetMediaPath(AHC_MEDIA_ID path);
AHC_MEDIA_ID AHC_GetMediaPath(void);
AHC_BOOL AHC_SwitchMediaPath(void);
AHC_BOOL AHC_RemountDevices(MEDIASETING_SETTING media);
AHC_BOOL AHC_IsSDInserted(void);
AHC_BOOL AHC_Is2ndSDInserted(void);
AHC_BOOL AHC_IsSDWriteProtect(void);
AHC_BOOL AHC_MountPhysicalDevice(UINT8 byMediaID);
AHC_BOOL AHC_UnmountPhysicalDevice(UINT8 byMediaID);
AHC_BOOL AHC_DisMountStorageMediaEx(UINT8 byMediaID, AHC_BOOL bUnmountPhysical );
AHC_BOOL AHC_UnmountVolume(UINT8 byMediaID);
AHC_BOOL AHC_ResetPhysicalDevice(UINT8 byMediaID);
AHC_BOOL AHC_GetVolumeName(INT8* pchVolume, UINT32* puiVolNameSize);
AHC_BOOL AHC_EnableDir(void);
UINT32   AHC_Media_SerialFlashFwCheckSum( void );

void AHC_Media_GetFreeSpace(UINT64 *pFreeBytes);

//SD Card Function
#if (ENABLE_SD_HOT_PLUGGING)
SDMMC_STATE AHC_SDMMC_GetState(void);
void 		AHC_SDMMC_SetState(SDMMC_STATE val);
AHC_SD_MOUNT_STATUS 	AHC_SDMMC_GetMountState(void);
void 		AHC_SDMMC_SetMountState(AHC_SD_MOUNT_STATUS val);
AHC_BOOL 	AHC_SDMMC_IsSD1MountDCF(void);
#endif
UINT8 		AHC_SDMMC_GetClass(UINT32 id);
UINT8 		AHC_SDMMC_Get1stCardClass(UINT32 id);
#if(defined(DEVICE_GPIO_2NDSD_PLUG))
AHC_BOOL 	AHC_SDMMC_IsSD2MountDCF(void);
UINT8 		AHC_SDMMC_Get2ndCardClass(UINT32 id);
#endif

AHC_BOOL AHC_DCF_IsNoFitStorageAlloc(void);

#if (SUPPORT_LONGSYS_SMART_CARD)
AHC_BOOL AHC_Media_GetSmartCardInfo(PSMART_CARD_STATUS ptSmartCardInfo);
#endif

INT8* AIHC_GetMediaRootName(void);
AHC_BOOL    AHC_SDMMC_BasicCheck(void);

#endif //_AHC_MEDIA_H_
