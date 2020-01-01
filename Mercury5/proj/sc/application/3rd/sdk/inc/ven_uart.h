/**
 *
 * @file    ven_uart.h
 * @brief   This file defines UART interface
 *
 * @author  William.Tseng
 * @version $Id$
 *
 */
#ifndef __VEN_UART_H_
#define __VEN_UART_H_


#ifdef __SDK_DEVICE_CONTROL__
#include "sys_vm_v24.hi"


typedef struct
{
    vm_v24_Rate_t baudrate; /*map to vm_v24_Rate_t*/
    vm_v24_SerialLength_t bitsPerChar;/*map to vm_v24_SerialLength_t*/
    vm_v24_SerialStop_t stopBits;/*map to vm_v24_SerialStop_t*/
    vm_v24_SerialParity_t parity; /*map to vm_v24_SerialParity_t*/
} vensysUart_cfg_t;

extern int ven_sys_uart_open(int port);
extern int ven_sys_uart_config(int handle, vensysUart_cfg_t* jaluart_cfg);
extern int ven_sys_uart_read(int handle, char* buffer, int len);
extern int ven_sys_uart_write(int handle, char* buffer, int len);
extern int ven_sys_uart_available(int handle);
extern int ven_sys_uart_close(int handle);

#endif /* __SDK_DEVICE_CONTROL__ */
#endif /*__VEN_UART_H_*/
