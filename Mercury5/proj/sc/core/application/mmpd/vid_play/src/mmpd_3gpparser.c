/// @ait_only
/** @file mmpd_3gpparser.c
@brief 3GP Parser Control driver and host side parser
@author Truman Yang
@author Philip Lin,
@version 1.0 Original version
*/

#include "mmp_lib.h"
#include "mmpd_3gpparser.h"
#include "mmpd_h264dec.h"
#include "mmpd_system.h"
#include "mmph_hif.h"
#include "mmp_3gpparser.h"
#include "mmpf_3gpparser.h"
#include "lib_retina.h"

#if 0
void _____Operations_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPPSR_Parse
//  Description :
//------------------------------------------------------------------------------
/** @brief Parsing 3gp file
@param[in] file_size file size
@param[out] pFileValidation File validation from the firmware
@param[in] bCardMode card mode or mem mode
@return Always return success now.
*/
MMP_ERR MMPD_3GPPSR_Parse(const MMP_ULONG file_size, MMP_VID_FILEVALIDATION *fileValidation, MMP_BOOL bCardMode)
{
	MMP_ERR	mmpstatus;

    MMPD_VIDPSR_SetSWVidWorkingBuf();
	
    if (bCardMode) {
    
    	MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
        mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_PARSE);

		if (mmpstatus == MMP_ERR_NONE) {
        	MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
		}
        if (mmpstatus == MMP_ERR_NONE) {
    		*fileValidation = (MMP_VID_FILEVALIDATION)MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
    		if (*fileValidation != MMP_VID_FILE_VALID) {
    			mmpstatus = MMP_VIDPSR_ERR_CONTENT_PIPE_OPEN_FAILED;
    		}
        }
        MMPH_HIF_ReleaseSem(GRP_IDX_VID);
        
        MMPD_VIDPSR_GetSWVidWorkingBufSize();
    }

	return mmpstatus;
}

/** @brief Playback control: Predecode
@param[in]  bCardMode card mode or mem mode
@param[in]  bDecodeAudio decode audio or not
@param[out] sample_rate audio sampling rate
@pre The firmware is loaded and free to response
@return The status from the firmware
*/
MMP_ERR MMPD_3GPPSR_Predecode(MMP_BOOL bCardMode,MMP_BOOL bDecodeAudio, MMP_BOOL bDecodeVideo, MMP_ULONG *sample_rate)
{
    MMP_ERR	mmpstatus;
       
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, bDecodeAudio);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8, bDecodeVideo);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, VIDPLAY_PREDECODE | HIF_VID_CMD_PARSER);
	
	if (mmpstatus == MMP_ERR_NONE) {
		mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
	}
	if (mmpstatus == MMP_ERR_NONE) {
	    *sample_rate = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
	}	    
    
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return mmpstatus;
}

/** @brief Seek the video by time in millisecond.

@param[in] ulTargetTime      Time in millisecond
@param[in] bCardMode         card mode or mem mode
@param[in] bSeekToPrecisePos Seek to precise position or not (I frame only)
@return The status of the function call
@retval MMP_M_ERR_BAD_PARAMETER When the percentage is out of range.
*/
MMP_ERR MMPD_3GPPSR_SeekByTime(const MMP_ULONG ulTime,MMP_BOOL bCardMode, MMP_ULONG ulSeekOption)
{
	MMP_ERR	mmpstatus;

    if (bCardMode) {
    
        MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, MMPD_VIDPLAY_PARAMETER_SEEK_BY_TIME);
        MMPH_HIF_SetParameterL(GRP_IDX_VID, 8, ulTime);
        MMPH_HIF_SetParameterL(GRP_IDX_VID, 12, ulSeekOption);
        
        mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_VIDPLAY_OTHER | VIDPLAY_SET_PARAMETER);

		if (mmpstatus == MMP_ERR_NONE) {
			mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
		}
	    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    }
    
    return mmpstatus;
}

#if 0
void _____Property_Interface_____(){}
#endif

/** @brief Choose to use card mode or not
@param bCardMode card mode or mem mode
@param FileHandle file handle
@return MMP_ERR_NONE
*/
MMP_ERR MMPD_VIDPSR_SetCardMode(MMP_BOOL bCardMode, void* FileHandle)
{
    MMP_ERR	mmpstatus;
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);    
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, bCardMode);
    
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, VIDEO_DECODE_STORAGE_PATH | HIF_VID_CMD_PARSER);
   
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_VIDPSR_SetFileName
//  Description :
//------------------------------------------------------------------------------
/** @brief Set File Name for play
@param[in] ulFileNameAddr The memory address to put file name in the firmware
@param[in] ubFilename File name
@param[in] usLength Length of file name. Max size is 64. This value will be sent to the firmware
@return MMPD_3GPPLAY_SUCCESS
*/
MMP_ERR MMPD_VIDPSR_SetFileName(const MMP_ULONG ulFileNameAddr, const MMP_BYTE* ubFilename,
                                MMP_USHORT usLength, MMP_ULONG  *ParserType)
{
	MMP_UBYTE	null = 0;
    MMP_ERR		mmpstatus;
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    
    MMPH_HIF_MemCopyHostToDev(ulFileNameAddr, (MMP_UBYTE*)ubFilename, usLength+1);
    MMPH_HIF_MemCopyHostToDev(ulFileNameAddr + usLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(ulFileNameAddr + usLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulFileNameAddr);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDEO_DECODE_FILE_NAME);

	if (mmpstatus == MMP_ERR_NONE) {
    	mmpstatus   = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    	*ParserType = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
	}

    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_VIDPSR_SetHandShakeAddr
//  Description :
//------------------------------------------------------------------------------
/** @brief Set hand-shake buffer for 3gp parser
@param[in] ulAddr  buffer address
@param[in] ulSize  buffer size
@return The status of the function call
*/
MMP_ERR MMPD_VIDPSR_SetHandShakeAddr(const MMP_ULONG ulAddr, const MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, ulSize);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDEO_SET_HANDSHAKE_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return MMP_ERR_NONE;
}

/** @brief Set bitstream addresses to the firmware in host-parsed memory mode

@param[in] ulVideoBSAddr  The video bitstream address in the host
@param[in] ulVideoBSSize  The video bitstream size in the host
@param[in] ulVideoBufType The video bitstream buffer type
@return The status of the function call
*/
MMP_ERR MMPD_VIDPSR_SetVideoBSAddr(const MMP_ULONG ulVideoBSAddr, const MMP_ULONG ulVideoBSSize, 
								   MMP_ULONG ulVideoBufType, MMP_BOOL bGetFrame)
{
    MMPD_H264DEC_SetBitstreamAddr(ulVideoBSAddr, ulVideoBSSize);
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4,  MMPD_VIDPLAY_PARAMETER_VIDEO_BITSTREAM);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8,  ulVideoBSAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 12, ulVideoBSSize);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 16, ulVideoBufType);
    
    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_SET_PARAMETER);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return MMP_ERR_NONE;
}

/** @brief Set bitstream addresses to the firmware in host-parsed memory mode
@param[in] ulAudioBSAddr The audio bitstream address in the host
@param[in] ulAudioBSSize The audio bitstream size in the host. Set 0 to avoid passing these setting
                         the firmware.
@return The status of the function call
*/
MMP_ERR MMPD_VIDPSR_SetAudioBSAddr(const MMP_ULONG ulAudioBSAddr, const MMP_ULONG ulAudioBSSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4 , MMPD_VIDPLAY_PARAMETER_AUDIO_BITSTREAM);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8 , ulAudioBSAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 12, ulAudioBSSize);
    
    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_SET_PARAMETER);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return MMP_ERR_NONE;     
}

/** @brief Map the command from the parameter to the hif commnad

@param[in] parameter The parameter
@return The mapped command
*/
static MMP_USHORT MMPD_VIDPSR_MapCommand(const MMPD_VIDPLAY_PARAMETER parameter)
{
    MMP_USHORT usCmd;
    switch (parameter & MMPD_VIDPLAY_PARAMETER_GROUP) {
        case MMPD_VIDPLAY_PARAMETER_PARSER_BASE:
            usCmd = HIF_VID_CMD_PARSER;
            break;
        case MMPD_VIDPLAY_PARAMETER_DECODER_BASE:
            usCmd = HIF_VID_CMD_VIDEO_DECODER;
            break;
        case MMPD_VIDPLAY_PARAMETER_POSTPROCESSOR_BASE:
            usCmd = HIF_VID_CMD_POST_PROCESSOR;
            break;
        case MMPD_VIDPLAY_PARAMETER_RENDERER_BASE:
            usCmd = HIF_VID_CMD_RENDERER;
            break;
        case MMPD_VIDPLAY_PARAMETER_CLOCK_BASE:
            usCmd = HIF_VID_CMD_VIDPLAY_CLOCK;
            break;
        case MMPD_VIDPLAY_PARAMETER_INFO_BASE:
            usCmd = HIF_VID_CMD_VIDPLAY_INFO;
            break;
        default:
            usCmd = HIF_VID_CMD_VIDPLAY_OTHER;
            break;
    }
    return usCmd;
}

/** @brief Get other parameter

There are too many parameters. Use this type to enumerate the types that are seldom used and
	not listed in another group. By this type, all parameters with long can simply use
	MMPS_VIDPLAY_GetParameter and MMPS_VIDPLAY_SetParameter to access. This can also reduce
	the MMPD layer interface.
@param[in] parameter Which paramaters to get
@param[out] output The MMP_ULONG pointer of the parameter
@return the result of the function call
*/
MMP_ERR MMPD_VIDPSR_GetParameter(const MMPD_VIDPLAY_PARAMETER parameter, void* output)
{
    MMP_USHORT size;
    MMP_ULONG temp;
    MMP_ERR		mmpstatus;
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);    
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, parameter);
	
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, MMPD_VIDPSR_MapCommand(parameter) | VIDPLAY_GET_PARAMETER);

    switch(parameter) {
    case MMPD_VIDPLAY_PARAMETER_AUDIO_FORMAT:
        size = sizeof(MMP_VID_AUDIOTYPE);
        break;
    case MMPD_VIDPLAY_PARAMETER_VIDEO_FORMAT:
        size = sizeof(MMP_VID_VIDEOTYPE);
        break;
    case MMPD_VIDPLAY_PARAMETER_PLAYER_STATE:
        size = sizeof(MMP_M_STATE);
        break;
    case MMPD_VIDPLAY_PARAMETER_SUPPORTED_AUDIO:
        size = sizeof(MMP_VID_AUDIOTYPE);
        break;
    default:
        size = 4;
        break;
    }
	
	if (mmpstatus == MMP_ERR_NONE) {
		mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
	}
		
	if (mmpstatus == MMP_ERR_NONE) {	
	    temp = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
    	if (size == 4) {
	        *((MMP_ULONG*)output) = temp;
    	}
	    else if (size == 2) {
    	    *((MMP_USHORT*)output) = temp;
	    }
    	else if (size == 1) {
        	*((MMP_UBYTE*)output) = temp;
	    }
	}	    
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
	return mmpstatus;
}

/** @brief Set other parameter

There are too many parameters. Use this type to enumerate the types that are seldom used and
	not listed in another group. By this type, all parameters with long can simply use
	MMPS_VIDPLAY_GetParameter and MMPS_VIDPLAY_SetParameter to access. This can also reduce
	the MMPD layer interface.
@param[in] parameter Which paramaters to get
@param[out] value The MMP_ULONG value of the parameter
@return the result of the function call
*/
MMP_ERR MMPD_VIDPSR_SetParameter(const MMPD_VIDPLAY_PARAMETER parameter, const MMP_ULONG value)
{
	MMP_ERR	mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, parameter);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8, value);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, MMPD_VIDPSR_MapCommand(parameter) | VIDPLAY_SET_PARAMETER);
    
	if (mmpstatus == MMP_ERR_NONE) {
		mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
	}
	MMPH_HIF_ReleaseSem(GRP_IDX_VID);
	
	return mmpstatus;
}

/** @brief Set other parameters

The same as MMPD_3GPPLAY_SetParameter but set many MMP_ULONGs at the same time.
It useful to set parameter with multiple values, such as bitstream buffers.
@param[in] parameter Which parameter to set
@param[in] ulParam1 The first parameter value
@param[in] ulParam2 The second parameter value
@param[in] ulParam3 The third parameter value
@param[in] ulParam4 The forth parameter value
@return the result of the function call, returned from firmware
*/
MMP_ERR MMPD_VIDPSR_SetParameters(const MMPD_VIDPLAY_PARAMETER parameter, 
								  const MMP_ULONG ulParam1, 
        						  const MMP_ULONG ulParam2, 
        						  const MMP_ULONG ulParam3, 
        						  const MMP_ULONG ulParam4, 
        						  const MMP_USHORT usWidth, const MMP_USHORT usHeight)
{
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 12, ulParam2);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 16, ulParam3);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 20, ulParam4);
    MMPH_HIF_SetParameterW(GRP_IDX_VID, 0, usWidth);
    MMPH_HIF_SetParameterW(GRP_IDX_VID, 2, usHeight);
    
    return MMPD_VIDPSR_SetParameter(parameter, ulParam1);
}

/** @brief Get the general file info from the 3GP parser.

This infomation typically does not change during the playing
@param[out] pFileInfo The pointer of the structure to get the general video file info
@param[in] bCardMode card mode or mem mode
It should be able to be used for other parser later.
@return MMP_ERR
*/
MMP_ERR MMPD_VIDPSR_GetFileInfo(MMP_VIDEO_CONTAINER_INFO* pInfo, MMP_BOOL bCardMode)
{
	MMP_ERR	mmpstatus = MMP_ERR_NONE;
    MMP_UBYTE i = 0;

    if (bCardMode) {

    	// Get total track number first.
        MMPH_HIF_WaitSem(GRP_IDX_VID, 0);

        mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_GET_PARAMETER | VIDPARAM_SET_GETTRACKNUM);

		if (mmpstatus == MMP_ERR_NONE) {
			mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
		}
		if (mmpstatus) { 
			MMPH_HIF_ReleaseSem(GRP_IDX_VID);
			return mmpstatus;
        }
        pInfo->videoTrackNum = MMPH_HIF_GetParameterB(GRP_IDX_VID, 4);

        for (i = 0 ; i < pInfo->videoTrackNum; i++) {

            MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, i);
            mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_GET_PARAMETER | VIDPARAM_VIDEO_RESOL);
    	    
    		if (mmpstatus == MMP_ERR_NONE) {
    			mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    		}
    		if (mmpstatus) { 
    			MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    			return mmpstatus;
            }
            pInfo->video_info[i].width                 = MMPH_HIF_GetParameterW(GRP_IDX_VID, 4);
            pInfo->video_info[i].height                = MMPH_HIF_GetParameterW(GRP_IDX_VID, 6);
            pInfo->video_info[i].cropping_left         = MMPH_HIF_GetParameterW(GRP_IDX_VID, 8);
            pInfo->video_info[i].cropping_top          = MMPH_HIF_GetParameterW(GRP_IDX_VID, 10);
            pInfo->video_info[i].cropping_right        = MMPH_HIF_GetParameterW(GRP_IDX_VID, 12);
            pInfo->video_info[i].cropping_bottom       = MMPH_HIF_GetParameterW(GRP_IDX_VID, 14);
            pInfo->video_info[i].bInterlacedSequence   = 0;
            
            MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, i);
            mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_GET_PARAMETER | VIDPARAM_TOTAL_TIME);
    	    if (mmpstatus == MMP_ERR_NONE) {
    			mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    		}
    		if (mmpstatus) {
    		    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    			return mmpstatus;
            }
            pInfo->total_file_time              	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
            pInfo->audio_info.total_audio_time  	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 8);
            pInfo->video_info[i].total_video_time  	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 12);
            pInfo->file_size                    	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 16);
            pInfo->video_info[i].total_keyframe_num	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 20);

            MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, i);
            mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_GET_PARAMETER | VIDPARAM_FORMAT);
    	    if (mmpstatus == MMP_ERR_NONE) {
    			mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    		}
    		if (mmpstatus) {
    		    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    			return mmpstatus; 
            }
            pInfo->audio_info.format            	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
            pInfo->video_info[i].format            	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 8);
            pInfo->is_audio_available           	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 12);
            pInfo->is_video_available[i]           	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 16);
            pInfo->is_video_seekable[i]            	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 20);

            MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, i);
            mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_GET_PARAMETER | VIDPARAM_SAMPLING);
    	    if (mmpstatus == MMP_ERR_NONE) {
    			mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    		}
    		if (mmpstatus) {
    		    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    			return mmpstatus;
            }
            pInfo->audio_info.sampling_rate     	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
            pInfo->audio_info.channel_nums      	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 8);
            pInfo->audio_info.bitrate           	= MMPH_HIF_GetParameterL(GRP_IDX_VID, 12);
            pInfo->video_info[i].bitrate           = MMPH_HIF_GetParameterL(GRP_IDX_VID, 16);
            pInfo->video_info[i].fps               = MMPH_HIF_GetParameterL(GRP_IDX_VID, 20);
        }
        MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    }
    
    return mmpstatus;
}

/** @brief Get the general file user data information from 3GP parser.

This infomation typically does not change during the playing
@param[in] ubIndex get the index atom information in udat atom.
@param[out] AtomData: atom data
@param[out] ulAtomdataLength: atom data length
@param[out] ulAtomName: atom name
@param[out] ubExist: the atom for this index is exist or not.

It should be able to be used for other parser later.
@return MMP_ERR
*/
MMP_ERR MMPD_VIDPSR_GetUserDataInfo(MMP_ULONG *ulUserDataAddr)
{
	MMP_ERR	mmpstatus = MMP_ERR_NONE;
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_GET_PARAMETER | VIDPARAM_SET_GETUDTAINFO);
	if (mmpstatus == MMP_ERR_NONE) {
		mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
	}
	if (mmpstatus) { 
		MMPH_HIF_ReleaseSem(GRP_IDX_VID);
		return mmpstatus;
    }
    *ulUserDataAddr = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    return MMP_ERR_NONE;
}

/** @brief Get the depack buffer size

@param[out] ulDepackSize the depack buffer size
@return MMP_ERR
*/
MMP_ERR MMPD_VIDPSR_GetDepackBufSize(MMP_ULONG *ulDepackSize)
{
    MMP_ERR mmpstatus;
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_GET_PARAMETER | VIDPARAM_DEPACK_SIZE);
    
	if (mmpstatus == MMP_ERR_NONE) {
		mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
	}
	if (mmpstatus == MMP_ERR_NONE) {
		*ulDepackSize = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
	}

    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return mmpstatus;
}

/** @brief Get 3GP info by the HOST parser

@param[in] szFilename       filename
@param[in] ulFileNameLength filename length
@param[in] pInfo            information

@return The status of the function call. MMP_ERR_NONE for success.
*/
MMP_ERR MMPD_3GPPSR_GetContainerInfo(MMP_BYTE *szFilename, MMP_ULONG ulFileNameLength, MMP_VIDEO_CONTAINER_INFO* pInfo)
{
    MMP_ERR     error = MMP_ERR_NONE;
    MMP_ULONG   ulParserType;
    MMP_VID_FILEVALIDATION file_err = MMP_VID_FILE_VALID;

	file_err = MMPF_3GPPSR_SetFileName((const MMP_ULONG)szFilename);
    if (file_err != MMP_VID_FILE_VALID) {
        return file_err;
    }

	MMPF_VIDPSR_GetParserType(&ulParserType);
	
	switch(ulParserType){
	    case MMP_PSR_3GPPARSER:
	        file_err = MMPF_3GPPSR_ParseEx(pInfo, MMP_FALSE);
	    break;
        #if (MMP_AVIPARSER_SUPPORT)
	    case MMP_PSR_AVIPARSER:
	        file_err = MMPF_AVIPSR_ParseEx(pInfo, MMP_FALSE);
	    break;
        #endif
        #if (MMP_TSPARSER_SUPPORT)
	    case MMP_PSR_TSPARSER:
	        file_err = MMPF_TSPSR_ParseEx(pInfo, MMP_FALSE);
	    break;
        #endif
	    default:
	        // TBD
	    break;
	}

    if (file_err != MMP_VID_FILE_VALID) {
        error = MMP_VIDPSR_ERR_UNSUPPORTED_SETTING;
    }

	MMPF_VIDPSR_OpenFileForDepackCache(NULL);

    return error;
}

#if 0
void _____WMV_PLAYER____(){}
#endif

static MMP_ULONG m_ulVIDWorkingBufSize;
static MMP_ULONG m_ulVIDTempBSSize;
static MMP_ULONG m_ulVIDWorkingBufStart;

//------------------------------------------------------------------------------
//  Function    : MMPD_VIDPSR_SetSWVidBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_VIDPSR_SetSWVidBuffer(MMP_ULONG ulBufStart, MMP_ULONG ulBufSize, MMP_ULONG ulBSSize)
{
    m_ulVIDWorkingBufStart 	= ulBufStart;
    m_ulVIDTempBSSize 		= ulBSSize;
    m_ulVIDWorkingBufSize 	= ulBufSize;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_VIDPSR_GetSWVidBufStart
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_VIDPSR_GetSWVidBufStart(MMP_ULONG *ulBufStart)
{
    *ulBufStart = m_ulVIDWorkingBufStart;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_VIDPSR_GetSWVidBufferUsed
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_VIDPSR_GetSWVidBufferUsed(MMP_ULONG *ulBufSize, MMP_ULONG *ulBSBufSize)
{
    *ulBufSize	 = m_ulVIDWorkingBufSize;
    *ulBSBufSize = m_ulVIDTempBSSize;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_VIDPSR_SetSWVidWorkingBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_VIDPSR_SetSWVidWorkingBuf(void)
{
    MMP_ERR mmpstatus;
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, m_ulVIDWorkingBufStart);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDEO_SET_WORKINGBUF);
    
	if (mmpstatus == MMP_ERR_NONE) {
    	mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_VIDPSR_GetSWVidWorkingBufSize
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_VIDPSR_GetSWVidWorkingBufSize(void)
{
    MMP_ERR mmpstatus;
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDEO_GET_WORKINGBUFSIZE);
    
	if (mmpstatus == MMP_ERR_NONE) {
    	mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    }
    if (mmpstatus == MMP_ERR_NONE) {
        m_ulVIDWorkingBufSize = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
        m_ulVIDTempBSSize = MMPH_HIF_GetParameterL(GRP_IDX_VID, 8);
    }
    
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return mmpstatus;
}

/** @brief Parsing 3gp file
@param[in] file_size file size
@param[out] pFileValidation File validation from the firmware
@param[in] bCardMode card mode or mem mode
@return Always return success now.
*/
MMP_ERR MMPD_WMVPSR_Parse(const MMP_ULONG file_size,MMP_VID_FILEVALIDATION *fileValidation,MMP_BOOL bCardMode)
{
	MMP_ERR	mmpstatus;
    MMP_BOOL bParseAudio;
    
    MMPD_VIDPSR_SetSWVidWorkingBuf();
        	
    if (bCardMode) {
        
        MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, bParseAudio);
        
        mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_PARSER | VIDPLAY_PARSE);
        
		if (mmpstatus == MMP_ERR_NONE) {
        	mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
		}

		if (mmpstatus == MMP_ERR_NONE) {
    	    *fileValidation = (MMP_VID_FILEVALIDATION)MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
        }
        
        MMPH_HIF_ReleaseSem(GRP_IDX_VID);        
        MMPD_VIDPSR_GetSWVidWorkingBufSize();

        return mmpstatus;
    }

    return MMP_ERR_NONE;
}
