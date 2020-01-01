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
* @file    hal_ext_int.h
* @version
* @brief   External interrupt controller header file
*
*/

#ifndef __HAL_EXT_INT_H__
#define __HAL_EXT_INT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "hal_ext_int_pub.h"
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
#ifndef __SDK_SIMULATION__
/** HalExtIntInit
* @brief        Initialize external interrupt controller
*
* @param[in]
*
* @retval
*
*/
extern void HalExtIntInit(void);

/** HalExtIntInstallIrq
* @brief        Install INTC interrupt if necessary
*
* @param[in]    eExtIntMap          Interrupt mapping to INTC.
*
* @retval
*
*/
void HalExtIntInstallIrq(ExtIntMap_e eExtIntMap);

/** HalExtIntSetClkDebCfgReg
* @brief        Setup debounce clock division factor
*
* @param[in]    eExtIntClkDiv       Debounce clock division factor.
*
* @retval
*
*/
extern void HalExtIntSetClkDebCfgReg(ExtIntClkDiv_e eExtIntClkDiv);

/** HalExtIntSetCfgReg
* @brief        Setup EXT_INT_CFG register for specific interrupt
*
* @param[in]    eExtIntNumber       External interrupt number.
* @param[in]    eExtIntPolarity     Polarity.
* @param[in]    eExtIntMode         Processing mode.
* @param[in]    eExtIntDebounce     Debounce time.
*
* @retval
*
*/
extern void HalExtIntSetCfgReg(ExtIntNumber_e eExtIntNumber, ExtIntPolarity_e eExtIntPolarity, ExtIntMode_e eExtIntMode, ExtIntDebounce_e eExtIntDebounce);

/** HalExtIntMask
* @brief        Mask an interrupt on EXT_INT
*
* @param[in]    eExtIntMap          Interrupt mapping to INTC.
* @param[in]    eExtIntNumber       External interrupt number.
*
* @retval
*
*/
extern void HalExtIntMask(ExtIntMap_e eExtIntMap, ExtIntNumber_e eExtIntNumber);

/** HalExtIntUnmask
* @brief        Unmask an interrupt on EXT_INT
*
* @param[in]    eExtIntMap          Interrupt mapping to INTC.
* @param[in]    eExtIntNumber       External interrupt number.
*
* @retval
*
*/
extern void HalExtIntUnmask(ExtIntMap_e eExtIntMap, ExtIntNumber_e eExtIntNumber);

/** HalExtIntIsMask
* @brief        Check an external interrupt is masked or not.
*
* @param[in]    eExtIntMap          Interrupt mapping to INTC.
* @param[in]    eExtIntNumber       External interrupt number.
*
* @retval       TRUE                Interrupt is not masked.
* @retval       FALSE               Interrupt is masked.
*
*/
extern bool HalExtIntIsMask(ExtIntMap_e eExtIntMap, ExtIntNumber_e eExtIntNumber);

/** HalExtIntClear
* @brief        Clear an interrupt on EXT_INT
*
* @param[in]    eExtIntNumber       External interrupt number.
*
* @retval
*
*/
extern void HalExtIntClear(ExtIntNumber_e eExtIntNumber);

/** HalExtIntMaskAll
* @brief        Mask an interrupt on EXT_INT for all mask registers
*
* @param[in]    eExtIntNumber       External interrupt number.
*
* @retval
*
*/
extern void HalExtIntMaskAll(ExtIntNumber_e eExtIntNumber);

/** HalExtIntGetStatus
* @brief        Unmask an interrupt on EXT_INT
*
* @param[in]    eExtIntMap          Interrupt mapping to INTC.
* @param[in]    eExtIntNumber       External interrupt number.
*
* @retval       u32                                     32-bit register value.
*
*/
extern u32 HalExtIntGetStatus(ExtIntMap_e eExtIntMap);

/** ExtIntGetRawStatus
* @brief        Read raw status register
*
* @param[in]
*
* @retval       u32                                     32-bit register value.
*
*/
extern u32 HalExtIntGetRawStatus(void);

/** HalExtIntAllocateExtIntNumber
* @brief        Query the external interrupt number
*
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
*
* @retval       ExtIntNumber_e                          External interrupt number.
*
*/
extern ExtIntNumber_e HalExtIntAllocateExtIntNumber(IoChipPadNum_e ePadNum);

/** HalExtIntSetExtIntFunction
* @brief        Configure pin function as external interrupt
*
* @param[in]    ePadNum             The GPIO number of an external interrupt pin.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
extern bool HalExtIntSetExtIntFunction(IoChipPadNum_e ePadNum);

#endif // __SDK_SIMULATION__
#endif // __HAL_EXT_INT_H__

