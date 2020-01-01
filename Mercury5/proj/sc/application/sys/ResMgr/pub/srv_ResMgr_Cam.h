/**
* @file srv_ResMgr_Cam.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*   drivers and Resource Manager
*  This header file defines the declaration of operations of Camera.
*
*/

#ifndef __SRV_RESMGR_CAM_H__
#define __SRV_RESMGR_CAM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_cam_itf.h"
#include "MediaRspItf.h"
//#include "MML_Manager.h"
#include "srv_resmgr_mmlcamera_types.h"
#include "srv_resmgr_mmlimage_types.h"
#include "srv_resmgr_mmlvideo_types.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef esl_CamStatus_e ABL_CamStatus_e;
typedef esl_CamMedium_t ABL_CamMedium_t;

typedef struct ABL_CamInit_t_
{
    esl_CamID_e camID;
} ABL_CamInit_t;

typedef struct ABL_CamExit_t_
{
    esl_CamID_e camID;
} ABL_CamExit_t;

typedef struct ABL_CamSetMedium_t_
{
    esl_CamMedium_t camMedium;
} ABL_CamSetMedium_t;

typedef struct ABL_CamSetAWB_t_
{
    esl_CamAWB_e camAWB;
} ABL_CamSetAWB_t;

typedef struct ABL_CamSetAE_t_
{
    esl_CamAE_e camAE;
} ABL_CamSetAE_t;

typedef struct ABL_CamSetZoom_t_
{
    esl_CamZoom_e camZoom;
} ABL_CamSetZoom_t;

typedef struct ABL_CamSetEV_t_
{
    esl_CamEV_e camEV;
} ABL_CamSetEV_t;

typedef struct ABL_CamSetImgEffect_t_
{
    esl_CamImgEffect_e camImgEffect;
} ABL_CamSetImgEffect_t;

typedef struct ABL_CamSetAntiFlicker_t_
{
    esl_CamAntiFlicker_e camAntiFlicker;
} ABL_CamSetAntiFlicker_t;

typedef struct ABL_CamSetNightMode_t_
{
    esl_CamNightMode_e camNightMode;
} ABL_CamSetNightMode_t;

typedef struct ABL_CamSetFlashlightSwitch_t_
{
    esl_CamFlashlightSwitch_e camFlashlightSwitch;
} ABL_CamSetFlashlightSwitch_t;

typedef struct ABL_CamSetFocusMode_t_
{
    esl_CamFocusMode_e camFocusMode;
} ABL_CamSetFocusMode_t;

typedef struct ABL_CamVdoStabilizer_t_
{
    esl_CamVdoStabilizer_e camVdoStabilizer;
}ABL_CamVdoStabilizer_t;

typedef esl_CamDispRegion_t ABL_CamDispRegion_t;

typedef struct ABL_CamPreview_t_
{
    esl_CamPreview_e camPreview;
    esl_CamDispRegion_t camDispRegion;
} ABL_CamPreview_t;

typedef struct ABL_CamCapture_t_
{
    esl_CamJpegSetting_t camJPEGSetting;
} ABL_CamCapture_t;

typedef struct ABL_CamMotionDetect_t_
{
    esl_CamID_e camID;
} ABL_CamMotionDetect_t;

typedef esl_CamJpegSetting_t ABL_CamJpegSetting_t;
typedef esl_CamQRCSetting_t ABL_CamQRCSetting_t;
typedef esl_CamGetQuota_t ABL_CamGetQuota_t;

typedef struct ABL_CamQRCCmd_t_
{
    esl_CamQRCSetting_t camQRCSetting;
} ABL_CamQRCCmd_t;

typedef esl_CamVdoSetting_t ABL_CamVdoSetting_t;
typedef struct ABL_CamRecord_t_
{
    esl_CamVdoSetting_t camVideoSetting;
} ABL_CamRecord_t;

typedef esl_CamGetQRC_t ABL_CamGetQRC_t;

typedef struct ABL_CamGetQRCCmd_t_
{
    esl_CamGetQRC_t camGetQRC;
} ABL_CamGetQRCCmd_t;

typedef struct ABL_CamGetStatus_t_
{
    esl_CamStatus_e camStatus;
} ABL_CamGetStatus_t;

typedef esl_CamFileName_t ABL_CamFileName_t;

typedef struct ABL_CamGetFile_t_
{
    esl_CamFileName_t camFileName;
} ABL_CamGetFile_t;

typedef struct ABL_CamSetStickerCmd_t_
{
    u8 isEnable;
    u8 *pSticker;
} ABL_CamSetStickerCmd_t;

typedef struct ABL_CamRecSaveAction_t_
{
    u8 saveClip;
} ABL_CamRecSaveAction_t;

typedef esl_CamRecSaveInfo_t ABL_CamRecSave_t;
typedef esl_CamAttr_t ABL_CamAttr_t;
typedef esl_CamInfo_t ABL_CamInfo_t;
typedef esl_CamRegion_t ABL_CamRegion_t;
typedef esl_CamImg_t ABL_CamImg_t;

typedef enum ABL_CamErrCode_e_
{
    ABL_CAM_OK,                 //ESL_CAM_OK
    ABL_CAM_FAIL,               //ESL_CAM_FAIL
    ABL_CAM_SKIP,               //ESL_CAM_SKIP
    ABL_CAM_PARAM_ERROR,        //ESL_CAM_PARAM_ERROR
    ABL_CAM_MEM_ALLOC_ERROR,    //ESL_CAM_MEM_ALLOC_ERROR
    ABL_CAM_REJECT,             //ESL_CAM_REJECT
    ABL_CAM_ABORT,              //ESL_CAM_ABORT
    ABL_CAM_TIMEOUT,            //ESL_CAM_TIMEOUT
    ABL_CAM_DENY,
    ABL_CAM_MERGE
} ABL_CamErrCode_e;

typedef struct ABL_CamRspInfo_t_
{
    ABL_CamErrCode_e eErrCode;
    ABL_CamInfo_t tCameraInfo;
    u32 uExtInfo;
} ABL_CamRspInfo_t;

typedef struct DBLCamRemapErrCode_t_
{
    ABL_CamErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLCamRemapErrCode_t;

typedef enum ABL_CamRecError_e_
{
    ABL_CAM_REC_ERROR_NONE,                 //ESL_CAM_REC_ERROR_NONE
    ABL_CAM_REC_ERROR_SPACE_FULL,           //ESL_CAM_REC_ERROR_SPACE_FULL
    ABL_CAM_REC_ERROR_UNKNOW,               //ESL_CAM_REC_ERROR_UNKNOW
    ABL_CAM_REC_ERROR_TIMEOUT,              //ESL_CAM_REC_ERROR_TIMEOUT
    ABL_CAM_REC_ERROR_NOT_SUPPORT,          //ESL_CAM_REC_ERROR_NOT_SUPPORT
    ABL_CAM_REC_ERROR_SDCARD_NOT_DETECTED,  //ESL_CAM_REC_ERROR_SDCARD_NOT_DETECTED
    ABL_CAM_REC_ERROR_SAVE_COMPLETE,        //ESL_CAM_REC_ERROR_SAVE_COMPLETE
    ABL_CAM_REC_ERROR_OVER_SIZE,            //ESL_CAM_REC_ERROR_OVER_SIZE
    ABL_CAM_REC_ERROR_MEMORY_INSUFFICIENCY, //ESL_CAM_REC_ERROR_MEMORY_INSUIFFICIENCY
    ABL_CAM_REC_ERROR_NUM                   //ESL_CAM_REC_ERROR_NUM
} ABL_CamRecError_e;

typedef enum ABL_CamID_e_
{
    ABL_CAM_ID_MAIN,                //ESL_CAM_ID_MAIN
    ABL_CAM_ID_SUB,                 //ESL_CAM_ID_SUB
    ABL_CAM_ID_ATV,                 //ESL_CAM_ID_ATV
    ABL_CAM_ID_NUM
} ABL_CamID_e;

typedef enum ABL_CamMode_e_
{
    ABL_CAMERA,                     //ESL_CAMERA
    ABL_CAMCORDER,                  //ESL_CAMCORDER
    ABL_QRC                         //ESL_QRC
} ABL_CamMode_e;

typedef enum ABL_CamPath_e_
{
    ABL_CAM_PATH_DIR,               //ESL_CAM_PATH_DIR
    ABL_CAM_PATH_PREFIX,            //ESL_CAM_PATH_PREFIX
    ABL_CAM_PATH_ABSOLUTE           //ESL_CAM_PATH_ABSOLUTE
} ABL_CamPath_e;

typedef enum
{
    ABL_CAM_STORAGE_CARD,           //ESL_CAM_STORAGE_CARD
    ABL_CAM_STORAGE_BB,             //ESL_CAM_STORAGE_BB
    ABL_CAM_STORAGE_NAND            //ESL_CAM_STORAGE_NAND
} ABL_CamStorage_e;

typedef enum ABL_CamAttrType_e_
{
    ABL_CAM_AWB,                    //ESL_CAM_AWB
    ABL_CAM_AE,                     //ESL_CAM_AE
    ABL_CAM_AF,                     //ESL_CAM_AF
    ABL_CAM_ZOOM,                   //ESL_CAM_ZOOM
    ABL_CAM_EV,                     //ESL_CAM_EV
    ABL_CAM_ANTIFILCKER,            //ESL_CAM_ANTIFILCKER
    ABL_CAM_IMGEFFECT,              //ESL_CAM_IMGEFFECT
    ABL_CAM_NIGHT,                  //ESL_CAM_NIGHT
    ABL_CAM_FLASHLIGHT,             //ESL_CAM_FLASHLIGHT
    ABL_CAM_FOCUSMODE,              //ESL_CAM_FOCUSMODE
    ABL_CAM_VIDEOSTABILIZER         //ESL_CAM_VIDEOSTABILIZZER
} ABL_CamAttrType_e;

typedef enum ABL_CamAWB_e_
{
    ABL_CAM_AWB_ON,                 //ESL_CAM_AWB_ON
    ABL_CAM_AWB_CLOUDY,             //ESL_CAM_AWB_CLOUDY
    ABL_CAM_AWB_DAYLIGHT,           //ESL_CAM_AWB_DAYLIGHT
    ABL_CAM_AWB_FLUORESCENT,        //ESL_CAM_AWB_FLUORESCENT
    ABL_CAM_AWB_TUNGSTEN            //ESL_CAM_AWB_TUNGSTEN
} ABL_CamAWB_e;

typedef enum ABL_CamAE_e_
{
    ABL_CAM_AE_WHOLE_IMAGE,         //ESL_CAM_AE_WHOLE_IMAGE
    ABL_CAM_AE_CENTRALWIN,          //ESL_CAM_AE_CENTRALWIN
    ABL_CAM_AE_WEIGHTED_CENTRALWIN, //ESL_CAM_AE_WEIGHTED_CENTRALWIN
    ABL_CAM_AE_CENTRAL_POINT        //ESL_CAM_AE_CENTRAL_POINT
} ABL_CamAE_e;

typedef enum ABL_CamZoom_e_
{
    ABL_CAM_ZOOM_MIN,               //ESL_CAM_ZOOM_MIN
    ABL_CAM_ZOOM_IN,                //ESL_CAM_ZOOM_IN
    ABL_CAM_ZOOM_OUT,               //ESL_CAM_ZOOM_OUT
    ABL_CAM_ZOOM_MAX,               //ESL_CAM_ZOOM_MAX
    ABL_CAM_ZOOM_DEFAULT            //ESL_CAM_ZOOM_DEFAULT
} ABL_CamZoom_e;

typedef enum ABL_CamEV_e_
{
    ABL_CAM_EV_MIN,                 //ESL_CAM_EV_MIN
    ABL_CAM_EV_INC,                 //ESL_CAM_EV_INC
    ABL_CAM_EV_DEC,                 //ESL_CAM_EV_DEC
    ABL_CAM_EV_MAX,                 //ESL_CAM_EV_MAX
    ABL_CAM_EV_DEFAULT              //ESL_CAM_EV_DEFAULT
} ABL_CamEV_e;

typedef enum ABL_CamAntiFlicker_e_
{
    ABL_CAM_ANTIFLICKER_OFF,        //ESL_CAM_ANTIFLICKER_OFF
    ABL_CAM_ANTIFLICKER_ON_60HZ,    //ESL_CAM_ANTIFLICKER_ON_60HZ
    ABL_CAM_ANTIFLICKER_ON_50HZ     //ESL_CAM_ANTIFLICKER_ON_50HZ
} ABL_CamAntiFlicker_e;

typedef enum ABL_CamImgEffect_e_
{
    ABL_CAM_IMG_NORMAL,             //ESL_CAM_IMG_NORMAL
    ABL_CAM_IMG_MONO,               //ESL_CAM_IMG_MONO
    ABL_CAM_IMG_SEPIA,              //ESL_CAM_IMG_SEPIA
    ABL_CAM_IMG_NEGATIVE,           //ESL_CAM_IMG_NEGATIVE
    ABL_CAM_IMG_SKETCH,             //ESL_CAM_IMG_SKETCH
    ABL_CAM_IMG_OIL_PAINTING,       //ESL_CAM_IMG_OIL_PAINTING
    ABL_CAM_IMG_AMBOS,              //ESL_CAM_IMG_AMBOS
    ABL_CAM_IMG_MOSAIC,             //ESL_CAM_IMG_MOSAIC
    ABL_CAM_IMG_ZIPPER,             //ESL_CAM_IMG_ZIPPER
    ABL_CAM_IMG_BLUR,               //ESL_CAM_IMG_BLUR
    ABL_CAM_IMG_SEPIAGREEN,         //ESL_CAM_IMG_SEPIAGREEN
    ABL_CAM_IMG_SEPIABLUE,          //ESL_CAM_IMG_SEPIABLUE
    ABL_CAM_IMG_SEPIARED,           //ESL_CAM_IMG_SEPIARED
    ABL_CAM_IMG_GRAYINVERSION,      //ESL_CAM_IMG_GRAYINVERSION
    ABL_CAM_IMG_WHITEBOARD,         //ESL_CAM_IMG_WHITEBOARD
    ABL_CAM_IMG_COPPERCARVING,      //ESL_CAM_IMG_COPPERCARVING
    ABL_CAM_IMG_BLUECARVING,        //ESL_CAM_IMG_BLUECARVING
    ABL_CAM_IMG_BLACKCARVING,       //ESL_CAM_IMG_BLACKCARVING
    ABL_CAM_IMG_WHITECARVING,       //ESL_CAM_IMG_WHITECARVING
    ABL_CAM_IMG_CONTRAST,           //ESL_CAM_IMG_CONTRAST
    ABL_CAM_IMG_SOLARIZATION,       //ESL_CAM_IMG_SOLARIZATION
    ABL_CAM_IMG_USERDEFINED1,       //ESL_CAM_IMG_USERDEFINED1
    ABL_CAM_IMG_USERDEFINED2,       //ESL_CAM_IMG_USERDEFINED2
    ABL_CAM_IMG_USERDEFINED3,       //ESL_CAM_IMG_USERDEFINED3
    ABL_CAM_IMG_USERDEFINED4,       //ESL_CAM_IMG_USERDEFINED4
    ABL_CAM_IMG_USERDEFINED5        //ESL_CAM_IMG_USERDEFINED5
} ABL_CamImgEffect_e;

typedef enum ABL_CamNightMode_e_
{
    ABL_CAM_NORMAL_MODE,            //ESL_CAM_NORMAL_MODE
    ABL_CAM_NIGHT_MODE              //ESL_CAM_NIGHT_MODE
} ABL_CamNightMode_e;

typedef enum ABL_CamFlashlightSwitch_e_
{
    ABL_CAM_FLASHLIGHT_ON,          //ESL_CAM_FLASHLIGHT_ON
    ABL_CAM_FLASHLIGHT_OFF          //ESL_CAM_FLASHLIGHT_OFF
} ABL_CamFlashlightSwitch_e;

typedef enum ABL_CamFocusMode_e_
{
    ABL_CAM_FOCUS_MODE_AUTO_FOCUS,          //ESL_CAM_FOCUS_MODE_AUTO_FOCUS
    ABL_CAM_FOCUS_MODE_TOUCH_TO_FOCUS,      //ESL_CAM_FOCUS_MODE_TOUCH_TO_FOCUS
    ABL_CAM_FOCUS_MODE_INVALID              //ESL_CAM_FOCUS_MODE_INVALID
} ABL_CamFocusMode_e;

typedef enum ABL_CamVdoStabilizer_e_
{
    ABL_CAM_VIDEOSTABILIZER_ON,         //ESL_CAM_VIDEOSTABILIZER_ON
    ABL_CAM_VIDEOSTABILIZER_OFF         //ESL_CAM_VIDEOSTABILIZER_OFF
} ABL_CamVdoStabilizer_e;

typedef enum ABL_CamRotate_e_
{
    ABL_CAM_ROTATE_NONE,            //ESL_CAM_ROTATE_NONE
    ABL_CAM_ROTATE_90,              //ESL_CAM_ROTATE_90
    ABL_CAM_ROTATE_180,             //ESL_CAM_ROTATE_180
    ABL_CAM_ROTATE_270              //ESL_CAM_ROTATE_270
} ABL_CamRotate_e;

typedef enum ABL_CamCaptureRotate_e_
{
    ABL_CAM_ROTATION_0,             //ESL_CAL_ROTATION_0
    ABL_CAM_ROTATION_90,            //ESL_CAL_ROTATION_90
    ABL_CAM_ROTATION_180,           //ESL_CAL_ROTATION_180
    ABL_CAM_ROTATION_270            //ESL_CAL_ROTATION_270
} ABL_CamCaptureRotate_e;


typedef enum ABL_CamPreview_e_
{
    ABL_CAM_PREVIEW_OFF,            //ESL_CAM_PREVIEW_OFF
    ABL_CAM_PREVIEW_ON,             //ESL_CAM_PREVIEW_ON
    ABL_CAM_PREVIEW_CAMCORDER_ON,   //ESL_CAM_PREVIEW_CAMCORDER_ON
    ABL_CAM_PREVIEW_ASPECTRATIO_ON, //ESL_CAM_PREVIEW_ASPECTRATIO_ON
    ABL_CAM_PREVIEW_QRC_ON          //ESL_CAM_PREVIEW_QRC_ON
} ABL_CamPreview_e;

typedef enum ABL_CamCaptureRes_e_
{
    ABL_CAM_3264_2448,              //ESL_CAM_3264_2448,
    ABL_CAM_3072_2304,              //ESL_CAM_3072_2304,
    ABL_CAM_3032_2008,              //ESL_CAM_3032_2008,
    ABL_CAM_2560_1920,              //ESL_CAM_2560_1920,
    ABL_CAM_2240_1680,              //ESL_CAM_2240_1680,
    ABL_CAM_2048_1536,              //ESL_CAM_2048_1536
    ABL_CAM_1600_1200,              //ESL_CAM_1600_1200
    ABL_CAM_1280_1024,              //ESL_CAM_1280_1024
    ABL_CAM_1024_768,               //ESL_CAM_1024_768
    ABL_CAM_800_600,                //ESL_CAM_800_600
    ABL_CAM_640_480,                //ESL_CAM_640_480
    ABL_CAM_320_240,                //ESL_CAM_320_240
    ABL_CAM_240_320,                //ESL_CAM_240_320
    ABL_CAM_176_220,                //ESL_CAM_176_220
    ABL_CAM_160_120,                //ESL_CAM_160_120
    ABL_CAM_128_128,                //ESL_CAM_128_128
    ABL_CAM_96_96,                  //ESL_CAM_96_96
    ABL_CAM_WALLPAPER_PORTRAIT,     //ESL_CAM_WALLPAPER_PORTRAIT
    ABL_CAM_WALLPAPER_LANDSCAPE     //ESL_CAM_WALLPAPER_LANDSCAPE
} ABL_CamCaptureRes_e;

typedef enum ABL_CamShotMode_e_
{
    ABL_CAM_SINGLE,                 //ESL_CAM_SINGLE
    ABL_CAM_ROTATION,               //ESL_CAM_ROTATION
    ABL_CAM_PHOTOSTICKER,           //ESL_CAM_PHOTOSTICKER
    ABL_CAM_PANORAMA,               //ESL_CAM_PANORAMA
    ABL_CAM_LOMO_4LENS,             //ESL_CAM_LOMO_4LENS
    ABL_CAM_MIRROR                  //ESL_CAM_MIRROR
} ABL_CamShotMode_e;

typedef enum ABL_CamQuality_e_
{
    ABL_CAM_QUALITY_LOW,            //ESL_CAM_QUALITY_LOW
    ABL_CAM_QUALITY_NORMAL,         //ESL_CAM_QUALITY_NORMAL
    ABL_CAM_QUALITY_HIGH            //ESL_CAM_QUALITY_HIGH
} ABL_CamQuality_e;

typedef enum ABL_CamRecRes_e_
{
    ABL_CAM_VDO_704_576,            //ESL_CAM_VDO_704_576
    ABL_CAM_VDO_352_288,            //ESL_CAM_VDO_352_288
    ABL_CAM_VDO_176_144,            //ESL_CAM_VDO_176_144
    ABL_CAM_VDO_128_96,             //ESL_CAM_VDO_128_96
    ABL_CAM_VDO_640_480,            //ESL_CAM_VDO_640_480
    ABL_CAM_VDO_320_240,            //ESL_CAM_VDO_320_240
    ABL_CAM_VDO_400_240,            //ESL_CAM_VDO_400_240
    ABL_CAM_VDO_480_320,            //ESL_CAM_VDO_480_320
    ABL_CAM_VDO_720_576,            //ESL_CAM_VDO_720_576
    ABL_CAM_VDO_720_480             //ESL_CAM_VDO_720_480
} ABL_CamRecRes_e;

typedef enum ABL_CamVdoCodec_e_
{
    ABL_CAM_VDO_CODEC_H263,         //ESL_CAM_VDO_CODEC_H263
    ABL_CAM_VDO_CODEC_MPEG4         //ESL_CAM_VDO_CODEC_MPEG4
}ABL_CamVdoCodec_e;

typedef enum ABL_CamAudCodec_e_
{
    ABL_CAM_AUD_CODEC_AMR_NB,       //ESL_CAM_AUD_CODEC_AMR_NB
    ABL_CAM_AUD_CODEC_AMR_WB,       //ESL_CAM_AUD_CODEC_AMR_WB
    ABL_CAM_AUD_CODEC_MP3           //ESL_CAM_AUD_CODEC_MP3
}ABL_CamAudCodec_e;

typedef enum ABL_CamVdoFileType_e_
{
    ABL_CAM_VDO_FILE_TYPE_3GP,      //ESL_CAM_VDO_FILE_TYPE_3GP
    ABL_CAM_VDO_FILE_TYPE_MP4       //ESL_CAM_VDO_FILE_TYPE_MP4
}ABL_CamVdoFileType_e;

typedef enum ABL_CamVdoLimitType_e_
{
    ABL_CAM_VDO_SIZE_LIMIT,         //ESL_CAM_VDO_SIZE_LIMIT
    ABL_CAM_VDO_TIME_LIMIT          //ESL_CAM_VDO_TIME_LIMIT
} ABL_CamVdoLimitType_e;

typedef enum ABL_CamSoundPath_e_
{
    ABL_CAM_SOUND_DEFAULT,          //ESL_CAM_SOUND_DEFAULT
    ABL_CAM_SOUND_DOWNLOAD,         //ESL_CAM_SOUND_DOWNLOAD
    ABL_CAM_SOUND_CARD              //ESL_CAM_SOUND_CARD
} ABL_CamSoundPath_e;

typedef enum ABL_CamOrientationInfo_e_
{
    ABL_ORIENTATION_TOP_LEFT,         //ESL_ORIENTATION_TOP_LEFT
    ABL_ORIENTATION_TOP_RIGHT,        //ESL_ORIENTATION_TOP_RIGHT
    ABL_ORIENTATION_BOTTOM_RIGHT,     //ESL_ORIENTATION_BOTTOM_RIGHT
    ABL_ORIENTATION_BOTTOM_LEFT,      //ESL_ORIENTATION_BOTTOM_LEFT
    ABL_ORIENTATION_LEFT_TOP,         //ESL_ORIENTATION_LEFT_TOP
    ABL_ORIENTATION_RIGHT_TOP,        //ESL_ORIENTATION_RIGHT_TOP
    ABL_ORIENTATION_RIGHT_BOTTOM,     //ESL_ORIENTATION_RIGHT_BOTTOM
    ABL_ORIENTATION_LEFT_BOTTOM,      //ESL_ORIENTATION_LEFT_BOTTOM
} ABL_CamOrientationInfo_e;

typedef enum ABL_CamRecordSave_e_
{
    ABL_CAM_REC_SAVE_DEFERRING,       //ESL_CAM_DEFERRING_SAVE,     /**< Deferring Save, defer the decision to save or abort the clip */
    ABL_CAM_REC_SAVE_DECIDING,        //ESL_CAM_DECIDING_SAVE,      /**< Deciding Save */
    ABL_CAM_REC_SAVE_DEFERRING_CHECK, //ESL_CAM_DEFERRING_CHECK     /**< Deferring Check, check if there is clip not saved completely */
} ABL_CamRecSaveMode_e;

typedef MmlVideoStartRecording_t    ABL_VideoStartRecording_t;
typedef MmlCameraStartPreview_t     ABL_CameraStartPreview_t;
typedef MmlImageEncodeImage_t       ABL_ImageEncodeImage_t;
typedef MmlImageBufferParam_t       ABL_ImageBufferParam_t;
typedef MmlVideoSetRecordingSetting_t ABL_CamSetRecordSetting_t;
typedef MmlImageGetCaptureInfo_t    ABL_ImageGetCaptureInfo_t;
typedef MmlCameraGetCameraInfo_t    ABL_CameraGetCameraInfo_t;
typedef MmlImageEncodeCompleteInfo_t ABL_CamEncodeComplete_t;
typedef MmlCameraSetMotionDetection_t       ABL_CameraSetMotionDetection_t;
typedef MmlImageGetCaptureCapability_t      ABL_CamGetCaptureCapability_t;
typedef MmlVideoGetRecordingCapability_t    ABL_CamGetRecordingCapability_t;
typedef esl_CamCaptureCapability_t          ABL_CamCaptureCap_t;
typedef esl_CamRecordingCapability_t        ABL_CamRecordingCap_t;

typedef struct ABL_CamGetRecCapInfo_t_
{
    ABL_CamErrCode_e eErrCode;
    ABL_CamRecordingCap_t tCamRecCap;
} ABL_CamGetRecCapInfo_t;

/**
 *  @brief The structure defines the notification value for application layer.
 *          should sync. with esl_CamNotifyInfo_t
 */
typedef struct
{
    MediaRspId_e camNotifyType;
    union
    {
        u16 bFocused;
        u32 position;
        ABL_CamRecError_e recError;
        ABL_CamEncodeComplete_t tEncodeCompleteInfo;
    } notify;
} ABL_CamNotifyInfo_t;

typedef void (*ABL_CamCb)(u16 uSenderId, u32 uUserValue, ABL_CamErrCode_e eErrCode, ABL_CamInfo_t *pCamInfo);
typedef struct
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_CamCb pfnCb;
} ABL_CamCb_t;

typedef struct ABL_CamSetAttribute_t_
{
    ABL_CamAttrType_e eAttr;
    union
    {
        ABL_CamSetAWB_t tCamSetAWBParams;
        ABL_CamSetAE_t tCamSetAEParams;
        ABL_CamSetZoom_t tCamSetZoomParams;
        ABL_CamSetEV_t tCamSetEVParams;
        ABL_CamSetImgEffect_t tCamSetImgEffectParams;
        ABL_CamSetAntiFlicker_t tCamSetAntiFlickerParams;
        ABL_CamSetNightMode_t tCamSetNightModeParams;
        ABL_CamSetFlashlightSwitch_t tCamSetFlashlightSwitchParams;
        ABL_CamSetFocusMode_t tCamSetFocusModeParams;
        ABL_CamVdoStabilizer_t tCamVdoStabilizerParams;
    } attr;
} ABL_CamSetAttribute_t;

typedef struct CameraCmd_t_
{
    ABL_CamCb_t *pCbParams;
    u32 uHandle;
    union
    {
        ABL_VideoStartRecording_t tVideoStartRecording;
        ABL_CameraStartPreview_t tCameraStartPreview;
        ABL_ImageEncodeImage_t tEncodeImage;               ///< Encode image (jpeg)
        ABL_ImageBufferParam_t tImageBufferParam;
        ABL_CamSetRecordSetting_t tCamSetRecSettingParams;
        ABL_ImageGetCaptureInfo_t tImageGetCaptureInfo;
        ABL_CameraGetCameraInfo_t tCameraGetCameraInfo;
        ABL_CameraSetMotionDetection_t tCameraSetMotionDetection;  ///< Motion Detection
        ABL_CamGetCaptureCapability_t tCamGetCaptureCapability;
        ABL_CamGetRecordingCapability_t tCamGetRecordingCapability;
        ABL_CamInit_t tCamInitParams;
        ABL_CamExit_t tCamExitParams;
        ABL_CamSetMedium_t tCamSetMediumParams;
        ABL_CamSetAttribute_t tCamSetAttributeParams;
        ABL_CamPreview_t tCamPreviewParams;
        ABL_CamCapture_t tCamCaptureParams;
        ABL_CamQRCCmd_t tCamQRCCmdParams;
        ABL_CamRecord_t tCamRecordParams;
        ABL_CamRecSave_t tCamRecSaveParams;
        ABL_CamGetQRCCmd_t tCamGetQRCParams;
        ABL_CamGetStatus_t tCamGetStatusParams;
        ABL_CamGetFile_t tCamGetFileParams;
        ABL_CamSetStickerCmd_t tCamSetStickerParams;
        ABL_CamImg_t tCamImageParams;
        ABL_CamGetQuota_t tCamGetQuotaParams;
        ABL_CamMotionDetect_t tCamMotionDetectParams;
    } tParams;
} CameraCmd_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ABL_CmnErrCode_e ABL_CamOpenSessionReq(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamCloseSessionReq(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamOpen(ResMgr_AppId_e eAppId, ABL_CamID_e eCamID, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamClose(ResMgr_AppId_e eAppId, ABL_CamID_e eCamID, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamSetConfig(ResMgr_AppId_e eAppId, ABL_CamMedium_t *tCamMedium, ABL_CamCb_t *pCamCb);
void ABL_CamGetConfig(u8 *pPath, u16 *pPathLen);
ABL_CmnErrCode_e ABL_CamSetAttribution(ResMgr_AppId_e eAppId, ABL_CamAttr_t *pCamAttr, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamPreview(ResMgr_AppId_e eAppId, ABL_CamPreview_e eCamPreview, ABL_CamDispRegion_t *pCamDispRegion, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamFocus(ResMgr_AppId_e eAppId,ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamCapture(ResMgr_AppId_e eAppId, ABL_CamJpegSetting_t *pCamJpegSetting, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamCaptureStop(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamAbortPanoramaCapture(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
void ABL_CamQRCStart(ResMgr_AppId_e eAppId, ABL_CamQRCSetting_t *pCamQRCSetting, ABL_CamCb_t *pCamCb);
void ABL_CamQRCStop(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamRecordStart(ResMgr_AppId_e eAppId, ABL_CamVdoSetting_t *pCamVdoSetting, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamRecordStop(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamQueryNoneSavingFile(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamDeleteTempVideoFile(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamSaveVideoFile(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamAbortSavingVideoFileAction(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamGetFileName(ResMgr_AppId_e eAppId, ABL_CamFileName_t *pCamFileName, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamGetImage(ResMgr_AppId_e eAppId, ABL_CamImg_t *pCamImg, ABL_CamCb_t *pCamCb);
void ABL_CamGetQRC(ResMgr_AppId_e eAppId, ABL_CamGetQRC_t *pCamGetQRC, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamSetSticker(ResMgr_AppId_e eAppId, u8 uEnable, u8 *pSticker, ABL_CamCb_t *pCamCb);
void ABL_CamGetStatus(ResMgr_AppId_e eAppId, ABL_CamStatus_e eCamStatus, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamGetImage(ResMgr_AppId_e eAppId, ABL_CamImg_t *pCamImg, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamGetCaptureQuota(ResMgr_AppId_e eAppId, ABL_CamGetQuota_t* ptGetQuotaSetting, ABL_CamCb_t *pCamCb);
void ABL_CamEnableMotionDetect(ResMgr_AppId_e eAppId, ABL_CamID_e eCamId, ABL_CamCb_t *pCamCb);
void ABL_CamDisableMotionDetect(ResMgr_AppId_e eAppId, ABL_CamID_e eCamId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamSetRecordSetting(ResMgr_AppId_e eAppId, ABL_CamSetRecordSetting_t *pCamRecSetting, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamSaveRecordingFile(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamDiscardRecordingFile(ResMgr_AppId_e eAppId, ABL_CamCb_t *pCamCb);
ABL_CmnErrCode_e ABL_CamGetCameraInfo(ResMgr_AppId_e eAppId, ABL_CameraGetCameraInfo_t *pGetCameraInfo_t, ABL_CamCb_t *pCamCb);
void ABL_CamGetCaptureCapability(ResMgr_AppId_e eAppId, ABL_CamGetCaptureCapability_t *pCamGetCaptureCapability, ABL_CamCb_t *pCamCb);
void ABL_CamGetRecordingCapability(ResMgr_AppId_e eAppId, ABL_CamGetRecordingCapability_t *pCamGetRecordingCapability, ABL_CamCb_t *pCamCb);
void ABL_CamGetCaptureQuotaInfo(ResMgr_AppId_e eAppId, ABL_ImageGetCaptureInfo_t *pImageGetCaptureInfo, ABL_CamCb_t *pCamCb);
esl_CamAttrType_e ABL_CamRemapAttrType(ABL_CamAttrType_e eAttr);
esl_CamAWB_e ABL_CamRemapAWBAttr(ABL_CamAWB_e eAWB);
esl_CamAE_e ABL_CamRemapAEAttr(ABL_CamAE_e eAE);
esl_CamZoom_e ABL_CamRemapZoomAttr(ABL_CamZoom_e eZoom);
esl_CamEV_e ABL_CamRemapEVAttr(ABL_CamEV_e eEV);
esl_CamAntiFlicker_e ABL_CamRemapAntiFlickerAttr(ABL_CamAntiFlicker_e eAntiFlicker);
esl_CamImgEffect_e ABL_CamRemapImgEffectAttr(ABL_CamImgEffect_e eImgEffect);
esl_CamNightMode_e ABL_CamRemapNightModeAttr(ABL_CamNightMode_e eNightMode);
esl_CamFlashlightSwitch_e ABL_CamRemapFlashlightAttr(ABL_CamFlashlightSwitch_e eFlashlightSwitch);
esl_CamFocusMode_e ABL_CamRemapFocusModeAttr(ABL_CamFocusMode_e eFocusMode);
esl_CamRotate_e ABL_CamRemapRotateAngle(ABL_CamRotate_e eRotate);
esl_CamRotation_e ABL_CamRemapCaptureRotateAngle(ABL_CamCaptureRotate_e eRotate);
esl_CamVdoStabilizer_e ABL_CamRemapVideoStabilizer(ABL_CamVdoStabilizer_e eVideoStabilizer);
esl_CamCaptureRes_e ABL_CamRemapCpatureRes(ABL_CamCaptureRes_e eCaptureRes);
esl_CamQuality_e ABL_CamRemapCamQuality(ABL_CamQuality_e eCamQuality);
esl_CamOrientationInfo_e ABL_CamRemapOriInfo(ABL_CamOrientationInfo_e eOriInfo);
esl_CamShotMode_e ABL_CamRemapShotMode(ABL_CamShotMode_e eShotMode);
esl_CamRecRes_e ABL_CamRemapRecRes(ABL_CamRecRes_e eRecRes);
esl_CamVdoLimitType_e ABL_CamRemapVdoLimitType(ABL_CamVdoLimitType_e eLimitType);
esl_CamSoundPath_e ABL_CamRemapSoundPath(ABL_CamSoundPath_e eSoundPath);
esl_CamPath_e ABL_CamRemapCamPath(ABL_CamPath_e ePath);
esl_CamMode_e ABL_CamRemapCamMode(ABL_CamMode_e emode);
esl_CamStorage_e ABL_CamRemapCamStorage(ABL_CamStorage_e eStorage);
esl_CamVdoCodec_e ABL_CamRemapCamVdoCodec(ABL_CamVdoCodec_e eVdoCodec);
esl_CamAudCodec_e ABL_CamRemapCamAudCodec(ABL_CamAudCodec_e eAudCodec);
esl_CamVdoFileType_e ABL_CamRemapCamVdoFileType(ABL_CamVdoFileType_e eVdoFileType);
MmlCameraSensorSource_e ABL_CamRemapSensorSource(ABL_CamID_e eCamId);
MmlCameraImageEffect_e ABL_CamRemapLomoEffectAttr(esl_CamImgEffect_e eImgEffect);
#endif //__SRV_RESMGR_CAM_H__


