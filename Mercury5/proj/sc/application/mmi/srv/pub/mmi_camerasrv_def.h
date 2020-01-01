/**
 * @file    mmi_camerasrv_def.h
 * @brief   Define Camera related enum and structure.
 * @version $Id:
 */

#ifndef __MMI_CAMERASRV_DEF_H__
#define __MMI_CAMERASRV_DEF_H__

#include "mmi_mae_motiondetector.h"
#include "mmi_class.h"

#define __CAMERA_V1_ITF__
// Constants definition
#define CAMERASRV_STORED_PATH_LEN          (64)  // Driver defines 128 bytes u8, but uses unicode filename.  Thus we define 128/2=64 length in XMMI.
#define CAMERASRV_MAX_MULTISHOT_NUM        (9)
#define CAMERASRV_LOMO_4LENS_CAPTURE_TIMES (4)   // don't modify this value.

/**
 * External Events
 */

//_CameraSrvNotifyCb
typedef enum CameraSrvStatusEvt_e_
{
    CAMERASRV_EVT_PLAY_SHUTTER_SOUND_IND = 0,
    CAMERASRV_EVT_CAPTURE_STOP_IND,
    CAMERASRV_EVT_RECORD_STOP_IND,
    CAMERASRV_EVT_STOP_SPACE_FULL_IND,
    CAMERASRV_EVT_UPDATE_POSITION_IND,
    CAMERASRV_EVT_ERROR_CNF,
    CAMERASRV_EVT_RECORD_DELETE_IND,
    CAMERASRV_EVT_AUTOFOCUS_COMPLETE_IND,
    CAMERASRV_EVT_MOTION_DETECT_IND
} CameraSrvStatusEvt_e;
//_CameraSrvResMgrNotifyCb

typedef enum CameraSrvInterruptEvt_e_
{
    CAMERASRV_EVT_RESMGR_SUSPEND_IND = 0,
    CAMERASRV_EVT_RESMGR_RESUME_IND
} CameraSrvInterruptEvt_e;

typedef enum CameraSrvDev_e_
{
    CAMERASRV_DEV__MAIN = 0,
    CAMERASRV_DEV__SUB,
    CAMERASRV_DEV__NUM
} CameraSrvDev_e;

typedef enum
{
    CAMERASRV_APP__PIC = 0,
    CAMERASRV_APP__VDO,
    CAMERASRV_APP__EM,
    CAMERASRV_APP__NUM
} CameraSrvAppType_e;

typedef enum CameraSrvSizeLimit_e_
{
    CAMERASRV_SIZE_LIMIT__NONE = 0,
    CAMERASRV_SIZE_LIMIT__FOR_MMS,
    CAMERASRV_SIZE_LIMIT__NUM
} CameraSrvSizeLimit_e;

typedef enum CameraSrvTimeLimit_e_
{
    CAMERASRV_TIME_LIMIT__NONE = 0,
    CAMERASRV_TIME_LIMIT__15SEC,
    CAMERASRV_TIME_LIMIT__30SEC,
    CAMERASRV_TIME_LIMIT__60SEC,
    CAMERASRV_TIME_LIMIT__NUM
} CameraSrvTimeLimit_e;

typedef enum CameraSrvPicResolution_e_
{
    CAMERASRV_PIC_RESOLUTION__FOR_CONTACT = 0,
    CAMERASRV_PIC_RESOLUTION__WALLPAPER,
    CAMERASRV_PIC_RESOLUTION__320X240,
    CAMERASRV_PIC_RESOLUTION__640X480,
    CAMERASRV_PIC_RESOLUTION__800X600,
    CAMERASRV_PIC_RESOLUTION__1024X768,
    CAMERASRV_PIC_RESOLUTION__1280X1024,
    CAMERASRV_PIC_RESOLUTION__1600X1200,
    CAMERASRV_PIC_RESOLUTION__2048X1536,
    CAMERASRV_PIC_RESOLUTION__2240X1680,
    CAMERASRV_PIC_RESOLUTION__2560X1920,
    CAMERASRV_PIC_RESOLUTION__3032X2008,
    CAMERASRV_PIC_RESOLUTION__3072X2304,
    CAMERASRV_PIC_RESOLUTION__3264X2448,
    CAMERASRV_PIC_RESOLUTION__NUM
} CameraSrvPicResolution_e;

typedef enum CameraSrvVdoResolution_e_
{
    CAMERASRV_VDO_RESOLUTION__128X96 = 0,    //SUB_QCIF
    CAMERASRV_VDO_RESOLUTION__176X144,       //QCIF
    CAMERASRV_VDO_RESOLUTION__352X288,       //CIF
    CAMERASRV_VDO_RESOLUTION__704X576,       //4CIF
    CAMERASRV_VDO_RESOLUTION__320X240,       //QVGA
#ifdef __MMI_WQVGA_RECORD_SUPPORT__
    CAMERASRV_VDO_RESOLUTION__400X240,       //WQVGA
#endif
#ifdef __MMI_HVGA_RECORD_SUPPORT__
    CAMERASRV_VDO_RESOLUTION__480X320,       //HVGA
#endif
    CAMERASRV_VDO_RESOLUTION__640X480,       //VGA
    CAMERASRV_VDO_RESOLUTION__NUM
} CameraSrvVdoResolution_e;

typedef enum CameraSrvTimer_e_
{
    CAMERASRV_TIMER__OFF = 0,
    CAMERASRV_TIMER__5_SEC,
    CAMERASRV_TIMER__10_SEC,
    CAMERASRV_TIMER__15_SEC,
    CAMERASRV_TIMER__NUM
} CameraSrvTimer_e;

typedef enum CameraSrvShutterSound_e_
{
    CAMERASRV_SHUTTER_SOUND__OFF = 0,
    CAMERASRV_SHUTTER_SOUND__ON,
    CAMERASRV_SHUTTER_SOUND__NUM
} CameraSrvShutterSound_e;

typedef enum CameraSrvSoundType_e_
{
    CAMERASRV_SOUND_TYPE__PHONE = 0,
    CAMERASRV_SOUND_TYPE__CARD,
    CAMERASRV_SOUND_TYPE__MMP_DEFAULT,
    CAMERASRV_SOUND_TYPE__BB_DEFAULT,
    CAMERASRV_SOUND_TYPE__NUM
} CameraSrvSoundType_e;

typedef enum CameraSrvMultiShot_e_
{
    CAMERASRV_MULTI_SHOT__OFF = 0,
    CAMERASRV_MULTI_SHOT__4 = 4,
    CAMERASRV_MULTI_SHOT__6 = 6,
    CAMERASRV_MULTI_SHOT__9 = CAMERASRV_MAX_MULTISHOT_NUM,
    CAMERASRV_MULTI_SHOT__NUM
} CameraSrvMultiShot_e;

typedef enum CameraSrvStorage_e_
{
    CAMERASRV_STORAGE__CARD = 0,
    CAMERASRV_STORAGE__CARD2,
    CAMERASRV_STORAGE__PHONE_EXTERNAL,
    CAMERASRV_STORAGE__PHONE_INTERNAL,
    CAMERASRV_STORAGE__PHONE_NUM
} CameraSrvStorage_e;

typedef enum CameraSrvImgQuality_e_
{
    CAMERASRV_IMG_QUALITY__LOW = 0,
    CAMERASRV_IMG_QUALITY__NORMAL,
    CAMERASRV_IMG_QUALITY__HIGH,
    CAMERASRV_IMG_QUALITY__NUM
} CameraSrvImgQuality_e;

typedef enum CameraSrvVdoQuality_e_
{
    CAMERASRV_VDO_QUALITY__LOW = 0,
    CAMERASRV_VDO_QUALITY__NORMAL,
    CAMERASRV_VDO_QUALITY__HIGH,
    CAMERASRV_VDO_QUALITY__NUM
} CameraSrvVdoQuality_e;

typedef enum CameraSrvVdoSound_e_
{
    CAMERASRV_VDO_SOUND__OFF = 0,
    CAMERASRV_VDO_SOUND__ON,
    CAMERASRV_VDO_SOUND__NUM
} CameraSrvVdoSound_e;

typedef enum CameraSrvImgDataType_e_
{
    CAMERASRV_IMAGE_DATA_TYPE__RAW = 0,
    CAMERASRV_IMAGE_DATA_TYPE__JPEG,
    CAMERASRV_IMAGE_DATA_TYPE__NUM
} CameraSrvImgDataType_e;

typedef enum CameraSrvSticker_e_
{
    CAMERASRV_STICKER__NONE = 0,
    CAMERASRV_STICKER__FRAME1,
    CAMERASRV_STICKER__FRAME2,
    CAMERASRV_STICKER__FRAME3,
    CAMERASRV_STICKER__NUM
} CameraSrvSticker_e;

typedef enum CameraSrvLomo_e_
{
    CAMERASRV_LOMO__OFF = 0,
    CAMERASRV_LOMO__ON,
    CAMERASRV_LOMO__NUM
} CameraSrvLomo_e;

typedef enum CameraSrvMirror_e_
{
    CAMERASRV_MIRROR__OFF = 0,
    CAMERASRV_MIRROR__HORIZONTAL,
    CAMERASRV_MIRROR__VERTICAL,
    CAMERASRV_MIRROR__NUM
} CameraSrvMirror_e;

typedef enum CameraSrvPanorama_e_
{
    CAMERASRV_PANORAMA__OFF = 0,
    CAMERASRV_PANORAMA__LEFT_TO_RIGHT,
    CAMERASRV_PANORAMA__RIGHT_TO_LEFT,
    CAMERASRV_PANORAMA__TOP_TO_DOWN,
    CAMERASRV_PANORAMA__DOWN_TO_TOP,
    CAMERASRV_PANORAMA__NUM
} CameraSrvPanorama_e;

typedef enum CameraSrvCptureMode_e_
{
    CAMERASRV_PIC_CAPTURE_MODE_NORMAL =0,
    CAMERASRV_PIC_CAPTURE_MODE_LOMO,
    CAMERASRV_PIC_CAPTURE_MODE_MIRROR,
    CAMERASRV_PIC_CAPTURE_MODE_PANORAMA,
    CAMERASRV_PIC_CAPTURE_MODE_NUM
} CameraSrvCaptureMode_e;

typedef enum
{
    CAMERASRV_AWB__ON = 0,
    CAMERASRV_AWB__CLOUDY,
    CAMERASRV_AWB__DAYLIGHT,
    CAMERASRV_AWB__FLUORESCENT,
    CAMERASRV_AWB__INCANDESCENCE,
    CAMERASRV_AWB__NUM
} CameraSrvAWB_e;

typedef enum
{
    CAMERASRV_AE__WHOLE_IMAGE = 0,
    CAMERASRV_AE__CENTRALWIN,
    CAMERASRV_AE__WEIGHTED_CENTRALWIN,
    CAMERASRV_AE__CENTRAL_POINT,
    CAMERASRV_AE__NUM
} CameraSrvAE_e;

typedef enum
{
    CAMERASRV_AF__OFF = 0,
    CAMERASRV_AF__ON,
    CAMERASRV_AF__NUM
}CameraSrvAF_e;

typedef enum
{
    CAMERASRV_FLASHLIGHT__OFF = 0,
    CAMERASRV_FLASHLIGHT__ON,
    CAMERASRV_FLASHLIGHT__NUM
}CameraSrvFlashlight_e;

typedef enum
{
    CAMERASRV_VDO_STABILIZER__OFF = 0,
    CAMERASRV_VDO_STABILIZER__ON,
    CAMERASRV_VDO_STABILIZER_INVALID,
    CAMERASRV_VDO_STABILIZER__NUM
}CameraSrvVdoStabilizer_e;

typedef enum
{
    CAMERASRV_ZOOM__DEFAULT = 0,
    CAMERASRV_ZOOM__1,
    CAMERASRV_ZOOM__2,
    CAMERASRV_ZOOM__3,
    CAMERASRV_ZOOM__4,
    CAMERASRV_ZOOM__5,
    CAMERASRV_ZOOM__MAX,
    CAMERASRV_ZOOM__MIN,
    CAMERASRV_ZOOM__IN,
    CAMERASRV_ZOOM__OUT
}CameraSrvZoom_e;

typedef enum
{
    CAMERASRV_EV__MIN = 0,
    CAMERASRV_EV__MINUS_1,
    CAMERASRV_EV__DEFAULT,
    CAMERASRV_EV__PLUS_1,
    CAMERASRV_EV__MAX,
    CAMERASRV_EV__ADD,
    CAMERASRV_EV__MINUS
}CameraSrvEV_e;

typedef enum
{
    CAMERASRV_ANTI_FLICKER__50HZ = 0,
    CAMERASRV_ANTI_FLICKER__60HZ,
    CAMERASRV_ANTI_FLICKER__NUM
}CameraSrvAntiFlicker_e;

typedef enum
{
//these value are sync to MDL, please consult with MDL before change it.
    CAMERASRV_EFFECT__NORMAL = 0,
    CAMERASRV_EFFECT__MONO,
    CAMERASRV_EFFECT__SEPIA,
    CAMERASRV_EFFECT__NEGATIVE,
    CAMERASRV_EFFECT__SKETCH,
    CAMERASRV_EFFECT__OIL_PAINTING,
    CAMERASRV_EFFECT__EMBOSS,
    CAMERASRV_EFFECT__MOSAIC,
    CAMERASRV_EFFECT__ZIPPER,
    CAMERASRV_EFFECT__BLUR,
    CAMERASRV_EFFECT__SEPIAGREEN,           // ´_¥jºñ
    CAMERASRV_EFFECT__SEPIABLUE,            // ´_¥jÂÅ
    CAMERASRV_EFFECT__SEPIARED,             // ´_¥j¬õ
    CAMERASRV_EFFECT__GRAYINVERSION,
    CAMERASRV_EFFECT__WHITEBOARD,           // ¥ÕªO
    CAMERASRV_EFFECT__COPPERCARVING,        // »ÉÀJ
    CAMERASRV_EFFECT__BLUECARVING,
    CAMERASRV_EFFECT__BLACKCARVING,
    CAMERASRV_EFFECT__WHITECARVING,
    CAMERASRV_EFFECT__CONTRAST,             //¹ï¤ñ
    CAMERASRV_EFFECT__SOLARIZATION,
    CAMERASRV_EFFECT__USERDEFINED1,
    CAMERASRV_EFFECT__USERDEFINED2,
    CAMERASRV_EFFECT__USERDEFINED3,
    CAMERASRV_EFFECT__USERDEFINED4,
    CAMERASRV_EFFECT__USERDEFINED5,
    CAMERASRV_EFFECT__NUM
}CameraSrvEffect_e;

typedef enum
{
    CAMERASRV_NIGHT_MODE__OFF = 0,
    CAMERASRV_NIGHT_MODE__ON,
    CAMERASRV_NIGHT_MODE__NUM
}CameraSrvEnv_e;

typedef enum CameraSrvPreviewMode_e_
{
    CAMERASRV_PREVIEW_MODE__OFF,
    CAMERASRV_PREVIEW_MODE__ON,
    CAMERASRV_PREVIEW_MODE__CAMCORDER_ON,
    CAMERASRV_PREVIEW_MODE__WALLPAPER_ON,
    CAMERASRV_PREVIEW_MODE__WALLPAPER_NUM
} CameraSrvPreviewMode_e;

typedef enum CameraSrvPreviewType_e_
{
    CAMERASRV_PREVIEW_TYPE__PORTRAIT = 0,
    CAMERASRV_PREVIEW_TYPE__LANDSCAPE,
    CAMERASRV_PREVIEW_TYPE__NUM
} CameraSrvPreviewType_e;

typedef enum
{
    CAMERASRV_PREVIEW_ANGLE__0 = 0,
    CAMERASRV_PREVIEW_ANGLE__90,
    CAMERASRV_PREVIEW_ANGLE__180,
    CAMERASRV_PREVIEW_ANGLE__270,
    CAMERASRV_PREVIEW_ANGLE__NUM
} CameraSrvPreviewAngle_e;

typedef enum
{
    CAMERASRV_FOCUS_MODE__AUTO_FOCUS = 0,
    CAMERASRV_FOCUS_MODE__TOUCH_TO_FOCUS,
    CAMERASRV_FOCUS_MODE__INVALID,
    CAMERASRV_FOCUS_MODE__NUM
} CameraSrvFocusMode_e;

typedef enum
{
    CAMERASRV_RET__SUCCESS = 0,
    CAMERASRV_RET__FAILURE,
    CAMERASRV_RET__REJECT,
    CAMERASRV_RET__PARAM_ERROR,
    CAMERASRV_RET__MEM_ALLOC_ERROR,
    CAMERASRV_RET__TIMEOUT
} CameraSrvRetCode_e;

typedef enum
{
    CAMERASRV_ERR__NONE = 0,
    /**< Notify MMI that no error */
    CAMERASRV_ERR__SPACE_FULL,
    /**< Notify MMI that space full error */
    CAMERASRV_ERR__UNKNOW,
    /**< Notify MMI that error unknow */
    CAMERASRV_ERR__TIMEOUT,
    /**< Notify MMI that time's up (for QR Cdoe only) */
    CAMERASRV_ERR__NOT_SUPPORT,
    /**< Notify MMI that format is unsupport (for QR Cdoe only) */
    CAMERASRV_ERR__SDCARD_NOT_DETECTED,
    /**< Notify MMI that the camera capture/camcorder recording had an unexpected error */
    CAMERASRV_ERR__SAVE_COMPLETE,
    /**< Notify MMI that saved completely before deferring save */
    CAMERASRV_ERR__OVER_SIZE,
    /**< Notify MMI that recording over size limitation */
    CAMERASRV_ERR__MEMORY_INSUFFICIENCY,
    /**< Notify MMI that memory space isn't enough for the command*/
    CAMERASRV_ERR__NUM
    /**< Error numbers */
} CameraSrvErrCode_e;

typedef enum
{
    CAMERASRV_CAPTURE_ROTATION__0 = 0,
    CAMERASRV_CAPTURE_ROTATION__90,
    CAMERASRV_CAPTURE_ROTATION__180,
    CAMERASRV_CAPTURE_ROTATION__270,
    CAMERASRV_CAPTURE_ROTATION__NUM
} CameraSrvCaptureRotation_e;

typedef enum
{
    CAMERASRV_CAPTURE_STOP__USER_STOP = 0,
    CAMERASRV_CAPTURE_STOP__CAPTURE_END,
    CAMERASRV_CAPTURE_STOP__RUNTIME_ERROR
} CameraSrvCaptureStopType_e;

typedef enum
{
    CAMERASRV_SENSORSTATUS_ALL = 0,     ///< Primary and secondary sensors are available
    CAMERASRV_SENSORSTATUS_PRIMARY,     ///< Only primary sensor is available
    CAMERASRV_SENSORSTATUS_SECONDARY,   ///< Only secondary sensor is available
    CAMERASRV_SENSORSTATUS_NONE,        ///< No sensor is available
    CAMERASRV_SENSORSTATUS_NUM
} CameraSrvSensorStatus_e;

typedef struct {
    u32 nSize;   /**< image buffer length */
    u32 nImgOutAddr; /**< image buffer address (MMI should release file name buffer after receiving response msg) */
} CameraSrvImage_t;

#define CAMERASRV_RES_TYPE_NORMAL           ((u16)0x0000)    // Refer to the specified width and height
#define CAMERASRV_RES_TYPE_PIC_CONTACT      ((u16)0x0001)    // Image capture with contact-sized resolution
#define CAMERASRV_RES_TYPE_PIC_WALLPAPER    ((u16)0x0002)    // Image capture with wallpaper-sized resolution

typedef struct
{
    u16     nResType;
    u16     nWidth;                 // Output width in pixels
    u16     nHeight;                // Output height in pixels
    u16     nMaxZoomLevel;          // Maximum zoom level (1000: 1x, 1300: 1.3x, ..., 4000: 4x)
    u16     nNumZoomLevelSteps;     // Number of zoom level steps supported (0: 1 step, 1: 2 steps, ..., 63: 64 steps)
    u16     bMultiShootSupported;   ///< Multi shoot supported ?
} CameraSrvZoomInfo_t;

typedef struct
{
    u16                        nZoomInfoListSize;          // Size in elements of the pZoomInfoList
    CameraSrvZoomInfo_t        *pZoomInfoList;             // Pointer to a list of zoom info queried
    u16                        nSensorWidth;               // Sensor width
    u16                        nSensorHeight;              // Sensor height
    u16                        nMaxInterpolatedWidth;      // Maximum interpolated width
    u16                        nMaxInterpolatedHeight;     // Maximum interpolated height
    u16                        bImageEffectSupported;      // Special image effect supported ?
    u16                        bSensorImageEffectSupported;    ///< Sensor special image effect supported ?
    u16                        bVideoStabilizerSupported;     ///< Video stabilizer supported ?
    u16                        bAutoFocusSupported;    ///< Auto focus supported ?
    u32                        nImageEffectSupported;          ///< Special image effects supported (chip + sensor)
    CameraSrvSensorStatus_e    eSensorStatus;                  ///< Result of sensor detection

} CameraSrvCameraInfo_t;

typedef struct {
    u16 nLen;        /**< file name length */
    u32 nFileNameOutAddr; /**< file name buffer address (MMI should release file name buffer after receiving response msg) */
} CameraSrvFileName_t;

typedef struct {
    CameraSrvPanorama_e     eCamPanorama;
    u8                      *pPanoramaBuffer;
    u32                     nPanoramaBufferSize;
    u32                     nTotalPicsNum;
    u32                     nCurrentPicsNum;
} CameraSrvPanoramaInfo_t;

typedef struct CameraSrvRegion_t_
{
    u16 nX;		    // 0 ~ 2^16-1
    u16 nY;		    // 0 ~ 2^16-1
    u16 nWidth;	// 0 ~ 2^12-1, denotes 1 ~ 2^12
    u16 nHeight;	// 0 ~ 2^12-1, denotes 1 ~ 2^12
} CameraSrvRegion_t;

typedef struct
{
    u8 *pCamSettingData; //storage or image buffer
    u32 nPathLen;
} CameraSrvStorageConfig_t;

typedef struct
{
    CameraSrvPicResolution_e eCamPicRes;
    CameraSrvImgQuality_e eCamImgQty;
    ORIENTATION_e eCamOriInfo;
    CameraSrvMultiShot_e eCamMultiShot;
    CameraSrvSticker_e eCamSticker;
    CameraSrvCaptureRotation_e eCamCaptureRotation;
} CameraSrvCaptureConfig_t;

typedef struct
{
    CameraSrvCaptureMode_e  eCaptureMode;
    union
    {
        CameraSrvLomo_e eCamLomo;
        CameraSrvMirror_e eCamMirror;
        CameraSrvPanoramaInfo_t tCamPanoramaInfo;
    }param;
} CameraSrvCaptureAttribute_t;

typedef struct
{
    CameraSrvShutterSound_e eShutSound;
    CameraSrvSoundType_e eSoundType;
    u8 *pSoundBuf;
    u32 nBufLen;
} CameraSrvShutterSoundSetting_t;

typedef struct
{
    CameraSrvVdoResolution_e eCamVdoRes;
    CameraSrvVdoQuality_e eCamVdoQty;
    CameraSrvVdoSound_e eCamVdoSound;
    CameraSrvSizeLimit_e eCamSizeLimit;			        // Video recording size limitation
    CameraSrvTimeLimit_e eCamTimeLimit;			    // Video recording time limitation
} CameraSrvRecordConfig_t;

typedef struct
{
    CameraSrvDev_e             eCamId;               // Main/Sub camera
    u16                        nZoomInfoListSize;    // Size in elements of the pZoomInfoList
    CameraSrvZoomInfo_t        *pZoomInfoList;       // Pointer to a list of resolutions to be queried
} CameraSrvGetCameraInfo_t;

typedef struct
{
    u8 nCaptureCount;   //Count of shutter sound
    u8 nFileNum;       //Number of obtained file/image
    CameraSrvStorage_e eStorageType; //The storage type set by app
    union
    {
        CameraSrvFileName_t* aCaptureFile[CAMERASRV_MAX_MULTISHOT_NUM]; //Used for SD card and phone(external)
        CameraSrvImage_t* aCaptureImage[CAMERASRV_MAX_MULTISHOT_NUM]; //Used for phone(internal)
    } uCapture;
} CameraSrvCaptureFile_t;

#ifdef __CAMERA_V1_ITF__
typedef struct
{
    u32 nEvtCode;
    union
    {
        CameraSrvRetCode_e eRetCode;
        CameraSrvErrCode_e eErrCode; // Notify Rec error type
        u32 nPosition;  //Notify update video position
        u16 bFocused;
    } uNotify;
} CameraSrvCamStatusChange_t;

typedef struct
{
    u32 nEvtCode;
    CameraSrvRetCode_e eRetCode;
} CameraSrvInterruptNotify_t;
#endif

typedef struct
{
    CameraSrvStatusEvt_e eStatusEvt;
    CameraSrvErrCode_e eErrCode; // Notify Rec error type
    union
    {
        u16 bFocused;
        u32 nPosition;  //Notify update video position
        CameraSrvCaptureFile_t *pCaptureFile; //Notify capture files after receive capture finished event(capture end, space full or error)
    } uNotify;
} CameraSrvCamStatusChangeEx_t;

typedef struct
{
    CameraSrvInterruptEvt_e eInterruptEvt;
} CameraSrvInterruptNotifyEx_t;

typedef struct _CameraSrvPicSettings_t
{
    CameraSrvStorageConfig_t *pStorageConfig;
    CameraSrvStorage_e eCamStorage;
    CameraSrvEnv_e eCamShootingMode;
    CameraSrvAntiFlicker_e eCamAntiFlicker;
    CameraSrvAWB_e eCamAWB;
    CameraSrvEffect_e eCamEffect;
    CameraSrvAE_e eCamAE;
    CameraSrvZoom_e eCamZoom;
    CameraSrvEV_e eCamEV;
    CameraSrvFocusMode_e eCamFocusMode;
    CameraSrvVdoStabilizer_e eCamVdoStabilizer;
} CameraSrvSettings_t;

typedef struct
{
    u16 x;
    u16 y;
} CameraSrvFocusPosition_t;

// Callback function definition
typedef void (*CameraSrvCnfCb)(void *pThis, CameraSrvRetCode_e eRetCode);
typedef void (*CameraSrvGetQuotaCb)(void *pThis, u32 nQuota, CameraSrvRetCode_e eRetCode);
typedef void (*CameraSrvGetCameraInfoCb)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvCameraInfo_t *pGetCameraInfo);
#ifdef __CAMERA_V1_ITF__
typedef void (*CameraSrvGetFileCb)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvFileName_t *pGetFileName);
typedef void (*CameraSrvGetImageCb)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvImage_t *pGetImage);
typedef void (*CameraSrvResMgrNotifyCb)(void *pThis, CameraSrvInterruptNotify_t *pCbData);
typedef void (*CameraSrvStatusChangeCb)(void *pThis, CameraSrvCamStatusChange_t *pCbData);
#endif
typedef void (*CameraSrvSaveFileCb)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvFileName_t *pGetFileName);
typedef void (*CameraSrvStopCaptureCb)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvCaptureFile_t *pCaptureFile);
typedef void (*CameraSrvResMgrNotifyCbEx)(void *pThis, CameraSrvInterruptNotifyEx_t *pCbData);
typedef void (*CameraSrvStatusChangeCbEx)(void *pThis, CameraSrvCamStatusChangeEx_t *pCbData);

// Callback data definition

typedef struct
{
    u32 nSrvInstId;
    u32 nAppInstId;
    u32 pfnCallback;
} CameraSrvCusInfo_t;


typedef enum
{
    CameraSrvInit_Start         = 0x0000,
    CameraSrvInit_SetStorage    = 0x0001,
    CameraSrvInit_SetAWB        = 0x0002,
    CameraSrvInit_SetAE         = 0x0004,
    CameraSrvInit_SetZoom       = 0x0008,
    CameraSrvInit_SetEV         = 0x0010,
    CameraSrvInit_SetAntiFlicker= 0x0020,
    CameraSrvInit_SetEffect     = 0x0040,
    CameraSrvInit_SetEnv        = 0x0080,
    CameraSrvInit_SetFocus      = 0x0100,
    CameraSrvInit_SetVS         = 0x0200,
    CameraSrvInit_SetAll        = 0x03ff,
    CameraSrvInit_Finish        = 0x0400,
    CameraSrvInit_Mask          = 0x07ff
}
CameraSrvInitProcess_e;

typedef struct
{
    CameraSrvCusInfo_t *pCallBackDataInfo;
    CameraSrvInitProcess_e eInitProcess;
    CameraSrvSettings_t *pConfigValue;
    u8 nEVSettingCounter;
} CameraSrvInitInfo_t;

#endif /* __MMI_CAMERASRV_DEF_H__ */

