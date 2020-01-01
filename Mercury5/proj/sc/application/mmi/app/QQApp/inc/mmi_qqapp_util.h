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
* @file    mmi_qqapp_util.h
* @version
* @brief   QQ applet utility header file

*/

#ifndef __MMI_QQAPP_UTIL_H__
#define __MMI_QQAPP_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define QQAPP_LOGIN_ID_MAX_LENGTH 10
#define QQAPP_LOGIN_ID_MIN_LENGTH 5
#define QQAPP_MAX_MESSAGE_LENGTH  2048
#define QQAPP_SEND_MESSAGE_MAX_TEXT_LEN 1024
#define QQAPP_INTERVAL_TIME  400
#define QQAPP_MESSAGE_HISTORY_PERPAGE_NUM  10
#define QQAPP_MAX_BUDDY_INFO_LENGTH 2048
#ifdef __MULTIPLE_QQ__
#define QQAPP_Tab_Number 3
#define QQAPP_MAX_QQCLIENT_NUMBER 2
#else
#define QQAPP_Tab_Number 2
#endif
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_wdg_headers.h"

void QQApp_QQLoginSetFocus(void *pUserData, u32 newFocus);

void QQApp_QQLoginInputFocusChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bFocus, IWidget *pWidget);

void QQApp_AddBuddyWndQQIDInputTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

boolean QQApp_HandleLoginKeyPress(void *pApplet, u32 param1, u32 param2);

void QQApp_IDInputWidgetTextChangeCb(void *pApplet, void *pUsrData,
    WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

boolean QQApp_IDInputTxtWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_IDInputTxtWdgEvtHandlerFree(void *pUserData);

boolean QQApp_IDHistoryImageWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_IDHistoryImageWdgEvtHandlerFree(void *pUserData);

void QQApp_IDHistoryButtonClickHandleCb(void *pApplet, void *pUsrData,
    WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

boolean QQApp_PswInputTxtWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_PswInputTxtWdgEvtHandlerFree(void *pUserData);

boolean QQApp_RemPswTxtWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_RemPswTxtWdgEvtHandlerFree(void *pUserData);

boolean QQApp_RemPswSwitchIconWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_RemPswSwitchIconWdgEvtHandlerFree(void *pUserData);

boolean QQApp_RecvGroupMsgTxtWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_RecvGroupMsgTxtWdgEvtHandlerFree(void *pUserData);

boolean QQApp_RecvGroupMsgSwitchIconWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_RecvGroupMsgSwitchIconWdgEvtHandlerFree(void *pUserData);

boolean QQApp_HideLoginTxtWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_HideLoginTxtWdgEvtHandlerFree(void *pUserData);

boolean QQApp_HideLoginSwitchIconWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_HideLoginSwitchIconWdgEvtHandlerFree(void *pUserData);

boolean QQApp_VibrateOnTxtWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_VibrateOnTxtWdgEvtHandlerFree(void *pUserData);

boolean QQApp_VibrateOnSwitchIconWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_VibrateOnSwitchIconWdgEvtHandlerFree(void *pUserData);

boolean QQApp_SoundOnTxtWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_SoundOnTxtWdgEvtHandlerFree(void *pUserData);

boolean QQApp_SoundOnSwitchIconWdgEvtHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void QQApp_SoundOnSwitchIconWdgEvtHandlerFree(void *pUserData);

boolean QQApp_HandleSHOWLISTKeyPress(void *pCusHandle, MAE_EventId evt, u32 param1, u32 param2);

MAE_Ret QQ_WND_SHOWLISTWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam, void *pRC);

void QQApp_QQLoginOptionMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void QQApp_QQMessageHistoryOptionMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret QQApp_CreateAddBuddyReqOptMenuWnd(void * pCusHandle);

MAE_Ret QQ_WND_MAINMENUWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam, void *pRC);

void QQApp_QQMainMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode,  HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void QQApp_QQAddBuddyOptMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode,  HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void QQApp_SendMessageOptionMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret QQ_WND_PRESET_MESSAGEWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam, void *pRC);

void QQApp_QQPresetMessageSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode,  HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret _QQApp_DelBuddyConfirmDlgHandler(void *pApplet, MAEEvent_t eventID, u32 nParam1, u32 nParam2);

void _QQApp_PopupSelectSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _QQApp_PopupSelectAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);

MAE_Ret QQApp_WND_POPUPSELECTWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam, void *pRC);

MAE_Ret _QQAppSetting_Clean_ChatlogConfirmDlgHandler(void *pApplet, MAEEvent_t eventID, u32 nParam1, u32 nParam2);

MAE_Ret _QQAppSetting_Clean_LoginInfoConfirmDlgHandler(void *pApplet, MAEEvent_t eventID, u32 nParam1, u32 nParam2);

void QQApp_InitQQClientCB(void *pCusHandle, u32 status);

MAE_Ret  QQApp_CpyUtf8ToUcs2(u8 *pu8Str, MAE_WChar **ppwStr);

MAE_Ret  QQApp_CpyUcs2ToUtf8(MAE_WChar *pwStr, u8 **ppu8Str, size_t *pBytesWritten);

void QQApp_Init(void *pCusHandle);

void QQApp_DualSimSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _QQSelActiveSim(void *pCusHandle);

void _QQApp_SHOWLISTViewAdaptFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void _QQApp_SHOWLISTWndMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);

void _QQApp_LoginCB(void *pCusHandle, QQSrvErrCode_e status, u32 param2);

void _QQApp_ShowListTabChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);

void _QQApp_ShowListSetMenuWidgetSize(void *pApplet, u32 nId);

void _QQApp_ContactsListViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin,
                                   WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);

void _QQApp_QunListViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin,
                                  WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
#ifdef  __MULTIPLE_QQ__
void _QQApp_AccountListViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin,
                                  WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
#endif
void _QQApp_StatusChangeListenerCb(void *pApplet, QQSrvEvtUpdateItem_t *pEvtUpdateData);

void _QQApp_GetUnreadMsg(MAE_WChar **ppWmsgStr, VectorClass_t *pMsgVector, u32 Type);

MAE_Ret _QQApp_CheckUnreadMsg(void *pApplet);

void QQApp_SendQQSendMsgReq(void *pThis);

void QQApp_Logout(void *pApplet);

void _QQApp_BlinkHeadImageCb(void *pApplet);

MAE_Ret _QQApp_GetListVectorIndexByID(u32 VectorType, u32 u32ItemID, u32 *pu32ItemIndex);

void _QQApp_MoveToNextUreadMsgItem(void *pApplet);

void _QQApp_ShowListMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _QQApp_SendMsgOptionMenuLayer2SelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _QQApp_CreateSendMessageWND(void *pApplet);

void _QQApp_ShowListHandleMiddleKey(void *pApplet);

void QQApp_handleAppResumeStoppingCB(void *pApplet);

MAE_Ret QQApp_BootupFailed(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

void QQApp_AccessoryPlugStatusCB(void *pThis, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

void QQApp_UsbStatusChangedCB(void *pApplet, MMI_USB_STATUS_E eUsbStatus);

MAE_Ret QQApp_WND_SettingWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam, void *pRC);

void QQApp_AddBuddyByIdCB(void *pThis, QQSrvErrCode_e errCode, u32 param1);

void _QQApp_CreateLoadMessageHistoryWND(void *pApplet);

void _QQApp_ShowMessageHistoryWND(void *pApplet);

void _QQApp_DeleteMessageHistory(void *pApplet);

void _QQApp_CreateGetBuddyInfoWND(void *pApplet);

#ifdef __cplusplus
}
#endif

#endif /* __MMI_QQAPP_UTIL_H__ */
