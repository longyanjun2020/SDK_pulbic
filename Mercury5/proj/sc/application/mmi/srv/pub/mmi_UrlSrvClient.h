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
* @file    UrlSrvClient.h
* @brief   Define the APIs for Url Service Client 
*          
*          
*/

#ifndef __MMI_URL_SRV_CLIENT_H__
#define __MMI_URL_SRV_CLIENT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
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

/** UrlSrvClientInit
* @brief      init url service info for client
*
* @param[in]  eTaskId          TaskId  for client
* @param[in]  uMailBox         Mailbox for client
*
* @retval     None
*
*/
void UrlSrvClientInit(Srv_TaskId_e eTaskId, u32 uMailBox);

/** UrlSrvClientUnInit
* @brief      un-init url service info for client
*
* @param      None
*
* @retval     None
*
*/
void UrlSrvClientUnInit(void);

/** UrlSrvClientMsgParser
* @brief      the parser for client task
*
* @param[in]  pvMsg            incoming message
*
* @retval     None
*
*/
MAE_Ret UrlSrvClientMsgParser(void *pvMsg);


#endif/* __MMI_URL_SRV_CLIENT_H__ */

