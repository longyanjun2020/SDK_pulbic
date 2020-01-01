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


#ifndef MP4M_H
#define MP4M_H

#include "avp_ms_input.h"
#include "avp_mp4def.h"

//-----------------------------------------------------------------------------
// for demuxer
//-----------------------------------------------------------------------------
MP4FileHandle MP4Open(void *ctx, const cb_io_st *input, int ringbuf_size, void *mem_ctx);
uint8_t MP4Read(void *ctx, MP4FileHandle hFile);
uint8_t MP4Close(void *ctx, MP4FileHandle hFile);
uint32_t MP4GetNumberOfTracks(MP4FileHandle hFile);

#endif /* MP4M_H */
