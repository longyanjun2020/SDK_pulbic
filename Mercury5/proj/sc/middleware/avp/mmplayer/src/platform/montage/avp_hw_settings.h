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


#ifndef MONTAGE_HW_SETTINGS_H
#define MONTAGE_HW_SETTINGS_H

extern void flush_share_buffer(U8 mode);
extern void adjust_power_saving_mode(mp4player *player, U8 mode);
extern void hw_frequency_workaround(mp4player *player, U8 mode);
extern void MDrv_MP4Dec_SRC_ADDR_BANK_SWITCH(mp4player *player);

#endif // MONTAGE_HW_SETTINGS_H
