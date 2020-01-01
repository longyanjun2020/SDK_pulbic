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


#ifndef PIONEER_HWMJPD_DECODE
#define PIONEER_HWMJPD_DECODE

#include "avp_video_decoder.h"

typedef struct _mjpd_video_disp_info
{
    unsigned short u16Width;
    unsigned short u16Height;
	unsigned short u16FrameRate;
	unsigned short u16temp;

	unsigned char bInterlace;
	unsigned char par_width;
	unsigned char par_height;

} mjpd_video_disp_info;

mjpd_video_disp_info mjpd_disp_info;

int init_PIONEER_HW_MJPD_decoder(video_decoder_t **decoder, uint32_t data_fmt, void *player);

#endif
