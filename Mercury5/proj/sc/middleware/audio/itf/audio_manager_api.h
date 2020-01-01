/*!
 * \file  audio_manager_api.h
 * \brief MMI or HWL to audio manager
 *
 *  This file defines the audio manager interface that is offered to the  MMI and the HWL.
 *
 *  The interface allows to :
 *   \li use Stereo Channel to play music (MP3, Polyphony, AAC, WAV...)
 *   \li use Voice Channel to input/output voice or AMR voice memo.
 *   \li define inputs (micros) and outputs (Headset, Loudspeaker,...).
 *   \li play DTMF
 *   \li play PCM buffers
 *
 */


#ifndef  __AUDIO_MANAGER_API_H__
#define  __AUDIO_MANAGER_API_H__

#include "vm_types.ht"
#include "vm_audio_api.h"

s32 AudioManager_Open(const vm_AudioChannel_e channel, vm_AudioManagerParam_t  * param);
s32 AudioManager_Config(const vm_AudioChannel_e channel, const vm_AudioManagerParam_t  * param);
s32 AudioManager_GetConfig(const vm_AudioChannel_e channel, const vm_AudioManagerParam_t  * param);
s32 AudioManager_SpeakerEnable(const vm_AudioChannel_e channel, bool enable);
s32 AudioManager_SetInGain(const vm_AudioChannel_e channel, vm_AudioGain_t inputGain);
s32 AudioManager_GetInGain(const vm_AudioChannel_e channel, vm_AudioGain_t *inputGain);
s32 AudioManager_SetInput(const vm_AudioChannel_e channel, vm_AudioInput_e input);
s32 AudioManager_GetInput(const vm_AudioChannel_e channel, vm_AudioInput_e *input);
s32 AudioManager_SetOutGain(const vm_AudioChannel_e channel, vm_AudioGain_t outputGain);
s32 AudioManager_GetOutGain(const vm_AudioChannel_e channel, vm_AudioGain_t *outputGain);
s32 AudioManager_SetBalance(const vm_AudioChannel_e channel, vm_AudioGain_t leftGain, vm_AudioGain_t rightGain);
s32 AudioManager_SetOutput(const vm_AudioChannel_e channel, vm_AudioOutput_e output);
s32 AudioManager_GetOutput(const vm_AudioChannel_e channel, vm_AudioOutput_e *output);
s32 AudioManager_MuteInput(const vm_AudioChannel_e channel, vm_AudioInput_e input, bool mute);
s32 AudioManager_SetFrequency(const vm_AudioChannel_e channel, vm_AudioFrequency_e frequency);
s32 AudioManager_GetFrequency(const vm_AudioChannel_e channel, vm_AudioFrequency_e *frequency);
s32 AudioManager_SetRecordFrequency(vm_AudioFrequency_e frequency);
s32 AudioManager_GetRecordFrequency(vm_AudioFrequency_e *frequency);
s32 AudioManager_Close(const vm_AudioChannel_e channel);
s32 AudioManager_Subscribe(u8 mailbox);
bool AudioManager_IsHeadsetPlugged(void);
void AudioManager_HeadsetEvent(vm_AudioManagerMsgType_e event);
s32 AudioManager_OpenDtmfSession(const vm_AudioChannel_e channel);
s32 AudioManager_PlayDtmf(const vm_AudioChannel_e channel, const vm_AudioDtmfParam_t *param);
s32 AudioManager_CloseDtmfSession(const vm_AudioChannel_e channel);
s32 AudioManager_OpenPCMSession(const vm_AudioManagerPCMParam_t *param);
s32 AudioManager_StartPCMPlayback(s32 session);
s32 AudioManager_PausePCMPlayback(s32 session);
s32 AudioManager_ResumePCMPlayback(s32 session);
s32 AudioManager_StopPCMPlayback(s32 session);
s32 AudioManager_AddPCMData(s32 session, u32* new_data, u32 nb_data, bool last_data);
bool AudioManager_IsPCMFifoFull(s32 session);
s32 AudioManager_ClosePCMSession(s32 session);
s32 AudioManager_SetAECStatus(const vm_AudioAECStatus_t *StatusPtr);
s32 AudioManager_GetAECStatus(vm_AudioAECStatus_t *StatusPtr);
s32 AudioManager_GetChannelStatus(vm_AudioChannel_e channel, vm_AudioManagerChannelState_e *channelStatus);
s32 AudioManager_SetCpuPath(vm_AudioChannel_e channel, bool cpuPath);
s32 AudioManager_GetCpuPath(vm_AudioChannel_e channel, bool *CpuPath);
s32 AudioManager_StartAudioLoop(u16 loopType);
s32 AudioManager_StopAudioLoop(void);
s32 AudioManager_TCHOpenCB(const vm_AudioChannel_e channel);
s32 AudioManager_TCHCloseCB(const vm_AudioChannel_e channel);
s32 AudioManager_SpeakerEnableCB(const vm_AudioChannel_e channel, const bool enable);
s32 AudioManager_FadeOutCB(const vm_AudioChannel_e channel, const vm_AudioGain_t gain);
s32 AudioManager_FadeInCB(const vm_AudioChannel_e channel, const vm_AudioGain_t gain);
vm_AudioMgrErrorCode_e AudioManager_ConfigSTGain(vm_AudioGain_t *stGaindBTbl);
vm_AudioMgrErrorCode_e AudioManager_ConfigDRCScheme(u8 drc);
vm_AudioMgrErrorCode_e AudioManager_ConfigOutputDriverGainBoost(u8 *outputDrvGainBoostTbl);
s32 AudioManager_SetMixing(const vm_AudioChannel_e channel, const bool mixing);
s32 AudioManager_SetStereoMode(const vm_AudioStereoMode_e mode);

#endif //__AUDIO_MANAGER_API_H__
