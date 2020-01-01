#ifndef _zm_bt_mouse_h_
#define _zm_bt_mouse_h_

#include "zm_typedef.h"

typedef struct
{
/**
 *	进入蓝牙鼠标接口
 */
	zm_void (*zm_btmouse_entry_remote_control)(zm_void);

/**
 *	退出蓝牙鼠标接口
 */
	zm_void (*zm_btmouse_exit_remote_control)(zm_void);

/**
 *	发送数据接口
 */
	zm_void (*zm_btmouse_send_data_req)(zm_int data_len, zm_uint8* data);

/**
 *	获取输入框中的输入文本
 */
	zm_int8* (*zm_btmouse_get_input_buffer)(zm_void);

}zm_btmouse;

/**
 * 获取蓝牙鼠标接口
 */
zm_extern zm_btmouse* zm_get_btmouse(zm_void);

#endif//_zm_bt_mouse_h_
