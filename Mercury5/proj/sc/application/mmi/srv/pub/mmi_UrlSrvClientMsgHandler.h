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
* @file    UrlSrvClientMsgHandler.h
* @brief   Define the Msg Handler For Url Service Client 
*          
*          
*/

#ifndef __MMI_URL_SRV_CLIENT_MSG_HANDLER_H__
#define __MMI_URL_SRV_CLIENT_MSG_HANDLER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvCommonMsgBodyDef.h"
#include "mmi_UrlSrvClientMsgIdDef.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/// the proto-type for Ap task's message handler
typedef void (*UrlSrvClientMsgHandler)(UrlSrvClientMsgId_e eMsgId, vm_msg_t *psVmMsg);

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvClientHandleUrlReq
* @brief      Handler for URL_SRV_CLIENT_MSG_HANDLE_URL_REQ
*
* @param[in]  eMsgId      Message id
* @param[in]  psVmMsg     Message
*
* @retval     Mailbox for this task
*
*/
__SLDPM_FREE__ void UrlSrvClientHandleUrlReq(UrlSrvClientMsgId_e eMsgId, vm_msg_t *psVmMsg);

/** UrlSrvClientHandleUrlRsp
* @brief      Handler for URL_SRV_CLIENT_MSG_HANDLE_URL_LAUNCH_RSP_REQ
*
* @param[in]  eMsgId      Message id
* @param[in]  psVmMsg     Message
*
* @retval     Mailbox for this task
*
*/
void UrlSrvClientHandleUrlLaunchRsp(UrlSrvClientMsgId_e eMsgId, vm_msg_t *psVmMsg);



/** UrlSrvClientHandleUrDatalRsp
* @brief      Handler for URL_SRV_CLIENT_MSG_HANDLE_URL_DATA_RSP_REQ
*
* @param[in]  eMsgId      Message id
* @param[in]  psVmMsg     Message
*
* @retval     Mailbox for this task
*
*/
void  UrlSrvClientHandleUrlDataRsp(UrlSrvClientMsgId_e eMsgId, vm_msg_t *psVmMsg);

#endif/* __MMI_URL_SRV_CLIENT_MSG_HANDLER_H__ */
