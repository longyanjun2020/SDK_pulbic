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
* @file    hal_clkgen_top.h
* @version
* @brief   This file contains the HAL interface of clkgen bbtop
*          part.
*
*/

#ifndef __HAL_CLKGEN_TOP_H__
#define __HAL_CLKGEN_TOP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define CLKGEN_INVALID_INDEX    0xFFFF

/*=============================================================*/
// Global function definition
/*=============================================================*/

extern ClkgenResult_e HalClkgenTopInit(void);
extern ClkgenResult_e HalClkgenTopSetClkSpeed(ClkgenTopClk_e eTopClk, ClkgenClkSpeed_e eClkSpeed, u16 nClkSrc);
extern ClkgenResult_e HalClkgenTopUpdateClkSpeed(ClkgenTopClk_e eTopClk);
extern ClkgenClkSpeed_e HalClkgenTopGetClkSpeed(ClkgenTopClk_e eTopClk);
extern u32 HalClkgenTopGetClkEnableCount(ClkgenTopClk_e eTopClk);
extern bool HalClkgenTopGetTestItem(u32 nIndex, ClkgenTopClk_e *peBbtopClk, ClkgenClkSpeed_e *peClkSpeed, u16 *pnClkSrc);
extern ClkgenResult_e HalClkgenTopSetMaxMiuSpeed(ClkgenClkSpeed_e eClkSpeed);
extern ClkgenResult_e HalClkgenTopClkEnable(ClkgenTopClk_e eTopClk);
extern void HalClkgenTopClkDisable(ClkgenTopClk_e eTopClk);

#endif //__HAL_CLKGEN_TOP_H__
