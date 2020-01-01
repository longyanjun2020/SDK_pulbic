
#ifndef _FS_CFG_H_
#define _FS_CFG_H_

//==============================================================================
//
//  File        : fs_cfg.h
//  Description : File System configure file
//  Author      : Rony Yeh
//  Revision    : 1.0
//==============================================================================

//#include "includes_fw.h"
//#include "config_fw.h"
//#include "lib_retina.h"
#include "config_fw.h"
#include "mmp_lib.h"

#include "mmpf_storage_api.h"
#include "FS_ConfDefaults.h"
#include "NewCache.h" //FS_NEWBUFFER
#include "fs_dev.h" //FS_NEWBUFFER
#include "mmpf_fs_api.h" //FS_NEWBUFFER

//==============================================================================
//
//                              Define
//
//==============================================================================
#define   AHC_FS_SDNEWCACHE     (1) //0:disable NEWCache 1:enable NEWCache
#if(AHC_FS_SDNEWCACHE)
#define NEWCACHEDEBUGVIEW       (0)//enable for NewCache debug info;should sync with FS_NEWCACHEDEBUGVIEW
#else
#define NEWCACHEDEBUGVIEW       (0)
#endif
//#define SD_GET_FREE_SPACE_SIZE    (8*1024)

/* pins for socket0 match the padset0 of SD0 */
#define SD_SOCKET0_MAP_ID           (0)
/* pins for socket1 match the padset0 of SD1 */
#define SD_SOCKET1_MAP_ID           (1)

/** @brief FW and MSDC device config
    Below define is AIT supported storage. Please config FS_MAX_DEVICES/MSDC_MAX_DEVICES first, then select storage.
    Support storage: "SD:\\", "SD1:\\", "SM:\\", "MEM:\\"
*/

/* config FS storage driver */
#if defined(MBOOT_FW)||defined(ALL_FW)||defined(MINIBOOT_FW)
#define FS_MAX_UNITS                (5 + USING_SD1_IF)
#endif
#if defined(UPDATER_FW)
#define FS_MAX_UNITS                (3) //Support storage: "SD:\\", "SD1:\\", "SF:\\"
#endif

#define FS_1ST_DEV                  "SF:0:\\"
#define FS_2ND_DEV                  "SF:1:\\"
#define FS_3RD_DEV                  "SF:2:\\"
#define FS_4TH_DEV                  "SF:3:\\"
#define FS_5TH_DEV                  "SD:0:\\"
#define FS_6TH_DEV                  "SD1:0:\\"

#define FS_1ST_DEV_MAX_SUPPORT_STORAGE_SIZE_MB (64)
#define FS_2ND_DEV_MAX_SUPPORT_STORAGE_SIZE_MB (64)
#define FS_3RD_DEV_MAX_SUPPORT_STORAGE_SIZE_MB (64)
#define FS_4TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB (64)
#define FS_5TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB (FS_MAX_SUPPORT_STORAGE_SIZE_GB * 1024)
#define FS_6TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB (FS_MAX_SUPPORT_STORAGE_SIZE_GB * 1024)

/* config MSDC storage driver */
#if defined(MBOOT_FW)||defined(ALL_FW)|| defined(MINIBOOT_FW)
#define MSDC_MAX_UNITS              (1 + USING_SD1_IF)  //Support storage: "SD:\\", "SD1:\\", "SM:\\", "MEM:\\" //CarDV...
#endif
#if defined(UPDATER_FW)
#define MSDC_MAX_UNITS              (1)
#endif

#if (USING_SD1_IF)
#define MSDC_1ST_DEV                "SD:0:\\"
#define MSDC_2ND_DEV                "SD1:0:\\"
#define MSDC_3RD_DEV                "SF:0:\\"
#define MSDC_4TH_DEV                "SF:1:\\"
#define MSDC_5TH_DEV                "SF:2:\\"
#define MSDC_6TH_DEV                "SF:3:\\"
#else
#define MSDC_1ST_DEV                "SD:0:\\"
#define MSDC_2ND_DEV                "SF:0:\\"
#define MSDC_3RD_DEV                "SF:1:\\"
#define MSDC_4TH_DEV                "SF:2:\\"
#define MSDC_5TH_DEV                "SF:3:\\"
#endif

    // Do not modify here.
#if (FS_1ST_DEV_MAX_SUPPORT_STORAGE_SIZE_MB > 1024) // Large than 1GB.
    #define FS_1ST_DEV_FREE_CLUSTER_TABLE_SIZE (FS_1ST_DEV_MAX_SUPPORT_STORAGE_SIZE_MB)
#else
    #define FS_1ST_DEV_FREE_CLUSTER_TABLE_SIZE (1 * 1024)
#endif
#if (FS_2ND_DEV_MAX_SUPPORT_STORAGE_SIZE_MB > 1024) // Large than 1GB.
    #define FS_2ND_DEV_FREE_CLUSTER_TABLE_SIZE (FS_2ND_DEV_MAX_SUPPORT_STORAGE_SIZE_MB)
#else
    #define FS_2ND_DEV_FREE_CLUSTER_TABLE_SIZE (1 * 1024)
#endif
#if (FS_3RD_DEV_MAX_SUPPORT_STORAGE_SIZE_MB > 1024) // Large than 1GB.
    #define FS_3RD_DEV_FREE_CLUSTER_TABLE_SIZE (FS_3RD_DEV_MAX_SUPPORT_STORAGE_SIZE_MB)
#else
    #define FS_3RD_DEV_FREE_CLUSTER_TABLE_SIZE (1 * 1024)
#endif
#if (FS_4TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB > 1024) // Large than 1GB.
    #define FS_4TH_DEV_FREE_CLUSTER_TABLE_SIZE (FS_4TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB)
#else
    #define FS_4TH_DEV_FREE_CLUSTER_TABLE_SIZE (1 * 1024)
#endif
#if (FS_5TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB > 1024) // Large than 1GB.
    #define FS_5TH_DEV_FREE_CLUSTER_TABLE_SIZE (FS_5TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB)
#else
    #define FS_5TH_DEV_FREE_CLUSTER_TABLE_SIZE (1 * 1024)
#endif
#if (FS_6TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB > 1024) // Large than 1GB.
    #define FS_6TH_DEV_FREE_CLUSTER_TABLE_SIZE (FS_6TH_DEV_MAX_SUPPORT_STORAGE_SIZE_MB)
#else
    #define FS_6TH_DEV_FREE_CLUSTER_TABLE_SIZE (1 * 1024)
#endif

#if (FS_SUPPORT_CACHE)
#define FS_CACHE_LENGTH (8*1024)
#endif

//==============================================================================
//
//                              Extern Variable
//
//==============================================================================

#if (AHC_FS_SDNEWCACHE)
extern void FS__AddCacheDeviceMap(FS_CACHE_DEVICE_MAP *pCacheDevMap);
//extern void FS__AddCacheRWAPIMap(const FS_CACHE_API *pCacheRWAPIMap);
extern const FS_DEVICE_TYPE FS_MMC_CardMode_SDCacheDriver;
//extern const FS_CACHE_API _NewCacheRWAPI;
#if defined (ALL_FW)
#define   FS_MMC_CardMode_SDDriverType   (SDCacheInfo.pCacheDeviceMap->pSelf)
#else
#define   FS_MMC_CardMode_SDDriverType   (&FS_MMC_CardMode_Driver)
#endif
#else
#define   FS_MMC_CardMode_SDDriverType   (&FS_MMC_CardMode_Driver)
#endif

#if (FS_SUPPORT_CACHE)
#if (FS_MULTI_CACHE)
extern MMP_ULONG acCacheMemory[FS_MAX_UNITS][(FS_CACHE_LENGTH>>2)*3];
#else
extern MMP_ULONG acCacheMemory[FS_MAX_UNITS][FS_CACHE_LENGTH>>2];
#endif
#endif

#if (FS_NEW_GET_FREE_SPACE == 1)||(FS_SUPPORT_FAST_FORMAT == 1)
#if (FS_NEW_GET_FREE_SPACE == 1)&&(FS_NEW_SEARCH_FREE_CLUSTER == 1)
extern MMP_UBYTE *m_ubSDFreeClusterTable[FS_MAX_UNITS];
#endif
#endif

/* gpFS_Device are devices AIT FileSystem support */
extern STORAGE_UNIT gpFS_DeviceCustom[FS_MAX_UNITS];

/* gpMSDC_Device are devices AIT MSDC support */
extern STORAGE_UNIT gpMSDC_DeviceCustom[MSDC_MAX_UNITS];

/*********************************************************************
*
*       Declaration
*/
int FS_Init(void); // FS_NEWBUFFER


#endif //_FS_CFG_H_
