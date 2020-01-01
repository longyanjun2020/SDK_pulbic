/**
* @file mmi_audiorecordersrv.h
* Class Id: CLSID_AUDIORECORDERSRV
*/
#ifndef __MMI_AUDIORECORDERSRV_H__
#define __MMI_AUDIORECORDERSRV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mediasrv_common.h"

#define __AUDIO_REC_DEBUG__

#if defined(__AUDIO_REC_DEBUG__) && !defined(__SMALL_ROM__)
#define AUDIO_SRV_DBG_MAX_HISTORY_ITEM_NUM 50
typedef enum AudioRecSrvOpType_e_
{
    AUDIO_REC_SRV_OP__INIT_REC,
    AUDIO_REC_SRV_OP__UNINIT_REC,
    AUDIO_REC_SRV_OP__START_REC,
    AUDIO_REC_SRV_OP__START_REC_CB,
    AUDIO_REC_SRV_OP__STOP_REC,
    AUDIO_REC_SRV_OP__STOP_REC_CB,
    AUDIO_REC_SRV_OP__SAVE_FILE,
    AUDIO_REC_SRV_OP__SAVE_FILE_CB,
    AUDIO_REC_SRV_OP__SAVE_FILE_NOT_INFORM,
    AUDIO_REC_SRV_OP__SAVE_FILE_NOT_INFORM_CB,
    AUDIO_REC_SRV_OP__RECEIVE_INTERRUPT_NOTIFY,
    AUDIO_REC_SRV_OP__RECEIVE_STATUS_NOTIFY
} AudioRecSrvOpType_e;

typedef struct AudioRecSrvHistoryItem_t_
{
    u8 eOpType;
    u8 nResult;
    u16 nLine;
    u32 nExtInfo;
} AudioRecSrvHistoryItem_t;

typedef struct AudioRecSrvHistoryTab_t_
{
    AudioRecSrvHistoryItem_t tAudioRecDbgHistory[AUDIO_SRV_DBG_MAX_HISTORY_ITEM_NUM];
    u8 nLastIdx;
} AudioRecSrvHistoryTab_t;
#endif

#define AUDIO_RECORDER_FILENAME_LENGTH  64

typedef struct AudioRecSrvFileInfo_t_
{
    MediaSrvFileFormat_e efileFormat;
    u16 *pFileName;
    u16 nFileNameLen;
} AudioRecSrvFileInfo_t;

/*
    1.Service will notify its client of error cause besides status typed
      when driver returned MEDIA_RSP_ID__AUDIO_REC_ERROR status indication.
    2.Service will notify its client of position information besides status
      indication when driver returned MEDIA_RSP_ID__AUDIO_REC_POSITION_UPDATE
    3.Service will notify its client of recorded file information besides status
      indication when driver returned MEDIA_RSP_ID__AUDIO_REC_SAPCE_FULL
*/
typedef struct AudioRecSrvStatusNotifyInfo_t_
{
    union
    {
        u32 nErrCode;
        u32 nPosition;
        AudioRecSrvFileInfo_t tFileInfo;
    } uParam;
} AudioRecSrvStatusNotifyInfo_t;

typedef enum AudioRecSrvStatusInd_e_
{
    AUDIO_REC_SRV_STATUS__SAPCE_FULL
   ,AUDIO_REC_SRV_STATUS__ERROR
   ,AUDIO_REC_SRV_STATUS__POSITION_UPDATE
} AudioRecSrvStatusInd_e;

typedef void (*AudioRecSrvCmnCb)(void *pThis, MediaSrvErrCode_e nErrCode);
typedef void (*AudioRecSrvStopRecCb)(void *pThis, MediaSrvErrCode_e nErrCode, AudioRecSrvFileInfo_t *pFileInfo);
typedef void (*AudioRecSrvGetRecStreamData)(void *pThis, u16 *pData, u32 nDataLen, u32 nUserData);
typedef void (*AudioRecSrvStatusNotify)(void *pThis, u32 nCusData, AudioRecSrvStatusInd_e eStatus, AudioRecSrvStatusNotifyInfo_t *pInfo);

typedef struct AudioRecSrvGetRecStreamData_t_
{
    u32 nSrvClientInsId;
    u32 nCusData;
    AudioRecSrvGetRecStreamData pfnGetData;
} AudioRecSrvGetRecStreamData_t;

typedef struct AudioRecSrvSetRecStatusNotifyData_t_
{
    u32 nSrvClientInsId;
    u32 nCusData;
    AudioRecSrvStatusNotify pfnRecStatusNotify;
} AudioRecSrvSetRecStatusNotifyData_t;

typedef struct AudioRecSrvSetInterruptNotifyData_t_
{
    u32 nSrvClientInsId;
    u32 nCusData;
    MediaSrvInterruptNotifyCb pfnInterruptNotify;
} AudioRecSrvSetInterruptNotifyData_t;

/**
 * IAudioRecSrv Interfaces
 */
#define INHERIT_IAudioRecSrv(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IAudioRecSrv);

#define IAudioRecSrvQueryInterface(pICntlr, id, pp, po) GET_FUNCTBL((pICntlr), IAudioRecSrv)->QueryInterface(pICntlr, id, pp, po)
#define IAudioRecSrvHandleEvent(pICntlr, e, p1, p2) GET_FUNCTBL((pICntlr), IAudioRecSrv)->HandleEvent(pICntlr, e, p1, p2)

/**
* Application structure
*/
typedef struct AudioRecSrv_t_
{
    DECLARE_FUNCTBL(IAudioRecSrv);
    u32 nRefCnt;
    u16 nAppId;
    AudioRecSrvSetRecStatusNotifyData_t *pRecStatusNotifyData;
    AudioRecSrvSetInterruptNotifyData_t *pInterruptNotifyData;
    AudioRecSrvGetRecStreamData_t *pGetRecStreamData;
	boolean bErrorOccurred;
} AudioRecSrv_t;

/**
 * Audio Recorder Service Interface
 */
MAE_Ret AudioRecSrvNew(MAE_ClsId nId, void **ppObj);
MAE_Ret AudioRecSrvSuspendBackgroundMusic(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId);
MAE_Ret AudioRecSrvResumeBackgroundMusic(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId);
MAE_Ret AudioRecSrvStartRecord(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId, MediaSrvAudCodec_e eCodecType, MediaSrvRecPath_e eRecPath, const MAE_WChar *pUrl, AudioRecSrvCmnCb pfnCb);
MAE_Ret AudioRecSrvStopRecord(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId, AudioRecSrvStopRecCb pfnCb);
MAE_Ret AudioRecSrvStartStreamRecord(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId, AudioRecSrvCmnCb pfnCb);
MAE_Ret AudioRecSrvStopStreamRecord(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId, AudioRecSrvCmnCb pfnCb);
void AudioRecSrvSetGetRecStreamDataCb(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId, AudioRecSrvGetRecStreamData pfnGetData, u32 nCusData);
void AudioRecSrvSetRecStatusCb(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId, AudioRecSrvStatusNotify pfnRecStatusNotify, u32 nCusData);
void AudioRecSrvSetInterruptNotifyCb(AudioRecSrv_t *pAudioRecSrv, u32 nSrvClient, u16 nAppId, MediaSrvInterruptNotifyCb pfnInterruptNotify, u32 nCusData);

#endif /* __MMI_AUDIORECORDERSRV_H__ */


