/**
* @file mmi_videotelephonyapp_priv.h
*
* Class Id: CLSID_VIDEOTELEPHONYAPP
*
*/
#ifndef __MMI_VIDEOTELEPHONYAPP_PRIV_H__
#define __MMI_VIDEOTELEPHONYAPP_PRIV_H__
/*-------------------------------------------------------------------------*/
#include "mmi_common_dialog.h"
#include "mmi_videotelephonyapp.h"
#include "mmi_phbapp.h"
#include "mmi_baseapplet.h"
#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"
#include "mmi_common_wdgvar.h"
#include "mmi_videotelephonyapp_id.h"
//#include "mmi_videotelephonyapp_rs.h"
#include "mmi_srv_vtm.h"
#include "mmi_srv_mobilitymgr.h"
#include "videotelephonyapp_resource.h"
//#include "ccapp_resource.h"

/// For VT Record function
#define __VIDEOTELEPHONYAPP_RECORD__

/// For big remote view layout
//#define __VIDEOTELEPHONYAPP_BIG_REMOTE_VIEW__

#define VIDEOTELEPHONYAPP_IPNUMBER_MAX_BYTE         (IPCALL_MAX_NUM_LEN * sizeof(MAE_WChar))
#define  MMI_VIDEOTELEPHONYAPP_DIGITAL_LEN	10
#define MMI_VIDEOTELEPHONYAPP_RECORD_VOICE_LIMIT_SIZE_KB 10
#define VIDEOTELEPHONYAPP_RECORD_VIDEO_MIN_SIZE_KB 500 // 500KB


#define VIDEOTELEPHONYAPP_OUTGOING_TONE_TIMER 5000
#define VIDEOTELEPHONYAPP_CALLEND_TIMER	2000
#define VIDEOTELEPHONYAPP_DONE_TIMER	1000
#define VIDEOTELEPHONYAPP_CALLFAILED_TIMER	2000
#define VIDEOTELEPHONYAPP_OPERATION_NOT_ALLOW_TIMER	2000
#define VIDEOTELEPHONYAPP_INFORMATION_TIMER	2500
#define VIDEOTELEPHONYAPP_EVERYSECOND_TIMER	1000
#define VIDEOTELEPHONYAPP_AUTO_DTMF_TIMER	2500
#define VIDEOTELEPHONYAPP_STOP_DTMF_TIMER	100
#define VIDEOTELEPHONYAPP_TS_LONGPRESS_TIME 1500
#define VIDEOTELEPHONYAPP_CALL_END_TONE_TIMER	500	// Call end tone: work-around solution
#define VIDEOTELEPHONYAPP_CALL_INDICATOR_FLASH_ON 300
#define VIDEOTELEPHONYAPP_CALL_INDICATOR_FLASH_OFF 200
#define VIDEOTELEPHONYAPP_LOW_BATTERY_ALARM_TIMER 30 // 30s, low battery alarm interval

#define VIDEOTELEPHONYAPP_MIN_MEM_FOR_RECORDING (450*1024) // 450KB
#define VIDEOTELEPHONYAPP_MIN_MEM_FOR_PHB (1600*1024) // 1600KB
#define VIDEOTELEPHONYAPP_MIN_MEM_FOR_MSG (1500*1024) // 1500KB
#define VIDEOTELEPHONYAPP_MIN_MEM_FOR_VT_CALL (2650*1024) // 2650KB
#define VIDEOTELEPHONYAPP_MIN_MEM_FOR_SOURCE_FILE (200*1024) // 200KB

#ifdef __ANSWER_INDICATOR_MMI__
#define VIDEOTELEPHONYAPP_ANSWER_REMINDER  1000
#endif

#ifdef __IP_CALL_MMI__
//#include "mmi_common_cfg.h"
#define VIDEOTELEPHONYAPP_IPNUMBER_TIMER 2500
#define VIDEOTELEPHONYAPP_MIN_IPNUMBER 1
#endif
#define VIDEOTELEPHONYAPP_PUBLIC_MMI_STRING_LEN		2
#define VIDEOTELEPHONYAPP_CRUNCH_DONE_TIMER	1000


#define VIDEOTELEPHONYAPP_REDIAL_STR_LEN 60

#ifdef __FEATURE_VECTOR_FONT__
#define VIDEOTELEPHONYAPP_TWO_LINE_CHAR_LENGTH (15*2)
#else
#define VIDEOTELEPHONYAPP_TWO_LINE_CHAR_LENGTH ( 9*2)
#endif

typedef enum
{
	VIDEOTELEPHONYAPP_DIRECTION_UNKNOWN = 0 ,
	VIDEOTELEPHONYAPP_MT_ANSWER_BY_BT_HEADSET,
	VIDEOTELEPHONYAPP_MT_ANSWER_BY_HANDSET,
	VIDEOTELEPHONYAPP_MO_CALL,
	VIDEOTELEPHONYAPP_BT_RECONNECT
} MMI_VIDEOTELEPHONYAPP_DIRECTION_BT_e;

typedef struct MMI_VIDEOTELEPHONYAPP_SETTING_TAG {
	u8     AutoRedial;
	u16    MinuteReminder;
}MMI_VIDEOTELEPHONYAPP_SETTING;

typedef enum
{
	VIDEOTELEPHONYAPP_TS_TOUCHGRID1,
	VIDEOTELEPHONYAPP_TS_TOUCHGRID2
} MMI_VIDEOTELEPHONYAPP_TS_GRID_e;

typedef enum
{
	VIDEOTELEPHONYAPP_HANDSET,
	VIDEOTELEPHONYAPP_SPEAKER,
	VIDEOTELEPHONYAPP_BT_HEADSET,
} MMI_VIDEOTELEPHONYAPP_AUDIO_PATH_e;

#ifdef __IP_CALL_MMI__
typedef struct MMI_VIDEOTELEPHONYAPP_IPCALL_TAG{
	  MmiVideoTelephonyAppDuoOption_t tDuoOption;
	  u32 nHeightLightID; // height ID , ID : menu ID
	  u32 nKeyCode; // for editor key press
	  u8 *pDialNum;
}MMI_VIDEOTELEPHONYAPP_IPCALL_t;
#endif

typedef enum
{
	VIDEOTELEPHONYAPP_IFONE_UNKNOWN = 0 ,
	VIDEOTELEPHONYAPP_IFONE_PHONEBOOK,
	VIDEOTELEPHONYAPP_IFONE_MESSAGE
} MMI_VIDEOTELEPHONYAPP_IFONE_START_AP_e;

/*
typedef enum
{
	MMI_COMMON_VIEW_DIALOG = 0 ,
	MMI_COMMON_VIEW_OPTION_MENU,
	MMI_COMMON_VIEW_POPUP
} MMI_COMMON_VIEW_TYPE_e;
*/

typedef enum
{
	VIDEOTELEPHONYAPP_ZOOM_1X = 0,
	VIDEOTELEPHONYAPP_ZOOM_2X,
	VIDEOTELEPHONYAPP_ZOOM_3X,
	VIDEOTELEPHONYAPP_ZOOM_4X
} MMI_VIDEOTELEPHONYAPP_ZOOM_e;

typedef enum
{
	VIDEOTELEPHONYAPP_LIGHT_MINUS_TWO = 0,
	VIDEOTELEPHONYAPP_LIGHT_MINUS_ONE,
	VIDEOTELEPHONYAPP_LIGHT_DEFAULT,
	VIDEOTELEPHONYAPP_LIGHT_PLUS_ONE,
	VIDEOTELEPHONYAPP_LIGHT_PLUS_TWO
} MMI_VIDEOTELEPHONYAPP_LIGHT_e;

typedef enum
{
	VIDEOTELEPHONYAPP_SCREEN_MODE_LOCAL_SMALL = 0,
	VIDEOTELEPHONYAPP_SCREEN_MODE_LOCAL_LARGE,
	VIDEOTELEPHONYAPP_SCREEN_MODE_REMOTE_ONLY,
	VIDEOTELEPHONYAPP_SCREEN_MODE_LOCAL_ONLY
} MMI_VIDEOTELEPHONYAPP_SCREEN_MODE_e;

typedef enum
{
	VIDEOTELEPHONYAPP_CAMERA_ON = 0,
	VIDEOTELEPHONYAPP_CAMERA_OFF
} MMI_VIDEOTELEPHONYAPP_CAMERA_ONOFF_e;

typedef enum
{
	VIDEOTELEPHONYAPP_LOCAL_IMAGE_SOURCE_CAMERA = 0,
	VIDEOTELEPHONYAPP_LOCAL_IMAGE_SOURCE_FILE,
} MMI_VIDEOTELEPHONYAPP_LOCAL_IMAGE_SOURCE_e;

typedef struct MMI_VIDEOTELEPHONYAPP_VIDEO_SETTING_TAG {
	MMI_VIDEOTELEPHONYAPP_ZOOM_e     nZoomValue;
	MMI_VIDEOTELEPHONYAPP_LIGHT_e nLightValue;
	MMI_VIDEOTELEPHONYAPP_SCREEN_MODE_e nScreenMode;
	MMI_VIDEOTELEPHONYAPP_CAMERA_ONOFF_e nCameraOnOff;
	MMI_VIDEOTELEPHONYAPP_LOCAL_IMAGE_SOURCE_e nLocalImageSource;
}MMI_VIDEOTELEPHONYAPP_VIDEO_SETTING;

typedef struct VideoTelephonyAppTalkViewWdgList_t_
{
	IWidget *pCallScreenBgImgWdg;
	IWidget *pVideoCallBgImgWdg;
	IWidget *pVideoCallSmallBgImgWdg;
	IWidget *pVideoCallOsdWdg;
	IWidget *pVideoCallLocalOsdWdg;    
	IWidget *pMainContainer;
	IWidget *pImgAreaContainer;
	/*
	IWidget *pMptyImgWdg1;
	IWidget *pMptyImgWdg2;
	IWidget *pMptyImgWdg3;
	IWidget *pMptyImgWdg4;
	IWidget *pMptyImgWdg5;
	*/
	IWidget *pTimeAreaContainer;
	IWidget *pDuoImgWdg;
	IWidget *pRecordImgWdg;
    IWidget *pRecordTimerWdg;
	IWidget *pTimerWdg;
	IWidget *pMuteImgWdg;
	IWidget *pAudioSourceImgWdg;
	IWidget *pTextAreaContainer;
	IWidget *pTextAreaBgImgWdg;
	IWidget *pCallInfoImgWdg1;
	IWidget *pCallInfoTextWdg1;
	/*
	IWidget *pCallInfoMptyListWdg;
	IWidget *pCallInfoImgWdg2;
	IWidget *pCallInfoTextWdg2;
	*/
} VideoTelephonyAppTalkViewWdgList_t;


typedef struct VideoTelephonyAppOutgoingCallViewWdgList_t_
{
	IWidget *pCallScreenBGWdg;
	IWidget *pMainContainer;
	IWidget *pImgAreaContainer;
	IWidget *pOutgoingCallImgWdg;
	IWidget *pTextAreaContainer;
	IWidget *pCallStatesTextWdg;
	IWidget *pCallInfoTextWdg;
	IWidget *pDuoStateTextWdg;
} VideoTelephonyAppOutgoingCallViewWdgList_t;

typedef struct VideoTelephonyAppDialingWdgList_t_
{
	IWidget *pMainContainer;
	IWidget *pInputWidget;
	IWidget *pShortcutWidget;
#ifdef __TOUCH_SCREEN_MMI__
	IWidget *pGridWdg1;
	IWidget *pButtonWdg1;
	IWidget *pGridWdg2;
	IWidget *pButtonWdg2;
#endif
} VideoTelephonyAppDialingWdgList_t;


typedef struct VideoTelephonyAppIpNumEdirotViewWdgList_t_
{
	IWidget *pInputWdg;
} VideoTelephonyAppIpNumEdirotViewWdgList_t;

 /**
 * Application structure
 */
typedef struct MMI_VIDEOTELEPHONYAPP_TAG {
    APPLET_BASE_ELEMENTS;
	CallTable_t		*pCallTableCache;
	MMI_VTCC_AP_FID_E	fid;
	MmiMakeCallReq_t* ptMakeCallReq;
	MMI_VIDEOTELEPHONYAPP_DIRECTION_BT_e	BTDirection;	// Decide VIDEOTELEPHONYAPP have to connect SCO link or not

	u8				u8SessDualId;
	COMMON_SIM_CARD_STATUS_e DuoSimStatus;

	boolean		bSpeakerOn;			// Flag for Speaker state	(TRUE-->Speaker On	,FALSE-->Speaker Off)
	boolean		bMuteState;			// Flag for Mute State		(TRUE-->Mute		,FALSE-->Unmute)
	boolean		bRecordState;		// Flag for Record State	(TRUE-->Record		,FALSE-->Stop record)
	boolean		bIdle;				// Flag for close cc ap 	(TRUE --> gotoIdle, FALSE --> still active)
	boolean 	bDTMF;				// Flag for DTMF reauest  	(TRUE --> enable, FALSE --> disable)
	boolean     bAlertFlag;         // Flag for alert state
	boolean     bAudioChannelFlag;  // Flag for audio channel opened or not
	boolean		bPhbMakeCall;
	u8          u8ProgressInd;      // Keep last progress indication
	u16			u16MinuteReminder;
	u8			*pPubMmiStr;		// Store the short string for public MMI operation in outgoincall mode (EX. 1 Send)
	u32			MOKeycode;			// Use this flag to distinguish Send/Send2 key

	// Widget for Screen View

	s32			s32InCallDurationTick;
	u32			u32RecordDurationTick;
	IWidget		*pProgressWdg;

	// Widget for Menu View

	// Widget for Option Menu View
	IWidget		*pOptMenuWdg;

	u8			u8MPTYOperCallID;
	u16			u16MPTYListIndex;		// Store index for returning from MPTYListOption mode

	// For InCallEditor
	u32			nFirstKeyCode;			// Keep the first key-stoke and assign it to input editor for InCallEditor
	u16		u16DTMFCount;

	// For Auto Redial
	u8			u8RedialAtttmptLimit;
	u8			u8RedialCount;
	s16			s16RedialRemainTime;
	MmiMakeCallReq_t	*pRedialMakeCallReq;

	// For Auto DTMF
	u8			*pCurDTMFStr;	// It will copy one segment of Auto DTMF to here to process (EX: "1234" for 1st time, "4567" for 2nd time, "7890" for 3rd)
	u8			u8CurDTMFPos;
	u8			u8DTMFCnfNum;

	boolean	bRemotePartyEndCall;
	MMI_VIDEOTELEPHONYAPP_SETTING CallSetting;
	MMI_VIDEOTELEPHONYAPP_VIDEO_SETTING VideoSetting;
	
	WidgetHandler_t DialogViewHdlData;
	WidgetHandler_t NotificationViewHdlData;
	// For Record
	MAE_WChar *pTempFilePath;
#ifdef __TOUCH_SCREEN_MMI__
	MMI_VIDEOTELEPHONYAPP_TS_GRID_e eTouchGrid;
	boolean         bLongPressed;
#endif
#ifdef __IP_CALL_MMI__
	MMI_VIDEOTELEPHONYAPP_IPCALL_t *pIPCAll;
    //boolean bShortPress;
#endif

	SetDisplayMenuStyle_e eMenuStyle;
    VideoCall_Setting_LoopBack_e eLoopBackTestSetting;
        
	//For keep volume level
	boolean                 bUpdateVolume;
	SetRingToneVolume_e     eVolume;

	//For keep InCallEditor status
	boolean bEnableOptionMenu;

	//For recording dialog
	IWidget		*pRecordingImageWidget;	
	IWidget		*pRecordingTimerDurationWidget;
	boolean     bStopRecording;

	// Hide incall option menu items
	boolean	bUSBUsed;
	// Allow OFFAP interrupt flag
	SoftkeyID_e ePreLeftSoftkeyID;
	AudioEnvSrvAudPath_e ePreAudioPath;
	boolean bChangeAudioPath;
#ifdef __DEDICATE_END_KEY_MMI__
	SoftkeyID_e ePreRightSoftkeyID;
#endif

	u8               *pWFuncStr;
	boolean          bWFuncFlag;
	boolean bIsNeedDTMFStop;

	u8 			nMPTYNum;
	u8  bIsStopped;
	//For keep end call flag
	boolean bEndCall;
	boolean bIsLaunchOtherAP;
	boolean bIsShowBTDialog;
	boolean bIsAtCallFailScreen;
	boolean bIsCallRelease;
	boolean bPowerOffInt;
	boolean bIsShowCallEndDialog;
	//boolean bIsOpenAudioSession;
#ifdef __IP_CALL_MMI__
	boolean bIsBackToIPCall;
#endif
	boolean bHandlingInCallEditorSendAction;

	boolean bMakeCallCnf;
	boolean bAudioSourceOff;
	MAE_WChar* pLocalSidePictureURL;

    boolean bIsSDInsert;
	boolean bSelectPicture;

	//IBitmap *pStickerData;
	//DIB_t *pStickerDIB;    
	boolean bRemoteLostSync;
	boolean bVtmOpenFailed, bVtmOpened;
	boolean bLowBatteryAlarmInCall;
	u32 u32LowBatteryAlarmStartTime;
} MMI_VIDEOTELEPHONYAPP;


MAE_Ret VideoTelephonyAppWndDualMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndOutgoingCallHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __IP_CALL_MMI__
MAE_Ret VideoTelephonyAppWndIPNumberListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndIPNumberEditorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret VideoTelephonyAppWndInCallScreenHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndInCallScreenOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndInCallScreenModeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndInCallScreenSourceHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndInCallScreenRecordingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndInCallEditorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndInCallEditorOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndMultipartyListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndMultipartyOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDTMFNumberInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);


MAE_Ret VideoTelephonyAppWndCreateDUALMENU(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyDUALMENU(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowDUALMENU(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideDUALMENU(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateOUTGOINGCALL(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyOUTGOINGCALL(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowOUTGOINGCALL(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideOUTGOINGCALL(void* pCusHandle,void* pWndData);
#ifdef __IP_CALL_MMI__
MAE_Ret VideoTelephonyAppWndCreateIPNUMBERLIST(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyIPNUMBERLIST(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowIPNUMBERLIST(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideIPNUMBERLIST(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateIPNUMBEREDITOR(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyIPNUMBEREDITOR(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowIPNUMBEREDITOR(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideIPNUMBEREDITOR(void* pCusHandle,void* pWndData);
#endif

MAE_Ret VideoTelephonyAppWndCreateINCALLSCREEN(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyINCALLSCREEN(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowINCALLSCREEN(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideINCALLSCREEN(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateInCallScreenMode(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyInCallScreenMode(void *pCusHandle, void *pWndData);

MAE_Ret VideoTelephonyAppWndCreateInCallScreenSource(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyInCallScreenSource(void *pCusHandle, void *pWndData);

MAE_Ret VideoTelephonyAppWndCreateINCALLEDITOR(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyINCALLEDITOR(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowINCALLEDITOR(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideINCALLEDITOR(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateMultipartyList(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyMultipartyList(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowMultipartyList(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideMultipartyList(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateMultipartyOptionMenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VideoTelephonyAppWndDestroyMultipartyOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndShowMultipartyOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret VideoTelephonyAppWndHideMultipartyOptionMenu(void* pCusHandle,void* pWndData);

MAE_Ret VideoTelephonyAppWndCreateDTMFNumberInputPopup(void* pCusHandle,void* pWndData, u32 nWndInitParam);


//============================utility===========================//
MAE_Ret VideoTelephonyAppLoadOutgoingCallView(MMI_VIDEOTELEPHONYAPP *pThis, VideoTelephonyAppOutgoingCallViewWdgList_t *pData);
MAE_Ret VideoTelephonyAppCheckDual(MMI_VIDEOTELEPHONYAPP* pThis, u8 u32SessID);
MAE_Ret VideoTelephonyAppExit(MMI_VIDEOTELEPHONYAPP* pThis);
MAE_Ret VideoTelephonyAppLoadDualMenuView(MMI_VIDEOTELEPHONYAPP *pThis);
u32 VideoTelephonyAppGetKeyCodeByGridIndex(MMI_VIDEOTELEPHONYAPP* pThis, u32 nGridIndex, MMI_VIDEOTELEPHONYAPP_TS_GRID_e eTouchGrid);
void VideoTelephonyAppGetDeviceStatus(MMI_VIDEOTELEPHONYAPP* pThis);
boolean VideoTelephonyAppIsUsbUsed(void);

void VideoTelephonyAppRecord_Done(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppRecord_Fail(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppRecord_Full(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppStopRecord(MMI_VIDEOTELEPHONYAPP* pThis);

void VideoTelephonyAppResumeSendSMS(IBase* pUser, u32 Param);

void VideoTelephonyAppDrawRecordingDialog(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppStopDrawRecordingView(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppMakeCallSuccess(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppCallEnd(MMI_VIDEOTELEPHONYAPP* pThis);
#ifdef __IP_CALL_MMI__
void VideoTelephonyAppGetIPNumber(MMI_VIDEOTELEPHONYAPP* pThis, u8 *pNum, MmiVideoTelephonyAppDuoOption_t *pDuoOption);
#endif
void VideoTelephonyAppShowOperationNotAllowScreen(MMI_VIDEOTELEPHONYAPP* pThis, u32 TextID, PFN_DlgHandler pfnDialogHdl);
void VideoTelephonyAppShowRecordingOperationNotAllowScreen(MMI_VIDEOTELEPHONYAPP* pThis, u32 TextID);
void VideoTelephonyAppAutoRedialStart(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppCallFail(MMI_VIDEOTELEPHONYAPP* pThis);

void VideoTelephonyAppShowWaitingDialog(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppWFunction(MMI_VIDEOTELEPHONYAPP *pThis);
void VideoTelephonyAppStartDTMF(MMI_VIDEOTELEPHONYAPP *pThis);
void VideoTelephonyAppStopDTMF(void* data);


#if defined(__TOUCH_SCREEN_MMI__)
void VideoTelephonyAppResumeSaveToContact(IBase* pUser, u32 Param);
#endif

void  VideoTelephonyAppInCallScreenAudioPath(MMI_VIDEOTELEPHONYAPP* pThis, u32 u32AudioPath);
MAE_Ret VideoTelephonyAppMakeCallAttempt(MMI_VIDEOTELEPHONYAPP* pThis);
#ifdef __IP_CALL_MMI__
void VideoTelephonyAppIPNumberItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
#endif
void VideoTelephonyAppAutoRedialEnd(MMI_VIDEOTELEPHONYAPP* pThis);


//============================CCSRV CB===========================//
void VideoTelephonyAppMakeCallCnfCb(void *pThis, boolean bResult, u32 nCause);
void VideoTelephonyAppMake2ndCallCnfCb(void *pThis, boolean bResult, u32 nCause);
void VideoTelephonyAppIncallSessionTimerCb(void *pThis);
void VideoTelephonyAppReleaseIndCb( void *pThis, u32 nCause );
void VideoTelephonyAppReleaseActiveCallIndCb(void *pThis, boolean bResult, u32 nCause);
void VideoTelephonyAppReleaseHoldCallIndCb(void *pThis, boolean bResult, u32 nCause);
void VideoTelephonyAppHoldCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppRetrieveCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppSwapCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppHangUpOutgoingCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppReplaceActiveCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppReleaseHoldCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppJoinMPTYCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppSplitCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppReleaseSpecificCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppAlertIndCb( void *pThis, u32 nProgID );
void VideoTelephonyAppTransferCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppHangUpCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppHangUpCallCnfExitCCappCb( void *pThis,boolean bResult,u32 nCause );
void VideoTelephonyAppDTMFCnfCb( void *pThis, boolean bResult );
void VideoTelephonyAppAbortDTMFCnfCb( void *pThis, u32 nResult );
void VideoTelephonyAppAudioChannelIndCb( void *pThis );
void VideoTelephonyAppProgressIndCb( void *pThis, u32 nProgID );
void VideoTelephonyAppInCallNotifyInd( void *pThis,u32 ServiceCode,u32 index,u32 nTonNpi,u8 *CalledNb );
void VideoTelephonyAppCallSetupNotifyIndCb( void *pThis,u32 nServiceCode,u32 nIndex );
void VideoTelephonyAppWfuncStartDTMFCnfCb( void *pThis, boolean bResult );
void VideoTelephonyAppWfuncStopDTMFCnfCb( void *pThis, boolean bResult );
void VideoTelephonyAppSrvVtCcReleaseOutgoingCallCb(void *pThis, u32 nCause);
void VideoTelephonyApp3G324MCallStateCb(void *pThis, VtCc3G324MCallState_e eState);
void VideoTelephonyAppVtmCnfOpenCb(void *pThis, VtmSrvErrCode_e eErrorCode);
MAE_Ret VideoTelephonyAppFallbackDialogCnfCb(void* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void VideoTelephonyAppChannelOnOffCb(void *pThis, VtCc3G324MOnOffState_e eState, VtCc3G324MChannelType_e eType);

//============================Alarm SRV CB===========================//
void VideoTelephonyAppAlarmExpireCb( void *pThis,ALARMSRV_ALARMALERTDATA_t *pAlarmAlertData );

#ifdef __BLUETOOTH_MMI__
//============================BT SRV CB===========================//
void VideoTelephonyAppSrvBtAudioCallIndCnfCB( void *pThis,BTSRV_StatusCode_e eResult,BTSRV_AudioCallType_e eType );
void VideoTelephonyAppSrvBtAudioLinkIndCB( void *pThis,u8 nItem,BTSRV_Link_Status_e eLinkStatus );
void VideoTelephonyAppSrvBtAtchldCB( void *pThis, u32 value ); //BTSRV_EVT_ATCHLD
void VideoTelephonyAppSrvBtAtchupCB( void *pThis ); //BTSRV_EVT_ATCHUP
void VideoTelephonyAppSrvBtAudioVolumeCB( void *pThis, s8 nVolLevel ); //BTSRV_EVT_AudioVolumeInd
#endif

//============================Media SRV CB===========================//
void VideoTelephonyAppStatusNotifyIndCb(void *pData, u32 nCusData, VtmSrvNotifyCbInfo_t *pNotifyCbInfo);
void VideoTelephonyAppRecordingInterruptIndCb(void *pData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
void VideoTelephonyAppVtmCnfStopRecordCb(void *pThis, VtmSrvErrCode_e eErrorCode);
void VideoTelephonyAppSetBlankPreviewCb(void *pThis, VtmSrvErrCode_e eErrorCode);

//============================Window CB===========================//
boolean VideoTelephonyAppStartCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VideoTelephonyAppStopCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VideoTelephonyAppKeyPressCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VideoTelephonyAppKeyLongpressCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
//boolean VideoTelephonyAppKeyReleaseCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VideoTelephonyAppResumeCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VideoTelephonyAppSuspendCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
//MAE_Ret VideoTelephonyAppGetPropertyCb(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
MAE_Ret VideoTelephonyAppConstructorCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret VideoTelephonyAppDestructorCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean VideoTelephonyAppGetProperty(IApplet *pApplet, u32 nEvt, u32 key, u32 outVal);


//============================WIDGET Wrapper CB===========================//
void VideoTelephonyAppDualSelectMenuSoftkeyActCb (void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __IP_CALL_MMI__
void VideoTelephonyAppIpNumberEditorInputWidgetTextChangeCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void VideoTelephonyAppMenuIpNumberListSoftkeyActCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
void VideoTelephonyAppMenuGrid1FocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoTelephonyAppMenuGrid2FocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void VideoTelephonyAppButtonWdg1ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
void VideoTelephonyAppButtonWdg2ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
void VideoTelephonyAppIncallEditorInputWidgetTextChangeCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void VideoTelephonyAppMPTYMenuSoftkeyActCB(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoTelephonyAppInCallEditorOptionMenuSoftkeyActCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoTelephonyAppMPTYOptionMenuSoftkeyActCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoTelephonyAppInCallEditorInputWidgetDTMFKeyInCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, DTMFData_t *pDTMFData, IWidget *pWidget);
void VideoTelephonyAppInCallOptionMenuOptionLev2Cb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoTelephonyAppIPcallInputEditorHandleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void VideoTelephonyAppScreenModeListSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoTelephonyAppScreenSourceListSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoTelephonyAppGetFileByBrowseCb(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);


//============================Timer CB===========================//
void VideoTelephonyAppIPNumberBackIncallTimerCB(void* data);
void VideoTelephonyAppIPNumberBackIdleTimerCB(void* data);
#ifdef __TOUCH_SCREEN_MMI__
void VideoTelephonyAppTsLongPressCb(void* data);
#endif //__TOUCH_SCREEN_MMI__
void VideoTelephonyAppGotoRecordingScreenCB(void *data);
void VideoTelephonyAppRedialTimerCB(void* data);

#ifdef __ANSWER_INDICATOR_MMI__
void VideoTelephonyAppAnswerReminderTimerCB(void* data);
#endif

//============================Dialog CB===========================//
MAE_Ret VideoTelephonyAppIncallScreenDialogCB(void *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);

//============================Non view template======================//
MAE_Ret _VideoTelephonyAppCreateTalkView(HWIN hWin, VideoTelephonyAppTalkViewWdgList_t *pWdgList);
MAE_Ret _VideoTelephonyAppCreateOutgoingCallView(HWIN hWin, VideoTelephonyAppOutgoingCallViewWdgList_t *pWdgList);
MAE_Ret _VideoTelephonyAppCreateIncallEditorView(HWIN hWin, VideoTelephonyAppDialingWdgList_t *pWdgList);
#ifdef __IP_CALL_MMI__
MAE_Ret _VideoTelephonyAppCreateIpNumEditorView(HWIN hWin, VideoTelephonyAppIpNumEdirotViewWdgList_t *pWdgList);
#endif
MAE_Ret _VideoTelephonyAppCreateActiveDialingView(HWIN hWin, VideoTelephonyAppDialingWdgList_t *pWdgList);

#ifdef __VIDEOTELEPHONYAPP_RECORD__
void VideoTelephonyAppVtmGetFilenameCb(void *pThis, VtmSrvErrCode_e eErrorCode, VtmSrvFileName_t *pGetFilename);
void VideoTelephonyAppSaveFileReqCb(void *pThis, VtmSrvErrCode_e eErrorCode, VtmSrvFileName_t *pGetFilename);
#endif

static void VideoTelephonyAppSrvBatteryBattLevelChangeCb(void *pUserData, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
#endif /* __MMI_VIDEOTELEPHONYAPP_PRIV_H__ */
