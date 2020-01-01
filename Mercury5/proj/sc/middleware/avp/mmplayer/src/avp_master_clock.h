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


#ifndef MASTER_CLOCK_H
#define MASTER_CLOCK_H

#include <stdint.h>
#include "avp_thread_mapping.h"

#define MONTAGE_CLOCK 1
#define PIONEER_CLOCK 2

#define PRE_BUFFERRING_TIME 0     // millisecond

typedef struct master_clock_s master_clock_st;

struct master_clock_s {

    void    (* open)                   (master_clock_st *self);

    int64_t (* get_master_clock)       (master_clock_st *self);

    int64_t (* convert_to_system_time) (master_clock_st *self, int64_t clock);

    int32_t (* get_audio_delay)        (master_clock_st *self);

    void    (* close)                  (master_clock_st **self);

    void    (* run)                    (master_clock_st *self);

    void    (* pause)                  (master_clock_st *self);

    int64_t (* get_audio_clock)        (master_clock_st *self);

    void    (* set_audio_clock)        (master_clock_st *self, int64_t audio_clock);

    int64_t (* get_clock_base)         (master_clock_st *self);

    void    (* set_clock_base)         (master_clock_st *self, int64_t clock);

    int64_t (* get_time)               (master_clock_st *self);

    void           *player;

    int             running;            /* whether clock is running or stopped/paused */

    int64_t         audio_clock;        /* the timestamp of the last delivered audio chunk */

    int64_t         pause_clock;        /* the clock value when playback paused */

    int64_t         base_clock;         /* the initial clock value */

    int64_t         last_apts;          /* the last time we update drift value */

    int64_t         clock_drift;        /* the difference between system clock and audio clock */

    mmp_mutex_t     clock_mutex;
};


extern int init_master_clock(void *player, int type);

#endif // MASTER_CLOCK_H
