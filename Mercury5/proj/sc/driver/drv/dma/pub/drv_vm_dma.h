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
 * @file drv_vm_dma.h
 * @brief
 */
#ifndef __DRV_VM_DMA_H__
#define __DRV_VM_DMA_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/****** ERROR CODE DEFINITION *******/
typedef enum
{
    DRV_DMAC_OK,
    DRV_DMAC_ERR_CHANNEL_ACTIVE,
    DRV_DMAC_ERR_CHANNEL_NOTAVAIL,
    DRV_DMAC_ERR_BLOCK_TOO_BIG,
    DRV_DMAC_ERR_WRONG_ID,
    DRV_DMAC_ERR_ENABLE_FAILED,
    DRV_DMAC_ERR_CHANNEL_NOTENABLED,
    DRV_DMAC_ERR_CHANNEL_NOT_EXIST,
    DRV_DMAC_ERR_MISC,
    DRV_DMAC_ERR_INVALID_PARAM
} DmaErrMsg_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Local function prototype & definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
#endif
