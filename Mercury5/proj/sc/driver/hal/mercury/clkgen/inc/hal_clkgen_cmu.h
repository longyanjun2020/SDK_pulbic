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
* @file    hal_clkgen_cmu.h
* @version
* @brief   This file contains the HAL interface of clkgen cmu
*          part.
*
*/

#ifndef __HAL_CLKGEN_CMU_H__
#define __HAL_CLKGEN_CMU_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define CLKGEN_C0CORE_OC_SPEED CLKGEN_400MHZ

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    C0_CPU_ROOT_CLK,
    C0_CORE_CLK,
    CMU_CLK_INVALID,
} ClkgenCmuClk_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __AUTO_CPU_SPEED__
extern void ROOT_CLK312MHZ_C0_CORE_CLK_312MHZ (void);
extern void ROOT_CLK312MHZ_C0_CORE_CLK_156MHZ (void);
extern void ROOT_CLK312MHZ_C0_CORE_CLK_104MHZ (void);
extern void ROOT_CLK312MHZ_C0_CORE_CLK_78MHZ (void);
extern void ROOT_CLK312MHZ_C0_CORE_CLK_52MHZ (void);
extern void ROOT_CLK312MHZ_C0_CORE_CLK_39MHZ (void);
extern void ROOT_CLK312MHZ_C0_CORE_CLK_26MHZ (void);
#endif // __AUTO_CPU_SPEED__

extern ClkgenResult_e HalClkgenCmuInit(ClkgenPllType_e ePllType, ClkgenClkSpeed_e eC0RootClkSpeed, ClkgenClkSpeed_e eC0CoreClkSpeed);
extern ClkgenClkSpeed_e HalClkgenCmuGetCpuStallSpeed(vm_sys_SpeedProfile_e eSpeedProfile, u8 nE2pIndex);
extern ClkgenResult_e HalClkgenCmuSetClkSpeed(ClkgenCmuClk_e eCmuClk, ClkgenClkSpeed_e eClkSpeed);
extern u32 HalClkgenCmuGetClkSwitchBitmap(void);

extern ClkgenClkSpeed_e HalClkgenGetCpuClock(void);
extern ClkgenClkSpeed_e HalClkgenGetDspClock(void);

extern ClkgenResult_e HalClkgenCmuSetCpuClock(ClkgenClkSpeed_e eClkSpeed);

extern ClkgenResult_e HalClkgenEnableClock(PeriphType_e eHWIP, bool bEnable);
extern ClkgenResult_e HalClkgenEnableReset(PeriphType_e eHWIP, bool bEnable);
extern ClkgenResult_e HalClkgenEnablePower(PeriphType_e eHWIP, bool bEnable);
extern ClkgenResult_e HalClkgenCheckCpuClock(ClkgenClkSpeed_e eSpeed);

extern ClkgenResult_e HalClkgenAutoCpuSpeed(ClkgenClkSpeed_e eSpeed);
extern ClkgenResult_e HalClkgenAutoCpuGetSpeedInfo(void **eppSpeedTab, u8 *pTblSize);

//extern bool HalClkgenIsForceOn26MHz(void);

#endif //__HAL_CLKGEN_CMU_H__

