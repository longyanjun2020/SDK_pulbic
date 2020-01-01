/// @ait_only
//==============================================================================
//
//  File        : mmpd_audio.h
//  Description : Audio Control Driver Function
//  Author      : Hnas Liu
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_AUDIO_H_
#define _MMPD_AUDIO_H_

#include "ait_config.h"
#include "mmp_aud_inc.h"

/** @addtogroup MMPD_AUDIO
 *  @{
 */

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE          (24)

#define MMPD_AUDIO_REC_HANDSHAKE_BUF_SIZE           (8)

#define MMPD_AUDIO_REC_WRITE_HIGH_PTR_OFFSET_W      (0)
#define MMPD_AUDIO_REC_WRITE_PTR_OFFSET_W           (2)
#define MMPD_AUDIO_REC_READ_HIGH_PTR_OFFSET_W       (4)
#define MMPD_AUDIO_REC_READ_PTR_OFFSET_W            (6)

#define MMPD_AUDIO_SPECTRUM_DATA_SIZE               (64)

#define OGG_TAG_BUF_SIZE                            (512)

//==============================================================================
//
//                              ENUMERATIONS
//
//==============================================================================

typedef enum _MMPD_AUDIO_PLAY_DATAPATH
{
    MMPD_AUDIO_PLAY_FROM_MEM = 0,   ///< memory mode
    MMPD_AUDIO_PLAY_FROM_CARD,      ///< card mode
    MMPD_AUDIO_PLAY_FROM_MMP_MEM    ///< MMP memory mode
} MMPD_AUDIO_PLAY_DATAPATH;

typedef enum _MMPD_AUDIO_RECORD_DATAPATH
{
    MMPD_AUDIO_RECORD_TO_MEM = 0,   ///< memory mode
    MMPD_AUDIO_RECORD_TO_CARD       ///< card mode
} MMPD_AUDIO_RECORD_DATAPATH;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

extern MMP_ERR	MMPD_AUDIO_PlayFadeOutEn(MMP_UBYTE channelID, MMP_BOOL bAFadeOutEn);
extern MMP_ERR  MMPD_AUDIO_GetDecOutBuf(MMP_ULONG *ulBufAddr, MMP_ULONG *ulBufSize);
extern MMP_ERR	MMPD_AUDIO_CheckPlayEnd(void);
extern MMP_ERR  MMPD_AUDIO_GetAACPlusFileInfo(MMP_AUDIO_AACPLUS_INFO *aacplusinfo);
extern MMP_ERR  MMPD_AUDIO_GetMIDIFileInfo(MMP_AUDIO_MIDI_INFO *midiinfo);
extern MMP_ERR  MMPD_AUDIO_GetMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info);
extern MMP_ERR  MMPD_AUDIO_GetWMAFileInfo(MMP_AUDIO_WMA_INFO *wmainfo);
extern MMP_ERR  MMPD_AUDIO_GetRAFileInfo(MMP_AUDIO_RA_INFO *rainfo);
extern MMP_ERR  MMPD_AUDIO_GetAMRFileInfo(MMP_AUDIO_AMR_INFO *amrinfo);
extern MMP_ERR  MMPD_AUDIO_GetAACFileInfo(MMP_AUDIO_AAC_INFO *aacinfo);
extern MMP_ERR  MMPD_AUDIO_GetWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo);
extern MMP_ERR	MMPD_AUDIO_GetFLACFileInfo(MMP_AUDIO_FLAC_INFO *flacinfo);
extern MMP_ERR  MMPD_AUDIO_ReadAACPlusFileInfo(MMP_AUDIO_AACPLUS_INFO *aacplusinfo);
extern MMP_ERR  MMPD_AUDIO_ReadMIDIFileInfo(MMP_AUDIO_MIDI_INFO *midiinfo);
extern MMP_ERR  MMPD_AUDIO_ReadMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info);
extern MMP_ERR  MMPD_AUDIO_ReadWMAFileInfo(MMP_AUDIO_WMA_INFO *wmainfo);
extern MMP_ERR  MMPD_AUDIO_ReadAMRFileInfo(MMP_AUDIO_AMR_INFO *amrinfo);
extern MMP_ERR  MMPD_AUDIO_ReadOGGFileInfo(MMP_AUDIO_OGG_INFO *ogginfo);
extern MMP_ERR  MMPD_AUDIO_ReadRAFileInfo(MMP_AUDIO_RA_INFO *rainfo);
extern MMP_ERR  MMPD_AUDIO_ReadWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo);
extern MMP_ERR	MMPD_AUDIO_ReadFLACFileInfo(MMP_AUDIO_FLAC_INFO *flacinfo);
extern MMP_ERR  MMPD_AUDIO_StopAudioPlay(void);
extern MMP_ERR	MMPD_AUDIO_ResumeAudioPlay(void);
extern MMP_ERR	MMPD_AUDIO_PauseAudioPlay(void);
extern MMP_ERR	MMPD_AUDIO_StartAudioPlay(void* , void* );
extern MMP_ERR  MMPD_AUDIO_GetAACPlusPlayTime(MMP_USHORT *usPosRatio,MMP_ULONG *ulMilliSecond);
extern MMP_ERR	MMPD_AUDIO_GetMIDIPlayTime(MMP_USHORT *usTimeRatio,MMP_ULONG *ulMilliSecond);
extern MMP_ERR  MMPD_AUDIO_GetMP3PlayTime(MMP_USHORT *usPosRatio,MMP_ULONG *ulMilliSecond);
extern MMP_ERR  MMPD_AUDIO_GetWMAPlayTime(MMP_USHORT *usPosRatio,MMP_ULONG *ulMilliSecond);
extern MMP_ERR  MMPD_AUDIO_GetRAPlayTime(MMP_USHORT *usPosRatio,MMP_ULONG *ulMilliSecond);
extern MMP_ERR  MMPD_AUDIO_GetOGGPlayTime(MMP_ULONG *ulMilliSecond);
extern MMP_ERR  MMPD_AUDIO_GetWAVPlayTime(MMP_ULONG *ulMilliSecond);
extern MMP_ERR  MMPD_AUDIO_GetAMRPlayTime(MMP_USHORT *usPosRatio,MMP_ULONG *ulMilliSecond);
extern MMP_ERR	MMPD_AUDIO_GetFLACPlayTime(MMP_USHORT *usPosRatio, MMP_ULONG *ulMilliSecond);
extern MMP_ERR	MMPD_AUDIO_SetMIDIPlayTime(MMP_ULONG ulTime);
extern MMP_ERR	MMPD_AUDIO_SetAACPlusPlayTime(MMP_ULONG ulMilliSec);
extern MMP_ERR	MMPD_AUDIO_SetMP3PlayTime(MMP_ULONG ulMilliSec);
extern MMP_ERR	MMPD_AUDIO_SetWMAPlayTime(MMP_ULONG ulTime);
extern MMP_ERR	MMPD_AUDIO_GetWMAVersion(MMP_ULONG *ulVersion);
extern MMP_ERR	MMPD_AUDIO_SetRAPlayTime(MMP_ULONG ulTime);
extern MMP_ERR	MMPD_AUDIO_SetOGGPlayTime(MMP_ULONG ulTime);
extern MMP_ERR  MMPD_AUDIO_SetWAVPlayTime(MMP_ULONG ulMilliSec);
extern MMP_ERR	MMPD_AUDIO_SetAACPlayTime(MMP_ULONG ulMilliSec);
extern MMP_ERR	MMPD_AUDIO_SetAMRPlayTime(MMP_ULONG ulMilliSec);
extern MMP_ERR	MMPD_AUDIO_SetFLACPlayTime(MMP_ULONG ulMilliSec);
extern MMP_ERR  MMPD_AUDIO_GetPlayStatus(MMP_USHORT *usStatus);
extern MMP_ERR	MMPD_AUDIO_SetEncodeFileSize(MMP_ULONG ulSize);
extern MMP_ERR	MMPD_AUDIO_StartAudioRecord(void);
extern MMP_ERR	MMPD_AUDIO_PauseAudioRecord(void);
extern MMP_ERR	MMPD_AUDIO_ResumeAudioRecord(void);
extern MMP_ERR	MMPD_AUDIO_StopAudioRecord(void);
extern MMP_ERR	MMPD_AUDIO_StartLiveAudioRecord(void);
extern MMP_ERR 	MMPD_AUDIO_PauseLiveAudioRecord(void);
extern MMP_ERR 	MMPD_AUDIO_ResumeLiveAudioRecord(void);
extern MMP_ERR 	MMPD_AUDIO_StopLiveAudioRecord(void);

extern MMP_ERR	MMPD_AUDIO_SetPlayPosition(MMP_ULONG ulPos);
extern MMP_ERR	MMPD_AUDIO_EnableABRepeatMode(MMP_USHORT usEnable);
extern MMP_ERR	MMPD_AUDIO_SetPlayVolume(MMP_UBYTE ubSWGain, MMP_UBYTE ubDGain, MMP_UBYTE ubAGain, MMP_BOOL bSWGainOnly);
extern MMP_ERR	MMPD_AUDIO_SetRecordVolume(MMP_UBYTE ubDGain, MMP_UBYTE ubAGain);
extern MMP_ERR	MMPD_AUDIO_SetRecordHeadMuteTime(MMP_ULONG ulMilliSec);
extern MMP_ERR 	MMPD_AUDIO_SetRecordTailCutTime(MMP_ULONG ulMilliSec);
extern MMP_ERR	MMPD_AUDIO_StopMIDINotePlay(void);
extern MMP_ERR	MMPD_AUDIO_StartMIDINotePlay(void);
extern MMP_ERR	MMPD_AUDIO_SetEQType(MMP_USHORT usType, void* argHandler);
extern MMP_ERR	MMPD_AUDIO_SetPlayBuf(MMP_ULONG ulAddr,MMP_ULONG ulSize);
extern MMP_ERR  MMPD_AUDIO_SetPlayFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength);
extern MMP_ERR  MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_DATAPATH ubPath);
extern MMP_ERR  MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_DATAPATH ubPath);
extern MMP_ERR  MMPD_AUDIO_SetEncodeFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength);
extern MMP_ERR	MMPD_AUDIO_SetEncodeBuf(MMP_ULONG ulAddr,MMP_ULONG ulSize);
extern MMP_ERR	MMPD_AUDIO_SetLiveEncodeMode(MMP_USHORT usMode);
extern MMP_ERR	MMPD_AUDIO_GetLiveEncodeMode(MMP_USHORT *usMode);
extern MMP_ERR	MMPD_AUDIO_SetEncodeMode(MMP_USHORT usMode);
extern MMP_ERR	MMPD_AUDIO_GetEncodeMode(MMP_USHORT *usMode);
extern MMP_ERR  MMPD_AUDIO_GetRecordSize(MMP_ULONG *ulSize);
extern MMP_ERR  MMPD_AUDIO_GetRecordStatus(MMP_USHORT *usStatus);
extern MMP_ERR  MMPD_AUDIO_GetLiveRecordStatus(MMP_USHORT *usStatus);
extern MMP_ERR  MMPD_AUDIO_GetRecordFrameCntInSeconds(MMP_ULONG ulSec, MMP_ULONG *ulCnt);

extern MMP_ERR  MMPD_AUDIO_GetWriteCardStatus(MMP_USHORT *usStatus);
extern MMP_ERR	MMPD_AUDIO_GetPlayFileSize(MMP_ULONG *ulFileSize);
extern MMP_ERR	MMPD_AUDIO_UpdatePlayReadPtr(void);
extern MMP_ERR	MMPD_AUDIO_UpdatePlayWritePtr(void);
extern MMP_ERR	MMPD_AUDIO_SetPlayFileSize(MMP_ULONG ulFileSize);
extern MMP_ERR  MMPD_AUDIO_TransferDataToAIT(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, 
				MMP_ULONG *ulReturnSize);
extern MMP_ERR	MMPD_AUDIO_InitPlayRWPtr(void);
extern MMP_ERR	MMPD_AUDIO_SetPlayHandshakeBuf(MMP_ULONG addr,MMP_ULONG ulSize);
extern MMP_ERR	MMPD_AUDIO_SetRecHandshakeBuf(MMP_ULONG ulAddr,MMP_ULONG ulSize);
extern MMP_ERR	MMPD_AUDIO_UpdateRecWritePtr(void);
extern MMP_ERR  MMPD_AUDIO_TransferDataToHost(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, 
				MMP_ULONG *ulReturnSize);
extern MMP_ERR	MMPD_AUDIO_InitRecRWPtr(void);
extern MMP_ERR	MMPD_AUDIO_SetSBCEncodeEnable(MMP_UBYTE ubEnable,MMP_ULONG ulIntPeriod);
extern MMP_ERR	MMPD_AUDIO_GetSBCEncodeEnable(MMP_BOOL *bEnable);
extern MMP_ERR	MMPD_AUDIO_SetSBCChannelMode(MMP_USHORT usMode);
extern MMP_ERR	MMPD_AUDIO_SetSBCAllocMethod(MMP_USHORT usMethod);
extern MMP_ERR	MMPD_AUDIO_SetSBCNrofBlocks(MMP_USHORT usBlocks);
extern MMP_ERR	MMPD_AUDIO_SetSBCNrofSubbands(MMP_USHORT usSubBands);
extern MMP_ERR	MMPD_AUDIO_SetSBCBitrate(MMP_USHORT usBitRate);
extern MMP_ERR	MMPD_AUDIO_SetSBCBitPool(MMP_USHORT usBitPool);
extern MMP_ERR  MMPD_AUDIO_GetSBCInfo(  MMP_ULONG *ulOutSampleRate, 
                                        MMP_ULONG *ulOutBitRate,
                                        MMP_ULONG *ulOutFrameSize,
                                        MMP_ULONG *ulSBCFrameCount,
                                        MMP_ULONG *ulSBCSamplesPerFrame,
                                        MMP_ULONG *ulSBCChannelNum,
                                        MMP_ULONG *ulSBCBitpool);

extern MMP_ERR MMPD_AUDIO_SetAC3VHPar(MMP_LONG lm3deff, MMP_LONG ldb, MMP_BOOL bSet_m3deff, MMP_BOOL bSet_db);

extern MMP_ERR	MMPD_AUDIO_SetWAVEncodeEnable(MMP_UBYTE ubEnable);
extern MMP_ERR  MMPD_AUDIO_GetWAVInfo(MMP_ULONG *ulOutSampleCount);

extern MMP_ERR  MMPD_AUDIO_TransferMIDIDataToAIT(MMP_UBYTE *audio_ptr, MMP_ULONG ulFileSize);
extern MMP_ERR	MMPD_AUDIO_SetABRepeatMode(MMP_USHORT point , MMP_ULONG pos);
extern MMP_ERR	MMPD_AUDIO_GetPlayPosition(MMP_ULONG *pos);
extern MMP_ERR	MMPD_AUDIO_SetPlaySpectrumBuf(MMP_ULONG ulAddr,MMP_ULONG ulSize);
extern MMP_ERR	MMPD_AUDIO_GetPlaySpectrum(MMP_USHORT *usSpectrum);
extern MMP_ERR	MMPD_AUDIO_AACPlusPlayTime2FileOffset(MMP_ULONG ulMilliSec,MMP_ULONG *ulFileOffset);
extern MMP_ERR	MMPD_AUDIO_MP3PlayTime2FileOffset(MMP_ULONG ulMilliSec,MMP_ULONG *ulFileOffset);
extern MMP_ERR  MMPD_AUDIO_WAVPlayTime2FileOffset(MMP_ULONG ulMilliSec, MMP_ULONG *ulFileOffset);
extern MMP_ERR	MMPD_AUDIO_AMRPlayTime2FileOffset(MMP_ULONG ulMilliSec,MMP_ULONG *ulFileOffset);
extern MMP_ERR	MMPD_AUDIO_SaveAACRecParameter(MMP_ULONG ulMode);
extern MMP_ERR	MMPD_AUDIO_ReadAACRecParameter(MMP_ULONG *ulBitRate, MMP_USHORT *usSampleRate);
extern MMP_ERR	MMPD_AUDIO_SaveMP3RecParameter(MMP_ULONG ulMode);
extern MMP_ERR	MMPD_AUDIO_ReadMP3RecParameter(MMP_ULONG *ulBitRate, MMP_USHORT *usSampleRate);
extern MMP_ERR	MMPD_AUDIO_SaveAMRRecParameter(MMP_ULONG ulMode);
extern MMP_ERR	MMPD_AUDIO_ReadAMRRecParameter(MMP_ULONG *ulBitRate);
extern MMP_ERR  MMPD_AUDIO_SaveWAVRecParameter(MMP_ULONG ulMode);
extern MMP_ERR  MMPD_AUDIO_ReadWAVRecParameter(MMP_USHORT *usSampleRate);
extern MMP_ERR	MMPD_AUDIO_GetPlayStartSeekFlag(MMP_USHORT *usFlag);
extern MMP_ERR	MMPD_AUDIO_GetPlayFinishSeekFlag(MMP_USHORT *usFlag);
extern MMP_ERR	MMPD_AUDIO_SetPlayStartSeekFlag(MMP_USHORT usFlag);
extern MMP_ERR	MMPD_AUDIO_GetPlayFileSeekOffset(MMP_ULONG *ulOffset);
extern MMP_ERR	MMPD_AUDIO_UpdatePlayStreamSize(MMP_ULONG ulFileSize);
extern MMP_ERR	MMPD_AUDIO_UpdatePlayFileRemainSize(MMP_ULONG ulFileSize);
extern MMP_ERR	MMPD_AUDIO_InitPlaySeekFlag(void);
extern MMP_ERR  MMPD_AUDIO_SetAudioTagBuf(MMP_ULONG ulTagAddr,MMP_ULONG ulTagSize);
extern MMP_ERR  MMPD_AUDIO_GetWMATagLen(MMP_ULONG *Len, MMP_AUDIO_WMA_INFO *wmaproinfo);
extern MMP_ERR  MMPD_AUDIO_GetOGGFileInfo(MMP_AUDIO_OGG_INFO *ogginfo);
extern MMP_ERR  MMPD_AUDIO_GetOGGTagInfo(MMP_AUDIO_OGG_TAG_INFO *TagInfo);

extern MMP_ERR  MMPD_AUDIO_SetPlayFileNameBuf(MMP_ULONG ulBufAddr);
extern MMP_ERR  MMPD_AUDIO_SetEncodeFileNameBuf(MMP_ULONG ulBufAddr);
extern MMP_ERR	MMPD_AUDIO_GetAudioPlayBufSize(MMP_ULONG *ulSize);
extern MMP_ERR	MMPD_AUDIO_SetRecReadPtr(void);
extern MMP_ERR	MMPD_AUDIO_SetPlayIntThreshold(MMP_USHORT usThreshold);
extern MMP_ERR	MMPD_AUDIO_SetRecordIntThreshold(MMP_USHORT usThreshold);
extern MMP_ERR  MMPD_AUDIO_SetGraphicEQEnable(MMP_BOOL ubEnable);
extern MMP_ERR	MMPD_AUDIO_SetGraphicEQBand(MMP_USHORT usFreq, MMP_USHORT usQrange, MMP_USHORT usGain);
extern MMP_ERR  MMPD_AUDIO_SetForeignEffectEnable(MMP_BOOL ubEnable);
extern MMP_ERR  MMPD_AUDIO_SetForeignEffectType(MMP_ULONG ulParam1, MMP_ULONG ulParam2, MMP_ULONG ulParam3);
extern MMP_ERR  MMPD_AUDIO_StartPreview(MMP_ULONG ulStartTime, MMP_ULONG ulDuration);
extern MMP_ERR  MMPD_AUDIO_GetPreviewStatus(MMP_BOOL *bDataReady, MMP_SHORT **usDataBuf, MMP_ULONG *ulSampleNum);
extern MMP_ERR	MMPD_AUDIO_SetPlayFileSize(MMP_ULONG ulFileSize);
extern MMP_ERR	MMPD_AUDIO_SetEncodeFileSize(MMP_ULONG ulSize);
extern MMP_ERR  MMPD_AUDIO_PreDACPowerOn(MMP_ULONG ulSampleRate);
extern MMP_BOOL MMPD_AUDIO_GetDACPowerOnStatus(void);
extern MMP_BOOL MMPD_AUDIO_GetADCPowerOnStatus(void);

MMP_ERR	MMPD_AUDIO_SetI2SWorkMode(MMP_UBYTE ch, MMP_I2S_WORK_MODE workingMode);
MMP_ERR	MMPD_AUDIO_SetI2SMclkMode(MMP_UBYTE ch, MMP_I2S_MCLK_MODE mclkMode);
MMP_ERR	MMPD_AUDIO_SetI2SOutBitWidth(MMP_UBYTE ch, MMP_I2S_OUT_BITS outputBitSize);
MMP_ERR	MMPD_AUDIO_SetI2SLRckPolarity(MMP_UBYTE ch, MMP_I2S_WS_POLARITY lrckPolarity);
MMP_ERR	MMPD_AUDIO_SetI2SOutDataDelayMode(MMP_UBYTE ch, MMP_I2S_DELAY_MODE outDataDelayMode);
MMP_ERR	MMPD_AUDIO_SetI2SOutBySDI(MMP_UBYTE ch, MMP_BOOL bOutputBySDI);
MMP_ERR	MMPD_AUDIO_SetI2SInFromSDO(MMP_UBYTE ch, MMP_BOOL bInputFromSDO);
MMP_ERR	MMPD_AUDIO_SetI2SInBitAlign(MMP_UBYTE ch, MMP_UBYTE ubInBitAlign);
MMP_ERR	MMPD_AUDIO_SetI2SOutBitAlign(MMP_UBYTE ch, MMP_UBYTE ubOutBitAlign);
MMP_ERR	MMPD_AUDIO_SetI2SMclkFreq(MMP_UBYTE ch, MMP_I2S_MCLK_MODE mclkMode, MMP_ULONG ulSamplerate, MMP_ULONG ulFixedMclkFreq);
MMP_ERR	MMPD_AUDIO_EnableI2SMclk(MMP_UBYTE ch, MMP_I2S_WORK_MODE workMode, MMP_I2S_MCLK_MODE mclkMode, MMP_BOOL bEnable);

MMP_ERR	MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_ENCODE_FMT encodefmt);
MMP_ERR	MMPD_AUDIO_SetLiveEncodeFormat( MMP_AUDIO_ENCODE_FMT    encodefmt,
                                        MMP_ULONG               inSamplerate,
                                        MMP_ULONG               outSamplerate,
                                        MMP_UBYTE               inCh,
                                        MMP_UBYTE               outCh);
MMP_ERR	MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_DECODE_FMT decodefmt);
MMP_ERR	MMPD_AUDIO_SetInPath(MMP_ULONG audiopath);
MMP_ERR	MMPD_AUDIO_SetOutPath(MMP_ULONG audiopath);
MMP_ERR	MMPD_AUDIO_SetLineInChannel(MMP_AUD_LINEIN_CH lineinchannel);

MMP_ERR	MMPD_AUDIO_SetPlayReadPtr(MMP_ULONG usAudioPlayReadPtr, MMP_ULONG usAudioPlayReadPtrHigh);
MMP_ERR	MMPD_AUDIO_SetPlayWritePtr(MMP_ULONG usAudioPlayWritePtr, MMP_ULONG usAudioPlayWritePtrHigh);
MMP_ERR MMPD_AUDIO_TransferDataHostToDev(void);
MMP_ERR MMPD_AUDIO_InitialMemModePointer(MMP_UBYTE *ubBufAddr, MMP_ULONG ulBufSize, MMP_ULONG ulReadSize, MMP_ULONG ulBufThreshold);
MMP_ERR MMPD_AUDIO_SetMemModeReadPointer(MMP_ULONG ulMemReadPtr, MMP_ULONG ulMemReadPtrHigh);
MMP_ERR MMPD_AUDIO_TransferDataCardToHost(void* FileHandle);
MMP_ERR MMPD_AUDIO_SetPLL(MMP_USHORT usSampleRate);
MMP_ERR MMPD_AUDIO_SetGaplessEnable(MMP_BOOL bEnable, void *nextFileCB, MMP_ULONG param1);
MMP_ERR MMPD_AUDIO_GetGaplessAllowedOp(MMP_USHORT *op);

MMP_ERR MMPD_AUDIO_TransferAudioDataToHost(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, MMP_ULONG ulFrameSize, MMP_ULONG *ulReturnSize);
MMP_ERR	MMPD_AUDIO_SetMemModeFileHostInfo(void* FileHandle, MMP_ULONG ulAudioPlayFileSize);

MMP_ERR	MMPD_AUDIO_SetPlayDigitalGain(MMP_UBYTE ubDGain);
MMP_ERR	MMPD_AUDIO_SetPlayAnalogGain(MMP_UBYTE ubAGain);
MMP_ERR	MMPD_AUDIO_SetRecordDigitalGain(MMP_UBYTE ubDGain);
MMP_ERR MMPD_AUDIO_EnableDummyRecord(MMP_BOOL bEnable);
MMP_ERR MMPD_AUDIO_SetRecordSilence(MMP_BOOL bEnable);
MMP_ERR	MMPD_AUDIO_SetRecordAnalogGain(MMP_UBYTE ubAGain);
MMP_ERR MMPD_AUDIO_GetPlayFormat(MMP_AUDIO_DECODE_FMT *format);
MMP_ERR MMPD_AUDIO_GetEncodeFormat(MMP_AUDIO_ENCODE_FMT *fmt);
MMP_ERR MMPD_AUDIO_GetLiveEncodeFormat(MMP_AUDIO_ENCODE_FMT *fmt);

MMP_ERR	MMPD_AUDIO_SetParseFormat(MMP_AUDIO_DECODE_FMT fmt);
MMP_ERR MMPD_AUDIO_SetParseFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength);
MMP_ERR MMPD_AUDIO_SetParseFileNameBuf(MMP_ULONG ulBufAddr);
MMP_ERR MMPD_AUDIO_SetParseBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize);
MMP_ERR MMPD_AUDIO_SetParsePath(MMPD_AUDIO_PLAY_DATAPATH ubPath);
MMP_ERR MMPD_AUDIO_PresetPlayFileNameBuf(MMP_ULONG ulBufAddr);

MMP_ERR MMPD_AUDIO_SetLiveEncodeCB(MMP_LivePCMCB  LivePCMCB);
extern MMP_ERR	MMPD_AUDIO_StartAudioRecordEx(  MMP_BOOL                bPreEncode,
                                                MMP_AUDIO_ENCODE_FMT    encodefmt,
                                                MMP_ULONG               samplerate);
extern MMP_ERR  MMPD_AUDIO_DoLiveEncodeOp(MMP_USHORT op);
extern MMP_ERR  MMPD_AUDIO_GetEncodeBuf(MMP_ULONG* ulAddr, MMP_ULONG* ulSize);

extern MMP_ERR  MMPD_AUDIO_ConfigWNR(MMP_AUDIO_WNR_CFG *cfg);
extern MMP_ERR  MMPD_AUDIO_SetWNREnable(MMP_BOOL enable);
extern MMP_ERR  MMPD_AUDIO_SetAGCEnable(MMP_BOOL enable);
/// @}
#endif // _MMPD_AUDIO_H_
/// @end_ait_only
