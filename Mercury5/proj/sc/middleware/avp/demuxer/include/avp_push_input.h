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


#ifndef PUSH_INPUT_H
#define PUSH_INPUT_H

#include "avp_ms_io.h"
#include "avp_streaming.h"

//for SIMU_PUSH_THREAD usage
void create_push_thread(const ms_fnchar *arg);
int destroy_push_thread(void);

//public API
int init_mvc_push_input(void);
int close_mvc_push_input(void);
int mvc_push_data(void *buf, int size);
int mvc_get_push_buff_free_size(void);

#endif /* PUSH_INPUT_H */
