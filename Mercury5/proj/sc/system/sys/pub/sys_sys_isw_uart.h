/****************************************************************************
 *
 *  File :   sys_sys_isw_uart.h
 *
 ****************************************************************************/
#ifndef __SYS_SYS_ISW_UART_H__
#define __SYS_SYS_ISW_UART_H__

//#include "vm_types.ht"
#include "stdcomp.h"


void send_msg (char *msg);
void send_buffer (char *buffer, u32 len);
int get_char (void);
char *get_string (void);
char* get_string_irda (void);
s8 UartSendTrace(const char *strFormat, ...);

s32 vm_atoi(const char *input);
s32 vm_htoi(const char *input);
int check_val8(u8 expected_data, u8 read_data);
int check_val16(u16 expected_data, u16 read_data);
int check_val32(u32 expected_data, u32 read_data);
void wait (int nb_nop);
char *wait_for_command(void);



#endif // __SYS_SYS_ISW_UART_H__
