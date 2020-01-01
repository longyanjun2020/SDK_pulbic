/// @ait_only
//==============================================================================
//
//  File        : mmps_dma.c
//  Description : Ritian DMA(2D) Engine Control driver function
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmps_dma.c
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
#include "mmps_dma.h"

/** @addtogroup MMPS_DMA
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_DMA_MoveData
//  Description : 
//------------------------------------------------------------------------------
/** @brief The function is fast move DMA.

  @param[in] Dmamid the ID of fast move DMA
  @param[in] ulSrcaddr the source address of fast move DMA
  @param[in] ulDstaddr the destination address of fast move DMA
  @param[in] ulCount the total byte counter of fast move DMA. Maxmum byte count 24 bit(1~16777215bytes)
  @param[in] cb Callback function for move done
  @param[in] lineOfst move dma line offset config, enable line offset if not NULL.
  @return It reports the status of the operation.
*/
MMP_ERR MMPS_DMA_MoveData(MMP_ULONG ulSrcAddr, MMP_ULONG ulDstAddr, MMP_ULONG ulCount, 
                          DmaCallBackFunc *cb, MMP_DMA_LINE_OFST *lineOfst)
{
    MMP_ERR error;
    
    error = MMPD_DMA_MoveData(ulSrcAddr, ulDstAddr, ulCount, cb, lineOfst);
    
    return error;
}