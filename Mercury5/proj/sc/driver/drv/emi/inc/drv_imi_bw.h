////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
* @file    drv_imi_bw.h
* @version
* @brief   IMI bus watcher driver
*
*/

#ifndef __DRV_IMI_BUS_WATCHER_H__
#define __DRV_IMI_BUS_WATCHER_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    IMIBW_SUCCESS,
    IMIBW_FAIL,
    IMIBW_UNKNOW_HANDLE,
    IMIBW_PARAM_INVALID,
    IMIBW_PARAM_NULL,
} ImiBwErrorno_e;

typedef enum
{
    IMIBW_RANGE_16_BYTES = 0,
    IMIBW_RANGE_32_BYTES,
    IMIBW_RANGE_64_BYTES,
    IMIBW_RANGE_128_BYTES,
    IMIBW_RANGE_256_BYTES,
    IMIBW_RANGE_512_BYTES,
    IMIBW_RANGE_1024_BYTES,
    IMIBW_RANGE_2048_BYTES,
} ImiBwRange_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
extern "C" {
#endif

ImiBwErrorno_e DrvImiBw_SetConfiguration(u32 idx, u32 start_addr, u32 end_addr, u32 pattern, ImiBwRange_e range, u32 offset);
ImiBwErrorno_e DrvImiBw_Enable(bool bEnable);
ImiBwErrorno_e DrvImiBw_Clear(void);
bool DrvImiBw_IsHit(void);

#ifdef __cplusplus
}
#endif

#endif //__DRV_IMI_BUS_WATCHER_H__
