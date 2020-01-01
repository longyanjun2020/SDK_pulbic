/*
 * AHC_Stream.c
 */
//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "ahc_general.h"
#include "ahc_stream.h"
#include "ahc_audio.h"
#include "ahc_video.h"
#include "ahc_sensor.h"
#include "ahc_display.h"
#include "AHC_V4L.h"
#include "ahc_usbhost.h"
#include "MenuSetting.h"
#include "mmpf_ringbuf.h"
#include "mmpf_streaming.h"
#include "mmpf_usbh_uvc.h"
#include "mmp_media_def.h"
#include "mmps_iva.h"
#include "mmps_audio.h"
#include "mmps_sensor.h"
#include "mmps_vidplay.h"
#include "mmps_3gprecd.h"
#include "mmps_dsc.h"
#include "mmpd_dsc.h"
#include "netapp.h"
#include "usb_cfg.h"
#include "snr_cfg.h"
#include "component_dip.h"
#include "component_scl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#if (defined(WIFI_PORT) && WIFI_PORT == 1)

#define SET_VID_PRE_REC_MODE (0)

#define IS_TRANSCODING(streamingMode) (streamingMode & AHC_STREAM_TRANSCODE)
#define IS_RESUME(streamingMode) (streamingMode & AHC_STREAM_RESUME)

#define MMP_H264_ALIGNMENT  (32)

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

static MMP_MJPEG_OBJ_PTR            m_sMjpegHdl;
static AHC_STREAMING_MODE           m_AhcStreamingMode      = AHC_STREAM_NONE;
static AHC_STREAMING_MODE           m_AhcStreamingResume    = AHC_STREAM_NONE;
static MMP_ULONG                    mCompressThreshold;

void*                        m_sH264WifiHdl[VR_MAX_H264_STREAM_NUM];

static MMP_UBYTE VidCnxt[] = "Transcode";

UINT32 h264StreamStart, h264StreamSize;

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
INT32   gslCGIFeedbackStatus    = 0;
UINT32  gulCGIFeedbackEvent     = 0;
UINT32 ulLastWiFiChagneTime = (UINT32) -1;
#endif

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

INT32 AIHC_CloseTranscode(void);

#if (SET_VID_PRE_REC_MODE)
void VRSeamlessCB(void);
void VRFileFullCB(void);
void VRMediaFullCB(void);
void VRMediaErrorCB(MMP_ULONG VideoStatus, MMP_ULONG VideoFileErr);
#endif
#if (MOTION_DETECTION_EN)
void VRMotionDetectCB(void);
#endif
void AIHC_SetH264Buf(UINT32 addr, UINT32 size);
AHC_BOOL AHC_Config2ndVideo(AHC_VIDEO_2ND_CONFIG *cfg);

extern MMP_USHORT   gsAhcUsbhSensor;

extern AHC_BOOL     m_ubMotionDtcEn;
extern MMP_DISPLAY_OUTPUT_SEL   gsAhcCurrentDisplay;
extern AHC_BOOL                 gbAhcDbgBrk;

static AHC_BOOL AIHC_StartH264WifiStream(MMP_UBYTE ubSnrSel);
INT32 WLAN_SYS_GetMode(void);

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____WIFI_Function____(){ruturn;} //dummy
#endif

/***********************************************************************************************/
//      function: AHC_Get_WiFi_Streaming_Status()
//   description: To read whether WiFi is streaming or not..
//      output  : True stands for Streaming.
/***********************************************************************************************/
AHC_BOOL AHC_Get_WiFi_Streaming_Status(void)
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    return ns_get_streaming_status() & NETAPP_STREAM_PLAY;
#else
    return AHC_FALSE;
#endif
}

void AHC_WiFi_Toggle_StreamingMode(void)
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    short   en;

    if(!AHC_Get_WiFi_Streaming_Status() && AHC_GetStreamingMode() == AHC_STREAM_OFF)
        en = 1;
    else
        en = 0;
    ncam_set_streaming(en);
#endif
}

ULONG AHC_CheckWiFiOnOffInterval(MMP_ULONG waiting_time)
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    MMP_ULONG ulNow;
    MMP_ULONG ulExpend;

    MMPF_OS_GetTime(&ulNow);

    if (-1 != ulLastWiFiChagneTime) {
        if (ulNow >= ulLastWiFiChagneTime) {
            ulExpend = TICK_TO_MS(ulNow - ulLastWiFiChagneTime);
        }
        else {
            ulExpend = TICK_TO_MS(((MMP_ULONG) (-1)) - ulLastWiFiChagneTime + ulNow);
        }

        if (ulExpend < waiting_time) {
            return (waiting_time - ulExpend);
        }
    }
#endif

    return 0;
}

AHC_BOOL AHC_WiFi_Switch(AHC_BOOL wifi_switch_on)
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    #undef WIFI_ON_DELAY_TIME
    #undef WIFI_OFF_DELAY_TIME
    #define WIFI_ON_DELAY_TIME                  (2000)      // ms
    #define WIFI_OFF_DELAY_TIME                 (2000)      // ms

    UINT32 ulWiFiFlag = WIFI_MODE_OFF;
    AHC_BOOL wifi_sw;

    wifi_sw = wifi_switch_on;

    if (NETAPP_NET_STATUS_INIT_FAIL == nhw_get_status())
        return AHC_FALSE;

    if (NETAPP_NET_STATUS_INIT == nhw_get_status()) {
        MMPF_OS_GetTime(&ulLastWiFiChagneTime);
        return AHC_TRUE;
    }

    AHC_Menu_SettingGetCB((char*) COMMON_KEY_WIFI_EN, &ulWiFiFlag);

    if (WIFI_MODE_OFF == ulWiFiFlag) {
        wifi_sw = AHC_FALSE;
    }

    if (AHC_TRUE == wifi_switch_on) {
        if ((NETAPP_NET_STATUS_NONE == nhw_get_status()) ||
            (NETAPP_NET_STATUS_DOWN == nhw_get_status())) {
            if (AHC_CheckWiFiOnOffInterval(WIFI_OFF_DELAY_TIME)) {
                return AHC_FALSE;
            }

            RTNA_DBG_Str0(BG_GREEN("\r\nnhw_init_network\r\n"));
            printc(FG_GREEN("%s: nhw_get_status = 0x%X, %d\r\n"), __FUNCTION__, nhw_get_status(), wifi_switch_on);

            #if 0//CUS_SDIO_CONNECTION
            if (CheckWifiModuleConnect())
            #endif
            {
                nhw_init_network();
                MMPF_OS_GetTime(&ulLastWiFiChagneTime);
            }
        }
    }
    else {
        if (WLAN_SYS_GetMode() != -1) {
            if (AHC_Get_WiFi_Streaming_Status()){
                RTNA_DBG_Str0(BG_GREEN("\r\nncam_set_streaming off\r\n"));
                ncam_set_streaming(0);
            }

            if (NETAPP_NET_STATUS_DOWN != nhw_get_status()) {
                if (AHC_CheckWiFiOnOffInterval(WIFI_OFF_DELAY_TIME)) {
                    printc(FG_GREEN("%s:stop network twice\r\n"), __FUNCTION__);
                    return AHC_FALSE;
                }
                RTNA_DBG_Str0(BG_GREEN("\r\nnhw_stop_network\r\n"));
                printc(FG_GREEN("%s: nhw_get_status = 0x%X, %d\r\n"), __FUNCTION__, nhw_get_status(), wifi_switch_on);

                nhw_stop_network();
                MMPF_OS_GetTime(&ulLastWiFiChagneTime);
            }
        }
    }
#endif

    return AHC_TRUE;
}

#if 0
void ____Streaming_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AIHC_VIDEO_MapFromRawVRes
//  Description : Map Integer Video resolutions to AHC resolution
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_VIDEO_MapFromRawVRes(UINT16 w, UINT16 h, AHC_VIDRECD_RESOL *AhcRes)
{
    if (w >= 2688) {
        *AhcRes = AHC_VIDRECD_RESOL_3200x1808;
    }
    else if (w >= 2560) {
        *AhcRes = AHC_VIDRECD_RESOL_2560x1440;
    }
    else if (w >= 2304) {
        *AhcRes = AHC_VIDRECD_RESOL_2304x1296;
    }
    else if (w >= 1920) {
        *AhcRes = AHC_VIDRECD_RESOL_1920x1088;
    }
    else if (w >= 1600) {
        *AhcRes = AHC_VIDRECD_RESOL_1600x900;
    }
    else if (w >= 1440) {
        *AhcRes = AHC_VIDRECD_RESOL_1440x1088;
    }
    else if (w >= 1280) {
        if (h >= 960) {
            *AhcRes = AHC_VIDRECD_RESOL_1280x960;
        }
        else {
            *AhcRes = AHC_VIDRECD_RESOL_1280x720;
        }
    }
    else if (w >= 720) {
        *AhcRes = AHC_VIDRECD_RESOL_720x480;
    }
    else if (w >= 640) {
        if (h == 360)
            *AhcRes = AHC_VIDRECD_RESOL_640x360;
        else
            *AhcRes = AHC_VIDRECD_RESOL_640x480;
    }
    else {
        *AhcRes = AHC_VIDRECD_RESOL_MAX;
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_VIDEO_MapToRawVRes
//  Description : Map AHC resolution to Integer Video resolutions
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_VIDEO_MapToRawVRes(AHC_VIDRECD_RESOL res, UINT16 *w, UINT16 *h)
{
    switch(res) {
    case AHC_VIDRECD_RESOL_640x360:
        *w = 640;
        *h = 360;
        break;
    case AHC_VIDRECD_RESOL_640x480:
        *w = 640;
        *h = 480;
        break;
    case AHC_VIDRECD_RESOL_720x480:
        *w = 720;
        *h = 480;
        break;
    case AHC_VIDRECD_RESOL_1280x720:
        *w = 1280;
        *h = 720;
        break;
    case AHC_VIDRECD_RESOL_1280x960:
        *w = 1280;
        *h = 960;
        break;
    case AHC_VIDRECD_RESOL_1440x1088:
        *w = 1440;
        *h = 1080;
        break;
    case AHC_VIDRECD_RESOL_1600x900:
        *w = 1600;
        *h = 912;
        break;
    case AHC_VIDRECD_RESOL_1920x1088:
        *w = 1920;
        *h = 1080;
        break;
    case AHC_VIDRECD_RESOL_2304x1296:
        *w = 2304;
        *h = 1296;
        break;
    case AHC_VIDRECD_RESOL_2560x1440:
        *w = 2560;
        *h = 1440;
        break;
    case AHC_VIDRECD_RESOL_3200x1808:
        *w = 3200;
        *h = 1800;
        break;
    default:
        *h = 0;
        *w = 0;
        return MMP_FALSE;
        break;
    }
    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : VideoPlayStopCb
//  Description :
//------------------------------------------------------------------------------
static void VideoPlayStopCb(void *Context, MMP_ULONG flag1, MMP_ULONG flag2)
{
    printc("%s Video stopped with flag %X, %X\r\n", Context, flag1, flag2);
}

//------------------------------------------------------------------------------
//  Function    : VideoRecordStreamCallback
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL VideoRecordStreamCallback(MMP_M_STREAMCB_ACTION cb_action, MMP_ULONG framesize, MMP_M_STREAM_INFO* moveinfo)
{
    return vidioc_notify(cb_action, framesize, moveinfo);
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetStreamingMode
//  Description :
//------------------------------------------------------------------------------
AHC_STREAMING_MODE AHC_GetStreamingMode(void)
{
    return m_AhcStreamingMode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Config2ndVideo
//  Description :
//------------------------------------------------------------------------------
#if (defined(WIFI_PORT) && WIFI_PORT == 1)
AHC_BOOL AHC_Config2ndVideo(AHC_VIDEO_2ND_CONFIG *cfg)
{
    const UINT16 stream = 1;
    UINT32 effective_bitrate, bitrate;

    switch (cfg->vFormat) {
    case AHC_MOVIE_VIDEO_CODEC_YUV422:
        AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_RESOLUTION, AHC_VIDRECD_RESOL_AUTO);
        break;
    case AHC_MOVIE_VIDEO_CODEC_MJPEG:
        AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_RESOLUTION, cfg->param.mj.ahcRes);
        AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_BITRATE, cfg->param.mj.Bitrate);
        bitrate = cfg->param.mj.Bitrate;
        break;
    case AHC_MOVIE_VIDEO_CODEC_H264:
        AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_RESOLUTION, cfg->param.h264.mmpRes);
        AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_BITRATE, cfg->param.h264.Bitrate);
        bitrate = cfg->param.h264.Bitrate;
        break;
    case AHC_MOVIE_VIDEO_CODEC_NONE:
        return AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_CODEC_TYPE, cfg->vFormat);
        break;
    default:
        return AHC_FALSE;
        break;
    }

    AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_CODEC_TYPE, cfg->vFormat);
    AHC_VIDEO_SetMovieCfg(stream, AHC_FRAME_RATE, cfg->FPS);

    cfg->FPS = AHC_VIDEO_GetVideoRealFpsX1000(cfg->FPS);
    cfg->FPS = cfg->FPS / AHC_VIDRECD_TIME_INCREMENT_BASE;

    // CHECK
    if (cfg->FpsOutx1000 > 0 && (cfg->FpsOutx1000 <= cfg->FPS * 1000)) {
        if (0 != ns_set_frc(cfg->FPS * 1000, cfg->FpsOutx1000, "VIDEO.0/EncMJPEG")) {
            return AHC_FALSE;
        }

        // Assume max 35,000,000 * 120 FPS and still not overflow.
        effective_bitrate = bitrate * cfg->FPS / cfg->FpsOutx1000 * 1000;
        printc("Effective Bitrate %d by %d in/out %d/%d\r\n",
               effective_bitrate, cfg->param.mj.Bitrate, cfg->FPS, cfg->FpsOutx1000);

        AHC_VIDEO_SetMovieCfg(stream, AHC_VIDEO_BITRATE, effective_bitrate);
    }
    return AHC_TRUE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_AdjustMJpegStreamResFromSnr
//  Description :
//------------------------------------------------------------------------------
void AHC_AdjustMJpegStreamResFromSnr(UINT16 w, UINT16 h, UINT16* suggestedWidth, UINT16* suggestedHeight)
{
    MMP_ULONG  SensorWidth, SensorHeight;
    MMP_ULONG  SuggestWidth, SuggestHeight;

    MMPS_Sensor_GetCurPrevScalInputRes(gsAhcPrmSensor, &SensorWidth, &SensorHeight);

    MMPS_Display_PureAdjustScaleInSize(MMP_FALSE, SensorWidth, SensorHeight, w, h, &SuggestWidth, &SuggestHeight);

    // Aligned with JEPG HW
    *suggestedWidth = ALIGN16(SuggestWidth);
    *suggestedHeight = ALIGN8(SuggestHeight);

    printc("Sensor %dx%d to preview MJPEG %dx%d\r\n", SensorWidth, SensorHeight, *suggestedWidth, *suggestedHeight);
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetMJpegStreamResolution
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetMJpegStreamResolution(UINT16 stream, UINT16 *pu16W, UINT16 *pu16H)
{
    UINT32      ulRes;
    MMP_USHORT  configWidth, configHeight;

    *pu16W = *pu16H = 0;

    if (AHC_FALSE == AHC_VIDEO_GetMovieCfg(stream, AHC_VIDEO_RESOLUTION, &ulRes)) {
        return AHC_FALSE;
    }

    if (AIHC_VIDEO_MapToRawVRes(ulRes, pu16W, pu16H) == MMP_FALSE) {
        printc ("--E-- unsupported resolution config %d\r\n", ulRes);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_IsMJPEGStreaming
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_IsMJPEGStreaming(void)
{
    return (AHC_STREAM_MJPEG == (m_AhcStreamingMode & AHC_STREAM_V_MASK));
}

//------------------------------------------------------------------------------
//  Function    : AIHC_Restore2ndVideo
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_Restore2ndVideo(void)
{
#if (SUPPORT_MJPEG_WIFI_STREAM)
    MMP_ERR err;

    err = MMPS_MJPEG_StopStream(m_sMjpegHdl);

    if (err == MMP_ERR_NONE) {

        #if (UVC_HOST_VIDEO_ENABLE)
        if (CAM_CHECK_USB(USB_CAM_AIT)) {
            if (MMP_MJPEG_STREAM_RCAM_VIDEO == m_sMjpegHdl->usEncID) {

                /* Disable Streaming to inform USB host driver */
                gUsbh_UvcMjpegWifiCfg.bEnWiFi = MMP_FALSE;

                /* Restore previous Mjpeg bitrate */
                //AHC_HostUVC_SetMjpegBitrate(gsUVCHostCfg.ulMjpegkbps);
            }
        }
        #endif
    }

    if (err == MMP_ERR_NONE) {
        return AHC_TRUE;
    }
    return AHC_FALSE;
#else
    return AHC_TRUE;
#endif
}

AHC_BOOL AIHC_ApplyVideoTranscoding(UINT16 streamID, AHC_BOOL bPlay)
{
    #if (VIDEO_DEC_TO_MJPEG)
    MMP_ERR err = MMP_ERR_NONE;
    UINT16 w, h;
    AHC_MODE_ID ahcMode = AHC_GetAhcSysMode();
    #endif
    UINT32 fpsx10, bitRate, fps;
    MMPF_FRAME_RING_BUF_HANDLE pVideoRing = MMPF_StreamRing_GetFrameRing(VIDEO1_RING_STREAM);

    // Set audio volume
    #if (AUDIO_SET_DB == 0x01)
    MMPS_AUDIO_SetPlayVolumeDb(95);
    #else
    MMPS_AUDIO_SetPlayVolume(12, MMP_FALSE);
    #endif

    #if (VIDEO_DEC_TO_MJPEG)
    // Initial Wifi MJPEG resolution
    if (AHC_FALSE == AHC_GetMJpegStreamResolution(streamID, &w, &h)) {
        AIHC_CloseTranscode();
        return AHC_FALSE;
    }
    MMPS_DSC_SetVideo2MJpegResol(w, h);

    if (AHC_MODE_NET_PLAYBACK   != ahcMode &&
        AHC_MODE_IDLE           != ahcMode &&
        AHC_MODE_THUMB_BROWSER  != ahcMode) {
        printc(FG_RED("Error. Cannot transcode during AHC MODE %X\r\n"), ahcMode);
        AIHC_CloseTranscode();
        return AHC_FALSE;
    }

    //set bit rate & FPS
    {
        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_BITRATE, &bitRate);
        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_FRAME_RATEx10, &fpsx10);
        MMPS_VIDPLAY_GetCurFileFps(&fps);
        MMPS_DSC_SetTranscodeRate(fps * 10, fpsx10, bitRate);
    }

    {
        MMP_USHORT fileW, fileH;
        fileW = MMPS_VIDPLAY_Get3gpConTnerVidInf()->width;
        fileH = MMPS_VIDPLAY_Get3gpConTnerVidInf()->height;
        err = MMPS_DSC_ConfigVideo2Mjpeg(fileW, fileH);
        MMPF_FrameRing_SetFrc(pVideoRing, fps * 1000, fpsx10 * 100);
    }

    if(!bPlay)
        return AHC_TRUE;

    if (err == MMP_ERR_NONE) {
        err = MMPS_VIDPLAY_Play((void *)VideoPlayStopCb, (void *)VidCnxt);
    }

    if (err != MMP_ERR_NONE) {
        printc("Unable to play the file (%X).\r\n", err);

        AIHC_CloseTranscode();
        return AHC_FALSE;
    }

    /// Get the file duration for SDP
    {
        ncam_val_t value = {VALUE_TYPE_INT, NULL};
        MMPS_VIDPLAY_GetCurFileDuration((MMP_ULONG*)&value.v.i32);
        if (!ncam_set_setting(NCS_FILE_DURATION, &value)) {
            printc(FG_RED("[ERR] set file duration %d\r\n"), value.v.i32);
            return AHC_FALSE;
        }
    }

    //reset the player into regular playing mode
    MMPS_VIDPLAY_SetDramMallocAddr(NULL);
    return err;
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_ApplyVideoConfig
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_ApplyVideoConfig(UINT16 streamID, UINT16 camID)
{
    #if (SUPPORT_MJPEG_WIFI_STREAM)
    MMP_MJPEG_ENC_INFO  StillCapture;
    MMP_ULONG           ulFpsX10;
    MMP_MJPEG_RATE_CTL  *pRC = NULL;
    MMP_ULONG           ulBitRate;
    #endif
    MMP_ULONG           val;
    AHC_MODE_ID         ahcMode;
    MMP_USHORT          usMJPEGWiFiMode;

    if (streamID != 1) {
        return AHC_FALSE;
    }

    AHC_VIDEO_GetMovieCfg(streamID, AHC_VIDEO_CODEC_TYPE, &val);

    printc("Stream[%d] Cam[%d] vFmt[%d] \r\n",streamID, camID, val);

    ahcMode = AHC_GetAhcSysMode();

    if( ahcMode == AHC_MODE_CAPTURE_PREVIEW ||
        ahcMode == AHC_MODE_STILL_CAPTURE ||
        ahcMode == AHC_MODE_RAW_CAPTURE ){
        usMJPEGWiFiMode = MMP_STREAM_UI_MODE_WIFI_DSC;
    }
    else{
        usMJPEGWiFiMode = MMP_STREAM_UI_MODE_WIFI_VR;
    }

    if (MMPS_3GPRECD_VIDEO_FORMAT_YUV422 == val)
    {
    #if (SUPPORT_MJPEG_WIFI_STREAM)
        /* During AHC_STREAM_MJPEG, switch flow: */
        /* Cam[0] vFmt[2] ==> switch ==> Cam[0] vFmt[3] ==> Cam[1] vFmt[2] */
        if (AIHC_Restore2ndVideo()) {
            MMPS_MJPEG_CloseStream(&m_sMjpegHdl);
        }
        else
    #endif
            return AHC_FALSE;
    }
    else if (MMPS_3GPRECD_VIDEO_FORMAT_MJPEG == val)
    {
    #if (SUPPORT_MJPEG_WIFI_STREAM)
        AHC_STREAMING_MODE ahcStreamingMode;
        UINT32 ulValue;

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, &ulValue);
        ahcStreamingMode = ulValue;

        if (AHC_STREAMING_TRANSCODE == ahcStreamingMode) {
            return AIHC_ApplyVideoTranscoding(streamID, AHC_TRUE);
        }

        StillCapture.bTargetCtl     = MMP_FALSE;
        StillCapture.bLimitCtl      = MMP_FALSE;
        StillCapture.bTargetSize    = 200;
        StillCapture.bLimitSize     = 220;
        StillCapture.bMaxTrialCnt   = 1;
        StillCapture.Quality        = MMP_JPGENC_RC_QUALITY_SEL_HIGH;

        if (AHC_FALSE == AHC_GetMJpegStreamResolution(streamID, &StillCapture.usEncWidth, &StillCapture.usEncHeight)) {
            return AHC_FALSE;
        }

        AHC_VIDEO_GetMovieCfg(streamID, AHC_VIDEO_BITRATE, &ulBitRate);
        AHC_VIDEO_GetMovieCfg(streamID, AHC_FRAME_RATEx10, &ulFpsX10);

        StillCapture.bTargetCtl = MMP_TRUE;
        StillCapture.bTargetSize    = ((ulBitRate * 10 / ulFpsX10) >> (3 + 10)) + 1;

        printc("Stream[%d] TargetSize %d KB\r\n",streamID, StillCapture.bTargetSize);

        if (camID == AHC_STREAM_FRONT) {
            MMPS_MJPEG_OpenStream(PRM_SENSOR, MMP_MJPEG_STREAM_FCAM_VIDEO, usMJPEGWiFiMode, &m_sMjpegHdl);
        }
        else if (camID == AHC_STREAM_REAR_VIF) {
            MMPS_MJPEG_OpenStream(SCD_SENSOR, MMP_MJPEG_STREAM_RCAM_VIDEO, usMJPEGWiFiMode, &m_sMjpegHdl);
        }
        else if (camID == AHC_STREAM_REAR_USBH) {
            MMPS_MJPEG_OpenStream(USBH_SENSOR, MMP_MJPEG_STREAM_RCAM_VIDEO, usMJPEGWiFiMode, &m_sMjpegHdl);
        }

        if (NULL != m_sMjpegHdl) {

            UINT32 sensorFPS, outFPS;

            sensorFPS = 30;//AHC_SNR_GetCurSensorFPS(PRM_SENSOR);

            if (0 == sensorFPS) {
                sensorFPS = 30;
            }

            AHC_VIDEO_GetMovieCfg(streamID, AHC_FRAME_RATEx10, &outFPS);

            if (outFPS > 0) {
                if (0 != ns_set_frc(sensorFPS * 1000, outFPS * 100, "VIDEO.0/EncMJPEG")) {
                    return AHC_FALSE;
                }
            }

            MMPS_MJPEG_STREAM_ConfigPipe(m_sMjpegHdl,
                                         StillCapture.usEncWidth, StillCapture.usEncHeight,
                                         &StillCapture.usEncWidth, &StillCapture.usEncHeight);

            if (camID == AHC_STREAM_FRONT) {
                MMPS_MJPEG_StartStream(usMJPEGWiFiMode, m_sMjpegHdl, &StillCapture, pRC);
            }
            else if (camID == AHC_STREAM_REAR_VIF ||
                     camID == AHC_STREAM_REAR_USBH) {

                if (camID == AHC_STREAM_REAR_USBH) {

                    #if (UVC_HOST_VIDEO_ENABLE)
                    /* Keep MJPEG Wifi Parameters */
                    gUsbh_UvcMjpegWifiCfg.dwTargetWidth     = StillCapture.usEncWidth;
                    gUsbh_UvcMjpegWifiCfg.dwTargetHeight    = StillCapture.usEncHeight;
                    gUsbh_UvcMjpegWifiCfg.bTargetCtl        = StillCapture.bTargetCtl;
                    gUsbh_UvcMjpegWifiCfg.bLimitCtl         = StillCapture.bLimitCtl;
                    gUsbh_UvcMjpegWifiCfg.dwTargetSz        = StillCapture.bTargetSize;
                    gUsbh_UvcMjpegWifiCfg.dwLimitSz         = StillCapture.bLimitSize;
                    gUsbh_UvcMjpegWifiCfg.wMaxTrialCnt      = StillCapture.bMaxTrialCnt;
                    gUsbh_UvcMjpegWifiCfg.mQlty             = StillCapture.Quality;
                    #endif

                    /* Don't need stop recording, don't need stop preview */
                    #if (UVC_HOST_VIDEO_ENABLE)
                    /* Change Mjpeg frame size request from stream */
                    AHC_HostUVC_SetMjpegFrmSz(StillCapture.bTargetSize);
                    #endif
                }

                MMPS_MJPEG_StartStream(usMJPEGWiFiMode, m_sMjpegHdl, &StillCapture, pRC);

                #if (UVC_HOST_VIDEO_ENABLE)
                if (camID == AHC_STREAM_REAR_USBH) {
                    /* Enable Streaming to inform USB host driver */
                    gUsbh_UvcMjpegWifiCfg.bEnWiFi = MMP_TRUE;
                }
                #endif
            }
        }
    #endif
    }
    else if (MMPS_3GPRECD_VIDEO_FORMAT_H264 == val)
    {
    #if (SUPPORT_H264_WIFI_STREAM)
        UINT32 op;
        AHC_MEDIA_USAGE usage;

        (void)AHC_VIDEO_GetMovieCfg(streamID, AHC_VIDEO_USAGE, &op);
        usage = (AHC_MEDIA_USAGE) op;

        if (usage == AHC_MEDIA_STREAMING) {

            if (AHC_FALSE == AIHC_StartH264WifiStream(camID)) {
                return AHC_FALSE;
            }
            MMPD_Streaming_Enable(VIDEO1_RING_STREAM, MMP_TRUE, MMP_TRUE);
        }
        else {
            #if (SUPPORT_H264_WIFI_STREAM)
            // Disable H264 stream
            MMPS_H264_STREAM_StopStream(&m_sH264WifiHdl[0]);
            #endif
            MMPD_Streaming_Enable(VIDEO1_RING_STREAM, MMP_FALSE, MMP_FALSE);
        }
    #endif
    }
    else if (MMPS_3GPRECD_VIDEO_FORMAT_OTHERS == val)
    {
        MMP_M_STATE     state;
        MMP_ULONG       KeyFrameNum;

        MMPS_VIDPLAY_GetState(&state);

        if (state != MMP_M_STATE_IDLE) {
            MMPS_VIDPLAY_Stop(&KeyFrameNum);
        }

        // Stop Streaming Timer after transcode to reset time stamp
        MMPD_Streaming_Enable(VIDEO1_RING_STREAM, MMP_FALSE, MMP_FALSE);
        AIHC_CloseTranscode();
    }
    else {
        printc("Unknown v format %d\r\n", val);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_ApplyAudioBypass
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_ApplyAudioBypass(UINT16 streamID)
{
    MMP_ULONG addr, size;

    MMPS_VIDPLAY_GetCurAudioBuffer(&addr, &size);

    MMPD_Streaming_Init(AUDIO_RING_STREAM);
    MMPD_Streaming_SetCompBuf(AUDIO_RING_STREAM, MMP_STREAM_UI_MODE_WIFI_VR, addr, size, MMP_STREAM_CODEC_AUDIO, NULL);
    MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : _Is_LiveAudio_Recording
//  Description :
//------------------------------------------------------------------------------
static __inline AHC_BOOL _Is_LiveAudio_Recording(void)
{
    MMP_USHORT  status;

    MMPD_AUDIO_GetLiveRecordStatus(&status);

    if (status == ENCODE_OP_START || status == ENCODE_OP_PREENCODE) {
        return AHC_TRUE;
    }
    return AHC_FALSE;
}

AHC_BOOL AIHC_ApplyAudioConfig(UINT16 streamID, AHC_STREAMING_MODE mode)
{
    UINT32 val;
    UINT32 mute;
    AHC_BOOL bValidStream;
    MMP_ULONG bitRate, samplingRate;
    MMPS_3GPRECD_AUDIO_FORMAT format;

    bValidStream = AHC_VIDEO_GetMovieCfg(streamID, AHC_AUD_MUTE_END, &mute);
    if (!bValidStream) {
        printc("invalid audio stream %d\r\n", streamID);
        return AHC_FALSE;
    }

    AHC_VIDEO_GetMovieCfg(streamID, AHC_AUD_CODEC_TYPE, &val);

    if (mute == MMP_TRUE) {
        //TODO do something to turn off the streaming audio track
        //reset the buffer to 0. Now they are used to know as ring buffer initialization indicator.
        //MMPD_Streaming_SetCompBuf(1, 0, 0);
        //probably need to return here.
    }

    if (mode == AHC_STREAM_ADPCM) {
        // This is PCM format, we are not support ADPCM
        VIDENC_FW_STATUS  status_vid;

        MMPS_3GPRECD_GetPrmEncoderStatus(&status_vid);

        if ((status_vid != VIDENC_FW_STATUS_START) && (status_vid != VIDENC_FW_STATUS_PREENCODE)) {
            MMP_ERR     err;
            MMP_UBYTE   ubWMR;

            AIHC_InitAudioExtDACIn();
            MMPS_3GPRECD_SetAudioRecMode(MMPS_3GPRECD_REC_AUDIO_DATA);

            AHC_Menu_SettingGetCB((char *)COMMON_KEY_WNR_EN, &ubWMR);

            if( ubWMR == WNR_ON ) {
                AHC_VIDEO_SetRecWithWNR(AHC_TRUE);
            }
            else {
                AHC_VIDEO_SetRecWithWNR(AHC_FALSE);
            }

            AHC_VIDEO_GetMovieCfg(streamID, AHC_AUD_CHANNEL_CONFIG, &val);
            MMPS_AUDIO_SetLineInChannel(val);

            AHC_Audio_ParseOptions(AHC_ADPCM_AUDIO_OPTION, &format, &samplingRate, &bitRate);

            err = MMPS_3GPRECD_SetAudioFormat(format, AHC_ADPCM_AUDIO_OPTION);
            if (MMP_ERR_NONE != err) {
                //this should be an assertion! the code should not go here. The current code could not handle this!
                printc("[ERR] Unable to set audio format\r\n");
            }

            //These 2 keeps the value of the setting for quicker reference only. The real settings
            // automatically applied in MMPS
            AHC_VIDEO_SetMovieCfg(streamID, AHC_AUD_BITRATE, bitRate);
            AHC_VIDEO_SetMovieCfg(streamID, AHC_AUD_SAMPLE_RATE, samplingRate);

            if(MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_ON)
                AHC_VIDEO_SetRecVolumeByMenuSetting(AHC_TRUE);
            else
                AHC_VIDEO_SetRecVolumeByMenuSetting(AHC_FALSE);

            if (1) {
                UINT32 addr, size;

                MMPD_Streaming_Init(AUDIO_RING_STREAM); //new a ring buffer in the name of JPEG functions
                MMPD_AUDIO_GetEncodeBuf(&addr, &size);

                AHC_VIDEO_SetRecVolumeToFW(AHC_TRUE);
                MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);

                MMPS_AUDIO_InitLiveRecord(MMP_AUDIO_PCM_ENCODE, 0, AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE_ADPCM), NULL);

                if(m_AhcStreamingMode != AHC_STREAM_PAUSE) {
                    MMPS_LiveAudio_StopRecord();
                    MMPS_LiveAudio_StartRecord();
                }
                return AHC_TRUE;
            }
            return AHC_FALSE;
        }

        if ((status_vid == VIDENC_FW_STATUS_START) || (status_vid == VIDENC_FW_STATUS_PREENCODE)) {

            MMPD_Streaming_Init(AUDIO_RING_STREAM); //new a ring buffer in the name of JPEG functions
            //Get sampling rate from master audio.
            MMPS_AUDIO_InitLiveRecord(MMP_AUDIO_PCM_ENCODE, 0, AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE_ADPCM), NULL);
            MMPS_LiveAudio_StopRecord();
            MMPS_LiveAudio_StartRecord();
            MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);
           // MMPD_AUDIO_DoEncodeOp(ENCODE_OP_START);
        }
        else {
            printc(ESC_ATR_COLOR_BRIGHTER FG_RED("not recording, this path is not implemented\r\n"));
            return AHC_FALSE;
        }
    }
    else {

        if (AHC_STREAM_AAC == mode) {
            if (!_Is_LiveAudio_Recording()) {
                MMP_AUDIO_ENCODE_FMT mmps_fmt;
                mmps_fmt = MMP_AUDIO_AAC_ENCODE;
                //review MMPS_AUDIO_LINEIN_DUAL & 48000

                MMPD_Streaming_Init(AUDIO_RING_STREAM); //new a ring buffer in the name of JPEG functions

                AHC_VIDEO_GetMovieCfg(streamID, AHC_AUD_CHANNEL_CONFIG, &val);
                if(m_AhcStreamingMode != AHC_STREAM_PAUSE) {
                    MMP_ERR err;
                    //AHC_VIDEO_GetMovieCfg(streamID, AHC_AUD_SAMPLE_RATE, &samplingRate);
                    MMPS_AUDIO_InitLiveRecord(mmps_fmt, MMPS_AUDIO_AAC_RECORD_32K_128K, 32000, NULL);
                    (void)MMPS_LiveAudio_StopRecord();
                    err = MMPS_LiveAudio_StartRecord();
                    if (err != MMP_ERR_NONE) {
                        printc(FG_RED("Unable to start live audio. %X\r\n"), err);
                    }
                }
                MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);
            }

        }
        else if ((AHC_MOVIE_AUDIO_CODEC_G711 == val) || (MMPS_3GPRECD_AUDIO_FORMAT_PCM == val)) {
            //mixed use with MMPS_AUDIO since there is no MMPS_3GPRECD_AUDIO_FORMAT_G711 now.
            //Need to be revised later with RD team.
            //VIDENC_FW_STATUS  status_vid;
            //TODO here it assumes it is recording, otherwise there is an error about this

            //MMPS_3GPRECD_GetVidStatus(VIDENC_STREAM_PRM_RECD, &status_vid);
            //if ((status_vid != VIDENC_FW_STATUS_START) && (status_vid != VIDENC_FW_STATUS_PREENCODE)) {
            if (!_Is_LiveAudio_Recording()) {
                MMP_AUDIO_ENCODE_FMT mmps_fmt;
                if (AHC_MOVIE_AUDIO_CODEC_G711 == val) {
                    mmps_fmt = MMP_AUDIO_G711_ENCODE;
                }
                else {
                    mmps_fmt = MMP_AUDIO_PCM_ENCODE;
                }

                MMPD_Streaming_Init(AUDIO_RING_STREAM); //new a ring buffer in the name of JPEG functions

                AHC_VIDEO_GetMovieCfg(streamID, AHC_AUD_CHANNEL_CONFIG, &val);
                if(m_AhcStreamingMode != AHC_STREAM_PAUSE) {
                    MMP_ERR err;
                    AHC_VIDEO_GetMovieCfg(streamID, AHC_AUD_SAMPLE_RATE, &samplingRate);
                    MMPS_AUDIO_InitLiveRecord(mmps_fmt, 0, samplingRate, NULL);
                    (void)MMPS_LiveAudio_StopRecord();
                    err = MMPS_LiveAudio_StartRecord();
                    if (err != MMP_ERR_NONE) {
                        printc(FG_RED("Unable to start live audio. %X\r\n"), err);
                    }
                }
                MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);
            }
        }
        else {
            printc("Unsupported audio format %d\r\n", val);
        }
    }
    return AHC_TRUE;
}

//Centralize all state transition which would cause problems.
//The goal is to remove the constrain as much as possible.
//assume all streaming state could transit to AHC_STREAM_OFF
static AHC_BOOL AIHC_IsStateStreamable(AHC_STREAMING_MODE streamingMode)
{
    AHC_MODE_ID mode = AHC_GetAhcSysMode();

    if ((streamingMode & AHC_STREAM_TRANSCODE) || (m_AhcStreamingMode & AHC_STREAM_TRANSCODE)) {
        return AHC_TRUE;
    }

    if (AHC_MODE_VIDEO_RECORD  != mode &&
        AHC_MODE_RECORD_PRERECD  != mode &&
        AHC_MODE_RECORD_PREVIEW  != mode &&
        AHC_MODE_CAPTURE_PREVIEW != mode &&
        AHC_MODE_STILL_CAPTURE   != mode) {
        return AHC_FALSE;
    }

    //validate the setting mode
    if (((m_AhcStreamingMode & AHC_STREAM_V_MASK) <= AHC_STREAM_V_MAX) &&
        ((m_AhcStreamingMode & AHC_STREAM_A_MASK) <= AHC_STREAM_A_MAX))
        return AHC_TRUE;

    return AHC_FALSE;
}

AHC_BOOL AHC_IsRecorderControllable(AHC_MODE_ID ahcMode)
{
    if (AHC_STREAM_OFF != m_AhcStreamingMode) {
    //    return AHC_FALSE;
    }
    if (AHC_STREAM_H264 == m_AhcStreamingMode) {
        //return AHC_FALSE;
    }
    if ((ahcMode == AHC_MODE_VIDEO_RECORD)       ||
        (ahcMode == AHC_MODE_RECORD_PRERECD)     ||
        (ahcMode == AHC_MODE_RECORD_PREVIEW))
    {
        return AHC_TRUE;
    }
    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_Video_MapResToIdx
//  Description :
//------------------------------------------------------------------------------
/** @brief Map 2 dimensions resolution to UVC or resolution index
 *
 *  @note The crop only deal with right and bottom
 *  @param[in] w Width
 *  @param[in] h Height
 *  @param[out] ResIdx The index of the resolution. It might be UVC index or CAR DV index
 *  @param[out] cropBottom Crop
 *  @param[out] cropRight The index of the resolution. It might be UVC index or CAR DV index
 */
AHC_BOOL AIHC_Video_MapResToIdx(UINT16 w, UINT16 h, UINT16 *ResIdx, UINT16 *cropBottom, UINT16 *cropRight)
{
    MMP_USHORT                  VideoRes;

    if((1920 == w) && ((1088 == h) || (1080 == h))){
        VideoRes = VIDRECD_RESOL_1920x1088;
    }
    #ifdef VIDRECD_RESOL_1600x900
    else if((1600 == w) && (912 == h)){
        VideoRes = VIDRECD_RESOL_1600x900;
    }
    #endif
    #ifdef VIDRECD_RESOL_1280x960
    else if((1280 == w) && (960 == h)){
        VideoRes = VIDRECD_RESOL_1280x960;
    }
    #endif
    else if((1280 == w) && (720 == h)){
        VideoRes = VIDRECD_RESOL_1280x720;
    }
    else if((640 == w) && (480 == h)){
        VideoRes = VIDRECD_RESOL_640x480;
    }
    else if((640 == w) && ((368 == h) || (360 == h))){
        VideoRes = VIDRECD_RESOL_640x368;
    }
    else if ((960 == w) && (720 == h)) {
        VideoRes = VIDRECD_RESOL_960x720;
    }
    else if((2304 == w) && (1296 == h)){
        VideoRes = VIDRECD_RESOL_2304x1296;
    }
    else if ((736 == w) && (736 == h)) {
        VideoRes = VIDRECD_RESOL_1472x736;
    }
    else if ((1472 == w) && (736 == h)) {
        VideoRes = VIDRECD_RESOL_1472x736;
    }
    else if ((1280 == w) && (640 == h)) {
        VideoRes = VIDRECD_RESOL_1472x736;
    }
    else{
        printc(FG_RED("--E-- Video resolution error. %dx%d\r\n"), w, h);
        return AHC_FALSE;
    }

    *ResIdx = VideoRes;

    *cropBottom = 0;
    *cropRight = 0;

    if (*ResIdx == VIDRECD_RESOL_1920x1088 ||
        *ResIdx == VIDRECD_RESOL_640x368) {
        *cropBottom = 8;
    }
#ifdef VIDRECD_RESOL_1600x900
    else if (*ResIdx == VIDRECD_RESOL_1600x900) {
        *cropBottom = 12;
    }
#endif

    return AHC_TRUE;
}

#if (SUPPORT_H264_WIFI_STREAM)
//------------------------------------------------------------------------------
//  Function    : AIHC_GetNetH264Resolution
//  Description :
//------------------------------------------------------------------------------
/** @brief Map 2 dimensions resolution to UVC or resolution index
 *
 *  @note The crop only deal with right and bottom
 *  @param[out] ResIdx The index of the resolution. It might be UVC index or CAR DV index
 *  @param[out] cropBottom Crop
 *  @param[out] cropRight The index of the resolution. It might be UVC index or CAR DV index
 */
AHC_BOOL AIHC_GetNetH264Resolution(UINT16 *mmpResIdx, UINT16 *cropBottom, UINT16 *cropRight)
{
    int conf_w, conf_h;
    UINT16 w, h;

    if (ncfg_get_h264_res(&conf_w, &conf_h) < 0) {
        printc("Unable to get H.264 resolution from conf\r\n");
        return AHC_FALSE;
    }

    w = (UINT16)(ALIGN16(conf_w));
    h = (UINT16)(ALIGN16(conf_h));

    if (AHC_TRUE != AIHC_Video_MapResToIdx(w, h, mmpResIdx, cropRight, cropBottom)) {
        printc("Unable to map H.264 image size %dx%d\r\n", w, h);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_CalH264EncResolution
//  Description :
//------------------------------------------------------------------------------
/** calculate H.264 resolution used in Encoder
 *
 * @param[in,out] encW Input is intended width. Output is width used in encoder.
 * @param[in,out] encH Input is intended height. Output is height used in encoder. e.g. 360 would be 368.
 * @param[out] cropBottom Cropping in pixels
 * @param[out] cropRight Cropping in pixels
 * @param[out] mmpResIdx The resolution index used in MMP library
 * @return AHC_TRUE for success. AHC_FALSE for false
 */
AHC_BOOL AIHC_CalH264EncResolution(UINT16 *encW, UINT16 *encH, UINT16 *cropBottom, UINT16 *cropRight, UINT16 *mmpResIdx)
{
    *encW = (UINT16)(ALIGN16(*encW));
    *encH = (UINT16)(ALIGN16(*encH));

    if (AHC_TRUE != AIHC_Video_MapResToIdx(*encW, *encH, mmpResIdx, cropRight, cropBottom)) {
        printc("Unable to map H.264 image size %dx%d\r\n", *encW, *encH);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_SetH264WifiAttributes
//  Description :
//------------------------------------------------------------------------------
static void AIHC_SetH264WifiAttributes(void* pvWifiHandle)
{
    MMP_H264_STREAM_OBJ     *pstStream  = (MMP_H264_STREAM_OBJ*)pvWifiHandle;
    MMPS_3GPRECD_FRAMERATE  stSnrFps    = {1001, 30000};
    MMPS_3GPRECD_FRAMERATE  stMgrFps    = {1001, 30000};
    UINT32                  u32Param    = 0;
    MMP_ULONG               ulBitrate   = 1000000;
    MMP_USHORT              usEncWidth  = 0, usEncHeight = 0;
    MMP_ERR                 eRetErr     = MMP_ERR_NONE;

    MMPF_VIDENC_SetH264ForceICount(0);

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_RESOLUTION, &u32Param);

    switch (u32Param) {
    case VIDRECD_RESOL_640x480:
        usEncWidth  = 640;
        usEncHeight = 480;
        break;
    case VIDRECD_RESOL_1280x720:
        usEncWidth  = 1280;
        usEncHeight = 720;
        break;
    case VIDRECD_RESOL_1920x1088:
        usEncWidth  = 1920;
        usEncHeight = 1080;
        break;
    default:
        AHC_DBG_ERR(1, "UnSupport WIFI H264 Resolution [%d]\r\n", u32Param);
        MMPF_VIDENC_SetH264ForceICount(0);
        return;
        break;
    }

    eRetErr = MMPS_H264_STREAM_ConfigPipe(pstStream, usEncWidth, usEncHeight);
    if (MMP_ERR_NONE != eRetErr) {
        AHC_DBG_ERR(1, "H264_STREAM_ConfigPipe Fail\r\n");
        MMPF_VIDENC_SetH264ForceICount(0);
        return;
    }

    // Must after MMPS_H264_STREAM_ConfigPipe
    MMPS_H264_STREAM_CustomedResol(pstStream->ubStrmSel, MMP_SCAL_FITMODE_OPTIMAL, usEncWidth, usEncHeight);

    /* Set Video Stream Attribute */
    pstStream->stEncCfg.VisualProfile = H264ENC_MAIN_PROFILE;
    MMPS_H264_STREAM_SetProfile(pstStream->ubStrmSel, pstStream->stEncCfg.VisualProfile);

    stSnrFps.ulTimeIncre = 1001;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_FRAME_RATEx10, &u32Param);
    if (u32Param)
        stSnrFps.ulTimeResol = u32Param * 100;
    else
        stSnrFps.ulTimeResol = 30000; // TBD

    stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
    stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;

    pstStream->stEncCfg.SnrFrameRate.ulTimeIncre = stSnrFps.ulTimeIncre;
    pstStream->stEncCfg.SnrFrameRate.ulTimeResol = stSnrFps.ulTimeResol;
    pstStream->stEncCfg.EncFrameRate.ulTimeIncre = stSnrFps.ulTimeIncre;
    pstStream->stEncCfg.EncFrameRate.ulTimeResol = stSnrFps.ulTimeResol;
    pstStream->stEncCfg.MgrFrameRate.ulTimeIncre = stMgrFps.ulTimeIncre;
    pstStream->stEncCfg.MgrFrameRate.ulTimeResol = stMgrFps.ulTimeResol;
    MMPS_H264_STREAM_SetFrameRatePara(pstStream->ubStrmSel,
                                      &(pstStream->stEncCfg.SnrFrameRate),
                                      &(pstStream->stEncCfg.EncFrameRate),
                                      &(pstStream->stEncCfg.MgrFrameRate));

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_BITRATE, &ulBitrate);
    pstStream->stEncCfg.ulBitrate = ulBitrate;
    MMPS_H264_STREAM_SetBitrate(pstStream->ubStrmSel, pstStream->stEncCfg.ulBitrate);

    pstStream->stEncCfg.usPFrameCount = 7;
    MMPS_H264_STREAM_SetPFrameCount(pstStream->ubStrmSel, pstStream->stEncCfg.usPFrameCount);

    pstStream->stEncCfg.usBFrameCount = 0;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StartH264WifiStream
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_StartH264WifiStream(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulWifiEncUseMode = VIDRECD_USEMODE_CB2AP;
    MMP_ULONG   ulCompBufAddr, ulCompBufSize;
    MMP_ERR     err = MMP_ERR_NONE;
    AHC_MODE_ID ahcMode;
    MMP_UBYTE   ubStreamSel = MMPS_H264_STRM_PRM;

    if (ubCamSel == AHC_STREAM_FRONT)
        ubStreamSel = MMPS_H264_STRM_PRM;
    else
        ubStreamSel = MMPS_H264_STRM_SCD;

    ahcMode = AHC_GetAhcSysMode();

    if (ahcMode == AHC_MODE_CAPTURE_PREVIEW ||
        ahcMode == AHC_MODE_STILL_CAPTURE ||
        ahcMode == AHC_MODE_RAW_CAPTURE) {
        MMPS_H264_STREAM_OpenStream(ubStreamSel, ubCamSel, MMP_H264_STREAM_USAGE_WIFI, &m_sH264WifiHdl[ubStreamSel], MMP_H264_STREAM_MODE_DSC);
    }
    else {
        MMPS_H264_STREAM_OpenStream(ubStreamSel, ubCamSel, MMP_H264_STREAM_USAGE_WIFI, &m_sH264WifiHdl[ubStreamSel], MMP_H264_STREAM_MODE_VR);
    }

    AIHC_SetH264WifiAttributes(m_sH264WifiHdl[ubStreamSel]);

    /* ubCamSel use to tell MMPS layer usStreamType, then, MMPS layer use usStreamType to identify front/rear cam */
    if (ubCamSel == AHC_STREAM_FRONT) {
        ((MMP_H264_STREAM_OBJ*)m_sH264WifiHdl[ubStreamSel])->usStreamType = VIDENC_STREAM_WIFI_PRM;
    }
    else if (ubCamSel == AHC_STREAM_REAR_VIF ||
             ubCamSel == AHC_STREAM_REAR_USBH) {
        ((MMP_H264_STREAM_OBJ*)m_sH264WifiHdl[ubStreamSel])->usStreamType = VIDENC_STREAM_WIFI_SCD;

        if (ubCamSel == AHC_STREAM_REAR_USBH) {
            if (CAM_CHECK_USB(USB_CAM_AIT) && MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_NV12_H264) {
                MMPF_USBH_UVC_STREAM_CFG *pUVCCfg = MMPF_USBH_GetUVCCFG();
                MMPS_H264_STREAM_CustomedResol(ubStreamSel, MMP_SCAL_FITMODE_OPTIMAL, pUVCCfg->mPrevw.usWidth, pUVCCfg->mPrevw.usHeight);
            }
        }
    }
    else {
        AHC_DBG_ERR(1, FG_RED("[ERR] Unknown ubSnrSel %d.")"\r\n", ubCamSel);
        return AHC_TRUE;
    }

    if (ubCamSel == PRM_SENSOR) {
        MMPS_3GPRECD_SetH264EncUseMode(VIDENC_STREAM_WIFI_PRM, ulWifiEncUseMode);
    }
    else if (ubCamSel == SCD_SENSOR ||
             ubCamSel == USBH_SENSOR) {
        MMPS_3GPRECD_SetH264EncUseMode(VIDENC_STREAM_WIFI_SCD, ulWifiEncUseMode);
    }

    err = MMPS_H264_STREAM_StartWifiStream(m_sH264WifiHdl[ubStreamSel]);

    if (err) {
        AHC_DBG_ERR(1, "Start Wifi Stream failed\r\n");
        return AHC_FALSE;
    }

    if (ubCamSel == PRM_SENSOR) {
        MMPS_3GPRECD_GetEncodeCompBuf(VIDENC_STREAM_WIFI_PRM, &ulCompBufAddr, &ulCompBufSize, &mCompressThreshold);
    }
    else if (ubCamSel == SCD_SENSOR ||
             ubCamSel == USBH_SENSOR) {
        MMPS_3GPRECD_GetEncodeCompBuf(VIDENC_STREAM_WIFI_SCD, &ulCompBufAddr, &ulCompBufSize, &mCompressThreshold);
    }

    AIHC_SetH264RingBuf(ulCompBufAddr, ulCompBufSize);

    AHC_DBG_MSG(1, "Wifi H264 Start...\r\n");

    return AHC_TRUE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_ChangeH264StreamRes
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_ChangeH264StreamRes(UINT16 VidResIdx)
{
    MMP_ERR err;
    MMP_H264_STREAM_OBJ *obj;

    LOCK_AHC_MODE();

    obj = m_sH264WifiHdl[0];

    // Now, H264 WIFI streaming is supported in record mode
    if (AIHC_IsStateStreamable(AHC_GetStreamingMode()) == AHC_FALSE) {
        printc("Incorrect AHC mode to start H.264 streaming\r\n");
        goto stream_fail;
    }

    MMPS_H264_STREAM_StopStream(&m_sH264WifiHdl[0]);

    // Wait extra 33 MS for DMA to V4L safety
    AHC_OS_SleepMs(33);

    // Starting the video stream
    err = MMPS_H264_STREAM_StartWifiStream(obj);
    if (err) {
        printc("Start H264 streaming err %X\r\n", err);
        goto stream_fail;
    }

    // The compress buffer has been changed in MMPS_3GPRECD_StartWifiStream
    {
        MMP_ULONG ulCompBufAddr, ulCompBufSize;

        MMPS_3GPRECD_GetEncodeCompBuf(VIDENC_STREAM_WIFI_PRM, &ulCompBufAddr, &ulCompBufSize, &mCompressThreshold);
        //printd(__prettyfunc__" F264 buf %X sz %X\r\n", ulCompBufAddr, ulCompBufSize);

        AIHC_SetH264RingBuf(ulCompBufAddr, ulCompBufSize);
        MMPD_Streaming_Enable(VIDEO1_RING_STREAM, MMP_TRUE, MMP_TRUE);
    }

    UNLOCK_AHC_MODE();
    return AHC_TRUE;

stream_fail:

    UNLOCK_AHC_MODE();
    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_CalThreshold0
//  Description :
//------------------------------------------------------------------------------
static MMP_ULONG AIHC_CalThreshold0(MMP_ULONG ulFrameSize)
{
    return mCompressThreshold;
}

//------------------------------------------------------------------------------
//  Function    : _AHC_Config1stAudio
//  Description :
//------------------------------------------------------------------------------
//It's bad that we have to config 1st audio here in case the 1st audio has never been started before.
//Typical case is to start streaming without preencode or recording.
static void _AHC_Config1stAudio(void)
{
    if (VR_AUDIO_TYPE == VR_AUDIO_TYPE_ADPCM) {
        AHC_VIDEO_ConfigAudio(AHC_AUDIO_STREAM_ID, AHC_MOVIE_AUDIO_CODEC_ADPCM, AHC_AUDIO_CHANNEL_MONO_R);
    }
    else if (VR_AUDIO_TYPE == VR_AUDIO_TYPE_AAC) {
        AHC_VIDEO_ConfigAudio(AHC_AUDIO_STREAM_ID, AHC_MOVIE_AUDIO_CODEC_AAC, AHC_AUDIO_CHANNEL_MONO_R);
    }
    else {
        // Error
    }
    AHC_VIDEO_SetMovieCfg(AHC_AUDIO_STREAM_ID, AHC_AUD_MUTE_END, AHC_TRUE);
}

//------------------------------------------------------------------------------
//  Function    : _AHC_Config2ndAudio
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL _AHC_Config2ndAudio(AHC_MOVIE_CONFIG_PARAM configParam, AHC_STREAMING_MODE streamingMode)
{
    if ((configParam <= AHC_MOVIE_AUDIO_CODEC_START) || (configParam >= AHC_MOVIE_AUDIO_CODEC_END)) {
        RTNA_DBG_Str(0, "C2AF0\r\n");
        return AHC_FALSE;
    }

    if (AHC_VIDEO_ConfigAudio(AHC_AUDIO_STREAM_2_ID, configParam, AHC_AUDIO_CHANNEL_MONO_R) == AHC_FALSE) {
        RTNA_DBG_Str(0, "C2AF1\r\n");
        return AHC_FALSE;
    }

    AHC_VIDEO_SetMovieCfg(AHC_AUDIO_STREAM_2_ID, AHC_AUD_MUTE_END, AHC_FALSE);

    /*if (IS_TRANSCODING(streamingMode)) {
        MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);
    }
    else*/ {
        UINT32 liveCodecType;
        //live streaming
        AHC_VIDEO_GetMovieCfg(AHC_AUDIO_STREAM_2_ID, AHC_AUD_CODEC_TYPE, &liveCodecType);

        if (AHC_FALSE == AIHC_ApplyAudioConfig(AHC_AUDIO_STREAM_2_ID, liveCodecType)) {
            RTNA_DBG_Str(0, "C2AF2\r\n");
            return AHC_FALSE;
        }
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_SetH264Buf
//  Description :
//------------------------------------------------------------------------------
void AIHC_SetH264RingBuf(UINT32 addr, UINT32 size)
{
    h264StreamStart = addr;
    h264StreamSize = size;

    MMPD_Streaming_Init(VIDEO1_RING_STREAM);
    MMPD_Streaming_SetCompBuf(VIDEO1_RING_STREAM, MMP_STREAM_UI_MODE_WIFI_VR, h264StreamStart, h264StreamSize, MMP_STREAM_H264, AIHC_CalThreshold0);
    MMPF_StreamRing_ConfigBuffer(VIDEO1_RING_STREAM, h264StreamStart, h264StreamSize, MMP_H264_ALIGNMENT, MMP_TRUE);
}

static AHC_BOOL AIHC_ConfigStreamingH264(AHC_BOOL on, AHC_BOOL isTranscoding, AHC_BOOL isResume)
{
#if (SUPPORT_H264_WIFI_STREAM)
    AHC_VIDEO_2ND_CONFIG cfg;
    int iVal = 0, result;
    AHC_STREAM_ID ahcSrcStreamId;

    ahcSrcStreamId = (AHC_STREAM_ID)ncam_get_cam_src((unsigned int)AHC_STREAM_H264);

    if (AHC_TRUE != AIHC_GetNetH264Resolution(&cfg.param.h264.mmpRes, &cfg.param.h264.cropR, &cfg.param.h264.cropB)) {
        printc("Unable to map H.264 image size MMP IDX %d\r\n", cfg.param.h264.mmpRes);
        goto config_h264_err;
    }

    if (on) {
        if (isTranscoding) {
            MMP_ULONG fps;
            AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_STREAMING_TRANSCODE);
            AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_USAGE, AHC_MEDIA_STREAMING);

            MMPS_VIDPLAY_GetCurFileFps(&fps);
            cfg.FPS = fps; //it is only known after parsing
        }
        else {
            AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_STREAMING_ON);
            AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_USAGE, AHC_MEDIA_STREAMING);

            //get it from current sensor setting
            cfg.FPS = 30;//AHC_SNR_GetCurSensorFPS(PRM_SENSOR);
            if (0 == cfg.FPS) {
                cfg.FPS = 30;
            }
        }
    }
    else {
        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_USAGE, AHC_MEDIA_DISABLE);
    }

    cfg.vFormat = AHC_MOVIE_VIDEO_CODEC_H264;

    cfg.param.h264.Bitrate = ncfg_get_h264_bitrate();
    if (isResume && ns_has_stream_control()) {
        MMP_H264_STREAM_OBJ      *pWifi = (MMP_H264_STREAM_OBJ*)m_sH264WifiHdl[0];
        cfg.param.h264.Bitrate = pWifi->stEncCfg.ulBitrate;
    }

    result = ncfg_get("Camera.Preview.H264.fps", &iVal);
    if (result >= 0 && iVal != 0) {
        cfg.FpsOutx1000 = iVal * 1000;
    } else {
        cfg.FpsOutx1000 = 30 * 1000; //default 30FPS if missing Camera.Preview.H264.fps or set to invalid number
    }

    if (AHC_TRUE != AHC_Config2ndVideo(&cfg)) {
        printd("unable to config 2nd video\r\n");
        goto config_h264_err;
    }
    return AIHC_ApplyVideoConfig(1,ahcSrcStreamId);

    return AHC_TRUE;
config_h264_err:
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_STREAMING_OFF);
    return AHC_FALSE;
#else
    printc(FG_RED("[ERR] Unable to support H.264 streaming.\r\n"));
    return AHC_FALSE;
#endif
}

static AHC_BOOL AIHC_ConfigStreamingMjpeg(AHC_BOOL on, AHC_BOOL isTranscoding)
{
    AHC_VIDEO_2ND_CONFIG cfg;

    //support one streaming only
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_STREAMING, AHC_STREAMING_OFF);

    if (on) {
        int iVal;
        AHC_VIDRECD_RESOL AhcRes;
        int w, h;

        if (isTranscoding) {
            MMP_ULONG fps;
            AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_STREAMING_TRANSCODE);
            MMPS_VIDPLAY_GetCurFileFps(&fps);
            cfg.FPS = fps; //it is only known after parsing
        }
        else {
            AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_STREAMING_ON);
            //get it from current sensor setting
            cfg.FPS = 30;//AHC_SNR_GetCurSensorFPS(PRM_SENSOR);
            if (0 == cfg.FPS) {
                cfg.FPS = 30;
            }
        }
        cfg.vFormat = AHC_MOVIE_VIDEO_CODEC_MJPEG;
        ncfg_get("Camera.Preview.MJPEG.bitrate", &cfg.param.mj.Bitrate);
        ncfg_get("Camera.Preview.MJPEG.fps", &iVal);
        if (iVal != 0) {
            cfg.FpsOutx1000 = iVal * 1000;
        }

        iVal = ncfg_get_v_res("Camera.Preview.MJPEG", &w, &h);
        if (iVal != 0) {
            printc("Unable to get MJPEG resolution from conf\r\n");
            AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_STREAMING_OFF);
            return AHC_FALSE;
        }

        if (AHC_TRUE == AIHC_VIDEO_MapFromRawVRes((UINT16) w, (UINT16) h, &AhcRes)) {
            cfg.param.mj.ahcRes = AhcRes;
        } else {
            cfg.param.mj.ahcRes = AhcRes; //A resolution by UART for testing
        }

        AHC_Config2ndVideo(&cfg);
        AIHC_ApplyVideoConfig(1,ncam_get_cam_src((unsigned int)AHC_STREAM_MJPEG));
    } else {
        cfg.FPS = 30;
        cfg.vFormat = AHC_MOVIE_VIDEO_CODEC_YUV422;
        cfg.param.mj.Bitrate = 0;//don't care
        cfg.param.mj.ahcRes = AHC_VIDRECD_RESOL_AUTO;//by LCD
        //when doing transcoding, change to no streaming, not back to YUV preview.
        if (isTranscoding) {
            cfg.vFormat = AHC_MOVIE_VIDEO_CODEC_NONE;
        }
        AHC_Config2ndVideo(&cfg);
        AIHC_ApplyVideoConfig(1,0);

        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_STREAMING, AHC_STREAMING_OFF);
        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_STREAMING_OFF);
    }
    return AHC_TRUE;
}

static AHC_BOOL AIHC_StopExistingStreaming(void)
{
    AHC_STREAMING_MODE vMode;

    vMode = m_AhcStreamingMode & AHC_STREAM_V_MASK;

    if (vMode == AHC_STREAM_MJPEG) {
        AIHC_ConfigStreamingMjpeg(AHC_FALSE, IS_TRANSCODING(m_AhcStreamingMode));
    }
    else if (vMode == AHC_STREAM_H264) {
        AIHC_ConfigStreamingH264(AHC_FALSE, IS_TRANSCODING(m_AhcStreamingMode), AHC_FALSE);
    }
    return AHC_TRUE;
}

/** Set the streaming mode
 *
 * The streaming logic is put here.
 * @param streamingMode The streaming mode
 * @param bWait. In some case like as MoveFrame call Push to get a V4L buffer to move frame.
 *               It should not wait, because the MoveFrame is critical in timing of audio and
 *               video, and the _AHC_SetStreamingMode may block by AHC_SetMode a while.
 *               In this case, the bWait must be FALSE, and causes MoveFrame to drop a frame.
 *               It will keep Ring healthy working.
 * @return AHC_FALSE fail to config streaming mode.
 */
AHC_BOOL _AHC_SetStreamingMode(AHC_STREAMING_MODE streamingMode, AHC_BOOL bWait, char * str, int line)
{
    MMP_BOOL bKeepTimerAlive = 0;
    AHC_BOOL audioEn = AHC_FALSE; //get the audio config from MMI later
    //currently because audio streaming is not supported, so it is always off.
    //MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_ON
    AHC_STREAMING_MODE vMode, aMode,vMode2;
    MMP_BOOL    dscv, vidv;

    if (!bWait) {
        UINT16  cnt;
        AHC_OS_QuerySem(m_AhcModeSemID, &cnt);
        if (cnt == 0) return AHC_FALSE;
        if (LOCK_AHC_MODE_NOWAIT() != 0) {
            RTNA_DBG_Str(0, "SMF0\r\n");
            return AHC_FALSE;
        }
    } else {
        LOCK_AHC_MODE();
    }
    /*
     * NOTE:
     * the expression ((streamingMode | m_AhcStreamingMode) & AHC_STREAM_TRANSCODE == 0)
     * it seems to do like as (streamingMode | m_AhcStreamingMode) & (AHC_STREAM_TRANSCODE == 0)
     * not as our thought ((streamingMode | m_AhcStreamingMode) & AHC_STREAM_TRANSCODE) == 0
     */
    MMPS_DSC_GetPreviewPipeStatus(gsAhcPrmSensor, &dscv);
    MMPS_3GPRECD_GetPreviewPipeStatus(gsAhcPrmSensor, &vidv);
    //printc("@@AHC_SetStreamingMode: mode %x -> %x AHCMODE %x %d/%d @ %s line %d\r\n",
    //        m_AhcStreamingMode, streamingMode, AHC_GetAhcSysMode(), dscv, vidv, str, line);
    if (((m_AhcStreamingMode & AHC_STREAM_TRANSCODE) && streamingMode == AHC_STREAM_PAUSE) ||
        ((m_AhcStreamingResume & AHC_STREAM_TRANSCODE) && streamingMode == AHC_STREAM_RESUME)) {

        if (streamingMode == AHC_STREAM_PAUSE) {
            printc(BG_PURPLE("TXC_PAUSE")"\r\n");
            MMPS_VIDPLAY_Pause();
            m_AhcStreamingResume = m_AhcStreamingMode;
            m_AhcStreamingMode   = streamingMode;
        }
        else {
            MMPS_VIDPLAY_Resume();
            printc(BG_BLUE("TXC_RESUME")"\r\n");
            m_AhcStreamingMode   = m_AhcStreamingResume;
            m_AhcStreamingResume = AHC_STREAM_NONE;
        }
        UNLOCK_AHC_MODE();
        return AHC_TRUE;
    }
    if (!(streamingMode & AHC_STREAM_TRANSCODE) && !(m_AhcStreamingResume & AHC_STREAM_TRANSCODE)) {

        if (AHC_GetAhcSysMode() == AHC_MODE_IDLE && (((streamingMode | m_AhcStreamingMode) & AHC_STREAM_TRANSCODE) == 0)) {
            printc(FG_YELLOW("VIDEO PREVIEW WAS OFF!!\n"));
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
        }
    }

    if (m_AhcStreamingMode == streamingMode) { // no change, just return
        UNLOCK_AHC_MODE();
        return AHC_TRUE;
    }
    if ((streamingMode == AHC_STREAM_PAUSE  && m_AhcStreamingMode == AHC_STREAM_NONE) ||
        (streamingMode == AHC_STREAM_RESUME && m_AhcStreamingMode != AHC_STREAM_PAUSE)) {
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }
    if (streamingMode == AHC_STREAM_RESUME) {
        streamingMode = m_AhcStreamingResume;
        printc(BG_BLUE("RESUME")"\r\n");
        aMode = AHC_STREAM_RESUME;
    }
    else if (streamingMode == AHC_STREAM_PAUSE) {
        if ((m_AhcStreamingMode & (AHC_STREAM_V_MASK | AHC_STREAM_A_MASK)) == AHC_STREAM_NONE) {
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
        }
        m_AhcStreamingResume = m_AhcStreamingMode;
        aMode = AHC_STREAM_PAUSE;
        printc(BG_YELLOW("PAUSE")"\r\n");
    }
    else {
        aMode = streamingMode & AHC_STREAM_A_MASK;
    }

    vMode = streamingMode & AHC_STREAM_V_MASK;
    vMode2 = streamingMode & AHC_STREAM_V_MASK2;// add for rear MJPEG

    /*
    *For streaming without audio,blow conditions will cause the player stuck,
    *keepping streaming timer alive maybe is a solution
    *1.streaming pause => resume
    *2.switch rear/front cam
    */
    if((streamingMode & AHC_STREAM_EX_OP_MASK) == AHC_STREAM_KEEP_TIMER_ALIVE ||
        streamingMode == AHC_STREAM_PAUSE )
        bKeepTimerAlive = 1;

    if (AIHC_IsStateStreamable(streamingMode) == AHC_FALSE) {
        #if 0 // No need ?
        if (AHC_GetAhcSysMode() == AHC_MODE_IDLE && vMode != AHC_STREAM_NONE && vMode2 != AHC_STREAM_NONE) {
            /* In some case, there is no SD and LCD. It won't be previewing
             * or other viewing state and is in idle mode instead.
             * */
            UNLOCK_AHC_MODE();

            if (AHC_SetMode(AHC_MODE_RECORD_PREVIEW) == AHC_FALSE) {
                printc("Unable to set RECORD_PREVIEW mode\r\n");
                return AHC_FALSE;
            }
            LOCK_AHC_MODE();
        }
        else {
        #endif
            printc("Unable to set streaming mode %d due to current AHC_Mode and streaming Mode\r\n",
                    streamingMode);
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
       // }
    }

    if ((AHC_STREAM_NONE == vMode)&& (AHC_STREAM_NONE == vMode2)) {
        // Turn off H264 Streaming
        MMPS_3GPRECD_RegisterCallback (VIDMGR_EVENT_STREAMCB,     (void*)NULL);
    }
    else {

        if (vMode == AHC_STREAM_H264) {
            MMPS_3GPRECD_RegisterCallback (VIDMGR_EVENT_STREAMCB,     (void*)VideoRecordStreamCallback);
        }
    }

    if ((AHC_STREAM_NONE == vMode) && (AHC_STREAM_NONE == vMode2)&&(AHC_STREAM_NONE == aMode)){
        MMPF_FrameRing_SetMoveCallback(NULL);
    }
    else {
        MMPF_FrameRing_SetMoveCallback(VideoRecordStreamCallback);
    }

    if(bKeepTimerAlive)
        MMPF_StreamingTimer_KeepTimerAlive(1);

    if (aMode != AHC_STREAM_NONE && aMode != AHC_STREAM_PAUSE && aMode != AHC_STREAM_RESUME) {
        audioEn = AHC_TRUE;

        if (AHC_STREAM_AAC == aMode || AHC_STREAM_ADPCM == aMode) {
            // AHC_VIDEO_ConfigAudio(AHC_AUDIO_STREAM_ID, AHC_MOVIE_AUDIO_CODEC_AAC, AHC_AUDIO_CHANNEL_MONO_R);
            if (streamingMode & AHC_STREAM_TRANSCODE) {
                ///@warning assume it's video transcoding and audio bypass
                //TODO check if the file contains AAC, since here it should be parsed
                if (AHC_TRUE != AIHC_ApplyAudioBypass(AHC_AUDIO_STREAM_ID)) {

                }
            }
            else {
                if (AHC_TRUE != AIHC_ApplyAudioConfig(AHC_AUDIO_STREAM_ID, aMode)) {
                    printc("error applying audio track %d\r\n", AHC_AUDIO_STREAM_ID);
                    goto restore_video;
                }
            }
            // for live streaming (liveRTSP) to set PCM or ACC.
            // for file streaming (txRTSP) it should set it
            //   when liveRTSP_describe call ncam_parse_file, but set again in here.
            if (AHC_STREAM_ADPCM == aMode) { /* for StreamPCM */
                printc(FG_GREEN("SET audio stream IS PCM\n"));
            }
            else {    /* for StreamAAC */
                printc(FG_GREEN("SET audio stream IS AAC\n"));
            }
        }
        else if (AHC_STREAM_G711 == aMode && (VR_AUDIO_TYPE == VR_AUDIO_TYPE_AAC)) {
            _AHC_Config1stAudio();
            if (AHC_FALSE == _AHC_Config2ndAudio(AHC_MOVIE_AUDIO_CODEC_G711, streamingMode)) {
                RTNA_DBG_Str(0, "SMF2\r\n");

                goto restore_video;
            }
        }
        else if (AHC_STREAM_PCM == aMode) {
            _AHC_Config1stAudio();
            if (AHC_FALSE == _AHC_Config2ndAudio(AHC_MOVIE_AUDIO_CODEC_PCM, streamingMode)) {
                RTNA_DBG_Str(0, "SMF3\r\n");

                goto restore_video;
            }
        }
        else {
            printc("Unsupported audio format %X\r\n", aMode);
            goto restore_video;
        }
    }
    else if (aMode == AHC_STREAM_NONE) {
        /* NOTE:
         * 1. not to stop audio for timer when in pause state
         *    because if stop timer the timestamp will restart at 0
         *    it will cause player waiting until time of streaming to
         *    paused time.
         * 2. If pause both of video and audio, it will cause player to stop or restart RTSP.
         * 3. Before stopping audio engine, it will check Audio ring and video recording status
         *    - MMPF_IsReadyToOp()
         *    Consequently, it needs stop Audio streaming first,
         *    then stop Audio Engine - MMPD_AUDIO_DoEncodeOp(ENCODE_OP_STOP).
         */
        MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_FALSE, MMP_FALSE);
        // TODO: should add PAUSE for ONLY VIDEO or AUDIO or BOTH

        #if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)

        #else
        // Not to STOP AUDIO in Video Recording.
        if (MMP_ERR_NONE != MMPS_LiveAudio_StopRecord()) {
            printc(FG_RED("[ERR] Unable to stop audio encode\r\n"));
        }
        #endif
    }

    AHC_VIDEO_SetMovieCfg(AHC_AUDIO_STREAM_ID, AHC_AUD_STREAMING, audioEn);

    /* Video Streaming */
    if (AHC_STREAM_MJPEG == vMode) {
        (void)AIHC_StopExistingStreaming();
        if (AHC_TRUE != AIHC_ConfigStreamingMjpeg(AHC_TRUE, IS_TRANSCODING(streamingMode))) {
            if(bKeepTimerAlive)
                MMPF_StreamingTimer_KeepTimerAlive(0);
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
        }
    }
    else if (AHC_STREAM_H264 == vMode) {
        (void)AIHC_StopExistingStreaming();
        //This path. WIFI stream could be controlled separately
        if (AHC_TRUE != AIHC_ConfigStreamingH264(AHC_TRUE, IS_TRANSCODING(streamingMode), aMode & AHC_STREAM_RESUME)) {
            if(bKeepTimerAlive)
                MMPF_StreamingTimer_KeepTimerAlive(0);
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
        }
    } else if (AHC_STREAM_NONE == vMode) {
        (void)AIHC_StopExistingStreaming();
        // Need to add restore video here ?


    }
    else {
        if(bKeepTimerAlive)
            MMPF_StreamingTimer_KeepTimerAlive(0);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    m_AhcStreamingMode = streamingMode;
    if(bKeepTimerAlive)
        MMPF_StreamingTimer_KeepTimerAlive(0);
    UNLOCK_AHC_MODE();
    return AHC_TRUE;

restore_video:
    if (AHC_STREAM_MJPEG == vMode) {
        #if (SUPPORT_MJPEG_WIFI_STREAM)
        if (AIHC_Restore2ndVideo()) {
            MMPS_MJPEG_CloseStream(&m_sMjpegHdl);
        }
        #endif
    }

    if(bKeepTimerAlive)
        MMPF_StreamingTimer_KeepTimerAlive(0);

    UNLOCK_AHC_MODE();


    return AHC_FALSE;
}

#if 0
void _____Streaming_Functions_____(){}
#endif

/*
 * For Streaming
 */
#include "ahc_message.h"
#include "ahc_general.h"
#include "keyparser.h"
int sps_pps_update = 0;
#define sps_pps_renew() (sps_pps_update != 0)
#define sps_pps_clean() sps_pps_update = 0

int wait_sps_pps_renew(int tc)
{
    while (!sps_pps_renew() && tc != 0) {
        tc--;
        AHC_OS_SleepMs(100);
    }
    if (tc)
        return 1;
    return 0;
}

int AHC_OpenVideoStream(void *handle)
{
    sps_pps_clean();
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, VIRTUAL_EVENT, EVENT_OPEN_H264_STREAM);
    /* wait sps/pps in 2 sec */
    return wait_sps_pps_renew(20);
}

int AHC_CloseVideoStream(void *handle)
{
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, VIRTUAL_EVENT, EVENT_CLOSE_H264_STREAM);
    return 0;
}

#if (WIFI_PORT == 1)
//a global transcoding mode. This is a temp variable which is a bad coding style.
//It will be removed later for better modulization.
int transcoding;

#define UNDEFINED_SEM_ID (0xFF)
#define MAX_TRANSCODING_SESSION (1)
static struct AHC_TRANSCODE_CONTEXT
{
    AHC_OS_SEMID sessSem; //used for block open right after close case
    AHC_OS_SEMID opSem;   //used for block close right after open case
                          //play and stop are not protected
    UINT32 semTimeOut;
} m_transcodeContext = {UNDEFINED_SEM_ID, UNDEFINED_SEM_ID, 5000};

INT32 AIHC_OpenTranscode(void)
{
#if (VIDEO_DEC_TO_MJPEG)
    if (m_transcodeContext.sessSem == UNDEFINED_SEM_ID) {
        ///@warning assume it would not have re-entry issue here!!
        m_transcodeContext.sessSem = AHC_OS_CreateSem(MAX_TRANSCODING_SESSION);
        m_transcodeContext.opSem = AHC_OS_CreateSem(1);
    }

    if (0 == AHC_OS_AcquireSem(m_transcodeContext.sessSem, m_transcodeContext.semTimeOut)) {
        AHC_MODE_ID ahcMode = AHC_GetAhcSysMode();
        UINT16 sem_count;
        AHC_OS_QuerySem(m_transcodeContext.sessSem, &sem_count);
        if ((ahcMode != AHC_MODE_IDLE &&
             ahcMode != AHC_MODE_NET_PLAYBACK &&
             ahcMode != AHC_MODE_THUMB_BROWSER) ||
            sem_count >= MAX_TRANSCODING_SESSION) {
            printc(FG_RED("ERR: Transcoding could only be done in AHC IDLE mode cnt=%d!\r\n"), sem_count);
            AHC_OS_ReleaseSem(m_transcodeContext.sessSem);
            return -2;
        }
    #if MAX_TRANSCODING_SESSION > 1
        if (sem_count < (MAX_TRANSCODING_SESSION - 1)) {
            return 1; //OK
        }
    #endif

        if (0 == AHC_OS_AcquireSem(m_transcodeContext.opSem, m_transcodeContext.semTimeOut)) {
            transcoding = 1;

            MMPS_DSC_SetVideo2MJpegEnable(MMP_TRUE);
            MMPS_VIDPLAY_EnableGraphicsScaler(MMP_FALSE);
            MMPS_VIDPLAY_SetMemoryMode(MMP_FALSE);

            AHC_OS_ReleaseSem(m_transcodeContext.opSem);
        } else {
            printc(FG_RED("ERR: Cannot acquire opSem!\r\n"));
            return -3;
        }
    } else {
        //1: time out, 2: ISR
        printc(FG_RED("ERR: Transcoding timeout!\r\n"));
        return -1;
    }

#endif

    return 0;
}

///@retval -1: err.\n
/// 1: closed one session but not stop the transcoding.
/// 0: stop the transcoding.
INT32 AIHC_CloseTranscode(void)
{
#if (VIDEO_DEC_TO_MJPEG)
    UINT16 sem_count;
    AHC_OS_QuerySem(m_transcodeContext.sessSem, &sem_count);
    if (m_transcodeContext.sessSem == UNDEFINED_SEM_ID || sem_count == MAX_TRANSCODING_SESSION) {
        //check calling flow for this error.
        printc(FG_RED("ERR: Transcoding on closing! sem_cnt:%d\r\n"), sem_count);
        return -1;
    }
    #if MAX_TRANSCODING_SESSION > 1
    if (sem_count < (MAX_TRANSCODING_SESSION - 1)) {
        AHC_OS_ReleaseSem(m_transcodeContext.sessSem);
        return 1; //OK
    }
    #endif

    //close the transcoding
    AHC_OS_AcquireSem(m_transcodeContext.opSem, m_transcodeContext.semTimeOut);
    {
        MMPS_VIDPLAY_Close();
        MMPS_DSC_SetVideo2MJpegEnable(MMP_FALSE);
        MMPS_VIDPLAY_EnableGraphicsScaler(MMP_TRUE);
        transcoding = 0;
    }
    AHC_OS_ReleaseSem(m_transcodeContext.opSem);

    AHC_OS_ReleaseSem(m_transcodeContext.sessSem);
    // TODO:
    // AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, TRANSCODE_EVENT, 0);
#endif
    return 0;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_StreamingTimer_Start
//  Description :
//------------------------------------------------------------------------------
void AHC_StreamingTimer_Start(void)
{
#if (WIFI_PORT == 1)
    MMPF_StreamingTimer_Start();
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_StreamingTimer_Stop
//  Description :
//------------------------------------------------------------------------------
void AHC_StreamingTimer_Stop(void)
{
#if (WIFI_PORT == 1)
    MMPF_StreamingTimer_Stop();
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_StreamingTimer_SetMs
//  Description :
//------------------------------------------------------------------------------
void AHC_StreamingTimer_SetMs(MMP_ULONG ulMs)
{
#if (WIFI_PORT == 1)
    MMPF_StreamingTimer_SetMs(ulMs);
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_StreamingTimer_GetMs
//  Description :
//------------------------------------------------------------------------------
MMP_ULONG AHC_StreamingTimer_GetMs(void)
{
#if (WIFI_PORT == 1)
    return MMPF_StreamingTimer_GetMs();
#else
    return 0;
#endif
}

#else // WIFI_PORT

AHC_BOOL VideoRecordStreamCallback(MMP_M_STREAMCB_ACTION cb_action, MMP_ULONG framesize, MMP_M_STREAM_INFO* moveinfo)
{
    return AHC_FALSE;
}

#endif  // WIFI_PORT
