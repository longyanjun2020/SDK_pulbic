/*
 * hal_pwm.h
 *
 *  Created on: 2017/9/12
 *      Author: titan.huang
 */

#ifndef __HAL_PWM_H__
#define __HAL_PWM_H__

#include "drv_pwm.h"

/**
* @brief        HalPWMPadSet ,configuration multi-function IO mode, set enable to PWM mode,or disable PWM mode
* @param[in]    ePWNIndex           PWM PIN Index.
* @param[in]    ePadMode           	decide that PWM use which PAD to output.
* @retval		None
 */
void HalPWMPadSet(DrvPWMSe ePWNIndex, DrvPadModeSe ePadMode);

/**
* @brief        HalPWNOutputPulse , Set PWM to output pulse
* @param[in]    ePWNIndex		PWM PIN Index.
* @param[in]    sPWMConfig		Config How to generate PWM pulse.
* @retval		None
*/
void HalPWNOutputPulse(DrvPWMSe ePWNIndex,PWMConfig_t sPWMConfig);

#endif /* __HAL_PWM_H__ */
