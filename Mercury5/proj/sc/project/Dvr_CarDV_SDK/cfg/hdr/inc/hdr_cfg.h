//------------------------------------------------------------------------------
//
//  File        : hdr_cfg.h
//  Description : Header file of HDR configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _HDR_CFG_H_
#define _HDR_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "drv_ms_cus_sensor.h"
#include "snr_cfg.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
    HDR_MODE_STAGGER,
    HDR_MODE_SEQUENTIAL,
    HDR_MODE_NUM
} HDR_MODE;

typedef enum {
    HDR_BITMODE_8BIT,
    HDR_BITMODE_10BIT,
    HDR_BITMODE_NUM
} HDR_BITMODE;

typedef enum {
    HDR_VC_STORE_2PLANE,
    HDR_VC_STORE_2ENGINE,
    HDR_VC_STORE_PLACEMENT_NUM
} HDR_VC_STORE_PLACEMENT;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct {
    MMP_BYTE    ubVidHdrType;
    MMP_BYTE    ubDscHdrType;
    MMP_UBYTE   ubMode;
    MMP_BOOL    bRawGrabEnable;
    MMP_UBYTE   ubRawStoreBitMode;
    MMP_UBYTE   ubVcStoreMethod;
    MMP_UBYTE   ubBktFrameNum;
} HDR_CFG;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern HDR_CFG gsHdrCfg[2];

//==============================================================================
//
//                              Function
//
//==============================================================================

void     MMP_SetVidHDRType(CAM_TYPE camtype, MMP_BYTE ubVidHdrType);
void     MMP_SetDscHDRType(CAM_TYPE camtype, MMP_BYTE ubDscHdrType);
MMP_BYTE MMP_GetVidHDRType(CAM_TYPE camtype);
MMP_BYTE MMP_GetDscHDRType(CAM_TYPE camtype);

#endif // _HDR_CFG_H_

