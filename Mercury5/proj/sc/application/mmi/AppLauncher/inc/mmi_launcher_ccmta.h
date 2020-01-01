#ifndef __CCMTA_LAUNCHER_H__
#define __CCMTA_LAUNCHER_H__

#include "mmi_launcher_common.h"
#include "mmi_UrlSrvUtil.h"


typedef enum
{
CCMTA_MT_TYPE_RING = 0,
CCMTA_MT_TYPE_WAITING = 1,  // For 1A1W or 1H1W
CCMTA_MT_TYPE_WAITING_FULL = 2,    // For 1A1H1W
CCMTA_MT_TYPE_VT_RING = 3,
CCMTA_MT_TYPE_VT_WAITING = 4,  // For 1A1W or 1H1W
CCMTA_MT_TYPE_VT_WAITING_FULL = 5      // For 1A1H1W
} CcMtaType_e;

/// URL Format: CcMta://Launch?APM_Mode=%d&DualId=%d&Type=%d
/// No data response callback
void LaunchCcMtaApp
( 
	AppLaunchMode_e eAppLaunchMode,
	u8 nDualID,
	CcMtaType_e etype,
	LaunchAppTransParam_t *psTransParam,
	CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif /* __CCMTA_LAUNCHER_H__*/
