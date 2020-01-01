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
#ifndef KMV_TOOL_H
#define KMV_TOOL_H

#include <stdint.h>
#include "avp_kmv_api.h"

#define KMV_CHECK_INDEX_DATA
#define KMV_STCO_HEADER (4+4+3+1)
#define KMV_META_HEADER (4+4)
#define KMV_STSZ_HEADER (4+4)
#define KMV_SAMPLE_ELEMENT (1+2+2+1)
#define KMV_Gtype 2
#define KMV_CURRENT_VERSION 0x1

#ifdef KMV_ENCRYPT
#define KMV_NALU_TYPE_SLICE   1
#define KMV_NALU_TYPE_DPA     2
#define KMV_NALU_TYPE_DPB     3
#define KMV_NALU_TYPE_DPC     4
#define KMV_NALU_TYPE_IDR     5
#define KMV_NALU_TYPE_SEI     6
#define KMV_NALU_TYPE_SPS     7
#define KMV_NALU_TYPE_PPS     8
#define KMV_NALU_TYPE_AUD     9
#define KMV_NALU_TYPE_EOSEQ   10
#define KMV_NALU_TYPE_EOSTREAM 11
#define KMV_NALU_TYPE_FILLER  12

#define KMV_START_CODE_AVC1    3
#define KMV_NALU_TYPE_SLICE   1
#define KMV_NALU_TYPE_IDR     5
#define KMV_AVC_START_CODE1 0x000001
#define KMV_bsSWAP(a,b) (b=((a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3]))
#define KMV_FUNSHIFT3(a,b)  (((a)<<24) | (((uint32_t)(b))>>8 ))
#define KMV_FUNSHIFT1(a,b)  (((a)<<8)  | (((uint32_t)(b))>>24))
#endif


#ifdef KMV_3D
#define RGBClip(iValue) (((iValue) < (0))?(0):(((iValue) > (255))?(255):(iValue)))
void ConvertStereo(unsigned char *src,int width,int height,unsigned char* txtmap);
void Covert2RGB(unsigned char *pYsrc, unsigned char *pCbCrsrc,
                int width,
                int rw, int rh,
                unsigned char *Rval,
                unsigned char *Gval,
                unsigned char *Bval);
void Covert2YUV(unsigned char *pYsrc, unsigned char *pCbCrsrc,
                int width, int stride,
                int rw, int rh,
                unsigned char *Rval,
                unsigned char *Gval,
                unsigned char *Bval);

void Convert3DRGBYUV(unsigned char *pYsrc, unsigned char *pCbCrsrc,
                     unsigned char* Rval, unsigned char* Gval, unsigned char* Bval,
                     int regW, int regH, int width, int offset);

#endif // KMV_3D

#ifdef NoStrideFunction
int copyMB(int j, int i, int dj, int di,int bufH, int bufW, uint8_t *src, uint8_t *dst);
int copyMbFromTop(int j, int i, int rMBy, int rMBx, int recH, int recW, int bufH, int bufW, uint8_t *src, uint8_t *dst, int *txtmap);
int copyMbFromLeft(int j, int i, int rMBy, int rMBx, int recH, int recW, int bufH, int bufW, uint8_t *src, uint8_t *dst, int *txtmap);
int copyMbFromBot(int j, int i, int rMBy, int rMBx, int recH, int recW, int bufH, int bufW, uint8_t *src, uint8_t *dst, int *txtmap);
int copyMbFromRight(int j, int i, int rMBy, int rMBx, int recH, int recW, int bufH, int bufW, uint8_t *src, uint8_t *dst, int *txtmap);
int CopyTextMB(int recH, int recW, int dMBy, int dMBx,int bufH, int bufW, uint8_t *src, uint8_t *dst, int *txtmap);
int copyMB_mMerge(int j, int i,  int bufH, int bufW, uint8_t *src, uint8_t *dst);
int CopyTextMB_mMerge(int recH, int recW,
                      int bufH, int bufW,
                      int dMby, int dMbx,
                      uint8_t *src, uint8_t *dst, uint8_t *txtmap);

#endif

#endif /* KMV_TOOL_H */
