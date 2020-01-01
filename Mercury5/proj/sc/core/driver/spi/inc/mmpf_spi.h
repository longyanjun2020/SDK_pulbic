//==============================================================================
//
//  File        : mmpf_spi.h
//  Description : INCLUDE File for the Host PSPI Driver.
//  Author      : Sunny Sun
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmpf_spi.h
 *  @brief The header File for the Host PSPI Driver
 *  @author Sunny Sun
 *  @version 1.0
 */

#ifndef _MMPF_SPI_H_
#define _MMPF_SPI_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmpf_typedef.h"

/** @addtogroup MMPF_Spi
 *  @{
 */

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_SPI_ID
{
    MMPF_SPI_ID_0 = 0,
    MMPF_SPI_ID_1,
    MMPF_SPI_ID_2,
    MMPF_SPI_ID_MAX
} MMPF_SPI_ID;

typedef enum _MMPF_SPI_DIR
{
    MMPF_SPI_TX = 0x1,
    MMPF_SPI_RX = 0x2
} MMPF_SPI_DIR;

typedef enum _MMPF_SPI_MODE
{
    MMPF_SPI_MASTER_MODE = 0,
    MMPF_SPI_SLAVE_MODE
} MMPF_SPI_MODE;

typedef enum _MMPF_SPI_PAD
{
    MMPF_SPI_PAD_0 = 0,
    MMPF_SPI_PAD_1,
    MMPF_SPI_PAD_2,
    MMPF_SPI_PAD_MAX
} MMPF_SPI_PAD;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMPF_SPI_ATTRIBUTE
{
    MMPF_SPI_MODE       spiMode;        /// Master or Slave mode
    MMP_USHORT          usSignalCtl;    /// Control signal setting (SS and SCLK)
    MMP_UBYTE			ubWordLength;   /// Word length in one time transfer
    MMP_UBYTE			ubSclkDiv;      /// SPI clock division
    MMP_USHORT			ubPspiDelay;    /// Delay count in consecutive transfer when SS is inactive
    MMP_USHORT			ubPspiWait;     /// Wait count in consecutive transfer when SS is active
    MMP_UBYTE           ubTxFIFOThres;  /// Tx FIFO threshold
    MMP_UBYTE           ubRxFIFOThres;  /// Rx FIFO threshold
    MMP_ULONG           ulIntEnable;    /// Interrupt Enable setting
    MMPF_SPI_PAD        padCtl;         /// Choose which pad to be used by SPI module
} MMPF_SPI_ATTRIBUTE;

typedef struct _MMPF_SPI_OPERATION
{
    MMPF_SPI_DIR        dir;            /// Transfer direction
    MMP_ULONG	        ulTxDmaAddr;    /// Tx DMA address
    MMP_UBYTE	        *ubTxFifoPtr;   /// Tx FIFO address
    MMP_ULONG	        ulRxDmaAddr;    /// Rx DMA address
    MMP_UBYTE	        *ubRxFifoPtr;   /// Rx FIFO address
    MMP_USHORT	        usTransferSize; /// Data transfer size
} MMPF_SPI_OPERATION;

typedef void SPICallBackFunc(void);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPF_SPI_ISR(void);
MMP_ERR MMPF_SPI_Initialize(void);
MMP_ERR MMPF_SPI_SetAttributes(MMPF_SPI_ID spiID, MMPF_SPI_ATTRIBUTE *spiattribute);
MMP_ERR MMPF_SPI_Operation(MMPF_SPI_ID spiID, MMPF_SPI_OPERATION *spiop, SPICallBackFunc* fpSPICallBack);
MMP_ERR MMPF_SPI_Write(MMPF_SPI_ID usSpiID, MMP_ULONG ulTxAddr, MMP_ULONG ulTxSize);
MMP_ERR MMPF_SPI_Read(MMPF_SPI_ID usSpiID, MMP_ULONG ulRxAddr, MMP_ULONG ulRxSize,MMP_ULONG ulTxAddr, MMP_ULONG ulTxSize);

/// @}

#endif // _MMPF_SPI_H_
