/**
 @file ahc_gpio.h
 @brief Header File for the ahc gpio API.
 @author 
 @version 1.0
*/

#ifndef _AHC_GPIO_H_
#define _AHC_GPIO_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "mmp_gpio_inc.h"
#include "ahc_common.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 
#define PAD_NORMAL_TRIG             0x00
#define PAD_SCHMITT_TRIG            0x01
#define PAD_PULL_DOWN               0x02
#define PAD_PULL_UP                 0x04
#define PAD_FAST_SLEW               0x08
#define PAD_SLOW_SLEW               0x00
#define PAD_IDDQ_TEST_EN            0x10
#define PAD_OUT_DRIVING(_a)         (((_a)&0x03)<<5)
/*===========================================================================
 * Enum define
 *===========================================================================*/ 

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

/*===========================================================================
 * Function prototype
 *===========================================================================*/
// GPIO Function
AHC_BOOL    AHC_GPIO_ConfigPad(MMP_GPIO_PIN piopin, MMP_UBYTE config);
AHC_BOOL 	AHC_GPIO_SetOutputMode(MMP_GPIO_PIN ahc_piopin, UINT8 bDirection);
AHC_BOOL 	AHC_GPIO_SetTrigMode(MMP_GPIO_PIN ahc_piopin, MMP_GPIO_TRIG bPolarity);
AHC_BOOL 	AHC_GPIO_EnableInterrupt(MMP_GPIO_PIN ahc_piopin, void* (phHandleFunc), UINT8 bEnable);
AHC_BOOL 	AHC_GPIO_SetData(MMP_GPIO_PIN ahc_piopin, UINT8 bState);
AHC_BOOL 	AHC_GPIO_GetData(MMP_GPIO_PIN ahc_piopin, UINT8 *pwState);


#endif // _AHC_GPIO_H_
