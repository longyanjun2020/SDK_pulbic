/**
* @file    mmi_srv_audiorecorder.h
* @brief  The document describes the service wrapper interface of audio recorder
*
*/

#ifndef __MMI_SRV_AUDIORECORDER_H__
#define __MMI_SRV_AUDIORECORDER_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_audiorecordersrv.h"
#include "mmi_mediasrv_common.h"

/**
SrvAudioRecCreateService
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv AudioRecorder client.
@param[in]      pData                   init used data // non use in MAE

@retval MAE_RET_SUCCESS           If successful.
@retval MAE_RET_FAILED            If an error happen.
*/
MAE_Ret SrvAudioRecCreateService(SrvClient_t *pClient, s32 *pData);

/**
SrvAudioRecDestroyService
@brief  The interface is use to destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv AudioRecorder client.
@param[in]      pData                   init used data // non use in MAE

@retval MAE_RET_SUCCESS           If successful.
@retval MAE_RET_FAILED            If an error happen.
*/
MAE_Ret SrvAudioRecDestroyService(SrvClient_t *pClient, s32 *pData);

/**
SrvAudioRecSuspendBackgroundMusic
@brief  To suspend background playing music
*/
MAE_Ret SrvAudioRecSuspendBackgroundMusic(void);

/**
SrvAudioRecResumeBackgroundMusic
@brief  To resume background playing music
*/
MAE_Ret SrvAudioRecResumeBackgroundMusic(void);

/**
SrvAudioRecStartRecord
@brief  Start to record

@param[in]      eCodecType        Record codec type
@param[in]      eRecPath        	Record path
@param[in]      pUrl                 	The URL to store recorded file
@param[in]      pfnCb                  Start record call back function pointer.

@retval MAE_RET_SUCCESS        If successful.
@retval MAE_RET_FAILED            If an error happen.
@retval MAE_RET_FS_FULL         If the SD space full
*/
MAE_Ret SrvAudioRecStartRecord(MediaSrvAudCodec_e eCodecType, MediaSrvRecPath_e eRecPath, const MAE_WChar* pUrl, AudioRecSrvCmnCb pfnCb);

/**
SrvAudioRecStopRecord
@brief  Stop recording

@param[in]      pfnCb                  Stop record call back function pointer.
*/
MAE_Ret SrvAudioRecStopRecord(AudioRecSrvStopRecCb pfnCb);

/**
SrvAudioRecStartStreamRecord
@brief  Start streaming record

@param[in]      pfnCb                  Start streaming record call back function pointer.
*/
MAE_Ret SrvAudioRecStartStreamRecord(AudioRecSrvCmnCb pfnCb);

/**
SrvAudioRecStopStreamRecord
@brief  Stop streaming record

@param[in]      pfnCb                  Stop streaming record call back function pointer.
*/
MAE_Ret SrvAudioRecStopStreamRecord(AudioRecSrvCmnCb pfnCb);

/**
SrvAudioRecSetGetRecStreamDataCb
@brief  Set a call back function to get stream record data

@param[in]      pfnGetData         Get stream record data call back function pointer.
@param[in]      nCusData
*/
MAE_Ret SrvAudioRecSetGetRecStreamDataCb(AudioRecSrvGetRecStreamData pfnGetData, u32 nCusData);

/**
SrvAudioRecSetRecStatusCb
@brief  Set a call back function to listen record status event

@param[in]      pfnRecStatusNotify	Record status notify call back function pointer.
@param[in]      nCusData
*/
MAE_Ret SrvAudioRecSetRecStatusCb(AudioRecSrvStatusNotify pfnRecStatusNotify, u32 nCusData);

/**
SrvAudioRecSetInterruptNotifyCb
@brief  Set a call back function to listen interrupt event

@param[in]      pfnInterruptNotify		Interrupt notify call back function pointer.
@param[in]      nCusData
*/
MAE_Ret SrvAudioRecSetInterruptNotifyCb(MediaSrvInterruptNotifyCb pfnInterruptNotify, u32 nCusData);

#endif /* __MMI_SRV_AUDIORECORDER_H__ */


