/**
 @file AHC_Audio.c
 @brief AHC audio control Function
 @author 
 @version 1.0
*/
/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_audio.h"
#include "ahc_uf.h"
#include "ahc_dcf.h"
#include "aihc_dcf.h"
#include "ahc_display.h"
#include "soundeffectname.h"
#include "ahc_utility.h"

#include "mmpf_audio_ctl.h"
#include "mmps_audio.h"
#include "mmps_aui.h"

/** @addtogroup AHC_AUDIO
@{
*/

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

static UINT8                        AudioCnxt[6] = "Audio";
static AHC_BOOL                     m_bAudioEof = MMP_FALSE;
static MMPS_AUDIO_I2S_CFG           m_AhcI2Scfg = {MMP_I2S_MASTER_MODE, MMP_I2S_256FS_MODE, MMP_I2S_OUT_16BIT, MMP_I2S_LRCK_L_LOW};
static UINT32                       m_ulI2S_SampleRate = 44100;
static UINT8                        m_uiRecAudioFmt = MMP_AUDIO_MP3_ENCODE;
UINT8                               m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_MP3;
MMP_AUDIO_MP3_INFO                  m_gsAHCMp3Info;
MMP_AUDIO_OGG_INFO                  m_gsAHCOggInfo;
MMP_AUDIO_WMA_INFO                  m_gsAHCWmaInfo;
MMP_AUDIO_WAV_INFO                  m_gsAHCWavInfo;
MMP_AUDIO_AAC_INFO                  m_gsAHCAacInfo;
AHC_BOOL                            m_bAHCAudioPlaying = AHC_FALSE;
static INT8                         m_bAudioEncodeFileName[MAX_FULL_FILENAME_SIZE];
static UINT16                       m_usAudioRecDirKey;
static UINT32                       m_ulAudioEncMode[MAX_AUDIO_ENC_FORMAT]    = {1,29,5};
static UINT32                       m_ulAudioEncChans[MAX_AUDIO_ENC_FORMAT]   = {   AHC_AUDIO_CHANNEL_MONO_R,
                                                                                    AHC_AUDIO_CHANNEL_MONO_R,
                                                                                    AHC_AUDIO_CHANNEL_MONO_R};
static AHC_BOOL                     m_bRecordDcfAudioFile = AHC_TRUE;

static const UINT32  m_uiAHCMp3EncParameter[8][2]={
                                            {32000,160000},{32000,128000},
                                            {32000,96000}, {32000,64000},
                                            {44100,160000},{44100,128000},
                                            {44100,96000}, {44100,64000}};

static const UINT32 m_uiAHCAACEncParameter[56][2] = {
                {16000, 16000}, {16000, 24000},  {16000, 32000},  {16000, 64000},
                {16000, 96000}, {16000, 128000}, {16000, 160000}, {16000, 192000},
                ///////////////////////////////////////////////////////////////////////
                {22050, 16000}, {22050, 24000},  {22050, 32000},  {22050, 64000},
                {22050, 96000}, {22050, 128000}, {22050, 160000}, {22050, 192000}, {22050, 256000},
                ///////////////////////////////////////////////////////////////////////
                {24000, 16000}, {24000, 24000},  {24000, 32000},  {24000, 64000},
                {24000, 96000}, {24000, 128000}, {24000, 160000}, {24000, 192000}, {24000, 256000},
                ///////////////////////////////////////////////////////////////////////
                {32000, 16000}, {32000, 24000},  {32000, 32000},  {32000, 64000},
                {32000, 96000}, {32000, 128000}, {32000, 160000}, {32000, 192000}, {32000, 256000}, {32000, 320000},
                ///////////////////////////////////////////////////////////////////////
                {44100, 16000}, {44100, 24000},  {44100, 32000},  {44100, 64000},
                {44100, 96000}, {44100, 128000}, {44100, 160000}, {44100, 192000}, {44100, 256000}, {44100, 320000},
                ///////////////////////////////////////////////////////////////////////
                {48000, 16000}, {48000, 24000},  {48000, 32000},  {48000, 64000},
                {48000, 96000}, {48000, 128000}, {48000, 160000}, {48000, 192000}, {48000, 256000}, {48000, 320000}
            };

static const UINT32 m_uiAHCWAVRecParameter[8] = {8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000};

static AHC_BOOL                     gSpeaker_en             = AHC_FALSE;
AHC_SOUND_FILE_ATTRIBUTE            SoundEffectFile[8];
static UINT8                        m_bSoundEffectExist     = AHC_FALSE;

#if 1
#if (PLAY_SOUND_SEQUENTIALLY)
AHC_SOUND_FILE_QUEUE    gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE] = {{AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #if (PLAY_SOUND_FILE_QUEUE_SIZE > 3)
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #endif
                                                                        #if (PLAY_SOUND_FILE_QUEUE_SIZE > 4)
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #endif
                                                                        #if (PLAY_SOUND_FILE_QUEUE_SIZE > 5)
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #endif
                                                                        #if (PLAY_SOUND_FILE_QUEUE_SIZE > 6)
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #endif
                                                                        #if (PLAY_SOUND_FILE_QUEUE_SIZE > 7)
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #endif
                                                                        #if (PLAY_SOUND_FILE_QUEUE_SIZE > 8)
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #endif
                                                                        #if (PLAY_SOUND_FILE_QUEUE_SIZE > 9)
                                                                        {AHC_SOUNDEFFECT_MAX_NUM, {0}},
                                                                        #endif
                                                                        };
UINT8                   gubAhcPlaySoundQue = 0;
UINT8                   gubAhcPlaySoundQueEventNum = 0;
#endif
#endif

/*===========================================================================
 * Extern function
 *===========================================================================*/ 
 
extern MMP_ERR MMPC_AudioExtCodec_SetPath(MMP_ULONG path);
extern MMP_ERR MMPC_AudioExtCodec_Init(MMPS_AUDIO_I2S_CFG *I2SConfig, MMP_ULONG samplerate, MMP_ULONG ulFixedMclkFreq);

/*===========================================================================
 * Main body
 *===========================================================================*/ 
 
#if 0
void __INTERNAL_API__(){}
#endif

/**
 @brief The callback function for audio stop 

 The callback function for audio stop 

 @param[in] Context  string
 @param[in] flag1    flag1
 @param[in] flag2    flag2
*/
static void AIHC_AudioStopCBTest(void *Context, UINT32 flag1, UINT32 flag2)
{
    DBG_S(0, "Audio is Stop!!!!!\r\n");
    DBG_S(0, (char *)Context);
    VAR_L(0, flag1);
    
    m_bAudioEof = MMP_TRUE;
}

/**
 @brief Config the external audio DAC for input patch

 This function  config the external audio DAC for input patch
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AIHC_InitAudioExtDACIn(void)
{
    #if (EXT_CODEC_SUPPORT == 1)
    UINT8                       I2Sch = MMP_I2S_CH0;
    MMPS_AUDIO_I2S_CFG          I2Scfg;

    if (MMPS_AUDIO_GetInPath() & MMPS_AUDIO_IN_I2S_MASK) {
        I2Scfg.workingMode      = m_AhcI2Scfg.workingMode;
        I2Scfg.mclkMode         = m_AhcI2Scfg.mclkMode;
        I2Scfg.outputBitSize    = m_AhcI2Scfg.outputBitSize;
        I2Scfg.lrckPolarity     = m_AhcI2Scfg.lrckPolarity;
        I2Scfg.outDataDelayMode = MMP_I2S_OUT_DELAY_STD;
        I2Scfg.bOutputBySDI     = MMP_FALSE;
        I2Scfg.bInputFromSDO    = MMP_FALSE;
        I2Scfg.ubInBitAlign     = 0;
        I2Scfg.ubOutBitAlign    = 0;
        #if (CHIP == VSN_V5)
        I2Sch = (MMPS_AUDIO_GetInPath() == MMPS_AUDIO_IN_I2S0) ?
                    MMP_I2S_CH0 : MMP_I2S_CH1;
        #endif
        MMPS_AUDIO_InitializeI2SConfig(I2Sch,&I2Scfg);
        MMPS_AUDIO_EnableI2SMclk(I2Sch,MMP_TRUE, m_ulI2S_SampleRate, 0);

        MMPC_AudioExtCodec_SetPath(AUDIO_EXT_MIC_IN);
        MMPC_AudioExtCodec_Init(&I2Scfg, m_ulI2S_SampleRate, 0);
    }
    #endif
    
    return AHC_TRUE;
}

/**
 @brief Config the external audio DAC for output patch

 This function  config the external audio DAC for output patch
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AIHC_InitAudioExtDACOut(void)
{
    #if (EXT_CODEC_SUPPORT == 1)
    UINT8                       I2Sch = MMP_I2S_CH0;
    MMPS_AUDIO_I2S_CFG           I2Scfg;

    if (MMPS_AUDIO_GetOutPath() & MMPS_AUDIO_OUT_I2S_MASK) {
        I2Scfg.workingMode      = m_AhcI2Scfg.workingMode;
        I2Scfg.mclkMode         = m_AhcI2Scfg.mclkMode;
        I2Scfg.outputBitSize    = m_AhcI2Scfg.outputBitSize;
        I2Scfg.lrckPolarity     = m_AhcI2Scfg.lrckPolarity;
        I2Scfg.outputBitSize    = MMP_I2S_OUT_16BIT;
        I2Scfg.outDataDelayMode = MMP_I2S_OUT_DELAY_STD;
        I2Scfg.bOutputBySDI     = MMP_FALSE;
        I2Scfg.bInputFromSDO    = MMP_FALSE;
        I2Scfg.ubInBitAlign     = 0;
        I2Scfg.ubOutBitAlign    = 16;
        #if (CHIP == VSN_V5)
        I2Sch = (MMPS_AUDIO_GetOutPath() == MMPS_AUDIO_OUT_I2S0) ?
                    MMP_I2S_CH0 : MMP_I2S_CH1;
        #endif
        MMPS_AUDIO_InitializeI2SConfig(I2Sch, &I2Scfg);
        MMPS_AUDIO_EnableI2SMclk(I2Sch, MMP_TRUE, m_ulI2S_SampleRate, 0);

        MMPC_AudioExtCodec_SetPath(AUDIO_EXT_HP_OUT);
        MMPC_AudioExtCodec_Init(&I2Scfg, m_ulI2S_SampleRate, 0);
    }
    #endif
    
    return AHC_TRUE;
}

#if 0
void __AHC_AUDIO_API__(){}
#endif

/**
 @brief Config audio

 This function controls the most important part of audio operation. It defines 
 the configuration of audio port and its capability.
 Parameters:
 @param[in] byPortCFG Configures the basic parts of audio port.
 @param[in] uwSampleRate Sample rate.
 @param[in] uwSDivider Audio bit clock division factor.
 @param[in] uwFDivider Audio frame clock division factor.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_ConfigAudioExtDevice(AHC_AUDIO_I2S_CFG* byPortCFG, UINT16 uwSampleRate)
{
    //MMPS_AUDIO_I2S_CFG I2Scfg;

    m_AhcI2Scfg.workingMode      = byPortCFG->workingMode;
    m_AhcI2Scfg.mclkMode         = byPortCFG->mclkMode;
    m_AhcI2Scfg.outputBitSize    = byPortCFG->outputBitSize;
    m_AhcI2Scfg.lrckPolarity     = byPortCFG->lrckPolarity;

    m_ulI2S_SampleRate           = uwSampleRate;

    return AHC_TRUE;
}

/**
 @brief Get audio file attribute

 This API gets the information of an audio file. The file must be selected as 
 current DCF object first.
 @param[out] *pAudioAttr Address for placing the audio attributes.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetAudioFileAttr(AUDIO_ATTR *pAudioAttr)
{
    UINT32              CurrentDcfIdx;
    MMP_ERR             err;
    MMPS_AUDIO_FILEINFO fileinfo;
    UINT8               FileType;
    
    if ( !pAudioAttr )
        return AHC_FALSE;
    
    MEMSET(pAudioAttr, 0, sizeof(AUDIO_ATTR) );
        
    if ( m_bAHCAudioPlaying ) {
        if ( AHC_AUDIO_PLAY_FMT_MP3 == m_uiPlayAudioFmt ) {
            pAudioAttr->sample_rate = m_gsAHCMp3Info.usSampleRate;
            pAudioAttr->channels    = m_gsAHCMp3Info.usChans;
            pAudioAttr->avg_bitrate = m_gsAHCMp3Info.ulBitRate;
            pAudioAttr->total_time  = m_gsAHCMp3Info.ulTotalTime;
        }
        else if ( AHC_AUDIO_PLAY_FMT_WAVE == m_uiPlayAudioFmt ) {
            pAudioAttr->sample_rate = m_gsAHCWavInfo.ulSampleRate;
            pAudioAttr->channels    = m_gsAHCWavInfo.usChans;
            pAudioAttr->avg_bitrate = m_gsAHCWavInfo.ulBitRate;
            pAudioAttr->total_time  = m_gsAHCWavInfo.ulTotalTime;
        }
        else if ( AHC_AUDIO_PLAY_FMT_OGG == m_uiPlayAudioFmt ) {
            pAudioAttr->sample_rate = m_gsAHCOggInfo.usSampleRate;
            pAudioAttr->channels    = m_gsAHCOggInfo.usChans;
            pAudioAttr->avg_bitrate = m_gsAHCOggInfo.ulBitRate;
            pAudioAttr->total_time  = m_gsAHCOggInfo.ulTotalTime;
        }
        else if ( AHC_AUDIO_PLAY_FMT_WMA == m_uiPlayAudioFmt ) {
            pAudioAttr->sample_rate = m_gsAHCWmaInfo.ulSampleRate;
            pAudioAttr->channels    = m_gsAHCWmaInfo.usChans;
            pAudioAttr->avg_bitrate = m_gsAHCWmaInfo.ulBitRate;
            pAudioAttr->total_time  = m_gsAHCWmaInfo.ulTotalTime;
        }
        else if ( AHC_AUDIO_PLAY_FMT_AAC == m_uiPlayAudioFmt ) {
            pAudioAttr->sample_rate = m_gsAHCAacInfo.usSampleRate;
            pAudioAttr->channels    = m_gsAHCAacInfo.usChans;
            pAudioAttr->avg_bitrate = m_gsAHCAacInfo.ulBitRate;
            pAudioAttr->total_time  = m_gsAHCAacInfo.ulTotalTime;
        }
    }
    else {        
        MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH_CARD);

        AHC_UF_GetCurrentIndex(&CurrentDcfIdx);
        AHC_UF_GetFilePathNamebyIndex(CurrentDcfIdx, fileinfo.bFileName);
        fileinfo.usFileNameLength = STRLEN((char*)fileinfo.bFileName);
        AHC_UF_GetFileTypebyIndex(CurrentDcfIdx, &FileType);

        if ( FileType == DCF_OBG_MP3 ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_MP3;
            err = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCMp3Info, MMPS_AUDIO_CODEC_MP3);
            
            if (err == MMP_ERR_NONE) {
                pAudioAttr->sample_rate = m_gsAHCMp3Info.usSampleRate;
                pAudioAttr->channels    = m_gsAHCMp3Info.usChans;
                pAudioAttr->avg_bitrate = m_gsAHCMp3Info.ulBitRate;
                pAudioAttr->total_time  = m_gsAHCMp3Info.ulTotalTime;
            
                MMPS_AUDIO_StopPlay();
            }
        }
        else if (FileType == DCF_OBG_WAV ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WAVE;
            err = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCWavInfo, MMPS_AUDIO_CODEC_WAV);
            
            if (err == MMP_ERR_NONE) {
                pAudioAttr->sample_rate = m_gsAHCWavInfo.ulSampleRate;
                pAudioAttr->channels    = m_gsAHCWavInfo.usChans;
                pAudioAttr->avg_bitrate = m_gsAHCWavInfo.ulBitRate;
                pAudioAttr->total_time  = m_gsAHCWavInfo.ulTotalTime;
                
                MMPS_AUDIO_StopPlay();
            }
        }
        else if ( FileType == DCF_OBG_OGG ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_OGG;
            err = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCOggInfo, MMPS_AUDIO_CODEC_OGG);
            
            if (err == MMP_ERR_NONE) {
                pAudioAttr->sample_rate = m_gsAHCOggInfo.usSampleRate;
                pAudioAttr->channels    = m_gsAHCOggInfo.usChans;
                pAudioAttr->avg_bitrate = m_gsAHCOggInfo.ulBitRate;
                pAudioAttr->total_time  = m_gsAHCOggInfo.ulTotalTime;
                
                MMPS_AUDIO_StopPlay();
            }
        }
        else if (FileType == DCF_OBG_WMA ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WMA;
            err = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCWmaInfo, MMPS_AUDIO_CODEC_WMA);
            
            if (err == MMP_ERR_NONE) {
                pAudioAttr->sample_rate = m_gsAHCWmaInfo.ulSampleRate;
                pAudioAttr->channels    = m_gsAHCWmaInfo.usChans;
                pAudioAttr->avg_bitrate = m_gsAHCWmaInfo.ulBitRate;
                pAudioAttr->total_time  = m_gsAHCWmaInfo.ulTotalTime;

                MMPS_AUDIO_StopPlay();
            }
        }
        else if (FileType == DCF_OBG_AAC ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_AAC;
            err = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCAacInfo, MMPS_AUDIO_CODEC_AAC);            
            if (err == MMP_ERR_NONE) {
                pAudioAttr->sample_rate = m_gsAHCAacInfo.usSampleRate;
                pAudioAttr->channels    = m_gsAHCAacInfo.usChans;
                pAudioAttr->avg_bitrate = m_gsAHCAacInfo.ulBitRate;
                pAudioAttr->total_time  = m_gsAHCAacInfo.ulTotalTime;

                MMPS_AUDIO_StopPlay();
            }
        }
    }  
    
    return AHC_TRUE;
}

/**
 @brief Capture audio message

 Captures a period of audio message in still image playback mode.
 This recorded audio will be treated as a audio memo for the playing 
 image/thumb file.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_CaptureAudioMessage(void)
{
    return AHC_TRUE;
}

/**
 @brief Stop audio message record

 Stops the audio capture process.
 Parameters:
 @param[out] *pulTime Returns the recorded audio time.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_StopRecording(UINT32 *pulTime)
{
    MMP_ERR retStatus;

    retStatus =  MMPS_AUDIO_StopRecord();
    
    if ( retStatus ) {
        return AHC_FALSE;
    }
    else {
        retStatus = MMPS_AUDIO_GetRecordTime((MMP_ULONG*)pulTime);
        
        if ( m_bRecordDcfAudioFile ) {
            AHC_UF_PreAddFile(m_usAudioRecDirKey,(INT8*)m_bAudioEncodeFileName);
            AHC_UF_PostAddFile(m_usAudioRecDirKey,(INT8*)m_bAudioEncodeFileName);
        }
    }
    
    if ( retStatus )
        return AHC_FALSE;

    return AHC_TRUE;   
}

/**
 @brief Play audio message

 Plays the corresponded audio message recorded by AHC_CaptrueAudioMessage() in 
 playback mode while the thumb or image is displayed.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PlayAudioMessage(void)
{
    return AHC_TRUE;
}
/**
 @brief config record audio format

 This API configures the pure audio recording format
 @param[in] 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_ConfigAudioRecFormat(UINT8 byAudioFormat, UINT32 uiAudioSampleRate, UINT8 bySelChannel , UINT32 uiBitRate)
{
    UINT16  i;
    UINT8   Idx;
    
    if ( bySelChannel >= AHC_AUDIO_CHANNEL_MAX )
        return AHC_FALSE;

    switch(byAudioFormat){

    case AHC_AUDIO_CODEC_MP3:
        m_ulAudioEncMode[0]    = 0xFFFF; //default value;

        for ( i = 0; i<(sizeof(m_uiAHCMp3EncParameter)>>2); i++) {
            if ((m_uiAHCMp3EncParameter[i][1] == uiBitRate) && (m_uiAHCMp3EncParameter[i][0] == uiAudioSampleRate)) {
                m_ulAudioEncMode[0] = i;
                break;
            }
        }

        Idx = 0;
        break;
    case AHC_AUDIO_CODEC_AAC:
        m_ulAudioEncMode[1]    = 0xFFFF; //default value;

        for ( i = 0; i<(sizeof(m_uiAHCAACEncParameter)>>2); i++) {
            if ((m_uiAHCAACEncParameter[i][1] == uiBitRate) && (m_uiAHCAACEncParameter[i][0] == uiAudioSampleRate)) {
                m_ulAudioEncMode[1] = i;
                break;
            }
        }

        Idx = 1;

        break;
    case AHC_AUDIO_CODEC_WAV:
        m_ulAudioEncMode[2]    = 0xFFFF; //default value;
        
        for ( i = 0; i<(sizeof(m_uiAHCWAVRecParameter)>>2); i++) {
            if (m_uiAHCWAVRecParameter[i] == uiAudioSampleRate) {
                m_ulAudioEncMode[2] = i;
                break;
            }
        }

        Idx = 2;

        break;
    default:
        return AHC_FALSE;
        break;
    }

    if (m_ulAudioEncMode[Idx] == 0xFFFF) {
        //unsupport mode;
        return AHC_FALSE;
    }

    m_ulAudioEncChans[Idx]   = bySelChannel;

    return AHC_TRUE;
}

/**
 @brief Record or play audio message

 This API controls the audio record/play operation.
 @param[in] byOpType Operation for audio playback and record.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_RecordAudioCmd(UINT8 byAudioFormat, UINT8 byOpType)
{
    MMP_ERR             err = MMP_ERR_NONE;
    MMPS_AUDIO_FILEINFO fileinfo;
    char                DirName[16];
    UINT8               RecFileName[16];
    INT8                RecExtension[4];
    UINT32              MaxRecordSize = 0xFFFFFFFF;
    UINT8               Idx;
    UINT8               bCreateNewDir;
    AHC_RTC_TIME        m_audioRecStartRtc;
    char                FilePath[MAX_FULL_FILENAME_SIZE];
    
    switch( byOpType ){
    
    case AHC_AUDIO_RECORD_START:        
        MEMSET(DirName                  , 0, sizeof(DirName));
        MEMSET(RecFileName              , 0, sizeof(RecFileName));
        MEMSET(RecExtension             , 0, sizeof(RecExtension));
        MEMSET(m_bAudioEncodeFileName   , 0, sizeof(m_bAudioEncodeFileName));
        #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
        if ( AHC_UF_GetName(&m_usAudioRecDirKey, (INT8*)DirName, (INT8*)RecFileName, &bCreateNewDir) == AHC_TRUE) {
            STRCPY(fileinfo.bFileName,(INT8*)AHC_UF_GetRootDirName());
            STRCAT(fileinfo.bFileName,"\\");
            STRCAT(fileinfo.bFileName,DirName);
            if ( bCreateNewDir ) {
                MMPS_FS_DirCreate((INT8*)fileinfo.bFileName, STRLEN(fileinfo.bFileName));
                AHC_UF_AddDir(DirName);
            }
            
            STRCAT(fileinfo.bFileName,"\\");
            STRCAT(fileinfo.bFileName,(INT8*)RecFileName);
            STRCAT(fileinfo.bFileName, EXT_DOT);
        }
        #elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
        STRCAT( FilePath, (INT8*)DirName);
        STRCAT(FilePath, (INT8*)RecFileName);
        MEMSET(FilePath   , 0, sizeof(FilePath));
        AHC_RTC_GetTime(&m_audioRecStartRtc);
        if ( AHC_UF_GetName2(&m_audioRecStartRtc, FilePath, (INT8*)RecFileName, &bCreateNewDir) == AHC_TRUE) {
            STRCPY(fileinfo.bFileName,(INT8*)FilePath);
            STRCAT(fileinfo.bFileName, EXT_DOT);
        #endif
        
            switch(byAudioFormat){
            case AHC_AUDIO_CODEC_MP3:
                STRCPY(RecExtension,(MMP_BYTE*)"MP3");
                
                Idx             = 0;                
                m_uiRecAudioFmt = MMP_AUDIO_MP3_ENCODE;
                
                break;
            case AHC_AUDIO_CODEC_AAC:
                STRCPY(RecExtension,(MMP_BYTE*)"AAC");
                
                Idx             = 1;                
                m_uiRecAudioFmt = MMP_AUDIO_AAC_ENCODE;
                
                break;
            case AHC_AUDIO_CODEC_WAV:
                STRCPY(RecExtension,(MMP_BYTE*)"WAV");

                Idx             = 2;                
                m_uiRecAudioFmt = MMP_AUDIO_WAV_ENCODE;

                break;
            default:
                return AHC_FALSE;
                break;
            }

            if (0xFFFF == m_ulAudioEncMode[Idx])
                return AHC_FALSE;
        
            AIHC_InitAudioExtDACIn();
    
            err = MMPS_AUDIO_SetLineInChannel(m_ulAudioEncChans[Idx]);

            if (MMP_ERR_NONE != err)
                return AHC_FALSE;
            
            STRCAT(fileinfo.bFileName,(MMP_BYTE*)RecExtension);
            fileinfo.usFileNameLength = STRLEN(fileinfo.bFileName);

            STRCPY(m_bAudioEncodeFileName,(INT8 *)RecFileName);
            STRCAT(m_bAudioEncodeFileName, EXT_DOT);
            STRCAT(m_bAudioEncodeFileName,(INT8 *)RecExtension);
            
            MMPS_AUDIO_InitRecord(MMPS_AUDIO_MEDIA_PATH_CARD, &fileinfo, m_uiRecAudioFmt, m_ulAudioEncMode[Idx], MaxRecordSize);
            if (MMP_ERR_NONE != err)
                return AHC_FALSE;
        }
        else {
            return AHC_FALSE;

        }

        err = MMPS_AUDIO_StartRecord();
        
        m_bRecordDcfAudioFile = AHC_TRUE;
        break;
    case AHC_AUDIO_RECORD_PAUSE:
        err = MMPS_AUDIO_PauseRecord();
        break;
    case AHC_AUDIO_RECORD_RESUME:
        err = MMPS_AUDIO_ResumeRecord();
        break;
    case AHC_AUDIO_RECORD_STOP:
        err = MMPS_AUDIO_StopRecord();

        printc("MMPS_AUDIO_StopRecord %s\r\n",err);
   
        if (MMP_ERR_NONE == err) {
            if ( m_bRecordDcfAudioFile ) {
                AHC_UF_PreAddFile(m_usAudioRecDirKey,(INT8*)m_bAudioEncodeFileName);
                AHC_UF_PostAddFile(m_usAudioRecDirKey,(INT8*)m_bAudioEncodeFileName);
            }
        }
        
        break;
    }
    
    return AHC_TRUE;
}

/**
 @brief record audio clip by name

 Record a audio clip by the specific name.
 @param[in] byOpType Operation for audio record.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_RecordAudioByName(UINT8* pFileName) 
{
    MMP_ERR             err = MMP_ERR_NONE;
    MMPS_AUDIO_FILEINFO fileinfo;
    char                subName;
    UINT32              Idx;
    UINT32              MaxRecordSize = 0xFFFFFFFF;

    STRCPY(fileinfo.bFileName, (char*)(pFileName));
    fileinfo.usFileNameLength = STRLEN((char*)(pFileName));

    subName = fileinfo.bFileName[fileinfo.usFileNameLength-1]; //get last char;
    fileinfo.mediaPath = MMPS_AUDIO_MEDIA_PATH_CARD;

    switch (subName){
        case '3':
            Idx             = 0;
            m_uiRecAudioFmt = MMP_AUDIO_MP3_ENCODE;
            break;
        case 'c':
        case 'C':
            Idx             = 1;
            m_uiRecAudioFmt = MMP_AUDIO_AAC_ENCODE;
            break;
        case 'v':
        case 'V':
            Idx             = 2;
            m_uiRecAudioFmt = MMP_AUDIO_WAV_ENCODE;
            break;
        default:
            //unsupport format;
            return AHC_FALSE;
        break;
    }

    if ( 0xFFFF == m_ulAudioEncMode[Idx])
        return AHC_FALSE;

    AIHC_InitAudioExtDACIn();
            
    err = MMPS_AUDIO_SetLineInChannel(m_ulAudioEncChans[Idx]);
    if (MMP_ERR_NONE != err)
        return AHC_FALSE;

    MMPS_AUDIO_InitRecord(MMPS_AUDIO_MEDIA_PATH_CARD, &fileinfo, m_uiRecAudioFmt, m_ulAudioEncMode[Idx], MaxRecordSize);
    if (MMP_ERR_NONE != err)
        return AHC_FALSE;

    err = MMPS_AUDIO_StartRecord();
    if (MMP_ERR_NONE != err)
        return AHC_FALSE;
        
    m_bRecordDcfAudioFile = AHC_FALSE;

    return AHC_TRUE;
}

AHC_BOOL AHC_GetAudioCurRecTime(UINT32 *pulTime)
{
    MMP_ERR retStatus;

    retStatus = MMPS_AUDIO_GetRecordTime((MMP_ULONG*)pulTime);

    if (!retStatus)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PlayFadeOutEn
//------------------------------------------------------------------------------
/** 
    @brief  Enable/Disable AUI or NON_AUI player's audio fade out effect  
    @param[in]  channelID type UINT8
                -    0:MMPF_NON_AUI_PLAYER
                -    1:MMPF_AUI_PLAYER
                bAFadeOutEn.
    @return MMP_ERR_NONE
*/
AHC_BOOL AHC_PlayFadeOutEn(UINT8 channelID, AHC_BOOL bAFadeOutEn)
{
    MMPS_AUDIO_PlayFadeOutEn(channelID, bAFadeOutEn);    
    return AHC_TRUE;
}
/**
 @brief Audio playback cmd

 Audio playback cmd.
 
 @param[in] byOpType command
 @param[in] byParam  parameter
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PlayAudioCmd(UINT8 byOpType, UINT32 byParam)
{
    UINT32              CurrentDcfIdx;
    MMPS_AUDIO_FILEINFO fileinfo;
    UINT8               FileType;
    INT32               TargetTime;
    UINT16              TimeRatio;
    UINT32              PlayTime;
    MMP_ERR             retStatus;
    UINT32              Param;

    switch(byOpType) {
    
        case AHC_AUDIO_PLAY_START:
            AIHC_InitAudioExtDACOut();

            AHC_UF_GetCurrentIndex(&CurrentDcfIdx);
    
            AHC_UF_GetFilePathNamebyIndex(CurrentDcfIdx, fileinfo.bFileName);

            MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH_CARD);

            fileinfo.usFileNameLength = STRLEN((char*)fileinfo.bFileName);

            AHC_UF_GetFileTypebyIndex(CurrentDcfIdx, &FileType);
            if ( FileType == DCF_OBG_MP3 ) {
                m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_MP3;
                retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCMp3Info, MMPS_AUDIO_CODEC_MP3);
            }
            else if ( FileType == DCF_OBG_WAV ) {
                m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WAVE;
                retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCWavInfo, MMPS_AUDIO_CODEC_WAV);
            }
            else if ( FileType == DCF_OBG_OGG ) {
                m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_OGG;
                retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCOggInfo, MMPS_AUDIO_CODEC_OGG);
            }
            else if (FileType == DCF_OBG_WMA ) {
                m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WMA;
                retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCWmaInfo, MMPS_AUDIO_CODEC_WMA);
            }
            else if (FileType == DCF_OBG_AAC ) {
                m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_AAC;
                retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCAacInfo, MMPS_AUDIO_CODEC_AAC);
            }

            // set audio volume
            AHC_GetParam(PARAM_ID_AUDIO_VOLUME      ,&Param);
            
            #if (AUDIO_SET_DB == 0x01) 
            MMPS_AUDIO_SetPlayVolumeDb(Param);
            #else
            MMPS_AUDIO_SetPlayVolume(Param, MMP_FALSE);
            #endif

            if ( retStatus == MMP_ERR_NONE ) {
                retStatus = MMPS_AUDIO_StartPlay((void *)AIHC_AudioStopCBTest, (void *)AudioCnxt);
            }
            if ( retStatus != MMP_ERR_NONE )
                return AHC_FALSE;

            m_bAHCAudioPlaying = AHC_TRUE;

            break;
        case AHC_AUDIO_PLAY_PAUSE:
            MMPS_AUDIO_PausePlay();
            break;
        case AHC_AUDIO_PLAY_STOP:
            MMPS_AUDIO_StopPlay();
            m_bAHCAudioPlaying = AHC_FALSE;
            break;
        //TBD
        case AHC_AUDIO_PLAY_STOP_AUTO:
            MMPS_AUDIO_StopPlay();
            m_bAHCAudioPlaying = AHC_FALSE;
            break;
        case AHC_AUDIO_PLAY_RESUME:
            MMPS_AUDIO_ResumePlay();
            break;
        case AHC_AUDIO_PLAY_SEEK_BY_TIME:
           MMPS_AUDIO_SeekByTime(byParam);
            break;
        case AHC_AUDIO_PLAY_FAST_FORWARD:
            MMPS_AUDIO_GetPlayTime(&TimeRatio, &PlayTime);

            TargetTime = PlayTime + byParam;
            if (TargetTime < 0)
                TargetTime = 0;

            MMPS_AUDIO_SeekByTime(TargetTime);
            break;
        case AHC_AUDIO_PLAY_FAST_FORWARD_RATE:
            break;
        case AHC_AUDIO_PLAY_SET_VOLUME:
            #if (AUDIO_SET_DB == 0x01) 
            MMPS_AUDIO_SetPlayVolumeDb(byParam);
            #else
            MMPS_AUDIO_SetPlayVolume(byParam, MMP_FALSE);
            #endif
            break;
        case AHC_AUDIO_PLAY_2ND_START:
            //MMPS_AUI_StartPlay(&m_uiPlayAudioFmt);
            MMPS_AUI_StartPlay();
            m_bAHCAudioPlaying = AHC_TRUE;
            break;
        case AHC_AUDIO_PLAY_2ND_STOP_AUTO:
            //MMPS_AUI_StopPlay(&m_uiPlayAudioFmt);
            MMPS_AUI_StopPlay();
            m_bAHCAudioPlaying = AHC_FALSE;
            break;
        default:
            //unsupport command;
            return AHC_FALSE;
            break;
    }
    return AHC_TRUE;
}

/**
 @brief Play audio clip by name

 Play a audio clip by the specific name.
 @param[in] byOpType Operation for audio playback.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PlayAudioByName(UINT8 *pFileName, UINT8 byOpType)
{
    UINT32              Param;
    MMP_ERR             retStatus;
    MMPS_AUDIO_FILEINFO fileinfo;
    char                subName;

    switch(byOpType) {
    
        case AHC_AUDIO_PLAY_START:
            AIHC_InitAudioExtDACOut();

            MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH_CARD);

            #if (FS_INPUT_ENCODE == UCS2)
            uniStrcpy(fileinfo.bFileName, pFileName);
            fileinfo->usFileNameLength = uniStrlen((short *)fileinfo->bFileName);
            #elif (FS_INPUT_ENCODE == UTF8)
            STRCPY(fileinfo.bFileName, (char*)pFileName);
            fileinfo.usFileNameLength = STRLEN((char*)pFileName);
            #endif

            subName = fileinfo.bFileName[fileinfo.usFileNameLength-1]; //get last char;
            switch (subName){
                case 'a':
                case 'A':
                    m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WMA;
                    retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCWmaInfo, MMPS_AUDIO_CODEC_WMA);
                break;
                case '3':
                    m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_MP3;
                    retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCMp3Info, MMPS_AUDIO_CODEC_MP3);
                break;
                case 'v':
                case 'V':
                    m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WAVE;
                    retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCWavInfo, MMPS_AUDIO_CODEC_WAV);
                break;
                case 'C':
                case 'c':
                    m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_AAC;
                    retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCAacInfo, MMPS_AUDIO_CODEC_AAC);
                break;

                case 'g':
                case 'G':
                    m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_OGG;
                    retStatus = MMPS_AUDIO_OpenFile(fileinfo, &m_gsAHCOggInfo, MMPS_AUDIO_CODEC_OGG);
                break;
                default:
                    //unsupport format;
                    return AHC_FALSE;
                break;
            }

            // set audio volume
            AHC_GetParam(PARAM_ID_AUDIO_VOLUME      ,&Param);
            
            #if (AUDIO_SET_DB == 0x01) 
            MMPS_AUDIO_SetPlayVolumeDb(Param);
            #else
            MMPS_AUDIO_SetPlayVolume(Param, MMP_FALSE);
            #endif

            if ( retStatus == MMP_ERR_NONE ) {
                retStatus = MMPS_AUDIO_StartPlay((void *)AIHC_AudioStopCBTest, (void *)AudioCnxt);
            }
            if ( retStatus != MMP_ERR_NONE )
                return AHC_FALSE;
            break;
        default:
            //unsupport command;
            return AHC_FALSE;
        break;
    }
    return AHC_TRUE;
}

/**
 @brief Config audio annotation

 Configures the audio annotation feature and ON/OFF upon the value of bOn. A kind
  of memo for still captured image.
 @param[in] bValue Enable/disable this feature.
 @param[in] uwPre Number of seconds to pre-record before capture.
 @param[in] uwAfter Number of seconds to record after capture.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_ConfigAudioAnnotation(AHC_BOOL bValue, UINT16 uwPre, UINT16 uwAfter)
{
    return AHC_TRUE;
}

/**
 @brief Stop audio annotation

 Terminates the audio annotation recording.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_AudioAnnotationStop(void)
{
    return AHC_TRUE;
}

/**
 @brief Select audio unit

 Selects the HW audio unit for current operation.
 @param[in] eAudId The audio units..
 @retval AHC_TRUE Success.
*/

AHC_BOOL AHC_SelectAudioUnit(AHC_AUDIO_UINT_ID eAudId)
{ 
    MMP_ERR mmpstatus;

    switch(eAudId) {

        case AHC_AUDIO_EXTERNAL_CODEC:
            mmpstatus = MMPS_AUDIO_InitialInPath(MMPS_AUDIO_IN_I2S0);
            if (mmpstatus)
                return AHC_FALSE;
            mmpstatus =MMPS_AUDIO_InitialOutPath(MMPS_AUDIO_OUT_I2S0);
            if (mmpstatus)
                return AHC_FALSE;
        break;
        case AHC_AUDIO_INTERNAL_CODEC:
            MMPS_AUDIO_InitialInPath(MMPS_AUDIO_IN_AFE_SING);
            if (mmpstatus)
                return AHC_FALSE;
            MMPS_AUDIO_InitialOutPath(MMPS_AUDIO_OUT_AFE_LINE);
            if (mmpstatus)
                return AHC_FALSE;
        break;
        case AHC_AUDIO_HDMI:
        break;
        default:
            //unsupport unit
            return AHC_FALSE;
        break;
    }
    return AHC_TRUE;
}

/**
 @brief Get audio unit

 Get the ID of current operating audio codec.
 @param[out] *peAudId The audio units.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetCurrentAudioUnit(AHC_AUDIO_UINT_ID *peAudId)
{
    MMP_ERR  mmpstatus;
    UINT8    tmpCodec;

    mmpstatus = MMPS_AUDIO_GetCurCodec(&tmpCodec);
    
    if ( mmpstatus ) {
        return AHC_FALSE;
    }
    else {
        switch(tmpCodec){
            case 0:
                *peAudId = AHC_AUDIO_INTERNAL_CODEC;
            break;
            case 1:
                *peAudId = AHC_AUDIO_EXTERNAL_CODEC;
            break;
            case 2:
                *peAudId = AHC_AUDIO_HDMI;
            break;
            default:
                return AHC_FALSE;
            break;
        }
        return AHC_TRUE;
    }
    return AHC_TRUE;
}

/**
 @brief Get audio current time

 This API gets the current time of playing audio file.
 @param[in] *pulTime The current time of playing audio file.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetAudioCurrentTime(UINT32 *pulTime)
{
    MMP_ERR retStatus;
    UINT16  timeRatio;

    retStatus = MMPS_AUDIO_GetPlayTime(&timeRatio, (UINT32*)pulTime);

    if (!retStatus)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}


/**
 @brief Set the multiplier of audio recording

 This API set the multiplier of audio recording
 @param[in] fMultiplier, if set to 2.00, the audio value
 multiply to 2.
 @retval AHC_TRUE Success.
 @note   Now only work on adpcm format.
*/
AHC_BOOL AHC_AudioSetRecMultiplier(float fMultiplier )
{
    INT16 sMultiplier;

    if( fMultiplier < 0.0f || fMultiplier > 100.0f)
    {
        return AHC_FALSE;
    }

    fMultiplier *= 100;

    sMultiplier = (INT16)fMultiplier;

    //MMPF_Audio_SetSoftwareGain(sMultiplier); //Rogers:***

    return AHC_TRUE;
}

AHC_BOOL AHC_Audio_ParseOptions(MMPS_3GPRECD_AUDIO_OPTION option, MMPS_3GPRECD_AUDIO_FORMAT *format,
        UINT32 *samplingRate, UINT32 *bitRate)
{
    struct __packed MMPS_AUDIO_OPTIONS 
    {
    
        MMPS_3GPRECD_AUDIO_OPTION option;
        MMPS_3GPRECD_AUDIO_FORMAT format;
        UINT32 samplingRate;
        UINT32 bitRate;
    };
    static const struct MMPS_AUDIO_OPTIONS options[] = {
        {MMPS_3GPRECD_AUDIO_AAC_16K_32K,     MMPS_3GPRECD_AUDIO_FORMAT_AAC, 16000,  32000},
        {MMPS_3GPRECD_AUDIO_AAC_16K_64K,     MMPS_3GPRECD_AUDIO_FORMAT_AAC, 16000,  64000},
        {MMPS_3GPRECD_AUDIO_AAC_22d05K_64K,  MMPS_3GPRECD_AUDIO_FORMAT_AAC, 22050,  64000},
        {MMPS_3GPRECD_AUDIO_AAC_22d05K_128K, MMPS_3GPRECD_AUDIO_FORMAT_AAC, 22050, 128000},
        {MMPS_3GPRECD_AUDIO_AAC_32K_64K,     MMPS_3GPRECD_AUDIO_FORMAT_AAC, 32000,  64000},
        {MMPS_3GPRECD_AUDIO_AAC_32K_128K,    MMPS_3GPRECD_AUDIO_FORMAT_AAC, 32000, 128000},
        {MMPS_3GPRECD_AUDIO_AAC_48K_128K,    MMPS_3GPRECD_AUDIO_FORMAT_AAC, 48000, 128000},
        {MMPS_3GPRECD_AUDIO_AAC_44d1K_64K,   MMPS_3GPRECD_AUDIO_FORMAT_AAC, 44100,  64000},
        {MMPS_3GPRECD_AUDIO_AAC_44d1K_128K,  MMPS_3GPRECD_AUDIO_FORMAT_AAC, 44100, 128000},
        {MMPS_3GPRECD_AUDIO_AMR_4d75K,       MMPS_3GPRECD_AUDIO_FORMAT_AMR,  8000,   4750},
        {MMPS_3GPRECD_AUDIO_AMR_5d15K,       MMPS_3GPRECD_AUDIO_FORMAT_AMR,  8000,   5150},
        {MMPS_3GPRECD_AUDIO_AMR_12d2K,       MMPS_3GPRECD_AUDIO_FORMAT_AMR,  8000,  12200},
        //ADPCM section, need to sync with MMPF_SetADPCMEncMode
        {MMPS_3GPRECD_AUDIO_ADPCM_16K_22K,   MMPS_3GPRECD_AUDIO_FORMAT_ADPCM, 16000,  22000},
        {MMPS_3GPRECD_AUDIO_ADPCM_32K_22K,   MMPS_3GPRECD_AUDIO_FORMAT_ADPCM, 32000,  22000},
        {MMPS_3GPRECD_AUDIO_ADPCM_44d1K_22K, MMPS_3GPRECD_AUDIO_FORMAT_ADPCM, 44100,  22000},
        {MMPS_3GPRECD_AUDIO_MP3_32K_128K,    MMPS_3GPRECD_AUDIO_FORMAT_MP3,   32000, 128000},
        {MMPS_3GPRECD_AUDIO_MP3_44d1K_128K,  MMPS_3GPRECD_AUDIO_FORMAT_MP3,   44100, 128000},
    };
    int i;

    for (i = 0; i < sizeof(options) / sizeof(options[0]); ++i) {
        if (options[i].option == option) {
            *format = options[i].format;
            *samplingRate = options[i].samplingRate;
            *bitRate = options[i].bitRate;
            return AHC_TRUE;
        }
    }
    *format = *samplingRate = *bitRate = 0;
    return AHC_FALSE;
}

#if 1
#if 0
void ____SoundEffect_Function_____(){ruturn;} //dummy
#endif
AHC_BOOL AHC_IsSpeakerEnable(void)
{
    return gSpeaker_en;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SpeakerEnable
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SpeakerEnable(MMP_GPIO_PIN piopin, AHC_BOOL enable)
{
    //Enable GPIO mode for GPIO nNum
    DrvGPIOPadSet(89/*DRV_IO_SPI0_GPIO3*/,1);
    //Configure GPIO nNum as output PIN
    DrvGPIOOutputEnable(89/*DRV_IO_SPI0_GPIO3*/,1);
    //Set GPIO nNum to High
    DrvGPIOSetOutputData(89/*DRV_IO_SPI0_GPIO3*/,enable);

    gSpeaker_en = enable;
#if 0
#if SUPPORT_SPEAKER
    UINT32 ulNow;

    MMPF_OS_GetTime(&ulNow);

    #if (NEVER_TURN_OFF_SPEAKER == 1)
    enable = 1;
    #endif

    #ifdef CFG_CUS_CONTROL_SPEAKER
    enable = CFG_CUS_CONTROL_SPEAKER();
    #endif

    if (piopin != MMP_GPIO_MAX)
    {
        AHC_GPIO_ConfigPad(piopin, PAD_OUT_DRIVING(0)|PAD_PULL_UP);

        if(enable)
        {
            AHC_GPIO_SetOutputMode(piopin, AHC_TRUE);
            AHC_GPIO_SetData(piopin, SPEAKER_ENABLE_LEVEL);

            #if (NEVER_TURN_OFF_SPEAKER == 0)
            if(gSpeaker_en != AHC_TRUE)
                AHC_OS_SleepMs(70);
            #endif

            gSpeaker_en = AHC_TRUE;
        }
        else
        {
            #ifdef SPEAKER_ENABLE_GPIO_USING_INPUT_MODE
            AHC_GPIO_SetOutputMode(piopin, AHC_FALSE);
            #else
            AHC_GPIO_SetOutputMode(piopin, AHC_TRUE);
            AHC_GPIO_SetData(piopin, !SPEAKER_ENABLE_LEVEL);
            #endif
            gSpeaker_en = AHC_FALSE;
        }
    }
    else
    {
        gSpeaker_en = AHC_FALSE;
        return AHC_FALSE;
    }
#endif
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetSoundEffectStatus
//  Description :
//------------------------------------------------------------------------------
#define AIT_BOOT_HEADER_ADDR     0x106200
#define SOUNDFILE_DRAM_ADDR      AHC_SOUNDFILE_DRAM_ADDR

AHC_BOOL AHC_GetSoundEffectStatus(UINT8 *ubSoundEffectStatus)
{
    MMPS_AUDIO_PLAY_STATUS audio_status = 0;

    MMPS_AUI_GetPlayStatus(&audio_status);

    switch(audio_status)
    {
        case MMPS_AUDIO_PLAY_START:
            *ubSoundEffectStatus = AHC_SOUND_EFFECT_STATUS_START;
        break;
        case MMPS_AUDIO_PLAY_PAUSE:
            *ubSoundEffectStatus = AHC_SOUND_EFFECT_STATUS_PAUSE;
        break;
        case MMPS_AUDIO_PLAY_STOP:
            *ubSoundEffectStatus = AHC_SOUND_EFFECT_STATUS_STOP;
        break;
        case MMPS_AUDIO_PLAY_INVALID:
            *ubSoundEffectStatus = AHC_SOUND_EFFECT_STATUS_INVALID;
        break;
    }
    return AHC_TRUE;
}

#define USE_WAV_SOUND_EFFECT (0)
#define USE_MP3_SOUND_EFFECT (1)

char* GetAudioFileExtension(char* path, char *copystr)
{
    int i;
    int nLength = STRLEN(path);
    int nTmp    = nLength;
    int nExtSize = 0;
    char szAudioExt[6];

    while( nTmp && path[nTmp] != '.' )
    {
        nTmp--;
    }

    if(nTmp==0) return AHC_FALSE;

    nTmp++;

    nExtSize = nLength - nTmp;

    for( i=0; i< nExtSize; i++ )
    {
        copystr[i] = path[nTmp+i];
    }

    copystr[i] = '\0';
    return szAudioExt;
}

AHC_MSOUND_TYPE gbMSoundType;
UINT32 glMSoundSize;
UINT32 glMWavSize1;
UINT32 glMWavSize2;
UINT32 glOutputSampleCnt;

AHC_BOOL AHC_PlaySoundEffectEx(AHC_SOUNDEFFECT_TYPE soundtype,  AHC_MSOUND_TYPE  MSType,  AHC_SOUND_IMPORTANCE SImportance)
{
    static UINT8        ubFileType = USE_WAV_SOUND_EFFECT;
    #if (PLAY_SOUND_SEQUENTIALLY)
    UINT32 FILEID;
    UINT64 filesize;
    UINT32 rdcnt;
    #endif
    MMP_AUDIO_DECODE_FMT soundeffectFileFmt;

    MMPS_AUDIO_FILEINFO fileinfo;
    //MMP_AUDIO_MP3_INFO  mp3info;
    //MMP_AUDIO_WAV_INFO  wavinfo;
    MMP_ERR             mmps_status;
    UINT32              value;
    UINT8               ubSoundEffectStatus = 0;
    UINT32              ulDacStatus = 0;
    char                path[256];
    #if(PLAY_SOUND_SEQUENTIALLY)
    AHC_RTC_TIME        sCurTime;
    UINT8               ubCnt = 0;
    #endif
    INT32               iValue = 0;
    char                audioFileExt[20];
    printc("Ex soundtype : %d\r\n",soundtype);
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_PRERECORD_DAC, &ulDacStatus);
    if(soundtype < AHC_SOUNDEFFECT_SPCAM_START || soundtype > AHC_SOUNDEFFECT_SPCAM_END)
    {
        AHC_Menu_SettingGetCB(COMMON_KEY_BEEP, &iValue);
        if((iValue == BEEP_OFF)||(ulDacStatus == AHC_FALSE))
        {
            //printc("--I-- Beep is OFF or Volume is 0\r\n");
            return AHC_FALSE;
        }
    }
    #if 0
    else if(!AHC_GetSoundEffectExist())
    {
        return AHC_FALSE;
    }
    #endif

    #if(PLAY_SOUND_SEQUENTIALLY)
    if(soundtype == AHC_SOUNDEFFECT_PLAYSOUND_EVENT)
    {
        if(gubAhcPlaySoundQue == 1)
        {
            gubAhcPlaySoundQue = 0;
        }
        goto L_SOUNDPLAY;
    }

    AHC_RTC_GetTime(&sCurTime);

    for(ubCnt = 0; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE; ubCnt++)
    {
        #if (PLAY_SOUND_DELETE_SAME_AUDIO)
        if(gsAhcPlaySoundQue[ubCnt].soundtype == soundtype)
        {
            printc("same AUI type\r\n");
            break;
        }
        #endif

        if(gsAhcPlaySoundQue[ubCnt].soundtype == AHC_SOUNDEFFECT_MAX_NUM)
        {
            if(SImportance == AHC_SOUND_IMPORTANCE_MAYBELOST) {
                if(ubCnt > 0) {
                    printc("AHC_PlaySoundEffectEx: Sound lost!!!\r\n");
                    return AHC_FALSE;
                }
            }
            gsAhcPlaySoundQue[ubCnt].soundtype = soundtype;
            gsAhcPlaySoundQue[ubCnt].mstype = MSType;
            memcpy(&(gsAhcPlaySoundQue[ubCnt].soundInitTime), &sCurTime, sizeof(AHC_RTC_TIME));
            //printc("AUI Index=%d, Q.Yesr=%d, cur.Year=%d\r\n",ubCnt, gsAhcPlaySoundQue[ubCnt].soundInitTime.uwYear, sCurTime.uwYear);
            break;
        }
    }

    #if (PLAY_SOUND_TIMEOUT_TIME != 0)
    if(ubCnt == PLAY_SOUND_FILE_QUEUE_SIZE)
    {
        UINT32  uiCurTime = 0xFFFFFFFF;
        UINT32  uiOldestFileTime  = 0xFFFFFFFF;

        uiCurTime = sCurTime.uwYear - 2000;
        uiCurTime = uiCurTime << 26;
        uiCurTime = uiCurTime | sCurTime.uwMonth << 22  |\
                                        sCurTime.uwDay << 17    |\
                                        sCurTime.uwHour << 12   |\
                                        sCurTime.uwMinute << 6  |\
                                        sCurTime.uwSecond;

        uiOldestFileTime = gsAhcPlaySoundQue[0].soundInitTime.uwYear - 2000;
        uiOldestFileTime = uiOldestFileTime << 26;
        uiOldestFileTime = uiOldestFileTime |   gsAhcPlaySoundQue[0].soundInitTime.uwMonth << 22    |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwDay << 17  |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwHour << 12 |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwMinute << 6    |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwSecond + PLAY_SOUND_TIMEOUT_TIME;
        if(uiCurTime > uiOldestFileTime)
        {
            printc("Old Sound Timeout \r\n");
            for(ubCnt = 0 ; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE-1; ubCnt++)
            {
                memcpy(&(gsAhcPlaySoundQue[ubCnt]), &(gsAhcPlaySoundQue[ubCnt+1]), sizeof(AHC_SOUND_FILE_QUEUE));
            }

            gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundtype = soundtype;
            gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].mstype = MSType;
            memcpy(&(gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundInitTime), &sCurTime, sizeof(AHC_RTC_TIME));
        }
    }
    #endif

    for(ubCnt = 0 ; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE; ubCnt++)
    {
        //printc("1 Q[%d].sound=%d\r\n", ubCnt, gsAhcPlaySoundQue[ubCnt].soundtype);
    }
    #endif

    AHC_GetSoundEffectStatus(&ubSoundEffectStatus);

    #if(PLAY_SOUND_SEQUENTIALLY)
    if(ubSoundEffectStatus != AHC_SOUND_EFFECT_STATUS_STOP)
    {
        return AHC_TRUE;
    }
    #else
    if(ubSoundEffectStatus == AHC_SOUND_EFFECT_STATUS_START)

        #if 0
        mmps_status = MMPS_AUI_StopWAVPlay();
        #else
        mmps_status = MMPS_AUI_StopPlay();
        #endif
    #endif

#if (PLAY_SOUND_SEQUENTIALLY)
L_SOUNDPLAY:
#endif
    #if (PLAY_SOUND_SEQUENTIALLY)
    STRCPY(path, AHC_GetSoundEffectFileName(gsAhcPlaySoundQue[0].soundtype));
    #else
    STRCPY(path, AHC_GetSoundEffectFileName(soundtype));
    #endif
    
#if (PLAY_SOUND_SEQUENTIALLY)
    gbMSoundType = gsAhcPlaySoundQue[0].mstype;
    printc("gbMSoundNum=%d\r\n", gbMSoundType);
    if((gbMSoundType == AHC_MSOUND_START) || (gbMSoundType == AHC_MSOUND_NULL)) {
        glMSoundSize = 0;
        glMWavSize1 = 0;
        glMWavSize2 = 0;
    }

    for(ubCnt = 0 ; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE-1; ubCnt++)
    {
        memcpy(&(gsAhcPlaySoundQue[ubCnt]), &(gsAhcPlaySoundQue[ubCnt+1]), sizeof(AHC_SOUND_FILE_QUEUE));
    }

    gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundtype = AHC_SOUNDEFFECT_MAX_NUM;
    gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].mstype = AHC_MSOUND_END;
    memset(&(gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundInitTime), 0, sizeof(AHC_RTC_TIME));

    for(ubCnt = 0 ; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE; ubCnt++)
    {
        //printc("2 Q[%d].sound=%d\r\n", ubCnt, gsAhcPlaySoundQue[ubCnt].soundtype);
    }
    printc("file path: %s\r\n", path);
#endif

    if (NULL == path) {
        return AHC_FALSE;
    }

    #if (FS_INPUT_ENCODE == UCS2)
    uniStrcpy(fileinfo.bFileName, path);
    fileinfo.usFileNameLength = uniStrlen((short *)fileinfo.bFileName);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(fileinfo.bFileName, path);
    fileinfo.usFileNameLength = STRLEN(path);
    #endif
    GetAudioFileExtension(path, audioFileExt);
    soundeffectFileFmt = MMPS_AUI_GetPlayFormat(audioFileExt);

    #if 0
    if (STRCMP(audioFileExt, "mp3") == 0) {
        ubFileType = USE_MP3_SOUND_EFFECT;
    }
    else {
        ubFileType = USE_WAV_SOUND_EFFECT;
    }
    #endif
    

    {
#if !(PLAY_SOUND_SEQUENTIALLY)
    OS_CRITICAL_INIT(); 
    OS_ENTER_CRITICAL();

    MMPS_AUI_SetMediaPath(MMPS_AUI_MEDIA_PATH_CARD);

    MMPS_AUI_InitializePlay(&fileinfo, soundeffectFileFmt);

    AHC_GetParam(PARAM_ID_AUDIO_VOLUME_DB,&value);

    #if (AUDIO_SET_DB == 0x1)
    MMPS_AUDIO_SetPlayVolumeDb(value);
    #else
    MMPS_AUDIO_SetPlayVolume(value, AHC_FALSE);
    #endif

    mmps_status = MMPS_AUI_StartPlay();

    OS_EXIT_CRITICAL();
 #else
  {
       if (soundeffectFileFmt == MMP_AUDIO_MP3_PLAY) { //ubFileType = USE_MP3_SOUND_EFFECT: Unsupport Memory Mode  
            OS_CRITICAL_INIT();
            OS_ENTER_CRITICAL();
            MMPS_AUI_SetMediaPath(MMPS_AUI_MEDIA_PATH_CARD);
            MMPS_AUI_InitializePlay(&fileinfo, soundeffectFileFmt);

            AHC_GetParam(PARAM_ID_AUDIO_VOLUME_DB,&value);

            #if (AUDIO_SET_DB == 0x1)
            MMPS_AUDIO_SetPlayVolumeDb(value);
            #else
            MMPS_AUDIO_SetPlayVolume(value, AHC_FALSE);
            #endif

            mmps_status = MMPS_AUI_StartPlay();

            OS_EXIT_CRITICAL();
       }
    else if(soundeffectFileFmt == MMP_AUDIO_WAV_PLAY) { //ubFileType = USE_WAV_SOUND_EFFECT: Support Memory Mode
        MMP_ERR err;

        fileinfo.ubBuf = (MMP_UBYTE*)(AHC_MSOUND_BASE_ADDR);
        err = MMPS_FS_FileOpen(fileinfo.bFileName, fileinfo.usFileNameLength, "rb", sizeof("rb"), &FILEID);
        if (MMP_ERR_NONE != err)
        {
            printc(FG_RED(" MMPS_FS_FileWrite %d error")"\r\n", err);
        }

     MMPS_FS_FileGetSize(FILEID, &filesize);

     if((gbMSoundType == AHC_MSOUND_MIDDLE) || (gbMSoundType == AHC_MSOUND_END) ) {
        MMPS_FS_FileSeek(FILEID, 40, MMPS_FS_SEEK_SET);
        MMPS_FS_FileRead(FILEID, (MMP_UBYTE *)&glOutputSampleCnt, 4, &rdcnt);
        MMPS_FS_FileSeek(FILEID, 44, MMPS_FS_SEEK_SET);
            MMPS_FS_FileRead(FILEID, fileinfo.ubBuf+glMSoundSize, glOutputSampleCnt, &rdcnt);
        //filesize -= 44;
     }
     else {
        MMPS_FS_FileSeek(FILEID, 40, MMPS_FS_SEEK_SET);
        MMPS_FS_FileRead(FILEID, (MMP_UBYTE *)&glOutputSampleCnt, 4, &rdcnt);
        MMPS_FS_FileSeek(FILEID, 0, MMPS_FS_SEEK_SET);
        MMPS_FS_FileRead(FILEID,fileinfo.ubBuf, glOutputSampleCnt+44, &rdcnt);
        glMSoundSize = 44;
     }
    MMPS_FS_FileClose(FILEID);
    glMSoundSize += glOutputSampleCnt;

    if(glMSoundSize > AHC_MSOUND_MEMORY_SIZE) {
        printc(FG_RED("AHC_ERROR : AHC_MSOUND_MEMORY_SIZE(0x%X) is too small!!\r\n"), AHC_MSOUND_MEMORY_SIZE);
    }

       if((gbMSoundType == AHC_MSOUND_END) ||(gbMSoundType == AHC_MSOUND_NULL) ) {
         OS_CRITICAL_INIT();
            *(MMP_ULONG *)(fileinfo.ubBuf+0x28) = glMSoundSize -44;
        fileinfo.ulBufSize = glMSoundSize;

          OS_ENTER_CRITICAL();
        MMPS_AUI_SetMediaPath(MMPS_AUI_MEDIA_PATH_MMP_MEM);
        #if 1
        mmps_status =MMPS_AUI_InitializePlay(&fileinfo, soundeffectFileFmt);
        #else
          mmps_status = MMPS_AUI_InitializeWAVPlay(&fileinfo, &wavinfo);
        #endif
        AHC_GetParam(PARAM_ID_AUDIO_VOLUME_DB,&value);

        #if (AUDIO_SET_DB == 0x1)
        MMPS_AUDIO_SetPlayVolumeDb(value);
        #else
        MMPS_AUDIO_SetPlayVolume(value, AHC_FALSE);
        #endif
        #if 1
        mmps_status = MMPS_AUI_StartPlay();
        #else
        MMPS_AUI_StartWAVPlay();
        #endif
           OS_EXIT_CRITICAL();

        glMSoundSize = 0;
        }

       if(soundtype == AHC_SOUNDEFFECT_PLAYSOUND_EVENT) {
        if((gbMSoundType == AHC_MSOUND_START) ||(gbMSoundType == AHC_MSOUND_MIDDLE) ) {
            AHC_PlaySoundEffectEx(AHC_SOUNDEFFECT_PLAYSOUND_EVENT, AHC_MSOUND_NULL, AHC_SOUND_IMPORTANCE_NECESSARY);
            }
       }
    }
    }
 #endif
    }
    
    #if (SUPPORT_SPEAKER == 1)
    {
#if 1 //Andy Liu TBD. 
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);        
#else
    
        #ifdef TV_SPEAKER_OUT_EN

        #if (SUPPORT_HDMI)
        if(HDMIFunc_GetStatus() == AHC_HDMI_NONE_STATUS)
        #else
        if(1)
        #endif
        {
            AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
        }
        else {
            AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);
        }

        #else

        #if (SUPPORT_HDMI && SUPPORT_TV)
        if(HDMIFunc_GetStatus()==AHC_HDMI_NONE_STATUS && TVFunc_Status()==AHC_TV_NONE_STATUS)
        #elif ((!SUPPORT_HDMI) && SUPPORT_TV)
        if(TVFunc_Status()==AHC_TV_NONE_STATUS)
        #elif (SUPPORT_HDMI && (!SUPPORT_TV))
        if (TVFunc_Status()==AHC_TV_NONE_STATUS)
        #else
        if(1)
        #endif
        {
            AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
        }
        else {
            AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);
        }

        #endif
#endif
    }
    #endif

#if 1 //Andy Liu TBD. 
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);        
#else
    #if (SUPPORT_HDMI)
    if(HDMIFunc_GetStatus() != AHC_HDMI_NONE_STATUS) {
        AHC_OS_SleepMs(400); //Fix Issue: Audio I2S ISR doesn't disable Reg0x80008800=0x08
    }
    #endif
#endif

    #if ( (MENU_STYLE == 1) && (!STYLE001_SUPPORT_TOUCH_PANEL) )
     // Fix no Beep sound issue when UI leave Menu state to Video state in charging case.
    #if (ENABLE_CHARGER_IC && defined(Car_DV))
        if (!AHC_Charger_GetStatus())
    #endif
            AHC_OS_SleepMs(200);
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PlaySoundEffect
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_PlaySoundEffect(AHC_SOUNDEFFECT_TYPE soundtype)
{
    MMPS_AUDIO_FILEINFO fileinfo;
    //static UINT8        ubFileType = USE_WAV_SOUND_EFFECT;
    MMP_ERR             mmps_status;
    UINT32              value;
    UINT8               ubSoundEffectStatus = 0;
    UINT32              ulDacStatus = 0;
    char                path[256];
    #if(PLAY_SOUND_SEQUENTIALLY)
    AHC_RTC_TIME        sCurTime;
    UINT8               ubCnt = 0;
    #endif
    char                *pSoundEffectPath = NULL;
    INT32               iValue = 0;
    char                audioFileExt[20];
    MMP_AUDIO_DECODE_FMT soundeffecFileFmt;

    #ifdef SoundEffectBreakExcptionCase
    if (AHC_DetectSoundEffectBreak());
        return AHC_FALSE;
    #endif

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_PRERECORD_DAC, &ulDacStatus );

    if (soundtype < AHC_SOUNDEFFECT_SPCAM_START || soundtype > AHC_SOUNDEFFECT_SPCAM_END)
    {
        AHC_Menu_SettingGetCB(COMMON_KEY_BEEP, &iValue);
        if ((iValue == BEEP_OFF)||(ulDacStatus == AHC_FALSE))
        {
            //printc("--I-- Beep is OFF or Volume is 0\r\n");
            return AHC_FALSE;
        }
    }

    #if (PLAY_SOUND_SEQUENTIALLY)
    if(soundtype == AHC_SOUNDEFFECT_PLAYSOUND_EVENT)
    {
        if(gubAhcPlaySoundQue == 1)
        {
            gubAhcPlaySoundQue = 0;
        }
        goto L_SOUNDPLAY;
    }

    AHC_RTC_GetTime(&sCurTime);
    for(ubCnt = 0; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE; ubCnt++)
    {
        #if (PLAY_SOUND_DELETE_SAME_AUDIO)
        if(gsAhcPlaySoundQue[ubCnt].soundtype == soundtype)
        {
            printc("same AUI type\r\n");
            break;
        }
        #endif

        if(gsAhcPlaySoundQue[ubCnt].soundtype == AHC_SOUNDEFFECT_MAX_NUM)
        {
            gsAhcPlaySoundQue[ubCnt].soundtype = soundtype;
            memcpy(&(gsAhcPlaySoundQue[ubCnt].soundInitTime), &sCurTime, sizeof(AHC_RTC_TIME));
            gubAhcPlaySoundQueEventNum = ubCnt + 1;
            //printc("AUI Index=%d, Q.Yesr=%d, cur.Year=%d\r\n",ubCnt, gsAhcPlaySoundQue[ubCnt].soundInitTime.uwYear, sCurTime.uwYear);
            break;
        }
    }

    #if(PLAY_SOUND_TIMEOUT_TIME != 0)
    if(ubCnt == PLAY_SOUND_FILE_QUEUE_SIZE)
    {
        UINT32  uiCurTime = 0xFFFFFFFF;
        UINT32  uiOldestFileTime  = 0xFFFFFFFF;

        uiCurTime = sCurTime.uwYear - 2000;
        uiCurTime = uiCurTime << 26;
        uiCurTime = uiCurTime | sCurTime.uwMonth << 22  |\
                                        sCurTime.uwDay << 17    |\
                                        sCurTime.uwHour << 12   |\
                                        sCurTime.uwMinute << 6  |\
                                        sCurTime.uwSecond;

        uiOldestFileTime = gsAhcPlaySoundQue[0].soundInitTime.uwYear - 2000;
        uiOldestFileTime = uiOldestFileTime << 26;
        uiOldestFileTime = uiOldestFileTime |   gsAhcPlaySoundQue[0].soundInitTime.uwMonth << 22    |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwDay << 17  |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwHour << 12 |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwMinute << 6    |\
                                                gsAhcPlaySoundQue[0].soundInitTime.uwSecond + PLAY_SOUND_TIMEOUT_TIME;
        if(uiCurTime > uiOldestFileTime)
        {
            printc("Old Sound Timeout \r\n");
            for(ubCnt = 0 ; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE-1; ubCnt++)
            {
                memcpy(&(gsAhcPlaySoundQue[ubCnt]), &(gsAhcPlaySoundQue[ubCnt+1]), sizeof(AHC_SOUND_FILE_QUEUE));
            }
            gubAhcPlaySoundQueEventNum = gubAhcPlaySoundQueEventNum - 1;
            gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundtype = soundtype;
            memcpy(&(gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundInitTime), &sCurTime, sizeof(AHC_RTC_TIME));
        }
    }
    #endif

    for(ubCnt = 0 ; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE; ubCnt++)
    {
        //printc("1 Q[%d].sound=%d\r\n", ubCnt, gsAhcPlaySoundQue[ubCnt].soundtype);
    }
    #endif

    AHC_GetSoundEffectStatus(&ubSoundEffectStatus);

    #if(PLAY_SOUND_SEQUENTIALLY)
    if(ubSoundEffectStatus != AHC_SOUND_EFFECT_STATUS_STOP)
    {
        return AHC_TRUE;
    }
    #else
    if (ubSoundEffectStatus == AHC_SOUND_EFFECT_STATUS_START) {
        mmps_status =MMPS_AUI_StopPlay();
    }
    #endif

#if(PLAY_SOUND_SEQUENTIALLY)
L_SOUNDPLAY:
#endif

    #if(PLAY_SOUND_SEQUENTIALLY)
    pSoundEffectPath = AHC_GetSoundEffectFileName(gsAhcPlaySoundQue[0].soundtype);
    #else
    pSoundEffectPath = AHC_GetSoundEffectFileName(soundtype);
    #endif

    if (NULL == pSoundEffectPath) {
        return AHC_FALSE;
    }

    STRCPY(path, pSoundEffectPath);

    GetAudioFileExtension(path, audioFileExt);

    soundeffecFileFmt = MMPS_AUI_GetPlayFormat(audioFileExt);

    #if(PLAY_SOUND_SEQUENTIALLY)
    for (ubCnt = 0 ; ubCnt < PLAY_SOUND_FILE_QUEUE_SIZE-1; ubCnt++)
    {
        memcpy(&(gsAhcPlaySoundQue[ubCnt]), &(gsAhcPlaySoundQue[ubCnt+1]), sizeof(AHC_SOUND_FILE_QUEUE));
    }
    gubAhcPlaySoundQueEventNum = gubAhcPlaySoundQueEventNum - 1;
    gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundtype = AHC_SOUNDEFFECT_MAX_NUM;
    memset(&(gsAhcPlaySoundQue[PLAY_SOUND_FILE_QUEUE_SIZE-1].soundInitTime), 0, sizeof(AHC_RTC_TIME));
    #endif

    #if (FS_INPUT_ENCODE == UCS2)
    uniStrcpy(fileinfo.bFileName, path);
    fileinfo.usFileNameLength = uniStrlen((short *)fileinfo.bFileName);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(fileinfo.bFileName, path);
    fileinfo.usFileNameLength = STRLEN(path);
    #endif

    MMPS_AUI_SetMediaPath(MMPS_AUI_MEDIA_PATH_CARD);

    mmps_status =MMPS_AUI_InitializePlay(&fileinfo, soundeffecFileFmt);

    if (mmps_status != MMP_ERR_NONE) {
        printc(FG_RED("ERR:MMPS_AUI_Initialize %d Play %x\r\n"),soundeffecFileFmt,mmps_status);
        return AHC_FALSE;
    }
 
    AHC_GetParam(PARAM_ID_AUDIO_VOLUME_DB, &value);

    #if (AUDIO_SET_DB == 0x1)
    MMPS_AUDIO_SetPlayVolumeDb(value);
    #else
    MMPS_AUDIO_SetPlayVolume(value, AHC_FALSE);
    #endif

    #if (SUPPORT_SPEAKER == 1)
    AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
    #endif

    mmps_status = MMPS_AUI_StartPlay();

    if (mmps_status != MMP_ERR_NONE) {
        printc(FG_RED("ERR:MMPS_AUI_Start %d Play %X\r\n"), soundeffecFileFmt,mmps_status);
        return AHC_FALSE;
    }

    #if (SUPPORT_HDMI)
    if (AHC_IsHdmiConnect()) { // Dont consider the ui state since it should be desided by caller.
        AHC_OS_SleepMs(400); //Fix Issue: Audio I2S ISR doesn't disable Reg0x80008800=0x08
    }
    #endif

    #if ((MENU_STYLE == 1) && (!STYLE001_SUPPORT_TOUCH_PANEL))
     // Fix no Beep sound issue when UI leave Menu state to Video state in charging case.
        #if (ENABLE_CHARGER_IC && defined(Car_DV))
        if (!AHC_Charger_GetStatus())
        #endif
            AHC_OS_SleepMs(200);
    #endif

    return AHC_TRUE;
}

AHC_BOOL AHC_SetSoundEffectExist(AHC_BOOL bExist)
{
    m_bSoundEffectExist = bExist;
    return AHC_TRUE;
}

UINT8 AHC_GetSoundEffectExist(void)
{
    return m_bSoundEffectExist;
}

AHC_BOOL AHC_LoadSoundEffect(void)
{
    char *SoundEffectfile[256] = {"SM:1:\\Shutter.wav",
                                  "SM:1:\\start.wav",
                                  "SM:1:\\sound_operation.wav",
                                  "SM:1:\\Record_start.wav",
                                  "SM:1:\\Record_stop.wav",
                                  "SM:1:\\sound_focus.wav",
                                  "SM:1:\\sound_error.wav",
                                  "SM:1:\\Record_start.wav",
                                  "SM:1:\\SelfTimer.wav"};
    UINT8   i;
    UINT32  ulFileId,ulFileSize,ulFileLoad;
    UINT32  error = 0;

    if (SOUNDFILE_DRAM_ADDR == 0) {
        printc("AHC_LoadSoundEffect: SOUNDFILE_DRAM_ADDR=0\r\n");
        AHC_SetSoundEffectExist(AHC_FALSE);
        return AHC_FALSE;
    }

    for (i = 0; i < 9; i++)
    {
        STRCPY(SoundEffectFile[i].path,SoundEffectfile[i]);

        error |= AHC_FS_FileOpen(SoundEffectFile[i].path,AHC_StrLen(SoundEffectFile[i].path),"rb",AHC_StrLen("rb"),&ulFileId);
        error |= AHC_FS_FileGetSize(ulFileId,&ulFileSize);

        SoundEffectFile[i].ulSize = ulFileSize;

        if (i == 0)
            SoundEffectFile[i].ulStartAddress = SOUNDFILE_DRAM_ADDR;
        else
            SoundEffectFile[i].ulStartAddress = (SoundEffectFile[i-1].ulStartAddress + SoundEffectFile[i-1].ulSize);

        error |= AHC_FS_FileRead(ulFileId,(UINT8 *)SoundEffectFile[i].ulStartAddress,SoundEffectFile[i].ulSize,&ulFileLoad);
        error |= AHC_FS_FileClose(ulFileId);
    }

    if (error)
    {
        AHC_SetSoundEffectExist(AHC_FALSE);
        return AHC_FALSE;
    }
    else
    {
        AHC_SetSoundEffectExist(AHC_TRUE);
        return AHC_TRUE;
    }
}
#endif

/// @}
