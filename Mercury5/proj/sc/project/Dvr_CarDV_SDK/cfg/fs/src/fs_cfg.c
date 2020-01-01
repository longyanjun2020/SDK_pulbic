//==============================================================================
//
//  File        : FS_cfg.c
//  Description : File System configure file
//  Author      : Rony Yeh
//  Revision    : 1.0
//==============================================================================

#include "AIT_Init.h"
#include "fs_cfg.h"

#if defined(__GNUC__)
#include "vm_types.ht"
#endif

//==============================================================================
//
//                              EXTERNAL FUNC
//
//==============================================================================

extern void _SD_DevSetPad(MMP_ULONG ulPad);

//==============================================================================
//
//                              Structure
//
//==============================================================================

typedef struct _FCTABLE_LIST 
{
    MMP_UBYTE *ubTableAddress;
	MMP_ULONG  ulTableLength;
}FCTABLE_LIST;

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

#if (FS_SUPPORT_CACHE)
//__align(8)        MMP_ULONG acCache[2];	//Ted remove after verifying all function
#if (FS_MULTI_CACHE)
__align(8)        MMP_ULONG acCacheMemory[FS_MAX_UNITS][(FS_CACHE_LENGTH>>2)*3];
#else
__align(8)        MMP_ULONG acCacheMemory[FS_MAX_UNITS][FS_CACHE_LENGTH>>2];
#endif
#endif

#if (FS_NEW_GET_FREE_SPACE == 1)||(FS_SUPPORT_FAST_FORMAT == 1)
//#define	SD_GET_FREE_SPACE_SIZE	(8*1024)
//__align(32)		MMP_UBYTE m_ubSDGetFreeSpaceTmp[SD_GET_FREE_SPACE_SIZE];
//extern void MMPF_MMU_InvalidateDCacheMVA(MMP_ULONG ulRegion, MMP_ULONG ulSize);
//extern void MMPF_MMU_FlushDCacheMVA(MMP_ULONG ulRegion, MMP_ULONG ulSize);
#if (FS_NEW_GET_FREE_SPACE == 1)&&(FS_NEW_SEARCH_FREE_CLUSTER == 1)

//The table cost too much space in SRAM,no need to use it in Bootloader_SRAM case
#if !defined(MBOOT_SRAM_FW) 

MMP_UBYTE m_ubSDFreeClusterTable1[FS_1ST_DEV_FREE_CLUSTER_TABLE_SIZE];
#if (FS_MAX_UNITS > 1)
MMP_UBYTE m_ubSDFreeClusterTable2[FS_2ND_DEV_FREE_CLUSTER_TABLE_SIZE];
#endif
#if (FS_MAX_UNITS > 2)
MMP_UBYTE m_ubSDFreeClusterTable3[FS_3RD_DEV_FREE_CLUSTER_TABLE_SIZE];
#endif
#if (FS_MAX_UNITS > 3)
MMP_UBYTE m_ubSDFreeClusterTable4[FS_4TH_DEV_FREE_CLUSTER_TABLE_SIZE];	
#endif
#if (FS_MAX_UNITS > 4)
MMP_UBYTE m_ubSDFreeClusterTable5[FS_5TH_DEV_FREE_CLUSTER_TABLE_SIZE];
#endif

MMP_UBYTE *m_ubSDFreeClusterTable[FS_MAX_UNITS] = {
    m_ubSDFreeClusterTable1,
#if (FS_MAX_UNITS > 1)
    m_ubSDFreeClusterTable2,
#endif
#if (FS_MAX_UNITS > 2)
    m_ubSDFreeClusterTable3,
#endif
#if (FS_MAX_UNITS > 3)
    m_ubSDFreeClusterTable4,
#endif
#if (FS_MAX_UNITS > 4)
    m_ubSDFreeClusterTable5,
#endif
};

FCTABLE_LIST FCTableContent[FS_MAX_UNITS] = {
    {m_ubSDFreeClusterTable1,FS_1ST_DEV_FREE_CLUSTER_TABLE_SIZE},
#if (FS_MAX_UNITS > 1)    
    {m_ubSDFreeClusterTable2,FS_2ND_DEV_FREE_CLUSTER_TABLE_SIZE},
#endif
#if (FS_MAX_UNITS > 2)  
    {m_ubSDFreeClusterTable3,FS_3RD_DEV_FREE_CLUSTER_TABLE_SIZE},
#endif
#if (FS_MAX_UNITS > 3)    
    {m_ubSDFreeClusterTable4,FS_4TH_DEV_FREE_CLUSTER_TABLE_SIZE},
#endif
#if (FS_MAX_UNITS > 4)    
    {m_ubSDFreeClusterTable5,FS_5TH_DEV_FREE_CLUSTER_TABLE_SIZE},
#endif
};

#endif
#endif
#endif

/* gpFS_Device are devices AIT FileSystem support */
STORAGE_UNIT gpFS_DeviceCustom[FS_MAX_UNITS] = 
{
    {FS_1ST_DEV, 0, NULL}, 
    #if (FS_MAX_UNITS > 1)
    {FS_2ND_DEV, 0, NULL}, 
    #endif
    #if (FS_MAX_UNITS > 2)
    {FS_3RD_DEV, 0, NULL}, 
    #endif
    #if (FS_MAX_UNITS > 3)
    {FS_4TH_DEV, 0, NULL}, 
    #endif
    #if (FS_MAX_UNITS > 4)
    {FS_5TH_DEV, 0, NULL}, 
    #endif
};

/* gpMSDC_Device are devices AIT MSDC support */
STORAGE_UNIT gpMSDC_DeviceCustom[MSDC_MAX_UNITS] = 
{
    {MSDC_1ST_DEV, 0, NULL}, 
#if (MSDC_MAX_UNITS > 1)
    {MSDC_2ND_DEV, 0, NULL}, 
#endif
#if (MSDC_MAX_UNITS > 2)
    {MSDC_3RD_DEV, 0, NULL}, 
#endif
#if (MSDC_MAX_UNITS > 3)
    {MSDC_4TH_DEV, 0, NULL}, 
#endif
#if (MSDC_MAX_UNITS > 4)
    {MSDC_5TH_DEV, 0, NULL},
#endif
};

#if (AHC_FS_SDNEWCACHE)
#if defined (ALL_FW)

extern FS_CACHE_INFO	SDCacheInfo;

FS_CACHE_DEVICE_MAP   Cache_SD_Mapping = {
&FS_MMC_CardMode_Driver,
&FS_MMC_CardMode_SDCacheDriver,
&SDCacheInfo
};

//CacheObject for SD media
FS_CACHE_INFO	SDCacheInfo = { 
8,
32*1024,
0,
8*32*1024,
0,0,0,0,0,0,0,0,0,0,0,0,
FS_MAX_SECTOR_SIZE,
&Cache_SD_Mapping,
//&_NewCacheRWAPI,
0,0,0,0,0,0,0,0,0,0,0,0,

SECTOR_INDEX_INVALIDATE,SECTOR_INDEX_INVALIDATE,\
SECTOR_INDEX_INVALIDATE,SECTOR_INDEX_INVALIDATE,\
SECTOR_INDEX_INVALIDATE,SECTOR_INDEX_INVALIDATE,\
SECTOR_INDEX_INVALIDATE,SECTOR_INDEX_INVALIDATE,\
SECTOR_INDEX_INVALIDATE,SECTOR_INDEX_INVALIDATE,\
SECTOR_INDEX_INVALIDATE,SECTOR_INDEX_INVALIDATE,

SECTOR_INDEX_INVALIDATE,
SECTOR_INDEX_INVALIDATE,
SECTOR_INDEX_INVALIDATE,

MMPF_FS_SetCacheStartAddrSize,
MMPF_FS_SetCacheNumSize,
MMPF_FS_SetCacheSectorSize,
MMPF_FS_SetFatNumSectors,
MMPF_FS_SetFirstDataSector,
MMPF_FS_SetHiddenSector,
MMPF_FS_RegCacheMedia,
MMPF_FS_RegCacheSelf,
MMPF_FS_RegCacheObject

};
#endif
#endif

/*********************************************************************
*
*       FS_Init
*
*  Function description:
*    Start the file system.
*
*  Parameters:
*    None.
*  
*  Return value:
*    ==0         - File system has been started.
*    !=0         - An error has occurred.
*/
int FS_Init(void) {
  int x;
  
  x = FS_OS_INIT();  /* Init the OS, e.g. create semaphores  */
  FS_LOCK();
  #if FS_USE_SMC_DRIVER
    FS__AddDevice(&FS_SMC_Driver);
  #endif
  #if FS_USE_SFNAND_DRIVER 
    FS__AddDevice(&FS_SFNAND_Driver); 
  #endif  
  #if FS_USE_NAND2K_DRIVER
    FS__AddDevice(&FS_NAND2K_Driver);
  #endif
  #if FS_USE_MMC_DRIVER
    #if FS_MMC_USE_SPI_MODE
      FS__AddDevice(&FS_MMC_SPI_Driver);
    #else 
      FS__AddDevice(FS_MMC_CardMode_SDDriverType); 
    #if (AHC_FS_SDNEWCACHE)//FS_NEWBUFFER
    #if defined (ALL_FW)
      FS__AddCacheDeviceMap(SDCacheInfo.pCacheDeviceMap);
      //FS__AddCacheRWAPIMap(SDCacheInfo.pLinkCacheAPI);
      //FS__AddCacheInfoDeviceMap(SDCacheInfo.pCacheDeviceMap->pSelf);
    #endif
    #endif
    #endif
  #endif

  #if FS_USE_MMC1_DRIVER
      FS__AddDevice(&FS_MMC1_CardMode_Driver);
  #endif

  #if FS_USE_IDE_DRIVER
    FS__AddDevice(&FS_IDE_Driver);
  #endif
  #if FS_USE_FLASH_DRIVER
    FS__AddDevice(&FS_FLASH_Driver);
  #endif
  #if FS_USE_SFLASH_DRIVER
    FS__AddDevice(&FS_SFLASH_Driver);
  #endif
  #if FS_USE_WINDRIVE_DRIVER
    FS__AddDevice(&FS_WINDRIVE_Driver);
  #endif
  #if FS_USE_RAMDISK_DRIVER
    FS__AddDevice(&FS_RAMDISK_Driver);
    {
      static U8 _aRamDiskData[FS_RAMDISK_NUM_SECTORS * FS_RAMDISK_SECTOR_SIZE];
      FS_VOLUME  * pVolume;
      const char * s;

      FS_RAMDISK_Configure(0, _aRamDiskData, FS_RAMDISK_SECTOR_SIZE, FS_RAMDISK_NUM_SECTORS);
      pVolume = FS__FindVolume("ram:", &s);
      FS__Format(pVolume, 0);
      #if FS_RAMDISK_MAXUNIT > 1
      pVolume = FS_FindVolume("ram:1:", &s);
      FS__Format(pVolume, 0);
      #endif
    }
  #endif
  #if FS_USE_GENDEV_DRIVER
    FS__AddDevice(&FS_GENERIC_Driver);
  #endif
  FS_UNLOCK();
  return x;
}


//The table cost too much space in SRAM,no need to use it in Bootloader_SRAM case
#if !defined(MBOOT_SRAM_FW)  

int FS_Module_Init(void)
{
#if 0//1 //TBD
    RTNA_DBG_Str(0, "FS_Module_Init\r\n");
#else
    MMP_ULONG dev;

    _SD_DevSetPad(SD_SOCKET0_MAP_ID);
    
    #if (USING_SD1_IF == 1)
    _SD1_DevSetPad(SD_SOCKET1_MAP_ID);
    #endif

    for (dev = 0; dev < FS_MAX_UNITS; dev++) {
        MMPF_STORAGE_RegisterFSDevie(&gpFS_DeviceCustom[dev],
                                    (MMP_ULONG)&acCacheMemory[dev],
                                    FS_CACHE_LENGTH,
                                    (MMP_ULONG)(m_ubSDFreeClusterTable[dev]),
                                    FCTableContent[dev].ulTableLength); 
    }
    for (dev = 0; dev < MSDC_MAX_UNITS; dev++) {
        MMPF_STORAGE_RegisterMSDCDevie(&gpMSDC_DeviceCustom[dev]);
    }
#endif

    return 0;
}


#if defined(__GNUC__)
__section__(initcall6)
#else //#if defined(__GNUC__)
#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
#endif
ait_module_init(FS_Module_Init);
#if defined(__GNUC__)
//NOP
#else //#if defined(__GNUC__)
#pragma
#pragma arm section rodata, rwdata, zidata
#endif
#endif

