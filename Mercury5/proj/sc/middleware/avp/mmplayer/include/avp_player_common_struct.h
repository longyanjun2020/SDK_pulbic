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


#ifndef PLAYER_COMMON_STRUCT_H
#define PLAYER_COMMON_STRUCT_H

#include "avp_ms_io.h"
#include "avp_ms-mem.h"

typedef struct player_common_inst_s
{
    ms_fnchar file_name[MS_MAX_PATH];
    int       file_type;
    int       audio_only;
    int       video_only;   // for Mute/UnMute
    memory_slot_st memory_table[MAX_SLOT_COUNT];
} player_common_inst;

#endif
