/**
  @file ait_config.c
  @brief It contains the configurations need to be ported to the customer platform.
  @author Rogers

  @version
- 1.0 Original version
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "ait_config.h"
#include "snr_cfg.h"
#include "dram_cfg.h"
#include "mmps_system.h"
#include "mmps_dsc.h"
#include "mmps_display.h"
#include "mmps_vidplay.h"
#include "mmps_3gprecd.h"
#include "lcd_common.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define QTABLE_NUM          (3)

#define LCD_MODEL_RATIO_X               (16)
#define LCD_MODEL_RATIO_Y               (9)

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static const MMP_UBYTE Q_table[QTABLE_NUM][128] =
{
    // High quality
    0x08,0x06,0x06,0x06,0x06,0x06,0x08,0x08,
    0x08,0x08,0x0c,0x08,0x06,0x08,0x0c,0x0e,
    0x0a,0x08,0x08,0x0a,0x0e,0x10,0x0c,0x0c,
    0x0e,0x0c,0x0c,0x10,0x10,0x10,0x12,0x12,
    0x12,0x12,0x10,0x14,0x14,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,

    0x08,0x0a,0x0a,0x10,0x0e,0x10,0x14,0x14,
    0x14,0x14,0x20,0x14,0x14,0x14,0x20,0x20,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    //Normal quality
    0x09,0x0a,0x0a,0x0a,0x0a,0x0a,0x0c,0x0c,
    0x0c,0x0c,0x10,0x0c,0x0a,0x0a,0x10,0x16,
    0x10,0x0c,0x0c,0x10,0x16,0x18,0x10,0x10,
    0x16,0x10,0x10,0x18,0x18,0x18,0x1c,0x1c,
    0x1c,0x1c,0x18,0x20,0x20,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,

    0x0a,0x10,0x10,0x18,0x16,0x18,0x20,0x20,
    0x20,0x20,0x28,0x20,0x20,0x20,0x28,0x28,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    //Low quality
    0x0b,0x0c,0x0c,0x0c,0x0c,0x0c,0x10,0x10,
    0x10,0x10,0x14,0x10,0x0c,0x0c,0x14,0x1a,
    0x14,0x10,0x10,0x14,0x1a,0x1c,0x14,0x14,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
    0x28,0x28,0x28,0x28,0x28,0x28,0x28,0x28,
    0x28,0x28,0x28,0x28,0x28,0x28,0x28,0x28,
    0x28,0x28,0x28,0x28,0x28,0x28,0x28,0x28,

    0x0c,0x12,0x12,0x1a,0x1a,0x1c,0x24,0x24,
    0x24,0x24,0x2c,0x24,0x24,0x24,0x2c,0x2c,
    0x2c,0x2c,0x2c,0x2c,0x2c,0x2c,0x2c,0x2c,
    0x2c,0x2c,0x2c,0x2c,0x2c,0x2c,0x2c,0x2c,
    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
};

#if (AUDIO_SET_DB == 0x0)
static const MMP_UBYTE ubAudOutVol_HP_table[31][3] =
{
    /* 0*-  mute*/ { 0,0x00,0x00}, /* 1*-49.5dB*/ {10,0x3F,0xAA}, /* 2*-48.0dB*/ {11,0x3F,0xAA}, /* 3*-46.5dB*/ {12,0x3F,0xAA}, /* 4*-45.0dB*/ {13,0x3F,0xAA},
    /* 5*-43.5dB*/ {14,0x3F,0xAA}, /* 6*-42.0dB*/ {15,0x3F,0xAA}, /* 7*-40.5dB*/ {16,0x3F,0xAA}, /* 8*-39.0dB*/ {17,0x3F,0xAA}, /* 9*-37.5dB*/ {18,0x3F,0xAA},
    /*10*-36.0dB*/ {19,0x3F,0xAA}, /*11*-34.5dB*/ {20,0x3F,0xAA}, /*12*-33.0dB*/ {21,0x3F,0xAA}, /*13*-31.5dB*/ {22,0x3F,0xAA}, /*14*-30.0dB*/ {23,0x3F,0xAA},
    /*15*-28.5dB*/ {24,0x3F,0xAA}, /*16*-27.0dB*/ {25,0x3F,0xAA}, /*17*-25.5dB*/ {26,0x3F,0xAA}, /*18*-24.0dB*/ {27,0x3F,0xAA}, /*19*-22.5dB*/ {28,0x3F,0xAA},
    /*20*-21.0dB*/ {29,0x3F,0xAA}, /*21*-19.5dB*/ {30,0x3F,0xAA}, /*22*-18.0dB*/ {31,0x3F,0xAA}, /*23*-16.5dB*/ {32,0x3F,0xAA}, /*24*-15.0dB*/ {33,0x3F,0xAA},
    /*25*-13.5dB*/ {34,0x3F,0xAA}, /*26*-12.0dB*/ {35,0x3F,0xAA}, /*27*-10.5dB*/ {36,0x3F,0xAA}, /*28*- 9  dB*/ {37,0x3F,0xAA}, /*29*- 7.5dB*/ {38,0x3F,0xAA},
    /*30*- 6  dB*/ {39,0x3F,0xAA},
};

static const MMP_UBYTE ubAudOutVol_Line_table[31][2] =
{
    /* 0*-  Mute*/ { 0,0x00}, /* 1*-45.0dB*/ { 9,0x3F}, /* 2*-43.5dB*/ {10,0x3F}, /* 3*-42.0dB*/ {11,0x3F}, /* 4*-40.5dB*/ {12,0x3F},
    /* 5*-39.0dB*/ {13,0x3F}, /* 6*-37.5dB*/ {14,0x3F}, /* 7*-36.0dB*/ {15,0x3F}, /* 8*-34.5dB*/ {16,0x3F}, /* 9*-33.0dB*/ {17,0x3F},
    /*10*-31.5dB*/ {18,0x3F}, /*11*-30.0dB*/ {19,0x3F}, /*12*-28.5dB*/ {20,0x3F}, /*13*-27.0dB*/ {21,0x3F}, /*14*-25.5dB*/ {22,0x3F},
    /*15*-24.0dB*/ {23,0x3F}, /*16*-22.5dB*/ {24,0x3F}, /*17*-21.0dB*/ {25,0x3F}, /*18*-19.5dB*/ {26,0x3F}, /*19*-18.0dB*/ {27,0x3F},
    /*20*-16.5dB*/ {28,0x3F}, /*21*-15.0dB*/ {29,0x3F}, /*22*-13.5dB*/ {30,0x3F}, /*23*-12.0dB*/ {31,0x3F}, /*24*-10.5dB*/ {32,0x3F},
    /*25*- 9.0dB*/ {33,0x3F}, /*26*- 7.5dB*/ {34,0x3F}, /*27*- 6.0dB*/ {35,0x3F}, /*28*- 4.5dB*/ {36,0x3F}, /*29*- 3.0dB*/ {37,0x3F},
    /*30*- 1.5dB*/ {38,0x3F},
};
#else
static const MMP_UBYTE ubAudOutVol_HP_table[31][3] =
{
    /* 0*-  mute*/ { 0,0x00,0x00}, /* 1*-49.5dB*/ {10,0x3F,0xAA}, /* 2*-48.0dB*/ {11,0x3F,0xAA}, /* 3*-46.5dB*/ {12,0x3F,0xAA}, /* 4*-45.0dB*/ {13,0x3F,0xAA},
    /* 5*-43.5dB*/ {14,0x3F,0xAA}, /* 6*-42.0dB*/ {15,0x3F,0xAA}, /* 7*-40.5dB*/ {16,0x3F,0xAA}, /* 8*-39.0dB*/ {17,0x3F,0xAA}, /* 9*-37.5dB*/ {18,0x3F,0xAA},
    /*10*-36.0dB*/ {19,0x3F,0xAA}, /*11*-34.5dB*/ {20,0x3F,0xAA}, /*12*-33.0dB*/ {21,0x3F,0xAA}, /*13*-31.5dB*/ {22,0x3F,0xAA}, /*14*-30.0dB*/ {23,0x3F,0xAA},
    /*15*-28.5dB*/ {24,0x3F,0xAA}, /*16*-27.0dB*/ {25,0x3F,0xAA}, /*17*-25.5dB*/ {26,0x3F,0xAA}, /*18*-24.0dB*/ {27,0x3F,0xAA}, /*19*-22.5dB*/ {28,0x3F,0xAA},
    /*20*-21.0dB*/ {29,0x3F,0xAA}, /*21*-19.5dB*/ {30,0x3F,0xAA}, /*22*-18.0dB*/ {31,0x3F,0xAA}, /*23*-16.5dB*/ {32,0x3F,0xAA}, /*24*-15.0dB*/ {33,0x3F,0xAA},
    /*25*-13.5dB*/ {34,0x3F,0xAA}, /*26*-12.0dB*/ {35,0x3F,0xAA}, /*27*-10.5dB*/ {36,0x3F,0xAA}, /*28*- 9  dB*/ {37,0x3F,0xAA}, /*29*- 7.5dB*/ {38,0x3F,0xAA},
    /*30*- 6  dB*/ {39,0x3F,0xAA},
};

static const MMP_UBYTE ubAudOutVol_Line_table[31][2] =
{
    /* 0*-  Mute*/ { 0,0x00}, /* 1*-29.0dB*/ {67,0x3F}, /* 2*-28.0dB*/ {68,0x3F}, /* 3*-27.0dB*/ {69,0x3F}, /* 4*-26.0dB*/ {70,0x3F},
    /* 5*-25.0dB*/ {71,0x3F}, /* 6*-24.0dB*/ {72,0x3F}, /* 7*-23.0dB*/ {73,0x3F}, /* 8*-22.0dB*/ {74,0x3F}, /* 9*-21.0dB*/ {75,0x3F},
    /*10*-20.0dB*/ {76,0x3F}, /*11*-19.0dB*/ {77,0x3F}, /*12*-18.0dB*/ {78,0x3F}, /*13*-17.0dB*/ {79,0x3F}, /*14*-16.0dB*/ {80,0x3F},
    /*15*-15.0dB*/ {81,0x3F}, /*16*-14.0dB*/ {82,0x3F}, /*17*-13.0dB*/ {83,0x3F}, /*18*-12.0dB*/ {84,0x3F}, /*19*-11.0dB*/ {85,0x3F},
    /*20*-10.0dB*/ {86,0x3F}, /*21*- 9.0dB*/ {87,0x3F}, /*22*- 8.0dB*/ {88,0x3F}, /*23*- 7.0dB*/ {89,0x3F}, /*24*- 6.0dB*/ {90,0x3F},
    /*25*- 5.0dB*/ {91,0x3F}, /*26*- 4.0dB*/ {92,0x3F}, /*27*- 3.0dB*/ {93,0x3F}, /*28*- 2.0dB*/ {94,0x3F}, /*29*- 1.0dB*/ {95,0x3F},
    /*30*-   0dB*/ {96,0x3F},
};
#endif

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

extern MMP_DISPLAY_INIT_FUNC MMPC_Display_InitMainLCD;
extern MMP_DISPLAY_INIT_FUNC MMPC_Display_ReinitMainLCD;

//------------------------------------------------------------------------------
//  Function    : MMPC_DSC_InitConfig
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPC_DSC_InitConfig(void)
{
#if !defined(MBOOT_FW)
    MMP_ULONG i, j;
    MMPS_DSC_CONFIG *pDscConfig = MMPS_DSC_GetConfig();

    /* DSC Encode Mode parameter */
    if (QTABLE_NUM > DSC_QTABLE_MAX_NUM) {
        PRINTF("ERROR: QTABLE_NUM > DSC_QTABLE_MAX_NUM\r\n");
    }
    else {
        for (i = 0; i < QTABLE_NUM; i++) {
            for (j = 0; j < 128; j++) {
                pDscConfig->encParams.ubDscQtable[i][j] = Q_table[i][j];
            }
        }
    }

    pDscConfig->encParams.ulMaxThumbnailSize    = 0x5000;       // 20KB
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    pDscConfig->encParams.ulMaxLargeThumbSize   = 512 * 1024;   // 512KB
    #endif

    /* For JPEG decoder */
    pDscConfig->decParams.ulExifWorkingBufSize      = 0x40000;
    pDscConfig->decParams.ulDscDecMaxCompBufSize    = 3 * 1024 * 1024;
    pDscConfig->decParams.ulDscDecMaxInbufSize      = 1 * 1024;
#endif
    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : MMPC_3gpRecd_InitConfig
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPC_3gpRecd_InitConfig(void)
{
#if !defined(MBOOT_FW)
    #define VR_BITRATE_SHD30P_SUPER     (18000000)
    #define VR_BITRATE_SHD30P_FINE      (12000000)
    #define VR_BITRATE_FHD60P_SUPER     (24000000)
    #define VR_BITRATE_FHD60P_FINE      (16000000)
    #define VR_BITRATE_FHD30P_SUPER     (12000000)
    #define VR_BITRATE_FHD30P_FINE      ( 8000000)
    #define VR_BITRATE_HD30P_SUPER      ( 6000000)
    #define VR_BITRATE_HD30P_FINE       ( 4000000)
    #define VR_BITRATE_HD60P_SUPER      (12000000)
    #define VR_BITRATE_HD60P_FINE       ( 7200000)
    #define VR_BITRATE_VGA30P_SUPER     ( 1200000)
    #define VR_BITRATE_VGA30P_FINE      ( 1000000)

    #define AHC_VIDEO_BITRATE_SHD30FPS_SUPPERFINE   (VR_BITRATE_SHD30P_SUPER)   //24000000
    #define AHC_VIDEO_BITRATE_SHD30FPS_FINE         (VR_BITRATE_SHD30P_FINE)    // 8000000
    #define AHC_VIDEO_BITRATE_FHD60FPS_SUPPERFINE   (VR_BITRATE_FHD60P_SUPER)   //32000000
    #define AHC_VIDEO_BITRATE_FHD60FPS_FINE         (VR_BITRATE_FHD60P_FINE)    //16000000
    #define AHC_VIDEO_BITRATE_FHD30FPS_SUPPERFINE   (VR_BITRATE_FHD30P_SUPER)   //16000000
    #define AHC_VIDEO_BITRATE_FHD30FPS_FINE         (VR_BITRATE_FHD30P_FINE)    // 8000000
    #define AHC_VIDEO_BITRATE_HD30FPS_SUPPERFINE    (VR_BITRATE_HD30P_SUPER)    // 7200000
    #define AHC_VIDEO_BITRATE_HD30FPS_FINE          (VR_BITRATE_HD30P_FINE)     // 4000000
    #define AHC_VIDEO_BITRATE_HD60FPS_SUPPERFINE    (VR_BITRATE_HD60P_SUPER)    //12000000
    #define AHC_VIDEO_BITRATE_HD60FPS_FINE          (VR_BITRATE_HD60P_FINE)     // 7200000
    #define AHC_VIDEO_BITRATE_VGA30FPS_SUPPERFINE   (VR_BITRATE_VGA30P_SUPER)   //12000000
    #define AHC_VIDEO_BITRATE_VGA30FPS_FINE         (VR_BITRATE_VGA30P_FINE)    //10000000
    #define AHC_VIDEO_BITRATE_900P30FPS_SUPPERFINE  (VR_BITRATE_900P30FPS_SUPER)
    #define AHC_VIDEO_BITRATE_900P30FPS_FINE        (VR_BITRATE_900P30FPS_FINE)
    #define AHC_VIDEO_BITRATE_960P30FPS_SUPPERFINE  (VR_BITRATE_960P30FPS_SUPER)
    #define AHC_VIDEO_BITRATE_960P30FPS_FINE        (VR_BITRATE_960P30FPS_FINE)

    MMPS_3GPRECD_PRESET_CFG *pVideoConfig = MMPS_3GPRECD_GetPresetCfg();
    int idx = 0;

    MEMSET(pVideoConfig, 0, sizeof(MMPS_3GPRECD_PRESET_CFG)); // Need to reinit~ sometime. such as change rearcam type.

    // Video encode setting : Encode Width / Height
    pVideoConfig->usEncWidth[VIDRECD_RESOL_640x368]         = 640;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_640x368]        = 368;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_640x480]         = 640;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_640x480]        = 480;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_720x480]         = 720;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_720x480]        = 480;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_848x480]         = 840;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_848x480]        = 480;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_960x720]         = 960;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_960x720]        = 720;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_1280x720]        = 1280;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_1280x720]       = 720;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_1472x736]        = 1472;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_1472x736]       = 736;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_1440x1088]       = 1440;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_1440x1088]      = 1088;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_1920x1088]       = 1920;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_1920x1088]      = 1080;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_2304x1296]       = 2304;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_2304x1296]      = 1296;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_2560x1440]       = 2560;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_2560x1440]      = 1440;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_2704x1536]       = 2704;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_2704x1536]      = 1536;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_3200x1808]       = 3200;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_3200x1808]      = 1808;
    pVideoConfig->usEncWidth[VIDRECD_RESOL_3840x2160]       = 3840;
    pVideoConfig->usEncHeight[VIDRECD_RESOL_3840x2160]      = 2160;

    // Video encode setting : Bitrate
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_640x368][VIDRECD_QUALITY_LOW]     = 1920000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_640x368][VIDRECD_QUALITY_MID]     = 2880000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_640x368][VIDRECD_QUALITY_HIGH]    = 3840000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_640x368][VIDRECD_QUALITY_LOW]     = 3840000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_640x368][VIDRECD_QUALITY_MID]     = 5760000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_640x368][VIDRECD_QUALITY_HIGH]    = 7680000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_640x480][VIDRECD_QUALITY_LOW]     = 1920000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_640x480][VIDRECD_QUALITY_MID]     = AHC_VIDEO_BITRATE_VGA30FPS_FINE;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_640x480][VIDRECD_QUALITY_HIGH]    = AHC_VIDEO_BITRATE_VGA30FPS_SUPPERFINE;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_640x480][VIDRECD_QUALITY_LOW]     = 3840000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_640x480][VIDRECD_QUALITY_MID]     = 5760000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_640x480][VIDRECD_QUALITY_HIGH]    = 7680000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_720x480][VIDRECD_QUALITY_LOW]     = 2000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_720x480][VIDRECD_QUALITY_MID]     = 3000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_720x480][VIDRECD_QUALITY_HIGH]    = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_720x480][VIDRECD_QUALITY_LOW]     = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_720x480][VIDRECD_QUALITY_MID]     = 6000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_720x480][VIDRECD_QUALITY_HIGH]    = 8000000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_848x480][VIDRECD_QUALITY_LOW]     = 2000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_848x480][VIDRECD_QUALITY_MID]     = 3000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_848x480][VIDRECD_QUALITY_HIGH]    = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_848x480][VIDRECD_QUALITY_LOW]     = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_848x480][VIDRECD_QUALITY_MID]     = 6000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_848x480][VIDRECD_QUALITY_HIGH]    = 8000000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_960x720][VIDRECD_QUALITY_LOW]     = 2000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_960x720][VIDRECD_QUALITY_MID]     = 3000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_960x720][VIDRECD_QUALITY_HIGH]    = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_960x720][VIDRECD_QUALITY_LOW]     = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_960x720][VIDRECD_QUALITY_MID]     = 6000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_960x720][VIDRECD_QUALITY_HIGH]    = 8000000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1280x720][VIDRECD_QUALITY_LOW]    = 2000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1280x720][VIDRECD_QUALITY_MID]    = AHC_VIDEO_BITRATE_HD30FPS_FINE;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1280x720][VIDRECD_QUALITY_HIGH]   = AHC_VIDEO_BITRATE_HD30FPS_SUPPERFINE;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1280x720][VIDRECD_QUALITY_LOW]    = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1280x720][VIDRECD_QUALITY_MID]    = AHC_VIDEO_BITRATE_HD60FPS_FINE;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1280x720][VIDRECD_QUALITY_HIGH]   = AHC_VIDEO_BITRATE_HD60FPS_SUPPERFINE;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1472x736][VIDRECD_QUALITY_LOW]    = 4000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1472x736][VIDRECD_QUALITY_MID]    = 7000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1472x736][VIDRECD_QUALITY_HIGH]   = 11000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1472x736][VIDRECD_QUALITY_LOW]    = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1472x736][VIDRECD_QUALITY_MID]    = 7200000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1472x736][VIDRECD_QUALITY_HIGH]   = 12000000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1440x1088][VIDRECD_QUALITY_LOW]   = 4000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1440x1088][VIDRECD_QUALITY_MID]   = 11440000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1440x1088][VIDRECD_QUALITY_HIGH]  = 22880000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1440x1088][VIDRECD_QUALITY_LOW]   = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1440x1088][VIDRECD_QUALITY_MID]   = 11440000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1440x1088][VIDRECD_QUALITY_HIGH]  = 22880000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1920x1088][VIDRECD_QUALITY_LOW]   = 4000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1920x1088][VIDRECD_QUALITY_MID]   = AHC_VIDEO_BITRATE_FHD30FPS_FINE;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_1920x1088][VIDRECD_QUALITY_HIGH]  = AHC_VIDEO_BITRATE_FHD30FPS_SUPPERFINE;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1920x1088][VIDRECD_QUALITY_LOW]   = 8000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1920x1088][VIDRECD_QUALITY_MID]   = AHC_VIDEO_BITRATE_FHD60FPS_FINE;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_1920x1088][VIDRECD_QUALITY_HIGH]  = AHC_VIDEO_BITRATE_FHD60FPS_SUPPERFINE;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2304x1296][VIDRECD_QUALITY_LOW]   = 5720000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2304x1296][VIDRECD_QUALITY_MID]   = AHC_VIDEO_BITRATE_SHD30FPS_FINE;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2304x1296][VIDRECD_QUALITY_HIGH]  = AHC_VIDEO_BITRATE_SHD30FPS_SUPPERFINE;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2304x1296][VIDRECD_QUALITY_LOW]   = 5720000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2304x1296][VIDRECD_QUALITY_MID]   = 11440000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2304x1296][VIDRECD_QUALITY_HIGH]  = 22880000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2560x1440][VIDRECD_QUALITY_LOW]   = 5720000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2560x1440][VIDRECD_QUALITY_MID]   = AHC_VIDEO_BITRATE_SHD30FPS_FINE;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2560x1440][VIDRECD_QUALITY_HIGH]  = AHC_VIDEO_BITRATE_SHD30FPS_SUPPERFINE;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2560x1440][VIDRECD_QUALITY_LOW]   = 5720000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2560x1440][VIDRECD_QUALITY_MID]   = 11440000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2560x1440][VIDRECD_QUALITY_HIGH]  = 22880000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2704x1536][VIDRECD_QUALITY_LOW]   = 4000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2704x1536][VIDRECD_QUALITY_MID]   = 8000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_2704x1536][VIDRECD_QUALITY_HIGH]  = 16000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2704x1536][VIDRECD_QUALITY_LOW]   = 8000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2704x1536][VIDRECD_QUALITY_MID]   = 16000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_2704x1536][VIDRECD_QUALITY_HIGH]  = 32000000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_3200x1808][VIDRECD_QUALITY_LOW]   = 4000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_3200x1808][VIDRECD_QUALITY_MID]   = 8000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_3200x1808][VIDRECD_QUALITY_HIGH]  = 16000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_3200x1808][VIDRECD_QUALITY_LOW]   = 8000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_3200x1808][VIDRECD_QUALITY_MID]   = 16000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_3200x1808][VIDRECD_QUALITY_HIGH]  = 32000000;

    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_3840x2160][VIDRECD_QUALITY_LOW]   = 4000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_3840x2160][VIDRECD_QUALITY_MID]   = 8000000;
    pVideoConfig->ulFps30BitrateMap[VIDRECD_RESOL_3840x2160][VIDRECD_QUALITY_HIGH]  = 16000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_3840x2160][VIDRECD_QUALITY_LOW]   = 4000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_3840x2160][VIDRECD_QUALITY_MID]   = 8000000;
    pVideoConfig->ulFps60BitrateMap[VIDRECD_RESOL_3840x2160][VIDRECD_QUALITY_HIGH]  = 16000000;

    for (idx = 0; idx < VIDRECD_RESOL_MAX_NUM; idx++) {
        if (pVideoConfig->ulFps30BitrateMap[idx][VIDRECD_QUALITY_LOW] == 0)
            pVideoConfig->ulFps30BitrateMap[idx][VIDRECD_QUALITY_LOW] = 2000000;
        if (pVideoConfig->ulFps30BitrateMap[idx][VIDRECD_QUALITY_MID] == 0)
            pVideoConfig->ulFps30BitrateMap[idx][VIDRECD_QUALITY_MID] = 3000000;
        if (pVideoConfig->ulFps30BitrateMap[idx][VIDRECD_QUALITY_HIGH] == 0)
            pVideoConfig->ulFps30BitrateMap[idx][VIDRECD_QUALITY_HIGH] = 4000000;
        if (pVideoConfig->ulFps60BitrateMap[idx][VIDRECD_QUALITY_LOW] == 0)
            pVideoConfig->ulFps60BitrateMap[idx][VIDRECD_QUALITY_LOW] = 4000000;
        if (pVideoConfig->ulFps60BitrateMap[idx][VIDRECD_QUALITY_MID] == 0)
            pVideoConfig->ulFps60BitrateMap[idx][VIDRECD_QUALITY_MID] = 6000000;
        if (pVideoConfig->ulFps60BitrateMap[idx][VIDRECD_QUALITY_HIGH] == 0)
            pVideoConfig->ulFps60BitrateMap[idx][VIDRECD_QUALITY_HIGH] = 8000000;
    }

    // Video encode setting : Frame Rate
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_7d5FPS].ulTimeIncre    = 8000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_7d5FPS].ulTimeResol    = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_10FPS].ulTimeIncre     = 6000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_10FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_12FPS].ulTimeIncre     = 5000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_12FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_12d5FPS].ulTimeIncre   = 4800;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_12d5FPS].ulTimeResol   = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_15FPS].ulTimeIncre     = 4000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_15FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_20FPS].ulTimeIncre     = 3000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_20FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_24FPS].ulTimeIncre     = 2407;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_24FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_25FPS].ulTimeIncre     = 2400;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_25FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_30FPS].ulTimeIncre     = 2000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_30FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_50FPS].ulTimeIncre     = 1200;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_50FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_60FPS].ulTimeIncre     = 1000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_60FPS].ulTimeResol     = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_100FPS].ulTimeIncre    = 600;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_100FPS].ulTimeResol    = 60000;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_120FPS].ulTimeIncre    = 500;
    pVideoConfig->stFrameRate[VIDRECD_FRAMERATE_120FPS].ulTimeResol    = 60000;

    // Feature setting
    pVideoConfig->bSeamlessMode         = MMP_TRUE;

    // Buffer Reserved Size
    #if (AHC_EMERGENTRECD_SUPPORT == 1)
    pVideoConfig->ulAudioCompBufSize    = 1024*1024;
    #else
    pVideoConfig->ulAudioCompBufSize    = 750*1024;
    #endif

    // ulPrmVidCompBufSize would affect emergency recording pre-enocde duration
    // m_ulEmergRecdPreEncDuration = ((ulPrmVidCompBufSize * 8 / bitrate) - 2) * 1000 (ms);
    // ex. m_ulEmergRecdPreEncDuration = math.floor[ (6*1024*1024 * 8 / 12000000 - 2) ] * 1000 = 2000 (ms);
    #if (AHC_EMERGENTRECD_SUPPORT == 1)
    pVideoConfig->ulPrmVidCompBufSize   = 8*1024*1024;
    #else
    pVideoConfig->ulPrmVidCompBufSize   = 6*1024*1024;
    #endif
    pVideoConfig->ulScdVidCompBufSize   = pVideoConfig->ulPrmVidCompBufSize;
    pVideoConfig->ulTrdVidCompBufSize   = pVideoConfig->ulPrmVidCompBufSize;
    pVideoConfig->ulUvcVidCompBufSize   = pVideoConfig->ulPrmVidCompBufSize;
    pVideoConfig->ulWifiVidCompBufSize  = 2*1024*1024;

    // Video: 8(bytes / frame), Audio 4: (bytes / frame)
    // Video: 8(bytes / frame) * 30 (frames / sec) = 240 (bytes / sec)
    // Audio: 48k(sample / sec) * 4 (bytes / frame) / 1024(sample / frame) = 187.5 (bytes /sec)
    // Total 25 mins: (240 + 187.5) * 60 * 25 = 641,250 (bytes) = 0x9C8E2
    // Total 10 mins: (240 + 187.5) * 60 * 10 = 256,500 (bytes) = 0x3E9F4
    pVideoConfig->ulTailBufSize         = 0x40000;

    #if (UVC_VIDRECD_SUPPORT)
    pVideoConfig->ulUVCTailBufSize      = pVideoConfig->ulTailBufSize;
    #endif
    #if (UVC_EMERGRECD_SUPPORT)
    pVideoConfig->ulUVCEmergTailBufSize = pVideoConfig->ulTailBufSize;//0x90000;
    #endif
    #if (DUAL_EMERGRECD_SUPPORT)
    pVideoConfig->ulDualEmergTailBufSize = pVideoConfig->ulTailBufSize;//0x90000;
    #endif
    #if (SUPPORT_VR_REFIX_TAILINFO)
    pVideoConfig->ulReFixTailBufSize    = pVideoConfig->ulTailBufSize;//0xA0000;
    #endif

#endif

    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : MMPC_3gpPlay_InitConfig
//  Description :
//------------------------------------------------------------------------------
/** @brief Initialized the preset configurations for 3GP playing

@pre This function must be called after MMPC_Display_InitConfig because of the TV attribute dependence
@pre The DRAM is initlized so that the DRAM type and size are assigned.
@return Always returns true;
*/
MMP_BOOL MMPC_3gpPlay_InitConfig(void)
{
#if !defined(MBOOT_FW)
    MMPS_SYSTEM_VIDEODECMODES *pModes;

    pModes = MMPS_VIDPLAY_GetConfig();

    pModes->deblock_type = MMPS_VIDPLAY_DEBLOCK_NONE;

    // 3GPPLAY mode standard LCD out, fit width for demo
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.usX                  = 0;
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.usY                  = 0;
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.usWidth              = RTNA_LCD_GetAttr()->usPanelW;
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.usHeight             = RTNA_LCD_GetAttr()->usPanelH;
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.bMirror              = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.rotationtype         = MMP_DISPLAY_ROTATE_NO_ROTATE;

    switch (RTNA_LCD_GetAttr()->ubDevType)
    {
    case LCD_TYPE_PLCD:
        pModes->config[VIDEOPLAY_MODE_STD_LCD].display.outputpanel      = MMP_DISPLAY_P_LCD;
        break;
    case LCD_TYPE_PLCD_FLM:
        pModes->config[VIDEOPLAY_MODE_STD_LCD].display.outputpanel      = MMP_DISPLAY_P_LCD_FLM;
        break;
    case LCD_TYPE_RGBLCD:
        pModes->config[VIDEOPLAY_MODE_STD_LCD].display.outputpanel      = MMP_DISPLAY_RGB_LCD;
        break;
    default:
        pModes->config[VIDEOPLAY_MODE_STD_LCD].display.outputpanel      = MMP_DISPLAY_NONE;
        break;
    }

    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.bFullyFilled         = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.bKeepRatio           = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_STD_LCD].display.bUseScaler           = MMP_TRUE;

    // 3GPPLAY mode standard LCD out, custom display
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.usX           = 0;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.usY           = 0;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.usWidth       = RTNA_LCD_GetAttr()->usPanelW;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.usHeight      = RTNA_LCD_GetAttr()->usPanelH;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.bMirror       = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.rotationtype  = MMP_DISPLAY_ROTATE_RIGHT_90;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.outputpanel   = MMP_DISPLAY_P_LCD;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.bFullyFilled  = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.bKeepRatio    = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_FULLSCREEN_LCD].display.bUseScaler    = MMP_TRUE;

    // 3GPPLAY mode standard LCD out, Rotate 180
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.usX                 = 0;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.usY                 = 0;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.usWidth             = MMPS_Display_GetConfig()->mainlcd.usWidth;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.usHeight            = MMPS_Display_GetConfig()->mainlcd.usHeight;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.bMirror             = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.rotationtype        = MMP_DISPLAY_ROTATE_RIGHT_180;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.outputpanel         = MMP_DISPLAY_P_LCD;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.bFullyFilled        = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.bKeepRatio          = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_ZOOM_LCD].display.bUseScaler          = MMP_TRUE;

    // 3GPPLAY mode standard LCD out, Rotate 270
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.usX               = 0;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.usY               = 0;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.usWidth           = MMPS_Display_GetConfig()->mainlcd.usWidth;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.usHeight          = MMPS_Display_GetConfig()->mainlcd.usHeight;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.bMirror           = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.rotationtype      = MMP_DISPLAY_ROTATE_RIGHT_270;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.outputpanel       = MMP_DISPLAY_P_LCD;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.bFullyFilled      = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.bKeepRatio        = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_ACTUAL_LCD].display.bUseScaler        = MMP_FALSE;

    // Standard TV out, fit width for demo
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.usX                  = 0;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.usY                  = 0;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.usWidth              = 720;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.usHeight             = 480;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.bMirror              = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.rotationtype         = MMP_DISPLAY_ROTATE_NO_ROTATE;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.outputpanel          = MMP_DISPLAY_TV;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.bFullyFilled         = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.bKeepRatio           = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_NTSC_TV].display.bUseScaler           = MMP_TRUE;

    // Standard TV out, fit width for demo
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.usX                   = 0;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.usY                   = 0;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.usWidth               = 720;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.usHeight              = 576;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.bMirror               = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.rotationtype          = MMP_DISPLAY_ROTATE_NO_ROTATE;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.outputpanel           = MMP_DISPLAY_TV;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.bFullyFilled          = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.bKeepRatio            = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_PAL_TV].display.bUseScaler            = MMP_TRUE;

    // HDMI output
    pModes->config[VIDEOPLAY_MODE_HDMI].display.usX                     = 0;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.usY                     = 0;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.usWidth                 = MMPS_Display_GetConfig()->hdmi.usDisplayWidth;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.usHeight                = MMPS_Display_GetConfig()->hdmi.usDisplayHeight;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.bMirror                 = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.rotationtype            = MMP_DISPLAY_ROTATE_NO_ROTATE;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.outputpanel             = MMP_DISPLAY_HDMI;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.bFullyFilled            = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.bKeepRatio              = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_HDMI].display.bUseScaler              = MMP_TRUE; // For 720P display to 1080P HDMI.

    // CCIR output
    pModes->config[VIDEOPLAY_MODE_CCIR].display.usX                     = 0;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.usY                     = 0;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.usWidth                 = 720;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.usHeight                = 480;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.bMirror                 = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.rotationtype            = MMP_DISPLAY_ROTATE_NO_ROTATE;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.outputpanel             = MMP_DISPLAY_CCIR;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.bFullyFilled            = MMP_TRUE;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.bKeepRatio              = MMP_FALSE;
    pModes->config[VIDEOPLAY_MODE_CCIR].display.bUseScaler              = MMP_TRUE;

    // Buffer size for video stream
    pModes->ulVideoStreamBufSize    = 2 * 1024 * 1024;
    #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
    pModes->ulRotateDMABufNum       = 0;
    #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    pModes->ulRotateDMABufNum       = 3;
    #endif

    pModes->usMP4DecBufNum          = 6;  // must >= 3
    pModes->window_type             = MMP_DISPLAY_WIN_PIP;
    pModes->videoplay_mode          = VIDEOPLAY_MODE_STD_LCD;

#endif
    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : MMPC_Display_InitConfig
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPC_Display_InitConfig(void)
{
    switch (RTNA_LCD_GetAttr()->ubDevType)
    {
    case LCD_TYPE_PLCD:
        MMPS_Display_GetConfig()->mainlcd.lcdtype           = MMP_DISPLAY_P_LCD;
        MMPS_Display_GetConfig()->mainlcd.cssel             = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->mainlcd.initialfx         = MMPC_Display_InitMainLCD;
        MMPS_Display_GetConfig()->mainlcd.reinitialfx       = MMPC_Display_ReinitMainLCD;
        MMPS_Display_GetConfig()->mainlcd.usWidth           = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->mainlcd.usHeight          = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->mainlcd.colordepth        = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->mainlcd.ulBgColor         = 0x000000;

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        if (LCD_RATIO_16_9 == RTNA_LCD_GetAttr()->ubRatio) {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 16;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 9;
        }
        else {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 4;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 3;
        }
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        if (LCD_RATIO_16_9 == RTNA_LCD_GetAttr()->ubRatio) {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 9;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 16;
        }
        else {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 3;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 4;
        }
#endif

        MMPS_Display_GetConfig()->mainlcd.bFLMType          = MMP_FALSE;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        MMPS_Display_GetConfig()->mainlcd.bRotateVerticalLCD = MMP_FALSE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        MMPS_Display_GetConfig()->mainlcd.bRotateVerticalLCD = MMP_TRUE;
#endif

        MMPS_Display_GetConfig()->sublcd.lcdtype            = MMP_DISPLAY_P_LCD;
        MMPS_Display_GetConfig()->sublcd.cssel              = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->sublcd.initialfx          = NULL;
        MMPS_Display_GetConfig()->sublcd.reinitialfx        = MMPC_Display_ReinitMainLCD;
        MMPS_Display_GetConfig()->sublcd.usWidth            = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->sublcd.usHeight           = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->sublcd.colordepth         = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->sublcd.ulBgColor          = 0xBB0000;
        MMPS_Display_GetConfig()->sublcd.ulPanelXratio      = 4;
        MMPS_Display_GetConfig()->sublcd.ulPanelYratio      = 3;
        MMPS_Display_GetConfig()->sublcd.bFLMType           = MMP_FALSE;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_FALSE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_TRUE;
#endif

        break;
    case LCD_TYPE_PLCD_FLM:
        MMPS_Display_GetConfig()->mainlcd.lcdtype           = MMP_DISPLAY_P_LCD_FLM;
        MMPS_Display_GetConfig()->mainlcd.cssel             = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->mainlcd.initialfx         = MMPC_Display_InitMainLCD;
        MMPS_Display_GetConfig()->mainlcd.reinitialfx       = MMPC_Display_ReinitMainLCD;
        MMPS_Display_GetConfig()->mainlcd.usWidth           = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->mainlcd.usHeight          = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->mainlcd.colordepth        = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->mainlcd.ulBgColor         = 0x000000;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        if (LCD_RATIO_16_9 == RTNA_LCD_GetAttr()->ubRatio) {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 16;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 9;
        }
        else {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 4;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 3;
        }
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        if (LCD_RATIO_16_9 == RTNA_LCD_GetAttr()->ubRatio) {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 9;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 16;
        }
        else {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 3;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 4;
        }
#endif

        MMPS_Display_GetConfig()->mainlcd.bFLMType          = MMP_TRUE;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        MMPS_Display_GetConfig()->mainlcd.bRotateVerticalLCD = MMP_FALSE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        MMPS_Display_GetConfig()->mainlcd.bRotateVerticalLCD = MMP_TRUE;
#endif
        MMPS_Display_GetConfig()->sublcd.lcdtype            = MMP_DISPLAY_P_LCD;
        MMPS_Display_GetConfig()->sublcd.cssel              = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->sublcd.initialfx          = NULL;
        MMPS_Display_GetConfig()->sublcd.reinitialfx        = MMPC_Display_ReinitMainLCD;
        MMPS_Display_GetConfig()->sublcd.usWidth            = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->sublcd.usHeight           = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->sublcd.colordepth         = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->sublcd.ulBgColor          = 0xBB0000;
        MMPS_Display_GetConfig()->sublcd.ulPanelXratio      = 4;
        MMPS_Display_GetConfig()->sublcd.ulPanelYratio      = 3;
        MMPS_Display_GetConfig()->sublcd.bFLMType           = MMP_TRUE;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_FALSE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_TRUE;
#endif
        break;
    case LCD_TYPE_RGBLCD:
        MMPS_Display_GetConfig()->mainlcd.lcdtype           = MMP_DISPLAY_RGB_LCD;
        MMPS_Display_GetConfig()->mainlcd.cssel             = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->mainlcd.initialfx         = MMPC_Display_InitMainLCD;
        MMPS_Display_GetConfig()->mainlcd.reinitialfx       = MMPC_Display_ReinitMainLCD;
        MMPS_Display_GetConfig()->mainlcd.usWidth           = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->mainlcd.usHeight          = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->mainlcd.colordepth        = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->mainlcd.ulBgColor         = 0x000000;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        if (LCD_RATIO_16_9 == RTNA_LCD_GetAttr()->ubRatio) {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 16;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 9;
        }
        else {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 4;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 3;
        }
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        if (LCD_RATIO_16_9 == RTNA_LCD_GetAttr()->ubRatio) {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 9;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 16;
        }
        else {
            MMPS_Display_GetConfig()->mainlcd.ulPanelXratio = 3;
            MMPS_Display_GetConfig()->mainlcd.ulPanelYratio = 4;
        }
#endif

        MMPS_Display_GetConfig()->mainlcd.bFLMType          = MMP_FALSE;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        MMPS_Display_GetConfig()->mainlcd.bRotateVerticalLCD = MMP_FALSE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        MMPS_Display_GetConfig()->mainlcd.bRotateVerticalLCD = MMP_TRUE;
#endif
        MMPS_Display_GetConfig()->sublcd.lcdtype            = MMP_DISPLAY_RGB_LCD;
        MMPS_Display_GetConfig()->sublcd.cssel              = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->sublcd.initialfx          = NULL;
        MMPS_Display_GetConfig()->sublcd.reinitialfx        = MMPC_Display_ReinitMainLCD;
        MMPS_Display_GetConfig()->sublcd.usWidth            = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->sublcd.usHeight           = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->sublcd.colordepth         = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->sublcd.ulBgColor          = 0xBB0000;
        MMPS_Display_GetConfig()->sublcd.ulPanelXratio      = 4;
        MMPS_Display_GetConfig()->sublcd.ulPanelYratio      = 3;
        MMPS_Display_GetConfig()->sublcd.bFLMType           = MMP_FALSE;
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_FALSE;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_FALSE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_TRUE;
#endif
        break;
    default:
        MMPS_Display_GetConfig()->mainlcd.lcdtype           = MMP_DISPLAY_NONE;
        MMPS_Display_GetConfig()->mainlcd.cssel             = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->mainlcd.initialfx         = NULL;
        MMPS_Display_GetConfig()->mainlcd.reinitialfx       = NULL;
        MMPS_Display_GetConfig()->mainlcd.usWidth           = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->mainlcd.usHeight          = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->mainlcd.colordepth        = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->mainlcd.ulBgColor         = 0x000000;
        MMPS_Display_GetConfig()->mainlcd.ulPanelXratio     = LCD_MODEL_RATIO_X;
        MMPS_Display_GetConfig()->mainlcd.ulPanelYratio     = LCD_MODEL_RATIO_Y;
        MMPS_Display_GetConfig()->mainlcd.bFLMType          = MMP_FALSE;
        MMPS_Display_GetConfig()->mainlcd.bRotateVerticalLCD = MMP_FALSE;

        MMPS_Display_GetConfig()->sublcd.lcdtype            = MMP_DISPLAY_NONE;
        MMPS_Display_GetConfig()->sublcd.cssel              = MMP_LCD_CS_SEL_1;
        MMPS_Display_GetConfig()->sublcd.initialfx          = NULL;
        MMPS_Display_GetConfig()->sublcd.reinitialfx        = NULL;
        MMPS_Display_GetConfig()->sublcd.usWidth            = RTNA_LCD_GetAttr()->usPanelW;
        MMPS_Display_GetConfig()->sublcd.usHeight           = RTNA_LCD_GetAttr()->usPanelH;
        MMPS_Display_GetConfig()->sublcd.colordepth         = MMP_LCD_COLORDEPTH_16;
        MMPS_Display_GetConfig()->sublcd.ulBgColor          = 0x000000;
        MMPS_Display_GetConfig()->sublcd.ulPanelXratio      = 4;
        MMPS_Display_GetConfig()->sublcd.ulPanelYratio      = 3;
        MMPS_Display_GetConfig()->sublcd.bFLMType           = MMP_FALSE;
        MMPS_Display_GetConfig()->sublcd.bRotateVerticalLCD = MMP_FALSE;
        break;
    }

    MMPS_Display_GetConfig()->ntsctv.tvtype             = MMP_TV_TYPE_NTSC;
    MMPS_Display_GetConfig()->ntsctv.usStartX           = 0;
    MMPS_Display_GetConfig()->ntsctv.usStartY           = 0;
    MMPS_Display_GetConfig()->ntsctv.usDisplayWidth     = 720;
    MMPS_Display_GetConfig()->ntsctv.usDisplayHeight    = 480;
    MMPS_Display_GetConfig()->ntsctv.ulDspyBgColor      = 0x00;
    MMPS_Display_GetConfig()->ntsctv.ubTvBgYColor       = 0x00;
    MMPS_Display_GetConfig()->ntsctv.ubTvBgUColor       = 0x80;
    MMPS_Display_GetConfig()->ntsctv.ubTvBgVColor       = 0x80;

    MMPS_Display_GetConfig()->paltv.tvtype              = MMP_TV_TYPE_PAL;
    MMPS_Display_GetConfig()->paltv.usStartX            = 0;
    MMPS_Display_GetConfig()->paltv.usStartY            = 0;
    MMPS_Display_GetConfig()->paltv.usDisplayWidth      = 720;
    MMPS_Display_GetConfig()->paltv.usDisplayHeight     = 576;
    MMPS_Display_GetConfig()->paltv.ulDspyBgColor       = 0x00;
    MMPS_Display_GetConfig()->paltv.ubTvBgYColor        = 0x00;
    MMPS_Display_GetConfig()->paltv.ubTvBgUColor        = 0x80;
    MMPS_Display_GetConfig()->paltv.ubTvBgVColor        = 0x80;

    MMPS_Display_GetConfig()->hdmi.ubColorType          = MMP_HDMI_COLORMODE_RGB888;
    MMPS_Display_GetConfig()->hdmi.usDisplayWidth       = 1920;
    MMPS_Display_GetConfig()->hdmi.usDisplayHeight      = 1080;
    MMPS_Display_GetConfig()->hdmi.ulDspyBgColor        = 0x000000;
    MMPS_Display_GetConfig()->hdmi.ubOutputMode         = MMP_HDMI_OUTPUT_1920X1080P;

    // ubOutputColor is needed same as ubColorType while ubColorType is not yuv420)
    MMPS_Display_GetConfig()->ccir.ubCCIRMode           = MMP_CCIR_656_NTSC; //only support CCIR_656_NTSC & MMP_CCIR_601_NTSC
    MMPS_Display_GetConfig()->ccir.ubColorType          = MMP_CCIR656_YUV422_8BIT_UYVY;
    MMPS_Display_GetConfig()->ccir.usDisplayWidth       = 720;
    MMPS_Display_GetConfig()->ccir.usDisplayHeight      = 480;
    if(MMPS_Display_GetConfig()->ccir.ubCCIRMode == MMP_CCIR_656_NTSC) {
        MMPS_Display_GetConfig()->ccir.ubClockDiv           = 5;
        MMPS_Display_GetConfig()->ccir.ubHSyncClkInv        = MMP_FALSE;
        MMPS_Display_GetConfig()->ccir.ubVSyncClkInv        = MMP_FALSE;
    }
    else if (MMPS_Display_GetConfig()->ccir.ubCCIRMode == MMP_CCIR_601_NTSC) {
        MMPS_Display_GetConfig()->ccir.ubClockDiv           = 10;
        MMPS_Display_GetConfig()->ccir.ubHSyncClkInv        = MMP_TRUE;
        MMPS_Display_GetConfig()->ccir.ubVSyncClkInv        = MMP_FALSE;
    }
    MMPS_Display_GetConfig()->OutputPanel               = MMP_DISPLAY_SEL_MAIN_LCD;

    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : MMPC_Audio_InitConfig
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPC_Audio_InitConfig(void)
{
#if !defined(MBOOT_FW)
    MMP_UBYTE i, j;

    #if 1
    MMPS_Audio_GetConfig()->AudioOutPath        = MMPS_AUDIO_OUT_AFE_LINE;
    #else
    MMPS_Audio_GetConfig()->AudioOutPath        = MMPS_AUDIO_OUT_I2S;
    #endif

    #if 1
    MMPS_Audio_GetConfig()->AudioInPath         = MMPS_AUDIO_IN_AFE_DIFF;
    #else
    MMPS_Audio_GetConfig()->AudioInPath         = MMPS_AUDIO_IN_I2S0;
    #endif

    MMPS_AUDIO_InitialInPath(MMPS_Audio_GetConfig()->AudioInPath);
    MMPS_AUDIO_InitialOutPath(MMPS_Audio_GetConfig()->AudioOutPath);

    #if (AUDIO_SET_DB == 0x0)
    MMPS_Audio_GetConfig()->ubVolumeLevel       = 31;
    #else
    MMPS_Audio_GetConfig()->ubVolumeLevel       = 31;
    #endif

    for(i = 0; i < MMPS_Audio_GetConfig()->ubVolumeLevel; i++) {
        for(j=0; j < 3; j++) {
            MMPS_Audio_GetConfig()->ubAudioOutVolHPTable[i][j] = ubAudOutVol_HP_table[i][j];
        }
    }
    for(i = 0; i < MMPS_Audio_GetConfig()->ubVolumeLevel; i++) {
        for(j=0; j < 2; j++) {
            MMPS_Audio_GetConfig()->ubAudioOutVolLineTable[i][j] = ubAudOutVol_Line_table[i][j];
        }
    }

    //SBC setting
    MMPS_Audio_GetConfig()->SBC.ChannelMode         = MMPS_AUDIO_SBC_CHANNEL_STEREO;
    MMPS_Audio_GetConfig()->SBC.AllocMethod         = MMPS_AUDIO_SBC_METHOD_SNR;
    MMPS_Audio_GetConfig()->SBC.usNrofBlocks        = 16;
    MMPS_Audio_GetConfig()->SBC.usNrofSubbands      = 8;
    MMPS_Audio_GetConfig()->SBC.ulBitRate           = 350;
    MMPS_Audio_GetConfig()->SBC.ulIntPeriod         = 200;
    MMPS_Audio_GetConfig()->SBC.ulMaxTransferSize   = 16*1024;

    MMPS_Audio_GetConfig()->ulNameBufSize           = 0x200;
    MMPS_Audio_GetConfig()->ulParameterBufSize      = 0x400;
    MMPS_Audio_GetConfig()->ulSdBufSize             = 0x400;
    MMPS_Audio_GetConfig()->ulSmBufSize             = 0x400;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_CARD_MODE].ulBufStartAddr = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_CARD_MODE].ulPlayBufSize  = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_CARD_MODE].ulSbcBufSize   = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_CARD_MODE].ulParseBufSize = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_MEM_MODE].ulBufStartAddr = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_MEM_MODE].ulPlayBufSize  = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_MEM_MODE].ulSbcBufSize   = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AACPLUS_P_MEM_MODE].ulParseBufSize = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_CARD_MODE].ulBufStartAddr   = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_CARD_MODE].ulPlayBufSize    = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_CARD_MODE].ulSbcBufSize     = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_CARD_MODE].ulParseBufSize   = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_MEM_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_MEM_MODE].ulPlayBufSize     = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_MEM_MODE].ulPlayBufSize     = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_FLAC_P_MEM_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MIDI_P_CARD_MODE].ulBufStartAddr   = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MIDI_P_CARD_MODE].ulPlayBufSize    = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MIDI_P_CARD_MODE].ulParseBufSize   = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MIDI_P_MEM_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MIDI_P_MEM_MODE].ulPlayBufSize     = 0x10000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MIDI_P_MEM_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_PCM_P_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_PCM_P_MEM_MODE].ulPlayBufSize      = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_PCM_P_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_CARD_MODE].ulPlayBufSize     = 0x4000;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_CARD_MODE].ulSbcBufSize      = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_CARD_MODE].ulWavBufSize      = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_CARD_MODE].ulParseBufSize    = 0x4000;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_MEM_MODE].ulPlayBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_MEM_MODE].ulSbcBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_MEM_MODE].ulWavBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_P_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_CARD_MODE].ulTagBufSize      = 0x200;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_CARD_MODE].ulPlayBufSize     = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_CARD_MODE].ulSbcBufSize      = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_MEM_MODE].ulTagBufSize       = 0x200;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_MEM_MODE].ulPlayBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_MEM_MODE].ulSbcBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WMA_P_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_CARD_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_CARD_MODE].ulTagBufSize       = 0x200;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_CARD_MODE].ulPlayBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_CARD_MODE].ulSbcBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_CARD_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_MEM_MODE].ulBufStartAddr      = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_MEM_MODE].ulTagBufSize        = 0x200;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_MEM_MODE].ulPlayBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_MEM_MODE].ulSbcBufSize        = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_RA_P_MEM_MODE].ulParseBufSize      = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_CARD_MODE].ulTagBufSize      = 0x200;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_CARD_MODE].ulPlayBufSize     = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_CARD_MODE].ulSbcBufSize      = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_MEM_MODE].ulTagBufSize       = 0x200;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_MEM_MODE].ulPlayBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_MEM_MODE].ulSbcBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_OGG_P_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_CARD_MODE].ulPlayBufSize     = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_CARD_MODE].ulSbcBufSize      = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_MEM_MODE].ulPlayBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_MEM_MODE].ulSbcBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_P_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_CARD_MODE].ulPlayBufSize     = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_CARD_MODE].ulSbcBufSize      = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_MEM_MODE].ulPlayBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_MEM_MODE].ulSbcBufSize       = 0x8000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_P_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_R_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_R_CARD_MODE].ulRecBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_R_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_R_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_R_MEM_MODE].ulRecBufSize       = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AMR_R_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AAC_R_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AAC_R_CARD_MODE].ulRecBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AAC_R_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AAC_R_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AAC_R_MEM_MODE].ulRecBufSize       = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_AAC_R_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_R_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_R_CARD_MODE].ulRecBufSize      = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_R_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_R_MEM_MODE].ulBufStartAddr     = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_R_MEM_MODE].ulRecBufSize       = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_MP3_R_MEM_MODE].ulParseBufSize     = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_R_CARD_MODE].ulBufStartAddr    = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_R_CARD_MODE].ulRecBufSize      = 0xC000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUDIO_WAV_R_CARD_MODE].ulParseBufSize    = 0;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_MP3_P_CARD_MODE].ulBufStartAddr      = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_MP3_P_CARD_MODE].ulPlayBufSize       = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_MP3_P_CARD_MODE].ulParseBufSize      = 0x4000;

    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_WAV_P_CARD_MODE].ulBufStartAddr      = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_WAV_P_CARD_MODE].ulPlayBufSize       = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_WAV_P_CARD_MODE].ulParseBufSize      = 0;

	MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_AMR_P_CARD_MODE].ulBufStartAddr      = 0;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_AMR_P_CARD_MODE].ulPlayBufSize       = 0x4000;
    MMPS_Audio_GetConfig()->AudioMode[MMPS_AUI_AMR_P_CARD_MODE].ulParseBufSize      = 0x4000;
#endif
    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : MMPC_System_InitConfig
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPC_System_InitConfig(void)
{
    MMPS_SYSTEM_CONFIG *pConfig = MMPS_System_GetConfig();

    pConfig->ulStackMemoryStart     = 0x1000000;
    pConfig->ulMaxReserveBufferSize = 96*1024;
    pConfig->ulMaxReserveChannel    = 2;
    pConfig->ulStackMemorySize      = m_DramSettings.DRAM_SIZE;

    if(m_DramSettings.DRAMID == DRAM_DDR){
        pConfig->stackMemoryType        = MMPS_DRAM_TYPE_AUTO;
        pConfig->stackMemoryMode        = MMPS_DRAM_MODE_DDR;
    }
    else if(m_DramSettings.DRAMID == DRAM_DDR2){
        pConfig->stackMemoryType        = MMPS_DRAM_TYPE_EXT;
        pConfig->stackMemoryMode        = MMPS_DRAM_MODE_DDR2;
    }
    else if(m_DramSettings.DRAMID == DRAM_DDR3){
        pConfig->stackMemoryType        = MMPS_DRAM_TYPE_AUTO; //???
        pConfig->stackMemoryMode        = MMPS_DRAM_MODE_DDR3;
    }
    return MMP_TRUE;
}
