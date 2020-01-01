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
* @file mmi_btnotifyapp_priv.h
*
* Class Id: CLSID_BTNOTIFYAPP
*
* @version $Id: mmi_btnotifyapp_priv.h 30527 2009-05-12 03:40:04Z mark.yang $
*/
#ifndef __MMI_BTNOTIFYAPP_PRIV_H__
#define __MMI_BTNOTIFYAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_btnotifyapp.h"
#include "mmi_baseapplet.h"
#include "mmi_common_dialog_id.h"
#include "mmi_btnotifyapp_rs.h"

#ifdef __BLUETOOTH_MMI__
/*=============================================================*/
// Macro definition
/*=============================================================*/
#define BTNOTIFYAPP_RESULT_TIMER COMMON_DIALOG_AUTOCLOSE_TIME
#define BTNOTIFYAPP_DISPLAY_STRING_BUG 50

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    BTNOTIFYAPP_MODE_ENTERPINCODE,
    BTNOTIFYAPP_MODE_PAIRING,
    BTNOTIFYAPP_MODE_PAIRINGRESULT,
    BTNOTIFYAPP_MODE_CONNECTNOTICE,
    BTNOTIFYAPP_MODE_ACCEPTRECVFILE,
    BTNOTIFYAPP_MODE_ACCEPTRECVFILE_FINISH,
    BTNOTIFYAPP_MODE_ACCEPTIMPORTFILE
} BtNotifyAppMode_e;

typedef struct
{
    APPLET_BASE_ELEMENTS;
#ifdef __BLUETOOTH_OBEX_MMI__
    boolean             bIsRsp;
#endif
    IWidget             *pInputTextWdg;
    BTSRV_IndMsg_t      *ptIndMsg;
    boolean             bIsApStart;
    boolean             bIsSendPinRsp;
    BtNotifyAppMode_e   eMode;
} BtNotifyAppData_t;

typedef enum
{
    BTNOTIFYAPP_WND_ENTERPINCODE = WND_ID_APP_BASE
} BtNotifyAppWndId_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret BtNotifyAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret BtNotifyAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtNotifyAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtNotifyAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtNotifyAppResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtNotifyAppSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

void BtNotifyAppBtRecvFileIndCB(void *pApplet, BTSRV_TRANS_RESULT_e eResult);
void BtNotifyAppPairDondIndCB(void *pApplet, BTSRV_StatusCode_e eResult);
void BtNotifyAppPinCodeIndCB(void *pApplet, BTSRV_DevInfo_t *pPairDevInfo, BTSRV_StatusCode_e eResult);

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/
MAE_Ret _BtNotifyAppWndCreateEnterPinCode(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtNotifyAppWndDestroyEnterPinCode(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtNotifyAppWndSetEnterPinCode(void *pCusHandle, void *pWndData);
MAE_Ret _BtNotifyAppWndEnterPinCodeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif /*__BLUETOOTH_MMI__*/
#endif /* __MMI_BTNOTIFYAPP_PRIV_H__ */
