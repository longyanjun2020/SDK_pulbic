//==============================================================================
//
//  File        : mmpf_uart.h
//  Description : INCLUDE File for the Firmware UART Control Driver
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_UART_H_
#define _MMPF_UART_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_uart_inc.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR	MMPF_Uart_Open(MMP_UART_ID uart_id, MMP_UART_ATTR *uartattribute);
MMP_ERR	MMPF_Uart_Write(MMP_UART_ID uart_id, const char *pWrite_Str, MMP_ULONG ulLength);
MMP_ERR	MMPF_Uart_Close(MMP_UART_ID uart_id);

// The following UART DMA are opened for upper layer using.
MMP_ERR MMPF_UART_UseTxDMA(MMP_UART_ID uart_id, MMP_ULONG ulTxStartAddr, MMP_USHORT usTxTotalByte,  MMP_UART_DMA_INT_MODE uart_int_mode, MMP_BOOL bEnableInt, UartCallBackFunc* callBackFunc);
MMP_ERR MMPF_UART_UseRxDMA(MMP_UART_ID uart_id, MMP_BOOL bRingModeEn, MMP_ULONG ulRxStartAddr, MMP_ULONG ulRxEndAddr, MMP_ULONG ulRxLowBoundAddr,  MMP_UART_DMA_INT_MODE uart_int_mode, 
							MMP_BOOL bEnableInt, UartCallBackFunc* callBackFunc, MMP_USHORT usRxThreshold, MMP_UBYTE ubRxTimeOut);

// The following UART DMA functions are used inside the driver, upper layer usually does not need to access them.
MMP_ERR MMPF_Uart_SwitchToDmaMode(MMP_UART_ID uart_id, MMP_BOOL bEnable, MMP_UBYTE *ubUartCtl);
MMP_ERR MMPF_Uart_SetTxDmaMode(MMP_UART_ID uart_id, MMP_UART_DMAMODE uart_dma_mode, MMP_ULONG ulTxStartAddr, MMP_USHORT usTxTotalByte);
MMP_ERR MMPF_Uart_SetRxDmaMode(MMP_UART_ID uart_id, MMP_UART_DMAMODE uart_dma_mode, MMP_ULONG ulRxStartAddr, MMP_ULONG ulRxEndAddr, MMP_ULONG ulRxLowBoundAddr);
MMP_ERR MMPF_Uart_SetDmaInterruptMode (MMP_UART_ID uart_id, MMP_UART_DMA_INT_MODE uart_int_mode, MMP_BOOL bEnable, UartCallBackFunc* callBackFunc, MMP_USHORT usRxThreshold, MMP_UBYTE ubRxTimeOut);
MMP_ERR MMPF_Uart_EnableDmaMode(MMP_UART_ID uart_id, MMP_UART_DMAMODE uart_dma_mode, MMP_BOOL bEnable);

// Functions for UART RX interrupt mode
#if (UART_RXINT_MODE_EN == 1)
MMP_BOOL MMPF_Uart_IsRxEnable(MMP_UART_ID uart_id);
MMP_ERR MMPF_Uart_EnableRx(MMP_UART_ID uart_id, MMP_ULONG threshold, UartCallBackFunc *callBackFunc);
MMP_ERR MMPF_Uart_DisableRx(MMP_UART_ID uart_id);
#endif

#endif // _MMPF_UART_H_
