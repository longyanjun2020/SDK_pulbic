/**
* @file DBL_Aud.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of audio.
*
*/

#ifndef __DBL_AUD_H__
#define __DBL_AUD_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
#include "ABL_Aud.h"
#include "HAL_AudResCtrl.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
#define __DBL_AUDIO_REC_DEBUG__

#if defined(__DBL_AUDIO_REC_DEBUG__) && !defined(__SMALL_ROM__)
#define DBL_DBG_MAX_HISTORY_ITEM_NUM 50

typedef struct
{
    bool tAudioRecDbgHistory[DBL_DBG_MAX_HISTORY_ITEM_NUM];
    u8 nLastIdx;
} DblAudioRecHistoryTab_t;
#endif

typedef enum DBL_AudPlayCmd_e_
{
    DBL_AUD_PLAY_CMD__STOP,
    DBL_AUD_PLAY_CMD__PAUSE,
    DBL_AUD_PLAY_CMD__RESUME,
    DBL_AUD_PLAY_CMD__NUM
} DBL_AudPlayCmd_e;

typedef struct DBL_AudPlayCmdParam_t_
{
    u16 uStopCmdParam;
    u16 uPauseCmdParam;
    u16 uResumeCmdParam;
} DBL_AudPlayCmdParam_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
s16 DBL_AudSetMute(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudSetVol(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudEnableSpeech(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudDisableSpeech(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudOpenSpeechSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudCloseSpeechSession(ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ s16 DBL_AudSetPath(AudChannel_e eChannel, AudPath_e ePath);
s16 DBL_AudSetVolume(AudChannel_e eChannel, u8 uVol, u8 uRange);
s16 DBL_AudSetBalance(AudChannel_e eChannel, s8 sBalance);
s16 DBL_AudPlayKeypadTone(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudPlayTone(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_AudPlayKeypadToneCb(u16 uSenderId, u32 uUserValue, esl_AudErrCode_e eErrCode, esl_AudInfo_t *pAudInfo);
void DBL_AudPlayToneCb(u16 uSenderId, u32 uUserValue, esl_AudErrCode_e eErrCode, esl_AudInfo_t *pAudInfo);
s16 DBL_AudPcmRecStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudPcmRecStop(ResMgr_CmdHdl_t pCurCmdHdl);

s16 DBL_AudInitPcmRecorder(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_AudPcmDataNotify(u16 *pData, u32 uDataLen, u32 uCusData);
void DBL_AudCmnCb(u16 uSenderId, u32 uUserValue, esl_AudErrCode_e eErrCode, esl_AudInfo_t *pAudInfo);
void DBL_MmlAudCmnCb(u16 uSenderId, u32 uUserValue, MmlAudioResult_e eErrCode, MmlAudioResponse_t *pAudInfo);
s16 DBL_AudSetMediaConfig(MediaConfigParm_t *pMediaConfigParm, bool bResetAudBuffer);
s16 DBL_MmlAudSetMediaConfig(MediaConfigParm_t *pMediaConfigParm, bool bResetAudBuffer);
s16 DBL_MmlAudPlayStream(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudPlayStreamAddBuffer(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudPlayMemory(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudPlayFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudStopPlayFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetID3V1Info(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetAdvancedInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetFileInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetStreamInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudSetPosition(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetPosition(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudSeekCancel(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudRecStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudRecStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudRecGetFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudStopPlay(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudPausePlay(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudResumePlay(ResMgr_CmdHdl_t pCurCmdHdl);

s16 DBL_AudSetPEQTableAddress(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudGetPEQTableAddress(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudSetUserPEQConfig(ResMgr_CmdHdl_t pCurCmdHdl);

s16 DBL_AudOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudOpenRecSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudCloseRecSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudInitRecorder(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudUninitRecorder(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudRegNotify(u16 uEvtType, void *pCusData, DBL_AudNotifyCb AudNotifyCb);
__SLDPM_FREE__ void DBL_MmlAudEvtNotify(u16 senderID, u32 userValue, MmlAudioNotify_t *pNotifyInfo);
void DBL_AudEvtNotify(u16 senderID, u32 userValue, DBL_AudNotifyInfo *pNotifyInfo);
void DBL_MmlAudUpdatePos(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
ABL_AudErrCode_e DBL_AudRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_AudErrCode_e DBL_MmlAudRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
s16 DBL_MmlAudSetRecordSetting(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudRecSaveFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudRecDiscardFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetMemoryInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetRecRemainTime(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudSetPEQTableAddress(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetPEQTableAddress(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_AudPcmRegCb(u16 uSenderId, u32 uUserValue, esl_AudErrCode_e eErrCode, esl_AudInfo_t *pAudInfo);
s16 DBL_MmlAudGetPlaybackCapability(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetRecordingCapability(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_AudErrCode_e DBL_AudGetSpectrumData(void *pSpectrumData, u32 uDataSize);
void DBL_AudSetSpectrumMode(bool bSpectrumOn);
ABL_AudErrCode_e DBL_AudSetMicLoopBack(bool bMicLoopBack);
s16 DBL_MmlAudSetPreProcessTableAddress(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudGetPreProcessTableAddress(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudSetMediaARPConfig(MediaARPConfigParm_t *pMediaARPConfigParm);
#if defined(__BLUETOOTH_A2DP_MMI__)
s16 DBL_MmlBtRegPosUpdateNotify(void);
s16 DBL_MmlBtRegPlayErrNotify(void);
s16 DBL_MmlAudStartBt(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudPauseBt(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudResumeBt(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudStopBt(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudEndBt(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudForceStopBt(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlAudForceStopM2(ResMgr_CmdHdl_t pCurCmdHdl);
#endif
s16 DBL_AudSetMusicMode(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_AudEnableLocalTone(bool bEnable);
s16 DBL_AudSetDistortedVoice(ResMgr_CmdHdl_t pCurCmdHdl);
#endif //__DBL_AUD_H__

