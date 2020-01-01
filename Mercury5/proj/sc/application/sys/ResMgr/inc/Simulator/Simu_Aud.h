/**
* @file Simu_Aud.h
*
* This header file defines the interface of lower layer device simulation for audio
*
*/
#ifndef __SIMU_AUD_H__
#define __SIMU_AUD_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"
#include "ABL_Aud.h"
// for WB test
#include "srv_resmgr_mmlaudio_types.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct Simu_AudCbRemap_t_
{
    u16 uTimerId;
    ABL_AudCb AudCb;
} Simu_AudCbRemap_t;

typedef struct SimuAudWBUserData_t_
{
    u32 AudWBId;
    u32 nData;
    MmlAudioUCParam_t AudioUCParam;
}SimuAudWBUserData_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_AudPlayKeypadToneCb(void *pUserData);
void Simu_AudPlayToneCb(void *pUserData);
void Simu_AudStopDTMFCb(void *pUserData);
void Simu_AudPlayStreamCb(void *pUserData, u16 uFormat);
void Simu_AudPlayStreamAddBufferCb(void *pUserData);
void Simu_AudPlayMemoryCb(void *pUserData, u16 uFormat);
void Simu_AudPlayFileCb(void *pUserData);
void Simu_AudGetID3V1InfoCb(void *pUserData);
void Simu_AudGetAdvInfoCb(ABL_AudGetAdvInfo_t *pGetAdvInfo, void *pUserData);
void Simu_AudGetFileInfoCb(void *pUserData);
void Simu_AudGetStreamInfoCb(void *pUserData);
void Simu_AudGetMemoryInfoCb(void *pUserData);
void Simu_AudGetRecRemainTimeCb(void *pUserData);
void Simu_AudSetPosCb(void *pUserData);
void Simu_AudGetPosCb(void *pUserData);
void Simu_AudRecStartCb(void *pUserData);
void Simu_AudRecStopCb(void *pUserData);
void Simu_AudRecGetFileCb(void *pUserData);
void Simu_AudStopPlayCb(void *pUserData);
void Simu_AudPausePlayCb(void *pUserData);
void Simu_AudResumePlayCb(void *pUserData);
void Simu_AudPcmRecStartCb(void *pUserData);
void Simu_AudPcmRecStopCb(void *pUserData);
void Simu_AudSetMusicModeCb(void *pUserData);
void Simu_AudSetDistortedVoiceCb(void *pUserData);
void Simu_AudPcmRegCb(void *pUserData);
void Simu_AudStartBtCb(void *pUserData);
void Simu_AudPauseBtCb(void *pUserData);
void Simu_AudResumeBtCb(void *pUserData);
void Simu_AudStopBtCb(void *pUserData);
void Simu_AudEndBtCb(void *pUserData);
void Simu_AudForceStopBtCb(void *pUserData);
void Simu_AudGetPlaybackCapabilityCb(void *pUserData);
void Simu_AudGetRecordingCapabilityCb(void *pUserData);
void Simu_AudWBTc1(void *pUserData);
void Simu_AudWBTc2(void *pUserData);
void Simu_AudWBTc3(void *pUserData);
void Simu_AudWBTc4(void *pUserData);
#endif //__SIMU_AUD_H__


