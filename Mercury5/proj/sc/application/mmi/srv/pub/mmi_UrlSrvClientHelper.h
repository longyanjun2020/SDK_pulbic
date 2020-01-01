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
* @file    UrlSrvClientHelper.h
* @brief   Define the Helper Function for Service Client
*          
*          
*/

#ifndef __MMI_URL_SRV_CLIENT_HELPER_H__
#define __MMI_URL_SRV_CLIENT_HELPER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvUtilUrl.h"
#include "mmi_UrlSrvCommonSchemeTbl.h"

#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void (*UrlSrvRspDataFreeCb)(void *pvRspData);
typedef void (*UrlSrvUrlRspCb)(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, UrlSrvRspDataFreeCb pfnRspDataFreeCb);
typedef void (*UrlSrvUrlListenerCb)(void *pvUserData, MAE_Ret nRspCode);
typedef void (*UrlSrvRegHdlrRspCb)(void *pvUserData, MAE_Ret nRspCode);

typedef enum
{
	SRV_URLHANDLER_TYPE_HOOK = 0,
	SRV_URLHANDLER_TYPE_ALL,
	SRV_URLHANDLER_TYPE_NUM,
	SRV_URLHANDLER_TYPE_INVALID,
}UrlSrvUrlHandlerType_e;

typedef struct
{
	void *pvUserData;
    UrlSrvUrlListenerCb pfnLaunchListenerCb;
	UrlSrvUrlRspCb pfnCbUrlDataRspCb;
}UrlSrvUrlRspInfo_t;

typedef boolean (*UrlSrvUrlHandler)(UrlSrvUrlHdl_t pUrl, void *pvUserData, void **ppvLaunchObj, UrlSrvUrlRspInfo_t *psRspCbInfo);

typedef struct
{
	UrlSrvUrlHandlerType_e eHandlerType;
	UrlSrvUrlHandler pfnUrlHandler;
	void *pvUserData;
}UrlSrvUrlHandlerInfo_t;


typedef struct
{
    void *pvUserData;
    UrlSrvRegHdlrRspCb pfnRegHdlrRspCb;
}UrlSrvRegHdlrRspInfo_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvClientAddUrlHandler
* @brief      Register Url Handler For Specified Scheme + Action
*
* @param[in]  eScheme            Scheme for url handler
* @param[in]  eAction            Action for url handler
* @param[in]  psUrlHdlrInfo      Url handler information you want to add  
* @param[in]  psRegHdlrRspCbInfo Response callback
*
* @retval     None
*
*/
void UrlSrvClientAddUrlHandler(UrlSrvUrlScheme_e eScheme, UrlSrvUrlHandlerInfo_t *psUrlHdlrInfo, UrlSrvRegHdlrRspInfo_t *psRegHdlrRspCbInfo);

/** UrlSrvClientRemoveUrlHandler
* @brief      Register Url Handler For Specified Scheme + Action
*
* @param[in]  eScheme              Scheme for url handler
* @param[in]  eAction              Action for url handler
* @param[in]  psOldUrlHdlrInfo     Url handler information you want to remove  
* @param[in]  psRegHdlrRspCbInfo   Response callback
*
* @retval     None
*
*/
void UrlSrvClientRemoveUrlHandler(UrlSrvUrlScheme_e eScheme, UrlSrvUrlHandlerInfo_t *psOldUrlHdlrInfo, UrlSrvRegHdlrRspInfo_t *psRegHdlrRspCbInfo);

/** UrlSrvClientRemoveUrlHandler
* @brief      Register Url Handler For Specified Scheme + Action
*
* @param[in]  eScheme               Scheme for url handler
* @param[in]  eAction               Action for url handler
* @param[in]  psOldUrlHdlrInfo      Url handler information you want to remove  
* @param[in]  psNewUrlHdlrInfo      Url handler information you want to add  
* @param[in]  psRegHdlrRspCbInfo    Response callback
*
* @retval     None
*
*/
void UrlSrvClientOverrideUrlHandler(UrlSrvUrlScheme_e eScheme, UrlSrvUrlHandlerInfo_t *psOldUrlHdlrInfo, UrlSrvUrlHandlerInfo_t *psNewUrlHdlrInfo, UrlSrvRegHdlrRspInfo_t *psRegHdlrRspCbInfo);

/** UrlSrvClientDispatchUrlObj
* @brief      Dispatch request url object
*
* @param[in]  pUrl            request url object
* @param[in]  psRspCbInfo     Response callback
*
* @retval     None
*
*/
void UrlSrvClientDispatchUrlObj(UrlSrvUrlHdl_t pUrl, UrlSrvUrlRspInfo_t *psRspCbInfo);

/** UrlSrvCmnUrlRspInfo
* @brief      Common Url Response Callback
*
* @param[in]  pvUserData        user data
* @param[in]  nRspCode          result code
* @param[in]  pvRspData         response data
* @param[in]  pfnRspDataFreeCb  free function for response data
*
* @retval     None
*
*/
void UrlSrvCmnRegUrlRspCb(void *pvUserData, MAE_Ret nRspCode);

#endif/* __MMI_URL_SRV_CLIENT_HELPER_H__ */

