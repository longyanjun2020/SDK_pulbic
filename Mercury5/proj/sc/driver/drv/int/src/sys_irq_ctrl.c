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
* @file    sys_irq_ctrl.c
* @version
* @brief   System interrupt controller (INTC) source file
*
*/

#define __SYS_IRQ_CTRL_C__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "sys_irq_ctrl_pub_types.h"
#include "sys_irq_ctrl_pub_api.h"
#include "sys_sys_dbg.h"

#if defined(__G1_GDB_RSP__)
#include <r2_gpr_defs.h>
#endif

#include "hal_int_ctrl.h"



/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

#ifdef __REAL_TIME_PROBLEM_DIAGNOSE__
#if defined(__arm)
#pragma arm section rwdata = "imi_variable", zidata = "imi_variable"
#endif
void * g_apSysLastPcBeforeItPreemption[4] = // Recording the last thread preemted by IRQ
{
    (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF
};
u32    g_nSysLastPcBeforeItPreemptionIndex = 0;
void * g_apSysLastPcDisablingIt[4] = // Recording the last thread which disables IRQ/FIQ
{
    (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF
};
u32    g_anSysLastPcDisablingItCpsr[4] = // Recording the CPRS snapshot at the moment of disabling IRQ/FIQ
{
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};
u32    g_nSysLastPcDisablingItIndex = 0;
u32    g_nSysCpsrSnapShot = 0xffffffff;     // Indicate whether we are still in RTK2_DISABLE critical section (=0 means not)
void * g_pSysActiveIsr = (void*)0xffffffff; // The ISR currently on-going. If there's no IRQ active at this moment,
                                            // this value will be 0xffffffff. This information is to supplement Rtk_CurrentTask.
u8     g_anSysHacPreemtedByItHistogram[IT_MAX_NUMBER]; // A record of how many times each IT occurs during HAC is running
#if defined(__arm)
#pragma arm section
#endif
#endif

#if defined(__SEPARATE_INTERRUPT_API__)
#if defined(__arm)
#pragma arm section rwdata = "imi_variable", zidata = "imi_variable"
#endif
u32 g_nSysDisableInterrupt = FALSE;
u32 g_nSysDisableInterrupt_k = FALSE;
u32 g_anSysDisableIntCpsr[4] =
{
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};
u32 g_anSysDisableIntCpsr_k[4] =
{
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};
void * g_apSysDisableIntLr[4] =
{
    (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF
};
void * g_apSysDisableIntLr_k[4] =
{
    (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF, (void *)0xFFFFFFFF
};
u32 g_nSysDisableIntIndex = 0;
u32 g_nSysDisableIntIndex_k = 0;
#if defined(__arm)
#pragma arm section
#endif
#endif

#if defined(__SEPARATE_INTERRUPT_API_PROFILE__)
#if defined(__arm)
#pragma arm section rwdata = "imi_variable", zidata = "imi_variable"
#endif
u32 g_nSysDikQbOverheadSum = 0;
u32 g_nSysDikQbOverheadCount = 0;
u32 g_nSysDikQbOverheadMax = 0;
u32 g_nSysDiuQbOverheadSum = 0;
u32 g_nSysDiuQbOverheadCount = 0;
u32 g_nSysDiuQbOverheadMax = 0;
u32 g_nSysEikQbOverheadSum = 0;
u32 g_nSysEikQbOverheadCount = 0;
u32 g_nSysEikQbOverheadMax = 0;
u32 g_nSysEiuQbOverheadSum = 0;
u32 g_nSysEiuQbOverheadCount = 0;
u32 g_nSysEiuQbOverheadMax = 0;
u32 g_nSysIsrQbOverheadSum = 0;
u32 g_nSysIsrQbOverheadCount = 0;
u32 g_nSysIsrQbOverheadMax = 0;
#if defined(__arm)
#pragma arm section
#endif
#endif

/*=============================================================*/
// Local function definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#if defined(__arm) && !defined(__GNUC__)
#pragma arm
#endif

/** IntcIrqHandler
* @brief        IRQ Handler
*
* @param[in]
*
* @retval
*
*/
#if defined(__G1_GDB_RSP__)
void IntcIrqHandler(struct regs *regs)
{
    HalCommonIntHandler(INTC_MAP_IRQ, regs);
}
#else
void IntcIrqHandler(void)
{
    HalCommonIntHandler(INTC_MAP_IRQ);
}
#endif

/** IntcFiqHandler
* @brief        FIQ Handler
*
* @param[in]
*
* @retval
*
*/
#if defined(__G1_GDB_RSP__)
void IntcFiqHandler(struct regs *regs)
{
    HalCommonIntHandler(INTC_MAP_FIQ, regs);
}
#else
void IntcFiqHandler(void)
{
    HalCommonIntHandler(INTC_MAP_FIQ);
}
#endif

#if defined(__arm) && !defined(__GNUC__)
#pragma thumb
#endif

