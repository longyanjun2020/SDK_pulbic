////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2017 MStar Semiconductor, Inc.
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
 * @file hal_dmagen.h
 * @brief definitions for using General DMA to transfer data
 */

#ifndef __HAL_DMAGEN_H__
#define __HAL_DMAGEN_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "hal_int_irq_pub.h"

/*=============================================================*/
// Enumeration definition
/*=============================================================*/

typedef enum
{
    HAL_DMAGEN_M_0 = 0,
    HAL_DMAGEN_M_1,
    HAL_DMAGEN_M_MAX
} HalDmaGenMoveId_e;

typedef enum
{
    HAL_DMAGEN_NO_ERR           = 0,
    HAL_DMAGEN_ERR_PARAM        = -1,
    HAL_DMAGEN_POLLING_TIMEOUT  = -2
} HalDmaGenErr_e;

/*=============================================================*/
// Structure definition
/*=============================================================*/

typedef void HalDmaGenCBFunc(u32 argu);

typedef struct {
    u32                 ulSrcWidth;     ///< Width of source
    u32                 ulSrcOffset;    ///< Line-to-line offset of source
    u32                 ulDstWidth;     ///< Width of destination
    u32                 ulDstOffset;    ///< Line-to-line offset of destination
} HalDmaGenLineOfst_t;

typedef struct {
    u32                 ulSrcAddr;
    u32                 ulDstAddr;
    u32                 ulCount;
    HalDmaGenCBFunc     *CallBackFunc;
    u32                 CallBackArg;
    u32                 bEnLineOfst;
    HalDmaGenLineOfst_t *pstLineOfst;
} HalDmaGenParam_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

HalDmaGenErr_e HalDmaGen_MoveData(HalDmaGenParam_t *ptDmaGenParam);

#endif // __HAL_DMAGEN_H__

