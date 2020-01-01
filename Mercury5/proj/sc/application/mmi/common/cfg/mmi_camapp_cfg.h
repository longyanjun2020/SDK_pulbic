
#ifndef __MMI_CAMAPP_CFG__H__
#define __MMI_CAMAPP_CFG__H__


#include "mmi_camerasrv_def.h"
typedef struct _MMI_Camera_Pic_Settings_t
{
    u32 nCamFileIndex;
    CameraSrvStorage_e eCamStorage;
    CameraSrvPicResolution_e eCamResolution;
    CameraSrvImgQuality_e eCamImgQuality;
    CameraSrvEnv_e eCamShootingMode;
    CameraSrvAntiFlicker_e eCamAntiFlicker;
    CameraSrvAWB_e eCamAWB;
    CameraSrvShutterSound_e eCamShutterSound;
    CameraSrvFocusMode_e  eCamFocusMode;	
} MMI_Camera_Pic_Settings_t;
typedef struct _MMI_Camera_Vdo_Settings_t
{
    CameraSrvStorage_e eCamStorage;
    CameraSrvVdoResolution_e eCamResolution;
    CameraSrvVdoQuality_e eCamVdoQuality;
    CameraSrvEnv_e eCamShootingMode;
    CameraSrvAWB_e eCamAWB;
    CameraSrvAntiFlicker_e eCamAntiFlicker;
    CameraSrvSizeLimit_e eCamSizeLimit;
    CameraSrvTimeLimit_e eCamTimeLimit;
    CameraSrvVdoSound_e eCamVdoSound;
    CameraSrvVdoStabilizer_e eCamVdoStabilizer;
} MMI_Camera_Vdo_Settings_t;

// Allow Mater Reset

//#define CONFIG_DEFINE(cfgId, type, name, value)
#define CONFIG_AMR_CAMERA_MAIN_PIC_CONFIG  CONFIG_DEFINE(CFGIT_CAMERA_MAIN_PIC_CONFIG, MMI_Camera_Pic_Settings_t, 1,  \
                                                                                {1/*nCamFileIndex*/,  \
                                                                                CAMERASRV_STORAGE__CARD/*eCamStorage*/, \
                                                                                CAMERASRV_PIC_RESOLUTION__320X240/*eCamResolution*/, \
                                                                                CAMERASRV_IMG_QUALITY__NORMAL/*eCamImgQuality*/, \
                                                                                CAMERASRV_NIGHT_MODE__OFF/*eCamShootingMode*/, \
                                                                                CAMERASRV_ANTI_FLICKER__50HZ/*eCamAntiFlicker*/, \
                                                                                CAMERASRV_AWB__ON/*eCamAWB*/,  \
                                                                                CAMERASRV_SHUTTER_SOUND__ON/*eCamShutterSound*/,  \
                                                                                CAMERASRV_FOCUS_MODE__TOUCH_TO_FOCUS/*eCamFocusMode*/}/*camPicConfig*/ )

#define CONFIG_AMR_CAMERA_MAIN_VDO_CONFIG  CONFIG_DEFINE(CFGIT_CAMERA_MAIN_VDO_CONFIG, MMI_Camera_Vdo_Settings_t, 1, \
                                                                                {CAMERASRV_STORAGE__CARD/*eCamStorage*/,    \
                                                                                CAMERASRV_VDO_RESOLUTION__352X288/*eCamResolution*/,    \
                                                                                CAMERASRV_VDO_QUALITY__NORMAL/*eCamVdoQuality*/,    \
                                                                                CAMERASRV_NIGHT_MODE__OFF/*eCamShootingMode*/,  \
                                                                                CAMERASRV_AWB__ON/*eCamAWB*/,   \
                                                                                CAMERASRV_ANTI_FLICKER__50HZ/*eCamAntiFlicker*/,    \
                                                                                CAMERASRV_SIZE_LIMIT__NONE/*eCamSizeLimit*/,    \
                                                                                CAMERASRV_TIME_LIMIT__NONE/*eCamTimeLimit*/,    \
                                                                                CAMERASRV_VDO_SOUND__ON/*eCamVdoSound*/,     \
                                                                                CAMERASRV_VDO_STABILIZER__OFF/*eCamVdoStabilizer*/}/*camVdoConfig*/ )

#ifdef __DUAL_CAMERA_MMI__
#define CONFIG_AMR_CAMERA_SUB_PIC_CONFIG  CONFIG_DEFINE(CFGIT_CAMERA_SUB_PIC_CONFIG, MMI_Camera_Pic_Settings_t, 1, {1/*nCamFileIndex*/, \
CAMERASRV_STORAGE__CARD/*eCamStorage*/, \
CAMERASRV_PIC_RESOLUTION__320X240/*eCamResolution*/, \
CAMERASRV_IMG_QUALITY__NORMAL/*eCamImgQuality*/, \
CAMERASRV_NIGHT_MODE__OFF/*eCamShootingMode*/, \
CAMERASRV_ANTI_FLICKER__50HZ/*eCamAntiFlicker*/, \
CAMERASRV_AWB__ON/*eCamAWB*/, \
CAMERASRV_SHUTTER_SOUND__ON/*eCamShutterSound*/,    \
CAMERASRV_FOCUS_MODE__TOUCH_TO_FOCUS/*eCamFocusMode*/} )

#define CONFIG_AMR_CAMERA_SUB_VDO_CONFIG  CONFIG_DEFINE(CFGIT_CAMERA_SUB_VDO_CONFIG, MMI_Camera_Vdo_Settings_t, 1, {CAMERASRV_STORAGE__CARD/*eCamStorage*/, \
CAMERASRV_VDO_RESOLUTION__352X288/*eCamResolution*/, \
CAMERASRV_VDO_QUALITY__NORMAL/*eCamVdoQuality*/, \
CAMERASRV_NIGHT_MODE__OFF/*eCamShootingMode*/, \
CAMERASRV_AWB__ON/*eCamAWB*/, \
CAMERASRV_ANTI_FLICKER__50HZ/*eCamAntiFlicker*/, \
CAMERASRV_SIZE_LIMIT__NONE/*eCamSizeLimit*/, \
CAMERASRV_TIME_LIMIT__NONE/*eCamTimeLimit*/, \
CAMERASRV_VDO_SOUND__ON/*eCamVdoSound*/, \
CAMERASRV_VDO_STABILIZER__OFF/*eCamVdoStabilizer*/} )
#else
#define CONFIG_AMR_CAMERA_SUB_PIC_CONFIG
#define CONFIG_AMR_CAMERA_SUB_VDO_CONFIG
#endif

#define CAMAPP_AMR_ALL_CONFIG \
                   CONFIG_AMR_CAMERA_MAIN_PIC_CONFIG  \
                   CONFIG_AMR_CAMERA_MAIN_VDO_CONFIG  \
                   CONFIG_AMR_CAMERA_SUB_PIC_CONFIG  \
                   CONFIG_AMR_CAMERA_SUB_VDO_CONFIG

#endif //__MMI_CAMAPP_CFG__H__
