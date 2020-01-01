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
* @file    drv_vm_io_forward.h
* @version
* @brief   nput/Output Public Interface
*
*/

#ifndef __DRV_VM_IO_FORWARD_H__
#define __DRV_VM_IO_FORWARD_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
// Serial ports
opaque_enum(vm_ioPort_e_);
typedef enum vm_ioPort_e_ vm_ioPort_e;

/* Multiplexed features definition structure */
opaque_enum(vm_ioFeature_e_);
typedef enum vm_ioFeature_e_ vm_ioFeature_e;

// Serial states
opaque_enum(vm_ioSerialSwitchState_e_);
typedef enum vm_ioSerialSwitchState_e_ vm_ioSerialSwitchState_e;

typedef struct vm_ioSerialSwitchStateRsp_t_ vm_ioSerialSwitchStateRsp_t;

// Update type for Port update
opaque_enum(vm_ioPortUpdateType_e_);
typedef enum vm_ioPortUpdateType_e_ vm_ioPortUpdateType_e;

// Message Body for VM_IO_PORT_UPDATE_INFO
typedef struct vm_ioPortUpdateInfo_t_ vm_ioPortUpdateInfo_t;

// Update type for gpio update
opaque_enum(vm_ioUpdateType_e_);
typedef enum vm_ioUpdateType_e_ vm_ioUpdateType_e;

// Message Body for VM_IO_UPDATE_INFO
typedef struct vm_ioUpdateInfo_t_ vm_ioUpdateInfo_t;

// IO TYPE
opaque_enum(VmIoType_e_);
typedef enum VmIoType_e_ VmIoType_e;

typedef u32 VmIoHandle_t;

/**
 * @brief Pin State definition
 */
opaque_enum(VmIoState_e_);
typedef enum VmIoState_e_ VmIoState_e;

/**
 * @brief Pwm Control Code definition
 */
opaque_enum(VmIoPwm_e_);
typedef enum VmIoPwm_e_ VmIoPwm_e;

/**
 * @brief PWM parameters
 */
opaque_enum(VmIoPwmClkSel_e_);
typedef enum VmIoPwmClkSel_e_ VmIoPwmClkSel_e;

/**
 * @brief PWM parameters
 * PWM output freq = clksel/(prescaler+1)/period
 * PWM output duty = ratio/period
 * Note : Ratio must greater than 0
 */
typedef struct vm_IoPwmParam_t_ vm_IoPwmParam_t;

/**
 * @brief Duty cycle of a LED component ( @ref VM_IO_ABB_LED_RED, @ref VM_IO_ABB_LED_GREEN, @ref VM_IO_ABB_LED_BLUE)
 */
opaque_enum(vm_IoAbbLedDutyCycle_t_);
typedef enum vm_IoAbbLedDutyCycle_t_ vm_IoAbbLedDutyCycle_t;

/**
 * @brief Analog BaseBand RGB LED mode
 */
opaque_enum(vm_IoAbbLedRGBMode_t_);
typedef enum vm_IoAbbLedRGBMode_t_ vm_IoAbbLedRGBMode_t;

/**
 * @brief Analog BaseBand RGB Led parameters
 */
typedef struct vm_IoAbbRGBParam_t_ vm_IoAbbRGBParam_t;

/**
 * @brief Error Code for gpio procedures
 */
opaque_enum(VmIoErrorCode_e_);
typedef enum VmIoErrorCode_e_ VmIoErrorCode_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif // __DRV_VM_IO_FORWARD_H__

