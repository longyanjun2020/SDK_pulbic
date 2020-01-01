#ifndef __FMSCH_APP_H__
#define __FMSCH_APP_H__

#include "mmi_launcher_common.h"

typedef enum
{
    FMR_LAUNCH_MODE_NORMAL = 0,
    FMR_LAUNCH_MODE_SCH_PLAY,
    FMR_LAUNCH_MODE_SCH_REC,
}FmRadioLaunchMode_e;

/// "FmSch://LaunchFmScp?APM_Mode=%d&Type=%d""
void LaunchFmSchApp(AppLaunchMode_e eAppLaunchMode, CmnAppLaunchRspCbInfo_t *pRspCbInfo);

#ifdef __APP_MMI_FM_SCHEDULE__
/// 1.
/// Launch Fm Radio App with schedule playback
/// 
/// URL Format: "FmRadio://Launch?APM_Mode=%d&LaunchMode=FMR_LAUNCH_MODE_SCH_PLAY&SchId=%d"
/// No data response callback
void LaunchFmRadioAppToSchPlay(AppLaunchMode_e eAppLaunchMode,
							  u32 nSchId,
							  CmnAppLaunchRspCbInfo_t *pRspCbInfo);

/// 2.
/// Launch Fm Radio App with schedule record
/// 
/// URL Format: "FmRadio://Launch?APM_Mode=%d&LaunchMode=FMR_LAUNCH_MODE_SCH_REC&SchId=%d"
/// No data response callback
void LaunchFmRadioAppToSchRecord(AppLaunchMode_e eAppLaunchMode,
							  u32 nSchId,
							  CmnAppLaunchRspCbInfo_t *pRspCbInfo);
#endif

#endif/* __FMSCH_APP_H__ */
