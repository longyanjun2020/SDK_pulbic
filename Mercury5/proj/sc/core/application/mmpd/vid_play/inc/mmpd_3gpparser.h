/// @ait_only
/**
 @file mmpd_3gpparser.h
 @brief Header File for the Host 3GP Driver.
 @author Truman Yang
 @version 1.1
 @date 08-Jun-06 1.1 Updates the comments and change API to align with the System Software
 	Architecture
*/

#ifndef _MMPD_3GP_PARSER_H_
#define _MMPD_3GP_PARSER_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_mp4vdec.h"
#include "mmpd_vidplayer.h"
//#include "ait_utility.h"
#include "mmp_vidplay_inc.h"
#include "mmpf_3gpparser.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define NEAR_RING_BUFFER    			(2)
#define RING_BUFFER         			(3)

#define MMPD_VIDPSR_SEEK_NORMAL      	(0x00000000)
#define MMPD_VIDPSR_SEEK_PRECISE     	(0x00000001)
#define MMPD_VIDPSR_NEXT_KEYFRAME    	(0x00000002)
#define MMPD_VIDPSR_SEEK_AUDIO_ONLY  	(0x00000004)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef MMP_ERR (sParser_Parse_Func)     (const MMP_ULONG file_size,MMP_VID_FILEVALIDATION *fileValidation,MMP_BOOL bCardMode);
typedef MMP_ERR (sParser_Predecode_Func) (MMP_BOOL bCardMode, MMP_BOOL bDecodeAudio, MMP_BOOL bDecodeVideo, MMP_ULONG *sample_rate);
typedef MMP_ERR (sParser_SeekByTime_Func)(const MMP_ULONG ulTime,MMP_BOOL bCardMode, MMP_ULONG ulSeekOption);

typedef sParser_Parse_Func* 		sParser_Parse_FuncPtr;
typedef sParser_Predecode_Func*	    sParser_Predecode_FuncPtr; 
typedef sParser_SeekByTime_Func*	sParser_SeekByTime_FuncPtr;

typedef struct _MMPD_VIDPSR_FUNC {
    sParser_Parse_FuncPtr			MMPD_VIDPSR_Parse;
	sParser_Predecode_FuncPtr		MMPD_VIDPSR_Predecode; 
	sParser_SeekByTime_FuncPtr		MMPD_VIDPSR_SeekByTime;
} MMPD_VIDPSR_FUNC;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/** @addtogroup MMPD_3GPPSR
 *  @{
 */
MMP_ERR MMPD_VIDPSR_SetVideoBSAddr(const MMP_ULONG ulVideoBSAddr, const MMP_ULONG ulVideoBSSize, MMP_ULONG ulVideoBufType, MMP_BOOL bGetFrame);
MMP_ERR MMPD_VIDPSR_SetAudioBSAddr(const MMP_ULONG ulAudioBSAddr, const MMP_ULONG ulAudioBSSize);
MMP_ERR MMPD_VIDPSR_GetParameter(const MMPD_VIDPLAY_PARAMETER parameter, void* output);
MMP_ERR MMPD_VIDPSR_SetParameter(const MMPD_VIDPLAY_PARAMETER parameter, const MMP_ULONG value);
MMP_ERR MMPD_VIDPSR_SetParameters(const MMPD_VIDPLAY_PARAMETER parameter, const MMP_ULONG ulParam1, 
                                  const MMP_ULONG ulParam2, const MMP_ULONG ulParam3, const MMP_ULONG ulParam4, const MMP_USHORT usWidth, const MMP_USHORT usHeight);
MMP_ERR MMPD_3GPPSR_Parse(const MMP_ULONG file_size,MMP_VID_FILEVALIDATION *pFileValidation,MMP_BOOL bCardMode);
MMP_ERR MMPD_VIDPSR_SetCardMode(MMP_BOOL bCardMode,void* FileHandle);
MMP_ERR MMPD_VIDPSR_SetFileName(const MMP_ULONG ulFileNameAddr, const MMP_BYTE* ubFilename, MMP_USHORT usLength,MMP_ULONG  *ParserType);
MMP_ERR MMPD_VIDPSR_GetFileInfo(MMP_VIDEO_CONTAINER_INFO* pInfo,MMP_BOOL bCardMode);
MMP_ERR MMPD_3GPPSR_GetContainerInfo(MMP_BYTE *szFilename, MMP_ULONG ulFileNameLength,MMP_VIDEO_CONTAINER_INFO* pInfo);

// Playback control
MMP_ERR MMPD_3GPPSR_Predecode(MMP_BOOL bCardMode,MMP_BOOL bDecodeAudio, MMP_BOOL bDecodeVideo, MMP_ULONG *sample_rate);
MMP_ERR MMPD_3GPPSR_SeekByTime(const MMP_ULONG ulTargetTime,MMP_BOOL bCardMode, MMP_ULONG ulSeekOption);

MMP_ERR MMPD_VIDPSR_SetHandShakeAddr(const MMP_ULONG ulAddr, const MMP_ULONG ulBSSize);
MMP_ERR MMPD_VIDPSR_GetDepackBufSize(MMP_ULONG *ulDepackSize);

// For WMV
MMP_ERR MMPD_WMVPSR_Parse(const MMP_ULONG file_size,MMP_VID_FILEVALIDATION *fileValidation,MMP_BOOL bCardMode);

// For software decoder
MMP_ERR MMPD_VIDPSR_SetSWVidBuffer(MMP_ULONG ulBufStart, MMP_ULONG ulBufSize, MMP_ULONG ulBSSize);
MMP_ERR MMPD_VIDPSR_GetSWVidBufStart(MMP_ULONG *ulBufStart);
MMP_ERR MMPD_VIDPSR_GetSWVidBufferUsed(MMP_ULONG *ulBufSize, MMP_ULONG *ulBSBufSize);
MMP_ERR MMPD_VIDPSR_SetSWVidWorkingBuf(void);
MMP_ERR MMPD_VIDPSR_GetSWVidWorkingBufSize(void);
MMP_ERR MMPD_VIDPSR_GetUserDataInfo(MMP_ULONG *ulUserDataAddr);
/// @}

#endif // _MMPD_3GPPARSER_H_

/// @end_ait_only
