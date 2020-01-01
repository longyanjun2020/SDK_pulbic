
/// @ait_only
//==============================================================================
//
//  File        : mmps_dma.h
//  Description : INCLUDE File for the Host DMA(Graphics) Driver.
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmps_dma.h
 *  @brief The header File for the Host DMA(Graphic) control functions
 *  @author Alan Wu
 *  @version 1.0
 */

#ifndef _MMPS_DMA_H_
#define _MMPS_DMA_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_dma.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPS_DMA_MoveData(MMP_ULONG ulSrcaddr, MMP_ULONG ulDstaddr,
                          MMP_ULONG ulCount, DmaCallBackFunc *cb,
                          MMP_DMA_LINE_OFST *lineOfst);

#endif //_MMPS_DMA_H_