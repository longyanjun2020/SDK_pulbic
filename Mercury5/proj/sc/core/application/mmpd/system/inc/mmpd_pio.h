//==============================================================================
//
//  File        : mmpd_pio.h
//  Description : INCLUDE File for the pio
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmpd_pio.h
 *  @brief Header File for the PIO API.
 *  @author Ben Lu
 *  @version 1.0
 */

#ifndef _MMPD_PIO_H_
#define _MMPD_PIO_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_gpio_inc.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_PIO_EnableOutputMode(MMP_GPIO_PIN piopin, MMP_BOOL bEnable);
MMP_ERR MMPD_PIO_EnableTrigMode(MMP_GPIO_PIN piopin, MMP_GPIO_TRIG trigmode,
                                MMP_BOOL bEnable);
MMP_ERR MMPD_PIO_EnableInterrupt(MMP_GPIO_PIN piopin, MMP_BOOL bEnable,
                                MMP_ULONG boundingTime, GpioCallBackFunc *cb);
MMP_ERR MMPD_PIO_SetData(MMP_GPIO_PIN piopin, MMP_UBYTE outputValue);
MMP_ERR MMPD_PIO_GetData(MMP_GPIO_PIN piopin, MMP_UBYTE* returnValue);
MMP_ERR MMPD_PIO_PadConfig(MMP_GPIO_PIN piopin, MMP_UBYTE config);

#endif // _MMPD_PIO_H_