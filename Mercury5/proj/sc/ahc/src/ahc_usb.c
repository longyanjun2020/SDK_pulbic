//==============================================================================
//
//  File        : AHC_USB.c
//  Description : AHC USB function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_usb.h"
#include "ahc_gpio.h"
#include "ahc_video.h"
#include "ahc_modectl.h"
#include "ahc_usbhost.h"
#include "component_cfg.h"
#include "component_dip.h"
#include "component_uvc.h"
#include "mmps_system.h"
#include "mmp_usbctl_inc.h"
#include "mmp_usb_inc.h"
#include "snr_cfg.h"
#include "usb_cfg.h"
#include "mmpf_usbmsdc.h"
#if (SUPPORT_UVC_FUNC)
#include "pCam_api.h"
#include "mmpf_usbuvc.h"
#endif
#include "drvUSB_rtk.h"
#include "mdl_hostuvc.h"
#include "MenuSetting.h"
#if(WIFI_PORT)
#include "net_cfg.h"
#endif
/*===========================================================================
 * Macro define
 *===========================================================================*/

#ifdef __FUNCTION__
#undef __FUNCTION__
#endif

#define _AHC_USB_CHECK_POINTER_VALID(p) if (p==NULL) {UartSendTrace("%s,%d error!\r\n",__FUNCTION__,__LINE__);while(1);}
#define _AHC_USB_ASSERT {UartSendTrace("%s,%d error!\r\n",__FUNCTION__,__LINE__);while(1);}
#define _AHC_USB_PRINTC(...) //UartSendTrace(__VA_ARGS__) //Enable it in debug mode.

/*===========================================================================
 * Global variable
 *===========================================================================*/

#ifndef USB_IN_DETECT_VBUS_PIN
#error "Please define USB_IN_DETECT_VBUS_PIN!"
#endif
#ifndef USB_OUT_PWR_SW_PIN
#error "Please define USB_OUT_PWR_SW_PIN!  If the project does not support rear camera, define it as MMP_GPIO_MAX."
#endif

static const struct USB_DETECT_ROUTINE _usb_det_routine = {
    USB_DETECT_PHASE_INIT,
    USB_DETECT_PHASE_INIT,
    200,
    USB_DETECTION_DISABLE_TIMEOUT_CNT,
    USB_DETECTION_DISABLE_TIMEOUT_CNT,
    (!USB_IN_DETECT_VBUS_PIN_ACTIVE) & 0x01,
    0,
    NULL,
    NULL,
    AHC_USBDetectRoutine
};

static const struct USB_DETECT_TYPE _usb_det_type[USB_DETECT_PHASE_MAX] = {
    //{&_usb_det_routine, sizeof(struct USB_DETECT_TYPE), USB_DETECT_PHASE_OP_NONE, AHC_USB_SizeOf, AHC_USB_SubRoutine, NULL, NULL, NULL},
    {&_usb_det_routine, USB_DETECT_PHASE_INIT,          AHC_USB_SubRoutine, AHC_USB_INIT_Detect,            AHC_USB_INIT_Exec,          AHC_USB_INIT_Notify},
#if USB_DETECTION_CUSTOM
    {&_usb_det_routine, USB_DETECT_PHASE_CHECK_VBUS,    AHC_USB_SubRoutine, AHC_USB_Check_VBUS_Custom_Detect,      AHC_USB_Check_VBUS_Custom_Exec,    AHC_USB_Check_VBUS_Custom_Notify},
    {&_usb_det_routine, USB_DETECT_PHASE_CHECK_USBID,   AHC_USB_SubRoutine, AHC_USB_Check_USBID_Custom_Detect,     AHC_USB_Check_USBID_Custom_Exec,   AHC_USB_Check_USBID_Custom_Notify},
#else
    {&_usb_det_routine, USB_DETECT_PHASE_CHECK_VBUS,    AHC_USB_SubRoutine, AHC_USB_Check_VBUS_Detect,      AHC_USB_Check_VBUS_Exec,    AHC_USB_Check_VBUS_Notify},
    {&_usb_det_routine, USB_DETECT_PHASE_CHECK_USBID,   AHC_USB_SubRoutine, AHC_USB_Check_USBID_Detect,     AHC_USB_Check_USBID_Exec,   AHC_USB_Check_USBID_Notify},
#endif
    {&_usb_det_routine, USB_DETECT_PHASE_OTG_SESSION,   AHC_USB_SubRoutine, AHC_USB_OTG_Session_Detect,     AHC_USB_OTG_Session_Exec,   AHC_USB_OTG_Session_Notify},
    {&_usb_det_routine, USB_DETECT_PHASE_VBUS_ACTIVE,   AHC_USB_SubRoutine, AHC_USB_VBUS_Active_Detect,     AHC_USB_VBUS_Active_Exec,   AHC_USB_VBUS_Active_Notify},
#if USB_DETECTION_CUSTOM
    {&_usb_det_routine, USB_DETECT_PHASE_CHECK_CONN,    AHC_USB_SubRoutine, AHC_USB_Check_Connect_Custom_Detect,   AHC_USB_Check_Connect_Exec, AHC_USB_Check_Connect_Notify},
    {&_usb_det_routine, USB_DETECT_PHASE_REAR_CAM,      AHC_USB_SubRoutine, AHC_USB_Check_Connect_Custom_Detect,   AHC_USB_Check_Connect_Exec, AHC_USB_Rearcam_Notify},
    {&_usb_det_routine, USB_DETECT_PHASE_REAR_CAM_DISCONN,      AHC_USB_SubRoutine, AHC_USB_RearCam_Disconn_Custom_Detect, AHC_USB_RearCam_Disconn_Custom_Exec, AHC_USB_RearCam_Disconn_Custom_Notify},
#else
    {&_usb_det_routine, USB_DETECT_PHASE_CHECK_CONN,    AHC_USB_SubRoutine, AHC_USB_Check_Connect_Detect,   AHC_USB_Check_Connect_Exec, AHC_USB_Check_Connect_Notify},
    {&_usb_det_routine, USB_DETECT_PHASE_REAR_CAM,      AHC_USB_SubRoutine, AHC_USB_Check_Connect_Detect,   AHC_USB_Check_Connect_Exec, AHC_USB_Rearcam_Notify},
#endif
    {&_usb_det_routine, USB_DETECT_PHASE_NG,            AHC_USB_SubRoutine, NULL,                           NULL,                       NULL},
};

AHC_BOOL                    gbAHC_USBDetectionHighPriority = AHC_TRUE;

static AHC_BOOL             gbUVCDeviceEnum = AHC_FALSE;

static void*                m_pvH264UVCHdl[VR_MAX_H264_STREAM_NUM];
static MMP_MJPEG_OBJ_PTR    m_stUvcMJpegObjPtr = {0};

AHC_BOOL                    bUsbForcePCAM = AHC_FALSE;

/*===========================================================================
 * Extern function
 *===========================================================================*/

#if (MTP_FUNC == 1)
extern MMP_USHORT   usb_initialize(USB_STATE *pState);
extern MMP_USHORT   usb_checkcommand(USB_STATE *pState);
extern MMP_USHORT   usb_receivedata(USB_STATE *pState, MMP_UBYTE *pBuffer, MMP_ULONG size, MMP_ULONG *pCount, USB_TRANSFER *state);
extern MMP_USHORT   usb_senddata(USB_STATE *pState, MMP_UBYTE *pBuffer, MMP_ULONG size, MMP_ULONG *pCount, USB_TRANSFER state);
extern MMP_USHORT   usb_sendevent(USB_STATE *pState, MMP_UBYTE *pBuffer, MMP_ULONG size, MMP_USHORT *count);
extern MMP_USHORT   usb_disconnect(USB_STATE *pState);
extern MMP_USHORT   usb_connect(USB_STATE *pState);
extern MMP_USHORT   usb_reset(USB_STATE *pState);
extern void         usb_stall(USB_STATE *pState);
extern void         usb_unstall(USB_STATE *pState);
extern MMP_USHORT   usb_isconnected(USB_STATE *pState);
#endif
#if  (defined(SUPPORT_ISP_CALIBRATION) && (SUPPORT_ISP_CALIBRATION == 1))
extern void         AHC_WriteISPCalibData2SIF_CB(MMP_USB_EVENT event);
#endif
extern void         USB_BDevice_In(UINT8 in);
extern void         MApi_USBHost_Init();

extern MMP_ULONG    m_glOpenFileCount;
extern AHC_BOOL     gbAhcDbgBrk;
extern const UINT16 gsAhcPrmSensor;
extern const UINT16 gsAhcScdSensor;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

#if 0
void __UVC_Streaming_API__(){}
#endif

#if (SUPPORT_UVC_FUNC && (SUPPORT_H264_WIFI_STREAM || SUPPORT_MJPEG_WIFI_STREAM))
//------------------------------------------------------------------------------
//  Function    : AIHC_SetH264UVCAttr
//  Description :
//------------------------------------------------------------------------------
static void AIHC_SetH264UVCAttr(void* pvWifiHandle, MMP_UBYTE ubCamSel)
{
    MMP_H264_STREAM_OBJ     *pstStream = (MMP_H264_STREAM_OBJ*)pvWifiHandle;
    MMPS_3GPRECD_FRAMERATE  stSnrFps = {1001, 30000};
    MMPS_3GPRECD_FRAMERATE  stEncFps = {1001, 30000};
    MMPS_3GPRECD_FRAMERATE  stMgrFps = {1001, 30000};
    UINT32                  u32Param = 0;
    MMP_ULONG               ulBitrate = 8000000;
    MMP_UBYTE               ubStreamSel = 0;

    if (ubCamSel == PRM_SENSOR)
        ubStreamSel = MMPS_H264_STRM_PRM;
    else
        ubStreamSel = MMPS_H264_STRM_SCD;

    MMPF_VIDENC_SetH264ForceICount(3);
    MMPF_VIDMGR_SetUVCH264StreamingEnable(MMP_TRUE);

    // Must match USB description. e.g. H264_FRAME_DESC(0x03, 1920, 1080, 30) TBD
    switch (pcam_usb_get_info()->pCamVideoRes) {
        case PCAM_USB_RESOL_720x480:
            MMPS_H264_STREAM_CustomedResol(ubStreamSel, MMP_SCAL_FITMODE_OPTIMAL, 720, 480);
            ulBitrate = 4000000;
            break;
        case PCAM_USB_RESOL_1024x576:
            MMPS_H264_STREAM_CustomedResol(ubStreamSel, MMP_SCAL_FITMODE_OPTIMAL, 1024, 576);
            ulBitrate = 6000000;
            break;
        case PCAM_USB_RESOL_1280x720:
            MMPS_H264_STREAM_CustomedResol(ubStreamSel, MMP_SCAL_FITMODE_OPTIMAL, 1280, 720);
            ulBitrate = 8000000;
            break;
        case PCAM_USB_RESOL_1920x1080:
            MMPS_H264_STREAM_CustomedResol(ubStreamSel, MMP_SCAL_FITMODE_OPTIMAL, 1920, 1080);
            ulBitrate = 12000000;
            break;
        default:
            AHC_DBG_ERR(1, "UnSupport UVC H264 Resolution [%d]\r\n", pcam_usb_get_info()->pCamVideoRes);
            MMPF_VIDENC_SetH264ForceICount(0);
            MMPF_VIDMGR_SetUVCH264StreamingEnable(MMP_FALSE);
            return;
            break;
    }

    if (pcam_usb_get_info()->pCamVideoBitrate != 0) {
        ulBitrate = pcam_usb_get_info()->pCamVideoBitrate;
    }

    /* Set Video Stream Attribute */
    pstStream->stEncCfg.VisualProfile = H264ENC_MAIN_PROFILE;
    MMPS_H264_STREAM_SetProfile(ubStreamSel, pstStream->stEncCfg.VisualProfile);

    stSnrFps.ulTimeIncre = 1001;
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATEx10, &u32Param);
    if (u32Param)
        stSnrFps.ulTimeResol = u32Param * 100;
    else
        stSnrFps.ulTimeResol = 30000; // TBD

    stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
    stEncFps.ulTimeResol = stSnrFps.ulTimeResol;

    if (pcam_usb_get_info()->pCamVideoFrameRate != 0) {
        stEncFps.ulTimeIncre = 1001;
        stEncFps.ulTimeResol = pcam_usb_get_info()->pCamVideoFrameRate * 1000;
    }
    
    stMgrFps.ulTimeIncre = stEncFps.ulTimeIncre;
    stMgrFps.ulTimeResol = stEncFps.ulTimeResol;

    pstStream->stEncCfg.SnrFrameRate.ulTimeIncre = stSnrFps.ulTimeIncre;
    pstStream->stEncCfg.SnrFrameRate.ulTimeResol = stSnrFps.ulTimeResol;
    pstStream->stEncCfg.EncFrameRate.ulTimeIncre = stEncFps.ulTimeIncre;
    pstStream->stEncCfg.EncFrameRate.ulTimeResol = stEncFps.ulTimeResol;
    pstStream->stEncCfg.MgrFrameRate.ulTimeIncre = stMgrFps.ulTimeIncre;
    pstStream->stEncCfg.MgrFrameRate.ulTimeResol = stMgrFps.ulTimeResol;
    MMPS_H264_STREAM_SetFrameRatePara(ubStreamSel,
                                      &(pstStream->stEncCfg.SnrFrameRate),
                                      &(pstStream->stEncCfg.EncFrameRate),
                                      &(pstStream->stEncCfg.MgrFrameRate));

    pstStream->stEncCfg.ulBitrate = ulBitrate;
    MMPS_H264_STREAM_SetBitrate(ubStreamSel, pstStream->stEncCfg.ulBitrate);

    pstStream->stEncCfg.usPFrameCount = pcam_usb_get_info()->pCamVideoPFrameCount;
    MMPS_H264_STREAM_SetPFrameCount(ubStreamSel, pstStream->stEncCfg.usPFrameCount);

    pstStream->stEncCfg.usBFrameCount = 0;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StartH264UVCStream
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_StartH264UVCStream(void* pvUvcCfg)
{
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;
    MMP_UBYTE               ubCamSel = pstUvcCBCfg->ubCamSel;
    MMP_UBYTE               ubStreamSel = 0;

    if (ubCamSel == PRM_SENSOR)
        ubStreamSel = MMPS_H264_STRM_PRM;
    else
        ubStreamSel = MMPS_H264_STRM_SCD;

    eRetErr = MMPS_H264_STREAM_OpenStream(ubStreamSel, ubCamSel, MMP_H264_STREAM_USAGE_PCAM, &m_pvH264UVCHdl[ubStreamSel], MMP_H264_STREAM_MODE_NONE);

    AIHC_SetH264UVCAttr(m_pvH264UVCHdl[ubStreamSel], ubCamSel);

    if (ubCamSel == gsAhcPrmSensor)
        eRetErr = MMPS_3GPRECD_SetH264EncUseMode(VIDRECD_USEMODE_CB2AP, VIDENC_STREAM_WIFI_PRM);
    else if (ubCamSel == gsAhcScdSensor)
        eRetErr = MMPS_3GPRECD_SetH264EncUseMode(VIDRECD_USEMODE_CB2AP, VIDENC_STREAM_WIFI_SCD);

    eRetErr = MMPS_H264_STREAM_StartUVCStream(m_pvH264UVCHdl[ubStreamSel]);

    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "AIHC_StartH264UVCStream => Opne/Start Stream Fail\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StopH264UVCStream
//  Description :
//---------------------------------------------------------------------------
static AHC_BOOL AIHC_StopH264UVCStream(void* pvUvcCfg)
{
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;

    MMPF_VIDENC_SetH264ForceICount(0);
    MMPF_VIDMGR_SetUVCH264StreamingEnable(MMP_FALSE);

    eRetErr = MMPS_H264_STREAM_StopStream(&m_pvH264UVCHdl[pstUvcCBCfg->ubCamSel]);
    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "AIHC_StopH264UVCStream => Stop Stream Fail\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StartMJPEGUVCStream
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_StartMJPEGUVCStream(void* pvUvcCfg)
{
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;
    MMP_MJPEG_ENC_INFO      stMjpgEncInfo;
    MMP_MJPEG_RATE_CTL      *pRC = NULL;

    if (pcam_usb_get_2nd_vid_fmt() == PCAM_USB_VIDEO_FORMAT_MJPEG) {
        stMjpgEncInfo.bTargetCtl     = MMP_TRUE;
        stMjpgEncInfo.bLimitCtl      = MMP_TRUE;
        stMjpgEncInfo.bTargetSize    = (pcam_usb_get_info()->pCam2ndVideoBitrate / pcam_usb_get_info()->pCam2ndVideoFrameRate) / 1024;
        stMjpgEncInfo.bLimitSize     = (stMjpgEncInfo.bTargetSize * 110) / 100;
        stMjpgEncInfo.bMaxTrialCnt   = 1;
        stMjpgEncInfo.Quality        = 1;//MMP_JPGENC_RC_QUALITY_SEL_NORMAL;
        stMjpgEncInfo.usEncWidth     = ALIGN_X(pstUvcCBCfg->usStreamW, 16);
        stMjpgEncInfo.usEncHeight    = ALIGN_X(pstUvcCBCfg->usStreamH, 16);
    }
    else {
        stMjpgEncInfo.bTargetCtl     = MMP_FALSE;
        stMjpgEncInfo.bLimitCtl      = MMP_FALSE;
        stMjpgEncInfo.bTargetSize    = 200;
        stMjpgEncInfo.bLimitSize     = 220;
        stMjpgEncInfo.bMaxTrialCnt   = 1;
        stMjpgEncInfo.Quality        = 1;//MMP_JPGENC_RC_QUALITY_SEL_NORMAL;
        stMjpgEncInfo.usEncWidth     = ALIGN_X(pstUvcCBCfg->usStreamW, 16);
        stMjpgEncInfo.usEncHeight    = ALIGN_X(pstUvcCBCfg->usStreamH, 16);
    }

    if (pstUvcCBCfg->ubCamSel == gsAhcPrmSensor) {
        eRetErr = MMPS_MJPEG_OpenStream(gsAhcPrmSensor, MMP_MJPEG_STREAM_FCAM_VIDEO, MMP_STREAM_UI_MODE_UVC_VR, &m_stUvcMJpegObjPtr);
        eRetErr = MMPS_MJPEG_StartStream(MMP_STREAM_UI_MODE_UVC_VR, m_stUvcMJpegObjPtr, &stMjpgEncInfo, pRC);
    }
    else {
        eRetErr = MMPS_MJPEG_OpenStream(gsAhcScdSensor, MMP_MJPEG_STREAM_RCAM_VIDEO, MMP_STREAM_UI_MODE_UVC_VR, &m_stUvcMJpegObjPtr);
        eRetErr = MMPS_MJPEG_StartStream(MMP_STREAM_UI_MODE_UVC_VR, m_stUvcMJpegObjPtr, &stMjpgEncInfo, pRC);
    }

    if (eRetErr) {
        AHC_DBG_ERR(1, "AIHC_StartMJPEGUVCStream => Open/Start Stream Fail\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StopMJPEGUVCStream
//  Description :
//---------------------------------------------------------------------------
static AHC_BOOL AIHC_StopMJPEGUVCStream(void* pvUvcCfg)
{
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;

    eRetErr = MMPS_MJPEG_StopStream(m_stUvcMJpegObjPtr);
    eRetErr |= MMPS_MJPEG_CloseStream(&m_stUvcMJpegObjPtr);

    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "AIHC_StopMJPEGUVCStream => Stop Stream Fail\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StartYUV422UVCStream
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_StartYUV422UVCStream(void* pvUvcCfg)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_YUV422_STREAM_OpenUVCStream(pvUvcCfg);

    eRetErr |= MMPS_YUV422_STREAM_StartUVCStream(pvUvcCfg);

    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "AIHC_StartYUV422UVCStream => Start Stream Fail\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_StopYUV422UVCStream
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_StopYUV422UVCStream(void* pvUvcCfg)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_YUV422_STREAM_StopUVCStream(pvUvcCfg);

    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "AIHC_StopYUV422UVCStream => Stop Stream Fail\r\n");
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_UVC_InitISP
//  Description :
//---------------------------------------------------------------------------
static int AHC_UVC_InitISP(void* pvUvcCfg)
{
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;
    MMP_UBYTE               ubCamSel = pstUvcCBCfg->ubCamSel;
    MMP_BOOL                ubPrevwEn = MMP_FALSE;
    MMP_UBYTE               ubHdrType = 0;

    if (pvUvcCfg == NULL) {
        return 1;
    }

    eRetErr = MMPS_3GPRECD_GetPreviewPipeStatus(ubCamSel, &ubPrevwEn);

    if (MMP_TRUE == pcam_usb_get_mix_mode() || ubPrevwEn == MMP_TRUE) {
        return 0;
    }

    /* Initial ISP */
    eRetErr = MMPF_ISP_GlobalInit();

    ubHdrType = (MMP_UBYTE)MMP_GetVidHDRType(CAM_TYPE_PRM);

    if ((ubCamSel == gsAhcPrmSensor) && (MMP_IsPrmCamExist())) { //Only primary sensor can support HDR function.

        /* Initial Channel Setting */
        if (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR)) {
            eRetErr = MMPF_ISP_AllocatePrmSensorChannel(ubHdrType);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return 1;}
        }
        else if ((CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) ||
                 (CAM_CHECK_PRM(PRM_CAM_YUV_SENSOR))) {
            eRetErr = MMPF_ISP_AllocatePrmRAWStoreSensorChannel();
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return 1;}
        }
    }
    else if ((ubCamSel == gsAhcScdSensor) && (MMP_IsScdCamExist())) {
        // TBD
    }

    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "AHC_UVC_InitISP Fail Fmt[%d]\r\n", pstUvcCBCfg->usStreamFmt);
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : AHC_UVC_InitPipe
//  Description :
//---------------------------------------------------------------------------
static int AHC_UVC_InitPipe(void* pvUvcCfg)
{
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;
    MMP_UBYTE               ubCamSel = pstUvcCBCfg->ubCamSel;
    MMP_BOOL                ubPrevwEn = MMP_FALSE;
    MMP_UBYTE               ulHdrType = 0;

    if (pvUvcCfg == NULL) {
        return 1;
    }

    eRetErr = MMPS_3GPRECD_SetUVCPreviewPipe( pstUvcCBCfg );

    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "AHC_UVC_InitPipe Fail Fmt[%d]\r\n", pstUvcCBCfg->usStreamFmt);
    }

    eRetErr = MMPS_3GPRECD_GetPreviewPipeStatus(ubCamSel, &ubPrevwEn);

    if (MMP_TRUE == pcam_usb_get_mix_mode() || ubPrevwEn == MMP_TRUE) {
        return 0;
    }

    ulHdrType = (MMP_UBYTE)MMP_GetVidHDRType(CAM_TYPE_PRM);

    if ((ubCamSel == gsAhcPrmSensor) && (MMP_IsPrmCamExist())) { //Only primary sensor can support HDR function.
        MMP_ULONG ulIqCfgIdx = 0;

        ulIqCfgIdx = (ulHdrType == 0) ? 0 : 1; // For iqcfg file
        eRetErr = MMPS_Sensor_SetPreviewMode(gsAhcPrmSensor, AHC_SNR_GetPresetPrmSnrMode());
        eRetErr = MMPS_Sensor_Initialize(gsAhcPrmSensor, AHC_SNR_GetPresetPrmSnrMode(), MMP_SNR_VID_PRW_MODE, ulHdrType, ulIqCfgIdx);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return 1; }

        /* Start Prm Preview Flow (Open VIF) */
        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            MMPF_Sensor_SetDualBayerSensor(MMP_FALSE);
        }

        eRetErr = MMPS_3GPRECD_PrmCamPreviewStart(gsAhcPrmSensor, MMP_FALSE);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return 1;}
    }
    else if ((ubCamSel == gsAhcScdSensor) && (MMP_IsScdCamExist())) {
        // TBD
    }

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : AHC_UVC_StartStreaming
//  Description :
//---------------------------------------------------------------------------
static int AHC_UVC_StartStreaming(void* pvUvcCfg)
{
    AHC_BOOL                bAhcRet = AHC_TRUE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;

    if (pvUvcCfg == NULL) {
        return 1;
    }

    switch (pstUvcCBCfg->usStreamFmt) {
    case MMPS_3GPRECD_VIDEO_FORMAT_H264:
        bAhcRet = AIHC_StartH264UVCStream(pvUvcCfg);
        break;
    case MMPS_3GPRECD_VIDEO_FORMAT_MJPEG:
        bAhcRet = AIHC_StartMJPEGUVCStream(pvUvcCfg);
        break;
    case MMPS_3GPRECD_VIDEO_FORMAT_YUV422:
        bAhcRet = AIHC_StartYUV422UVCStream(pvUvcCfg);
        break;
    case MMPS_3GPRECD_VIDEO_FORMAT_YUV420:
        break;
    }

    if (pcam_usb_get_2nd_vid_fmt() == PCAM_USB_VIDEO_FORMAT_MJPEG) {
        USBH_UVC_CB_FUNC_CFG    stUvcCBCfg;
        stUvcCBCfg.ubCamSel       = pstUvcCBCfg->ubCamSel;
        stUvcCBCfg.usStreamW      = pcam_usb_get_info()->pCam2ndVideoWidth;
        stUvcCBCfg.usStreamH      = pcam_usb_get_info()->pCam2ndVideoHeight;
        stUvcCBCfg.usStreamFmt    = pcam_usb_get_info()->pCam2ndVideoFormat;

        bAhcRet &= AIHC_StartMJPEGUVCStream(&stUvcCBCfg);
    }

    if (bAhcRet != AHC_TRUE) {
        AHC_DBG_ERR(1, "AHC_UVC_StartStreaming Fail Fmt[%d]\r\n", pstUvcCBCfg->usStreamFmt);
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : AHC_UVC_StopStreaming
//  Description :
//---------------------------------------------------------------------------
static int AHC_UVC_StopStreaming(void* pvUvcCfg)
{
    AHC_BOOL                bAhcRet = AHC_TRUE;
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;
    MMP_UBYTE               ubCamSel = pstUvcCBCfg->ubCamSel;

    if (pvUvcCfg == NULL) {
        return 1;
    }

    switch (pstUvcCBCfg->usStreamFmt) {
    case MMPS_3GPRECD_VIDEO_FORMAT_H264:
        bAhcRet = AIHC_StopH264UVCStream(pvUvcCfg);
        break;
    case MMPS_3GPRECD_VIDEO_FORMAT_MJPEG:
        bAhcRet = AIHC_StopMJPEGUVCStream(pvUvcCfg);
        break;
    case MMPS_3GPRECD_VIDEO_FORMAT_YUV422:
        bAhcRet = AIHC_StopYUV422UVCStream(pvUvcCfg);
        break;
    case MMPS_3GPRECD_VIDEO_FORMAT_YUV420:
        break;
    }

    if (pcam_usb_get_2nd_vid_fmt() == PCAM_USB_VIDEO_FORMAT_MJPEG) {
        USBH_UVC_CB_FUNC_CFG    stUvcCBCfg;
        stUvcCBCfg.ubCamSel       = pstUvcCBCfg->ubCamSel;
        stUvcCBCfg.usStreamW      = pcam_usb_get_info()->pCam2ndVideoWidth;
        stUvcCBCfg.usStreamH      = pcam_usb_get_info()->pCam2ndVideoHeight;
        stUvcCBCfg.usStreamFmt    = pcam_usb_get_info()->pCam2ndVideoFormat;

        bAhcRet = AIHC_StopMJPEGUVCStream(&stUvcCBCfg);

        usb_uvc_reset_multi_stream();
    }

    if (bAhcRet != AHC_TRUE) {
        AHC_DBG_ERR(1, "AHC_UVC_StopStreaming Fail Fmt[%d]\r\n", pstUvcCBCfg->usStreamFmt);
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : AHC_UVC_CloseStreaming
//  Description :
//---------------------------------------------------------------------------
int AHC_UVC_CloseStreaming(MMP_UBYTE ubCamSel)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    // Ref : AHC_VIDEO_RecdCmdStateExecIdle()
    if (MMP_FALSE == pcam_usb_get_mix_mode()) {
        eRetErr = MMPS_3GPRECD_EnablePreviewPipe(ubCamSel, MMP_FALSE, MMP_FALSE);
        eRetErr = MMPS_Sensor_PowerDown(ubCamSel);
        eRetErr = MMPF_ISP_GlobalUnInit();
    }

    eRetErr = MMPS_3GPRECD_CloseUVCPreviewSrc(ubCamSel);

    return 0;
}
#endif

#if 0
void __INTERNAL_API__(){}
#endif

static void AHC_USB_Plug_Callback(unsigned char u8Event, unsigned u32Para, char *s)
{
    if(u32Para == 0) {
        if (u8Event == 1) {
            AHC_DBG_MSG(1, FG_GREEN("[USB CB] plug-in (%d)\n\n"), u32Para);
            MMPF_USBH_SetDeviceConnectedSts(MMP_TRUE);
        }
        else if (u8Event == 2) {
            AHC_DBG_MSG(1, FG_GREEN("[USB CB] plug-out (%d)\n\n"), u32Para);
            MMPF_USBH_SetDeviceConnectedSts(MMP_FALSE);
        }
    }
}

AHC_BOOL AHC_USB_DisConnectDevice(void)
{
    MMP_ERR sRet = MMP_ERR_NONE;

    AHC_SetUsbMode(AHC_USB_MODE_NONE);

    sRet = MMPS_USB_StopDevice();
    sRet |= MMPS_USB_DisconnectDevice();

    if (sRet != MMP_ERR_NONE) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

#if 0
void __AHC_USB_API__(){}
#endif

/**
 @brief Set USB operating mode

 This function setup the USB operating mode and return execution status.
 Parameters:
 @param[in] byMode: the enum value of current support USB operating mode
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_SetUsbMode(AHC_USB_OP_MODE byMode)
{
    AHC_USB_OP_MODE     USBOpMode = AHC_USB_MODE_NONE;
    MMPS_USB_OP_MODE    mmps_op_mode = MMPS_USB_NONE_MODE;
    MMP_ERR             sRet = MMP_ERR_NONE;
    UINT32              ulTimeout = 50;

    //if USB device is running, then disconnect device before change mode;
    if ((AHC_IsUsbConnect() == AHC_TRUE) && (AHC_GetUsbMode(&USBOpMode) == AHC_TRUE)) {
        if (USBOpMode == byMode) {
            AHC_DBG_MSG(1, "USBOpMode is same\r\n");
            return AHC_TRUE;
        }
        else if (USBOpMode != AHC_USB_MODE_NONE) {
            AHC_DBG_MSG(1, "%s,%d USB mode is not idle!\r\n",__FUNCTION__,__LINE__);
            //AHC_UsbConnect(AHC_FALSE);
        }
    }

    switch(byMode){
        case AHC_USB_MODE_WEBCAM:
            mmps_op_mode = MMPS_USB_PCCAM_MODE;
            break;
        case AHC_USB_MODE_MASS_STORAGE:
            mmps_op_mode = MMPS_USB_MSDC_MODE;
            break;
        case AHC_USB_MODE_DPS_MODE:
            mmps_op_mode = MMPS_USB_DPS_MODE;
            break;
        case AHC_USB_MODE_PTP_MODE:
            mmps_op_mode = MMPS_USB_PTP_MODE;
            break;
        case AHC_USB_MODE_PCSYNC_MODE:
            mmps_op_mode = MMPS_USB_PCSYNC_MODE;
            break;
        case AHC_USB_MODE_MTP_MODE:
            mmps_op_mode = MMPS_USB_MTP_MODE;
            break;
        case AHC_USB_MODE_DETECT_MODE:
            mmps_op_mode = MMPS_USB_DETECT_MODE;
            break;
        case AHC_USB_MODE_NONE:
        case AHC_USB_MODE_MAX:
        default:
            AHC_DBG_MSG(1, "%s,%d,%d error!\r\n", __FUNCTION__, __LINE__,byMode);
            break;
    }

    if (mmps_op_mode == MMPS_USB_NONE_MODE) {
        AHC_DBG_ERR(1, "%s Set Mode None\r\n", __FUNCTION__);
        return AHC_FALSE;
    }

    sRet = MMPS_USB_AdjustVref(gususb_vref);
    sRet |= MMPS_USB_AdjustBiasCurrent(gususb_bias_current);
    sRet |= MMPS_USB_AdjustSignal(gususb_tx_cur, gususb_tx_cur_plus, gususb_sq_level);

    if (sRet != MMP_ERR_NONE) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet);
        return AHC_FALSE;
    }

    if (mmps_op_mode == MMPS_USB_MSDC_MODE) {

        if (m_glOpenFileCount) {
            AHC_DBG_MSG(1, "MMPS_System_AllocateFSBuffer wait m_glOpenFileCount to be zero\r\n");

            do {
                if ((m_glOpenFileCount == 0))
                    break;

                MMPF_OS_Sleep(100);
            } while (m_glOpenFileCount && (--ulTimeout > 0));

            if (ulTimeout == 0) {
                AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet);
                return AHC_FALSE;
            }
            sRet = MMPS_System_AllocateFSBuffer();
        }
        else {
            sRet = MMPS_System_AllocateFSBuffer();
        }
    }
    else if (mmps_op_mode == MMPS_USB_PCCAM_MODE) {

        #if (SUPPORT_UVC_FUNC && (SUPPORT_H264_WIFI_STREAM || SUPPORT_MJPEG_WIFI_STREAM))
        sRet = MMPF_USBUVC_RegisterCallback(USBUVC_EVENT_INIT_SENSOR, (void*)AHC_UVC_InitISP);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet); return AHC_FALSE;}

        sRet = MMPF_USBUVC_RegisterCallback(USBUVC_EVENT_INIT_PIPE, (void*)AHC_UVC_InitPipe);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet); return AHC_FALSE;}

        sRet = MMPF_USBUVC_RegisterCallback(USBUVC_EVENT_START_STREAMING, (void*)AHC_UVC_StartStreaming);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet); return AHC_FALSE;}

        sRet = MMPF_USBUVC_RegisterCallback(USBUVC_EVENT_STOP_STREAMING, (void*)AHC_UVC_StopStreaming);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet); return AHC_FALSE;}
        #endif

        #if  (defined(SUPPORT_ISP_CALIBRATION) && (SUPPORT_ISP_CALIBRATION == 1))
        sRet = MMPS_USB_RegisterCallback(MMP_USB_EVENT_WR_CALI2SIF, (MMP_USB_Callback *)AHC_WriteISPCalibData2SIF_CB);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;}
        #endif
    }

    sRet = MMPS_USB_SetMode(mmps_op_mode);
    if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;}

    return AHC_TRUE;
}

/**
 @brief Get and return current USB operating mode

 This function is used to get the current working USB operating mode.
 Parameters:
 @param[in] *puiMode: pointer which is used to pass the enum value of current USB operating mode.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetUsbMode(AHC_USB_OP_MODE *puiMode)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    AHC_BOOL ahcRet = AHC_FALSE;
    MMPS_USB_OP_MODE usbMode;

    *puiMode = AHC_USB_MODE_NONE;

    sRet = MMPS_USB_GetMode(&usbMode);
    if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); /*return AHC_FALSE;*/}

    switch(usbMode){
    case MMPS_USB_PCCAM_MODE:
        *puiMode = AHC_USB_MODE_WEBCAM;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_MSDC_MODE:
        *puiMode = AHC_USB_MODE_MASS_STORAGE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_DPS_MODE:
        *puiMode = AHC_USB_MODE_DPS_MODE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_PTP_MODE:
        *puiMode = AHC_USB_MODE_PTP_MODE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_PCSYNC_MODE:
        *puiMode = AHC_USB_MODE_PCSYNC_MODE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_MTP_MODE:
        *puiMode = AHC_USB_MODE_MTP_MODE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_DETECT_MODE:
        *puiMode = AHC_USB_MODE_DETECT_MODE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_ISOTEST_MODE:
        *puiMode = AHC_USB_MODE_ISOTEST_MODE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_ADAPTER_MODE:
        *puiMode = AHC_USB_MODE_ADAPTER_MODE;
        ahcRet = AHC_TRUE;
        break;
    case MMPS_USB_NONE_MODE:
    case MMPS_USB_MAX_MODE:
    //case MMPS_USB_MSDC_AIT_DEBUG_MODE:
    default:
        ahcRet = AHC_FALSE;
        break;
    }

    return ahcRet;
}

AHC_BOOL AHC_USB_WaitUntilFirstRoundDone(UINT32 ulTimeoutMs)
{
    void *pusb_obj = NULL;
    USB_DETECT_PHASE USBCurPhase, USBNextPhase;

    ulTimeoutMs /= 10;

    do {
        pusb_obj = AHC_USBGetCurTypeObj(0);
        USBCurPhase = (USB_DETECT_PHASE)AHC_USBGetPhase(pusb_obj, AHC_USB_GET_PHASE_CURRENT);
        USBNextPhase = (USB_DETECT_PHASE)AHC_USBGetPhase(pusb_obj, AHC_USB_GET_PHASE_NEXT);
        AHC_OS_Sleep(10);
    } while((((USBCurPhase == USB_DETECT_PHASE_CHECK_VBUS) && (USBNextPhase == USB_DETECT_PHASE_VBUS_ACTIVE)) ||
            (USBNextPhase == USB_DETECT_PHASE_CHECK_USBID) ||
            (USBNextPhase == USB_DETECT_PHASE_OTG_SESSION) ||
            (USBNextPhase == USB_DETECT_PHASE_CHECK_CONN)) &&
            (--ulTimeoutMs > 0));

    if (ulTimeoutMs > 0) {
        return AHC_TRUE;
    }

    return AHC_FALSE;
}

void AHC_USB_PauseDetection(UINT8 bPauseDetection)
{
    void *pusb_obj=NULL;
    struct USB_DETECT_TYPE *pdet_type = NULL;
    struct USB_DETECT_ROUTINE *pusb_det_routine = NULL;

    pusb_obj = AHC_USBGetCurTypeObj(0);
    pdet_type = (struct USB_DETECT_TYPE *)pusb_obj;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    pusb_det_routine->pause_detection = bPauseDetection;
}

/**
 @brief Check the connection of USB device

 This function
 Parameters:
 @param[in]: ulM: The max period that host try to connect with B device.  Unit: milliseconds.
 @retval void
*/
void AHC_USB_SetDetectBDeviceTimeout(UINT32 ulMs)
{
    void *pusb_obj=NULL;
    struct USB_DETECT_TYPE *pdet_type = NULL;
    struct USB_DETECT_ROUTINE *pusb_det_routine = NULL;

    pusb_obj = AHC_USBGetCurTypeObj(0);
    pdet_type = (struct USB_DETECT_TYPE *)pusb_obj;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    /*
    USB_DETECT_PHASE_CHECK_VBUS -> USB_DETECT_PHASE_CHECK_USBID: USBH_CHECK_ID_TIMEOUT
    USB_DETECT_PHASE_CHECK_USBID -> USB_DETECT_PHASE_OTG_SESSION: WAIT_OTG_SESSION_INTERVAL
    USB_DETECT_PHASE_OTG_SESSION -> USB_DETECT_PHASE_CHECK_CONN: WAIT_CHECK_BDEVICE_CONN_INTERVAL
    USB_DETECT_PHASE_CHECK_CONN -> USB_DETECT_PHASE_CHECK_VBUS: POLLING_VBUS_INTERVAL
    */

    pusb_det_routine->timeout_init_val = pusb_det_routine->timeout = ((ulMs+
        (USBH_CHECK_ID_TIMEOUT+WAIT_OTG_SESSION_INTERVAL+WAIT_CHECK_BDEVICE_CONN_INTERVAL+POLLING_VBUS_INTERVAL) -1 ) /
        (USBH_CHECK_ID_TIMEOUT+WAIT_OTG_SESSION_INTERVAL+WAIT_CHECK_BDEVICE_CONN_INTERVAL+POLLING_VBUS_INTERVAL));
}

/**
 @brief Check the connection of USB device

 This function
 Parameters:
 @param[in]: void
 @retval AHC_USB_STATUS: AHC_USB_NORMAL, AHC_USB_ISADAPTER, AHC_USB_IDLE
*/
AHC_USB_STATUS AHC_USB_GetLastStatus(void)
{
    return MMPS_USB_GetLastStatus();
}

void AHC_USB_FunctionExit(void)
{
    AHC_USB_OP_MODE uiMode;

    if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC/PCCAM mode
    {
        AHC_GetUsbMode(&uiMode);

        if (uiMode == AHC_USB_MODE_MASS_STORAGE) {
            AHC_DBG_MSG(1, "AHC_USB_MODE_MASS_STORAGE exit\r\n");

            MSDCFunc_Enable(AHC_FALSE);
            MSDCTimer_Stop();
            //AHC_USB_DisConnectDevice();   //doing it in AHC_SetMode(AHC_MODE_IDLE);
            AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
        }
        else if (uiMode == AHC_USB_MODE_WEBCAM) {
            AHC_DBG_MSG(1, "AHC_USB_MODE_WEBCAM exit\r\n");
            PCCAMFunc_Enable(AHC_FALSE);
        }
    }
}

/**
 @brief Check the connection of USB device

 This function
 Parameters:
 @param[in]: void
 @retval AHC_TRUE:Connect AHC_FALSE: NO connection.
*/
AHC_BOOL AHC_IsUsbConnect(void)
{
    void *pusb_obj=NULL;
    UINT16 cur_phase;
    UINT8 bVBus_State;
    UINT16 ulTimeout=50;

    pusb_obj = AHC_USBGetCurTypeObj(0);

    cur_phase = AHC_USBGetPhase(pusb_obj, AHC_USB_GET_PHASE_CURRENT);

    //Under initiating...
    while((USB_DETECT_PHASE_INIT == cur_phase) && (--ulTimeout > 0)){
        cur_phase = AHC_USBGetPhase(pusb_obj, AHC_USB_GET_PHASE_CURRENT);
        AHC_OS_Sleep(10);
    }

    if (ulTimeout == 0) {
        AHC_DBG_MSG(1, "%s,%s timeout.\r\n", __FUNCTION__, __LINE__);
    }

    bVBus_State = AHC_USBGetVBUS(pusb_obj);

    if (USB_IN_DETECT_VBUS_PIN_ACTIVE == bVBus_State) {
        return AHC_TRUE;
    }

    return AHC_FALSE;
}

/**
 @brief Check the connection of DC Cable

 This function
 Parameters:
 @param[in]: void
 @retval AHC_TRUE:Connect AHC_FALSE: NO connection.
*/
AHC_BOOL AHC_IsDcCableConnect(void)
{
#if defined(DEVICE_GPIO_DC_INPUT)
    UINT8 bStatus;

    if (DEVICE_GPIO_DC_INPUT != MMP_GPIO_MAX) {
        AHC_GPIO_ConfigPad(DEVICE_GPIO_DC_INPUT, PAD_NORMAL_TRIG);
        AHC_GPIO_SetOutputMode(DEVICE_GPIO_DC_INPUT, AHC_FALSE);
        AHC_GPIO_GetData(DEVICE_GPIO_DC_INPUT, &bStatus);

        return (DEVICE_GPIO_DC_INPUT_LEVEL == bStatus) ? (AHC_TRUE) : (AHC_FALSE);
    }
#endif

    return AHC_FALSE;
}

AHC_BOOL AHC_IsUsbBooting(void)
{
    return (((AHC_GetBootingSrc() & PWR_ON_BY_VBUS) == PWR_ON_BY_VBUS) ? AHC_TRUE : AHC_FALSE);
}

AHC_BOOL AHC_IsDCInBooting(void)
{
    return (((AHC_GetBootingSrc() & PWR_ON_BY_DC) == PWR_ON_BY_DC) ? AHC_TRUE : AHC_FALSE);
}

#if (MSDC_SUPPORT_SECRECY_LOCK)
AHC_BOOL AHC_SetMsdcSecrecyLock(AHC_BOOL bLockMode)
{
    MMPF_MSDC_SetSecrecyLock((MMP_BOOL) bLockMode);
    return AHC_TRUE;
}

AHC_BOOL AHC_GetMsdcSecrecyLock(void)
{
    return (AHC_BOOL) MMPF_MSDC_GetSecrecyLock();
}
#endif

#if (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD)
AHC_BOOL AHC_AitScsiCustomerCmd_Register_CB(MSDC_AIT_SCSI_CUSTOMER_CB cb)
{
    MMPF_MSDC_AITSCSI_Customer_Register_CB(cb);
    return AHC_TRUE;
}
#endif

#if 0
void _USB_PTP_RELATE_FUNC_(){}
#endif

#if (MTP_FUNC == 1)
/**
 @brief Initialize PTP protocal

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpInitialize(USB_STATE* pState)//(AHC_PTP_STATE *pState)
{
    MMP_USHORT retStatus;

    retStatus = usb_initialize(pState);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief check PTP command

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpCheckCommand(USB_STATE *pState)
{
    MMP_USHORT retStatus;

    retStatus = usb_checkcommand(pState);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief Receive PTP data

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpReceiveData(USB_STATE *pState, UINT8 *pBuffer, UINT32 size, UINT32 *pCount, USB_TRANSFER *state)
{
    MMP_USHORT retStatus;

    retStatus = usb_receivedata(pState, (MMP_UBYTE*)pBuffer, (MMP_ULONG)size, (MMP_ULONG*)pCount, state);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief send PTP data

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpSendData(USB_STATE *pState, UINT8 *pBuffer, UINT32 size, UINT32 *pCount, USB_TRANSFER state)
{
    MMP_USHORT retStatus;

    retStatus = usb_senddata(pState, (MMP_UBYTE*)pBuffer, (MMP_ULONG)size, (MMP_ULONG*)pCount, state);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief send PTP event

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpSendEvent(USB_STATE *pState, UINT8 *pBuffer, UINT32 size, UINT16 *count)
{
    MMP_USHORT retStatus;

    retStatus = usb_sendevent(pState, (MMP_UBYTE*)pBuffer, (MMP_ULONG)size, (MMP_USHORT*)count);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief disconnect ptp

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpDisconnect(USB_STATE *pState)
{
    MMP_USHORT retStatus;

    retStatus = usb_disconnect(pState);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief connect PTP

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpConnect(USB_STATE *pState)
{
    MMP_USHORT retStatus;

    retStatus = usb_disconnect(pState);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief reset PTP

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpReset(USB_STATE *pState)
{
    MMP_USHORT retStatus;

    retStatus = usb_reset(pState);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

/**
 @brief stall PTP transfer

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpStall(USB_STATE *pState)
{
    usb_stall(pState);

    return AHC_TRUE;
}

/**
 @brief unstall PTP transfer

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpUnstall(USB_STATE *pState)
{
    usb_stall(pState);

    return AHC_TRUE;
}

/**
 @brief check if PTP is connected

 This function
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PtpIsConnected(USB_STATE *pState)
{
    MMP_USHORT retStatus;

    retStatus = usb_isconnected(pState);

    if (retStatus)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

#endif //#if (MTP_FUNC == 1)

void AHC_USBGetStates(USB_DETECT_PHASE *pUSBPhase, AHC_USB_GET_PHASE_STAGE sUSBPhaseStage)
{
    void *pusb_obj=NULL;

    pusb_obj = AHC_USBGetCurTypeObj(0);
    *pUSBPhase = (USB_DETECT_PHASE)AHC_USBGetPhase(pusb_obj, sUSBPhaseStage);
}

void AHC_USBGetVBUSPinData(UINT8 *bVBusStates)
{
    MMP_UBYTE   ubVbusSR;

#if defined(__RTK_OS__)//MV5
    ubVbusSR = *(volatile MMP_UBYTE *)0x1F006848;
    //AHC_DBG_MSG(1, "ubVbusSR=%x\r\n",ubVbusSR);

    if(ubVbusSR & 0x04){//bit2:Power key-2 status--->sch pad_name=5V_EVENT
        ubVbusSR = GPIO_HIGH;
    }
    else{
        ubVbusSR = GPIO_LOW;
    }
    *bVBusStates = (USB_IN_DETECT_VBUS_PIN_ACTIVE==ubVbusSR) ?
        USB_IN_DETECT_VBUS_PIN_ACTIVE : (!USB_IN_DETECT_VBUS_PIN_ACTIVE) & 0x01;

#else
    if (USB_IN_DETECT_VBUS_PIN != MMP_GPIO_MAX){
        MMPS_PIO_GetData(USB_IN_DETECT_VBUS_PIN, &ubVbusSR);
    }
    else{
        ubVbusSR = (!USB_IN_DETECT_VBUS_PIN_ACTIVE) & 0x01; //No USB connected
    }

    *bVBusStates = (USB_IN_DETECT_VBUS_PIN_ACTIVE==ubVbusSR) ?
        USB_IN_DETECT_VBUS_PIN_ACTIVE : (!USB_IN_DETECT_VBUS_PIN_ACTIVE) & 0x01;
#endif
}

void AHC_USBDetectRoutine(void *proutine, UINT8 stage)
{
#define OS_TIMER_ID_UNDEF MMPF_OS_CREATE_TMR_INT_ERR

    static MMP_ULONG os_timer_id = OS_TIMER_ID_UNDEF;
    struct USB_DETECT_ROUTINE *pusb_det_routine = (struct USB_DETECT_ROUTINE *)proutine;
    MMP_UBYTE ret;

    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    if (stage == 0) { //Stop timer.
        if(os_timer_id != OS_TIMER_ID_UNDEF){
            //OS_CRITICAL_INIT();
            //OS_ENTER_CRITICAL();
            ret = MMPF_OS_StopTimer(os_timer_id, MMPF_OS_TMR_OPT_NONE);
            //OS_EXIT_CRITICAL();

            if (ret) {
                _AHC_USB_ASSERT
            }
            else {
                os_timer_id = OS_TIMER_ID_UNDEF;
            }
        }
    }
    else{ //Start timer.

        os_timer_id = MMPF_OS_StartTimer(pusb_det_routine->timer_interval, MMPF_OS_TMR_OPT_ONE_SHOT, (MMPF_OS_TMR_CALLBACK)pusb_det_routine->pCallback, (void *)pusb_det_routine->pCallbackArg);
        if (os_timer_id == OS_TIMER_ID_UNDEF) {
            _AHC_USB_ASSERT
        }
    }
}

void AHC_USB_INIT_Detect(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);

    pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
    pusb_det_routine->timer_interval = POLLING_USB_INIT_INTERVAL;//POLLING_VBUS_INTERVAL; //TBD
    pusb_det_routine->timeout = 200; //TBD
    pusb_det_routine->Vbus_states = (!USB_IN_DETECT_VBUS_PIN_ACTIVE) & 0x01;
    pusb_det_routine->pause_detection = 0;

    if(CAM_CHECK_USB(USB_CAM_NONE))
        AHC_USBDetectSetPriority(AHC_FALSE);

#if (SUPPORT_USB_HOST_FUNC) //TODO : or support NET/WIFI
    if (1) {
        MApi_USBHost_Init();
        MDrv_USB_HotPlug_RegisterCallBack(AHC_USB_Plug_Callback);
        //TODO : below code must move to start OTG session phase
        MDrv_USB_Port_Init(0);
    #if (WIFI_PORT == 1 && WIFI_USB_HOST == 1)
        MDrv_USB_Port_Init(1);
    #endif
        uvcl_init();
        ms_otg_init_irq(NULL);

        //TODO ,need to remove below code when otg driver enable
        /*pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_CONN;
        pusb_det_routine->timer_interval = WAIT_CHECK_BDEVICE_CONN_INTERVAL;
        pusb_det_routine->timeout = 500; //TBD
        pusb_det_routine->Vbus_states = USB_IN_DETECT_VBUS_PIN_ACTIVE;
        pusb_det_routine->pause_detection = 0;*/
    }
#endif
}

void AHC_USB_INIT_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;
    MMP_ERR sRet = MMP_ERR_NONE;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_CHECK_VBUS:
            #ifdef USB_PATH_SELECT_GPIO
            if (USB_PATH_SELECT_GPIO != MMP_GPIO_MAX){
                sRet = MMPS_PIO_SetData(USB_PATH_SELECT_GPIO, USB_PATH_SELECT_SET);
                sRet |= MMPS_PIO_EnableOutputMode(USB_PATH_SELECT_GPIO, MMP_TRUE);
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            }
            #endif

            #ifdef USB_OUT_PWR_SW_PIN
            if (USB_OUT_PWR_SW_PIN != MMP_GPIO_MAX){
                sRet = MMPS_PIO_SetData(USB_OUT_PWR_SW_PIN, (!USB_OUT_PWR_SW_PIN_ACTIVE) & 0x01);
                sRet |= MMPS_PIO_EnableOutputMode(USB_OUT_PWR_SW_PIN, MMP_TRUE);
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            }
            #endif

            #if 0//def USB_IN_DETECT_VBUS_PIN
            if (USB_IN_DETECT_VBUS_PIN != MMP_GPIO_MAX){
                sRet = MMPS_PIO_EnableOutputMode(USB_IN_DETECT_VBUS_PIN, MMP_FALSE);
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            }
            #endif

            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
#if defined( __RTK_OS__ )
        case USB_DETECT_PHASE_CHECK_CONN:
        case USB_DETECT_PHASE_REAR_CAM:
            break;
#endif
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_INIT_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)
}

void AHC_USB_Check_VBUS_Detect(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    AHC_USBGetVBUSPinData(&pusb_det_routine->Vbus_states);

    if(1 == pusb_det_routine->pause_detection){
        pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL;
    }
    else if(USB_IN_DETECT_VBUS_PIN_ACTIVE==pusb_det_routine->Vbus_states){
        /* VBUS Active */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_VBUS_ACTIVE;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL; //USBH_WAIT_DEV_CONN_CHECK_INTERVAL*USBH_WAIT_DEV_CONN_TIMEOUT_CNT;
    }
    else{
        /* VBUS inactive */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_USBID;
        pusb_det_routine->timer_interval = USBH_CHECK_ID_TIMEOUT;
    }
}

void AHC_USB_Check_VBUS_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;
    MMP_ERR sRet = MMP_ERR_NONE;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_VBUS_ACTIVE:
        	if(IsBootAsPCAMOnly()) {
        		extern MMP_BOOL	gbIsAdapter;
        		gbIsAdapter = MMP_FALSE;
        	}
        	else
            {
                MMP_UBYTE   i = 0x0, ubTimeOutLimit = 0x10; // 0x10->0x20 for some PC, USB RESET may delay arrived
                AHC_BOOL    ubAdapterConnect = AHC_TRUE;

                //MMPF_SetUSBChangeMode(USB_DETECT_MODE);
                usb_device_function(USB_DETECT_MODE);
                ubTimeOutLimit = 15;//35;
                for(i = 0x0; i < ubTimeOutLimit ; i++) {
                    if(!MMPF_USB_IsAdapter()) {
                        ubAdapterConnect = MMP_FALSE;
                        break;
                    }
                    AHC_OS_Sleep(100); //To lower the checking frequency, it can be adjusted !
                }

                if(i == ubTimeOutLimit){
                    sRet = MMPF_USB_StopDevice();
                    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
                }
            }
        	_AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_USBID:
            sRet = MMPS_USB_TriggerReadUSBID(0);            //TBD
            if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

extern void USB_Cable_In(UINT8 in);

void AHC_USB_Check_VBUS_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_VBUS_ACTIVE:
            USB_Cable_In(1);
            AHC_DBG_MSG(1, "========== USB cable in. ========== \r\n");
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_USBID:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Check_USBID_Detect(void *ptype)
{
    MMP_UBYTE ubDevSR;
    MMP_ERR sRet = MMP_ERR_NONE;

    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    sRet = MMPS_USB_ReadUSBID(&ubDevSR);
    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }

    AHC_USBGetVBUSPinData(&pusb_det_routine->Vbus_states);

    if (GPIO_LOW == ubDevSR) {

        if (USB_IN_DETECT_VBUS_PIN_ACTIVE == pusb_det_routine->Vbus_states) {
            /* denied case: exception */
            //_ASSERT_V("OTG_CABLE_VBUS_IN!",__FILE__,__LINE__);
            pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;//USB_DETECT_PHASE_NG;
            pusb_det_routine->timer_interval = 0; //TBD
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
        else {
            pusb_det_routine->next_phase = USB_DETECT_PHASE_OTG_SESSION;
            pusb_det_routine->timer_interval = WAIT_OTG_SESSION_INTERVAL;
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
    }
    else{
        /* USB_ID HIGH: NC or B Device */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL;
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
}

void AHC_USB_Check_USBID_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;
    MMP_ERR sRet = MMP_ERR_NONE;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_OTG_SESSION:
            /* Enable PWR SW, VBus power to device */
            #ifdef USB_OUT_PWR_SW_PIN
            if (USB_OUT_PWR_SW_PIN != MMP_GPIO_MAX) {
                sRet = MMPS_PIO_SetData(USB_OUT_PWR_SW_PIN, USB_OUT_PWR_SW_PIN_ACTIVE);
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            }
            #endif
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_NG:
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Check_USBID_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    //NOP
    _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
}

#if USB_DETECTION_CUSTOM
void AHC_USB_Check_VBUS_Custom_Detect(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    AHC_USBGetVBUSPinData(&pusb_det_routine->Vbus_states);

    if((USB_IN_DETECT_VBUS_PIN_ACTIVE == pusb_det_routine->Vbus_states) ){
        /* VBUS Active */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_USBID;
        pusb_det_routine->timer_interval = USBH_CHECK_ID_TIMEOUT; //USBH_WAIT_DEV_CONN_CHECK_INTERVAL*USBH_WAIT_DEV_CONN_TIMEOUT_CNT;
        pusb_det_routine->timeout = (pusb_det_routine->timeout > 0) ? pusb_det_routine->timeout - 1 : pusb_det_routine->timeout;
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
    else{
        /* VBUS inactive */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL;
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
}

void AHC_USB_Check_VBUS_Custom_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;
    MMP_ERR sRet = MMP_ERR_NONE;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_USBID:
            sRet = MMPS_USB_TriggerReadUSBID(0);            //TBD
            if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Check_VBUS_Custom_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_USBID:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Check_USBID_Custom_Detect(void *ptype)
{
    MMP_UBYTE ubDevSR;
    MMP_ERR sRet = MMP_ERR_NONE;

    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    sRet = MMPS_USB_ReadUSBID(&ubDevSR);
    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }

    AHC_USBGetVBUSPinData(&pusb_det_routine->Vbus_states);

    if(GPIO_LOW == ubDevSR){
        if(USB_IN_DETECT_VBUS_PIN_ACTIVE==pusb_det_routine->Vbus_states && (pusb_det_routine->timeout != 0)){
            pusb_det_routine->next_phase = USB_DETECT_PHASE_OTG_SESSION;
            pusb_det_routine->timer_interval = WAIT_OTG_SESSION_INTERVAL;
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
        else{
            pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
            pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL;
            pusb_det_routine->timeout = pusb_det_routine->timeout ? pusb_det_routine->timeout - 1 : 0;
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
    }
    else{
        if(USB_IN_DETECT_VBUS_PIN_ACTIVE==pusb_det_routine->Vbus_states){
            /* VBUS Active and ID=High*/
            pusb_det_routine->next_phase = USB_DETECT_PHASE_VBUS_ACTIVE;
            pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL; //USBH_WAIT_DEV_CONN_CHECK_INTERVAL*USBH_WAIT_DEV_CONN_TIMEOUT_CNT;
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
        else{
            /* USB_ID HIGH: NC or B Device */
            pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
            pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL;
            pusb_det_routine->timeout = pusb_det_routine->timeout ? pusb_det_routine->timeout - 1 : 0;
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
    }
}

void AHC_USB_Check_USBID_Custom_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;
    MMP_ERR sRet = MMP_ERR_NONE;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_OTG_SESSION:
            /* Enable PWR SW, VBus power to device */
            #ifdef USB_OUT_PWR_SW_PIN
            if (USB_OUT_PWR_SW_PIN != MMP_GPIO_MAX) {
                sRet = MMPS_PIO_SetData(USB_OUT_PWR_SW_PIN, USB_OUT_PWR_SW_PIN_ACTIVE);
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            }
            #endif
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_VBUS_ACTIVE:
            {
                MMP_UBYTE   i = 0x0, ubTimeOutLimit = 0x10; // 0x10->0x20 for some PC, USB RESET may delay arrived
                AHC_BOOL    ubAdapterConnect = AHC_TRUE;

                MMPF_SetUSBChangeMode(USB_DETECT_MODE);
                ubTimeOutLimit = 15;//35;
                for(i = 0x0; i < ubTimeOutLimit ; i++) {
                    if(!MMPF_USB_IsAdapter()) {
                        ubAdapterConnect = MMP_FALSE;
                        break;
                    }
                    AHC_OS_Sleep(100); //To lower the checking frequency, it can be adjusted !
                }

                if(i == ubTimeOutLimit){
                    sRet = MMPF_USB_StopDevice();
                    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
                }
                _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            }
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Check_USBID_Custom_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)
    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_OTG_SESSION:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_VBUS_ACTIVE:
            USB_Cable_In(1);
            AHC_DBG_MSG(1, "========== USB cable in. ========== \r\n");
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Check_Connect_Custom_Detect(void *ptype)
{
    MMP_BOOL    bStatus = MMP_TRUE;
    MMP_BOOL    bRearCamValid = AHC_FALSE;
    MMP_ERR sRet = MMP_ERR_NONE;

    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    sRet = MMPS_USB_GetDevConnSts(&bStatus);
    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet);}

    AHC_USBGetVBUSPinData(&pusb_det_routine->Vbus_states);

    bRearCamValid = ((MMP_TRUE == bStatus) && (USB_IN_DETECT_VBUS_PIN_ACTIVE == pusb_det_routine->Vbus_states)) ? AHC_TRUE : AHC_FALSE;

#if (UVC_HOST_VIDEO_ENABLE)
    {
        UINT32 ulUVCHostErrorType=0;
        AHC_HostUVCVideoReadErrorType(&ulUVCHostErrorType);
        if((ulUVCHostErrorType & UVC_HOST_ERROR_EP0_TIMEOUT) ||
            (ulUVCHostErrorType & UVC_HOST_ERROR_FRM_RX_LOST_TH_2) ||
            (ulUVCHostErrorType & UVC_HOST_ERROR_DISCONNECTED)){
            /* invalid. Connection is lost.*/
            bRearCamValid = AHC_FALSE;
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
        else if((ulUVCHostErrorType & UVC_HOST_ERROR_TRAN_TIMEOUT) ||
            (ulUVCHostErrorType & UVC_HOST_ERROR_FRM_RX_LOST) ||
            (ulUVCHostErrorType & UVC_HOST_ERROR_SEQ_NO_LOST)){
            //Force I
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
    }
#endif

    if(AHC_TRUE == bRearCamValid){
        /* valid rear cam */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_REAR_CAM;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL; //TBD
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
    else{
        switch(pusb_det_routine->cur_phase){
            case USB_DETECT_PHASE_CHECK_CONN:
                pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
                pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL; //TBD
                _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
                break;
            case USB_DETECT_PHASE_REAR_CAM:
                /*Go to USB_DETECT_PHASE_REAR_CAM_DISCONN states to check VBUS pin.*/
                pusb_det_routine->next_phase = USB_DETECT_PHASE_REAR_CAM_DISCONN;
                pusb_det_routine->timer_interval = 1500; //Wait until VBUS stable
                _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
                break;
            default:
                _AHC_USB_ASSERT
                break;
        }

        if(pusb_det_routine->cur_phase == USB_DETECT_PHASE_CHECK_CONN){
            pusb_det_routine->timeout = pusb_det_routine->timeout ? pusb_det_routine->timeout - 1 : 0;
        }
        else{
        }

        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
}

void AHC_USB_RearCam_Disconn_Custom_Detect(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
    pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL;
    pusb_det_routine->timeout = pusb_det_routine->timeout_init_val;
    _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
}

void AHC_USB_RearCam_Disconn_Custom_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_CHECK_VBUS:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_RearCam_Disconn_Custom_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    AHC_USBGetVBUSPinData(&pusb_det_routine->Vbus_states);

    if(USB_IN_DETECT_VBUS_PIN_ACTIVE == pusb_det_routine->Vbus_states){
        //NOP
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
    else{
        USB_Cable_In(0);
        AHC_DBG_MSG(1, "========== USB cable out. ========== \r\n");
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
}


#endif

void AHC_USB_OTG_Session_Detect(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_CONN;//USB_DETECT_PHASE_OTG_SESSION;
    pusb_det_routine->timer_interval = WAIT_CHECK_BDEVICE_CONN_INTERVAL;

    _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
}

void AHC_USB_OTG_Session_Exec(void *ptype)
{
#if (UVC_HOST_VIDEO_ENABLE)
    MMP_ERR sRet = MMP_ERR_NONE;
#endif
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)
#if (UVC_HOST_VIDEO_ENABLE)
    sRet = MMPS_USB_AdjustVref(gususbh_vref);
    sRet |= MMPS_USB_AdjustBiasCurrent(gususbh_bias_current);
    sRet |= MMPS_USB_AdjustSignal(gususbh_tx_cur, gususbh_tx_cur_plus, gususbh_sq_level);
    sRet |= MMPS_USB_StartOTGSession(0);
    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
#endif
    _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
}

void AHC_USB_OTG_Session_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    //NOP
    _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
}

void AHC_USB_Check_Connect_Detect(void *ptype)
{
    MMP_BOOL bStatus = MMP_TRUE;
    MMP_ERR sRet = MMP_ERR_NONE;

    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;
    static MMP_ULONG ulOTGDisconnectDelay = WAIT_CHECK_BDEVICE_DISCONN_DELAY_CNT;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    sRet = MMPS_USB_GetDevConnSts(&bStatus);
    if (sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }

    if (1 == pusb_det_routine->pause_detection) {

        pusb_det_routine->next_phase = pusb_det_routine->cur_phase;//USB_DETECT_PHASE_REAR_CAM;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL; //TBD
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
#if defined(__RTK_OS__)
    else if (MMP_TRUE == bStatus && uvcl_is_mdl_done())
#else
    else if (MMP_TRUE == bStatus)
#endif
    {

        /* valid rear cam */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_REAR_CAM;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL; //TBD

        #if (UVC_HOST_VIDEO_ENABLE)
        {
            UINT32 ulUVCHostErrorType=0;

            AHC_HostUVCVideoReadErrorType(&ulUVCHostErrorType);

            if((ulUVCHostErrorType & UVC_HOST_ERROR_EP0_TIMEOUT) ||
                (ulUVCHostErrorType & UVC_HOST_ERROR_FRM_RX_LOST_TH_2) ||
                (ulUVCHostErrorType & UVC_HOST_ERROR_DISCONNECTED)){
                /* invalid. Connection is lost.*/
                pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
                pusb_det_routine->timer_interval = WAIT_BDEVICE_SHUTDOWN_INTERVAL;
                AHC_DBG_ERR(1, "USBDetect Error=0x%x\n",ulUVCHostErrorType);
                _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            }
            else if((ulUVCHostErrorType & UVC_HOST_ERROR_TRAN_TIMEOUT) ||
                (ulUVCHostErrorType & UVC_HOST_ERROR_FRM_RX_LOST) ||
                (ulUVCHostErrorType & UVC_HOST_ERROR_SEQ_NO_LOST)){
                //Force I
                _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            }
        }
        #endif

        ulOTGDisconnectDelay = WAIT_CHECK_BDEVICE_DISCONN_DELAY_CNT;

        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
    else {

        #if 0//defined(__RTK_OS__)
        if(pusb_det_routine->cur_phase == USB_DETECT_PHASE_REAR_CAM){
            pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_CONN;
            pusb_det_routine->timer_interval = WAIT_CHECK_BDEVICE_CONN_INTERVAL;
            pusb_det_routine->timeout = 500; //TBD
            pusb_det_routine->Vbus_states = USB_IN_DETECT_VBUS_PIN_ACTIVE;
            pusb_det_routine->pause_detection = 0;
        }
        #else
        if (--ulOTGDisconnectDelay > 0) {
            //Wait until countdown to zero.
            pusb_det_routine->next_phase = pusb_det_routine->cur_phase;
            pusb_det_routine->timer_interval = WAIT_BDEVICE_DISCONN_INTERVAL;//WAIT_CHECK_BDEVICE_CONN_INTERVAL;//
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
        else {
            /* invalid / timeout.  Only OTG cable but no device connected.*/
            pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
            pusb_det_routine->timer_interval = WAIT_BDEVICE_SHUTDOWN_INTERVAL;
            ulOTGDisconnectDelay = WAIT_CHECK_BDEVICE_DISCONN_DELAY_CNT;

            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
        }
        #endif
    }
}

void AHC_USB_Check_Connect_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

#if (UVC_HOST_VIDEO_ENABLE)
    UINT32 ulUVCHostErrorType=0;
    AHC_BOOL ahcRet = AHC_TRUE;
#endif
    MMP_ERR sRet = MMP_ERR_NONE;
    MMP_BOOL bStatus = MMP_TRUE;
    sRet = MMPS_USB_GetDevConnSts(&bStatus);
    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

#if (UVC_HOST_VIDEO_ENABLE)
    AHC_HostUVCVideoReadErrorType(&ulUVCHostErrorType);
#endif

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_REAR_CAM:
            #if (UVC_HOST_VIDEO_ENABLE)
            if(gbUVCDeviceEnum == AHC_FALSE){
                AHC_HostUVCVideoClearError((UINT32)(-1)); //Cleare all error flag.
                ahcRet = AHC_HostUVC_EnumDevice(AHC_TRUE);

                if(ahcRet == AHC_TRUE){
                    gbUVCDeviceEnum = AHC_TRUE;
                }
                else{ //Enum fail.
                    pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
                    pusb_det_routine->timer_interval = WAIT_BDEVICE_SHUTDOWN_INTERVAL;

                    //Disable rear cam power.
                    #ifdef USB_OUT_PWR_SW_PIN
                    if (USB_OUT_PWR_SW_PIN != MMP_GPIO_MAX){
                        sRet = MMPS_PIO_SetData(USB_OUT_PWR_SW_PIN, (!USB_OUT_PWR_SW_PIN_ACTIVE) & 0x01);
                        if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
                    }
                    #endif

                    AHC_DBG_MSG(1, "Enum fail\r\n");
                }
            }
            else{
                if((ulUVCHostErrorType & UVC_HOST_ERROR_TRAN_TIMEOUT) ||
                    (ulUVCHostErrorType & UVC_HOST_ERROR_FRM_RX_LOST) ||
                    (ulUVCHostErrorType & UVC_HOST_ERROR_SEQ_NO_LOST)){
                    //Force I
                    ahcRet = AHC_HostUVC_ForceIFrame();
                    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }

                    //Clear error flag
                    AHC_HostUVCVideoClearError(UVC_HOST_ERROR_TRAN_TIMEOUT | UVC_HOST_ERROR_FRM_RX_LOST | UVC_HOST_ERROR_SEQ_NO_LOST);
                    _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
                }
            }
            #endif
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
            #ifdef USB_OUT_PWR_SW_PIN
            if (USB_OUT_PWR_SW_PIN != MMP_GPIO_MAX){
                sRet = MMPS_PIO_SetData(USB_OUT_PWR_SW_PIN, (!USB_OUT_PWR_SW_PIN_ACTIVE) & 0x01);
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            }
            #endif
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
#if defined (__RTK_OS__)
        case USB_DETECT_PHASE_CHECK_CONN:

#else
        case USB_DETECT_PHASE_CHECK_CONN:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
#endif

#if USB_DETECTION_CUSTOM
        case USB_DETECT_PHASE_REAR_CAM_DISCONN:
#endif
            gbUVCDeviceEnum = AHC_FALSE;

            #if (UVC_HOST_VIDEO_ENABLE)
            ahcRet = AHC_HostUVC_EnumDevice(AHC_FALSE);
            if(ahcRet == AHC_FALSE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); }

            if((ulUVCHostErrorType & UVC_HOST_ERROR_EP0_TIMEOUT) ||
               (ulUVCHostErrorType & UVC_HOST_ERROR_FRM_RX_LOST_TH_2) ||
               (ulUVCHostErrorType & UVC_HOST_ERROR_DISCONNECTED)){
                //EP0 timeout happens only in idle states.
                /* forced to clear connect status because of disconnected, not from USB_OTG_ISR (PHY) */
                sRet = MMPS_USB_SetDevConnSts(MMP_FALSE);
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }

                /* reset USB */
                sRet = MMPS_USB_DisconnectDevice();
                if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
            }
            AHC_HostUVCVideoClearError((UINT32)(-1)); //Cleare all error flag.
            #endif
            //Disable rear cam power.
            if(!bStatus) {
                #ifdef USB_OUT_PWR_SW_PIN
                if (USB_OUT_PWR_SW_PIN != MMP_GPIO_MAX){
                    sRet = MMPS_PIO_SetData(USB_OUT_PWR_SW_PIN, (!USB_OUT_PWR_SW_PIN_ACTIVE) & 0x01);
                    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); }
                }
                #endif
            }


            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;

        default:
            gbUVCDeviceEnum = AHC_FALSE;
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Check_Connect_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_REAR_CAM:
            //TBD
            //Rear cam plugs in.
            USB_BDevice_In(1);
            AHC_DBG_MSG(1, "========== Rearcam in. ========== \r\n");
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
#if USB_DETECTION_CUSTOM
        case USB_DETECT_PHASE_REAR_CAM_DISCONN:
#endif
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            //NOP
            break;
        case USB_DETECT_PHASE_CHECK_CONN:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_VBUS_Active_Detect(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    AHC_USBGetVBUSPinData(&pusb_det_routine->Vbus_states);

    if(USB_IN_DETECT_VBUS_PIN_ACTIVE==pusb_det_routine->Vbus_states){
        /* VBUS active */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_VBUS_ACTIVE;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL; //TBD
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
    else{
        /* VBUS inactive */
        pusb_det_routine->next_phase = USB_DETECT_PHASE_CHECK_VBUS;
        pusb_det_routine->timer_interval = POLLING_VBUS_INTERVAL;
        _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
    }
}

void AHC_USB_VBUS_Active_Exec(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_VBUS_ACTIVE:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
            //MMPS_USB_TriggerReadUSBID(0);
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_VBUS_Active_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_VBUS_ACTIVE:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
            //SetKeyPadEvent(USB_CABLE_OUT); //TBD
            USB_Cable_In(0);
            AHC_DBG_MSG(1, "========== USB cable out. ========== \r\n");
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_Rearcam_Notify(void *ptype)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    switch(pusb_det_routine->next_phase){
        case USB_DETECT_PHASE_REAR_CAM:
            //NOP
            _AHC_USB_PRINTC("%s,%d\r\n", __FUNCTION__, __LINE__);
            break;
        case USB_DETECT_PHASE_CHECK_VBUS:
#if defined(__RTK_OS__)
        case USB_DETECT_PHASE_CHECK_CONN:
#endif
#if USB_DETECTION_CUSTOM
        case USB_DETECT_PHASE_REAR_CAM_DISCONN:
#endif
            //To do here.
            //Rear cam plugs out.
            USB_BDevice_In(0);
            AHC_HostUVC_EnumDevice(AHC_FALSE);
            gbUVCDeviceEnum = AHC_FALSE;

            AHC_DBG_MSG(1, "========== RearCam Out ==========\r\n");
            break;
        default:
            _AHC_USB_ASSERT
            break;
    }
}

void AHC_USB_SubRoutine(void *ptype, void *ptmr, void *parg, UINT8 stage)
{
    struct USB_DETECT_TYPE *pdet_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pdet_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    if(stage == 0){
        pusb_det_routine->pCallback = ptmr;
        pusb_det_routine->pCallbackArg = parg;
    }
    pusb_det_routine->usb_routine((void *)pusb_det_routine, stage);
}

UINT32 AHC_USBGetTypeNum(void)
{
    return sizeof(_usb_det_type) / sizeof(struct USB_DETECT_TYPE);
}

void *AHC_USBGetCurTypeObj(UINT16 type_num)
{
    struct USB_DETECT_TYPE *pusb_det_type;

    pusb_det_type = (struct USB_DETECT_TYPE *)(&_usb_det_type);
    return (void *)(pusb_det_type + type_num);
}

UINT16 AHC_USBGetCurTypePhase(void *pdet_type)
{
    struct USB_DETECT_TYPE *pusb_det_type = (struct USB_DETECT_TYPE *)pdet_type;

    _AHC_USB_CHECK_POINTER_VALID(pusb_det_type)
    return pusb_det_type->usb_phase;
}

void AHC_USBRoutine(void *ptype, void *ptmr, void *parg, UINT8 stage)
{
    struct USB_DETECT_TYPE *pusb_det_type = (struct USB_DETECT_TYPE *)ptype;

    _AHC_USB_CHECK_POINTER_VALID(pusb_det_type)
    pusb_det_type->routine_func((void *)pusb_det_type, ptmr, parg, stage);
}

void AHC_USB_Do(void *ptype)
{
    struct USB_DETECT_TYPE *pusb_det_type = (struct USB_DETECT_TYPE *)ptype;

    _AHC_USB_CHECK_POINTER_VALID(pusb_det_type)

    pusb_det_type->detect_func((void *)pusb_det_type);
    if(pusb_det_type->exec_func){
        pusb_det_type->exec_func((void *)pusb_det_type);
    }
    if(pusb_det_type->notify_func){
        pusb_det_type->notify_func((void *)pusb_det_type);
    }
}

void AHC_USBSetPhase(void *ptype, UINT16 phase)
{
    struct USB_DETECT_TYPE *pusb_det_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pusb_det_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    pusb_det_routine->cur_phase = (USB_DETECT_PHASE)phase;
}

UINT16 AHC_USBGetPhase(void *ptype, UINT8 cur_or_next)
{
    struct USB_DETECT_TYPE *pusb_det_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pusb_det_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    if(AHC_USB_GET_PHASE_NEXT==cur_or_next){ // 1: next
        return (UINT16)pusb_det_routine->next_phase;
    }

    // 0: current
    return (UINT16)pusb_det_routine->cur_phase;
}

UINT8 AHC_USBGetVBUS(void *ptype)
{
    struct USB_DETECT_TYPE *pusb_det_type = (struct USB_DETECT_TYPE *)ptype;
    struct USB_DETECT_ROUTINE *pusb_det_routine;

    pusb_det_routine = (struct USB_DETECT_ROUTINE *)pusb_det_type->usb_detect_routine;
    _AHC_USB_CHECK_POINTER_VALID(pusb_det_routine)

    return pusb_det_routine->Vbus_states;
}

void AHC_USBDetectSetPriority(AHC_BOOL bHighPriority)
{
    gbAHC_USBDetectionHighPriority = bHighPriority;
}

void AHC_StartUSBDetect(void)
{
    extern MMPF_OS_MQID         MidTaskWork_QId;
    extern MMPF_OS_MQID         HighTaskWork_QId;

    if (AHC_TRUE == gbAHC_USBDetectionHighPriority) {
        MMPF_OS_PutMessage(HighTaskWork_QId, (void *)(&AHC_USBDetectHandler));
    }
    else {
        MMPF_OS_PutMessage(MidTaskWork_QId, (void *)(&AHC_USBDetectHandler));
    }
}

void AHC_USBDetectTimerCB(void *ptmr, void *parg)
{
    extern MMPF_OS_MQID         MidTaskWork_QId;
    extern MMPF_OS_MQID         HighTaskWork_QId;

    if (AHC_TRUE == gbAHC_USBDetectionHighPriority) {
        MMPF_OS_PutMessage(HighTaskWork_QId, (void *)(&AHC_USBDetectHandler));
    }
    else {
        MMPF_OS_PutMessage(MidTaskWork_QId, (void *)(&AHC_USBDetectHandler));
    }
}

void AHC_USBDetectHandler(void)
{
    UINT32 loop = 0, total_num = 0;
    UINT16 cur_phase = 0;
    void *pusb_obj = NULL;

    if (bUsbForcePCAM == AHC_TRUE) {
        return;
    }

#if (UVC_HOST_VIDEO_ENABLE)
    {
        // Only once after power-on
        static AHC_BOOL isFirstSetting = AHC_TRUE;

        if (isFirstSetting) {
            MMP_ERR sRet = MMP_ERR_NONE;

            isFirstSetting = AHC_FALSE;

            sRet = MMPS_USB_SetCheckDevAliveCFG(CHECK_EP0_TIMEOUT_INTERVAL,(void *)AHC_HostUVCVideoSetEp0TimeoutCB);
            if(sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); /*return;*/}
            sRet = MMPS_USB_SetTranTimeoutCFG(CHECK_TRAN_TIMEOUT_INTERVAL, (void *)AHC_HostUVCVideoSetTranTimeoutCB);
            if(sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); /*return;*/}
            sRet = MMPS_USB_SetFrmRxTimeoutCFG(CHECK_FRM_RX_LOST_TH, CHECK_FRM_RX_FIRST_ADD_GAP, (void *)AHC_HostUVCVideoSetFrmRxTimeoutCB);
            if(sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); /*return;*/}
            sRet = MMPS_USB_SetFrmRxTimeout2CFG(CHECK_FRM_RX_LOST_TH_2,    (void *)AHC_HostUVCVideoSetFrmRxTimeout2CB);
            if(sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); /*return;*/}
            sRet = MMPS_USB_SetFrmSeqNoLostCFG(CHECK_FRM_SEQ_NO_LOST_TH,   (void *)AHC_HostUVCVideoSetFrmSeqNoLostCB);
            if(sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); /*return;*/}
            sRet = MMPS_USB_SetDropRxFrmCFG(CHECK_FRM_RX_DROP_TOTAL_CNT, CHECK_FRM_RX_DROP_CONTI_CNT, (void *)AHC_HostUVCVideoSetFrmRxDropCB);
            if(sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); /*return;*/}
            sRet = MMPS_USB_RegDetectCallBack(NULL, NULL, NULL, (void *)AHC_HostUVCVideoDevDisconnectedCB);
            if(sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); /*return;*/}
        }
    }
#endif

    total_num = AHC_USBGetTypeNum();

    for (loop = 0; loop < total_num; ++loop) {

        pusb_obj = AHC_USBGetCurTypeObj(loop);
        cur_phase = AHC_USBGetPhase(pusb_obj, AHC_USB_GET_PHASE_CURRENT);//USB_DETECT_PHASE_INIT
        //AHC_DBG_MSG(1, "%s,%d, usb_phase=%d,cur_phase=%d\r\n", __FUNCTION__, __LINE__, ((struct USB_DETECT_TYPE *)pusb_obj)->usb_phase,cur_phase);

        if (cur_phase == AHC_USBGetCurTypePhase(pusb_obj)) {
            AHC_USBRoutine(pusb_obj, (void *)&AHC_USBDetectTimerCB, NULL, 0);
            AHC_USB_Do(pusb_obj);
            AHC_USBSetPhase(pusb_obj, AHC_USBGetPhase(pusb_obj, AHC_USB_GET_PHASE_NEXT));
            AHC_USBRoutine(pusb_obj, NULL, NULL, 1);
            break;
        }
    }
}
