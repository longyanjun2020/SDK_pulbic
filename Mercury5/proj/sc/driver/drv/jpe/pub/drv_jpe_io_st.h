////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2017 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __JPE_DRV_IO_ST_H__
#define __JPE_DRV_IO_ST_H__

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define JPE_W_ALIGN_BASE_YUV422    (16)
#define JPE_H_ALIGN_BASE_YUV422    (8)
#define JPE_W_ALIGN_BASE_NV12      (16)
#define JPE_H_ALIGN_BASE_NV12      (16)

//==============================================================================
//
//                              Type Definition
//
//==============================================================================

#if defined(__linux__)
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum // Sync with JpeHalInBufMode_e
{
    JPE_IBUF_ROW_MODE   = 0x0,
    JPE_IBUF_FRAME_MODE = 0x1
} JpeInBufMode_e;

typedef enum // Sync with JpeHalRawFormat_e
{
    JPE_RAW_YUYV = 0x0,
    JPE_RAW_YVYU = 0x1,
    JPE_RAW_NV12 = 0x3,
    JPE_RAW_NV21 = 0x4,
} JpeRawFormat_e;

typedef enum // Sync with JpeHalCodecFormat_e
{
    JPE_CODEC_JPEG          = 0x1,
    JPE_CODEC_H263I         = 0x2,  //! obsolete
    JPE_CODEC_ENCODE_DCT    = 0x4,  //! obsolete
} JpeCodecFormat_e;

typedef enum // Sync with JpeHalDevStatus_e
{
    JPE_IDLE_STATE          = 0,
    JPE_BUSY_STATE          = 1,
    JPE_FRAME_DONE_STATE    = 2,
    JPE_OUTBUF_FULL_STATE   = 3,
    JPE_INBUF_FULL_STATE    = 4
} JpeState_e;

typedef enum // Sync with JpeHalIocRetStatus_e
{
    JPE_IOC_RET_SUCCESS             = 0,
    JPE_IOC_RET_BAD_QTABLE          = 1,
    JPE_IOC_RET_BAD_QP              = 2,
    JPE_IOC_RET_BAD_BITSOFFSET      = 3,
    JPE_IOC_RET_BAD_BANKNUM         = 4,
    JPE_IOC_RET_BAD_INBUF           = 5,
    JPE_IOC_RET_BAD_OUTBUF          = 6,
    JPE_IOC_RET_BAD_NULLPTR         = 7,
    JPE_IOC_RET_BAD_BANKCNT         = 8,
    JPE_IOC_RET_BAD_LASTZZ          = 9,
    JPE_IOC_RET_UNKOWN_COMMAND      = 10,
    JPE_IOC_RET_BAD_VIRTUAL_MEM     = 11,
    JPE_IOC_RET_NEED_DRIVER_INIT    = 12,
    JPE_IOC_RET_FMT_NOT_SUPPORT     = 13,
    JPE_IOC_RET_HW_IS_RUNNING       = 14,
    JPE_IOC_RET_FAIL                = 15
} JpeIocRetStatus_e;

typedef enum // Sync with JpeHalColorPlane_e
{
    JPE_COLOR_PLANE_LUMA     = 0,
    JPE_COLOR_PLANE_CHROMA   = 1,
    JPE_COLOR_PLANE_MAX      = 2
} JpeColorPlane_e;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct // Sync with JpeHalCaps_t
{
    u32                 u32JpeId;
    u32                 nRefYLogAddrAlign[2];
    u32                 nRefCLogAddrAlign[2];
    u32                 nOutBufSLogAddrAlign;
    u8                  nSclHandShakeSupport;
    u8                  nCodecSupport;
    u8                  nBufferModeSupport;
} JpeCaps_t;

typedef struct // Sync with JpeHalBitstreamInfo_t
{
    unsigned long       nAddr;
    unsigned long       nOrigSize;
    unsigned long       nOutputSize;
    JpeState_e          eState;
} JpeBitstreamInfo_t, *pJpeBitstreamInfo;

typedef struct // Sync with JpeHalBufInfo_t
{
    unsigned long       nStAddr;
    unsigned long       nEdAddr;
    unsigned long       nSize;
} JpeBufInfo_t;

typedef struct // Sync with JpeHalCfg_t
{
    JpeInBufMode_e      eInBufMode;
    JpeRawFormat_e      eRawFormat;
    JpeCodecFormat_e    eCodecFormat;

    u32                 nWidth;
    u32                 nHeight;
    u32                 nYPitch;
    u32                 nCPitch;
    u16                 YQTable[64];
    u16                 CQTable[64];
    u16                 nQScale;

    JpeBufInfo_t        InBuf[JPE_COLOR_PLANE_MAX];
    JpeBufInfo_t        OutBuf;
    u32                 nJpeOutBitOffset;
} JpeCfg_t;

/* NOTE: remove below definition when move this file to  linux-3.18\drivers\mstar\include\ */
#if defined(__I_SW__) || defined(__KERNEL__)
#include "drv_jpe_io_st_kernel.h"
#endif

#endif // __JPE_DRV_IO_ST_H__
