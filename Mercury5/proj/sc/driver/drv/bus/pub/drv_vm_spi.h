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
 * @page SPI_API SPI Interface
 *
 *
 * @section intro_sec Introduction
 *
 * This document describes the SPI bus Interface
 *
 *  <hr>
 * @section SectionMMI2SPI 1. MMI to SPI Interface
 *
 * @li @ref vm_spiOpen
 * @li @ref vm_spiClose
 * @li @ref vm_spiWrite
 * @li @ref vm_spiRead
 *
 *
 *  <hr>
 * @section Usage 2. Usage
 *
 *  The client first calls @ref vm_spiOpen to open a session on the SPI bus. This allocates the IOs used for this bus.
 *
 *  Then it can call @ref vm_spiWrite or/and @ref vm_spiRead to read and write data from/to the SPI bus.
 *
 *  A call to @ref vm_spiClose will close the session and free all resources (IOs) and powers off the SPI block.
 *
 *
 *
 *
 *
 *  <hr>
 *  @section Notes 3. NOTES
 *
 *  Current limitations :
 *
 *  \li 1. The clock speed cannot be changed during an opened session.
 *
 *
 */

/**
 * @file drv_vm_spi.h
 * @brief API prototypes for SPI bus
 */

#ifndef __DRV_VM_SPI_H__
#define __DRV_VM_SPI_H__

#ifndef __SDK_SIMULATION__

#include "vm_types.ht"
#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"

/****************************************************************************/
/*  SPI constants definitions                                               */
/****************************************************************************/
#define DRV_SPI_MAX_CS    2

/**
 * @brief Functions return values constants
 */
typedef enum
{
    VM_SPI_PROC_DONE = 0,               ///< Function executed with success
    VM_SPI_ERROR = -1,                  ///< Bus error
    VM_SPI_BAD_PARAMETER = -11,         ///< Bad parameter
    VM_SPI_ALREADY_USED = -12,          ///< SPI block already used
    VM_SPI_UNKNOWN_HANDLE = -21,        ///< Unknow handle
    VM_SPI_HANDLE_NOT_OPENED = -22,     ///< SPI block not openned
    VM_SPI_NO_MORE_HANDLE_FREE = -23,   ///< No more handle
    VM_FS_SPI_SPTE_TIMEOUT = -31,       ///< Full Speed SPI SPTE register polling timeout
    VM_FS_SPI_SPRF_TIMEOUT = -32,       ///< Full Speed SPI SPRF register polling timeout
    VM_FS_SPI_RAW_END_TIMEOUT = -33,    ///< Full Speed SPI RAW_END register polling timeout
    VM_FS_SPI_RDWR_TIMEOUT = -34,
    VM_PAGING_SPI_WR_RDY_TIMEOUT = -41, ///< Paging SPI Write ready register polling timeout
    VM_PAGING_SPI_RD_RDY_TIMEOUT = -42, ///< Paging SPI Read ready register polling timeout
    VM_FS_SPI_DMA_ERROR = -51,          ///< Full Speed DMA error
    VM_SPI_DMA_MODE_NOT_SUPPORT = -52,  ///< Paging SPI not support DMA mode
    VM_SPI_FSP_NOT_SUPPORT = -53,
    VM_SPI_MASTER_NOT_SUPPORT = -54,
    VM_MASTER_SPI_POLLING_TIMEOUT = -61,
    VM_MASTER_SPI_GDMA_ERROR = -62,
    VM_MASTER_SPI_GDMA_POLLING_TIMEOUT = -63,
    VM_FSP_SPI_POLLING_TIMEOUT = -71,
    VM_SPI_OPERATION_NOT_SUPPORT = -81
} VmSpiErrorCode_e;

/****************************************************************************/
/*  BUS types definitions                                                   */
/****************************************************************************/

/**
 * @brief SPI device
 */
typedef enum
{
    VM_FS_SPI = 0,                      ///< Full Speed SPI
    VM_PAGING_SPI = 1,                  ///< Paging SPI
    VM_MASTER_SPI = 2,                  ///< MASTER SPI
    VM_SPI_NUMBER                       ///< Number of SPI buses
} VmSpiBloc_e;

/**
 * @brief SPI Path Select
 */
typedef enum
{
    VM_SPI_CS_0 = 0x00,
    VM_SPI_CS_1 = 0x01,
    VM_SPI_SPI_ASURA = 0x00,
    VM_SPI_BTIF = 0x01,
    VM_SPI_MPIF_FLASH = 0x02,
    VM_SPI_CMMB_GPIO = 0x03,
    VM_SPI_MASTER = 0x04,
    
    VM_SPI_PAD_IO = 0x05,
    VM_SPI_BTIF_MINT = 0x06,
    VM_SPI_I2S_CMMBIO  = 0x07,
    VM_SPI_LCD_D  = 0x08
} VmSpiPathSelect_e;

/**
 * @brief SPI SSL Path Select
 */
typedef enum
{
    VM_SPI_SSL0_PAD_IO = 0x00,
    VM_SPI_SSL0_BTINT = 0x01,
    VM_SPI_SSL0_CMMB_GPIO = 0x02,
    VM_SPI_SSL0_LCD_D = 0x03,
    VM_SPI_SSL1_CMMB_GPIO = 0x04,
    VM_SPI_SSL1_MPIF_GPIO = 0x05,
    VM_SPI_SSL1_I2S  = 0x06,
    VM_SPI_SSL1_LCD_D  = 0x07
} VmSpiSslPathSelect_e;

/**
 * @brief Paging SPI bus settings options
 */
typedef struct
{
    u8 nCsCurrent;
    u8 nCsNum;
    IoChipPadNum_e eCsPad[DRV_SPI_MAX_CS];
} VmGpioCs_t;

/**
 * @brief Full Speed SPI mode
 */
typedef enum
{
    VM_FS_SPI_MODE_MASTER = 0,          ///< master
    VM_FS_SPI_MODE_SLAVE = 1            ///< slave
} VmFsSpiMode_e;

/**
 * @brief Full Speed SPI bus clock speed (bit rate)
 */
typedef enum
{
    VM_FS_SPI_SCL_SPEED_13Mhz = 0x00,   ///< 13 MHz
    VM_FS_SPI_SCL_SPEED_10_4Mhz = 0x01, ///< 10.4 MHz
    VM_FS_SPI_SCL_SPEED_8_67Mhz = 0x02, ///< 8.67 MHz
    VM_FS_SPI_SCL_SPEED_6_5Mhz = 0x03,  ///< 6.5 MHz
    VM_FS_SPI_SCL_SPEED_5_2Mhz = 0x04,  ///< 5.2 MHz
    VM_FS_SPI_SCL_SPEED_3_71Mhz = 0x05, ///< 3.71 MHz
    VM_FS_SPI_SCL_SPEED_2_36Mhz = 0x06, ///< 2.36 MHz
    VM_FS_SPI_SCL_SPEED_1Mhz = 0x07     ///< 1 MHz
} VmFsSpiClkSpeed_e;

/**
 * @brief Full Speed SPI Chip Select Polarity
 */
typedef enum
{
    VM_FS_SPI_CS_LOW_POLARITY = 0x00,   ///< Low polarity
    VM_FS_SPI_CS_HIGH_POLARITY = 0x01   ///< High polarity
} VmFsSpiCsPolarity_e;

/**
 * @brief Full Speed SPI Slave Select destination(chip select)
 */
typedef enum
{
    VM_FS_SPI_SSL_DST_0 = 0,          ///< SSL0
    VM_FS_SPI_SSL_DST_1 = 1           ///< SSL1
} VmFsSpiSslDst_e;

/**
 * @brief Full Speed SPI bus size
 *
 * Constants values are equal to number of bits
 */
typedef enum
{
    VM_FS_SPI_BUS_SIZE_1_BIT = 1,
    VM_FS_SPI_BUS_SIZE_2_BITS = 2,
    VM_FS_SPI_BUS_SIZE_3_BITS = 3,
    VM_FS_SPI_BUS_SIZE_4_BITS = 4,
    VM_FS_SPI_BUS_SIZE_5_BITS = 5,
    VM_FS_SPI_BUS_SIZE_6_BITS = 6,
    VM_FS_SPI_BUS_SIZE_7_BITS = 7,
    VM_FS_SPI_BUS_SIZE_BYTE = 8,
    VM_FS_SPI_BUS_SIZE_9_BITS = 9,
    VM_FS_SPI_BUS_SIZE_10_BITS = 10,
    VM_FS_SPI_BUS_SIZE_11_BITS = 11,
    VM_FS_SPI_BUS_SIZE_12_BITS = 12,
    VM_FS_SPI_BUS_SIZE_13_BITS = 13,
    VM_FS_SPI_BUS_SIZE_14_BITS = 14,
    VM_FS_SPI_BUS_SIZE_15_BITS = 15,
    VM_FS_SPI_BUS_SIZE_WORD = 16,
    VM_FS_SPI_BUS_SIZE_17_BITS = 17,
    VM_FS_SPI_BUS_SIZE_18_BITS = 18,
    VM_FS_SPI_BUS_SIZE_19_BITS = 19,
    VM_FS_SPI_BUS_SIZE_20_BITS = 20,
    VM_FS_SPI_BUS_SIZE_21_BITS = 21,
    VM_FS_SPI_BUS_SIZE_22_BITS = 22,
    VM_FS_SPI_BUS_SIZE_23_BITS = 23,
    VM_FS_SPI_BUS_SIZE_24_BITS = 24,
    VM_FS_SPI_BUS_SIZE_25_BITS = 25,
    VM_FS_SPI_BUS_SIZE_26_BITS = 26,
    VM_FS_SPI_BUS_SIZE_27_BITS = 27,
    VM_FS_SPI_BUS_SIZE_28_BITS = 28,
    VM_FS_SPI_BUS_SIZE_29_BITS = 29,
    VM_FS_SPI_BUS_SIZE_30_BITS = 30,
    VM_FS_SPI_BUS_SIZE_31_BITS = 31,
    VM_FS_SPI_BUS_SIZE_32_BITS = 32
} VmFsSpiBusSize_e;

/**
 * @brief Paging SPI bus clock speed (bit rate)
 *
 * Constants values are equal to number of bits
 */
typedef enum
{
    VM_PAGING_SPI_CLK_DIV2 = 0x001,
//    VM_PAGING_SPI_CLK_DIV3 = 0x002,   // Reserved
    VM_PAGING_SPI_CLK_DIV4 = 0x004,
//    VM_PAGING_SPI_CLK_DIV5 = 0x008,   // Reserved
//    VM_PAGING_SPI_CLK_DIV6 = 0x010,   // Reserved
//    VM_PAGING_SPI_CLK_DIV7 = 0x020,   // Reserved
    VM_PAGING_SPI_CLK_DIV8 = 0x040,
    VM_PAGING_SPI_CLK_DIV16 = 0x080,
    VM_PAGING_SPI_CLK_DIV32 = 0x100,
    VM_PAGING_SPI_CLK_DIV64 = 0x200,
    VM_PAGING_SPI_CLK_DIV128 = 0x400
} VmPagingSpiClkSpeed_e;

/**
 * @brief Master SPI bus clock speed (bit rate)
 */
typedef enum
{
    VM_MASTER_SPI_CLK_DIV2 = 0x0,
    VM_MASTER_SPI_CLK_DIV4 = 0x1,
    VM_MASTER_SPI_CLK_DIV8 = 0x2,
    VM_MASTER_SPI_CLK_DIV16 = 0x3,
    VM_MASTER_SPI_CLK_DIV32 = 0x4,
    VM_MASTER_SPI_CLK_DIV64 = 0x5,
    VM_MASTER_SPI_CLK_DIV128 = 0x6,
    VM_MASTER_SPI_CLK_DIV256 = 0x7
} VmMasterSpiCLKSpeed_e;

/**
 * @brief Master SPI:
 * The time from mspi trigger to first MSPI clock
 * The time from last MSPI to done flag assert
 */
typedef enum
{
    VM_MASTER_SPI_DELAY_CLK1 = 0x0,     //Delay 1 MSPI Clock
    VM_MASTER_SPI_DELAY_CLK2 = 0x1,     //Delay 2 MSPI Clock
    VM_MASTER_SPI_DELAY_CLK16 = 0xf,    //Delay 16 MSPI Clock
    VM_MASTER_SPI_DELAY_CLK256 = 0xff   //Delay 256 MSPI Clock
} VmMasterSpiDelayTime_e;

/**
 * @brief Master SPI:
 * The time between byte to byte transfer
 * The time between last write and first read
 */
typedef enum
{
    VM_MASTER_SPI_TRDELAY_CLK0 = 0x0,     //No Delay
    VM_MASTER_SPI_TRDELAY_CLK1 = 0x1,     //Delay 1 MSPI Clock
    VM_MASTER_SPI_TRDELAY_CLK15 = 0xf,    //Delay 15 MSPI Clock
    VM_MASTER_SPI_TRDELAY_CLK255 = 0xff   //Delay 255 MSPI Clock
} VmMasterSpiTRDelayTime_e;

/**
 * @brief Master SPI:
 *  How many bits will be transferred in write buffer0~7
 *
 */
typedef enum
{
    VM_MASTER_SPI_BUS_SIZE_1_BIT = 0x0,
    VM_MASTER_SPI_BUS_SIZE_2_BITS = 0x1,
    VM_MASTER_SPI_BUS_SIZE_3_BITS = 0x2,
    VM_MASTER_SPI_BUS_SIZE_4_BITS = 0x3,
    VM_MASTER_SPI_BUS_SIZE_5_BITS = 0x4,
    VM_MASTER_SPI_BUS_SIZE_6_BITS = 0x5,
    VM_MASTER_SPI_BUS_SIZE_7_BITS = 0x6,
    VM_MASTER_SPI_BUS_SIZE_BYTE = 0x7,
} VmMasterSpiBusSize_e;

/**
 * @brief Full Speed SPI bus settings options
 */
typedef struct
{
    VmFsSpiMode_e eSpiMode;             ///< slave or master (0 default) mode
    VmFsSpiClkSpeed_e eClkSpeed;        ///< transfer bit rate
    u8 nStopClklatency;                 ///< Indicates the number of SCLK advance or offset periods related to SSL ending
    u8 nStartClockLatency;              ///< Indicates the number of SCLK advance or offset periods related to SSL starting
    VmFsSpiCsPolarity_e eCSPolarity;    ///< true SSL is active high
    bool bStopClockPosition;            ///< determines the SCLK stop position 0 stops before SSL 1 stops after SSL
    bool bLsbFirst;                     ///< true Less Significant Bit is transmitted/received first
    bool bStartClockPosition;           ///< determines the SCLK start position 0 starts before SSL 1 stops after SSL
    bool bFullDuplex;                   ///< true full duplex mode
    bool bApdDis;                       ///< true Auto power down mode disable bit
    bool bTfrModeDMA;                   ///< true Rx,Tx registers are accessed by DMA
    bool bBigEndian;                    ///< true Big endian alignment for Rx & Tx data
    u8 nItrMode;                        ///< interword mode
    u8 nItrDelay;                       ///< determines the number of SCLK periods between 2 consecutives words
    bool bSslInactPolEn;
    bool bSsl0InactPolHigh;
    bool bSsl1InactPolHigh;
    VmFsSpiBusSize_e eAccessSize;
} VmFsSpiOptions_t;

/**
 * @brief Paging SPI bus settings options
 */
typedef struct
{
    VmPagingSpiClkSpeed_e eClkDiv;
} VmPagingSpiOptions_t;

/**
 * @brief Master SPI bus settings options
 */
typedef struct
{
    bool                        bThreeWireMode;
    bool                        bGdmaIntMode;
    VmMasterSpiCLKSpeed_e       eClkDiv;
    VmMasterSpiDelayTime_e      eStartTime;
    VmMasterSpiDelayTime_e      eEndTime;
    VmMasterSpiTRDelayTime_e    eByteInterval;
    VmMasterSpiTRDelayTime_e    eTurnAroundTime;
    VmMasterSpiBusSize_e        eBusSize;
} VmMasterSpiOptions_t;




/**
 * @brief SPI bus settings structure
 */
typedef struct
{
    bool bClockPhase;
    bool bClockPolarity;
    VmSpiPathSelect_e ePathSelect;
    VmSpiSslPathSelect_e eSslPathSelect;
    VmGpioCs_t tGpioCs;
    VmFsSpiOptions_t tFsOpt;
    VmPagingSpiOptions_t tPagingOpt;
    VmMasterSpiOptions_t tMasterOpt;
} VmSpiSettings_t;

/**
 * @brief SPI bus operation structure
 */
typedef struct
{
    VmSpiErrorCode_e (* PfnOpInit)(VmSpiSettings_t *pSettings);
    VmSpiErrorCode_e (* PfnOpDeInit)(void);
    VmSpiErrorCode_e (* PfnOpTransactionStart)(VmSpiSettings_t *pSettings);
    VmSpiErrorCode_e (* PfnOpTransactionEnd)(VmSpiSettings_t *pSettings);
    VmSpiErrorCode_e (* PfnOpWrite)(VmSpiSettings_t *pSettings, const void *pDataToWrite, u32 nNbBytes);
    VmSpiErrorCode_e (* PfnOpRead)(VmSpiSettings_t *pSettings, void *pDataToRead, u32 nNbBytes);
VmSpiErrorCode_e (* PfnOpWriteAndRead)(VmSpiSettings_t *pSettings, const void *pDataToWrite, u32 nNbWBytes, void *pDataToRead, u32 nNbRBytes);
    VmSpiErrorCode_e (* PfnOpDMAWrite)(VmSpiSettings_t *pSettings, const void *pDataToWrite, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
    VmSpiErrorCode_e (* PfnOpDMARead)(VmSpiSettings_t *pSettings, void *pDataToRead, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
VmSpiErrorCode_e (* PfnOpWriteMSB2321)(VmSpiSettings_t *pSettings,u32 nStarAddr, const void *pDataToWrite, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
VmSpiErrorCode_e (* PfnOpReadMSB2321)(VmSpiSettings_t *pSettings,u32 nStarAddr, void *pDataToRead, u32 nNbBytes, void (*pfnDmaCallBack)(u32 nChannel));
} VmSpiOperations_t;

#endif /* __SDK_SIMULATION__ */
#endif /* __DRV_VM_SPI_H__*/

