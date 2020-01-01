
//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmpd_fctl.h"
#include "mmph_hif.h"
#include "component_dip.h"
#include "component_scl.h"
#include "snr_cfg.h"

/** @addtogroup MMPD_FCTL
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_Fctl_EnablePreview
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR MMPD_Fctl_EnablePreview(MMP_UBYTE ubSnrSel, MMP_BOOL bEnable, MMP_BOOL bCheckFrameEnd)
{
    return MMPF_Sensor_EnablePreview(ubSnrSel, bEnable);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Fctl_SetDIPCompAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Fctl_SetDIPCompAttr(MMP_UBYTE ubDipType,
                                 MMP_UBYTE ubDipUseIdx,
                                 MMP_ULONG ulInX,   MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,
                                 MMP_ULONG ulCropX, MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH,
                                 MMP_ULONG ulOutX,  MMP_ULONG ulOutY,   MMP_ULONG ulOutW,   MMP_ULONG ulOutH,
                                 MMP_UBYTE ubInColor, MMP_UBYTE ubOutColor,
                                 MMP_UBYTE ubMirrorType,
                                 MMP_USHORT usLineBias,
                                 MMP_UBYTE ubBufCnt)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    DIP_COMP_RECT       stDipRect;
    int                 iParamIdxInRes, iParamIdxCropRes, iPrarmIdxOutRes, iParamIdxInFmt, iParamIdxOutFmt;
    int                 iParamIdxBufCnt, iParamIdxBufSize;
    int                 iParamIdxLineBias, iParamIdxBufferBias;
    MMP_ULONG           ulBufBias = 0;
    MMP_ULONG           ulBufSize = 0;
    DIP_COMP_COLOR_FMT  eDipInFmt, eDipOutFmt;
    void                *pvHandler = NULL;

    switch (ubDipType) {
    case DIP_COMP_TYPE_ID_ROT:
        iParamIdxInRes      = DIP_COMP_PARAM_ROT_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_ROT_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_ROT_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_ROT_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_ROT_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_ROT_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_ROT_BUF_SIZE;
        pvHandler           = &Component_DIP_Rotate[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_SCL:
        iParamIdxInRes      = DIP_COMP_PARAM_SCL_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_SCL_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_SCL_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_SCL_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_SCL_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_SCL_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_SCL_BUF_SIZE;
        iParamIdxLineBias   = DIP_COMP_PARAM_SCL_LINE_BIAS;
        iParamIdxBufferBias = DIP_COMP_PARAM_SCL_BUF_BIAS;
        pvHandler           = &Component_DIP_Scale[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_OSDB:
        iParamIdxInRes      = DIP_COMP_PARAM_OSDB_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_OSDB_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_OSDB_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_OSDB_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_OSDB_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_OSDB_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_OSDB_BUF_SIZE;
        pvHandler           = &Component_DIP_OSDB[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_CC:
        iParamIdxInRes      = DIP_COMP_PARAM_CC_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_CC_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_CC_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_CC_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_CC_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_CC_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_CC_BUF_SIZE;
        pvHandler           = &Component_DIP_ColorConvert[ubDipUseIdx];
        break;
    default:
        MMP_DBG_ERR(1, "UnSupport DIP Comp Type\r\n");
        return MMP_ERR_NONE;
        break;
    }

    stDipRect.ulX = ulInX;
    stDipRect.ulY = ulInY;
    stDipRect.ulW = ulInW;
    stDipRect.ulH = ulInH;
    stDipRect.ulLineOffset = ulInW;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxInRes, (void*)&stDipRect);

    stDipRect.ulX = ulCropX;
    stDipRect.ulY = ulCropY;
    stDipRect.ulW = ulCropW;
    stDipRect.ulH = ulCropH;
    stDipRect.ulLineOffset = ulInW;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxCropRes, (void*)&stDipRect);

    stDipRect.ulX = ulOutX;
    stDipRect.ulY = ulOutY;
    stDipRect.ulW = ulOutW;
    stDipRect.ulH = ulOutH;
    stDipRect.ulLineOffset = ulOutW;
    eRetErr |= Component_DIP_SetParam(pvHandler, iPrarmIdxOutRes, (void*)&stDipRect);

    eDipInFmt = ubInColor;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxInFmt, (void*)&eDipInFmt);

    eDipOutFmt = ubOutColor;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxOutFmt, (void*)&eDipOutFmt);

    if (ubDipType == DIP_COMP_TYPE_ID_SCL) {
        eRetErr |= Component_DIP_SetParam(pvHandler, DIP_COMP_PARAM_SCL_MIRROR_EN, (void*)&ubMirrorType);
    }

    ulBufSize = (eDipOutFmt <= DIP_COMP_COLOR_FMT_YUV420_T16X32_VU) ?
                (DIP_COMP_BUF_SIZE_YUV420(ulOutW, (ulOutH + usLineBias))) : (DIP_COMP_BUF_SIZE_YUV422(ulOutW, (ulOutH + usLineBias)));

    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxBufCnt, (void*)&ubBufCnt);
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxBufSize, (void*)&ulBufSize);

    if (ubDipType == DIP_COMP_TYPE_ID_SCL) {
        eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxLineBias, (void*)&usLineBias);
        ulBufBias = ulOutW * usLineBias;
        eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxBufferBias, (void*)&ulBufBias);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Fctl_SetDIPCompAttr_LineOffset
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Fctl_SetDIPCompAttr_LineOffset(MMP_UBYTE ubDipType,
                              MMP_UBYTE ubDipUseIdx, MMP_UBYTE ubDipOutCompIdx,
                              MMP_ULONG ulInX,   MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,  MMP_ULONG ulInLineOffset,
                              MMP_ULONG ulCropX, MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH,
                              MMP_ULONG ulOutX,  MMP_ULONG ulOutY,   MMP_ULONG ulOutW,   MMP_ULONG ulOutH, MMP_ULONG ulOutLineOffset,
                              MMP_UBYTE ubInColor, MMP_UBYTE ubOutColor,
                              MMP_UBYTE ubMirrorType,
                              MMP_USHORT usLineBias,
                              MMP_UBYTE ubBufCnt)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    DIP_COMP_RECT       stDipRect;
    int                 iParamIdxInRes, iParamIdxCropRes, iPrarmIdxOutRes, iParamIdxInFmt, iParamIdxOutFmt;
    int                 iParamIdxBufCnt, iParamIdxBufSize;
#if (SUPPORT_MFE_SHAREBUFFER)
    int                 iParamIdxLineBias, iParamIdxBufferBias;
    MMP_ULONG           ulBufBias = 0;
#endif
    MMP_ULONG           ulBufSize = 0;
    DIP_COMP_COLOR_FMT  eDipInFmt, eDipOutFmt;
    void                *pvHandler = NULL;

    switch (ubDipType) {
    case DIP_COMP_TYPE_ID_ROT:
        iParamIdxInRes      = DIP_COMP_PARAM_ROT_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_ROT_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_ROT_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_ROT_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_ROT_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_ROT_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_ROT_BUF_SIZE;
        pvHandler           = &Component_DIP_Rotate[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_SCL:
        iParamIdxInRes      = DIP_COMP_PARAM_SCL_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_SCL_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_SCL_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_SCL_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_SCL_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_SCL_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_SCL_BUF_SIZE;
#if (SUPPORT_MFE_SHAREBUFFER)
        iParamIdxLineBias   = DIP_COMP_PARAM_SCL_LINE_BIAS;
        iParamIdxBufferBias = DIP_COMP_PARAM_SCL_BUF_BIAS;
#endif
        pvHandler           = &Component_DIP_Scale[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_OSDB:
        iParamIdxInRes      = DIP_COMP_PARAM_OSDB_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_OSDB_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_OSDB_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_OSDB_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_OSDB_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_OSDB_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_OSDB_BUF_SIZE;
        pvHandler           = &Component_DIP_OSDB[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_CC:
        iParamIdxInRes      = DIP_COMP_PARAM_CC_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_CC_CROP_RES;
        iPrarmIdxOutRes     = DIP_COMP_PARAM_CC_OUT_RES;
        iParamIdxInFmt      = DIP_COMP_PARAM_CC_IN_FMT;
        iParamIdxOutFmt     = DIP_COMP_PARAM_CC_OUT_FMT;
        iParamIdxBufCnt     = DIP_COMP_PARAM_CC_BUF_COUNT;
        iParamIdxBufSize    = DIP_COMP_PARAM_CC_BUF_SIZE;
        pvHandler           = &Component_DIP_ColorConvert[ubDipUseIdx];
        break;
    default:
        MMP_DBG_ERR(1, "UnSupport DIP Comp Type\r\n");
        return MMP_ERR_NONE;
        break;
    }

    stDipRect.ulX = ulInX;
    stDipRect.ulY = ulInY;
    stDipRect.ulW = ulInW;
    stDipRect.ulH = ulInH;
    stDipRect.ulLineOffset = ulInLineOffset;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxInRes, (void*)&stDipRect);

    stDipRect.ulX = ulCropX;
    stDipRect.ulY = ulCropY;
    stDipRect.ulW = ulCropW;
    stDipRect.ulH = ulCropH;
    stDipRect.ulLineOffset = ulInLineOffset;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxCropRes, (void*)&stDipRect);

    stDipRect.ulX = ulOutX;
    stDipRect.ulY = ulOutY;
    stDipRect.ulW = ulOutW;
    stDipRect.ulH = ulOutH;
    stDipRect.ulLineOffset = ulOutLineOffset;
    eRetErr |= Component_DIP_SetParam(pvHandler, iPrarmIdxOutRes, (void*)&stDipRect);

    eDipInFmt = ubInColor;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxInFmt, (void*)&eDipInFmt);

    eDipOutFmt = ubOutColor;
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxOutFmt, (void*)&eDipOutFmt);

    if (ubDipType == DIP_COMP_TYPE_ID_SCL) {
        eRetErr |= Component_DIP_SetParam(pvHandler, DIP_COMP_PARAM_SCL_MIRROR_EN, (void*)&ubMirrorType);
        eRetErr |= Component_DIP_SetParam(pvHandler, DIP_COMP_PARAM_SCL_OUT_COMP_IDX, (void*)&ubDipOutCompIdx);
    }

#if (SUPPORT_MFE_SHAREBUFFER)
    ulBufSize = (eDipOutFmt <= DIP_COMP_COLOR_FMT_YUV420_T16X32_VU) ?
             (DIP_COMP_BUF_SIZE_YUV420(ulOutW, (ulOutH + usLineBias))) : (DIP_COMP_BUF_SIZE_YUV422(ulOutW, (ulOutH + usLineBias)));
#else
    ulBufSize = (eDipOutFmt <= DIP_COMP_COLOR_FMT_YUV420_T16X32_VU) ?
             (DIP_COMP_BUF_SIZE_YUV420(ulOutW, ulOutH)) : (DIP_COMP_BUF_SIZE_YUV422(ulOutW, ulOutH));
#endif

    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxBufCnt, (void*)&ubBufCnt);
    eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxBufSize, (void*)&ulBufSize);

#if (SUPPORT_MFE_SHAREBUFFER)
    if (ubDipType == DIP_COMP_TYPE_ID_SCL) {
        eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxLineBias, (void*)&usLineBias);
        ulBufBias = ulOutW * usLineBias;
        eRetErr |= Component_DIP_SetParam(pvHandler, iParamIdxBufferBias, (void*)&ulBufBias);
    }
#endif

    return eRetErr;

}

//------------------------------------------------------------------------------
//  Function    : MMPD_Fctl_SetDIPCompCropWin
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Fctl_SetDIPCompCropWin( MMP_UBYTE ubDipType,
                                     MMP_UBYTE ubDipUseIdx,
                                     MMP_ULONG ulCropX, MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH)
{
    MMP_ERR         eRetErr = MMP_ERR_NONE;
    DIP_COMP_RECT   stDipRect;
    int             iParamIdxCropRes;
    void            *pvHandler = NULL;

    switch (ubDipType) {
    case DIP_COMP_TYPE_ID_ROT:
        iParamIdxCropRes    = DIP_COMP_PARAM_ROT_CROP_RES;
        pvHandler           = &Component_DIP_Rotate[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_SCL:
        iParamIdxCropRes    = DIP_COMP_PARAM_SCL_CROP_RES;
        pvHandler           = &Component_DIP_Scale[ubDipUseIdx];
        break;
    default:
        MMP_DBG_ERR(1, "UnSupport DIP Comp Type\r\n");
        return MMP_ERR_NONE;
        break;
    }

    stDipRect.ulX = ulCropX;
    stDipRect.ulY = ulCropY;
    stDipRect.ulW = ulCropW;
    stDipRect.ulH = ulCropH;
    eRetErr = Component_DIP_SetParam(pvHandler, iParamIdxCropRes, (void*)&stDipRect);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Fctl_GetDIPCompWin
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Fctl_GetDIPCompWin( MMP_UBYTE ubDipType,
                                 MMP_UBYTE ubDipUseIdx,
                                 MMP_ULONG *pulInX,   MMP_ULONG *pulInY,   MMP_ULONG *pulInW,   MMP_ULONG *pulInH,
                                 MMP_ULONG *pulCropX, MMP_ULONG *pulCropY, MMP_ULONG *pulCropW, MMP_ULONG *pulCropH)
{
    MMP_ERR         eRetErr = MMP_ERR_NONE;
    DIP_COMP_RECT   stDipRect;
    int             iParamIdxCropRes, iParamIdxInRes;
    void            *pvHandler = NULL;

    switch (ubDipType) {
    case DIP_COMP_TYPE_ID_ROT:
        iParamIdxInRes      = DIP_COMP_PARAM_ROT_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_ROT_CROP_RES;
        pvHandler           = &Component_DIP_Rotate[ubDipUseIdx];
        break;
    case DIP_COMP_TYPE_ID_SCL:
        iParamIdxInRes      = DIP_COMP_PARAM_SCL_IN_RES;
        iParamIdxCropRes    = DIP_COMP_PARAM_SCL_CROP_RES;
        pvHandler           = &Component_DIP_Scale[ubDipUseIdx];
        break;
    default:
        MMP_DBG_ERR(1, "UnSupport DIP Comp Type\r\n");
        return MMP_ERR_NONE;
        break;
    }

    eRetErr = Component_DIP_GetParam(pvHandler, iParamIdxInRes, (void*)&stDipRect);
    if (pulInX) {
        *pulInX = stDipRect.ulX;
    }
    if (pulInY) {
        *pulInY = stDipRect.ulY;
    }
    if (pulInW) {
        *pulInW = stDipRect.ulW;
    }
    if (pulInH) {
        *pulInH = stDipRect.ulH;
    }

    eRetErr |= Component_DIP_GetParam(pvHandler, iParamIdxCropRes, (void*)&stDipRect);
    if (pulCropX) {
        *pulCropX = stDipRect.ulX;
    }
    if (pulCropY) {
        *pulCropY = stDipRect.ulY;
    }
    if (pulCropW) {
        *pulCropW = stDipRect.ulW;
    }
    if (pulCropH) {
        *pulCropH = stDipRect.ulH;
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Fctl_SetSCLCompAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Fctl_SetSCLCompAttr(MMP_UBYTE ubSclType,
                                 MMP_UBYTE ubSclUseIdx,
                                 MMP_ULONG ulInX,   MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,
                                 MMP_ULONG ulOutX,  MMP_ULONG ulOutY,   MMP_ULONG ulOutW,   MMP_ULONG ulOutH,
                                 MMP_UBYTE ubBufCnt)
{
    MMP_ERR         eRetErr = MMP_ERR_NONE;
    SCL_COMP_RECT   stSCLInRect, stSCLOutRect;
    MMP_ULONG       ulBufSize = 0;
    MMP_BOOL        bMCNR = 0;
    MMP_BOOL        bCIIR = 0;
    MMP_BOOL        bLDC = 0;
    void            *pvHandler = NULL;
    MMP_USHORT      usMFEOffset = 0;
    MMP_ULONG       ulBufBias = 0;

    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        if (ubSclType == SCL_COMP_TYPE_ID_SCL0)
            ubBufCnt = 4; // For Record
        else
            ubBufCnt = 4; // For Preview
    } 

    // Configure SCL0, Currently ISP Max Output is 1920x1080
    stSCLInRect.ulX = ulInX;
    stSCLInRect.ulY = ulInY;
    stSCLInRect.ulW = ulInW;
    stSCLInRect.ulH = ulInH;

    stSCLOutRect.ulX = ulOutX;
    stSCLOutRect.ulY = ulOutY;
    stSCLOutRect.ulW = ulOutW;
    stSCLOutRect.ulH = ulOutH;

    if (ubSclType != SCL_COMP_TYPE_ID_SCL0) {
        usMFEOffset = 0;
    }
    else {
        usMFEOffset = MFE_SHARE_BUF_LINE_BIAS;
    }
    ulBufSize = SCL_COMP_BUF_SIZE_YUV420(ulOutW, (ulOutH + usMFEOffset));
    ulBufSize = ulBufSize * ubBufCnt;
    ulBufBias = usMFEOffset * ulOutW;

    switch (ubSclType) {
    case SCL_COMP_TYPE_ID_SCL0:
        pvHandler = &Component_SCL0[ubSclUseIdx];
        eRetErr |= Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_LINE_BIAS, (void*)&usMFEOffset);
        eRetErr |= Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_BUF_BIAS, (void*)&ulBufBias);
        eRetErr |= Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_IN_RECT, (void*)&stSCLInRect);
        eRetErr |= Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_OUT_RECT, (void*)&stSCLOutRect);
        eRetErr |= Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        eRetErr |= Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_BUF_SIZE, (void*)&ulBufSize);

        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            if (ubSclUseIdx == 0) {
                bMCNR = 0;
                bCIIR = 0;
                bLDC = 0;
            }
            else {
                bMCNR = 0;//1;
                bCIIR = 0;//1;
                bLDC = 0;
            }
            Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_MCNR_EN, (void*)&bMCNR);
            Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_CIIR_EN, (void*)&bCIIR);
            Component_SCL0_SetParam(pvHandler, SCL_COMP_PARAM_LDC_EN, (void*)&bLDC);
            SCL_SetCMDQUse(0);
        }
        break;
    case SCL_COMP_TYPE_ID_SCL1:
        pvHandler = &Component_SCL1[ubSclUseIdx];
        eRetErr |= Component_SCL1_SetParam(pvHandler, SCL_COMP_PARAM_LINE_BIAS, (void*)&usMFEOffset);
        eRetErr |= Component_SCL1_SetParam(pvHandler, SCL_COMP_PARAM_BUF_BIAS, (void*)&ulBufBias);
        eRetErr |= Component_SCL1_SetParam(pvHandler, SCL_COMP_PARAM_IN_RECT, (void*)&stSCLInRect);
        eRetErr |= Component_SCL1_SetParam(pvHandler, SCL_COMP_PARAM_OUT_RECT, (void*)&stSCLOutRect);
        eRetErr |= Component_SCL1_SetParam(pvHandler, SCL_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
        eRetErr |= Component_SCL1_SetParam(pvHandler, SCL_COMP_PARAM_BUF_SIZE, (void*)&ulBufSize);

        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            SCL_SetCMDQUse(0);
        }
        break;
    default:
        eRetErr = MMP_HIF_ERR_PARAMETER;
        return eRetErr;
        break;
    }

    return eRetErr;
}

/// @}
