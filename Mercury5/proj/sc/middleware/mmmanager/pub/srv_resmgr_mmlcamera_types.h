////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_resmgr_mmlcamera_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLCAMERA_TYPES_H__
#define __SRV_RESMGR_MMLCAMERA_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerCamera
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseCameraId_e_)
{
    /* Camera Init */
    MML_UCID_CAMERA_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_CAMERA),
    MML_UCID_CAMERA_REG_NOTIFY_CALLBACK = MML_UCID_CAMERA_INIT_BASE,        ///< 00080000 = Reg notify callback
    MML_UCID_CAMERA_UNREG_NOTIFY_CALLBACK,                                  ///< 00080001 = Unreg notify callback
    MML_UCID_CAMERA_OPEN,                                                   ///< 00080002 = Open
    MML_UCID_CAMERA_CLOSE,                                                  ///< 00080003 = Close
    MML_UCID_CAMERA_INIT_CATEGORY,

    /* Camera Get */
    MML_UCID_CAMERA_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_CAMERA),
    MML_UCID_CAMERA_GET_CAMERA_INFO = MML_UCID_CAMERA_GET_BASE,             ///< 00080100 = Get camera information
    MML_UCID_CAMERA_GET_DIGITAL_ZOOM,                                       ///< 00080101 = Get digital zoom
    MML_UCID_CAMERA_GET_PREVIEW_FRAME,                                      ///< 00080102 = Get preview frame
    MML_UCID_CAMERA_GET_CATEGORY,

    /* Camera Set */
    MML_UCID_CAMERA_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_CAMERA),
    MML_UCID_CAMERA_SET_DIGITAL_ZOOM = MML_UCID_CAMERA_SET_BASE,            ///< 00080200 = Set digital zoom
    MML_UCID_CAMERA_SET_EXPOSURE,                                           ///< 00080201 = Set exposure
    MML_UCID_CAMERA_SET_WHITE_BALANCE,                                      ///< 00080202 = Set white balance
    MML_UCID_CAMERA_SET_FOCUS,                                              ///< 00080203 = Set Focus
    MML_UCID_CAMERA_SET_EV,                                                 ///< 00080204 = Set EV
    MML_UCID_CAMERA_SET_ANTI_FLICKER,                                       ///< 00080205 = Set anti_flicker
    MML_UCID_CAMERA_SET_IMAGE_EFFECT,                                       ///< 00080206 = Set image effect
    MML_UCID_CAMERA_SET_NIGHT_MODE,                                         ///< 00080207 = Set night mode
    MML_UCID_CAMERA_SET_SCENE_MODE,                                         ///< 00080208 = Set scene mode
    MML_UCID_CAMERA_SET_FLASH_MODE,                                         ///< 00080209 = Set flash mode
    MML_UCID_CAMERA_SET_MOTION_DETECTION,                                   ///< 0008020a = Set motion detection
    MML_UCID_CAMERA_SET_FRAME_BUFFER_SIZE,									///< 0008020b = Set frame buffer size
    MML_UCID_CAMERA_SET_VIDEO_STABILIZER,                                   ///< 0008020c = Set video stabilizer
    MML_UCID_CAMERA_SET_AUTOFOCUS_CAPTURE,                                  ///< 0008020c = Set auto focus capture
	MML_UCID_CAMERA_SET_CATEGORY,

    /* Camera Execute */
    MML_UCID_CAMERA_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_CAMERA),
    MML_UCID_CAMERA_START_PREVIEW = MML_UCID_CAMERA_EXECUTE_BASE,           ///< 00080300 = Start preview
    MML_UCID_CAMERA_STOP_PREVIEW,                                           ///< 00080301 = Stop preview
    MML_UCID_CAMERA_LOCK_AUTO,                                              ///< 00080302 = Lock auto
    MML_UCID_CAMERA_DETECT_SENSOR,                                          ///< 00080303 = Detect sensor
    MML_UCID_CAMERA_START_AUTOFOCUS,                                        ///< 00080304 = Start auto focus
    MML_UCID_CAMERA_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_CAMERA_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerCamera
    @brief      Response results
*/
typedef enum
{
    /* Common */
    CAMERA_ERROR_SUCCESS = 0,
    CAMERA_ERROR_FAIL,
    CAMERA_ERROR_PARAMETER_INVALID,
    CAMERA_ERROR_STATE_CHANGE,
    CAMERA_ERROR_ACCEPT,
    CAMERA_ERROR_IGNORE,
    CAMERA_ERROR_REJECT,
    CAMERA_ERROR_TIMEOUT,
    CAMERA_ERROR_ALLOCATE_FAIL,
    CAMERA_ERROR_MEMORY_FAILURE,
    /* */
    CAMERA_ERROR_NUM
} MmlCameraResult_e;

/** @ingroup    MMLayerCamera
    @brief      States
*/
typedef enum
{
    CAMERA_STATE_CLOSED = 0,
    /* Preview */
    CAMERA_STATE_PREVIEW_ON,
    CAMERA_STATE_PREVIEW_OFF,
    /* Motion Detection */
    CAMERA_STATE_MOTION_DETECTING,
    /* */
    CAMERA_STATE_DONTCARE,
    CAMERA_STATE_NUM
} MmlCameraState_e;

/** @ingroup    MMLayerCamera
    @brief      Events
*/
typedef enum
{
    /* Common */
    CAMERA_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_CAMERA),
    CAMERA_EVENT_RUNTIME_ERROR,
    CAMERA_EVENT_AUTOFOCUS_COMPLETE,
    /* Video Chat */
    CAMERA_EVENT_GET_FRAME_COMPLETE,
    /* Magic Eye */
	CAMERA_EVENT_MOTION_DETECTED,
    /* */
    CAMERA_EVENT_DONTCARE,
    CAMERA_EVENT_ALL,
    CAMERA_EVENT_NUM
} MmlCameraEvent_e;

/** @ingroup    MMLayerCamera
    @brief      Zoom statuses
*/
typedef enum
{
    CAMERA_ZOOMSTATUS_NOTOUTOFLIMIT = 0,     ///< Not out of limit
    CAMERA_ZOOMSTATUS_REACHMIN,              ///< Reach minimum
    CAMERA_ZOOMSTATUS_REACHMAX,              ///< Reach maximum
    CAMERA_ZOOMSTATUS_DEFAULT,               ///< Default zoom setting
    /* */
    CAMERA_ZOOMSTATUS_NUM
} MmlCameraZoomStatus_e;

/** @ingroup    MMLayerCamera
    @brief      Sensor source
*/
typedef enum MmlCameraSensorSource_e_
{
    CAMERA_SENSOR_PRIMARY = 0,   ///< Primary sensor
    CAMERA_ATV               ,   ///< ATV
    CAMERA_SENSOR_SECONDARY,     ///< Secondary sensor
    /* */
    CAMERA_SENSOR_NUM
} MmlCameraSensorSource_e;

/** @ingroup    MMLayerCamera
    @brief      Rotation angles
*/
typedef enum
{
    CAMERA_ROTATION_0 = 0,    ///< 0 degree
    CAMERA_ROTATION_90,       ///< 90 degree
    CAMERA_ROTATION_180,      ///< 180 degree
    CAMERA_ROTATION_270,      ///< 270 degree
    /* */
    CAMERA_ROTATION_NUM
} MmlCameraRotationAngle_e;

/** @ingroup    MMLayerCamera
    @brief      Zoom levels
*/
typedef enum
{
    CAMERA_ZOOMLEVEL_1X = 0,     ///< 1x
    CAMERA_ZOOMLEVEL_1X3,        ///< 1.3x
    CAMERA_ZOOMLEVEL_1X6,        ///< 1.6x
    CAMERA_ZOOMLEVEL_2X,         ///< 2x
    CAMERA_ZOOMLEVEL_2X5,        ///< 2.5x
    CAMERA_ZOOMLEVEL_3X2,        ///< 3.2x
    CAMERA_ZOOMLEVEL_4X,         ///< 4x
    /* */
    CAMERA_ZOOMLEVEL_NUM
} MmlCameraZoomLevel_e;

/** @ingroup    MMLayerCamera
    @brief      Exposure modes
*/
typedef enum
{
    CAMERA_EXPOSUREMODE_MANUAL = 0,    ///< Manual (AE off)
    CAMERA_EXPOSUREMODE_AUTO,          ///< Auto exposure
    /* */
    CAMERA_EXPOSUREMODE_NUM
} MmlCameraExposureMode_e;

/** @ingroup    MMLayerCamera
    @brief      AE Regions
*/
typedef enum
{
    CAMERA_AEREGION_WHOLEIMAGE = 0,         ///< Whole image
    CAMERA_AEREGION_CENTRALWINDOW,          ///< Central window
    CAMERA_AEREGION_WEIGHTEDCENTERWINDOW,   ///< Weighted center window
    CAMERA_AEREGION_CENTRALPOINT,           ///< Central point
    /* */
    CAMERA_AEREGION_NUM
} MmlCameraAERegion_e;

/** @ingroup    MMLayerCamera
    @brief      White balance modes
*/
typedef enum
{
    CAMERA_WHITEBALANCEMODE_MANUAL = 0,     ///< Manual (AWB off)
    CAMERA_WHITEBALANCEMODE_AUTO,           ///< Auto white balance
    CAMERA_WHITEBALANCEMODE_CLOUDY,         ///< Cloudy
    CAMERA_WHITEBALANCEMODE_DAYLIGHT,       ///< Daylight
    CAMERA_WHITEBALANCEMODE_FLUORESCENT,    ///< Fluorescent
    CAMERA_WHITEBALANCEMODE_TUNGSTEN,       ///< Tungsten
    /* */
    CAMERA_WHITEBALANCEMODE_NUM
} MmlCameraWhiteBalanceMode_e;

/** @ingroup    MMLayerCamera
    @brief      Focus modes
*/
typedef enum
{
    CAMERA_FOCUSMODE_MANUAL = 0,    ///< Manual (AF off)
    CAMERA_FOCUSMODE_AUTO,          ///< Auto focus
    /* */
    CAMERA_FOCUSMODE_NUM
} MmlCameraFocusMode_e;

/** @ingroup    MMLayerCamera
    @brief      AF Region
*/
typedef enum
{
    CAMERA_AFREGION_CENTRALSPOT = 0,    ///< Central spot
    CAMERA_AFREGION_CENTRALWINDOW,      ///< Central window
    CAMERA_AFREGION_FACEDETECTION,      ///< Face detection
    /* */
    CAMERA_AFREGION_NUM
} MmlCameraAFRegion_e;

/** @ingroup    MMLayerCamera
    @brief      EV levels
*/
typedef enum
{
    CAMERA_EVLEVEL_DEFAULT = 0,    ///< Default
    CAMERA_EVLEVEL_MAXIMUM,        ///< Maximum
    CAMERA_EVLEVEL_MINIMUM,        ///< Minimum
    CAMERA_EVLEVEL_INCREMENT,      ///< +1
    CAMERA_EVLEVEL_DECREMENT,      ///< -1
    /* */
    CAMERA_EVLEVEL_NUM
} MmlCameraEVLevel_e;

/** @ingroup    MMLayerCamera
    @brief      Frequencies
*/
typedef enum MmlCameraFrequency_e_
{
    CAMERA_FREQUENCY_50HZ = 0,    ///< 50 Hz
    CAMERA_FREQUENCY_60HZ,        ///< 60 Hz
    /* */
    CAMERA_FREQUENCY_NUM
} MmlCameraFrequency_e;

/** @ingroup    MMLayerCamera
    @brief      Image effects
*/
typedef enum
{
    CAMERA_IMAGEEFFECT_NORMAL = 0,     ///< Normal
    CAMERA_IMAGEEFFECT_MONO,           ///< Mono
    CAMERA_IMAGEEFFECT_SEPIA,          ///< Sepia
    CAMERA_IMAGEEFFECT_NEGATIVE,       ///< Nagative
    CAMERA_IMAGEEFFECT_SKETCH,         ///< Sketch
    CAMERA_IMAGEEFFECT_OILPAINTING,    ///< Oil painting
    CAMERA_IMAGEEFFECT_AMBOS,          ///< Ambos
    CAMERA_IMAGEEFFECT_MOSAIC,         ///< Mosaic
    CAMERA_IMAGEEFFECT_ZIPPER,         ///< Zipper
    CAMERA_IMAGEEFFECT_BLUR,           ///< Blur
    CAMERA_IMAGEEFFECT_SEPIAGREEN,     ///< Sepia green
    CAMERA_IMAGEEFFECT_SEPIABLUE,      ///< Sepia blue
    CAMERA_IMAGEEFFECT_SEPIARED,       ///< Sepia red
    CAMERA_IMAGEEFFECT_GRAYINVERSION,  ///< Gray inversion
    CAMERA_IMAGEEFFECT_WHITEBOARD,     ///< White board
    CAMERA_IMAGEEFFECT_COPPERCARVING,  ///< Copper carving
    CAMERA_IMAGEEFFECT_BLUECARVING,    ///< Blue carving
    CAMERA_IMAGEEFFECT_BLACKCARVING,   ///< Black carving
    CAMERA_IMAGEEFFECT_WHITECARVING,   ///< White carving
    CAMERA_IMAGEEFFECT_CONTRAST,       ///< Contrast
    CAMERA_IMAGEEFFECT_SOLARIZATION,   ///< Solarization
    CAMERA_IMAGEEFFECT_USERDEFINED1,   ///< User defined 1
    CAMERA_IMAGEEFFECT_USERDEFINED2,   ///< User defined 2
    CAMERA_IMAGEEFFECT_USERDEFINED3,   ///< User defined 3
    CAMERA_IMAGEEFFECT_USERDEFINED4,   ///< User defined 4
    CAMERA_IMAGEEFFECT_USERDEFINED5,   ///< User defined 5
    /* */
    CAMERA_IMAGEEFFECT_NUM
} MmlCameraImageEffect_e;

/** @ingroup    MMLayerCamera
    @brief      Scene modes
*/
typedef enum
{
    CAMERA_SCENEMODE_OFF = 0,      ///< Off
    CAMERA_SCENEMODE_AUTO,         ///< Auto
    CAMERA_SCENEMODE_LANDSCAPE,    ///< Landscape
    CAMERA_SCENEMODE_PORTRAIT,     ///< Portrait
    CAMERA_SCENEMODE_NIGHT,        ///< Night
    CAMERA_SCENEMODE_SUNSET,       ///< Sunset
    /* */
    CAMERA_SCENEMODE_NUM
} MmlCameraSceneMode_e;

/** @ingroup    MMLayerCamera
    @brief      Preview modes
*/
typedef enum
{
    CAMERA_PREVIEWMODE_NORMAL = 0,        ///< Normal preview
    CAMERA_PREVIEWMODE_VIDEORECORDING,    ///< Video recording preview
    CAMERA_PREVIEWMODE_VIDEOCHAT,         ///< Video chat preview
    /* */
    CAMERA_PREVIEWMODE_NUM
} MmlCameraPreviewMode_e;

/** @ingroup    MMLayerCamera
    @brief      In-memory source/destination, used to hold input/output data
*/
typedef	struct
{
    u8      *pBuffer;       ///< Pointer to the data buffer
    u32     nBufferSize;    ///< Size in bytes of the data buffer
    u32     nDataSize;      ///< Read/Write size in bytes of data in the data buffer
} MmlCameraMemoryParam_t;

/** @ingroup    MMLayerCamera
    @brief      Rectangle
*/
typedef struct
{
    u16     nLeft;      ///< x-position of the top left corner of rectangle
    u16     nTop;       ///< y-position of the top left corner of rectangle
    u16     nWidth;     ///< Width of rectangle
    u16     nHeight;    ///< Height of rectangle
} MmlCameraRectangle_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Get frame complete info
*/
typedef struct
{
    MmlCameraMemoryParam_t    tPreviewFrameData;    ///< Output buffer address and size
} MmlCameraGetFrameCompleteInfo_t;

/** @ingroup    MMLayerCamera
    @brief      State change info
*/
typedef	struct
{
    MmlCameraState_e     eState;    ///< The new state after the transition
    MmlCameraEvent_e	 eCause;    ///< The cause of state change, if any
} MmlCameraStateChange_t;

/** @ingroup    MMLayerCamera
    @brief      Notification payload
*/
typedef struct
{
    MmlCameraEvent_e            eEvent;    ///< Specify the event you want to notify

    /// union of MmlCameraNotify_t parameters
    union
    {
        u16                                bFocused;                 ///< Used with CAMERA_EVENT_AUTOFOCUS_COMPLETE event
        MmlCameraStateChange_t             tStateChange;             ///< Used with CAMERA_EVENT_STATE_CHANGE event
        MmlCameraResult_e                  eErrCode;                 ///< Used with CAMERA_EVENT_RUNTIME_ERROR event
        MmlCameraGetFrameCompleteInfo_t    tGetFrameCompleteInfo;    ///< Used with CAMERA_EVENT_GET_FRAME_COMPLETE event
	} uParam;
} MmlCameraNotify_t;

/** @ingroup    MMLayerCamera
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pCameraNotify     Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlCameraNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlCameraNotify_t *pCameraNotify);

/** @ingroup    MMLayerCamera
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;            ///< Sender's mailbox ID
    u32                             nUserValue;           ///< Interface self-reference
    PfnMmlCameraNotifyCallback      pfnNotifyCallback;    ///< Callback function your want to register
} MmlCameraNotifyCallback_t;

#define MML_CAMERA_RESOLUTIONTYPE_NORMAL                    ((u16)0x0000)    ///< Refer to the specified width and height
#define MML_CAMERA_RESOLUTIONTYPE_IMAGECAPTURE_CONTACT      ((u16)0x0001)    ///< Image capture with contact-sized resolution
#define MML_CAMERA_RESOLUTIONTYPE_IMAGECAPTURE_WALLPAPER    ((u16)0x0002)    ///< Image capture with wallpaper-sized resolution

/** @ingroup    MMLayerCamera
    @brief      Zoom info
*/
typedef struct
{
    u16    nResolutionType;
    u16    nWidth;                 ///< Output width in pixels
    u16    nHeight;                ///< Output height in pixels
    u16    nMaxZoomLevel;          ///< Maximum zoom level (1000: 1x, 1300: 1.3x, ..., 4000: 4x)
    u16    nNumZoomLevelSteps;     ///< Number of zoom level steps supported (0: 1 step, 1: 2 steps, ..., 63: 64 steps)
    u16    bMultiShootSupported;   ///< Multi shoot supported ?
} MmlCameraZoomInfo_t;

#define MML_IMAGEEFFECT_BITMASK_NORMAL           ((u32) 0x00000001)
#define MML_IMAGEEFFECT_BITMASK_MONO             ((u32) 0x00000002)
#define MML_IMAGEEFFECT_BITMASK_SEPIA            ((u32) 0x00000004)
#define MML_IMAGEEFFECT_BITMASK_NEGATIVE         ((u32) 0x00000008)
#define MML_IMAGEEFFECT_BITMASK_SKETCH           ((u32) 0x00000010)
#define MML_IMAGEEFFECT_BITMASK_OILPAINTING      ((u32) 0x00000020)
#define MML_IMAGEEFFECT_BITMASK_AMBOS            ((u32) 0x00000040)
#define MML_IMAGEEFFECT_BITMASK_MOSAIC           ((u32) 0x00000080)
#define MML_IMAGEEFFECT_BITMASK_ZIPPER           ((u32) 0x00000100)
#define MML_IMAGEEFFECT_BITMASK_BLUR             ((u32) 0x00000200)
#define MML_IMAGEEFFECT_BITMASK_SEPIAGREEN       ((u32) 0x00000400)
#define MML_IMAGEEFFECT_BITMASK_SEPIABLUE        ((u32) 0x00000800)
#define MML_IMAGEEFFECT_BITMASK_SEPIARED         ((u32) 0x00001000)
#define MML_IMAGEEFFECT_BITMASK_GRAYINVERSION    ((u32) 0x00002000)
#define MML_IMAGEEFFECT_BITMASK_WHITEBOARD       ((u32) 0x00004000)
#define MML_IMAGEEFFECT_BITMASK_COPPERCARVING    ((u32) 0x00008000)
#define MML_IMAGEEFFECT_BITMASK_BLUECARVING      ((u32) 0x00010000)
#define MML_IMAGEEFFECT_BITMASK_BLACKCARVING     ((u32) 0x00020000)
#define MML_IMAGEEFFECT_BITMASK_WHITECARVING     ((u32) 0x00040000)
#define MML_IMAGEEFFECT_BITMASK_CONTRAST         ((u32) 0x00080000)
#define MML_IMAGEEFFECT_BITMASK_SOLARIZATION     ((u32) 0x00100000)
#define MML_IMAGEEFFECT_BITMASK_USERDEFINED1     ((u32) 0x00200000)
#define MML_IMAGEEFFECT_BITMASK_USERDEFINED2     ((u32) 0x00400000)
#define MML_IMAGEEFFECT_BITMASK_USERDEFINED3     ((u32) 0x00800000)
#define MML_IMAGEEFFECT_BITMASK_USERDEFINED4     ((u32) 0x01000000)
#define MML_IMAGEEFFECT_BITMASK_USERDEFINED5     ((u32) 0x02000000)

/** @ingroup    MMLayerCamera
    @brief      Sensor status
*/
typedef enum
{
    CAMERA_SENSORSTATUS_ALL = 0,    ///< Primary and secondary sensors are available
    CAMERA_SENSORSTATUS_PRIMARY,    ///< Only primary sensor is available
    CAMERA_SENSORSTATUS_SECONDARY,  ///< Only secondary sensor is available
    CAMERA_SENSORSTATUS_NONE,       ///< No sensor is available
    /* */
    CAMERA_SENSORSTATUS_NUM
} MmlCameraSensorStatus_e;

/** @ingroup    MMLayerCamera
    @brief      Camera info
*/
typedef struct
{
    u16                        nZoomInfoListSize;              ///< Size in elements of the pZoomInfoList
    MmlCameraZoomInfo_t        *pZoomInfoList;                 ///< Pointer to a list of zoom info queried
    u16                        nSensorWidth;                   ///< Sensor width
    u16                        nSensorHeight;                  ///< Sensor height
    u16                        nMaxInterpolatedWidth;          ///< Maximum interpolated width
    u16                        nMaxInterpolatedHeight;         ///< Maximum interpolated height
    u16                        bImageEffectSupported;          ///< Special image effect supported ?
    u16                        bSensorImageEffectSupported;    ///< Sensor special image effect supported ?
    u16                        bVideoStabilizerSupported;      ///< Video stabilizer supported ?
    u16                        bAutoFocusSupported;            ///< Auto focus supported ?
    u32                        nImageEffectSupported;          ///< Special image effects supported (chip + sensor)
    MmlCameraSensorStatus_e    eSensorStatus;                  ///< Result of sensor detection

} MmlCameraCameraInfo_t;

/** @ingroup    MMLayerCamera
    @brief      Camera status structure
*/
typedef struct
{
    MmlCameraZoomLevel_e    eZoomLevel;
    MmlCameraZoomStatus_e   eZoomStatus;
} MmlCameraZoomStatus_t;

/** @ingroup    MMLayerCamera
    @brief      Response callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      eErrCode          Returned result (error code)
    @param      pCameraResponse   Pointer to the returned response payload
*/
struct MmlCameraResponse_t_;
typedef void (*PfnMmlCameraResponseCallback)(u16 nSenderID, u32 nUserValue, MmlCameraResult_e eErrCode, struct MmlCameraResponse_t_ *pCameraResponse);

/** @ingroup    MMLayerCamera
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlCameraResponseCallback    pfnResponseCallback;    ///< Callback function your want to register
} MmlCameraResponseCallback_t;

/** @ingroup    MMLayerCamera
    @brief      Register notification callback
*/
typedef struct
{
    MmlCameraEvent_e                 eEvent;            ///< Specify which event you want to handle
    MmlCameraNotifyCallback_t        tNotifyCallback;   ///< Callback function your want to register
} MmlCameraRegNotifyCallback_t;

/** @ingroup    MMLayerCamera
    @brief      Start preview\n
                We define the use cases - "Detect sensor" and "Start preview" in camera multimedia group.
                Scenario is as below.
                1. When power on, MM manager sends the "Detect sensor" use case command to the common task
                   to get the sensor table indexes, and save the indexes for later use.
                2. After that, every time the "Start preview" is sent, MM manager will complete the lack
                   of sensor table parameters.
*/
typedef struct
{
    MmlCameraSensorSource_e     eSensorSource;           ///< Sensor source
    MmlCameraRectangle_t        tDisplayOutput;          ///< Display output
    MmlCameraRotationAngle_e    eRotationAngle;          ///< Rotation angle
    MmlCameraPreviewMode_e      ePreviewMode;            ///< Preview mode
    u16                         bXAxisMirrorEnable;      ///< Enable x-axis mirror
    u16                         bYAxisMirrorEnable;      ///< Enable y-axis mirror
    u16                         bAspectRatioEnable;      ///< Enable aspect ratio
    u32                         nTableAddress;           ///< 32-bit starting address of sensor table
    u32                         nTableSize;              ///< Type-A table size =  (table buffer size) x 2
                                                         ///< Type-C table size =  table size in NOR
    u32                         nPrimaryTableIndex;      ///< 32-bit index of primary sensor table
    u32                         nSecondaryTableIndex;    ///< 32-bit index of secondary sensor table
    u16                         bLockExposure;           ///< Lock exposure
    u16                         bLockWhiteBalance;       ///< Lock white balance

} MmlCameraStartPreview_t;

/** @ingroup    MMLayerCamera
    @brief      Set digital zoom
*/
typedef struct MmlCameraSetDigitalZoom_t_
{
    MmlCameraZoomLevel_e        eZoomLevel;
    u16                         bAspectRatioEnable;
} MmlCameraSetDigitalZoom_t;

/** @ingroup    MMLayerCamera
    @brief      Set exposure
*/
typedef struct
{
    MmlCameraExposureMode_e     eExposureMode;
    MmlCameraAERegion_e         eAERegion;
} MmlCameraSetExposure_t;

/** @ingroup    MMLayerCamera
    @brief      Set white balance
*/
typedef struct
{
    MmlCameraWhiteBalanceMode_e     eWhiteBalanceMode;
} MmlCameraSetWhiteBalance_t;

/** @ingroup    MMLayerCamera
    @brief      Set focus
*/
typedef struct
{
    MmlCameraFocusMode_e        eFocusMode;
    MmlCameraAFRegion_e         eAFRegion;
} MmlCameraSetFocus_t;

/** @ingroup    MMLayerCamera
    @brief      Set EV
*/
typedef struct
{
    MmlCameraEVLevel_e     eEVLevel;
} MmlCameraSetEV_t;

/** @ingroup    MMLayerCamera
    @brief      Set anit-flicker (50/60 Hz)
*/
typedef struct
{
    u16                         bAntiFlickerEnable;
    MmlCameraFrequency_e        eFrequency;
} MmlCameraSetAntiFlicker_t;

/** @ingroup    MMLayerCamera
    @brief      Set image effect
*/
typedef struct
{
    MmlCameraImageEffect_e      eImageEffect;
     /// union of MmlCameraSetImageEffect_t parameters
    union
    {
        u16                                 nLevel;           ///<Brightness (Range from 0 to 10,default level 5)
                                                              ///<Contrast   (Range from 0 to 10,default level 5)
	} uParam;
} MmlCameraSetImageEffect_t;

/** @ingroup    MMLayerCamera
    @brief      Set scene mode
*/
typedef struct
{
    MmlCameraSceneMode_e      eSceneMode;
} MmlCameraSetSceneMode_t;

/** @ingroup    MMLayerCamera
    @brief      Detect sensor\n
                If Verify Index = 0xFFFFFFFF, driver detects the sensor. Otherwise, driver verifies
                the sensor table pointed by the index to see if it matches the current sensor.
*/
typedef struct
{
    u32     nTableAddress;            ///< 32-bit starting address of sensor table
    u32     nTotalTableSize;          ///< 32-bit size in bytes of total sensor tables
    u32     nPrimaryVerifyIndex;      ///< 32-bit verify index of primary sensor table
    u32     nSecondaryVerifyIndex;    ///< 32-bit verify index of secondary sensor table
} MmlCameraDetectSensor_t;

/** @ingroup    MMLayerCamera
    @brief      Sensor info\n
                Index = 0xFFFFFFFF indicates there is no matched table
*/
typedef struct
{
    u32     nPrimaryTableIndex;      ///< 32-bit index of primary sensor table
    u32     nSecondaryTableIndex;    ///< 32-bit index of secondary sensor table
} MmlCameraSensorInfo_t;

/** @ingroup    MMLayerCamera
    @brief      Get preview frame
*/
typedef struct
{
    u16                       nWidth;               ///< Width of preview frame
    u16                       nHeight;              ///< Height of preview frame
    MmlCameraMemoryParam_t    tPreviewFrameData;    ///< Specify the buffer to store the preview frame data
} MmlCameraGetPreviewFrame_t;

/** @ingroup    MMLayerCamera
    @brief      Set frame buffer size
*/
typedef struct
{
    u16                       nWidth;               ///< Width of frame buffer
    u16                       nHeight;              ///< Height of frame buffer
    MmlImageColorFormat_e     eColorFormat;         ///< Color format
} MmlCameraSetFrameBufferSize_t;

/** @ingroup    MMLayerCamera
    @brief      Get camera info
*/
typedef struct
{
    MmlCameraSensorSource_e    eSensorSource;        ///< Sensor source
    u16                        nZoomInfoListSize;    ///< Size in elements of the pZoomInfoList
    MmlCameraZoomInfo_t        *pZoomInfoList;       ///< Pointer to a list of resolutions to be queried
} MmlCameraGetCameraInfo_t;

/** @ingroup    MMLayerCamera
    @brief      Set motion detection
*/
typedef struct
{
    MmlCameraSensorSource_e     eSensorSource;    ///< Sensor source
    u16                         bEnable;          ///< Enable motion detection
} MmlCameraSetMotionDetection_t;

/** @ingroup    MMLayerCamera
    @brief      Response payload
*/
typedef struct MmlCameraResponse_t_
{
    MmlCameraState_e        eState;    ///< Current state

    union
    {
        MmlCameraCameraInfo_t               tCameraInfo;                ///< Used with 'Get camera info'
        MmlCameraZoomStatus_t               tZoomStatus;                ///< Used with 'Get digital zoom'
        MmlCameraStateChange_t              tStateChange;               ///< Used with 'CAMERA_ERROR_STATE_CHANGE' result
        MmlCameraSensorInfo_t               tSensorInfo;                ///< Used with 'Detect sensor'
        MmlCameraGetFrameCompleteInfo_t     tGetFrameCompleteInfo;      ///< Used with CAMERA_EVENT_GET_FRAME_COMPLETE event
    } uParam;
} MmlCameraResponse_t;

/** @ingroup    MMLayerCamera
    @brief      Camera use case parameters
*/
typedef struct
{
    u32                                 nUseCaseID;
    MmlCameraResponseCallback_t         *pResponseCallback;
    MmlCameraResponse_t                 *pResponse;

    union
    {
   	    /* No parameter: 'Stop preivew, Get digital zoom, Open, Close'  */

        u16                             bEnable;                /* Set night mode */
                                                                /* Set flash mode */
                                                                /* Set video stabilizer mode */
                                                                /* Set autofocus capture mode */
        MmlCameraSensorSource_e         eSensorSource;          /* Get camera info - To be removed @ ck.wang 2010/07/20 */
        MmlCameraGetCameraInfo_t        tGetCameraInfo;         /* Get camera info */
        MmlCameraStartPreview_t         tStartPreview;          /* Start preview */
        MmlCameraSetDigitalZoom_t       tSetDigitalZoom;        /* Set digital zoom */
        MmlCameraSetExposure_t          tSetExposure;           /* Set exposure */
        MmlCameraSetWhiteBalance_t      tSetWhiteBalance;       /* Set white balance */
        MmlCameraSetFocus_t             tSetFocus;              /* Set focus */
        MmlCameraSetEV_t                tSetEV;                 /* Set EV */
        MmlCameraSetAntiFlicker_t       tSetAntiFlicker;        /* Set anti-flicker (50/60 Hz) */
        MmlCameraSetImageEffect_t       tSetImageEffect;        /* Set image effect */
        MmlCameraSetSceneMode_t         tSetSceneMode;          /* Set scene mode */
        MmlCameraSetMotionDetection_t	tSetMotionDetection;	/* Set motion detection */
        MmlCameraSetFrameBufferSize_t   tSetFrameBufferSize;    /* Set frame buffer size*/
        MmlCameraDetectSensor_t         tDetectSensor;          /* Detect sensor */
        MmlCameraGetPreviewFrame_t      tGetPreviewFrame;       /* Get preview frame */

        /* Lock auto */
    } uParam;
} MmlCameraUCParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLCAMERA_TYPES_H__
