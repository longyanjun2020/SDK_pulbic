//==============================================================================
//
//  File        : mmps_oaep.c
//  Description : OAEP setting
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_oaep.c
 *  @brief The LGE OAEP control function
 *  @author Penguin Torng
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_oaep.h"

/** @addtogroup MMPS_AUDIO
@{
*/

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : MMPS_OAEP_SetEffectType
//  Description :
//------------------------------------------------------------------------------
MMP_ERR  MMPS_OAEP_SetEffectType(MMP_ULONG ulEffectType)
{
    return MMPD_OAEP_SetEffectType(ulEffectType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_OAEP_SetPlayingMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR  MMPS_OAEP_SetPlayingMode(MMP_ULONG ulPlayingMode)
{
    return MMPD_OAEP_SetPlayingMode(ulPlayingMode);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_OAEP_SetAudioOutType
//  Description :
//------------------------------------------------------------------------------
MMP_ERR  MMPS_OAEP_SetAudioOutType(MMP_ULONG ulAudioOutType)
{
    return MMPD_OAEP_SetAudioOutType(ulAudioOutType);
}

/// @}



