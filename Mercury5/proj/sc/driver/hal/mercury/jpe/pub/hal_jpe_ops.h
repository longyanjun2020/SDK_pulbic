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

#ifndef __HAL_JPE_OPS_H__
#define __HAL_JPE_OPS_H__

#include "hal_jpe_defs.h"
#include "hal_jpe_ios.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#if defined(__linux__)
#define JPE_DEV_STATE_NULL  -1
#define JPE_DEV_STATE_IDLE   0
#define JPE_DEV_STATE_BUSY   1
#else
#define JPE_DEV_STATE_NULL  -1
#define JPE_DEV_STATE_IDLE   1
#define JPE_DEV_STATE_BUSY   0
#endif

#define JPE_CTX_STATE_NULL  -1
#define JPE_CTX_STATE_IDLE   0
#define JPE_CTX_STATE_BUSY   1

#define JPE_USER_DATA_SIZE  (4*1024)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct
{
    u32                 u32JpeId;
    u32                 nRefYLogAddrAlign[2];
    u32                 nRefCLogAddrAlign[2];
    u32                 nOutBufSLogAddrAlign;
    u8                  nSclHandShakeSupport;
    u8                  nCodecSupport;
    u8                  nBufferModeSupport;
} JpeHalCaps_t;

typedef struct
{
    unsigned long       nAddr;
    unsigned long       nOrigSize;
    unsigned long       nOutputSize;
    JpeHalDevStatus_e   eState;
} JpeHalBitstreamInfo_t;

typedef struct
{
    unsigned long       nStAddr;
    unsigned long       nEdAddr;
    unsigned long       nSize;
} JpeHalBufInfo_t;

typedef struct
{
    JpeHalInBufMode_e   eInBufMode;
    JpeHalRawFormat_e   eRawFormat;
    JpeHalCodecFormat_e eCodecFormat;

    u32                 nWidth;
    u32                 nHeight;
    u32                 nYPitch;
    u32                 nCPitch;
    u16                 YQTable[64];
    u16                 CQTable[64];
    u16                 nQScale;

    JpeHalBufInfo_t     InBuf[JPE_HAL_COLOR_PLANE_MAX];
    JpeHalBufInfo_t     OutBuf;
    u32                 nJpeOutBitOffset;
} JpeHalCfg_t;

typedef struct JpeOpsCB_t JpeOpsCB_t;

struct JpeOpsCB_t
{
    char   jpename[16];
    void*                   (*jpeJob)(JpeOpsCB_t*);                 //! get mhve_job object.
    JpeHalIocRetStatus_e    (*init)(JpeOpsCB_t*, JpeHalCfg_t*);     //! initialize.
    JpeHalIocRetStatus_e    (*getCaps)(JpeOpsCB_t*, JpeHalCaps_t*); //! get capabilities.
    JpeHalIocRetStatus_e    (*setConf)(JpeOpsCB_t*, JpeHalCfg_t*);  //! apply config from JpegCfg
    JpeHalIocRetStatus_e    (*getConf)(JpeOpsCB_t*, JpeHalCfg_t*);  //! query config.
    void                    (*release)(JpeOpsCB_t*);                //! release this object.
};

typedef struct JpeOps_t
{
    JpeOpsCB_t              ops;
    JpeHalBitstreamInfo_t   *pEncOutBuf;
    JpeHalHandle_t          tJpeHalHandle;
    unsigned short          nClkSelect;
} JpeOps_t;

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

JpeOpsCB_t* JpeOpsAcquire(int id);

#endif //__HAL_JPE_OPS_H__
