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
* @file    mmi_callsettingapp_priv.h
* @version
* @brief   CallSetting applet private header file
*
*/

#ifndef __MMI_CALLSETTINGAPP_PRIV_H__
#define __MMI_CALLSETTINGAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_callsettingapp.h"

#include "mmi_common_vtm.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_rai_id.h"
#include "mmi_srv_header.h"
#include "mmi_common_cfg.h"
#include "mmi_event.h"

//#ifdef __IP_CALL_MMI__
#include "mmi_common_cfg.h"
//#endif
#include "mmi_launcher_calllog.h"
#include "mmi_launcher_shortcut.h"
#include "mmi_launcher_voicemail.h"
#include "mmi_launcher_filemanager.h"
#include "mmi_launcher_voicememo.h"
#ifdef __APP_MMI_ANSWERING_MACHINE__
#include "mmi_launcher_sendvia.h"
#include "mmi_launcher_phb.h"
#include "mmi_common_window.h"
#endif
#ifdef __APP_VIDEO_TELEPHONY__
#include "mmi_common_window.h"
#endif
#include "mmi_callsettingapp_id.h"
#include "callsettingapp_resource.h"
#include "mmi_subject.h"

#ifndef CALLSETTINGAPP_SUPPORT_ANY_KEY_ANSWER
#define CALLSETTINGAPP_SUPPORT_ANY_KEY_ANSWER
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

#define CALLSETTING_TITLE_FORMAT L"%s %s"
#define CALLSETTING_TITLE_LEN 35

/*=============================================================*/
// Internal Event
/*=============================================================*/
#define CALLSETTINGAP_IEVT_REFRESH_WND (CLSID_CALLSETTINGAPP << 16 | 1)


/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    boolean     bFreeStructure;
    boolean     bLogHistory;
    u32         nLogFirstItemIndex;
    u32         nLogHighlightIndex;
    boolean     bLogHistory_Lev2;
    u32         nLogFirstItemIndex_Lev2;
    u32         nLogHighlightIndex_Lev2;

    boolean     bLogHistory_Class;
    u32         nLogFirstItemIndex_Class;
    u32         nLogHighlightIndex_Class;
}CallSettingMainList_t;

typedef struct
{
    IWidget *pVolWdg;
} CallSettingAppVolume_t;


#ifdef __APP_MMI_ANSWERING_MACHINE__
typedef enum
{
	VB_CONFIRM = 0,
	VB_DELETING,
	VB_UNKNOWN
} VB_DELETE_MODE_e;
#endif

typedef struct
{
    //Keep settings of call setting ap
    u16         nMinuteReminder; //keep reminder seconds
    u8          nCallerIdentity1;
	u8          nCallerIdentity2;
    u8          nAnswerMode;
    u8          nAutoRedial;
#ifdef __ANSWER_INDICATOR_MMI__
    u8          nAnswerIndicator;
#endif
#ifdef __FT_AUTO_TEST__
	boolean		bRejectMT;
#endif
#ifdef __DISTORTED_VOICE_MMI__
	boolean    bIsLaunchByCS; // Is distorted voice launch by call settings app?
	boolean    bDistortedVoice;
	u8         nDistortedEffect;
#endif
#ifdef __HALL_SWITCH_MMI__
   boolean bCloseHangUpCall;
   boolean bOpenAcceptCall;
#endif
	boolean bEnterOtherAP;//, bCardInserted;
	CFGItemID_e eCFGItemID;
	MMI_USB_STATUS_E ePreUsbStatus;
#if defined(__APP_MMI_CHECKDISK__)
	SubjectStatus_e ePreCheckDiskStatus;
#endif
	boolean bPlaying;
#ifdef __APP_MMI_ANSWERING_MACHINE__
	boolean bAMStatus, bDeleteAll, bViaStorageSelect;
	MAE_WChar *pszTextLine2, *pszUserDefined, *pszCurFolder;
	u8 u8AMAutoAnswerAfterRing;
	//MMI_CALLSETTING_AM_STORAGE_e eAMStorage;
	FileMgrHandleID_t nFileHandle;
    ArrayClass_t *pVoiceBoxIndexArray;
	u32 nHighlightedIndex;
	VB_DELETE_MODE_e eDeleteMode;
#endif
#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
	boolean bCBSStatus;
	CallBgSound_Play_Type_e eCBSPlayType;
	u8 u8CBSPlayInterval;
	u8 u8CBSCurEffect;
	SetRingToneVolume_e eCBSVolume, eTmpVolume;
	MAE_WChar *pITextLine2PlayType, *pITextLine2EffectSound, *pITextLine2Volume, *pIntervalText;
	IWidget *pIOptionMenuWidget;
	ModelListener_t stL1OptionModelListener;
	boolean bLogEffectListHistory;
	u32 u32LogEffectListFirstItemIndex;
	u32 u32LogEffectListHighlightIndex;
#endif
#ifdef __APP_VIDEO_TELEPHONY__
	VideoCall_Setting_MODE_e eVcMode;
#endif
#ifdef __AUTO_RECORDING_MMI__
    boolean     bAutoRecording;
#endif
} CallSettingAppSetting_t;

typedef struct
{
    //Keep settings of CUG
    MAE_WChar   *pWStrIndex;
    u8          nStatus;
    u8          nIndex;
    u8          nOutsideAccess;

}CallSettingCUGSetting_t;

typedef enum
{
    CS_EDIT_PWD_STEP_OLD,       //enter old pwd
    CS_EDIT_PWD_STEP_NEW,       //enter new pwd
    CS_EDIT_PWD_STEP_CONFIRM    //enter confirm pwd
} CS_EDIT_PWD_STEP_e;

typedef enum
{
    CS_REQUEST_TYPE_NONE = 0,   //none
    CS_REQUEST_TYPE_CFX,        //Call Divert
    CS_REQUEST_TYPE_CBX,        //Call Barring
    CS_REQUEST_TYPE_CWX,        //Call Waiting
    CS_REQUEST_TYPE_CHANGE_PWD, //change barring password
    CS_REQUEST_TYPE_USER_GROUP_QUERY,  //get user group
    CS_REQUEST_TYPE_USER_GROUP_SET,  //set user group
    CS_REQUEST_TYPE_CALLER_IDENTITY, //CALLER IDENTITY
    CS_REQUEST_TYPE_CALL_COST, // call cost
} CS_REQUEST_TYPE_e;

typedef union
{
    SSSRV_CallDivertReq_t           tCallDivertReq;
    SSSRV_CallBarringReq_t          tCallBarringReq;
    SSSRV_CallWaitingReq_t          tCallWaitingReq;
    SSSRV_ChangeBarringPwdReq_t     tChangeBarringPwdReq;
    SSSRV_UserGroupReq_t            tUserGroupReq;
} CS_UNION_REQUEST_INFO_t;

typedef struct
{
    CS_REQUEST_TYPE_e        eRequestType;      /*Record request type */
    CS_UNION_REQUEST_INFO_t  tRequestInfo;       /*Record request information */
} CS_REQUEST_t;


#ifdef __IP_CALL_MMI__
typedef enum
{
    CS_IPCALL_EDIT_NAME = 0,
    CS_IPCALL_EDIT_NUMBER
} CS_IPCALL_EDIT_e;
#endif

typedef struct
{
    APPLET_BASE_ELEMENTS;

    u8          nCurrDualID;

    CallSettingAppSetting_t         tCallSetting;       //for keep current call settings
    CallSettingCUGSetting_t         tCUGSetting;        //for keep current CUG settings
    CallSettingCUGSetting_t         tCUGSettingTemp;    //for keep temp CUG settings
    CallSettingMainList_t           *pMMIMainList;
    CS_EDIT_PWD_STEP_e              ePwdStep;           //for keep change pwd step

#ifdef __IP_CALL_MMI__
    MAE_WChar                           *pWChar;
    IPCALL_SET_t                        *pIPCALL_SET;
    IPCALL_SET_t                        *pTmp_IPCALL_Set;

    u8                  nIPcallListIdx;
    u8                  nIPcallDetailIdx;
    u8                  nTotalIpNum;
    u8                  nTargetIdx;
    boolean             bIsAddNum;
    boolean             bIsFromDetailView;
    boolean             bHasNameText;
#endif

    //Request data
    CS_REQUEST_t                        tRequestData;
    CS_REQUEST_TYPE_e                   eCurrentRequestType;
    MMI_SSSRV_CallClass_e               eCurrentCallClass;
	MAE_WChar				            *pWStrTitle;

    //UI enhancement
    MMI_CALLSETTING_APP_MODE_e          eAppMode;

    boolean             bIsWaitingCnf;       //for keep current request status
    boolean             bIsLaunchVMAAP;
    CmnAppLaunchRspCbInfo_t tRspCbInfo;
} CallSettingAppData_t;

typedef struct
{
    SimSelectionWdgList_t tWdgList;
}SelectDualSIMWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
}MainListWndData_t;

#ifdef __HALL_SWITCH_MMI__
typedef struct
{
    MenuWdgList_t tWdgList;
}SlideSettingWndData_t;
#endif

typedef struct
{
    MenuWdgList_t tWdgList;
}ClassListWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
}DivertListWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
}DivertSelectTypeListWndData_t;

typedef struct
{
    PopUpInputWdgList_t tWdgList;
}DivertToNumberInputPopupWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
}BarringListWndData_t;

typedef struct
{
    PopUpInputWdgList_t tWdgList;
}BarringCheckPasswordInputPopupWndData_t;

typedef struct
{
    PopUpInputWdgList_t tWdgList;
}BarringChangePasswordInputPopupWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
}OperationListWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
}AnswerModeMenuWndData_t;

typedef struct
{
    PopUpSelectWdgList_t tWdgList;
}CallerIdentityMenuPopupWndData_t;

typedef struct
{
    PopUpSelectWdgList_t tWdgList;
    PopUpSelectCB_t tCB;
}MinuteReminderMenuPopupWndData_t;

#ifdef __APP_VIDEO_TELEPHONY__
typedef struct
{
    PopUpSelectWdgList_t tWdgList;
    PopUpSelectCB_t tCB;
}VideoCallMenuPopupWndData_t;
#endif

typedef struct
{
    PopUpInputWdgList_t tWdgList;
}MinuteReminderInputPopupWndData_t;

typedef struct
{
    PopUpSelectWdgList_t tWdgList;
}AnswerIndicatorMenuPopupWndData_t;

typedef struct
{
    PopUpInfoWdgList_t tWdgList;
}NewResultScreenPopupWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
    MenuCB_t tCB;
}UserGroupListWndData_t;

typedef struct
{
    PopUpInputWdgList_t tWdgList;
}UserGroupSetIndexInputPopupWndData_t;

#ifdef __IP_CALL_MMI__

typedef struct
{
    MenuWdgList_t tWdgList;
    MenuCB_t tCB;
}IPcallNumberListWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
    MenuCB_t tCB;
}IPcallDetailListWndData_t;

typedef struct
{
    InputVtmWdgList_t tWdgList;
}IPcallNameInputWindowWndData_t;

typedef struct
{
    PopUpInputWdgList_t tWdgList;
}IPcallNumberInputPopupWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
}IPcallNameInputOptionMenuWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
}IPcallNameOptionMenuWndData_t;

#endif


#ifdef __DISTORTED_VOICE_MMI__
typedef struct
{
    MenuWdgList_t tWdgList;
}DistortedVoiceWndData_t;

typedef struct
{
    PopUpSelectWdgList_t tWdgList;
}DistortedEffectWndData_t;
#endif

#ifdef __MMI_CALL_FIREWALL__
typedef struct
{
    MenuWdgList_t tWdgList;
}CallFirewallWndData_t;

typedef struct
{
    PopUpSelectWdgList_t tWdgList;
}FirewallFilterWndData_t;

typedef struct
{
    PopUpSelectWdgList_t tWdgList;
}FirewallAnsweringWndData_t;
#endif

/*=============================================================*/
// Global function definition
/*=============================================================*/

boolean CallSettingConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallSettingDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallSettingStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallSettingStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallSettingSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallSettingResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallSettingKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallSettingEmbeddedApCloseCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void CallSettingSSSrvCFXCnfCb(void *pApplet, SSSRV_CallDivertCnf_t *pCallDivert);
void CallSettingSSSrvCBXCnfCb(void *pApplet, SSSRV_CallBarringCnf_t *pCallBarring);
void CallSettingSSSrvCWXCnfCb(void *pApplet, SSSRV_CallWaitingCnf_t *pCallWaiting);
void CallSettingSSSrvPWDCnfCb(void *pApplet, MMI_SSSRV_SS_Result_e eResult);
void CallSettingSSSrvQueryCUGCnfCb(void *pApplet, SSSRV_UserGroupQueCnf_t *pQueCUG);
void CallSettingSSSrvSetCUGCnfCb(void *pApplet, MMI_SSSRV_SS_Result_e eResult);
void CallSettingIPcallCfgSrvUpdateCb(void *pUserData, SrvCfgItemStatusChangeType_e eIndType, SrvCfgItemUpdateResult_t tResult);
MAE_Ret CallSettingDoneScreenTimerCb(void *pData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CallSettingProcessingScreenCancelCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CallSettingConfirmScreenCheckCb(IApplet *pApplet, u32 nEvt, MAEEvent_t nParam1, u32 nParam2);
void CallSettingInputWidgetTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

#ifdef __IP_CALL_MMI__

MAE_Ret CallSettingIPcallSaveScreenDialogTimerCb(void* data, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CallSettingIPcallDeleteScreenDialogTimerCb(void* data, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CallSettingIPcallListFullScreenDialogTimerCb(void* data, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CallSettingIPcallNumIsEmptyScreenDialogTimerCb(void* data, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

#endif

//Window manager related function
MAE_Ret CallSettingWndSelectDualSIMHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndMainListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndClassListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __HALL_SWITCH_MMI__
MAE_Ret CallSettingWndSlideSettingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void CallSettingSlideSettingMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
MAE_Ret CallSettingWndOperationListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndDivertListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndDivertSelectTypeListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndDivertToNumberInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndBarringListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndBarringCheckPasswordInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndBarringChangePasswordInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndNewResultScreenPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndAnswerModeMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndCallerIdentityMenuPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __APP_VIDEO_TELEPHONY__
MAE_Ret CallSettingWndVideoCallSettingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndVideoCallMenuPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _CallSettingWndConvertVideoCallSetting(void *pCusHandle, void* pWndData);
#endif
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _CallSettingWndConvertVideoCallMenuPopup(void *pCusHandle, void* pWndData);
#endif
static void CallSettingVideoCallSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
MAE_Ret CallSettingWndMinuteReminderMenuPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndMinuteReminderInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __ANSWER_INDICATOR_MMI__
MAE_Ret CallSettingWndAnswerIndicatorMenuPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret CallSettingWndEditDivertToHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndEditPwdHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndEditTimerHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndUserGroupListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndUserGroupSetIndexInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#ifdef __IP_CALL_MMI__

MAE_Ret CallSettingWndIPcallDetailListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndIPcallNumberListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndIPcallOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndIPcallNumberInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndIPcallNameInputWindowHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CallSettingWndIPcallNameInputOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif
MAE_Ret _CallSettingWndConvertMainList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndCONVERTSelectDualSIM(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertClassList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertBarringList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertDivertList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertAnswerModeMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertIPcallDetailList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertIPcallNumberList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertIPcallOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertUserGroupList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertAnswerIndicatorMenuPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertCallerIdentityMenuPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertDivertSelectTypeList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertIPcallNameInputWindow(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertIPcallNumberInputPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertMinuteReminderInputPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertNewResultScreenPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertBarringChangePasswordInputPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertBarringCheckPasswordInputPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertDivertToNumberInputPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertIPcallNameInputOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallSettingWndConvertUserGroupSetIndexInputPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);

#ifdef __DISTORTED_VOICE_MMI__
static void    CallSettingShowDistortedVoice(CallSettingAppData_t* pThis, u32 nParam1, u32 nParam2);
static MAE_Ret CallSettingWndDistortedVoiceHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingDistortedVoiceCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingDistortedVoiceConvert(void* pCusHandle, void* pWndData);
#endif
static void    CallSettingDistortedVoiceSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void    CallSettingDistortedVoiceStatusSet(CallSettingAppData_t* pThis);
static void    CallSettingDistortedVoiceNotifyChange(CallSettingAppData_t* pThis);
static void    CallSettingShowDistortedEffect(CallSettingAppData_t* pThis, u32 nParam1, u32 nParam2);
static MAE_Ret CallSettingWndDistortedEffectHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingDistortedEffectCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingDistortedEffectConvert(void *pCusHandle, void *pWndData);
static void    CallSettingDistortedEffectSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

boolean CallSettingIsMassStorage(void);
boolean CallSettingRefreshWnd(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static void CallSettingSavePopupInputData(CallSettingAppData_t *pThis, MAE_WndId nWndID);

#if defined(__APP_MMI_ANSWERING_MACHINE__) || defined(__APP_MMI_CALL_BACKGROUND_SOUND__)
static void CallSettingLaunchFileManager(CallSettingAppData_t *pThis, CFGItemID_e eCFGItemID, u32 nTextID);
static void CallSettingFileMgrContentFilterCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);
static void CallSettingGetFileByBrowseCb(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
static void CallSettingAudioFileInfoCB(void *pApplet, MediaSrvErrCode_e eErrorCode, u32 nCusData, AudioSrvFileInfo_t *pAudFileInfo);
static void CallSettingAccessorySrvPlugStatusCB(void *pThis, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
static void CallSettingUsbStatusChangedCB(void *pThis, MMI_USB_STATUS_E eUsbStatus);
#if defined(__APP_MMI_CHECKDISK__)
static void CallSettingCheckDiskListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif
static void CallSettingPopupMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void CallSettingShowPopupInput(CallSettingAppData_t* pThis, MAE_WndId nWndID);
static MAE_Ret CallSettingWndPopupInputHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingWndCreatePopupInput(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
MAE_Ret CallSettingWndConvertPopupInput(void *pCusHandle, void *pWndData);
#endif
static void CallSettingShowOptionMenu(CallSettingAppData_t* pThis, MAE_WndId nWinID);
static MAE_Ret CallSettingWndOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingCreateOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingConvertOptionMenu(void *pCusHandle, void* pWndData);
#endif
static void CallSettingOptionMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
static void CallSettingLogMenuHistory(CallSettingAppData_t* pThis);

#ifdef __APP_MMI_ANSWERING_MACHINE__
static void CallSettingShowAnsweringMachineMenu(CallSettingAppData_t* pThis, u32 nParam1);
static void CallSettingShowAMGreetingPopupMenu(CallSettingAppData_t* pThis, u32 nParam1);
static void CallSettingShowAMAfterRingPopupMenu(CallSettingAppData_t* pThis, u32 nParam1);
static void CallSettingShowAMVoiceBoxMenu(CallSettingAppData_t* pThis, u32 nParam1);
static MAE_Ret CallSettingWndAnsweringMachineListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingWndAMGreetingPopupMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingWndAMAfterRingPopupMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingWndAMVoiceBoxListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingWndCreateAnsweringMachineList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingWndConvertAnsweringMachineList(void *pCusHandle, void* pWndData);
#endif
static MAE_Ret CallSettingWndCreateAMGreetingPopupMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingWndConvertAMGreetingPopupMenu(void *pCusHandle, void* pWndData);
#endif
static MAE_Ret CallSettingWndCreateAMAfterRingPopupMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingWndConvertAMAfterRingPopupMenu(void *pCusHandle, void* pWndData);
#endif
static MAE_Ret CallSettingWndCreateAMVoiceBoxList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingWndConvertAMVoiceBoxList(void *pCusHandle, void* pWndData);
#endif
static void CallSettingAnsweringMachineListMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static MAE_Ret CallSettingAMSelectStorageMenuCb(void *pCusHandle, const CommWindowMsg_t *pWndMsg, void *pParam1, void *pParam2);
static MAE_Ret CallSettingAMSetStorageMenuCb(void *pCusHandle, const CommWindowMsg_t *pWndMsg, void *pParam1, void *pParam2);
static void CallSettingAMVoiceBoxListSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void CallSettingAMVoiceBoxListMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
static void CallSettingMenuReqLayer2Cb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void CallSettingLaunchVoiceMemo(CallSettingAppData_t *pThis);
static void CallSettingVoiceMemoFileOpRspCb(void *pvUserData, MAE_Ret nRspCode, FileOpInfo_t *psRspData, CmnLaunchAppFileOpRspFreeCb pfnRspFreeCb);
static void CallSettingAMVoiceBoxListMenuGetItemData(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
static void CallSettingAMVoiceBoxListMenuFreeItemData(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static boolean CallSettingGetVoiceBoxAMRFiles(CallSettingAppData_t *pThis);
static s32 CallSettingFileDecreasingDateComp(void *pBase, void* pRef);
static void CallSettingPhbGetNameByNumber(MAE_WChar *pwNumber, MAE_WChar **ppwName);
static void CallSettingVoiceBoxPlay(CallSettingAppData_t *pThis);
static void CallSettingVoiceBoxStop(CallSettingAppData_t *pThis);
static void CallSettingVoiceBoxAudioSrvPlayStatusCb(void *pData, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
static void CallSettingVoiceBoxAudioSrvInterruptNotifyCb(void *pThis, u32 nCusData, MediaSrvInterruptStatus_e nStatus);
static void CallSettingVoiceBoxOpenVolumeDlg(CallSettingAppData_t *pThis);
static void CallSettingVolumeModelListener(void *pUserData, ModelEvent_t *pModelEvent);
static void CallSettingVoiceBoxCloseVolumeDlg(CallSettingAppData_t *pThis);
static void CallSettingVoiceBoxSendVia(CallSettingAppData_t *pThis);
static MAE_Ret CallSettingVoiceBoxGetCurFilePathName(CallSettingAppData_t *pThis, MAE_WChar *pURL);
static void CallSettingVoiceBoxSetAsIncoming(CallSettingAppData_t *pThis, u32 u32SelectedID);
static void CallSettingVoiceBoxSetAsContact(CallSettingAppData_t *pThis);
#ifdef __USER_DEFINE_POWERONOFF_MELODY__
static void CallSettingVoiceBoxSetAsPowerOnOff(CallSettingAppData_t *pThis, u32 u32SelectedID);
#endif
static void CallSettingVoiceBoxSetAsAlarm(CallSettingAppData_t *pThis);
static void CallSettingVoiceBoxOpenDeleteConfirmDlg(CallSettingAppData_t *pThis, boolean bDeleteAll);
static MAE_Ret CallSettingVoiceBoxDlgHandler(void *pData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
static void CallSettingVoiceBoxOpenDeleteWaitingDlg(CallSettingAppData_t *pThis);
static void CallSettingVoiceBoxTimerDoDeleteAction(void *pUserData);
#endif // __APP_MMI_ANSWERING_MACHINE_
#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
static void CallSettingShowCallBgSndMenu(CallSettingAppData_t* pThis, u32 nParam1);
static MAE_Ret CallSettingWndCallBgSndListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingCreateCallBgSndList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingConvertCallBgSndList(void *pCusHandle, void* pWndData);
#endif
static void CallSettingCallBgSndMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static boolean CallSettingCBSResetCurrentEffect(CallSettingAppData_t *pThis);
static void CallSettingShowCBSPlayTypeMenu(CallSettingAppData_t* pThis, u32 nParam1);
static MAE_Ret CallSettingWndCBSPlayTypeMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingCreateCBSPlayTypeMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void CallSettingConvertCBSPlayTypeMenu(void *pCusHandle, void* pWndData);
#endif
static void CallSettingShowCBSEffectSoundList(CallSettingAppData_t* pThis, u32 nParam1);
static MAE_Ret CallSettingWndCBSEffectSoundListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingCreateCBSEffectSoundList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static void CallSettingCBSEffectSoundListSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static MAE_Ret CallSettingConvertCBSEffectSoundList(void *pCusHandle, void *pWndData);
static void CallSettingCBSEffectSoundListMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
static void CallSettingCBSEffectSoundListGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
static void CallSettingCBSEffectSoundListFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static boolean CallSettingCBSSelectEffectItem(CallSettingAppData_t *pThis, u32 u32Selected);
static void CallSettingCBSAudioSrvCb(void *pData, MediaSrvErrCode_e eErrorCode);
static void CallSettingCBSAudioSrvInterruptNotifyCb(void *pThis, u32 nCusData, MediaSrvInterruptStatus_e nStatus);
static void CallSettingShowCBSVolume(CallSettingAppData_t* pThis, u32 nParam1);
static MAE_Ret CallSettingWndCBSVolumeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CallSettingCreateCBSVolumeWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
MAE_Ret CallSettingSetCBSVolumeWnd(void *pCusHandle, void *pWndData);
#endif
static void CallSettingCBSVolumeChange(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nCurrentLevel, IWidget *pWidget);
static void CallSettingCBSNotifyChange(CallSettingAppData_t* pThis, const CFGItemID_e eCFGItemID, const u8 u8Data);
#endif
#endif /* __MMI_CALLSETTINGAPP_PRIV_H__ */

