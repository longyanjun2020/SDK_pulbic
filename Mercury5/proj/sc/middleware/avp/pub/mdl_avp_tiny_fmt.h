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

#ifndef MDL_AVP_TINY_FMT_H
#define MDL_AVP_TINY_FMT_H

#include <stdint.h>

#define MDL_AVP_TINY_MAX_CONFIG_LEN   256

typedef enum MDL_AVP_TINY_FRAME_TYPE_e
{
    MDL_AVP_TINY_EOF_FRAME = 0,
    MDL_AVP_TINY_AUDIO_FRAME,
    MDL_AVP_TINY_VIDEO_FRAME,
    MDL_AVP_TINY_A_CONFIG_FRAME,
    MDL_AVP_TINY_V_CONFIG_FRAME,
} MDL_AVP_TINY_FRAME_TYPE;

typedef enum MDL_AVP_TINY_VIDEO_CODEC_TYPE_e
{
    MDL_AVP_TINY_VIDEO_TYPE_ERROR = -1,
    MDL_AVP_TINY_VIDEO_TYPE_UNKNOWN,
    MDL_AVP_TINY_VIDEO_TYPE_MP2V,
    MDL_AVP_TINY_VIDEO_TYPE_DIV3,
    MDL_AVP_TINY_VIDEO_TYPE_DIVX,
    MDL_AVP_TINY_VIDEO_TYPE_H263,
    MDL_AVP_TINY_VIDEO_TYPE_M4V,
    MDL_AVP_TINY_VIDEO_TYPE_MP4S,
    MDL_AVP_TINY_VIDEO_TYPE_MP41,
    MDL_AVP_TINY_VIDEO_TYPE_MP42,
    MDL_AVP_TINY_VIDEO_TYPE_MP43,
    MDL_AVP_TINY_VIDEO_TYPE_WMV1,
    MDL_AVP_TINY_VIDEO_TYPE_WMV2,
    MDL_AVP_TINY_VIDEO_TYPE_WMV3,
    MDL_AVP_TINY_VIDEO_TYPE_WMVA,
    MDL_AVP_TINY_VIDEO_TYPE_AVC1,
    MDL_AVP_TINY_VIDEO_TYPE_RVCH,
    MDL_AVP_TINY_VIDEO_TYPE_FLV1,
    MDL_AVP_TINY_VIDEO_TYPE_RV10,
    MDL_AVP_TINY_VIDEO_TYPE_RV20,
    MDL_AVP_TINY_VIDEO_TYPE_RV30,
    MDL_AVP_TINY_VIDEO_TYPE_RV40,
    MDL_AVP_TINY_VIDEO_TYPE_AVS1,
    MDL_AVP_TINY_VIDEO_TYPE_MJPG,
    MDL_AVP_TINY_VIDEO_TYPE_MSVC,
    MDL_AVP_TINY_VIDEO_TYPE_VP60,
    MDL_AVP_TINY_VIDEO_TYPE_VP70,
    MDL_AVP_TINY_VIDEO_TYPE_VP80,
} MDL_AVP_TINY_VIDEO_CODEC_TYPE;

typedef enum MDL_AVP_TINY_AUDIO_CODEC_TYPE_e
{
    MDL_AVP_TINY_AUDIO_TYPE_ERROR = -1,
    MDL_AVP_TINY_AUDIO_TYPE_UNKNOWN,
    MDL_AVP_TINY_AUDIO_TYPE_AAC,
    MDL_AVP_TINY_AUDIO_TYPE_AC3,
    MDL_AVP_TINY_AUDIO_TYPE_AMRNB,
    MDL_AVP_TINY_AUDIO_TYPE_AMRNBIF2,
    MDL_AVP_TINY_AUDIO_TYPE_AMRWB,
    MDL_AVP_TINY_AUDIO_TYPE_ATRC,
    MDL_AVP_TINY_AUDIO_TYPE_COOK,
    MDL_AVP_TINY_AUDIO_TYPE_DRA,
    MDL_AVP_TINY_AUDIO_TYPE_DTS,
    MDL_AVP_TINY_AUDIO_TYPE_MP3,
    MDL_AVP_TINY_AUDIO_TYPE_PCM,
    MDL_AVP_TINY_AUDIO_TYPE_SIPR,
    MDL_AVP_TINY_AUDIO_TYPE_WMA1,
    MDL_AVP_TINY_AUDIO_TYPE_WMA2,
    MDL_AVP_TINY_AUDIO_TYPE_WMA3,
} MDL_AVP_TINY_AUDIO_CODEC_TYPE;

typedef enum MDL_AVP_TINY_SUBTITLE_TYPE_e
{
    MDL_AVP_TINY_SUBTITLE_TYPE_ERROR = -1,
    MDL_AVP_TINY_SUBTITLE_TYPE_UNKNOWN,
    MDL_AVP_TINY_SUBTITLE_TYPE_DXSB,
    MDL_AVP_TINY_SUBTITLE_TYPE_MP4S,
} MDL_AVP_TINY_SUBTITLE_TYPE;

typedef struct MDLAvpTinyVideoConfig_s
{
    int codec_type;
    int width;
    int height;
    int config_len;

    uint8_t config[MDL_AVP_TINY_MAX_CONFIG_LEN];
    /*
    config contains following fields
    1. int stride_y
    2. int stride_uv
    */

} MDLAvpTinyVideoConfig;

typedef struct MDLAvpTinyAudioConfig_s
{
    int codec_type;
    int sample_rate;
    int channel_num;
    int bits_per_sample;
    int frame_length;
    int config_len;
    uint8_t config[MDL_AVP_TINY_MAX_CONFIG_LEN];
} MDLAvpTinyAudioConfig;

#endif /* MDL_AVP_TINY_FMT_H */

