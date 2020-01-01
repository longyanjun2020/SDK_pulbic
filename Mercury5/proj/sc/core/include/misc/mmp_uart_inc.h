//==============================================================================
//
//  File        : mmp_uart_inc.h
//  Description : INCLUDE File for the Firmware UART Control Driver
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_UART_INC_H_
#define _MMP_UART_INC_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define UART_RXINT_MODE_EN	    (1)
#define UART_RXINT_SEM_TIMEOUT  (0x10000)
#define UART_DMA_MODE_EN	    (1)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_UART_ID
{
    MMP_UART_ID_0 = 0,
    MMP_UART_ID_1,
    MMP_UART_ID_2,
    MMP_UART_ID_3,
    MMP_UART_MAX_COUNT
} MMP_UART_ID;

typedef enum _MMP_UART_PADSET
{
    MMP_UART_PADSET_0 = 0,
    MMP_UART_PADSET_1,
    MMP_UART_PADSET_2,
    MMP_UART_PADSET_3,  
    MMP_UART_PADSET_4,
    MMP_UART_PADSED_MAX
} MMP_UART_PADSET;

typedef enum _MMP_UART_DMAMODE
{
    MMP_UART_RXDMA_RING = 0,
    MMP_UART_TXDMA,
    MMP_UART_RXDMA,
    MMP_UART_DMA_MAX
} MMP_UART_DMAMODE;

typedef enum _MMP_UART_DMA_INT_MODE
{
    MMP_UART_TXDMA_END_EN = 0,
    MMP_UART_RXDMA_TH_EN,
    MMP_UART_RXDMA_WRMEM_EN,
    MMP_UART_RXDMA_DROPDATA_EN,
    MMP_UART_DMA_INT_MAX
} MMP_UART_DMA_INT_MODE;

typedef enum _MMP_UART_PARITY
{
	MMP_UART_PARITY_NONE = 0,
	MMP_UART_PARITY_EVEN,
	MMP_UART_PARITY_ODD,
	MMP_UART_PARITY_FORCE0,
	MMP_UART_PARITY_FORCE1,
	MMP_UART_PARITY_MAX
} MMP_UART_PARITY;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef void UartCallBackFunc(MMP_UBYTE num, ...);

typedef struct _MMP_UART_ATTR
{
    MMP_UART_PADSET    	padset;
    MMP_ULONG           ulMasterclk;
    MMP_ULONG           ulBaudrate;
    MMP_BOOL			bParityEn;
    MMP_BOOL			bFlowCtlEn;
    MMP_UBYTE			ubFlowCtlSelect; //0: low active , 1: high active
    MMP_UART_PARITY    	parity;
} MMP_UART_ATTR;


#endif // _MMP_UART_INC_H_
