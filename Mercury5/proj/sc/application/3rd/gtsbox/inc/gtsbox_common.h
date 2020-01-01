#ifndef __GTSBOX_COMMON_H__
#define __GTSBOX_COMMON_H__

#include "xlite_type.h"
#include "xlite_E_type.h"
#include "gtsbox.h"
#include "xml4c.h"

//////////////////////////////////////////////////////////////////////////
//OPTION

// 是否处理后台任务
#define GTSBOX_SUPPORT_PRIORITY_9
// 超时选项,单位,毫秒
#define GTSBOX_HTTP_TIMEOUT					30000
// 更新间隔时间(天)
#define UPDATE_INTERVAL_DAY	10
// 更新间隔次数
#define UPDATE_INTERVAL_TIMES	20

//////////////////////////////////////////////////////////////////////////
//event

typedef enum
{
	GBX_EVT_GET_SIM_INFO_OK,
	GBX_EVT_END
}gtsbox_evt_enum;

//////////////////////////////////////////////////////////////////////////
// error code

#define GTSBOX_ERR_NONE 0

//初始化错误
#define GTSBOX_ERR_INIT -1000
//初始化失败
#define GTSBOX_ERR_INIT_FAILED (GTSBOX_ERR_INIT-1)
//初始化等待回调
#define GTSBOX_ERR_INIT_WAIT_CALLBACK (GTSBOX_ERR_INIT-2)


//加载游戏错误
#define GTSBOX_ERR_LOAD_GAME -2000
//无法找到游戏
#define GTSBOX_ERR_NO_SUCH_APP			(GTSBOX_ERR_LOAD_GAME-1)
//加载游戏失败
#define GTSBOX_ERR_LOAD_APP_FAILED		 (GTSBOX_ERR_LOAD_GAME-2)
//无法找到应用入口
#define GTSBOX_ERR_PARSE_ENTRYFUNC_FAILED		(GTSBOX_ERR_LOAD_GAME-3)
//为加载器分配内存失败
#define GTSBOX_ERR_LOADER_MALLOC_FAILED		(GTSBOX_ERR_LOAD_GAME-4)

//HTTP错误
#define GTSBOX_ERR_HTTP -3000
//下载游戏列表错
#define GTSBOX_ERR_DOWNLOAD_GAMELIST (GTSBOX_ERR_HTTP-1)
//没有空闲的mission
#define GTSBOX_ERR_NO_FREE_MISSION (GTSBOX_ERR_HTTP-2)
//无法连接网络
#define GTSBOX_ERR_CAN_NOT_CONNECT (GTSBOX_ERR_HTTP-3)
//下载列表中没有该游戏
#define GTSBOX_ERR_APP_NOT_FOUND_IN_DOWNLOAD_LIST (GTSBOX_ERR_HTTP-4)
//已经下载完成
#define GTSBOX_ERR_APP_ALREDAY_DOWNLOAD (GTSBOX_ERR_OTHER-5)


//其他错误
#define GTSBOX_ERR_OTHER -4000
//磁盘空间不足
#define GTSBOX_ERR_NO_ENOUGH_FREE_SPACE (GTSBOX_ERR_OTHER-1)
//USB功能使用中
#define GTSBOX_ERR_USB_IN_MASS_STORAGE (GTSBOX_ERR_OTHER-2)
//没有T卡
#define GTSBOX_ERR_NO_REMOVEABLE_DISK (GTSBOX_ERR_OTHER-3)

//设备复位
#define GTSBOX_ERR_DEVICE_RESET	-5000
//////////////////////////////////////////////////////////////////////////
// var
#define LOADER_MEM_SIZE (5*100*1024)

#define HTTP_HEAD_START "HTTP"
#define HTTP_HEAD_START_LENGTH 4
#define HTTP_HEAD_END "\r\n\r\n"
#define HTTP_HEAD_END_LENGTH 4
#define HTTP_HEAD_LINE_END "\r\n"
#define HTTP_HEAD_LINE_END_LENGTH 2
#define HTTP_HEAD_NAME_SYMBOL ':'
#define HTTP_HEAD_NAME_SYMBOL_LENGTH 1

#define GAME_PID_LENGTH 5

#define HTTP_HEAD_FILENAME_CONTENT "Content-Disposition"
#define HTTP_HEAD_FILENAME_CONTENT_LENGTH 19
#define HTTP_HEAD_FILENAME_VAL_NAME "filename"
#define HTTP_HEAD_FILENAME_VAL_NAME_LENGTH 9
#define HTTP_HEAD_FILESIZE_CONTENT "Content-Length"

#define DEFAULT_HEAD_LIST_NUMBER 5

#define DEFAULE_GAME_TEMPFILE_EXT "tmp"
#define DEFAULT_GAME_ENTRY_SYMBOL "gtsbox_app_start"

typedef enum
{
	http_mission_type_none,
	http_mission_type_download_app,
	http_mission_type_charge_push,
	http_mission_type_charge_day_push,
	http_mission_type_get_charge_tip,
	http_mission_type_update_server_url,
	//下载任务
	http_mission_type_download
}gtsbox_http_mission_type_enum;

typedef enum
{
	http_mission_state_free,
	http_mission_state_running,
	http_mission_state_finished,
	http_mission_state_failed
}gtsbox_http_mission_state_enum;


typedef enum
{
	http_mission_proxy_cmwap_only,
	http_mission_proxy_cmnet_only,
	http_mission_proxy_cmwap_first,
	http_mission_proxy_cmnet_first,
}gtsbox_http_mission_proxy_enum;

typedef enum
{
	http_mission_pri_first,
	http_mission_pri_second
}gtsbox_http_mission_pri_enum;

#define GTSBOX_HTTP_EVT_CONNECT	1
#define GTSBOX_HTTP_EVT_SEND		2
#define GTSBOX_HTTP_EVT_RECV		3
#define GTSBOX_HTTP_EVT_END		4

#define GTSBOX_HTTP_ERR_NONE					0
#define GTSBOX_HTTP_ERR_CONNECT_FAILED		-1
#define GTSBOX_HTTP_ERR_RESPONSE_CODE		-2
#define GTSBOX_HTTP_ERR_NO_FREE_SPACE		-3
#define GTSBOX_HTTP_ERR_TIME_OUT				-4
#define GTSBOX_HTTP_ERR_CHECK_FAILED			-5


typedef enum
{
	SHELL_NODE_TYPE_INVALID = 0,
	SHELL_NODE_TYPE_HEAD = 0x01,//头节点
	SHELL_NODE_TYPE_INFO = 0x02,//信息节点
	SHELL_NODE_TYPE_ICON = 0x03,//图标节点
	SHELL_NODE_TYPE_PUBLSHER =	0x04,
	SHELL_NODE_TYPE_RESOURCE =	0x05,
	SHELL_NODE_TYPE_LOADER_MEM_SIZE	=	0x06,//记录loader解析当前游戏的内存开销
	SHELL_NODE_TYPE_APP = 0xFE,//app内容节点
	SHELL_NODE_TYPE_END = 0xFF//结束标记节点
}gbx_shell_node_type;


#define GTSBOX_UPDATE_FILE_NAME			"XML.DAT"
//////////////////////////////////////////////////////////////////////////

typedef xl_void (*start_func_ptr)(xl_void);

typedef struct
{
	//common
	xl_uint32 		app_id;								//应用id
	xl_wchar	 		cname[20];							//中文名
	xlite_version 		m_Version;							//版本号，同时存在内置和加载时以加载的为准

	//static
	start_func_ptr		start_func;							//入口函数
	
	//dynamic
	xl_uint32 		offset;								//.o文件在.gbx文件中的偏移量
	xl_uint32 		size;								//.gbx文件大小
	xl_wchar			full_path_name[XLITE_MAX_PATH];		//完整的路径和文件名
	xl_uint32 		m_MemSizeOfLoader;				//加载所需的内存大小

	//state	
	xl_bool			in_download_list;					//是否可以被下载
	xlite_version		download_version;					//下载列表中的版本号，用于判断是否需要更新
	xl_bool			in_push_list;						//是否可以被推送
}gtsbox_app_info_struct;


typedef struct
{
	xl_uint32 		app_id;								//应用id
	xl_wchar* 		cname;								//中文名
	start_func_ptr		start_func;							//入口函数
}default_app_info_struct;


typedef struct  
{
	xl_uint8 type;
	xl_uint32 length;
}gtsbox_base_node_struct;

typedef struct  
{
	xl_char verify_char[3];
	xl_uint8 main_version;
	xl_uint8 sub_version;
}gtsbox_head_node_struct;

typedef struct  
{
	xl_char file_name[XLITE_MAX_PATH];
	xl_uint32 content_length;
	xl_uint32 downloaded_length;
	xl_uint32 last_act_tick;
	
	gtsbox_http_mission_state_enum state;
	gtsbox_http_mission_type_enum type;
	gtsbox_http_mission_proxy_enum proxy;
	gtsbox_http_mission_pri_enum pri;
	xl_int32 error;

	xlite_http_request http_req;
	xlite_http_session* session;

	xlite_E_http_event_handler handler;
	
	xl_bool is_charge_xml_discard;

	xl_bool download_cancel;
}gtsbox_http_mission_struct;

typedef struct
{
	xl_int16 app_list_index;
	xl_int16 menuitem_index;
	xl_int16 apn_menu_index;
	xl_uint16 download_time;
	xl_wchar menu_title[10];
}gtsbox_mmi_struct;

//***************add by dk begin**********************
// 菜单定义
typedef struct _menuitem_data
{
	xl_char		*title;//菜单的标题
	xl_char		*strId;//菜单ID
	xl_int16	mSelected;//上层菜单高亮选中的项
}menuitem_data_t;//用于菜单跳转

typedef struct  _curtmenuitem
{
	xl_wchar*	title;//菜单名字
}curt_menuitem_t;//当前的菜单的菜单项属性

typedef struct
{
	xl_int16	totalindex;//当前的菜单的菜单项数量，从1算起
	xl_int16	crtindex;//当前选中的菜单项，从0算起
}curt_menuitem_Index_t;

//*****MACRO DEFS ********************************************************
#define STR_MENU					("menu")
#define STR_EXPLAIN					("explain")
#define STR_APP						("app")
#define STR_PUSH					("push")
#define STR_PUSH_VALUE				("1")
#define STR_VERSION					("version")
#define STR_DYNAMICMENU			("dynamicMenu")
#define STR_NAME					("name")
#define STR_DATA					("data")
#define STR_ID						("id")

#define STR_STAR					("*")
#define STR_TYPE					("type")
#define STR_ZERO					("0")

#define STR_ENTER_1					("e1")
#define STR_ENTER_2					("e2")
#define STR_ENTER_3					("e3")
#define STR_ENTER_4					("e4")
#define STR_ENTER_5					("e5")
#define STR_ENTER_6					("e6")
#define STR_ENTER_7					("e7")
#define STR_ENTER_8					("e8")
#define STR_ENTER_9					("e9")
#define STR_ENTER_10				("e10")
#define STR_ENTER_11				("e11")
#define STR_ENTER_12				("e12")
#define STR_ENTER_13				("e13")
#define STR_ENTER_14				("e14")
#define STR_ENTER_15				("e15")
#define STR_ENTER_16				("e16")
#define STR_ENTER_17				("e17")
#define STR_ENTER_18				("e18")
#define STR_ENTER_19				("e19")
#define STR_ENTER_20				("e20")
#define STR_ENTER_21				("e21")
#define STR_ENTER_22				("e22")
#define STR_ENTER_23				("e23")
#define STR_ENTER_24				("e24")
#define STR_ENTER_25				("e25")
#define STR_ENTER_26				("e26")
#define STR_ENTER_27				("e27")
#define STR_ENTER_28				("e28")
#define STR_ENTER_29				("e29")
#define STR_ENTER_30				("e30")
#define STR_ENTER_31				("e31")
#define STR_ENTER_32				("e32")
#define STR_ENTER_33				("e33")
#define STR_ENTER_34				("e34")
#define STR_ENTER_35				("e35")
#define STR_ENTER_36				("e36")
#define STR_ENTER_37				("e37")
#define STR_ENTER_38				("e38")
#define STR_ENTER_39				("e39")
#define STR_ENTER_40				("e40")
#define STR_ENTER_41				("e41")
#define STR_ENTER_42				("e42")
#define STR_ENTER_43				("e43")
#define STR_ENTER_44				("e44")
#define STR_ENTER_45				("e45")
#define STR_ENTER_46				("e46")
#define STR_ENTER_47				("e47")
#define STR_ENTER_48				("e48")
#define STR_ENTER_49				("e49")
#define STR_ENTER_50				("e50")



//入口的类型。。
#define	ENTER_MENU_OUTSIDE		("0")//在外头找菜单。。
#define	ENTER_MENU_SUB			("1")//子链表为菜单项
#define	ENTER_APP					("2")//直接进入应用，入口为子菜单第一项

//***********************add by dk end****************************************
///////
//gtsbox core
xl_int32 gbx_start_app(xl_wchar* fname);
xl_void gbx_quit_current_app(xl_void);
xl_void gbx_on_pen_event(gtsbox_pen_event evt, xl_int16 x, xl_int16 y);
xl_void gbx_on_key_event(xl_int32 keycode);
xl_void gbx_app_create(xl_void);
xl_void gbx_app_active(xl_void);
xl_void gbx_app_inactive(xl_void);
//check if app(static or not) is running
xl_bool gbx_is_app_running(xl_void);
//force quit current app
xl_void gbx_app_force_quit(xl_void);
xl_int32 gbx_core_start(xl_void);
xl_void gbx_core_quit(xl_void);

//////
//gtsbox network
xl_void gtsbox_http_release(xl_void);
xl_void gtsbox_http_download_app(xl_uint32 app_id, gtsbox_http_mission_pri_enum  pri, xlite_E_http_event_handler handler);
xl_void gtsbox_http_download_cancel(xl_void(*callback)(xl_int32 evt, xl_int32 param));
//download from url, save to file
xl_void gtsbox_http_download(xl_char* url, xl_char* fullpath, xl_void(*callback)(xl_int32 evt, xl_int32 param));
//sys callback
xl_void gtsbox_http_callback(xl_int32 evt, xl_int32 param);
// create mission by request and event handler
gtsbox_http_mission_struct* gbx_http_mission_create(xlite_http_request* request, xlite_E_http_event_handler handler);
// release mission
gtsbox_http_mission_struct* gbx_http_mission_release(gtsbox_http_mission_struct* mission);
// add a mission to mission list
xl_void gbx_http_mission_add(gtsbox_http_mission_struct* mission);
// set auto save file, null is don't save file
xl_void gbx_http_mission_set_save_file(gtsbox_http_mission_struct* mission, xl_wchar* fullpath);
//重命名临时文件
xl_void gbx_http_mission_rename_save_file(gtsbox_http_mission_struct* mission);
//删除临时文件
xl_void gbx_http_mission_delete_save_file(gtsbox_http_mission_struct* mission);
// 设置代理模式，有四种
xl_void gbx_http_mission_set_proxy(gtsbox_http_mission_struct* mission,  gtsbox_http_mission_proxy_enum proxy);
//取消当前所有联网
xl_void gtsbox_app_cancel_all_network(xl_void);


//gtsbox app manager
xl_int32 gbx_check_app_file(xl_wchar* full_path_name);
xl_void gbx_add_dynamic_app_to_list(xl_wchar* fullpath);
xl_int32 gbx_set_current_app_by_app_id(xl_int32 app_id);
xl_void gbx_set_current_app(gtsbox_app_info_struct* app);
gtsbox_app_info_struct*  gbx_get_current_app(xl_void);
xl_int32 gbx_start_current_app(xl_void);
xl_void gbx_delete_current_app(xl_void);

//gtsbox common
xl_char* gbx_get_root_path(xl_void);
default_app_info_struct* gbx_get_default_app_info_array(xl_void);
xl_bool gbx_get_file_buffer(xl_char *pathdat,xl_char **buffer);


//gtsbox charge
xl_uint32 gbx_get_origin_id(xl_void);
xl_char* gbx_get_device_id(xl_void);
//other
xl_void gbx_set_screen_rotate(xl_int32 rotate);
xl_int32 gbx_get_screen_rotate(xl_void);

/************************************************************************/
/* func declaration                                                						      */
/************************************************************************/

xl_void gbx_menuitem_push(menuitem_data_t* mData,xml_node *node);
xl_void gbx_menuitem_pop();
xl_void gbx_release_all_menuitem_node();
menuitem_data_t* get_stack_top_menuitem();
xl_uint32 get_stack_menuitem_number();
xl_void gbx_release_curt_menuitem();
xl_void gbx_dynamicmenu_on_enter(xml_node *node);
xl_void gbx_create_menuItem_list(xml_node *node,xl_char* attrName);
xl_void gbx_get_history_highlight_mItemIndex();
xl_void gbx_set_highlight_mItemIndex();
xl_int32 gbx_connect_menuItem(xl_char *entryMenuID,xl_int32 appID);
xl_void gbx_enter_app_screen(xl_void);
xl_void gbx_release_dynamicMenu(xl_void);
xl_void gbx_set_menuEntryID(xl_char *entryID);
xlite_list* gbx_get_app_list(xl_void);
xl_void gbx_set_app_list_index(xl_int32 idx);
xl_int16 gbx_get_app_list_index(xl_void);
xml_node* gbx_get_crt_highlight_menuitem_node(xl_void);
xl_wchar* gbx_get_hilight_app_id(xl_void);
xl_wchar* gbx_get_menu_content(xl_void);
xl_wchar* gbx_get_menu_title(xl_void);
xlite_list* gbx_get_menuItem_list(xl_void);
xl_bool gbx_is_in_menuList(xl_void);
xl_void gbx_set_in_menuList(xl_bool b);
xl_void gbx_reset_menu_title(xl_void);
xl_void gbx_reset_menu_content(xl_void);
xl_bool gbx_is_dynamicmenu_file_exist(xl_void);
xl_void gtsbox_app_push_download(xl_void);

#endif
