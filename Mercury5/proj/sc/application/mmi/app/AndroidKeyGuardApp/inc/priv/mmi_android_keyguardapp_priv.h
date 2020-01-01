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
* @file    mmi_keyguardapp_priv.h
* @version
* @brief   KeyGuard applet private header file
*
*/
#ifdef __UI_STYLE_MMI_ANDROID_KEYGUARD__

#ifndef __MMI_KEYGUARDAPP_PRIV_H__
#define __MMI_KEYGUARDAPP_PRIV_H__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_android_keyguardapp.h"
#include "mmi_common_inttbl.h"
#include "mmi_common_dialog.h"

#include "mmi_srv_header.h"
#include "mmi_wdg_keyguard_type.h"
#include "mmi_launcher_cc.h"
#include "mmi_android_keyguardapp_id.h"
#include "AndroidKeyGuardApp_resource.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define ANDROID_KEYGUARDAPP_STAGE_CHANGE_TIMER	2000
#define ANDROID_KEYGUARDAPP_EM_TERM	L"\n"

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    IWidget *pBGWdg;
    IWidget *pUnlockWdg;
#ifndef __UI_STYLE_MMI_ANDROID_4_0__
    IWidget *pDarkWdg;
#endif // __UI_STYLE_MMI_ANDROID_4_0__
    IWidget *pEMNumWdg;
    IWidget *pIdleInfoCntr;
    IWidget *pTimeWdg;
    IWidget *pI12HWdg;
    IWidget *pDateWdg;
    IWidget *pMediaNameWdg;
    IWidget *pCountdownWdg;
    IWidget *pNetworkWdg;
#ifdef __DUAL_SIM_MMI__
    IWidget *pNetworkSlaveWdg;
#endif
    //--Dialog info widget
    IWidget *pDialogInfoBGWdg;
    IWidget *pDialogInfoTextWdg;
    //--New message widget
    IWidget *pNewMsgWdg;
    IWidget *pNewMsgTextWdg;
    //--Miss call widget
    IWidget *pMissCallWdg;
    IWidget *pMissCallTextWdg;
#ifndef __UI_STYLE_MMI_ANDROID_4_0__
    IWidget *pAndroidUnlockCntr;
    IWidget *pUpBgImgWdg;
    IWidget *pLockTxtWdg;
    IWidget *pLockIconWdg;
    IWidget *pDownBgWdg;
    IWidget *pDownUnlockTxtWdg;
    IWidget *pLeftAnimWdg;
    IWidget *pRightAnimWdg;
#endif // !__UI_STYLE_MMI_ANDROID_4_0__
}AndroidKeyGuardWndWdgList_t;

typedef struct
{
    AndroidKeyGuardWndWdgList_t tWdgList;

    u8 pEmergencyQueue[COMMON_MAX_ECC_LEN];
	boolean	bKeyGuardUnlock;
	boolean	bSOSEnabled;
	boolean	bEmergencyNum;
	boolean bDialogTriggeredByEventCenter;

	u32 nNewMsgEvt;
	u32 nMissedCallEvt;

	u32	nAlarmUserCode;
	u32	nEvtCenterUserCode;
} AndroidKeyGuardWndData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    MAE_WChar *pstrMediaName;
	WidgetHandler_t UnlockCntrHandler;
	WidgetHandler_t UnlockWdgHandler;

    COMMON_TotalEccList_t tTotalEccList;
    SetKeyGuardType_e nKeyGuardType;
    boolean bShowMediaName;

#if defined(__G3D_MMI__)
    u8  u8wallpaperIdx;
    u8  u8CubeFocusIdx;
#endif

    s32 sTouchPressPos;
    s32 sUnlockCntPressPos;
    s32 sAutobackLength;
    boolean bIsAutoback;
    boolean bIsFadeIn;
    IBitmap *pDownTxtBitmap;
    IBitmap *pDownBgBitmap;
    u32 nMaskVal;

    ITouchSrv          *pITouchSrv;			///< Touch service
    boolean bInitFail;
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
    u32 nReserve;
    boolean bIsSlideCompleteExitCbExist;
#endif
} AndroidKeyGuardAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret AndroidKeyGuardConstructor(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret AndroidKeyGuardDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidKeyGuardStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidKeyGuardStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidKeyGuardResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidKeyGuardSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidKeyGuardKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidKeyGuardDrawCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidUnlockCntrTSPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidUnlockCntrTSMoveCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AndroidUnlockCntrTSReleaseCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static MAE_Ret _AndroidKeyguardMoveByFinger(AndroidKeyGuardAppData_t *pThis, u32 nEvt);
void _AndroidKeyguardAutoBackCb(AndroidKeyGuardAppData_t *pThis);
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
static void _KeyGaurdAppFlushApStackCB(IBASE *pApplet, u32 nResult);
#else // __UI_STYLE_MMI_ANDROID_4_0__
void _AndroidKeyguardInVisiableWdgCb(AndroidKeyGuardAppData_t *pThis);
void _AndroidKeyguardDownBgFadeIn(AndroidKeyGuardAppData_t *pThis);
#endif // __UI_STYLE_MMI_ANDROID_4_0__
void AndroidKeyguardSetAlplaValue(IBitmap *pBitmap,u32 nMaskVal);
MAE_Ret AndroidKeyGuardWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AndroidKeyGuardWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret AndroidKeyGuardWndDestroyMain(void *pCusHandle, void *pWndData);
MAE_Ret AndroidKeyGuardWndSetMain(void *pCusHandle, void *pWndData);
void AndroidKeyGuardStageChangeTimerCb(void *pUserData);
MAE_Ret AndroidKeyGuardDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void AndroidKeyGuardNewMessageNumCb(void *pApplet,  u16 nNewMsgNum);
void AndroidKeyGuardMissedCallNumCb(void *pApplet,  u16 nMissedCallNum);
void AndroidKeyGuardNewAlarmIdCb(void *pApplet, u32 nAlarmUserCode1, u32 nAlarmUserCode2);
void AndroidKeyGuardStartDialogNotifyCb(void *pApplet, EvtCenter_Dialog_Type_e eDialogType, u32 nMsgId);
void AndroidKeyGuardPlayMediaStatusCb(void *pApplet, SrvAudioPlayerPlayStatus_e ePlayStatus);
void AndroidKeyGuardPlayingMediaNameCb(void *pUserData, MAE_WChar *pMediaName);
void AndroidKeyGuardNetworkRegIndCb(void *pUserData, MMI_MMSRV_RegStat_e eState, MAE_DualMode_t eDualMode);
void AndroidKeyGuardGPRSRegStatusIndCb(void *pUserData, MMSRV_GPRSRegInd_t *pData, MAE_DualMode_t eDualMode);
void AndroidKeyGuardCountDownTimerStateChangeCB(void *pUserData, CountDownTimerSrv_State_e eState);
void AndroidKeyGuardUSBStatusIndCb(void* pUserData, MMI_USB_STATUS_E eUSBStatus);

void AndroidKeyGuardDateTickCb(void *pUserData);
void AndroidKeyGuardMinuteTickCb(void *pUserData);
static MAE_Ret _AndroidKeyGuardSetTimeWidget(IBase *pThis, IWidget *pTimeWidget, IWidget *p12HWidget, COMMON_Time_Type_e nType);
static MAE_Ret _AndroidKeyGuardSetTimeStrToGridWidget(IBase *pThis, IWidget *pTimeWidget, MAE_WChar *pstrTime);
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
static MAE_Ret _AndroidKeyGuardSetEmNumStrToGridWidget(IBase *pThis, IWidget *pEmNumWidget, MAE_WChar *pstrNum);
#endif // !__UI_STYLE_MMI_ANDROID_4_0__
void AndroidKeyguardBacklightOnOffCB(void *pUserData, boolean bBackLightOn);

#ifdef KEYGUARD_ENABLE_READSIMFILE
void AndroidKeyGuardSIMReadSIMFileCnfCb(void *pUserData, SIMSRV_FileReadCnf_t *tFileReadCnf, SIMSRV_SIM_ID_e eSIMID);
#endif
void AndroidKeyGuardCloseDialogInfoTimerCb(void *pData);

#ifdef __TOUCH_SCREEN_MMI__
void AndroidKeyGuardSlideCompleteCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
#endif

#ifdef __HALL_SWITCH_MMI__
void AndroidKeyGuardAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
#endif

#ifdef __UI_STYLE_MMI_ANDROID_4_0__
static boolean _BallSlideWdgHandleEvent(void *pUserData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#else // __UI_STYLE_MMI_ANDROID_4_0__
static boolean _AndroidUnlockCntrHandleEvent(void *pUserData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif // __UI_STYLE_MMI_ANDROID_4_0__

#endif /*__UI_STYLE_MMI_ANDROID_KEYGUARD__*/
#endif /* __MMI_KEYGUARDAPP_PRIV_H__ */
