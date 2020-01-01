////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
* @file    Marrecoder.h
* @version
* @brief   Multimedia audio recorder header file
*
*/

////////////////////////////////////////////////////////////////////////////////

#ifndef _MARENCODER_H
#define _MARENCODER_H

//-----------------------------------------------------------------------------
//Include Files
//-----------------------------------------------------------------------------
//#include <sys/bsdtypes.h>
//#include <cyg/kernel/kapi.h>
//#include <cyg/infra/diag.h>
//#include <cyg/hal/plf_intr.h>

//#include "shellcfg.h"

#include "ms_io.h"
#include "srv_resmgr_mml_forward.h"
#include "srv_resmgr_mmlaudio_types.h" // Lib release stage1's workaround

#include "mdw_aud_handle.h"
#include "mdw_aud_stream_ring.h"

#include "mdl_mmaudio_marrecorder.h"

#ifdef __B3_AUDIO_DRV_API__
#include "mdl_aud_dma_api.h"
#define PcmBufSize 1024*128
//__align(32) u8 uPcmBuf[PcmBufSize];
#define __MAR_EVENT_BASE__

#define __B3_AUDDRV_INTERRUPT__

#ifdef __B3_AUDDRV_INTERRUPT__
#undef __B3_AUDDRV_POLLING__
#endif

#ifdef __SDK_SIMULATION__
#undef __B3_AUDDRV_INTERRUPT__
#define __B3_AUDDRV_POLLING__
#endif
#endif



// the duration to wait pcm data
#define MDLAUD_INTER_TIMER_DURATION 10

#define DAT_RESERVE_SIZE 64

#ifndef __AMR_REC__
#define __AMR_REC__
#endif

//-----------------------------------------------------------------------------
//Structure Declaration
//-----------------------------------------------------------------------------
typedef enum
{
    MAR_DOUBLE_BUF_FLAG   = 0x00000001
} MARREC_FLAG;

typedef struct _recorder_write_mem_addr
{

    u32 ringbuflen;
    u32 ringhighwater;
    u32 ringlowwater;
    u32 u32FullThreshold;

} recorder_write_mem_addr;

typedef enum
{
    MAR_CONVERT_1X            = 1,
    MAR_DOWN_CONVERT_2X       = 2,
    MAR_DOWN_CONVERT_3X       = 3,
    MAR_DOWN_CONVERT_4X       = 4,
    MAR_DOWN_CONVERT_6X       = 6,
    MAR_UP_CONVERT_2X       = 12,
    MAR_UP_CONVERT_3X       = 13,
    MAR_UP_CONVERT_4X       = 14,
    MAR_UP_CONVERT_6X       = 16,
} MAR_SAMPLE_CONVERT;

typedef enum
{
    MAR_MEM_CLOSE       = 0,
    MAR_MEM_AVAILABLE   = 1,
} MAR_MEM_STATUS;

typedef struct _gmar_input_setting
{
    u8  u8channels;
    u16 u16format;
    u16 u16samplerate;
    u32 u32bitrate;

    MmlAudioEncoderId_e eEncoderId;
    MmlAudioInputType_e eInputType;
    MmlAudioOutputType_e eOutputType;
    MmlAudioSamplingRate_e eSamplingRate;
    MmlAudioChannelMode_e eChannelMode;
} gmar_input_setting;


typedef struct _MarAudioCallbackParam_t
{
    u32                             nSizeLimit;         ///< Callback function invoked when reaching the size limit, in bytes.
    u32                             nUserData;          ///< Interface self-reference
    PfnMmlAudioDataCallback         pfnDataCallback;    ///< Callback function you want to register
} MarAudioCallbackParam_t;


typedef struct _marwritethread_s_
{
    recorder_common_inst     comm_inst;
    mar_input_setting       rec_input_set;
    recorder_write_mem_addr    rec_write_mem;
    VFS_FILE *rec_file_handle;
    u32 error_notify_send; // record error notify have been send
    u32 *pOutMemBuf;
    u32 nBufferSize;
    u32 u32marWt_stop_type;
    stream_ring_buffer *mar_stream_ring;
    MarAudioCallbackParam_t MarAudioCallback;

#ifdef __MDL_AUD_REC_DYN_TASK__
    MsTaskId_e nTaskId;
    u32 *nStackTopAddr;
#endif

#ifdef __MDL_AUD_REC_RINGBUF__
    u32 *pRingBuffer;
    u32 rbHandle;
#endif
} marwritethread_s;

//extern s32 init_audio_codec(void *player, s32 data_fmt);

extern void fnCreateMARThread(void);
extern void fnMAR_StateChange(MmlAudioState_e nextState);
extern gmar_input_setting gMARInputSetting;

//s32 fnMAR_RecStart(const char *filename, void *pInst, s32 datafmt);
s32 fnMAR_RecStart(void *pInst);
void fnMAR_DiscardSaving(void);
void fnMAR_Cleanup(void *pInst);
s32 fnMAR_Preparation(void *pInst);
void fnMAR_setStop(void *pInst, MmlAudioResult_e eCause);
s32 fnMAR_ParaSet(void *pInst, MmlAudioStartRecording_t * pAudioStartRecording);
s32 fnMAR_SetRecordingPara(void *pInst, MmlAudioSetRecordingSetting_t * pAudioRecordingSetting);
void fnMAR_RecordingSetttingInit(void);
void MdlAudMARSendMsg(u16 MbxSrc, u16 MbxDst, MdlAudioCtlMsgId_e eMsgId, u32 nErrCode);
void MDLAudRecordCtlInterProc(void *pMessage);
void fnMAR_reachLimit(void *pInst);
s32 fnMAR_PushBuf(void *pInst, s32 s32pushsize, u8* u8pushsample);
s32 _fnMARProcessData(void *pInst);
s32 MdlAudRecQueryPosition(void);
bool MdlMARParamValid(void *pInst);
u32 MdlAudRecGetPosition(void);
void fnMARGetSamplerate(MmlAudioSamplingRate_e eSamplingRate, u16 *u16samplerate);

#endif //_AUDPLAYER_H
