/**
* @file mmi_ccmtaapp_priv.h
*
* Class Id: CLSID_CCMTA
*
*/
#ifndef __MMI_CCMTAAPP_PRIV_H__
#define __MMI_CCMTAAPP_PRIV_H__

#include "mmi_common_dialog.h"
#include "mmi_mae_common_def.h"
#include "mmi_ccmtaapp.h"

#include "mmi_phbapp.h"
#include "mmi_common_cfg.h"
#include "mmi_baseapplet.h"

#include "mmi_common_vtm.h"
#include "mmi_common_wdgvar.h"

#include "mmi_ccmtaapp_id.h"
#include "ccmtaapp_resource.h"


#define CCAPP_NOTIFICATION_TIMER	2500
#define CCAPP_STOP_MEDIA_AGAIN_TIMER	200
#define CCMTA_AUTO_ANSWER_TIMER 2000
#ifdef __APP_MMI_ANSWERING_MACHINE__
#define CCMTA_AM_RECORD_VOICE_LIMIT_SIZE_IN_SECOND 10
#endif

enum
{
	PickCall_None =0,
	PickCall_InComing,
	PickCall_Waiting,
};
typedef u8 PickCallType_e;

enum
{
	ReplaceWaitingCallIn_None = 0,
	ReplaceWaitingCallIn_Active,
	ReplaceWaitingCallIn_Held,
};
typedef u8 ReplaceWaitingCallInType_e;

enum
{
	CCMTA_STATUS_NONE = 0,
	CCMTA_STATUS_REQ,
	CCMTA_STATUS_CNF,
	CCMTA_STATUS_RET_ERROR
};
typedef u8 CCMTA_STOP_AUDIO_STATUS_e;

enum
{
	CCMTA_RING_STATUS_NONE = 0,
	CCMTA_RING_STATUS_PLAYING,
	CCMTA_RING_STATUS_PLAYED,
	CCMTA_RING_STATUS_STOPPING,
	CCMTA_RING_STATUS_STOPPED,
	CCMTA_RING_STATUS_RET_ERR
};
typedef u8 CCMTA_RING_STATUS_e;


#ifdef __UI_STYLE_MMI_IFONE__
typedef struct CcMtaIncomingCallViewWdgList_t_
{
    IWidget *pCallInfoCntr;
    IWidget *pCallInfoTextWdg;	
    IWidget *pDuoStateImgWdg;	
    IWidget *pCallImgWdg;
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
	IWidget *pIncomingCallVideoOsdWdg;
	IWidget *pIncomingCallVideoFirstFrameImgWdg;
#endif
    IWidget *pBtnCntr;
    IWidget *pRejectBtnWdg;
    IWidget *pHoldBtnWdg;
    IWidget *pOpCntr;
    IWidget *pEndCallBtnWdg;
    IWidget *pAnswerCallBtnWdg;
    IWidget *pCallStateTextWdg;
}CcMtaIncomingCallViewWdgList_t;
#else
typedef struct CcMtaIncomingCallViewWdgList_t_
{
    IWidget *pCallScreenBGWdg;
    IWidget *pMainContainer;
    IWidget *pImgAreaContainer;
    IWidget *pIncomingCallImgWdg;
    IWidget *pIncomingCallTextAreaBgImgWdg;
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
	IWidget *pIncomingCallVideoOsdWdg;
	IWidget *pIncomingCallVideoFirstFrameImgWdg;
#endif
    IWidget *pTextAreaContainer;
    IWidget *pCallInfoTextWdg;
    IWidget *pCallStateTextWdg;
    IWidget *pDuoStateTextWdg;

#ifdef __CALLER_LOCATION__
    IWidget *pCallLocationTextWdg;
#endif
} CcMtaIncomingCallViewWdgList_t;
#endif

typedef struct CcMtaPetIncomingCallViewWdgList_t_
{
    IWidget *pContainer;
    IWidget *pNoSbContainer;
    IWidget *pBgContainer;
    IWidget *pBgImgWdg;
    IWidget *pIncomingCallImgWdg;
    IWidget *pDuoStateImgWdg;
    IWidget *pCallInfoTextWdg;
    IWidget *pCallStateTextWdg;
    IWidget *pIncomingAliveWdgDog;
	
#ifdef __CALLER_LOCATION__
    IWidget *pCallLocationTextWdg;
#endif
} CcMtaPetIncomingCallViewWdgList_t;

/**
 * Application structure
 */
typedef struct MMI_CCMTA_TAG {
    APPLET_BASE_ELEMENTS;
	boolean		bFreePossible;			// Use this flag to judge CCMta could be free or not
	boolean		bFreeStartup;			// Use this flag to release CCMta, use at APP startup stage, not Active stage
	CallTable_t		*pCallTableCache;

#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
	boolean		bStopVideoToneAgain;
#endif
    u8          u8RingtoneState; //For keep ringtone play state
	boolean		bMuteByUser;
	CcMtaIncomingCallViewWdgList_t tIncomingCallViewWdgList;
	CcMtaPetIncomingCallViewWdgList_t tPetIncomingCallViewWdgList;

	IWidget		*pCallInfo;
	IWidget		*pCallState;
	IWidget		*pImgWdg;
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
	IWidget 	*pVideoWdg; 
	IWidget		*pVideoFirstFrameImageWdg;
    MMI_Common_Location_Type_e eVideoLocType;
#endif
	IWidget 	*pImgContainer;

	u8				u8SessDualId;
	u8		        u8AnswerBy;
	u8				*pPubMmiStr;
	PickCallType_e	ePickupCall;		// This flag will be set if Answer the MT call, use this flag to Launch CCAPP if receive IMedia_Stop Callback (To avoid audio conflict between CCMTA and CCAPP)
	//CCMTA_STOP_AUDIO_STATUS_e eAudioStatus;
	boolean		bFromWaitingCall;    // For Pet incoming. Avoid draw Pet incoming for Waiting->Incoming case

	// Widget for Option Menu View
	IWidget		*pOptMenuWdg;
	// record the toneplay setting for ringtone playing  after vibration
	SetRingToneVolume_e	eRingVolume ;
	SetRingToneRingType_e eRingType ;
	u32 nPhbRingID;
 	boolean bRejctCall;
	boolean		bShowPet;
	SetDisplayMenuStyle_e eMenuStyle;

	boolean bShowNotify;
	u32 u32ServiceCode, u32Index;
	ReplaceWaitingCallInType_e eReplaceWaitingCallIn;
	boolean bPlayingRingtone;	
	IImage *pContactImage;
	MMI_Common_Location_Type_e eContactRingtoneLocType;
#ifdef __DISTORTED_VOICE_MMI__
	boolean bIsSetDistortedVoice;
#endif
#ifdef __APP_MMI_ANSWERING_MACHINE__
	boolean bEnableAnsweringMachine;
	boolean bAnsweringMachineTimeout;
	u8 u8TimerAfterRing;
	ANSWERING_MACHINE_FAILED_TYPE_e eAnsweringMachineFailedType;
#endif
#ifdef __APP_VIDEO_TELEPHONY__
	CallTable_t		*pVtCallTableCache;
	boolean isVideoCall;
    boolean isLaunchVT;
	boolean isFallback;
	u8 *pFallbackNumber;
#endif
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
	boolean bOpenVideoSession, bPlayAgain, bVideoPlaying, bAnswerCall, bCallReleased;
	u32 u32VideoID;
#endif
#ifdef __AUTO_ANSWER_MMI__
    boolean isAutoAnswered;
#endif
} MMI_CCMTA;


MAE_Ret CcMtaConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret CcMtaDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);

boolean CcMtaAppStartCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcMtaKeyPressCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcMtaKeyLongPressCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcMtaKeyReleaseCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcMtaAppResumeCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcMtaAppSuspendCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean CcMtaAppStopCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);



void CcMtaSrvCcReleaseSpecificCallCB( void *pThis, boolean bResult,u32 nCause );
void CcMtaSrvCcReleaseActiveCallCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcReleaseHoldCallCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcRejectWaitingCallCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcAcceptCallCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcReplaceActiveInWaitingCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcReplaceHoldInWaitingCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcTransferCallCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcHangUpCallCB( void *pThis,boolean bResult,u32 nCause );
void CcMtaSrvCcAllCallReleasedCB( void *pThis );
void CcMtaSrvCcInCallNotifyCB( void *pThis, u32 ServiceCode,u32 index,u32 nTonNpi,u8 *CalledNb );
void CcMtaSrvCcWaitingToIncomingCall( void *pThis );
void CcMtaSrvCcReleaseIncomingCallCB( void *pThis, u32 nCause );
void CcMtaSrvCcReleaseWaitingCallCB( void *pThis, u32 nCause );
void CcMtaSrvCcReleaseCB( void *pThis, u32 nCause );


void CcMtaWaitingToIncomingTimerCb(void* pUserData);
void CcMtaAccessoryNotifyCb(void *pThis, u32 nCusData, MediaSrvAccessoryStatus_e nStatus);



MAE_Ret CcMtaWndCreateIncomingcall(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcMtaWndDestroyIncomingcall(void* pWndHandle, void* pWndData);
MAE_Ret CcMtaWndSetIncomingcall(void* pWndHandle, void* pWndData);
MAE_Ret CcMtaWndShowIncomingcall(void* pWndHandle, void* pWndData);
MAE_Ret CcMtaWndHideIncomingcall(void* pWndHandle, void* pWndData);

MAE_Ret CcMtaWndCreateWaitingcall(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcMtaWndDestroyWaitingcall(void* pCusHandle,void* pWndData);
MAE_Ret CcMtaWndSetWaitingcall(void* pCusHandle,void* pWndData);
MAE_Ret CcMtaWndShowWaitingcall(void* pCusHandle,void* pWndData);
MAE_Ret CcMtaWndHideWaitingcall(void* pCusHandle,void* pWndData);

MAE_Ret CcMtaWndCreateWaitingcallOptionmenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcMtaWndDestroyWaitingcallOptionmenu(void* pCusHandle,void* pWndData);
MAE_Ret CcMtaWndSetWaitingcallOptionmenu(void* pCusHandle,void* pWndData);
MAE_Ret CcMtaWndShowWaitingcallOptionmenu(void* pCusHandle,void* pWndData);
MAE_Ret CcMtaWndHideWaitingcallOptionmenu(void* pCusHandle,void* pWndData);

void CcMtaReplaceOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#ifdef __BLUETOOTH_MMI__
void CcMtaSrvBtAudioLinkIndCB(void *pThis, u8 nItem, BTSRV_Link_Status_e eLinkStatus); //BTSRV_EVT_AudioCallInd
void CcMtaSrvBtAudioCallIndCB( void *pThis, BTSRV_StatusCode_e eResult, BTSRV_AudioCallType_e eType ); //BTSRV_EVT_AudioCallInd
void CcMtaSrvBtAtaCB( void *pThis ); //BTSRV_EVT_ATA
void CcMtaSrvBtAtchldCB( void *pThis, u32 value ); //BTSRV_EVT_ATCHLD
void CcMtaSrvBtAtchupCB( void *pThis ); //BTSRV_EVT_ATCHUP
#endif
#ifdef __UI_STYLE_MMI_IFONE__
void CcMtaAppRejectButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcMtaAppHoldButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcMtaAppAnswerCallButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void CcMtaAppEndCallButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

#endif

MAE_Ret _CcMtaCreateIncomingCallView(HWIN hWin, CcMtaIncomingCallViewWdgList_t *pWdgList);
MAE_Ret _CcMtaCreatePetIncomingCallView(HWIN hWin, CcMtaPetIncomingCallViewWdgList_t *pWdgList);
MAE_Ret _CcMtaSetIncomingCallView(HWIN hWin, CcMtaIncomingCallViewWdgList_t *pWdgList);
MAE_Ret _CcMtaSetPetIncomingCallView(HWIN hWin, CcMtaPetIncomingCallViewWdgList_t *pWdgList);

#ifdef __CCMTA_OPTION_MENU_MMI__
boolean HandleKeyPressIncomingCallOptionMenu(MMI_CCMTA* pThis, u32 nKeycode);
MAE_Ret CCMTAWndIncomingCallOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CcMtaWndCreateIncomingCallOptionMenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret CcMtaWndDestroyIncomingCallOptionMenu(void* pCusHandle,void* pWndData);
void CcMtaIncomingCallOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __DISTORTED_VOICE_MMI__
void CcMtaDistortedVoiceDataRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
#endif // __DISTORTED_VOICE_MMI__
#endif // __CCMTA_OPTION_MENU_MMI__

#ifdef __DUAL_LCD__
MAE_Ret CcMtaSubWndCreateIncomingcall(void *pCusHandle,void *pWndData, u32 nWndInitParam);
MAE_Ret _CcMtaSubCreateIncomingCallView(HWIN hWin, CcMtaIncomingCallViewWdgList_t *pWdgList);
#endif // __DUAL_LCD__

#endif /* __MMI_CCMTAAPP_PRIV_H__ */
