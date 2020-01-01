/**
* @file mmi_voicecallsrv.h
*
* Class Id: CLSID_VOICECALLSRV
*
* @version $Id$
*/
#ifndef __MMI_VOICECALLSRV_H__
#define __MMI_VOICECALLSRV_H__
/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mediasrv_common.h"
#include "mmi_audioenvsrv.h"
/*-------------------------------------------------------------------------*/
#define INHERIT_IVoiceCallSrv(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IVoiceCallSrv);

#define IVoiceCallSrv_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), IVoiceCallSrv)->QueryInterface(pICntlr, id, pp, po)
#define IVoiceCallSrv_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), IVoiceCallSrv)->HandleEvent(pICntlr, e, p1, p2)

typedef enum VoiceCallAudPath_e_
{
    VOICECALL_SRV_PATH__HANDSET
   ,VOICECALL_SRV_PATH__HEADSET
   ,VOICECALL_SRV_PATH__SPEAKER
   ,VOICECALL_SRV_PATH__BT_HEADSET
   ,VOICECALL_SRV_PATH__RIGHT_SPEAKER
   ,VOICECALL_SRV_PATH__LEFT_SPEAKER,
} VoiceCallAudPath_e;

typedef enum VoiceCallSrvVolLevel_e_
{
   VOICECALL_SRV_VOLLEVEL__DEFAULT  = AUDIOENVSRV_VOLLEVEL__DEFAULT,
   VOICECALL_SRV_VOLLEVEL__OFF      = AUDIOENVSRV_VOLLEVEL__OFF,
   VOICECALL_SRV_VOLLEVEL__MIN      = AUDIOENVSRV_VOLLEVEL__MIN,
   VOICECALL_SRV_VOLLEVEL__0        = AUDIOENVSRV_VOLLEVEL__0,
   VOICECALL_SRV_VOLLEVEL__1        = AUDIOENVSRV_VOLLEVEL__1,
   VOICECALL_SRV_VOLLEVEL__2        = AUDIOENVSRV_VOLLEVEL__2,
   VOICECALL_SRV_VOLLEVEL__3        = AUDIOENVSRV_VOLLEVEL__3,
   VOICECALL_SRV_VOLLEVEL__4        = AUDIOENVSRV_VOLLEVEL__4,
   VOICECALL_SRV_VOLLEVEL__5        = AUDIOENVSRV_VOLLEVEL__5,
   VOICECALL_SRV_VOLLEVEL__6        = AUDIOENVSRV_VOLLEVEL__6,
   VOICECALL_SRV_VOLLEVEL__7        = AUDIOENVSRV_VOLLEVEL__7,
   VOICECALL_SRV_VOLLEVEL__8        = AUDIOENVSRV_VOLLEVEL__8,
   VOICECALL_SRV_VOLLEVEL__MAX      = AUDIOENVSRV_VOLLEVEL__MAX
} VoiceCallSrvVolLevel_e;

typedef enum VoiceCallSrvChannel_e_
{
    VOICECALL_SRV_CHAN__VOICE       = AUDIOENVSRV_CHAN__VOICE,          //AUD_CHAN__VOICE = 0,
    VOICECALL_SRV_CHAN__STEREO      = AUDIOENVSRV_CHAN__STEREO,         //AUD_CHAN__STEREO,
    VOICECALL_SRV_CHAN__AUX         = AUDIOENVSRV_CHAN__AUX,            //AUD_CHAN__AUX,
    VOICECALL_SRV_CHAN__VOICE_SLAVE = AUDIOENVSRV_CHAN__VOICE_SLAVE,    //AUD_CHAN__VOICE_SLAVE,
    VOICECALL_SRV_CHAN__NUM         = AUDIOENVSRV_CHAN__NUM,            //AUD_CHAN__NUM,
    VOICECALL_SRV_CHAN__INVALID     = AUDIOENVSRV_CHAN__INVALID         //AUD_CHAN__INVALID
}
VoiceCallSrvChannel_e;

typedef enum VoiceCallAudMusicMode_e_
{
    VOICECALL_SRV_MUSIC_MODE__ALLOW_LOCAL_MUSIC_ONLY        //ABL_AUD_MUSIC_MODE__TO_NE_WITHOUT_GSM_DL
    ,VOICECALL_SRV_MUSIC_MODE__ALLOW_LOCAL_MUSIC_DOWN_LINK  //ABL_AUD_MUSIC_MODE__TO_NE_WITH_GSM_DL
    ,VOICECALL_SRV_MUSIC_MODE__ALLOW_REMOTE_MUSIC_ONLY      //ABL_AUD_MUSIC_MODE__TO_FE_WITHOUT_ADC_UL
    ,VOICECALL_SRV_MUSIC_MODE__ALLOW_REMOTE_MUSIC_UP_LINK   //ABL_AUD_MUSIC_MODE__TO_FE_WITH_ADC_UL
    ,VOICECALL_SRV_MUSIC_MODE__ALLOW_ALL                    //ABL_AUD_MUSIC_MODE__TO_NE_FE_WITH_GSM_UL_ADC_DL
} VoiceCallMusicMode_e;

typedef enum VoiceCallSrvDistortedVoice_e_
{
    VOICECALL_SRV_DISTORTED_VOICE__NORMAL = 0 //ABL_AUD_DISTORTED_VOICE__NORMAL
    ,VOICECALL_SRV_DISTORTED_VOICE__KID       //ABL_AUD_DISTORTED_VOICE__KID,
    ,VOICECALL_SRV_DISTORTED_VOICE__GIRL      //ABL_AUD_DISTORTED_VOICE__GIRL,
    ,VOICECALL_SRV_DISTORTED_VOICE__WOMAN     //ABL_AUD_DISTORTED_VOICE__WOMAN,
    ,VOICECALL_SRV_DISTORTED_VOICE__MALE      //ABL_AUD_DISTORTED_VOICE__MALE,
    ,VOICECALL_SRV_DISTORTED_VOICE__MAN       //ABL_AUD_DISTORTED_VOICE__MAN,
    ,VOICECALL_SRV_DISTORTED_VOICE__BASS      //ABL_AUD_DISTORTED_VOICE__BASS,
    ,VOICECALL_SRV_DISTORTED_VOICE__NUM = VOICECALL_SRV_DISTORTED_VOICE__BASS
} VoiceCallSrvDistortedVoice_e;

typedef struct VoiceCallSrv_t_
{
    DECLARE_FUNCTBL(IVoiceCallSrv);
    u32 nRefCnt;
} VoiceCallSrv_t;

MAE_Ret VoiceCallSrvNew(MAE_ClsId nId, void **ppObj);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Voice Call Service interface
/////////////////////////////////////////////////////////////////////////////////////////////////////////
MAE_Ret VoiceCallSrvSuspendBackgroundAudio(VoiceCallSrv_t *pVoiceCallSrv, u32 nInstanceID);
MAE_Ret VoiceCallSrvResumeBackgroundAudio(VoiceCallSrv_t *pVoiceCallSrv, u32 nInstanceID);
MAE_Ret VoiceCallSrvEnableSpeech(VoiceCallSrv_t *pVoiceCallSrv, u32 nInstanceID);
MAE_Ret VoiceCallSrvDisableSpeech(VoiceCallSrv_t *pVoiceCallSrv, u32 nInstanceID);
MAE_Ret VoiceCallSrvMuteVoice(VoiceCallSrv_t *pVoiceCallSrv, u32 nInstanceID, boolean bMute);
MAE_Ret VoiceCallSrvSetChannelVolume(VoiceCallSrv_t *pVoiceCallSrv, u16 nAppId, VoiceCallSrvChannel_e eChannel, VoiceCallSrvVolLevel_e eVolume);
MediaSrvErrCode_e VoiceCallSrvSetMusicMode(VoiceCallSrv_t *pVoiceCallSrv, u32 nAppInstance, VoiceCallMusicMode_e eMode);
MAE_Ret VoiceCallSrvSetDistortedVoice(VoiceCallSrv_t *pVoiceCallSrv, u32 nAppInstance, VoiceCallSrvDistortedVoice_e eDistortedVoice);
MediaSrvErrCode_e VoiceCallSrvEnableLocalTone(VoiceCallSrv_t *pVoiceCallSrv, u32 nAppInstance, boolean bEnable);
/*-------------------------------------------------------------------------*/
#endif /* __MMI_VOICECALLSRV_H__ */
