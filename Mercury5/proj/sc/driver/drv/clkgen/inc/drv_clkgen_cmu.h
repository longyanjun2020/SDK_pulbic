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
* @file    drv_clkgen_cmu.h
* @version
* @brief   Clock Management Unit driver
*
*/

#ifndef __DRV_CLKGEN_CMU_H__
#define __DRV_CLKGEN_CMU_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"
#include "kernel.h"
#include "hal_clkgen.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define LOG_CLKGEN_TRACE (_SYS|LEVEL_4)
#define LOG_CLKGEN_ERROR (_SYS|LEVEL_4)
#define LOG_CLKGEN_FATAL (_SYS|LEVEL_4|FATAL)

/*=============================================================*/
// Global function definition
/*=============================================================*/

extern ClkgenResult_e DrvClkgenInit(ClkgenClkSpeed_e eC0CoreClkSpeed);
extern ClkgenClkSpeed_e DrvClkgenGetCpuStallSpeed(vm_sys_SpeedProfile_e eSpeedProfile, u8 nE2pIndex);
extern ClkgenResult_e DrvClkgenDrvSetMaxMiuSpeed(ClkgenClkSpeed_e eClkSpeed);
extern ClkgenResult_e DrvClkgenDrvClockCtl(ClkgenModule_e eModule, ClkgenClkReq_e eClkReq);
extern ClkgenResult_e DrvClkgenDrvClockUpdate(ClkgenModule_e eModule, ClkgenClkUpdate_e eClk, ClkgenClkSpeed_e eClkSpeed);
extern bool DrvClkgenModIsEnable(ClkgenModule_e eModule);
extern ClkgenResult_e DrvClkgenChangeCpuClock(ClkgenClkSpeed_e eNewSpeed);
extern ClkgenResult_e DrvClkgenFixedCpuClock(ClkgenClkSpeed_e eNewSpeed);
extern ClkgenResult_e DrvClkgenChangeDspClock(ClkgenClkSpeed_e eNewSpeed);
extern ClkgenResult_e DrvClkgenGetCpuClock(ClkgenClkSpeed_e *peCpuSpeed);
extern ClkgenResult_e DrvClkgenGetDspClock(ClkgenClkSpeed_e *peDspSpeed);
extern ClkgenResult_e DrvClkgenEnableClock(PeriphType_e eHWIP, bool bEnable);
extern ClkgenResult_e DrvClkgenEnableReset(PeriphType_e eHWIP, bool bEnable);
extern ClkgenResult_e DrvClkgenEnablePower(PeriphType_e eHWIP, bool bEnable);

#endif //__DRV_CLKGEN_CMU_H__

