/// @ait_only
//==============================================================================
//
//  File        : mmpd_spi.h
//  Description : INCLUDE File for the Host PSPI Driver.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================


/**
 *  @file mmpd_spi.h
 *  @brief The header File for the Host PSPI Driver
 *  @author Penguin Torng
 *  @version 1.0
 */

#ifndef _MMPD_SPI_H_
#define _MMPD_SPI_H_

#include    "mmp_lib.h"
#include 	"ait_config.h"

/** @addtogroup MMPD_Spi
 *  @{
 */
//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================


//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
#define SPI_OFFSET 0x100

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef enum _MMPD_SPI_ID
{
    MMPD_SPI_ID_0 = 0,
    MMPD_SPI_ID_1,
	MMPD_SPI_CNT
} MMPD_SPI_ID;

typedef enum _MMPD_SPI_DIR
{
    MMPD_SPI_TX = 0x1,
    MMPD_SPI_RX = 0x2
} MMPD_SPI_DIR;

typedef enum _MMPD_SPI_MODE
{
    MMPD_SPI_MASTER_MODE = 0,
    MMPD_SPI_SLAVE_MODE
} MMPD_SPI_MODE;

typedef enum _MMPD_SPI_PAD
{
    MMPD_SPI_PAD_0 = 0,
    MMPD_SPI_PAD_1
} MMPD_SPI_PAD;

typedef struct _MMPD_SPI_ATTRIBUTE
{
    MMPD_SPI_MODE       mode;
    MMP_USHORT          usSignalCtl;
    MMP_UBYTE			ubWordLength;
    MMP_UBYTE			ubSclkDiv;
    MMP_UBYTE			ubPspiDelay;
    MMP_UBYTE			ubPspiWait;
    MMPD_SPI_PAD        padCtl;
} MMPD_SPI_ATTRIBUTE;

typedef struct _MMPD_SPI_OPERATION
{
    MMPD_SPI_DIR        dir;
    MMP_ULONG	        ulTxDmaAddr;
    MMP_UBYTE	        *ubTxFifoPtr;
    MMP_ULONG	        ulRxDmaAddr;
    MMP_UBYTE	        *ubRxFifoPtr;
    MMP_USHORT	        usTransferSize;
} MMPD_SPI_OPERATION;

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================


//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR MMPD_SPI_SetAttributes(MMPD_SPI_ID spiID, MMPD_SPI_ATTRIBUTE *spiattribute);
MMP_ERR MMPD_SPI_Operation(MMPD_SPI_ID spiID, MMPD_SPI_OPERATION *spiop);

//==============================================================================
//
//                              MACRO FUNCTIONS
//
//==============================================================================
/// @}
#endif // _MMPD_SPI_H_
/// @end_ait_only

