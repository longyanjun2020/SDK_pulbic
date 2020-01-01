//------------------------------------------------------------------------------
//
//  File        : mmp_dma_inc.h
//  Description : Header file of DMA common information
//  Author      : Alterman
//  Revision    : 1.0
//
//------------------------------------------------------------------------------

#ifndef _MMP_DMA_INC_H_
#define _MMP_DMA_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

typedef void DmaCallBackFunc(MMP_ULONG argu);
typedef void DmaRCallBackFunc(void* arg1, void* arg2); // Use DIP Rotate

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/* DMA mirror direction */
typedef enum _MMP_DMA_MIRROR_DIR {
    DMA_MIRROR_H = 0,   ///< horizontal
    DMA_MIRROR_V,       ///< vertical
    DMA_NO_MIRROR
} MMP_DMA_MIRROR_DIR;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/* line-to-line offset configuration for DMA */
typedef struct _MMP_DMA_LINE_OFST {
    MMP_ULONG   ulSrcWidth;     ///< width of source
    MMP_ULONG   ulSrcOffset;    ///< line-to-line offset of source
    MMP_ULONG   ulDstWidth;     ///< width of destination
    MMP_ULONG   ulDstOffset;    ///< line-to-line offset of destination
} MMP_DMA_LINE_OFST;

#endif // _MMP_DMA_INC_H_

