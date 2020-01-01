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
* @file    sys_irq_ctrl_pub_api.h
* @version
* @brief   System interrupt controller (INTC) header file
*
*/

#ifndef __SYS_IRQ_CTRL_PUB_API_H__
#define __SYS_IRQ_CTRL_PUB_API_H__

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

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype & definition
/*=============================================================*/
#if defined(__G1_GDB_RSP__)
#include <r2_gpr_defs.h>
extern void IntcIrqHandler(struct regs *regs);
extern void IntcFiqHandler(struct regs *regs);
#else
extern void IntcIrqHandler(void);
extern void IntcFiqHandler(void);
#endif

#endif // __SYS_IRQ_CTRL_PUB_API_H__

