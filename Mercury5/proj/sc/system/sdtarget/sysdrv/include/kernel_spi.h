/*******************************************************************************
 *  kernel_spi.h
 *------------------------------------------------------------------------------
 *  Scope: SPI related definitions
 *
 ******************************************************************************/

#ifndef __KERNEL_SPI_H__
#define __KERNEL_SPI_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "cpu_mem_map.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/* configuration register */
#define SPI_DUPLEX_MODE_FULL    (1 << 31)   /* mode half/full duplex */
#define SPI_DUPLEX_MODE_HALF    (0 << 31)
#define SPI_APDDIS              (1 << 30)   /* Auto Power Down Disable */
#define SPI_TFR_MODE_DMA        (1 << 29)   /* transfer mode */
#define SPI_TFR_MODE_CPU        (0 << 29)
#define SPI_BIG_ENDIAN          (1 << 28)   /* endian alignment */
#define SPI_LITTLE_ENDIAN       (0 << 28)
#define SPI_DBL_MODE            (1 << 27)   /* double byte mode */
#define SPI_MLOUT               (1 << 26)   /* MSB or LSB first transmitted data */
#define SPI_MLIN                (1 << 25)   /* MSB or LSB first received data */
#define SPI_SSL_DST_SSL0        (0 << 24)   /* Slave Select Destination*/
#define SPI_SSL_DST_SSL1        (1 << 24)   /* Slave Select Destination*/
#define SPI_SSL_MODE_MSK        (1 << 23)
#define SPI_SSL_MODE_SW         (0 << 23)   /* Slave Select Mode software/hardware */
#define SPI_SSL_MODE_HW         (1 << 23)   /* Slave Select Mode software/hardware */
#define SPI_SSL_POL_LOW         (0 << 22)   /* Slave Select Polarity low */
#define SPI_SSL_POL_HIGH        (1 << 22)   /* Slave Select Polarity high */
/* inter word mode determines the ssl & sclk level between 2 consecutive words */
/* 0 SSL is keep active / SCLK is shut down */
/* 1 SSL becomes inactive / SCLK is remained */
/* 2 SSL becomes inactive / SCLK is shut down */
#define SPI_ITR_MODE_POS        20
#define SPI_ITR_MODE_MASK       (3 << SPI_ITR_MODE_POS)

#define SPI_ITR_DEL_POS         16          /* inter word delay */
#define SPI_ITR_DEL_MASK        (0x0F << SPI_ITR_DEL_POS)
#define SPI_MODE_MASTER         (0 << 15)   /* spi mode */
#define SPI_MODE_SLAVE          (1 << 15)   /* spi mode */
#define SPI_BR_POS              12          /* data byte rate */
#define SPI_BR_MASK             (0x07 << SPI_BR_POS)

/*  Stop Clock Latency Indicates the number of SCLK advance or offset periods related to SSL starting*/
#define SPI_SPCL_POS            8
#define SPI_SPCL_MASK           (0x0F << SPI_SPCL_POS)

#define SPI_STCL_POS            4           /*  Start Clock Latency */
#define SPI_STCL_MASK           (0x0F << SPI_STCL_POS)
#define SPI_CSPPOS              (1 << 3)    /* clock stop  */
#define SPI_CSTPOS              (1 << 2)    /* clock start */
#define SPI_CPHA                (1 << 1)    /* clock phase */
#define SPI_CPOL                (1 << 0)    /* clock polarity */

/* control register */
#define SPI_DTL_POS             3           /* data transfer length */
#define SPI_DTL_MASK            (0x0F << SPI_DTL_POS)   /* data transfer length */
#define SPI_CYCLE_STOP          (1 << 2)    /* cycle stop */
#define SPI_READ                (1 << 1)    /* read transfer mode */
#define SPI_WRITE               (1 << 0)    /* write  transfer mode */
#define SPI_SSL_INACT_POL_EN    (1 << 8)
#define SPI_SSL0_INACT_POL_HIGH (1 << 9)
#define SPI_SSL0_INACT_POL_LOW  (0 << 9)
#define SPI_SSL1_INACT_POL_HIGH (1 << 10)
#define SPI_SSL1_INACT_POL_LOW  (0 << 10)

/* NWORD register */
#define SPI_MAX_NWORD           0x8000
#define SPI_RX_NWORD_POS        16          /* number of word to receive */
#define SPI_RX_NWORD_MASK       (0x7FFF << SPI_RX_NWORD_POS)
#define SPI_TX_NWORD_POS        0           /* number of word to transmit */
#define SPI_TX_NWORD_MASK       (0x7FFF << SPI_TX_NWORD_POS)

/* SPI Status*/
#define SPI_SPTE                (1 << 1)    /* Transmit register empty */
#define SPI_SPRF                (1 << 0)    /* Receiver register full */

/* Interrupt status, mask, and clear */
#define SPI_INTBIT_WAKEUP       (1 << 11)   /* wake up required */
#define SPI_INTBIT_END          (1 << 10)   /* spi cycle end */
#define SPI_INTBIT_SSLSP        (1 << 9)    /* ssl stop detect */
#define SPI_INTBIT_SSLST        (1 << 8)    /* ssl start detect */
#define SPI_INTBIT_TX_OVR       (1 << 7)    /* Tx Overrun */
#define SPI_INTBIT_RX_OVR       (1 << 6)    /* Rx Overrun */
#define SPI_INTBIT_TX_OVF       (1 << 5)    /* Tx Overflow */
#define SPI_INTBIT_RX_OVF       (1 << 4)    /* Tx Overflow */
#define SPI_INTBIT_TX_NWC       (1 << 3)    /* Tx N word completed */
#define SPI_INTBIT_RX_NWC       (1 << 2)    /* Rx N word completed */
#define SPI_INTBIT_SPTE         (1 << 1)    /* Transmitter Register Empty */
#define SPI_INTBIT_SPRF         (1 << 0)    /* Receiver Register Full */


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/************************************************/
/* SPI registers definition                     */
/************************************************/
typedef struct OSpi_s
{
    u32 Config;
    u32 Control;
    u32 NWord;
    u32 RxTx;
    u32 Status;
    u32 Spare;
    u32 InterruptMask;
    u32 InterruptStatus;
    u32 InterruptClear;
    u32 RawInterruptStatus;
} OSpi_t;

#endif // __KERNEL_SPI_H__
