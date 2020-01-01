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


#ifndef BUF_ELEMENT_H
#define BUF_ELEMENT_H

#include <stdint.h>

typedef struct _buf_element_s_ buf_element_t;

struct _buf_element_s_
{
    uint32_t buff_size;          /* read video compressed buff size */

    int32_t pts;                 /* pts time */

    uint32_t duration;           /* duration of video or audio buffer */

    uint32_t flag;               /* status flag for this buffer */

    uint8_t *buffer;             /* compressed buff */
};


//====================================================================
// buffer element flag in ringbuffer queue
//
#define DMX_BUF_START               (1 <<  9)
#define DMX_BUF_END                 (1 << 10)
#define DMX_BUF_BODY                (1 << 11)

#define PLAYER_NEW_PTS              (1 << 13)

#define DMX_VIDEO_EOF               (1 << 14)
#define DMX_AUDIO_EOF               (1 << 15)

#define RBUF_FLAG_PADDING           (1 << 16)
#define FLAG_CONFIG_ONLY            (1 << 17)
#define FLAG_MORE_FRAME             (1 << 18)

#endif // BUF_ELEMENT_H
