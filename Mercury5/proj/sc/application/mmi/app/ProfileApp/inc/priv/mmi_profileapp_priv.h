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
* @file mmi_profile_priv.h
*
* Class Id: CLSID_PROFILEAPP
*
* @version $Id$
*/
#ifndef __MMI_PROFILEAPP_PRIV_H__
#define __MMI_PROFILEAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_profileapp.h"
#include "mmi_baseapplet.h"
#include "mmi_common_util.h"
#include "mmi_common_dialog.h"

#include "mmi_profilesrv.h"
#include "mmi_previewline2srv.h"

#include "mmi_launcher_common.h"
#include "mmi_launcher_security.h"

#include "mmi_common_vtm.h"
#include "mmi_profileapp_id.h"
#include "profileapp_resource.h"

#include "mmi_usbsrv.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

typedef u32 MenuItemID_e;
#define START_PLAY_POSITION 0
#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    u32             u32NextFormType;
    u32             u32ViewID;
} ProfileAppEditListModelItem_t;

typedef struct
{
    IWidget         *pIMenuWdg;
} ProfileAppMainList_t;

typedef struct
{
    IWidget         *pIOptMenuWdg;
} ProfileAppOptionMenuList_t;

typedef struct
{
    ProfileSettings_t   stProfileSetting;
    IWidget             *pIMenuWdg;
} ProfileAppEditList_t;

typedef struct
{
    IWidget             *pVolumeWdg;    //Image widget
    MAE_WChar           *pMelodyURL;    //MAE_WChar using for play ringer URL
    MenuItemId_e        eMenuItemID;
    CFGItemID_e         eCFGItemID;
    u32                 nVolRetryCount;
    SetRingToneVolume_e eOrigVolumeLevel;
    SetRingToneVolume_e ePlayVolumeLevel;
    boolean             bSuspendWndClose;   //T: wnd closed by suspend, F: wnd closed normally 
} ProfileAppVolume_t;

typedef struct
{
    IWidget             *pIMenuWdg;
} ProfileAppVoiceCalls_t;

typedef struct
{
    IWidget             *pIMenuWdg;
} ProfileAppMessaging_t;

typedef struct
{
    IWidget             *pIMenuWdg;
} ProfileAppCalendar_t;

typedef struct
{
    IWidget             *pIMenuWdg;
} ProfileAppAlarm_t;

#ifdef __USER_DEFINE_POWERONOFF_MELODY__
typedef struct
{
    IWidget             *pIMenuWdg;
} ProfileAppPowerOn_t;

typedef struct
{
    IWidget             *pIMenuWdg;
} ProfileAppPowerOff_t;
#endif

typedef struct
{
    IWidget             *pIMenuWdg;
} ProfileAppLaunchFileMgr_t;

typedef struct
{
    IWidget         *pIMenuWdg;
    MenuItemID_e    eEditMenuItemID;
} ProfileAppVibrateType_t;

typedef struct
{
    IWidget         *pIMenuWdg;
    MenuItemID_e    eEditMenuItemID;
} ProfileAppVoiceCallsRingingType_t;

typedef struct
{
    IWidget         *pIMenuWdg;
    MenuItemID_e    eEditMenuItemID;
} ProfileAppMessageTone_t;

typedef struct
{
    IWidget         *pIMenuWdg;
    MenuItemID_e    eEditMenuItemID;
} ProfileAppCalendarTone_t;

typedef struct
{
    IWidget         *pIMenuWdg;
    MenuItemID_e    eEditMenuItemID;
} ProfileAppAlarmTone_t;

#ifdef __USER_DEFINE_POWERONOFF_MELODY__
typedef struct
{
    IWidget         *pIMenuWdg;
} ProfileAppPowerOnTone_t;

typedef struct
{
    IWidget         *pIMenuWdg;
} ProfileAppPowerOffTone_t;
#endif

typedef struct
{
    APPLET_BASE_ELEMENTS;
    ProfileID_e     eHighlightPrifileID;
    u16             nToneSettingItemID;                 // the item ID of Tone Select Item Id
    u32             u32VoiceCallHighlightIdx;
    boolean         bEnterOtherAp;                      //enter filemgrapp
    boolean         bLogHistory;
    u32             *pSettingValue;
    u32             u32LogFirstItemIndexMainList;
    u32             u32LogHighlightIndexMainList;
    u32             u32LogFirstItemIndexEditList;
    u32             u32LogHighlightIndexEditList;
} ProfileAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret ProfileAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret ProfileAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ProfileAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ProfileAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ProfileAppPhoneLockSuccessCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ProfileAppResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ProfileAppSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/*=============================================================*/
// Local function definition
/*=============================================================*/

MAE_Ret _ProfileAppWndCreateMainList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyMainList(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyOption(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateEditList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#ifdef __POWER_SAVING_PROFILE_MMI__
MAE_Ret _ProfileAppWndPowerSaveInfoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndCreatePowerSaveInfo(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#endif // __POWER_SAVING_PROFILE_MMI__

MAE_Ret _ProfileAppWndDestroyEditList(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateVolume(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyVolume(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateVibrateType(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyVibrateType(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateVoiceCallsRingingType(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyVoiceCallsRingingType(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateMessageTone(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyMessageTone(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateCalendarTone(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyCalendarTone(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateAlarmTone(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyAlarmTone(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateVoiceCalls(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyVoiceCalls(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateMessaging(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyMessaging(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateCalendar(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyCalendar(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreateAlarm(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyAlarm(void *pCusHandle, void *pWndData);
#ifdef __USER_DEFINE_POWERONOFF_MELODY__
MAE_Ret _ProfileAppWndCreatePowerOn(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyPowerOn(void *pCusHandle, void *pWndData);

MAE_Ret _ProfileAppWndCreatePowerOff(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyPowerOff(void *pCusHandle, void *pWndData);
#endif
MAE_Ret _ProfileAppWndCreateFileMgr(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndDestroyFileMgr(void *pCusHandle, void *pWndData);

static void _ProfileAppAccessoryPlugStatusChangeCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

// Key Press
void _ProfileAppHandleKeyPressVolume(ProfileAppData_t *pThis, u32 param);

// Phone Lock Success
bool _ProfileAppLaunchPhoneLock(ProfileAppData_t *pThis);

// Resume
void _ProfileAppHandleResumeFileMgr(ProfileAppData_t *pThis, u32 param);

MAE_Ret _ProfileAppWndMainListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndEditListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndVolumeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndVibrateTypeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndVoiceCallsRingingTypeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndMessageToneHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndCalendarToneHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndAlarmToneHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndVoiceCallsHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndMessagingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndCalendarHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __USER_DEFINE_POWERONOFF_MELODY__
MAE_Ret _ProfileAppWndPowerOnHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndPowerOffHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret _ProfileAppWndAlarmHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ProfileAppWndFileMgrHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);


#ifdef __USB_MMI_NON_BLOCKING_USAGE__
static void _ProfileAppUsbStatusChangedCb(void *pApplet, MMI_USB_STATUS_E eUsbStatus);
#endif

#if defined(__APP_MMI_CHECKDISK__)
static void _ProfileAppCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif

// Main List
static void _ProfileAppProfileChangeCB(void *pUserData, ProfileID_e eProfileID);

// Restore Profile
static boolean _ProfileAppRestoreProfileConfirmDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static MAE_Ret _ProfileAppRestoreProfileConfirmDialog(ProfileAppData_t *pThis);

// Volume
static void _ProfileAppVolumeViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nCurrentLevel,IWidget *pWidget);
static void _ProfileAppVolumeViewInterruptCb(void *pUserData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);

u32 _ProfileAppGetRingToneText(u32 nMenuId, u32 nItemId);
u32 _ProfileAppGetRingToneLine2Text(ProfileAppData_t *pThis, u32 nMenuId);

MAE_WChar *_ProfileAppGetToneSettingLine2Text(ProfileAppData_t *pThis, u32 nMenuId, ProfileSettings_t *pProfileSetting);
void _ProfileAppActivateProfile(ProfileAppData_t *pThis, ProfileID_e eProfileID, PFN_DlgHandler pDlgHandler);

static void _ProfileAppOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppOptionMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppMainListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppMainListMenuSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppVibrateTypeSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppVoiceCallsRingingTypeSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppMessageToneSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppCalendarToneSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppAlarmToneSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppVoiceCallsSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppMessagingSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppCalendarSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppAlarmSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __USER_DEFINE_POWERONOFF_MELODY__
static void _ProfileAppPowerOnSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _ProfileAppPowerOffSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
static void _ProfileAppEditListSoftKeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _ProfileAppLaunchFileManager(ProfileAppData_t* pThis, MenuItemId_e eMenuItemID, u32 nSelectedID);
void _ProfileAppFileMgrViewMdlListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _ProfileAppLaunchSecInfoCB(void *pvUserData, MAE_Ret nRspCode, SecurityLaunchRspData_t *psRspData, SecurityLaunchRspDataFreeCb pfnRspDataFreeCb);

void _ProfileAppDeleteMenuItem(IWidget *pMenuWdg, u32 u32MenuId);

#endif /* __MMI_PROFILEAPP_PRIV_H__ */
