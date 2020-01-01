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

#ifndef __HALEX_RTK_TIMER_H__
#define __HALEX_RTK_TIMER_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// External definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#if defined(__RTK_USER_TICK_4DOT6MS__)
#define HAL_RTK_TICK_TIME        5
#define HAL_RTK_TICK_TIME_REAL   4.638
#define HAL_RTK_MS_TO_TICK(MsT)  ((u32)((MsT) >= HAL_RTK_TICK_TIME ? (((MsT)* 221) / 1024) : 1))
#define HAL_RTK_MS_TO_TICK_64(MsT)  ((u64)((MsT) >= HAL_RTK_TICK_TIME ? div64_ul(((MsT)* 221), 1024) : 1))
#define HAL_RTK_S_TO_TICK(SecT)  ((u32)(((SecT)* 55189) >> 8))
#define HAL_RTK_MN_TO_TICK(MnT)  ((u32)(((MnT)* 206959) >> 4))
/* In order to avoid the phenomenon of overflow */
//#define HAL_RTK_AO_S_TO_TICK(SecT)  ((u32)((((u64)SecT)* 55189) >> 8))

#define HAL_RTK_TICK_TO_MS(T) ((u32)(((u64)(T)* 303955) >> 16))
//#define VM_RTK_TICK_TO_MS(T) ((u32)(((T)* 303955) >> 16))
#define HAL_RTK_TICK_TO_S(T)  ((u32)(((u64)(T)* 19) >> 12))

//#define HAL_RTK_FRAME_TO_TICK(F) ((u32)(((F)* 1019) >> 10))
//#define HAL_RTK_TICK_TO_FRAME(T) ((u32)(((T)* 1029) >> 10))

#define HAL_RTK_MAXTIMER_VALUE      0x3FFFFFFF

#elif defined(__RTK_USER_TICK_15MS__) //__SDK_SIMULATION__
#define HAL_RTK_TICK_TIME        15
#define HAL_RTK_TICK_TIME_REAL   (15.0)
#define HAL_RTK_MS_TO_TICK(MsT)  ((u32)((MsT) >= HAL_RTK_TICK_TIME) ? (((MsT)+(HAL_RTK_TICK_TIME-1) )/HAL_RTK_TICK_TIME) : 1)
#define HAL_RTK_S_TO_TICK(SecT)  HAL_RTK_MS_TO_TICK((SecT*60))
#define HAL_RTK_MN_TO_TICK(MnT)  HAL_RTK_MS_TO_TICK((MnT*3600))
/* In order to avoid the phenomenon of overflow */
//#define HAL_RTK_AO_S_TO_TICK(SecT)  ((u32)((((u64)SecT)* 55189) >> 8))

#define HAL_RTK_TICK_TO_S(T)  ((u32)((T)* HAL_RTK_TICK_TIME)/1000)
#define HAL_RTK_TICK_TO_MS(T) ((u32)((T)* HAL_RTK_TICK_TIME))

//#define HAL_RTK_FRAME_TO_TICK(_x)   ((_x & 0x3) ? ((_x >> 2)+1) : (_x >> 2))
//#define HAL_RTK_TICK_TO_FRAME(T)    ((T*HAL_RTK_TICK_TIME)>>2)

#define DRV_RTK_MAXTIMER_VALUE      -1L
#else
#define HAL_RTK_TICK_TIME        1
#define HAL_RTK_TICK_TIME_REAL   (1)
#define HAL_RTK_MS_TO_TICK(MsT)  ((u32)MsT)
#define HAL_RTK_MS_TO_TICK_64(MsT) ((u64)MsT)
#define HAL_RTK_S_TO_TICK(SecT)  HAL_RTK_MS_TO_TICK((SecT*1000))
#define HAL_RTK_MN_TO_TICK(MnT)  HAL_RTK_MS_TO_TICK((MnT*60000))

#define HAL_RTK_TICK_TO_S(T)  ((u32)((T)* HAL_RTK_TICK_TIME)/1000)
#define HAL_RTK_TICK_TO_MS(T) ((u32)((T)* HAL_RTK_TICK_TIME))

#define HAL_RTK_MAXTIMER_VALUE      -1L

#endif //__SDK_SIMULATION__

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif //__HALEX_RTK_TIMER_H__
