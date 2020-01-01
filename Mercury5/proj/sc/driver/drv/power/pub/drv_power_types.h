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
* @file    drv_power_types.h
* @version
* @brief   This module defines the power supply control driver
*
*/

#ifndef __DRV_POWER_TYPES_H__
#define __DRV_POWER_TYPES_H__

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
opaque_enum(PowerState_e_)
{
    PWR_STATE_DOWN = 0,	/**< power off */
    PWR_STATE_LOW  = 1,	/**< low quiescent */
    PWR_STATE_FULL = 3  /**< full power */
};

/**
 * @brief Power Supply Errors
 */
opaque_enum(PowerSupplyError_e_)
{
    PWR_ERR_OK            =  0,   /**< No Error */
    PWR_ERR_TYPE            = -1,   /**< Error : Unknown power type */
    PWR_ERR_VOLTAGE         = -2,   /**< Error : Unknown power voltage */
    PWR_ERR_MODE            = -3,   /**< Error : Unknown power mode */
    PWR_ERR_STATE           = -4,   /**< Error : Unknown power state */
    PWR_ERR_TYPE_MODE       = -5,   /**< Error : mode/type incompatibility */
    PWR_ERR_STATE_MODE      = -6,   /**< Error : state/mode incompatibility */

    PWR_ERR                 = -7    /**< Error : Unknown error */
};

#if 0
/**
 * @brief PMU Power Supply Type (any mode : Active and/or Standby)
 */
opaque_enum(PowerSuppplyType_e_)
{
    PWR_VABB = 0,   /**<   */
    PWR_VABBRF,     /**<   */
    PWR_VABBAUD,    /**<   */
    PWR_VDIG,       /**<   */
    PWR_VAUDR,      /**<   */
    PWR_VDBBIO2,    /**<   */
    PWR_VMMPIO,     /**<   */
    PWR_VMMPBUCK1,  /**<   */
    PWR_VMMPBUCK2,  /**<   */

    PWR_VDIGRF,     /**<    */
    PWR_VSIM,       /**<    */
    PWR_VDBBIO1,    /**<    */
    PWR_VTCXO,      /**<    */
    PWR_VRF1,       /**<    */
    PWR_VRF2,       /**<    */
    PWR_VMEM,       /**<    */
    PWR_VUSB,       /**<    */
    PWR_VRFID,      /**<    */

    PWR_VLCD,       /**<    */
    PWR_VSPARE,     /**<    */
    PWR_VBUS,

    PWR_SUPPLY_TYPE_NUM /**<  number of supply types  */
};
#endif

#if 0
/**
 * @brief  Power Supply Modes
 */
opaque_enum(PowerMode_e_)
{
	PWR_MODE_ACTIVE     = 0,        /**< active mode */
	PWR_MODE_STANDBY,               /**< standby mode */
	PWR_MODE_COMBINED,              /**< active/standby mode */

	PWR_MODE_NUM
};
#endif

/***************/
/*  LDO CTRL   */
/***************/

/**
 * @brief VPER output voltage
 */
opaque_enum(VperVolt_e_)
{
    VPER_1_8 = 0, /**<  Volt: 1.80V */
    VPER_2_5,     /**<  Volt: 2.50V */
    VPER_2_8,     /**<  Volt: 2.80V */
    VPER_3_2,     /**<  Volt: 3.20V */
    VPER_SUPPLY_NUM
};

/**
 * @brief VPER3 output voltage
 */
opaque_enum(Vper3Volt_e_)
{
    VPER3_1_8 = 0, /**<  Volt: 1.80V */
    VPER3_1_2,     /**<  Volt: 1.20V */
    VPER3_1_5,     /**<  Volt: 1.50V */
    VPER3_2_8,     /**<  Volt: 2.80V */
    VPER3_SUPPLY_NUM
};

/**
 * @brief VSIM output voltage
 */
opaque_enum(VsimVolt_e_)
{
    VSIM_1_5 = 0, /**<  Volt: 1.50V */
    VSIM_1_8,     /**<  Volt: 1.80V */
    VSIM_2_9,     /**<  Volt: 2.90V */
    VSIM_3_0,     /**<  Volt: 3.00V */
    VSIM_SUPPLY_NUM
};

/**
 * @brief VA output voltage
 */
opaque_enum(VaVolt_e_)
{
    VA_1_5 = 0, /**<  Volt: 1.50V */
    VA_1_8,     /**<  Volt: 1.80V */
    VA_2_8,     /**<  Volt: 2.80V */
    VA_2_9,     /**<  Volt: 2.90V */
    VA_SUPPLY_NUM
};

/**
 * @brief VABBAUD output voltage
 */
opaque_enum(VabbaudVolt_e_)
{
    VABBAUD_1_8 = 0, /**<  Volt: 1.80V */
    VABBAUD_2_28,    /**<  Volt: 2.28V */
    VABBAUD_2_5,     /**<  Volt: 2.50V */
    VABBAUD_2_8,     /**<  Volt: 2.80V */
    VABBAUD_SUPPLY_NUM
};

/**
 * @brief VAUX output voltage
 */
opaque_enum(VauxVolt_e_)
{
    VAUX_1_8 = 0, /**<  Volt: 1.80V */
    VAUX_2_28,    /**<  Volt: 2.28V */
    VAUX_2_5,     /**<  Volt: 2.50V */
    VAUX_2_8,     /**<  Volt: 2.80V */
    VAUX_SUPPLY_NUM
};

/**
 * @brief VABBRF output voltage
 */
opaque_enum(VabbrfVolt_e_)
{
    VABBRF_1_8 = 0, /**<  Volt: 1.80V */
    VABBRF_2_28,    /**<  Volt: 2.28V */
    VABBRF_2_5,     /**<  Volt: 2.50V */
    VABBRF_2_8,     /**<  Volt: 2.80V */
    VABBRF_SUPPLY_NUM
};

/**
 * @brief VDIG output voltage
 */
opaque_enum(VdigVolt_e_)
{
    VDIG_1_2 = 0, /**<  Volt: 1.20V */
    VDIG_1_25,    /**<  Volt: 1.25V */
    VDIG_1_3,     /**<  Volt: 1.30V */
    VDIG_1_1,     /**<  Volt: 1.10V */
    VDIG_SUPPLY_NUM
};

/**
 * @brief VIO output voltage
 */
opaque_enum(VioVolt_e_)
{
    VIO_1_5 = 0, /**<  Volt: 1.50V */
    VIO_1_8,     /**<  Volt: 1.80V */
    VIO_2_5,     /**<  Volt: 2.50V */
    VIO_2_8,     /**<  Volt: 2.80V */
    VIO_SUPPLY_NUM
};

/**
 * @brief VDIGRF output voltage
 */
opaque_enum(VdigrfVolt_e_)
{
    VDIGRF_2_5 = 0, /**<  Volt: 2.50V */
    VDIGRF_1_8,     /**<  Volt: 1.80V */
    VDIGRF_2_8,     /**<  Volt: 2.80V */
    VDIGRF_2_9,     /**<  Volt: 2.90V */
    VDIGRF_SUPPLY_NUM
};

#if 0
/**
 * @brief General Purpose IO
 */
opaque_enum(GpioNumber_e_)
{
    GPIO_0 = 0,    ///<  GPIO 0
    GPIO_1,        ///<  GPIO 1
    GPIO_2,        ///<  GPIO 2
    GPIO_3,        ///<  GPIO 3
    GPIO_4,        ///<  GPIO 4
    GPIO_5,        ///<  GPIO 5
    GPIO_6,        ///<  GPIO 6
    GPIO_7,        ///<  GPIO 7
    NB_IO
};
#endif

/* MST change -- begin */
/**
 * @brief Power On Cause
 */
opaque_enum(PowerOnCause_e_)
{
    POWER_ON_NONE = 0,              ///<  no power on cause
    POWER_ON_NORMAL,                ///<  KEYON power on
    POWER_ON_CHARGER,               ///<  Charger power on
    POWER_ON_ALARM,                 ///<  Alarm power on
    POWER_ON_RESET,                 ///<  watch dog reset
    POWER_ON_TIMEEVT,               ///<  minute event power on
    POWER_ON_POWERCUT,              ///<  power-cut power on    //peterwei test for power-cut
    POWER_ON_SWRESET,               ///<  power-cut power on    //peterwei test for power-cut
    POWER_ON_NORMAL_KEY_RELEASE,    ///<  KEYON power on but not long press
    POWER_ON_SIMRESET,              ///<  SIM reset (special type of SW reset, branch to zero directly and skip some LCD init)
    POWER_ON_MAX                    ///<
};
/* MST change -- end */
#include "drv_power_forward.h"


/*--------------------------------------------------------------------------*/
/* VARIABLE DEFINITION                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

#endif //__DRV_POWER_TYPES_H__

