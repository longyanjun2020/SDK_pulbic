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
 * @file    halex_timer.h
 * @version
 * @brief   This file contains the HAL interface of timer/WDT which will be exported to driver interface.
 *          Notes : this file will be included by drv_timer.h directly.
 *          The file include 2 parts,
 *          1. hardware capability macro
 *          2. Time critical macro
 *
 */

#ifndef __HALEX_TIMER_H__
#define __HALEX_TIMER_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "kernel.h"
#include "kernel_systimer.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define TIMER_WDTIMER_MAX_TICK      0xFFFFFFFF
#define TIMER_WDTIMER_0_TICK        (0x3940000/2) //5s

#define HAL_OSTICK_MAX_COUNT        0xFFFFFFFF
#define HAL_STDATIMER_MAX_COUNT     0xFFFFFFFF
#define HAL_GLOBAL_TIMER_MAX_COUNT  0xFFFFFFFF


#define STDA_CLK_N      24      // ARM Internal clk 6 MHz,Tickx4 = 24MHz
#define STDA_CLK_D      1      // Frequency divider

#define GLOBAL_CLK_N    24000   // ARM Internal clk 6 MHz,Tickx4 = 24MHz
#define GLOBAL_CLK_D    1

#define OSTICK_CLK_N    24000
#define OSTICK_CLK_D    1

/* Timer0 for OS Tick */
#define HAL_OSTICK_STOP() \
    do \
    { \
        g_ptKeInfinteTimer0->reg_timer_en = 0x00; \
    } while(0)

#define HAL_OSTICK_RUN(tick) \
    do \
    { \
        g_ptKeInfinteTimer0->reg_timer_int_en = (tick == HAL_OSTICK_MAX_COUNT) ? 0x00 : 0x01; \
        g_ptKeInfinteTimer0->reg_timer_max_low = ((tick)&0xFFFF); \
        g_ptKeInfinteTimer0->reg_timer_max_high = ((tick>>16)&0xFFFF); \
        g_ptKeInfinteTimer0->reg_timer_en = 0x01; \
    } while(0)

#define HAL_OSTICK_GET_TIMEOUTLENGTH() ((g_ptKeInfinteTimer0->reg_timer_max_low + (g_ptKeInfinteTimer0->reg_timer_max_high<<16)))
#define HAL_OSTICK_GET_COUNT() ((g_ptKeInfinteTimer0->reg_timer_cap_low + (g_ptKeInfinteTimer0->reg_timer_cap_high<<16)))

#define HAL_OSTICK_INT_FLAG() (g_ptKeInfinteTimer0->reg_timer_hit)

#define HAL_OSTICK_INT_CLEAR() \
    do \
    { \
        g_ptKeInfinteTimer0->reg_timer_hit = 1; \
    } while(0)

#define HAL_OSTICK_INT_ENABLE() \
    do \
    { \
        g_ptKeInfinteTimer0->reg_timer_int_en = 0x01; \
    } while(0)

#define HAL_OSTICK_INT_DISABLE() \
    do \
    { \
        g_ptKeInfinteTimer0->reg_timer_int_en = 0x0; \
    } while(0)

#define HAL_SYSTIMER_INT_RAW_STAUTS() g_ptKeInfinteTimer0->reg_timer_hit
#define HAL_SYSTIMER_INT_STAUTS()     g_ptKeInfinteTimer0->reg_timer_hit

/* Timer1 for Delay */
#define HAL_OSTICK1_RUN(tick) \
    do \
    { \
        g_ptKeInfinteTimer1->reg_timer_int_en = (tick == HAL_OSTICK_MAX_COUNT) ? 0x00 : 0x01; \
        g_ptKeInfinteTimer1->reg_timer_max_low = ((tick)&0xFFFF); \
        g_ptKeInfinteTimer1->reg_timer_max_high = ((tick>>16)&0xFFFF); \
        g_ptKeInfinteTimer1->reg_timer_en = 0x01; \
     } while(0)

// STDATIMER is Ostick1 ; HAL_STDATIMER_START replace by timer_open( MS_TIMER1,.... );
#define HAL_STDATIMER_START() HAL_OSTICK1_RUN(HAL_STDATIMER_MAX_COUNT)
#define HAL_STDATIMER_TIMEOUTLENGTH() (HAL_STDATIMER_MAX_COUNT)
//#define HAL_STDATIMER_GETTICK() ((g_ptKeInfinteTimer1->reg_timer_cap_low + (g_ptKeInfinteTimer1->reg_timer_cap_high<<16)))
#define HAL_STDATIMER_GETTICK() HalArchCounter12M32Bit()
#define HAL_STDATIMER_UDELAY(us) HalTimerUDelay(us, 1)
#define HAL_STDATIMER_UDELAY_COND(cond, us) HalTimerUDelay(us, cond)

#define MAX_DELAY_US (0xFFFFFFFF/STDA_CLK_N*STDA_CLK_D) //357s
#define MAX_DELAY_TICK (MAX_DELAY_US/STDA_CLK_N*STDA_CLK_N)

/* Timer2 for OS Timer */
#define HAL_OSTICK2_STOP() \
    do \
    { \
        g_ptKeInfinteTimer2->reg_timer_en = 0x00; \
    } while(0)

#define HAL_OSTICK2_RUN(tick) \
    do \
    { \
        g_ptKeInfinteTimer2->reg_timer_int_en = (tick == HAL_GLOBAL_TIMER_MAX_COUNT) ? 0x00 : 0x01; \
        g_ptKeInfinteTimer2->reg_timer_max_low = ((tick)&0xFFFF); \
        g_ptKeInfinteTimer2->reg_timer_max_high = ((tick>>16)&0xFFFF); \
        g_ptKeInfinteTimer2->reg_timer_en = 0x01; \
     } while(0)

//#define HAL_OSTICK2_GET_TIMEOUTLENGTH() ((g_ptKeInfinteTimer2->reg_timer_max_low + (g_ptKeInfinteTimer2->reg_timer_max_high<<16)))
//#define HAL_OSTICK2_GET_COUNT() ((g_ptKeInfinteTimer2->reg_timer_cap_low) + (g_ptKeInfinteTimer2->reg_timer_cap_high<<16))
#define HAL_OSTICK2_GET_TIMEOUTLENGTH() (HAL_GLOBAL_TIMER_MAX_COUNT)
#define HAL_OSTICK2_GET_COUNT() HalArchCounter12M32Bit()
#define HAL_OSTICK2_INT_FLAG()  (g_ptKeInfinteTimer2->reg_timer_hit)

#define HAL_OSTICK2_INT_CLEAR() \
    do \
    { \
        g_ptKeInfinteTimer2->reg_timer_hit = 1; \
    } while(0)

#define HAL_OSTICK2_INT_ENABLE() \
    do \
    { \
        g_ptKeInfinteTimer2->reg_timer_int_en = 0x01; \
    } while(0)

#define HAL_OSTICK2_INT_DISABLE() \
    do \
    { \
        g_ptKeInfinteTimer2->reg_timer_int_en = 0x0; \
    } while(0)

// GLOBAL_TIMER is Ostick2 ; HAL_GLOBAL_TIMER_START replace by timer_open( MS_TIMER2,.... );
#define HAL_GLOBAL_TIMER_STOP() HAL_OSTICK2_STOP()
#define HAL_GLOBAL_TIMER_START() HAL_OSTICK2_RUN(HAL_GLOBAL_TIMER_MAX_COUNT)
#define HAL_GLOBAL_TIMER_GET_TICK() HAL_OSTICK2_GET_COUNT()

/*=============================================================*/
// Global function definition
/*=============================================================*/

void HalTimerUDelay(u32 us, int cond);

void HalGlobalTimerIsrReg(PfnTimerIntcISR pfnOstickTimerISR);
void HalGlobalTimerIsrRel(void);
void HalGlobalTimerIsrMask(void);
void HalGlobalTimerIsrUnMask(void);
void HalOsTickTimerIsrReg(PfnTimerIntcISR pfnOstickTimerISR);
void HalOsTickTimerIsrRel(void);
void HalWDTimerIsrReg(PfnTimerIntcISR pfnWDTimerISR);
void HalWDTimerIsrRel(void);
u64 HalArchCounterGetCntpct(void);
u32 HalArchCounter12M32Bit(void);
#endif //__HALEX_TIMER_H__
