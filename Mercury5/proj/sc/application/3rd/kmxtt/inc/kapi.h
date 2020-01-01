
/*

Public platform independent Komoxo API.

Version 1.4

Copyright (C) 2009-2011 Beijing Komoxo Inc.
All rights reserved.

*/

#ifndef KAPI_H
#define KAPI_H

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************

Basic data types.

****************************************************************************/

#ifndef TRUE
    #define TRUE        1
#endif

#ifndef FALSE
    #define FALSE       0
#endif

#ifndef NULL
    #define NULL        0
#endif

typedef int KBOOL;
typedef int KSTATUS;
typedef unsigned int KPARAM;

typedef unsigned short KWCHAR;

typedef unsigned int KFONT;
typedef unsigned int KCOLOR;

#if defined(_MSC_VER)
    /* Microsoft Visual C/C++ */
    typedef __int64 KINT64;
    typedef unsigned __int64 KUINT64;
#elif defined(__BORLANDC__)
    /* Borland C++ */
    typedef __int64 KINT64;
    typedef unsigned __int64 KUINT64;
#elif defined(__MWERKS__)
    /* Metrowerks CodeWarrior */
    typedef long long int KINT64;
    typedef unsigned long long int KUINT64;
#elif defined(__GNUC__)
    /* GCC */
    typedef long long int KINT64;
    typedef unsigned long long int KUINT64;
#else
    /* For other compilers */
    typedef long long KINT64;
    typedef unsigned long long KUINT64;
#endif

typedef struct
{
    int     left;
    int     top;
    int     right;
    int     bottom;
} KRECT;

typedef struct 
{
    unsigned short year;    /* [1970..2099]                      */
    unsigned char month;    /* months since January,     [0..11] */
    unsigned char day;      /* day of the month,         [1..31] */
    unsigned char hour;     /* hours since midnight,     [0..23] */
    unsigned char minute;   /* minutes after the hour,   [0..59] */
    unsigned char second;   /* seconds after the minute, [0..59] */
    unsigned char pad;
} KTIME;

#define K_COLOR_R(c)      ((unsigned char)((c) >> 16))
#define K_COLOR_G(c)      ((unsigned char)((c) >> 8))
#define K_COLOR_B(c)      ((unsigned char)(c))

#define K_MAKE_COLOR(r, g, b)   \
    (KCOLOR) ( (((unsigned char)(r)) << 16) | (((unsigned char)(g)) << 8) | ((unsigned char)(b)) )

#define K_LANG_DEFAULT                  0
#define K_LANG_CHINESE_SIMPLIFIED       1
#define K_LANG_CHINESE_TRADITIONAL      2
#define K_LANG_ENGLISH                  3
#define K_MAX_LANG                      4

#define K_FONT_SMALL                    0
#define K_FONT_MEDIUM                   1
#define K_FONT_LARGE                    2
#define K_MAX_FONT                      3

#define K_STATUS_OK                         0
#define K_STATUS_ERROR                      1
#define K_STATUS_NOT_INITIALIZED            2
#define K_STATUS_INVALID_PARAMETER          3
#define K_STATUS_OUT_OF_MEMORY              4
#define K_STATUS_NOT_SUPPORTED              5
#define K_STATUS_EXIT                       6
#define K_STATUS_NOT_HANDLED                7
#define K_STATUS_TIME_OUT                   8
#define K_STATUS_BUFFER_FULL                9
#define K_STATUS_FILE_NOT_FOUND             10
#define K_STATUS_MISSING_IMPORT             11
#define K_STATUS_CONNECTION_END             12
#define K_STATUS_CANCEL                     13
#define K_STATUS_NOT_LOADED                 14
#define K_STATUS_ALREADY_LOADED             15
#define K_STATUS_BAD_FILE_NAME              16
#define K_STATUS_BAD_MODULE                 17
#define K_STATUS_ERROR_FILE_OPEN            18
#define K_STATUS_ERROR_FILE_CREATE          19
#define K_STATUS_ERROR_FILE_READ            20
#define K_STATUS_ERROR_FILE_WRITE           21
#define K_STATUS_ERROR_FILE_SEEK            22
#define K_STATUS_OPEN_FILES_EXCEED_LIMIT    23
#define K_STATUS_CONNECTIONS_EXCEED_LIMIT   24
#define K_STATUS_CHANNEL_NOT_AVAILABLE      25
#define K_STATUS_SENDING_REQUEST            26
#define K_STATUS_REQUEST_SENT               27
#define K_STATUS_ALREADY_OPENED             28
#define K_STATUS_FIRST_SENDING_REQUEST      29
#define K_STATUS_FIRST_REQUEST_SENT         30

/****************************************************************************

Platform basic interface.

****************************************************************************/

#define K_CAPS_TOUCH             0x00000001
#define K_CAPS_REDUCED_KEYPAD    0x00000010
#define K_CAPS_NORMAL_KEYPAD     0x00000020
#define K_CAPS_QWERTY_KEYPAD     0x00000040
#define K_CAPS_WIFI_SUPPORT      0x01000000

#define K_CAPS_KEYPAD            (K_CAPS_REDUCED_KEYPAD | K_CAPS_NORMAL_KEYPAD | K_CAPS_QWERTY_KEYPAD)

#define K_CAPS_API_DRAW_IMAGE_FILE      0x00000001
#define K_CAPS_API_LOAD_CAMERA          0x00000002

#define K_TIMER_0        0
#define K_TIMER_1        1
#define K_TIMER_2        2
#define K_TIMER_3        3
#define K_NUM_TIMERS     4

typedef struct
{
    KRECT app_rect;
    int screen_width;
    int screen_height;
    int device_caps;
    int api_caps;
    unsigned int language;
    void* reserved;
} K_BASIC_SYSTEM_INFO;

typedef void (*k_func_ptr) (void);

k_func_ptr k_get_proc_addr(const char* name);

void k_print(const char* message);
void k_break(void);

void* k_malloc(unsigned int size);
void k_free(void* ptr);

void k_query_basic_system_info(K_BASIC_SYSTEM_INFO* info);

unsigned int k_get_tick_count(void);
void k_get_time(KTIME* local_time, KTIME* utc_time);

void k_start_timer(unsigned int id, unsigned int delay);    /* milliseconds */
void k_stop_timer(unsigned int id);

void k_acquire_lock(void);
void k_release_lock(void);

void k_flush_cpu_cache(void* addr, unsigned int len);

/****************************************************************************

Platform file system interface.

****************************************************************************/

typedef int K_FILE_HANDLE;

#define K_FILE_OPEN_CREATE      0
#define K_FILE_OPEN_READ        1
#define K_FILE_OPEN_READ_WRITE  2

#define K_FILE_SEEK_CUR         0
#define K_FILE_SEEK_END         1
#define K_FILE_SEEK_SET         2

#define K_MAX_OPEN_FILES        16

#define K_MAX_PATH              128

#define K_FILE_ATTR_DIR         0x10

typedef struct
{
    char sys_drive_letter;
    char aux_drive_letter;
} K_FILE_SYSTEM_INFO;

typedef struct
{
    KWCHAR          file_name[K_MAX_PATH + 1];
    unsigned char   attrs;
    unsigned int    file_size;
} K_FILE_INFO;

void k_query_file_system_info(K_FILE_SYSTEM_INFO* info);

KSTATUS k_get_disk_free_space(const KWCHAR* root_path, unsigned int* free_space);

KSTATUS k_create_dir(const KWCHAR* dir);

KSTATUS k_remove_dir(const KWCHAR* dir);

KSTATUS k_file_delete(const KWCHAR* file_name);

KSTATUS k_file_rename(
    const KWCHAR* old_name,
    const KWCHAR* new_name);

KSTATUS k_file_open(
    const KWCHAR* file_name,
    int mode,
    K_FILE_HANDLE* handle);

void k_file_close(K_FILE_HANDLE handle);

KSTATUS k_file_seek(
    K_FILE_HANDLE handle,
    int offset,
    int origin);

KSTATUS k_file_tell(
    K_FILE_HANDLE handle,
    unsigned int* position);

KSTATUS k_file_read(
    K_FILE_HANDLE handle,
    void* buffer,
    unsigned int size,
    unsigned int* read_size);

KSTATUS k_file_write(
    K_FILE_HANDLE handle,
    const void* buffer,
    unsigned int size,
    unsigned int* written_size);

KSTATUS k_file_flush(K_FILE_HANDLE handle);

KSTATUS k_file_truncate(K_FILE_HANDLE handle, unsigned int pos);

KSTATUS k_find_first(
    const KWCHAR*  dir,  
    K_FILE_INFO*   file_info,
    K_FILE_HANDLE* handle);

KSTATUS k_find_next(K_FILE_HANDLE handle, K_FILE_INFO* file_info);

void k_find_close(K_FILE_HANDLE handle);

/****************************************************************************

Platform GUI interface.

****************************************************************************/

void k_gui_begin_paint(void);
void k_gui_end_paint(const KRECT* rect);

void k_gui_set_clip(const KRECT* clip_rect);

void k_gui_fill_rect(
    const KRECT* rect,
    KCOLOR rect_color);

void k_gui_draw_pixel(
    int x,
    int y,
    KCOLOR pixel_color);

void k_gui_draw_line(
    int x1,
    int y1,
    int x2,
    int y2,
    KCOLOR line_color);

void k_gui_get_text_extent(
    const KWCHAR* text,
    int text_length,
    KFONT text_font,
    int* text_width,
    int* text_height);

void k_gui_draw_text(
    int x,
    int y,
    const KWCHAR* text,
    int text_length,
    KFONT text_font,
    KCOLOR text_color);

void k_gui_draw_image(
    const KRECT* rect,
    const void* image_data,
    unsigned int image_data_length);

void k_gui_draw_image_file(
    const KRECT*    rect,
    const KWCHAR*   image_file);

void k_gui_get_image_file_dimension(
    const KWCHAR*   image_file,
    int*            width,
    int*            height);

/****************************************************************************

Platform text input interface.

****************************************************************************/

#define K_IME_DEFAULT       0
#define K_IME_NUMBER        1
#define K_IME_PASSWORD      2
#define K_IME_EMAIL         3

typedef struct
{
    unsigned int id;
    KWCHAR* text_buffer;
    unsigned int text_limit;
    const KWCHAR* title;
    unsigned int input_method;
} K_TEXT_INPUT_REQUEST;

typedef struct
{
    unsigned int id;
    KSTATUS status;
    KWCHAR* text;
} K_TEXT_INPUT_RESPONSE;

void k_text_input(K_TEXT_INPUT_REQUEST* request);

/****************************************************************************

Platform browse image interface.

****************************************************************************/

typedef struct
{
    KWCHAR* path_buffer;
    unsigned int max_path_length;
} K_BROWSE_IMAGE_REQUEST;

typedef struct
{
    KSTATUS status;
    KWCHAR* path;
} K_BROWSE_IMAGE_RESPONSE;

void k_browse_image(K_BROWSE_IMAGE_REQUEST* request);

/****************************************************************************

Platform load camera interface.

****************************************************************************/

typedef struct
{
    unsigned int max_path_length;
} K_LOAD_CAMERA_REQUEST;

typedef struct
{
    KSTATUS status;
    KWCHAR* path;
} K_LOAD_CAMERA_RESPONSE;

void k_load_camera(K_LOAD_CAMERA_REQUEST* request);

/*****************************************************************************
 *
 * Set WAP browser profile.
 *
 *****************************************************************************/

void k_set_wap_profile(void);

/*****************************************************************************
 *
 * Sending sms & getting sim card information interface.
 *
 *****************************************************************************/

enum
{
    K_SIM_START,

    K_SIM_1 = K_SIM_START,
    K_SIM_2,
    K_SIM_3,
    K_SIM_4,

    K_SIM_MAX
};

enum
{
    K_CARRIER_UNKNOWN,

    K_CARRIER_CHINA_MOBILE,
    K_CARRIER_CHINA_UNICOM,
    K_CARRIER_CHINA_TELECOM
};

typedef struct
{
    unsigned char   sim;
    unsigned char   carrier;

    unsigned short  reserved;
} K_SIM_INFO;

void k_query_sim_info(K_SIM_INFO* info, int sim_max, int *sim_count);
void k_query_sim_name(int sim, KWCHAR* sim_name, int max_name_size);
KSTATUS k_send_sms(
    int             sim,
    const char*     number,
    const KWCHAR*   text, 
    int             text_length);

/****************************************************************************

Platform network service interface.

****************************************************************************/

#define K_HTTP_METHOD_GET       0
#define K_HTTP_METHOD_POST      1

#define K_HTTP_FLAG_STATUS      0x01
#define K_HTTP_FLAG_HEADER      0x02
#define K_HTTP_FLAG_CONTENT     0x04

#define K_HTTP_MAX_CONNECTIONS  8

typedef struct
{
    unsigned int id;
    int method;
    const char* url;
    const char* header;
    const char* post_data;
} K_HTTP_REQUEST;

typedef struct
{
    unsigned int id;
    KSTATUS status;
    int flags;
    int http_status;
    const char* header;
    unsigned int header_length;
    const char* content;
    unsigned int content_length;
} K_HTTP_RESPONSE;

KSTATUS k_net_open_channel(void);
void k_net_close_channel(void);

KSTATUS k_net_send_http_request(K_HTTP_REQUEST* request);
void k_net_cancel_http_request(unsigned int id);

/****************************************************************************

Event code constants.

****************************************************************************/

#define K_EVENT_SUSPEND             10
#define K_EVENT_RESUME              11
#define K_EVENT_PAINT               12
#define K_EVENT_TIMER               13
#define K_EVENT_TEXT_INPUT          14
#define K_EVENT_BROWSE_IMAGE        15
#define K_EVENT_LOAD_CAMERA         16

#define K_EVENT_KEY_DOWN            20
#define K_EVENT_KEY_UP              21

#define K_EVENT_PEN_DOWN            30
#define K_EVENT_PEN_MOVE            31
#define K_EVENT_PEN_UP              32

#define K_EVENT_CHANNEL_RESPONSE    40
#define K_EVENT_HTTP_RESPONSE       41

#define K_EVENT_SMS_RESPONSE        50

#define K_EVENT_API_CALL            81
#define K_EVENT_SLEEP               82
#define K_EVENT_GET_APP_NAME        83

#define K_EVENT_SWITCH_APP_MODE     91

/****************************************************************************

Key code constants.

****************************************************************************/

#define K_KEY_LSK           0x01
#define K_KEY_CSK           0x02
#define K_KEY_RSK           0x03

#define K_KEY_LEFT          0x04
#define K_KEY_RIGHT         0x05
#define K_KEY_UP            0x06
#define K_KEY_DOWN          0x07

#define K_KEY_POWER         0x08

#define K_KEY_ENTER         0x0A

#define K_KEY_CALL_START    0x0E
#define K_KEY_CALL_END      0x0F

#define K_KEY_HOME          0x10
#define K_KEY_END           0x11
#define K_KEY_PAGE_UP       0x12
#define K_KEY_PAGE_DOWN     0x13

#define K_KEY_SMARTKEY      0x14

#define K_KEY_STAR          0x23
#define K_KEY_POUND         0x2A

#define K_KEY_0             0x30
#define K_KEY_1             0x31
#define K_KEY_2             0x32
#define K_KEY_3             0x33
#define K_KEY_4             0x34
#define K_KEY_5             0x35
#define K_KEY_6             0x36
#define K_KEY_7             0x37
#define K_KEY_8             0x38
#define K_KEY_9             0x39

#define K_KEY_BACK          0x40

/****************************************************************************

Application interface.

****************************************************************************/

KSTATUS k_sys_load(const KWCHAR* file_name, const char* args);
void k_sys_unload(void);

KSTATUS k_sys_run(const KWCHAR* app_name, const char* args);
int k_sys_get_exit_code(void);

KSTATUS k_sys_handle_event(int event, KPARAM param1, KPARAM param2);

#define K_EXIT_CODE_SLEEP   100

/****************************************************************************

Download interface.

****************************************************************************/

#define K_DOWNLOAD_END_SUCCESS          0
#define K_DOWNLOAD_PENDING              1
#define K_DOWNLOAD_OUT_OF_MEMORY        2
#define K_DOWNLOAD_FILE_ERROR           3
#define K_DOWNLOAD_CONNECTION_ERROR     4
#define K_DOWNLOAD_RESPONSE_ERROR       5
#define K_DOWNLOAD_TIMEOUT              6
#define K_DOWNLOAD_NOT_AVAIL            7
#define K_DOWNLOAD_RESUME_MISMATCH      8

KSTATUS k_sys_download_start(void);
void k_sys_download_cleanup(void);

KSTATUS k_sys_download_handle_event(int event, KPARAM param1, KPARAM param2);
const KWCHAR* k_sys_download_get_message(void);

/****************************************************************************

Net config interface.

****************************************************************************/

#define K_MAX_GPRS_APN_LEN      22
#define K_MAX_NET_CONFIG_COUNT  4
typedef struct
{
    unsigned char   proxy_ip[4];
    unsigned short  proxy_port;
    unsigned char   use_proxy;
    unsigned char   reserved;
    unsigned char   username[30];
    unsigned char   password[30];
    KWCHAR          apn[K_MAX_GPRS_APN_LEN]; /* L'0' terminiated */
} K_NET_CONFIG_ITEM;

KSTATUS k_net_config_set_active(int sim, int index, int use_proxy);
KSTATUS k_net_config_get_active(int* sim, int* index, int* use_proxy);
K_NET_CONFIG_ITEM* k_net_config_get_item(int index);
int k_net_config_get_num_items(void);
const KWCHAR* k_net_config_get_apn(int index);

/****************************************************************************

TT status access interface.

****************************************************************************/

typedef struct tagK_TT_USTR
{
    KWCHAR *      val;     /* pointer to the item data, with a terminated '\0' */
    unsigned int  len;     /* length of the item data, in KWCHAR */
} K_TT_USTR;

typedef struct tagK_TT_STR
{
    char          *val;    /* pointer to the item data, with a terminated '\0'  */
    unsigned int  len;     /* length of the item data, in char */
} K_TT_STR;

typedef unsigned int KTICK;

#define K_STATUS_FIELD_NOT_FOUND        8001
#define K_STATUS_DATATYPE_NOT_MATCHED   8002
#define K_STATUS_INVALID_ALIGNMENT      8003
#define K_STATUS_FILE_CORRUPT           8004
#define K_STATUS_VERSION_NOT_MATCHED    8005
#define K_STATUS_ENDIAN_NOT_MATCHED     8006

/* {{{serialized object */
typedef struct tagK_TT_STATUS
{
    KUINT64             id;                     /* ID of the status */
    unsigned int        comments;               /* Number of the comments on this status, -1 means not available */
    unsigned int        retweets;               /* Number of the retweets on this status, -1 means not avaialble */
    K_TT_USTR           source;                 /* Status publishing source */
    K_TT_USTR           thumnail_file_name;     /* File name of the thumbnail_pic */
    K_TT_USTR           pic_file_name;          /* File name of the large picture */
    K_TT_USTR           text;                   /* Text of the status, utf16 encoded */
    KTICK               created_at;             /* When the status was created */
    KBOOL               favorited;              /* Favorited by the current user? */
    KBOOL               have_image;             /* Does the status have a image? */
    unsigned int        pad1;

    /* User fields */
    KUINT64             user_id;                /* ID the the user who write the status */
    K_TT_USTR           user_screen_name;       /* Screen name of the user */
    K_TT_USTR           user_location;          /* Location of the user */
    K_TT_USTR           user_icon_file_name;    /* Icon file name of the user */
    unsigned int        user_followers_count;   /* Followers count of the user */
    unsigned int        user_friends_count;     /* Friends count of the user */
    unsigned int        user_statuses_count;    /* Statuses count of the user */
    unsigned int        user_favourites_count;  /* Favourtes count of the user */
    unsigned char       user_verified;          /* Is the user verified? (0 or non-0) */
    unsigned char       user_gender;            /* 'm'->male, 'f'->female, 'u'->unknown */
    unsigned short      pad2;
    unsigned int        pad3;

    /* Retweeted status fields */

    KUINT64             rt_id;                  /* ID of the retweeted status which is referenced by the status */
    unsigned int        rt_comments;            /* Number of the comments on the retweeted status, -1 means not available */
    unsigned int        rt_retweets;            /* Number of the retweets on the retweeted status, -1 means not avaialble */
    K_TT_USTR           rt_thumnail_file_name;  /* File name of the retweeted status thumnail picture */
    K_TT_USTR           rt_pic_file_name;       /* File name of the retweeted status large picture */
    K_TT_USTR           rt_text;                /* Text of the retweeted status */

    /* Retweeted status user fields */
    
    KUINT64             rt_user_id;             /* User id of the retweeted status */
    K_TT_USTR           rt_user_screen_name;    /* User screen name of the retweeted status */
} K_TT_STATUS;
/* serialized object}}} */

KSTATUS k_tt_api_status_db_open(const KWCHAR* app_dir);
void k_tt_api_status_db_close(void);

KSTATUS k_tt_api_save_status(const K_TT_STATUS* status);
KSTATUS k_tt_api_read_status(int index, K_TT_STATUS* tt_status, unsigned int buf_size);
KSTATUS k_tt_api_get_status_count(unsigned int* count);
KSTATUS k_tt_api_get_max_status_size(unsigned int* max_size);
KSTATUS k_tt_api_dump_status_object(const K_TT_STATUS* tt_status, const KWCHAR* file_name);
/*  format tick to time, save in time*/
void k_tt_api_format_tick_to_time(KTICK tick, KTIME time);
KTICK k_tt_api_format_message_to_relative_date(KTICK tick, KTICK* local);

/* API result status */
#define K_STATUS_API_ERROR                      8100
#define K_STATUS_API_NO_ACCOUNT                 8101
#define K_STATUS_API_ACCOUNT_LOGOUT             8102
#define K_STATUS_API_AUTH_ERROR                 8103
#define K_STATUS_API_NETWORK_ERROR              8104
#define K_STATUS_API_INVALID_PARAMETER          8105
#define K_STATUS_API_ACCESS_ERROR               8106        /* Read or write file failure */
#define K_STATUS_API_CANCEL                     8107
#define K_STATUS_API_NOT_SUPPORT                8108
#define K_STATUS_API_FULL_STORE                 8109

#define K_STATUS_API_NO_SIMCARD                 8150
#define K_STATUS_API_ALREADY_START              8151
#define K_STATUS_API_DOWNLOADING                8152
#define K_STATUS_API_NETWORK_SETTING            8153
#define K_STATUS_API_BUILT_IN_APP               8154

/*============== Open API return result access routines ====================*/

/* {{{serialized object */
typedef struct tagK_TT_GET_STATISTICS_RESULT
{
    KUINT64         num_comments;      /* Unread comment count */
    KUINT64         num_drmsgs;        /* Unread drmsg count */
    KUINT64         num_followers;     /* Unread followers count */
    KUINT64         num_mentions;      /* Unread metions count */
    KUINT64         num_statuses;      /* Unread statuses count */
} K_TT_GET_STATISTICS_RESULT;
/* serialized object}}} */

KSTATUS k_tt_api_save_get_statistics_result(const K_TT_GET_STATISTICS_RESULT* result);
KSTATUS k_tt_api_load_get_statistics_result(K_TT_GET_STATISTICS_RESULT* result, unsigned int* buf_size);

/* {{{serialized object */
typedef struct tagK_TT_SET_ACCOUNT_RESULT
{
    K_TT_USTR        app_name;
    K_TT_USTR        login_name;
} K_TT_SET_ACCOUNT_RESULT;
/* serialized object}}} */

KSTATUS k_tt_api_save_set_account_result(const K_TT_SET_ACCOUNT_RESULT* result);
KSTATUS k_tt_api_load_set_account_result(K_TT_SET_ACCOUNT_RESULT* result, unsigned int* buf_size);

/* {{{serialized object */
typedef struct tagK_TT_EDIT_BLOG_RESULT
{
    K_TT_USTR        text;
    K_TT_USTR        pic_path;
} K_TT_EDIT_BLOG_RESULT;
/* serialized object}}} */

KSTATUS k_tt_api_save_edit_blog_result(const K_TT_EDIT_BLOG_RESULT* result);
KSTATUS k_tt_api_load_edit_blog_result(K_TT_EDIT_BLOG_RESULT* result, unsigned int* buf_size);

/*set wallpaper*/
KSTATUS k_tt_api_set_wallpaper(const KWCHAR* path);

/****************************Share Information api type*****************************************/

enum{

    K_SHARE_INFORMATION_DEFAULT = 0,
    K_SHARE_INFORMATION_BY_MMS,
    
    K_SHARE_INFORMATION_MAX= 65535
};

/****************************Measure & Draw text helpers*****************************************/

#define K_BITMAP_MONO       0
#define K_BITMAP_GRAY_16    1
typedef struct
{
    int             format;
    int             width;
    int             height;
    int             pitch;
    const void*     buffer;
} K_BITMAP;

void k_fe_initialize(void);
void k_fe_cleanup(void);
void k_get_char_width(
    KWCHAR ch,
    int font_size,
    int* char_width,
    int* char_height);
void k_draw_char(
    int x,
    int y,
    KWCHAR ch,
    int font_size,
    KCOLOR text_color,
    int* char_width);

#ifdef __cplusplus
}
#endif

#endif /* KAPI_H */
