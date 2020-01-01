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
* @file    mmi_fmradioapp_priv.h
* @version
* @brief   Fm radio applet private header file
*
*/

#ifndef __MMI_FMRADIOAPP_PRIV_H__
#define __MMI_FMRADIOAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_fmradioapp.h"
#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"
#include "mmi_common_dialog_id.h"
#include "mmi_fmradioapp_id.h"
#include "fmradioapp_resource.h"
#include "mmi_launcher_fmradio.h"
#ifdef __APP_MMI_FM_SCHEDULE__
#include "mmi_fmsch_cfg.h"
#endif


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define FMR_MAX_CHANNEL_NAME_LENGTH     15
#define FMR_MAX_CHANNEL_FREQ_LENGTH     5
#define FMR_MAX_AUTOSEARCH_CHANNEL_NUMBER  50
#define FMR_AUTOSEARCH_CHANNEL_NUMBER_LENGTH  6

/* If length of a record file name is too long, we cut it on the dailog. */
#define FMR_RECORD_NAME_STR_CUT_LEN 15
/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    IWidget *pBgImageWdg;
    IWidget *pNameTextWdg;
    IWidget *pFrequencyTextWdg;
    IWidget *pBgPlaySwitchIconWdg;
    IWidget *pChannelAddButtonWdg;
    IWidget *pForwardButtonWdg;
    IWidget *pBackwardButtonWdg;
    IWidget *pPowerOnOffSwitchIconWdg;
    IWidget *pPowerOnOffImageWdg;
    IWidget *pRecButtonWdg;
    IWidget *pVolumePlusButtonWdg;
    IWidget *pVolumeMinusButtonWdg;
#ifndef __FMRADIOAPP_SMALLROM__
    IWidget *pVolumeLev8ImageWdg;
    IWidget *pVolumeLev7ImageWdg;
    IWidget *pVolumeLev6ImageWdg;
    IWidget *pVolumeLev5ImageWdg;
    IWidget *pVolumeLev4ImageWdg;
    IWidget *pVolumeLev3ImageWdg;
    IWidget *pVolumeLev2ImageWdg;
    IWidget *pVolumeLev1ImageWdg;
    IWidget *pSoundOnOffImageWdg;
#endif
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
    IWidget *pBatteryImageWdg;
#endif
    IWidget *pFreqIndicatorWdg;
    IWidget *pPosTextWdg;
#ifdef __FMRADIOAPP_SMALLROM__
    IWidget *pTitleBarImageWdg;
    IWidget *pVolumeBgImageWdg;
    IWidget *pVolumeImageWdg;
	IWidget *pFmTextWdg;
#endif

#if defined(__3D_UI_FMRADIO__)
	IWidget *pMainAbsContainer;
	IWidget *pFrequencyUnitImageWdg;
	IWidget *pVolumeLev8ImageBgWdg;
	IWidget *pVolumeLev7ImageBgWdg;
	IWidget *pVolumeLev6ImageBgWdg;
	IWidget *pVolumeLev5ImageBgWdg;
	IWidget *pVolumeLev4ImageBgWdg;
	IWidget *pVolumeLev3ImageBgWdg;
	IWidget *pVolumeLev2ImageBgWdg;
	IWidget *pVolumeLev1ImageBgWdg;
	IWidget *pPosImgWdg;
	IWidget	*pChannelMenuWdg;
	IWidget	*pChannelMenuNextWdg;
	IWidget	*pChannelMenuBackWdg;
#endif //#if defined(__3D_UI_FMRADIO__)

} FmRadioMainPanelViewWdgList_t;

typedef struct
{
#ifndef __FMRADIOAPP_SMALLROM__
    IWidget *pTextWdgDate;
    IWidget *pTextWdgTime;
    IWidget *pImageWdgBg;
    IWidget *pTextWdgChannel;
    IWidget *pTextWdgCount;
    IWidget *pImageWdgRec;
    IWidget *pTextWdgStatus;
#else
    IWidget *pImageTitleBg;
    IWidget *pTextWdgDate;
    IWidget *pTextWdgTime;
    IWidget *pTextWdgStatus;
    IWidget *pTextWdgChannel;
    IWidget *pTextWdgCount;
#endif
} FmRadioRecordViewWdgList_t;

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pMenuWdg;
    IWidget *pFreqThmTextWdg;
} FmRadioMyChannelListViewWdgList_t;

typedef struct
{
    IWidget *pMenuWdg;
} FmRadioEditChannelViewWdgList_t;

typedef struct
{
    IWidget *pScrollBarWidget;
    IWidget *pMflContainer;
    IWidget *pBgPlayWidget;
    IWidget *pSpeakerWidget;
    IWidget *pRecordTypeWidget;
    IWidget *pStorageWidget;
} FmRadioSettingsViewWdgList_t;

typedef struct
{
    IWidget *pMenuWdg;
} FmRadioSetRecordTypeViewWdgList_t;

typedef struct
{
    IWidget *pMenuWdg;
} FmRadioSetRecordStorageViewWdgList_t;

typedef struct
{
    FmRadioMainPanelViewWdgList_t   tWdgList;
    IndicatorData_t                 tIndicatorData;
    //boolean                         bCreateMainPanel;

#if defined(__3D_UI_FMRADIO__)
    boolean                         bUpdateFirstTime;
#endif
} FmRadioMainPanelWndData_t;

typedef struct
{
    FmRadioRecordViewWdgList_t   tWdgList;
} FmRadioRecordWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
    OptionMenuData_t    tOptionMenuData;
} FmRadioOptionMenuWndData_t;

typedef struct
{
    FmRadioMyChannelListViewWdgList_t   tWdgList;
    boolean                             bDeleteAll;    //Keep remove or remove all status.
} FmRadioMyChannelListWndData_t;

typedef struct
{
    u16 nRssi;
    u32 nFrequency;
} FmRadioRssiIndex_t;

typedef struct
{
    MenuWdgList_t tWdgList;
    boolean bStopAutoSearch;
    boolean bStopAutoSearchCmdOn;
	boolean bSetFirstItemFocusOn;
    u32 nCurrentFrequency;
    u32 nPreviousFrequency;
    u32 nFirstFrequency;
    u32 nCurAutoSearchChannelIndex;
#ifdef __APP_MMI_FM_SCHEDULE__
	boolean bSchFired;
#endif
    FmRadioRssiIndex_t *pSignal;
} FmRadioAutoSearchListWndData_t;

typedef struct
{
    FmRadioEditChannelViewWdgList_t tWdgList;
} FmRadioEditChannelMainWndData_t;

typedef struct
{
    PopUpPromptWdgList_t    tWdgList;
    boolean                 bSKShown;   //Check if softkey is shown.
} FmRadioEditChannelFreqWndData_t;

typedef struct
{
    InputVtmWdgList_t   tWdgList;
    boolean             bSKShown;       //Check if softkey is shown.
} FmRadioEditChannelNameWndData_t;

typedef struct
{
    FmRadioSettingsViewWdgList_t tWdgList;
    ScrollData_t tScrollData;
    u32 nSettingsFocusWdgId;
} FmRadioSettingsWndData_t;

typedef struct
{
    FmRadioSetRecordTypeViewWdgList_t tWdgList;
} FmRadioSetRecordTypeWndData_t;

typedef struct
{
    VOICE_RECORD_Type_e eRecType;
    StorageCfg_t eStorageCFG;
    StorageType_e eRecStorage;
} FmRecSettingData_t;

#ifdef __APP_MMI_FM_SCHEDULE__
typedef enum
{
    FM_SCH_NONE,
    FM_SCH_PLAY,
    FM_SCH_REC,
} FmSchType_e;

typedef struct
{
    FmSchType_e eSchType;
    u32 nSchId;
    union {
        FMSCH_ENTITY_t tSchPlayEntity;
        FMRECSCH_ENTITY_t tSchRecEntity;
    } uSchEntity;
} FmSchData_t;
#endif

#ifdef __APP_MMI_FM_RADIO_REC__
typedef struct
{
#ifdef __APP_MMI_FM_SCHEDULE__
    boolean bRecSchFired;
    FMRECSCH_ENTITY_t *ptRecSchEntity;
#endif
    MAE_WChar *strRecordFilePath; // New record path, or append record file.
} FmRecData_t;
#endif

typedef enum
{
    FMR_RECORD_START,
    FMR_RECORD_PAUSE,
    FMR_RECORD_STOP
} FmRecStatus_e;


/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
    FMR_CHANNEL_RECORD_t    tMyChannelList[FMR_CHANNEL_NUM_MAX];
    FMR_CHANNEL_RECORD_t    tChannelDataTemp;
    FmradioSrvStatus_e      eFmrStatus;             //Fm radio status
    AudioEnvSrvVolLevel_e   eFmrVolume;             //Fm radio current volume
    MMI_FMR_SETTING_e       eFmrSpeaker;            //Keep fm radio speaker
    MMI_FMR_SETTING_e       eFmrBackgroundPlay;     //Keep fm radio background play
    u8                      nMyChannelListNum;      //Keep my channel list number
    u32                     nFmrFrequency;          //Fm radio current frequency
    u32                     nCurMyChannelIndex;     //Keep current selected my channel index
    u32                     nFirstItemIndex;        //Keep first item index if needed
    u32                     nSelectedItemIndex;     //Keep selected item index if needed
    u32                     nFirstItemIndexLev2;    //Keep first item index if needed
    u32                     nSelectedItemIndexLev2; //Keep selected item index if needed
    boolean                 bLongPressed;           //Keep long pressed flag.
    boolean                 bAddChannelMode;        //Keep key pressed flag.
    boolean                 bIsHeadsetInserted;     //Keep headset status.
    boolean                 bIsNeedPopDialog;       //Keep pop dialog status.
    //boolean                 bIsShowConfirm;         //Keep confirm dialog status.
    boolean                 bIsAirplaneMode;        //Keep airplane mode status.
    //boolean                 bChangeHeadsetStatus;   //Keep headset status change.
    boolean                 bIsInAutoSearchWnd;    //Keep auto search view status.
    boolean                 bIsNeedConfirmStop;     //Keep confirm stopped status.
	boolean					bAntennaSupport;		//Keep Antenna support status
	boolean                 bShowWarning;           //Check whether ap need to show "PleaseConnectHeadset" dialog.
	boolean                 bIsPowerOn;
#ifdef __APP_MMI_FM_RADIO_REC__
    FmRecSettingData_t      tRecSettingData;        //Keep record setting data.
    FmRecData_t             tRecData;               //Keep the record data.
    boolean                 bRecordPaused;          //Keep the status if record paused.
    boolean                 bRecordOn;          //Keep the status if record ON/OFF.
    boolean                 bPlugCardRecordErr;     //record if sd plug out rec err happened
#endif
#ifdef __APP_MMI_FM_SCHEDULE__
    FmSchData_t             tSchData;               //Keep the schedule data.
    u32                     nSchErrShow;	    //Keep the text label of schedule initial error. For showing when window is created.
#ifdef __APP_MMI_FM_RADIO_REC__
    u32                     nEndTime;
    u8                      nSchRecToPlay;
#endif
    boolean                 bExitByEndKey;
#endif
	//boolean                 bLockOptionMenu;          //Keep the Record status
} FmRadioAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret FmRadioConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret FmRadioDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmRadioStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmRadioStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmRadioSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmRadioResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmRadioKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmRadioKeyLongPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

//Window manager related function
MAE_Ret FmRadioWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndRecordHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndMainOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndMyChannelListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndMyChannelListOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndEditChannelMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndEditChannelEditNameHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndEditChannelEditNameOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndEditChannelEditFreqHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndAutoSearchListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndManualInputHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndSettingsHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __APP_MMI_FM_RADIO_REC__
MAE_Ret FmRadioWndSetRecordTypeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmRadioWndSetRecordStorageHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

#endif /* __MMI_FMRADIOAPP_PRIV_H__ */
