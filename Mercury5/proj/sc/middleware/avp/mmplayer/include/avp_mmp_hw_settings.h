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


#ifndef MMP_HW_SETTINGS_H
#define MMP_HW_SETTINGS_H

#include <stdint.h>

void mmp_d_cache_flush(uint8_t *buf, int size);
void mmp_d_cache_invalidate(uint8_t *buf, int size);
void mmp_d_cache_flush_all(void);
void mmp_reset_watchdog(void);

#endif // MMP_HW_SETTINGS_H
