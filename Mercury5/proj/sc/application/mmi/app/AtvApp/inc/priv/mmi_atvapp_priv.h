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
* @file    mmi_atvapp_priv.h
* @version
* @brief   ATV applet private header file
*
*/

#ifndef __MMI_ATVAPP_PRIV_H__
#define __MMI_ATVAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"

#include "mmi_atvapp.h"
#include "mmi_atvapp_esgparser.h"

#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"

#include "mmi_atvapp_id.h"
#include "AtvApp_resource.h"
#include "mmi_atvapp_rs.h"

#include "mmi_common_window.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define ATVAPP_IEVT_MAIN_MENU               (CLSID_ATVAPP << 16 | 1)
#define ATVAPP_IEVT_POWER_ON                (CLSID_ATVAPP << 16 | 2)
#define ATVAPP_IEVT_WATCH                   (CLSID_ATVAPP << 16 | 3)
#define ATVAPP_IEVT_CAPTURE                 (CLSID_ATVAPP << 16 | 4)
#define ATVAPP_IEVT_SEARCH_CHANNEL          (CLSID_ATVAPP << 16 | 5)
#define ATVAPP_IEVT_POWER_OFF               (CLSID_ATVAPP << 16 | 6)
#define ATVAPP_IEVT_LIST_CHANNEL            (CLSID_ATVAPP << 16 | 7)
#define ATVAPP_IEVT_EDIT_CHANNEL            (CLSID_ATVAPP << 16 | 8)
#define ATVAPP_IEVT_VIEW_PICTURES           (CLSID_ATVAPP << 16 | 9)
#define ATVAPP_IEVT_SET_AREA                (CLSID_ATVAPP << 16 | 10)
#define ATVAPP_IEVT_SET_RATIO               (CLSID_ATVAPP << 16 | 11)
#define ATVAPP_IEVT_SHOW_NOTICE             (CLSID_ATVAPP << 16 | 12)
#define ATVAPP_IEVT_SUSPEND                 (CLSID_ATVAPP << 16 | 13)
#define ATVAPP_IEVT_EXIT                    (CLSID_ATVAPP << 16 | 14)
#define ATVAPP_IEVT_STOP_WATCH              (CLSID_ATVAPP << 16 | 15)
#define ATVAPP_IEVT_SETCONFIG               (CLSID_ATVAPP << 16 | 16)
#define ATVAPP_IEVT_GETINFO                 (CLSID_ATVAPP << 16 | 17)
#define ATVAPP_IEVT_SWITCH_CHANNEL          (CLSID_ATVAPP << 16 | 18)
#define ATVAPP_IEVT_RESOURCE_ACQUIRED       (CLSID_ATVAPP << 16 | 19)
#define ATVAPP_IEVT_RESOURCE_WAIT_RESUME    (CLSID_ATVAPP << 16 | 20)
#define ATVAPP_IEVT_SELECT_STORAGE          (CLSID_ATVAPP << 16 | 21)

#ifndef __ATVAPP_SMALLROM__
#define ATV_STORAGE_CONFIG_ITEM             CFGIT_ATV_STORAGE_CONFIG
#endif // !__ATVAPP_SMALLROM__

#define ATV_COLOR_CHANNEL_NAME_TEXT         COLOR_WHITE

/*=============================================================*/
// Data type definition
/*=============================================================*/

#ifdef __ATV_CMMB__
typedef struct
{
	u8 nDataType;
	u8 *pGzBuffer;
	u32 nGzBufferLen;
} EsgGzBuffer_t;

typedef struct
{
	u16 nGzBufferCount;
	EsgGzBuffer_t *pGzBuffers;
} EsgGzBufferList_t;

typedef struct
{
	u16 nServiceId;
	u8 timeslot[MMI_ATVAPP_TIME_SLOT_LENGTH];
} AtvServiceIdTimeslotTbl_t;

typedef struct Program_t {
    u8  mfID;
    u8  msfID;
    u16 serviceID;
    u8  encrypted;
} AtvProgram;

typedef struct AtvAppCmctSmct_t {
    s8   m_timeslot[ATVAPP_MAX_TIMESLOTNUM]; // to notify the time slot of selected channel
    s8   m_frameNum;
    u8  available;
} AtvAppCmctSmct;

typedef struct AtvAppProgramID_t {
    AtvProgram prog[ATVAPP_MAX_PROGRAM_NUM];
    u8 total_program;
} AtvAppProgramID;

typedef struct
{
    u16 uEmmid;
    u8  nEmmTimeslot[MMI_ATVAPP_TIME_SLOT_LENGTH];
}AtvAppCatInfo;
#endif

typedef struct
{
    IWidget *pOsdWdg;
    IWidget *pWaitingImgWdg;
    IWidget *pSignalImgWdg;
    IWidget *pChannelNameTextWdg;
#ifdef __ATVAPP_SMALLROM__
    IWidget *pStatusAbsCntr;
    IWidget *pStatusAbsBGBtnWdg;
#else
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
    IWidget *pBatteryImgWdg;
#endif
    IWidget *pVolumeAbsCntr;
#endif
    IWidget *pAdjustBGVolumeImgWdg;
    IWidget *pAdjustLevelVolumeImgWdg;
    IWidget *pControlAbsCntr;
    IWidget *pAbsBGBtnWdg;
#ifdef __ATVAPP_SMALLROM__
    IWidget *pReturnWdg;
#else
    IWidget *pPowerOffBGBtnWdg;
#endif
    IWidget *pVolumeIncBtnWdg;
    IWidget *pVolumeDecBtnWdg;
#ifndef __ATVAPP_SMALLROM__
    IWidget *pCaptureBtnWdg;
#endif // !__ATVAPP_SMALLROM__
    IWidget *pChannelPreBtnWdg;
    IWidget *pChannelNextBtnWdg;
    IWidget *pScreenRatioBtnWdg;
}AtvWatchWdgList_t;

typedef struct
{
    IWidget *pCapturePicImgWdg;
    IWidget *pPreviewIconImgWdg;
}AtvCaptureWdgList_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    boolean		bIsLandscapeScreen;

    boolean		bIsAirplaneMode;
    boolean		bIsBTOn;

    MAEEvent_t  postEvent;
    MAEEvent_t  sourceEvent;
    boolean		bIsNeedAutoSearch;
    boolean		bIsPowerOff;
    boolean		bIsStop;
    boolean		bIsApSuspend;
    boolean		bIsResourceSuspend;
    boolean		bIsCaptured;

    u16			u16MainMenuSelectIndex;

    boolean		bIsWatchRunning;
#ifdef __ATV_CMMB__
    boolean		bIsGotoWatch;
#endif
    boolean		bIsPowerOn;
    boolean		bIsSearchRunning;
    boolean		bIsError;
    u32		    u32SearchIndex;
    TvSrvHybridType_e eHybridType;

    ATVInfo_t		   *ptInfo;
    ATVChannelsInfo_t  *ptChannelsInfo;

    // Widget for Menu View
    u32				u32ListSelectIndex;


    //Widget for Watch View
    IAbsContainer   *pIWatchContainer;
    IWidget         *pWaitingWdg;
    IWidget			*pSignalWdg;
    IWidget			*pChannelNameWdg;
#ifdef __ATVAPP_SMALLROM__
    IAbsContainer   *pIStatusBarContainer;
    IWidget         *pVolumeAdjustBGWdg;
#else
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
    IWidget			*pBatteryWdg;
#endif
#endif
    IAbsContainer   *pIControlBarContainer;
#ifndef __ATVAPP_SMALLROM__
    IAbsContainer   *pIVolumeBarContainer;
#endif
    IWidget		    *pVolumeAdjustWdg;
    IWidget		    *pRatioButtonWdg;
    IWidget		    *pIncVolumeAdjustWdg;
    IWidget		    *pDecVolumeAdjustWdg;
    IWidget			*pPreviousButtonWdg;
    IWidget			*pNextButtonWdg;
#ifndef __ATVAPP_SMALLROM__
    IWidget			*pCaptureButtonWdg;
#endif // !__ATVAPP_SMALLROM__
#ifdef __ATVAPP_SMALLROM__
    IWidget			*pReturnWdg;
#else
    IWidget			*pPowerOffBGBtnWdg;
#endif
    IWidget 		*pOsdWdg;

    boolean		bIsShowControlBar;
    u16			u16ControlBarCounter;
    boolean		bIsShowStatus;
    boolean		bIsFirstShowStatus;
    u16			u16StatusCounter;
    boolean		bIsShowVolumeBar;
    u16			u16VolumeBarCounter;

    boolean        bIsWaitCnf;

#if defined(__MMI_BATTERY_ICON_DISPLAY__) && !defined(__ATVAPP_SMALLROM__)
    MAEBatteryLevel_e     u8AtvMasterBatteryLevel;
    MAEChargerStatus_e  u8AtvMasterBatteryStatus;
    MAEBatteryLevel_e     u8AtvSlaveBatteryLevel;
    MAEChargerStatus_e  u8AtvSlaveBatteryStatus;
    MAEBatteryID_e        u8AtvActiveBatteryID;
#endif
    u8				  u8SingalLv;

    //Capture

    MAE_WChar		*ppFileName;

    //Edit Channel name
    IWidget         *pIEditInputWidget;
    //Search channel
    IWidget			*pProgressWidget;

    TvSrvConfig_t    tTvSetting;
    TvSrvShutterSoundSetting_t pSoundSetting;
    boolean          bIsPower;
    u32              u32MsgId;
    boolean          bIsSearchFinish;
    boolean		     bIsSearchCancel;
#ifndef __ATVAPP_SMALLROM__
    boolean          bCardPlugIn;
#ifdef __DUAL_CARD__
    boolean          bCard2PlugIn;
#endif //__DUAL_CARD__
#endif //!__ATVAPP_SMALLROM__
#ifdef __ATV_CMMB__
    EsgServiceList_t		*pServiceList;			// ESG parser result of Service
    EsgServiceAuxList_t	*pServiceAuxList;		// ESG parser result of ServiceAux
    EsgScheduleList_t		*pScheduleList;			// ESG parser result of Schedule
    EsgContentList_t		*pContentList;			// ESG parser result of Content
    EsgServiceParaList_t	*pServiceParaList;		// ESG parser result of ServicePara
    EsgScheduleList_t		*pScheduleAllList;			// ESG parser result of Schedule
    EsgGzBufferList_t   tEsgGzBufferList;
    u8                     *pCat;
    u32                    nCatSize;
    u8                       *pEsg;
    u32                      nEsgSize;
    u8                       *pCaCardNumber;
    u32                    nCaCardNumberSize;
    AtvServiceIdTimeslotTbl_t nServiceIdTimeslotTbl[ATVAPP_MAX_PROGRAM_NUM];
    u16         uServiceIdNum;
    u16         uEmmServiceId;
    u8          nEmmTimeslot[MMI_ATVAPP_TIME_SLOT_LENGTH];
    boolean     bHasPaseEsgDataBuffer;
#endif //__ATV_CMMB_
    boolean         bReadyDestruct;
    boolean         bIsBTTurningOff;
    boolean         bIsSessionOpen;
#ifndef __ATVAPP_SMALLROM__
    boolean         bFailtoShowPic;
#endif
} AtvAppData_t;

typedef struct
{
	MenuWdgList_t tWdgList;
} AtvMainMenuWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
} AtvChannelListWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
} AtvAreaWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
} AtvRatioWndData_t;

typedef struct
{
    OptionMenuWdgList_t tWdgList;
} AtvChannelListOptionWndData_t;
/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret AtvConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret AtvDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AtvStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AtvStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AtvSuspendCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean AtvResumeCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean AtvKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AtvTSPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#if defined(__MMI_BATTERY_ICON_DISPLAY__) && !defined(__ATVAPP_SMALLROM__)
void AtvSrvBatteryBattLevelChangeCb(void *pUserData, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
void AtvSrvBatteryChargingStatusChangeCb(void *pUserData, MAEChargingStatus_e eChargingStatus, MAEBatteryID_e eBatID);
#endif
void AtvSrvCfgItemUpdateIndCB(void *pUserData, SrvCfgItemStatusChangeType_e IndType, SrvCfgItemUpdateResult_t tresult);
void AtvMainMenuMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvMainMenuMenuBackCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvChannelListMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvChannelListMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void AtvChannelListMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvChannelListMenuBackCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvAreaMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvRatioMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvMenuBackCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvCreateChannelListOptionMenuLayer1SoftkeyCancelCb (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void AtvPowerOnOpenSrvCommonCb(void *pUserData, u32 nRetCode);
void AtvPowerOnSetRegionSrvCommonCb(void *pUserData, u32 nRetCode);
#ifndef __ATVAPP_SMALLROM__
void AtvSrvCaptureNotifyCb(void *pUserData, TvSrvCaptureNotifyCbDataEx_t *pCaptureNotifyCbData);
#endif // !__ATVAPP_SMALLROM__
void AtvSearchWatchSrvCommonCb(void *pUserData, u32 nRetCode);
#ifdef __ATV_CMMB__
void AtvSearchSrvSignalLevelCb(void *pUserData, u32 nRetCode, TvSrvCmmbTvInfo_t *pCmmbTvInfo);
#else
void AtvSearchSrvSignalLevelCb(void *pUserData, u32 nRetCode, TvSrvSignalLevel_t *pSignal);
#endif
void AtvSearchSrvChannelInfoCb(void *pThis, u32 nRetCode, TvSrvChannelInfo_t *pChInfo);
void AtvStopWatchStopSrvCommonCb(void *pUserData, u32 nRetCode);
void AtvPowerOffCloseSrvCommonCb(void *pUserData, u32 nRetCode);
void AtvWatchWatchSrvCommonCb(void *pUserData, u32 nRetCode);
#ifdef __ATV_CMMB__
void AtvWatchSrvSignalLevelCb(void *pUserData, u32 nRetCode, TvSrvCmmbTvInfo_t *pCmmbTvInfo);
#else
void AtvWatchSrvSignalLevelCb(void *pUserData, u32 nRetCode, TvSrvSignalLevel_t *pSignal);
#endif
void AtvWatchSetChannelSrvCommonCb(void *pUserData, u32 nRetCode);
void AtvWatchSetDisplayParamSrvCommonCb(void *pUserData, u32 nRetCode);
#ifndef __ATVAPP_SMALLROM__
void AtvCaptureCapturePictureSrvCommonCb(void *pUserData, u32 nRetCode);
#endif // !__ATVAPP_SMALLROM__
#ifdef __TOUCH_SCREEN_MMI__
void AtvPowerOffButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,  u32 dwParam,IWidget *pWidget);
void AtvVolumeIncButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,  u32 dwParam,IWidget *pWidget);
void AtvVolumeDecButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,  u32 dwParam,IWidget *pWidget);
#ifndef __ATVAPP_SMALLROM__
void AtvCaptureButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,  u32 dwParam,IWidget *pWidget);
#else //__ATVAPP_SMALLROM__
void AtvReturnButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif // !__ATVAPP_SMALLROM__
void AtvScreenRatioButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,  u32 dwParam,IWidget *pWidget);
void AtvChannelPreButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,  u32 dwParam,IWidget *pWidget);
void AtvChannelNextButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,  u32 dwParam,IWidget *pWidget);
#endif

MAE_Ret AtvConfirmDialogueCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret AtvProgressDialogueCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret AtvInfoDialogueCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

void AtvSrvBtPowerOnOffCB(void *pApplet, BTSRV_StatusCode_e eResult, BTSRV_PowerAction_e eOnOffStatus);
void AtvUSBStatusIndCB(void *pApplet, MMI_USB_STATUS_E eUSBStatus);
#if defined(__APP_MMI_CHECKDISK__)
void AtvCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif
/*=============================================================*/
// Local function definition
/*=============================================================*/
MAE_Ret _AtvMainMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateMainMenuWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _AtvDestroyMainMenuWnd(void* pCusHandle,void* pWndData);
MAE_Ret _AtvWatchWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateWatchWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _AtvDestroyWatchWnd(void* pCusHandle,void* pWndData);
#ifndef __ATVAPP_SMALLROM__
MAE_Ret _AtvCaptureWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateCaptureWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
#endif // !__ATVAPP_SMALLROM__
MAE_Ret _AtvChannelListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateChannelListWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _AtvDestroyChannelListWnd(void* pCusHandle,void* pWndData);
MAE_Ret _AtvChannelListEditWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateChannelListEditWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _AtvAreaWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateAreaWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _AtvDestroyAreaWnd(void* pCusHandle,void* pWndData);
MAE_Ret _AtvRatioWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateRatioWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _AtvDestroyRatioWnd(void* pCusHandle,void* pWndData);
MAE_Ret _AtvChannelListOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AtvCreateChannelListOptionWnd(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _AtvDestroyChannelListOptionWnd(void* pCusHandle,void* pWndData);
static void  _AtvShowDialogueByID(AtvAppData_t* pThis, u32 u32MsgID, u32 u32DialogStyle, boolean bIsLandscape);
static void  _AtvShowDialogue(AtvAppData_t* pThis, MAE_WChar *pMsg, u32 u32DialogStyle, boolean bIsLandscape);
static void _AtvGetAppConflictStr(AtvAppData_t *pThis, u32 nConflictID, u32 nMsgID, MAE_WChar* pOut);
boolean _AtvHandleKeyPressWatch(AtvAppData_t* pThis,u32 nParam);
boolean _AtvHandleKeyPressChannelListEdit(AtvAppData_t* pThis,u32 nParam);
void _AtvPowerOn(AtvAppData_t* pThis);
void _AtvSearchChannel(AtvAppData_t* pThis);
void  _AtvSearchChannelEnd(AtvAppData_t* pThis);
//void _AtvStopWatch(AtvAppData_t* pThis);
void _AtvPowerOff(AtvAppData_t* pThis);
void _AtvPowerOffClose(void* pApplet);
void _AtvPowerOffResume(AtvAppData_t* pThis);
#ifndef __ATVAPP_SMALLROM__
void _AtvCapture(AtvAppData_t* pThis);
MAE_Ret _AtvCreateCaptureView(HWIN hWin, AtvCaptureWdgList_t *pWdgList);
#endif // !__ATVAPP_SMALLROM__
MAE_Ret _AtvCreateWatchView(HWIN hWin, AtvWatchWdgList_t *pWdgList);
//--------------
MAE_Ret _ATVAPP_Init(AtvAppData_t	*pThis );
MAE_Ret _ATVAPP_ReadChannelsInfo(AtvAppData_t *pThis, ATVChannelsInfo_t  **pptChannelsInfo);
void _ATVAPP_CheckFileDir(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_InitFile(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_ReadInfo(AtvAppData_t *pThis, ATVInfo_t  **pptInfo);
boolean _ATVAPP_IsSaveFileExist(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_SetAudioVolume(AtvAppData_t	*pThis,u8 volume , boolean bIsNeedSave);
MAE_Ret _ATVAPP_UpdateVolumeIcon(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_UpdateButtonIcon(AtvAppData_t *pThis,IWidget	*pWdg,u32	u32UnPressID,u32 u32PressID);
void _ATVAPP_ComputeRegion(AtvAppData_t	*pThis,TvSrvRatio_e eLastRatio,TvSrvRotate_e eLastRotate,TvSrvRegion_t *region);
MAE_Ret _ATVAPP_UpdateRatio(AtvAppData_t *pThis,TvSrvRatio_e eRatio);
MAE_Ret _ATVAPP_SaveInfo(AtvAppData_t *pThis, const ATVInfo_t  *tInfo);
MAE_Ret _ATVAPP_UpdateArea(AtvAppData_t *pThis,TvSrvRegion_e eArea,u16 u16Index);
MAE_Ret _ATVAPP_SaveChannelsInfo(AtvAppData_t *pThis, const ATVChannelsInfo_t  *tChannelsInfo);
MAE_Ret _ATVAPP_CreateSearchScreen(AtvAppData_t	*pThis,u32 u32Total);
void _ATVAPP_UpdateSearchScreenProgress(AtvAppData_t	*pThis, u32 u32Index , u32 u32Total);
void _ATVAPP_StartSearchWatchTimerCB(void *pUsr);
#ifdef __ATV_CMMB__
void _ATVAPP_RetiveATVInfo(AtvAppData_t	*pThis,TvSrvCmmbTvInfo_t *pTnfo);
#else
void _ATVAPP_RetiveATVInfo(AtvAppData_t	*pThis,TvSrvSignalLevel_t *pTnfo);
#endif
void _ATVAPP_SearchTimerCB(void *pUsr);
void _ATVAPP_RetiveSearchInfo(AtvAppData_t	*pThis,TvSrvChannelInfo_t *pTnfo);
MAE_Ret _ATVAPP_PowerOffAction(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_VolumeIncreaseAction(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_VolumeDecreaseAction(AtvAppData_t *pThis);
#ifndef __ATVAPP_SMALLROM__
MAE_Ret _ATVAPP_CaptureAction(AtvAppData_t *pThis);
#else // __ATVAPP_SMALLROM__
MAE_Ret _ATVAPP_ReturnAction(AtvAppData_t *pThis);
#endif // !__ATVAPP_SMALLROM__
MAE_Ret _ATVAPP_PreviousChannelAction(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_NextChannelAction(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_RatioChangeAction(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_UpdateRatioButtonIcon(AtvAppData_t	*pThis);
#if defined(__MMI_BATTERY_ICON_DISPLAY__) && !defined(__ATVAPP_SMALLROM__)
MAE_Ret _ATVAPP_UpdateBatteryIcon(AtvAppData_t	*pThis);
#endif
void _ATVAPP_StartWatch(AtvAppData_t *pThis);
MAE_Ret _ATVAPP_IncreaseAudioVolume(AtvAppData_t	*pThis);
MAE_Ret _ATVAPP_DecreaseAudioVolume(AtvAppData_t	*pThis);
MAE_Ret _ATVAPP_SetChannelIndex(AtvAppData_t	*pThis,u8 index);
MAE_Ret _ATVAPP_UpdateWatchScreen(AtvAppData_t	*pThis);
MAE_Ret _ATVAPP_UpdateSignalIcon(AtvAppData_t	*pThis);
MAE_Ret _ATVAPP_UpdateChannelName(AtvAppData_t	*pThis);
void _ATVAPP_WatchTimerCB(void *pUsr);
MAE_Ret _ATVAPP_RetiveFileInfo(AtvAppData_t	*pThis,TvSrvFileName_t *pTnfo);
MAE_Ret _ATVAPP_Update_Icon(AtvAppData_t* pThis, IWidget *pImageWdg, u32 nImageId);
void _ATVAPPInterruptNotifyCb(void *pThis, MediaSrvInterruptStatus_e eStatus);
static void _ATVSuspendHandle(AtvAppData_t *pThis);
static void _ATVResumeHandle(AtvAppData_t *pThis);
void _ATV_FreeBuffer(void *pData);

#if !defined(__ATVAPP_SMALLROM__) && defined(__SPACE_FULL_STORAGE_SELECTION_MMI__)
static boolean _AtvIsOtherStorageAvailable(AtvAppData_t *pThis);
static MAE_Ret _AtvWatchSelectStoragePopUpMenuSelectCb(void *pCusHandle, const CommWindowMsg_t *pWndMsg, void *pParam1, void *pParam2);
#endif // !__ATVAPP_SMALLROM__ && __SPACE_FULL_STORAGE_SELECTION_MMI__

#ifndef __ATVAPP_SMALLROM__
void _AtvCreateStoragePopUpMenu(AtvAppData_t *pThis);
void _AtvMainMenuShowHideStorageItem(AtvAppData_t *pThis);
void AtvAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
MAE_Ret _AtvSelectStoragePopUpMenuSelectCb(void *pCusHandle, const CommWindowMsg_t *pWndMsg, void *pParam1, void *pParam2);
#endif // !__ATVAPP_SMALLROM__

#endif /* __MMI_ATVAPP_PRIV_H__ */
