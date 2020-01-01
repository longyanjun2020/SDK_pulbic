//------------------------------------------------------------------------------
//
//  File        : snr_cfg.h
//  Description : Header file of Sensor configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _SNR_CFG_H_
#define _SNR_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================
#include "lib_retina.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
    CAM_TYPE_PRM = 0,
    CAM_TYPE_SCD,
    CAM_TYPE_TRD,
    CAM_TYPE_USB,
    CAM_TYPE_NUM
} CAM_TYPE;

typedef enum {
    PRM_CAM_NONE = 0,
    PRM_CAM_BAYER_SENSOR,
    PRM_CAM_ANA_DECODER,
    PRM_CAM_YUV_SENSOR
} PRM_CAM_ID;

typedef enum {
    SCD_CAM_NONE = 0,
    SCD_CAM_BAYER_SENSOR,
    SCD_CAM_ANA_DECODER,
    SCD_CAM_YUV_SENSOR
} SCD_CAM_ID;

typedef enum {
    TRD_CAM_NONE = 0,
    TRD_CAM_BAYER_SENSOR,
    TRD_CAM_ANA_DECODER,
    TRD_CAM_YUV_SENSOR
} TRD_CAM_ID;

typedef enum {
    USB_CAM_NONE = 0,
    USB_CAM_AIT,
    USB_CAM_SONIX_MJPEG,
    USB_CAM_SONIX_MJPEG2H264
} USB_CAM_ID;

typedef enum {
    AIT_REAR_CAM_STRM_NV12_H264	= 0,    // Preview: NV12, Save file: H264
    AIT_REAR_CAM_STRM_MJPEG_H264,       // Preview: MJPEG, Save file: H264                     // USB Cam
    AIT_REAR_CAM_STRM_TYPE_NUM
} AIT_REAR_CAM_STRM_TYPE;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern AIT_REAR_CAM_STRM_TYPE   gsAitCamStreamType;

extern PRM_CAM_ID               sPrmCam;
extern SCD_CAM_ID               sScdCam;
extern TRD_CAM_ID               sTrdCam;
extern USB_CAM_ID               sUSBCam;

#define CAM_CHECK_PRM(p)        (sPrmCam == p)
#define CAM_CHECK_SCD(s)        (sScdCam == s)
#define CAM_CHECK_TRD(t)        (sTrdCam == t)
#define CAM_CHECK_USB(u)        (sUSBCam == u)

#define CAM_GET_PRM             (sPrmCam)
#define CAM_GET_SCD             (sScdCam)
#define CAM_GET_TRD             (sTrdCam)
#define CAM_GET_USB             (sUSBCam)

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_BOOL MMP_IsPrmCamExist(void);
MMP_BOOL MMP_IsScdCamExist(void);
MMP_BOOL MMP_IsTrdCamExist(void);
MMP_BOOL MMP_IsUSBCamExist(void);
MMP_UBYTE MMP_GetScdCamType(void);
MMP_UBYTE MMP_GetUSBCamType(void);
MMP_BOOL MMP_SetUSBCamType(USB_CAM_ID eCamID);
MMP_UBYTE MMP_GetAitCamStreamType(void);

//ANA_CAM_TYPE MMP_GetANACamType(void);
//void MMP_SetANACamType(ANA_CAM_TYPE type);
void MMP_SetRawStoreNum(MMP_BYTE bNum);
MMP_BYTE MMP_GetRawStoreNum(void);
#endif // _SNR_CFG_H_

