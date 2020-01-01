/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_message.h"
#include "ahc_display.h"
#include "ahc_preview.h"
#include "ahc_uf.h"
#include "ahc_usb.h"
#include "ahc_usbhost.h"
#include "ahc_media.h"
#include "ahc_video.h"
#include "ahc_stream.h"
#include "ahc_general_cardv.h"
#include "zoomcontrol.h"
#include "statevideofunc.h"
#include "MenuDrawCommon.h"
#include "drawstatevideofunc.h"
#include "ledcontrol.h"
#include "ahc_msgqueue.h"
#include "ahc_ptz.h"
#include "ahc_modectl.h"
#include "aihc_deletion.h"
#include "ahc_poweroff.h"
#include "ahc_charger.h"
#include "MenuStateModeSelectMenu.h"
#if (GSENSOR_CONNECT_ENABLE)
#include "GSensor_ctrl.h"
#endif
#if (GPS_CONNECT_ENABLE)
#include "gps_ctl.h"
#endif
#if (TOUCH_UART_FUNC_EN)
#include "Touch_Uart_ctrl.h"
#endif
#include "disp_drv.h"
#include "MenuDrawingFunc.h"
#include "MenuTouchButton.h"
#include "mmps_iva.h"
#include "mmps_fs.h"
#include "mmps_3gprecd.h"
#include "mmps_sensor.h"
#include "snr_cfg.h"
#include "ldc_cfg.h"
#if (SUPPORT_UVC_FUNC)
#include "pCam_api.h"
#endif
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "amnss_mmobjs.h"
#include "wlan.h"
#include "netapp.h"
#endif
#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
#include "3rd_speech.h"
#include "mmpd_audio.h"
#endif
#if (ENABLE_ADAS_LDWS)
#include "ldws_cfg.h"
#include "mmps_aui.h"
#include "mmps_adas.h"
#endif
#include "hdr_cfg.h"
#include "ahc_sensor.h"
#include "driving_safety.h"

#if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)
#include "mmpf_usbh_uvc.h"
#endif

#include "ahc_adas.h"
#include "parkingmodectrl.h"

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE == 1)
#include "mmpf_usbuvc.h"
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/

/* Lock File functions */
//  Export functions
AHC_BOOL VideoFunc_LockFileEnabled(void);
//  Internal Functions & Variables
static AHC_BOOL     _bLockVRFile = AHC_FALSE;
static int          _nLockType;
//UINT32              ulCurLockTime ;

static void EnableLockFile(AHC_BOOL bEnable, int type);
static void LockFileTypeChange(int arg);
/* Lock File functions */

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define PARKING_RECORD_FORCE_20SEC          (0)

#define STORAGE_MIN_SIZE                    (2*1024*1024)
#define PRE_RECORD_STORAGE_MIN_SIZE         (4*1024*1024)
#define VIDEO_TIMER_UNIT                    (10) //unit :ms
#define TICKS_PER_SECOND                    (1000)
#define TICKS_PER_MINUTE                    (60 * 1000)

#define MOTION_DETECTION_STABLE_TIME        ((SUPPORT_PARKINGMODE == PARKINGMODE_NONE) ? 10 : 2)        // second // This time is used to wait AE stable after enter Pre-recording mode
#define MOTION_DETECTION_STABLE_TIME2       (0.5)//unit=SEC after the first time

#define NIGHT_MODE_FPS                      (4)

/*===========================================================================
 * Global variable
 *===========================================================================*/

MOVIESIZE_SETTING           m_eUiVideoRecResol      = MOVIE_SIZE_NUM;
static AHC_BOOL             m_bUiVideoRecording     = AHC_FALSE;
UINT8                       bVideoPreRecordStatus   = AHC_FALSE;
AHC_BOOL                    bAudioRecording         = AHC_FALSE;
UINT32                      VideoTimerID            = AHC_OS_CREATE_TMR_INT_ERR;
UINT32                      VideoCounter            = 0;
static UINT32               m_u32UiRecordTimeOffset = 0;
AHC_BOOL                    bShowHdmiWMSG           = AHC_TRUE;
AHC_BOOL                    bShowTvWMSG             = AHC_TRUE;

AHC_BOOL                    bMuteRecord             = AHC_FALSE;
AHC_BOOL                    bDisableVideoPreRecord  = AHC_FALSE;
UINT32                      m_uiSlowMediaCBCnt      = 0;
AHC_BOOL                    bNightMode              = AHC_FALSE;
AHC_BOOL                    bGPS_PageExist          = AHC_FALSE;

#if (LIMIT_MAX_LOCK_FILE_NUM)
UINT32                      m_ulLockFileNum         = 0;
UINT32                      m_ulLockEventNum        = 0;
#endif

#if (LIMIT_MAX_LOCK_FILE_TIME)
static UINT32               m_u32UiVRTotalTime      = 0;
#endif

#if (VIDEO_DIGIT_ZOOM_EN==1)
static AHC_BOOL             bZoomStop               = AHC_TRUE;
#endif

#if (GSENSOR_CONNECT_ENABLE || GPS_CONNECT_ENABLE)
static UINT32               ulCounterForGpsGsnrUpdate;
#endif

#if (MOTION_DETECTION_EN)
AHC_BOOL                    m_ubInRemindTime        = AHC_FALSE;
#ifdef CFG_REC_CUS_VMD_REMIND_TIME
UINT32                      m_ulVMDRemindTime       = CFG_REC_CUS_VMD_REMIND_TIME;
#else
UINT32                      m_ulVMDRemindTime       = 10;
#endif
UINT32                      m_ulVMDCloseBacklightTime  = 41;
AHC_BOOL                    m_ubVMDStart            = AHC_FALSE;
AHC_BOOL                    m_ulVMDCancel           = AHC_FALSE;
UINT32                      m_ulVMDStableCnt        = 0;  // This counter is used to wait AE stable after enter Pre-recording mode
static UINT32               m_ulVMDStopCnt          = 0;
#endif
#ifdef CFG_ENABLE_VIDEO_LASER_LED
UINT32                      m_ulLaserTime           = 10*10; //10s
AHC_BOOL                    m_ubLaserStart          = AHC_FALSE;
static UINT32               m_ubLaserStop           = AHC_FALSE;
#endif

#if (VR_PREENCODE_EN)
AHC_BOOL                    m_ubPreRecording        = AHC_FALSE;
AHC_BOOL                    m_ubPreEncodeEn         = AHC_FALSE;
#endif

#if (SUPPORT_TOUCH_PANEL)
AHC_BOOL                    m_ubShowVRTouchPage     = AHC_FALSE;
#endif

#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
UINT32                      m_ulGSNRRecStopCnt      = POWER_ON_GSNR_MOVIE_TIME * 10;
#endif

AHC_BOOL                    m_ubParkingModeRecTrigger = AHC_FALSE;

UINT32                      m_ulEventPreRecordTime = 0;
UINT32                      m_ulEventHappenTime = 0;

AHC_BOOL                    m_bCurrentTimeLessThanPreRecord = AHC_FALSE;
#if (ENABLE_ADAS_LDWS)
UINT32                      m_ulLDWSWarn = 0;
#endif
#if (ENABLE_ADAS_FCWS)
UINT32                      m_ulFCWSWarn = 0;
#endif
#if (ENABLE_ADAS_SAG)
UINT32                      m_ulSAGWarn = 0;
#endif

static UINT8                gbWinExchangedCnt = F_LARGE_R_SMALL;

#if (UPDATE_UI_USE_MULTI_TASK)
AHC_BOOL                    m_ubUpdateUiByOtherTask = AHC_FALSE;
#endif
AHC_BOOL                    gbVideoInSubMode = AHC_FALSE;

AHC_BOOL                    gbVideoTimerEventBusy = AHC_FALSE;

static AHC_BOOL             m_bFirstDrawTimeStamp = AHC_TRUE;

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern AHC_BOOL             bForce_PowerOff;
#if (AUTO_HIDE_OSD_EN)
extern AHC_BOOL             m_ubHideOSD;
extern UINT32               m_ulOSDCounter;
#endif

#if (MOTION_DETECTION_EN)
extern AHC_BOOL             m_ubMotionDtcEn;
#endif

#if (GPS_CONNECT_ENABLE)
extern GPS_ATTRIBUTE        gGPS_Attribute;
#endif

#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
extern AHC_BOOL             ubGsnrPwrOnActStart;
extern AHC_BOOL             m_ubGsnrIsObjMove;
#endif

#if (GSENSOR_CONNECT_ENABLE)
extern AHC_BOOL             m_ubGsnrIsObjMove;
#endif

extern AHC_BOOL             gbAhcDbgBrk;

#if (AHC_SHAREENC_SUPPORT)
extern AHC_BOOL             m_bAhcFirstShareFile;
extern MMP_ULONG            m_ulAhcSharePreEncTime;
#endif

extern MMP_BOOL             g_bDrawUnfix;//use to draw GPS unfix message onetime.
#if defined(PCAM_UVC_MIX_MODE_ENABLE) && PCAM_UVC_MIX_MODE_ENABLE
extern AHC_BOOL             m_ubFormatSDing;
#endif

/*===========================================================================
 * Extern Function
 *===========================================================================*/

#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
extern UINT32 AHC_GSNR_PWROn_MovieTimeReset(void);
#endif

AHC_BOOL VideoFunc_GetRecordStatus(void);

/*===========================================================================
 * Main body
 *===========================================================================*/

#if (ENABLE_ADAS_LDWS)
void ResetLDWSCounter(void)
{
    m_ulLDWSWarn = 0;
}
#endif

#if (ENABLE_ADAS_FCWS)
void ResetFCWSCounter(void)
{
    m_ulFCWSWarn = 0;
}
#endif

#if (ENABLE_ADAS_SAG)
void ResetSAGCounter(void)
{
    m_ulSAGWarn = 0;
}
#endif

void VideoTimer_Event_Busy(AHC_BOOL bBusy)
{
    gbVideoTimerEventBusy = bBusy;
}

AHC_BOOL VideoTimer_Event_IsBusy(void)
{
    return gbVideoTimerEventBusy;
}

void VideoTimer_ISR_Fast(void *tmr, void *arg)
{
    AHC_RTC_TIME    stRtcTime;
    static UINT32   _kt = 0;
    UINT8           u8ForceUpdate = 0;

    AHC_RTC_GetTime(&stRtcTime);

    #if defined(INFO_ISP_MSG_ON_PNL)&&(INFO_ISP_MSG_ON_PNL)
    u8ForceUpdate = ShowOnPnl_ForceUpdateGetFlag();
    #endif

    if (m_bFirstDrawTimeStamp || (_kt != stRtcTime.uwSecond) || u8ForceUpdate) {
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_TIMESTAMP_UPDATE, 0);
        _kt = stRtcTime.uwSecond;
        m_bFirstDrawTimeStamp = AHC_FALSE;
    }
}

void VideoTimerMonitor(void)
{
    MMP_ULONG   star;
    static MMP_ULONG    last=0,cnt=0,tt=0;

    MMPF_OS_GetTimeMs(&star);
    cnt++;

    if (star >= last)
        tt += (star-last);
    else
        tt += (star+0xFFFFFFFF-last);

    if (cnt == 100) {//10sec
        //AHC_DBG_MSG(1, "GPS UPDATE send every msg%dms\r\n",tt/cnt);
        cnt = 0;
        tt = 0;
    }

    last = star;
}

void VideoTimer_ISR_Slow(void *tmr, void *arg)
{
#if (ENABLE_ADAS_LDWS)
    if (m_ulLDWSWarn == 1) {
        m_ulLDWSWarn = 0;
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_LDWS_STOP, 0);
    }
    else if (m_ulLDWSWarn > 0) {
        m_ulLDWSWarn--;
    }
#endif
#if (ENABLE_ADAS_FCWS)
    if (m_ulFCWSWarn == 1) {
        m_ulFCWSWarn = 0;
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_FCWS_STOP, 0);
    }
    else if (m_ulFCWSWarn > 0) {
        m_ulFCWSWarn--;
    }
#endif
#if (ENABLE_ADAS_SAG)
    if (m_ulSAGWarn == 1) {
        m_ulSAGWarn = 0;
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_SAG_STOP, 0);
    }
    else if (m_ulSAGWarn > 0){
        m_ulSAGWarn--;
    }
#endif

    #ifdef CFG_ENABLE_VIDEO_LASER_LED
    if((!m_ubLaserStart)&&(VideoFunc_GetRecordStatus()))
    {
        AHC_DBG_MSG(1, "m_ubLaserStart \r\n");
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_FUNC2_LPRESS, 0);
        m_ubLaserStart = AHC_TRUE;
    }
    else if((VideoFunc_GetRecordStatus())&&(m_ulLaserTime>0)&&(m_ubLaserStart))
    {
        m_ulLaserTime--;
        if(m_ulLaserTime==0)
        {
            m_ubLaserStop = AHC_TRUE;
            AHC_DBG_MSG(1, "m_ubLaserStop \r\n");
            AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_FUNC2_LPRESS, 0);
        }
    }
    #endif

    #if defined(CFG_WIFI_TIMEOUT_OFF) && defined(WIFI_PORT) && (WIFI_PORT == 1)
    {
        static  MMP_USHORT cnt;

        if ((nhw_get_status() != 0) && (NETAPP_NET_STATUS_NONE != nhw_get_status()))
        {
            if (AHC_CheckWiFiOnOffInterval(ulWiFiSwitchToggleInterval) == 0)
            {
                if (AHC_Get_WiFi_Streaming_Status())
                {
                    cnt = 0;
                }
                else
                {
                    cnt++;
                    if (cnt>(10*3*60))  //100*10ms
                    {  // TurnOffWiFiModule
                        //AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_REC_REL, 0);  // TBD
                        cnt = 0;
                    }
                }
            }
        }
        else
        {
            cnt = 0;
        }
    }
    #endif

    if( VideoCounter == 0)
    {
        #ifdef CFG_REC_CUS_EVENT_PERIOD //may be defined in config_xxx.h, must not == 0
        VideoCounter = CFG_REC_CUS_EVENT_PERIOD;
        #else
        VideoCounter = 5;
        #endif
        #if (UPDATE_UI_USE_MULTI_TASK)
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
        #endif
        #if (TOUCH_UART_FUNC_EN)
        #if (DTV_UART_SEND_LDWS)
        if(DTV_UART_Get_LDWS())
            AHC_OS_SetFlags(UartCtrlFlag, Touch_Uart_FLAG_SETPACK, AHC_OS_FLAG_SET);
        #endif //#if (DTV_UART_SEND_LDWS)

        #if (DTV_UART_SEND_FCWS)
        if(DTV_UART_Get_FCWS())
            AHC_OS_SetFlags(UartCtrlFlag, Touch_Uart_FLAG_SETPACK, AHC_OS_FLAG_SET);
        #endif  //#if (DTV_UART_SEND_FCWS)
        #endif  //#if (TOUCH_UART_FUNC_EN)
        #ifdef VMD_EN_BY_CHARGER_OUT
        if(m_ubMotionDtcEn)
        {
            AutoPowerOffCounterReset();
            LCDPowerSaveCounterReset();
            VideoPowerOffCounterReset();
        }
        #endif
    }

    VideoCounter--;

#if((SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN) && \
    (GSNR_PWRON_REC_BY && (GSNR_PWRON_REC_BY_SHAKED || GSNR_PWRON_REC_BY_VMD)))
    if(ubGsnrPwrOnActStart)
    {
        LCDPowerSaveCounterReset();
        VideoPowerOffCounterReset();
        if(m_ulGSNRRecStopCnt && VideoFunc_GetRecordStatus())
        {
            m_ulGSNRRecStopCnt--;

            if(m_ulGSNRRecStopCnt==0)
            {
                if(POWER_ON_GSNR_IDLE_TIME == 0)
                {
                    bForce_PowerOff = AHC_TRUE;
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_POWER_OFF, 0);
                    m_ulGSNRRecStopCnt = 0;
                }
                else
                {
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_VIDEO_RECORD, EVENT_VRCB_MOTION_DTC);
                    AutoPowerOffCounterReset();
                }
            }
        }
    }
    else
#endif
    {
        #if (MOTION_DETECTION_EN) && (VMD_ACTION & VMD_RECORD_VIDEO)
        if (m_ulVMDStopCnt && m_ubVMDStart)
        {
            m_ulVMDStopCnt--;

            if (m_ulVMDStopCnt == 0) {
                // Stop Video Record in VMD mode.
                // Please make sure EVENT - BUTTON_REC_PRESS is to stop video recording
                //AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_VIDEO_RECORD, EVENT_VRCB_MOTION_DTC);
            }
        }
        #endif

        #if (MOTION_DETECTION_EN)
        if( m_ulVMDStableCnt > 0 )
        {
            m_ulVMDStableCnt--;
            if( m_ulVMDStableCnt == 0 )
            {
                m_ubVMDStart = AHC_TRUE; // Really start to detect motions
            }
        }
        #endif
    }

    #if ( ((GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO))     || \
          ((GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)) )
    if((VideoFunc_GetRecordStatus() || uiGetParkingModeEnable() == AHC_TRUE || AHC_VIDEO_IsEmergRecStarted() == AHC_TRUE))
    {
        #if (GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO)
        if( 0 == (ulCounterForGpsGsnrUpdate % (10/(gGPS_Attribute.ubStoreFreq))))
            AHC_GPS_SetCurInfo();
        #endif
        #if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)
        if( 0 == (ulCounterForGpsGsnrUpdate % (10/(AHC_Gsensor_GetAttributeAddr()->ubStoreFreq))))
            AHC_Gsensor_SetCurInfo();
        #endif
        #if (GPS_CONNECT_ENABLE || GSENSOR_CONNECT_ENABLE)
        ulCounterForGpsGsnrUpdate++;
        #endif
    }
    else
    {
        ulCounterForGpsGsnrUpdate = 0;
    }
    #endif
}

void VideoTimer_ISR(void *tmr, void *arg)
{
    static UINT32 u32Fast2Slow = 0;

    VideoTimer_ISR_Fast(tmr, arg); //10 ms

    if((u32Fast2Slow % 10) == 0) {
        VideoTimer_ISR_Slow(tmr, arg); //100 ms
        u32Fast2Slow = 0;
    }

    u32Fast2Slow++;
}

AHC_BOOL VideoTimer_Start(UINT32 ulTime)
{
    if (VideoTimerID == AHC_OS_CREATE_TMR_INT_ERR) {
        VideoCounter = 0;
        VideoTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, VideoTimer_ISR, (void*)NULL );
        //AHC_DBG_MSG(1, FG_GREEN("VideoTimer_Start: VideoTimerID =0x%X\r\n"), VideoTimerID);

        if (AHC_OS_CREATE_TMR_INT_ERR == VideoTimerID) {
            AHC_DBG_MSG(1, FG_RED("Start Video Timer fail - 0x%X!!!")"\r\n", VideoTimerID);
            return AHC_FALSE;
        }
    }

    #ifdef CFG_CUS_VIDEO_TIMER_START
    CFG_CUS_VIDEO_TIMER_START();
    #endif

    m_bFirstDrawTimeStamp = AHC_TRUE;

    return AHC_TRUE;
}

AHC_BOOL VideoTimer_Stop(void)
{
    UINT8    ret = 0;
    UINT32   ulTimeout = 0x1000000;
    AHC_BOOL bVideoTimerBusy = AHC_FALSE;

    #ifdef CFG_CUS_VIDEO_TIMER_STOP
    CFG_CUS_VIDEO_TIMER_STOP();
    #endif

    if (VideoTimerID != AHC_OS_CREATE_TMR_INT_ERR) {

        AHC_DBG_MSG(1, FG_GREEN("VideoTimer_Stop: VideoTimerID =0x%X\r\n"), VideoTimerID);

        ret = AHC_OS_StopTimer( VideoTimerID, AHC_OS_TMR_OPT_PERIODIC );
        VideoTimerID = AHC_OS_CREATE_TMR_INT_ERR;

        do {
            bVideoTimerBusy = VideoTimer_Event_IsBusy();
        } while((AHC_TRUE == bVideoTimerBusy) && (--ulTimeout > 0));

        AHC_DBG_MSG(1, FG_RED("\r\n\r\nStop video timer wait time:%d\r\n"), 0x1000000-bVideoTimerBusy);

        if (0 == ulTimeout) {
            AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0);
        }

        if (ret) {
            AHC_DBG_MSG(1, FG_RED("Stop Video Timer fail !!!")"\r\n");
            return AHC_FALSE;
        }
    }

    return AHC_TRUE;
}

void VideoFunc_SetRecordStatus(AHC_BOOL bRecding)
{
    m_bUiVideoRecording = bRecding;
}

AHC_BOOL VideoFunc_GetRecordStatus(void)
{
    return m_bUiVideoRecording;
}

//------------------------------------------------------------------------------
//  Function    : VideoFunc_SetAttribute
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL VideoFunc_SetAttribute(void)
{
    UINT8       u8ZoomRatio = 4;
    AHC_BOOL    ahcRet = AHC_TRUE;

    AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8 *) VIDEO_DEFAULT_FLIE_FREECHAR);

    VideoFunc_PresetPrmSnrMode(MenuSettingConfig()->uiMOVSize);
    VideoFunc_SetResolution(MenuSettingConfig()->uiMOVSize);
    VideoFunc_PresetFrameRate(MenuSettingConfig()->uiMOVSize);

    AHC_SetPreviewZoomConfig(ZoomCtrl_GetVideoDigitalZoomMax(), (UINT8)u8ZoomRatio);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : VideoFunc_SetPreviewWindow
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL VideoFunc_SetPreviewWindow(AHC_BOOL bPreSet)
{
    UINT8       bMirror = SCD_CAM_PREVIEW_MIRROR;
    UINT16      u16DispW = 0, u16DispH = 0;
    UINT16      u16PipW = 0, u16PipH = 0;
    AHC_BOOL    ahcRet = AHC_TRUE;

    u16DispW = RTNA_LCD_GetAttr()->usPanelW;
    u16DispH = RTNA_LCD_GetAttr()->usPanelH;

    u16PipW = PIP_WIDTH;
    u16PipH = PIP_HEIGHT;

    #if (ENABLE_SET_YUV_ATTRIBUTE)
    MMPS_Display_SetYuvAttribute(YUV_U2U, YUV_V2U, YUV_U2V, YUV_V2V, YUV_YGAIN, YUV_YOFFSET);
    #endif

    #if (AHC_SHAREENC_SUPPORT)
    AHC_VIDEO_SetShareRecdResIdx(VIDRECD_RESOL_640x480);
    #endif

    if (MMP_IsPrmCamExist()) {
        AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, AHC_FALSE, 0, 0, u16DispW, u16DispH);
    }

    if (MMP_IsUSBCamExist()) {
        AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_UVC, AHC_TRUE, bMirror, 0, 0, u16PipW, u16PipH);
    }

    if ((CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) ||
        (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR))  ||
        (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))) {
        AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_SCD, AHC_TRUE, bMirror, 0, 0, u16PipW, u16PipH);
    }

    return ahcRet;
}

AHC_BOOL VideoFunc_IsShareRecordStarted(void)
{
    #if (AHC_SHAREENC_SUPPORT)
    return AHC_VIDEO_IsShareRecdStarted();
    #endif
    return AHC_FALSE;
}

AHC_BOOL VideoFunc_StartShareRecord(void)
{
    AHC_BOOL ret = AHC_TRUE;

#if (AHC_SHAREENC_SUPPORT)
    UINT32 ulCurRecordedTime = 0;

    AHC_VIDEO_GetCurRecordingTime(&ulCurRecordedTime);

    AHC_DBG_MSG(1, FG_PURPLE("VideoFunc_StartShareRecord Cur [%d] ms\r\n"), ulCurRecordedTime);

    DBG_AutoTestPrint(ATEST_ACT_1CLICKSHARE_0x000A, ATEST_STS_START_0x0001, 0, 0, gbAhcDbgBrk);

    #if (GPS_CONNECT_ENABLE && (GPS_FUNC & FUNC_VIDEOSTREM_INFO))
    AHC_GPS_SetSHAREIndex();
    #endif
    #if (GSENSOR_CONNECT_ENABLE && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO))
    AHC_Gsensor_SetSHAREIndex();
    #endif

    ret = AHC_VIDEO_StartShareRecord();
#endif
    return ret;
}

AHC_BOOL VideoFunc_StopShareRecord(void)
{
#if (AHC_SHAREENC_SUPPORT)
    return AHC_VIDEO_StopShareRecord();
#else
    return AHC_TRUE;
#endif
}

AHC_BOOL VideoFunc_PreRecordStatus(void)
{
#if (VR_PREENCODE_EN)
    return m_ubPreRecording;
#else
    return AHC_FALSE;
#endif
}

AHC_BOOL VideoFunc_GPSPageStatus(void)
{
    return bGPS_PageExist;
}

UINT32 VideoFunc_GetRecordTimeOffset(void)
{
    return m_u32UiRecordTimeOffset;
}

//------------------------------------------------------------------------------
//  Function    : VideoFunc_SetResolution
//  Description :
//------------------------------------------------------------------------------
void VideoFunc_SetResolution(MOVIESIZE_SETTING eResolution)
{
    m_eUiVideoRecResol = eResolution;

    switch(m_eUiVideoRecResol)
    {
        #if (MENU_MOVIE_SIZE_4K_24P_EN)
        case MOVIE_SIZE_4K_24P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 3200, 1808/*1800*/);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1440_30P_EN)
        case MOVIE_SIZE_1440_30P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 2560, 1440);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_30P_EN)
        case MOVIE_SIZE_SHD_30P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 2304, 1296);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_25P_EN)
        case MOVIE_SIZE_SHD_25P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 2304, 1296);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_24P_EN)
        case MOVIE_SIZE_SHD_24P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 2304, 1296);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_60P_EN)
        case MOVIE_SIZE_1080_60P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1920, 1080);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_24P_EN)
        case MOVIE_SIZE_1080_24P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1920, 1080);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_EN)
        case MOVIE_SIZE_1080P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1920, 1080);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_30_HDR_EN) || (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN)
        case MOVIE_SIZE_1080_30P_HDR:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1920, 1080);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_900P_30P_EN)
        case MOVIE_SIZE_900P_30P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1600, 912);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_960P_30P_EN)
        case MOVIE_SIZE_960P_30P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1280, 960);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720P_EN)
        case MOVIE_SIZE_720P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1280, 720);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720_60P_EN)
        case MOVIE_SIZE_720_60P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1280, 720);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720_24P_EN)
        case MOVIE_SIZE_720_24P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1280, 720);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA30P_EN)
        case MOVIE_SIZE_VGA_30P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 640, 480);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA120P_EN)
        case MOVIE_SIZE_VGA_120P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 640, 480);
        break;
        #endif
        case MOVIE_SIZE_360_30P:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 640, 368);
        break;
        default:
            AHC_VIDEO_SetRecdResol(gsAhcPrmSensor, 1280, 720);
        break;
    }
}

//------------------------------------------------------------------------------
//  Function    : VideoFunc_PresetPrmSnrMode
//  Description :
//------------------------------------------------------------------------------
void VideoFunc_PresetPrmSnrMode(MOVIESIZE_SETTING eResolution)
{
    AHC_BOOL ahc_ret = AHC_FALSE;

    switch(eResolution)
    {
        #if (MENU_MOVIE_SIZE_4K_24P_EN)
        case MOVIE_SIZE_4K_24P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_4K2K_24P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1440_30P_EN)
        case MOVIE_SIZE_1440_30P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_1440_30P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_30P_EN)
        case MOVIE_SIZE_SHD_30P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_SUPER_HD_30P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_25P_EN)
        case MOVIE_SIZE_SHD_25P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_SUPER_HD_25P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_24P_EN)
        case MOVIE_SIZE_SHD_24P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_SUPER_HD_24P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_60P_EN)
        case MOVIE_SIZE_1080_60P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_60P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_EN)
        case MOVIE_SIZE_1080P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_30_HDR_EN)
        case MOVIE_SIZE_1080_30P_HDR:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION_HDR);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN)
        case MOVIE_SIZE_1080_30P_HDR:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION_COMBINED_HDR);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_24P_EN)
        case MOVIE_SIZE_1080_24P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_24P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_900P_30P_EN)
        case MOVIE_SIZE_900P_30P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_1600x900_30P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_960P_30P_EN)
        case MOVIE_SIZE_960P_30P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_4TO3_1D2M_30P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720P_EN)
        case MOVIE_SIZE_720P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_HD_30P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720_60P_EN)
        case MOVIE_SIZE_720_60P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_HD_60P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720_24P_EN)
        case MOVIE_SIZE_720_24P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_HD_24P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA30P_EN)
        case MOVIE_SIZE_VGA_30P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_4TO3_VGA_30P_RESOLUTION);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA120P_EN)
        case MOVIE_SIZE_VGA_120P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_VGA_120P_RESOLUTION);
        break;
        #endif
        case MOVIE_SIZE_360_30P:
            ahc_ret = AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_VGA_30P_RESOLUTION);
        break;
        default:
            AHC_DBG_MSG(1,  FG_RED("VideoFunc_PresetPrmSnrMode: Unsupported resolution - %d\r\n"), eResolution);
        break;
    }
}

//------------------------------------------------------------------------------
//  Function    : VideoFunc_PresetFrameRate
//  Description :
//------------------------------------------------------------------------------
void VideoFunc_PresetFrameRate(MOVIESIZE_SETTING eResolution)
{
    AHC_BOOL ahc_ret = AHC_FALSE;

    switch(eResolution)
    {
        #if (MENU_MOVIE_SIZE_4K_24P_EN)
        case MOVIE_SIZE_4K_24P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 24);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1440_30P_EN)
        case MOVIE_SIZE_1440_30P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_30P_EN)
        case MOVIE_SIZE_SHD_30P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_25P_EN)
        case MOVIE_SIZE_SHD_25P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 25);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_24P_EN)
        case MOVIE_SIZE_SHD_24P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 24);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_60P_EN)
        case MOVIE_SIZE_1080_60P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 60);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_24P_EN)
        case MOVIE_SIZE_1080_24P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 24);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_EN)
        case MOVIE_SIZE_1080P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_30_HDR_EN) || (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN)
        case MOVIE_SIZE_1080_30P_HDR:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_900P_30P_EN)
        case MOVIE_SIZE_900P_30P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_960P_30P_EN)
        case MOVIE_SIZE_960P_30P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720P_EN)
        case MOVIE_SIZE_720P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720_60P_EN)
        case MOVIE_SIZE_720_60P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 60);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_720_24P_EN)
        case MOVIE_SIZE_720_24P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 24);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA30P_EN)
        case MOVIE_SIZE_VGA_30P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA120P_EN)
        case MOVIE_SIZE_VGA_120P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 120);
        break;
        #endif
        case MOVIE_SIZE_360_30P:
            ahc_ret = AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, 30);
        break;
        default:
            AHC_DBG_MSG(1,  FG_RED("VideoFunc_PresetFrameRate: Unsupported resolution - %d\n"), eResolution);
        break;
    }
}

AHC_BOOL VideoFunc_PreRecord(void)
{
    AHC_BOOL ahcRet = AHC_FALSE;

    if (AHC_MODE_RECORD_PREVIEW != AHC_GetAhcSysMode()) {

        if (AHC_MODE_RECORD_PRERECD == AHC_GetAhcSysMode()) {
            return AHC_TRUE;
        }
        else {
            AHC_DBG_ERR(1, "VideoFunc_PreRecord Fail-1 [%x]\r\n", AHC_GetAhcSysMode());
            return AHC_FALSE;
        }
    }

    AHC_DBG_MSG(1, FG_RED(" ## Enter Parking PreEncode\r\n"));

    {
        UINT32 Param, FrameRate, ulTimeResol;

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &Param);
        FrameRate = AHC_VIDEO_GetVideoRealFpsX1000(Param);

        ulTimeResol = FrameRate;

        AHC_VIDEO_SetSlowMotionFPS(AHC_FALSE, AHC_VIDRECD_TIME_INCREMENT_BASE, ulTimeResol);
    }

#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN == 1)
    {
        UINT32 Param, FrameRate, ulTimeResol;

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &Param);
        FrameRate = AHC_VIDEO_GetVideoRealFpsX1000(Param);

        ulTimeResol = FrameRate;

        AHC_VIDEO_SetTimeLapseFPS(AHC_FALSE, AHC_VIDRECD_TIME_INCREMENT_BASE, ulTimeResol);
    }
#endif

    if (MenuSettingConfig()->uiMOVSoundRecord != MOVIE_SOUND_RECORD_ON) {
        AHC_VIDEO_SetRecordModeAudioOn(AHC_FALSE);
    }
    else {
        AHC_VIDEO_SetRecordModeAudioOn(AHC_TRUE);
    }

    ahcRet = AHC_SetMode(AHC_MODE_RECORD_PRERECD);
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return ahcRet;}

#if (AHC_SHAREENC_SUPPORT)
    if (m_ulAhcSharePreEncTime == 0) {
        m_ulAhcSharePreEncTime = DUAL_RECORD_WRITE_PRETIME*1000 + EM_VR_TIME_LIMIT_OFFSET;
        AHC_DBG_MSG(1, "[%s, %d] Share Pre %d ms.\r\n", __FUNCTION__, __LINE__, m_ulAhcSharePreEncTime);
    }
    AHC_VIDEO_StartSharePreRecord();
#endif

    return ahcRet;
}

VIDEO_RECORD_STATUS VideoFunc_Record(void)
{
    AHC_BOOL    ahc_ret         = AHC_TRUE;
    UINT64      u64FreeSpace     = 0;
    UINT8       Hour, Min, Sec;
    UINT32      u32AudBitRate    = 128000;//128K
    UINT32      u32VidBitRate;
    UINT32      u32Timelimit     = AHC_VIDEO_GetRecTimeLimitEx();
    UINT64      u64SpaceNeeded   = 0;
    UINT32      MaxDcfObj       = 0;
    UINT32      ulResvSize      = 0;
    UINT32      ulPreRecordedTime = 0;
    AHC_AUDIO_FORMAT aformat;
    AHC_BOOL    bEnableSlowMotion = AHC_FALSE;
    AHC_BOOL    bTimeLapseEnable  = AHC_FALSE;

    if (AHC_FALSE == AHC_SDMMC_IsSD1MountDCF())
    {
        AHC_DBG_MSG(1, FG_RED("No Card: Mount Fail !!!!!!\r\n"));
        return VIDEO_REC_NO_SD_CARD;
    }

    AHC_Media_GetFreeSpace(&u64FreeSpace);
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &u32VidBitRate);

    DBG_AutoTestPrint(ATEST_ACT_REC_0x0001, ATEST_STS_START_0x0001, 0, 0, gbAhcDbgBrk);
    DBG_AutoTestPrint(ATEST_ACT_REC_0x0001, ATEST_STS_CYCLE_TIME_0x0005, (u32Timelimit & 0xFFFF0000)>>16, (u32Timelimit & 0xFFFF), gbAhcDbgBrk);
    DBG_AutoTestPrint(ATEST_ACT_REC_0x0001, ATEST_STS_BIT_RATE_0x0007, (u32VidBitRate & 0xFFFF0000)>>16, (u32VidBitRate & 0xFFFF), gbAhcDbgBrk);

    if (u32Timelimit == NON_CYCLING_TIME_LIMIT)
    {
        // 0 to get time for current setting of bitrate
        AHC_VIDEO_AvailableRecTimeEx(0, &Hour, &Min, &Sec);

        if (Hour == 0 && Min == 0 && Sec <= 2)
        {
            AHC_DBG_MSG(1, FG_RED("Space is not enough for Non-Cycling recording, Card Full!\r\n"));
            return VIDEO_REC_CARD_FULL;
        }
    }
    else
    {
        /* For Cyclic-Record Space Guaranty */
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
        UINT32 u32VRTimelapse = 0;       // Off

        if ((AHC_Menu_SettingGetCB(COMMON_KEY_VR_TIMELAPSE, &u32VRTimelapse) == AHC_TRUE) && (u32VRTimelapse != PRJ_VR_TIMELAPSE_OFF)){
            UINT32      Framerate, Frate;
            AHC_DBG_MSG(1, " TimeLapse record.....\r\n");

            AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &Frate);
            Framerate = AHC_VIDEO_GetVideoRealFpsX1000(Frate) / AHC_VIDRECD_TIME_INCREMENT_BASE;
            AHC_VIDEO_GetTimeLapseBitrate(Framerate, u32VRTimelapse, &u32VidBitRate, &u32AudBitRate);
        }
        else
#endif
        {
            if (MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_OFF)
                u32AudBitRate = 0;
        }

#if (FS_FORMAT_FREE_ENABLE == 0)
        #if (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_3)
        if (uiGetParkingModeEnable() == AHC_FALSE)
        {
            if (AHC_Deletion_Romove(AHC_FALSE) == AHC_FALSE)
                return VIDEO_REC_SEAMLESS_ERROR;
        }
        else
        {
            if (AHC_Deletion_RemoveEx(DCF_DB_TYPE_DB1_PARKING, AHC_VIDEO_GetRecTimeLimitEx()) == AHC_FALSE)
            {
                if (AHC_Deletion_RemoveEx(DCF_DB_TYPE_DB1_PARKING, AHC_VIDEO_GetRecTimeLimitEx()) == AHC_FALSE)
                    return VIDEO_REC_SEAMLESS_ERROR;
            }
        }
        #else
        {
            #if (DELETION_BY_FILE_NUM)
            {
                UINT32 uiFileCount;
                DCF_DB_TYPE sCurDB;
                DCF_DB_TYPE eDBType;

                sCurDB = AHC_UF_GetDB();

                #if (DCF_DB_COUNT >= 2)
                if (uiGetParkingModeEnable() == AHC_TRUE)
                {
                    eDBType = DCF_DB_TYPE_DB1_PARKING;
                }
                else
                #endif
                {
                    eDBType = DCF_DB_TYPE_DB0_NORMAL;
                }

                AHC_UF_SelectDB(eDBType);
                AHC_UF_GetTotalFileCount(&uiFileCount);

                if(1)// (uiFileCount >= AHC_UF_GetFileTH(eDBType))
                {
                    if (AHC_Deletion_RemoveEx(eDBType, AHC_VIDEO_GetRecTimeLimitEx()) == AHC_FALSE)
                    {
                        AHC_DBG_MSG(1, FG_RED("AHC_Deletion_Romove Error\r\n"));
                        return AHC_FALSE;
                    }
                }
                AHC_UF_SelectDB(sCurDB);
            }
            #endif //#if (DELETION_BY_FILE_NUM)

            AHC_VIDEO_GetRecStorageSpaceNeed(u32VidBitRate, u32AudBitRate, u32Timelimit, &u64SpaceNeeded);

            if (u64FreeSpace < u64SpaceNeeded)
            {
                MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);

                if (MaxDcfObj == 0)
                {
                    AHC_DBG_MSG(1, "--E-- Space is not enough for cycle recording !!!\r\nPlease Clean SD card!\r\n");
                    return VIDEO_REC_SEAMLESS_ERROR;
                }
                else
                {
                    AHC_DBG_MSG(1, "-I- Space is not enough for recording, Delete video file first!\r\n");
                    if (AHC_VIDEO_DeleteDcfMinKeyFile(AHC_TRUE, (const char *) AHC_GetVideoExt()) != AHC_TRUE)
                        return VIDEO_REC_SEAMLESS_ERROR;
                }
            }
        }
        #endif
#endif
    }

    // Video
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_CODEC_TYPE        , AHC_MOVIE_VIDEO_CODEC_H264);
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_COMPRESSION_RATIO , MenuSettingConfig()->uiMOVQuality);
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_MAX_PFRAME_NUM          , 14);

    // Audio
#if (VR_AUDIO_TYPE == VR_AUDIO_TYPE_AAC)
    aformat = AHC_MOVIE_AUDIO_CODEC_AAC;
#elif (VR_AUDIO_TYPE == VR_AUDIO_TYPE_MP3)
    aformat = AHC_MOVIE_AUDIO_CODEC_MP3;
#elif (VR_AUDIO_TYPE == VR_AUDIO_TYPE_ADPCM)
    aformat = AHC_MOVIE_AUDIO_CODEC_ADPCM;
#elif (VR_AUDIO_TYPE == VR_AUDIO_TYPE_PCM)
    aformat = AHC_MOVIE_AUDIO_CODEC_PCM;
#endif

    AHC_VIDEO_ConfigAudio(AHC_AUDIO_STREAM_ID, aformat, AHC_AUDIO_CHANNEL_MONO_R);

    #if (VR_PREENCODE_EN)
    ulResvSize = (m_ubPreEncodeEn)?(STORAGE_MIN_SIZE+PRE_RECORD_STORAGE_MIN_SIZE):(STORAGE_MIN_SIZE);
    #else
    ulResvSize = STORAGE_MIN_SIZE;
    #endif
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_RESERVED_SIZE, ulResvSize);

    if (uiGetParkingModeEnable() == AHC_TRUE)
    {
        AHC_VIDEO_GetCurRecordingTime(&ulPreRecordedTime);
        // for parking pre-encode
        {
            MMP_ULONG ulNewTime = 0;
            AHC_DBG_MSG(1, "Cur Parking Recd Time [%d] ms\r\n", ulPreRecordedTime);
            ulNewTime = ulPreRecordedTime + (AHC_GetVMDRecTimeLimit()*1000);
            AHC_DBG_MSG(1, "New Parking Clip Time [%d] ms\r\n", ulNewTime);
            MMPS_3GPRECD_SetFileTimeLimit(ulNewTime);
            //AHC_VIDEO_SetRecTimeLimit((ulNewTime+999)/1000);
        }
    }

    #if (GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO)
    if (uiGetParkingModeEnable() == AHC_TRUE)
    {
        AHC_GPS_TriggerRestorePreRecordInfo(AHC_TRUE, ulPreRecordedTime, AHC_FALSE);
    }
    else
    {
        GPSCtrl_ResetBufferControlVariable();
    }
    #endif

    #if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)
    if (uiGetParkingModeEnable() == AHC_TRUE)
    {
        AHC_Gsensor_TriggerRestorePreRecordInfo( AHC_TRUE, ulPreRecordedTime, AHC_FALSE );
    }
    else
    {
        AHC_Gsensor_ResetBufCtrlVariable();
    }
    #endif

    #if (GSENSOR_CONNECT_ENABLE)
    {
        extern AHC_BOOL AHC_Gsensor_GetCurIntStatus(AHC_BOOL* bObjMove);

        AHC_BOOL    dummy;
        // Clean GSensor INT status to avoid getting the status of before recording
        AHC_Gsensor_GetCurIntStatus(&dummy);
    }
    #endif

    m_uiSlowMediaCBCnt  = 0;

    {
        int iSlowMotionRatioSetting = pf_SLOWMOTION_EnGet();
        UINT32 uiSlowMotionRatio = 1;
        UINT32 Param, FrameRate, ulTimeIncre, ulTimeResol;

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &Param);
        FrameRate = AHC_VIDEO_GetVideoRealFpsX1000(Param);

        ulTimeIncre = AHC_VIDRECD_TIME_INCREMENT_BASE;
        ulTimeResol = FrameRate;

        switch(iSlowMotionRatioSetting){
        case SLOWMOTION_X2:
            uiSlowMotionRatio = 2;
            bEnableSlowMotion = AHC_TRUE;
            break;
        case SLOWMOTION_X4:
            uiSlowMotionRatio = 4;
            bEnableSlowMotion = AHC_TRUE;
            break;
        case SLOWMOTION_X8:
            uiSlowMotionRatio = 8;
            bEnableSlowMotion = AHC_TRUE;
            break;
        case SLOWMOTION_X1:
        default:
            uiSlowMotionRatio = 1;
            break;
        }

        if (uiSlowMotionRatio != 1) {
            AHC_DBG_MSG(1, FG_GREEN("SlowMotionRatio:X%x\r\n"), uiSlowMotionRatio);
        }

        AHC_VIDEO_SetSlowMotionFPS(bEnableSlowMotion, AHC_VIDRECD_TIME_INCREMENT_BASE, ulTimeResol * AHC_VIDRECD_TIME_INCREMENT_BASE / ulTimeIncre / uiSlowMotionRatio);
    }

#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN == 1)
    {
        int iTimeLapseSetting;
        UINT32 uiTimeLapseRatio = 1;
        UINT32 Param, FrameRate, ulTimeIncre, ulTimeResol;

        pf_General_EnGet(COMMON_KEY_VR_TIMELAPSE, &iTimeLapseSetting);
        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &Param);
        FrameRate = AHC_VIDEO_GetVideoRealFpsX1000(Param);

        ulTimeIncre = AHC_VIDRECD_TIME_INCREMENT_BASE;
        ulTimeResol = FrameRate;

        switch(iTimeLapseSetting){
        case PRJ_VR_TIMELAPSE_1SEC:
            bTimeLapseEnable = AHC_TRUE;
            uiTimeLapseRatio = 1;
            break;
        case PRJ_VR_TIMELAPSE_5SEC:
            bTimeLapseEnable = AHC_TRUE;
            uiTimeLapseRatio = 5;
            break;
        case PRJ_VR_TIMELAPSE_10SEC:
            bTimeLapseEnable = AHC_TRUE;
            uiTimeLapseRatio = 10;
            break;
        case PRJ_VR_TIMELAPSE_30SEC:
            bTimeLapseEnable = AHC_TRUE;
            uiTimeLapseRatio = 30;
            break;
        case PRJ_VR_TIMELAPSE_60SEC:
            bTimeLapseEnable = AHC_TRUE;
            uiTimeLapseRatio = 60;
            break;
        case PRJ_VR_TIMELAPSE_OFF:
        default:
            uiTimeLapseRatio = 1;
            break;
        }

        if (AHC_TRUE == bTimeLapseEnable) {
            AHC_DBG_MSG(1, FG_GREEN("TimeLapse 0x%x sec\r\n"), uiTimeLapseRatio);
        }
        else {
            AHC_DBG_MSG(0, FG_GREEN("TimeLapse Off\r\n"));
        }
        AHC_VIDEO_SetTimeLapseFPS(bTimeLapseEnable, AHC_VIDRECD_TIME_INCREMENT_BASE, ulTimeIncre / uiTimeLapseRatio);
    }
#endif

    AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8 *) VIDEO_DEFAULT_FLIE_FREECHAR);

    if ((MenuSettingConfig()->uiMOVSoundRecord != MOVIE_SOUND_RECORD_ON) ||
        (AHC_TRUE == bEnableSlowMotion) ||
        (AHC_TRUE == bTimeLapseEnable)) {
        AHC_VIDEO_SetRecordModeAudioOn(AHC_FALSE);
    }
    else {
        AHC_VIDEO_SetRecordModeAudioOn(AHC_TRUE);
    }

    ahc_ret = AHC_SetMode(AHC_MODE_VIDEO_RECORD);
    if (ahc_ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret); return VIDEO_REC_STOP;}

#if (MOTION_DETECTION_EN)
    // m_ulVMDStopCnt is not zero that is trigged by MVD, update VMD stop count again.
    if (m_ulVMDStopCnt && (AHC_TRUE == ahc_ret)) {
        #if (PARKING_RECORD_FORCE_20SEC == 1)
        UINT32 ulTime = 0;
        AHC_VIDEO_GetCurRecordingTime(&ulTime);
        ulTime += VideoFunc_GetRecordTimeOffset();
        AHC_DBG_MSG(1, FG_BLUE("Parking: Recorded time = %d ms\r\n"), ulTime);
        m_ulVMDStopCnt = 200 - (ulTime / 100); // Set remaining recording time
        #else
        m_ulVMDStopCnt = AHC_GetVMDRecTimeLimit() * 1000 / VIDEO_TIMER_UNIT;
        #endif
    }
    else
    {
        // When VR is error, stop down count for VMD VR
        m_ulVMDStopCnt = 0;
    }
#endif

    if (AHC_TRUE == ahc_ret)
    {
        uiStateSetLocked(AHC_TRUE);
        VideoFunc_SetRecordStatus(AHC_TRUE);
    }
    else
    {
        return VIDEO_REC_STOP;
    }

    #if (defined(CUS_ADAS_OUTPUT_LOG) && ADAS_OUTPUT_LOG == 1)
    ADAS_open_txt((char *) AHC_VIDEO_GetCurPrmRecdFileName(0));
    ADAS_CTL_SetADASOutputLog(MMP_TRUE);
    #endif

    return VIDEO_REC_START;
}

AHC_BOOL VideoFunc_RecordStop(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

#if (FLICKER_PWR_LED_AT_VR_STATE)
    LedCtrl_PowerLed(AHC_TRUE);
#endif

#if (VR_PREENCODE_EN)
    if (m_ubPreEncodeEn) {
        m_ubPreRecording = AHC_FALSE;
    }
#endif

    if (AHC_VIDEO_IsEmergRecStarted() == AHC_TRUE) {

        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE) {
            AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
        }
        else if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
                 (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)) {
            AHC_VIDEO_StopEmergRecord();
            SystemSettingConfig()->byStartNormalRecordAfterEmergencyRecord = 0;
            AHC_VIDEO_EmergRecPostProcess();
            AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
            AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_AHC_DONE);
        }
    }
    else if (uiGetParkingModeEnable()) {
         //AHC_MODE_RECORD_PRERECD => exit parking mode from idle <No need to PostAddFile if exit from idle>
         //AHC_MODE_VIDEO_RECORD => exit parking mode from recording
         if ( AHC_MODE_VIDEO_RECORD == AHC_GetAhcSysMode() )
             AHC_VIDEO_ParkingModePostProcess();
    }

    ahc_ret = VideoFunc_SetAttribute();

#if (MOTION_DETECTION_EN)
    m_ulVMDRemindTime = 1;
    #if !defined(CFG_MVD_MODE_LINK_WITH_MENU_SENSITIVITY)
    m_ubVMDStart      = AHC_FALSE;
    #endif
    m_ulVMDStopCnt    = 0;
#endif

    if (VideoFunc_LockFileEnabled()) {
        // Remove Lock Next file
        LockFileTypeChange(1 /* Remove Next */);
    }

    ahc_ret = AHC_SetMode(AHC_MODE_RECORD_PREVIEW);

#if (VR_PREENCODE_EN)
    if (m_ubPreEncodeEn) {
        m_ubPreRecording = AHC_TRUE;
    }
#endif

    if (AHC_TRUE == ahc_ret) {
        uiStateSetLocked(AHC_FALSE);
        VideoFunc_SetRecordStatus(AHC_FALSE);

        #if (AHC_SHAREENC_SUPPORT)
        AHC_VIDEO_SetShareRecdStarted(AHC_FALSE);
        m_bAhcFirstShareFile = AHC_FALSE;
        #endif
    }
    else {
        AHC_DBG_ERR(1, "Back to Preview Error\r\n");
    }

    #if (defined(CUS_ADAS_OUTPUT_LOG) && ADAS_OUTPUT_LOG == 1)
    ADAS_close_txt();
    ADAS_CTL_SetADASOutputLog(MMP_FALSE);
    #endif

    DBG_AutoTestPrint(ATEST_ACT_REC_0x0001, ATEST_STS_END_0x0003, 0, !ahc_ret, gbAhcDbgBrk);

    return ahc_ret;
}

AHC_BOOL VideoFunc_RecordPause(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32   CurSysMode;

    DBG_AutoTestPrint(ATEST_ACT_REC_0x0001, ATEST_STS_PAUSE_0x0002, 0, 0, gbAhcDbgBrk);

    AHC_GetSystemStatus(&CurSysMode);

    CurSysMode >>= 16;

    if ((CurSysMode != AHC_MODE_VIDEO_RECORD))
    {
        return AHC_FALSE;
    }

    ahc_ret = AHC_VIDEO_CaptureClipCmd(AHC_CAPTURE_CLIP_PAUSE, 0);

    return ahc_ret;
}

AHC_BOOL VideoFunc_RecordResume(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;
    UINT32   CurSysMode;

    AHC_FS_SetCreationTime();
    AHC_GetSystemStatus(&CurSysMode);

    CurSysMode >>= 16;

    if( ( CurSysMode != AHC_MODE_VIDEO_RECORD ) )
    {
        return AHC_FALSE;
    }

    ahc_ret = AHC_VIDEO_CaptureClipCmd(AHC_CAPTURE_CLIP_RESUME, 0);

    return ahc_ret;
}

AHC_BOOL VideoFunc_Shutter(void)
{
    AHC_BOOL bAhcRet = AHC_TRUE;

    bAhcRet = AHC_VIDEO_CaptureClipCmd(AHC_CAPTURE_SNAPSHOT, 0);

    return bAhcRet;
}

AHC_BOOL VideoFunc_ShutterFail(void)
{
    return AHC_TRUE;
}

AHC_BOOL VideoFunc_Preview(void)
{
    AHC_BOOL    ahc_ret = AHC_TRUE;
    UINT8       ubNightMode = 0;
    int         iTimeLapseSetting;
    int         iSlowMotionRatioSetting;

#if (ENABLE_ADAS_LDWS || ENABLE_ADAS_FCWS || ENABLE_ADAS_SAG)
    UINT32 bLDWS_En = COMMON_LDWS_EN_OFF;
    UINT32 bFCWS_En = COMMON_FCWS_EN_OFF;
    UINT32 bSAG_En  = COMMON_SAG_EN_OFF;
    UINT32 uiAdasFlag = 0;
#endif
    AHC_BOOL ahcRet = AHC_TRUE;

#if (VR_PREENCODE_EN)
    if (m_ubPreEncodeEn)
        m_ubPreRecording = AHC_FALSE;
#endif

    ahc_ret = VideoFunc_SetPreviewWindow(AHC_TRUE);
    ahc_ret = VideoFunc_SetAttribute();

#ifdef  _OEM_
    Oem_SetVideo_Prop(MenuSettingConfig()->uiMOVSize);
#endif

    AHC_PreSetFlashLED();

#if (MOTION_DETECTION_EN)
    m_ubVMDStart      = AHC_FALSE;
    m_ulVMDStopCnt    = 0;
#endif

    //Select Y-type.
#if (ENABLE_ADAS_LDWS || ENABLE_ADAS_FCWS || ENABLE_ADAS_SAG)
    AHC_GetParam(PARAM_ID_ADAS, &uiAdasFlag);

#if (ENABLE_ADAS_LDWS)
    #ifdef CFG_ADAS_MENU_SETTING_OLD_STYLE
    if (MenuSettingConfig()->uiLDWS == COMMON_LDWS_EN_ON)
    #else
    if (uiAdasFlag & AHC_ADAS_ENABLED_LDWS)
    #endif
    {
        bLDWS_En = COMMON_LDWS_EN_ON;
    }
#endif

#if (ENABLE_ADAS_FCWS)
    #ifdef CFG_ADAS_MENU_SETTING_OLD_STYLE
    if (MenuSettingConfig()->uiFCWS == COMMON_FCWS_EN_ON)
    #else
    if (uiAdasFlag & AHC_ADAS_ENABLED_FCWS)
    #endif
    {
        bFCWS_En = COMMON_FCWS_EN_ON;
    }
#endif

#if (ENABLE_ADAS_SAG)
    if (uiAdasFlag & AHC_ADAS_ENABLED_SAG)
    {
        bSAG_En = COMMON_SAG_EN_ON;
    }
#endif

    //Init With ADAS mode.
    if (bLDWS_En == COMMON_LDWS_EN_ON ||
        bFCWS_En == COMMON_FCWS_EN_ON ||
        bSAG_En  == COMMON_SAG_EN_ON){
        ahcRet = AHC_VIDEO_SetRecordModeRegisterInit((void *)AHC_VIDEO_SetRecordModeInitADASMode);
        ahcRet = AHC_VIDEO_SetRecordModeRegisterUnInit((void *)AHC_VIDEO_SetRecordModeUnInitADASMode);
    }
    else
#endif
    {
        //Init With default mode.
        ahcRet = AHC_VIDEO_SetRecordModeRegisterInit((void *)AHC_VIDEO_SetRecordModeInit);
        ahcRet = AHC_VIDEO_SetRecordModeRegisterUnInit((void *)AHC_VIDEO_SetRecordModeUnInit);
    }

    #if (MENU_MOVIE_NIGHT_MODE_EN)
    AHC_Menu_SettingGetCB((char *)COMMON_KEY_NIGHT_MODE_EN, &ubNightMode);
    if (ubNightMode == COMMON_NIGHT_MODE_EN_ON) {

        pf_General_EnGet(COMMON_KEY_VR_TIMELAPSE, &iTimeLapseSetting);
        iSlowMotionRatioSetting = pf_SLOWMOTION_EnGet();

        if (iSlowMotionRatioSetting != SLOWMOTION_X1 ||
            iTimeLapseSetting != PRJ_VR_TIMELAPSE_OFF) {
            AHC_SetParam(PARAM_ID_NIGHT_MODE_AE, 0);
            AHC_VIDEO_SetNightMode(0, AHC_FALSE, NIGHT_MODE_FPS);
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_VIDEO_SetNightMode(1, AHC_FALSE, NIGHT_MODE_FPS);
        }
        else {
            AHC_SetParam(PARAM_ID_NIGHT_MODE_AE, 1);
            AHC_VIDEO_SetNightMode(0, AHC_TRUE, NIGHT_MODE_FPS);
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_VIDEO_SetNightMode(1, AHC_TRUE, NIGHT_MODE_FPS);
        }
    }
    else {
        AHC_SetParam(PARAM_ID_NIGHT_MODE_AE, 0);
        AHC_VIDEO_SetNightMode(0, AHC_FALSE, NIGHT_MODE_FPS);
        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
            AHC_VIDEO_SetNightMode(1, AHC_FALSE, NIGHT_MODE_FPS);
    }
    #endif

    {
        pf_General_EnGet(COMMON_KEY_VR_TIMELAPSE, &iTimeLapseSetting);
        iSlowMotionRatioSetting = pf_SLOWMOTION_EnGet();

        if (iSlowMotionRatioSetting != SLOWMOTION_X1 ||
            iTimeLapseSetting != PRJ_VR_TIMELAPSE_OFF) {
            MMPS_3GPRECD_SetAVSyncMethod(VIDMGR_AVSYNC_REF_VID);
        }
        else {
            MMPS_3GPRECD_SetAVSyncMethod(VIDMGR_AVSYNC_REF_AUD);
        }
    }

    #if 0
    if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_TS) {
        MMPS_3GPRECD_SetMuxerConstFps(MMP_FALSE);
        MMPS_3GPRECD_SetAVSyncMethod(VIDMGR_AVSYNC_REF_AUD);
        AHC_DBG_MSG(1, FG_YELLOW("\r\nMTS AVSync by AUD\r\n"));
    }
    #endif

    ahc_ret = AHC_SetMode(AHC_MODE_RECORD_PREVIEW);

#if (VR_PREENCODE_EN)
    if (m_ubPreEncodeEn)
    {
        m_ubPreRecording = AHC_TRUE;
        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_RESERVED_SIZE, STORAGE_MIN_SIZE+PRE_RECORD_STORAGE_MIN_SIZE);
    }
#endif

#if (SUPPORT_VR_THUMBNAIL)
    //AHC_VIDEO_SetVRThumbAttr(512, 288);
    AHC_VIDEO_SetVRThumbAttr(480, 272);
#else
    AHC_VIDEO_SetVRThumbAttr(0, 0);
#endif

#if (SUPPORT_EIS)
    {
        static int testgyro_flag = 0;

        extern void MMPF_EIS_mode_init(void);
        extern void MMPF_EIS_start_gyro_sample(void);
        extern MMP_SLONG MMPF_EIS_enable(MMP_ULONG en);

        MMPF_EIS_mode_init();
        AHC_DBG_MSG(1, "\r\nMMPF_EIS_mode_init\r\n");

        if (testgyro_flag == 0) {
            testgyro_flag = 1;

            MMPF_EIS_start_gyro_sample();
            AHC_DBG_MSG(1, "\r\nMMPF_EIS_start_gyro_sample\r\n");
        }
        MMPF_EIS_enable(1);
    }
#endif

    return ahc_ret;
}

AHC_BOOL VideoFunc_EnterVMDMode(void)
{
#if (MOTION_DETECTION_EN)

    if (AHC_SDMMC_BasicCheck() != AHC_FALSE ||
        MenuSettingConfig()->uiMotionDtcSensitivity == MOTION_DTC_SENSITIVITY_OFF)
        return AHC_FALSE;

    if (VideoFunc_GetRecordStatus())
        return AHC_TRUE;

    m_ulVMDCancel    = AHC_FALSE;
    m_ubInRemindTime = AHC_TRUE;

    #ifdef CFG_REC_CUS_VMD_REMIND_TIME //may be defined in config_xxx.h
    m_ulVMDRemindTime = CFG_REC_CUS_VMD_REMIND_TIME;
    #else
    m_ulVMDRemindTime = 10;
    #endif

    m_ubMotionDtcEn = AHC_TRUE;
    #if (VR_PREENCODE_EN)
    m_ubPreEncodeEn = AHC_FALSE;
    #endif
    AHC_SetMode(AHC_MODE_IDLE);
    VideoFunc_Preview();

#endif
    return AHC_TRUE;
}

AHC_BOOL VideoFunc_ExitVMDMode(void)
{
#if (MOTION_DETECTION_EN)

    #if (VR_PREENCODE_EN)
    m_ubPreEncodeEn = AHC_FALSE;
    #endif
    m_ubMotionDtcEn = AHC_FALSE;

    m_ubInRemindTime = AHC_FALSE;

    if (VideoFunc_GetRecordStatus())
    {
        VideoFunc_RecordStop();
        DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);
    }
    else
    {
        bDisableVideoPreRecord = AHC_TRUE;
    }

    if (m_ulVMDRemindTime)
    {
        m_ulVMDCancel = AHC_TRUE;
    }
    else
    {
        AHC_SetMode(AHC_MODE_IDLE);
        VideoFunc_Preview();
    }
#endif
    return AHC_TRUE;
}

AHC_BOOL VideoFunc_ZoomOperation(AHC_ZOOM_DIRECTION bZoomDir)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

#if (VIDEO_DIGIT_ZOOM_EN)

    if( AHC_SENSOR_ZOOM_IN == bZoomDir )
    {
        if( ZoomCtrl_GetVideoDigitalZoomMax() > ZoomCtrl_GetVideoDigitalZoomLevel() )
        {
            ahc_ret = ZoomCtrl_DigitalZoom(VIDEO_CAPTURE_MODE, AHC_SENSOR_ZOOM_IN);
        }
    }
    else if(AHC_SENSOR_ZOOM_OUT == bZoomDir )
    {
        if( 0 < ZoomCtrl_GetVideoDigitalZoomLevel() )
        {
            ahc_ret = ZoomCtrl_DigitalZoom(VIDEO_CAPTURE_MODE, AHC_SENSOR_ZOOM_OUT);
        }
    }
    else
    {
        ahc_ret = ZoomCtrl_DigitalZoom(VIDEO_CAPTURE_MODE, AHC_SENSOR_ZOOM_STOP);
    }
#endif
    return ahc_ret;
}

//------------------------------------------------------------------------------
//  Function    : VideoFunc_RecordRestart
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL VideoFunc_RecordRestart(void)
{
    UINT64      u64FreeSpace    = 0;
    UINT64      u64SpaceNeeded  = 0;
    UINT32      u32AudBitRate   = 128000;//128K
    UINT32      u32VidBitRate   = 0;
    AHC_BOOL    bDeleteFile     = AHC_FALSE;
    AHC_BOOL    ahc_ret         = AHC_TRUE;
    UINT32      u32Timelimit    = 0;
#if (DCF_DB_COUNT >= 2)
    UINT32      u32SpaceNeededInClusters = 0;
    DCF_DB_TYPE eDBType;
#endif
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    UINT32      u32VRTimelapse = 0;      // Off
#endif
    VIDENC_FW_STATUS ePrmEncStatus = VIDENC_FW_STATUS_NONE;

    MMPS_3GPRECD_GetPrmEncoderStatus(&ePrmEncStatus);

    if (ePrmEncStatus != VIDENC_FW_STATUS_PREENCODE) {
        AHC_DBG_ERR(1, FG_RED("Prm Encoder Status Wrong [%d]\r\n"), ePrmEncStatus);
        return AHC_FALSE;
    }

    ahc_ret = VideoFunc_SetAttribute();

    if (AHC_SDMMC_BasicCheck() == AHC_FALSE) {
        AHC_DBG_ERR(1, "AHC_SDMMC_BasicCheck Fail\r\n");
        return AHC_FALSE;
    }

    u32Timelimit = AHC_VIDEO_GetRecTimeLimitEx();

    if (u32Timelimit == NON_CYCLING_TIME_LIMIT)
    {
        UINT32 ulCurrRecTime = 0;

        AHC_VIDEO_GetCurRecordingTime(&ulCurrRecTime);
        m_u32UiRecordTimeOffset += ulCurrRecTime;

        u64SpaceNeeded  = 0x24000000;
        bDeleteFile     = AHC_FALSE;
    }
    else
    {
        #if (LIMIT_MAX_LOCK_FILE_TIME)
        // Calculate Correct Time Offset, CHECK
        if (VideoFunc_LockFileEnabled()) {
            m_u32UiRecordTimeOffset += m_u32UiVRTotalTime;
            u32Timelimit = AHC_GetVideoMaxLockFileTime();
            m_u32UiVRTotalTime = u32Timelimit * 1000;
        }
        else {
            if (m_u32UiVRTotalTime != 0) {
                m_u32UiRecordTimeOffset += m_u32UiVRTotalTime;
                m_u32UiVRTotalTime = 0;
            }
            else {
                m_u32UiRecordTimeOffset += (u32Timelimit*1000/*ms*/);
            }
        }
        #else
        m_u32UiRecordTimeOffset += (u32Timelimit*1000/*ms*/);
        #endif

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &u32VidBitRate);

    #if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
        if ((AHC_Menu_SettingGetCB(COMMON_KEY_VR_TIMELAPSE, &u32VRTimelapse) == AHC_TRUE) &&
            (u32VRTimelapse != PRJ_VR_TIMELAPSE_OFF)) {

            UINT32 u32FrameRate = 0;
            UINT32 u32FrateIdx = 0;

            AHC_DBG_MSG(1, " TimeLapse record.\r\n");

            AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &u32FrateIdx);
            u32FrameRate = AHC_VIDEO_GetVideoRealFpsX1000(u32FrateIdx) / AHC_VIDRECD_TIME_INCREMENT_BASE;

            AHC_VIDEO_GetTimeLapseBitrate(u32FrameRate, u32VRTimelapse, &u32VidBitRate, &u32AudBitRate);
        }
        else
    #endif
        {
            if (MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_OFF) {
                u32AudBitRate = 0;
            }
        }

        AHC_VIDEO_GetRecStorageSpaceNeed(u32VidBitRate, u32AudBitRate, u32Timelimit, &u64SpaceNeeded);

        AHC_Media_GetFreeSpace(&u64FreeSpace);

        #if (DCF_DB_COUNT >= 2)
        eDBType = AHC_UF_GetDB();
        #if (AHC_SHAREENC_SUPPORT)
        if (eDBType != DCF_DB_TYPE_DB0_NORMAL) {
        #else
        if (eDBType != DCF_DB_TYPE_DB0_NORMAL && !VideoFunc_LockFileEnabled()) {
        #endif
            AHC_DBG_MSG(1, FG_YELLOW("1: %s, %d, current db:%d\r\n"), __FUNCTION__, __LINE__, eDBType);
            AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
        }
        #endif

    #if (DCF_DB_COUNT >= 2)
        if (uiGetParkingModeEnable() == AHC_FALSE) {
            eDBType = DCF_DB_TYPE_DB0_NORMAL;
        }
        else {
            eDBType = DCF_DB_TYPE_DB1_PARKING;
        }

        u32SpaceNeededInClusters = u64SpaceNeeded / AHC_UF_GetClusterSize(eDBType);

        if ((AHC_UF_GetFileCluster(eDBType)+ u32SpaceNeededInClusters > AHC_UF_GetClusterTH(eDBType)) ||
            (u64FreeSpace < u64SpaceNeeded))
        {
            AHC_DBG_MSG(1, "## Delete File For More Free Space\r\n");
            bDeleteFile = AHC_TRUE;
        }
        #if (DELETION_BY_FILE_NUM)
        else
        {
            UINT32 u32FileCount = 0;
            DCF_DB_TYPE sCurDB;

            eDBType = AHC_UF_GetDB();

            #if (AHC_SHAREENC_SUPPORT)
            if (eDBType != DCF_DB_TYPE_DB0_NORMAL) {
            #else
            if (eDBType != DCF_DB_TYPE_DB0_NORMAL && !VideoFunc_LockFileEnabled()) {
            #endif
                AHC_DBG_MSG(1, FG_YELLOW("2: %s, %d, current db:%d\r\n"), __FUNCTION__, __LINE__, eDBType);
                AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
            }

            AHC_UF_GetTotalFileCount(&u32FileCount);
            if (u32FileCount >= AHC_UF_GetFileTH(sCurDB)) {
                AHC_DBG_MSG(1, "FileCount > FileNum Threshold\r\n");
                bDeleteFile = AHC_TRUE;
            }
        }
        #endif //#if (DELETION_BY_FILE_NUM)
    #else
        if (u64FreeSpace < u64SpaceNeeded)
        {
            AHC_DBG_MSG(1, "--I-- %s:%d Storage space is not enough for recording, delete video file\r\n", __FUNCTION__, __LINE__);
            bDeleteFile = AHC_TRUE;
        }
        #if (DELETION_BY_FILE_NUM)
        else
        {
            UINT32 u32FileCount;

            AHC_UF_GetTotalFileCount(&u32FileCount);
            if (u32FileCount >= AHC_UF_GetFileTH(DCF_DB_TYPE_DB0_NORMAL)){
                AHC_DBG_MSG(1, "FileCount > FileNum Threshold\r\n");
                bDeleteFile = AHC_TRUE;
            }
        }
        #endif //#if (DELETION_BY_FILE_NUM)
    #endif
    }

#if (RESET_RECORDED_TIME)
    m_u32UiRecordTimeOffset = 0;
#endif

    AHC_DBG_MSG(1, "======================================\r\n");
    AHC_DBG_MSG(0, "Restart TimeOffset [%d] ms\r\n", m_u32UiRecordTimeOffset);

#if (DCF_DB_COUNT >= 2)
    eDBType = AHC_UF_GetDB();
    #if (AHC_SHAREENC_SUPPORT)
    if (eDBType != DCF_DB_TYPE_DB0_NORMAL) {
    #else
    if (eDBType != DCF_DB_TYPE_DB0_NORMAL && !VideoFunc_LockFileEnabled()) {
    #endif
        AHC_DBG_MSG(1, FG_YELLOW("3: %s, %d, current db:%d\r\n"), __FUNCTION__, __LINE__, eDBType);
        AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
    }
#endif

    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_RESERVED_SIZE, STORAGE_MIN_SIZE);

    m_uiSlowMediaCBCnt = 0;

    #if (UPDATE_UI_USE_MULTI_TASK)
    m_ubUpdateUiByOtherTask = AHC_TRUE;
    #endif

    AHC_VIDEO_SetRecdDeleteFileEn(bDeleteFile);

    ahc_ret = AHC_VIDEO_RestartRecMode();

    #if (UPDATE_UI_USE_MULTI_TASK)
    m_ubUpdateUiByOtherTask = AHC_FALSE;
    #endif

    // Re-Set TimeLimit in case a time specified at file locked.
    AHC_VIDEO_SetRecTimeLimit(u32Timelimit);

    if (AHC_TRUE == ahc_ret) {
        uiStateSetLocked(AHC_TRUE);
        VideoFunc_SetRecordStatus(AHC_TRUE);
    }

    #if (defined(CUS_ADAS_OUTPUT_LOG) && ADAS_OUTPUT_LOG == 1)
    ADAS_close_txt();
    ADAS_open_txt((char *) AHC_VIDEO_GetCurPrmRecdFileName(0));
    #endif

    return ahc_ret;
}

AHC_BOOL VideoFunc_ChangeCurFileTimeLimit(void)
{
    #if (LIMIT_MAX_LOCK_FILE_TIME)
    {
        UINT32 ulCurVRTime, u32TimeLimit;
        UINT32 ulMaxVRTime = AHC_GetVideoMaxLockFileTime();

        AHC_VIDEO_GetCurRecordingTime(&ulCurVRTime);//ms
        //ulCurLockTime = ulCurVRTime;//ms
        AHC_DBG_MSG(1, "Current Recording Time %d ms\r\n",ulCurVRTime);

        if(ulCurVRTime > ulMaxVRTime * 1000)
        {
            m_u32UiVRTotalTime = ulCurVRTime;
        } else {
            m_u32UiVRTotalTime = ulMaxVRTime * 1000;
        }

        u32TimeLimit = (ulMaxVRTime+ulCurVRTime/1000);

        if (u32TimeLimit < ((0x7FFFFFFF - VR_TIME_LIMIT_OFFSET) / 1000)) {
            u32TimeLimit = u32TimeLimit * 1000 + VR_TIME_LIMIT_OFFSET;
        }else{
            u32TimeLimit = u32TimeLimit * 1000;
        }

        #if 1
        AHC_VIDEO_ChangeCurFileTimeLimit(u32TimeLimit);
        #else
        AHC_VIDEO_SetRecTimeLimit(ulMaxVRTime+ulCurVRTime/1000);//continue record locktime
        #endif
        //AHC_VIDEO_SetRecTimeLimit(1);//trigger media file full evnet,restart lock file...
    }
    #endif
    return AHC_TRUE;
}

AHC_BOOL VideoFunc_SetFileLock(void)
{
    if(AHC_WMSG_States())
    {
        AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
    }

    if(!VideoFunc_LockFileEnabled())
    {
        #if (LIMIT_MAX_LOCK_FILE_NUM) && (MAX_LOCK_FILE_ACT==LOCK_FILE_STOP)
        if (m_ulLockFileNum  >= MAX_LOCK_FILE_NUM )
            return AHC_FALSE;
        #endif

        AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
        EnableLockFile(AHC_TRUE, VR_LOCK_FILE_TYPE);

        #if (LIMIT_MAX_LOCK_FILE_NUM)
        m_ulLockEventNum++;
        #endif

        #if (LIMIT_MAX_LOCK_FILE_TIME)
        VideoFunc_ChangeCurFileTimeLimit();
        #endif
    }
    else
    {
        #if (LIMIT_MAX_LOCK_FILE_NUM)
        m_ulLockEventNum--;
        #endif
        EnableLockFile(AHC_FALSE, 0);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_UNLOCK_CUR_FILE, 2);
        AHC_Protect_SetType(AHC_PROTECT_NONE);
    }

    return AHC_TRUE;
}

AHC_BOOL VideoRecMode_Start(void)
{
    AHC_BOOL    ahc_ret = AHC_TRUE;
    UINT8       ubLCDstatus;
    MMP_UBYTE   ubNightMode;

    bShowHdmiWMSG   = AHC_TRUE;
    bShowTvWMSG     = AHC_TRUE;

    if (pf_SLOWMOTION_EnGet() == SLOWMOTION_X2) {
    }
    else if (pf_SLOWMOTION_EnGet() == SLOWMOTION_X4) {
    }
    else if (pf_SLOWMOTION_EnGet() == SLOWMOTION_X8){
    }
    else {
        SetCurrentOpMode(VIDEOREC_MODE);
    }

    AHC_OSDSetActive(0, 0);

    if (AHC_WMSG_States())
       AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);

    ahc_ret = VideoFunc_Preview();
    if (AHC_TRUE != ahc_ret){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret); return ahc_ret;}

    // Enter video pre-encode flow.
    if (MenuSettingConfig()->uiMOVPreRecord == MOVIE_PRE_RECORD_ON) {
        ahc_ret = VideoFunc_PreRecord();
    }

#if (SUPPORT_TOUCH_PANEL) && !defined(_OEM_TOUCH_)
    KeyParser_ResetTouchVariable();
    KeyParser_TouchItemRegister(&VideoMainPage_TouchButton[0], ITEMNUM(VideoMainPage_TouchButton));
#endif

    VideoTimer_Start(VIDEO_TIMER_UNIT);

    bMuteRecord = (MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_ON)?(AHC_FALSE):(AHC_TRUE);

#if (DAY_NIGHT_MODE_SWITCH_EN)
    bNightMode = (MenuSettingConfig()->uiScene == SCENE_TWILIGHT)?(AHC_TRUE):(AHC_FALSE);
#endif

    AHC_LCD_GetStatus(&ubLCDstatus);

    if (ubLCDstatus == AHC_LCD_NORMAL)
        DrawStateVideoRecUpdate(EVENT_LCD_COVER_NORMAL);
    else if (ubLCDstatus == AHC_LCD_REVERSE)
        DrawStateVideoRecUpdate(EVENT_LCD_COVER_ROTATE);

    return ahc_ret;
}

void VideoRecMode_PreviewUpdate(void)
{
    UINT8       ubLCDstatus;
    AHC_BOOL    ubUpdatePreview   = AHC_FALSE;

    if (m_eUiVideoRecResol != MenuSettingConfig()->uiMOVSize)
        ubUpdatePreview = AHC_TRUE;

    #if (ENABLE_ADAS_LDWS)
    {
        UINT32 bLDWS_En;

        if (LDWS_SettingChanged() == MMP_TRUE) {
            ubUpdatePreview = AHC_TRUE;
        }

        if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_LDWS_EN, &bLDWS_En) == AHC_TRUE ) {
            if ((LDWS_EN_OFF == bLDWS_En) && (MMPS_Sensor_GetADASFeatureEn(MMPS_ADAS_LDWS) == MMP_TRUE) ) {
                ubUpdatePreview = AHC_TRUE;
            }
            else if ((LDWS_EN_ON == bLDWS_En) && (MMPS_Sensor_GetADASFeatureEn(MMPS_ADAS_LDWS) == MMP_FALSE) ) {
                ubUpdatePreview = AHC_TRUE;
            }
        }
        if (LDWS_IsStart()) {
            LDWS_Unlock();
            ResetLDWSCounter();
        }
    }
    #endif

    #if (ENABLE_ADAS_FCWS)
    {
        UINT32 bFCWS_En;

        if ( AHC_Menu_SettingGetCB( (char *)COMMON_KEY_FCWS_EN, &bFCWS_En ) == AHC_TRUE ) {
            if ((FCWS_EN_OFF == bFCWS_En) && (MMPS_Sensor_GetADASFeatureEn(MMPS_ADAS_FCWS) == MMP_TRUE) ) {
                ubUpdatePreview = AHC_TRUE;
            }
            else if ((pf_FCWS_EnGet() == FCWS_EN_ON) && (MMPS_Sensor_GetADASFeatureEn(MMPS_ADAS_FCWS) == MMP_FALSE) ) {
                ubUpdatePreview = AHC_TRUE;
            }
        }
    }
    #endif

    {
        UINT32 hdr_En;

        if ( AHC_Menu_SettingGetCB( (char *)COMMON_KEY_HDR_EN, &hdr_En ) == AHC_TRUE ) {
            if ((MMP_GetVidHDRType(CAM_TYPE_PRM) == CUS_SNR_HDR_DCG) && (hdr_En == COMMON_HDR_EN_OFF) ) {
                ubUpdatePreview = AHC_TRUE;
            }
            else if ((MMP_GetVidHDRType(CAM_TYPE_PRM) == CUS_SNR_HDR_DISABLE) && (hdr_En == COMMON_HDR_EN_ON) ) {
                ubUpdatePreview = AHC_TRUE;
            }
        }
    }

    #if (MOTION_DETECTION_EN)
    if (m_ubMotionDtcEn && (MMPS_Sensor_IsVMDEnable() == MMP_FALSE)) {
        AHC_DBG_MSG(1, FG_GREEN("Motion setting changed - Need turn-on\r\n"));
        ubUpdatePreview = AHC_TRUE;
    }
    else if (!m_ubMotionDtcEn && (MMPS_Sensor_IsVMDEnable() == MMP_TRUE)) {
        AHC_DBG_MSG(1, FG_GREEN("Motion setting changed - Need turn-off\r\n"));
        ubUpdatePreview = AHC_TRUE;
    }
    #endif

    #if (VR_PREENCODE_EN)
    {
        UINT32  ulPreRecordStatus = 0;

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_PRERECORD_STATUS, &ulPreRecordStatus);

        if(bVideoPreRecordStatus != ulPreRecordStatus)
        {
            bVideoPreRecordStatus = ulPreRecordStatus;
            ubUpdatePreview       = AHC_TRUE;
        }
    }
    #endif

    #if (MENU_MOVIE_NIGHT_MODE_EN)
    {
        MMP_UBYTE   ubNightMode;
        UINT32      ulNightMode;
        int         iTimeLapseSetting;
        int         iSlowMotionRatioSetting = pf_SLOWMOTION_EnGet();

        pf_General_EnGet(COMMON_KEY_VR_TIMELAPSE, &iTimeLapseSetting);

        if (iTimeLapseSetting == PRJ_VR_TIMELAPSE_OFF &&
            iSlowMotionRatioSetting == SLOWMOTION_X1) {
            AHC_Menu_SettingGetCB((char *)COMMON_KEY_NIGHT_MODE_EN, &ubNightMode);
            AHC_GetParam(PARAM_ID_NIGHT_MODE_AE, &ulNightMode);

            if ((ubNightMode == COMMON_NIGHT_MODE_EN_OFF) && (ulNightMode == 1)) {
                AHC_SetParam(PARAM_ID_NIGHT_MODE_AE, 0);
                AHC_VIDEO_SetNightMode(0, AHC_FALSE, NIGHT_MODE_FPS);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    AHC_VIDEO_SetNightMode(1, AHC_FALSE, NIGHT_MODE_FPS);
            }
            else if ((ubNightMode == COMMON_NIGHT_MODE_EN_ON) && (ulNightMode == 0)) {
                AHC_SetParam(PARAM_ID_NIGHT_MODE_AE, 1);
                AHC_VIDEO_SetNightMode(0, AHC_TRUE, NIGHT_MODE_FPS);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    AHC_VIDEO_SetNightMode(1, AHC_TRUE, NIGHT_MODE_FPS);
            }
        }
    }
    #endif

#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN == 1)
    {
        int    iTimeLapseSetting;
        UINT32 ulNightMode;

        pf_General_EnGet(COMMON_KEY_VR_TIMELAPSE, &iTimeLapseSetting);

        if (iTimeLapseSetting != PRJ_VR_TIMELAPSE_OFF) {
            AHC_GetParam(PARAM_ID_NIGHT_MODE_AE, &ulNightMode);
            if (ulNightMode == 1) {
                AHC_DBG_MSG(1, FG_GREEN("[TimeLapse] Night Mode Off\n"));
                AHC_SetParam(PARAM_ID_NIGHT_MODE_AE, 0);
                AHC_VIDEO_SetNightMode(0, AHC_FALSE, NIGHT_MODE_FPS);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    AHC_VIDEO_SetNightMode(1, AHC_FALSE, NIGHT_MODE_FPS);
            }
        }
    }
#endif

    {
        int    iSlowMotionRatioSetting = pf_SLOWMOTION_EnGet();
        UINT32 ulNightMode;

        if (iSlowMotionRatioSetting != SLOWMOTION_X1) {
            AHC_GetParam(PARAM_ID_NIGHT_MODE_AE, &ulNightMode);
            if (ulNightMode == 1) {
                AHC_DBG_MSG(1, FG_GREEN("[SlowMotion] Night Mode Off\n"));
                AHC_SetParam(PARAM_ID_NIGHT_MODE_AE, 0);
                AHC_VIDEO_SetNightMode(0, AHC_FALSE, NIGHT_MODE_FPS);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    AHC_VIDEO_SetNightMode(1, AHC_FALSE, NIGHT_MODE_FPS);
            }
        }
    }

    {
        int    iTimeLapseSetting;
        int    iSlowMotionRatioSetting;

        pf_General_EnGet(COMMON_KEY_VR_TIMELAPSE, &iTimeLapseSetting);
        iSlowMotionRatioSetting = pf_SLOWMOTION_EnGet();

        if (iTimeLapseSetting != PRJ_VR_TIMELAPSE_OFF ||
            iSlowMotionRatioSetting != SLOWMOTION_X1) {
            MMPS_3GPRECD_SetAVSyncMethod(VIDMGR_AVSYNC_REF_VID);
        }
        else {
            MMPS_3GPRECD_SetAVSyncMethod(VIDMGR_AVSYNC_REF_AUD);
        }
    }

    g_bDrawUnfix = MMP_FALSE;

    AHC_LCD_GetStatus(&ubLCDstatus);

    if(ubLCDstatus == AHC_LCD_NORMAL)
        DrawStateVideoRecUpdate(EVENT_LCD_COVER_NORMAL);
    else if(ubLCDstatus == AHC_LCD_REVERSE)
        DrawStateVideoRecUpdate(EVENT_LCD_COVER_ROTATE);

    if(ubUpdatePreview == AHC_TRUE)
    {
        #if (VR_PREENCODE_EN)
        if(!m_ubPreEncodeEn)
            bDisableVideoPreRecord = AHC_TRUE;
        #endif
        AHC_SetMode(AHC_MODE_IDLE);

        VideoFunc_Preview();
    }

    bMuteRecord = (MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_ON)?(AHC_FALSE):(AHC_TRUE);

    #if (DAY_NIGHT_MODE_SWITCH_EN)
    bNightMode = (MenuSettingConfig()->uiScene == SCENE_TWILIGHT)?(AHC_TRUE):(AHC_FALSE);
    #endif

    #if (SUPPORT_TOUCH_PANEL) && !defined(_OEM_TOUCH_)
    KeyParser_ResetTouchVariable();
    KeyParser_TouchItemRegister(&VideoMainPage_TouchButton[0], ITEMNUM(VideoMainPage_TouchButton));
    #endif

    #if VIRTUAL_KEY_BOARD_FOR_WIFI
    {
        extern unsigned char ucWifiAPParamModified;
        extern unsigned char ucWifiSTAParamModified;
        extern unsigned char ucwifiStassid[6][64];
        extern unsigned char ucwifiStapswd[6][64];
        //amn_currConfig_get_enum( "Net.Dev.%d.BootProto", ucWifiAPParamModified )->v.strVal;

        AHC_DBG_MSG(1, "ucWifiAPParamModified %d, ucWifiSTAParamModified %d\n",ucWifiAPParamModified, ucWifiSTAParamModified);
        if(ucWifiAPParamModified)
        {
            ucWifiAPParamModified = 0;
            nhw_reset_network();
        }

        if(ucWifiSTAParamModified)
        {
            //0 none,  1 AES,  2 WEP
            switch (LwIP_join_WLAN_AP(ucwifiStassid[ucWifiSTAParamModified], 1, ucwifiStapswd[ucWifiSTAParamModified], 28 ))
            {
                case 1:
                    AHC_DBG_MSG(1, "... failed\n");
                    return;
                case 0:
                    AHC_DBG_MSG(1, "joined sucessful\n");
                    break;
            }

            if (LwIP_start_netif( NULL, NULL ) < 0)
            {
                nhw_set_status(NETAPP_NET_STATUS_NOIP);
            }
            else
            {
                nhw_set_status(NETAPP_NET_STATUS_READY);
            }

            ucWifiSTAParamModified = 0;
        }
    }
    #endif

    Menu_SetEV(0, MenuSettingConfig()->uiEV);
    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetEV(1, MenuSettingConfig()->uiEV);

    VideoTimer_Start(VIDEO_TIMER_UNIT);
}

AHC_BOOL VideoFunc_TriggerEmerRecord(void)
{
#if (EMER_RECORD_DUAL_WRITE_ENABLE == 1)
    if (AHC_VIDEO_IsEmergRecStarted() == AHC_TRUE)
    {
        UINT32 uiTime;
        UINT32 uiInterval;

        AHC_VIDEO_GetEmergRecTime(&uiTime);
        //AHC_DBG_MSG(1, "Emer Cur Time : %d \n", uiTime);

        uiInterval = AHC_VIDEO_GetEmergRecInterval();
        uiTime = (uiTime+1000 - 1)/1000;
        //AHC_DBG_MSG(1, "Emer Cur Time2 : %d (%d)\n", uiTime, uiInterval);

        if(uiInterval < EMER_RECORD_DUAL_WRTIE_MAX_TIME)
        {
            if(uiTime >= (uiInterval - EMER_RECORD_DUAL_WRTIE_DELTA))
            {
                uiTime+=EMER_RECORD_DUAL_WRITE_POSTTIME;

                if(uiTime > EMER_RECORD_DUAL_WRTIE_MAX_TIME){
                    uiTime = EMER_RECORD_DUAL_WRTIE_MAX_TIME;
                }else if(uiTime < EMER_RECORD_DUAL_WRITE_INTERVAL){
                    uiTime = EMER_RECORD_DUAL_WRITE_INTERVAL;
                }

                AHC_VIDEO_SetEmergRecInterval(uiTime);
            }
        }

        return AHC_FALSE;
    }

    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)) {
        if ((AHC_VIDEO_IsEmergRecStarted() == AHC_FALSE) &&
            (AHC_VIDEO_IsEmergPostDone() == AHC_TRUE) &&
            (AHC_VIDEO_GetKernalEmergStopStep() == AHC_KERNAL_EMERGENCY_AHC_DONE)) {
            #if (GPS_RAW_FILE_EMER_EN == 1)
            if(GPSCtrl_GetGPSRawStart_Emer() == AHC_FALSE)
            #else
            if(1)
            #endif
            {
                UINT32 ulCurrentRecordedTime = 0;
                AHC_VIDEO_FILENAME_MGR *pstScdRecdFileNameMgr = NULL;
                AHC_KERNAL_EMERGENCY_STOP_STEP eOrigEmergStep;

                AHC_VIDEO_GetCurRecordingTime(&ulCurrentRecordedTime);
                eOrigEmergStep = AHC_VIDEO_GetKernalEmergStopStep();

                AHC_VIDEO_GetEmergRecTimeOffset(&m_ulEventPreRecordTime);
                AHC_OS_GetTime(&m_ulEventHappenTime);

                AHC_DBG_MSG(1, FG_BLUE("TriggerEmerRecord PreRecTime [%d] CurrentRecTime [%d] \r\n"), m_ulEventPreRecordTime, ulCurrentRecordedTime);
                m_bCurrentTimeLessThanPreRecord = (m_ulEventPreRecordTime > ulCurrentRecordedTime)? AHC_TRUE : AHC_FALSE;

                #if (GPS_CONNECT_ENABLE)
                AHC_GPS_FlushBackupBuffer(0, AHC_TRUE);
                if (MMP_IsScdCamExist()) {
                    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);
                    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
                        AHC_GPS_FlushBackupBuffer(1, AHC_TRUE);
                    }
                }
                else if (MMP_IsUSBCamExist()) {
                    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);
                    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
                        AHC_GPS_FlushBackupBuffer(1, AHC_TRUE);
                    }
                }
                #endif
                #if (GSENSOR_CONNECT_ENABLE)
                AHC_Gsensor_FlushBackupBuffer(0, AHC_TRUE);
                if (MMP_IsScdCamExist()) {
                    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);
                    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
                        AHC_Gsensor_FlushBackupBuffer(1, AHC_TRUE);
                    }
                }
                else if (MMP_IsUSBCamExist()) {
                    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);
                    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
                        AHC_Gsensor_FlushBackupBuffer(1, AHC_TRUE);
                    }
                }
                #endif

                AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_RECORD);

                if (AHC_VIDEO_StartEmergRecord() == AHC_TRUE)
                {
                    return AHC_TRUE;
                }
                else
                {
                    AHC_VIDEO_SetKernalEmergStopStep(eOrigEmergStep);
                    return AHC_FALSE;
                }
            }
            else
            {
                return AHC_FALSE;
            }
        }
    }
    else if ((AHC_VIDEO_IsEmergRecStarted() == AHC_FALSE) &&
             (AHC_VIDEO_IsEmergPostDone() == AHC_TRUE)) {
        #if (GPS_RAW_FILE_EMER_EN == 1)
        if(GPSCtrl_GetGPSRawStart_Emer() == AHC_FALSE)
        #else
        if(1)
        #endif
        {
            AHC_VIDEO_StartEmergRecord();
            return AHC_TRUE;
        }
        else
        {
            return AHC_FALSE;
        }
    }

    #if (DELETION_BY_FILE_NUM)
    {
        UINT32 uiFileCount;
        DCF_DB_TYPE sCurDB;

        sCurDB = AHC_UF_GetDB();
        AHC_UF_GetTotalFileCount(&uiFileCount);
        if(uiFileCount >= AHC_UF_GetFileTH(sCurDB))
        {
            if(AHC_Deletion_RemoveEx(sCurDB, AHC_VIDEO_GetRecTimeLimitEx()) == AHC_FALSE)
            {
                AHC_DBG_MSG(1, FG_RED("AHC_Deletion_Romove Error\r\n"));
                return AHC_FALSE;
            }
        }
    }
    #endif
#endif

    return AHC_FALSE;
}

//******************************************************************************
//
//                              AHC State Video Mode
//
//******************************************************************************
AHC_BOOL StateVideoRecMode_StartRecordingProc(UINT32 ulJobEvent)
{
    VIDEO_RECORD_STATUS retVal;
    MMP_ULONG           checkHUVCtime = 0;
    MMP_BOOL            bUsbCamConnected = MMP_FALSE;

    if (AHC_SDMMC_BasicCheck() == AHC_FALSE) {

        #ifdef CFG_VIDEO_RECORD_FLICK_LED_BY_CARD_ERROR
        LedCtrl_FlickerLedByCustomer(LED_GPIO_SDMMC_ERROR, LED_GPIO_SDMMC_FLICK_PERIOD, LED_GPIO_SDMMC_FLICK_TIMES);
        #endif

        AHC_DBG_ERR(1, FG_RED("StartRecordingProc Card Error\r\n"));
        CGI_SET_STATUS(ulJobEvent, CGI_ERR_CARD_ERROR);
        return AHC_FALSE;
    }

    // wait for USB cam frame ready
    if (MMP_IsUSBCamExist()) {
        MMPF_USBH_GetUVCPrevwSts(&bUsbCamConnected);
        checkHUVCtime = 0;
        if ((bUsbCamConnected) && (Component_HUVC_CheckRdyStatus() == MMP_FALSE)) {
            do {
                AHC_OS_SleepMs(100);
                checkHUVCtime += 100;
            } while ((Component_HUVC_CheckRdyStatus() == MMP_FALSE) && (checkHUVCtime < 5000));
            if (checkHUVCtime < 5000)
                AHC_DBG_MSG(1, "[StartRecord] wait huvc rdy time: [%d] ms\r\n", checkHUVCtime);
            else
                AHC_DBG_MSG(1, "[StartRecord] wait huvc rdy timeout.\r\n");
        }
    }

    #if defined(CFG_ENABLE_VIDEO_REC_VIBRATION) && defined(CFG_VIDEO_REC_VIBRATION_TIME)
    if (AHC_SDMMC_IsSD1MountDCF())
    {
        UINT64 u64FreeSpace;

        AHC_Media_GetFreeSpace(&u64FreeSpace);

        if (u64FreeSpace)
        {
            AHC_Vibration_Enable(CFG_VIDEO_REC_VIBRATION_TIME);

            #if defined(CFG_VIDEO_REC_VIBRATION_TIMES) && (CFG_VIDEO_REC_VIBRATION_TIMES >= 2)
            {
                UINT16 times = CFG_VIDEO_REC_VIBRATION_TIMES - 1;

                while (times--) {
                    AHC_OS_SleepMs(CFG_VIDEO_REC_VIBRATION_TIME + 100);
                    AHC_Vibration_Enable(CFG_VIDEO_REC_VIBRATION_TIME);
                }
            }
            #endif

            AHC_OS_SleepMs(CFG_VIDEO_REC_VIBRATION_TIME);
        }
    }
    #endif  // defined(CFG_ENABLE_VIDEO_REC_VIBRATION) && defined(CFG_VIDEO_REC_VIBRATION_TIME)

    if (uiGetParkingModeEnable() == AHC_TRUE) {
        AHC_UF_SelectDB(DCF_DB_TYPE_DB1_PARKING);
    }
    else {
        AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
    }

    m_u32UiRecordTimeOffset = 0;

    retVal = VideoFunc_Record();
    AHC_DBG_MSG(1, "VideoFunc_Record() return %#x\r\n", retVal);

    switch (retVal) {
    case VIDEO_REC_START:
        #ifdef CFG_ENABLE_VIDEO_REC_LED
        RecLED_Timer_Start(100);
        #endif
        break;
    case VIDEO_REC_NO_SD_CARD:
    case VIDEO_REC_CARD_FULL:
        #ifdef CFG_VIDEO_RECORD_FLICK_LED_BY_CARD_ERROR
        LedCtrl_FlickerLedByCustomer(LED_GPIO_SDMMC_ERROR, LED_GPIO_SDMMC_FLICK_PERIOD, LED_GPIO_SDMMC_FLICK_TIMES);
        #endif
        break;
    case VIDEO_REC_PRERECD:
        AHC_DBG_MSG(1, "Enter pre record mode and wait to start record...\r\n");
        break;
    }

    #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE) // jeff.li
    if (VIDEO_REC_START != retVal && AHC_TRUE == m_ubParkingModeRecTrigger) {
        m_ubParkingModeRecTrigger = AHC_FALSE;
    }
    #endif

    if (VIDEO_REC_NO_SD_CARD == retVal) {
        CGI_SET_STATUS(ulJobEvent, CGI_ERR_NO_CARD);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_INSERT_SD_AGAIN, 3);
        AHC_DBG_MSG(1, "%s,%d error!", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
    else if (VIDEO_REC_CARD_FULL == retVal) {
        CGI_SET_STATUS(ulJobEvent, CGI_ERR_CARD_FULL);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_STORAGE_FULL, 3);
        AHC_DBG_MSG(1, "%s,%d error!", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
    else if (VIDEO_REC_SEAMLESS_ERROR == retVal) {
        CGI_SET_STATUS(ulJobEvent, CGI_ERR_SEAMLESS);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_SEAMLESS_ERROR, 3);
        AHC_DBG_MSG(1, "%s,%d error!", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
    else if (VIDEO_REC_SD_CARD_ERROR == retVal) {
        CGI_SET_STATUS(ulJobEvent, CGI_ERR_CARD_ERROR);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_FORMAT_SD_CARD, 3);
        AHC_DBG_MSG(1, "%s,%d error!", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
    else if (VIDEO_REC_START == retVal){
        CGI_SET_STATUS(ulJobEvent, CGI_ERR_NONE);
    }
    else {
        CGI_SET_STATUS(ulJobEvent, CGI_ERR_CARD_ERROR);
    }

    if (VIDEO_REC_START == retVal)
        DrawStateVideoRecUpdate(ulJobEvent);
    else
        DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);

    if ((uiGetParkingModeEnable()) && (retVal != VIDEO_REC_START)) {
        AHC_DBG_MSG(1, "%s: Re-init Parking Mode.\r\n", __FUNCTION__);
        uiSetParkingModeEnable(AHC_FALSE);
        AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_MENU_LPRESS, 0);
    }

    return AHC_TRUE;
}

AHC_BOOL StateVideoRecMode_StopRecordingProc(UINT32 ulJobEvent)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = VideoFunc_RecordStop();

    #if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
    m_ulGSNRRecStopCnt = 0;
    #endif

    //not muted recoding every time when recording starts
    #ifdef CFG_REC_FORCE_UNMUTE //may be defined in config_xxx.h
    if (bMuteRecord)
        AHC_ToggleMute();
    #endif

    //TODO Add callbacks here
    #ifdef CFG_ENABLE_VIDEO_REC_LED
    RecLED_Timer_Stop();
    #endif

    #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
    if (uiGetParkingModeEnable() == AHC_TRUE) {
        #if (MOTION_DETECTION_EN)
        m_ulVMDStableCnt = MOTION_DETECTION_STABLE_TIME2 * 1000 / (VIDEO_TIMER_UNIT*10);// REF::VideoTimer_ISR_Slow(tmr, arg); //100 ms
        m_ubVMDStart     = AHC_FALSE;
        #endif
        m_ubParkingModeRecTrigger = AHC_FALSE;
    }
    #endif

    DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);

    #ifdef NET_SYNC_PLAYBACK_MODE
    if (ulJobEvent != EVENT_NET_ENTER_PLAYBACK)
    #endif
        CGI_SET_STATUS(ulJobEvent, CGI_RET_STOP/*1*/ /* STOP */);

    return ahcRet;
}

#if (ENABLE_ADAS_LDWS)

extern MMP_UBYTE ADAS_CTL_GetLDWSAttr(ldws_params_t *ldws_attr, MMP_LONG *alert);

void VideoFunc_LDWSWarn(void)
{
    ldws_params_t cur_ldws_attribute;
    MMP_LONG  ulAlert;

    ADAS_CTL_GetLDWSAttr(&cur_ldws_attribute, &ulAlert);

    #if (OSD_SHOW_LDWS_ALARM)
    if (ulAlert == LDWS_STATE_DEPARTURE_LEFT)
    {   // Left Shift
        AHC_WMSG_Draw(AHC_TRUE, WMSG_LDWS_LeftShift, 1);
        #ifdef OSD_SHOW_LDWS_ALARM_WITH_MULTI_AUDIO
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_ATTENTION);
        #endif
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_LDWS_WARNING);
    }
    else if(ulAlert == LDWS_STATE_DEPARTURE_RIGHT)
    {   // Right Shift
        AHC_WMSG_Draw(AHC_TRUE, WMSG_LDWS_RightShift, 1);
        #ifdef OSD_SHOW_LDWS_ALARM_WITH_MULTI_AUDIO
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_ATTENTION);
        #endif
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_LDWS_WARNING);
    }
    #endif
}
#endif

#if (ENABLE_ADAS_FCWS)
extern void DrawVideo_FCWSWarn(int ldws_state, AHC_BOOL bDraw);

void VideoFunc_FCWSWarn(void)
{
    AHC_PlaySoundEffect(AHC_SOUNDEFFECT_FCWS_WARNING);
    DrawVideo_FCWSWarn(0, AHC_TRUE);
}
#endif

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_RECORDTIME_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_RECORDRES_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_FILE_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_PICTURE_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_GSENSOR_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_AUDIO_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_STATUS_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_REC_MODE_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_FIRMWARE_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_MMC_CONTROL)
{
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_SWITCH_MSDC_MODE)
{
    AHC_USB_DisConnectDevice();

    AHC_DBG_MSG(1,  "Set AHC idle mode...\r\n");
    AHC_DBG_MSG(1,  "Set USB MSDC mode...\r\n");

    StateSwitchMode(UI_MSDC_STATE);
}
#endif

#if (VIDEO_DIGIT_ZOOM_EN)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_TELE_PRESS_LCD)
{
    AHC_BOOL    ret = AHC_TRUE;

    if((!bZoomStop)&&(bZoomDirect == AHC_SENSOR_ZOOM_OUT)){
        VideoFunc_ZoomOperation(AHC_SENSOR_ZOOM_STOP);
        bZoomStop = AHC_TRUE;
    }

    if(bZoomStop){
        ret = VideoFunc_ZoomOperation(AHC_SENSOR_ZOOM_IN);
        bZoomStop = AHC_FALSE;
        bZoomDirect = AHC_SENSOR_ZOOM_IN;
        DrawStateVideoRecUpdate(EVENT_KEY_TELE_PRESS);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_WIDE_PRESS_LCD)
{
    AHC_BOOL    ret = AHC_TRUE;

    if((!bZoomStop)&&(bZoomDirect == AHC_SENSOR_ZOOM_IN)){
        ret = VideoFunc_ZoomOperation(AHC_SENSOR_ZOOM_STOP);
        if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, ret); }

        bZoomStop = AHC_TRUE;
    }

    if(bZoomStop){
        ret = VideoFunc_ZoomOperation(AHC_SENSOR_ZOOM_OUT);
        if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, ret); }

        bZoomStop = AHC_FALSE;
        bZoomDirect = AHC_SENSOR_ZOOM_OUT;
        DrawStateVideoRecUpdate(EVENT_KEY_WIDE_PRESS);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_WIDE_STOP_LCD)
{
    AHC_BOOL    ret = AHC_TRUE;

    ret = VideoFunc_ZoomOperation(AHC_SENSOR_ZOOM_STOP);
    if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, ret); }

    bZoomStop = AHC_TRUE;
    DrawStateVideoRecUpdate(EVENT_KEY_WIDE_STOP);
}
#endif

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_EV_INCREASE_LCD)
{
    AHC_ChangeEV(AHC_FALSE, 1);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_EV_DECREASE_LCD)
{
    AHC_ChangeEV(AHC_FALSE, 0);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_LEFT_LCD)
{
    AHC_ChangeEV(AHC_TRUE, 0);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_RIGHT_LCD)
{
    AHC_ToggleFlashLED(LED_MODE_AUTO_ON_OFF);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_SET_LCD)
{
    UINT32      CurSysMode;

    AHC_GetSystemStatus(&CurSysMode);

    if( (CurSysMode == ((AHC_MODE_VIDEO_RECORD<<16)|AHC_SYS_VIDRECD_PAUSE)) ){
        VideoFunc_RecordResume();
        DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD);
    }
    else if((CurSysMode == ((AHC_MODE_VIDEO_RECORD<<16)|AHC_SYS_VIDRECD_RESUME)) ||
        (CurSysMode == ((AHC_MODE_VIDEO_RECORD<<16)|AHC_SYS_VIDRECD_START)) ) {
        VideoFunc_RecordPause();
        DrawStateVideoRecUpdate(EVENT_KEY_SET);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_MENU_LCD)
{
#if CR_USE_STATE_SWITCH_SUB_MODE == 0
    AHC_BOOL    ret = AHC_TRUE;
    UI_STATE_ID ubParentUIState = 0;
#endif

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    if(AHC_STREAM_OFF != AHC_GetStreamingMode())
        return;//break;
#endif

    g_bDrawUnfix = MMP_FALSE;

    if (!VideoFunc_GetRecordStatus())
    {
        // Clean downcount screen
#if MOTION_DETECTION_EN
        if (m_ulVMDRemindTime)
        UpdateMotionRemindTime(-1);
#endif

#if 0
        DrawStateVideoRecUpdate(EVENT_KEY_MENU);
        VideoTimer_Stop();
#endif

#if CR_USE_STATE_SWITCH_SUB_MODE
        StateReplaceSubMode(UI_VIDEO_MENU_STATE);
#else
        StateModeGetParent(uiGetCurrentState(), &ubParentUIState);
        if(UI_STATE_UNSUPPORTED != ubParentUIState){
            AHC_DBG_MSG(1, "%s,%d, DettachSubMode:%d\r\n", __FUNCTION__, __LINE__, uiGetCurrentState());
            ret = StateDetachSubMode();
            if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, ret);}
        }
        StateAttachSubMode(UI_VIDEO_MENU_STATE);
        if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ret); }
#endif
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_MODE_LCD)
{
    AHC_BOOL    ret = AHC_TRUE;

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
    if(AHC_STREAM_OFF != AHC_GetStreamingMode())
        return;//break;
    #endif

    AHC_PauseKeyUI();

    if(!VideoFunc_GetRecordStatus())
    {
        DrawStateVideoRecUpdate(EVENT_KEY_MODE);
        VideoTimer_Stop();

        gbWinExchangedCnt = F_LARGE_R_SMALL;

        #if (VR_PREENCODE_EN)
        bDisableVideoPreRecord = AHC_TRUE;
        #endif

        #if (MOTION_DETECTION_EN)
        // Reset MVD downcount to zero when switch to DSC mode
        if (m_ubInRemindTime) {
            m_ulVMDRemindTime = 0;
            m_ubInRemindTime = 0;
        }
        #endif

        #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
        if( uiGetParkingModeEnable() == AHC_TRUE )
        {
            uiSetParkingModeEnable( AHC_FALSE );
            AHC_VIDEO_SetRecordMode(AHC_VIDRECD_STOP);
            AHC_VIDEO_SetRecordMode(AHC_VIDRECD_IDLE);
        }
        #endif

        #if (DSC_MODE_ENABLE)
        ret = StateSwitchMode(UI_CAMERA_STATE);
        #else
        ret = StateSwitchMode(UI_BROWSER_STATE);
        #endif
        if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ret); }
    }

    AHC_ResumeKeyUI();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_ENTER_NET_PLAYBACK_LCD)
{
    AHC_PauseKeyUI();

    if (VideoFunc_GetRecordStatus())
    {
        #ifdef CFG_ENABLE_MIN_VR_TIME
        // For min VR time
        UINT32 ulTime = CFG_ENABLE_MIN_VR_TIME;

        AHC_VIDEO_GetCurRecordingTime(&ulTime);

        if (ulTime < CFG_ENABLE_MIN_VR_TIME)
            AHC_OS_SleepMs(CFG_ENABLE_MIN_VR_TIME - ulTime);
        #endif

        StateVideoRecMode_StopRecordingProc(EVENT_NET_ENTER_PLAYBACK);
    }


    DrawStateVideoRecUpdate(ulEvent);
    VideoTimer_Stop();

    #if (VR_PREENCODE_EN)
    bDisableVideoPreRecord = AHC_TRUE;
    #endif

    #if (MOTION_DETECTION_EN)
    // Reset MVD downcount to zero when switch to DSC mode
    if (m_ubInRemindTime) {
        m_ulVMDRemindTime = 0;
        m_ubInRemindTime = 0;
    }
    #endif

    #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
    if( uiGetParkingModeEnable() == AHC_TRUE )
    {
        uiSetParkingModeEnable( AHC_FALSE );
        AHC_VIDEO_SetRecordMode(AHC_VIDRECD_STOP);
        AHC_VIDEO_SetRecordMode(AHC_VIDRECD_IDLE);
    }
    #endif

    StateSwitchMode(UI_NET_PLAYBACK_STATE);

    AHC_ResumeKeyUI();

    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_KEY_RECORD_LCD)
{
    AHC_BOOL ahcRet = AHC_TRUE;

#if (FS_FORMAT_FREE_ENABLE)
    if (SystemSettingConfig()->byNeedToFormatMediaAsFormatFree > 0) {
        AHC_DBG_MSG(1, FG_RED("MediaError!!! Need to format media as FORMAT FREE type!!!\r\n"));
        return;
    }
#endif

    if (bAudioRecording) {
        return;
    }

    AHC_PauseKeyUI();

    if (VideoFunc_GetRecordStatus()) {
        #ifdef CFG_ENABLE_MIN_VR_TIME
        // For min VR time
        UINT32 ulTime = CFG_ENABLE_MIN_VR_TIME;

        AHC_VIDEO_GetCurRecordingTime(&ulTime);

        if (ulTime < CFG_ENABLE_MIN_VR_TIME)
            AHC_OS_SleepMs(CFG_ENABLE_MIN_VR_TIME - ulTime);
        #endif

        ahcRet = StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);

        if (uiGetParkingModeEnable() == AHC_TRUE) {
            DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);
            // Enter pre-encode.
            ahcRet = VideoFunc_PreRecord();
            DrawVideoParkingMode(uiGetParkingModeEnable());
            uiSetParkingModeRecord(AHC_FALSE);
        }
    }
    else {
        ahcRet = StateVideoRecMode_StartRecordingProc(EVENT_VIDEO_KEY_RECORD);
    }

    AHC_ResumeKeyUI();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_KEY_PLAYBACK_MODE_LCD)
{
    AHC_BOOL    ret = AHC_TRUE;

    if(!VideoFunc_GetRecordStatus())
    {
        DrawStateVideoRecUpdate(EVENT_KEY_PLAYBACK_MODE);
        VideoTimer_Stop();

#if (VR_PREENCODE_EN)
        bDisableVideoPreRecord = AHC_TRUE;
#endif
        ret = StateSwitchMode(UI_BROWSER_STATE);
        if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ret); }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_POWER_OFF_LCD)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

    AHC_PauseKeyUI();

    if (VideoFunc_GetRecordStatus()) {
        ahcRet = VideoFunc_RecordStop();
        if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ahcRet); }

        DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);
        AHC_OS_Sleep(100);
    }
    else if (uiGetParkingModeEnable() == AHC_TRUE) {
        ahcRet = VideoFunc_ParkingModeStop();
        if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ahcRet); }
    }

#ifdef CFG_BOOT_CLEAR_ICON_WHEN_OFF //may be defined in config_xxx.h
    //If LCD gets poor quality, and icons is sticky
    //Need to clear icons
    DrawStateVideoRecClearIcon();
#endif

    AHC_PowerOff_NormalPath();
    AHC_ResumeKeyUI();

    ahcRet = StateSwitchMode(UI_VIDEO_STATE);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ahcRet); }

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
    if (AHC_TRUE == AHC_WiFi_Switch(AHC_TRUE)) {
        Setpf_WiFi(WIFI_MODE_ON);
        // Need save menusetting to Flash - TBD
    }
    #endif

    LedCtrl_LcdBackLight(AHC_TRUE);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_CHANGE_LED_MODE_LCD)
{
#if (LED_FLASH_CTRL!=LED_BY_NONE)
    AHC_ToggleFlashLED(LED_MODE_ON_OFF);
#endif
}

#ifdef LED_GPIO_LASER
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LASER_LED_ONOFF_LCD)
{
    if (LED_GPIO_LASER != MMP_GPIO_MAX)
    {
        static MMP_UBYTE flag = AHC_FALSE;

        if(!flag)
        {
            LedCtrl_LaserLed(LED_GPIO_LASER_ACT_LEVEL);
            flag = AHC_TRUE;
        }
        else
        {
            LedCtrl_LaserLed(!LED_GPIO_LASER_ACT_LEVEL);
            flag = AHC_FALSE;
        }
    }
}
#endif

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_FORMAT_MEDIA_LCD)
{
#if (QUICK_FORMAT_SD_EN || POWER_ON_BUTTON_ACTION)
    AHC_DBG_MSG(1, ">>> EVENT_FORMAT_MEDIA or EVENT_FORMAT_RESET_ALL\n");

    if( VideoFunc_GetRecordStatus() )
    {
        StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);

        AHC_OS_SleepMs(500);
        QuickMediaOperation(MEDIA_CMD_FORMAT);

        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_VIDEO_RECORD, 0);
    }
    else
    {
        QuickMediaOperation(MEDIA_CMD_FORMAT);
    }
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_KEY_CAPTURE_LCD)
{
#ifdef KEY_CAPATURE_SWITCH_VIDEO //may be defined in config_xxx.h
    AHC_BOOL    ret = AHC_TRUE;
#endif
    if (AHC_SDMMC_BasicCheck() == AHC_FALSE || AHC_SDMMC_IsSD1MountDCF() == AHC_FALSE) {
        #if (USE_SHUTTER_SOUND)
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
        #endif
        // Call trigger the op is failed!!
        VideoFunc_ShutterFail();

        return;//break;
    }

    AHC_PauseKeyUI();

//Switch to DSC Mode then switch back
#ifdef KEY_CAPATURE_SWITCH_VIDEO //may be defined in config_xxx.h
    if(!VideoFunc_GetRecordStatus())
    {
        DrawStateVideoRecUpdate(EVENT_KEY_MODE);
        VideoTimer_Stop();

        #if (VR_PREENCODE_EN)
        bDisableVideoPreRecord = AHC_TRUE;
        #endif

        ret = StateSwitchMode(UI_CAMERA_STATE);

        if(ret)
            SetKeyPadEvent(KEY_DSC_CAPTURE);
        else
            VideoFunc_Shutter();
    }
    else
#endif
    {
        DCF_DB_TYPE sType = AHC_UF_GetDB();
        AHC_BOOL bSuccess;
        int LockRet;
        #if (DCF_DB_COUNT >= 4)
        AHC_UF_SelectDB(DCF_DB_TYPE_DB3_PHOTO);
        #endif

        #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        LockRet = netapp_cap_lock(LOCK_CAPTURE, LOCK_CAPTURE_TIMEOUT);
        if (0) {
            AHC_SetStreamingMode(AHC_STREAM_PAUSE);
        }
        #endif

        #if (USE_SHUTTER_SOUND)
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_SHUTTER);
        #endif

        #ifdef CFG_CAPTURE_WITH_VIBRATION
        AHC_Vibration_Enable(CFG_CAPTURE_VIBRATION_TIME);
        #endif

        #ifdef CFG_CAPTURE_WITH_KEY_LED_CAPTURE
        LedCtrl_ButtonLed(KEY_LED_CAPTURE, AHC_TRUE);
        #endif

        DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_CAPTURE);
        bSuccess = VideoFunc_Shutter();

        #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        if(LockRet == 0)
            netapp_cap_lock(UNLOCK_CAPTURE, 0);
        if (0) {
            AHC_SetStreamingMode(AHC_STREAM_RESUME);
        }
        ncgi_op_feedback((void*)ulEvent, (int)(bSuccess? 0:-1)) ;//netapp_CGIOpFeedback((void*)ulEvent, (int)(bSuccess? 0:-1)) ;
        #endif

        if (VideoFunc_GetRecordStatus()) {
            DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD);
        } else {
            DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);
        }

        AHC_UF_SelectDB(sType);
    }

    AHC_ResumeKeyUI();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_RECORD_MUTE_LCD)
{
    AHC_ToggleMute();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LCD_POWER_SAVE_LCD)
{
    AHC_SwitchLCDBackLight();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_CUS_SW1_ON_LCD)
{
    if(!VideoFunc_GetRecordStatus())
    {
        AHC_DBG_MSG(1, "MenuSettingConfig()->uiMOVSize %d\n", MenuSettingConfig()->uiMOVSize);
        if(MenuSettingConfig()->uiMOVSize == MOVIE_SIZE_1080P)
        {
            MenuSettingConfig()->uiMOVSize= MOVIE_SIZE_720_60P;
            AHC_SetMode(AHC_MODE_IDLE);
            VideoFunc_Preview();
        }
    }
}

void STATE_VIDEO_REC_MODE_EVENT_CUS_SW1_OFF_LCD(UINT32 ulEvent)
{
    if(!VideoFunc_GetRecordStatus())
    {
        AHC_DBG_MSG(1, "MenuSettingConfig()->uiMOVSize %d\n", MenuSettingConfig()->uiMOVSize);
        if(MenuSettingConfig()->uiMOVSize == MOVIE_SIZE_720_60P)
        {
            MenuSettingConfig()->uiMOVSize= MOVIE_SIZE_1080P;   //MOVIE_SIZE_720P;
            AHC_SetMode(AHC_MODE_IDLE);
            VideoFunc_Preview();
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_CHANGE_NIGHT_MODE_LCD)
{
    AHC_ToggleTwilightMode();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_ALL_BROWSER_LCD)
{
    if(!VideoFunc_GetRecordStatus())
    {
        DrawStateVideoRecUpdate(EVENT_KEY_PLAYBACK_MODE);
        VideoTimer_Stop();

        #if (VR_PREENCODE_EN)
        bDisableVideoPreRecord = AHC_TRUE;
        #endif

        if(ulEvent==EVENT_CAMERA_BROWSER)
            SetCurrentOpMode(JPGPB_MODE);
        else if(ulEvent==EVENT_VIDEO_BROWSER)
            SetCurrentOpMode(MOVPB_MODE);
        else if(ulEvent==EVENT_ALL_BROWSER)
            SetCurrentOpMode(JPGPB_MOVPB_MODE);

        StateSwitchMode(UI_BROWSER_STATE);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_CAMERA_PREVIEW_LCD)
{
    AHC_BOOL    ret = AHC_TRUE;

    if(!VideoFunc_GetRecordStatus())
    {
        DrawStateVideoRecUpdate(EVENT_KEY_MODE);
        VideoTimer_Stop();

        #if (VR_PREENCODE_EN)
        bDisableVideoPreRecord = AHC_TRUE;
        #endif

        ret = StateSwitchMode(UI_CAMERA_STATE);
        if(ret != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ret); }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_AUDIO_RECORD_LCD)
{
    if(VideoFunc_GetRecordStatus())
        return;//break;

    if(bAudioRecording)
    {
        if(AHC_RecordAudioCmd(AHC_AUDIO_CODEC_MP3, AHC_AUDIO_RECORD_STOP))
        {
            bAudioRecording = AHC_FALSE;
            DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);
        }
    }
    else
    {
        if(AHC_SDMMC_BasicCheck()==AHC_FALSE)
            return;//break;

        if(AHC_RecordAudioCmd(AHC_AUDIO_CODEC_MP3, AHC_AUDIO_RECORD_START))
        {
            bAudioRecording = AHC_TRUE;
            DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD);
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SWITCH_VMD_MODE_LCD)
{
#if (MOTION_DETECTION_EN)


    if (!m_ubMotionDtcEn &&
#if VR_PREENCODE_EN
        !m_ubPreEncodeEn &&
#endif
        1)
    {
        VideoFunc_EnterVMDMode();

#ifdef CFG_LCD_RESET_POWER_SAVER_IN_VMD //may be defined in config_xxx.h
        LCDPowerSaveCounterReset();
#endif
    }
    else
    {
        VideoFunc_ExitVMDMode();

#ifdef CFG_LCD_RESET_POWER_SAVER_IN_VMD //may be defined in config_xxx.h
        LCDPowerSaveCounterReset();
#endif
    }
#endif

}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SWITCH_PANEL_TVOUT_LCD)
{
    AHC_SwitchLCDandTVOUT();
}

#if (SUPPORT_TOUCH_PANEL) && !defined(_OEM_TOUCH_)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SWITCH_TOUCH_PAGE_LCD)
{
    m_ubShowVRTouchPage ^= 1;

    if(m_ubShowVRTouchPage)
    {
        KeyParser_ResetTouchVariable();
        KeyParser_TouchItemRegister(&VideoCtrlPage_TouchButton[0], ITEMNUM(VideoCtrlPage_TouchButton));

        DrawVideoRecStatePageSwitch(TOUCH_CTRL_PAGE);
    }
    else
    {
        KeyParser_ResetTouchVariable();
        KeyParser_TouchItemRegister(&VideoMainPage_TouchButton[0], ITEMNUM(VideoMainPage_TouchButton));

        DrawVideoRecStatePageSwitch(TOUCH_MAIN_PAGE);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_TOUCH_MENU_LCD)
{
    //TBD
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_TOUCH_MODE_LCD)
{
    //TBD
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_TOUCH_RECORD_PRESS_LCD)
{
    //TBD
}
#endif

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_EVENT_DC_CABLE_IN_LCD)
{
#if defined(VMD_EN_BY_CHARGER_OUT)
    VideoFunc_ExitVMDMode();
    LedCtrl_LcdBackLight(AHC_TRUE);
#endif

#if (CHARGER_IN_ACT_VIDEO_MODE==ACT_RECORD_VIDEO)
    if(VideoFunc_GetRecordStatus()==AHC_FALSE)
        AHC_SetRecordByChargerIn(3);
#elif (CHARGER_IN_ACT_VIDEO_MODE == ACT_FORCE_POWER_OFF)
    SetKeyPadEvent(KEY_POWER_OFF);
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_DC_CABLE_OUT_LCD)
{
    AHC_Charger_SetEnable(AHC_FALSE);

    #if defined(VMD_EN_BY_CHARGER_OUT)
    if(MenuSettingConfig()->uiMotionDtcSensitivity != MOTION_DTC_SENSITIVITY_OFF)
    {
        LedCtrl_LcdBackLight(AHC_FALSE);
        if( VideoFunc_GetRecordStatus() )
        {
            VideoFunc_RecordStop();
            AHC_OS_Sleep(100);
        }

        VideoFunc_EnterVMDMode();
    }
    else
    #endif
    {
        if( VideoFunc_GetRecordStatus() )
        {
            #if (CHARGER_OUT_ACT_VIDEO_REC==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_VIDEO_REC==ACT_DELAY_POWER_OFF)
            AHC_SetShutdownByChargerOut(AHC_TRUE);
            #endif
        }
        else
        {
            #if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
            AHC_SetShutdownByChargerOut(AHC_TRUE);
            #endif
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_USB_DETECT_LCD)
{
    if (!AHC_IsUsbConnect()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return;}

    if (IsAdapter_Connect())
    {
    #ifdef CFG_REC_IGNORE_USB //may be defined in config_xxx.h
        if (VideoFunc_GetRecordStatus()) {
            // Video Recording to ignore USB Charger
            return;//break;
        }
        else {
            //Power Off
        }
    #else
        #if defined(VMD_EN_BY_CHARGER_OUT)
        VideoFunc_ExitVMDMode();
        LedCtrl_LcdBackLight(AHC_TRUE);
        #endif

        #if (CHARGER_IN_ACT_VIDEO_MODE == ACT_RECORD_VIDEO)
        if (VideoFunc_GetRecordStatus()==AHC_FALSE)
            AHC_SetRecordByChargerIn(3);
        #elif (CHARGER_IN_ACT_VIDEO_MODE == ACT_FORCE_POWER_OFF)
        SetKeyPadEvent(KEY_POWER_OFF);
        #endif
    #endif
    }
    else
    {
        #if (SUPPORT_UVC_FUNC)
        if (MMP_TRUE == pcam_usb_get_mix_mode()) {
            AHC_SetUsbMode(AHC_USB_MODE_WEBCAM);
        }
        else
        #endif
        {
            #ifdef CFG_REC_IGNORE_USB //may be defined in config_xxx.h
            if (VideoFunc_GetRecordStatus()) {
                // Video Recording to ignore USB
                return;//break;
            }
            else {
                VideoTimer_Stop();
            }
            #else
            if (VideoFunc_GetRecordStatus())
            {
                StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
                AHC_VIDEO_WaitVideoWriteFileFinish();
            }

            VideoTimer_Stop();
            #endif

            #if (VR_PREENCODE_EN)
            bDisableVideoPreRecord = AHC_TRUE;
            #endif

            #if (USB_MODE_SELECT_EN)
            if (MMPS_USB_NORMAL == MMPS_USB_GetStatus()) {
                if (AHC_GetQuickKey(QUICK_PCCAM)) {
                    extern AHC_BOOL bUsbForcePCAM;
                    printc(FG_YELLOW("======================== UI_PCCAM_STATE =================\r\n"));
                    bUsbForcePCAM = AHC_TRUE;
                    #if (USB_MODE_SELECT_EN)
                    USBSelectModePCam(NULL,0);
                    #endif
                    StateSwitchMode(UI_PCCAM_STATE);
                } 
                else { 
                    StateSwitchMode(UI_USBSELECT_MENU_STATE);
                }
            }
            else
            {
                #ifdef CFG_POWER_ON_ENTER_CAMERA_STATE
                StateSwitchMode(UI_CAMERA_STATE);
                #else
                StateSwitchMode(UI_VIDEO_STATE);
                #endif
            }
             #else
            if(MenuSettingConfig()->uiUSBFunction == MENU_SETTING_USB_MSDC)
            {
                StateSwitchMode(UI_MSDC_STATE);
            }
            else
            {
                StateSwitchMode(UI_PCCAM_STATE);
            }
            #endif
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_USB_REMOVED_LCD)
{
    /* In Video state, the event should always be USB adapter out,
     * the real USB plug-out event should be received in MSDC state.
     *
     * The function AHC_USB_GetLastStatus() may return wrong status,
     * when USB plug-in/out then adapter plug-in.
     *
     */
    if (AHC_IsDcCableConnect() == AHC_TRUE)
        return;//break;

    AHC_Charger_SetEnable(AHC_FALSE);
    #if defined(VMD_EN_BY_CHARGER_OUT)
    if(MenuSettingConfig()->uiMotionDtcSensitivity != MOTION_DTC_SENSITIVITY_OFF)
    {
        LedCtrl_LcdBackLight(AHC_FALSE);

        if( VideoFunc_GetRecordStatus() )
        {
            VideoFunc_RecordStop();
            AHC_OS_Sleep(100);
        }

        VideoFunc_EnterVMDMode();
    }
    else
    #endif
    {
        if( VideoFunc_GetRecordStatus() )
        {
            #if (CHARGER_OUT_ACT_VIDEO_REC==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_VIDEO_REC==ACT_DELAY_POWER_OFF)
            AHC_SetShutdownByChargerOut(AHC_TRUE);
            #endif
        }
        else
        {
            #if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
            AHC_SetShutdownByChargerOut(AHC_TRUE);
            #endif
        }
    }

    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) )
    {
        AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_AHC_DONE);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVNET_SUB_MODE_ENTER_LCD)
{
    //NOP
    gbVideoInSubMode = AHC_TRUE;
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVNET_SUB_MODE_EXIT_LCD)
{
    MMP_UBYTE   ubNightMode;
    UINT32      ulNightMode = 0;

    gbVideoInSubMode = AHC_FALSE;
    g_bDrawUnfix = MMP_FALSE;
    //DrawStateVideoRecUpdate(EVENT_LCD_COVER_NORMAL); //TBD. Clear OSD buffer and reset transparent color.
}


DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDEO_KEY_SWAP_PIP_LCD)
{
    UINT16 u16DispW, u16DispH, u16RearW, u16RearH;
    AHC_BOOL bMirror = SCD_CAM_PREVIEW_MIRROR;
    MMP_UBYTE ubUiMode = MMPS_PREVIEW_UI_MODE_VR;

    if (MMP_IsUSBCamExist()) {

        UINT8                   action = 1;
        USB_DETECT_PHASE        USBCurrentStates = 0;

        AHC_DBG_MSG(1, "EVENT_VIDEO_KEY_SWAP_PIP \n");

        AHC_USBGetStates(&USBCurrentStates, AHC_USB_GET_PHASE_CURRENT);

        if (USBCurrentStates == USB_DETECT_PHASE_REAR_CAM) {
            action = 0;
        }

        if (action == 0)
        {
            gbWinExchangedCnt++;

            switch (gbWinExchangedCnt % PIP_SWAP_TYPE_NUM)
            {
                case F_LARGE_R_SMALL:
                    AHC_DBG_MSG(1, "F_LARGE_R_SMALL\r\n");
                    u16DispW = RTNA_LCD_GetAttr()->usPanelW;
                    u16DispH = RTNA_LCD_GetAttr()->usPanelH;
                    u16RearW = PIP_WIDTH;
                    u16RearH = PIP_HEIGHT;
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, u16DispW, u16DispH);
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_UVC, AHC_TRUE, bMirror, 0, 0, u16RearW, u16RearH);
                    MMPS_Display_SetUsbCamPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_FULL_USBH_PIP);
                    break;
                case F_SMALL_R_LARGE:
                    AHC_DBG_MSG(1, "F_SMALL_R_LARGE\r\n");
                    u16DispW = PIP_WIDTH;
                    u16DispH = PIP_HEIGHT;
                    u16RearW = RTNA_LCD_GetAttr()->usPanelW;
                    u16RearH = RTNA_LCD_GetAttr()->usPanelH;
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, u16DispW, u16DispH);
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_UVC, AHC_TRUE, bMirror, 0, 0, u16RearW, u16RearH);
                    MMPS_Display_SetUsbCamPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_PIP_USBH_FULL);
                    break;
                case ONLY_FRONT:
                    AHC_DBG_MSG(1, "ONLY_FRONT\r\n");
                    u16DispW = RTNA_LCD_GetAttr()->usPanelW;
                    u16DispH = RTNA_LCD_GetAttr()->usPanelH;
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, u16DispW, u16DispH);
                    MMPS_Display_SetUsbCamPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_FULL_USBH_NONE);
                    break;
                case ONLY_REAR:
                    AHC_DBG_MSG(1, "ONLY_REAR\r\n");
                    u16RearW = RTNA_LCD_GetAttr()->usPanelW;
                    u16RearH = RTNA_LCD_GetAttr()->usPanelH;
                    AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_UVC, AHC_TRUE, bMirror, 0, 0, u16RearW, u16RearH);
                    MMPS_Display_SetUsbCamPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_NONE_USBH_FULL);
                    break;
            }
        }
    }
    else if ((CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) ||
             (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR))  ||
             (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))) {
        UINT8 action = 1;

        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {

            MMP_SNR_ANADEC_SRC_TYPE eAnaDecCurSrc = 0;

            MMPS_Sensor_GetAnaDecSrcType(&eAnaDecCurSrc);

            if ((eAnaDecCurSrc != MMP_SNR_ANADEC_SRC_DISCNT) &&
                (eAnaDecCurSrc != MMP_SNR_ANADEC_SRC_NO_READY)) {
                action = 0;
            }
        }
        else {
            action = 0;
        }

        AHC_DBG_MSG(1, "EVENT_VIDEO_KEY_SWAP_PIP \n");

        if (action == 0) {
            gbWinExchangedCnt++;

            switch (gbWinExchangedCnt % PIP_SWAP_TYPE_NUM) {
            case F_LARGE_R_SMALL:
                AHC_DBG_MSG(1, "F_LARGE_R_SMALL \r\n");
                u16DispW = RTNA_LCD_GetAttr()->usPanelW;
                u16DispH = RTNA_LCD_GetAttr()->usPanelH;
                u16RearW = PIP_WIDTH;
                u16RearH = PIP_HEIGHT;
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, u16DispW, u16DispH);
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_SCD, AHC_TRUE, bMirror, 0, 0, u16RearW, u16RearH);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    MMPS_Display_SetScdBayerPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_FULL_SCD_PIP);
                else
                    MMPS_Display_SetScdAnaDecPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_FULL_SCD_PIP);
                break;
            case F_SMALL_R_LARGE:
                AHC_DBG_MSG(1, "F_SMALL_R_LARGE \r\n");
                u16DispW = PIP_WIDTH;
                u16DispH = PIP_HEIGHT;
                u16RearW = RTNA_LCD_GetAttr()->usPanelW;
                u16RearH = RTNA_LCD_GetAttr()->usPanelH;
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, u16DispW, u16DispH);
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_SCD, AHC_TRUE, bMirror, 0, 0, u16RearW, u16RearH);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    MMPS_Display_SetScdBayerPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_PIP_SCD_FULL);
                else
                    MMPS_Display_SetScdAnaDecPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_PIP_SCD_FULL);
                break;
            case ONLY_FRONT:
                AHC_DBG_MSG(1, "ONLY_FRONT \r\n");
                u16DispW = RTNA_LCD_GetAttr()->usPanelW;
                u16DispH = RTNA_LCD_GetAttr()->usPanelH;
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, u16DispW, u16DispH);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    MMPS_Display_SetScdBayerPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_FULL_SCD_NONE);
                else
                    MMPS_Display_SetScdAnaDecPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_FULL_SCD_NONE);
                break;
            case ONLY_REAR:
                AHC_DBG_MSG(1, "ONLY_REAR \r\n");
                u16RearW = RTNA_LCD_GetAttr()->usPanelW;
                u16RearH = RTNA_LCD_GetAttr()->usPanelH;
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_SCD, AHC_TRUE, bMirror, 0, 0, u16RearW, u16RearH);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    MMPS_Display_SetScdBayerPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_NONE_SCD_FULL);
                else
                    MMPS_Display_SetScdAnaDecPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_NONE_SCD_FULL);
                break;
            case F_HALF_R_HALF:
                AHC_DBG_MSG(1, "F_HALF_R_HALF \r\n");
                u16DispW = RTNA_LCD_GetAttr()->usPanelW;
                u16DispH = RTNA_LCD_GetAttr()->usPanelH;
                u16RearW = RTNA_LCD_GetAttr()->usPanelW;
                u16RearH = RTNA_LCD_GetAttr()->usPanelH;
                if (RTNA_LCD_GetAttr()->usPanelW > RTNA_LCD_GetAttr()->usPanelH) {
                    u16DispW = u16DispW >> 1;
                    u16RearW = u16RearW >> 1;
                }
                else {
                    u16DispH = u16DispH >> 1;
                    u16RearH = u16RearH >> 1;
                }
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, u16DispW, u16DispH);
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_SCD, AHC_TRUE, bMirror, 0, 0, u16RearW, u16RearH);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    MMPS_Display_SetScdBayerPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_HALF_SCD_HALF);
                else
                    MMPS_Display_SetScdAnaDecPreviewPIPType(ubUiMode, MMPS_DISPLAY_PRM_HALF_SCD_HALF);
                break;
            }
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SD_DETECT_LCD)
{
    #if (FS_FORMAT_FREE_ENABLE)
    SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 0; //Reset it in case user plug-in correct card
    if (AHC_CheckMedia_FormatFree(AHC_MEDIA_MMC) == AHC_FALSE)
    {
        SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 1;
    }
    else
    #endif
    {
        AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
        DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);
    }

    AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8 *) VIDEO_DEFAULT_FLIE_FREECHAR);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SD_REMOVED_LCD)
{
    if (VideoFunc_GetRecordStatus())
    {
        if (VideoFunc_LockFileEnabled()) {
            #if (LIMIT_MAX_LOCK_FILE_NUM)
            m_ulLockEventNum--;
            #endif
            EnableLockFile(AHC_FALSE, 0);
            AHC_Protect_SetType(AHC_PROTECT_NONE);
        }
        StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_CARD, 3);
    }

    if (AHC_TRUE == AHC_SDMMC_IsSD1MountDCF())
    {
        AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
        Enable_SD_Power(0 /* Power Off */);
    }

    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE))
    {
        AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_AHC_DONE);
    }
}

#if (TVOUT_ENABLE)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_TV_DETECT_LCD)
{
    StateSwitchMode(UI_VIDEO_STATE);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_TV_REMOVED_LCD)
{
    bShowTvWMSG = AHC_TRUE;
    StateSwitchMode(UI_VIDEO_STATE);
}
#endif

#if (HDMI_ENABLE)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_HDMI_DETECT_LCD)
{
    StateSwitchMode(UI_VIDEO_STATE);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_HDMI_REMOVED_LCD)
{
    bShowHdmiWMSG = AHC_TRUE;

    StateSwitchMode(UI_VIDEO_STATE);

    //RTNA_LCD_Backlight(MMP_TRUE);
}
#endif

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LCD_COVER_OPEN_LCD)
{
    if (!LedCtrl_GetBacklightStatus())
        LedCtrl_LcdBackLight(AHC_TRUE);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LCD_COVER_CLOSE_LCD)
{
    LedCtrl_LcdBackLight(AHC_FALSE);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LCD_COVER_NORMAL_LCD)
{
    AHC_DrawRotateEvent(ulEvent);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_MEDIA_FULL_LCD)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    #if defined(CFG_VR_DISABLE_CYCLING_RECORDING)
    // No cycling record mode
    if (1)
    #else
    if (MenuSettingConfig()->uiMOVClipTime == MOVIE_CLIP_TIME_OFF)
    #endif
    {
        ahcRet = StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_STORAGE_FULL, 3);
        #ifdef CFG_CUS_HANDLER_VR_MEDIA_FULL
        CFG_CUS_HANDLER_VR_MEDIA_FULL();
        #endif
    }
    else
    {
        //For Seamless Exception
        ahcRet = StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
        m_u32UiRecordTimeOffset = 0;
        ahcRet = StateVideoRecMode_StartRecordingProc(EVENT_VIDEO_KEY_RECORD);

        DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD);
    }

    if (AHC_GetCurKeyEventID() == BUTTON_VRCB_MEDIA_FULL) {
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else {
        AHC_DBG_ERR(1, "BUTTON_VRCB_MEDIA_FULL Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_FILE_FULL_LCD)
{
    AHC_BOOL ahcRet = AHC_FALSE;

    if (AHC_VIDEO_IsVRSeamless() == AHC_FALSE) {

        StateVideoRecMode_StopRecordingProc(EVENT_VRCB_FILE_FULL);
        DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);

        if (uiGetParkingModeEnable() == AHC_TRUE) {
            DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);
            // Enter pre-encode.
            ahcRet = VideoFunc_PreRecord();
            DrawVideoParkingMode(uiGetParkingModeEnable());
            uiSetParkingModeRecord(AHC_FALSE);
        }
    }
    else {
        if (VideoFunc_RecordRestart() == AHC_FALSE) {
            AHC_DBG_MSG(1, "--E-- VideoFunc_RecordRestart Fail\r\n");
            StateVideoRecMode_StopRecordingProc(EVENT_VRCB_FILE_FULL);
            AHC_ShowErrorDialog(WMSG_STORAGE_FULL);

#ifdef CFG_REC_WD_RESET_AFTER_RESTART_FAIL //may be defined in config_xxx.h
            while (1);  // Let OEM WD reset.
#endif
        }
        else {
            DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD);
        }
    }

    if (AHC_GetCurKeyEventID() == BUTTON_VRCB_FILE_FULL) {
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else {
        AHC_DBG_ERR(1, "BUTTON_VRCB_FILE_FULL Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_SHARE_FILE_FULL_LCD)
{
#if (AHC_SHAREENC_SUPPORT)
    AHC_BOOL                ahcRet = AHC_FALSE;
    AHC_VIDEO_FILENAME_MGR  *pstShareFileNameMgr = NULL;
    DCF_DB_TYPE             eDBType = AHC_UF_GetDB();

    AHC_DBG_MSG(0, "VRCB_SHARE_FILE_FULL_LCD\r\n");

    pstShareFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMSHARE);

    AHC_UF_SelectDB(DCF_DB_FORMAT_FREE_DB);
    ahcRet = AHC_UF_SizeinFile_Update((INT8*)pstShareFileNameMgr->u8FileName);
    ahcRet = AHC_UF_PostAddFile(0, (INT8*)pstShareFileNameMgr->u8FileName);
    AHC_UF_SelectDB(eDBType);

    MEMSET(pstShareFileNameMgr->u8FileName, 0, sizeof(pstShareFileNameMgr->u8FileName));

    m_bAhcFirstShareFile = AHC_FALSE;

    AHC_VIDEO_SetShareRecdStarted(AHC_FALSE);

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
    ncgi_notify_fn(NCGI_SHORT_FN, (char*)pstShareFileNameMgr->u8FullName);
    #endif

    if (AHC_GetCurKeyEventID() == BUTTON_VRCB_SHARE_FILE_FULL) {
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else {
        AHC_DBG_ERR(1, "BUTTON_VRCB_SHARE_FILE_FULL Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
    }
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_LONG_TIME_FILE_FULL_LCD)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, "Long time file full\r\n");
    StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
    VideoFunc_SetRecordStatus(AHC_FALSE);

    DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);

    AHC_DBG_MSG(1, "Long time file full start record\r\n");
    ahcRet = StateVideoRecMode_StartRecordingProc(EVENT_VIDEO_KEY_RECORD);
    if(ahcRet){
        VideoFunc_SetRecordStatus(AHC_TRUE);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_MEDIA_SLOW_LCD)
{
    if (VideoFunc_GetRecordStatus())
    {
        UINT8 bSDClass = 0;

        m_uiSlowMediaCBCnt++;

        if (m_uiSlowMediaCBCnt == SLOW_MEDIA_CB_THD)
        {
            bSDClass = AHC_SDMMC_GetClass(AHC_SD_0);

            if (bSDClass == 0xFF || bSDClass < SLOW_MEDIA_CLASS)
            {
                AHC_DBG_ERR(1, "Slow Media Stop\r\n");
                StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
                DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);
                AHC_ShowErrorDialog(WMSG_CARD_SLOW);
            }
            m_uiSlowMediaCBCnt = 0;
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_RECDSTOP_CARDSLOW_LCD)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, "# Card Slow Stop #\r\n");

    ahcRet = StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
    VideoFunc_SetRecordStatus(AHC_FALSE);

    DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD_STOP);

    if (uiGetParkingModeEnable() == AHC_TRUE) {

        DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);

        AHC_DBG_MSG(1, "# Restart PreRecord\r\n");
        ahcRet = VideoFunc_PreRecord();
        DrawVideoParkingMode(uiGetParkingModeEnable());
    }
    else {

        DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);

        AHC_DBG_MSG(1, "# Restart Record\r\n");
        ahcRet = StateVideoRecMode_StartRecordingProc(EVENT_VIDEO_KEY_RECORD);
        if (ahcRet == AHC_TRUE) {
            VideoFunc_SetRecordStatus(AHC_TRUE);
        }
    }

    if (AHC_GetCurKeyEventID() == BUTTON_VRCB_RECDSTOP_CARDSLOW) {
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else {
        AHC_DBG_ERR(1, "BUTTON_VRCB_RECDSTOP_CARDSLOW Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_SEAM_LESS_LCD)
{
    // Prevent multiple event of Filefull and Seamless
    AHC_BOOL ahcRet = AHC_FALSE;

    if (AHC_VIDEO_IsVRSeamless() == AHC_FALSE) {

        StateVideoRecMode_StopRecordingProc(EVENT_VRCB_FILE_FULL);
        DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);

        if (uiGetParkingModeEnable() == AHC_TRUE) {
            DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);
            // Enter pre-encode.
            ahcRet = VideoFunc_PreRecord();
            DrawVideoParkingMode(uiGetParkingModeEnable());
        }
    }
    else if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE && AHC_VIDEO_IsEmergRecStarted() == AHC_FALSE) ||
             MMPS_3GPRECD_GetEmergActionType() != MMP_3GPRECD_EMERG_SWITCH_FILE) {
        if (VideoFunc_RecordRestart() == AHC_FALSE) {
            AHC_DBG_ERR(1, "--E-- VideoFunc_RecordRestart Fail\r\n");
            StateVideoRecMode_StopRecordingProc(EVENT_VRCB_FILE_FULL);
            AHC_ShowErrorDialog(WMSG_STORAGE_FULL);

            #ifdef CFG_REC_WD_RESET_AFTER_RESTART_FAIL //may be defined in config_xxx.h
            while (1);  // Let OEM WD reset.
            #endif
        }
        else {
            DrawStateVideoRecUpdate(EVENT_VIDEO_KEY_RECORD);
        }
    }

    if (AHC_GetCurKeyEventID() == BUTTON_VRCB_SEAM_LESS) {
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else {
        AHC_DBG_ERR(1, "BUTTON_VRCB_SEAM_LESS Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
    }

    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE) {
        //Fix: Fail to move normal video file to event folder.
        //      Set m_bStartEmerVR to false to allow next move.
        AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_MOTION_DTC_LCD)
{
#if (MOTION_DETECTION_EN) && (VMD_ACTION & VMD_RECORD_VIDEO)

    if (m_ubVMDStart)
    {
        if (AHC_SDMMC_BasicCheck() == AHC_FALSE)
            return;

        #if (PARKING_RECORD_FORCE_20SEC == 0)
        // Update VMD stop recording timer
        m_ulVMDStopCnt = AHC_GetVMDRecTimeLimit() * 10; // Video Time period is 100ms.
        #endif

        #if((SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN) && \
            (GSNR_PWRON_REC_BY && GSNR_PWRON_REC_BY_VMD))
        if(ubGsnrPwrOnActStart)
        {
            m_ulGSNRRecStopCnt = AHC_GSNR_PWROn_MovieTimeReset();
        }
        #endif

        #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
        if( m_ubParkingModeRecTrigger == AHC_FALSE )
        #endif
        {
            m_ulVMDStopCnt = AHC_GetVMDRecTimeLimit() * 1000 / VIDEO_TIMER_UNIT;

            // VMD Trigger Video record and countdown (m_ulVMDStopCnt) to stop recording.
            //AHC_DBG_MSG(1, FG_RED("!!! SomeBody/SomeThing is Moved!!! m_ulVMDStopCnt=%d %d\r\n"), m_ulVMDStopCnt, EVENT_VRCB_MOTION_DTC);
            AHC_DBG_MSG(1, FG_RED("!!! SomeThing is Moved!!!\r\n"));

            if (VideoFunc_GetRecordStatus() == AHC_FALSE)
                AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_VIDEO_RECORD, EVENT_VRCB_MOTION_DTC);

            #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
            m_ubParkingModeRecTrigger = AHC_TRUE;
            #endif
        }
    }
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_MEDIA_ERROR_LCD)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, FG_RED("EVENT_VRCB_MEDIA_ERROR\r\n"));

    AHC_WMSG_Draw(AHC_TRUE, WMSG_INSERT_SD_AGAIN, 2);

    if (VideoFunc_GetRecordStatus())
    {
        StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
        AHC_ShowErrorDialog(WMSG_INSERT_SD_AGAIN);
        VideoFunc_SetRecordStatus(AHC_FALSE);
    }

    if (uiGetParkingModeEnable() == AHC_TRUE) {

        DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);

        //Enter pre-encode.
        ahcRet = VideoFunc_PreRecord();

        if (ahcRet == AHC_TRUE) {
            DrawVideoParkingMode(uiGetParkingModeEnable());
            uiSetParkingModeRecord(AHC_FALSE);
        }
        else {
            AHC_PRINT_RET_ERROR(0, 0);
            ahcRet = VideoFunc_ParkingModeStop();
            ahcRet |= VideoFunc_Preview();
            return;
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VR_START_LCD)
{
/*
    #if (GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO)
    GPSCtrl_StartRecord();
    #endif
    #if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)
    AHC_Gsensor_StartRecord();
    #endif
*/
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VR_STOP_LCD)
{
/*
    #if (GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO)
    GPSCtrl_EndRecord();
    #endif
    #if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)
    AHC_Gsensor_EndRecord();
    #endif
*/
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VR_WRITEINFO_LCD)
{
    //NOP
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LOCK_VR_FILE_LCD)
{
    if(VideoFunc_GetRecordStatus()) {
        AHC_Protect_SetType(AHC_PROTECT_MENU);
        VideoFunc_SetFileLock();
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LOCK_FILE_G_LCD)
{
    AHC_DBG_MSG(1, FG_BLUE("@@@ EVENT_LOCK_FILE_G\r\n"));

#if (SUPPORT_GSENSOR) && (GSENSOR_FUNC & FUNC_LOCK_FILE)
    #if((SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN) && \
        (GSNR_PWRON_REC_BY & GSNR_PWRON_REC_BY_SHAKED) && \
        (GSNR_PWRON_MOVIE_SHAKED_ACT == GSNR_PWRON_MOVIE_LOCKED))
    if (ubGsnrPwrOnActStart && ubGsnrPwrOnFirstREC)
    {
        if ( VideoFunc_GetRecordStatus() && !VideoFunc_LockFileEnabled() && (m_ubGsnrIsObjMove == AHC_TRUE) )
        {
            AHC_DBG_MSG(1, FG_BLUE("Lock file by G-Sensor Power-On !!!\r\n"));

            AHC_Protect_SetType(AHC_PROTECT_G);

        #if (LIMIT_MAX_LOCK_FILE_NUM)
            #if (MAX_LOCK_FILE_ACT == LOCK_FILE_STOP)
            if (m_ulLockFileNum < MAX_LOCK_FILE_NUM)
            #endif
            {
                AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                EnableLockFile(AHC_TRUE, LOCK_FILE_CUR);
                m_ulLockEventNum++;
            }
        #else
            {
                AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                EnableLockFile(AHC_TRUE, LOCK_FILE_CUR);
            }
        #endif

            m_ubGsnrIsObjMove = AHC_FALSE;  //Reset
            ubGsnrPwrOnFirstREC = AHC_FALSE;
        }
    }
    else
    #endif//POWER_ON_BY_GSENSOR_EN
    if ( (MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF) &&
         (VideoFunc_GetRecordStatus() && !VideoFunc_LockFileEnabled()) )
    {
        if (m_ubGsnrIsObjMove == AHC_TRUE)
        {
            AHC_DBG_MSG(1, "CarDV is Shaking !! Lock Previous/Current Files\r\n");

            AHC_Protect_SetType(AHC_PROTECT_G);

        #if (LIMIT_MAX_LOCK_FILE_NUM)
            #if (MAX_LOCK_FILE_ACT == LOCK_FILE_STOP)
            if (m_ulLockFileNum < MAX_LOCK_FILE_NUM)
            #endif
            {
                AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                EnableLockFile(AHC_TRUE, VR_LOCK_FILE_TYPE);
                m_ulLockEventNum++;
            }
        #else
            {
                AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                EnableLockFile(AHC_TRUE, VR_LOCK_FILE_TYPE);
            }
        #endif
        #if (LIMIT_MAX_LOCK_FILE_TIME)
        VideoFunc_ChangeCurFileTimeLimit();
        #endif
            m_ubGsnrIsObjMove = AHC_FALSE;//Reset
        }
    }
    else
    {
        m_ubGsnrIsObjMove = AHC_FALSE;//Reset
    }
#endif
}

#if (AHC_SHAREENC_SUPPORT == 0) || (AHC_EMERGENTRECD_SUPPORT)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VR_EMERGENT_LCD)
{
    if (uiGetParkingModeEnable())
        return;

    if( MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF && VideoFunc_GetRecordStatus() )
    {
        #if (GSENSOR_CONNECT_ENABLE)
        m_ubGsnrIsObjMove = AHC_FALSE;//Reset
        #endif

        AHC_DBG_MSG(1, "CarDV is Shaking !!!!!\r\n");

        switch (MMPS_3GPRECD_GetEmergActionType()) {
            case MMP_3GPRECD_EMERG_DUAL_FILE:
                AHC_DBG_MSG(1, "Action: Emerg Dual File.\r\n");
                break;
            case MMP_3GPRECD_EMERG_SWITCH_FILE:
                AHC_DBG_MSG(1, "Action: Emerg Switch File.\r\n");
                break;
            case MMP_3GPRECD_EMERG_MOVE_FILE:
                AHC_DBG_MSG(1, "Action: Emerg Move File.\r\n");
                break;
            case MMP_3GPRECD_EMERG_NO_ACT:
                AHC_DBG_MSG(1, "Action: Emerg No Act.\r\n");
                break;
        }

        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_NO_ACT)
        {
            AHC_DBG_MSG(1, "No pre-defined action to do. \r\n");
            return;
        }

        if( (AHC_VIDEO_IsEmergRecStarted() == AHC_FALSE) &&
            (AHC_VIDEO_IsEmergPostDone() == AHC_TRUE))
        {
            if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE)
            {
                if (AHC_Deletion_RemoveEx(DCF_DB_TYPE_DB2_EVENT, AHC_VIDEO_GetRecTimeLimitEx()) == AHC_TRUE)
                {
                    AHC_DBG_MSG(1, "Emergency Record: Go !!!! \n");

                    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE)
                    {
                        AHC_DBG_MSG(1, " [%d] Emergency Act: Move file !!!! \n", __LINE__);
                        AHC_VIDEO_SetNormal2Emergency(AHC_TRUE);
                        {
                            UINT32 ulTickCount = 0, ulTickCount2 = 0;
                            AHC_OS_GetTime(&ulTickCount);
                            //DrawVideo_UpdatebyEvent(EVENT_VR_EMERGENT);
                            AHC_VIDEO_SetEmergRecStarted(AHC_TRUE);
                            AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                            AHC_OS_GetTime(&ulTickCount2);
                            AHC_DBG_MSG(1, "AHC_WMSG_Draw() Time = %d ms \n\r", ((ulTickCount2 - ulTickCount)*1000)/ OS_TICKS_PER_SEC);
                            //CGI_SET_STATUS(WIRELESS_REC_EMERGENCY, CGI_ERR_NONE)
                        }
                    }
                    else
                    {
                        AHC_DBG_MSG(1, " [%d] Emergency Act: Switch file !!!! \n", __LINE__);
                        if (VideoFunc_TriggerEmerRecord())
                        {
                            UINT32 ulTickCount = 0, ulTickCount2 = 0;
                            AHC_OS_GetTime(&ulTickCount);
                            //DrawVideo_UpdatebyEvent(EVENT_VR_EMERGENT);
                            AHC_VIDEO_SetEmergRecStarted(AHC_TRUE);
                            AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                            AHC_OS_GetTime(&ulTickCount2);
                            AHC_DBG_MSG(1, "AHC_WMSG_Draw() Time = %d ms \n\r", ((ulTickCount2 - ulTickCount)*1000)/ OS_TICKS_PER_SEC);
                            //CGI_SET_STATUS(WIRELESS_REC_EMERGENCY, CGI_ERR_NONE)
                        }
                    }
                }
            }
            else
            {
                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                {
                    VIDENC_FW_STATUS  status_vid;
                    MMPS_3GPRECD_GetPrmEncoderStatus(&status_vid);
                    if (status_vid != VIDENC_FW_STATUS_START)
                    {
                        AHC_DBG_MSG(1, FG_RED("Failed to start Emergency record because Normal recording is not triggered!!!(1)\r\n"));
                        // Wait a while, then trigger Emergency record again.
                        AHC_OS_Sleep(300);
                        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_LOCK_FILE_G, 0);
                        return;
                    }
                }

                if (AHC_Deletion_RemoveEx(DCF_DB_TYPE_DB2_EVENT, EMER_RECORD_DUAL_WRTIE_MAX_TIME) == AHC_TRUE)
                {
                    AHC_DBG_MSG(1, "Emergency Record: Go !!!! \n");

                    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE)
                    {
                        AHC_VIDEO_SetNormal2Emergency(AHC_TRUE);
                        {
                            UINT32 ulTickCount = 0, ulTickCount2 = 0;
                            AHC_OS_GetTime(&ulTickCount);
                            //DrawVideo_UpdatebyEvent(EVENT_VR_EMERGENT);
                            AHC_VIDEO_SetEmergRecStarted(AHC_TRUE);
                            AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                            AHC_OS_GetTime(&ulTickCount2);
                            AHC_DBG_MSG(1, "AHC_WMSG_Draw() Time = %d ms \n\r", ((ulTickCount2 - ulTickCount)*1000)/ OS_TICKS_PER_SEC);
                            //CGI_SET_STATUS(WIRELESS_REC_EMERGENCY, CGI_ERR_NONE)
                        }
                    }
                    else
                    {
                        if (VideoFunc_TriggerEmerRecord())
                        {
                            UINT32 ulTickCount = 0, ulTickCount2 = 0;
                            AHC_OS_GetTime(&ulTickCount);
                            //DrawVideo_UpdatebyEvent(EVENT_VR_EMERGENT);
                            AHC_VIDEO_SetEmergRecStarted(AHC_TRUE);
                            AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
                            AHC_OS_GetTime(&ulTickCount2);
                            AHC_DBG_MSG(1, "AHC_WMSG_Draw() Time = %d ms \n\r", ((ulTickCount2 - ulTickCount)*1000)/ OS_TICKS_PER_SEC);
                            //CGI_SET_STATUS(WIRELESS_REC_EMERGENCY, CGI_ERR_NONE)
                        }
                    }
                }
            }
        }
        else
        {
            AHC_DBG_MSG(1, "Emergency Record: Keep going !!!! \n");

            if(VideoFunc_TriggerEmerRecord())
            {
                //DrawVideo_UpdatebyEvent(EVENT_VR_EMERGENT);
                //CGI_SET_STATUS(WIRELESS_REC_EMERGENCY, CGI_ERR_INVALID_STATE)
            }
        }
    }
    else {
        CGI_SET_STATUS(WIRELESS_REC_EMERGENCY, CGI_ERR_INVALID_STATE)
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_EMER_DONE_LCD)
{
    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) )
    {
        if (AHC_VIDEO_GetKernalEmergStopStep() == AHC_KERNAL_EMERGENCY_STOP)
            AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_AHC_DONE);
        else
            return;//break;
    }

    #if 0
    SystemSettingConfig()->byStartNormalRecordAfterEmergencyRecord = (UINT8)VideoFunc_GetRecordStatus();
    #else
    {
        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE)
            SystemSettingConfig()->byStartNormalRecordAfterEmergencyRecord = AHC_FALSE;
        else
            SystemSettingConfig()->byStartNormalRecordAfterEmergencyRecord = AHC_TRUE;
    }
    #endif
    AHC_VIDEO_EmergRecPostProcess();
    //DrawVideo_UpdatebyEvent(EVENT_VRCB_EMER_DONE);

    AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
}

#else
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VR_EMERGENT_LCD)
{
    MMP_ULONG   newtime;
    UINT32      ulTime = 0;
    AHC_PauseKeyUI();

    if( (AHC_VIDEO_IsEmergRecStarted() == AHC_FALSE) && (AHC_VIDEO_IsEmergPostDone() == AHC_TRUE))
    {
        if (VideoFunc_GetRecordStatus())
        {
            AHC_DBG_MSG(1, FG_PURPLE("EVENT_VR_EMERGENT: Go !!!! \r\n"));
            AHC_VIDEO_SetEmergRecStarted(AHC_TRUE);
            AHC_VIDEO_SetEmergPostDone(AHC_FALSE);

            AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);
            EnableLockFile(AHC_TRUE, VR_LOCK_FILE_TYPE);

            AHC_VIDEO_GetCurRecordingTime(&ulTime);
            AHC_DBG_MSG(1, FG_PURPLE("Emer time -- %d ms\r\n"), ulTime);
            newtime = ulTime+(EMER_RECORD_WRITE_INTERVAL*1000);
            AHC_DBG_MSG(1, "new due time = %d ms\r\n", newtime);
            MMPS_3GPRECD_ChangeCurFileTimeLimit(newtime);
        }
    }
    else if (AHC_VIDEO_IsEmergRecStarted() == AHC_TRUE)
    {
        AHC_DBG_MSG(1, "EVENT_VR_EMERGENT: Keep going !!!! \r\n");
    }

    AHC_ResumeKeyUI();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VRCB_EMER_DONE_LCD)
{
    AHC_DBG_MSG(1, FG_PURPLE("EVENT_VRCB_EMER_DONE -\r\n"));
    AHC_DBG_MSG(1, "Emer file=%s\r\n", AHC_VIDEO_GetCurPrmRecdFileName(0));

    AHC_VIDEO_SetEmergPostDone(AHC_TRUE);
    AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
}
#endif

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VIDREC_UPDATE_MESSAGE_LCD)
{
    MMPS_FS_SetCreationTime();
#if (VIDEO_DIGIT_ZOOM_EN ==1)
    if(!AHC_VIDEO_GetCurZoomStatus()){
        if(!bZoomStop){
            VideoFunc_ZoomOperation(AHC_SENSOR_ZOOM_STOP);
            bZoomStop = AHC_TRUE;
        }
    }
#endif

#if (MOTION_DETECTION_EN)
    if(m_ubInRemindTime && m_ulVMDRemindTime==0)
    {
        DrawStateVideoRecUpdate(ulEvent);
        m_ubInRemindTime = AHC_FALSE;
        DrawVideoParkingMode(uiGetParkingModeEnable());
        return;//break;
    }
#endif

#if (FLICKER_PWR_LED_AT_VR_STATE)
    if(VideoFunc_GetRecordStatus())
    {
        static AHC_BOOL ubLEDstatus = 0;
        LedCtrl_PowerLed(ubLEDstatus++ & 0x2);
    }
#endif

    {
        static UINT32 m_VidWarningCounter = 0;

        if(AHC_IsDialogPresent())
            m_VidWarningCounter++;
        else
            m_VidWarningCounter = 0;

        if(m_VidWarningCounter!=0 && m_VidWarningCounter%10==0)
            AHC_ShowSoundWarning();
    }

    DrawStateVideoRecUpdate(ulEvent);
    #if 0 // Show g-sensor value for debug...
    DrawStateVideoRecUpdate(EVENT_GPSGSENSOR_UPDATE);
    #endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SHOW_FW_VERSION_LCD)
{
    AHC_WMSG_Draw(AHC_TRUE, WMSG_SHOW_FW_VERSION, 5);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SHOW_GPS_INFO_LCD)
{
    #if (SUPPORT_GPS)
    if(bGPS_PageExist)
    {
        bGPS_PageExist = AHC_FALSE;
        DrawStateVideoRecUpdate(EVENT_LCD_COVER_NORMAL);
    }
    else
    {
        UINT8 bID0 = 0, bID1 = 0;

        CHARGE_ICON_ENABLE(AHC_FALSE);
        bGPS_PageExist = AHC_TRUE;
        OSDDraw_EnterDrawing(&bID0, &bID1);
        QuickDrawGPSInfoPage(bID0, AHC_FALSE);
        QuickDrawGPSInfoPage(bID0, AHC_TRUE);
        OSDDraw_ExitDrawing(&bID0, &bID1);
        CHARGE_ICON_ENABLE(AHC_TRUE);
    }
    #endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_TIMESTAMP_UPDATE_LCD)
{
    UpdateVideoCurrentTimeStamp(AHC_TRUE);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_VR_OSD_SHOW_LCD)
{
#if (AUTO_HIDE_OSD_EN)
    m_ulOSDCounter  = 0;
    m_ubHideOSD     = AHC_FALSE;
    DrawStateVideoRecInit();
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_REC_SHORT)
{
#if (AHC_SHAREENC_SUPPORT)
    VIDENC_FW_STATUS eVidEncStatus = VIDENC_FW_STATUS_NONE;

    MMPS_3GPRECD_GetPrmEncoderStatus(&eVidEncStatus);

    if ((eVidEncStatus != VIDENC_FW_STATUS_STOP &&
         eVidEncStatus != VIDENC_FW_STATUS_NONE) &&
        (AHC_VIDEO_IsShareRecdStarted() == AHC_FALSE))
    {
        AHC_DBG_MSG(1, "# SHARE_RECD Is Trigger\r\n");

        AHC_WMSG_Draw(AHC_TRUE, WMSG_LOCK_CURRENT_FILE, 2);

        if (!VideoFunc_StartShareRecord()) {
            CGI_SET_STATUS(WIRELESS_REC_SHORT, CGI_ERR_GENERAL)
        }
        else {
            CGI_SET_STATUS(WIRELESS_REC_SHORT, CGI_ERR_NONE)
        }
    }
    else {
        AHC_DBG_MSG(0, "The main video must be recording and the share video is not recording.\r\n");
        CGI_SET_STATUS(ulEvent, CGI_ERR_INVALID_STATE)
    }
#else
    AHC_DBG_MSG(1, BG_RED("Get event ID %d. TBD")"\r\n", ulEvent);
    CGI_SET_STATUS(ulEvent, CGI_ERR_GENERAL)
#endif
}

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_OPEN_H264_STREAM_LCD)
{
    #if (VR_PREENCODE_EN)
    m_ubPreEncodeEn = AHC_TRUE;
    #endif
    AHC_SetMode(AHC_MODE_IDLE);
    VideoFunc_Preview();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_CLOSE_H264_STREAM_LCD)
{
    #if (VR_PREENCODE_EN)
    m_ubPreEncodeEn = AHC_FALSE;
    #endif
    AHC_SetMode(AHC_MODE_IDLE);
    VideoFunc_Preview();
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SWITCH_WIFI_STREAMING_MODE_LCD)
{
    if (NETAPP_NET_STATUS_NONE == nhw_get_status()) {
        return;//break;
    }

    if(aitstreamer_is_ready()==AHC_FALSE) {
        AHC_DBG_MSG(1, "--E-- A-I-T streamer is not ready !!!\n");
        return;//break;
    }

    if (nhw_get_status()) {
        AHC_WiFi_Toggle_StreamingMode();
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_WIFI_SWITCH_TOGGLE_LCD)
{
    AHC_DBG_MSG(1, "EVENT_WIFI_SWITCH_TOGGLE -\r\n");

    if ((NETAPP_NET_STATUS_DOWN == nhw_get_status()) || (NETAPP_NET_STATUS_NONE == nhw_get_status()) || (WLAN_SYS_GetMode() == -1))
        AHC_WiFi_Switch(AHC_TRUE);
    else
        AHC_WiFi_Switch(AHC_FALSE);
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_WIFI_SWITCH_DISABLE_LCD)
{
    AHC_DBG_MSG(1, "EVENT_WIFI_SWITCH_DISABLE -\r\n");

    if (AHC_TRUE == AHC_WiFi_Switch(AHC_FALSE)) {
        Setpf_WiFi(WIFI_MODE_OFF);
        // Need save menusetting to Flash - TBD
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_WIFI_SWITCH_ENABLE_LCD)
{
    AHC_DBG_MSG(1, "EVENT_WIFI_SWITCH_ENABLE -\r\n");

    if (AHC_TRUE == AHC_WiFi_Switch(AHC_TRUE)) {
        Setpf_WiFi(WIFI_MODE_ON);
        // Need save menusetting to Flash - TBD
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_CGI_DUMMY)
{
    AHC_DBG_MSG(1, "EVENT_WIFI_CGI_DUMMY -\r\n");

    AHC_DBG_MSG(1, BG_RED("Get event ID %d. TBD")"\r\n", ulEvent);
    CGI_SET_STATUS(ulEvent, CGI_ERR_GENERAL)
}



#include "amn_sysobjs.h"
extern struct osal_ev_download_parm ev_download_param;
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_DOWNLOAD)
{
    /** @note If the downloading file is too small, when the event is processed here,
     *  it is closed. In that file close will be seen twice.
     *
     *  @note Due to current code structure, only ulEvent is passed here.
     *  now temporary use a quick-dirty global variable here.
     *  A parameter for event data is expected.
     *
     *  @todo Compare the file name with DCF, if that is a certain file, then display
     *  downloading icon or hide that icon while closed.
     */
    AHC_DBG_MSG(1, "STATE_VIDEO_REC_MODE_EVENT_DOWNLOAD -\r\n");

    AHC_DBG_MSG(1, "event file:%s %s\r\n", ev_download_param.filename, ev_download_param.start ? "open": "close");
    if (ev_download_param.start == 0) {
        ncgi_clr_notify_fn(NCGI_ANY_FN, ev_download_param.filename);
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_NET_ONOFF)
{
    AHC_DBG_MSG(1, "EVENT_WIFI_SWITCH_ENABLE\r\n");
    if ((NETAPP_NET_STATUS_DOWN == nhw_get_status()) || (NETAPP_NET_STATUS_NONE == nhw_get_status()) || (WLAN_SYS_GetMode() == -1))
        AHC_WiFi_Switch(AHC_TRUE);
    else
        AHC_WiFi_Switch(AHC_FALSE);
}

#endif

AHC_BOOL VIDEO_REC_MODE_EVENT_PARKING_REGCB(AHC_BOOL bEnable)
{
    AHC_BOOL                ahcRet = AHC_TRUE;
    AHC_VIDEO_FILENAME_MGR  *pstPrmRecdFileNameMgr = NULL;
    AHC_VIDEO_FILENAME_MGR  *pstScdRecdFileNameMgr = NULL;

    if (bEnable) {
        //Init With default mode.
        ahcRet = AHC_VIDEO_SetRecordModeRegisterInit((void *)AHC_VIDEO_SetRecordModeInitParkingMode);

        ahcRet = AHC_VIDEO_SetRecordModeRegisterUnInit((void *)AHC_VIDEO_SetRecordModeUnInitParkingMode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_BITRATE,
                    (void *)AHC_VIDEO_SetRecordModeSetBitRateParkingMode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_AUDIO_ENCODE,
                    (void *)AHC_VIDEO_SetRecordModeSetAudioEncodeParkingMode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_TIME_LIMIT,
                    (void *)AHC_VIDEO_SetRecordModeSetTimeLimitParkingMode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_SEAMLESS,
                    (void *)AHC_VIDEO_SetRecordModeSetSeamlessParkingMode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_EMERGENCY,
                    (void *)AHC_VIDEO_SetRecordModeSetEmergencyParkingMode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PRERECORD_TO_RECORD,
                    AHC_VIDRECD_MODE_API_REGISTER_CALLBACK,
                    (void *)AHC_VIDEO_SetRecordModeRegisterCallbackParkingMode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_SEAMLESS_START_NEXT_RECORD,
                    AHC_VIDRECD_MODE_API_CYCLIC_DELETE_FILES,
                    (void *)AHC_VIDEO_CyclicDeleteFilesParkingMode);

        pstPrmRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMREC);
        if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
            MEMSET(pstPrmRecdFileNameMgr->u8FullName, 0, sizeof(pstPrmRecdFileNameMgr->u8FullName));
            MEMSET(pstPrmRecdFileNameMgr->u8FileName, 0, sizeof(pstPrmRecdFileNameMgr->u8FileName));
        }
        #if (AHC_MULTI_TRACK_EN == 0)
        if (MMP_IsScdCamExist()) {
            pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);
            if (pstScdRecdFileNameMgr->u8DeviceStatus) {
                MEMSET(pstScdRecdFileNameMgr->u8FullName, 0, sizeof(pstScdRecdFileNameMgr->u8FullName));
                MEMSET(pstScdRecdFileNameMgr->u8FileName, 0, sizeof(pstScdRecdFileNameMgr->u8FileName));
            }
        }
        else if (MMP_IsUSBCamExist()) {
            pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);
            if (pstScdRecdFileNameMgr->u8DeviceStatus) {
                MEMSET(pstScdRecdFileNameMgr->u8FullName, 0, sizeof(pstScdRecdFileNameMgr->u8FullName));
                MEMSET(pstScdRecdFileNameMgr->u8FileName, 0, sizeof(pstScdRecdFileNameMgr->u8FileName));
            }
        }
        #endif
    }
    else {
        ahcRet = AHC_VIDEO_SetRecordModeRegisterInit((void *)AHC_VIDEO_SetRecordModeInit);

        ahcRet = AHC_VIDEO_SetRecordModeRegisterUnInit((void *)AHC_VIDEO_SetRecordModeUnInit);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_BITRATE,
                    (void *)AHC_VIDEO_SetRecordModeSetBitRate);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_AUDIO_ENCODE,
                    (void *)AHC_VIDEO_SetRecordModeSetAudioEncode);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_TIME_LIMIT,
                    (void *)AHC_VIDEO_SetRecordModeSetTimeLimit);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_SEAMLESS,
                    (void *)AHC_VIDEO_SetRecordModeSetSeamless);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD,
                    AHC_VIDRECD_MODE_API_SET_EMERGENCY,
                    (void *)AHC_VIDEO_SetRecordModeSetEmergency);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_PRERECORD_TO_RECORD,
                    AHC_VIDRECD_MODE_API_REGISTER_CALLBACK,
                    (void *)AHC_VIDEO_SetRecordModeRegisterCallback);

        ahcRet =  AHC_VIDEO_SetRecordModeRegisterAction(
                    AHC_VIDRECD_FLOW_TYPE_SEAMLESS_START_NEXT_RECORD,
                    AHC_VIDRECD_MODE_API_CYCLIC_DELETE_FILES,
                    (void *)AHC_VIDEO_CyclicDeleteFiles);
    }

    return ahcRet;
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_PARKING_KEY_LCD)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (MenuSettingConfig()->uiMotionDtcSensitivity == MOTION_DTC_SENSITIVITY_OFF) {
        return;
    }

    if (AHC_IsSDInserted() &&
        AHC_GetMountStorageMediaStatus() &&
        AHC_SDMMC_IsSD1MountDCF()) {
        //NOP
    }
    else {
        AHC_PRINT_RET_ERROR(0, 0);
        AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_CARD, 2);
        AHC_DBG_MSG(1, "SD card is not ready yet!\r\n");
        return;
    }

    //Enable Parking mode.
    if (uiGetParkingModeEnable() == AHC_FALSE) {
        ahcRet = VideoFunc_SetPreviewWindow(AHC_TRUE);
        ahcRet = VideoFunc_ParkingModeStart();

        //Enter video preview with motion detection.
        ahcRet = AHC_SetMode(AHC_MODE_RECORD_PREVIEW);
        if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, 0); return;}

        DrawStateVideoRecUpdate(EVENT_LCD_COVER_NORMAL);

        //Enter pre-encode flow.
        ahcRet = VideoFunc_PreRecord();
        if (ahcRet != AHC_TRUE) {
            AHC_PRINT_RET_ERROR(0, 0);
            ahcRet = VideoFunc_ParkingModeStop();
            DrawVideoParkingMode(uiGetParkingModeEnable());
            ahcRet = VideoFunc_Preview();
            return;
        }
    }
    else { //Disable Parking mode.
        ahcRet = VideoFunc_ParkingModeStop();
        ahcRet = VideoFunc_Preview();
    }

    DrawVideoParkingMode( uiGetParkingModeEnable() );
}

#if (UVC_HOST_VIDEO_ENABLE)
DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_USB_B_DEVICE_DETECT_LCD)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT8 u8ParkingModeStatus = 0;

    u8ParkingModeStatus = uiGetParkingModeEnable();

    /////////////////////////////////////////////////////// Description ////////////////////////////////////////////////////
    // EVENT_USB_B_DEVICE_DETECT: Got when Rear Cam streaming was detected
    // EVENT_USB_B_DEVICE_REMOVED: Got when Rear Cam streaming was disconnected
    // Note: When some UVC error happened (ex: AHC_HostUVCVideoSetEp0TimeoutCB() / AHC_HostUVCVideoSetFrmRxTimeout2CB() was called),
    //       EVENT_USB_B_DEVICE_REMOVED will be sent. Below sample code will stop current recording and start next recording with only Front Cam.
    //       Once AHC_USBDetectHandler() detected Rear Cam streaming was recovered, EVENT_USB_B_DEVICE_DETECT will be sent.
    //       Below sample code will stop current recording and start next recording with Front & Rear Cam.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        MMP_BOOL bStatus = MMP_FALSE;
        AHC_BOOL bRecording = AHC_FALSE;

        // Receive USB B device event during booting time.
        if (ulEvent == EVENT_USB_B_DEVICE_DETECT) {

            //Check if UVC preview is enabled
            MMPF_USBH_GetUVCPrevwSts(&bStatus);

            #if defined(WIFI_PORT) && (WIFI_PORT == 1)
            ncam_set_rear_cam_ready(AHC_TRUE);
            #endif

            if (bStatus) {

                AHC_USB_PauseDetection(0);
                if ((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
                    (AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)) {
                    AHC_SetCurKeyEventID(EVENT_NONE);
                }
                else {
                    AHC_DBG_ERR(1, "BUTTON_USB_B_DEVICE_DETECTED,REMOVED Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
                }
                return;
            }
        }

        bRecording = VideoFunc_GetRecordStatus();
        if (bRecording) {
            ahcRet = StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
        }

        if (ulEvent == EVENT_USB_B_DEVICE_REMOVED) {

            AHC_HostUVC_PreviewStop(AHC_HUVC_UI_MODE_VR);

            /* BE CAREFUL, forced stop frame Rx and clear FIFO */
            MMPS_USB_StopFrmRxClrFIFO();
            /* BE CAREFUL, SPECIAL CASE! */
            /* forced to clear connect status because of disconnected, not from USB_OTG_ISR (PHY) */
            MMPS_USB_SetDevConnSts(MMP_FALSE);

            #if defined(WIFI_PORT) && (WIFI_PORT == 1)
            if (AHC_STREAM_REAR_USBH == ncam_get_cam_src((unsigned int)AHC_STREAM_H264)) {
                AHC_SetStreamingMode(AHC_STREAM_OFF);
            }
            ncam_set_rear_cam_ready(AHC_FALSE);
            #endif

            if (gbWinExchangedCnt != ONLY_FRONT &&
                gbWinExchangedCnt != F_LARGE_R_SMALL) {
                gbWinExchangedCnt = F_LARGE_R_SMALL;
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH);
                AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_UVC, AHC_TRUE, SCD_CAM_PREVIEW_MIRROR, 0, 0, PIP_WIDTH, PIP_HEIGHT);
                MMPS_Display_SetUsbCamPreviewPIPType(MMPS_PREVIEW_UI_MODE_VR, MMPS_DISPLAY_PRM_FULL_USBH_NONE);
            }

            /* reset USB */
            MMPS_USB_DisconnectDevice();
        }

        if (ulEvent == EVENT_USB_B_DEVICE_DETECT) {
            MMP_ERR sRet = MMP_ERR_NONE;
            AHC_DISPLAY_OUTPUTPANEL OutputDevice;
            UINT32 ulFlickerMode = COMMON_FLICKER_50HZ;

            AHC_Menu_SettingGetCB( (char *)COMMON_KEY_FLICKER, &ulFlickerMode);

            AHC_GetDisplayOutputDev(&OutputDevice);
            sRet = MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, OutputDevice);
            if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }

            if (!AHC_HostUVC_PreviewStart(AHC_HUVC_UI_MODE_VR, ulFlickerMode)) {
                AHC_DBG_MSG(1, "%s,%d,CNNT RearCam type(%X) fail!\r\n"__func__, __LINE__,CAM_GET_SCD);
            }
        }

        if (u8ParkingModeStatus) {
            DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);
            //Enter video preview with motion detection.
            AHC_SetMode(AHC_MODE_RECORD_PREVIEW);
            //Enter pre-encode flow.
            VideoFunc_PreRecord();
        }
        else {
            if (bRecording) {
                ahcRet = StateVideoRecMode_StartRecordingProc(EVENT_VIDEO_KEY_RECORD);
            }
        }
    }

    AHC_USB_PauseDetection(0);

    if ((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
        (AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)) {
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else {
        AHC_DBG_ERR(1, "BUTTON_USB_B_DEVICE_DETECTED,REMOVED Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
    }
}
#endif

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_TV_DECODER_SRC_TYPE_LCD)
{
    AHC_BOOL                ahcRet = AHC_TRUE;
    AHC_BOOL                bRecording = AHC_FALSE;
    UINT8                   u8ParkingModeStatus = 0;
    MMP_SNR_ANADEC_SRC_TYPE eSrcType = MMP_SNR_ANADEC_SRC_NO_READY;

    MMPS_Sensor_GetAnaDecSrcType(&eSrcType);

    if ((eSrcType == MMP_SNR_ANADEC_SRC_PAL) ||
        (eSrcType == MMP_SNR_ANADEC_SRC_NTSC) ||
        (eSrcType == MMP_SNR_ANADEC_SRC_HD) ||
        (eSrcType == MMP_SNR_ANADEC_SRC_FHD)) {
        #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        ncam_set_rear_cam_ready(AHC_TRUE);
        #endif

        #if defined(FORCE_PREVIEW_REAR_CAM_ONLY)&&(FORCE_PREVIEW_REAR_CAM_ONLY)
        if (gbWinExchangedCnt != ONLY_REAR) {

            gbWinExchangedCnt = ONLY_REAR;
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_SCD, AHC_TRUE, 0, 0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH);
            MMPS_Display_SetScdAnaDecPreviewPIPType(MMPS_PREVIEW_UI_MODE_VR, MMPS_DISPLAY_PRM_NONE_SCD_FULL);
        }
        #endif
    }
    else {
        #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        ncam_set_rear_cam_ready(AHC_FALSE);
        #endif

        if (gbWinExchangedCnt != ONLY_FRONT &&
            gbWinExchangedCnt != F_LARGE_R_SMALL) {

            gbWinExchangedCnt = F_LARGE_R_SMALL;
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_PRM, AHC_TRUE, 0, 0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH);
            AHC_SetDisplayWindow(DISPLAY_SYSMODE_VIDEOCAPTURE_SCD, AHC_TRUE, SCD_CAM_PREVIEW_MIRROR, 0, 0, PIP_WIDTH, PIP_HEIGHT);
            MMPS_Display_SetScdAnaDecPreviewPIPType(MMPS_PREVIEW_UI_MODE_VR, MMPS_DISPLAY_PRM_FULL_SCD_NONE);
        }
    }

    u8ParkingModeStatus = uiGetParkingModeEnable();

    bRecording = AHC_VIDEO_GetRecdStateWhenDecSnrPlug();
    //bRecording = VideoFunc_GetRecordStatus();

    if (bRecording) {
        StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
    }

    if (u8ParkingModeStatus) {
        DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);

        // Enter video preview with motion detection.
        AHC_SetMode(AHC_MODE_RECORD_PREVIEW);
        // Enter pre-encode flow.
        VideoFunc_PreRecord();
    }
    else {
        // Switch to single camera recording
        if (bRecording) {
            ahcRet = StateVideoRecMode_StartRecordingProc(EVENT_VIDEO_KEY_RECORD);
        }
    }

    if (AHC_GetCurKeyEventID() == BUTTON_TV_DECODER_SRC_TYPE) {
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else {
        AHC_DBG_ERR(1, "BUTTON_TV_DECODER_SRC_TYPE Interrupted By [%d]\r\n", AHC_GetCurKeyEventID());
    }
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LDWS_START_LCD)
{
#if (ENABLE_ADAS_LDWS)

    LDWS_Lock();

    MMPS_AUI_StopPlay();
    m_ulLDWSWarn = 20;
    VideoFunc_LDWSWarn();
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_LDWS_STOP_LCD)
{
#if (ENABLE_ADAS_LDWS)
    LDWS_Unlock();
    ResetLDWSCounter();

    MMPS_AUI_StopPlay();
    DrawStateVideoRecUpdate(EVENT_LDWS_STOP);
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_FCWS_START_LCD)
{
#if (ENABLE_ADAS_FCWS)

    MMPS_AUI_StopPlay();

    m_ulFCWSWarn = 20;
    VideoFunc_FCWSWarn();
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_FCWS_STOP_LCD)
{
#if (ENABLE_ADAS_FCWS)
    ResetFCWSCounter();

    //          if ((CheckAlertState() != ALERT_NON) && (CheckAlertState() != ALERT_FCWS))
    //              return;

    MMPS_AUI_StopPlay();
    DrawStateVideoRecUpdate(EVENT_FCWS_STOP);
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SAG_START_LCD)
{
#if (ENABLE_ADAS_SAG)
    if(m_ulSAGWarn > 0){
        AHC_DBG_MSG(1, "===== >>> Previous SAG warning is not over yet! <<< ===== \r\n");
        return;//break;
    }
    MMPS_AUI_StopPlay();
    m_ulSAGWarn = 20;
    AHC_DBG_MSG(1, "===== >>> SAG warning begin! <<< ===== \r\n");
    AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON); //TBD. This is only an example.
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_SAG_STOP_LCD)
{
#if (ENABLE_ADAS_SAG)
    ResetSAGCounter();
    MMPS_AUI_StopPlay();
    AHC_DBG_MSG(1, "===== >>> SAG warning end! <<< ===== \r\n");
#endif
}

DECL_AHC_EV_HANDLER(STATE_VIDEO_REC_MODE_EVENT_MENU_EXIT_LCD)
{
    VideoRecMode_PreviewUpdate();
}

UINT32 StateVideoRecModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)//(UINT32 ulEvent)
{
    UINT32 ulVideoEvent = 0;
    ulVideoEvent  = KeyParser_VideoRecEvent(ulMsgId, ulEvent, ulParam);
#if DBG_UI_NET_EVENT
    if (ulVideoEvent != EVENT_VIDREC_UPDATE_MESSAGE) {
        if (ulVideoEvent >= WIRELESS_MESSAGE_START) {
            AHC_DBG_MSG(1, "ulMsgId:%X, param:%X, ", ulMsgId, ulParam);
        }
        AHC_DBG_MSG(1, "ulVideoEvent:x%X\r\n", ulVideoEvent);
    }
#endif
    StateModeDoHandlerEvent(ulMsgId, ulVideoEvent, ulParam);

    return 0;
}


void StateVideoRecTVMode(UINT32 ulJobEvent)
{
}


/*
 * lock functions
 */
/*
 * Get lock file status;
 */
AHC_BOOL VideoFunc_LockFileEnabled(void)
{
    return _bLockVRFile;
}

void EnableLockFile(AHC_BOOL bEnable, int type)
{
    _bLockVRFile = bEnable;
    _nLockType   = type;
}

/*
 * Change Lock file type, when stop recording by manual
 */
void LockFileTypeChange(int arg)
{
    if (arg == 1 /* Remove type of lock NEXT file */) {
        // When Stop recording by manual, remove lock NEXT
        if (_nLockType == LOCK_FILE_CUR_NEXT) {
            _nLockType = LOCK_FILE_CUR;
        } else if (_nLockType == LOCK_FILE_PREV_CUR_NEXT) {
            _nLockType = LOCK_FILE_PREV_CUR;
        }
    }
}

/*
 * a Hook function called by MMPF after VID file closed.
 */
void CUS_VideoProtectProcess(void)
{
    if (VideoFunc_LockFileEnabled()) {
        switch (_nLockType) {
        case LOCK_FILE_PREV_CUR:
        case LOCK_FILE_PREV_CUR_NEXT:
            AHC_DBG_MSG(1, "LOCK PREVIOUS and CURRENT...\r\n");
            DBG_AutoTestPrint(ATEST_ACT_EMERGENCY_0x0009, ATEST_STS_END_0x0003, 0, 0, gbAhcDbgBrk);
            AHC_Protect_SetVRFile(AHC_PROTECTION_BOTH_FILE, AHC_Protect_GetType());

            if (_nLockType == LOCK_FILE_PREV_CUR_NEXT) {
                _nLockType = LOCK_FILE_CUR;
            } else {
                AHC_DBG_MSG(1, "LOCK FINISH...\r\n");
                EnableLockFile(AHC_FALSE, 0);
                AHC_Protect_SetType(AHC_PROTECT_NONE);
            }
            break;

        case LOCK_FILE_CUR:
        case LOCK_FILE_CUR_NEXT:
            AHC_DBG_MSG(1, "LOCK CURRENT...\r\n");
            AHC_Protect_SetVRFile(AHC_PROTECTION_CUR_FILE, AHC_Protect_GetType());

            if (_nLockType == LOCK_FILE_CUR_NEXT) {
                _nLockType = LOCK_FILE_CUR;
            } else {
                AHC_DBG_MSG(1, "LOCK FINISH...\r\n");
                EnableLockFile(AHC_FALSE, 0);
                AHC_Protect_SetType(AHC_PROTECT_NONE);
            }
        }
    }
}

AHC_BOOL VideoFunc_TriggerRecdByVMD(void)
{
#if (MOTION_DETECTION_EN && (VMD_ACTION & VMD_RECORD_VIDEO))
    return (0 == m_ulVMDStopCnt) ? AHC_FALSE : AHC_TRUE;
#else
    return AHC_FALSE;
#endif
}

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE == 1)
int VideoFunc_UVCXUCmd_GetAtomValue(int CtlType, int *pCurr, int *pMin, int *pMax)
{
    AHC_BOOL bRet = AHC_TRUE;

#if 0 //Andy Liu TBD
    switch(CtlType) {
        case UVC_XU_RECORDTIME_CONTROL:
            bRet = GetAtomValue(COMMON_KEY_VR_CLIP_TIME, pCurr, pMin, pMax);
            break;
        case UVC_XU_RECORDRES_CONTROL:
            bRet = GetAtomValue(COMMON_KEY_MOVIE_SIZE, pCurr, pMin, pMax);
            break;
        case UVC_XU_GSENSOR_CONTROL:
            bRet = GetAtomValue(COMMON_KEY_GSENSOR_SENS, pCurr, pMin, pMax);
            break;
        case UVC_XU_AUDIO_CONTROL:
            bRet = GetAtomValue("RecordWithAudio", pCurr, pMin, pMax);
            break;
        case UVC_XU_REC_STATUS_CONTROL:
            *pCurr = VideoFunc_GetRecordStatus();
            *pMin  = 0;
            *pMax  = 1;
            break;
        case UVC_XU_REC_MODE_CONTROL:
            bRet = GetAtomValue("AutoRec", pCurr, pMin, pMax);
            break;
        default:
            AHC_PRINT_RET_ERROR(0, 0);
            break;
    }
#endif
    return bRet;
}

int VideoFunc_UVCXUCmd_SetAtomValue(int CtlType, int nValue)
{
    AHC_BOOL bRet = AHC_TRUE;

    switch(CtlType) {
        case UVC_XU_RECORDTIME_CONTROL:
            MenuSettingConfig()->uiMOVClipTime = nValue;
            break;
        case UVC_XU_RECORDRES_CONTROL:
            MenuSettingConfig()->uiMOVSize = nValue;
            break;
        case UVC_XU_GSENSOR_CONTROL:
            MenuSettingConfig()->uiGsensorSensitivity = nValue;
            break;
        case UVC_XU_AUDIO_CONTROL:
            MenuSettingConfig()->uiMOVSoundRecord = nValue;
            break;
        case UVC_XU_REC_STATUS_CONTROL:
            break;
        case UVC_XU_REC_MODE_CONTROL:
            MenuSettingConfig()->uiAutoRec = nValue;
            break;
        default:
            AHC_PRINT_RET_ERROR(0, 0);
            break;
    }

    Menu_ImportSetting();

    return bRet;
}

void VideoFunc_UVCXUCmd_CommonCtl(int CtlType, MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    AHC_BOOL bRecording = AHC_FALSE;
    int nCurr = 0,nMin = 0,nMax = 0;

    if (m_ubFormatSDing)
        return;

    if (VideoFunc_UVCXUCmd_GetAtomValue(CtlType, &nCurr, &nMin, &nMax) == AHC_FALSE)
        return;

    bRecording = VideoFunc_GetRecordStatus();

    switch(pCmd[1]) {
        case SET_CUR_CMD:
            if (CtlType == UVC_XU_REC_STATUS_CONTROL)
            {
                if (bRecording == AHC_TRUE && pCmd[2] == 0)
                {
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_REC_REL, 0);
                }
                else if(bRecording == AHC_FALSE && pCmd[2] == 1)
                {
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_REC_REL, 0);
                }
            }
            else if (CtlType == UVC_XU_PICTURE_CONTROL)
            {
                AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_REC_LPRESS, 0);
            }
            else if (CtlType == UVC_XU_MMC_CONTROL)
            {
                if (bRecording)
                    break;

                m_ubFormatSDing = AHC_TRUE;
                QuickMediaOperation(MEDIA_CMD_FORMAT);
                m_ubFormatSDing = AHC_FALSE;
            }
            else
            {
                if (bRecording)
                    break;

                if (pCmd[2] >= nMin && pCmd[2] <= nMax)
                {
                    VideoFunc_UVCXUCmd_SetAtomValue(CtlType, pCmd[2]);
                }
            }
            break;
        case GET_CUR_CMD:
            pResult[0] = nCurr;
            break;
        case GET_MIN_CMD:
            pResult[0] = nMin;
            break;
        case GET_MAX_CMD:
            pResult[0] = nMax;
            break;
        case GET_RES_CMD:
            pResult[0] = 1;
            break;
        case GET_LEN_CMD:
            break;
        case GET_INFO_CMD:
            break;
        case GET_DEF_CMD:
            pResult[0] = nMin;
            if (CtlType == UVC_XU_AUDIO_CONTROL)
            {
                pResult[0] = nMax;
            }
            break;
        default:
            AHC_PRINT_RET_ERROR(0, 0);
            break;
    }
}

// Depends on customer.
void VideoFunc_UVCXUCmd_RecordTimeCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_RECORDTIME_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_RecordResCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_RECORDRES_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_FileCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    // TBD
}

void VideoFunc_UVCXUCmd_PictureCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_PICTURE_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_GSensorCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_GSENSOR_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_AudioCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_AUDIO_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_RecordStatusCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_REC_STATUS_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_RecordModeCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_REC_MODE_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_FirmwareCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    // TBD
}

void VideoFunc_UVCXUCmd_MMCCtl(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    VideoFunc_UVCXUCmd_CommonCtl(UVC_XU_MMC_CONTROL, pCmd, pResult, ulCmdLen, ulResultLen);
}

void VideoFunc_UVCXUCmd_SwitchMSDCMode(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    if (VideoFunc_GetRecordStatus() == AHC_FALSE)
    {
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_VIDEO_UVC_XU_SWITCH_MSDC_MODE, 0);
    }
}

void VideoFunc_UVCXUCmd_MMP16CmdHandler(MMP_UBYTE *pCmd, MMP_UBYTE *pResult, MMP_ULONG ulCmdLen, MMP_ULONG ulResultLen)
{
    AHC_DBG_MSG(1, "%s,%d cmd:0x%x\r\n", __func__, __LINE__, pCmd[0]);

    switch(pCmd[0]) {
        case UVC_XU_RECORDTIME_CONTROL:
            VideoFunc_UVCXUCmd_RecordTimeCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_RECORDRES_CONTROL:
            VideoFunc_UVCXUCmd_RecordResCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_FILE_CONTROL:
            VideoFunc_UVCXUCmd_FileCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_PICTURE_CONTROL:
            VideoFunc_UVCXUCmd_PictureCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_GSENSOR_CONTROL:
            VideoFunc_UVCXUCmd_GSensorCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_AUDIO_CONTROL:
            VideoFunc_UVCXUCmd_AudioCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_REC_STATUS_CONTROL:
            VideoFunc_UVCXUCmd_RecordStatusCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_REC_MODE_CONTROL:
            VideoFunc_UVCXUCmd_RecordModeCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_FIRMWARE_CONTROL:
            VideoFunc_UVCXUCmd_FirmwareCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_MMC_CONTROL:
            VideoFunc_UVCXUCmd_MMCCtl(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        case UVC_XU_SWITCH_MSDC_MODE:
            VideoFunc_UVCXUCmd_SwitchMSDCMode(pCmd, pResult, ulCmdLen, ulResultLen);
            break;
        default:
            AHC_PRINT_RET_ERROR(0, pCmd[0]);
            break;
    }
}

AHC_BOOL VideoFunc_UVCXUCmdRegisterHandler(void)
{
    usb_vc_eu1_mmp_cmd16_register_handler((void *)VideoFunc_UVCXUCmd_MMP16CmdHandler);
    return AHC_TRUE;
}
#endif

#if (defined(SPEECH_RECOGNIZE_EN)&&(SPEECH_RECOGNIZE_EN))
//  char msginfo_1[] = "wo yao lu xiang";
//  char msginfo_2[] = "wo yao pai zhao";
//  char msginfo_3[] = "da kai lu yin";
//  char msginfo_4[] = "guan bi lu yin";
//  char msginfo_5[] = "da kai re dian";
//  char msginfo_6[] = "guan bi re dian";
//  char msginfo_7[] = "da kai ping mu";
//  char msginfo_8[] = "guan bi ping mu";
//  char msginfo_9[] ="qie huan hou lu";
//  char msginfo_10[]="hui dao qian lu";
void StateVideoRecSpeechCB(MMP_ULONG ID)
{
    AHC_DBG_MSG(1, "%s:SpeechRecogCB=%X...\r\n",__FUNCTION__,ID);

    if(1 == ID)
        AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_REC_REL, 0);
    else if(2 == ID)
        AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, BUTTON_REC_LPRESS, 0);
    else if(7 == ID){
        LCDPowerSaveCounterReset();
        if(LedCtrl_GetBacklightStatus()==AHC_FALSE/* && uiIsUsingLcd()*/)
        {
            LedCtrl_LcdBackLight(AHC_TRUE);
        }
    }
    else if(8 == ID){
        LCDPowerSaveCounterReset();
        if(LedCtrl_GetBacklightStatus()==AHC_TRUE/* && uiIsUsingLcd()*/)
        {
            LedCtrl_LcdBackLight(AHC_FALSE);
        }
    }
    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
    else if(5 == ID || 6 == ID){
        if (ID == 5 &&((NETAPP_NET_STATUS_DOWN == nhw_get_status()) || (NETAPP_NET_STATUS_NONE == nhw_get_status()) || (WLAN_SYS_GetMode() == -1)))
            AHC_WiFi_Switch(AHC_TRUE);
        else
            AHC_WiFi_Switch(AHC_FALSE);
    }
    #endif
}
#endif

// for ADAS_LDWS, TBD
AHC_BOOL StateVideoRecModeInitLCD(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevLCD();

#if (ENABLE_ADAS_LDWS)
    MMPS_ADAS_RegisterCallBack(LDWS_Callback);
#endif

#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
    if(Speech_AuthPass()){
        MMPS_AUDIO_InitLiveRecord(MMP_AUDIO_PCM_ENCODE, 0, 16000, (MMP_LivePCMCB)Speech_PCMTransferCB);
        MMPS_LiveAudio_StartRecord();
        Speech_SetCB((MMP_SpeechRecogCbFunc)StateVideoRecSpeechCB);
    }
#endif

    StateLedControl(UI_VIDEO_STATE);
    StateLCDCheckStatus(UI_VIDEO_STATE);

    RTNA_LCD_Backlight(MMP_TRUE);
    SetCurrentOpMode(VIDEOREC_MODE);
    //uiSysState.CurrentState = UI_VIDEO_STATE;   //When Hdmi remove ,Video ICON no display, need check
    ahcRet = VideoRecMode_Start();

    return ahcRet;
}

#if (TVOUT_ENABLE)
AHC_BOOL StateVideoRecModeInitTV(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    RTNA_LCD_Backlight(MMP_FALSE);
#ifdef CFG_ENBLE_PANEL_SLEEP
    RTNA_LCD_Enter_Sleep();
#endif

    ahcRet = AHC_SwitchDisplayOutputDevTVout();

#if (ENABLE_ADAS_LDWS)
    //LDWS_RegistCallback(LDWS_Callback);
    MMPS_ADAS_RegisterCallBack(LDWS_Callback);
#endif

    //StateLedControl(UI_VIDEO_STATE);
    //StateLCDCheckStatus(UI_VIDEO_STATE);

    //AHC_SetMode(AHC_MODE_IDLE);

    SetCurrentOpMode(VIDEOREC_MODE);
    //uiSysState.CurrentState = UI_VIDEO_STATE;   //When Hdmi remove ,Video ICON no display, need check
    ahcRet = VideoRecMode_Start();

    return ahcRet;
}
#endif

#if (HDMI_PREVIEW_EN)
AHC_BOOL StateVideoRecModeInitHDMI(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    RTNA_LCD_Backlight(MMP_FALSE);
#ifdef CFG_ENBLE_PANEL_SLEEP
    RTNA_LCD_Enter_Sleep();
#endif

    //AHC_SetMode(AHC_MODE_IDLE);

    ahcRet = AHC_SwitchDisplayOutputDevHDMI();

#if (ENABLE_ADAS_LDWS)
    //LDWS_RegistCallback(LDWS_Callback);
    ADAS_CTL_RegistCallback(LDWS_Callback);
#endif

    StateLedControl(UI_VIDEO_STATE);
    //StateLCDCheckStatus(UI_VIDEO_STATE);

    SetCurrentOpMode(VIDEOREC_MODE);
    //uiSysState.CurrentState = UI_VIDEO_STATE;   //When Hdmi remove ,Video ICON no display, need check
    ahcRet = VideoRecMode_Start();
    //return StateVideoRecModeInitLCD();

    return ahcRet;
}
#endif

AHC_BOOL VideoFunc_Init_NoDisplay(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    return ahcRet;
}

AHC_BOOL StateVideoRecModeShutDown(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (uiGetParkingModeEnable() == AHC_TRUE) {
        VideoFunc_ParkingModeStop();
    }

    if (VideoFunc_GetRecordStatus()) {
        StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
    }

#if (VR_PREENCODE_EN)
    bDisableVideoPreRecord = AHC_TRUE;
#endif

    g_bDrawUnfix = MMP_FALSE;

    VideoTimer_Stop();

    if (AHC_WMSG_States()) {
        AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
    }

#if (MOTION_DETECTION_EN)
#if (defined(PROJECT_ID) && (PROJECT_ID == PROJECT_ID_SP86G || PROJECT_ID == PROJECT_ID_SP20G))
    if (m_ubMotionDtcEn)
    {
        VideoFunc_ExitVMDMode();
    }
#endif
#endif

#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
    MMPS_LiveAudio_StopRecord();
#endif

    AHC_SetMode(AHC_MODE_IDLE);

    #if (UVC_HOST_VIDEO_ENABLE)
    if (MMP_IsUSBCamExist()) {
        ahcRet = AHC_HostUVC_SetIdleStates();
    }
    #endif

    return ahcRet;
}

AHC_BOOL StateSelectFuncVideoRecordMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

    uiSaveCurrentState();

#if 0//#ifndef CFG_MENU_CAMERA_ALWAYS_ENTER_CAPTURE_MODE //may be defined in config_xxx.h
    if(AHC_TRUE == StateIsInMenuMode()){
        StateModeSetOperation(UI_VIDEO_STATE, (void*)StateVideoRecModeInitFromMenu, (void*)StateVideoRecModeShutDown, (void *)StateVideoRecModeHandler);
    }
    else
#endif
    {
        // Common function.
        #if (VIDEO_DIGIT_ZOOM_EN)
        RegisterEventCb(EVENT_KEY_TELE_PRESS,           STATE_VIDEO_REC_MODE_EVENT_KEY_TELE_PRESS_LCD);
        RegisterEventCb(EVENT_KEY_WIDE_PRESS,           STATE_VIDEO_REC_MODE_EVENT_KEY_WIDE_PRESS_LCD);
        RegisterEventCb(EVENT_KEY_WIDE_STOP,            STATE_VIDEO_REC_MODE_EVENT_KEY_WIDE_STOP_LCD);
        #endif

        RegisterEventCb(EVENT_EV_INCREASE,              STATE_VIDEO_REC_MODE_EVENT_EV_INCREASE_LCD);
        RegisterEventCb(EVENT_EV_DECREASE,              STATE_VIDEO_REC_MODE_EVENT_EV_DECREASE_LCD);
        RegisterEventCb(EVENT_MENU_EXIT,                STATE_VIDEO_REC_MODE_EVENT_MENU_EXIT_LCD);
        RegisterEventCb(EVENT_KEY_LEFT,                 STATE_VIDEO_REC_MODE_EVENT_KEY_LEFT_LCD);
        RegisterEventCb(EVENT_KEY_RIGHT,                STATE_VIDEO_REC_MODE_EVENT_KEY_RIGHT_LCD);
        RegisterEventCb(EVENT_KEY_SET,                  STATE_VIDEO_REC_MODE_EVENT_KEY_SET_LCD);
        RegisterEventCb(EVENT_KEY_MENU,                 STATE_VIDEO_REC_MODE_EVENT_KEY_MENU_LCD);
        RegisterEventCb(EVENT_KEY_MODE,                 STATE_VIDEO_REC_MODE_EVENT_KEY_MODE_LCD);
        RegisterEventCb(EVENT_VIDEO_KEY_RECORD,         STATE_VIDEO_REC_MODE_EVENT_VIDEO_KEY_RECORD_LCD);
        RegisterEventCb(EVENT_VIDEO_KEY_SWAP_PIP,       STATE_VIDEO_REC_MODE_EVENT_VIDEO_KEY_SWAP_PIP_LCD);
        RegisterEventCb(EVENT_RECORD_MUTE,              STATE_VIDEO_REC_MODE_EVENT_RECORD_MUTE_LCD);
        RegisterEventCb(EVENT_KEY_PLAYBACK_MODE,        STATE_VIDEO_REC_MODE_EVENT_KEY_PLAYBACK_MODE_LCD);
        RegisterEventCb(EVENT_POWER_OFF,                STATE_VIDEO_REC_MODE_EVENT_POWER_OFF_LCD);
        RegisterEventCb(EVENT_CHANGE_LED_MODE,          STATE_VIDEO_REC_MODE_EVENT_CHANGE_LED_MODE_LCD);
        RegisterEventCb(EVENT_PARKING_KEY,              STATE_VIDEO_REC_MODE_EVENT_PARKING_KEY_LCD);
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
        RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,       STATE_VIDEO_REC_MODE_EVENT_ENTER_NET_PLAYBACK_LCD);
        #if 1
        RegisterEventCb(EVENT_VR_EMERGENT,              STATE_VIDEO_REC_MODE_EVENT_VR_EMERGENT_LCD);
        RegisterEventCb(EVENT_LOCK_FILE_G,              STATE_VIDEO_REC_MODE_EVENT_LOCK_FILE_G_LCD);
        RegisterEventCb(EVENT_VRCB_EMER_DONE,           STATE_VIDEO_REC_MODE_EVENT_VRCB_EMER_DONE_LCD);
        #else
        RegisterEventCb(EVENT_VR_EMERGENT,              STATE_VIDEO_REC_MODE_EVENT_CGI_DUMMY);
        RegisterEventCb(EVENT_LOCK_FILE_G,              STATE_VIDEO_REC_MODE_EVENT_CGI_DUMMY);
        #endif
        #if (AHC_SHAREENC_SUPPORT)
        RegisterEventCb(EVENT_VR_SHORT,                 STATE_VIDEO_REC_MODE_EVENT_REC_SHORT);
        #endif
        RegisterEventCb(EVENT_NET_DOWNLOAD,             STATE_VIDEO_REC_MODE_EVENT_DOWNLOAD);
        RegisterEventCb(EVENT_WIFI_SWITCH_ENABLE,       STATE_VIDEO_REC_MODE_EVENT_NET_ONOFF);
#else
        #if (EMERGENTRECD_SUPPORT)
        RegisterEventCb(EVENT_VR_EMERGENT,              STATE_VIDEO_REC_MODE_EVENT_VR_EMERGENT_LCD);
        RegisterEventCb(EVENT_LOCK_FILE_G,              STATE_VIDEO_REC_MODE_EVENT_LOCK_FILE_G_LCD);
        RegisterEventCb(EVENT_VRCB_EMER_DONE,           STATE_VIDEO_REC_MODE_EVENT_VRCB_EMER_DONE_LCD);
        #endif
#endif
#ifdef LED_GPIO_LASER
        RegisterEventCb(EVENT_LASER_LED_ONOFF,          STATE_VIDEO_REC_MODE_EVENT_LASER_LED_ONOFF_LCD);
#endif
        RegisterEventCb(EVENT_FORMAT_MEDIA,             STATE_VIDEO_REC_MODE_EVENT_FORMAT_MEDIA_LCD);
        RegisterEventCb(EVENT_VIDEO_KEY_CAPTURE,        STATE_VIDEO_REC_MODE_EVENT_VIDEO_KEY_CAPTURE_LCD);
        RegisterEventCb(EVENT_CAMERA_PREVIEW,           STATE_VIDEO_REC_MODE_EVENT_CAMERA_PREVIEW_LCD);

        RegisterEventCb(EVENT_USB_DETECT,               STATE_VIDEO_REC_MODE_EVENT_USB_DETECT_LCD);
        RegisterEventCb(EVENT_USB_REMOVED,              STATE_VIDEO_REC_MODE_EVENT_USB_REMOVED_LCD);
        RegisterEventCb(EVENT_SD_DETECT,                STATE_VIDEO_REC_MODE_EVENT_SD_DETECT_LCD);
        RegisterEventCb(EVENT_SD_REMOVED,               STATE_VIDEO_REC_MODE_EVENT_SD_REMOVED_LCD);
#if (TVOUT_ENABLE)
        RegisterEventCb(EVENT_TV_DETECT,                STATE_VIDEO_REC_MODE_EVENT_TV_DETECT_LCD);
        RegisterEventCb(EVENT_TV_REMOVED,               STATE_VIDEO_REC_MODE_EVENT_TV_REMOVED_LCD);
#endif
#if (HDMI_ENABLE)
        RegisterEventCb(EVENT_HDMI_DETECT,              STATE_VIDEO_REC_MODE_EVENT_HDMI_DETECT_LCD);
        RegisterEventCb(EVENT_HDMI_REMOVED,             STATE_VIDEO_REC_MODE_EVENT_HDMI_REMOVED_LCD);
#endif
        RegisterEventCb(EVENT_VRCB_MEDIA_FULL,          STATE_VIDEO_REC_MODE_EVENT_VRCB_MEDIA_FULL_LCD);
        RegisterEventCb(EVENT_VRCB_FILE_FULL,           STATE_VIDEO_REC_MODE_EVENT_VRCB_FILE_FULL_LCD);
        RegisterEventCb(EVENT_VRCB_SHARE_FILE_FULL,     STATE_VIDEO_REC_MODE_EVENT_VRCB_SHARE_FILE_FULL_LCD);
        RegisterEventCb(EVENT_VRCB_LONG_TIME_FILE_FULL, STATE_VIDEO_REC_MODE_EVENT_VRCB_LONG_TIME_FILE_FULL_LCD);
        RegisterEventCb(EVENT_VRCB_MEDIA_SLOW,          STATE_VIDEO_REC_MODE_EVENT_VRCB_MEDIA_SLOW_LCD);
        RegisterEventCb(EVENT_VRCB_RECDSTOP_CARDSLOW,   STATE_VIDEO_REC_MODE_EVENT_VRCB_RECDSTOP_CARDSLOW_LCD);
        RegisterEventCb(EVENT_VRCB_SEAM_LESS,           STATE_VIDEO_REC_MODE_EVENT_VRCB_SEAM_LESS_LCD);
        RegisterEventCb(EVENT_VRCB_MEDIA_ERROR,         STATE_VIDEO_REC_MODE_EVENT_VRCB_MEDIA_ERROR_LCD);
        RegisterEventCb(EVENT_VRCB_MOTION_DTC,          STATE_VIDEO_REC_MODE_EVENT_VRCB_MOTION_DTC_LCD);
        RegisterEventCb(EVENT_VR_START,                 STATE_VIDEO_REC_MODE_EVENT_VR_START_LCD);
        RegisterEventCb(EVENT_VR_STOP,                  STATE_VIDEO_REC_MODE_EVENT_VR_STOP_LCD);
        RegisterEventCb(EVENT_VR_WRITEINFO,             STATE_VIDEO_REC_MODE_EVENT_VR_WRITEINFO_LCD);
        RegisterEventCb(EVENT_LOCK_VR_FILE,             STATE_VIDEO_REC_MODE_EVENT_LOCK_VR_FILE_LCD);
        RegisterEventCb(EVENT_VIDREC_UPDATE_MESSAGE,    STATE_VIDEO_REC_MODE_EVENT_VIDREC_UPDATE_MESSAGE_LCD);
        RegisterEventCb(EVENT_TIMESTAMP_UPDATE,         STATE_VIDEO_REC_MODE_EVENT_TIMESTAMP_UPDATE_LCD);
#if (UVC_HOST_VIDEO_ENABLE)
        RegisterEventCb(EVENT_USB_B_DEVICE_DETECT,      STATE_VIDEO_REC_MODE_EVENT_USB_B_DEVICE_DETECT_LCD);
        RegisterEventCb(EVENT_USB_B_DEVICE_REMOVED,     STATE_VIDEO_REC_MODE_EVENT_USB_B_DEVICE_DETECT_LCD);
#endif

        RegisterEventCb(EVENT_LDWS_START,               STATE_VIDEO_REC_MODE_EVENT_LDWS_START_LCD);
        RegisterEventCb(EVENT_LDWS_STOP,                STATE_VIDEO_REC_MODE_EVENT_LDWS_STOP_LCD);
        RegisterEventCb(EVENT_FCWS_START,               STATE_VIDEO_REC_MODE_EVENT_FCWS_START_LCD);
        RegisterEventCb(EVENT_FCWS_STOP,                STATE_VIDEO_REC_MODE_EVENT_FCWS_STOP_LCD);
        RegisterEventCb(EVENT_SAG_START,                STATE_VIDEO_REC_MODE_EVENT_SAG_START_LCD);
        RegisterEventCb(EVENT_SAG_STOP,                 STATE_VIDEO_REC_MODE_EVENT_SAG_STOP_LCD);

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE)
        RegisterEventCb(EVENT_VIDEO_UVC_XU_RECORDTIME_CONTROL,  STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_RECORDTIME_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_RECORDRES_CONTROL,   STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_RECORDRES_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_FILE_CONTROL,        STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_FILE_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_PICTURE_CONTROL,     STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_PICTURE_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_GSENSOR_CONTROL,     STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_GSENSOR_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_AUDIO_CONTROL,       STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_AUDIO_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_REC_MODE_CONTROL,    STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_REC_MODE_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_STATUS_CONTROL,      STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_STATUS_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_FIRMWARE_CONTROL,    STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_FIRMWARE_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_MMC_CONTROL,         STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_MMC_CONTROL);
        RegisterEventCb(EVENT_VIDEO_UVC_XU_SWITCH_MSDC_MODE,    STATE_VIDEO_REC_MODE_EVENT_VIDEO_UVC_XU_SWITCH_MSDC_MODE);
#endif

        RegisterEventCb(EVNET_SUB_MODE_ENTER,           STATE_VIDEO_REC_MODE_EVNET_SUB_MODE_ENTER_LCD);
        RegisterEventCb(EVNET_SUB_MODE_EXIT,            STATE_VIDEO_REC_MODE_EVNET_SUB_MODE_EXIT_LCD);

        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            RegisterEventCb(EVENT_TV_DECODER_SRC_TYPE,  STATE_VIDEO_REC_MODE_EVENT_TV_DECODER_SRC_TYPE_LCD);
        }

        #if (HDMI_ENABLE)
        MMPF_OS_Sleep_MS(5);
        if (AHC_IsHdmiConnect()){//LCD
            //Register HDMI specific functions here!
            StateModeSetOperation(UI_VIDEO_STATE, StateVideoRecModeInitHDMI, StateVideoRecModeShutDown, StateVideoRecModeHandler);
        }
        else
        #endif
        #if (TVOUT_ENABLE)
        if (AHC_IsTVConnectEx()){
            StateModeSetOperation(UI_VIDEO_STATE, StateVideoRecModeInitTV, StateVideoRecModeShutDown, StateVideoRecModeHandler);
        }else
        #endif
        {
            StateModeSetOperation(UI_VIDEO_STATE, StateVideoRecModeInitLCD, StateVideoRecModeShutDown, StateVideoRecModeHandler);
        }
    }

    ahcRet =  SwitchUIDrawSetVideoRecordMode();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,ahcRet); return ahcRet;}

    return ahcRet;
}


//For parking mode.
#if (ENABLE_ADAS_LDWS || ENABLE_ADAS_FCWS || ENABLE_ADAS_SAG)
//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeInitADASMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeInitADASMode(void)
{
    UINT8 byType = MMPS_3GPRECD_Y_FRAME_TYPE_NONE;
    UINT32 bLDWS_En = COMMON_LDWS_EN_OFF;
    UINT32 bFCWS_En = COMMON_FCWS_EN_OFF;
    UINT32 bSAG_En  = COMMON_SAG_EN_OFF;
    UINT32 uiAdasFlag = 0;

    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_GetParam(PARAM_ID_ADAS, &uiAdasFlag);

#if (ENABLE_ADAS_LDWS)
    #ifdef CFG_ADAS_MENU_SETTING_OLD_STYLE
    if (MenuSettingConfig()->uiLDWS == COMMON_LDWS_EN_ON)
    #else
    if (uiAdasFlag & AHC_ADAS_ENABLED_LDWS)
    #endif
    {
        bLDWS_En = COMMON_LDWS_EN_ON;
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_LDWS, MMP_TRUE);
    }
    else
    {
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_LDWS, MMP_FALSE);
    }
#endif

#if (ENABLE_ADAS_FCWS)
    #ifdef CFG_ADAS_MENU_SETTING_OLD_STYLE
    if (MenuSettingConfig()->uiFCWS == COMMON_FCWS_EN_ON)
    #else
    if (uiAdasFlag & AHC_ADAS_ENABLED_FCWS)
    #endif
    {
        bFCWS_En = COMMON_FCWS_EN_ON;
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_FCWS, MMP_TRUE);
    }
    else
    {
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_FCWS, MMP_FALSE);
    }
#endif

#if (ENABLE_ADAS_SAG)
    if (uiAdasFlag & AHC_ADAS_ENABLED_SAG)
    {
        bSAG_En = COMMON_SAG_EN_ON;
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_SAG, MMP_TRUE);
    }
    else
    {
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_SAG, MMP_FALSE);
    }
#endif

    if (bLDWS_En == COMMON_LDWS_EN_ON ||
        bFCWS_En == COMMON_FCWS_EN_ON ||
        bSAG_En  == COMMON_SAG_EN_ON)
    {
        byType = MMPS_3GPRECD_Y_FRAME_TYPE_ADAS;
    }

    // It must be set before enter Preview mode
    MMPS_3GPRECD_SetYFrameType(byType);

    ahcRet = AHC_VIDEO_SetRecordModeInitCommon();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, 0); return ahcRet;}

#if (ENABLE_ADAS_LDWS || ENABLE_ADAS_FCWS || ENABLE_ADAS_SAG)

    #if (MOTION_DETECTION_EN)
    if (MMPS_Sensor_IsVMDEnable()== MMP_FALSE)
    #else
    if (1)
    #endif
    {
        UINT32 uiAdasFlag = 0;

        AHC_GetParam(PARAM_ID_ADAS, &uiAdasFlag);

        #ifdef CFG_ADAS_MENU_SETTING_OLD_STYLE
        if ((MenuSettingConfig()->uiLDWS == COMMON_LDWS_EN_ON) ||
            (MenuSettingConfig()->uiFCWS == COMMON_FCWS_EN_ON) ||
            (uiAdasFlag & AHC_ADAS_ENABLED_SAG))
        #else
        if ((uiAdasFlag & AHC_ADAS_ENABLED_LDWS) ||
            (uiAdasFlag & AHC_ADAS_ENABLED_FCWS) ||
            (uiAdasFlag & AHC_ADAS_ENABLED_SAG ) )
        #endif
        {
            AHC_EnableADAS(AHC_TRUE);
        }
        else {
            AHC_EnableADAS(AHC_FALSE);
        }
    }
#endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeUnInitADASMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeUnInitADASMode(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    MMP_ERR sRet = MMP_ERR_NONE;

    //Exec common uninit.
    ahcRet = AHC_VIDEO_SetRecordModeUnInitCommon();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, 0); return ahcRet;}

    MMPS_3GPRECD_SetYFrameType(MMPS_3GPRECD_Y_FRAME_TYPE_NONE);

    sRet = MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_LDWS, MMP_FALSE);
    sRet = MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_FCWS, MMP_FALSE);
    sRet = MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_SAG, MMP_FALSE);

    ahcRet = AHC_EnableADAS(AHC_FALSE);

    return ahcRet;
}
#endif

AHC_BOOL VideoFunc_ParkingModeStart(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if ((AHC_MODE_RECORD_PRERECD == AHC_GetAhcSysMode()) ||
        (AHC_MODE_VIDEO_RECORD == AHC_GetAhcSysMode())) {
        StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
    }

    AHC_SetMode(AHC_MODE_IDLE);

    uiSetParkingModeEnable(AHC_TRUE);

    #if (MOTION_DETECTION_EN)
    Menu_SetMotionDtcSensitivity(MenuSettingConfig()->uiMotionDtcSensitivity);

    m_ulVMDStableCnt = MOTION_DETECTION_STABLE_TIME * 1000 / (VIDEO_TIMER_UNIT*10);// REF::VideoTimer_ISR_Slow(tmr, arg); //100 ms
    m_ubVMDStart     = AHC_FALSE;
    #endif

    ahcRet = VIDEO_REC_MODE_EVENT_PARKING_REGCB(AHC_TRUE);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(0, 0); return ahcRet;}

    return ahcRet;
}

AHC_BOOL VideoFunc_ParkingModeStop(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if ( (AHC_MODE_RECORD_PRERECD == AHC_GetAhcSysMode()) || (AHC_MODE_VIDEO_RECORD == AHC_GetAhcSysMode()) ){
        StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
    }

    AHC_SetMode(AHC_MODE_IDLE);

    uiSetParkingModeEnable(AHC_FALSE);

    #if (MOTION_DETECTION_EN)
    Menu_SetMotionDtcSensitivity(MOTION_DTC_SENSITIVITY_OFF/* MenuSettingConfig()->uiMotionDtcSensitivity */);
    m_ubVMDStart     = AHC_FALSE;
    m_ulVMDStopCnt   = 0;
    m_ulVMDStableCnt = 0;
    #endif

    ahcRet = VIDEO_REC_MODE_EVENT_PARKING_REGCB(AHC_FALSE);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(0, 0); return ahcRet;}

    return ahcRet;
}

#if (MOTION_DETECTION_EN)
//------------------------------------------------------------------------------
//  Function    : VRMotionDetectCB
//  Description :
//------------------------------------------------------------------------------
void VRMotionDetectCB(void)
{
    static AHC_BOOL bRunning = AHC_FALSE;
    static MMP_ULONG ulPreviousTime = 0;
    MMP_ULONG ulCurrentTime;

    // Add this protection since it may be called by multi-tasks
    if (bRunning == AHC_TRUE) {
        return;
    }

    bRunning = AHC_TRUE;

    #if (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_1)
    if (uiGetParkingModeEnable())
    {
        if (m_ubVMDStart)
        {
            // Update VMD stop recording timer
            m_ulVMDStopCnt = AHC_GetVMDRecTimeLimit() * 8;
        }

        if (!VideoFunc_GetRecordStatus())
        {
            AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MOTION_DTC, 0);
        }
    }
    #elif (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
    if (uiGetParkingModeEnable())
    {
        UINT32 ulTickCount = 0;
        AHC_OS_GetTime(&ulTickCount);
        ulCurrentTime = (ulTickCount * 1000) / OS_TICKS_PER_SEC;
        if ((ulCurrentTime - ulPreviousTime) > 500) // SW debounce
        {
            ulPreviousTime = ulCurrentTime;
            AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MOTION_DTC, 0);
        }
    }
    #elif (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_3)
    if (uiGetParkingModeEnable())
    {
        UINT32 ulTickCount = 0;
        AHC_OS_GetTime(&ulTickCount);
        ulCurrentTime = (ulTickCount * 1000) / OS_TICKS_PER_SEC;
        if ((ulCurrentTime - ulPreviousTime) > 500) // SW debounce
        {
            ulPreviousTime = ulCurrentTime;
            AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MOTION_DTC, 0);
        }
    }
    #else
    if (uiGetParkingModeEnable())
    {
        UINT32 ulTickCount = 0;
        AHC_OS_GetTime(&ulTickCount);
        ulCurrentTime = (ulTickCount * 1000) / OS_TICKS_PER_SEC;
        if ((ulCurrentTime - ulPreviousTime) > 500) // SW debounce
        {
            ulPreviousTime = ulCurrentTime;
            AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MOTION_DTC, 0);
        }
    }
    #endif

    bRunning = AHC_FALSE;
}
#endif
