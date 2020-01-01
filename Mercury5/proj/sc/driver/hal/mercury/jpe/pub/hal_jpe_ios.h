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

#ifndef __HAL_JPE_IOS_H__
#define __HAL_JPE_IOS_H__

#include "hal_jpe_defs.h"
#include "hal_jpe_reg.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    JPE_HAL_IRQ_FRAME_DONE      = 0x00000001,   // bit 0, jpe_framedone
    JPE_HAL_IRQ_BSPOBUF0_FULL   = 0x00000002,   // bit 1, jpe_bspobuf0_full, SW mode: buf full; HW mode: buf0 full
    JPE_HAL_IRQ_IMGBUF_FULL     = 0x00000004,   // bit 2, img_buf_full_irq
    JPE_HAL_IRQ_BSPOBUF1_FULL   = 0x00000008,   // bit 3, jpe_bspobuf1_full, SW mode: not used; HW mode: buf1 full
    JPE_HAL_IRQ_FS_FAIL         = 0x00000020,   // bit 5, fs_fail_irq
    JPE_HAL_IRQ_LESS_ROW_DONE   = 0x00000080,   // bit 7, less_row_down_irq
    JPE_HAL_IRQ_IMI_OVERFLOW    = 0x00000100,   // bit 8, jpe2scl_imi_overflow_int
    JPE_HAL_IRQ_TXIP_TIMEOUT    = 0x10000000,   // bit 4 when reg_jpe_g_vs_irq_en = 0, txip_time_out_irq
    JPE_HAL_IRQ_VS              = 0x20000000,   // bit 4 when reg_jpe_g_vs_irq_en = 1, vs
    JPE_HAL_IRQ_NET_TRIGGER     = 0x40000000,   // bit 6 when reg_jpe_g_row_down_irq_en = 0, net_trigger
    JPE_HAL_IRQ_VIU_ROW_DONE    = 0x80000000,   // bit 6 when reg_jpe_g_row_down_irq_en = 1, viu2jpe_row_done_jpe
    JPE_HAL_IRQ_ALL             = 0xF00001AF    // ALL bits
} JpeHalIrqEvent_e;

typedef enum
{
    JPE_HAL_OBUF_0 = 0,
    JPE_HAL_OBUF_1 = 1,
} JpeHalOBufOdr_e;

typedef enum
{
    JPE_HAL_FSVS_SW_MODE = 0,
    JPE_HAL_FSVS_SW_HW_MODE,
    JPE_HAL_FSVS_HW_MODE,
    JPE_HAL_FSVS_HW_WO_RESTART_MODE,
    JPE_HAL_FSVS_HW_WI_RESTART_MODE,
    JPE_HAL_FSVS_INVALID,
} JpeFsVsGenerationMode_e;

typedef enum
{
    JPE_HAL_OBUF_SINGLE_MODE    = 0x0,
    JPE_HAL_OBUF_MULTI_MODE     = 0x1
} JpeHalOutBufMode_e;

typedef enum
{
    JPE_HAL_INBUF_ROW_MODE      = 0x0,
    JPE_HAL_INBUF_FRAME_MODE    = 0x1
} JpeHalInBufMode_e;

typedef enum
{
    JPE_HAL_CODEC_JPEG          = 0x1,
    JPE_HAL_CODEC_H263I         = 0x2,
    JPE_HAL_CODEC_ENCODE_DCT    = 0x4,
} JpeHalCodecFormat_e;

typedef enum
{
    JPE_HAL_SCL_HANDSHAKE_OFF   = 0,
    JPE_HAL_SCL_HANDSHAKE_ON
} JpeHalSclHandShake_e;

typedef enum
{
    JPE_HAL_RAW_YUYV = 0x0,
    JPE_HAL_RAW_YVYU = 0x1,
    JPE_HAL_RAW_NV12 = 0x3,
    JPE_HAL_RAW_NV21 = 0x4,
} JpeHalRawFormat_e;

typedef enum
{
    JPE_HAL_COLOR_PLANE_LUMA    = 0,
    JPE_HAL_COLOR_PLANE_CHROMA  = 1,
    JPE_HAL_COLOR_PLANE_MAX     = 2
} JpeHalColorPlane_e;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef int JpeIOsCBFunc(int);

typedef struct
{
    u32             nInBufYAddr[2];
    u32             nInBufCAddr[2];
} JpeHalInBufCfg_t, *pJpeHalInBufCfg;

typedef struct
{
    u32             nOutBufStAddr[2];
    u32             nOutBufEdAddr[2];
    u32             nOutBufSize[2];
    u32             nJpeOutBitOffset;
} JpeHalOutBufCfg_t, *pJpeHalOutBufCfg;

typedef struct
{
    // Register configuration
    u32             nBaseAddr;
    u32             nSize;
    JpeReg_t        tJpeReg;

    // JPEG configuration
    int             nInBufMode;
    int             nRawFormat;
    int             nCodecFormat;
    u32             nWidth;
    u32             nHeight;
    u32             nYPitch;
    u32             nCPitch;
    u16             YQTable[64];
    u16             CQTable[64];
    u16             nQScale;

    JpeHalInBufCfg_t    tJpeHalInBufCfg;
    JpeHalOutBufCfg_t   tJpeHalOutBufCfg;
} JpeHalHandle_t;

typedef struct JpeRegIndex_t
{
    int             i_id;
    void*           base;
    int             size;
} JpeRegIndex_t;

typedef struct JpeIosCB_t
{
    void                    (*release)(void*);                      //! release this object.
    JpeHalIocRetStatus_e    (*setBank)(void*, JpeRegIndex_t*);      //! assign register base pointer.
    JpeHalIocRetStatus_e    (*setCBFunc)(void*, void*);             //! assign callback function.
    JpeHalIocRetStatus_e    (*setClock)(void*, int);                //! set module clock.
    JpeHalIocRetStatus_e    (*encFire)(void*, void*, JpeJob_t*);    //! process and trigger encoder job.
    JpeHalIocRetStatus_e    (*isrFunc)(void*, int);                 //! interrupt service routine.
    JpeHalIocRetStatus_e    (*irqMask)(void*, int);                 //! masking irq.
    JpeHalIocRetStatus_e    (*rstModule)(void*);                    //! reset module state machine.
} JpeIosCB_t;

typedef struct JpeIos_t
{
    JpeIosCB_t          mios;

    // Configuration used for encode
    u32                 nBaseAddr;
    JpeReg_t            tJpeReg;

    // Result after encode
    JpeHalDevStatus_e   eJpeDevStatus;
    u32                 nEncodeSize;
} JpeIos_t;

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

extern JpeIosCB_t* JpeIosAcquire(char* pTags);

#endif // __HAL_JPE_IOS_H__
