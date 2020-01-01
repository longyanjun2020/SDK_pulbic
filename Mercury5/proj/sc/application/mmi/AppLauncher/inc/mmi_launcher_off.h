#ifndef __OFF_APP_H__
#define __OFF_APP_H__

#include "mmi_launcher_common.h"

/// 1. Em App,            APM_Mode = APM_LAUNCH_INTERRUPTIVE,                            Mode = PowerOffType_Normal
/// 2. Idle App,          APM_Mode = APM_LAUNCH_NORMAL,                                  Mode = PowerOffType_Normal         
///                       APM_Mode = APM_LAUNCH_INTERRUPTIVE | APML_ABORT_ON_INT_FAILED, Mode = PowerOffType_Normal
///                       APM_Mode = APM_LAUNCH_INTERRUPTIVE | APML_ABORT_ON_INT_FAILED, Mode = PowerOffType_PowerOffMenu
/// 3. Main Menu App,     APM_Mode = APM_LAUNCH_NORMAL,                                  Mode = PowerOffType_PowerOffMenu
///                       APM_Mode = APM_LAUNCH_INTERRUPTIVE | APML_ABORT_ON_INT_FAILED, Mode = PowerOffType_Normal
///                       APM_Mode = APM_LAUNCH_INTERRUPTIVE | APML_ABORT_ON_INT_FAILED, Mode = PowerOffType_PowerOffMenu
/// 4. On App             APM_Mode = APM_LAUNCH_NORMAL,                                  Mode = PowerOffType_Normal         
/// 5. Sec App            APM_Mode = APM_LAUNCH_NORMAL,                                  Mode = PowerOffType_Normal         
/// 6. Setting App        APM_Mode = APM_LAUNCH_NORMAL,                                  Mode = PowerOffType_FactoryMode    
///                       APM_Mode = APM_LAUNCH_NORMAL,                                  Mode = PowerOffType_SwitchDualMode 
/// 7. Alarm Srv          APM_Mode = APM_LAUNCH_INTERRUPTIVE,                            Mode = PowerOffType_Auto           
/// 8. Eventer Center Srv APM_Mode = APM_LAUNCH_INTERRUPTIVE,                            Mode = PowerOffType_LowBattery     
/// 
/// Note: Mode = PowerOffType_ATCommand is not used by anyone now


typedef enum
{
	OFF_LAUNCH_MODE_MIN = 0,         /// APM_LAUNCH_NORMAL       + PowerOffType_Normal
	OFF_LAUNCH_MODE_NORMAL = OFF_LAUNCH_MODE_MIN,
	OFF_LAUNCH_MODE_AUTO,               /// APM_LAUNCH_INTERRUPTIVE + PowerOffType_Auto
	OFF_LAUNCH_MODE_POWER_OFF_MENU,
	OFF_LAUNCH_MODE_SWITCH_DUAL_MODE,   /// APM_LAUNCH_NORMAL       + PowerOffType_SwitchDualMode
	OFF_LAUNCH_MODE_LOW_BATTERY,        /// APM_LAUNCH_INTERRUPTIVE + PowerOffType_LowBattery	
	OFF_LAUNCH_MODE_ATCOMMAND,
    OFF_LAUNCH_MODE_FACTORY,            /// APM_LAUNCH_NORMAL       + PowerOffType_FactoryMode	
	OFF_LAUNCH_MODE_MAX = OFF_LAUNCH_MODE_FACTORY,
}OffLaunchMode_e;

/// URL Format: "Off://Launch?APM_Mode=%d&StartMode=%d"
/// No data response callback
void LaunchOffApp
(
  AppLaunchMode_e eAppLaunchMode,
  OffLaunchMode_e eLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
