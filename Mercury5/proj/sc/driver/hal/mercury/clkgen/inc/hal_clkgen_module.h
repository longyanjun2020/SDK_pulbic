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
* @file    hal_clkgen_module.h
* @version
* @brief   This file contains the HAL interface of module
*          support.
*
*/

#ifndef __HAL_CLKGEN_MODULE_H__
#define __HAL_CLKGEN_MODULE_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    ClkgenModule_e      eModule;
    ClkgenTopClk_e      eTopClk;
    ClkgenClkSpeed_e    eClkSpeed;
    u16                 nClkSrc;
} ClkgenTopClkReq_t;

typedef struct
{
    ClkgenModule_e      eModule;
    ClkgenTopClk_e      eTopClk;
} ClkgenModuleClkMap_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

extern ClkgenResult_e HalClkgenModuleInit(void);
extern ClkgenResult_e HalClkgenModuleClockCtl(ClkgenModule_e eModule, ClkgenClkReq_e eClkReq);
extern ClkgenResult_e HalClkgenModuleClockUpdate(ClkgenModule_e eModule, ClkgenClkUpdate_e eClk, ClkgenClkSpeed_e eClkSpeed);
extern ClkgenResult_e HalClkgenModuleClockSelectSrc(ClkgenModule_e eModule, ClkgenClkUpdate_e eClk, U16 nClkSrc);
extern u32 HalClkgenModuleGetClkSwitchBitmap(void);
extern void HalClkgenModuleSetMemClock(void);

#endif //__HAL_CLKGEN_MODULE_H__

