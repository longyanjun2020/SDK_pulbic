#ifndef __CC_APP_H__
#define __CC_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_ccsrv_def.h"

#define MAX_CC_CALL_NUMBER_LEN (40)
#define MAX_CC_CALL_NAME_LEN   (41)

typedef enum
{
    CC_CALL_TYPE_MIN = 0,
    CC_CALL_TYPE_MAKE_CALL = CC_CALL_TYPE_MIN,
    CC_CALL_TYPE_INCOMING_CALL,
    CC_CALL_TYPE_WAITING_CALL,
#ifdef __IP_CALL_MMI__
    CC_CALL_TYPE_IP_CALL,
#endif
    CC_CALL_TYPE_END_CALL,
    CC_CALL_TYPE_MAX = CC_CALL_TYPE_END_CALL,

} CcAppCallType_e;

typedef enum
{
    CC_MAKECALL_RESULT = 0,
    CC_MAKECALL_CALLID,
} CcAppRspType_e;

enum
{
	CC_MT_UNKNOWN = 0 ,
	CC_MT_ANSWER_BY_BT_HEADSET,
	CC_MT_ANSWER_BY_HANDSET,
	CC_MT_ANSWER_BY_HEADSET_HOOK
};
typedef u8 MMI_CC_ANSWER_DEVICE_e;


typedef struct 
{
	boolean	bIsDualDisable; // Set TRUE if other AP already decide Master or Slave
	SimID_e eSimId; // Set DUAL_MASTER/DUAL_SLAVE if bDisable is TRUE

} CcAppDualOption_t;

typedef struct
{
	CcAppCallType_e	eCallType;
	u8 CallNumber[MAX_CC_CALL_NUMBER_LEN+1];		
	MAE_WChar CallName[MAX_CC_CALL_NAME_LEN+1];	
	u32	nImgId;									
	u32 nRingtoneId;
	CcAppDualOption_t tDualOption;
	
} CcAppMakeCallReqData_t;

typedef struct
{
    CcAppRspType_e nRspType;
    union {
		boolean bMakeCallCnf;
		u32 nCallRefID;
    } param;
} CcAppMakeCallRspData_t;


///	1. CallLog App,     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = TRUE,  tDuoOption.u8SessDualId = DUAL_MASTER/DUAL_SLAVE , bSTKMakeCall = NULL
///                     APM_MODE = APM_LAUNCH_INTERRUPTIVE, param = MmiCCAPPMakeCallReq_t,     Mode = CC_AP_FID_IPCALL/CC_AP_FID_MAKECALL,        CallNumber = au8Number, CallName = NULL, u32ImageID = NULL, u32RingtoneID = NULL, tDuoOption.bDisable = FALSE, tDuoOption.u8SessDualId = NULL ,                   bSTKMakeCall = NULL
///	2. Ccmta App,       APM_MODE = APM_LAUNCH_NORMAL,       param = MmiCCAPPIncomingCallInd_t, Mode = CC_AP_FID_INCOMINCALL/CC_AP_FID_WAITINGCALL,u8SessDualId = u8SessDualId, u8AnswerBy =  u8AnswerBy
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
void LaunchCcAppToMakeCall(AppLaunchMode_e eAppLaunchMode, 
						   CcAppMakeCallReqData_t *pMakeCallReqData,
						   boolean bIsMakeCallBySTK,
						   LaunchAppTransParam_t *psTransParam,
						   CmnAppLaunchRspCbInfo_t *pRspCbInfo);

////////////////// Private //////////////////////////////////////

/// Only used in CCMTA
/// URL Format: "CallCtrl://WaitingCall?APM_Mode=%d&SimId=%d&AnswerCallBy=%d"
/// No data response callback
void LaunchCcAppToWaitingCall
(
  AppLaunchMode_e eAppLaunchMode,
  SimID_e eSimId,
  u8 u8AnswerCallBy,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// URL Format: "CallCtrl://IncomingCall?APM_Mode=%d&SimId=%d&AnswerCallBy=%d"
/// No data response callback
void LaunchCcAppToIncomingCall
(
  AppLaunchMode_e eAppLaunchMode,
  SimID_e eSimId, 
  u8 u8AnswerCallBy,
  boolean bLaunchFuncEnable,
  boolean bEnableAnsweringMachine,
  ANSWERING_MACHINE_FAILED_TYPE_e eAnsweringMachineFailedType,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// Only used in mmi_ccsrv
/// URL Format: "CallCtrl://EndCall?APM_Mode=%d"
/// No data response callback
void LaunchCcAppToEndCall
(
  AppLaunchMode_e eAppLaunchMode,
  MMI_CC_AP_FID_E eAppFID,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// URL Format: "CallCtrl://EndCall?APM_Mode=%d&CALL_ID=%d"
/// No data response callback
void LaunchCcAppToEndSpecificCall
(
  AppLaunchMode_e eAppLaunchMode,
  MMI_CC_AP_FID_E eAppFID,
  u32 nCallID,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);


//////////////////////////////////////////////////////////////////////////

#endif
