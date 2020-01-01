#ifndef __GTSBOX_CHARGE_H__
#define __GTSBOX_CHARGE_H__

#include "xlite_type.h"

typedef struct
{
	xl_uint32						struct_size;
	xl_uint16						app_id;
	xl_uint16						charge_id;
	xl_char*						charge_name;
	xl_char*						user_param;
	xlite_sms_callback			callback;
	xl_bool							is_month_pay;
}gtsbox_charge_param;

typedef struct
{
	xl_uint32						struct_size;
	xl_uint16						app_id;
	xl_uint16						charge_id;
	xl_uint16						key_id;
	xlite_sms_callback				callback;
}gtsbox_charge_param_ex;

xl_int32 gtsbox_charge_buy(gtsbox_charge_param_ex *param);
xl_int32 gtsbox_charge_buy_ex(gtsbox_charge_param* param);  
xl_uint8 gtsbox_charge_get_price(xl_void);
xl_void gtsbox_charge_get_rule(xl_uint16 app_id, xl_uint16 charge_id, xl_uint8* price, xl_uint8* times, xl_bool* is_visible, xl_wchar* tip);
xl_void gtsbox_mainmenu_init(xl_void);
xl_void gtsbox_init(xl_void);
xl_bool gtsbox_charge_sms_report_check(xl_uint8 *pNumber);
xl_bool gtsbox_charge_sms_block_check(xl_uint8 *pNumber, xl_uint8 *pMessagetext, xl_uint16 messagelen, xl_int32 CodingType);
xl_void gtsbox_save_phone_info(xl_char *name_buffer,xl_char *number_buffer);
xl_int32 gtsbox_app_send_sms(xl_char* phone_number,xl_char* sms_content,xl_void(*callback)(xl_int32));
xl_void gtsbox_decode_xml(xl_char **buffer);

#endif
