//==============================================================================
//
//  File        : mmps_aui.h
//  Description : Aui Player
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_aui.h
 *  @brief Header File for the Host Aui Player API.
 *  @author Penguin Torng
 *  @version 1.0
 */

#ifndef _MMPS_AUI_H_
#define _MMPS_AUI_H_

#include "mmps_audio.h"
#include "mmpd_aui.h"

/** @addtogroup MMPS_AUI
@{
*/


//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

typedef enum _MMPS_AUI_MEDIA_PATH {
    MMPS_AUI_MEDIA_PATH_CARD,       ///< Media operation by B/E file mode
    MMPS_AUI_MEDIA_PATH_MMP_MEM,    ///< Media operation by MMP memory
    MMPS_AUI_MEDIA_PATH_MAX
} MMPS_AUI_MEDIA_PATH;

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

MMP_ERR MMPS_AUI_SetMediaPath(MMPS_AUI_MEDIA_PATH mediapath);
MMP_ERR MMPS_AUI_InitializeMP3Play(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MP3_INFO *mp3info);
MMP_ERR MMPS_AUI_InitializeWAVPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WAV_INFO *wavinfo);
MMP_ERR MMPS_AUI_GetPlayStatus(MMPS_AUDIO_PLAY_STATUS *status);
#if 0
MMP_ERR MMPS_AUI_StartMP3Play(void);
MMP_ERR MMPS_AUI_PauseMP3Play(void);
MMP_ERR MMPS_AUI_ResumeMP3Play(void);
MMP_ERR MMPS_AUI_StopMP3Play(void);

MMP_ERR MMPS_AUI_StartWAVPlay(void);
MMP_ERR MMPS_AUI_PauseWAVPlay(void);
MMP_ERR MMPS_AUI_ResumeWAVPlay(void);
MMP_ERR MMPS_AUI_StopWAVPlay(void);
#endif
MMP_ERR MMPS_AUI_StartPlay(void);
MMP_ERR MMPS_AUI_StopPlay(void);


/// @end_ait_only
/// @}
#endif // _MMPS_AUI_H_
