/// @ait_only
//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
//#include "ait_utility.h"
#include "os_wrap.h"
#include "mmpd_audio.h"
#include "mmpd_aui.h"
#include "mmpd_system.h"
#include "mmph_hif.h"

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

/** @addtogroup MMPD_AUDIO
 *  @{
 */

static MMP_AUDIO_MP3_INFO   m_MP3FileInfo;
static MMP_AUDIO_WAV_INFO   m_WAVFileInfo;
static MMP_AUDIO_AMR_INFO   m_AMRFileInfo;

static MMP_ULONG            m_ulAudioPlayFileNameBufStart;
static MMP_ULONG            m_ulAudioParseFileNameBufStart;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//==============================================================================
//  Function    : MMPD_AUI_SetPlayFormat
//==============================================================================
/** 
    @brief  Set Audio Play Mode
    @param[in]  decodefmt: decode format
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPD_AUI_SetPlayFormat(MMP_AUDIO_DECODE_FMT decodefmt)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, decodefmt);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_FORMAT);
	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

	return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_SetPlayFileName
//==============================================================================
/** 
    @brief  Set Audio Play File Name
    @param[in] *bFileName : file name
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_SetPlayFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength)
{
    MMP_UBYTE null = 0;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayFileNameBufStart, (MMP_UBYTE *)bFileName, ulNameLength);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayFileNameBufStart + ulNameLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayFileNameBufStart + ulNameLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, m_ulAudioPlayFileNameBufStart);
    
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_FILE_NAME);

    if (MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0)) {
    	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_AUDIO_ERR_OPENFILE_FAIL;
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_SetPlayFileNameBuf
//==============================================================================
/** 
    @brief  Set Audio Play File Name Buffer Address
    @param[in] ulBufAddr : buffer address
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_SetPlayFileNameBuf(MMP_ULONG ulBufAddr)
{
	m_ulAudioPlayFileNameBufStart = ulBufAddr;
    return MMP_ERR_NONE;    
}

//==============================================================================
//  Function    : MMPD_AUI_PresetPlayFileNameBuf
//==============================================================================
/** 
    @brief  Preset Audio Play File Name Buffer Address
    @param[in] ulBufAddr : buffer address
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_PresetPlayFileNameBuf(MMP_ULONG ulBufAddr)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulBufAddr);
    
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PRESET_FILE_NAME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);    

    return MMP_ERR_NONE;    
}

//==============================================================================
//  Function    : MMPD_AUI_SetPlayBuf
//==============================================================================
/** 
    @brief  Set Audio Play Input  Stream Buffer
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size(must be power of 2)
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPD_AUI_SetPlayBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, ulSize);
    
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_SetPlayPath
//==============================================================================
/** 
    @brief  Set AUI Play Path
    @param[in]  ubPath : card mode or MMP memory path
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPD_AUI_SetPlayPath(MMPD_AUI_PLAY_DATAPATH ubPath)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
	MMPH_HIF_SetParameterB(GRP_IDX_AUD, 4, ubPath);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_PATH);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_GetPlayFileSize
//==============================================================================
/** 
    @brief  Get Audio Play File Size From Firmware(Card Mode)
    @param[out] *ulFileSize : file size (in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPD_AUI_GetPlayFileSize(MMP_ULONG *ulFileSize)
{  
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);

	MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_GET_FILE_SIZE);
	*ulFileSize = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
	return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_SetParseFormat
//==============================================================================
/** 
    @brief  Set Audio Play Mode
    @param[in]  decodefmt: decode format
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPD_AUI_SetParseFormat(MMP_AUDIO_DECODE_FMT decodefmt)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, decodefmt);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_FORMAT);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_SetParseFileName
//==============================================================================
/** 
    @brief  Set Audio File Name For Parsing
    @param[in] *bFileName : file name
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_SetParseFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength)
{
    MMP_UBYTE	null = 0;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioParseFileNameBufStart, (MMP_UBYTE *)bFileName, ulNameLength);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioParseFileNameBufStart + ulNameLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioParseFileNameBufStart + ulNameLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, m_ulAudioParseFileNameBufStart);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_FILE_NAME);

    if (MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0)) {
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_AUDIO_ERR_OPENFILE_FAIL;
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;    
}

//==============================================================================
//  Function    : MMPD_AUI_SetParseFileNameBuf
//==============================================================================
/** 
    @brief  Set Audio File Name Buffer Address For Parsing
    @param[in] ulBufAddr : buffer address
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_SetParseFileNameBuf(MMP_ULONG ulBufAddr)
{
	m_ulAudioParseFileNameBufStart = ulBufAddr;
    return MMP_ERR_NONE;    
}

//==============================================================================
//  Function    : MMPD_AUI_SetParseBuf
//==============================================================================
/** 
    @brief  Set Audio Play Input Stream Buffer For Parsing
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPD_AUI_SetParseBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, ulSize);
    
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_SetParsePath
//==============================================================================
/** 
    @brief  Set AUI Media Path For Parsing
    @param[in]  ubPath : card mode or MMP memory path
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPD_AUI_SetParsePath(MMPD_AUI_PLAY_DATAPATH ubPath)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
	MMPH_HIF_SetParameterB(GRP_IDX_AUD, 4, ubPath);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_PATH);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_GetMP3FileInfo
//==============================================================================
/** 
    @brief  Get MP3 File Info
    @param[out] *mp3info : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_GetMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info)
{	
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);

	MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_MP3FILEINFO);

	mp3info->ulBitRate      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
	mp3info->usSampleRate   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
	mp3info->usChans        = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
	mp3info->usLayer        = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8);
	mp3info->usVersion      = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 10);
	mp3info->usVbr          = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 12);
    mp3info->ulTotalTime    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 16);
    mp3info->usNotSupport   = 0;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if (mp3info->ulBitRate == 0) {
        printc("Unsupport BitRate = %d\r\n!", mp3info->ulBitRate);
	    mp3info->ulTotalTime = 0;
	    mp3info->usNotSupport = 1;
	}
    else if ((mp3info->usSampleRate < 8000) || (mp3info->usSampleRate > 48000)) {
        printc("Unsupport sample rate = %d\r\n!", mp3info->usSampleRate);
        mp3info->usNotSupport = 1;
    }

    m_MP3FileInfo = *mp3info;

	return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_ReadMP3FileInfo
//==============================================================================
/** 
    @brief  Read MP3 File Info
    @param[out] *mp3info : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_ReadMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info)
{
    *mp3info = m_MP3FileInfo;
    return MMP_ERR_NONE;	
}

//==============================================================================
//  Function    : MMPD_AUI_GetWAVFileInfo
//==============================================================================
/**
    @brief  Get WAV File Info
    @param[out] *wavinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_GetWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

    wavinfo->ulBitRate       = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    wavinfo->ulSampleRate    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 4);
    wavinfo->ulNewSampleRate = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 8);
    wavinfo->ulTotalTime     = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    wavinfo->usChans         = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 16);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    wavinfo->usNotSupport = 0;

    if (wavinfo->ulBitRate == 0) {
        wavinfo->ulTotalTime = 0;
        wavinfo->usNotSupport = 1;
    }
    else if ((wavinfo->ulSampleRate < 8000) || (wavinfo->ulSampleRate > 192000)) {
        PRINTF("Unsupport sample rate = %d\r\n!", wavinfo->ulNewSampleRate);
        wavinfo->usNotSupport = 1;
    }

    m_WAVFileInfo = *wavinfo;

    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_ReadWAVFileInfo
//==============================================================================
/** 
    @brief  Read WAV File Info
    @param[out] *wavinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_ReadWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo)
{
    *wavinfo = m_WAVFileInfo;
    return MMP_ERR_NONE;    
}

//==============================================================================
//  Function    : MMPD_AUI_GetAMRFileInfo
//==============================================================================
/**
    @brief  Get WAV File Info
    @param[out] *wavinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_GetAMRFileInfo(MMP_AUDIO_AMR_INFO *amrinfo)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

	#if 0
    amrinfo->ulBitRate       = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    amrinfo->ulSampleRate    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 4);
    amrinfo->ulNewSampleRate = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 8);
    amrinfo->ulTotalTime     = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    amrinfo->usChans         = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 16);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    amrinfo->usNotSupport = 0;

    if (amrinfo->ulBitRate == 0) {
        amrinfo->ulTotalTime = 0;
        amrinfo->usNotSupport = 1;
    }
    else if ((amrinfo->ulSampleRate != 8000) || (amrinfo->ulSampleRate != 16000)) {
        PRINTF("Unsupport sample rate = %d\r\n!", amrinfo->ulNewSampleRate);
        amrinfo->usNotSupport = 1;
    }

    m_WAVFileInfo = *amrinfo;
	#endif
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUI_GetPlayStatus
//==============================================================================
/** 
    @brief  Get Audio Play Status
    @param[out] *usStatus : status(stop,pause...)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUI_GetPlayStatus(MMP_USHORT *usStatus)
{
	MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_STATUS | PLAY_STATUS);
    *usStatus = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
	
	return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPD_AUDIO_StartAudioPlay
//==============================================================================
/** 
    @brief  Start Audio Play
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR	MMPD_AUI_StartAudioPlay(void)
{
    MMP_USHORT  status;

    MMPD_AUI_GetPlayStatus(&status);
    
    if (status == DECODE_OP_STOP) {
    
		MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
		MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    	MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_START);
    	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        return MMP_ERR_NONE;
    }
	return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//==============================================================================
//  Function    : MMPD_AUI_PauseAudioPlay
//==============================================================================
/** 
    @brief  Pauses Audio Play
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR	MMPD_AUI_PauseAudioPlay(void)
{
    MMP_USHORT  status;
    
    MMPD_AUI_GetPlayStatus(&status);
    
    if (status == DECODE_OP_START) {

		MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
		MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    	MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_PAUSE);
    	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;        
    }

	return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//==============================================================================
//  Function    : MMPD_AUI_ResumeAudioPlay
//==============================================================================
/** 
    @brief  Resume Audio Play
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR	MMPD_AUI_ResumeAudioPlay(void)
{
    MMP_USHORT  status;
    
    MMPD_AUI_GetPlayStatus(&status);
    
	if (status == DECODE_OP_PAUSE) {

		MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
		MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    	MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_RESUME);
    	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
	return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//==============================================================================
//  Function    : MMPD_AUI_StopAudioPlay
//==============================================================================
/** 
    @brief  Stop Audio Play
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR	MMPD_AUI_StopAudioPlay(void)
{
    MMP_USHORT  status;
    
    MMPD_AUI_GetPlayStatus(&status);
    
    if ((status == DECODE_OP_START) || (status == DECODE_OP_PAUSE)) {

		MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
		MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUI);
    	MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_STOP);
    	MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//==============================================================================
//  Function    : MMPD_AUI_CheckPlayEnd
//==============================================================================
/**
    @brief  Check and wait until the audio fifo end
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR	MMPD_AUI_CheckPlayEnd(void)
{
    MMP_USHORT  play_status;

    do {
        if (MMPD_AUI_GetPlayStatus(&play_status) != MMP_ERR_NONE) {
            return MMP_SYSTEM_ERR_CMDTIMEOUT;
        }    
	} while (play_status != DECODE_OP_STOP);

    return MMP_ERR_NONE;   
}

/// @}
/// @end_ait_only
