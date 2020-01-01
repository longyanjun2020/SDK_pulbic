////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
* @file     hal_fuart.h
* @version
* @Platform M5
* @brief    This file defines the HAL UART driver interface
*
*/

#ifndef __HAL_FUART_H__
#define __HAL_FUART_H__

#include "hal_int_irq_pub.h"
#include "sys_wmh_v24.hi"

/*--------------------------------------------------------------------------*/
/* Enumeration Definition                                                   */
/*--------------------------------------------------------------------------*/

/*
 * UART Register Control ID
 * Use: hal_uart_GetRegValue()
 */
typedef enum {
    HUC_UART_REG_IER = 0,
    HUC_UART_REG_IIR,
    HUC_UART_REG_LCR,
    HUC_UART_REG_MCR,
    HUC_UART_REG_LSR,
    HUC_UART_REG_MSR,
    HUC_UART_REG_USR
} Uart_REG_t;

/* Platform UART Port List */
typedef enum {
    HAL_UART1 = 1,    ///< Same as V24 UART1 defined
    HAL_UART2 = 2,    ///< Same as V24 UART2 defined
    HAL_UART3 = 3,
    HAL_FUART = 4,
    HAL_UART_UNKNOWN
} HAL_UART_NUM_t;

/*--------------------------------------------------------------------------*/
/* Basic Definition                                                         */
/*--------------------------------------------------------------------------*/

#define HAL_UART_NUM            (4)

/* UART RX TX FIFO Length */
#define HUC_UART_RX_FIFO_SIZE   (16)
#define HUC_UART_TX_FIFO_SIZE   (16)

/*--------------------------------------------------------------------------*/
/* UART Register Bit Definition                                             */
/*--------------------------------------------------------------------------*/

//******************************
// UART Interrupt Control
//******************************

/*
 * UART Interrupt register Mask (Hardware Dependence)
 */
#define HUC_UART_IER_RX_IT              UART_IER_RDICTI
#define HUC_UART_IER_TX_IT              (UART_IER_THRI | UART_IER_PTHRI)
#define HUC_UART_IER_LSR_IT             UART_IER_RLSI
#define HUC_UART_IER_MSR_IT             UART_IER_MSI

#define HUC_V24_IT_MASK                 (HUC_UART_IER_RX_IT  | HUC_UART_IER_TX_IT  |\
                                         HUC_UART_IER_LSR_IT | HUC_UART_IER_MSR_IT )

/*
 * UART Line Status register Mask (Hardware Dependence)
 */
#define HUC_UART_BREAK_DETECTED         UART_LSR_BI
#define HUC_UART_OVERRUN_ERROR          UART_LSR_OE
#define HUC_UART_PARITY_ERROR           UART_LSR_PE
#define HUC_UART_FRAMING_ERROR          UART_LSR_FE
#define HUC_UART_RX_ERROR               UART_LSR_RX_ERROR

/*
 * UART Interrupt Source Macro (Hardware Dependence)
 */
#define HAL_UART_GET_IT_SOURCE(OUart)	(hal_uart_ReadIIR(OUart) & UART_IIR_ID_MASK)

/*
 * UART Interrupt Source Bit Mask (Hardware Dependence) only for clear, not required now
 */
#define HUC_UART_RX_FULL                UART_IIR_RDI
#define HUC_UART_RX_CHAR_TIMEOUT        UART_IIR_RX_TIMEOUT
#define HUC_UART_TX_EMPTY               UART_IIR_THRI
#define HUC_UART_MSR_EVENT              UART_IIR_MSI
#define HUC_UART_LSR_EVENT              UART_IIR_RLSI
#define HUC_UART_BUSY_DETECT            UART_IIR_BUSY

/*
 *  Interrupt Source Check, In ISR for checking pending cause.
 */
#define HAL_IS_UART_RX_FIFO_AVALIABLE(Source)   ((Source == HUC_UART_RX_FULL) || (Source ==HUC_UART_RX_CHAR_TIMEOUT))
#define HAL_IS_UART_TX_FIFO_EMPTY(Source)       (Source == HUC_UART_TX_EMPTY)
#define HAL_IS_UART_LSR_EVENT(Source)           (Source == HUC_UART_LSR_EVENT)
#define HAL_IS_UART_MSR_EVENT(Source)           (Source == HUC_UART_MSR_EVENT)
#define HAL_IS_UART_RXXOFF_EVENT(Source)        FALSE//(Source & HUC_UART_RX_XOFF_IT)
#define HAL_IS_UART_BUSY_DETECT(Source)         (Source == HUC_UART_BUSY_DETECT)  
/*
 * UART Busy Check (Hardware Dependence)
 */
#define HAL_UART_IS_BUSY(OUart)                 ((OUart == NULL) ? FALSE : ((hal_uart_ReadUSR(OUart) & UART_USR_BUSY) ? TRUE : FALSE))

/*
 * UART Interrupt Pending Check (Hardware Dependence)
 */
#define HAL_UART_IS_IT_PENDING(s)       ((s == UART_IIR_NO_INT) ? FALSE : TRUE)

/*--------------------------------------------------------------------------*/
/* Define Baud Rate Setting                                                 */
/*--------------------------------------------------------------------------*/

/*
 * UART Source Clock Setting (Hardware Dependence)
 */
#if defined( __MV5_FPGA__)
#define HUC_UART_CLK                (12000000)
#else
#define HUC_UART_CLK                (172800000)
#endif

/*
 * Divisor computation with Baudrate (Hardware Dependence)
 */
#define COMPUTE_DIVISOR(Baudrate)   ((u16)((U64)(HUC_UART_CLK + 8*(Baudrate))/(16 * (Baudrate)) ))

/*
 * Baudrate Divisor Value (Hardware Dependance)
 */
#define HUC_BAUD_75                 0//144000 not support       ///< 75 bps
#define HUC_BAUD_300                COMPUTE_DIVISOR(300)        ///< 300 bps
#define HUC_BAUD_600                COMPUTE_DIVISOR(600)        ///< 600 bps
#define HUC_BAUD_1200               COMPUTE_DIVISOR(1200)       ///< 1200 bps
#define HUC_BAUD_2400               COMPUTE_DIVISOR(2400)       ///< 2400 bps
#define HUC_BAUD_4800               COMPUTE_DIVISOR(4800)       ///< 4800 bps
#define HUC_BAUD_9600               COMPUTE_DIVISOR(9600)       ///< 9600 bps
#define HUC_BAUD_19200              COMPUTE_DIVISOR(19200)      ///< 19200 bps
#define HUC_BAUD_38400              COMPUTE_DIVISOR(38400)      ///< 38400 bps
#define HUC_BAUD_57600              COMPUTE_DIVISOR(57600)      ///< 57600 bps
#define HUC_BAUD_115200             COMPUTE_DIVISOR(115200)     ///< 115200 bps
#define HUC_BAUD_230400             COMPUTE_DIVISOR(230400)     ///< 230400 bps
#define HUC_BAUD_460800             COMPUTE_DIVISOR(460800)     ///< 160800 bps
#define HUC_BAUD_921600             COMPUTE_DIVISOR(921600)     ///< 921600 bps

/*--------------------------------------------------------------------------*/
/* Basical read/write actions on UART registers                             */
/*--------------------------------------------------------------------------*/

/*
 *  UART IP Register Structure Prototype
 */
#define HAL_UART_TYPE(obj)              ((volatile FURUart_t *)obj)
#define HAL_UART_DMA_TYPE(obj)          ((volatile FURDMA_t  *)obj)

/*
 *  UART Object (Hardware Dependence)
 */
#define HAL_UART_GET_OBJ(uart_id)       ((uart_id == HAL_UART1) ? g_ptFURUart0 : ((uart_id == HAL_UART2) ? g_ptFURUart1 : ((uart_id == HAL_UART3) ? g_ptFURUart2 : g_ptFURFUart)))

/*
 *  UART FIFO read/write
 */
#define hal_uart_write_char(uart, a)    (HAL_UART_TYPE(uart)->u32_DLL_THR_RBR = (a))
#define hal_uart_read_char(uart)        (HAL_UART_TYPE(uart)->u32_DLL_THR_RBR)

/*
 *  UART Interrupt Control
 */
#define hal_uart_ReadIIR(uart)          (HAL_UART_TYPE(uart)->u32_IIR_FCR)
#define hal_uart_WriteIIR_Mask(uart, a) (HAL_UART_TYPE(uart)->u32_DLH_IER = (a)) //Mask =1, enable interrupt
#define hal_uart_ReadIIR_Mask(uart)     (HAL_UART_TYPE(uart)->u32_DLH_IER)
#define hal_uart_WriteIER(uart, a)     	(HAL_UART_TYPE(uart)->u32_DLH_IER = (a))
#define hal_uart_ReadIIR_Raw(uart)
#define hal_uart_WriteIIR_Clear(uart, a)

/*
 * UART State Control
 */
#define hal_uart_ReadUSR(uart)          (HAL_UART_TYPE(uart)->u32_USR & 0xFF)
#define hal_uart_ReadLSR(uart)          (HAL_UART_TYPE(uart)->u32_LSR & 0xFF)
#define hal_uart_ReadMSR(uart)          (HAL_UART_TYPE(uart)->u32_MSR & 0xFF)

/*
 * UART Configuration, Line, Modem
 */
#define hal_uart_WriteDLL(uart, a)      (HAL_UART_TYPE(uart)->u32_DLL_THR_RBR  = (a))
#define hal_uart_WriteDLH(uart, a)      (HAL_UART_TYPE(uart)->u32_DLH_IER = (a))
#define hal_uart_ReadLCR(uart)          (HAL_UART_TYPE(uart)->u32_LCR)
#define hal_uart_WriteLCR(uart, a)      (HAL_UART_TYPE(uart)->u32_LCR = (a))
#define hal_uart_WriteFCR(uart, a)      (HAL_UART_TYPE(uart)->u32_IIR_FCR = (a))
#define hal_uart_WriteFCR_or(uart, a)   (HAL_UART_TYPE(uart)->u32_IIR_FCR |= (a))
#define hal_uart_WriteMCR(uart, a)      (HAL_UART_TYPE(uart)->u32_MCR = (a))
#define hal_uart_ReadMCR(uart)          (HAL_UART_TYPE(uart)->u32_MCR)

/*
 * XAUTO_MODE setting
 */
#define hal_uart_ReadEFSS(uart)    

#define HUC_UART_RX_IT_BUF_LEN          1024   /* must be a power of 2 */
#define HUC_UART_TX_IT_BUF_LEN          2048

/* Receiver FIFO Trigger Level */
#define HUC_RCV_LVL_0                  (UART_FCR_TRIGGER_RX_L0 | UART_FCR_FIFO_ENABLE)
#define HUC_RCV_LVL_1                  (UART_FCR_TRIGGER_RX_L1 | UART_FCR_FIFO_ENABLE)
#define HUC_RCV_LVL_2                  (UART_FCR_TRIGGER_RX_L2 | UART_FCR_FIFO_ENABLE)
#define HUC_RCV_LVL_3                  (UART_FCR_TRIGGER_RX_L3 | UART_FCR_FIFO_ENABLE)

#define HUC_UART_TRIGGER_LEVEL          HUC_RCV_LVL_3

/* Transmit FIFO Trigger */
#define HUC_UART_TX_FIFO_NOT_FULL       UART_USR_TXFIFO_NOT_FULL

/*--------------------------------------------------------------------------*/
/* HAL UART Macros, for V24.                                                */
/*--------------------------------------------------------------------------*/

#define HAL_UART_SET_RTS_ON(uart)               (hal_uart_WriteMCR( uart, hal_uart_ReadMCR(uart) |  UART_MCR_RTS ))
#define HAL_UART_SET_RTS_OFF(uart)              (hal_uart_WriteMCR( uart, hal_uart_ReadMCR(uart) & ~UART_MCR_RTS ))
#define HAL_UART_SET_DTR_ON(uart)               (hal_uart_WriteMCR( uart, hal_uart_ReadMCR(uart) |  UART_MCR_DTR ))
#define HAL_UART_SET_DTR_OFF(uart)              (hal_uart_WriteMCR( uart, hal_uart_ReadMCR(uart) & ~UART_MCR_DTR ))
#define HAL_UART_IS_CTS_ON(uart)                ((hal_uart_ReadMSR(uart) & UART_MSR_CTS_COMP)?TRUE:FALSE )
#define HAL_UART_IS_CTS_CHANGE(msr, available)  ((available==FALSE)?(FALSE):( ((msr) & UART_MSR_DCTS)?TRUE:FALSE ))
#define HAL_UART_IS_DSR_CHANGE(msr)             (((msr) & UART_MSR_DDSR)?TRUE:FALSE )
#define HAL_UART__IS_CTS_ON(msr, available)     ((available==FALSE )?TRUE:( ((msr) & UART_MSR_CTS_COMP)?TRUE:FALSE ))
#define HAL_UART__IS_DSR_ON(msr)                (((msr) & UART_MSR_DSR_COMP )?TRUE:FALSE)
#define HAL_UART_SET_DCD_ON(uart)
#define HAL_UART_SET_DCD_OFF(uart)
#define HAL_UART_CLEAR_IIR(uart)                 
#define HAL_UART_IS_BREAK(lsr)                  (lsr & HUC_UART_BREAK_DETECTED )
#define HAL_UART_IS_OVERRUN(lsr)                (lsr & HUC_UART_OVERRUN_ERROR )
#define HAL_UART_IS_RX_ERROR(lsr)               (lsr & HUC_UART_RX_ERROR )
#define HAL_UART_SET_IT_MASK(uart, m)           (hal_uart_WriteIIR_Mask( uart, m ))
#define HAL_UART_SET_IT_SRC(uart, m)            (HAL_UART_TYPE(uart)->u32_DLH_IER |= (m))
#define HAL_UART_CLR_IT_SRC(uart, m)            (HAL_UART_TYPE(uart)->u32_DLH_IER &= ~(m))
#define HAL_UART_RX_FIFO_NOT_EMPTY(uart)        (hal_uart_ReadUSR(uart) & UART_USR_RXFIFO_NOT_EMPTY)
#define HAL_UART_TX_FIFO_NOT_FULL(uart)         (hal_uart_ReadUSR(uart) & UART_USR_TXFIFO_NOT_FULL)
#define HAL_UART_RX_FIFO_EMPTY(uart)            (~(hal_uart_ReadUSR(uart)) & UART_USR_RXFIFO_NOT_EMPTY)
#define HAL_UART_TX_FIFO_EMPTY(uart)            (hal_uart_ReadUSR(uart) & UART_USR_TXFIFO_EMPTY)
#define HAL_UART_CLR_RX_FIFO(uart, lvl)         (hal_uart_WriteFCR( uart, UART_FCR_CLEAR_RCVR | (lvl) ))
#define HAL_UART_CLR_TX_FIFO(uart, lvl)         (hal_uart_WriteFCR( uart, UART_FCR_CLEAR_XMIT | (lvl) ))
#define HAL_UART_ENABLE_FIFOs(uart)             (hal_uart_WriteFCR( uart, UART_FCR_FIFO_ENABLE | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT ))
#define HAL_UART_RESET_FIFOs(uart)              (HAL_UART_ENABLE_FIFOs( uart ))
#define HAL_UART_SET_TRIGGER_LVL(uart,lvl)      (hal_uart_WriteFCR( uart, UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT | (lvl) ))
#define HAL_UART_START_BREAK(uart)              (hal_uart_WriteLCR( uart, hal_uart_ReadLCR( uart ) |  UART_LCR_SBC ))
#define HAL_UART_STOP_BREAK(uart)               (hal_uart_WriteLCR( uart, hal_uart_ReadLCR( uart ) & ~UART_LCR_SBC ))
#define HAL_UART_SET_AUTO_RTS_CTS(uart)         (hal_uart_WriteMCR( uart, hal_uart_ReadMCR( uart ) | UART_MCR_AFCE ))
#define HAL_UART_OFF_AUTO_RTS_CTS(uart)         (hal_uart_WriteMCR( uart, hal_uart_ReadMCR( uart ) & ~UART_MCR_AFCE ))

/*
 *  UART XON/XOFF, G1 UART does not support.
 */
#ifdef __V24_SOFT_FC_XAUTO_MODE__
#define HAL_UART_SET_XAUTO_MODE_1(OUart)
#define HAL_UART_SET_XAUTO_MODE_DISABLED(OUart)
#define HAL_UART_SET_XON1_CHAR(OUart)
#define HAL_UART_RESET_XON1_CHAR(OUart)
#define HAL_UART_SET_XOFF1_CHAR(OUart)
#define HAL_UART_RESET_XOFF1_CHAR(OUart)
#define HAL_UART_CLEAR_XOFF_STATUS( OUart )
#define HAL_UART_IS_XOFF_RECEIVED( efss )
#endif

/*--------------------------------------------------------------------------*/
/* FUART DMA Registers Control                                              */
/*--------------------------------------------------------------------------*/

#define FURDMA_MODE_DMA(fuart)                  (fuart->u32_hwSetting |= FURDMA_URDMA_MODE)
#define FURDMA_MODE_MCU(fuart)                  (fuart->u32_hwSetting &= ~FURDMA_URDMA_MODE)
#define FURDMA_RX_MODE_DEFAULT(fuart)           (fuart->u32_hwSetting &= ~FURDMA_RX_OP_MODE)
#define FURDMA_RX_MODE_STOP(fuart)              (fuart->u32_hwSetting |= FURDMA_RX_OP_MODE)
#define FURDMA_RX_ENABLE(fuart)                 (fuart->u32_hwSetting |= FURDMA_RX_EN)
#define FURDMA_TX_ENABLE(fuart)                 (fuart->u32_hwSetting |= FURDMA_TX_EN)
#define FURDMA_RX_DISABLE(fuart)                (fuart->u32_hwSetting &= ~FURDMA_RX_EN)
#define FURDMA_TX_DISABLE(fuart)                (fuart->u32_hwSetting &= ~FURDMA_TX_EN)
#define FURDMA_SET_RX_BUF_H(fuart, base_h)      (fuart->u32_rxBufBaseH = (base_h))
#define FURDMA_SET_RX_BUF_L(fuart, base_l)      (fuart->u32_rxBufBaseL = (base_l))
#define FURDMA_SET_RX_BUF_SIZE(fuart, size)     (fuart->u32_rxBufSize = (size))
#define FURDMA_SET_RX_THRESHOLD(fuart, thres)   (fuart->u32_intrThres = (thres))
#define FURDMA_SET_TX_BUF_H(fuart, base_h)      (fuart->u32_txBufBaseH = (base_h))
#define FURDMA_SET_TX_BUF_L(fuart, base_l)      (fuart->u32_txBufBaseL = (base_l))
#define FURDMA_SET_TX_BUF_SIZE(fuart, size)     (fuart->u32_txBufSize = (size))
#define FURDMA_RX_INT1_ENABLE(fuart)            (fuart->u32_dmaInt |= FURDMA_RX_INT1_EN)
#define FURDMA_RX_INT2_ENABLE(fuart)            (fuart->u32_dmaInt |= FURDMA_RX_INT2_EN)
#define FURDMA_TX_INT_ENABLE(fuart)             (fuart->u32_dmaInt |= FURDMA_TX_INT_EN)
#define FURDMA_RX_INT1_DISABLE(fuart)           (fuart->u32_dmaInt &= ~FURDMA_RX_INT1_EN)
#define FURDMA_RX_INT2_DISABLE(fuart)           (fuart->u32_dmaInt &= ~FURDMA_RX_INT2_EN)
#define FURDMA_TX_INT_DISABLE(fuart)            (fuart->u32_dmaInt &= ~FURDMA_TX_INT_EN)
#define FURDMA_RX_INT_CLEAR(fuart)              (fuart->u32_dmaInt |= FURDMA_RX_INT_CLR)
#define FURDMA_TX_INT_CLEAR(fuart)              (fuart->u32_dmaInt |= FURDMA_TX_INT_CLR)
#define FURDMA_INT_STATUS(fuart)                (fuart->u32_dmaInt)
#define FURDMA_RX_WPTR(fuart)                   (fuart->u32_rxBufWptr)
#define FURDMA_TX_WPTR(fuart, ptr)              (fuart->u32_txBufWptr = (ptr))
#define FURDMA_TX_RPTR(fuart)                   (fuart->u32_txBufRptr)
#define FURDMA__IS_INT_OCCUR(status)            (status & ((FURDMA_TX_INTR)|(FURDMA_RX_INT2_THRES)|(FURDMA_RX_INT1_TIMEOUT)))
#define FURDMA__IS_RX_BUSY(fuart)               (fuart->u32_hwSetting & FURDMA_RX_BUSY)
#define FURDMA__IS_TX_BUSY(fuart)               (fuart->u32_hwSetting & FURDMA_TX_BUSY)
#define FURDMA_TX_EMPTY                         (FURDMA_TX_INTR)
#define FURDMA_RX_TIMEOUT                       (FURDMA_RX_INT1_TIMEOUT)
#define FURDMA_RX_FULL                          (FURDMA_RX_INT2_THRES)

/*--------------------------------------------------------------------------*/
/* Export Function                                                          */
/*--------------------------------------------------------------------------*/

/*
 *  UART Config Function (Hardware Dependence)
 */
void hal_uart_set_rate( HAL_UART_NUM_t uart_num, u8 Rate);
void hal_uart_set_framing( HAL_UART_NUM_t uart_num, u8 Framing);
void hal_uart_debug_init(u8 port);
void hal_uart_debug_wrt_string(u8* buf, u8 length, bool force_carriage_return_after_line_feed);
void hal_uart_hw_init(void);
void hal_uart_hw_init_ex(HAL_UART_NUM_t uart_num);
bool hal_uart_int_init(HAL_UART_NUM_t uart_num, PfnIntcISR uart_isr);
void hal_uart_int_mask(HAL_UART_NUM_t uart_num);
void hal_uart_int_unmask(HAL_UART_NUM_t uart_num);
void hal_uart_int_clear(HAL_UART_NUM_t uart_num);

/*
 *  UART MISC
 */
u32  hal_uart_get_reg_value(HAL_UART_NUM_t uart_num, Uart_REG_t reg);

#endif /* __HAL_FUART_H__ */
