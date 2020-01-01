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
* @file    drv_bdma_pub_api.h
* @version
* @brief   Bdma driver interface
*
*/

#ifndef __DRV_BDMA_PUB_API_H__
#define __DRV_BDMA_PUB_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "drv_bdma_pub_forward.h"
//#include "_drv_bdma.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** DrvBdmaTransfer
* @brief        Transfer data by using BDMA engine
*
* @retval       HAL_BDMA_PROC_DONE Success.
* @retval       Other              Failed.
*
*/
DrvBdmaErr_e DrvBdma_Transfer(u8 ePath, u8 *pSrcAddr, u32 nDstAddr, u32 nLength);
DrvBdmaErr_e DrvBdma_FillPattern(u32 nDstAddr, u32 nLength, u32 nPattern);

#endif /* __DRV_BDMA_PUB_API_H__ */




