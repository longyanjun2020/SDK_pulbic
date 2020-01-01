/**
 *
 * @file    esl_vdo_itf.h
 *
 * @brief   This module defines Enchaced Service Layer interface of Video playback service
 *
 * @author  Jack Hsieh
 * @version $Id: esl_vdo_itf.h 15238 2008-10-16 09:40:41Z jack.hsieh $
 *
 */
#ifndef __ESL_VDO_ITF_H__
#define __ESL_VDO_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "MML_Video.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_VDO_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif
#define EMA_LEVEL_VDO            _CUS2 | LEVEL_8


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the ESL video playback error code
 */
typedef enum {
  ESL_VDO_OK,                 /**< Function complete successfully */
  ESL_VDO_FAIL,               /**< Function common fail */
  ESL_VDO_PARAM_ERROR,        /**< The input parameter is wrong */
  ESL_VDO_MEM_ALLOC_ERROR,    /**< Can not allocate memory from OS */
  ESL_VDO_LICENSE_MISMATCH,    /**< license mismatch */
  ESL_VDO_LICENSE_NOTEXIST,    /**< license does not exist */
  ESL_VDO_PASSWORD_MISMATCH,  /**< do not input correct password for the video file*/
  ESL_VDO_REJECT,             /**< Request rejected because of other function's confliction */
  ESL_VDO_ABORT,              /**< Request aborted because of incorrect sequence */
  ESL_VDO_TIMEOUT,            /**< Request no response timeout, this error is returned by call back function */
  ESL_VDO_FORMAT_NOT_SUPPORT  /**< Request video file format not support */
} esl_VdoErrCode_e;

/**
 *  @brief The enumeration defines the Video media format
 */
typedef enum {
  ESL_VDO_H263I,             /**< Format 3gp, h.263 I frame or H.262 + AAC */
  ESL_VDO_H263,              /**< Format 3gp, h.263 I+P frame or H.263 + AAC,AMR MP4V _AMR,AAC */
  ESL_VDO_H264,              /**< Format H.264 + AMR */
  ESL_VDO_IPTV,              /**< Format IPTV (used in video streaming) */
  ESL_VDO_MP4,               /**< Format MP4 */
  ESL_VDO_WMV,               /**< Format WMV */
  ESL_VDO_WAV_STREAMING,     /**< Format PCM streaming*/
  ESL_VDO_MEM,							 /**< Play from memory>*/
  ESL_VDO_MOVIEKING,         /**< Format Movie King */
  ESL_VDO_UNKNOW_FORMAT,     /**< Unknow video format */
} esl_VdoFormat_e;


/**
 *  @brief The enumeration defines the Video media format for play from norm
 */
typedef enum{
	ESL_VDO_MEM_3GP,           /**< Format 3GP */
	ESL_VDO_MEM_MP4,           /**< Format MP4 */
	ESL_VDO_MEM_RM,            /**< Format RM */
	ESL_VDO_MEM_AVI,           /**< Format AVI */
	ESL_VDO_MEM_MFS,           /**< Format MFS */
	ESL_VDO_MEM_TS,            /**< Format TS */
  ESL_VDO_MEM_FLV,           /**< Format FLV */
  ESL_VDO_MEM_UNKNOW_FORMAT
} esl_VdoMemFormat_e;

/**
 *  @brief The enumeration defines the video layer rotation angle
 */
typedef enum {
  ESL_VDO_ROTATE_NONE = 0,    /**< No Rotation */
  ESL_VDO_ROTATE_90,          /**< Rotate angle 90 degree */
  ESL_VDO_ROTATE_180,         /**< Rotate angle 180 degree */
  ESL_VDO_ROTATE_270,         /**< Rotate angle 270 degree */
  ESL_VDO_ROTATE_NUM
} esl_VdoRotateAngle_e;

/**
 *  @brief The enumeration defines the video playback command
 */
typedef enum {
  ESL_VDO_PAUSE = 0,          /**< Video play pause */
  ESL_VDO_RESUME,             /**< Video play resume */
  ESL_VDO_STOP,               /**< Video play stop */
  ESL_VDO_SEEK_CALCEL,        /**< Video seek cancel */
} esl_VdoPlayCmd_e;

/**
 *  @brief The enumeration defines the video playback speed configuration
 */
typedef enum {
  ESL_VDO_PLAY_SPEED_0_5X = 0,   /**< Playback speed = 0.5x */
  ESL_VDO_PLAY_SPEED_1X,         /**< Playback speed = 1x */
  ESL_VDO_PLAY_SPEED_2X,         /**< Playback speed = 2x */
  ESL_VDO_PLAY_SPEED_4X,         /**< Playback speed = 4x */
  ESL_VDO_PLAY_SPEED_8X,         /**< Playback speed = 8x */
} esl_VdoPlaySpeed_e;

/**
 *  @brief The enumeration defines type of the video notification.
 */
typedef enum {
  ESL_VDO_NOTIFY_PLAY_END = 0,              /**< Notify when video playing ended, only notified for playback auto stop */
  ESL_VDO_NOTIFY_PLAY_ERROR,                /**< Notify when video playing occurs error */
  ESL_VDO_NOTIFY_POSITION_UPDATE,           /**< Notify when video play position updated, MMP should update position per sec */
  ESL_VDO_NOTIFY_BITRATE_CHANGE,            /**< Notify when play bitrate changed */
  ESL_VDO_NOTIFY_IPTV_PACKAGE,              /**< Notify when IPTV notify package */
  ESL_VDO_NOTIFY_STREAMING_WRITEBUFFER,     /**< Notify for streaming (ex:IPTV) writing buffer */
  ESL_VDO_NOTIFY_ALL
} esl_VdoNotifyType_e;

/**
 *  @brief The enumeration defines type of the video playback error.
 */
typedef enum {
  ESL_VDO_ERROR_SEEK = 0,             /**< Video error type about seeking fail */
  ESL_VDO_ERROR_FILE,                 /**< Video error type about file action fail */
  ESL_VDO_ERROR_PLAY,                 /**< Video error type about video playing fail */
  ESL_VDO_ERROR_UNKNOWN,              /**< Video error type about unknown type */
  ESL_VDO_ERROR_FORMAT_NOT_SUPPORT,   /**< Video error type about format not support */
  ESL_VDO_ERROR_MEMORY_ALLOCATE_FAIL,
  ESL_VDO_ERROR_NONE                  /**< Video error type about no error */
} esl_VdoErrorType_e;

/**
 *  @brief The enumeration defines the "seekable" attribute of video file.
 */
typedef enum{
  ESL_VDO_UNSEEKABLE        = 0,   /**< specified video file is unseekable */
  ESL_VDO_SEEKABLE          = 1,   /**< specified video file is seekable */
  ESL_VDO_SEEK_TAKES_TIME   = 2,   /**< specified video file is seekable, but takes time */
} esl_VdoSeekable_e;

/**
 *  @brief The enumeration defines type of the video streaming command.
 */
typedef enum {
  ESL_VDO_STREAM_START = 0,    /**< Video stream command about starting streaming play */
  ESL_VDO_STREAM_BUFFERING,    /**< Video stream command about streaming buffering */
  ESL_VDO_STREAM_ADD_BUFFER,   /**< Video stream command about adding streaming data in playing video*/
  ESL_VDO_STREAM_STOP,         /**< Video stream command about stopping streaming play (currently not used, only reserved)*/
} esl_VdoStreamCmd_e;

/**
 *  @brief Video buffer information definition for first frame decode
 */
typedef struct  {
 u8   *pBuffer;                /**< Video decode buffer point*/
 u32   bufferLen;              /**< Video decode buffer length*/
} esl_VdoBufferInfo_t;


/**
 *  @brief Video streaming information
 */
typedef struct  {
 u16   data;                /**< Video streaming information for network usage*/
 u32   msmInfo;             /**< Video streaming information for network usage*/
} esl_VdoStreamInfo_t;


/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
typedef struct {
  esl_VdoNotifyType_e  notifyTyp;    /**< Type of video notification */
  union {
      esl_VdoErrorType_e   errorTyp;     /**< Video playback error type */
      u32                  position;     /**< Video playback updated position, only valid when notifyType = ESL_VDO_NOTIFY_POS_UPDATE */
      esl_VdoBufferInfo_t  bufferInfo;   /**< Video buffero info include buffer pointer and length */
      esl_VdoStreamInfo_t  streamInfo;   /**< Video streaming information */
  } param;
} esl_VdoNotifyInfo_t;

/**
 *  @brief The structure defines the window area property
 */
typedef struct {
  u16   posX;     /**< The origin (x=0) is top-left in rotate 0 (Horizontal), top-right in rotate 90 (Vertical)...etc*/
  u16   posY;     /**< The origin (y=0) is top-left in rotate 0 (Vertical), top-right in rotate 90 (Horizontal)...etc*/
  u16   width;    /**< Horizontal width */
  u16   height;   /**< Vertical height */
} esl_VdoRegion_t;

/**
 *  @brief The structure defines the video filename information
 */
typedef struct {
  esl_VdoFormat_e   fileFormat;       /**< Video file format */
  u16               *pFileName;       /**< Video file name in UCS2 format */
  u16               fileNameLen;      /**< Video file name length (UCS2)*/
  u32               *pExtInfo;     /**< Extended info for movie king*/
  u32               extInfoLen;
  u8                   bufferNumber;     /**< buffer number needed for M3 */
} esl_VdoFileInfo_t;


typedef struct{
	esl_VdoBufferInfo_t  inputBuffer;
	esl_VdoMemFormat_e   mediaFormat;
  u32                  *pExtInfo;    /**< Extended info for movie king*/
  u32                  extInfoLen;
} esl_VdoMemInfo_t;


typedef struct{
	esl_VdoBufferInfo_t  inputBuffer;
	esl_VdoMemFormat_e   mediaFormat;
  esl_VdoRotateAngle_e rotateAngle;      /**< Video rotation angle */
  esl_VdoRegion_t      playRegion;       /**< Video playback region */
  u8                   transLevel;       /**< Video playback OSD transparency level (0~255) 0: transparent 255: opaque*/
} esl_VdoMemParam_t;

/**
 *  @brief The structure defines the video media file parameter for playback operation
 */
typedef struct {
  esl_VdoFileInfo_t    fileInfo;         /**< Video filename information */
  esl_VdoRotateAngle_e rotateAngle;      /**< Video rotation angle */
  esl_VdoRegion_t      playRegion;       /**< Video playback region */
  u8                   transLevel;       /**< Video playback OSD transparency level (0~255) 0: transparent 255: opaque*/
} esl_VdoFileParam_t;

/**
 *  @brief The structure defines the video streaming playback information
 */
typedef	struct {
  esl_VdoFormat_e      format;           /**< Video streaming data format */
	esl_VdoStreamCmd_e   cmd;              /**< To indicate play streaming data command start, add buffer and (stop) */
  esl_VdoRotateAngle_e rotateAngle;      /**< Video rotation angle */
  esl_VdoRegion_t      playRegion;       /**< Video playback region */
	u8                  *pStreamData;      /**< Streaming data buffer pointer */
	u32                  dataLen;          /**< Total size of the streaming data buffer */
  u8                   transLevel;       /**< Video playback OSD transparency level (0~255) 0: transparent 255: opaque*/
	esl_VdoStreamInfo_t  streamInfo;       /**< Video streaming information for network usage*/
} esl_VdoStreamParam_t;

/**
 *  @brief The structure defines the video frame decoding parameter
 */
typedef struct {
  esl_VdoFileInfo_t    fileInfo;          /**< Video filename information */
  esl_VdoBufferInfo_t  decodeBufInfo;     /**< Video decode buffer info */
  esl_VdoRotateAngle_e rotateAngle;       /**< Video decode rotation angle */
  u16                  width;             /**< Video decode frame scale width (<= orignal frame width) */
  u16                  height;            /**< Video decode frame scale height (<= orignal frame height) */
} esl_VdoDecodeParam_t;

typedef struct {
  esl_VdoMemInfo_t     memInfo;           /**< Video buffer information */
  esl_VdoBufferInfo_t  decodeBufInfo;     /**< Video decode buffer info */
  esl_VdoRotateAngle_e rotateAngle;       /**< Video decode rotation angle */
  u16                  width;             /**< Video decode frame scale width (<= orignal frame width) */
  u16                  height;            /**< Video decode frame scale height (<= orignal frame height) */
} esl_VdoDecodeMemParam_t;

/**
 *  @brief The structure defines the video media file information
 */
typedef struct {
  u32                totalTime;   /**< Video play total time */
  u32                sampleRate;  /**< This media's audio sameple rate */
  u32                bitRate;     /**< This media's audio bit rate */
  u32                vdoBitRate;  /**< This media's Video bit rate */
  u8                 bufferNumber;/**< Buffer number needed */
  esl_VdoFormat_e    format;      /**< Video format */
  bool               stereo;      /**< stereo(true) or mono(false) */
  esl_VdoSeekable_e  seekable;    /**< Video seek availability*/
  esl_VdoPlaySpeed_e maxSpeed;    /**< Video playback support max speed */
  u16                height;      /**< Video resolution height */
  u16                width;       /**< Video resolution width */
} esl_VdoMediaInfo_t;


typedef MmlVideoPlaybackCapability_t    esl_VdoPlaybackCapability_t;

/**
 *  @brief The sturcture defines the return information of video media file
 */
typedef struct {
  union {
    u32                 position;       /**< Video current play position return */
    esl_VdoMediaInfo_t  mediaInfo;      /**< Video file detail information */
    esl_VdoBufferInfo_t decodeBuffInfo; /**< Video decode 1st frame buffer information response */
    esl_VdoPlaybackCapability_t tPlaybackCapability;
  } param;
} esl_VdoInfo_t;

/**
 *  @brief Notification function, Application needs to provide the function entry
 *
 * @param senderID      : Sender task id.
 * @param userValue      : Reference value for indicating different sender in same task or check msg response.
 * @param pVdoNotifyInfo : Notified information returned by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_VdoNotifyCb)(u16 senderID, u32 userValue, esl_VdoNotifyInfo_t *pVdoNotifyInfo);

/**
 *  @brief Call back function, Application needs to provide the function entry
 *
 * @param senderID       : Sender task id.
 * @param userValue      : Reference value for indicating different sender in same task or check msg response
 * @param errCode        : The error code return by Multimedia task to know process success or fail
 * @param pVdoInfo       : Callback information returned by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_VdoCb)(u16 senderID, u32 userValue, esl_VdoErrCode_e errCode, esl_VdoInfo_t *pVdoInfo);

/**
 *  @brief The video playback call back function structure definition
 */
typedef struct {
  u16           senderID;     /**< Task id of sender */
  u32           userValue;    /**< userValue of sender for checking msg response to realted applicatoin */
  esl_VdoCb     pfnCb;        /**< Done call back function that called by EMA */
} esl_VdoCb_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct{
  u16              senderID;   /**< Sender ID */
  u32              userValue;  /**< Reference value for indicating different sender in same task or check msg response. */
  esl_VdoNotifyCb  pfnNotifyCb;/**< Notification call back function that called by Media task after receiving the notification. */
} esl_VdoNotifyCb_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/**
 * @brief This function is used to play a video file
 *
 * @param  fileParam                    : Video media file parameter information
 * @param  position                     : Position to start video playback in milli-second
 * @param  pVdoCb                       : Video file playback call back function pointer
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoPlayFileReq(esl_VdoFileParam_t fileParam, u32 position, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to play a video file from memory
 *
 * @param  memParam                     : Video media parameter information
 * @param  position                     : Position to start video playback in milli-second
 * @param  pVdoCb                       : Video file playback call back function pointer
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoPlayMemReq(esl_VdoMemParam_t memParam, u32 position, esl_VdoCb_t *pVdoCb);


/**
 * @brief EMA video play stream (support H.263, H.264 and IPTV format)
 *
 * @param  pStreamParam                 : Streaming parameter pointer include data buffer, length, streaming command and some video play environment.
 * @param  pVdoCb 									    : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoPlayStreamReq(esl_VdoStreamParam_t *pStreamParam, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used set the video playback command
 *
 * @param  playCmd                      : Video play command
 * @param  pVdoCb                       : Video call back function pointer (It will return playback position in "STOP" command)
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoPlayCmdReq(esl_VdoPlayCmd_e playCmd, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to set the video playback speed
 *
 * @param  playSpeed                    : Video set speed
 * @param  pVdoCb                       : Video call back function pointer
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoSetPlaySpeedReq(esl_VdoPlaySpeed_e playSpeed, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to set position of video media file
 *
 * @param  position                     : Video set position in milli-second
 * @param  pVdoCb                       : Video call back structure pointer
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoSetPositionReq(u32 position, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to decode first frame of video media file
 *
 * @param  pDecodeParam                 : Video decode first frame parameter pointer
 * @param  pVdoCb                       : Video call back function pointer (It will return the decode information 'esl_VdoBufferInfo_t')
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoDecodeFirstFrameReq(esl_VdoDecodeParam_t *pDecodeParam, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to decode first frame of video media from memory
 *
 * @param  pDecodeParam                 : Video decode first frame parameter pointer
 * @param  pVdoCb                       : Video call back function pointer (It will return the decode information 'esl_VdoBufferInfo_t')
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoDecodeFirstFrameMemReq(esl_VdoDecodeMemParam_t *memParam	, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to reset video playing window
 *
 * @param  region                       : Video play resize region
 * @param  rotateAngle                  : Video resize rotate angle
 * @param  pVdoCb                       : Video call back structure pointer (It will return the media information 'esl_VdoMediaInfo_t')
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoResetWindowReq(esl_VdoRegion_t region,esl_VdoRotateAngle_e rotateAngle, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to get video file information (sample rate, bit rate, total play time, width and height)
 *
 * @param  fileInfo                     : Video filename information
 * @param  pVdoCb                       : Video call back structure pointer (It will return the media information 'esl_VdoMediaInfo_t')
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoGetFileInfoReq(esl_VdoFileInfo_t fileInfo, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to get video information from memory(sample rate, bit rate, total play time, width and height)
 *
 * @param  fileInfo                     : Video filename information
 * @param  pVdoCb                       : Video call back structure pointer (It will return the media information 'esl_VdoMediaInfo_t')
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoGetMemInfoReq(esl_VdoMemInfo_t inputBuffer,esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to register the Video function notification entry
 *
 * @param notifyType                    : Notification selected type to register
 * @param notifyCb                      : Notification call back to info MMI when Multimedia task receivd notification.
 * @param pVdoCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoRegNotifyReq(esl_VdoNotifyType_e notifyType, esl_VdoNotifyCb_t notifyCb, esl_VdoCb_t *pVdoCb);


/**
 * @brief This function is used to init before playing a video file (re-load firmware and set G0 geometry,
 *        MMI should update screen (load OSD) before play video)
 *
 * @param  pFileInfo                    : Video filename information pointer
 * @param  pVdoCb                       : Video file init call back function pointer
 *
 * @return ESL_VDO_OK                   : function request success
 * @return ESL_VDO_FAIL                 : function request fail
 * @return ESL_VDO_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_VDO_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_VDO_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_VDO_ABORT                : Request aborted becuase of incorrect sequence
 * @return ELS_VDO_PLAYBACK_ERROR       : Video plaback error
 * @return ESL_VDO_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_VdoErrCode_e esl_VdoPlayInitReq(esl_VdoFileInfo_t *pFileInfo, esl_VdoCb_t *pVdoCb);

#endif /* __ESL_VDO_ITF_H__ */

