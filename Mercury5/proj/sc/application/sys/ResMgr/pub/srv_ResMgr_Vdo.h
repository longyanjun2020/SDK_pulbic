/**
* @file srv_ResMgr_Vdo.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of video.
*
*/

#ifndef __SRV_RESMGR_VDO_H__
#define __SRV_RESMGR_VDO_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_vdo_itf.h"
#include "MediaRspItf.h"
#include "srv_resmgr_mmlvideo_types.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* ResMgr_VdoStmHdl_t;

typedef enum ABL_VdoErrCode_e_
{
    ABL_VDO_OK,               //ESL_VDO_OK
    ABL_VDO_FAIL,             //ESL_VDO_FAIL
    ABL_VDO_BAD_PARAMS,       //ESL_VDO_PARAM_ERROR
    ABL_VDO_MEM_ALLOC_ERROR,  //ESL_VDO_MEM_ALLOC_ERROR
    ABL_VDO_LICENSE_MISMATCH, //ESL_VDO_LICENSE_MISMATCH
    ABL_VDO_LICENSE_NOTEXIST, //ESL_VDO_LICENSE_NOTEXIST
    ABL_VDO_PASSWORD_MISMATCH,//ESL_VDO_PASSWORD_MISMATCH
    ABL_VDO_REJECT,           //ESL_VDO_REJECT
    ABL_VDO_ABORT,            //ESL_VDO_ABORT
    ABL_VDO_TIMEOUT,          //ESL_VDO_TIMEOUT
    ABL_VDO_NOT_SUPPORT,      //ESL_VDO_FORMAT_NOT_SUPPORT
    ABL_VDO_DENY,
    ABL_VDO_MERGE,
    ABL_VDO_SKIP
} ABL_VdoErrCode_e;

typedef esl_VdoFileInfo_t ABL_VdoFileInfo_t;
typedef esl_VdoRegion_t ABL_VdoRegion_t;
typedef esl_VdoMediaInfo_t ABL_VdoMediaInfo_t;
typedef esl_VdoMemInfo_t ABL_VdoMemInfo_t;
typedef esl_VdoPlaybackCapability_t ABL_VdoPlaybackCap_t;

typedef struct ABL_VdoGetPlaybackCapInfo_t_
{
    ABL_VdoErrCode_e eErrCode;
    ABL_VdoPlaybackCap_t tVdoPlaybackCap;
} ABL_VdoGetPlaybackCapInfo_t;

typedef struct ABL_VdoDecodeFrameParam_t_
{
    MmlVideoRotationAngle_e     eRotationAngle;        ///< 0, 90, 180, 270 degree
    MmlVideoRectangle_t         tOutputWindow;         ///< Output window
    MmlVideoBufferParam_t       tBufferParam;          ///< Output thumbnail buffer
    MmlImageStereoType_e        eImageStereoType;
} ABL_VdoDecodeFrameParam_t;

typedef struct ABL_VdoSeekParams_t_
{
    u32 uPosition;
    u32 uTimeout;
    MmlVideoSeekType_e eSeekType;
} ABL_VdoSeekParams_t;

typedef enum ABL_VdoPlaySpeed_e_
{
    ABL_VDO_PLAY_SPEED_0_5X,    //ESL_VDO_PLAY_SPEED_0_5X
    ABL_VDO_PLAY_SPEED_1X,      //ESL_VDO_PLAY_SPEED_1X
    ABL_VDO_PLAY_SPEED_2X,      //ESL_VDO_PLAY_SPEED_2X
    ABL_VDO_PLAY_SPEED_4X,      //ESL_VDO_PLAY_SPEED_4X
    ABL_VDO_PLAY_SPEED_8X,      //ESL_VDO_PLAY_SPEED_8X
    ABL_VDO_PLAY_SPEED_NUM
} ABL_VdoPlaySpeed_e;

typedef enum ABL_VdoRotateAngle_e_
{
    ABL_VDO_ROTATE_NONE,    //ESL_VDO_ROTATE_NONE
    ABL_VDO_ROTATE_90,      //ESL_VDO_ROTATE_90
    ABL_VDO_ROTATE_180,     //ESL_VDO_ROTATE_180
    ABL_VDO_ROTATE_270,      //ESL_VDO_ROTATE_270
    ABL_VDO_ROTATE_NUM
} ABL_VdoRotateAngle_e;

#ifdef __MMI_STEREO_VIDEO__
typedef enum
{
    ABL_VDO_CONFIGURATIONTYPE_DISPLAYCALIBRATION  = 0,       ///< ESL_VDO_CONFIGURATIONTYPE_DISPLAYCALIBRATION
    ABL_VDO_CONFIGURATIONTYPE_STEREO_TYPE,                   ///< ESL_VDO_CONFIGURATIONTYPE_3D
    ABL_VDO_CONFIGURATIONTYPE_DEPTH,                         ///< Depth
    ABL_VDO_CONFIGURATIONTYPE_DISPLAYCALIBRATION_MAX         ///< ESL_VDO_CONFIGURATIONTYPE_DISPLAYCALIBRATION_MAX
} ABL_VdoConfigurationType_e;

typedef enum
{
    ABL_VDO_IMAGE_STEREOTYPE_NONE = 0,  ///< ESL_VDO_IMAGE_STEREOTYPE_NONE
    ABL_VDO_IMAGE_STEREOTYPE_RED_CYAN,  ///< ESL_VDO_IMAGE_STEREOTYPE_RED_CYAN
    ABL_VDO_IMAGE_STEREOTYPE_NUM        ///< ESL_VDO_IMAGE_STEREOTYPE_NUM
} ABL_VdoImageStereoType_e;
#endif

typedef enum ABL_VdoFormat_e_
{
    ABL_VDO_H263I,            //ESL_VDO_H263I
    ABL_VDO_H263,             //ESL_VDO_H263
    ABL_VDO_H264,             //ESL_VDO_H264
    ABL_VDO_IPTV,             //ESL_VDO_IPTV
    ABL_VDO_MP4,              //ESL_VDO_MP4
    ABL_VDO_WMV,              //ESL_VDO_WMV
    ABL_VDO_WAV_STREAMING,    //ESL_VDO_WAV_STREAMING
    ABL_VDO_MEM,              //ESL_VDO_MEM
    ABL_VDO_MOVIEKING,        //ESL_VDO_MOVIEKING
    ABL_VDO_UNKNOW_FORMAT     //ESL_VDO_UNKNOW_FORMAT
} ABL_VdoFormat_e;

typedef enum
{
    ABL_VDO_MEM_3GP,            //ESL_VDO_MEM_3GP
    ABL_VDO_MEM_MP4,            //ESL_VDO_MEM_MP4
    ABL_VDO_MEM_RM,             //ESL_VDO_MEM_RM
    ABL_VDO_MEM_AVI,            //ESL_VDO_MEM_AVI
    ABL_VDO_MEM_MFS,            //ESL_VDO_MEM_MFS
    ABL_VDO_MEM_TS,             //ESL_VDO_MEM_TS
    ABL_VDO_MEM_FLV,            //ESL_VDO_MEM_FLV
    ABL_VDO_MEM_UNKNOW_FORMAT   //ESL_VDO_MEM_UNKNOW_FORMAT
} ABL_VdoMemFormat_e;

typedef enum ABL_VdoErrorType_e_
{
    ABL_VDO_ERROR_SEEK = 0,             //ESL_VDO_ERROR_SEEK
    ABL_VDO_ERROR_FILE,                 //ESL_VDO_ERROR_FILE
    ABL_VDO_ERROR_PLAY,                 //ESL_VDO_ERROR_PLAY
    ABL_VDO_ERROR_UNKNOWN,              //ESL_VDO_ERROR_UNKNOWN
    ABL_VDO_ERROR_FORMAT_NOT_SUPPORT,   //ESL_VDO_ERROR_FORMAT_NOT_SUPPORT
    ABL_VDO_ERROR_MEMORY_ALLOCATE_FAIL,
    ABL_VDO_ERROR_NONE,                 //ESL_VDO_ERROR_NONE
    ABL_VDO_ERROR_NETWORK,
    ABL_VDO_ERROR_DISK_FULL,
} ABL_VdoErrorType_e;

typedef enum ABL_VdoCodecType_e_
{
    ABL_VDO_VDO_CODEC__MPEG2,           //VIDEO_VIDEOCODEC_MPEG2
    ABL_VDO_VDO_CODEC__H263,            //VIDEO_VIDEOCODEC_H263
    ABL_VDO_VDO_CODEC__MPEG4,           //VIDEO_VIDEOCODEC_MPEG4
    ABL_VDO_VDO_CODEC__AVC,             //VIDEO_VIDEOCODEC_AVC
    ABL_VDO_VDO_CODEC__VC1,             //VIDEO_VIDEOCODEC_VC1
    ABL_VDO_VDO_CODEC__RVC,             //VIDEO_VIDEOCODEC_RVC
    ABL_VDO_VDO_CODEC__MJPEG,           //VIDEO_VIDEOCODEC_MJPEG
    ABL_VDO_VDO_CODEC__KMV,             //VIDEO_VIDEOCODEC_KMV
    ABL_VDO_VDO_CODEC__DONTCARE,        //VIDEO_VIDEOCODEC_DONTCARE
    ABL_VDO_VDO_CODEC__NUM,             //VIDEO_VIDEOCODEC_NUM
    ABL_VDO_VDO_CODEC__UNSUPPORTED      //VIDEO_VIDEOCODEC_UNSUPPORTED
} ABL_VdoCodecType_e;

typedef enum ABL_AudCodecType_e_
{
    ABL_AUD_AUD_CODEC__WAVE = 0,        //AUDIO_AUDIOCODEC_WAVE = 0,
    ABL_AUD_AUD_CODEC__MIDI,            //AUDIO_AUDIOCODEC_MIDI,
    ABL_AUD_AUD_CODEC__IMY,             //AUDIO_AUDIOCODEC_IMY,
    ABL_AUD_AUD_CODEC__MP3,             //AUDIO_AUDIOCODEC_MP3,
    ABL_AUD_AUD_CODEC__AAC,             //AUDIO_AUDIOCODEC_AAC,
    ABL_AUD_AUD_CODEC__AMR,             //AUDIO_AUDIOCODEC_AMR,
    ABL_AUD_AUD_CODEC__AWB,             //AUDIO_AUDIOCODEC_AWB,
    ABL_AUD_AUD_CODEC__RAM,             //AUDIO_AUDIOCODEC_RAM,
    ABL_AUD_AUD_CODEC__WMA,             //AUDIO_AUDIOCODEC_WMA,
    ABL_AUD_AUD_CODEC__WMV,             //AUDIO_AUDIOCODEC_WMV,
    ABL_AUD_AUD_CODEC__MP4,             //AUDIO_AUDIOCODEC_MP4,
    ABL_AUD_AUD_CODEC__3GP,             //AUDIO_AUDIOCODEC_3GP,
    ABL_AUD_AUD_CODEC__WAVE_EXT,        //AUDIO_AUDIOCODEC_WAVE_EXT,
    ABL_AUD_AUD_CODEC__MIDI_EVENT,      //AUDIO_AUDIOCODEC_MIDI_EVENT,
    ABL_AUD_AUD_CODEC__PCM,             //AUDIO_AUDIOCODEC_PCM,
    ABL_AUD_AUD_CODEC__COOK,            //AUDIO_AUDIOCODEC_COOK,
    ABL_AUD_AUD_CODEC__APE,             //AUDIO_AUDIOCODEC_APE,
    ABL_AUD_AUD_CODEC__M4A,             //AUDIO_AUDIOCODEC_M4A,
    ABL_AUD_AUD_CODEC__DONTCARE,        //AUDIO_AUDIOCODEC_DONTCARE,
    /* */                               /* */
    ABL_AUD_AUD_CODEC__NUM,             //AUDIO_AUDIOCODEC_NUM,
    ABL_AUD_AUD_CODEC__UNSUPPORTED      //AUDIO_AUDIOCODEC_UNSUPPORTED
} ABL_AudCodecType_e;

typedef esl_VdoInfo_t ABL_VdoInfo_t;

typedef struct ABL_VdoRspInfo_t_
{
    ABL_VdoErrCode_e eErrCode;
    ABL_VdoInfo_t tVdoInfo;
    u32 uExtInfo;
} ABL_VdoRspInfo_t;

#ifdef __MMI_STEREO_VIDEO__
typedef enum
{
    ABL_VDO_STEREO_TYPE__NONE = 0,
    ABL_VDO_STEREO_TYPE__RED_CYAN,
    ABL_VDO_STEREO_TYPE__NUM
} ABLVdoStereoType_e;

typedef MmlVideoSetConfiguration_t ABL_VdoSetConfiguration_t;
#endif

typedef esl_VdoBufferInfo_t ABL_VdoBufferInfo_t;
typedef MmlVideoSeekByteUpdate_t ABL_VdoStreamByteUpdate_t;
typedef MmlVideoSeekPositionUpdate_t ABL_VdoStreamTimeUpdate_t;
typedef MmlVideoDownloadProgressUpdate_t ABL_VdoDownloadProgress_t;
typedef MmlVideoRebufferingProgressUpdate_t ABL_VdoRebufferingProgress_t;
typedef MmlVideoOpenPlayback_t ABL_VideoOpenPlayback_t;
typedef MmlVideoStartPlaybackWithHandle_t ABL_VideoStartPlaybackWithHandle_t;
typedef MmlVideoGetVideoInfo_t ABL_VideoGetVideoInfo_t;
typedef MmlVideoGetVideoInfoWithHandle_t ABL_VideoGetInfoByHandle_t;
typedef MmlVideoSetPlaybackSpeed_t ABL_VideoSetPlaybackSpeed_t;
typedef MmlVideoSetPlaybackPosition_t ABL_VideoSetPlaybackPosition_t;
typedef MmlVideoSetFullScreen_t ABL_VideoSetFullScreen_t;
typedef MmlVideoDecodeVideoThumbnailWithHandle_t ABL_VideoDecodeThumbnailByHandle_t;
typedef MmlVideoGetPlaybackCapability_t ABL_VideoGetPlaybackCapability_t;
typedef MmlVideoRecordingCapability_t ABL_VideoRecordingCap_t;
/**
 *  @brief The structure defines the notification value for application layer.
 *			should sync. with esl_VdoNotifyInfo_t
 */
typedef struct {
  MediaRspId_e  notifyTyp;    			 /**< Type of video notification */
  union {
      ABL_VdoErrorType_e   errorTyp;     /**< Video playback error type */
      u32                  position;     /**< Video playback updated position, only valid when notifyType = ESL_VDO_NOTIFY_POS_UPDATE */
      ABL_VdoBufferInfo_t  bufferInfo;   /**< Video buffer info include buffer pointer and length */
      ABL_VdoStreamByteUpdate_t tByteUpdate;   /**< Video streaming information */
      ABL_VdoStreamTimeUpdate_t tTimeUpdate;   /**< Video streaming information */
      u32                  nFileSize;    /**< Video streaming file size */
      ABL_VdoDownloadProgress_t tDownloadProgress; /**< Video streaming download progress */
      ABL_VdoRebufferingProgress_t tRebufferProg; /**< Video streaming rebuffer progress */
  } param;
} ABL_VdoNotifyInfo_t;

typedef void (*ABL_VdoCb)(u16 uSenderId, u32 uUserValue, ABL_VdoErrCode_e eErrCode, ABL_VdoInfo_t *pVdoInfo);
typedef struct {
    u16 uSenderId;     /**< Task id of sender */
    u32 uUserValue;    /**< userValue of sender for checking msg response to related applicatoin */
    ABL_VdoCb pfnCb;        /**< Done call back function that called by EMA */
} ABL_VdoCb_t;

typedef struct VideoCmd_t_
{
    ABL_VdoCb_t *pCbParams;
    u32 uHandle;
    u32 nPosition;
    union
    {
        ABL_VideoOpenPlayback_t tVideoOpenPlayback;
        ABL_VideoStartPlaybackWithHandle_t tVideoStartPlaybackWithHandle;
        ABL_VideoGetVideoInfo_t tVideoGetVideoInfo;
        ABL_VideoGetInfoByHandle_t tVideoGetInfoByHandle;
        ABL_VideoSetPlaybackSpeed_t tVideoSetPlaybackSpeed;
        ABL_VideoSetPlaybackPosition_t tVideoSetPlaybackPosition;
        ABL_VideoSetFullScreen_t tVideoSetFullScreen;
        ABL_VideoDecodeThumbnailByHandle_t tVideoDecodeThumbnailByHandle;
        ABL_VideoGetPlaybackCapability_t tVideoGetPlaybackCapability;
#ifdef __MMI_STEREO_VIDEO__
        ABL_VdoSetConfiguration_t tVdoConfiguration;
#endif
    } tParams;
} VideoCmd_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ABL_CmnErrCode_e ABL_VdoOpenSessionReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb, bool bMute);
ABL_CmnErrCode_e ABL_VdoCloseSessionReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);
void ABL_VdoGetPositionReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoGetFileInfoReq(ResMgr_AppId_e eAppId, ABL_VdoFileInfo_t *pFileInfo, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoSetPlaySpeedReq(ResMgr_AppId_e eAppId, ABL_VdoPlaySpeed_e ePlaySpeed, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoSetPositionReq(ResMgr_AppId_e eAppId, u32 uPosition, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoResetWindowReq(ResMgr_AppId_e eAppId, ABL_VdoRegion_t *pRegion, ABL_VdoRotateAngle_e eRotateAngle, ABL_VdoCb_t *pVdoCb);
#ifdef __MMI_STEREO_VIDEO__
ABL_CmnErrCode_e ABL_VdoSetConfigurationReq(ResMgr_AppId_e eAppId,ABL_VdoSetConfiguration_t *pVdoConfig,ABL_VdoCb_t *pVdoCb);
MmlImageStereoType_e ABLRemapMmlStereoType(ABLVdoStereoType_e eType);
#endif
ABL_CmnErrCode_e ABL_VdoStopPlayReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoPausePlayReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoResumePlayReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoGetMemInfoReq(ResMgr_AppId_e eAppId, ABL_VdoMemInfo_t *pMemInfo, ABL_VdoCb_t *pVdoCb);
void ABL_VdoGetPlaybackCapabilityReq(ResMgr_AppId_e eAppId, ABL_VideoGetPlaybackCapability_t *pVideoGetPlaybackCapability, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoOpenReq(ResMgr_AppId_e eAppId, ABL_VideoOpenPlayback_t *pOpenParam, ABL_VdoCb_t *pVdoCb, bool bMute);
ABL_CmnErrCode_e ABL_VdoCloseReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoPlayReq(ResMgr_AppId_e eAppId, ABL_VideoStartPlaybackWithHandle_t *pPlayParam, ABL_VdoCb_t *pVdoCb, bool bMute);
ABL_CmnErrCode_e ABL_VdoGetInfoReq(ResMgr_AppId_e eAppId, ABL_VdoBufferInfo_t *pExtInfo, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoDecodeFirstFrameExtReq(ResMgr_AppId_e eAppId, ABL_VdoDecodeFrameParam_t *pDecodeParam, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoCancelDecodeFirstFrameReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoSeekReq(ResMgr_AppId_e eAppId, ABL_VdoSeekParams_t *pSeekParam, ABL_VdoCb_t *pVdoCb);
ABL_CmnErrCode_e ABL_VdoCancelSeekReq(ResMgr_AppId_e eAppId, ABL_VdoCb_t *pVdoCb);

void ABL_VdoGetFileInfoSyncReq(ResMgr_AppId_e eAppId, ABL_VdoFileInfo_t *pFileInfo, ABL_VdoCb_t *pVdoCb);
void ABL_VdoGetMemInfoSyncReq(ResMgr_AppId_e eAppId, ABL_VdoMemInfo_t *pMemInfo, ABL_VdoCb_t *pVdoCb);
ABL_VdoCodecType_e ABL_RemapVdoCodecType(MmlVideoVideoCodec_e eCodec);
#endif //__ABL_VDO_H__
