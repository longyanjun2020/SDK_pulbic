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
* @file    sys_cpu.h
* @version
* @brief   auto cpu speed change.
*
*/

#ifndef __SYS_CPU_H__
#define __SYS_CPU_H__



/*=============================================================*/
//  Includes Files
/*=============================================================*/

#ifndef __SDK_SIMULATION__
#include "sys_sys_vm_sys.h"
#include "drv_clkgen_cmu.h"
#include "hal_clkgen.h"
#include "mdl_pm.h"
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum {
  SYS_CPU_CLIENT_APP   = 0x1,
  SYS_CPU_CLIENT_STACK = 0x2
} sysCpuClient_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
//  Local function definition
/*=============================================================*/

/*=============================================================*/
// Global Function definition
/*=============================================================*/

#ifndef __SDK_SIMULATION__
void sys_AutoCpuInit(void);
void sys_AutoCpuProfiling(u8 taskId);
void sys_AutoCpuUpdate(u8 taskId);
void sys_AutoCpuIsrAdjust(u32 intNum, u32 intPriority);
void sys_AutoCpuIdleAdjust(void);
void sys_AutoCpuReset(void);
void sys_AutoCpuSetSleep(u8 sleep);
void sys_AutoCpuWakeup(void);
u32 sys_AutoCpuSleepCompensate(void);
void sys_AudoCpuIsrStartTime(void);
void sys_AutoCpuSetSpeed(ClkgenClkSpeed_e cpuSpeed);
void sys_AutoCpuPmVoltageCb(MdlPmReturnCode_e eReturnCode);
void sys_AutoCpuSetMonitorTimeUs(u32 us);
void sys_AutoCpuSetSlowLoading(u8 loading);
void sys_AutoCpuSetFastLoading(u8 loading);
void sys_AudoCpuForceSpeed(u32 speed);
void sys_AutoCpuChangeSpeedProfile(sysCpuClient_e client, vm_sys_SpeedProfile_e speedProfile, vm_sys_SpeedProfileId_e speedProfileId);
#endif

#endif /* __SYS_CPU_H__ */

