/**************************************************************************
 *  kernel_uart.h
 *--------------------------------------------------------------------------
 *  Scope: UART related definitions
 *
 ***************************************************************************/
 
#ifndef __KERNEL_UART_H__
#define __KERNEL_UART_H__

#include "cpu_mem_map.hc"

/****************************************************************************/
/*   UART registers and access macros                                       */
/****************************************************************************/

typedef struct FURUart_s
{
  u32 u32_DLL_THR_RBR;      // 0x00
  u32 u32_reserve0;
  u32 u32_DLH_IER;          // 0x02
  u32 u32_reserve1;
  u32 u32_IIR_FCR;          // 0x04
  u32 u32_reserve2;
  u32 u32_LCR;              // 0x06
  u32 u32_reserve3;
  u32 u32_MCR;              // 0x08
  u32 u32_reserve4;
  u32 u32_LSR;              // 0x0A
  u32 u32_reserve5;
  u32 u32_MSR;              // 0x0C
  u32 u32_reserve6;
  u32 u32_USR;              // 0x0E
  u32 u32_reserve7;
  u32 u32_TFL;              // 0x10
  u32 u32_reserve8;
  u32 u32_RFL;              // 0x12
} FURUart_t;

/*** RBR register ***/
#define UART_RX_DATA_MSK        (0x00FF)

/*** THR register ***/
#define UART_TX_DATA_MSK        (0x00FF)

/* Interrupt Enable Register (IER)*/
#define UART_IER_RDICTI         0x01    /* Received Data Available & Character Timeout Interrupt */
#define UART_IER_THRI           0x02    /* Transmitter Holding Register Empty Interrupt */
#define UART_IER_RLSI           0x04    /* Receiver Line Status Interrupt */
#define UART_IER_MSI            0x08    /* Modem Status Interrupt */
#define UART_IER_PTHRI          0x80    /* Programmable THRE Interrupt */

/* Interrupt Identification Register (IIR) */
#define UART_IIR_MSI            0x00    /* 0000: Modem Status */
#define UART_IIR_NO_INT         0x01    /* 0001: No pending interrupts */
#define UART_IIR_THRI           0x02    /* 0010: Transmitter Holding Register Empty */
#define UART_IIR_RDI            0x04    /* 0100: Receiver Data Available */
#define UART_IIR_RLSI           0x06    /* 0110: Receiver Line Status */
#define UART_IIR_BUSY           0x07    /* 0111: Busy detect indication (try to write LCR while UART is busy) */ // CHECK : Removed?
#define UART_IIR_RX_TIMEOUT     0x0C    /* 1100: Character timeout */
#define UART_IIR_ID_MASK        0x0F    /* Mask Bit[3:0] for IIR */

/* FIFO Control Register (FCR) */
#define UART_FCR_FIFO_ENABLE    0x01    /* FIFO enable */
#define UART_FCR_CLEAR_RCVR     0x02    /* Clear & Reset Rx FIFO buffer */
#define UART_FCR_CLEAR_XMIT     0x04    /* Clear & Reset Tx FIFO buffer */
#define UART_FCR_TRIGGER_TX_L0  0x00    /* Trigger Write when empty */
#define UART_FCR_TRIGGER_TX_L1  0x10    /* Trigger Write when 2 characters */
#define UART_FCR_TRIGGER_TX_L2  0x20    /* Trigger Write when 1/4 full */
#define UART_FCR_TRIGGER_TX_L3  0x30    /* Trigger Write when 1/2 full */
#define UART_FCR_TRIGGER_RX_L0  0x00    /* Trigger Read when there is 1 char*/
#define UART_FCR_TRIGGER_RX_L1  0x40    /* Trigger Read when 1/4 full */
#define UART_FCR_TRIGGER_RX_L2  0x80    /* Trigger Read when 1/2 full */
#define UART_FCR_TRIGGER_RX_L3  0xC0    /* Trigger Read when 2 less then full  */

/* Line Control Register (LCR) */
#define UART_LCR_WL_MASK        0x03    /* Word length mask */
#define UART_LCR_WLEN5          0x00    /* Word length is 5 bits */
#define UART_LCR_WLEN6          0x01    /* Word length is 6 bits */
#define UART_LCR_WLEN7          0x02    /* Word length is 7 bits */
#define UART_LCR_WLEN8          0x03    /* Word length is 8 bits */
#define UART_LCR_STOP_MASK      0x04    /* Stop bit mask */
#define UART_LCR_STOP1          0x00    /* Stop length is 1 bit */
#define UART_LCR_STOP2          0x04    /* Stop length is 1.5 bits (5-bit char), 2 bits (otherwise) */
#define UART_LCR_PARITY_EN      0x08    /* Parity Enable */
#define UART_LCR_PARITY_SEL     0x10    /* Even Parity Select */
#define UART_LCR_SBC            0x40    /* Set break control */
#define UART_LCR_DLAB           0x80    /* Divisor Latch Access bit, 1 = Divisor Latch, 0 = Normal Register */

/* Modem Control Register (MCR) */
#define UART_MCR_DTR            0x01    /* DTR complement */
#define UART_MCR_RTS            0x02    /* RTS complement */
#define UART_MCR_OUT1           0x04    /* Out1 complement */
#define UART_MCR_OUT2           0x08    /* Out2 complement */
#define UART_MCR_LOOPBACK       0x10    /* Enable loopback test mode */
#define UART_MCR_AFCE           0x20    /* Auto flow control enable */

/* Line Status Register (LSR) */
#define UART_LSR_DR             0x01    /* Data Ready, at least one char in FIFO buffer*/
#define UART_LSR_OE             0x02    /* Overrun Error, FIFO buffer is full */
#define UART_LSR_PE             0x04    /* Parity Error */
#define UART_LSR_FE             0x08    /* Framing Error, no valid stop bit */
#define UART_LSR_BI             0x10    /* Break Interrupt */
#define UART_LSR_THRE           0x20    /* Tx FIFO buffer is empty*/
#define UART_LSR_TEMT           0x40    /* Both TX FIFO buffer & shift register are empty */
#define UART_LSR_RX_ERROR       0x80    /* Rx FIFO buffer error */

/* Modem Status Register (MSR) */
#define UART_MSR_DCTS           0x01    // Delta CTS
#define UART_MSR_DDSR           0x02    // Delta DSR
#define UART_MSR_TERI           0x04    // Trailing edge ring indicator
#define UART_MSR_DDCD           0x08    // Delta DCD
#define UART_MSR_CTS_COMP       0x10    // Clear to Send
#define UART_MSR_DSR_COMP       0x20    // Data Set Ready
#define UART_MSR_RI_COMP        0x40    // Ring Indicator
#define UART_MSR_DCD_COMP       0x80    // Data Carrier Detect

/* USR */
#define UART_USR_BUSY             0x01
#define UART_USR_TXFIFO_NOT_FULL  0x02
#define UART_USR_TXFIFO_EMPTY     0x04
#define UART_USR_RXFIFO_NOT_EMPTY 0x08
#define UART_USR_RXFIFO_FULL      0x10

/*** TFL:Transmit FIFO Level ***/
#define UART_TX_FIFO_LVL_MASK   (0x003F)

/*** RFL:Receive FIFO Level ***/
#define UART_RX_FIFO_LVL_MASK   (0x003F)

extern volatile FURUart_t* const g_ptFURUart0;
extern volatile FURUart_t* const g_ptFURUart1;
extern volatile FURUart_t* const g_ptFURUart2;
extern volatile FURUart_t* const g_ptFURFUart;

/****************************************************************************/
/*   UART DMA registers and access macros                                   */
/****************************************************************************/

typedef struct FURDMA_s
{
    u32 u32_hwSetting;
    u32 u32_intrThres;
    u32 u32_txBufBaseH;
    u32 u32_txBufBaseL;
    u32 u32_txBufSize;
    u32 u32_txBufRptr;
    u32 u32_txBufWptr;
    u32 u32_txTimeOut;
    u32 u32_rxBufBaseH;
    u32 u32_rxBufBaseL;
    u32 u32_rxBufSize;
    u32 u32_rxBufWptr;
    u32 u32_rxTimeOut;
    u32 u32_dmaInt;
    u32 reserve0;
    u32 reserve1;
} FURDMA_t;

/* HW setting */
#define FURDMA_RX_BUSY          (0x0001<<13)
#define FURDMA_TX_BUSY          (0x0001<<12)
#define FURDMA_RX_OP_MODE       (0x0001<<11)
#define FURDMA_RX_SW_RST        (0x0001<<7)
#define FURDMA_TX_SW_RST        (0x0001<<6)
#define FURDMA_RX_ENDIAN        (0x0001<<5)
#define FURDMA_TX_ENDIAN        (0x0001<<4)
#define FURDMA_RX_EN            (0x0001<<3)
#define FURDMA_TX_EN            (0x0001<<2)
#define FURDMA_URDMA_MODE       (0x0001<<1)
#define FURDMA_SW_RST           (0x0001<<0)

/* Interrupt status */
#define FURDMA_TX_INTR          (0x0001<<15)
#define FURDMA_TX_INT_EN        (0x0001<<9)
#define FURDMA_TX_INT_CLR       (0x0001<<8)
#define FURDMA_RX_INTR          (0x0001<<7)
#define FURDMA_RX_INT2_THRES    (0x0001<<5)
#define FURDMA_RX_INT1_TIMEOUT  (0x0001<<4)
#define FURDMA_RX_INT2_EN       (0x0001<<2)
#define FURDMA_RX_INT1_EN       (0x0001<<1)
#define FURDMA_RX_INT_CLR       (0x0001<<0)

extern volatile FURDMA_t *const g_ptFURDMA;

#endif /* __KERNEL_UART_H__ */

