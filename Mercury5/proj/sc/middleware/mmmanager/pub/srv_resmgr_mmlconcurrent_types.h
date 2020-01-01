////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_resmgr_mmlconcurrent_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLCONCURRENT_TYPES_H__
#define __SRV_RESMGR_MMLCONCURRENT_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MML_SET_CONFLICT(eSection1, eSection2) \
{ \
    _g_bConcurrentConflict[(u32)eSection1][(u32)eSection2] = TRUE; \
    _g_bConcurrentConflict[(u32)eSection2][(u32)eSection1] = TRUE; \
}

#define MML_RESET_CONFLICT(eSection1, eSection2) \
{ \
    _g_bConcurrentConflict[(u32)eSection1][(u32)eSection2] = FALSE; \
    _g_bConcurrentConflict[(u32)eSection2][(u32)eSection1] = FALSE; \
}

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerManager
    @brief      Section states
*/
typedef enum
{
    CONCURRENT_SECTIONSTATE_TERMINATED = 0,
    CONCURRENT_SECTIONSTATE_CREATED,
    CONCURRENT_SECTIONSTATE_READY,
    CONCURRENT_SECTIONSTATE_RUNNING,
    CONCURRENT_SECTIONSTATE_BLOCKED,
    CONCURRENT_SECTIONSTATE_SUSPENDED,
    /* */
    CONCURRENT_SECTIONSTATE_DONTCARE,
    CONCURRENT_SECTIONSTATE_NUM
} MmlConcurrentSectionState_e;

/** @ingroup    MMLayerManager
    @brief      Sections
*/
opaque_enum(MmlConcurrentSection_e_)
{
    CONCURRENT_SECTION_BLUETOOTH_POWERON = 0,           /* Bluetooth Power On */
    CONCURRENT_SECTION_BLUETOOTH_OBJECTPUSHPROFILE,     /* Bluetooth Object Push Profile (OPP) */
    CONCURRENT_SECTION_VIDEO_PLAYBACK,                  /* Video Playback */
    CONCURRENT_SECTION_VIDEO_RECORDING,                 /* Video Recording */
    CONCURRENT_SECTION_IMAGE_CAPTURE,                   /* Image Capture */
    CONCURRENT_SECTION_GAME_NES,                        /* Game */
    CONCURRENT_SECTION_CAMERA_PREVIEW,                  /* Camera Preview */
    CONCURRENT_SECTION_AUDIO_PLAYBACK,                  /* Audio Playback */
    CONCURRENT_SECTION_USB_PCCAM,                       /* PC-Cam */
    CONCURRENT_SECTION_FM_RECORDING,                    /* FM Recording */
    /* */
    CONCURRENT_SECTION_NUM
};

/** @ingroup    MMLayerManager
    @brief      Marker types
*/
typedef enum
{
    CONCURRENT_MARKERTYPE_COMMAND = 0,           ///< Command
    CONCURRENT_MARKERTYPE_RESPONSE,              ///< Command response
    CONCURRENT_MARKERTYPE_NOTIFY,                ///< Notificatin event
    /* */
    CONCURRENT_MARKERTYPE_NUM
} MmlConcurrentMarkerType_e;

/** @ingroup    MMLayerManager
    @brief      Marker
*/
typedef struct
{
    MmlConcurrentMarkerType_e      eType;          ///< Specify which type of this marker
    u32                            nIdentifier;    ///< Use case ID (COMMAND/RESPONSE), Notify event (NOTIFY)
} MmlConcurrentMarker_t;

/** @ingroup    MMLayerManager
    @brief      Sections
*/
typedef struct
{
    MmlConcurrentSection_e         eSection;         ///< Concurrent section
    MmlConcurrentSectionState_e    eSectionState;    ///< State of the concurrent section
    MmlConcurrentMarker_t          tCreated;         ///< Beginning of the concurrent section
    MmlConcurrentMarker_t          tTerminated;      ///< End of the concurrent section
} MmlConcurrentSection_t;

#define MML_PLATFORM_CAPABILITY_SIGNATURE                         ((u32) 0x54414C50)     ///< ascii 'PLAT'
#define MML_PLATFORM_FLASHTYPE_NAND                               ((u16) 0x0010)         ///< Nand flash
#define MML_PLATFORM_FLASHTYPE_NOR                                ((u16) 0x0020)         ///< Nor flash
#define MML_PLATFORM_FLASHTYPE_SPI                                ((u16) 0x0030)         ///< SPI flash
#define MML_PLATFORM_MEMORYTYPE_TYPE1                             ((u16) 0x0021)         ///< Type1: Nor(Page)+Psram(Page)/Nor(Burst)+Psram(Page)
#define MML_PLATFORM_MEMORYTYPE_TYPE2                             ((u16) 0x0022)         ///< Type2: Nor(Page)+Psram(Burst)/Nor(Burst)+Psram(Burst)
#define MML_PLATFORM_MEMORYTYPE_TYPE3                             ((u16) 0x0023)         ///< Type3: Nand+Sdram
#define MML_PLATFORM_MEMORYTYPE_TYPE4                             ((u16) 0x0024)         ///< Type4: SPI+Psram(Burst)
#define MML_PLATFORM_MEMORYCONFIG_128X32                          ((u16) 0x0031)         ///< 128x32
#define MML_PLATFORM_MEMORYCONFIG_64X32                           ((u16) 0x0032)         ///< 64x32

/* Video playback resolutions supported */
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_SUBQCIF128x96     ((u16) 0x0040)         ///< 128x96
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_QCIF176x144       ((u16) 0x0041)         ///< 176x144
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_QVGA320x240       ((u16) 0x0042)         ///< 320x240
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_CIF352x288        ((u16) 0x0043)         ///< 352x288
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_VGA640x480        ((u16) 0x0044)         ///< 640x480
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_4CIF704x576       ((u16) 0x0045)         ///< 704x576
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_DVDPAL720x480     ((u16) 0x0046)         ///< 720x480
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_DVDNTSC720x576    ((u16) 0x0047)         ///< 720x576
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_720P1280x720      ((u16) 0x0048)         ///< 1280x720
#define MML_PLATFORM_MAXVIDEOPLAYBACKRESOLUTION_1080P1920x1080    ((u16) 0x0049)         ///< 1920x1080

/* Video recording resolutions supported */
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_SUBQCIF128x96    ((u16) 0x0050)         ///< 128x96
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_QCIF176x144      ((u16) 0x0051)         ///< 176x144
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_QVGA320x240      ((u16) 0x0052)         ///< 320x240
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_CIF352x288       ((u16) 0x0053)         ///< 352x288
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_VGA640x480       ((u16) 0x0054)         ///< 640x480
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_4CIF704x576      ((u16) 0x0055)         ///< 704x576
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_DVDPAL720x480    ((u16) 0x0056)         ///< 720x480
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_DVDNTSC720x576   ((u16) 0x0057)         ///< 720x576
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_720P1280x720     ((u16) 0x0058)         ///< 1280x720
#define MML_PLATFORM_MAXVIDEORECORDINGRESOLUTION_1080P1920x1080   ((u16) 0x0059)         ///< 1920x1080

/** @ingroup    MMLayerManager
    @brief      Platform capability
*/
struct MmlPlatformCapability_t_
{
  u32    nVersion;
  u32    nSignature;                                              ///< Signature = MML_PLATFORM_CAPABILITY_SIGNATURE
  u16    (*pConcurrentConflict)[(u32)CONCURRENT_SECTION_NUM];     ///< Pointer to the concurrent conflict table
  u16    nFlashType;                                              ///< Nand/Nor/SPI flash
  u16    nMemoryType;                                             ///< Flash-Dram combinations\n
                                                                  ///<     Type1: Nor(Page)+Psram(Page)/Nor(Burst)+Psram(Page)\n
                                                                  ///<     Type2: Nor(Page)+Psram(Burst)/Nor(Burst)+Psram(Burst)\n
                                                                  ///<     Type3: Nand+Sdram\n
                                                                  ///<     Type4: SPI+Psram(Burst)
  u16    nMemoryConfig;                                           ///< 128x32/64x32 configuration
  u16    bImageEffectSupported;                                   ///< Special image effect supported ? (0: No, 1: Yes)
  u16    bVideoPlaybackQcif15fpsOnly;                             ///< Only QCIF @ 15 frame/sec supported ? (0: No, 1: Yes)
  u16    bSensor03MegaOnly;                                       ///< Only 0.3 mega sensor supported ? (0: No, 1: Yes)
  u16    bImageCapture13MegaOnly;                                 ///< Only 1.3 mega (1280x1024) image capture supported ? (0: No, 1: Yes)
  u16    nMaxVideoPlaybackResolution;                             ///< Maximum video playback resolution supported, only limited by page-page condition
  u16    nMaxVideoRecordingResolution;                            ///< Maximum video recording resolution supported, only limited by page-page condition
  u16    bAudioUserEQSupported;                                   ///< User EQ supported ?
  u16    bAudio3DEffectSupported;                                 ///< 3D effect ?
};

/** @ingroup    MMLayerManager
    @brief      Platform chip types
*/
/*
enum MmlPlatformChipType_e_
{
    MML_PLATFORM_CHIPTYPE_8533C = 0x0,
    MML_PLATFORM_CHIPTYPE_8533C1,
    MML_PLATFORM_CHIPTYPE_8533N,
    MML_PLATFORM_CHIPTYPE_8536N,
    MML_PLATFORM_CHIPTYPE_8830C,
    MML_PLATFORM_CHIPTYPE_8830N,
    MML_PLATFORM_CHIPTYPE_8533D,
    MML_PLATFORM_CHIPTYPE_NUM
};
*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLCONCURRENT_TYPES_H__
