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
* @file    sys_sys_cpu.h
* @version
* @brief   auto cpu speed change application.
*
*/

#ifndef __SYS_SYS_CPU_H__
#define __SYS_SYS_CPU_H__



/*=============================================================*/
//  Includes Files
/*=============================================================*/

#include "sys_sys_vm_sys.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum {
  MS_CPU_CLIENT_APP   = 0x1,
  MS_CPU_CLIENT_STACK = 0x2
} msCpuClient_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
//  Local function definition
/*=============================================================*/

/*=============================================================*/
// Global Function definition
/*=============================================================*/

void MsSysAutoCpuInit(void);
void MsSysAutoCpuProfiling(u8 taskId);
void MsSysAutoCpuUpdate(u8 taskId);
void MsSysAutoCpuIsrAdjust(u32 intNum, u32 intPriority);
void MsSysAutoCpuIdleAdjust(void);
void MsSysAutoCpuSetSleep(u8 sleep);
void MsSysAutoCpuWakeup(void);
void MsSysAutoCpuIsrStartTime(void);
bool MsSysAutoCpuIsEnable(void);
void MsSysAutoCpuSetMonitorTimeUs(u32 us);
void MsSysAutoCpuSetSlowLoading(u8 loading);
void MsSysAutoCpuSetFastLoading(u8 loading);
void MsSysAutoCpuForceSpeed(u32 speed);
void MsSysAutoCpuChangeSpeedProfile(msCpuClient_e client, vm_sys_SpeedProfile_e speedProfile, vm_sys_SpeedProfileId_e speedProfileId);

#endif /* __SYS_SYS_CPU_H__ */

