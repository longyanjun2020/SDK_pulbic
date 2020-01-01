////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_aud_core_api.h
* @version
* @brief   header file
*
*/

#ifndef __MDL_AUD_CORE_API_H__
#define __MDL_AUD_CORE_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_rtk_ho.h"
#include "drv_vm_io_types.h"
// #include mdl_audio.h" is replaced by the following three header
//#include "hal_audio.h"
#include "vm_audio_api.h"
#include "mdl_audio_pub_api.h"

#include "mdl_aud_pub_api.h"
#include "mdl_aud_dma_api.h"
#include "mdl_aud_cp_pub_api.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "mdl_aud_forward.h"
#include "drv_audio_pub_forward.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/
extern cus_ErrCode_e MsPollSem(MsSemId_e semID);

/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __MDL_AUD_CORE_C__
#define	DefExtern
#else
#define	DefExtern	extern
#endif

#define  MDL_AUD_SYNC_BLOCK          MsConsumeSem(VOC_SYNC_SEM)
#define  MDL_AUD_SYNC_UNBLOCK        MsProduceSem(VOC_SYNC_SEM)

#define  MDL_AUD_REENTRY_LOCK        MsConsumeSem(VOC_REENTRY_LOCK_SEM)
#define  MDL_AUD_REENTRY_UNLOCK      MsProduceSem(VOC_REENTRY_LOCK_SEM)

#define  MDL_AUD_ENTER_MSG_CS        MsConsumeSem(VOC_MSG_SEM)
#define  MDL_AUD_TEST_ENTER_MSG_CS   MsPollSem(VOC_MSG_SEM)
#define  MDL_AUD_LEAVE_MSG_CS        MsProduceSem(VOC_MSG_SEM)

#define  MDL_AUD_ENTER_PCM_CS        MsConsumeSem(VOC_PCM_SEM)
#define  MDL_AUD_TEST_ENTER_PCM_CS   MsPollSem(VOC_PCM_SEM)
#define  MDL_AUD_LEAVE_PCM_CS        MsProduceSem(VOC_PCM_SEM)

#define  MDL_AUD_PERIODIC_OP_CHECK_TIME    2000

#define  MDL_AUD_PCM_DUMP_TIME       20

#define  __MDL_AUD_PCM_RECORD_USE_DSP__

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/
DefExtern u32  gnPcmHandle;
DefExtern u32  gnPcmConsumedBlock;
DefExtern u16  gnVocOpStatus;

DefExtern MdlAudPcmStateMachine_e       gePcmState;
DefExtern MdlAudHandlerStateMachine_e   geMdlAudHandlerState;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MdlAudRet_e  MdlAudGetVoicePath           (MdlAudOutput_e eOutput, MdlAudProfile_e *pePath);
MdlAudRet_e  MdlAudGetVoiceGain           (MdlAudOutput_e eOutput, u16 nVgrValue, u8 *pnLevel, MdlAudGain_t *ptOutGain, MdlAudGain_t *ptInGain);
MdlAudRet_e  MdlAudSetMicGain             (MdlAudOutput_e eOutput, u8 nInGainValue);
MdlAudRet_e  MdlAudGetSpeakerAmpStatus    (VmIoState_e *peState);
MdlAudRet_e  MdlAudCheckAudioPowerStatus  (bool *pbDrvStatus, bool *pbHwStatus);

MdlAudRet_e  MdlAudPcmOpen                (u8 *pnBuffer, u32 nlength, u32 *pnHandle);
MdlAudRet_e  MdlAudPcmClose               (u32 nHandle);
MdlAudRet_e  MdlAudPcmPlay                (u32 nHandle);
MdlAudRet_e  MdlAudPcmAddDataToDma        (u32 nHandle);
MdlAudRet_e  MdlAudPcmAddBuffer           (u32 nHandle, u8 *pnBuffer, u32 nLength, bool bLast, MdlAudCb_t *ptAudCb);
MdlAudRet_e  MdlAudPcmAddFirstBuffer      (u32 nHandle, bool bLast, MdlAudCb_t *ptAudCb);
MdlAudRet_e  MdlAudPcmPlayCmd             (u32 nHandle, u32 nPrim);
MdlAudRet_e  MdlAudPcmRegNotify           (MdlAudNotifyType_e eNotifyType, MdlAudNotifyCb_t tNotifyCb);
MdlAudRet_e  MdlAudPcmStopHandler         (u32 nHandle, MdlAudNotifyType_e eStopType);
MdlAudRet_e  MdlAudPcmDmaEventHandler     (u32 nHandle, vm_AudioManagerPCMMsg_t *ptMsg);
MdlAudRet_e  MdlAudTonePlay               (MdlAudDTMF_e eToneID);
MdlAudRet_e  MdlAudToneStop               (void);
MdlAudRet_e  MdlAudToneSetVol             (u8 nVolRange, u8 nVolLevel);
MdlAudRet_e  MdlAudSetDtmfId                  (MdlAudDTMF_e eToneID);
MdlAudRet_e  MdlAudSwitchSpeakerAmplifier     (MdlAudChannel_e channel, bool bOn, u32 nDelay, u32 nExtInfo);
MdlAudRet_e  MdlAudSwitchSpeakerAmp           (MdlAudChannel_e channel, bool bOn);
MdlAudRet_e  MdlAudVocSetMute                 (bool bMute);
MdlAudRet_e  MdlAudVocGetMute                 (bool *pbMute);
MdlAudRet_e  MdlAudVocSetPath                 (MdlAudChannel_e eChanId, MdlAudPath_e eAudPath);
MdlAudRet_e  MdlAudVocGetChannelSetting       (MdlAudChannel_e channel, MdlAudInput_e *input, MdlAudOutput_e *output);
MdlAudRet_e  MdlAudVocSetVol                  (MdlAudChannel_e eChanId, u8 nRange, u8 nVolume);
MdlAudRet_e  MdlAudVocSetBalance              (MdlAudChannel_e eChanId, s8 nRange, s8 nLevel);
MdlAudRet_e  MdlAudVocGetChannelPath          (MdlAudChannel_e channel, MdlAudPath_e *pPath);
MdlAudRet_e  MdlAudVocEnableLocalTone         (bool bEnable);
MdlAudRet_e  MdlAudVocEnableStreamRec         (bool bEnable);
MdlAudRet_e  MdlAudVocEnableSpeech            (bool bEnable);
MdlAudRet_e  MdlAudVocAudioOpen               (MdlAudChannel_e eChannel, MdlAudType_e eAudioType);
MdlAudRet_e  MdlAudVocAudioClose              (MdlAudChannel_e eChannel, MdlAudType_e eAudioType);
MdlAudRet_e  MdlAudVocAudioConfig  (MdlAudChannel_e eMdlChannel, MdlAudioManagerParam_t tMdlParam);
MdlAudRet_e  MdlAudVocAudioSetInGain          (MdlAudChannel_e eChannel, MdlAudGain_t tInputGain);
MdlAudRet_e  MdlAudVocAudioSetInput           (MdlAudChannel_e eChannel, MdlAudInput_e eInput);
MdlAudRet_e  MdlAudVocAudioGetOutput          (MdlAudChannel_e eChannel, MdlAudOutput_e *peOutput);
MdlAudRet_e  MdlAudVocAudioSetOutput          (MdlAudChannel_e eChannel, MdlAudOutput_e eOutput);
MdlAudRet_e  MdlAudVocAudioGetOutputGain      (MdlAudChannel_e eChannel, MdlAudType_e eAudioType, MdlAudGain_t *ptOutputGain);
MdlAudRet_e  MdlAudVocAudioSetFrequency       (MdlAudChannel_e eChannel, MdlAudSamplingRate_e eSamplingRate);
MdlAudRet_e  MdlAudVocAudioSetRecFrequency    (MdlAudSamplingRate_e eSamplingRate);
MdlAudRet_e  MdlAudVocAudioGetInfo            (MdlAudConfig_t *pAudConfig, MdlAudType_e *pAudState);
MdlAudRet_e  MdlAudVocAudioSpeakerEnable      (MdlAudChannel_e eChannel, bool bEnable);
MdlAudRet_e  MdlAudVocAudioSpeakerStatus      (MdlAudChannel_e eChannel, bool *pbStatus);
MdlAudRet_e  MdlAudVocAudioGainFadeOut        (MdlAudChannel_e eChannel, MdlAudGain_t tGain);
MdlAudRet_e  MdlAudVocAudioGainFadeIn         (MdlAudChannel_e eChannel, MdlAudGain_t tGain);
MdlAudRet_e  MdlAudVocGetVoiceOutGain         (MdlAudOutput_e eOutput, MdlAudVoiceType_e type, u8  nVolRange, u8 nVolLevel, MdlAudGain_t *ptOutGain);
MdlAudRet_e  MdlAudVocGetKeypadToneGain       (MdlAudOutput_e eOutput, MdlAudGain_t *ptOutGain);
MdlAudRet_e  MdlAudVocGetMediaOutGain         (MdlAudPath_e ePath, MdlAudType_e eType, u8 nVolRange, u8 nVolLevel, MdlAudGain_t *ptOutGain);
MdlAudRet_e  MdlAudVocGetMediaInGain          (MdlAudType_e eType, MdlAudInput_e eInput, MdlAudGain_t *ptOutGain);
MdlAudRet_e  MdlAudVocGetAuxOutGain           (MdlAudOutput_e eOutput, u8  nVolRange, u8 nVolLevel, MdlAudGain_t *ptOutGain);
MdlAudRet_e  MdlAudVocCheckAudioChannelStatus (bool *pbStatus);
MdlAudRet_e  MdlAudVocRegPcmRecordCb          (MdlAudPcmRecordCb *pfnCb, u32 nUserData);
MdlAudRet_e  MdlAudVocSetAuxVol               (void);
MdlAudRet_e  MdlAudVocSetMusicMode            (MdlAudMusicMode_e eMode);
MdlAudRet_e  MdlAudSetDistortedVoice          (MdlAudDistortedVoice_e eMode);
MdlAudRet_e  MdlAudDrvChannelToMdlChannel     (DrvAudioChannel_e eDrvChannel, MdlAudChannel_e *peMdlChannel);
MdlAudRet_e  MdlAudMdlChannelToDrvChannel     (MdlAudChannel_e eMdlChannel, DrvAudioChannel_e *peDrvChannel);
MdlAudRet_e  MdlAudDrvInputToMdlInput         (DrvAudioInput_e eDrvInput, MdlAudInput_e *peMdlInput);
MdlAudRet_e  MdlAudMdlInputToDrvInput         (MdlAudInput_e eMDlInput, DrvAudioInput_e *peDrvInput);
MdlAudRet_e  MdlAudDrvOutputToMdlOutput       (DrvAudioOutput_e eDrvOutput, MdlAudOutput_e *peMdlOutput);
MdlAudRet_e  MdlAudMdlOutputToDrvOutput       (MdlAudOutput_e eMdlOutput, DrvAudioOutput_e *peDrvOutput);
MdlAudRet_e  MdlAudDrvConfigToMdlConfig       (DrvAudioManagerParam_t tParam, MdlAudioManagerParam_t *ptParam);
MdlAudRet_e  MdlAudMdlConfigToDrvConfig       (MdlAudioManagerParam_t tParam, DrvAudioManagerParam_t *ptParam);
MdlAudRet_e  MdlAudDrvSamplingRateToMdlSamplingRate (DrvAudioSamplingRate_e eDrvSamplingRate, MdlAudSamplingRate_e *peMdlSamplingRate);
MdlAudRet_e  MdlAudMdlSamplingRateToDrvSamplingRate (MdlAudSamplingRate_e eMdlSamplingRate, DrvAudioSamplingRate_e *peDrvSamplingRate);
MdlAudRet_e  MdlAudHeadsetEventHandler        (void);
MdlAudRet_e  MdlAudDmaRecRegCallback          (MdlAudDmaCbFn_t tFullCb, MdlAudDmaCbFn_t tOverrunCb, MdlAudDmaCbFn_t tUnderrunCb);
MdlAudRet_e  MdlAudDmaPlayRegCallback         (MdlAudDmaCbFn_t tEmptyCb, MdlAudDmaCbFn_t tOverrunCb, MdlAudDmaCbFn_t tUnderrunCb);
MdlAudRet_e  MdlAudDma2PlayRegCallback        (MdlAudDmaCbFn_t tEmptyCb, MdlAudDmaCbFn_t tOverrunCb, MdlAudDmaCbFn_t tUnderrunCb);
MdlAudRet_e  MdlAudDmaEventHandler            (void);
MdlAudRet_e  MdlAudCpRegCallback              (MdlAudCPCbFn_t tCpCb);
MdlAudRet_e  MdlAudCpEventHandler             (u8 bufferId);
MdlAudRet_e  MdlAudVocEmAudioTest             (bool bOn, MdlAudChannel_e eChannel, MdlAudInput_e eInput, MdlAudOutput_e eOutput, MdlAudGain_t tInputGain, MdlAudGain_t tOutputGain);
MdlAudRet_e  MdlAudRegGainInfoCb              (MdlAudGainInfoCbFn_t tGainInfoCb);
MdlAudRet_e  MdlAudDeregGainInfoCb            (MdlAudGainInfoCbFn_t tGainInfoCb);
MdlAudRet_e  MdlAudHandleGainInfoCb           (void);
MdlAudRet_e  MdlAudRegA2dpStatusCb            (MdlAudA2dpStatusCbFn_t tA2dpStatusCb);
MdlAudRet_e  MdlAudDeregA2dpStatusCb          (MdlAudA2dpStatusCbFn_t tA2dpStatusCb);
bool         MdlAudQueryA2dpStatus            (void);
MdlAudRet_e  MdlAudGetExtAmpGainOffset        (bool *pbExtAmp, s8 *pnGainOffset);

MdlAudRet_e MdlAudVocDmaPlayPowerSavingPause(void);
MdlAudRet_e MdlAudVocDmaPlayPowerSavingResume(void);
MdlAudRet_e MdlAudVocDmaPlayReset(void);
MdlAudRet_e MdlAudVocDmaPlayPowerSavingReset(void);

MdlAudRet_e  MdlAudMicLoopBackEnable(bool bOn, MdlAudInput_e eInput, MdlAudOutput_e eOutput, MdlAudGain_t tInputGain, MdlAudGain_t tOutputGain);
MdlAudRet_e MdlAudGetStereoState(MdlAudType_e *eType);

#if defined(__SPEECH_CTA_CHEATING_MODE__)
void MdlAudSetCTASTMute(void);
void MdlAudSetCTASTRes(void);
#endif

#ifdef __MIC_IN_CHANGED_TO_HANDSET_IF_3_SEGMENT_HEADSET__
MdlAudRet_e  MdlAud3SegmentHeadsetIndication  (void);
MdlAudRet_e  MdlAudGet3SegmentHeadsetStatus   (MdlAudHeadsetType_e *peHeadsetType);
#endif

bool MdlAudIsOpAmpNecessary (DrvAudioOutput_e eOutput);

#endif //__MDL_AUD_CORE_API_H__

