/// @ait_only
//==============================================================================
//
//  File        : mmpd_dma.c
//  Description : DMA(2D) Engine Control driver function
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmpd_dma.c
*  @brief The DMA control functions
*  @author Alan Wu
*  @version 1.0
*/

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_dma.h"
#include "mmpf_dma.h"

/** @addtogroup MMPD_DMA
 *  @{
 */
 
//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_DMA_MoveData
//  Description : 
//------------------------------------------------------------------------------
/** @brief The function is fast move DMA.

  @param[in] ulSrcaddr the source address of fast move DMA
  @param[in] ulDstaddr the destination address of fast move DMA
  @param[in] ulCount the total byte counter of fast move DMA. Maxmum byte count 24 bit(1~16777215bytes)
  @param[in] cb Callback function for move done
  @param[in] pLineOfst is the move dma line offset settings.
  @return It reports the status of the operation.
*/
MMP_ERR MMPD_DMA_MoveData(MMP_ULONG         ulSrcAddr, 
                          MMP_ULONG         ulDstAddr,
                          MMP_ULONG         ulCount, 
                          DmaCallBackFunc   *cb,
                          MMP_DMA_LINE_OFST *pLineOfst)
{
    MMP_BOOL bLineOfstEn = (pLineOfst ? MMP_TRUE : MMP_FALSE);

    return MMPF_DMA_MoveData(ulSrcAddr, ulDstAddr, ulCount, cb, NULL,
                             bLineOfstEn, pLineOfst);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DMA_RotateImageBuftoBuf
//  Description :
//------------------------------------------------------------------------------
/** @brief   The function copy image date from one frame buffer to another frame buffer

  The function copy image date from one buffer to another buffer
  @param[in] srcBufAttr the source graphic buffer
  @param[in] srcRect the rect of source frame buffer
  @param[in] dstBufAttr the destination graphic buffer
  @param[in] usDststartx the x position of destination frame buffer
  @param[in] usDststarty the y position of destination frame buffer
  @param[in] rotateType the rotate direction
  @return It reports the status of the operation.
*/
MMP_ERR MMPD_DMA_RotateImageBuftoBuf(MMP_GRAPHICS_BUF_ATTR  *srcBufAttr,
                                     MMP_GRAPHICS_RECT      *srcRect,
                                     MMP_GRAPHICS_BUF_ATTR  *dstBufAttr,
                                     MMP_USHORT             usDstStartX,
                                     MMP_USHORT             usDstStartY,
                                     MMP_GRAPHICS_ROTATE_TYPE rotateType,
                                     DmaRCallBackFunc       *cbFunc,
                                     MMP_BOOL               bMirrorEn,
                                     MMP_DMA_MIRROR_DIR     mirrorType)
{
    return MMPF_DMA_RotateImageBuftoBuf(srcBufAttr, srcRect, dstBufAttr,
                                        usDstStartX, usDstStartY, rotateType, 
                                        cbFunc, NULL, bMirrorEn, mirrorType);
}

/// @}
/// @end_ait_only
