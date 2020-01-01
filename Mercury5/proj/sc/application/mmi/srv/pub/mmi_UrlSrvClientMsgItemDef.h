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
* @file    UrlSrvClientMsItemDef.h
* @brief   define the message items
*          
*/

#ifndef __MMI_URL_SRV_CLIENT_MSG_ITEM_DEF_H__
#define __MMI_URL_SRV_CLIENT_MSG_ITEM_DEF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/


/// Message To Url Service Client
#define URL_SRV_CLIENT_MSG_ITEM_COLS	\
	URL_SRV_MSG_ITEM(URL_SRV_CLIENT_MSG_START, NULL)	\
	URL_SRV_MSG_ITEM(URL_SRV_CLIENT_MSG_HANDLE_URL_REQ, UrlSrvClientHandleUrlReq)	\
	URL_SRV_MSG_ITEM(URL_SRV_CLIENT_MSG_HANDLE_URL_LAUNCH_RSP_REQ, UrlSrvClientHandleUrlLaunchRsp)	\
    URL_SRV_MSG_ITEM(URL_SRV_CLIENT_MSG_HANDLE_URL_DATA_RSP_REQ, UrlSrvClientHandleUrlDataRsp)	\
	URL_SRV_MSG_ITEM(URL_SRV_CLIENT_MSG_END, NULL)


/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __MMI_URL_SRV_CLIENT_MSG_ITEM_DEF_H__ */
