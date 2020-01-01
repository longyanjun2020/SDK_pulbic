//------------------------------------------------------------------------------
//
//  File        : snr_cfg.c
//  Description : Source file of Sensor configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "snr_cfg.h"
#include "mmp_vidrec_inc.h"
#include "mmpf_sensor.h"
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/*
 * Configure of AIT Cam Stream Type
 */
AIT_REAR_CAM_STRM_TYPE  gsAitCamStreamType = AIT_REAR_CAM_STRM_MJPEG_H264;

/*
 * Configure of Primary Cam
 */
//PRM_CAM_ID sPrmCam = PRM_CAM_NONE;
PRM_CAM_ID sPrmCam = PRM_CAM_BAYER_SENSOR;
//PRM_CAM_ID sPrmCam = PRM_CAM_YUV_SENSOR;
//PRM_CAM_ID sPrmCam = PRM_CAM_ANA_DECODER;

/*
 * Configure of Secondary Cam
 */
//SCD_CAM_ID sScdCam = SCD_CAM_NONE;
//SCD_CAM_ID sScdCam = SCD_CAM_BAYER_SENSOR;
SCD_CAM_ID sScdCam = SCD_CAM_ANA_DECODER;
//SCD_CAM_ID sScdCam = SCD_CAM_YUV_SENSOR;

/*
 * Configure of Third Cam
 */
TRD_CAM_ID sTrdCam = TRD_CAM_NONE;
//TRD_CAM_ID sTrdCam = TRD_CAM_BAYER_SENSOR;
//TRD_CAM_ID sTrdCam = TRD_CAM_ANA_DECODER;
//TRD_CAM_ID sTrdCam = TRD_CAM_YUV_SENSOR;

/*
 * Configure of USB Cam
 */
USB_CAM_ID sUSBCam = USB_CAM_NONE;
//USB_CAM_ID sUSBCam = USB_CAM_AIT;
//USB_CAM_ID sUSBCam = USB_CAM_SONIX_MJPEG;
//USB_CAM_ID sUSBCam = USB_CAM_SONIX_MJPEG2H264;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMP_IsPrmCamExist
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMP_IsPrmCamExist(void)
{
    return ((sPrmCam == PRM_CAM_ANA_DECODER) ||\
            (sPrmCam == PRM_CAM_BAYER_SENSOR) ||\
            (sPrmCam == PRM_CAM_YUV_SENSOR));
}

//------------------------------------------------------------------------------
//  Function    : MMP_IsScdCamExist
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMP_IsScdCamExist(void)
{
    return ((sScdCam == SCD_CAM_ANA_DECODER) ||\
            (sScdCam == SCD_CAM_BAYER_SENSOR) ||\
            (sScdCam == SCD_CAM_YUV_SENSOR));
}

//------------------------------------------------------------------------------
//  Function    : MMP_GetScdCamType
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMP_GetScdCamType(void)
{
    return sScdCam;
}

//------------------------------------------------------------------------------
//  Function    : MMP_IsTrdCamExist
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMP_IsTrdCamExist(void)
{
    return ((sTrdCam == TRD_CAM_ANA_DECODER) ||\
            (sTrdCam == TRD_CAM_BAYER_SENSOR) ||\
            (sTrdCam == TRD_CAM_YUV_SENSOR));
}

#if 0
void _____USBCam_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMP_GetUSBCamType
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMP_GetUSBCamType(void)
{
    return sUSBCam;
}

//------------------------------------------------------------------------------
//  Function    : MMP_SetScdCamType
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMP_SetUSBCamType(USB_CAM_ID eCamID)
{
    if (eCamID >= USB_CAM_NONE &&
        eCamID <= USB_CAM_SONIX_MJPEG2H264)
    {
        sUSBCam = eCamID;
        return MMP_TRUE;
    }

    return MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : MMP_IsUSBCamExist
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMP_IsUSBCamExist(void)
{
    return ((sUSBCam == USB_CAM_AIT) ||\
            (sUSBCam == USB_CAM_SONIX_MJPEG) ||\
            (sUSBCam == USB_CAM_SONIX_MJPEG2H264));
}

//------------------------------------------------------------------------------
//  Function    : MMP_GetAitCamStreamType
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMP_GetAitCamStreamType(void)
{
    return gsAitCamStreamType;
}

//------------------------------------------------------------------------------
//  Function    : MMP_GetANACamType
//  Description :
//------------------------------------------------------------------------------
ANA_CAM_TYPE MMP_GetANACamType(void)
{
    return MMPF_GetANACamType();
}

//------------------------------------------------------------------------------
//  Function    : MMP_SetANACamType
//  Description :
//------------------------------------------------------------------------------
void MMP_SetANACamType(ANA_CAM_TYPE type)
{
    MMPF_SetANACamType(type);
}

//------------------------------------------------------------------------------
//  Function    : MMP_SetRawStoreNum
//  Description :
//------------------------------------------------------------------------------
void MMP_SetRawStoreNum(MMP_BYTE bNum)
{
    MMPF_SetRawStoreNum(bNum);
}

//------------------------------------------------------------------------------
//  Function    : MMP_GetRawStoreNum
//  Description :
//------------------------------------------------------------------------------
MMP_BYTE MMP_GetRawStoreNum(void)
{
    return MMPF_GetRawStoreNum();
}


