//==============================================================================
//
//  File        : mmpf_uarttouch.h
//  Description : INCLUDE File for the uart touch Driver Function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_UARTTOUCH_H_
#define _MMPF_UARTTOUCH_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_uart.h"

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern MMPF_OS_FLAGID   	UartCtrlFlag;

#define Touch_Uart_FLAG_INITIAL                 0x00001000
#define Touch_Uart_FLAG_GETPACK            		0x00002000
#define Touch_Uart_FLAG_PARSERPACK           	0x00004000
#define Touch_Uart_FLAG_SETPACK            		0x00008000

#define UART_CMD_WRITE_IOCTL                    0x01

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern MMPF_OS_FLAGID   	UartCtrlFlag;


//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================


typedef struct _3RD_PARTY_TOUCH_UART 
{
    //0
    MMP_ERR (*pTouch_Uart_Initialize)(struct _3RD_PARTY_TOUCH_UART *,MMP_UART_ATTR uartatt);
    MMP_ERR (*pTouch_Uart_GetString)(struct _3RD_PARTY_TOUCH_UART *, MMP_BYTE *usData,MMP_ULONG *length);
    MMP_ERR (*pTouch_Uart_SetString)(struct _3RD_PARTY_TOUCH_UART *, MMP_BYTE *usData,MMP_ULONG length);
    MMP_BOOL (*pTouch_Uart_ModuleAttached)(struct _3RD_PARTY_TOUCH_UART *);
    MMP_ERR (*pTouch_Uart_IOControl)(struct _3RD_PARTY_TOUCH_UART *, MMP_UBYTE cmd,MMP_UBYTE *arg);
		
} THIRD_PARTY_TOUCH_UART ;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR Touch_Uart_Ctrl_Init(void);
MMP_ERR Touch_Uart_Ctrl_GetString(MMP_BYTE *data,MMP_ULONG *length);
MMP_ERR Touch_Uart_Ctrl_SetString(MMP_BYTE *data,MMP_ULONG length);
MMP_ERR Touch_Uart_Ctrl_ParserMain(MMP_UBYTE *data,MMP_ULONG length);
MMP_BOOL Touch_Uart_Ctrl_Attached(void);
MMP_ERR Touch_Uart_Ctrl_IOControl(MMP_UBYTE cmd, MMP_UBYTE* arg);

void Touch_Uart_Ctrl_Register(struct _3RD_PARTY_TOUCH_UART *pdev_obj);
void Touch_Uart_Ctrl_Unregister(void);


#endif // 
