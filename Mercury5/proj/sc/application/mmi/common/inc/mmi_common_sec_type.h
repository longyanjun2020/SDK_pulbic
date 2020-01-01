#ifndef __MMI_COMMON_SEC_TYPE_H__
#define __MMI_COMMON_SEC_TYPE_H__

#include "mmi_launcher_security.h"

/*
 * data type definition of secapp that is needed by other libraries
 * */

typedef enum
{
    SecurityType_Unknown = 0,   // unknown reason. //
    SecurityType_OnWithPhoneLock,         // begin checking security lock from PIN lock while power on //
    SecurityType_OnWithPhoneLock_Powercut,    // begin checking security lock from PIN lock while power on without UI//
    SecurityType_OnWithoutPhoneLock,        // begin checking security lock from PIN lock except phone lock while power on //
    SecurityType_OnWithoutPhoneLock_Powercut, // begin checking security lock from PIN lock except phone lock while power on without UI//
    SecurityType_OnCheckPhoneLockOnly,      // check Phone lock only while power on //
    SecurityType_OnCheckPhoneLockOnly_Powercut,   // check Phone lock only while power on without UI//
    SecurityType_SecurityMenu, // launch security menu //
    SecurityType_APVerifyPhoneLockOnce,  // verify Phone lock only one time for AP //
    SecurityType_APVerifyPhoneLockOnceWithoutDialog,  // verify Phone lock only one time for AP and don't show done dialog //
    SecurityType_APVerifyPhoneLockUntilPass,  // verify Phone lock until pass for AP //
    SecurityType_APVerifyPhoneLockUntilPassWithoutDialog,  // verify Phone lock until pass for AP and don't show done dialog //
    SecurityType_APVerifyPIN2LockOnce,  // verify PIN2 lock only one time for AP //
    SecurityType_APVerifyPIN2LockOnceWithoutDialog,  // verify PIN2 lock only one time for AP and don't show done dialog //
    SecurityType_APVerifyPIN2LockUntilPass,  // verify PIN2 lock until pass for AP //
    SecurityType_APVerifyPIN2LockUntilPassWithoutDialog,  // verify PIN2 lock until pass for AP and don't show done dialog //
    SecurityType_SIMSecurityCode,  // change PIN code by SIM Security code //
    SecurityType_ChangeSIMMode,  // checking security lock for changing SIM mode  //
    SecurityType_AntiSteal,
	SecurityType_AntiSteal_Powercut
}SecurityType_e;  // All start reasons for launching Security AP //

typedef struct
{
    SecurityType_e eSecType;  //start reason for launching security ap.
    IApplet *pCallerAP; //The pointer of caller ap instance.
    u32 nSIMID;     //Don't care for Single SIM mode; DUAL_MASTER or DUAL_SLAVE for DUAL SIM mode. Only needed when PIN/PUK/SIM relative checking.
    u8 *pstrSecurityCode; //securtiy code string when eSectype is SecurityType_SIMSecurityCode.
    u32 nTitleID;   //The text id of title string. It is meaningful when the security type belongs to AP lock verification.
    SecurityLaunchRspCb pfnCallerRspCb;
	bool bSIMError;
} SecAppStart_t;

#endif // __MMI_COMMON_SEC_TYPE_H__
