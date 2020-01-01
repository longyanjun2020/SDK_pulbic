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
* @file    hal_clkgen.h
* @version
* @brief   This file contains the HAL interface of clkgen.
*
*/

#ifndef __HAL_CLKGEN_H__
#define __HAL_CLKGEN_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

//#define CLKGEN_DATA __attribute__((section("clkgen_data"),zero_init))
#define CLKGEN_DATA  __attribute__((section("clkgen_data"),nocommon))

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    CLKGEN_PLLTYPE_1 = 0, /* MPLL = 432MHz*/
    CLKGEN_PLLTYPE_INVALID,
} ClkgenPllType_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#include "hal_clkgen_common.h"
#include "hal_clkgen_cmu.h"
#include "hal_clkgen_top.h"
#include "hal_clkgen_module.h"

extern ClkgenResult_e HalClkgenInit(ClkgenClkSpeed_e eC0CoreClkSpeed);
extern ClkgenResult_e HalClkgenInitSec(void);
extern ClkgenResult_e HalClkgenSetCpuClock(ClkgenClkSpeed_e eClkSpeed);
extern ClkgenResult_e HalClkgenSetDspClock(ClkgenClkSpeed_e eClkSpeed);
extern void HalClkgenMdcgDma2dEn(void);
extern u32 HalClkgenGetPllSwitchTable(void);

#endif //__HAL_CLKGEN_H__

