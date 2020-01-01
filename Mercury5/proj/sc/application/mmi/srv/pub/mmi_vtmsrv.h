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
* @file mmi_vtmsrv.h
*
* Class Id: CLSID_VTMSRV
*
*
*/
/*=============================================================*/
// Include Files
/*=============================================================*/

#ifdef __VT_3G324M__	

#ifndef __MMI_VTMSRV_H__
#define __MMI_VTMSRV_H__

#include "mmi_mae_applet.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_notifier.h"
#include "mmi_log.h"
#include "mmi_mediasrv_common.h"
#include "ABL_Vtm.h"

/**
 * IVTMSRV Interfaces
 */
#define INHERIT_IVTMSRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IVTMSRV);

#define IVTMSRV_QueryInterface(pICntlr, id, pp, po)GET_FUNCTBL((pICntlr), IVTMSRV)->QueryInterface(pICntlr, id, pp, po)
#define IVTMSRV_HandleEvent(pICntlr, e, p1, p2)GET_FUNCTBL((pICntlr), IVTMSRV)->HandleEvent(pICntlr, e, p1, p2)

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/** @VideoTelephony Service
      @brief      Screen modes
*/
typedef enum
{
    VTMSRV_SCREENMODE_LOCALLARGE = 0,     ///< Local screen large size
    VTMSRV_SCREENMODE_LOCALSMALL,         ///< Local screen small size
    VTMSRV_SCREENMODE_LOCALONLY,          ///< Local screen only
    VTMSRV_SCREENMODE_REMOTEONLY,         ///< Remote screen only
    VTMSRV_SCREENMODE_NUM
} VtmSrvScreenMode_e;

/** @VideoTelephony Service
    @brief      Setting types
*/
typedef enum
{
    VTMSRV_SETTINGTYPE_DIGITALZOOM = 0,   ///< Digital zoom level
    VTMSRV_SETTINGTYPE_SCREENMODE,        ///< Screen mode
    VTMSRV_SETTINGTYPE_INPUTSOURCE,       ///< Input source
    VTMSRV_SETTINGTYPE_BRIGHTNESS,        ///< Brightness
    VTMSRV_SETTINGTYPE_CONTRAST,          ///< Contrast    
    VTMSRV_SETTINGTYPE_REMOTEPICTURE,     ///< Remote picture
    VTMSRV_SETTINGTYPE_BLANKPREVIEW,      ///< Blank preview
    VTMSRV_SETTINGTYPE_NUM
} VtmSrvSettingType_e;

/** @VideoTelephony Service
      @brief      Video codecs
*/
typedef enum
{
    VTMSRV_VIDEOCODEC_MPEG2 = 0,    ///< MPEG2, also known as H.262 video format
    VTMSRV_VIDEOCODEC_H263,         ///< ITU H.263 video format
    VTMSRV_VIDEOCODEC_MPEG4,        ///< MPEG4 video format
    VTMSRV_VIDEOCODEC_AVC,          ///< MPEG4 Part 10 Advanced Video Coding, also known as H.264 video format
    VTMSRV_VIDEOCODEC_VC1,          ///< Windows Media Codec video format
    VTMSRV_VIDEOCODEC_DONTCARE,    
    VTMSRV_VIDEOCODEC_NUM
} VtmSrvVideoCodec_e;

/** @VideoTelephony Service
      @brief      MUX formats
*/
typedef enum
{
    VTMSRV_MUXFORMAT_H223 = 0,   ///< .223
    VTMSRV_MUXFORMAT_UNKNOWN,    ///< I don't know what format it is
    VTMSRV_MUXFORMAT_NUM
} VtmSrvMuxFormat_e;

/** @VideoTelephony Service
      @brief      Rotation angles
*/
typedef enum
{
    VTMSRV_ROTATION_0 = 0,
    VTMSRV_ROTATION_90,
    VTMSRV_ROTATION_180,
    VTMSRV_ROTATION_270,
    VTMSRV_ROTATION_NUM
} VtmSrvRotationAngle_e;

/** @VideoTelephony Service
      @brief      Input source types
*/
typedef enum
{
    /* Video Playback */
    VTMSRV_INPUT_FILE = 0,    ///< Playback from file-based source
    VTMSRV_INPUT_MEMORY,      ///< Playback from in-memory source
    /* Video Recording */
    /* Video Telephony */
    VTMSRV_INPUT_CAMERA,      ///< Input image from camera sensor
    /* */
    VTMSRV_INPUT_NUM
} VtmSrvInputType_e;

/** @VideoTelephony Service
@brief      Output source types
*/
typedef enum
{
    /* Video Recording */
    VTMSRV_OUTPUT_FILE = 0,    ///< Record to file-based destination
    VTMSRV_OUTPUT_MEMORY,      ///< Record to in-memory destination
    /* Video Playback */
    /* */
    VTMSRV_OUTPUT_NUM
} VtmSrvOutputType_e;

/** @VideoTelephony Service
      @brief      Video formats
*/
typedef enum
{
    VTMSRV_FORMAT_3GP = 0,    ///< .3gp
    VTMSRV_FORMAT_MP4,        ///< .mp4
    VTMSRV_FORMAT_RM,         ///< .rm
    VTMSRV_FORMAT_RMVB,       ///< .rmvb
    VTMSRV_FORMAT_AVI,        ///< .avi
    VTMSRV_FORMAT_FLV,        ///< .flv
    VTMSRV_FORMAT_PS,         ///< .ps
    VTMSRV_FORMAT_TS,         ///< .ts
    VTMSRV_FORMAT_H324,       ///< .h324 (video telephony)    
    VTMSRV_FORMAT_UNKNOWN,    ///< I don't know what format it is
    VTMSRV_FORMAT_NUM
} VtmSrvFormat_e;

/** @VideoTelephony Service
    @brief      Zoom levels
*/
typedef enum
{
    VTMSRV_CAMERA_ZOOMLEVEL_1X = 0,     ///< 1x
    VTMSRV_CAMERA_ZOOMLEVEL_1X3,        ///< 1.3x
    VTMSRV_CAMERA_ZOOMLEVEL_1X6,        ///< 1.6x
    VTMSRV_CAMERA_ZOOMLEVEL_2X,         ///< 2x
    VTMSRV_CAMERA_ZOOMLEVEL_2X5,        ///< 2.5x
    VTMSRV_CAMERA_ZOOMLEVEL_3X2,        ///< 3.2x
    VTMSRV_CAMERA_ZOOMLEVEL_4X,         ///< 4x
    VTMSRV_CAMERA_ZOOMLEVEL_NUM
} VtmSrvCameraZoomLevel_e;

/** @VideoTelephony Service
      @brief      Filename formats
*/
typedef enum
{
    VTMSRV_FILENAMEFORMAT_DIRECTORY = 0x0,    ///< Specify the folder only
    VTMSRV_FILENAMEFORMAT_PREFIX,             ///< Specify the folder + filename's prefix
    VTMSRV_FILENAMEFORMAT_ABSOLUTE,           ///< Specify the folder + filename
    VTMSRV_FILENAMEFORMAT_NUM
} VtmSrvFilenameFormat_e;

/** @VideoTelephony Service
    @brief      Sensor source
*/
typedef enum
{
    VTMSRV_CAMERA_SENSOR_PRIMARY = 0,   ///< Primary sensor
    VTMSRV_CAMERA_ATV,   ///< ATV
    VTMSRV_CAMERA_SENSOR_SECONDARY,     ///< Secondary sensor
    /* */
    VTMSRV_CAMERA_SENSOR_NUM
} VtmSrvCameraSensorSource_e;


/** @VideoTelephony Service
      @brief      Rectangle
*/
typedef struct
{
    u16     nLeft;      ///< x-position of the top left corner of rectangle
    u16     nTop;       ///< y-position of the top left corner of rectangle
    u16     nWidth;     ///< Width of rectangle
    u16     nHeight;    ///< Height of rectangle
} VtmSrvRectangle_t;


/** @VideoTelephony Service
      @brief      File-based source
*/
typedef struct
{
    VtmSrvFormat_e       		eFormat;
    VtmSrvFilenameFormat_e    	eFilenameFormat;
    u16                    *pFileName;
    u16  	               nFileNameSize;
} VtmSrvFileParam_t;

/** @VideoTelephony Service
      @brief      In-memory source
*/
typedef	struct
{
    VtmSrvFormat_e    eFormat;
    u8                  *pBuffer;
    u32                 nBufferSize;
    u16                 bRepeat;
} VtmSrvMemoryParam_t;

/** @VideoTelephony Service
      @brief      Remote telephony setting
*/
typedef struct
{
    VtmSrvVideoCodec_e   eEncoderId;     ///< Specify the supported video encoder
    VtmSrvMuxFormat_e    eMuxFormat;     ///< MUX format
    u16                             nWidth;         ///< Output frame width in pixels
    u16                             nHeight;        ///< Output frame height in pixels
    u16                             nQualityLevel;  ///< Compression level in 0-1000, 0: default, 1: best, 1000: worst (highest compression)
    u16                             bVideoOnly;     ///< Enable video only muxing
    u16                             bAudioOnly;     ///< Enable audio only muxing
    u16                             nFrameRate;     ///< Encoding frame rate in units of frames per second
    u32                             nBitRate;       ///< 0 is to use the default bitrate
} VtmSrvVideoTelephonyRemoteSetting_t;

/** @VideoTelephony Service
      @brief      Local telephony setting
*/
typedef struct
{
    VtmSrvInputType_e          eInputType;                 ///< Input source type
    u32                         		 nPosition;                  ///< 32-bit value expressed in milliseconds and relative to the beginning of the content
    VtmSrvRotationAngle_e     eRemoteRotationAngle;       ///< Remote rotation (0, 90, 180, 270 degree)
    VtmSrvRotationAngle_e     eLocalRotationAngle;        ///< Local rotation (0, 90, 180, 270 degree)    
    VtmSrvRectangle_t         	 tRemoteOutputWindow;        ///< Remote output window
    u16                         		 nRemoteOutputWindowPitch;   ///< Remote output window pitch
    VtmSrvRectangle_t           tLocalOutputWindow;         ///< Local output window
    u16                         		 nLocalOutputWindowPitch;    ///< Local output window pitch
    u16                         		 bVideoOnly;                 ///< Enable video only playback
    u16                          	 bAudioOnly;                 ///< Enable audio only playback
	
    /// union of MmlVideoTelephonyLocalSetting_t parameters
    union
    {
	    VtmSrvFileParam_t         tFileParam;      ///< Image input from file-based source (Picture mode)
	    VtmSrvMemoryParam_t       tMemoryParam;    ///< Image input from in-memory source (Picture mode)
	    VtmSrvCameraSensorSource_e     eSensorSource;   ///< Image input from camera sensor (Camera mode)
     } uInputParam;	
} VtmSrvVideoTelephonyLocalSetting_t;

/** @VideoTelephony Service
      @brief      Open video telephony
*/
typedef struct
{
    VtmSrvRotationAngle_e         	eRemoteRotationAngle;       ///< Remote rotation (0, 90, 180, 270 degree)
    VtmSrvRotationAngle_e         	eLocalRotationAngle;        ///< Local rotation (0, 90, 180, 270 degree)
    VtmSrvRectangle_t             	tRemoteOutputWindow;        ///< Remote output window
    u16                             		nRemoteOutputWindowPitch;   ///< Remote output window pitch
    VtmSrvRectangle_t             	tLocalOutputWindow;         ///< Local output window
    u16                             		nLocalOutputWindowPitch;    ///< Local output window pitch
} VtmSrvOpenVideoTelephony_t;

/** @VideoTelephony Service
      @brief      Start video telephony
*/
typedef struct
{
    VtmSrvVideoTelephonyLocalSetting_t     		tLocalSetting;     ///< Local telephony setting
    VtmSrvVideoTelephonyRemoteSetting_t    	tRemoteSetting; 	  ///< Remote telephony setting
    VtmSrvScreenMode_e       				eScreenMode;       ///< Screen mode
} VtmSrvStartVideoTelephony_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Input source
*/
typedef struct
{
    VtmSrvInputType_e             eInputType;                 ///< Input source type

    /// union of MmlVideoTelephonyInputSource_t parameters
    union
    {
	    VtmSrvFileParam_t         tFileParam;      ///< Image input from file-based source (Picture mode)
	    VtmSrvMemoryParam_t       tMemoryParam;    ///< Image input from in-memory source (Picture mode)
	    VtmSrvCameraSensorSource_e     eSensorSource;   ///< Image input from camera sensor (Camera mode)
    } uInputParam;
} VtmSrvInputSource_t;

/** @VideoTelephony Service
    @brief      Set digital zoom
*/
typedef struct
{
    VtmSrvCameraZoomLevel_e        eZoomLevel;
    u16                         bAspectRatioEnable;
} VtmSrvCameraSetDigitalZoom_t;


/** @VideoTelephony Service
    @brief      Remote picture
*/
typedef struct
{
    VtmSrvInputType_e                eInputType;      ///< Input source type
    boolean                             	bEnable;           ///< Enable remote picture mode

    /// union of MmlVideoTelephonyInputSource_t parameters
    union
    {
	    VtmSrvFileParam_t          tFileParam;      ///< Image input from file-based source (Picture mode)
	    VtmSrvMemoryParam_t   tMemoryParam;    ///< Image input from in-memory source (Picture mode)
    } uInputParam;
} VtmSrvRemotePicture_t;

/** @VideoTelephony Service
    @brief      Blank Preview
*/
typedef struct
{
    u16                             bEnable;         ///< Enable blank preview
} VtmSrvBlankPreview_t;

/** @VideoTelephony Service
    @brief      Start video telephony recording
*/
typedef struct
{
    VtmSrvOutputType_e        eOutputType;    ///< Output destination type

    /// union of MmlVideoStartVideoTelephonyRecording_t parameters
    union
    {
        VtmSrvFileParam_t     tFileParam;     ///< Record to file-based destination
        VtmSrvMemoryParam_t   tMemoryParam;   ///< Record to in-memory destination
    } uParam;
} VtmSrvStartRecord_t;

/** @VideoTelephony Service
    @brief      Set video telephony setting
*/
typedef struct
{
    VtmSrvSettingType_e      eSettingType;      ///< Specify which type of setting to set

    /// union of MmlVideoSetVideoTelephonySetting_t parameters
    union
    {
        VtmSrvCameraSetDigitalZoom_t       	tSetDigitalZoom;  ///< Specify digital zoom level
        VtmSrvScreenMode_e   				eScreenMode;      ///< Screen mode
        VtmSrvInputSource_t  				tInputSource;     ///< Input source
        u16                             	nLevel;   		  ///< Brightness (0: black - 100: white)
                                                           	  ///< Contrast (0: maximum - 100: minimum)
        VtmSrvRemotePicture_t    			tRemotePicture;   ///< Remote picture
        VtmSrvBlankPreview_t				tBlankPreview;    ///< Blank preview
    } uParam;
} VtmSrvSetVideoTelephonySetting_t;

/** @VideoTelephony Service
    @brief      Get video telephony setting
*/
typedef struct
{
    VtmSrvSettingType_e      eSettingType;      ///< Specify which type of setting to get
} VtmSrvGetVideoTelephonySetting_t;

typedef enum
{
    VTMSRV_ERR_OK,
    VTMSRV_ERR_FAIL,
    VTMSRV_ERR_PARAM_ERROR,
    VTMSRV_ERR_MEM_ALLOC_ERROR,
    VTMSRV_ERR_REJECT,
    VTMSRV_ERR_EOF,
    VTMSRV_ERR_TIMEOUT,
    VTMSRV_ERR_NOT_SUPPORT,
    VTMSRV_ERR_DENY,
    VTMSRV_ERR_NUM
} VtmSrvErrCode_e;

typedef enum
{
    VTMSRV_NOTIFY_VTM_POSITION_UPDATE = 0,
    VTMSRV_NOTIFY_VTM_REC_STOP,
    VTMSRV_NOTIFY_VTM_REC_SPACE_FULL,
    VTMSRV_NOTIFY_VTM_REC_ERROR,
    VTMSRV_NOTIFY_VTM_ERROR,
    VTMSRV_NOTIFY_ERR_NUM
} VtmSrvNotify_e;

typedef struct
{
    VtmSrvNotify_e eNotify;
    union
    {        
        u32 nPosition;
    } uParam;
} VtmSrvNotifyCbInfo_t;

typedef struct
{
    u16 nLen;        /**< file name length */
    u32 nFileNameOutAddr; /**< file name buffer address (MMI should release file name buffer after receiving response msg) */
} VtmSrvFileName_t;

typedef void (*VtmSrvCnfCb)(void *pThis, VtmSrvErrCode_e eErrorCode);
typedef void (*VtmSrvGetFilenameCb)(void *pThis, VtmSrvErrCode_e eErrorCode, VtmSrvFileName_t *pGetFilename);
typedef void (*VtmSrvNotifyCb)(void *pThis, u32 nCusData, VtmSrvNotifyCbInfo_t *pNotifyCbInfo);

typedef struct
{
    u32 nSrvInstId;
    u32 nSrvClientInsId;
    u32 nCusData;
    u32 pfnCb;
} VtmSrvCusInfo_t;

typedef struct VtmSrv_t_
{
    DECLARE_FUNCTBL(IVTMSRV);
    u32 nRefCnt;
    VtmSrvCusInfo_t *pVtmStatus;
    VtmSrvCusInfo_t *pVtmData;    
} VtmSrv_t;

/*=============================================================*/
// Variable Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
MAE_Ret VtmSrvNew(MAE_ClsId nId, void **ppObj);
void VtmSrvOpenSession(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId);
void VtmSrvCloseSession(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId);
MAE_Ret VtmSrvOpen(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvOpenVideoTelephony_t *pOpenVideoTelephony, VtmSrvCnfCb pFnCb);
MAE_Ret VtmSrvStart(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvCnfCb pFnCb);
MAE_Ret VtmSrvStop(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvCnfCb pFnCb);
MAE_Ret VtmSrvClose(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvCnfCb pFnCb);
void VtmSrvSetZoomLevel(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvCameraZoomLevel_e eZoomLevel, boolean bAspectRatioEnable, VtmSrvCnfCb pFnCb);
void VtmSrvSetScreenMode(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvScreenMode_e eScreenMode, VtmSrvCnfCb pFnCb);
void VtmSrvSetInputSource(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvInputSource_t *pInputSource, VtmSrvCnfCb pFnCb);
void VtmSrvSetBrightness(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, u16 nLevel, VtmSrvCnfCb pFnCb);
void VtmSrvSetContrast(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, u16 nLevel, VtmSrvCnfCb pFnCb);
void VtmSrvSetRemotePicture(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvRemotePicture_t *pRemotePicture, VtmSrvCnfCb pFnCb);
void VtmSrvSetBlankPreview(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, boolean bEnable, VtmSrvCnfCb pFnCb);
MAE_Ret VtmSrvStartRecord(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvStartRecord_t *pStartRecord, VtmSrvCnfCb pFnCb);
MAE_Ret VtmSrvStopRecord(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvCnfCb pFnCb);
MAE_Ret VtmSrvSaveRecordFile(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvGetFilenameCb pFnCb);
MAE_Ret VtmSrvDiscardRecordFile(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvCnfCb pFnCb);
MAE_Ret VtmSrvAbortSavingFile(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvCnfCb pFnCb);
void VtmSrvSetInterruptNotifyCb(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, MediaSrvInterruptNotifyCb pfnVtmSrvCb, u32 nCusData);
void VtmSrvSetNotifyCb(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, VtmSrvNotifyCb pfnVtmSrvCb, u32 nCusData);
/*=============================================================*/
// Private Function Implementations
/*=============================================================*/
#endif

#endif //#ifdef __VT_3G324M__

