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
* @file    drv_bdma_pub_types.h
* @version
* @brief   Bdma driver interface
*
*/

#ifndef __DRV_BDMA_PUB_TYPES_H__
#define __DRV_BDMA_PUB_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"
#include "drv_bdma_pub_forward.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/

opaque_enum(DrvBdmaErr_e_)
{
    DRV_BDMA_PROC_DONE       = 0,
    DRV_BDMA_ERROR           = -1,
    DRV_BDMA_POLLING_TIMEOUT = -2
};

opaque_enum(DrvBdmaCh_e_)
{
    DRV_BDMA_CH0 = 0,
    DRV_BDMA_CH1,
    DRV_BDMA_CH_NUM
};

opaque_enum(DrvBdmaPathSel_e_)
{
    DRV_BDMA_MIU2MIU = 0x0,
    DRV_BDMA_MIU2IMI = 0x1,
    DRV_BDMA_IMI2MIU = 0x2,
    DRV_BDMA_IMI2IMI = 0x3,
    DRV_BDMA_SPI2MIU = 0x4,
    DRV_BDMA_SPI2IMI = 0x5
};

#endif /* __DRV_BDMA_PUB_TYPES_H__ */




