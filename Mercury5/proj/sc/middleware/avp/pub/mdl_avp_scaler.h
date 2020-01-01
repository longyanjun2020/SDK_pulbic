////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2010 MStar Semiconductor, Inc.
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

#ifndef MDL_AVP_SCALER_H
#define MDL_AVP_SCALER_H

#include <stdint.h>

#define AVP_CODEC_4CC(a, b, c, d) \
            (((uint32_t) (a) << 24) | ((uint32_t) (b) << 16) | \
             ((uint32_t) (c) <<  8) | ((uint32_t) (d)))

enum AVP_CODEC_TYPE
{
    VIDEO_CODEC_I420    = AVP_CODEC_4CC('i','4','2','0'),
    VIDEO_CODEC_RGB565  = AVP_CODEC_4CC('r','g','b', 16),
};

typedef struct MDLAvpRect_s
{
    uint16_t                x;
    uint16_t                y;
    uint16_t                w;
    uint16_t                h;
} MDLAvpRect_s;

typedef struct MDLAvpVideoConfig_s
{
    uint8_t                 version;
    uint32_t                codecType;  /* only I420 is available for now */
    uint16_t                width;
    uint16_t                height;
    uint32_t                frameRateNum;
    uint32_t                frameRateDen;
    uint8_t                 tsType;
    uint8_t                *configData; /* codec specific config data*/
    int32_t                 configLen;
} MDLAvpVideoConfig_st;

typedef struct MDLVideoFrame_s
{
    uint8_t                 version;
    uint8_t                *data[4];
    int32_t                 stride[4];
    int32_t                 pts;        /* unit: ms */
    MDLAvpRect_s            dispArea;
    void                   *opaque;     /* callback data */
} MDLVideoFrame_st;

#endif /* MDL_AVP_SCALER_H */
