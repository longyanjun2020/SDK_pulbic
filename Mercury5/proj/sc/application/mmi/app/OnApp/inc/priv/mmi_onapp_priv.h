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
* @file    mmi_onapp_priv.h
* @version
* @brief   OnApp applet private header file
*
*/

#ifndef __MMI_ONAPP_PRIV_H__
#define __MMI_ONAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_onapp.h"
#include "mmi_baseapplet.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_cfg.h"
#include "mmi_secapp.h"
#include "mmi_secapp_cfg.h"
#include "mmi_sys_cfg.h"
#ifdef __TOUCH_SCREEN_MMI__
//for calibration
#include "mmi_common_rai_id.h"
#include "mmi_calibrationapp.h"
#endif
#include "mmi_onapp_custom.h"
#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"
#include "mmi_wdg_headers.h"

#include "mmi_onapp_id.h"
#include "mmi_onapp_view_id.h"
#include "onapp_resource.h"
#include "sys_sys_bootinit.h" 


/*=============================================================*/
// Extern definition
/*=============================================================*/
#define ONAPP_ANIMATION_FRAME_INTERVAL 100
#define ONAPP_DONT_CARE_TIMER 10000
#define ONAPP_SIMRACK_MAX 16
/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    StepNone = 0,
    StepCheckPowerOnCause,
    StepCheckBattery,
    StepCheckTouchScreenFwUpdate,
    StepCheckCalibration,
    StepShowStandbyMenu,
    StepShowPowerOnAnimation,
    StepCheckSecurity,
    StepCheckSimReady,
    StepCheckOfflineMode,
    StepSearchNetwork,
    StepChargingNoAnimation,
    StepCharging,

} OnAppRunStatus_e;

typedef enum
{
    LaunchNone = 0,
    LaunchCalibration,
    LaunchAlarm,
    LaunchSecurity,
    LaunchOff,
    LaunchIdle,
    LaunchEMTouchScreenFwUpdate,

} OnAppLaunchType_e;

typedef enum
{
    BatteryStatus_Init = 0,
    BatteryStatus_Low,      /* Can't power on handset if battery status is low. */
    BatteryStatus_Normal,   /* Show charing dialog while charing. */
    BatteryStatus_Full,     /* Show battery full dialog while charging. */
    BatteryStatus_Invalid,   /* Show invalid battery dialog. */
    BatteryStatus_OverVoltage,   /* Show over voltage dialog. */
    BatteryStatus_Temperture  /* Show over temperture dialog. */

} BatteryStatus_e;

typedef enum    //When resume from ccapp, onapp needs to know whick stage should be countinued.
{
    OnApp_SIM_Error_ModuleID_None = 0,
    OnApp_SIM_Error_ModuleID_Master,
    OnApp_SIM_Error_ModuleID_Slave,

} OnApp_SIM_Error_ModuleID_e;

typedef enum    //When resume from ccapp, onapp needs to know whick stage should be countinued.
{
    OnApp_Resume_To_Normal = 0, /* do not care */
    OnApp_Resume_To_Security,   /* To check security */
    OnApp_Resume_To_Idle,       /* To start Idle */

} OnApp_Resume_To_e;

typedef enum
{
    SearchNetworkStatus_None = 0,     /* Not search network yet. */
    SearchNetworkStatus_Searching,    /* Network is searching, not response yet. */
    SearchNetworkStatus_Attached,     /* Network is already attached. */
    SearchNetworkStatus_Fail,         /* Fail to attach network. */

} SearchNetworkStatus_e;

typedef enum    //When resume from ccapp, onapp needs to know whick stage should be countinued.
{
    VerifyNull = 0,
    VerifySlave,
#ifdef __ANTI_STEAL_MMI__
    VerifyAntiSteal,
#endif
    VerifyEnd,
} OnAppVerify_e;

#ifdef __QUAD_SIM_DUAL_STANDBY__

typedef enum
{
    E_ACT_NONE = 0,
    E_ACT_SIM1RACK1,
    E_ACT_SIM1RACK2,
    E_ACT_SIM2RACK3,
    E_ACT_SIM2RACK4,
    E_SHOW_SIM1MENU,
    E_SHOW_SIM2MENU,
    E_SHOW_SIM1SIM2MENU,
} OnAppStandbyAction_e;

#endif

enum //VID_OFFAPP_SWITCHDUALMODE_enum
{
    WID_STANDBY_MENU=0x1100,
}; //VID_OFFAPP_SWITCHDUALMODE_enum

#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
typedef struct
{
    IWidget *pOsdWdg;
    IWidget *pImg;
    IWidget *pMainAbsContainer;
} VideoWndWdgList_t;

typedef struct
{
    VideoWndWdgList_t tWdgList;
    MAE_WChar   *stImageURL;
} PowerOnVideoWndData_t;

typedef enum
{
    ON_VIDEO_STOP_CAUSE_NONE,
    ON_VIDEO_STOP_CAUSE_HOTPLUG,
    ON_VIDEO_STOP_CAUSE_LAUNCHOFF,
    ON_VIDEO_STOP_CAUSE_PLAYEND,
    ON_VIDEO_STOP_CAUSE_MAX,
}OnVideoStopCause_e;

#endif // __USER_DEFINE_POWERONOFF_VIDEO__

typedef struct OnAppData_t_
{
    APPLET_BASE_ELEMENTS;

    HistoryInfo_t       MenuHistory;    //menu history for emergency call list.

    OnAppRunStatus_e    OnAppRunStep;
    OnAppLaunchType_e   LaunchType;
    OnAppVerify_e       NeedToVerifyNext;   //check if need to verify security of Slave SIM;

	bool bMSIMError; //Mastar SIM Error
	bool bSSIMError; //Slave SIM Error

    OnAppStart_t        OnAppStart; //store start type and alarm event code.
    BatteryStatus_e     eBatteryStatus;     //store battery status for charging usage.
    MAEChargingStatus_e eChargingStatus;    //check charging status;
    boolean             bPrechargOn;            //store precharg status.

    boolean             bInterruptByCCApp;      //check if interrupted by CCapp;
    OnApp_Resume_To_e   eResumeTo;  //To know which stage of power on procedure should be countinued when resume from ccapp;

    SearchNetworkStatus_e  eSearchNetworkStatus;  //store searching network status. Search network process might be done before entering SearchNetwork Mode.
    boolean bNeedCalibration;   //check if need to do calibration;
    boolean bPowerOnWhenCharging; //store whether if user long presses END key to power on handset while charing state and battery is low.
    boolean bNeedTouchScreenFwUpdate;   //check if need to do TouchScreenFwUpdate;
#ifdef __DUAL_BATT_MMI__
    boolean bBat1IsFull;
    boolean bBat2IsFull;
#endif

#ifdef __ONAPP_POWERON_ANIM_DONT_WAIT_MELODY__
	boolean bLaunchSecApp;
#endif
	boolean bSkipShutdownIfBreakCharging;
	boolean bChargerPlugged;
#if defined(__APP_MMI_CHECKDISK__)
	boolean	bCheckDisk;	//Check if need to do Check Disk
#endif

#ifdef __QUAD_SIM_DUAL_STANDBY__
    OnAppStandbyAction_e eStandbyAction;
    SIMSRV_SIM_INSERT_NEW_e eaAllRackInsertedStaus[SIMSRV_SIMRACK_MAX];
    SIMSRV_SIM_RACK_ID_e eSim1Rack;
    SIMSRV_SIM_RACK_ID_e eSim2Rack;
    u8 nSim1InsertedRack;
    u8 nSim2InsertedRack;
    u8 nCurSimStandbyMenu;
    boolean bSim1Disabled;
#endif
    boolean     bMusicEnd;
    boolean     bDefaultAnim;
#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
    OnVideoStopCause_e eVideoStop;
#endif

} OnAppData_t;

typedef struct
{
    u32 nCurrentAnimImgID;
    IWidget     *pImg;  //WID_ONAPP_POWERONANIM_IMAGE
    IWidget     *pPropCntr; //WID_ONAPP_POWERONANIM_CONTAINER
    MAE_WChar   *stImageURL;
    MAE_WChar   *stRingerURL;
    IImage      *pIPowerOnImage;
} PowerOnAnimationWndData_t;

#ifdef __DUAL_LCD__
typedef struct
{
    u32 nCurrentAnimIdx; // Current index of image in power-on animation image table
    ImageVtmWdgList_t tWdgList;
    MAE_WChar   *stImageURL;
    MAE_WChar   *stRingerURL;
} PowerOnAnimationSubWndData_t;
#endif // __DUAL_LCD__

#ifdef __DUAL_BATT_MMI__
typedef struct
{
    IWidget *pBat1ImgWdg;
    IWidget *pBat2ImgWdg;
    IWidget *pId1ImgWdg;
    IWidget *pId2ImgWdg;
    IWidget *pBgImgWdg;
} DualBatWndWdgList_t;

typedef struct
{
    DualBatWndWdgList_t tWdgList;

} DualBatChargingWndData_t;

typedef struct
{
    IWidget *pBatImgWdg;
    IWidget *pIdImgWdg;
    IWidget *pBgImgWdg;
} DualBatSingleWndWdgList_t;

typedef struct
{
    DualBatSingleWndWdgList_t tWdgList;

} DualBatSingleChargingWndData_t;

#endif
/*=============================================================*/
// Global function definition
/*=============================================================*/
__ONCE_CALL_ON_BOOT__ MAE_Ret OnAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret OnAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
__ONCE_CALL_ON_BOOT__ boolean OnAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean OnAppStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
__ONCE_CALL_ON_BOOT__ boolean OnAppKeyPress(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
__ONCE_CALL_ON_BOOT__ boolean OnAppKeyLongPess(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean OnAppSuspend(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
__ONCE_CALL_ON_BOOT__ boolean OnAppResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

//Window manager related function
MAE_Ret OnAppWndLogoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppWndPowerOnAnimHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppWndStandbyHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppWndSearchNetworkHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppWndChargingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppChargerFullHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#ifdef __DUAL_LCD__
MAE_Ret OnAppSubWndLogoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppSubWndPowerOnAnimHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppSubWndSearchNetworkHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppSubWndChargingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppSubChargerFullHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

#ifdef __DUAL_BATT_MMI__
MAE_Ret OnAppWndDualBatChargerHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret OnAppWndDualBatSingleChargerHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

#ifdef __QUAD_SIM_DUAL_STANDBY__
MAE_Ret OnAppWndSimStandbyHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
MAE_Ret OnAppWndPowerOnVideoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

#endif /* __MMI_ONAPP_PRIV_H__ */
