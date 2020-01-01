/**
 *
 * @file    drv_ven_uart.h
 * @brief   This file defines UART interface
 *
 * @author  William.Tseng
 * @version $Id$
 *
 */
#ifndef __DRV_VEN_UART_H_
#define __DRV_VEN_UART_H_

#ifdef __SDK_DEVICE_CONTROL__
#include "sys_v24.hv"

extern int DrvVenSysUartOpen(int port);
extern int DrvVenSysUartConfig(int handle, v24_Rate_t Rate, v24_Framing_t Framing);
extern int DrvVenSysUartRead(int handle, char* buffer, int len);
extern int DrvVenSysUartWrite(int handle, char* buffer, int len);
extern int DrvVenSysUartAvailable(int handle);
extern int DrvVenSysUartClose(int handle);

#endif /* __SDK_DEVICE_CONTROL__ */

#endif /*__DRV_VEN_UART_H_*/
