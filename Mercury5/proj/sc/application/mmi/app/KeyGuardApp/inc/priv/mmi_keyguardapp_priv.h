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

#ifndef __MMI_KEYGUARDAPP_PRIV_H__
#define __MMI_KEYGUARDAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_keyguardapp.h"
#include "mmi_common_inttbl.h"
#include "mmi_common_dialog.h"

#include "mmi_srv_header.h"
#include "mmi_launcher_cc.h"
#include "mmi_keyguardapp_id.h"
#include "keyguardapp_resource.h"

#ifdef __3D_UI_KEYGUARD__
#include "mae_image_priv.h"
#include "mae_animation.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define KEYGUARDAPP_STAGE_CHANGE_TIMER	2000
#define KEYGUARDAPP_EM_TERM	L"\n"

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    IWidget *pBGWdg;
    IWidget *pUnlockWdg;
    IWidget *pDarkWdg;
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
#ifdef __DUAL_SIM_MMI__
    IWidget *pMissCallSlaveWdg;
    IWidget *pMissCallSlaveTextWdg;
#endif

#ifdef __3D_UI_KEYGUARD__
    IWidget *pSlideTextWdg;
    IWidget *pEMNum1Wdg;
    IWidget *pEMNum2Wdg;
    IWidget *pEMNum3Wdg;
    IWidget *pClothEffectWdg;
    IWidget *pOtherCntr;
    IWidget *pTitleCntr;
    IWidget *pEMNumCntr;
    IWidget *pEMNumBGWdg;
    IWidget *pBottomBGWdg;
    IWidget *pAnimImgWdg;
#endif
}KeyGuardWndWdgList_t;

typedef struct
{
    KeyGuardWndWdgList_t tWdgList;

    u8 pEmergencyQueue[COMMON_MAX_ECC_LEN];
	boolean	bKeyGuardUnlock;
	boolean	bSOSEnabled;
	boolean	bEmergencyNum;
	boolean bDialogTriggeredByEventCenter;

	u32 nNewMsgEvt;
	u32 nMissedCallEvt;
#ifdef __DUAL_SIM_MMI__
	u32 nMissedCallSlaveEvt;
#endif
	u32	nAlarmUserCode;
	u32	nEvtCenterUserCode;
} KeyGuardWndData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    MAE_WChar *pstrMediaName;
    WidgetHandler_t UnlockWdgHandler;

    COMMON_TotalEccList_t tTotalEccList;
    SetKeyGuardType_e nKeyGuardType;
    boolean bShowMediaName;
    boolean bInitFail;

#ifdef __3D_UI_KEYGUARD__
    boolean	bBeautyClock;
    IAnimation *pAnimation;
    IImage *pImage;
    IWidget *pStatusPageWidget;
    boolean bToShowStatusPageAfterResume;
	boolean bShowAirplanceModeWaitingDlg;
    boolean bExecuteEffect;
    boolean bSwitchAnimEnable;
    boolean bIsSuspend;
    boolean bDecodeFail;
    Pos_t tCurrentSwitchPos;
	MAE_DateTime_t sTime;
	MAE_DateTime_t sShowTime;
    boolean bIsReceiveKeypadFromCoreSrv;
#endif

} KeyGuardAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret KeyGuardConstructor(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret KeyGuardDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean KeyGuardStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean KeyGuardStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean KeyGuardResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean KeyGuardSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean KeyGuardGetProperty(IApplet *pApplet, u32 nEvt, u32 key, u32 outVal);
boolean KeyGuardKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean KeyGuardDrawCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret KeyGuardWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifndef __3D_UI_KEYGUARD__
MAE_Ret KeyGuardWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret KeyGuardWndDestroyMain(void *pCusHandle, void *pWndData);
#ifndef __3D_UI_KEYGUARD__
MAE_Ret KeyGuardWndSetMain(void *pCusHandle, void *pWndData);
#endif
void KeyGuardStageChangeTimerCb(void *pUserData);
MAE_Ret KeyGuardDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void KeyGuardNewMessageNumCb(void *pApplet,  u16 nNewMsgNum);
void KeyGuardMissedCallNumCb(void *pApplet,  u16 nMissedCallNum);
void KeyGuardNewAlarmIdCb(void *pApplet, u32 nAlarmUserCode1, u32 nAlarmUserCode2);
void KeyGuardStartDialogNotifyCb(void *pApplet, EvtCenter_Dialog_Type_e eDialogType, u32 nMsgId);
void KeyGuardPlayMediaStatusCb(void *pApplet, SrvAudioPlayerPlayStatus_e ePlayStatus);
void KeyGuardPlayingMediaNameCb(void *pUserData, MAE_WChar *pMediaName);
void KeyGuardNetworkRegIndCb(void *pUserData, MMI_MMSRV_RegStat_e eState, MAE_DualMode_t eDualMode);
#ifdef __GPRS_MMI__
void KeyGuardGPRSRegStatusIndCb(void *pUserData, MMSRV_GPRSRegInd_t *pData, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
#if (defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)) && !defined(__3D_UI_KEYGUARD__)  // gadgetbar only desktop widgets
void KeyGuardNonSingletonCountDownCb(void *pUserData, AliveWidget_InputEvent_e eEvtType);
#endif // #if (defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)) && !defined(__3D_UI_KEYGUARD__)
void KeyGuardCountDownTimerStateChangeCB(void *pUserData, CountDownTimerSrv_State_e eState);
void KeyGuardUSBStatusIndCb(void* pUserData, MMI_USB_STATUS_E eUSBStatus);
void KeyGuardDateTickCb(void *pUserData);
void KeyGuardMinuteTickCb(void *pUserData);
static MAE_Ret _KeyGuardSetTimeWidget(IBase *pThis, IWidget *pTimeWidget, IWidget *p12HWidget, COMMON_Time_Type_e nType);
#ifndef __APP_MMI_SMALLROM__
static MAE_Ret _KeyGuardSetTimeStrToGridWidget(IBase *pThis, IWidget *pTimeWidget, MAE_WChar *pstrTime);
#endif

#ifdef KEYGUARD_ENABLE_READSIMFILE
void KeyGuardSIMReadSIMFileCnfCb(void *pUserData, SIMSRV_FileReadCnf_t *tFileReadCnf, SIMSRV_SIM_ID_e eSIMID);
#endif
void KeyGuardCloseDialogInfoTimerCb(void *pData);

#ifdef __TOUCH_SCREEN_MMI__
void KeyGuardSlideCompleteCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
#endif

#ifdef __HALL_SWITCH_MMI__
void KeyGuardCloseAppletTimerCB(void* pUserData);
#endif

void KeyGuardAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

#ifdef __3D_UI_KEYGUARD_BEAUTY_CLK__
MAE_Ret  KeyGuardWndCreateBeautyClkMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret  KeyGuardWndSetBeautyClkMain(void *pCusHandle, void *pWndData);
boolean KeyGuardTouchCb(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
#endif

#ifdef __3D_UI_KEYGUARD_GLOW__
MAE_Ret  KeyGuardWndCreateGlowMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret  KeyGuardWndSetGlowMain(void *pCusHandle, void *pWndData);
#endif

#endif /* __MMI_KEYGUARDAPP_PRIV_H__ */
