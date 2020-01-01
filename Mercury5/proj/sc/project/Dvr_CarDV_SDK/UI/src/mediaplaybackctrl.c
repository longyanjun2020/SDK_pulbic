/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "lcd_common.h"
#include "ahc_common.h"
#include "ahc_parameter.h"
#include "ahc_general.h"
#include "ahc_mediaplayback.h"
#include "ahc_message.h"
#include "ahc_utility.h"
#include "ahc_display.h"
#include "ahc_audio.h"
#include "ahc_capture.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_browser.h"
#include "ahc_video.h"
#include "ahc_os.h"
#include "mediaplaybackctrl.h"
#include "IconPosition.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define  JPG_PAN_SPEED			(30)
#define  JPG_MAX_ZOOMLEVEL		(8)

/*===========================================================================
 * Global varible
 *===========================================================================*/

static PLAYBACK_FILETYPE   	iFileType;
static JPG_PLAYBACK_CONFIG 	JpgConfig;
static MOV_PLAYBACK_CONFIG 	MovConfig;
static AUD_PLAYBACK_CONFIG 	AudConfig;
extern AHC_BOOL 			m_ubPlaybackRearCam;


/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ________Photo_Function_________(){ruturn;} //dummy
#endif

PLAYBACK_FILETYPE GetPlayBackFileType(void)
{
    return iFileType;
}

JPG_PLAYBACK_CONFIG *GetJpgConfig(void)
{
    return &JpgConfig;
}

void JpgZoomCalc(UINT32 ZoomLevel,UINT32 *OffsetX,UINT32 *OffsetY, UINT32 *DispWidth,UINT32 *DispHeight)
{
    MMPS_DSC_PlaybackCalculatePTZ(ZoomLevel, OffsetX, OffsetY, DispWidth, DispHeight);
}

void JpgPlaybackParamReset(void)
{
    JpgConfig.iRotate 		= AHC_DISPLAY_ROTATE_NO_ROTATE;
    JpgConfig.iCurZoomLevel = 0;
    JpgConfig.iDecodeWidth 	= 1024;
    JpgConfig.iDecodeHeight = 768;
}

AHC_BOOL JpgPlayback_Play(void)
{
    return AHC_SetMode(AHC_MODE_PLAYBACK);
}

AHC_BOOL JpgPlayback_Zoom(JPGPB_ZOOM_CTRL uJpgZoomSel)
{
    AHC_BOOL 	ahc_ret = AHC_TRUE;
    UINT32 		OffsetX,OffsetY;

    switch(uJpgZoomSel)
    {
        case JPGPB_ZOOM_IN   :

            if(JpgConfig.iCurZoomLevel < JPG_MAX_ZOOMLEVEL) {

                JpgZoomCalc(JpgConfig.iCurZoomLevel+1, &OffsetX, &OffsetY, &JpgConfig.iJpegDispWidth, &JpgConfig.iJpegDispHeight);

                ahc_ret = AHC_PlaybackZoom(OffsetX, OffsetY, JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight);

                if ( AHC_TRUE == ahc_ret )
                {
                    JpgConfig.iStartX = OffsetX;
                    JpgConfig.iStartY = OffsetY;
                    JpgConfig.iCurZoomLevel++;
                }
            }
        break;

        case JPGPB_ZOOM_OUT  :

            if( 0 < JpgConfig.iCurZoomLevel )
            {
                JpgZoomCalc(JpgConfig.iCurZoomLevel-1, &OffsetX, &OffsetY, &JpgConfig.iJpegDispWidth, &JpgConfig.iJpegDispHeight);
            }
            else
            {
                JpgZoomCalc(0, &OffsetX, &OffsetY, &JpgConfig.iJpegDispWidth, &JpgConfig.iJpegDispHeight);
            }

            ahc_ret = AHC_PlaybackZoom(OffsetX, OffsetY, JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight);

            if ( AHC_TRUE == ahc_ret )
            {
                JpgConfig.iStartX = OffsetX;
                JpgConfig.iStartY = OffsetY;

                if (JpgConfig.iCurZoomLevel > 0)
                    JpgConfig.iCurZoomLevel--;
            }
        break;

        case JPGPB_ZOOM_NONE :
            JpgConfig.iCurZoomLevel = 0;
            JpgZoomCalc(JpgConfig.iCurZoomLevel, &OffsetX, &OffsetY, &JpgConfig.iJpegDispWidth, &JpgConfig.iJpegDispHeight);
            ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX  + OffsetX, JpgConfig.iStartY  + OffsetY, JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight);
        break;

        default:
            printc("ImagePlayback_ZoomControl: Not support! \n");
        break;
    }
    return ahc_ret;
}

AHC_BOOL JpgPlayback_IsZoomNone(void)
{
    if(JpgConfig.iCurZoomLevel == 0)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL JpgPlayback_Pan(JPGPB_PAN_CTRL ulDir)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    AHC_DISPLAY_OUTPUTPANEL    	OutputDevice;
    
    AHC_GetDisplayOutputDev(&OutputDevice);

    if(OutputDevice == AHC_DISPLAY_MAIN_LCD)
    {
        switch(ulDir)
        {
            case JPGPB_PAN_UP    :
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY-JPG_PAN_SPEED), JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  -= JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) 
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX+JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX += JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270) //TBD
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX+JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX += JPG_PAN_SPEED;                
#endif
            break;

            case JPGPB_PAN_DOWN  :
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY+JPG_PAN_SPEED),JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  += JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) 
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX-JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX -= JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270) //TBD
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX-JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX -= JPG_PAN_SPEED;
#endif
            break;

            case JPGPB_PAN_LEFT  :
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX-JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX -= JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) 
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY-JPG_PAN_SPEED), JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  -= JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270) //TBD
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY-JPG_PAN_SPEED), JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  -= JPG_PAN_SPEED;
#endif
            break;

            case JPGPB_PAN_RIGHT :
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX+JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX += JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) 
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY+JPG_PAN_SPEED),JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  += JPG_PAN_SPEED;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270) //TBD
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY+JPG_PAN_SPEED),JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  += JPG_PAN_SPEED;
#endif
            break;

            default:
                printc("JpgPlayback_PanControl: Not support! \n");
            break;
        }
    }
    else
    {
        switch(ulDir)
        {
            case JPGPB_PAN_UP    :
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY-JPG_PAN_SPEED), JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  -= JPG_PAN_SPEED;
            break;

            case JPGPB_PAN_DOWN  :
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom(JpgConfig.iStartX, (JpgConfig.iStartY+JPG_PAN_SPEED),JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartY  += JPG_PAN_SPEED;
            break;

            case JPGPB_PAN_LEFT  :
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX-JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX -= JPG_PAN_SPEED;
            break;

            case JPGPB_PAN_RIGHT :
                if ( AHC_TRUE == (ahc_ret = AHC_PlaybackZoom((JpgConfig.iStartX+JPG_PAN_SPEED), JpgConfig.iStartY ,JpgConfig.iJpegDispWidth, JpgConfig.iJpegDispHeight)) )
                    JpgConfig.iStartX += JPG_PAN_SPEED;
            break;

            default:
                printc("JpgPlayback_PanControl: Not support! \n");
            break;
        }
    }

    return ahc_ret;
}

AHC_BOOL JpgPlayback_Rotate( MEDIAPB_ROTATE_CTRL ulDir )
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    if(MEDIAPB_ROTATE_CW == ulDir)
    {
        JpgConfig.iRotate = (JpgConfig.iRotate < AHC_DISPLAY_ROTATE_RIGHT_270)?(JpgConfig.iRotate+1):AHC_DISPLAY_ROTATE_NO_ROTATE;
    }
    else if(MEDIAPB_ROTATE_CCW == ulDir)
    {
        JpgConfig.iRotate = (JpgConfig.iRotate > AHC_DISPLAY_ROTATE_NO_ROTATE)?(JpgConfig.iRotate-1):AHC_DISPLAY_ROTATE_RIGHT_270;
    }

    return ahc_ret;
}

void JpgPlaybackSetOutputDev(AHC_DISPLAY_OUTPUTPANEL Device)
{
    AHC_DISPLAY_HDMIOUTPUTMODE HdmiMode;
    UINT16 Width, Height;

    switch(Device)
    {
        case AHC_DISPLAY_MAIN_LCD:
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_TRUE, AHC_FALSE, 0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH);
        break;

        case AHC_DISPLAY_HDMI:
            AHC_GetHDMIOutputMode(&HdmiMode);
            AHC_GetHdmiDisplayWidthHeight(&Width, &Height);

            switch(HdmiMode){
                case AHC_DISPLAY_HDMIOUTPUT_1920X1080P:
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height);
                    break;
                case AHC_DISPLAY_HDMIOUTPUT_1920X1080I:
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height<<1);
                    break;
                case AHC_DISPLAY_HDMIOUTPUT_1280X720P:
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height);
                    break;
                case AHC_DISPLAY_HDMIOUTPUT_640X480P:  //TBD
                case AHC_DISPLAY_HDMIOUTPUT_720X480P:
                case AHC_DISPLAY_HDMIOUTPUT_720X576P:
                case AHC_DISPLAY_HDMIOUTPUT_1280X720P_50FPS:
                case AHC_DISPLAY_HDMIOUTPUT_1920X1080P_30FPS:
                default:
                    printc(0, "JpgPlayback_Config: It doesn't support the HDMI output!!\r\n");
                    break;
            }
        break;

        case AHC_DISPLAY_NTSC_TV:
            AHC_GetNtscTvDisplayWidthHeight(&Width, &Height);
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height-20);
        break;

        case AHC_DISPLAY_PAL_TV:
            AHC_GetPalTvDisplayWidthHeight(&Width, &Height);
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width-30, Height-20);
        break;
    }
}

#if 0
void ________Movie_Function_________(){ruturn;} //dummy
#endif

MOV_PLAYBACK_CONFIG *GetMovConfig(void)
{
    return &MovConfig;
}

AHC_BOOL GetMovTotalTime(UINT32 *ultime)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    AHC_VIDEO_ATTR  Info;

    ahc_ret = AHC_GetVideoFileAttr(&Info);

    *ultime = (AHC_TRUE == ahc_ret)?(Info.TotalTime):(0);

    return ahc_ret;
}

AHC_BOOL GetMovCurrPlayTime(UINT32 *ultime)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32 ulCurtime;

    ahc_ret = AHC_GetVideoCurrentPlayTime(&ulCurtime);

    *ultime = (AHC_TRUE == ahc_ret)?(ulCurtime):(0);

    return ahc_ret;
}

void MovPlaybackParamReset(void)
{
    MovConfig.iState  = MOV_STATE_STOP;
    MovConfig.iRotate = AHC_DISPLAY_ROTATE_NO_ROTATE;
}

AHC_BOOL MovPlayback_Play(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = AHC_SetMode(AHC_MODE_PLAYBACK);

    if(AHC_TRUE == ahc_ret)
        MovConfig.iState = MOV_STATE_PLAY;

    return ahc_ret;
}

AHC_BOOL MovPlayback_Forward(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32  ulState;

    AHC_GetVideoPlayStopStatus(&ulState);
    if (ulState) {
        return ahc_ret;
    }
    AHC_SetVideoPlayStopStatus(AHC_VIDEO_PLAY);
    AHC_PlaybackClipCmd(AHC_PB_MOVIE_PAUSE, 0);
    ahc_ret = AHC_PlaybackClipCmd(AHC_PB_MOVIE_FAST_FORWARD, 0);
    AHC_PlaybackClipCmd(AHC_PB_MOVIE_RESUME, 0);
    MovConfig.iState = MOV_STATE_FF;

    return ahc_ret;
}

AHC_BOOL MovPlayback_Backward(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32  ulState;
    
    AHC_GetVideoPlayStopStatus(&ulState);
    if (ulState) {
        return ahc_ret;
    }
    AHC_SetVideoPlayStopStatus(AHC_VIDEO_PLAY);
    AHC_PlaybackClipCmd(AHC_PB_MOVIE_PAUSE, 0);
    ahc_ret = AHC_PlaybackClipCmd(AHC_PB_MOVIE_BACKWARD, 0);
    AHC_PlaybackClipCmd(AHC_PB_MOVIE_RESUME, 0);
    MovConfig.iState = MOV_STATE_FF;

    return ahc_ret;
}

AHC_BOOL MovPlayback_NormalSpeed(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32  ulState;
    
    AHC_GetVideoPlayStopStatus(&ulState);
    if (ulState) {
        return ahc_ret;
    }

    extern void MovPBFunc_ResetPlaySpeed(void);
    MovPBFunc_ResetPlaySpeed();

    ahc_ret = AHC_PlaybackClipCmd(AHC_PB_MOVIE_NORMAL_PLAY_SPEED, 0);
    MovConfig.iState = MOV_STATE_PLAY;

    return ahc_ret;
}

AHC_BOOL MovPlayback_Rotate(MEDIAPB_ROTATE_CTRL ulDir)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    if(MEDIAPB_ROTATE_CW == ulDir)
    {
        MovConfig.iRotate = (MovConfig.iRotate < AHC_DISPLAY_ROTATE_RIGHT_270)?(MovConfig.iRotate+1):AHC_DISPLAY_ROTATE_NO_ROTATE;
    }
    else if(MEDIAPB_ROTATE_CCW == ulDir)
    {
        MovConfig.iRotate = (MovConfig.iRotate > AHC_DISPLAY_ROTATE_NO_ROTATE)?(MovConfig.iRotate-1):AHC_DISPLAY_ROTATE_RIGHT_270;
    }

    ahc_ret = AHC_PlaybackClipCmd(AHC_PB_MOVIE_ROTATE, MovConfig.iRotate );
    return ahc_ret;
}

AHC_BOOL MovPlayback_Pause(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = AHC_PlaybackClipCmd(AHC_PB_MOVIE_PAUSE, 0);
    MovConfig.iState = MOV_STATE_PAUSE;

    return ahc_ret;
}

AHC_BOOL MovPlayback_Resume(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32  ulState;
    
    AHC_GetVideoPlayStopStatus(&ulState);
    if (ulState) {
        return ahc_ret;
    }

    AHC_SetVideoPlayStopStatus(AHC_VIDEO_PLAY);
    ahc_ret = AHC_PlaybackClipCmd(AHC_PB_MOVIE_RESUME, 0);
    MovConfig.iState = MOV_STATE_PLAY;

    return ahc_ret;
}

void MovPlaybackSetOutputDev(AHC_DISPLAY_OUTPUTPANEL Device)
{
    UINT16 Width, Height;

    switch(Device)
    {
        case AHC_DISPLAY_MAIN_LCD:
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH);
        break;

        case AHC_DISPLAY_HDMI:
            AHC_GetHdmiDisplayWidthHeight(&Width, &Height);
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height);
        break;

        case AHC_DISPLAY_NTSC_TV:
            AHC_GetNtscTvDisplayWidthHeight(&Width, &Height);
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height);
        break;

        case AHC_DISPLAY_PAL_TV:
            AHC_GetPalTvDisplayWidthHeight(&Width, &Height);			
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height);
        break;
        
        case AHC_DISPLAY_CCIR:
            AHC_GetPalTvDisplayWidthHeight(&Width, &Height);			
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOPLAYBACK, AHC_FALSE, AHC_FALSE, 0, 0, Width, Height);
        break;        
    }
}

#if 0
void ________Audio_Function_________(){ruturn;} //dummy
#endif

AUD_PLAYBACK_CONFIG *GetAudConfig(void)
{
    return &AudConfig;
}

#if WIFI_PORT == 0
AHC_BOOL GetAudCurrPlayTime(UINT32 *ultime)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32 ulCurtime;

    ahc_ret = AHC_GetAudioCurrentTime(&ulCurtime);

    *ultime = (AHC_TRUE == ahc_ret)?(ulCurtime):(0);

    return ahc_ret;
}
#endif

void AudPlaybackParamReset(void)
{
    AudConfig.iState  = AUD_STATE_STOP;
}

AHC_BOOL AudPlayback_Play(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = AHC_SetMode(AHC_MODE_PLAYBACK);

    if(AHC_TRUE == ahc_ret)
        AudConfig.iState = AUD_STATE_PLAY;

    return ahc_ret;
}

AHC_BOOL AudPlayback_Forward(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = AHC_PlayAudioCmd(AHC_AUDIO_PLAY_FAST_FORWARD, 1000);
    AudConfig.iState = AUD_STATE_FF;

    return ahc_ret;
}

AHC_BOOL AudPlayback_Backward(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = AHC_PlayAudioCmd(AHC_AUDIO_PLAY_FAST_FORWARD, -1000);
    AudConfig.iState = AUD_STATE_FF;

    return ahc_ret;
}

AHC_BOOL AudPlayback_NormalSpeed(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    extern void AudPBFunc_ResetPlaySpeed(void);
    AudPBFunc_ResetPlaySpeed();

    //ahc_ret = AHC_PlaybackClipCmd(AHC_PB_MOVIE_NORMAL_PLAY_SPEED, 0);
    AudConfig.iState = AUD_STATE_PLAY;

    return ahc_ret;
}

AHC_BOOL AudPlayback_Pause(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = AHC_PlayAudioCmd(AHC_AUDIO_PLAY_PAUSE, 0);
    AudConfig.iState = AUD_STATE_PAUSE;

    return ahc_ret;
}

AHC_BOOL AudPlayback_Resume(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = AHC_PlayAudioCmd(AHC_AUDIO_PLAY_RESUME, 0);
    AudConfig.iState = AUD_STATE_PLAY;

    return ahc_ret;
}

#if 0
void ________General_Function_________(){ruturn;} //dummy
#endif

AHC_BOOL MediaPlaybackConfig(UINT8 iSelect)
{
    UINT32       				CurObjIdx;
    UINT32       				SelectObjIdx;
    UINT32       				MaxDcfObj;
    AHC_DISPLAY_OUTPUTPANEL    	OutputDevice;
    UINT8                       FileType;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){ 
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);   
    }
    
    AHC_UF_GetCurrentIndex(&CurObjIdx);
    AHC_UF_GetTotalFileCount(&MaxDcfObj);

    if(CurObjIdx > MaxDcfObj)
    {
        AHC_UF_SetCurrentIndex(0);
        AHC_UF_GetCurrentIndex(&CurObjIdx);
    }

    if (MaxDcfObj == 0) {
        return AHC_FALSE;
    }

    //Get DcfInfo
    if( PLAYBACK_PREVIOUS == iSelect )
    {
        SelectObjIdx = ( CurObjIdx > 0 )?(CurObjIdx - 1):(MaxDcfObj - 1);
    }
    else if( PLAYBACK_NEXT == iSelect )
    {
        SelectObjIdx = ( CurObjIdx < MaxDcfObj - 1 )?(CurObjIdx + 1):(0);
    }
    else
    {
        SelectObjIdx = CurObjIdx;
    }

    AHC_UF_SetCurrentIndex(SelectObjIdx);
    AHC_UF_GetFileTypebyIndex(SelectObjIdx, &FileType);

    //Set display window
    if ( ( DCF_OBG_MOV == FileType ) ||
         ( DCF_OBG_MP4 == FileType ) ||
         ( DCF_OBG_AVI == FileType ) ||
         ( DCF_OBG_3GP == FileType ) ||
         ( DCF_OBG_TS  == FileType ) ||
         ( DCF_OBG_WMV == FileType ) )
    {
        AHC_GetDisplayOutputDev(&OutputDevice);

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
        MovConfig.iRotate  = AHC_DISPLAY_ROTATE_NO_ROTATE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        if(OutputDevice == AHC_DISPLAY_MAIN_LCD){
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
            MovConfig.iRotate  = AHC_DISPLAY_ROTATE_RIGHT_90;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
            MovConfig.iRotate  = AHC_DISPLAY_ROTATE_RIGHT_270;
#endif
        }
        else{
            MovConfig.iRotate  = AHC_DISPLAY_ROTATE_NO_ROTATE;       
        }
#endif

        AHC_SetParam(PARAM_ID_DISPLAY_ROTATE_ENABLE     , MovConfig.iRotate);
        AHC_SetParam(PARAM_ID_AUDIO_VOLUME              , 0x49);

        //Rogers@20110815: Patch for video display to HDMI
        MovPlaybackSetOutputDev(OutputDevice);

        iFileType = PLAYBACK_VIDEO_TYPE;
    }
    else if ( DCF_OBG_JPG == FileType )
    {
        JpgConfig.iRotate = AHC_DISPLAY_ROTATE_NO_ROTATE;

        AHC_SetParam(PARAM_ID_DISPLAY_ROTATE_ENABLE     ,JpgConfig.iRotate);

        //Rogers@20110811: Patch for Jpeg display to HDMI1080I
        AHC_GetDisplayOutputDev(&OutputDevice);
        JpgPlaybackSetOutputDev(OutputDevice);

        iFileType = PLAYBACK_IMAGE_TYPE;

        JpgConfig.iStartX    	= 0;
        JpgConfig.iStartY    	= 0;
        JpgConfig.iCurZoomLevel = 0;
    }
    else if ( ( DCF_OBG_MP3 == FileType ) ||
              ( DCF_OBG_WAV == FileType ) ||
              ( DCF_OBG_OGG == FileType ) ||
              ( DCF_OBG_WMA == FileType ) )
    {
        AHC_SetParam(PARAM_ID_AUDIO_VOLUME              ,0x49);
        iFileType = PLAYBACK_AUDIO_TYPE;
    }

    return AHC_TRUE;
}
