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
#ifndef SMOOTH_FILTER_H
#define SMOOTH_FILTER_H


void smooth_semiplaner(unsigned char* Src ,int in_stride ,int out_stride, int Alpha,int Beta,int Chro);
#ifndef KMV_USE_HW_SCL
void smooth_frame_semiplaner(unsigned char* in_out_buf,int width,int height,int Alpha,int Beta,const int qp ,unsigned char* txtmap);
#endif
void smooth_frame(unsigned char *src_y, unsigned char *src_u, unsigned char *src_v,
                  int width,int height,
                  int stride_y, int stride_uv, int qp,
                  unsigned char *txtmap, int SMRECT);
#endif

