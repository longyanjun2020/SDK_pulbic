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
* @file    drv_io_chip_pub_api.h
* @version
* @brief   Header for High level GPIO interface.
*
*/

#ifndef __DRV_IO_CHIP_PUB_API_H__
#define __DRV_IO_CHIP_PUB_API_H__

#ifndef __SDK_SIMULATION__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "hal_io_chip_pub.h"
#include "drv_io_chip_pub_forward.h"
#include "drv_vm_io_forward.h"
#include "mdl_pm.h"		// TODO : include forward instead

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** DrvIoChipInitSubsystem
* @brief        Initialize IoChip subsystem
*
* @param[in]
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipInitSubsystem(void);

/** DrvIoChipSetFunction
* @brief        Setup the multiplex function of a pin
*
* @param[in]    ePadNum             GPIO pin to setup.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipSetFunction(IoChipPadNum_e ePadNum);

/** DrvIoChipSetDirInputGpio
* @brief        Setup the multiplex function of a pin as GPIO input
*
* @param[in]    ePadNum             GPIO pin to setup.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipSetDirInputGpio(IoChipPadNum_e ePadNum);

/** DrvIoChipSetDirOutputGpio
* @brief        Setup the multiplex function of a pin as GPIO output
*
* @param[in]    ePadNum             GPIO pin to setup.
* @param[in]    eState              Initial GPIO output state.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipSetDirOutputGpio(IoChipPadNum_e ePadNum, VmIoState_e eState);

/** DrvIoChipAcqGpio
* @brief        Read from a GPIO pin
*
* @param[in]    ePadNum             GPIO pin to read.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoState_e DrvIoChipAcqGpio(IoChipPadNum_e ePadNum);

/** DrvIoChipSetPull
* @brief        Setup pull of a GPIO pin
*
* @param[in]    ePadNum             GPIO pin to setup.
* @param[in]    ePull               Pull type.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipSetPull(IoChipPadNum_e ePadNum, IoChipPull_e ePull);

/** DrvIoChipUpGpio
* @brief        Setup output of a GPIO pin to high state
*
* @param[in]    ePadNum             GPIO pin to setup.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipUpGpio(IoChipPadNum_e ePadNum);

/** DrvIoChipDwnGpio
* @brief        Setup output of a GPIO pin to low state
*
* @param[in]    ePadNum             GPIO pin to setup.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipDwnGpio(IoChipPadNum_e ePadNum);

/** DrvIoChipSetSlewRate
* @brief        Setup driving current of a GPIO pin
*
* @param[in]    ePadNum             GPIO pin to setup.
* @param[in]    eDrive              Drive type.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipSetSlewRate(IoChipPadNum_e ePadNum, IoChipDrive_e eDrive);

/** DrvIoChipPwmCtrl
* @brief        Setup pwm pin
*
* @param[in]    ePadNum             GPIO pin to setup.
* @param[in]    eIoPwm              Pwm operation code.
* @param[in]    ptIoPwmParam        Parameter for PWM operation.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipPwmCtrl(IoChipPadNum_e ePadNum, VmIoPwm_e eIoPwm, vm_IoPwmParam_t *ptIoPwmParam);

/** DrvIoChipGetIoNumber
* @brief        Find default GPIO output function number
*
* @param[in]    bMmpPad             Is MMP pad or DBB pad.
* @param[in]    nNumber             GPIO number.
*
* @retval       PAD_NUM_INVALID                         Fail.
* @retval       OTHER VALUE                             Success.
*
*/
extern IoChipPadNum_e DrvIoChipGetIoNumber(bool bMmpPad, u32 nNumber);

/** DrvIoChipIsIoNumberEqual
* @brief        Check if two IoChipPadNum_e type data are same pin
*
* @param[in]    ePadNum1            GPIO pin to compare.
* @param[in]    ePadNum2            GPIO pin to compare.
*
* @retval       TRUE                                    Same pin.
* @retval       FALSE                                   Not same pin.
*
*/
extern bool DrvIoChipIsIoNumberEqual(IoChipPadNum_e ePadNum1, IoChipPadNum_e ePadNum2);

/** DrvIoChipAllocate
* @brief        Allocate a GPIO pin
*
* @param[in]    ePadNum             GPIO pin to setup.
* @param[out]   ptIoHandle          Pointer to allocate handle.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipAllocate(IoChipPadNum_e ePadNum, VmIoHandle_t *ptIoHandle);

/** DrvIoChipRelease
* @brief        Release a GPIO pin
*
* @param[in/out]ptIoHandle          Handle to destroy.
* @param[in]    eOption             Option to handle this pad after release.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipRelease(VmIoHandle_t *ptIoHandle, IoChipReleaseOption_e eOption);

/** DrvIoChipEnterSleepMode
* @brief        Configure baseband GPIO registers before entering sleep mode
*
* @param[in]
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipEnterSleepMode(void);

/** DrvIoChipLeaveSleepMode
* @brief        Restore baseband GPIO registers after leaving sleep mode
*
* @param[in]
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipLeaveSleepMode(void);

/** DrvIoChipPadPowerEnable
* @brief        Enable pad power
*
* @param[in]    ePadNum             GPIO pin to enable pad power.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipPadPowerEnable(IoChipPadNum_e ePadNum);

/** DrvIoChipPadPowerEnable
* @brief        Disable pad power
*
* @param[in]    ePadNum             GPIO pin to disable pad power.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipPadPowerDisable(IoChipPadNum_e ePadNum);

/** DrvIoChipDevPadPowerCtl
* @brief        Hook function for power manager to enable/disable pad power
*
* @param[in]    eDevice             The device to turn on/off.
* @param[in]    ePowerReq           Request to turn on/off device.
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipDevPadPowerCtl(MdlPmDevice_e eDevice, MdlPmPowerReq_e ePowerReq);

/** DrvIoChipRfPadEnable
* @brief        Configure RF pads
*
* @param[in]
*
* @retval       VM_IO_SUCCESS                           Success.
* @retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* @retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* @retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipRfPadEnable(bool bEnable);

VmIoErrorCode_e DrvIoChipGetGPIORegAddr(IoChipPadNum_e ePadNum,u32 *addr);

extern bool DrvIoIsChipRfPadEnable(void);

#endif // __SDK_SIMULATION__
#endif // __DRV_IO_CHIP_PUB_API_H__

