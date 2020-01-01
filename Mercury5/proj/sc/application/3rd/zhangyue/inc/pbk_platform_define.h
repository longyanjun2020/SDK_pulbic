#if defined(__ZYUE_ENGINE__)
#ifndef PBK_PLATFORM_DEFINE_H
#define PBK_PLATFORM_DEFINE_H

//只包含宏定义，类型定义，结构体，枚举等

#define PBK_PLATFORM_V6000 //版本控制宏
#define PBK_PLATFORM_V6100

//c type
typedef unsigned char       c_uint8;
typedef unsigned short      c_uint16;
typedef unsigned int        c_uint32;
#ifdef WIN32
typedef unsigned __int64    c_uint64;
#else
typedef unsigned long long  c_uint64;
#endif
typedef signed char         c_int8;
typedef signed short        c_int16;
typedef signed int          c_int32;
typedef unsigned short      c_wchar;

#ifndef WIN32
/*
typedef c_int32 *va_list[1];
#define va_start(ap, parmN) (void)(*(ap) = __va_start(parmN))
#define va_arg(ap, type) __va_arg(*(ap), type)
#define va_copy(dest, src) ((void)(*(dest) = *(src)))
#define va_end(ap) ((void)(*(ap) = 0))
*/
#include "stdarg.h"
#else
#include <windows.h>
#endif

#ifndef WIN32
#define PBK_ALIGN __align(4)
#else
#define PBK_ALIGN
#endif

//common
//http://hi.baidu.com/nettechfans/blog/item/655449d83adc992a11df9bf9.html
#define PBK_INT_ALIGN(d, a) (((d) + (a - 1)) & ~(a - 1))
#define PBK_ABS(x) ((x) >= 0 ? (x) : -(x))
#define PBK_MAX(a,b) ((a)>(b)?(a):(b))
#define PBK_MIN(a,b) ((a)<(b)?(a):(b))
#define PBK_RGB_2_565(c) (((c & 0xf80000)>>8)|((c&0xfc00)>>5)|((c&0xf8)>>3))
#define PBK_RGB_2_565_2(r, g, b)  ((((c_uint16)r << 8) & 0xF800) | (((c_uint16)g << 3) & 0x07E0) |(((c_uint16)b >> 3) & 0x001F))
#define PBK_565_R(c) ((c & 0xF800) >> 8)
#define PBK_565_G(c) ((c & 0x07E0) >> 3)
#define PBK_565_B(c) ((c & 0x001F) << 3)
#define PBK_RGB_888_R(c) (c & 0x000000FF)
#define PBK_RGB_888_G(c) ((c & 0x00FF00) >> 8)
#define PBK_RGB_888_B(c) ((c & 0xFF0000) >> 16)

#define PBK_RGB_2_888(c)(VEN_MAKE_RGB888((PBK_RGB_888_B(c)),(PBK_RGB_888_G(c)),(PBK_RGB_888_R(c))))

#if defined(PBK_LOG_ON)
#define PBK_TRACE(ARG)  (pbk_log ARG)
#else
#define PBK_TRACE(ARG) ((void)0)
#endif


/***********************************************
//0: platform ex api
//平台相关扩展
************************************************/
#ifdef PBK_PLATFORM_V6000
typedef struct __PBK_NAME_VALUE
{
    char* name;
    char* value;
}PBK_NAME_VALUE;
#endif

/***********************************************
//1: standard c
//标准c库部分函数
************************************************/
#ifdef PBK_PLATFORM_V6000
#endif

/***********************************************
//2: encoding unicode
//字符编码转换和unicode字符串操作
************************************************/
#ifdef PBK_PLATFORM_V6000
typedef enum __PBK_STR_ENCODE_TYPE
{
    PBK_STR_ENCODE_GB2312 = 1,  //liuwp20100424
    PBK_STR_ENCODE_UNICODE,
    PBK_STR_ENCODE_UTF8,

    PBK_STR_ENCODE_TYPE_MAX
}PBK_STR_ENCODE_TYPE;
#endif

/***********************************************
//3: memory
//内存
************************************************/



/***********************************************
//4: file
//文件系统
************************************************/
#ifdef PBK_PLATFORM_V6000
#define PBK_FILE_SEEK_BEGIN 0
#define PBK_FILE_SEEK_CUR 1
#define PBK_FILE_SEEK_END 2

#define PBK_FILE_ATTR_READ_ONLY 0x01
#define PBK_FILE_ATTR_HIDDEN        0x02
#define PBK_FILE_ATTR_SYSTEM        0x04
#define PBK_FILE_ATTR_VOLUME        0x08
#define PBK_FILE_ATTR_DIR           0x10
#define PBK_FILE_ATTR_ARCHIVE       0x20
#define PBK_FILE_ATTR_LONGNAME  0x0F

#define PBK_FILE_FULL_PATH_LEN_MAX   254
typedef struct __PBK_FILE_FIND_INFO
{
     c_uint8 file_name[PBK_FILE_FULL_PATH_LEN_MAX+2];
     c_uint32 attr;
     c_uint32 size;
}PBK_FILE_FIND_INFO;

typedef struct __PBK_DISK_INFO
{
     c_uint32 disk_count;
     char disk_letter[7]; //最多7个驱动器
     char sys_letter; //系统 不可见区域
}PBK_DISK_INFO;

#endif

/***********************************************
//5: timer
//定时器
************************************************/
#ifdef PBK_PLATFORM_V6000
typedef void (*PBK_TIMER_CALLBACK)(void* param);
#endif


/***********************************************
//6: gui
//图形图像
************************************************/
#ifdef PBK_PLATFORM_V6000

//图层管理
typedef struct __PBK_FONT_INFO
{
    c_int32         ascii_char_h;/* ascii字符的高度 */
    c_int8          ascii_char_w[256];/* ascii字符的宽度 */
    c_int32         ascii_char_w_max;/* ascii字符的宽度最宽多大 */
    c_int32     cn_char_h;/* 汉字字符的高度 */
    c_int32     cn_char_w;/* 汉字字符的宽度 */
    c_uint32        curr_font_type;/* 当前字体风格 */

    c_uint8*     fonts_cache_data;/* 总的fonts字模内存指针 */

    c_uint8*    ascii_fonts_data;     /*ascii  字模数据*/
    c_int32      ascii_fonts_bytes;   /*一个ascii  字模数据占据的大小*/

    c_uint8*    cn_fonts_data;           /* 汉字字模数据*/
    c_int32      cn_fonts_bytes;     /*一个汉字字模数据占据的大小*/

    c_uint16*   fonts_data_hash;   /* 常用数据的hash表 */

    c_uint32    font_file_id;       /* 字库文件句柄 */
}PBK_FONT_INFO;

typedef enum __PBK_FONT_TYPE
{
    PBK_FONT_TYPE_DEFAULT = 1, /* 系统默认字体 */
    PBK_FONT_TYPE_SMALL,  /* 16X16  点阵小字体*/
    PBK_FONT_TYPE_RESVERD1,  /* 预留 */
    PBK_FONT_TYPE_RESVERD2,  /* 预留 */

    PBK_FONT_TYPE_MAX
}PBK_FONT_TYPE;

//按照j2me， 以中心点，垂直镜像，顺时针旋转
typedef enum __PBK_TRANS_TYPE
{
    PBK_TRANS_MIRROR = 2,
    PBK_TRANS_MIRROR_ROT180 = 1,
    PBK_TRANS_MIRROR_ROT270 = 4,
    PBK_TRANS_MIRROR_ROT90 = 7,
    PBK_TRANS_NONE = 0,
    PBK_TRANS_ROT180 = 3,
    PBK_TRANS_ROT270 = 6,
    PBK_TRANS_ROT90 = 5
}PBK_TRANS_TYPE;

typedef struct __PBK_GUI_LAYER
{
    c_uint32 id;
    c_int32 w; //宽
    c_int32 h; //高
    c_uint8* buf; //位图内存区

    c_uint32 cur_color; //当前颜色
    c_uint32 trans_color; //透明色

    //当前裁剪区
    c_int32 x1;
    c_int32 y1;
    c_int32 x2;
    c_int32 y2;
}PBK_GUI_LAYER;
typedef struct __PBK_GUI_RECT
{
    c_int16 x1;
    c_int16 y1;
    c_int16 x2;
    c_int16 y2;
}PBK_GUI_RECT;

#endif

/***********************************************
//7: socket
//网络通讯
************************************************/
#ifdef PBK_PLATFORM_V6000
typedef struct __PBK_SOC_EVENT
{
    c_int32   result;
    c_uint32 event_type;
    c_uint32 l_param;
}PBK_SOC_EVENT;

typedef void (*PBK_SOC_EVENT_CALLBACK)(PBK_SOC_EVENT* soc_event);

typedef struct __PBK_SOC_GET_HOST_EVENT
{
    c_int32 result;
    c_int32 addr_len;
    c_uint8 addr[16];
    c_uint32 l_param;
}PBK_SOC_GET_HOST_EVENT;
typedef void(*PBK_SOC_GET_HOST_CALLBACK)(PBK_SOC_GET_HOST_EVENT* get_host_event);

typedef struct __PBK_GPRS_ACCOUNT
{
    c_int32 present;   //是否有效
    c_uint8 account_name[32];  //名字 unicode
    c_uint8 APN[32];    //APN unicode
    c_int32 auth_type;   /* Authentication Type */
    char user_name[16];  /* User of a Data Account */
    char password[16];   /* Password for a Data Account */
    c_uint8 dns_addr[4]; /* DNS IP Address */

    c_uint8 proxy_ip[4];
    c_uint32 proxy_port;
    c_int32 account_dcs;
    c_uint32 reserved;
}PBK_GPRS_ACCOUNT;

typedef enum __PBK_NET_TYPE
{
    PBK_NET_TYPE_CMWAP = 0, //cmwap方式
    PBK_NET_TYPE_CMNET = 1, //cmnet方式
    PBK_NET_TYPE_UNIWAP = 2, //联通 卡走cmwap
    PBK_NET_TYPE_WIFI = 3, //wifi
    PBK_NET_TYPE_3G_CMWAP = 4, 
    PBK_NET_TYPE_3G_CMNET = 5,
    PBK_NET_TYPE_4G_CMWAP = 6, 
    PBK_NET_TYPE_4G_CMNET = 7, 
    PBK_NET_TYPE_UNINET  = 8, //联通 卡uninet方式
    PBK_NET_TYPE_CTWAP  = 9, //电信 卡ctwap方式
    PBK_NET_TYPE_CTNET    = 10, //电信 卡ctnet方式
    
    PBK_NET_TYPE_MAX
}PBK_NET_TYPE;

//socket上发生的事件类型
typedef enum __PBK_SOC_EVENT_TYPE
{
    PBK_SOC_EVENT_CONNECTING = 1, //开始连接
    PBK_SOC_EVENT_CONNECT,  //连接建立
    PBK_SOC_EVENT_DISCONNECT, //连接断开
    PBK_SOC_EVENT_SEND, //可发送
    PBK_SOC_EVENT_RECV, //可接收
    PBK_SOC_EVENT_ERROR, //错误
    PBK_SOC_EVENT_MAX,
    PBK_SOC_EVENT_PUSH_0
}PBK_SOC_EVENT_TYPE;

//接收数据提前获取的状态
typedef enum __PBK_SOCKET_PEEK_STATE
{
    PBK_SOCKET_PEEK_NO = 0,  //没有提取数据
    PBK_SOCKET_PEEK_START, //第一次提取，需要上层记住数据头部
    PBK_SOCKET_PEEK_CONTINUE, //中间提取
    PBK_SOCKET_PEEK_END, //最后一次提取，结束

    PBK_SOCKET_PEEK_STATE_MAX
}PBK_SOCKET_PEEK_STATE;



//http
typedef enum __PBK_HTTP_REQ_TYPE
{
    PBK_HTTP_REQ_GET = 0, //get方式请求
    PBK_HTTP_REQ_POST,    //post方式请求

    PBK_HTTP_REQ_TYPE_MAX
}PBK_HTTP_REQ_TYPE;

typedef enum __PBK_HTTP_EVENT
{
    PBK_HTTP_START = 1, //连接网络
    PBK_HTTP_REQUEST, //请求服务器      l:剩余多少没发 w:总共要发送多少
    PBK_HTTP_RESP, //接收数据           l:目前接收长度 w:总共要接收的长度
    PBK_HTTP_PEEK, //转移缓冲区数据 l:数据缓冲区 w:数据长度
    PBK_HTTP_END, //接收完毕 l:数据缓冲区 w:数据长度
    PBK_HTTP_ERROR, //错误
    PBK_HTTP_TIMEOUT, //请求超时

    PBK_HTTP_EVENT_MAX
}PBK_HTTP_EVENT;

typedef struct __PBK_HTTP_REQ_INFO
{
    char* host;
    char* url; //请求url
    char* ref_url; //referer参数，字符串最后不要加换行结束符
    char* ua; //User-Agent参数，字符串最后不要加换行结束符
    char* head_param; //其他请求头参数，字符串最后不要加换行结束符
    char* get_data; //get方式传递的数据
    c_uint8* post_data; //post方式发送的数据
    c_uint32 post_data_length;
    c_uint32 req_type; //PBK_HTTP_REQ_TYPE  0:get 1:post 请求方式
}PBK_HTTP_REQ_INFO;

typedef enum __PBK_HTTP_CONTENT_TYPE
{
    PBK_MIME_TEXT_HTML = 1,
    PBK_MIME_TEXT_XHTML,
    PBK_MIME_TEXT_WML,
    PBK_MIME_TEXT_PLAIN,
    PBK_MIME_IMAGE_JPEG,
    PBK_MIME_IMAGE_GIF,
    PBK_MIME_IMAGE_PNG,
    PBK_MIME_EBK2_ZLIB_PAGE,
    PBK_MIME_JAVA_JAD,
    PBK_MIME_JAVA_JAR,
    PBK_MIME_SYMBIAN_SIS,
    PBK_MIME_MMS,

    PBK_HTTP_CONTENT_TYPE_MAX
}PBK_HTTP_CONTENT_TYPE;

typedef struct __PBK_HTTP_RESP_INFO
{
    c_uint32 status;            //返回状态
    c_uint32 content_length;    //body长度
    c_uint32 content_offset;        //body在返回数据中的偏移
    c_uint32 content_type;
    c_uint32 is_chunked; //transfer-encoding: chunked
    char* location; //location:
    //char* file_name; //Content-disposition: attachment;filename=""

    c_uint32 charset; //0:utf-8 1:gb2312
}PBK_HTTP_RESP_INFO;

typedef struct __PBK_HTTP_DATA PBK_HTTP_DATA;
typedef void (*PBK_HTTP_EVENT_CALLBACK)(PBK_HTTP_DATA* http_data, c_uint32 event_type, c_uint32 l_param, c_uint32 w_param);

struct __PBK_HTTP_DATA
{
    char* req_head_buf; //请求头数据缓冲，指向send_buf
    c_uint32 req_head_length;
    c_uint32 req_head_offset;

    char* resp_head_buf; //返回头数据缓冲，指向recv_buf
    c_uint32 resp_head_length;
    c_uint32 resp_head_offset;

    PBK_HTTP_RESP_INFO resp_info; //返回头部分析后的结果

    PBK_HTTP_EVENT_CALLBACK event_callback; //通知上层的回调接口

    char* (*get_url_param)(char* url); //根据url获取特殊参数

    //保存一份联网方式和使用的sim卡，每次联网前都要设置，因为本次联网后设置可能被其他应用改变
    c_int32 net_type; //连接方式
    c_uint32 net_sim_index; //上网sim卡序号，双卡双待机有效
    c_uint32 timeout_timer_id; //用于超时处理的

    void* w_param; //附带的一个参数
    c_uint32 is_net_used; //此通道是否请求过网络

    //socket 数据start
    c_int32 soc_id; //系统socket id
    c_uint32 can_recv; //数据还没收完，缓冲区满了，处理后继续收

    c_uint8* send_buf; //发送缓冲区
    c_uint32 send_buf_size; //发送缓冲区大小

    c_uint8* recv_buf; //接收缓冲区
    c_uint32 recv_buf_size; //接收数据缓冲区大小

    c_uint32 send_data_length; //发送数据长度
    c_uint32 recv_data_length; //接收数据长度

    //c_uint32 once_send_data_length; //调用一次系统发送函数所发送出去的数据长度
    //c_uint32 once_recv_data_length; //调用一次系统接收函数所接收的数据长度

    //缓冲数据预处理
    c_uint32 peek_data_length;
    c_uint32 peek_state;
    //socket 数据end
};
#endif


/***********************************************
//8: device
//设备信息
************************************************/
#ifdef PBK_PLATFORM_V6000
typedef enum __PBK_LCD_TYPE
{
    PBK_LCD_128_128 = 1,
    PBK_LCD_128_160 = 2,
    PBK_LCD_176_220 = 3,
    PBK_LCD_240_320 = 4,
    PBK_LCD_240_400 = 5,
    PBK_LCD_240_432 = 6,
    PBK_LCD_320_240 = 7,
    PBK_LCD_400_240 = 8,
    PBK_LCD_432_240 = 9,
    PBK_LCD_320_480 = 10,
    PBK_LCD_480_320 = 11,
    PBK_LCD_480_800 = 12,
    PBK_LCD_360_480 = 15,
	PBK_LCD_360_640 = 21,
    PBK_LCD_TYPE_MAX
}PBK_LCD_TYPE;
typedef enum __PBK_LCD_DIRECTION
{
    PBK_LCD_ANGLE_0   ,
    PBK_LCD_ANGLE_90  ,
    PBK_LCD_ANGLE_180 ,
    PBK_LCD_ANGLE_270
}PBK_LCD_DIRECTION;

typedef enum __PBK_SIM_TYPE
{
    PBK_SIM_MOBILE = 0, //移动卡
    PBK_SIM_UNICOM = 1, //联通卡
    PBK_SIM_INVALID = 2, //无效卡
    PBK_SIM_TELECOM = 3, //电信卡

    PBK_SIM_MAX
}PBK_SIM_TYPE;

typedef enum __PBK_KEYBOARD_TYPE
{
    PBK_KEYBOARD_COMMON = 0, //触屏带键盘
    PBK_KEYBOARD_ONLY_TOUCH = 1, //只有触屏
    PBK_KEYBOARD_ONLY_KEYBOARD = 2, //只有键盘
    PBK_KEYBOARD_QWERTY_KEYBOARD, //全键盘

    PBK_KEYBOARD_TYPE_MAX
}PBK_KEYBOARD_TYPE;

typedef enum __PBK_LANGUAGE_TYPE
{
    PBK_LANGUAGE_CN = 0, //中文
    PBK_LANGUAGE_EN, //英文

    PBK_LANGUAGE_TYPE_MAX
}PBK_LANGUAGE_TYPE;
typedef enum __PBK_DEVICE_TYPE
{
    PBK_DEVICE_TOUCH_SCREEN,
    PBK_DEVICE_KEYBOARD,
    PBK_DEVICE_DUAL_SIM,
    PBK_DEVICE_FM,
    PBK_DEVICE_TV,
    PBK_DEVICE_CMMP,
    PBK_DEVICE_GPS,
    PBK_DEVICE_BLUETOOTH,
    PBK_DEVICE_WIFI,
    PBK_DEVICE_DIRECT_SENSOR,
    PBK_DEVICE_MOTION,
    PBK_DEVICE_MEM_LARGER_MODE, //大内存
    PBK_DEVICE_MEM_SCREEN, //屏幕内存
    PBK_DEVICE_VECTOR_FONT, //矢量字体
    PBK_DEVICE_TRI_SIM,            // sim卡3
    PBK_DEVICE_QUAD_SIM,        // sim卡4

    PBK_DEVICE_MAX
}PBK_DEVICE_TYPE;

typedef enum __PBK_SYS_FUNC_ID
{
    PBK_SYS_FUNC_ID_TEST = 0, 
    PBK_SYS_FUNC_ID_ZHNAGYUE_DIR = 1, 
    PBK_SYS_FUNC_ID_EBOOK_DIR = 2, 
    PBK_SYS_FUNC_ID_SBAPI = 3, //状态栏相关api
    PBK_SYS_FUNC_ID_SIMAPI = 4, //sim卡相关api
    PBK_SYS_FUNC_ID_6100API = 5, //6100版本新增

    PBK_SYS_FUNC_ID_GUI = 8, //gui扩展
    PBK_SYS_FUNC_ID_6105API = 9, //6.5版本书城以后新增API
    
    PBK_SYS_FUNC_ID_EMBED_BOOK = 10,
//#ifdef	PBK_OPEN_EMBED_URL
    PBK_SYS_FUNC_ID_EMBEDURL = 11, //更改主页
//#endif

    PBK_SYS_FUNC_ID_MAX = 16,
    //
    PBK_SYS_FUNC_ID_DEWAV_FEE_FUN = 1000,
    PBK_SYS_FUNC_ID_DEWAV_EXTRA_FUN = 1001,
    PBK_SYS_FUNC_ID_IS_SUPPORT_SIM_SELECT    = 10000,    
    PBK_SYS_FUNC_ID_UPDATE_ZPP = 10001,            // 要升级的 ZPP 名称
}PBK_SYS_FUNC_ID;

typedef enum __PBK_SYS_DEVICE_ID
{
    PBK_SYS_DEVICE_ID_TEST = 0,

    PBK_SYS_DEVICE_ID_MAX
}PBK_SYS_DEVICE_ID;

typedef enum __PBK_SYS_THIRD_APP_ID
{
    PBK_SYS_THIRD_APP_QQ = 0,

    PBK_SYS_THIRD_APP_ID_MAX
}PBK_SYS_THIRD_APP_ID;
#endif

/***********************************************
//9: system
//系统相关功能调用
************************************************/
#ifdef PBK_PLATFORM_V6000
typedef struct __PBK_TIME
{
    c_uint16 year;
    c_uint8 month;
    c_uint8 day;
    c_uint8 hour;
    c_uint8 min;
    c_uint8 sec;
    c_uint8 day_index; /* 0=Sunday */
}PBK_TIME;

//input
typedef enum __PBK_INPUT_TYPE
{
    PBK_INPUT_PINYIN = 1, //拼音
    PBK_INPUT_NUM = 2, //数字
    PBK_INPUT_ABC = 3, //字母

    PBK_INPUT_TYPE_MAX
}PBK_INPUT_TYPE;

typedef enum __PBK_POP_TYPE
{
    PBK_POP_WARNING = 1, //警告
    PBK_POP_SUCCESS = 2, //成功
    PBK_POP_FAILED = 3, //失败

    PBK_POP_TYPE_MAX
}PBK_POP_TYPE;

typedef void (*PBK_SYS_CALLBACK) (c_int32 result, void* data);

#endif


/***********************************************
//10: media
//多媒体
************************************************/
#ifdef PBK_PLATFORM_V6000
enum
{
    PBK_AUDIO_AMR,                  // AMR
    PBK_AUDIO_WAV,                  // WAV
    PBK_AUDIO_MIDI,                 // MIDI
    PBK_AUDIO_MP3,                  // 3GP mp3?
    PBK_AUDIO_WMA,
    PBK_AUDIO_MAX
};

enum
{
    PBK_AUDIO_SPEAKER,
    PBK_AUDIO_MICROPHONE,
    PBK_AUDIO_SPEAKER2,
    PBK_AUDIO_LOUDSPEAKER,
    PBK_AUDIO_SPEAKER_BOTH,
    PBK_AUDIO_BT_HEADSET,
    PBK_AUDIO_DEVICE_MAX
};
enum
{
    PBK_TONE_RING,
    PBK_TONE_POWERON,
    PBK_TONE_POWER_OFF,
    PBK_TONE_MESSAGE,
    PBK_TONE_KEYPAD,
    PBK_TONE_ALARM,
    PBK_TONE_CARD2_RING,
    PBK_TONE_CARD2_MESSAGE,
    PBK_TONE_MAX
};
#endif


/***********************************************
//11: zpp
//加载运行
************************************************/
#ifdef PBK_PLATFORM_V6000
typedef enum __PBK_WM_ID
{
//app
    PBK_WM_START = 1,
    PBK_WM_PAUSE,
    PBK_WM_RESUME,
    PBK_WM_EXIT,

//key
    PBK_WM_KEY_DOWN,
    PBK_WM_KEY_UP,
    PBK_WM_KEY_REPEAT,
    PBK_WM_KEY_LONG_PRESS,
    PBK_WM_KEY_HALF_PRESS_DOWN,
    PBK_WM_KEY_HALF_PRESS_UP,
//mouse
    PBK_WM_MOUSE_DOWN,
    PBK_WM_MOUSE_UP,
    PBK_WM_MOUSE_MOVE,

//input
    PBK_WM_CHAR, //输入字符

    PBK_WM_DRAW,

    PBK_WM_WIN, //直接发给控件
//timer
    PBK_WM_TIMER,
//t card
    PBK_WM_TCARD_INSERT,
    PBK_WM_TCARD_REJECT,
//usb cable

//sms
    PBK_WM_SMS_DELIVER,
    PBK_WM_SMS_SEND_RESULT,
    PBK_WM_SOCKET,

//motion
    PBK_WM_MOTION,
    PBK_WM_LONG_PRESS_KEY, //chenjinlei 20100610
//fee
    PBK_WM_FEE_RESULT, 
//net type
    PBK_WM_NET_STATUS_UPDATE,     // 激活 GPRS WIFI 等
//lcd switch
    PBK_WM_LCD_SWITCH,        // LCD 旋转，方向定义参见 PBK_LCD_DIRECTION
    PBK_WM_MOUSE_LONG_PRESS, 
    PBK_WM_MOUSE_DOUBLE_PRESS, 

	PBK_WM_FEE_RESULT_SYNC, //liuwp 异步通知
	PBK_WM_FEE_REQ, //计费请求
	PBK_WM_CONFIRM_REQ, //
	
//fm
//audio
//tv
//cmmb
//bt
    //liuwp 20101105
    PBK_WM_SYS_MIN_ID = 100, //系统消息从100开始
    PBK_WM_SYS_RUN, //运行
    PBK_WM_SYS_RUN_CHANGE, //切换到另外一个已经启动的app运行
    PBK_WM_SYS_DESTORY, //销毁
    PBK_WM_SYS_DESTORY_ALL, //销毁所有app


    PBK_WM_MAX
}PBK_WM_ID;

//key define
typedef enum __PBK_KEY_DEF
{
    C_KEY_0 = 0,
    C_KEY_1,
    C_KEY_2,
    C_KEY_3,
    C_KEY_4,
    C_KEY_5,
    C_KEY_6,
    C_KEY_7,
    C_KEY_8,
    C_KEY_9,
    C_KEY_LEFT_SOFTKEY,
    C_KEY_RIGHT_SOFTKEY,
    C_KEY_CENTER_SOFTKEY,
    C_KEY_UP_ARROW,
    C_KEY_DOWN_ARROW,
    C_KEY_LEFT_ARROW,
    C_KEY_RIGHT_ARROW,
    C_KEY_SEND,
    C_KEY_END,
    C_KEY_CLEAR,    //clr
    C_KEY_STAR,     //*
    C_KEY_POUND,    //#
    C_KEY_VOL_UP,
    C_KEY_VOL_DOWN,
    C_KEY_CAMERA,
    C_KEY_ENTER,
    C_KEY_OK = C_KEY_ENTER,
    C_KEY_EXTRA_1,
    C_KEY_EXTRA_2,
    C_KEY_PLAY_STOP,
    C_KEY_FWD,
    C_KEY_BACK,
    C_KEY_POWER,                    // power 和 end 有的项目上是同一个键
    C_KEY_EXTRA_A,
    C_KEY_EXTRA_B,

    C_KEY_MAX
}PBK_KEY_DEF;

typedef struct __PBK_APP_INFO
{
    //c_uint32 name_id; //app编号
    c_uint32 version;  //版本
    c_uint32 build_time; //生成时间
    c_uint32 file_size;  //文件大小
    c_uint8 name[32];           // 名称 unicode
    c_uint8 description[256];   // 简介 unicode
    //c_uint8 icon_data[2 * 1024];
    c_uint32 icon_offset;
    c_uint32 icon_size;
}PBK_APP_INFO;

typedef c_uint32 (*PBK_APP_MSG_PROCESS_FUNC)(c_uint32 msg_id, c_uint32 from_app_id, c_uint32 l_param, c_uint32 w_param); //from_app_id为发送此消息的app_id

//image type
typedef enum __PBK_RES_TYPE
{
    PBK_RES_TYPE_STR,           // string, text, html, zlib compress
    PBK_RES_TYPE_UNICODE,       // string, text, html,
    PBK_RES_TYPE_TXT,           // string, text, html, zlib compress
    PBK_RES_TYPE_BMP,           // BMP
    PBK_RES_TYPE_LZ,            // 16BIT LZCSS
    PBK_RES_TYPE_GIF,           // GIF
    PBK_RES_TYPE_PNG,           // PNG
    PBK_RES_TYPE_JPG,           // JPG
    PBK_RES_TYPE_BIN,           // 自定义,其它类型
    PBK_RES_TYPE_BITMAP,        // 16BIT LZCSS 解压之后的位图
    PBK_RES_TYPE_MAX
}PBK_RES_TYPE;

#define PBK_IMG_TYPE_BMP    PBK_RES_TYPE_BMP
#define PBK_IMG_TYPE_LZ     PBK_RES_TYPE_LZ
#define PBK_IMG_TYPE_GIF    PBK_RES_TYPE_GIF
#define PBK_IMG_TYPE_JPEG   PBK_RES_TYPE_JPG
#define PBK_IMG_TYPE_PNG    PBK_RES_TYPE_PNG
#define PBK_IMG_TYPE_BITMAP PBK_RES_TYPE_BITMAP
#define PBK_IMG_TYPE_UNKOWN 0xffffffff

typedef struct __PBK_IMAGE
{
    c_int32 w;
    c_int32 h;
    c_uint8* data;
    c_uint32 data_size;
    c_uint32 type;              //PBK_IMAGE_TYPE, 兼容 bitmap 结构
}PBK_IMAGE;

/*
typedef struct __PBK_BITMAP
{
    c_int32 w;
    c_int32 h;
    c_uint8* data;
    c_uint32 data_size;
}PBK_BITMAP;
*/
#endif

/***********************************************
//12: 
************************************************/
#ifdef PBK_PLATFORM_V6100
#define PBK_FEE_ENTER_TAG (0x5a504159) //入口数据标识ZPAY

typedef struct __PBK_FEE_CALLBACK_DATA
{
    char fee_key[32];
    void* callback_data;
}PBK_FEE_CALLBACK_DATA;

typedef struct __PBK_FEE_ENTER_DATA
{
    c_uint32 tag;
    char* app_name;
    c_uint32 app_name_id;
    c_uint32 app_run_id;
    c_uint32 res_id; 
    c_uint32 fee_num; 
    char* app_info;
    char* tip_info; 
    PBK_SYS_CALLBACK result_callback; 
    void* callback_data;

    c_uint8* body_buf;
    c_uint32 body_length;
    c_uint32 reserverd[4];
}PBK_FEE_ENTER_DATA;

typedef struct __PBK_SMS_CONFIRM_ENTER_DATA
{
    char* addr;
    c_uint8* content;
    void* confirm_item;
    c_uint32 reserverd[4];
}PBK_SMS_CONFIRM_ENTER_DATA;
#endif

typedef enum __PBK_APP_UPDATE_EVENT_TYPE
{
    PBK_APP_UPDATE_EVENT_START = 0, //开始更新
    PBK_APP_UPDATE_EVENT_END, //更新完成
    PBK_APP_UPDATE_EVENT_PROCESS, //l_param:文件总字节数   w_param:当前已经下载的字节数
    PBK_APP_UPDATE_EVENT_ERROR, //更新失败，l_param:错误码

    PBK_APP_UPDATE_EVENT_TYPE_MAX
}PBK_APP_UPDATE_EVENT_TYPE;

//type 0: fail  1: success  2: process, file_size & curr_size available
typedef void (*PBK_APP_UPDATE_CALLBACK)(c_uint32 evnet_type, c_uint32 l_param, c_uint32 w_param);

typedef enum __PBK_APP_UPDATE_TIP_TYPE
{
    PBK_APP_UPDATE_TIP_NONE = 0, //无提示，应用自己根据回调处理
    PBK_APP_UPDATE_TIP_DOWNLOAD, //下载提示
    PBK_APP_UPDATE_TIP_UPDATE, //更新提示
    PBK_APP_UPDATE_TIP_APP, //平台内部用

    PBK_APP_UPDATE_TIP_MAX
}PBK_APP_UPDATE_TIP_TYPE;



//状态栏api
typedef enum __PBK_SBAPI_FUNC_ID
{
    PBK_SBAPI_FUNC_ID_BAR_HEIGHT = 0, //获取高度
    PBK_SBAPI_FUNC_ID_DRAW = 1, //绘制手机状态栏

    PBK_SBAPI_FUNC_ID_MAX = 8
}PBK_SBAPI_FUNC_ID;
    
//sim卡相关api
typedef enum __PBK_SIMAPI_FUNC_ID
{
    PBK_SIMAPI_FUNC_ID_SIM_NUM = 0,        //获取sim 卡数量 
    PBK_SIMAPI_FUNC_ID_SIM3_VALID = 1, //sim卡3是否有效
    PBK_SIMAPI_FUNC_ID_SIM4_VALID = 2, //sim卡4是否有效
    PBK_SIMAPI_FUNC_ID_SIM3_TYPE = 3, //sim卡3类型
    PBK_SIMAPI_FUNC_ID_SIM4_TYPE = 4, //sim卡4类型

    PBK_SIMAPI_FUNC_ID_MAX = 8
}PBK_SIMAPI_FUNC_ID;

//6100新增
typedef enum __PBK_6100API_FUNC_ID
{
	PBK_6100API_FUNC_ID_GET_UID = 0, 
	PBK_6100API_FUNC_ID_GET_PHONE_NUM = 1, 
	PBK_6100API_FUNC_ID_SET_PHONE_NUM = 2, 
	PBK_6100API_FUNC_ID_CHECK_DATA_CLEAR = 3, 
	PBK_6100API_FUNC_ID_GET_CHECK_DATA = 4, 
	PBK_6100API_FUNC_ID_GET_URL_PARAM = 5, 
	PBK_6100API_FUNC_ID_UPLOAD_INFO_ADD = 6, 
	PBK_6100API_FUNC_ID_UPLOAD_INFO_UPLOAD = 7, 
	PBK_6100API_FUNC_ID_GET_PARENT_APP_ID = 8, 
	PBK_6100API_FUNC_ID_FEE_ABORT_AS_SERVER = 9, 
	PBK_6100API_FUNC_ID_GET_CUSTOM_STR = 10, 
	PBK_6100API_FUNC_ID_FLIP2_SIMPLE_LEFT = 11, //从右往左
	PBK_6100API_FUNC_ID_FLIP2_SIMPLE_RIGHT = 12, //从左往右
	PBK_6100API_FUNC_ID_FEE_SET_FAIL_TYPE = 13, 
	PBK_6100API_FUNC_ID_FEE_GET_FAIL_TYPE = 14, 

	PBK_6100API_FUNC_ID_MAX = 16
}PBK_6100API_FUNC_ID;

//#ifdef PBK_OPEN_EMBED_URL
typedef enum __PBK_EMBED_URL_FUNC_ID
{
	PBK_EMBED_URL_FUNC_GET_URL = 0,	 // 获取URL连接地址
	PBK_EMBED_URL_FUNC_GET_DATA = 1, // 获取URL页面数据
	PBK_EMBED_URL_FUNC_GET_DATALEN = 2,
		
	PBK_EMBED_URL_FUNC_ID_MAX = 16
}PBK_EMBED_URL_FUNC_ID;
//#endif

#endif
#endif
