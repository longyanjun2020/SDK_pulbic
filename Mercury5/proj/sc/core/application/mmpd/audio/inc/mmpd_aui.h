/// @ait_only
//==============================================================================
//
//  File        : mmpd_aui.h
//  Description : Audio Control Driver Function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_AUI_H_
#define _MMPD_AUI_H_

#include "ait_config.h"
#include "mmpd_audio.h"

/** @addtogroup MMPD_AUI
 *  @{
 */

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

typedef enum _MMPD_AUI_PLAY_DATAPATH {
    MMPD_AUI_PLAY_FROM_CARD,      ///< Card mode
    MMPD_AUI_PLAY_FROM_MMP_MEM,   ///< MMP memory mode
    MMPD_AUI_PLAY_MAX_DATAPATH
} MMPD_AUI_PLAY_DATAPATH;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

MMP_ERR		MMPD_AUI_SetPlayFormat(MMP_AUDIO_DECODE_FMT decodefmt);
MMP_ERR		MMPD_AUI_SetPlayFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength);
MMP_ERR		MMPD_AUI_SetPlayFileNameBuf(MMP_ULONG ulBufAddr);
MMP_ERR     MMPD_AUI_PresetPlayFileNameBuf(MMP_ULONG ulBufAddr);
MMP_ERR		MMPD_AUI_SetPlayBuf(MMP_ULONG ulAddr,MMP_ULONG ulSize);
MMP_ERR	    MMPD_AUI_SetPlayPath(MMPD_AUI_PLAY_DATAPATH ubPath);
MMP_ERR		MMPD_AUI_GetPlayFileSize(MMP_ULONG *ulFileSize);
MMP_ERR 	MMPD_AUI_GetPlayStatus(MMP_USHORT *usStatus);

MMP_ERR		MMPD_AUI_SetParseFormat(MMP_AUDIO_DECODE_FMT decodefmt);
MMP_ERR		MMPD_AUI_SetParseFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength);
MMP_ERR     MMPD_AUI_SetParseFileNameBuf(MMP_ULONG ulBufAddr);
MMP_ERR	    MMPD_AUI_SetParseBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize);
MMP_ERR	    MMPD_AUI_SetParsePath(MMPD_AUI_PLAY_DATAPATH ubPath);

MMP_ERR 	MMPD_AUI_GetMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info);
MMP_ERR 	MMPD_AUI_ReadMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info);
MMP_ERR 	MMPD_AUI_GetWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo);
MMP_ERR 	MMPD_AUI_ReadWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo);

MMP_ERR		MMPD_AUI_StartAudioPlay(void);
MMP_ERR		MMPD_AUI_PauseAudioPlay(void);
MMP_ERR		MMPD_AUI_ResumeAudioPlay(void);
MMP_ERR		MMPD_AUI_StopAudioPlay(void);
MMP_ERR		MMPD_AUI_CheckPlayEnd(void);

/// @}

#endif // _MMPD_AUI_H_

/// @end_ait_only
