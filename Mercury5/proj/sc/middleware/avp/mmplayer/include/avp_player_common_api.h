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


#ifndef PLAYER_COMMON_API_H
#define PLAYER_COMMON_API_H

#include <stdint.h>

#define MMP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define MMP_MIN(a, b) ((a) < (b) ? (a) : (b))
#define MMP_ABS(a)    ((a) > 0 ? (a) : -(a))

int aud_post_process_init(int sample_rate, int channel, int eq_mode, int init_mode);
int aud_post_process_play(void *player, void *buf, int size, int channel, int64_t pts);
int aud_post_process_close(void);

#endif
