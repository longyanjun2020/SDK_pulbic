// xstrike Lite engine
// type definition
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_type.h 99 2008-08-29 09:53:31Z royal $
#ifndef __XLITE_TYPE_H__
#define __XLITE_TYPE_H__

/*!
 * @file xLite_type.h
 * @brief xstrike lite 类型定义
 */


// type definition
/*! 32位有符号整型 */
typedef int					xl_int32;
/*! 32位无符号整型 */
typedef unsigned int		xl_uint32;
/*! 16位有符号整型 */
typedef short				xl_int16;
/*! 16位无符号整型 */
typedef unsigned short		xl_uint16;
/*! 8位有符号整型 */
typedef signed char			xl_int8;
/*! 8位无符号整型 */
typedef unsigned char		xl_uint8;
/*! 64位有符号整型 */
typedef __int64				xl_int64;
/*! 64位无符号整型 */
typedef unsigned __int64	xl_uint64;
/*! void */
typedef void				xl_void;
/*! boolean */
typedef xl_int32			xl_bool;
/*! wide char */
typedef xl_uint16			xl_wchar;
/*! char */
typedef char				xl_char;
/*! 565格式颜色 */
typedef xl_uint16			xl_color;
/*! float */
typedef float				xl_float;
/*! 无参函数指针 */
typedef xl_void			(*xl_func_ptr)(xl_void);

//////////////////////////////////////////////////////////////////////////
// MACRO
//////////////////////////////////////////////////////////////////////////
/*! 求最小值 */
#define XLITE_MIN(a,b)					((a) > (b) ? (b) : (a))
/*! 求最大值 */
#define XLITE_MAX(a,b)					((a) > (b) ? (a) : (b))

		
/*
 * @brief 获取xlite_pf_rgb_565的像素中red分量的值
 * @param c 颜色
 * @return red分量的值
 */
#define XLITE_GET_RED(c)					( (xl_uint8)( ( ( (c) & 0xF800 ) >> 11 ) << 3 ) )

/*
 * @brief 获取xlite_pf_rgb_565的像素中green分量的值
 * @param c 颜色
 * @return green分量的值
 */
#define XLITE_GET_GREEN(c)					( (xl_uint8)( ( ( (c) & 0x7E0 ) >> 5 ) << 2 ) )

/*
 * @brief 获取xlite_pf_rgb_565的像素中blue分量的值
 * @param c 颜色
 * @return blue分量的值
 */
#define XLITE_GET_BLUE(c)					( (xl_uint8)( ( ( (c) & 0x1F) << 3) ) )



// constant definition

#define XL_NULL							0
#define XL_TRUE							1
#define XL_FALSE						0
#define XLITE_MAX_PATH					0xFF
#define XLITE_MAX_URL					0xFF

/*! open file for read */
#define XLITE_FILE_READ					0x01
/*! open file for read and write */
#define XLITE_FILE_WRITE				0x02
/*! open file for read and write,destroy content if file already existed. */
#define XLITE_FILE_CREATE_ALWAYS		0x04
/*! open file, if it does not exist, creat it */
#define XLITE_FILE_CREATE				0x08


#	define XLITE_SEEK_BEGIN				0 // FS_FILE_BEGIN
#	define XLITE_SEEK_CURRENT			1 //FS_FILE_CURRENT
#	define XLITE_SEEK_END				2 //FS_FILE_END


//////////////////////////////////////////////////////////////////////////
// xLite_memory.h
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief 内存调试信息
 */
typedef struct  
{
	xl_uint32	alloc_called_times;				/*!< xlite_mem_alloc的调用次数 */
	xl_uint32	free_called_times;				/*!< xlite_mem_free的调用次数 */
	xl_uint32	total_alloced_size;				/*!< 当前申请的内存的字节数 */
	xl_uint32	max_once_alloced_size;			/*!< 单次最大申请的内存的字节数 */
	xl_uint32	max_total_alloced_size;			/*!< 内存申请的字节数峰值 */
} xlite_mem_debug_info;

//////////////////////////////////////////////////////////////////////////
// xLite_directscreen.h
//////////////////////////////////////////////////////////////////////////
/*!
 * @struct xlite_directscreen xLite_type.h "xLite_directscreen.h"
 * @brief DirectScreen 结构
 * @sa xLite_directscreen.h
 */
typedef struct  
{
	xl_int32 screen_width;				/*!< 屏幕的宽度 */
	xl_int32 screen_height;				/*!< 屏幕的高度 */
	xl_uint8* buffer_ptr;				/*!< 屏幕缓冲的指针 */
	xl_int32 bit_per_pixel;				/*!< 屏幕缓冲的格式 */

	xl_void* handle;					/*!< 平台相关句柄 */
} xlite_directscreen;




//////////////////////////////////////////////////////////////////////////
// xLite_version.h
//////////////////////////////////////////////////////////////////////////

/*!
 * @struct xlite_version xLite_type.h "xLite_version.h"
 * @brief xlite 版本信息
 */
typedef struct  
{
	xl_uint32			platform_id;		/*!< 平台ID */
	xl_uint32			sdk_version;		/*!< SDK ID */
	
	xl_uint32			major;				/*!< 引擎主版本号 */
	xl_uint32			minor;				/*!< 引擎副版本号 */
	xl_uint32			reserved;			/*!< 保留 */

} xlite_version;


//////////////////////////////////////////////////////////////////////////
// xLite_sys.h
//////////////////////////////////////////////////////////////////////////
typedef xl_void (* xlite_timer_func)(xl_void);
typedef xl_void (* xlite_sms_callback)(xl_int32);
typedef xl_void (* xlite_sys_callback)(xl_int32, xl_int32);

typedef enum
{
	XLITE_SYS_CALLBACK_NONE,

	XLITE_SYS_CALLBACK_SMS,
	XLITE_SYS_CALLBACK_GPRS_ACCOUNT,
	XLITE_SYS_CALLBACK_IMSI,
	XLITE_SYS_CALLBACK_IMEI,
	XLITE_SYS_CALLBACK_AREA_CODE,

	
	XLITE_SYS_CALLBACK_END
}xlite_sys_callback_enum;



#define XLITE_SYS_SEND_SMS_ERR_NO_ERROR					0
#define XLITE_SYS_SEND_SMS_ERR_NO_SERVICE				-1
#define XLITE_SYS_SEND_SMS_ERR_NOT_READY				-2
#define XLITE_SYS_SEND_SMS_ERR_OTHER_SMS_PROCESSING		-3
#define XLITE_SYS_SEND_SMS_ERR_APPEND_EMS_ERROR		-4
#define XLITE_SYS_SEND_SMS_ERR_OTHER_ERROR		-5

/*!
 * @brief 日期时间数据结构
 */
typedef struct  
{
	xl_uint16	year;		/*!< 年 */
	xl_uint8	month;		/*!< 月 */
	xl_uint8	day;		/*!< 日 */
	xl_uint8	hour;		/*!< 小时 */
	xl_uint8	minute;		/*!< 分钟 */
	xl_uint8	second;		/*!< 秒 */
	xl_uint8	day_index;	/*!< 星期索引,0 = 星期日*/
} xlite_date_time;


/*!
 * @brief SIM卡通信商
 */
typedef enum
{
	xlite_operator_unknown,			/*!< 未知的 */
	xlite_operator_cmcc,				/*!< 中国移动 */
	xlite_operator_unicom			/*!< 中国联通 */
} xlite_operator;

/*!
 * @brief 接入点类型
 */

typedef enum
{
	xlite_gprs_account_invalid,
	xlite_gprs_account_cmwap,
	xlite_gprs_account_cmnet,
	xlite_gprs_account_uniwap,
	xlite_gprs_account_uninet
} xlite_gprs_account;


//////////////////////////////////////////////////////////////////////////
// xLite_file.h
//////////////////////////////////////////////////////////////////////////
typedef void*			xlite_file_handle;
typedef enum
{
	xlite_driver_system,
	xlite_driver_normal,
	xlite_driver_removable
} xlite_driver_type;


//////////////////////////////////////////////////////////////////////////
// structures

/*!
 * @brief 保存搜索文件结果的数据结构
 */
typedef struct
{
	xl_wchar path_name[XLITE_MAX_PATH];			/*!< 完整的文件名 */
	xl_uint32 file_size;						/*!< 文件的字节数 */
	xl_bool is_folder;							/*!< 是否为目录 */
	xl_uint16 number_index;				/*!<找到的第几个*/
} xlite_file_find_info;


typedef struct
{
	xl_wchar path_name[XLITE_MAX_PATH];			/*!< 完整的文件名 */
	xl_uint32 file_size;						/*!< 文件的字节数 */
	xlite_date_time create_time;				/*!< 创建的日期 */
	xlite_date_time access_time;				/*!< 访问的日期 */
	xlite_date_time write_time;				/*!< 修改的日期 */
} xlite_file_info;

/*!
 * @brief 
 * @note 如果回调函数返回XL_TRUE继续搜索下一个符合条件的文件,否则中断搜索
 */
typedef xl_bool(* xlite_file_find_callback)(const xlite_file_find_info* ffi);

//////////////////////////////////////////////////////////////////////////
// xlite_socket.h
//////////////////////////////////////////////////////////////////////////

//操作成功
#define XLITE_SOCKET_SUCCESS				(0)
//操作失败
#define XLITE_SOCKET_ERROR					(-1)
//阻塞，需等待
#define XLITE_SOCKET_WOULDBLOCK				(-2)
//操作中，需重试
#define XLITE_SOCKET_IN_PROGRESS			(-3)
//socket非法
#define XLITE_SOCKET_INVALID_SOCKET			(-4)
//非法host地址
#define XLITE_SOCKET_INVALID_ADDR			(-5)
//#define XLITE_SOCKET_OPNOTSUPP				(-8)		
//#define XLITE_SOCKET_CONNABORTED			(-9)
//#define XLITE_SOCKET_INVAL					(-10)
//#define XLITE_SOCKET_PIPE					(-11)
//#define XLITE_SOCKET_NOTCONN				(-12)
//#define XLITE_SOCKET_MSGSIZE				(-13)
//#define XLITE_SOCKET_BEARER_FAIL			(-14)
//#define XLITE_SOCKET_CONNRESET				(-15)

#define XLITE_SOCKET_MAX_OPEN_LIMITED		(-100)
#define XLITE_SOCKET_CANT_FIND_IN_SLOT		(-101)

#define XLITE_INVALID_SOCKET				(-1)

typedef enum 
{
	xlite_socket_pf_inet	= 0			//PF_INET,
} xlite_socket_domain;

typedef enum
{
	xlite_socket_stream		= 0,			// SOCK_STREAM
	xlite_socket_dgram		= 1,			// SOCK_DGRAM
	xlite_socket_sms		= 2,			// SOCK_SMS
	xlite_socket_raw		= 3				// SOCK_RAW
} xlite_socket_type;

typedef enum
{
	xlite_socket_ip			= 0,
	xlite_socket_tcp		= 6,
	xlite_socket_udp		= 17
} xlite_socket_protocol;

typedef enum
{
	xlite_socket_sd_receive = 0x01,
	xlite_socket_sd_send = 0x02,
	xlite_socket_sd_both = (xlite_socket_sd_receive | xlite_socket_sd_send)
} xlite_socket_shutdown_flag;


typedef enum
{
	xlite_socket_opt_nbio	= 0x04,
	xlite_socket_opt_async	= 0x08
} xlite_socket_option;

typedef enum
{
	xlite_socket_event_read		= 0x01,
	xlite_socket_event_write	= 0x02,
	xlite_socket_event_accept	= 0x04,
	xlite_socket_event_connect	= 0x08,
	xlite_socket_event_close	= 0x10
} xlite_socket_event;

typedef struct  
{
	xl_uint32 sec;
	xl_uint32 usec;		// micro-secont
} xlite_socket_timeval;


/*
 * @brief 事件处理函数
 * @param ptr xlite_socket_handle 指针
 * @param e 事件
 */
typedef xl_void(* xlite_socket_event_handler)(xlite_socket_event evt,xl_int32 error_no,xl_void* user_param);




typedef xl_int32						xlite_socket;

#define XLITE_MAX_SOCK_ADDR_LEN 28

typedef struct 
{
    xl_int16	addr_len;
    xl_uint16	port;
    xl_uint8	addr[XLITE_MAX_SOCK_ADDR_LEN];
} xlite_socket_sockaddr_struct;

//同时可以打开的最大的socket数
#define XLITE_MAX_SOCKET_NUM 6

typedef struct
{
   xl_uint8	fds_bits[XLITE_MAX_SOCKET_NUM];
} xlite_fd_set;


/*!
 * @brief get host by name event handle
 */
typedef xl_void(* xlite_socket_gethostbyname_event_handler)(xlite_socket_sockaddr_struct* sock_addr,xl_int32 request_id,xl_int32 result,xl_void* handler_param);


//////////////////////////////////////////////////////////////////////////
// xlite_drawtext.h
//////////////////////////////////////////////////////////////////////////
typedef enum {
	xlite_font_size_small		= 0,
	xlite_font_size_medium,
	xlite_font_size_large
} xlite_font_size;


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// xLite_E_input_screen.h
//////////////////////////////////////////////////////////////////////////
#define XLITE_INPUT_SCREEN_OK					XL_TRUE
#define XLITE_INPUT_SCREEN_CANCEL				XL_FALSE

#define XLITE_INPUT_SCREEN_TYPE_NONE							0
#define XLITE_INPUT_SCREEN_TYPE_NUMBERIC						1
#define XLITE_INPUT_SCREEN_TYPE_ALPHANUMBERIC_UPPERCASE			2
#define XLITE_INPUT_SCREEN_TYPE_ALPHANUMBERIC_LOWERCASE			3
#define XLITE_INPUT_SCREEN_TYPE_ALPHANUMBERIC_SENTENCECASE		4
#define XLITE_INPUT_SCREEN_TYPE_NUMBERIC_PASSWORD				5
#define XLITE_INPUT_SCREEN_TYPE_ALPHANUMBERIC_PASSWORD			6




typedef xl_void (* xlite_input_screen_callback)(xl_void* user_param,xl_uint32 ctrl_id,xl_int32 ok_cancel);

// 调用xlite_E_input_screen_show的参数
typedef struct  
{
	
	xl_int16  type;
	xl_uint16 id;		// 用来标记是由什么发起的,可以填0
	xl_uint8* buffer;
	xl_uint32 buf_len;
	
	xlite_input_screen_callback callback;
	xl_void* callback_param;
} xlite_input_screen_param;

//////////////////////////////////////////////////////////////////////////
// xlite_audio.h
//////////////////////////////////////////////////////////////////////////

typedef xl_int32 xlite_audio_handle;

//////////////////////////////////////////////////////////////////////////
// xlite_sensor.h
//////////////////////////////////////////////////////////////////////////

#define XLITE_SENSOR_TYPE_NONE	0
#define XLITE_SENSOR_TYPE_XY		2
#define XLITE_SENSOR_TYPE_XYZ		3

#define XLITE_SENSOR_AXIS_NOFLIP 1
#define XLITE_SENSOR_AXIS_FLIP (-1)

//value range, don't edit it, by wxb
#define XLITE_SENSOR_VALUE_RANGE (100)
#define XLITE_SENSOR_ROTATE_RANGE (360)

//////////////////////////////////////////////////////////////////////////
// xlite_log.h
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief 日志输出等级
 */
typedef enum
{
	xlite_log_message,
	xlite_log_warning,
	xlite_log_error,
	xlite_log_misc
} xlite_log_level;

//////////////////////////////////////////////////////////////////////////
// xlite_assert.h
//////////////////////////////////////////////////////////////////////////

typedef enum
{
	XLITE_ASSERT_LEVEL1, //永远不关闭的会导致系统崩溃的错误
	XLITE_ASSERT_LEVEL2,
	XLITE_ASSERT_LEVEL3,
	XLITE_ASSERT_LEVEL4
} xlite_assert_level;

#endif


