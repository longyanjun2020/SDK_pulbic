/*
 * drv_pwm.h
 *
 *  Created on: 2017¦~9¤ë12¤é
 *      Author: titan.huang
 */

#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include "vm_types.ht"

#define DRV_PWM_PM_PAD_BIT		4

typedef enum
{
	DRV_PWM_0,
	DRV_PWM_1,
	DRV_PWM_2,
	DRV_PWM_3,
	DRV_PWM_4,
	DRV_PWM_5,
	DRV_PWM_6,
	DRV_PWM_7,
	DRV_PWM_MAX
} DrvPWMSe;

typedef enum
{
	DRV_PWM_PAD_MODE0 = 0x00,								//disable non-PM Pad
	DRV_PWM_PAD_MODE1,
	DRV_PWM_PAD_MODE2,
	DRV_PWM_PAD_MODE3,
	DRV_PWM_PAD_MODE4,
	DRV_PWM_PAD_MODE_NOSUPPORT,
	DRV_PWM_PM_PAD_MODE0 = (1 << DRV_PWM_PM_PAD_BIT) | 0x00,	//disable PM Pad
	DRV_PWM_PM_PAD_MODE1,
	DRV_PWM_PM_PAD_MODE2,
	DRV_PWM_PM_PAD_MODE_NOSUPPORT
} DrvPadModeSe;

typedef struct{
    u32                 nFrequency;        	//PWM period in Hz
    u32					nDuty;				//Duty in percentage(0~100)
    bool				bInvert;			//Invert signal or not
    u32					nPulseShift;		//shift of duty cycle in percentage(0~100)
} PWMConfig_t;

/**
* @brief        DrvPWMPadSet ,configuration multi-function IO mode, set enable to PWM mode,or disable PWM mode
* @param[in]    ePWNIndex           PWM PIN Index.
* @param[in]    ePadMode           	decide that PWM use which PAD to output.
* @retval		None
 */
void DrvPWMPadSet(DrvPWMSe ePWNIndex, DrvPadModeSe ePadMode);

/**
* @brief        DrvPWNOutputPulse , Set PWM to output pulse
* @param[in]    ePWNIndex		PWM PIN Index.
* @param[in]    sPWMConfig		Config How to generate PWM pulse.
* @retval		None
*/
void DrvPWNOutputPulse(DrvPWMSe ePWNIndex,PWMConfig_t sPWMConfig);


#endif /* __DRV_PWM_H__ */
