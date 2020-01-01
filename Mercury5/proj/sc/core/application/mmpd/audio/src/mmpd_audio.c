/// @ait_only
//==============================================================================
//
//  File        : mmpd_audio.c
//  Description : Audio Control Driver Function
//  Author      : Hans Liu
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_lib.h"
//#include "ait_utility.h"
#include "os_wrap.h"
#if (OMA_DRM_EN == 1)
#include "mmpd_omadrm.h"
#endif
#include "mmpd_audio.h"
#include "mmpd_system.h"
#include "mmph_hif.h"
#include "mmpf_i2s_ctl.h"
#include "mmpf_audio_ctl.h"
#include "mmps_fs.h" //for MMPS_FS_SEEK_SET. Remove later...

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

/** @addtogroup MMPD_AUDIO
 *  @{
 */

static MMP_AUDIO_AACPLUS_INFO   m_AACPlusFileInfo;
static MMP_AUDIO_AAC_INFO       m_AACFileInfo;
static MMP_AUDIO_FLAC_INFO      m_FLACFileInfo;
static MMP_AUDIO_MIDI_INFO      m_MIDIFileInfo;
static MMP_AUDIO_MP3_INFO       m_MP3FileInfo;
static MMP_AUDIO_AMR_INFO       m_AMRFileInfo;
static MMP_AUDIO_WMA_INFO       m_WMAFileInfo;
static MMP_AUDIO_RA_INFO        m_RAFileInfo;
static MMP_AUDIO_OGG_INFO       m_OGGFileInfo;
static MMP_AUDIO_WAV_INFO       m_WAVFileInfo;

static MMP_AUDIO_ENCODE_FMT     m_AudioEncodeFormat;
static MMP_AUDIO_ENCODE_FMT     m_AudioLiveEncodeFormat;
static MMP_AUDIO_DECODE_FMT     m_AudioDecodeFormat;

static MMP_ULONG                m_ulAudioPlayFileSize;
static MMP_UBYTE                m_ubAudioPlayPath;
static MMP_ULONG                m_ulAudioPlayReadPtr;
static MMP_ULONG                m_ulAudioPlayWritePtr;
static MMP_ULONG                m_ulAudioPlayReadPtrHigh;
static MMP_ULONG                m_ulAudioPlayWritePtrHigh;  

static MMP_USHORT               m_usAudioRecReadPtr;
static MMP_USHORT               m_usAudioRecWritePtr;
static MMP_USHORT               m_usAudioRecReadPtrHigh;
static MMP_USHORT               m_usAudioRecWritePtrHigh; 

static MMP_ULONG                m_ulAudioPlayRemainFileSize;
static MMP_ULONG                m_ulAudioPlayBufStart, m_ulAudioPlayBufSize;     
static MMP_ULONG                m_ulAudioPlayHandshakeBufAddr; 
static MMP_ULONG                m_ulAudioRecHandshakeBufStart;
static MMP_ULONG                m_ulAudioRecBufStart, m_ulAudioRecBufSize;  
static MMP_ULONG                m_ulAudioPlaySpectrumBufStart;

static MMP_ULONG                m_ulAudioTagBuf;
static MMP_ULONG                m_ulAudioTagBufSize;
static MMP_ULONG                m_ulAudioPlayFileNameBufStart;
static MMP_ULONG                m_ulAudioEncodeFileNameBufStart; 
static MMP_ULONG                m_ulAudioParseFileNameBufStart;

/* AAC SampleRate, BitRate */
static MMP_ULONG    m_usAACRecSamplerate;
static MMP_ULONG    m_ulAACRecBitrate;
static MMP_ULONG    m_ulAACRecParameter[56][2] = 
{
    {16000, 16000}, {16000, 24000}, {16000, 32000}, {16000, 64000},
    {16000, 96000}, {16000, 128000}, {16000, 160000}, {16000, 192000},
    ///////////////////////////////////////////////////////////////////////
    {22050, 16000}, {22050, 24000}, {22050, 32000}, {22050, 64000},
    {22050, 96000}, {22050, 128000}, {22050, 160000}, {22050, 192000}, {22050, 256000},
    ///////////////////////////////////////////////////////////////////////
    {24000, 16000}, {24000, 24000}, {24000, 32000}, {24000, 64000},
    {24000, 96000}, {24000, 128000}, {24000, 160000}, {24000, 192000}, {24000, 256000},
    ///////////////////////////////////////////////////////////////////////
    {32000, 16000}, {32000, 24000}, {32000, 32000}, {32000, 64000},
    {32000, 96000}, {32000, 128000}, {32000, 160000}, {32000, 192000}, {32000, 256000}, {32000, 320000},
    ///////////////////////////////////////////////////////////////////////
    {44100, 16000}, {44100, 24000}, {44100, 32000}, {44100, 64000},
    {44100, 96000}, {44100, 128000}, {44100, 160000}, {44100, 192000}, {44100, 256000}, {44100, 320000},
    ///////////////////////////////////////////////////////////////////////
    {48000, 16000}, {48000, 24000}, {48000, 32000}, {48000, 64000},
    {48000, 96000}, {48000, 128000}, {48000, 160000}, {48000, 192000}, {48000, 256000}, {48000, 320000}
};

/* MP3 SampleRate, BitRate */ 
static MMP_ULONG    m_usMP3RecSamplerate;
static MMP_ULONG    m_ulMP3RecBitrate;
static MMP_ULONG    m_ulMP3RecParameter[8][2] = 
{ 
    {32000, 160000},
    {32000, 128000},
    {32000, 96000},
    {32000, 64000},
    {44100, 160000},
    {44100, 128000},
    {44100, 96000},
    {44100, 64000}
};

/* AMR BitRate */
static MMP_ULONG    m_ulAMRRecBitrate;
static MMP_ULONG    m_ulAMRRecParameter[8] = {5200, 5600, 6400, 7200, 8000, 8400, 10800, 12800};

/* WAV SampleRate */
static MMP_ULONG    m_usWAVRecSamplerate;
static MMP_ULONG    m_ulWAVRecParameter[8] = {8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000};

/* Memory mode buffer management */
static  MMP_UBYTE   *m_ubMemPtr;
static  MMP_ULONG   m_ulMemBufSize, m_ulBufThreshold;
static  MMP_ULONG   m_ulMemReadPtr, m_ulMemReadPtrHigh;
static  MMP_ULONG   m_ulMemWritePtr, m_ulMemWritePtrHigh;

static  MMP_USHORT  m_usAudioEncodeMode;
static  MMP_USHORT  m_usAudioLiveEncodeMode;

static  MMP_ULONG   m_ulSBCSampleRate, m_ulSBCFrameSize, m_ulSBCFrameCount,m_ulSBCSamplesPerFrame, m_ulSBCChannelNum;
static  MMP_BOOL    m_bSBCEnable;

static  MMP_ULONG   m_ulWAVCSamplePerFrame;

/* The audio function memory file mode ID */
static void         *m_AudioPlayFileHandle;

/* The WMA decoder version */
static  MMP_ULONG   m_ulWMADecoderVersion;

#if (GAPLESS_PLAY_EN == 1)
static  MMP_BOOL    m_bGaplessEnable = MMP_FALSE;
#endif

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_PreDACPowerOn
//------------------------------------------------------------------------------
/**
    @brief  power on DAC module early
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_PreDACPowerOn(MMP_ULONG ulSampleRate)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulSampleRate);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AUDIO_POWER_ON);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetDACPowerOnStatus
//------------------------------------------------------------------------------
MMP_BOOL MMPD_AUDIO_GetDACPowerOnStatus(void)
{   
    return MMPF_Audio_GetDACPowerOnStatus();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetADCPowerOnStatus
//------------------------------------------------------------------------------
MMP_BOOL MMPD_AUDIO_GetADCPowerOnStatus(void)
{   
    return MMPF_Audio_GetADCPowerOnStatus();
}

#if 0
void ____PlayBack_Operation_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StartAudioPlay
//------------------------------------------------------------------------------
/** 
    @brief  Start Audio Play
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPD_AUDIO_StartAudioPlay(void* callBackFunc, void* context)
{
    MMP_USHORT  status;
    MMP_ULONG   file_offset = 0, align_offset = 0, return_size = 0;
    MMP_USHORT  start_flag, finish_flag;
    #if (GAPLESS_PLAY_EN == 1)
    MMP_BOOL    bClkEn = MMP_TRUE;
    #endif
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   drmOffset;
    MMP_UBYTE   drmIV[16];

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPD_AUDIO_GetPlayStatus(&status);
    
    #if (GAPLESS_PLAY_EN == 1)
    if (m_bGaplessEnable && (status != DECODE_OP_STOP)) {
        status = DECODE_OP_STOP;
        bClkEn = MMP_FALSE;
    }
    else {
        bClkEn = MMP_TRUE;
    }
    #endif
    
    if (status == DECODE_OP_STOP) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, (MMP_ULONG)callBackFunc);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, (MMP_ULONG)context);        
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_SET_CALLBACK);

        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_START);

        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        if (m_AudioDecodeFormat == MMP_AUDIO_OGG_PLAY ||
            m_AudioDecodeFormat == MMP_AUDIO_WMA_PLAY ||
            m_AudioDecodeFormat == MMP_AUDIO_AAC_PLAY ||
            m_AudioDecodeFormat == MMP_AUDIO_MP3_PLAY 
            ) {
            if ((m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) ||
                (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MMP_MEM)) {
                // NOP
            }
            else if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MEM) {
            
                do {
                    MMPD_AUDIO_GetPlayStartSeekFlag(&start_flag);
                    
                    if (start_flag == 0x01) {
                    
                        MMPD_AUDIO_GetPlayFileSeekOffset(&file_offset);
                        align_offset = (file_offset >> 9) << 9;

                        if (m_AudioPlayFileHandle) { // Host file mode
                            #if (OMA_DRM_EN == 1)
                            if (drmEn) {
                                MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                                MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset + drmOffset - 16, MMPS_FS_SEEK_SET);
                                MMPC_FS_FileRead(m_AudioPlayFileHandle, drmIV, 16, &return_size);
                                MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
                            }
                            else {
                                MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                            }
                            #else
                            MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                            #endif
                            MMPC_FS_FileRead(m_AudioPlayFileHandle, m_ubMemPtr, m_ulMemBufSize, &return_size);
                        }
                        
                        MMPD_AUDIO_UpdatePlayFileRemainSize(m_ulAudioPlayFileSize - align_offset);
                        MMPD_AUDIO_InitPlayRWPtr();

                        if (m_AudioPlayFileHandle) {
                            MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, return_size, 1024);
                        }
                        else { // Memory mode
                            MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, m_ulAudioPlayFileSize, 0);
                            MMPD_AUDIO_SetMemModeReadPointer(align_offset, 0);
                        }
                        
                        MMPD_AUDIO_TransferDataHostToDev();
                        
                        if (m_AudioPlayFileHandle) {
                            MMPD_AUDIO_TransferDataCardToHost(m_AudioPlayFileHandle);
                        }
                        MMPD_AUDIO_SetPlayReadPtr(file_offset - align_offset, 0);

                        MMPD_AUDIO_SetPlayStartSeekFlag(0);
                    }
                    
                    MMPD_AUDIO_GetPlayFinishSeekFlag(&finish_flag);
                    
                } while(finish_flag != 0x01);
                
                MMPD_AUDIO_TransferDataHostToDev();

                MMPD_AUDIO_UpdatePlayStreamSize(m_ulAudioPlayFileSize - align_offset);
            }               
        }

        return MMP_ERR_NONE;
    }
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_PauseAudioPlay
//------------------------------------------------------------------------------
/** 
    @brief  Pauses Audio Play
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_PauseAudioPlay(void)
{
    MMP_USHORT status;
    
    MMPD_AUDIO_GetPlayStatus(&status);
    
    if (status == DECODE_OP_START) {
    
        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_PAUSE);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        
        return MMP_ERR_NONE;
    }

    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ResumeAudioPlay
//------------------------------------------------------------------------------
/** 
    @brief  Resume Audio Play
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_ResumeAudioPlay(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetPlayStatus(&status);
    
    if (status == DECODE_OP_PAUSE) {
    
        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_RESUME);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StopAudioPlay
//------------------------------------------------------------------------------
/** 
    @brief  Stop Audio Play
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_StopAudioPlay(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetPlayStatus(&status);
    
    if ((status == DECODE_OP_START) || (status == DECODE_OP_PAUSE)) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_STOP);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

#if 0
void ____Record_Operation_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StartAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Start Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_StartAudioRecord(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetRecordStatus(&status);

    if (status == ENCODE_OP_STOP) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENC_OP | ENCODE_OP_START);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_PauseAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Pause Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_PauseAudioRecord(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetRecordStatus(&status);
    
    if (status == ENCODE_OP_START) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENC_OP | ENCODE_OP_PAUSE);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ResumeAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Resume Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_ResumeAudioRecord(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetRecordStatus(&status);

    if (status == ENCODE_OP_PAUSE) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENC_OP | ENCODE_OP_RESUME);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StopAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Stop Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_StopAudioRecord(void)
{
    MMP_USHORT  record_status;
    
    MMPD_AUDIO_GetRecordStatus(&record_status);

    if ((record_status == ENCODE_OP_PAUSE) || (record_status == ENCODE_OP_START)) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENC_OP | ENCODE_OP_STOP);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

#if 0
void ____Live_Audio_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StartLiveAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Start Live Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_StartLiveAudioRecord(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetLiveRecordStatus(&status);

    if (status == ENCODE_OP_STOP) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_ENC_OP | ENCODE_OP_START);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_PauseLiveAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Pause Live Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_PauseLiveAudioRecord(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetLiveRecordStatus(&status);
    
    if (status == ENCODE_OP_START) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_ENC_OP | ENCODE_OP_PAUSE);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ResumeLiveAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Resume Live Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_ResumeLiveAudioRecord(void)
{
    MMP_USHORT  status;
    
    MMPD_AUDIO_GetLiveRecordStatus(&status);

    if (status == ENCODE_OP_PAUSE) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_ENC_OP | ENCODE_OP_RESUME);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StopLiveAudioRecord
//------------------------------------------------------------------------------
/** 
    @brief  Stop Live Audio Record
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_StopLiveAudioRecord(void)
{
    MMP_USHORT  record_status;
    
    MMPD_AUDIO_GetLiveRecordStatus(&record_status);

    if ((record_status == ENCODE_OP_PAUSE) || (record_status == ENCODE_OP_START)) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_ENC_OP | ENCODE_OP_STOP);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StartAudioRecordEx
//------------------------------------------------------------------------------
/** 
    @brief  Start Audio Record Preencode
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_StartAudioRecordEx(  MMP_BOOL                bPreEncode,
                                        MMP_AUDIO_ENCODE_FMT    encodeFmt,
                                        MMP_ULONG               samplerate)
{
    MMP_USHORT  status;

    MMPD_AUDIO_GetLiveRecordStatus(&status);

    if (status == ENCODE_OP_STOP) {
    
        MMPD_AUDIO_SetLiveEncodeFormat(encodeFmt, samplerate, samplerate, 2, 2);

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

        if (bPreEncode) {
            MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_ENC_OP | ENCODE_OP_PREENCODE);
            MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
            MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        }

        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_ENC_OP | ENCODE_OP_START);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_DoLiveEncodeOp
//------------------------------------------------------------------------------
/**
    @brief  Bypass most regular audio only logic and send the operation to MMPF directly

    This is mainly used for streaming case and pass the op to audio task
    @param[in] OP an HIF_CMD_AUDIO_ENC_OP parameter
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_COMMAND_INVALID
*/
MMP_ERR MMPD_AUDIO_DoLiveEncodeOp(MMP_USHORT op)
{
    MMP_USHORT  status;

    MMPD_AUDIO_GetLiveRecordStatus(&status);

    if (op < ENCODE_OP_START || op > ENCODE_OP_PREENCODE) {
        return MMP_AUDIO_ERR_PARAMETER;
    }

    // Always enable clock in order to send following GRP_IDX_AUD HIF command
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_ENC_OP | op);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

#if 0
void ____Get_Info_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetAACPlusFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get AACPLUS File Info
    @param[out] *aacplusinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetAACPlusFileInfo(MMP_AUDIO_AACPLUS_INFO *aacplusinfo)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);
    
    aacplusinfo->ulBitRate      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    aacplusinfo->usSampleRate   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
    aacplusinfo->usHeaderType   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
    aacplusinfo->usChans        = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8);
    aacplusinfo->usNotSupport   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 10);
    aacplusinfo->ulTotalTime    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if ((aacplusinfo->usHeaderType == 0) || (aacplusinfo->ulBitRate == 0)) {
        aacplusinfo->ulTotalTime = 0;
        aacplusinfo->usNotSupport = 1;
    }
    else if ((aacplusinfo->usSampleRate < 8000) || (aacplusinfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate = %d\r\n!", aacplusinfo->usSampleRate);
        aacplusinfo->usNotSupport = 1;
    }
    else if (aacplusinfo->usNotSupport == 0) {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }
    }

    m_AACPlusFileInfo = *aacplusinfo;
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetAACFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get AAC File Info
    @param[out] *aacinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetAACFileInfo(MMP_AUDIO_AAC_INFO *aacinfo)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);
    
    aacinfo->ulBitRate      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    aacinfo->usSampleRate   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
    aacinfo->usHeaderType   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
    aacinfo->usChans        = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8);
    aacinfo->ulTotalTime    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    aacinfo->usNotSupport   = 0;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if ((aacinfo->usHeaderType == 0) || (aacinfo->ulBitRate == 0)) {
        aacinfo->ulTotalTime = 0;
        aacinfo->usNotSupport = 1;
    }
    else if ((aacinfo->usSampleRate < 8000) || (aacinfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate = %d\r\n!", aacinfo->usSampleRate);
        aacinfo->usNotSupport = 1;
    }
    else if (aacinfo->usNotSupport == 0) {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }
    }
    
    m_AACFileInfo = *aacinfo;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadAACPlusFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read AACPLUS File Info
    @param[out] *aacplusinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadAACPlusFileInfo(MMP_AUDIO_AACPLUS_INFO *aacplusinfo)
{
    *aacplusinfo = m_AACPlusFileInfo;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetFLACFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get FLAC File Info
    @param[out] *flacinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetFLACFileInfo(MMP_AUDIO_FLAC_INFO *flacinfo)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

    flacinfo->usSampleRate      = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    flacinfo->usChans           = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 2);
    flacinfo->ulTotalSamples    = (MMP_ULONG64)MMPH_HIF_GetParameterL(GRP_IDX_AUD, 4) + ((MMP_ULONG64)MMPH_HIF_GetParameterL(GRP_IDX_AUD, 8) << 32);
    flacinfo->ulBitRate         = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    flacinfo->ulTotalTime       = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 16);
    flacinfo->usNotSupport      = 0;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if ((flacinfo->usSampleRate == 0) || (flacinfo->usChans == 0) ||
        (flacinfo->ulTotalSamples == 0) || (flacinfo->ulBitRate == 0)) {
        flacinfo->ulTotalTime = 0;
        flacinfo->usNotSupport = 1;
    }
    else if (flacinfo->usNotSupport == 0) {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }   
    }
    
    m_FLACFileInfo = *flacinfo;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadFLACFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read FLAC File Info
    @param[out] *flacinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadFLACFileInfo(MMP_AUDIO_FLAC_INFO *flacinfo)
{
    *flacinfo = m_FLACFileInfo;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetMIDIFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get MIDI File Info
    @param[out] *midiinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetMIDIFileInfo(MMP_AUDIO_MIDI_INFO *midiinfo)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

    midiinfo->usSampleRate  = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    midiinfo->ulTotalTime   = (MMP_ULONG)((MMP_ULONG)(MMPH_HIF_GetParameterW(GRP_IDX_AUD, 2)+1)*1000);
    midiinfo->usNotSupport  = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if (midiinfo->usNotSupport == 0) {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }
    }
    
    m_MIDIFileInfo = *midiinfo;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadMIDIFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read MIDI File Info
    @param[out] *midiinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadMIDIFileInfo(MMP_AUDIO_MIDI_INFO *midiinfo)
{
    *midiinfo = m_MIDIFileInfo;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetMP3FileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get MP3 File Info
    @param[out] *mp3info : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_MP3FILEINFO);

    mp3info->ulBitRate      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    mp3info->usSampleRate   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
    mp3info->usChans        = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
    mp3info->usLayer        = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8);
    mp3info->usVersion      = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 10);
    mp3info->usVbr          = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 12);
    mp3info->bIsMp3HdFile   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 14);
    mp3info->ulTotalTime    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 16);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    mp3info->usNotSupport = 0;

    if (mp3info->ulBitRate == 0) {
        mp3info->ulTotalTime = 0;
        mp3info->usNotSupport = 1;
    }
    else if ((mp3info->usSampleRate < 8000) || (mp3info->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate = %d!\r\n", mp3info->usSampleRate);
        mp3info->usNotSupport = 1;
    }

    m_MP3FileInfo = *mp3info;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadMP3FileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read MP3 File Info
    @param[out] *mp3info : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadMP3FileInfo(MMP_AUDIO_MP3_INFO *mp3info)
{
    *mp3info = m_MP3FileInfo;
    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetAMRFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get AMR File Info
    @param[out] *amrinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetAMRFileInfo(MMP_AUDIO_AMR_INFO *amrinfo)
{
    MMP_UBYTE frame_size[8] = {12, 13, 15, 17, 19, 20, 26, 31};     

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

    amrinfo->usMode         = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    amrinfo->ulTotalTime    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 4);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    amrinfo->usSampleSize   = frame_size[amrinfo->usMode] + 1;
    amrinfo->ulBitRate      = (frame_size[amrinfo->usMode] + 1) * 50 * 8;
    amrinfo->usSampleRate   = 8000;
    amrinfo->usNotSupport   = 0;
    
    if (amrinfo->usMode >= 8) { // Invalid mode
        amrinfo->ulTotalTime = 0;
        amrinfo->usNotSupport = 1;
    }
    else {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }
    }
    
    m_AMRFileInfo = *amrinfo;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadAMRFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read AMR File Info
    @param[out] *amrinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadAMRFileInfo(MMP_AUDIO_AMR_INFO *amrinfo)
{
    *amrinfo = m_AMRFileInfo;
    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWMAFileInfo
//------------------------------------------------------------------------------
/**
    @brief  Get WMA Pro File Info
    @param[out] *wmaproinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetWMAFileInfo(MMP_AUDIO_WMA_INFO *wmainfo)
{
    MMP_ULONG   file_offset, align_offset;
    MMP_USHORT  start_flag, finish_flag;
    MMP_ULONG   return_size;   
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   drmOffset;
    MMP_UBYTE   drmIV[16];
    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, m_ulAudioTagBuf);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);
    
    if ((m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) ||
        (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MMP_MEM)) {
        // NOP
    }
    else if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MEM) {

        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        do{
            MMPD_AUDIO_GetPlayStartSeekFlag(&start_flag);
            
            if (start_flag == 0x01) {
            
                MMPD_AUDIO_GetPlayFileSeekOffset(&file_offset);
            
                align_offset = (file_offset >> 9) << 9;

                if (m_AudioPlayFileHandle) { // Host file mode
                    #if (OMA_DRM_EN == 1)
                    if (drmEn) {
                        MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)(align_offset + drmOffset - 16), MMPS_FS_SEEK_SET);
                        MMPC_FS_FileRead(m_AudioPlayFileHandle, drmIV, 16, &return_size);
                        MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
                    }
                    else {
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    }
                    #else
                    MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    #endif
                    MMPC_FS_FileRead(m_AudioPlayFileHandle, m_ubMemPtr, m_ulMemBufSize, &return_size);
                }

                MMPD_AUDIO_UpdatePlayFileRemainSize(m_ulAudioPlayFileSize - align_offset);
                MMPD_AUDIO_InitPlayRWPtr();

                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, return_size, 1024);
                }
                else {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, m_ulAudioPlayFileSize, 0);
                    MMPD_AUDIO_SetMemModeReadPointer(align_offset, 0);
                }

                MMPD_AUDIO_TransferDataHostToDev();
                
                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_TransferDataCardToHost(m_AudioPlayFileHandle);
                }    
                MMPD_AUDIO_SetPlayReadPtr(file_offset - align_offset, 0);

                MMPD_AUDIO_SetPlayStartSeekFlag(0);
            }
            
            MMPD_AUDIO_GetPlayFinishSeekFlag(&finish_flag);
        
        } while(finish_flag != 0x01);

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    }

    wmainfo->ulBitRate          = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    wmainfo->usBitsPerSample    = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
    wmainfo->usChans            = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
    wmainfo->usTagInfo          = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8);
    wmainfo->usVbrInfo          = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 10);
    wmainfo->ulTotalTime        = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    wmainfo->usNotSupport       = 0;
    wmainfo->ulSampleRate       = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 16);
    wmainfo->usVersion          = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 20); // > 2 => wma pro

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if (wmainfo->usVersion > 2 && m_ulWMADecoderVersion == 9) {
        PRINTF("WMA decoder with WMAPRO bitstream\r\n");
        wmainfo->usNotSupport = 1;
    }

    if (wmainfo->ulBitRate == 0) {
        wmainfo->ulTotalTime = 0;
        wmainfo->usNotSupport = 1;
    }
    else if ((wmainfo->ulSampleRate < 8000) || (wmainfo->ulSampleRate > 48000)) {
        PRINTF("Unsupport sample rate = %d!\r\n", wmainfo->ulSampleRate);
        wmainfo->usNotSupport = 1;
    }
    else if (wmainfo->usBitsPerSample > 16) {
        PRINTF("Unsupport bit per sample = %d!\r\n", wmainfo->usBitsPerSample);
        wmainfo->usNotSupport = 1;
    }
    else {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }   
    }

    m_WMAFileInfo = *wmainfo;
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadWMAFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get WMA File Info
    @param[out] *wmainfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadWMAFileInfo(MMP_AUDIO_WMA_INFO *wmainfo)
{
    *wmainfo = m_WMAFileInfo;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWMATagLen
//------------------------------------------------------------------------------
/**
    @brief  Get WMA Tag Length
    @param[out] ulLen : Length of WMA tag information
    @param[in] wmainfo: file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetWMATagLen(MMP_ULONG *ulLen, MMP_AUDIO_WMA_INFO *wmainfo)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    
    if (wmainfo->usTagInfo != 0) {
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_WMA_DEC_OP | DECODE_OP_EXTRACT_TAG);

        ulLen[0] = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0); // wmapro_tag_length.title_len
        ulLen[1] = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 2); // wmapro_tag_length.author_len
        ulLen[2] = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4); // wmapro_tag_length.copyright_len
        ulLen[3] = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6); // wmapro_tag_length.description_len
        ulLen[4] = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8); // wmapro_tag_length.rating_len
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetRAFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get realaudio File Info
    @param[out] *rainfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetRAFileInfo(MMP_AUDIO_RA_INFO *rainfo)
{
    MMP_ULONG   file_offset, align_offset;
    MMP_USHORT  start_flag, finish_flag;
    MMP_ULONG   return_size;    
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   drmOffset;
    MMP_UBYTE   drmIV[16];
    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

    if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
        // NOP
    }
    else if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MEM) {

        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        do {
            MMPD_AUDIO_GetPlayStartSeekFlag(&start_flag);
            
            if (start_flag == 0x01) {
            
                MMPD_AUDIO_GetPlayFileSeekOffset(&file_offset);
            
                align_offset = (file_offset >> 9) << 9;

                if (m_AudioPlayFileHandle) {
                    #if (OMA_DRM_EN == 1)
                    if (drmEn) {
                        MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)(align_offset + drmOffset - 16), MMPS_FS_SEEK_SET);
                        MMPC_FS_FileRead(m_AudioPlayFileHandle, drmIV, 16, &return_size);
                        MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
                    }
                    else {
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    }
                    #else
                    MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    #endif
                    MMPC_FS_FileRead(m_AudioPlayFileHandle, m_ubMemPtr, m_ulMemBufSize, &return_size);
                }

                MMPD_AUDIO_UpdatePlayFileRemainSize(m_ulAudioPlayFileSize - align_offset);
                MMPD_AUDIO_InitPlayRWPtr();

                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, return_size, 1024);
                }
                else {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, m_ulAudioPlayFileSize, 0);
                    MMPD_AUDIO_SetMemModeReadPointer(align_offset, 0);
                }
                MMPD_AUDIO_TransferDataHostToDev();

                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_TransferDataCardToHost(m_AudioPlayFileHandle);
                }

                MMPD_AUDIO_SetPlayReadPtr(file_offset - align_offset, 0);

                MMPD_AUDIO_SetPlayStartSeekFlag(0);
            }
            
            MMPD_AUDIO_GetPlayFinishSeekFlag(&finish_flag);
        
        } while(finish_flag != 0x01);

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    }

    rainfo->ulBitRate       = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    rainfo->usSampleRate    = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
    rainfo->usChans         = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
    rainfo->ulTotalTime     = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 8);
    rainfo->usVbrInfo       = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 12);
    rainfo->bSeekable       = MMPH_HIF_GetParameterB(GRP_IDX_AUD, 14);
    rainfo->usNotSupport    = 0;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if (rainfo->ulBitRate == 0) {
        rainfo->ulTotalTime = 0;
        rainfo->usNotSupport = 1;
    }
    else if ((rainfo->usSampleRate < 8000) || (rainfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate = %d\r\n!", rainfo->usSampleRate);
        rainfo->usNotSupport = 1;
    }
    else {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }   
    }
    
    m_RAFileInfo = *rainfo;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadRAFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read RA File Info
    @param[out] *rainfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadRAFileInfo(MMP_AUDIO_RA_INFO *rainfo)
{
    *rainfo = m_RAFileInfo;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetOGGFileInfo
//------------------------------------------------------------------------------
/**
    @brief  Get OGG File Info
    @param[out] *ogginfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetOGGFileInfo(MMP_AUDIO_OGG_INFO *ogginfo)
{
    MMP_ULONG   file_offset, align_offset;
    MMP_USHORT  start_flag, finish_flag;
    MMP_ULONG   return_size;   
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   drmOffset;
    MMP_UBYTE   drmIV[16];
    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, m_ulAudioTagBuf);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

    if ((m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) ||
        (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MMP_MEM)) {
        // NOP
    }
    else if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MEM) {

        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        do {
            MMPD_AUDIO_GetPlayStartSeekFlag(&start_flag);
            
            if (start_flag == 0x01) {
            
                MMPD_AUDIO_GetPlayFileSeekOffset(&file_offset);
            
                align_offset = (file_offset >> 9) << 9;
            
                if (m_AudioPlayFileHandle) { // Host file mode
                    #if (OMA_DRM_EN == 1)
                    if (drmEn) {
                        MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)(align_offset + drmOffset - 16), MMPS_FS_SEEK_SET);
                        MMPC_FS_FileRead(m_AudioPlayFileHandle, drmIV, 16, &return_size);
                        MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
                    }
                    else {
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    }
                    #else
                    MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    #endif
                    MMPC_FS_FileRead(m_AudioPlayFileHandle, m_ubMemPtr, m_ulMemBufSize, &return_size);
                }

                MMPD_AUDIO_UpdatePlayFileRemainSize(m_ulAudioPlayFileSize - align_offset);
                MMPD_AUDIO_InitPlayRWPtr();

                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, return_size, 1024);
                }
                else {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, m_ulAudioPlayFileSize, 0);
                    MMPD_AUDIO_SetMemModeReadPointer(align_offset, 0);
                }
                MMPD_AUDIO_TransferDataHostToDev();

                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_TransferDataCardToHost(m_AudioPlayFileHandle);
                }
                MMPD_AUDIO_SetPlayReadPtr(file_offset - align_offset, 0);

                MMPD_AUDIO_SetPlayStartSeekFlag(0);
            }
            
            MMPD_AUDIO_GetPlayFinishSeekFlag(&finish_flag);
        
        } while(finish_flag != 0x01);

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    }

    ogginfo->ulBitRate      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    ogginfo->usSampleRate   = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
    ogginfo->usChans        = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
    ogginfo->usTagInfo      = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8);
    ogginfo->usVbrInfo      = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 10);
    ogginfo->ulTotalTime    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    ogginfo->usNotSupport   = 0;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if (ogginfo->ulBitRate == 0) {
        ogginfo->ulTotalTime = 0;
        ogginfo->usNotSupport = 1;
    }
    else if ((ogginfo->usSampleRate < 8000) || (ogginfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate = %d\r\n!", ogginfo->usSampleRate);
        ogginfo->usNotSupport = 1;
    }
    else {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }
    }
    
    m_OGGFileInfo = *ogginfo;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadOGGFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read OGG File Info
    @param[out] *ogginfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadOGGFileInfo(MMP_AUDIO_OGG_INFO *ogginfo)
{
    *ogginfo = m_OGGFileInfo;
    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetOGGTagInfo
//------------------------------------------------------------------------------
/**
    @brief  Get OGG Tag Info
    @param[out] *TagInfo : comment info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetOGGTagInfo(MMP_AUDIO_OGG_TAG_INFO *TagInfo)
{
    const char  *ptrTag;
    MMP_ULONG   total_length=0;
    MMP_UBYTE   OggTagbuffer[OGG_TAG_BUF_SIZE];   

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_EXTRACT_TAG);

    TagInfo->title_len = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    total_length += TagInfo->title_len;
    TagInfo->version_len = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 4);
    total_length += TagInfo->version_len;
    TagInfo->album_len = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 6);
    total_length += TagInfo->album_len;
    TagInfo->artist_len = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 8);
    total_length += TagInfo->artist_len;
    TagInfo->description_len = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 10);
    total_length += TagInfo->description_len;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if (total_length > OGG_TAG_BUF_SIZE) {
        total_length = OGG_TAG_BUF_SIZE;
    }
    
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&OggTagbuffer[0], m_ulAudioTagBuf, total_length);
    
    ptrTag = (const char *)&OggTagbuffer[0];
    
    if (TagInfo->title_len) {
        ptrTag += TagInfo->title_len;
    }
    if (TagInfo->version_len) {
        ptrTag += TagInfo->version_len;
    }
    if (TagInfo->album_len) {
        ptrTag += TagInfo->album_len;
    }
    if (TagInfo->artist_len) {
        ptrTag += TagInfo->artist_len;
    }
    if (TagInfo->description_len) {
        ptrTag += TagInfo->description_len;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWAVFileInfo
//------------------------------------------------------------------------------
/**
    @brief  Get WAV File Info
    @param[out] *wavinfo : file info
    @return MMP_ERR_NONE
*/

MMP_ERR MMPD_AUDIO_GetWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_GET_FILEINFO);

    wavinfo->ulBitRate          = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    wavinfo->ulSampleRate       = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 4);
    wavinfo->ulNewSampleRate    = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 8);
    wavinfo->ulTotalTime        = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
    wavinfo->usChans            = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 16);
    wavinfo->usNotSupport       = 0;

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if (wavinfo->ulBitRate == 0) {
        wavinfo->ulTotalTime = 0;
        wavinfo->usNotSupport = 1;
    }
    else if ((wavinfo->ulSampleRate < 8000) || (wavinfo->ulSampleRate > 192000)) {
        PRINTF("Unsupport sample rate = %d\r\n!", wavinfo->ulSampleRate);
        wavinfo->usNotSupport = 1;
    }
    else {
        if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) {
            MMPD_AUDIO_GetPlayFileSize(&m_ulAudioPlayFileSize);
        }
    }
    
    m_WAVFileInfo = *wavinfo;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadWAVFileInfo
//------------------------------------------------------------------------------
/** 
    @brief  Read WAV File Info
    @param[out] *wavinfo : file info
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadWAVFileInfo(MMP_AUDIO_WAV_INFO *wavinfo)
{
    *wavinfo = m_WAVFileInfo;
    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWAVInfo
//------------------------------------------------------------------------------
/** 
    @brief  Get WAV info
    @param[out] ulOutSampleCount
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetWAVInfo(MMP_ULONG *ulOutSampleCount)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_WAV_ENCODE | GET_WAV_INFO);
    
    *ulOutSampleCount = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    m_ulWAVCSamplePerFrame = *ulOutSampleCount;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SaveAACRecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Save AAC Record Parameter
    @param[in]   ulMode: mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SaveAACRecParameter(MMP_ULONG ulMode)
{
    m_usAACRecSamplerate = m_ulAACRecParameter[ulMode][0];
    m_ulAACRecBitrate    = m_ulAACRecParameter[ulMode][1];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadAACRecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Read AAC Record Parameter
    @param[out]   *ulBitRate: mode
    @param[out]   *usSampleRate: sample rate
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadAACRecParameter(MMP_ULONG *ulBitRate, MMP_USHORT *usSampleRate)
{
     *ulBitRate     = m_ulAACRecBitrate;
     *usSampleRate  = m_usAACRecSamplerate;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SaveMP3RecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Save MP3 Record Parameter
    @param[in]   ulMode: mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SaveMP3RecParameter(MMP_ULONG ulMode)
{
    m_usMP3RecSamplerate    = m_ulMP3RecParameter[ulMode][0];
    m_ulMP3RecBitrate       = m_ulMP3RecParameter[ulMode][1];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadMP3RecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Read MP3 Record Parameter
    @param[out]   *ulBitRate: mode
    @param[out]   *usSampleRate: sample rate
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadMP3RecParameter(MMP_ULONG *ulBitRate, MMP_USHORT *usSampleRate)
{
    *ulBitRate      = m_ulMP3RecBitrate;
    *usSampleRate   = m_usMP3RecSamplerate;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SaveAMRRecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Save AMR Record Parameter
    @param[in]   ulMode: mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SaveAMRRecParameter(MMP_ULONG ulMode)
{
    m_ulAMRRecBitrate = m_ulAMRRecParameter[ulMode];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadAMRRecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Read AMR Record Parameter
    @param[out]   *ulBitRate: mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadAMRRecParameter(MMP_ULONG *ulBitRate)
{
    *ulBitRate = m_ulAMRRecBitrate;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SaveWAVRecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Save WAV Record Parameter
    @param[in]   ulMode: mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SaveWAVRecParameter(MMP_ULONG ulMode)
{
    m_usWAVRecSamplerate = m_ulWAVRecParameter[ulMode];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ReadWAVRecParameter
//------------------------------------------------------------------------------
/** 
    @brief  Read WAV Record Parameter
    @param[out]   *usSampleRate: sample rate
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_ReadWAVRecParameter(MMP_USHORT *usSampleRate)
{
    *usSampleRate = m_usWAVRecSamplerate;

    return MMP_ERR_NONE;
}

#if 0
void ____Volume_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_PlayFadeOutEn
//------------------------------------------------------------------------------
/** 
    @brief  Enable/Disable AUI or NON_AUI player's audio fade out effect  
    @param[in]  channelID type MMP_UBYTE
                -    0:MMPF_NON_AUI_PLAYER
                -    1:MMPF_AUI_PLAYER
                bAFadeOutEn.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_PlayFadeOutEn(MMP_UBYTE channelID, MMP_BOOL bAFadeOutEn)
{ 
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, channelID);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 1, bAFadeOutEn);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_PLAY_FADE_OUT_CTL);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayAnalogGain
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Analog Gain
    @param[in] ubAGain  : Audio ANALOG GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayAnalogGain(MMP_UBYTE ubAGain)
{ 
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ubAGain);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_PLAY_ANALOG_GAIN);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayDigitalGain
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Digital Gain
    @param[in] ubDGain  : Audio DIGITAL GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayDigitalGain(MMP_UBYTE ubDGain)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ubDGain);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_PLAY_DIGITAL_GAIN);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayVolume
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play Volume
    @param[in] ubSWGain : Audio SW GAIN.
    @param[in] ubDGain  : Audio DIGITAL GAIN.
    @param[in] ubAGain  : Audio ANALOG GAIN.
    @param[in] bSWGainOnly : Set SW GAIN only. DIGITAL GAIN and ANALOG GAIN use default value.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayVolume(MMP_UBYTE ubSWGain, MMP_UBYTE ubDGain, MMP_UBYTE ubAGain, MMP_BOOL bSWGainOnly)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0,  ubSWGain);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4,  ubDGain);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8,  ubAGain);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 12, bSWGainOnly);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_PLAY_VOLUME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecordAnalogGain
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record Volume
    @param[in] ubAGain  : Audio ANALOG GAIN.
    @param[in] bboostup : Audio ANALOG GAIN boost up.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecordAnalogGain(MMP_UBYTE ubAGain)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ubAGain);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_RECORD_ANALOG_GAIN);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecordDigitalGain
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record Volume
    @param[in] ubDGain  : Audio DIGITAL GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecordDigitalGain(MMP_UBYTE ubDGain)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ubDGain);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_RECORD_DIGITAL_GAIN);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecordVolume
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record Volume
    @param[in] ubDGain  : Audio DIGITAL GAIN.
    @param[in] ubAGain  : Audio ANALOG GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecordVolume(MMP_UBYTE ubDGain, MMP_UBYTE ubAGain)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ubDGain);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ubAGain);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_RECORD_VOLUME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecordHeadMuteTime
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Head Mute Time
    @param[in] ulMilliSec  : Time to mute in record head.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecordHeadMuteTime(MMP_ULONG ulMilliSec)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulMilliSec);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_RECORD_HEAD_MUTE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecordTailCutTime
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Tail Cut Time
    @param[in] ulMilliSec  : Time to cut in record tail.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecordTailCutTime(MMP_ULONG ulMilliSec)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulMilliSec);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_RECORD_TAIL_CUT);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnableDummyRecord
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Volume
    @param[in] bEnable  : To enable or disable audio dummy record function.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_EnableDummyRecord(MMP_BOOL bEnable)
{   
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, bEnable);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_RECORD_ENABLE_DUMMY);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRecordSilence
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record data to silence
    @param[in] bEnable  : To enable or disable audio recorded as silence.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecordSilence(MMP_BOOL bEnable)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, bEnable);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SET_VOLUME | AUDIO_RECORD_SILENCE);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

#if 0
void ____Time_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetMIDIPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set MIDI Start Play Time
    @param[in] ulTime : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetMIDIPlayTime(MMP_ULONG ulTime)
{
    if (ulTime > m_MIDIFileInfo.ulTotalTime) {
        ulTime = m_MIDIFileInfo.ulTotalTime;
    }

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulTime);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_MIDI_DEC_OP | DECODE_OP_SET_PLAYTIME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetWMAPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set WMA Start Play Time
    @param[in]  ulTime : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetWMAPlayTime(MMP_ULONG ulTime)
{
    if (ulTime > m_WMAFileInfo.ulTotalTime) {
        ulTime = m_WMAFileInfo.ulTotalTime;
    }
    
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulTime);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_WMA_DEC_OP | DECODE_OP_SET_STARTTIME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRAPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set RealAudio Start Play Time
    @param[in]  ulTime : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRAPlayTime(MMP_ULONG ulTime)
{
    MMP_ULONG   file_offset, align_offset;
    MMP_USHORT  start_flag, finish_flag;
    MMP_ULONG   return_size;    
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   drmOffset;
    MMP_UBYTE   drmIV[16];
    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    #endif

    if (ulTime > m_RAFileInfo.ulTotalTime) {
        ulTime = m_RAFileInfo.ulTotalTime;
    }
    
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulTime);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_RA_DEC_OP | DECODE_OP_RA_SET_STARTTIME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    if ((m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_CARD) ||
        (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MMP_MEM)) {
        // NOP
    }
    else if (m_ubAudioPlayPath == MMPD_AUDIO_PLAY_FROM_MEM) {
        do{
            MMPD_AUDIO_GetPlayStartSeekFlag(&start_flag);
            
            if (start_flag == 0x01) {
            
                MMPD_AUDIO_GetPlayFileSeekOffset(&file_offset);
            
                align_offset = (file_offset >> 9) << 9;

                if (m_AudioPlayFileHandle) {
                    #if (OMA_DRM_EN == 1)
                    if (drmEn) {
                        MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)(align_offset + drmOffset - 16), MMPS_FS_SEEK_SET);
                        MMPC_FS_FileRead(m_AudioPlayFileHandle, drmIV, 16, &return_size);
                        MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
                    }
                    else {
                        MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    }
                    #else
                    MMPC_FS_FileSeek(m_AudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
                    #endif
                    MMPC_FS_FileRead(m_AudioPlayFileHandle, m_ubMemPtr, m_ulMemBufSize, &return_size);
                }
                
                MMPD_AUDIO_UpdatePlayFileRemainSize(m_ulAudioPlayFileSize - align_offset);
                MMPD_AUDIO_InitPlayRWPtr();

                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, return_size, 1024);
                }
                else {
                    MMPD_AUDIO_InitialMemModePointer(m_ubMemPtr, m_ulMemBufSize, m_ulAudioPlayFileSize, 0);
                    MMPD_AUDIO_SetMemModeReadPointer(align_offset, 0);
                }
                
                MMPD_AUDIO_TransferDataHostToDev();
                
                if (m_AudioPlayFileHandle) {
                    MMPD_AUDIO_TransferDataCardToHost(m_AudioPlayFileHandle);
                }
                MMPD_AUDIO_SetPlayReadPtr(file_offset - align_offset, 0);

                MMPD_AUDIO_SetPlayStartSeekFlag(0);
            }
            
            MMPD_AUDIO_GetPlayFinishSeekFlag(&finish_flag);
        
        } while(finish_flag != 0x01);

        if (m_ubMemPtr)
            MMPD_AUDIO_UpdatePlayStreamSize(m_ulAudioPlayFileSize - align_offset);
        else
            MMPD_AUDIO_UpdatePlayStreamSize(m_ulAudioPlayFileSize - file_offset);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetOGGPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set OGG Start Play Time
    @param[in]  ulTime : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetOGGPlayTime(MMP_ULONG ulTime)
{
    if (ulTime > m_OGGFileInfo.ulTotalTime) {
        ulTime = m_OGGFileInfo.ulTotalTime;
    }
    
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulTime);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_PLAY_POS | SET_PLAY_TIME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetAACPlusPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set AACPLUS Start Play Time
    @param[in]  ulMilliSec : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetAACPlusPlayTime(MMP_ULONG ulMilliSec)
{
    MMP_ULONG pos;

    if (ulMilliSec < m_AACPlusFileInfo.ulTotalTime) {
        pos = (MMP_ULONG)(((MMP_ULONG64)ulMilliSec * m_AACPlusFileInfo.ulBitRate) / 8000);
        pos = (pos >> 9) << 9;
    }
    else {
        pos = m_ulAudioPlayFileSize;
    }
    
    MMPD_AUDIO_SetPlayPosition(pos);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetWAVPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set WAV Start Play Time
    @param[in]  ulMilliSec : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetWAVPlayTime(MMP_ULONG ulMilliSec)
{
    MMP_ULONG pos;

    if (ulMilliSec < m_WAVFileInfo.ulTotalTime) {
        pos = (MMP_ULONG)(((MMP_ULONG64)ulMilliSec * m_WAVFileInfo.ulBitRate) / 8000);
        pos = (pos >> 9) << 9;
    }
    else {
        pos = m_ulAudioPlayFileSize;
    }
    
    MMPD_AUDIO_SetPlayPosition(pos);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetAACPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set AAC Start Play Time
    @param[in]  ulMilliSec : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetAACPlayTime(MMP_ULONG ulMilliSec)
{
    MMP_ULONG pos;

    if (ulMilliSec < m_AACFileInfo.ulTotalTime) {
        pos = (MMP_ULONG)(((MMP_ULONG64)ulMilliSec * m_AACFileInfo.ulBitRate) / 8000);
        pos = (pos >> 9) << 9;
    }
    else {
        pos = m_ulAudioPlayFileSize;
    }
    
    MMPD_AUDIO_SetPlayPosition(pos);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetAMRPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set AMR Start Play Time
    @param[in]  ulMilliSec : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetAMRPlayTime(MMP_ULONG ulMilliSec)
{
    MMP_ULONG pos;

    if (ulMilliSec < m_AMRFileInfo.ulTotalTime) {
        pos = (MMP_ULONG)(((MMP_ULONG64)ulMilliSec * m_AMRFileInfo.ulBitRate) / 8000);
        pos = (pos >> 9) << 9;
    }
    else {
        pos = m_ulAudioPlayFileSize;
    }
    
    MMPD_AUDIO_SetPlayPosition(pos);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetMP3PlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set MP3 Start Play Time
    @param[in]  ulMilliSec : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetMP3PlayTime(MMP_ULONG ulMilliSec)
{
    MMP_ULONG pos;

    if (!m_MP3FileInfo.bIsMp3HdFile) {
        if (ulMilliSec < m_MP3FileInfo.ulTotalTime) {
            pos = (MMP_ULONG)(((MMP_ULONG64)ulMilliSec * m_MP3FileInfo.ulBitRate) / 8000);
            pos = (pos >> 9) << 9;
        }
        else {
            MMPD_AUDIO_GetPlayFileSize(&pos);
        }
        MMPD_AUDIO_SetPlayPosition(pos);
    }
    else {
        if (ulMilliSec > m_MP3FileInfo.ulTotalTime) {
            ulMilliSec = m_MP3FileInfo.ulTotalTime;
        }    
        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulMilliSec);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_PLAY_POS | SET_PLAY_TIME);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
        return MMP_ERR_NONE;
    }
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetFLACPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Set FLAC Start Play Time
    @param[in]  ulMilliSec : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetFLACPlayTime(MMP_ULONG ulMilliSec)
{
    if (ulMilliSec > m_FLACFileInfo.ulTotalTime) {
        ulMilliSec = m_FLACFileInfo.ulTotalTime;
    }
    
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulMilliSec);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_PLAY_POS | SET_PLAY_TIME);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetMIDIPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get MIDI Play Current Time
    @param[out] *usTimeRatio : (current time)/(total time)
    @param[out] *ulMilliSecond : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetMIDIPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulMilliSecond)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_MIDI_DEC_OP | DECODE_OP_GET_PLAYTIME);
    
    *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    
    if (m_MIDIFileInfo.ulTotalTime) {
        *usTimeRatio = (MMP_USHORT)(((MMP_ULONG64) * ulMilliSecond * 1000) / (m_MIDIFileInfo.ulTotalTime));;
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWAVPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get WAV Current Play Time & Ratio
    @param[out] ulMilliSecond: Current play time in ms.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetWAVPlayTime(MMP_ULONG *ulMilliSecond)
{
    *ulMilliSecond = 0;

    if (m_WAVFileInfo.ulTotalTime != 0) {
    
        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_PLAY_POS | GET_PLAY_TIME);
        *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetMP3PlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get MP3 Current Play Time
    @param[out]  *usPosRatio : (current play position) / (total file size)
    @param[out]  *ulMilliSecond : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetMP3PlayTime(MMP_USHORT *usPosRatio, MMP_ULONG *ulMilliSecond)
{
    *ulMilliSecond  = 0;
    *usPosRatio     = 0;

    if (m_MP3FileInfo.ulTotalTime != 0) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, GET_PLAY_TIME|HIF_AUD_CMD_PLAY_POS);
        *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        *usPosRatio = (MMP_USHORT)(((MMP_ULONG64) * ulMilliSecond * 100) / m_MP3FileInfo.ulTotalTime);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetAACPlusPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get AACPLUS Current Play Time
    @param[out]  *usPosRatio : (current play position) / (total file size)
    @param[out]  *ulMilliSecond : milli second
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/ 
MMP_ERR MMPD_AUDIO_GetAACPlusPlayTime(MMP_USHORT *usPosRatio, MMP_ULONG *ulMilliSecond)
{
    *usPosRatio     = 0;
    *ulMilliSecond  = 0;

    if (m_AACPlusFileInfo.ulTotalTime != 0) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, GET_PLAY_TIME|HIF_AUD_CMD_PLAY_POS);
        *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        *usPosRatio = (MMP_USHORT)(((MMP_ULONG64)*ulMilliSecond * 100) / m_AACPlusFileInfo.ulTotalTime);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetFLACPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get FLAC Current Play Time
    @param[out]  *usPosRatio : (current play position) / (total file size)
    @param[out]  *ulMilliSecond : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetFLACPlayTime(MMP_USHORT *usPosRatio, MMP_ULONG *ulMilliSecond)
{
    *ulMilliSecond  = 0;
    *usPosRatio     = 0;

    if (m_FLACFileInfo.ulTotalTime != 0) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, GET_PLAY_TIME|HIF_AUD_CMD_PLAY_POS);
        *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        *usPosRatio = (MMP_USHORT)(((MMP_ULONG64)(*ulMilliSecond) * 100) / (m_FLACFileInfo.ulTotalTime));
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetAMRPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get AMR Current Play Time
    @param[out] *usPosRatio : (current play position) / (total file size)
    @param[out] *ulMilliSecond : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetAMRPlayTime(MMP_USHORT *usPosRatio, MMP_ULONG *ulMilliSecond)
{
    *usPosRatio     = 0;
    *ulMilliSecond  = 0;

    if (m_AMRFileInfo.ulTotalTime != 0) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, GET_PLAY_TIME|HIF_AUD_CMD_PLAY_POS);
        *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        *usPosRatio = (MMP_USHORT)(((MMP_ULONG64)*ulMilliSecond * 100) / m_AMRFileInfo.ulTotalTime);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetOGGPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get OGG Current Play Time
    @param[out] *ulMilliSecond : milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetOGGPlayTime(MMP_ULONG *ulMilliSecond)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_PLAY_POS | GET_PLAY_TIME);
    
    *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWMAPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get WMA Current Play Time & Ratio
    @param[out] usPosRatio: Play position ratio in 1/1000.
    @param[out] ulMilliSecond: Current play time in ms.
    @return MMP_ERR_NONE
*/

MMP_ERR MMPD_AUDIO_GetWMAPlayTime(MMP_USHORT *usPosRatio, MMP_ULONG *ulMilliSecond)
{
    *usPosRatio     = 0;
    *ulMilliSecond  = 0;

    if ((m_WMAFileInfo.ulTotalTime != 0)) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, GET_PLAY_TIME|HIF_AUD_CMD_PLAY_POS);
        *ulMilliSecond = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

        // With rounding
        *usPosRatio = (MMP_USHORT)((((((MMP_ULONG64)(*ulMilliSecond)*100)<<1)/m_WMAFileInfo.ulTotalTime)+1)>>1);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetRAPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get RA Current Play Time & Ratio
    @param[out] *RACurTime : Time in ms
    @                *usPosRatio: ration in 1/1000
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetRAPlayTime(MMP_USHORT *usPosRatio, MMP_ULONG *ulRACurTime)
{
    if ((usPosRatio == NULL) || (ulRACurTime == NULL) || (m_RAFileInfo.ulTotalTime == 0))
        return MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, GET_PLAY_TIME|HIF_AUD_CMD_PLAY_POS);
    *ulRACurTime = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    #if 0 //w/o rounding
    *usPosRatio = (MMP_USHORT)((MMP_ULONG64)(*ulRaCurTime)*100/m_RAFileInfo.ulTotalTime);
    #else// w/  rounding
    *usPosRatio = (MMP_USHORT)((((((MMP_ULONG64)(*ulRACurTime)*100)<<1)/m_RAFileInfo.ulTotalTime)+1)>>1);
    #endif
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

#if 0
void ____Status_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlayStatus
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Play Status
    @param[out] *usStatus : status(stop,pause...)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetPlayStatus(MMP_USHORT *usStatus)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_STATUS | PLAY_STATUS);
        
    *usStatus = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetRecordStatus
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Record Status
    @param[out] *usStatus : status(stop,pause...)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetRecordStatus(MMP_USHORT *usStatus)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_REC_STATUS);
    *usStatus = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetLiveRecordStatus
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_GetLiveRecordStatus(MMP_USHORT *usStatus)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_LIVE_REC_STATUS);
    *usStatus = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWriteCardStatus
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Write Card Status
    @param[out] *usStatus : 0 : write card normal. 1: write card fail.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetWriteCardStatus(MMP_USHORT *usStatus)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_WRITE_STATUS);
    *usStatus = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

#if 0
void ____Buffer_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetEncodeBuf
//------------------------------------------------------------------------------
/** 
    @brief  Get audio encoding buffer
    @param[out]  ulAddr Address of the buffer
    @param[out]  ulSize Size of the buffer
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetEncodeBuf(MMP_ULONG* ulAddr, MMP_ULONG* ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    *ulAddr = m_ulAudioRecBufStart;
    *ulSize = m_ulAudioRecBufSize;
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetDecOutBuf
//------------------------------------------------------------------------------
/**
    @brief  Get the buffer which store the decoded PCM samples
    @param[out] *ulBufAddr : Decoded PCM buffer address
    @param[out] *ulBufSize : Decoded PCM buffer size (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPD_AUDIO_GetDecOutBuf(MMP_ULONG *ulBufAddr, MMP_ULONG *ulBufSize)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    status = MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_GET_DECODE_PCM_BUF);
    *ulBufAddr = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    *ulBufSize = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 4);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play Input  Stream Buffer
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size(must be power of 2)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    m_ulAudioPlayBufSize = ulSize;
    m_ulAudioPlayBufStart = ulAddr;    

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, ulSize);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_BUF);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEncodeBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record Output  Stream Buffer
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size(must be power of 2)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEncodeBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
    m_ulAudioRecBufStart = ulAddr;
    m_ulAudioRecBufSize = ulSize;
    
    if (ulAddr && ulSize) {
        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulAddr);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulSize);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_BUF);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    }
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetParseBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Bitstream Buffer For Parsing
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetParseBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);   

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, ulSize);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_BUF);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_PresetPlayFileNameBuf
//------------------------------------------------------------------------------
/** 
    @brief  Preset Audio Play File Name Buffer Address
    @param[in] ulBufAddr : buffer address
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_PresetPlayFileNameBuf(MMP_ULONG ulBufAddr)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulBufAddr);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PRESET_FILE_NAME);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayHandshakeBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play Memory Mode Handshake Buffer
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayHandshakeBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulAddr);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_HANDSHAKE_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecHandshakeBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record Memory Mode Handshake Buffer
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecHandshakeBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    m_ulAudioRecHandshakeBufStart = ulAddr;
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulAddr);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_HANDSHAKE_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlaySpectrumBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play Spectrum Buffer
    @param[in]  ulAddr : buffer address
    @param[in]  ulSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlaySpectrumBuf(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    m_ulAudioPlaySpectrumBufStart = ulAddr;
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulAddr);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_SPECTRUM_BUF);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetAudioTagBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Tag Bufer (WMA, WMAPRO, OGG)
    @param[in] ulTagAddr : tag buffer address
    @param[in] ulTagSize : tag buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetAudioTagBuf(MMP_ULONG ulTagAddr, MMP_ULONG ulTagSize)
{
    m_ulAudioTagBuf     = ulTagAddr;
    m_ulAudioTagBufSize = ulTagSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayFileNameBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play File Name Buffer Address
    @param[in] ulBufAddr : buffer address
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayFileNameBuf(MMP_ULONG ulBufAddr)
{
    m_ulAudioPlayFileNameBufStart = ulBufAddr;

    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEncodeFileNameBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record File Name Buffer Address
    @param[in] ulBufAddr : buffer address
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEncodeFileNameBuf(MMP_ULONG ulBufAddr)
{
    m_ulAudioEncodeFileNameBufStart = ulBufAddr;

    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetParseFileNameBuf
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play File Name Buffer Address
    @param[in] ulBufAddr : buffer address
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetParseFileNameBuf(MMP_ULONG ulBufAddr)
{
    m_ulAudioParseFileNameBufStart = ulBufAddr;
    return MMP_ERR_NONE;    
}

#if 0
void ____Misc_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_CheckPlayEnd
//------------------------------------------------------------------------------
/**
    @brief  Check and wait until the audio fifo end
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPD_AUDIO_CheckPlayEnd(void)
{
    MMP_USHORT  play_status;

    do {
        if (MMPD_AUDIO_GetPlayStatus(&play_status) != MMP_ERR_NONE) {
            return MMP_SYSTEM_ERR_CMDTIMEOUT;
        }    
    } while (play_status != DECODE_OP_STOP);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayPosition
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Start Play Position
    @param[in] ulPos : position(in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayPosition(MMP_ULONG ulPos)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulPos);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_PLAY_POS | SET_PLAY_POS);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlayPosition
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Play Current Position
    @param[out] *ulPos : position (in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetPlayPosition(MMP_ULONG *ulPos)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_PLAY_POS | GET_PLAY_POS);
    *ulPos = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetABRepeatMode
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play AB Repeat Mode
    @param[in] usPoint : A or B
    @param[in] ulPos : position (in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetABRepeatMode(MMP_USHORT usPoint, MMP_ULONG ulPos)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    if (usPoint == ABREPEAT_SET_POINTA) {
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AB_REPEAT_MODE | ABREPEAT_SET_POINTA);
    } 
    else {
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulPos);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AB_REPEAT_MODE | ABREPEAT_SET_POINTB);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_EnableABRepeatMode
//------------------------------------------------------------------------------
/** 
    @brief  Enable AB Repeat Mode
    @param[in] usEnable : enable or disable
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_EnableABRepeatMode(MMP_USHORT usEnable)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    if (usEnable) {
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AB_REPEAT_MODE | ABREPEAT_MODE_ENABLE);
    } 
    else {
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AB_REPEAT_MODE | ABREPEAT_MODE_DISABLE);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StartMIDINotePlay
//------------------------------------------------------------------------------
/** 
    @brief  Start MIDI Note Play
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_StartMIDINotePlay(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_MIDI_DEC_OP | DECODE_OP_PLAY_NOTE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StopMIDINotePlay
//------------------------------------------------------------------------------
/** 
    @brief  Stop MIDI Note Play
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_StopMIDINotePlay(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_MIDI_DEC_OP | DECODE_OP_STOP_NOTE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetWMAVersion
//------------------------------------------------------------------------------
/** 
    @brief  Get the wma decoder version
    @param[in]  ulVersion : version of the WMA decoder
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetWMAVersion(MMP_ULONG *ulVersion)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_WMA_DEC_OP | DECODE_OP_GET_VERSION);
    
    *ulVersion = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    m_ulWMADecoderVersion = *ulVersion;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEncodeMode
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Encode Mode
    @param[in]  usMode : mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEncodeMode(MMP_USHORT usMode)
{  
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usMode);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_MODE);
    
    m_usAudioEncodeMode = usMode;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetLiveEncodeMode
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Live Encode Mode
    @param[in]  usMode : mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetLiveEncodeMode(MMP_USHORT usMode)
{  
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usMode);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_LIVEENCODE_MODE);
    
    m_usAudioLiveEncodeMode = usMode;
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetLiveEncodeSampleRate
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_SetLiveEncodeSampleRate(MMP_USHORT usSampleRate)
{  
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usSampleRate);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_LIVEENCODE_SAMPLERATE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetEncodeMode
//------------------------------------------------------------------------------
/** 
    @brief  get Audio Encode Mode
    @param[in]  usMode : mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetEncodeMode(MMP_USHORT *usMode)
{
    *usMode = m_usAudioEncodeMode;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetLiveEncodeMode
//------------------------------------------------------------------------------
/** 
    @brief  get Audio Encode Mode
    @param[in]  usMode : mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetLiveEncodeMode(MMP_USHORT *usMode)
{
    *usMode = m_usAudioLiveEncodeMode;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEncodeFormat
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Encode Format
    @param[in]  encodefmt: encode format
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_ENCODE_FMT encodefmt)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, encodefmt);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_FORMAT);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    m_AudioEncodeFormat = encodefmt;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetLiveEncodeCB
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_SetLiveEncodeCB(MMP_LivePCMCB  LivePCMCB)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, (MMP_ULONG)LivePCMCB);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_LIVEENCODE_CB);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetLiveEncodeFormat
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_SetLiveEncodeFormat( MMP_AUDIO_ENCODE_FMT    encodefmt,
                                        MMP_ULONG               inSamplerate,
                                        MMP_ULONG               outSamplerate,
                                        MMP_UBYTE               inCh,
                                        MMP_UBYTE               outCh)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0,  encodefmt);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4,  inSamplerate);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8,  outSamplerate);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 12, inCh);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 16, outCh);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_LIVEENCODE_PARAM);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    m_AudioLiveEncodeFormat = encodefmt;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEncodeFileSize
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Encode File Size(stop recording while over limitation)
    @param[in]  ulSize : file size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEncodeFileSize(MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulSize);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_FILE_LIMIT);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayFileName
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play File Name
    @param[in] *bFileName : file name
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength)
{
    MMP_UBYTE   null = 0;
    MMP_ERR     mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayFileNameBufStart, (MMP_UBYTE *)bFileName, ulNameLength);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayFileNameBufStart + ulNameLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayFileNameBufStart + ulNameLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, m_ulAudioPlayFileNameBufStart);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_FILE_NAME);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    if (mmpstatus) {
        return MMP_AUDIO_ERR_OPENFILE_FAIL;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEncodeFileName
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record File Name
    @param[in] *bFileName : file name
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEncodeFileName(MMP_BYTE *bFileName, MMP_ULONG ulFileNameLength)
{
    MMP_UBYTE   null = 0;
    MMP_ERR     mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioEncodeFileNameBufStart, (MMP_UBYTE *)bFileName, ulFileNameLength);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioEncodeFileNameBufStart + ulFileNameLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioEncodeFileNameBufStart + ulFileNameLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, m_ulAudioEncodeFileNameBufStart);        
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_FILE_NAME);
    
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    if (mmpstatus) {
        return MMP_AUDIO_ERR_OPENFILE_FAIL;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayPath
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play Path
    @param[in]  ubPath : card mode or memory path
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_DATAPATH ubPath)
{
    m_ubAudioPlayPath = ubPath;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 4, ubPath);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_PATH);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEncodePath
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record Path
    @param[in]  ubPath : card mode or memory path
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_DATAPATH ubPath)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, ubPath);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_PATH);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetRecordFileSize
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Record Current File Size
    @param[out] *ulSize : file size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetRecordSize(MMP_ULONG *ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENC_OP | ENCODE_OP_GET_FILESIZE);

    *ulSize = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlayFileSize
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Play File Size From Firmware(Card Mode)
    @param[out] *ulFileSize : file size (in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetPlayFileSize(MMP_ULONG *ulFileSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_GET_FILE_SIZE);
    
    *ulFileSize = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetRecordFrameCntInSeconds
//------------------------------------------------------------------------------
/** 
    @brief  Get The Expected Audio Record Frame Count in The Specified Time
    @param[in]   ulSec : Specify the time in unit of second
    @param[out] *ulCnt : The encoded frame count expected in the given time
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetRecordFrameCntInSeconds(MMP_ULONG ulSec, MMP_ULONG *ulCnt)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulSec);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_GET_ENCODE_PARAM | FRAME_CNT_IN_SEC);

    *ulCnt = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayFileSize
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play File Size to Firmware (Memory Mode)
    @param[out] ulFileSize : file size (in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayFileSize(MMP_ULONG ulFileSize)
{
    // Control the data put in the internal audio buffer
    m_ulAudioPlayRemainFileSize = ulFileSize;
    m_ulAudioPlayFileSize       = ulFileSize;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulFileSize);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_SET_FILE_SIZE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetAC3VHPar
//------------------------------------------------------------------------------
/**
    @brief  Set virtualizer parameters, m3deff or db.
    @param[in] lm3deff : -1..10 (-1,0 - no effect (simple downmixer will be used), 1 - min level, 10 �V max level)
    @param[in] ldb : dB = 0..20 ( prescaling value in dB, 0 - no volume reduction )
    @param[in] bSet_m3deff : Set m3deff parameter or ignore
    @param[in] bSet_db : Set db parameter or ignore
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetAC3VHPar(MMP_LONG lm3deff, MMP_LONG ldb, MMP_BOOL bSet_m3deff, MMP_BOOL bSet_db)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, lm3deff);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ldb);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, bSet_m3deff);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 12, bSet_db);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AC3_CODE_OP | SET_AC3_VHPAR);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetWAVEncodeEnable
//------------------------------------------------------------------------------
/** 
    @brief  Set Wav Encode Enable or not
    @param[in] ubEnable
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetWAVEncodeEnable(MMP_UBYTE ubEnable)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0,ubEnable);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_WAV_ENCODE | SET_WAV_ENCODE_ENABLE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlaySpectrum
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Play Spectrum 
    @param[out]  usSpectrum[] : spectrum data
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetPlaySpectrum(MMP_USHORT usSpectrum[])
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AUDIO_SPECTRUM);
    
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)usSpectrum, m_ulAudioPlaySpectrumBufStart, MMPD_AUDIO_SPECTRUM_DATA_SIZE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_AACPlusPlayTime2FileOffset
//------------------------------------------------------------------------------
/** 
    @brief  Convert AACPLUS Play Time to File Offset
    @param[in]   ulMilliSec: milli second
    @param[out]  *ulFileOffset : file offset
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_AACPlusPlayTime2FileOffset(MMP_ULONG ulMilliSec, MMP_ULONG *ulFileOffset)
{
    *ulFileOffset = (ulMilliSec/1000) * (m_AACPlusFileInfo.ulBitRate/8);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_MP3PlayTime2FileOffset
//------------------------------------------------------------------------------
/** 
    @brief  Convert MP3 Play Time to File Offset
    @param[in]   ulMilliSec: milli second
    @param[out]  *ulFileOffset : file offset
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_MP3PlayTime2FileOffset(MMP_ULONG ulMilliSec, MMP_ULONG *ulFileOffset)
{
    *ulFileOffset = ulMilliSec * (m_MP3FileInfo.ulBitRate/8000);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_WAVPlayTime2FileOffset
//------------------------------------------------------------------------------
/** 
    @brief  Convert WAV Play Time to File Offset
    @param[in]   ulMilliSec: milli second
    @param[out]  *ulFileOffset : file offset
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_WAVPlayTime2FileOffset(MMP_ULONG ulMilliSec, MMP_ULONG *ulFileOffset)
{
    *ulFileOffset = ulMilliSec * (m_WAVFileInfo.ulBitRate/8000);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_AMRPlayTime2FileOffset
//------------------------------------------------------------------------------
/** 
    @brief  Convert AMR Play Time to File Offset
    @param[in]   ulMilliSec: milli second
    @param[out]  *ulFileOffset : file offset
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_AMRPlayTime2FileOffset(MMP_ULONG ulMilliSec, MMP_ULONG *ulFileOffset)
{
    *ulFileOffset = ulMilliSec * (m_AMRFileInfo.ulBitRate/8000);
    *ulFileOffset = *ulFileOffset - (*ulFileOffset%m_AMRFileInfo.usSampleSize);
    *ulFileOffset = *ulFileOffset + 6;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetAudioPlayBufSize
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Play Input Stream Buffer Size
    @param[out]  *ulSize : buffer size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetAudioPlayBufSize(MMP_ULONG *ulSize)
{
    *ulSize = m_ulAudioPlayBufSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayFormat
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play Mode
    @param[in]  decodefmt: decode format
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_DECODE_FMT decodefmt)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, decodefmt);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_FORMAT);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    m_AudioDecodeFormat = decodefmt;

    return MMP_ERR_NONE;
}    

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayIntThreshold
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play Interrupt Threshold
    @param[in]  usThreshold : threshold
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayIntThreshold(MMP_USHORT usThreshold)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usThreshold);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_INT_THRESHOLD);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecordIntThreshold
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Record Interrupt Threshold
    @param[in]  usThreshold : threshold
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecordIntThreshold(MMP_USHORT usThreshold)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usThreshold);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_INT_THRESHOLD);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

#if (AUDIO_PREVIEW_SUPPORT == 1)
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_StartPreview
//------------------------------------------------------------------------------
/**
    @brief  Start Audio Preview
    @param[in] ulStartTime : start time to preview (ms)
    @param[in] ulDuration : preview duration (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPD_AUDIO_StartPreview(MMP_ULONG ulStartTime, MMP_ULONG ulDuration)
{
    MMP_ERR err;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulStartTime);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, ulDuration);
    
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DEC_OP | DECODE_OP_PREVIEW);
    err = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return err;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPreviewStatus
//------------------------------------------------------------------------------
/**
    @brief  Get Audio Preview Data Status
    @param[out] *bDataReady : Preview data is ready or not
    @param[out] **usDataBuf : Preview data buffer address
    @param[out] *ulSampleNum : Number of samples in buffer
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPD_AUDIO_GetPreviewStatus(MMP_BOOL *bDataReady, MMP_SHORT **usDataBuf, MMP_ULONG *ulSampleNum)
{
    *usDataBuf = NULL;
    *ulSampleNum = 0;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_STATUS | PREVIEW_STATUS);
    
    *bDataReady = MMPH_HIF_GetParameterB(GRP_IDX_AUD, 0);
    
    if (*bDataReady == MMP_TRUE) {
        *usDataBuf = (MMP_SHORT *)MMPH_HIF_GetParameterL(GRP_IDX_AUD, (4);
        *ulSampleNum = MMPH_HIF_GetParameterL(GRP_IDX_AUD, (8);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetInPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set Audio In Path
    @param[in] audiopath specific audio output path
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetInPath(MMP_ULONG audiopath)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, audiopath);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_ADC_PATH);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    mmpstatus = MMP_ERR_NONE;

    return mmpstatus;
}
    
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetLineInChannel
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set Audio In Channel
    @param[in] lineinchannel specific audio input path
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetLineInChannel(MMP_AUD_LINEIN_CH lineinchannel)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, (MMP_USHORT)lineinchannel);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_LINEIN_CHANNEL);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetOutPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Out Path
    @param[in] audiopath specific audio output path
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetOutPath(MMP_ULONG audiopath)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, audiopath);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, AUDIO_DECODE_DAC_PATH | HIF_AUD_CMD_DECODE_PARAM);

    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    mmpstatus = MMP_ERR_NONE;

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPLL
//------------------------------------------------------------------------------
/**
    @brief  Dynamic change PLL for audio DAC.
    @param[in] usSampleRate : audio sample rate
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPLL(MMP_USHORT usSampleRate)
{
    MMP_ERR retstatus = MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, (MMP_ULONG)usSampleRate);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_ENCODE_PARAM | AUDIO_ENCODE_SET_AUDIO_PLL);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return retstatus;
}

#if (GAPLESS_PLAY_EN == 1)
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetGaplessAllowedOp
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Get current allowed operation in gapless playback
    @param[out] MMP_USHORT : 
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetGaplessAllowedOp(MMP_USHORT *op)
{
    if (m_bGaplessEnable) {
        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_GAPLESS | GET_ALLOWED_OP);
        *op = MMPH_HIF_GetParameterW(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    }
    else {
        *op = MMP_AUDIO_GAPLESS_OP_ALL;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetGaplessEnable
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set gapless mode playback enable or disable
    @param[in] bEnable : enable or disable gapless mode playback
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetGaplessEnable(MMP_BOOL bEnable, void *nextFileCB, MMP_ULONG param1)
{
    m_bGaplessEnable = bEnable;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, bEnable);
    
    if (bEnable) {
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, (MMP_ULONG)nextFileCB);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, param1);
    }
    else {
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, 0);
        MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, 0);
    }
    
    MMPH_HIF_SendCmd(GRP_IDX_AUD, GAPLESS_SET_MODE | HIF_AUD_CMD_GAPLESS);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlayFormat
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_GetPlayFormat(MMP_AUDIO_DECODE_FMT *format)
{
    *format = m_AudioDecodeFormat;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetEncodeFormat
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_GetEncodeFormat(MMP_AUDIO_ENCODE_FMT *fmt)
{
    *fmt = m_AudioEncodeFormat;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetLiveEncodeFormat
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_GetLiveEncodeFormat(MMP_AUDIO_ENCODE_FMT *fmt)
{
    *fmt = m_AudioLiveEncodeFormat;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetParseFormat
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Format For Parsing
    @param[in]  fmt: parsing format
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetParseFormat(MMP_AUDIO_DECODE_FMT fmt)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, fmt);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_FORMAT);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetParseFileName
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio File Name For Parsing
    @param[in] *bFileName : file name
    @param[in] ulNameLength : file name length
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetParseFileName(MMP_BYTE *bFileName, MMP_ULONG ulNameLength)
{
    MMP_UBYTE   null = 0;
    MMP_ERR     mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioParseFileNameBufStart, (MMP_UBYTE *)bFileName, ulNameLength);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioParseFileNameBufStart + ulNameLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioParseFileNameBufStart + ulNameLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, m_ulAudioParseFileNameBufStart);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_FILE_NAME);
    
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    if (mmpstatus) {
        return MMP_AUDIO_ERR_OPENFILE_FAIL;
    }

    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetParsePath
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Path For Parsing
    @param[in]  ubPath : card/memory/MMP memory mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetParsePath(MMPD_AUDIO_PLAY_DATAPATH ubPath)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, MMP_AUD_PLAYER_TYPE_AUDIO);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 4, ubPath);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_PARSE_PATH);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_UpdatePlayStreamSize
//------------------------------------------------------------------------------
/** 
    @brief  Set Aduio Play File Remain Size
    @param[in]   ulFileSize: file remain size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_UpdatePlayStreamSize(MMP_ULONG ulFileSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    m_ulAudioPlayRemainFileSize = ulFileSize;

    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulFileSize);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_DECODE_PARAM | AUDIO_DECODE_SET_FILE_SIZE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_UpdatePlayFileRemainSize
//------------------------------------------------------------------------------
/** 
    @brief  Set Aduio Play File Remain Size (Memory Mode)
    @param[in]   ulFileSize: file remain size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_UpdatePlayFileRemainSize(MMP_ULONG ulFileSize)
{ 
    m_ulAudioPlayRemainFileSize = ulFileSize;
    return MMP_ERR_NONE;
}

#if 0
void ____Memory_Mode_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlayFinishSeekFlag
//------------------------------------------------------------------------------
/** 
    @brief  Get Aduio Play Finish Seek Flag (Memory Mode)
    @param[out]   *usFlag: finish seek flag
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetPlayFinishSeekFlag(MMP_USHORT *usFlag)
{
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)usFlag, m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_FINISH_SEEK_W, 2);    

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlayStartSeekFlag
//------------------------------------------------------------------------------
/** 
    @brief  Get Aduio Play Start Seek Flag (Memory Mode)
    @param[out]   *usFlag: start seek flag
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetPlayStartSeekFlag(MMP_USHORT *usFlag)
{ 
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)usFlag, m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_START_SEEK_W, 2); 

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayStartSeekFlag
//------------------------------------------------------------------------------
/** 
    @brief  Set Aduio Play Start Seek Flag (Memory Mode)
    @param[in]   usFlag: start seek flag
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayStartSeekFlag(MMP_USHORT usFlag)
{
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_START_SEEK_W, (MMP_UBYTE *)&usFlag, 2);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetPlayFileSeekOffset
//------------------------------------------------------------------------------
/** 
    @brief  Get Aduio Play File Seek Offset (Memory Mode)
    @param[out]   *ulOffset: file offset
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetPlayFileSeekOffset(MMP_ULONG *ulOffset)
{
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)ulOffset, m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_FILE_SEEK_OFFSET_L_W, 4);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_InitPlaySeekFlag
//------------------------------------------------------------------------------
/** 
    @brief  Reset Aduio Play Seek Flag (Memory Mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_InitPlaySeekFlag(void)
{    
    MMP_USHORT flag = 0;

    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_START_SEEK_W, (MMP_UBYTE *)&flag, 2);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_FINISH_SEEK_W, (MMP_UBYTE *)&flag, 2);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_InitPlayRWPtr
//------------------------------------------------------------------------------
/** 
    @brief  Reset Audio Play Stream R/W Pointer (Memoey mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_InitPlayRWPtr(void)
{
    m_ulAudioPlayReadPtr        = 0;
    m_ulAudioPlayReadPtrHigh    = 0;    
    m_ulAudioPlayWritePtr       = 0;
    m_ulAudioPlayWritePtrHigh   = 0;

    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_PTR_OFST,
                              (MMP_UBYTE *)&m_ulAudioPlayReadPtr, 4);
                                
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_HPTR_OFST,
                              (MMP_UBYTE *)&m_ulAudioPlayReadPtrHigh, 4);

    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_W_PTR_OFST,
                              (MMP_UBYTE *)&m_ulAudioPlayWritePtr, 4);
                                
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_W_HPTR_OFST,
                              (MMP_UBYTE *)&m_ulAudioPlayWritePtrHigh, 4);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_InitRecRWPtr
//------------------------------------------------------------------------------
/** 
    @brief  Reset Audio Record Stream R/W Pointer(Memoey mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_InitRecRWPtr(void)
{
    m_usAudioRecReadPtr         = 0;
    m_usAudioRecReadPtrHigh     = 0;    
    m_usAudioRecWritePtr        = 0;
    m_usAudioRecWritePtrHigh    = 0;
    
    MMPH_HIF_MemCopyHostToDev(m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_WRITE_PTR_OFFSET_W,
                              (MMP_UBYTE *)&m_usAudioRecWritePtr, 2);
    
    MMPH_HIF_MemCopyHostToDev(m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_WRITE_HIGH_PTR_OFFSET_W,
                              (MMP_UBYTE *)&m_usAudioRecWritePtrHigh, 2);

    MMPH_HIF_MemCopyHostToDev(m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_READ_PTR_OFFSET_W,
                              (MMP_UBYTE *)&m_usAudioRecReadPtr, 2);
    
    MMPH_HIF_MemCopyHostToDev(m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_READ_HIGH_PTR_OFFSET_W,
                              (MMP_UBYTE *)&m_usAudioRecReadPtrHigh, 2);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_InitialMemModePointer
//------------------------------------------------------------------------------
/** 
    @brief Initial buffer pointer for Memory Mode
    @param[in] ubBufAddr buffer address for audio data
    @param[in] ulBufSize buffer size for audio data
    @param[in] ulWriteSize write size
    @param[in] ulBufThreshold buffer threshold
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_InitialMemModePointer(MMP_UBYTE *ubBufAddr, MMP_ULONG ulBufSize, MMP_ULONG ulWriteSize, MMP_ULONG ulBufThreshold)
{
    m_ubMemPtr          = ubBufAddr;
    m_ulMemBufSize      = ulBufSize;
    m_ulBufThreshold    = ulBufThreshold;

    m_ulMemReadPtr      = 0;
    m_ulMemReadPtrHigh  = 0;
    m_ulMemWritePtr     = 0;
    m_ulMemWritePtrHigh = 0;

    if (m_ubMemPtr && m_ulMemBufSize) {
        m_ulMemWritePtr += ulWriteSize;
        if (m_ulMemWritePtr >= m_ulMemBufSize) {
            m_ulMemWritePtr -= m_ulMemBufSize;
            m_ulMemWritePtrHigh++;
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetMemModeReadPointer
//------------------------------------------------------------------------------
/** 
    @brief Set buffer read pointer for Memory Mode
    @param[in] ulMemReadPtr read pointer position
    @param[in] ulMemReadPtrHigh high part of read pointer
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetMemModeReadPointer(MMP_ULONG ulMemReadPtr, MMP_ULONG ulMemReadPtrHigh)
{
    m_ulMemReadPtr      = ulMemReadPtr;
    m_ulMemReadPtrHigh  = ulMemReadPtrHigh;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_TransferDataHostToDev
//------------------------------------------------------------------------------
/** 
    @brief  Transfer Audio Data From Host to Firmware (Memory Mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_TransferDataHostToDev(void)
{
    MMP_ULONG   cur_buf_to_put_size;
    MMP_ULONG   tmp_size, rem_size;
    MMP_UBYTE   *data_ptr;
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPD_AUDIO_UpdatePlayReadPtr();
    
    data_ptr = (MMP_UBYTE *)(m_ubMemPtr + m_ulMemReadPtr);
    
    if (m_ulAudioPlayReadPtr == m_ulAudioPlayWritePtr) {
    
        if (m_ulAudioPlayReadPtrHigh == m_ulAudioPlayWritePtrHigh) {
            if (m_ulAudioPlayReadPtr == m_ulAudioPlayWritePtr) {
                cur_buf_to_put_size = m_ulAudioPlayBufSize;
            }   
            else{
                return MMP_AUDIO_ERR_STREAM_BUF_FULL;   
            }
        }   
        else {
            if ((m_ulAudioPlayWritePtrHigh - m_ulAudioPlayReadPtrHigh) != 1) {
                return  MMP_AUDIO_ERR_STREAM_UNDERFLOW;
            }
            else {
                return MMP_AUDIO_ERR_STREAM_BUF_FULL;   
            }   
        }       
    }
    else {
        if (m_ulAudioPlayReadPtr > m_ulAudioPlayWritePtr) 
            cur_buf_to_put_size = m_ulAudioPlayReadPtr - m_ulAudioPlayWritePtr; 
        else 
            cur_buf_to_put_size = m_ulAudioPlayBufSize - (m_ulAudioPlayWritePtr - m_ulAudioPlayReadPtr);    
    }   

    //cur_buf_to_put_size : the empty count for the internal frame buffer
    //cur_buf_to_put_size : shrink to make the fetch of host buffer to be non-ring type
    if (cur_buf_to_put_size > (m_ulMemBufSize - m_ulMemReadPtr))
        cur_buf_to_put_size = m_ulMemBufSize - m_ulMemReadPtr;
        
    if (cur_buf_to_put_size > m_ulAudioPlayRemainFileSize)
        cur_buf_to_put_size = m_ulAudioPlayRemainFileSize;

    tmp_size = m_ulAudioPlayBufSize - m_ulAudioPlayWritePtr;
    
    if (tmp_size > cur_buf_to_put_size) {
        tmp_size = cur_buf_to_put_size;
        
        #if (OMA_DRM_EN == 1)
        if (drmEn) {
            tmp_size = (tmp_size >> 4) << 4; // Must 16 bytes alignment
            cur_buf_to_put_size = tmp_size;
            if (tmp_size) {
                MMPD_AUDIO_DecryptBufByKey((MMP_UBYTE *)(data_ptr), tmp_size, MMPD_OMADRM_FOR_PLAY);
            }
        }
        #endif
        
        MMPH_HIF_MemCopyHostToDev((m_ulAudioPlayWritePtr + m_ulAudioPlayBufStart),data_ptr, tmp_size);
         
        data_ptr += tmp_size;       
            
        m_ulAudioPlayWritePtr += tmp_size;
    }
    else {
        rem_size = cur_buf_to_put_size - tmp_size;

        #if (OMA_DRM_EN == 1)
        if (drmEn) {
            if (tmp_size & 0x0F) {
                PRINTF("Audio play input stream buffer must be 16-byte algnment\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
            MMPD_AUDIO_DecryptBufByKey((MMP_UBYTE *)(data_ptr), tmp_size, MMPD_OMADRM_FOR_PLAY);
            cur_buf_to_put_size = tmp_size;
        }
        #endif
        
        MMPH_HIF_MemCopyHostToDev((m_ulAudioPlayWritePtr + m_ulAudioPlayBufStart), data_ptr, tmp_size);
        
        data_ptr += tmp_size;       
    
        m_ulAudioPlayWritePtr = 0;
        m_ulAudioPlayWritePtrHigh += 1;
        
        if (rem_size) {
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                rem_size = (rem_size >> 4) << 4; // Must 16 bytes alignment
                if (rem_size) {
                    MMPD_AUDIO_DecryptBufByKey((MMP_UBYTE *)(data_ptr), rem_size, MMPD_OMADRM_FOR_PLAY);
                    cur_buf_to_put_size += rem_size;
                }
            }
            #endif
            
            MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayBufStart, data_ptr, rem_size);
            data_ptr += rem_size;

            m_ulAudioPlayWritePtr = rem_size;
        }
    }   

    MMPD_AUDIO_UpdatePlayWritePtr();
    m_ulAudioPlayRemainFileSize -= cur_buf_to_put_size;

    m_ulMemReadPtr += cur_buf_to_put_size;
    
    if (m_ulMemReadPtr >= m_ulMemBufSize) {
        m_ulMemReadPtrHigh++;
        m_ulMemReadPtr = 0;
    }       

    if (m_ulAudioPlayRemainFileSize) {
        return MMP_ERR_NONE;
    }
    else {
        return MMP_AUDIO_ERR_END_OF_FILE;
    }       
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_TransferDataCardToHost
//------------------------------------------------------------------------------
/** 
    @brief  Transfer Audio Data From Firmware to Host (Memory Mode)
    @param[in] ulFileID file ID
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_TransferDataCardToHost(void* FileHandle)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_ULONG   cur_buf_to_read_size;
    MMP_ULONG   return_size, tmp_size;

    if (m_ulMemReadPtr == m_ulMemWritePtr) {
        if (m_ulMemReadPtrHigh == m_ulMemWritePtrHigh) {
            cur_buf_to_read_size = m_ulMemBufSize;
        }   
        else if ((m_ulMemReadPtrHigh - m_ulMemWritePtrHigh) == 1) {
            return MMP_AUDIO_ERR_STREAM_BUF_FULL;   
        }
        else {
            return  MMP_AUDIO_ERR_STREAM_UNDERFLOW; 
        }       
    }
    else {
        if (m_ulMemReadPtr > m_ulMemWritePtr) 
            cur_buf_to_read_size = m_ulMemReadPtr - m_ulMemWritePtr;    
        else 
            cur_buf_to_read_size = m_ulMemBufSize - (m_ulMemWritePtr - m_ulMemReadPtr); 
    }
    
    if (cur_buf_to_read_size > m_ulBufThreshold)
        cur_buf_to_read_size = (cur_buf_to_read_size / m_ulBufThreshold) * m_ulBufThreshold;
    else    
        cur_buf_to_read_size = 0;               

    if (cur_buf_to_read_size) {
    
        tmp_size = m_ulMemBufSize - m_ulMemWritePtr;
        
        if (cur_buf_to_read_size > tmp_size) {
            
            err = MMPC_FS_FileRead(FileHandle, m_ubMemPtr + m_ulMemWritePtr, tmp_size, &return_size);
            if (err != MMP_ERR_NONE) {
                return err;
            }

            m_ulMemWritePtrHigh++;
            m_ulMemWritePtr = 0;
            
            err = MMPC_FS_FileRead(FileHandle, m_ubMemPtr, cur_buf_to_read_size - tmp_size, &return_size);
            if (err != MMP_ERR_NONE) {
                return err;
            }
            
            m_ulMemWritePtr = cur_buf_to_read_size - tmp_size;
        }
        else {
            err = MMPC_FS_FileRead(FileHandle, m_ubMemPtr + m_ulMemWritePtr, cur_buf_to_read_size, &return_size);
            if (err != MMP_ERR_NONE) {
                return err;
            }

            m_ulMemWritePtr += cur_buf_to_read_size;
            if (m_ulMemWritePtr >= m_ulMemBufSize) {
                m_ulMemWritePtrHigh++;
                m_ulMemWritePtr = 0;
            }
        }
    }       

    return  MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_UpdatePlayReadPtr
//------------------------------------------------------------------------------
/** 
    @brief  Update Audio Play Stream Buffer Read Pointer(Memory Mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_UpdatePlayReadPtr(void)
{    
    MMP_ULONG low_temp, high_temp;

    low_temp = m_ulAudioPlayReadPtr;
    high_temp = m_ulAudioPlayReadPtrHigh;

    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_ulAudioPlayReadPtr, m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_PTR_OFST, 4);
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_ulAudioPlayReadPtrHigh, m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_HPTR_OFST, 4);

    if (((m_ulAudioPlayReadPtrHigh > high_temp) && (m_ulAudioPlayReadPtr >= low_temp)) || 
        ((m_ulAudioPlayReadPtrHigh == high_temp) && (m_ulAudioPlayReadPtr < low_temp))) {
        MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_ulAudioPlayReadPtr, m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_PTR_OFST, 4);
        MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_ulAudioPlayReadPtrHigh, m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_HPTR_OFST, 4);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_UpdateRecWritePtr
//------------------------------------------------------------------------------
/** 
    @brief  Update Audio Record Stream Buffer Write Pointer(Memory Mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_UpdateRecWritePtr(void)
{    
    MMP_USHORT low_temp,high_temp;

    low_temp = m_usAudioRecWritePtr;
    high_temp = m_usAudioRecWritePtrHigh;
    
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_usAudioRecWritePtr, m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_WRITE_PTR_OFFSET_W, 2);
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_usAudioRecWritePtrHigh, m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_WRITE_HIGH_PTR_OFFSET_W, 2);

    if (((m_usAudioRecWritePtrHigh > high_temp)&&(m_usAudioRecWritePtr >= low_temp))||
        ((m_usAudioRecWritePtrHigh == high_temp)&&(m_usAudioRecWritePtr < low_temp))){
        MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_usAudioRecWritePtr, m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_WRITE_PTR_OFFSET_W, 2);
        MMPH_HIF_MemCopyDevToHost((MMP_UBYTE *)&m_usAudioRecWritePtrHigh, m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_WRITE_HIGH_PTR_OFFSET_W, 2);
    }  

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayReadPtr
//------------------------------------------------------------------------------
/** 
    @brief  Update Audio Play Stream Buffer Read Pointer to Firmware(Memory mode). It's briefly used
            for inform decoder to decode from the specified position.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayReadPtr(MMP_ULONG ulAudioPlayReadPtr, MMP_ULONG ulAudioPlayReadPtrHigh)
{ 
    m_ulAudioPlayReadPtr = ulAudioPlayReadPtr;
    m_ulAudioPlayReadPtrHigh = ulAudioPlayReadPtrHigh;      

    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_PTR_OFST, 
                        (MMP_UBYTE *)&m_ulAudioPlayReadPtr, 4);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_R_HPTR_OFST, 
                        (MMP_UBYTE *)&m_ulAudioPlayReadPtrHigh, 4);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetPlayWritePtr
//------------------------------------------------------------------------------
/** 
    @brief  Update Audio Play Stream Buffer Write Pointer to Firmware(Memory mode). It's briefly used
            for inform decoder how many data stored in buffer
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetPlayWritePtr(MMP_ULONG ulAudioPlayWritePtr, MMP_ULONG ulAudioPlayWritePtrHigh)
{
    m_ulAudioPlayWritePtr = ulAudioPlayWritePtr;
    m_ulAudioPlayWritePtrHigh = ulAudioPlayWritePtrHigh;        

    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_W_PTR_OFST, 
                        (MMP_UBYTE *)&m_ulAudioPlayWritePtr, 4);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_W_HPTR_OFST, 
                        (MMP_UBYTE *)&m_ulAudioPlayWritePtrHigh, 4);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_UpdatePlayWritePtr
//------------------------------------------------------------------------------
/** 
    @brief  Update Audio Play Stream Buffer Write Pointer to Firmware(Memory mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_UpdatePlayWritePtr(void)
{   
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_W_PTR_OFST, 
                        (MMP_UBYTE *)&m_ulAudioPlayWritePtr, 4);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayHandshakeBufAddr + AUDIO_PLAY_W_HPTR_OFST, 
                        (MMP_UBYTE *)&m_ulAudioPlayWritePtrHigh, 4);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetRecReadPtr
//------------------------------------------------------------------------------
/** 
    @brief  Update Audio Record Stream Buffer Read Pointer to Firmware(Memory mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetRecReadPtr(void)
{
    MMPH_HIF_MemCopyHostToDev(m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_READ_PTR_OFFSET_W, 
                        (MMP_UBYTE *)&m_usAudioRecReadPtr, 2);
    MMPH_HIF_MemCopyHostToDev(m_ulAudioRecHandshakeBufStart + MMPD_AUDIO_REC_READ_HIGH_PTR_OFFSET_W, 
                        (MMP_UBYTE *)&m_usAudioRecReadPtrHigh, 2);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_TransferDataToHost
//------------------------------------------------------------------------------
/** 
    @brief  Transfer Audio Data From Firmware to Host(Memory Mode)
    @param[in] ubAudioPtr : audio data buffer start pointer
    @param[in] ulMaxSize  : max data size to transfer
    @param[out] *ulReturnSize : actual transfer data size    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_TransferDataToHost(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, MMP_ULONG *ulReturnSize)
{
    MMP_USHORT  cur_buf_to_get_size;
    MMP_USHORT  tmp_size;
    MMP_UBYTE   *data_ptr;
    
    MMPD_AUDIO_UpdateRecWritePtr();

    data_ptr = (MMP_UBYTE *)ubAudioPtr;
    
    *ulReturnSize = 0;
    
    if (m_usAudioRecWritePtr == m_usAudioRecReadPtr) {
        if (m_usAudioRecWritePtrHigh == m_usAudioRecReadPtrHigh) {
            return MMP_AUDIO_ERR_STREAM_BUF_EMPTY;  
        }   
        else {
            if ((m_usAudioRecWritePtrHigh - m_usAudioRecReadPtrHigh) != 1) { 
                return MMP_AUDIO_ERR_STREAM_OVERFLOW;
            }   
        }       
    }
    else {
        if (m_usAudioRecWritePtr > m_usAudioRecReadPtr) 
            cur_buf_to_get_size = m_usAudioRecWritePtr - m_usAudioRecReadPtr;   
        else 
            cur_buf_to_get_size = m_ulAudioRecBufSize - (m_usAudioRecReadPtr - m_usAudioRecWritePtr);   
            
        if (cur_buf_to_get_size > ulMaxSize) {
            cur_buf_to_get_size = ulMaxSize;
        }   
                
        *ulReturnSize = cur_buf_to_get_size;
            
        tmp_size = m_ulAudioRecBufSize - m_usAudioRecReadPtr;

        if (tmp_size > cur_buf_to_get_size) {
            tmp_size = cur_buf_to_get_size;
            
            MMPH_HIF_MemCopyDevToHost(data_ptr, (m_usAudioRecReadPtr + m_ulAudioRecBufStart), tmp_size);
        
            m_usAudioRecReadPtr += tmp_size;
        }
        else {
            MMPH_HIF_MemCopyDevToHost(data_ptr, (m_usAudioRecReadPtr + m_ulAudioRecBufStart), tmp_size);
        
            data_ptr += tmp_size;
            m_usAudioRecReadPtr = 0;
            m_usAudioRecReadPtrHigh += 1;
            
            MMPH_HIF_MemCopyDevToHost(data_ptr, m_ulAudioRecBufStart, (cur_buf_to_get_size - tmp_size));
        
            m_usAudioRecReadPtr = cur_buf_to_get_size - tmp_size;
        }   
    }   
    
    MMPD_AUDIO_SetRecReadPtr();
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_TransferAudioDataToHost
//------------------------------------------------------------------------------
/** 
    @brief  Transfer SBC Data From Firmware to Host(Memory Mode)
    @param[in] ubAudioPtr : audio data buffer start pointer
    @param[in] ulMaxSize  : max data size to transfer
    @param[in] ulFrameSize  : frame size
    @param[out] *ulReturnSize : actual transfer data size    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_TransferAudioDataToHost(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, MMP_ULONG ulFrameSize, MMP_ULONG *ulReturnSize)
{
    MMP_USHORT  cur_buf_to_get_size;
    MMP_USHORT  tmp_size;
    MMP_UBYTE   *data_ptr;
    
    MMPD_AUDIO_UpdateRecWritePtr();

    data_ptr = (MMP_UBYTE *)ubAudioPtr;
   
    *ulReturnSize = 0;
    
    if (m_usAudioRecWritePtr == m_usAudioRecReadPtr) {
        if (m_usAudioRecWritePtrHigh == m_usAudioRecReadPtrHigh) { 
            return MMP_AUDIO_ERR_STREAM_BUF_EMPTY;  
        }
    }

    if (m_usAudioRecWritePtr > m_usAudioRecReadPtr) 
        cur_buf_to_get_size = m_usAudioRecWritePtr - m_usAudioRecReadPtr;   
    else 
        cur_buf_to_get_size = m_ulAudioRecBufSize - (m_usAudioRecReadPtr - m_usAudioRecWritePtr);   
    
    if (cur_buf_to_get_size < ulFrameSize) {
        return MMP_AUDIO_ERR_STREAM_UNDERFLOW;
    }
        
    if (cur_buf_to_get_size > ulMaxSize) {
        cur_buf_to_get_size = ulMaxSize;
    }

    cur_buf_to_get_size = (cur_buf_to_get_size / ulFrameSize) * ulFrameSize;
            
    *ulReturnSize = cur_buf_to_get_size;
        
    tmp_size = m_ulAudioRecBufSize - m_usAudioRecReadPtr;

    if (tmp_size > cur_buf_to_get_size) {
        tmp_size = cur_buf_to_get_size;
        
        MMPH_HIF_MemCopyDevToHost(data_ptr, (m_usAudioRecReadPtr + m_ulAudioRecBufStart), tmp_size);
    
        m_usAudioRecReadPtr += tmp_size;
    }
    else {
        MMPH_HIF_MemCopyDevToHost(data_ptr, (m_usAudioRecReadPtr + m_ulAudioRecBufStart), tmp_size);
    
        data_ptr += tmp_size;
        m_usAudioRecReadPtr = 0;
        m_usAudioRecReadPtrHigh += 1;
        
        MMPH_HIF_MemCopyDevToHost(data_ptr, m_ulAudioRecBufStart, (cur_buf_to_get_size - tmp_size));
    
        m_usAudioRecReadPtr = cur_buf_to_get_size - tmp_size;
    }   

    MMPD_AUDIO_SetRecReadPtr();
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_TransferDataToAIT
//------------------------------------------------------------------------------
/** 
    @brief  Transfer Audio Data From Host to Firmware(Memory Mode)
    @param[in] ubAudioPtr : audio data start pointer
    @param[in] ulMaxSize  : max data size to transfer
    @param[out] ulReturnSize : actual transfer data size    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_TransferDataToAIT(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, MMP_ULONG *ulReturnSize)
{
    MMP_ULONG   cur_buf_to_put_size;
    MMP_ULONG   tmp_size;
    MMP_UBYTE   *data_ptr;

    *ulReturnSize = 0;

    data_ptr = (MMP_UBYTE *)ubAudioPtr;

    MMPD_AUDIO_UpdatePlayReadPtr();
    
    if (m_ulAudioPlayReadPtr == m_ulAudioPlayWritePtr) {
    
        if (m_ulAudioPlayReadPtrHigh == m_ulAudioPlayWritePtrHigh) {
            MMPD_AUDIO_UpdatePlayReadPtr();
            if (m_ulAudioPlayReadPtr == m_ulAudioPlayWritePtr) {
                cur_buf_to_put_size = m_ulAudioPlayBufSize;
            }   
            else {
                return MMP_AUDIO_ERR_STREAM_BUF_FULL;   
            }
        }   
        else {
            if ((m_ulAudioPlayWritePtrHigh - m_ulAudioPlayReadPtrHigh) != 1) {
                return  MMP_AUDIO_ERR_STREAM_UNDERFLOW; 
            }
            else {
                *ulReturnSize = 0;
                return MMP_AUDIO_ERR_STREAM_BUF_FULL;   
            }   
        }       
    }
    else {
        if (m_ulAudioPlayReadPtr > m_ulAudioPlayWritePtr) 
            cur_buf_to_put_size = m_ulAudioPlayReadPtr - m_ulAudioPlayWritePtr; 
        else 
            cur_buf_to_put_size = m_ulAudioPlayBufSize - (m_ulAudioPlayWritePtr - m_ulAudioPlayReadPtr);    
    }   
    
    if (cur_buf_to_put_size > ulMaxSize)
        cur_buf_to_put_size = ulMaxSize;
        
    if (cur_buf_to_put_size > m_ulAudioPlayRemainFileSize)
        cur_buf_to_put_size = m_ulAudioPlayRemainFileSize;

    *ulReturnSize = cur_buf_to_put_size;
        
    tmp_size = m_ulAudioPlayBufSize - m_ulAudioPlayWritePtr;
    
    if (tmp_size > cur_buf_to_put_size) {
        tmp_size = cur_buf_to_put_size;

        MMPH_HIF_MemCopyHostToDev((m_ulAudioPlayWritePtr + m_ulAudioPlayBufStart), data_ptr, tmp_size);
        data_ptr += tmp_size;       
            
        m_ulAudioPlayWritePtr += tmp_size;
    }
    else {

        MMPH_HIF_MemCopyHostToDev((m_ulAudioPlayWritePtr + m_ulAudioPlayBufStart), data_ptr, tmp_size);
        
        data_ptr += tmp_size;       
    
        m_ulAudioPlayWritePtr = 0;
        m_ulAudioPlayWritePtrHigh += 1;

        MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayBufStart, data_ptr, (cur_buf_to_put_size - tmp_size));
        data_ptr += (cur_buf_to_put_size - tmp_size);       
            
        m_ulAudioPlayWritePtr = cur_buf_to_put_size - tmp_size;
    }
    
    MMPD_AUDIO_UpdatePlayWritePtr();
    
    m_ulAudioPlayRemainFileSize -= cur_buf_to_put_size;
    
    if (m_ulAudioPlayRemainFileSize) {
        return MMP_ERR_NONE;
    } 
    else {
        return MMP_AUDIO_ERR_END_OF_FILE;
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_TransferMIDIDataToAIT
//------------------------------------------------------------------------------
/** 
    @brief  Transfer MIDI Data From Host to Firmware(Memory Mode)
    @param[in] ubAudioPtr : audio data start pointer
    @param[in] ulFileSize  : file size to transfer
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_TransferMIDIDataToAIT(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulFileSize)
{
    MMPH_HIF_MemCopyHostToDev(m_ulAudioPlayBufStart, ubAudioPtr, ulFileSize);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetMemModeFileHostInfo
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_SetMemModeFileHostInfo(void *AudioPlayFileHandle, MMP_ULONG ulAudioPlayFileSize)
{
    m_AudioPlayFileHandle = AudioPlayFileHandle;
    m_ulAudioPlayFileSize = ulAudioPlayFileSize;

    return MMP_ERR_NONE;
}

#if 0
void ____SBC_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetSBCEncodeEnable
//------------------------------------------------------------------------------
/** 
    @brief  Enable or Disable SBC Encode
    @param[in] bEnable : enable or  disable
    @param[in] IntPeriod : transfer INT period
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetSBCEncodeEnable(MMP_BOOL bEnable, MMP_ULONG ulIntPeriod)
{
    m_bSBCEnable = bEnable;

    if (bEnable) {
        // NOP
    }
    else {
        m_ulSBCSampleRate       = 0;
        m_ulSBCFrameSize        = 0;
        m_ulSBCFrameCount       = 0;
        m_ulSBCSamplesPerFrame  = 0;
        m_ulSBCChannelNum       = 0;
    }
    
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, bEnable);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulIntPeriod);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | SET_SBC_ENCODE_ENABLE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetSBCEncodeEnable
//------------------------------------------------------------------------------
/** 
    @brief  Get SBC is encoded or disabled
    @param[out] bEnable : enable or  disable
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_GetSBCEncodeEnable(MMP_BOOL *bEnable)
{
    *bEnable = m_bSBCEnable;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_GetSBCInfo
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIO_GetSBCInfo(  MMP_ULONG *ulOutSampleRate, 
                                MMP_ULONG *ulOutBitRate,
                                MMP_ULONG *ulOutFrameSize,
                                MMP_ULONG *ulSBCFrameCount,
                                MMP_ULONG *ulSBCSamplesPerFrame,
                                MMP_ULONG *ulSBCChannelNum,
                                MMP_ULONG *ulSBCBitpool)
{
    if (m_bSBCEnable) {

        MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | GET_SBC_INFO);
      
        m_ulSBCSampleRate       = *ulOutSampleRate      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        m_ulSBCFrameSize        = *ulOutFrameSize       = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 4);
        m_ulSBCFrameCount       = *ulSBCFrameCount      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 8);
        m_ulSBCSamplesPerFrame  = *ulSBCSamplesPerFrame = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 12);
        m_ulSBCChannelNum       = *ulSBCChannelNum      = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 16);
                                  *ulOutBitRate         = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 20);
        
        MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | GET_SBC_BITPOOL);
        *ulSBCBitpool = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
        MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    }
    else {
        *ulOutSampleRate      = 0;
        *ulOutFrameSize       = 0;
        *ulSBCFrameCount      = 0;
        *ulSBCSamplesPerFrame = 0;
        *ulSBCChannelNum      = 0;
        *ulSBCBitpool         = 0;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetSBCChannelMode
//------------------------------------------------------------------------------
/** 
    @brief  Set SBC Channel Mode
    @param[in] usMode : channel mode
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetSBCChannelMode(MMP_USHORT usMode)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usMode);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | SET_SBC_CHANNEL_MODE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetSBCAllocMethod
//------------------------------------------------------------------------------
/** 
    @brief  Set SBC Alloc Method
    @param[in] usMethod : alloc method
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetSBCAllocMethod(MMP_USHORT usMethod)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usMethod);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | SET_SBC_ALLOC_METHOD);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetSBCNrofBlocks
//------------------------------------------------------------------------------
/** 
    @brief  Set SBC Number of Blocks
    @param[in] usBlocks : number of blocks
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetSBCNrofBlocks(MMP_USHORT usBlocks)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usBlocks);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | SET_SBC_NROF_BLOCKS);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetSBCNrofSubbands
//------------------------------------------------------------------------------
/** 
    @brief  Set SBC Number of Subbands
    @param[in] usSubBands : number of subbands
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetSBCNrofSubbands(MMP_USHORT usSubBands)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usSubBands);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | SET_SBC_NROF_SUBBANDS);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetSBCBitrate
//------------------------------------------------------------------------------
/** 
    @brief  Set SBC Encode Bitrate
    @param[in] usBitRate : bitrate
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetSBCBitrate(MMP_USHORT usBitRate)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usBitRate);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | SET_SBC_BITRATE);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetSBCBitPool
//------------------------------------------------------------------------------
/** 
    @brief  Set SBC bitpool size
    @param[in] usBitPool : bit pool size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetSBCBitPool(MMP_USHORT usBitPool)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usBitPool);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_SBC_ENCODE | SET_SBC_BITPOOL);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

#if 0
void ____I2S_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SWorkMode
//------------------------------------------------------------------------------
/**
    @brief  Set I2S working mode
    @param[in]  workingMode AIT acts as master or slave.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SWorkMode(MMP_UBYTE ch, MMP_I2S_WORK_MODE workingMode)
{
    MMPF_I2S_SetWorkMode(ch, workingMode);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SMclkMode
//------------------------------------------------------------------------------
/**
    @brief  Set I2S Mclk mode
    @param[in]  mclkMode output Mclk in N*fs mode or USB mode.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SMclkMode(MMP_UBYTE ch, MMP_I2S_MCLK_MODE mclkMode)
{
    MMPF_I2S_SetI2SMclkMode(ch, mclkMode);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SOutBitSize
//------------------------------------------------------------------------------
/**
    @brief  Set I2S output data bit width
    @param[in]  outputBitSize output data bit width.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SOutBitWidth(MMP_UBYTE ch, MMP_I2S_OUT_BITS outputBitSize)
{
    MMPF_I2S_SetOutBitWidth(ch, outputBitSize);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SLRckPolarity
//------------------------------------------------------------------------------
/**
    @brief  Set I2S LRCK ploarity
    @param[in]  lrckPolarity LRCK polarity.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SLRckPolarity(MMP_UBYTE ch, MMP_I2S_WS_POLARITY lrckPolarity)
{
    MMPF_I2S_SetLRckPolarity(ch, lrckPolarity);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SOutDataDelayMode
//------------------------------------------------------------------------------
/**
    @brief  Set I2S output data delay mode
    @param[in]  outDataDelayMode output data delay mode.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SOutDataDelayMode(MMP_UBYTE ch, MMP_I2S_DELAY_MODE outDataDelayMode)
{
    MMPF_I2S_SetOutDataDelayMode(ch, outDataDelayMode);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SOutBySDI
//------------------------------------------------------------------------------
/**
    @brief  Set I2S output data SDI pad or SDO pad
    @param[in]  bOutputBySDI set MMP_TRUE to output data by SDI pad, otherwise, by SDO pad.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SOutBySDI(MMP_UBYTE ch, MMP_BOOL bOutputBySDI)
{
    MMPF_I2S_SetOutBySDI(ch, bOutputBySDI);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SInFromSDO
//------------------------------------------------------------------------------
/**
    @brief  Set I2S receive input data from SDO pad or SDI pad
    @param[in]  bInputFromSDO set MMP_TRUE to receive in data from SDO pad, otherwise, from SDI pad.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SInFromSDO(MMP_UBYTE ch, MMP_BOOL bInputFromSDO)
{
    MMPF_I2S_SetInFromSDO(ch, bInputFromSDO);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SInBitAlign
//------------------------------------------------------------------------------
/**
    @brief  Set I2S input data bypass bit before starting fetch.
    @param[in]  bOutputBySDI set the bypass bit before start fetch data.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SInBitAlign(MMP_UBYTE ch, MMP_UBYTE ubInBitAlign)
{
    MMPF_I2S_SetInBitAlign(ch, ubInBitAlign);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SOutBitAlign
//------------------------------------------------------------------------------
/**
    @brief  Set the number of 0's in front of PCM for alignment
    @param[in]  ubOutBitAlign set the number of 0's in front of PCM for alignment
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SOutBitAlign(MMP_UBYTE ch, MMP_UBYTE ubOutBitAlign)
{
    MMPF_I2S_SetOutBitAlign(ch, ubOutBitAlign);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetI2SMclkFreq
//------------------------------------------------------------------------------
/**
    @brief  Set I2S Mclk output frequency
    @param[in]  mclkMode set Mclk as N*fs mode or USB mode.
    @param[in]  ulSamplerate for N*fs mode only, in unit of Hz (ex.44100, 48000)
    @param[in]  ulFixedMclkFreq for USB mode only, in unit of KHz (ex. 12000)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetI2SMclkFreq(MMP_UBYTE ch, MMP_I2S_MCLK_MODE mclkMode, MMP_ULONG ulSamplerate, MMP_ULONG ulFixedMclkFreq)
{
    if ((mclkMode <= MMP_I2S_MCLK_MODE_NONE) ||
        (mclkMode >= MMP_I2S_MAX_MCLK_MODE)) {
        return MMP_AUDIO_ERR_PARAMETER;
    }

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, mclkMode);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulSamplerate);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, ulFixedMclkFreq);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 12, ch);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_I2S_CONFIG | SET_MCLK_FREQ);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_EnableI2SMclk
//------------------------------------------------------------------------------
/**
    @brief  Enable or disable I2S Mclk output
    @param[in]  mclkMode set Mclk as N*fs mode or USB mode.
    @param[in]  bEnable set MMP_TRUE to enable Mclk output and MMP_FALSE to disable it.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_EnableI2SMclk(MMP_UBYTE ch, MMP_I2S_WORK_MODE workMode, MMP_I2S_MCLK_MODE mclkMode, MMP_BOOL bEnable)
{
    if (bEnable) {
        MMPF_I2S_EnableMclk(ch, workMode, bEnable);
    }
    else {
        MMPF_I2S_EnableMclk(ch, workMode, bEnable);
    }
    return MMP_ERR_NONE;
}

#if 0
void ____Play_Effect_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetEQType
//------------------------------------------------------------------------------
/** 
    @brief  Set Audio Play EQ Type
    @param[in] usType : eq type
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetEQType(MMP_USHORT usType, void* argHandler)
{
    MMP_ERR mmpstatus;
    
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, (MMP_ULONG)argHandler);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AUDIO_EQ | usType);
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return mmpstatus; 
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetGraphicEQEnable
//------------------------------------------------------------------------------
/**
    @brief  Enable or disable graphic EQ
    @param[in]  ubEnable    : Enable or disable graphic EQ
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetGraphicEQEnable(MMP_BOOL bEnable)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, bEnable);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AUDIO_EQ | AUDIO_GRAPHIC_EQ);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetGraphicEQBand
//------------------------------------------------------------------------------
/**
    @brief  Adjust one band parameter of EQ filter
    @param[in]  usFreq    : Center frequency index
    @param[in]  usQrange  : Q range for selected frequency band
    @param[in]  usGain    : Gain of selected frequency band
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetGraphicEQBand(MMP_USHORT usFreq, MMP_USHORT usQrange, MMP_USHORT usGain)
{
    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 0, usFreq);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 2, usQrange);
    MMPH_HIF_SetParameterW(GRP_IDX_AUD, 4, usGain);
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AUDIO_EQ | AUDIO_ADJUST_EQ_BAND);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetForeignEffectEnable
//------------------------------------------------------------------------------
/**
    @brief  Enable or disable customer's privately sound effect
    @param[in]  ubEnable    : Enable or disable foreign sound effect
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetForeignEffectEnable(MMP_BOOL bEnable)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, bEnable);

    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AUDIO_EQ | SET_FOREIGN_EQ);
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetForeignEffectType
//------------------------------------------------------------------------------
/**
    @brief  Adjust customer's privately sound effect type
    @param[in]  ulParam1    : The first parameter for adjust effect type
    @param[in]  ulParam2    : The second parameter for adjust effect type
    @param[in]  ulParam3    : The third parameter for adjust effect type
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_AUDIO_SetForeignEffectType(MMP_ULONG ulParam1, MMP_ULONG ulParam2, MMP_ULONG ulParam3)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 0, ulParam1);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 4, ulParam2);
    MMPH_HIF_SetParameterL(GRP_IDX_AUD, 8, ulParam3);
    
    MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_AUDIO_EQ | ADJUST_FOREIGN_EQ);
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_AUD, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return mmpstatus;
}

#if 0
void ____Record_Effect_Function____(){ruturn;} //dummy
#endif

#if (WNR_EN)
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_ConfigWNR
//------------------------------------------------------------------------------
/**
    @brief  Configure wind noise reduction algorithm
    @param[in] cfg : configurations for wind noise reduction
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPD_AUDIO_ConfigWNR(MMP_AUDIO_WNR_CFG *cfg)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, cfg->bEnWNR);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 1, cfg->bEnNR);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_REC_EFFECT | CFG_WNR);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetWNREnable
//------------------------------------------------------------------------------
/**
    @brief  Enable or disable wind noise reduction operation
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPD_AUDIO_SetWNREnable(MMP_BOOL bEnable)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, bEnable);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_REC_EFFECT | SET_WNR_EN);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return mmpstatus;
}
#endif

#if (AGC_SUPPORT)
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIO_SetAGCEnable
//------------------------------------------------------------------------------
/**
    @brief  Enable or disable auto gain control (AGC) operation
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPD_AUDIO_SetAGCEnable(MMP_BOOL bEnable)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_AUD, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_AUD, 0, bEnable);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_AUD, HIF_AUD_CMD_REC_EFFECT | SET_AGC_EN);
    MMPH_HIF_ReleaseSem(GRP_IDX_AUD);

    return mmpstatus;
}
#endif

/// @}
/// @end_ait_only
