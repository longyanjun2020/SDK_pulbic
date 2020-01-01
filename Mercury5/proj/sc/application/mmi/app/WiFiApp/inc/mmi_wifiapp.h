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
* @file mmi_btapp.h
*
* Class Id: CLSID_WIFIAPP
*
* @version $Id$
*/
#ifndef __MMI_WIFIAPP_H__
#define __MMI_WIFIAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_filemgr.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_UrlSrvClientHelper.h"
#include "mmi_launcher_bt.h"
#include "mmi_launcher_sendvia.h"
#include "mmi_wlansrv.h"


/*=============================================================*/
// Data type definition
/*=============================================================*/


/* Launch Mode */
typedef enum
{
    WIFIAPP_LAUNCHED_BY_UNKNOWN=0,
    WIFIAPP_LAUNCHED_BY_SETTING,
    WIFIAPP_LAUNCHED_BY_LOWSIGNAL
} WiFiAppLaunchedMode_e;


/* Unused */
#if 0
typedef enum
{
    WiFiApp_NONE,
    WiFiApp_SEARCH_DEVICES,
    WiFiApp_PAIRED_DEVICES_LIST,
    WiFiApp_SEND_FILE
} MMI_WiFiApp_ENTRY_MODE_e;
#endif


/*=============================================================*/
// Global function definition
/*=============================================================*/


/* WIFI APP Basic */
void        WiFiPreNew(void);
MAE_Ret     WiFiAppNew(MAE_ClsId id, void **ppObj);


/*=============================================================*/
// Local function definition
/*=============================================================*/


#endif /* __MMI_WiFiAPP_H__ */
