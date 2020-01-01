/**
* @file ABL_Vtm.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of video telephony multimedia operations.
*
*/

#ifndef __ABL_VTM_H__
#define __ABL_VTM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "MediaRspItf.h"
#include "MML_Manager.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum ABL_VtmErrCode_e_
{
    ABL_VTM_OK,
    ABL_VTM_FAIL,
    ABL_VTM_BAD_PARAMS,
    ABL_VTM_MEM_ALLOC_ERROR,
    ABL_VTM_REJECT,
    ABL_VTM_ABORT,
    ABL_VTM_TIMEOUT,
    ABL_VTM_NOT_SUPPORT,
    ABL_VTM_DENY,
    ABL_VTM_SKIP
} ABL_VtmErrCode_e;

typedef struct DBLVtmRemapErrCode_t_
{
    ABL_VtmErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLVtmRemapErrCode_t;

/** @ ABL VideoTelephony
      @brief      Screen modes
*/
typedef enum
{
    ABL_VTM_SCREENMODE_LOCALLARGE = 0,     ///< Local screen large size
    ABL_VTM_SCREENMODE_LOCALSMALL,         ///< Local screen small size
    ABL_VTM_SCREENMODE_LOCALONLY,          ///< Local screen only
    ABL_VTM_SCREENMODE_REMOTEONLY,         ///< Remote screen only
    ABL_VTM_SCREENMODE_NUM
} ABL_VtmScreenMode_e;

/** @ ABL VideoTelephony
    @brief      Setting types
*/
typedef enum
{
    ABL_VTM_SETTINGTYPE_DIGITALZOOM = 0,   ///< Digital zoom level
    ABL_VTM_SETTINGTYPE_SCREENMODE,        ///< Screen mode
    ABL_VTM_SETTINGTYPE_INPUTSOURCE,       ///< Input source
    ABL_VTM_SETTINGTYPE_BRIGHTNESS,        ///< Brightness
    ABL_VTM_SETTINGTYPE_CONTRAST,          ///< Contrast
    ABL_VTM_SETTINGTYPE_REMOTEPICTURE,     ///< Remote picture
    ABL_VTM_SETTINGTYPE_BLANKPREVIEW,      ///< Blank preview
    ABL_VTM_SETTINGTYPE_NUM
} ABL_VtmSettingType_e;

/** @ ABL VideoTelephony
      @brief      Video codecs
*/
typedef enum
{
    ABL_VTM_VIDEOCODEC_MPEG2 = 0,    ///< MPEG2, also known as H.262 video format
    ABL_VTM_VIDEOCODEC_H263,         ///< ITU H.263 video format
    ABL_VTM_VIDEOCODEC_MPEG4,        ///< MPEG4 video format
    ABL_VTM_VIDEOCODEC_AVC,          ///< MPEG4 Part 10 Advanced Video Coding, also known as H.264 video format
    ABL_VTM_VIDEOCODEC_VC1,          ///< Windows Media Codec video format
    ABL_VTM_VIDEOCODEC_DONTCARE,
    ABL_VTM_VIDEOCODEC_NUM
} ABL_VtmVideoCodec_e;

/** @ ABL VideoTelephony
      @brief      MUX formats
*/
typedef enum
{
    ABL_VTM_MUXFORMAT_H223 = 0,   ///< .223
    ABL_VTM_MUXFORMAT_UNKNOWN,    ///< I don't know what format it is
    ABL_VTM_MUXFORMAT_NUM
} ABL_VtmMuxFormat_e;

/** @ ABL VideoTelephony
    @brief      Zoom levels
*/
typedef enum
{
    ABL_VTM_CAMERA_ZOOMLEVEL_1X = 0,     ///< 1x
    ABL_VTM_CAMERA_ZOOMLEVEL_1X3,        ///< 1.3x
    ABL_VTM_CAMERA_ZOOMLEVEL_1X6,        ///< 1.6x
    ABL_VTM_CAMERA_ZOOMLEVEL_2X,         ///< 2x
    ABL_VTM_CAMERA_ZOOMLEVEL_2X5,        ///< 2.5x
    ABL_VTM_CAMERA_ZOOMLEVEL_3X2,        ///< 3.2x
    ABL_VTM_CAMERA_ZOOMLEVEL_4X,         ///< 4x
    ABL_VTM_CAMERA_ZOOMLEVEL_NUM
} ABL_VtmCameraZoomLevel_e;

/** @VideoTelephony Service
    @brief      Sensor source
*/
typedef enum
{
    ABL_VTM_CAMERA_SENSOR_PRIMARY = 0,   ///< Primary sensor
    ABL_VTM_CAMERA_ATV,   ///< ATV
    ABL_VTM_CAMERA_SENSOR_SECONDARY,     ///< Secondary sensor
    /* */
    ABL_VTM_CAMERA_SENSOR_NUM
} ABL_VtmCameraSensorSource_e;

/** @VideoTelephony Service
    @brief      Input source types
*/
typedef enum
{
    ABL_VTM_INPUT_FILE = 0,    ///< Playback from file-based source
    ABL_VTM_INPUT_MEMORY,      ///< Playback from in-memory source
    ABL_VTM_INPUT_CAMERA,      ///< Input image from camera sensor
    ABL_VTM_INPUT_NUM
} ABL_VtmInputType_e;

/** @VideoTelephony Service
@brief      Output destination types
*/
typedef enum
{
    /* Video Recording */
    ABL_VTM_OUTPUT_FILE = 0,    ///< Record to file-based destination
    ABL_VTM_OUTPUT_MEMORY,      ///< Record to in-memory destination
    /* Video Playback */
    /* */
    ABL_VTM_OUTPUT_NUM
} ABL_VtmOutputType_e;

typedef struct
{
    u16 nOutLen;        /**< file name length */
    u32 nFileNameOutAddr; /**< file name buffer address (MMI should release file name buffer after receiving response msg) */
} ABL_VtmRecFileName_t;

typedef struct
{
  union {
    u32 uPlayHandle;      //play video telephony handle.
    u32 uRecHandle;      //record video telephony handle.
    u16 nLevel;               ///< Used with 'Get video telephony setting' (Brightness, Contrast)
    ABL_VtmRecFileName_t	tRecFilename; //saving record file with filename in response.
  } param;
} ABL_VtmRspData_t;

typedef struct
{
    ABL_VtmErrCode_e eErrCode;
    ABL_VtmRspData_t tRspData;
} ABL_VtmRspInfo_t;

typedef MmlVideoTelephonyRemoteSetting_t        ABL_VtmRemoteSetting_t;
typedef MmlVideoTelephonyLocalSetting_t         ABL_VtmLocalSetting_t;
typedef MmlVideoOpenVideoTelephony_t            ABL_VideoOpenVideoTelephony_t;
typedef MmlVideoStartVideoTelephonyRecording_t  ABL_VtmStartRecord_t;

//Set Config
typedef MmlVideoSetVideoTelephonySetting_t      ABL_VtmSetVideoTelephonySetting_t;
typedef MmlCameraSetDigitalZoom_t 		    ABL_VtmCameraSetDigitalZoom_t;
typedef MmlVideoTelephonyInputSource_t 	    ABL_VtmInputSource_t;

/**
 *  @brief The structure defines the notification value for application layer.
 *			should sync. with esl_VtmNotifyInfo_t
 */
typedef struct {
  MediaRspId_e  eNotifyType;    			 /**< Type of video notification */
  union
  {
      u32 nPosition;
      ABL_VtmErrCode_e     eErrorType;     /**< Video playback error type */
  } param;
} ABL_VtmNotifyInfo_t;

typedef void (*ABL_VtmCb)(u16 uSenderId, u32 uUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
typedef struct {
    u16 uSenderId;     /**< Task id of sender */
    u32 uUserValue;    /**< userValue of sender for checking msg response to related applicatoin */
    ABL_VtmCb pfnCb;        /**< Done call back function that called by EMA */
} ABL_VtmCb_t;

typedef struct VtmCmd_t_
{
    ABL_VtmCb_t *pCbParams;
    u32 uPlayHandle;
    u32 uRecHandle;
    union
    {
        ABL_VideoOpenVideoTelephony_t tOpenVideoTelephony;
        ABL_VtmSetVideoTelephonySetting_t tSetVideoTelephonySetting;
        ABL_VtmStartRecord_t    tStartRecord;
    } tParams;
} VtmCmd_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void ABL_VtmOpenSessionReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmCloseSessionReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmOpenReq(ResMgr_AppId_e eAppId, ABL_VideoOpenVideoTelephony_t *pOpenVideoTelephony, ABL_VtmCb_t *pVtmCb);
void ABL_VtmCloseReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmStartReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmStopReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmSetConfigReq(ResMgr_AppId_e eAppId, ABL_VtmSetVideoTelephonySetting_t *pSetVideoTelephonySetting, ABL_VtmCb_t *pVtmCb);
void ABL_VtmStartRecordReq(ResMgr_AppId_e eAppId, ABL_VtmStartRecord_t *pStartRecord, ABL_VtmCb_t *pVtmCb);
void ABL_VtmStopRecordReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmSaveRecordFileReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmDiscardRecordFileReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);
void ABL_VtmAbortSavingFileReq(ResMgr_AppId_e eAppId, ABL_VtmCb_t *pVtmCb);

ResMgr_ExecRes_e ABL_VtmParseExecRes(s16 sResult);
void ABL_VtmInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_VtmFreeCusData(void *pCusData);
void ABL_VtmFreeSetConfigCusData(void *pCusData);
void ABL_VtmFreeStartRecordCusData(void *pCusData);
void ABL_VtmGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);

MmlVideoTelephonySettingType_e ABL_VtmRemapSettingType(ABL_VtmSettingType_e eSettingType);
MmlCameraZoomLevel_e ABL_VtmRemapZoomLevel(ABL_VtmCameraZoomLevel_e eZoomLevel);
MmlVideoTelephonyScreenMode_e ABL_VtmRemapScreenMode(ABL_VtmScreenMode_e eScreenMode);
MmlCameraSensorSource_e ABL_VtmRemapCameraSensorSource(ABL_VtmCameraSensorSource_e eCamerSensorSource);

#endif //__ABL_VTM_H__

