#ifndef __SEC_APP_H__
#define __SEC_APP_H__

#include "mmi_launcher_common.h"

/// 1. CallLog App,  APM_Mode = APM_LAUNCH_NORMAL,       SecurityType = SecurityType_APVerifyPhoneLockUntilPass,             pstrSecurityCode = NULL,     nTitleID = NULL
/// 2. Dialer App,   APM_Mode = APM_LAUNCH_NORMAL,       SecurityType = SecurityType_SIMSecurityCode,                        pstrSecurityCode = pSecCode, nTitleID = NULL
/// 3. Fdn App,      APM_Mode = APM_LAUNCH_NORMAL,       SecurityType = SecurityType_APVerifyPIN2LockUntilPassWithoutDialog, pstrSecurityCode = NULL,     nTitleID = NULL
/// 4. Mca App,      APM_Mode =
/// 5. Off App,      APM_Mode = APM_LAUNCH_NORMAL,       SecurityType = SecurityType_ChangeSIMMode,                          pstrSecurityCode = NULL,     nTitleID = NULL
/// 6. On App,       APM_Mode = APM_LAUNCH_NORMAL,       SecurityType = eSecType,                                            pstrSecurityCode = NULL,     nTitleID = NULL
/// 7. Profile App,  APM_Mode = APM_LAUNCH_EMBEDDED,     SecurityType = SecurityType_APVerifyPhoneLockUntilPass,             pstrSecurityCode = NULL,     nTitleID = NULL
/// 8. Setting App,  APM_Mode = APM_LAUNCH_EMBEDDED,     SecurityType = SecurityType_APVerifyPhoneLockUntilPassWithoutDialog,pstrSecurityCode = NULL,     nTitleID = TXT_LIL_N_RESTORE_SETTINGS
///                  APM_Mode = APM_LAUNCH_EMBEDDED,     SecurityType = SecurityType_SecurityMenu,                           pstrSecurityCode = NULL,     nTitleID = NULL
/// 9. Shortcut Srv, APM_Mode = APM_LAUNCH_INTERRUPTIVE, SecurityType = SecurityType_SecurityMenu,                           pstrSecurityCode = NULL,     nTitleID = NULL


typedef enum
{
	SECURITY_LAUNCH_MODE_SIM_RELATED_MIN = 0,
	SECURITY_LAUNCH_MODE_POWER_ON_WITH_PHONE_LOCK = SECURITY_LAUNCH_MODE_SIM_RELATED_MIN,
	SECURITY_LAUNCH_MODE_POWER_ON_WITH_PHONE_LOCK_POWERCUT,
	SECURITY_LAUNCH_MODE_POWER_ON_WITHOUT_PHONE_LOCK,
	SECURITY_LAUNCH_MODE_POWER_ON_WITHOUT_PHONE_LOCK_POWERCUT,
	SECURITY_LAUNCH_MODE_POWER_ON_CHECK_PHONE_LOCK_ONLY,
	SECURITY_LAUNCH_MODE_POWER_ON_CHECK_PHONE_LOCK_ONLY_POWERCUT,
	SECURITY_LAUNCH_MODE_CHANGE_SIM_MODE,
#ifdef __ANTI_STEAL_MMI__
	SECURITY_LAUNCH_MODE_ANTI_STEAL,
	SECURITY_LAUNCH_MODE_ANTI_STEAL_POWERCUT,
#endif
	SECURITY_LAUNCH_MODE_SIM_RELATED_MAX = SECURITY_LAUNCH_MODE_CHANGE_SIM_MODE,
}SecurityLaunchSimRelatedMode_e;

typedef enum
{
	SECURITY_LAUNCH_MODE_LOCK_VERIFY_MIN = 0,
	SECURITY_LAUNCH_MODE_AP_VERIFY_PHONE_LOCK_UNTIL_PASS = SECURITY_LAUNCH_MODE_LOCK_VERIFY_MIN,
	SECURITY_LAUNCH_MODE_AP_VERIFY_PHONE_LOCK_UNTIL_PASS_WITH_DIALOG,
	SECURITY_LAUNCH_MODE_AP_VERIFY_PIN2_LOCK_UNTIL_PASS,
	SECURITY_LAUNCH_MODE_AP_VERIFY_PIN2_LOCK_UNTIL_PASS_WITH_DIALOG,
	SECURITY_LAUNCH_MODE_AP_VERIFY_PHONE_LOCK_UNTIL_PASS_WITHOUT_INTERRUPT,
	SECURITY_LAUNCH_MODE_LOCK_VERIFY_MAX = SECURITY_LAUNCH_MODE_AP_VERIFY_PIN2_LOCK_UNTIL_PASS_WITH_DIALOG,
}SecurityLaunchAPLockVerifyMode_e;


typedef enum
{
	SECURITY_RESULT_CODE_MIN = 0 ,
	SECURITY_RESULT_CODE_POWER_ON_ALL_LOCK_SUCCESS = SECURITY_RESULT_CODE_MIN,
    SECURITY_RESULT_CODE_POWER_ON_PHONE_LOCK_ONLY_SUCCESS,
	SECURITY_RESULT_CODE_POWER_ON_PHONE_LONG_PRESS_END_KEY,
	SECURITY_RESULT_CODE_PHONE_LOCK_SUCCESS,
	SECURITY_RESULT_CODE_PHONE_LOCK_FAIL,
	SECURITY_RESULT_CODE_PHONE_LOCK_CANCEL,
	SECURITY_RESULT_CODE_PIN2_LOCK_SUCCESS,
	SECURITY_RESULT_CODE_PIN2_LOCK_FAIL,
	SECURITY_RESULT_CODE_PIN2_LOCK_CANCEL,
	SECURITY_RESULT_CODE_ON_NETWORK_LOCK_SUCCESS,
    SECURITY_RESULT_CODE_ON_LOCK_CANCEL,
    SECURITY_RESULT_CODE_MAX = SECURITY_RESULT_CODE_PIN2_LOCK_CANCEL,
}SecurityResCode_e;

typedef struct
{
    SecurityResCode_e *peResCode;
    u8 *pu8OutputStr;
}SecurityLaunchRspData_t;

typedef void (*SecurityLaunchRspDataFreeCb)(SecurityLaunchRspData_t *psRspData);
typedef void (*SecurityLaunchRspCb)(void *pvUserData, MAE_Ret nRspCode, SecurityLaunchRspData_t *psRspData, SecurityLaunchRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
    void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    SecurityLaunchRspCb pfnRspCb;
}SecurityLaunchRspCbInfo_t;

typedef struct
{
	SecurityLaunchAPLockVerifyMode_e eMode;
	SimID_e nSIMID;
	u32 nTitleID;		//The text id of title string. It is meaningful when the security type belongs to AP lock verification.
}SecurityLaunchAPLockVerifyData_t;

typedef struct
{
	SecurityLaunchSimRelatedMode_e eMode;
	SimID_e nSIMID;
	boolean bSIMError;
}SecurityLaunchSimRelatedData_t;


/// URL Format: "Security://LaunchMenu?APM_Mode=%d"
/// Use data response callback to retrieve data
void LaunchSecurityAppToLaunchMenu
(
  AppLaunchMode_e eAppLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  SecurityLaunchRspCbInfo_t *psRspCbInfo
);

/// URL Format: "Security://CheckSecurityCode?APM_Mode=%d&SecurityCode=%s"
/// Use data response callback to retrieve data
void LaunchSecurityAppToCheckSecurityCode
(
  AppLaunchMode_e eAppLaunchMode,
  MAE_WChar *pstrSecurityCode,
  LaunchAppTransParam_t *psTransParam,
  SecurityLaunchRspCbInfo_t *psRspCbInfo
);

/// URL Format: "Security://CheckBySim?APM_Mode=%d&StartMode=%d&SimID=%d"
/// Use data response callback to retrieve data
void LaunchSecurityAppToCheckBySim
(
  AppLaunchMode_e eAppLaunchMode,
  SecurityLaunchSimRelatedData_t *psLaunchData,
  LaunchAppTransParam_t *psTransParam,
  SecurityLaunchRspCbInfo_t *psRspCbInfo
);

/// URL Format: "Security://CheckAPLockVerification?APM_Mode=%d&StartMode=%d&SimID=%d&TitleID=%d"
/// Use data response callback to retrieve data
void LaunchSecurityAppToCheckAPLockVerification
(
  AppLaunchMode_e eAppLaunchMode,
  SecurityLaunchAPLockVerifyData_t *psLaunchData,
  LaunchAppTransParam_t *psTransParam,
  SecurityLaunchRspCbInfo_t *psRspCbInfo
);

#endif
