//==============================================================================
//
//  File        : mmpf_hwcounter.h
//  Description : INCLUDE File for the Firmware hw counter
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_HW_COUNTER_H_
#define _MMPF_HW_COUNTER_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define TIMER_CLOCK_SELECT_MCLK_DIV_2 		(0)
#define TIMER_CLOCK_SELECT_MCLK_DIV_8 		(1)
#define TIMER_CLOCK_SELECT_MCLK_DIV_32 		(2)
#define TIMER_CLOCK_SELECT_MCLK_DIV_128 	(3)
#define TIMER_CLOCK_SELECT_MCLK_DIV_1024 	(4)
#define TIMER_CLOCK_SELECT_MCLK_DIV_4 		(5)
#define TIMER_CLOCK_SELECT_MCLK_DIV_16 		(6)
#define TIMER_CLOCK_SELECT_MCLK_DIV_1 		(7)

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void 		MMPF_OsCounterInit(int iDividerType, MMP_BOOL bReset);
MMP_ULONG 	MMPF_OsCounterGet(void);
MMP_ULONG 	MMPF_OsCounterGetFreqHz(void);
MMP_ULONG 	MMPF_OsCounterGetFreqKhz(void);
MMP_ULONG 	MMPF_OsCounterGetMs(void);
MMP_ULONG 	MMPF_OsCounterGetUs(void);

#endif // _MMPF_HW_COUNTER_H_
