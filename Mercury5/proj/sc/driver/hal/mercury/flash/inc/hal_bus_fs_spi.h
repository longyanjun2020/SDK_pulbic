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
* @file    hal_bus_fs_spi.h
* @version
* @brief   This file contains the bus SPI hardware layer headers.
*
*/

#ifndef __HAL_BUS_FS_SPI_H__
#define __HAL_BUS_FS_SPI_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "drv_vm_spi.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define MSDRV_BUS_SPI_ERROR_LEVEL               (_DEV)
#define MSDRV_BUS_SPI_TRACE_LEVEL               (MSDRV_BUS_SPI_ERROR_LEVEL | LEVEL_6)

#define MSDRV_SPI_TR_SIZE                       16
#define MSDRV_SPI_TR_MSK                        0xFFFF

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

VmSpiErrorCode_e HalFsSpiBusTransactionStart(VmSpiSettings_t *pSpiSettings);
VmSpiErrorCode_e HalFsSpiBusTransactionEnd(VmSpiSettings_t *pSpiSettings);
VmSpiErrorCode_e HalFsSpiBusInit(VmSpiSettings_t *pSpiSettings);
VmSpiErrorCode_e HalFsSpiBusClose(void);
VmSpiErrorCode_e HalFsSpiBusWrite(VmSpiSettings_t *pSpiSettings, const void *pDataToSend, u32 nNbItems);
VmSpiErrorCode_e HalFsSpiBusRead(VmSpiSettings_t *pSpiSettings, void *pDataToStore, u32 nNbItems);
VmSpiErrorCode_e HalFsSpiBusDMAWrite(VmSpiSettings_t *pSpiSettings, const void *pDataToSend, u32 nNbItems, void (*pfnDmaCallBack)(u32 nChannel));
VmSpiErrorCode_e HalFsSpiBusDMARead(VmSpiSettings_t *pSpiSettings, void *pDataToStore, u32 nNbItems, void (*pfnDmaCallBack)(u32 nChannel));

#endif //__HAL_BUS_FS_SPI_H__
