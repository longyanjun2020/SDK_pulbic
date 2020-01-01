/// @ait_only
//==============================================================================
//
//  File        : mmpd_dma.h
//  Description : INCLUDE File for the Host DMA(Graphics) Driver.
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmpd_dma.h
 *  @brief The header File for the Host DMA(Graphic) control functions
 *  @author Alan Wu
 *  @version 1.0
 */

#ifndef _MMPD_DMA_H_
#define _MMPD_DMA_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmp_graphics_inc.h"
#include "mmp_dma_inc.h"

/** @addtogroup MMPD_DMA
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_DMA_MoveData(MMP_ULONG         ulSrcAddr, 
                          MMP_ULONG         ulDstAddr,
                          MMP_ULONG         ulCount, 
                          DmaCallBackFunc   *cb,
                          MMP_DMA_LINE_OFST *pLineOfst);

MMP_ERR MMPD_DMA_RotateImageBuftoBuf(MMP_GRAPHICS_BUF_ATTR  *srcBufAttr,
                                     MMP_GRAPHICS_RECT      *srcRect,
                                     MMP_GRAPHICS_BUF_ATTR  *dstBufAttr,
                                     MMP_USHORT             usDstStartX,
                                     MMP_USHORT             usDstStartY,
                                     MMP_GRAPHICS_ROTATE_TYPE rotateType,
                                     DmaRCallBackFunc       *cbFunc,
                                     MMP_BOOL               bMirrorEn,
                                     MMP_DMA_MIRROR_DIR     mirrorType);

/// @}

#endif // _MMPD_DMA_H_

/// @end_ait_only
