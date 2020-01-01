#ifndef _MOBILE_ALLIANCE_TYPE_DEF_H_
#define _MOBILE_ALLIANCE_TYPE_DEF_H_

#ifdef  __cplusplus
extern "C" 
{
#endif

//typedef void				zm_void;
#define zm_void 			void
typedef char				zm_int8;
typedef unsigned char		zm_uint8;
typedef short				zm_int16;
typedef unsigned short		zm_uint16;
typedef int				zm_int;
typedef unsigned int		zm_uint;
typedef long				zm_int32;
typedef unsigned long		zm_uint32;
typedef float				zm_real32;
typedef double			zm_real64;
typedef char				zm_bool;
typedef zm_int32			zm_hwnd;		/*窗口句柄*/
typedef zm_int32			zm_color;		/*RGB颜色*/
typedef zm_int			zm_net_handle;	/*无限数据网络连接句柄*/
typedef void				zm_file;		/*文件句柄*/
typedef void*			zm_func_ptr;	/*函数指针*/

#ifdef  __cplusplus
};
#endif

#ifndef zm_invalid_net_handle
#define zm_invalid_net_handle -1
#endif

#ifndef zm_null
#define zm_null		0
#endif

#ifndef zm_true
#define zm_true		1
#endif

#ifndef zm_false
#define zm_false	0
#endif

#ifdef __cplusplus
#define zm_extern extern "C"
#else
#define zm_extern extern
#endif

typedef enum stZM_KeyCode
{
	ZM_EKeyNum0 = 0,
	ZM_EKeyNum1,
	ZM_EKeyNum2,
	ZM_EKeyNum3,
	ZM_EKeyNum4,
	ZM_EKeyNum5,
	ZM_EKeyNum6,
	ZM_EKeyNum7,
	ZM_EKeyNum8,
	ZM_EKeyNum9,
	ZM_EKeySoftLeft,
	ZM_EKeySoftRight,
	ZM_EKeySoftCSK,
	ZM_EKeyUp,
	ZM_EKeyDown,
	ZM_EKeyLeft,
	ZM_EKeyRight,
	ZM_EKeySoftSend,
	ZM_EKeySoftEnd,
	ZM_EKeySoftClear,
	ZM_EKeyStar,
	ZM_EKeyHash,
	ZM_EKeyVolUp,
	ZM_EKeyVolDown,
	ZM_EKeyQuickAcs,
	ZM_EKeyCamera=ZM_EKeyQuickAcs,
	ZM_EKeySoftOk,	
	ZM_EKeyWap,
	ZM_EKeyIp,
	ZM_EKeyMax/* max key codes support */	
}ZM_KeyCode;

typedef enum
{
	ZM_EKeyEventDown = 10,
	ZM_EKeyEventUp,
	ZM_EKeyEventLongPress,
	ZM_EKeyEventRepeat
}ZM_KeyEvent;

typedef enum
{
	ZM_EKeyWasNotConsumed,
	ZM_EKeyWasConsumed
} ZM_KeyResponse;

typedef enum
{
	ZM_EPenDown = 20,
	ZM_EPenUp,
	ZM_EPenMove
} ZM_PenEvnent;

/*
 *	字体类型定义
 */
typedef enum
{
	zm_font_normal = 1,		/*normal font*/
	zm_font_small, 			/*small font*/
	zm_font_large,          /*large font*/
	zm_font_unicode 		/*unicode font*/
}zm_font_type;

/*
 * 输入法定义
 */
typedef enum
{
	zm_input_abc,
	zm_input_123,
	zm_input_password,
	zm_input_pinyin
}zm_input_type;

/*
 *	文本编码方式定义
 */
typedef enum
{
	zm_unicode,		/*unicode coding*/
	zm_utf8,		/*utf8 coding*/
	zm_ascii		/*ascall coding*/
}zm_encoding_type;

/*
 *	图片格式
 */
typedef enum
{
	zm_img_bmp =0,
	zm_img_png,
	zm_img_jpg,
	zm_img_gif,
	zm_img_unknow
}zm_img_format;

/*
 *	画图片方式
 */
typedef enum
{
	zm_rop_copy = 1,	/*拷贝到目标设备上*/
	zm_rop_xor			/*和目标设备上的做 xor 运算*/
}zm_bitblt_rop;

/*
 *	文本对齐方式, 垂直方向采用VCENTER
 */
typedef enum
{
	zm_text_left	= 0x01,
	zm_text_right	= 0x02,
	zm_text_center	= 0x04
}zm_text_align;

/*
 *	网络类型
 */
typedef enum
{
	network_mobile = 0,	/* china mobile */
	network_unicom,		/* GSM network of china unicom */
	network_cdma,		/* CDMA network of China unicom */
	network_unkown		/* Unknow network: just not send SMS */
}zm_network_type;

/*
 *	无线数据连路状态
 */
typedef enum
{
	zm_netstate_connteted,		/*the connect request is confirmed with success*/
	zm_netstate_connect_fail,	/*the connect request is confirmed with FALSE*/
	zm_netstate_disconnect,		/*the connect was disconnected*/
	zm_netstate_receive,		/*data is received via the connect*/
	zm_netstat_gethostname,		/*域名解析成功*/
	zm_netstate_send_error,
	zm_netstate_write
}zm_net_state;

/*
 *	无线数据网络类型
 */
typedef enum
{
	zm_cmnet,	/*gprs cmnet, connect driction*/
	zm_cmwap	/*gprs cmwap, connect mobile proxy(10.0.0.172)*/
}zm_gprs_type;

/*
 *	文件定位 whence 定义
 */
typedef enum
{
    zm_seek_cur=0, /*current position of file pointer*/
    zm_seek_end, /*end of file*/
    zm_seek_set	 /*beginning of file*/
}zm_file_seek_type;

/*
 *	颜色表定义定义
 */
#define ZM_COLOR_TRANSLAT		(-1)
#define ZM_COLOR_WHITE			zm_get_rgb_color(0xff,0xff,0xff)
#define ZM_COLOR_BLACK			zm_get_rgb_color(0x0,0x0,0x0)
#define ZM_COLOR_MENUBAR_FRAME	zm_get_rgb_color(0x0,0x0,0x0)
#define ZM_COLOR_MENUBAR_BG		zm_get_rgb_color(0,81,162)
#define ZM_COLOR_MENUBAR_FG		zm_get_rgb_color(0xff,0xff,0xff)
#define ZM_COLOR_ICON_SELECTED	zm_get_rgb_color(0x0F,0xAD,0xFF)
#define ZM_COLOR_TEXT_SELECTED	zm_get_rgb_color(0x0F,0xAD,0xFF)
#define ZM_COLOR_CAPTION_FG		zm_get_rgb_color(0xff,0xff,0xff)
#define ZM_COLOR_CAPTION_BG		zm_get_rgb_color(0x0F,0xDF,0xFF)
#define ZM_COLOR_FOCUS_BG		zm_get_rgb_color(117,186,255)
#define ZM_COLOR_GRAY			zm_get_rgb_color(120,127,127)

typedef struct
{
	zm_int16 left;
	zm_int16 top;
	zm_int16 width;
	zm_int16 height;
}zm_rect;

typedef struct
{
	zm_int16 x;
	zm_int16 y;
}zm_point;

typedef struct
{
	zm_int16 cx;
	zm_int16 cy;
}zm_size;

typedef struct
{
	zm_int tm_hour;			/* hours */
	zm_int tm_min;			/* minutes */
	zm_int tm_sec;			/* seconds */	

	zm_int tm_year;			/* year */
	zm_int tm_mon;			/* month */
	zm_int tm_mday;			/* day of the month */	
	
	zm_int tm_wday;			/* day of the week */
	zm_uint32 tm_time_sec;	/* time_t*/
}zm_tm;

/*
 * GPRS receive data buffer struct
 */
typedef struct
{
	zm_int8*  buf;
	zm_uint32 length;
}zm_net_message;


/*
 * 无限数据链路 event callback function interface
 *  @pMess, 如果事件无数据可以为 zm_null, pMess->buf 的内存所有全归回调函数的调用方
 */
typedef zm_void (*ZM_NetCallbackFuncPtr)(zm_net_handle lHandler,zm_net_state nState, zm_net_message* pMess);

/*
 *	按键回调函数
 */
typedef ZM_KeyResponse (*ZM_OfferKeyEventFuncPtr)(ZM_KeyEvent event, ZM_KeyCode code);

/*
 *	触笔回调函数
 */
typedef zm_void (*ZM_OfferPenEventFuncPtr)(ZM_PenEvnent event, zm_point* pt);

/*
 *	菜单事件
 */
typedef zm_void (*ZM_MenuCmdHandlerFuncPtr)(zm_uint32 cmdId , zm_uint32 lparam);

/*
 * 资源提供 provider
 */
typedef zm_void (*zm_resource_provider)(zm_int id, zm_int8** pBuf, zm_int* len);

#ifdef ZMOL_NO_GLOBAL_VAR
//#define __align(n)  __attribute__((aligned(4))) 
#endif

#endif/*_MOBILE_ALLIANCE_TYPE_DEF_H_*/
