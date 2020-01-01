////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file drv_dma.h
 * @brief definitions for DMA interface between client and driver
 *
 */

#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"
#include "drv_vm_dma.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define DMA_ERROR_LEVEL             (_CUS2)
#define DMA_TRACE_LEVEL             (DMA_ERROR_LEVEL | LEVEL_6)

/**
 * @brief Number of DMA channels available
 */
#define DMAC_NUM_CHANNELS 6

/**
 * @brief Maximum number of items in a DMA block
 */
#define DMAC_MAX_BLOCK_SIZE 1023


/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 * @brief Transfer width definitions
 */
typedef enum {
    DMAC_TFR_WIDTH_8BITS   = 0x0, ///< 8 bits transfer
    DMAC_TFR_WIDTH_16BITS  = 0x1, ///< 16 bits transfer
    DMAC_TFR_WIDTH_32BITS  = 0x2, ///< 32 bits transfer
    DMAC_TFR_WIDTH_64BITS  = 0x3, ///< 64 bits transfer
    DMAC_TFR_WIDTH_128BITS = 0x4, ///< 128 bits transfer
    DMAC_TFR_WIDTH_256BITS = 0x5  ///< 256 bits transfer
} DmaTfrWidth_e;

/**
 * @brief Increment type definitions
 */
typedef enum {
    DMAC_TFR_INCR_INCR     = 0x0, ///< increment address
    DMAC_TFR_INCR_DECR     = 0x1, ///< decrement address
    DMAC_TFR_INCR_NONE     = 0x2  ///< constant address
} DmaTfrIncr_e;

/**
 * @brief Number of data item definitions
 */
typedef enum {
    DMAC_TFR_MSIZE_1       = 0x0, ///< 1 bit
    DMAC_TFR_MSIZE_4       = 0x1, ///< 4 bits
    DMAC_TFR_MSIZE_8       = 0x2, ///< 8 bits
    DMAC_TFR_MSIZE_16      = 0x3, ///< 16 bits
    DMAC_TFR_MSIZE_32      = 0x4, ///< 32 bits
    DMAC_TFR_MSIZE_64      = 0x5, ///< 64 bits
    DMAC_TFR_MSIZE_128     = 0x6, ///< 128 bits
    DMAC_TFR_MSIZE_256     = 0x7  ///< 256 bits
} DmaTfrMsize_e;

/**
 * @brief Master IF definitions
 */
typedef enum {
    DMAC_TFR_MS_AHB1       = 0x0, ///< AHB1
    DMAC_TFR_MS_AHB2       = 0x1, ///< AHB2
    DMAC_TFR_MS_AHB3       = 0x2, ///< AHB3
    DMAC_TFR_MS_AHB4       = 0x3  ///< AHB4
} DmaMaster_e;

/**
 * @brief Flow controller definitions
 *
 * M for Memory
 * P for Peripheral
 * C for dmaController
 * SP for Source Peripheral
 * DP for Destination Peripheral
 * format is : Source2Dst_FlowController
 */
typedef enum {
    DMAC_CH_FC_M2M_C       = 0x0, ///< memory to memory, FC by DMA controller
    DMAC_CH_FC_M2P_C       = 0x1, ///< memory to peripheral, FC by DMA controller
    DMAC_CH_FC_P2M_C       = 0x2, ///< peripheral to memory, FC by DMA controller
    DMAC_CH_FC_P2P_C       = 0x3, ///< peripheral to peripheral, FC by DMA controller
    DMAC_CH_FC_P2M_P       = 0x4, ///< peripheral to memory, FC by peripheral
    DMAC_CH_FC_P2P_SP      = 0x5, ///< peripheral to peripheral, FC by source peripheral
    DMAC_CH_FC_M2P_P       = 0x6, ///< memory to peripheral, FC by peripheral
    DMAC_CH_FC_P2P_DP      = 0x7  ///< peripheral to peripheral, FC by destination peripheral
} DmaFlow_e;

/**
 * @brief Prototype for callback function called after end of block
 */
typedef void (* PfnDmaBlockCallback)(u32 nSession, u32 nBlocknum);

/**
 * @brief Prototype for callback function called after end of transfer
 */
typedef void (* PfnDmaTransferCallback)(u32 nSession);

/**
 * @brief DMA interface configuration structure to set up a transfer
 */
typedef struct {
    u32                    nSrcaddr;          ///< source address
    u32                    nDstaddr;          ///< destination address
    u32                    nSize;              ///< total size to transfer
    DmaTfrWidth_e          eSrcwidth;         ///< source transfer width: 8, 16, 32 bits
    DmaTfrWidth_e          eDstwidth;         ///< destination transfer width: 8, 16, 32 bits
    DmaTfrIncr_e           eSrcincr;          ///< source increment type
    DmaTfrIncr_e           eDstincr;          ///< destination increment type
    DmaTfrMsize_e          eSrcmsize;         ///< source burst transaction length
    DmaTfrMsize_e          eDstmsize;         ///< destination burst transaction length
    DmaMaster_e            eSrcms;            ///< source master IF
    DmaMaster_e            eDstms;            ///< destination master IF
    u32                    nSrcper;           ///<
    u32                    nDstper;           ///<
    bool                   bFifoMode;         ///< enable or disable fifo mode
    DmaFlow_e              eFctype;           ///< flow control type (mem -> periph, periph -> mem , mem-> mem ...)
    u32                    nPriority;          ///< transfer priority
    u32                    nSrcjumpinter;    ///< source gather interval
    u32                    nSrcjumpcount;    ///< source gather count
    u32                    nDstjumpinter;    ///< destination scatter interval
    u32                    nDstjumpcount;    ///< destination scatter count
    PfnDmaBlockCallback    pfnBlockcallback;    ///< end of block callback function
    PfnDmaTransferCallback pfnTransfercallback; ///< end of transfer callback function
} DmaParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 * @brief launch a single DMA transfer
 *
 * @param [in] p_dma_param  parameters set by client driver
 * @return a session number, which is the number of DMA channel used
 */
extern DmaErrMsg_e DrvDmaStart(DmaParam_t *pDmaparam, u8 *Channel);

/**
 * @brief stops a currently running DMA transfer
 *
 * @param [in] session DMA channel number
 * @return DRV_DMAC_OK if success, else error code
 */
extern DmaErrMsg_e DrvDmaStop(s32 session);

/**
 * @brief initializes a transfer for data added countinuously
 *
 * @param [in] p_dma_param   parameters set by client driver
 * @param [in] nb_blocks     number of client blocks in linked list
 * @return a session number, which is the number of DMA channel used
 */
extern DmaErrMsg_e DrvDmaLoopInit(DmaParam_t *p_dma_param, u32 nb_blocks, u8 *Channel);

/**
 * @brief adds data in a list of blocks to transfer
 *
 * A transfer must have been initialized successfully on a DMA channel with
 * DrvDmaLoopInit before calling this function.
 *
 * @param [in] session       DMA channel number
 * @param [in] p_data        data buffer
 * @param [in] nb_data       number of samples in data buffer
 * @param [in] block_number  client block number
 * @param [in] last_data     indicates the last client block
 * @return DRV_DMAC_OK if success, or an error code (<0)
 */
extern DmaErrMsg_e DrvDmaLoopAddData(s32 session, u32 *p_data, u32 nb_data, u32 block_number, bool last_data);

DmaErrMsg_e DrvDmaLoopPause(u32 session);
DmaErrMsg_e DrvDmaLoopResume(u32 session);

/**
 * @brief starts transfer with DMA (data already added in a loop)
 *
 * A transfer must have been initialized successfully on a DMA channel with
 * DrvDmaLoopInit before calling this function, which starts transferring data
 * already in a list of blocks.
 *
 * @param [in] session DMA channel number
 * @return DRV_DMAC_OK if success, else error code
 */
extern DmaErrMsg_e DrvDmaLoopStart(u32 session);


#endif // __SYS_DMA_ITF_H__

