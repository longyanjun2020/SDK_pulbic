//==============================================================================
//
//  File        : mmps_pio.h
//  Description : INCLUDE File for the pio
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_pio.h
 *  @brief Header File for the pio API.
 *  @author Ben Lu
 *  @version 1.0
 */

#ifndef _MMPS_PIO_H_
#define _MMPS_PIO_H_

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

MMP_ERR MMPS_PIO_EnableOutputMode(MMP_GPIO_PIN piopin, MMP_BOOL bEnable);
MMP_ERR MMPS_PIO_EnableTrigMode(MMP_GPIO_PIN piopin, MMP_GPIO_TRIG trigmode,
                                MMP_BOOL bEnable);
MMP_ERR MMPS_PIO_EnableInterrupt(MMP_GPIO_PIN piopin, MMP_BOOL bEnable,
                                MMP_ULONG boundingTime, GpioCallBackFunc *cb);
MMP_ERR MMPS_PIO_SetData(MMP_GPIO_PIN piopin, MMP_UBYTE outputValue);
MMP_ERR MMPS_PIO_GetData(MMP_GPIO_PIN piopin, MMP_UBYTE *returnValue);
MMP_ERR MMPS_PIO_PadConfig(MMP_GPIO_PIN piopin, MMP_UBYTE config);

#endif // _MMPS_PIO_H_