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
* @file    hal_sys_ext_int.h
* @version
* @brief   External interrupt controller header file
*
*/

#ifndef __HAL_SYS_EXT_INT_H__
#define __HAL_SYS_EXT_INT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "sys_sys_vm_sys.h"
#include "drv_io_chip_pub_forward.h"
#include "hal_ext_int.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define EXT_INT_FATAL    (_SYS|FATAL)
#define EXT_INT_ERROR    (_SYS)
#define EXT_INT_WARN     (_SYS)

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
#ifndef __SDK_SIMULATION__
/** ExtIntInitController
* @brief        Initialize external interrupt controller
*
* @param[in]
*
* @retval
*
*/
extern void ExtIntInitController(void);

/** ExtIntExecuteUserIsrs
* @brief        Check status register and execute ISRs installed by driver
*
* @param[in]    eExtIntMap          The mapping to system interrupt controller
*
* @retval
*
*/
extern void ExtIntExecuteUserIsrs(ExtIntMap_e eExtIntMap);

/** ExtIntSetClkDebCfg
* @brief        Set the clock division factor of debounce logic
*
* @param[in]    eDebClkDiv          Clock division factor for debounce.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
extern bool ExtIntSetClkDebCfg(ExtIntClkDiv_e eClkDiv);

/** ExtIntInitialize
* @brief        Initialize an external interrupt
*
* @param[in]    ptItParam           Initialization parameter of an external interrupt.
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
extern bool ExtIntInitialize(ExtIntParam_t *ptItParam, IoChipPadNum_e ePadNum);

/** ExtIntMask
* @brief        Mask an external interrupt
*
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
extern bool ExtIntMask(IoChipPadNum_e ePadNum);

/** ExtIntUnMask
* @brief        Unmask an external interrupt
*
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
extern bool ExtIntUnMask(IoChipPadNum_e ePadNum);

/** ExtIntIsMask
* @brief        Check an external interrupt is masked or not.
*
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
*
* @retval       TRUE                Interrupt is not masked.
* @retval       FALSE               Interrupt is masked.
*
*/
extern bool ExtIntIsMask(IoChipPadNum_e ePadNum);

/** ExtIntClear
* @brief        Clear an external interrupt
*
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
extern bool ExtIntClear(IoChipPadNum_e ePadNum);

/** ExtIntGetRawStatus
* @brief        Read raw status register
*
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
* @param[out]   pbRawStatus         Pointer to return raw status; TRUE is high and FALSE is low.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
extern bool ExtIntGetRawStatus(IoChipPadNum_e ePadNum, bool *pbRawStatus);

#endif // __SDK_SIMULATION__
#endif // __HAL_SYS_EXT_INT_H__

