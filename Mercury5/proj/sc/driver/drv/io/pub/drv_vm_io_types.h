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
* @file    drv_vm_io_types.h
* @version
* @brief   nput/Output Public Interface
*
*/

#ifndef __DRV_VM_IO_TYPES_H__
#define __DRV_VM_IO_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_vm_io_forward.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
// Request return values
#define VM_IO_SWITCH_SERIAL_OK            (0)
#define VM_IO_SWITCH_SERIAL_MODE_UNKNOWN  (-2)
#define VM_IO_SWITCH_SERIAL_FLOW_CLOSED   (-3)

#define VM_IO_O_LO            0x00UL
#define VM_IO_O_HI            0x01UL

/* default option for pad initialization, don't use it in code */
#define VM_IO_DEFAULT         0xFFUL

#define VM_IO_NULL_HANDLE  (VmIoHandle_t)0xFFFFUL

/*=============================================================*/
// Data type definition
/*=============================================================*/
// Serial ports
opaque_enum(vm_ioPort_e_)
{
    VM_IO_NO_PORT                 = 0x00,
    VM_IO_USB                     = 0x00, // USB port
    VM_IO_UART1                   = 0x01, // Uart 1 port
    VM_IO_UART2                   = 0x02, // Uart 2 port
    VM_IO_UART_MAX                = 0x03,

    VM_IO_UART1_VIRTUAL_BASE      = 0x10, // Base for UART1 virtual ports
    VM_IO_UART2_VIRTUAL_BASE      = 0x20, // Base for UART2 virtual ports
    VM_IO_USB_VIRTUAL_BASE        = 0x30, // Base for USB virtual ports
    VM_IO_BLUETOOTH_VIRTUAL_BASE  = 0x40, // Base for BlueTooth virtual ports
    VM_IO_GSM_BASE                = 0x50, // Base for GSM CSD FCM data flow
    VM_IO_GPRS_BASE               = 0x60, // Base for GPRS FCM Data flow
    VM_IO_OPEN_AT_VIRTUAL_BASE    = 0x80  // Base for Open-AT application tasks
};

/* Multiplexed features definition structure */
opaque_enum(vm_ioFeature_e_)
{
    VM_IO_FEATURE_NONE,
    VM_IO_FEATURE_BUS_SPI1_CLK,           // SPI 1 bus Clock pin
    VM_IO_FEATURE_BUS_SPI1_IO,            // SPI 1 bus bi-directional data / uni-directional output pin
    VM_IO_FEATURE_BUS_SPI1_I,             // SPI 1 bus uni-directional input pin
    VM_IO_FEATURE_BUS_SPI1_CS,            // SPI 1 hardware chip select pin
    VM_IO_FEATURE_BUS_SPI2_CLK,           // SPI 2 bus Clock pin
    VM_IO_FEATURE_BUS_SPI2_IO,            // SPI 2 bus bi-directional data / uni-directional output pin
    VM_IO_FEATURE_BUS_SPI2_I,             // SPI 2 bus uni-directional input pin
    VM_IO_FEATURE_BUS_SPI2_CS,            // SPI 2 hardware chip select pin
    VM_IO_FEATURE_BUS_I2C,                // I2C bus
    VM_IO_FEATURE_BUS_PARALLEL_ADDR1,     // Parallel bus address pin
    VM_IO_FEATURE_BUS_PARALLEL_ADDR2_CS2, // Parallel bus Chip Select 2 / address pin
    VM_IO_FEATURE_KBD,                    // Keypad
    VM_IO_FEATURE_SIMPRES,                // SIM presence signal
    VM_IO_FEATURE_UART1,                  // UART 1 port
    VM_IO_FEATURE_UART2,                  // UART 2 port
    VM_IO_FEATURE_INT0,                   // External interrupt INT0 pin
    VM_IO_FEATURE_INT1,                   // External interrupt INT1 pin
    VM_IO_FEATURE_BT_RST,                 // Bluetooth reset signal
    VM_IO_FEATURE_LAST
};

// Serial states
opaque_enum(vm_ioSerialSwitchState_e_)
{
    VM_IO_SERIAL_AT_MODE,   /* module computes incoming at commands                 */
    VM_IO_SERIAL_DATA_MODE, /* module transmit all incoming datas to open at        */
    VM_IO_SERIAL_ATO,       /* back to online mode after a +++ from external device */

    // Not usable with the vm_ioSerialSwitchState API
    VM_IO_SERIAL_AT_OFFLINE /* the serial port is switched to offline mode by a "+++" sequence */
};

struct vm_ioSerialSwitchStateRsp_t_
{
    vm_ioSerialSwitchState_e  SerialMode;     /* serial mode requested     */
    s8                        RequestReturn;  /* a value < 0 means refused */
    /* RequestReturn may take the values :                                   */
    /* VM_IO_SWITCH_SERIAL_OK                                                */
    /* VM_IO_SWITCH_SERIAL_MODE_UNKNOWN                                      */
    /* VM_IO_SWITCH_SERIAL_FLOW_CLOSED                                       */
    vm_ioPort_e               Port;           /* switched serial port      */
};

// Update type for Port update
opaque_enum(vm_ioPortUpdateType_e_)
{
    VM_IO_PORT_UPDATE_OPENED, // New opened port
    VM_IO_PORT_UPDATE_CLOSED  // The port is now closed
};

// Message Body for VM_IO_PORT_UPDATE_INFO
struct vm_ioPortUpdateInfo_t_
{
    vm_ioPort_e              Port;    // Port identifier
    vm_ioPortUpdateType_e    Update;  // Update type (Opened/Closed)
};

// Update type for gpio update
opaque_enum(vm_ioUpdateType_e_)
{
    VM_IO_UPDATE_TYPE_ALLOCATION,
    VM_IO_UPDATE_TYPE_RELEASE
};

// Message Body for VM_IO_UPDATE_INFO
struct vm_ioUpdateInfo_t_
{
    vm_ioUpdateType_e UpdateType;         // Update type (allocation or release)
    u8                FeaturesNb;         // Number of allocated/released features
    vm_ioFeature_e    UpdatedFtrList[1];  // Updates features table
};

// IO TYPE
opaque_enum(VmIoType_e_)
{
    VM_IO_NOT_USED,   /**< IO type : Not Used (0)  */
    VM_IO_BASEBAND,   /**< IO type : BaseBand (1)  */
    VM_IO_GPIO,       /**< IO type : GPIO     (2)  */
};

/**
 * @brief Pin State definition
 */
opaque_enum(VmIoState_e_)
{
    VM_IO_LOW = 0, ///< Low State (0)
    VM_IO_HIGH,    ///< High State (1)
    VM_IO_SKIP     ///< Don't care, only used in DrvIoChipSetDirOutputGpio function
};

/**
 * @brief Pwm Control Code definition
 */
opaque_enum(VmIoPwm_e_)
{
    VM_IO_PWM_EN = 0, ///< enable pwn function
    VM_IO_PWM_DIS,    ///< disable pwn function
};

/**
 * @brief PWM parameters
 */
opaque_enum(VmIoPwmClkSel_e_)
{
    VM_IO_PWM_CLKSEL_13M = 0,
    VM_IO_PWM_CLKSEL_32K = 1,
};

/**
 * @brief PWM parameters
 * PWM output freq = clksel/(prescaler+1)/period
 * PWM output duty = ratio/period
 * Note : Ratio must greater than 0
 */
struct vm_IoPwmParam_t_
{
    u8              period;    ///< Period
    u8              prescaler; ///< Prescaler
    u8              ratio;     ///< Ratio
    u8              cycle0;    ///< Cycle 0 : non-invert cycle
    u8              cycle1;    ///< Cycle 1 : invert cycle
    VmIoPwmClkSel_e clksel;    ///< ClkSel
};

/**
 * @brief Duty cycle of a LED component ( @ref VM_IO_ABB_LED_RED, @ref VM_IO_ABB_LED_GREEN, @ref VM_IO_ABB_LED_BLUE)
 */
opaque_enum(vm_IoAbbLedDutyCycle_t_)
{
    VM_IO_ABB_LED_0_PER_15 = 0, ///< always inactive
    VM_IO_ABB_LED_1_PER_15,     ///< active 1/15 of the time
    VM_IO_ABB_LED_2_PER_15,     ///< active 2/15 of the time
    VM_IO_ABB_LED_3_PER_15,     ///< active 3/15 of the time
    VM_IO_ABB_LED_4_PER_15,     ///< active 4/15 of the time
    VM_IO_ABB_LED_5_PER_15,     ///< active 5/15 of the time
    VM_IO_ABB_LED_6_PER_15,     ///< active 6/15 of the time
    VM_IO_ABB_LED_7_PER_15,     ///< active 7/15 of the time
    VM_IO_ABB_LED_8_PER_15,     ///< active 8/15 of the time
    VM_IO_ABB_LED_9_PER_15,     ///< active 9/15 of the time
    VM_IO_ABB_LED_10_PER_15,    ///< active 10/15 of the time
    VM_IO_ABB_LED_11_PER_15,    ///< active 11/15 of the time
    VM_IO_ABB_LED_12_PER_15,    ///< active 12/15 of the time
    VM_IO_ABB_LED_13_PER_15,    ///< active 13/15 of the time
    VM_IO_ABB_LED_14_PER_15,    ///< active 14/15 of the time
    VM_IO_ABB_LED_15_PER_15     ///< always active
};

/**
 * @brief Analog BaseBand RGB LED mode
 */
opaque_enum(vm_IoAbbLedRGBMode_t_)
{
    VM_IO_ABB_LED_PULSE_MODE = 0, ///< Pulse mode
    VM_IO_ABB_LED_ROTATION_MODE   ///< Rotation mode
};

/**
 * @brief Analog BaseBand RGB Led parameters
 */
struct vm_IoAbbRGBParam_t_
{
    vm_IoAbbLedDutyCycle_t dutyCycles[3]; ///< Duty cycles of the 3 components (Red, Green, Blue)
    vm_IoAbbLedRGBMode_t   RGBMode;
    u8                     offTime;
    u8                     onTime;
    bool                   repeat;
};

/**
 * @brief Error Code for gpio procedures
 */
opaque_enum(VmIoErrorCode_e_)
{
    VM_IO_SUCCESS = 0,       ///< Process is done, nothing wrong
    VM_IO_INVALID_HANDLE,    ///< Client's handle is out of range or not in used
    VM_IO_INVALID_PARAMETER, ///< Configure pwn function with NULL paramater pointer
    VM_IO_IO_ALREADY_USED,   ///< IO is already used by other client
};

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif // __DRV_VM_IO_TYPES_H__

