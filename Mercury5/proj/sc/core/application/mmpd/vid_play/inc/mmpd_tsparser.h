/// @sigmastar_only
/**
 @file mmpd_tsparser.h
 @brief Header File for the Host TS Driver.
 @author Tunglin Hsieh
 @version 1.1
 @date 18-Mar-22 1.1 Updates the comments and change API to align with the System Software
 	Architecture
*/

#ifndef _MMPD_TS_PARSER_H_
#define _MMPD_TS_PARSER_H_

#include "mmp_lib.h"
#include "mmpd_mp4vdec.h" // for CODEC structure in parser and memory mode decoder API
#include "mmpd_vidplayer.h"
#include "mmpd_3gpparser.h"

MMP_ERR MMPD_TSPSR_Parse(const MMP_ULONG file_size,MMP_VID_FILEVALIDATION *pFileValidation,MMP_BOOL bCardMode);
MMP_ERR MMPD_TSPSR_Predecode(MMP_BOOL bCardMode,MMP_BOOL bDecodeAudio, MMP_BOOL bDecodeVideo, MMP_ULONG *sample_rate);
MMP_ERR MMPD_TSPSR_SeekByTime(const MMP_ULONG ulTargetTime,MMP_BOOL bCardMode, MMP_ULONG ulSeekOption);
MMP_ERR MMPD_TSPSR_FeedData(MMP_BOOL *bFinished);
MMP_ERR MMPD_TSPSR_Init(const MMP_ULONG ulDefaultBSAddress);
#endif // _INCLUDES_H_
/// @end_sigmastar_only
