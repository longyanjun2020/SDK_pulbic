#ifndef __VIDEOTELEPHONY_APP_H__
#define __VIDEOTELEPHONY_APP_H__

#include "mmi_launcher_common.h"

#ifdef __APP_VIDEO_TELEPHONY__

#define MAX_VIDEOTELEPHONY_CALL_NUMBER_LEN (40)
#define MAX_VIDEOTELEPHONY_CALL_NAME_LEN   (41)

typedef enum
{
	VIDEOTELEPHONY_CALL_TYPE_MIN = 0,
	VIDEOTELEPHONY_CALL_TYPE_MAKE_CALL = VIDEOTELEPHONY_CALL_TYPE_MIN,
	VIDEOTELEPHONY_CALL_TYPE_INCOMING_CALL,
	VIDEOTELEPHONY_CALL_TYPE_WAITING_CALL,
	VIDEOTELEPHONY_CALL_TYPE_VIDEO_CALL,
	VIDEOTELEPHONY_CALL_TYPE_END_CALL,
	VIDEOTELEPHONY_CALL_TYPE_MAX = VIDEOTELEPHONY_CALL_TYPE_END_CALL,
} VideoTelephonyAppCallType_e;

typedef struct 
{
	boolean	bIsDualDisable; // Set TRUE if other AP already decide Master or Slave
	SimID_e eSimId; // Set DUAL_MASTER/DUAL_SLAVE if bDisable is TRUE
} VideoTelephonyAppDualOption_t;

typedef struct
{
	VideoTelephonyAppCallType_e	eCallType;
	u8 CallNumber[MAX_VIDEOTELEPHONY_CALL_NUMBER_LEN+1];		
	MAE_WChar CallName[MAX_VIDEOTELEPHONY_CALL_NAME_LEN+1];	
	u32	nImgId;									
	u32 nRingtoneId;
	VideoTelephonyAppDualOption_t tDualOption;	
} VideoTelephonyAppMakeCallReqData_t;


///	1. CallLog App,     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
///	2. Ccmta App,       APM_MODE = APM_LAUNCH_NORMAL,       param = MmiCCAPPIncomingCallInd_t, Mode = CC_AP_FID_INCOMINCALL/CC_AP_FID_WAITINGCALL,u8SessDualId = u8SessDualId, bAnswerByBT =  bAnswerByBT
///	3. Dialer App,      APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
///	4. Fdn App,         APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL 
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
///	5. KeyGuard App,    APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL 
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
///	6. Map App,         APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL 

///	7. Message View App,APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = , Mode = CC_AP_FID_IPCALL
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = , Mode = CC_AP_FID_MAKECALL

///	8. Phb App,         APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL 
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
///	9. Sec App,         APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL

/// 10.Shortcut App,    APM_MODE = APM_LAUNCH_NORMAL,       param = , Mode = CC_AP_FID_MAKECALL

/// 11.Stk App,         APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = TRUE
/// 12.Vendor App,      APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL
/// 13.VoiceMail App,   APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL
/// 14.Bt Srv,          APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL 
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
/// 15.Cc Srv,          APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = Mode,                      Mode = CC_AP_FID_ENDCALL  /// end call by srv
/// 16.Shortcut Srv,    APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL 
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_MAKECALL,                         CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
/// 17.Sva App,         APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL 
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL

/*============public================*/

/// URL Format: "CallCtrl://MakeCall?APM_Mode=%d&CallType=%d&CallNum=%s&CallName=%s&ImageId=%d&RingtoneId=%d&SimId=%d&IsDualDisable=%d&IsMakeCallBySTK=%d"
/// No data response callback
void LaunchVideoTelephonyAppToMakeCall
(
	AppLaunchMode_e eAppLaunchMode, 
	VideoTelephonyAppMakeCallReqData_t *pMakeCallReqData,
	boolean bIsMakeCallBySTK,
	LaunchAppTransParam_t *psTransParam,
	CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

////////////////// Private //////////////////////////////////////

/// Only used in CCMTA
/// URL Format: "CallCtrl://WaitingCall?APM_Mode=%d&SimId=%d&IsAnswerCallByBT=%d"
/// No data response callback
void LaunchVideoTelephonyAppToWaitingCall
(
	AppLaunchMode_e eAppLaunchMode,
	SimID_e eSimId,
	boolean bIsAnswerCallByBT,
	LaunchAppTransParam_t *psTransParam,
	CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// URL Format: "CallCtrl://IncomingCall?APM_Mode=%d&SimId=%d&IsAnswerCallByBT=%d"
/// No data response callback
void LaunchVideoTelephonyAppToIncomingCall
(
	AppLaunchMode_e eAppLaunchMode,
	SimID_e eSimId, 
	boolean bIsAnswerCallByBT,
	LaunchAppTransParam_t *psTransParam,
	CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// Only used in mmi_ccsrv
/// URL Format: "CallCtrl://EndCall?APM_Mode=%d"
/// No data response callback
void LaunchVideoTelephonyAppToEndCall
(
	AppLaunchMode_e eAppLaunchMode,
	LaunchAppTransParam_t *psTransParam,
	CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

//////////////////////////////////////////////////////////////////////////
#endif
#endif
