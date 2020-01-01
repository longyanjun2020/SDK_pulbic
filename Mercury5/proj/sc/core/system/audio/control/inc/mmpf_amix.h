#ifndef	_MMPF_AMIX_H_
#define	_MMPF_AMIX_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_err.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#if (AUDIO_MIXER_EN == 1)

#if (GAPLESS_EN == 1)
#define	MMPF_AMIX_QUEUE_SIZE	100
#else
#define	MMPF_AMIX_QUEUE_SIZE	40
#endif

#if (GAPLESS_EN == 1)||(SRC_SUPPORT == 1)
#define 				    UNION_AUDIO_OUTBUF_SIZE		192*1024  // For Audio Player, max output PCM "samples"
#define 				    UNION_AUI_OUTBUF_SIZE		128*1024  // For AUI Player, max output PCM "samples"
#if (AUDIO_PREVIEW_SUPPORT == 1)
#define                     EXTRA_AUDIO_PREVIEW_SIZE    128*1024  // For Audio Preview extra PCM out size
#else
#define                     EXTRA_AUDIO_PREVIEW_SIZE    0         // For Audio Preview extra PCM out size
#endif
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_AMIX_CHANNEL
{
    MMPF_NON_AUI_PLAYER = 0, 	// Any other channel, including Audio Player, Video Player, and Streaming Player
    MMPF_AUI_PLAYER = 1,		// AUI player input channel
    MMPF_MAX_MIXER_COUNT 		// Maximum channel count
} MMPF_AMIX_CHANNEL;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef void AmixCallbackFunc(MMP_ULONG ulDataConsume, MMP_BOOL bConsumeRealData);

typedef struct _MMPF_AMIX_PCM_DATA
{
	MMP_SHORT *sData;
	MMP_ULONG ulLength;
	MMP_ULONG ulTime;
} MMPF_AMIX_PCM_DATA;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_ERR MMPF_AMIX_ConfigSpeed(MMP_ULONG ulSpeed);
MMP_ERR	MMPF_AMIX_FadeOutEn(MMPF_AMIX_CHANNEL channelID, MMP_BOOL bAudFadeOutEn);
MMP_ERR	MMPF_AMIX_FadeOutCtl(MMPF_AMIX_CHANNEL channelID, MMP_BOOL bAudFadeOutEn);
MMP_ERR	MMPF_AMIX_FadeInCtl(MMPF_AMIX_CHANNEL channelID, MMP_BOOL bAudFadeInEn);

MMP_ERR MMPF_AMIX_Initialize(void);
MMP_ERR	MMPF_AMIX_InitializeChannel(MMPF_AMIX_CHANNEL channelID, AmixCallbackFunc* callback);
MMP_ERR	MMPF_AMIX_OpenMixer(MMPF_AMIX_CHANNEL channelID, MMP_ULONG ulSampleRate);
MMP_ERR MMPF_AMIX_AddPCMData(MMPF_AMIX_CHANNEL channelID, MMP_SHORT *sData, MMP_ULONG ulLength, MMP_ULONG ulTime);
MMP_ERR MMPF_AMIX_ReadPCMData(MMPF_AMIX_CHANNEL channelID, MMP_SHORT **sData, MMP_ULONG *ulLength, MMP_ULONG *ulCurPos);
//MMP_ERR MMPF_AMIX_AdvancePCMData(MMPF_AMIX_CHANNEL channelID, MMP_ULONG ulCurPos);
//MMP_ERR MMPF_AMIX_AdvancePCMData(MMPF_AMIX_CHANNEL channelID, MMP_ULONG ulCurPos, MMP_BOOL bEnableCallBack);
MMP_ERR MMPF_AMIX_AdvancePCMData(MMPF_AMIX_CHANNEL channelID, MMP_ULONG ulCurPos, MMP_BOOL bEnableCallBack
                                                                        , MMP_BOOL bBypassMixerBuf);
MMP_ERR	MMPF_AMIX_CloseMixer(MMPF_AMIX_CHANNEL channelID);
MMP_ERR	MMPF_AMIX_StopMixer(MMPF_AMIX_CHANNEL channelID);
MMP_ERR MMPF_AMIX_Operate(void);
#if (PCM_TO_DNSE_EN == 1)
MMP_ERR MMPF_AMIX_OutputPCMData(MMPF_AMIX_CHANNEL channelID, MMP_SHORT *sData, MMP_ULONG ulLength, MMP_ULONG ulTime);
#endif
MMP_ERR	MMPF_AMIX_CheckMixerState(MMPF_AMIX_CHANNEL channelID, MMP_BOOL *opened);
#if (SRC_SUPPORT == 1)
MMP_ERR	MMPF_AMIX_InitSRC(MMPF_AMIX_CHANNEL channelID, MMP_ULONG ulSampleRate, MMP_USHORT *pusOutSampleRate);
#endif
MMP_ERR	MMPF_AMIX_CheckMixerGlobalState(MMP_BOOL *opened);
MMP_ERR	MMPF_AMIX_CleanQueue(MMPF_AMIX_CHANNEL channelID);
MMP_ERR MMPF_AMIX_GetPlayTime(MMPF_AMIX_CHANNEL channelID, MMP_ULONG *ulTime);
MMP_ERR MMPF_AMIX_SetPlayTime(MMPF_AMIX_CHANNEL channelID, MMP_ULONG ulTime);

MMP_ERR MMPF_AMIX_AddPCMDataToDMA(void);
MMP_ERR MMPF_AMIX_TriggerCallBack(void);
MMP_ERR MMPF_AMIX_GetDMACurCnt(MMP_ULONG *ulDataSize);
MMP_ERR MMPF_AMIX_GetDMABufferSize(MMP_ULONG *ulDataSize);


MMP_ERR MMPF_AMIX_UpdateAudSampleToTime(MMP_USHORT idx);
MMP_ERR MMPF_AMIX_ResetStartupDMACount(void);
MMP_ERR MMPF_AMIX_RegisterCallBack(AmixCallbackFunc* callback);
MMP_ERR MMPF_AMIX_SetAudSts(MMP_USHORT usOpType);
MMP_USHORT MMPF_AMIX_GetAudSts(void);

#endif //AUDIO_MIXER_EN

#endif //_MMPF_AMIX_H_


