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
* @file    sys_MsWrapper_cus_os_int_pub.h
* @version
* @brief   System wrapper header file for interrupts
*
*/

#ifndef __SYS_MSWRAPPER_CUS_OS_INT_PUB_H__
#define __SYS_MSWRAPPER_CUS_OS_INT_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef u32 MsIntMask_e;

/*=============================================================*/
// Macro definition
/*=============================================================*/



/**
 * \fn MsDisableInterrupt()
 * \brief The MsDisableInterrupt primitive disable the interrupt and return the mask of disabled interrupts. The mask would be used in enable interrupt. This interface operates the CPU coprocessor IRQ bit and is defined as the kernel mode operation.
 *
 * e.g.
 * \code
 *      MsIntMask_e Mask;
 *
 *      Mask = MsDisableInterrupt();   // disable interrupt
 *
 *      / * The period while the interrupt is disabled. * /
 *
 *      MsEnableInterrupt(Mask);       // enable interrupt
 * \endcode
 * \return The mask of disabled interrupts
 */
#define MsDisableInterrupt() 0

/**
 * \fn MsEnableInterrupt(MsIntMask_e eMask)
 * \brief The MsEnableInterrupt primitive enables the interrupt from the mask returned from MsDisableInterrupt primitive. This interface operates the CPU coprocessor IRQ bit and is defined as the kernel mode operation
 * \param[in] eMask The mask of interrupt to enable
 * \return None
 */
#define MsEnableInterrupt(x)

/**
 * \fn MsDisableInterruptUser()
 * \brief The MsDisableInterruptUser primitive disable the interrupt except FINT and return the mask of disabled interrupts. The mask would be used in enable interrupt. This interface operates at the INTC level and is regarded as user mode operation
 * \return The mask of disabled interrupts
 */
#define MsDisableInterruptUser() 0

/**
 * \fn MsEnableInterruptUser(MsIntMask_e eMask)
 * \brief The MsEnableInterruptUser primitive enable the interrupt from the mask returned from MsDisableInterruptUser primitive. This interface operates at the INTC level and is regarded as user mode operation
 * \param[in] eMask The mask of interrupt to enable
 * \return None
 */
#define MsEnableInterruptUser(x)

/** @}*/
#endif // __SYS_MSWRAPPER_CUS_OS_INT_PUB_H__
