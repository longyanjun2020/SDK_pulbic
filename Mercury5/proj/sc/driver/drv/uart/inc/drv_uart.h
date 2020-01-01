/**
 * @page UART driver Interface
 *
 *
 * @section intro_sec Introduction
 *
 * This document describes the UART driver Interface
 *
 *  <hr>
 * @section SectionUser2UART 1. User to UART Interface
 *
 * @li @ref uart_Open
 * @li @ref uart_SetRate
 * @li @ref uart_SetFraming
 * @li @ref uart_Write
 * @li @ref uart_Read
 * @li @ref uart_GetRxFifoLevel
 * @li @ref uart_IsTxFifoEmpty
 * @li @ref uart_ClearRxBuffer
 *
 *
 *  <hr>
 * @section Usage 2. Usage
 *
 *  The client first calls @ref uart_Open to open the given UART and configure it
 *
 *  Then it can call one or more other functions to change the rate or framing. It can read data from the UART software FIFO
 * by calling @ref uart_Read, or write data by calling @ref uart_Write.
 * It can also get the level (@ref uart_GetRxFifoLevel) and clear (@ref uart_ClearRxBuffer) the Rx software FIFO, know if the Tx hardware FIFO is empty (@ref uart_IsTxFifoEmpty).
 *
 *
 *
 *  <hr>
 *  @section Notes 3. NOTES
 *
 *  Current limitations :
 *
 *  \li 1. Only one session by UART.
 *  \li 2. callbacks given in @ref uart_Open must be executed as fast as possible, because tehy are called under IRQ.
 *
 *
 */


/*!
 * @file  uart_drv.h
 * @brief User to UART driver
 *
 *  This file defines the UART driverinterface that is offered to the  V24, Bluetooth.
 *
 */
/**
 * @addtogroup Manager
 * @{
 */

#ifndef __UART_DRV_H__
#define __UART_DRV_H__

#include "vm_types.ht"
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "kernel.h"
#include "drv_uart_api.h"
#include "sys_wmh_v24.hi"
#include "sys_vm_v24.hi"
#include "hal_fuart.h"

/**
 * @brief UART port
 *
 *  Used in all uart functions.
 */
typedef enum {
    UART_1,
    UART_2,
    UART_3,
    FUART,
    NB_UART
} Uart_Num_t;

extern volatile FURUart_t * const FURUart[NB_UART];

/**
 * @brief Baud rate for G1
 */
enum
{
	_921600 = HUC_BAUD_921600,	///< 921600 bps
	_460800 = HUC_BAUD_460800,	///< 460800 bps
	_230400 = HUC_BAUD_230400,	///< 230400 bps
	_115200 = HUC_BAUD_115200,	///< 115200 bps
	_57600 = HUC_BAUD_57600,	///< 57600 bps
	_38400 = HUC_BAUD_38400,	///< 38400 bps
	_19200 = HUC_BAUD_19200,	///< 19200 bps
	_9600 = HUC_BAUD_9600, ///< 9600 bps
	_4800 = HUC_BAUD_4800,	///< 4800 bps
	_2400 = HUC_BAUD_2400,	///< 2400 bps
	_1200 = HUC_BAUD_1200,	///< 1200 bps
	_600 = HUC_BAUD_600,	///< 600 bps
	_300 = HUC_BAUD_300,	///< 300 bps
	_75 = HUC_BAUD_75 ///< 75 bps
};

/****************************************************************************************************/
/*************************** V24 Action Macros on Uart Signals **************************************/
/****************************************************************************************************/
#define UART_GET_HAL_NUM(Uart_num) (Uart_num+HAL_UART1)

#define UART_GET_OBJ(Uart_num) HAL_UART_GET_OBJ(UART_GET_HAL_NUM(Uart_num))

#define UART_SET_RTS_ON(Uart_num)		HAL_UART_SET_RTS_ON(UART_GET_OBJ(Uart_num))

#define UART_SET_RTS_OFF(Uart_num)		HAL_UART_SET_RTS_OFF(UART_GET_OBJ(Uart_num))

#define UART_SET_DTR_ON(Uart_num)		HAL_UART_SET_DTR_ON(UART_GET_OBJ(Uart_num))

#define UART_SET_DTR_OFF(Uart_num)      HAL_UART_SET_DTR_OFF(UART_GET_OBJ(Uart_num))

#define UART_IS_CTS_CHANGE( msr, available )      HAL_UART_IS_CTS_CHANGE( msr, available )
#define UART_IS_DSR_CHANGE( msr )      HAL_UART_IS_DSR_CHANGE(msr)

#define UART__IS_CTS_ON( msr, available )         HAL_UART__IS_CTS_ON( msr, available )
#define UART__IS_DSR_ON( msr )         HAL_UART__IS_DSR_ON(msr)

#define UART_SET_DCD_ON( Uart_num )  	//sys_DwnGpio( v24_CustomDcdGpio )
#define UART_SET_DCD_OFF( Uart_num ) 	//sys_UpGpio ( v24_CustomDcdGpio )
#define UART_SET_RI_ON( Uart_num ) 		//sys_DwnGpio( v24_CustomRiGpio )
#define UART_SET_RI_OFF( Uart_num )		//sys_UpGpio ( v24_CustomRiGpio )

#define UART_IS_CTS_ON(Uart_num )        HAL_UART_IS_CTS_ON(UART_GET_OBJ(Uart_num))

/****************************************************************************************************/
/*************************** V24 general functionnalities MACROS ************************************/
/****************************************************************************************************/
#define UART_CLEAR_IIR( Uart_num )      //(uart_WriteIIR_Clear(HAL_UART_GET_OBJ(Uart_num),0))

#define UART_IS_BREAK( lsr )        HAL_UART_IS_BREAK( lsr )
#define UART_IS_OVERRUN( lsr )      HAL_UART_IS_OVERRUN( lsr )

#define UART_SET_IT_MASK( Uart_num, m ) 	HAL_UART_SET_IT_MASK( UART_GET_OBJ(Uart_num), m )
#define UART_SET_IT_SRC( Uart_num, m )  	HAL_UART_SET_IT_SRC( UART_GET_OBJ(Uart_num), m)
#define UART_CLR_IT_SRC( Uart_num, m )  	HAL_UART_CLR_IT_SRC( UART_GET_OBJ(Uart_num), m )

#define UART_RX_FIFO_NOT_EMPTY( Uart_num )  	HAL_UART_RX_FIFO_NOT_EMPTY( UART_GET_OBJ(Uart_num))
#define UART_RX_FIFO_EMPTY(Uart_num)        	HAL_UART_RX_FIFO_EMPTY(UART_GET_OBJ(Uart_num))

/**
 * @brief only for target to gain speed
 */
//#define UART__RX_FIFO_NOT_EMPTY( Uart_num )   (  W5Uart[Uart_num]->u32_ModemStatus & UART_DATA_READY )
/**
 * @brief following macro tests transmit register empty bit. If so it means that
 * fifo (or transmit holding reg) is also empty.
*/

#define UART_TX_FIFO_EMPTY( Uart_num )        		HAL_UART_TX_FIFO_EMPTY(UART_GET_OBJ(Uart_num))

#define UART_CLR_RX_FIFO( Uart_num, lvl ) HAL_UART_CLR_RX_FIFO( UART_GET_OBJ(Uart_num), lvl )
#define UART_CLR_TX_FIFO( Uart_num, lvl ) HAL_UART_CLR_TX_FIFO( UART_GET_OBJ(Uart_num), lvl )

/**
 * @brief CAUTION: following two macro clear also the trigger level
*/
#define UART_ENABLE_FIFOs( Uart_num ) 	HAL_UART_ENABLE_FIFOs( UART_GET_OBJ(Uart_num) )
#define UART_RESET_FIFOs( Uart_num )   HAL_UART_RESET_FIFOs( UART_GET_OBJ(Uart_num))

#define UART_SET_TRIGGER_LVL( Uart_num,lvl ) 	HAL_UART_SET_TRIGGER_LVL( UART_GET_OBJ(Uart_num),lvl )

/****************************************************************************************************/
/*************************** V24 special functionnalities MACROS ************************************/
/****************************************************************************************************/
#define UART_START_BREAK( Uart_num )   HAL_UART_START_BREAK(UART_GET_OBJ(Uart_num))
#define UART_STOP_BREAK( Uart_num )    HAL_UART_STOP_BREAK(UART_GET_OBJ(Uart_num))


#define UART_RX_IT_BUF_LEN     256   /* must be a power of 2 */
#define UART_TX_IT_BUF_LEN     384

s32 uart_Open( Uart_Num_t uart_num, Uart_cfg_t *uart_cfg );
void uart_SetRate(Uart_Num_t uart_num, vm_v24_Rate_t Rate );
void uart_SetFraming( Uart_Num_t uart_num, vm_v24_Framing_t Framing );
s32 uart_Write( Uart_Num_t uart_num, u8 *string,  u32 length);
s32 uart_Read( Uart_Num_t uart_num, u8 *string,  u32 length);
s32 uart_GetRxFifoLevel( Uart_Num_t uart_num);
bool uart_IsTxFifoEmpty( Uart_Num_t uart_num);
s32 uart_ClearRxBuffer( Uart_Num_t uart_num);

#endif /* __UART_DRV_H__ */
