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
* @file    sys_MsWrapper_cus_os_int_ctrl.h
* @version
* @brief   System wrapper header file for interrupts
*
*/

#ifndef __SYS_MSWRAPPER_CUS_OS_INT_CTRL_H__
#define __SYS_MSWRAPPER_CUS_OS_INT_CTRL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_MsWrapper_cus_os_type.h"
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "drv_int_ctrl_pub_api.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef IntInitParam_u MsIntInitParam_u;
typedef IntNumber_e	MsIntNumber_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** \addtogroup IntMan
 *  @{
 */

/**
 *
 * \brief Initialize the interrupt controller. The interrupts are initialized to be automatically
 *  acknowledged. All pending acknowledged interrupts before this call are cleared
 */
// extern void MsInitInterruptController(void);

/**
  * \fn s32 MsInitInterrupt(MsIntInitParam_u *puParam, MsIntNumber_e eIntNum)
  * \brief This function initializes the specific interrupt enum number from the input parameter block
  * \param[in] *puParam Pointer of interrupt parameter block
  * \param[in] eIntNum ISystem interrupt enum
  * \return Retrun TRUE if success, otherwise FALSE.
  */
extern s32 MsInitInterrupt(MsIntInitParam_u *puParam, MsIntNumber_e eIntNum);

/**
  * \fn void MsAckInterrupt(MsIntNumber_e eIntNum);
  * \brief This function Acks the specifc interrupt line
  * \param[in] eIntNum ISystem interrupt enum
  */
extern void MsAckInterrupt(MsIntNumber_e eIntNum);

/**
  * \fn void MsClearInterrupt(MsIntNumber_e eIntNum)
  * \brief This function clears the specifc interrupt line
  * \param[in] eIntNum ISystem interrupt enum
  */
extern void MsClearInterrupt(MsIntNumber_e eIntNum);

/**
  * \fn void MsMaskInterrupt(MsIntNumber_e eIntNum)
  * \brief This function masks the specifc interrupt line
  * \param[in] eIntNum ISystem interrupt enum
  */
extern void MsMaskInterrupt(MsIntNumber_e eIntNum);

/**
  * \fn void MsUnmaskInterrupt(MsIntNumber_e eIntNum)
  * \brief This function unmasks the specifc interrupt line
  * \param[in] eIntNum ISystem interrupt enum
  */
extern void MsUnmaskInterrupt(MsIntNumber_e eIntNum);

/**
  * \fn bool MsIsMaskInterrupt(MsIntNumber_e eIntNum);
  * \brief check an interrupt mask
  * \param[in] eIntNum ISystem interrupt enum
  * \retval    bool     TRUE: interrupt not masked, FALSE: interrupt masked.
  */
extern bool MsIsMaskInterrupt(MsIntNumber_e eIntNum);

/**
  * \fn bool MsIntGetRawStatus(MsIntNumber_e eIntNum, bool *pbRawStatus)
  * \brief Get interrupt raw status
  * \param[in] eIntNum ISystem interrupt enum
  * \param[out] pbRawStatus raw status of the interrupt
  * \retval    bool     TRUE: ok , FALSE: fail
  */
//extern bool MsIntGetRawStatus(MsIntNumber_e eIntNum, bool *pbRawStatus);

/** @}*/
#endif // __SYS_MSWRAPPER_CUS_OS_INT_CTRL_H__
