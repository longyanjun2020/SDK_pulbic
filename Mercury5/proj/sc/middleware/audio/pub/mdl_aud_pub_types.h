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
* @file    mdl_audio_pub_types.h
* @version
* @brief   Abscontainer middleware audio datatype header file
*
*/

#ifndef __MDL_AUD_PUB_TYPES_H__
#define __MDL_AUD_PUB_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mdl_audio_pub_api.h"
#include "mdl_aud_forward.h"
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * @brief The enumeration defines Audio channel
 */
opaque_enum(MdlAudChannel_e_)
{
	MDL_AUD_VOICE_CHANNEL = 0,   /**< Voice channel for speech/DTMF (in/out, 8 kHz) */
	MDL_AUD_MUSIC_CHANNEL,       /**< Music channel for media playback/recording (in only, up to 48 kHz) */
	MDL_AUD_LINEIN_CHANNEL,      /**< Auxiliary line-in channel for FM Radio */
	MDL_AUD_MAX_CHANNEL
};

/**
 * @brief The enumeration defines Audio DTMF tone index
 */
opaque_enum(MdlAudDTMF_e_)
{
    MDL_AUD_DTMFTONE_0              = 0,  /**< Index '0' DTMF Tone */
    MDL_AUD_DTMFTONE_1              = 1,  /**< Index '1' DTMF Tone */
    MDL_AUD_DTMFTONE_2              = 2,  /**< Index '2' DTMF Tone */
    MDL_AUD_DTMFTONE_3              = 3,  /**< Index '3' DTMF Tone */
    MDL_AUD_DTMFTONE_4              = 4,  /**< Index '4' DTMF Tone */
    MDL_AUD_DTMFTONE_5              = 5,  /**< Index '5' DTMF Tone */
    MDL_AUD_DTMFTONE_6              = 6,  /**< Index '6' DTMF Tone */
    MDL_AUD_DTMFTONE_7              = 7,  /**< Index '7' DTMF Tone */
    MDL_AUD_DTMFTONE_8              = 8,  /**< Index '8' DTMF Tone */
    MDL_AUD_DTMFTONE_9              = 9,  /**< Index '9' DTMF Tone */
    MDL_AUD_DTMFTONE_A              = 10, /**< Index 'A' DTMF Tone */
    MDL_AUD_DTMFTONE_B              = 11, /**< Index 'B' DTMF Tone */
    MDL_AUD_DTMFTONE_C              = 12, /**< Index 'C' DTMF Tone */
    MDL_AUD_DTMFTONE_D              = 13, /**< Index 'D' DTMF Tone */
    MDL_AUD_DTMFTONE_STAR           = 14, /**< Index '*' DTMF Tone */
    MDL_AUD_DTMFTONE_HASH           = 15, /**< Index '#' DTMF Tone */
    MDL_AUD_DTMFTONE_BEEP1          = 16,
    MDL_AUD_DTMFTONE_BEEP2          = 17,
    MDL_AUD_DTMFTONE_WAITINGCALL    = 18,
    MDL_AUD_DTMFTONE_ACC_PLUG_IN    = 19,
    MDL_AUD_DTMFTONE_ACC_PLUG_OUT   = 20,
    MDL_AUD_DTMFTONE_OUTGOING       = 21,
    MDL_AUD_DTMFTONE_ALARM_CLOCK    = 22,
    MDL_AUD_DTMFTONE_CALL_END       = 23,
    MDL_AUD_DTMFTONE_MAX_NUM
};

/**
 *  @brief AV file format
 */ 
opaque_enum(MdlAudFormat_e_)
{
    MDL_AUD_WAVE = 0,          /**< Format wav */
    MDL_AUD_MIDI,              /**< Format MID */
    MDL_AUD_IMY,               /**< Format iMelody */
    MDL_AUD_MP3,               /**< Format MP3 */
    MDL_AUD_AAC,               /**< Format AAC */
    MDL_AUD_AMR,               /**< Format AMR */
    MDL_AUD_AWB,               /**< Format AWB */
    MDL_AUD_RAM,               /**< Format RAM */
    MDL_AUD_WMA,               /**< Format WMA */
    MDL_AUD_WMV,               /**< Format WMV */
    MDL_AUD_MP4,               /**< Format MP4 */
    MDL_AUD_3GP,               /**< Format 3gp */
    MDL_AUD_WAVE_EXT,
    MDL_AUD_MIDI_EVENT,        /**< Format midi event for Java */
    MDL_AUD_PCM,               /**< Format PCM (no wave header)*/
    MDL_AUD_UNKNOW_FORMAT
};

/**
 *  @brief Audio frequency
 */
opaque_enum(MdlAudSamplingRate_e_)
{
    MDL_AUD_8_KHZ = 0,   /**< 8 kHz */
    MDL_AUD_11_025_KHZ,  /**< 11.025 kHz */
    MDL_AUD_12_KHZ,      /**< 12 kHz */
    MDL_AUD_16_KHZ,      /**< 16 kHz */
    MDL_AUD_22_050_KHZ,  /**< 22.050 kHz */
    MDL_AUD_24_KHZ,      /**< 24 kHz */
    MDL_AUD_32_KHZ,      /**< 32 kHz */
    MDL_AUD_44_1_KHZ,    /**< 44.1 kHz */
    MDL_AUD_48_KHZ,      /**< 48 kHz */
    MDL_AUD_64_KHZ,      /**< 64 kHz */
    MDL_AUD_96_KHZ,      /**< 96 kHz */
    MDL_AUD_MAX_SAMPLING_RATE
};

/**
 *  @brief The structure defines the audio streaming playback information
 */
struct MdlAudStreamParam_t_{
    MdlAudFormat_e eFileFormat;    /**< Audio streaming data format */
    u8             nMode;          /**< To indicate data buffer start:0/streaming:1/end:2/start_end:3 */
    u8            *pnStreamData;   /**< Streaming data buffer pointer */
    u32            nDataLen;       /**< Total size of the streaming data buffer */

    union
    {
        struct
        {
            MdlAudSamplingRate_e   nSampleRate;     /**< sample rate */
            bool                   bStereo;         /**< stereo(true) or mono(false) */
        } tPcmParam;
    } tParam;

};

/**
 *  @brief The enumeration defines the music playing mode
 */
opaque_enum(MdlAudMusicMode_e_)
{
    MDL_AUD_MUSIC_TO_NE_WITHOUT_GSM_DL,         /**< Play music to near end */
    MDL_AUD_MUSIC_TO_NE_WITH_GSM_DL,            /**< Play music and GSM DL to near end */
    MDL_AUD_MUSIC_TO_FE_WITHOUT_ADC_UL,         /**< Play music to far end */
    MDL_AUD_MUSIC_TO_FE_WITH_ADC_UL,            /**< Play music and ADC UL to far end */
    MDL_AUD_MUSIC_TO_NE_FE_WITH_GSM_UL_ADC_DL,  /**< Play music to both near end and far end */
};

/**
 *  @brief The enumeration defines the medium type
 */
opaque_enum(MdlAudType_e_)
{
    MDL_AUD_MUSIC_NONE = 0,
    MDL_AUD_MUSIC_PLAY,
    MDL_AUD_MIDI_PLAY,
    MDL_AUD_VIDEO_PLAY,
    MDL_AUD_SHUTTER_PLAY,
    MDL_AUD_IPTV_PLAY,
    MDL_AUD_FMR_PLAY,
    MDL_AUD_ATV_PLAY,
    MDL_AUD_MUSIC_REC,
    MDL_AUD_MIDI_REC,
    MDL_AUD_VIDEO_REC,
    MDL_AUD_VOICE_REC,
    MDL_AUD_FMR_REC,
    MDL_AUD_VIDEO_TELEPHONY,   ///< only use for 3G video telephony
    MDL_AUD_TONE_PLAY,         ///< onely use for 3G
    MDL_AUD_RING_TONE_PLAY,    ///< use Ring Tone
    MDL_AUD_A2DP_PLAY,         ///< use for sw a2dp
    MDL_AUD_MIC_LOOP_BACK,
    MDL_AUD_MUSIC_PLAY_AND_REC,      ///< play and record simultaneously
    MDL_AUD_AUDIO_TYPE_MAX,
};

/**
 * \brief Audio distorted voice type
 *
 *  @brief MdlAudDistortedVoice_e to specify the distorted voice.
 */
opaque_enum(MdlAudDistortedVoice_e_)
{
    MDL_AUD_DISTORTED_VOICE_NORMAL = 0,
    MDL_AUD_DISTORTED_VOICE_KID,
    MDL_AUD_DISTORTED_VOICE_GIRL,
    MDL_AUD_DISTORTED_VOICE_WOMAN,
    MDL_AUD_DISTORTED_VOICE_MALE,
    MDL_AUD_DISTORTED_VOICE_MAN,
    MDL_AUD_DISTORTED_VOICE_BASS,
};

/**
 * \brief Audio Tch config params
 *
 */
opaque_enum(MdlAudioTchOutput_e_)
{
    MDL_AUDIO_TCH_LINE_STEREO_OUT = 0, /**< Line out (stereo) */
    MDL_AUDIO_TCH_EARPIECE_OUT,        /**< earpiece (mono) */
    MDL_AUDIO_TCH_HEADSET_OUT,         /**< Headset (stereo) */
    MDL_AUDIO_TCH_ALL_OUT,             /**< Earpiece + line + headset */
    MDL_AUDIO_TCH_LINE_LEFT_OUT,       /**< Line out (left only) */
    MDL_AUDIO_TCH_LINE_RIGHT_OUT,      /**< Line out (right only) */
    MDL_AUDIO_TCH_HEADSET_LEFT_OUT,    /**< earpiece (left only) */
    MDL_AUDIO_TCH_HEADSET_RIGHT_OUT,   /**< earpiece (right only) */
    MDL_AUDIO_TCH_HEADSET_LINE_OUT,    /**< Headset + Line out */
    MDL_AUDIO_TCH_BT_MONO_OUT,         /**< BT (mono) */
    MDL_AUDIO_TCH_BT_STEREO_OUT,       /**< BT (stereo) */
    MDL_AUDIO_TCH_BT_VT_OUT,           /**< BT (video telephony) */
    MDL_AUDIO_TCH_MAX_OUT              /**< no output needed */
};

opaque_enum(MdlAudioTchInput_e_)
{
    MDL_AUDIO_TCH_HEADSET_MIC_IN = 0,  /**< headset microphone */
    MDL_AUDIO_TCH_HANDSET_MIC_IN,      /**< handset microphone */
    MDL_AUDIO_TCH_AUX_IN,              /**< Aux input */
    MDL_AUDIO_TCH_BT_MONO_IN,          /**< BT headset microphone */
    MDL_AUDIO_TCH_MAX_IN               /**< no input needed */
};

opaque_enum(MdlAudioTchIF_e_)
{
    MDL_AUDIO_IF_I2S = 0,         ///< primary I2S (ASL1) CPU/DSP
    MDL_AUDIO_IF_I2S2,            ///< one-way I2S
    MDL_AUDIO_IF_EAI_I2SE,        ///< secondary I2S (EAI): DSP only
    MDL_AUDIO_IF_EAI_PCM_M_128,   ///< PCM Master BCLK=128kHz (EAI): DSP only
    MDL_AUDIO_IF_EAI_PCM_M_256,   ///< PCM Master BCLK=256kHz (EAI): DSP only
    MDL_AUDIO_IF_EAI_PCM_S_128,   ///< PCM Slave BCLK=128kHz (EAI): DSP only
    MDL_AUDIO_IF_EAI_PCM_S_256,   ///< PCM Slaver BCLK=256kHz (EAI): DSP only
    MDL_AUDIO_IF_EAI_DAI_0,       ///< DAI (EAI) in normal mode
    MDL_AUDIO_IF_EAI_DAI_1,       ///< DAI (EAI) in test mode 1
    MDL_AUDIO_IF_EAI_DAI_2,       ///< DAI (EAI) in test mode 2
    MDL_AUDIO_IF_EAI_DAI_3        ///< DAI (EAI) in test mode 3
};

opaque_enum(MdlAudioTchCfgReq_e_)
{
    Mdl_AUDIO_CFG_REQ_NONE = 0,   ///< Request None
    Mdl_AUDIO_CFG_REQ_MO,         ///< Request Voice MO call
    Mdl_AUDIO_CFG_REQ_MT,         ///< Request Voice MT call
    Mdl_AUDIO_CFG_REQ_CC_TCH_IND, ///< Request CC TCH got notification, possible MO or MT
    Mdl_AUDIO_CFG_REQ_DTMF,       ///< Request DTMF
    Mdl_AUDIO_CFG_REQ_WAVE        ///< Request WAVE
};

opaque_enum(MdlAudioTchRenderType_e_)
{
    MDL_AUDIO_RENDER_NONE = 0,
    MDL_AUDIO_RENDER_UL_DL,
    MDL_AUDIO_RENDER_DL,
    MDL_AUDIO_RENDER_UL,
    MDL_AUDIO_RENDER_MAX_TYPE
};

struct MdlAudioManagerParam_t_
{
    MdlAudSamplingRate_e    eSamplingRate;  ///< frequency of channel
    MdlAudioTchOutput_e     eOutput;        ///< output of channel
    MdlAudioTchInput_e      eInput;         ///< input of channel
    MdlAudGain_t            tInputGain;     ///< input gain of channel
    MdlAudGain_t            tOutputGain;    ///< output gain of channel
    bool                    bStereo;        ///< if TRUE, stereo output will be used
    bool                    bCpuPath;       ///< - TRUE if the audio should be accessed by the cpu ( mp3,...)
                                            ///  - FALSE if the audio should be accessed by the dsp ( amr playback/recording, polyphonies playback,...)
    bool                    bMixing;        ///< - TRUE if the audio output should be the mixing of microphone output and voice output
                                            ///  - FALSE if the audio ouput should be only the voice output
    MdlAudioTchIF_e         eHwIF;          ///< HW IF in use for this channel
    u8                      nMailbox;       ///< mailbox in which to send the headset messages
    MdlAudioTchCfgReq_e     eCfgReq;        ///< Configuration usage
    MdlAudioTchRenderType_e eRenderType;    ///< Render Type
};

struct MdlAudTchConfig_t_
{
    MdlAudChannel_e         eChannel;
    MdlAudioManagerParam_t  tParam;
};

/**
 *  @brief The structure defines speaker type
 */
opaque_enum(MdlAudSpeakerType_e_)
{
    MDL_AUD_SPEAKER_MONO = 0,
    MDL_AUD_SPEAKER_STEREO,
    MDL_AUD_SPEAKER_MAX_TYPE
};

/**
 *  @brief The enumeration defines the audio playback command
 */ 
opaque_enum(MdlAudPlayCmd_e_)
{
    MDL_AUD_VOICE_PAUSE,    /**< DBB audio play pause */
    MDL_AUD_VOICE_RESUME,   /**< DBB audio play pause */
    MDL_AUD_VOICE_STOP      /**< DBB audio play pause */
};

/**
 *  @brief The sturcture defines the return information of audio media file information
 */
struct MdlAudInfo_t_
{
	union
    {
        u32 nInfo;
    } tParam;
};

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
typedef void (*MdlAudCbFn_t)(u16 nSenderID, u32 nUserValue, MdlAudRet_e eErrCode, MdlAudInfo_t *ptAudInfo);


/**
 *  @brief Esl call back function structure definition
 */
struct MdlAudCb_t_{
  u16            nSenderID;       /**< Task id of sender */
  u32            nUserValue;      /**< userValue of sender for checking msg response */
  MdlAudCbFn_t   ptfnCb;          /**< Call back function that called by Media task after process finished. */
};

/**
 *  @brief The enumeration defines type of the audio notification.
 */
opaque_enum(MdlAudNotifyType_e_)
{
    MDL_AUD_NOTIFY_PLAY_END,                       /**< Notify when audio playing ended */
    MDL_AUD_NOTIFY_PLAY_ERROR,                     /**< Notify when audio playing occurs error */
    MDL_AUD_NOTIFY_PLAY_POSITION_UPDATE,           /**< Notify when play position updated */
    MDL_AUD_NOTIFY_PLAY_ADD_BUFFER_DONE,           /**< Notify when add buffer done */
    MDL_AUD_NOTIFY_PLAY_BITRATE_CHANGE,            /**< Notify when play bitrate changed */
    MDL_AUD_NOTIFY_PLAY_LYRICS_UPDATE,             /**< Notify when play lyrics updated */
    MDL_AUD_NOTIFY_PLAY_STREAM_DECODE_COMPLETE,    /**< Notify when stream decode complete */

    MDL_AUD_NOTIFY_REC_END,                        /**< Notify when audio recording end */
    MDL_AUD_NOTIFY_REC_SAPCE_FULL,                 /**< Notify when audio recording stops because of space fully */
    MDL_AUD_NOTIFY_REC_ERROR,                      /**< Notify when audio recording ocuurs error */
    MDL_AUD_NOTIFY_REC_POSITION_UPDATE,            /**< Notify when audio recording position updated */

    MDL_AUD_NOTIFY_PLAY_ALL,
    MDL_AUD_NOTIFY_REC_ALL,
    MDL_AUD_NOTIFY_GENERAL_UPDATE,
    MDL_AUD_NOTIFY_NB,

    MDL_AUD_NOTIFY_VOICE_PLAY_BASS,
    MDL_AUD_NOTIFY_VOICE_PLAY_END = MDL_AUD_NOTIFY_VOICE_PLAY_BASS,
    MDL_AUD_NOTIFY_VOICE_PLAY_ERROR,
    MDL_AUD_NOTIFY_VOICE_PLAY_MAX
};

/**
 *  @brief The enumeration defines the ESL notify error code
 */
opaque_enum(MdlAudNotifyErr_e_)
{
    MDL_AUD_NOTIFY_ERR_UNKNOWN,
    MDL_AUD_NOTIFY_ERR_OUT_MEMORY,
    MDL_AUD_NOTIFY_ERR_FILE_DATA_FAIL,
    MDL_AUD_NOTIFY_ERR_FORMAT_NOT_SUPPORT,
    MDL_AUD_NOTIFY_ERR_SDCARD_NOT_DETECTED,
};

/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
struct MdlAudNotifyInfo_t_{
    MdlAudNotifyType_e	eNotifyType;  /**< Type of audio notification */
    union
    {
        MdlAudNotifyErr_e eNotifyErr; /**< audio error code for "ESL_AUD_NOTIFY_PLAY_ERROR" */
        u32               nPosition;  /**< audio playback position for "ESL_AUD_NOTIFY_PLAY_POSITION_UPDATE"*/
        u32               nBitrate;   /**< audio decode bitrate for "ESL_AUD_NOTIFY_PLAY_STREAM_DECODE_COMPLETE"*/
	} tNotify;
};

/**
 *  @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID      : Sender task id.
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pAudGetInfo   : Notification value return by Multimedia task.
 *
 * @return None
 */
typedef void (*MdlAudNotifyCb)(u16 nSenderID, u32 nUserValue, MdlAudNotifyInfo_t *tAudNotifyInfo);

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
struct MdlAudNotifyCb_t_
{
    u16             nSenderID;       /**< Sender ID */
    u32             nUserValue;      /**< Reference value for indicating different sender in same task or check msg response. */
    MdlAudNotifyCb  pfnNotifyCb;     /**< Notification call back function that called by Media task after receiving the notification. */
};

/**
 * @brief The enumeration defines the audio Input/Output path
 */
opaque_enum(MdlAudPath_e_)
{
    MDL_AUD_PATH_NONE = 0,            /**< No audio path select */
    MDL_AUD_PATH_HANDSET,             /**< Audio handset path (Micrphone + Receiver)  */
    MDL_AUD_PATH_HEADSET,             /**< Audio headset path (Headset output and Headset microphone input) */
    MDL_AUD_PATH_HANDSFREE,           /**< Audio handsfree path (Microphone + Speaker) */
    MDL_AUD_PATH_LINE_OUT,            /**< Audio Line out speaker path for media channel (Speaker only)*/
    MDL_AUD_PATH_LINE_LEFT_OUT,       /**< Audio Line left out speaker path for media channel (Speaker only) */
    MDL_AUD_PATH_LINE_RIGHT_OUT,      /**< Audio Line right out speaker path for media channel (Speaker only) */
    MDL_AUD_PATH_HEADPHONE_OUT,       /**< Audio Line out headset path for media channel (Headset output only)*/
    MDL_AUD_PATH_BT_MONO,             /**< Audio Bluetooth mono path for voice channel */
    MDL_AUD_PATH_BT_STEREO,           /**< Audio Bluetooth stereo path for media channel */
    MDL_AUD_PATH_BT_VT,               /**< Audio Bluetooth video telephony path for media channel */
    MDL_AUD_PATH_HEADSET_AND_LINE_OUT,/**< Audio Headset and Line out speaker path (Headset + Lineout output */
    MDL_AUD_PATH_ALL_OUT,             /**< Audio all path (Receiver + Headset output + Speaker) */
};

/**
 * \brief Audio input type
 *
 *  Used in \ref vm_AudioManagerParam_t to specify the input of the channel, if necessary.
 */
opaque_enum(MdlAudInput_e_)
{
    MDL_AUD_HEADSET_IN = 0, ///< headset microphone
    MDL_AUD_HANDSET_IN,     ///< handset microphone
    MDL_AUD_AUX_IN,         ///< Aux input
    MDL_AUD_BT_MONO_IN,     ///< BT mono microphone
    MDL_AUD_MAX_IN          ///< no input needed
};

/**
 * \brief Audio output type
 *
 *  Used in \ref vm_AudioManagerParam_t to specify the output of the channel.
 */
opaque_enum(MdlAudOutput_e_)
{
    MDL_AUD_LINE_STEREO_OUT=0,   ///< Line out (stereo)
    MDL_AUD_EARPIECE_OUT ,       ///< earpiece (mono)
    MDL_AUD_HEADSET_OUT,         ///<  Headset (stereo)
    MDL_AUD_ALL_OUT ,            ///< Earpiece + line + headset
    MDL_AUD_LINE_LEFT_OUT,
    MDL_AUD_LINE_RIGHT_OUT,
    MDL_AUD_HEADSET_LEFT_OUT,
    MDL_AUD_HEADSET_RIGHT_OUT,
    MDL_AUD_HEADSET_LINE_OUT,    ///< Headset + Line out
    MDL_AUD_BT_MONO_OUT,         ///< BT (mono)
	MDL_AUD_BT_STEREO_OUT,       ///< BT (stereo)
	MDL_AUD_BT_VT_OUT,           ///< BT (video telephony)
    MDL_AUD_MAX_OUT              ///< no output needed
};

/**
 *  @brief The sturcture defines the audio config parameter
 */
struct MdlAudConfig_t_
{
    MdlAudPath_e    eAudPath;      /**< Audio path */
    MdlAudInput_e   eInput;        /**< input path */
    MdlAudOutput_e  eOutput;       /**< Output path */
    u8              nVolRange;     /**< Volume range */
    u8              nVolLevel;     /**< Volume level */
    s8              nBalanceRange; /**< Balance range */
    s8              nBalanceLevel; /**< Balance level */
    bool            bInMute;       /**< Mute */
    bool            bOutputOn;     /**< Output on */
};

/**
 *  @brief The sturcture defines the return information of audio gain information
 */
struct MdlAudGainInfo_t_
{
    /* fixed point Q16 { */
    s32             nMmpDpgaGain;  // stereo channal DPGA gain
    s32             nVppAfterDac;
    s32             nAnalogGain;
    s32             nVppAfterDrv;
    s32             nAmpGain;
    s32             nVppAfterAmp;
    s32             nExtAmpGain;
    s32             nVppAfterExtAmp;
    /* fixed point Q16 } */
    s8              nMmpDpgaGainInx;   // gain (dB)
};

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
#endif //__MDL_AUD_PUB_TYPES_H__

