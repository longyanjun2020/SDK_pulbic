//==============================================================================
//
//  File        : mmpd_oaep.c
//  Description : OAEP setting
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmpd_oaep.c
 *  @brief The Device Driver for LGE OAEP control function
 *  @author Penguin Torng
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmph_hif.h"
#include "mmpd_oaep.h"
#include "os_wrap.h"

/** @addtogroup MMPD_AUDIO
@{
*/

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_OAEP_SetEffectType
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_OAEP_SetEffectType(MMP_ULONG ulEffectType)
{
 	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
 	
 	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMPD_OAEP_EFFECT_TYPE);
 	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulEffectType);
	MMPH_HIF_SendCmd(GRP_IDX_AUD, SET_OAEP_PARAMETER | HIF_AUD_CMD_AUDIO_EQ);
	
 	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
 	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_OAEP_SetPlayingMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_OAEP_SetPlayingMode(MMP_ULONG ulPlayingMode)
{
 	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
 	
 	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMPD_OAEP_PLAYING_MODE);
 	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulPlayingMode);
	MMPH_HIF_SendCmd(GRP_IDX_AUD, SET_OAEP_PARAMETER | HIF_AUD_CMD_AUDIO_EQ);
	
 	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
 	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_OAEP_SetAudioOutType
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_OAEP_SetAudioOutType(MMP_ULONG ulAudioOutType)
{
 	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
 	
 	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMPD_OAEP_AUDIO_OUT_TYPE);
 	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulAudioOutType);
	MMPH_HIF_SendCmd(GRP_IDX_AUD, SET_OAEP_PARAMETER | HIF_AUD_CMD_AUDIO_EQ);
	
 	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
 	return MMP_ERR_NONE;
}