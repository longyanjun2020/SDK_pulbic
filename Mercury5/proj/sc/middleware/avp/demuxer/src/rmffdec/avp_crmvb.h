////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
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


#ifndef CRMVB_H
#define CRMVB_H

#include <stdint.h>
#include "avp_rmvb.h"

#define PAD_EVEN(x) ( ((x)+1) & ~1 )

#define MAX_VOP_BUFFER_NUM  350 //230
#define BUFFER_FOR_AUDIO 150 //80
#define PARSE_WHOLE_VFRAME(a) ((a)&0x20000000)
#define MORE_VFRAME_IN_PACKET(a) ((a)&0x0fffffff)

// ERROR handling message
enum GET_AUD_PKT_RTN
{
    GET_AUD_PKT_READY,
    GET_AUD_PKT_PREPARING,
    GET_AUD_PKT_CORRUPT
};

#define I_VOP       0
#define P_VOP       1
#define B_VOP       2


typedef struct CRMVB_member {
    int         videotype;
    int         audiotype;
    uint32_t    ulPartialFrameOffset;
    uint32_t    ulPartialFrameSize;
    rv_segment  Segments[MAX_RV_NUM_PACKETS];
    uint32_t    ulAUDataLen[MAX_RA_NUM_AU];
    uint32_t    ulFrameSize;
    uint32_t    ulNumPackets;
    int         width;
    int         height;
    int         fps;
} CRMVB_MEMBER;

typedef struct rm_demuxer_s
{
    CRMVB_MEMBER        CRMVB_m;
    RM_FORMAT_CONTEXT   rm_cont;
    cb_buffer_st        cbuffer;
    mvc_allocator_st    allocator;
    void               *alloc_ctx;
    void               *mem_ctx;
    uint32_t            video_alloc_size;
    uint32_t            audio_alloc_size;
    mvc_drop_level_et   drop_level;
    int                 drop_index;
    int                 drop_ratio_num;
    int                 drop_ratio_den;
    int                 decode_B_1_3;
} rm_demuxer_st;

#endif // CRMVB_H
