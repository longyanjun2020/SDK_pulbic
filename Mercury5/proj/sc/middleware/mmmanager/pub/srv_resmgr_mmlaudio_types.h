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
* @file    srv_resmgr_mmlaudio_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLAUDIO_TYPES_H__
#define __SRV_RESMGR_MMLAUDIO_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/** @defgroup MMLayerAudio Audio
    Audio Playback and Recording
    @{
*/
    /** @defgroup MMLayerAudioPlayback Audio Playback
        Audio Playback
        @{
    */
    /** @} */

    /** @defgroup MMLayerAudioRecording Audio Recording
        Audio Recording
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

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerAudio
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseAudioId_e_)
{
    /* Audio Init */
    MML_UCID_AUDIO_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_AUDIO),
    MML_UCID_AUDIO_REG_NOTIFY_CALLBACK = MML_UCID_AUDIO_INIT_BASE,              ///< 00010000 = Reg notify callback
    MML_UCID_AUDIO_UNREG_NOTIFY_CALLBACK,                                       ///< 00010001 = Unreg notify callback
    MML_UCID_AUDIO_INIT_CATEGORY,

    /* Audio Get */
    MML_UCID_AUDIO_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_AUDIO),
    MML_UCID_AUDIO_GET_POSTPROC_SETTING = MML_UCID_AUDIO_GET_BASE,              ///< 00010100 = Get post-proc setting
    MML_UCID_AUDIO_GET_MP3_ID3_TAG,                                             ///< 00010101 = Get mp3 ID3 tag
    MML_UCID_AUDIO_GET_MUSIC_LYRICS,                                            ///< 00010102 = Get music lyrics
    MML_UCID_AUDIO_GET_AUDIO_INFO,                                              ///< 00010103 = Get audio info
    MML_UCID_AUDIO_GET_PLAYBACK_POSITION,                                       ///< 00010104 = Get playback position
    MML_UCID_AUDIO_GET_RECORDING_SETTING,                                       ///< 00010105 = Get recording setting
    MML_UCID_AUDIO_GET_RECORDING_INFO,                                          ///< 00010106 = Get recording info
    MML_UCID_AUDIO_GET_CONFIGURATION,                                           ///< 00010107 = Get configuration
    MML_UCID_AUDIO_GET_PLAYBACK_CAPABILITY,                                     ///< 00010108 = Get playback capability
    MML_UCID_AUDIO_GET_RECORDING_CAPABILITY,                                    ///< 00010109 = Get recording capability
    MML_UCID_AUDIO_GET_CATEGORY,

    /* Audio Set */
    MML_UCID_AUDIO_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_AUDIO),
    MML_UCID_AUDIO_SET_POSTPROC_SETTING = MML_UCID_AUDIO_SET_BASE,              ///< 00010200 = Set post-proc setting
    MML_UCID_AUDIO_UPDATE_POSTPROC_SETTING,                                     ///< 00010201 = Update post-proc setting
    MML_UCID_AUDIO_SET_MP3_ID3_TAG,                                             ///< 00010202 = Set mp3 ID3 tag
    MML_UCID_AUDIO_SET_CONFIGURATION,                                           ///< 00010203 = Set configuration
    MML_UCID_AUDIO_SET_PLAYBACK_SPEED,                                          ///< 00010204 = Set playback speed
    MML_UCID_AUDIO_SET_PLAYBACK_POSITION,                                       ///< 00010205 = Set playback position
    MML_UCID_AUDIO_SET_RECORDING_SETTING,                                       ///< 00010206 = Set recording setting
    MML_UCID_AUDIO_SET_PREPROC_SETTING,                                         ///< 00010207 = Set pre-proc setting
    MML_UCID_AUDIO_SET_CATEGORY,

    /* Audio Execute */
    MML_UCID_AUDIO_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_AUDIO),
    MML_UCID_AUDIO_START_PLAYBACK = MML_UCID_AUDIO_EXECUTE_BASE,                ///< 00010300 = Start playback
    MML_UCID_AUDIO_STOP_PLAYBACK,                                               ///< 00010301 = Stop playback
    MML_UCID_AUDIO_PAUSE_PLAYBACK,                                              ///< 00010302 = Pause playback
    MML_UCID_AUDIO_RESUME_PLAYBACK,                                             ///< 00010303 = Resume playback
    MML_UCID_AUDIO_CANCEL_SEEK,                                                 ///< 00010304 = Cancel seek

    MML_UCID_AUDIO_START_RECORDING,                                             ///< 00010305 = Start recording
    MML_UCID_AUDIO_STOP_RECORDING,                                              ///< 00010306 = Stop recording
    MML_UCID_AUDIO_PAUSE_RECORDING,                                             ///< 00010307 = Pause recording
    MML_UCID_AUDIO_RESUME_RECORDING,                                            ///< 00010308 = Resume recording
    MML_UCID_AUDIO_SAVE_RECORDING_FILE,                                         ///< 00010309 = Save recording file
    MML_UCID_AUDIO_DISCARD_RECORDING_FILE,                                      ///< 0001030a = Discard recording file
    MML_UCID_AUDIO_ABORT_SAVING,                                                ///< 0001030b = Abort saving
    MML_UCID_AUDIO_PLAY_TONE,                                                   ///< 0001030c = Play tone
    MML_UCID_AUDIO_EXECUTE_CATEGORY,


    /* Force ID to be at least 32-bits */
    MML_UCID_AUDIO_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerAudio
    @brief      Response results
*/
typedef enum
{
    /* Common */
    AUDIO_ERROR_SUCCESS = 0,
    AUDIO_ERROR_FAIL,
    AUDIO_ERROR_PARAMETER_INVALID,
    AUDIO_ERROR_STATE_CHANGE,
    AUDIO_ERROR_ACCEPT,
    AUDIO_ERROR_IGNORE,
    AUDIO_ERROR_REJECT,
    AUDIO_ERROR_MEMORY_FAILURE,
    AUDIO_ERROR_FORMAT_NOT_SUPPORT,

    /* Audio Playback */
    AUDIO_ERROR_STREAMING_UNDERRUN,
    AUDIO_ERROR_MAP_PLAYERR,
    AUDIO_ERROR_MAP_SEEKERR,
    AUDIO_ERROR_MAP_PLAYERR_BLUETOOTH,
    AUDIO_ERROR_PLAYBACK_STOP_FAIL,
    /* Audio Recording */
    AUDIO_ERROR_DISK_FULL,
    AUDIO_ERROR_WRITE_ERROR,
    AUDIO_ERORR_MAR_PUSH_BUF_ERROR,
    AUDIO_ERROR_SDCARD_NOT_DETECTED,
    AUDIO_ERROR_CREATE_FILE_ERR,
    AUDIO_ERROR_ENCODER_ERROR,
    AUDIO_ERROR_SRC_PROC_FAIL,
    AUDIO_ERROR_MEM_ALLOC_FAIL,
    AUDIO_ERROR_AUD_ERR,
    AUDIO_ERROR_RECORDING_STOP_FAIL,
    /* */
    AUDIO_ERROR_NUM
} MmlAudioResult_e;

/** @ingroup    MMLayerAudio
    @brief      States
*/
typedef enum
{
    /* Audio Playback */
    AUDIO_STATE_PLAYBACK_STOPPED = 0,
    AUDIO_STATE_PLAYBACK_PLAYING,
    AUDIO_STATE_PLAYBACK_PAUSED,
    AUDIO_STATE_PLAYBACK_SEEKING,
    AUDIO_STATE_PLAYBACK_MAP_PAUSE_TRAN,
    AUDIO_STATE_PLAYBACK_MAP_RESUME_TRAN,
    AUDIO_STATE_PLAYBACK_MAP_STOP_TRAN,
    AUDIO_STATE_PLAYBACK_READ_PAUSE_TRAN,
    AUDIO_STATE_PLAYBACK_READ_RESUME_TRAN,
    AUDIO_STATE_PLAYBACK_READ_STOP_TRAN,
    AUDIO_STATE_PLAYBACK_MAP_SEEK_TRAN,
    AUDIO_STATE_PLAYBACK_MAP_SEEKCANCEL_TRAN,
    AUDIO_STATE_PLAYBACK_READ_PLAYEND_TRAN,
    AUDIO_STATE_PLAYBACK_READ_PLAYERR_TRAN,
    AUDIO_STATE_PLAYBACK_READ_SEEKERR_TRAN,
    AUDIO_STATE_PLAYBACK_PLAYING_TRAN,
    AUDIO_STATE_PLAYBACK_MAP_READERR_TRAN,
    /* Audio Recording */
    AUDIO_STATE_RECORDING_STOPPED,
    AUDIO_STATE_RECORDING_RECORDING,
    AUDIO_STATE_RECORDING_PAUSED,
    AUDIO_STATE_RECORDING_SAVING,
    AUDIO_STATE_RECORDING_STOP_TRAN,
    AUDIO_STATE_RECORDING_RECORD_TRAN,
    AUDIO_STATE_RECORDING_PAUSE_TRAN,
    AUDIO_STATE_RECORDING_SAVING_TRAN,
    AUDIO_STATE_RECORDING_ERROR_TRAN,
    /* */
    AUDIO_STATE_DONTCARE,
    AUDIO_STATE_NUM
} MmlAudioState_e;

/** @ingroup    MMLayerAudio
    @brief      Events
*/
typedef enum
{
    /* Common */
    AUDIO_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_AUDIO),
    AUDIO_EVENT_RUNTIME_ERROR,
    AUDIO_EVENT_POSITION_UPDATE,
    /* Audio Playback */
    AUDIO_EVENT_PLAYBACK_STATE_CHANGE,
    AUDIO_EVENT_PLAYBACK_RUNTIME_ERROR,
    AUDIO_EVENT_PLAYBACK_POSITION_UPDATE,
    AUDIO_EVENT_PLAYBACK_TOTALPLAYTIME_UPDATE,
    AUDIO_EVENT_SEEK_COMPLETE,
    AUDIO_EVENT_SEEK_CANCELED,
    AUDIO_EVENT_SEEK_ERROR,
    AUDIO_EVENT_PLAYBACK_END,
    AUDIO_EVENT_PLAYBACK_STREAM_UNDERRUN,
    /* Audio Playback - BT handshaking */
    AUDIO_EVENT_PLAYBACK_HANDSHAKING_MASTER_AUDIO,     // audio invoke and BT listening
    AUDIO_EVENT_PLAYBACK_HANDSHAKING_MASTER_BLUETOOTH, // BT invoke and audio listening
    /* Audio Recording */
    AUDIO_EVENT_RECORDING_STATE_CHANGE,
    AUDIO_EVENT_RECORDING_RUNTIME_ERROR,
	AUDIO_EVENT_RECORDING_POSITION_UPDATE,
    AUDIO_EVENT_SAVE_FILE_COMPLETE,
    AUDIO_EVENT_RECORD_FILE_DISCARDED,
    AUDIO_EVENT_SAVE_FILE_ABORTED,
    AUDIO_EVENT_REACH_TIME_LIMIT,
    AUDIO_EVENT_REACH_SIZE_LIMIT,
    AUDIO_EVENT_WRITE_ERROR,
    AUDIO_EVENT_SAVE_MEMORY_COMPLETE,
    /* */
    AUDIO_EVENT_DONTCARE,
    AUDIO_EVENT_ALL,
    AUDIO_EVENT_NUM
} MmlAudioEvent_e;

/** @ingroup    MMLayerAudio
    @brief      Input source types
*/
typedef enum
{
    /* Audio Playback */
    AUDIO_INPUT_FILE = 0,    ///< Playback from file-based source
    AUDIO_INPUT_MEMORY,      ///< Playback from in-memory source
    AUDIO_INPUT_STREAMING,   ///< Playback from streaming source
    /* Audio Recording */
    AUDIO_INPUT_IIS,         ///< Record from IIS
    AUDIO_INPUT_FM,          ///< Record from FMRx
    AUDIO_INPUT_SPDIF,       ///< Record from SPDIF
    AUDIO_INPUT_FM_ATV,      ///< Record from FMRx (built in ATV)
    /* */
    AUDIO_INPUT_NUM
} MmlAudioInputType_e;

/** @ingroup    MMLayerAudio
    @brief      Output destination types
*/
typedef enum
{
    /* Audio Recording */
    AUDIO_OUTPUT_FILE = 0,    ///< Record to file-based destination
    AUDIO_OUTPUT_MEMORY,      ///< Record to in-memory destination
    AUDIO_OUTPUT_STREAMING,   ///< Record to streaming destination
    AUDIO_OUTPUT_CALLBACK,    ///< Record to callback-based destination
    /* Audio Playback */
    AUDIO_OUTPUT_IIS,         ///< Decode (playback) to IIS
    AUDIO_OUTPUT_A2DP,        ///< Decode (playback) to A2DP
    /* */
    AUDIO_OUTPUT_NUM
} MmlAudioOutputType_e;

/** @ingroup    MMLayerAudio
    @brief      Storage types
*/
typedef enum
{
    AUDIO_STORAGETYPE_CARD = 0,    ///< SD Card
    AUDIO_STORAGETYPE_CARD2,       ///< SD Card 2
    AUDIO_STORAGETYPE_NORFLASH,    ///< Nor flash
    AUDIO_STORAGETYPE_NANDFLASH,   ///< Nand flash
    /* */
    AUDIO_STORAGETYPE_NUM
} MmlAudioStorageType_e;

/** @ingroup    MMLayerAudio
    @brief      Audio formats
*/
typedef enum
{
    AUDIO_FORMAT_WAVE = 0,          /* WAV */
    AUDIO_FORMAT_MIDI,              /* MIDI */
    AUDIO_FORMAT_IMY,               /* IMELODY */
    AUDIO_FORMAT_MP3,               /* MP3 */
    AUDIO_FORMAT_AAC,               /* AAC */
    AUDIO_FORMAT_AMR,               /* AMR */
    AUDIO_FORMAT_AWB,               /* AWB */
    AUDIO_FORMAT_RAM,               /* RAM */
    AUDIO_FORMAT_WMA,               /* WMA */
    AUDIO_FORMAT_WMV,               /* WMV */
    AUDIO_FORMAT_MP4,               /* MP4 */
    AUDIO_FORMAT_3GP,               /* 3GP */
    AUDIO_FORMAT_WAVE_EXT,
    AUDIO_FORMAT_MIDI_EVENT,        /* MIDI event for JAVA */
    AUDIO_FORMAT_PCM,               /* PCM (no wave header) */
    AUDIO_FORMAT_COOK,              /* COOK */
    AUDIO_FORMAT_APE,               /* APE */
    AUDIO_FORMAT_M4A,               /* M4A */
    AUDIO_FORMAT_ASF,               /* ASF */
    /* audio of video stream*/
    AUDIO_FORMAT_RM,                /* RM */
    AUDIO_FORMAT_RMVB,              /* RMVB */
    AUDIO_FORMAT_AVI,               /* AVI */
    AUDIO_FORMAT_FLV,               /* FLV */
    AUDIO_FORMAT_PS,                /* PS */
    AUDIO_FORMAT_TS,                /* TS */
    AUDIO_FORMAT_H324,              /* H324 (video telephony) */
    AUDIO_FORMAT_MPG,               /* MPG/MPEG */
    AUDIO_FORMAT_VOB,               /* VOB */
    AUDIO_FORMAT_DAT,               /* DAT */
    AUDIO_FORMAT_DIVX,              /* DIVX */
    AUDIO_FORMAT_MOV,               /* MOV */
    AUDIO_FORMAT_KMV,               /* KMV */
    AUDIO_FORMAT_MKV,               /* MKV */
    AUDIO_FORMAT_DONTCARE,
    AUDIO_FORMAT_NUM
} MmlAudioFormat_e;

/** @ingroup    MMLayerAudio
    @brief      Audio codecs
*/
typedef enum MmlAudioAudioCodec_e_
{
    AUDIO_AUDIOCODEC_WAVE = 0,          /* WAV */
    AUDIO_AUDIOCODEC_MIDI,              /* MIDI */
    AUDIO_AUDIOCODEC_IMY,               /* IMELODY */
    AUDIO_AUDIOCODEC_MP3,               /* MP3 */
    AUDIO_AUDIOCODEC_AAC,               /* AAC */
    AUDIO_AUDIOCODEC_AMR,               /* AMR */
    AUDIO_AUDIOCODEC_AWB,               /* AWB */
    AUDIO_AUDIOCODEC_RAM,               /* RAM */
    AUDIO_AUDIOCODEC_WMA,               /* WMA */
    AUDIO_AUDIOCODEC_WMV,               /* WMV */
    AUDIO_AUDIOCODEC_MP4,               /* MP4 */
    AUDIO_AUDIOCODEC_3GP,               /* 3GP */
    AUDIO_AUDIOCODEC_WAVE_EXT,
    AUDIO_AUDIOCODEC_MIDI_EVENT,        /* MIDI event for JAVA */
    AUDIO_AUDIOCODEC_PCM,               /* PCM (no wave header) */
    AUDIO_AUDIOCODEC_COOK,              /* COOK */
    AUDIO_AUDIOCODEC_APE,               /* APE */
    AUDIO_AUDIOCODEC_M4A,               /* M4A */
    AUDIO_AUDIOCODEC_DONTCARE,
    /* */
    AUDIO_AUDIOCODEC_NUM,
    AUDIO_AUDIOCODEC_UNSUPPORTED        /* Unsupported codec */
} MmlAudioAudioCodec_e;

/** @ingroup    MMLayerAudio
    @brief      Sampling rates
*/
typedef enum MmlAudioSamplingRate_e_
{
    AUDIO_SAMPLING_RATE_8000 = 0,
    AUDIO_SAMPLING_RATE_11025,
    AUDIO_SAMPLING_RATE_12000,
    AUDIO_SAMPLING_RATE_16000,
    AUDIO_SAMPLING_RATE_22050,
    AUDIO_SAMPLING_RATE_24000,
    AUDIO_SAMPLING_RATE_32000,
    AUDIO_SAMPLING_RATE_44100,
    AUDIO_SAMPLING_RATE_48000,
    AUDIO_SAMPLING_RATE_64000,
    AUDIO_SAMPLING_RATE_96000,
    AUDIO_SAMPLING_RATE_UNSUPPORT  // To be removed, ck.wang@20100409
} MmlAudioSamplingRate_e;

/** @ingroup    MMLayerAudio
    @brief      Channel modes
*/
typedef enum MmlAudioChannelMode_e_
{
    AUDIO_CHANNEL_MODE_MONO = 0,
    AUDIO_CHANNEL_MODE_STEREO
} MmlAudioChannelMode_e;

/** @ingroup    MMLayerAudio
    @brief      Bits per sample
*/
typedef enum MmlAudioBitsPerSample_e_
{
    AUDIO_BITSPERSAMPLE_8 = 0,
    AUDIO_BITSPERSAMPLE_16,
    AUDIO_BITSPERSAMPLE_24,
    AUDIO_BITSPERSAMPLE_32
} MmlAudioBitsPerSample_e;
/** @ingroup    MMLayerAudio
    @brief      Bitrate types
*/
typedef enum
{
    AUDIO_BITRATETYPE_CBR = 0,    ///< Constant bitrate
    AUDIO_BITRATETYPE_VBR         ///< Variable bitrate
} MmlAudioBitRateType_e;

/** @ingroup    MMLayerAudio
    @brief      Configuration types
*/
typedef enum
{
    AUDIO_CONFIGURATIONTYPE_VOLUMECONTROL = 0,       ///< Volume control
    AUDIO_CONFIGURATIONTYPE_VOLUMEBALANCE,           ///< Volume balance
    AUDIO_CONFIGURATIONTYPE_BLUETOOTH,               ///< Bluetooth (A2DP)
    AUDIO_CONFIGURATIONTYPE_3DEFFECT_USEREQ,         ///< 3D effect + User EQ
    AUDIO_CONFIGURATIONTYPE_PARAMETRICEQ,            ///< Parametric EQ
    AUDIO_CONFIGURATIONTYPE_DRCLIMIT,                ///< DRC limit
    AUDIO_CONFIGURATIONTYPE_POSTPROCALL,             ///< Select post-processing effects, device type, and media type
    AUDIO_CONFIGURATIONTYPE_APPENGINE_CALIBRATION,   ///< Audio post-processing engine calibration
    AUDIO_CONFIGURATIONTYPE_PREPROCALL,        		 ///< Select device type
	AUDIO_CONFIGURATIONTYPE_ARPENGINE_CALIBRATION,   ///< Audio pre-processing engine calibration
	AUDIO_CONFIGURATIONTYPE_POSTPROCEFFECT,          ///< Select post-processing effects
    AUDIO_CONFIGURATIONTYPE_POSTPROCDEVICETYPE,      ///< Select post-processing device type
    AUDIO_CONFIGURATIONTYPE_POSTPROCMEDIATYPE        ///< Select post-processing media type

} MmlAudioConfigurationType_e;

/** @ingroup    MMLayerAudio
    @brief      Media parameters
*/
typedef struct
{
    u16                       bIsValid;
    MmlAudioSamplingRate_e    eSamplingRate;
    MmlAudioBitsPerSample_e   eBitsPerSample;
    MmlAudioChannelMode_e     eChannelMode;
} MmlAudioMediaParam_t;

/** @ingroup    MMLayerAudio
    @brief      File-based source/destination
*/
typedef struct
{
    MmlAudioFormat_e          eFormat;
    MmlFilenameFormat_e       eFilenameFormat;
    MmlFileOperatingMode_e    eFileOperatingMode;
    u16                       *pFileName;
    u16  	                  nFileNameSize;
    u16                       bRepeat;
} MmlAudioFileParam_t;

/** @ingroup    MMLayerAudio
    @brief      In-memory source/destination
*/
typedef	struct
{
    MmlAudioFormat_e    eFormat;
    u8                  *pBuffer;
    u32                 nBufferSize;
    u16                 bRepeat;
} MmlAudioMemoryParam_t;

/** @ingroup    MMLayerAudio
    @brief      Streaming source/destination
*/
typedef struct
{
    MmlAudioFormat_e    eFormat;                   ///< Audio stream format
    u32                 nHandle;                   ///< 32-bit ring buffer handle, used for streaming
    u32                 nAvailableStreamThreshold; ///< Available stream threshold expressed in milliseconds
} MmlAudioStreamingParam_t;


/** @ingroup    MMLayerAudio
    @brief      Data callback prototype\n
                User can register the callback function to process the data
    @param      pData         Pointer to the data
    @param      nDataSize     Size in bytes of the data
    @param      nUserData     Interface self-reference
*/
typedef void (*PfnMmlAudioDataCallback)(u16 *pData, u32 nDataSize, u32 nUserData);

/** @ingroup    MMLayerAudio
    @brief      Callback-based destination
*/
typedef struct
{
    u32                             nSizeLimit;         ///< Callback function invoked when reaching the size limit, in bytes.
    u32                             nUserData;          ///< Interface self-reference
    PfnMmlAudioDataCallback         pfnDataCallback;    ///< Callback function you want to register
} MmlAudioCallbackParam_t;

/** @ingroup    MMLayerAudio
    @brief      A block of memory, used to hold input/output data
*/
typedef	struct
{
    u8                  *pBuffer;       ///< Pointer to the data buffer
    u32                 nBufferSize;    ///< Size in bytes of the data buffer
    u32                 nDataSize;      ///< Read/Write size in bytes of data in the data buffer
} MmlAudioBufferParam_t;

/** @ingroup    MMLayerAudio
    @brief      Audio info
*/
typedef struct
{
    MmlAudioFormat_e                eFormat;           ///< Format
    MmlAudioSamplingRate_e          eSamplingRate;     ///< Sampling rate (Hz) To be removed, ck.wang @ 20100409
    u32                             nSamplingRate;     ///< Sampling rate (Hz)
    MmlAudioChannelMode_e           eChannelMode;      ///< Channel mode
    MmlAudioBitRateType_e           eBitRateType;      ///< Bitrate type
    u32                             nBitRate;          ///< 32-bit bitrate in units of bps
    u32                             nTotalPlayTime;    ///< 32-bit total play time expressed in milliseconds
    u16     			            bAudioIsSeekable;  ///< TRUE for seekable audio
} MmlAudioInfo_t;

/** @ingroup    MMLayerAudio
    @brief      State change info
*/
typedef	struct
{
    MmlAudioState_e            eState;        ///< The new state after the transition
    MmlAudioEvent_e	           eCause;        ///< The cause of state change, if any

    /// union of MmlAudioStateChange_t parameters
    union
    {
   	    MmlAudioFileParam_t    tFileParam;    ///< Filename of the saved file
        MmlAudioBufferParam_t  tBufferParam;  ///< Memory info of the recorded stream
   	    u32                    nPosition;     ///< The last playback position returned from 'Stop playback'
    } uParam;
} MmlAudioStateChange_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Bluetooth handshaking causes
*/
typedef enum
{
    AUDIO_BLUETOOTH_HANDSHAKING_ENCODE_START = 0,
    AUDIO_BLUETOOTH_HANDSHAKING_ENCODE_START_CONFIRM,
    AUDIO_BLUETOOTH_HANDSHAKING_PLAYERR,
    AUDIO_BLUETOOTH_HANDSHAKING_PLAYERR_CONFIRM,
    AUDIO_BLUETOOTH_HANDSHAKING_PLAYEND,
    AUDIO_BLUETOOTH_HANDSHAKING_PLAYEND_CONFIRM,
    AUDIO_BLUETOOTH_HANDSHAKING_FORCE_PLAYSTOP,
    AUDIO_BLUETOOTH_HANDSHAKING_FORCE_PLAYSTOP_CONFIRM,
    AUDIO_BLUETOOTH_HANDSHAKING_PAUSE,
    AUDIO_BLUETOOTH_HANDSHAKING_PAUSE_CONFIRM,
    AUDIO_BLUETOOTH_HANDSHAKING_RESUME,
    AUDIO_BLUETOOTH_HANDSHAKING_RESUME_CONFIRM,
    AUDIO_BLUETOOTH_HANDSHAKING_SET_POSITION,
    AUDIO_BLUETOOTH_HANDSHAKING_SET_POSITION_CONFRIM,
    AUDIO_BLUETOOTH_HANDSHAKING_PLAYERR_BT,
    AUDIO_BLUETOOTH_HANDSHAKING_PLAYERR_BT_CONFRIM,
    AUDIO_BLUETOOTH_HANDSHAKING_POSITION_UPDATE_BT
} MmlAudioBTHandshakingCause_e;

/** @ingroup    MMLayerAudioPlayback
    @brief      Bluetooth handshaking parameters
   */
typedef struct
{
    u32                              nHandle;      ///< Bluetooth ring buffer handle
    MmlAudioBTHandshakingCause_e     eCause;       ///< Identify which cause of BT handshaking
    u32                              nPosition;    ///< Used with A2DP_EVENT_POSITION_UPDATE event
    u32                              nbitRate;     ///< Used with BITRATE event
} MmlAudioBTHandshakeParam_t;

/** @ingroup    MMLayerAudio
    @brief      Notification payload
*/
typedef struct
{
    MmlAudioEvent_e	            eEvent;        ///< Specify the event you want to notify
    u32                         nHandle;       ///< 32-bit playback/recording handle

    /// union of MmlAudioNotify_t parameters
    union
    {
        MmlAudioStateChange_t          tStateChange;         ///< Used with AUDIO_EVENT_STATE_CHANGE event
        MmlAudioResult_e               eErrCode;             ///< Used with AUDIO_EVENT_RUNTIME_ERROR event
        MmlAudioFileParam_t            tFileParam;           ///< Used with AUDIO_EVENT_SAVE_FILE_COMPLETE event
        MmlAudioBufferParam_t          tBufferParam;         ///< Used with AUDIO_EVENT_SAVE_MEMORY_COMPLETE event
        u32                            nPosition;            ///< Used with AUDIO_EVENT_POSITION_UPDATE event
        u32                            nTimeLimit;           ///< Used with AUDIO_EVENT_REACH_TIME_LIMIT event
        u32                            nSizeLimit;           ///< Used with AUDIO_EVENT_REACH_SIZE_LIMIT event
        MmlAudioBTHandshakeParam_t     tBTHandshakeParam;    ///< MDW_A2DP_PLAYBACK_RB_FEATURE, used for BT/Audio handshaking
        u32                            nTotalPlayTime;       ///< Used with AUDIO_EVENT_PLAYBACK_TOTALPLAYTIME_UPDATE event, 32-bit total play time expressed in milliseconds
        u32                            nAvailableStreamTime; ///< Used with AUDIO_EVENT_PLAYBACK_STREAM_UNDERRUN, expressed in milliseconds
	} uParam;
} MmlAudioNotify_t;

/** @ingroup    MMLayerAudio
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pAudioNotify      Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlAudioNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlAudioNotify_t *pAudioNotify);

/** @ingroup    MMLayerAudio
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;           ///< Sender's mailbox ID
    u32                             nUserValue;          ///< Interface self-reference
    PfnMmlAudioNotifyCallback       pfnNotifyCallback;   ///< Callback function your want to register
} MmlAudioNotifyCallback_t;

/** @ingroup    MMLayerAudio
    @brief      Response callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      eErrCode          Returned result (error code)
    @param      pAudioResponse    Pointer to the returned response payload
*/
struct MmlAudioResponse_t_;
typedef void (*PfnMmlAudioResponseCallback)(u16 nSenderID, u32 nUserValue, MmlAudioResult_e eErrCode, struct MmlAudioResponse_t_ *pAudioResponse);

/** @ingroup    MMLayerAudio
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlAudioResponseCallback     pfnResponseCallback;    ///< Callback function your want to register
} MmlAudioResponseCallback_t;

/** @ingroup    MMLayerAudio
    @brief      Register notification callback
*/
typedef struct
{
    MmlAudioEvent_e                 eEvent;             ///< Specify which event you want to handle
    MmlAudioNotifyCallback_t        tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlAudioRegNotifyCallback_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Get MP3 ID3 tag
*/
typedef struct
{
    MmlAudioInputType_e             eInputType;     ///< Input source type
    u8                              *pBuffer;       ///< Pointer to the output ID3 tag data buffer
    u32                             nBufferSize;    ///< Size in bytes of the output ID3 tag data buffer

    /// union of MmlAudioGetMP3ID3Tag_t parameters
    union
    {
	    MmlAudioFileParam_t         tFileParam;     ///< Get from file-based source
	    MmlAudioMemoryParam_t       tMemoryParam;   ///< Get from in-memory source
	} uParam;
} MmlAudioGetMP3ID3Tag_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Get music lyrics
*/
typedef struct
{
    MmlAudioFileParam_t             tFileParam;     ///< Get info from file-based source
    u8                              *pBuffer;       ///< Pointer to the output lyric data buffer
    u32                             nBufferSize;    ///< Size in bytes of the output lyric data buffer
} MmlAudioGetMusicLyrics_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Playback speeds
*/
typedef enum
{
    AUDIO_PLAYBACK_SPEED_50 = 0,    ///< 0.5x
    AUDIO_PLAYBACK_SPEED_100,       ///< 1x
    AUDIO_PLAYBACK_SPEED_200,       ///< 2x
    AUDIO_PLAYBACK_SPEED_400        ///< 4x
} MmlAudioPlaybackSpeed_e;

/** @ingroup    MMLayerAudioPlayback
    @brief      Start playback (file/memory)
*/
typedef struct
{
    MmlAudioInputType_e         eInputType;     ///< Input source type
    MmlAudioOutputType_e        eOutputType;    ///< Output destination type (IIS, A2DP)
    u32                         nPosition;      ///< 32-bit value expressed in milliseconds and relative to the beginning of the content
    u32                         nHandle;        ///< 32-bit ring buffer handle, used for spectrum output
    MmlAudioMediaParam_t        tMediaParam;    ///< Media parameters
    u16                         bIsRingTone;    ///< Is ring tone
    /// union of MmlAudioStartPlayback_t parameters
    union
    {
        MmlAudioFileParam_t         tFileParam;         ///< Playback from file-based source
	    MmlAudioMemoryParam_t       tMemoryParam;       ///< Playback from in-memory source
	    MmlAudioStreamingParam_t    tStreamingParam;    ///< Playback from streaming source

	} uParam;
} MmlAudioStartPlayback_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Get audio Info (file/memory)\n
                If the advanced info selected, it will take more time to get the total play time.
*/
typedef struct
{
    MmlAudioInputType_e         eInputType;      ///< Input source type
    u16                         bAdvanceInfo;    ///< If enabled, the audio info contains total play time

    /// union of MmlAudioGetAudioInfo_t parameters
    union
    {
	    MmlAudioFileParam_t     tFileParam;      ///< Get info from file-based source
	    MmlAudioMemoryParam_t   tMemoryParam;    ///< Get info from in-memory source
	} uParam;
} MmlAudioGetAudioInfo_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Set playback speed
*/
typedef struct
{
    u32                         nHandle;           ///< 32-bit playback handle
    MmlAudioPlaybackSpeed_e     ePlaybackSpeed;    ///< Playback speed
} MmlAudioSetPlaybackSpeed_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Set playback position
*/
typedef struct
{
    u32                         nHandle;        ///< 32-bit playback handle
    u32                         nPosition;      ///< 32-bit value expressed in milliseconds and relative to the beginning of the content
} MmlAudioSetPlaybackPosition_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Volume up/down
*/
typedef enum
{
    AUDIO_VOLUMEUPDOWN_PLUSDB = 0,    ///< +dB (volume up)
    AUDIO_VOLUMEUPDOWN_MINUSDB,       ///< -dB (volume down)
} MmlAudioVolumeUpDown_e;

/** @ingroup    MMLayerAudioPlayback
    @brief      Volume control
*/
typedef struct
{
    u16                         bMuteEnable;      ///< If true, the volume is muted
    MmlAudioVolumeUpDown_e      eVolumeUpDown;    ///< +/-dB (volume up/down)
    u16                         nMagnitude;       ///< Magnitude (0: 0dB, 1: 0.5dB, ... , 254: 127dB, 255: 127.5dB)
} MmlAudioVolumeControl_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Balance left/right
*/
typedef enum
{
    AUDIO_BALANCELEFTRIGHT_LEFT = 0,    ///< Balance left
    AUDIO_BALANCELEFTRIGHT_RIGHT,       ///< Balance right
} MmlAudioBalanceLeftRight_e;

/** @ingroup    MMLayerAudioPlayback
    @brief      Volume balance
*/
typedef struct
{
    MmlAudioBalanceLeftRight_e    eBalanceLeftRight;    ///< Balance left/right
    u16                           nStep;                ///< Step (0: balance, 1: 1 step, ... , 100: 100 steps)
} MmlAudioVolumeBalance_t;

#define MML_AUDIO_BLUETOOTH_SAMPLINGRATE_BITMASK_16000           ((u32) 0x00000001)
#define MML_AUDIO_BLUETOOTH_SAMPLINGRATE_BITMASK_32000           ((u32) 0x00000002)
#define MML_AUDIO_BLUETOOTH_SAMPLINGRATE_BITMASK_44100           ((u32) 0x00000004)
#define MML_AUDIO_BLUETOOTH_SAMPLINGRATE_BITMASK_48000           ((u32) 0x00000008)

#define MML_AUDIO_BLUETOOTH_CHANNELMODE_BITMASK_MONO             ((u32) 0x00000001)
#define MML_AUDIO_BLUETOOTH_CHANNELMODE_BITMASK_DUALCHANNEL      ((u32) 0x00000002)
#define MML_AUDIO_BLUETOOTH_CHANNELMODE_BITMASK_STEREO           ((u32) 0x00000004)
#define MML_AUDIO_BLUETOOTH_CHANNELMODE_BITMASK_JOINTSTEREO      ((u32) 0x00000008)

#define MML_AUDIO_BLUETOOTH_BLOCKLENGTH_BITMASK_4                ((u32) 0x00000001)
#define MML_AUDIO_BLUETOOTH_BLOCKLENGTH_BITMASK_8                ((u32) 0x00000002)
#define MML_AUDIO_BLUETOOTH_BLOCKLENGTH_BITMASK_12               ((u32) 0x00000004)
#define MML_AUDIO_BLUETOOTH_BLOCKLENGTH_BITMASK_16               ((u32) 0x00000008)

#define MML_AUDIO_BLUETOOTH_SUBBAND_BITMASK_4                    ((u32) 0x00000001)
#define MML_AUDIO_BLUETOOTH_SUBBAND_BITMASK_8                    ((u32) 0x00000002)

#define MML_AUDIO_BLUETOOTH_ALLOCATIONMETHOD_BITMASK_SNR         ((u32) 0x00000001)
#define MML_AUDIO_BLUETOOTH_ALLOCATIONMETHOD_BITMASK_LOUDNESS    ((u32) 0x00000002)

/** @ingroup    MMLayerAudioPlayback
    @brief      Bluetooth
*/
typedef struct
{
    u16        eBluetoothEnable;     ///< If true, the bluetooth is enabled
    u32        nSamplingRate;        ///< A bitwise OR of sampling rates supported, MML_AUDIO_BLUETOOTH_SAMPLINGRATE_BITMASK_XXX
    u32        nChannelMode;         ///< A bitwise OR of channel modes supported, MML_AUDIO_BLUETOOTH_CHANNELMODE_BITMASK_XXX
    u32        nBlockLength;         ///< A bitwise OR of block lengths supported, MML_AUDIO_BLUETOOTH_BLOCKLENGTH_BITMASK_XXX
    u32        nSubband;             ///< A bitwise OR of subbands supported, MML_AUDIO_BLUETOOTH_SUBBAND_BITMASK_XXX
    u32        nAllocationMethod;    ///< A bitwise OR of allocation methods supported, MML_AUDIO_BLUETOOTH_ALLOCATIONMETHOD_BITMASK_XXX
    u16        nMaxBitpoolValue;     ///< Maximum bitpool value	(Min: 2 ~ Max: 250)
    u16        nMinBitpoolValue;     ///< Minimum bitpool value	(Min: 2 ~ Max: 250)
} MmlAudioBluetooth_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Post-processing engine calibration
*/
typedef struct
{
    u8         *pPostProcEngineTable;    ///< Pointer to the audio post-processing engine table
    u32        nTableSize;               ///< Size in bytes of the table
} MmlAudioPostProcEngineCalibration_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Pre-processing engine calibration
*/
typedef struct
{
    u8         *pPreProcEngineTable;    ///< Pointer to the audio pre-processing engine table
    u32        nTableSize;              ///< Size in bytes of the table
} MmlAudioPreProcEngineCalibration_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Set configuration
*/
typedef struct
{
    MmlAudioConfigurationType_e    eConfigurationType;    ///< Specify which type of setting to be configured

    /// union of MmlAudioSetConfiguration_t parameters
    union
    {
        MmlAudioVolumeControl_t                 tVolumeControl;
        MmlAudioVolumeBalance_t                 tVolumeBalance;
        MmlAudioBluetooth_t                     tBluetooth;
        MmlAudioPostProcEngineCalibration_t     tPostProcEngineCalibration_t;
        MmlAudioPreProcEngineCalibration_t      tPreProcEngineCalibration;
	} uParam;
} MmlAudioSetConfiguration_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Get configuration
*/
typedef struct
{
    MmlAudioConfigurationType_e    eConfigurationType;    ///< Specify which type of setting to get
} MmlAudioGetConfiguration_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      SRS WOW HD parameters
*/
typedef struct
{
    u16     bSrsEnable;     ///< Is SRS enabled
    u16     nMaximumLevel;  ///< Maximum level
    u16     nTruBass;       ///< Tru bass level
    u16     n3DCenter;      ///< 3D center level
    u16     n3DSpace;       ///< 3D space level
    u16     nFocus;         ///< Focus level
    u16     nDefinition;    ///< Definition level
} MmlAudioSrsWowhdParam_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Post-process effects
*/
typedef struct
{
    u16                 	n3DEffectId;            ///< Used to apply a 3D effect setting from the post-processing table
    u16                 	nUserEQId;              ///< Used to apply a user EQ setting from the post-processing table
    u16                 	nDolbyId;               ///< Used to apply the Dolby solution, mutually exclusive to 3D effect and user EQ
    u16                 	nPitchStretchId;        ///< Used to apply a pitch stretch setting from the post-processing table
    u16                 	nTimeStretchId;         ///< Used to apply a time stretch setting from the post-processing table
    u16                 	nReverbId;              ///< Used to apply a reverberated effect setting from the post-processing table
    MmlAudioSrsWowhdParam_t	tSrsWowhdParam;         ///< Used to apply a SRS WOW HD effect setting
    u16                     bVirtualBassEnable;     ///< Used to enable(disable) virtual bass
} MmlAudioPostProcEffect_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      All of the post-processing setting
*/
typedef struct
{
    MmlAudioPostProcEffect_t    tPostProcEffect;    ///< Used to apply the post-processing effects
    u16                         nDeviceType;        ///< Used to specify device type (0: none, 1: earphone, 2: speaker, 3: bluetooth)
    u16                         nMediaType;         ///< Used to specify media type  (0: none, 1: music, 2: video)
} MmlAudioPostProcAll_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Set post-processing setting
*/
typedef struct
{
    MmlAudioConfigurationType_e    eConfigurationType;    ///< Specify which type of setting to be configured
    u16                            bResetDMA;             ///< If true, DMA is reset

    /// union of MmlAudioSetPostProcSetting_t parameters
    union
    {
        MmlAudioPostProcEffect_t    tPostProcEffect;      ///< Used to apply the post-processing effects
        u16                         nDeviceType;          ///< Used to specify device type (0: none, 1: earphone, 2: speaker, 3: bluetooth)
        u16                         nMediaType;           ///< Used to specify media type (0: none, 1: music, 2: video)
        MmlAudioPostProcAll_t       tPostProcAll;         ///< Used to set all of the post-processing settings
	} uParam;
} MmlAudioSetPostProcSetting_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      All of the pre-processing setting
*/
typedef struct
{
    u16     						nDeviceType;          ///< Used to select a device type for the pre-processing((0: none, 1: microphone, 2: FM))
    u16             				nMediaType;           ///< Used to specify media type (0: none, 1: music, 2: video)
} MmlAudioPreProcAll_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Set pre-processing setting
*/
typedef struct
{
    MmlAudioConfigurationType_e    eConfigurationType;    ///< Specify which type of setting to be configured

    /// union of MmlAudioSetPreProcSetting_t parameters
    union
    {
        MmlAudioPreProcAll_t       tPreProcAll;           ///< Used to set all of the pre-processing settings
	} uParam;
} MmlAudioSetPreProcSetting_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Tone IDs
*/
typedef enum
{
    AUDIO_TONEID_DTMFTONE_0              = 0,    ///< Index '0' DTMF tone (post-proc setting)
    AUDIO_TONEID_DTMFTONE_1              = 1,    ///< Index '1' DTMF tone (post-proc setting)
    AUDIO_TONEID_DTMFTONE_2              = 2,    ///< Index '2' DTMF tone (post-proc setting)
    AUDIO_TONEID_DTMFTONE_3              = 3,    ///< Index '3' DTMF tone (post-proc setting)
    AUDIO_TONEID_DTMFTONE_4              = 4,    ///< Index '4' DTMF tone
    AUDIO_TONEID_DTMFTONE_5              = 5,    ///< Index '5' DTMF tone
    AUDIO_TONEID_DTMFTONE_6              = 6,    ///< Index '6' DTMF tone
    AUDIO_TONEID_DTMFTONE_7              = 7,    ///< Index '7' DTMF tone
    AUDIO_TONEID_DTMFTONE_8              = 8,    ///< Index '8' DTMF tone
    AUDIO_TONEID_DTMFTONE_9              = 9,    ///< Index '9' DTMF tone
    AUDIO_TONEID_DTMFTONE_A              = 10,   ///< Index 'A' DTMF tone
    AUDIO_TONEID_DTMFTONE_B              = 11,   ///< Index 'B' DTMF tone
    AUDIO_TONEID_DTMFTONE_C              = 12,   ///< Index 'C' DTMF tone
    AUDIO_TONEID_DTMFTONE_D              = 13,   ///< Index 'D' DTMF tone
    AUDIO_TONEID_DTMFTONE_STAR           = 14,   ///< Index '*' DTMF tone
    AUDIO_TONEID_DTMFTONE_HASH           = 15,   ///< Index '#' DTMF tone
    AUDIO_TONEID_DTMFTONE_BEEP1          = 16,
    AUDIO_TONEID_DTMFTONE_BEEP2          = 17,
    AUDIO_TONEID_DTMFTONE_WAITINGCALL    = 18,
    AUDIO_TONEID_DTMFTONE_ACCPLUGIN      = 19,
    AUDIO_TONEID_DTMFTONE_ACCPLUGOUT     = 20,
    AUDIO_TONEID_DTMFTONE_OUTGOING       = 21,
    AUDIO_TONEID_DTMFTONE_ALARMCLOCK     = 22,
    AUDIO_TONEID_DTMFTONE_CALLEND        = 23,
    AUDIO_TONEID_DTMFTONE_NUM
} MmlAudioToneId_e;

/** @ingroup    MMLayerAudioPlayback
    @brief      Play tone
*/
typedef struct
{
    MmlAudioToneId_e         eToneId;           ///< Specify what type of tone to play
    u16                      nVolumeRange;      ///< Set the volume range to play with
    u16                      nVolumeLevel;      ///< Set the volume level to play with
} MmlAudioPlayTone_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Encoder IDs
*/
typedef enum MmlAudioEncoderId_e_
{
    AUDIO_ENCODERID_AMR_NB = 0,
    AUDIO_ENCODERID_AMR_WB,
    AUDIO_ENCODERID_WAV_IMAADPCM_4BIT,
    AUDIO_ENCODERID_WAV_IMAADPCM_3BIT,
    AUDIO_ENCODERID_WAV_MSADPCM4BIT,
    AUDIO_ENCODERID_MP3_LAYERII,
    AUDIO_ENCODERID_PCM,
    AUDIO_ENCODERID_MP3_LAYERIII,
    AUDIO_ENCODERID_NUM
} MmlAudioEncoderId_e;

/** @ingroup    MMLayerAudioRecording
    @brief      Start recording
*/
typedef struct
{
    MmlAudioInputType_e         eInputType;     ///< Input source type
    MmlAudioOutputType_e        eOutputType;    ///< Output destination type
    u32                         nTimeLimit;     ///< 32-bit value on the duration of total recorded content in milliseconds. 0 is no limit
    u32                         nSizeLimit;     ///< 32-bit value on the duration of total recorded content in bytes. 0 is no limit

    /// union of MmlAudioStartRecording_t parameters
    union
    {
        MmlAudioFileParam_t         tFileParam;         ///< Record to file-based destination
	    MmlAudioMemoryParam_t       tMemoryParam;       ///< Record to in-memory destination
	    MmlAudioStreamingParam_t    tStreamingParam;    ///< Record to streaming destination
	    MmlAudioCallbackParam_t     tCallbackParam;     ///< Record to callback-based destination
    } uParam;
} MmlAudioStartRecording_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Recording setting
*/
typedef struct
{
    MmlAudioEncoderId_e         eEncoderId;     ///< Specify the supported audio encoder
    MmlAudioSamplingRate_e      eSamplingRate;  ///< Sampling rate (hz)
    u32                         nBitRate;       ///< 0 is to use the default bitrate
    MmlAudioChannelMode_e       eChannelMode;   ///< Channel mode
    u32                         nTimeLimit;     ///< 32-bit value on the duration of total recorded content in milliseconds. 0 is no limit
    u32                         nSizeLimit;     ///< 32-bit value on the duration of total recorded content in bytes. 0 is no limit
} MmlAudioRecordingSetting_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Set recording setting
*/
typedef struct
{
    MmlAudioEncoderId_e         eEncoderId;     ///< Specify the supported audio encoder
    MmlAudioSamplingRate_e      eSamplingRate;  ///< Sampling rate (hz)
    u32                         nBitRate;       ///< 0 is to use the default bitrate
    MmlAudioChannelMode_e       eChannelMode;   ///< Channel mode
} MmlAudioSetRecordingSetting_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Recording info
*/
typedef struct
{
    u32    nRemainingRecodingTime;    ///< 32-bit remaining recording time in seconds
} MmlAudioRecordingInfo_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Get recording info
*/
typedef struct
{
    MmlAudioEncoderId_e         eEncoderId;     ///< Specify the supported audio encoder
    MmlAudioSamplingRate_e      eSamplingRate;  ///< Sampling rate (hz)
    u32                         nBitRate;       ///< 0 is to use the default bitrate
    MmlAudioChannelMode_e       eChannelMode;   ///< Channel mode
    MmlAudioStorageType_e       eStorageType;   ///< Specify what kind of storage is used to save the recorded data
    MmlAudioFileParam_t         tFileParam;     ///< Record to file-based destination
} MmlAudioGetRecordingInfo_t;

#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_WAVE                   ((u32) 0x00000001)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_MIDI                   ((u32) 0x00000002)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_IMY                    ((u32) 0x00000004)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_MP3                    ((u32) 0x00000008)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_AAC                    ((u32) 0x00000010)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_AMR                    ((u32) 0x00000020)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_AWB                    ((u32) 0x00000040)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_RAM                    ((u32) 0x00000080)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_WMA                    ((u32) 0x00000100)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_WMV                    ((u32) 0x00000200)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_MP4                    ((u32) 0x00000400)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_3GP                    ((u32) 0x00000800)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_WAVE_EXT               ((u32) 0x00001000)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_MIDI_EVENT             ((u32) 0x00002000)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_PCM                    ((u32) 0x00004000)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_COOK                   ((u32) 0x00008000)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_APE                    ((u32) 0x00010000)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_M4A                    ((u32) 0x00020000)
#define MML_AUDIOPLAYBACK_FORMAT_BITMASK_ASF                    ((u32) 0x00040000)
#define MML_AUDIOPLAYBACK_CHANNELMODE_BITMASK_MONO              ((u32) 0x00000001)
#define MML_AUDIOPLAYBACK_CHANNELMODE_BITMASK_STEREO            ((u32) 0x00000002)

/** @ingroup    MMLayerAudioPlayback
    @brief      Audio playback capability
*/
typedef struct
{
    u32     nFormatSupported;     ///< Playback formats supported
    //u32     nMaxSamplingRate;     ///< Maximum sampling rate supported (Hz)
    //u32     nMinSamplingRate;     ///< Minimum sampling rate supported (Hz)
    //u32     nMaxBitRate;          ///< Maximum bitrate supported (bps)
    //u32     nMinBitRate;          ///< Minimum bitrate supported (bps)
    u32     nChannelMode;         ///< Channel modes supported
    u16     bUserEQSupported;     ///< User EQ supported ?
    u16     b3DEffectSupported;   ///< 3D effect supported ?
    u16     bTimeStretchSupported;///< Time stretch supported ?
    u16     bReverbSupported;     ///< Reverb supported ?
    u16     bAudioMixSupported;   ///< Audio mix supported ?
    u16     bPitchShiftSupported; ///< Pitch shift supported ?
    u16     bDolbySupported;      ///< Dolby supported ?
    u16     bSrsWowhdSupported;   ///< SRS WOW HD supported ?
    u16     bVirtualBassSupported;///< Virtual bass supported ?
} MmlAudioPlaybackCapability_t;

/** @ingroup    MMLayerAudioPlayback
    @brief      Get playback capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlAudioGetPlaybackCapability_t;

#define MML_AUDIORECORDING_ENCODER_BITMASK_AMR_NB               ((u32) 0x00000001)
#define MML_AUDIORECORDING_ENCODER_BITMASK_AMR_WB               ((u32) 0x00000002)
#define MML_AUDIORECORDING_ENCODER_BITMASK_WAV_IMAADPCM_4BIT    ((u32) 0x00000004)
#define MML_AUDIORECORDING_ENCODER_BITMASK_WAV_IMAADPCM_3BIT    ((u32) 0x00000008)
#define MML_AUDIORECORDING_ENCODER_BITMASK_WAV_MSADPCM4BIT      ((u32) 0x00000010)
#define MML_AUDIORECORDING_ENCODER_BITMASK_MP3_LAYERII          ((u32) 0x00000020)
#define MML_AUDIORECORDING_ENCODER_BITMASK_PCM                  ((u32) 0x00000040)
#define MML_AUDIORECORDING_ENCODER_BITMASK_MP3_LAYERIII         ((u32) 0x00000080)
#define MML_AUDIORECORDING_CHANNELMODE_BITMASK_MONO             ((u32) 0x00000001)
#define MML_AUDIORECORDING_CHANNELMODE_BITMASK_STEREO           ((u32) 0x00000002)

/** @ingroup    MMLayerAudioRecording
    @brief      Audio recording capability
*/
typedef struct
{
    u32     nEncoderSupported;    ///< Encoders supported
    u32     nMaxSamplingRate;     ///< Maximum sampling rate supported (Hz)
    u32     nMinSamplingRate;     ///< Minimum sampling rate supported (Hz)
    u32     nMaxBitRate;          ///< Maximum bitrate supported (bps)
    u32     nMinBitRate;          ///< Minimum bitrate supported (bps)
    u32     nChannelMode;         ///< Channel modes supported
} MmlAudioRecordingCapability_t;

/** @ingroup    MMLayerAudioRecording
    @brief      Get recording capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlAudioGetRecordingCapability_t;

/** @ingroup    MMLayerAudio
    @brief      Response payload
*/
typedef struct MmlAudioResponse_t_
{
    MmlAudioState_e         eState;       ///< Current state
    u32                     nHandle;      ///< 32-bit playback/recording handle

    /// union of MmlAudioResponse_t parameters
	union
	{
        u32                                    nPosition;                       ///< Used with 'Get playback position'
        u32                                    nDataSize;                       ///< Used with 'Get music lyrics'
        MmlAudioRecordingSetting_t             tRecordingSetting;               ///< Used with 'Get recording setting'
        MmlAudioStateChange_t                  tStateChange;                    ///< Used with 'AUDIO_ERROR_STATE_CHANGE' result
        MmlAudioBufferParam_t                  tBufferParam;                    ///< Used with 'Get MP3 ID3 tag' and 'Get music lyrics'
        MmlAudioInfo_t                         tAudioInfo;                      ///< Used with 'Get audio info'
        MmlAudioRecordingInfo_t                tRecordingInfo;                  ///< Used with 'Get recording info'
        MmlAudioPostProcEngineCalibration_t    tPostProcEngineCalibration_t;    ///< Used with 'Get configuration'
        MmlAudioPreProcEngineCalibration_t     tPreProcEngineCalibration;       ///< Used with 'Get configuratoin'
        MmlAudioPlaybackCapability_t           tPlaybackCapability;             ///< Used with 'Get playback capability'
        MmlAudioRecordingCapability_t          tRecordingCapability;            ///< Used with 'Get recording capability'
    } uParam;
} MmlAudioResponse_t;

/** @ingroup    MMLayerAudio
    @brief      Audio use case parameters
*/
typedef struct
{
	u32                                 nUseCaseID;             ///< Use case ID
	MmlAudioResponseCallback_t          *pResponseCallback;     ///< Pointer to the response callback registration data
	MmlAudioResponse_t                  *pResponse;             ///< Pointer to the response payload

    /// union of MmlAudioUCParam_t parameters
	union
	{
	    /* No parameter: 'Get recording setting' */

        u32                                 nHandle;                    ///< Used with 'Stop playback, Pause playback, Resume playback,
                                                                        ///< Stop recording, Pause recording, Resume recording, Cancel seek
                                                                        ///< Save recording file, Discard recording file, Get playback position,
                                                                        ///< Abort saving'
	    MmlAudioStartPlayback_t             tStartPlayback;             ///< Used with 'Start playback'
	    MmlAudioRegNotifyCallback_t         tRegNotifyCallback;         ///< Used with 'Register notification callback'
	    MmlAudioStartRecording_t            tStartRecording;            ///< Used with 'Start recording'
	    MmlAudioSetPlaybackPosition_t       tSetPlaybackPosition;       ///< Used with 'Set playback position'
	    MmlAudioSetPlaybackSpeed_t          tSetPlaybackSpeed;          ///< Used with 'Set playback speed'
	    MmlAudioGetMP3ID3Tag_t              tGetMP3ID3Tag;              ///< Used with 'Get MP3 ID3 tag'
	    MmlAudioGetMusicLyrics_t            tGetMusicLyrics;            ///< Used with 'Get music lyrics'
	    MmlAudioSetRecordingSetting_t       tSetRecordingSetting;       ///< Used with 'Set recording setting'
        MmlAudioGetAudioInfo_t              tGetAudioInfo;              ///< Used with 'Get audio info'
        MmlAudioSetConfiguration_t          tSetConfiguration;          ///< Used with 'Set configuration'
        MmlAudioSetPostProcSetting_t        tSetPostProcSetting;        ///< Used with 'Set post-processing setting'
        MmlAudioSetPreProcSetting_t         tSetPreProcSetting;         ///< Used with 'Set pre-processing setting'
	    MmlAudioGetRecordingInfo_t          tGetRecordingInfo;          ///< Used with 'Get recording info'
        MmlAudioGetConfiguration_t          tGetConfiguration;          ///< Used with 'Get configuration'
        MmlAudioPlayTone_t                  tPlayTone;                  ///< Used with 'Play tone'
        MmlAudioGetPlaybackCapability_t     tGetPlaybackCapability;     ///< Used with 'Get playback capability'
        MmlAudioGetRecordingCapability_t    tGetRecordingCapability;    ///< Used with 'Get recording capability'
	} uParam;
} MmlAudioUCParam_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLAUDIO_TYPES_H__

