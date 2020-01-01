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
 * @file drv_bus_i2c.h
 * @brief API prototypes for I2C bus
 */

#ifndef __DRV_BUS_I2C_H__
#define __DRV_BUS_I2C_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"
#include "drv_i2c_common.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/
//#define __USE_SW_I2C__

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
I2CErrorCode_e DrvI2cOpen(s32 *pHandle, I2COptions_t *psI2cSettings);
I2CErrorCode_e DrvI2cClose(s32 nHandle);
I2CErrorCode_e DrvI2cWrite(s32 nHandle, void * pDataToWrite, u32 nNbBytes, bool bStopBit);
I2CErrorCode_e DrvI2cRead(s32 nHandle, void * pDataToRead, u32 nNbBytes);
I2CErrorCode_e DrvI2cWriteAndRead(s32 nHandle, void * pDataToWrite, u32 nNbBytesToWrite, void * pDataToRead, u32 nNbBytesToRead);
I2CErrorCode_e DrvI2cOpenSW(u32 nAddress, I2cClockSpeed_e eClkSpeed, IoChipPadNum_e eScl, IoChipPadNum_e eSda, s32 *pHandle);
I2CErrorCode_e DrvI2cAddrWrite(s32 nHandle, u16 nAddress, u16 nDataToWrite, bool bStopBit);
I2CErrorCode_e DrvI2cAddrRead(s32 nHandle, u16 nAddress, u16 *pDataToRead, bool bStopBit);


#endif /* __DRV_BUS_I2C_H__*/

