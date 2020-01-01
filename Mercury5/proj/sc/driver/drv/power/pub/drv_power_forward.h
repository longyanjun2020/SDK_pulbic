////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    drv_power_forward.h
* @version
* @brief   This module defines the power supply control driver
*
*/

#ifndef __DRV_POWER_FORWARD_H__
#define __DRV_POWER_FORWARD_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"

/*--------------------------------------------------------------------------*/
/* EXTERN DEFINITION                                                        */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* MACRO DEFINITION                                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* DATA TYPE DEFINITION                                                     */
/*--------------------------------------------------------------------------*/
/**
 * @brief  Power Supply States during Standby
 */
opaque_enum(PowerState_e_);
typedef enum PowerState_e_ PowerState_e;

/**
 * @brief Power Supply Errors
 */
opaque_enum(PowerSupplyError_e_); 
typedef enum PowerSupplyError_e_ PowerSupplyError_e;

#if 0
/**
 * @brief PMU Power Supply Type (any mode : Active and/or Standby)
 */
opaque_enum(PowerSuppplyType_e_); 
typedef enum PowerSuppplyType_e_ PowerSuppplyType_e;
#endif

#if 0
/**
 * @brief  Power Supply Modes
 */
opaque_enum(PowerMode_e_); 
typedef enum PowerMode_e_ PowerMode_e;
#endif

/***************/
/*  LDO CTRL   */
/***************/

/**
 * @brief VPER output voltage
 */
opaque_enum(VperVolt_e_); 
typedef enum VperVolt_e_ VperVolt_e;

/**
 * @brief VPER3 output voltage
 */
opaque_enum(Vper3Volt_e_); 
typedef enum Vper3Volt_e_ Vper3Volt_e;

/**
 * @brief VSIM output voltage
 */
opaque_enum(VsimVolt_e_); 
typedef enum VsimVolt_e_ VsimVolt_e;

/**
 * @brief VA output voltage
 */
opaque_enum(VaVolt_e_); 
typedef enum VaVolt_e_ VaVolt_e;

/**
 * @brief VABBAUD output voltage
 */
opaque_enum(VabbaudVolt_e_); 
typedef enum VabbaudVolt_e_ VabbaudVolt_e;

/**
 * @brief VAUX output voltage
 */
opaque_enum(VauxVolt_e_); 
typedef enum VauxVolt_e_ VauxVolt_e;

/**
 * @brief VABBRF output voltage
 */
opaque_enum(VabbrfVolt_e_); 
typedef enum VabbrfVolt_e_ VabbrfVolt_e;

/**
 * @brief VDIG output voltage
 */
opaque_enum(VdigVolt_e_); 
typedef enum VdigVolt_e_ VdigVolt_e;

/**
 * @brief VIO output voltage
 */
opaque_enum(VioVolt_e_); 
typedef enum VioVolt_e_ VioVolt_e;

/**
 * @brief VDIGRF output voltage
 */
opaque_enum(VdigrfVolt_e_); 
typedef enum VdigrfVolt_e_ VdigrfVolt_e;

#if 0
/**
 * @brief General Purpose IO
 */
opaque_enum(GpioNumber_e_); 
typedef enum GpioNumber_e_ GpioNumber_e;
#endif

/* MST change -- begin */
/**
 * @brief Power On Cause
 */
opaque_enum(PowerOnCause_e_); 
typedef enum PowerOnCause_e_ PowerOnCause_e;
/* MST change -- end */

/*--------------------------------------------------------------------------*/
/* VARIABLE DEFINITION                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

#endif //__DRV_POWER_FORWARD_H__

