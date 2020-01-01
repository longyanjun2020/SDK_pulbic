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
* @file    UrlSrvServerMsgHandler
* @brief   define the message handler for 
*          Server
*          
*/

#ifndef __MMI_URL_SRV_SERVER_MSG_HANDLER_H__
#define __MMI_URL_SRV_SERVER_MSG_HANDLER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvCommonMsgBodyDef.h"
#include "mmi_UrlSrvServerMsgIdDef.h"
#include "mmi_UrlSrvServerMgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void (*UrlSrvServerHandler)(UrlSrvServerMsgId_e eMsgId, vm_msg_t *psVmMsg, UrlSrvServerMgrHdl_t pSrvMgr);
/// SRV_Task_Srv_MsgHandler

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvServerRegUrl
* @brief      Handler for URL_SRV_SERVER_MSG_REG_URL_HANDLER_REQ
*
* @param[in]  eMsgId      Message id
* @param[in]  psVmMsg     Message
* @param[in]  pSrvMgr     Handle to server manager
*
* @retval     None
*
*/
void UrlSrvServerRegUrl(UrlSrvServerMsgId_e eMsgId, vm_msg_t *psVmMsg, UrlSrvServerMgrHdl_t pSrvMgr);

/** UrlSrvServerOverrideUrl
* @brief      Handler for URL_SRV_SERVER_MSG_OVERRIDE_URL_HANDLER_REQ
*
* @param[in]  eMsgId      Message id
* @param[in]  psVmMsg     Message
* @param[in]  pSrvMgr     Handle to server manager
*
* @retval     None
*
*/
void UrlSrvServerOverrideUrl(UrlSrvServerMsgId_e eMsgId, vm_msg_t *psVmMsg, UrlSrvServerMgrHdl_t pSrvMgr);

/** UrlSrvServerDispatchUrl
* @brief      Handler for URL_SRV_SERVER_MSG_DISPATCH_URL_REQ
*
* @param[in]  eMsgId      Message id
* @param[in]  psVmMsg     Message
* @param[in]  pSrvMgr     Handle to server manager
*
* @retval     None
*
*/
__SLDPM_FREE__ void UrlSrvServerDispatchUrl(UrlSrvServerMsgId_e eMsgId, vm_msg_t *psVmMsg, UrlSrvServerMgrHdl_t pSrvMgr);

#endif/* __MMI_URL_SRV_SERVER_MSG_HANDLER_H__ */
