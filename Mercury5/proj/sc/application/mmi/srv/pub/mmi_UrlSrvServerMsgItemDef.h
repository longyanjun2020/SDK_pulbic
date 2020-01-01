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
* @file    UrlSrvServerMsgItemDef.h
* @brief   define the message item collections
*          
*/

#ifndef __MMI_URL_SRV_SERVER_MSG_ITEM_DEF_H__
#define __MMI_URL_SRV_SERVER_MSG_ITEM_DEF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/


/// Message To Url Service Task
#define URL_SRV_SERVER_MSG_ITEM_COLS	\
	URL_SRV_MSG_ITEM(URL_SRV_SERVER_MSG_START, NULL)	\
	URL_SRV_MSG_ITEM(URL_SRV_SERVER_MSG_REG_URL_HANDLER_REQ, UrlSrvServerRegUrl)	\
	URL_SRV_MSG_ITEM(URL_SRV_SERVER_MSG_OVERRIDE_URL_HANDLER_REQ, UrlSrvServerOverrideUrl)	\
	URL_SRV_MSG_ITEM(URL_SRV_SERVER_MSG_DISPATCH_URL_REQ, UrlSrvServerDispatchUrl)	\
	URL_SRV_MSG_ITEM(URL_SRV_SERVER_MSG_END, NULL)


/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __MMI_URL_SRV_SERVER_MSG_ITEM_DEF_H__ */
