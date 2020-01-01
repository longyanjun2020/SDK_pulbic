/**
* @file HAL_MmpResCtrl.h
*
* This header file defines the interfaces of multimedia resources
* in HW adaptor layer
*/

#ifndef __HAL_MMPRESCTRL_H__
#define __HAL_MMPRESCTRL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "HAL_MmpResCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum MediaMmpRes_e_
{
    MEDIA_MMP_RES__MMP_CAMERA = 0,
    MEDIA_MMP_RES__MMP_AUD,
    MEDIA_MMP_RES__MMP_VDO,
    MEDIA_MMP_RES__MMP_VDO_NON_PLAYBACK,
    MEDIA_MMP_RES__MMP_USB,
    MEDIA_MMP_RES__MMP_USB_MSC,
    MEDIA_MMP_RES__MMP_USB_CDC,
    MEDIA_MMP_RES__MMP_IMG_CODEC,
    MEDIA_MMP_RES__MMP_IMG_CODEC_SW,
    MEDIA_MMP_RES__MMP_VFS,
    MEDIA_MMP_RES__MMP_VDOCHAT,
    MEDIA_MMP_RES__MMP_GPS,
    MEDIA_MMP_RES__MMP_CAMERA_I2C,
    MEDIA_MMP_RES__MMP_VT,    //video telephony
    MEDIA_MMP_RES__NUM,
    MEDIA_MMP_RES__INVALID
} MediaMmpRes_e;

typedef struct MediaMmpResInfo_t_
{
    u16 uResNum;
    MediaMmpRes_e *pMediaMmpInfo;
} MediaMmpResInfo_t;

typedef struct MmpResCtrl_TravData_t_
{
    u16 uNewReqResID;
    ResCtrlHandle_t pConflictResCtrlHdl;
    bool bConflict;
} MmpResCtrl_TravData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__HAL_MMPRESCTRL_H__

