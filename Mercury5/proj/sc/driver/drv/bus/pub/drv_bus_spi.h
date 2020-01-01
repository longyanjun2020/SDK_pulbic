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
 * @file drv_bus_spi.h
 * @brief API prototypes for SPI bus
 */

#ifndef __DRV_BUS_SPI_H__
#define __DRV_BUS_SPI_H__

#ifndef __SDK_SIMULATION__

#include "vm_types.ht"
#include "drv_vm_spi.h"

/****************************************************************************/
/*  BUS functions                                                           */
/****************************************************************************/
VmSpiErrorCode_e DrvSpiSwitchDevice(s32 nHandle, u8 nCsCurrent);
VmSpiErrorCode_e DrvSpiTransactionStart(s32 nHandle);
VmSpiErrorCode_e DrvSpiTransactionEnd(s32 nHandle);
VmSpiErrorCode_e DrvSpiOpen(s32 *pHandle, VmSpiBloc_e eSpiBloc, VmSpiSettings_t *pSettings);
VmSpiErrorCode_e DrvSpiClose(s32 nHandle);
VmSpiErrorCode_e DrvSpiWrite(s32 nHandle, void *pDataToWrite, u32 nNbBytes);
VmSpiErrorCode_e DrvSpiRead(s32 nHandle, void *pDataToRead, u32 nNbBytes);
VmSpiErrorCode_e DrvSpiDMAWrite(s32 nHandle, void *pDataToWrite, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
VmSpiErrorCode_e DrvSpiDMARead(s32 nHandle, void *pDataToRead, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
VmSpiErrorCode_e DrvSpiWriteMSB2321(s32 nHandle, u32 nStarAddr, void *pDataToWrite, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
VmSpiErrorCode_e DrvSpiReadMSB2321(s32 nHandle, u32 nStarAddr, void *pDataToRead, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
VmSpiErrorCode_e DrvSpiWriteAndRead(s32 nHandle, void *pDataToWrite, u32 nNbWBytes, void *pDataToRead, u32 nNbRBytes);

#endif /* __SDK_SIMULATION__ */
#endif /* __DRV_BUS_SPI_H__*/

