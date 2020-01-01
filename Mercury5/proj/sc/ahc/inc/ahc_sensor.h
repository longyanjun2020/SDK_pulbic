//==============================================================================
//
//  File        : ahc_sensor.h
//  Description : INCLUDE File for the AHC sensor control function porting.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_SENSOR_H_
#define _AHC_SENSOR_H_

/*============================================================================
 * Include files
 *============================================================================*/

#include "ahc_common.h"

/*============================================================================
 * Enum define
 *============================================================================*/

typedef enum _AHC_SENSOR_MODE
{
    // Index 0
    AHC_SENSOR_MODE_VGA_30P_RESOLUTION,         // 640*360 30P
    AHC_SENSOR_MODE_VGA_50P_RESOLUTION,         // 640*360 50P
    AHC_SENSOR_MODE_VGA_60P_RESOLUTION,         // 640*360 60P
    AHC_SENSOR_MODE_VGA_100P_RESOLUTION,        // 640*360 100P
    AHC_SENSOR_MODE_VGA_120P_RESOLUTION,        // 640*360 120P

    // Index 5
    AHC_SENSOR_MODE_HD_24P_RESOLUTION,          // 1280*720 24P
    AHC_SENSOR_MODE_HD_30P_RESOLUTION,          // 1280*720 30P
    AHC_SENSOR_MODE_HD_50P_RESOLUTION,          // 1280*720 50P
    AHC_SENSOR_MODE_HD_60P_RESOLUTION,          // 1280*720 60P
    AHC_SENSOR_MODE_HD_100P_RESOLUTION,         // 1280*720 100P

    // Index 10
    AHC_SENSOR_MODE_HD_120P_RESOLUTION,         // 1280*720 120P
    AHC_SENSOR_MODE_1600x900_30P_RESOLUTION,    // 1600*900 30P
    AHC_SENSOR_MODE_FULL_HD_15P_RESOLUTION,     // 1920*1080 15P
    AHC_SENSOR_MODE_FULL_HD_24P_RESOLUTION,     // 1920*1080 24P
    AHC_SENSOR_MODE_FULL_HD_25P_RESOLUTION,     // 1920*1080 25P

    // Index 15
    AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION,     // 1920*1080 30P
    AHC_SENSOR_MODE_FULL_HD_50P_RESOLUTION,     // 1920*1080 50P
    AHC_SENSOR_MODE_FULL_HD_60P_RESOLUTION,     // 1920*1080 60P
    AHC_SENSOR_MODE_SUPER_HD_30P_RESOLUTION,    // 2304x1296 30P
    AHC_SENSOR_MODE_SUPER_HD_25P_RESOLUTION,    // 2304x1296 25P

    // Index 20
    AHC_SENSOR_MODE_SUPER_HD_24P_RESOLUTION,    // 2304x1296 24P
    AHC_SENSOR_MODE_1440_30P_RESOLUTION,        // 2560x1440 30P
    AHC_SENSOR_MODE_2D7K_15P_RESOLUTION,        // 2704*1524 15P
    AHC_SENSOR_MODE_2D7K_30P_RESOLUTION,        // 2704*1524 30P
    AHC_SENSOR_MODE_4K2K_15P_RESOLUTION,        // 3840*2160 15P

    //Index 25
    AHC_SENSOR_MODE_4K2K_30P_RESOLUTION,        // 3840*2160 30P
    AHC_SENSOR_MODE_4TO3_VGA_30P_RESOLUTION,    // 640*480   30P
    AHC_SENSOR_MODE_4TO3_1D2M_30P_RESOLUTION,   // 1280*960  30P
    AHC_SENSOR_MODE_4TO3_1D5M_30P_RESOLUTION,   // 1440*1080 30P
    AHC_SENSOR_MODE_4TO3_3M_15P_RESOLUTION,     // 2048*1536 15P

    //Index 30
    AHC_SENSOR_MODE_4TO3_3M_30P_RESOLUTION,     // 2048*1536 30P
    AHC_SENSOR_MODE_4TO3_5M_15P_RESOLUTION,     // 2560*1920 15P
    AHC_SENSOR_MODE_4TO3_5M_30P_RESOLUTION,     // 2560*1920 30P
    AHC_SENSOR_MODE_4TO3_8M_15P_RESOLUTION,     // 3264*2448 15P
    AHC_SENSOR_MODE_4TO3_8M_30P_RESOLUTION,     // 3264*2448 30P

    //Index 35
    AHC_SENSOR_MODE_4TO3_10M_15P_RESOLUTION,    // 3648*2736 15P
    AHC_SENSOR_MODE_4TO3_10M_30P_RESOLUTION,    // 3648*2736 30P
    AHC_SENSOR_MODE_4TO3_12M_15P_RESOLUTION,    // 4032*3024 15P
    AHC_SENSOR_MODE_4TO3_12M_30P_RESOLUTION,    // 4032*3024 30P
    AHC_SENSOR_MODE_4TO3_14M_15P_RESOLUTION,    // 4352*3264 15P

    //Index 40
    AHC_SENSOR_MODE_4TO3_14M_30P_RESOLUTION,    // 4352*3264 30P
    AHC_SENSOR_MODE_4K2K_24P_RESOLUTION,        // 3200*1800 24P

    ///////////////////////////////////////////////////////////////////////
    AHC_SENSOR_MODE_BEST_CAMERA_PREVIEW_RESOLUTION,
    AHC_SENSOR_MODE_BEST_CAMERA_CAPTURE_4TO3_RESOLUTION,
    AHC_SENSOR_MODE_BEST_CAMERA_CAPTURE_16TO9_RESOLUTION,
    AHC_SENSOR_MODE_DEFAULT_PCCAM_RESOLUTION,

    AHC_SENSOR_MODE_PAL_25FPS,
    AHC_SENSOR_MODE_NTSC_30FPS,

    AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION_HDR, // 1920*1080 30P HDR
    AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION_COMBINED_HDR, // 1920*1080 30P Combined mode HDR

    AHC_SENSOR_MODE_MAX,
    AHC_SENSOR_MODE_AUTO = 0xFFFF
} AHC_SENSOR_MODE;

typedef enum _AHC_SENSOR_DEBAND_MODE
{
    AHC_SENSOR_DSC_DEBAND_60HZ = 0,
    AHC_SENSOR_DSC_DEBAND_50HZ,
    AHC_SENSOR_VIDEO_DEBAND_60HZ,
    AHC_SENSOR_VIDEO_DEBAND_50HZ
} AHC_SENSOR_DEBAND_MODE;

typedef enum _AHC_SENSOR_FLIP_TYPE
{
    AHC_SENSOR_NO_FLIP = 0,
    AHC_SENSOR_COLUMN_FLIP,
    AHC_SENSOR_ROW_FLIP,
    AHC_SENSOR_COLROW_FLIP
} AHC_SENSOR_FLIP_TYPE;

typedef enum _AHC_SNR_STATUS
{
    AHC_SNR_NORMAL = 0,
    AHC_SNR_REVERSE,
    AHC_SNR_NOFLIP
} AHC_SNR_STATUS;

/*============================================================================
 * Extern Variable
 *============================================================================*/

extern const UINT16 gsAhcPrmSensor;
extern const UINT16 gsAhcScdSensor;

/*============================================================================
 * Function prototype
 *============================================================================*/

AHC_BOOL    AHC_SNR_IsSnrInitialized(UINT8 u8SnrSel);
AHC_BOOL    AHC_SNR_SetFlipDir(UINT8 u8SnrSel, AHC_SENSOR_FLIP_TYPE eFlipType);
AHC_BOOL    AHC_SNR_SetLightFreq(UINT8 ubSnrSel, AHC_SENSOR_DEBAND_MODE eMode);
AHC_BOOL    AHC_SNR_GetScalInputWH(UINT8 u8SnrSel, UINT16 u16Mode, UINT16* pu16Width, UINT16* pu16Height);
void        AHC_SNR_SetSnrDirStatus(UINT8 u8SNRState);
UINT8       AHC_SNR_GetSnrDirStatus(void);
AHC_BOOL    AHC_SNR_PowerCtrl(AHC_BOOL bOn);

AHC_BOOL    AHC_SNR_PresetPrmSnrMode(INT16 wMode);
INT16       AHC_SNR_GetPresetPrmSnrMode(void);
AHC_BOOL    AHC_SNR_PresetPrmCaptureSnrMode(INT16 wMode);
INT16       AHC_SNR_GetPresetPrmCaptureSnrMode(void);

AHC_BOOL    AHC_SNR_GetAnaDecSnrCnntStatus(void);
AHC_BOOL    AHC_SNR_PresetAnaDecSnrMode(INT32 i32SnrMode);
INT32       AHC_SNR_GetPresetAnaDecSnrMode(void);
AHC_BOOL    AHC_SNR_CheckAnaDecSrcType(UINT8 u8UiMode, UINT8 u8SnrSel);

AHC_BOOL    AHC_SNR_GetYuvSnrCnntStatus(void);
AHC_BOOL    AHC_SNR_PresetYuvSnrSrcType(UINT32 u32SrcType);
UINT32      AHC_SNR_GetPresetYuvSnrSrcType(void);
AHC_BOOL    AHC_SNR_CheckYUVSnrSrcType(UINT8 u8UiMode, UINT8 u8SnrSel);

AHC_BOOL    AHC_SNR_CheckPrmCamConnectSts(void);
AHC_BOOL    AHC_SNR_CheckScdCamConnectSts(void);

#endif //_AHC_SENSOR_H_
