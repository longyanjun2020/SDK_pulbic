#ifndef _zm_ipqq_ex_h_
#define _zm_ipqq_ex_h_
#include "zm_typedef.h"

#define ZM_IPQQ_EX_SIZE		(14*1024)
typedef struct
{
	zm_uint16	cmd;
	zm_uint16	length;
	zm_uint8*	data;
}zm_ipqq_ex_msg;
typedef zm_void (*zm_ipqq_ex_msg_hook)(zm_void* p_data, zm_ipqq_ex_msg* p_msg);
typedef zm_void (*ZM_QQ_TIMER_CALLBACK_FUNCPTR)(zm_void);

#ifdef __ZM_QQ_BG_ONLINE__

//QQ½Ó¿Ú
zm_extern zm_void* zm_ipqq_ex_prot(zm_void);
zm_extern zm_void zm_ipqq_ex_free(zm_void);
zm_extern zm_int zm_ipqq_ex_init(zm_uint32 uid, zm_void* p_data, zm_ipqq_ex_msg_hook hook);
zm_extern zm_int zm_ipqq_ex_release(zm_int logout);
zm_extern zm_uint32 zm_ipqq_ex_get_uid(zm_void);
zm_extern zm_int zm_ipqq_ex_request(zm_uint32 cmd, zm_void* param);

//qq system timer
zm_extern zm_void zm_ipqq_ex_start_timer(zm_uint32 dwMiliSec,ZM_QQ_TIMER_CALLBACK_FUNCPTR pCallback);
zm_extern zm_void zm_ipqq_ex_stop_timer(ZM_QQ_TIMER_CALLBACK_FUNCPTR pCallback);

//status icon
zm_extern zm_void zm_ipqq_show_status_icon(zm_int16 icon_ID);
zm_extern zm_void zm_ipqq_hide_status_icon(zm_int16 icon_ID);
zm_extern zm_void zm_ipqq_update_status_icons(zm_void);
zm_extern zm_void zm_ipqq_change_status_icon_image(zm_int16 icon_ID, zm_uint16 image_ID);
zm_extern zm_void zm_ipqq_ex_show_dlg(const zm_uint16* info, zm_int type, zm_uint32 delay);

#else//__ZM_QQ_BG_ONLINE__

zm_extern zm_int	zm_ipqq_ex_init(zm_uint32 uid, zm_void* p_data, zm_ipqq_ex_msg_hook hook);
zm_extern zm_int	zm_ipqq_ex_release(zm_int logout);
zm_extern zm_uint32 zm_ipqq_ex_get_uid(zm_void);
zm_extern zm_int	zm_ipqq_ex_request(zm_uint32 cmd, zm_void* param);

//qq system timer
zm_extern zm_void	zm_ipqq_ex_start_timer(zm_uint32 dwMiliSec,ZM_QQ_TIMER_CALLBACK_FUNCPTR pCallback);
zm_extern zm_void	zm_ipqq_ex_stop_timer(ZM_QQ_TIMER_CALLBACK_FUNCPTR pCallback);

//status icon
zm_extern zm_void	zm_ipqq_show_status_icon(zm_int16 icon_ID);
zm_extern zm_void	zm_ipqq_hide_status_icon(zm_int16 icon_ID);
zm_extern zm_void	zm_ipqq_update_status_icons(zm_void);
zm_extern zm_void	zm_ipqq_change_status_icon_image(zm_int16 icon_ID, zm_uint16 image_ID);
zm_extern zm_void	zm_ipqq_ex_show_dlg(const zm_uint16* info, zm_int type, zm_uint32 delay);

#endif//__ZM_QQ_BG_ONLINE__

zm_extern zm_int	zm_ipqq_ex_getmem(zm_void** buf, zm_int* len);
zm_extern zm_uint16 zm_ipqq_ex_get_statusicons(zm_uint16** icons);

#endif//_zm_ipqq_ex_h_
