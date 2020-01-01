//==============================================================================
//
//  File        : mmps_pwm.h
//  Description : Header File for the PWM
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_rtc.h
 *  @brief Header File for the PWM.
 *  @author Ben Lu
 *  @version 1.0
 */

#ifndef _MMPS_PWM_H_
#define _MMPS_PWM_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//============================================================================== 

#include "mmpd_pwm.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPS_PWM_Initialize(void);
MMP_ERR MMPS_PWM_SetOutputPin(MMP_PWM_PIN pwm_pin,MMP_PWM_PAD_MODE pad_mode);
MMP_ERR MMPS_PWM_OutputPulse(MMP_PWM_PIN pwm_pin, MMP_ULONG shift,
                            MMP_ULONG ulFreq, MMP_ULONG ulDuty,
                            MMP_BOOL bHigh2Low, MMP_BOOL bEnableInterrupt,
                            PwmCallBackFunc *cb, MMP_ULONG ulNumOfPulse);

#endif // _MMPS_PWM_H_