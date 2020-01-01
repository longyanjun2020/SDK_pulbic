//==============================================================================
//
//  File        : mmps_aui.c
//  Description : Audio UI Tone User Application Interface
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_aui.c
 *  @brief The Audio UI tone control functions for AUI player
 *  @author Penguin Torng
 *  @version 1.0
 */

#include "mmp_lib.h"
#include "mmps_aui.h"
#include "mmps_audio.h"
#include "mmpd_aui.h"
#include "mmph_hif.h"
#include "mmpd_system.h"
//#include "ait_utility.h" //recover later pohan chen 
/** @addtogroup MMPS_AUI
@{
*/

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
static MMPS_AUI_MEDIA_PATH m_auiMediaPath = MMPS_AUI_MEDIA_PATH_MAX;
//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
/// @ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUI_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Audio Mode Memory Allocation
    @param[in] ulMode : audio mode
    @param[in] usStartAddrMode : index for buffer start address, which depends on different codec implementation
    @return MMP_ERR_NONE
*/
static MMP_ERR MMPS_AUI_AllocateBuffer(MMP_ULONG ulMode)
{
    MMP_ULONG   buf_start, cur_buf, play_buf_size;

    MMPS_System_GetAudioFrameStart(1, &buf_start);
    RTNA_DBG_Str(3,"buf_start = 0x%X\r\n", buf_start);
    //RTNA_DBG_Str(0,"buf_start = 0x%X\r\n", buf_start);
    cur_buf = buf_start;
    switch(ulMode) {
    case MMPS_AUI_WAV_P_CARD_MODE:
        if (m_auiMediaPath != MMPS_AUI_MEDIA_PATH_MMP_MEM) {
            play_buf_size = MMPS_Audio_GetConfig()->AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUI_SetPlayBuf(cur_buf, play_buf_size);
        }

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUI_SetPlayFileNameBuf(cur_buf);
        break;
    case MMPS_AUI_MP3_P_CARD_MODE:
    case MMPS_AUI_AMR_P_CARD_MODE:
        if (m_auiMediaPath != MMPS_AUI_MEDIA_PATH_MMP_MEM) {
            play_buf_size = MMPS_Audio_GetConfig()->AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUI_SetPlayBuf(cur_buf, play_buf_size);
            play_buf_size = MMPS_Audio_GetConfig()->AudioMode[ulMode].ulParseBufSize;
            if (play_buf_size) {
                cur_buf -= play_buf_size;
                MMPD_AUI_SetParseBuf(cur_buf, play_buf_size);
            }
        }

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUI_PresetPlayFileNameBuf(cur_buf);
        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUI_SetParseFileNameBuf(cur_buf);
        break;
    }

    RTNA_DBG_Str(3, "Audio Alloc Buf Start:0x%X\r\n", buf_start);
    RTNA_DBG_Str(3, "Audio Alloc Buf End:0x%X\r\n", cur_buf);
    if (cur_buf > buf_start) {
        RTNA_DBG_Str(3, "Audio use 0x%X memory\r\n", (cur_buf - buf_start));
    }
    else {
        RTNA_DBG_Str(3, "Audio use 0x%X memory\r\n", (buf_start - cur_buf));
    }

    return MMP_ERR_NONE;
}
/// @end_ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUI_SetMediaPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set Media Path
    @param[in] mediapath : media path
        -   MMPS_AUI_MEDIA_PATH_CARD: file is located at card
        -   MMPS_AUI_MEDIA_PATH_MMP_MEM: file is located at MMP stacked memory
    @return MMP_ERR_NONE

    @pre Media path must be set before playback initialization.
    @pre Do @b NOT use for host parser or meta data parser, it will impact playback.
*/
MMP_ERR MMPS_AUI_SetMediaPath(MMPS_AUI_MEDIA_PATH mediapath)
{
    m_auiMediaPath = mediapath;
    return  MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPS_AUI_InitializeMP3Play
//==============================================================================
/**
    @brief  Initialize MP3 Play
    @param[in] *fileinfo : mp3 file name input parameter
    @param[out] *mp3info : mp3 file info

    @return MMP_ERR_NONE,MMP_AUDIO_ERR_UNSUPPORT_FORMAT
*/
MMP_ERR MMPS_AUI_InitializeMP3Play(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MP3_INFO *mp3info)
{
    MMP_ERR     status;
    MMPS_AUDIO_OUT_PATH audiooutpath;

    audiooutpath = MMPS_AUDIO_GetOutPath();
    MMPD_AUDIO_SetOutPath(audiooutpath);
    MMPD_AUI_SetParseFormat(MMP_AUDIO_MP3_PLAY);
    if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_CARD)
        MMPD_AUI_SetParsePath(MMPD_AUI_PLAY_FROM_CARD);
    else if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_MMP_MEM)
        MMPD_AUI_SetParsePath(MMPD_AUI_PLAY_FROM_MMP_MEM);
    else
        return MMP_AUDIO_ERR_INVALID_FLOW;

    MMPS_AUI_AllocateBuffer(MMPS_AUI_MP3_P_CARD_MODE); //NOTE: use CARD_MODE here even for streaming play
    if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_CARD) {
        status = MMPD_AUI_SetParseFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            printc(FG_RED("ERR:AUDIO_ERR_OPEN MP3 FILE_FAIL \r\n"));
            return status;
        }
    }
    else {
        MMPD_AUI_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        MMPD_AUI_SetParseBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
    }

    MMPD_AUI_GetMP3FileInfo((MMP_AUDIO_MP3_INFO *)mp3info);
    if (mp3info->usNotSupport) {
        printc(FG_RED("ERR:AUDIO_ERR NOT SUPPORT FORMAT \r\n"));
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    return MMP_ERR_NONE;
}
#if 0
//------------------------------------------------------------------------------
//  Function    : MMPS_AUI_StartMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Start MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUI_InitializeMP3Play was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.
*/
MMP_ERR MMPS_AUI_StartMP3Play(void)
{
    return MMPD_AUI_StartAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUI_PauseMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Pause MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUI_PauseMP3Play(void)
{
    MMP_ERR     status = MMP_ERR_NONE;
    MMP_USHORT  play_status;

    status = MMPD_AUI_PauseAudioPlay();
    if (status != MMP_ERR_NONE)
        return status;

    do {
        status = MMPD_AUI_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
        else if (play_status == DECODE_OP_STOP)
            return MMP_AUDIO_ERR_PARAMETER;
    } while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUI_ResumeMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Resume MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUI_ResumeMP3Play(void)
{
    return MMPD_AUI_ResumeAudioPlay();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUI_StopMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Stop MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUI_StopMP3Play(void)
{
    MMP_ERR status = MMP_ERR_NONE;

    status = MMPD_AUI_StopAudioPlay();
    if (status != MMP_ERR_NONE) {
        return status;
    }

    MMPD_AUI_CheckPlayEnd();

    return MMP_ERR_NONE;
}
#endif
//==============================================================================
//  Function    : MMPS_AUI_InitializeWAVPlay
//==============================================================================
/**
    @brief  Initialize WAV Play
            The function initialize the WAV Play. It will return the WAV media information,
            and prepare for WAV playback.
    @param[in] *fileinfo : input file parameters
    @param[out] *wavinfo : wav file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_AUDIO_ERR_UNSUPPORT_FORMAT, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: Audio output path has been set by @ref MMPS_AUDIO_SetMediaPath.
    @pre 2: DRM IV/Key/header offset settings have beed set for DRM file playback.
    @pre 3: @e bFileName and @e usFileNameLength in @e fileinfo must be set properly.
    @pre 4: For host file mode, @e ubBuf and @e ulBufSize must also be set properly.
            @e ulBufSize must be a multiple of 1024.

    @post 1: After initialized, playback can be supported or not will be reported by FW parser.
             For unsupport file located at host storage, file will be closed directly.
    @post 2: After initialized successfully, @ref MMPS_AUDIO_StopWAVPlay must be called to close
             file located at host storage, even @ref MMPS_AUDIO_StartWAVPlay was not called.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE   m_ubHostBuf[200*1024];
    AIT_WAV_Player_Init(MMP_BYTE *filename, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO         fileinfo;
        MMP_AUDIO_WAV_INFO          wavinfo;

        fileinfo.bFileName          = filename;
        fileinfo.usFileNameLength   = STRLEN(fileinfo.bFileName);
        if (!bCardMode) {
            //buffer for input audio data read from host storage
            fileinfo.ubBuf          = m_ubHostBuf;
            fileinfo.ulBufSize      = sizeof(m_ubHostBuf);
        }

        if (bCardMode) {
            MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH_CARD);
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PLAY);
        }
        else {
            MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE);
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PLAY);
        }

        if (drminfo == NULL) {
            //set DRM disabled
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PLAY);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PLAY);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PLAY);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PLAY);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PLAY);
        }
        MMPS_AUDIO_InitializeWAVPlay(&fileinfo, &wavinfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUI_InitializeWAVPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WAV_INFO *wavinfo)
{
    MMP_ERR     status;
    MMP_USHORT  playstatus;
    MMPS_AUDIO_OUT_PATH audiooutpath;
    
    MMPD_AUI_GetPlayStatus(&playstatus);
    if(playstatus != DECODE_OP_STOP) {
        return  MMP_AUDIO_ERR_FILE_IO_FAIL;
    }
    
    audiooutpath = MMPS_AUDIO_GetOutPath();
    MMPD_AUDIO_SetOutPath(audiooutpath);
    MMPD_AUI_SetPlayFormat(MMP_AUDIO_WAV_PLAY);
    if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_CARD)
        MMPD_AUI_SetPlayPath(MMPD_AUI_PLAY_FROM_CARD);
    else if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_MMP_MEM)
        MMPD_AUI_SetPlayPath(MMPD_AUI_PLAY_FROM_MMP_MEM);
    else
        return MMP_AUDIO_ERR_INVALID_FLOW;

    MMPS_AUI_AllocateBuffer(MMPS_AUI_WAV_P_CARD_MODE); //NOTE: use CARD_MODE here even for streaming play
    if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_CARD) {
        status = MMPD_AUI_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            return status;
        }
    }
    else {
        MMPD_AUI_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
    }

    MMPD_AUI_GetWAVFileInfo((MMP_AUDIO_WAV_INFO *)wavinfo);
    if (wavinfo->usNotSupport) {
        PRINTF("MMPS_AUDIO_InitializeWAVPlay: unsupport\r\n");
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    return MMP_ERR_NONE;
}
MMP_ERR MMPS_AUI_InitializeAMRPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AMR_INFO *amrinfo)
{
    MMP_ERR     status;
    MMP_USHORT  playstatus;
    MMPS_AUDIO_OUT_PATH audiooutpath;
    
    MMPD_AUI_GetPlayStatus(&playstatus);
    if(playstatus != DECODE_OP_STOP) {
        return  MMP_AUDIO_ERR_FILE_IO_FAIL;
    }
    
    audiooutpath = MMPS_AUDIO_GetOutPath();
    MMPD_AUDIO_SetOutPath(audiooutpath);
    MMPD_AUI_SetPlayFormat(MMP_AUDIO_AMR_PLAY);

    if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_CARD)
        MMPD_AUI_SetPlayPath(MMPD_AUI_PLAY_FROM_CARD);
    else if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_MMP_MEM)
        MMPD_AUI_SetPlayPath(MMPD_AUI_PLAY_FROM_MMP_MEM);
    else
        return MMP_AUDIO_ERR_INVALID_FLOW;

    MMPS_AUI_AllocateBuffer(MMPS_AUI_AMR_P_CARD_MODE); //NOTE: use CARD_MODE here even for streaming play
    if (m_auiMediaPath == MMPS_AUI_MEDIA_PATH_CARD) {
        status = MMPD_AUI_SetParseFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            UartSendTrace(FG_RED("ERR:AUDIO_ERR_OPEN MP3 FILE_FAIL \r\n"));
            return status;
        }
    }
    else {
        MMPD_AUI_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        MMPD_AUI_SetParseBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
    }

    #if 0
    MMPD_AUI_GetWAVFileInfo((MMP_AUDIO_AMR_INFO *)amrinfo);
    if (amrinfo->usNotSupport) {
        PRINTF("MMPS_AUDIO_InitializeWAVPlay: unsupport\r\n");
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    #endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUI_GetPlayStatus
//------------------------------------------------------------------------------
/**
    @brief  Get Play Status
    @param[out] *status : play status
        -   MMPS_AUDIO_PLAY_START
        -   MMPS_AUDIO_PLAY_PAUSE
        -   MMPS_AUDIO_PLAY_STOP
        -   MMPS_AUDIO_PLAY_INVALID
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state)
         before get current status, otherwise, unexpected values will be returned.
*/
MMP_ERR MMPS_AUI_GetPlayStatus(MMPS_AUDIO_PLAY_STATUS *status)
{
    MMP_ERR     mmpstatus;
    MMP_USHORT  play_status;

    mmpstatus = MMPD_AUI_GetPlayStatus(&play_status);
    *status = play_status;

    return mmpstatus;
}

#if 0
__FOR_AHC_2ND_PLAY_FUNC__(){}
#endif

MMP_ERR MMPS_AUI_InitializePlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_DECODE_FMT audFmt)
{
    MMP_ERR             status = MMP_ERR_NONE;
    MMP_AUDIO_MP3_INFO  mp3info;
    MMP_AUDIO_WAV_INFO  wavinfo;
    MMP_AUDIO_AMR_INFO  amrinfo;

    switch(audFmt)
    {
    case MMP_AUDIO_MP3_PLAY:
        status = MMPS_AUI_InitializeMP3Play(fileinfo, &mp3info);
        break;
    case MMP_AUDIO_WAV_PLAY:
        status = MMPS_AUI_InitializeWAVPlay(fileinfo, &wavinfo);
        break;
    case MMP_AUDIO_AMR_PLAY:
        status = MMPS_AUI_InitializeAMRPlay(fileinfo, &amrinfo);
        break;
    default:
        break;
    }
    return status;
}

MMP_ERR MMPS_AUI_StartPlay(void)
{
    return MMPD_AUI_StartAudioPlay();
}

MMP_ERR MMPS_AUI_StopPlay(void)
{
    MMP_ERR     status;
    MMP_USHORT  u16status;
    
    MMPD_AUI_GetPlayStatus(&u16status);
    if(u16status == DECODE_OP_STOP)
        return MMP_ERR_NONE;
    
    status = MMPD_AUI_StopAudioPlay();
    if (status != MMP_ERR_NONE) {
        return status;
    }

    MMPD_AUI_CheckPlayEnd();

    return MMP_ERR_NONE;
}

MMP_ERR MMPS_AUI_PausePlay(MMP_UBYTE *audFmt)
{
    MMP_ERR status;
    MMP_USHORT play_status;

    status = MMPD_AUI_PauseAudioPlay();
    if (status != MMP_ERR_NONE)
        return status;

    do {
        status = MMPD_AUI_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
        else if (play_status == DECODE_OP_STOP)
            return MMP_AUDIO_ERR_PARAMETER;
    } while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}

MMP_ERR MMPS_AUI_ResumePlay(void)
{
    return MMPD_AUI_ResumeAudioPlay();
}

MMP_AUDIO_DECODE_FMT MMPS_AUI_GetPlayFormat(char *audioFileExt)
{
    MMP_AUDIO_DECODE_FMT auiFmt = MMP_AUDIO_ERR_PLAY_FMT;

    if (audioFileExt == NULL) {
        UartSendTrace("audioFileExt null string \n");
        return auiFmt;
    }

    if (STRCMP(audioFileExt, "mp3") == 0) {
        auiFmt =MMP_AUDIO_MP3_PLAY;
    }
    else if (STRCMP(audioFileExt, "wav") == 0) {
        auiFmt =MMP_AUDIO_WAV_PLAY;
    }
    else if (STRCMP(audioFileExt, "amr") == 0) {
        auiFmt =MMP_AUDIO_AMR_PLAY;
    }
    return auiFmt;
}

/// @}
