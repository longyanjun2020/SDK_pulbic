/**
* @file mmi_audiosrv.h
*
* Class Id: CLSID_AUDIOSRV
*
* @version $Id$
*/
#ifndef __MMI_AUDIOSRV_H__
#define __MMI_AUDIOSRV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
/*-------------------------------------------------------------------------*/
#include "mmi_mediasrv_common.h"

typedef enum AudioSrvStreamMode_e_
{
    AUDIOSRV_STREAM_MODE__START = 0
   ,AUDIOSRV_STREAM_MODE__STREAMING
   ,AUDIOSRV_STREAM_MODE__END
   ,AUDIOSRV_STREAM_MODE__START_END
,     //Non-streaming mode (one rawdata block)
    AUDIOSRV_STREAM_MODE__NUM
} AudioSrvStreamMode_e;

typedef enum AudioSrvPlayMode_e_
{
    AUDIOSRV_PLAY__ONCE = 0
   ,/**< Play once */
    AUDIOSRV_PLAY__REPEAT
   ,/**< Repeat playing until user stops melody */
    AUDIOSRV_PLAY__NUM
} AudioSrvPlayMode_e;

typedef enum AudioSrvToneID_e_
{
    AUDIOSRV_TONE_ID__0 = 0
   ,/**< Index '0' DTMF Tone */
    AUDIOSRV_TONE_ID__1 = 1
   ,/**< Index ...  DTMF Tone */
    AUDIOSRV_TONE_ID__2 = 2
   ,AUDIOSRV_TONE_ID__3 = 3
   ,AUDIOSRV_TONE_ID__4 = 4
   ,AUDIOSRV_TONE_ID__5 = 5
   ,AUDIOSRV_TONE_ID__6 = 6
   ,AUDIOSRV_TONE_ID__7 = 7
   ,AUDIOSRV_TONE_ID__8 = 8
   ,AUDIOSRV_TONE_ID__9 = 9
   ,AUDIOSRV_TONE_ID__A = 10
   ,AUDIOSRV_TONE_ID__B = 11
   ,AUDIOSRV_TONE_ID__C = 12
   ,AUDIOSRV_TONE_ID__D = 13
   ,/**< Index 'D' DTMF Tone */
    AUDIOSRV_TONE_ID__STAR = 14
   ,/**< Index '*' DTMF Tone */
    AUDIOSRV_TONE_ID__HASH = 15
   ,/**< Index '#' DTMF Tone */
    AUDIOSRV_TONE_ID__BEEP1 = 16
   ,AUDIOSRV_TONE_ID__BEEP2 = 17
   ,AUDIOSRV_TONE_ID__WAITINGCALL = 18
   ,AUDIOSRV_TONE_ID__ACC_PLUG_IN = 19
   ,AUDIOSRV_TONE_ID__ACC_PLUG_OUT = 20
   ,AUDIOSRV_TONE_ID__OUTGOING = 21
   ,AUDIOSRV_TONE_ID__ALARM = 22
   ,AUDIOSRV_TONE_ID__CALL_END = 23
   ,AUDIOSRV_TONE_ID__NUM
} AudioSrvToneID_e;

typedef enum AudioSrvToneVolumeLevel_e_
{
    AUDIOSRV_TONE_VOLLEVEL__DEFAULT = 4
   ,AUDIOSRV_TONE_VOLLEVEL__MIN = 0
   ,AUDIOSRV_TONE_VOLLEVEL__0 = AUDIOSRV_TONE_VOLLEVEL__MIN
   ,AUDIOSRV_TONE_VOLLEVEL__1 = 1
   ,AUDIOSRV_TONE_VOLLEVEL__2 = 2
   ,AUDIOSRV_TONE_VOLLEVEL__3 = 3
   ,AUDIOSRV_TONE_VOLLEVEL__4 = 4
   ,AUDIOSRV_TONE_VOLLEVEL__5 = 5
   ,AUDIOSRV_TONE_VOLLEVEL__6 = 6
   ,AUDIOSRV_TONE_VOLLEVEL__7 = 7
   ,AUDIOSRV_TONE_VOLLEVEL__8 = 8
   ,AUDIOSRV_TONE_VOLLEVEL__MAX = AUDIOSRV_TONE_VOLLEVEL__8
} AudioSrvToneVolLevel_e;

typedef enum AudioSrvPlayStatusEvent_e_
{
    AUDIOSRV_PLAYSTATUS__PLAY_END = 0
   ,AUDIOSRV_PLAYSTATUS__PLAY_ERROR
   ,AUDIOSRV_PLAYSTATUS__PLAY_TICK
   ,AUDIOSRV_PLAYSTATUS__NUM
} AudioSrvPlayStatusEvent_e;

typedef struct AudioSrvFileInfo_t_
{
    u32 nFormat;
    u32 nSampleRate;   //audio sample rate
    u32 nBitrate;
    boolean bStereo;
    u32 nTotalTime;
} AudioSrvFileInfo_t;

typedef void (*AudioSrvCb)(void *pThis, MediaSrvErrCode_e eErrorCode);
typedef void (*AudioSrvFileInfoCb)(void *pThis, MediaSrvErrCode_e eErrorCode, u32 nCusData, AudioSrvFileInfo_t *pAudFileInfo);
typedef void (*AudioSrvPlayStatusCb)(void *pThis, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);

/*-------------------------------------------------------------------------*/
/**
 * IAUDIOSRV Interfaces
 */
#define INHERIT_IAUDIOSRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IAUDIOSRV);

#define IAUDIOSRV_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), IAUDIOSRV)->QueryInterface(pICntlr, id, pp, po)
#define IAUDIOSRV_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), IAUDIOSRV)->HandleEvent(pICntlr, e, p1, p2)

MAE_Ret AudioSrvNew(MAE_ClsId nId, void **ppObj);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Audio Service interface
/////////////////////////////////////////////////////////////////////////////////////////////////////////
boolean AudioSrvQueryAudioMixingSupport(bool * pUserAudioMixingSupported);
MAE_Ret AudioSrvSuspendBackgroundMusic(IAUDIOSRV *pAudioSrv, u16 nAppId);
MAE_Ret AudioSrvResumeBackgroundMusic(IAUDIOSRV *pAudioSrv, u16 nAppId);
MAE_Ret AudioSrvGetAudFileInfo(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, MAE_WChar *pURL, u32 nCusData, AudioSrvFileInfoCb pfnCallBack);
MAE_Ret AudioSrvPlay(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, MAE_WChar *pURL, u32 nPosition, AudioSrvPlayMode_e ePlayMode, AudioSrvCb pfnCallBack);
MAE_Ret AudioSrvPlayStream(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, void *pRawData, u32 nDataLength, MediaSrvMimeType_e eMimeType, AudioSrvStreamMode_e eStreamMode, AudioSrvPlayMode_e ePlayMode, AudioSrvCb pfnCallBack);
MAE_Ret AudioSrvPlayTone(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, AudioSrvToneID_e eToneID, AudioSrvToneVolLevel_e eVolRange, AudioSrvToneVolLevel_e eVolume);
MAE_Ret AudioSrvPlayKeypadTone(IAUDIOSRV *pAudioSrv, AudioSrvToneID_e eToneID, AudioSrvToneVolLevel_e eVolRange, AudioSrvToneVolLevel_e eVolume);
MAE_Ret AudioSrvEnableKeypadTone(IAUDIOSRV *pAudioSrv, u16 nAppId);
MAE_Ret AudioSrvDisableKeypadTone(IAUDIOSRV *pAudioSrv, u16 nAppId);
MAE_Ret AudioSrvPause(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, AudioSrvCb pfnCallBack);
MAE_Ret AudioSrvResume(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, AudioSrvCb pfnCallBack);
void AudioSrvForceResume(IAUDIOSRV *pAudioSrv, u16 nAppId);
MAE_Ret AudioSrvStop(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, AudioSrvCb pfnCallBack);
MAE_Ret AudioSrvSetPlayStatusNotifyCb(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, u32 nCusData, AudioSrvPlayStatusCb pfnCallBack);
MAE_Ret AudioSrvSetInterruptNotifyCb(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, u32 nCusData, MediaSrvInterruptNotifyCb pfnCallBack);
MAE_Ret AudioSrvSetAccessoryNotifyCb(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, u32 nCusData, MediaSrvAccessoryNotifyCb pfnCallBack);
#ifdef __LANTERN_BY_AUDIO__
MAE_Ret AudioSrvSetSpectrumCb(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, u32 nCusData, MediaSrvSpectrumCb pfnCallBack);
MAE_Ret AudioSrvSetSpectrumCbInterval(IAUDIOSRV *pAudioSrv, u32 nInstanceID, u16 nAppId, u16 nSpectrumInterval);
#endif

#endif /* __MMI_AUDIOSRV_H__ */
