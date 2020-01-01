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

/*=============================================================*/
// Include files
/*=============================================================*/

#include "drv_io_chip_pub_types.h"
#include "hal_io_chip_pub.h"

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

VmIoErrorCode_e DrvIoChipInitBacklightGpio(void);

/** 
* \fn VmIoErrorCode_e DrvIoChipSetDirOutputGpio(IoChipPadNum_e ePadNum, VmIoState_e eState)
* \brief        Setup the multiplex function of a pin as GPIO output.
*
* Ex: 
* \n Set IO_CHIP_BATT_BAT_EN as GPIO, direction as output, and state as high.
* \code
*        eIoState = DrvIoChipSetDirOutputGpio(IO_CHIP_BATT_BAT_EN, VM_IO_HIGH);  
* \endcode
*                 IO_CHIP_BATT_BAT_EN should define a pad in cust_gpio.c. \n
*                 See MSW8533x GPIO framework.ppt for further information
*
* \param[in]    ePadNum             GPIO pin to setup. Please check hal_io_chip_pub.h.
* \param[in]    eState              Initial GPIO output state.
*
* \retval       VM_IO_SUCCESS                           Success.
* \retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* \retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* \retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipSetDirOutputGpio(IoChipPadNum_e ePadNum, VmIoState_e eState);

/** 
* \fn VmIoErrorCode_e DrvIoChipUpGpio(IoChipPadNum_e ePadNum)
* \brief        Setup output of a GPIO pin to high state
*
* \param[in]    ePadNum             GPIO pin to setup. Please check hal_io_chip_pub.h.
*
* \retval       VM_IO_SUCCESS                           Success.
* \retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* \retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* \retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipUpGpio(IoChipPadNum_e ePadNum);

/** 
* \fn VmIoErrorCode_e DrvIoChipDwnGpio(IoChipPadNum_e ePadNum)
* \brief        Setup output of a GPIO pin to low state
*
* \param[in]    ePadNum             GPIO pin to setup. Please check hal_io_chip_pub.h.
*
* \retval       VM_IO_SUCCESS                           Success.
* \retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* \retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* \retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipDwnGpio(IoChipPadNum_e ePadNum);

#if 0
/** 
* \fn VmIoErrorCode_e DrvIoChipPwmCtrl(IoChipPadNum_e ePadNum, VmIoPwm_e eIoPwm, vm_IoPwmParam_t *ptIoPwmParam)
* \brief        Setup pwm pin
*
* \param[in]    ePadNum             GPIO pin to setup. Please check hal_io_chip_pub.h.
* \param[in]    eIoPwm              Pwm operation code.
* \param[in]    ptIoPwmParam        Parameter for PWM operation.
*
* \retval       VM_IO_SUCCESS                           Success.
* \retval       VM_IO_INVALID_HANDLE                    Invalid handle.
* \retval       VM_IO_INVALID_PARAMETER                 Invalid parameter.
* \retval       VM_IO_IO_ALREADY_USED                   Can't allocate this pad.
*
*/
extern VmIoErrorCode_e DrvIoChipPwmCtrl(IoChipPadNum_e ePadNum, VmIoPwm_e eIoPwm, vm_IoPwmParam_t *ptIoPwmParam);
#endif
#endif // __DRV_IO_CHIP_PUB_API_H__

