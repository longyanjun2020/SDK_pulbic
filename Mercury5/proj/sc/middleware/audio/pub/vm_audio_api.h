////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * \page AUDIO_MANAGER Audio Manager Interface
 *
 *
 * \section intro_sec Introduction
 *
 * This document describes the Audio Manager Interface
 *
 *  <hr>
 * \section SectionMMI2Audio 1. MMI to Audio Manager Interface
 *
 * \li \ref vm_audioManager_Open
 * \li \ref vm_audioManager_Close
 * \li \ref vm_audioManager_SetInGain
 * \li \ref vm_audioManager_GetInGain
 * \li \ref vm_audioManager_SetInput
 * \li \ref vm_audioManager_GetInput
 * \li \ref vm_audioManager_SetOutGain
 * \li \ref vm_audioManager_GetOutGain
 * \li \ref vm_audioManager_SetOutput
 * \li \ref vm_audioManager_GetOutput
 * \li \ref vm_audioManager_MuteInput
 * \li \ref vm_audioManager_SetFrequency
 * \li \ref vm_audioManager_GetFrequency
 * \li \ref vm_audioManager_IsHeadsetPlugged
 * \li \ref vm_audioManager_OpenDtmfSession
 * \li \ref vm_audioManager_PlayDtmf
 * \li \ref vm_audioManager_CloseDtmfSession
 * \li \ref vm_audioManager_OpenPCMSession
 * \li \ref vm_audioManager_StartPCMPlayback
 * \li \ref vm_audioManager_StopPCMPlayback
 * \li \ref vm_audioManager_AddPCMData
 * \li \ref vm_audioManager_IsPCMFifoFull
 * \li \ref vm_audioManager_ClosePCMSession
 *
 *  <hr>
 * \section SectionAudio2MMI 2. Audio Layer to MMI and HWL Interface
 *
 *  \li \ref MSG_AUDIO_HEADSET_PLUGGED      message sent when the headset is plugged
 *  \li \ref MSG_AUDIO_HEADSET_PRESSED      message sent when the headset button is pressed
 *  \li \ref MSG_AUDIO_HEADSET_RELEASED     message sent when the headset button is released
 *  \li \ref MSG_AUDIO_HEADSET_UNPLUGGED    message sent when the headset is unplugged
 *  \li \ref VM_AUDIO_PCM_MESSAGE_ID message sent when a PCM buffer is consumed
 *
 *  <hr>
 * \section Usage 3. Usage
 *
 *  The client first calls \ref vm_audioManager_Open to define the required audio channel operation and
 *  its associated parameters
 *
 *  Then he can call one or more other functions to define the input, output and gains of this audio channel.
 *
 *  He can also open a DTMF session, with \ref vm_audioManager_OpenDtmfSession, then play single or dual tones
 *  with \ref vm_audioManager_PlayDtmf. After all tones have been played, he can close the session with
 *  \ref vm_audioManager_CloseDtmfSession
 *
 *  During this Audio session, he can also play PCM wave buffer. To do so, he's got to:
 *  \li 1. Open a PCM playback session with \ref vm_audioManager_OpenPCMSession
 *  \li 2. Add data in the PCM FIFO using \ref vm_audioManager_AddPCMData less than \ref VM_AUDIO_NB_MAX_PCM_BUFFERS times,
 *  or until this function returns \ref AUDIO_FIFO_FULL
 *  \li 3. Start playback using \ref vm_audioManager_StartPCMPlayback
 *  \li 4. When receiving the \ref VM_AUDIO_PCM_MESSAGE_ID message with  \ref VM_AUDIO_PCM_BUFFER_CONSUMED type
 *  refill the Fifo with \ref vm_audioManager_AddPCMData, setting the last_data argument to TRUE when this is the last buffer
 *  \li 5. Stop playback with \ref vm_audioManager_StopPCMPlayback
 *  \li 6. Close the playback session with \ref vm_audioManager_ClosePCMSession
 *
 *  A call to \ref vm_audioManager_Close will close the channel and free all resources.
 *
 *
 *
 *  <hr>
 *  \section Notes 4. NOTES
 *
 *  Current limitations :
 *
 * <hr>
 * \section AudioSynchronisation 5. HWL/MMI coexistancy
 *
 *  HWL/MMI synchronisation for audio channels :
 *
 *  The MMI will usually only use the stereo channel, and the HWL will use the voice channel.
 *
 *  The MMI should open an audio channel prior to begin playback (using AudioInterface)
 *
 *
 */


/*!
 * \file  vm_audio.h
 * \brief MMI or HWL to audio manager
 *
 *  This file defines the audio manager interface that is offered to the  MMI and the HWL.
 *
 *  The interface allows to :
 *   \li use Stereo Channel to play music (MP3, Polyphony, AAC, WAV...)
 *   \li use Voice Channel to input/output voice or AMR voice memo.
 *   \li define inputs (micros) and outputs (Headset, Loudspeaker,...).
 *
 */
/**
 * \addtogroup Manager
 * @{
 */


#ifndef  __VM_AUDIO_API_H__
#define  __VM_AUDIO_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "vm_msgof.hc"
#include "mdl_aud_forward.h"
#include "mdl_aud_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
/**
 * \brief Audio input gain
 *
 *  Used in \ref vm_audioManager_SetInGain to specify the gain.
 */
#define VM_AUDIO_MIN_IN_GAIN_DB 0
#define VM_AUDIO_MAX_IN_GAIN_DB 15
/**
 * \brief Audio output gain
 *
 *  Used in \ref vm_audioManager_SetOutGain to specify the gain.
 */
#define VM_AUDIO_MIN_OUT_GAIN_DB -64
#define VM_AUDIO_MAX_OUT_GAIN_DB 12

/**
 * \brief Maximum level for DTMF tones
 */
#define VM_AUDIO__DTMF_MAX_LEVEL 0x7FF

/**
 * \brief Maximum frequency for DTMF tones (in Hz)
 */
#define VM_AUDIO__DTMF_MAX_FREQ 7999

/**
 * \brief Maximum duration for DTMF tones (in ms)
 */
#define VM_AUDIO__DTMF_MAX_DURATION (0x3FF/8)


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "vm_audio_message_define__.hi"
};

/**
 * \brief AEC
 */
#define VM_AUDIO_AEC_CONFIG_NB 3
#define VM_AUDIO_AEC_ALL_FEATURE         0x3FFF
#define VM_AUDIO_AEC_RESTORE_FEATURE     0x4000

/**
 * \brief Maximum number of PCM buffers
 */
#define VM_AUDIO_NB_MAX_PCM_BUFFERS         10

/*** Audio Downlink Dynamic Range Control */
#define VM_AUDIO_DRC_SCHEME_DISABLE         0
#define VM_AUDIO_DRC_SCHEME_CURVE2          1
#define VM_AUDIO_DRC_SCHEME_CURVE3          2
#define VM_AUDIO_DRC_SCHEME_TOTAL           3


/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
  *
  * \fn        const s32 AudioManager_Open(const vm_AudioChannel_e channel, const vm_AudioManagerParam_t  * param);
  * \brief        Opens the audio channel for music or voice purpose
  * \param    param the audio parameters. In the case of openning by Audio System of HWL, it may be NULL
  * \param    channel  the required audio channel
  * \return      an s32 value that is
   *         \li \ref AUDIO_OK                the function call was successfull.
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_Open(const vm_AudioChannel_e channel, const vm_AudioManagerParam_t  * param);


/**
  *
  * \fn        const s32 AudioManager_Config(const vm_AudioChannel_e channel, const vm_AudioManagerParam_t  * param);
  * \brief        Opens the audio channel for music or voice purpose
  * \param    param the audio parameters. In the case of openning by Audio System, it may be NULL
  * \param    channel  the required audio channel
  * \return      an s32 value that is
  *         \li \ref AUDIO_OK                the function call was successfull.
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_Config(const vm_AudioChannel_e channel, const vm_AudioManagerParam_t  * param);


/**
  *
  * \fn        const s32 AudioManager_SetInGain(const vm_AudioChannel_e channel, vm_AudioGain_t inputGain);
  * \brief        Sets the gain applied to the given audio channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    inputGain the gain to be applied to the current input  of the channel
  * \return      an s32 value that is
  *               - A positive value that is the channel identifier for the required operation
  *               if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_SetInGain(const vm_AudioChannel_e channel, vm_AudioGain_t inputGain);


/**
  *
  * \fn        const s32 AudioManager_GetInGain(const vm_AudioChannel_e channel, vm_AudioGain_t *inputGain);
  * \brief        Gets the gain applied to the given audio channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    inputGain: the gain currently applied to the input of the channel
  * \return   an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_GetInGain(const vm_AudioChannel_e channel, vm_AudioGain_t *inputGain);


/**
  *
  * \fn        const s32 AudioManager_SetInput(const vm_AudioChannel_e channel, vm_AudioInput_e input);
  * \brief      Sets the input type for the given channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    input: the input to be used for the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_SetInput(const vm_AudioChannel_e channel, vm_AudioInput_e input);


/**
  *
  * \fn        const s32 AudioManager_GetInput(const vm_AudioChannel_e channel, vm_AudioInput_e *input);
  * \brief        Gets the input type for the given audio channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    input: the input currently used for the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_GetInput(const vm_AudioChannel_e channel, vm_AudioInput_e *input);


/**
  *
  * \fn        const s32 AudioManager_SetOutGain(const vm_AudioChannel_e channel, vm_AudioGain_t outputGain);
  * \brief        Sets the output gain applied to the given audio channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    outputGain the gain to be applied to the current output of the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_SetOutGain(const vm_AudioChannel_e channel, vm_AudioGain_t outputGain);


/**
  *
  * \fn        const s32 AudioManager_GetOutGain(const vm_AudioChannel_e channel, vm_AudioGain_t *outputGain);
  * \brief        Gets the output gain applied to the given audio channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    outputGain: the gain currently applied to the output of the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_GetOutGain(const vm_AudioChannel_e channel, vm_AudioGain_t *outputGain);


/**
  *
  * \fn        const s32 AudioManager_SetOutput(const vm_AudioChannel_e channel, vm_AudioOutput_e output);
  * \brief      Sets the output type for the given channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    output: the output to be used for the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_SetOutput(const vm_AudioChannel_e channel, vm_AudioOutput_e output);


/**
  *
  * \fn        const s32 AudioManager_GetOutput(const vm_AudioChannel_e channel, vm_AudioOutput_e *output);
  * \brief        Gets the output type for the given audio channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    output: the output currently used for the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_GetOutput(const vm_AudioChannel_e channel, vm_AudioOutput_e *output);


/**
  *
  * \fn        const s32 AudioManager_MuteInput(const vm_AudioChannel_e channel, vm_AudioInput_e input, bool mute);
  * \brief      Mutes on or off the input type for the given channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    input: the input to be used for the channel
  * \param    mute: if TRUE? mutes the input, otherwise it unmutes it
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_MuteInput(const vm_AudioChannel_e channel, vm_AudioInput_e input, bool mute);


/**
  *
  * \fn        const s32 AudioManager_SetFrequency(const vm_AudioChannel_e channel, vm_AudioFrequency_e frequency);
  * \brief      Sets the frequency type for the given channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    frequency: the frequency to be used for the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_SetFrequency(const vm_AudioChannel_e channel, vm_AudioFrequency_e frequency);


/**
  *
  * \fn        const s32 AudioManager_GetFrequency(const vm_AudioChannel_e channel, vm_AudioFrequency_e *frequency);
  * \brief        Gets the frequency for the given audio channel
  * \param    channel: the channel identifier returned by \ref AudioManager_Open
  * \param    frequency: the frequency currently used for the channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_GetFrequency(const vm_AudioChannel_e channel, vm_AudioFrequency_e *frequency);


/**
  *
  * \fn          s32 AudioManager_Close(const vm_AudioChannel_e channel);
  * \brief       Closes the audio channel.
  *
*               After a call to this function, the channel is released and can no more be
  *               used.
  *
  * \param    channel the channel identifier returned by \ref AudioManager_Open
  * \return    a \ref s32 defining the function call result.
  *              \li \ref AUDIO_BAD_SESSION if the specified channel does not exist
  *         \li \ref AUDIO_OK                the function call was successfull.
  *
  */
s32 vm_audioManager_Close(const vm_AudioChannel_e channel);


/**
  *
  * \fn        const s32 AudioManager_Subscribe(u8 mailbox);
  * \brief        Used to subscribe to Audio Manager events (headset events for instance)
  * \param    [in] mailbox mailbox that should receive the Audio manager events
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *
  */
s32 vm_audioManager_Subscribe(u8 mailbox);


/**
  *
  * \fn          bool AudioManager_IsHeadsetPlugged(void);
  * \brief       Gets the state of the headset.
  * \return    a \ref bool defining the function call result.
  *              \li \ref TRUE if the headset is plugged
  *         \li \ref FALSE if the headset is not plugged.
  *
  */
bool vm_audioManager_IsHeadsetPlugged(void);


/**
  *
  * \fn        const s32 AudioManager_OpenDtmfSession(const vm_AudioChannel_e channel);
  * \brief      Opens a DTMF session on the given channel
  * \param    channel: the required audio channel
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_OpenDtmfSession(const vm_AudioChannel_e channel);


/**
  *
  * \fn        const s32 AudioManager_PlayDtmf(const vm_AudioChannel_e channel, vm_AudioDtmfParam_t param);
  * \brief      Plays a DTMF with the given parameter on the given channel
  * \param    channel: the required audio channel
  * \param    parameters: parameters of the desired DTMF (frequencies, gains and duration)
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_PlayDtmf(const vm_AudioChannel_e channel, const vm_AudioDtmfParam_t *param);


/**
  *
  * \fn        const s32 AudioManager_CloseDtmfSession(const vm_AudioChannel_e channel);
  * \brief      Closes the DTMF session on the given channel
  * \param    channel: the required audio channel
  * \param    param: parameters of the desired DTMF (frequencies, gains and duration
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_CloseDtmfSession(const vm_AudioChannel_e channel);


/**
  *
  * \fn        const s32 AudioManager_OpenPCMSession(vm_AudioManagerPCMParam_t *param);
  * \brief      Opens a PCM Playback session
  * \param    param [in]: all parameters required for PCM playback
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *                   .
  *
  */
s32 vm_audioManager_OpenPCMSession(const vm_AudioManagerPCMParam_t *param);


/**
  *
  * \fn        const s32 AudioManager_StartPCMPlayback(s32 session);
  * \brief      Starts an open PCM Playback session
  * \param    session [in]: the session handler returned by \ref AudioManager_OpenPCMSession
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *
  */
s32 vm_audioManager_StartPCMPlayback(s32 session);


/**
  *
  * \fn        const s32 AudioManager_PausePCMPlayback(s32 session);
  * \brief      Pauses an already started PCM Playback session
  * \param    session [in]: the session handler returned by \ref AudioManager_OpenPCMSession
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *
  */
s32 vm_audioManager_PausePCMPlayback(s32 session);


/**
  *
  * \fn        const s32 AudioManager_ResumesPCMPlayback(s32 session);
  * \brief      Resumes an already paused PCM Playback session
  * \param    session [in]: the session handler returned by \ref AudioManager_OpenPCMSession
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *
  */
s32 vm_audioManager_ResumePCMPlayback(s32 session);


/**
  *
  * \fn        const s32 AudioManager_StopPCMPlayback(s32 session);
  * \brief      Stops the started PCM playback
  * \param    session [in]: the session handler returned by \ref AudioManager_OpenPCMSession
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *
  */
s32 vm_audioManager_StopPCMPlayback(s32 session);


/**
 *
 * \fn     const s32 AudioManager_AddPCMData(s32 session, u32* new_data, u32 nb_data, bool last_data);
 * \brief This function adds audio data in the FIFO
 * \param [in] session: the session handler returned by \ref AudioManager_OpenPCMSession
 * \param [in] new_data  pointer to data buffer to add in the FIFO
 * \param [in] nb_data   number of items
 * \param [in] last_data if TRUE, this are the last data of the transmission
 * \return   an s32 value that is
                                                                                                                        *               - \ref AUDIO_OK  if the function call is successfull
 *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
 *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
 *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
 *
 */
s32 vm_audioManager_AddPCMData(s32 session, u32* new_data, u32 nb_data, bool last_data);


/**
  *
  * \fn        const bool AudioManager_IsPCMFifoFull(s32 session);
  * \brief          Checks if the data FIFO is full or not. If not, the client can call \ref AudioManager_AddPCMData again
  * \param    session [in]: the session handler returned by \ref AudioManager_OpenPCMSession
  * \return      an boolean value that is
  *               - TRUE if the FIFO is full
  *               - FALSE otherwise
  *
  */
bool vm_audioManager_IsPCMFifoFull(s32 session);


/**
  *
  * \fn        const s32 AudioManager_ClosePCMSession(s32 session);
  * \brief      Closes the PCM session
  * \param    session [in]: the session handler returned by \ref AudioManager_OpenPCMSession
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise. The error code is one of :
  *                   - \ref AUDIO_NO_SESSION  if there are no more channels available.
  *                   - \ref AUDIO_BAD_PARAM  one of the parameters is not correct </a>
  *
  */
s32 vm_audioManager_ClosePCMSession(s32 session);


/**
  *
  * \fn        const s32 AudioManager_SetAECStatus(vm_AudioAECStatus_t *StatusPtr);
  * \brief     Configures the Echo Cancellation feature (enables or disables + parameters)
  * \param    StatusPtr [in]: parameters to set
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise.
  *
  */
s32 vm_audioManager_SetAECStatus(const vm_AudioAECStatus_t *StatusPtr);


/**
  *
  * \fn        const s32 AudioManager_GetAECStatus(vm_AudioAECStatus_t *StatusPtr);
  * \brief     Gets the Echo Cancellation pamaters (enabled or disabled + parameters)
  * \param    StatusPtr [out]: parameters to get
  * \return      an s32 value that is
  *               - \ref AUDIO_OK  if the function call is successfull
  *               - A negative value that defines the error code of the function call otherwise.
  *
  */
s32 vm_audioManager_GetAECStatus(vm_AudioAECStatus_t *StatusPtr);


/**
  *
  * \fn        s32 AudioManager_StartAudioLoop(u16 loopType);
  * \brief     Launch audio loop tests
  * \param     loopType[in]: Loop Type : VOCODER or FIFO loop
  * \return    an s32 value that is
  *            - \ref AUDIO OK
  *
  */
s32 vm_audioManager_StartAudioLoop(u16 loopType);


/**
  *
  * \fn        s32 AudioManager_StopAudioLoop(u16 loopType);
  * \brief     Stop audio loop tests
  * \return    an s32 value that is
  *            - \ref AUDIO OK
  *
  */
s32 vm_audioManager_StopAudioLoop(void);


/**
  *
  * \fn        s32 AudioManager_GetChannelStatus(vm_AudioChannel_e channel, vm_AudioManagerChannelState_e *channelStatus);
  * \brief     Gets the Channel Status (Close, Open, Configured, Wait TCH Close)
  * \param    channel[in]: channel used
  * \param    channelStatus[out]: gives the status of the channel
  * \return      an s32 value that is
  *                    - \ref AUDIO OK
  *
  */
s32 vm_audioManager_GetChannelStatus(vm_AudioChannel_e channel, vm_AudioManagerChannelState_e *channelStatus);

 /**
  *  @}
  */
#endif //__VM_AUDIO_API_H__
