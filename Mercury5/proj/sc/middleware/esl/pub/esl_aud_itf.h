/**
 *
 * @file    esl_aud_itf.h
 *
 * @brief   This module defines Enhanced Service Layer interface of Audio service
 *
 * @author  Roger Lai
 * @version $Id: esl_aud_itf.h 18000 2008-12-10 11:54:34Z ian-y.chen $
 *
 */
#ifndef __ESL_AUD_ITF_H__
#define __ESL_AUD_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "mdl_aud_types.h"
#include "vm_audio_api.h"
//#include "MML_Audio.h"
#include "srv_resmgr_mmlaudio_types.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_AUD_ITF__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


#define SONGNAME_LEN        62  /**< Character size of music ID3V1 'song name' */
#define ARTIST_LEN          62  /**< Character size of music ID3V1 'artist name' */
#define ALBUM_LEN           62  /**< Character size of music ID3V1 'album name' */
#define YEAR_LEN            62  /**< Character size of music ID3V1 'year' */
#define COMMENT_LEN         62  /**< Character size of music ID3V1 'comment' */
#define TRACK_LEN           62   /**< Character size of music ID3V1 'song track' */
#define GENRE_LEN           2   /**< Character size of music ID3V1 'genre' */

#define EMA_LEVEL_AUD            _CUS2 | LEVEL_7
#define VOC_DEBUG_LEVEL          _CUS8 | LEVEL_1

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the ESL audio error code
 */
typedef enum {
  ESL_AUD_OK,               /**< Function complete successfully */
  ESL_AUD_FAIL,             /**< Function fail */
  ESL_AUD_SKIP,             /**< Request skip */
  ESL_AUD_PARAM_ERROR,      /**< The input parameter is wrong */
  ESL_AUD_MEM_ALLOC_ERROR,  /**< Can not allocate available memory from OS */
  ESL_AUD_REJECT,           /**< Request reject because of other function's confliction */
  ESL_AUD_ABORT,            /**< Request abort because of incorrect sequence */
  ESL_AUD_PATH_ERROR,       /**< Incorret request of audio path with related audio function */
  ESL_AUD_TIMEOUT,           /**< Request command to MMP is no response */
  ESL_AUD_FORMAT_NOT_SUPPORT  /**< Request audio file format not support */
} esl_AudErrCode_e;


/**
 *  @brief The enumeration defines the ESL notify error code
 */
typedef enum {
  ESL_AUD_NOTIFY_ERR_UNKNOWN,
  ESL_AUD_NOTIFY_ERR_OUT_MEMORY,
  ESL_AUD_NOTIFY_ERR_FILE_DATA_FAIL,
  ESL_AUD_NOTIFY_ERR_FORMAT_NOT_SUPPORT,
  ESL_AUD_NOTIFY_ERR_SDCARD_NOT_DETECTED,
  ESL_AUD_NOTIFY_ERR_SDCARD_STOP_BY_FULLSPACE,
  ESL_AUD_NOTIFY_ERR_SDCARD_FULLSPACE,
  ESL_AUD_NOTIFY_ERR_NAND_STOP_BY_FULLSPACE,
  ESL_AUD_NOTIFY_ERR_NAND_FULLSPACE,
  ESL_AUD_NOTIFY_ERR_FORMAT_NOT_MATCH,
} esl_AudNotifyErr_e;

/**
 * @brief The enumeration defines the audio Input/Output path
 */
typedef enum {
  ESL_AUD_PATH_NONE = 0,      /**< No audio path select */
  ESL_AUD_PATH_HANDSET,       /**< Audio handset path (Micrphone + Receiver)  */
  ESL_AUD_PATH_HEADSET,       /**< Audio headset path (Headset output and Headset microphone input) */
  ESL_AUD_PATH_HANDSFREE,     /**< Audio handsfree path (Microphone + Speaker) */
  ESL_AUD_PATH_LINE_OUT,      /**< Audio Line out speaker path for media channel (Speaker only)*/
  ESL_AUD_PATH_LINE_LEFT_OUT, /**< Audio Line left out speaker path for media channel (Speaker only) */
  ESL_AUD_PATH_LINE_RIGHT_OUT,/**< Audio Line right out speaker path for media channel (Speaker only) */
  ESL_AUD_PATH_HEADPHONE_OUT, /**< Audio Line out headset path for media channel (Headset output only)*/
  ESL_AUD_PATH_BT_MONO,       /**< Audio Bluetooth mono path for voice channel */
  ESL_AUD_PATH_BT_STEREO,     /**< Audio Bluetooth stereo path for media channel */
  ESL_AUD_PATH_ALL_OUT,       /**< Audio all path (Receiver + Headset output + Speaker) */
} esl_AudPath_e;

/**
 * @brief The enumeration defines Audio channel
 */
typedef enum {
	ESL_AUD_VOICE_CHANNEL = 0,   /**< Voice channel for speech/DTMF (in/out, 8 kHz) */
	ESL_AUD_MUSIC_CHANNEL,       /**< Music channel for media playback/recording (in only, up to 48 kHz) */
	ESL_AUD_LINEIN_CHANNEL,      /**< Auxiliary line-in channel for FM Radio */
	ESL_AUD_VOICE_SLAVE_CHANNEL  /**< Voice channel for slave SIM */
} esl_AudChannel_e;

/**
 * @brief The enumeration defines Audio DTMF tone index
 */
typedef enum {
  ESL_AUD_DTMFTONE_0              = 0,  /**< Index '0' DTMF Tone */
  ESL_AUD_DTMFTONE_1              = 1,  /**< Index '1' DTMF Tone */
  ESL_AUD_DTMFTONE_2              = 2,  /**< Index '2' DTMF Tone */
  ESL_AUD_DTMFTONE_3              = 3,  /**< Index '3' DTMF Tone */
  ESL_AUD_DTMFTONE_4              = 4,  /**< Index '4' DTMF Tone */
  ESL_AUD_DTMFTONE_5              = 5,  /**< Index '5' DTMF Tone */
  ESL_AUD_DTMFTONE_6              = 6,  /**< Index '6' DTMF Tone */
  ESL_AUD_DTMFTONE_7              = 7,  /**< Index '7' DTMF Tone */
  ESL_AUD_DTMFTONE_8              = 8,  /**< Index '8' DTMF Tone */
  ESL_AUD_DTMFTONE_9              = 9,  /**< Index '9' DTMF Tone */
  ESL_AUD_DTMFTONE_A              = 10, /**< Index 'A' DTMF Tone */
  ESL_AUD_DTMFTONE_B              = 11, /**< Index 'B' DTMF Tone */
  ESL_AUD_DTMFTONE_C              = 12, /**< Index 'C' DTMF Tone */
  ESL_AUD_DTMFTONE_D              = 13, /**< Index 'D' DTMF Tone */
  ESL_AUD_DTMFTONE_STAR           = 14, /**< Index '*' DTMF Tone */
  ESL_AUD_DTMFTONE_HASH           = 15, /**< Index '#' DTMF Tone */
  ESL_AUD_DTMFTONE_BEEP1          = 16,
  ESL_AUD_DTMFTONE_BEEP2          = 17,
  ESL_AUD_DTMFTONE_WAITINGCALL    = 18,
  ESL_AUD_DTMFTONE_ACC_PLUG_IN    = 19,
  ESL_AUD_DTMFTONE_ACC_PLUG_OUT   = 20,
  ESL_AUD_DTMFTONE_OUTGOING       = 21,
  ESL_AUD_DTMFTONE_ALARM_CLOCK    = 22,
  ESL_AUD_DTMFTONE_CALL_END       = 23,
  ESL_AUD_DTMFTONE_MAX_NUM
} esl_AudDTMF_e;

/**
 *  @brief The enumeration defines the audio 3D effect ON/OFF features
 */
typedef enum {
	ESL_AUD_3D_DISABLE = 0,      /**< 3D effect disable */
	ESL_AUD_3D_NORMAL,       /**< 3D effect normal level enable */
	ESL_AUD_3D_HIGH          /**< 3D effect high level enable */
} esl_Aud3D_e;

/**
 *  @brief Audio Equalizer type definition. Currently, only "MP3" playback supports EQ-Type setting.
 */
typedef enum {
	ESL_AUD_EQ_0 = 0,    /**< NORMAL */
	ESL_AUD_EQ_1,    /**< FULL BASS */
	ESL_AUD_EQ_2,    /**< FULL TREBLE */
	ESL_AUD_EQ_3,    /**< CLASSIC */
	ESL_AUD_EQ_4,    /**< ROCK */
	ESL_AUD_EQ_5,            /**< LIVE */
	ESL_AUD_EQ_6,            /**< TV (treble/Bass) */
	ESL_AUD_EQ_MAX
} esl_AudEQ_e;


/**
 *  @brief Audio Speaker PEQ type definition.
 */
typedef enum {
	ESL_AUD_SPEAKER_PEQ_0 = 0,    /**< Speaker PEQ mode 0 (Power Off)*/
	ESL_AUD_SPEAKER_PEQ_1,    		/**< Speaker PEQ mode 1 (Earphone Path)*/
	ESL_AUD_SPEAKER_PEQ_2,    		/**< Speaker PEQ mode 2 (Speaker Path)*/
	ESL_AUD_SPEAKER_PEQ_3,    		/**< Speaker PEQ mode 3 (Bluetooth Path)*/
} esl_AudSpeakerPEQ_e;


/**
 *  @brief The enumeration defines the DRC limiter mode features
 */
typedef enum {
	ESL_AUD_DRC_LIMITER_0 = 0,      /**< DRC limiter mode 0 (Power Off)*/
	ESL_AUD_DRC_LIMITER_1,      /**< DRC limiter mode 1 (Earphone Path)*/
	ESL_AUD_DRC_LIMITER_2,      /**< DRC limiter mode 2 (Speaker Path)*/
	ESL_AUD_DRC_LIMITER_3,      /**< DRC limiter mode 3 (Bluetooth Path)*/
} esl_AudDRCLimiter_e;


/**
 *  @brief The structure defines the PEQ features
 */
typedef struct {
  esl_AudEQ_e eq;                   /**< User EQ type setting */
  esl_Aud3D_e threed;               /**< 3D effect setting */
  esl_AudSpeakerPEQ_e seq;          /**< Speaker PEQ mode setting */
  esl_AudDRCLimiter_e drc;          /**< DRC limiter disable/enable */
} esl_AudPEQ_t;

/**
 *  @brief The enumeration definesa audio configuration item
 */
typedef enum {
  ESL_AUD_EQ_TYPE,            /**< EQ type configutation*/
  ESL_AUD_3D_EFFECT,          /**< 3D effect configuration*/
  ESL_AUD_PEQ_SETTING         /**< PEQ configuration*/
} esl_AudConfigItem_e;

/**
 *  @brief The enumeration defines the audio playback command
 */
typedef enum {
  ESL_AUD_MUSIC_PAUSE,    /**< MMP audio play pause */
  ESL_AUD_MUSIC_RESUME,   /**< MMP audio play pause */
  ESL_AUD_MUSIC_STOP,     /**< MMP audio play pause */
  ESL_AUD_VOICE_PAUSE,    /**< DBB audio play pause */
  ESL_AUD_VOICE_RESUME,   /**< DBB audio play pause */
  ESL_AUD_VOICE_STOP      /**< DBB audio play pause */
} esl_AudPlayCmd_e;

/**
 *  @brief The enumeration defines the audio playback speed configuration
 */
typedef enum {
  ESL_AUD_PLAY_SPEED_0_5X = 0,   /**< Playback speed = 0.5x */
  ESL_AUD_PLAY_SPEED_1X,         /**< Playback speed = 1x */
  ESL_AUD_PLAY_SPEED_2X,         /**< Playback speed = 2x */
  ESL_AUD_PLAY_SPEED_4X          /**< Playback speed = 4x */
} esl_AudPlaySpeed_e;

/**
 *  @brief The enumeration defines string encoding scheme
 */
typedef enum {
	ESL_AUD_ISO_8859_1,
	ESL_AUD_UTF16,
	ESL_AUD_UTF16BE,
	ESL_AUD_UTF8
} esl_AudEncodeScheme_e;

/**
 *  @brief The enumeration defines type of the audio notification.
 */
typedef enum {
  ESL_AUD_NOTIFY_PLAY_END,                       /**< Notify when audio playing ended */
  ESL_AUD_NOTIFY_PLAY_ERROR,                     /**< Notify when audio playing occurs error */
  ESL_AUD_NOTIFY_PLAY_POSITION_UPDATE,           /**< Notify when play position updated */
  ESL_AUD_NOTIFY_PLAY_ADD_BUFFER_DONE,           /**< Notify when add buffer done */
  ESL_AUD_NOTIFY_PLAY_BITRATE_CHANGE,            /**< Notify when play bitrate changed */
  ESL_AUD_NOTIFY_PLAY_LYRICS_UPDATE,             /**< Notify when play lyrics updated */
  ESL_AUD_NOTIFY_PLAY_STREAM_DECODE_COMPLETE,    /**< Notify when stream decode complete */

  ESL_AUD_NOTIFY_REC_END,                        /**< Notify when audio recording end */
  ESL_AUD_NOTIFY_REC_SAPCE_FULL,                 /**< Notify when audio recording stops because of space fully */
  ESL_AUD_NOTIFY_REC_ERROR,                      /**< Notify when audio recording ocuurs error */
  ESL_AUD_NOTIFY_REC_POSITION_UPDATE,            /**< Notify when audio recording position updated */

  ESL_AUD_NOTIFY_PLAY_ALL,
  ESL_AUD_NOTIFY_REC_ALL,

  ESL_AUD_NOTIFY_GENERAL_UPDATE,

  ESL_AUD_NOTIFY_NB,

  ESL_AUD_NOTIFY_VOICE_BASE,
  ESL_AUD_NOTIFY_VOICE_PLAY_END = ESL_AUD_NOTIFY_VOICE_BASE, /* 12 */
  ESL_AUD_NOTIFY_VOICE_PLAY_ERROR,
  ESL_AUD_NOTIFY_VOICE_MAX
} esl_AudNotifyType_e;

/**
 *  @brief The structure defines the audio configuration information
 */
typedef struct {
  esl_AudConfigItem_e     cfgItem;
  union {
    esl_AudEQ_e           EQLevel;        /**< EQ type */
    esl_Aud3D_e           aud3D;          /**< 3D effect enable */
    esl_AudPEQ_t          audPEQ;         /**< PEQ parameter */
  } param;
} esl_AudMediaConfig_t;


/**
 *  @brief The structure defines the EQ band Magnitude setting
 */
typedef struct {
	s8	band1;							/**< Band 1 Magnitude +50~-50 */
	s8	band2;							/**< Band 2 Magnitude +50~-50 */
	s8	band3;							/**< Band 3 Magnitude +50~-50 (invalid for EQ6 type)*/
	s8	band4;							/**< Band 4 Magnitude +50~-50 (invalid for EQ6 type)*/
	s8	band5;							/**< Band 5 Magnitude +50~-50 (invalid for EQ6 type)*/
} esl_AudUserPEQConfig_t;

/**
 *  @brief AV file format
 */
typedef enum {
  ESL_AUD_WAVE = 0,          /**< Format wav */
  ESL_AUD_MIDI,              /**< Format MID */
  ESL_AUD_IMY,               /**< Format iMelody */
  ESL_AUD_MP3,               /**< Format MP3 */
  ESL_AUD_MP2,               /**< Format MP2 */
  ESL_AUD_MP1,               /**< Format MP1 */
  ESL_AUD_AAC,               /**< Format AAC */
  ESL_AUD_APE,               /**< Format APE */
  ESL_AUD_AMR,               /**< Format AMR NB*/
  ESL_AUD_AWB,               /**< Format AWB */
  ESL_AUD_RAM,               /**< Format RAM */
  ESL_AUD_ASF,               /**< Format ASF */
  ESL_AUD_WMA,               /**< Format WMA */
  ESL_AUD_WMV,               /**< Format WMV */
  ESL_AUD_MP4,               /**< Format MP4 */
  ESL_AUD_3GP,               /**< Format 3gp */
  ESL_AUD_WAVE_EXT,
  ESL_AUD_MIDI_EVENT,        /**< Format midi event for Java */
  ESL_AUD_PCM,               /**< Format PCM (no wave header)*/
  ESL_AUD_RA,
  ESL_AUD_RM,
  ESL_AUD_AVI,
  ESL_AUD_MFS,
  ESL_AUD_TS,
	ESL_AUD_M4A,
  ESL_AUD_RMVB,             /**< Format RMVB for audio of video stream */
  ESL_AUD_FLV,              /**< Format FLV for audio of video stream */
  ESL_AUD_PS,               /**< Format PS for audio of video stream */
  ESL_AUD_H324,             /**< Format H324 for audio of video stream */
  ESL_AUD_MPG,              /**< Format MPG for audio of video stream */
  ESL_AUD_VOB,              /**< Format VOB for audio of video stream */
  ESL_AUD_DAT,              /**< Format DAT for audio of video stream */
  ESL_AUD_DIVX,             /**< Format DIVX for audio of video stream */
  ESL_AUD_MOV,              /**< Format MOV for audio of video stream */
  ESL_AUD_KMV,              /**< Format KMV for audio of video stream */
  ESL_AUD_MKV,              /**< Format MKV for audio of video stream */
  ESL_AUD_UNKNOW_FORMAT
} esl_AudFormat_e;

/**
 *  @brief The structure defines the audio flile playback parameter
 */
typedef struct {
  esl_AudFormat_e fileFormat;  /**< Audio file format */
  u16   *pFileName;             /**< Audio file name in UCS2 format */
  u16 	fileNameLen;           /**< Audio file name length */
} esl_AudFileParam_t;

/**
 *  @brief Audio frequency
 */
typedef enum {
  ESL_AUDIO_8_KHZ = 0,   /**< 8 kHz */
  ESL_AUDIO_11_025_KHZ,  /**< 11.025 kHz */
  ESL_AUDIO_12_KHZ,      /**< 12 kHz */
  ESL_AUDIO_16_KHZ,      /**< 16 kHz */
  ESL_AUDIO_22_050_KHZ,  /**< 22.050 kHz */
  ESL_AUDIO_24_KHZ,      /**< 24 kHz */
  ESL_AUDIO_32_KHZ,      /**< 32 kHz */
  ESL_AUDIO_44_1_KHZ,    /**< 44.1 kHz */
  ESL_AUDIO_48_KHZ,      /**< 48 kHz */
  ESL_AUDIO_64_KHZ,      /**< 64 kHz */
  ESL_AUDIO_96_KHZ       /**< 96 kHz */
} esl_AudioFrequency_e;

/**
 *  @brief The structure defines the audio streaming playback information
 */
typedef	struct {
  esl_AudFormat_e format;    /**< Audio streaming data format */
  u8   mode;                     /**< To indicate data buffer start:0/streaming:1/end:2/start_end:3 */
  u8   *pStreamData;             /**< Streaming data buffer pointer */
  u32  dataLen;                  /**< Total size of the streaming data buffer */
  union	{
    struct {
      esl_AudioFrequency_e    sampleRate;     /**< sample rate */
      bool                    stereo;         /**< stereo(true) or mono(false) */
    } pcmParam;
    struct {
      esl_AudioFrequency_e    sampleRate;     /**< sample rate */
    } mp3Param;
  } param;
} esl_AudStreamParam_t;

/**
 *  @brief The structure defines the audio memory playback information
 */
typedef	struct {
  esl_AudFormat_e format;        /**< Audio streaming data format */
  u8   *pStreamData;             /**< Streaming data buffer pointer */
  u32  dataLen;                  /**< Total size of the streaming data buffer */
  u32  position;                 /**< position to start playing the streaming data buffer */
  bool isLoop;                   /**< Indicate playbck if loop */
} esl_AudMemoryParam_t;

/**
 * @brief The structure defines Audio DTMF tone setting
 */
typedef struct {
  esl_AudDTMF_e   toneId;        /**< DTMF tone id */
  u8              volRange;      /**< DTMF tone volume range */
  u8              volLevel;      /**< DTMF tone volume level */
} esl_AudDtmfParam_t;


typedef enum {
  ESL_AUD_GET_INFOLEN,           /**< To indicae getting advanced info len */
  ESL_AUD_GET_INFODATA           /**< To indicae getting advanced info data */
} esl_AudGetMode_e;


typedef	struct {
  u8   index;                   /**< To indicate the return information is LRC(0) or ID3V2(1) */
  u32  infoDataLen;             /**< Total size of the Advanced data buffer */
  u8   *pInfoData;              /**< Advanced data buffer */
} esl_AudAdvancedInfo_t;

/**
 *  @brief The enumeration defines the audio recording type, only AMR is supported currently
 */
typedef enum {
  ESL_AUD_REC_CODEC_AMR,              /**< AMR recording codec */
  ESL_AUD_REC_CODEC_AWB,              /**< AMR_WB recording codec */
  ESL_AUD_REC_CODEC_WAV_IMAADPCM4BIT, /**< WAV_IMAADPCM4BIT recording codec */
  ESL_AUD_REC_CODEC_WAV_IMAADPCM3BIT, /**< WAV_IMAADPCM3BIT recording codec */
  ESL_AUD_REC_CODEC_WAV_MSADPCM4BIT,  /**< WAV_MSADPCM4BIT recording codec */
  ESL_AUD_REC_CODEC_MP3,              /**< MP3 recording codec */
  ESL_AUD_REC_CODEC_AAC,              /**< AAC recording codec */
  ESL_AUD_REC_CODEC_PCM,              /**< PCM recording codec */
} esl_AudRecType_e;

/**
 *  @brief The enumeration defines the audio recording storage type
 */
typedef enum {
  ESL_AUD_REC_STORAGE_SD,       /**< Audio recording storage SD card */
  ESL_AUD_REC_STORAGE_MEMORY,   /**< Audio recording storage memory */
} esl_AudRecStorage_e;

/**
 *  @brief The enumeration defines the audio recording path type
 */
typedef enum {
  ESL_AUD_REC_PATH_DIR,         /**< Directory */
  ESL_AUD_REC_PATH_PREFIX,      /**< Prefix */
  ESL_AUD_REC_PATH_ABSOLUTE     /**< Absolute filename */
}esl_AudRecPath_e;


typedef enum {
  ESL_AUD_REC_APPEND_FIRST,     /**< 0: Append time from 0 */
  ESL_AUD_REC_APPEND_LAST_TIME, /**< 1: Append from last time */
}esl_AudRecAppendTimeMode_e;


/**
 *  @brief The enumeration defines the audio recording limitation setting
 */
typedef enum {
  ESL_AUD_REC_LIMIT_SPACE,  /**< space limit (byte) of audio recording */
  ESL_AUD_REC_LIMIT_TIME    /**< time limit (second) of audio recording */
} esl_AudRecLimitType_e;



/**
 *  @brief The enumeration defines the audio recording remain storage type
 */
typedef enum {
  ESL_AUD_REC_REMAIN_STORAGE_SD,      /**< SD Card */
  ESL_AUD_REC_REMAIN_STORAGE_NOR,     /**< NOR Flash */
  ESL_AUD_REC_REMAIN_STORAGE_NAND,    /**< NAND Flash */
}esl_AudRecRemainStorage_e;


/**
 *  @brief The enumeration defines the music playing mode
 */
typedef enum {
  ESL_AUD_MUSIC_TO_NE_WITHOUT_GSM_DL,         /**< Play music to near end */
  ESL_AUD_MUSIC_TO_NE_WITH_GSM_DL,            /**< Play music and GSM DL to near end */
  ESL_AUD_MUSIC_TO_FE_WITHOUT_ADC_UL,         /**< Play music to far end */
  ESL_AUD_MUSIC_TO_FE_WITH_ADC_UL,            /**< Play music and ADC UL to far end */
  ESL_AUD_MUSIC_TO_NE_FE_WITH_GSM_UL_ADC_DL,  /**< Play music to both near end and far end */
} esl_AudMusicMode_e;


/**
 *  @brief The enumeration defines the ID3 tag version
 */
typedef enum{
    ESL_ID3_VERSION_V1,
    ESL_ID3_VERSION_V2,
}esl_ID3Version_e;

/**
 *  @brief The structure defines the music playing mode
 */
typedef struct {
  esl_AudMusicMode_e  mode;
} esl_AudSetMusicModeParam_t;

/**
 *  @brief The sturcture defines the property of the audio recording.
 */
typedef struct {
  esl_AudRecType_e recType;   /**< to indicate audio record type, only AMR supported currently */
  esl_AudioFrequency_e    sampleRate; /**< To set audio record sample rate, only valid in MP3/AAC format */
  u32 bitRate;                /**< To set audio record bit rate, only valid in MP3/AAC format */
  esl_AudRecPath_e  pathType;         /**< Storage path type (0:Directory,2:Prefix,3:Absolute filename) */
  esl_AudRecAppendTimeMode_e timeMode;  /**< Record append time mode (0:Start from 0,1:Start from last time) */
  esl_AudRecStorage_e     storageMode;/**< Storage path mode (0:SD,1:Memory) */
  union {
    struct {
      u32 memorySize;                 /**< Storage memory size */
      u8  *pMemory;                   /**< Storage memory pointer */
    } memory;
  struct {
    u16 pathLen;                      /**< Storage path length */
    u16 *pPathName;                   /**< Storage path */
  } path;
  } storage;
  struct {
    esl_AudRecLimitType_e limitType;  /**< To indicate audio recording limit type including size limit and time limit */
    u32 limitSize;                    /**< To indicate limit size for space (byte) or time (second), '0' = No limitation */
  } limit;
} esl_AudRecParam_t;

/**
 *  @brief The sturcture defines the property of the audio remain time.
 */
typedef struct {
  esl_AudRecRemainStorage_e   remainStorageMode;  /**< To indicate audio remain storage type */
  esl_AudRecType_e recType;                       /**< to indicate audio record type, only AMR supported currently */
  esl_AudioFrequency_e    sampleRate;             /**< To set audio record sample rate, only valid in MP3/AAC format */
} esl_AudRecTimeParam_t;


typedef struct {
    u8 *pContent;
    u8 length;
    esl_AudEncodeScheme_e encode;
}esl_AudID3TextInfo_t;

typedef struct {
    u8 *pContent;
    u32 length;
}esl_AudID3PictureInfo_t;
/**
 *  @brief The structure defines the audio media ID3 information
 */
typedef struct {
    esl_ID3Version_e ID3Version;
    esl_AudID3TextInfo_t songName;
    esl_AudID3TextInfo_t artist;
    esl_AudID3TextInfo_t album;
    esl_AudID3TextInfo_t year;
    esl_AudID3TextInfo_t comment;
    esl_AudID3TextInfo_t track;
    esl_AudID3PictureInfo_t picture;
} esl_AudID3V1Info_t;

/**
 *  @brief The structure defines the audio media information
 */
typedef struct {
  u32               totalTime;      /**< total play time (unit: milliseconds) */
  u32               sampleRate;     /**< sample rate (unit: Hz) */
  u32               bitRate;        /**< bit rate (unit: bps) */
  bool              stereo;         /**< stereo(true) or mono(false) */
  MmlAudioFormat_e  eFormat;        /**< format enum defined in MML */
  u16               bAudioIsSeekable;  /** report seek capability*/
} esl_AudMediaInfo_t;

/**
    @brief      Audio playback capability
*/
typedef MmlAudioPlaybackCapability_t esl_AudioPlaybackCapability_t;
/**
    @brief      Audio recording capability
*/
typedef MmlAudioRecordingCapability_t esl_AudioRecordingCapability_t;

typedef struct {
    u32 addr;
    u32 size;
} esl_Audaddr_t;

/**
 *  @brief The sturcture defines the return information of audio media file information
 */
typedef struct {
    esl_AudRecStorage_e        storageMode;     /**< Storage path mode (0:SD,1:Memory) */
	union
    {
        u32                    position;        /**< audio playing time in milli-second */
        u32                    dataSize;        /**< audio lyrics buffer size or audio record size*/
        esl_Audaddr_t          PEQTableAddress; /**< PEQ table address*/
        u32                    recRemainTime;   /**< audio recording remain time */
        esl_AudID3V1Info_t	  *pID3Info;        /**< mp3 ID3V1 information pointer */
        esl_AudMediaInfo_t     mediaInfo;       /**< General audio file media information */
        esl_AudFileParam_t     fileInfo;        /**< File name buffer and length */
        MmlAudioBufferParam_t  tBufferParam;    /**< Memory info of the recorded stream */
        esl_AudAdvancedInfo_t *pAdvancedInfo;   /**< lyrics information pointer */
        esl_AudioPlaybackCapability_t	tAudioPlaybackCapability;	/**< audio playback capability */
        esl_AudioRecordingCapability_t tAudioRecordingCapability;	/**< audio recording capability */
        esl_Audaddr_t          pPreProcessTableAddress;            /**< audio get pre-process table address */
  } param;
} esl_AudInfo_t;

/**
 *  @brief Call back function, MMI need to provide the function entity
 *
 * @param senderID      : Sender task id.
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param errCode       : The error code return by Multimedia task to know process success or fail
 * @param pAudGetRsp    : Query data return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_AudCb)(u16 senderID, u32 userValue, esl_AudErrCode_e errCode, esl_AudInfo_t *pAudInfo);

/**
 *  @brief Esl call back function structure definition
 */
typedef struct {
  u16             senderID;        /**< Task id of sender */
  u32             userValue;       /**< userValue of sender for checking msg response */
  esl_AudCb       pfnCb;           /**< Call back function that called by Media task after process finished. */
} esl_AudCb_t;

/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
typedef struct {
    esl_AudNotifyType_e	  notifyType;  /**< Type of audio notification */
    union{
    esl_AudNotifyErr_e  notifyErr;     /**< audio error code for "ESL_AUD_NOTIFY_PLAY_ERROR" */
    u32 position;	                     /**< audio playback position for "ESL_AUD_NOTIFY_PLAY_POSITION_UPDATE"*/
    u32 bitrate;                       /**< audio decode bitrate for "ESL_AUD_NOTIFY_PLAY_STREAM_DECODE_COMPLETE"*/
    u32                 dataSize;      /**< audio record data length for "ESL_AUD_NOTIFY_REC_END" and "ESL_AUD_NOTIFY_REC_SAPCE_FULL"*/
    u32                 userData[2];   /**< audio user data for "ESL_AUD_NOTIFY_GENERAL_UPDATE"*/
    } notify;
} esl_AudNotifyInfo_t;

/**
 *  @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID      : Sender task id.
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pAudGetInfo   : Notification value return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_AudNotifyCb)(u16 senderID, u32 userValue, esl_AudNotifyInfo_t *pAudNotifyInfo);

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct{
	u16              senderID;       /**< Sender ID */
	u32              userValue;      /**< Reference value for indicating different sender in same task or check msg response. */
	esl_AudNotifyCb  pfnNotifyCb;    /**< Notification call back function that called by Media task after receiving the notification. */
} esl_AudNotifyCb_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct{
  esl_AudNotifyType_e notifyType; /**< Notification type */
  esl_AudNotifyCb_t   notifyCb;   /**< Notification callback */
} esl_AudRegNotify_t;

/**
 *  @brief The sturcture defines the audio config parameter
 */
typedef struct {
  esl_AudPath_e     audPath;      /**< Audio path */
  vm_AudioInput_e   input;        /**< input path */
  vm_AudioOutput_e  output;       /**< Output path */
  u8                volRange;     /**< Volume range */
  u8                volLevel;     /**< Volume level */
  s8                balanceRange; /**< Balance range */
  s8                balanceLevel; /**< Balance level */
  bool              inMute;       /**< Mute */
  bool              outputOn;     /**< Output on */
} esl_AudConfig_t;

/**
 *  @brief The sturcture defines the audio set mute parameter
 */
typedef struct {
  bool          bMute;  /**< Mute */
} esl_AudSetMute_t;

/**
 *  @brief The sturcture defines the audio set path parameter
 */
typedef struct {
  esl_AudChannel_e chanId;   /**< Channel id */
  esl_AudPath_e    audPath;  /**< Audio path */
} esl_AudSetPath_t;

/**
 *  @brief The sturcture defines the audio set volume parameter
 */
typedef struct {
  esl_AudChannel_e chanId;   /**< Channel id */
  u8               range;    /**< Volume range */
  u8               volume;   /**< Volume level */
} esl_AudSetVol_t;

/**
 *  @brief The sturcture defines the audio set balance parameter
 */
typedef struct {
  esl_AudChannel_e chanId;   /**< Channel id */
  s8               range;    /**< Balance range */
  s8               level;    /**< Balance level */
} esl_AudSetBalance_t;

/**
 *  @brief The sturcture defines the audio enable local tone parameter
 */
typedef struct {
  bool          bEnable;  /**< Enable */
} esl_AudEnableLocalTone_t;

/**
 *  @brief The sturcture defines the audio enable speech parameter
 */
typedef struct {
  bool          bEnable;  /**< Enable */
} esl_AudEnableSpeech_t;

/**
 * @brief Call back function, Application needs to provide the function entry
 *
 * @param pData         : PCM data
 * @param dataLen       : data length
 *
 * @return None
 */
typedef void (*esl_AudPcmRecordCb)(u16 *pData, u32 dataLen, u32 userData);

/**
 *  @brief The structure defines the PCM recording parameter
 */
typedef struct {
  esl_AudPcmRecordCb  *pfnCb;
  u32 userData;
} esl_AudRegPcmRecordCb_t;


#ifdef __BLUETOOTH_A2DP_DRV__
/**
 *  @brief The structure defines the A2DP callback structure
 */
typedef struct {
  esl_AudCb_t         playCb;               /**< A2DP play command callback */
  esl_AudCb_t         stopCb;               /**< A2DP stop command callback */
  esl_AudCb_t         pauseCb;              /**< A2DP pause command callback */
  esl_AudCb_t         resumeCb;             /**< A2DP resume command callback */
  esl_AudCb_t		  notifyUIUpdateCb;		      /**< A2DP indicate MMI for UI update notify callback */
  esl_AudRegNotify_t  playEndNotifyCb;      /**< A2DP play end notify callback */
  esl_AudRegNotify_t  playErrNotifyCb;      /**< A2DP play error notify callback */
  esl_AudRegNotify_t  postionUpdateNotifyCb;/**< A2DP postion update notify callback */
} esl_AudA2dpCb_t;
#endif

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __ESL_AUD_ITF_H__ */

