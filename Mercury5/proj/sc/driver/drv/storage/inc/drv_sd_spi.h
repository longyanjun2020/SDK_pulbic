////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
 * @file drv_sd_spi.h
 * @brief API prototypes for SD card access using SPI bus
 */

#ifndef __DRV_SD_SPI_H__
#define __DRV_SD_SPI_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
RW_STATUS DrvSDSPI_Init(u8 nDisk);
WP_STATUS _DrvSDMMC_GetWriteProtectState(U8 u8Disk);
RW_STATUS MDrvSPIStorageR(u8 nDisk, u32 nStartSector, u32 nSectorCount, u32 nMiuAddr);
RW_STATUS MDrvSPIStorageW(u8 nDisk, u32 nStartSector, u32 nSectorCount, u32 nMiuAddr);

#endif
