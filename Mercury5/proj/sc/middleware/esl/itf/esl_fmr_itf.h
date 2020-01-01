/**
 *
 * @file    esl_fmr_itf.h
 *
 * @brief   This interface defines FM radio service of Enhanced Service Layer
 *
 * @author  Roger Lai
 * @version $Id$
 *
 */
#ifndef __ESL_FMR_ITF_H__
#define __ESL_FMR_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "srv_ResMgr_MmlAudio_types.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_FMR_ITF__
#define	DefExtern
#else
#define	DefExtern	extern
#endif

#include "MML_Radio.h"
/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* CONSTANT DEFINITION                                                      */
/*--------------------------------------------------------------------------*/

#define     FMR_DEBUG_LEVEL            _CUS1 | LEVEL_10

/*--------------------------------------------------------------------------*/
/* MARCO DEFINITION                                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the error code of FM radio service
 */
typedef enum {
  ESL_FMR_OK,                 /**< Function complete successfully */
  ESL_FMR_FAIL,               /**< Function common fail */
  ESL_FMR_PARAM_ERROR,        /**< The input parameter is wrong */
  ESL_FMR_MEM_ALLOC_ERROR,    /**< Can not allocate memory from OS */
  ESL_FMR_REJECT,             /**< Request reject because of other function's confliction */
  ESL_FMR_ABORT,              /**< Request abort because of incorrect sequence */  
  ESL_FMR_SKIP,               /**< Request skip */
  ESL_FMR_PATH_ERROR,         /**< Incorret request of audio path with related audio function */  
  ESL_FMR_TIMEOUT,            /**< Request command to MMP is no response */
  ESL_FMR_FORMAT_NOT_SUPPORT  /**< Request audio file format not support */    
} esl_FmrErrCode_e;


/**
 *  @brief The enumeration defines the ESL notify error code
 */
typedef enum {
  ESL_FMR_NOTIFY_ERR_UNKNOWN,
  ESL_FMR_NOTIFY_ERR_OUT_MEMORY,
  ESL_FMR_NOTIFY_ERR_FILE_DATA_FAIL,
  ESL_FMR_NOTIFY_ERR_FORMAT_NOT_SUPPORT,
  ESL_FMR_NOTIFY_ERR_SDCARD_NOT_DETECTED,
  ESL_FMR_NOTIFY_ERR_FORMAT_NOT_MATCH,
} esl_FmrNotifyErr_e;


/**
 *  @brief The enumeration defines the frequency band of FM radio
 */
typedef enum {
  ESL_FMR_US_BAND,            /**< U.S. FM band */
  ESL_FMR_JAP_BAND            /**< JAPAN FM band */
} esl_FmrBand_e;


/**
 *  @brief The enumeration defines the area of FM radio
 */
typedef enum {
  ESL_FMR_DEEMPHASIS_50US = 0,
  ESL_FMR_DEEMPHASIS_75US,
  ESL_FMR_DEEMPHASIS_NUM
} esl_FmrDeEmphasis_e;

typedef enum {
  ESL_FMR_STEP_50KHZ = 0,
  ESL_FMR_STEP_100KHZ,
  ESL_FMR_STEP_200KHZ,
  ESL_FMR_STEP_30KHZ,    /* M3 not support yet */
  ESL_FMR_STEP_300KHZ,   /* M3 not support yet */
  ESL_FMR_STEP_NUM
} esl_FmrStepSpace_e;

typedef enum {
  ESL_FMR_BPFIR_100KHZ = 0,
  ESL_FMR_BPFIR_120KHZ,
  ESL_FMR_BPFIR_150KHZ,
  ESL_FMR_BPFIR_200KHZ,
  ESL_FMR_BPFIR_NUM
} esl_FmrBpfir_e;

typedef enum {
  ESL_FMR_BEGIN_66MHZ = 0, /* M3 not support yet */
  ESL_FMR_BEGIN_68MHZ,     /* M3 not support yet */
  ESL_FMR_BEGIN_73MHZ,     /* M3 not support yet */
  ESL_FMR_BEGIN_76MHZ,
  ESL_FMR_BEGIN_87_5MHZ,
  ESL_FMR_BEGIN_87_8MHZ,
  ESL_FMR_BEGIN_88MHZ,
  ESL_FMR_BEGIN_100MHZ,
  ESL_FMR_BEGIN_NUM
} esl_FmrBeginRange_e;

typedef enum {
  ESL_FMR_END_68MHZ = 0, /* M3 not support yet */
  ESL_FMR_END_73MHZ,     /* M3 not support yet */
  ESL_FMR_END_74MHZ,     /* M3 not support yet */
  ESL_FMR_END_87_5MHZ,
  ESL_FMR_END_90MHZ,
  ESL_FMR_END_100MHZ,
  ESL_FMR_END_108MHZ,
  ESL_FMR_END_NUM
} esl_FmrEndRange_e;

typedef struct {
  esl_FmrDeEmphasis_e    FmrDeEmphasis;
  esl_FmrStepSpace_e     FmrStepSpace;
  esl_FmrBpfir_e         FmrBpfir;
  esl_FmrBeginRange_e    FmrBeginRange;
  esl_FmrEndRange_e      FmrEndRange;
} esl_FmrAreaConfig_t;


typedef enum {
  ESL_FMR_SET_POWER,        /**< Command to set FM radio power on/off */  
  ESL_FMR_SET_BAND,         /**< Command to set FM radio channel band */
  ESL_FMR_SET_FREQUENCY,    /**< Command to set FM radio channel frequency */
  ESL_FMR_SET_MUTE,         /**< Command to set FM radio mute on/off */ 
  ESL_FMR_SET_SEARCH,       /**< Command to search FM radio channel */  
  ESL_FMR_GET_INFO          /**< Command to get FM radio channel information */  
} esl_FmrCmd_e;

typedef struct {
   u32   freq;              /**< channel frequency */
   u16   signal;            /**< Signal strength of current channel */
   u8    stereo;            /**< Stereo/Mono status of current channel */
} esl_FmrChanInfo_t;

typedef struct {
  u8  version;
  u16 manufactrId;
  u16 chipId;
} esl_FmrChipInfo_t;



/**
 *  @brief The enumeration defines type of the FMR recording notification.
 */
typedef enum {
  ESL_FMR_NOTIFY_REC_END,                        /**< Notify when audio recording end */
  ESL_FMR_NOTIFY_REC_SPACE_FULL,                 /**< Notify when audio recording stops because of space fully */
  ESL_FMR_NOTIFY_REC_ERROR,                      /**< Notify when audio recording ocuurs error */
  ESL_FMR_NOTIFY_REC_POSITION_UPDATE,            /**< Notify when audio recording position updated */

  ESL_FMR_NOTIFY_REC_ALL,
  ESL_FMR_NOTIFY_NB
} esl_FmrNotifyType_e;

/**
 *  @brief AV file format
 */
typedef enum {
  ESL_FMR_WAVE = 0,          /**< Format wav */ 
  ESL_FMR_MIDI,              /**< Format MID */ 
  ESL_FMR_IMY,               /**< Format iMelody */
  ESL_FMR_MP3,               /**< Format MP3 */
  ESL_FMR_MP2,               /**< Format MP2 */ 
  ESL_FMR_MP1,               /**< Format MP1 */ 
  ESL_FMR_AAC,               /**< Format AAC */ 
  ESL_FMR_AMR,               /**< Format AMR */
  ESL_FMR_AWB,               /**< Format AWB */
  ESL_FMR_RAM,               /**< Format RAM */
  ESL_FMR_WMA,               /**< Format WMA */ 
  ESL_FMR_WMV,               /**< Format WMV */ 
  ESL_FMR_MP4,               /**< Format MP4 */  
  ESL_FMR_3GP,               /**< Format 3gp */
  ESL_FMR_WAVE_EXT,
  ESL_FMR_MIDI_EVENT,        /**< Format midi event for Java */
  ESL_FMR_PCM,               /**< Format PCM (no wave header)*/              
  ESL_FMR_UNKNOW_FORMAT
} esl_FmrFormat_e;

/**
 *  @brief The structure defines the audio file playback parameter
 */
typedef struct {
  esl_FmrFormat_e fileFormat;  /**< Audio file format */
  u16   *pFileName;            /**< Audio file name in UCS2 format */
  u16 	fileNameLen;           /**< Audio file name length */
} esl_FmrFileParam_t;



typedef MmlRadioCapability_t esl_FmrCapability_t;

/**
 *  @brief The sturcture defines the return information of video media file
 */
typedef struct {  
  u16  typMsg;    /**< FMR Command ID */
  
  union {
    esl_FmrCapability_t capability;
    esl_FmrChipInfo_t chipInfo;
    esl_FmrChanInfo_t chanInfo;
    u32 dataSize;                     /**< FMR record size*/
    esl_FmrFileParam_t fileInfo;      /**< File name buffer and length */
  } info;
} esl_FmrInfo_t;

/**
 *  @brief The enumeration defines the FMR recording type, only AMR is supported currently
 */
typedef enum {
  ESL_FMR_REC_CODEC_AMR_NB,                 /**< AMR NB recording codec */
  ESL_FMR_REC_CODEC_AMR_WB,                 /**< AMR WB recording codec */
  ESL_FMR_REC_CODEC_WAV_IMAADPCM4BIT,       /**< WAV IMAADPCM4BIT recording codec */
  ESL_FMR_REC_CODEC_WAV_IMAADPCM3BIT,       /**< WAV IMAADPCM3BIT recording codec */
  ESL_FMR_REC_CODEC_MP3,                    /**< MP3 recording codec */
  ESL_FMR_REC_CODEC_AAC,                    /**< AAC recording codec */
  ESL_FMR_REC_CODEC_NUM
} esl_FmrRecType_e;

/**
 *  @brief The enumeration defines the FM recording storage type
 */
typedef enum {
  ESL_FMR_REC_STORAGE_SD,       /**< FM recording storage SD card */
  ESL_FMR_REC_STORAGE_MEMORY,   /**< FM recording storage memory */
} esl_FmrRecStorage_e;

/**
 *  @brief The enumeration defines the FM recording path type
 */
typedef enum {
  ESL_FMR_REC_PATH_DIR,         /**< Directory */
  ESL_FMR_REC_PATH_PREFIX,      /**< Prefix */
  ESL_FMR_REC_PATH_ABSOLUTE,    /**< Absolute filename */
  ESL_FMR_REC_PATH_NUM
}esl_FmrRecPath_e;

/**
 *  @brief Fmr audio recording frequency
 */
typedef enum {
  ESL_FMR_8_KHZ = 0,   /**< 8 kHz */
  ESL_FMR_11_025_KHZ,  /**< 11.025 kHz */
  ESL_FMR_12_KHZ,      /**< 12 kHz */
  ESL_FMR_16_KHZ,      /**< 16 kHz */
  ESL_FMR_22_050_KHZ,  /**< 22.050 kHz */
  ESL_FMR_24_KHZ,      /**< 24 kHz */
  ESL_FMR_32_KHZ,      /**< 32 kHz */
  ESL_FMR_44_1_KHZ,    /**< 44.1 kHz */
  ESL_FMR_48_KHZ,      /**< 48 kHz */
  ESL_FMR_64_KHZ,      /**< 64 kHz */
  ESL_FMR_96_KHZ       /**< 96 kHz */
} esl_FmrAudioRecFrequency_e;

/**
 *  @brief The enumeration defines the Fmr recording limitation setting
 */
typedef enum {
  ESL_FMR_REC_LIMIT_SPACE,  /**< space limit (byte) of FMR recording */
  ESL_FMR_REC_LIMIT_TIME,   /**< time limit (second) of FMR recording */
  ESL_FMR_REC_LIMIT_NUM
} esl_FmrRecLimitType_e;

typedef enum {
  ESL_FMR_REC_APPEND_FIRST,     /**< 0: Append time from 0 */
  ESL_FMR_REC_APPEND_LAST_TIME, /**< 1: Append from last time */
  ESL_FMR_REC_APPEND_NUM
}esl_FmrRecAppendTimeMode_e;

/**
 *  @brief The sturcture defines the property of the FMR recording.
 */
typedef struct {
  esl_FmrRecType_e              recType;    /**< to indicate FMR record type, only AMR supported currently */
  esl_FmrAudioRecFrequency_e    sampleRate; /**< To set FMR record sample rate, only valid in MP3/AAC format */
  u32                           bitRate;    /**< To set FMR record bit rate, only valid in MP3/AAC format */
  esl_FmrRecPath_e  pathType;         /**< Storage path type (0:Directory,2:Prefix,3:Absolute filename) */
  esl_FmrRecAppendTimeMode_e timeMode;  /**< Record append time mode (0:Start from 0,1:Start from last time) */
  esl_FmrRecStorage_e     storageMode;/**< Storage path mode (0:SD,1:Memory) */ 
  union {
    struct {
      u16 memorySize;                 /**< Storage memory size */
      u8  *pMemory;                   /**< Storage memory pointer */
    } memory;   
    struct {
      u16 pathLen;                      /**< Storage path length */
      u16 *pPathName;                   /**< Storage path */
    } path; 
  } storage;
  struct {
    esl_FmrRecLimitType_e  limitType;  /**< To indicate FMR recording limit type including size limit and time limit */
    u32                    limitSize;  /**< To indicate limit size for space (byte) or time (second), '0' = No limitation */
  } limit;
  MmlAudioInputType_e InputPath;
} esl_FmrRecParam_t;


/**
 *  @brief Call back function, Application needs to provide the function entry 
 *
 * @param senderID       : Sender task ID
 * @param userValue      : Reference value for indicating different sender in same task or check msg response
 * @param errCode        : The error code return by FM radio task to know process success or fail 
 * @param pFmrInfo       : Callback information returned by FM radio task
 *
 * @return None
 */
typedef void (*esl_FmrCb)(u16 senderID, u32 userValue, esl_FmrErrCode_e errCode, esl_FmrInfo_t *pFmrInfo);

/**
 *  @brief FM Radio ESL call back structure definition
 */
typedef struct {
	u16           senderID;     /**< Task id of sender */	   
	u32	          userValue;		/**< Value of sender customized usage */
  esl_FmrCb	    pfnCb;				/**< Call back function that called by FMR task after process finished */
} esl_FmrCb_t;



/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
typedef struct {
  esl_FmrNotifyType_e   notifyType;    /**< Type of audio notification */
  union{
    esl_FmrNotifyErr_e  notifyErr;     /**< Fmr error code for "ESL_FMR_NOTIFY_PLAY_ERROR" */
    u32                 position;      /**< Fmr playback position for "ESL_FMR_NOTIFY_PLAY_POSITION_UPDATE"*/       
    u32                 bitrate;       /**< Fmr decode bitrate for "ESL_FMR_NOTIFY_PLAY_STREAM_DECODE_COMPLETE"*/   
    u32                 dataSize;      /**< Fmr record data length for "ESL_FMR_NOTIFY_REC_END" and "ESL_AUD_NOTIFY_REC_SAPCE_FULL"*/   
    u32                 frequency;
  } notify; 
} esl_FmrNotifyInfo_t;

/**
 *  @brief Notification Call back function, MMI need to provide the function entity 
 *
 * @param senderID      : Sender task id. 
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pAudGetInfo   : Notification value return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_FmrNotifyCb)(u16 senderID, u32 userValue, esl_FmrNotifyInfo_t *pFmrNotifyInfo);

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct{
	u16              senderID;       /**< Sender ID */	   
	u32              userValue;      /**< Reference value for indicating different sender in same task or check msg response. */
	esl_FmrNotifyCb  pfnNotifyCb;    /**< Notification call back function that called by Media task after receiving the notification. */
} esl_FmrNotifyCb_t;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/** 
 * @brief This function is used to power ON/OFF FM radio
 *   
 * @param  on                           : Power ON/OFF (1/0 = on/off)
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrPowerOnOff(bool on, esl_FmrCb_t *pFmrCb);


/** 
 * @brief This function is used to set the band configuration	
 *
 * @param  band                         : FM radio band setting (USA/Europe or Japan)
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrSetBand(esl_FmrBand_e band, esl_FmrCb_t *pFmrCb);


/** 
 * @brief This function is used to set FM channel to specified frequency	
 *   
 * @param  freq                         : Frequency 87.5~108 (MHz)
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrSetFrequency(u32 freq, esl_FmrCb_t *pFmrCb);


/** 
 * @brief This function is used to set FM radio mute
 *   
 * @param  mute                         : Mute or Un-mute FM radio (1/0 = mute/unmute)
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrSetMute(bool mute, esl_FmrCb_t *pFmrCb);


/** 
 * @brief This function is used to set FM radio stereo
 *   
 * @param  stereo                       : Stereo or forced mono (1/0 = on/off)
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrSetStereo(bool stereo, esl_FmrCb_t *pFmrCb);


/** 
 * @brief This function is used to search radio station		
 *   
 * @param  on                           : On or Off channel search (1/0 = on/off)
 * @param  direction                    : Search up or search down (1/0 = up/down)
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrSearchChannel(bool on, bool direction, esl_FmrCb_t *pFmrCb);


/** 
 * @brief This function is used to get FM radio channel information	
 *   
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrGetChanInfo(esl_FmrCb_t *pFmrCb);



/** 
 * @brief This function is used to set the FM area configuration	
 *
 * @param  area                         : FM radio area setting (0: Taiwan, 1: China)
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrSetArea(esl_FmrAreaConfig_t areaConfig, esl_FmrCb_t *pFmrCb);


/** 
 * @brief This function is used to set the FM carrier lock threshold.	
 *
 * @param  CarrierOn                    : FM radio carrier lock threshold (default: 0x20). 
                                          If set the value low, it will lock the channel with higher strength.
 * @param  CarrierOff                   : FM radio carrier unlock threshold (default: 0x40). 
                                          If set the value higher, it will unlock the channel with lower quality.
 * @param  pFmrCb                       : FM radio call back function pointer
 *
 * @return ESL_FMR_OK                   : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 */
esl_FmrErrCode_e esl_FmrSetCarrierThreshold(u8 carrierOn, u8 carrierOff, esl_FmrCb_t *pFmrCb);


/** 
 * @brief Register notification for FMR recording 
 *  
 * @param notifyType                    : Notification selected type to register
 * @param notifyCb      : Notification call back to info MMI when Multimedia task receivd notification.
 * @param pFmrCb  	         : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_FMR_OK       				    : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_FMR_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_FMR_ABORT                : Request aborted becuase of incorrect sequence 
 */
esl_FmrErrCode_e esl_FmrRegNotifyReq(esl_FmrNotifyType_e notifyType, esl_FmrNotifyCb_t notifyCb, esl_FmrCb_t *pFmrCb);

/** 
 * @brief This function is used for FMR recording, only AMR is supported currently
 *   
 * @param  recParam                     : Property setting - codec type, sample rate, bitrate and storage path
 * @param  pFmrCb	                      : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_FMR_OK       				    : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_FMR_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_FMR_ABORT                : Request aborted becuase of incorrect sequence 
 */
esl_FmrErrCode_e esl_FmrRecStartReq(esl_FmrRecParam_t recParam, esl_FmrCb_t *pFmrCb);

/** 
 * @brief This function is used terminate FMR recording function
 *   
 * @param  pFmrCb	          : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_FMR_OK       				    : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_FMR_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_FMR_ABORT                : Request aborted becuase of incorrect sequence 
 */
esl_FmrErrCode_e esl_FmrRecStopReq(esl_FmrCb_t *pFmrCb);

/** 
 * @brief This function is used to get FMR recorded audio file name
 *   
 * @param  fileParam        : The structure defines the audio file playback parameter.
 * @param  pFmrCb	          : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_FMR_OK       				    : function request success
 * @return ESL_FMR_FAIL                 : function request fail
 * @return ESL_FMR_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_FMR_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_FMR_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_FMR_ABORT                : Request aborted becuase of incorrect sequence 
 */
esl_FmrErrCode_e esl_FmrRecGetFileReq(esl_FmrFileParam_t fileParam, esl_FmrCb_t *pFmrCb);



#endif /* __ESL_FMR_ITF_H__ */

