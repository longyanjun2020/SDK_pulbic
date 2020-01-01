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
* @file    mmi_fmradioapp_util.h
* @version
* @brief   Fm radio applet utility header file
*
*/

#ifndef __MMI_FMRADIOAPP_UTIL_H__
#define __MMI_FMRADIOAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_common_cfg.h"
#ifdef __APP_MMI_FM_RADIO_REC__
#include "mmi_fmradioapp_cfg.h"
#include "mmi_common_window.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define FMRAPP_DONE_TIMER	    2000
#define FMRAPP_TEMP_STRING_SIZE	20

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
//Fm radio service callback
void FmRadioPlayStatusNotify(void *pThis, u32 nCusData, FmradioSrvPlayInfo_t *pPlayInfo);
void FmRadioPlayCb(void *pThis);
void FmRadioStopPlayCb(void *pThis);
void FmRadioStopPlayForAppStopCb(void *pThis);
void FmRadioSetFreqCb(void *pThis, FmradioSrvChannelInfo_t *pChanInfo);
void FmRadioCancelSearchCb(void *pThis, MediaSrvErrCode_e eErrCode);
void FmRadioSearchChannelCb(void *pThis, FmradioSrvChannelInfo_t *pChannelInfo);
void FmRadioAutoSearchListCb(void *pThis, FmradioSrvChannelInfo_t *pChannelInfo);
#ifdef __FMR_SIGNAL_INFO__
void FmRadioGetChannelInfoCb(void *pThis, FmradioSrvChannelInfo_t *pChannelInfo);
#endif // __FMR_SIGNAL_INFO__
void FmRadioChannelInfoNotify(void *pThis, u32 nCusData, FmradioSrvChannelInfo_t *pChanInfo);
void FmRadioErrorNotify(void *pThis, u32 nCusData, FmradioSrvErrorInfo_t *pErrorInfo);

#if defined(__MMI_BATTERY_ICON_DISPLAY__)
//Battery callback
void FmRadioBatteryExtPwrChangeCb(void *pUserData, boolean bChargerPlugged);
void FmRadioBatteryBattLevelChangeCb(void *pUserData, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
void FmRadioBatteryChargingStatusChangeCb(void *pUserData, MAEChargingStatus_e eChargingStatus, MAEBatteryID_e eBatID);
void FmRadioBatteryHardwareAlarmCb(void *pUserData, MAEBattAlarmType_e eAlarmType);
MAE_Ret FmRadioMainPanelUpdateBatteryIcon(FmRadioAppData_t *pThis);
#endif

//Headset callback
void FmRadioHandleAccessoryEvtCb(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
void FmRadioPlugOutHeadsetHookFunc(void *pThis, u32 nCusData);
void FmRadioPlugInHeadsetHookFunc(void *pThis, u32 nCusData);

//ResMgr interrupt callback
void FmradioResMgrNotifyCb(void *pUserData, FmradioSrvResMgrNotifyData_t *pCbData);

/*** FMRAPP_WND_MAIN window related function ***/
MAE_Ret FmRadioMainPanelUpdateNameText(FmRadioAppData_t *pThis, MAE_WChar *pChannelName);
MAE_Ret FmRadioMainPanelUpdateFreqText(FmRadioAppData_t *pThis, u32 nFreq);
MAE_Ret FmRadioMainPanelUpdateVolume(FmRadioAppData_t *pThis, u8 nVolume);
MAE_Ret FmRadioMainPanelUpdateFreqIndicator(FmRadioAppData_t *pThis);

#ifdef __TOUCH_SCREEN_MMI__
//Frequency change button callback
void FmRadioMainPanelFreqChangeButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void FmRadioMainPanelFreqChangeButtonLongPressCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void FmRadioMainPanelFreqChangeButtonInvalidCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid, IWidget *pWidget);

//Volume change button callback
void FmRadioMainPanelVolumeChangeButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

//Channel add button callback
void FmRadioMainPanelChannelAddButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif // __TOUCH_SCREEN_MMI__

//Frequency indicator callback
//Justin: Change (IDataModel* pDataModel, ) --> (u32 dwParam)  The data word param (NOT use now)
void FmRadioMainPanelFreqIndDataChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

//Background play switch icon callback
//Justin: Change (IDataModel *pDataModel, ) --> (u32 dwParam)  The data word param (NOT use now)
void FmRadioMainPanelBgPlaySwitchIconDataChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

//Power on/off switch icon callback
//Justin: Change (IDataModel *pDataModel, ) --> (u32 dwParam)  The data word param (NOT use now)
void FmRadioMainPanelPowerOnOffSwitchIconSwitchingCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bCheck, IWidget *pWidget);
#ifdef __TOUCH_SCREEN_MMI__
#ifdef __APP_MMI_FM_RADIO_REC__
void FmRadioMainPanelRecButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
#endif
/*** FMRAPP_WND_MAIN_OPTIONMENU, FMRAPP_WND_MYCHANNELLIST_OPTIONMENU, FMRAPP_WND_EDITCHANNEL_EDITNAME_OPTIONMENU window related function ***/
//Option menu callback
void FmRadioOptionMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FmRadioOptionMenuLayer2SoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FmRadioEditNameOptionMenuLayer2SoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/*** FMRAPP_WND_MYCHANNELLIST window related function ***/
void FmRadioMyChannelListAdapterGetItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eMenuItemType, IWidget *pMenu, u32 nIndex);
void FmRadioMyChannelListFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eMenuItemType);

//My channel list menu callback
void FmRadioMyChannelListMenuCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FmRadioMyChannelListMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);

/*** FMRAPP_WND_AUTOSEARCHLIST window related function ***/
void FmRadioAutoSearchChannelFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eMenuItemType);

//Auto search list menu callback
void FmRadioAutoSearchChannelActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FmRadioAutoSearchChannelOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);

/*** FMRAPP_WND_EDITCHANNEL_MAIN window related function ***/
//Edit channel menu callback
void FmRadioEditChannelMenuCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/*** FMRAPP_WND_EDITCHANNEL_EDITFREQ, FMRAPP_WND_MANUALINPUT window related function ***/
//Frequency input callback
void FmRadioFrequencyInputTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

/*** FMRAPP_WND_EDITCHANNEL_EDITNAME window related function ***/
//Channel name input callback
void FmRadioChannelNameInputTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

/*** Fm radio utility function ***/
MAE_Ret FmRadioSaveChannelRecord(FmRadioAppData_t *pThis);
MAE_Ret FmRadioGetInputName(FmRadioAppData_t *pThis);
MAE_WChar* FmRadioGetChannelName(FmRadioAppData_t *pThis, u32 nFreq);
void FmRadioUpdateMyChannelCount(FmRadioAppData_t *pThis);
MAE_Ret FmRadioDrawDoneScreen(FmRadioAppData_t *pThis, u8 nDialogViewId, u32 nTextId);
MAE_Ret FmRadioDrawConfirmDialog(FmRadioAppData_t *pThis, u32 nTextId);
u32 FmRadioCovertWStrToFreq(MAE_WChar *pWStr);
void FmRadioSelectMyChannel(FmRadioAppData_t *pThis, MMI_FMR_CHANNEL_NO_e nChannel);
void FmRadioChangeVolume(FmRadioAppData_t *pThis, u8 nNewVolume);
void FmRadioAutoSearchStopProc(FmRadioAppData_t *pThis);
#ifdef __FMR_SIGNAL_INFO__
void FmRadioGetChannelInfoTimerCb(void *data);
#endif // __FMR_SIGNAL_INFO__
MAE_WChar* FmRadioGetFrequencyStr(u32 nChannelFreq);
MAE_Ret FmRadioOptionMenuHideRecItems(FmRadioAppData_t *pThis, FmRadioOptionMenuWndData_t *pData);

MAE_Ret FmRadioRecordUpdateFreqText(FmRadioAppData_t *pThis, u32 nFreq);
MAE_Ret FmRadioRecordUpdateStatusText(FmRadioAppData_t *pThis, FmRecStatus_e eRecordStatus);
MAE_Ret FmRadioMainPanelUpdatePosText(FmRadioAppData_t *pThis, u32 nRecordPos);
MAE_Ret FmRadioRecordUpdatePosText(FmRadioAppData_t *pThis, u32 nRecordPos);
MAE_Ret FmRadioRecordStart(FmRadioAppData_t *pThis);
void FmRadioRecordStartCb(void *pThis);
void FmRadioRecordPauseCb(void *pThis, FmradioSrvFileInfo_t *pFileInfo);
void FmRadioRecordStopCb(void *pThis, FmradioSrvFileInfo_t *pFileInfo);
void FmRadioMainPanelUpdateOnRecord(FmRadioAppData_t *pThis);
boolean FmRadioIsRecFormatSupport(VOICE_RECORD_Type_e eRecordType);
u32 FmRadioNumRecFormatSupport(void);
MAE_Ret FmRadioDrawRecDialog(FmRadioAppData_t *pThis, u8 nDialogViewId, u32 nTextId);
void FmRadioDrawStopBGPlayDialog(void *pData, boolean bByEndKey);
void FmRadioRecStatusNotify(void *pThis, u32 nCusData, FmradioSrvRecInfo_t *pRecInfo);
MAE_Ret FmRadioRecordStop(FmRadioAppData_t *pThis);
MAE_Ret FmRadioRecordPause(FmRadioAppData_t *pThis);
MAE_Ret FmRadioRecordResume(FmRadioAppData_t *pThis);
MAE_Ret FmRadioDrawHeadsetInsertDialog(FmRadioAppData_t *pThis);

#ifdef __APP_MMI_FM_SCHEDULE__
MAE_Ret FmRadioUtilGetScheduleDataFromConfig(FMSCH_ENTITY_t *pSchData, u32 nSchId);
void FmRadioSchInit(void *pThis, FmRadioLaunchData_t *pLaunchData);
void FmRadioSchLaunch(void *pThis);

#ifdef __APP_MMI_FM_RADIO_REC__
MAE_Ret FmRadioUtilGetRecScheduleDataFromConfig(FMRECSCH_ENTITY_t *pSchData, u32 nSchId);
void FmRadioRecordUpdateDateText(FmRadioAppData_t *pThis, IWidget *pIDateTextWidget, u32 nRecordDatetime);
void FmRadioRecordUpdateTimeText(FmRadioAppData_t *pThis, IWidget *pITimeTextWidget, u32 nRecordStartTime, u32 nRecordEndTime);
u32 FmSchUtilConvertSchRecEndTime(u32 nEndTime, u32 nCurrentTime);
#endif

#endif
#ifdef __APP_MMI_FM_RADIO_REC__
void FMradioResetRegisterAccessoryEvtCb(void *pThis);
MAE_Ret FmRadioSetRecordStorageMenuSoftkeyActCb(void* pCusHandle, const CommWindowMsg_t *pWndMsg, void *pParam1, void *pParam2);
void FMRadioSelectStorage(FmRadioAppData_t *pThis);
#endif
#endif /* __MMI_FMRADIOAPP_UTIL_H__ */
