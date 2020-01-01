//------------------------------------------------------------------------------
//
//  File        : hdr_cfg.c
//  Description : Source file of HDR configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "hdr_cfg.h"
#include "snr_cfg.h"
#include "mmps_3gprecd.h"
#include "drv_ms_cus_sensor.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/*
 * Configure of HDR
 */
HDR_CFG gsHdrCfg[2] = 
{
    {
        CUS_SNR_HDR_DISABLE,    // ubVidHdrType
        CUS_SNR_HDR_DISABLE,    // ubDscHdrType
#if 0//(HDR_FULL_FOV_EN)
        HDR_MODE_SEQUENTIAL,    // ubMode
        MMP_FALSE,              // bRawGrabEnable
#else
        HDR_MODE_STAGGER,       // ubMode
        MMP_TRUE,               // bRawGrabEnable
#endif
        HDR_BITMODE_8BIT,       // ubRawStoreBitMode
        #if 1
        HDR_VC_STORE_2PLANE,    // ubVcStoreMethod
        #else
        HDR_VC_STORE_2ENGINE,   // ubVcStoreMethod
        #endif
        2                       // ubBktFrameNum
    },
    {
        CUS_SNR_HDR_DISABLE,    // ubVidHdrType
        CUS_SNR_HDR_DISABLE,    // ubDscHdrType
        HDR_MODE_STAGGER,       // ubMode
        MMP_TRUE,               // bRawGrabEnable
        HDR_BITMODE_8BIT,       // ubRawStoreBitMode
        HDR_VC_STORE_2PLANE,    // ubVcStoreMethod
        2                       // ubBktFrameNum
    }
};

void MMP_SetVidHDRType(CAM_TYPE camtype, MMP_BYTE ubVidHdrType)
{
    gsHdrCfg[camtype].ubVidHdrType = ubVidHdrType;

    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR) && ubVidHdrType == CUS_SNR_HDR_DCG) {
        gsHdrCfg[camtype].ubVidHdrType = CUS_SNR_HDR_DISABLE;
        gsHdrCfg[camtype].ubDscHdrType = CUS_SNR_HDR_DISABLE;
    }
}

void MMP_SetDscHDRType(CAM_TYPE camtype, MMP_BYTE ubDscHdrType)
{
    gsHdrCfg[camtype].ubDscHdrType = ubDscHdrType;
}

MMP_BYTE MMP_GetVidHDRType(CAM_TYPE camtype)
{
    return gsHdrCfg[camtype].ubVidHdrType;
}

MMP_BYTE MMP_GetDscHDRType(CAM_TYPE camtype)
{
    return gsHdrCfg[camtype].ubDscHdrType;
}
