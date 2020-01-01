//==============================================================================
//
//  File        : strobe_ncp5080.h
//  Description : 
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#ifndef _strobe_ncp5080_H_
#define _strobe_ncp5080_H_

#if 0		 
void _____HEADER_____(){}
#endif


#include "mmpf_pio.h"
#include "mmpf_pwm.h"
#include "mmpf_timer.h"
#include "includes_fw.h"
#include "lib_retina.h"

#define EXT_CLK_HZ 				12		///< (12MHz)
#define PWM_MAX_TICKS 			65536 	///< (ticks)
#define PWM_MAX_TIME 			5461 	///< (us) = 65536/12 = 5461
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR STROBE_Initialize_5080(	MMP_GPIO_PIN 	strobeChargeOn, 
								MMP_GPIO_PIN 	strobeChargeReady, 
								MMP_PWM_PIN		strobeTrigger,
								MMPF_TIMER_ID	timerID);
MMP_ERR STROBE_EanbleCharge_5080(MMP_BOOL bEnable);
MMP_ERR STROBE_CheckChargeReady_5080(MMP_BOOL *bEnable);
MMP_ERR STROBE_TriggerInitialization_5080(	MMP_ULONG	ulBlankDuration,
										MMP_ULONG	ulTriggerDuration);
void STROBE_Trigger_5080(void);
MMP_ERR STROBE_ForceTimerClosed_5080(MMP_BOOL bForce);
MMP_ERR STROBE_GetTimerStatus_5080(MMP_BOOL* bTimerStatus, MMP_ULONG* ulHardwareTime, TimerCallBackFunc* FuncPtr);
#endif