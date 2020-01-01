/**
 @file mmpf_3gpparser.h
 @brief Header function of 3gp processor
 @author Truman Yang
 @version 1.0 Original Version
*/

#ifndef _MMPF_3GPPARSER_H_
#define _MMPF_3GPPARSER_H_

#include "includes_fw.h"
#include "mmpf_media_struct.h"
#include "mmp_vidplay_inc.h"

//==============================================================================
//                                IPC SECTION
//==============================================================================
/** @addtogroup MMPF_3GPP
@{
*/
	/** @brief The validation of the file

	Used to check if the firmware is able to play the file.
	Sometimes the file is invalid but it still has the change to play it.
	Such as unsupported frame rate, say 60 frames per second video but with small QCIF size and low bit rate.
	We leave the decision to the upper layer API.
	*/
	typedef enum MMP_VID_FILEVALIDATION {
	    MMP_VID_FILE_VALID = 0,           ///< The loaded firmware could play the file.
	    MMP_VID_INVALID_FILE_NAME,        ///< Cannot find the file, including a invalid file path.
	    MMP_VID_UNSUPPORTED_FILE,         ///< The file is not able to be parsed correctly.
	    MMP_VID_NO_AV_TRACK,              ///< No audio and video track.
	    MMP_VID_NEED_TO_CHANGE_FIRMWARE,  /**< The loaded firmware could not play the file, but there is another firmware
	                                            available. The file might be played if using the correct firmware. */
	    MMP_VID_UNSUPPORTED_AUDIO,        /**< The file is correctly parsed but the CODEC is unsupported. No other firmware
	                                            could play the this file. Such as 3GP file with H.263 + WMA */
	    MMP_VID_UNSUPPORTED_VIDEO,        /**< The file is correctly parsed but the CODEC is unsupported. No other firmware
	                                            could play the this file. Such as 3GP file with H.263 + WMA */
	    MMP_VID_UNSUPPORTED_SIZE,         /**< The resolution is not supported. This is due to memory limitation in most cases.
	                                            Other common reason is the width or height is not the multiple of 16. */
	    MMP_VID_UNSUPPORTED_SAMPLING_RATE,/**< The sampling rate is not supported. Such as a 120FPS video, or a 96kHz, 37kHz
	                                            audio.*/
	    MMP_VID_UNSUPPORTED_FILE_PARAMETERS, /**< Basically the file is correct, but the firmware cannot play it.
	                                            Because of some other reason. such as unsupported sampling rate.*/
	    MMP_VID_UNKNOWN_FILE_HEADER,
	    MMP_VID_UNKNOWN_INVALIDATION,      ///< Other reason, for example: invalid state transition
	    MMP_VID_FILE_VALIDATION_MAX
	} MMP_VID_FILEVALIDATION;

    typedef enum MMPF_3GPPLAY_PLAYSPEED_MODE {
        MMPF_3GPPLAY_PLAYSPEED_NORMAL,
        MMPF_3GPPLAY_PLAYSPEED_FAST_FORWARD,
        MMPF_3GPPLAY_PLAYSPEED_FAST_BACKWARD,
        MMPF_3GPPLAY_PLAYSPEED_2X,
        MMPF_3GPPLAY_PLAYSPEED_DIVIDE_2
    }MMPF_3GPPLAY_PLAYSPEED_MODE;

// This header uses the audio type and video type IPC enum so they had to be put after these
#include "mmp_3gpparser.h"

/** @} */ // end of IPC
//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

#define MMPF_VIDPSR_SEEK_NORMAL   			(0x00000000)
#define MMPF_VIDPSR_SEEK_PRECISE  			(0x00000001)
#define MMPF_VIDPSR_NEXT_KEYFRAME 			(0x00000002)
#define MMPF_VIDPSR_SEEK_AUDIO_ONLY		 	(0x00000004)
#define MMPF_VIDPSR_SEEK_NEARESTKEY 		(0x00000008)
#define MMPF_VIDPSR_SEEK_PRECISE_WITH_IDX 	(0x00000010)
#define MMPF_VIDPSR_SEEK_PREPARE_FW 		(0x00000020)
#define MMPF_VIDPSR_SEEK_PREPARE_BW 		(0x00000040)
#define MMPF_VIDPSR_SEEK_FILE_START         (0x00000080)
//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

/** The depack buffer cache size. Set to one page of the file system

It must be a power to 2 because the CachePosMask is define as this value - 1
*/
#define DEPACK_CACHE_SIZE (8*1024)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef MMP_ERR (Parser_Init_Func)(void);
typedef MMP_ERR (Parser_Deinit_Func)(void);
typedef MMP_ERR (Parser_Demux_Func)(void);
typedef MMP_VID_FILEVALIDATION (Parser_Parser_Func)(void);
typedef MMP_ERR (Parser_SeekByTime_Func)(const MMP_LONG ulTime, MMP_ULONG ulSeekOption);

typedef Parser_Init_Func*   	Parser_Init_FuncPtr;
typedef Parser_Deinit_Func*   	Parser_Deinit_FuncPtr;
typedef Parser_Demux_Func*  	Parser_Demux_FuncPtr;
typedef Parser_Parser_Func* 	Parser_Parser_FuncPtr;
typedef Parser_SeekByTime_Func* Parser_SeekByTime_FuncPtr;

typedef struct {
    Parser_Init_FuncPtr     	MMPF_PSR_Init;
    Parser_Deinit_FuncPtr   	MMPF_PSR_Deinit;
    Parser_Demux_FuncPtr    	MMPF_PSR_Demux;
    Parser_Parser_FuncPtr   	MMPF_PSR_Parser;
    Parser_SeekByTime_FuncPtr   MMPF_PSR_SeekByTime;
} MMPF_PSR_FUNC;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void    MMPF_BS_ResetBuffer(void);
void    MMPF_BS_InitBufInfoStruc(MMP_ULONG ulVideoInAddr, const MMP_ULONG ulLength,MMP_ULONG buffer_type);

MMP_ERR MMPF_VIDPSR_OpenFileForDepackCache(MMP_BYTE *fileName);
MMP_ERR MMPF_3GPPSR_Demux(void);
void    MMPF_PSR_SetVideoInBuffers(const MMP_ULONG ulVideoInAddr, const MMP_ULONG ulLength,MMP_ULONG buffer_type);
MMP_ERR MMPF_3GPPSR_SetFileName(const MMP_ULONG ulFilenameaddr);

MMP_ERR MMPF_3GPPSR_SeekByTime(const MMP_LONG ulTime, MMP_ULONG ulSeekOption);
MMP_VID_FILEVALIDATION MMPF_3GPPSR_Parse(void);

MMP_ERR MMPF_VIDPSR_TestVideoSeekable(MMP_ULONG ulTime, MMP_BOOL bCheckVideoOnly);

void    MMPF_VIDPSR_SetDepackBufAddr(const MMP_ULONG address);
MMP_ERR MMPF_VIDPSR_GetCommonInfo(MMP_VIDEO_CONTAINER_INFO **pInfo);
MMP_ERR MMPF_VIDPSR_GetParserType(MMP_ULONG *pParserType);
MMP_ERR MMPF_3GPPSR_GetAudioTimeBase(MMP_ULONG *pData);
MMP_ERR MMPF_3GPPSR_GetVideoInBuffers(MMP_ULONG* ulVideoInAddr, MMP_ULONG *ulLength,MMP_ULONG *ulBufType);

MMP_ERR MMPF_3GPPSR_RegisterDemux(const MMP_USHORT usDemuxOption,MMP_UBYTE bWait);
MMP_ERR MMPF_3GPPSR_Init(void);
void    MMPF_PSR_Reset(void);
#if (EN_SPEED_UP_VID & CACHE_HDL)
MMP_ERR MMPF_3GPPSR_FileObjCopy(const MMP_ULONG ulIndexTo, const MMP_ULONG ulIndexFrom);
MMP_ERR MMPF_3GPPSR_InitParseObjByTrack(MMP_ULONG ulTrack, MMP_ULONG ulAtomType);
#endif //#if (EN_SPEED_UP_CACHE_HDL == 1)
MMP_VID_FILEVALIDATION MMPF_3GPPSR_ParseEx(MMP_VIDEO_CONTAINER_INFO* pInfo, MMP_BOOL bInitCodec);
MMP_VID_FILEVALIDATION MMPF_AVIPSR_ParseEx(MMP_VIDEO_CONTAINER_INFO* pInfo, MMP_BOOL bInitCodec);
MMP_ERR MMPF_3GPPSR_GetState(MMP_M_STATE *state);
MMP_ERR MMPF_3GPPSR_SetState(MMP_M_STATE  state);

#if (VIDEO_BGPARSER_EN == 1)
void MMPF_VIDPSR_CloseBGParser(MMP_ULONG ulTimeOut);
#endif
#if defined(__RTK_OS__)
MMP_ERR MMPF_PSR_StartCodePadding(MMP_UBYTE *ptr);
#endif
/** @} */ // end of group MMPF_3GPP

MMP_ERR MMPF_WMVPSR_SeekByTime(const MMP_LONG ulTime, MMP_ULONG ulSeekOption);

#endif