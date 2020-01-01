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
* @file    UrlSrvClientMsgIdDef.h
* @brief   define the message id
*          
*/

#ifndef __MMI_URL_SRV_SERVER_MSG_ID_DEF_H__
#define __MMI_URL_SRV_SERVER_MSG_ID_DEF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvServerMsgItemDef.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

#ifdef URL_SRV_MSG_ITEM
#undef URL_SRV_MSG_ITEM
#endif /* URL_SRV_MSG_ITEM */

#define URL_SRV_MSG_ITEM(MSG_ID, MSG_HANDLER) MSG_ID,

typedef enum
{
	URL_SRV_SERVER_MSG_ITEM_COLS
}UrlSrvServerMsgId_e;

/*

/// The preprocessor result
/// is as the following

typedef enum
{
    URL_SRV_SERVER_MSG_START,
    URL_SRV_SERVER_MSG_REG_URL_HANDLER_REQ,
	URL_SRV_SERVER_MSG_OVERRIDE_URL_HANDLER_REQ,
    URL_SRV_SERVER_MSG_DISPATCH_URL_REQ,
    URL_SRV_SERVER_MSG_END,
}UrlSrvServerMsgId_e;

*/


#undef URL_SRV_MSG_ITEM

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __MMI_URL_SRV_SERVER_MSG_ID_DEF_H__ */
