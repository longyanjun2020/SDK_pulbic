#ifndef __VM_AUDIO_TYPES_H__
#define __VM_AUDIO_TYPES_H__

#include "mdl_aud_forward.h"
// vm_audio_api.h
/**
 * \brief Audio channel type
 *
 *  Used in \ref vm_AudioManagerParam_t .
 */
opaque_enum(vm_AudioChannel_e_)
{
    VM_AUDIO_VOICE_CHANNEL = 0, ///< Voice channel (in/out, 8 or 16 kHz)
    VM_AUDIO_STEREO_CHANNEL,    ///< Stereo channel (in only, up to 48 kHz)
    VM_AUDIO_AUX_CHANNEL,       ///< Auxillary channel (analog)
    VM_AUDIO_NB_CHANNELS        ///< NB max channels
};

/**
 * \brief Audio input type
 *
 *  Used in \ref vm_AudioManagerParam_t to specify the input of the channel, if necessary.
 */
opaque_enum(vm_AudioInput_e_)
{
    VM_AUDIO_HEADSET_IN = 0, ///< headset microphone
    VM_AUDIO_HANDSET_IN, ///< handset microphone
    VM_AUDIO_AUX_IN,  ///< Aux input
    VM_AUDIO_BT_MONO_IN, ///< BT headset microphone
    VM_AUDIO_MAX_IN ///< no input needed
};

/**
 * \brief Audio output type
 *
 *  Used in \ref vm_AudioManagerParam_t to specify the output of the channel.
 */
opaque_enum(vm_AudioOutput_e_)
{
    VM_AUDIO_LINE_STEREO_OUT=0,   ///< Line out (stereo)
    VM_AUDIO_EARPIECE_OUT ,       ///< earpiece (mono)
    VM_AUDIO_HEADSET_OUT,         ///<  Headset (stereo)
    VM_AUDIO_ALL_OUT ,            ///< Earpiece + line + headset
    VM_AUDIO_LINE_LEFT_OUT,
    VM_AUDIO_LINE_RIGHT_OUT,
    VM_AUDIO_HEADSET_LEFT_OUT,
    VM_AUDIO_HEADSET_RIGHT_OUT,
    VM_AUDIO_HEADSET_LINE_OUT,    ///< Headset + Line out
    VM_AUDIO_BT_MONO_OUT,         ///< BT (mono)
	VM_AUDIO_BT_STEREO_OUT,       ///< BT (stereo)
    VM_AUDIO_MAX_OUT    ///< no output needed
};

/**
 * \brief Audio frequency
 *
 *  Used in \ref vm_AudioManagerParam_t to specify the frequency of the signal.
 */
opaque_enum(vm_AudioFrequency_e_)
{
    VM_AUDIO_8_KHZ = 0,   ///< 8 kHz
    VM_AUDIO_11_025_KHZ,  ///< 11.025 kHz
    VM_AUDIO_12_KHZ,      ///< 12 kHz
    VM_AUDIO_16_KHZ,      ///< 16 kHz
    VM_AUDIO_22_050_KHZ,  ///< 22.050 kHz
    VM_AUDIO_24_KHZ,      ///< 24 kHz
    VM_AUDIO_32_KHZ,      ///< 32 kHz
    VM_AUDIO_44_1_KHZ,    ///< 44.1 kHz
    VM_AUDIO_48_KHZ,      ///< 48 kHz
    VM_AUDIO_64_KHZ,      ///< 64 kHz
    VM_AUDIO_96_KHZ       ///< 96 kHz
} ;

/**
 * \brief Audio HW Interface selection
 *
 *  Used in \ref vm_AudioManagerParam_t to specify the HW IF to use (I2S1, EAI_PCM, EAI_I2SE, EAI_DAI)
 */
opaque_enum(vm_AudioIF_e_)
{
    VM_AUDIO_IF_I2S = 0,    ///< primary I2S (ASL1) CPU/DSP
    VM_AUDIO_IF_I2S2,       ///< one-way I2S
    VM_AUDIO_IF_EAI_I2SE,   ///< secondary I2S (EAI): DSP only
    VM_AUDIO_IF_EAI_PCM_M_128,   ///< PCM Master BCLK=128kHz (EAI): DSP only
    VM_AUDIO_IF_EAI_PCM_M_256,   ///< PCM Master BCLK=256kHz (EAI): DSP only
    VM_AUDIO_IF_EAI_PCM_S_128,   ///< PCM Slave BCLK=128kHz (EAI): DSP only
    VM_AUDIO_IF_EAI_PCM_S_256,   ///< PCM Slaver BCLK=256kHz (EAI): DSP only
    VM_AUDIO_IF_EAI_DAI_0,   ///< DAI (EAI) in normal mode
    VM_AUDIO_IF_EAI_DAI_1,   ///< DAI (EAI) in test mode 1
    VM_AUDIO_IF_EAI_DAI_2,   ///< DAI (EAI) in test mode 2
    VM_AUDIO_IF_EAI_DAI_3   ///< DAI (EAI) in test mode 3
};

/**
 * \brief Audio Request usage
 *
 *  Used in \ref vm_AudioManagerParam_t to specify the channel configuration usage
 */
opaque_enum(vm_AudioCfgReq_e_)
{
    VM_AUDIO_CFG_REQ_NONE = 0,   ///< Request None
    VM_AUDIO_CFG_REQ_MO,         ///< Request Voice MO call
    VM_AUDIO_CFG_REQ_MT,         ///< Request Voice MT call
    VM_AUDIO_CFG_REQ_CC_TCH_IND, ///< Request CC TCH got notification, possible MO or MT
    VM_AUDIO_CFG_REQ_DTMF,       ///< Request DTMF
    VM_AUDIO_CFG_REQ_WAVE        ///< Request WAVE
};

/**
 * \brief Stereo channel playing mode
 *
 *  Used in \ref vm_AudioStereoDirection_t to specify the output direction of stereo channel
 */
opaque_enum(vm_AudioStereoMode_e_)
{
    VM_AUDIO_STEREO_TO_NE_WITHOUT_GSM_DL = 0,     ///< Only stereo to output (near end)
    VM_AUDIO_STEREO_TO_NE_WITH_GSM_DL,            ///< Stereo mixes with DSM DL (nead end)
    VM_AUDIO_STEREO_TO_FE_WITHOUT_ADC_UL,         ///< Only stereo to UL (far end)
    VM_AUDIO_STEREO_TO_FE_WITH_ADC_UL,            ///< Stereo mixed with ADC input (far end)
    VM_AUDIO_STEREO_TO_NE_FE_WITH_GSM_DL_ADC_UL,  ///< Stereo to both near end and far end
};

/**
 * \brief Audio processus parameter
 *
 *  used in \ref vm_audioManager_Open to specify the audio processus parameters.
 */
struct vm_AudioManagerParam_t_{
    vm_AudioFrequency_e   freq; ///< frequency of channel
    vm_AudioOutput_e output;    ///< output of channel
    vm_AudioInput_e input;      ///< input of channel
    vm_AudioGain_t inputGain;   ///< input gain of channel
    vm_AudioGain_t outputGain;  ///< output gain of channel
    bool stereo;                ///< if TRUE, stereo output will be used
    bool cpuPath;               ///< - TRUE if the audio should be accessed by the cpu ( mp3,...)
                                ///  - FALSE if the audio should be accessed by the dsp ( amr playback/recording, polyphonies playback,...)
    bool mixing;                ///< - TRUE if the audio output should be the mixing of microphone output and voice output
                                ///  - FALSE if the audio ouput should be only the voice output
    vm_AudioIF_e hwIF;          ///< HW IF in use for this channel
    u8 mailbox; ///< mailbox in which to send the headset messages
    vm_AudioCfgReq_e cfgReq;          ///< Configuration usage
};

/**
 * \brief Audio error codes returned by the interface functions.
 */
opaque_enum(vm_AudioMgrErrorCode_e_)
{
    AUDIO_ERR_PCM_ADD_DATA_FAILURE = -11,
    AUDIO_ERR_PCM_PLAY_FAILURE = -10,
    AUDIO_ERR_PCM_OPEN_FAILURE = -9,
    AUDIO_ERR_PCM_TCH_EXISTED = -8, ///< The TCH channel is still opened => can't operate PCM
    AUDIO_CLOSE_DELAYED = -7,   ///< The TCH channel is still opened => wait for close
    AUDIO_NO_SESSION,           ///< No more sessions available
    AUDIO_RESOURCE_ERR,         ///< Audio Resource allocation failed
    AUDIO_BAD_PARAM,            ///< Bad parameter
    AUDIO_BAD_SESSION,          ///< Bad session identifier
    AUDIO_FAILURE,              ///< Requested operation failed
    AUDIO_FIFO_FULL,            ///< PCM FIFO full
    AUDIO_OK= 0,                ///< No error
};

/**
 * \brief Audio channel state
 *
 *  used to check the state of the channel.
 */
opaque_enum(vm_AudioManagerChannelState_e_)
{
    CHANNEL_CLOSED= 0,      ///< channel is physically closed
    CHANNEL_CONFIGURED,     ///< channel is configured but not open
    CHANNEL_OPEN,           ///< channel is open (but may not be configured)
    CHANNEL_WAIT_TCH_CLOSE, ///< the channel is not closed because the TCH channel is still opened
    CHANNEL_MODIFIED,       ///< some channel parameters have been modified
    CHANNEL_RESTORE_VOICE   ///< channel is in MT ring tone close and restore voice
};

/**
 * \brief Audio messages types
 */
opaque_enum(vm_AudioManagerMsgType_e_)
{
    MSG_AUDIO_HEADSET_PLUGGED = 0,       ///< Sent when the headset is plugged
    MSG_AUDIO_HEADSET_PRESSED,           ///< Sent when the headset button is pressed
    MSG_AUDIO_HEADSET_RELEASED,          ///< Sent when the headset button is released
    MSG_AUDIO_HEADSET_UNPLUGGED          ///< Sent when the headset is unplugged
   ,MSG_AUDIO_HEADSET_LAST = MSG_AUDIO_HEADSET_UNPLUGGED
   ,MSG_AUDIO_SWITCH_OP_AMP
   ,MSG_AUDIO_TCH_OPEN_CB               /* Handling ABB task */
   ,MSG_AUDIO_TCH_CLOSE_CB              /* ABB task */
   ,MSG_AUDIO_SPEAKER_ENABLE_CB
   ,MSG_AUDIO_FADE_OUT_CB
   ,MSG_AUDIO_FADE_IN_CB
   ,MSG_AUDIO_TYPE_LAST
};

/**
 * \brief DTMF parameters
 */
struct vm_AudioDtmfParam_t_{
  u16 freq1; ///< frequency of first tone (in Hz)
  u16 gain1; ///< gain of first tone (0 = silent)
  u16 freq2; ///< frequency of second tone (in Hz)
  u16 gain2; ///< gain of second tone (0 = silent)
  u16 duration_ms; ///< duration of the DTMF in ms
};

/**
 * \brief Notification event sent to customer tasks
 */
/* MST Begin */
//moved MSG_AUDIO_SWITCH_OP_AMP to vm_AudioManagerMsgType_e
//#define MSG_AUDIO_SWITCH_OP_AMP         (MSG_AUDIO_HEADSET_LAST+1)
struct vm_AudioSwitchOpAmp_t_
{
    vm_AudioManagerMsgType_e nMsgType;
    vm_AudioChannel_e        channel; //OP not-off problem
    u8  bOnOff;
    u32 nDelay;
    u32 nExtInfo;
};

struct vm_AudioHwlCB_t_
{
    vm_AudioManagerMsgType_e nMsgType;
    vm_AudioChannel_e        channel;
    vm_AudioGain_t           gain;
    u8  bOnOff;
};
/* MST End */

/**
 * \brief Parameters needed to open a PCM Playback session (with \ref vm_audioManager_OpenPCMSession)
 */
struct vm_AudioManagerPCMParam_t_{
    u32  nMaxSize;    ///< max block size (blocks put in FIFO with \ref vm_audioManager_AddPCMData)
    u8   nMailbox;     ///< mailbox in which Fifo messages will be sent
    bool bStereoData;  ///< if TRUE, data will be read as 32 bits, otherwise as 16 bits
    bool bLeftChannel; ///< if mono data, the 16 bits data can be set in Left or rigth channel
};

/**
 * \brief PCM messages types
 */
opaque_enum(vm_AudioManagerPCMMsgType_e_)
{
    VM_AUDIO_PCM_FIFO_EMPTY = 0,  ///< PCM FIFO is empty, transfer has been stopped
    VM_AUDIO_PCM_BUFFER_CONSUMED  ///< a buffer has been consumed so that another buffer can be added
};

/**
 * \brief Parameters structure for messages sent to client's mailbox
 */
struct vm_AudioManagerPCMMsg_t_{
    vm_AudioManagerPCMMsgType_e msg_typ;  ///< message type
    u32 *buffer_used;      ///< buffer used by the PCM driver, that can be released
};

/**
 * \brief Parameters structure for Echo Cancelation management
 */
struct vm_AudioAECStatus_t_
{
  bool State; ///< State of the AEC algorithm: ENABLED or DISABLED
  u16  Features; ///< Bit fied containing the active feature of AEC algorithm (refer to hwlaud_ChangeAECFeature definition)
  u8   Type; ///< The AEC Active config
};

// end vm_audio_api.h
#endif // __VM_AUDIO_TYPES_H__

