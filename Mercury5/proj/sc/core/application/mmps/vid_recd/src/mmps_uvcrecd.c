
//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmps_3gprecd.h"
#include "mmps_display.h"
#include "mmps_uvcrecd.h"
#include "mmpd_uvcrecd.h"
#include "mmpf_usbh_uvc.h"
#include "mmpf_mp4venc.h"
#include "mmpf_3gpmgr.h"
#include "mmph_hif.h"

#include "mmp_component_ctl.h"
#include "cust_component_cfg.h"
#include "component_cfg.h"
#include "component_jpd.h"
#include "component_dip.h"
#include "component_pip.h"

#include "snr_cfg.h"
//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MMPS_HUVC_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMPS_HUVC_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

MMP_BOOL                                m_bUVCRecdSupport       = MMP_FALSE;
static MMPS_HUVC_AHC_PREVIEW_INFO       m_stAhcVideoUVCPrevInfo  = {0};

/// For Decode MJPEG to Preview attribute
static MMP_USHORT                       m_usDecMjpegToPreviewSrcW = 1280;
static MMP_USHORT                       m_usDecMjpegToPreviewSrcH = 720;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____HUVC_DecMjpegToPreview_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_GetDecMjpegToPreviewSrcAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_GetDecMjpegToPreviewSrcAttr(MMP_USHORT *pusW, MMP_USHORT *pusH)
{
    if (!MMP_IsSupportDecMjpegToPreview()) {
        return MMP_ERR_NONE;
    }

    if (pusW)
        *pusW = m_usDecMjpegToPreviewSrcW;
    if (pusH)
        *pusH = m_usDecMjpegToPreviewSrcH;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetDecMjpegToPreviewSrcAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_SetDecMjpegToPreviewSrcAttr(MMP_USHORT usSrcW, MMP_USHORT usSrcH)
{
    if (!MMP_IsSupportDecMjpegToPreview()) {
        return MMP_ERR_NONE;
    }

    m_usDecMjpegToPreviewSrcW = usSrcW;
    m_usDecMjpegToPreviewSrcH = usSrcH;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_InitVRDecMjpegToPreview
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_InitVRDecMjpegToPreview(MMP_USHORT usJpegSrcW, MMP_USHORT usJpegSrcH)
{
    MMP_UBYTE                       ubCompUseType   = JPD_COMP_MJPEG_DEC;
    MMP_UBYTE                       ubDecSrc        = JPD_COMP_DEC_SRC_MJPEG;
    MMP_UBYTE                       ubDecImgType    = JPD_COMP_IMG_TYPE_PRIMARY;
    MMP_UBYTE                       ubJpdBufCount   = 2;
    MMP_ULONG                       ulBufSize       = 0;
    MMP_COMPONENT_BASE              *pJpdComp       = &Component_JPD[ubCompUseType];
    JPD_COMP_RESOL                  stJpdRect;
    MMP_ERR                         eRetErr = MMP_ERR_NONE;

    if (!MMP_IsSupportDecMjpegToPreview()) {
        return MMP_ERR_NONE;
    }

    if (usJpegSrcW == 0 || usJpegSrcH == 0) {
        return MMP_3GPRECD_ERR_PARAMETER;
    }

    /* Update component JPD setting */
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_SRC, (void*)&ubDecSrc);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_IMG_TYPE, (void*)&ubDecImgType);

    stJpdRect.ulStartX = 0;
    stJpdRect.ulStartY = 0;
    stJpdRect.ulWidth  = usJpegSrcW;
    stJpdRect.ulHeight = usJpegSrcH;
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_RES, (void*)&stJpdRect);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_COUNT, (void*)&ubJpdBufCount);

    ulBufSize = JPD_COMP_BUF_SIZE_YUV422(stJpdRect.ulWidth, stJpdRect.ulHeight); // JPD always output YUV422 format
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_SIZE, (void*)&ulBufSize);

    MMPS_Display_SetUsbhPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_VR, MMPS_DISPLAY_PREVIEW_PIP_WIN);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_VR_RCAM_RECD,
                                        0, 0, usJpegSrcW, usJpegSrcH,
                                        0, 0, usJpegSrcW, usJpegSrcH,
                                        0, 0, usJpegSrcW, usJpegSrcH,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV, // For MFE encode format
                                        DIP_COMP_MIRROR_DIS,
                                        MFE_SHARE_BUF_LINE_BIAS,
                                        DIP_COMP_RECORD_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "DIP Comp Error!", gubMmpDbgBk); return eRetErr; }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_VRDecMjpegPreviewStart
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_VRDecMjpegPreviewStart(void)
{
    if (gbLCDRotate) {
        OpenScript(COMPO_SCRIPT_VR_R_PREV_USBH_SRC);
        OpenScript(COMPO_SCRIPT_VR_R_PREV_USBH_PIP);
    }
    else {
        OpenScript(COMPO_SCRIPT_VR_N_PREV_USBH_SRC);
        OpenScript(COMPO_SCRIPT_VR_N_PREV_USBH_PIP);
    }

    OpenPortScript(PORT_SCRIPT_VR_PREV_USBH_SRC);

    if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, MMP_FALSE) & VID_RECD_ENCODE_H264) {
    	OpenScript(COMPO_SCRIPT_VR_USBH_RECD_SCAL_OSD);
    }
    else if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, MMP_FALSE) == VID_RECD_STORE_FILE) {
    	OpenScript(COMPO_SCRIPT_VR_USBH_UVC_RECD_SCAL_OSD);
    }

    OpenPortScript(PORT_SCRIPT_VR_USBH_RECD_SRC);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_VRDecMjpegPreviewStop
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_VRDecMjpegPreviewStop(void)
{
    ClosePortScript(PORT_SCRIPT_VR_USBH_RECD_SRC);
    //Port_Config_VR_USBH_RECD_SRC;//JPD1-OUTPORT1

    if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, MMP_FALSE) & VID_RECD_ENCODE_H264) {
    	CloseScript(COMPO_SCRIPT_VR_USBH_RECD_SCAL_OSD);
    }
    else if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, MMP_FALSE) == VID_RECD_STORE_FILE) {
    	CloseScript(COMPO_SCRIPT_VR_USBH_UVC_RECD_SCAL_OSD);
    }
    //Component_Config_VR_USBH_RECD_SCAL_OSD;//JPD1<-DIP_S3->JPE4/MFE1/DIP_S6

    ClosePortScript(PORT_SCRIPT_VR_PREV_USBH_SRC);
    //Port_Config_VR_PREV_USBH_SRC;//JPD1-OUTPORT0

    if (gbLCDRotate) {
        CloseScript(COMPO_SCRIPT_VR_R_PREV_USBH_SRC);
        //Component_Config_VR_R_PREV_USBH_SRC;//HostUVC->JPD1->DIP_S1/DIP_S3/DIP_S8

        CloseScript(COMPO_SCRIPT_VR_R_PREV_USBH_FULL);
        //Component_Config_VR_R_PREV_USBH_FULL;//DIP_S1->DIP_R1->DISP
        CloseScript(COMPO_SCRIPT_VR_R_PREV_USBH_PIP);
        //Component_Config_VR_R_PREV_USBH_PIP;//DIP_S1->DIP_R1->PIP0
    }
    else {
        CloseScript(COMPO_SCRIPT_VR_N_PREV_USBH_SRC);
        CloseScript(COMPO_SCRIPT_VR_N_PREV_USBH_FULL);
        CloseScript(COMPO_SCRIPT_VR_N_PREV_USBH_PIP);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_InitDscDecMjpegToPreview
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_InitDscDecMjpegToPreview(MMP_USHORT usJpegSrcW, MMP_USHORT usJpegSrcH)
{
    MMP_UBYTE                       ubCompUseType   = JPD_COMP_MJPEG_DEC;
    MMP_UBYTE                       ubDecSrc        = JPD_COMP_DEC_SRC_MJPEG;
    MMP_UBYTE                       ubDecImgType    = JPD_COMP_IMG_TYPE_PRIMARY;
    MMP_UBYTE                       ubJpdBufCount   = 2;
    MMP_ULONG                       ulBufSize       = 0;
    MMP_COMPONENT_BASE              *pJpdComp       = &Component_JPD[ubCompUseType];
    JPD_COMP_RESOL                  stJpdRect;
    MMP_ERR                         eRetErr = MMP_ERR_NONE;

    if (!MMP_IsSupportDecMjpegToPreview()) {
        return MMP_ERR_NONE;
    }

    if (usJpegSrcW == 0 || usJpegSrcH == 0) {
        return MMP_DSC_ERR_PARAMETER;
    }

    /* Update component JPD setting */
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_SRC, (void*)&ubDecSrc);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_IMG_TYPE, (void*)&ubDecImgType);

    stJpdRect.ulStartX = 0;
    stJpdRect.ulStartY = 0;
    stJpdRect.ulWidth  = usJpegSrcW;
    stJpdRect.ulHeight = usJpegSrcH;
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_RES, (void*)&stJpdRect);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_COUNT, (void*)&ubJpdBufCount);

    ulBufSize = JPD_COMP_BUF_SIZE_YUV422(stJpdRect.ulWidth, stJpdRect.ulHeight); // JPD always output YUV422 format
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_SIZE, (void*)&ulBufSize);

    MMPS_Display_SetUsbhPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_DSC, MMPS_DISPLAY_PREVIEW_PIP_WIN);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_RCAM_CAPTURE,
                                        0, 0, usJpegSrcW, usJpegSrcH,
                                        0, 0, usJpegSrcW, usJpegSrcH,
                                        0, 0, usJpegSrcW, usJpegSrcH,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        DIP_COMP_RECORD_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) {MMP_PRINT_RET_ERROR(0, eRetErr, "DIP Comp Error!",gubMmpDbgBk); return eRetErr;}

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_DscDecMjpegPreviewStart
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_DscDecMjpegPreviewStart(void)
{
    if (gbLCDRotate) {
        OpenScript(COMPO_SCRIPT_DSC_R_PREV_USBH_SRC);
        OpenScript(COMPO_SCRIPT_DSC_R_PREV_USBH_PIP);
    }
    else {
        OpenScript(COMPO_SCRIPT_DSC_N_PREV_USBH_SRC);
        OpenScript(COMPO_SCRIPT_DSC_N_PREV_USBH_PIP);
    }

    OpenPortScript(PORT_SCRIPT_DSC_PREV_USBH);

    OpenScript(COMPO_SCRIPT_DSC_USBH_CAPT_SCAL_OSD);
    OpenPortScript(PORT_SCRIPT_DSC_USBH_CAPTURE_SRC);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_DscDecMjpegPreviewStop
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_DscDecMjpegPreviewStop(void)
{
    ClosePortScript(PORT_SCRIPT_DSC_USBH_CAPTURE_SRC);
    CloseScript(COMPO_SCRIPT_DSC_USBH_CAPT_SCAL_OSD);

    ClosePortScript(PORT_SCRIPT_DSC_PREV_USBH);

    if (gbLCDRotate) {
        CloseScript(COMPO_SCRIPT_DSC_R_PREV_USBH_SRC);
        CloseScript(COMPO_SCRIPT_DSC_R_PREV_USBH_FULL);
        CloseScript(COMPO_SCRIPT_DSC_R_PREV_USBH_PIP);
    }
    else {
        CloseScript(COMPO_SCRIPT_DSC_N_PREV_USBH_SRC);
        CloseScript(COMPO_SCRIPT_DSC_N_PREV_USBH_FULL);
        CloseScript(COMPO_SCRIPT_DSC_N_PREV_USBH_PIP);
    }

    return MMP_ERR_NONE;
}

#if 0
void ____UVC_Recd_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetCustomedPrevwAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set video preview resolution.
 @param[in] bUserConfig     Use user defined preview configuration.
 @param[in] bMirror         Use DIP scale to mirror preview buffer.
 @param[in] sFitMode        Scaler fit mode.
 @param[in] usBufWidth      Preview buffer width.
 @param[in] usBufHeight     Preview buffer height.
 @param[in] usStartX        The X Offset of the display window.
 @param[in] usStartY        The Y Offset of the display window.
 @param[in] usWinWidth      The width of the display window.
 @param[in] usWinHeight     The height of the display window.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_HUVC_SetCustomedPrevwAttr( MMP_BOOL      bUserConfig,
                                        MMP_BOOL      bMirror,
                                        MMP_UBYTE     sFitMode,
                                        MMP_USHORT    usBufWidth, MMP_USHORT usBufHeight,
                                        MMP_USHORT    usStartX,   MMP_USHORT usStartY,
                                        MMP_USHORT    usWinWidth, MMP_USHORT usWinHeight)
{
    m_stAhcVideoUVCPrevInfo.bUserDefine      = bUserConfig;
    m_stAhcVideoUVCPrevInfo.bPreviewMirror   = bMirror;
    m_stAhcVideoUVCPrevInfo.sFitMode         = sFitMode;
    m_stAhcVideoUVCPrevInfo.ulPreviewBufW    = usBufWidth;
    m_stAhcVideoUVCPrevInfo.ulPreviewBufH    = usBufHeight;
    m_stAhcVideoUVCPrevInfo.ulDispStartX     = usStartX;
    m_stAhcVideoUVCPrevInfo.ulDispStartY     = usStartY;
    m_stAhcVideoUVCPrevInfo.ulDispWidth      = usWinWidth;
    m_stAhcVideoUVCPrevInfo.ulDispHeight     = usWinHeight;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_GetCustomedPrevwAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_GetCustomedPrevwAttr( MMP_BOOL      *pbUserConfig,
                                        MMP_BOOL      *pbMirror,
                                        MMP_UBYTE     *psFitMode,
                                        MMP_USHORT    *pusBufWidth,   MMP_USHORT *pusBufHeight,
                                        MMP_USHORT    *pusStartX,     MMP_USHORT *pusStartY,
                                        MMP_USHORT    *pusWinWidth,   MMP_USHORT *pusWinHeight)
{
    *pbUserConfig   = m_stAhcVideoUVCPrevInfo.bUserDefine;
    *pbMirror       = m_stAhcVideoUVCPrevInfo.bPreviewMirror;
    *psFitMode      = m_stAhcVideoUVCPrevInfo.sFitMode;
    *pusBufWidth    = m_stAhcVideoUVCPrevInfo.ulPreviewBufW;
    *pusBufHeight   = m_stAhcVideoUVCPrevInfo.ulPreviewBufH;
    *pusStartX      = m_stAhcVideoUVCPrevInfo.ulDispStartX;
    *pusStartY      = m_stAhcVideoUVCPrevInfo.ulDispStartY;
    *pusWinWidth    = m_stAhcVideoUVCPrevInfo.ulDispWidth;
    *pusWinHeight   = m_stAhcVideoUVCPrevInfo.ulDispHeight;

    return MMP_ERR_NONE;
}

#if (UVC_VIDRECD_SUPPORT)
//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetUVCRecdSupport
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable UVC video recording.

 Enable UVC video recording.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_HUVC_SetUVCRecdSupport(MMP_BOOL bSupport)
{
    m_bUVCRecdSupport = bSupport;

    MMPF_VIDMGR_SetUvcRecdEn(bSupport);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_GetUVCRecdSupport
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get UVC video recording enable states.

Get UVC video recording enable states.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_HUVC_GetUVCRecdSupport(MMP_BOOL *pbSupport)
{
    if (pbSupport) {
        *pbSupport = m_bUVCRecdSupport;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_OpenRecdFile
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Open UVC video recording file.

 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_HUVC_OpenRecdFile(void)
{
    #if (SUPPORT_UVC_FUNC)
    MMP_BOOL bStatus;

    MMPF_USBH_GetUVCPrevwSts(&bStatus);

    if (bStatus == MMP_FALSE) {
        RTNA_DBG_Str3("Enter preview first!\r\n");
        return MMP_USB_ERR_UNSUPPORT_MODE;
    }

    MMPF_USBH_GetUVCRecdSts(&bStatus);

    if (bStatus == MMP_TRUE) {
        RTNA_DBG_Str3("[WARN]: RECDING \r\n");
        return MMP_USB_ERR_UNSUPPORT_MODE;
    }
    #endif

    if (m_bUVCRecdSupport && !MMPF_VIDMGR_GetMultiTrackEn())
    {
        extern MMP_ULONG m_ulPrmRecdID;
        if (MMPF_VIDENC_GetStatus(m_ulPrmRecdID) != VIDENC_FW_STATUS_PREENCODE) {
            MMPF_VIDMGR_UVCOpenFile(VIDENC_STREAM_UVC_RECD);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_EnableRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Enable UVC video recording.

 Enable to inform USBH, and driver will start recording later when I-frame received.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_HUVC_EnableRecd(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetStartFrameofUVCRecd();
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_StopRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop UVC video recording.

 Stop UVC recording and save the 3GP file.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPS_HUVC_StopRecd(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_OPERATION | MERGER_UVCRECD_STOP);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    return MMP_ERR_NONE;
}
#endif

#if (SUPPORT_USB_HOST_FUNC)
//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_StartPreview
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start UVC display preview mode, include stream on(UVC VS_COMMIT_CONTROL).
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS Unsupport resolution.
*/
MMP_ERR MMPS_HUVC_StartPreview(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_StartUVCPrevw();
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_StopPreview
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop UVC display preview mode, and stream off(UVC CLEAR_FEATURE).
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS Unsupport resolution.
*/
MMP_ERR MMPS_HUVC_StopPreview(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_StopUVCPrevw();
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetUVCRecdResol
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set UVC H264 encoded resolution.
 @param[in] usResol Resolution for UVC H264 record video.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS Unsupport resolution.
*/
MMP_ERR MMPS_HUVC_SetUVCRecdResol(MMP_UBYTE ubResol)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCRecdResol(ubResol,
                                        MMPS_3GPRECD_GetPresetCfg()->usEncWidth[ubResol],
                                        MMPS_3GPRECD_GetPresetCfg()->usEncHeight[ubResol]);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetRecdBitrate
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set UVC encoded quality.
 @param[in] ulBitrate Bitrate of UVC record video.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_HUVC_SetRecdBitrate(MMP_ULONG ulBitrate)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCRecdBitrate(ulBitrate);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetRecdFrameRate
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set frame rate for UVC H264 recorded video.
 @param[in] usFrameRate Frame rate for UVC H264 record video.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_HUVC_SetRecdFrameRate(MMP_USHORT usTimeIncrement, MMP_USHORT usTimeIncrResol)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCRecdFrameRate(usTimeIncrement, usTimeIncrResol);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetRecdPFrameCount
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set P frame count of one cycle.
 @param[in] usFrameCount Count of P frame.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_HUVC_SetRecdPFrameCount(MMP_USHORT usFrameCount)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCRecdFrameCount(usFrameCount);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetPrevwResol
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set UVC YUV encoded resolution.
 @param[in] usWidth Resolution width for UVC YUV preview video.
 @param[in] usHeight Resolution height for UVC YUV preview video.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS Unsupport resolution.
*/
MMP_ERR MMPS_HUVC_SetPrevwResol(MMP_USHORT usWidth, MMP_USHORT usHeight)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCPrevwResol(usWidth,usHeight);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetPrevwStrmTyp
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set UVC preview stream type.
 @param[in] ubPrevwStrmTyp Stream type for UVC preview video.
 @retval MMP_ERR_NONE Success.
 @retval MMP_USB_ERR_UNSUPPORT_MODE Unsupport resolution.
*/
MMP_ERR MMPS_HUVC_SetPrevwStrmTyp(MMP_UBYTE ubPrevwStrmTyp)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCPrevwStrmTyp(ubPrevwStrmTyp);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetPrevwFrameRate
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set frame rate for UVC YUV preview video.
 @param[in] ubFps Frame rate for UVC YUV preview video.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_HUVC_SetPrevwFrameRate(MMP_UBYTE ubFps)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCPrevwFrameRate(ubFps);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_AddDevCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function sets UVC device following configs.
@param[in] pubStr Device Chip info strings.
@param[in] pOpenDevCallback The callback to be executed when USB device connected, one part of prob.
@param[in] pStartDevCallback The callback to be executed when UVC device commit(one part of commit).
@param[in] pNaluInfo The H264 nalu info, mejors are sps/pps related.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_HUVC_AddDevCFG(MMP_UBYTE *pubStr, void *pOpenDevCallback, void *pStartDevCallback, void *pNaluInfo)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_AddDevCFG(pubStr, pOpenDevCallback, pStartDevCallback, pNaluInfo);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_UpdDevCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function sets to update UVC device following configs.
@param[in] Event Operation event as update open CV, start CB, and nalu table.
@param[in] pubStr Device Chip info strings.
@param[in] pParm The parameters to be updated info.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_UVC_CFG_OP Event, MMP_UBYTE *pubStr, void *pParm)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    return MMPF_USBH_UpdDevCFG(Event, pubStr, pParm);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetDevTotalCount
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_HUVC_SetDevTotalCount(MMP_UBYTE ubCount)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetUVCDevTotalCount(ubCount);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_RegDevAddiCFG
//  Description :
//------------------------------------------------------------------------------
/**
@brief The function sets to register UVC device info configs.
@param[in] ulRegTyp Register info type.
@param[in] pubStr Device Chip info strings.
@param[in] ulParm0 The parameter 0 to be registered.
@param[in] ulParm1 The parameter 1 to be registered.
@param[in] ulParm2 The parameter 2 to be registered.
@param[in] ulParm3 The parameter 3 to be registered.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_HUVC_RegDevAddiCFG(MMP_ULONG ulRegTyp, MMP_UBYTE *pubStr, MMP_ULONG ulParm0, MMP_ULONG ulParm1, MMP_ULONG ulParm2, MMP_ULONG ulParm3)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_RegDevAddiCFG(ulRegTyp, pubStr, ulParm0,ulParm1,ulParm2,ulParm3);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetClassIfCmd
//  Description :
//------------------------------------------------------------------------------
/**
@brief Set UVC class IF command.
@param[in] bReq SETUP field bRequest.
@param[in] wVal SETUP field wValue.
@param[in] wInd SETUP field wIndex.
@param[in] wLen SETUP field wLength.
@param[in] UVCDataBuf received data.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_HUVC_SetClassIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_UBYTE *UVCDataBuf)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetClassIfCmd(bReq, wVal, wInd, wLen, UVCDataBuf);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_GetClassIfCmd
//  Description :
//------------------------------------------------------------------------------
/**
@brief Get UVC class IF command.
@param[in] bReq SETUP field bRequest.
@param[in] wVal SETUP field wValue.
@param[in] wInd SETUP field wIndex.
@param[in] wLen SETUP field wLength.
@param[in] UVCDataLength exact received data length.
@param[in] UVCDataBuf received data.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_HUVC_GetClassIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_ULONG *UVCDataLength, MMP_UBYTE *UVCDataBuf)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_GetClassIfCmd(bReq, wVal, wInd, wLen, UVCDataLength, UVCDataBuf);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_SetStdIfCmd
//  Description :
//------------------------------------------------------------------------------
/**
@brief Set UVC standard IF command.
@param[in] bReq SETUP field bRequest.
@param[in] wVal SETUP field wValue.
@param[in] wInd SETUP field wIndex.
@param[in] wLen SETUP field wLength.
@param[in] UVCDataBuf received data.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_HUVC_SetStdIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_UBYTE *UVCDataBuf)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_SetStdIfCmd(bReq, wVal, wInd, wLen, UVCDataBuf);
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_HUVC_GetStdDevCmd
//  Description :
//------------------------------------------------------------------------------
/**
@brief Get UVC standard DEV command.
@param[in] bReq SETUP field bRequest.
@param[in] wVal SETUP field wValue.
@param[in] wInd SETUP field wIndex.
@param[in] wLen SETUP field wLength.
@param[in] UVCDataLength exact received data length.
@param[in] UVCDataBuf received data.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_HUVC_GetStdDevCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_ULONG *UVCDataLength, MMP_UBYTE *UVCDataBuf)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (SUPPORT_USB_HOST_FUNC)
    eRetErr = MMPF_USBH_GetStdDevCmd(bReq, wVal, wInd, wLen, UVCDataLength, UVCDataBuf);
    #endif

    return eRetErr;
}
#endif
