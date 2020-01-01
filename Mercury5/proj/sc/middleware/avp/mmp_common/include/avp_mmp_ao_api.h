////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
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


#ifndef MMP_AO_API_H
#define MMP_AO_API_H

#include <stdint.h>

enum AUDIO_DRV_STATUS
{
    AUD_DRV_STOP = 0,
    AUD_DRV_PLAY,
    AUD_DRV_PAUSE,
};

enum AUDIO_DRV_INIT_MODE
{
    AUD_DRV_TX_ONLY = 0,
    AUD_DRV_TX_RX,
};

typedef struct ao_driver_s
{
    // audio driver relate API
    int         (* init_drv)          (struct ao_driver_s *handle, int channel, int sample_rate, int BitsPerSample, int init_mode);
    int         (* reset_drv)         (struct ao_driver_s *handle, int channel, int sample_rate, int BitsPerSample, int init_mode);
    int         (* set_volume)        (struct ao_driver_s *handle, uint32_t volume);
    int         (* get_volume)        (struct ao_driver_s *handle, uint32_t *volume);
    int         (* close_drv)         (struct ao_driver_s **handle);
    // audio driver data related API
    void        (* start_play)        (struct ao_driver_s *handle);
    int         (* pause_play)        (struct ao_driver_s *handle);
    int         (* get_status)        (struct ao_driver_s *handle);
    int         (* queue_data)        (struct ao_driver_s *handle, void *outstream, int32_t outsize, int channel, int64_t timestamp);
    int         (* get_free_size)     (struct ao_driver_s *handle, uint32_t *u32uiUsefulSampleSize);
    int         (* get_sample_number) (struct ao_driver_s *handle);
    int         (* chk_sample_finish) (struct ao_driver_s *handle, int8_t *stop_flag);
    int         (* play_cur_buf)      (struct ao_driver_s *handle); // play the remaining data (< 8k) in IIS buffer
    void        (* wakeup)            (struct ao_driver_s *handle);
    int         (* ready)             (struct ao_driver_s *handle);
    int         open_success;
} ao_driver_st;

int init_default_audio_out(struct ao_driver_s **handle);
int init_rtk_A2DP(struct ao_driver_s**handle);
int init_null_audio_out(struct ao_driver_s **handle);
int init_rtk_audio_out(struct ao_driver_s **handle, int enable_down_mix);

#endif /* MMP_AO_API_H */
