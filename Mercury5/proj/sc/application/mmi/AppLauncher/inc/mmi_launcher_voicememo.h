#ifndef __MMI_LAUNCHER_VOICEMEMO_H__
#define __MMI_LAUNCHER_VOICEMEMO_H__

#include "mmi_launcher_common.h"
#include "mmi_launcher_filemanager.h"

/// URL Format: "VoiceMemo://Launch?APM_Mode=%d"
/// No Response Data Callback
void LaunchVoiceMemoApp
(
    AppLaunchMode_e eAppLaunchMode,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

#endif /* __MMI_LAUNCHER_VOICEMEMO_H__ */
