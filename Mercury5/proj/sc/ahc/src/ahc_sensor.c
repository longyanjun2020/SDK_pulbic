//==============================================================================
//
//  File        : AHC_Sensor.c
//  Description : AHC Sensor control function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ait_config.h"
#include "mmps_sensor.h"
#include "mmpf_sensor.h"
#include "ahc_sensor.h"
#include "isp_if.h"
#include "hdr_cfg.h"
#include "snr_cfg.h"
#include "MenuSetting.h"
#include "drv_ms_cus_sensor.h"

/*===========================================================================
 * Local variable
 *===========================================================================*/

static INT32    m_s32AhcPrmSnrPrevwMode     = AHC_SENSOR_MODE_AUTO;
static INT32    m_s32AhcPrmSnrCaptureMode   = AHC_SENSOR_MODE_AUTO;
static INT32    m_s32AhcAnaDecSnrMode       = AHC_SENSOR_MODE_AUTO;
static INT32    m_s32AhcYuvSnrMode          = AHC_SENSOR_MODE_AUTO;

static UINT8    m_u8AhcSnrFlipType[2]       = {0, 0};
static UINT8    m_u8AhcSnrDirStatus         = AHC_SNR_NORMAL;

const UINT16    gsAhcPrmSensor              = PRM_SENSOR;
const UINT16    gsAhcScdSensor              = SCD_SENSOR;

/*===========================================================================
 * Main body
 *===========================================================================*/

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_IsSnrInitialized
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_IsSnrInitialized(UINT8 u8SnrSel)
{
    return MMPS_Sensor_IsInitialized(u8SnrSel);
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_SetFlipDir
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_SetFlipDir(UINT8 u8SnrSel, AHC_SENSOR_FLIP_TYPE eFlipType)
{
    MMPS_Sensor_SetFlip(u8SnrSel, eFlipType);

    m_u8AhcSnrFlipType[u8SnrSel] = (UINT8)eFlipType;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_SetLightFreq
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_SetLightFreq(UINT8 ubSnrSel, AHC_SENSOR_DEBAND_MODE eMode)
{
    MMPS_Sensor_Set3AFunction(ubSnrSel, MMP_ISP_3A_FUNC_SET_AE_FLICKER_MODE, (MMP_SNR_DEBAND_MODE)eMode);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetScalInputWH
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_GetScalInputWH(UINT8 ubSnrSel, UINT16 u16Mode, UINT16* pu16Width, UINT16* pu16Height)
{
    MMP_ULONG ulWidth = 0, ulHeight = 0;

    if (u16Mode == SENSOR_DRIVER_MODE_NOT_SUUPORT) {
        *pu16Width = ulWidth;
        *pu16Height = ulHeight;
        return AHC_FALSE;
    }

    MMPS_Sensor_GetScalInputRes(ubSnrSel, u16Mode, &ulWidth, &ulHeight);

    *pu16Width = ulWidth;
    *pu16Height = ulHeight;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_SetSnrDirStatus
//  Description :
//------------------------------------------------------------------------------
void AHC_SNR_SetSnrDirStatus(UINT8 u8SNRState)
{
    m_u8AhcSnrDirStatus = u8SNRState;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetSnrDirStatus
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_SNR_GetSnrDirStatus(void)
{
    return m_u8AhcSnrDirStatus;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_PowerCtrl
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_PowerCtrl(AHC_BOOL bOn)
{
#if 0//def SENSOR_EN_GPIO
    if (SENSOR_EN_GPIO != MMP_PAD_MAX)
    {
        AHC_GPIO_ConfigPad(SENSOR_EN_GPIO, PAD_OUT_DRIVING(0));
        AHC_GPIO_SetOutputMode(SENSOR_EN_GPIO, AHC_TRUE);
        AHC_GPIO_SetData(SENSOR_EN_GPIO, (bOn ? SENSOR_EN_GPIO_ACT_MODE : !SENSOR_EN_GPIO_ACT_MODE));
    }
#endif

    return AHC_TRUE;
}

#if 0
void _____Prm_Sensor_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_PresetPrmSnrMode
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This API preset sensor mode for AHC usage.

 This function preset sensor mode for AHC usage. This APS is
 for select sensor mode before enter video preview or still
 capture preview.

 Parameters:

 @param[in] wMode          The sensor mode id. This is the
                           definition in sensor driver or in
                           ait_config.c .

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_SNR_PresetPrmSnrMode(INT16 wMode)
{
    UINT32 ulHdrEn = 0;

    switch(wMode) {
        case AHC_SENSOR_MODE_VGA_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_VGA_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_50P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_VGA_50P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_60P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_VGA_60P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_100P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_VGA_100P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_120P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_VGA_120P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_24P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_HD_24P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_HD_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_50P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_HD_50P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_60P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_HD_60P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_100P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_HD_100P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_120P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_HD_120P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_1600x900_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_1600x900_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_24P_RESOLUTION:
             m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_24P_RESOLUTION;
             break;
        case AHC_SENSOR_MODE_FULL_HD_25P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_25P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION_HDR:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION_HDR;
            break;
        case AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION_COMBINED_HDR:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION_COMBINED_HDR;
            break;
        case AHC_SENSOR_MODE_FULL_HD_50P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_50P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_60P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_FULL_HD_60P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_1440_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_1440_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_SUPER_HD_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_SUPER_HD_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_SUPER_HD_25P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_SUPER_HD_25P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_SUPER_HD_24P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_SUPER_HD_24P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_2D7K_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_2D7K_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_2D7K_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_2D7K_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4K2K_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4K2K_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4K2K_24P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4K2K_24P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4K2K_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4K2K_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_VGA_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_VGA_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_1D2M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_1D2M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_1D5M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_1D5M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_3M_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_3M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_3M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_3M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_5M_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_5M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_5M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_5M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_8M_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_8M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_8M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_8M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_10M_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_10M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_10M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_10M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_12M_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_12M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_12M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_12M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_14M_15P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_14M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_14M_30P_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_4TO3_14M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_PAL_25FPS:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_PAL_25P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_NTSC_30FPS:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_NTSC_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_BEST_CAMERA_PREVIEW_RESOLUTION:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_BEST_CAMERA_PREVIEW_RESOLUTION;
            break;
        default:
            m_s32AhcPrmSnrPrevwMode = SENSOR_DRIVER_MODE_NOT_SUUPORT;
            break;
    }

    if (m_s32AhcPrmSnrPrevwMode == SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION_HDR) {
        MMP_SetVidHDRType(CAM_TYPE_PRM, CUS_SNR_HDR_DCG);
    }
    else if (m_s32AhcPrmSnrPrevwMode == SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION_COMBINED_HDR) {
        MMP_SetVidHDRType(CAM_TYPE_PRM, CUS_SNR_COMBINED_HDR);
    }
    else {
        MMP_SetVidHDRType(CAM_TYPE_PRM, CUS_SNR_HDR_DISABLE);
    }

    if (m_s32AhcPrmSnrPrevwMode == SENSOR_DRIVER_MODE_NOT_SUUPORT) {
        AHC_DBG_ERR(1, ">>>>> AHC_SNR_PresetPrmSnrMode Error!!!:%d\r\n", wMode);
        while(1);
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetPresetPrmSnrMode
//  Description :
//------------------------------------------------------------------------------
INT16 AHC_SNR_GetPresetPrmSnrMode(void)
{
    return m_s32AhcPrmSnrPrevwMode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_PresetPrmCaptureSnrMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_PresetPrmCaptureSnrMode(INT16 wMode)
{
    switch(wMode) {
        case AHC_SENSOR_MODE_VGA_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_VGA_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_50P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_VGA_50P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_60P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_VGA_60P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_100P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_VGA_100P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_VGA_120P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_VGA_120P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_HD_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_50P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_HD_50P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_60P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_HD_60P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_100P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_HD_100P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_HD_120P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_HD_120P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_1600x900_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_1600x900_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_FULL_HD_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_25P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_FULL_HD_25P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_50P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_FULL_HD_50P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_1440_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_1440_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_SUPER_HD_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_SUPER_HD_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_FULL_HD_60P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_FULL_HD_60P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_2D7K_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_2D7K_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_2D7K_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_2D7K_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4K2K_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4K2K_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4K2K_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4K2K_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_VGA_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_VGA_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_1D2M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_1D2M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_1D5M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_1D5M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_3M_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_3M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_3M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_3M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_5M_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_5M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_5M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_5M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_8M_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_8M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_8M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_8M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_10M_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_10M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_10M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_10M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_12M_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_12M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_12M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_12M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_14M_15P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_14M_15P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_4TO3_14M_30P_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_4TO3_14M_30P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_BEST_CAMERA_CAPTURE_4TO3_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_BEST_CAMERA_CAPTURE_4TO3_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_BEST_CAMERA_CAPTURE_16TO9_RESOLUTION:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_BEST_CAMERA_CAPTURE_16TO9_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_PAL_25FPS:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_PAL_25P_RESOLUTION;
            break;
        case AHC_SENSOR_MODE_NTSC_30FPS:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_NTSC_30P_RESOLUTION;
            break;
        default:
            m_s32AhcPrmSnrCaptureMode = SENSOR_DRIVER_MODE_NOT_SUUPORT;
            break;
    }

    if (m_s32AhcPrmSnrCaptureMode == SENSOR_DRIVER_MODE_NOT_SUUPORT) {
        AHC_DBG_ERR(1, ">>>>> AHC_SNR_PresetPrmCaptureSnrMode Error!!!:%d\r\n", wMode);
        while(1);
    }

    MMPS_Sensor_SetCaptureMode(gsAhcPrmSensor, m_s32AhcPrmSnrCaptureMode);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetPresetPrmCaptureSnrMode
//  Description :
//------------------------------------------------------------------------------
INT16 AHC_SNR_GetPresetPrmCaptureSnrMode(void)
{
    return m_s32AhcPrmSnrCaptureMode;
}

#if 0
void _____AnaDec_Sensor_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetAnaDecSnrCnntStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_GetAnaDecSnrCnntStatus(void)
{
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSnrSrc = MMP_SNR_ANADEC_SRC_NO_READY;

    MMPS_Sensor_GetAnaDecSrcType(&eAnaDecSnrSrc);

    if ((eAnaDecSnrSrc == MMP_SNR_ANADEC_SRC_NO_READY) ||
        (eAnaDecSnrSrc == MMP_SNR_ANADEC_SRC_DISCNT)) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_PresetAnaDecSnrMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_PresetAnaDecSnrMode(INT32 i32SnrMode)
{
    switch (i32SnrMode) {
    case AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION:
        m_s32AhcAnaDecSnrMode = SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION;
        break;
    case AHC_SENSOR_MODE_HD_30P_RESOLUTION:
        m_s32AhcAnaDecSnrMode = SENSOR_DRIVER_MODE_HD_30P_RESOLUTION;
        break;
    case AHC_SENSOR_MODE_PAL_25FPS:
        m_s32AhcAnaDecSnrMode = SENSOR_DRIVER_MODE_PAL_25P_RESOLUTION;
        break;
    case AHC_SENSOR_MODE_NTSC_30FPS:
    default:
        m_s32AhcAnaDecSnrMode = SENSOR_DRIVER_MODE_NTSC_30P_RESOLUTION;
        break;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetPresetAnaDecSnrMode
//  Description :
//------------------------------------------------------------------------------
INT32 AHC_SNR_GetPresetAnaDecSnrMode(void)
{
    return m_s32AhcAnaDecSnrMode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_CheckAnaDecSrcType
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_CheckAnaDecSrcType(UINT8 u8UiMode, UINT8 u8SnrSel)
{
    AHC_BOOL                ahcRet = AHC_TRUE;
    UINT32                  u32Timeout = 50, u32KeepCnt = 0;
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSnrSrc = MMP_SNR_ANADEC_SRC_NO_READY;
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSnrSrcKeep = MMP_SNR_ANADEC_SRC_NO_READY;

    // Wait until source type ready.
    do {
        MMPS_Sensor_CheckAnaDecSrcType(u8SnrSel, &eAnaDecSnrSrc);

        if (MMP_SNR_ANADEC_SRC_NO_READY == eAnaDecSnrSrc) {
            u32KeepCnt = 0;
        }
        else {
            if (eAnaDecSnrSrcKeep != eAnaDecSnrSrc) {
                eAnaDecSnrSrcKeep = eAnaDecSnrSrc;
                u32KeepCnt = 0;
            }
            else {
                u32KeepCnt++;
            }
        }

        AHC_OS_Sleep(20);
    } while ((u32KeepCnt < SNR_R_CHECK_SIG_STABLE_COUNT) && (--u32Timeout > 0));

    if (u32Timeout == 0) {
        AHC_DBG_ERR(1, "AHC_SNR_CheckAnaDecSrcType TimeOut\r\n", eAnaDecSnrSrc);
        MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_TRUE);
        return AHC_FALSE;
    }

    AHC_DBG_MSG(1, "# AHC_SNR_CheckAnaDecSrcType %d\r\n", eAnaDecSnrSrc);

    if (u8SnrSel == PRM_SENSOR) {

        if (MMP_SNR_ANADEC_SRC_PAL == eAnaDecSnrSrc) {
            AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_PAL_25FPS);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetPrmSnrMode());
        }
        else if (MMP_SNR_ANADEC_SRC_NTSC == eAnaDecSnrSrc) {
            AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_NTSC_30FPS);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetPrmSnrMode());
        }
        else if (MMP_SNR_ANADEC_SRC_HD == eAnaDecSnrSrc) {
            AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetPrmSnrMode());
        }
        else if (MMP_SNR_ANADEC_SRC_FHD == eAnaDecSnrSrc) {
            AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetPrmSnrMode());
        }
        else {
            AHC_DBG_ERR(1, FG_RED("SNR0 check signal type TimeOut.\r\n"));
        }
    }
    else if (u8SnrSel == SCD_SENSOR) {

        if (MMP_SNR_ANADEC_SRC_PAL == eAnaDecSnrSrc) {
            AHC_SNR_PresetAnaDecSnrMode(AHC_SENSOR_MODE_PAL_25FPS);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetAnaDecSnrMode());
        }
        else if (MMP_SNR_ANADEC_SRC_NTSC == eAnaDecSnrSrc) {
            AHC_SNR_PresetAnaDecSnrMode(AHC_SENSOR_MODE_NTSC_30FPS);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetAnaDecSnrMode());
        }
        else if (MMP_SNR_ANADEC_SRC_HD == eAnaDecSnrSrc) {
            AHC_SNR_PresetAnaDecSnrMode(AHC_SENSOR_MODE_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetAnaDecSnrMode());
        }
        else if (MMP_SNR_ANADEC_SRC_FHD == eAnaDecSnrSrc) {
            AHC_SNR_PresetAnaDecSnrMode(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetAnaDecSnrMode());
        }
        else {
            AHC_DBG_ERR(1, FG_RED("SNR1 check signal type TimeOut.\r\n"));
        }
    }

    MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_TRUE);

    return ahcRet;
}

#if 0
void _____YUV_Sensor_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetYuvSnrCnntStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_GetYuvSnrCnntStatus(void)
{
    MMP_SNR_YUV_SRC_TYPE eYuvSnrSrc = MMP_SNR_YUV_SRC_DISCNT;

    MMPS_Sensor_GetYUVSnrSrcType(&eYuvSnrSrc);

    if ((MMP_SNR_YUV_SRC_DISCNT == eYuvSnrSrc)) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_PresetYuvSnrSrcType
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_PresetYuvSnrSrcType(UINT32 u32SrcType)
{
    switch (u32SrcType) {
    case AHC_SENSOR_MODE_HD_30P_RESOLUTION:
        m_s32AhcYuvSnrMode = SENSOR_DRIVER_MODE_HD_30P_RESOLUTION;
        break;
    default:
        m_s32AhcYuvSnrMode = SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION;
        break;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_GetPresetYuvSnrSrcType
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_SNR_GetPresetYuvSnrSrcType(void)
{
    return m_s32AhcYuvSnrMode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_CheckYUVSnrSrcType
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_CheckYUVSnrSrcType(UINT8 u8UiMode, UINT8 u8SnrSel)
{
    AHC_BOOL                ahcRet = AHC_TRUE;
    UINT32                  u32Timeout = 50;
    MMP_SNR_YUV_SRC_TYPE    eYuvSnrSrc = MMP_SNR_YUV_SRC_DISCNT;

    // Wait until YUV source type ready.
    do {
        MMPS_Sensor_GetYUVSnrSrcType(&eYuvSnrSrc);
        //MMPS_Sensor_CheckYUVSnrSrcType(u8SnrSel, &eYuvSnrSrc);

        if (MMP_SNR_YUV_SRC_DISCNT == eYuvSnrSrc) {
            AHC_OS_Sleep(20);
        }
        else {
            break;
        }
    } while ((MMP_SNR_YUV_SRC_DISCNT == eYuvSnrSrc) && (--u32Timeout > 0));

    if (u32Timeout == 0) {
        return AHC_FALSE;
    }

    if (u8SnrSel == PRM_SENSOR) {

        switch(eYuvSnrSrc) {
        case MMP_SNR_YUV_SRC_HD:
            AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetPrmSnrMode());
            break;
        case MMP_SNR_YUV_SRC_FHD:
            AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetPrmSnrMode());
            break;
        default:
            AHC_DBG_ERR(1, FG_RED("SNR0 check signal type TimeOut.\r\n"));
            break;
        }
    }
    else if (u8SnrSel == SCD_SENSOR) {

        switch(eYuvSnrSrc) {
        case MMP_SNR_YUV_SRC_HD:
            AHC_SNR_PresetYuvSnrSrcType(AHC_SENSOR_MODE_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetYuvSnrSrcType());
            break;
        case MMP_SNR_YUV_SRC_FHD:
            AHC_SNR_PresetYuvSnrSrcType(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION);
            MMPS_Sensor_SetPreviewMode(u8SnrSel, AHC_SNR_GetPresetYuvSnrSrcType());
            break;
        default:
            AHC_DBG_ERR(1, FG_RED("SNR1 check signal type TimeOut.\r\n"));
            break;
        }
    }

    //MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_TRUE);

    return ahcRet;
}

#if 0
void _____Check_Camera_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_CheckPrmCamConnectSts
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_CheckPrmCamConnectSts(void)
{
    AHC_BOOL bPrmCamConnected = AHC_FALSE;

    if (CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) {
        if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus()) {
            bPrmCamConnected = AHC_TRUE;
        }
    }
    else if (CAM_CHECK_PRM(PRM_CAM_YUV_SENSOR)) {
        if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus()) {
            bPrmCamConnected = AHC_TRUE;
        }
    }
    else if (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR)) {
        bPrmCamConnected = AHC_TRUE;
    }

    return bPrmCamConnected;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SNR_CheckScdCamConnectSts
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SNR_CheckScdCamConnectSts(void)
{
    AHC_BOOL bScdCamConnected = AHC_FALSE;

    if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
        if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus()) {
            bScdCamConnected = AHC_TRUE;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus()) {
            bScdCamConnected = AHC_TRUE;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        bScdCamConnected = AHC_TRUE;
    }

    return bScdCamConnected;
}
