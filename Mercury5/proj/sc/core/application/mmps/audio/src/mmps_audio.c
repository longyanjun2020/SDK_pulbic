//==============================================================================
//
//  File        : mmps_audio.c
//  Description : Audio User Application Interface
//  Author      : Hans Liu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_audio.c
 *  @brief The Audio playback/record control functions
 *  @author Hans Liu
 *  @version 1.0
 */

#include "mmp_lib.h"
#include "mmpd_audiodb.h"
#include "mmps_audio.h"
#include "mmpd_audio.h"
#include "mmph_hif.h"
#include "mmpd_system.h"
//#include "ait_utility.h" //recover later pohan
#include "mmpd_audioparser.h"
#if (OMA_DRM_EN == 1)
#include "mmpd_omadrm.h"
#endif

#include "mmps_fs.h" //For MMPS_FS_SEEK_SET

/** @addtogroup MMPS_AUDIO
@{
*/
//#define MMPS_FS_SEEK_SET 0 //remove later pohan chen
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

#define     SBC_SLOT_NUM            8
/**@brief The audio function card mode memory mode status.

Use @ref MMPS_AUDIO_SetMediaPath to change it state.
*/
static  MMPS_AUDIO_MEDIA_PATH   m_audioPath;

/// Audio in path
static MMPS_AUDIO_IN_PATH   m_audioInPath;
/// Audio out path
static MMPS_AUDIO_OUT_PATH  m_audioOutPath;

/// Audio Memory Allocation Information
static MMPS_AUDIOMODE_CONFIG_INFO m_AudioBufInfo;

/// Audio I2S related settings
static MMPS_AUDIO_I2S_CFG   m_AudioI2SConfig[MMP_I2S_CH_NUM];

/// Music List File Id
#if (SUPPORT_MTP_FUNC == 1)
static MMP_ULONG       m_usMusicListFileId;
/// Music List Information
static MMPS_AUDIO_MUSICLIST_INFO    m_MusicListListInfo;
///unknown string
static MMP_USHORT  m_UnknownUniStr[]={0x0008,0x0075,0x006E,0x006B,0x006E,0x006F,0x0077,0x006E,0x0000};
#endif
/**@brief The audio function memory file mode ID.

Use @ref MMPS_AUDIO_InitializeMP3Play to change it state.
*/
static	void        *m_ulAudioPlayFileHandle = 0;

static  MMP_BYTE    m_bAudioPlayFileName[AUDIO_MAX_FILE_NAME_SIZE * 2];
static  MMP_USHORT  m_usAudioPlayFileNameLength;
static  MMP_ULONG   m_ulAudioPlayFileSize;
static  MMP_UBYTE   *m_ubAudioPlayBuf;
static  MMP_ULONG   m_ulAudioPlayBufSize;
static	MMP_ULONG	m_ulAudioMemEnd;
static	MMP_ULONG	m_ulAudioMemMapMode;
static  MMP_USHORT  m_AudioPlayVolume = 0;

//SBC
//static  MMP_ULONG   m_ulSBCBitRate;
static  MMP_UBYTE   *m_ucSBCBufStart;
static  MMP_UBYTE   *m_ucSBCBufRead, *m_ucSBCBufWrite;
static  MMP_ULONG   m_ulSBCBufSize;
static  MMP_ULONG   m_ulSBCSamplingRate;
static  MMP_ULONG   m_ulSBCFrameLen;
static  MMP_ULONG   m_ulSBCSamples;
static  MMP_ULONG   m_ulSBCChannels;
static  MMP_ULONG   m_ulSBCSizeSlot[SBC_SLOT_NUM];
static  MMP_ULONG   m_ulSBCSizeReadIdx;
static  MMP_ULONG   m_ulSBCSizeWriteIdx;
static  MMP_ULONG   m_ulSBCSizeNum;
static  MMP_ULONG   m_ulSBCSlotSize;
static  MMP_ULONG   m_ulSBCConsumedData;
static  MMP_ULONG   m_ulSBCStartTime;
static  MMP_ULONG   m_ulSBCMaxTransSize;

//Wave
#define     WAV_SLOT_NUM            8
#define     MAX_WAV_OUTPUT_SIZE     10 * 1024
#define     MAX_WAV_TRANSFER_SIZE   10 * 1024

static  MMP_UBYTE   *m_ucWAVBufStart;
static  MMP_UBYTE   *m_ucWAVBufRead, *m_ucWAVBufWrite;
static  MMP_ULONG   m_ulWAVBufStart;
static  MMP_ULONG   m_ulWAVBufSize;
static  MMP_ULONG	m_ulWAVSampleCount;
static  MMP_ULONG   m_ulWAVSizeSlot[WAV_SLOT_NUM];
static  MMP_ULONG   m_ulWAVSizeReadIdx;
static  MMP_ULONG   m_ulWAVSizeWriteIdx;
static  MMP_ULONG   m_ulWAVSizeNum;
static  MMP_ULONG   m_ulWAVSlotSize;
static  MMP_ULONG	m_ulWAVSampleRate;
static  MMP_ULONG	m_ulWAVChans;
static	MMP_ULONG	m_ulWAVConsumedData;
static	MMP_ULONG	m_ulWAVStartTime;
static  MMP_LONG    m_lMP3TagSize;

static  MMP_AUDIO_MP3_INFO      *m_Mp3Info;
static  MMP_AUDIO_AACPLUS_INFO  *m_AacplusInfo;
static  MMP_AUDIO_OGG_INFO      *m_OggInfo;
static  MMP_AUDIO_RA_INFO       *m_RaInfo;
static  MMP_AUDIO_WMA_INFO      *m_WMAproInfo;
static  MMP_AUDIO_FLAC_INFO     *m_FLACInfo;
static  MMP_AUDIO_WAV_INFO      *m_WavInfo;
static  MMP_AUDIO_MIDI_INFO     *m_MIDIInfo;
static  MMP_AUDIO_AMR_INFO      *m_AmrInfo;
static  void*                   m_pAudioCBFunc;
static  void*                   m_pAudioCBContext;

    
#if (AUDIO_HOST_DB_EN == 1)    
//++ for the database
static	MMP_UBYTE	m_ubDBFileName[50];
static	MMP_ULONG	m_ulDBFileNameSize;
static  MMPS_AUDIO_DB_SORT_TYPE	m_sortType = MMPS_AUDIO_DB_SORT_MAX;   
static	MMPD_AUDIODB_BTNODE *m_treeRoot;
static	MMPD_AUDIODB_BFNODE *m_forestRoot;
static  MMP_ULONG	m_ulTreeNodeCount, m_ulForestNodeCount; 
static	MMPS_AUDIO_DB_TRACK* m_trackEntry;
static  MMPS_AUDIO_DB_ENTRY* m_dbEntry;

static	MMP_UBYTE	m_ubFilterString[AUDIODB_MAX_FILE_NAME_SIZE*2];
static	MMP_ULONG	m_ulFilterStringLength;

static	MMP_ULONG   m_ulFilterStart, m_ulFilterEnd;
static	MMP_ULONG	m_ulFilterCurrentCount;

static MMP_ULONG    m_ulOpenedDirID[10];
static MMP_ULONG	m_ulDepth;
static MMP_BYTE     m_bLastDirName[AUDIO_MAX_FILE_NAME_SIZE*3];

static MMP_BOOL		m_bDatabaseDirty = MMP_FALSE;
//-- for the database
#endif
static MMP_BOOL     m_bMP3GetInfoStage = MMP_FALSE;

//TBD
#if (MP3HD_DEC_EN == 1)
static MMP_UBYTE    ubMp3ID3CacheBuf[0x200];
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_Audio_GetConfig
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Get Audio Configuration Structure
    @return m_AudioBufInfo
*/
MMPS_AUDIOMODE_CONFIG_INFO *MMPS_Audio_GetConfig(void)
{
    return &m_AudioBufInfo;
}

/// @ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PreDACPowerOn
//------------------------------------------------------------------------------
/**
    @brief  Fast charge capacitor for reduce DAC power on delay
*/
MMP_ERR MMPS_AUDIO_PreDACPowerOn(MMP_ULONG ulSampleRate)
{
    return MMPD_AUDIO_PreDACPowerOn(ulSampleRate);
}
/// @end_ait_only

//------------------------------------------------------------------------------
//  Function    : MMPS_Audio_GetDACPowerOnStatus
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPS_Audio_GetDACPowerOnStatus(void)
{   
    return MMPD_AUDIO_GetDACPowerOnStatus();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Audio_GetADCPowerOnStatus
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPS_Audio_GetADCPowerOnStatus(void)
{   
    return MMPD_AUDIO_GetADCPowerOnStatus();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitialInPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Initialize Audio In Path
    @param[in] audioinpath specific audio input path
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitialInPath(MMPS_AUDIO_IN_PATH audioinpath)
{
    m_audioInPath = audioinpath;
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetLineInChannel
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set Line In Channel
    @param[in] lineinchannel specific linein channel (Dual/R/L)
        -   MMPS_AUDIO_LINEIN_DUAL  : LIP/RIP
        -   MMPS_AUDIO_LINEIN_R     : RIP
        -   MMPS_AUDIO_LINEIN_L     : LIP
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_SetLineInChannel(MMPS_AUDIO_LINEIN_CHANNEL lineinchannel)
{
    return MMPD_AUDIO_SetLineInChannel((MMP_AUD_LINEIN_CH)lineinchannel);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitialOutPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Initialize Audio Out Path
    @param[in] audiooutpath specific audio output path
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitialOutPath(MMPS_AUDIO_OUT_PATH audiooutpath)
{
    m_audioOutPath = audiooutpath;
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetInPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Get Audio In Path
    @return audio in path
        - MMPS_AUDIO_IN_I2S0            I2S channel 0
        - MMPS_AUDIO_IN_I2S1            I2S channel 1 (Vision V5 only)
        - MMPS_AUDIO_IN_AFE_SING        (AUXL/AUXR)
        - MMPS_AUDIO_IN_AFE_DIFF        (LIP/LIN/RIP/RIN)
        - MMPS_AUDIO_IN_AFE_DIFF2SING   (LIP/RIP)
    @pre Audio in path has beed set either by @ref MMPS_AUDIO_InitialInPath or 
         @ref MMPS_AUDIO_SetInPath
*/
MMPS_AUDIO_IN_PATH MMPS_AUDIO_GetInPath(void)
{
    return m_audioInPath;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetOutPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Get Audio Out Path
    @return audio out path
        - MMPS_AUDIO_OUT_I2S0           I2S channel 0
        - MMPS_AUDIO_OUT_I2S1           I2S channel 1 (Vision V5 only)
        - MMPS_AUDIO_OUT_AFE_HP         (LOUT/ROUT)
        - MMPS_AUDIO_OUT_AFE_HP_INVT    (LOUT/ROUT)
        - MMPS_AUDIO_OUT_AFE_LINE       (LOUT2/ROUT2)
        - MMPS_AUDIO_OUT_AFE_LINE_INVT  (LOUT2/ROUT2)
    @pre Audio out path has beed set either by @ref MMPS_AUDIO_InitialOutPath or 
         @ref MMPS_AUDIO_SetOutPath
*/
MMPS_AUDIO_OUT_PATH MMPS_AUDIO_GetOutPath(void)
{
    return m_audioOutPath;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetInPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set Audio In Path
    @param[in] audiopath specific audio input path
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: If input path is the same as current setting, do nothing.
    @pre 2: If recording status is in recording state, pause recording before change input path.
    @Post If recording was paused for changing input path, resume recording after changed.
*/
MMP_ERR MMPS_AUDIO_SetInPath(MMPS_AUDIO_IN_PATH audiopath)
{
    MMP_ERR status = MMP_ERR_NONE;

    if (m_audioInPath != audiopath) {
        status = MMPD_AUDIO_SetInPath(audiopath);
        m_audioInPath = audiopath;
    }
    return status;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetOutPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Out Path
    @param[in] audiopath specific audio output path
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: If output path is the same as current setting, do nothing.
    @pre 2: If playback status is in playing state, pause playback before change out path.
    @pre 3: playback volume has been set by @ref MMPS_AUDIO_SetPlayVolume previously.
    @Post If playback was paused for changing output path, resume playback after changed.
*/
MMP_ERR MMPS_AUDIO_SetOutPath(MMPS_AUDIO_OUT_PATH audiopath)
{
    MMP_ERR     status = MMP_ERR_NONE;
	MMP_USHORT  usLevel = 0;

    if (m_audioOutPath != audiopath) {
        status = MMPD_AUDIO_SetOutPath(audiopath);
        if (status != MMP_ERR_NONE)
            return status;

        m_audioOutPath = audiopath;

		status = MMPS_AUDIO_GetPlayVolume(&usLevel);
        if (status != MMP_ERR_NONE)
            return status;
		status = MMPS_AUDIO_SetPlayVolume(usLevel, MMP_FALSE);
    }
    return status;
}

#if 0
void __AUDIO_I2S_CTL__(){}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeI2SConfig
//------------------------------------------------------------------------------
/**
    @brief  Initialize I2S related settings
    @param[in] I2SConfig : specified I2S configuration
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_InitializeI2SConfig(MMP_UBYTE ch, MMPS_AUDIO_I2S_CFG *I2SConfig)
{
    MMP_ERR err = MMP_ERR_NONE;

    if (ch >= MMP_I2S_CH_NUM) {
        return MMP_AUDIO_ERR_PARAMETER;
    }
    
    if ((I2SConfig->workingMode > MMP_I2S_WORK_MODE_NONE) &&
        (I2SConfig->workingMode < MMP_I2S_MAX_WORK_MODE)) {
        m_AudioI2SConfig[ch].workingMode = I2SConfig->workingMode;
    }
    else {
        err = MMP_AUDIO_ERR_PARAMETER;
        m_AudioI2SConfig[ch].workingMode = MMP_I2S_MASTER_MODE;
    }
    if ((I2SConfig->mclkMode > MMP_I2S_MCLK_MODE_NONE) &&
        (I2SConfig->mclkMode < MMP_I2S_MAX_MCLK_MODE)) {
        m_AudioI2SConfig[ch].mclkMode = I2SConfig->mclkMode;
    }
    else {
        err = MMP_AUDIO_ERR_PARAMETER;
        m_AudioI2SConfig[ch].mclkMode = MMP_I2S_256FS_MODE;
    }
    if ((I2SConfig->outputBitSize > MMP_I2S_OUT_BITS_NONE) &&
        (I2SConfig->outputBitSize < MMP_I2S_MAX_OUT_BIT_MODE)) {
        m_AudioI2SConfig[ch].outputBitSize = I2SConfig->outputBitSize;
    }
    else {
        err = MMP_AUDIO_ERR_PARAMETER;
        m_AudioI2SConfig[ch].outputBitSize = MMP_I2S_OUT_16BIT;
    }

    if ((I2SConfig->lrckPolarity > MMP_I2S_LRCK_POLARITY_NONE) &&
        (I2SConfig->lrckPolarity < MMP_I2S_MAX_WS_POLARITY)) {
        m_AudioI2SConfig[ch].lrckPolarity = I2SConfig->lrckPolarity;
    }
    else {
        err = MMP_AUDIO_ERR_PARAMETER;
        m_AudioI2SConfig[ch].lrckPolarity = MMP_I2S_LRCK_L_LOW;
    }
    if ((I2SConfig->outDataDelayMode > MMP_I2S_OUT_DELAY_NONE) &&
        (I2SConfig->outDataDelayMode < MMP_I2S_MAX_OUT_DELAY_MODE)) {
        m_AudioI2SConfig[ch].outDataDelayMode = I2SConfig->outDataDelayMode;
    }
    else {
        err = MMP_AUDIO_ERR_PARAMETER;
        if (m_AudioI2SConfig[ch].workingMode == MMP_I2S_MASTER_MODE)
            m_AudioI2SConfig[ch].outDataDelayMode = MMP_I2S_OUT_DELAY_STD;
        else
            m_AudioI2SConfig[ch].outDataDelayMode = MMP_I2S_OUT_DELAY_I2S;
    }
    m_AudioI2SConfig[ch].bOutputBySDI   = I2SConfig->bOutputBySDI;
    m_AudioI2SConfig[ch].bInputFromSDO  = I2SConfig->bInputFromSDO;
    m_AudioI2SConfig[ch].ubInBitAlign   = I2SConfig->ubInBitAlign;
    m_AudioI2SConfig[ch].ubOutBitAlign  = I2SConfig->ubOutBitAlign;

    MMPD_AUDIO_SetI2SWorkMode(ch, m_AudioI2SConfig[ch].workingMode);
    MMPD_AUDIO_SetI2SMclkMode(ch, m_AudioI2SConfig[ch].mclkMode);
    MMPD_AUDIO_SetI2SOutBitWidth(ch, m_AudioI2SConfig[ch].outputBitSize);
    MMPD_AUDIO_SetI2SLRckPolarity(ch, m_AudioI2SConfig[ch].lrckPolarity);
    MMPD_AUDIO_SetI2SOutDataDelayMode(ch, m_AudioI2SConfig[ch].outDataDelayMode);
    MMPD_AUDIO_SetI2SOutBySDI(ch, m_AudioI2SConfig[ch].bOutputBySDI);
    MMPD_AUDIO_SetI2SInFromSDO(ch, m_AudioI2SConfig[ch].bInputFromSDO);
    MMPD_AUDIO_SetI2SInBitAlign(ch, m_AudioI2SConfig[ch].ubInBitAlign);
    MMPD_AUDIO_SetI2SOutBitAlign(ch, m_AudioI2SConfig[ch].ubOutBitAlign);

    return err;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnableI2SMclk
//------------------------------------------------------------------------------
/**
    @brief  Control I2S Mclk output enable/disable
    @param[in] bEnable : Enable/disable Mclk output
    @param[in] ulSamplerate : For N*fs mode only, in unit of Hz (ex.44.1K => 44100)
    @param[in] ulFixedMclkFreq : For USB mode only, in unit of KHz (ex. 12M => 12000)
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre I2S related settings are well configured by @ref MMPS_AUDIO_InitializeI2SConfig.
*/
MMP_ERR MMPS_AUDIO_EnableI2SMclk(MMP_UBYTE ch, MMP_BOOL bEnable, MMP_ULONG ulSamplerate, MMP_ULONG ulFixedMclkFreq)
{
    MMP_ERR err = MMP_ERR_NONE;

    if (ch >= MMP_I2S_CH_NUM) {
        return MMP_AUDIO_ERR_PARAMETER;
	}

    if (bEnable) {
        //set I2S Mclk freqency only when enable Mclk output
        err = MMPD_AUDIO_SetI2SMclkFreq(ch, m_AudioI2SConfig[ch].mclkMode, ulSamplerate, ulFixedMclkFreq);
    }
    if (err == MMP_ERR_NONE) {
        err = MMPD_AUDIO_EnableI2SMclk(ch, m_AudioI2SConfig[ch].workingMode, 
                                       m_AudioI2SConfig[ch].mclkMode, bEnable);
    }

    return err;
}
/// @ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Audio Mode Memory Allocation
    @param[in] ulMode : audio mode
    @param[in] usStartAddrMode : index for buffer start address, which depends on different codec implementation
    @return MMP_ERR_NONE
*/
static MMP_ERR MMPS_AUDIO_AllocateBuffer(MMP_ULONG ulMode)
{
    MMP_ULONG 	buf_start = 0, cur_buf, play_buf_size, parse_buf_size, tag_buf_size, rec_buf_size;

    m_ulAudioMemMapMode = ulMode;

    switch(ulMode) {
    case MMPS_AUDIO_MIDI_P_CARD_MODE:
    case MMPS_AUDIO_MIDI_P_MEM_MODE:

        MMPS_System_GetAudioFrameStart(0, &buf_start);
        cur_buf = buf_start;

        if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            play_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUDIO_SetPlayBuf(cur_buf, play_buf_size);
        }

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUDIO_SetPlayFileNameBuf(cur_buf);
        break;
    case MMPS_AUDIO_PCM_P_MEM_MODE:

        MMPS_System_GetAudioFrameStart(0, &buf_start);
        cur_buf = buf_start;

        if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            play_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUDIO_SetPlayBuf(cur_buf, play_buf_size);
        }

        cur_buf -= MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE;
        MMPD_AUDIO_SetPlayHandshakeBuf(cur_buf, MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE);
        break;
    case MMPS_AUDIO_WAV_P_CARD_MODE:
    case MMPS_AUDIO_WAV_P_MEM_MODE:
    case MMPS_AUDIO_AMR_P_CARD_MODE:
    case MMPS_AUDIO_AMR_P_MEM_MODE:

		MMPS_System_GetAudioFrameStart(0, &buf_start);
        cur_buf = buf_start;

        if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            play_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUDIO_SetPlayBuf(cur_buf, play_buf_size);
        }

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUDIO_SetPlayFileNameBuf(cur_buf);

        cur_buf -= MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE;
        MMPD_AUDIO_SetPlayHandshakeBuf(cur_buf, MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE);
        break;
	case MMPS_AUDIO_FLAC_P_CARD_MODE:
	case MMPS_AUDIO_FLAC_P_MEM_MODE:

		MMPS_System_GetAudioFrameStart(0, &buf_start);
		cur_buf = buf_start;

        if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            play_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUDIO_SetPlayBuf(cur_buf, play_buf_size);
        }

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUDIO_SetPlayFileNameBuf(cur_buf);

        cur_buf -= MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE;
        MMPD_AUDIO_SetPlayHandshakeBuf(cur_buf, MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE);		
	    break;
    case MMPS_AUDIO_AACPLUS_P_CARD_MODE:
    case MMPS_AUDIO_AACPLUS_P_MEM_MODE:
    case MMPS_AUDIO_MP3_P_MEM_MODE:
    case MMPS_AUDIO_RA_P_CARD_MODE:
    case MMPS_AUDIO_RA_P_MEM_MODE:

		MMPS_System_GetAudioFrameStart(0, &buf_start);
        cur_buf = buf_start;

        if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            play_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUDIO_SetPlayBuf(cur_buf, play_buf_size);
        }

        cur_buf -= MMPD_AUDIO_SPECTRUM_DATA_SIZE;
        MMPD_AUDIO_SetPlaySpectrumBuf(cur_buf, MMPD_AUDIO_SPECTRUM_DATA_SIZE);

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUDIO_SetPlayFileNameBuf(cur_buf);

        cur_buf -= MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE;
        MMPD_AUDIO_SetPlayHandshakeBuf(cur_buf, MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE);
        break;
    case MMPS_AUDIO_MP3_P_CARD_MODE:

        MMPS_System_GetAudioFrameStart(0, &buf_start);
        cur_buf = buf_start;
        if (m_bMP3GetInfoStage) { //parsing stage
            if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
                parse_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulParseBufSize;
                cur_buf -= parse_buf_size;
                MMPD_AUDIO_SetParseBuf(cur_buf, parse_buf_size);

                cur_buf -= MMPD_AUDIO_SPECTRUM_DATA_SIZE;   //reserved of spectrum
                cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;    //reserved of play file name
                MMPD_AUDIO_PresetPlayFileNameBuf(cur_buf);
                cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
                MMPD_AUDIO_SetParseFileNameBuf(cur_buf);
            }
        }
        else { //parsing done stage
            if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
                play_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulPlayBufSize;
                cur_buf -= play_buf_size;
                MMPD_AUDIO_SetPlayBuf(cur_buf, play_buf_size);
            }

            cur_buf -= MMPD_AUDIO_SPECTRUM_DATA_SIZE;
            MMPD_AUDIO_SetPlaySpectrumBuf(cur_buf, MMPD_AUDIO_SPECTRUM_DATA_SIZE);

            cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
            MMPD_AUDIO_PresetPlayFileNameBuf(cur_buf);
            cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
            MMPD_AUDIO_SetParseFileNameBuf(cur_buf);

            cur_buf -= MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE;
            MMPD_AUDIO_SetPlayHandshakeBuf(cur_buf, MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE);
        }
        break;
    case MMPS_AUDIO_WMA_P_CARD_MODE:
    case MMPS_AUDIO_WMA_P_MEM_MODE:
    case MMPS_AUDIO_OGG_P_CARD_MODE:
    case MMPS_AUDIO_OGG_P_MEM_MODE:

		MMPS_System_GetAudioFrameStart(0, &buf_start);
        cur_buf = buf_start;

        if (m_audioPath != MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            play_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulPlayBufSize;
            cur_buf -= play_buf_size;
            MMPD_AUDIO_SetPlayBuf(cur_buf, play_buf_size);
        }

        cur_buf -= MMPD_AUDIO_SPECTRUM_DATA_SIZE;
        MMPD_AUDIO_SetPlaySpectrumBuf(cur_buf, MMPD_AUDIO_SPECTRUM_DATA_SIZE);

        tag_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulTagBufSize;
        cur_buf -= tag_buf_size;
        MMPD_AUDIO_SetAudioTagBuf(cur_buf, tag_buf_size);

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUDIO_SetPlayFileNameBuf(cur_buf);

        cur_buf -= MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE;
        MMPD_AUDIO_SetPlayHandshakeBuf(cur_buf, MMPD_AUDIO_PLAY_HANDSHAKE_BUF_SIZE);
        break;
    case MMPS_AUDIO_AMR_R_CARD_MODE:
    case MMPS_AUDIO_AMR_R_MEM_MODE:
    case MMPS_AUDIO_AAC_R_CARD_MODE:
    case MMPS_AUDIO_AAC_R_MEM_MODE:
    case MMPS_AUDIO_MP3_R_CARD_MODE:
    case MMPS_AUDIO_MP3_R_MEM_MODE:
    case MMPS_AUDIO_WAV_R_CARD_MODE:

		MMPS_System_GetAudioFrameStart(0, &buf_start);
        cur_buf = buf_start;

        rec_buf_size = m_AudioBufInfo.AudioMode[ulMode].ulRecBufSize;
        cur_buf -= rec_buf_size;
        MMPD_AUDIO_SetEncodeBuf(cur_buf, rec_buf_size);

        cur_buf -= AUDIO_MAX_FILE_NAME_SIZE * 3;
        MMPD_AUDIO_SetEncodeFileNameBuf(cur_buf);

        cur_buf -= MMPD_AUDIO_REC_HANDSHAKE_BUF_SIZE;
        MMPD_AUDIO_SetRecHandshakeBuf(cur_buf, MMPD_AUDIO_REC_HANDSHAKE_BUF_SIZE);
        break;
    }

    PRINTF("Audio Alloc Buf Start:0x%X\r\n", buf_start);
    PRINTF("Audio Alloc Buf End:0x%X\r\n", cur_buf);
    if (cur_buf > buf_start) {
        PRINTF("Audio use 0x%X memory\r\n", (cur_buf - buf_start));
    }	
    else {
        PRINTF("Audio use 0x%X memory\r\n", (buf_start - cur_buf));
    }    	

    m_ulAudioMemEnd = cur_buf;

    return MMP_ERR_NONE;
}
/// @end_ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetMediaPath
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Get Media path
    @param[in] mediapath : media path
        -   MMPS_AUDIO_MEDIA_PATH_MEM: audio data is located at host memory
        -   MMPS_AUDIO_MEDIA_PATH_CARD: file is located at card
        -   MMPS_AUDIO_MEDIA_PATH_HOST_FILE: file is located at host storage
        -   MMPS_AUDIO_MEDIA_PATH_MMP_MEM: file is located at MMP stacked memory
    @return MMP_ERR_NONE

    @pre Media path must be set before playback initialization.
    @pre Do @b NOT use for host parser or meta data parser, it will impact playback.
*/
MMP_ERR MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH mediapath)
{
    m_audioPath = mediapath;
    return  MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetPlayStatus
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
MMP_ERR MMPS_AUDIO_GetPlayStatus(MMPS_AUDIO_PLAY_STATUS *status)
{
    MMP_ERR     mmpstatus = MMP_ERR_NONE;
    MMP_USHORT  play_status = MMPS_AUDIO_PLAY_INVALID;

    mmpstatus = MMPD_AUDIO_GetPlayStatus(&play_status);
    *status = play_status;

    return mmpstatus;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetDecOutBuf
//------------------------------------------------------------------------------
/**
    @brief  Get the buffer which store the decoded PCM samples
    @param[out] *ulBufAddr : Decoded PCM buffer address
    @param[out] *ulBufSize : Decoded PCM buffer size (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_GetDecOutBuf(MMP_ULONG *ulBufAddr, MMP_ULONG *ulBufSize)
{
    return MMPD_AUDIO_GetDecOutBuf(ulBufAddr, ulBufSize);
}

#if (GAPLESS_PLAY_EN == 1)
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ChkOperationAllowed
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Check if requested operation is allowed when gapless mode playback
    @param[out] bAllow : if requested operation is allowed or not
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_ChkOperationAllowed(MMP_AUDIO_GAPLESS_OP op, MMP_BOOL *bAllow)
{
    MMP_ERR     mmpstatus;
    MMP_USHORT  allowedOp = 0;

    *bAllow = MMP_FALSE;

    mmpstatus = MMPD_AUDIO_GetGaplessAllowedOp(&allowedOp);
    if (mmpstatus != MMP_ERR_NONE)
        return mmpstatus;

    if (allowedOp & op)
        *bAllow = MMP_TRUE;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetGaplessEnable
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Set gapless mode playback enable or disable
    @param[in] bEnable : enable or disable gapless mode playback
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetGaplessEnable(MMP_BOOL bEnable, void *nextFileCB, MMP_ULONG param1)
{
    return MMPD_AUDIO_SetGaplessEnable(bEnable, nextFileCB, param1);
}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeAACPlusPlay
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Initialize AACPlus Play
            The function initialize the AACPlus Play. It will return the AACPlus
            media information, and prepare for AACPlus playback.
    @param[in] *fileinfo : aacplus input file parameters
    @param[out] *aacplusinfo : aacplus file info

    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_AUDIO_ERR_UNSUPPORT_FORMAT, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: Audio output path has been set by @ref MMPS_AUDIO_SetMediaPath.
    @pre 2: DRM IV/Key/header offset settings have beed set for DRM file playback.
    @pre 3: @e bFileName and @e usFileNameLength in @e fileinfo must be set properly.
    @pre 4: For host file mode, @e ubBuf and @e ulBufSize must also be set properly.
            @e ulBufSize must be a multiple of 1024.

    @post 1: After initialized, playback can be supported or not will be reported by FW parser.
             For unsupport file located at host storage, file will be closed directly.
    @post 2: After initialized successfully, @ref MMPS_AUDIO_StopAACPlusPlay must be called to close
             file located at host storage, even @ref MMPS_AUDIO_StartAACPlusPlay was not called.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE   m_ubHostBuf[200*1024];
    AIT_AACPlus_Player_Init(MMP_BYTE *filename, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO         fileinfo;
        MMP_AUDIO_AACPLUS_INFO      aacplusinfo;

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
        MMPS_AUDIO_InitializeAACPlusPlay(&fileinfo, &aacplusinfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_InitializeAACPlusPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AACPLUS_INFO *aacplusinfo)
{
    MMP_ERR     status;
    MMP_ULONG64 filesize;
    MMP_ULONG   readsize;
    #if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
	MMP_ULONG	drmOffset;

	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
	MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);	
    #endif

    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_AACPLUS_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AACPLUS_P_CARD_MODE);
        status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            return status;
        }
    }
    else if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (fileinfo->ubBuf == NULL || fileinfo->ulBufSize == 0) {
            PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (fileinfo->ulBufSize & 0x3FF) {
                PRINTF("Please set ulBufSize to be multiple of 1024\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
        }
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        else
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AACPLUS_P_MEM_MODE);
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }

        m_ubAudioPlayBuf = fileinfo->ubBuf;

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
            m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
            m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            MMPC_FS_FileGetSize(m_ulAudioPlayFileHandle, &filesize);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	filesize -= drmOffset;
                filesize = (filesize >> 4) << 4; //16-byte alignment
            }	
			#endif
            if (m_ulAudioPlayBufSize > filesize)
                m_ulAudioPlayBufSize = filesize;
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	MMPC_FS_FileSeek((void *)m_ulAudioPlayFileHandle, (MMP_LONG64)drmOffset, MMPS_FS_SEEK_SET);
            }	
			#endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            m_ulAudioPlayFileSize = filesize;
        }
        else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) {
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }
        else {
            m_ubAudioPlayBuf = 0;
            m_ulAudioPlayBufSize = 0;
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }
        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
        else {
            MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        }
    }

    status = MMPD_AUDIO_GetAACPlusFileInfo((MMP_AUDIO_AACPLUS_INFO *)aacplusinfo);
    if (status != MMP_ERR_NONE) {
        return status;
    }
    if (aacplusinfo->usNotSupport) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
		        MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
	   	    }
        }
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
        (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
        (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        // restart for decode from the top of the memory
        MMPD_AUDIO_SetPlayReadPtr(0, 0);

        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartAACPlusPlay
//------------------------------------------------------------------------------
/**
    @brief  Start AACPLUS Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUDIO_InitializeAACPlusPlay was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.

    <b>Sample codes:</b><br>
    @code
    //AACPlus play has been initialized, start playback with specified starting time.
    AIT_AACPlus_Player_Start(MMP_BOOL bCardMode, MMP_ULONG ulStartTimeMs)
    {
        if (ulStartTimeMs) {
            if (!bCardMode) {
                //host file mode, change position to specified time
                MMPS_AUDIO_AACPlusPlayTime2FileOffset(ulStartTimeMs);
            }
            MMPS_AUDIO_SetAACPlusPlayTime(ulStartTimeMs);
        }
        MMPS_AUDIO_StartAACPlusPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_StartAACPlusPlay(void* callBackFunc, void* context)
{
    return MMPD_AUDIO_StartAudioPlay(callBackFunc, context);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseAACPlusPlay
//------------------------------------------------------------------------------
/**
    @brief  Pause AACPlus Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_PauseAACPlusPlay(void)
{
    MMP_ERR     status = MMP_ERR_NONE;
    MMP_USHORT  play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if (status != MMP_ERR_NONE)
        return status;

    do {
        status = MMPD_AUDIO_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
	} while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeAACPlusPlay
//------------------------------------------------------------------------------
/**
    @brief  Resume AACPlus Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in paused state before resume playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_ResumeAACPlusPlay(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopAACPlusPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop AACPlus Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_StopAACPlusPlay(void)
{
    MMP_ERR status = MMP_ERR_NONE;

    status = MMPD_AUDIO_StopAudioPlay();
    if (status != MMP_ERR_NONE) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
                MMPC_FS_FileClose(m_ulAudioPlayFileHandle);
                m_ulAudioPlayFileHandle = 0;
            }	
        }
        
        goto AAC_STOP_EXIT;
    }

    status = MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
        if (m_ulAudioPlayFileHandle) {
            MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
            m_ulAudioPlayFileHandle = 0;
        }
    }

AAC_STOP_EXIT:
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAACPlusPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get AACPLUS Current Play Time
    @param[out] *usTimeRatio : (current time) / (total time)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetAACPlusPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    return MMPD_AUDIO_GetAACPlusPlayTime(usTimeRatio, ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAACPlusPlaySpectrum
//------------------------------------------------------------------------------
/**
    @brief  Get AACPLUS Play Spectrum
    @param[out] usSpectrum[] : spectrum data (32 words = 64 bytes)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be in playing state before get spectrum, otherwise,
         unexpected spectrum values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetAACPlusPlaySpectrum(MMP_USHORT usSpectrum[])
{
    return MMPD_AUDIO_GetPlaySpectrum(usSpectrum);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetAACPlusPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set AACPlus Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1. This function should be used when playback was in stopped state,
            either stopped by @ref MMPS_AUDIO_StopAACPlusPlay or due to EOF.
    @pre 2. For host file mode, this function should be used 
            combining with @ref MMPS_AUDIO_AACPlusPlayTime2FileOffset.
    @post You can @b NOT get updated play time until you restart playback
          by @ref MMPS_AUDIO_StartAACPlusPlay.

    <b>Sample codes:</b><br>
    @code
    AIT_AACPlus_Player_Seek(MMP_BOOL bCardMode, MMP_ULONG ulTargetTime)
    {
        MMPS_AUDIO_PLAY_STATUS  play_status;

        //Stop playback first if needed.
        MMPS_AUDIO_GetPlayStatus(&play_status);
        if (play_status != MMPS_AUDIO_PLAY_STOP)
            MMPS_AUDIO_StopAACPlusPlay();

        if (!bCardMode) {
            //host file mode, re-open file, change position to the beginning of file
            MMPS_AUDIO_AACPlusPlayTime2FileOffset(ulTargetTime);
        }
        MMPS_AUDIO_SetAACPlusPlayTime(ulTargetTime);
        MMPS_AUDIO_StartAACPlusPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_SetAACPlusPlayTime(MMP_ULONG ulPlayTime)
{
    return MMPD_AUDIO_SetAACPlusPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAACPlusPlayPosition
//------------------------------------------------------------------------------
/**
    @brief  Get AACPlus Play Current Position
    @param[out] *ulPos : file position (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play position. Otherwise, unexpected values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetAACPlusPlayPosition(MMP_ULONG *ulPos)
{
    return MMPD_AUDIO_GetPlayPosition(ulPos);
}
//==============================================================================
//  Function    : MMPS_AUDIO_InitializeFLACPlay
//==============================================================================
/** 
    @brief  Initialize FLAC Play
    @param[in] *fileinfo : FLAC file name input parameter
    @param[out] *flacinfo : flac file info
    
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_UNSUPPORT_FORMAT
*/
MMP_ERR MMPS_AUDIO_InitializeFLACPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_FLAC_INFO *flacinfo)
{
    MMP_ERR		status;
    MMP_ULONG64	filesize;
    MMP_ULONG	readsize;
	#if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
	MMP_ULONG	drmOffset;

	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
	MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);	
    #endif
    
    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_FLAC_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);
    
    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
	    MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
	    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_FLAC_P_CARD_MODE);
	    status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
    	if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            flacinfo->usNotSupport = 1;
	    	return status;
	    }   
	}	    
	else if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
			(m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) ||
			(m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)) {
		if (fileinfo->ubBuf == NULL || fileinfo->ulBufSize == 0) {
			PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
			return MMP_AUDIO_ERR_PARAMETER;
		}	

		if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			if (fileinfo->ulBufSize & 0x3FF) {
				PRINTF("Please set ulBufSize to be multiple of 1024\r\n");
				return MMP_AUDIO_ERR_PARAMETER;
			}
		}
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        else			
		    MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
    	MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_FLAC_P_MEM_MODE);
		if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }

		m_ubAudioPlayBuf = fileinfo->ubBuf;

		if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
			m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
			m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            MMPC_FS_FileGetSize(m_ulAudioPlayFileHandle, &filesize);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	filesize -= drmOffset;
                filesize = (filesize >> 4) << 4; //16-byte alignment
            }	
			#endif
            if (m_ulAudioPlayBufSize > filesize)
                m_ulAudioPlayBufSize = filesize;
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	MMPC_FS_FileSeek((void *)m_ulAudioPlayFileHandle, (MMP_LONG64)drmOffset, MMPS_FS_SEEK_SET);
            }	
			#endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            m_ulAudioPlayFileSize = filesize;
		}			
        else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) {
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }
        else {
            m_ubAudioPlayBuf = 0;
            m_ulAudioPlayBufSize = 0;
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }

	
	    MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
	    MMPD_AUDIO_InitPlayRWPtr();
	    
	    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
	    	MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
		}	    	
		else {
	    	MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, 
	    									m_ulAudioPlayFileSize, 0);
		}
        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
        else {
            MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        }
	}

    status = MMPD_AUDIO_GetFLACFileInfo((MMP_AUDIO_FLAC_INFO *)flacinfo);
	if(flacinfo->usNotSupport) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
		        MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
	   	    }
        }
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }		    

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
        (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
        (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        // restart for decode from the top of the memory
        MMPD_AUDIO_SetPlayReadPtr(0, 0);

        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
    }
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPS_AUDIO_StartFLACPlay
//==============================================================================
/** 
    @brief  Start FLAC Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StartFLACPlay(void* callBackFunc, void* context)
{
    return MMPD_AUDIO_StartAudioPlay(callBackFunc, context);
}
//==============================================================================
//  Function    : MMPS_AUDIO_PauseFLACPlay
//==============================================================================
/** 
    @brief  Pause FLAC Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_PauseFLACPlay(void)
{
    MMP_ERR status;
    MMP_USHORT play_status;
    status = MMPD_AUDIO_PauseAudioPlay();
    if(status == MMP_AUDIO_ERR_COMMAND_INVALID) {
        return status;
    }    
    
    do{
        MMPD_AUDIO_GetPlayStatus(&play_status);
	}while(play_status != DECODE_OP_PAUSE);
    
    return MMP_ERR_NONE;
}
//==============================================================================
//  Function    : MMPS_AUDIO_ResumeFLACPlay
//==============================================================================
/** 
    @brief  Resume FLAC Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_ResumeFLACPlay(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}
//==============================================================================
//  Function    : MMPS_AUDIO_StopFLACPlay
//==============================================================================
/** 
    @brief  Stop FLAC Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StopFLACPlay(void)
{
    MMP_ERR status = MMP_ERR_NONE;

    status = MMPD_AUDIO_StopAudioPlay();
    if (status != MMP_ERR_NONE) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
                MMPC_FS_FileClose(m_ulAudioPlayFileHandle);
                m_ulAudioPlayFileHandle = 0;
            }	
        }
        
        goto FLAC_STOP_EXIT;
    }

    status = MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
        if (m_ulAudioPlayFileHandle) {
            MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
            m_ulAudioPlayFileHandle = 0;
        }
    }
    
FLAC_STOP_EXIT:

    return status;
}

//==============================================================================
//  Function    : MMPS_AUDIO_GetFLACPlayTime
//==============================================================================
/** 
    @brief  Get FLAC Current Play Time
    @param[out] *usTimeRatio : (current time) / (total time)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetFLACPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    MMPD_AUDIO_GetFLACPlayTime(usTimeRatio, ulPlayTime);
			       
    return MMP_ERR_NONE;
}

//==============================================================================
//  Function    : MMPS_AUDIO_SetFLACPlayTime
//==============================================================================
/** 
    @brief  Set FLAC Start Play Time
    @param[in] ulPlayTime : play time (ms) 
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetFLACPlayTime(MMP_ULONG ulPlayTime)
{
    return MMPD_AUDIO_SetFLACPlayTime(ulPlayTime);

}
//==============================================================================
//  Function    : MMPS_AUDIO_SetFLACPlayEQ
//==============================================================================
/** 
    @brief  Set FLAC Play EQ Type
    @param[out] usType : eq type
        -   MMPS_AUDIO_PLAY_EQ_NONE
        -   MMPS_AUDIO_PLAY_EQ_CLASSIC
        -   MMPS_AUDIO_PLAY_EQ_JAZZ
        -   MMPS_AUDIO_PLAY_EQ_POP
        -   MMPS_AUDIO_PLAY_EQ_ROCK
        -   MMPS_AUDIO_PLAY_EQ_BASS3
        -   MMPS_AUDIO_PLAY_EQ_BASS9
        -   MMPS_AUDIO_PLAY_HP_SURROUND
        -   MMPS_AUDIO_PLAYSPK_SURROUND
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetFLACPlayEQ(MMPS_AUDIO_EQTYPE usType)
{
    MMPD_AUDIO_SetEQType(usType, (void*)NULL);
    
    return MMP_ERR_NONE;
}
/// @ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitMIDIPlayFromCard
//------------------------------------------------------------------------------
/**
    @brief  Initialize MIDI Play From Card
    @param[in] *fileinfo : file information
    @param[out] *midiinfo : midi specific info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_UNSUPPORT_FORMAT
*/
MMP_ERR MMPS_AUDIO_InitMIDIPlayFromCard(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MIDI_INFO *midiinfo)
{
    MMP_ERR status;

    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_MIDI_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);
    MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_MIDI_P_CARD_MODE);
    
    status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
    if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
        return status;
    }
    MMPD_AUDIO_GetMIDIFileInfo((MMP_AUDIO_MIDI_INFO *)midiinfo);
    if (midiinfo->usNotSupport) {
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitMIDIPlayFromMem
//------------------------------------------------------------------------------
/**
    @brief  Initialize MIDI Play From Mem
    @param[in] *ubAudioPtr : audio data start pointer
    @param[in] ulFileSize : file size
    @param[out] *fileinfo : midi file info
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_INSUFFICIENT_BUF,MMP_AUDIO_ERR_UNSUPPORT_FORMAT
*/
MMP_ERR MMPS_AUDIO_InitMIDIPlayFromMem(MMP_UBYTE *ubAudioPtr,MMP_ULONG ulFileSize, MMP_AUDIO_MIDI_INFO *fileinfo)
{
    MMP_ULONG buf_size;

    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_MIDI_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);
    MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_MIDI_P_MEM_MODE);
    MMPD_AUDIO_SetPlayFileSize(ulFileSize);

    MMPD_AUDIO_GetAudioPlayBufSize(&buf_size);
    if (ulFileSize > buf_size) {
        return  MMP_AUDIO_ERR_INSUFFICIENT_BUF;
    }

    MMPD_AUDIO_TransferMIDIDataToAIT(ubAudioPtr,ulFileSize);
    MMPD_AUDIO_GetMIDIFileInfo((MMP_AUDIO_MIDI_INFO *)fileinfo);
    if (fileinfo->usNotSupport) {
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartMIDIPlay
//------------------------------------------------------------------------------
/**
    @brief  Start MIDI Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StartMIDIPlay(void)
{
    return MMPD_AUDIO_StartAudioPlay(NULL, NULL);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseMIDIPlay
//------------------------------------------------------------------------------
/**
    @brief  Pause MIDI Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_PauseMIDIPlay(void)
{
    MMP_ERR status;
    MMP_USHORT play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if(status == MMP_AUDIO_ERR_COMMAND_INVALID){
        return status;
    }

    do {
        MMPD_AUDIO_GetPlayStatus(&play_status);
	} while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseMIDIPlay
//------------------------------------------------------------------------------
/**
    @brief  Resume MIDI Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_ResumeMIDIPlay(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopMIDIPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop MIDI Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StopMIDIPlay(void)
{
    MMP_ERR status;

    status = MMPD_AUDIO_StopAudioPlay();

    if(status == MMP_AUDIO_ERR_COMMAND_INVALID){
	    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			if (m_ulAudioPlayFileHandle) {	
	        	MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
			}	
	    }
	    
        goto MIDI_STOP_EXIT;
    }

	MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
		if (m_ulAudioPlayFileHandle) {	
        	MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
			m_ulAudioPlayFileHandle = 0;
		}	
    }

MIDI_STOP_EXIT:
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetMIDIPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get MIDI Current Play Time
    @param[out] *usTimeRatio : (current time) / (total time)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetMIDIPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    return MMPD_AUDIO_GetMIDIPlayTime(usTimeRatio,ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetMIDIPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set MIDI Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetMIDIPlayTime(MMP_ULONG ulPlayTime)
{
    return MMPD_AUDIO_SetMIDIPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartMIDINotePlay
//------------------------------------------------------------------------------
/**
    @brief  Start MIDI Note Play
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_StartMIDINotePlay(void)
{
    return MMPD_AUDIO_StartMIDINotePlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopMIDINotePlay
//------------------------------------------------------------------------------
/**
    @brief  Stop MIDI Note Play
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_StopMIDINotePlay(void)
{
    return MMPD_AUDIO_StopMIDINotePlay();
}
/// @end_ait_only

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Initialize MP3 Play
            The function initialize the MP3 Play. It will return the MP3 media 
            information, and prepare for MP3 playback.

    @param[in] *fileinfo : input file parameters
    @param[out] *mp3info : mp3 file info

    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_AUDIO_ERR_UNSUPPORT_FORMAT, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: Audio output path has been set by @ref MMPS_AUDIO_SetMediaPath.
    @pre 2: DRM IV/Key/header offset settings have beed set for DRM file playback.
    @pre 3: @e bFileName and @e usFileNameLength in @e fileinfo must be set properly.
    @pre 4: For host file mode, @e ubBuf and @e ulBufSize must also be set properly.
            @e ulBufSize must be a multiple of 1024.

    @post 1: After initialized, playback can be supported or not will be reported by FW parser.
             For unsupport file located at host storage, file will be closed directly.
    @post 2: After initialized successfully, @ref MMPS_AUDIO_StopMP3Play must be called to close
             file located at host storage, even @ref MMPS_AUDIO_StartMP3Play was not called.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE   m_ubHostBuf[200*1024];
    AIT_MP3_Player_Init(MMP_BYTE *filename, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO         fileinfo;
        MMP_AUDIO_MP3_INFO          mp3info;

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
        MMPS_AUDIO_InitializeMP3Play(&fileinfo, &mp3info);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_InitializeMP3Play(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MP3_INFO *mp3info)
{
    MMP_ERR     status;
    #if (OMA_DRM_EN == 1)
    MMP_USHORT	drmEn;
    MMP_ULONG	drmOffset;

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

    mp3info->usNotSupport = 1;
    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_MP3_PLAY);

    m_bMP3GetInfoStage = MMP_TRUE;

    MMPD_AUDIO_SetParseFormat(MMP_AUDIO_MP3_PLAY);
    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPD_AUDIO_SetParsePath(MMPD_AUDIO_PLAY_FROM_CARD);
        status = MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_MP3_P_CARD_MODE);
        if (status != MMP_ERR_NONE) {
            return status;
        }
        status = MMPD_AUDIO_SetParseFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            return status;
        }
    }
    else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
        if ((fileinfo->ubBuf == NULL) || (fileinfo->ulBufSize == 0)) {
            PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }
        MMPD_AUDIO_SetParsePath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        //NOTE: use CARD_MODE for buffer allocation here even for streaming play
        status = MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_MP3_P_CARD_MODE);
        if (status != MMP_ERR_NONE) {
            return status;
        }
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            MMPD_AUDIO_SetParseBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }
        m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
        m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
    }
    else {
        PRINTF("Not supported media path!\r\n");
        return MMP_AUDIO_ERR_PARAMETER;
    }

    MMPD_AUDIO_GetMP3FileInfo((MMP_AUDIO_MP3_INFO *)mp3info);
    m_bMP3GetInfoStage = MMP_FALSE;
    if (mp3info->usNotSupport)
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;

    status = MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_MP3_P_CARD_MODE);
    if (status != MMP_ERR_NONE) {
        return status;
    }
    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
        MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        // restart for decode from the top of the memory
        MMPD_AUDIO_SetPlayReadPtr(0, 0);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Start MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUDIO_InitializeMP3Play was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.

    <b>Sample codes:</b><br>
    @code
    //MP3 play has been initialized, start playback with specified starting time.
    AIT_MP3_Player_Start(MMP_BOOL bCardMode, MMP_ULONG ulStartTimeMs)
    {
        if (ulStartTimeMs) {
            if (!bCardMode) {
                //host file mode, change position to specified time
                MMPS_AUDIO_MP3PlayTime2FileOffset(ulStartTimeMs);
            }
            MMPS_AUDIO_SetMP3PlayTime(ulStartTimeMs);
        }
        MMPS_AUDIO_StartMP3Play();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_StartMP3Play(void* callBackFunc, void* context)
{
    return MMPD_AUDIO_StartAudioPlay(callBackFunc, context);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Pause MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_PauseMP3Play(void)
{
    MMP_ERR     status = MMP_ERR_NONE;
    MMP_USHORT  play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if (status != MMP_ERR_NONE)
        return status;

    do {
        status = MMPD_AUDIO_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
	} while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Resume MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_ResumeMP3Play(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopMP3Play
//------------------------------------------------------------------------------
/**
    @brief  Stop MP3 Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_StopMP3Play(void)
{
    MMP_ERR status = MMP_ERR_NONE;

    status = MMPD_AUDIO_StopAudioPlay();

    if (status != MMP_ERR_NONE) {
	    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			if (m_ulAudioPlayFileHandle) {	
	        	MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
			}		
	    }
        goto MP3_STOP_EXIT;
    }

	MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
		if (m_ulAudioPlayFileHandle) {	
			MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
			m_ulAudioPlayFileHandle = 0;
		}
    }
    
MP3_STOP_EXIT:

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetMP3PlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get MP3 Current Play Time
    @param[out] *usTimeRatio : (current time) / (total time)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetMP3PlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    return MMPD_AUDIO_GetMP3PlayTime(usTimeRatio, ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetMP3PlaySpectrum
//------------------------------------------------------------------------------
/**
    @brief  Get MP3 Play Spectrum
    @param[out]  usSpectrum[] : spectrum data (32 words =64 bytes)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be in playing state before get spectrum, otherwise,
         unexpected spectrum values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetMP3PlaySpectrum(MMP_USHORT usSpectrum[])
{
    return MMPD_AUDIO_GetPlaySpectrum(usSpectrum);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetMP3PlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set MP3 Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1. This function should be used when playback was in stopped state,
            either stopped by @ref MMPS_AUDIO_StopMP3Play or due to EOF.
    @pre 2. For host file mode, this function should be used 
            combining with @ref MMPS_AUDIO_MP3PlayTime2FileOffset.
    @post You can @b NOT get updated play time until you restart playback
          by @ref MMPS_AUDIO_StartMP3Play.

    <b>Sample codes:</b><br>
    @code
    AIT_MP3_Player_Seek(MMP_BOOL bCardMode, MMP_ULONG ulTargetTime)
    {
        MMPS_AUDIO_PLAY_STATUS  play_status;

        //Stop playback first if needed.
        MMPS_AUDIO_GetPlayStatus(&play_status);
        if (play_status != MMPS_AUDIO_PLAY_STOP)
            MMPS_AUDIO_StopMP3Play();

        if (!bCardMode) {
            //host file mode, re-open file, change position to the beginning of file
            MMPS_AUDIO_MP3PlayTime2FileOffset(ulTargetTime);
        }
        MMPS_AUDIO_SetMP3PlayTime(ulTargetTime);
        MMPS_AUDIO_StartMP3Play();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_SetMP3PlayTime(MMP_ULONG ulPlayTime)
{
    return MMPD_AUDIO_SetMP3PlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetMP3PlayPosition
//------------------------------------------------------------------------------
/**
    @brief  Get MP3 Play Current Position
    @param[out] *ulPos : position (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play position. Otherwise, unexpected values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetMP3PlayPosition(MMP_ULONG *ulPos)
{
    return MMPD_AUDIO_GetPlayPosition(ulPos);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetParserCacheBuf
//------------------------------------------------------------------------------
/**
    @brief  Set cache buffer address and size for parsing audio information
    @param[in] ulCacheAddr : host buffer address used as parser cache
    @param[in] ulCacheSize : cache size
    @return MMP_ERR_NONE

    @pre For better performance, @e ulCacheSize should be a multiple of 512 Byte.
*/
MMP_ERR MMPS_AUDIO_SetParserCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize)
{
    #if (MP3_HOST_PARSER_EN == 1)||(AAC_HOST_PARSER_EN == 1)||\
    	(WMA_HOST_PARSER_EN	== 1)||(WAV_HOST_PARSER_EN == 1)||\
    	(OGG_HOST_PARSER_EN	== 1)||(RA_HOST_PARSER_EN == 1) ||\
    	(AMR_HOST_PARSER_EN	== 1)
    return MMPD_AUDPSR_SetCacheBuf(ulCacheAddr, ulCacheSize);
    #else
    return MMP_ERR_NONE;
    #endif
}

/// @ait_only
#if (AUDIO_HOST_DB_EN == 1) && (FS_INPUT_ENCODE == UCS2)
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_WSTRCPY
//------------------------------------------------------------------------------
/**
    @brief  Copy the wide character string pointed by @e src into the array 
            pointed by @dst, including the terminating null characters.
    @param[in] *dst : destination wide character string
    @param[in] *src : source wide character string
    @return MMP_ERR_NONE
*/
static MMP_ERR MMPS_AUDIO_WSTRCPY(MMP_BYTE *dst, MMP_BYTE *src)
{
    for(; *(MMP_USHORT*)src != 0x0000; ) {
        *(MMP_USHORT*)dst = *(MMP_USHORT*)src;
        src = src + 2;
        dst = dst + 2;
    }
    *(MMP_USHORT*)dst = 0;
    return MMP_ERR_NONE;
}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_AddPartAudioInfo
//------------------------------------------------------------------------------
/**
    @brief  Add partial audio info into database
    @param[in] *bDirName : Name of searched directory
    @param[in] ulDirNameSize : Searched directory name length
    @param[in] ulTotalNum : How much info the user want to add into database
    @param[out] *ulAddNum : How much info the function add into database
    @param[in] ulInitDepth : The directory depth when first call
    @return MMP_ERR_NONE
*/
#if (AUDIO_HOST_DB_EN == 1)
static MMP_ERR MMPS_AUDIO_AddPartDatabaseInfo(MMP_BYTE* bDirName, MMP_ULONG ulDirNameSize,
                                    MMP_ULONG ulTotalNum, MMP_ULONG *ulAddNum, MMP_ULONG ulInitDepth)
{
    #if (FS_INPUT_ENCODE == UCS2)
    MMP_BYTE        		ret_file_name[AUDIO_MAX_FILE_NAME_SIZE * 2];
    MMP_BYTE 				bNewName[AUDIO_MAX_FILE_NAME_SIZE * 2];
    #elif (FS_INPUT_ENCODE == UTF8)
    MMP_BYTE        		ret_file_name[AUDIO_MAX_FILE_NAME_SIZE * 3];
    MMP_BYTE 				bNewName[AUDIO_MAX_FILE_NAME_SIZE * 3];
    #endif
    MMP_ERR         		err;

    MMPS_FS_ATTRIBUTE 		attribute;
    MMP_ULONG       		open_dir_id;
    MMP_USHORT      		i;
    MMP_ULONG				fileID;
    MMP_ULONG 				ulPtr = 0;

    
//    PRINTF("-------------------------------------------\r\n");
//	print_ucs2("Dir", bDirName);
   
    
	if (m_ulOpenedDirID[m_ulDepth] == 0) {
        err = MMPS_FS_DirOpen(bDirName, ulDirNameSize, &open_dir_id);
	    if (err) { 
	        PRINTF("DirOpen failed.%d\r\n", err);
    	    err = MMPS_FS_DirClose(open_dir_id);
	        if (err) {
	            PRINTF("DirClose failed.%d\r\n", err);
    	    }
	        return MMP_AUDIO_ERR_NO_AUDIO_FOUND;
    	}
		m_ulOpenedDirID[m_ulDepth] = open_dir_id;
    }
    
    i = 0;
    while(1) {
        err = MMPS_FS_GetDBFileList(m_ulOpenedDirID[m_ulDepth],
									ret_file_name,
									&attribute,
									&fileID);
                                        
        if  (err) {
            if (MMP_FS_ERR_NO_MORE_ENTRY == err) {
                break;
            }
            else {
                PRINTF("GetFileList failed. %X\r\n", err);
                return err;
            }
        }
        if (MMPS_FS_ATTR_DIRECTORY & attribute) {
            PRINTF("%2d:         [%s]\r\n", i, ret_file_name);
            
            #if (FS_INPUT_ENCODE == UCS2)
            if(!((ret_file_name[0] == '.') && (ret_file_name[1] == 0))) {
                ulPtr = 0;

                MMPS_AUDIO_WSTRCPY(bNewName, bDirName);
                ulPtr += uniStrlen((const MMP_SHORT *)bDirName);
                MMPS_AUDIO_WSTRCPY(&bNewName[ulPtr], ret_file_name);
                ulPtr += uniStrlen((const MMP_SHORT *)ret_file_name);

                bNewName[ulPtr] = '\\';
                bNewName[ulPtr+1] = 0;
                bNewName[ulPtr+2] = '\0';
                bNewName[ulPtr+3] = 0;
                
                m_ulDepth++;
                
                err = MMPS_AUDIO_AddPartDatabaseInfo(bNewName, uniStrlen((const short *)bNewName), ulTotalNum, ulAddNum, ulInitDepth);
                if(err) return err;
            }
            #elif (FS_INPUT_ENCODE == UTF8)
            if(ret_file_name[0] != '.') {
                STRCPY(bNewName, bDirName);
                STRCAT(bNewName, ret_file_name);
                STRCAT(bNewName, "\\");
                
                m_ulDepth++;
                
                PRINTF("sub Name : %s\r\n\r\n", bNewName);
                err = MMPS_AUDIO_AddPartDatabaseInfo(bNewName, uniStrlen((const short *)bNewName), ulTotalNum, ulAddNum, ulInitDepth);
                if(err) return err;
            }
            #endif
            if(*ulAddNum >= ulTotalNum) {               
                break;
            }          
        }
        else {
//        	print_ucs2("File", ret_file_name);
            
            #if (FS_INPUT_ENCODE == UCS2)
			ulPtr = 0;
			MMPS_AUDIO_WSTRCPY(bNewName, bDirName);
			ulPtr += uniStrlen((const MMP_SHORT *)bDirName);
			MMPS_AUDIO_WSTRCPY(&bNewName[ulPtr], ret_file_name);

			err = MMPD_AUDIODB_AddMusic(bNewName, fileID);
            #elif (FS_INPUT_ENCODE == UTF8)
            STRCPY(bNewName, bDirName);
            STRCAT(bNewName, ret_file_name);
            err = MMPD_AUDIODB_AddMusic(bNewName, fileID);
            #endif

            if(err == MMP_ERR_NONE) {
                *ulAddNum += 1;
            }

            if(*ulAddNum >= ulTotalNum) {
	            #if (FS_INPUT_ENCODE == UCS2)
				MMPS_AUDIO_WSTRCPY(m_bLastDirName, bDirName);
        	    #elif (FS_INPUT_ENCODE == UTF8)
				STRCPY(m_bLastDirName, bDirName);
	            #endif
				break;
            }
        }
        i ++;
    }
    if(*ulAddNum < ulTotalNum) {
        err = MMPS_FS_DirClose(m_ulOpenedDirID[m_ulDepth]);
        if (err) { 
            PRINTF("DirClose failed.\r\n");
            return err;
        }
        m_ulOpenedDirID[m_ulDepth] = 0;
        if((m_ulDepth > 0) && (ulInitDepth >= m_ulDepth)) {
            #if (FS_INPUT_ENCODE == UCS2)
            ulPtr = ulDirNameSize - 4;
            while (ulPtr) {
                if(bDirName[ulPtr] == '\\' && bDirName[ulPtr+1] == 0) {
                    bDirName[ulPtr+2] = '\0';
                    bDirName[ulPtr+3] = 0;
                    for(ulPtr = ulPtr+4; ulPtr < ulDirNameSize; ulPtr++){
                        bDirName[ulPtr] = 0;
                    }
                    break;
                }
                ulPtr -= 2;
            }
            #elif (FS_INPUT_ENCODE == UTF8)
            ulPtr = ulDirNameSize - 2;
            while (ulPtr) {
                if(bDirName[ulPtr] == '\\') {
                    bDirName[ulPtr+1] = '\0';
                    for(ulPtr = ulPtr+2; ulPtr < ulDirNameSize; ulPtr++){
                        bDirName[ulPtr] = 0;
                    }
                    break;
                }
                ulPtr -= 1;
            }
            #endif
            m_ulDepth--;
            err = MMPS_AUDIO_AddPartDatabaseInfo(bDirName, uniStrlen((const short *)bDirName), ulTotalNum, ulAddNum, m_ulDepth);
            if(err) 
            	return err;
        } else if(m_ulDepth > 0) {
            m_ulDepth--;
        }
    }
     
    return MMP_ERR_NONE;
    
}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_AddDatabasePart
//------------------------------------------------------------------------------
/**
    @brief  Add partial audio info into database
    @param[in] ulRequestNum : How much info the user want to add into database
    @param[out] ulAddNum : How much info the function add into database
    @return MMP_ERR_NONE if no error
*/
MMP_ERR MMPS_AUDIO_AddDatabasePart(MMP_ULONG ulRequestNum, MMP_ULONG *ulAddNum)
{
	#if (AUDIO_HOST_DB_EN == 1)
	*ulAddNum = 0;
    return MMPS_AUDIO_AddPartDatabaseInfo(m_bLastDirName, uniStrlen((const short *)m_bLastDirName), ulRequestNum, ulAddNum, m_ulDepth);
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeDatabase
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
	@param[in] bDirName    directory name string.
	@param[in] ulDirNameSize   The length, in bytes, of bDirName string, including the terminating null character.
    @param[in] bDBFileName : database file name
	@param[in] ulDBFileNameSize   The length, in bytes, of bDBFileName string, including the terminating null character.
    @param[in] ulID3CacheAddr : ID3 parser cache address
    @param[in] ulID3CacheSize : ID3 parser cache size
    @param[in] ulDBWriteCacheAddr : Database cache address
    @param[in] ulDBWriteCacheSize : Database cache size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitializeDatabase(MMP_BYTE *bDirName, MMP_ULONG ulDirNameSize,
									MMP_BYTE* bDBFileName, MMP_ULONG ulDBFileNameSize,
									MMP_ULONG ulID3CacheAddr, MMP_ULONG ulID3CacheSize,
									MMP_ULONG ulDBWriteCacheAddr, MMP_ULONG ulDBWriteCacheSize)
{
	#if (AUDIO_HOST_DB_EN == 1)
    MMP_ULONG 	i;
    MMP_ERR		err;
    
    for(i = 0; i < 10; i++) {
        m_ulOpenedDirID[i] = 0;
    }
    m_ulDepth = 0;
    
    MEMCPY(m_bLastDirName, bDirName, ulDirNameSize);

    //Initial ID3 parser cache space
    #if (MP3_P_EN) || (VMP3_P_EN)
    MMPD_ID3_SetParseCacheBuf(ulID3CacheAddr, ulID3CacheSize, ulID3CacheSize);
	#endif

    //Initial database, data base is always stores to SD card.
    MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
	MEMCPY(m_ubDBFileName, bDBFileName, ulDBFileNameSize);
	m_ulDBFileNameSize = ulDBFileNameSize;
    err = MMPD_AUDIODB_CreateInitialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize);
    if (err != MMP_ERR_NONE)
        return err;
    err = MMPD_AUDIODB_SetWriteCacheBuf(ulDBWriteCacheAddr, ulDBWriteCacheSize);
    if (err != MMP_ERR_NONE)
        return err;

   
    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_FinishDatabase
//------------------------------------------------------------------------------
/**
    @brief  Finish the audio database index file
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_FinishDatabase(void)
{
	#if (AUDIO_HOST_DB_EN == 1)
    MMP_ULONG       i;
    MMP_ERR         err;

    for(i = 0; m_ulOpenedDirID[i] != 0; i++) {
        err = MMPS_FS_DirClose(m_ulOpenedDirID[i]);
        if (err) { 
            PRINTF("DirClose failed.\r\n");
        }
    }
    MMPD_AUDIODB_CreateFinish();
    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_DBMngrInitialize
//------------------------------------------------------------------------------
/**
    @brief  Allocate memory for audio database
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_DBMngrInitialize(void)
{
	#if (AUDIO_HOST_DB_EN == 1)
    return MMPD_AUDIODB_MemAlloc();
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_DBMngrFinish
//------------------------------------------------------------------------------
/**
    @brief  Free memory for audio database
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_DBMngrFinish(void)
{
	#if (AUDIO_HOST_DB_EN == 1)
	MMP_ERR	err;
	MMP_ULONG	file_size;

	if (m_sortType != MMPS_AUDIO_DB_SORT_MAX) {
		switch(m_sortType) {
		case MMPS_AUDIO_DB_SORT_TITLE:
			MMPD_AUDIODB_BTreeFree(&m_treeRoot);
			break;
		case MMPS_AUDIO_DB_SORT_ARTIST:
		case MMPS_AUDIO_DB_SORT_ALBUM:
		case MMPS_AUDIO_DB_SORT_GENRES:
			MMPD_AUDIODB_BForestFree(&m_forestRoot);
			break;
		}
		m_sortType = MMPS_AUDIO_DB_SORT_MAX;
	}		
	if (m_bDatabaseDirty) {
	    MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
	    err = MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "a+b");
	    if (err) return err;
		err = MMPD_AUDIODB_CheckDatabaseDirty(&file_size);
	    if (err) return err;
		MMPD_AUDIODB_Finish();	
		
		if (!file_size) {
			MMPD_AUDIODB_DeleteDatabase((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize);
		}
		
		m_bDatabaseDirty = MMP_FALSE;
	}		
    return MMPD_AUDIODB_MemFree();
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_AddAllAudioInfo
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
	@param[in] bDirName    directory name string.
	@param[in] ulDirNameSize   The length, in bytes, of bDirName string, including the terminating null character.
    @return MMP_ERR_NONE
*/
#if (AUDIO_HOST_DB_EN == 1)
static MMP_ERR MMPS_AUDIO_AddAllAudioInfo(MMP_BYTE* bDirName, MMP_ULONG ulDirNameSize)
{
    #if (FS_INPUT_ENCODE == UCS2)
    MMP_BYTE        		ret_file_name[AUDIO_MAX_FILE_NAME_SIZE * 2];
    MMP_BYTE 				bNewName[AUDIO_MAX_FILE_NAME_SIZE * 2];
    MMP_ULONG 				ulPtr = 0;
    #elif (FS_INPUT_ENCODE == UTF8)
    MMP_BYTE        		ret_file_name[AUDIO_MAX_FILE_NAME_SIZE * 3];
    MMP_BYTE 				bNewName[AUDIO_MAX_FILE_NAME_SIZE * 3];
    #endif
    MMP_ERR         		err;
    MMPS_FS_ATTRIBUTE 		attribute;
    MMP_ULONG       		open_dir_id;
    MMP_USHORT      		i;		
    MMP_ULONG				fileID;

    //PRINTF("-------------------------------------------\r\n");
    //PRINTF(" %s\r\n", bDirName);

    err = MMPS_FS_DirOpen(bDirName, ulDirNameSize, &open_dir_id);
    if (err) { 
        PRINTF("DirOpen failed.%d\r\n", err);
        err = MMPS_FS_DirClose(open_dir_id);
        if (err) {
            PRINTF("DirClose failed.%d\r\n", err);
        }
        return MMP_AUDIO_ERR_NO_AUDIO_FOUND;
    }

    i = 0;
    while(1) {
        err = MMPS_FS_GetDBFileList(open_dir_id,
								ret_file_name,
								&attribute,
								&fileID);
                                        
        if (err) {
            if (MMP_FS_ERR_NO_MORE_ENTRY == err) {
                break;
            }
            else {
                PRINTF("GetFileList failed. %X\r\n", err);
                break;
            }
        }
        if (MMPS_FS_ATTR_DIRECTORY & attribute) {
            //PRINTF("%2d:         [%s]\r\n", i, ret_file_name);
            #if (FS_INPUT_ENCODE == UCS2)
            if(!((ret_file_name[0] == '.') && (ret_file_name[1] == 0))) {
				ulPtr = 0;

                MMPS_AUDIO_WSTRCPY(bNewName, bDirName);
                ulPtr += uniStrlen((const MMP_SHORT *)bDirName);
                MMPS_AUDIO_WSTRCPY(&bNewName[ulPtr], ret_file_name);
                ulPtr += uniStrlen((const MMP_SHORT *)ret_file_name);

                bNewName[ulPtr] = '\\';
                bNewName[ulPtr+1] = 0;
                bNewName[ulPtr+2] = '\0';
                bNewName[ulPtr+3] = 0;
                
                MMPS_AUDIO_AddAllAudioInfo(bNewName, uniStrlen((const short *)bNewName));
            }
            #elif (FS_INPUT_ENCODE == UTF8)
            if (ret_file_name[0] != '.') {
                STRCPY(bNewName, bDirName);
                STRCAT(bNewName, ret_file_name);
                STRCAT(bNewName, "\\");
                
                PRINTF("sub Name : %s\r\n\r\n", bNewName);
                MMPS_AUDIO_AddAllAudioInfo(bNewName, STRLEN(bNewName));
            }
            #endif
                        
        }
        else {
       	   	#if (FS_INPUT_ENCODE == UCS2)
        	print_ucs2("File", ret_file_name);
        	#endif
            
            #if (FS_INPUT_ENCODE == UCS2)
			ulPtr = 0;
			MMPS_AUDIO_WSTRCPY(bNewName, bDirName);
			ulPtr += uniStrlen((const MMP_SHORT *)bDirName);
			MMPS_AUDIO_WSTRCPY(&bNewName[ulPtr], ret_file_name);
			MMPD_AUDIODB_AddMusic(bNewName, fileID);
            #elif (FS_INPUT_ENCODE == UTF8)
            STRCPY(bNewName, bDirName);
            STRCAT(bNewName, ret_file_name);
            MMPD_AUDIODB_AddMusic(bNewName, fileID);
            #endif

        }
        i ++;
    }
    
    err = MMPS_FS_DirClose(open_dir_id);
    if (err) { 
        PRINTF("DirClose failed.\r\n");
    } 
     
    return MMP_ERR_NONE;
}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_CreateDatabase
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
	@param[in] bDirName    directory name string.
	@param[in] ulDirNameSize   The length, in bytes, of bDirName string, including the terminating null character.
    @param[in] bDBFileName : database file name
	@param[in] ulDBFileNameSize   The length, in bytes, of bDBFileName string, including the terminating null character.
    @param[in] ulID3CacheAddr : ID3 parser cache address
    @param[in] ulID3CacheSize : ID3 parser cache size
    @param[in] ulDBWriteCacheAddr : Database cache address
    @param[in] ulDBWriteCacheSize : Database cache size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_CreateDatabase(MMP_BYTE *bDirName, MMP_ULONG ulDirNameSize,
									MMP_BYTE* bDBFileName, MMP_ULONG ulDBFileNameSize,
									MMP_ULONG ulID3CacheAddr, MMP_ULONG ulID3CacheSize,
									MMP_ULONG ulDBWriteCacheAddr, MMP_ULONG ulDBWriteCacheSize)
{	
	#if (AUDIO_HOST_DB_EN == 1)
    MMP_ERR err = MMP_ERR_NONE;

    //Initial ID3 parser cache space
    #if (MP3_P_EN) || (VMP3_P_EN)
    MMPD_ID3_SetParseCacheBuf(ulID3CacheAddr, ulID3CacheSize, ulID3CacheSize);
	#endif

    //Initial database, data base is always stores to SD card.
    MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
	MEMCPY(m_ubDBFileName, bDBFileName, ulDBFileNameSize);
	m_ulDBFileNameSize = ulDBFileNameSize;
    err = MMPD_AUDIODB_CreateInitialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize);
    if (err != MMP_ERR_NONE)
        return err;
    err = MMPD_AUDIODB_SetWriteCacheBuf(ulDBWriteCacheAddr, ulDBWriteCacheSize);
    if (err != MMP_ERR_NONE)
        return err;
    err = MMPS_AUDIO_AddAllAudioInfo(bDirName, ulDirNameSize);
    if (err != MMP_ERR_NONE)
        return err;
    MMPD_AUDIODB_CreateFinish();
    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetDatabaseCacheBuf
//------------------------------------------------------------------------------
/**
    @brief  Set the cache address for the database usage for MMPS_AUDIO_GetDBMngrFileList/MMPS_AUDIO_GetDBMngrTrackList
    @param[in] ulDBCacheAddr : cache address
    @param[in] ulDBCacheSize : cache size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetDatabaseCacheBuf(MMP_ULONG ulDBCacheAddr, MMP_ULONG ulDBCacheSize)
{
	#if (AUDIO_HOST_DB_EN == 1)
	if (ulDBCacheSize & 0x1FF)
		return 	MMP_AUDIO_ERR_PARAMETER;

    return	MMPD_AUDIODB_SetParseCacheBuf(ulDBCacheAddr, ulDBCacheSize);
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : strcmp_w_limit
//------------------------------------------------------------------------------
#if (AUDIO_HOST_DB_EN == 1)
static MMP_LONG strcmp_w_limit(MMP_BYTE *str1, MMP_BYTE *str2, MMP_ULONG length)
{
	MMP_USHORT *s1 = (MMP_USHORT*)str1;
	MMP_USHORT *s2 = (MMP_USHORT*)str2;
	MMP_ULONG	i = 0;

    while (*s1 == *s2) {
   	    i++;
    	if (i == length) {
    		return 0;
    	}
    	else {	
	        if(*s1 == 0)
    	        return 0;
        	s1++;
	        s2++;
		}	    	    
    }
    return (MMP_LONG)*s1 - (MMP_LONG)*s2;
}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetDBMngrFileListActionArtist
//------------------------------------------------------------------------------
/**
    @brief  Get the file list for artist
	@param[in] node : forest node
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetDBMngrFileListActionArtist(MMPD_AUDIODB_BFNODE *node)
{
	#if (AUDIO_HOST_DB_EN == 1)
	if (m_ulFilterStringLength) {
		// filter function
		if (strcmp_w_limit(node->data, (MMP_BYTE *)m_ubFilterString, m_ulFilterStringLength)) {
			// not match
			return MMP_ERR_NONE;
		}			
		else {
			if (m_ulFilterCurrentCount >= m_ulFilterStart) {
				if (m_ulFilterCurrentCount < m_ulFilterEnd) {
					m_ulFilterCurrentCount++;
				}
				else {
					m_ulFilterCurrentCount++;
					return	MMP_ERR_NONE;
				}	
			}
		}
	}
	
	m_dbEntry->usAlbumNum = node->usMetadataCount;
	m_dbEntry->usTrackNum = node->usTreeNodeNumber;
	PRINTF("AlbumNum = %d. TrackNum = %d\r\n", m_dbEntry->usAlbumNum, m_dbEntry->usTrackNum);
	MEMCPY(m_dbEntry->usArtistName, node->data, TEXT_FRAME_MAX_LEN*2);
   	#if (FS_INPUT_ENCODE == UCS2)    
	print_ucs2("Artist", m_dbEntry->usArtistName);
	#endif
	m_dbEntry++;

	return	MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetDBMngrFileListActionAlbum
//------------------------------------------------------------------------------
/**
    @brief  Get the file list for artist
	@param[in] node : forest node
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetDBMngrFileListActionAlbum(MMPD_AUDIODB_BFNODE *node)
{
	#if (AUDIO_HOST_DB_EN == 1)
	if (m_ulFilterStringLength) {
		// filter function
		if (strcmp_w_limit(node->data, (MMP_BYTE *)m_ubFilterString, m_ulFilterStringLength)) {
			// not match
			return MMP_ERR_NONE;
		}			
		else {
			if (m_ulFilterCurrentCount >= m_ulFilterStart) {
				if (m_ulFilterCurrentCount < m_ulFilterEnd) {
					m_ulFilterCurrentCount++;
				}
				else {
					m_ulFilterCurrentCount++;
					return	MMP_ERR_NONE;
				}	
			}
		}
	}

	m_dbEntry->usTrackNum = node->usTreeNodeNumber;
	MEMCPY(m_dbEntry->usAlbumName, node->data, TEXT_FRAME_MAX_LEN*2);
	if (node->usMetadataCount == 1) {
		MEMCPY(m_dbEntry->usArtistName, node->metadata_root->data, TEXT_FRAME_MAX_LEN*2);
	}
	else {
		MEMCPY(m_dbEntry->usArtistName, "V\0a\0r\0i\0o\0u\0s\0 \0A\0r\0t\0i\0s\0t\0\0\0", TEXT_FRAME_MAX_LEN*2);
	}	
	PRINTF("%d : ", m_dbEntry->usTrackNum);
   	#if (FS_INPUT_ENCODE == UCS2)
	print_ucs2("Album", m_dbEntry->usAlbumName);
	print_ucs2("Artist", m_dbEntry->usArtistName);
	#endif
	m_dbEntry++;
	return	MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetDBMngrFileListActionGenre
//------------------------------------------------------------------------------
/**
    @brief  Get the file list for artist
	@param[in] node : forest node
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetDBMngrFileListActionGenre(MMPD_AUDIODB_BFNODE *node)
{
	#if (AUDIO_HOST_DB_EN == 1)
	if (m_ulFilterStringLength) {
		// filter function
		if (strcmp_w_limit(node->data, (MMP_BYTE *)m_ubFilterString, m_ulFilterStringLength)) {
			// not match
			return MMP_ERR_NONE;
		}			
		else {
			if (m_ulFilterCurrentCount >= m_ulFilterStart) {
				if (m_ulFilterCurrentCount < m_ulFilterEnd) {
					m_ulFilterCurrentCount++;
				}
				else {
					m_ulFilterCurrentCount++;
					return	MMP_ERR_NONE;
				}	
			}
		}
	}

	m_dbEntry->usTrackNum = node->usTreeNodeNumber;
	MEMCPY(m_dbEntry->usGenreName, node->data, AUDIODB_GENRE_SIZE);
	PRINTF("%d : ", m_dbEntry->usTrackNum);
   	#if (FS_INPUT_ENCODE == UCS2)
	print_ucs2("Genre", m_dbEntry->usGenreName);
	#endif
	m_dbEntry++;
	return	MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetDBMngrFileList
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
    @param[in] sortindex : sort index
	@param[out] dbentry : returned database structure
	@param[out] ulTotalCount : returned total count of the sortindex
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetDBMngrFileList(MMPS_AUDIO_DB_INDEX *sortindex, MMPS_AUDIO_DB_ENTRY* dbentry, MMP_ULONG *ulTotalCount)
{
	#if (AUDIO_HOST_DB_EN == 1)
	MMP_ERR		err;
	MMP_ULONG	file_size;

	switch (sortindex->sortType) {
	case MMPS_AUDIO_DB_SORT_ARTIST:
	case MMPS_AUDIO_DB_SORT_ALBUM:
	case MMPS_AUDIO_DB_SORT_GENRES:
		if (m_sortType != sortindex->sortType) {
            switch(m_sortType) {
            case MMPS_AUDIO_DB_SORT_TITLE:
                MMPD_AUDIODB_BTreeFree(&m_treeRoot);
                MMPD_AUDIODB_MemFree();
                break;
            case MMPS_AUDIO_DB_SORT_ARTIST:
            case MMPS_AUDIO_DB_SORT_ALBUM:
            case MMPS_AUDIO_DB_SORT_GENRES:
                MMPD_AUDIODB_BForestFree(&m_forestRoot);
                MMPD_AUDIODB_MemFree();
                break;
            }

			if (m_bDatabaseDirty) {
	    		MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
			    err = MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "a+b");
			    if (err) return err;
				err = MMPD_AUDIODB_CheckDatabaseDirty(&file_size);
			    if (err) return err;
				MMPD_AUDIODB_Finish();	
				
				if (!file_size)
					MMPD_AUDIODB_DeleteDatabase((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize);
				m_bDatabaseDirty = MMP_FALSE;
			}		

			//Initial database cache space, data base is always stores to SD card.
		    MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
		    err = MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "r+b");
    		if (err)
	    		return err;
			
			err = MMPD_AUDIODB_MemAlloc();
    		if (err)
	    		return err;

			switch(sortindex->sortType) {
			case MMPS_AUDIO_DB_SORT_ARTIST:
				// sort the tree : 1-artist 2-title/filename
				m_forestRoot = MMPD_AUDIODB_DBCreateForest(MMPD_AUDIODB_ARTIST, &m_ulForestNodeCount);
				// according to the artist tree, build album subtree
				MMPD_AUDIODB_DBMetadataCount(m_forestRoot, MMPD_AUDIODB_ARTIST, MMPD_AUDIODB_ALBUM);
				PRINTF("m_ulForestNodeCount = 0x%X\r\n", m_ulForestNodeCount);
				break;
			case MMPS_AUDIO_DB_SORT_ALBUM:
				// sort the tree : 1-album 2-title/filename
				m_forestRoot = MMPD_AUDIODB_DBCreateForest(MMPD_AUDIODB_ALBUM, &m_ulForestNodeCount);
				// according to the album tree, build artist subtree
				MMPD_AUDIODB_DBMetadataCount(m_forestRoot, MMPD_AUDIODB_ALBUM, MMPD_AUDIODB_ARTIST);
				PRINTF("m_ulForestNodeCount = 0x%X\r\n", m_ulForestNodeCount);
				break;
			case MMPS_AUDIO_DB_SORT_GENRES:
				// sort the tree : 1-genre 2-title/filename
				m_forestRoot = MMPD_AUDIODB_DBCreateForest(MMPD_AUDIODB_GENRE, &m_ulForestNodeCount);
				PRINTF("m_ulForestNodeCount = 0x%X\r\n", m_ulForestNodeCount);
				break;
			}
							
			if (m_forestRoot) {
				m_sortType = sortindex->sortType;
			}
			else {
				m_sortType = MMPS_AUDIO_DB_SORT_MAX;
				return	MMP_AUDIO_ERR_DATABASE_SORT;
			}

			MMPD_AUDIODB_Finish();	
		}		
		*ulTotalCount = m_ulForestNodeCount;

		m_dbEntry = dbentry;
		if (!m_dbEntry)
			return MMP_ERR_NONE;

		// set filter length to be zero to turn off the filter function;
		m_ulFilterStringLength = 0;

		switch(sortindex->sortType) {
		case MMPS_AUDIO_DB_SORT_ARTIST:
			MMPD_AUDIODB_SetBForestWalk(sortindex->usIndexId - 1, (sortindex->usIndexId + sortindex->ubIndexCount - 1), MMPS_AUDIO_GetDBMngrFileListActionArtist);
			break;
		case MMPS_AUDIO_DB_SORT_ALBUM:
			MMPD_AUDIODB_SetBForestWalk(sortindex->usIndexId - 1, (sortindex->usIndexId + sortindex->ubIndexCount - 1), MMPS_AUDIO_GetDBMngrFileListActionAlbum);
			break;
		case MMPS_AUDIO_DB_SORT_GENRES:
			MMPD_AUDIODB_SetBForestWalk(sortindex->usIndexId - 1, (sortindex->usIndexId + sortindex->ubIndexCount - 1), MMPS_AUDIO_GetDBMngrFileListActionGenre);
			break;
		}

		MMPD_AUDIODB_BForestWalk(m_forestRoot);
		break;
	case MMPS_AUDIO_DB_SORT_TITLE:
	case MMPS_AUDIO_DB_SORT_RATING:
	case MMPS_AUDIO_DB_SORT_PCNT:
		return MMP_AUDIO_ERR_PARAMETER;
	}

    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SearchDBMngrFileList
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
    @param[in] sortindex : sort index
	@param[out] dbentry : returned database structure
	@param[out] ulTotalCount : returned total count of the sortindex
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SearchDBMngrFileList(MMPS_AUDIO_DB_INDEX *sortindex, MMP_UBYTE *ubFilterString, MMP_ULONG ulFilterStringLength, 
										MMPS_AUDIO_DB_ENTRY* dbentry, MMP_ULONG *ulTotalCount)
{
	#if (AUDIO_HOST_DB_EN == 1)
	switch (sortindex->sortType) {
	case MMPS_AUDIO_DB_SORT_ARTIST:
	case MMPS_AUDIO_DB_SORT_ALBUM:
	case MMPS_AUDIO_DB_SORT_GENRES:
		if (m_sortType != sortindex->sortType) {
			return	MMP_AUDIO_ERR_DATABASE_FLOW;
		}		
		
		if (ulFilterStringLength == 0) {
			return	MMP_AUDIO_ERR_PARAMETER;
		}

		MEMCPY(m_ubFilterString, ubFilterString, ulFilterStringLength*2);
		m_ulFilterStringLength = ulFilterStringLength;

		m_ulFilterStart = sortindex->usIndexId - 1;
		m_ulFilterEnd = sortindex->usIndexId + sortindex->ubIndexCount - 1;
		m_ulFilterCurrentCount = 0;

		m_dbEntry = dbentry;
		if (!m_dbEntry)
			return MMP_ERR_NONE;
			
		if (sortindex->sortType == MMPS_AUDIO_DB_SORT_ARTIST)
			MMPD_AUDIODB_SetBForestWalk(0, 0, MMPS_AUDIO_GetDBMngrFileListActionArtist);
		if (sortindex->sortType == MMPS_AUDIO_DB_SORT_ALBUM)
			MMPD_AUDIODB_SetBForestWalk(0, 0, MMPS_AUDIO_GetDBMngrFileListActionAlbum);
		if (sortindex->sortType == MMPS_AUDIO_DB_SORT_GENRES)
			MMPD_AUDIODB_SetBForestWalk(0, 0, MMPS_AUDIO_GetDBMngrFileListActionGenre);

		MMPD_AUDIODB_BForestFilter(m_forestRoot);

		*ulTotalCount = m_ulFilterCurrentCount;
		break;
	case MMPS_AUDIO_DB_SORT_TITLE:
	case MMPS_AUDIO_DB_SORT_RATING:
	case MMPS_AUDIO_DB_SORT_PCNT:
		return MMP_AUDIO_ERR_PARAMETER;
	}

    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetDBMngrTrackListAction1
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
    @param[in] sortindex : sort index
	@param[in] dbentry : returned database structure
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetDBMngrTrackListAction1(MMPD_AUDIODB_BTNODE *node)
{
	#if (AUDIO_HOST_DB_EN == 1)
	MMPD_AUDIODB_AUDIOINFO infobuf;

	MMPD_AUDIODB_GetBTreeNodeInfo(&infobuf, node);

	if (m_ulFilterStringLength) {
		// filter function
		if (strcmp_w_limit(node->data, (MMP_BYTE *)m_ubFilterString, m_ulFilterStringLength)) {
			// not match
			return MMP_ERR_NONE;
		}			
		else {
			if (m_ulFilterCurrentCount >= m_ulFilterStart) {
				if (m_ulFilterCurrentCount < m_ulFilterEnd) {
					m_ulFilterCurrentCount++;
				}
				else {
					m_ulFilterCurrentCount++;
					return	MMP_ERR_NONE;
				}	
			}
		}
	}
	
	MEMCPY(m_trackEntry->usTitleName, infobuf.bTitle, TEXT_FRAME_MAX_LEN*2);
	MEMCPY(m_trackEntry->usFullPathName, infobuf.ubFullFileName, AUDIODB_MAX_FILE_NAME_SIZE*2);
	PRINTF("0x%X ", (MMP_ULONG)node);
   	#if (FS_INPUT_ENCODE == UCS2)
	print_ucs2("Title", m_trackEntry->usTitleName);
	print_ucs2("FullPath", m_trackEntry->usFullPathName);
	#endif
	m_trackEntry++;
	return	MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetDBMngrTrackList
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
    @param[in] sortindex : sort index
	@param[in] trackentry : returned database structure
	@param[out] ulTotalCount : returned the total count of requested sort index
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetDBMngrTrackList(MMPS_AUDIO_DB_INDEX *sortindex, MMPS_AUDIO_DB_TRACK *trackentry, MMP_ULONG *ulTotalCount)
{
	#if (AUDIO_HOST_DB_EN == 1)
	MMP_ERR	err;
    MMPD_AUDIODB_BFNODE		**forest_locator;
    MMPD_AUDIODB_BTNODE 	*BTreeRoot;
    MMPD_AUDIODB_OBJECT_PROPERTY groupindex;
    MMP_ULONG				file_size;

    switch (sortindex->sortType) {
    case MMPS_AUDIO_DB_SORT_TITLE:
        groupindex = MMPD_AUDIODB_OBJECT_NAME;
        break;
    case MMPS_AUDIO_DB_SORT_RATING:
        groupindex = MMPD_AUDIODB_RATING;
        break;
    case MMPS_AUDIO_DB_SORT_PCNT:
        groupindex = MMPD_AUDIODB_PLAYCNT;
        break;
    case MMPS_AUDIO_DB_SORT_ARTIST:
    case MMPS_AUDIO_DB_SORT_ALBUM:
    case MMPS_AUDIO_DB_SORT_GENRES:
        if (m_sortType != sortindex->sortType) {
            return  MMP_AUDIO_ERR_DATABASE_FLOW;
        }
        //Get requested forest node according to indexId first.
		forest_locator = MMPD_AUDIODB_GetBForestNodeLocator(&m_forestRoot, sortindex->usIndexId - 1);
		if (!forest_locator || !*forest_locator) {
			return	MMP_AUDIO_ERR_DATABASE_NOT_FOUND;
		}			
        
        *ulTotalCount = (*forest_locator)->usTreeNodeNumber;

        BTreeRoot = (*forest_locator)->root;
        break;
    }

	switch (sortindex->sortType) {
	case MMPS_AUDIO_DB_SORT_TITLE:
    case MMPS_AUDIO_DB_SORT_RATING:
    case MMPS_AUDIO_DB_SORT_PCNT:
		if (m_sortType != sortindex->sortType) {
			switch (m_sortType) {
			case MMPS_AUDIO_DB_SORT_ARTIST:
			case MMPS_AUDIO_DB_SORT_ALBUM:
			case MMPS_AUDIO_DB_SORT_GENRES:
				MMPD_AUDIODB_BForestFree(&m_forestRoot);
                MMPD_AUDIODB_MemFree();
				break;
			}

			if (m_bDatabaseDirty) {
	    		MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
			    err = MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "a+b");
			    if (err) return err;
				err = MMPD_AUDIODB_CheckDatabaseDirty(&file_size);
			    if (err) return err;
				MMPD_AUDIODB_Finish();	

				if (!file_size)
					MMPD_AUDIODB_DeleteDatabase((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize);

				m_bDatabaseDirty = MMP_FALSE;
			}		
		
			//Initial database cache space, data base is always stores to SD card.
		    MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
		    err = MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "r+b");
		    if (err)
		    	return err;

			err = MMPD_AUDIODB_MemAlloc();
    		if (err)
	    		return err;
		
            m_treeRoot = MMPD_AUDIODB_DBCreateTree(groupindex, &m_ulTreeNodeCount);
			if (m_treeRoot) {
				m_sortType = MMPS_AUDIO_DB_SORT_TITLE;
			}
			else {
				m_sortType = MMPS_AUDIO_DB_SORT_MAX;
				return	MMP_AUDIO_ERR_DATABASE_SORT;
			}
			
			MMPD_AUDIODB_Finish();	
		}		
		*ulTotalCount = m_ulTreeNodeCount;

        BTreeRoot = m_treeRoot;
	case MMPS_AUDIO_DB_SORT_ARTIST:
	case MMPS_AUDIO_DB_SORT_ALBUM:
	case MMPS_AUDIO_DB_SORT_GENRES:
		//Initial database cache space, data base is always stores to SD card.
		MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
		err = MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "r+b");
		if (err)
			return err;

		m_trackEntry = trackentry;
		if (!m_trackEntry)
			return MMP_ERR_NONE;

		m_ulFilterStringLength = 0;

		MMPD_AUDIODB_SetBTreeWalk(sortindex->usTrackId - 1, (sortindex->usTrackId + sortindex->ubIndexCount - 1), MMPS_AUDIO_GetDBMngrTrackListAction1);
		MMPD_AUDIODB_BTreeWalk(BTreeRoot);

	    MMPD_AUDIODB_Finish();

		break;
	}
	
    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SearchDBMngrTrackList
//------------------------------------------------------------------------------
/**
    @brief  Create the audio database index file
    @param[in] sortindex : sort index
	@param[in] dbentry : returned database structure
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SearchDBMngrTrackList(MMPS_AUDIO_DB_INDEX *sortindex, MMP_UBYTE *ubFilterString, MMP_ULONG ulFilterStringLength, 
											MMPS_AUDIO_DB_TRACK* trackentry, MMP_ULONG *ulTotalCount)
{
	#if (AUDIO_HOST_DB_EN == 1)
	MMPD_AUDIODB_BFNODE		**forest_locator = NULL;
	MMPD_AUDIODB_BTNODE 	*BTreeRoot = NULL;
	
	*ulTotalCount = 0;

	if (m_sortType != sortindex->sortType) {
		return	MMP_AUDIO_ERR_DATABASE_FLOW;
	}		

	if (ulFilterStringLength == 0 || sortindex->ubIndexCount == 0) {
		return	MMP_AUDIO_ERR_PARAMETER;
	}			

	MEMCPY(m_ubFilterString, ubFilterString, ulFilterStringLength*2);
	m_ulFilterStringLength = ulFilterStringLength;

	m_ulFilterStart = sortindex->usTrackId - 1;
	m_ulFilterEnd = sortindex->usTrackId + sortindex->ubIndexCount - 1;
	m_ulFilterCurrentCount = 0;

	m_trackEntry = trackentry;
	if (!m_trackEntry)
		return MMP_ERR_NONE;


	switch (sortindex->sortType) {
	case MMPS_AUDIO_DB_SORT_TITLE:
	case MMPS_AUDIO_DB_SORT_RATING:
	case MMPS_AUDIO_DB_SORT_PCNT:
		BTreeRoot = m_treeRoot;
		break;
	case MMPS_AUDIO_DB_SORT_ARTIST:
	case MMPS_AUDIO_DB_SORT_ALBUM:
	case MMPS_AUDIO_DB_SORT_GENRES:
		forest_locator = MMPD_AUDIODB_GetBForestNodeLocator(&m_forestRoot, sortindex->usIndexId - 1);
		if (!forest_locator || !*forest_locator) {
			return	MMP_AUDIO_ERR_DATABASE_NOT_FOUND;
		}			

		BTreeRoot = (*forest_locator)->root;
		break;
	}

	// Reinitial database for create the final sorted tree
    MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
   	MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "r+b");

	MMPD_AUDIODB_SetBTreeWalk(0, 0, MMPS_AUDIO_GetDBMngrTrackListAction1);
	MMPD_AUDIODB_BTreeFilter(BTreeRoot);

    MMPD_AUDIODB_Finish();
	    
    *ulTotalCount = m_ulFilterCurrentCount;

    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_DeleteDBMngrTrackList
//------------------------------------------------------------------------------
/**
    @brief  Delete from audio database with specified index
    @param[in] deleteindex : seleted index to delete
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_DeleteDBMngrTrackList(MMPS_AUDIO_DB_INDEX *deleteindex)
{
	#if (AUDIO_HOST_DB_EN == 1)
	MMPD_AUDIODB_BFNODE		**forest_locator;
	MMPD_AUDIODB_BTNODE     **tree_locator;
    MMPD_AUDIODB_AUDIOINFO  infobuf;
    MMP_ULONG				i, start_index, end_index;

	if (m_sortType != deleteindex->sortType) {
		return	MMP_AUDIO_ERR_DATABASE_FLOW;
	}

    MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
   	MMPD_AUDIODB_Initialize((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize, "a+b");

	switch (deleteindex->sortType) {
	case MMPS_AUDIO_DB_SORT_TITLE:
	case MMPS_AUDIO_DB_SORT_RATING:
	case MMPS_AUDIO_DB_SORT_PCNT:
		if (deleteindex->usTrackId) {
			tree_locator = MMPD_AUDIODB_GetBTreeNodeLocator(&m_treeRoot, deleteindex->usTrackId - 1);
			if (!tree_locator || !*tree_locator) {
				MMPD_AUDIODB_Finish();
				return	MMP_AUDIO_ERR_DATABASE_NOT_FOUND;
			}			

			// get the detele node information for delete
		    MMPD_AUDIODB_GetBTreeNodeInfo(&infobuf, *tree_locator);
			MMPD_AUDIODB_DirtyFile(&infobuf, *tree_locator);
			
			MMPD_AUDIODB_BTreeKillNode(tree_locator, (MMP_USHORT *)&m_ulTreeNodeCount);			
			m_bDatabaseDirty = MMP_TRUE;
		}
		else {
			// delete all
			MMPD_AUDIODB_Finish();
			MMPD_AUDIODB_DeleteDatabase((MMP_BYTE*)m_ubDBFileName, m_ulDBFileNameSize);
			m_treeRoot = NULL;
			m_ulTreeNodeCount = 0;
			m_bDatabaseDirty = MMP_FALSE;
		}
		break;
	case MMPS_AUDIO_DB_SORT_ARTIST:
	case MMPS_AUDIO_DB_SORT_ALBUM:
	case MMPS_AUDIO_DB_SORT_GENRES:
		forest_locator = MMPD_AUDIODB_GetBForestNodeLocator(&m_forestRoot, deleteindex->usIndexId - 1);
		if (!forest_locator || !*forest_locator) {
			MMPD_AUDIODB_Finish();
			return	MMP_AUDIO_ERR_DATABASE_NOT_FOUND;
		}			
		
		if (deleteindex->usTrackId) {
			start_index = deleteindex->usTrackId;
			end_index = deleteindex->usTrackId + 1;			
		}
		else {
			// delete all
			start_index = 1;
			end_index = (*forest_locator)->usTreeNodeNumber + 1;			
		}	
		
		for (i = start_index; i < end_index; i++) {
			if (deleteindex->usTrackId) {
				tree_locator = MMPD_AUDIODB_GetBTreeNodeLocator(&((*forest_locator)->root), i - 1);
			}	
			else {
				tree_locator = MMPD_AUDIODB_GetBTreeNodeLocator(&((*forest_locator)->root), 0);				
			}				
			if (!tree_locator || !*tree_locator) {
				MMPD_AUDIODB_Finish();
				return	MMP_AUDIO_ERR_DATABASE_NOT_FOUND;
			}			

			// delete the DBIndex file
		    MMPD_AUDIODB_GetBTreeNodeInfo(&infobuf, *tree_locator);
			MMPD_AUDIODB_DirtyFile(&infobuf, *tree_locator);

			if (deleteindex->sortType == MMPS_AUDIO_DB_SORT_ARTIST)
				MMPD_AUDIODB_KillTrack(tree_locator, forest_locator, MMPD_AUDIODB_ALBUM, (MMP_USHORT *)&m_ulForestNodeCount, &infobuf);
			if (deleteindex->sortType == MMPS_AUDIO_DB_SORT_ALBUM)		
				MMPD_AUDIODB_KillTrack(tree_locator, forest_locator, MMPD_AUDIODB_ARTIST, (MMP_USHORT *)&m_ulForestNodeCount, &infobuf);
			if (deleteindex->sortType == MMPS_AUDIO_DB_SORT_GENRES)		
				MMPD_AUDIODB_BTreeKillNode(tree_locator, &((*forest_locator)->usTreeNodeNumber));

			m_bDatabaseDirty = MMP_TRUE;

			m_ulTreeNodeCount -= 1;
		}
		break;
	}
	MMPD_AUDIODB_Finish();

    return MMP_ERR_NONE;
    #else
    return MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT;
    #endif
}

#if 0
void __AUDIO_FILE_INFO_OP__(){}
#endif

/// @end_ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetMp3Info
//------------------------------------------------------------------------------
/**
    @brief  Get MP3 media spec information
            This is an independent host parser for parsing media spec. So it could be used
            during playing the same file or another file.

    @param[in] *fileinfo: input file parameters
    @param[out] *mp3info : mp3 media spec information
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, 
            MMP_FS_ERR_READ_FAIL, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, MP3 host parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_MP3_Player_GetFileInfo(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMP_AUDIO_MP3_INFO  mp3info;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetMp3Info(&fileinfo, &mp3info);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetMp3Info(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MP3_INFO *mp3info)
{
    #if (MP3_HOST_PARSER_EN == 1)
    MMP_ERR ret = MMP_ERR_NONE;

    mp3info->usNotSupport = 1;
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support MP3 host parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
	ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
	if (ret)
		return ret;
    ret = MMPD_AUDPSR_GetMp3Info((MMP_AUDIO_MP3_INFO *)mp3info);
    if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetAACPlusInfo
//------------------------------------------------------------------------------
/**
    @brief  Using the Host parser to get the aacplus file information
            This is an independent host parser for parsing media spec. So it could be used
            during playing the same file or another file.
    @param[in] *fileinfo : input file parameters
    @param[out] *aacplusinfo : aacplus file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, AACPlus host parser will use
         4. @e fileinfo->ulFileID as file handler without file open and close.
    @pre DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_AACPlus_Player_GetFileInfo(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO     fileinfo;
        MMP_AUDIO_AACPLUS_INFO  aacplusinfo;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetAACPlusInfo(&fileinfo, &aacplusinfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetAACPlusInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AACPLUS_INFO *aacplusinfo)
{
    #if (AAC_HOST_PARSER_EN == 1)
    MMP_ERR ret;

    aacplusinfo->usNotSupport = 1;
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support AAC host parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
	ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
	if (ret)
		return ret;
    ret = MMPD_AUDPSR_GetAACPlusInfo((MMP_AUDIO_AACPLUS_INFO *)aacplusinfo);
	if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetWMAInfo
//------------------------------------------------------------------------------
/**
    @brief  Using the Host parser to get the wma file information
    This is an independent host parser for parsing media spec. So it could be used
    during playing the same file or another file.

    @param[in] *fileinfo : input file parameters
    @param[out] *wmainfo : wma file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, 
            MMP_AUDIO_ERR_NO_AUDIO_FOUND, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, WMA host parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_WMA_Player_GetFileInfo(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMP_AUDIO_WMA_INFO  wmainfo;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetWMAInfo(&fileinfo, &wmainfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetWMAInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WMA_INFO *wmainfo)
{
    #if (WMA_HOST_PARSER_EN == 1)
    MMP_ERR ret;

    wmainfo->usNotSupport = 1;
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support WMA host parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
	ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
	if (ret)
		return ret;
    ret = MMPD_AUDPSR_GetWMAInfo((MMP_AUDIO_WMA_INFO *)wmainfo);
	if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetWMATag
//------------------------------------------------------------------------------
/**
    @brief  Using the Host parser to get the wma file meta data
    This is an independent host parser for parsing WMA meta data. So it could be used
    during playing the same file or another file.

    @param[in] *fileinfo : input file parameters
    @param[out] *meta : meta data info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, WMA tag parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_WMA_Player_GetMetaData(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMPD_ID3_INFO       meta;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetWMATag(&fileinfo, &meta);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetWMATag(MMPS_AUDIO_FILEINFO *fileinfo, MMPD_ID3_INFO *meta)
{
    #if (WMA_HOST_PARSER_EN == 1)
    MMP_ERR ret;

    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support WMA tag parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
	ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
	if (ret)
		return ret;
    ret = MMPD_AUDPSR_GetWMAMetaData(meta);
	if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetWAVInfo
//------------------------------------------------------------------------------
/**
    @brief  Using the Host parser to get the wav file information
    This is an independent host parser for parsing media spec. So it could be used
    during playing the same file or another file.

    @param[in] *fileinfo : input file parameters
    @param[out] *wavinfo : wav file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, 
            MMP_FS_ERR_READ_FAIL, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, WAV host parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_WAV_Player_GetFileInfo(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMP_AUDIO_WAV_INFO  wavinfo;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetWAVInfo(&fileinfo, &wavinfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetWAVInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WAV_INFO *wavinfo)
{
    #if (WAV_HOST_PARSER_EN == 1)
    MMP_ERR ret;

    wavinfo->usNotSupport = 1;
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support WAV host parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
    ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
    if (ret)
        return ret;
    ret = MMPD_AUDPSR_GetWAVInfo((MMP_AUDIO_WAV_INFO *)wavinfo);
    if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetOGGInfo
//------------------------------------------------------------------------------
/**
    @brief  Using the Host parser to get the ogg file information
    This is an independent host parser for parsing media spec. So it could be used
    during playing the same file or another file.

    @param[in] *fileinfo : input file parameters
    @param[out] *ogginfo : ogg file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, OGG host parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_OGG_Player_GetFileInfo(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMP_AUDIO_OGG_INFO  ogginfo;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetOGGInfo(&fileinfo, &ogginfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetOGGInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_OGG_INFO *ogginfo)
{
    #if (OGG_HOST_PARSER_EN == 1)
    MMP_ERR ret;

    ogginfo->usNotSupport = 1;
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support OGG host parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
	ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
	if (ret)
		return ret;
    ret = MMPD_AUDPSR_GetOGGInfo((MMP_AUDIO_OGG_INFO *)ogginfo);
	if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetRAInfo
//------------------------------------------------------------------------------
/**
    @brief  Using the Host parser to get the ra file information
    This is an independent host parser for parsing media spec. So it could be used
    during playing the same file or another file.

    @param[in] *fileinfo : input file parameters
    @param[out] *rainfo : ra file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, RA host parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_RA_Player_GetFileInfo(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMP_AUDIO_RA_INFO   rainfo;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetRAInfo(&fileinfo, &rainfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetRAInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_RA_INFO *rainfo)
{
    #if (RA_HOST_PARSER_EN == 1)
    MMP_ERR ret;

    rainfo->usNotSupport = 1;
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support RA host parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
	ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
	if (ret)
		return ret;
    ret = MMPD_AUDPSR_GetRAInfo((MMP_AUDIO_RA_INFO *)rainfo);
	if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ParserGetAMRInfo
//------------------------------------------------------------------------------
/**
    @brief  Using the Host parser to get the amr file information
    This is an independent host parser for parsing media spec. So it could be used
    during playing the same file or another file.

    @param[in] *fileinfo : input file parameters
    @param[out] *amrinfo : amr file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_OPENFILE_FAIL, 
            MMP_FS_ERR_READ_FAIL, MMP_AUDIO_ERR_UNSUPPORT_FORMAT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetParserCacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, AMR host parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_AMR_Player_GetFileInfo(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMP_AUDIO_AMR_INFO  amrinfo;

        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetParserCacheBuf((MMP_ULONG)ubHostBuf, 8*1024);
        MMPS_AUDIO_ParserGetAMRInfo(&fileinfo, &amrinfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_ParserGetAMRInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AMR_INFO *amrinfo)
{
    #if (AMR_HOST_PARSER_EN == 1)
    MMP_ERR ret;

    amrinfo->usNotSupport = 1;
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support AMR host parsing in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }
    ret = MMPD_AUDPSR_Initialize(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID);
    if (ret)
        return ret;
    ret = MMPD_AUDPSR_GetAMRInfo((MMP_AUDIO_AMR_INFO *)amrinfo);
    if (fileinfo->usFileNameLength)
	    MMPD_AUDPSR_Finish(MMP_TRUE);
    else
        MMPD_AUDPSR_Finish(MMP_FALSE); //don't need to close file

    return ret;
    #else
    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    #endif
}

#if 0
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetMP3PlayID3CacheBuf
//------------------------------------------------------------------------------
/**
    @brief  Set cache buffer address and size for parsing MP3 ID3 tag.
            Larger cache with size @e ulMaxCacheSize is used for parsing 
            APIC frames and for shifting file content in editing ID3 tag.
    @param[in] ulCacheAddr : host buffer address used as 
    @param[in] ulCacheSize : cache size (must be a multiple of 2)
    @param[in] ulMaxCacheSize: maximum cacahe size can be used for better performance
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER

    @pre For better performance, @e ulCacheSize and @e ulMaxCacheSize should be
         a multiple of 512 Byte.
*/
MMP_ERR MMPS_AUDIO_SetMP3PlayID3CacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize,
                                         MMP_ULONG ulMaxCacheSize)
{
#if (MP3_P_EN) || (VMP3_P_EN)
    if (ulCacheSize > ulMaxCacheSize) {
        return MMP_AUDIO_ERR_PARAMETER;
    }
    return MMPD_ID3_SetParseCacheBuf(ulCacheAddr, ulCacheSize, ulMaxCacheSize);
#else
	return MMP_ERR_NONE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetMP3PlayID3Tag
//------------------------------------------------------------------------------
/**
    @brief  Get ID3 tag
            This is an independent host parser for parsing ID3 tag. So it could 
            be used during playing the same file or another file. 
            AAC/MP3 format might use ID3 tag to store their meta info.

    @param[in] *fileinfo: input file parameters
    @param[in] *CallBackFunc: callback function to allocate memory for APIC
    @param[out] *id3info : id3 tag information
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_FS_ERR_FILE_SEEK_FAIL, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetMP3PlayID3CacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. If @e fileinfo->usFileNameLength is set to zero, MP3 host parser will use
            @e fileinfo->ulFileID as file handler without file open and close.
    @pre 4. DRM IV/Key/header offset settings have beed set for DRM file parsing.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    AIT_Audio_Player_GetID3(MMP_BYTE *filename, MMP_ULONG ulFileID, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMPD_ID3_INFO       id3info;

        MEMSET(&id3info, 0, sizeof(id3info));
        STRCPY(fileinfo.bFileName, filename);
        if (ulFindID == 0) {
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
            fileinfo.ulFileID = 0;
        }
        else {
            fileinfo.usFileNameLength = 0;
            fileinfo.ulFileID = ulFileID;
        }
        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        if (drminfo == NULL) {
            MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPS_AUDIO_SetDRMIV(drminfo->ucVEC, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMKEY(drminfo->Key, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMHeaderOff(drminfo->uDataStartPos + 0x10, MMPD_OMADRM_FOR_PARSER);
            MMPS_AUDIO_SetDRMEnable(MMP_TRUE, MMPD_OMADRM_FOR_PARSER);
        }

        MMPS_AUDIO_SetMP3PlayID3CacheBuf((MMP_ULONG)ubHostBuf, 1024, 8*1024);
        MMPS_AUDIO_GetMP3PlayID3Tag(&fileinfo, &id3info, MMPC_System_AllocZeroMem);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_GetMP3PlayID3Tag(MMPS_AUDIO_FILEINFO *fileinfo, MMPD_ID3_INFO *id3info, 
                                    AllocZeroMemCBFunc *CallBackFunc)
{
#if (MP3_P_EN) || (VMP3_P_EN)
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_ID3_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_ID3_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support ID3 tag in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }

    return MMPD_ID3_GetInfo(fileinfo->bFileName, fileinfo->usFileNameLength, fileinfo->ulFileID, 
                           id3info, 0, CallBackFunc, NULL);
#else
	return MMP_ERR_NONE;
#endif
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetMP3PlayID3Tag
//------------------------------------------------------------------------------
/**
    @brief  Set MP3 Play ID3 tag
    @param[in] *fileinfo: input file parameters
    @param[in] frameType: The ID3 frame type to set
    @param[in] payload: payload (data) of frame
    @param[in] payloadLen: payload (data) length
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_INSUFFICIENT_BUF, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_FS_ERR_WRITE_FAIL, MMP_FS_ERR_FILE_SEEK_FAIL, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1. Cache buffer address and size have been set by @ref MMPS_AUDIO_SetMP3PlayID3CacheBuf.
    @pre 2. @e fileinfo->mediaPath has been set properly.
    @pre 3. DRM files are not support.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE ubHostBuf[8*1024];
    //Set POPM (rating/play count) frame in ID3
    AIT_MP3_Player_SetMetaPOPM(MMP_BYTE *filename, MMP_UBYTE ubRating, MMP_LONG lPlayCnt, MMP_BOOL bCardMode)
    {
        MMPS_AUDIO_FILEINFO fileinfo;
        MMP_UBYTE           ubPopmFrame[6];

        STRCPY(fileinfo.bFileName, filename);
        fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);
        fileinfo.ulFileID = 0;

        if (bCardMode) {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_CARD, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_HOST_FILE;
            MMPS_AUDIO_SetDRMPath(MMPS_AUDIO_MEDIA_PATH_HOST_FILE, MMPD_OMADRM_FOR_PARSER);
        }
        MMPS_AUDIO_SetDRMEnable(MMP_FALSE, MMPD_OMADRM_FOR_PARSER);

        //set POPM frame content
        ubPopmFrame[0] = 0x00;      //Email: set empty (null terminated string)
        ubPopmFrame[1] = ubRating;  //Rating: 1 byte
        ubPopmFrame[2] = (ulPlayCnt & 0xFF000000) >> 24; //Play count: 4 bytes
        ubPopmFrame[3] = (ulPlayCnt & 0x00FF0000) >> 16;
        ubPopmFrame[4] = (ulPlayCnt & 0x0000FF00) >> 8;
        ubPopmFrame[5] = (ulPlayCnt & 0x000000FF);

        MMPS_AUDIO_SetMP3PlayID3CacheBuf((MMP_ULONG)ubHostBuf, 1024, 8*1024);
        MMPS_AUDIO_SetMP3PlayID3Tag(&fileinfo, MMPD_ID3_FRAME_POPM, ubPopmFrame, sizeof(ubPopmFrame));
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_SetMP3PlayID3Tag(MMPS_AUDIO_FILEINFO *fileinfo, MMPD_ID3_FRAME_ID frameType, MMP_UBYTE *payload, MMP_LONG payloadLen)
{
#if (MP3_P_EN) || (VMP3_P_EN)
    switch(fileinfo->mediaPath) {
    case MMPS_AUDIO_MEDIA_PATH_CARD:
        MMPD_ID3_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        break;
    case MMPS_AUDIO_MEDIA_PATH_HOST_FILE:
        MMPD_ID3_SetMediaPath(MMPD_AUDIO_PLAY_FROM_MEM);
        break;
    case MMPS_AUDIO_MEDIA_PATH_MEM:
    case MMPS_AUDIO_MEDIA_PATH_MMP_MEM:
        PRINTF("Not support ID3 tag in pure memory mode yet\r\n");
    default:
        return MMP_AUDIO_ERR_PARAMETER;
    }

    return MMPD_ID3_EditTag(fileinfo->bFileName, fileinfo->usFileNameLength, frameType, payload, payloadLen);
#else
	return MMP_ERR_NONE;
#endif
}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeWMAPlay
//  Description :
//------------------------------------------------------------------------------
/** @brief  Initialize WMA Play
            The function initialize the WMA Play. It will return the WMA media information,
            and prepare for WMA playback.
    @param[in] *fileinfo : input file parameters
    @param[out] *wmainfo : wma file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_AUDIO_ERR_UNSUPPORT_FORMAT, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: Audio output path has been set by @ref MMPS_AUDIO_SetMediaPath.
    @pre 2: DRM IV/Key/header offset settings have beed set for DRM file playback.
    @pre 3: @e bFileName and @e usFileNameLength in @e fileinfo must be set properly.
    @pre 4: For host file mode, @e ubBuf and @e ulBufSize must also be set properly.
            @e ulBufSize must be a multiple of 1024.

    @post 1: After initialized, playback can be supported or not will be reported by FW parser.
             For unsupport file located at host storage, file will be closed directly.
    @post 2: After initialized successfully, @ref MMPS_AUDIO_StopWMAPlay must be called to close
             file located at host storage, even @ref MMPS_AUDIO_StartWMAPlay was not called.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE   m_ubHostBuf[200*1024];
    AIT_WMA_Player_Init(MMP_BYTE *filename, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO         fileinfo;
        MMP_AUDIO_WMA_INFO          wmainfo;

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
        MMPS_AUDIO_InitializeWMAPlay(&fileinfo, &wmainfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_InitializeWMAPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WMA_INFO *wmainfo)
{
    MMP_ERR     status;
    MMP_ULONG64 filesize;
    MMP_ULONG   readsize;
    MMP_ULONG	version;
    #if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
	MMP_ULONG	drmOffset;

	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
	MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_WMA_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);

	MMPD_AUDIO_GetWMAVersion(&version);

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_WMA_P_CARD_MODE);
        status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            wmainfo->usNotSupport = 1;
            return status;
        }
    }
    else if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (fileinfo->ubBuf == NULL || fileinfo->ulBufSize == 0) {
            PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (fileinfo->ulBufSize & 0x3FF) {
                PRINTF("Please set ulBufSize to be multiple of 1024\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
        }
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        else
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_WMA_P_MEM_MODE);
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }

        m_ubAudioPlayBuf = fileinfo->ubBuf;

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
            m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
            m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            MMPC_FS_FileOpen(m_bAudioPlayFileName, "rb", &m_ulAudioPlayFileHandle);
            MMPC_FS_FileGetSize(m_ulAudioPlayFileHandle, &filesize);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	filesize -= drmOffset;
                filesize = (filesize >> 4) << 4; //16-byte alignment
            }
            #endif
            if (m_ulAudioPlayBufSize > filesize)
            	m_ulAudioPlayBufSize = filesize;
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	MMPC_FS_FileSeek((void *)m_ulAudioPlayFileHandle, (MMP_LONG64)drmOffset, MMPS_FS_SEEK_SET);
            }
			#endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            m_ulAudioPlayFileSize = filesize;
        }
        else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) {
            m_ulAudioPlayFileHandle = 0;
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }
        else {
            m_ulAudioPlayFileHandle = 0;
            m_ubAudioPlayBuf = 0;
            m_ulAudioPlayBufSize = 0;
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }
        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
        else {
            MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        }

       	MMPD_AUDIO_InitPlaySeekFlag();
		MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }

	MMPD_AUDIO_SetWMAPlayTime(0);

	MMPD_AUDIO_GetWMAFileInfo((MMP_AUDIO_WMA_INFO *)wmainfo);
	if(wmainfo->ulBitRate     == 0 ||
		wmainfo->ulSampleRate == 0 ||
		wmainfo->ulTotalTime  == 0 ||
		wmainfo->usChans      == 0 ||
		wmainfo->usNotSupport == 1) {
		wmainfo->usNotSupport = 1;
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
		        MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
	   	    }	
        }
		return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
	}

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartWMAPlay
//------------------------------------------------------------------------------
/**
    @brief  Start WMA Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUDIO_InitializeWMAPlay was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.

    <b>Sample codes:</b><br>
    @code
    //WMA play has been initialized, start playback with specified starting time.
    AIT_WMA_Player_Start(MMP_ULONG ulStartTimeMs)
    {
        if (ulStartTimeMs)
            MMPS_AUDIO_SetWMAPlayTime(ulStartTimeMs);
        MMPS_AUDIO_StartWMAPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_StartWMAPlay(void* callBackFunc, void* context)
{
    MMP_ULONG	readsize;
    MMP_ULONG	startPos = 0;
    #if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
    MMP_UBYTE   drmIV[16];
	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    if (drmEn){
	    MMPD_AUDIO_GetDRMOffset(&startPos, MMPD_OMADRM_FOR_PLAY);
    }
    #endif

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)startPos - 16, MMPS_FS_SEEK_SET);
                MMPC_FS_FileRead(m_ulAudioPlayFileHandle, drmIV, 16, &readsize);
                MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
            }
            else {
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)startPos, MMPS_FS_SEEK_SET);
            }
            #else
            MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)startPos, MMPS_FS_SEEK_SET);
            #endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }
        // restart for decode from the top of the memory
        MMPD_AUDIO_SetPlayReadPtr(0, 0);
        MMPS_AUDIO_TransferDataHostToDev();
       	MMPD_AUDIO_InitPlaySeekFlag();
    }
    else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_SetPlayReadPtr(0, 0);
        MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        MMPD_AUDIO_InitPlaySeekFlag();
    }

    return MMPD_AUDIO_StartAudioPlay(callBackFunc, context);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseWMAPlay
//------------------------------------------------------------------------------
/**
    @brief  Pause WMA Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_PauseWMAPlay(void)
{
    MMP_ERR status;
    MMP_USHORT play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if (status != MMP_ERR_NONE) {
        return status;
    }

    do {
        status = MMPD_AUDIO_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
    } while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeWMAPlay
//------------------------------------------------------------------------------
/**
    @brief  Resume WMA Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_ResumeWMAPlay(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopWMAPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop WMA Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_StopWMAPlay(void)
{
    MMP_ERR status;

    status = MMPD_AUDIO_StopAudioPlay();
    if (status != MMP_ERR_NONE) {
	    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			if (m_ulAudioPlayFileHandle) {	
	        	MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
			}	
	    }
	    
        goto WMA_STOP_EXIT;
    }

	status = MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
		if (m_ulAudioPlayFileHandle) {	
			MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
			m_ulAudioPlayFileHandle = 0;
		}	
    }

WMA_STOP_EXIT :
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWMAPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get WMA Current Play Time
    @param[out] *usTimeRatio : (current time) / (total time)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetWMAPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    return MMPD_AUDIO_GetWMAPlayTime(usTimeRatio,ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWMAPlaySpectrum
//------------------------------------------------------------------------------
/**
    @brief  Get WMA Play Spectrum
    @param[out] usSpectrum[] : spectrum data (32 words = 64 bytes)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be in playing state before get spectrum, otherwise,
         unexpected spectrum values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetWMAPlaySpectrum(MMP_USHORT usSpectrum[])
{
    return MMPD_AUDIO_GetPlaySpectrum(usSpectrum);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetWMAPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set WMA Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre This function should be used when playback was in stopped state,
         either stopped by @ref MMPS_AUDIO_StopWMAPlay or due to EOF.
    @post You can @b NOT get updated play time until you restart playback
          by @ref MMPS_AUDIO_StartWMAPlay.

    <b>Sample codes:</b><br>
    @code
    AIT_WMA_Player_Seek(MMP_ULONG ulTargetTimeMs)
    {
        MMPS_AUDIO_PLAY_STATUS  play_status;

        //Stop playback first if needed. For host file mode, file will be closed.
        MMPS_AUDIO_GetPlayStatus(&play_status);
        if (play_status != MMPS_AUDIO_PLAY_STOP)
            MMPS_AUDIO_StopWMAPlay();

        //Seek to specified position. For host file mode, file will be re-opened.
        MMPS_AUDIO_SetWMAPlayTime(ulStartTimeMs);
        MMPS_AUDIO_StartWMAPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_SetWMAPlayTime(MMP_ULONG ulPlayTime)
{
    if ((m_ulAudioPlayFileHandle == 0) && (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
        MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }
    return MMPD_AUDIO_SetWMAPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWMAPlayPosition
//------------------------------------------------------------------------------
/**
    @brief  Get WMA Play Current Position
    @param[out] *ulPos : position (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play position. Otherwise, unexpected values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetWMAPlayPosition(MMP_ULONG *ulPos)
{
    return MMPD_AUDIO_GetPlayPosition(ulPos);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeRAPlay
//  Description :
//------------------------------------------------------------------------------
/** @brief  Initialize RealAudio Play
            The function initialize the Real audio Play. It will return the RA media information,
            and prepare for RA playback.
    @param[in] *fileinfo : input file parameters
    @param[out] *rainfo : ra file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_AUDIO_ERR_UNSUPPORT_FORMAT, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: Audio output path has been set by @ref MMPS_AUDIO_SetMediaPath.
    @pre 2: DRM IV/Key/header offset settings have beed set for DRM file playback.
    @pre 3: @e bFileName and @e usFileNameLength in @e fileinfo must be set properly.
    @pre 4: For host file mode, @e ubBuf and @e ulBufSize must also be set properly.
            @e ulBufSize must be a multiple of 1024.

    @post 1: After initialized, playback can be supported or not will be reported by FW parser.
             For unsupport file located at host storage, file will be closed directly.
    @post 2: After initialized successfully, @ref MMPS_AUDIO_StopRAPlay must be called to close
             file located at host storage, even @ref MMPS_AUDIO_StartRAPlay was not called.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE   m_ubHostBuf[200*1024];
    AIT_RA_Player_Init(MMP_BYTE *filename, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO         fileinfo;
        MMP_AUDIO_RA_INFO           rainfo;

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
        MMPS_AUDIO_InitializeRAPlay(&fileinfo, &rainfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_InitializeRAPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_RA_INFO *rainfo)
{
    MMP_ERR     status;
    MMP_ULONG64 filesize;
    MMP_ULONG   readsize;
    #if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
	MMP_ULONG	drmOffset;

	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
	MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);	
    #endif

    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_RA_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_RA_P_CARD_MODE);
        status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            rainfo->usNotSupport = 1;
            return status;
        }
    }
    else if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if ((fileinfo->ubBuf == NULL) || (fileinfo->ulBufSize == 0)) {
            PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (fileinfo->ulBufSize & 0x3FF) {
                PRINTF("Please set ulBufSize to be multiple of 1024\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
        }
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        else
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_RA_P_MEM_MODE);
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }

        m_ubAudioPlayBuf = fileinfo->ubBuf;

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
            m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
            m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            MMPC_FS_FileOpen(m_bAudioPlayFileName, "rb", &m_ulAudioPlayFileHandle);
            MMPC_FS_FileGetSize(m_ulAudioPlayFileHandle, &filesize);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	filesize -= drmOffset;
                filesize = (filesize >> 4) << 4; //16-byte alignment
            }
            #endif
            if (m_ulAudioPlayBufSize > filesize)
            	m_ulAudioPlayBufSize = filesize;
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	MMPC_FS_FileSeek((void *)m_ulAudioPlayFileHandle, (MMP_LONG64)drmOffset, MMPS_FS_SEEK_SET);
            }
			#endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            m_ulAudioPlayFileSize = filesize;
        }
        else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) {
            m_ulAudioPlayFileHandle = 0;
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }
        else {
            m_ulAudioPlayFileHandle = 0;
            m_ubAudioPlayBuf = 0;
            m_ulAudioPlayBufSize = 0;
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }

        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
        else {
            MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        }

       	MMPD_AUDIO_InitPlaySeekFlag();
		MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }

	MMPD_AUDIO_GetRAFileInfo((MMP_AUDIO_RA_INFO *)rainfo);
	if (rainfo->ulBitRate    == 0 ||
        rainfo->usSampleRate == 0 || 
        rainfo->ulTotalTime  == 0 || 
        rainfo->usChans      == 0 ) {
		rainfo->usNotSupport = 1;
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
		        MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
	   	    }	
        }
		return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
	}
	MMPD_AUDIO_SetRAPlayTime(0);
	
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartRAPlay
//------------------------------------------------------------------------------
/**
    @brief  Start RealAudio Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUDIO_InitializeRAPlay was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.

    <b>Sample codes:</b><br>
    @code
    //RA play has been initialized, start playback with specified starting time.
    AIT_RA_Player_Start(MMP_ULONG ulStartTimeMs)
    {
        if (ulStartTimeMs)
            MMPS_AUDIO_SetRAPlayTime(ulStartTimeMs);
        MMPS_AUDIO_StartRAPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_StartRAPlay(void* callBackFunc, void* context)
{
    return MMPD_AUDIO_StartAudioPlay(callBackFunc, context);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseRAPlay
//------------------------------------------------------------------------------
/**
    @brief  Pause RealAudio Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_PauseRAPlay(void)
{
    MMP_ERR     status;
    MMP_USHORT  play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if (status != MMP_ERR_NONE) {
        return status;
    }

    do {
        status = MMPD_AUDIO_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
	} while (play_status != DECODE_OP_PAUSE);
    
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeRAPlay
//------------------------------------------------------------------------------
/**
    @brief  Resume RealAudio Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_ResumeRAPlay(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopRAPlay
//------------------------------------------------------------------------------
/** 
    @brief  Stop RealAudio Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_StopRAPlay(void)
{
    MMP_ERR status;

	status = MMPD_AUDIO_StopAudioPlay();
    if (status != MMP_ERR_NONE) {
        goto RA_STOP_EXIT;
    }    

    status = MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
		if (m_ulAudioPlayFileHandle) {	
			MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
			m_ulAudioPlayFileHandle = 0;
		}	
    }

RA_STOP_EXIT:

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetRAPlayTime
//------------------------------------------------------------------------------
/** 
    @brief  Get RealAudio Current Play Time
    @param[out] *usTimeRatio : (current time) / (total time)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetRAPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    return MMPD_AUDIO_GetRAPlayTime(usTimeRatio,ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRAPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set RealAudio Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre This function should be used when playback was in stopped state,
         either stopped by @ref MMPS_AUDIO_StopRAPlay or due to EOF.
    @post You can @b NOT get updated play time until you restart playback
          by @ref MMPS_AUDIO_StartRAPlay.

    <b>Sample codes:</b><br>
    @code
    AIT_RA_Player_Seek(MMP_ULONG ulTargetTimeMs)
    {
        MMPS_AUDIO_PLAY_STATUS  play_status;

        //Stop playback first if needed. For host file mode, file will be closed.
        MMPS_AUDIO_GetPlayStatus(&play_status);
        if (play_status != MMPS_AUDIO_PLAY_STOP)
            MMPS_AUDIO_StopRAPlay();

        //Seek to specified position. For host file mode, file will be re-opened.
        MMPS_AUDIO_SetRAPlayTime(ulStartTimeMs);
        MMPS_AUDIO_StartRAPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_SetRAPlayTime(MMP_ULONG ulPlayTime)
{
    if ((m_ulAudioPlayFileHandle == 0) && (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
        MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }
    return MMPD_AUDIO_SetRAPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeOGGPlay
//------------------------------------------------------------------------------
/**
    @brief  Initialize OGG Play
            The function initialize the OGG Play. It will return the OGG media information,
            and prepare for OGG playback.
    @param[in] *fileinfo : input file parameters
    @param[out] *ogginfo : ogg file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_AUDIO_ERR_UNSUPPORT_FORMAT, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: Audio output path has been set by @ref MMPS_AUDIO_SetMediaPath.
    @pre 2: DRM IV/Key/header offset settings have beed set for DRM file playback.
    @pre 3: @e bFileName and @e usFileNameLength in @e fileinfo must be set properly.
    @pre 4: For host file mode, @e ubBuf and @e ulBufSize must also be set properly.
            @e ulBufSize must be a multiple of 1024.

    @post 1: After initialized, playback can be supported or not will be reported by FW parser.
             For unsupport file located at host storage, file will be closed directly.
    @post 2: After initialized successfully, @ref MMPS_AUDIO_StopOGGPlay must be called to close
             file located at host storage, even @ref MMPS_AUDIO_StartOGGPlay was not called.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE   m_ubHostBuf[200*1024];
    AIT_OGG_Player_Init(MMP_BYTE *filename, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO         fileinfo;
        MMP_AUDIO_OGG_INFO          ogginfo;

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
        MMPS_AUDIO_InitializeOGGPlay(&fileinfo, &ogginfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_InitializeOGGPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_OGG_INFO *ogginfo)
{
    MMP_ERR     status;
    MMP_ULONG64 filesize;
    MMP_ULONG   readsize;
    MMP_AUDIO_OGG_TAG_INFO taginfo;

    #if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
	MMP_ULONG	drmOffset;

	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
	MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

	MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_OGG_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);
    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_OGG_P_CARD_MODE);
        status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            ogginfo->usNotSupport = 1;
            return status;
        }
    }
    else if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (fileinfo->ubBuf == NULL || fileinfo->ulBufSize == 0) {
            PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (fileinfo->ulBufSize & 0x3FF) {
                PRINTF("Please set ulBufSize to be multiple of 1024\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
        }
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        else
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_OGG_P_MEM_MODE);
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) { //set input bitstream addr and size
            MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }

        m_ubAudioPlayBuf = fileinfo->ubBuf;

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
            m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
            m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            status = MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", (void *)&m_ulAudioPlayFileHandle);
            if(status != MMP_ERR_NONE) {
                return status;
			}
            MMPC_FS_FileGetSize((void *)m_ulAudioPlayFileHandle, &filesize);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                filesize -= drmOffset;
                filesize = (filesize >> 4) << 4; //16-byte alignment
            }
            #endif
            if (m_ulAudioPlayBufSize > filesize)
                m_ulAudioPlayBufSize = filesize;
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                MMPC_FS_FileSeek((void *)m_ulAudioPlayFileHandle, (MMP_LONG64)drmOffset, MMPS_FS_SEEK_SET);
            }
            #endif
            status = MMPC_FS_FileRead((void *)m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            if (status != MMP_ERR_NONE) {
                return status;
			}
            m_ulAudioPlayFileSize = filesize;
        }
        else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) {
            m_ulAudioPlayFileHandle = 0;
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }
        else {
            m_ulAudioPlayFileHandle = 0;
            m_ubAudioPlayBuf = 0;
            m_ulAudioPlayBufSize = 0;
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }

        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
        else {
            MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        }

        MMPD_AUDIO_InitPlaySeekFlag();
        MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }
    MMPD_AUDIO_SetOGGPlayTime(0);

    MMPD_AUDIO_GetOGGFileInfo((MMP_AUDIO_OGG_INFO *)ogginfo);
    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        // Must call MMPD_AUDIO_GetOGGFileInfo() first
        MMPD_AUDIO_GetOGGTagInfo((MMP_AUDIO_OGG_TAG_INFO *)&taginfo);
    }

    PRINTF("ogginfo->ulBitRate: %d\r\n", ogginfo->ulBitRate);
    PRINTF("ogginfo->usSampleRate: %d\r\n", ogginfo->usSampleRate);
    PRINTF("ogginfo->usChans: %d\r\n", ogginfo->usChans);
    PRINTF("ogginfo->ulTotalTime: %d\r\n", ogginfo->ulTotalTime);    
    PRINTF("ogginfo->usVbrInfo: %x\r\n", ogginfo->usVbrInfo);    
    PRINTF("ogginfo->usNotSupport: %x\r\n", ogginfo->usNotSupport);  
    if (ogginfo->usNotSupport) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
		        MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
	   	    }	
        }
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartOGGPlay
//------------------------------------------------------------------------------
/**
    @brief  Start OGG Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUDIO_InitializeOGGPlay was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.

    <b>Sample codes:</b><br>
    @code
    //OGG play has been initialized, start playback with specified starting time.
    AIT_OGG_Player_Start(MMP_ULONG ulStartTimeMs)
    {
        if (ulStartTimeMs)
            MMPS_AUDIO_SetOGGPlayTime(ulStartTimeMs);
        MMPS_AUDIO_StartOGGPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_StartOGGPlay(void* callBackFunc, void* context)
{
    MMP_ULONG	readsize;
    MMP_ULONG   startPos = 0;
    #if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
    MMP_UBYTE   drmIV[16];

	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    if (drmEn) {
	    MMPD_AUDIO_GetDRMOffset(&startPos, MMPD_OMADRM_FOR_PLAY);
    }
    #endif

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)startPos - 16, MMPS_FS_SEEK_SET);
                MMPC_FS_FileRead(m_ulAudioPlayFileHandle, drmIV, 16, &readsize);
                MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
            }
            else {
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)startPos, MMPS_FS_SEEK_SET);
            }
            #else
            MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)startPos, MMPS_FS_SEEK_SET);
            #endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }
        // restart for decode from the top of the memory
        MMPD_AUDIO_SetPlayReadPtr(0, 0);
        MMPS_AUDIO_TransferDataHostToDev();
       	MMPD_AUDIO_InitPlaySeekFlag();
    }
    else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_SetPlayReadPtr(0, 0);
        MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        MMPD_AUDIO_InitPlaySeekFlag();
    }

    return MMPD_AUDIO_StartAudioPlay(callBackFunc, context);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseOGGPlay
//------------------------------------------------------------------------------
/**
    @brief  Pause OGG Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_PauseOGGPlay(void)
{
    MMP_ERR status;
    MMP_USHORT play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if (status != MMP_ERR_NONE) {
        return status;
    }

    do {
        status = MMPD_AUDIO_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
    } while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeOGGPlay
//------------------------------------------------------------------------------
/**
    @brief  Resume OGG Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_ResumeOGGPlay(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopOGGPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop OGG Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_StopOGGPlay(void)
{
    MMP_ERR     status;

    status = MMPD_AUDIO_StopAudioPlay();

    if (status != MMP_ERR_NONE) {
	    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			if (m_ulAudioPlayFileHandle) {	
	        	MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
			}	
	    }
	    
        goto OGG_STOP_EXIT;
    }

	status = MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
		if (m_ulAudioPlayFileHandle) {	
			MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
			m_ulAudioPlayFileHandle = 0;
		}
    }
    
OGG_STOP_EXIT:

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetOGGPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get OGG Current Play Time
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetOGGPlayTime(MMP_ULONG *ulPlayTime)
{
    return  MMPD_AUDIO_GetOGGPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetOGGPlaySpectrum
//------------------------------------------------------------------------------
/**
    @brief  Get OGG Play Spectrum
    @param[out] usSpectrum[] : spectrum data (32 words = 64 bytes)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be in playing state before get spectrum, otherwise,
         unexpected spectrum values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetOGGPlaySpectrum(MMP_USHORT usSpectrum[])
{
    return  MMPD_AUDIO_GetPlaySpectrum(usSpectrum);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetOGGPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set OGG Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre This function should be used when playback was in stopped state,
         either stopped by @ref MMPS_AUDIO_StopOGGPlay or due to EOF.
    @post You can @b NOT get updated play time until you restart playback
          by @ref MMPS_AUDIO_StartOGGPlay.

    <b>Sample codes:</b><br>
    @code
    AIT_OGG_Player_Seek(MMP_ULONG ulTargetTimeMs)
    {
        MMPS_AUDIO_PLAY_STATUS  play_status;

        //Stop playback first if needed. For host file mode, file will be closed.
        MMPS_AUDIO_GetPlayStatus(&play_status);
        if (play_status != MMPS_AUDIO_PLAY_STOP)
            MMPS_AUDIO_StopOGGPlay();

        //Seek to specified position. For host file mode, file will be re-opened.
        MMPS_AUDIO_SetOGGPlayTime(ulStartTimeMs);
        MMPS_AUDIO_StarOGGPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_SetOGGPlayTime(MMP_ULONG ulPlayTime)
{
    if ((m_ulAudioPlayFileHandle == 0) && (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
        MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }
    return  MMPD_AUDIO_SetOGGPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetOGGPlayPosition
//------------------------------------------------------------------------------
/**
    @brief  Get OGG Play Current Position
    @param[out] *ulPos : position (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play position. Otherwise, unexpected values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetOGGPlayPosition(MMP_ULONG *ulPos)
{
    return  MMPD_AUDIO_GetPlayPosition(ulPos);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeWAVPlay
//------------------------------------------------------------------------------
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
MMP_ERR MMPS_AUDIO_InitializeWAVPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WAV_INFO *wavinfo)
{
    MMP_ERR     status;
    MMP_ULONG64 filesize;
    MMP_ULONG   readsize;
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   drmOffset;

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_WAV_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_WAV_P_CARD_MODE);
        status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            wavinfo->usNotSupport = 1;
            return status;
        }
    }
    else if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (fileinfo->ubBuf == NULL || fileinfo->ulBufSize == 0) {
            PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (fileinfo->ulBufSize & 0x3FF) {
                PRINTF("Please set ulBufSize to be multiple of 1024\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
        }
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        else
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_WAV_P_MEM_MODE);
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }

        m_ubAudioPlayBuf = fileinfo->ubBuf;

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
            m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
            m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            status = MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", (void *)&m_ulAudioPlayFileHandle);
            if(status != MMP_ERR_NONE) {
                return status;
            }
            MMPC_FS_FileGetSize((void *)m_ulAudioPlayFileHandle, &filesize);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                filesize -= drmOffset;
                filesize = (filesize >> 4) << 4; //16-byte alignment
            }
            #endif
            if (m_ulAudioPlayBufSize > filesize)
                m_ulAudioPlayBufSize = filesize;
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                MMPC_FS_FileSeek((void *)m_ulAudioPlayFileHandle, (MMP_LONG64)drmOffset, MMPS_FS_SEEK_SET);
            }
            #endif
            MMPC_FS_FileRead((void *)m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            m_ulAudioPlayFileSize = filesize;
        }
        else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) {
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }
        else {
            m_ubAudioPlayBuf = 0;
            m_ulAudioPlayBufSize = 0;
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }

        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
        else {
            MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        }
    }

    MMPD_AUDIO_GetWAVFileInfo((MMP_AUDIO_WAV_INFO *)wavinfo);
    if (wavinfo->usNotSupport) {
        PRINTF("MMPS_AUDIO_InitializeWAVPlay: unsupport\r\n");
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
		        MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
	   	    }	
        }
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
        (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
        (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        // restart for decode from the top of the memory
        MMPD_AUDIO_SetPlayReadPtr(0, 0);

        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartWAVPlay
//------------------------------------------------------------------------------
/**
    @brief  Start WAV Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUDIO_InitializeWAVPlay was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.

    <b>Sample codes:</b><br>
    @code
    //WAV play has been initialized, start playback with specified starting time.
    AIT_WAV_Player_Start(MMP_BOOL bCardMode, MMP_ULONG ulStartTimeMs)
    {
        if (ulStartTimeMs) {
            if (!bCardMode) {
                //host file mode, change position to specified time
                MMPS_AUDIO_WAVPlayTime2FileOffset(ulStartTimeMs);
            }
            MMPS_AUDIO_SetWAVPlayTime(ulStartTimeMs);
        }
        MMPS_AUDIO_StartWAVPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_StartWAVPlay(void* callBackFunc, void* context)
{
    return MMPD_AUDIO_StartAudioPlay(callBackFunc, context);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseWAVPlay
//------------------------------------------------------------------------------
/**
    @brief  Pause WAV Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_PauseWAVPlay(void)
{
    MMP_ERR status;
    MMP_USHORT play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if(status == MMP_AUDIO_ERR_COMMAND_INVALID) {
        return status;
    }

    do {
        MMPD_AUDIO_GetPlayStatus(&play_status);
    } while (play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeWAVPlay
//------------------------------------------------------------------------------
/**
    @brief  Resume WAV Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_ResumeWAVPlay(void)
{
    return MMPD_AUDIO_ResumeAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopWAVPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop WAV Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_StopWAVPlay(void)
{
    MMP_ERR     status;

    status = MMPD_AUDIO_StopAudioPlay();

    if (status == MMP_AUDIO_ERR_COMMAND_INVALID) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {  
                MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
                m_ulAudioPlayFileHandle = 0;
            }
        }
        
        goto WAV_STOP_EXIT;
    }

    MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
        if (m_ulAudioPlayFileHandle) {  
            MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
            m_ulAudioPlayFileHandle = 0;
        }   
    }

WAV_STOP_EXIT:
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWAVPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get WAV Current Play Time
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetWAVPlayTime(MMP_ULONG *ulPlayTime)
{
    return MMPD_AUDIO_GetWAVPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetWAVPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set WAV Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1. This function should be used when playback was in stopped state,
            either stopped by @ref MMPS_AUDIO_StopWAVPlay or due to EOF.
    @pre 2. For host file mode, this function should be used 
            combining with @ref MMPS_AUDIO_WAVPlayTime2FileOffset.
    @post You can @b NOT get updated play time until you restart playback
          by @ref MMPS_AUDIO_StartWAVPlay.

    <b>Sample codes:</b><br>
    @code
    AIT_WAV_Player_Seek(MMP_BOOL bCardMode, MMP_ULONG ulTargetTime)
    {
        MMPS_AUDIO_PLAY_STATUS  play_status;

        //Stop playback first if needed.
        MMPS_AUDIO_GetPlayStatus(&play_status);
        if (play_status != MMPS_AUDIO_PLAY_STOP)
            MMPS_AUDIO_StopWAVPlay();

        if (!bCardMode) {
            //host file mode, re-open file, change position to the beginning of file
            MMPS_AUDIO_WAVPlayTime2FileOffset(ulTargetTime);
        }
        MMPS_AUDIO_SetWAVPlayTime(ulTargetTime);
        MMPS_AUDIO_StartWAVPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_SetWAVPlayTime(MMP_ULONG ulPlayTime)
{
    return MMPD_AUDIO_SetWAVPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWAVPlayPosition
//------------------------------------------------------------------------------
/**
    @brief  Get WAV Play Current Position
    @param[out] *ulPos : position (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play position. Otherwise, unexpected values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetWAVPlayPosition(MMP_ULONG *ulPos)
{
    return MMPD_AUDIO_GetPlayPosition(ulPos);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeAMRPlay
//------------------------------------------------------------------------------
/**
    @brief  Initialize AMR Play
            The function initialize the AMR Play. It will return the AMR media information,
            and prepare for AMR playback.
    @param[in] *fileinfo : input file parameters
    @param[out] *amrinfo : amr file info
    @return MMP_ERR_NONE, MMP_AUDIO_ERR_PARAMETER, MMP_AUDIO_ERR_OPENFILE_FAIL,
            MMP_AUDIO_ERR_UNSUPPORT_FORMAT, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre 1: Audio output path has been set by @ref MMPS_AUDIO_SetMediaPath.
    @pre 2: DRM IV/Key/header offset settings have beed set for DRM file playback.
    @pre 3: @e bFileName and @e usFileNameLength in @e fileinfo must be set properly.
    @pre 4: For host file mode, @e ubBuf and @e ulBufSize must also be set properly.
            @e ulBufSize must be a multiple of 1024.

    @post 1: After initialized, playback can be supported or not will be reported by FW parser.
             For unsupport file located at host storage, file will be closed directly.
    @post 2: After initialized successfully, @ref MMPS_AUDIO_StopAMRPlay must be called to close
             file located at host storage, even @ref MMPS_AUDIO_StartAMRPlay was not called.

    <b>Sample codes:</b><br>
    @code
    MMP_UBYTE   m_ubHostBuf[200*1024];
    AIT_AMR_Player_Init(MMP_BYTE *filename, MMP_BOOL bCardMode, DRM_INFO *drminfo)
    {
        MMPS_AUDIO_FILEINFO         fileinfo;
        MMP_AUDIO_AMR_INFO          amrinfo;

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
        MMPS_AUDIO_InitializeAMRPlay(&fileinfo, &amrinfo);
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_InitializeAMRPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AMR_INFO *amrinfo)
{
    MMP_ERR     status;
    MMP_ULONG64 filesize;
    MMP_ULONG   readsize;
    #if (OMA_DRM_EN == 1)
	MMP_USHORT	drmEn;
	MMP_ULONG	drmOffset;

	MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
	MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif
    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_AMR_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AMR_P_CARD_MODE);
        status = MMPD_AUDIO_SetPlayFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (status == MMP_AUDIO_ERR_OPENFILE_FAIL) {
            amrinfo->usNotSupport = 1;
            return status;
        }
    }
    else if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || 
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) ||
             (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (fileinfo->ubBuf == NULL || fileinfo->ulBufSize == 0) {
            PRINTF("Please set ubBuf pointer and set ulBufSize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (fileinfo->ulBufSize & 0x3FF) {
                PRINTF("Please set ulBufSize to be multiple of 1024\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
        }
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM)
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MMP_MEM);
        else
            MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AMR_P_MEM_MODE);
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MMP_MEM) {
            MMPD_AUDIO_SetPlayBuf((MMP_ULONG)fileinfo->ubBuf, fileinfo->ulBufSize);
        }

        m_ubAudioPlayBuf = fileinfo->ubBuf;

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
            m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
            m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            MMPC_FS_FileGetSize(m_ulAudioPlayFileHandle, &filesize);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	filesize -= drmOffset;
                filesize = (filesize >> 4) << 4; //16-byte alignment
            }	
			#endif		
			            
            if (m_ulAudioPlayBufSize > filesize)
            	m_ulAudioPlayBufSize = filesize;
            	
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
            	MMPC_FS_FileSeek((void *)m_ulAudioPlayFileHandle, (MMP_LONG64)drmOffset, MMPS_FS_SEEK_SET);
            }	
			#endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            m_ulAudioPlayFileSize = filesize;
        }
        else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) {
            m_ulAudioPlayFileHandle = 0;
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }
        else {
            m_ulAudioPlayFileHandle = 0;
            m_ubAudioPlayBuf = 0;
            m_ulAudioPlayBufSize = 0;
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }

        if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
            (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
            MMPS_AUDIO_TransferDataHostToDev();
        }
        else {
            MMPD_AUDIO_SetPlayWritePtr(0, 1); //all input audio data are in already buffer
        }

        // restart for decode from the top of the memory
        MMPD_AUDIO_InitPlaySeekFlag();
        MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }

    MMPD_AUDIO_GetAMRFileInfo((MMP_AUDIO_AMR_INFO *)amrinfo);
    if(amrinfo->usNotSupport) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle) {	
		        MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
	   	    }	
        }
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    MMPD_AUDIO_SetAMRPlayTime(0);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartAMRPlay
//------------------------------------------------------------------------------
/**
    @brief  Start AMR Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @ref MMPS_AUDIO_InitializeAMRPlay was successfully executed.
    @post For card mode, the file will be opened if originally file was not opened or closed.

    <b>Sample codes:</b><br>
    @code
    //AMR play has been initialized, start playback with specified starting time.
    AIT_WAV_Player_Start(MMP_ULONG ulStartTimeMs)
    {
        if (ulStartTimeMs) {
            MMPS_AUDIO_StartAMRPlay(ulStartTimeMs);
        }
        MMPS_AUDIO_StartAMRPlay();
    }
    @endcode
*/
MMP_ERR MMPS_AUDIO_StartAMRPlay(void)
{
    return MMPD_AUDIO_StartAudioPlay(NULL, NULL);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseAMRPlay
//------------------------------------------------------------------------------
/**
    @brief  Pause AMR Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing state before pause playback,
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_PauseAMRPlay(void)
{
    MMP_ERR		status;
    MMP_USHORT play_status;

    status = MMPD_AUDIO_PauseAudioPlay();
    if (status != MMP_ERR_NONE) {
        return status;
    }

    do{
        status = MMPD_AUDIO_GetPlayStatus(&play_status);
        if (status != MMP_ERR_NONE)
            return status;
    } while(play_status != DECODE_OP_PAUSE);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeAMRPlay
//------------------------------------------------------------------------------
/**
    @brief  Resume AMR Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_ResumeAMRPlay(void)
{
    return	MMPD_AUDIO_ResumeAudioPlay();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopAMRPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop AMR Play
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback status should be in playing or paused state before stop playback, 
         otherwise, invalid command error will be returned.
*/
MMP_ERR MMPS_AUDIO_StopAMRPlay(void)
{
    MMP_ERR status;

    status = MMPD_AUDIO_StopAudioPlay();
    if(status == MMP_AUDIO_ERR_COMMAND_INVALID) {
	    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			if (m_ulAudioPlayFileHandle) {	
	        	MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
			}	
	    }
	    
        goto AMR_STOP_EXIT;
    }

	status = MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
		if (m_ulAudioPlayFileHandle) {	
			MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
			m_ulAudioPlayFileHandle = 0;
		}
    }

AMR_STOP_EXIT:
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAMRPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get AMR Current Play Time
    @param[out] *usTimeRatio : time ratio (%)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetAMRPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    return MMPD_AUDIO_GetAMRPlayTime(usTimeRatio,ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetAMRPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Set AMR Start Play Time
    @param[in] ulPlayTime : play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_SetAMRPlayTime(MMP_ULONG ulPlayTime)
{
    if ((m_ulAudioPlayFileHandle == 0) && (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
        MMPD_AUDIO_SetMemModeFileHostInfo(m_ulAudioPlayFileHandle, m_ulAudioPlayFileSize);
    }
    return MMPD_AUDIO_SetAMRPlayTime(ulPlayTime);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAMRPlayPosition
//------------------------------------------------------------------------------
/**
    @brief  Get AMR Play Current Position
    @param[out] *ulPos : position (in byte)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play position. Otherwise, unexpected values will be returned.
*/
MMP_ERR MMPS_AUDIO_GetAMRPlayPosition(MMP_ULONG *ulPos)
{
    return MMPD_AUDIO_GetPlayPosition(ulPos);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartAMRRecord
//------------------------------------------------------------------------------
/**
    @brief  Start AMR Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StartAMRRecord(void)
{
    if (!(MMPS_AUDIO_GetInPath() & MMPS_AUDIO_IN_I2S_MASK)) {
        MMPD_AUDIO_SetPLL(8000);
    }
    return MMPD_AUDIO_StartAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseAMRRecord
//------------------------------------------------------------------------------
/**
    @brief  Pause AMR Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_PauseAMRRecord(void)
{
    return MMPD_AUDIO_PauseAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeAMRRecord
//------------------------------------------------------------------------------
/**
    @brief  Resume AMR Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_ResumeAMRRecord(void)
{
    return MMPD_AUDIO_ResumeAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopAMRRecord
//------------------------------------------------------------------------------
/**
    @brief  Stop AMR Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StopAMRRecord(void)
{
    MMP_ERR error;
    
    error = MMPD_AUDIO_StopAudioRecord();
    
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartAACRecord
//------------------------------------------------------------------------------
/**
    @brief  Start AAC Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StartAACRecord(void)
{
    MMP_USHORT sampleRate;
    MMP_ULONG bitRate;

    if (!(MMPS_AUDIO_GetInPath() & MMPS_AUDIO_IN_I2S_MASK)) {
        MMPD_AUDIO_ReadAACRecParameter(&bitRate, &sampleRate);
        MMPD_AUDIO_SetPLL(sampleRate);
    }
    else {
        // TODO customer file power on DAC
    }

    return MMPD_AUDIO_StartAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseAACRecord
//------------------------------------------------------------------------------
/**
    @brief  Pause AAC Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_PauseAACRecord(void)
{
    return MMPD_AUDIO_PauseAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeAACRecord
//------------------------------------------------------------------------------
/**
    @brief  Resume AAC Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_ResumeAACRecord(void)
{
    return MMPD_AUDIO_ResumeAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopAACRecord
//------------------------------------------------------------------------------
/**
    @brief  Stop AAC Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StopAACRecord(void)
{
    MMP_ERR error;
    
    error =  MMPD_AUDIO_StopAudioRecord();
    
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAACRecordSize
//------------------------------------------------------------------------------
/**
    @brief  Get AAC Record Current File Size
    @param[out] *ulSize : file size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetAACRecordSize(MMP_ULONG *ulSize)
{
    return MMPD_AUDIO_GetRecordSize(ulSize);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAACRecordTime
//------------------------------------------------------------------------------
/**
    @brief  Get AAC Record Current Time
    @param[out] *ulMilliSec : time (ms)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetAACRecordTime(MMP_ULONG *ulMilliSec)
{
    MMP_ULONG size,bitrate;
    MMP_USHORT samplerate;
    MMPD_AUDIO_GetRecordSize(&size);

    MMPD_AUDIO_ReadAACRecParameter(&bitrate, &samplerate);
    *ulMilliSec =  size/(bitrate/8000);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartMP3Record
//------------------------------------------------------------------------------
/**
    @brief  Start MP3 Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StartMP3Record(void)
{
    MMP_USHORT sampleRate;
    MMP_ULONG bitrate;

    if (!(MMPS_AUDIO_GetInPath() & MMPS_AUDIO_IN_I2S_MASK)) {
        MMPD_AUDIO_ReadMP3RecParameter(&bitrate, &sampleRate);
        MMPD_AUDIO_SetPLL(sampleRate);
    }
    else {
        // TODO customer file power on DAC
    }

    return MMPD_AUDIO_StartAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseMP3Record
//------------------------------------------------------------------------------
/**
    @brief  Pause MP3 Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_PauseMP3Record(void)
{
    return MMPD_AUDIO_PauseAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeMP3Record
//------------------------------------------------------------------------------
/**
    @brief  Resume MP3 Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_ResumeMP3Record(void)
{
    return MMPD_AUDIO_ResumeAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopMP3Record
//------------------------------------------------------------------------------
/**
    @brief  Stop MP3 Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StopMP3Record(void)
{
    MMP_ERR error;
    
    error = MMPD_AUDIO_StopAudioRecord();
    
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetMP3RecordSize
//------------------------------------------------------------------------------
/**
    @brief  Get MP3 Record Current File Size
    @param[out] *ulSize : file size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetMP3RecordSize(MMP_ULONG *ulSize)
{
    return MMPD_AUDIO_GetRecordSize(ulSize);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetMP3RecordTime
//------------------------------------------------------------------------------
/**
    @brief  Get MP3 Record Current Time
    @param[out] *ulMilliSec : time (ms)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetMP3RecordTime(MMP_ULONG *ulMilliSec)
{
    MMP_ULONG size,bitrate;
    MMP_USHORT samplerate;
    MMPD_AUDIO_GetRecordSize(&size);

    MMPD_AUDIO_ReadMP3RecParameter(&bitrate, &samplerate);
    *ulMilliSec =  size/(bitrate/8000);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartWAVRecord
//------------------------------------------------------------------------------
/**
    @brief  Start WAV Record
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StartWAVRecord(void)
{
    MMP_USHORT  usSampleRate;
    
    
    if (!(MMPS_AUDIO_GetInPath() & MMPS_AUDIO_IN_I2S_MASK)) {     
        MMPD_AUDIO_ReadWAVRecParameter(&usSampleRate);
        MMPD_AUDIO_SetPLL(usSampleRate);
    }
    else {
        // TODO customer file power on DAC
    }
    
    return MMPD_AUDIO_StartAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseWAVRecord
//------------------------------------------------------------------------------
/**
    @brief  Pause WAV Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_PauseWAVRecord(void)
{
    return MMPD_AUDIO_PauseAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeWAVRecord
//------------------------------------------------------------------------------
/**
    @brief  Resume WAV Record
    @return MMP_ERR_NONE, MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_ResumeWAVRecord(void)
{
    return MMPD_AUDIO_ResumeAudioRecord();
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopWAVRecord
//------------------------------------------------------------------------------
/**
    @brief  Stop WAV Record
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StopWAVRecord(void)
{
    MMP_ERR error;
    
    error = MMPD_AUDIO_StopAudioRecord();
    
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWAVRecordSize
//------------------------------------------------------------------------------
/**
    @brief  Get WAV Record Current File Size
    @param[out] *ulSize : file size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetWAVRecordSize(MMP_ULONG *ulSize)
{
    return MMPD_AUDIO_GetRecordSize(ulSize);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWAVRecordTime
//------------------------------------------------------------------------------
/**
    @brief  Get WAV Record Current Time
    @param[out] *ulMilliSec : time (ms)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetWAVRecordTime(MMP_ULONG *ulMilliSec)
{
    MMP_ULONG   ulSize;
    MMP_USHORT  usSamplerate;

    MMPD_AUDIO_GetRecordSize(&ulSize);
    MMPD_AUDIO_ReadWAVRecParameter(&usSamplerate);
    //ToDo: only support 16-bit sample currently
    *ulMilliSec = (MMP_ULONG)((MMP_ULONG64)ulSize*1000/(usSamplerate << 2));

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetPlayVolumeDb
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Play Volume by db
    @param[in] ulInputDb : input db value, 0~96 is valid for this value
*/
MMP_ERR MMPS_AUDIO_SetPlayVolumeDb(MMP_BYTE ulInputDb)
{
	
	#if (AUDIO_SET_DB == 0x1)	 
    // CarDV++
	if (m_audioOutPath == MMPS_AUDIO_OUT_AFE_LINE) {
	        if (ulInputDb > MMPS_Audio_GetConfig()->ubAudioOutVolLineTable[30][0])
	            ulInputDb = MMPS_Audio_GetConfig()->ubAudioOutVolLineTable[30][0];
	    }
    // CarDV--
	return MMPD_AUDIO_SetPlayVolume(ulInputDb, DEFAULT_DAC_DIGITAL_GAIN,
                                    DEFAULT_DAC_LINEOUT_GAIN, MMP_FALSE);
	#else
	return MMP_ERR_NONE;
	#endif
}

//==============================================================================
//  Function    : MMPS_AUDIO_SetPlayAnalogGain
//==============================================================================
/** 
    @brief  Set Audio Analog Gain
    @param[in] ubAGain  : Audio ANALOG GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPS_AUDIO_SetPlayAnalogGain(MMP_UBYTE ubAGain)
{
	return MMPD_AUDIO_SetPlayAnalogGain(ubAGain);
}

//==============================================================================
//  Function    : MMPS_AUDIO_SetPlayDigitalGain
//==============================================================================
/** 
    @brief  Set Audio Digital Gain
    @param[in] ubDGain  : Audio DIGITAL GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPS_AUDIO_SetPlayDigitalGain(MMP_UBYTE ubDGain)
{
	return MMPD_AUDIO_SetPlayDigitalGain(ubDGain);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetPlayVolume
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Play Volume
    @param[in] usLevel : volume level
    @param[in] bSWGainOnly : Set SW gain only, reset digital and analog gain to default value.
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre @e usLevel must less than maximum volume level, otherwise,
         the maximum allowed level will be used instead of @e usLevel.
    @pre Playback volume can be set before playing or after stopping, and apply to following
         playback. During playing, the volume setting would be applied immediately.
*/
MMP_ERR MMPS_AUDIO_SetPlayVolume(MMP_USHORT usLevel, MMP_BOOL bSWGainOnly)
{
    MMP_UBYTE ubSWGain = 0, ubDGain = 0, ubAGain = 0; 

    if (usLevel >= MMPS_Audio_GetConfig()->ubVolumeLevel)
    	usLevel = MMPS_Audio_GetConfig()->ubVolumeLevel - 1;
    m_AudioPlayVolume = usLevel;

    if (bSWGainOnly) {
    	if (m_audioOutPath == MMPS_AUDIO_OUT_AFE_LINE)
    	            ubSWGain = MMPS_Audio_GetConfig()->ubAudioOutVolLineTable[usLevel][0];
    }
    else {
    	if (m_audioOutPath == MMPS_AUDIO_OUT_AFE_LINE) {
    	            ubSWGain = MMPS_Audio_GetConfig()->ubAudioOutVolLineTable[usLevel][0];
    	            ubDGain = MMPS_Audio_GetConfig()->ubAudioOutVolLineTable[usLevel][1];
    	            ubAGain = DEFAULT_DAC_LINEOUT_GAIN;
    	}
    }
    return  MMPD_AUDIO_SetPlayVolume(ubSWGain, ubDGain, ubAGain, bSWGainOnly);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetPlayVolume
//------------------------------------------------------------------------------
/**
    @brief  Get Audio Play Volume
    @param[out] usLevel : volume level
    @return MMP_ERR_NONE

    @pre Playback volume must have been set by @ref MMPS_AUDIO_SetPlayVolume,
         otherwise, unexpected value will be returned.
*/
MMP_ERR MMPS_AUDIO_GetPlayVolume(MMP_USHORT *usLevel) 
{
    *usLevel = m_AudioPlayVolume;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRecordDigitalGain
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Digital Gain
    @param[in] ubDGain  : Audio DIGITAL GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPS_AUDIO_SetRecordDigitalGain(MMP_UBYTE ubDGain)
{
	return MMPD_AUDIO_SetRecordDigitalGain(ubDGain);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRecordAnalogGain
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Analog Gain
    @param[in] ubAGain  : Audio ANALOG GAIN.
    @param[in] bboostup : Audio ANALOG GAIN boost up.
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPS_AUDIO_SetRecordAnalogGain(MMP_UBYTE ubAGain, MMP_BOOL bboostup)
{
	return MMPD_AUDIO_SetRecordAnalogGain(ubAGain);
}


//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRecordVolume
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Volume
    @param[in] ubDGain  : Audio DIGITAL GAIN.
    @param[in] ubAGain  : Audio ANALOG GAIN.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetRecordVolume(MMP_UBYTE ubDGain, MMP_UBYTE ubAGain)
{
    return MMPD_AUDIO_SetRecordVolume(ubDGain, ubAGain);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRecordHeadMuteTime
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Volume
    @param[in] ulMilliSec  : Time to mute in record head.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetRecordHeadMuteTime(MMP_ULONG ulMilliSec)
{
	return MMPD_AUDIO_SetRecordHeadMuteTime(ulMilliSec);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRecordTailCutTime
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Volume Tail Cut Time
    @param[in] ulMilliSec  : Time to cut in record tail.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetRecordTailCutTime(MMP_ULONG ulMilliSec)
{
	return MMPD_AUDIO_SetRecordTailCutTime(ulMilliSec);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnableDummyRecord
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Volume
    @param[in] bEnable  : To enable or disable audio dummy record function.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_EnableDummyRecord(MMP_BOOL bEnable)
{
    return MMPD_AUDIO_EnableDummyRecord(bEnable);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitAMRRecordToCard
//------------------------------------------------------------------------------
/**
    @brief  Initialize AMR Record To Card
    @param[in] *fileinfo : file information
    @param[in] mode : amr record mode
        -   MMPS_AUDIO_AMR_MR475_ENCODE_MODE : 4.75K
        -   MMPS_AUDIO_AMR_MR515_ENCODE_MODE : 5.15K
    @param[in] ulMaxSize : file size limitation
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitAMRRecordToCard(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_AMR_ENCODEMODE mode,MMP_ULONG ulMaxSize)
{
    MMPD_AUDIO_SetInPath(MMPS_AUDIO_GetInPath());
    MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_CARD);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AMR_R_CARD_MODE);
    MMPD_AUDIO_SetEncodeFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
    MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_AMR_ENCODE);
    MMPD_AUDIO_SetEncodeMode(mode);
    MMPD_AUDIO_SaveAMRRecParameter(mode);
    MMPD_AUDIO_SetEncodeFileSize(ulMaxSize);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitAMRRecordToMem
//------------------------------------------------------------------------------
/**
    @brief  Initialize AMR Record To Mem
    @param[in] mode : amr record mode
        -   MMPS_AUDIO_AMR_MR475_ENCODE_MODE : 4.75K
        -   MMPS_AUDIO_AMR_MR515_ENCODE_MODE : 5.15K
    @param[in] ulMaxSize : file size limitation
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitAMRRecordToMem(MMPS_AUDIO_AMR_ENCODEMODE mode, MMP_ULONG ulMaxSize)
{
    MMPD_AUDIO_SetInPath(MMPS_AUDIO_GetInPath());
    MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_MEM);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AMR_R_MEM_MODE);
    MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_AMR_ENCODE);
    MMPD_AUDIO_SetEncodeMode(mode);
    MMPD_AUDIO_InitRecRWPtr();
    MMPD_AUDIO_SaveAMRRecParameter(mode);
    MMPD_AUDIO_SetEncodeFileSize(ulMaxSize);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitAACRecordToCard
//------------------------------------------------------------------------------
/**
    @brief  Initialize AAC Record To Card
    @param[in] *fileinfo : file information
    @param[in] mode : aac record mode.
             -  MMPS_AUDIO_AAC_RECORD_32K_160K : sample rate 32k,bitrate 160k
             -  MMPS_AUDIO_AAC_RECORD_32K_128K : sample rate 32k,bitrate 128k
             -  MMPS_AUDIO_AAC_RECORD_32K_96K : sample rate 32k,bitrate 96k
             -  MMPS_AUDIO_AAC_RECORD_32K_64K : sample rate 32k,bitrate 64k
             -  MMPS_AUDIO_AAC_RECORD_22K_160K : sample rate 22.05k,bitrate 160k
             -  MMPS_AUDIO_AAC_RECORD_22K_128K : sample rate 22.05k,bitrate 128k
             -  MMPS_AUDIO_AAC_RECORD_22K_96K : sample rate 22.05k,bitrate 96k
             -  MMPS_AUDIO_AAC_RECORD_22K_64K : sample rate 22.05k,bitrate 64k
    @param[in] ulMaxSize : file size limitation
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitAACRecordToCard(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_AAC_ENCODEMODE mode,MMP_ULONG ulMaxSize)
{
    MMPD_AUDIO_SetInPath(m_audioInPath);
    MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_CARD);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AAC_R_CARD_MODE);
    MMPD_AUDIO_SetEncodeFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
    MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_AAC_ENCODE);
    MMPD_AUDIO_SetEncodeMode(mode);
    MMPD_AUDIO_SaveAACRecParameter(mode);
    MMPD_AUDIO_SetEncodeFileSize(ulMaxSize);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitAACRecordToMem
//------------------------------------------------------------------------------
/**
    @brief  Initialize AAC Record To Mem
    @param[in] mode : aac record mode
             -  MMPS_AUDIO_AAC_RECORD_32K_160K : sample rate 32k,bitrate 160k
             -  MMPS_AUDIO_AAC_RECORD_32K_128K : sample rate 32k,bitrate 128k
             -  MMPS_AUDIO_AAC_RECORD_32K_96K : sample rate 32k,bitrate 96k
             -  MMPS_AUDIO_AAC_RECORD_32K_64K : sample rate 32k,bitrate 64k
             -  MMPS_AUDIO_AAC_RECORD_22K_160K : sample rate 22.05k,bitrate 160k
             -  MMPS_AUDIO_AAC_RECORD_22K_128K : sample rate 22.05k,bitrate 128k
             -  MMPS_AUDIO_AAC_RECORD_22K_96K : sample rate 22.05k,bitrate 96k
             -  MMPS_AUDIO_AAC_RECORD_22K_64K : sample rate 22.05k,bitrate 64k
    @param[in] ulMaxSize : file size limitation
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitAACRecordToMem(MMPS_AUDIO_AAC_ENCODEMODE mode,MMP_ULONG ulMaxSize)
{
    MMPD_AUDIO_SetInPath(MMPS_AUDIO_GetInPath());
    MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_MEM);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_AAC_R_MEM_MODE);
    MMPD_AUDIO_InitRecRWPtr();
    MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_AAC_ENCODE);
    MMPD_AUDIO_SetEncodeMode(mode);
    MMPD_AUDIO_SaveAACRecParameter(mode);
    MMPD_AUDIO_SetEncodeFileSize(ulMaxSize);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitMP3RecordToCard
//------------------------------------------------------------------------------
/**
    @brief  Initialize MP3 Record To Card
    @param[in] *fileinfo : file information
    @param[in] mode : mp3 record mode
             -  MMPS_AUDIO_MP3_RECORD_32K_160K : sample rate 32k,bitrate 160k
             -  MMPS_AUDIO_MP3_RECORD_32K_128K : sample rate 32k,bitrate 128k
             -  MMPS_AUDIO_MP3_RECORD_32K_96K : sample rate 32k,bitrate 96k
             -  MMPS_AUDIO_MP3_RECORD_32K_64K : sample rate 32k,bitrate 64k
    @param[in] ulMaxSize : file size limitation
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitMP3RecordToCard(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_MP3_ENCODEMODE mode, MMP_ULONG ulMaxSize)
{
    MMP_ERR err;

    MMPD_AUDIO_SetInPath(m_audioInPath);
    MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_CARD);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_MP3_R_CARD_MODE);
    err = MMPD_AUDIO_SetEncodeFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
    if (err != MMP_ERR_NONE)
        return err;
    MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_MP3_ENCODE);
    MMPD_AUDIO_SetEncodeMode(mode);
    MMPD_AUDIO_SaveMP3RecParameter(mode);
    MMPD_AUDIO_SetEncodeFileSize(ulMaxSize);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitMP3RecordToMem
//------------------------------------------------------------------------------
/**
    @brief  Initialize MP3 Record To Mem
    @param[in] mode : mp3 record mode
             -  MMPS_AUDIO_MP3_RECORD_32K_160K : sample rate 32k,bitrate 160k
             -  MMPS_AUDIO_MP3_RECORD_32K_128K : sample rate 32k,bitrate 128k
             -  MMPS_AUDIO_MP3_RECORD_32K_96K : sample rate 32k,bitrate 96k
             -  MMPS_AUDIO_MP3_RECORD_32K_64K : sample rate 32k,bitrate 64k
    @param[in] ulMaxSize : file size limitation
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitMP3RecordToMem(MMPS_AUDIO_MP3_ENCODEMODE mode,MMP_ULONG ulMaxSize)
{
    MMPD_AUDIO_SetInPath(m_audioInPath);
    MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_MEM);
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_MP3_R_MEM_MODE);
    MMPD_AUDIO_InitRecRWPtr();
    MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_MP3_ENCODE);
    MMPD_AUDIO_SetEncodeMode(mode);
    MMPD_AUDIO_SaveMP3RecParameter(mode);
    MMPD_AUDIO_SetEncodeFileSize(ulMaxSize);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitWAVRecord
//------------------------------------------------------------------------------
/**
    @brief  Initialize WAV Record
    @param[in] mode : wav record mode
    @param[in] ulMaxSize : file size limitation
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitWAVRecord(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_WAV_ENCODEMODE wav_encode_mode, MMP_ULONG ulMaxSize)
{
    MMP_ERR err = MMP_ERR_NONE;

    MMPD_AUDIO_SetInPath(m_audioInPath);
    
    if (fileinfo->mediaPath == MMPS_AUDIO_MEDIA_PATH_CARD)
        MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_CARD);
    else
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        
    
    MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_WAV_R_CARD_MODE);
    if (fileinfo->mediaPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        err = MMPD_AUDIO_SetEncodeFileName(fileinfo->bFileName, fileinfo->usFileNameLength);
        if (err != MMP_ERR_NONE)
            return err;
    }
    else if (fileinfo->mediaPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
        MMPD_AUDIO_InitRecRWPtr();
    }
    MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_WAV_ENCODE);
    MMPD_AUDIO_SetEncodeMode(wav_encode_mode);
    MMPD_AUDIO_SaveWAVRecParameter(wav_encode_mode);
    MMPD_AUDIO_SetEncodeFileSize(ulMaxSize);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAMRRecordSize
//------------------------------------------------------------------------------
/**
    @brief  Get AMR Record Current File Size
    @param[out] *ulSize : file size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetAMRRecordSize(MMP_ULONG *ulSize)
{
    return MMPD_AUDIO_GetRecordSize(ulSize);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetAMRRecordTime
//------------------------------------------------------------------------------
/**
    @brief  Get AMR Record Current Time
    @param[out] *ulMilliSec : time (ms)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetAMRRecordTime(MMP_ULONG *ulMilliSec)
{
    MMP_ULONG size,bitrate;
    MMPD_AUDIO_GetRecordSize(&size);

    MMPD_AUDIO_ReadAMRRecParameter(&bitrate);
    *ulMilliSec =  (size*80)/(bitrate/100);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_TransferDataHostToDev
//------------------------------------------------------------------------------
/**
    @brief  Transfer Audio Data From Host to Firmware(Memory Mode)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_TransferDataHostToDev(void)
{
    MMP_ERR status;

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) ||
        (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        status = MMPD_AUDIO_TransferDataHostToDev();
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_TransferDataCardToHost(m_ulAudioPlayFileHandle);
        }
    }
    else {
        return MMP_AUDIO_ERR_INVALID_FLOW;
    }

    return  status;
}
/// @ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_TransferDataToAIT
//------------------------------------------------------------------------------
/**
    @brief  Transfer Audio Data From Host to Firmware(Memory Mode)
    @param[in] ubAudioPtr : audio data start pointer
    @param[in] ulMaxSize  : max data size to transfer
    @param[out] *ulReturnSize : actual transfer data size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_TransferDataToAIT(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize,
                MMP_ULONG *ulReturnSize)
{
    return MMP_AUDIO_ERR_COMMAND_INVALID;
}
/// @end_ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_TransferDataToHost
//------------------------------------------------------------------------------
/**
    @brief  Transfer Audio Data From Firmware to Host(Memory Mode)
    @param[in] ubAudioPtr : audio data buffer start pointer
    @param[in] ulMaxSize  : max data size to transfer
    @param[out] *ulReturnSize : actual transfer data size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_TransferDataToHost(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize,
                MMP_ULONG *ulReturnSize)
{
    return MMPD_AUDIO_TransferDataToHost(ubAudioPtr,ulMaxSize,ulReturnSize);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_TransferAudioDataToHost
//------------------------------------------------------------------------------
/**
    @brief  Transfer SBC/WAV Data From Firmware to Host(Memory Mode)
    @param[in] ubAudioPtr : audio data buffer start pointer
    @param[in] ulMaxSize  : max data size to transfer
    @param[in] ulFrameSize  : frame size
    @param[out] *ulReturnSize : actual transfer data size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_TransferAudioDataToHost(MMP_UBYTE * ubAudioPtr, MMP_ULONG ulMaxSize,MMP_ULONG ulFrameSize, MMP_ULONG * ulReturnSize)
{
    return MMPD_AUDIO_TransferAudioDataToHost(ubAudioPtr, ulMaxSize, ulFrameSize, ulReturnSize);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetSBCBitPool
//------------------------------------------------------------------------------
/**
    @brief  Get SBC bitpool size
    @param[in] ulBitRate    : bitrate (unit : K)
    @param[in] ulSampleRate : sample rate
    @param[in] ulBitPool    : bit pool
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetSBCBitPool(MMP_ULONG ulBitRate, MMP_ULONG ulSampleRate, MMP_ULONG *ulBitPool)
{
    MMP_LONG NumSb  = MMPS_Audio_GetConfig()->SBC.usNrofSubbands;
    MMP_LONG NumBlk = MMPS_Audio_GetConfig()->SBC.usNrofBlocks; 
    MMP_LONG ChMode = MMPS_Audio_GetConfig()->SBC.ChannelMode;
    MMP_LONG IsMono  = 8 * NumSb;
    MMP_LONG IsJoin  = 0;
	MMP_LONG Remainder, i;
    MMP_LONG Numerator;
    MMP_LONG Denominator = NumBlk;

    switch(ulSampleRate) {
	case 8000:	//6x
	case 12000:	//4x
	case 16000:	//3x
	case 24000:	//2x
	case 32000:	//1.5x
		ulSampleRate = 48000;
		break;
	case 11025:	//4x
	case 22050:	//2x
		ulSampleRate = 44100;
		break;
	default:
		break;
	}
    
    ulBitRate  = ulBitRate * 1000;
    *ulBitPool = 0;
    
	if (ChMode < MMPS_AUDIO_SBC_CHANNEL_STEREO) {
		if(ChMode == MMPS_AUDIO_SBC_CHANNEL_MONO)
			IsMono >>= 1;
		else
			Denominator <<= 1;
	}
	else if(ChMode == MMPS_AUDIO_SBC_CHANNEL_JOINT) {
		IsJoin = NumSb;
	}

	for(i = 0 ; i < 35 ; i++) {
		Numerator  = (ulBitRate * NumSb * NumBlk / ulSampleRate - 4*8 - IsMono - IsJoin);
	    *ulBitPool = Numerator / Denominator;
	    Remainder  = Numerator % Denominator;

		// check rounding
	    if(Remainder != 0 && Remainder > Denominator/2) {
	        if (Remainder*8 > Denominator*7) //increase if > den*7/8
	            (*ulBitPool)++;
	    }

		if (ChMode < MMPS_AUDIO_SBC_CHANNEL_STEREO) {
			if(*ulBitPool <= (16 * NumSb)) {
				break;
			}
		}
		else {
			if(*ulBitPool <= (32 * NumSb)) {
				break;
			}
		}
		ulBitRate -= 10000;
	}     
   
	return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeSBCEncode
//------------------------------------------------------------------------------
/**
    @brief  Initial SBC Encode
    @param[in] ulBufStartAddr : buffer start address
    @param[in] ulBufSize : buffer size
    @param[in] ulBitRate : bit rate (unit: K)
    @param[in] ulBitPool : bit pool size 
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitializeSBCEncode(MMP_ULONG ulBufStartAddr, MMP_ULONG ulBufSize, MMP_ULONG ulBitRate, MMP_ULONG ulBitPool)
{
	MMP_ULONG	cur_buf,sbc_buf_size;

    cur_buf = m_ulAudioMemEnd;
    
	cur_buf -= MMPD_AUDIO_REC_HANDSHAKE_BUF_SIZE;                
    MMPD_AUDIO_SetRecHandshakeBuf(cur_buf, MMPD_AUDIO_REC_HANDSHAKE_BUF_SIZE);

    sbc_buf_size = m_AudioBufInfo.AudioMode[m_ulAudioMemMapMode].ulSbcBufSize;
    cur_buf -= sbc_buf_size;  
    MMPD_AUDIO_SetEncodeBuf(cur_buf, sbc_buf_size);

    MMPD_AUDIO_SetSBCChannelMode(MMPS_Audio_GetConfig()->SBC.ChannelMode);
    MMPD_AUDIO_SetSBCAllocMethod(MMPS_Audio_GetConfig()->SBC.AllocMethod);
    MMPD_AUDIO_SetSBCNrofBlocks(MMPS_Audio_GetConfig()->SBC.usNrofBlocks);
    MMPD_AUDIO_SetSBCNrofSubbands(MMPS_Audio_GetConfig()->SBC.usNrofSubbands);
    if (ulBitPool == 0) {
        MMPD_AUDIO_SetSBCBitrate(ulBitRate);
    }
    else {
        MMPD_AUDIO_SetSBCBitPool(ulBitPool);
    }

    MMPD_AUDIO_InitRecRWPtr();

    //m_ulSBCBitRate = ulBitRate;
    m_ucSBCBufStart = (MMP_UBYTE *)ulBufStartAddr;
    m_ucSBCBufRead  = m_ucSBCBufStart;
    m_ucSBCBufWrite = m_ucSBCBufStart;

    m_ulSBCMaxTransSize   = m_AudioBufInfo.SBC.ulMaxTransferSize;
    m_ulSBCSizeReadIdx    = 0;
    m_ulSBCSizeWriteIdx   = 0;
    m_ulSBCSizeNum        = 0;
    m_ulSBCBufSize        = ulBufSize;
    m_ulSBCSlotSize       = m_ulSBCMaxTransSize;
    m_ulSBCConsumedData   = 0;

    MEMSET(m_ulSBCSizeSlot, 0, sizeof(MMP_ULONG)*SBC_SLOT_NUM);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetSBCEncodeEnable
//------------------------------------------------------------------------------
/**
    @brief  Enable or Disable SBC Enable
    @param[in] bEnable : enable or disable
    @param[in] ulStartTime : start time
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetSBCEncodeEnable(MMP_BOOL bEnable, MMP_ULONG ulStartTime)
{
    MMP_ULONG ulOutBitRate, SBCFrameCount,ulBitpool;
    
    MMPD_AUDIO_SetSBCEncodeEnable(bEnable,m_AudioBufInfo.SBC.ulIntPeriod);

    MMPD_AUDIO_GetSBCInfo(&m_ulSBCSamplingRate,&ulOutBitRate  ,&m_ulSBCFrameLen,
                          &SBCFrameCount  ,&m_ulSBCSamples,&m_ulSBCChannels,&ulBitpool);
    
    m_ulSBCStartTime = ulStartTime;

    if(bEnable == MMP_FALSE) {
        m_ulSBCSizeReadIdx    = 0;
        m_ulSBCSizeWriteIdx   = 0;
        m_ulSBCSizeNum        = 0;
        m_ulSBCConsumedData   = 0;
        MEMSET(m_ulSBCSizeSlot,0,sizeof(MMP_ULONG)*SBC_SLOT_NUM);
    }
    
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetSBCInfo
//------------------------------------------------------------------------------
/**
    @brief  Get SBC information
    @param[in] ulOutSampleRate : Sample rate
    @param[in] ulOutBitRate : bitrate
    @param[in] ulOutFrameSize : SBC framesize
    @param[in] ulOutBitpool   : Bitpool size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetSBCInfo(MMP_ULONG *ulOutSampleRate, MMP_ULONG *ulOutBitRate,MMP_ULONG *ulOutFrameSize,MMP_ULONG *ulOutBitpool)
{
    MMP_ULONG SBCFrameCount;
    MMP_ULONG SBCSamples;
    MMP_ULONG SBCChans;

    MMPD_AUDIO_GetSBCInfo(  ulOutSampleRate,ulOutBitRate,ulOutFrameSize,
                            &SBCFrameCount,&SBCSamples,&SBCChans,ulOutBitpool);

    //*ulOutBitRate = m_ulSBCBitRate;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetSBCTime
//------------------------------------------------------------------------------
/**
    @brief  Get current SBC time
    @param[in] time : current time
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetSBCTime(MMP_ULONG *time)
{   
    if (m_ulSBCFrameLen == 0) {
        *time = 0;
        return MMP_ERR_NONE;
    }

    *time = m_ulSBCStartTime + ((MMP_ULONG64)(m_ulSBCConsumedData / m_ulSBCFrameLen) * m_ulSBCSamples * (10 / m_ulSBCChannels)) / (m_ulSBCSamplingRate / 100);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_TransferSBCDataFromDev
//------------------------------------------------------------------------------
/**
    @brief  Transfer SBC encoded data from device
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_TransferSBCDataFromDev()
{
    MMP_BOOL    bSBCEnable = MMP_FALSE;
    MMP_ULONG   MaxSize = m_ulSBCMaxTransSize;
    MMP_ULONG   return_size, i;

    if (m_ulSBCSizeNum >= SBC_SLOT_NUM)
        return MMP_ERR_NONE;

    MMPD_AUDIO_GetSBCEncodeEnable(&bSBCEnable);
    if ((bSBCEnable == MMP_FALSE)||(m_ulSBCFrameLen == 0)) {
        PRINTF("bSBCEnable = %d, m_ulSBCFrameLen = %d\r\n", bSBCEnable, m_ulSBCFrameLen);
        return MMP_ERR_NONE;
    }

    MaxSize = ( MaxSize / m_ulSBCFrameLen ) * m_ulSBCFrameLen;
    if (MaxSize == 0)
        MaxSize = m_ulSBCFrameLen;

    for(i = 0; i < 1; i++) {
        MMPS_AUDIO_TransferAudioDataToHost(m_ucSBCBufWrite, MaxSize, m_ulSBCFrameLen, &return_size);

        if (return_size == 0)
			return MMP_ERR_NONE;

        m_ucSBCBufWrite  += m_ulSBCSlotSize;
        if (((MMP_ULONG)m_ucSBCBufWrite) >= ((MMP_ULONG)m_ucSBCBufStart + (m_ulSBCSlotSize*SBC_SLOT_NUM))) {
            m_ucSBCBufWrite  = m_ucSBCBufStart;
        }

        m_ulSBCSizeSlot[m_ulSBCSizeWriteIdx] = return_size;
        m_ulSBCSizeWriteIdx = (m_ulSBCSizeWriteIdx + 1) % SBC_SLOT_NUM;
        m_ulSBCSizeNum++;

        if (m_ulSBCSizeNum >= SBC_SLOT_NUM)
            return MMP_ERR_NONE;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetCurrnetSBCBuf
//------------------------------------------------------------------------------
/**
    @brief  Get current SBC data start position and available data size
    @param[in] pBuf : data pointer
    @param[in] DataSize : available data size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetCurrnetSBCBuf(MMP_UBYTE **pBuf, MMP_ULONG *DataSize)
{
    MMP_ULONG   tmpBufSizeNum;
    MMP_ULONG   i;

    *DataSize = 0;

    if(m_ulSBCSizeNum == 0){
        *pBuf = NULL;
         *DataSize  = 0;
        return MMP_ERR_NONE;
    }
    *pBuf           = (MMP_UBYTE*)(m_ucSBCBufRead);
    tmpBufSizeNum = m_ulSBCSizeNum;

    for(i=0;i<1;i++) {
        *DataSize    += m_ulSBCSizeSlot[m_ulSBCSizeReadIdx+i];
        if(*DataSize >= m_ulSBCMaxTransSize)
            break;
        tmpBufSizeNum--;
        if(tmpBufSizeNum == 0)
            break;
    }
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetSBCDataDone
//------------------------------------------------------------------------------
/**
    @brief  Get SBC data done, update buffer pointers
    @param[in] DataSize : consumed data size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetSBCDataDone(MMP_ULONG DataSize)
{
    if(DataSize == 0)
        return MMP_ERR_NONE;
    if(m_ulSBCSizeNum == 0)
        return MMP_ERR_NONE;
    
    m_ucSBCBufRead  += m_ulSBCSlotSize;
    if( ((MMP_ULONG)m_ucSBCBufRead) >= ((MMP_ULONG)m_ucSBCBufStart + (m_ulSBCSlotSize*SBC_SLOT_NUM)))
    {
        m_ucSBCBufRead  = m_ucSBCBufStart;
    }
    
    m_ulSBCConsumedData += DataSize;
    DataSize -= m_ulSBCSizeSlot[m_ulSBCSizeReadIdx];
    m_ulSBCSizeReadIdx = (m_ulSBCSizeReadIdx + 1) % SBC_SLOT_NUM;
    
    m_ulSBCSizeNum--;
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializeWAVEncode
//------------------------------------------------------------------------------
/**
    @brief  Initial WAV Encode
    @param[in] ulBufStartAddr : buffer start address
    @param[in] ulBufSize : buffer size
    @param[in] ulSampleRate : sample rate
    @param[in] ulChans : number of channels
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitializeWAVEncode(MMP_ULONG ulBufStartAddr, MMP_ULONG ulBufSize,MMP_ULONG ulSampleRate,MMP_ULONG ulChans)
{
	MMP_ULONG	cur_buf,wav_buf_size;
	
    if (ulBufSize < MAX_WAV_TRANSFER_SIZE*WAV_SLOT_NUM) {
        return MMP_AUDIO_ERR_INSUFFICIENT_BUF;
    }
    
    cur_buf = m_ulAudioMemEnd;
    
	cur_buf -= MMPD_AUDIO_REC_HANDSHAKE_BUF_SIZE;                
    MMPD_AUDIO_SetRecHandshakeBuf(cur_buf, MMPD_AUDIO_REC_HANDSHAKE_BUF_SIZE);

    wav_buf_size = m_AudioBufInfo.AudioMode[m_ulAudioMemMapMode].ulWavBufSize;
    cur_buf -= wav_buf_size;  
    MMPD_AUDIO_SetEncodeBuf(cur_buf, wav_buf_size);
    
    MMPD_AUDIO_InitRecRWPtr();
    
    m_ulWAVBufStart    = ulBufStartAddr;
    m_ulWAVBufSize     = ulBufSize;
    
    m_ucWAVBufStart = (MMP_UBYTE *)ulBufStartAddr;
    m_ucWAVBufRead  = m_ucWAVBufStart;
    m_ucWAVBufWrite = m_ucWAVBufStart;

    m_ulWAVSizeReadIdx    = 0;
    m_ulWAVSizeWriteIdx   = 0;
    m_ulWAVSizeNum        = 0;
    m_ulWAVBufSize        = ulBufSize;
    m_ulWAVSlotSize       = MAX_WAV_TRANSFER_SIZE;
    m_ulWAVSampleRate	  = ulSampleRate;
    m_ulWAVChans	      = ulChans;
    m_ulWAVConsumedData   = 0;
    
    MEMSET(m_ulWAVSizeSlot,0,sizeof(MMP_ULONG)*WAV_SLOT_NUM);
    

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetWAVEncodeEnable
//------------------------------------------------------------------------------
/**
    @brief  enable/disable WAV Encode
    @param[in] ubEnable : ENABLE/DISABLE
    @param[in] ulStartTime : StartTime
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetWAVEncodeEnable(MMP_BOOL ubEnable, MMP_ULONG ulStartTime)
{		
	MMPD_AUDIO_SetWAVEncodeEnable(ubEnable);

    MMPD_AUDIO_GetWAVInfo(&m_ulWAVSampleCount);

	m_ulWAVStartTime = ulStartTime;
	          
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_TransferWAVDataFromDev
//------------------------------------------------------------------------------
/**
    @brief  transfer WAV data from device
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_TransferWAVDataFromDev(void)
{
	MMP_ULONG   MaxSize = MAX_WAV_TRANSFER_SIZE;
    MMP_ULONG   return_size,i;

    if (m_ulWAVSizeNum >= WAV_SLOT_NUM)
        return MMP_ERR_NONE;
    
    MaxSize = ( MaxSize / (m_ulWAVSampleCount*2) ) * (m_ulWAVSampleCount*2);
    if(MaxSize == 0)
        MaxSize = m_ulWAVSampleCount * 2;
	
    for(i = 0; i < 1; i++) {
        MMPS_AUDIO_TransferAudioDataToHost(m_ucWAVBufWrite,MaxSize,m_ulWAVSampleCount * 2,&return_size);
		
        if(return_size == 0)
	        return MMP_ERR_NONE;

        m_ucWAVBufWrite  += m_ulWAVSlotSize;
        
        if( ((MMP_ULONG)m_ucWAVBufWrite) >= ((MMP_ULONG)m_ucWAVBufStart + (m_ulWAVSlotSize*WAV_SLOT_NUM)))
        {
            m_ucWAVBufWrite  = m_ucWAVBufStart;
        }
		
        m_ulWAVSizeSlot[m_ulWAVSizeWriteIdx] = return_size;
        m_ulWAVSizeWriteIdx = (m_ulWAVSizeWriteIdx + 1) % WAV_SLOT_NUM;
        m_ulWAVSizeNum++;

        if (m_ulWAVSizeNum >= WAV_SLOT_NUM)
	        return MMP_ERR_NONE;
    }

	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetCurrnetWAVBuf
//------------------------------------------------------------------------------
/**
    @brief  get current WAV data start position and available data size
    @param[in] pBuf : current WAV data start position
    @param[in] DataSize : available data size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetCurrnetWAVBuf(MMP_UBYTE **pBuf, MMP_ULONG *DataSize)
{
	MMP_ULONG   tmpBufSizeNum;
    MMP_ULONG   i;

    *DataSize = 0;

    if(m_ulWAVSizeNum == 0)
        return MMP_ERR_NONE;
    
    *pBuf           = (MMP_UBYTE*)(m_ucWAVBufRead);
    tmpBufSizeNum = m_ulWAVSizeNum;

    for(i=0;i<1;i++) {
        *DataSize    += m_ulWAVSizeSlot[m_ulWAVSizeReadIdx+i];
        if(*DataSize >= MAX_WAV_OUTPUT_SIZE)
            break;
        tmpBufSizeNum--;
        if(tmpBufSizeNum == 0)
            break;
    }
       
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWAVDataDone
//------------------------------------------------------------------------------
/**
    @brief  get WAV data done, and update buffer pointers
    @param[in] DataSize : consumed data size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetWAVDataDone(MMP_ULONG DataSize)
{
	if(DataSize == 0)
        return MMP_ERR_NONE;
    if(m_ulWAVSizeNum == 0)
        return MMP_ERR_NONE;
    
    m_ucWAVBufRead  += m_ulWAVSlotSize;
    if( ((MMP_ULONG)m_ucWAVBufRead) >= ((MMP_ULONG)m_ucWAVBufStart + (m_ulWAVSlotSize*WAV_SLOT_NUM)))
    {
        m_ucWAVBufRead  = m_ucWAVBufStart;
    }
    
    m_ulWAVConsumedData += DataSize;
    DataSize -= m_ulWAVSizeSlot[m_ulWAVSizeReadIdx];
    m_ulWAVSizeReadIdx = (m_ulWAVSizeReadIdx + 1) % WAV_SLOT_NUM;
    
    m_ulWAVSizeNum--;
    
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWAVTime
//------------------------------------------------------------------------------
/**
    @brief get current time
    @param[in] time : time
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetWAVTime(MMP_ULONG *time)
{
	MMP_ULONG framesize = m_ulWAVSampleCount * 2;
	
	if (m_ulWAVSampleCount == 0) {
        *time = 0;
        return MMP_ERR_NONE;
    }
    
    *time = m_ulWAVStartTime + ((MMP_ULONG64)(m_ulWAVConsumedData / framesize) * m_ulWAVSampleCount * 1000 / m_ulWAVChans) / m_ulWAVSampleRate;
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetABRepeatMode
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Play AB Repeat Mode
    @param[in] usPoint : A or B
        -   MMPS_AUDIO_AB_MODE_POINTA : point A
        -   MMPS_AUDIO_AB_MODE_POINTB : point B
    @param[in] ulPos : position (in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetABRepeatMode(MMPS_AUDIO_ABMODE_POS usPoint, MMP_ULONG ulPos)
{
    MMPD_AUDIO_SetABRepeatMode(usPoint, ulPos);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnableABRepeatMode
//------------------------------------------------------------------------------
/**
    @brief  Enable AB Repeat Mode
    @param[in] ubEnable : enable or disable
        -   MMPS_AUDIO_AB_MODE_ENABLE
        -   MMPS_AUDIO_AB_MODE_DISABLE
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_EnableABRepeatMode(MMPS_AUDIO_ABMODE_SWITCH ubEnable)
{
    MMPD_AUDIO_EnableABRepeatMode(ubEnable);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_AACPlusPlayTime2FileOffset
//------------------------------------------------------------------------------
/**
    @brief  Convert AACPLUS Play Time to File offset
    @param[in]   ulMilliSec: milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_AACPlusPlayTime2FileOffset(MMP_ULONG ulMilliSec)
{
    MMP_ULONG   readsize;
    MMP_ULONG   align_offset;

    MMP_ULONG   fileoffset;
    #if (OMA_DRM_EN == 1)
    MMP_USHORT	drmEn;
    MMP_ULONG	drmOffset;
    MMP_UBYTE   drmIV[16];

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPD_AUDIO_AACPlusPlayTime2FileOffset(ulMilliSec, &fileoffset);
    align_offset = (fileoffset >> 9) << 9;

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle == 0)
                MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset + drmOffset - 16, MMPS_FS_SEEK_SET);
                MMPC_FS_FileRead(m_ulAudioPlayFileHandle, drmIV, 16, &readsize);
                MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
            }
            else {
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
            }
            #else
            MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
            #endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
        }

        MMPD_AUDIO_UpdatePlayStreamSize(m_ulAudioPlayFileSize - align_offset);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf + fileoffset, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize -  fileoffset, 0);
        }
        MMPS_AUDIO_TransferDataHostToDev();
        MMPD_AUDIO_SetPlayReadPtr(fileoffset - align_offset, 0);
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_MP3PlayTime2FileOffset
//------------------------------------------------------------------------------
/**
    @brief  Convert MP3 Play Time to File offset
    @param[in]   ulMilliSec: milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_MP3PlayTime2FileOffset(MMP_ULONG ulMilliSec)
{
    MMP_ULONG   readsize;
    MMP_ULONG   align_offset;

    MMP_ULONG   fileoffset;
    #if (OMA_DRM_EN == 1)
    MMP_USHORT	drmEn;
    MMP_ULONG	drmOffset;
    MMP_UBYTE   drmIV[16];

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPD_AUDIO_MP3PlayTime2FileOffset(ulMilliSec, &fileoffset);
    fileoffset += m_lMP3TagSize;
    align_offset = (fileoffset >> 9) << 9;

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle == 0)
                MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset + drmOffset - 16, MMPS_FS_SEEK_SET);
                MMPC_FS_FileRead(m_ulAudioPlayFileHandle, drmIV, 16, &readsize);
                MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
            }
            else {
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
            }
            #else
            MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
            #endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
        }

        MMPD_AUDIO_UpdatePlayStreamSize(m_ulAudioPlayFileSize + m_lMP3TagSize - align_offset);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf + fileoffset, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize -  fileoffset, 0);
        }
        MMPS_AUDIO_TransferDataHostToDev();
        MMPD_AUDIO_SetPlayReadPtr(fileoffset - align_offset, 0);
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_WAVPlayTime2FileOffset
//------------------------------------------------------------------------------
/**
    @brief  Convert WAV Play Time to File offset
    @param[in] ulMilliSec: milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_WAVPlayTime2FileOffset(MMP_ULONG ulMilliSec)
{
    MMP_ULONG   readsize;
    MMP_ULONG   align_offset;

    MMP_ULONG   fileoffset;
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   drmOffset;
    MMP_UBYTE   drmIV[16];

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

    MMPD_AUDIO_WAVPlayTime2FileOffset(ulMilliSec, &fileoffset);
    align_offset = (fileoffset >> 9) << 9;

    if ((m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM) || (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE)) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (m_ulAudioPlayFileHandle == 0)
                MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset + drmOffset - 16, MMPS_FS_SEEK_SET);
                MMPC_FS_FileRead(m_ulAudioPlayFileHandle, drmIV, 16, &readsize);
                MMPD_AUDIO_SetDRMIV(drmIV, MMPD_OMADRM_FOR_PLAY);
            }
            else {
                MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
            }
            #else
            MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
            #endif
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
        }

        MMPD_AUDIO_UpdatePlayStreamSize(m_ulAudioPlayFileSize - align_offset);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf + fileoffset, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize -  fileoffset, 0);
        }
        MMPS_AUDIO_TransferDataHostToDev();
        MMPD_AUDIO_SetPlayReadPtr(fileoffset - align_offset, 0);
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_AMRPlayTime2FileOffset
//------------------------------------------------------------------------------
/**
    @brief  Convert AMR Play Time to File offset
    @param[in]   ulMilliSec: milli second
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_AMRPlayTime2FileOffset(MMP_ULONG ulMilliSec)
{

    MMP_ULONG   readsize;
    MMP_ULONG   align_offset;

    MMP_ULONG   fileoffset;

    MMPD_AUDIO_AMRPlayTime2FileOffset(ulMilliSec, &fileoffset);
    align_offset = (fileoffset >> 9) << 9;

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM || m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            MMPC_FS_FileSeek(m_ulAudioPlayFileHandle, (MMP_LONG64)align_offset, MMPS_FS_SEEK_SET);
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
        }

        MMPD_AUDIO_UpdatePlayStreamSize(m_ulAudioPlayFileSize - align_offset);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf + fileoffset, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize -  fileoffset, 0);
        }
        MMPS_AUDIO_TransferDataHostToDev();
        MMPD_AUDIO_SetPlayReadPtr(fileoffset - align_offset, 0);
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetAC3VHPar
//------------------------------------------------------------------------------
/**
    @brief  Set virtualizer parameters, m3deff or db.
    @param[in] lm3deff : -1..10 (-1,0 ¡V no effect (simple downmixer will be used), 1 - min level, 10 ¡V max level)
    @param[in] ldb : dB = 0..20 ( prescaling value in dB, 0 ¡V no volume reduction )
    @param[in] bSet_m3deff : Set m3deff parameter or ignore
    @param[in] bSet_db : Set db parameter or ignore
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetAC3VHPar(MMP_LONG lm3deff, MMP_LONG ldb, MMP_BOOL bSet_m3deff, MMP_BOOL bSet_db)
{
    return MMPD_AUDIO_SetAC3VHPar(lm3deff, ldb, bSet_m3deff, bSet_db);
}
/// @ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetPlayIntThreshold
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Play Int Threshold(for memory mode)
    @param[in] usThreshold : threshold
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetPlayIntThreshold(MMP_USHORT usThreshold)
{
    MMPD_AUDIO_SetPlayIntThreshold(usThreshold);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetRecordIntThreshold
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Record Int Threshold(for memory mode)
    @param[in] usThreshold : threshold
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetRecordIntThreshold(MMP_USHORT usThreshold)
{
    MMPD_AUDIO_SetRecordIntThreshold(usThreshold);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitializePCMPlay
//------------------------------------------------------------------------------
/**
    @brief  Initialize PCM Play
    @param[in] *fileinfo : pcm file name input parameter

    @return MMP_ERR_NONE,MMP_AUDIO_ERR_UNSUPPORT_FORMAT
*/
MMP_ERR MMPS_AUDIO_InitializePCMPlay(MMPS_AUDIO_FILEINFO *fileinfo)
{
    MMP_ULONG64 filesize;
    MMP_ULONG   readsize;
    MMP_ULONG   bufsize;

    MMPD_AUDIO_SetOutPath(m_audioOutPath);
    MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_PCM_PLAY);
    MMPD_AUDIO_EnableABRepeatMode(MMPS_AUDIO_AB_MODE_DISABLE);
    MMPD_AUDIO_SetPlayPosition(0);

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_CARD) {
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    else if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_MEM || m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
        if (fileinfo->ubBuf == NULL || fileinfo->ulBufSize == 0) {
            PRINTF("Please set usMp3buf pointer and set ulMp3bufsize\r\n");
            return MMP_AUDIO_ERR_PARAMETER;
        }

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            if (fileinfo->ulBufSize & 0x3FF) {
                PRINTF("Please set ulMp3bufsize to be multiple of 1024\r\n");
                return MMP_AUDIO_ERR_PARAMETER;
            }
        }

        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
        MMPS_AUDIO_AllocateBuffer(MMPS_AUDIO_PCM_P_MEM_MODE);

        m_ubAudioPlayBuf = fileinfo->ubBuf;

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            STRCPY(m_bAudioPlayFileName, fileinfo->bFileName);
            m_usAudioPlayFileNameLength = fileinfo->usFileNameLength;
            m_ulAudioPlayBufSize = fileinfo->ulBufSize;

            MMPC_FS_FileOpen(m_bAudioPlayFileName, "r", &m_ulAudioPlayFileHandle);
            MMPC_FS_FileGetSize(m_ulAudioPlayFileHandle, &filesize);
            if (m_ulAudioPlayBufSize > filesize)
            	m_ulAudioPlayBufSize = filesize;
            MMPC_FS_FileRead(m_ulAudioPlayFileHandle, m_ubAudioPlayBuf, m_ulAudioPlayBufSize, &readsize);
            m_ulAudioPlayFileSize = filesize;
        }
        else {
            m_ulAudioPlayBufSize = 0xFFFFFFFF;  // infinite size
            m_ulAudioPlayFileSize = fileinfo->ulBufSize;
        }


        MMPD_AUDIO_GetAudioPlayBufSize(&bufsize);
        if (m_ulAudioPlayFileSize > bufsize) {
            return  MMP_AUDIO_ERR_INSUFFICIENT_BUF;
        }

        MMPD_AUDIO_SetPlayFileSize(m_ulAudioPlayFileSize);
        MMPD_AUDIO_InitPlayRWPtr();

        if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize, readsize, 1024);
        }
        else {
            MMPD_AUDIO_InitialMemModePointer(m_ubAudioPlayBuf, m_ulAudioPlayBufSize,
                                            m_ulAudioPlayFileSize, 0);
        }

        MMPS_AUDIO_TransferDataHostToDev();
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartPCMPlay
//------------------------------------------------------------------------------
/**
    @brief  Start PCM Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StartPCMPlay(void)
{
    return MMPD_AUDIO_StartAudioPlay(NULL, NULL);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopPCMPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop PCM Play
    @return MMP_ERR_NONE,MMPS_AUDIO_COMMAND_INVALID
*/
MMP_ERR MMPS_AUDIO_StopPCMPlay(void)
{
    MMP_ERR    status;
 
    status = MMPD_AUDIO_StopAudioPlay();
    if(status == MMP_AUDIO_ERR_COMMAND_INVALID){
	    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
			if (m_ulAudioPlayFileHandle) {	
	        	MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
				m_ulAudioPlayFileHandle = 0;
			}	
	    }
        return status;
    }

	MMPD_AUDIO_CheckPlayEnd();

    if (m_audioPath == MMPS_AUDIO_MEDIA_PATH_HOST_FILE) {
		if (m_ulAudioPlayFileHandle) {
			MMPC_FS_FileClose((void *)m_ulAudioPlayFileHandle);
			m_ulAudioPlayFileHandle = 0;
		}
    }

    return MMP_ERR_NONE;
}
/// @end_ait_only
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetEncodeFileSize
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Encode File Size(stop recording while over limitation)
    @param[in]  ulSize : file size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetEncodeFileSize(MMP_ULONG ulSize)
{
    MMPD_AUDIO_SetEncodeFileSize(ulSize);
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetPlayFileSize
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Play File Size to Firmware(Memory Mode)
    @param[in] ulFileSize : file size (in byte)
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SetPlayFileSize(MMP_ULONG ulFileSize)
{
    MMPD_AUDIO_SetPlayFileSize(ulFileSize);
    return MMP_ERR_NONE;
}


//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_OpenFile
//------------------------------------------------------------------------------
/**
    @brief  Open the audio file to playback
    
    @param[in] fileinfo      audio file information
    @param[in] ContainerInfo audio file information
    @param[in] AudioFormat   audio format
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_OpenFile(MMPS_AUDIO_FILEINFO	fileinfo, void* ContainerInfo,MMPS_AUDIO_CODEC AudioFormat) 
{
    MMP_ERR                 error = MMP_ERR_NONE;
    

    switch(AudioFormat)
    {
    case MMPS_AUDIO_CODEC_MP3:
        m_Mp3Info = (MMP_AUDIO_MP3_INFO*)ContainerInfo;
        
        #if 0//(MP3HD_DEC_EN == 1)
    	MMPS_AUDIO_SetMP3PlayID3CacheBuf((MMP_ULONG)ubMp3ID3CacheBuf, sizeof(ubMp3ID3CacheBuf), sizeof(ubMp3ID3CacheBuf));
    	#endif
	
        error = MMPS_AUDIO_InitializeMP3Play(&fileinfo, m_Mp3Info);
        
        if (m_Mp3Info->usNotSupport==1) {
            error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
        break;
    case MMPS_AUDIO_CODEC_WAV:
        m_WavInfo = (MMP_AUDIO_WAV_INFO*)ContainerInfo;
        
        error = MMPS_AUDIO_InitializeWAVPlay(&fileinfo, m_WavInfo);
        
        if (m_WavInfo->usNotSupport==1) {
            error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
        break;
    case MMPS_AUDIO_CODEC_MIDI:
        //TBD
        error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        break;
    case MMPS_AUDIO_CODEC_AMR:
        //TBD
        error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        break;
    case MMPS_AUDIO_CODEC_WMA:
        m_WMAproInfo = (MMP_AUDIO_WMA_INFO*)ContainerInfo;
        
        error = MMPS_AUDIO_InitializeWMAPlay(&fileinfo, m_WMAproInfo);
        
        if (m_WMAproInfo->usNotSupport==1) {
            error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
        break;
    case MMPS_AUDIO_CODEC_AAC:
        m_AacplusInfo = (MMP_AUDIO_AACPLUS_INFO*)ContainerInfo;
        
        error = MMPS_AUDIO_InitializeAACPlusPlay(&fileinfo, m_AacplusInfo);
    
        if (m_AacplusInfo->usNotSupport==1) {
            error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
        break;
    case MMPS_AUDIO_CODEC_OGG:
        m_OggInfo = (MMP_AUDIO_OGG_INFO*)ContainerInfo;
        
        error = MMPS_AUDIO_InitializeOGGPlay(&fileinfo, m_OggInfo);
        
        if (m_OggInfo->usNotSupport==1) {
            error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
        break;
    case MMPS_AUDIO_CODEC_RA:
        m_RaInfo = (MMP_AUDIO_RA_INFO*)ContainerInfo;
        
        error = MMPS_AUDIO_InitializeRAPlay(&fileinfo, m_RaInfo);
        
        if (m_RaInfo->usNotSupport==1) {
            error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
        break;
    case MMPS_AUDIO_CODEC_FLAC:
        m_FLACInfo = (MMP_AUDIO_FLAC_INFO*)ContainerInfo;
        
        error = MMPS_AUDIO_InitializeFLACPlay(&fileinfo, m_FLACInfo);
        
        if (m_FLACInfo->usNotSupport==1) {
            error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
        break;
    default:
        error = MMP_AUDIO_ERR_OPENFILE_FAIL;
        break;
    }
    
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartPlay
//------------------------------------------------------------------------------
/**
    @brief  Start Audio Playback
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_StartPlay(void* callBackFunc, void* context) {
    MMP_AUDIO_DECODE_FMT    format;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetPlayFormat(&format);
    
    m_pAudioCBFunc      = callBackFunc;
    m_pAudioCBContext   = context;
    
    switch(format)
    {
    case MMP_AUDIO_MP3_PLAY:
        error = MMPS_AUDIO_StartMP3Play(callBackFunc, context);
        break;
    case MMP_AUDIO_WAV_PLAY:
        error = MMPS_AUDIO_StartWAVPlay(callBackFunc, context);
        break;
    case MMP_AUDIO_MIDI_PLAY:
        error = MMPS_AUDIO_StartMIDIPlay();
        break;
    case MMP_AUDIO_AMR_PLAY:
        error = MMPS_AUDIO_StartAMRPlay();
        break;
    case MMP_AUDIO_WMA_PLAY:
        error = MMPS_AUDIO_StartWMAPlay(callBackFunc, context);
        break;
    case MMP_AUDIO_AAC_PLAY:
    case MMP_AUDIO_AACPLUS_PLAY:
        error = MMPS_AUDIO_StartAACPlusPlay(callBackFunc, context);
        break;
    case MMP_AUDIO_OGG_PLAY:
        error = MMPS_AUDIO_StartOGGPlay(callBackFunc, context);
        break;
    case MMP_AUDIO_RA_PLAY:
        error = MMPS_AUDIO_StartRAPlay(callBackFunc, context);
        break;
    case MMP_AUDIO_FLAC_PLAY:
        error = MMPS_AUDIO_StartFLACPlay(callBackFunc, context);
        break;
    default:
        break;
    }
    return error;
}


//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PausePlay
//------------------------------------------------------------------------------
/**
    @brief  Pause Audio Playback
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_PausePlay() {
    MMP_AUDIO_DECODE_FMT    format;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetPlayFormat(&format);
    
    switch(format)
    {
    case MMP_AUDIO_MP3_PLAY:
        error = MMPS_AUDIO_PauseMP3Play();
        break;
    case MMP_AUDIO_WAV_PLAY:
        error = MMPS_AUDIO_PauseWAVPlay();
        break;
    case MMP_AUDIO_MIDI_PLAY:
        error = MMPS_AUDIO_PauseMIDIPlay();
        break;
    case MMP_AUDIO_AMR_PLAY:
        error = MMPS_AUDIO_PauseAMRPlay();
        break;
    case MMP_AUDIO_WMA_PLAY:
        error = MMPS_AUDIO_PauseWMAPlay();
        break;
    case MMP_AUDIO_AAC_PLAY:
    case MMP_AUDIO_AACPLUS_PLAY:
        error = MMPS_AUDIO_PauseAACPlusPlay();
        break;
    case MMP_AUDIO_OGG_PLAY:
        error = MMPS_AUDIO_PauseOGGPlay();
        break;
    case MMP_AUDIO_RA_PLAY:
        error = MMPS_AUDIO_PauseRAPlay();
        break;
    case MMP_AUDIO_FLAC_PLAY:
        error = MMPS_AUDIO_PauseFLACPlay();
        break;
    default:
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumePlay
//------------------------------------------------------------------------------
/**
    @brief  Resume Audio Playback
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_ResumePlay() {
    MMP_AUDIO_DECODE_FMT    format;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetPlayFormat(&format);
    
    switch(format)
    {
    case MMP_AUDIO_MP3_PLAY:
        error = MMPS_AUDIO_ResumeMP3Play();
        break;
    case MMP_AUDIO_WAV_PLAY:
        error = MMPS_AUDIO_ResumeWAVPlay();
        break;
    case MMP_AUDIO_MIDI_PLAY:
        error = MMPS_AUDIO_ResumeMIDIPlay();
        break;
    case MMP_AUDIO_AMR_PLAY:
        error = MMPS_AUDIO_ResumeAMRPlay();
        break;
    case MMP_AUDIO_WMA_PLAY:
        error = MMPS_AUDIO_ResumeWMAPlay();
        break;
    case MMP_AUDIO_AAC_PLAY:
    case MMP_AUDIO_AACPLUS_PLAY:
        error = MMPS_AUDIO_ResumeAACPlusPlay();
        break;
    case MMP_AUDIO_OGG_PLAY:
        error = MMPS_AUDIO_ResumeOGGPlay();
        break;
    case MMP_AUDIO_RA_PLAY:
        error = MMPS_AUDIO_ResumeRAPlay();
        break;
    case MMP_AUDIO_FLAC_PLAY:
        error = MMPS_AUDIO_ResumeFLACPlay();
        break;
    default:
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopPlay
//------------------------------------------------------------------------------
/**
    @brief  Stop Audio Playback
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_StopPlay(void) 
{
    MMP_AUDIO_DECODE_FMT    format;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetPlayFormat(&format);
    
    switch(format)
    {
    case MMP_AUDIO_MP3_PLAY:
        error = MMPS_AUDIO_StopMP3Play();
        break;
    case MMP_AUDIO_WAV_PLAY:
        error = MMPS_AUDIO_StopWAVPlay();
        break;
    case MMP_AUDIO_MIDI_PLAY:
        error = MMPS_AUDIO_StopMIDIPlay();
        break;
    case MMP_AUDIO_AMR_PLAY:
        error = MMPS_AUDIO_StopAMRPlay();
        break;
    case MMP_AUDIO_WMA_PLAY:
        error = MMPS_AUDIO_StopWMAPlay();
        break;
    case MMP_AUDIO_AAC_PLAY:
    case MMP_AUDIO_AACPLUS_PLAY:
        error = MMPS_AUDIO_StopAACPlusPlay();
        break;
    case MMP_AUDIO_OGG_PLAY:
        error = MMPS_AUDIO_StopOGGPlay();
        break;
    case MMP_AUDIO_RA_PLAY:
        error = MMPS_AUDIO_StopRAPlay();
        break;
    case MMP_AUDIO_FLAC_PLAY:
        error = MMPS_AUDIO_StopFLACPlay();
        break;
    default:
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetPlayTime
//------------------------------------------------------------------------------
/**
    @brief  Get Current Play Time
    @param[out] *usTimeRatio : (current time) / (total time)
    @param[out] *ulPlayTime : current play time (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT

    @pre Playback must be already started (may be in playing, paused, or stopped state) 
         before get play time. Otherwise, unexpected values returned will be returned.
*/
MMP_ERR MMPS_AUDIO_GetPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime)
{
    MMP_AUDIO_DECODE_FMT    format;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetPlayFormat(&format);
    
    switch(format)
    {
    case MMP_AUDIO_MP3_PLAY:
        error = MMPS_AUDIO_GetMP3PlayTime(usTimeRatio, ulPlayTime);
        break;
    case MMP_AUDIO_WAV_PLAY:
        error = MMPS_AUDIO_GetWAVPlayTime(ulPlayTime);
        break;
    case MMP_AUDIO_MIDI_PLAY:
        error = MMPS_AUDIO_GetMIDIPlayTime(usTimeRatio, ulPlayTime);
        break;
    case MMP_AUDIO_AMR_PLAY:
        error = MMPS_AUDIO_GetAMRPlayTime(usTimeRatio, ulPlayTime);
        break;
    case MMP_AUDIO_WMA_PLAY:
        error = MMPS_AUDIO_GetWMAPlayTime(usTimeRatio, ulPlayTime);
        break;
    case MMP_AUDIO_AAC_PLAY:
    case MMP_AUDIO_AACPLUS_PLAY:
        error = MMPS_AUDIO_GetAACPlusPlayTime(usTimeRatio, ulPlayTime);
        break;
    case MMP_AUDIO_OGG_PLAY:
        error = MMPS_AUDIO_GetOGGPlayTime(ulPlayTime);
        break;
    case MMP_AUDIO_RA_PLAY:
        error = MMPS_AUDIO_GetRAPlayTime(usTimeRatio, ulPlayTime);
        break;
    case MMP_AUDIO_FLAC_PLAY:
        error = MMPS_AUDIO_GetFLACPlayTime(usTimeRatio, ulPlayTime);
        break;
    default:
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SeekByTime
//------------------------------------------------------------------------------
/**
    @brief  Seek Audio to the target time
    
    @param[in] TargetTime Target time
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_SeekByTime(MMP_LONG TargetTime) 
{
    MMP_AUDIO_DECODE_FMT    format;
    MMP_ERR                 error = MMP_ERR_NONE;
    #if (GAPLESS_PLAY_EN == 1)
    MMP_BOOL                bOpAllowed = MMP_TRUE;
    #endif
    
    #if (GAPLESS_PLAY_EN == 1)
    MMPS_AUDIO_ChkOperationAllowed(MMP_AUDIO_GAPLESS_SEEK, &bOpAllowed);
    if (!bOpAllowed) {
        PRINTF("Seek is not alllowed in this period!\r\n");
        return MMP_AUDIO_ERR_COMMAND_INVALID;
    }
    #endif
                
    MMPD_AUDIO_GetPlayFormat(&format);
    
    switch(format)
    {
    case MMP_AUDIO_MP3_PLAY:
        error = MMPS_AUDIO_StopMP3Play();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_Mp3Info->ulTotalTime ) {
                TargetTime = m_Mp3Info->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetMP3PlayTime(TargetTime);
            error = MMPS_AUDIO_StartMP3Play(m_pAudioCBFunc, m_pAudioCBContext);
        }
        break;
    case MMP_AUDIO_WAV_PLAY:
        error = MMPS_AUDIO_StopWAVPlay();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_WavInfo->ulTotalTime ) {
                TargetTime = m_WavInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetWAVPlayTime(TargetTime);
            error = MMPS_AUDIO_StartWAVPlay(m_pAudioCBFunc, m_pAudioCBContext);
        }
        
        break;
    case MMP_AUDIO_MIDI_PLAY:
        error = MMPS_AUDIO_StopMIDIPlay();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_MIDIInfo->ulTotalTime ) {
                TargetTime = m_MIDIInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetMIDIPlayTime(TargetTime);
            error = MMPS_AUDIO_StartMIDIPlay();
        }
        break;
    case MMP_AUDIO_AMR_PLAY:
        error = MMPS_AUDIO_StopAMRPlay();
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_AmrInfo->ulTotalTime ) {
                TargetTime = m_AmrInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetAMRPlayTime(TargetTime);
            error = MMPS_AUDIO_StartAMRPlay();
        }
        break;
    case MMP_AUDIO_WMA_PLAY:
        error = MMPS_AUDIO_StopWMAPlay();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_WMAproInfo->ulTotalTime ) {
                TargetTime = m_WMAproInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetWMAPlayTime(TargetTime);
            error = MMPS_AUDIO_StartWMAPlay(m_pAudioCBFunc, m_pAudioCBContext);
        }
        
        break;
    case MMP_AUDIO_AAC_PLAY:
    case MMP_AUDIO_AACPLUS_PLAY:
        error = MMPS_AUDIO_StopAACPlusPlay();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_AacplusInfo->ulTotalTime ) {
                TargetTime = m_AacplusInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetAACPlusPlayTime(TargetTime);
            error = MMPS_AUDIO_StartAACPlusPlay(m_pAudioCBFunc, m_pAudioCBContext);
        }
        
        break;
    case MMP_AUDIO_OGG_PLAY:
        error = MMPS_AUDIO_StopOGGPlay();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_OggInfo->ulTotalTime ) {
                TargetTime = m_OggInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetOGGPlayTime(TargetTime);
            error = MMPS_AUDIO_StartOGGPlay(m_pAudioCBFunc, m_pAudioCBContext);
        }
        
        break;
    case MMP_AUDIO_RA_PLAY:
        error = MMPS_AUDIO_StopRAPlay();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_RaInfo->ulTotalTime ) {
                TargetTime = m_RaInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetRAPlayTime(TargetTime);
            error = MMPS_AUDIO_StartRAPlay(m_pAudioCBFunc, m_pAudioCBContext);
        }
        
        break;
    case MMP_AUDIO_FLAC_PLAY:
        error = MMPS_AUDIO_StopFLACPlay();
        
        if ( MMP_ERR_NONE == error ) {
            if ( TargetTime >= m_FLACInfo->ulTotalTime ) {
                TargetTime = m_FLACInfo->ulTotalTime;
            }
            else if ( TargetTime < 0 ) {
                TargetTime = 0;
            }
            
            error = MMPS_AUDIO_SetFLACPlayTime(TargetTime);
            error = MMPS_AUDIO_StartFLACPlay(m_pAudioCBFunc, m_pAudioCBContext);
        }
        
        break;
    default:
        break;
    }
    return error;
}

/// @ait_only
#if (SUPPORT_MTP_FUNC == 1)
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_OpenMusicListFile
//------------------------------------------------------------------------------
/**
    @brief  Open MusicList File
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_OPENFILE_FAIL
*/
MMP_ERR  MMPS_AUDIO_OpenMusicListFile(void)
{
    MMP_ERR fs_status;
    MMP_ULONG read_count,i;
    MMPS_AUDIO_MUSICLIST_HEADER list_header;

    fs_status = MMPS_FS_FileOpen(MMPS_AUDIO_MUSICLIST_FILENAME , STRLEN(MMPS_AUDIO_MUSICLIST_FILENAME),
                                            "r+", STRLEN("r+"), &m_usMusicListFileId);

    if (MMP_ERR_NONE != fs_status){
        MMPC_FS_FileClose((void*)m_usMusicListFileId);
        PRINTF("Open MusicList File Fails\r\n");

        return MMP_AUDIO_ERR_OPENFILE_FAIL;
    }

    MMPS_FS_FileRead(m_usMusicListFileId, (void *) &list_header, sizeof(MMPS_AUDIO_MUSICLIST_HEADER),&read_count);

    m_MusicListListInfo.ObjCnt = list_header.ObjCnt;

    if(list_header.ObjCnt>MMPS_AUDIO_MUSICLIST_MAX_OBJECT){
        m_MusicListListInfo.ObjCnt = MMPS_AUDIO_MUSICLIST_MAX_OBJECT;
    }

    for(i=0;i<m_MusicListListInfo.ObjCnt;i++){
        MMPS_FS_FileRead(m_usMusicListFileId, (void *) &m_MusicListListInfo.ListContent, sizeof(MMPS_AUDIO_MUSICLIST_CONTENT),&read_count);
        m_MusicListListInfo.FileFmt[i] = m_MusicListListInfo.ListContent.FileFmt;
        m_MusicListListInfo.Flag[i] = m_MusicListListInfo.ListContent.Flag;
    }

    m_MusicListListInfo.CurrentContentIndex = m_MusicListListInfo.ObjCnt-1;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_CloseMusicListFile
//------------------------------------------------------------------------------
/**
    @brief  Close MusicList File
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_CloseMusicListFile(void)
{
    MMPS_FS_FileClose(m_usMusicListFileId);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_UniStrCmp
//------------------------------------------------------------------------------
/**
    @brief  Compare 2 unicode str
    @param[in] *usStr1 : unicode string 1
    @param[in] *usStr2 : unicode string 2
    @param[out] *usResult : compare result
                - MMPS_AUDIO_STR_EXACT
                - MMPS_AUDIO_STR_DIFFERENT
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_UniStrCmp(MMP_USHORT *usStr1,MMP_USHORT *usStr2,MMP_USHORT *usResult)
{
    MMP_USHORT length,i;

    *usResult = MMPS_AUDIO_STR_EXACT;

    if(usStr1[0]!=usStr2[0]){

        *usResult = MMPS_AUDIO_STR_DIFFERENT;

        return MMP_ERR_NONE;
    }
    length = usStr1[0];

    for(i=1;i<=length;i++){
        if(usStr1[i]!=usStr2[i]){
            *usResult = MMPS_AUDIO_STR_DIFFERENT;
            break;
        }
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ChkSupportFmt
//------------------------------------------------------------------------------
/**
    @brief  Check Support Format
    @param[in] *usStr1 : unicode string 1
    @param[out] *usResult : chk result
                - MMPS_AUDIO_SUPPORT_FORMAT
                - MMPS_AUDIO_UNSUPPORT_FORMAT
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_ChkSupportFmt(MMP_USHORT usIdx,MMP_USHORT *usResult)
{

    if((m_MusicListListInfo.FileFmt[usIdx]==MMPS_AUDIO_FORMAT_ASF)||(m_MusicListListInfo.FileFmt[usIdx]==MMPS_AUDIO_FORMAT_WMA)&&(m_MusicListListInfo.Flag[usIdx]==0)){
        *usResult =  MMPS_AUDIO_SUPPORT_FORMAT;
    }else{
        *usResult = MMPS_AUDIO_UNSUPPORT_FORMAT;
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ReadMusicListContent
//------------------------------------------------------------------------------
/**
    @brief  Read Contest of Music List Using Index
    @param[in] ulIndex: music list index
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_ReadMusicListContent(MMP_ULONG ulIndex)
{
    MMP_LONG64 offset;
    MMP_ULONG  read_count;

    if(ulIndex!=m_MusicListListInfo.CurrentContentIndex){
        if(ulIndex>m_MusicListListInfo.CurrentContentIndex){
            offset = (((MMP_LONG64)ulIndex-m_MusicListListInfo.CurrentContentIndex-1)*sizeof(MMPS_AUDIO_MUSICLIST_CONTENT));
            MMPS_FS_FileSeek(m_usMusicListFileId, offset, MMPS_FS_SEEK_CUR);
            MMPS_FS_FileRead(m_usMusicListFileId, (void *) &m_MusicListListInfo.ListContent, sizeof(MMPS_AUDIO_MUSICLIST_CONTENT),&read_count);
        }else{
            offset = ((MMP_LONG64)ulIndex*sizeof(MMPS_AUDIO_MUSICLIST_CONTENT))+sizeof(MMPS_AUDIO_MUSICLIST_HEADER);
            MMPS_FS_FileSeek(m_usMusicListFileId, offset, MMPS_FS_SEEK_SET);
            MMPS_FS_FileRead(m_usMusicListFileId, (void *) &m_MusicListListInfo.ListContent, sizeof(MMPS_AUDIO_MUSICLIST_CONTENT),&read_count);
        }
        m_MusicListListInfo.CurrentContentIndex =  ulIndex;
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_WriteMusicListContent
//------------------------------------------------------------------------------
/**
    @brief  Write Contest of Music List Usign Index
    @param[in] ulIndex: music list index
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_WriteMusicListContent(MMP_ULONG ulIndex)
{
    MMP_LONG64 offset;
    MMP_ULONG  write_count;

    offset = ((MMP_LONG64)ulIndex*sizeof(MMPS_AUDIO_MUSICLIST_CONTENT)) + sizeof(MMPS_AUDIO_MUSICLIST_HEADER);
    MMPS_FS_FileSeek(m_usMusicListFileId, offset, MMPS_FS_SEEK_SET);
    MMPS_FS_FileWrite(m_usMusicListFileId,(void *) &m_MusicListListInfo.ListContent, sizeof(MMPS_AUDIO_MUSICLIST_CONTENT),&write_count);
    MMPS_FS_FileClose(m_usMusicListFileId);

    MMPS_FS_FileOpen(MMPS_AUDIO_MUSICLIST_FILENAME , STRLEN(MMPS_AUDIO_MUSICLIST_FILENAME),
                                            "r+", STRLEN("r+"), &m_usMusicListFileId);

    ulIndex++;
    offset = ((MMP_LONG64)ulIndex*sizeof(MMPS_AUDIO_MUSICLIST_CONTENT)) + sizeof(MMPS_AUDIO_MUSICLIST_HEADER);
    MMPS_FS_FileSeek(m_usMusicListFileId, offset, MMPS_FS_SEEK_SET);


    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetObjNameFromFullPath
//------------------------------------------------------------------------------
/**
    @brief  Get Object Name From Full Path
    @param[in] *usFullPath: full-path name string
    @param[in] *usObjectName: object name string
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_GetObjNameFromFullPath(MMP_USHORT *usFullPath,MMP_USHORT *usObjectName)
{
    MMP_SHORT length,i,j;

    length = usFullPath[0];

    for(i=length;i>=0;i--){
        if(usFullPath[i]==0x005C){
            break;
        }
    }
    i++;
    j=1;
    for(;i<=length;i++){
        usObjectName[j++] = usFullPath[i];
    }
    usObjectName[0] = j-1;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetObjFullPath
//------------------------------------------------------------------------------
/**
    @brief  Get Object Full-Path Name
    @param[out] *usUniString : full-path name string
    @param[in] usId: object id
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_GetObjFullPath(MMP_USHORT *usUniString,MMP_USHORT usId)
{
    MMP_USHORT i;

    MMPS_AUDIO_ReadMusicListContent(usId);

    usUniString[0] = m_MusicListListInfo.ListContent.FileName[0];
    for(i=1;i<=m_MusicListListInfo.ListContent.FileName[0];i++){
        usUniString[i] = m_MusicListListInfo.ListContent.FileName[i];
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_OpenEnumObjPrpty
//------------------------------------------------------------------------------
/**
    @brief  Open Enum Object Property
    @param[in] Property: object proprety
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_OpenEnumObjPrpty(MMPS_AUDIO_OBJECT_PROPERTY Property)
{
    m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex = 0;
    m_MusicListListInfo.EnumObjPrptyInfo.ArtistCnt = 0;
    m_MusicListListInfo.EnumObjPrptyInfo.GenreCnt = 0;
    m_MusicListListInfo.EnumObjPrptyInfo.AlbumNameCnt = 0;
    m_MusicListListInfo.EnumObjPrptyInfo.Property = Property;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnumObjPrpty
//------------------------------------------------------------------------------
/**
    @brief  Enum Object Property
    @param[out] *usUniString : property string
    @param[out] *usId: property id
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_END_OF_FILE
*/
MMP_ERR  MMPS_AUDIO_EnumObjPrpty(MMP_USHORT *usUniString,MMP_USHORT *usId)
{
    MMP_ULONG i,while_loop;
    MMP_USHORT cmp_result,unknowm_str,chk_support_format_result;

    while_loop = 1;

    while(while_loop){
        unknowm_str = 0;

        for(i=m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex;i<m_MusicListListInfo.ObjCnt;i++){

            MMPS_AUDIO_ChkSupportFmt(i,&chk_support_format_result);
            if(chk_support_format_result==MMPS_AUDIO_SUPPORT_FORMAT){
                break;
            }

            m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex++;
        }
        //PRINTF("%d--i\r\n",i);

        if(i==m_MusicListListInfo.ObjCnt){
            return MMP_AUDIO_ERR_END_OF_FILE;
        }

        MMPS_AUDIO_ReadMusicListContent(m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex);

        switch(m_MusicListListInfo.EnumObjPrptyInfo.Property){
            case MMPS_AUDIO_OBJECT_NAME:
                *usId = m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex;

                MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);

                while_loop = 0;
                break;

            case MMPS_AUDIO_ALBUM:
                if(m_MusicListListInfo.ListContent.AlbumName[0]==0){
                    unknowm_str = 1;
                }

                for(i=0;i<m_MusicListListInfo.EnumObjPrptyInfo.AlbumNameCnt;i++){
                    if(unknowm_str==1){
                        MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i],m_UnknownUniStr,&cmp_result);
                    }else{
                        MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i],m_MusicListListInfo.ListContent.AlbumName,&cmp_result);
                    }
                    if(cmp_result==MMPS_AUDIO_STR_EXACT){
                        break;
                    }
                }

                if(i==m_MusicListListInfo.EnumObjPrptyInfo.AlbumNameCnt){
                    if(m_MusicListListInfo.EnumObjPrptyInfo.AlbumNameCnt==MMPS_AUDIO_MAX_OBJ_PROPERTY_NUM){
                        return MMP_AUDIO_ERR_END_OF_FILE;
                    }
                    if(unknowm_str){
                        m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i][0] = m_UnknownUniStr[0];
                        usUniString[0] = m_UnknownUniStr[0];
                        for(i=1;i<=m_UnknownUniStr[0];i++){
                            m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[m_MusicListListInfo.EnumObjPrptyInfo.AlbumNameCnt][i] = m_UnknownUniStr[i];
                            usUniString[i] = m_UnknownUniStr[i];
                        }
                    }else{
                        m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i][0] = m_MusicListListInfo.ListContent.AlbumName[0];
                        usUniString[0] = m_MusicListListInfo.ListContent.AlbumName[0];
                        for(i=1;i<=m_MusicListListInfo.ListContent.AlbumName[0];i++){
                            m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[m_MusicListListInfo.EnumObjPrptyInfo.AlbumNameCnt][i] = m_MusicListListInfo.ListContent.AlbumName[i];
                            usUniString[i] = m_MusicListListInfo.ListContent.AlbumName[i];
                        }
                    }

                    *usId = m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex;
                    m_MusicListListInfo.EnumObjPrptyInfo.AlbumNameCnt++;
                    while_loop = 0;
                }
                break;

            case MMPS_AUDIO_ARTIST:
                if(m_MusicListListInfo.ListContent.Artist[0]==0){
                    unknowm_str = 1;
                }

                for(i=0;i<m_MusicListListInfo.EnumObjPrptyInfo.ArtistCnt;i++){
                    if(unknowm_str==1){
                        MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i],m_UnknownUniStr,&cmp_result);
                    }else{
                        MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i],m_MusicListListInfo.ListContent.Artist,&cmp_result);
                    }
                    if(cmp_result==MMPS_AUDIO_STR_EXACT){
                        break;
                    }
                }

                if(i==m_MusicListListInfo.EnumObjPrptyInfo.ArtistCnt){
                    if(m_MusicListListInfo.EnumObjPrptyInfo.ArtistCnt==MMPS_AUDIO_MAX_OBJ_PROPERTY_NUM){
                        return MMP_AUDIO_ERR_END_OF_FILE;
                    }
                    if(unknowm_str){
                        m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i][0] = m_UnknownUniStr[0];
                        usUniString[0] = m_UnknownUniStr[0];
                        for(i=1;i<=m_UnknownUniStr[0];i++){
                            m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[m_MusicListListInfo.EnumObjPrptyInfo.ArtistCnt][i] = m_UnknownUniStr[i];
                            usUniString[i] = m_UnknownUniStr[i];
                        }
                    }else{
                        m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i][0] = m_MusicListListInfo.ListContent.Artist[0];
                        usUniString[0] = m_MusicListListInfo.ListContent.Artist[0];
                        for(i=1;i<=m_MusicListListInfo.ListContent.Artist[0];i++){
                            m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[m_MusicListListInfo.EnumObjPrptyInfo.ArtistCnt][i] = m_MusicListListInfo.ListContent.Artist[i];
                            usUniString[i] = m_MusicListListInfo.ListContent.Artist[i];
                        }
                    }

                    *usId = m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex;
                    m_MusicListListInfo.EnumObjPrptyInfo.ArtistCnt++;
                    while_loop = 0;
                }
                break;

            case MMPS_AUDIO_GENRE:
                if(m_MusicListListInfo.ListContent.Genre[0]==0){
                    unknowm_str = 1;
                }

                for(i=0;i<m_MusicListListInfo.EnumObjPrptyInfo.GenreCnt;i++){
                    if(unknowm_str==1){
                        MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i],m_UnknownUniStr,&cmp_result);
                    }else{
                        MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i],m_MusicListListInfo.ListContent.Genre,&cmp_result);
                    }
                    if(cmp_result==MMPS_AUDIO_STR_EXACT){
                        break;
                    }
                }

                if(i==m_MusicListListInfo.EnumObjPrptyInfo.GenreCnt){
                    if(m_MusicListListInfo.EnumObjPrptyInfo.GenreCnt==MMPS_AUDIO_MAX_OBJ_PROPERTY_NUM){
                        return MMP_AUDIO_ERR_END_OF_FILE;
                    }
                    if(unknowm_str){
                        m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i][0] = m_UnknownUniStr[0];
                        usUniString[0] = m_UnknownUniStr[0];
                        for(i=1;i<=m_UnknownUniStr[0];i++){
                            m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[m_MusicListListInfo.EnumObjPrptyInfo.GenreCnt][i] = m_UnknownUniStr[i];
                            usUniString[i] = m_UnknownUniStr[i];
                        }
                    }else{
                        m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[i][0] = m_MusicListListInfo.ListContent.Genre[0];
                        usUniString[0] = m_MusicListListInfo.ListContent.Genre[0];
                        for(i=1;i<=m_MusicListListInfo.ListContent.Genre[0];i++){
                            m_MusicListListInfo.EnumObjPrptyInfo.PrptyStr[m_MusicListListInfo.EnumObjPrptyInfo.GenreCnt][i] = m_MusicListListInfo.ListContent.Genre[i];
                            usUniString[i] = m_MusicListListInfo.ListContent.Genre[i];
                        }
                    }

                    *usId = m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex;
                    m_MusicListListInfo.EnumObjPrptyInfo.GenreCnt++;
                    while_loop = 0;
                }
                break;
        }
        m_MusicListListInfo.EnumObjPrptyInfo.CurrentIndex++;

    }
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_OpenEnumObjByPrpty
//------------------------------------------------------------------------------
/**
    @brief  Open Enum Object Name By Property
    @param[in] Property: object proprety
    @param[out] usId: property id
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_OpenEnumObjByPrpty(MMPS_AUDIO_OBJECT_PROPERTY Property,MMP_USHORT usId)
{
    MMP_USHORT *usUniString,i;
    m_MusicListListInfo.EnumObjInfo.PropertyId = usId;
    m_MusicListListInfo.EnumObjInfo.Property = Property;
    m_MusicListListInfo.EnumObjInfo.CurrentIndex = 0;
    usUniString = m_MusicListListInfo.EnumObjInfo.PrptyStr;

    if(usId!=0xFFFF){
        MMPS_AUDIO_ReadMusicListContent(usId);

        switch(m_MusicListListInfo.EnumObjInfo.Property){
            case MMPS_AUDIO_ALBUM:
                usUniString[0] = m_MusicListListInfo.ListContent.AlbumName[0];
                for(i=1;i<=m_MusicListListInfo.ListContent.AlbumName[0];i++){
                    usUniString[i] = m_MusicListListInfo.ListContent.AlbumName[i];
                }
                break;

            case MMPS_AUDIO_ARTIST:
                usUniString[0] = m_MusicListListInfo.ListContent.Artist[0];
                for(i=1;i<=m_MusicListListInfo.ListContent.Artist[0];i++){
                    usUniString[i] = m_MusicListListInfo.ListContent.Artist[i];
                }
                break;

            case MMPS_AUDIO_GENRE:
                usUniString[0] = m_MusicListListInfo.ListContent.Genre[0];
                for(i=1;i<=m_MusicListListInfo.ListContent.Genre[0];i++){
                    usUniString[i] = m_MusicListListInfo.ListContent.Genre[i];
                }
                break;
    }
    }
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnumObjByPrpty
//------------------------------------------------------------------------------
/**
    @brief  Enum Object Name By Property
    @param[out] *usUniString : Object name string
    @param[out] *usId: object id
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_END_OF_FILE
*/
MMP_ERR  MMPS_AUDIO_EnumObjByPrpty(MMP_USHORT *usUniString,MMP_USHORT *usId)
{

    MMP_ULONG i,while_loop;
    MMP_USHORT cmp_result,chk_support_format_result,unknown_str;

    if(m_MusicListListInfo.EnumObjInfo.PropertyId==0xFFFF){
        unknown_str = 1;
    }else{
        unknown_str = 0;
    }
    while_loop = 1;

    while(while_loop){

        for(i=m_MusicListListInfo.EnumObjInfo.CurrentIndex;i<m_MusicListListInfo.ObjCnt;i++){

            MMPS_AUDIO_ChkSupportFmt(i,&chk_support_format_result);
            if(chk_support_format_result==MMPS_AUDIO_SUPPORT_FORMAT){
                break;
            }

            m_MusicListListInfo.EnumObjInfo.CurrentIndex++;
        }

        if(i==m_MusicListListInfo.ObjCnt){
            return MMP_AUDIO_ERR_END_OF_FILE;
        }

        MMPS_AUDIO_ReadMusicListContent(m_MusicListListInfo.EnumObjInfo.CurrentIndex);
        *usId = m_MusicListListInfo.EnumObjInfo.CurrentIndex;

        switch(m_MusicListListInfo.EnumObjInfo.Property){
            case MMPS_AUDIO_ALBUM:
                if(unknown_str==1){
                    if(m_MusicListListInfo.ListContent.AlbumName[0]==0){
                        MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);
                        while_loop=0;
                    }
                }else{
                    MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjInfo.PrptyStr,m_MusicListListInfo.ListContent.AlbumName,&cmp_result);
                    if(cmp_result==MMPS_AUDIO_STR_EXACT){
                        MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);
                        while_loop=0;
                    }
                }

                break;

            case MMPS_AUDIO_ARTIST:
                if(unknown_str==1){
                    if(m_MusicListListInfo.ListContent.Artist[0]==0){
                        MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);
                        while_loop=0;
                    }
                }else{
                    MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjInfo.PrptyStr,m_MusicListListInfo.ListContent.Artist,&cmp_result);
                    if(cmp_result==MMPS_AUDIO_STR_EXACT){
                        MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);
                        while_loop=0;
                    }
                }
                break;

            case MMPS_AUDIO_GENRE:
                if(unknown_str==1){
                    if(m_MusicListListInfo.ListContent.Genre[0]==0){
                        MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);
                        while_loop=0;
                    }
                }else{
                    MMPS_AUDIO_UniStrCmp(m_MusicListListInfo.EnumObjInfo.PrptyStr,m_MusicListListInfo.ListContent.Genre,&cmp_result);
                    if(cmp_result==MMPS_AUDIO_STR_EXACT){
                        MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);
                        while_loop=0;
                    }
                }
                break;
        }
        m_MusicListListInfo.EnumObjInfo.CurrentIndex++;

    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_UTF16ToUTF8
//------------------------------------------------------------------------------
/**
    @brief  Convert UTF16 String to UTF8 String
    @param[in] *usUTF16Str : utf16 string
    @param[out] *ubUTF8Str: utf8 string
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_UTF16ToUTF8(MMP_USHORT *usUTF16Str,MMP_UBYTE *ubUTF8Str)
{
    MMP_ULONG j,r;
    MMP_USHORT utf16_char;
    MMP_UBYTE *s;

    j=1;
    s = ubUTF8Str;

    while(j<=usUTF16Str[0]){

        utf16_char = usUTF16Str[j++];

        if (utf16_char & 0xF800) {
            r = 3;
        } else if (utf16_char & 0xFF80) {
            r = 2;
        } else {
            r = 1;
        }

        switch (r) {
            case 1:
                *s++ = utf16_char;
                break;
            case 2:
                *s++ = 0xC0 | (utf16_char >> 6);
                *s++ = 0x80 | (utf16_char & 0x3F);
                break;
            case 3:
                *s++ = 0xE0 | (utf16_char >> 12);
                *s++ = 0x80 | ((utf16_char >> 6) & 0x3F);
                *s++ = 0x80 | (utf16_char & 0x3F);
                break;
        }
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetObjPrpty
//------------------------------------------------------------------------------
/**
    @brief  Get Object Property
    @param[in] Property: object proprety
    @param[out] *usUniString :  property string
    @param[in] usId: object id
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_GetObjPrpty(MMPS_AUDIO_OBJECT_PROPERTY Property,MMP_USHORT *usUniString,MMP_USHORT usId)
{
    MMP_USHORT i;

    MMPS_AUDIO_ReadMusicListContent(usId);

    switch(Property){
        case MMPS_AUDIO_OBJECT_NAME:

                MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);
            break;

        case MMPS_AUDIO_ALBUM:
            if(m_MusicListListInfo.ListContent.AlbumName[0]==0){
                usUniString[0] = m_UnknownUniStr[0];
                for(i=1;i<=m_UnknownUniStr[0];i++){
                    usUniString[i] = m_UnknownUniStr[i];
                }
            }else{
                usUniString[0] = m_MusicListListInfo.ListContent.AlbumName[0];
                for(i=1;i<=m_MusicListListInfo.ListContent.AlbumName[0];i++){
                    usUniString[i] = m_MusicListListInfo.ListContent.AlbumName[i];
                }
            }
            break;

        case MMPS_AUDIO_ARTIST:
            if(m_MusicListListInfo.ListContent.Artist[0]==0){
                usUniString[0] = m_UnknownUniStr[0];
                for(i=1;i<=m_UnknownUniStr[0];i++){
                    usUniString[i] = m_UnknownUniStr[i];
                }
            }else{
                usUniString[0] = m_MusicListListInfo.ListContent.Artist[0];
                for(i=1;i<=m_MusicListListInfo.ListContent.Artist[0];i++){
                    usUniString[i] = m_MusicListListInfo.ListContent.Artist[i];
                }
            }
            break;

        case MMPS_AUDIO_GENRE:
            if(m_MusicListListInfo.ListContent.Genre[0]==0){
                usUniString[0] = m_UnknownUniStr[0];
                for(i=1;i<=m_UnknownUniStr[0];i++){
                    usUniString[i] = m_UnknownUniStr[i];
                }
            }else{
                usUniString[0] = m_MusicListListInfo.ListContent.Genre[0];
                for(i=1;i<=m_MusicListListInfo.ListContent.Genre[0];i++){
                    usUniString[i] = m_MusicListListInfo.ListContent.Genre[i];
                }
            }
            break;
    }


    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_OpenEnumPlayList
//------------------------------------------------------------------------------
/**
    @brief  Open Enum Play List
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_OpenEnumPlayList(void)
{
    m_MusicListListInfo.EnumPlayListInfo.CurrentIndex = 0;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnumPlayList
//------------------------------------------------------------------------------
/**
    @brief  Enum Play List
    @param[out] *usUniString : play list string
    @param[out] *usId: play list id
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_END_OF_FILE
*/
MMP_ERR  MMPS_AUDIO_EnumPlayList(MMP_USHORT *usUniString,MMP_USHORT *usId)
{
    MMP_ULONG i;

    for(i=m_MusicListListInfo.EnumPlayListInfo.CurrentIndex;i<m_MusicListListInfo.ObjCnt;i++){

        if((m_MusicListListInfo.FileFmt[i]==MMPS_AUDIO_FORMAT_Abstract_Audio_Video_Playlist)&&(m_MusicListListInfo.Flag[i]==0)){
            break;
        }
        m_MusicListListInfo.EnumPlayListInfo.CurrentIndex++;
    }

    if(i==m_MusicListListInfo.ObjCnt){
        return MMP_AUDIO_ERR_END_OF_FILE;
    }

    MMPS_AUDIO_ReadMusicListContent(m_MusicListListInfo.EnumPlayListInfo.CurrentIndex);

    *usId = m_MusicListListInfo.EnumPlayListInfo.CurrentIndex;

    MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);

    m_MusicListListInfo.EnumPlayListInfo.CurrentIndex++;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_OpenEnumObjByPlayList
//------------------------------------------------------------------------------
/**
    @brief  Open Enum Object Name By Play List
    @param[out] usId: play list id
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_OpenEnumObjByPlayList(MMP_USHORT usId)
{
    m_MusicListListInfo.EnumObjInfo.CurrentIndex = 0;
    m_MusicListListInfo.EnumObjInfo.PropertyId = usId;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnumObjByPlayList
//------------------------------------------------------------------------------
/**
    @brief  Enum Object Name By Play List
    @param[out] *usUniString : Object name string
    @param[out] *usId: object id
    @return MMP_ERR_NONE,MMP_AUDIO_ERR_END_OF_FILE
*/
MMP_ERR  MMPS_AUDIO_EnumObjByPlayList(MMP_USHORT *usUniString,MMP_USHORT *usId)
{

    MMPS_AUDIO_ReadMusicListContent(m_MusicListListInfo.EnumObjInfo.PropertyId);

    if(m_MusicListListInfo.EnumObjInfo.CurrentIndex==m_MusicListListInfo.ListContent.ObjReference[0]){
        return MMP_AUDIO_ERR_END_OF_FILE;
    }

    *usId = m_MusicListListInfo.ListContent.ObjReference[m_MusicListListInfo.EnumObjInfo.CurrentIndex+1]-1;

    MMPS_AUDIO_ReadMusicListContent(*usId);

    MMPS_AUDIO_GetObjNameFromFullPath(m_MusicListListInfo.ListContent.FileName,usUniString);

    m_MusicListListInfo.EnumObjInfo.CurrentIndex++;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_UpdateObjUseCnt
//------------------------------------------------------------------------------
/**
    @brief  Increase Object Use Count
    @param[in] usId: object id
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_UpdateObjUseCnt(MMP_USHORT usId)
{

    MMPS_AUDIO_ReadMusicListContent(usId);

    m_MusicListListInfo.ListContent.UseCount++;
    m_MusicListListInfo.ListContent.RoundTrip =1;

    MMPS_AUDIO_WriteMusicListContent(usId);

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetObjRating
//------------------------------------------------------------------------------
/**
    @brief  Get Object Rating
    @param[in] usId: object id
    @param[out] *usRating: rating
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_GetObjRating(MMP_USHORT usId,MMP_USHORT *usRating)
{

    MMPS_AUDIO_ReadMusicListContent(usId);

    *usRating = m_MusicListListInfo.ListContent.Rating;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetObjRating
//------------------------------------------------------------------------------
/**
    @brief  Set Object Raing
    @param[in] usId: object id
    @param[in] usRating: rating
    @return MMP_ERR_NONE
*/
MMP_ERR  MMPS_AUDIO_SetObjRating(MMP_USHORT usId,MMP_USHORT usRating)
{

    MMPS_AUDIO_ReadMusicListContent(usId);

    m_MusicListListInfo.ListContent.Rating = usRating;
    m_MusicListListInfo.ListContent.RoundTrip =1;

    MMPS_AUDIO_WriteMusicListContent(usId);

    return MMP_ERR_NONE;
}

#endif

MMP_ERR MMPS_AUDIO_GetCurCodec(MMP_UBYTE* ubcurCodec)
{
	if ((m_audioInPath & MMPS_AUDIO_IN_I2S_MASK) ||
        (m_audioOutPath & MMPS_AUDIO_OUT_I2S_MASK))
		*ubcurCodec = MMPS_AUDIO_EXTERNAL_CODEC;
	else 
	    *ubcurCodec = MMPS_AUDIO_INTERNAL_CODEC;
	
	return MMP_ERR_NONE;
}

#if (AUDIO_PREVIEW_SUPPORT == 1)
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartPreview
//------------------------------------------------------------------------------
/**
    @brief  Start Audio Preview
    @param[in] ulStartTime : start time to preview (ms)
    @param[in] ulDuration : preview duration (ms)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_StartPreview(MMP_ULONG ulStartTime, MMP_ULONG ulDuration)
{
    return MMPD_AUDIO_StartPreview(ulStartTime, ulDuration);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetPreviewStatus
//------------------------------------------------------------------------------
/**
    @brief  Get Audio Preview Data Status
    @param[out] *bDataReady : Preview data is ready or not
    @param[out] **usDataBuf : Preview data buffer address
    @param[out] *ulSampleNum : Number of samples in buffer
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_GetPreviewStatus(MMP_BOOL *bDataReady, MMP_SHORT **usDataBuf, MMP_ULONG *ulSampleNum)
{
    return MMPD_AUDIO_GetPreviewStatus(bDataReady, usDataBuf, ulSampleNum);
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetWriteCardStatus
//------------------------------------------------------------------------------
/** 
    @brief  Get Audio Write Card Status
    @param[out] usStatus : 0 : write card normal. 1: write card fail.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetWriteCardStatus(MMP_USHORT *usStatus)
{
	return MMPD_AUDIO_GetWriteCardStatus(usStatus);
}

#if 0
void __AUDIO_RECORD_OP__(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitRecord
//------------------------------------------------------------------------------
/**
    @brief  Init audio record
    
    @param[in] MediaPath    card mode or mem mode
    @param[in] fileinfo     audio file information
    @param[in] fmt          audio encode format
    @param[in] mode         audio encode mode (bitrate and sample rate)
    @param[in] ulMaxSize    max audio encode size
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitRecord(  MMPS_AUDIO_MEDIA_PATH MediaPath, 
                                MMPS_AUDIO_FILEINFO *fileinfo, 
                                MMP_AUDIO_ENCODE_FMT fmt, 
                                MMP_ULONG mode, 
                                MMP_ULONG ulMaxSize)
{
    MMP_ERR                 error = MMP_ERR_NONE;
    
    switch (fmt) {
		case MMP_AUDIO_AMR_ENCODE:
		    if ( MMPS_AUDIO_MEDIA_PATH_CARD == MediaPath ) {
			    error = MMPS_AUDIO_InitAMRRecordToCard(fileinfo, mode, ulMaxSize);
			}
			else {
			    error = MMPS_AUDIO_InitAMRRecordToMem(mode, ulMaxSize);
			}
		    break;
		case MMP_AUDIO_AAC_ENCODE:
		    if ( MMPS_AUDIO_MEDIA_PATH_CARD == MediaPath ) {
			    error = MMPS_AUDIO_InitAACRecordToCard(fileinfo, mode, ulMaxSize);
			}
			else {
			    error = MMPS_AUDIO_InitAACRecordToMem(mode, ulMaxSize);
			}
		    break;
		case MMP_AUDIO_MP3_ENCODE:
		    if ( MMPS_AUDIO_MEDIA_PATH_CARD == MediaPath ) {
			    error = MMPS_AUDIO_InitMP3RecordToCard(fileinfo, mode, ulMaxSize);
			}
			else {
			    error = MMPS_AUDIO_InitMP3RecordToMem(mode, ulMaxSize);
			}
		    break;
		case MMP_AUDIO_WAV_ENCODE:
		    if ( MMPS_AUDIO_MEDIA_PATH_CARD == MediaPath ) {
			    error = MMPS_AUDIO_InitWAVRecord(fileinfo, mode, ulMaxSize);
			}
			else {
			    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
			}
		    break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
            break;
    }
    
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_InitLiveRecord
//------------------------------------------------------------------------------
/**
    @brief  Init live audio record

    @param[in] fmt           live audio encode format
    @param[in] ulAdcSampleRate  The actuall ADC sample rate, usually it should
                                set as the sample rate of audio recording.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_InitLiveRecord(  MMP_AUDIO_ENCODE_FMT    fmt,
                                    MMP_USHORT              mode,
                                    MMP_ULONG               ulAdcSampleRate,
                                    MMP_LivePCMCB           LivePCMCB)
{
    MMP_ERR    error = MMP_ERR_NONE;
    MMP_USHORT  usStatus;

    MMPD_AUDIO_GetRecordStatus(&usStatus);
    if (usStatus == ENCODE_OP_STOP) {
        if (!(MMPS_AUDIO_GetInPath() & MMPS_AUDIO_IN_I2S_MASK)) {
            MMPD_AUDIO_SetPLL(ulAdcSampleRate);
        }
    }
    MMPD_AUDIO_SetInPath(MMPS_AUDIO_GetInPath());
    switch (fmt) {
    case MMP_AUDIO_G711_ENCODE:
        MMPD_AUDIO_SetLiveEncodeFormat(fmt,	ulAdcSampleRate, 8000, 2, 1);
        break;
    case MMP_AUDIO_PCM_ENCODE:
        MMPD_AUDIO_SetLiveEncodeFormat(fmt,	ulAdcSampleRate, ulAdcSampleRate, 2, 1);
        if (LivePCMCB != NULL)
            MMPD_AUDIO_SetLiveEncodeCB(LivePCMCB);
        break;
    case MMP_AUDIO_AAC_ENCODE:
        MMPD_AUDIO_SetLiveEncodeFormat(fmt,	ulAdcSampleRate, ulAdcSampleRate, 2, 2);
        MMPD_AUDIO_SetEncodePath(MMPD_AUDIO_RECORD_TO_MEM);
        MMPD_AUDIO_SetLiveEncodeMode((MMPS_AUDIO_AAC_ENCODEMODE)mode); 
        break;
    default:
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StartRecord
//------------------------------------------------------------------------------
/**
    @brief  Start audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_StartRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetEncodeFormat(&fmt);
    
    switch (fmt) {
		case MMP_AUDIO_AMR_ENCODE:
			error = MMPS_AUDIO_StartAMRRecord();
		break;
		case MMP_AUDIO_AAC_ENCODE:
			error = MMPS_AUDIO_StartAACRecord();
		break;
		case MMP_AUDIO_MP3_ENCODE:
			error = MMPS_AUDIO_StartMP3Record();
		break;
		case MMP_AUDIO_WAV_ENCODE:
			error = MMPS_AUDIO_StartWAVRecord();
		break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_LiveAudio_StartRecord
//------------------------------------------------------------------------------
/**
    @brief  Start live audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_LiveAudio_StartRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetLiveEncodeFormat(&fmt);

    switch (fmt) {
        case MMP_AUDIO_AAC_ENCODE:
        case MMP_AUDIO_G711_ENCODE:
        case MMP_AUDIO_PCM_ENCODE:
            error = MMPD_AUDIO_StartLiveAudioRecord();
        break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PauseRecord
//------------------------------------------------------------------------------
/**
    @brief  Pause audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_PauseRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetEncodeFormat(&fmt);
    
    switch (fmt) {
		case MMP_AUDIO_AMR_ENCODE:
			error = MMPS_AUDIO_PauseAMRRecord();
		break;
		case MMP_AUDIO_AAC_ENCODE:
			error = MMPS_AUDIO_PauseAACRecord();
		break;
		case MMP_AUDIO_MP3_ENCODE:
			error = MMPS_AUDIO_PauseMP3Record();
		break;
		case MMP_AUDIO_WAV_ENCODE:
			error = MMPS_AUDIO_PauseWAVRecord();
		break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_LiveAudio_PauseRecord
//------------------------------------------------------------------------------
/**
    @brief  Pause live audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_LiveAudio_PauseRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetLiveEncodeFormat(&fmt);
    
    switch (fmt) {
        case MMP_AUDIO_G711_ENCODE:
        case MMP_AUDIO_PCM_ENCODE:
        case MMP_AUDIO_AAC_ENCODE:
        case MMP_AUDIO_VAAC_ENCODE:
            error = MMPD_AUDIO_PauseLiveAudioRecord();
        break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_StopRecord
//------------------------------------------------------------------------------
/**
    @brief  Stop audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_StopRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetEncodeFormat(&fmt);
    
    switch (fmt) {
		case MMP_AUDIO_AMR_ENCODE:
			error = MMPS_AUDIO_StopAMRRecord();
		break;
		case MMP_AUDIO_AAC_ENCODE:
			error = MMPS_AUDIO_StopAACRecord();
		break;
		case MMP_AUDIO_MP3_ENCODE:
			error = MMPS_AUDIO_StopMP3Record();
		break;
		case MMP_AUDIO_WAV_ENCODE:
			error = MMPS_AUDIO_StopWAVRecord();
		break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_LiveAudio_StopRecord
//------------------------------------------------------------------------------
/**
    @brief  Stop live audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_LiveAudio_StopRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetLiveEncodeFormat(&fmt);
    
    switch (fmt) {
        case MMP_AUDIO_G711_ENCODE:
        case MMP_AUDIO_PCM_ENCODE:
        case MMP_AUDIO_AAC_ENCODE:
        case MMP_AUDIO_VAAC_ENCODE:
            error = MMPD_AUDIO_StopLiveAudioRecord();
        break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    MMPD_AUDIO_SetLiveEncodeCB(NULL);
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ResumeRecord
//------------------------------------------------------------------------------
/**
    @brief  Resume audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_ResumeRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetEncodeFormat(&fmt);
    
    switch (fmt) {
		case MMP_AUDIO_AMR_ENCODE:
			error = MMPS_AUDIO_ResumeAMRRecord();
		break;
		case MMP_AUDIO_AAC_ENCODE:
			error = MMPS_AUDIO_ResumeAACRecord();
		break;
		case MMP_AUDIO_MP3_ENCODE:
			error = MMPS_AUDIO_ResumeMP3Record();
		break;
		case MMP_AUDIO_WAV_ENCODE:
			error = MMPS_AUDIO_ResumeWAVRecord();
		break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_LiveAudio_ResumeRecord
//------------------------------------------------------------------------------
/**
    @brief  Resume live audio record
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_LiveAudio_ResumeRecord(void)
{
    MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetLiveEncodeFormat(&fmt);
    
    switch (fmt) {
        case MMP_AUDIO_G711_ENCODE:
        case MMP_AUDIO_PCM_ENCODE:
        case MMP_AUDIO_AAC_ENCODE:
        case MMP_AUDIO_VAAC_ENCODE:
            error = MMPD_AUDIO_ResumeLiveAudioRecord();
        break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_GetRecordTime
//------------------------------------------------------------------------------
/**
    @brief  Get current audio record time
    
    @param[out] recTime    recording time
    
    @return MMP_ERR_NONE
*/
MMP_ERR MMPS_AUDIO_GetRecordTime(MMP_ULONG *recTime)
{
	MMP_AUDIO_ENCODE_FMT    fmt;
    MMP_ERR                 error = MMP_ERR_NONE;
    
    MMPD_AUDIO_GetEncodeFormat(&fmt);
    
    switch (fmt) {
		case MMP_AUDIO_AMR_ENCODE:
			error = MMPS_AUDIO_GetAMRRecordTime(recTime);
		break;
		case MMP_AUDIO_AAC_ENCODE:
			error = MMPS_AUDIO_GetAACRecordTime(recTime);
		break;
		case MMP_AUDIO_MP3_ENCODE:
			error = MMPS_AUDIO_GetMP3RecordTime(recTime);
		break;
		case MMP_AUDIO_WAV_ENCODE:
			error = MMPS_AUDIO_GetWAVRecordTime(recTime);
		break;
        default:
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        break;
    }
    return error;
}

#if 0
void __AUDIO_PLAY_EFFECT__(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_PlayFadeOutEn
//------------------------------------------------------------------------------
/** 
    @brief  Enable/Disable AUI or NON_AUI player's audio fade out effect  
    @param[in]  channelID type MMP_UBYTE
                -    0:MMPF_NON_AUI_PLAYER
                -    1:MMPF_AUI_PLAYER
                bAFadeOutEn.
    @return MMP_ERR_NONE
*/
MMP_ERR	MMPS_AUDIO_PlayFadeOutEn(MMP_UBYTE channelID, MMP_BOOL bAFadeOutEn)
{
    return MMPD_AUDIO_PlayFadeOutEn(channelID, bAFadeOutEn);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetEQType
//------------------------------------------------------------------------------
/**
    @brief  Set Audio Play EQ Type
    @param[out] usType : eq type
        -   MMPS_AUDIO_PLAY_EQ_NONE
        -   MMPS_AUDIO_PLAY_EQ_CLASSIC
        -   MMPS_AUDIO_PLAY_EQ_JAZZ
        -   MMPS_AUDIO_PLAY_EQ_POP
        -   MMPS_AUDIO_PLAY_EQ_ROCK
        -   MMPS_AUDIO_PLAY_EQ_BASS3
        -   MMPS_AUDIO_PLAY_EQ_BASS9
        -   MMPS_AUDIO_PLAY_EQ_LOUDNESS
        -   MMPS_AUDIO_PLAY_EQ_SPK:     High pass filter
        -   MMPS_AUDIO_PLAY_HP_SURROUND
        -   MMPS_AUDIO_PLAYSPK_SURROUND
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
    @pre Change EQ type in playing, paused, stopped state, or before playing.
*/
MMP_ERR MMPS_AUDIO_SetEQType(MMPS_AUDIO_EQTYPE usType, void* argHandler)
{
    return MMPD_AUDIO_SetEQType(usType, argHandler);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetGraphicEQEnable
//------------------------------------------------------------------------------
/**
    @brief  Enable or Disable graphic EQ
    @param[in] ubEnable : enable or disable
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_SetGraphicEQEnable(MMP_BOOL ubEnable)
{
    return MMPD_AUDIO_SetGraphicEQEnable(ubEnable);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetGraphicEQBand
//------------------------------------------------------------------------------
/**
    @brief  Adjust one band parameter of EQ filter
    @param[in]  usFreq    : Center frequency
        - MMPS_AUDIO_BAND_60Hz
        - MMPS_AUDIO_BAND_170Hz
        - MMPS_AUDIO_BAND_310Hz
        - MMPS_AUDIO_BAND_600Hz
        - MMPS_AUDIO_BAND_1000Hz
        - MMPS_AUDIO_BAND_3000Hz
        - MMPS_AUDIO_BAND_6000Hz
        - MMPS_AUDIO_BAND_12000Hz
        - MMPS_ADUIO_BAND_14000Hz
        - MMPS_AUDIO_BAND_16000Hz
    @param[in]  usQrange  : Q range for the selected frequency band
        - MMPS_AUDIO_Q_115_4
        - MMPS_AUDIO_Q_57_7
        - MMPS_AUDIO_Q_28_8
        - MMPS_AUDIO_Q_14_4
        - MMPS_AUDIO_Q_7_20
        - MMPS_AUDIO_Q_4_80
        - MMPS_AUDIO_Q_3_59
        - MMPS_AUDIO_Q_2_87
        - MMPS_AUDIO_Q_2_38
        - MMPS_AUDIO_Q_2_04
        - MMPS_AUDIO_Q_1_78
        - MMPS_AUDIO_Q_1_57
        - MMPS_AUDIO_Q_1_41
        - MMPS_AUDIO_Q_0_66
        - MMPS_AUDIO_Q_0_004
        - MMPS_AUDIO_Q_0_003
    @param[in]  usGain    : Gain of selected frequency band (-20dB~20dB)
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_SetGraphicEQBand(MMPS_AUDIO_EQ_BAND usFreq, MMPS_AUDIO_EQ_QRANGE usQrange, MMP_USHORT usGain)
{
    if (usFreq >= MMPS_AUDIO_BAND_MAX || usQrange >= MMPS_AUDIO_Q_MAX) {
        return MMP_AUDIO_ERR_PARAMETER;
    }

    return MMPD_AUDIO_SetGraphicEQBand((MMP_USHORT)usFreq, (MMP_USHORT)usQrange, usGain);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetForeignEffectEnable
//------------------------------------------------------------------------------
/**
    @brief  Enable or Disable customer's privately sound effect system.
    @param[in] ubEnable : enable or disable foreign sound effect system
    
    @pre 1 : Sound effect type must be set by @ref MMPS_AUDIO_SetForeignEffectType
             before enable sound effect system.
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_SetForeignEffectEnable(MMP_BOOL ubEnable)
{
    return MMPD_AUDIO_SetForeignEffectEnable(ubEnable);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_SetForeignEffectType
//------------------------------------------------------------------------------
/**
    @brief  Adjust customer's privately sound effect type
    @param[in] ulParam1 : the first parameter for adjust effect type
    @param[in] ulParam2 : the second parameter for adjust effect type
    @param[in] ulParam3 : the third parameter for adjust effect type
    @return MMP_ERR_NONE, MMP_SYSTEM_ERR_CMDTIMEOUT
*/
MMP_ERR MMPS_AUDIO_SetForeignEffectType(MMP_ULONG ulParam1, MMP_ULONG ulParam2, MMP_ULONG ulParam3)
{
    return MMPD_AUDIO_SetForeignEffectType(ulParam1, ulParam2, ulParam3);
}

#if 0
void __AUDIO_RECORD_EFFECT__(){}
#endif

#if (WNR_EN)
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_ConfigWNR
//------------------------------------------------------------------------------
/**
    @brief  Configure wind noise reduction algorithm
    @param[in] cfg : configurations for wind noise reduction
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPS_AUDIO_ConfigWNR(MMP_AUDIO_WNR_CFG *cfg)
{
    return MMPD_AUDIO_ConfigWNR(cfg);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnableWNR
//------------------------------------------------------------------------------
/**
    @brief  Enable wind noise reduction operation
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPS_AUDIO_EnableWNR(void)
{
    return MMPD_AUDIO_SetWNREnable(MMP_TRUE);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_DisableWNR
//------------------------------------------------------------------------------
/**
    @brief  Disable wind noise reduction operation
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPS_AUDIO_DisableWNR(void)
{
    return MMPD_AUDIO_SetWNREnable(MMP_FALSE);
}
#endif

#if (AGC_SUPPORT)
//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_EnableAGC
//------------------------------------------------------------------------------
/**
    @brief  Enable auto gain control (AGC) operation
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPS_AUDIO_EnableAGC(void)
{
    return MMPD_AUDIO_SetAGCEnable(MMP_TRUE);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_AUDIO_DisableAGC
//------------------------------------------------------------------------------
/**
    @brief  Disable auto gain control (AGC) operation
    @return MMP_ERR_NONE for success, others for failure
*/
MMP_ERR MMPS_AUDIO_DisableAGC(void)
{
    return MMPD_AUDIO_SetAGCEnable(MMP_FALSE);
}
#endif

/// @}
