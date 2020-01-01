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
* @file    hal_bus_i2c_adpt.h
* @version
* @brief
*
*/

#ifndef __HAL_BUS_I2C_ADPT_H__
#define __HAL_BUS_I2C_ADPT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_i2c_common.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define HALI2CGETOSTIME DrvTimerStdaTimerGetTick() //0.923us
/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
void HalI2cAdptInit(void);
bool HalI2cAdptInitPort(I2COptions_t * pstI2CSetting);
void HalI2cAdptClockSet(I2COptions_t *pOption);
void HalI2cAdptPadAlloc(void);
void HalI2cAdptPadDeAlloc(void);
I2CErrorCode_e HalI2cAdptAddrWrite(u8 nPortNum, u16 nAddress, u16 nDataToWrite, bool bStopBit, I2COptions_t *pOption);
I2CErrorCode_e HalI2cAdptAddrRead(u8 nPortNum, u16 nAddress, u16 *pDataToRead, bool bStopBit, I2COptions_t *pOption);
I2CErrorCode_e HalI2cAdptWrite(u8 nPortNum, void *pDataToWrite, u16 nNbBytes, bool bStopBit, I2COptions_t *pOption);
I2CErrorCode_e HalI2cAdptRead(u8 nPortNum, void *pDataToRead, u32 nNbBytes, I2COptions_t *pOption);
I2CErrorCode_e HalI2cAdptWriteAndRead(u8 nPortNum, void *pDataToWrite, u32 nNbBytesToWrite, void *pDataToRead, u32 nNbBytesToRead, I2COptions_t *pOption);

#endif //__HAL_BUS_I2C_ADPT_H__
