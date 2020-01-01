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
 * @file hal_bdma.h
 * @brief definitions for using BDMA to transfer data
 */

#ifndef __HAL_BDMA_H__
#define __HAL_BDMA_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "hal_int_irq_pub.h"

/*=============================================================*/
// System Data Type
/*=============================================================*/

/// data type unsigned char, data length 1 byte
typedef unsigned char               MS_U8;// 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short              MS_U16;// 2 bytes
/// data type unsigned int, data length 4 byte
typedef unsigned long               MS_U32;// 4 bytes
/// data type signed int, data length 4 byte
typedef signed long                 MS_S32;// 4 bytes
/// definition for MS_BOOL
typedef unsigned char               MS_BOOL;

#define ENABLE                      1

////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////
#define HAL_BDMA_MS(x)          (3955 * (x))

//v: value n: shift n bits
#define __BIT(x)    ((MS_U8)(1 << (x)))
#define __BIT0       __BIT(0)
#define __BIT1       __BIT(1)
#define __BIT2       __BIT(2)
#define __BIT3       __BIT(3)
#define __BIT4       __BIT(4)
#define __BIT5       __BIT(5)
#define __BIT6       __BIT(6)
#define __BIT7       __BIT(7)

#define BDMA_REG_BASE               (0x100200)  // NONPM: 0x1002
#define BDMA_REG_CH0_BASE           (BDMA_REG_BASE+0)
#define BDMA_CH_REG_OFFSET          (0x20)
#define BDMA_SET_CH0_REG(x)         (BDMA_REG_CH0_BASE+(x))
#define BDMA_SET_CH1_REG(x)         (BDMA_SET_CH0_REG(x)+BDMA_CH_REG_OFFSET)

#define BDMA_REG_CH0_CTRL           BDMA_SET_CH0_REG(0)
#define BDMA_REG_CH0_STATUS         BDMA_SET_CH0_REG(0x02)
#define BDMA_REG_CH0_SRC_SEL        BDMA_SET_CH0_REG(0x04)
#define BDMA_REG_CH0_DST_SEL        BDMA_SET_CH0_REG(0x05)
#define BDMA_REG_CH0_MISC           BDMA_SET_CH0_REG(0x06)
#define BDMA_REG_CH0_DWUM_CNT       BDMA_SET_CH0_REG(0x07)
#define BDMA_REG_CH0_SRC_ADDR_L     BDMA_SET_CH0_REG(0x08)
#define BDMA_REG_CH0_SRC_ADDR_H     BDMA_SET_CH0_REG(0x0A)
#define BDMA_REG_CH0_DST_ADDR_L     BDMA_SET_CH0_REG(0x0C)
#define BDMA_REG_CH0_DST_ADDR_H     BDMA_SET_CH0_REG(0x0E)
#define BDMA_REG_CH0_SIZE_L         BDMA_SET_CH0_REG(0x10)
//Ch0 Special command 0
#define BDMA_REG_CH0_CMD0_L         BDMA_SET_CH0_REG(0x14)
#define BDMA_REG_CH0_CMD0_H         BDMA_SET_CH0_REG(0x16)
//Ch0 Special command 1
#define BDMA_REG_CH0_CMD1_L         BDMA_SET_CH0_REG(0x18)
#define BDMA_REG_CH0_CMD1_H         BDMA_SET_CH0_REG(0x1A)
//Ch0 Special command 2
#define BDMA_REG_CH0_CMD2_L         BDMA_SET_CH0_REG(0x1C)
#define BDMA_REG_CH0_CMD2_H         BDMA_SET_CH0_REG(0x1E)

//---------------------------------------------
// definition for BDMA_REG_CH0_CTRL/BDMA_REG_CH1_CTRL
//---------------------------------------------
#define BDMA_CH_TRIGGER             __BIT0
#define BDMA_CH_STOP                __BIT4
//---------------------------------------------
// definition for REG_BDMA_CH0_STATUS/REG_BDMA_CH1_STATUS
//---------------------------------------------
#define BDMA_CH_QUEUED              __BIT0
#define BDMA_CH_BUSY                __BIT1
#define BDMA_CH_INT                 __BIT2
#define BDMA_CH_DONE                __BIT3
#define BDMA_CH_RESULT              __BIT4
#define BDMA_CH_CLEAR_STATUS        (BDMA_CH_INT|BDMA_CH_DONE|BDMA_CH_RESULT)
//---------------------------------------------
// definition for REG_BDMA_CH0_MISC/REG_BDMA_CH1_MISC
//---------------------------------------------
#define BDMA_CH_ADDR_DECDIR         __BIT0
#define BDMA_CH_DONE_INT_EN         __BIT1
#define BDMA_CH_CRC_REFLECTION      __BIT4
#define BDMA_CH_MOBF_EN             __BIT5

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    HAL_BDMA_PROC_DONE       = 0,
    HAL_BDMA_ERROR           = -1,
    HAL_BDMA_POLLING_TIMEOUT = -2
} HalBdmaErr_e;

typedef enum
{
    HAL_BDMA_CH0 = 0,
    HAL_BDMA_CH1,
    HAL_BDMA_CH_NUM
} HalBdmaCh_e;

typedef enum
{
    HAL_BDMA_TRIGGER = 0x1,
    HAL_BDMA_STOP    = 0x10
} HalBdmaCtrl_e;

typedef enum
{
    HAL_BDMA_MIU2MIU = 0x0,
    HAL_BDMA_MIU2IMI = 0x1,
    HAL_BDMA_IMI2MIU = 0x2,
    HAL_BDMA_IMI2IMI = 0x3,
    HAL_BDMA_SPI2MIU = 0x4,
    HAL_BDMA_SPI2IMI = 0x5,
    HAL_BDMA_MEM2MIU = 0x6,
    HAL_BDMA_MIU2FSP = 0x7
} HalBdmaPathSel_e;

typedef enum
{
    HAL_BDMA_DATA_BYTE_1  = 0x0,
    HAL_BDMA_DATA_BYTE_2  = 0x1,
    HAL_BDMA_DATA_BYTE_4  = 0x2,
    HAL_BDMA_DATA_BYTE_8  = 0x3,
    HAL_BDMA_DATA_BYTE_16 = 0x4
} HalBdmaDataWidth_e;

typedef enum
{
    HAL_BDMA_ADDR_INC = 0x0,
    HAL_BDMA_ADDR_DEC = 0x1
} HalBdmaAddrMode_e;

typedef enum _Hal_BDMA_ACT
{
    E_BDMA_ACT_COPY_MEM
    ,E_BDMA_ACT_COPY_FLASH
    ,E_BDMA_ACT_MEM_FILL
    ,E_BDMA_ACT_SEARCH
    ,E_BDMA_ACT_CRC32
    ,E_BDMA_ACT_MAX
} BDMA_Act;

typedef enum _BDMA_HalDev  //map to BDMA_Dev
{
    E_BDMA_HALDEV_MIU0
    ,E_BDMA_HALDEV_MIU1
    ,E_BDMA_HALDEV_SEARCH
    ,E_BDMA_HALDEV_CRC32
    ,E_BDMA_HALDEV_MEM_FILL
    ,E_BDMA_HALDEV_FLASH
    ,E_BDMA_HALDEV_DMDMCU
    ,E_BDMA_HALDEV_VDMCU
    ,E_BDMA_HALDEV_DSP
    ,E_BDMA_HALEV_TSP
    ,E_BDMA_HALDEV_NOT_SUPPORT
} BDMA_HalDev;

//Data width
typedef enum _BDMA_Dw
{
    E_BDMA_DW_1BYTE = 0x00
    ,E_BDMA_DW_2BYTE = 0x10
    ,E_BDMA_DW_4BYTE = 0x20
    ,E_BDMA_DW_8BYTE = 0x30
    ,E_BDMA_DW_16BYTE = 0x40
    ,E_BDMA_DW_MAX = E_BDMA_DW_16BYTE
} BDMA_Dw;

typedef enum _Hal_BDMA_Ch
{
    E_BDMA_CH_START
    ,E_BDMA_CH0 = E_BDMA_CH_START
    ,E_BDMA_CH1
    ,E_BDMA_CH_END
} BDMA_ChNum;

/*=============================================================*/
// Structure definition
/*=============================================================*/

typedef void (* HalBdmaTxCb)(u32);

typedef struct {
    bool                    bIntMode;
    HalBdmaPathSel_e        ePathSel;
    HalBdmaDataWidth_e      eSrcDataWidth;
    HalBdmaDataWidth_e      eDstDataWidth;
    HalBdmaAddrMode_e       eDstAddrMode;
    u32                     nTxCount;
    u32                     nPattern;
    void                    *pSrcAddr;
    void                    *pDstAddr;
    HalBdmaTxCb             pfTxCbFunc;
} HalBdmaParam_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

HalBdmaErr_e HalBdma_Initialize(void);
HalBdmaErr_e HalBdma_Transfer(u8* pDmaCh, HalBdmaParam_t *ptBdmaParam);
void         HalBdma_TriggerBDMA2FSPTransfer(u8* pDmaCh, HalBdmaParam_t *ptBdmaParam);
HalBdmaErr_e HalBdma_WaitTransferDone(u8* pDmaCh, HalBdmaParam_t *ptBdmaParam);
MS_BOOL      HalBdma_IsBDMAinit(void);

#endif // __HAL_BDMA_H__

