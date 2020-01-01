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
* @file    drv_int_ctrl_pub_api.h
* @version
* @brief   System wrapper header file for interrupts
*
*/

#ifndef __DRV_INT_CTRL_PUB_API_H__
#define __DRV_INT_CTRL_PUB_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
/*
#include "sys_MsWrapper_cus_os_type.h"
#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"
#include "incense_reg.h"
#include "kernel.h"
#include "sys_rtk_ho.h"
#include "sys_ext_int.h"
#include "sys_irq_ctrl.h"
*/
#include "hal_int_ctrl_pub.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/
extern u32 *isr_execution_ticks;
extern u32 *isr_execution_func;
extern u32 *isr_execution_services;
extern u32 *nested_isr_accumulation;
extern u32 sys_bSwdISRProfileOn;
extern u8 isr_execution_array_size;
extern u8 isr_accumulation_array_size;

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/**
 *
 * \brief Initialize the interrupt controller. The interrupts are initialized to be automatically
 *  acknowledged. All pending acknowledged interrupts before this call are cleared
 */
void DrvInitInterruptController(void);

/**
  *
  * \brief Initialize a interrupt and mask it
  * \param[in] psParam Parameters to initialize the interrupt
  * \param[in] u8IntNum Interrupt number
  * \return 0 if the result is OK. -1 otherwise.
  */
s32 DrvInitInterrupt(IntInitParam_u *puParam, IntNumber_e eIntNum);

/**
  * \brief Ack a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void DrvAckInterrupt(IntNumber_e eIntNum);

/**
  * \brief Clear a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void DrvClearInterrupt(IntNumber_e eIntNum);

/**
  * \brief Mask a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void DrvMaskInterrupt(IntNumber_e eIntNum);

/**
  * \brief Unmask a interrupt
  * \param[in] u8IntNum Interrupt line number
  */
void DrvUnmaskInterrupt(IntNumber_e eIntNum);

/**
  * \brief check an interrupt mask
  * \param[in] u8IntNum Interrupt line number
  * \retval    bool     TRUE: interrupt not masked, FALSE: interrupt masked.
  */
bool DrvIsMaskInterrupt(IntNumber_e eIntNum);

/**
  * \brief Get interrupt raw status
  * \param[in] ePadNum io line number
  * \param[out] pbRawStatus raw status of the interrupt
  * \retval    bool     TRUE: ok , FALSE: fail
  */
//bool DrvIntGetRawStatus(IntNumber_e eIntNum, bool *pbRawStatus);

/**
  * \brief Set ISR
  * \param[in] ePadNum io line number
  * \param[out] pbRawStatus raw status of the interrupt
  * \retval    bool     TRUE: ok , FALSE: fail
  */
void DrvIntcSetIsr(PfnIntcISR pfnIntcIsr, u32 nIntcNumber);

/**
  * \brief Set ISR
  * \param[in] ePadNum io line number
  * \param[out] pbRawStatus raw status of the interrupt
  * \retval    bool     TRUE: ok , FALSE: fail
  */
PfnIntcISR DrvIntcGetIsr(u32 nIntcNumber);



#endif // __DRV_INT_CTRL_PUB_API_H__

