//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "usb_cfg.h"

#include "lib_retina.h"
#include "mmp_mjpeg_inc.h"
#include "mmps_dsc.h"
#include "mmpd_dsc.h"
#include "mmpf_ringbuf.h"
#include "mmpf_jpeg_enc_rc.h"

#include "component_scl.h"
#include "component_dip.h"
#include "component_jpe.h"
#include "component_raws.h"
#include "component_cfg.h"
#include "pCam_api.h"

#if (SUPPORT_MJPEG_WIFI_STREAM)

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MMPS_MJPEG_ENC_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMPS_MJPEG_ENC_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

static MMP_MJPEG_OBJ m_sMjpegStreamObj[MAX_MJPEG_STREAM_NUM];
static MMP_ULONG     m_ulNearRingThd = 0;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____MJPEG_Streaming_Function_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_MJPEG_IsValidObj
//  Description :
//------------------------------------------------------------------------------
static MMP_BOOL MMPS_MJPEG_IsValidObj(MMP_MJPEG_OBJ_PTR pHandle)
{
    if (pHandle == NULL) {
        return MMP_FALSE;
    }
    return MMP_TRUE;
}

static MMP_ULONG MMPS_MJPEG_GetThreshold(MMP_ULONG ulFrameSize)
{
    return m_ulNearRingThd;
}

static MMP_ULONG MMPS_MJPEG_SetThreshold(MMP_ULONG ulNearRingThd)
{
    m_ulNearRingThd = ulNearRingThd;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_MJPEG_STREAM_ConfigPipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_MJPEG_STREAM_ConfigPipe(MMP_MJPEG_OBJ_PTR pstStreamObj,
                                     MMP_USHORT usStreamW, MMP_USHORT usStreamH,
                                     MMP_USHORT *pusAlignStreamW, MMP_USHORT *pusAlignStreamH)
{
    SCL_COMP_RECT   stSclRect;
    MMP_ULONG       ulScaleInW = 0, ulScaleInH = 0;
    MMP_ULONG       ulAlignOutW = 0, ulAlignOutH = 0;
    MMP_UBYTE       ubDipBufCnt = DIP_COMP_PREVW_BUF_COUNT;
    MMP_UBYTE       ubDIPCompSel = DIP_S_COMP_VR_FCAM_STREAMING;
    MMP_UBYTE       ubInColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    MMP_UBYTE       ubOutColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    MMP_ERR         eRetErr = MMP_ERR_NONE;

    if (MMP_FALSE == MMPS_MJPEG_IsValidObj(pstStreamObj)) {
        return MMP_MJPGD_ERR_PARAMETER;
    }

    if (pstStreamObj->usEncID == MMP_MJPEG_STREAM_FCAM_VIDEO &&
        pstStreamObj->ubCamSel == PRM_SENSOR) {

        if (pstStreamObj->eUiModeID == MMP_STREAM_UI_MODE_WIFI_DSC) {
            ubDIPCompSel = DIP_S_COMP_DSC_FCAM_STREAMING;
            Component_SCL1_GetParam(&Component_SCL1[SCL1_COMP_PRM_CAM], SCL_COMP_PARAM_OUT_RECT, &stSclRect);
        }
        else if (pstStreamObj->eUiModeID == MMP_STREAM_UI_MODE_WIFI_VR) {
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
        *pusAlignStreamW = ulAlignOutW;
        *pusAlignStreamH = ulAlignOutH;

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
    else if (pstStreamObj->usEncID == MMP_MJPEG_STREAM_RCAM_VIDEO) {

        if (pstStreamObj->eUiModeID == MMP_STREAM_UI_MODE_WIFI_DSC) {
            ubDIPCompSel = DIP_S_COMP_DSC_RCAM_STREAMING;
        }
        else if (pstStreamObj->eUiModeID == MMP_STREAM_UI_MODE_WIFI_VR) {
            ubDIPCompSel = DIP_S_COMP_VR_RCAM_STREAMING;
        }

        // Update DIP_S component
        ulAlignOutW = usStreamW;
        ulAlignOutH = usStreamH;
        ulAlignOutW = ALIGN_X(ulAlignOutW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulAlignOutH = ALIGN_X(ulAlignOutH, DIP_S_COMP_WIDTH_ALIGN_BASE);
        *pusAlignStreamW = ulAlignOutW;
        *pusAlignStreamH = ulAlignOutH;

        if (pstStreamObj->ubCamSel == SCD_SENSOR) {
            Component_RawS_GetParam(&Component_RawS[RAWS_COMP_IDX], RAWS_COMP_PARAM_WIDTH, &ulScaleInW);
            Component_RawS_GetParam(&Component_RawS[RAWS_COMP_IDX], RAWS_COMP_PARAM_HEIGHT, &ulScaleInH);
        }
        else if (pstStreamObj->ubCamSel == USBH_SENSOR) {
            ulScaleInW = gUsbh_UvcDevInfo.wPrevwMaxWidth;
            ulScaleInH = gUsbh_UvcDevInfo.wPrevwMaxHeight;
        }

        ubInColor  = DIP_COMP_COLOR_FMT_YUV422_YUYV;
        ubOutColor = DIP_COMP_COLOR_FMT_YUV420_UV;
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
//  Function    : MMPS_MJPEG_OpenStream
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_MJPEG_OpenStream(MMP_UBYTE ubCamSel, MMP_USHORT usEncID, MMP_USHORT usMode, MMP_MJPEG_OBJ_PTR *ppHandle)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if ((usEncID != MMP_MJPEG_STREAM_FCAM_VIDEO) &&
        (usEncID != MMP_MJPEG_STREAM_RCAM_VIDEO)) {
        MMPS_MJPEG_ENC_DBG_ERR(1, "MJPEG EncID [%d] Wrong\r\n", usEncID);
        return MMP_MJPGD_ERR_PARAMETER;
    }

    if (usMode >= MMP_STREAM_UI_MODE_ID_NUM) {
        MMPS_MJPEG_ENC_DBG_ERR(1, "MJPEG ModeID [%d] Wrong\r\n", usMode);
        return MMP_MJPGD_ERR_PARAMETER;
    }

    *ppHandle = NULL;

    eRetErr = MMPD_Streaming_Init(usEncID);

    *ppHandle = &m_sMjpegStreamObj[usEncID];

    m_sMjpegStreamObj[usEncID].usEncID   = usEncID;
    m_sMjpegStreamObj[usEncID].ubCamSel  = ubCamSel;
    m_sMjpegStreamObj[usEncID].eUiModeID = usMode;

    eRetErr = MMPD_Streaming_SetModeID(usEncID, usMode);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_MJPEG_StartStream
//  Description : TBD
//------------------------------------------------------------------------------
MMP_ERR MMPS_MJPEG_StartStream(MMP_UBYTE           ubMode,
                               MMP_MJPEG_OBJ_PTR   pHandle,
                               MMP_MJPEG_ENC_INFO  *pMjpegInfo,
                               MMP_MJPEG_RATE_CTL  *pRateCtrl)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubCompUseType = JPE_COMP_PRM_MJPEG;
    MMP_USHORT  usMjpegEncId = MMP_MJPEG_STREAM_FCAM_VIDEO;
    MMP_UBYTE   ubRcIdx = MMP_JPGENC_RC_ID_PRM_MJPEG_STREAM;
    MMPF_STREAM_RING_ID eRingId = VIDEO1_RING_STREAM;
    MMP_ULONG   ulNearRingThd = 0;

    if (pHandle == NULL) {
        MMPS_MJPEG_ENC_DBG_ERR(1, "MJPEG Handle is NULL\r\n");
        return MMP_MJPGD_ERR_PARAMETER;
    }

    if (pHandle->ubCamSel == PRM_SENSOR) {
        ubCompUseType = JPE_COMP_PRM_MJPEG;
        usMjpegEncId = MMP_MJPEG_STREAM_FCAM_VIDEO;
        ubRcIdx = MMP_JPGENC_RC_ID_PRM_MJPEG_STREAM;
        eRingId = VIDEO1_RING_STREAM;
    }
    else if (pHandle->ubCamSel == SCD_SENSOR ||
             pHandle->ubCamSel == USBH_SENSOR) {
        ubCompUseType = JPE_COMP_SCD_MJPEG;
        usMjpegEncId = MMP_MJPEG_STREAM_RCAM_VIDEO;
        ubRcIdx = MMP_JPGENC_RC_ID_SCD_MJPEG_STREAM;
        eRingId = VIDEO2_RING_STREAM;
    }

    /* Set JPEG Parameters */
    MMPS_DSC_SetJpeUIMode(ubCompUseType, JPE_COMP_UI_MODE_VR); // TBD:DSC Mode

    MMPS_DSC_SetShotMode(ubCompUseType, JPE_COMP_MJPEG_MODE);
    MMPS_DSC_SetMaxShotNum(ubCompUseType, 0xFFFFFFFF);

    MMPS_DSC_SetJpegEncFmt(ubCompUseType, JPE_COMP_FMT_NV12);
    MMPS_DSC_SetJpegEncResol(ubCompUseType, pMjpegInfo->usEncWidth, pMjpegInfo->usEncHeight);

    MMPS_DSC_SetCaptureJpegQuality( ubRcIdx,
                                    pMjpegInfo->bTargetCtl,
                                    pMjpegInfo->bLimitCtl,
                                    pMjpegInfo->bTargetSize,
                                    pMjpegInfo->bLimitSize,
                                    pMjpegInfo->bMaxTrialCnt,
                                    pMjpegInfo->Quality);

    /* Set MJPEG encode done mode */
    MMPS_DSC_SetMjpegEncDoneMode(ubMode);

    /* Allocate buffer */
    MMPS_DSC_CalculateJpeOBufAttr(ubCompUseType, MMP_FALSE);

    /* Set streaming attribute */
    if (pRateCtrl != NULL) {
        eRetErr = MMPD_MJPEG_SetFPS(usMjpegEncId, pRateCtrl->FPSx10, 10);
    }
    else {
        eRetErr = MMPD_MJPEG_SetFPS(usMjpegEncId, 300, 10);
    }

    /* Open Script */
    if (ubMode == MMP_STREAM_UI_MODE_WIFI_VR) {
        Component_JPE_GetParam(&Component_JPE[ubCompUseType], JPE_COMP_PARAM_BUF_RING_THD, (void*)&ulNearRingThd);
        MMPS_MJPEG_SetThreshold(ulNearRingThd);

        if (pHandle->ubCamSel == PRM_SENSOR) {
            OpenScript(COMPO_SCRIPT_PCAM_PRM_MJPEG);
            OpenPortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
        }
        else if (pHandle->ubCamSel == SCD_SENSOR) {
            OpenScript(COMPO_SCRIPT_VR_SCD_ANADEC_MJPEG_WIFI);
            OpenPortScript(PORT_SCRIPT_VR_SCD_ANADEC_WIFI);
        }
        else if (pHandle->ubCamSel == USBH_SENSOR) {
            OpenScript(COMPO_SCRIPT_VR_USBH_MJPEG_WIFI);
            OpenPortScript(PORT_SCRIPT_VR_USBH_WIFI);
        }

        eRetErr = MMPD_Streaming_SetCompBuf(eRingId, ubMode, 0, 0, MMP_STREAM_JPEG, MMPS_MJPEG_GetThreshold);
        eRetErr = MMPD_Streaming_Enable(eRingId, MMP_TRUE, MMP_FALSE);
    }
    else if (ubMode == MMP_STREAM_UI_MODE_UVC_VR) {
        if (pHandle->ubCamSel == PRM_SENSOR) {

            if (pcam_usb_get_2nd_vid_fmt() == PCAM_USB_VIDEO_FORMAT_MJPEG) {
                
                OpenScript(COMPO_SCRIPT_PCAM_PRM_MJPEG_2ND);
                OpenPortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC_2ND);
            
            }
            else {
                OpenScript(COMPO_SCRIPT_PCAM_PRM_MJPEG);

                if (MMP_TRUE == pcam_usb_get_mix_mode()) {
                    OpenPortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
                }
                else {
                    OpenPortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
                }
            }
        }
        else {
            //OpenScript(COMPO_SCRIPT_PCAM_SCD_MJPEG);
            //OpenPortScript(PORT_SCRIPT_MIX_PCAM_SCD_SRC);
        }
    }

    if (eRetErr != MMP_ERR_NONE) {
        return MMP_WIFI_ERR_PARAMETER;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_MJPEG_StopStream
//  Description : TBD
//------------------------------------------------------------------------------
MMP_ERR MMPS_MJPEG_StopStream(MMP_MJPEG_OBJ_PTR pHandle)
{
    MMP_BOOL    bStreamEnable = MMP_FALSE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (MMP_FALSE == MMPS_MJPEG_IsValidObj(pHandle)) {
        return MMP_MJPGD_ERR_PARAMETER;
    }

    if ((MMP_STREAM_UI_MODE_WIFI_VR == pHandle->eUiModeID) ||
        (MMP_STREAM_UI_MODE_WIFI_DSC == pHandle->eUiModeID)) {

        if (pHandle->usEncID == MMP_MJPEG_STREAM_FCAM_VIDEO) {
            bStreamEnable = MMPF_StreamRing_IsEnabled(VIDEO1_RING_STREAM);
        }
        else if (pHandle->usEncID == MMP_MJPEG_STREAM_RCAM_VIDEO) {
            bStreamEnable = MMPF_StreamRing_IsEnabled(VIDEO2_RING_STREAM);
        }

        eRetErr = MMPD_Streaming_Enable(pHandle->usEncID, MMP_FALSE, MMP_FALSE);

        eRetErr = MMPD_MJPEG_CheckEncodeDone(pHandle->usEncID);

        if (pHandle->ubCamSel == PRM_SENSOR) {
            //ClosePortScript(PORT_SCRIPT_VR_PRM_MJPEG_WIFI);
            //CloseScript(COMPO_SCRIPT_VR_PRM_MJPEG_WIFI);
            ClosePortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
            CloseScript(COMPO_SCRIPT_PCAM_PRM_MJPEG);
        }
        else if (pHandle->ubCamSel == SCD_SENSOR){
            ClosePortScript(PORT_SCRIPT_VR_SCD_ANADEC_WIFI);
            CloseScript(COMPO_SCRIPT_VR_SCD_ANADEC_MJPEG_WIFI);
        }
        else if (pHandle->ubCamSel == USBH_SENSOR){
            ClosePortScript(PORT_SCRIPT_VR_USBH_WIFI);
            CloseScript(COMPO_SCRIPT_VR_USBH_MJPEG_WIFI);
        }

        if (eRetErr != MMP_ERR_NONE) {
            MMPS_MJPEG_ENC_DBG_ERR(1, "MJPEG_StopStream Fail-1\r\n");
            return eRetErr;
        }
    }
    #if (SUPPORT_UVC_FUNC)
    else if ((MMP_STREAM_UI_MODE_UVC_VR == pHandle->eUiModeID) ||
             (MMP_STREAM_UI_MODE_UVC_DSC == pHandle->eUiModeID)) {

        eRetErr = MMPD_MJPEG_CheckEncodeDone(pHandle->usEncID);

        if (pcam_usb_get_2nd_vid_fmt() == PCAM_USB_VIDEO_FORMAT_MJPEG) {
            
            ClosePortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC_2ND);
            CloseScript(COMPO_SCRIPT_PCAM_PRM_MJPEG_2ND);
        
        }
        else {
            if (MMP_TRUE == pcam_usb_get_mix_mode()) {
                ClosePortScript(PORT_SCRIPT_MIX_PCAM_PRM_SRC);
            }
            else {
                ClosePortScript(PORT_SCRIPT_PURE_PCAM_PRM_SRC);
            }

            CloseScript(COMPO_SCRIPT_PCAM_PRM_MJPEG);
        }

        if (eRetErr != MMP_ERR_NONE) {
            MMPS_MJPEG_ENC_DBG_ERR(1, "MJPEG_StopStream Fail-2\r\n");
            return eRetErr;
        }
    }
    #endif
    else {
        return MMP_MJPGD_ERR_PARAMETER;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_MJPEG_CloseStream
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_MJPEG_CloseStream(MMP_MJPEG_OBJ_PTR* ppHandle)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    //eRetErr = MMPS_MJPEG_StopStream(*ppHandle);

    if (eRetErr == MMP_ERR_NONE) {
        (*ppHandle)->usEncID    = MAX_MJPEG_STREAM_NUM;
        (*ppHandle)->eUiModeID  = MMP_STREAM_UI_MODE_ID_NUM;
        (*ppHandle)             = NULL;
    }
    return eRetErr;
}

#endif //SUPPORT_MJPEG_WIFI_STREAM
