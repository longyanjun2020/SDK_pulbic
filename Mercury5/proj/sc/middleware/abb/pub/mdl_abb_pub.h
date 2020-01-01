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
* @file    mdl_abb_pub.h
* @version
* @brief   MDL header file of ABB task
*
*/
#ifndef __MDL_ABB_PUB_H__
#define __MDL_ABB_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "Drv_abb_pub.h"
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
 *  @brief The structure defines touch panel coordination.
 */

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** MdlAbbServiceSubscribe
* @brief        main loop of ABB task
*
* @param[in]    eServiceType: enum of ABB service type
* @param[in]    mailbox: subscriber's mailbox
* @retval       None
*
*/
s32 MdlAbbServiceSubscribe(DrvServiceType_e eServiceType, DrvAbbServiceParam_t *ptAbbServiceParam);

#endif //__MDL_ABB_PUB_H__

