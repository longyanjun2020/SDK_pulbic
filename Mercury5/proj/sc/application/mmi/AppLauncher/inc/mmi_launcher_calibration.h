#ifndef __CALIBRATION_APP_H__
#define __CALIBRATION_APP_H__

#include "mmi_launcher_common.h"

/// 1. Em App,      APM_Mode = APM_LAUNCH_NORMAL, param = Mmi_CalibrationApp_StartData_t, Mode = MMI_CALIBRATIONAPP_START_ENGINEER_MODE
/// 2. On App,      APM_Mode = APM_LAUNCH_NORMAL, param = NULL
/// 3. Setting App, APM_Mode = APM_LAUNCH_NORMAL, param = NULL

typedef enum
{
	CALIBRATION_LAUNCH_MODE_MIN,
    CALIBRATION_LAUNCH_MODE_NORMAL = CALIBRATION_LAUNCH_MODE_MIN,  /// 2. 3.
	CALIBRATION_LAUNCH_MODE_ENGINEERING, /// 1.
	CALIBRATION_LAUNCH_MODE_MAX = CALIBRATION_LAUNCH_MODE_ENGINEERING,
}CalibrationAppLaunchMode_e;

typedef struct
{
	boolean bPass;
}CalibrationAppLaunchRspData_t;

typedef void (CalibrationAppRspDataFreeCb)(CalibrationAppLaunchRspData_t *psRspData);
typedef void (*CalibrationAppRspDataCb)(void *pvUserData, MAE_Ret nRet, CalibrationAppLaunchRspData_t *psRspData, CalibrationAppRspDataFreeCb pfnDataFreeCb);

typedef struct
{
    void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    CalibrationAppRspDataCb pfnDataRspCb;
}CalibrationAppRspCbInfo_t;

/// 1. 2. 3.
/// URL Format:  "Calibration://Launch?APM_Mode=%d&StartMode=%d"
/// Use data response callback to retrieve data
void LaunchCalibrationApp
(
  AppLaunchMode_e eLaunchMode,
  CalibrationAppLaunchMode_e eAppLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CalibrationAppRspCbInfo_t *pRspCbInfo
);

#endif
