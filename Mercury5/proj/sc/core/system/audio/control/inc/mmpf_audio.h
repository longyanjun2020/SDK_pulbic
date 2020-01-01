/// @ait_only
//==============================================================================
//
//  File        : mmpf_audio.h
//  Description : INCLUDE File for the Audio Driver.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_AUDIO_H_
#define _MMPF_AUDIO_H_

/** @addtogroup MMPF_AUDIO
@{
*/

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "aitu_ringbuf.h"
#include "mmp_aud_inc.h"
#include "mmp_err.h"

//==============================================================================
//
//                              DATA TYPE
//
//==============================================================================

typedef void (MMPF_Audio_Callback) (void);

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_AUDIO_DATAPATH
{
    MMPF_AUDIO_DATAPATH_MEM = 0,///< memory mode
    MMPF_AUDIO_DATAPATH_CARD,   ///< card mode
    MMPF_AUDIO_DATAPATH_MMP_MEM ///< MMP memory mode
} MMPF_AUDIO_DATAPATH;

#if (SEC_DNSE_VH_ON)
typedef enum
{
    VH_CHANNEL       = 0, 
    VH_MONO          = 1,
    VH_STEREO        = 2,
    VH_3F            = 3,
    VH_2F1R          = 4,
    VH_3F1R          = 5,
    VH_2F2R          = 6,
    VH_3F2R          = 7,
    VH_CHANNEL1      = 8,
    VH_CHANNEL2      = 9,
    VH_DOLBY         = 10,
    VH_CHANNEL_MASK  = 15, 
    VH_LFE           = 16,
    VH_ADJUST_LEVEL  = 32
} AudioDec_DownMixMode;
#endif

#if (AUDIO_PREVIEW_SUPPORT == 1)
typedef enum _MMPF_AUDIO_PREVIEW_MODE
{
    MMPF_AUD_PREVIEW_L_MONO = 0,    ///< convert stereo to mono, select L
    MMPF_AUD_PREVIEW_R_MONO,        ///< convert stereo to mono, select R
    MMPF_AUD_PREVIEW_LR_AVG,        ///< convert stereo to mono, average of L/R
    MMPF_AUD_PREVIEW_STEREO         ///< stereo
} MMPF_AUDIO_PREVIEW_MODE;
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

#if (AUDIO_PREVIEW_SUPPORT == 1)
typedef struct _MMPF_AUDIO_PREVIEW_CFG
{
    MMP_ULONG ulOutSamplerate;      ///< sample rate requested
    MMP_ULONG ulPreviewStartMs;     ///< start time to do preview
    MMP_ULONG ulPreviewDuration;    ///< preview duration in ms unit
    MMP_ULONG ulReqSamples;         ///< number of samples requested
    MMP_ULONG ulDataBufAddr;        ///< Buffer address of preview data
    MMP_ULONG ulAccuSamples;        ///< number of samples accumulated
    MMPF_AUDIO_PREVIEW_MODE chMode; ///< channel mode
    MMP_BOOL  bSrcEnable;           ///< SRC needed
    MMP_BOOL  bDataCompleted;       ///< indicated preview data ready or not
} MMPF_AUDIO_PREVIEW_CFG;
#endif

typedef struct {
    unsigned int rd_ind;
    unsigned int wr_ind;
    int          SampleLeft;
    unsigned int BufButton;
} OutDataObj;

//==============================================================================
//
//                              TYPE DEFINE
//
//==============================================================================

typedef AUTL_RINGBUF * (*MMP_GetRingBufHandle) (void);
typedef MMP_SHORT * (*MMP_RingBufDataStart) (void);
typedef void (*MMP_AdvanceRingBufReadPtr) (MMP_ULONG ulSize);
typedef void (*MMP_AdvanceRingBufWritePtr) (MMP_ULONG ulSize);
typedef MMP_ULONG (*MMP_RingBufDataAvailable) (void);
typedef void (*MMP_RingBufReadInBuf) (MMP_SHORT *target, MMP_ULONG samples);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

extern void MMPF_SetAMRDecodeOp(MMP_USHORT op, MMP_ULONG *parameter);
extern void MMPF_SetAMREncodeOp(MMP_USHORT op);
extern void MMPF_SetMP3DecodeOp(MMP_USHORT op, MMP_ULONG *parameter);
extern void MMPF_SetAACPLUSDecodeOp(MMP_USHORT op);
extern void MMPF_SetFLACDecodeOp(MMP_USHORT op);
extern void MMPF_SetAACEncodeOp(MMP_USHORT op);
extern void MMPF_SetMP3EncodeOp(MMP_USHORT op);
extern void MMPF_SetWAVEncodeOp(MMP_USHORT op);
extern void MMPF_SetADPCMEncodeOp(MMP_USHORT op);
extern void MMPF_SetWMADecodeOp(MMP_USHORT op,MMP_ULONG *parameter);
extern void MMPF_SetWMAProDecodeOp(MMP_USHORT op,MMP_ULONG *parameter);
extern void MMPF_SetRADecodeOp(MMP_USHORT op,MMP_ULONG *parameter);
extern void MMPF_SetMIDIDecodeOp(MMP_USHORT op);
extern void MMPF_SetPCMDecodeOp(MMP_USHORT op);
extern void MMPF_SetOGGDecodeOp(MMP_USHORT op,MMP_ULONG *parameter);
extern void MMPF_SetWAVDecodeOp(MMP_USHORT op, MMP_ULONG *parameter);
extern void MMPF_SetLiveG711EncodeOp(MMP_USHORT op);
extern void MMPF_SetLiveAACEncodeOp(MMP_USHORT op);
extern MMP_ERR MMPF_Audio_SetLiveEncodeCB(MMP_LivePCMCB  LivePCMCB);
#if (VIDEO_DEC_TO_MJPEG)
extern void MMPF_Audio_InitTranscoding(MMPF_Audio_Callback *dec_cb);
extern void MMPF_Audio_SetTranscodeUsePlayerInfo(MMP_ULONG samplerate, MMP_UBYTE chanum);
extern void MMPF_Audio_TriggerTranscode(MMP_SHORT *pcm, MMP_ULONG count, MMP_ULONG time);
#endif

#if (SEC_DNSE_VH_ON)
extern void MMPF_AudioDec_InitVH(int flags, int mode, int sample_rate);
extern void MMPF_AudioDec_DeInitVH(void);
extern void MMPF_AudioDec_SetVHPar(const int m3deff, const int db, char set_m3deff, char set_db);
#endif

extern AUTL_RINGBUF *MMPF_Audio_GetEncInBufHandle(void);
extern AUTL_RINGBUF *MMPF_Audio_GetUACInBufHandle(void);

extern void MMPF_Audio_InitInBufHandle(AUTL_RINGBUF *ringbufHandle, MMP_SHORT *sBufAddr, MMP_ULONG ulBufSize);
extern MMP_SHORT *MMPF_Audio_EncInBufDataStart(AUTL_RINGBUF *ringbufHandle);
extern void MMPF_Audio_AdvanceInBufReadPtr(AUTL_RINGBUF *ringbufHandle, MMP_ULONG ulSize);
extern void MMPF_Audio_AdvanceInBufWritePtr(AUTL_RINGBUF *ringbufHandle, MMP_ULONG ulSize);
extern MMP_ULONG MMPF_Audio_InBufDataAvailable(AUTL_RINGBUF *ringbufHandle);
extern MMP_ULONG MMPF_Audio_InBufFreeSpace(AUTL_RINGBUF* ringbufHandle);
extern MMP_BOOL MMPF_Audio_InBufFull(AUTL_RINGBUF *ringbufHandle);
extern void MMPF_Audio_ReadInBuf(MMP_SHORT *target, MMP_ULONG samples);
extern void MMPF_Audio_WriteInBuf(MMP_SHORT *data, MMP_ULONG samples);
extern void MMPF_Audio_WriteInHandler(MMP_SHORT *data, MMP_ULONG samples, AUTL_RINGBUF *ringHandle);

extern void MMPF_Audio_WriteInStreamBuf(MMP_SHORT *data, MMP_ULONG samples);

extern MMP_ERR	MMPD_AUDIO_PlayFadeOutEn(MMP_UBYTE channelID, MMP_BOOL bAFadeOutEn);

/// @}

#endif //_MMPF_AUDIO_H_

/// @end_ait_only

