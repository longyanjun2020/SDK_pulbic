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
* @file    UrlSrvClientStaticUrlHandler.h
* @brief   define static url handlers table
*
*
*/


#ifndef __MMI_URL_SRV_CLIENT_STATIC_URL_HANDLER_H__
#define __MMI_URL_SRV_CLIENT_STATIC_URL_HANDLER_H__

#include "mmi_UrlSrvClientHelper.h"
#include "mmi_srv_client_commondefine.h"
#include "mmi_srv_client_platformdefines.h"

boolean UrlSrvMAELaunch
(
  UrlSrvUrlHdl_t pUrl,
  void *pvUserData,
  void **ppvLaunchObj,
  UrlSrvUrlRspInfo_t *psRspCbInfo
);


#endif/* __MMI_URL_SRV_CLIENT_STATIC_URL_HANDLER_H__ */

