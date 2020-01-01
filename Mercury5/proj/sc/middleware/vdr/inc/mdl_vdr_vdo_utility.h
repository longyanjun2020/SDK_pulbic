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

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_video.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_VDO_UTILITY_H__
#define __MDL_VDR_VDO_UTILITY_H__


//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "mdl_vdr_common.h"
#include "mdl_vdr_defines.h"

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

#define VIDEOUNSPECIFIED        (0)

#define MP4_REC_PLUGIN_IP  		1  // get video bitstream from IP codec
//#define MP4_REC_PLUGIN_VDO_FILE  1  // get video bitstream from file

#if defined(MP4_REC_PLUGIN_IP)
#define H263I_RECORDER
#endif
//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
// H263 header generation  -->
typedef struct _OutStream {
    // 1st Level buffer (32-bit)
    int m_nBufferEmptyBits;
    U32 m_SmallBuffer;

    // 2nd level buffer
    U8* m_pbFrameBuffer;
    U32 m_nByteCount;

    // Bit count
    U32 BC_nCumulativeBits;

    // Endian flag
    U8 m_bUseLittleEndian;
} OutStream;

typedef struct _M4VEINFO
{
    // Frame type
    int intStep;

    // Frame time
    int m_t;

    // Time parameters
    int nTimeResolution;
    int nFixedIncrement;
    int iClockRate;
} M4VEINFO;

typedef struct _VENC_CONFIG
{
    // [Input]
    int nDispWidth, nDispHeight;    // Display resolution
    int nBufWidth, nBufHeight;      // Image buffer resolution (aligned to 16 byte)
    // Rate control
    int FrameRatex100;
    //int nBitrate;
    int nQP;

    // Frame stat
    U8 vopPredType;         // I_VOP, P_VOP, B_VOP

    // Headers
    OutStream m_OutStream;
    U8 m_FdcBuffer[32];

    // Format-dependent
    M4VEINFO ctxM4veInfo;
} VENC_CONFIG;
// H263 header generation  <--

//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------
// Outstream Wrapper
void H263I_Init(VENC_CONFIG *pConfig);
void H263I_GetHeader(VENC_CONFIG *pConfig, int nDispOrder);


#endif // __MDL_VDR_VDO_UTILITY_H__

