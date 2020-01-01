//==============================================================================
//
//  File        : AHC_MediaPlayback.c
//  Description : AHC media playback function
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_mediaplayback.h"
#include "ahc_dcf.h"
#include "ahc_display.h"
#include "ahc_browser.h"
#include "mmps_audio.h"
#include "mmps_vidplay.h"
#include "mmps_dsc.h"
#include "snr_cfg.h"
#include "ahc_parameter.h"
#include "ahc_gui.h"
#include "ahc_audio.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

AHC_BOOL        m_ubPlaybackRearCam     = AHC_FALSE;
 
static UINT32   m_ulVideoPlayStopStatus = AHC_VIDEO_PLAY_EOF;
static UINT32   m_ulVideoPlayStartTime  = 0;
static UINT32   m_ulAudioPlayStopStatus = AHC_AUDIO_EVENT_EOF;
static UINT32   m_ulAudioPlayStartTime  = 0;

static UINT32   m_ulPlaybackFileType    = DCF_OBG_JPG;
static INT8     m_CurPlayFileName[MAX_FULL_FILENAME_SIZE];
static UINT32   m_ulCurrentPBFileType;
UINT16          m_ulCurrentPBWidth;
UINT16          m_ulCurrentPBHeight;

static UINT16   m_CurrentVolume;
static UINT32   m_ulMovPlayFFSpeed        = 5;
static UINT32   m_ulMovPlayRewSpeed       = 5;

/*===========================================================================
 * Extern function
 *===========================================================================*/ 

extern AHC_BOOL                     gbAhcDbgBrk;
extern UINT8                        m_uiPlayAudioFmt;
extern AHC_BOOL                     m_bAHCAudioPlaying;
extern MMP_AUDIO_MP3_INFO           m_gsAHCMp3Info;
extern MMP_AUDIO_OGG_INFO           m_gsAHCOggInfo;
extern MMP_AUDIO_WMA_INFO           m_gsAHCWmaInfo;
extern MMP_AUDIO_WAV_INFO           m_gsAHCWavInfo;

/*===========================================================================
 * Main body
 *===========================================================================*/ 
#if 0
void _____MediaPlayback_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_SetPlayBackRearCam
//  Description :
//------------------------------------------------------------------------------
void AHC_SetPlayBackRearCam(AHC_BOOL bIsRear)
{
    m_ubPlaybackRearCam = bIsRear;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetPlayBackRearCam
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetPlayBackRearCam(void)
{
    return m_ubPlaybackRearCam;
}

//------------------------------------------------------------------------------
//  Function    : VideoPlayStopCallback
//  Description :
//------------------------------------------------------------------------------
void VideoPlayStopCallback(void *Context, UINT32 flag1, UINT32 flag2)
{
    #if (DAC_NOT_OUTPUT_SPEAKER_HAS_NOISE)
    if (AHC_TRUE == AHC_IsSpeakerEnable())
    {
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);
    }
    #endif

    m_ulVideoPlayStopStatus = flag1;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetVideoPlayStartTime
//  Description :
//------------------------------------------------------------------------------
void AHC_SetVideoPlayStartTime(UINT32 ulStartTime)
{
    m_ulVideoPlayStartTime = ulStartTime;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetVideoPlayStopStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetVideoPlayStopStatus(UINT32 *pwValue)
{
    *pwValue = m_ulVideoPlayStopStatus;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetVideoPlayStopStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetVideoPlayStopStatus(UINT32 Value)
{
    m_ulVideoPlayStopStatus = Value;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AudioPlayStopCallback
//  Description :
//------------------------------------------------------------------------------
void AudioPlayStopCallback(void *Context, UINT32 flag1, UINT32 flag2)
{
    m_ulAudioPlayStopStatus = flag1;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetAudioPlayStopStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetAudioPlayStopStatus(UINT32 *pwValue)
{
    *pwValue = m_ulAudioPlayStopStatus;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAudioPlayStopStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetAudioPlayStopStatus(UINT32 Value)
{
    m_ulAudioPlayStopStatus = Value;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GetCurrentPBFileType
//  Description : Get current playback file type
//------------------------------------------------------------------------------
AHC_BOOL AIHC_GetCurrentPBFileType(UINT32 *pFileType)
{
    *pFileType = m_ulCurrentPBFileType;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GetCurrentPBHeight
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_GetCurrentPBHeight(UINT16 *pHeight)
{
    *pHeight = m_ulCurrentPBHeight;

    return AHC_TRUE;
}

#if (SUPPORT_ESD_RECOVER_MOVIEPB == 1)
void VideoMediaErrorPlayStopHandler(void)
{
    #if (SUPPORT_ESD_RECOVER_MOVIEPB == 1)
    UINT32 CurrentDcfIdx;
    INT8  chAllowedChar[MAX_ALLOWED_WORD_LENGTH];
    AHC_BOOL    err;

    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

    #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    if(AHC_IsSDInserted() && (m_ulVideoPlayStopStatus == AHC_VIDEO_PLAY_ERROR_STOP))
    #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    if( (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && (m_ulVideoPlayStopStatus == AHC_VIDEO_PLAY_ERROR_STOP) )
    #endif//TWOSD_WORK_MODEL

    #else//DEVICE_GPIO_2NDSD_PLUG

    if(AHC_IsSDInserted() && (m_ulVideoPlayStopStatus == AHC_VIDEO_PLAY_ERROR_STOP))

    #endif//DEVICE_GPIO_2NDSD_PLUG
    {
         UINT8 bValue = 0;

         MovPBFunc_StopTimer();
         AHC_UF_GetCurrentIndex(&CurrentDcfIdx);
         AHC_UF_GetAllowedChar(chAllowedChar, MAX_ALLOWED_WORD_LENGTH);

         AIHC_StopPlaybackMode();

         //AHC_GPIO_GetData(AHC_PIO_REG_LGPIO28,&bValue);
         //if(bValue != AHC_FALSE)
         AHC_FS_IOCtl(AHC_UF_GetRootName(), 4, AHC_FS_CMD_RESET_MEDIUM, NULL, NULL);

         err = AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);

         AHC_OS_Sleep(500);

         AHC_UF_SetFreeChar( 0,DCF_SET_FREECHAR,(UINT8*)chAllowedChar);
         AHC_UF_SetCurrentIndex(CurrentDcfIdx);
        // SetKeyPadEvent(VRCB_MEDIA_ERROR);

         MovPlaybackParamReset();
         MediaPlaybackConfig( 1 );
         MovPBFunc_StartTimer(300);
         //MovPlayback_Play();
         MovPlayback_Play_MediaError(m_CurPlayTime_MediaError);
    }
    #if 1

    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

    #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    else if( AHC_IsSDInserted() && (m_ulVideoPlayStopStatus == AHC_VIDEO_PLAY) )
    #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    else if( (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && (m_ulVideoPlayStopStatus == AHC_VIDEO_PLAY) )
    #endif

    #else//DEVICE_GPIO_2NDSD_PLUG

    else if (AHC_IsSDInserted() && (m_ulVideoPlayStopStatus == AHC_VIDEO_PLAY))

    #endif//DEVICE_GPIO_2NDSD_PLUG
    {
         UINT8 bValue = 0;
         
         AHC_UF_GetCurrentIndex(&CurrentDcfIdx);
         AHC_UF_GetAllowedChar(chAllowedChar, MAX_ALLOWED_WORD_LENGTH);

         AIHC_StopPlaybackMode();

         if(bValue != AHC_FALSE)
         AHC_FS_IOCtl(AHC_UF_GetRootName(), 4, AHC_FS_CMD_RESET_MEDIUM, NULL, NULL);

         AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);

         AHC_OS_Sleep(300);
         AHC_UF_SetFreeChar( 0,DCF_SET_FREECHAR,(UINT8*)chAllowedChar);
         AHC_UF_SetCurrentIndex(CurrentDcfIdx);
        AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, VRCB_MEDIA_ERROR, 0);
    }
    #endif
    
    #if 1
    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

    #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    else if( AHC_IsSDInserted() && (uiGetCurrentState() == UI_BROWSER_STATE) )
    #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    else if( (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && (uiGetCurrentState() == UI_BROWSER_STATE) )
    #endif

    #else//DEVICE_GPIO_2NDSD_PLUG

    else if(AHC_IsSDInserted() && (uiGetCurrentState() == UI_BROWSER_STATE))

    #endif//DEVICE_GPIO_2NDSD_PLUG
    {
         AHC_FS_IOCtl(AHC_UF_GetRootName(), 4, AHC_FS_CMD_RESET_MEDIUM, NULL, NULL);
         //AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
         //AHC_OS_Sleep(200);
    }
    #if 1

    #if(defined(DEVICE_GPIO_2NDSD_PLUG))
    #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    else if( AHC_IsSDInserted() && (uiGetCurrentState() == UI_PLAYBACK_STATE) )
    #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    else if( (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && (uiGetCurrentState() == UI_PLAYBACK_STATE) )
    #endif//TWOSD_WORK_MODEL

    #else//DEVICE_GPIO_2NDSD_PLUG

    else if(AHC_IsSDInserted() && (uiGetCurrentState() == UI_PLAYBACK_STATE))

    #endif//DEVICE_GPIO_2NDSD_PLUG
    {
         UINT8 bValue = 0;
         AHC_UF_GetCurrentIndex(&CurrentDcfIdx);
         AHC_UF_GetAllowedChar(chAllowedChar, MAX_ALLOWED_WORD_LENGTH);
         AHC_GPIO_GetData(AHC_PIO_REG_LGPIO28,&bValue);
         if(bValue != AHC_FALSE)
         AHC_FS_IOCtl(AHC_UF_GetRootName(), 4, AHC_FS_CMD_RESET_MEDIUM, NULL, NULL);

         AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
         AHC_OS_Sleep(300);
         AHC_UF_SetFreeChar( 0,DCF_SET_FREECHAR,(UINT8*)chAllowedChar);
         AHC_UF_SetCurrentIndex(CurrentDcfIdx);
         AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, VRCB_MEDIA_ERROR, 0);
    }
    #endif
    #if 1

    #if(defined(DEVICE_GPIO_2NDSD_PLUG))
    #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)

    else if( AHC_IsSDInserted() )
    #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    else if( AHC_IsSDInserted() || AHC_Is2ndSDInserted() )
    #endif//TWOSD_WORK_MODEL

    #else//DEVICE_GPIO_2NDSD_PLUG

    else if(AHC_IsSDInserted())

    #endif//DEVICE_GPIO_2NDSD_PLUG
    {
         UINT8 bValue = 0;

         //if(VideoFunc_GetRecordStatus() && MMPF_VIDENC_GetStatus()!= 0x01)
         if(VideoFunc_GetRecordStatus())
         {
            // AHC_SetMode(AHC_MODE_IDLE);
             AHC_GPIO_GetData(AHC_PIO_REG_LGPIO28,&bValue);
             if(bValue != AHC_FALSE)
             AHC_FS_IOCtl(AHC_UF_GetRootName(), 4, AHC_FS_CMD_RESET_MEDIUM, NULL, NULL);

             DrawVideo_UpdatebyEvent(EVENT_VIDEO_KEY_RECORD_STOP);
             //AHC_WMSG_Draw(AHC_TRUE, WMSG_FILE_ERROR, 1);
             #if (SUPPORT_ESD_RECOVER_VR)

             //AHC_FS_IOCtl("SD:\\", 4, AHC_FS_CMD_RESET_MEDIUM, NULL, NULL);
             VideoRecMode_RecordwithStatusChecking();
             #endif
         }
         else
         {
             AHC_GPIO_GetData(AHC_PIO_REG_LGPIO28,&bValue);
             if(bValue != AHC_FALSE)
             AHC_FS_IOCtl(AHC_UF_GetRootName(), 4, AHC_FS_CMD_RESET_MEDIUM, NULL, NULL);

             AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
             AHC_OS_Sleep(300);
             VideoRecMode_RecordwithStatusChecking();
         }
    }
    #endif
    #endif
    #endif
}

AHC_BOOL AIHC_SetPlaybackMediaErrorMode(void)
{
    UINT32                      CurrentDcfIdx;
    UINT8                       FileType;
    char                        FilePathName[MAX_FULL_FILENAME_SIZE];
    UINT32                      Param;
    MMP_DSC_JPEG_INFO           stJpegInfo;
    UINT16                      DispWidth,DispHeight;
    MMP_ERR                     sRet = MMP_ERR_NONE;
    MMP_ULONG                   ulFileNameLen;
    AHC_DISPLAY_OUTPUTPANEL     outputPanel;
    MMPS_AUDIO_FILEINFO         AudFileInfo;
    MMPS_VIDEO_CONTAINER_INFO   VideoFileInfo;
    MMPS_VIDPLAY_SCALERCONFIG   cfg;

    AHC_UF_GetCurrentIndex(&CurrentDcfIdx);

    MEMSET(FilePathName, 0, sizeof(FilePathName));
    AHC_UF_GetFilePathNamebyIndex(CurrentDcfIdx, FilePathName);
    AHC_UF_GetFileTypebyIndex(CurrentDcfIdx, &FileType);

    m_ulCurrentPBFileType = FileType;

    if (FileType == DCF_OBG_JPG)
    {
        STRCPY(stJpegInfo.bJpegFileName, FilePathName);

        stJpegInfo.usJpegFileNameLength   = STRLEN(FilePathName);
        stJpegInfo.ulJpegBufAddr          = 0;
        stJpegInfo.ulJpegBufSize          = 0;
        stJpegInfo.bDecodeThumbnail       = MMP_FALSE;
        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        stJpegInfo.bDecodeLargeThumb        = MMP_FALSE;
        #endif
        stJpegInfo.bValid                 = MMP_FALSE;
        stJpegInfo.bPowerOffLogo          = MMP_FALSE;

        AHC_GetDisplayOutputDev(&outputPanel);
        MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, outputPanel);

        sRet = MMPS_DSC_PlaybackJpeg(&stJpegInfo, 0, 0);
        if (sRet != MMP_ERR_NONE) {
            AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet);
            MMPS_DSC_ExitJpegPlayback();
            return AHC_FALSE;
        } 
        
        m_ulPlaybackFileType = FileType;
        return AHC_TRUE;
    }
    else if ((FileType == DCF_OBG_MOV) ||
             (FileType == DCF_OBG_MP4) ||
             (FileType == DCF_OBG_AVI) ||
             (FileType == DCF_OBG_3GP) ||
             (FileType == DCF_OBG_TS ) ||
             (FileType == DCF_OBG_WMV))
    {
        AIHC_InitAudioExtDACOut();

        MMPS_VIDPLAY_SetMemoryMode(MMP_FALSE);

        #if (SUPPORT_SPEAKER == 1)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
        #endif

        AHC_GetDisplayOutputDev( &outputPanel );

        MMPS_Display_SetOutputPanelMediaError(MMP_DISPLAY_PRM_CTL, outputPanel);

        STRCPY(m_CurPlayFileName, FilePathName);
        ulFileNameLen = STRLEN(FilePathName);

        MMPS_VIDPLAY_GetFileInfo(m_CurPlayFileName, ulFileNameLen, &VideoFileInfo);
        m_ulCurrentPBHeight = VideoFileInfo.video_info[0].height;

        AHC_Display_GetWidthHdight(&DispWidth, &DispHeight);

        MMPS_VIDPLAY_SetScalerCfg(&cfg, cfg.bUseScaler, DispWidth, DispHeight, 0, 0);
        
        if ((m_ulCurrentPBHeight == 1088) && (1080 == cfg.ulOutHeight)) {
            // 1080P@60 VR v.s. 1080P output => no scaling
            cfg.ulOutWidth  = 0;
            cfg.ulOutHeight = 0;
            cfg.bUseScaler  = MMP_FALSE;
        }
        else if (cfg.ulOutHeight < m_ulCurrentPBHeight) {
            cfg.bUseScaler = MMP_TRUE;

            if (cfg.ulOutHeight > AHC_HD_VIDPLAY_MAX_HEIGHT) {
                cfg.ulOutWidth = AHC_HD_VIDPLAY_MAX_WIDTH;
                cfg.ulOutHeight = AHC_HD_VIDPLAY_MAX_HEIGHT;
            }
        }
        else {
            cfg.ulOutWidth  = 0;
            cfg.ulOutHeight = 0;
            cfg.bUseScaler  = MMP_FALSE;
        }

        AHC_GetParam(PARAM_ID_DISPLAY_ROTATE_ENABLE,&Param);

        if (Param) {
            MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_MAX, Param, MMP_FALSE, NULL, &cfg);
        }

        // set audio volume
        AHC_GetParam(PARAM_ID_AUDIO_VOLUME_DB      ,&Param);

        #if (AUDIO_SET_DB == 0x01)
        MMPS_AUDIO_SetPlayVolumeDb(Param);
        #else
        MMPS_AUDIO_SetPlayVolume(Param, MMP_FALSE);
        #endif

        //TBD
        MMPS_Display_SetWinActive(LOWER_IMAGE_WINDOW_ID, MMP_FALSE);

        sRet = MMPS_VIDPLAY_Open(m_CurPlayFileName, ulFileNameLen, m_ulVideoPlayStartTime, MMP_TRUE, MMP_TRUE, &cfg);
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;} 
        
        #if 0
        if (err != MMP_ERR_NONE) {

            if(err != MMP_3GPPLAY_ERR_INCORRECT_STATE_OPERATION){
                PRINTF("Close Video\r\n");
                MMPS_VIDPLAY_Close();
            }

            return AHC_FALSE;
        }
        #endif
        
        m_ulVideoPlayStartTime = 0;

        m_ulPlaybackFileType = FileType;

        m_ulVideoPlayStopStatus = AHC_VIDEO_PLAY;

        sRet = MMPS_VIDPLAY_Play((void *)VideoPlayStopCallback, NULL);
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet);} 
        
        if (sRet != MMP_ERR_NONE) {

            MMPS_VIDPLAY_Close();

            #if (SUPPORT_SPEAKER == 1)
            AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO,AHC_FALSE);
            #endif

            m_ulVideoPlayStopStatus = AHC_VIDEO_PLAY_ERROR_STOP;

            AHC_OSDSetActive(THUMBNAIL_OSD_FRONT_ID, AHC_TRUE);

            return AHC_FALSE;
        }

        AHC_GetParam(PARAM_ID_MOVIE_AUTO_PLAY,&Param);

        if (Param) {
            MMPS_VIDPLAY_Pause();
        }
    }
    else if ((FileType == DCF_OBG_MP3) ||
             (FileType == DCF_OBG_WAV) ||
             (FileType == DCF_OBG_OGG) ||
             (FileType == DCF_OBG_WMA))
    {
        AIHC_InitAudioExtDACOut();

        MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH_CARD);

        STRCPY(AudFileInfo.bFileName, FilePathName);
        AudFileInfo.usFileNameLength = STRLEN(FilePathName);

        if ( FileType == DCF_OBG_MP3 ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_MP3;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCMp3Info, MMPS_AUDIO_CODEC_MP3);
        }
        else if ( FileType == DCF_OBG_WAV ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WAVE;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCWavInfo, MMPS_AUDIO_CODEC_WAV);
        }
        else if ( FileType == DCF_OBG_OGG ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_OGG;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCOggInfo, MMPS_AUDIO_CODEC_OGG);
        }
        else if ( FileType == DCF_OBG_WMA ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WMA;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCWmaInfo, MMPS_AUDIO_CODEC_WMA);
        }
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;} 
        
        AHC_GetParam(PARAM_ID_AUDIO_VOLUME, &Param);

        #if (AUDIO_SET_DB == 0x01)
        MMPS_AUDIO_SetPlayVolumeDb(Param);
        #else
        MMPS_AUDIO_SetPlayVolume(Param, MMP_FALSE);
        #endif

        m_ulAudioPlayStartTime = 0;

        m_ulPlaybackFileType = FileType;

        m_ulAudioPlayStopStatus = AHC_AUDIO_EVENT_PLAY;

        sRet = MMPS_AUDIO_StartPlay((void *)AudioPlayStopCallback, (void *)"AUDIO");
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); m_ulAudioPlayStopStatus = AHC_AUDIO_EVENT_EOF; return AHC_FALSE;} 

        m_bAHCAudioPlaying = AHC_TRUE;

        #if (SUPPORT_SPEAKER == 1)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
        #endif
    }
    else {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_SetPlaybackMode_MediaError(UINT32 ResumeTime)
{
    m_ulVideoPlayStartTime = ResumeTime;
    AIHC_SetPlaybackMediaErrorMode();
    return AHC_TRUE;
}
#endif

/**
 @brief Start Img / Video playback

 Start Img / Video playback

 @retval AHC_BOOL
*/
AHC_BOOL AIHC_SetPlaybackMode(void)
{
    UINT32                      CurrentDcfIdx;
    UINT8                       FileType;
    char                        FilePathName[MAX_FULL_FILENAME_SIZE];
    UINT32                      Param;
    MMP_DSC_JPEG_INFO           stJpegInfo;
    UINT16                      DispWidth,DispHeight;
    MMP_ERR                     sRet = MMP_ERR_NONE;
    MMP_ULONG                   ulFileNameLen;
    AHC_DISPLAY_OUTPUTPANEL     outputPanel;
    MMPS_AUDIO_FILEINFO         AudFileInfo;
    MMPS_VIDPLAY_SCALERCONFIG   cfg;
#if !(EN_SPEED_UP_VID & PB_CASE)    
    MMPS_VIDEO_CONTAINER_INFO   VideoFileInfo;
#endif
    
    #if (AHC_MULTI_TRACK_EN == 0)
    if ((!CAM_CHECK_SCD(SCD_CAM_NONE) || !CAM_CHECK_USB(USB_CAM_NONE)) && 
        (m_ubPlaybackRearCam == AHC_TRUE)) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    #endif

    AHC_UF_GetCurrentIndex(&CurrentDcfIdx);

    MEMSET(FilePathName, 0, sizeof(FilePathName)); 

    AHC_UF_GetFilePathNamebyIndex(CurrentDcfIdx, FilePathName);

    AHC_UF_GetFileTypebyIndex(CurrentDcfIdx, &FileType);
    #if (AHC_MULTI_TRACK_EN == 0)
    if ((!CAM_CHECK_SCD(SCD_CAM_NONE) || !CAM_CHECK_USB(USB_CAM_NONE)) && 
        (m_ubPlaybackRearCam == AHC_TRUE)) {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }
    #endif
    m_ulCurrentPBFileType = FileType;

    if (FileType == DCF_OBG_JPG)
    {
        STRCPY(stJpegInfo.bJpegFileName, FilePathName);

        stJpegInfo.usJpegFileNameLength = STRLEN(FilePathName);
        stJpegInfo.ulJpegBufAddr        = 0;
        stJpegInfo.ulJpegBufSize        = 0;
        stJpegInfo.bDecodeThumbnail     = MMP_FALSE;
        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        stJpegInfo.bDecodeLargeThumb    = MMP_FALSE;
        #endif
        stJpegInfo.bValid               = MMP_FALSE;
        stJpegInfo.bPowerOffLogo        = MMP_FALSE;
        stJpegInfo.bReEncodeThumb       = MMP_FALSE;

        AHC_GetDisplayOutputDev(&outputPanel);
        MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, outputPanel);

        if (outputPanel == MMP_DISPLAY_SEL_NTSC_TV) {
            MMPS_DSC_SetPlaybackMode(DSC_TV_NTSC_DECODE_MODE);
        }
        else if (outputPanel == MMP_DISPLAY_SEL_PAL_TV) {
            MMPS_DSC_SetPlaybackMode(DSC_TV_PAL_DECODE_MODE);
        }
        else if (outputPanel == MMP_DISPLAY_SEL_HDMI) {
            MMPS_DSC_SetPlaybackMode(DSC_HDMI_DECODE_MODE);
        }
        #if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)        
        else if (outputPanel == MMP_DISPLAY_SEL_CCIR) {
            MMPS_DSC_SetPlaybackMode(DSC_CCIR_DECODE_MODE);
        }
        #endif
        else {
            MMPS_DSC_SetPlaybackMode(DSC_NORMAL_DECODE_MODE);
        }

        sRet = MMPS_DSC_PlaybackJpeg(&stJpegInfo, 0, 0);
        if (sRet != MMP_ERR_NONE) {
            AHC_PRINT_RET_ERROR(0,sRet);
            MMPS_DSC_ExitJpegPlayback();
            return AHC_FALSE;
        }
        
        m_ulPlaybackFileType = FileType;
        return AHC_TRUE;
    }
    else if ( ( FileType == DCF_OBG_MOV ) ||
              ( FileType == DCF_OBG_MP4 ) ||
              ( FileType == DCF_OBG_AVI ) ||
              ( FileType == DCF_OBG_3GP ) ||
              ( FileType == DCF_OBG_TS  ) ||
              ( FileType == DCF_OBG_WMV ) )
    {
        AIHC_InitAudioExtDACOut();

        MMPS_VIDPLAY_SetMemoryMode(MMP_FALSE);

#if (DAC_NOT_OUTPUT_SPEAKER_HAS_NOISE)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);
#else
        #if (SUPPORT_SPEAKER == 1)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
        #endif
#endif

        AHC_GetDisplayOutputDev( &outputPanel );

        MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, outputPanel);

        #if (SUPPORT_SYS_CALIBRATION)
        if (uiGetCurrentState() == UI_SYS_CALIBRATION_STATE) {
            STRCPY(m_CurPlayFileName, "SD:\\test\\VideoRec.MOV");
            ulFileNameLen = STRLEN("SD:\\test\\VideoRec.MOV");
        }
        else
        #endif
        {
            STRCPY(m_CurPlayFileName, FilePathName);
            ulFileNameLen = STRLEN(FilePathName);
        }

        AHC_GetParam(PARAM_ID_DISPLAY_ROTATE_ENABLE,&Param);

        if (Param) {

            m_ulCurrentPBWidth = MMPS_VIDPLAY_Get3gpConTnerVidInf()->width;
            m_ulCurrentPBHeight = MMPS_VIDPLAY_Get3gpConTnerVidInf()->height; 

            AHC_Display_GetWidthHdight(&DispWidth, &DispHeight);//#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)

            MMPS_VIDPLAY_SetScalerCfg(&cfg, cfg.bUseScaler, DispWidth, DispHeight, 0, 0);
            if ((m_ulCurrentPBHeight == 1088) && (1080 == cfg.ulOutHeight)) {
                // 1080P@60 VR v.s. 1080P output => no scaling
                cfg.ulOutWidth  = 0;
                cfg.ulOutHeight = 0;
                cfg.bUseScaler  = MMP_FALSE;
            }
            else if (cfg.ulOutHeight < m_ulCurrentPBHeight) {
                cfg.bUseScaler = MMP_TRUE;
                
                if (cfg.ulOutHeight > AHC_HD_VIDPLAY_MAX_HEIGHT) {
                    cfg.ulOutWidth = AHC_HD_VIDPLAY_MAX_WIDTH;
                    cfg.ulOutHeight = AHC_HD_VIDPLAY_MAX_HEIGHT;
                }
            }
            else {
                cfg.ulOutWidth  = 0;
                cfg.ulOutHeight = 0;
                cfg.bUseScaler = MMP_FALSE;
            }
            MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_MAX, Param, MMP_FALSE, NULL, &cfg);
        }
        else//HDMI TV out
        {
            AHC_DISPLAY_OUTPUTPANEL sOutputDevice;
            AHC_GetDisplayOutputDev(&sOutputDevice);
            if(sOutputDevice == AHC_DISPLAY_NTSC_TV)
                 MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_NTSC_TV, Param, MMP_TRUE, NULL, &cfg);
            else if(sOutputDevice == AHC_DISPLAY_PAL_TV)
                MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_PAL_TV, Param, MMP_TRUE, NULL, &cfg);
            else if(sOutputDevice == AHC_DISPLAY_HDMI)
                MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_HDMI, Param, MMP_TRUE, NULL, &cfg);
        }

        // set audio volume
        AHC_GetParam(PARAM_ID_AUDIO_VOLUME_DB      ,&Param);

        #if (AUDIO_SET_DB == 0x01)
        MMPS_AUDIO_SetPlayVolumeDb(Param);
        #else
        MMPS_AUDIO_SetPlayVolume(Param, MMP_FALSE);
        #endif

        //TBD
        MMPS_Display_SetWinActive(LOWER_IMAGE_WINDOW_ID, MMP_FALSE);

#if !(EN_SPEED_UP_VID & PB_CASE)
        sRet = MMPS_VIDPLAY_GetFileInfo(m_CurPlayFileName, ulFileNameLen, &VideoFileInfo);
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(0,sRet); return AHC_FALSE;} 
        
        m_ulCurrentPBHeight = VideoFileInfo.video_info[0].height;

        AHC_Display_GetWidthHdight(&DispWidth, &DispHeight);//#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)

        cfg.ulOutWidth = DispWidth;
        cfg.ulOutHeight = DispHeight;
        if ((m_ulCurrentPBHeight == 1088) && (1080 == cfg.ulOutHeight)) {
            // 1080P@60 VR v.s. 1080P output => no scaling
            cfg.ulOutWidth  = 0;
            cfg.ulOutHeight = 0;
            cfg.bUseScaler  = MMP_FALSE;
        }
        else if (cfg.ulOutHeight < m_ulCurrentPBHeight) {
            cfg.bUseScaler = MMP_TRUE;
            
            if (cfg.ulOutHeight > AHC_HD_VIDPLAY_MAX_HEIGHT) {
                cfg.ulOutWidth = AHC_HD_VIDPLAY_MAX_WIDTH;
                cfg.ulOutHeight = AHC_HD_VIDPLAY_MAX_HEIGHT;
            }
        }
        else {
            cfg.ulOutWidth  = 0;
            cfg.ulOutHeight = 0;
            cfg.bUseScaler = MMP_FALSE;
        }
#else
        AHC_Display_GetWidthHdight(&DispWidth, &DispHeight);//#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)
        MMPS_VIDPLAY_SetScalerCfg(&cfg, cfg.bUseScaler, DispWidth, DispHeight, AHC_HD_VIDPLAY_MAX_WIDTH, AHC_HD_VIDPLAY_MAX_HEIGHT);
#endif
        if ( FileType == DCF_OBG_TS ) {
            MMPS_VIDPLAY_SetCurrentTrack(0);
        }
        else {
            #if VIDRECD_MULTI_TRACK
            if (m_ubPlaybackRearCam == AHC_TRUE) {
                MMPS_VIDPLAY_SetCurrentTrack(1);  //playback rear cam.
            }
            else {
                MMPS_VIDPLAY_SetCurrentTrack(0);  //playback front cam.
            }
            #endif
        }
        //TBD: TL
        //if (FileType != DCF_OBG_TS)
        {
            MMPS_VIDEO_CONTAINER_INFO info;
            sRet = MMPS_VIDPLAY_GetContainerInfo(m_CurPlayFileName, STRLEN(FilePathName), &info); 
        }
        sRet = MMPS_VIDPLAY_Open(m_CurPlayFileName, ulFileNameLen, m_ulVideoPlayStartTime, MMP_TRUE, MMP_TRUE, &cfg);
        DBG_AutoTestPrint(ATEST_ACT_PB_VID_0x0003,
                            ATEST_STS_RSOL_SIZE_0x0004, 
                            m_ulCurrentPBWidth, 
                            m_ulCurrentPBHeight, 
                            gbAhcDbgBrk);
#if (EN_SPEED_UP_VID & PB_CASE)
        m_ulCurrentPBWidth = MMPS_VIDPLAY_Get3gpConTnerVidInf()->width;
        m_ulCurrentPBHeight = MMPS_VIDPLAY_Get3gpConTnerVidInf()->height; 
#endif
        if (sRet != MMP_ERR_NONE) {
            if(sRet != MMP_3GPPLAY_ERR_INCORRECT_STATE_OPERATION){
                PRINTF("Close Video\r\n");
                MMPS_VIDPLAY_Close();
            }
            AHC_PRINT_RET_ERROR(0,sRet);
            return AHC_FALSE;
        }

        m_ulVideoPlayStartTime = 0;

        m_ulPlaybackFileType = FileType;

        m_ulVideoPlayStopStatus = AHC_VIDEO_PLAY;

        sRet = MMPS_VIDPLAY_Play((void *)VideoPlayStopCallback, NULL);
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet);} 

        if (sRet != MMP_ERR_NONE) {

            MMPS_VIDPLAY_Close();

            AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);

            m_ulVideoPlayStopStatus = AHC_VIDEO_PLAY_ERROR_STOP;

            AHC_OSDSetActive(THUMBNAIL_OSD_FRONT_ID, AHC_TRUE);

            return AHC_FALSE;
        }

#if (DAC_NOT_OUTPUT_SPEAKER_HAS_NOISE)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);
#else
        #if (SUPPORT_SPEAKER == 1)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
        #endif
#endif

        AHC_GetParam(PARAM_ID_MOVIE_AUTO_PLAY,&Param);

        if(Param) {
            MMPS_VIDPLAY_Pause();
        }
    }
    else if ( ( FileType == DCF_OBG_MP3 ) ||
              ( FileType == DCF_OBG_WAV ) ||
              ( FileType == DCF_OBG_OGG ) ||
              ( FileType == DCF_OBG_WMA ) )
    {
        AIHC_InitAudioExtDACOut();

        MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH_CARD);

        STRCPY(AudFileInfo.bFileName, FilePathName);
        AudFileInfo.usFileNameLength = STRLEN(FilePathName);

        if ( FileType == DCF_OBG_MP3 ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_MP3;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCMp3Info, MMPS_AUDIO_CODEC_MP3);
        }
        else if ( FileType == DCF_OBG_WAV ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WAVE;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCWavInfo, MMPS_AUDIO_CODEC_WAV);
        }
        else if ( FileType == DCF_OBG_OGG ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_OGG;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCOggInfo, MMPS_AUDIO_CODEC_OGG);
        }
        else if ( FileType == DCF_OBG_WMA ) {
            m_uiPlayAudioFmt = AHC_AUDIO_PLAY_FMT_WMA;
            sRet = MMPS_AUDIO_OpenFile(AudFileInfo, &m_gsAHCWmaInfo, MMPS_AUDIO_CODEC_WMA);
        }
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;} 

        AHC_GetParam(PARAM_ID_AUDIO_VOLUME, &Param);

        #if (AUDIO_SET_DB == 0x01)
        MMPS_AUDIO_SetPlayVolumeDb(Param);
        #else
        MMPS_AUDIO_SetPlayVolume(Param, MMP_FALSE);
        #endif

        m_ulAudioPlayStartTime = 0;

        m_ulPlaybackFileType = FileType;

        m_ulAudioPlayStopStatus = AHC_AUDIO_EVENT_PLAY;

        sRet = MMPS_AUDIO_StartPlay((void *)AudioPlayStopCallback, (void *)"AUDIO");
        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); m_ulAudioPlayStopStatus = AHC_AUDIO_EVENT_EOF; return AHC_FALSE;} 

        m_bAHCAudioPlaying = AHC_TRUE;

        #if (SUPPORT_SPEAKER == 1)        
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_TRUE);
        #endif
    }
    else {
        //TBD
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StopPlaybackMode
//  Description : Stop Image / Video playback
//------------------------------------------------------------------------------
AHC_BOOL AIHC_StopPlaybackMode(void)
{
    MMP_M_STATE     ubVideoState;
    MMP_ULONG       KeyFrameNum;
    MMP_ERR         sRet = MMP_ERR_NONE;

    if ((m_ulPlaybackFileType == DCF_OBG_MOV) ||
        (m_ulPlaybackFileType == DCF_OBG_MP4) ||
        (m_ulPlaybackFileType == DCF_OBG_AVI) ||
        (m_ulPlaybackFileType == DCF_OBG_3GP) ||
        (m_ulPlaybackFileType == DCF_OBG_TS ) ||
        (m_ulPlaybackFileType == DCF_OBG_WMV)) {

        MMPS_VIDPLAY_GetState(&ubVideoState);

        if (ubVideoState != MMP_M_STATE_IDLE) {
            MMPS_VIDPLAY_Stop(&KeyFrameNum);
        }

        sRet = MMPS_VIDPLAY_Close();
        
        DBG_AutoTestPrint(ATEST_ACT_PB_VID_0x0003, ATEST_STS_END_0x0003, 0, sRet, gbAhcDbgBrk);

        #if (SUPPORT_SPEAKER == 1)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO,AHC_FALSE);
        #endif
    }
    else if ((m_ulPlaybackFileType == DCF_OBG_MP3) ||
             (m_ulPlaybackFileType == DCF_OBG_WAV) ||
             (m_ulPlaybackFileType == DCF_OBG_OGG) ||
             (m_ulPlaybackFileType == DCF_OBG_WMA)) {

        MMPS_AUDIO_StopPlay();
        
        #if (SUPPORT_SPEAKER == 1)
        AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);
        #endif
        
        m_bAHCAudioPlaying = AHC_FALSE;
    }
    else if (m_ulPlaybackFileType == DCF_OBG_JPG) {
        MMPS_DSC_ExitJpegPlayback();
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetVideoCurrentPlayTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get video current play time

 This API gets the current time of playing video file.
 @param[in] *pulTime The current time of playing audio file.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetVideoCurrentPlayTime(UINT32 *pulTime)
{
    MMP_ULONG ulCurTime;

    MMPS_VIDPLAY_GetCurrentTime(&ulCurTime);

    *pulTime = ulCurTime;

    return AHC_TRUE;
}

/**
 @brief Play clip

 This functions controls playback of video and audio files and it works
 only under playback mode.
 Parameters:
 @param[in] bCommand Commands for controlling.
 @param[in] iOp Operand.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PlaybackClipCmd(AHC_PLAYBACK_CMDS bCommand, UINT32 iOp)
{
    UINT16          volume;
    UINT32          ret = AHC_TRUE;
    MMP_ERR         error;
    MMP_M_STATE     state;
    UINT16          DispWidth, DispHeight, Height;

    MMPS_VIDPLAY_SCALERCONFIG   cfg;

    switch(bCommand) {
    case AHC_PB_MOVIE_PAUSE:
        ret = MMPS_VIDPLAY_Pause();
        break;
    case AHC_PB_MOVIE_RESUME:
        ret = MMPS_VIDPLAY_Resume();
        break;
    case AHC_PB_MOVIE_FAST_FORWARD:
        if(m_ulMovPlayFFSpeed > 1)
            ret = MMPS_VIDPLAY_SetPlaySpeed(MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD, (m_ulMovPlayFFSpeed - 1)*100);
        break;
    case AHC_PB_MOVIE_FAST_FORWARD_RATE:
        m_ulMovPlayFFSpeed = (iOp / 1000);
        break;
    case AHC_PB_MOVIE_BACKWARD:
        if(m_ulMovPlayRewSpeed > 1)
            ret = MMPS_VIDPLAY_SetPlaySpeed(MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD, (m_ulMovPlayRewSpeed - 1)*100);
        break;
    case AHC_PB_MOVIE_NORMAL_PLAY_SPEED:
        ret = MMPS_VIDPLAY_SetPlaySpeed(MMPS_VIDPLAY_PLAYSPEED_NORMAL, 100);
        break;
    case AHC_PB_MOVIE_BACKWARD_RATE:
        m_ulMovPlayRewSpeed = (iOp / 1000);
        break;
    case AHC_PB_MOVIE_AUDIO_MUTE:
        if(iOp) {
            MMPS_AUDIO_GetPlayVolume(&m_CurrentVolume);
            ret = MMPS_AUDIO_SetPlayVolume(0,0);
        }
        else {
            MMPS_AUDIO_GetPlayVolume(&volume);

            if(volume == 0) {
                ret = MMPS_AUDIO_SetPlayVolume(m_CurrentVolume,0);
            }
        }
        break;
    case AHC_PB_MOVIE_SEEK_BY_TIME:
        ret = MMPS_VIDPLAY_SeekByTime(iOp, MMPS_VIDPSR_NEXT_KEYFRAME);
        break;
    case AHC_PB_MOVIE_SEEK_TO_SOS:
        ret = MMPS_VIDPLAY_SeekByTime(0, MMPS_VIDPSR_SEEK_PRECISE);
        break;
    case AHC_PB_MOVIE_ROTATE:
        error = MMPS_VIDPLAY_GetState(&state);

        if (MMP_M_STATE_EXECUTING == state) {
            MMPS_VIDPLAY_SetVideoDecodeEnable(MMP_FALSE);
        }

        AIHC_GetCurrentPBHeight(&Height);
        AHC_Display_GetWidthHdight(&DispWidth, &DispHeight);

        MMPS_VIDPLAY_SetScalerCfg(&cfg, cfg.bUseScaler, DispWidth, DispHeight, 0, 0);
        if ((Height == 1088) && (1080 == cfg.ulOutHeight)) {
            // 1080P@60 VR v.s. 1080P output => no scaling
            cfg.ulOutWidth  = 0;
            cfg.ulOutHeight = 0;
            cfg.bUseScaler  = MMP_FALSE;
        }
        else if (cfg.ulOutHeight < Height) {
            cfg.bUseScaler = MMP_TRUE;

            if (cfg.ulOutHeight > AHC_HD_VIDPLAY_MAX_HEIGHT) {
                cfg.ulOutWidth = AHC_HD_VIDPLAY_MAX_WIDTH;
                cfg.ulOutHeight = AHC_HD_VIDPLAY_MAX_HEIGHT;
            }
        }
        else {
            cfg.ulOutWidth = 0;
            cfg.ulOutHeight = 0;
            cfg.bUseScaler = MMP_FALSE;
        }

        if (MMP_M_STATE_EXECUTING == state) {
            ret = MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_MAX, iOp, MMP_FALSE, NULL, &cfg);
        }
        else {
            ret = MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_MAX, iOp, MMP_TRUE, NULL, &cfg);
        }

        if (MMP_M_STATE_EXECUTING == state) {

            MMPS_VIDPLAY_SetVideoDecodeEnable(MMP_TRUE);
        }

        break;
    }

    if ( ret )
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetVideoCurrentPlayTime
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDPLAY_SetPlaySpeed(AHC_PLAYBACK_CMDS cmd, UINT32 speed)
{
    if (cmd == AHC_PB_MOVIE_FAST_FORWARD_RATE) {
        m_ulMovPlayFFSpeed = speed;
    }
    else if (cmd == AHC_PB_MOVIE_BACKWARD_RATE) {
        m_ulMovPlayRewSpeed = speed;
    }
}

/**
 @brief Get audio file attribute

 This API gets the information of an video file. The file must be selected as
 current DCF object first.
 @param[out] *pVideoAttr Address for placing the video attributes.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetVideoFileAttr(AHC_VIDEO_ATTR *pVideoAttr)
{
    UINT32                      CurrentDcfIdx,CurFileType;
    char                        FilePathName[MAX_FULL_FILENAME_SIZE];
    UINT8                       ubFileType;
    UINT32                      CurMode;
    MMPS_VIDEO_CONTAINER_INFO   VideoInfo;
    MMP_ERR                     err;

    if (!pVideoAttr) {
        return AHC_FALSE;
    }

    MEMSET(pVideoAttr, 0, sizeof(AHC_VIDEO_ATTR) );

    AHC_GetSystemStatus(&CurMode);

    CurMode >>= 16;

    if ( (AHC_MODE_IDLE == CurMode) || (AHC_MODE_THUMB_BROWSER == CurMode) ){
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }
        AHC_UF_GetCurrentIndex(&CurrentDcfIdx);
        MEMSET(FilePathName, 0, sizeof(FilePathName));
        AHC_UF_GetFilePathNamebyIndex(CurrentDcfIdx, FilePathName);
        AHC_UF_GetFileTypebyIndex(CurrentDcfIdx, &ubFileType);
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }

        if ( ( ubFileType == DCF_OBG_MOV ) ||
             ( ubFileType == DCF_OBG_MP4 ) ||
             ( ubFileType == DCF_OBG_AVI ) ||
             ( ubFileType == DCF_OBG_3GP ) ||
             ( ubFileType == DCF_OBG_TS )  ||
             ( ubFileType == DCF_OBG_WMV ) ) {
            err = MMPS_VIDPLAY_GetContainerInfo(FilePathName, STRLEN(FilePathName), &VideoInfo);
        }
        else
            return AHC_FALSE;
    }
    else if (AHC_MODE_PLAYBACK == CurMode) {
        AIHC_GetCurrentPBFileType(&CurFileType);

        if ( ( CurFileType == DCF_OBG_MOV ) ||
             ( CurFileType == DCF_OBG_MP4 ) ||
             ( CurFileType == DCF_OBG_AVI ) ||
             ( CurFileType == DCF_OBG_3GP ) ||
             ( CurFileType == DCF_OBG_TS  ) ||
             ( CurFileType == DCF_OBG_WMV ) ) {

            err = MMPS_VIDPLAY_GetFileInfo(NULL, 0, &VideoInfo);
        }
        else
            return AHC_FALSE;
    }
    else {
        return AHC_FALSE;
    }

    if (MMP_ERR_NONE == err) {
        pVideoAttr->VideoAvailable[0]  = VideoInfo.is_video_available[0];
        pVideoAttr->VideoAvailable[1]  = VideoInfo.is_video_available[1];
        pVideoAttr->AudioAvailable  = VideoInfo.is_audio_available;
        pVideoAttr->Seekable[0]        = VideoInfo.is_video_seekable[0];
        pVideoAttr->Seekable[1]        = VideoInfo.is_video_seekable[1];
        pVideoAttr->TotalTime       = VideoInfo.total_file_time;

        pVideoAttr->VideoFormat[0]     = VideoInfo.video_info[0].format;
        pVideoAttr->VideoFormat[1]     = VideoInfo.video_info[1].format;
        pVideoAttr->Width[0]           = VideoInfo.video_info[0].width;
        pVideoAttr->Height[0]          = VideoInfo.video_info[0].height;
        pVideoAttr->Width[1]           = VideoInfo.video_info[1].width;
        pVideoAttr->Height[1]          = VideoInfo.video_info[1].height;

        pVideoAttr->AudioFormat     = VideoInfo.audio_info.format;
        pVideoAttr->SampleRate      = VideoInfo.audio_info.sampling_rate;
        pVideoAttr->Channels        = VideoInfo.audio_info.channel_nums;
    }
    else {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Playback_GetImageAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get image attribute

 This function get the attributes of current selected image.
 Parameters:
 @param[out] *pImgAttr ImageHSize, ImageVSize, ThumbHSize, ThumbVSize..etc
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Playback_GetImageAttr(AHC_IMG_ATTR *pImgAttr)
{
    MMP_ERR             error = MMP_ERR_NONE;
    MMP_DSC_JPEG_INFO   stJpegInfo;
    UINT32              u32CurDcfIdx = 0;
    UINT8               u8FileType = 0;
    char                FilePathName[MAX_FULL_FILENAME_SIZE];

    // Get file name
    AHC_UF_GetCurrentIndex(&u32CurDcfIdx);

    MEMSET(FilePathName, 0, sizeof(FilePathName));

    AHC_UF_GetFilePathNamebyIndex(u32CurDcfIdx, FilePathName);
    AHC_UF_GetFileTypebyIndex(u32CurDcfIdx, &u8FileType);

    if (u8FileType == DCF_OBG_JPG) {

        STRCPY(stJpegInfo.bJpegFileName, FilePathName);

        stJpegInfo.usJpegFileNameLength   = STRLEN(FilePathName);
        stJpegInfo.ulJpegBufAddr          = 0;
        stJpegInfo.ulJpegBufSize          = 0;
        stJpegInfo.bDecodeThumbnail       = MMP_FALSE;
        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        stJpegInfo.bDecodeLargeThumb      = MMP_TRUE;
        #endif
        stJpegInfo.bValid                 = MMP_FALSE;

        error = MMPS_DSC_GetJpegInfo(&stJpegInfo);

        if (error == MMP_ERR_NONE) {
            pImgAttr->ImageHSize = stJpegInfo.usPrimaryWidth;
            pImgAttr->ImageVSize = stJpegInfo.usPrimaryHeight;
            pImgAttr->ThumbHSize = stJpegInfo.usThumbWidth;
            pImgAttr->ThumbVSize = stJpegInfo.usThumbHeight;

            return AHC_TRUE;
        }
        else {
            return AHC_FALSE;
        }
    }
    else {
        return AHC_FALSE;
    }
}
