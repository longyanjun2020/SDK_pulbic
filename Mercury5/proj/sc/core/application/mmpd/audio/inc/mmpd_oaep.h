//==============================================================================
//
//  File        : mmpd_oaep.h
//  Description : OAEP setting
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmpd_oaep.h
 *  @brief Header File for OAEP processing
 *  @author Penguin Torng
 *  @version 1.0
 */

#ifndef _MMPD_OAEP_H_
#define _MMPD_OAEP_H_

/** @addtogroup MMPS_AUDIO
@{
*/

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPD_OAEP_PAREMETER
{
	MMPD_OAEP_EFFECT_TYPE	= 0x00,
	MMPD_OAEP_PLAYING_MODE	= 0x01,
	MMPD_OAEP_AUDIO_OUT_TYPE= 0x02
} MMPD_OAEP_PAREMETER;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR  MMPD_OAEP_SetEffectType(MMP_ULONG ulEffectType);
MMP_ERR  MMPD_OAEP_SetPlayingMode(MMP_ULONG ulPlayingMode);
MMP_ERR  MMPD_OAEP_SetAudioOutType(MMP_ULONG ulAudioOutType);

/// @}

#endif // _MMPS_OAEP_H_
