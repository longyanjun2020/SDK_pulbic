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
* @file    hal_int_irq.h
* @version
* @brief   HAL header for interrupt
*
*/

#ifndef __HAL_INT_IRQ_H__
#define __HAL_INT_IRQ_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "kernel.h"
#include "hal_int_irq_pub.h"
#include "hal_int_ctrl_pub.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/


/**
 * Read pending register only once in one interrupt
 */
//#define INTC_HANDLE_ONE_IRQ_ONLY

/**
 * Ignore re-entry of MMP interrupt
 */
//#define INTC_BB2_WORKAROUND

#define INTC_READ_FIQ_MASK0_REG(x)           do {(x) = g_pKeIrqControl->u32_Fiq_Mask0;} while(0)
#define INTC_READ_FIQ_MASK1_REG(x)           do {(x) = g_pKeIrqControl->u32_Fiq_Mask1;} while(0)
#define INTC_READ_FIQ_MASK2_REG(x)           do {(x) = g_pKeIrqControl->u32_Fiq_Mask2;} while(0)
#define INTC_READ_FIQ_MASK3_REG(x)           do {(x) = g_pKeIrqControl->u32_Fiq_Mask3;} while(0)
#define INTC_READ_IRQ_MASK0_REG(x)           do {(x) = g_pKeIrqControl->u32_Irq_Mask0;} while(0)
#define INTC_READ_IRQ_MASK1_REG(x)           do {(x) = g_pKeIrqControl->u32_Irq_Mask1;} while(0)
#define INTC_READ_IRQ_MASK2_REG(x)           do {(x) = g_pKeIrqControl->u32_Irq_Mask2;} while(0)
#define INTC_READ_IRQ_MASK3_REG(x)           do {(x) = g_pKeIrqControl->u32_Irq_Mask3;} while(0)
#define INTC_WRITE_FIQ_MASK0_REG(x)          do {g_pKeIrqControl->u32_Fiq_Mask0 = (x);} while(0)
#define INTC_WRITE_FIQ_MASK1_REG(x)          do {g_pKeIrqControl->u32_Fiq_Mask1 = (x);} while(0)
#define INTC_WRITE_FIQ_MASK2_REG(x)          do {g_pKeIrqControl->u32_Fiq_Mask2 = (x);} while(0)
#define INTC_WRITE_FIQ_MASK3_REG(x)          do {g_pKeIrqControl->u32_Fiq_Mask3 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK0_REG(x)          do {g_pKeIrqControl->u32_Irq_Mask0 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK1_REG(x)          do {g_pKeIrqControl->u32_Irq_Mask1 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK2_REG(x)          do {g_pKeIrqControl->u32_Irq_Mask2 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK3_REG(x)          do {g_pKeIrqControl->u32_Irq_Mask3 = (x);} while(0)

#define INTC_MASK_FIQ_MASK0_REG(mask)        do {g_pKeIrqControl->u32_Fiq_Mask0 |= (mask);} while(0)
#define INTC_MASK_FIQ_MASK1_REG(mask)        do {g_pKeIrqControl->u32_Fiq_Mask1 |= (mask);} while(0)
#define INTC_MASK_FIQ_MASK2_REG(mask)        do {g_pKeIrqControl->u32_Fiq_Mask2 |= (mask);} while(0)
#define INTC_MASK_FIQ_MASK3_REG(mask)        do {g_pKeIrqControl->u32_Fiq_Mask3 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK0_REG(mask)        do {g_pKeIrqControl->u32_Irq_Mask0 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK1_REG(mask)        do {g_pKeIrqControl->u32_Irq_Mask1 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK2_REG(mask)        do {g_pKeIrqControl->u32_Irq_Mask2 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK3_REG(mask)        do {g_pKeIrqControl->u32_Irq_Mask3 |= (mask);} while(0)
#define INTC_UNMASK_FIQ_MASK0_REG(mask)      do {g_pKeIrqControl->u32_Fiq_Mask0 &= ~(mask);} while(0)
#define INTC_UNMASK_FIQ_MASK1_REG(mask)      do {g_pKeIrqControl->u32_Fiq_Mask1 &= ~(mask);} while(0)
#define INTC_UNMASK_FIQ_MASK2_REG(mask)      do {g_pKeIrqControl->u32_Fiq_Mask2 &= ~(mask);} while(0)
#define INTC_UNMASK_FIQ_MASK3_REG(mask)      do {g_pKeIrqControl->u32_Fiq_Mask3 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK0_REG(mask)      do {g_pKeIrqControl->u32_Irq_Mask0 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK1_REG(mask)      do {g_pKeIrqControl->u32_Irq_Mask1 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK2_REG(mask)      do {g_pKeIrqControl->u32_Irq_Mask2 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK3_REG(mask)      do {g_pKeIrqControl->u32_Irq_Mask3 &= ~(mask);} while(0)

#define INTC_CLR_INT_FIQ0_REG(mask)          do {g_pKeIrqControl->u32_Fiq_Status0 |= mask;} while(0)
#define INTC_CLR_INT_FIQ1_REG(mask)          do {g_pKeIrqControl->u32_Fiq_Status1 |= mask;} while(0)
#define INTC_CLR_INT_FIQ2_REG(mask)          do {g_pKeIrqControl->u32_Fiq_Status2 |= mask;} while(0)
#define INTC_CLR_INT_FIQ3_REG(mask)          do {g_pKeIrqControl->u32_Fiq_Status3 |= mask;} while(0)

#define INTC_SET_FIQ_POLARITY0_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity0 |= (mask);} while(0)
#define INTC_SET_FIQ_POLARITY1_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity1 |= (mask);} while(0)
#define INTC_SET_FIQ_POLARITY2_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity2 |= (mask);} while(0)
#define INTC_SET_FIQ_POLARITY3_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity3 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY0_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity0 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY1_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity1 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY2_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity2 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY3_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity3 |= (mask);} while(0)
#define INTC_CLR_FIQ_POLARITY0_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity0 &= ~(mask);} while(0)
#define INTC_CLR_FIQ_POLARITY1_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity1 &= ~(mask);} while(0)
#define INTC_CLR_FIQ_POLARITY2_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity2 &= ~(mask);} while(0)
#define INTC_CLR_FIQ_POLARITY3_REG(mask)     do {g_pKeIrqControl->u32_Fiq_Polarity3 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY0_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity0 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY1_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity1 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY2_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity2 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY3_REG(mask)     do {g_pKeIrqControl->u32_Irq_Polarity3 &= ~(mask);} while(0)

// int_ctrl_1
#define INTC_READ_FIQ_MASK0_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Fiq_Mask0;} while(0)
#define INTC_READ_FIQ_MASK1_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Fiq_Mask1;} while(0)
#define INTC_READ_FIQ_MASK2_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Fiq_Mask2;} while(0)
#define INTC_READ_FIQ_MASK3_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Fiq_Mask3;} while(0)
#define INTC_READ_IRQ_MASK0_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Irq_Mask0;} while(0)
#define INTC_READ_IRQ_MASK1_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Irq_Mask1;} while(0)
#define INTC_READ_IRQ_MASK2_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Irq_Mask2;} while(0)
#define INTC_READ_IRQ_MASK3_REG_1(x)           do {(x) = g_pKeIrqControl_1->u32_Irq_Mask3;} while(0)
#define INTC_WRITE_FIQ_MASK0_REG_1(x)          do {g_pKeIrqControl_1->u32_Fiq_Mask0 = (x);} while(0)
#define INTC_WRITE_FIQ_MASK1_REG_1(x)          do {g_pKeIrqControl_1->u32_Fiq_Mask1 = (x);} while(0)
#define INTC_WRITE_FIQ_MASK2_REG_1(x)          do {g_pKeIrqControl_1->u32_Fiq_Mask2 = (x);} while(0)
#define INTC_WRITE_FIQ_MASK3_REG_1(x)          do {g_pKeIrqControl_1->u32_Fiq_Mask3 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK0_REG_1(x)          do {g_pKeIrqControl_1->u32_Irq_Mask0 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK1_REG_1(x)          do {g_pKeIrqControl_1->u32_Irq_Mask1 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK2_REG_1(x)          do {g_pKeIrqControl_1->u32_Irq_Mask2 = (x);} while(0)
#define INTC_WRITE_IRQ_MASK3_REG_1(x)          do {g_pKeIrqControl_1->u32_Irq_Mask3 = (x);} while(0)

#define INTC_MASK_FIQ_MASK0_REG_1(mask)        do {g_pKeIrqControl_1->u32_Fiq_Mask0 |= (mask);} while(0)
#define INTC_MASK_FIQ_MASK1_REG_1(mask)        do {g_pKeIrqControl_1->u32_Fiq_Mask1 |= (mask);} while(0)
#define INTC_MASK_FIQ_MASK2_REG_1(mask)        do {g_pKeIrqControl_1->u32_Fiq_Mask2 |= (mask);} while(0)
#define INTC_MASK_FIQ_MASK3_REG_1(mask)        do {g_pKeIrqControl_1->u32_Fiq_Mask3 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK0_REG_1(mask)        do {g_pKeIrqControl_1->u32_Irq_Mask0 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK1_REG_1(mask)        do {g_pKeIrqControl_1->u32_Irq_Mask1 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK2_REG_1(mask)        do {g_pKeIrqControl_1->u32_Irq_Mask2 |= (mask);} while(0)
#define INTC_MASK_IRQ_MASK3_REG_1(mask)        do {g_pKeIrqControl_1->u32_Irq_Mask3 |= (mask);} while(0)
#define INTC_UNMASK_FIQ_MASK0_REG_1(mask)      do {g_pKeIrqControl_1->u32_Fiq_Mask0 &= ~(mask);} while(0)
#define INTC_UNMASK_FIQ_MASK1_REG_1(mask)      do {g_pKeIrqControl_1->u32_Fiq_Mask1 &= ~(mask);} while(0)
#define INTC_UNMASK_FIQ_MASK2_REG_1(mask)      do {g_pKeIrqControl_1->u32_Fiq_Mask2 &= ~(mask);} while(0)
#define INTC_UNMASK_FIQ_MASK3_REG_1(mask)      do {g_pKeIrqControl_1->u32_Fiq_Mask3 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK0_REG_1(mask)      do {g_pKeIrqControl_1->u32_Irq_Mask0 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK1_REG_1(mask)      do {g_pKeIrqControl_1->u32_Irq_Mask1 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK2_REG_1(mask)      do {g_pKeIrqControl_1->u32_Irq_Mask2 &= ~(mask);} while(0)
#define INTC_UNMASK_IRQ_MASK3_REG_1(mask)      do {g_pKeIrqControl_1->u32_Irq_Mask3 &= ~(mask);} while(0)

#define INTC_CLR_INT_FIQ0_REG_1(mask)          do {g_pKeIrqControl_1->u32_Fiq_Status0 |= mask;} while(0)
#define INTC_CLR_INT_FIQ1_REG_1(mask)          do {g_pKeIrqControl_1->u32_Fiq_Status1 |= mask;} while(0)
#define INTC_CLR_INT_FIQ2_REG_1(mask)          do {g_pKeIrqControl_1->u32_Fiq_Status2 |= mask;} while(0)
#define INTC_CLR_INT_FIQ3_REG_1(mask)          do {g_pKeIrqControl_1->u32_Fiq_Status3 |= mask;} while(0)

#define INTC_SET_FIQ_POLARITY0_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity0 |= (mask);} while(0)
#define INTC_SET_FIQ_POLARITY1_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity1 |= (mask);} while(0)
#define INTC_SET_FIQ_POLARITY2_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity2 |= (mask);} while(0)
#define INTC_SET_FIQ_POLARITY3_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity3 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY0_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity0 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY1_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity1 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY2_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity2 |= (mask);} while(0)
#define INTC_SET_IRQ_POLARITY3_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity3 |= (mask);} while(0)
#define INTC_CLR_FIQ_POLARITY0_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity0 &= ~(mask);} while(0)
#define INTC_CLR_FIQ_POLARITY1_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity1 &= ~(mask);} while(0)
#define INTC_CLR_FIQ_POLARITY2_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity2 &= ~(mask);} while(0)
#define INTC_CLR_FIQ_POLARITY3_REG_1(mask)     do {g_pKeIrqControl_1->u32_Fiq_Polarity3 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY0_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity0 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY1_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity1 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY2_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity2 &= ~(mask);} while(0)
#define INTC_CLR_IRQ_POLARITY3_REG_1(mask)     do {g_pKeIrqControl_1->u32_Irq_Polarity3 &= ~(mask);} while(0)



/*#define INTC_READ_MASK0_REG(x)           do {(x) = g_ptW5IrqControl->u32_Mask0;} while(0)
#define INTC_READ_MASK1_REG(x)           do {(x) = g_ptW5IrqControl->u32_Mask1;} while(0)
#define INTC_WRITE_MASK0_REG(x)          do {g_ptW5IrqControl->u32_Mask0 = (x);} while(0)
#define INTC_WRITE_MASK1_REG(x)          do {g_ptW5IrqControl->u32_Mask1 = (x);} while(0)
#define INTC_CLEAR_MASK0_REG(mask)       do {g_ptW5IrqControl->u32_Mask0 &= ~(mask);} while(0)
#define INTC_CLEAR_MASK1_REG(mask)       do {g_ptW5IrqControl->u32_Mask1 &= ~(mask);} while(0)
#define INTC_READ_PENDING0_REG(x)        do {(x) = g_ptW5IrqControl->u32_Pending0;} while(0)
#define INTC_READ_PENDING1_REG(x)        do {(x) = g_ptW5IrqControl->u32_Pending1;} while(0)
#define INTC_READ_RAWSTATUS0_REG(x)      do {(x) = g_ptW5IrqControl->u32_RawStatus0;} while(0)
#define INTC_READ_RAWSTATUS1_REG(x)      do {(x) = g_ptW5IrqControl->u32_RawStatus1;} while(0)
#define INTC_READ_STATUS0_REG(x)         do {(x) = g_ptW5IrqControl->u32_Status0;} while(0)
#define INTC_READ_STATUS1_REG(x)         do {(x) = g_ptW5IrqControl->u32_Status1;} while(0)
#define INTC_WRITE_CLEAR0_REG(x)         do {g_ptW5IrqControl->u32_Clear0 = (x);} while(0)
#define INTC_WRITE_CLEAR1_REG(x)         do {g_ptW5IrqControl->u32_Clear1 = (x);} while(0)
#define INTC_WRITE_ACK0_REG(x)           do {g_ptW5IrqControl->u32_Ack0 = (x);} while(0)
#define INTC_WRITE_ACK1_REG(x)           do {g_ptW5IrqControl->u32_Ack1 = (x);} while(0)
#define INTC_READ_SERVICE0_REG(x)        do {(x) = g_ptW5IrqControl->u32_Service0;} while(0)
#define INTC_READ_SERVICE1_REG(x)        do {(x) = g_ptW5IrqControl->u32_Service1;} while(0)
#define INTC_CLEAR_WAKEUPMASK0_REG(mask) do {g_ptW5IrqControl->u32_WakeUpMask0 &= ~(mask);} while(0)
#define INTC_CLEAR_WAKEUPMASK1_REG(mask) do {g_ptW5IrqControl->u32_WakeUpMask1 &= ~(mask);} while(0)
*/
/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** HalIntcInit
* @brief        Initialize the controller
*
* @param[in]
*
* @retval
*
*/
extern void HalIntcInit(void);

/** HalIntcSetPriorityReg
* @brief        Setup priority register on INTC
*
* @param[in]    ePriority           Priority.
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
extern void HalIntcSetPriorityReg(IntcPriority_e ePriority, u32 nIntcNumber);

/** HalIntcSetMappingReg , no this register on iNfinity
* @brief        Setup mapping register on INTC
*
* @param[in]    eMap                Mapping.
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
//extern void HalIntcSetMappingReg(IntcMap_e eMap, u32 nIntcNumber);

/** HalIntcSetSensitivityReg , no this register on iNfinity
* @brief        Setup sensitivity register on INTC
*
* @param[in]    eSensitivity        Sensitivity.
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
//extern void HalIntcSetSensitivityReg(IntcSensitivity_e eSensitivity, u32 nIntcNumber);

/** HalIntcSetPolarityReg
* @brief        Setup polarity register on INTC
*
* @param[in]    ePolarity           Polarity.
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
extern void HalIntcSetPolarityReg(IntcPolarity_e ePolarity, u32 nIntcNumber);

/** HalIntcSetReentranceReg , no this register on iNfinity
* @brief        Setup reentrance register on INTC
*
* @param[in]    bReentrance         TRUE to allow reentrance.
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
//extern void HalIntcSetReentranceReg(bool bReentrance, u32 nIntcNumber);

/** HalIntcSetWakeUpReg , no this register on iNfinity
* @brief        Setup wakeup register on INTC
*
* @param[in]    bWakeUp             TRUE to allow wakeup CPU in sleep.
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
//extern void HalIntcSetWakeUpReg(bool bWakeUp, u32 nIntcNumber);

/** HalIntcAck , no this register on iNfinity
* @brief        Ack an interrupt on INTC
*
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
//extern void HalIntcAck(u32 nIntcNumber);

/** HalIntcClear
* @brief        Clear an interrupt on INTC
*
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
extern void HalIntcClear(u32 nIntcNumber);

/** HalIntcMask
* @brief        Mask an interrupt on INTC
*
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
extern void HalIntcMask(u32 nIntcNumber);

/** HalIntcUnMask
* @brief        Unmask an interrupt on INTC
*
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval
*
*/
extern void HalIntcUnMask(u32 nIntcNumber);

/** HalIntcIsMask
* @brief        Check an interrupt is masked on INTC or not
*
* @param[in]    nIntcNumber         Interrupt number.
*
* @retval       bool                TRUE: interrup not masked, FALSE: interrup masked.
*
*/
extern bool HalIntcIsMask(u32 nIntcNumber);

/** HalIntcAutoAckEnable , no this register on iNfinity
* @brief        Enable/Disable auto-ack function on INTC
*
* @param[in]    bEnable             TRUE to enable auto-ack function.
*
* @retval
*
*/
//extern void HalIntcAutoAckEnable(bool bEnable);

#endif //__HAL_INT_IRQ_H__

