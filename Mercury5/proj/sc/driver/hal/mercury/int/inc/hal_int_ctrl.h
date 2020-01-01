////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    Hal_int_ctrl.h
* @version
* @brief   Hal header file for interrupts
*
*/

#ifndef __HAL_INT_CTRL_H__
#define __HAL_INT_CTRL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_vm_io_types.h"
#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"
#include "hal_int_ctrl_pub.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 *
 * \brief Initialize the interrupt controller. The interrupts are initialized to be automatically
 *  acknowledged. All pending acknowledged interrupts before this call are cleared
 */
void HalInitInterruptController(void);

/**
  *
  * \brief Initialize a interrupt and mask it
  * \param[in] psParam Parameters to initialize the interrupt
  * \param[in] u8IntNum Interrupt number
  * \return 0 if the result is OK. -1 otherwise.
  */
s32 HalInitInterrupt(IntInitParam_u *puParam, IntNumber_e eIntNum);

/**
  * \brief Ack a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void HalAckInterrupt(IntNumber_e eIntNum);

/**
  * \brief Clear a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void HalClearInterrupt(IntNumber_e eIntNum);

/**
  * \brief Mask a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void HalMaskInterrupt(IntNumber_e eIntNum);

/**
  * \brief Unmask a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void HalUnmaskInterrupt(IntNumber_e eIntNum);

/**
  * \brief check an interrupt mask
  * \param[in] u8IntNum Interrupt line number
  * \retval    bool     TRUE: interrupt not masked, FALSE: interrupt masked.
  */
bool HalIsMaskInterrupt(IntNumber_e eIntNum);

/** HalCommonIntHandler
* @brief        Common handler for both IRQ and FIQ
*
* @param[in]    eMap                Mapping.
*
* @retval
*
*/
void HalCommonIntHandler(IntcMap_e eMap);

/** HalIntGetRawStatus
* @brief        Read raw status register
*
* @param[in]    eIntNum             The interrupt number of an external interrupt pin.
* @param[out]   pbRawStatus         Pointer to return raw status; TRUE is high and FALSE is low.
*
* @retval       TRUE                                    Success.
* @retval       FALSE                                   Failure.
*
*/
//bool HalIntGetRawStatus(IntNumber_e eIntNum, bool *pbRawStatus);

	
/** IntcInitialize
* @brief		 Initialize an interrupt on INTC
*
* @param[in]	 ptIntcParam		 Initialize parameters.
* @param[in]	 nIntcNumber		 Interrupt number.
*
* @retval
*
*/
extern void IntcInitialize(IntcParam_t *ptIntcParam, u32 nIntcNumber);

/** IntcUnMask
* @brief		 Unmask an interrupt on INTC
*
* @param[in]	 nIntcNumber		 Interrupt number.
*
* @retval
*
*/
extern void IntcUnMask(u32 nIntcNumber);

/** IntcSetIsr
* @brief		 Set ISR pointer of specific IRQ on INTC
*
* @param[in]	 pfnIntcIsr		 Function pointer of ISR.
* @param[in]	 nIntcNumber		 Interrupt number.
*
* @retval
*
*/
extern void IntcSetIsr(PfnIntcISR pfnIntcIsr, u32 nIntcNumber);

/** IntcGetIsr
* @brief		 Get ISR pointer of specific IRQ on INTC
*
* @param[in]	 nIntcNumber		 Interrupt number.
*
* @retval 	 PfnIntcISR						 Pointer of ISR.
*
*/
extern PfnIntcISR IntcGetIsr(u32 nIntcNumber);


#endif // __HAL_INT_CTRL_H__

