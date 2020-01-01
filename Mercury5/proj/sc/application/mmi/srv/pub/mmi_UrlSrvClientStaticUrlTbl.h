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

#ifndef __MMI_URL_SRV_CLIENT_STATIC_URL_TBL_H__
#define __MMI_URL_SRV_CLIENT_STATIC_URL_TBL_H__

// #define URL_SRV_URL_HANDLER_COLS	\
// 	URL_SRV_HANDLER_ITEM(URL_SRV_URL_SCHEME_MAE_TASK, URL_SRV_URL_HOST_CLOSE_CUR_EMBEDDED_APP,SRV_URLHANDLER_TYPE_ALL, UrlSrvMAECloseCurEmbeddedAppHandler, NULL)	

#define URL_SRV_STATIC_HANDLER_TASK_INFO_COLS	\
	DEFINE_URL_SRV_STATIC_HANDLER_TASK_INFO(CUS_MBX_MMI, URL_SRV_URL_SCHEME_MAE_TASK, SRV_URLHANDLER_TYPE_ALL, UrlSrvMAELaunch, NULL)

#endif/* __MMI_URL_SRV_CLIENT_STATIC_URL_TBL_H__ */
