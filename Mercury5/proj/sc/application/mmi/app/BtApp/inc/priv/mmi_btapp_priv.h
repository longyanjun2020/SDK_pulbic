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
* @file mmi_btapp_priv.h
*
* Class Id: CLSID_BTAPP
*
* @version $Id$
*/
#ifndef __MMI_BTAPP_PRIV_H__
#define __MMI_BTAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_btapp.h"
#include "mmi_srv_header.h"
#include "mmi_common_content.h"
#include "mmi_common_dialog.h"

#include "mmi_baseapplet.h"

#include "mmi_common_vtm.h"
#include "mmi_btapp_id.h"
#include "btapp_resource.h"


#ifdef __BLUETOOTH_MMI__
/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct 
{
    BTSRV_AudioDevLinkAction_e eLinkAction;
    BTSRV_PROFILE_e eProfile;
}BtAppAudioDeviceCmd_t;

typedef struct
{
    BTSRV_DevAddr_t BTAddr;
    u32 CoD;
}BtAppDevInfo_t;

typedef struct
{
    MenuWdgList_t tMenuWdgList;
} BtAppMain_t;

typedef struct
{
    MenuWdgList_t tMenuWdgList;
} BtAppSearching_t;

typedef struct
{
    MenuWdgList_t tMenuWdgList;
} BtAppSetting_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
} BtAppDeviceListOptionMenu_t;

typedef struct
{
    PromptInputWdgList_t tPromptInputWdgList;
} BtAppAddDeviceEnterPinCode_t;

typedef struct
{
    InputVtmWdgList_t tInputWdgList;
} BtAppInputShortName_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
} BtAppInputShortNameOptionMenu_t;

typedef struct
{
    InputVtmWdgList_t tInputWdgList;
} BtAppInputLocalName_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
} BtAppInputLocalNameOptionMenu_t;

typedef struct
{
    MenuWdgList_t           tMenuWdgList;
    BTSRV_DevAddr_t         SelectedPairDevAddr; /* The address of Pair Device which is selected by user */
} BtAppAddDevicetoMenu_t;

typedef struct
{
    PopUpInfoWdgList_t tPopupInfoWdgList;
} BtAppDeviceInfo_t;

typedef enum
{
    BtApp_AccessType_GET = 0,
    BtApp_AccessType_SET,
    BtApp_AccessType_RESET
} BtAppAccessType_e;

typedef enum
{
    BTAPP_MODE_NONE,
    BTAPP_MODE_IDLE,
    BTAPP_MODE_ADDDEVICE_TURNON,
    BTAPP_MODE_ADDDEVICE_WAITING,
    BTAPP_MODE_ADDDEVICE_SEARCHING,
    BTAPP_MODE_ADDDEVICE_FOUNDDEVICELIST,
    BTAPP_MODE_ADDDEVICE_PAIRING,    
    BTAPP_MODE_TURNONOFF_CANCELOPERATION,
    BTAPP_MODE_TURNONOFF_PROCESSING,
    BTAPP_MOVE_DEVICELIST_DEVICELISTMENU,
    BTAPP_MODE_DEVICELIST_TURNON,
    BTAPP_MODE_DEVICELIST_CONNECTING_CONNECTDEVICE,
    BTAPP_MODE_ADDDEVICE_NODEVICEFOUND,
    BTAPP_MODE_SENDFILE,
    BTAPP_MODE_SENDFILE_WAITING,
    BTAPP_MODE_SENDFILE_SENDING,
    BTAPP_MODE_DELETE_CONFIRM,
    BTAPP_MODE_DELETEALL_CONFIRM,
    BTAPP_MODE_ACCEPT_OTHER_DEVICE,
    BTAPP_MODE_ERRORGOBACK
} BtAppMode_e;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    boolean     bFreePossible;          // Use this flag to judge BTApp could be free or not

    MMI_BTAPP_ENTRY_MODE_e  eEntryFlag;
    u8  nMainMenuIdx;

    BTSRV_DevInfo_t     *pPairDevInfo; //The device to pair with

    BTSRV_StatusCode_e  PairResult;
    u8                  nPairDeviceIdx; //The dev idx in the pairing list selected by user
    u8              nSelectDevIdx; //The dev idx selected by user
    u8              nSettingFocusIdx;
    BTSRV_AudioLink_e eAudioLinkReq;
    BTSRV_AudioLink_e eConnParam;

    boolean     bIsNeedSendStop;
    boolean     bIsStopInquiry;
    boolean     bIsChipReset;
    boolean     bIsNeedSendDiscon;
    boolean     bIsStopInquiryBySelect;
    boolean     bIsBack;
    boolean     bIsSendPinRsp;
    boolean     bIsReqPowerOn;
    boolean     bIsNeedDisplayPairedNotice;
    boolean     bIsSendAbortTrans;
    boolean     bIsFailToChangeRecvFolder;

    // Widget for Menu View
    IWidget     *pMenuWdg;
    IWidget     *pITitleWdg;
    IWidget     *pProgressWdg;
    // startup data
    MmiBtappRequest_t tBtStartData;

    BtAppMode_e eMode;

    // nick.chan: pass parameters
    u8 nItem;
    boolean bFound;
    u8             nDevItemMaxSize;
    BtAppDevInfo_t *pDevItemData;

    u8             nAcceptAudioLinkItem;  //use this number to keep new dervice index (Ref. BtAppBtAcceptAudioLinkCnfCB)
    BtAppAudioDeviceCmd_t tAudioDevCmd;
    boolean bIsA2dpDisabled; //Display msg when this flag is TRUE 
    PFN_DlgHandler pfnAudioLinkDialogCB; //The dialog CB for audio link ind/cnf
} BtAppData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret BtAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret BtAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtAppStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtAppResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BtAppSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void BtAppBtPowerOnOffCnfCB(void *pApplet, BTSRV_StatusCode_e eResult, BTSRV_PowerAction_e eOnOffStatus);
void BtAppBtRecvFileIndCB(void *pApplet, BTSRV_TRANS_RESULT_e eResult);
void BtAppBtAudioLinkStatusChangeCB(void *pThis, u8 nItem, BTSRV_AudioDevLinkAction_e eLinkAction, BTSRV_PROFILE_e eLinkProfile, BTSRV_StatusCode_e eBtStatus, BTSRV_AudioDevLinkStatus_e eCurrentLinkStatus, BTSRV_AudioDevNotifyAttr_e eAttributes);
void BtAppBtAudioLinkCnfCB(void *pApplet, u8 nItem, BTSRV_Link_Status_e eLinkStatus);
void BtAppBtAudioLinkIndCB(void *pApplet, u8 nItem, BTSRV_Link_Status_e eLinkStatus);
void BtAppBtReadyCB(void *pApplet);
void BtAppBtPinCodeIndCB(void *pApplet, BTSRV_DevInfo_t *pPairDevInfo, BTSRV_StatusCode_e eResult);
void BtAppBtInquiryIndCB(void *pApplet, BTSRV_DevInfo_t *pBTDevInfo);
void BtAppBtInquiryCnfCB(void *pApplet, BTSRV_StatusCode_e eResult, u32 nNum);
void BtAppBtPairDoneIndCB(void *pApplet, BTSRV_StatusCode_e eResult);
void BtAppBtAclLinkCnfCB(void *pApplet, BTSRV_StatusCode_e eResult, BTSRV_ACLLink_t *pACLLink);
void BtAppBtTransProgressIndCB(void *pApplet, u32 nTransFileSize, u32 nTotalFileSize);
void BtAppBtSendFileIndCB(void *pApplet, BTSRV_TRANS_RESULT_e eResult);
void BtAppBtChipResetIndCB(void *pApplet);
void BtAppAccessoryPlugStatusChangeCB(void *pApplet, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
void BtAppBtAcceptAudioLinkCnfCB(void *pApplet, u8 nItem);
void BtAppBtCcRingIndCB(void *pApplet, u32 nDualID);

/*=============================================================*/
// Local function definition
/*=============================================================*/
MAE_Ret _BtAppWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyMain(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowMain(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideMain(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertMain(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateSetting(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroySetting(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowSetting(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideSetting(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertSetting(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateSearching(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroySearching(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowSearching(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideSearching(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertSearching(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateDeviceListOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyDeviceListOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowDeviceListOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideDeviceListOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertDeviceListOptionMenu(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateAddDeviceToMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyAddDeviceToMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowAddDeviceToMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideAddDeviceToMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertAddDeviceToMenu(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateAddDeviceEnterPinCode(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyAddDeviceEnterPinCode(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowAddDeviceEnterPinCode(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideAddDeviceEnterPinCode(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertAddDeviceEnterPinCode(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateInputShortName(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyInputShortName(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowInputShortName(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideInputShortName(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertInputShortName(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateInputShortNameOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyInputShortNameOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertInputShortNameOptionMenu(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateInputLocalName(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyInputLocalName(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndShowInputLocalName(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndHideInputLocalName(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertInputLocalName(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateInputLocalNameOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyInputLocalNameOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertInputLocalNameOptionMenu(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndCreateDeviceInformation(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDestroyDeviceInformation(void *pCusHandle, void *pWndData);
MAE_Ret _BtAppWndConvertDeviceInformation(void *pCusHandle, void *pWndData);

MAE_Ret _BtAppWndMainHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndSearchingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndSettingHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndLaunchNameEditorHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDeviceListOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndAddDeviceToMenuHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndAddDeviceEnterPinCodeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndInputShortNameHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndInputShortNameOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndInputLocalNameHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndInputLocalNameOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _BtAppWndDeviceInformationHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

void BtAppSwitchWindow(BtAppData_t *pThis, MAE_WndId nWndId, u32 nWndInitParam, boolean bClose);

void BtAppIdle(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void BtAppIdleAction(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);

void _BtAppAddDeviceTurnOn(BtAppData_t *pThis);
void _BtAppAddDeviceSearching(BtAppData_t *pThis);
void _BtAppDeviceListTurnOn(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);

void _BtAppInputLocalNameKeyPressCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppInputShortNameKeyPressCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);

boolean _BtAppIsHifiDevice(u32 CoD);
boolean _BtAppIsAudioDevice(u32 CoD);

#if 0
boolean _BtAppIsBtHandsFreeOnly(u32 CoD);
#endif

// Insert "search device" entry into DeviceList menu
static void _BtAppDeviceList_SearchDeviceEntry(BtAppData_t *pThis);

static void _BtAppFreeFoundDeviceItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void _BtAppMainMenuMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _BtAppDeviceFoundMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static u32 _BtAppGetDeviceImage(BtAppData_t *pThis, BTSRV_DevInfo_t *pBTDevInfo);
static void _BtAppAddDeviceToMenu(BtAppData_t *pThis, BTSRV_DevInfo_t *pBTDevInfo,  u8 index, boolean bFound);
void _BtAppPairedDeviceMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _BtAppPairedDeviceOptionSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _BtAppSettingMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __BLUETOOTH_A2DP_MMI__
static void _BtAppDeviceListOptionMenuLayer2SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pWidget);
static MAE_Ret _BtAppCloseA2dpStreamDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
#endif //__BLUETOOTH_A2DP_MMI__

void _BtAppTurnOnOffProcessingBtSrvPowerOnOffCnfCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppTurnOnOffCancelOperationBtSrvRecvFileIndCb(BtAppData_t *pThis);
MAE_Ret _BtAppDeviceListTurnOnEventCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppDeviceListConnecting(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppDeviceListConnectingCheckConnection(BtAppData_t *pThis);
void _BtAppDeviceListConnectingConnectDevice(BtAppData_t *pThis);
void _BtAppDeviceListOptionMenuAudioDeviceAction(BtAppData_t* pThis, BTSRV_AudioDevLinkAction_e eLinkAction, BTSRV_PROFILE_e eProfile);
void _BtAppAddDeviceWaitingBtSrvPinCodeIndCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceFoundDeviceList(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceFoundDeviceListBtSrvInquiryIndCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceFoundDeviceListMenuSelectCb(BtAppData_t *pThis);
void _BtAppAddDeviceFoundDeviceListMenuSelectBtSrvInquiryCnfCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceFoundDeviceListMenuBackCb(BtAppData_t *pThis);
void _BtAppAddDeviceFoundDeviceListMenuBackBtSrvInquiryCnfCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceFoundDeviceListBackCb(BtAppData_t *pThis);
void _BtAppDeviceListDeviceListMenu(BtAppData_t *pThis);
void _BtAppDeviceListSelectDeviceAction(BtAppData_t *pThis);
MAE_Ret _BtAppAddDeviceSearchingKeyPressCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceWaiting(BtAppData_t *pThis);
void _BtAppAddDeviceEnterPinCodeKeyPressCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceEnterPinCodeTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void _BtAppAddDevicePairing(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDevicePairingBtAclLinkCnfCb(BtAppData_t *pThis);
void _BtAppDeviceListSetAuthorize(BtAppData_t *pThis);
MAE_Ret _BtAppAddDevicePairingStopDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDevicePairingBtPairDoneIndCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppSendFileKeyPressCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppSendFileWaiting(BtAppData_t *pThis);
void _BtAppSendFile(BtAppData_t *pThis);
void _BtAppSendFileDeleteCurrentFile(BtAppData_t *pThis);
void _BtAppSendFileDeleteAllFiles(BtAppData_t *pThis);
MAE_Ret _BtAppAddDeviceTurnOnEventCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceNoDeviceFound(BtAppData_t *pThis);
void _BtAppHandleSendFileSendingEvt(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppSendFileSendingSuccessDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppSendFileSendingFailureDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppAddDeviceBtSrvRecvFileIndCb(BtAppData_t *pThis);
void _BtAppAddDeviceFoundDeviceListBtChipResetIndCb(BtAppData_t *pThis);
void _BtAppSendFileExit(BtAppData_t *pThis);
MAE_Ret _BtAppWarnGobackCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppErrorGobackCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppAudioLinkStatusChangeCB(BtAppData_t *pThis, u8 nItem, BTSRV_AudioDevLinkAction_e eLinkAction, BTSRV_PROFILE_e eLinkProfile, BTSRV_StatusCode_e eBtStatus, BTSRV_AudioDevLinkStatus_e eCurrentLinkStatus, BTSRV_AudioDevNotifyAttr_e eAttributes, PFN_DlgHandler pFnDlgHandler);
void _BtAppRestoreAudioDeviceCheckBox(BtAppData_t *pThis, BTSRV_PROFILE_e eProfile);
void _BtAppUpdateAudioDeviceCheckBox(BtAppData_t *pThis, BTSRV_AudioDevLinkStatus_e eCurrentLinkStatus);
void _BtAppAudioLinkCB(BtAppData_t *pThis, u8 nItem, BTSRV_Link_Status_e eLinkStatus, PFN_DlgHandler pFnHandler);
MAE_Ret _BtAppDeviceListDeleteConfirmDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret BtAppDeviceListDeleteAllConfirmDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret BtAppAudioLinkCnfDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppTurnOnOffProcessingDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppAddDeviceTurnOnDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppAddDeviceFoundDeviceListDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppAddDeviceNoDeviceFoundDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppAddDevicePairingDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppDeviceListTurnOnDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppAbortSendFile(BtAppData_t *pThis);
void _BtAppAbortRecvFile(BtAppData_t *pThis);

static MAE_Ret _BtAppBacklightOn(BtAppData_t *pThis);

static MAE_Ret _BtAppInputShortNameSave(BtAppData_t *pThis);
static void _BtAppInputShortNameOptionMenuViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _BtAppInputShortNameOptionMenuViewModelLayer2Listener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _BtAppInputShortNameTextInputOptionMenuViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

static MAE_Ret _BtAppInputLocalNameSave(BtAppData_t *pThis);
static void _BtAppInputLocalNameOptionMenuViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _BtAppInputLocalNameOptionMenuViewModelLayer2Listener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _BtAppInputLocalNameTextInputOptionMenuViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#ifdef __BLUETOOTH_USER_DEFINED_FOLDER_MMI__
static void BtAppSelectReceiveFolder(BtAppData_t *pThis);
#endif

#ifdef __BLUETOOTH_OBEX_MMI__
static void _BtAppDeleteSendingFile(BtAppData_t *pThis);
#endif

void _BtAppTurnOnOffCancelOperation(BtAppData_t *pThis);
void _BtAppTurnOnOffProcessing(BtAppData_t *pThis);

void _BtAppDeviceInformationKeyPressCb(BtAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _BtAppSetWdgLayout(HWIN hWin, IWidget *pWdg, Pos_t *pPos, WidgetSize_t *pSize);
MAE_Ret _BtAppBtAcceptAudioLinkCnfCB(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _BtAppBtAcceptAudioLinkWhenRecvFileCnfCB(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
static void _BtAppPrintoutString(BtAppData_t *pThis, MAE_WChar *pWStr);
static MAE_Ret _BtAppAudioLinkShowMsgDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _BtAppAccessSelPairDevAddr(BtAppData_t *pThis, BtAppAccessType_e accessType, BTSRV_DevAddr_t *pDevAddr);

#endif /*__BLUETOOTH_MMI__*/
#endif /* __MMI_BTAPP_PRIV_H__ */
