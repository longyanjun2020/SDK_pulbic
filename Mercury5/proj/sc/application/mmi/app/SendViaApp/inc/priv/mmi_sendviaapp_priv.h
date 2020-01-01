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
 * @file    mmi_sendviaapp_priv.h
 * @version
 * @brief   send by app
 *
 */

#ifndef __MMI_SENDVIAAPP_PRIV_H__
#define __MMI_SENDVIAAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_sendviaapp.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_vtm.h"
#include "mmi_common_sms.h"
#include "mmi_common_calendar.h"
#include "mmi_common_mimetype.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_email.h"
#include "mmi_launcher_sendvia.h"
#include "mmi_srv_accessory.h"
#include "mmi_srv_filemgr.h"
#ifdef __BLUETOOTH_OBEX_MMI__
#include "mmi_btapp.h"
#endif
#include "mmi_phbsrv_def.h"
#include "mmi_sendviaapp_id.h"
#include "sendviaapp_resource.h"

#include "mmi_UrlSrvUtilUrl.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/* The type of message to be displayed on dialog. */
typedef enum
{
    SENDVIA_MSG_PARAMETER_IS_NULL,
    SENDVIA_MSG_LAUNCH_AP_FAIL,
    SENDVIA_MSG_EXTCARD_ABSENT,
	SENDVIA_MSG_STORGE_FULL
#ifdef __SMART_MESSAGING_MMI_SUPPORT__
	,SENDVIA_MSG_PARAMETER_TOO_LARGE
#endif
    ,SENDVIA_MSG_MAIL_OVERCAPACITY
} SENDVIAPP_MSG_e;

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
    MenuItemId_e eSendVia;
    SENDVIAAPP_SENDDATA_t* pSendData;
    SENDVIAPP_MSG_e eMsgID;
    bool bDestoryMarkList;
	MAE_Ret nLaunchApCbRspCode;
#ifdef __SRV_SYS_API_H__
    CmnAppLaunchRspCbInfo_t callerRspCBInfo; //The callback function to notify the caller AP
#endif/* __SRV_SYS_API_H__ */
#ifdef __SMART_MESSAGING_MMI_SUPPORT__
	MmiPhbContactContent_t* pPhbContent;
#endif
} SendviaAppData_t;

typedef struct
{
    MAE_WChar * strMenuItem;
} SendviaMenuWndData;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret SendviaDestructor(IApplet *pApplet , u32 nEvt , u32 nParam1 , u32 nParam2);
boolean SendviaStartCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1 , u32 nParam2);
boolean SendviaEmbededApCloseCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret SendviaWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SendviaDialogTimeOut(void *pApplet, MAEEvent_t nEvt, u32 nParam1 , u32 nParam2);
void SendviaSoftKeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SendViaExportContactToFileAsyncCb(void *UserData, u32 pReq, boolean bSuccess);
static boolean _SendviaAppLaunch(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchRspCbInfo_t *psRspCbInfo);
static boolean _SendviaAppUrlHandlerSendByContent(UrlSrvUrlHdl_t pUrl, void *pvUserData, void **ppvLaunchObj, CmnAppLaunchRspCbInfo_t *psResponseInfo);
static boolean _SendviaAppUrlHandlerSendByUrl(UrlSrvUrlHdl_t pUrl, void *pvUserData, void **ppvLaunchObj, CmnAppLaunchRspCbInfo_t *psResponseInfo);
static boolean _SendviaAppUrlHandlerSendById(UrlSrvUrlHdl_t pUrl, void *pvUserData, void **ppvLaunchObj, CmnAppLaunchRspCbInfo_t *psResponseInfo);
/*-------------------------------------------------------------------------*/
#endif /* __MMI_SENDVIAAPP_PRIV_H__ */

