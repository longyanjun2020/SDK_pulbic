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
 * @file drv_mspi.h
 * @brief API prototypes for MSPI bus
 */

#ifndef __DRV_BUS_MSPI_H__
#define __DRV_BUS_MSPI_H__

#include "vm_types.ht"


typedef enum
{
    MSPI_PROC_DONE = 0,					///< Function executed with success
	MSPI_CHANNEL_NOT_INITIAL = -1,		///< Not initial
    MSPI_ERROR = -2,					///< Bus error
    MSPI_BAD_PARAMETER = -3,         	///< Bad parameter
    MSPI_ALREADY_USED = -4,          	///< SPI block already used
    MSPI_UNKNOWN_HANDLE = -5,        	///< Unknow handle
    MSPI_HANDLE_NOT_OPENED = -6,     	///< SPI block not openned
    MSPI_NO_MORE_HANDLE_FREE = -7,   	///< No more handle
    MSPI_POLLING_TIMEOUT = -8,
    MSPI_OPERATION_NOT_SUPPORT = -9,
	MSPI_PARAM_OVERFLOW = -10
} MSpiErrorCode_e;

typedef enum
{
    MSPI_CH0,
	MSPI_CH1,
	MSPI_CH2,
	MSPI_MAX
}MSpiChannel_e;

typedef enum
{
    MSPI_RW_METHOD_INTERRUPT,
	MSPI_RW_METHOD_POLLING,
	MSPI_RW_NOT_SUPPORTED
}MSpiRWMethod_e;

typedef enum {
    MSPI_MODE0, //CPOL = 0,CPHA =0
    MSPI_MODE1, //CPOL = 0,CPHA =1
    MSPI_MODE2, //CPOL = 1,CPHA =0
    MSPI_MODE3, //CPOL = 1,CPHA =1
	MSPI_MODE_MAX
} MSpiMode_e;

typedef enum {
    MSPI_PAD1 = 1,
	MSPI_PAD2,
	MSPI_PAD3,
	MSPI_PAD4,
	MSPI_PAD5,
	MSPI_PAD_MAX
} MSpiPad_e;
/**
 * @brief MSPI bus settings structure
 */
typedef struct
{
	MSpiChannel_e	eChannel;
	MSpiRWMethod_e	eRWMethod;						//polling or interrupt
	MSpiMode_e		eMSpiMode;						//MSPI_MODE0~MSPI_MODE3
	MSpiPad_e		ePadSelect;						//MSPI_PAD1~MSPI_PAD4 (MSPI_PAD5 => spi1 only)
    u32				nMspiClk;						//expected clock rate in Hz
} MSpiSettings_t;

typedef struct
{
    u8 u8TrStart;      //time from trigger to first SPI clock
    u8 u8TrEnd;        //time from last SPI clock to transferred done
    u8 u8TB;           //time between byte to byte transfer
    u8 u8TRW;          //time between last write and first read
} MSpi_DCConfig;

typedef struct
{
    u8 u8WBitConfig[8];      //bits will be transferred in write buffer
    u8 u8RBitConfig[8];      //bits Will be transferred in read buffer
} MSpi_BufferConfig;
/****************************************************************************/
/*  MSPI BUS functions                                                      */
/****************************************************************************/
MSpiErrorCode_e DrvMSpiOpen(MSpiChannel_e *pHandle, MSpiSettings_t *ptMSpiSetting);
MSpiErrorCode_e DrvMSpiClose(MSpiChannel_e nHandle);
MSpiErrorCode_e DrvMSpiWrite(MSpiChannel_e nHandle, void *pDataToWrite, u32 nWriteLen);
MSpiErrorCode_e DrvMSpiRead(MSpiChannel_e nHandle, void *pDataToRead, u32 nReadLen);


#endif /* __DRV_BUS_MSPI_H__*/
