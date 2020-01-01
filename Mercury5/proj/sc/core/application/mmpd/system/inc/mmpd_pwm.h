/// @ait_only
//==============================================================================
//
//  File        : mmpd_pwm.h
//  Description : INCLUDE File for the Host PWM Driver.
//  Author      : Rogers Chen
//  Revision    : 1.0
//
//==============================================================================
#ifndef _MMPD_PWM_H_
#define _MMPD_PWM_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmp_pwm_inc.h"

/** @addtogroup MMPD_PWM
 *  @{
 */

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR MMPD_PWM_Initialize(void);
MMP_ERR MMPD_PWM_SetOutputPin(MMP_PWM_PIN pwm_pin,MMP_PWM_PAD_MODE pad_mode);
MMP_ERR MMPD_PWM_OutputPulse(MMP_PWM_PIN pwm_pin, MMP_ULONG shift,
                             MMP_ULONG ulFrquency, MMP_ULONG ulDuty,
                             MMP_BOOL bHigh2Low, MMP_BOOL bEnableInterrupt,
                             PwmCallBackFunc *cb, MMP_ULONG ulNumOfPulse);

/// @}

#endif // _MMPD_PWM_H_

/// @end_ait_only

