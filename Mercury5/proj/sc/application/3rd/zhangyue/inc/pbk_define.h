#if defined(__ZYUE_ENGINE__)
#ifndef PBK_DEFINE_H
#define PBK_DEFINE_H

//实现某些接口功能定义的
#include "pbk_platform_define.h"

typedef struct __PBK_LAYER_DATA
{
	c_uint32 app_id;
	c_uint32 gdi_handle;
	c_uint32 l_param;
}PBK_LAYER_DATA;

typedef enum __PBK_SIM_INDEX
{
	PBK_SIM_INDEX_1 = 0, 
	PBK_SIM_INDEX_2 = 1,

	PBK_SIM_INDEX_MAX
}PBK_SIM_INDEX;

typedef struct __PBK_MEDIA_INFO
{
	c_int32     audio_vol;
	c_int32   	audio_path;
	c_int32		vibrator_timer_id;
}PBK_MEDIA_INFO;

typedef struct __PBK_SYS_CTRL_INPUT
{
	c_uint8* title;
	c_uint8* buf;
	c_uint32 max_len;
	c_uint32 input_type;
}PBK_SYS_CTRL_INPUT;

typedef struct __PBK_SYS_CTRL_TEXTVIEW
{
	c_uint8* title;
	c_uint8* text;
	c_int32 text_size;
}PBK_SYS_CTRL_TEXTVIEW;

typedef struct __PBK_SYS_CTRL_PHB
{
	c_uint8* select_name;
	c_uint8* select_num;
}PBK_SYS_CTRL_PHB;

typedef struct __PBK_SYS_CTRL_FILEMGR
{
	c_uint8* select_file;
}PBK_SYS_CTRL_FILEMGR;

typedef struct __PBK_SYS_CTRL_LIST
{
	c_uint8* title;
	c_uint8** items;
	c_int32 num;
	c_uint32  select_item_index;
}PBK_SYS_CTRL_LIST;

typedef struct __PBK_SYS_CTRL_SMS
{
	c_uint8*  sms_content;
	c_uint8*  sms_addr;
}PBK_SYS_CTRL_SMS;

typedef struct __PBK_SYS_CTRL_DATA
{
	PBK_SYS_CTRL_INPUT input_editor;
	PBK_SYS_CTRL_TEXTVIEW text_view;
	PBK_SYS_CTRL_PHB phb_info;
	PBK_SYS_CTRL_FILEMGR file_mgr;
	PBK_SYS_CTRL_LIST  list_box;
	PBK_SYS_CTRL_SMS  send_sms;
	PBK_SYS_CALLBACK cb;
	void* cb_data;
	c_uint32 app_id; //如果回调回来时，这个app已经关闭了，是不能执行的
}PBK_SYS_CTRL_DATA;


typedef struct __PBK_SMS_PROCESS_RESULT
{
	c_uint32 type; //1confirm 2filter
	c_uint32 is_tip; //
	void* data; //PBK_SMS_CONFIRM_ITEM
	c_uint32 reserved[4];
}PBK_SMS_PROCESS_RESULT;

typedef struct __PKB_APP_UPDATE_INFO
{
	c_int32	is_update_start;
	c_uint32	file_id;
	c_int32	try_count;
	c_int32	file_size;
	c_int32	curr_size;
	c_int32 old_size; //下载前的大小
	c_int32	is_run;			// is run after update
	//c_int32	tip_type;		// is update at bg
	PBK_APP_UPDATE_CALLBACK action_cb;
	c_int32 	app_ver;
	PBK_HTTP_DATA*http_data;
	c_wchar	*filename; //[PBK_APP_NAME_LEN];
	char	*arg; //[PBK_APP_ARG_LEN];

	c_uint32 tip_type; //PBK_APP_UPDATE_TIP_TYPE
}PKB_APP_UPDATE_INFO;

#define PBK_LAYER_MAX_NUM 4 //最多同时能支持的图层
#define PBK_SOC_MAX_NUM 4 //最多同时支持4个socket

typedef struct
{
    S16 x;
    S16 y;
} mmi_pen_point_struct;

#if 0

//////////////////////////////////////
//模拟任务调度
typedef enum __PBK_TASK_STATE
{
    PBK_TASK_INVALID = -1,/* 无效的ID */
    PBK_TASK_FREE = 0,
    PBK_TASK_TO_DO = 1,
    PBK_TASK_DOING = 2,
}PBK_TASK_STATE;

typedef enum __PBK_TASK_RES_STATE
{/* 共通使用的资源的状态 */
    PBK_TASK_RES_FREE = 0,
    PBK_TASK_RES_BUSY,
}PBK_TASK_RES_STATE;

typedef void (*pbk_task_cb)(void* data);

#endif

#endif
#endif
