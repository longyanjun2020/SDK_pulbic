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
* @file    drv_io_chip_pub_types.h
* @version
* @brief   Header for High level GPIO interface.
*
*/

#ifndef __DRV_IO_CHIP_PUB_TYPES_H__
#define __DRV_IO_CHIP_PUB_TYPES_H__

#ifndef __SDK_SIMULATION__
/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"
#include "hal_io_chip_pub.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

extern IoChipPadNum_e IO_CHIP_SDDL_BACKLIGHT_EN;
extern IoChipPadNum_e IO_CHIP_SDDL_BACKLIGHT_PWM;

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define IO_CHIP_BACKLIGHT_EN  IO_CHIP_SDDL_BACKLIGHT_EN
#define IO_CHIP_BACKLIGHT_PWM IO_CHIP_SDDL_BACKLIGHT_PWM

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 * @brief Signal index enumeration for pad mapping.
 */
typedef enum
{
    /* customer-defined GPIO */
    IO_CHIP_INDEX_BACKLIGHT_EN,
    IO_CHIP_INDEX_BACKLIGHT_PWM,
    IO_CHIP_INDEX_NONE
}IoChipSignalIndex_e;

/**
 * @brief The enumeration defines the PM devices.
 */
typedef enum
{
    MDL_PM_DEV_BACKLIGHT,         ///< Backlight
    MDL_PM_DEV_INVALID            ///< Invalid device
} MdlPmDevice_e;

typedef struct
{
    MdlPmDevice_e       eDevice; ///< Device mapping to the pad
    IoChipSignalIndex_e eIndex;  ///< Signal index
    IoChipPadNum_e      ePadNum; ///< Pad number
} IoChipSignalMapping_t;

/**
 * @brief Pwm Control Code definition
 */
typedef enum
{
    VM_IO_PWM_EN = 0, ///< Enable pwn function
    VM_IO_PWM_DIS,    ///< Disable pwn function
}VmIoPwm_e;

/**
 * @brief PWM parameters
 */
typedef enum
{
    VM_IO_PWM_CLKSEL_13M = 0,  ///< PWM 13MHz
    VM_IO_PWM_CLKSEL_32K = 1,  ///<PWM 32KHz
}VmIoPwmClkSel_e;

/**
 * @brief PWM parameters \n
 * PWM output freq = clksel/(prescaler+1)/period \n
 * PWM output duty = ratio/period \n
 * Note : Ratio must greater than 0
 */
typedef struct
{
    u8              period;    ///< Period
    u8              prescaler; ///< Prescaler
    u8              ratio;     ///< Ratio
    u8              cycle0;    ///< Cycle 0 : non-invert cycle
    u8              cycle1;    ///< Cycle 1 : invert cycle
    VmIoPwmClkSel_e clksel;    ///< ClkSel
}vm_IoPwmParam_t;

/**
 * @brief Error Code for gpio procedures
 */
typedef enum
{
    VM_IO_SUCCESS = 0,       ///< Process is done, nothing wrong
    VM_IO_INVALID_HANDLE,    ///< Client's handle is out of range or not in used
    VM_IO_INVALID_PARAMETER, ///< Configure pwn function with NULL paramater pointer
    VM_IO_IO_ALREADY_USED,   ///< IO is already used by other client
}VmIoErrorCode_e;

/**
 * @brief Pin State definition
 */
typedef enum
{
    VM_IO_LOW = 0, ///< Low State (0)
    VM_IO_HIGH,    ///< High State (1)
    VM_IO_SKIP     ///< Don't care, only used in DrvIoChipSetDirOutputGpio function
}VmIoState_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
///@endcond
/** @}*/
#endif // __SDK_SIMULATION__
#endif // __DRV_IO_CHIP_PUB_TYPES_H__

