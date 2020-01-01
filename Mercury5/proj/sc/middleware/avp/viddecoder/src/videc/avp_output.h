////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
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


#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>
#include "avp_input.h"
#include "avp_ms_io.h"

int output_write_frame(io_st *io, uint8_t *data, int length, MSFILE fseg, int streamtype);

#endif /* OUTPUT_H */
