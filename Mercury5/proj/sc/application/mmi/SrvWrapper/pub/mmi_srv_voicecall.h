/**
* @file    mmi_srv_voicecall.h
* @brief  The document describes the service wrapper interface of Voice Call Service
*
*
* @author
* @version $Id:$
*/

#ifndef __MMI_SRV_VOICECALL_H__
#define __MMI_SRV_VOICECALL_H__
/*-------------------------------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_audioenvsrv.h"
#include "mmi_voicecallsrv.h"

MAE_Ret SrvVoiceCallCreate(SrvClient_t *pClient, s32 *pData);
MAE_Ret SrvVoiceCallDestroy(SrvClient_t *pClient, s32 *pData);

MAE_Ret SrvVoiceCallSuspendBackgroundAudio(void);
MAE_Ret SrvVoiceCallResumeBackgroundAudio(void);
MAE_Ret SrvVoiceCallEnableSpeech(void);
MAE_Ret SrvVoiceCallDisableSpeech(void);
MAE_Ret SrvVoiceCallMuteVoice(void);
MAE_Ret SrvVoiceCallUnmuteVoice(void);
MAE_Ret SrvVoiceCallSetAudioPath(AudioEnvSrvPrefAudPath_e eAudPath);
MAE_Ret SrvVoiceCallSetChannelVolume(VoiceCallSrvChannel_e eChannel, VoiceCallSrvVolLevel_e eVolume);
MediaSrvErrCode_e SrvVoiceCallSetMusicMode(VoiceCallMusicMode_e eMode);
MAE_Ret SrvVoiceCallSetDistortedVoice(VoiceCallSrvDistortedVoice_e eDistortedVoiceMode);
MediaSrvErrCode_e SrvVoiceCallEnableLocalTone(void);
MediaSrvErrCode_e SrvVoiceCallDisableLocalTone(void);
#endif /* __MMI_SRV_VOICECALL_H__ */


