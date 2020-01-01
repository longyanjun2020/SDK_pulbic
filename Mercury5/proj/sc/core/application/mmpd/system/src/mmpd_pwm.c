/// @ait_only
//==============================================================================
//
//  File        : mmpd_pwm.c
//  Description : MMP PWM Module Control driver function
//  Author      : Rogers Chen
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmpd_pwm.c
*  @brief The PWM Module Control functions
*  @author Rogers Chen
*  @version 1.0
*/

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmph_hif.h"
#include "mmpd_pwm.h"
#include "mmpf_pwm.h"

/** @addtogroup MMPD_PWM
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_PWM_Initialize
//  Description : 
//------------------------------------------------------------------------------
/** @brief Driver init

Driver init
@return It reports the status of the operation.
*/
MMP_ERR MMPD_PWM_Initialize(void)
{
	return MMPF_PWM_Initialize();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PWM_SetOutputPin
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_PWM_SetOutputPin(MMP_PWM_PIN pwm_pin,MMP_PWM_PAD_MODE pad_mode)
{
	return MMPF_PWM_SetOutputPin(pwm_pin,pad_mode);
}
//------------------------------------------------------------------------------
//  Function    : MMPD_PWM_OutputPulse
//  Description : 
//------------------------------------------------------------------------------
/** @brief Simplely output some pulses (According to the parameters)

Simplely output some pulses (According to the parameters)
@param[in] pwm_pin : PWM I/O pin selection, please refer MMP_PWM_PIN
@param[in] shift : shift of duty cycle in percentage(0~100)
@param[in] ulFreq : the pulse frequency in unit of Hz
@param[in] duty	: Duty cycle in percentage(0~100)
@param[in] bHigh2Low : MMP_TRUE: High to Low pulse, MMP_FALSE: Low to High pulse
@param[in] bEnableInterrupt : enable interrupt or not
@param[in] cb : call back function when interrupt occurs
@param[in] ulNumOfPulse : number of pulse, 0 stand for using PWM auto mode to
                          generate infinite pulse.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_PWM_OutputPulse(MMP_PWM_PIN pwm_pin, MMP_ULONG shift,
                            MMP_ULONG ulFreq, MMP_ULONG ulDuty,
                            MMP_BOOL bHigh2Low, MMP_BOOL bEnableInterrupt,
                            PwmCallBackFunc *cb, MMP_ULONG ulNumOfPulse)
{
	return MMPF_PWM_OutputPulse(pwm_pin, shift, ulFreq, ulDuty,
	                            bHigh2Low, bEnableInterrupt, cb, ulNumOfPulse);
}

/// @}
/// @end_ait_only




