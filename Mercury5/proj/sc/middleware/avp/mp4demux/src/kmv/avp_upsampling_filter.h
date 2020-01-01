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
#ifndef UPSAMPLING_FILTER_H
#define UPSAMPLING_FILTER_H
#include <stdint.h>
#include "avp_kmv_api.h"

#if defined (KMV_USE_HW_SCL) && (defined (WIN32) || defined (WINCE)|| defined (LINUX))
#define KMV_SIMULATE_HW_SCL
#endif

int kmv_init_semaphore(void);
int kmv_close_semaphore(void);
#if ((defined (KMV_USE_HW_SCL)) && (!defined (KMV_SIMULATE_HW_SCL)))
int rtk_convert_yv12_rgb565_upsampling(KMV_frame_buffer_ext *frame_buf, uint8_t *dst);
#else //((defined (KMV_USE_HW_SCL)) && (!defined (KMV_SIMULATE_HW_SCL)))

#ifdef KMV_USE_HW_DECODE
void upsampling_method6_Y(unsigned char* p1,unsigned char* p3, int posX, int posY,int CurrW,int CurrH, int W,int H,int16_t* out_buf);
void upsampling_method8_U(unsigned char* p1,unsigned char* p3,int posX, int posY, int CurrW,int CurrH, int W,int H,int16_t* out_buf);
#endif

void upsampling_method_Y(unsigned char* p1,unsigned char* p3, int posX, int posY,int CurrW,int CurrH, int W,int H, int16_t* out_buf_Y, int stride_y);
void upsampling_method_U(unsigned char* dst_u, unsigned char* src_u, unsigned char* dst_v, unsigned char* src_v, int posX, int posY, int CurrW,int CurrH, int W,int H,int16_t* out_buf, int stride_uv);
#endif
#endif //((defined (KMV_USE_HW_SCL)) && (!defined (KMV_SIMULATE_HW_SCL)))
