////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file    mmi_ussdapp_priv.h
 * @version
 * @brief   ussd app
 */

#ifndef __MMI_USSDAPP_PRIV_H__
#define __MMI_USSDAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_ussdapp.h"

#include "mmi_srv_header.h"
#include "mmi_callsettingapp_util.h"
#include "mmi_wdg_headers.h"
#include "mmi_ussdapp_id.h"
#include "ussdapp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef union
{
    SSSRV_USSDCnf_t USSDCnf;
    SSSRV_USSDInd_t USSDInd;
    SSSRV_USSDNot_t USSDNot;
} UssdUnionData_t;

typedef struct
{
    IWidget *pUssdScrollbarWdg;
    IWidget *pUssdInputWdg;
}UssdDisplayWdgList_t;

typedef struct
{
    InputVtmWdgList_t tWdgList;
} ReplyWndData_t;

typedef struct
{
    MAE_WChar* pTitleStr;
    MAE_WChar* pResultStr;
} NewResultDisplayData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    boolean bIsWaitingCnf;   //for keep current request status
    boolean bIsAllowReply;   //for reply state
    boolean bIsInit;
    boolean bIsProcessScreen;
    boolean bIsSSProcessScreen;
    SSSRV_REQUEST_TYPE_e eSSReqType;      //keep SS request type
    MMI_SSSRV_USSD_Action_Type_e eCurrentActionType;
    UssdUnionData_t tUSSDReceivedData;
    SSSRV_unReqMsg_t *pSSReqData;     //keep SS request data
    u8 *pUSSDReqDataStr;
    u8 nUSSDReqDSC; //Data coding scheme
    u8 *pSSReqDataStr;  //keep SS related request string
    u8 nCurrDualID;
    UssdDisplayWdgList_t tWdgList;
    SSSRV_CreateUSSDAppReq_t tEventData; //Keep event data from APM event.
    boolean bIsSuspendByIntrFailed; // is suspend by interrupt failed
} UssdAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret UssdConstructCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UssdStartCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UssdStopCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UssdDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UssdKeyPressCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UssdResumeCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UssdSuspendCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void UssdUSSDIndCb(void *pApplet,SSSRV_USSDInd_t *pUSSDInd);
void UssdUSSDErrCb(void *pApplet,SSSRV_USSDErr_t *pUSSDErr);
void UssdUSSDCnfCb(void *pApplet, SSSRV_USSDCnf_t *pUSSD);
void UssdCFXCnfCb(void *pApplet, SSSRV_CallDivertCnf_t *pCallDivert);
void UssdCBXCnfCb(void *pApplet, SSSRV_CallBarringCnf_t *pCallBarring);
void UssdCWXCnfCb(void *pApplet, SSSRV_CallWaitingCnf_t *pCallWaiting);
void UssdPWDCnfCb(void *pApplet, MMI_SSSRV_SS_Result_e eRslt);
void UssdCLXCnfCb(void *pApplet, SSSRV_ClxCnf_t *pLineIdentity);
MAE_Ret UssdWndDualSimHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret UssdWndDisplayUssdHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret UssdWndReplyHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret UssdWndNewResultHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void UssdFreeUssdAppReq(IBase *pIssuer, u32 nParam);

#endif /* __MMI_USSDAPP_PRIV_H__ */
