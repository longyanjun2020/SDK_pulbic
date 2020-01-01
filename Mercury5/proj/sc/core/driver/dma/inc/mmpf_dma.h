//==============================================================================
//
//  File        : mmpf_dma.h
//  Description : INCLUDE File for the Firmware Graphic Driver (DMA portion).
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_DMA_H_
#define _MMPF_DMA_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_err.h"
#include "mmp_graphics_inc.h"
#include "mmp_dma_inc.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_DMA_M_ID
{
    MMPF_DMA_M_0 = 0,
    MMPF_DMA_M_1,
    MMPF_DMA_M_MAX
} MMPF_DMA_M_ID;

typedef enum _MMPF_DMA_R_TYPE
{
    MMPF_DMA_R_NO = 0,
    MMPF_DMA_R_90,
    MMPF_DMA_R_180,
    MMPF_DMA_R_270
} MMPF_DMA_R_TYPE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_DMA_Initialize(void);
MMP_ERR MMPF_DMA_MoveData(MMP_ULONG         ulSrcAddr,
                          MMP_ULONG         ulDstAddr,
                          MMP_ULONG         ulCount,
                          DmaCallBackFunc   *CallBackFunc,
                          MMP_ULONG         CallBackArg, 
                          MMP_BOOL          bEnLineOfst,
                          MMP_DMA_LINE_OFST *pLineOfst);
MMP_ERR MMPF_DMA_RotateImageBuftoBuf(MMP_GRAPHICS_BUF_ATTR      *srcBufAttr,
                                     MMP_GRAPHICS_RECT          *srcrect, 
                                     MMP_GRAPHICS_BUF_ATTR      *dstBufAttr,
                                     MMP_USHORT                 usDstStartX,
                                     MMP_USHORT                 usDstStartY,
                                     MMP_GRAPHICS_ROTATE_TYPE   rotatetype,
                                     DmaRCallBackFunc           *CallBackFunc,
                                     MMP_ULONG                  CallBackArgu, 
                                     MMP_BOOL                   bMirrorEn,
                                     MMP_DMA_MIRROR_DIR         mirrortype);

#endif // _MMPF_DMA_H_
