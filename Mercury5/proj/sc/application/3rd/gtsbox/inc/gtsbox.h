#ifndef __GTSBOX_H__
#define __GTSBOX_H__

#include "xlite_type.h"
#include "xlite_E_type.h"
//////////////////////////////////////////////////////////////////////////
// define

//pen event
typedef enum
{
	pen_down = 0,
	pen_move = 1,
	pen_up = 2
}gtsbox_pen_event;

typedef enum
{
	//update and flush lcd
	GTSBOX_MSG_UPDATE =	1,
	//active app
	GTSBOX_MSG_ACTIVE,
	//inactive app
	GTSBOX_MSG_INACTIVE,
	//create app
	GTSBOX_MSG_CREATE,
	//quit app
	GTSBOX_MSG_QUIT,
	//paint buffer and flush lcd
	GTSBOX_MSG_PAINT,
	//sys msg end
	GTSBOX_MSG_END = 255
}gtsbox_sys_event;

typedef enum
{
	MSG_KEYDOWN_LEFT = 0x01,
	MSG_KEYDOWN_RIGHT,
	MSG_KEYDOWN_UP,
	MSG_KEYDOWN_DOWN,
	MSG_KEYDOWN_1,
	MSG_KEYDOWN_2,
	MSG_KEYDOWN_3,
	MSG_KEYDOWN_4,
	MSG_KEYDOWN_5,
	MSG_KEYDOWN_6 = 0x10,
	MSG_KEYDOWN_7,
	MSG_KEYDOWN_8,
	MSG_KEYDOWN_9,
	MSG_KEYDOWN_0,
	MSG_KEYDOWN_OK,
	MSG_KEYDOWN_RSK,
	MSG_KEYDOWN_WEB,
	MSG_KEYDOWN_LSK,
	MSG_KEYDOWN_STAR,
	MSG_KEYDOWN_POUND = 0x20,

	MSG_KEYUP_LEFT = 0x21,
	MSG_KEYUP_RIGHT,
	MSG_KEYUP_UP,
	MSG_KEYUP_DOWN,
	MSG_KEYUP_1,
	MSG_KEYUP_2,
	MSG_KEYUP_3,
	MSG_KEYUP_4,
	MSG_KEYUP_5,
	MSG_KEYUP_6 = 0x30,
	MSG_KEYUP_7,
	MSG_KEYUP_8,
	MSG_KEYUP_9,
	MSG_KEYUP_0,
	MSG_KEYUP_OK,
	MSG_KEYUP_RSK,
	MSG_KEYUP_WEB,
	MSG_KEYUP_LSK,
	MSG_KEYUP_STAR,
	MSG_KEYUP_POUND = 0x40,
	MSG_KEYUP_END = 0xff
}gtsbox_key_value;
//////////////////////////////////////////////////////////////////////////
// func

// app entey func, define in app
xl_void gtsbox_app_start(xl_void);

// app quit func, gtsbox send GTSBOX_MSG_QUIT msg
xl_void gtsbox_app_quit(xl_void);

// get graphic handle from gtsbox
xlite_graphics* gtsbox_app_get_graphic_handle(xl_void);

// register system event callback func
xl_void gtsbox_app_reg_sysevt_callback(void(*func)(xl_int32));
// register key event callback func
xl_void gtsbox_app_reg_keyevt_callback(void(*func)(xl_int32));
// register pen event callback func
xl_void gtsbox_app_reg_penevt_callback(void(*func)(gtsbox_pen_event,xlite_point *));
xl_void gtsbox_app_release_resource(xl_uint8* data);
// get extern resource
xl_uint32 gtsbox_app_get_resource(xl_wchar* res_file_name, xl_uint32 res_hash, xl_uint8 ** pBuffer);
// get app file path
xl_void gtsbox_app_get_module_path(xl_wchar * pPath);

xl_void gtsbox_timer(xl_void);

#endif
