/*******************************************************************************
 *  kernel_uart.h
 *------------------------------------------------------------------------------
 *  Scope: UART related definitions
 *
 ******************************************************************************/

#ifndef __KERNEL_UART_H__
#define __KERNEL_UART_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "cpu_mem_map.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/* RBR register */
#define UART_RX_DATA_MSK             (0x00FF<<0)

/* THR register */
#define UART_TX_DATA_MSK             (0x00FF<<0)

/* IIR Masks register */
#define UART_OVERRUN_ERROR_INT       (0x0001<<0)
#define UART_PARITY_ERROR_INT        (0x0001<<1)
#define UART_FRAMING_ERROR_INT       (0x0001<<2)
#define UART_BREAK_DETECTED_INT      (0x0001<<3)
#define UART_RX_DATA_INT             (0x0001<<4)
#define UART_RX_CHAR_TIME_OUT        (0x0001<<5)
#define UART_THRE_SENDING_INT        (0x0001<<6)    /* and sending ended */
#define UART_TSRE_INT                (0x0001<<7)    /* and sending ended */
#define UART_MODEM_STATUS_INT        (0x0001<<8)
#define UART_RX_XOFF_INT             (0x0001<<9)
#define UART_SPEC_CHAR_INT           (0x0001<<10)
#define UART_AUTO_BAUD_INT           (0x0001<<11)
#define UART_AUTO_FRAM_INT           (0x0001<<12)

/* IIR register */
#define UART_PENDING_INT_MSK         (0x0001<<0)
#define UART_INT_LEVEL_MSK           (0x0003<<1)
#define UART_INT_LEVEL_POS           1
#define UART_TIMEOUT_INT             (0x0001<<3)
#define UART_EXTENDED_FUNC_INT       (0x0001<<4)

/* FCR register */
#define UART_RX_FIFO_ENABLE          (0x0001<<0)
#define UART_RX_FIFO_RESET           (0x0001<<1)
// bit 2 reserved
#define UART_RX_FIFO_TRIG_MSK        (0x001f<<3)
#define UART_RX_FIFO_TRIG_POS        3

#define UART_TX_FIFO_ENABLE          (0x0001<<8)
#define UART_TX_FIFO_RESET           (0x0001<<9)

#define UART_TX_FIFO_TRIG_MSK        (0x001f<<11)
#define UART_TX_FIFO_TRIG_POS        11

/* LCR register */
#define UART_WORD_LENGTH_MSK         (0x0003<<0)
#define UART_WORD_LENGTH_POS         0
#define UART_NB_STOP_BIT             (0x0001<<2)
#define UART_PARITY_ENA              (0x0001<<3)
#define UART_EVEN_PARITY_ENA         (0x0001<<4)
#define UART_STICK_PARITY_ENA        (0x0001<<5)
#define UART_BREAK_CTRL              (0x0001<<6)
#define UART_DIV_LATCH_ACCESS        (0x0001<<7)

/* MCR register */
#define UART_DTR_ACTIVE              (0x0001<<0)
#define UART_RTS_ACTIVE              (0x0001<<1)
#define UART_LOOP_BACK               (0x0001<<4)
#define UART_AUTO_RTS_CTS            (0x0001<<5)

/* Line Status register Mask */
#define UART_BREAK_ERROR             (0x0001<<0)
#define UART_FRAMING_ERROR           (0x0001<<1)
#define UART_PARITY_ERROR            (0x0001<<2)
#define UART_OVERRUN_ERROR           (0x0001<<3)
#define UART_RX_FIFO_ERROR           (0x0001<<4)
// bits 5:7 reserved
#define UART_DELTA_CTS               (0x0001<<8)
#define UART_DELTA_DSR               (0x0001<<9)

/* MSR register */
#define UART_DATA_READY              (0x0001<<0)
#define UART_RX_FIFO_EMP             (0x0001<<1)
#define UART_TX_FIFO_FULL            (0x0001<<2)
#define UART_RX_FIFO_FULL            (0x0001<<3)
#define UART_THR_EMPTY               (0x0001<<4)
#define UART_TRANSMITTER_EMPTY       (0x0001<<5)
// bit 6 reserved
#define UART_RX_BUSY                 (0x0001<<7)
#define UART_CTS_STATE               (0x0001<<8)

/* SCR register */
#define UART_SCRATCH_MSK             (0x00FF<<0)

/* DLL register */
#define UART_DIV_LATCH_LSB_MSK       (0x00FF<<0)

/* DLM register */
#define UART_DIV_LATCH_MSB_MSK       (0xFF00<<0)

/* EFR register */
#define UART_AUTOFLOW_CTRL_MSK       (0x0003<<0)
#define UART_AUTOFLOW_CTRL_POS       0
#define UART_CHAR_REC_ENA            (0x0001<<2)
#define UART_AUTO_BAUD_ENA           (0x0001<<3)
#define UART_AUTO_FRAM_ENA           (0x0001<<4)
#define UART_EXT_LOOP_BACK_ENA       (0x0001<<5)

/* EFS register */
#define UART_XOFF_STATUS_MSK         (0x0003<<0)
#define UART_XOFF_STATUS_POS         0
#define UART_SPEC_CHAR_RECVD         (0x0001<<2)
#define UART_AUTO_BAUD_COMPL         (0x0001<<3)
#define UART_AUTO_FRAM_COMPL         (0x0001<<4)
#define UART_GOOD_FRAMING            (0x0001<<5)

/* XON1 register */
#define UART_XON1_VALUE_MSK          (0x00FF<<0)

/* XON2 register */
#define UART_XON2_VALUE_MSK          (0x00FF<<0)

/* XOFF1 register */
#define UART_XOFF1_VALUE_MSK         (0x00FF<<0)

/* XOFF2 register */
#define UART_XOFF2_VALUE_MSK         (0x00FF<<0)

/* SRC register */
#define UART_CHAR_REC_VALUE_MSK      (0x00FF<<0)

/* XON2 register */
#define UART_CHAR_REC_MSK_VALUE_MSK  (0x00FF<<0)


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef struct W5Uart_s
{
   union {
      u32   u32_RBR;
      u32   u32_THR;
   } s_IO;
   u32 u32_LMSR_STATUS; // 0x04
   u32 u32_LMSR_CLEAR;  // 0x08
   u32 u32_LMFR;        // 0x0C
   u32 u32_DLM_DLL;     // 0x10
   u32 u32_LCR;
   u32 u32_FCR;         // 0x18
   u32 u32_DMACR;
   u32 u32_IIR_STATUS;
   u32 u32_IIR     ;
   u32 u32_IIR_RAW_STATUS;
   u32 u32_IIR_CLEAR;
   u32 u32_MCR;
   u32 u32_SCR;
   u32 u32_EFR;        
   u32 u32_EFS_STATUS; 
   u32 u32_EFS_CLEAR;  
   u32 u32_XON1;       
   u32 u32_XON2;       
   u32 u32_XOFF1;      
   u32 u32_XOFF2;      
   u32 u32_SRC;        
   u32 u32_MSK_SRC;    
   u32 u32_IRDA_CFG;
}  W5Uart_t;

#endif  //  __KERNEL_UART_H__
