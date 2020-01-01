//------------------------------------------------------------------------------
//
//  File        : cust_component_cfg.c
//  Description : Source file of Component configuration
//  Author      : CZ
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "component_cfg.h"
#include "mmp_component_ctl.h"
#include "cust_component_cfg.h"

#include "component_raws.h"
#include "component_dip.h"
#include "component_scl.h"
#include "component_display.h"
#include "component_mfe.h"
#include "component_mgr.h"
#include "component_jpe.h"
#include "component_jpemgr.h"
#include "component_jpd.h"
#include "component_aud.h"
#include "component_pip.h"
#include "component_hvd.h"
#include "component_HvdTimerCtl.h"
#include "component_adas.h"
#include "component_huvc.h"
#include "component_uvc.h"
#include "component_memhost.h"

#include "Config_SDK.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

// Preview Script:
// 1. Component_Config_N: Normal preview: SCL -> Display
// 2. Component_Config_R: Rotate preview: SCL -> DIP -> Display
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
MMP_BOOL gbLCDRotate = MMP_TRUE;
#else
MMP_BOOL gbLCDRotate = MMP_FALSE;
#endif

CUSTOMER_COMP_SCRIPT m_stScriptCfg[COMPO_SCRIPT_TYPE_NUM] =
{
    /* PCAM Mode */
    {
        COMPO_SCRIPT_PURE_PCAM_PRM_SRC,
        "PURE_PCAM_PRM_SRC",
        MMP_FALSE,
        Component_Config_PURE_PCAM_PRM_SRC,
        1,
        SCL0_COMP_PRM_CAM,              // DEVICE_SCL0
    },
    {
        COMPO_SCRIPT_PCAM_DUAL_STREAM_SRC,
        "PCAM_DUAL_STREAM_SRC",
        MMP_FALSE,
        Component_Config_PCAM_DUAL_STREAM_SRC,
        2,
        SCL0_COMP_PRM_CAM,              // DEVICE_SCL0
        SCL1_COMP_PRM_CAM,              // DEVICE_SCL1 (for Algorithm, ex: MDTC)
    },
    {
        COMPO_SCRIPT_PCAM_PRM_YUV422,
        "PCAM_PRM_YUV422",
        MMP_FALSE,
        Component_Config_PCAM_PRM_YUV422,
        2,
        DIP_S_COMP_VR_FCAM_STREAMING,   // DEVICE_DIP_S
        UVC_COMP_FCAM_PREVIEW,          // DEVICE_UVC
    },
    {
        COMPO_SCRIPT_PCAM_PRM_H264,
        "PCAM_PRM_H264",
        MMP_FALSE,
        Component_Config_PCAM_PRM_H264,
        3,
        DIP_S_COMP_VR_FCAM_STREAMING,   // DEVICE_DIP_S
        MFE_COMP_PRM_STREAM,            // DEVICE_MFE
        MGR_COMP_PRM_STREAM,            // DEVICE_MGR,
    },
    {
        COMPO_SCRIPT_PCAM_PRM_MJPEG,
        "PCAM_PRM_MJPEG",
        MMP_FALSE,
        Component_Config_PCAM_PRM_MJPEG,
        3,
        DIP_S_COMP_VR_FCAM_STREAMING,   // DEVICE_DIP_S
        JPE_COMP_PRM_MJPEG,             // DEVICE_JPE
        JPEMGR_COMP_PRM_MJPEG,          // DEVICE_JPE_MGR,
    },
    {
        COMPO_SCRIPT_PCAM_PRM_MJPEG_2ND,
        "PCAM_PRM_MJPEG_2ND",
        MMP_FALSE,
        Component_Config_PCAM_PRM_MJPEG_2ND,
        3,
        DIP_S_COMP_VR_FCAM_STREAMING_2, // DEVICE_DIP_S
        JPE_COMP_PRM_MJPEG,             // DEVICE_JPE
        JPEMGR_COMP_PRM_MJPEG,          // DEVICE_JPE_MGR,
    },
    {
        COMPO_SCRIPT_PCAM_SCD_YUV422,
        "PCAM_SCD_YUV422",
        MMP_FALSE,
        NULL,
        0,
    },
    {
        COMPO_SCRIPT_PCAM_SCD_H264,
        "PCAM_SCD_H264",
        MMP_FALSE,
        NULL,
        0,
    },
    {
        COMPO_SCRIPT_PCAM_SCD_MJPEG,
        "PCAM_SCD_MJPEG",
        MMP_FALSE,
        NULL,
        0,
    },
    /* VR Mode : No Rotate Preview Flow */
    {
        COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_SRC,
        "VR_N_PREV_PRM_BAYER_SRC",
        MMP_FALSE,
        Component_Config_VR_N_PREV_PRM_BAYER_SRC,
        2,
        SCL0_COMP_PRM_CAM,              // DEVICE_SCL0
        SCL1_COMP_PRM_CAM,              // DEVICE_SCL1
    },
    {
        COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_FULL,
        "VR_N_PREV_PRM_BAYER_FULL",
        MMP_FALSE,
        Component_Config_VR_N_PREV_PRM_BAYER_FULL,
        1,
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_PIP,
        "VR_N_PREV_PRM_BAYER_PIP",
        MMP_FALSE,
        Component_Config_VR_N_PREV_PRM_BAYER_PIP,
        2,
        DIP_S_COMP_VR_FCAM_PREVIEW,     // DEVICE_DIP_S
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_SRC,
        "VR_N_PREV_SCD_ANADEC_SRC",
        MMP_FALSE,
        Component_Config_VR_N_PREV_SCD_ANADEC_SRC,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_FULL,
        "VR_N_PREV_SCD_ANADEC_FULL",
        MMP_FALSE,
        Component_Config_VR_N_PREV_SCD_ANADEC_FULL,
        2,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_PIP,
        "VR_N_PREV_SCD_ANADEC_PIP",
        MMP_FALSE,
        Component_Config_VR_N_PREV_SCD_ANADEC_PIP,
        3,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_S_COMP_VR_RCAM_RESCAL_PREV, // DEVICE_DIP_S
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_SRC,
        "VR_N_PREV_SCD_BAYER_SRC",
        MMP_FALSE,
        Component_Config_VR_N_PREV_SCD_BAYER_SRC,
        2,
        SCL0_COMP_SCD_CAM,              // DEVICE_SCL0
        SCL1_COMP_SCD_CAM,              // DEVICE_SCL1
    },
    {
        COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_FULL,
        "VR_N_PREV_SCD_BAYER_FULL",
        MMP_FALSE,
        Component_Config_VR_N_PREV_SCD_BAYER_FULL,
        2,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_PIP,
        "VR_N_PREV_SCD_BAYER_PIP",
        MMP_FALSE,
        Component_Config_VR_N_PREV_SCD_BAYER_PIP,
        2,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_N_PREV_USBH_SRC,
        "VR_N_PREV_USBH_SRC",
        MMP_FALSE,
        Component_Config_VR_N_PREV_USBH_SRC,
        2,
        HUVC_COMP_UVC,                  // DEVICE_UVC
        JPD_COMP_MJPEG_DEC,             // DEVICE_JPD
    },
    {
        COMPO_SCRIPT_VR_N_PREV_USBH_FULL,
        "VR_N_PREV_USBH_FULL",
        MMP_FALSE,
        Component_Config_VR_N_PREV_USBH_FULL,
        2,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_N_PREV_USBH_PIP,
        "VR_N_PREV_USBH_PIP",
        MMP_FALSE,
        Component_Config_VR_N_PREV_USBH_PIP,
        2,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    /* VR Mode : Rotate Preview Flow */
    {
        COMPO_SCRIPT_VR_R_PREV_PRM_RAW_SRC,
        "VR RAW_CH1:DIP_S0->DIP_R0",
        //"VR RAW_CH1:DIP_S0->DIP_R0+DIP_S4",//"VR RAW_CH1:DIP_S14->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9",
        MMP_FALSE,
        Component_Config_VR_R_PREV_PRM_RAW_SRC,
        2,
        DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC,              // DEVICE_DIP_S
        DIP_S_COMP_VR_FCAM_PREVIEW,              // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_SRC,
        "VR_R_PREV_PRM_BAYER_SRC",
        MMP_FALSE,
        Component_Config_VR_R_PREV_PRM_BAYER_SRC,
        2,
        SCL0_COMP_PRM_CAM,              // DEVICE_SCL0
        SCL1_COMP_PRM_CAM,              // DEVICE_SCL1
    },
    {
        COMPO_SCRIPT_VR_R_PREV_PRM_RAW_FULL,
        "PREV_DIP_S0<-DIP_R0->DISP",
        MMP_FALSE,
        Component_Config_VR_R_PREV_PRM_RAW_FULL,
        2,
        DIP_R_COMP_VR_FCAM_PREVIEW,     // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_FULL,
        "VR_R_PREV_PRM_BAYER_FULL",
        MMP_FALSE,
        Component_Config_VR_R_PREV_PRM_BAYER_FULL,
        2,
        DIP_R_COMP_VR_FCAM_PREVIEW,     // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_PIP,
        "VR_R_PREV_PRM_BAYER_PIP",
        MMP_FALSE,
        Component_Config_VR_R_PREV_PRM_BAYER_PIP,
        3,
        DIP_S_COMP_VR_FCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_R_COMP_VR_FCAM_PREVIEW,     // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC,
        "VR_R_PREV_SCD_ANADEC_SRC",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_SRC,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN1_TEST,
        "VR_R_PREV_SCD_ANADEC_SRC_2IN1_TEST",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN1_TEST,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INA,
        "RAWS_CH1->DIP_S10+DIP_S12+DIP_S8+DIP_S0",//"VR_R_PREV_SCD_ANADEC_SRC_2IN1_INA",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INA,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1,
        "RAWS_CH1->DIP_S0+DIP_S14+DIP_S8",//"VR_R_PREV_SCD_ANADEC_SRC_2IN1_INA",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW2,
        "RAWS_CH2->DIP_S1/DIP_S3/DIP_S8",//"VR_R_PREV_SCD_ANADEC_SRC_2IN1_INA",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW2,
        1,
        RAWS_COMP_IDX2,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INB,
        "VR_R_PREV_SCD_ANADEC_SRC_2IN1_INB",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INB,
        1,
        RAWS_COMP_IDX2,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_FULL,
        "VR_R_PREV_SCD_ANADEC_FULL",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_FULL,
        3,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP,
        "VR_R_PREV_SCD_ANADEC_PIP",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_PIP,
        4,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_S_COMP_VR_RCAM_RESCAL_PREV, // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_2IN1_INA,
        "VR_R_PREV_SCD_ANADEC_2IN1_INA",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_2IN1_INA,
        1,
        DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA, // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_2IN1_INB,
        "VR_R_PREV_SCD_ANADEC_2IN1_INB",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_2IN1_INB,
        1,
        DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB, // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_FULL_2IN1_OUT,
        "VR_R_PREV_SCD_ANADEC_FULL_2IN1_OUT",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_FULL_2IN1_OUT,
        3,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT,
        "2IN1:DIP_S1->DIP_S2->DIP_R1->PIP0",//"VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT,
        4,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_S_COMP_VR_RCAM_RESCAL_PREV, // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP_2IN2_OUT,
        "2IN2:DIP_S1->DIP_S2->DIP_R1->PIP0",//"VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_PIP_2IN2_OUT,
        4,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_S_COMP_VR_RCAM_RESCAL_PREV, // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_SRC,
        "VR_R_PREV_SCD_BAYER_SRC",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_BAYER_SRC,
        2,
        SCL0_COMP_SCD_CAM,               // DEVICE_SCL0
        SCL1_COMP_SCD_CAM,               // DEVICE_SCL1
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_FULL,
        "VR_R_PREV_SCD_BAYER_FULL",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_BAYER_FULL,
        3,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_PIP,
        "VR_R_PREV_SCD_BAYER_PIP",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_BAYER_PIP,
        3,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_VR_R_PREV_USBH_SRC,
        "VR_R_PREV_USBH_SRC",
        MMP_FALSE,
        Component_Config_VR_R_PREV_USBH_SRC,
        2,
        HUVC_COMP_UVC,                  // DEVICE_UVC
        JPD_COMP_MJPEG_DEC,             // DEVICE_JPD
    },
    {
        COMPO_SCRIPT_VR_R_PREV_USBH_FULL,
        "VR_R_PREV_USBH_FULL",
        MMP_FALSE,
        Component_Config_VR_R_PREV_USBH_FULL,
        3,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_VR_R_PREV_USBH_PIP,
        "VR_R_PREV_USBH_PIP",
        MMP_FALSE,
        Component_Config_VR_R_PREV_USBH_PIP,
        3,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    /* VR Mode : Record/Streaming/Capture Flow */
    {
        COMPO_SCRIPT_VR_PRM_ANADEC_RECD_RAW1,
        "PRM_RECD:DIP_S14<-MFE0->MGR0",
        MMP_FALSE,
        Component_Config_VR_PRM_ANDDEC_RECD,
        2,
        MFE_COMP_PRM_RECD,              // DEVICE_MFE
        MGR_COMP_PRM_RECD,              // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1,
        "PRM_THUMB:DIP_S14<-DIP_S5->JPE9->MEMHOST1",
        MMP_FALSE,
        Component_Config_VR_PRM_ANADEC_Thumb,
        3,
        DIP_S_COMP_VR_FCAM_THUMB,       // DEVICE_DIP_S
        JPE_COMP_PRM_VR_THUMB,          // DEVICE_JPE
        MEMHOST_COMP_FCAM_VR_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_VR_PRM_ANADEC_RECD_SCAL_OSD_RAW1,
        "RAW1<-DIP_S14_RREC->MFE0/JPE3_PRIMARY/DIP_S5_RTHUMB",
        MMP_FALSE,
        Component_Config_VR_PRM_ANADEC_RECD_SCAL_OSD_2IN2_OUT,
        1,
        DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC,        // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_PRM_BAYER_RECD,
        "VR_PRM_BAYER_RECD",
        MMP_FALSE,
        Component_Config_VR_PRM_BAYER_RECD,
        2,
        MFE_COMP_PRM_RECD,              // DEVICE_MFE
        MGR_COMP_PRM_RECD,              // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_PRM_BAYER_H264_WIFI,
        "VR_PRM_BAYER_H264_WIFI",
        MMP_FALSE,
        Component_Config_VR_PRM_BAYER_H264_WIFI,
        3,
        DIP_S_COMP_VR_FCAM_STREAMING,   // DEVICE_DIP_S
        MFE_COMP_PRM_STREAM,            // DEVICE_MFE
        MGR_COMP_PRM_STREAM,            // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_PRM_BAYER_CAPTURE,
        "VR_PRM_BAYER_CAPTURE",
        MMP_FALSE,
        Component_Config_VR_PRM_BAYER_Capture,
        2,
        JPE_COMP_PRM_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_PRM_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_VR_PRM_BAYER_THUMB,
        "VR_PRM_BAYER_THUMB",
        MMP_FALSE,
        Component_Config_VR_PRM_BAYER_Thumb,
        3,
        DIP_S_COMP_VR_FCAM_THUMB,       // DEVICE_DIP_S
        JPE_COMP_PRM_VR_THUMB,          // DEVICE_JPE
        MEMHOST_COMP_FCAM_VR_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_VR_SHARE_RECD_SCAL_OSD,
        "VR_SHARE_RECD_SCAL_OSD",
        MMP_FALSE,
        Component_Config_VR_SHARE_RECD_SCAL_OSD,
        1,
        DIP_S_COMP_VR_SHARE_RECD,       // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_SHARE_RECD,
        "VR_SHARE_RECORD",
        MMP_FALSE,
        Component_Config_VR_SHARE_RECD,
        2,
        MFE_COMP_SCD_RECD,              // DEVICE_MFE
        MGR_COMP_SCD_RECD,              // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_SHARE_CAPTURE,
        "VR_SHARE_CAPTURE",
        MMP_FALSE,
        Component_Config_VR_SHARE_Capture,
        2,
        JPE_COMP_SCD_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_SCD_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_VR_SHARE_THUMB,
        "VR_SHARE_THUMB",
        MMP_FALSE,
        Component_Config_VR_SHARE_Thumb,
        3,
        DIP_S_COMP_VR_RCAM_THUMB,       // DEVICE_DIP_S
        JPE_COMP_SCD_VR_THUMB,          // DEVICE_JPE
        MEMHOST_COMP_RCAM_VR_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD,
        "VR_SCD_ANADEC_RECD_SCAL_OSD",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD,
        1,
        DIP_S_COMP_VR_RCAM_RECD,        // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INA,
        "VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INA",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INA,
        1,
        DIP_S_COMP_VR_RCAM_RECD_2IN1_INA, // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INB,
        "VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INB",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INB,
        1,
        DIP_S_COMP_VR_RCAM_RECD_2IN1_INB, // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_OUT,
        "DIP_S3_RREC->MFE1/JPE4_PRIMARY/DIP_S6_RTHUMB",//"VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_OUT",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_OUT,
        1,
        DIP_S_COMP_VR_RCAM_RECD,        // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN2_OUT,
        "RAW2<-DIP_S3_RREC->MFE1/JPE4_PRIMARY/DIP_S6_RTHUMB",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN2_OUT,
        1,
        DIP_S_COMP_VR_RCAM_RECD,        // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_RECD,
        "SCD_RECD:DIP_S3<-MFE1->MGR1",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_RECD,
        2,
        MFE_COMP_SCD_RECD,              // DEVICE_MFE
        MGR_COMP_SCD_RECD,              // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_H264_WIFI,
        "VR_SCD_ANADEC_H264_WIFI",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_H264_WIFI,
        3,
        DIP_S_COMP_VR_RCAM_STREAMING,   // DEVICE_DIP_S
        MFE_COMP_SCD_STREAM,            // DEVICE_MFE
        MGR_COMP_SCD_STREAM,            // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_MJPEG_WIFI,
        "VR_SCD_ANADEC_MJPEG_WIFI",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_MJPEG_WIFI,
        3,
        DIP_S_COMP_VR_RCAM_STREAMING,   // DEVICE_DIP_S
        JPE_COMP_SCD_MJPEG,             // DEVICE_JPE
        JPEMGR_COMP_SCD_MJPEG,          // DEVICE_JPE_MGR,
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_CAPTURE,
        "VR_SCD_ANADEC_CAPTURE",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_Capture,
        2,
        JPE_COMP_SCD_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_SCD_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_VR_SCD_ANADEC_THUMB,
        "SCD_THUMB:DIP_S3<-DIP_S6->JPE10->MEMHOST2",
        MMP_FALSE,
        Component_Config_VR_SCD_ANADEC_Thumb,
        3,
        DIP_S_COMP_VR_RCAM_THUMB,       // DEVICE_DIP_S
        JPE_COMP_SCD_VR_THUMB,          // DEVICE_JPE
        MEMHOST_COMP_RCAM_VR_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_VR_SCD_BAYER_RECD,
        "VR_SCD_BAYER_RECD",
        MMP_FALSE,
        Component_Config_VR_SCD_BAYER_RECD,
        2,
        MFE_COMP_SCD_RECD,              // DEVICE_MFE
        MGR_COMP_SCD_RECD,              // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_SCD_BAYER_CAPTURE,
        "VR_SCD_BAYER_CAPTURE",
        MMP_FALSE,
        Component_Config_VR_SCD_BAYER_Capture,
        2,
        JPE_COMP_SCD_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_SCD_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_VR_SCD_BAYER_THUMB,
        "VR_SCD_BAYER_THUMB",
        MMP_FALSE,
        Component_Config_VR_SCD_BAYER_Thumb,
        3,
        DIP_S_COMP_VR_RCAM_THUMB,       // DEVICE_DIP_S
        JPE_COMP_SCD_VR_THUMB,          // DEVICE_JPE
        MEMHOST_COMP_RCAM_VR_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_VR_USBH_RECD_SCAL_OSD,
        "VR_USBH_RECD_SCAL_OSD",
        MMP_FALSE,
        Component_Config_VR_USBH_RECD_SCAL_OSD,
        1,
        DIP_S_COMP_VR_RCAM_RECD,        // DEVICE_DIP_S
    },
    {
    	COMPO_SCRIPT_VR_USBH_UVC_RECD_SCAL_OSD,
        "VR_USBH_UVC_RECD_SCAL_OSD",
        MMP_FALSE,
		Component_Config_VR_USBH_UVC_RECD_SCAL_OSD,
        1,
        DIP_S_COMP_VR_RCAM_RECD,        // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_VR_USBH_RECD,
        "VR_USBH_RECD",
        MMP_FALSE,
        Component_Config_VR_USBH_RECD,
        2,
        MFE_COMP_SCD_RECD,              // DEVICE_MFE
        MGR_COMP_SCD_RECD,              // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_USBH_UVC_RECD,
        "VR_USBH_UVC_RECD",
        MMP_FALSE,
        Component_Config_VR_USBH_UVC_RECD,
        2,
		MFE_COMP_UVC_RECD,              // DEVICE_MFE
		MGR_COMP_UVC_RECD,              // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_USBH_H264_WIFI,
        "VR_USBH_H264_WIFI",
        MMP_FALSE,
        Component_Config_VR_USBH_H264_WIFI,
        3,
        DIP_S_COMP_VR_RCAM_STREAMING,   // DEVICE_DIP_S
        MFE_COMP_SCD_STREAM,            // DEVICE_MFE
        MGR_COMP_SCD_STREAM,            // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_VR_USBH_MJPEG_WIFI,
        "VR_USBH_MJPEG_WIFI",
        MMP_FALSE,
        Component_Config_VR_USBH_MJPEG_WIFI,
        3,
        DIP_S_COMP_VR_RCAM_STREAMING,   // DEVICE_DIP_S
        JPE_COMP_SCD_MJPEG,             // DEVICE_JPE
        JPEMGR_COMP_SCD_MJPEG,          // DEVICE_JPE_MGR,
    },
    {
        COMPO_SCRIPT_VR_USBH_CAPTURE,
        "VR_USBH_CAPTURE",
        MMP_FALSE,
        Component_Config_VR_USBH_Capture,
        2,
        JPE_COMP_SCD_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_SCD_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_VR_USBH_THUMB,
        "VR_USBH_THUMB",
        MMP_FALSE,
        Component_Config_VR_USBH_Thumb,
        3,
        DIP_S_COMP_VR_RCAM_THUMB,       // DEVICE_DIP_S
        JPE_COMP_SCD_VR_THUMB,          // DEVICE_JPE
        MEMHOST_COMP_RCAM_VR_THUMB,     // DEVICE_MEMHOST
    },
    /* DSC Mode : No Rotate Preview Flow */
    {
        COMPO_SCRIPT_DSC_N_PREV_PRM_SRC,
        "DSC_N_PREV_PRM_SRC",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_PRM_SRC,
        2,
        SCL0_COMP_PRM_CAM,              // DEVICE_SCL0
        SCL1_COMP_PRM_CAM,              // DEVICE_SCL1
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_PRM_FULL,
        "DSC_N_PREV_PRM_FULL",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_PRM_FULL,
        1,
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_PRM_PIP,
        "DSC_N_PREV_PRM_PIP",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_PRM_PIP,
        2,
        DIP_S_COMP_DSC_FCAM_PREVIEW,    // DEVICE_DIP_S
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_SRC,
        "DSC_N_PREV_SCD_ANADEC_SRC",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_SCD_ANADEC_SRC,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_FULL,
        "DSC_N_PREV_SCD_ANADEC_FULL",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_SCD_ANADEC_FULL,
        2,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_PIP,
        "DSC_N_PREV_SCD_ANADEC_PIP",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_SCD_ANADEC_PIP,
        3,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_S_COMP_DSC_RCAM_RESCAL_PREV,// DEVICE_DIP_S
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_USBH_SRC,
        "DSC_N_PREV_USBH_SRC",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_USBH_SRC,
        2,
        HUVC_COMP_UVC,                  // DEVICE_UVC
        JPD_COMP_MJPEG_DEC,             // DEVICE_JPD
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_USBH_FULL,
        "DSC_N_PREV_USBH_FULL",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_USBH_FULL,
        2,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DSC_N_PREV_USBH_PIP,
        "DSC_N_PREV_USBH_PIP",
        MMP_FALSE,
        Component_Config_DSC_N_PREV_USBH_PIP,
        2,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    /* DSC Mode : Rotate Preview Flow */
    {
        COMPO_SCRIPT_DSC_R_PREV_PRM_SRC,
        "DSC_R_PREV_PRM_SRC",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_PRM_SRC,
        2,
        SCL0_COMP_PRM_CAM,              // DEVICE_SCL0
        SCL1_COMP_PRM_CAM,              // DEVICE_SCL1
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_PRM_RAW_SRC,
        "DSC:RAW_CH1:DIP_S0->DIP_R0/DIP_S4",//"DSC:RAW_CH1:DIP_S14->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_PRM_RAW_SRC,
        #if 0
        2,
        DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC,        // DEVICE_DIP_S
        #else
        1,
        #endif
        DIP_S_COMP_VR_FCAM_PREVIEW,              // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_PRM_FULL,
        "DSC_R_PREV_PRM_FULL",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_PRM_FULL,
        2,
        DIP_R_COMP_DSC_FCAM_PREVIEW,    // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_PRM_PIP,
        "DSC_R_PREV_PRM_PIP",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_PRM_PIP,
        3,
        DIP_S_COMP_DSC_FCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_R_COMP_DSC_FCAM_PREVIEW,    // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC,
        "DSC_R_PREV_SCD_ANADEC_SRC",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_ANADEC_SRC,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_2IN1_INA,
        "DSC_R_PREV_SCD_ANADEC_2IN1_INA",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_2IN1_INA,//same as VR
        1,
        DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA, // DIP_S10
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_2IN1_INB,
        "DSC_R_PREV_SCD_ANADEC_2IN1_INB",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_2IN1_INB,//same as VR temp~
        1,
        DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB, // DIP_S11
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INA,
        "RAWS_CH1->DIP_S10+DIP_S12+DIP_S0",//"DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INA",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INA,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INB,
        "DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INB",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INB,
        1,
        RAWS_COMP_IDX2,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1,
        "DSC:RAW1->DIP_S0+DIP_S9",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1,
        1,
        RAWS_COMP_IDX,                  // DEVICE_RAW_STORE
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_FULL,
        "DSC_R_PREV_SCD_ANADEC_FULL",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_ANADEC_FULL,
        3,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_R_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_PIP,
        "DSC_R_PREV_SCD_ANADEC_PIP",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_ANADEC_PIP,
        4,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_S_COMP_DSC_RCAM_RESCAL_PREV,// DEVICE_DIP_S
        DIP_R_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_PIP_2IN1_OUT,
        "DSC_R_PREV_SCD_ANADEC_PIP_2IN1_OUT",
        MMP_FALSE,
        Component_Config_VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT,//todo:
        4,
        DIP_S_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_S
        DIP_S_COMP_VR_RCAM_RESCAL_PREV, // DEVICE_DIP_S
        DIP_R_COMP_VR_RCAM_PREVIEW,     // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_SRC,
        "DSC_R_PREV_SCD_BAYER_SRC",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_BAYER_SRC,
        2,
        SCL0_COMP_SCD_CAM,               // DEVICE_SCL0
        SCL1_COMP_SCD_CAM,               // DEVICE_SCL1
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_FULL,
        "DSC_R_PREV_SCD_BAYER_FULL",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_BAYER_FULL,
        3,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_R_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_PIP,
        "DSC_R_PREV_SCD_BAYER_PIP",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_SCD_BAYER_PIP,
        3,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_R_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_USBH_SRC,
        "DSC_R_PREV_USBH_SRC",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_USBH_SRC,
        2,
        HUVC_COMP_UVC,                  // DEVICE_UVC
        JPD_COMP_MJPEG_DEC,             // DEVICE_JPD
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_USBH_FULL,
        "DSC_R_PREV_USBH_FULL",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_USBH_FULL,
        3,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_R_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_R
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DSC_R_PREV_USBH_PIP,
        "DSC_R_PREV_USBH_PIP",
        MMP_FALSE,
        Component_Config_DSC_R_PREV_USBH_PIP,
        3,
        DIP_S_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_S
        DIP_R_COMP_DSC_RCAM_PREVIEW,    // DEVICE_DIP_R
        PIP_COMP_PIP_PREVIEW,           // DEVICE_PIP
    },
    /* DSC Mode : Capture Flow */
    {
        COMPO_SCRIPT_DSC_PRM_CAPTURE,
        "DSC_PRM_CAPTURE",
        MMP_FALSE,
        Component_Config_DSC_PRM_Capture,
        2,
        JPE_COMP_PRM_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_PRM_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_PRM_CAPTURE_RAW1,
        "DSC:DIP_S9<-JPE3->JPEMGR3",
        MMP_FALSE,
        Component_Config_DSC_PRM_Capture_Raw1,
        2,
        JPE_COMP_PRM_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_PRM_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_PRM_CAPTURE_THUMB,
        "DSC_PRM_CAPTURE_THUMB",
        MMP_FALSE,
        Component_Config_DSC_PRM_Capture_Thumb,
        5,
        DIP_S_COMP_DSC_THUMB_PRE_SCL,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_MID_SCL,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_POST_SCL,  // DEVICE_DIP_S
        JPE_COMP_PRM_THUMB,             // DEVICE_JPE
        JPEMGR_COMP_PRM_THUMB,          // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_PRM_CAPTURE_THUMB_RAW1,
        "DSC:DIP_S9<-DIP_S14->DIP_S5->DIP_S6->JPE6->JPGMGR6",
        MMP_FALSE,
        Component_Config_DSC_PRM_Capture_Thumb_Raw1,
        5,
        DIP_S_COMP_DSC_FCAM_THUMB_2IN2,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_MID_SCL,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_POST_SCL,  // DEVICE_DIP_S
        JPE_COMP_PRM_THUMB,             // DEVICE_JPE
        JPEMGR_COMP_PRM_THUMB,          // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_PRM_H264_WIFI,
        "DSC_PRM_H264_WIFI",
        MMP_FALSE,
        Component_Config_DSC_PRM_H264_WIFI,
        3,
        DIP_S_COMP_DSC_FCAM_STREAMING,  // DEVICE_DIP_S
        MFE_COMP_PRM_STREAM,            // DEVICE_MFE
        MGR_COMP_PRM_STREAM             // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_OUT,
        "DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_OUT",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_OUT,
        1,
        DIP_S_COMP_DSC_RCAM_CAPTURE,    // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD,
        "DSC_SCD_ANADEC_CAPT_SCAL_OSD",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD,
        1,
        DIP_S_COMP_DSC_RCAM_CAPTURE,    // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW1,
        "DSC:RAW1<-DIP_S9->JPE3+DIP_S14",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW1,
        1,
        DIP_S_COMP_DSC_FCAM_CAPT_2IN2,    // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW2,
        "DSC:RAW2<-DIP_S3->JPE4+DIP_S4",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW2,
        1,
        DIP_S_COMP_DSC_RCAM_CAPTURE,    // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INA,
        "DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INA",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INA,
        1,
        DIP_S_COMP_VR_RCAM_RECD_2IN1_INA, // DIP_S12
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INB,
        "DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INB",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INB,
        1,
        DIP_S_COMP_VR_RCAM_RECD_2IN1_INB, // DIP_S13
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPTURE,
        "DSC:DIP_S3<-JPE4->JPEMGR4",//"DSC_SCD_ANADEC_CAPTURE",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_Capture,
        2,
        JPE_COMP_SCD_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_SCD_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_CAPTURE_THUMB,
        "DSC:DIP_S3<-DIP_S4->DIP_S5->DIP_S6->JPE7->JPEMGR7",//"DSC_SCD_ANADEC_CAPTURE_THUMB"
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_Capture_Thumb,
        5,
        DIP_S_COMP_DSC_THUMB_PRE_SCL,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_MID_SCL,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_POST_SCL,  // DEVICE_DIP_S
        JPE_COMP_SCD_THUMB,             // DEVICE_JPE
        JPEMGR_COMP_SCD_THUMB,          // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_SCD_ANADEC_H264_WIFI,
        "DSC_SCD_ANADEC_H264_WIFI",
        MMP_FALSE,
        Component_Config_DSC_SCD_ANADEC_H264_WIFI,
        3,
        DIP_S_COMP_DSC_RCAM_STREAMING,  // DEVICE_DIP_S
        MFE_COMP_SCD_STREAM,            // DEVICE_MFE
        MGR_COMP_SCD_STREAM             // DEVICE_MGR
    },
    {
        COMPO_SCRIPT_DSC_SCD_BAYER_CAPTURE,
        "DSC_SCD_BAYER_CAPTURE",
        MMP_FALSE,
        Component_Config_DSC_SCD_BAYER_Capture,
        2,
        JPE_COMP_SCD_PRIMARY,           // DEVICE_JPE
        JPEMGR_COMP_SCD_PRIMARY,        // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_SCD_BAYER_CAPTURE_THUMB,
        "DSC_SCD_BAYER_CAPTURE_THUMB",
        MMP_FALSE,
        Component_Config_DSC_SCD_BAYER_Capture_Thumb,
        5,
        DIP_S_COMP_DSC_THUMB_PRE_SCL,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_MID_SCL,   // DEVICE_DIP_S
        DIP_S_COMP_DSC_THUMB_POST_SCL,  // DEVICE_DIP_S
        JPE_COMP_SCD_THUMB,             // DEVICE_JPE
        JPEMGR_COMP_SCD_THUMB,          // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_DSC_USBH_CAPT_SCAL_OSD,
        "DSC_USBH_CAPT_SCAL_OSD",
        MMP_FALSE,
        Component_Config_DSC_USBH_CAPT_SCAL_OSD,
        1,
        DIP_S_COMP_DSC_RCAM_CAPTURE,    // DEVICE_DIP_S
    },
    {
        COMPO_SCRIPT_DSC_USBH_H264_WIFI,
        "DSC_USBH_H264_WIFI",
        MMP_FALSE,
        Component_Config_DSC_USBH_H264_WIFI,
        3,
        DIP_S_COMP_DSC_RCAM_STREAMING,  // DEVICE_DIP_S
        MFE_COMP_SCD_STREAM,            // DEVICE_MFE
        MGR_COMP_SCD_STREAM             // DEVICE_MGR
    },
    /* Playback Mode */
    {
        COMPO_SCRIPT_JPG_PB_N,
        "JPG_PB_N",
        MMP_FALSE,
        Component_Config_JPG_PB_N,
        3,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_JPEG_PB,             // DEVICE_DIP_S
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_JPG_PB_R,
        "JPG_PB_R",
        MMP_FALSE,
        Component_Config_JPG_PB_R,
        4,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_JPEG_PB,             // DEVICE_DIP_S
        DIP_R_COMP_JPEG_PB,             // DEVICE_DIP_R
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_JPG_PB_RESCALE_N,
        "JPG_PB_RESCALE_N",
        MMP_FALSE,
        Component_Config_JPG_PB_ReScale_N,
        4,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_JPEG_PB,             // DEVICE_DIP_S
        DIP_S_COMP_JPEG_PB_RE_SCAL,     // DEVICE_DIP_S
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_JPG_PB_RESCALE_R,
        "JPG_PB_RESCALE_R",
        MMP_FALSE,
        Component_Config_JPG_PB_ReScale_R,
        5,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_JPEG_PB,             // DEVICE_DIP_S
        DIP_S_COMP_JPEG_PB_RE_SCAL,     // DEVICE_DIP_S
        DIP_R_COMP_JPEG_PB,             // DEVICE_DIP_R
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
    },
    {
        COMPO_SCRIPT_MOVIE_PB_N,
        "MOVIE_PB_N",
        MMP_FALSE,
        Component_Config_MOVIE_PB_N,
        4,
        ONLY_ONE_COMP_IDX,              // DEVICE_HVD       (ONLY ONE)
        DIP_S_COMP_MOVIE_PB,            // DEVICE_DIP_S
        HTCL_COMP_SKIP_FRM,             // DEVICE_TCL
        #if (VIDEO_PLAYBACK_USE_PIP)
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
        #else
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
        #endif
    },
    {
        COMPO_SCRIPT_MOVIE_PB_R,
        "MOVIE_PB_R",
        MMP_FALSE,
        Component_Config_MOVIE_PB_R,
        5,
        ONLY_ONE_COMP_IDX,              // DEVICE_HVD       (ONLY ONE)
        DIP_S_COMP_MOVIE_PB,            // DEVICE_DIP_S
        DIP_R_COMP_MOVIE_PB,            // DEVICE_DIP_R
        HTCL_COMP_SKIP_FRM,             // DEVICE_TCL
        #if (VIDEO_PLAYBACK_USE_PIP)
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
        #else
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
        #endif
    },
    {
        COMPO_SCRIPT_MOVIE_PB_RESCALE_N,
        "MOVIE_PB_RESCALE_N",
        MMP_FALSE,
        Component_Config_MOVIE_PB_ReScale_N,
        5,
        ONLY_ONE_COMP_IDX,              // DEVICE_HVD       (ONLY ONE)
        DIP_S_COMP_MOVIE_PB,            // DEVICE_DIP_S
        DIP_S_COMP_MOVIE_PB_RE_SCAL,    // DEVICE_DIP_S
        HTCL_COMP_SKIP_FRM,             // DEVICE_TCL
        #if (VIDEO_PLAYBACK_USE_PIP)
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
        #else
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
        #endif
    },
    {
        COMPO_SCRIPT_MOVIE_PB_RESCALE_R,
        "MOVIE_PB_RESCALE_R",
        MMP_FALSE,
        Component_Config_MOVIE_PB_ReScale_R,
        6,
        ONLY_ONE_COMP_IDX,              // DEVICE_HVD       (ONLY ONE)
        DIP_S_COMP_MOVIE_PB,            // DEVICE_DIP_S
        DIP_S_COMP_MOVIE_PB_RE_SCAL,    // DEVICE_DIP_S
        DIP_R_COMP_MOVIE_PB,            // DEVICE_DIP_R
        HTCL_COMP_SKIP_FRM,             // DEVICE_TCL
        #if (VIDEO_PLAYBACK_USE_PIP)
        PIP_COMP_PLAYBACK,              // DEVICE_PIP
        #else
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
        #endif
    },
    /* Browser Mode */
    {
        COMPO_SCRIPT_BROWSER_VID_THUMB_N,
        "BROWSER_VID_THUMB_N",
        MMP_FALSE,
        Component_Config_BROWSER_VID_THUMB_N,
        5,
        ONLY_ONE_COMP_IDX,              // DEVICE_HVD       (ONLY ONE)
        DIP_S_COMP_THUMB_SCL_PRE,       // DEVICE_DIP_S
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S // 864x480 -> 256x192
        DIP_S_COMP_THUMB_SCL_POST,      // DEVICE_DIP_S // 256x192 -> 192x128
        MEMHOST_COMP_BROWSER_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_BROWSER_VID_THUMB_R,
        "BROWSER_VID_THUMB_R",
        MMP_FALSE,
        Component_Config_BROWSER_VID_THUMB_R,
        6,
        ONLY_ONE_COMP_IDX,              // DEVICE_HVD       (ONLY ONE)
        DIP_S_COMP_THUMB_SCL_PRE,       // DEVICE_DIP_S
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S // 864x480 -> 256x192
        DIP_R_COMP_THUMB_ROT,           // DEVICE_DIP_R // 90 degree 256x192 -> 192x256
        DIP_S_COMP_THUMB_SCL_POST,      // DEVICE_DIP_S // 192x256 -> 128x192
        MEMHOST_COMP_BROWSER_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_N,
        "BROWSER_DSC_PRM2THUMB_N",
        MMP_FALSE,
        Component_Config_BROWSER_DSC_Prm2Thumb_N,
        5,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_THUMB_SCL_PRE,       // DEVICE_DIP_S
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S
        DIP_S_COMP_THUMB_SCL_POST,      // DEVICE_DIP_S
        MEMHOST_COMP_BROWSER_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_N,
        "BROWSER_DSC_PURE_THUMB_N",
        MMP_FALSE,
        Component_Config_BROWSER_DSC_Pure_Thumb_N,
        3,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S
        MEMHOST_COMP_BROWSER_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_R,
        "BROWSER_DSC_PRM2THUMB_R",
        MMP_FALSE,
        Component_Config_BROWSER_DSC_Prm2Thumb_R,
        6,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_THUMB_SCL_PRE,       // DEVICE_DIP_S
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S
        DIP_R_COMP_THUMB_ROT,           // DEVICE_DIP_R
        DIP_S_COMP_THUMB_SCL_POST,      // DEVICE_DIP_S
        MEMHOST_COMP_BROWSER_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_R,
        "BROWSER_DSC_PURE_THUMB_R",
        MMP_FALSE,
        Component_Config_BROWSER_DSC_Pure_Thumb_R,
        4,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S
        DIP_R_COMP_THUMB_ROT,           // DEVICE_DIP_R
        MEMHOST_COMP_BROWSER_THUMB,     // DEVICE_MEMHOST
    },
    {
        COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_REENCODE,
        "BROWSER_DSC_PRM2THUMB_REENCODE",
        MMP_FALSE,
        Component_Config_BROWSER_DSC_Prm2Thumb_ReEncode,
        6,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_THUMB_SCL_PRE,       // DEVICE_DIP_S
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S
        DIP_S_COMP_THUMB_SCL_POST,      // DEVICE_DIP_S
        JPE_COMP_PRM_THUMB,             // DEVICE_JPE
        JPEMGR_COMP_PRM_THUMB,          // DEVICE_JPE_MGR
    },
    {
        COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_REENCODE,
        "BROWSER_DSC_PURE_THUMB_REENCODE",
        MMP_FALSE,
        Component_Config_BROWSER_DSC_Pure_Thumb_ReEncode,
        4,
        JPD_COMP_STILL_DEC,             // DEVICE_JPD
        DIP_S_COMP_THUMB_SCL,           // DEVICE_DIP_S
        JPE_COMP_PRM_THUMB,             // DEVICE_JPE
        JPEMGR_COMP_PRM_THUMB,          // DEVICE_JPE_MGR
    },
    /* ADAS */
    {
        COMPO_SCRIPT_ADAS,
        "ADAS",
        MMP_FALSE,
        Component_Config_ADAS,
        2,
        DIP_S_COMP_VR_FCAM_ADAS,        // DEVICE_DIP_S
        ADAS_COMPONENT_STD,             // DEVICE_ADAS
    },
    {
        COMPO_SCRIPT_MDTC,
        "MDTC",
        MMP_FALSE,
        Component_Config_MDTC,
        2,
        DIP_S_COMP_VR_FCAM_ADAS,        // DEVICE_DIP_S
        MDTC_COMPONENT_STD,             // DEVICE_MDTC
    },
    /* Misc */
    {
        COMPO_SCRIPT_DEMO1,
        "DEMO1",
        MMP_FALSE,
        Component_Config_SCL_2_DSPY,
        3,
        ONLY_ONE_COMP_IDX,              // DEVICE_SCL0      (ONLY ONE)
        ONLY_ONE_COMP_IDX,              // DEVICE_SCL1      (ONLY ONE)
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_DISPLAY,
        "DISPLAY",
        MMP_FALSE,
        Component_Config_Display,
        1,
        ONLY_ONE_COMP_IDX,              // DEVICE_DISPLAY   (ONLY ONE)
    },
    {
        COMPO_SCRIPT_UNIT_TEST,
        "UT",
        MMP_FALSE,
        NULL,
        0,
    },
};

CUSTOMER_COMP_PORT_SCRIPT m_stPortScriptCfg[PORT_SCRIPT_TYPE_NUM] =
{
    /* PCAM Mode */
    {
        PORT_SCRIPT_PURE_PCAM_PRM_SRC,
        "PURE_PCAM_PRM_SRC",
        Port_Config_PURE_PCAM_PRM_SRC,
    },
    {
        PORT_SCRIPT_PURE_PCAM_PRM_SRC_2ND,
        "PURE_PCAM_PRM_SRC_2ND",
        Port_Config_PURE_PCAM_PRM_SRC_2ND,
    },
    {
        PORT_SCRIPT_MIX_PCAM_PRM_SRC,
        "MIX_PCAM_PRM_SRC",
        Port_Config_MIX_PCAM_PRM_SRC,
    },
    /* VR Mode Preview */
    {
        PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL,
        "VR_PREV_PRM_BAYER_FULL",
        Port_Config_VR_PREV_PRM_BAYER_FULL,
    },
    {
        PORT_SCRIPT_VR_PREV_PRM_RAW_FULL,
        "DIP_S0 open outport0=DIP_R0",
        Port_Config_VR_PREV_PRM_RAW_FULL,
    },
    {
        PORT_SCRIPT_VR_PREV_PRM_BAYER_PIP,
        "VR_PREV_PRM_BAYER_PIP",
        Port_Config_VR_PREV_PRM_BAYER_PIP,
    },
    {
        PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC,
        "VR_PREV_SCD_ANADEC_SRC",
        Port_Config_VR_PREV_SCD_ANADEC_SRC,
    },
    {
        PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST,
        "VR_PREV_SCD_ANADEC_SRC_2IN1_TEST",
        Port_Config_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST,
    },
    {
        PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_INA,
        "VR_PREV_SCD_ANADEC_SRC_2IN1_INA",
        Port_Config_VR_PREV_SCD_ANADEC_SRC_2IN1_INA,
    },
    {
        PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_INB,
        "VR_PREV_SCD_ANADEC_SRC_2IN1_INB",
        Port_Config_VR_PREV_SCD_ANADEC_SRC_2IN1_INB,
    },
    {
        PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW1,
        "RAWS_CH1 open port0=DIP_S0",//"VR_PREV_PRM_ANADEC_SRC_RAW",
        Port_Config_VR_PREV_PRM_ANADEC_SRC_RAW1,
    },
    {
        PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW2,
        "RAWS_CH2 open port0=DIP_S1",//"VR_PREV_PRM_ANADEC_SRC_RAW",
        Port_Config_VR_PREV_PRM_ANADEC_SRC_RAW2,
    },
    {
        PORT_SCRIPT_VR_PREV_SCD_BAYER,
        "VR_PREV_SCD_BAYER",
        Port_Config_VR_PREV_SCD_BAYER,
    },
    {
        PORT_SCRIPT_VR_PREV_USBH_SRC,
        "VR_PREV_USBH_SRC",
        Port_Config_VR_PREV_USBH_SRC,
    },
    /* VR Mode Record */
    {
        PORT_SCRIPT_VR_PRM_ANADEC_RECD_RAW1,
        "PRM_RECD:DIP_S14 opp0 MFE0",
        Port_Config_VR_RPM_ANADEC_RECD,
    },
    {
        PORT_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1,
        "VR_PRM_THUMB:DIP_S14 opp2 DIP_S5",
        Port_Config_VR_PRM_ANADEC_Thumb_Raw1,
    },
    {
        PORT_SCRIPT_VR_PRM_ANADEC_RECD_SRC_2IN2_RAW1,
        "PRM_RECD_SRC:RAW1 opp1 DIP_S14",
        Port_Config_VR_PRM_ANADEC_RECD_SRC_2IN2_RAW1,
    },
    {
        PORT_SCRIPT_VR_PRM_BAYER_RECD,
        "VR_PRM_BAYER_RECD",
        Port_Config_VR_RPM_BAYER_RECD,
    },
    {
        PORT_SCRIPT_VR_PRM_BAYER_H264_WIFI,
        "VR_PRM_BAYER_H264_WIFI",
        Port_Config_VR_PRM_BAYER_H264_WIFI,
    },
    {
        PORT_SCRIPT_VR_PRM_BAYER_CAPTURE,
        "VR_PRM_BAYER_CAPTURE",
        Port_Config_VR_PRM_BAYER_Capture,
    },
    {
        PORT_SCRIPT_VR_PRM_BAYER_THUMB,
        "VR_PRM_BAYER_THUMB",
        Port_Config_VR_PRM_BAYER_Thumb,
    },
    {
        PORT_SCRIPT_VR_SHARE_RECD_SRC,
        "VR_SHARE_RECD_SRC",
        Port_Config_VR_SHARE_RECD_SRC,
    },
    {
        PORT_SCRIPT_VR_SHARE_RECD,
        "VR_SHARE_RECD",
        Port_Config_VR_SHARE_RECD,
    },
    {
        PORT_SCRIPT_VR_SHARE_CAPTURE,
        "VR_SHARE_CAPTURE",
        Port_Config_VR_SHARE_Capture,
    },
    {
        PORT_SCRIPT_VR_SHARE_THUMB,
        "VR_SHARE_THUMB",
        Port_Config_VR_SHARE_Thumb,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC,
        "VR_SCD_ANADEC_RECD_SRC",
        Port_Config_VR_SCD_ANADEC_RECD_SRC,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC_2IN2_RAW2,
        "SCD_RECD_SRC:RAW2 opp1 DIP_S3",
        Port_Config_VR_SCD_ANADEC_RECD_SRC_2IN2_RAW2,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC_2IN1_INA,
        "VR_SCD_ANADEC_RECD_SRC_2IN1_INA",
        Port_Config_VR_SCD_ANADEC_RECD_SRC_2IN1_INA,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC_2IN1_INB,
        "VR_SCD_ANADEC_RECD_SRC_2IN1_INB",
        Port_Config_VR_SCD_ANADEC_RECD_SRC_2IN1_INB,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_RECD,
        "SCD_RECD:DIP_S3 opp0 MFE1",
        Port_Config_VR_SCD_ANADEC_RECD,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_WIFI,
        "VR_SCD_ANADEC_WIFI",
        Port_Config_VR_SCD_ANADEC_WIFI,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_CAPTURE,
        "VR_SCD_ANADEC_CAPTURE",
        Port_Config_VR_SCD_ANADEC_Capture,
    },
    {
        PORT_SCRIPT_VR_SCD_ANADEC_THUMB,
        "SCD_THUMB:DIP_S3 opp2 DIP_S4",
        Port_Config_VR_SCD_ANADEC_Thumb,
    },
    {
        PORT_SCRIPT_VR_SCD_BAYER_RECD,
        "VR_SCD_BAYER_RECORD",
        Port_Config_VR_SCD_BAYER_RECD,
    },
    {
        PORT_SCRIPT_VR_SCD_BAYER_CAPTURE,
        "VR_SCD_BAYER_CAPTURE",
        Port_Config_VR_SCD_BAYER_Capture,
    },
    {
        PORT_SCRIPT_VR_SCD_BAYER_THUMB,
        "VR_SCD_BAYER_THUMB",
        Port_Config_VR_SCD_BAYER_Thumb,
    },
    {
        PORT_SCRIPT_VR_USBH_RECD_SRC,
        "VR_USBH_RECD_SRC",
        Port_Config_VR_USBH_RECD_SRC,
    },
    {
        PORT_SCRIPT_VR_USBH_RECD,
        "VR_USBH_RERD",
        Port_Config_VR_USBH_RECD,
    },
    {
        PORT_SCRIPT_VR_USBH_WIFI,
        "VR_USBH_WIFI",
        Port_Config_VR_USBH_WIFI,
    },
    {
        PORT_SCRIPT_VR_USBH_CAPTURE,
        "VR_USBH_CAPTURE",
        Port_Config_VR_USBH_Capture,
    },
    {
        PORT_SCRIPT_VR_USBH_THUMB,
        "VR_USBH_THUMB",
        Port_Config_VR_USBH_Thumb,
    },
    /* DSC Mode Preview */
    {
        PORT_SCRIPT_DSC_PREV_PRM_FULL,
        "DSC_PREV_PRM_FULL",
        Port_Config_DSC_PREV_PRM_FULL,
    },
    {
        PORT_SCRIPT_DSC_PREV_PRM_PIP,
        "DSC_PREV_PRM_PIP",
        Port_Config_DSC_PREV_PRM_PIP,
    },
    {
        PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC,
        "DSC_PREV_SCD_ANADEC_SRC",
        Port_Config_DSC_PREV_SCD_ANADEC_SRC,
    },
    {
        PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC_2IN1_INA,
        "DSC_PREV_SCD_ANADEC_SRC_2IN1_INA",
        Port_Config_DSC_PREV_SCD_ANADEC_SRC_2IN1_INA,
    },
    {
        PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC_2IN1_INB,
        "DSC_PREV_SCD_ANADEC_SRC_2IN1_INB",
        Port_Config_DSC_PREV_SCD_ANADEC_SRC_2IN1_INB,
    },
    {
        PORT_SCRIPT_DSC_PREV_PRM_ANADEC_SRC_RAW,
        "RAWS_CH1 open port3=DIP_S0",//"DSC_PREV_PRM_ANADEC_SRC_RAW",
        Port_Config_DSC_PREV_PRM_ANADEC_SRC_RAW,
    },
    {
        PORT_SCRIPT_DSC_PREV_SCD_BAYER,
        "DSC_PREV_SCD_BAYER",
        Port_Config_DSC_PREV_SCD_BAYER,
    },
    {
        PORT_SCRIPT_DSC_PREV_USBH,
        "DSC_PREV_USBH",
        Port_Config_DSC_PREV_USBH_SRC,
    },
    /* DSC Mode Capture */
    {
        PORT_SCRIPT_DSC_PRM_CAPTURE,
        "DSC_PRM_CAPTURE",
        Port_Config_DSC_PRM_Capture,
    },
    {
        PORT_SCRIPT_DSC_PRM_CAPTURE_RAW1,
        "DSC_PRM_CAP:DIP_S9 open port0=JPE3",
        Port_Config_DSC_PRM_Capture_Raw1,
    },
    {
        PORT_SCRIPT_DSC_PRM_CAPTURE_THUMB,
        "DSC_PRM_CAPTURE_THUMB",
        Port_Config_DSC_PRM_Capture_Thumb,
    },
    {
        PORT_SCRIPT_DSC_PRM_CAPTURE_THUMB_RAW1,
        "DSC:DIP_S9 open port1=DIP_S14",
        Port_Config_DSC_PRM_Capture_Thumb_Raw1,
    },
    {
        PORT_SCRIPT_DSC_PRM_H264_WIFI,
        "DSC_PRM_H264_WIFI",
        Port_Config_DSC_PRM_H264_WIFI,
    },
    {
        PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC,
        "DSC_SCD_ANADEC_CAPTURE_SRC",
        Port_Config_DSC_SCD_ANADEC_Capture_SRC,
    },
    {
        PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN2_RAW1,
        "DSC:RAW1 open port1=DIP_S9",
        Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN2_RAW1,
    },
    {
        PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN2_RAW2,
        "DSC:RAW2 open port1=DIP_S3",//"DSC_SCD_ANADEC_CAPTURE_SRC"
        Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN2_RAW2,
    },
    {
        PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN1_INA,
        "DSC_SCD_ANADEC_CAPTURE_SRC_2IN1_INA",
        Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN1_INA,
    },
        {
        PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN1_INB,
        "DSC_SCD_ANADEC_CAPTURE_SRC_2IN1_INB",
        Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN1_INB,
    },
    {
        PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE,
        "DSC:DIP_S3 open port0=JPE4",//"DSC_SCD_ANADEC_CAPTURE",
        Port_Config_DSC_SCD_ANADEC_Capture,
    },
    {
        PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_THUMB,
        "DSC:DIP_S3 open port1=DIP_S4",//"DSC_SCD_ANADEC_CAPTURE_THUMB",
        Port_Config_DSC_SCD_ANADEC_Capture_Thumb,
    },
    {
        PORT_SCRIPT_DSC_SCD_ANADEC_H264_WIFI,
        "DSC_SCD_ANADEC_H264_WIFI",
        Port_Config_DSC_SCD_ANADEC_H264_WIFI,
    },
    {
        PORT_SCRIPT_DSC_SCD_BAYER_CAPTURE,
        "DSC_SCD_BAYER_CAPTURE",
        Port_Config_DSC_SCD_BAYER_Capture,
    },
    {
        PORT_SCRIPT_DSC_SCD_BAYER_CAPTURE_THUMB,
        "DSC_SCD_BAYER_CAPTURE_THUMB",
        Port_Config_DSC_SCD_BAYER_Capture_Thumb,
    },
    {
        PORT_SCRIPT_DSC_USBH_CAPTURE_SRC,
        "DSC_USBH_CAPTURE_SRC",
        Port_Config_DSC_USBH_Capture_SRC,
    },
    {
        PORT_SCRIPT_DSC_USBH_H264_WIFI,
        "DSC_USBH_H264_WIFI",
        Port_Config_DSC_USBH_H264_WIFI,
    },
    /* ADAS */
    {
        PORT_SCRIPT_ALGORITHM,
        "ALGORITHM",
        Port_Config_Algorithm,
    },
    {
        PORT_SCRIPT_ALGORITHM_PCAM,
        "ALGORITHM_PCAM",
        Port_Config_Algorithm_PCAM,
    },
    {
        PORT_SCRIPT_ADAS,
        "ADAS",
        Port_Config_ADAS,
    },
    {
        PORT_SCRIPT_MDTC,
        "MDTC",
        Port_Config_MDTC,
    }
};
