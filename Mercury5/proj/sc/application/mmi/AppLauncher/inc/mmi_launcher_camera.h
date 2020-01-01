#ifndef __CAM_APP_H__
#define __CAM_APP_H__

#include "mmi_launcher_common.h"


/// 1. Em App,       APM_Mode = APM_LAUNCH_NORMAL,       param = Mode, Mode = CAM_EM_MODE_AUTO_CLOSE,
///                  APM_Mode = APM_LAUNCH_NORMAL,       param = Mode, Mode = CAM_EM_MODE
///                  APM_Mode = APM_LAUNCH_NORMAL,       param = Mode, Mode = CAM_VIDEO_MODE
///                  APM_Mode = APM_LAUNCH_NORMAL,       param = Mode, Mode = CAM_PICTURE_MODE
/// 2. Shortcut Srv, APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode, Mode = CAM_PICTURE_MODE
///                  APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode, Mode = CAM_VIDEO_MODE
typedef enum
{
	CAMERA_LAUNCH_MODE_MIN = 0,
	CAMERA_LAUNCH_MODE_PICTURE = CAMERA_LAUNCH_MODE_MIN,
	CAMERA_LAUNCH_MODE_VIDEO, 
	CAMERA_LAUNCH_MODE_ENGINEERING,
	CAMERA_LAUNCH_MODE_ENGINEERING_AUTO_CLOSE,
	CAMERA_LAUNCH_MODE_MAX = CAMERA_LAUNCH_MODE_ENGINEERING_AUTO_CLOSE,
	CAMERA_LAUNCH_MODE_INVALID,
}CameraLaunchMode_e;

typedef struct
{
    u8                    nNumOfPhotoOrVideo;
    MAE_WChar       **ppFileName;
} CameraRspData_t;


/// 1. 2.
/// Camera://Launch?APM_Mode=%d&LaunchMode=%d
/// No data response callback
void LaunchCameraApp
(
  AppLaunchMode_e eAppLaunchMode, 
  CameraLaunchMode_e eLaunchMode, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// Camera://Launch?APM_Mode=%d&LaunchMode=%d&EnterPlaybackMode=%dReturnFilePath=%dMultiShot=%d
void LaunchCameraAppByCondition
(
  AppLaunchMode_e        eAppLaunchMode, 
  CameraLaunchMode_e     eLaunchMode, 
  boolean                 bIsEnterPlaybackMode,
  boolean                 bIsReturnFilePath,
  boolean                 bIsMultiShotSupport,
  boolean                 bIsAccessMultiMediaApp, 
  boolean                 bIsEnableBlogLink,
  LaunchAppTransParam_t   *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif
