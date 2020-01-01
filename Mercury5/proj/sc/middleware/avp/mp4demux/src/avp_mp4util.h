////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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


#ifndef MP4UTIL_H
#define MP4UTIL_H

#include <stdint.h>
#include "avp_mp4def.h"

#ifdef _MSC_VER
#include <string.h>
#define mp4_strcasecmp(a,b) _stricmp(a,b)
#elif defined(ECOS)
#include <string.h>
#define mp4_strcasecmp      strcasecmp
#elif defined(LINUX)
#include <strings.h>
#define mp4_strcasecmp      strcasecmp
#else
#define NEED_STRCASECMP
int16_t mp4_strcasecmp(const char* pszStr1, const char* pszStr2);
#endif

#define MP4_DBG_MSG(x, ...) ((void) 0)

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define ATTR_PACK __attribute__ ((packed))
#else
#define ATTR_PACK
#endif

enum MSFTWaveFormat
{
    WAVE_FORMAT_PCM       = 1,
    WAVE_FORMAT_ADPCM     = 0x0002,  /*  Microsoft Corporation  */
    WAVE_FORMAT_ALAW      = 6,
    WAVE_FORMAT_MULAW     = 7,
    WAVE_FORMAT_IMA_ADPCM = 0x11,
    WAVE_FORMAT_PCM_TWOS  = 0x7655, // signed, little endian format
    WAVE_FORMAT_PCM_SOWT  = 0x7656, // signed, big endian format
};

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

typedef struct pcm_audio_header_s
{
    uint16_t format_tag;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t bit_rate;
    uint16_t block_align;
    uint16_t sample_depth;
    /* uint16_t size_extra; */
} ATTR_PACK pcm_audio_header_st;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

int MP4AudioFormatToTag(uint32_t format);

void mdxInit(mp4_heap_st *ctx, unsigned char *heap, unsigned short size);

#define MP4Tolower(c)  (((c) >= 'A') && ((c) <= 'Z'))? (c) + ('a' - 'A') : (c)
#define MP4_MIN(a,b)   ((a) < (b) ? (a) : (b))

#endif /* MP4UTIL_H */
