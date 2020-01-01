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
* @file    hal_bus_fsp_spi.h
* @version
* @brief   This file contains the bus FSP SPI hardware layer headers.
*
*/

#ifndef __HAL_BUS_FSP_SPI_H__
#define __HAL_BUS_FSP_SPI_H__

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
/**
 * @brief FSP SPI access description structure
 */
typedef enum
{
    FSP_USE_ONE_CMD     = 0x0,
    FSP_USE_TWO_CMD     = 0x1,
    FSP_USE_THREE_CMD   = 0x2,
} FspCmdUse_e;


typedef enum
{
    FSP_CHK_BIT0 = 0x0,
    FSP_CHK_BIT1 = 0x1,
    FSP_CHK_BIT2 = 0x2,
    FSP_CHK_BIT3 = 0x3,
    FSP_CHK_BIT4 = 0x4,
    FSP_CHK_BIT5 = 0x5,
    FSP_CHK_BIT6 = 0x6,
    FSP_CHK_BIT7 = 0x7
} FspAutoCheckBit_e;

typedef enum
{
    FSP_FST_CMD   = 0x0,
    FSP_SND_CMD   = 0x1,
    FSP_TRD_CMD   = 0x2
} FspCmdList_e;

typedef struct {
    bool                bAutoCheck;
    FspAutoCheckBit_e   eAutoCheckBit;
    FspCmdList_e        eCmdRDSR;
    FspCmdUse_e         eCmdUse;
    u8                  nFSTCmdWLen;
    u8                  nSNDCmdWLen;
    u8                  nTRDCmdWLen;
    u8                  nFSTCmdRLen;
    u8                  nSNDCmdRLen;
    u8                  nTRDCmdRLen;
    u8                  nWBuffer[16];
    u8                  nRBuffer[10];
	U32                 u32WbfSizeOutside;
} FspSpiParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
#include "drv_vm_spi.h"
void HalFspSpiWriteAndRead(FspSpiParam_t *pFspParam);
VmSpiErrorCode_e HalFspSpiBusInit(void);
void HalFspSpiWriteBDMA2FSP(FspSpiParam_t *pFspParam);
bool HalFspWaitDone(void);
void printRegister(U8 is8bit, U32 regAddr, U16 regData);
#endif //__HAL_BUS_FSP_SPI_H__
