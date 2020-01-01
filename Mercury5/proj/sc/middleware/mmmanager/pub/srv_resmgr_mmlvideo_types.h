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
* @file    srv_resmgr_mmlvideo_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLVIDEO_TYPES_H__
#define __SRV_RESMGR_MMLVIDEO_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup MMLayerVideo Video
    Video Playback and Recording
    @{
*/
    /** @defgroup MMLayerVideoPlayback Video Playback
        Video Playback
        @{
    */
    /** @} */

    /** @defgroup MMLayerVideoRecording Video Recording
        Video Recording
        @{
    */
    /** @} */

    /** @defgroup MMLayerVideoTelephony Video Telephony
        Video Telephony
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"
#include "srv_resmgr_mmlaudio_types.h"
#include "srv_resmgr_mmlcamera_types.h"
#include "srv_resmgr_mmlimage_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerVideo
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseVideoId_e_)
{
    /* Video Init */
    MML_UCID_VIDEO_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_VIDEO),
    MML_UCID_VIDEO_REG_NOTIFY_CALLBACK = MML_UCID_VIDEO_INIT_BASE,              ///< 00020000 = Reg notify callback
    MML_UCID_VIDEO_UNREG_NOTIFY_CALLBACK,                                       ///< 00020001 = Unreg notify callback
    MML_UCID_VIDEO_INIT_CATEGORY,

    /* Video Get */
    MML_UCID_VIDEO_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_VIDEO),
    MML_UCID_VIDEO_GET_VIDEO_INFO = MML_UCID_VIDEO_GET_BASE,                    ///< 00020100 = Get video info
    MML_UCID_VIDEO_GET_VIDEO_INFO_WITH_HANDLE,                                  ///< 00020101 = Get video info with hanle
    MML_UCID_VIDEO_GET_PLAYBACK_POSITION,                                       ///< 00020102 = Get playback position
    MML_UCID_VIDEO_GET_RECORDING_SETTING,                                       ///< 00020103 = Get recording setting
    MML_UCID_VIDEO_GET_PLAYBACK_CAPABILITY,                                     ///< 00020104 = Get playback capability
    MML_UCID_VIDEO_GET_RECORDING_CAPABILITY,                                    ///< 00020105 = Get recording capability
    MML_UCID_VIDEO_GET_CONFIGURATION,                                           ///< 00020106 = Get playback configuration
    MML_UCID_VIDEO_GET_CATEGORY,

    /* Video Set */
    MML_UCID_VIDEO_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_VIDEO),
    MML_UCID_VIDEO_SET_PLAYBACK_SPEED = MML_UCID_VIDEO_SET_BASE,                ///< 00020200 = Set playback speed
    MML_UCID_VIDEO_SET_PLAYBACK_POSITION,                                       ///< 00020201 = Set playback position
    MML_UCID_VIDEO_SET_PLAYBACK_POSITION_ASYNC,                                 ///< 00020202 = Set playback position Async
    MML_UCID_VIDEO_SET_FULL_SCREEN,                                             ///< 00020203 = Set full screen
    MML_UCID_VIDEO_SET_RECORDING_SETTING,                                       ///< 00020204 = Set recording setting
    MML_UCID_VIDEO_SET_VIDEO_TELEPHONY_SETTING,                                 ///< 00020205 = Set video telephony setting
    MML_UCID_VIDEO_SET_CONFIGURATION,                                           ///< 00020206 = Set playback configuration
    MML_UCID_VIDEO_SET_CATEGORY,

    /* Video Execute */
    MML_UCID_VIDEO_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_VIDEO),
    MML_UCID_VIDEO_START_PLAYBACK = MML_UCID_VIDEO_EXECUTE_BASE,                ///< 00020300 = Start playback
    MML_UCID_VIDEO_OPEN_PLAYBACK,                                               ///< 00020301 = Open playback
    MML_UCID_VIDEO_START_PLAYBACK_WITH_HANDLE,                                  ///< 00020302 = Start playback after open playback
    MML_UCID_VIDEO_STOP_PLAYBACK,                                               ///< 00020303 = Stop playback
    MML_UCID_VIDEO_PAUSE_PLAYBACK,                                              ///< 00020304 = Pause playback
    MML_UCID_VIDEO_RESUME_PLAYBACK,                                             ///< 00020305 = Resume playback
    MML_UCID_VIDEO_CANCEL_SEEK,                                                 ///< 00020306 = Cancel seek
    MML_UCID_VIDEO_CLOSE_PLAYBACK,                                              ///< 00020307 = Close playback
    MML_UCID_VIDEO_DECODE_VIDEO_THUMBNAIL,                                      ///< 00020308 = Decode video thumbnail
    MML_UCID_VIDEO_DECODE_VIDEO_THUMBNAIL_WITH_HANDLE,                          ///< 00020309 = Async decode video thumbnail with handle
    MML_UCID_VIDEO_CANCEL_DECODE_VIDEO_THUMBNAIL_WITH_HANDLE,                   ///< 0002030A = Cancel decode video thumbnail with handle

    MML_UCID_VIDEO_START_RECORDING,                                             ///< 0002030B = Start recording
    MML_UCID_VIDEO_STOP_RECORDING,                                              ///< 0002030C = Stop recording
    MML_UCID_VIDEO_PAUSE_RECORDING,                                             ///< 0002030D = Pause recording
    MML_UCID_VIDEO_RESUME_RECORDING,                                            ///< 0002030E = Resume recording
    MML_UCID_VIDEO_SAVE_RECORDING_FILE,                                         ///< 0002030F = Save recording file
    MML_UCID_VIDEO_DISCARD_RECORDING_FILE,                                      ///< 00020310 = Discard recording file
    MML_UCID_VIDEO_ABORT_SAVING,                                                ///< 00020311 = Abort saving

    MML_UCID_VIDEO_OPEN_VIDEO_TELEPHONY,                                        ///< 00020312 = Open video telephony
    MML_UCID_VIDEO_CLOSE_VIDEO_TELEPHONY,                                       ///< 00020313 = Close video telephony
    MML_UCID_VIDEO_START_VIDEO_TELEPHONY,                                       ///< 00020314 = Start video telephony
    MML_UCID_VIDEO_STOP_VIDEO_TELEPHONY,                                        ///< 00020315 = Stop video telephony
    MML_UCID_VIDEO_START_VIDEO_TELEPHONY_RECORDING,                             ///< 00020316 = Start video telephony recording
    MML_UCID_VIDEO_STOP_VIDEO_TELEPHONY_RECORDING,                              ///< 00020317 = Stop video telephony recording
    MML_UCID_VIDEO_SAVE_VIDEO_TELEPHONY_RECORDING_FILE,                         ///< 00020318 = Save video telephony recording file
    MML_UCID_VIDEO_DISCARD_VIDEO_TELEPHONY_RECORDING_FILE,                      ///< 00020319 = Discard video telephony recording file
    MML_UCID_VIDEO_ABORT_VIDEO_TELEPHONY_SAVING,                                ///< 0002031A = Abort video telephony saving
    MML_UCID_VIDEO_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_VIDEO_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerVideo
    @brief      Response results
*/
typedef enum
{
    /* Common */
    VIDEO_ERROR_SUCCESS = 0,
    VIDEO_ERROR_FAIL,
    VIDEO_ERROR_PARAMETER_INVALID,
    VIDEO_ERROR_STATE_CHANGE,
    VIDEO_ERROR_ACCEPT,
    VIDEO_ERROR_IGNORE,
    VIDEO_ERROR_REJECT,
    VIDEO_ERROR_MEMORY_FAILURE,
    /* Video Playback */
    VIDEO_ERROR_PLAYBACK_STOP_FAIL,
    VIDEO_ERROR_PLAYBACK_REBUFFERING,
    VIDEO_ERROR_PLAYBACK_OPEN_FAIL,
    VIDEO_ERROR_LICENSE_MISMATCH,
    VIDEO_ERROR_LICENSE_NOTEXIST,
    VIDEO_ERROR_PASSWORD_MISMATCH,
    VIDEO_ERROR_NETWORK_FAIL,
    VIDEO_ERROR_INVALID_HANDLE_CAPABILITY,
    /* Video Recording */
    VIDEO_ERROR_DISK_FULL,
    VIDEO_ERROR_RECORDING_STOP_FAIL,
    /* Video Telephony */
    /* */
    VIDEO_ERROR_NUM
} MmlVideoResult_e;

/** @ingroup    MMLayerVideo
    @brief      States
*/
typedef enum
{
    /* Video Playback */
    VIDEO_STATE_PLAYBACK_STOPPED = 0,
    VIDEO_STATE_PLAYBACK_PLAYING,
    VIDEO_STATE_PLAYBACK_PAUSED,
    VIDEO_STATE_PLAYBACK_SEEKING,
    VIDEO_STATE_PLAYBACK_CLOSED,
    VIDEO_STATE_PLAYBACK_STOPPED_TRAN = 0,
    VIDEO_STATE_PLAYBACK_PLAYING_TRAN,
    VIDEO_STATE_PLAYBACK_PAUSED_TRAN,
    VIDEO_STATE_PLAYBACK_SEEKING_TRAN,
    /* Video Recording */
    VIDEO_STATE_RECORDING_STOPPED,
    VIDEO_STATE_RECORDING_RECORDING,
    VIDEO_STATE_RECORDING_PAUSED,
    VIDEO_STATE_RECORDING_SAVING,
    /* Video Telephony */
    VIDEO_STATE_TELEPHONY_CLOSED,
    VIDEO_STATE_TELEPHONY_OPENED,
    VIDEO_STATE_TELEPHONY_PLAYING,
    /* */
    VIDEO_STATE_DONTCARE,
    VIDEO_STATE_NUM
} MmlVideoState_e;

/** @ingroup    MMLayerVideo
    @brief      Events
*/
typedef enum
{
    /* Common */
    VIDEO_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_VIDEO),
    VIDEO_EVENT_RUNTIME_ERROR,
    VIDEO_EVENT_POSITION_UPDATE,
    /* Video Playback */
    VIDEO_EVENT_PLAYBACK_STATE_CHANGE,
    VIDEO_EVENT_PLAYBACK_RUNTIME_ERROR,
    VIDEO_EVENT_PLAYBACK_POSITION_UPDATE,
    VIDEO_EVENT_SEEK_COMPLETE,
    VIDEO_EVENT_SEEK_CANCELED,
    VIDEO_EVENT_SEEK_BYTE_UPDATE,
    VIDEO_EVENT_SEEK_TIME_UPDATE,
    VIDEO_EVENT_SEEK_ERROR,
    VIDEO_EVENT_PLAYBACK_END,
    VIDEO_EVENT_PLAYBACK_REBUFFERING,
    VIDEO_EVENT_PLAYBACK_REBUFFERING_PROGRESS_UPDATE,
    VIDEO_EVENT_PLAYBACK_REBUFFERING_DONE,
    VIDEO_EVENT_OPEN_COMPLETE,
    VIDEO_EVENT_OPEN_ERROR,
    VIDEO_EVENT_DECODE_THUMBNAIL_COMPLETE,
    VIDEO_EVENT_DECODE_THUMBNAIL_ERROR,
    VIDEO_EVENT_DOWNLOAD_PROGRESS_UPDATE,
    /* Video Recording */
    VIDEO_EVENT_RECORDING_STATE_CHANGE,
    VIDEO_EVENT_RECORDING_RUNTIME_ERROR,
    VIDEO_EVENT_RECORDING_POSITION_UPDATE,
    VIDEO_EVENT_SAVE_FILE_COMPLETE,
    VIDEO_EVENT_RECORD_FILE_DISCARDED,
    VIDEO_EVENT_SAVE_FILE_ABORTED,
    VIDEO_EVENT_REACH_TIME_LIMIT,
    VIDEO_EVENT_REACH_SIZE_LIMIT,
    /* Video Telephony */
    VIDEO_EVENT_TELEPHONY_STATE_CHANGE,
    VIDEO_EVENT_TELEPHONY_RUNTIME_ERROR,
    /* */
    VIDEO_EVENT_DONTCARE,
    VIDEO_EVENT_ALL,
    VIDEO_EVENT_NUM
} MmlVideoEvent_e;

/** @ingroup    MMLayerVideo
    @brief      Input source types
*/
typedef enum
{
    /* Video Playback */
    VIDEO_INPUT_FILE = 0,    ///< Playback from file-based source
    VIDEO_INPUT_MEMORY,      ///< Playback from in-memory source
    VIDEO_INPUT_STREAMING,   ///< Playback from streaming
    /* Video Recording */
    /* Video Telephony */
    VIDEO_INPUT_CAMERA,      ///< Input image from camera sensor
    /* */
    VIDEO_INPUT_NUM
} MmlVideoInputType_e;

/** @ingroup    MMLayerVideo
    @brief      Output destination types
*/
typedef enum
{
    /* Video Recording */
    VIDEO_OUTPUT_FILE = 0,    ///< Record to file-based destination
    VIDEO_OUTPUT_MEMORY,      ///< Record to in-memory destination
    /* Video Playback */
    /* */
    VIDEO_OUTPUT_NUM
} MmlVideoOutputType_e;

/** @ingroup    MMLayerVideo
    @brief      video streaming mode
*/
typedef enum
{
    VIDEO_STREAMING_MODE_FILE = 0,    ///< Streaming in file mode
    VIDEO_STREAMING_MODE_MEMORY,      ///< Streaming in memory mode
    VIDEO_STREAMING_MODE_NUM
} MmlVideoStreamingMode_e;

/** @ingroup    MMLayerVideo
    @brief      video streaming link type
*/
typedef enum
{
    VIDEO_STREAMING_LINKTYPE_WIFI = 0,       ///< Streaming link type wifi
    VIDEO_STREAMING_LINKTYPE_GPRS_SIM1,      ///< Streaming link type gprs sim1
    VIDEO_STREAMING_LINKTYPE_GPRS_SIM2       ///< Streaming link type gprs sim2
} MmlVideoStreamingLinkType_e;

/** @ingroup    MMLayerVideo
    @brief      video streaming download status
*/
typedef enum
{
    VIDEO_STREAMING_DOWNLOADSTATUS_COMPLETE = 0,    ///< Download status complete
    VIDEO_STREAMING_DOWNLOADSTATUS_INCOMPLETE,      ///< Download status incomplete
} MmlVideoStreamingDownloadStatus_e;

/** @ingroup    MMLayerVideo
    @brief      Video codecs
*/
typedef enum
{
    VIDEO_VIDEOCODEC_MPEG2 = 0,    ///< MPEG2, also known as H.262 video format
    VIDEO_VIDEOCODEC_H263,         ///< ITU H.263 video format
    VIDEO_VIDEOCODEC_MPEG4,        ///< MPEG4 video format
    VIDEO_VIDEOCODEC_AVC,          ///< MPEG4 Part 10 Advanced Video Coding, also known as H.264 video format
    VIDEO_VIDEOCODEC_VC1,          ///< Windows Media Codec video format
    VIDEO_VIDEOCODEC_RVC,          ///< Real Video Codec format
    VIDEO_VIDEOCODEC_MJPEG,        ///< Motion JPEG
    VIDEO_VIDEOCODEC_KMV,          ///< King Movie format
    VIDEO_VIDEOCODEC_DONTCARE,
    /* */
    VIDEO_VIDEOCODEC_NUM,
    VIDEO_VIDEOCODEC_UNSUPPORTED   ///< Unsupported codec
} MmlVideoVideoCodec_e;

/** @ingroup    MMLayerVideo
    @brief      Video formats
*/
typedef enum
{
    VIDEO_FORMAT_3GP = 0,    ///< .3gp
    VIDEO_FORMAT_MP4,        ///< .mp4
    VIDEO_FORMAT_RM,         ///< .rm
    VIDEO_FORMAT_RMVB,       ///< .rmvb
    VIDEO_FORMAT_AVI,        ///< .avi
    VIDEO_FORMAT_FLV,        ///< .flv
    VIDEO_FORMAT_PS,         ///< .ps
    VIDEO_FORMAT_TS,         ///< .ts
    VIDEO_FORMAT_H324,       ///< .h324 (video telephony)
    VIDEO_FORMAT_MPG,        ///< .mpg/.mpeg
    VIDEO_FORMAT_VOB,        ///< .vob
    VIDEO_FORMAT_DAT,        ///< .dat
    VIDEO_FORMAT_DIVX,       ///< .divx
    VIDEO_FORMAT_MOV,        ///< .mov
    VIDEO_FORMAT_KMV,        ///< .kmv
    VIDEO_FORMAT_MKV,        ///< .mkv
    VIDEO_FORMAT_UNKNOWN,    ///< I don't know what format it is
    VIDEO_FORMAT_NUM
} MmlVideoFormat_e;

/** @ingroup    MMLayerVideo
    @brief      Rotation angles
*/
typedef enum
{
    VIDEO_ROTATION_0 = 0,
    VIDEO_ROTATION_90,
    VIDEO_ROTATION_180,
    VIDEO_ROTATION_270,
    /* */
    VIDEO_ROTATION_NUM
} MmlVideoRotationAngle_e;

/** @ingroup    MMLayerVideo
    @brief      Seek type
*/
typedef enum
{
    VIDEO_SEEK_PRECISE = 0,                 ///< precise seeking type, considering all frames within video file.It takes longer time to complete seeking
    VIDEO_SEEK_FAST_IFRAME,                 ///< imprecise seeking type, considering iframes only.It takes less time to complete seeking
    VIDEO_SEEK_NUM
} MmlVideoSeekType_e;

/** @ingroup    MMLayerVideo
    @brief      Handle capability
*/
typedef enum
{
    VIDEO_HANDLE_CAPABILITY_LOW = 0,        ///< Use with 'MML_UCID_VIDEO_GET_VIDEO_INFO_WITH_HANDLE'
    VIDEO_HANDLE_CAPABILITY_MEDIUM,         ///< Use with 'MML_UCID_VIDEO_GET_VIDEO_INFO_WITH_HANDLE',
                                            ///<          'MML_UCID_VIDEO_DECODE_VIDEO_THUMBNAIL_WITH_HANDLE'
    VIDEO_HANDLE_CAPABILITY_HIGH            ///< Use with 'MML_UCID_VIDEO_GET_VIDEO_INFO_WITH_HANDLE'
                                            ///<          'MML_UCID_VIDEO_DECODE_VIDEO_THUMBNAIL_WITH_HANDLE'
                                            ///<          'MML_UCID_VIDEO_START_PLAYBACK_WITH_HANDLE'
} MmlVideoHandleCapability_e;

/** @ingroup    MMLayerVideo
    @brief      Configuration types
*/
typedef enum
{
    VIDEO_CONFIGURATIONTYPE_DISPLAYCALIBRATION  = 0,       ///< Display calibration
    VIDEO_CONFIGURATIONTYPE_IMAGESTEREO_TYPE,              ///< Image stereo type
    VIDEO_CONFIGURATIONTYPE_IMAGESTEREO_DEPTH,             ///< Image stereo depth
    /* Get only types */
    VIDEO_CONFIGURATIONTYPE_DISPLAYCALIBRATION_MAX         ///< Get maximum display calibration values
} MmlVideoConfigurationType_e;

/** @ingroup    MMLayerVideoTelephony
    @brief      MUX formats
*/
typedef enum
{
    VIDEO_TELEPHONY_MUXFORMAT_H223 = 0,   ///< .223
    VIDEO_TELEPHONY_MUXFORMAT_UNKNOWN,    ///< I don't know what format it is
    /* */
    VIDEO_TELEPHONY_MUXFORMAT_NUM
} MmlVideoTelephonyMuxFormat_e;

/** @ingroup    MMLayerVideoTelephony
    @brief      Screen modes
*/
typedef enum
{
    VIDEO_TELEPHONY_SCREENMODE_LOCALLARGE = 0,     ///< Local screen large size
    VIDEO_TELEPHONY_SCREENMODE_LOCALSMALL,         ///< Local screen small size
    VIDEO_TELEPHONY_SCREENMODE_LOCALONLY,          ///< Local screen only
    VIDEO_TELEPHONY_SCREENMODE_REMOTEONLY,         ///< Remote screen only
    /* */
    VIDEO_SCREENMODE_NUM
} MmlVideoTelephonyScreenMode_e;

/** @ingroup    MMLayerVideoTelephony
    @brief      Setting types
*/
typedef enum
{
    VIDEO_TELEPHONY_SETTINGTYPE_DIGITALZOOM = 0,   ///< Digital zoom level
    VIDEO_TELEPHONY_SETTINGTYPE_SCREENMODE,        ///< Screen mode
    VIDEO_TELEPHONY_SETTINGTYPE_INPUTSOURCE,       ///< Input source
    VIDEO_TELEPHONY_SETTINGTYPE_BRIGHTNESS,        ///< Brightness
    VIDEO_TELEPHONY_SETTINGTYPE_CONTRAST,          ///< Contrast
    VIDEO_TELEPHONY_SETTINGTYPE_REMOTEPICTURE,     ///< Remote picture
    VIDEO_TELEPHONY_SETTINGTYPE_BLANKPREVIEW,      ///< Blank preview
    VIDEO_TELEPHONY_SETTINGTYPE_SENSORSOURCE,      ///< Sensor source
    VIDEO_TELEPHONY_SETTINGTYPE_NUM
} MmlVideoTelephonySettingType_e;

/** @ingroup    MMLayerVideo
    @brief      File-based source
*/
typedef struct
{
    MmlVideoFormat_e       eFormat;
    MmlFilenameFormat_e    eFilenameFormat;
    u16                    *pFileName;
    u16  	               nFileNameSize;
    u16                    bStreamingEnable;       ///< Enable the file streaming
    u32                    nStreamingSize;         ///< Size in bytes of the streaming file
} MmlVideoFileParam_t;

/** @ingroup    MMLayerVideo
    @brief      In-memory source
*/
typedef	struct
{
    MmlVideoFormat_e    eFormat;
    u8                  *pBuffer;
    u32                 nBufferSize;
    u16                 bRepeat;
} MmlVideoMemoryParam_t;

/** @ingroup    MMLayerVideo
    @brief      Download module callback prototype
*/
typedef s32 (*PfnMmlVideoDownloadModuleCallback)(s32 nMessageType, s32 nDataSize, void *pData);

/** @ingroup    MMLayerVideo
    @brief      File mode streaming parameters
*/
typedef	struct
{
    MmlVideoStreamingDownloadStatus_e eDownloadStatus;
} MmlVideoStreamingFileParam_t;

/** @ingroup    MMLayerVideo
    @brief      Streaming parameters
*/
typedef	struct
{
    MmlVideoStreamingMode_e             eStreamingMode;
    MmlVideoStreamingLinkType_e         eStreamingLinkType;
    u16                                 *pUrl;
    u16  	                            nUrlSize;
    u16                                 *pFileName;
    u16  	                            nFileNameSize;
    PfnMmlVideoDownloadModuleCallback   pfnDownloadModuleCallback;
    union
    {
   	    MmlVideoStreamingFileParam_t    tStreamFileParam;         ///< File mode Streaming parameters

    } uParam;
} MmlVideoStreamingParam_t;

/** @ingroup    MMLayerVideo
    @brief      A block of memory, used to hold input/output data
*/
typedef	struct
{
    u8                  *pBuffer;       ///< Pointer to the data buffer
    u32                 nBufferSize;    ///< Size in bytes of the data buffer
    u32                 nDataSize;      ///< Read/Write size in bytes of data in the data buffer
} MmlVideoBufferParam_t;

/** @ingroup    MMLayerVideo
    @brief      Video streaming seek byte update info
*/
typedef	struct
{
    u32                 nSessionID;     /// Session ID
    u32                 nSeekByte;      /// Seek byte
} MmlVideoSeekByteUpdate_t;

/** @ingroup    MMLayerVideo
    @brief      Video streaming seek position update info
*/
typedef	struct
{
    u32                 nSessionID;     /// Session ID
    u32                 nPosition;      /// Seek position
} MmlVideoSeekPositionUpdate_t;


/** @ingroup    MMLayerVideo
    @brief      Video download progress update
*/
typedef	struct
{
    u32                 nStartPosition;     /// download start position
    u32                 nEndPosition;       /// download end position
} MmlVideoDownloadProgressUpdate_t;

/** @ingroup    MMLayerVideo
    @brief      Video streaming rebuffering progress update info
*/
typedef	struct
{
    u32                 nTotalSize;     /// Total rebuffering  size
    u32                 nCurrentSize;   /// Current rebuffering size
} MmlVideoRebufferingProgressUpdate_t;

/** @ingroup    MMLayerVideo
    @brief      Rectangle
*/
typedef struct
{
    u16     nLeft;      ///< x-position of the top left corner of rectangle
    u16     nTop;       ///< y-position of the top left corner of rectangle
    u16     nWidth;     ///< Width of rectangle
    u16     nHeight;    ///< Height of rectangle
} MmlVideoRectangle_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Playback speeds
*/
typedef enum
{
    VIDEO_PLAYBACK_SPEED_50 = 0,    ///< 0.5x
    VIDEO_PLAYBACK_SPEED_100,       ///< 1x
    VIDEO_PLAYBACK_SPEED_200,       ///< 2x
    VIDEO_PLAYBACK_SPEED_400,       ///< 4x
    VIDEO_PLAYBACK_SPEED_800        ///< 8x
} MmlVideoPlaybackSpeed_e;

/** @ingroup    MMLayerVideo
    @brief      Video info
*/
typedef struct
{
    MmlAudioSamplingRate_e        eSamplingRate;                    ///< Sampling rate (hz)
    MmlAudioChannelMode_e         eChannelMode;                     ///< Channel mode
    u32                           nAudioBitRate;                    ///< 32-bit audio bitrate in units of bps
    u32                           nVideoBitRate;                    ///< 32-bit video bitrate in units of bps
    u32                           nTotalPlayTime;                   ///< 32-bit total play time expressed in milliseconds
    u16                           nWidth;                           ///< Frame width in pixels
    u16                           nHeight;                          ///< Frame height in pixels
    MmlAudioAudioCodec_e          eAudioCodecId;                    ///< Associated audio codec ID
    MmlVideoVideoCodec_e          eVideoCodecId;                    ///< Associated video codec ID
    MmlVideoFormat_e              eFormat;                          ///< Video container format
    u16                           bVideoIsSeekable;                 ///< TRUE for seekable video
    MmlVideoPlaybackSpeed_e       ePlaybackSpeed;                   ///< Maximum supported playback speed
    MmlVideoBufferParam_t         tBufferParam;                     ///< Buffer to store the extended video info (KingMovie)
    MmlImageStereoType_e          eImageStereoType;                 ///< Image stereo types
    u16                           bIsImageStereoDepthAdjustable;    ///< Is image stereo depth adjustable
} MmlVideoInfo_t;

/** @ingroup    MMLayerVideo
    @brief      State change info
*/
typedef	struct
{
    MmlVideoState_e            eState;        ///< The new state after the transition
    MmlVideoEvent_e	           eCause;        ///< The cause of state change, if any

    /// union of MmlVideoStateChange_t parameters
    union
    {
   	    MmlVideoFileParam_t    tFileParam;         ///< Filename of the saved file
   	    u32                    nPosition;          ///< The last playback position returned from 'Stop playback'
        u32                    nStreamimgFileSize; ///< Streaming file size, used with open video streaming complete
    } uParam;
} MmlVideoStateChange_t;

/** @ingroup    MMLayerVideo
    @brief      Notification payload
*/
typedef struct
{
    MmlVideoEvent_e	            eEvent;             ///< Specify the event you want to notify
    u32                         nHandle;            ///< 32-bit playback/recording handle

    /// union of MmlVideoNotify_t parameters
    union
    {
        MmlVideoStateChange_t            	tStateChange;               ///< Used with VIDEO_EVENT_STATE_CHANGE event
        MmlVideoResult_e                 	eErrCode;                   ///< Used with VIDEO_EVENT_RUNTIME_ERROR event
        MmlVideoFileParam_t              	tFileParam;                 ///< Used with VIDEO_EVENT_SAVE_FILE_COMPLETE event
        MmlVideoBufferParam_t            	tBufferParam;               ///< Used with VIDEO_EVENT_DECODE_THUMBNAIL_COMPLETE event
        MmlVideoSeekByteUpdate_t         	tSeekByteUpdate;            ///< Used with VIDEO_EVENT_SEEK_BYTE_UPDATE event
        MmlVideoSeekPositionUpdate_t     	tSeekPositionUpdate;        ///< Used with VIDEO_EVENT_SEEK_TIME_UPDATE event
        MmlVideoDownloadProgressUpdate_t 	tDownloadProgressUpdate;    ///< Used with VIDEO_EVENT_DOWNLOAD_PROGRESS_UPDATE
        MmlVideoRebufferingProgressUpdate_t tRebufferingProgressUpdate; ///< Used with VIDEO_EVENT_PLAYBACK_REBUFFERING_PROGRESS_UPDATE event
        u32                              	nPosition;                  ///< Used with VIDEO_EVENT_POSITION_UPDATE/VIDEO_EVENT_SEEK_COMPLETE event
        u32                              	nTimeLimit;                 ///< Used with VIDEO_EVENT_REACH_TIME_LIMIT event
        u32                              	nSizeLimit;                 ///< Used with VIDEO_EVENT_REACH_SIZE_LIMIT event
        u32                              	nRebufferSize;              ///< Used with VIDEO_EVENT_PLAYBACK_REBUFFERING event
        u32                              	nSeekByte;                  ///< Used with VIDEO_EVENT_SEEK_BYTE_UPDATE event
	} uParam;
} MmlVideoNotify_t;

/** @ingroup    MMLayerVideo
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pVideoNotify      Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlVideoNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlVideoNotify_t *pVideoNotify);

/** @ingroup    MMLayerVideo
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;           ///< Sender's mailbox ID
    u32                             nUserValue;          ///< Interface self-reference
    PfnMmlVideoNotifyCallback       pfnNotifyCallback;   ///< Callback function your want to register
} MmlVideoNotifyCallback_t;

/** @ingroup    MMLayerVideo
    @brief      Response callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      eErrCode          Returned result (error code)
    @param      pVideoResponse    Pointer to the returned response payload
*/
struct MmlVideoResponse_t_;
typedef void (*PfnMmlVideoResponseCallback)(u16 nSenderID, u32 nUserValue, MmlVideoResult_e eErrCode, struct MmlVideoResponse_t_ *pVideoResponse);

/** @ingroup    MMLayerVideo
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlVideoResponseCallback     pfnResponseCallback;    ///< Callback function your want to register
} MmlVideoResponseCallback_t;

/** @ingroup    MMLayerVideo
    @brief      Register notification callback
*/
typedef struct
{
    MmlVideoEvent_e                 eEvent;             ///< Specify which event you want to handle
    MmlVideoNotifyCallback_t        tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlVideoRegNotifyCallback_t;

/** @ingroup    MMLayerVideo
    @brief      Get video info
*/
typedef struct
{
    MmlVideoInputType_e          eInputType;       ///< Input source types
    MmlVideoBufferParam_t        tBufferParam;     ///< Buffer to store the extended video info (KingMovie)
    u8                           *pPasswordBuffer; ///< Pointer to the password buffer
    u32                          nPasswordLength;  ///< Size in bytes of the password buffer
    /// union of MmlVideoGetVideoInfo_t parameters
    union
    {
	    MmlVideoFileParam_t     tFileParam;      ///< Get info from file-based source
	    MmlVideoMemoryParam_t   tMemoryParam;    ///< Get info from in-memory source
	    u32                     nHandle;         ///< Get info from streaming
	} uParam;

} MmlVideoGetVideoInfo_t;

/** @ingroup    MMLayerVideo
    @brief      Get video info
*/
typedef struct
{
    u32                          nHandle;          ///< Opened Handle
    MmlVideoBufferParam_t        tBufferParam;     ///< Buffer to store the extended video info (KingMovie)
} MmlVideoGetVideoInfoWithHandle_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Open playback (file/memory)
*/
typedef struct
{
    MmlVideoInputType_e         eInputType;            ///< Input source type
    u8                          *pPasswordBuffer;      ///< Pointer to the password buffer
    u32                         nPasswordLength;       ///< Size in bytes of the password buffer
    MmlVideoHandleCapability_e  eHandleCapability;     ///< Handle capability

    /// union of MmlVideoStartPlayback_t parameters
    union
    {
	    MmlVideoFileParam_t         tFileParam;      ///< Playback from file-based source
	    MmlVideoMemoryParam_t       tMemoryParam;    ///< Playback from in-memory source
	    MmlVideoStreamingParam_t    tStreamingParam; ///< Playback from streaming
		u32                         nHandle;         ///< Playback from streaming
	} uParam;
} MmlVideoOpenPlayback_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Start playback (file/memory)
*/
typedef struct
{
    MmlVideoInputType_e         eInputType;            ///< Input source type
    MmlAudioOutputType_e        eAudioOutputType;      ///< Audio Output destination type (IIS, A2DP)
    u32                         nPosition;             ///< 32-bit value expressed in milliseconds and relative to the beginning of the content
    MmlVideoRotationAngle_e     eRotationAngle;        ///< 0, 90, 180, 270 degree
    MmlVideoRectangle_t         tOutputWindow;         ///< Output window
    u16                         nOutputWindowPitch;    ///< Output window pitch
    u8                          *pPasswordBuffer;      ///< Pointer to the password buffer
    u32                         nPasswordLength;       ///< Size in bytes of the password buffer
    u16                         bIsRingTone;           ///< Is ring tone
    /// union of MmlVideoStartPlayback_t parameters
    union
    {
	    MmlVideoFileParam_t     tFileParam;      ///< Playback from file-based source
	    MmlVideoMemoryParam_t   tMemoryParam;    ///< Playback from in-memory source
	} uParam;
} MmlVideoStartPlayback_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Image stereo parameters
*/
typedef struct
{
    u32                         nImageStereoDepth;     ///< Image stereo depth
    MmlImageStereoType_e        eImageStereoType;      ///< Image stereo types
} MmlVideoImageStereoParam_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Start playback with handle (file/memory)
*/
typedef struct
{
    u32                         nHandle;               ///< Opened handle(instance)
    MmlAudioOutputType_e        eAudioOutputType;      ///< Audio Output destination type (IIS, A2DP)
    MmlVideoRotationAngle_e     eRotationAngle;        ///< 0, 90, 180, 270 degree
    MmlVideoRectangle_t         tOutputWindow;         ///< Output window
    u16                         nOutputWindowPitch;    ///< Output window pitch
    u16                         bAudioEnable;          ///< true: enable audio;false: disable audio
    MmlVideoImageStereoParam_t  tImageStereoParam;     ///< Image stereo parameters
    u16                         bIsRingTone;           ///< Is ring tone
} MmlVideoStartPlaybackWithHandle_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Decode video thumbnail (file/memory)
*/
typedef struct
{
    MmlVideoInputType_e         eInputType;            ///< Input source type
    MmlVideoRotationAngle_e     eRotationAngle;        ///< 0, 90, 180, 270 degree
    MmlVideoRectangle_t         tOutputWindow;         ///< Output window
    u16                         nOutputWindowPitch;    ///< Output window pitch
    MmlVideoBufferParam_t       tBufferParam;          ///< Output thumbnail buffer
    u8                          *pPasswordBuffer;      ///< Pointer to the password buffer
    u32                         nPasswordLength;       ///< Size in bytes of the password buffer
    /// union of MmlVideoDecodeVideoThumbnail_t parameters
    union
    {
	    MmlVideoFileParam_t     tFileParam;      ///< Decode from file-based source
	    MmlVideoMemoryParam_t   tMemoryParam;    ///< Decode from in-memory source
	    u32                     nHandle;         ///< Decode from streaming source
	} uParam;
} MmlVideoDecodeVideoThumbnail_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Decode video thumbnail with handle
*/
typedef struct
{
    u32                         nHandle;               ///< Opened Handle
    MmlVideoRotationAngle_e     eRotationAngle;        ///< 0, 90, 180, 270 degree
    MmlVideoRectangle_t         tOutputWindow;         ///< Output window
    u16                         nOutputWindowPitch;    ///< Output window pitch
    MmlVideoBufferParam_t       tBufferParam;          ///< Output thumbnail buffer
    MmlImageStereoType_e        eImageStereoType;      ///< Image stereo types
} MmlVideoDecodeVideoThumbnailWithHandle_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Set playback speed
*/
typedef struct
{
    u32                         nHandle;           ///< 32-bit playback handle
    MmlVideoPlaybackSpeed_e     ePlaybackSpeed;    ///< Playback speed
} MmlVideoSetPlaybackSpeed_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Set playback position
*/
typedef struct
{
    u32                         nHandle;        ///< 32-bit playback handle
    u32                         nPosition;      ///< 32-bit value expressed in milliseconds and relative to the beginning of the content
    u32                         nTimeout;       ///< Timeout in ms
    MmlVideoSeekType_e          eSeekType;      ///< Seek type
} MmlVideoSetPlaybackPosition_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Set full screen
*/
typedef struct
{
    u32                         nHandle;           ///< 32-bit playback handle
    MmlVideoRotationAngle_e     eRotationAngle;    ///< 0, 90, 180, 270 degree
    MmlVideoRectangle_t         tOutputWinddow;    ///< Output window
} MmlVideoSetFullScreen_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Display calibration
*/
typedef struct
{
    u16                         nContrast;         ///< Contrast
    u16                         nBrightness;       ///< Brightness
    u16                         nSaturation;       ///< Saturation
    u16                         nSharpness;        ///< Sharpness
    u16                         nBlackLevel;       ///< Black level
    u16                         nWhiteLevel;       ///< White level
} MmlVideoDisplayCalibration_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Set image stereo type
*/
typedef struct
{
    u32                         nHandle;           ///< 32-bit playback handle
    MmlImageStereoType_e        eImageStereoType;  ///< Image stereo types
} MmlVideoSetImageStereoType_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Set image stereo depth
*/
typedef struct
{
    u32                         nHandle;           ///< 32-bit playback handle
    u32                         nImageStereoDepth; ///< Image stereo depth
} MmlVideoSetImageStereoDepth_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Set configuration
*/
typedef struct
{
    MmlVideoConfigurationType_e    eConfigurationType;    ///< Specify which type of setting to be configured
    /// union of MmlVideoSetConfiguration_t parameters
    union
    {
       MmlVideoDisplayCalibration_t     tDisplayCalibration;    ///< Used with 'VIDEO_CONFIGURATIONTYPE_DISPLAY_CALIBRATION'
	   MmlVideoSetImageStereoType_t     tSetImageStereoType;    ///< Used with 'VIDEO_CONFIGURATIONTYPE_IMAGESTEREO_TYPE'
       MmlVideoSetImageStereoDepth_t    tSetImageStereoDepth;   ///< Used with 'VIDEO_CONFIGURATIONTYPE_IMAGESTEREO_DEPTH'
	} uParam;
} MmlVideoSetConfiguration_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Get configuration
*/
typedef struct
{
    MmlVideoConfigurationType_e    eConfigurationType;    ///< Specify which type of setting to get
} MmlVideoGetConfiguration_t;

/** @ingroup    MMLayerVideoRecording
    @brief      Start recording
*/
typedef struct
{
    MmlVideoVideoCodec_e        eEncoderId;     ///< Specify the supported video encoder
    MmlVideoFormat_e            eFormat;        ///< Output video format
    MmlVideoOutputType_e        eOutputType;    ///< Output destination type
    u16                         nWidth;         ///< Output frame width in pixels
    u16                         nHeight;        ///< Output frame height in pixels
    u16                         nQualityLevel;  ///< Compression level in 0-1000, 0: default, 1: best, 1000: worst (highest compression)
    u16                         bVideoOnly;     ///< Enable video only recording
    u16                         nFrameRate;     ///< Encoding frame rate in units of frames per second
    u32                         nBitRate;       ///< 0 is to use the default bitrate
    u32                         nTimeLimit;     ///< 32-bit value on the duration of total recorded content in milliseconds. 0 is no limit
    u32                         nSizeLimit;     ///< 32-bit value on the duration of total recorded content in bytes. 0 is no limit

    /// union of MmlVideoStartRecording_t parameters
    union
    {
        MmlVideoFileParam_t     tFileParam;     ///< Record to file-based destination
	    MmlVideoMemoryParam_t   tMemoryParam;   ///< Record to in-memory destination
    } uParam;
} MmlVideoStartRecording_t;

/** @ingroup    MMLayerVideoRecording
    @brief      Recording setting
*/
typedef struct MmlVideoRecordingSetting_t_
{
    MmlAudioEncoderId_e         eAudioEncoderId;     ///< Specify the supported audio encoder
    MmlAudioSamplingRate_e      eAudioSamplingRate;  ///< Sampling rate (hz)
    u32                         nAudioBitRate;       ///< 0 is to use the default bitrate
    MmlAudioChannelMode_e       eAudioChannelMode;   ///< Channel mode
    u32                         nTimeLimit;          ///< 32-bit value on the duration of total recorded content in milliseconds. 0 is no limit
    u32                         nSizeLimit;          ///< 32-bit value on the duration of total recorded content in bytes. 0 is no limit
} MmlVideoRecordingSetting_t;

/** @ingroup    MMLayerVideoRecording
    @brief      Set recording setting
*/
typedef struct
{
    MmlAudioEncoderId_e         eAudioEncoderId;     ///< Specify the supported audio encoder
    MmlAudioSamplingRate_e      eAudioSamplingRate;  ///< Sampling rate (hz)
    u32                         nAudioBitRate;       ///< 0 is to use the default bitrate
    MmlAudioChannelMode_e       eAudioChannelMode;   ///< Channel mode
    u16                         nMaxPreviewWidth;    ///< Maximum preview width
    u16                         nMaxPreviewHeight;   ///< Maximum preview height
} MmlVideoSetRecordingSetting_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Open video telephony
*/
typedef struct
{
    MmlVideoRotationAngle_e         eRemoteRotationAngle;       ///< Remote rotation (0, 90, 180, 270 degree)
    MmlVideoRotationAngle_e         eLocalRotationAngle;        ///< Local rotation (0, 90, 180, 270 degree)
    MmlVideoRectangle_t             tRemoteOutputWindow;        ///< Remote output window
    u16                             nRemoteOutputWindowPitch;   ///< Remote output window pitch
    MmlVideoRectangle_t             tLocalOutputWindow;         ///< Local output window
    u16                             nLocalOutputWindowPitch;    ///< Local output window pitch
} MmlVideoOpenVideoTelephony_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Remote telephony setting
*/
typedef struct
{
    MmlVideoVideoCodec_e            eEncoderId;     ///< Specify the supported video encoder
    MmlVideoTelephonyMuxFormat_e    eMuxFormat;     ///< MUX format
    u16                             nWidth;         ///< Output frame width in pixels
    u16                             nHeight;        ///< Output frame height in pixels
    u16                             nQualityLevel;  ///< Compression level in 0-1000, 0: default, 1: best, 1000: worst (highest compression)
    u16                             bVideoOnly;     ///< Enable video only muxing
    u16                             bAudioOnly;     ///< Enable audio only muxing
    u16                             nFrameRate;     ///< Encoding frame rate in units of frames per second
    u32                             nBitRate;       ///< 0 is to use the default bitrate
} MmlVideoTelephonyRemoteSetting_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Local telephony setting
*/
typedef struct
{
    MmlVideoInputType_e             eInputType;                 ///< Input source type
    u32                             nPosition;                  ///< 32-bit value expressed in milliseconds and relative to the beginning of the content
    u16                             bVideoOnly;                 ///< Enable video only playback
    u16                             bAudioOnly;                 ///< Enable audio only playback

    /// union of MmlVideoTelephonyLocalSetting_t parameters
    union
    {
	    MmlVideoFileParam_t         tFileParam;      ///< Image input from file-based source (Picture mode)
	    MmlVideoMemoryParam_t       tMemoryParam;    ///< Image input from in-memory source (Picture mode)
	    MmlCameraSensorSource_e     eSensorSource;   ///< Image input from camera sensor (Camera mode)
	} uInputParam;
} MmlVideoTelephonyLocalSetting_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Start video telephony
*/
typedef struct
{
    MmlVideoTelephonyLocalSetting_t     tLocalSetting;     ///< Local telephony setting
    MmlVideoTelephonyRemoteSetting_t    tRemoteSetting;    ///< Remote telephony setting
    MmlVideoTelephonyScreenMode_e       eScreenMode;       ///< Screen mode
} MmlVideoStartVideoTelephony_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Input source
*/
typedef struct
{
    MmlVideoInputType_e             eInputType;                 ///< Input source type

    /// union of MmlVideoTelephonyInputSource_t parameters
    union
    {
	    MmlVideoFileParam_t         tFileParam;      ///< Image input from file-based source (Picture mode)
	    MmlVideoMemoryParam_t       tMemoryParam;    ///< Image input from in-memory source (Picture mode)
	    MmlCameraSensorSource_e     eSensorSource;   ///< Image input from camera sensor (Camera mode)
	} uInputParam;
} MmlVideoTelephonyInputSource_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Remote picture
*/
typedef struct
{
    MmlVideoInputType_e             eInputType;      ///< Input source type
    u16                             bEnable;         ///< Enable remote picture mode

    /// union of MmlVideoTelephonyInputSource_t parameters
    union
    {
	    MmlVideoFileParam_t         tFileParam;      ///< Image input from file-based source (Picture mode)
	    MmlVideoMemoryParam_t       tMemoryParam;    ///< Image input from in-memory source (Picture mode)
	} uInputParam;
} MmlVideoTelephonyRemotePicture_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Blnak Preview
*/
typedef struct
{
    u16                             bEnable;         ///< Enable blank preview
} MmlVideoTelephonyBlankPreview_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Set video telephony setting
*/
typedef struct
{
    MmlVideoTelephonySettingType_e      eSettingType;      ///< Specify which type of setting to set

    /// union of MmlVideoSetVideoTelephonySetting_t parameters
    union
    {
        MmlCameraSetDigitalZoom_t           tSetDigitalZoom;   ///< Specify digital zoom level
        MmlVideoTelephonyScreenMode_e       eScreenMode;       ///< Screen mode
        MmlVideoTelephonyInputSource_t      tInputSource;      ///< Input source
        u16                                 nLevel;            ///< Brightness (0: black - 100: white)
                                                               ///< Contrast (0: maximum - 100: minimum)
        MmlVideoTelephonyRemotePicture_t    tRemotePicture;    ///< Remote picture
        MmlVideoTelephonyBlankPreview_t     tBlankPreview;     ///< Blank preview
	} uParam;
} MmlVideoSetVideoTelephonySetting_t;

/** @ingroup    MMLayerVideoTelephony
    @brief      Get video telephony setting
*/
typedef struct
{
    MmlVideoTelephonySettingType_e      eSettingType;      ///< Specify which type of setting to get
} MmlVideoGetVideoTelephonySetting_t;

#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_3GP                    ((u32) 0x00000001)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_MP4                    ((u32) 0x00000002)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_RM                     ((u32) 0x00000004)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_RMVB                   ((u32) 0x00000008)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_AVI                    ((u32) 0x00000010)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_FLV                    ((u32) 0x00000020)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_PS                     ((u32) 0x00000040)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_TS                     ((u32) 0x00000080)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_H324                   ((u32) 0x00000100)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_MPG                    ((u32) 0x00000200)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_VOB                    ((u32) 0x00000400)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_DAT                    ((u32) 0x00000800)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_DIVX                   ((u32) 0x00001000)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_MOV                    ((u32) 0x00002000)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_KMV                    ((u32) 0x00004000)
#define MML_VIDEOPLAYBACK_FORMAT_BITMASK_MKV                    ((u32) 0x00008000)
#define MML_VIDEOPLAYBACK_CHANNELMODE_BITMASK_MONO              ((u32) 0x00000001)
#define MML_VIDEOPLAYBACK_CHANNELMODE_BITMASK_STEREO            ((u32) 0x00000002)

/** @ingroup    MMLayerVideoPlayback
    @brief      Video playback capability
*/
typedef struct
{
    u32     nFormatSupported;     ///< Playback formats supported
    u16     nMaxFrameWidth;       ///< Maximum frame width in pixels
    u16     nMaxFrameHeight;      ///< Maximum frame height in pixels
    //u32     nMaxSamplingRate;     ///< Maximum sampling rate supported (Hz)
    //u32     nMinSamplingRate;     ///< Minimum sampling rate supported (Hz)
    //u32     nMaxAudioBitRate;     ///< Maximum audio bitrate supported (bps)
    //u32     nMinAudioBitRate;     ///< Minimum audio bitrate supported (bps)
    u32     nMaxVideoBitRate;     ///< Maximum video bitrate supported (bps)
    //u32     nMinVideoBitRate;     ///< Minimum video bitrate supported (bps)
    u32     nChannelMode;         ///< Channel modes supported
    u16     bA2dpSupported;       ///< A2DP supported
    u32     nImageStereoSupported;///< Image stereo supported bitmask
} MmlVideoPlaybackCapability_t;

/** @ingroup    MMLayerVideoPlayback
    @brief      Get playback capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlVideoGetPlaybackCapability_t;

#define MML_VIDEORECORDING_FORMAT_BITMASK_3GP                   ((u32) 0x00000001)
#define MML_VIDEORECORDING_FORMAT_BITMASK_MP4                   ((u32) 0x00000002)
#define MML_VIDEORECORDING_FORMAT_BITMASK_RM                    ((u32) 0x00000004)
#define MML_VIDEORECORDING_FORMAT_BITMASK_RMVB                  ((u32) 0x00000008)
#define MML_VIDEORECORDING_FORMAT_BITMASK_AVI                   ((u32) 0x00000010)
#define MML_VIDEORECORDING_FORMAT_BITMASK_FLV                   ((u32) 0x00000020)
#define MML_VIDEORECORDING_FORMAT_BITMASK_PS                    ((u32) 0x00000040)
#define MML_VIDEORECORDING_FORMAT_BITMASK_TS                    ((u32) 0x00000080)
#define MML_VIDEORECORDING_FORMAT_BITMASK_H324                  ((u32) 0x00000100)
#define MML_VIDEORECORDING_FORMAT_BITMASK_MPG                   ((u32) 0x00000200)
#define MML_VIDEORECORDING_FORMAT_BITMASK_VOB                   ((u32) 0x00000400)
#define MML_VIDEORECORDING_FORMAT_BITMASK_DAT                   ((u32) 0x00000800)
#define MML_VIDEORECORDING_FORMAT_BITMASK_DIVX                  ((u32) 0x00001000)
#define MML_VIDEORECORDING_FORMAT_BITMASK_MOV                   ((u32) 0x00002000)
#define MML_VIDEORECORDING_CHANNELMODE_BITMASK_MONO             ((u32) 0x00000001)
#define MML_VIDEORECORDING_CHANNELMODE_BITMASK_STEREO           ((u32) 0x00000002)
#define MML_VIDEORECORDING_AUDIOCODEC_BITMASK_AMR_NB            ((u32) 0x00000001)
#define MML_VIDEORECORDING_AUDIOCODEC_BITMASK_AMR_WB            ((u32) 0x00000002)
#define MML_VIDEORECORDING_AUDIOCODEC_BITMASK_AAC               ((u32) 0x00000004)
#define MML_VIDEORECORDING_AUDIOCODEC_BITMASK_WAV               ((u32) 0x00000008)
#define MML_VIDEORECORDING_AUDIOCODEC_BITMASK_MP3               ((u32) 0x00000010)
#define MML_VIDEORECORDING_VIDEOCODEC_BITMASK_H263              ((u32) 0x00000001)
#define MML_VIDEORECORDING_VIDEOCODEC_BITMASK_MPEG4             ((u32) 0x00000002)
#define MML_VIDEORECORDING_ASPECTRATIO_BITMASK_4_3              ((u32) 0x00000001)
#define MML_VIDEORECORDING_ASPECTRATIO_BITMASK_16_9             ((u32) 0x00000002)

/** @ingroup    MMLayerVideoRecording
    @brief      Video recording capability
*/
typedef struct
{
    u32     nFormatSupported;        ///< Recording formats supported
    u16     nMaxFrameRate;           ///< Maximum encoding frame rate supported (fps)
    u16     nMaxFrameWidth;          ///< Maximum frame width in pixels
    u16     nMaxFrameHeight;         ///< Maximum frame height in pixels
    u16     nMinFrameWidth;          ///< Minimum frame width in pixels
    u16     nMinFrameHeight;         ///< Minimum frame height in pixels
    u32     nMaxSamplingRate;        ///< Maximum sampling rate supported (Hz)
    u32     nMinSamplingRate;        ///< Minimum sampling rate supported (Hz)
    u32     nMaxBitRate;             ///< Maximum bitrate supported (bps)
    u32     nMinBitRate;             ///< Minimum bitrate supported (bps)
    u32     nChannelMode;            ///< Channel modes supported
    u32     nAudioCodecSupported;    ///< Audio codecs supported
    u32     nVideoCodecSupported;    ///< Video codecs supported
    u32     nAspectRatio;            ///< Aspect ratios supported
    u32     nMemoryRequirement;      ///< Memory requirement
} MmlVideoRecordingCapability_t;

/** @ingroup    MMLayerVideoRecording
    @brief      Get recording capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlVideoGetRecordingCapability_t;

/** @ingroup    MMLayerVideoRecording
    @brief      Start video telephony recording
*/
typedef struct
{
    MmlVideoOutputType_e        eOutputType;    ///< Output destination type

    /// union of MmlVideoStartVideoTelephonyRecording_t parameters
    union
    {
        MmlVideoFileParam_t     tFileParam;     ///< Record to file-based destination
	    MmlVideoMemoryParam_t   tMemoryParam;   ///< Record to in-memory destination
    } uParam;
} MmlVideoStartVideoTelephonyRecording_t;

/** @ingroup    MMLayerVideo
    @brief      Response payload
*/
typedef struct MmlVideoResponse_t_
{
    MmlVideoState_e         eState;       ///< Current state
    u32                     nHandle;      ///< 32-bit playback/recording handle

    /// union of MmlVideoResponse_t parameters
	union
	{
        u32                              nPosition;               ///< Used with 'Get playback position'
        MmlVideoInfo_t                   tVideoInfo;              ///< Used with 'Get video info'
        MmlVideoRecordingSetting_t       tRecordingSetting;       ///< Used with 'Get recording setting'
        MmlVideoStateChange_t            tStateChange;            ///< Used with 'VIDEO_ERROR_STATE_CHANGE' result
        MmlVideoBufferParam_t            tBufferParam;            ///< Used with 'Decode video thumbnail'
        u16                              nLevel;                  ///< Used with 'Get video telephony setting' (Brightness, Contrast)
        MmlVideoPlaybackCapability_t     tPlaybackCapability;     ///< Used with 'Get playback capability'
        MmlVideoRecordingCapability_t    tRecordingCapability;    ///< Used with 'Get recording capability'
        MmlVideoDisplayCalibration_t     tDisplayCalibration;     ///< Used with 'Get configuration'
    } uParam;
} MmlVideoResponse_t;

/** @ingroup    MMLayerVideo
    @brief      Video use case parameters
*/
typedef struct
{
	u32                                 nUseCaseID;             ///< Use case ID
	MmlVideoResponseCallback_t          *pResponseCallback;     ///< Pointer to the response callback registration data
	MmlVideoResponse_t                  *pResponse;             ///< Pointer to the response payload

    /// union of MmlVideoUCParam_t parameters
	union
	{
        /* No parameter: 'Get recording setting' */

        u32                                     nHandle;     ///< Used with 'Stop playback, Pause playback, Resume playback, Cancel seek,start playback with handle,Close playback
                                                             ///< Stop recording, Pause recording, Resume recording,
                                                             ///< Save recording file, Discard recording file, Get playback position,
                                                             ///< Abort saving, Open video telephony, Close video telephony,
                                                             ///< Stop video telephony, Stop video telephony recording,
															 ///< Save video telephony recording file, Discard video telephony recording file,
															 ///< Abort video telephony saving'

        MmlVideoOpenPlayback_t                     tOpenPlayback;                     ///< Used with 'Open playback'
	    MmlVideoStartPlayback_t                    tStartPlayback;                    ///< Used with 'Start playback'
        MmlVideoStartPlaybackWithHandle_t          tStartPlaybackWithHandle;          ///< Used with 'Start playback with handle'
	    MmlVideoRegNotifyCallback_t                tRegNotifyCallback;                ///< Used with 'Register notification callback'
	    MmlVideoStartRecording_t                   tStartRecording;                   ///< Used with 'Start recording'
	    MmlVideoSetPlaybackPosition_t              tSetPlaybackPosition;              ///< Used with 'Set playback position'
	    MmlVideoSetPlaybackSpeed_t                 tSetPlaybackSpeed;                 ///< Used with 'Set playback speed'
	    MmlVideoSetFullScreen_t                    tSetFullScreen;                    ///< Used with 'Set full screen'
        MmlVideoGetVideoInfo_t	                   tGetVideoInfo;                     ///< Used with 'Get video info'
	    MmlVideoSetRecordingSetting_t              tSetRecordingSetting;              ///< Used with 'Set recording setting'
        MmlVideoDecodeVideoThumbnail_t             tDecodeVideoThumbnail;             ///< Used with '(Sync/Async)Decode video thumbnail'
        MmlVideoOpenVideoTelephony_t               tOpenVideoTelephony;               ///< Used with 'Open video telephony'
        MmlVideoStartVideoTelephony_t              tStartVideoTelephony;              ///< Used with 'Start video telephony'
        MmlVideoSetVideoTelephonySetting_t         tSetVideoTelephonySetting;         ///< Used with 'Set video telephony setting'
        MmlVideoGetVideoTelephonySetting_t         tGetVideoTelephonySetting;         ///< Used with 'Get video telephony setting'
        MmlVideoGetPlaybackCapability_t            tGetPlaybackCapability;            ///< Used with 'Get playback capability'
        MmlVideoGetRecordingCapability_t           tGetRecordingCapability;           ///< Used with 'Get recording capability'
        MmlVideoStartVideoTelephonyRecording_t     tStartVideoTelephonyRecording;     ///< Used with 'Start video telephony recording'
        MmlVideoDecodeVideoThumbnailWithHandle_t   tDecodeVideoThumbnailWithHandle;   ///< Used with 'MML_UCID_VIDEO_DECODE_VIDEO_THUMBNAIL_WITH_HANDLE'
        MmlVideoGetVideoInfoWithHandle_t           tGetVideoInfoWithHandle;           ///< Used with 'MML_UCID_VIDEO_GET_VIDEO_INFO_WITH_HANDLE'
        MmlVideoSetConfiguration_t                 tSetConfiguration;                 ///< Used with 'MML_UCID_VIDEO_SET_CONFIGURATION'
        MmlVideoGetConfiguration_t                 tGetConfiguration;                 ///< Used with 'MML_UCID_VIDEO_GET_CONFIGURATION'
	} uParam;

} MmlVideoUCParam_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLVIDEO_TYPES_H__
