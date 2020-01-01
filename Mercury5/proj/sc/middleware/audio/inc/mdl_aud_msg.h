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
* @file    mdl_aud_msg.h
* @version
* @brief   header file
*
*/

#ifndef __MDL_AUD_MSG_H__
#define __MDL_AUD_MSG_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mdl_aud_pub_api.h"
#include "mdl_aud_types.h"
#include "mdl_aud_int_types.h"
#include "mdl_aud_dma_types.h"
#include "mdl_aud_dma_api.h"
#include "mdl_aud_cp_api.h"
#include "vm_audio_api.h"
#include "sys_rtk_vmoshi.h"

#if defined(__UPGRADE_DSP_R2__) && !defined(__SDK_SIMULATION__)
#include "api_mrl_au.h"
#endif // __UPGRADE_DSP_R2__

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define  vm_msg_t  vm_msg_t

/**
 *  @brief This enumeration defines the synchronous/asynchronous primtive mechanism
 */
typedef enum {
	MDL_AUD_SYNC,         /**< Synchronous transaction */
	MDL_AUD_ASYNC         /**< Asynchronous transaction */
} MdlAudTransType_e;


typedef struct
{
	MdlAudCb_t         *ptAudCb;
    MdlAudRet_e        *peErrCode;
	MdlAudTransType_e   TransType;   /**< Transaction type */

	union
	{
        MdlAudStreamParam_t            tStreamParam;
        MdlAudDTMF_e                   eToneId;
        MdlAudDtmfParam_t              tToneParam;
        MdlAudRegNotify_t              tAudRegNotifyParam;
        MdlAudSwitchSpeakerAmp_t       tSwitchSpeakerAmpParam;
        MdlAudSetMute_t                tMuteParam;
        MdlAudSetPath_t                tPathParam;
        MdlAudSetVol_t                 tVolParam;
        MdlAudSetBalance_t             tBalanceParam;
        MdlAudOpen_t                   tOpenParam;
        MdlAudClose_t                  tCloseParam;
        MdlAudTchConfig_t              tConfigParam;
        MdlAudSetInGain_t              tSetInGainParam;
        MdlAudSetInput_t               tSetInputParam;
        MdlAudGetOutput_t              tGetOutputParam;
        MdlAudSetOutput_t              tSetOutputParam;
        MdlAudSetFrequency_t           tSetFreqParam;
        MdlAudSetRecFrequency_t        tSetRecFreqParam;
        MdlAudSwitchTchStatus_t        tSwitchTchStatusParam;
        MdlAudGetInfo_t                tGetInfoParam;
        MdlAudEnableSpeech_t           tEnableSpeechParam;
        MdlAudSpeakerEnable_t          tSpeakerParam;
        MdlAudGainFadeOut_t            tFadeOutParam;
        MdlAudGainFadeIn_t             tFadeInParam;
        MdlAudGetPath_t                tGetPathParam;
        MdlAudRegPcmRecordCb_t         tRegPcmRecordCbParam;
        MdlAudSetMusicModeParam_t      tMusicModeParam;
        MdlAudSetDistortedVoiceParam_t tDistortedVoiceParam;
        MdlAudEnableLocalTone_t        tEnableLocalToneParam;
        MdlAudGetOutputGain_t          tGetOutputGainParam;
        MdlAudDmaRecSetBufAddr_t       tDmaRecSetBufAddr;
        MdlAudDmaRecSetBufThreshold_t  tDmaRecSetBufThreshold;
        MdlAudDmaRecSetSamplingRate_t  tDmaRecSetSamplingRate;
        MdlAudDmaRecRegCallback_t      tDmaRecRegCallback;
        MdlAudDmaRecGetBufInfo_t       tDmaRecGetBufInfo;
        MdlAudDmaRecReadData_t         tDmaRecReadData;
        MdlAudDmaPlaySetBufAddr_t      tDmaPlaySetBufAddr;
        MdlAudDmaPlaySetBufThreshold_t tDmaPlaySetBufThreshold;
        MdlAudDmaPlaySetSamplingRate_t tDmaPlaySetSamplingRate;
        MdlAudDmaPlayRegCallback_t     tDmaPlayRegCallback;
        MdlAudDmaPlayGetBufInfo_t      tDmaPlayGetBufInfo;
        MdlAudDmaPlayWriteData_t       tDmaPlayWriteData;
        MdlAudCpRegCallback_t          tCpRegCallback;
        MdlAudCpBufferId_t             tCpBufferAId;
        MdlAudCpBufferId_t             tCpBufferBId;
        MdlAudEmTest_t                 tEmTest;
        MdlAudGainInfoCbFn_t           tGainInfoCb;
  } tParam;
} MdlAudCmd_t;

/**
 *  @brief This structure defines the message body
 */
typedef union
{
    MdlAudCmd_t               AudCmd;        /**< audio command container */
    vm_osTimerMsgBody_t       AudTimerId;    /**< audio Timer Id */
    vm_AudioManagerPCMMsg_t   i2sMsg;
#if defined(__UPGRADE_DSP_R2__) && !defined(__SDK_SIMULATION__)
    Mrl_AU_SetPathReq_t       MrlAuSetPathReq;
#endif // __UPGRADE_DSP_R2__
} vm_msgBody_t;


/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif //__MDL_AUD_MSG_H__

