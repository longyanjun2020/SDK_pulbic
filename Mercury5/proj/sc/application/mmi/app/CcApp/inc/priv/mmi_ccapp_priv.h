/**
* @file mmi_ccapp_priv.h
*
* Class Id: CLSID_CCAPP
*
*/
#ifndef __MMI_CCAPP_PRIV_H__
#define __MMI_CCAPP_PRIV_H__
/*-------------------------------------------------------------------------*/
#include "mmi_common_dialog.h"
#include "mmi_ccapp.h"
#include "mmi_phbapp.h"
#include "mmi_baseapplet.h"
#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"
#include "mmi_common_wdgvar.h"
#include "mmi_ccapp_id.h"
#include "ccapp_resource.h"
#include "mmi_callsettingapp_util.h"

#define CCAPP_IPNUMBER_MAX_BYTE         (IPCALL_MAX_NUM_LEN * sizeof(MAE_WChar))
#define  MMI_CCAPP_DIGITAL_LEN	10
#define MMI_CCAPP_RECORD_VOICE_LIMIT_SIZE_IN_SECS 10

#define CCAPP_OUTGOING_TONE_TIMER 5000
#define CCAPP_CALLEND_TIMER	2000
#define CCAPP_DONE_TIMER	1000
#define CCAPP_CALLFAILED_TIMER	2000
#define CCAPP_OPERATION_NOT_ALLOW_TIMER	2000
#define CCAPP_INFORMATION_TIMER	2500
#define CCAPP_EVERYSECOND_TIMER	1000
#define CCAPP_AUTO_DTMF_TIMER	2500
#define CCAPP_STOP_DTMF_TIMER	100
#define CCAPP_TS_LONGPRESS_TIME 1500
#define CCAPP_CALL_END_TONE_TIMER	500	// Call end tone: work-around solution
#define CCAPP_CALL_INDICATOR_FLASH_ON 300
#define CCAPP_CALL_INDICATOR_FLASH_OFF 200
#define CCAPP_LOW_BATTERY_ALARM_TIMER 60 // 60s, low battery alarm interval
#define CCAPP_DTMF_COUNT_MAX 26
#ifdef __APP_MMI_CHECKDISK__
#define CCAPP_CHECKDISK_NOTIFY_TIMER	2000
#endif

#ifdef __ANSWER_INDICATOR_MMI__
#define CCAPP_ANSWER_REMINDER  1000
#endif

#ifdef __IP_CALL_MMI__
#include "mmi_common_cfg.h"
#define CCAPP_IPNUMBER_TIMER 2500
#define CCAPP_MIN_IPNUMBER 1
#endif
#define CCAPP_PUBLIC_MMI_STRING_LEN		2
#define CCAPP_CRUNCH_DONE_TIMER	1000

#define CCAPP_REDIAL_STR_LEN 60

#ifdef __FEATURE_VECTOR_FONT__
#ifdef __APP_MMI_SMALLROM__
#define CCAPP_TWO_LINE_CHAR_LENGTH ((u32)(FONTBASE_IsVectorFontExist()? (15*2):(9*3)))
#else
#define CCAPP_TWO_LINE_CHAR_LENGTH ((u32)(FONTBASE_IsVectorFontExist()? (15*2):(9*2)))
#endif
#else
#ifdef __APP_MMI_SMALLROM__
#define CCAPP_TWO_LINE_CHAR_LENGTH ( 9*3)
#else
#define CCAPP_TWO_LINE_CHAR_LENGTH ( 9*2)
#endif
#endif

enum
{
	CCAPP_DIRECTION_UNKNOWN = 0 ,
	CCAPP_MT_ANSWER_BY_BT_HEADSET,
	CCAPP_MT_ANSWER_BY_HANDSET,
	CCAPP_MT_ANSWER_BY_HEADSET_HOOK,
	CCAPP_MO_CALL,
	CCAPP_BT_RECONNECT
};
typedef u8 MMI_CCAPP_DIRECTION_BT_e;

typedef struct MMI_CCAPP_SETTING_TAG {
	u8     AutoRedial;
	u16    MinuteReminder;
}MMI_CCAPP_SETTING;

typedef enum
{
	CCAPP_TS_TOUCHGRID1,
	CCAPP_TS_TOUCHGRID2,
	CCAPP_TS_TOUCHGRID3
} MMI_CCAPP_TS_GRID_e;

typedef enum
{
	CCAPP_HANDSET,
	CCAPP_SPEAKER,
	CCAPP_BT_HEADSET,
} MMI_CCAPP_AUDIO_PATH_e;

#ifdef __IP_CALL_MMI__
typedef struct MMI_CCAPP_IPCALL_TAG{
      MmiCCAPPDuoOption_t tDuoOption;
      u32 nHeightLightID; // height ID , ID : menu ID
      u32 nKeyCode; // for editor key press
      u8 *pDialNum;
}MMI_CCAPP_IPCALL_t;
#endif

typedef enum
{
	CCAPP_IFONE_UNKNOWN = 0 ,
	CCAPP_IFONE_PHONEBOOK,
	CCAPP_IFONE_MESSAGE
} MMI_CCAPP_IFONE_START_AP_e;

/*
typedef enum
{
	MMI_COMMON_VIEW_DIALOG = 0 ,
	MMI_COMMON_VIEW_OPTION_MENU,
	MMI_COMMON_VIEW_POPUP
} MMI_COMMON_VIEW_TYPE_e;
*/


#ifdef __UI_STYLE_MMI_IFONE__
typedef struct CcAppTalkViewWdgList_t_
{
    IWidget *pCallInfoCntr;

    IWidget *pCallInfoTextWdg;
    IWidget *pHoldCallInfoTextWdg;	
    IWidget *pHoldTextWdg;	
    IWidget *pTimerWdg;	
    IWidget *pInputWidget;
    IWidget *pMptyBtnWdg;
	
    IWidget *pBtnCntr;

    IWidget *pMuteBtnWdg;
    IWidget *pKeypadBtnWdg;
    IWidget *pSpeakerBtnWdg;
    IWidget *pVolumeBtnWdg;

    IWidget *pOp1BtnWdg;
    IWidget *pOp2BtnWdg;
    IWidget *pContactBtnWdg;

    IWidget *pGridWdg;

    IWidget *pOpCntr;
    IWidget *pEndCallBtnWdg;
    IWidget *pHideKeypadBtnWdg;

}CcAppTalkViewWdgList_t;
#else
typedef struct CcAppTalkViewWdgList_t_
{
    IWidget *pCallScreenBgImgWdg;
    IWidget *pMainContainer;
    IWidget *pImgAreaContainer;
    IWidget *pMptyImgWdg1;
    IWidget *pMptyImgWdg2;
    IWidget *pMptyImgWdg3;
    IWidget *pMptyImgWdg4;
    IWidget *pMptyImgWdg5;
    IWidget *pTimeAreaContainer;
    IWidget *pDuoImgWdg;
    IWidget *pRecordImgWdg;
    IWidget *pTimerWdg;
    IWidget *pMuteImgWdg;
    IWidget *pTextAreaContainer;
    IWidget *pTextAreaBgImgWdg;
    IWidget *pCallInfoImgWdg1;
    IWidget *pCallInfoTextWdg1;
    IWidget *pCallInfoMptyListWdg;
    IWidget *pCallInfoImgWdg2;
    IWidget *pCallInfoTextWdg2;
} CcAppTalkViewWdgList_t;
#endif
#ifdef __UI_STYLE_MMI_IFONE__
typedef struct CcAppOutgoingCallViewWdgList_t_
{
    IWidget *pCallInfoCntr;
    IWidget *pCallInfoTextWdg;	
    IWidget *pDuoStateImgWdg;	
    IWidget *pOutgoingCallImgWdg;
    IWidget *pOutgoingCallTextAreaBgImgWdg;
    IWidget *pCallStatesTextWdg;
    IWidget *pOutgoingInputWidget;
    IWidget *pOutgoingGridWdg;
    IWidget *pOutgoingHideKeypadBtnWdg;
    IWidget *pBtnCntr;
    IWidget *pMuteBtnWdg;
    IWidget *pKeypadBtnWdg;
    IWidget *pSpeakerBtnWdg;
    IWidget *pOp1BtnWdg;
    IWidget *pOp2BtnWdg;
    IWidget *pContactBtnWdg;
    IWidget *pVolumeBtnWdg;

    IWidget *pOpCntr;
    IWidget *pEndCallBtnWdg;
    IWidget *pHideDialBtnWdg;

}CcAppOutgoingCallViewWdgList_t;
#else
typedef struct CcAppOutgoingCallViewWdgList_t_
{
    IWidget *pCallScreenBGWdg;
    IWidget *pMainContainer;
    //IWidget *pImgAreaContainer;
    IWidget *pOutgoingCallImgWdg;
    IWidget *pOutgoingCallTextAreaBgImgWdg;
    //IWidget *pTextAreaContainer;
    IWidget *pCallStatesTextWdg;
    IWidget *pCallInfoTextWdg;
    IWidget *pDuoStateTextWdg;
#ifdef __CALLER_LOCATION__
    IWidget *pCallLocationTextWdg;
#endif    
} CcAppOutgoingCallViewWdgList_t;
#endif
typedef struct CcAppDialingWdgList_t_
{
    IWidget *pMainContainer;
    IWidget *pInputWidget;
    IWidget *pShortcutWidget;
#ifdef __TOUCH_SCREEN_MMI__
    IWidget *pGridWdg1;
    IWidget *pButtonWdg1;
    IWidget *pGridWdg2;
    IWidget *pButtonWdg2;
    IWidget *pGridWdg3;
    IWidget *pButtonWdg3;
#ifdef __CCAPP_SMALLROM__
	IWidget *pButtonAbsContainer;
	IWidget *pButtonBgImageWdg;
#endif	// !__CCAPP_SMALLROM__
#endif
} CcAppDialingWdgList_t;


typedef struct CcAppIpNumEdirotViewWdgList_t_
{
    IWidget *pInputWdg;
} CcAppIpNumEdirotViewWdgList_t;

#ifdef __DISTORTED_VOICE_MMI__
typedef struct CcAppDistortedEffectWndData_t_
{
    MenuWdgList_t tWdgList;
} CcAppDistortedEffectWndData_t;

#endif

 
typedef struct CcAppFullRecordingWdgList_t_
{
	IWidget *pMainContainer;
	IWidget *pBgImgWdg;
	IWidget *pCallInfoTextWdg;
	IWidget *pInfoTextWdg;
	IWidget *pDurationTextWdg;  
} CcAppFullRecordingWdgList_t;

#ifdef __APP_MMI_ANSWERING_MACHINE__
typedef struct CcAppAnsweringMachineWdgList_t_
{
	IWidget *pMainContainer;
	IWidget *pBgImgWdg;
	IWidget *pRecordImgWdg;
	IWidget *pCallInfoTextWdg;
	IWidget *pInfoTextWdg;
	IWidget *pWaitingTextWdg;  
} CcAppFullAnsweringMachineWdgList_t;
#endif


 /**
 * Application structure
 */
typedef struct MMI_CCAPP_TAG {
    APPLET_BASE_ELEMENTS;
	CallTable_t		*pCallTableCache;
	MMI_CC_AP_FID_E	fid;
	MmiMakeCallReq_t* ptMakeCallReq;
	MMI_CCAPP_DIRECTION_BT_e	BTDirection;	// Decide CCAPP have to connect SCO link or not

	u8				u8SessDualId;
	COMMON_SIM_CARD_STATUS_e DuoSimStatus;
#ifdef __UI_STYLE_MMI_IFONE__
#ifdef __BLUETOOTH_MMI__
	boolean		bBtAudioLink;			// Flag for BtAudioLink state	(TRUE-->BtAudioLink On	,FALSE-->BtAudioLink Off)
	boolean		bSwitch;			// Flag for BtAudioLink state	(TRUE-->BtAudioLink On	,FALSE-->BtAudioLink Off)
#endif
#endif
	boolean		bSpeakerOn;			// Flag for Speaker state	(TRUE-->Speaker On	,FALSE-->Speaker Off)
	boolean		bMuteState;			// Flag for Mute State		(TRUE-->Mute		,FALSE-->Unmute)
	boolean		bRecordState;		// Flag for Record State	(TRUE-->Record		,FALSE-->Stop record)
	boolean		bIdle;				// Flag for close cc ap 	(TRUE --> gotoIdle, FALSE --> still active)
	boolean 	bDTMF;				// Flag for DTMF reauest  	(TRUE --> enable, FALSE --> disable)
	boolean     bAlertFlag;         // Flag for alert state
	boolean     bAudioChannelFlag;  // Flag for audio channel opened or not
	boolean     bUserAttachFlag;    // Flag for keep user attached or not
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

    //For keep MAE_MSG_BASE_KBD hook state
    boolean bHookKBDEvt;

	boolean	bRemotePartyEndCall;
	MMI_CCAPP_SETTING CallSetting;

	WidgetHandler_t DialogViewHdlData;
	WidgetHandler_t NotificationViewHdlData;
	// For Record
	MAE_WChar *pRecordingFilePath;
#ifdef __TOUCH_SCREEN_MMI__
	MMI_CCAPP_TS_GRID_e eTouchGrid;
	boolean bLongPressed;
	boolean bDigitInput;
#endif
#ifdef __IP_CALL_MMI__
    MMI_CCAPP_IPCALL_t *pIPCAll;
    //boolean bShortPress;
	MAE_WChar *pstrIPNum;
#endif

	SetDisplayMenuStyle_e eMenuStyle;

    //For keep volume level
    boolean                 bUpdateVolume;
    SetRingToneVolume_e     eVolume;

    //For keep InCallEditor status
    boolean bEnableOptionMenu;

    //For recording dialog
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
    boolean bIsOpenAudioSession;
#ifdef __IP_CALL_MMI__
    boolean bIsBackToIPCall;
#endif
	boolean bHandlingInCallEditorSendAction;
    boolean bMake2ndCallRequested; // if TRUE, means ccapp has made 2nd call request succesfully. ccapp will set this flag to FALSE when 2nd call cnf is received.
    boolean bResumeMakeCall;
	boolean bIsShowRecordingDlg;
	boolean bLowBatteryAlarmInCall;
	u32 u32LowBatteryAlarmStartTime;
	boolean bReplacingActiveCall;
    boolean bSTKCall;
    boolean bIsSendMakeCallReq;
    MmiCCAPPDuoOption_t tDuoOption;
	boolean bFirstEntry; // if TRUE, means it is the first time to enter CCApp
	boolean bCurIPCall; // indicate if the current outgoing call is IP call	
	boolean bHangingUp2ndOutgoingCall; // Flag to indicate if hanging up 2nd outgloing call is in progrss.
	AudioEnvSrvPrefAudPath_e ePrefAudPath; // The current prefer audio path
	IImage *pContactImage;
	boolean bDTMFKeyPressed;
	u8 u8DTMFKeyCode;
	boolean bSwapCall;
	boolean bJoinCall;
	boolean bHoldCall;
#ifdef __APP_MMI_ANSWERING_MACHINE__
	boolean bPlayBeep;
	boolean bAnsweringMachineMode;
	ANSWERING_MACHINE_FAILED_TYPE_e eAnsweringMachineFailedType;
	boolean bAMRecordedFileSaved; // indicate if the recorded file created by AnswerMachine is saved successfully, if TRUE, then we will prompt the user.
	boolean bAMStopPlaying; // indicates if leaving the AnswerMachine mode which playing greeting sound and beep
	//boolean bAMStopRecord; // indicate if leaving the Recording mode caused by AnswerMachine
	MAE_WChar *pstrAMNameOrNumber;
	boolean bAMChangeAudioPath;
#endif
#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
	// CBS stands for CallBackgroundSound
	boolean bCBSStatus, bLogHistory, bShowInfoDlg, bPlayingCBS, bPlayCBSAgain, bSubjectRequest;
	CallBgSound_Play_Type_e eCBSPlayType;
	u8 u8CBSPlayInterval, u8CBSCurEffectSound;
	SetRingToneVolume_e eCBSVolume;
	MAE_WChar *pITextLine2PlayType, *pITextLine2EffectSound, *pITextLine2Volume, *pIntervalText;
	u16 u16LogFirstItemIndex, u16LogHighlightIndex;
	MMI_USB_STATUS_E ePreUsbStatus;
#endif
	u32 nMakeCallRefID;
	CmnAppLaunchRspCbInfo_t tRspCbInfo;
	boolean bBTScoOnProcessing;
#ifdef __AUTO_RECORDING_MMI__
	boolean bAutoRecording;
#endif
} MMI_CCAPP;


MAE_Ret CcAppWndDualMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndOutgoingCallHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __IP_CALL_MMI__
MAE_Ret CcAppWndIPNumberListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndIPNumberEditorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret CcAppWndInCallScreenHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndInCallScreenRecordingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifndef __UI_STYLE_MMI_IFONE__
MAE_Ret CcAppWndInCallScreenOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndInCallEditorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndInCallEditorOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret CcAppWndMultipartyListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndMultipartyOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDTMFNumberInputPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

MAE_Ret CcAppWndRecordingScreenHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndCreateRecordingScreen(void* pCusHandle,void* pWndData, u32 nWndInitParam);
#ifdef __APP_MMI_ANSWERING_MACHINE__
MAE_Ret CcAppWndAnsweringMachineScreenHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndCreateAnsweringMachineScreen(void* pCusHandle,void* pWndData, u32 nWndInitParam);
#endif
void CcAppRecordingRSKHandling(MMI_CCAPP *pThis);

MAE_Ret CcAppWndCreateDUALMENU(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyDUALMENU(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetDUALMENU(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowDUALMENU(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideDUALMENU(void* pCusHandle,void* pWndData);

MAE_Ret CcAppWndCreateOUTGOINGCALL(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyOUTGOINGCALL(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetOUTGOINGCALL(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowOUTGOINGCALL(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideOUTGOINGCALL(void* pCusHandle,void* pWndData);
#ifdef __IP_CALL_MMI__
MAE_Ret CcAppWndCreateIPNUMBERLIST(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyIPNUMBERLIST(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetIPNUMBERLIST(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowIPNUMBERLIST(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideIPNUMBERLIST(void* pCusHandle,void* pWndData);

MAE_Ret CcAppWndCreateIPNUMBEREDITOR(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyIPNUMBEREDITOR(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetIPNUMBEREDITOR(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowIPNUMBEREDITOR(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideIPNUMBEREDITOR(void* pCusHandle,void* pWndData);
#endif

MAE_Ret CcAppWndCreateINCALLSCREEN(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyINCALLSCREEN(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetINCALLSCREEN(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowINCALLSCREEN(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideINCALLSCREEN(void* pCusHandle,void* pWndData);

#ifndef __UI_STYLE_MMI_IFONE__
MAE_Ret CcAppWndCreateINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideINCALLSCREENOptionMenu(void* pCusHandle,void* pWndData);

MAE_Ret CcAppWndCreateINCALLEDITOR(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyINCALLEDITOR(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetINCALLEDITOR(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowINCALLEDITOR(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideINCALLEDITOR(void* pCusHandle,void* pWndData);

MAE_Ret CcAppWndCreateINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideINCALLEDITOROptionMenu(void* pCusHandle,void* pWndData);
#endif

MAE_Ret CcAppWndCreateMultipartyList(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyMultipartyList(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetMultipartyList(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowMultipartyList(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideMultipartyList(void* pCusHandle,void* pWndData);

MAE_Ret CcAppWndCreateMultipartyOptionMenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndDestroyMultipartyOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndSetMultipartyOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndShowMultipartyOptionMenu(void* pCusHandle,void* pWndData);
MAE_Ret CcAppWndHideMultipartyOptionMenu(void* pCusHandle,void* pWndData);

MAE_Ret CcAppWndCreateDTMFNumberInputPopup(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcAppWndSetDTMFNumberInputPopup(void* pCusHandle,void* pWndData);

//============================utility===========================//
MAE_Ret CcAppLoadOutgoingCallView(MMI_CCAPP *pThis, CcAppOutgoingCallViewWdgList_t *pData);
MAE_Ret CcAppCheckDual(MMI_CCAPP* pThis, u8 u32SessID);
MAE_Ret CcAppExit(MMI_CCAPP* pThis);
MAE_Ret CcAppLoadDualMenuView(MMI_CCAPP *pThis);
u32 CcAppGetKeyCodeByGridIndex(MMI_CCAPP* pThis, u32 nGridIndex, MMI_CCAPP_TS_GRID_e eTouchGrid);
void CcAppGetDeviceStatus(MMI_CCAPP* pThis);
boolean CcAppIsUsbUsed(void);

void CcAppRecord_Done(MMI_CCAPP* pThis);
void CcAppRecord_Fail(MMI_CCAPP* pThis);
void CcAppRecord_Full(MMI_CCAPP* pThis);
void CcAppStartRecord(MMI_CCAPP* pThis);
void CcAppStopRecord(MMI_CCAPP* pThis);

void CcAppResumeSendSMS(IBase* pUser, u32 Param);
#ifdef __MMS_MMI_CDMMS__                            
void CcAppResumeSendMMS(IBase* pUser, u32 Param);
#endif

void CcAppDrawRecordingDialog(MMI_CCAPP* pThis);
void CcAppMakeCallSuccess(MMI_CCAPP* pThis);
void CcAppCallEnd(MMI_CCAPP* pThis);
#ifdef __IP_CALL_MMI__
void CcAppGetIPNumber(MMI_CCAPP* pThis, u8 *pNum, MmiCCAPPDuoOption_t *pDuoOption);
#endif
void CcAppShowOperationNotAllowScreen(MMI_CCAPP* pThis, u32 TextID, PFN_DlgHandler pfnDialogHdl);
void CcAppShowRecordingOperationNotAllowScreen(MMI_CCAPP* pThis, u32 TextID);
void CcAppAutoRedialStart(MMI_CCAPP* pThis);
void CcAppCallFail(MMI_CCAPP* pThis);

void CcAppShowWaitingDialog(MMI_CCAPP* pThis);
void CcAppWFunction(MMI_CCAPP *pThis);
void CcAppStartDTMF(MMI_CCAPP *pThis);
void CcAppStopDTMF(void* data);


#if defined(__TOUCH_SCREEN_MMI__)
void CcAppResumeSaveToContact(IBase* pUser, u32 Param);
#endif

void  CcAppInCallScreenAudioPath(MMI_CCAPP* pThis, u32 u32AudioPath);
MAE_Ret CcAppMakeCallAttempt(MMI_CCAPP* pThis);
#ifdef __IP_CALL_MMI__
void CcAppIPNumberItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
#endif
void CcAppAutoRedialEnd(MMI_CCAPP* pThis);
static void CcAppCheckDualAndEmergencyBeforeMakeCall(MMI_CCAPP* pThis);
void CcAppMakeIPorNormalCall(MMI_CCAPP* pThis);
void CcAppParseMakeCallReq(MMI_CCAPP* pThis, MmiCCAPPMakeCallReq_t *ptMakeCallReq);

//============================CCSRV CB===========================//
void CcAppMakeCallCnfCb(void *pThis, boolean bResult, u32 nCause);
void CcAppMake2ndCallCnfCb(void *pThis, boolean bResult, u32 nCause);
void CcAppIncallSessionTimerCb(void *pThis);
void CcAppReleaseIndCb( void *pThis, u32 nCause );
void CcAppReleaseActiveCallIndCb(void *pThis, boolean bResult, u32 nCause);
void CcAppReleaseHoldCallIndCb(void *pThis, boolean bResult, u32 nCause);
void CcAppHoldCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppRetrieveCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppSwapCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppHangUpOutgoingCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppReleaseActiveCallCnfCb( void *pThis,boolean bResult,u32 nCause );
//void CcAppReplaceActiveCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppReleaseHoldCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppJoinMPTYCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppSplitCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppReleaseSpecificCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppAlertIndCb( void *pThis, u32 nProgID );
void CcAppTransferCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppHangUpCallCnfCb( void *pThis,boolean bResult,u32 nCause );
void CcAppHangUpCallCnfExitCCappCb( void *pThis,boolean bResult,u32 nCause );
void CcAppDTMFCnfCb( void *pThis, boolean bResult );
void CcAppAbortDTMFCnfCb( void *pThis, u32 nResult );
void CcAppAudioChannelIndCb( void *pThis );
void CcAppProgressIndCb( void *pThis, u32 nProgID );
void CcAppInCallNotifyInd( void *pThis,u32 ServiceCode,u32 index,u32 nTonNpi,u8 *CalledNb );
void CcAppCallSetupNotifyIndCb( void *pThis,u32 nServiceCode,u32 nIndex );
void CcAppWfuncStartDTMFCnfCb( void *pThis, boolean bResult );
void CcAppWfuncStopDTMFCnfCb( void *pThis, boolean bResult );
void CcAppSrvCcReleaseOutgoingCallCb(void *pThis, u32 nCause);
static void CcAppSrvBatteryBattLevelChangeCb(void *pUserData, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
void CcAppCallRefIDIndCb(void *pThis, u32 nCause);
void CcAppMakeCallRsp(MMI_CCAPP *pThis, CcAppRspType_e nRspType, boolean bMakeCallCnf, u32 nCallRefID);


//============================Alarm SRV CB===========================//
void CcAppAlarmExpireCb( void *pThis,ALARMSRV_ALARMALERTDATA_t *pAlarmAlertData );

#ifdef __BLUETOOTH_MMI__
//============================BT SRV CB===========================//
void CcAppSrvBtAudioCallIndCnfCB( void *pThis,BTSRV_StatusCode_e eResult,BTSRV_AudioCallType_e eType );
void CcAppSrvBtAudioLinkIndCB( void *pThis,u8 nItem,BTSRV_Link_Status_e eLinkStatus );
void CcAppSrvBtAtchldCB( void *pThis, u32 value ); //BTSRV_EVT_ATCHLD
void CcAppSrvBtAtchupCB( void *pThis ); //BTSRV_EVT_ATCHUP
void CcAppSrvBtAudioVolumeCB( void *pThis, s8 nVolLevel ); //BTSRV_EVT_AudioVolumeInd
#ifdef __BLUETOOTH_A2DP_MMI__
void CcAppSrvBtA2dpStreamingStatusChangeCB(void *pThis, BTSRV_A2dpStreamingStatus_e);
#endif // __BLUETOOTH_A2DP_MMI__
#endif

//============================Media SRV CB===========================//
void CcAppAudioRecorderSrvStartCb(void *pThis, MediaSrvErrCode_e eErrorCode);
void CcAppAudioRecorderSrvStopCb(void *pThis, MediaSrvErrCode_e eErrorCode, AudioRecSrvFileInfo_t *pFileInfo);
void CcAppRecordingStatusIndCB(void *pData, u32 nCusData, AudioRecSrvStatusInd_e nStatus,AudioRecSrvStatusNotifyInfo_t *pInfo);
void CcAppRecordingInterruptIndCb(void *pData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
//============================Window CB===========================//
boolean CcAppStartCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcAppStopCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcAppKeyPressCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcAppKeyLongpressCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcAppKeyReleaseCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcAppResumeCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcAppSuspendCb(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
//MAE_Ret CcAppGetPropertyCb(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
MAE_Ret CcAppConstructorCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret CcAppDestructorCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean CcAppGetProperty(IApplet *pApplet, u32 nEvt, u32 key, u32 outVal);


//============================WIDGET Wrapper CB===========================//
void CcAppDualSelectMenuSoftkeyActCb (void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __IP_CALL_MMI__
void CcAppIpNumberEditorInputWidgetTextChangeCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void CcAppMenuIpNumberListSoftkeyActCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
void CcAppMenuGrid1FocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CcAppMenuGrid2FocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifndef __CCAPP_SMALLROM__
void CcAppMenuGrid3FocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
void CcAppButtonWdg1ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
void CcAppButtonWdg2ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
#ifndef __CCAPP_SMALLROM__
void CcAppButtonWdg3ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
#endif
void CcAppButtonWdgInvalidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
void CcAppIncallEditorInputWidgetTextChangeCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void CcAppMPTYMenuSoftkeyActCB(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CcAppInCallEditorOptionMenuSoftkeyActCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CcAppMPTYOptionMenuSoftkeyActCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CcAppInCallEditorInputWidgetDTMFKeyInCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, DTMFData_t *pDTMFData, IWidget *pWidget);
void CcAppInCallOptionMenuOptionLev2Cb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CcAppIPcallInputEditorHandleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

#ifdef __UI_STYLE_MMI_IFONE__
void CcAppMuteButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppOutgoingKeypadButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppKeypadButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppSpeakerButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppOp1ButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppOp2ButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppContactButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppOutgoingHideKeypadButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppHideKeypadButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppEndCallButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppMptyButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcAppVolumeButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
#endif

//============================Timer CB===========================//
void CcAppIPNumberBackIncallTimerCB(void* data);
void CcAppIPNumberBackIdleTimerCB(void* data);
#ifdef __TOUCH_SCREEN_MMI__
void CcAppTsLongPressCb(void* data);
#endif //__TOUCH_SCREEN_MMI__
void CcAppGotoRecordingScreenCB(void *data);
void CcAppRedialTimerCB(void* data);

#ifdef __ANSWER_INDICATOR_MMI__
void CcAppAnswerReminderTimerCB(void* data);
#endif

//============================Dialog CB===========================//
MAE_Ret CcAppIncallScreenDialogCB(void *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret CcAppRecordInfoDialogCB(void *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);

//============================Non view template======================//
MAE_Ret _CcAppCreateTalkView(HWIN hWin, CcAppTalkViewWdgList_t *pWdgList);
MAE_Ret _CcAppCreateOutgoingCallView(HWIN hWin, CcAppOutgoingCallViewWdgList_t *pWdgList);
MAE_Ret _CcAppCreateIncallEditorView(HWIN hWin, CcAppDialingWdgList_t *pWdgList);
MAE_Ret _CcAppCreateActiveDialingView(HWIN hWin, CcAppDialingWdgList_t *pWdgList);

//============================Distorted Voice===========================//
#ifdef __DISTORTED_VOICE_MMI__
static void CcAppShowDistortedEffectList(MMI_CCAPP *pThis, u32 nParam1, u32 nParam2);
static MAE_Ret CcAppWndDistortedEffectListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CcAppDistortedEffectListCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static void CcAppDistortedVoiceSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CcAppDistortedVoiceDataRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
#endif

#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
static void CcAppSrvCBSSettingChangeCb(void *pUserData, u32 eCFGItemID, u8 u8Data);
static void CcAppCBSGetSettingsFromSrv(MMI_CCAPP *pThis);
static void CcAppCBSGetSettingsFromCfg(MMI_CCAPP *pThis);
static void CcAppShowCallBgSndOption(MMI_CCAPP *pThis);
static MAE_Ret CcAppCallBgSndOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret CcAppCreateCallBgSndOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static void CcAppCallBgSndOptionGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
static void CcAppCallBgSndOptionFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void CcAppCallBgSndOptionSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void CcAppUsbStatusChangedCB(void *pThis, MMI_USB_STATUS_E eUsbStatus);
#endif

#if defined(__APP_MMI_CHECKDISK__)
static boolean _CcAppCheckDisk(void *pApplet);
#endif

#endif /* __MMI_CCAPP_PRIV_H__ */
