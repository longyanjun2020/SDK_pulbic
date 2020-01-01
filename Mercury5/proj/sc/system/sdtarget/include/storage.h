///////////////////////////////////////////////////////////////////////////////////////////////////
//   HEADER NAME:
//       storage.h
//
//   Written by Jeffrey.Chen@MSTAR Inc.
//---------------------------------------------------------------------
//
// Initial revision for ceramal 3
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STORAGE_H
#define STORAGE_H

#include "stdcomp.h"

typedef enum ECARDSTATUS
{
    STS_SUCCESS              = 0x00,
    STS_CR_FAIL              = 0x8C,
    STS_CR_NOMEDIA           = 0x8D,
    STS_CR_WRITE_PROTECT     = 0x8F,
    STS_CR_SECTOR_ADDR_ERR   = 0x90,
    STS_CR_IO_ERROR          = 0x93,
    STS_CR_CARD_INIT_OK      = 0x96,
    STS_CR_MIU_PATCH_FAIL    = 0x9A,

} RW_STATUS;

typedef enum ESD_STATUS
{
    SD_INIT_OK,
    SD_INIT_FAIL,
    SD_NOT_EXIST,
    STG_NOT_INIT_YET,
}
SD_STATUS;

#ifndef STG_DRIVER

extern void MDrvStorageInitial(void);
extern SD_STATUS MDrvCheckSDStatus(void);
extern RW_STATUS  MDrvStorageR(u8 u8Disk, u32 u32StartSector, u32 u32SectorCount, u32 u32MiuAddr);
// For bigblue3 ROM code, please set u8Disk as 0 to read SD card

#if defined( __SDAPPRAM__ ) || defined(__SDAPPRAM_PI__) || defined(__SDTARGET__)
typedef RW_STATUS (*pfnR)(u8 u8Disk, u32 u32StartSector, u32 u32SectorCount, u32 u32MiuAddr);
extern pfnR ptr_MDrvStorageR_B5_U01;
extern pfnR ptr_MDrvStorageR_B5_U02;
extern pfnR ptr_MDrvStorageR_B5_U03;
extern pfnR ptr_MDrvStorageR_B5_U04;
extern pfnR ptr_MDrvStorageR_B9_U01;
extern pfnR ptr_MDrvStorageR_B9_U02;
#else
#define MDRVSTORAGER    MDrvStorageR
#endif

#endif

#endif // #ifndef STORAGE_H
