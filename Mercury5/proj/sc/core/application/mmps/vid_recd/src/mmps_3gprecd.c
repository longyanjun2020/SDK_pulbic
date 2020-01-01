/**
 @file mmps_3gprecd.c
 @brief 3GP Recorder Control Function
 @author Will Tseng
 @version 1.0
*/

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "os_wrap.h"
#if (SUPPORT_ADAS) || (SUPPORT_MDTC)
#include "ldws_cfg.h"
#include "mdtc_cfg.h"
#endif
#include "snr_cfg.h"
#include "ptz_cfg.h"
#include "usb_cfg.h"
#include "mmp_display_inc.h"
#include "mmp_icon_inc.h"
#include "mmp_vidrec_inc.h"
#include "mmp_dsc_inc.h"
#include "mmps_iva.h"
#include "mmps_fs.h"
#include "mmps_3gprecd.h"
#include "mmps_dsc.h"
#include "mmps_sensor.h"
#include "mmps_audio.h"
#include "mmpd_fctl.h"
#include "mmpd_ptz.h"
#include "mmpd_3gpmgr.h"
#include "mmpd_uvcrecd.h"
#include "mmph_hif.h"
#include "mmpf_sensor.h"
#include "mmpf_mp4venc.h"
#include "mmpf_h264enc.h"
#include "mmpf_3gpmgr.h"
#include "mmpf_avimux.h"
#if (MTS_MUXER_EN)
#include "mmpf_mts.h"
#endif
#include "mmpf_vr_thumb.h"
#include "mmpf_usbh_ctl.h"
#include "mmpf_jpeg_enc_rc.h"

#include "component_cfg.h"
#include "component_mfe.h"
#include "component_mgr.h"
#include "component_jpe.h"
#include "component_scl.h"
#include "component_dip.h"
#include "component_pip.h"
#include "component_jpd.h"
#include "component_raws.h"
#include "component_display.h"
#include "component_uvc.h"
#include "cust_component_cfg.h"
#include "pCam_api.h"

/** @addtogroup MMPS_3GPRECD
@{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MMPS_VR_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMPS_VR_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define MAX_3GPRECD_FILENAME_LENGTH     (256)

#define VID_ENC_SPS_BUF_SIZE            (48)
#define VID_ENC_PPS_BUF_SIZE            (16)

#define VID_ENC_COMP_BUF_DURATION       (5) // Sec

#define VID_MGR_AUX_SIZE_TBL_BUF_SZ     (1024)
#define VID_MGR_AUX_TIME_TBL_BUF_SZ     (1024)

#define VID_MGR_REPACK_BUF_SIZE         (512 * 1024)
#define VID_MGR_REPACK_BUF_SIZE_EMERG   (512 * 1024 * 2)

#define FS_CLEAR_CACHE_PERIOD           (3000) // unit: millisec; force fs clear cache

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

// Video encode configuration
static MMPS_3GPRECD_RUNTIME_CFG m_VidRecdRuntimeCfg = {
    0,                          // usVideoPreviewMode
    {0, 0, 0},                  // usVideoEncResIdx
    {{0, 0},{0, 0},{0, 0}},     // SnrFrameRate
    {{0, 0},{0, 0},{0, 0}},     // EncFrameRate
    {{0, 0},{0, 0},{0, 0}},     // MgrFrameRate
    {0, 0, 0},                  // usPFrameCount
    {0, 0, 0},                  // usBFrameCount
    {0, 0, 0},                  // ulBitrate
    0,                          // ulAudBitrate
    0xFFFFFFFF,                 // ulSizeLimit
    0xFFFFFFFF,                 // ulTimeLimitMs
    0,                          // ulReservedSpace
    {VIDENC_OUT_MODE_CARD, VIDENC_OUT_MODE_CARD, VIDENC_OUT_MODE_CARD}, // eVideoOutMode
    {H264ENC_HIGH_PROFILE, H264ENC_HIGH_PROFILE, H264ENC_HIGH_PROFILE}, // eVisualProfile
    MMP_FALSE,                  // bSlowMotionEn
    {VID_ENC_COMP_BUF_DURATION, VID_ENC_COMP_BUF_DURATION, VID_ENC_COMP_BUF_DURATION}, // ulMaxCompBufDuration
};

static MMPS_3GPRECD_PRESET_CFG  m_VidRecdPresetCfg;
static MMPS_3GPRECD_AUDIO_FORMAT m_eVidRecdAudioFmt = MMPS_3GPRECD_AUDIO_FORMAT_ADPCM;

// Video context handle
MMP_ULONG                       m_ulPrmRecdID = INVALID_ENC_ID;
static MMP_ULONG                m_ulScdRecdID = INVALID_ENC_ID;
static MMP_ULONG                m_ulTrdRecdID = INVALID_ENC_ID;

#if (SUPPORT_H264_WIFI_STREAM)
static MMP_H264_STREAM_OBJ      m_stH264StreamObj[VR_MAX_H264_STREAM_NUM];
static MMP_ULONG                m_ulH264PrmStreamID = INVALID_ENC_ID;
static MMP_ULONG                m_ulH264ScdStreamID = INVALID_ENC_ID;
#endif

// Status of video preview/Encode
static MMP_BOOL                 m_bVidPreviewActive[VR_MAX_PREVIEW_NUM] = {MMP_FALSE, MMP_FALSE};
static MMP_BOOL                 m_bVidRecordActive[VR_MAX_ENCODE_NUM]   = {MMP_FALSE, MMP_FALSE, MMP_FALSE};
#if (SUPPORT_H264_WIFI_STREAM)
static MMP_BOOL                 m_bH264StreamActive[VR_MAX_H264_STREAM_NUM] = {MMP_FALSE, MMP_FALSE};
#endif

static MMP_ULONG                m_ulCurVidEncID[VR_MAX_ENCODE_NUM] = {INVALID_ENC_ID, INVALID_ENC_ID, INVALID_ENC_ID};
static MMP_UBYTE                m_ubTotalVidEncCnt = 0;

// Parameters of preview/record zoom
static MMPS_DSC_ZOOM_INFO       m_VidPreviewZoomInfo;
static MMPS_DSC_ZOOM_INFO       m_VidRecordZoomInfo;
static MMP_USHORT               m_usVidStaticZoomIndex = 0;
static MMP_UBYTE                m_PreviewPipe = 3; // TBD

// AHC parameters
static MMPS_3GPRECD_AHC_PREVIEW_INFO    m_stAhcVideoPrevInfo[VR_MAX_PREVIEW_NUM] = {{0},{0}};
static MMPS_3GPRECD_AHC_VIDEO_INFO      m_stAhcH264RecdInfo[VR_MAX_ENCODE_NUM] = {{0},{0},{0}};
#if (SUPPORT_H264_WIFI_STREAM)
static MMPS_3GPRECD_AHC_VIDEO_INFO      m_stAhcH264StreamInfo[VR_MAX_H264_STREAM_NUM] = {{0},{0}};
#endif

static MMP_BOOL                 m_bAhcConfigVideoRZoom = MMP_FALSE;

// Misc parameters
#if (SUPPORT_MDTC)||(SUPPORT_ADAS)
static MMPS_3GPRECD_Y_FRAME_TYPE m_eYFrameType = MMPS_3GPRECD_Y_FRAME_TYPE_NONE;
#endif

MMP_3GPRECD_EMERG_ACTION        m_eEmergActionType = MMP_3GPRECD_EMERG_DEFAULT_ACT;

static MMP_BOOL                 m_bStickerEnable[MMP_STICKER_ID_NUM] = {MMP_FALSE, MMP_FALSE};

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern MMP_BOOL     m_bUVCRecdSupport;


//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPS_3GPRECD_StopAllPipeZoom(void);
static MMP_ERR MMPS_3GPRECD_InitDigitalZoomParam(MMP_UBYTE ubPipe);
static MMP_ERR MMPS_3GPRECD_RestoreDigitalZoomRange(MMP_UBYTE ubPipe);

static MMP_ERR MMPS_3GPRECD_GetMaxFileSizeTimeLimit(MMP_ULONG64 *pu64MaxSizeLimit, MMP_ULONG64 *pu64MaxTimeLimit);
static MMP_ULONG MMPS_3GPRECD_GetContainerTailBufSize(MMP_UBYTE ubRecdSel);
MMP_ERR MMPS_3GPRECD_StopAllRecord(void);
void usb_uvc_mdtc_tx( void );

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____VR_Common_Config_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetPresetCfg
//  Description :
//------------------------------------------------------------------------------
MMPS_3GPRECD_PRESET_CFG* MMPS_3GPRECD_GetPresetCfg(void)
{
    return (&m_VidRecdPresetCfg);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetRuntimeCfg
//  Description :
//------------------------------------------------------------------------------
MMPS_3GPRECD_RUNTIME_CFG* MMPS_3GPRECD_GetRuntimeCfg(void)
{
    return (&m_VidRecdRuntimeCfg);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_ChkPrmRecdEnabled
//  Description :
//------------------------------------------------------------------------------
static MMP_UBYTE MMPS_3GPRECD_ChkPrmRecdEnabled(void)
{
    switch(CAM_GET_PRM)
    {
    case PRM_CAM_BAYER_SENSOR:
    case PRM_CAM_ANA_DECODER:
    case PRM_CAM_YUV_SENSOR:
        return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
        break;
    default:
        return VID_RECD_DISABLE;
        break;
    }

    return VID_RECD_DISABLE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_ChkScdRecdEnabled
//  Description :
//------------------------------------------------------------------------------
static MMP_UBYTE MMPS_3GPRECD_ChkScdRecdEnabled(void)
{
    if (MMPS_3GPRECD_IsShareRecordEn()) {
        return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
    }

    switch(CAM_GET_SCD)
    {
    case SCD_CAM_BAYER_SENSOR:
    case SCD_CAM_ANA_DECODER:
    case SCD_CAM_YUV_SENSOR:
        return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
        break;
    default:
        return VID_RECD_DISABLE;
        break;
    }

    return VID_RECD_DISABLE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_ChkTrdRecdEnabled
//  Description :
//------------------------------------------------------------------------------
static MMP_UBYTE MMPS_3GPRECD_ChkTrdRecdEnabled(void)
{
    switch(CAM_GET_TRD)
    {
    case TRD_CAM_BAYER_SENSOR:
    case TRD_CAM_ANA_DECODER:
    case TRD_CAM_YUV_SENSOR:
        return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
    break;
    default:
        return VID_RECD_DISABLE;
        break;
    }

    return VID_RECD_DISABLE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_ChkUsbhRecdEnabled
//  Description :
//------------------------------------------------------------------------------
static MMP_UBYTE MMPS_3GPRECD_ChkUsbhRecdEnabled(void)
{
    switch(CAM_GET_USB)
    {
    case USB_CAM_AIT:
        return VID_RECD_STORE_FILE;
        break;
    case USB_CAM_SONIX_MJPEG:
        return VID_RECD_STORE_FILE;
        break;
    case USB_CAM_SONIX_MJPEG2H264:
        return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
        break;
    default:
        break;
    }

    return VID_RECD_DISABLE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetTotalRecdEnabledCnt
//  Description :
//------------------------------------------------------------------------------
static MMP_UBYTE MMPS_3GPRECD_GetTotalRecdEnabledCnt(void)
{
    MMP_UBYTE ubCnt = 0;

    if (MMPS_3GPRECD_ChkPrmRecdEnabled() & VID_RECD_ENCODE_H264) {
        ubCnt++;
    }
    if (MMPS_3GPRECD_ChkScdRecdEnabled() & VID_RECD_ENCODE_H264) {
        ubCnt++;
    }
    if (MMPS_3GPRECD_ChkTrdRecdEnabled() & VID_RECD_ENCODE_H264) {
        ubCnt++;
    }
    if (MMPS_3GPRECD_ChkUsbhRecdEnabled() & VID_RECD_ENCODE_H264) {
        ubCnt++;
    }

    return ubCnt;
}

#if 0
void ____VR_Common_Preview_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_CustomedPreviewAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set video preview resolution.
 @param[in] bUserConfig     Use user defined preview configuration.
 @param[in] bMirror         Use DIP scale to mirror preview buffer.
 @param[in] ubRotateDir     DMA rotate direction.
 @param[in] sFitMode        Scaler fit mode.
 @param[in] usBufWidth      Preview buffer width.
 @param[in] usBufHeight     Preview buffer height.
 @param[in] usStartX        The X Offset of the display window.
 @param[in] usStartY        The Y Offset of the display window.
 @param[in] usWinWidth      The width of the display window.
 @param[in] usWinHeight     The height of the display window.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_CustomedPreviewAttr(MMP_UBYTE  ubCamSel,
                                         MMP_BOOL   bUserConfig,
                                         MMP_BOOL   bMirror,
                                         MMP_UBYTE  sFitMode,
                                         MMP_USHORT usBufWidth, MMP_USHORT usBufHeight,
                                         MMP_USHORT usStartX,   MMP_USHORT usStartY,
                                         MMP_USHORT usWinWidth, MMP_USHORT usWinHeight)
{
    m_stAhcVideoPrevInfo[ubCamSel].bPreviewMirror    = bMirror;
    m_stAhcVideoPrevInfo[ubCamSel].sFitMode          = sFitMode;
    m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufW     = usBufWidth;
    m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufH     = usBufHeight;
    m_stAhcVideoPrevInfo[ubCamSel].ulDispStartX      = usStartX;
    m_stAhcVideoPrevInfo[ubCamSel].ulDispStartY      = usStartY;
    m_stAhcVideoPrevInfo[ubCamSel].ulDispWidth       = usWinWidth;
    m_stAhcVideoPrevInfo[ubCamSel].ulDispHeight      = usWinHeight;

    MMPS_VR_DBG_MSG(0, "CustomedPreviewAttr Cam[%d] PreW[%d] PreH[%d] WinW[%d] WinH[%d]\r\n",
                    ubCamSel, usBufWidth, usBufHeight, usWinWidth, usWinHeight);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetPreviewMirror
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetPreviewMirror(MMP_UBYTE ubCamSel, MMP_BOOL *pbMirror)
{
    if (pbMirror) {
        *pbMirror = m_stAhcVideoPrevInfo[ubCamSel].bPreviewMirror;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetPreviewPipeWH
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetPreviewPipeWH(MMP_UBYTE ubCamSel, MMP_ULONG *pulAlignPrevW, MMP_ULONG *pulAlignPrevH)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (pulAlignPrevW == NULL || pulAlignPrevH == NULL) {
        return eRetErr;
    }

    *pulAlignPrevW = m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufW;
    *pulAlignPrevH = m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufH;

    if (gbLCDRotate) {
        if (DIP_R_COMP_ALIGN_CHECK(m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufW)) {
            *pulAlignPrevW = ALIGN_X(m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufW, DIP_R_COMP_ALIGN_BASE);
        }
        if (DIP_R_COMP_ALIGN_CHECK(m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufH)) {
            *pulAlignPrevH = ALIGN_X(m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufH, DIP_R_COMP_ALIGN_BASE);
        }
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetDisplayRes
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetDisplayRes(MMP_UBYTE ubCamSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight)
{
    if (pulWidth)
        *pulWidth   = m_stAhcVideoPrevInfo[ubCamSel].ulDispWidth;
    if (pulHeight)
        *pulHeight  = m_stAhcVideoPrevInfo[ubCamSel].ulDispHeight;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetDisplayPosition
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetDisplayPosition(MMP_UBYTE ubCamSel, MMP_ULONG *pulPosStartX, MMP_ULONG *pulPosStartY)
{
    if (pulPosStartX)
        *pulPosStartX = m_stAhcVideoPrevInfo[ubCamSel].ulDispStartX;
    if (pulPosStartY)
        *pulPosStartY = m_stAhcVideoPrevInfo[ubCamSel].ulDispStartY;

    return MMP_ERR_NONE;
}




//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetPreviewPipeStatus
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Return in video preview status or not.
 @param[out] bEnable preview enable.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetPreviewPipeStatus(MMP_UBYTE ubCamSel, MMP_BOOL *pbEnable)
{
    if (pbEnable) {
        *pbEnable = m_bVidPreviewActive[ubCamSel];
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnablePreviewPipe
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Turn on and off preview for video encode.

 @param[in] bEnable             Enable and disable scaler path for video preview.
 @param[in] bCheckFrameEnd      When "bEnable" is MMP_TRUE, the setting means check frame end or not.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_EnablePreviewPipe(MMP_UBYTE ubCamSel, MMP_BOOL bEnable, MMP_BOOL bCheckFrameEnd)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (!(bEnable ^ m_bVidPreviewActive[ubCamSel])) {
        return MMP_ERR_NONE;
    }

    if (bEnable) {
        eRetErr = MMPD_Fctl_EnablePreview(ubCamSel, bEnable, bCheckFrameEnd);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "EnablePreviewPipe Fail\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }
    }
    else
    {
        eRetErr = MMPD_Fctl_EnablePreview(ubCamSel, bEnable, MMP_TRUE);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "DisablePreviewPipe Fail\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }

        // Disable video encode timer
        if (ubCamSel == PRM_SENSOR) {
            eRetErr |= MMPF_VIDENC_EnableTimer(MMP_FALSE);
            if (eRetErr != MMP_ERR_NONE) {
                MMPS_VR_DBG_ERR(1, "Disable Encode Timer Fail\r\n");
                return eRetErr;
            }

            m_usVidStaticZoomIndex = 0;
        }
    }

    m_bVidPreviewActive[ubCamSel] = bEnable;

    return MMP_ERR_NONE;
}

#if 0
void ____VR_1st_Preview_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_CheckPrmPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_CheckPrmPipe(MMP_UBYTE ubCamSel)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if ((ubCamSel == PRM_SENSOR) &&
        (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR) ||
         CAM_CHECK_PRM(PRM_CAM_ANA_DECODER))) {
    }
    else {
        eRetErr = MMP_HIF_ERR_PARAMETER;
        return eRetErr;
    }

    if (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR)) {
        if (m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW < m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufW) {
            MMPS_VR_DBG_ERR(1, "VR Cam%d EncW [%d] < PrevW [%d]\r\n",
                            ubCamSel,
                            m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW,
                            m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufW);
            eRetErr = MMP_HIF_ERR_PARAMETER;
            return eRetErr;
        }

        if (m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH < m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufH) {
            MMPS_VR_DBG_ERR(1, "VR Cam%d EncH [%d] < PrevH [%d]\r\n",
                            ubCamSel,
                            m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                            m_stAhcVideoPrevInfo[ubCamSel].ulPreviewBufH);
            eRetErr = MMP_HIF_ERR_PARAMETER;
            return eRetErr;
        }
    }
    else if (CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) {
        // TBD
        MMPS_VR_DBG_MSG(1, "TODO:%s,line#%d\r\n",__FUNCTION__, __LINE__);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustPrmADASPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AdjustPrmADASPipe(MMP_UBYTE ubCamSel)
{
#if (SUPPORT_ADAS) || (SUPPORT_MDTC)
    DIP_COMP_RECT   stDipRect;
    MMP_ULONG       ulAlignPrevW = 0, ulAlignPrevH = 0;
    MMP_ERR         eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_3GPRECD_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);

    stDipRect.ulX = 0;
    stDipRect.ulY = 0;
    stDipRect.ulW = MDTC_WIDTH;
    stDipRect.ulH = MDTC_HEIGHT;

    if (m_eYFrameType == MMPS_3GPRECD_Y_FRAME_TYPE_ADAS) {
        stDipRect.ulW = LDWS_WIDTH;
        stDipRect.ulH = LDWS_HEIGHT;
    }
    else if (m_eYFrameType == MMPS_3GPRECD_Y_FRAME_TYPE_VMD) {
        stDipRect.ulW = MDTC_WIDTH;
        stDipRect.ulH = MDTC_HEIGHT;
    }

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_VR_FCAM_ADAS,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        DIP_COMP_PREVW_BUF_COUNT);

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set DIP Comp [%d] Error!\r\n", DIP_S_COMP_VR_FCAM_ADAS);
    }

    return eRetErr;
#else
    return MMP_ERR_NONE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustPrmBayerRecdPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AdjustPrmBayerRecdPipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulScaleInW = 0, ulScaleInH = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);

    eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL0,
                                        SCL0_COMP_PRM_CAM,
                                        1, 1, ulScaleInW, ulScaleInH,
                                        1, 1, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                                        SCL_COMP_RECORD_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set SCL0 Comp Error!\r\n");
    }

    return eRetErr;
}

static MMP_ERR MMPS_3GPRECD_AdjustPrmANADecRecd_Raw1(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulScaleInW = 0, ulScaleInH = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDipBufCnt = 2;

    //MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);
    MMPS_VR_DBG_MSG(1, FG_RED("TODO:%s,line#%d,Need to adjust dip input W&H \r\n"),__FUNCTION__, __LINE__);

    eRetErr = MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC,
                                        0, 0, 1280, 720,
                                        0, 0, 1280, 720,
                                        0, 0, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                                        DIP_COMP_COLOR_FMT_YUV422_UYVY,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        0,
                                        0,
                                        ubDipBufCnt);

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set DIP_S14 Comp Error!\r\n");
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustPrmBayerPrevwPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AdjustPrmBayerPrevwPipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulAlignPrevW = 0, ulAlignPrevH = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_3GPRECD_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);

    eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL1,
                                        SCL1_COMP_PRM_CAM,
                                        1, 1, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                                        1, 1, ulAlignPrevW, ulAlignPrevH,
                                        SCL_COMP_PREVW_BUF_COUNT);

    if (MMP_GetScdCamType() == SCD_CAM_BAYER_SENSOR) {
        eRetErr |= MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL1,
                                             SCL1_COMP_SCD_CAM,
                                             1, 1, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                                             1, 1, ulAlignPrevW, ulAlignPrevH,
                                             SCL_COMP_PREVW_BUF_COUNT);
    }

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set SCL1 Comp Error!\r\n");
        return eRetErr;
    }

    eRetErr = MMPS_Display_SetPrmPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_VR,
                                                 MMPS_DISPLAY_PREVIEW_FULL_SCREEN);
    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set PrmBayerPrevwPipe Error!\r\n");
        return eRetErr;
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustPrmShareRecdPipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AdjustPrmShareRecdPipe(void)
{
    DIP_COMP_RECT   stInDipRect, stOutDipRect;
    MMP_ERR         eRetErr = MMP_ERR_NONE;
    MMP_UBYTE       ubPrmRecdId = MMPS_VR_PRM_RECD;
    MMP_UBYTE       ubScdRecdId = MMPS_VR_SCD_RECD;

    stInDipRect.ulX = 0;
    stInDipRect.ulY = 0;
    stInDipRect.ulW = m_stAhcH264RecdInfo[ubPrmRecdId].ulVidEncBufW; // SCL0 OutW
    stInDipRect.ulH = m_stAhcH264RecdInfo[ubPrmRecdId].ulVidEncBufH; // SCL0 OutH

    stOutDipRect.ulX = 0;
    stOutDipRect.ulY = 0;
    stOutDipRect.ulW = m_stAhcH264RecdInfo[ubScdRecdId].ulVidEncBufW;
    stOutDipRect.ulH = m_stAhcH264RecdInfo[ubScdRecdId].ulVidEncBufH;

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_VR_SHARE_RECD,
                                        stInDipRect.ulX, stInDipRect.ulY, stInDipRect.ulW, stInDipRect.ulH,
                                        stInDipRect.ulX, stInDipRect.ulY, stInDipRect.ulW, stInDipRect.ulH,
                                        stOutDipRect.ulX, stOutDipRect.ulY, stOutDipRect.ulW, stOutDipRect.ulH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_MIRROR_DIS,
                                        MFE_SHARE_BUF_LINE_BIAS,
                                        DIP_COMP_RECORD_BUF_COUNT);

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set DIP Comp [%d] Error!\r\n", DIP_S_COMP_VR_SHARE_RECD);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustPrmPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AdjustPrmPipe(MMP_UBYTE ubCamSel)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (MMPS_3GPRECD_CheckPrmPipe(ubCamSel) == MMP_ERR_NONE) {
        if (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR)) {
            //
            if(MMP_GetANACamType() == ANA_CAM_2I2O){
                eRetErr = MMPS_3GPRECD_AdjustPrmANADecRecd_Raw1(ubCamSel);
                eRetErr |= MMPS_Display_SetPrmPreviewPipeAttr_Raw2I2O(MMPS_PREVIEW_UI_MODE_VR,MMPS_DISPLAY_PREVIEW_FULL_SCREEN);
            }
            else{
                eRetErr = MMPS_3GPRECD_AdjustPrmBayerRecdPipe(ubCamSel);
                eRetErr |= MMPS_3GPRECD_AdjustPrmADASPipe(ubCamSel);
                eRetErr |= MMPS_3GPRECD_AdjustPrmBayerPrevwPipe(ubCamSel);
            }
        }
        else if (CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) {
            // TBD
            MMPS_VR_DBG_MSG(1, FG_RED("TODO:%s,line#%d\r\n"),__FUNCTION__, __LINE__);
        }
        else if(MMP_GetANACamType() == ANA_CAM_2I2O){
            MMPS_VR_DBG_MSG(1, FG_RED("TODO:%s,line#%d\r\n"),__FUNCTION__, __LINE__);
        }

        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Adjust Prm Pipe Error!\r\n");
            return eRetErr;
        }
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnablePrmCamPreview
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set customized preview mode.
 @param[in] usPreviewMode Assign preview display mode.
            0: VIDRECD_NORMAL_PREVIEW_MODE,
            1: VIDRECD_FULL_PREVIEW_MODE,
            2: VIDRECD_NTSC_PREVIEW_MODE,
            3: VIDRECD_PAL_PREVIEW_MODE,
            4: VIDRECD_HDMI_PREVIEW_MODE
            5: VIDRECD_CCIR_PREVIEW_MODE
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_EnablePrmCamPreview(MMP_USHORT usPreviewMode)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    m_VidRecdRuntimeCfg.usVideoPreviewMode = usPreviewMode;

    if (usPreviewMode == (MMP_USHORT)(-1)) {

        /* Close ADAS port */
        #if (SUPPORT_ADAS) || (SUPPORT_MDTC)
        if (m_eYFrameType == MMPS_3GPRECD_Y_FRAME_TYPE_ADAS) {
            ClosePortScript(PORT_SCRIPT_ALGORITHM);
            CloseScript(COMPO_SCRIPT_ADAS);
        }
        else if (m_eYFrameType == MMPS_3GPRECD_Y_FRAME_TYPE_VMD) {
            ClosePortScript(PORT_SCRIPT_ALGORITHM);
            CloseScript(COMPO_SCRIPT_MDTC);
        }
        #endif

        if(MMP_GetANACamType() == ANA_CAM_2I2O){
            if (gbLCDRotate) {
                CloseScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_SRC);         //DIP_S14->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9
                                                                        //DIP_S0->DIP_R0/DIP_S4
                CloseScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_FULL);        //DIP_S0<-DIP_R0->DISP
                ClosePortScript(PORT_SCRIPT_VR_PREV_PRM_RAW_FULL);       //DIP_S0 open outport1
                //RAW_CH1 Open outport3=DIP_S0
            }
            else {
                MMPS_VR_DBG_MSG(1, "TODO:%s,line#%d\r\n",__FUNCTION__, __LINE__);
            }
        }else{
            /* Stop preview flow */
            if (gbLCDRotate) {

                ClosePortScript(PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL);
                ClosePortScript(PORT_SCRIPT_VR_PREV_PRM_BAYER_PIP);

                CloseScript(COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_FULL);
                CloseScript(COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_PIP);
                CloseScript(COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_SRC);
            }
            else {

                ClosePortScript(PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL);
                ClosePortScript(PORT_SCRIPT_VR_PREV_PRM_BAYER_PIP);

                CloseScript(COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_FULL);
                CloseScript(COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_PIP);
                CloseScript(COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_SRC);
            }
        }
    }
    else {
        if (MMP_IsPrmCamExist()) {
            eRetErr = MMPS_3GPRECD_AdjustPrmPipe(PRM_SENSOR);
        }

        if(MMP_GetANACamType() == ANA_CAM_2I2O){
            if (gbLCDRotate) {
                OpenScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_SRC);         //DIP_S14->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9
                                                                        //DIP_S0->DIP_R0/DIP_S4
                OpenScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_FULL);        //DIP_S0<-DIP_R0->DISP
                OpenPortScript(PORT_SCRIPT_VR_PREV_PRM_RAW_FULL);       //DIP_S0 open outport1
                //RAW_CH1 Open outport3=DIP_S0
            }
            else {
                MMPS_VR_DBG_MSG(1, "TODO:%s,line#%d\r\n",__FUNCTION__, __LINE__);
            }
        }else{
            /* Start preview flow */
            if (gbLCDRotate) {
                OpenScript(COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_SRC);       //SCL0_PRM->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9
                OpenScript(COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_FULL);      //SCL1_PRM<-DIP_R0->DISP
                OpenPortScript(PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL);     //SCL1_PRM outport1
            }
            else {
                OpenScript(COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_SRC);
                OpenScript(COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_FULL);
                OpenPortScript(PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL);
            }
        }

        /* Open ADAS port */
        #if (SUPPORT_ADAS) || (SUPPORT_MDTC)
        if (m_eYFrameType == MMPS_3GPRECD_Y_FRAME_TYPE_ADAS) {
            OpenScript(COMPO_SCRIPT_ADAS);
            OpenPortScript(PORT_SCRIPT_ALGORITHM);
        }
        else if (m_eYFrameType == MMPS_3GPRECD_Y_FRAME_TYPE_VMD) {
            OpenScript(COMPO_SCRIPT_MDTC);
            OpenPortScript(PORT_SCRIPT_ALGORITHM);
        }
        #endif
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_PrmCamPreviewStop
//  Description : Stop preview display mode.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_PrmCamPreviewStop(MMP_UBYTE ubCamSel)
{
    MMP_ULONG  ulFileNameAddr = 0;
    MMP_ULONG  ulFileNameSize = 0;
    CamOsRet_e eCamOsRet = CAM_OS_OK;

    MMPS_3GPRECD_EnablePreviewPipe(ubCamSel, MMP_FALSE, MMP_FALSE);

    MMPD_3GPMGR_GetTempFileNameAddr(&ulFileNameAddr, &ulFileNameSize);

    if (ulFileNameAddr) {

        eCamOsRet = CamOsDirectMemRelease((void*)ulFileNameAddr, ulFileNameSize);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_3GPMGR_SetTempFileNameAddr(0, 0);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_PrmCamPreviewStart
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set buffers and parameters. Then display preview mode.
 @param[in] bCheckFrameEnd  The setting will check VIF frame end or not.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS Unsupport resolution.
*/
MMP_ERR MMPS_3GPRECD_PrmCamPreviewStart(MMP_UBYTE ubCamSel, MMP_BOOL bCheckFrameEnd)
{
    if (MMPS_3GPRECD_EnablePreviewPipe(ubCamSel, MMP_TRUE, bCheckFrameEnd) != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "PrmCam Enable Video Preview Fail\r\n");
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    return MMP_ERR_NONE;
}

#if 0
void ____VR_2nd_Preview_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustScdAnaDecRecdPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AdjustScdAnaDecRecdPipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG               ulSensorOutW = 0, ulSensorOutH = 0;
    MMP_ULONG               ulScaleInW = 0, ulScaleInH = 0;
    MMP_ULONG               ulScaleInAlignedX = 0, ulScaleInAlignedY = 0;
    MMP_ULONG               ulScaleInAlignedW = 0, ulScaleInAlignedH = 0;
    MMP_UBYTE               ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSrc = MMP_SNR_ANADEC_SRC_NO_READY;
    MMP_UBYTE               ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV; //if YUV sensor, the order may be diff
    MMPF_SENSOR_YUV_ORDER   order = MMPF_SENSOR_YUV_ORDER_CY;

    MMPS_Sensor_GetAnaDecSrcType(&eAnaDecSrc);

    eRetErr = MMPS_Sensor_GetCurSensorOutputRes(ubCamSel, &ulSensorOutW, &ulSensorOutH);
    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "GetCurSensorOutputRes Error!\r\n");
        return eRetErr;
    }

    eRetErr = MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);
    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "GetCurPrevScalInputRes Error!\r\n");
        return eRetErr;
    }

    if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_PAL) {
        ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
        ulScaleInAlignedX = 0;
        ulScaleInAlignedY = 2;
        ulScaleInAlignedW = 672;
        ulScaleInAlignedH = (ulScaleInH == 288) ? (ulScaleInH - 32) : ulScaleInH;
        ulScaleInAlignedH -= 2;
    }
    else if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_NTSC) {
        ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
        ulScaleInAlignedX = 0;
        ulScaleInAlignedY = 2;
        ulScaleInAlignedW = 672;
        ulScaleInAlignedH = 240;
        ulScaleInAlignedH -= 2;
    }
    else if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_FHD ||
             eAnaDecSrc == MMP_SNR_ANADEC_SRC_HD) {
        ubSigType = RAWS_COMP_SIG_TYPE_PROGRESSIVE;
        ulScaleInAlignedW = ulScaleInW;
        ulScaleInAlignedH = ulScaleInH;
    }

    eRetErr = MMPD_RAWPROC_SetRawSCompAttr( RAWS_COMP_IDX,
                                            ubSigType,
                                            ulSensorOutW,
                                            ulSensorOutH,
                                            RAWS_COMP_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set RAWS Comp Error!\r\n");
        return eRetErr;
    }
    //get YUV order from sensor, and select input color format
    eRetErr = MMPF_Sensor_GetSensorYuvOrder(ubCamSel, &order);
    if (eRetErr != MMP_ERR_NONE){
        return eRetErr;
    }
    //mapping
    switch(order)
    {
        case MMPF_SENSOR_YUV_ORDER_YC:
            ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_UYVY;
        break;
        case MMPF_SENSOR_YUV_ORDER_CY:
        default:
            ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
        break;
    }
    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_VR_RCAM_RECD,
                                        0, 0, ulScaleInW, ulScaleInH,
                                        ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                        0, 0, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                                        ubDIPSCLInColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_MIRROR_DIS,
                                        MFE_SHARE_BUF_LINE_BIAS,
                                        DIP_COMP_RECORD_BUF_COUNT);

    if (MMP_GetANACamType() == ANA_CAM_2I1O){
        MMP_ULONG ulEncodeW = m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW;
        MMP_ULONG ulEncodeH = m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH;

        UartSendTrace(FG_YELLOW("[RearCam H.264 Enc] %d x %d\r\n"), ulEncodeW, ulEncodeH);

        MMPD_Fctl_SetDIPCompAttr_LineOffset(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_VR_RCAM_RECD_2IN1_INA, DIP_S_COMP_VR_RCAM_RECD, // Left image
                                    0, 0, ulScaleInW, ulScaleInH, ulScaleInW,
                                    ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                    0, 0, ulEncodeW / 2, ulEncodeH, ulEncodeW,
                                    ubDIPSCLInColor,
                                    DIP_COMP_COLOR_FMT_YUV420_UV,
                                    DIP_COMP_MIRROR_DIS,
                                    MFE_SHARE_BUF_LINE_BIAS,
                                    0 /*DIP_COMP_RECORD_BUF_COUNT*/); // Buffers will be allocated in DIP_S_COMP_VR_RCAM_RECD


        MMPD_Fctl_SetDIPCompAttr_LineOffset(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_VR_RCAM_RECD_2IN1_INB, DIP_S_COMP_VR_RCAM_RECD, // Right image
                                    0, 0, ulScaleInW, ulScaleInH, ulScaleInW,
                                    ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                    ulEncodeW / 2, 0, ulEncodeW / 2, ulEncodeH, ulEncodeW,
                                    ubDIPSCLInColor,
                                    DIP_COMP_COLOR_FMT_YUV420_UV,
                                    DIP_COMP_MIRROR_DIS,
                                    MFE_SHARE_BUF_LINE_BIAS,
                                    0 /*DIP_COMP_RECORD_BUF_COUNT*/); // Buffers will be allocated in DIP_S_COMP_VR_RCAM_RECD
    }

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set DIP Comp [%d] Error!\r\n", DIP_S_COMP_VR_RCAM_RECD);
        return eRetErr;
    }

    if(MMP_GetRawStoreNum() == 2 && RAWS_COMP_IDX != RAWS_COMP_IDX2) {
        eRetErr = MMPD_RAWPROC_SetRawSCompAttr( RAWS_COMP_IDX2,
                                                ubSigType,
                                                ulSensorOutW,
                                                ulSensorOutH,
                                                RAWS_COMP_BUF_COUNT);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Set RAWS Comp Error!\r\n");
            return eRetErr;
        }

        //TODO:other comp flow
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustScdBayerRecdPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AdjustScdBayerRecdPipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulScaleInW = 0, ulScaleInH = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);

    eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL0,
                                        SCL0_COMP_SCD_CAM,
                                        1, 1, ulScaleInW, ulScaleInH,
                                        1, 1, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                                        SCL_COMP_RECORD_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "Set SCL0 Comp Error!\r\n");
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustScdPrevwPipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AdjustScdRecdPipe(MMP_UBYTE ubCamSel)
{
    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        return MMPS_3GPRECD_AdjustScdBayerRecdPipe(ubCamSel);
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER) ||
             CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        return MMPS_3GPRECD_AdjustScdAnaDecRecdPipe(ubCamSel);
    }
    else {
        return MMP_ERR_NONE;
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustScdPrevwPipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AdjustScdPrevwPipe(MMP_UBYTE ubCamSel)
{
    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        return MMPS_Display_SetScdBayerPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_VR,
                                                       MMPS_DISPLAY_PREVIEW_PIP_WIN);
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER) ||
             CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        return MMPS_Display_SetScdAnaDecPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_VR,
                                                        MMPS_DISPLAY_PREVIEW_PIP_WIN);
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_ScdCamPreviewStop
//  Description : Stop preview display mode.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_ScdCamPreviewStop(MMP_UBYTE ubCamSel)
{
    return MMPS_3GPRECD_EnablePreviewPipe(ubCamSel, MMP_FALSE, MMP_FALSE);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_ScdCamPreviewStart
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set buffers and parameters. Then display preview mode.
 @param[in] bCheckFrameEnd  The setting will check VIF frame end or not.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS Unsupport resolution.
*/
MMP_ERR MMPS_3GPRECD_ScdCamPreviewStart(MMP_UBYTE ubCamSel, MMP_BOOL bCheckFrameEnd)
{
    if (MMPS_3GPRECD_EnablePreviewPipe(ubCamSel, MMP_TRUE, bCheckFrameEnd) != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "ScdCam Enable Video Preview Fail\r\n");
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    return MMP_ERR_NONE;
}

#if 0
void ____VR_Common_Capture_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StillDualCapture
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StillDualCapture(MMPS_DSC_CAPTURE_INFO *pCaptInfo)
{
    VIDENC_FW_STATUS        eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ERR                 eCamErr = MMP_ERR_NONE;
    MMPS_DSC_CAPTURE_INFO   *pstPrmInfo = (MMPS_DSC_CAPTURE_INFO*)pCaptInfo;
    MMPS_DSC_CAPTURE_INFO   *pstScdInfo = (MMPS_DSC_CAPTURE_INFO*)pCaptInfo + 1;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;

    /* Parameter check */
    if (!pstPrmInfo->bCaptureEn ||
        !pstScdInfo->bCaptureEn) {
        return MMP_ERR_NONE;
    }

    eCamErr = MMPS_DSC_CaptureDualJPEG(pstPrmInfo, pstScdInfo);

    if (pstPrmInfo->ubShotMode != JPE_COMP_SINGLE_SHOT) {
        return MMP_ERR_NONE;
    }

    if (eCamErr == MMP_ERR_NONE) {

        if (m_ulPrmRecdID != INVALID_ENC_ID) {

            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

            if ((eEncFwSts == VIDENC_FW_STATUS_START) ||
                (eEncFwSts == VIDENC_FW_STATUS_PAUSE) ||
                (eEncFwSts == VIDENC_FW_STATUS_RESUME)) {

                /* Inform encoder the reserved space is reduced */
                if ((eCamErr = MMPD_3GPMGR_MakeRoom(m_ulPrmRecdID, pstPrmInfo->ulJpegFileSize)) != MMP_ERR_NONE) {
                    MMPS_VR_DBG_ERR(1, "PrmCam MakeRoom Err %x\r\n", eCamErr);
                    eRetErr = MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE;
                    goto L_StillRet;
                }
                if ((eCamErr = MMPD_3GPMGR_MakeRoom(m_ulPrmRecdID, pstScdInfo->ulJpegFileSize)) != MMP_ERR_NONE) {
                    MMPS_VR_DBG_ERR(1, "ScdCam MakeRoom Err %x\r\n", eCamErr);
                    eRetErr = MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE;
                    goto L_StillRet;
                }
            }
        }

        if ((eCamErr = MMPS_DSC_JpegDram2Card(pstPrmInfo)) != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "PrmCam Save Card Err %x\r\n", eCamErr);
            eRetErr = MMP_3GPRECD_ERR_STILL_CAPTURE;
            goto L_StillRet;
        }
        if ((eCamErr = MMPS_DSC_JpegDram2Card(pstScdInfo)) != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "ScdCam Save Card Err %x\r\n", eCamErr);
            eRetErr = MMP_3GPRECD_ERR_STILL_CAPTURE;
            goto L_StillRet;
        }
    }
    else {
        MMPS_VR_DBG_ERR(1, "Prm/ScdCam VRCapture Err %x\r\n", eCamErr);
        eRetErr = MMP_3GPRECD_ERR_STILL_CAPTURE;
        goto L_StillRet;
    }

L_StillRet:

    MMPS_DSC_CaptureJPEGFinish(JPE_COMP_PRM_PRIMARY, pstPrmInfo);
    MMPS_DSC_CaptureJPEGFinish(JPE_COMP_SCD_PRIMARY, pstScdInfo);

    MMPS_DSC_DeInitJpegEncModule();

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StillPrmCapture
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StillPrmCapture(MMPS_DSC_CAPTURE_INFO *pCaptInfo)
{
    VIDENC_FW_STATUS        eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ERR                 ePrmCamErr = MMP_ERR_NONE;
    MMPS_DSC_CAPTURE_INFO   *pstPrmInfo = (MMPS_DSC_CAPTURE_INFO*)pCaptInfo;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;

    /* Parameter check */
    if (!pstPrmInfo->bCaptureEn) {
        return MMP_ERR_NONE;
    }

    ePrmCamErr = MMPS_DSC_CaptureJPEG(JPE_COMP_PRM_PRIMARY, pstPrmInfo);

    if (pstPrmInfo->ubShotMode != JPE_COMP_SINGLE_SHOT) {
        return MMP_ERR_NONE;
    }

    if (ePrmCamErr == MMP_ERR_NONE) {

        if (m_ulPrmRecdID != INVALID_ENC_ID) {

            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

            if ((eEncFwSts == VIDENC_FW_STATUS_START) ||
                (eEncFwSts == VIDENC_FW_STATUS_PAUSE) ||
                (eEncFwSts == VIDENC_FW_STATUS_RESUME)) {

                /* Inform encoder the reserved space is reduced */
                if ((ePrmCamErr = MMPD_3GPMGR_MakeRoom(m_ulPrmRecdID, pstPrmInfo->ulJpegFileSize)) != MMP_ERR_NONE) {
                    MMPS_VR_DBG_ERR(1, "PrmCam MakeRoom Err %x\r\n", ePrmCamErr);
                    eRetErr = MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE;
                    goto L_StillRet;
                }
            }
        }

        if ((ePrmCamErr = MMPS_DSC_JpegDram2Card(pstPrmInfo)) != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "PrmCam Save Card Err %x\r\n", ePrmCamErr);
            eRetErr = MMP_3GPRECD_ERR_STILL_CAPTURE;
            goto L_StillRet;
        }
    }
    else {
        MMPS_VR_DBG_ERR(1, "PrmCam DSC_VRCapture Err %x\r\n", ePrmCamErr);
        eRetErr = MMP_3GPRECD_ERR_STILL_CAPTURE;
        goto L_StillRet;
    }

L_StillRet:

    MMPS_DSC_CaptureJPEGFinish(JPE_COMP_PRM_PRIMARY, pstPrmInfo);

    MMPS_DSC_DeInitJpegEncModule();

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StillScdCapture
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StillScdCapture(MMPS_DSC_CAPTURE_INFO *pCaptInfo)
{
    VIDENC_FW_STATUS        eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ERR                 eScdCamErr = MMP_ERR_NONE;
    MMPS_DSC_CAPTURE_INFO   *pstScdInfo = (MMPS_DSC_CAPTURE_INFO*)pCaptInfo;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;

    /* Parameter check */
    if (!pstScdInfo->bCaptureEn) {
        return MMP_ERR_NONE;
    }

    if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264) || \
        CAM_CHECK_USB(USB_CAM_SONIX_MJPEG) || \
        CAM_CHECK_SCD(SCD_CAM_ANA_DECODER) || \
        CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)  || \
        CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
    {
        eScdCamErr = MMPS_DSC_CaptureJPEG(JPE_COMP_SCD_PRIMARY, pstScdInfo);

        if (pstScdInfo->ubShotMode != JPE_COMP_SINGLE_SHOT) {
            return MMP_ERR_NONE;
        }

        if (eScdCamErr == MMP_ERR_NONE) {

            if (m_ulPrmRecdID != INVALID_ENC_ID) {

                eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

                if ((eEncFwSts == VIDENC_FW_STATUS_START) ||
                    (eEncFwSts == VIDENC_FW_STATUS_PAUSE) ||
                    (eEncFwSts == VIDENC_FW_STATUS_RESUME)) {

                    /* Inform encoder the reserved space is reduced */
                    if ((eScdCamErr = MMPD_3GPMGR_MakeRoom(m_ulPrmRecdID, pstScdInfo->ulJpegFileSize)) != MMP_ERR_NONE) {
                        MMPS_VR_DBG_ERR(1, "RCam MakeRoom Err %x\r\n", eScdCamErr);
                        eRetErr = MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE;
                        goto L_StillRet;
                    }
                }
            }

            if ((eScdCamErr = MMPS_DSC_JpegDram2Card(pstScdInfo)) != MMP_ERR_NONE) {
                MMPS_VR_DBG_ERR(1, "RCam Save Card Err %x\r\n", eScdCamErr);
                eRetErr = MMP_3GPRECD_ERR_STILL_CAPTURE;
                goto L_StillRet;
            }
        }
        else {
            MMPS_VR_DBG_ERR(1, "RCam DSC_VRCapture Err %x\r\n", eScdCamErr);
            eRetErr = MMP_3GPRECD_ERR_STILL_CAPTURE;
            goto L_StillRet;
        }
    }
    else {
        return MMP_ERR_NONE;
    }

L_StillRet:

    MMPS_DSC_CaptureJPEGFinish(JPE_COMP_SCD_PRIMARY, pstScdInfo);

    MMPS_DSC_DeInitJpegEncModule();

    return eRetErr;
}

#if 0
void ____VR_Thumbnail_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_OpenPrmThumbPortCB
//  Description :
//------------------------------------------------------------------------------
static void MMPS_3GPRECD_OpenPrmThumbPortCB(void)
{
    if(MMP_GetANACamType() == ANA_CAM_2I2O)
        OpenPortScript(PORT_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1);
    else
        OpenPortScript(PORT_SCRIPT_VR_PRM_BAYER_THUMB);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_OpenScdThumbPortCB
//  Description :
//------------------------------------------------------------------------------
static void MMPS_3GPRECD_OpenScdThumbPortCB(void)
{
    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        OpenPortScript(PORT_SCRIPT_VR_SCD_BAYER_THUMB);
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER))
        OpenPortScript(PORT_SCRIPT_VR_SCD_ANADEC_THUMB);
    else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264))
        OpenPortScript(PORT_SCRIPT_VR_USBH_THUMB);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_OpenShareThumbPortCB
//  Description :
//------------------------------------------------------------------------------
static void MMPS_3GPRECD_OpenShareThumbPortCB(void)
{
    OpenPortScript(PORT_SCRIPT_VR_SHARE_THUMB);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_OpenTrdThumbPortCB
//  Description :
//------------------------------------------------------------------------------
static void MMPS_3GPRECD_OpenTrdThumbPortCB(void)
{
    //OpenPortScript(PORT_SCRIPT_VR_TRD_THUMB);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_InitVRThumbPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_InitVRThumbPipe(MMP_UBYTE ubRecdSel)
{
#if (SUPPORT_VR_THUMBNAIL)
    JPE_COMP_RESOL      stJpeResol;
    MMP_UBYTE           ubDipBufCount = 1;
    MMP_UBYTE           ubJpeBufCount = 1;
    MMP_ULONG           ulJpeBufSize = 0;
    MMP_UBYTE           ubRingBufType = VIDENC_THUMB_RING_BUF_PRM;
    MMP_ULONG           ulThumbW = 0, ulThumbH = 0;
    MMP_USHORT          usInitQF = 20;
    MMP_COMPONENT_BASE  *pJpeComp = &Component_JPE[JPE_COMP_PRM_VR_THUMB];
    JPE_COMP_COLOR_FMT  eColorFmt = JPE_COMP_FMT_NV12;
    MMP_ULONG           ulWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
    MMP_ULONG           ulHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;

    if (!MMPF_VIDENC_GetVRThumbEn()) {
        return MMP_ERR_NONE;
    }

    MMPF_VIDENC_GetVRThumbResol(&ulThumbW, &ulThumbH);

    if (ubRecdSel == MMPS_VR_PRM_RECD) {
        pJpeComp        = &Component_JPE[JPE_COMP_PRM_VR_THUMB];
        ubRingBufType   = VIDENC_THUMB_RING_BUF_PRM;

        MMPD_Fctl_SetDIPCompAttr(DIP_COMP_TYPE_ID_SCL,
                                 DIP_S_COMP_VR_FCAM_THUMB,
                                 0, 0, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH,
                                 0, 0, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH,
                                 0, 0, ulThumbW, ulThumbH,
                                 DIP_COMP_COLOR_FMT_YUV420_UV,
                                 DIP_COMP_COLOR_FMT_YUV420_UV,
                                 DIP_COMP_MIRROR_DIS,
                                 0,
                                 ubDipBufCount);
    }
    else if (ubRecdSel == MMPS_VR_SCD_RECD) {
        pJpeComp        = &Component_JPE[JPE_COMP_SCD_VR_THUMB];
        ubRingBufType   = VIDENC_THUMB_RING_BUF_SCD;

        MMPD_Fctl_SetDIPCompAttr(DIP_COMP_TYPE_ID_SCL,
                                 DIP_S_COMP_VR_RCAM_THUMB,
                                 0, 0, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH,
                                 0, 0, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH,
                                 0, 0, ulThumbW, ulThumbH,
                                 DIP_COMP_COLOR_FMT_YUV420_UV,
                                 DIP_COMP_COLOR_FMT_YUV420_UV,
                                 DIP_COMP_MIRROR_DIS,
                                 0,
                                 ubDipBufCount);
    }
    else if (ubRecdSel == MMPS_VR_TRD_RECD) {
        pJpeComp        = &Component_JPE[JPE_COMP_TRD_VR_THUMB];
        ubRingBufType   = VIDENC_THUMB_RING_BUF_TRD;

        MMPD_Fctl_SetDIPCompAttr(DIP_COMP_TYPE_ID_SCL,
                                 DIP_S_COMP_VR_RCAM_THUMB, // TBD
                                 0, 0, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH,
                                 0, 0, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH,
                                 0, 0, ulThumbW, ulThumbH,
                                 DIP_COMP_COLOR_FMT_YUV420_UV,
                                 DIP_COMP_COLOR_FMT_YUV420_UV,
                                 DIP_COMP_MIRROR_DIS,
                                 0,
                                 ubDipBufCount);
    }

    Component_JPE_GetParam(pJpeComp, JPE_COMP_PARAM_FMT, (void*)&eColorFmt);

    if (eColorFmt == JPE_COMP_FMT_NV12 ||
        eColorFmt == JPE_COMP_FMT_NV21) {
        ulWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
        ulHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;
    }
    else {
        ulWAlignBase = JPE_COMP_W_ALIGN_BASE_YUV422;
        ulHAlignBase = JPE_COMP_H_ALIGN_BASE_YUV422;
    }

    stJpeResol.ulEncW    = ulThumbW;
    stJpeResol.ulEncH    = ulThumbH;
    stJpeResol.ulEncBufW = ALIGN_X(ulThumbW, ulWAlignBase);
    stJpeResol.ulEncBufH = ALIGN_X(ulThumbH, ulHAlignBase);
    Component_JPE_SetParam(pJpeComp, JPE_COMP_PARAM_RES, (void*)&stJpeResol);

    usInitQF = 48; // TBD
    Component_JPE_SetParam(pJpeComp, JPE_COMP_PARAM_INIT_QF, (void*)&usInitQF);

    ulJpeBufSize = ALIGN32(ulThumbW * ulThumbH * 3 / 2); // (YUV420 * 0.7)
    ulJpeBufSize = ALIGN32(ulJpeBufSize * 7 / 10);
    MMPF_VIDENC_SetVRThumbMaxBufSize(ulJpeBufSize);

    ubJpeBufCount = MMPF_VIDENC_GetVRThumbRingBufNum(ubRingBufType);

    Component_JPE_SetParam(pJpeComp, JPE_COMP_PARAM_BUF_COUNT, (void*)&ubJpeBufCount);
    Component_JPE_SetParam(pJpeComp, JPE_COMP_PARAM_BUF_SIZE, (void*)&ulJpeBufSize);
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetVRThumbEn
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetVRThumbEn(MMP_UBYTE ubEnable, MMP_UBYTE ubIsCreateJpg)
{
    return MMPF_VIDENC_SetVRThumbEn(ubEnable, ubIsCreateJpg);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetVRThumbEn
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMPS_3GPRECD_GetVRThumbEn(void)
{
    return MMPF_VIDENC_GetVRThumbEn();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetVRThumbRingBufNum
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetVRThumbRingBufNum(MMP_UBYTE ubRingBufNum)
{
    return MMPF_VIDENC_SetVRThumbRingBufNum(ubRingBufNum);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetVRThumbResol
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetVRThumbResol(MMP_ULONG ulJpegW, MMP_ULONG ulJpegH)
{
    return MMPF_VIDENC_SetVRThumbResol(ulJpegW, ulJpegH);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetVRThumbResol
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetVRThumbResol(MMP_ULONG *pulJpegW, MMP_ULONG *pulJpegH)
{
    return MMPF_VIDENC_GetVRThumbResol(pulJpegW, pulJpegH);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StoreVRThumbToFile
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StoreVRThumbToFile(MMP_BYTE ubFilename[], MMP_USHORT usFileNameLen, MMP_USHORT ulStreamType)
{
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    MMPS_DSC_CAPTURE_INFO   stDscCaptInfo;

    if (!MMPF_VIDENC_IsVRThumbCreateFile()) {
        return MMP_ERR_NONE;
    }

    memset(&stDscCaptInfo, 0x0, sizeof(MMPS_DSC_CAPTURE_INFO));

    stDscCaptInfo.bFileName         = (MMP_BYTE*)ubFilename;
    stDscCaptInfo.ulFileNameLen     = usFileNameLen;
    stDscCaptInfo.bFirstShot        = MMP_TRUE;
    stDscCaptInfo.bExifEn           = MMP_FALSE;
    stDscCaptInfo.ulExtraBufAddr    = 0;

    if ((eRetErr = MMPS_DSC_ThumbDram2Card(&stDscCaptInfo, (MMP_ULONG)ulStreamType)) != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "VR Thumb Save Card Err\r\n");
        return MMP_3GPRECD_ERR_STILL_CAPTURE;
    }

    return MMP_ERR_NONE;
}

#if 0
void ____VR_Mem_Manage_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AllocAudioMemory
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AllocAudioMemory(void)
{
    const MMP_ULONG     ulAudCompBufSize = m_VidRecdPresetCfg.ulAudioCompBufSize;
    void*               pvAudCompBufVirt = NULL;
    CamOsRet_e          eCamOsRet = CAM_OS_OK;

    eCamOsRet = CamOsDirectMemAlloc("AudioComp", ulAudCompBufSize, &pvAudCompBufVirt, NULL, NULL);
    CAM_OS_RET_CHK(eCamOsRet);

    MMPD_AUDIO_SetEncodeBuf((MMP_ULONG)pvAudCompBufVirt, ulAudCompBufSize);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_FreeAudioMemory
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_FreeAudioMemory(void)
{
    MMP_ULONG   ulAudCompBufSize = 0;
    MMP_ULONG   ulAudCompBufVirt = 0;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    MMPD_AUDIO_GetEncodeBuf(&ulAudCompBufVirt, &ulAudCompBufSize);

    if (ulAudCompBufVirt) {
        eCamOsRet = CamOsDirectMemRelease((void*)ulAudCompBufVirt, ulAudCompBufSize);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_AUDIO_SetEncodeBuf(0, 0);
        MMPS_VR_DBG_MSG(0, "Free Audio Buffer\r\n");
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AllocUVCEncMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AllocUVCEncMemory(void* pvCompHandle, MMP_USHORT usStreamType)
{
#if (UVC_VIDRECD_SUPPORT)
    const MMP_ULONG         ulSPSSize       = VID_ENC_SPS_BUF_SIZE;
    const MMP_ULONG         ulPPSSize       = VID_ENC_PPS_BUF_SIZE;
    void*                   pvSPSBufVirt    = NULL;
    void*                   pvPPSBufVirt    = NULL;
    CamOsRet_e              eCamOsRet       = CAM_OS_OK;
    MMP_BOOL                bSupportUVC     = MMP_FALSE;

    if (usStreamType != VIDENC_STREAM_UVC_RECD) {
        return MMP_ERR_NONE;
    }

    MMPS_HUVC_GetUVCRecdSupport(&bSupportUVC);
    if (!bSupportUVC) {
        return MMP_ERR_NONE;
    }

    MMPF_H264ENC_SetUVCCompHandle(pvCompHandle);

    // Set SPS buffer
    eCamOsRet = CamOsDirectMemAlloc("UVC-SPS", ulSPSSize, &pvSPSBufVirt, NULL, NULL);
    CAM_OS_RET_CHK(eCamOsRet);

    // Set PPS buffer
    eCamOsRet = CamOsDirectMemAlloc("UVC-PPS", ulPPSSize, &pvPPSBufVirt, NULL, NULL);
    CAM_OS_RET_CHK(eCamOsRet);

    MMPF_H264ENC_SetUVCHeaderBuf((MMP_ULONG)pvSPSBufVirt, (MMP_ULONG)pvPPSBufVirt);

    MMPS_VR_DBG_MSG(0, "UVC SPS 0x%x PPS 0x%x\r\n",
                    (MMP_ULONG)pvSPSBufVirt,
                    (MMP_ULONG)pvPPSBufVirt);

#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_FreeUVCEncMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_FreeUVCEncMemory(MMP_USHORT usStreamType)
{
    const MMP_ULONG ulSPSSize = VID_ENC_SPS_BUF_SIZE;
    const MMP_ULONG ulPPSSize = VID_ENC_PPS_BUF_SIZE;
    MMP_ULONG       ulSPSAddr = 0;
    MMP_ULONG       ulPPSAddr = 0;
    CamOsRet_e      eCamOsRet = CAM_OS_OK;

    if (usStreamType != VIDENC_STREAM_UVC_RECD) {
        return MMP_ERR_NONE;
    }

    MMPF_H264ENC_GetUVCHeaderBuf(&ulSPSAddr, &ulPPSAddr);

    if (ulSPSAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)ulSPSAddr, ulSPSSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }
    if (ulPPSAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)ulPPSAddr, ulPPSSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    MMPF_H264ENC_SetUVCHeaderBuf(0, 0);

    MMPS_VR_DBG_MSG(0, "Free UVC Enc Mem\r\n");

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AllocUVCMGRMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AllocUVCMGRMemory(MMP_USHORT usStreamType, MMP_BOOL bMultiTrack)
{
#if (UVC_VIDRECD_SUPPORT)
    MMPD_3GPMGR_REPACKBUF   stUvcRepackMiscBuf;
    MMP_ULONG               ulUvcVidSizeTableSize   = VID_MGR_AUX_SIZE_TBL_BUF_SZ;
    MMP_ULONG               ulUvcVidTimeTableSize   = VID_MGR_AUX_TIME_TBL_BUF_SZ;
    MMP_ULONG               ulVidBufAddr            = 0, ulVidBufSize = 0;
    MMP_ULONG               ulAudBufAddr            = 0, ulAudBufSize = 0;
    void*                   pvVidSizeTblVirt        = NULL;
    void*                   pvVidTimeTblVirt        = NULL;
    void*                   pvTailBufVirt           = NULL;
    MMP_ULONG               ulTailBufSize           = 0;
    MMP_ULONG               ulTailBufMultiplier     = 1;
    CamOsRet_e              eCamOsRet               = CAM_OS_OK;
    MMP_BOOL                bSupportUVC             = MMP_FALSE;

    if (usStreamType != VIDENC_STREAM_UVC_RECD) {
        return MMP_ERR_NONE;
    }

    MMPS_HUVC_GetUVCRecdSupport(&bSupportUVC);
    if (!bSupportUVC) {
        return MMP_ERR_NONE;
    }

    if (MMPF_VIDMGR_IsUvcEmergEn() == MMP_FALSE) {
        ulTailBufMultiplier     = 1;
        ulUvcVidSizeTableSize   = VID_MGR_AUX_SIZE_TBL_BUF_SZ;
        ulUvcVidTimeTableSize   = VID_MGR_AUX_TIME_TBL_BUF_SZ;
    }
    else {
        ulTailBufMultiplier     = 2;
        ulUvcVidSizeTableSize   = VID_MGR_AUX_SIZE_TBL_BUF_SZ * 2;
        ulUvcVidTimeTableSize   = VID_MGR_AUX_TIME_TBL_BUF_SZ * 2;
    }

    // Set AV compress buffer information from encoder
    MMPF_H264ENC_GetUVCCompressBuf(&ulVidBufAddr, &ulVidBufSize);
    MMPD_AUDIO_GetEncodeBuf(&ulAudBufAddr, &ulAudBufSize);

    MMPF_VIDMGR_SetAVCompBufEx( usStreamType,
                                ulVidBufAddr,
                                ulVidBufSize,
                                ulAudBufAddr,
                                ulAudBufSize);

    if (bMultiTrack == MMP_FALSE && !MMPF_VIDMGR_GetMultiTrackEn()) {

        // Set aux size table buffer, must be 512 byte alignment
        eCamOsRet = CamOsDirectMemAlloc("Aux Video Size Table", ulUvcVidSizeTableSize, &pvVidSizeTblVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        stUvcRepackMiscBuf.ulVideoSizeTableAddr   = (MMP_ULONG)pvVidSizeTblVirt;
        stUvcRepackMiscBuf.ulVideoSizeTableSize   = ulUvcVidSizeTableSize;

        // Set aux time table buffer, must be 512 byte alignment
        eCamOsRet = CamOsDirectMemAlloc("Aux Video Time Table", ulUvcVidTimeTableSize, &pvVidTimeTblVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        stUvcRepackMiscBuf.ulVideoTimeTableAddr   = (MMP_ULONG)pvVidTimeTblVirt;
        stUvcRepackMiscBuf.ulVideoTimeTableSize   = ulUvcVidTimeTableSize;

        #if 0 // Move to component_mgr
        eCamOsRet = CamOsDirectMemAlloc("UVC Repack", ulUvcRepackBufSize, &pvAVRepackBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        stUvcRepackMiscBuf.ulAvRepackStartAddr    = (MMP_ULONG)pvAVRepackBufVirt;
        stUvcRepackMiscBuf.ulAvRepackSize         = ulUvcRepackBufSize;
        #else
        stUvcRepackMiscBuf.ulAvRepackStartAddr    = 0;
        stUvcRepackMiscBuf.ulAvRepackSize         = 0;
        #endif

        MMPD_3GPMGR_SetRepackMiscBuf(usStreamType, &stUvcRepackMiscBuf);

        // Set tail info buffer
        ulTailBufSize = m_VidRecdPresetCfg.ulUVCTailBufSize;

        ulTailBufSize = ALIGN32(ulTailBufSize);
        ulTailBufSize = ulTailBufSize * ulTailBufMultiplier;

        eCamOsRet = CamOsDirectMemAlloc("Tail Buf", ulTailBufSize, &pvTailBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_3GPMGR_SetRecordTailSpeed(usStreamType, MMP_TRUE, (MMP_ULONG)pvTailBufVirt, ulTailBufSize);
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_FreeUVCMGRMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_FreeUVCMGRMemory(MMP_USHORT usStreamType)
{
    MMPD_3GPMGR_REPACKBUF   stRepackMiscBuf;
    MMP_ULONG               ulTailBufVirt = 0, ulTailBufSize = 0;
    CamOsRet_e              eCamOsRet = CAM_OS_OK;

    if (usStreamType != VIDENC_STREAM_UVC_RECD) {
        return MMP_ERR_NONE;
    }

    MMPD_3GPMGR_GetRepackMiscBuf(usStreamType, &stRepackMiscBuf);

    MMPD_3GPMGR_GetRecordTailBuf(usStreamType, &ulTailBufVirt, &ulTailBufSize);

    // Free Misc buffer
    if (stRepackMiscBuf.ulVideoSizeTableAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)stRepackMiscBuf.ulVideoSizeTableAddr, stRepackMiscBuf.ulVideoSizeTableSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    if (stRepackMiscBuf.ulVideoTimeTableAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)stRepackMiscBuf.ulVideoTimeTableAddr, stRepackMiscBuf.ulVideoTimeTableSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    // Free Tail buffer
    if (ulTailBufVirt) {
        eCamOsRet = CamOsDirectMemRelease((void*)ulTailBufVirt, ulTailBufSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    stRepackMiscBuf.ulAvRepackStartAddr     = 0;
    stRepackMiscBuf.ulAvRepackSize          = 0;
    stRepackMiscBuf.ulVideoSizeTableAddr    = 0;
    stRepackMiscBuf.ulVideoSizeTableSize    = 0;
    stRepackMiscBuf.ulVideoTimeTableAddr    = 0;
    stRepackMiscBuf.ulVideoTimeTableSize    = 0;
    MMPD_3GPMGR_SetRepackMiscBuf(usStreamType, &stRepackMiscBuf);

    MMPD_3GPMGR_SetRecordTailSpeed(usStreamType, MMP_TRUE, 0, 0);

    MMPS_VR_DBG_MSG(0, "Free MGR Type %d : Misc, Tail Buffer\r\n", usStreamType);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustMGRMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AdjustMGRMemory(MMP_USHORT usStrmType)
{
    MMP_UBYTE ubBufCnt = 1;
    MMP_ULONG ulRepackBufSize = 0;
    MMP_BOOL  bMultiTrackEn = MMP_FALSE;

    if ((MMPF_VIDMGR_GetMultiTrackEn()) &&
        (usStrmType == VIDENC_STREAM_SCD_RECD ||
         usStrmType == VIDENC_STREAM_TRD_RECD ||
         usStrmType == VIDENC_STREAM_UVC_RECD)) {
        bMultiTrackEn = MMP_TRUE;
    }

    switch (usStrmType) {
    case VIDENC_STREAM_PRM_RECD:
        ubBufCnt = 1;
        ulRepackBufSize = (MMPF_VIDMGR_IsPrmEmergEn() == MMP_FALSE) ? VID_MGR_REPACK_BUF_SIZE : VID_MGR_REPACK_BUF_SIZE_EMERG;
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_PRM_RECD], MGR_COMP_PARAM_MULTI_TRACK, (void*)&bMultiTrackEn);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_PRM_RECD], MGR_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_PRM_RECD], MGR_COMP_PARAM_BUF_SIZE, (void*)&ulRepackBufSize);
        break;
    case VIDENC_STREAM_SCD_RECD:
        ubBufCnt = 1;
        ulRepackBufSize = (MMPF_VIDMGR_IsScdEmergEn() == MMP_FALSE) ? VID_MGR_REPACK_BUF_SIZE : VID_MGR_REPACK_BUF_SIZE_EMERG;
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_SCD_RECD], MGR_COMP_PARAM_MULTI_TRACK, (void*)&bMultiTrackEn);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_SCD_RECD], MGR_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_SCD_RECD], MGR_COMP_PARAM_BUF_SIZE, (void*)&ulRepackBufSize);
        break;
    case VIDENC_STREAM_TRD_RECD:
        ubBufCnt = 1;
        ulRepackBufSize = (MMPF_VIDMGR_IsTrdEmergEn() == MMP_FALSE) ? VID_MGR_REPACK_BUF_SIZE : VID_MGR_REPACK_BUF_SIZE_EMERG;
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_TRD_RECD], MGR_COMP_PARAM_MULTI_TRACK, (void*)&bMultiTrackEn);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_TRD_RECD], MGR_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_TRD_RECD], MGR_COMP_PARAM_BUF_SIZE, (void*)&ulRepackBufSize);
        break;
    case VIDENC_STREAM_UVC_RECD:
        ubBufCnt = 1;
        ulRepackBufSize = (MMPF_VIDMGR_IsUvcEmergEn() == MMP_FALSE) ? VID_MGR_REPACK_BUF_SIZE : VID_MGR_REPACK_BUF_SIZE_EMERG;
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_UVC_RECD], MGR_COMP_PARAM_MULTI_TRACK, (void*)&bMultiTrackEn);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_UVC_RECD], MGR_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_UVC_RECD], MGR_COMP_PARAM_BUF_SIZE, (void*)&ulRepackBufSize);
        break;
    case VIDENC_STREAM_WIFI_PRM:
        ubBufCnt = 0;
        ulRepackBufSize = 0;
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_PRM_STREAM], MGR_COMP_PARAM_MULTI_TRACK, (void*)&bMultiTrackEn);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_PRM_STREAM], MGR_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_PRM_STREAM], MGR_COMP_PARAM_BUF_SIZE, (void*)&ulRepackBufSize);
        break;
    case VIDENC_STREAM_WIFI_SCD:
        ubBufCnt = 0;
        ulRepackBufSize = 0;
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_SCD_STREAM], MGR_COMP_PARAM_MULTI_TRACK, (void*)&bMultiTrackEn);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_SCD_STREAM], MGR_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        Component_MGR_SetParam(&Component_MGR[MGR_COMP_SCD_STREAM], MGR_COMP_PARAM_BUF_SIZE, (void*)&ulRepackBufSize);
        break;
    default:
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AllocMGRMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AllocMGRMemory(MMP_USHORT usStrmType, MMP_BOOL bMultiTrack)
{
    MMP_ULONG                       ulVideoSizeTblSize  = VID_MGR_AUX_SIZE_TBL_BUF_SZ * 4; // Normal record and emergent record
    MMP_ULONG                       ulVideoTimeTblSize  = VID_MGR_AUX_TIME_TBL_BUF_SZ * 2; // Normal record and emergent record
    MMPD_3GPMGR_REPACKBUF           stRepackMiscBuf;
    MMP_ULONG                       ulEncId = 0;
    MMP_ULONG                       ulVidBufAddr = 0, ulVidBufSize = 0;
    MMP_ULONG                       ulAudBufAddr = 0, ulAudBufSize = 0;

    void*                           pvVidSizeTblVirt = NULL;
    void*                           pvVidTimeTblVirt = NULL;
    MMP_ULONG                       ulTailBufMultiplier = 1;
    MMP_ULONG                       ulTailBufSize = 0;
    void*                           pvTailBufVirt = NULL;
    MMP_UBYTE                       ubRecdSel = MMPS_VR_PRM_RECD;
    CamOsRet_e                      eCamOsRet = CAM_OS_OK;

    switch (usStrmType) {
    case VIDENC_STREAM_PRM_RECD:
        ubRecdSel = MMPS_VR_PRM_RECD;
        if (MMPF_VIDMGR_IsPrmEmergEn() == MMP_FALSE) {
            ulTailBufMultiplier = 1;
            ulVideoSizeTblSize  = VID_MGR_AUX_SIZE_TBL_BUF_SZ;
            ulVideoTimeTblSize  = VID_MGR_AUX_TIME_TBL_BUF_SZ;
        }
        else {
            ulTailBufMultiplier = 4;
            ulVideoSizeTblSize  = VID_MGR_AUX_SIZE_TBL_BUF_SZ * 4;
            ulVideoTimeTblSize  = VID_MGR_AUX_TIME_TBL_BUF_SZ * 2;
        }
        break;
    case VIDENC_STREAM_SCD_RECD:
        ubRecdSel = MMPS_VR_SCD_RECD;
        if (MMPF_VIDMGR_IsScdEmergEn() == MMP_FALSE) {
            ulTailBufMultiplier = 1;
            ulVideoSizeTblSize  = VID_MGR_AUX_SIZE_TBL_BUF_SZ;
            ulVideoTimeTblSize  = VID_MGR_AUX_TIME_TBL_BUF_SZ;
        }
        else {
            ulTailBufMultiplier = 2;
            ulVideoSizeTblSize  = VID_MGR_AUX_SIZE_TBL_BUF_SZ * 2;
            ulVideoTimeTblSize  = VID_MGR_AUX_TIME_TBL_BUF_SZ * 2;
        }
        break;
    case VIDENC_STREAM_TRD_RECD:
        ubRecdSel = MMPS_VR_TRD_RECD;
        if (MMPF_VIDMGR_IsTrdEmergEn() == MMP_FALSE) {
            ulTailBufMultiplier = 1;
            ulVideoSizeTblSize  = VID_MGR_AUX_SIZE_TBL_BUF_SZ;
            ulVideoTimeTblSize  = VID_MGR_AUX_TIME_TBL_BUF_SZ;
        }
        else {
            ulTailBufMultiplier = 2;
            ulVideoSizeTblSize  = VID_MGR_AUX_SIZE_TBL_BUF_SZ * 2;
            ulVideoTimeTblSize  = VID_MGR_AUX_TIME_TBL_BUF_SZ * 2;
        }
        break;
    default:
        break;
    }

    // Set AV compress buffer information from encoder
    ulEncId = MMPF_VIDMGR_GetInstIdFromStreamType(usStrmType);
    if (ulEncId >= VIDENC_MAX_STREAM_NUM) {
        MMPS_VR_DBG_ERR(1, "SetMGRMemory => Wrong Enc ID [%d][%d]\r\n", ulEncId, usStrmType);
        return MMP_ERR_NONE;
    }

    MMPD_H264ENC_GetBitstreamBuf(ulEncId, &ulVidBufAddr, &ulVidBufSize);
    MMPD_AUDIO_GetEncodeBuf(&ulAudBufAddr, &ulAudBufSize);

    MMPF_VIDMGR_SetAVCompBufEx( usStrmType,
                                ulVidBufAddr,
                                ulVidBufSize,
                                ulAudBufAddr,
                                ulAudBufSize);

    if (usStrmType == VIDENC_STREAM_WIFI_PRM ||
        usStrmType == VIDENC_STREAM_WIFI_SCD) {
        // Streaming flow didn't need Aux table and tail buffer
        return MMP_ERR_NONE;
    }

    if (bMultiTrack == MMP_FALSE) {

        // Set aux size table buffer, must be 512 byte alignment
        eCamOsRet = CamOsDirectMemAlloc("Aux Video Size Table", ulVideoSizeTblSize, &pvVidSizeTblVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        stRepackMiscBuf.ulVideoSizeTableAddr  = (MMP_ULONG)pvVidSizeTblVirt;
        stRepackMiscBuf.ulVideoSizeTableSize  = ulVideoSizeTblSize;

        // Set aux time table buffer, must be 512 byte alignment
        eCamOsRet = CamOsDirectMemAlloc("Aux Video Time Table", ulVideoTimeTblSize, &pvVidTimeTblVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        stRepackMiscBuf.ulVideoTimeTableAddr  = (MMP_ULONG)pvVidTimeTblVirt;
        stRepackMiscBuf.ulVideoTimeTableSize  = ulVideoTimeTblSize;

        #if 0 // Move to component_mgr
        // Set av repack buffer
        eCamOsRet = CamOsDirectMemAlloc("AV Repack", ulAVRepackBufSize, &AVRepackBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        stRepackMiscBuf.ulAvRepackStartAddr = (MMP_ULONG)AVRepackBufVirt;
        stRepackMiscBuf.ulAvRepackSize      = ulAVRepackBufSize;
        #else
        stRepackMiscBuf.ulAvRepackStartAddr = 0;
        stRepackMiscBuf.ulAvRepackSize      = 0;
        #endif

        MMPD_3GPMGR_SetRepackMiscBuf(usStrmType, &stRepackMiscBuf);

        // Set tail info buffer :TBD
        if (1) //(m_VidRecdPresetCfg.ulTailBufSize)
            ulTailBufSize = m_VidRecdPresetCfg.ulTailBufSize;
        else
            ulTailBufSize = MMPS_3GPRECD_GetContainerTailBufSize(ubRecdSel);

        ulTailBufSize = ALIGN32(ulTailBufSize);
        ulTailBufSize = ulTailBufSize * ulTailBufMultiplier;

        if (ulTailBufSize) {
            eCamOsRet = CamOsDirectMemAlloc("Tail Buf", ulTailBufSize, &pvTailBufVirt, NULL, NULL);
            CAM_OS_RET_CHK(eCamOsRet);

            MMPD_3GPMGR_SetRecordTailSpeed(usStrmType, MMP_TRUE, (MMP_ULONG)pvTailBufVirt, ulTailBufSize);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_FreeMGRMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_FreeMGRMemory(MMP_USHORT usStrmType)
{
    MMPD_3GPMGR_REPACKBUF   stRepackMiscBuf;
    MMP_ULONG               ulTailBufVirt = 0, ulTailBufSize = 0;
    CamOsRet_e              eCamOsRet = CAM_OS_OK;

    if (usStrmType == VIDENC_STREAM_WIFI_PRM ||
        usStrmType == VIDENC_STREAM_WIFI_SCD) {
        // Streaming flow didn't need Aux table and tail buffer
        return MMP_ERR_NONE;
    }

    MMPD_3GPMGR_GetRepackMiscBuf(usStrmType, &stRepackMiscBuf);

    MMPD_3GPMGR_GetRecordTailBuf(usStrmType, &ulTailBufVirt, &ulTailBufSize);

    // Free Misc buffer
    if (stRepackMiscBuf.ulVideoSizeTableAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)stRepackMiscBuf.ulVideoSizeTableAddr, stRepackMiscBuf.ulVideoSizeTableSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    if (stRepackMiscBuf.ulVideoTimeTableAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)stRepackMiscBuf.ulVideoTimeTableAddr, stRepackMiscBuf.ulVideoTimeTableSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    // Free Tail buffer
    if (ulTailBufVirt) {
        eCamOsRet = CamOsDirectMemRelease((void*)ulTailBufVirt, ulTailBufSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    stRepackMiscBuf.ulAvRepackStartAddr     = 0;
    stRepackMiscBuf.ulAvRepackSize          = 0;
    stRepackMiscBuf.ulVideoSizeTableAddr    = 0;
    stRepackMiscBuf.ulVideoSizeTableSize    = 0;
    stRepackMiscBuf.ulVideoTimeTableAddr    = 0;
    stRepackMiscBuf.ulVideoTimeTableSize    = 0;
    MMPD_3GPMGR_SetRepackMiscBuf(usStrmType, &stRepackMiscBuf);

    MMPD_3GPMGR_SetRecordTailSpeed(usStrmType, MMP_TRUE, 0, 0);

    MMPS_VR_DBG_MSG(0, "Free MGR Type [%d] Aux/Tail Buffer\r\n", usStrmType);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AllocVRThumbMemory
//  Description : TBD
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_AllocVRThumbMemory(void)
{
#if (SUPPORT_VR_THUMBNAIL)

    if (MMPF_VIDENC_GetVRThumbEn()) {

        extern VIDENC_THUMB_ATTR gstVRThumbAttr[VIDENC_THUMB_MAX_TYPE][VR_THUMB_MAX_BUF_NUM];

        void*       pvThumbVirt = NULL;
        MMP_ULONG   ulThumbW = 0, ulThumbH = 0;
        MMP_ULONG   ulThumbSize = 0;
        MMP_UBYTE   i = 0, j = 0;
        CamOsRet_e  eCamOsRet = CAM_OS_OK;

        MMPF_VIDENC_GetVRThumbResol(&ulThumbW, &ulThumbH);

        ulThumbSize = ALIGN32(ulThumbW * ulThumbH * 3 / 2); // (YUV420 * 0.7)
        ulThumbSize = ALIGN32(ulThumbSize * 7 / 10);
        MMPF_VIDENC_SetVRThumbMaxBufSize(ulThumbSize);

        for (i = VIDENC_THUMB_PRM_RECD; i <= VIDENC_THUMB_UVC_EMERG; i++) {
            for (j = 0; j < MMPF_VIDENC_GetVRThumbStreamBufNum(i); j++) {
                eCamOsRet = CamOsDirectMemAlloc("VR Thumb", ulThumbSize, &pvThumbVirt, NULL, NULL);
                CAM_OS_RET_CHK(eCamOsRet);
                gstVRThumbAttr[i][j].ulAddr     = (MMP_ULONG)pvThumbVirt;
                gstVRThumbAttr[i][j].ulSize     = 0;
                gstVRThumbAttr[i][j].ulProgCnt  = INVALID_THUMB_PROG_CNT;
                gstVRThumbAttr[i][j].ulFrmQIdx  = 0;

                MMPS_VR_DBG_MSG(0, "VRThumbAttr[%d][%d] Addr = 0x%X\r\n", i, j, gstVRThumbAttr[i][j].ulAddr);
            }
        }
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_FreeVRThumbMemory
//  Description : TBD
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_FreeVRThumbMemory(void)
{
#if (SUPPORT_VR_THUMBNAIL)

    if (MMPF_VIDENC_GetVRThumbEn()) {

        MMP_ULONG   ulThumbSize = 0;
        MMP_UBYTE   i = 0, j = 0;
        CamOsRet_e  eCamOsRet = CAM_OS_OK;

        extern VIDENC_THUMB_ATTR gstVRThumbAttr[VIDENC_THUMB_MAX_TYPE][VR_THUMB_MAX_BUF_NUM];

        ulThumbSize = MMPF_VIDENC_GetVRThumbMaxBufSize();

        for (i = VIDENC_THUMB_PRM_RECD; i <= VIDENC_THUMB_UVC_EMERG; i++) {
            for (j = 0; j < MMPF_VIDENC_GetVRThumbStreamBufNum(i); j++) {
                if (gstVRThumbAttr[i][j].ulAddr) {
                    eCamOsRet = CamOsDirectMemRelease(gstVRThumbAttr[i][j].ulAddr, ulThumbSize);
                    CAM_OS_RET_CHK(eCamOsRet);

                    gstVRThumbAttr[i][j].ulAddr = 0;
                    MMPS_VR_DBG_MSG(0, "Free VR Thumb Buffer\r\n");
                }
            }
        }
    }
#endif

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AdjustH264CompMemory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AdjustH264CompMemory(MMP_USHORT usStrmType)
{
#define VR_FHD_RESOLUTION       (1920*1080)
//#define VR_FHD_BUF_SIZE         (8*1024*1024)
//#define VR_NON_FHD_BUF_SIZE     (6*1024*1024)
#define VR_FHD_BUF_THD          (768*1024)
#define VR_NON_FHD_BUF_THD      (256*1024)
#define VR_RSVD_BUF_SZ          (384*1024)

    MMPF_USBH_UVC_STREAM_CFG *pUVCCfg = MMPF_USBH_GetUVCCFG();
    MFE_COMP_ENC_RESOL  stEncWH;
    MFE_COMP_FPS        stFPS;
    MMP_ULONG ulNearRingThd = VR_NON_FHD_BUF_THD;
    MMP_ULONG ulCompBufSize = 0;
    MMP_BOOL  bFHDEncode = MMP_FALSE;
    MMP_ULONG ulEncBufW = 0;
    MMP_ULONG ulEncBufH = 0;
    MMP_ULONG ulBitrate = 0;
    MMP_ULONG ulMaxCompBufDuration = 0;
    MMP_UBYTE ubCompType = 0;

    switch (usStrmType) {
    case VIDENC_STREAM_PRM_RECD:
        ubCompType = MFE_COMP_PRM_RECD;
        ulEncBufW = m_stAhcH264RecdInfo[MMPS_VR_PRM_RECD].ulVidEncBufW;
        ulEncBufH = m_stAhcH264RecdInfo[MMPS_VR_PRM_RECD].ulVidEncBufH;
        ulMaxCompBufDuration = m_VidRecdRuntimeCfg.ulMaxCompBufDuration[MMPS_VR_PRM_RECD];
        Component_MFE_GetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BITRATE, (void*)&ulBitrate);

        bFHDEncode = ((ulEncBufW*ulEncBufH) >= VR_FHD_RESOLUTION) ? (MMP_TRUE) : (MMP_FALSE);
        ulNearRingThd = (bFHDEncode) ? (VR_FHD_BUF_THD) : (VR_NON_FHD_BUF_THD);
        ulCompBufSize = (ulBitrate >> 3) * ulMaxCompBufDuration + ulNearRingThd + VR_RSVD_BUF_SZ;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_NEARRING_THD, (void*)&ulNearRingThd);
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BUF_SIZE, (void*)&ulCompBufSize);
        break;
    case VIDENC_STREAM_UVC_RECD:
        ubCompType = MFE_COMP_UVC_RECD;
        stFPS.usTimeIncre = pUVCCfg->mRecd.usTimeIncrement;
        stFPS.usTimeResol = pUVCCfg->mRecd.usTimeIncrResol;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_SNR_FPS, (void*)&stFPS);

        MMPF_VIDMGR_GetUVCEncodeResolution(&ulEncBufW,&ulEncBufH);
        stEncWH.ulEncBufW = stEncWH.ulEncW = ulEncBufW;
        stEncWH.ulEncBufH = stEncWH.ulEncH = ulEncBufH;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_RESOLUTION, (void*)&stEncWH);

        ulBitrate = pUVCCfg->mRecd.ulBitrate;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BITRATE, (void*)&ulBitrate);

        ulMaxCompBufDuration = m_VidRecdRuntimeCfg.ulMaxCompBufDuration[MMPS_VR_SCD_RECD];
        bFHDEncode = ((ulEncBufW*ulEncBufH) >= VR_FHD_RESOLUTION) ? (MMP_TRUE) : (MMP_FALSE);
        ulNearRingThd = (bFHDEncode) ? (VR_FHD_BUF_THD) : (VR_NON_FHD_BUF_THD);
        ulCompBufSize = (ulBitrate >> 3) * ulMaxCompBufDuration + ulNearRingThd + VR_RSVD_BUF_SZ;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BUF_SIZE, (void*)&ulCompBufSize);
        break;
    case VIDENC_STREAM_SCD_RECD:
        ubCompType = MFE_COMP_SCD_RECD;
        ulEncBufW = m_stAhcH264RecdInfo[MMPS_VR_SCD_RECD].ulVidEncBufW;
        ulEncBufH = m_stAhcH264RecdInfo[MMPS_VR_SCD_RECD].ulVidEncBufH;
        ulMaxCompBufDuration = m_VidRecdRuntimeCfg.ulMaxCompBufDuration[MMPS_VR_SCD_RECD];
        Component_MFE_GetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BITRATE, (void*)&ulBitrate);

        bFHDEncode = ((ulEncBufW*ulEncBufH) >= VR_FHD_RESOLUTION) ? (MMP_TRUE) : (MMP_FALSE);
        ulNearRingThd = (bFHDEncode) ? (VR_FHD_BUF_THD) : (VR_NON_FHD_BUF_THD);
        ulCompBufSize = (ulBitrate >> 3) * ulMaxCompBufDuration + ulNearRingThd + VR_RSVD_BUF_SZ;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_NEARRING_THD, (void*)&ulNearRingThd);
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BUF_SIZE, (void*)&ulCompBufSize);
        break;
    case VIDENC_STREAM_TRD_RECD:
        ubCompType = MFE_COMP_TRD_RECD;
        ulEncBufW = m_stAhcH264RecdInfo[MMPS_VR_TRD_RECD].ulVidEncBufW;
        ulEncBufH = m_stAhcH264RecdInfo[MMPS_VR_TRD_RECD].ulVidEncBufH;
        ulMaxCompBufDuration = m_VidRecdRuntimeCfg.ulMaxCompBufDuration[MMPS_VR_TRD_RECD];
        Component_MFE_GetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BITRATE, (void*)&ulBitrate);

        bFHDEncode = ((ulEncBufW*ulEncBufH) >= VR_FHD_RESOLUTION) ? (MMP_TRUE) : (MMP_FALSE);
        ulNearRingThd = (bFHDEncode) ? (VR_FHD_BUF_THD) : (VR_NON_FHD_BUF_THD);
        ulCompBufSize = (ulBitrate >> 3) * ulMaxCompBufDuration + ulNearRingThd + VR_RSVD_BUF_SZ;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_NEARRING_THD, (void*)&ulNearRingThd);
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BUF_SIZE, (void*)&ulCompBufSize);
        break;
    case VIDENC_STREAM_WIFI_PRM:
        ubCompType = MFE_COMP_PRM_STREAM;
        ulEncBufW = m_stAhcH264StreamInfo[MMPS_H264_STRM_PRM].ulVidEncBufW;
        ulEncBufH = m_stAhcH264StreamInfo[MMPS_H264_STRM_PRM].ulVidEncBufH;
        ulMaxCompBufDuration = VID_ENC_COMP_BUF_DURATION;
        Component_MFE_GetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BITRATE, (void*)&ulBitrate);

        bFHDEncode = ((ulEncBufW*ulEncBufH) >= VR_FHD_RESOLUTION) ? (MMP_TRUE) : (MMP_FALSE);
        ulNearRingThd = (bFHDEncode) ? (VR_FHD_BUF_THD)  : (VR_NON_FHD_BUF_THD);
        ulCompBufSize = (ulBitrate >> 3) * ulMaxCompBufDuration + ulNearRingThd + VR_RSVD_BUF_SZ;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_NEARRING_THD, (void*)&ulNearRingThd);
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BUF_SIZE, (void*)&ulCompBufSize);
        break;
    case VIDENC_STREAM_WIFI_SCD:
        ubCompType = MFE_COMP_SCD_STREAM;
        ulEncBufW = m_stAhcH264StreamInfo[MMPS_H264_STRM_SCD].ulVidEncBufW;
        ulEncBufH = m_stAhcH264StreamInfo[MMPS_H264_STRM_SCD].ulVidEncBufH;
        ulMaxCompBufDuration = VID_ENC_COMP_BUF_DURATION;
        Component_MFE_GetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BITRATE, (void*)&ulBitrate);

        bFHDEncode = ((ulEncBufW*ulEncBufH) >= VR_FHD_RESOLUTION) ? (MMP_TRUE) : (MMP_FALSE);
        ulNearRingThd = (bFHDEncode) ? (VR_FHD_BUF_THD)  : (VR_NON_FHD_BUF_THD);
        ulCompBufSize = (ulBitrate >> 3) * ulMaxCompBufDuration + ulNearRingThd + VR_RSVD_BUF_SZ;
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_NEARRING_THD, (void*)&ulNearRingThd);
        Component_MFE_SetParam(&Component_MFE[ubCompType], MFE_COMP_PARAM_BUF_SIZE, (void*)&ulCompBufSize);
        break;
    default:
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AllocH264Memory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AllocH264Memory(MMP_ULONG *pulEncId, void* pvCompHandle, MMP_USHORT usStreamType)
{
    const MMP_ULONG             ulSPSSize = VID_ENC_SPS_BUF_SIZE;
    const MMP_ULONG             ulPPSSize = VID_ENC_PPS_BUF_SIZE;
    MMPD_H264ENC_HEADER_BUF     stHeaderBuf;
    void*                       pvParamSetBufVirt = NULL;
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;

    // Initialize H264 instance
    if (MMPF_VIDENC_InitInstance(pulEncId, usStreamType, VIDENC_RC_MODE_CBR, pvCompHandle) != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "MMPF_VIDENC_InitInstance Fail1\r\n");
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }

    if (usStreamType == VIDENC_STREAM_PRM_RECD)
        m_ulPrmRecdID = *pulEncId;
    else if (usStreamType == VIDENC_STREAM_SCD_RECD)
        m_ulScdRecdID = *pulEncId;
    else if (usStreamType == VIDENC_STREAM_TRD_RECD)
        m_ulTrdRecdID = *pulEncId;
    else if (usStreamType == VIDENC_STREAM_WIFI_PRM)
        m_ulH264PrmStreamID = *pulEncId;
    else if (usStreamType == VIDENC_STREAM_WIFI_SCD)
        m_ulH264ScdStreamID = *pulEncId;
    else
        return MMP_ERR_NONE;

    if ((*pulEncId) == INVALID_ENC_ID) {
        MMPS_VR_DBG_ERR(1, "MMPF_VIDENC_InitInstance Fail2\r\n");
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }

    // Set SPS buffer
    eCamOsRet = CamOsDirectMemAlloc("SPS", ulSPSSize, &pvParamSetBufVirt, NULL, NULL);
    CAM_OS_RET_CHK(eCamOsRet);
    stHeaderBuf.ulSPSStart    = (MMP_ULONG)pvParamSetBufVirt;
    stHeaderBuf.ulSPSSize     = ulSPSSize;

    #if (SUPPORT_VUI_INFO)
    // Rebuild-SPS
    eCamOsRet = CamOsDirectMemAlloc("Re-SPS", ulSPSSize + 16, &pvParamSetBufVirt, NULL, NULL);
    CAM_OS_RET_CHK(eCamOsRet);
    stHeaderBuf.ulTmpSPSStart = (MMP_ULONG)pvParamSetBufVirt;
    stHeaderBuf.ulTmpSPSSize  = ulSPSSize + 16;
    #endif

    // Set PPS buffer
    eCamOsRet = CamOsDirectMemAlloc("PPS", ulPPSSize, &pvParamSetBufVirt, NULL, NULL);
    CAM_OS_RET_CHK(eCamOsRet);
    stHeaderBuf.ulPPSStart    = (MMP_ULONG)pvParamSetBufVirt;
    stHeaderBuf.ulPPSSize     = ulPPSSize;

    MMPD_H264ENC_SetHeaderBuf(*pulEncId, &stHeaderBuf);

    MMPS_VR_DBG_MSG(0, "MFE ID %d Type %d SPS 0x%x PPS 0x%x\r\n",
                    *pulEncId,
                    usStreamType,
                    (MMP_ULONG)stHeaderBuf.ulSPSStart,
                    (MMP_ULONG)stHeaderBuf.ulPPSStart);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_FreeH264Memory
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_FreeH264Memory(MMP_ULONG ulEncId)
{
    const MMP_ULONG         SPSSize     = VID_ENC_SPS_BUF_SIZE;
    const MMP_ULONG         PPSSize     = VID_ENC_PPS_BUF_SIZE;
    MMPD_H264ENC_HEADER_BUF stHeaderBuf;
    CamOsRet_e              eCamOsRet = CAM_OS_OK;

    MMPD_H264ENC_GetHeaderBuf(ulEncId, &stHeaderBuf);

    // Free SPS buffer
    if (stHeaderBuf.ulSPSStart) {
        eCamOsRet = CamOsDirectMemRelease((void*)stHeaderBuf.ulSPSStart, SPSSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    #if (SUPPORT_VUI_INFO)
    // Free Rebuild-SPS
    if (stHeaderBuf.ulTmpSPSStart) {
        eCamOsRet = CamOsDirectMemRelease((void*)stHeaderBuf.ulTmpSPSStart, SPSSize + 16);
        CAM_OS_RET_CHK(eCamOsRet);
    }
    #endif

    // Free PPS buffer
    if (stHeaderBuf.ulPPSStart) {
        eCamOsRet = CamOsDirectMemRelease((void*)stHeaderBuf.ulPPSStart, PPSSize);
        CAM_OS_RET_CHK(eCamOsRet);
    }

    stHeaderBuf.ulSPSStart    = 0;
    stHeaderBuf.ulSPSSize     = 0;
    stHeaderBuf.ulPPSStart    = 0;
    stHeaderBuf.ulPPSSize     = 0;
    MMPD_H264ENC_SetHeaderBuf(ulEncId, &stHeaderBuf);

    MMPS_VR_DBG_MSG(0, "Free MFE ID [%d] SPS/PPS Buffer\r\n", ulEncId);

    return MMP_ERR_NONE;
}

#if 0
void ____VR_Common_Record_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_CustomedEncResol
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set VideoR encode resolution
 @param[in] ubEncIdx    Encode instance ID
 @param[in] sFitMode    Scaler fit mode
 @param[in] usWidth     Encode width
 @param[in] usHeight    Encode height
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_CustomedEncResol(MMP_UBYTE ubCamSel, MMP_UBYTE stFitMode, MMP_USHORT usWidth, MMP_USHORT usHeight)
{
    MMP_UBYTE           ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);
    MFE_COMP_ENC_RESOL  stMfeResol;
    MFE_COMP_PIXFMT     ePixFmt = MFE_COMP_PIXFMT_NV12;
    MMP_ULONG           ulWAlignBase = MFE_COMP_W_ALIGN_BASE_NV12;
    MMP_ULONG           ulHAlignBase = MFE_COMP_H_ALIGN_BASE_NV12;

    Component_MFE_GetParam(&Component_MFE[MFE_COMP_PRM_RECD + ubRecdSel], MFE_COMP_PARAM_PIX_FMT, (void*)&ePixFmt);

    if (ePixFmt == MFE_COMP_PIXFMT_NV12 ||
        ePixFmt == MFE_COMP_PIXFMT_NV21) {
        ulWAlignBase = MFE_COMP_W_ALIGN_BASE_NV12;
        ulHAlignBase = MFE_COMP_H_ALIGN_BASE_NV12;
    }
    else {
        ulWAlignBase = MFE_COMP_W_ALIGN_BASE_YUV422;
        ulHAlignBase = MFE_COMP_H_ALIGN_BASE_YUV422;
    }

    m_stAhcH264RecdInfo[ubRecdSel].sFitMode       = stFitMode;
    m_stAhcH264RecdInfo[ubRecdSel].ulVidEncW      = usWidth;
    m_stAhcH264RecdInfo[ubRecdSel].ulVidEncH      = usHeight;
    m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW   = ALIGN_X(usWidth, ulWAlignBase);
    m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH   = ALIGN_X(usHeight, ulHAlignBase);

    stMfeResol.ulEncW    = m_stAhcH264RecdInfo[ubRecdSel].ulVidEncW;
    stMfeResol.ulEncH    = m_stAhcH264RecdInfo[ubRecdSel].ulVidEncH;
    stMfeResol.ulEncBufW = m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufW;
    stMfeResol.ulEncBufH = m_stAhcH264RecdInfo[ubRecdSel].ulVidEncBufH;
    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_RECD + ubRecdSel], MFE_COMP_PARAM_RESOLUTION, (void*)&stMfeResol);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnableRecordPipe
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Turn on and off record for video encode.

 @param[in] bEnable Enable and disable scaler path for video encode.
 @retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPS_3GPRECD_EnableRecordPipe(MMP_UBYTE ubCamSel, MMP_BOOL bEnable)
{
    MMP_UBYTE ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);

    if (m_bVidRecordActive[ubRecdSel] ^ bEnable) {
        m_bVidRecordActive[ubRecdSel] = bEnable;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetMaxCompBufDuration
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetMaxCompBufDuration(MMP_UBYTE ubCamSel, MMP_ULONG ulDuration)
{
    MMP_UBYTE ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);

    m_VidRecdRuntimeCfg.ulMaxCompBufDuration[ubRecdSel] = ulDuration;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetBitrate
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetBitrate(MMP_UBYTE ubCamSel, MMP_ULONG ulBitrate)
{
    MMP_UBYTE ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);
    MMP_ULONG ulMfeBitrate = ulBitrate;

    m_VidRecdRuntimeCfg.ulBitrate[ubRecdSel] = ulMfeBitrate;

    Component_MFE_SetParam(&Component_MFE[ubRecdSel], MFE_COMP_PARAM_BITRATE, (void*)&ulMfeBitrate);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetFrameRatePara
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set frame rate for recorded video.
 @param[in] pSnr_fps Sensor input frame rate
 @param[in] pEnc_fps Expected encode frame rate (normal/timelapse/slow motion)
 @param[in] pMgr_fps Frame rate for playback
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetFrameRatePara(MMP_UBYTE                 ubCamSel,
                                      MMPS_3GPRECD_FRAMERATE    *pSnr_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pEnc_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pMgr_fps)
{
    MMP_UBYTE       ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);
    MFE_COMP_FPS    stMfeFps;

    if ((pSnr_fps->ulTimeIncre == 0) ||
        (pSnr_fps->ulTimeResol == 0) ||
        (pEnc_fps->ulTimeIncre == 0) ||
        (pEnc_fps->ulTimeResol == 0) ||
        (pMgr_fps->ulTimeIncre == 0) ||
        (pMgr_fps->ulTimeResol == 0)) {
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }

    m_VidRecdRuntimeCfg.SnrFrameRate[ubRecdSel].ulTimeIncre = pSnr_fps->ulTimeIncre;
    m_VidRecdRuntimeCfg.SnrFrameRate[ubRecdSel].ulTimeResol = pSnr_fps->ulTimeResol;
    m_VidRecdRuntimeCfg.EncFrameRate[ubRecdSel].ulTimeIncre = pEnc_fps->ulTimeIncre;
    m_VidRecdRuntimeCfg.EncFrameRate[ubRecdSel].ulTimeResol = pEnc_fps->ulTimeResol;
    m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeIncre = pMgr_fps->ulTimeIncre;
    m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeResol = pMgr_fps->ulTimeResol;

    stMfeFps.usTimeIncre = pSnr_fps->ulTimeIncre;
    stMfeFps.usTimeResol = pSnr_fps->ulTimeResol;
    Component_MFE_SetParam(&Component_MFE[ubRecdSel], MFE_COMP_PARAM_SNR_FPS, (void*)&stMfeFps);

    stMfeFps.usTimeIncre = pEnc_fps->ulTimeIncre;
    stMfeFps.usTimeResol = pEnc_fps->ulTimeResol;
    Component_MFE_SetParam(&Component_MFE[ubRecdSel], MFE_COMP_PARAM_ENC_FPS, (void*)&stMfeFps);

    stMfeFps.usTimeIncre = pMgr_fps->ulTimeIncre;
    stMfeFps.usTimeResol = pMgr_fps->ulTimeResol;
    Component_MFE_SetParam(&Component_MFE[ubRecdSel], MFE_COMP_PARAM_MGR_FPS, (void*)&stMfeFps);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetPFrameCount
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set P frame count of one cycle.
 @param[in] usFrameCount Count of P frame.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetPFrameCount(MMP_UBYTE ubCamSel, MMP_USHORT usFrmCnt)
{
    MMP_UBYTE ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);
    MMP_ULONG ulMfePFrmCnt = usFrmCnt;

    m_VidRecdRuntimeCfg.usPFrameCount[ubRecdSel] = usFrmCnt;

    Component_MFE_SetParam(&Component_MFE[ubRecdSel], MFE_COMP_PARAM_P_FRM_CNT, (void*)&ulMfePFrmCnt);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetBFrameCount
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set B frame count per P frame.
 @param[in] usFrameCount Count of B frame.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetBFrameCount(MMP_UBYTE ubCamSel, MMP_USHORT usFrmCnt)
{
    MMP_UBYTE ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);

    m_VidRecdRuntimeCfg.usBFrameCount[ubRecdSel] = 0;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetProfile
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set profile for video encode.
 @param[in] eProfile Visual profile for the specified encoder.
 @retval none.
*/
MMP_ERR MMPS_3GPRECD_SetProfile(MMP_UBYTE ubCamSel, VIDENC_PROFILE eProfile)
{
    MMP_UBYTE           ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);
    MFE_COMP_PROFILE    eMfeProfile = (MFE_COMP_PROFILE)eProfile;

    m_VidRecdRuntimeCfg.eVisualProfile[ubRecdSel] = eProfile;

    Component_MFE_SetParam(&Component_MFE[ubRecdSel], MFE_COMP_PARAM_PROFILE, (void*)&eMfeProfile);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetContainerType
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetContainerType(VIDMGR_CONTAINER_TYPE eType)
{
    switch (eType) {
    case VIDMGR_CONTAINER_TS:
        MMPF_VIDMGR_SetClearCachePeriod(FS_CLEAR_CACHE_PERIOD);
    case VIDMGR_CONTAINER_3GP:
    case VIDMGR_CONTAINER_AVI:
        MMPF_VIDMGR_SetContainerType(eType);
        break;
    case VIDMGR_CONTAINER_NONE:
    default:
        MMPF_VIDMGR_SetContainerType(VIDMGR_CONTAINER_NONE);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetFileName
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Send encoded 3GP file name to firmware for card mode and creat file time.
 @param[in] bFilename File name.
 @param[in] usLength Length of file name in unit of byte.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetFileName(MMP_USHORT usStreamType, MMP_BYTE bFilename[], MMP_USHORT usLength)
{
    MMP_ULONG   ulFileNameAddr = 0;
    MMP_ULONG   ulFileNameSize = 0;
    void*       pvFileNameVirt = NULL;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    // Allocate memory for File name buffer
    MMPD_3GPMGR_GetTempFileNameAddr(&ulFileNameAddr, &ulFileNameSize);

    if (ulFileNameAddr == 0) {

        ulFileNameSize = MAX_3GPRECD_FILENAME_LENGTH;

        eCamOsRet = CamOsDirectMemAlloc("FileName", ulFileNameSize, &pvFileNameVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_3GPMGR_SetTempFileNameAddr((MMP_ULONG)pvFileNameVirt, ulFileNameSize);
    }

    MMPS_FS_SetCreationTime();

    return MMPD_3GPMGR_SetFileName(usStreamType, bFilename, usLength);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetUserDataAtom
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Send user data atom to firmware for card mode.
 @param[in] usStreamType Stream type.
 @param[in] bAtomName atom name, maximum 4 bytes.
 @param[in] bUserDataBuf user data atom buffer.
 @param[in] usUserDataLength Length of user data atom.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetUserDataAtom(MMP_USHORT usStreamType, MMP_BYTE bAtomName[], MMP_BYTE bUserDataBuf[], MMP_USHORT usUserDataLength)
{
    return MMPD_3GPMGR_SetUserDataAtom(usStreamType, bAtomName, bUserDataBuf, usUserDataLength);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetStoragePath
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Save encoded 3GP file to card mode or streaming mode.
 @param[in] SrcMode Card or streaming mode.
 @retval MMP_ERR_NONE Success.
 @note
 The parameter @a SrcMode can be:
 - VIDENC_OUT_MODE_CARD : save file to storage.
*/
MMP_ERR MMPS_3GPRECD_SetStoragePath(VIDENC_OUT_MODE eOutMode)
{
    m_VidRecdRuntimeCfg.eVideoOutMode[0] = eOutMode;
    m_VidRecdRuntimeCfg.eVideoOutMode[1] = eOutMode;
    m_VidRecdRuntimeCfg.eVideoOutMode[2] = eOutMode;

    MMPF_VIDMGR_SetStoragePath((MMP_UBYTE)m_VidRecdRuntimeCfg.eVideoOutMode[0]);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetReservedStorageSpace
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set reserved storage space which recorder or other system can not use it
        during recording. Ex. if user wants to reserve 10MB while 100MB free space,
        then total 90MB remained for recording & capture in recording to share.
 @pre MMPS_3GPRECD_SetStoragePath(VIDENC_OUT_MODE_CARD) was called, for card mode only
 @param[in] ulRsvdSize Reserved storage space.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetReservedStorageSpace(MMP_ULONG ulRsvdSize)
{
    if (m_VidRecdRuntimeCfg.eVideoOutMode[0] == VIDENC_OUT_MODE_CARD) {
        m_VidRecdRuntimeCfg.ulReservedSpace = ulRsvdSize;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetFileSizeLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the maximum 3GP file size for video encoding.
 @param[in] ulSizeLimit Maximum file size.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetFileSizeLimit(MMP_ULONG ulSizeLimit)
{
    MMP_ULONG64 u64MaxTimeLimit = 0, u64MaxSizeLimit = 0;

    MMPS_3GPRECD_GetMaxFileSizeTimeLimit(&u64MaxSizeLimit, &u64MaxTimeLimit);

    if ((u64MaxSizeLimit > 2*1024*1024) && (u64MaxSizeLimit < ulSizeLimit)) { // One clip at least 2 MB
        m_VidRecdRuntimeCfg.ulSizeLimit = u64MaxSizeLimit;
    }
    else {
        m_VidRecdRuntimeCfg.ulSizeLimit = ulSizeLimit;
    }

    MMPS_VR_DBG_MSG(0, "Size Limit [%d] bytes\r\n", m_VidRecdRuntimeCfg.ulSizeLimit);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetFileTimeLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the maximum 3GP file time for video encoding.
 @param[in] ulTimeLimitMs Maximum file time in unit of ms.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE Space not enough.

 @warn If ulTimeLimitMs is set to 0, then it doesn't take any effect.
*/
MMP_ERR MMPS_3GPRECD_SetFileTimeLimit(MMP_ULONG ulTimeLimitMs)
{
    if (ulTimeLimitMs) {
        m_VidRecdRuntimeCfg.ulTimeLimitMs = ulTimeLimitMs;
        MMPF_VIDMGR_SetAVFileTimeLimit(ulTimeLimitMs);
        return MMP_ERR_NONE;
    }

    return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_ChangeCurFileTimeLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Change the maximum 3GP file time for current video encoding .
 @param[in] ulTimeLimitMs Maximum file time in unit of ms.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE Space not enough.
*/
MMP_ERR MMPS_3GPRECD_ChangeCurFileTimeLimit(MMP_ULONG ulTimeLimitMs)
{
    if (ulTimeLimitMs) {
        return MMPD_3GPMGR_SetTimeDynamicLimit(ulTimeLimitMs);
    }

    return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_Set3GPCreateModifyTimeInfo
//  Description : Set creation time and modification time of 3GP file.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_Set3GPCreateModifyTimeInfo(MMP_USHORT usStreamType, AUTL_DATETIME stDateTimeNew)
{
    MMP_ULONG       ulCreateTime = 0, ulModifyTime = 0;
    MMP_ULONG       ulSeconds = 0;
    AUTL_DATETIME   stDateTimeBase = {2017, 1, 1, 0, 0, 0, 0, 0, 0};

    stDateTimeBase.usYear     = 1904;
    stDateTimeBase.usMonth    = 1;
    stDateTimeBase.usDay      = 1;
    stDateTimeBase.usHour     = 0;
    stDateTimeBase.usMinute   = 0;
    stDateTimeBase.usSecond   = 0;

    ulSeconds = AUTL_Calendar_DateToSeconds(&stDateTimeNew, &stDateTimeBase);
    ulCreateTime = ulSeconds;
    ulModifyTime = ulSeconds;

    MMPS_VR_DBG_MSG(0, "Create & Modify time [%d]\r\n", ulSeconds);

    return MMPF_VIDMGR_Set3GPCreateModifyTimeInfo(usStreamType, ulCreateTime, ulModifyTime);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetParameter
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get record parameter.
 @param[in] type    the specific parameter type.
 @param[in] param   Parameter value to update.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetParameter(MMP_UBYTE ubRecdSel, MMPS_3GPRECD_PARAMETER eParamType, MMP_ULONG *pulValue)
{
    MMP_ULONG ulParam = 0;

    switch (eParamType) {
    case MMPS_3GPRECD_PARAMETER_PREVIEWMODE:
        ulParam = m_VidRecdRuntimeCfg.usVideoPreviewMode;
        break;
    case MMPS_3GPRECD_PARAMETER_BITRATE:
        ulParam = m_VidRecdRuntimeCfg.ulBitrate[ubRecdSel];
        break;
    default:
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }

    if (pulValue) {
        *pulValue = ulParam;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_UpdateParameter
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Update record parameter dynamically. This function should not be used if
        recording is not yet started.
 @param[in] type    the specific parameter type.
 @param[in] param   Parameter value to update.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_UpdateParameter(MMP_ULONG ulStreamType, MMPS_3GPRECD_PARAMETER eParamType, void *param)
{
    MMP_ULONG               ulEncId = 0;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    VIDENC_FW_STATUS        eVidStatus = VIDENC_FW_STATUS_NONE;
    MMP_ULONG               ulBitrate = 0;
    MMPS_3GPRECD_FRAMERATE  *pstFps = NULL;

    if (ulStreamType == VIDENC_STREAM_PRM_RECD) {
        if (m_ulPrmRecdID == INVALID_ENC_ID)
            eVidStatus = VIDENC_FW_STATUS_NONE;
        else
            eVidStatus = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

        ulEncId = m_ulPrmRecdID;
    }
    else if (ulStreamType == VIDENC_STREAM_SCD_RECD) {
        if (m_ulScdRecdID == INVALID_ENC_ID)
            eVidStatus = VIDENC_FW_STATUS_NONE;
        else
            eVidStatus = MMPF_VIDENC_GetStatus(m_ulScdRecdID);

        ulEncId = m_ulScdRecdID;
    }
    else if (ulStreamType == VIDENC_STREAM_TRD_RECD) {
        if (m_ulTrdRecdID == INVALID_ENC_ID)
            eVidStatus = VIDENC_FW_STATUS_NONE;
        else
            eVidStatus = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);

        ulEncId = m_ulTrdRecdID;
    }
    #if (SUPPORT_H264_WIFI_STREAM)
    else if (ulStreamType == VIDENC_STREAM_WIFI_PRM) {
        if (m_ulH264PrmStreamID == INVALID_ENC_ID)
            eVidStatus = VIDENC_FW_STATUS_NONE;
        else
            eVidStatus = MMPF_VIDENC_GetStatus(m_ulH264PrmStreamID);

        ulEncId = m_ulH264PrmStreamID;
    }
    else if (ulStreamType == VIDENC_STREAM_WIFI_SCD) {
        if (m_ulH264ScdStreamID == INVALID_ENC_ID)
            eVidStatus = VIDENC_FW_STATUS_NONE;
        else
            eVidStatus = MMPF_VIDENC_GetStatus(m_ulH264ScdStreamID);

        ulEncId = m_ulH264ScdStreamID;
    }
    #endif
    else {
        return eRetErr;
    }

    if ((eVidStatus == VIDENC_FW_STATUS_NONE) ||
        (eVidStatus == VIDENC_FW_STATUS_STOP)) {
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    switch (eParamType) {
    case MMPS_3GPRECD_PARAMETER_BITRATE:
        if ((MMP_ULONG)param == 0) {
            return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
        }

        if (ulStreamType == VIDENC_STREAM_PRM_RECD) {
            m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_PRM_RECD] = (MMP_ULONG)param;
            ulBitrate = m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_PRM_RECD];
        }
        else if (ulStreamType == VIDENC_STREAM_SCD_RECD) {
            m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_SCD_RECD] = (MMP_ULONG)param;
            ulBitrate = m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_SCD_RECD];
        }
        else if (ulStreamType == VIDENC_STREAM_TRD_RECD) {
            m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_TRD_RECD] = (MMP_ULONG)param;
            ulBitrate = m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_TRD_RECD];
        }
        #if (SUPPORT_H264_WIFI_STREAM)
        else if (ulStreamType == VIDENC_STREAM_WIFI_PRM) {
            m_stH264StreamObj[MMPS_H264_STRM_PRM].stEncCfg.ulBitrate = (MMP_ULONG)param;
            ulBitrate = m_stH264StreamObj[MMPS_H264_STRM_PRM].stEncCfg.ulBitrate;
        }
        else if (ulStreamType == VIDENC_STREAM_WIFI_SCD) {
            m_stH264StreamObj[MMPS_H264_STRM_SCD].stEncCfg.ulBitrate = (MMP_ULONG)param;
            ulBitrate = m_stH264StreamObj[MMPS_H264_STRM_SCD].stEncCfg.ulBitrate;
        }
        #endif

        eRetErr = MMPF_VIDENC_SetBitRate(MMPF_H264ENC_GetHandle(ulEncId), ulBitrate);
        break;
    case MMPS_3GPRECD_PARAMETER_FRAME_RATE:
        pstFps = (MMPS_3GPRECD_FRAMERATE *)param;

        if ((pstFps->ulTimeIncre == 0) || (pstFps->ulTimeResol == 0)) {
            return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
        }

        // Update encode frame rate
        eRetErr = MMPF_VIDENC_UpdateEncFrameRate(MMPF_H264ENC_GetHandle(ulEncId),
                                                 pstFps->ulTimeIncre,
                                                 pstFps->ulTimeResol);

        if (ulStreamType == VIDENC_STREAM_PRM_RECD) {
            m_VidRecdRuntimeCfg.EncFrameRate[MMPS_VR_PRM_RECD].ulTimeIncre = pstFps->ulTimeIncre;
            m_VidRecdRuntimeCfg.EncFrameRate[MMPS_VR_PRM_RECD].ulTimeResol = pstFps->ulTimeResol;
        }
        else if (ulStreamType == VIDENC_STREAM_SCD_RECD && MMPF_VIDMGR_IsShareRecdEn() == MMP_FALSE) {
            m_VidRecdRuntimeCfg.EncFrameRate[MMPS_VR_SCD_RECD].ulTimeIncre = pstFps->ulTimeIncre;
            m_VidRecdRuntimeCfg.EncFrameRate[MMPS_VR_SCD_RECD].ulTimeResol = pstFps->ulTimeResol;
        }
        else if (ulStreamType == VIDENC_STREAM_TRD_RECD) {
            m_VidRecdRuntimeCfg.EncFrameRate[MMPS_VR_TRD_RECD].ulTimeIncre = pstFps->ulTimeIncre;
            m_VidRecdRuntimeCfg.EncFrameRate[MMPS_VR_TRD_RECD].ulTimeResol = pstFps->ulTimeResol;
        }
        #if (SUPPORT_H264_WIFI_STREAM)
        else if (ulStreamType == VIDENC_STREAM_WIFI_PRM) {
            m_stH264StreamObj[MMPS_H264_STRM_PRM].stEncCfg.EncFrameRate.ulTimeIncre = pstFps->ulTimeIncre;
            m_stH264StreamObj[MMPS_H264_STRM_PRM].stEncCfg.EncFrameRate.ulTimeResol = pstFps->ulTimeResol;
        }
        else if (ulStreamType == VIDENC_STREAM_WIFI_SCD) {
            m_stH264StreamObj[MMPS_H264_STRM_SCD].stEncCfg.EncFrameRate.ulTimeIncre = pstFps->ulTimeIncre;
            m_stH264StreamObj[MMPS_H264_STRM_SCD].stEncCfg.EncFrameRate.ulTimeResol = pstFps->ulTimeResol;
        }
        #endif
        break;
    default:
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetRecordSpeed
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetRecordSpeed(VIDENC_SPEED_MODE eSpeedMode, VIDENC_SPEED_RATIO eSpeedRatio)
{
    if (eSpeedMode == VIDENC_SPEED_SLOW) {
        MMPS_VR_DBG_MSG(1, "Not Support H264 Slow Record Mode\r\n");
        MMPF_VIDMGR_SetVideoEncodeSpeed(VIDENC_SPEED_NORMAL, VIDENC_SPEED_1X);
    }
    else {
        MMPF_VIDMGR_SetVideoEncodeSpeed(eSpeedMode, eSpeedRatio);
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartSeamless
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start video seamless recording,
        can be called before or after @ref MMPS_3GPRECD_StartRecord
 @param[in] bStart start or stop
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetSeamlessEnable(MMP_BOOL bStart)
{
    if (m_VidRecdPresetCfg.bSeamlessMode == MMP_TRUE) {
        MMPF_VIDMGR_SetSeamlessEnable(bStart);
        return MMP_ERR_NONE;
    }

    return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_RegisterCallback
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set callback for recording events

The function set callback for the following events.
    * media full  : record stopped due to card full (Task)
    * file full   : record stopped due to the specified time/space limitation (Task)
    * media slow  : record stopped due to the insufficient speed of media (ISR)
    * media error : record stopped due to some error in media writing (Task)
    * seamless    : to trigger the next recording in seamless mode (Task)
    * encode start: encoder started (Task/ISR)
    * encode stop : encoder stopped (ISR)
    * postprocess : for appending the user data in the file tail (Task)

@param[in] Event    Specified the event for register.
@param[in] CallBack The callback to be executed when the specified event happens.

@return It reports the status of the operation.

@warn The registered callback will not be auto deleted, please register a NULL
      to delete it.
*/
MMP_ERR MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT eEvent, void *pvCallBack)
{
    return MMPF_VIDMGR_RegisterCallback(eEvent, pvCallBack);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetNormalSkipFrmParam
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable video record skip mode to set total skip count and continuous skip count.

 @param[in] ulTotalCount - limitation of total skip count
 @param[in] ulContiCount - limitation of continuous skip count
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_SetNormalSkipFrmParam(MMP_ULONG ulTotalCount, MMP_ULONG ulContiCount)
{
    return MMPF_H264ENC_SetNormalFrmSkipCountThd(ulTotalCount, ulContiCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetSeamlessSkipFrmParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetSeamlessSkipFrmParam(MMP_ULONG ulTotalCount, MMP_ULONG ulContiCount)
{
    return MMPF_H264ENC_SetSeamlessFrmSkipCountThd(ulTotalCount, ulContiCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetH264EncUseMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetH264EncUseMode(MMP_USHORT usStreamType, MMP_ULONG ulEncUseMode)
{
    MMPF_VIDMGR_SetEncUseMode(usStreamType, ulEncUseMode);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetMuxer3gpConstFps
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetMuxerConstFps(MMP_BOOL bEnable)
{
    MMPF_VIDMGR_SetMuxConstFPS(bEnable);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetMgrMultiTrackEn
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetMgrMultiTrackEn(MMP_BOOL bEnable)
{
    MMPF_VIDMGR_SetMultiTrackEn(bEnable);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetAVSyncMethod
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetAVSyncMethod(VIDMGR_AVSYNC_METHOD eAVSyncMethod)
{
    MMPF_VIDMGR_SetAVSyncMethod((MMP_UBYTE)eAVSyncMethod);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetAudioFormat
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set audio mode to be AMR or AAC.
 @param[in] Format Assign the audio type is AMR or AAC with video encoder.
 @param[in] Option Assign audio sampling rate and bit rate.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_INVALID_PARAMETERS Invalid parameter.
 @note

 The parameter @a Option support:
 - MMPS_3GPRECD_AUDIO_AAC_22d05K_64K : 22.05KHz with 64kbps
 - MMPS_3GPRECD_AUDIO_AAC_22d05K_128K : 22.05KHz with 128kbps
 - MMPS_3GPRECD_AUDIO_AAC_32K_64K : 32KHz with 64kbps
 - MMPS_3GPRECD_AUDIO_AAC_32K_128K : 32KHz with 128kbps
 - MMPS_3GPRECD_AUDIO_AMR_4d75K : 4.75 KHz
 - MMPS_3GPRECD_AUDIO_AMR_5d15K : 5.15 KHz
 - MMPS_3GPRECD_AUDIO_AMR_12d2K : 12.2 KHz
*/
MMP_ERR MMPS_3GPRECD_SetAudioFormat(MMPS_3GPRECD_AUDIO_FORMAT eAudFmt, MMPS_3GPRECD_AUDIO_OPTION eOption)
{
    MMP_ULONG   ulAudioParam = 0;
    MMP_USHORT  usAudioMode = MMPS_AUDIO_AAC_RECORD_32K_128K;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (eAudFmt == MMPS_3GPRECD_AUDIO_FORMAT_AAC) {

        MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_VAAC_ENCODE);

        switch (eOption) {
        case MMPS_3GPRECD_AUDIO_AAC_16K_32K:
            usAudioMode = MMPS_AUDIO_AAC_RECORD_16K_32K;
            ulAudioParam = 16000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 32000;
            break;
        case MMPS_3GPRECD_AUDIO_AAC_16K_64K:
            usAudioMode = MMPS_AUDIO_AAC_RECORD_16K_64K;
            ulAudioParam = 16000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 64000;
            break;
        case MMPS_3GPRECD_AUDIO_AAC_22d05K_64K:
            usAudioMode   = MMPS_AUDIO_AAC_RECORD_22K_64K;
            ulAudioParam  = 22050;
            m_VidRecdRuntimeCfg.ulAudBitrate = 64000;
            break;
        case MMPS_3GPRECD_AUDIO_AAC_22d05K_128K:
            usAudioMode   = MMPS_AUDIO_AAC_RECORD_22K_128K;
            ulAudioParam  = 22050;
            m_VidRecdRuntimeCfg.ulAudBitrate = 128000;
            break;
        case MMPS_3GPRECD_AUDIO_AAC_32K_64K:
            usAudioMode   = MMPS_AUDIO_AAC_RECORD_32K_64K;
            ulAudioParam  = 32000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 64000;
            break;
        case MMPS_3GPRECD_AUDIO_AAC_32K_128K:
            usAudioMode   = MMPS_AUDIO_AAC_RECORD_32K_128K;
            ulAudioParam  = 32000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 128000;
            MMPD_AUDIO_SetPLL(ulAudioParam);
            break;
        case MMPS_3GPRECD_AUDIO_AAC_48K_128K:
            usAudioMode   = MMPS_AUDIO_AAC_RECORD_48K_128K;
            ulAudioParam  = 48000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 128000;
            break;
        default:
            eRetErr = MMP_3GPMGR_ERR_PARAMETER;
            break;
        }

        MMPD_AUDIO_SetEncodeFileSize(0xFFFFFFFF);
        MMPD_AUDIO_SetEncodeMode(usAudioMode);
        eRetErr |= MMPD_3GPMGR_SetAudioParam(ulAudioParam, MMPD_3GPMGR_AUDIO_FORMAT_AAC);

        m_eVidRecdAudioFmt = MMPS_3GPRECD_AUDIO_FORMAT_AAC;
    }
    else if (eAudFmt == MMPS_3GPRECD_AUDIO_FORMAT_AMR) {

        MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_VAMR_ENCODE);

        switch (eOption) {
        case MMPS_3GPRECD_AUDIO_AMR_4d75K:
            usAudioMode   = MMPS_AUDIO_AMR_MR475_ENCODE_MODE;
            ulAudioParam  = 13;
            m_VidRecdRuntimeCfg.ulAudBitrate = 4750;
            break;
        case MMPS_3GPRECD_AUDIO_AMR_5d15K:
            usAudioMode   = MMPS_AUDIO_AMR_MR515_ENCODE_MODE;
            ulAudioParam  = 14;
            m_VidRecdRuntimeCfg.ulAudBitrate = 5150;
            break;
        case MMPS_3GPRECD_AUDIO_AMR_12d2K:
            usAudioMode   = MMPS_AUDIO_AMR_MR122_ENCODE_MODE;
            ulAudioParam  = 32;
            m_VidRecdRuntimeCfg.ulAudBitrate = 1220;
            break;
        default:
            eRetErr = MMP_3GPMGR_ERR_PARAMETER;
            break;
        }

        MMPD_AUDIO_SetEncodeMode(usAudioMode);
        eRetErr |= MMPD_3GPMGR_SetAudioParam(ulAudioParam, MMPD_3GPMGR_AUDIO_FORMAT_AMR);

        m_eVidRecdAudioFmt = MMPS_3GPRECD_AUDIO_FORMAT_AMR;
    }
    else if (eAudFmt == MMPS_3GPRECD_AUDIO_FORMAT_ADPCM) {

        MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_VADPCM_ENCODE);

        switch (eOption) {
        case MMPS_3GPRECD_AUDIO_ADPCM_16K_22K:
            usAudioMode   = MMPS_3GPRECD_AUDIO_ADPCM_16K_22K;
            ulAudioParam  = 16000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 128000;
            break;
        case MMPS_3GPRECD_AUDIO_ADPCM_32K_22K:
            usAudioMode   = MMPS_3GPRECD_AUDIO_ADPCM_32K_22K;
            ulAudioParam  = 32000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 256000;
            break;
        case MMPS_3GPRECD_AUDIO_ADPCM_44d1K_22K:
            usAudioMode   = MMPS_3GPRECD_AUDIO_ADPCM_44d1K_22K;
            ulAudioParam  = 44100;
            m_VidRecdRuntimeCfg.ulAudBitrate = 352800;
            break;
        case MMPS_3GPRECD_AUDIO_ADPCM_48K_22K:
            usAudioMode   = MMPS_3GPRECD_AUDIO_ADPCM_48K_22K;
            ulAudioParam  = 48000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 384000;
            break;
        default:
            eRetErr = MMP_3GPMGR_ERR_PARAMETER;
            break;
        }

        MMPD_AUDIO_SetEncodeFileSize(0xFFFFFFFF);
        MMPD_AUDIO_SetEncodeMode(usAudioMode);
        eRetErr |= MMPD_3GPMGR_SetAudioParam(ulAudioParam, MMPD_3GPMGR_AUDIO_FORMAT_ADPCM);

        m_eVidRecdAudioFmt = MMPS_3GPRECD_AUDIO_FORMAT_ADPCM;
    }
    else if (eAudFmt == MMPS_3GPRECD_AUDIO_FORMAT_MP3) {

        MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_VMP3_ENCODE);

        switch (eOption) {
        case MMPS_3GPRECD_AUDIO_MP3_32K_128K:
            usAudioMode   = MMPS_AUDIO_MP3_RECORD_32K_128K;
            ulAudioParam  = 32000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 128000;
            break;
        case MMPS_3GPRECD_AUDIO_MP3_44d1K_128K:
            usAudioMode   = MMPS_AUDIO_MP3_RECORD_44d1K_128K;
            ulAudioParam  = 44100;
            m_VidRecdRuntimeCfg.ulAudBitrate = 128000;
            break;
        default:
            eRetErr = MMP_3GPMGR_ERR_PARAMETER;
            break;
        }

        MMPD_AUDIO_SetEncodeFileSize(0xFFFFFFFF);
        MMPD_AUDIO_SetEncodeMode(usAudioMode);
        eRetErr |= MMPD_3GPMGR_SetAudioParam(ulAudioParam, MMPD_3GPMGR_AUDIO_FORMAT_MP3);

        m_eVidRecdAudioFmt = MMPS_3GPRECD_AUDIO_FORMAT_MP3;
    }
    else if (eAudFmt == MMPS_3GPRECD_AUDIO_FORMAT_PCM) {

        MMPD_AUDIO_SetEncodeFormat(MMP_AUDIO_VPCM_ENCODE);

        switch (eOption) {
        case MMPS_3GPRECD_AUDIO_PCM_16K:
            usAudioMode   = MMPS_AUDIO_WAV_RECORD_16K;
            ulAudioParam  = 16000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 16000 * 2 * 2; // 2ch 16-bit sample
            break;
        case MMPS_3GPRECD_AUDIO_PCM_32K:
            usAudioMode   = MMPS_AUDIO_WAV_RECORD_32K;
            ulAudioParam  = 32000;
            m_VidRecdRuntimeCfg.ulAudBitrate = 32000 * 2 * 2; // 2ch 16-bit sample
            break;
        default:
            eRetErr = MMP_3GPMGR_ERR_PARAMETER;
            break;
        }

        MMPD_AUDIO_SetEncodeFileSize(0xFFFFFFFF);
        MMPD_AUDIO_SetEncodeMode(usAudioMode);
        eRetErr |= MMPD_3GPMGR_SetAudioParam(ulAudioParam, MMPD_3GPMGR_AUDIO_FORMAT_PCM);

        m_eVidRecdAudioFmt = MMPS_3GPRECD_AUDIO_FORMAT_PCM;
    }
    else {
        eRetErr = MMP_3GPMGR_ERR_PARAMETER;
    }

    if (eRetErr == MMP_ERR_NONE) {
        return MMP_ERR_NONE;
    }
    else {
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetAudioRecMode
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable audio encode.
 @param[in] bEnable Enable video record with audio.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetAudioRecMode(MMPS_3GPRECD_AUDIO_DATATYPE eMode)
{
    if (eMode != MMPS_3GPRECD_NO_AUDIO_DATA) {
        MMPD_AUDIO_SetInPath(MMPS_Audio_GetConfig()->AudioInPath);
        MMPF_VIDMGR_SetAudioSyncEncode(MMP_TRUE);
    }
    else {
        m_VidRecdRuntimeCfg.ulAudBitrate = 0;
        MMPF_VIDMGR_SetAudioSyncEncode(MMP_FALSE);
    }

    if (eMode == MMPS_3GPRECD_SILENCE_AUDIO_DATA)
        MMPD_AUDIO_SetRecordSilence(MMP_TRUE);
    else
        MMPD_AUDIO_SetRecordSilence(MMP_FALSE);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetEncCamType
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_SetEncCamType(MMP_UBYTE ubRecdSel)
{
    MMP_ULONG   ulEncId     = INVALID_ENC_ID;
    MMP_ULONG   ulCamType   = VIDENC_CAM_BAYER_SNR;

    if (ubRecdSel == MMPS_VR_PRM_RECD) {
        switch(CAM_GET_PRM)
        {
        case PRM_CAM_BAYER_SENSOR:
            ulCamType = VIDENC_CAM_BAYER_SNR;
            break;
        case PRM_CAM_ANA_DECODER:
            ulCamType = VIDENC_CAM_ANA_DECODER;
            break;
        case PRM_CAM_YUV_SENSOR:
            ulCamType = VIDENC_CAM_YUV_SNR;
            break;
        default:
            return MMP_ERR_NONE;
            break;
        }
        ulEncId = m_ulPrmRecdID;
    }
    else if (ubRecdSel == MMPS_VR_SCD_RECD) {
        if (MMPF_VIDMGR_IsShareRecdEn()) {
            switch(CAM_GET_PRM)
            {
            case PRM_CAM_BAYER_SENSOR:
                ulCamType = VIDENC_CAM_BAYER_SNR;
                break;
            case PRM_CAM_ANA_DECODER:
                ulCamType = VIDENC_CAM_ANA_DECODER;
                break;
            case PRM_CAM_YUV_SENSOR:
                ulCamType = VIDENC_CAM_YUV_SNR;
                break;
            default:
                return MMP_ERR_NONE;
                break;
            }
        }
        else {
            switch(CAM_GET_SCD)
            {
            case SCD_CAM_BAYER_SENSOR:
                ulCamType = VIDENC_CAM_BAYER_SNR;
                break;
            case SCD_CAM_ANA_DECODER:
                ulCamType = VIDENC_CAM_ANA_DECODER;
                break;
            case SCD_CAM_YUV_SENSOR:
                ulCamType = VIDENC_CAM_YUV_SNR;
                break;
            default:
                switch(CAM_GET_USB)
                {
                case USB_CAM_AIT:
                    ulCamType = VIDENC_CAM_USB_AIT;
                    break;
                case USB_CAM_SONIX_MJPEG:
                    ulCamType = VIDENC_CAM_USB_SONIX_MJPEG;
                    break;
                case USB_CAM_SONIX_MJPEG2H264:
                    ulCamType = VIDENC_CAM_USB_SONIX_MJPEG2H264;
                    break;
                default:
                    return MMP_ERR_NONE;
                    break;
                }
                break;
            }
        }
        ulEncId = m_ulScdRecdID;
    }
    else if (ubRecdSel == MMPS_VR_TRD_RECD) {
        switch(CAM_GET_TRD)
        {
        case TRD_CAM_BAYER_SENSOR:
            ulCamType = VIDENC_CAM_BAYER_SNR;
            break;
        case TRD_CAM_ANA_DECODER:
            ulCamType = VIDENC_CAM_ANA_DECODER;
            break;
        case TRD_CAM_YUV_SENSOR:
            ulCamType = VIDENC_CAM_YUV_SNR;
            break;
        default:
            return MMP_ERR_NONE;
            break;
        }
        ulEncId = m_ulTrdRecdID;
    }
    else {
        MMPS_VR_DBG_ERR(1, "SetEncCamType UnSupport Type [%d]\r\n", ubRecdSel);
    }

    if (ulEncId != INVALID_ENC_ID) {
        MMPF_VIDENC_SetCamType(MMPF_H264ENC_GetHandle(ulEncId), ulCamType);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetRecordPipeStatus
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Return in video record status or not.
 @param[in]  ubCamSel   Encode instance ID.
 @param[out] bEnable    Record enable.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetRecordPipeStatus(MMP_UBYTE ubCamSel, MMP_BOOL *pbEnable)
{
    MMP_UBYTE ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);

    if (pbEnable) {
        *pbEnable = m_bVidRecordActive[ubRecdSel];
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetEncodeCompBuf
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get start address and size of firmware compressed buffer.
 @param[in]  usStreamType: Stream type
 @param[out] *pulBufAddr : Compress buffer address
 @param[out] *pulBufSize : Compress buffer size
 @param[out] *pulThreshold : near ring buffer threshold size
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetEncodeCompBuf(MMP_USHORT usStreamType, MMP_ULONG *pulBufAddr, MMP_ULONG *pulBufSize, MMP_ULONG *pulThreshold)
{
    return MMPF_VIDMGR_GetVideoCompBuf(usStreamType, pulBufAddr, pulBufSize, pulThreshold);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetExpectedRecordTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the expected video encoding time in unit of second according to
        the specified storage space.
 @param[in] ulSpace the available free space
 @param[in] ulVidBitRate Video bitrate in bit per second.
 @param[in] ulAudBitRate Audio bitrate in bit per second (set to 0 if audio disabled).
 @retval the expected recording time, negative value indicates error.
*/
MMP_LONG MMPS_3GPRECD_GetExpectedRecordTime(MMP_ULONG64 u64Space, MMP_ULONG ulVidBitRate, MMP_ULONG ulAudBitRate)
{
    MMP_LONG    lRecordSec = 0;
    MMP_ULONG   ulContainerOverhead = 0;

    if ((ulVidBitRate + ulAudBitRate) < 8) {
        return 0;
    }

    switch (MMPF_VIDMGR_GetContainerType()) {
    case VIDMGR_CONTAINER_3GP:
    case VIDMGR_CONTAINER_NONE:
        ulContainerOverhead = 0; // TODO: set to 3GP header size
        break;
    case VIDMGR_CONTAINER_TS:
        ulContainerOverhead = 4;
        break;
    case VIDMGR_CONTAINER_AVI:
        switch(m_eVidRecdAudioFmt) {
        case MMPD_3GPMGR_AUDIO_FORMAT_AAC:
            ulContainerOverhead = AVI_AACLC_HEADERS_SIZE;
            break;
        case MMPD_3GPMGR_AUDIO_FORMAT_ADPCM:
            ulContainerOverhead = AVI_WAVE_HEADERS_SIZE;
            break;
        case MMPD_3GPMGR_AUDIO_FORMAT_MP3:
            ulContainerOverhead = AVI_MP3_HEADERS_SIZE;
            break;
        default:
            ulContainerOverhead = AVI_NO_AUD_HEADERS_SIZE;
            break;
        }
        break;
    default:
        return -1;
    }

    if (u64Space <= ulContainerOverhead)
        return 0;
    else
        u64Space -= ulContainerOverhead;

    lRecordSec = (MMP_LONG)(u64Space / ((ulVidBitRate + ulAudBitRate) >> 3));

    if (lRecordSec < VR_MIN_TIME_TO_RECORD) {
        return 0;
    }

    return (lRecordSec - VR_MIN_TIME_TO_RECORD);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetFrameRatePara
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get frame rate for recorded video.
 @param[in] pSnr_fps Sensor input frame rate
 @param[in] pEnc_fps Expected encode frame rate (normal/timelapse/slow motion)
 @param[in] pMgr_fps Frame rate for playback
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetFrameRatePara(MMP_UBYTE                 ubCamSel,
                                      MMPS_3GPRECD_FRAMERATE    *pSnr_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pEnc_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pMgr_fps)
{
    MMP_UBYTE ubRecdSel = VR_CAM_SEL_TO_RECD_SEL(ubCamSel);

    if (pSnr_fps) {
        pSnr_fps->ulTimeIncre = m_VidRecdRuntimeCfg.SnrFrameRate[ubRecdSel].ulTimeIncre;
        pSnr_fps->ulTimeResol = m_VidRecdRuntimeCfg.SnrFrameRate[ubRecdSel].ulTimeResol;
    }
    if (pEnc_fps) {
        pEnc_fps->ulTimeIncre = m_VidRecdRuntimeCfg.EncFrameRate[ubRecdSel].ulTimeIncre;
        pEnc_fps->ulTimeResol = m_VidRecdRuntimeCfg.EncFrameRate[ubRecdSel].ulTimeResol;
    }
    if (pMgr_fps) {
        pMgr_fps->ulTimeIncre = m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeIncre;
        pMgr_fps->ulTimeResol = m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeResol;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetMaxFileSizeTimeLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the maximum 3GP file time and size limit for video encoding.
 @param[out] pu64MaxSizeLimit  Maximum file size.
 @param[out] pu64MaxTimeLimit  Maximum file time.
 @retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPS_3GPRECD_GetMaxFileSizeTimeLimit(MMP_ULONG64 *pu64MaxSizeLimit, MMP_ULONG64 *pu64MaxTimeLimit)
{
    MMP_ULONG   ulAudSampleFreq = 0;
    MMP_ULONG   ulVidByteSec = 0, ulAudByteSec = 0, ulTotalByteSec = 0;
    MMP_ULONG64 u64TotalSec = 0, u64TotalSize = 0;
    MMP_UBYTE   ubRecdSel = MMPS_VR_PRM_RECD;

    MMPF_VIDMGR_GetAudioParam(&ulAudSampleFreq);

    ulVidByteSec = 8 /* BytePerFrame */ * ((m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeResol / m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeIncre) + 1);
    ulAudByteSec = 4 /* BytePerFrame */ * (ulAudSampleFreq / 1024 /* 1024 is SamplePerFrame */);
    ulTotalByteSec = ulVidByteSec + ulAudByteSec;

    u64TotalSec = (m_VidRecdPresetCfg.ulTailBufSize / ulTotalByteSec) - 1;

    if (pu64MaxTimeLimit)
        *pu64MaxTimeLimit = u64TotalSec * 1000; //ms

    u64TotalSize = u64TotalSec * m_VidRecdRuntimeCfg.ulBitrate[ubRecdSel];
    u64TotalSize = u64TotalSize >> 3;

    if (pu64MaxSizeLimit)
        *pu64MaxSizeLimit = u64TotalSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetAllEncPreRecordTime
//  Description : Get all encode stream pre-encode time and select the smaller.
//------------------------------------------------------------------------------
/**
 @brief For dual encode. Get all preencode time and select the smaller.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_GetAllEncPreRecordTime(MMP_ULONG ulPreCaptureMs, MMP_ULONG *pulRealPreCaptureMs)
{
    MMP_ULONG64 ullBitrate64        = 0;
    MMP_ULONG64 ullTimeIncr64       = 0;
    MMP_ULONG64 ullTimeResol64      = 0;
    MMP_ULONG   ulTargetFrameSize   = 0;
    MMP_ULONG   ulExpectBufSize     = 0;
    MMP_ULONG   ulPrmMaxPreEncMs    = 0;
    MMP_ULONG   ulScdMaxPreEncMs    = 0;
    MMP_ULONG   ulTrdMaxPreEncMs    = 0;
    MMP_ULONG   ulMaxPreEncMs       = 0;
    MMP_ULONG   ulMaxAudPreEncMs    = 0;
    #if (UVC_VIDRECD_SUPPORT) && (SUPPORT_USB_HOST_FUNC)
    MMPF_USBH_UVC_STREAM_CFG *pUVCCfg = MMPF_USBH_GetUVCCFG();
    #endif

    // Check primary cam record information.
    ulMaxAudPreEncMs = (m_VidRecdPresetCfg.ulAudioCompBufSize) / (m_VidRecdRuntimeCfg.ulAudBitrate >> 3) * 1000 - 1000;
    ulPrmMaxPreEncMs = 1000 * m_VidRecdRuntimeCfg.ulMaxCompBufDuration[MMPS_VR_PRM_RECD];

    ulMaxPreEncMs = (ulPrmMaxPreEncMs > ulMaxAudPreEncMs) ? (ulMaxAudPreEncMs) : (ulPrmMaxPreEncMs);

    // Check rear cam record information.
    if (MMPF_VIDMGR_IsScdRecdEn()) {

        if (((MMP_IsUSBCamExist() && MMP_IsUSBCamIsoMode()) || (MMP_IsScdCamExist())))
        {
            ulScdMaxPreEncMs = 1000 * m_VidRecdRuntimeCfg.ulMaxCompBufDuration[MMPS_VR_SCD_RECD];

            ulMaxPreEncMs = (ulScdMaxPreEncMs > ulMaxPreEncMs) ? (ulMaxPreEncMs) : (ulScdMaxPreEncMs);
        }
    }

    if (MMPF_VIDMGR_IsTrdRecdEn()) {

        if (MMP_IsTrdCamExist())
        {
            ulTrdMaxPreEncMs = 1000 * m_VidRecdRuntimeCfg.ulMaxCompBufDuration[MMPS_VR_TRD_RECD];

            ulMaxPreEncMs = (ulTrdMaxPreEncMs > ulMaxPreEncMs) ? (ulMaxPreEncMs) : (ulTrdMaxPreEncMs);
        }
    }

    if (MMPF_VIDMGR_IsUvcRecdEn()) { // TBD

        if (MMP_IsUSBCamExist() && !MMP_IsUSBCamIsoMode() && pUVCCfg->mRecd.ulBitrate)
        {
            ullBitrate64        = pUVCCfg->mRecd.ulBitrate;
            ullTimeIncr64       = pUVCCfg->mRecd.usTimeIncrement;
            ullTimeResol64      = pUVCCfg->mRecd.usTimeIncrResol;
            ulTargetFrameSize   = (MMP_ULONG)((ullBitrate64 * ullTimeIncr64)/(ullTimeResol64 * 8));
            ulExpectBufSize     = m_VidRecdPresetCfg.ulUvcVidCompBufSize - (ulTargetFrameSize * 3);

            ulScdMaxPreEncMs    = (MMP_ULONG)(((MMP_ULONG64)ulExpectBufSize * 1000) / (ullBitrate64 >> 3)) - 1000;

            MMPS_VR_DBG_MSG(0, "[USB] PreEnc: MaxMs[%d] BufSz[%d] BR[%d] FSz[%d]\r\n",
                            ulScdMaxPreEncMs, ulExpectBufSize, pUVCCfg->mRecd.ulBitrate, ulTargetFrameSize);

            ulMaxPreEncMs = (ulScdMaxPreEncMs > ulMaxPreEncMs) ? (ulMaxPreEncMs) : (ulScdMaxPreEncMs);
        }
    }

    if (ulPreCaptureMs > ulMaxPreEncMs) {
        MMPS_VR_DBG_MSG(0, "The pre-record duration %d is over preferred %d ms\r\n", ulPreCaptureMs, ulMaxPreEncMs);
        ulPreCaptureMs = ulMaxPreEncMs;
    }

    if (pulRealPreCaptureMs) {
        *pulRealPreCaptureMs = ulPreCaptureMs;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_CalMaxPreEncTime
//  Description :
//------------------------------------------------------------------------------
static MMP_ULONG MMPS_3GPRECD_CalMaxPreEncTime(MMP_UBYTE ubRecdSel)
{
#define VR_MAX_SKIP_FRM_RSVD_CNT (18) // Should >= MAX_SKIP_FRM_RSVD_CNT(18) in hal_mfe_arqc.c

    MMP_ULONG       ulTgtFrameSize      = 0;
    MMP_ULONG       ulExpectBufSize     = 0;
    MMP_ULONG       ulMaxVidPreEncMs    = 0;
    MMP_ULONG       ulMaxAudPreEncMs    = 0;
    MMP_ULONG       ulMaxPreEncMs       = 0;
    MMP_ULONG       ulVidCompBufSize    = 0;
    MMP_ULONG       ulVidNearRingThd    = 0;
    MMP_ULONG       ulVidBitrate        = 0;
    MMP_ULONG       ulEncId             = 0;
    MMP_UBYTE       ubMfeSel            = MFE_COMP_PRM_RECD;
    MFE_COMP_FPS    stMfeSnrFps;

    if (ubRecdSel == MMPS_VR_PRM_RECD) {
        ubMfeSel = MFE_COMP_PRM_RECD;
        ulEncId = m_ulPrmRecdID;
    }
    else if (ubRecdSel == MMPS_VR_SCD_RECD) {
        ubMfeSel = MFE_COMP_SCD_RECD;
        ulEncId = m_ulScdRecdID;
    }
    else if (ubRecdSel == MMPS_VR_TRD_RECD) {
        ubMfeSel = MFE_COMP_TRD_RECD;
        ulEncId = m_ulTrdRecdID;
    }
    else {
        MMPS_VR_DBG_ERR(1, "CalMaxPreEncTime UnSupport Type [%d]\r\n", ubRecdSel);
        return 0;
    }

    /* Note : GetParam() is effective after open script */
    Component_MFE_GetParam(&Component_MFE[ubMfeSel], MFE_COMP_PARAM_NEARRING_THD, (void*)&ulVidNearRingThd);
    Component_MFE_GetParam(&Component_MFE[ubMfeSel], MFE_COMP_PARAM_BUF_SIZE, (void*)&ulVidCompBufSize);
    Component_MFE_GetParam(&Component_MFE[ubMfeSel], MFE_COMP_PARAM_BITRATE, (void*)&ulVidBitrate);
    Component_MFE_GetParam(&Component_MFE[ubMfeSel], MFE_COMP_PARAM_SNR_FPS, (void*)&stMfeSnrFps);

    MMPS_VR_DBG_MSG(0, "CalMaxPreEncTime RingThd[%d] Buf[%d] Br[%d] Fps[%d][%d]\r\n",
                    ulVidNearRingThd,
                    ulVidCompBufSize,
                    ulVidBitrate,
                    stMfeSnrFps.usTimeIncre,
                    stMfeSnrFps.usTimeResol);

    // Calculate max pre-encode time limit
    ulTgtFrameSize = (MMP_ULONG)(((MMP_ULONG64)ulVidBitrate * (MMP_ULONG64)stMfeSnrFps.usTimeIncre)/((MMP_ULONG64)stMfeSnrFps.usTimeResol << 3));

    ulExpectBufSize = ulVidCompBufSize - ulVidNearRingThd - (ulTgtFrameSize * VR_MAX_SKIP_FRM_RSVD_CNT);

    ulMaxAudPreEncMs = (m_VidRecdPresetCfg.ulAudioCompBufSize) / (m_VidRecdRuntimeCfg.ulAudBitrate >> 3) * 1000;
    ulMaxVidPreEncMs = (MMP_ULONG)(((MMP_ULONG64)ulExpectBufSize * 1000) / (ulVidBitrate >> 3));

    MMPS_VR_DBG_MSG(0, "CalMaxPreEncTime Tgt[%d] EBuf[%d] Aud[%d] Vid[%d]\r\n",
                    ulTgtFrameSize, ulExpectBufSize, ulMaxAudPreEncMs, ulMaxVidPreEncMs);

    ulMaxPreEncMs = (ulMaxVidPreEncMs > ulMaxAudPreEncMs) ? (ulMaxAudPreEncMs) : (ulMaxVidPreEncMs);

    ulMaxPreEncMs = (ulMaxPreEncMs / 1000) * 1000;

    if (ulEncId != INVALID_ENC_ID) {
        MMPF_VIDENC_SetMaxPreEncTime(MMPF_H264ENC_GetHandle(ulEncId), ulMaxPreEncMs);
    }

    return ulMaxPreEncMs;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetRemainFrmTimeOffset
//  Description : Get the time of remain frame count in queue.
//------------------------------------------------------------------------------
/**
 @brief Get recording time offset.
 @param[out] ulTime Recording time offset in unit of ms.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetRemainFrmTimeOffset(MMP_USHORT usStreamType, MMP_ULONG *pulTimeMs)
{
    if (pulTimeMs)
        return MMPF_VIDMGR_GetRemainFrmTimeOffset(usStreamType, pulTimeMs);
    else
        return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_CalTailBufSizeNeeded
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Calculate the container tail buffer size according to the specified time.
 @param[in] time The specified time in unit of second.
 @return The size of tail buffer needed.
*/
static MMP_ULONG MMPS_3GPRECD_CalTailBufSizeNeeded(MMP_UBYTE ubRecdSel, MMP_ULONG ulTimeSec)
{
    MMP_ULONG ulTailVidSize = 0;
    MMP_ULONG ulTailAudSize = 0;
    MMP_ULONG ulSlowMoRatio = 1;

    /* Calculate tail info size for video frames */
    ulTailVidSize = (MMP_ULONG)(((MMP_ULONG64)ulTimeSec *
                    m_VidRecdRuntimeCfg.SnrFrameRate[ubRecdSel].ulTimeResol) /
                    m_VidRecdRuntimeCfg.SnrFrameRate[ubRecdSel].ulTimeIncre);

    if (MMPF_VIDMGR_GetMuxConstFPS()) {
        ulTailVidSize = ulTailVidSize << 2; // 4-byte for size info
    }
    else {
        ulTailVidSize = ulTailVidSize << 3; // 4-byte each for time & size info
    }

    MMPS_VR_DBG_MSG(0, "Calculate => [%d] Video Tail Buf [%d]\r\n", ubRecdSel, ulTailVidSize);

    /* Calculate tail info size for audio frames */
    if (MMPF_VIDMGR_GetAudioSyncEncode()) {

        #if 0 // If Slow Motion or Time Lapse Enable, Audio Track Is Disable.
        if (m_VidRecdRuntimeCfg.bSlowMotionEn) { // EROY CHECK
            ulSlowMoRatio = (m_VidRecdRuntimeCfg.EncFrameRate[ubRecdSel].ulTimeResol *
                            m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeIncre) /
                            (m_VidRecdRuntimeCfg.MgrFrameRate[ubRecdSel].ulTimeResol *
                            m_VidRecdRuntimeCfg.EncFrameRate[ubRecdSel].ulTimeIncre);

            if (ulSlowMoRatio != 0) {
                ulTimeSec = ulTimeSec * ulSlowMoRatio;
            }
        }
        #endif

        MMPD_AUDIO_GetRecordFrameCntInSeconds(ulTimeSec, &ulTailAudSize);

        ulTailAudSize = ulTailAudSize << 2; // 4-byte for size info

        MMPS_VR_DBG_MSG(0, "Calculate => [%d] Audio Tail Buf [%d]\r\n", ubRecdSel, ulTailAudSize);
    }

    return (ulTailVidSize + ulTailAudSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetContainerTailBufSize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the container tail buffer size.
 @return The size of tail buffer needed.

 @pre Container type is already set by MMPS_3GPRECD_SetContainerType();
      File size is already set by MMPS_3GPRECD_SetFileSizeLimit();
      File time is already set by MMPS_3GPRECD_SetFileTimeLimit();
      Video frame rate is already set by MMPS_3GPRECD_SetFrameRatePara();
      Audio mode is already selected by MMPS_3GPRECD_SetAudioRecMode();
      Audio format is already set by MMPS_3GPRECD_SetAudioFormat().
*/
static MMP_ULONG MMPS_3GPRECD_GetContainerTailBufSize(MMP_UBYTE ubRecdSel)
{
    MMP_LONG  lSpace2FTime  = 0;
    MMP_ULONG ulSizeByFTime = 0;
    MMP_ULONG ulSizeByFSize = 0;
    MMP_ULONG ulMarginTime  = 0;
    MMP_ULONG ulAudBitrate  = 0;

    switch (MMPF_VIDMGR_GetContainerType()) {
    case VIDMGR_CONTAINER_3GP:
        /* Currently only 3GP needs tail buffer */
        break;
    case VIDMGR_CONTAINER_AVI:
    case VIDMGR_CONTAINER_TS:
    case VIDMGR_CONTAINER_NONE:
    default:
        return 0;
    }

    /* If file time limit is set, calculate tail buffer size by time limit */
    if (m_VidRecdRuntimeCfg.ulTimeLimitMs != 0xFFFFFFFF) {
        ulMarginTime = (m_VidRecdRuntimeCfg.ulTimeLimitMs * 6) / 5000; // 20% margin
        ulSizeByFTime = MMPS_3GPRECD_CalTailBufSizeNeeded(ubRecdSel, ulMarginTime);
    }

    /* Calculate tail buffer size by size limit*/
    if (MMPF_VIDMGR_GetAudioSyncEncode()) {
        ulAudBitrate = m_VidRecdRuntimeCfg.ulAudBitrate;
    }
    else {
        ulAudBitrate = 0;
    }

    lSpace2FTime = MMPS_3GPRECD_GetExpectedRecordTime(  m_VidRecdRuntimeCfg.ulSizeLimit,
                                                        m_VidRecdRuntimeCfg.ulBitrate[ubRecdSel],
                                                        ulAudBitrate);

    if (lSpace2FTime > 0) {
        ulMarginTime = (lSpace2FTime * 27) / 20; // 35% margin
        ulSizeByFSize = MMPS_3GPRECD_CalTailBufSizeNeeded(ubRecdSel, ulMarginTime);
    }
    else {
        ulSizeByFSize = 0;
    }

    /* Select the smaller one */
    if (ulSizeByFTime)
        return (ulSizeByFTime < ulSizeByFSize) ? (ulSizeByFTime) : (ulSizeByFSize);
    else
        return ulSizeByFSize;
}

#if 0
void ____VR_1st_Record_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetCurRecordingTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get how many ms passed after starting recording.
 @param[out] pulTime Recording time in unit of ms.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetCurRecordingTime(MMP_ULONG *pulTimeMs)
{
    #if (EMERGENTRECD_SUPPORT) // TBD
    {
        extern MMP_BOOL m_bStartEmerVR;
        if ((m_bStartEmerVR) && (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)) {
            return MMPF_VIDMGR_GetRecordingTime(VIDENC_STREAM_PRM_EMERG, pulTimeMs);
        }
    }
    #endif

    return MMPF_VIDMGR_GetRecordingTime(VIDENC_STREAM_PRM_RECD, pulTimeMs);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_OpenPrmRecdScript
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_OpenPrmRecdScript(void)
{
    if (MMP_GetANACamType() == ANA_CAM_2I2O) {
        OpenScript(COMPO_SCRIPT_VR_PRM_ANADEC_RECD_RAW1);
        OpenPortScript(PORT_SCRIPT_VR_PRM_ANADEC_RECD_RAW1);
    }
    else {
        OpenScript(COMPO_SCRIPT_VR_PRM_BAYER_RECD);
        OpenPortScript(PORT_SCRIPT_VR_PRM_BAYER_RECD);
    }

    if (MMPF_VIDENC_GetVRThumbEn()) {
        MMPS_3GPRECD_InitVRThumbPipe(MMPS_VR_PRM_RECD);

        if (MMP_GetANACamType() == ANA_CAM_2I2O) {
            UartSendTrace(BG_BLUE("2IN2O TODO:%s,%d\n"),__FUNCTION__, __LINE__);
            OpenScript(COMPO_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1);
        }
        else
            OpenScript(COMPO_SCRIPT_VR_PRM_BAYER_THUMB);

        MMPF_VIDENC_SetVRThumbCBFunc(VIDENC_THUMB_PRM_RECD, MMPS_3GPRECD_OpenPrmThumbPortCB);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetPrmEncoderStatus
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get status of firmware video recorder.
 @param[out] peEncFwStatus Firmware operation status.
 @return Error status.
 @note

 The parameter @a retstatus can be:
 - VIDENC_FW_STATUS_NONE Idle.
 - VIDENC_FW_STATUS_START Under recording.
 - VIDENC_FW_STATUS_PAUSE Pause recording.
 - VIDENC_FW_STATUS_RESUME Restart recording.
 - VIDENC_FW_STATUS_STOP Stop recording.
*/
MMP_ERR MMPS_3GPRECD_GetPrmEncoderStatus(VIDENC_FW_STATUS *peEncFwStatus)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts = VIDENC_FW_STATUS_NONE;

    if (m_ulPrmRecdID == INVALID_ENC_ID) {
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    }
    else {
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);
    }

    if (peEncFwStatus) {
        *peEncFwStatus = eEncFwSts;
    }
    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartPrmPreEnc
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Pre start video recording.

 It start record without enable file saving
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_StartPrmPreEnc(MMP_ULONG *pulInPreEncMs)
{
    MMP_ERR             eRetErr         = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts       = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulMaxPreEncMs   = 0;
    MMP_ULONG           ulTimeout       = VR_QUERY_STATES_TIMEOUT;

    if (MMP_FALSE == MMPF_VIDENC_IsTimerEnabled()) {
        MMPF_VIDENC_EnableTimer(MMP_TRUE);
    }

    if (MMPF_VIDMGR_GetContainerType() == VIDMGR_CONTAINER_TS) {
        #if (MTS_MUXER_EN)
        MMPF_VIDMGR_SetMtsMuxEn(MMP_TRUE);
        MMPF_MTS_ResetAudVidCnt(MMP_TRUE);
        #else
        MMPF_VIDMGR_SetMtsMuxEn(MMP_FALSE);
        #endif
    }

    if (m_ulPrmRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        MMPS_3GPRECD_AllocAudioMemory();

        MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_PRM_RECD);
        MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_PRM_RECD);

        if (MMPF_VIDENC_GetVRThumbEn()) {
            MMPS_3GPRECD_AllocVRThumbMemory();
        }

        MMPS_3GPRECD_OpenPrmRecdScript();

        MMPS_3GPRECD_SetEncCamType(MMPS_VR_PRM_RECD);

        ulMaxPreEncMs = MMPS_3GPRECD_CalMaxPreEncTime(MMPS_VR_PRM_RECD);

        if (*pulInPreEncMs > ulMaxPreEncMs) {
            MMPS_VR_DBG_ERR(1, "The Prm Pre-Enc Duration [%d] Over Preferred [%d] ms\r\n", *pulInPreEncMs, ulMaxPreEncMs);
            *pulInPreEncMs = ulMaxPreEncMs;
        }

        if ((m_ubTotalVidEncCnt != 0) || (m_ubTotalVidEncCnt > MAX_VIDEO_STREAM_NUM)) {
            MMPS_VR_DBG_ERR(1, "MMPS Total Enc Count [%d] Wrong-1\r\n", m_ubTotalVidEncCnt);
        }
        m_ulCurVidEncID[MMPS_VR_PRM_RECD] = m_ulPrmRecdID;
        m_ubTotalVidEncCnt++;

        eRetErr = MMPD_3GPMGR_PreCapture(m_ulPrmRecdID, VIDENC_STREAM_PRM_RECD, *pulInPreEncMs);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Prm PreCapture Fail\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

            if (eEncFwSts != VIDENC_FW_STATUS_PREENCODE) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_PREENCODE) && ((--ulTimeout) > 0));

        if (0 == ulTimeout) {
            MMPS_VR_DBG_ERR(1, "Prm PreEncode TimeOut\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }

        #if (UVC_VIDRECD_SUPPORT)
        if (m_bUVCRecdSupport) {
            MMPS_HUVC_EnableRecd();
        }
        #endif
    }
    else {
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartPrmRecord
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start video recording.

 It can saves the 3GP file to host memory or memory card.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_StartPrmRecord(void)
{
    MMP_ERR             eRetErr         = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts       = VIDENC_FW_STATUS_NONE;
    MMP_ERR             eMgrStatus      = MMP_ERR_NONE;
    void                *pSeamlessCB    = NULL;
    MMP_ULONG           ulAvaSize       = 0;
    MMP_ULONG           ulTimeout       = VR_QUERY_STATES_TIMEOUT;
    MMP_ULONG           ulMaxPreEncMs   = 0;

    if (MMP_FALSE == MMPF_VIDENC_IsTimerEnabled()) {
        MMPF_VIDENC_EnableTimer(MMP_TRUE);
    }

    if (MMPF_VIDMGR_GetContainerType() == VIDMGR_CONTAINER_TS) {
        #if (MTS_MUXER_EN)
        MMPF_VIDMGR_SetMtsMuxEn(MMP_TRUE);
        MMPF_MTS_ResetAudVidCnt(MMP_TRUE);
        #else
        MMPF_VIDMGR_SetMtsMuxEn(MMP_FALSE);
        #endif
    }

    if (m_ulPrmRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        MMPS_3GPRECD_AllocAudioMemory();

        MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_PRM_RECD);
        MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_PRM_RECD);

        if (MMPF_VIDENC_GetVRThumbEn()) {
            MMPS_3GPRECD_AllocVRThumbMemory();
        }

        MMPS_3GPRECD_OpenPrmRecdScript();

        MMPS_3GPRECD_SetEncCamType(MMPS_VR_PRM_RECD);

        ulMaxPreEncMs = MMPS_3GPRECD_CalMaxPreEncTime(MMPS_VR_PRM_RECD);
    }

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
            (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

            if ((m_ubTotalVidEncCnt != 0) || (m_ubTotalVidEncCnt > MAX_VIDEO_STREAM_NUM)) {
                MMPS_VR_DBG_ERR(1, "MMPS Total Enc Count [%d] Wrong-2\r\n", m_ubTotalVidEncCnt);
            }
            m_ulCurVidEncID[MMPS_VR_PRM_RECD] = m_ulPrmRecdID;
            m_ubTotalVidEncCnt++;
        }

        if ((MMPF_VIDMGR_IsShareRecdEn() == MMP_FALSE) &&
            (MMPS_3GPRECD_GetTotalRecdEnabledCnt() >= MMPS_ENC_COUNT_2)) {

            MMPS_VR_DBG_MSG(0, "=> Prm Start By StartAllRecord()\r\n");
            return MMP_ERR_NONE;
        }
        else
        {   // Non dual encode case.

            MMPF_VIDMGR_SetAVFileSizeLimit(m_VidRecdRuntimeCfg.ulSizeLimit, m_VidRecdRuntimeCfg.ulReservedSpace, &ulAvaSize);

            if (MMPS_3GPRECD_GetExpectedRecordTime(ulAvaSize,
                                                   m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_PRM_RECD],
                                                   m_VidRecdRuntimeCfg.ulAudBitrate) <= 0) {
                MMPS_VR_DBG_ERR(1, "Prm GetExpectedRecordTime Fail\r\n");
                return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
            }
            else {
                MMPF_VIDMGR_SetAVFileTimeLimit(m_VidRecdRuntimeCfg.ulTimeLimitMs);
            }

            if (m_VidRecdPresetCfg.bSeamlessMode == MMP_TRUE) {
                // Seamless callback must be registered if seamless mode is enabled.
                MMPF_VIDMGR_GetRegisteredCallback(VIDMGR_EVENT_SEAMLESS, &pSeamlessCB);

                if (MMPF_VIDMGR_GetSeamlessEnable() && (pSeamlessCB == NULL)) {
                    MMPS_VR_DBG_ERR(1, "Seamless callback function NULL\r\n");
                    return MMP_3GPRECD_ERR_GENERAL_ERROR;
                }
            }

            eRetErr = MMPD_3GPMGR_StartCapture(m_ulPrmRecdID, VIDENC_STREAM_PRM_RECD);
            if (eRetErr != MMP_ERR_NONE) {
                MMPS_VR_DBG_ERR(1, "Prm StartCapture Fail [%x]\r\n", eRetErr);
                return MMP_3GPRECD_ERR_GENERAL_ERROR;
            }

            do {
                MMPF_VIDMGR_GetMergerErrStatus(&eMgrStatus);

                eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

                if (eEncFwSts == VIDENC_FW_STATUS_STOP) {
                    return MMP_3GPRECD_ERR_STOPRECD_SLOWCARD;
                }
                if ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL)) {
                    MMPF_OS_SleepMs(10);
                }
            } while ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL) && ((--ulTimeout) > 0));

            if (0 == ulTimeout) {
                MMPS_VR_DBG_ERR(1, "Prm StartRecd TimeOut\r\n");
                return MMP_3GPRECD_ERR_GENERAL_ERROR;
            }

            if (eMgrStatus == MMP_FS_ERR_OPEN_FAIL) {
                MMPS_VR_DBG_ERR(1, "Prm File Open Fail\r\n");
                return MMP_3GPRECD_ERR_OPEN_FILE_FAILURE;
            }
        }
    }
    else {
        MMPS_VR_DBG_ERR(1, "Prm Recd Status [%#x]\r\n", eEncFwSts);
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    MMPS_3GPRECD_EnableRecordPipe(PRM_SENSOR, MMP_TRUE);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StopPrmRecord
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop video recording and fill 3GP tail.

 It works after video start, pause and resume.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_StopPrmRecord(void)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_ULONG           ulVidNumActive = 0;
    VIDENC_FW_STATUS    eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulTimeout = VR_QUERY_STATES_TIMEOUT;

    if (m_ulPrmRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_START)   ||
        (eEncFwSts == VIDENC_FW_STATUS_PAUSE)   ||
        (eEncFwSts == VIDENC_FW_STATUS_RESUME)  ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)    ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        eRetErr = MMPD_3GPMGR_StopCapture(m_ulPrmRecdID, VIDENC_STREAM_PRM_RECD);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Prm StopCapture Fail [%x]\r\n", eRetErr);
            MMPF_VIDENC_SetStatus(m_ulPrmRecdID, VIDENC_FW_STATUS_STOP);
            goto L_StopPrmRecdOut;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);
            if (eEncFwSts != VIDENC_FW_STATUS_STOP) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_STOP) && ((--ulTimeout) > 0));

        if (ulTimeout == 0) {
            MMPS_VR_DBG_ERR(1, "Prm StopRecd TimeOut\r\n");
            MMPF_VIDENC_SetStatus(m_ulPrmRecdID, VIDENC_FW_STATUS_STOP);
        }

        m_ulPrmRecdID = INVALID_ENC_ID;

        m_ulCurVidEncID[MMPS_VR_PRM_RECD] = m_ulPrmRecdID;
        if (m_ubTotalVidEncCnt > 0) {
            m_ubTotalVidEncCnt -= 1;
        }
    }
    else if (eEncFwSts == VIDENC_FW_STATUS_NONE) {

        ulVidNumActive = MMPF_VIDENC_GetActiveInstCnt();

        if ((ulVidNumActive > 0) && (m_ulPrmRecdID != INVALID_ENC_ID)) {

            MMPF_VIDENC_DeInitInstance(m_ulPrmRecdID);

            m_ulPrmRecdID = INVALID_ENC_ID;

            m_ulCurVidEncID[MMPS_VR_PRM_RECD] = m_ulPrmRecdID;
            if (m_ubTotalVidEncCnt > 0) {
                m_ubTotalVidEncCnt -= 1;
            }
        }
    }

L_StopPrmRecdOut:

    if (MMPF_VIDENC_GetActiveInstCnt() == 0) {
        if (MMPF_VIDENC_IsModuleInit()) {
            MMPF_VIDENC_DeinitModule();
        }
    }

    MMPS_3GPRECD_EnableRecordPipe(PRM_SENSOR, MMP_FALSE);

    MMPS_3GPRECD_FreeAudioMemory();

    if (eRetErr)
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    else
        return MMP_ERR_NONE;
}

#if 0
void ____VR_2nd_Record_Function____(){ruturn;} //dummy
#endif

static MMP_ERR MMPS_3GPRECD_OpenScdRecdScript(void)
{
    if (MMPF_VIDMGR_IsShareRecdEn()) {
        OpenScript(COMPO_SCRIPT_VR_SHARE_RECD_SCAL_OSD);
        OpenScript(COMPO_SCRIPT_VR_SHARE_RECD);
        OpenPortScript(PORT_SCRIPT_VR_SHARE_RECD_SRC);
        OpenPortScript(PORT_SCRIPT_VR_SHARE_RECD);
    }
    else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        OpenScript(COMPO_SCRIPT_VR_SCD_BAYER_RECD);
        OpenPortScript(PORT_SCRIPT_VR_SCD_BAYER_RECD);
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
        OpenScript(COMPO_SCRIPT_VR_SCD_ANADEC_RECD);
        OpenPortScript(PORT_SCRIPT_VR_SCD_ANADEC_RECD);
    }
    else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) {
        OpenScript(COMPO_SCRIPT_VR_USBH_RECD);
        OpenPortScript(PORT_SCRIPT_VR_USBH_RECD);
    }

    if (MMPF_VIDENC_GetVRThumbEn()) {

        MMPS_3GPRECD_InitVRThumbPipe(MMPS_VR_SCD_RECD);

        if (MMPF_VIDMGR_IsShareRecdEn()) {
            OpenScript(COMPO_SCRIPT_VR_SHARE_THUMB);
            MMPF_VIDENC_SetVRThumbCBFunc(VIDENC_THUMB_SCD_RECD, MMPS_3GPRECD_OpenShareThumbPortCB);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            OpenScript(COMPO_SCRIPT_VR_SCD_BAYER_THUMB);
            MMPF_VIDENC_SetVRThumbCBFunc(VIDENC_THUMB_SCD_RECD, MMPS_3GPRECD_OpenScdThumbPortCB);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            OpenScript(COMPO_SCRIPT_VR_SCD_ANADEC_THUMB);
            MMPF_VIDENC_SetVRThumbCBFunc(VIDENC_THUMB_SCD_RECD, MMPS_3GPRECD_OpenScdThumbPortCB);
        }
        else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) {
            OpenScript(COMPO_SCRIPT_VR_USBH_THUMB);
            MMPF_VIDENC_SetVRThumbCBFunc(VIDENC_THUMB_SCD_RECD, MMPS_3GPRECD_OpenScdThumbPortCB);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnableScdRecd
//  Description : Enable dual video recording.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_EnableScdRecd(MMP_BOOL bEnable)
{
    MMPF_VIDMGR_SetScdRecdEn(bEnable);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetScdEncoderStatus
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetScdEncoderStatus(VIDENC_FW_STATUS *peEncFwStatus)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts = VIDENC_FW_STATUS_NONE;

    if (m_ulScdRecdID == INVALID_ENC_ID) {
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    }
    else {
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);
    }

    if (peEncFwStatus) {
        *peEncFwStatus = eEncFwSts;
    }
    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartScdPreEnc
//  Description : Start video pre-recording for 2nd H264 Encode.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StartScdPreEnc(MMP_ULONG *pulInPreEncMs)
{
    MMP_ERR             eRetErr         = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts       = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulMaxPreEncMs   = 0;
    MMP_ULONG           ulTimeout       = VR_QUERY_STATES_TIMEOUT;

    if (m_ulScdRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_SCD_RECD);
        MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_SCD_RECD);

        MMPS_3GPRECD_OpenScdRecdScript();

        MMPS_3GPRECD_SetEncCamType(MMPS_VR_SCD_RECD);

        ulMaxPreEncMs = MMPS_3GPRECD_CalMaxPreEncTime(MMPS_VR_SCD_RECD);

        if (*pulInPreEncMs > ulMaxPreEncMs) {
            MMPS_VR_DBG_ERR(1, "The Scd Pre-Enc Duration [%d] Over Preferred [%d] ms\r\n", *pulInPreEncMs, ulMaxPreEncMs);
            *pulInPreEncMs = ulMaxPreEncMs;
        }

        if (MMPF_VIDMGR_IsShareRecdEn()) {
            MMPS_VR_DBG_MSG(1, "Set New Share Pre Enc [%d] ms\r\n", *pulInPreEncMs);
            MMPF_VIDMGR_SetShareRecdPreEncDuration(*pulInPreEncMs);
        }

        if (m_ubTotalVidEncCnt > MAX_VIDEO_STREAM_NUM) {
            MMPS_VR_DBG_ERR(1, "MMPS Total Enc Count [%d] Wrong-3\r\n", m_ubTotalVidEncCnt);
        }
        m_ulCurVidEncID[MMPS_VR_SCD_RECD] = m_ulScdRecdID;
        m_ubTotalVidEncCnt++;

        eRetErr = MMPD_3GPMGR_PreCapture(m_ulScdRecdID, VIDENC_STREAM_SCD_RECD, *pulInPreEncMs);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Scd PreCapture Fail\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);

            if (eEncFwSts != VIDENC_FW_STATUS_PREENCODE) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_PREENCODE) && ((--ulTimeout) > 0));

        if (0 == ulTimeout) {
            MMPS_VR_DBG_ERR(1, "Scd PreEncode TimeOut\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }
    }
    else {
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartScdRecd
//  Description : Start video recording for 2nd H264 encode.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StartScdRecd(void)
{
    MMP_ERR             eRetErr     = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts   = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulAvaSize   = 0;
    MMP_ULONG           ulTimeout   = VR_QUERY_STATES_TIMEOUT;
    MMP_ULONG           ulMaxPreEncMs = 0;

    if (m_ulScdRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_SCD_RECD);
        MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_SCD_RECD);

        MMPS_3GPRECD_OpenScdRecdScript();

        MMPS_3GPRECD_SetEncCamType(MMPS_VR_SCD_RECD);

        ulMaxPreEncMs = MMPS_3GPRECD_CalMaxPreEncTime(MMPS_VR_SCD_RECD);
    }

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
            (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

            if (m_ubTotalVidEncCnt > MAX_VIDEO_STREAM_NUM) {
                MMPS_VR_DBG_ERR(1, "MMPS Total Enc Count [%d] Wrong-4\r\n", m_ubTotalVidEncCnt);
            }
            m_ulCurVidEncID[MMPS_VR_SCD_RECD] = m_ulScdRecdID;
            m_ubTotalVidEncCnt++;
        }

        if ((MMPF_VIDMGR_IsShareRecdEn() == MMP_FALSE) &&
            (MMPS_3GPRECD_GetTotalRecdEnabledCnt() >= MMPS_ENC_COUNT_2)) {

            MMPS_VR_DBG_MSG(0, "=> Scd Start By StartAllRecord()\r\n");
            return MMP_ERR_NONE;
        }
        else {
            MMPF_VIDMGR_SetAVFileSizeLimit(m_VidRecdRuntimeCfg.ulSizeLimit, m_VidRecdRuntimeCfg.ulReservedSpace, &ulAvaSize);

            if (MMPS_3GPRECD_GetExpectedRecordTime(ulAvaSize,
                                                   m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_SCD_RECD],
                                                   m_VidRecdRuntimeCfg.ulAudBitrate) <= 0) {
                MMPS_VR_DBG_ERR(1, "Scd GetExpectedRecordTime Fail\r\n");
                return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
            }

            eRetErr = MMPD_3GPMGR_StartCapture(m_ulScdRecdID, VIDENC_STREAM_SCD_RECD);
            if (eRetErr != MMP_ERR_NONE) {
                MMPS_VR_DBG_ERR(1, "Scd StartCapture Fail [%x]\r\n", eRetErr);
                return MMP_3GPRECD_ERR_GENERAL_ERROR;
            }

            do {
                eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);

                if (eEncFwSts == VIDENC_FW_STATUS_STOP) {
                    return MMP_3GPRECD_ERR_STOPRECD_SLOWCARD;
                }
                if (eEncFwSts != VIDENC_FW_STATUS_START) {
                    MMPF_OS_SleepMs(10);
                }
            } while ((eEncFwSts != VIDENC_FW_STATUS_START) && ((--ulTimeout) > 0));

            if (ulTimeout == 0) {
                MMPS_VR_DBG_ERR(1, "Scd StartRecd TimeOut\r\n");
                return MMP_3GPRECD_ERR_GENERAL_ERROR;
            }
        }
    }
    else {
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    MMPS_3GPRECD_EnableRecordPipe(SCD_SENSOR, MMP_TRUE);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StopScdRecord
//  Description : Stop video recording and fill 3GP tail.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StopScdRecord(void)
{
    MMP_ERR             eRetErr     = MMP_ERR_NONE;
    MMP_ULONG           ulVidNumActive = 0;
    VIDENC_FW_STATUS    eEncFwSts   = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulTimeout   = VR_QUERY_STATES_TIMEOUT;

    if (m_ulScdRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_START)   ||
        (eEncFwSts == VIDENC_FW_STATUS_PAUSE)   ||
        (eEncFwSts == VIDENC_FW_STATUS_RESUME)  ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)    ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        eRetErr = MMPD_3GPMGR_StopCapture(m_ulScdRecdID, VIDENC_STREAM_SCD_RECD);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Scd StopCapture Fail [%x]\r\n", eRetErr);
            MMPF_VIDENC_SetStatus(m_ulScdRecdID, VIDENC_FW_STATUS_STOP);
            goto L_StopScdRecdOut;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);
            if (eEncFwSts != VIDENC_FW_STATUS_STOP) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_STOP) && ((--ulTimeout) > 0));

        if (0 == ulTimeout) {
            MMPS_VR_DBG_ERR(1, "Scd StopRecd TimeOut\r\n");
            MMPF_VIDENC_SetStatus(m_ulScdRecdID, VIDENC_FW_STATUS_STOP);
        }

        m_ulScdRecdID = INVALID_ENC_ID;

        m_ulCurVidEncID[MMPS_VR_SCD_RECD] = m_ulScdRecdID;
        if (m_ubTotalVidEncCnt > 0) {
            m_ubTotalVidEncCnt -= 1;
        }
    }
    else if (eEncFwSts == VIDENC_FW_STATUS_NONE) {

        ulVidNumActive = MMPF_VIDENC_GetActiveInstCnt();

        if ((ulVidNumActive > 0) && (m_ulScdRecdID != INVALID_ENC_ID)) {

            MMPF_VIDENC_DeInitInstance(m_ulScdRecdID);

            m_ulScdRecdID = INVALID_ENC_ID;

            if (MMPF_VIDMGR_IsShareRecdEn() == MMP_FALSE) { // EROY CHECK
                m_ulCurVidEncID[MMPS_VR_SCD_RECD] = m_ulScdRecdID;
                if (m_ubTotalVidEncCnt > 0) {
                    m_ubTotalVidEncCnt -= 1;
                }
            }
        }
    }

L_StopScdRecdOut:

    if (MMPF_VIDENC_GetActiveInstCnt() == 0) {
        if (MMPF_VIDENC_IsModuleInit()) {
            MMPF_VIDENC_DeinitModule();
        }
    }

    MMPS_3GPRECD_EnableRecordPipe(SCD_SENSOR, MMP_FALSE);

    if (eRetErr)
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    else
        return MMP_ERR_NONE;
}

#if 0
void ____VR_3rd_Record_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_OpenTrdRecdScript
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_3GPRECD_OpenTrdRecdScript(void)
{
#if 0 // TBD
        OpenScript(COMPO_SCRIPT_VR_TRD_RECD);
        OpenPortScript(PORT_SCRIPT_VR_TRD_RECORD);

        if (MMPF_VIDENC_GetVRThumbEn()) {

            MMPS_3GPRECD_InitVRThumbPipe(MMPS_VR_TRD_RECD);

            OpenScript(COMPO_SCRIPT_VR_TRD_THUMB);
            MMPF_VIDENC_SetVRThumbCBFunc(VIDENC_THUMB_TRD_RECD, MMPS_3GPRECD_OpenTrdThumbPortCB);
        }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnableTrdRecd
//  Description : Enable 3rd video recording.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_EnableTrdRecd(MMP_BOOL bEnable)
{
    MMPF_VIDMGR_SetTrdRecdEn(bEnable);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetTrdEncoderStatus
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetTrdEncoderStatus(VIDENC_FW_STATUS *peEncFwStatus)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts = VIDENC_FW_STATUS_NONE;

    if (m_ulTrdRecdID == INVALID_ENC_ID) {
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    }
    else {
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);
    }

    if (peEncFwStatus) {
        *peEncFwStatus = eEncFwSts;
    }
    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartTrdPreEnc
//  Description : Start video pre-recording for 3rd H264 Encode.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StartTrdPreEnc(MMP_ULONG *pulInPreEncMs)
{
    MMP_ERR             eRetErr         = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts       = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulMaxPreEncMs   = 0;
    MMP_ULONG           ulTimeout       = VR_QUERY_STATES_TIMEOUT;

    if (m_ulTrdRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_TRD_RECD);
        MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_TRD_RECD);

        MMPS_3GPRECD_OpenTrdRecdScript();

        MMPS_3GPRECD_SetEncCamType(MMPS_VR_TRD_RECD);

        ulMaxPreEncMs = MMPS_3GPRECD_CalMaxPreEncTime(MMPS_VR_TRD_RECD);

        if (*pulInPreEncMs > ulMaxPreEncMs) {
            MMPS_VR_DBG_ERR(1, "The Trd Pre-Enc Duration [%d] Over Preferred [%d] ms\r\n", *pulInPreEncMs, ulMaxPreEncMs);
            *pulInPreEncMs = ulMaxPreEncMs;
        }

        if (m_ubTotalVidEncCnt > MAX_VIDEO_STREAM_NUM) {
            MMPS_VR_DBG_ERR(1, "MMPS Total Enc Count [%d] Wrong-5\r\n", m_ubTotalVidEncCnt);
        }
        m_ulCurVidEncID[MMPS_VR_TRD_RECD] = m_ulTrdRecdID;
        m_ubTotalVidEncCnt++;

        eRetErr = MMPD_3GPMGR_PreCapture(m_ulTrdRecdID, VIDENC_STREAM_TRD_RECD, *pulInPreEncMs);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Trd PreCapture Fail\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);

            if (eEncFwSts != VIDENC_FW_STATUS_PREENCODE) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_PREENCODE) && ((--ulTimeout) > 0));

        if (0 == ulTimeout) {
            MMPS_VR_DBG_ERR(1, "Trd PreEncode TimeOut\r\n");
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }
    }
    else {
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartTrdRecd
//  Description : Start video recording for 3rd H264 encode.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StartTrdRecd(void)
{
    MMP_ERR             eRetErr     = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts   = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulAvaSize   = 0;
    MMP_ULONG           ulTimeout   = VR_QUERY_STATES_TIMEOUT;
    MMP_ULONG           ulMaxPreEncMs = 0;

    if (m_ulTrdRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_TRD_RECD);
        MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_TRD_RECD);

        MMPS_3GPRECD_OpenTrdRecdScript();

        MMPS_3GPRECD_SetEncCamType(MMPS_VR_TRD_RECD);

        ulMaxPreEncMs = MMPS_3GPRECD_CalMaxPreEncTime(MMPS_VR_TRD_RECD);
    }

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
            (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

            if (m_ubTotalVidEncCnt > MAX_VIDEO_STREAM_NUM) {
                MMPS_VR_DBG_ERR(1, "MMPS Total Enc Count [%d] Wrong-6\r\n", m_ubTotalVidEncCnt);
            }
            m_ulCurVidEncID[MMPS_VR_TRD_RECD] = m_ulTrdRecdID;
            m_ubTotalVidEncCnt++;
        }

        if (MMPS_3GPRECD_GetTotalRecdEnabledCnt() >= MMPS_ENC_COUNT_3) {
            MMPS_VR_DBG_MSG(0, "=> Trd Start By StartAllRecord()\r\n");
            return MMP_ERR_NONE;
        }
        else {
            MMPF_VIDMGR_SetAVFileSizeLimit(m_VidRecdRuntimeCfg.ulSizeLimit, m_VidRecdRuntimeCfg.ulReservedSpace, &ulAvaSize);

            if (MMPS_3GPRECD_GetExpectedRecordTime(ulAvaSize,
                                                   m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_TRD_RECD],
                                                   m_VidRecdRuntimeCfg.ulAudBitrate) <= 0) {
                MMPS_VR_DBG_ERR(1, "Trd GetExpectedRecordTime Fail\r\n");
                return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
            }

            eRetErr = MMPD_3GPMGR_StartCapture(m_ulTrdRecdID, VIDENC_STREAM_TRD_RECD);
            if (eRetErr != MMP_ERR_NONE) {
                MMPS_VR_DBG_ERR(1, "Trd StartCapture Fail [%x]\r\n", eRetErr);
                return MMP_3GPRECD_ERR_GENERAL_ERROR;
            }

            do {
                eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);

                if (eEncFwSts == VIDENC_FW_STATUS_STOP) {
                    return MMP_3GPRECD_ERR_STOPRECD_SLOWCARD;
                }
                if (eEncFwSts != VIDENC_FW_STATUS_START) {
                    MMPF_OS_SleepMs(10);
                }
            } while ((eEncFwSts != VIDENC_FW_STATUS_START) && ((--ulTimeout) > 0));

            if (ulTimeout == 0) {
                MMPS_VR_DBG_ERR(1, "Trd StartRecd TimeOut\r\n");
                return MMP_3GPRECD_ERR_GENERAL_ERROR;
            }
        }
    }
    else {
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    MMPS_3GPRECD_EnableRecordPipe(TRD_SENSOR, MMP_TRUE);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StopTrdRecord
//  Description : Stop video recording and fill 3GP tail.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StopTrdRecord(void)
{
    MMP_ERR             eRetErr     = MMP_ERR_NONE;
    MMP_ULONG           ulVidNumActive = 0;
    VIDENC_FW_STATUS    eEncFwSts   = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulTimeout   = VR_QUERY_STATES_TIMEOUT;

    if (m_ulTrdRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_START)   ||
        (eEncFwSts == VIDENC_FW_STATUS_PAUSE)   ||
        (eEncFwSts == VIDENC_FW_STATUS_RESUME)  ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)    ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        eRetErr = MMPD_3GPMGR_StopCapture(m_ulTrdRecdID, VIDENC_STREAM_TRD_RECD);
        if (eRetErr != MMP_ERR_NONE) {
            MMPS_VR_DBG_ERR(1, "Trd StopCapture Fail [%x]\r\n", eRetErr);
            MMPF_VIDENC_SetStatus(m_ulTrdRecdID, VIDENC_FW_STATUS_STOP);
            goto L_StopTrdRecdOut;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);
            if (eEncFwSts != VIDENC_FW_STATUS_STOP) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_STOP) && ((--ulTimeout) > 0));

        if (0 == ulTimeout) {
            MMPS_VR_DBG_ERR(1, "Trd StopRecd TimeOut\r\n");
            MMPF_VIDENC_SetStatus(m_ulTrdRecdID, VIDENC_FW_STATUS_STOP);
        }

        m_ulTrdRecdID = INVALID_ENC_ID;

        m_ulCurVidEncID[MMPS_VR_TRD_RECD] = m_ulTrdRecdID;
        if (m_ubTotalVidEncCnt > 0) {
            m_ubTotalVidEncCnt -= 1;
        }
    }
    else if (eEncFwSts == VIDENC_FW_STATUS_NONE) {

        ulVidNumActive = MMPF_VIDENC_GetActiveInstCnt();

        if ((ulVidNumActive > 0) && (m_ulTrdRecdID != INVALID_ENC_ID)) {

            MMPF_VIDENC_DeInitInstance(m_ulTrdRecdID);

            m_ulTrdRecdID = INVALID_ENC_ID;

            m_ulCurVidEncID[MMPS_VR_TRD_RECD] = m_ulTrdRecdID;
            if (m_ubTotalVidEncCnt > 0) {
                m_ubTotalVidEncCnt -= 1;
            }
        }
    }

L_StopTrdRecdOut:

    if (MMPF_VIDENC_GetActiveInstCnt() == 0) {
        if (MMPF_VIDENC_IsModuleInit()) {
            MMPF_VIDENC_DeinitModule();
        }
    }

    MMPS_3GPRECD_EnableRecordPipe(TRD_SENSOR, MMP_FALSE);

    if (eRetErr)
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    else
        return MMP_ERR_NONE;
}

#if 0
void ____VR_Multi_Record_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartAllRecord
//  Description : Start all record with MGR function.
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StartAllRecord(void)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    VIDENC_FW_STATUS    eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulAvaSize = 0;
    void                *pSeamlessCB = NULL;
    MMP_ULONG           ulTimeout = VR_QUERY_STATES_TIMEOUT;
    MMP_ERR             eMgrStatus = MMP_ERR_NONE;
    MMP_BOOL            bSlowCardStop = MMP_FALSE;
    MMP_BOOL            bSlowCardStopDone = MMP_TRUE;

    if (MMPF_VIDMGR_IsShareRecdEn()) {
        MMPS_VR_DBG_ERR(1, "Share Recd Can Not Enter StartAllRecord()\r\n");
        return MMP_ERR_NONE;
    }

    if (m_ubTotalVidEncCnt == 0) {
        return MMP_ERR_NONE;
    }

    if (MMPF_VIDMGR_GetContainerType() == VIDMGR_CONTAINER_TS) {
        #if (MTS_MUXER_EN)
        MMPF_VIDMGR_SetMtsMuxEn(MMP_TRUE);
        MMPF_MTS_ResetAudVidCnt(MMP_TRUE);
        #else
        MMPF_VIDMGR_SetMtsMuxEn(MMP_FALSE);
        #endif
    }

    // Prepare primary record
    if (m_ulPrmRecdID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulPrmRecdID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        MMPF_VIDMGR_SetAVFileSizeLimit(m_VidRecdRuntimeCfg.ulSizeLimit, m_VidRecdRuntimeCfg.ulReservedSpace, &ulAvaSize);

        if (MMPS_3GPRECD_GetExpectedRecordTime(ulAvaSize,
                                               m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_PRM_RECD],
                                               m_VidRecdRuntimeCfg.ulAudBitrate) <= 0) {
            MMPS_VR_DBG_ERR(1, "All_Prm GetExpectedRecordTime Fail\r\n");
            return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
        }
        else {
            MMPF_VIDMGR_SetAVFileTimeLimit(m_VidRecdRuntimeCfg.ulTimeLimitMs);
        }

        if (m_VidRecdPresetCfg.bSeamlessMode == MMP_TRUE) {
            // Seamless callback must be registered if seamless mode is enabled.
            MMPF_VIDMGR_GetRegisteredCallback(VIDMGR_EVENT_SEAMLESS, &pSeamlessCB);

            if (MMPF_VIDMGR_GetSeamlessEnable() && (pSeamlessCB == NULL)) {
                return MMP_3GPRECD_ERR_GENERAL_ERROR;
            }
        }
    }

    // Prepare second record
    if (m_ubTotalVidEncCnt >= 2) {

        if (m_ulScdRecdID == INVALID_ENC_ID)
            eEncFwSts = VIDENC_FW_STATUS_NONE;
        else
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulScdRecdID);

        if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
            (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
            (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

            MMPF_VIDMGR_SetAVFileSizeLimit(m_VidRecdRuntimeCfg.ulSizeLimit, m_VidRecdRuntimeCfg.ulReservedSpace, &ulAvaSize);

            if (MMPS_3GPRECD_GetExpectedRecordTime( ulAvaSize,
                                                    m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_SCD_RECD],
                                                    m_VidRecdRuntimeCfg.ulAudBitrate) <= 0) {
                MMPS_VR_DBG_ERR(1, "All_Scd GetExpectedRecordTime Fail\r\n");
                return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
            }
        }
    }

    // Prepare third record
    if (m_ubTotalVidEncCnt >= 3) {

        if (m_ulTrdRecdID == INVALID_ENC_ID)
            eEncFwSts = VIDENC_FW_STATUS_NONE;
        else
            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulTrdRecdID);

        if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
            (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
            (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

            MMPF_VIDMGR_SetAVFileSizeLimit(m_VidRecdRuntimeCfg.ulSizeLimit, m_VidRecdRuntimeCfg.ulReservedSpace, &ulAvaSize);

            if (MMPS_3GPRECD_GetExpectedRecordTime( ulAvaSize,
                                                    m_VidRecdRuntimeCfg.ulBitrate[MMPS_VR_TRD_RECD],
                                                    m_VidRecdRuntimeCfg.ulAudBitrate) <= 0) {
                MMPS_VR_DBG_ERR(1, "All_Trd GetExpectedRecordTime Fail\r\n");
                return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
            }
        }
    }

    eRetErr = MMPD_3GPMGR_StartAllCapture(m_ubTotalVidEncCnt, &m_ulCurVidEncID[0]);
    if (eRetErr != MMP_ERR_NONE) {
        MMPS_VR_DBG_ERR(1, "StartAllCapture Fail [%x]\r\n", eRetErr);
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }

    ulTimeout = VR_QUERY_STATES_TIMEOUT;

    do {

        MMPF_VIDMGR_GetMergerErrStatus(&eMgrStatus);

        eEncFwSts = MMPF_VIDENC_GetStatus(m_ulCurVidEncID[MMPS_VR_PRM_RECD]);

        if (eEncFwSts == VIDENC_FW_STATUS_STOP) {
            MMPS_VR_DBG_ERR(1, "All Start Meet Slow Card Prm\r\n");
            return MMP_3GPRECD_ERR_STOPRECD_SLOWCARD;
        }
        else if ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL)) {
            MMPF_OS_SleepMs(10);
        }
    } while ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL) && ((--ulTimeout) > 0));

    if (0 == ulTimeout) {
        MMPS_VR_DBG_ERR(1, "All Start PrmRecd TimeOut\r\n");
        goto L_AllStartErr;
    }

    if (eMgrStatus == MMP_FS_ERR_OPEN_FAIL) {
        MMPS_VR_DBG_ERR(1, "All Start File Open Fail1\r\n");
        goto L_AllStartErr;
    }

    if (eEncFwSts == VIDENC_FW_STATUS_START) {
        MMPS_3GPRECD_EnableRecordPipe(PRM_SENSOR, MMP_TRUE);
    }

    if (m_ubTotalVidEncCnt >= 2) {

        ulTimeout = VR_QUERY_STATES_TIMEOUT;

        do {
            MMPF_VIDMGR_GetMergerErrStatus(&eMgrStatus);

            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulCurVidEncID[MMPS_VR_SCD_RECD]);

            if (eEncFwSts == VIDENC_FW_STATUS_STOP) {
                MMPS_VR_DBG_ERR(1, "All Start Meet Slow Card Scd\r\n");
                return MMP_3GPRECD_ERR_STOPRECD_SLOWCARD;
            }
            else if ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL)) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL) && ((--ulTimeout) > 0));

        if (ulTimeout == 0) {
            MMPS_VR_DBG_ERR(1, "All Start ScdRecd TimeOut\r\n");
            goto L_AllStartErr;
        }

        if (eMgrStatus == MMP_FS_ERR_OPEN_FAIL) {
            MMPS_VR_DBG_ERR(1, "All Start File Open Fail2\r\n");
            goto L_AllStartErr;
        }

        if (eEncFwSts == VIDENC_FW_STATUS_START) {
            MMPS_3GPRECD_EnableRecordPipe(SCD_SENSOR, MMP_TRUE);
        }
    }

    if (m_ubTotalVidEncCnt >= 3) {

        ulTimeout = VR_QUERY_STATES_TIMEOUT;

        do {
            MMPF_VIDMGR_GetMergerErrStatus(&eMgrStatus);

            eEncFwSts = MMPF_VIDENC_GetStatus(m_ulCurVidEncID[MMPS_VR_TRD_RECD]);

            if (eEncFwSts == VIDENC_FW_STATUS_STOP) {
                MMPS_VR_DBG_ERR(1, "All Start Meet Slow Card Trd\r\n");
                return MMP_3GPRECD_ERR_STOPRECD_SLOWCARD;
            }
            else if ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL)) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_START) && (eMgrStatus != MMP_FS_ERR_OPEN_FAIL) && ((--ulTimeout) > 0));

        if (ulTimeout == 0) {
            MMPS_VR_DBG_ERR(1, "All Start TrdRecd TimeOut\r\n");
            goto L_AllStartErr;
        }

        if (eMgrStatus == MMP_FS_ERR_OPEN_FAIL) {
            MMPS_VR_DBG_ERR(1, "All Start File Open Fail3\r\n");
            goto L_AllStartErr;
        }

        if (eEncFwSts == VIDENC_FW_STATUS_START) {
            MMPS_3GPRECD_EnableRecordPipe(TRD_SENSOR, MMP_TRUE);
        }
    }

L_AllStartErr:

    bSlowCardStop       = MMPF_VIDMGR_IsCardSlowStop();
    bSlowCardStopDone   = MMPF_VIDMGR_IsCardSlowStopDone();

    if ((bSlowCardStop == MMP_TRUE) ||
        (bSlowCardStopDone == MMP_FALSE)) {
        MMPS_VR_DBG_ERR(1, "All Start Meet Slow Card\r\n");
        return MMP_3GPRECD_ERR_STOPRECD_SLOWCARD;
    }

    if ((ulTimeout == 0) || (eMgrStatus == MMP_FS_ERR_OPEN_FAIL)) {
        return MMP_3GPRECD_ERR_GENERAL_ERROR;
    }
    else {
        return MMP_ERR_NONE;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StopAllRecord
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop video recording and fill 3GP tail.

 It works after video start, pause and resume.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_StopAllRecord(void)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_BOOL    bStopPrmRecd = MMP_FALSE;
    MMP_BOOL    bStopScdRecd = MMP_FALSE;
    MMP_BOOL    bStopTrdRecd = MMP_FALSE;

    if (MMPS_3GPRECD_GetTotalRecdEnabledCnt() >= MMPS_ENC_COUNT_3) {
        bStopPrmRecd = (m_ulCurVidEncID[MMPS_VR_PRM_RECD] != INVALID_ENC_ID) ? (MMP_TRUE) : (MMP_FALSE);
        bStopScdRecd = (m_ulCurVidEncID[MMPS_VR_SCD_RECD] != INVALID_ENC_ID) ? (MMP_TRUE) : (MMP_FALSE);
        bStopTrdRecd = (m_ulCurVidEncID[MMPS_VR_TRD_RECD] != INVALID_ENC_ID) ? (MMP_TRUE) : (MMP_FALSE);
    }
    else if (MMPS_3GPRECD_GetTotalRecdEnabledCnt() >= MMPS_ENC_COUNT_2) {
        bStopPrmRecd = (m_ulCurVidEncID[MMPS_VR_PRM_RECD] != INVALID_ENC_ID) ? (MMP_TRUE) : (MMP_FALSE);
        bStopScdRecd = (m_ulCurVidEncID[MMPS_VR_SCD_RECD] != INVALID_ENC_ID) ? (MMP_TRUE) : (MMP_FALSE);
        bStopTrdRecd = MMP_FALSE;
    }
    else if (MMPS_3GPRECD_GetTotalRecdEnabledCnt() >= MMPS_ENC_COUNT_1) {
        bStopPrmRecd = (m_ulCurVidEncID[MMPS_VR_PRM_RECD] != INVALID_ENC_ID) ? (MMP_TRUE) : (MMP_FALSE);
        bStopScdRecd = MMP_FALSE;
        bStopTrdRecd = MMP_FALSE;
    }
    else {
        return eRetErr;
    }

    static MMP_UBYTE ubMmpsVRStopAllEntryOnce = 0;

    OS_CRITICAL_INIT();
    OS_ENTER_CRITICAL();

    if (ubMmpsVRStopAllEntryOnce > 0) {
        OS_EXIT_CRITICAL();
        MMPS_VR_DBG_ERR(1, "StopAllRecord => ReEntry\r\n");
        return eRetErr;
    }

    if (!bStopPrmRecd && !bStopScdRecd && !bStopTrdRecd) {
        OS_EXIT_CRITICAL();
        MMPS_VR_DBG_ERR(1, "StopAllRecord => Redundant\r\n");
        return eRetErr;
    }

    ubMmpsVRStopAllEntryOnce = 1;
    OS_EXIT_CRITICAL();

    /* Close Port */
    if (bStopTrdRecd) {
        //ClosePortScript(PORT_SCRIPT_VR_TRD_RECORD);
    }

    if (bStopScdRecd) {
        if (MMPF_VIDMGR_IsShareRecdEn()) {
            ClosePortScript(PORT_SCRIPT_VR_SHARE_RECD_SRC);
            ClosePortScript(PORT_SCRIPT_VR_SHARE_RECD);
            ClosePortScript(PORT_SCRIPT_VR_SHARE_THUMB);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            ClosePortScript(PORT_SCRIPT_VR_SCD_BAYER_RECD);
            ClosePortScript(PORT_SCRIPT_VR_SCD_BAYER_THUMB);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            ClosePortScript(PORT_SCRIPT_VR_SCD_ANADEC_RECD);
            ClosePortScript(PORT_SCRIPT_VR_SCD_ANADEC_THUMB);
        }
        else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) {
            ClosePortScript(PORT_SCRIPT_VR_USBH_RECD);
            ClosePortScript(PORT_SCRIPT_VR_USBH_THUMB);
        }
    }

    if (bStopPrmRecd) {
        if(MMP_GetANACamType() == ANA_CAM_2I2O){
            ClosePortScript(PORT_SCRIPT_VR_PRM_ANADEC_RECD_RAW1);
            ClosePortScript(PORT_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1);
         }else{
            ClosePortScript(PORT_SCRIPT_VR_PRM_BAYER_RECD);
            ClosePortScript(PORT_SCRIPT_VR_PRM_BAYER_THUMB);
        }
    }

    /* Stop Encoder and Merger */
    if (bStopTrdRecd) {
        eRetErr = MMPS_3GPRECD_StopTrdRecord();
    }

    if (bStopScdRecd) {
        eRetErr = MMPS_3GPRECD_StopScdRecord();
    }

    if (bStopPrmRecd) {
        eRetErr = MMPS_3GPRECD_StopPrmRecord();
    }

    /* Close Script and Release Memory */
    if (bStopTrdRecd) {
        //CloseScript(COMPO_SCRIPT_VR_TRD_RECD);

        if (MMPF_VIDENC_GetVRThumbEn()) {
            //CloseScript(COMPO_SCRIPT_VR_TRD_THUMB);
        }
    }

    if (bStopScdRecd) {

        if (MMPF_VIDMGR_IsShareRecdEn()) {
            CloseScript(COMPO_SCRIPT_VR_SHARE_RECD_SCAL_OSD);
            CloseScript(COMPO_SCRIPT_VR_SHARE_RECD);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            CloseScript(COMPO_SCRIPT_VR_SCD_BAYER_RECD);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            CloseScript(COMPO_SCRIPT_VR_SCD_ANADEC_RECD);
        }
        else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) {
            CloseScript(COMPO_SCRIPT_VR_USBH_RECD);
        }

        if (MMPF_VIDENC_GetVRThumbEn()) {
            if (MMPF_VIDMGR_IsShareRecdEn()) {
                CloseScript(COMPO_SCRIPT_VR_SHARE_THUMB);
            }
            else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                CloseScript(COMPO_SCRIPT_VR_SCD_BAYER_THUMB);
            }
            else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
                CloseScript(COMPO_SCRIPT_VR_SCD_ANADEC_THUMB);
            }
            else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) {
                CloseScript(COMPO_SCRIPT_VR_USBH_THUMB);
            }
        }
    }

    if (bStopPrmRecd) {
        if(MMP_GetANACamType() == ANA_CAM_2I2O){
             CloseScript(COMPO_SCRIPT_VR_PRM_ANADEC_RECD_RAW1);
            if (MMPF_VIDENC_GetVRThumbEn()) {
                CloseScript(COMPO_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1);
             }
        }
        else
        {
            CloseScript(COMPO_SCRIPT_VR_PRM_BAYER_RECD);
            if (MMPF_VIDENC_GetVRThumbEn()) {
                CloseScript(COMPO_SCRIPT_VR_PRM_BAYER_THUMB);
            }
        }
    }

    if (MMPF_VIDENC_GetVRThumbEn()) {
        MMPS_3GPRECD_FreeVRThumbMemory();
    }

    MMPF_VIDMGR_ResetErrFlag();

    m_ubTotalVidEncCnt = 0;
    m_ulCurVidEncID[MMPS_VR_PRM_RECD] = m_ulPrmRecdID = INVALID_ENC_ID;
    m_ulCurVidEncID[MMPS_VR_SCD_RECD] = m_ulScdRecdID = INVALID_ENC_ID;
    m_ulCurVidEncID[MMPS_VR_TRD_RECD] = m_ulTrdRecdID = INVALID_ENC_ID;

    if (eRetErr) {
        MMPS_VR_DBG_ERR(1, "StopAllRecord => Stop Fail [%x]\r\n", eRetErr);
    }
#if 0
    if (MMPF_VIDENC_GetActiveInstCnt() != 0) {
        MMPS_VR_DBG_ERR(1, "StopAllRecord => Inst Still Active\r\n");
    }
    if (MMPF_VIDENC_IsModuleInit()) {
        MMPS_VR_DBG_ERR(1, "StopAllRecord => Module Still Active\r\n");
    }
#endif

    ubMmpsVRStopAllEntryOnce = 0;

    return eRetErr;
}

#if 0
void ____VR_Share_Record_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetShareRecordEn
//  Description :
//------------------------------------------------------------------------------
void MMPS_3GPRECD_SetShareRecordEn(MMP_BOOL bEnable)
{
    MMPF_VIDMGR_SetShareRecdEn(bEnable);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_IsShareRecordEn
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPS_3GPRECD_IsShareRecordEn(void)
{
    return MMPF_VIDMGR_IsShareRecdEn();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetShareFileTimeLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the maximum 3GP file time for video encoding.
 @param[in] ulTimeLimitMs Maximum file time in unit of ms.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE Space not enough.
*/
MMP_ERR MMPS_3GPRECD_SetShareFileTimeLimit(MMP_ULONG ulTimeLimitMs)
{
    if (ulTimeLimitMs) {
        MMPF_VIDMGR_SetShareRecdTimeLimit(ulTimeLimitMs);
        return MMP_ERR_NONE;
    }

    return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetSharePreEncDuration
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the the pre-encoding time limit.
 @param[in] ulTimeLimitMs Maximum file time in ms.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE Space not enough.
*/
MMP_ERR MMPS_3GPRECD_GetSharePreEncDuration(MMP_ULONG *pulDuration)
{
    if (pulDuration) {
        *pulDuration = MMPF_VIDMGR_GetShareRecdPreEncDuration();
        return MMP_ERR_NONE;
    }

    return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetShareRecordingTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get dual recording time.
 @param[out] ulTime Recording time in unit of ms.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetShareRecordingTime(MMP_ULONG *pulTime)
{
    if (pulTime) {
        return MMPF_VIDMGR_GetRecordingTime(VIDENC_STREAM_SCD_RECD, pulTime);
    }
    else {
        return MMP_ERR_NONE;
    }
}

#if 0
void ____VR_Streaming_Function____(){ruturn;} //dummy
#endif

#if (SUPPORT_H264_WIFI_STREAM)
//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_CustomedResol
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set H264 Wifi resolution
 @param[in] sFitMode    scaler fit mode
 @param[in] usWidth     encode width
 @param[in] usHeight    encode height
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_H264_STREAM_CustomedResol(MMP_UBYTE ubStrmSel, MMP_UBYTE sFitMode, MMP_USHORT usWidth, MMP_USHORT usHeight)
{
    MFE_COMP_ENC_RESOL  stMfeResol;
    MFE_COMP_PIXFMT     ePixFmt;
    MMP_ULONG           ulWAlignBase = MFE_COMP_W_ALIGN_BASE_NV12;
    MMP_ULONG           ulHAlignBase = MFE_COMP_H_ALIGN_BASE_NV12;

    Component_MFE_GetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_PIX_FMT, (void*)&ePixFmt);

    if (ePixFmt == MFE_COMP_PIXFMT_NV12 ||
        ePixFmt == MFE_COMP_PIXFMT_NV21) {
        ulWAlignBase = MFE_COMP_W_ALIGN_BASE_NV12;
        ulHAlignBase = MFE_COMP_H_ALIGN_BASE_NV12;
    }
    else {
        ulWAlignBase = MFE_COMP_W_ALIGN_BASE_YUV422;
        ulHAlignBase = MFE_COMP_H_ALIGN_BASE_YUV422;
    }

    m_stAhcH264StreamInfo[ubStrmSel].sFitMode       = sFitMode;
    m_stAhcH264StreamInfo[ubStrmSel].ulVidEncW      = usWidth;
    m_stAhcH264StreamInfo[ubStrmSel].ulVidEncH      = usHeight;
    m_stAhcH264StreamInfo[ubStrmSel].ulVidEncBufW   = ALIGN_X(usWidth, ulWAlignBase);
    m_stAhcH264StreamInfo[ubStrmSel].ulVidEncBufH   = ALIGN_X(usHeight, ulHAlignBase);

    stMfeResol.ulEncW       = m_stAhcH264StreamInfo[ubStrmSel].ulVidEncW;
    stMfeResol.ulEncH       = m_stAhcH264StreamInfo[ubStrmSel].ulVidEncH;
    stMfeResol.ulEncBufW    = m_stAhcH264StreamInfo[ubStrmSel].ulVidEncBufW;
    stMfeResol.ulEncBufH    = m_stAhcH264StreamInfo[ubStrmSel].ulVidEncBufH;
    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_RESOLUTION, (void*)&stMfeResol);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_EnablePipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_H264_STREAM_EnablePipe(MMP_UBYTE ubStrmSel, MMP_BOOL bEnable)
{
    if (m_bH264StreamActive[ubStrmSel] ^ bEnable) {
        m_bH264StreamActive[ubStrmSel] = bEnable;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_SetBitrate
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_H264_STREAM_SetBitrate(MMP_UBYTE ubStrmSel, MMP_ULONG ulBitrate)
{
    MMP_ULONG ulMfeBitrate = ulBitrate;

    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_BITRATE, (void*)&ulMfeBitrate);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_SetFrameRatePara
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set frame rate for recorded video.
 @param[in] pSnr_fps Sensor input frame rate
 @param[in] pEnc_fps Expected encode frame rate (normal/timelapse/slow motion)
 @param[in] pMgr_fps Frame rate for playback
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_H264_STREAM_SetFrameRatePara(MMP_UBYTE                 ubStrmSel,
                                          MMPS_3GPRECD_FRAMERATE    *pSnr_fps,
                                          MMPS_3GPRECD_FRAMERATE    *pEnc_fps,
                                          MMPS_3GPRECD_FRAMERATE    *pMgr_fps)
{
    MFE_COMP_FPS stMfeFps;

    if ((pSnr_fps->ulTimeIncre == 0) ||
        (pSnr_fps->ulTimeResol == 0) ||
        (pEnc_fps->ulTimeIncre == 0) ||
        (pEnc_fps->ulTimeResol == 0) ||
        (pMgr_fps->ulTimeIncre == 0) ||
        (pMgr_fps->ulTimeResol == 0)) {
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }

    stMfeFps.usTimeIncre = pSnr_fps->ulTimeIncre;
    stMfeFps.usTimeResol = pSnr_fps->ulTimeResol;
    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_SNR_FPS, (void*)&stMfeFps);

    stMfeFps.usTimeIncre = pEnc_fps->ulTimeIncre;
    stMfeFps.usTimeResol = pEnc_fps->ulTimeResol;
    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_ENC_FPS, (void*)&stMfeFps);

    stMfeFps.usTimeIncre = pMgr_fps->ulTimeIncre;
    stMfeFps.usTimeResol = pMgr_fps->ulTimeResol;
    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_MGR_FPS, (void*)&stMfeFps);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_SetPFrameCount
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set P frame count of one cycle.
 @param[in] usFrameCount Count of P frame.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_H264_STREAM_SetPFrameCount(MMP_UBYTE ubStrmSel, MMP_USHORT usFrmCnt)
{
    MMP_ULONG ulMfePFrmCnt = usFrmCnt;

    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_P_FRM_CNT, (void*)&ulMfePFrmCnt);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_SetProfile
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set profile for video encode.
 @param[in] eProfile Visual profile for the specified encoder.
 @retval none.
*/
MMP_ERR MMPS_H264_STREAM_SetProfile(MMP_UBYTE ubStrmSel, VIDENC_PROFILE eProfile)
{
    MFE_COMP_PROFILE eMfeProfile = (MFE_COMP_PROFILE)eProfile;

    Component_MFE_SetParam(&Component_MFE[MFE_COMP_PRM_STREAM + ubStrmSel], MFE_COMP_PARAM_PROFILE, (void*)&eMfeProfile);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_ConfigPipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_H264_STREAM_ConfigPipe(MMP_H264_STREAM_OBJ *pstStreamObj, MMP_USHORT usStreamW, MMP_USHORT usStreamH)
{
    SCL_COMP_RECT   stSclRect;
    MMP_ULONG       ulScaleInW = 0, ulScaleInH = 0;
    MMP_ULONG       ulAlignOutW = 0, ulAlignOutH = 0;
    MMP_UBYTE       ubDipBufCnt = DIP_COMP_RECORD_BUF_COUNT;
    MMP_UBYTE       ubDIPCompSel = DIP_S_COMP_VR_FCAM_STREAMING;
    MMP_UBYTE       ubInColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    MMP_UBYTE       ubOutColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    MMP_UBYTE       ubBypass = MMP_FALSE;
    MMP_ERR         eRetErr = MMP_ERR_NONE;

    if (pstStreamObj == NULL) {
        return eRetErr;
    }

    if (pstStreamObj->ubStrmSel == MMPS_H264_STRM_PRM && pstStreamObj->ubCamSel == PRM_SENSOR) {

        if (pstStreamObj->ubUiMode == MMP_H264_STREAM_MODE_DSC) {
            ubDIPCompSel = DIP_S_COMP_DSC_FCAM_STREAMING;
            Component_SCL1_GetParam(&Component_SCL1[SCL1_COMP_PRM_CAM], SCL_COMP_PARAM_OUT_RECT, &stSclRect);
        }
        else {
            ubDIPCompSel = DIP_S_COMP_VR_FCAM_STREAMING;
            Component_SCL0_GetParam(&Component_SCL0[SCL0_COMP_PRM_CAM], SCL_COMP_PARAM_OUT_RECT, &stSclRect);
        }

        ulScaleInW = stSclRect.ulW;
        ulScaleInH = stSclRect.ulH;

        // Update DIP_S component
        ulAlignOutW = usStreamW;
        ulAlignOutH = usStreamH;
        ulAlignOutW = ALIGN_X(ulAlignOutW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulAlignOutH = ALIGN_X(ulAlignOutH, DIP_S_COMP_WIDTH_ALIGN_BASE);

        eRetErr |= MMPD_Fctl_SetDIPCompAttr(DIP_COMP_TYPE_ID_SCL,
                                            ubDIPCompSel,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            0, 0, ulAlignOutW, ulAlignOutH,
                                            DIP_COMP_COLOR_FMT_YUV420_UV,
                                            DIP_COMP_COLOR_FMT_YUV420_UV,
                                            DIP_COMP_MIRROR_DIS,
                                            MFE_SHARE_BUF_LINE_BIAS,
                                            ubDipBufCnt);
    }
    else if (pstStreamObj->ubStrmSel == MMPS_H264_STRM_SCD) {

        if (pstStreamObj->ubUiMode == MMP_H264_STREAM_MODE_DSC) {
            ubDIPCompSel = DIP_S_COMP_DSC_RCAM_STREAMING;
        }
        else {
            ubDIPCompSel = DIP_S_COMP_VR_RCAM_STREAMING;
        }

        // Update DIP_S component
        ulAlignOutW = usStreamW;
        ulAlignOutH = usStreamH;
        ulAlignOutW = ALIGN_X(ulAlignOutW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulAlignOutH = ALIGN_X(ulAlignOutH, DIP_S_COMP_WIDTH_ALIGN_BASE);

        if (pstStreamObj->ubCamSel == SCD_SENSOR) {
            Component_RawS_GetParam(&Component_RawS[RAWS_COMP_IDX], RAWS_COMP_PARAM_WIDTH, &ulScaleInW);
            Component_RawS_GetParam(&Component_RawS[RAWS_COMP_IDX], RAWS_COMP_PARAM_HEIGHT, &ulScaleInH);
        }
        else if (pstStreamObj->ubCamSel == USBH_SENSOR) {
            ulScaleInW = gUsbh_UvcDevInfo.wPrevwMaxWidth;
            ulScaleInH = gUsbh_UvcDevInfo.wPrevwMaxHeight;
        }

        #if (SUPPORT_MFE_SHAREBUFFER == 0)
        if (ulScaleInW == ulAlignOutW &&
            ulScaleInH == ulAlignOutH) {
            ubBypass = MMP_TRUE;
        }
        #endif

        if (ubBypass == MMP_TRUE) {
            MFE_COMP_PIXFMT ePixFmt = MFE_COMP_PIXFMT_YUYV;

            Component_MFE_SetParam(&Component_MFE[MFE_COMP_SCD_STREAM], MFE_COMP_PARAM_PIX_FMT, (void*)&ePixFmt);
            Component_DIP_SetParam(&Component_DIP_Scale[ubDIPCompSel], DIP_COMP_PARAM_SCL_BYPASS, (void*)&ubBypass);

            ubInColor  = DIP_COMP_COLOR_FMT_YUV422_YUYV;
            ubOutColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
        }
        else {
            MFE_COMP_PIXFMT ePixFmt = MFE_COMP_PIXFMT_NV12;

            Component_MFE_SetParam(&Component_MFE[MFE_COMP_SCD_STREAM], MFE_COMP_PARAM_PIX_FMT, (void*)&ePixFmt);
            Component_DIP_SetParam(&Component_DIP_Scale[ubDIPCompSel], DIP_COMP_PARAM_SCL_BYPASS, (void*)&ubBypass);

            ubInColor  = DIP_COMP_COLOR_FMT_YUV422_YUYV;
            ubOutColor = DIP_COMP_COLOR_FMT_YUV420_UV;
        }

        eRetErr |= MMPD_Fctl_SetDIPCompAttr(DIP_COMP_TYPE_ID_SCL,
                                            ubDIPCompSel,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            0, 0, ulAlignOutW, ulAlignOutH,
                                            ubInColor,
                                            ubOutColor,
                                            DIP_COMP_MIRROR_DIS,
                                            MFE_SHARE_BUF_LINE_BIAS,
                                            ubDipBufCnt);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_OpenStream
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_H264_STREAM_OpenStream(MMP_UBYTE ubStrmSel, MMP_UBYTE ubCamSel, MMP_UBYTE ubUsage, void** ppvHandle, MMP_H264_STREAM_MODE ubUiMode)
{
    MMP_H264_STREAM_OBJ *pstStream = NULL;

    if (ubStrmSel >= VR_MAX_H264_STREAM_NUM) {
        return MMP_ERR_NONE;
    }

    *ppvHandle = (void*)(&m_stH264StreamObj[ubStrmSel]);

    MEMSET(&m_stH264StreamObj[ubStrmSel], 0, sizeof(MMP_H264_STREAM_OBJ));

    pstStream               = &m_stH264StreamObj[ubStrmSel];
    pstStream->ulEncID      = INVALID_ENC_ID;
    pstStream->usStreamType = (ubStrmSel == MMPS_H264_STRM_PRM) ? (VIDENC_STREAM_WIFI_PRM) : (VIDENC_STREAM_WIFI_SCD);
    pstStream->bEnableWifi  = MMP_TRUE;
    pstStream->ubStrmSel    = ubStrmSel;
    pstStream->ubCamSel     = ubCamSel;
    pstStream->ubUiMode     = ubUiMode;
    pstStream->eUsage       = (MMP_H264_STREAM_USAGE)ubUsage;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_StartWifiStream
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_H264_STREAM_StartWifiStream(void* pWifiHandle)
{
    VIDENC_FW_STATUS    eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulTimeout = VR_QUERY_STATES_TIMEOUT;
    MMP_H264_STREAM_OBJ *pstStream = (MMP_H264_STREAM_OBJ*)pWifiHandle;

    if (pstStream && !pstStream->bEnableWifi) {
        return MMP_WIFI_ERR_INVALID_PARAMETERS;
    }

    if (MMP_FALSE == MMPF_VIDENC_IsTimerEnabled()) {
        MMPF_VIDENC_EnableTimer(MMP_TRUE);
    }

    if (pstStream->ulEncID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(pstStream->ulEncID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM) {
            MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_WIFI_PRM);
            MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_WIFI_PRM);

            if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC) {
                OpenScript(COMPO_SCRIPT_DSC_PRM_H264_WIFI);
                OpenPortScript(PORT_SCRIPT_DSC_PRM_H264_WIFI);
            }
            else {
                OpenScript(COMPO_SCRIPT_VR_PRM_BAYER_H264_WIFI);
                OpenPortScript(PORT_SCRIPT_VR_PRM_BAYER_H264_WIFI);
            }
        }
        else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD) {
            MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_WIFI_SCD);
            MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_WIFI_SCD);

            if (pstStream->ubCamSel == SCD_SENSOR) {
                if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC) {
                    OpenScript(COMPO_SCRIPT_DSC_SCD_ANADEC_H264_WIFI);
                    OpenPortScript(PORT_SCRIPT_DSC_SCD_ANADEC_H264_WIFI);
                }
                else {
                    OpenScript(COMPO_SCRIPT_VR_SCD_ANADEC_H264_WIFI);
                    OpenPortScript(PORT_SCRIPT_VR_SCD_ANADEC_WIFI);
                }
            }
            else if (pstStream->ubCamSel == USBH_SENSOR) {
                if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC) {
                    OpenScript(COMPO_SCRIPT_DSC_USBH_H264_WIFI);
                    OpenPortScript(PORT_SCRIPT_DSC_USBH_H264_WIFI);
                }
                else {
                    OpenScript(COMPO_SCRIPT_VR_USBH_H264_WIFI);
                    OpenPortScript(PORT_SCRIPT_VR_USBH_WIFI);
                }
            }
        }
    }

    if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM) {
        pstStream->ulEncID = m_ulH264PrmStreamID;
    }
    else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD) {
        pstStream->ulEncID = m_ulH264ScdStreamID;
    }
    else {
        return MMP_WIFI_ERR_INVALID_PARAMETERS;
    }

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        if (MMPF_VIDMGR_StreamingStartEnc(pstStream->ulEncID, pstStream->usStreamType) != MMP_ERR_NONE) {
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(pstStream->ulEncID);
            if (eEncFwSts != VIDENC_FW_STATUS_START) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_START) && (--ulTimeout) > 0);

        if (ulTimeout == 0) {
            MMPS_VR_DBG_ERR(1, "H264 WIFI Start TimeOut\r\n");
            return MMP_WIFI_ERR_PARAMETER;
        }

        MMPS_H264_STREAM_EnablePipe(pstStream->ubStrmSel, MMP_TRUE);

        return MMP_ERR_NONE;
    }
    else {
        return MMP_WIFI_ERR_PARAMETER;
    }
}

#if(SUPPORT_UVC_FUNC)
//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_StartUVCStream
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_H264_STREAM_StartUVCStream(void* pvStreamHandle)
{
    VIDENC_FW_STATUS    eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ULONG           ulTimeout = VR_QUERY_STATES_TIMEOUT;
    MMP_H264_STREAM_OBJ *pstStream = (MMP_H264_STREAM_OBJ*)pvStreamHandle;

    if (pstStream && !pstStream->bEnableWifi) {
        return MMP_WIFI_ERR_INVALID_PARAMETERS;
    }

    if (MMP_FALSE == MMPF_VIDENC_IsTimerEnabled()) {
        MMPF_VIDENC_EnableTimer(MMP_TRUE);
    }

    if (pstStream->ulEncID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(pstStream->ulEncID);

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)) {

        if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM) {
            MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_WIFI_PRM);
            MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_WIFI_PRM);

            OpenScript(COMPO_SCRIPT_PCAM_PRM_H264);

            if (MMP_TRUE == pcam_usb_get_mix_mode()) {
                OpenPortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
            }
            else {
                OpenPortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
            }
        }
        else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD) { // TBD
            MMPS_3GPRECD_AdjustH264CompMemory(VIDENC_STREAM_WIFI_SCD);
            MMPS_3GPRECD_AdjustMGRMemory(VIDENC_STREAM_WIFI_SCD);

            OpenScript(COMPO_SCRIPT_PCAM_SCD_H264);

            if (MMP_TRUE == pcam_usb_get_mix_mode()) {
                //OpenPortScript(PORT_SCRIPT_VR_SCD_PCAM);
            }
            else {
                //OpenPortScript(PORT_SCRIPT_VR_SCD_PCAM);
            }
        }
    }

    if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM) {
        pstStream->ulEncID = m_ulH264PrmStreamID;
    }
    else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD) {
        pstStream->ulEncID = m_ulH264ScdStreamID;
    }
    else {
        return MMP_WIFI_ERR_INVALID_PARAMETERS;
    }

    if ((eEncFwSts == VIDENC_FW_STATUS_NONE) ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP) ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        if (MMPF_VIDMGR_StreamingStartEnc(pstStream->ulEncID, pstStream->usStreamType) != MMP_ERR_NONE) {
            return MMP_3GPRECD_ERR_GENERAL_ERROR;
        }

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(pstStream->ulEncID);
            if (eEncFwSts != VIDENC_FW_STATUS_START) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_START) && (--ulTimeout) > 0);

        if (ulTimeout == 0) {
            MMPS_VR_DBG_ERR(1, "H264 UVC Start TimeOut\r\n");
            return MMP_WIFI_ERR_PARAMETER;
        }

        MMPS_H264_STREAM_EnablePipe(pstStream->ubStrmSel, MMP_TRUE);

        return MMP_ERR_NONE;
    }
    else {
        return MMP_WIFI_ERR_PARAMETER;
    }
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_StopStream
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_H264_STREAM_StopStream(void** ppvStreamHandle)
{
    MMP_ULONG               i = 0;
    MMP_ULONG               ulVidNumActive = 0;
    MMP_H264_STREAM_OBJ     **ppstHeadStreamHandler = (MMP_H264_STREAM_OBJ**)ppvStreamHandle;
    MMP_H264_STREAM_OBJ     *pstStream = NULL;
    VIDENC_FW_STATUS        eEncFwSts = VIDENC_FW_STATUS_NONE;
    MMP_ULONG               ulTimeout = VR_QUERY_STATES_TIMEOUT;

    if (!ppstHeadStreamHandler) {
        MMPS_VR_DBG_ERR(1, "Invalid H264 WIFI Handle\r\n");
        return MMP_WIFI_ERR_INVALID_PARAMETERS;
    }

    for (i = 0; i < VR_MAX_H264_STREAM_NUM; i++) {
        if (*ppstHeadStreamHandler && (*ppstHeadStreamHandler)->bEnableWifi)
            break;

        if (i == VR_MAX_H264_STREAM_NUM)
            return MMP_WIFI_ERR_INVALID_PARAMETERS;
        else
            ppstHeadStreamHandler++;
    }

    pstStream = *ppstHeadStreamHandler;

    /* Close Port */
    if (pstStream->eUsage == MMP_H264_STREAM_USAGE_PCAM) {
        if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM) {
            if (MMP_TRUE == pcam_usb_get_mix_mode()) {
                ClosePortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
            }
            else {
                ClosePortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
            }
        }
        else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD) {
            //ClosePortScript(PORT_SCRIPT_VR_SCD_PCAM);
        }
    }
    else if (pstStream->eUsage == MMP_H264_STREAM_USAGE_WIFI) {

        if (pstStream->ubCamSel == PRM_SENSOR) {
            if(pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC)
                ClosePortScript(PORT_SCRIPT_DSC_PRM_H264_WIFI);
            else
                ClosePortScript(PORT_SCRIPT_VR_PRM_BAYER_H264_WIFI);
        }
        else if (pstStream->ubCamSel == SCD_SENSOR) {
            if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC)
                ClosePortScript(PORT_SCRIPT_DSC_SCD_ANADEC_H264_WIFI);
            else
                ClosePortScript(PORT_SCRIPT_VR_SCD_ANADEC_WIFI);
        }
        else if (pstStream->ubCamSel == USBH_SENSOR) {
            if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC)
                ClosePortScript(PORT_SCRIPT_DSC_USBH_H264_WIFI);
            else
                ClosePortScript(PORT_SCRIPT_VR_USBH_WIFI);
        }
    }
    else {
        return MMP_ERR_NONE;
    }

    if (pstStream->ulEncID == INVALID_ENC_ID)
        eEncFwSts = VIDENC_FW_STATUS_NONE;
    else
        eEncFwSts = MMPF_VIDENC_GetStatus(pstStream->ulEncID);

    if ((eEncFwSts == VIDENC_FW_STATUS_START)   ||
        (eEncFwSts == VIDENC_FW_STATUS_PAUSE)   ||
        (eEncFwSts == VIDENC_FW_STATUS_RESUME)  ||
        (eEncFwSts == VIDENC_FW_STATUS_STOP)    ||
        (eEncFwSts == VIDENC_FW_STATUS_PREENCODE)) {

        MMPF_VIDMGR_StreamingStopEnc(pstStream->ulEncID, pstStream->usStreamType);

        do {
            eEncFwSts = MMPF_VIDENC_GetStatus(pstStream->ulEncID);
            if (eEncFwSts != VIDENC_FW_STATUS_STOP) {
                MMPF_OS_SleepMs(10);
            }
        } while ((eEncFwSts != VIDENC_FW_STATUS_STOP) && ((--ulTimeout) > 0));

        if (0 == ulTimeout) {
            MMPS_VR_DBG_ERR(1, "H264 Stream Stop TimeOut\r\n");
        }

        // Deinit H264 module if all stream are stop.
        if (MMPF_VIDENC_GetActiveInstCnt() == 0) {
            if (MMPF_VIDENC_IsModuleInit()) {
                MMPF_VIDENC_DeinitModule();
            }
        }

        if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM)
            m_ulH264PrmStreamID = INVALID_ENC_ID;
        else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD)
            m_ulH264ScdStreamID = INVALID_ENC_ID;
        else
            return MMP_WIFI_ERR_INVALID_PARAMETERS;
    }
    else if (eEncFwSts == VIDENC_FW_STATUS_NONE) {

        ulVidNumActive = MMPF_VIDENC_GetActiveInstCnt();

        if ((ulVidNumActive > 0) && (pstStream->ulEncID != INVALID_ENC_ID)) {

            MMPF_VIDENC_DeInitInstance(pstStream->ulEncID);

            if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM)
                m_ulH264PrmStreamID = INVALID_ENC_ID;
            else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD)
                m_ulH264ScdStreamID = INVALID_ENC_ID;
            else
                return MMP_WIFI_ERR_INVALID_PARAMETERS;

            if (MMPF_VIDENC_GetActiveInstCnt() == 0) {
                if (MMPF_VIDENC_IsModuleInit()) {
                    MMPF_VIDENC_DeinitModule();
                }
            }
        }
    }
    else {
        return MMP_WIFI_ERR_PARAMETER;
    }

    MMPS_H264_STREAM_EnablePipe(pstStream->ubCamSel, MMP_FALSE);

    /* Close Script */
    if (pstStream->eUsage == MMP_H264_STREAM_USAGE_PCAM) {
        if (pstStream->ubStrmSel == MMPS_H264_STRM_PRM) {
            CloseScript(COMPO_SCRIPT_PCAM_PRM_H264);
        }
        else if (pstStream->ubStrmSel == MMPS_H264_STRM_SCD) {
            CloseScript(COMPO_SCRIPT_PCAM_SCD_H264);
        }
    }
    else if (pstStream->eUsage == MMP_H264_STREAM_USAGE_WIFI) {

        if (pstStream->ubCamSel == PRM_SENSOR) {
            if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC)
                CloseScript(COMPO_SCRIPT_DSC_PRM_H264_WIFI);
            else
                CloseScript(COMPO_SCRIPT_VR_PRM_BAYER_H264_WIFI);
        }
        else if (pstStream->ubCamSel == SCD_SENSOR) {
            if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC)
                CloseScript(COMPO_SCRIPT_DSC_SCD_ANADEC_H264_WIFI);
            else
                CloseScript(COMPO_SCRIPT_VR_SCD_ANADEC_H264_WIFI);
        }
        else if (pstStream->ubCamSel == USBH_SENSOR) {
            if (pstStream->ubUiMode == MMP_H264_STREAM_MODE_DSC)
                CloseScript(COMPO_SCRIPT_DSC_USBH_H264_WIFI);
            else
                CloseScript(COMPO_SCRIPT_VR_USBH_H264_WIFI);
        }
    }

    MMPS_H264_STREAM_Return2Display(pstStream);

    pstStream->bEnableWifi = MMP_FALSE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_H264_STREAM_Return2Display
//  Description : TBD
//------------------------------------------------------------------------------
MMP_ERR MMPS_H264_STREAM_Return2Display(void* pvStreamHandle)
{
    return MMP_ERR_NONE;
}
#endif

#if 0
void ____UVC_Stream_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_YUV422_STREAM_OpenUVCStream
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_YUV422_STREAM_OpenUVCStream(void* pvUvcCfg)
{
    USBH_UVC_CB_FUNC_CFG    *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;
    void                    *pvHandler = NULL;
    UVC_COMP_FORMAT         eVidFmt = UVC_COMP_FORMAT_YUV422;
    MMP_UBYTE               ubCamSel = pstUvcCBCfg->ubCamSel;
    MMP_UBYTE               ubBufCnt = 2;
    MMP_ULONG               ulBufSize = 0;
    UVC_COMP_RESOL          stUvcResol;

    if (ubCamSel == PRM_SENSOR) {
        pvHandler = &Component_UVC[UVC_COMP_FCAM_PREVIEW];
    }
    else {
        pvHandler = &Component_UVC[UVC_COMP_RCAM_PREVIEW];
    }

    stUvcResol.ulW = pstUvcCBCfg->usStreamW;
    stUvcResol.ulH = pstUvcCBCfg->usStreamH;
    Component_UVC_SetParameter(pvHandler, UVC_COMP_PARAM_RESOL, (void *)(&stUvcResol));

    eVidFmt = UVC_COMP_FORMAT_YUV422;
    Component_UVC_SetParameter(pvHandler, UVC_COMP_PARAM_FORMAT, (void *)(&eVidFmt));

    ubBufCnt = 2;
    Component_UVC_SetParameter(pvHandler, UVC_COMP_PARAM_BUF_COUNT, (void *)(&ubBufCnt));

    ulBufSize = UVC_COMP_BUF_SIZE_YUV422(stUvcResol.ulW, stUvcResol.ulH);
    Component_UVC_SetParameter(pvHandler, UVC_COMP_PARAM_BUF_SIZE, (void *)(&ulBufSize));

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_YUV422_STREAM_StartUVCStream
//  Description : TBD
//------------------------------------------------------------------------------
MMP_ERR MMPS_YUV422_STREAM_StartUVCStream(void* pvUvcCfg)
{
    USBH_UVC_CB_FUNC_CFG *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;

    if (pstUvcCBCfg->ubCamSel == PRM_SENSOR) {
        OpenScript(COMPO_SCRIPT_PCAM_PRM_YUV422);
        if (MMP_TRUE == pcam_usb_get_mix_mode()) {
            OpenPortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
        }
        else {
            OpenPortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
        }
    }
    else if (pstUvcCBCfg->ubCamSel == SCD_SENSOR ||
             pstUvcCBCfg->ubCamSel == USBH_SENSOR) {
        OpenScript(COMPO_SCRIPT_PCAM_SCD_YUV422);
        if (MMP_TRUE == pcam_usb_get_mix_mode()) {
            //OpenPortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
        }
        else {
            //OpenPortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_YUV422_STREAM_StartUVCStream
//  Description : TBD
//------------------------------------------------------------------------------
MMP_ERR MMPS_YUV422_STREAM_StopUVCStream(void* pvUvcCfg)
{
    USBH_UVC_CB_FUNC_CFG *pstUvcCBCfg = (USBH_UVC_CB_FUNC_CFG *)pvUvcCfg;

    if (pstUvcCBCfg->ubCamSel == PRM_SENSOR) {
        if (MMP_TRUE == pcam_usb_get_mix_mode()) {
            ClosePortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
        }
        else {
            ClosePortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
        }
    }
    else if (pstUvcCBCfg->ubCamSel == SCD_SENSOR ||
             pstUvcCBCfg->ubCamSel == USBH_SENSOR) {

    }

    /* Close Script */
    if (pstUvcCBCfg->ubCamSel == PRM_SENSOR) {
        CloseScript(COMPO_SCRIPT_PCAM_PRM_YUV422);
    }
    else if (pstUvcCBCfg->ubCamSel == SCD_SENSOR ||
             pstUvcCBCfg->ubCamSel == USBH_SENSOR) {
        CloseScript(COMPO_SCRIPT_PCAM_SCD_YUV422);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetUVCPreviewPipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetUVCPreviewPipe( USBH_UVC_CB_FUNC_CFG    * pstUvcCBCfg )
{
    MMP_UBYTE  ubCamSel     = pstUvcCBCfg->ubCamSel;
    MMP_USHORT usStreamW    = pstUvcCBCfg->usStreamW;
    MMP_USHORT usStreamH    = pstUvcCBCfg->usStreamH;
    MMP_USHORT usStreamFmt  = pstUvcCBCfg->usStreamFmt;

    MMP_ULONG                   ulScaleInW = 0, ulScaleInH = 0;
    MMP_ULONG                   ulScaleAlignOutW = 0, ulScaleAlignOutH = 0;
    MMP_ULONG                   ulDIPAlignOutW = 0, ulDIPAlignOutH = 0;
    MMP_ERR                     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE                   ubInColor, ubOutColor;
    MMPS_3GPRECD_VIDEO_FORMAT   eVidFmt = (MMPS_3GPRECD_VIDEO_FORMAT)usStreamFmt;

    if (eVidFmt == MMPS_3GPRECD_VIDEO_FORMAT_YUV422) {
        ubInColor  = DIP_COMP_COLOR_FMT_YUV420_UV;
        ubOutColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
    }
    else if (eVidFmt == MMPS_3GPRECD_VIDEO_FORMAT_H264) {
        ubInColor  = DIP_COMP_COLOR_FMT_YUV420_UV;
        ubOutColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    }
    else {
        ubInColor  = DIP_COMP_COLOR_FMT_YUV420_UV;
        ubOutColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    }

    if (MMP_FALSE == pcam_usb_get_mix_mode()) {

        MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);

        ulScaleAlignOutW = ALIGN_X(ulScaleInW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulScaleAlignOutH = ALIGN_X(ulScaleInH, DIP_S_COMP_WIDTH_ALIGN_BASE);

        eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL0,
                                            SCL0_COMP_PRM_CAM,
                                            1, 1, ulScaleInW, ulScaleInH,
                                            1, 1, ulScaleAlignOutW, ulScaleAlignOutH,
                                            SCL_COMP_RECORD_BUF_COUNT);

        ulDIPAlignOutW = ALIGN_X(usStreamW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulDIPAlignOutH = ALIGN_X(usStreamH, DIP_S_COMP_WIDTH_ALIGN_BASE);

        eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                            DIP_S_COMP_VR_FCAM_STREAMING,
                                            0, 0, ulScaleAlignOutW, ulScaleAlignOutH,
                                            0, 0, ulScaleAlignOutW, ulScaleAlignOutH,
                                            0, 0, ulDIPAlignOutW, ulDIPAlignOutH,
                                            ubInColor,
                                            ubOutColor,
                                            DIP_COMP_MIRROR_DIS,
                                            MFE_SHARE_BUF_LINE_BIAS,
                                            DIP_COMP_RECORD_BUF_COUNT);

        if (pcam_usb_get_2nd_vid_fmt() != 0) {
            
            MMP_ULONG AlgoWidth  = MDTC_WIDTH;
            MMP_ULONG AlgoHeight = MDTC_HEIGHT;

            ulDIPAlignOutW = ALIGN_X(pcam_usb_get_info()->pCam2ndVideoWidth, DIP_S_COMP_WIDTH_ALIGN_BASE);
            ulDIPAlignOutH = ALIGN_X(pcam_usb_get_info()->pCam2ndVideoHeight, DIP_S_COMP_WIDTH_ALIGN_BASE);

            if (pcam_usb_get_2nd_vid_fmt() == PCAM_USB_VIDEO_FORMAT_MJPEG) {
                ubInColor  = DIP_COMP_COLOR_FMT_YUV420_UV;
                ubOutColor = DIP_COMP_COLOR_FMT_YUV420_UV;
            }

            eRetErr |= MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                                DIP_S_COMP_VR_FCAM_STREAMING_2,
                                                0, 0, ulScaleAlignOutW, ulScaleAlignOutH,
                                                0, 0, ulScaleAlignOutW, ulScaleAlignOutH,
                                                0, 0, ulDIPAlignOutW, ulDIPAlignOutH,
                                                ubInColor,
                                                ubOutColor,
                                                (pcam_usb_get_info()->pCam2ndVideoMirrorEn)? DIP_COMP_MIRROR_EN : DIP_COMP_MIRROR_DIS,
                                                MFE_SHARE_BUF_LINE_BIAS,
                                                DIP_COMP_RECORD_BUF_COUNT);

            eRetErr |= MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL1,
                                                SCL1_COMP_PRM_CAM,
                                                1, 1, ulScaleAlignOutW, ulScaleAlignOutH, //m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW, m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH,
                                                1, 1, AlgoWidth, AlgoHeight,
                                                SCL_COMP_PREVW_BUF_COUNT);

            OpenScript(COMPO_SCRIPT_PCAM_DUAL_STREAM_SRC);

            #if 1 //(MOTION_DETECTION_EN)
            if (pcam_usb_get_info()->pCamEnableMDTC == MMP_TRUE) {   
                
                eRetErr |= MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                                    DIP_S_COMP_VR_FCAM_ADAS,
                                                    0, 0, AlgoWidth, AlgoHeight,
                                                    0, 0, AlgoWidth, AlgoHeight,
                                                    0, 0, AlgoWidth, AlgoHeight,
                                                    DIP_COMP_COLOR_FMT_YUV420_UV,
                                                    DIP_COMP_COLOR_FMT_YUV420_UV,
                                                    DIP_COMP_MIRROR_DIS,
                                                    0,
                                                    DIP_COMP_PREVW_BUF_COUNT);
            
                AHC_SetMotionDtcSensitivity(pcam_usb_get_info()->pCamMdtcSensitivity, 5);
                MMPS_Sensor_RegisterVMDCallback(MMPS_IVA_EVENT_MDTC, (void *)usb_uvc_mdtc_tx);

                OpenScript(COMPO_SCRIPT_MDTC);
                OpenPortScript(PORT_SCRIPT_ALGORITHM_PCAM);

                MMPS_Sensor_EnableVMD(MMP_TRUE); // Need to enable MD after OpenScript(COMPO_SCRIPT_MDTC) which will init MD
            }
            #endif
            
        }
        else {
            OpenScript(COMPO_SCRIPT_PURE_PCAM_PRM_SRC);
        }

    }
    else {

        ulScaleInW = m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufW;
        ulScaleInH = m_stAhcH264RecdInfo[ubCamSel].ulVidEncBufH;

        ulDIPAlignOutW = ALIGN_X(usStreamW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulDIPAlignOutH = ALIGN_X(usStreamH, DIP_S_COMP_WIDTH_ALIGN_BASE);

        eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                            DIP_S_COMP_VR_FCAM_STREAMING,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            0, 0, ulDIPAlignOutW, ulDIPAlignOutH,
                                            ubInColor,
                                            ubOutColor,
                                            DIP_COMP_MIRROR_DIS,
                                            MFE_SHARE_BUF_LINE_BIAS,
                                            DIP_COMP_RECORD_BUF_COUNT);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_CloseUVCPreviewSrc
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_CloseUVCPreviewSrc(MMP_UBYTE ubCamSel)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (MMP_FALSE == pcam_usb_get_mix_mode()) {

        if (pcam_usb_get_2nd_vid_fmt() != 0) {
            if (pcam_usb_get_info()->pCamEnableMDTC == MMP_TRUE) {   
                MMPS_Sensor_EnableVMD(MMP_FALSE);
                CloseScript(COMPO_SCRIPT_MDTC);
                ClosePortScript(PORT_SCRIPT_ALGORITHM_PCAM);
            }
            eRetErr = CloseScript(COMPO_SCRIPT_PCAM_DUAL_STREAM_SRC);
        }
        else {
            eRetErr = CloseScript(COMPO_SCRIPT_PURE_PCAM_PRM_SRC);
        }
    }

    return eRetErr;
}

#if 0
void ____VR_Zoom_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetZoomConfig
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set zoom config

The function set zoom config, total step and max zoom multiplier

@param[in] usMaxSteps   max zoom steps.
@param[in] usMaxRatio   max zoom ratio.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_3GPRECD_SetZoomConfig(MMP_USHORT usMaxSteps, MMP_USHORT usMaxRatio)
{
    m_VidPreviewZoomInfo.usMaxZoomSteps = usMaxSteps;
    m_VidPreviewZoomInfo.usMaxZoomRatio = usMaxRatio;

    m_VidRecordZoomInfo.usMaxZoomSteps  = usMaxSteps;
    m_VidRecordZoomInfo.usMaxZoomRatio  = usMaxRatio;

    m_bAhcConfigVideoRZoom = MMP_TRUE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_InitDigitalZoomParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_InitDigitalZoomParam(MMP_UBYTE ubPipe)
{
    if (ubPipe == m_PreviewPipe)
    {
        // Initial preview zoom parameters
        m_VidPreviewZoomInfo.scalerpath     = m_PreviewPipe;
        m_VidPreviewZoomInfo.usCurZoomStep  = 0;
        m_VidPreviewZoomInfo.usMaxZoomRatio = gsVidPtzCfg.usMaxZoomRatio;
        m_VidPreviewZoomInfo.usMaxZoomSteps = gsVidPtzCfg.usMaxZoomSteps;
        m_VidPreviewZoomInfo.sMaxPanSteps   = gsVidPtzCfg.sMaxPanSteps;
        m_VidPreviewZoomInfo.sMinPanSteps   = gsVidPtzCfg.sMinPanSteps;
        m_VidPreviewZoomInfo.sMaxTiltSteps  = gsVidPtzCfg.sMaxTiltSteps;
        m_VidPreviewZoomInfo.sMinTiltSteps  = gsVidPtzCfg.sMinTiltSteps;

        MMPD_PTZ_InitPtzRange(m_VidPreviewZoomInfo.scalerpath,
                              m_VidPreviewZoomInfo.usMaxZoomRatio,
                              m_VidPreviewZoomInfo.usMaxZoomSteps,
                              m_VidPreviewZoomInfo.sMaxPanSteps,
                              m_VidPreviewZoomInfo.sMinPanSteps,
                              m_VidPreviewZoomInfo.sMaxTiltSteps,
                              m_VidPreviewZoomInfo.sMinTiltSteps);

        MMPD_PTZ_SetDigitalZoom(m_VidPreviewZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);
    }
    else if (ubPipe == 0/*m_RecordFctlLink.scalerpath*/)
    {
        // Initail video zoom parameters
        m_VidRecordZoomInfo.scalerpath      = 0;
        m_VidRecordZoomInfo.usCurZoomStep   = 0;
        m_VidRecordZoomInfo.usMaxZoomRatio  = gsVidPtzCfg.usMaxZoomRatio;
        m_VidRecordZoomInfo.usMaxZoomSteps  = gsVidPtzCfg.usMaxZoomSteps;
        m_VidRecordZoomInfo.sMaxPanSteps    = gsVidPtzCfg.sMaxPanSteps;
        m_VidRecordZoomInfo.sMinPanSteps    = gsVidPtzCfg.sMinPanSteps;
        m_VidRecordZoomInfo.sMaxTiltSteps   = gsVidPtzCfg.sMaxTiltSteps;
        m_VidRecordZoomInfo.sMinTiltSteps   = gsVidPtzCfg.sMinTiltSteps;

        MMPD_PTZ_InitPtzRange(m_VidRecordZoomInfo.scalerpath,
                              m_VidRecordZoomInfo.usMaxZoomRatio,
                              m_VidRecordZoomInfo.usMaxZoomSteps,
                              m_VidRecordZoomInfo.sMaxPanSteps,
                              m_VidRecordZoomInfo.sMinPanSteps,
                              m_VidRecordZoomInfo.sMaxTiltSteps,
                              m_VidRecordZoomInfo.sMinTiltSteps);

        MMPD_PTZ_SetDigitalZoom(m_VidRecordZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_RestoreDigitalZoomRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_RestoreDigitalZoomRange(MMP_UBYTE ubPipe)
{
    if (m_usVidStaticZoomIndex)
    {
        if (ubPipe == m_PreviewPipe)
        {
            m_VidPreviewZoomInfo.usCurZoomStep = m_usVidStaticZoomIndex;

            MMPD_PTZ_SetTargetPtzStep(m_VidPreviewZoomInfo.scalerpath,
                                      MMP_PTZ_ZOOM_INC_IN,
                                      m_VidPreviewZoomInfo.usCurZoomStep, 0, 0);

            MMPD_PTZ_SetDigitalZoomOP(PRM_SENSOR,
                                      m_VidPreviewZoomInfo.scalerpath,
                                      MMP_PTZ_ZOOMIN,
                                      MMP_TRUE);
        }
        else if (ubPipe == 0)
        {
            m_VidRecordZoomInfo.usCurZoomStep = m_usVidStaticZoomIndex;

            MMPD_PTZ_SetTargetPtzStep(m_VidRecordZoomInfo.scalerpath,
                                      MMP_PTZ_ZOOM_INC_IN,
                                      m_VidRecordZoomInfo.usCurZoomStep, 0, 0);

            MMPD_PTZ_SetDigitalZoomOP(PRM_SENSOR,
                                      m_VidRecordZoomInfo.scalerpath,
                                      MMP_PTZ_ZOOMIN,
                                      MMP_TRUE);
        }

        // Reset zoom index
        m_usVidStaticZoomIndex = 0;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetCurZoomStep
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_GetCurZoomStep(MMP_UBYTE ubPipe, MMP_USHORT *usCurZoomStep)
{
    MMP_USHORT  usCurStep;
    MMP_ERR     status = MMP_ERR_NONE;

    if (MMP_IsVidPtzEnable() == MMP_FALSE) {
        usCurZoomStep = 0;
        return status;
    }

    if (ubPipe == m_PreviewPipe)
    {
        status = MMPD_PTZ_GetCurPtzStep(m_VidPreviewZoomInfo.scalerpath,
                                        NULL, &usCurStep, NULL, NULL);

        *usCurZoomStep = usCurStep;

        if (m_bVidPreviewActive[0]) {
            m_VidPreviewZoomInfo.usCurZoomStep = usCurStep;
        }
    }
    else if (ubPipe == 0)
    {
        status = MMPD_PTZ_GetCurPtzStep(m_VidRecordZoomInfo.scalerpath,
                                        NULL, &usCurStep, NULL, NULL);

        *usCurZoomStep = usCurStep;

        if (m_bVidRecordActive[0]) {
            m_VidRecordZoomInfo.usCurZoomStep = usCurStep;
        }
    }

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetCurZoomStatus
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMPS_3GPRECD_GetCurZoomStatus(void)
{
    return MMPD_PTZ_GetCurPtzStatus();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetPreviewZoom
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH sPath, MMP_PTZ_ZOOM_DIR sZoomDir, MMP_USHORT usCurZoomStep)
{
    MMP_BOOL            bComplete[2] = {MMP_FALSE, MMP_FALSE};
    MMP_PTZ_ZOOM_INC    sZoomInc;
    MMP_UBYTE           ubPipe;
    MMP_USHORT          usMaxStep = 0;

    if (m_bVidPreviewActive[0] != MMP_TRUE) {
        m_usVidStaticZoomIndex = usCurZoomStep;
        return MMP_ERR_NONE;
    }

    /* Decide the zoom step increment */
    if (sZoomDir == MMP_PTZ_ZOOMIN) {
        sZoomInc = MMP_PTZ_ZOOM_INC_IN;
    }
    else if (sZoomDir == MMP_PTZ_ZOOMOUT) {
        sZoomInc = MMP_PTZ_ZOOM_INC_OUT;
    }

    if ((sPath == MMPS_3GPRECD_ZOOM_PATH_PREV && m_bVidPreviewActive[0]) ||
        (sPath == MMPS_3GPRECD_ZOOM_PATH_RECD && m_bVidRecordActive[0]))
    {
        if (sPath == MMPS_3GPRECD_ZOOM_PATH_PREV) {
            ubPipe      = m_VidPreviewZoomInfo.scalerpath;
            usMaxStep   = m_VidPreviewZoomInfo.usMaxZoomSteps;
        }
        else {
            ubPipe      = m_VidRecordZoomInfo.scalerpath;
            usMaxStep   = m_VidRecordZoomInfo.usMaxZoomSteps;
        }

        MMPD_PTZ_CheckZoomComplete(ubPipe, bComplete);

        if (!bComplete[0]) {

            MMPD_PTZ_SetDigitalZoom(ubPipe, MMP_PTZ_ZOOMSTOP, MMP_TRUE);

            do {
                MMPD_PTZ_CheckZoomComplete(ubPipe, bComplete);
            } while (!bComplete[0]);
        }

        if (sZoomDir == MMP_PTZ_ZOOMIN) {
            MMPD_PTZ_SetTargetPtzStep(ubPipe,
                                      sZoomInc,
                                      usMaxStep, 0, 0);
        }
        else if (sZoomDir == MMP_PTZ_ZOOMOUT) {
            MMPD_PTZ_SetTargetPtzStep(ubPipe,
                                      sZoomInc,
                                      0, 0, 0);
        }

        MMPD_PTZ_SetDigitalZoom(ubPipe, sZoomDir, MMP_TRUE);
    }
    else if (sPath == MMPS_3GPRECD_ZOOM_PATH_BOTH && m_bVidPreviewActive[0] && m_bVidRecordActive[0])
    {
        MMPD_PTZ_CheckZoomComplete(m_VidPreviewZoomInfo.scalerpath, bComplete);
        MMPD_PTZ_CheckZoomComplete(m_VidRecordZoomInfo.scalerpath, bComplete + 1);

        if (!bComplete[0]) {

            MMPD_PTZ_SetDigitalZoom(m_VidPreviewZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);
            MMPD_PTZ_SetDigitalZoom(m_VidRecordZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);

            do {
                MMPD_PTZ_CheckZoomComplete(m_VidPreviewZoomInfo.scalerpath, bComplete);
                MMPD_PTZ_CheckZoomComplete(m_VidRecordZoomInfo.scalerpath, bComplete + 1);
            } while (!bComplete[0] && !bComplete[1]);
        }

        if (sZoomDir == MMP_PTZ_ZOOMIN) {
            MMPD_PTZ_SetTargetPtzStep(m_VidPreviewZoomInfo.scalerpath,
                                      sZoomInc,
                                      m_VidPreviewZoomInfo.usMaxZoomSteps, 0, 0);
        }
        else if (sZoomDir == MMP_PTZ_ZOOMOUT) {
            MMPD_PTZ_SetTargetPtzStep(m_VidPreviewZoomInfo.scalerpath,
                                      sZoomInc,
                                      0, 0, 0);
        }

        MMPD_PTZ_SetDigitalZoom(m_VidPreviewZoomInfo.scalerpath, sZoomDir, MMP_TRUE);

        if (sZoomDir == MMP_PTZ_ZOOMIN) {
            MMPD_PTZ_SetTargetPtzStep(m_VidRecordZoomInfo.scalerpath,
                                      sZoomInc,
                                      m_VidRecordZoomInfo.usMaxZoomSteps, 0, 0);
        }
        else if (sZoomDir == MMP_PTZ_ZOOMOUT) {
            MMPD_PTZ_SetTargetPtzStep(m_VidRecordZoomInfo.scalerpath,
                                      sZoomInc,
                                      0, 0, 0);
        }

        MMPD_PTZ_SetDigitalZoom(m_VidRecordZoomInfo.scalerpath, sZoomDir, MMP_TRUE);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StopAllPipeZoom
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_StopAllPipeZoom(void)
{
    MMP_BOOL bComplete[2] = {MMP_FALSE, MMP_FALSE};

    return MMP_ERR_NONE; //TBD

    if (1)
    {
        MMPD_PTZ_CheckZoomComplete(m_VidPreviewZoomInfo.scalerpath, bComplete);
        MMPD_PTZ_CheckZoomComplete(m_VidRecordZoomInfo.scalerpath, bComplete + 1);

        if ((!bComplete[0]) || (!bComplete[1])) {
            MMPD_PTZ_SetDigitalZoom(m_VidPreviewZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);
            MMPD_PTZ_SetDigitalZoom(m_VidRecordZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);

            do {
                MMPD_PTZ_CheckZoomComplete(m_VidPreviewZoomInfo.scalerpath, bComplete);
                MMPD_PTZ_CheckZoomComplete(m_VidRecordZoomInfo.scalerpath, bComplete + 1);
            } while((!bComplete[0]) || (!bComplete[1]));
        }
    }

    return MMP_ERR_NONE;
}

#if 0
void ____VR_Sticker_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetStickerAttr
//  Description :
//------------------------------------------------------------------------------
/** @brief The function sets the attributes to the video sticker

The function sets the attributes to the specified video sticker with
its sticker ID.

  @param[in] stickerID the sticker ID
  @param[in] stickerAtrribute the sticker attributes
  @return It reports the status of the operation.
*/
MMP_ERR MMPS_3GPRECD_SetStickerAttr(MMP_STICKER_ATTR *pstStickerAttr)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (pstStickerAttr) {
        eRetErr = MMPF_Icon_SetAttributes(pstStickerAttr);
    }
    else {
        return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnableSticker
//  Description :
//------------------------------------------------------------------------------
/** @brief The function enable or disable video recording with sticker

The function enables or disables the specified video sticker with its sticker ID.

@param[in] sStickerID specified the sticker id for video recording
@param[in] bEnable enable or disable the sticker of the specified ID.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID eStickerID, MMP_BOOL bEnable)
{
    if (MMPF_Icon_SetEnable(eStickerID, bEnable) == MMP_ERR_NONE) {
        m_bStickerEnable[eStickerID] = bEnable;
        return MMP_ERR_NONE;
    }
    else {
        return MMP_ICON_ERR_ENABLE;
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_IsStickerEnable
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID eStickerID)
{
    return m_bStickerEnable[eStickerID];
}

#if 0
void ____VR_TimeLapse_Function____(){ruturn;} //dummy
#endif

#if (SUPPORT_TIMELAPSE)
MMPS_3GPRECD_AVI_LIST AVIRiff =
{
    MKTAG('R','I','F','F'),
    327904,
    MKTAG('A','V','I',' ')
};

MMPS_3GPRECD_AVI_LIST AVIHdrl =
{
    MKTAG('L','I','S','T'),
    192,
    MKTAG('h','d','r','l')
};

MMPS_3GPRECD_AVI_LIST AVIStrl =
{
    MKTAG('L','I','S','T'),
    116,
    MKTAG('s','t','r','l')
};

MMPS_3GPRECD_AVI_LIST AVIMovi =
{
    MKTAG('L','I','S','T'),
    4,
    MKTAG('m','o','v','i')
};

MMPS_3GPRECD_AVI_MainHeader AVIMainHdr =
{
    MKTAG('a','v','i','h'),
    0x38,
    33333,
    20000,
    0,
    0x00000010,
    0,
    0,
    1,  // Stream number
    0,
    1280,  // width
    720,   // height
    0,
    0,
    0,
    0
};

MMPS_3GPRECD_AVI_StreamHeader AVIStrHdr =
{
    MKTAG('s','t','r','h'),
    0x38,
    MKTAG('v','i','d','s'),
    MKTAG('M','J','P','G'),
    0,
    0,
    0,
    1000,
    30000,
    0,
    0,
    0,
    0xFFFFFFFF,
    0,
    0,
    0
};

MMPS_3GPRECD_AVI_StreamFormat AVIStrFormat =
{
    MKTAG('s','t','r','f'),
    0x28,
    0x28,
    1280,
    720,
    0x00180001,
    MKTAG('M','J','P','G'),
    1843200,
    0,
    0,
    0,
    0
};

#define AVIINDEX_BUFFER_SIZE (0x50000)

MMPS_3GPRECD_AVI_Header AVIIndex =
{
    MKTAG('i','d','x','1'),
    AVIINDEX_BUFFER_SIZE
};

MMP_UBYTE m_IndexBuff[512];

MMP_ULONG m_ulHeaderSizePos = 0x04;
MMP_ULONG m_ulMoviSizePos = AVIINDEX_BUFFER_SIZE + 0xE0;
MMP_ULONG m_ulMainHdrFNumPos = 0x30;
MMP_ULONG m_ulStrHdrLengthPos = 0x8C;
MMP_ULONG m_ulIndexStartPos = 0xDC;

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_InitAVIFile
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_InitAVIFile(MMP_BYTE *bAviName, MMP_ULONG ulNameSize, MMP_ULONG ulWidth, MMP_ULONG ulHeight,
                                 MMP_ULONG CoedcFourCC, MMP_ULONG FrameRate, MMP_ULONG ulBitRate, MMP_BOOL bInit, MMP_ULONG *FileID)
{
    MMP_ERR error;
    MMP_ULONG ulWriteCnt = 0, i, BufSize = sizeof(m_IndexBuff);

    if (!bInit) {
        return MMPS_FS_FileOpen(bAviName, ulNameSize, "r+b", sizeof("r+b"), FileID);
    }
    else {

        error = MMPS_FS_FileOpen(bAviName, ulNameSize, "w+b", sizeof("w+b"), FileID);

        if (error != MMP_ERR_NONE || *FileID == 0) {
            *FileID = 0;
            return error;
        }

        memset(m_IndexBuff, 0, BufSize);

        if (ulWidth != 0) {
            AVIMainHdr.ulWidth = ulWidth;
            AVIStrFormat.ulWidth = ulWidth;
        }
        if (ulHeight != 0) {
            AVIMainHdr.ulHeight = ulHeight;
            AVIStrFormat.ulHeight = ulHeight;
        }
        if (CoedcFourCC != 0) {
            AVIStrHdr.Handler = CoedcFourCC;
            AVIStrFormat.ubCompression = CoedcFourCC;
        }
        if (FrameRate != 0) {
            AVIStrHdr.ulRate = FrameRate;
            AVIMainHdr.ulMSecPreFrame = (1000*1000*1000) / FrameRate;
        }
        if (ulBitRate != 0) {
            AVIMainHdr.ulMaxByteRate = ulBitRate/8;
        }

        AVIStrFormat.ulImageSize = (AVIMainHdr.ulWidth * AVIMainHdr.ulHeight) << 1;

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIRiff, sizeof(AVIRiff), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIHdrl, sizeof(AVIHdrl), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIMainHdr, sizeof(AVIMainHdr), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIStrl, sizeof(AVIStrl), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIStrHdr, sizeof(AVIStrHdr), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIStrFormat, sizeof(AVIStrFormat), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIIndex, sizeof(AVIIndex), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }

        for (i = 0; i < AVIIndex.ulSize; i += BufSize) {
            if ((AVIIndex.ulSize - i) < BufSize) {
                error = MMPS_FS_FileWrite(*FileID, m_IndexBuff, (AVIIndex.ulSize - i), &ulWriteCnt);
                if (error != MMP_ERR_NONE) {
                    return error;
                }
            }
            else {
                error = MMPS_FS_FileWrite(*FileID, m_IndexBuff, BufSize, &ulWriteCnt);
                if (error != MMP_ERR_NONE) {
                    return error;
                }
            }
        }

        error = MMPS_FS_FileWrite(*FileID, (MMP_UBYTE *)&AVIMovi, sizeof(AVIMovi), &ulWriteCnt);
        if (error != MMP_ERR_NONE) {
            return error;
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_AVIAppendFrame
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_AVIAppendFrame(MMP_ULONG ulFID, MMP_UBYTE *pData, MMP_ULONG ulSize, MMP_ULONG64 *ulFileSize, MMP_ULONG *ulFrameNum)
{
    MMP_ERR                     error;
    MMP_ULONG                   ulWriteCnt = 0;
    MMP_ULONG64                 ulFSize = 0, ulTempSize, ulTempLen;
    MMPS_3GPRECD_AVI_Header     Chunk;
    MMP_UBYTE                   TempData[4];
    MMPS_3GPRECD_AVI_IndexEntry Entry;

    Chunk.ubFourCC = MKTAG('0','0','d','c');
    Chunk.ulSize = ulSize;
    ulSize = ulSize + (ulSize&0x01);

    MMPS_FS_FileGetSize(ulFID, &ulFSize);

    if (((MMP_ULONG64)((MMP_ULONG64)ulFSize + (MMP_ULONG64)ulSize)) > 0xFFFFFFFF) {
        *ulFileSize = ulFSize;
        return MMP_FS_ERR_WRITE_FAIL;
    }

    MMPS_FS_FileSeek(ulFID, m_ulMainHdrFNumPos, MMPS_FS_SEEK_SET);
    MMPS_FS_FileRead(ulFID, TempData, 4, &ulWriteCnt);

    ulTempLen = TempData[0] | TempData[1] << 8 | TempData[2] << 16 | TempData[3] << 24;
    if (ulTempLen >= (AVIIndex.ulSize / 16)) {
        *ulFrameNum = ulTempLen;
        return MMP_FS_ERR_WRITE_FAIL;
    }

    MMPS_FS_FileSeek(ulFID, 0, MMPS_FS_SEEK_END);

    error = MMPS_FS_FileWrite(ulFID, (MMP_UBYTE *)&Chunk, sizeof(Chunk), &ulWriteCnt);
    if (error != MMP_ERR_NONE) {
        return error;
    }
    error = MMPS_FS_FileWrite(ulFID, pData, ulSize, &ulWriteCnt);
    if (error != MMP_ERR_NONE) {
        return error;
    }

    *ulFileSize = ulFSize + ulSize + sizeof(Chunk);
    MMPS_FS_FileSeek(ulFID, m_ulHeaderSizePos, MMPS_FS_SEEK_SET);
    ulTempSize = *ulFileSize - m_ulHeaderSizePos - 4;

    error = MMPS_FS_FileWrite(ulFID, (MMP_UBYTE *)&ulTempSize, 4, &ulWriteCnt);
    if (error != MMP_ERR_NONE) {
        return error;
    }

    // Set Main header frame number
    MMPS_FS_FileSeek(ulFID, m_ulMainHdrFNumPos, MMPS_FS_SEEK_SET);
    MMPS_FS_FileRead(ulFID, TempData, 4, &ulWriteCnt);
    ulTempLen = TempData[0] | TempData[1] << 8 | TempData[2] << 16 | TempData[3] << 24;
    ulTempLen++;
    *ulFrameNum = ulTempLen;

    MMPS_FS_FileSeek(ulFID, m_ulMainHdrFNumPos, MMPS_FS_SEEK_SET);
    error = MMPS_FS_FileWrite(ulFID, (MMP_UBYTE *)&ulTempLen, 4, &ulWriteCnt);
    if (error != MMP_ERR_NONE) {
        return error;
    }

    // Set Stream header frame number
    MMPS_FS_FileSeek(ulFID, m_ulStrHdrLengthPos, MMPS_FS_SEEK_SET);
    error = MMPS_FS_FileWrite(ulFID, (MMP_UBYTE *)&ulTempLen, 4, &ulWriteCnt);
    if (error != MMP_ERR_NONE) {
        return error;
    }

    // Set Index entry
    Entry.ubFourCC = MKTAG('0','0','d','c');
    Entry.ulFlag = 0x00000010;
    Entry.ulPos = ulFSize;
    Entry.ulSize = Chunk.ulSize;
    ulTempLen--;

    MMPS_FS_FileSeek(ulFID, (m_ulIndexStartPos + (ulTempLen*16)), MMPS_FS_SEEK_SET);
    error = MMPS_FS_FileWrite(ulFID, (MMP_UBYTE *)&Entry, sizeof(Entry), &ulWriteCnt);
    if (error != MMP_ERR_NONE) {
        return error;
    }

    // Set Movi Size
    MMPS_FS_FileSeek(ulFID, m_ulMoviSizePos, MMPS_FS_SEEK_SET);
    ulTempSize = *ulFileSize - m_ulMoviSizePos - 4;
    error = MMPS_FS_FileWrite(ulFID, (MMP_UBYTE *)&ulTempSize, 4, &ulWriteCnt);
    if (error != MMP_ERR_NONE) {
        return error;
    }

    return error;
}
#endif

#if 0
void ____VR_Emergent_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetEmergActionType
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set emergency record flow type.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetEmergActionType(MMP_3GPRECD_EMERG_ACTION emergact)
{
    m_eEmergActionType = emergact;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetEmergActionType
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Check what emergency record flow type is.
 @retval MMP_ERR_NONE Success.
*/
MMP_3GPRECD_EMERG_ACTION MMPS_3GPRECD_GetEmergActionType(void)
{
    return m_eEmergActionType;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetEmergFileName
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Send emergent 3GP file name to firmware for card mode and creat file time.
 @param[in] bFilename File name.
 @param[in] usLength Length of file name in unit of byte.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetEmergFileName(MMP_BYTE bFilename[], MMP_USHORT usLength)
{
    #if (EMERGENTRECD_SUPPORT)
    MMPS_FS_SetCreationTime();
    MMPD_3GPMGR_SetFileName(VIDENC_STREAM_PRM_EMERG, bFilename, usLength);
    #endif

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnableEmergentRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable emergent video recording.

 Enable emergent video recording.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_EnableEmergentRecd(MMP_BOOL bEnable)
{
    #if (EMERGENTRECD_SUPPORT)
    MMPF_VIDMGR_SetPrmEmergEn(bEnable);
    #endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnableUVCEmergentRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable UVC emergent video recording.

 Enable uvc emergent video recording.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_EnableUVCEmergentRecd(MMP_BOOL bEnable)
{
    #if (UVC_EMERGRECD_SUPPORT)
    MMPF_VIDMGR_SetUvcEmergEn(bEnable);
    #else
    MMPF_VIDMGR_SetUvcEmergEn(MMP_FALSE);
    #endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_EnableDualEmergentRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable Dual emergent video recording.

 Enable uvc emergent video recording.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_EnableDualEmergentRecd(MMP_BOOL bEnable)
{
    #if (DUAL_EMERGRECD_SUPPORT)
    MMPF_VIDMGR_SetScdEmergEn(bEnable);
    #else
    MMPF_VIDMGR_SetScdEmergEn(MMP_FALSE);
    #endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StartEmergentRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start emergent video recording.

 Start to save the 3GP file.
 @param[in] bStopNormRecd: stop normal record, keep emergent record
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_StartEmergentRecd(MMP_BOOL bStopNormRecd)
{
    #if (EMERGENTRECD_SUPPORT)
    return MMPD_3GPMGR_StartEmergentRecd(bStopNormRecd);
    #else
    return MMP_3GPMGR_ERR_UNSUPPORT;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_StopEmergentRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop emergent video recording.

 Stop to save the 3GP file.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_3GPRECD_StopEmergentRecd(MMP_BOOL bBlocking)
{
    #if (EMERGENTRECD_SUPPORT)
    MMP_BOOL    bEnable = MMP_FALSE, bEmergStart = MMP_FALSE;
    MMP_ULONG   ulTimeout = VR_QUERY_STATES_TIMEOUT;

    bEnable = MMPF_VIDMGR_IsPrmEmergEn();
    bEmergStart = MMPF_VIDMGR_IsEmergRecdStart();

    if (bEnable && bEmergStart) {

        MMPD_3GPMGR_StopEmergentRecd();

        if (!bBlocking) {
            return MMP_ERR_NONE;
        }

        do {
            bEmergStart = MMPF_VIDMGR_IsEmergRecdStart();
            if (bEmergStart != MMP_FALSE) {
                MMPF_OS_SleepMs(10);
            }
        } while ((bEmergStart != MMP_FALSE) && ((--ulTimeout) > 0));

        if (0 == ulTimeout) {
            MMPS_VR_DBG_ERR(1, "StopEmergentRecd TimeOut\r\n");
        }
    }
    else {
        return MMP_3GPMGR_ERR_INVLAID_STATE;
    }
    #endif

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetEmergentFileTimeLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the maximum 3GP file time for video encoding.
 @param[in] ulTimeLimitMs Maximum file time in unit of ms.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE Space not enough.
*/
MMP_ERR MMPS_3GPRECD_SetEmergentFileTimeLimit(MMP_ULONG ulTimeLimitMs)
{
    #if (EMERGENTRECD_SUPPORT)
    if (ulTimeLimitMs) {
        MMPF_VIDMGR_SetEmergentFileTimeLimit(ulTimeLimitMs);
        return MMP_ERR_NONE;
    }
    #endif

    return MMP_3GPRECD_ERR_INVALID_PARAMETERS;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetEmergPreEncTimeLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the the pre-encoding time limit.
 @param[in] ulTimeLimitMs Maximum file time in ms.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE Space not enough.
*/
MMP_ERR MMPS_3GPRECD_SetEmergPreEncTimeLimit(MMP_ULONG ulTimeLimitMs)
{
    if (ulTimeLimitMs) {
        MMPF_VIDMGR_SetEmergPreEncDuration(ulTimeLimitMs);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetEmergentRecordingTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get emergent recording time.
 @param[out] ulTime Recording time in unit of ms.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_GetEmergentRecordingTime(MMP_ULONG *pulTime)
{
    #if (EMERGENTRECD_SUPPORT)
    return MMPF_VIDMGR_GetRecordingTime(VIDENC_STREAM_PRM_EMERG, pulTime);
    #else
    return MMP_ERR_NONE;
    #endif
}

#if 0
void ____VR_Misc_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetTime2FlushFSCache
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set max time to flush FS cache buffer to SD.

 @param[in] time Set max time (s).
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_3GPRECD_SetTime2FlushFSCache(MMP_ULONG ulTime)
{
#if (SUPPORT_VR_REFIX_TAILINFO)
    m_ulMaxTime2FlushFSCache = ulTime*1000;
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_CheckFile2Refix
//  Description :
//------------------------------------------------------------------------------
/**
 @brief check if there is a file need to be refixed.

 @retval MMP_ERR_NONE Success.
*/
#if (SUPPORT_VR_REFIX_TAILINFO)
MMP_ERR MMPS_3GPRECD_CheckFile2Refix(void)
{
    //MMPF_VIDMGR_SetVidRecdMuxFuncPtr();
    //MMPF_VIDMGR_RefixVidRecdFile(&RefixTailMgr);
    return MMP_ERR_NONE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_SetYFrameType
//  Description : Configure the usage of Y-frame pipe (ex: Motion Detection or LDWS)
//------------------------------------------------------------------------------
MMP_ERR MMPS_3GPRECD_SetYFrameType(MMPS_3GPRECD_Y_FRAME_TYPE enType)
{
#if (SUPPORT_MDTC)||(SUPPORT_ADAS)
    m_eYFrameType = enType;
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_3GPRECD_GetYFrameType
//  Description : Configure the usage of Y-frame pipe (ex: Motion Detection or LDWS)
//------------------------------------------------------------------------------
#if (SUPPORT_MDTC)||(SUPPORT_ADAS)
MMPS_3GPRECD_Y_FRAME_TYPE MMPS_3GPRECD_GetYFrameType(void)
{
    return m_eYFrameType;
}
#endif

/**
 @brief Add Atom IDIT for GVP, the atom store starting time of recording.

 @retval size of atom IDIT
*/
#if (MGR_SUPPORT_AVI == 1)
#if (AVI_IDIT_CHUNK_EN == 1)

#define _3GP_FOURCC(b0, b1, b2, b3) (((unsigned long)(b0)      ) +  \
                                     ((unsigned long)(b1) <<  8) +  \
                                     ((unsigned long)(b2) << 16) +  \
                                     ((unsigned long)(b3) << 24))

#define ATOM_IDIT       _3GP_FOURCC('I', 'D', 'I', 'T')
#define ATOM_IDIT_SIZE  sizeof(struct idit_t)
#define ATOM_IDIT_DACB  20

typedef struct idit_t {
    unsigned long   atombc;
    unsigned long   atomid;
    unsigned char   tmstr[ATOM_IDIT_DACB];
} IDIT_T;

typedef struct idit_avi {
    unsigned long   atomid;
    unsigned long   atombc;
    unsigned char   tmstr[ATOM_IDIT_DACB];
} IDIT_AVI;

extern AUTL_DATETIME gVidRecdRTCTime;

__inline unsigned int CONVERT_ENDIAN(unsigned int d)
{
    unsigned int t = d;

    *((char*)&d + 3) = *((char*)&t + 0);
    *((char*)&d + 2) = *((char*)&t + 1);
    *((char*)&d + 1) = *((char*)&t + 2);
    *((char*)&d + 0) = *((char*)&t + 3);

    return d;
}

unsigned int MMPS_3GPMUX_Build_IDIT(void **ptr)
{
    extern int snprintf(char * /*s*/, size_t /*n*/, const char * /*format*/, ...);

    static IDIT_T   idit;

    idit.atombc = CONVERT_ENDIAN(ATOM_IDIT_SIZE);
    idit.atomid = ATOM_IDIT;

    snprintf((void*)idit.tmstr, ATOM_IDIT_DACB,
             "%04d-%02d-%02d %02d:%02d:%02d",
             gVidRecdRTCTime.usYear,
             gVidRecdRTCTime.usMonth,
             gVidRecdRTCTime.usDay,
             gVidRecdRTCTime.usHour,
             gVidRecdRTCTime.usMinute,
             gVidRecdRTCTime.usSecond);

    *ptr = &idit;

    return ATOM_IDIT_SIZE;
}

unsigned int MMPS_AVIMUX_Build_IDIT(void **ptr)
{
    extern int snprintf(char * /*s*/, size_t /*n*/, const char * /*format*/, ...);

    static IDIT_AVI idit;

    idit.atombc = ATOM_IDIT_DACB;
    idit.atomid = MAKE_FCC('I','D','I','T');;

    snprintf((void*)idit.tmstr, ATOM_IDIT_DACB,
             "%04d-%02d-%02d %02d:%02d:%02d",
             gVidRecdRTCTime.usYear,
             gVidRecdRTCTime.usMonth,
             gVidRecdRTCTime.usDay,
             gVidRecdRTCTime.usHour,
             gVidRecdRTCTime.usMinute,
            gVidRecdRTCTime.usSecond);

    *ptr = &idit;

    return ATOM_IDIT_SIZE;
}

#endif //#if (AVI_IDIT_CHUNK_EN == 1
#endif //#if (MGR_SUPPORT_AVI == 1)

/// @}
