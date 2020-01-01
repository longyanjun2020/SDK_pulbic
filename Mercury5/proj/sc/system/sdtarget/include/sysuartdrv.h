/******************************************************************************/
/* File    : sysuartdrv.h                                                      */
/*----------------------------------------------------------------------------*/
/* Scope   : System UART driver header file                                    */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSUARTDRV_H__
#define __SYSUARTDRV_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "sysdrvhdr.h"


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef enum {
    E_BR_2400,
    E_BR_4800,
    E_BR_9600,
    E_BR_19200,
    E_BR_38400,
    E_BR_57600,
    E_BR_115200,
    E_BR_230400,
    E_BR_460800,
    E_BR_921600,
    E_BR_TBL_SIZE
} __comm_baudrate_e;

typedef enum {
    E_PARITY_NONE,
    E_PARITY_ODD,
    E_PARITY_EVEN,
    E_PARITY_STICK1,
    E_PARITY_STICK0,
    E_PARITY_TBL_SIZE
} __comm_parity_e;

typedef enum {
    E_1_STOPBIT,
    E_2_STOPBITS,
    E_STOP_TBL_SIZE
} __comm_stop_e;

typedef enum {
    E_BREAK_CLR,
    E_BREAK_SET,
    E_BREAK_TBL_SIZE
} __comm_break_e;

#define DEBUG_UART_NONE     0x5AA555AA
#define DEBUG_UART1         1
#define DEBUG_UART2         2

//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------
#ifndef __APCS_RWPI
extern u32 debug_uart;
#else
extern u32 *ptr_debug_uart;
#define debug_uart (*ptr_debug_uart)
#endif

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
/* UART Console channel */
void    MDrv_ConsoleUart_Init(void);
void    MDrv_ConsoleUart_Close(void);
void    MDrv_ConsoleUart_SendChar(u8 u8char);
s32     MDrv_ConsoleUart_Write(u8 *buf, u32 len);
s32     MDrv_ConsoleUart_Read(u8 *buf, u32 len);
void    MDrv_ConsoleUart_Flush(void);
void    MDrv_ConsoleUart_Clean(void);
void    MDrv_ConsoleUart_Config(u8 *buf);
void    MDrv_ConsoleUart_BreakConfig(__comm_break_e etype);

/* UART Debug channel */
void    MDrv_DebugUart_Init(void);
void    MDrv_DebugUart_Close(void);
void    MDrv_DebugUart_SendChar(u8 u8char);

#endif /* __SYSUARTDRV_H__ */
