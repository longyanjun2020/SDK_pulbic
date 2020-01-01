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
* @file    sys_irq_ctrl_pub_types.h
* @version
* @brief   System interrupt controller (INTC) header file
*
*/

#ifndef __SYS_IRQ_CTRL_PUB_TYPES_H__
#define __SYS_IRQ_CTRL_PUB_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "sys_traces.ho"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define INTC_FATAL  (_SYS|FATAL)
#define INTC_ERROR  (_SYS)
#define INTC_WARN   (_SYS|WARNING)

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/
#if defined(__REAL_TIME_PROBLEM_DIAGNOSE__)
extern void * g_apSysLastPcBeforeItPreemption[4];
extern u32    g_nSysLastPcBeforeItPreemptionIndex;
extern void * g_apSysLastPcDisablingIt[4];
extern u32    g_anSysLastPcDisablingItCpsr[4];
extern u32    g_nSysLastPcDisablingItIndex;
extern u32    g_nSysCpsrSnapShot;
extern void * g_pSysActiveIsr;
extern u8     g_anSysHacPreemtedByItHistogram[IT_MAX_NUMBER];
#endif

#if defined(__SEPARATE_INTERRUPT_API__)
extern u32 g_nSysDisableInterrupt;
extern u32 g_nSysDisableInterrupt_k;
#endif

#if defined(__SEPARATE_INTERRUPT_API__)
extern u32 g_anSysDisableIntCpsr[4];
extern u32 g_anSysDisableIntCpsr_k[4];
extern void* g_apSysDisableIntLr[4];
extern void* g_apSysDisableIntLr_k[4];
extern u32 g_nSysDisableIntIndex;
extern u32 g_nSysDisableIntIndex_k;
#endif

#if defined(__SEPARATE_INTERRUPT_API_PROFILE__)
extern u32 g_nSysDikQbOverheadSum;
extern u32 g_nSysDikQbOverheadCount;
extern u32 g_nSysDikQbOverheadMax;
extern u32 g_nSysDiuQbOverheadSum;
extern u32 g_nSysDiuQbOverheadCount;
extern u32 g_nSysDiuQbOverheadMax;
extern u32 g_nSysEikQbOverheadSum;
extern u32 g_nSysEikQbOverheadCount;
extern u32 g_nSysEikQbOverheadMax;
extern u32 g_nSysEiuQbOverheadSum;
extern u32 g_nSysEiuQbOverheadCount;
extern u32 g_nSysEiuQbOverheadMax;
extern u32 g_nSysIsrQbOverheadSum;
extern u32 g_nSysIsrQbOverheadCount;
extern u32 g_nSysIsrQbOverheadMax;
#endif

#endif // __SYS_IRQ_CTRL_PUB_TYPES_H__

