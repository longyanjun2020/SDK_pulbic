////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
* @file    mdl_service.h
* @version
* @brief   System wrapper header file for interrupts
*
*/

#ifndef __MDL_SERVICE_H__
#define __MDL_SERVICE_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_MsWrapper_cus_os_type.h"
//#include "kernel.h"
#include "sys_rtk_ho.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 *  @brief The enumeration defines the return code of the cus core srv middle interface
 */
typedef enum
{
    MDL_Cus_Core_Srv_OK,                 /**< Function complete successfully */
    MDL_Cus_Core_Srv_FAIL,               /**< Function common fail */
} MdlCusCoreSrvErrCode_e;

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
extern MdlCusCoreSrvErrCode_e MdlCusCoreSrvEnterSleepMode(void);

/**
  *
  * \brief Initialize a interrupt and mask it
  * \param[in] psParam Parameters to initialize the interrupt
  * \param[in] u8IntNum Interrupt number
  * \return 0 if the result is OK. -1 otherwise.
  */
extern MdlCusCoreSrvErrCode_e MdlCusCoreSrvLeaveSleepMode(void);


#endif //__MDL_SERVICE_H__

