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
* @file    UrlSrvCommon.h
* @brief   define the common util for server & client
*          
*/

#ifndef __MMI_URL_SRV_COMMON_H__
#define __MMI_URL_SRV_COMMON_H__

#include "mmi_UrlSrvConfig.h"
#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/


/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvTaskSend
* @brief      Function to send message
*
* @param[in]  pvMsg            Message
* @param[in]  uSrcMbxId        Source MailBox
* @param[in]  uDestMbxId       Destination MailBox
*
* @retval     None
*
*/
void UrlSrvTaskSend(void *pvMsg, u32 uSrcMbxId, u32 uDestMbxId);

#endif/* __MMI_URL_SRV_COMMON_H__ */
