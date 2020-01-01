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

#include "vidrec_cfg.h"
#include "snr_cfg.h"
#include "mmp_vidrec_inc.h"
#include "mmp_snr_inc.h"
#include "mmps_3gprecd.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/*
 * Configure of Video Record
 */
VIDREC_CFG gsVidRecCfg[MAX_CAM_NUM] = {
    {   // PRM_CAM
        VIDREC_H264_BASELINE_PROFILE,           // eProfile
        MMP_DISPLAY_WIN_PIP,/*LOWER_WINDOW*/    // eDispWinId
        MMP_TRUE,                               // bPreviewActive
    },
    {   // SCD_CAM
        VIDREC_H264_BASELINE_PROFILE,           // eProfile
        MMP_DISPLAY_WIN_OVERLAY,/*UPPER_WINDOW*/// eDispWinId
        MMP_TRUE,                               // bPreviewActive
    },
    {   // USBH_CAM
        VIDREC_H264_BASELINE_PROFILE,           // eProfile
        MMP_DISPLAY_WIN_OVERLAY,/*UPPER_WINDOW*/// eDispWinId
        MMP_TRUE,                               // bPreviewActive
    },
};
