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
 * @file drv_dmagen.h
 * @brief definitions for using General DMA to transfer data
 */

#ifndef __DRV_DMAGEN_H__
#define __DRV_DMAGEN_H__

#include "cam_os_wrapper.h"

/*=============================================================*/
// Enumeration definition
/*=============================================================*/

typedef enum
{
    DRV_DMAGEN_NO_ERR           = 0,
    DRV_DMAGEN_ERR_PARAM        = -1,
    DRV_DMAGENPOLLING_TIMEOUT   = -2
} DrvDmaGenErr_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/

DrvDmaGenErr_e DrvDmaGen_Initialize(void);
DrvDmaGenErr_e DrvDmaGen_MoveData(  u32     ulSrcAddr,
                                    u32     ulDstAddr,
                                    u32     ulCount,
                                    void    *CallBackFunc,
                                    u32     CallBackArg,
                                    u32     bEnLineOfst,
                                    void    *pLineOfst);

#endif // __DRV_DMAGEN_H__
