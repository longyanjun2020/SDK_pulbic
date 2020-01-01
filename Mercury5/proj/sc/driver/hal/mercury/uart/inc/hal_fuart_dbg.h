
#ifndef __HAL_FUART_DBG_H__
#define __HAL_FUART_DBG_H__

#include "vm_types.ht"

int hal_dbg_send_msg(char *msg);
void hal_dbg_send_buffer(char *buffer, u32 len);
s8 hal_dbg_send_trace(const char *strFormat, ...);

int hal_dbg_get_char(void);
char *hal_dbg_get_string(void);
char *hal_dbg_get_string_irda(void);

int hal_dbg_check_val8(u8 expected_data, u8 read_data);
int hal_dbg_check_val16(u16 expected_data, u16 read_data);
int hal_dbg_check_val32(u32 expected_data, u32 read_data) ;

#endif /* __HAL_FUART_DBG_H__ */


