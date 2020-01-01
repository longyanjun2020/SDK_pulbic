//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "component_cfg.h"
#include "mmp_component_ctl.h"

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

//==============================================================================
//
//                              COMPONENT_SCRIPT_CFG
//
//==============================================================================

#if 0
void _____Component_Script_PCCAM____(){}
#endif

COMPONENT_CFG Component_Config_PURE_PCAM_PRM_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        DEVICE_SCL0,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_PCAM_DUAL_STREAM_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        DEVICE_SCL0,
        NULL,
        2,
        {&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING_2],NULL,NULL,NULL},
        {MMP_TRUE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        DEVICE_SCL1,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_PCAM_PRM_YUV422[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_UVC[UVC_COMP_FCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_UVC[UVC_COMP_FCAM_PREVIEW],
        DEVICE_UVC,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        1,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_PCAM_PRM_H264[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_MFE[MFE_COMP_PRM_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MFE[MFE_COMP_PRM_STREAM],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        1,
        {&Component_MGR[MGR_COMP_PRM_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_PRM_STREAM],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_PRM_STREAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_PCAM_PRM_MJPEG[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_JPE[JPE_COMP_PRM_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_MJPEG],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_MJPEG],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_MJPEG],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_PCAM_PRM_MJPEG_2ND[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING_2],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_JPE[JPE_COMP_PRM_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_MJPEG],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING_2],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_MJPEG],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_MJPEG],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_VR_N_PREV____(){}
#endif

COMPONENT_CFG Component_Config_VR_N_PREV_PRM_BAYER_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        DEVICE_SCL0,
        NULL,
        5,
        {&Component_MFE[MFE_COMP_PRM_RECD],&Component_JPE[JPE_COMP_PRM_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],&Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD]},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
#if (COMPONENT_SUPPORT_ORDER)
        {2, 1, 1, 1, 1}
#else
        {1, 1, 1, 1, 1}
#endif
    },
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        DEVICE_SCL1,
        NULL,
        3,
        {&Component_Display,&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_PRM_BAYER_FULL[] =
{
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_PRM_BAYER_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_SCD_ANADEC_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_SCD_ANADEC_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_SCD_ANADEC_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_SCD_BAYER_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        DEVICE_SCL0,
        NULL,
        4,
        {&Component_MFE[MFE_COMP_SCD_RECD],&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
#if (COMPONENT_SUPPORT_ORDER)
        {2, 1, 1, 1, 1}
#else
        {1, 1, 1, 1, 1}
#endif
    },
    {
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        DEVICE_SCL1,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_SCD_BAYER_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_SCD_BAYER_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_USBH_SRC[] =
{
    {
        &Component_HUVC[HUVC_COMP_UVC],
        DEVICE_HUVC,
        NULL,
        1,
        {&Component_JPD[JPD_COMP_MJPEG_DEC],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        DEVICE_JPD,
        &Component_HUVC[HUVC_COMP_UVC],
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_USBH_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_N_PREV_USBH_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_VR_R_PREV____(){}
#endif

COMPONENT_CFG Component_Config_VR_R_PREV_PRM_RAW_SRC[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        5,
        {&Component_MFE[MFE_COMP_PRM_RECD],&Component_JPE[JPE_COMP_PRM_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],&Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD]},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        #if (COMPONENT_SUPPORT_ORDER == 1)
        {2, 1, 1, 1, 1}
        #else
        {1, 1, 1, 1, 1}
        #endif
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_PRM_BAYER_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        DEVICE_SCL0,
        NULL,
        5,
        {&Component_MFE[MFE_COMP_PRM_RECD],&Component_JPE[JPE_COMP_PRM_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],&Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD]},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        #if (COMPONENT_SUPPORT_ORDER == 1)
        {2, 1, 1, 1, 1}
        #else
        {1, 1, 1, 1, 1}
        #endif
    },
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        DEVICE_SCL1,
        NULL,
        3,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_PRM_RAW_FULL[] =
{
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_PRM_BAYER_FULL[] =
{
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_PRM_BAYER_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN1_TEST[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        5,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA], &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB], &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INA], &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INB], &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING]},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INA[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        4,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INA],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INB[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INB],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW2[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};
COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_2IN1_INA[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_2IN1_INB[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX2],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_FULL_2IN1_OUT[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        NULL,
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_PIP_2IN2_OUT[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX2],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RESCAL_PREV],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_BAYER_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        DEVICE_SCL0,
        NULL,
        3,
        {&Component_MFE[MFE_COMP_SCD_RECD],&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
#if (COMPONENT_SUPPORT_ORDER)
        {2, 1, 1, 1, 1}
#else
        {1, 1, 1, 1, 1}
#endif
    },
    {
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        DEVICE_SCL1,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_BAYER_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_SCD_BAYER_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_USBH_SRC[] =
{
    {
        &Component_HUVC[HUVC_COMP_UVC],
        DEVICE_HUVC,
        NULL,
        1,
        {&Component_JPD[JPD_COMP_MJPEG_DEC],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        DEVICE_JPD,
        &Component_HUVC[HUVC_COMP_UVC],
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_USBH_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_R_PREV_USBH_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_VR_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_VR_RECD____(){}
#endif

COMPONENT_CFG Component_Config_VR_PRM_ANDDEC_RECD[] =
{
    {
        &Component_MFE[MFE_COMP_PRM_RECD],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC],
        1,
        {&Component_MGR[MGR_COMP_PRM_RECD],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_PRM_RECD],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_PRM_RECD],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_PRM_BAYER_RECD[] =
{
    {
        &Component_MFE[MFE_COMP_PRM_RECD],
        DEVICE_MFE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_MGR[MGR_COMP_PRM_RECD],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_PRM_RECD],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_PRM_RECD],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_PRM_BAYER_H264_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_MFE[MFE_COMP_PRM_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MFE[MFE_COMP_PRM_STREAM],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_STREAMING],
        1,
        {&Component_MGR[MGR_COMP_PRM_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_PRM_STREAM],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_PRM_STREAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_PRM_BAYER_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_PRM_PRIMARY],
        DEVICE_JPE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_PRM_ANADEC_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC],
        1,
        {&Component_JPE[JPE_COMP_PRM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_VR_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],
        1,
        {&Component_MemHost[MEMHOST_COMP_FCAM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_FCAM_VR_THUMB],
        DEVICE_MEMHOST,
        &Component_JPE[JPE_COMP_PRM_VR_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_PRM_BAYER_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_JPE[JPE_COMP_PRM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_VR_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],
        1,
        {&Component_MemHost[MEMHOST_COMP_FCAM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_FCAM_VR_THUMB],
        DEVICE_MEMHOST,
        &Component_JPE[JPE_COMP_PRM_VR_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SHARE_RECD_SCAL_OSD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        3,
        {&Component_MFE[MFE_COMP_SCD_RECD],&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
#if (COMPONENT_SUPPORT_ORDER)
        {2, 1, 1, 1, 1}
#else
        {1, 1, 1, 1, 1}
#endif
    },
};

COMPONENT_CFG Component_Config_VR_SHARE_RECD[] =
{
    {
        &Component_MFE[MFE_COMP_SCD_RECD],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD],
        1,
        {&Component_MGR[MGR_COMP_SCD_RECD],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_RECD],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_RECD],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SHARE_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SHARE_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD],
        1,
        {&Component_JPE[JPE_COMP_SCD_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        1,
        {&Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],
        DEVICE_MEMHOST,
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        3,
        {&Component_MFE[MFE_COMP_SCD_RECD],&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
#if (COMPONENT_SUPPORT_ORDER == 1)
        {2, 1, 1, 1, 1}
#else
        {1, 1, 1, 1, 1}
#endif
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INA[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INA],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INB[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INB],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX2],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_OUT[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        DEVICE_DIP_SCALE,
        NULL,
        3,
        {&Component_MFE[MFE_COMP_SCD_RECD],&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
#if (COMPONENT_SUPPORT_ORDER == 1)
        {2, 1, 1, 1, 1}
#else
        {1, 1, 1, 1, 1}
#endif
    },
};

COMPONENT_CFG Component_Config_VR_PRM_ANADEC_RECD_SCAL_OSD_2IN2_OUT[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        3,
        {&Component_MFE[MFE_COMP_PRM_RECD],&Component_JPE[JPE_COMP_PRM_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
    #if (COMPONENT_SUPPORT_ORDER == 1)
        {2, 1, 1, 1, 1}
    #else
        {1, 1, 1, 1, 1}
    #endif
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN2_OUT[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX2],
        3,
        {&Component_MFE[MFE_COMP_SCD_RECD],&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
    #if (COMPONENT_SUPPORT_ORDER == 1)
        {2, 1, 1, 1, 1}
    #else
        {1, 1, 1, 1, 1}
    #endif
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_RECD[] =
{
    {
        &Component_MFE[MFE_COMP_SCD_RECD],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {&Component_MGR[MGR_COMP_SCD_RECD],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_RECD],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_RECD],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_H264_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_MFE[MFE_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MFE[MFE_COMP_SCD_STREAM],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        1,
        {&Component_MGR[MGR_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_STREAM],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_STREAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_MJPEG_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_JPE[JPE_COMP_SCD_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_MJPEG],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_MJPEG],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_MJPEG],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_ANADEC_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {&Component_JPE[JPE_COMP_SCD_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        1,
        {&Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],
        DEVICE_MEMHOST,
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_BAYER_RECD[] =
{
    {
        &Component_MFE[MFE_COMP_SCD_RECD],
        DEVICE_MFE,
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        1,
        {&Component_MGR[MGR_COMP_SCD_RECD],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_RECD],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_RECD],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_BAYER_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        DEVICE_JPE,
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_SCD_BAYER_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        1,
        {&Component_JPE[JPE_COMP_SCD_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        1,
        {&Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],
        DEVICE_MEMHOST,
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_USBH_RECD_SCAL_OSD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        3,
        {&Component_MFE[MFE_COMP_SCD_RECD],&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
#if (COMPONENT_SUPPORT_ORDER == 1)
        {2, 1, 1, 1, 1}
#else
        {1, 1, 1, 1, 1}
#endif
    },
};

COMPONENT_CFG Component_Config_VR_USBH_UVC_RECD_SCAL_OSD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        3,
        {NULL,&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_USBH_RECD[] =
{
    {
        &Component_MFE[MFE_COMP_SCD_RECD],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {&Component_MGR[MGR_COMP_SCD_RECD],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_RECD],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_RECD],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_USBH_UVC_RECD[] =
{
    {
        &Component_MFE[MFE_COMP_UVC_RECD],
        DEVICE_MFE,
        NULL,
        1,
        {&Component_MGR[MGR_COMP_UVC_RECD],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_UVC_RECD],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_UVC_RECD],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_USBH_H264_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_MFE[MFE_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MFE[MFE_COMP_SCD_STREAM],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        1,
        {&Component_MGR[MGR_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_STREAM],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_STREAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_USBH_MJPEG_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_JPE[JPE_COMP_SCD_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_MJPEG],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_STREAMING],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_MJPEG],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_MJPEG],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_MJPEG],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_USBH_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_VR_USBH_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {&Component_JPE[JPE_COMP_SCD_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_THUMB],
        1,
        {&Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_RCAM_VR_THUMB],
        DEVICE_MEMHOST,
        &Component_JPE[JPE_COMP_SCD_VR_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_DSC_N_PREV____(){}
#endif

COMPONENT_CFG Component_Config_DSC_N_PREV_PRM_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        DEVICE_SCL0,
        NULL,
        2,
        {&Component_JPE[JPE_COMP_PRM_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        DEVICE_SCL1,
        NULL,
        3,
        {&Component_Display,&Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_STREAMING],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_PRM_FULL[] =
{
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_PRM_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_SCD_ANADEC_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_SCD_ANADEC_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_SCD_ANADEC_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_RESCAL_PREV],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_RESCAL_PREV],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_RESCAL_PREV],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_USBH_SRC[] =
{
    {
        &Component_HUVC[HUVC_COMP_UVC],
        DEVICE_HUVC,
        NULL,
        1,
        {&Component_JPD[JPD_COMP_MJPEG_DEC],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        DEVICE_JPD,
        &Component_HUVC[HUVC_COMP_UVC],
        3,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_USBH_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_N_PREV_USBH_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_DSC_R_PREV____(){}
#endif
//DIP_S14->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9
//DIP_S0->DIP_R0/DIP_S4
COMPONENT_CFG Component_Config_DSC_R_PREV_PRM_RAW_SRC[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        2,
        {&Component_DIP_Rotate[DIP_R_COMP_VR_FCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_PRM_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        DEVICE_SCL0,
        NULL,
        2,
        {&Component_JPE[JPE_COMP_PRM_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        DEVICE_SCL1,
        NULL,
        3,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_FCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_PRM_FULL[] =
{
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_FCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_FCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_PRM_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_FCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_FCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_FCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_ANADEC_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};
COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INA[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        3,
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INA],&Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};
COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INB[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        DEVICE_RAW_STORE,
        NULL,
        2, //TODO
        {&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB],&Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INB],NULL,NULL,NULL}, //TODO
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};
COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        DEVICE_RAW_STORE,
        NULL,
        2,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_CAPT_2IN2],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};
COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_ANADEC_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_ANADEC_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_RESCAL_PREV],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_RESCAL_PREV],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_RESCAL_PREV],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_BAYER_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        DEVICE_SCL0,
        NULL,
        2,
        {&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        DEVICE_SCL1,
        NULL,
        2,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_BAYER_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_SCD_BAYER_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_USBH_SRC[] =
{
    {
        &Component_HUVC[HUVC_COMP_UVC],
        DEVICE_HUVC,
        NULL,
        1,
        {&Component_JPD[JPD_COMP_MJPEG_DEC],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        DEVICE_JPD,
        &Component_HUVC[HUVC_COMP_UVC],
        3,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],&Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_USBH_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_R_PREV_USBH_PIP[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_PREVIEW],
        1,
        {&Component_PIP[PIP_COMP_PIP_PREVIEW],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PIP_PREVIEW],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_DSC_RCAM_PREVIEW],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_DSC_CAPTURE____(){}
#endif

COMPONENT_CFG Component_Config_DSC_PRM_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_PRM_PRIMARY],
        DEVICE_JPE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_PRM_Capture_Raw1[] =
{
    {
        &Component_JPE[JPE_COMP_PRM_PRIMARY],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_CAPT_2IN2],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_PRM_Capture_Thumb_Raw1[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_THUMB_2IN2],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_CAPT_2IN2],//RAWS_COMP_IDX RAWS_COMP_CH1
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_THUMB_2IN2],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        1,
        {&Component_JPE[JPE_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_PRM_Capture_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        1,
        {&Component_JPE[JPE_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_PRM_H264_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_MFE[MFE_COMP_PRM_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MFE[MFE_COMP_PRM_STREAM],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_STREAMING],
        1,
        {&Component_MGR[MGR_COMP_PRM_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_PRM_STREAM],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_PRM_STREAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        2,
        {&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW2[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_CH2],//RAWS_COMP_CH2 RAWS_COMP_IDX2
        2,
        {&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW1[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_CAPT_2IN2],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],//RAWS_COMP_CH2 RAWS_COMP_IDX2
        2,
        {&Component_JPE[JPE_COMP_PRM_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_THUMB_2IN2],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INA[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INA],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INB[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD_2IN1_INB],//todo:
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX2],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_OUT[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        DEVICE_DIP_SCALE,
        NULL,
        2,
        {&Component_JPE[JPE_COMP_SCD_PRIMARY],&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_Capture_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        1,
        {&Component_JPE[JPE_COMP_SCD_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_THUMB],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_ANADEC_H264_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {&Component_MFE[MFE_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MFE[MFE_COMP_SCD_STREAM],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],
        1,
        {&Component_MGR[MGR_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_STREAM],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_STREAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_BAYER_Capture[] =
{
    {
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        DEVICE_JPE,
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_PRIMARY],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_PRIMARY],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_SCD_BAYER_Capture_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],
        DEVICE_DIP_SCALE,
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_PRE_SCL],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_MID_SCL],
        1,
        {&Component_JPE[JPE_COMP_SCD_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_SCD_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_THUMB_POST_SCL],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_SCD_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_SCD_THUMB],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_SCD_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_USBH_CAPT_SCAL_OSD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_JPE[JPE_COMP_SCD_PRIMARY],NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_DSC_USBH_H264_WIFI[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {&Component_MFE[MFE_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MFE[MFE_COMP_SCD_STREAM],
        DEVICE_MFE,
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_STREAMING],
        1,
        {&Component_MGR[MGR_COMP_SCD_STREAM],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MGR[MGR_COMP_SCD_STREAM],
        DEVICE_MGR,
        &Component_MFE[MFE_COMP_SCD_STREAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_PLAYBACK____(){}
#endif

COMPONENT_CFG Component_Config_JPG_PB_N[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_JPEG_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    }
};

COMPONENT_CFG Component_Config_JPG_PB_R[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_JPEG_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_JPEG_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_JPEG_PB],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        1,
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_JPEG_PB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    }
};

COMPONENT_CFG Component_Config_JPG_PB_ReScale_N[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_JPEG_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_JPEG_PB_RE_SCAL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB_RE_SCAL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        1,
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB_RE_SCAL],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    }
};

COMPONENT_CFG Component_Config_JPG_PB_ReScale_R[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_JPEG_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_JPEG_PB_RE_SCAL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB_RE_SCAL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_JPEG_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_JPEG_PB],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_JPEG_PB_RE_SCAL],
        1,
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_DIP_Rotate[DIP_R_COMP_JPEG_PB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    }
};

COMPONENT_CFG Component_Config_MOVIE_PB_N[] =
{
    {
        &Component_HVD,
        DEVICE_HVD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        DEVICE_DIP_SCALE,
        &Component_HVD,
        1,
        {&Component_TCL,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_TCL,
        DEVICE_TCL,
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        1,
#if (VIDEO_PLAYBACK_USE_PIP)
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#else
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#endif
};

COMPONENT_CFG Component_Config_MOVIE_PB_R[] =
{
    {
        &Component_HVD,
        DEVICE_HVD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        DEVICE_DIP_SCALE,
        &Component_HVD,
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_MOVIE_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_MOVIE_PB],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        1,
        {&Component_TCL,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_TCL,
        DEVICE_TCL,
        &Component_DIP_Rotate[DIP_R_COMP_MOVIE_PB],
        1,
#if (VIDEO_PLAYBACK_USE_PIP)
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#else
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#endif
};

COMPONENT_CFG Component_Config_MOVIE_PB_ReScale_N[] =
{
    {
        &Component_HVD,
        DEVICE_HVD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        DEVICE_DIP_SCALE,
        &Component_HVD,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_MOVIE_PB_RE_SCAL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB_RE_SCAL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        1,
        {&Component_TCL,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_TCL,
        DEVICE_TCL,
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB_RE_SCAL],
        1,
#if (VIDEO_PLAYBACK_USE_PIP)
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#else
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#endif
};

COMPONENT_CFG Component_Config_MOVIE_PB_ReScale_R[] =
{
    {
        &Component_HVD,
        DEVICE_HVD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        DEVICE_DIP_SCALE,
        &Component_HVD,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_MOVIE_PB_RE_SCAL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB_RE_SCAL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_MOVIE_PB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_MOVIE_PB],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_MOVIE_PB_RE_SCAL],
        1,
        {&Component_TCL,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_TCL,
        DEVICE_TCL,
        &Component_DIP_Rotate[DIP_R_COMP_MOVIE_PB],
        1,
#if (VIDEO_PLAYBACK_USE_PIP)
        {&Component_PIP[PIP_COMP_PLAYBACK],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_PIP[PIP_COMP_PLAYBACK],
        DEVICE_PIP,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#else
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_TCL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
#endif
};

#if 0
void _____Component_Script_BROWSER____(){}
#endif

COMPONENT_CFG Component_Config_BROWSER_VID_THUMB_N[] =
{
    {
        &Component_HVD,
        DEVICE_HVD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        DEVICE_DIP_SCALE,
        &Component_HVD,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        1,
        {&Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],
        DEVICE_MEMHOST,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_BROWSER_VID_THUMB_R[] =
{
    {
        &Component_HVD,
        DEVICE_HVD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        DEVICE_DIP_SCALE,
        &Component_HVD,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        DEVICE_DIP_SCALE,
        &Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],
        1,
        {&Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],
        DEVICE_MEMHOST,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_BROWSER_DSC_Prm2Thumb_N[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        1,
        {&Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],
        DEVICE_MEMHOST,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_BROWSER_DSC_Pure_Thumb_N[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],
        DEVICE_MEMHOST,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_BROWSER_DSC_Prm2Thumb_R[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        DEVICE_DIP_SCALE,
        &Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],
        1,
        {&Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],
        DEVICE_MEMHOST,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_BROWSER_DSC_Pure_Thumb_R[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        1,
        {&Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_MemHost[MEMHOST_COMP_BROWSER_THUMB],
        DEVICE_MEMHOST,
        &Component_DIP_Rotate[DIP_R_COMP_THUMB_ROT],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_BROWSER_DSC_Prm2Thumb_ReEncode[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_PRE],
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        DEVICE_DIP_SCALE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        1,
        {&Component_JPE[JPE_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL_POST],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_BROWSER_DSC_Pure_Thumb_ReEncode[] =
{
    {
        &Component_JPD[JPD_COMP_STILL_DEC],
        DEVICE_JPD,
        NULL,
        1,
        {&Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        DEVICE_DIP_SCALE,
        &Component_JPD[JPD_COMP_STILL_DEC],
        1,
        {&Component_JPE[JPE_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPE[JPE_COMP_PRM_THUMB],
        DEVICE_JPE,
        &Component_DIP_Scale[DIP_S_COMP_THUMB_SCL],
        1,
        {&Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_JPEMGR[JPEMGR_COMP_PRM_THUMB],
        DEVICE_JPE_MGR,
        &Component_JPE[JPE_COMP_PRM_THUMB],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_ADAS____(){}
#endif

COMPONENT_CFG Component_Config_ADAS[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_Adas,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Adas,
        DEVICE_ADAS,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_MDTC[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],
        DEVICE_DIP_SCALE,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {&Component_Mdtc,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Mdtc,
        DEVICE_MDTC,
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

#if 0
void _____Component_Script_Test_____(){}
#endif

COMPONENT_CFG Component_Config_Display[] =
{
    {
        &Component_Display,
        DEVICE_DISPLAY,
        NULL,
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};

COMPONENT_CFG Component_Config_SCL_2_DSPY[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        DEVICE_SCL0,
        NULL,
        1,
        {&Component_MFE[MFE_COMP_PRM_RECD],NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        DEVICE_SCL1,
        NULL,
        1,
        {&Component_Display,NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
    {
        &Component_Display,
        DEVICE_DISPLAY,
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE},
        {1, 1, 1, 1, 1}
    },
};
