////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    drv_flash_lowl_ho_pub.h
* @version
* @brief   Flash Memory Services - Type definitions
*
*/

#ifndef __DRV_FLASH_LOWL_HO_PUB_H__
#define __DRV_FLASH_LOWL_HO_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/****************************************************************************/
/*                        SPECIAL TYPES DEFINITIONS                         */
/****************************************************************************/

typedef struct
{
    const void *pfnFlashProgram;
    const void *pfnFlashErase;
    const void *pfnFlashSetProtect;
    const void *pfnFlashExtendedCmd;
    const void *pfnFlashBufferProgram;
} FlashActionsDescriptor_t;

typedef struct
{
    /* Joined manufacturer code and device code */
    const u32 nDeviceFullId;

    /* Supported features */
    const u32 nFeatures;

    /* Device geometry */
    const FlashDeviceGeometry_t *ptGeometry;
    const FlashBanksDescriptor_t *ptBanks;

    /* RAM based low-level functions */
    const FlashActionsDescriptor_t *ptActions;
} FlashConstDeviceDescriptor_t;


/****************************************************************************/
/* GEOMETRIES                                                               */
/****************************************************************************/

/*
 * Great! We need to more structured types derived from FlashDeviceGeometry_t
 * because this stupid armcc cannot handle zero-sized arrays properly in
 * initialisations.
 */

typedef struct
{
    u16 nDeviceSize;        /* Device size = u16_DeviceSize * 64 KiB */
    u8 nPad;
    u8 nRegionNumber;
    FlashDeviceSectorRegion_t nAsRegions[2];
} FlashTwoRegionGeometry_t;

typedef struct
{
    u16 nDeviceSize;        /* Device size = u16_DeviceSize * 64 KiB */
    u8 nPad;
    u8 nRegionNumber;
    FlashDeviceSectorRegion_t nAsRegions[1];
} FlashOneRegionGeometry_t;

typedef struct
{
    u16 nDeviceSize;        /* Device size = u16_DeviceSize * 64 KiB */
    u8 nPad;
    u8 nRegionNumber;
    FlashDeviceSectorRegion_t nAsRegions[3];
} FlashThreeRegionGeometry_t;


/****************************************************************************/
/* BANK CONFIGURATIONS                                                      */
/****************************************************************************/

/* Same remark as above... */
typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[1];   /* Containing last address of the bank /0x1000 */
} FlashMonoBank_t;

typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[2];
} FlashBiBank_t;

typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[4];
} FlashQuadriBank_t;

typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[8];
} FlashOctoBank_t;

typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[16];
} Flash16Bank_t;

typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[32];
} Flash32Bank_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif // __DRV_FLASH_LOWL_HO_PUB_H__
