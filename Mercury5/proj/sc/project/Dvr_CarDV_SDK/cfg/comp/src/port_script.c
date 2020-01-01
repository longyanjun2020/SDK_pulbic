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
//                              PORT SCRIPT
//
//==============================================================================

#if 0
void _____Port_Script_PCAM_____(){}
#endif

COMPONENT_PORT_CFG Port_Config_PURE_PCAM_PRM_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_PURE_PCAM_PRM_SRC_2ND[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_MIX_PCAM_PRM_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        3,
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE}
    },
};

#if 0
void _____Port_Script_VR_Preview____(){}
#endif

COMPONENT_PORT_CFG Port_Config_VR_PREV_PRM_BAYER_FULL[] =
{
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_PRM_RAW_FULL[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_PREVIEW],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_PRM_BAYER_PIP[] =
{
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_SCD_ANADEC_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {MMP_TRUE, MMP_TRUE, MMP_TRUE, MMP_TRUE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_SCD_ANADEC_SRC_2IN1_INA[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_SCD_ANADEC_SRC_2IN1_INB[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_PRM_ANADEC_SRC_RAW1[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_VR_PREV_PRM_ANADEC_SRC_RAW2[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_SCD_BAYER[] =
{
    {
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PREV_USBH_SRC[] =
{
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

#if 0
void _____Port_Script_VR_Recd____(){}
#endif

COMPONENT_PORT_CFG Port_Config_VR_RPM_ANADEC_RECD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_RPM_BAYER_RECD[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PRM_BAYER_H264_WIFI[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        3,
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PRM_BAYER_Capture[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PRM_BAYER_Thumb[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_PRM_ANADEC_Thumb_Raw1[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SHARE_RECD_SRC[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        4,
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_TRUE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SHARE_RECD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SHARE_Capture[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SHARE_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_SHARE_RECD],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_RECD_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_RECD_SRC_2IN2_RAW2[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_VR_PRM_ANADEC_RECD_SRC_2IN2_RAW1[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_RECD_SRC_2IN1_INA[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_RECD_SRC_2IN1_INB[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_RECD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_WIFI[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_Capture[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_ANADEC_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_BAYER_RECD[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_BAYER_Capture[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_SCD_BAYER_Thumb[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_USBH_RECD_SRC[] =
{
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_USBH_RECD[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_USBH_WIFI[] =
{
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_USBH_Capture[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_VR_USBH_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_RCAM_RECD],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

#if 0
void _____Port_Script_DSC_Preview_____(){}
#endif

COMPONENT_PORT_CFG Port_Config_DSC_PREV_PRM_FULL[] =
{
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_PREV_PRM_PIP[] =
{
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_PREV_SCD_ANADEC_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_PREV_SCD_ANADEC_SRC_2IN1_INA[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_PREV_SCD_ANADEC_SRC_2IN1_INB[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_DSC_PREV_PRM_ANADEC_SRC_RAW[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_DSC_PREV_SCD_BAYER[] =
{
    {
        &Component_SCL1[SCL1_COMP_SCD_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_PREV_USBH_SRC[] =
{
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

#if 0
void _____Port_Script_DSC_Capture_____(){}
#endif

COMPONENT_PORT_CFG Port_Config_DSC_PRM_Capture[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_DSC_PRM_Capture_Raw1[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_CAPT_2IN2],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}//port0=JPE3
    },
};
COMPONENT_PORT_CFG Port_Config_DSC_PRM_Capture_Thumb[] =
{
    {
        &Component_SCL0[SCL0_COMP_PRM_CAM],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_DSC_PRM_Capture_Thumb_Raw1[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_FCAM_CAPT_2IN2],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}//port1=DIP_S14
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_PRM_H264_WIFI[] =
{
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_Capture_SRC[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN2_RAW2[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN2_RAW1[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN1_INA[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_Capture_SRC_2IN1_INB[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX2],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_Capture[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_Capture_Thumb[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_DSC_RCAM_CAPTURE],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_ANADEC_H264_WIFI[] =
{
    {
        &Component_RawS[RAWS_COMP_IDX],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_BAYER_Capture[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_SCD_BAYER_Capture_Thumb[] =
{
    {
        &Component_SCL0[SCL0_COMP_SCD_CAM],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_USBH_Capture_SRC[] =
{
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_DSC_USBH_H264_WIFI[] =
{
    {
        &Component_JPD[JPD_COMP_MJPEG_DEC],
        2,
        {MMP_FALSE, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE}
    },
};

#if 0
void _____Port_Script_ADAS_____(){}
#endif

COMPONENT_PORT_CFG Port_Config_Algorithm[] =
{
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_Algorithm_PCAM[] =
{
    {
        &Component_SCL1[SCL1_COMP_PRM_CAM],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_ADAS[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],
        0,
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};

COMPONENT_PORT_CFG Port_Config_MDTC[] =
{
    {
        &Component_DIP_Scale[DIP_S_COMP_VR_FCAM_ADAS],
        1,
        {MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE}
    },
};
