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
* @file    hal_timer.h
* @version
* @brief   This file contains the HAL interface of timer/WDT.
*
*/

#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "hal_int_irq_pub.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

void HalSysTimerInit(void);

void HalWDTimer0Enable(bool en);
void HalWDTimer0IntEnable(bool en);
bool HalWDTimer0IsEnable(void);
void HalWDTimer0Ack(void);
void HalWDTimer0SetTimeoutTicks(u32 tick);
u32 HalWDTimer0GetTimeoutTicks(void);
bool HalWDTimer0IsTimeout(void);
void HalWDTimer0ClearTimeout(void);
u32 HalWDTimer0GetStatus(void);

#endif //__HAL_TIMER_H__
