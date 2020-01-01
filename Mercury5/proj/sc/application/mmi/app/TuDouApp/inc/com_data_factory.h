
#ifndef __COM_DATA_FACTORY_H__
#define __COM_DATA_FACTORY_H__

#include <stdio.h>
#include "mmi_srv_filemgr.h"
#include "mmi_mae_helper.h"
//#include "mmi_common_storage_mgr.h"
#include "mmi_log.h"
#include "mmi_srv_fstream.h"
#include "com_json_parser.h"
#include "http_client.h"
#include "mmi_tudouapp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef MAE_WChar*       VMWSTR;
typedef char*            VMSTR;
typedef unsigned char *  VMUSTR;
typedef int              VMUCHAR;
typedef char *           VMCHAR;
typedef void*            VMUINT32;
typedef s16              VMINT;
typedef s8               VMINT8;
typedef u16              VMUINT;
typedef u32              VMFILE;
typedef char             com_Int8;

#define vm_file_delete  SrvFileMgrSyncDelete
#define mv_fm_isFileExist SrvFileMgrIsExist
#define vm_file_mkdir SrvFileMgrMkDir
#define vm_file_rmdir SrvFileMgrRmDir
#define MODE_CREATE_ALWAYS_WRITE "w"
#define MODE_READ "r"
#define com_nw_http_cb SgHttpFuncPtr
#define com_nw_http_progress_ind  SG_UINT8 *
#define wstrlen mae_wstrlen
#define vm_calloc  MALLOC
#define vm_free  FREEIF
#define td_com_wsprintf SPRINTF
#define td_com_stristr mae_strrstr
#define td_com_wstrcat STRCAT


#define COM_DF_FILE_PATH_LEN 256
//#define COM_DF_VIDEO_LIST_PAGESIZE 15


#define COM_DF_DISK_RESERVE_SPACE 50*1024 //启动时磁盘需要的剩余空间

#define COM_DF_VIDEO_INFOR_LENGTH 255

enum
{
    TUDOU_DOWNLOAD_STOP = 0,
    TUDOU_DOWNLOAD_COMPLETE = 1,
    TUDOU_DOWNLOAD_DOWNING = 2,
};
typedef u8 DownLoadStatus_t;
/*
typedef struct
{
    int nYear;
    int nMonth;
    int nDay;
    int nHour;
    int nMin;
    int nSec;
    int DayIndex; // 0=Sunday
} COM_TIME;
*/

typedef struct
{
    int canvas;
}MV_LOAD_PIC_STRUCT;

/*
typedef struct
{
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int sec;
}vm_time_t;
*/
//#endif

#define DF_DATA_KEY_SYS_CODE "sys_code"
#define DF_DATA_KEY_BUSINESS_CODE "business_code"

#define DF_DATA_KEY_CI "ci"
#define DF_DATA_KEY_SESSIONID "sessionid"

#define DF_DATA_KEY_ITEMS "items"
#define DF_DATA_KEY_ITEMID "itemid"
#define DF_DATA_KEY_ORIGIN "origin"
#define DF_DATA_KEY_FLUENCY_TRANSCODE "fluency_transcode"
#define DF_DATA_KEY_CLEAR_TRANSCODE "clear_transcode"
#define DF_DATA_KEY_ISHD "ishd"
#define DF_DATA_KEY_PICURL "picurl"
#define DF_DATA_KEY_VIDEO_PATH "video_path"
#define DF_DATA_KEY_TITLE "title"
#define DF_DATA_KEY_DESCRIPTION "description"
#define DF_DATA_KEY_TOTALTIME "totaltime"
#define DF_DATA_KEY_PLAYTIMES "playtimes"
#define DF_DATA_KEY_FLUENCY_URL "fluency_url"
#define DF_DATA_KEY_FLUENCY_URL_SIZE "fluency_url_size"
#define DF_DATA_KEY_CLEAR_URL "clear_url"
#define DF_DATA_KEY_CLEAR_URL_SIZE "clear_url_size"
#define DF_DATA_KEY_DOWNLOADURL "downloadurl"
#define DF_DATA_KEY_DOWNLOADURL_SIZE "downloadurl_size"
#define DF_DATA_KEY_TAGS "tags"
#define DF_DATA_KEY_LEVEL "level"
#define DF_DATA_KEY_PAGE "page"
#define DF_DATA_KEY_PAGECOUNT "pagecount"
#define DF_DATA_KEY_TYPE "type"
#define DF_DATA_KEY_KEYWORDS "keywords"
#define DF_DATA_KEY_KEYWORDS_KW "kw"
#define DF_DATA_KEY_KEYWORDS_CNT "cnt"
#define DF_DATA_KEY_VERSION "version"
#define DF_DATA_KEY_NEWFEATURES "newfeatures"
#define DF_DATA_KEY_TIMESTAMP "timestamp"
#define DF_DATA_KEY_COLUMNS "columns"
#define DF_DATA_KEY_COLUMN_ID "columnid"

#ifdef TUDOU_APP_FEATURE_WAP
#define DF_DATA_KEY_WAP_LINK "wapurl"
#define COM_DF_WAP_ID "ee"
#endif

/********************
****sys_code 状态
*********************/
//#define DF_DATA_SYSCODE_OK "000"  //正常
//#define DF_DATA_SYSCODE_ERROR "001" //请求参数异常
//#define DF_DATA_SYSCODE_SERV_ERROR "002" //服务端内部异常
//#define DF_DATA_SYSCODE_SERV_TIMEROUT "003" //服务端依赖资源超时异常

/********************
****business_code 状态
*********************/
//正常
//#define DF_DATA_BUSINESS_OK "000"

//ci非法,此时需清除客户端ci并重新签到(SignIn)获取ci
//#define DF_DATA_BUSINESS_INVALID_CI "001"

//sessionid失效,此时需重新签到获取sessionid
//#define DF_DATA_BUSINESS_INVALID_SESSION "002"

/*本客户端有新的建议升级版本,
此时提示用户有新的升级包。若用户选择升级，则获取updateinfo(下面有补充说明)中信息进行升级；
若用户未选择升级，则客户端获取updateinfo中timestamp字段，并保存起来。以后每次访问接口，都拿服务器最新返回的updateinfo中的timestamp值与客户端保存的timestamp值比对：如果间隔时间没超过一周，不提示用户有新版本；反之，则再次提示用户有新的更新包，并拿服务器timestamp刷新客户端保存的timestamp值。重复上述过程。*/
//#define DF_DATA_BUSINESS_NEED_UPDATE "003"

 //有强制更新版本,必须强制更新客户端
//#define DF_DATA_BUSINESS_MUST_UPDATE "004"

/********************
****联网错误代码
*********************/
//#define DF_NW_ERROR -1
//#define DF_NW_SET_CHANNEL_ERROR -2
//#define DF_NW_WRITE_FILE_ERROR -3
//#define DF_NW_CREATE_TIMER_ERROR -4
//#define DF_NW_NO_ENOUGH_SPACE -5


typedef enum
{
	OP_TYPE_NONE,

	//OP_ROOT_DIR,
	//OP_TMP_DIR,
	//OP_TMP_FILE,
	//OP_TD_GET_INDEX,
	//OP_TD_FREE_GPRS_LIST,
	OP_TD_WAP_LINK_LIST,
	OP_TD_SEARCH_LIST,
	OP_USER_SIGNIN, //用户签到
	OP_HOT_VIDEO, //热门视频
	OP_VIDEO_DETAIL, //视频详情
	OP_VIDEO_SEARCH, //视频搜索
	OP_VIDEO_CHANNEL, //栏目分类
    OP_VIDEO_CHANNELINFO, //栏目分类
	OP_HOTWORD_SEARCH, //搜索热词
	//OP_VERSION_UPDATE, //版本更新
	OP_DOWNLOAD_VIDEO, //下载视频
	OP_DOWNLOAD_PIC, //下载图片
	OP_DOWNLOAD_HISTORY, //下载历史
	OP_SEARCH_HISTORY, //下载历史

    #ifdef TUDOU_APP_FEATURE_WAP
       OP_FRIEND_SHIP_LINK, //   友情链接 
    #endif
    
	COM_DF_OP_TYPE_MAX
}COM_DF_OP_TYPE;
/*
typedef enum
{
	DF_HISTORY_NONE,

	DF_HISTORY_DOWN,
	DF_HISTORY_SEARCH,

	DF_HISTORY_MAX
}COM_DF_HISTORY_TYPE;
*/
typedef struct
{
	char *text;
	char *itemID;
	int page;
	int pageSize;
	int area; //搜索区域, 0:土豆无线视频  1:土豆主站视频
	char *origin; //视频来源:  0:土豆 1:移动  2:联调  3:电信
	char *ishd; //是否黑豆视频
	int search; //<0 无效, 如果是搜索视频，有效，0:土豆无线视频  1:土豆主站视频
	char *columnid;
    boolean bNotDownloadingUrl;
}com_url_param;


typedef struct
{
	common_json_data *handle; //内部使用

	char *sys_code;
	char *business_code;

	char *ci;
	char *sessionID;
}df_user_signin_data;

typedef struct _df_video_channel_paynode_data
{
	char *pay_show;
	char *free;
    char *pay_times;
    char *pay_prompt;
    char *pay_id;
    char *pay_akc;
}df_video_channel_paynode_data;
typedef struct _df_video_channel_data
{
	char *title;
	char *focusiconurl;
    char *iconurl;
    df_video_channel_paynode_data *paynode;
    char *columnid;
}df_video_channel_data;
typedef struct _df_video_channel
{
	common_json_data *handle;
	char *sys_code;
	char *business_code;
	char *text;
	df_video_channel_data *channel_data;
	struct _df_video_channel *next;
	struct _df_video_channel *prev;
}df_video_channel;
typedef struct _df_video_channelinfo_data
{
    char *level;
    char *itemId;
	char *title;
    char *totalTime;
	char *picurl;
    char *albumId;
    char *playTimes;
    char *playlistId;
    char *ishd;
    char *haspwd;
    char *origin;
    char *pwd;
    char *hd;
#ifdef TUDOU_APP_FEATURE_WAP
    char *wapurl;
#endif

}df_video_channelinfo_data;

typedef struct _df_video_channelinfo
{
	common_json_data *handle;
	char *sys_code;
	char *business_code;
	char *text;
	df_video_channelinfo_data *channelinfo_data;
	struct _df_video_channelinfo *next;
	struct _df_video_channelinfo *prev;
}df_video_channelinfo;
typedef struct
{
	common_json_data *handle; //内部使用

	char *sys_code;
	char *business_code;

	char *title;
	char *picurl; //预览图
	char *description; //介绍
	char *level;
	char *totalTime; //播放时长
	char *playTimes; //播放次数
	char *fluency_url; //流畅版在线播放地址
	char *clear_url; //清晰版在线播放地址
	char *downloadurl; //下载地址
	char *fluency_url_size;  //流畅版文件大小
	char *clear_url_size;  //清晰版文件大小
	char *downloadurl_size; //下载文件大小
	char *tags; //标签

	int fluency_transcode; //流畅版转码类型 。1：预转码  2：实时转码
	int clear_transcode; //清晰版转码类型 。1：预转码    2：实时转码
	char* origin;   // for TUDOU_APP_FEATURE_KING_MOVIE
}df_video_detail_data;

typedef struct _df_video_hotkey_data
{
	char *key;
	char *count;
}df_video_hotkey_data;

typedef struct _df_video_hotkey
{
	common_json_data *handle;

    char *debug;
	char *sys_code;
	char *business_code;

	char *text;
	df_video_hotkey_data *hotkey_data;

	struct _df_video_hotkey *next;
	struct _df_video_hotkey *prev;
}df_video_hotkey;

typedef struct _df_video_list_item_data
{
	char *itemId;
	char *origin;
	char *ishd;
	char *picurl;
	char *title;
	char *totalTime;
	char *playTimes;
	char *level;
#ifdef TUDOU_APP_FEATURE_WAP
    	char *wapurl;
#endif

       MV_LOAD_PIC_STRUCT res_pic;

	int pic_dl_ok;
	struct _df_video_list_item_data *next;
}df_video_list_item_data;

typedef struct _df_video_list_data
{
	int page;
	int pageCount;
	int type;

	char *sys_code;
	char *business_code;

	common_json_data *handle; //内部使用

	df_video_list_item_data *item_data;

	struct _df_video_list_data *prev;
	struct _df_video_list_data *next;
}df_video_list_data;
/*
typedef struct _df_version_updata_info
{
	common_json_data *handle; //内部使用

	char *sys_code;
	char *business_code;

	char *version;
//	char *timestamp;
	char *newfeatures;
	char *downloadurl;
}df_version_updata_info;
*/

typedef struct _df_download_history
{
	common_json_data *handle; //内部使用

	char *title;
	char *itemID;
	char *totalTime;
	char *playTimes;
	char *picurl; //缩略图的本地文件路径
	char *video_path;
	char *timestamp;
	int level;
	int from_json;
    MV_LOAD_PIC_STRUCT res_pic;

	struct _df_download_history *prev;
	struct _df_download_history *next;
}df_download_history;

typedef struct _df_download_video_infor
{
    //u32 videoLength;
    u32 videoLotalLength;
    //DownLoadStatus_t eStatus;
    char title[COM_DF_VIDEO_INFOR_LENGTH];
	char itemID[COM_DF_VIDEO_INFOR_LENGTH];
	char totalTime[COM_DF_VIDEO_INFOR_LENGTH];
	//char playTimes[COM_DF_VIDEO_INFOR_LENGTH];
	char picurl[COM_DF_VIDEO_INFOR_LENGTH]; //缩略图的本地文件路径
	char downloadurl[COM_DF_VIDEO_INFOR_LENGTH];
    char videolocalurl[COM_DF_VIDEO_INFOR_LENGTH];
    char videoInforlocalurl[COM_DF_VIDEO_INFOR_LENGTH];
	//char level[COM_DF_VIDEO_INFOR_LENGTH];
	MAE_WChar pSize[15];
    MAE_WChar pTime[15];

}df_download_video_infor;

typedef struct
{
	char *itemId;
	char *downurl;
	char *file_size;
	char *playurl;
	char *picurl;
	char *title;
	char *totalTime;
	char *playTimes;
	char *level;
	char *desc;
	MV_LOAD_PIC_STRUCT res_pic;

	int pic_dl_ok;
	int playurl_trans; //在线播放地址是否需要中转
}mv_video_data_common_struct;


typedef struct _df_search_history
{
	common_json_data *handle; //内部使用

	char *title;

	int from_json;

	struct _df_search_history *prev;
	struct _df_search_history *next;
}df_search_history;

#ifdef TUDOU_APP_FEATURE_WAP
typedef struct _df_wap_index_data
{
	char videotitle[128];
       char indexurl[128];
}df_wap_index_data;
#endif

typedef enum
{
	COM_DF_APN_NONE,

	COM_DF_CMWAP,
	COM_DF_CMNET,
	COM_DF_WIFI,

	COM_DF_APN_MAX
}COM_DF_APN_ENUM;
typedef struct _com_df_config_info
{
	int storage;
	int apn; //COM_DF_APN_ENUM
}com_df_config_info;
/*
typedef enum
{
	COM_DF_STRING_ID_START,

	COM_STR_LOADING1,
	COM_STR_LOADING2,
	COM_STR_LOADING3,
	COM_STR_LOADING4,
	COM_STR_PLEASE_WAITING,
	COM_STR_DOWNLOADING,
	COM_STR_HS_SEARCH_WORD,
	COM_STR_SEARCH_HISTORY,
	COM_STR_T_CARD,
	COM_STR_PHONE,
	COM_STR_APN_SETTING,
	COM_STR_DL_STORAGE,
	COM_STR_SEARCH_REZ,
	COM_STR_INTRO,
	COM_STR_INPUT_SEARCH_WORD,
	COM_STR_DELETE_CONFIRM,
	COM_STR_DL_CANCEL_CONFIRM,
	COM_STR_PREV_PAGE,
	COM_STR_NEXT_PAGE,
	COM_STR_EXIT_CONFIRM,
	COM_STR_DL_PLAY,
	COM_STR_DL_DEL,
	COM_STR_DL_CANCEL,

	//错误提示语
	COM_STR_VIDEO_DOWNLOADED,
	COM_STR_NO_ENOUGH_SPACE,
	COM_STR_DOWNLOAD_ERROR,
	COM_STR_NW_ERROR,
	COM_STR_WRITE_FILE_ERROR,
	COM_STR_NO_VALID_URL,
	COM_STR_DOWNLOAD_OK,
	COM_STR_NO_VALID_SEARCH_KEY,
	COM_STR_HAS_INVALID_CHAR,
	COM_STR_ONLY_CMCC_SUPPORT,
	COM_STR_VIDEO_PLAY_ERROR,
	COM_STR_LIST_NULL,
       COM_STR_LIST_NO_REZ,


	COM_DF_STRING_ID_END
}COM_DF_STRING_ID_ENUM;
*/

//extern void  vm_log_debug(const MAE_WChar *pFormat,...);
//extern VMINT  vm_get_system_driver();
//extern VMINT  vm_get_removable_driver();

//extern u32 vm_graphic_get_screen_width();
//extern u32 vm_graphic_get_screen_height();

void com_df_init(IApplet *pApplet);
void com_df_read_signin_data(IApplet *pApplet);
MAE_Ret com_df_clean_cache(IApplet *pApplet);

//extern void com_df_clear_singin_data(IApplet *pApplet);

extern VMUINT32 com_df_parse_hot_video_file(IApplet *pApplet, int page);

extern VMUINT32 com_df_parse_video_detail_file(IApplet *pApplet, char *itemID);

//extern void com_df_destroy_video_detail(VMUINT32 handle);
extern VMUINT32 com_df_parse_video_search_file(IApplet *pApplet, int page);
extern VMUINT32 com_df_parse_video_hotkey_file(IApplet *pApplet);
extern void com_df_get_download_video_path(IApplet *pApplet, char *file_path, char *title, char *url);
extern void com_df_get_download_pic_path(IApplet *pApplet, char *file_path, char *itemId, char *url);

extern char* com_df_get_video_list_sys_code(VMUINT32 handle);
extern char* com_df_get_video_list_business_code(VMUINT32 handle);
extern char* com_df_get_hotkey_sys_code(VMUINT32 handle);
extern char* com_df_get_hotkey_business_code(VMUINT32 handle);

extern df_video_list_item_data* com_df_get_video_list_item(VMUINT32 handle, int index);
extern int com_df_get_video_list_count(VMUINT32 handle);
extern df_video_list_item_data* com_df_get_video_list_item(VMUINT32 handle, int index);
//extern void com_df_destroy_video_list(VMUINT32 handle);
//extern int com_df_get_hotkey_count(VMUINT32 handle);
//extern df_video_hotkey* com_df_get_hotkey_item(VMUINT32 handle, int index);
//extern void com_df_destroy_video_hotkey(VMUINT32 handle);
/*
extern VMUINT32 com_df_parse_history_list(char *file_path, int length, COM_DF_HISTORY_TYPE history_type);
extern void com_df_destroy_history_list(VMUINT32 handle, COM_DF_HISTORY_TYPE history_type);
extern VMUINT32 com_df_history_open(IApplet *pApplet, COM_DF_HISTORY_TYPE type);
extern void* com_df_history_get(VMUINT32 handle, int index, COM_DF_HISTORY_TYPE history_type);
extern int com_df_history_get_count(VMUINT32 handle, COM_DF_HISTORY_TYPE history_type);
extern void* com_df_history_get_page_item(VMUINT32 handle, int page, int page_count, int index, COM_DF_HISTORY_TYPE history_type);
extern VMUINT32 com_df_history_del(IApplet *pApplet, VMUINT32 handle, int index, COM_DF_HISTORY_TYPE history_type, VMINT8 del_file);
extern VMUINT32 com_df_history_add(IApplet *pApplet, VMUINT32 handle, mv_video_data_common_struct *item_data, char *video_file_path, COM_DF_HISTORY_TYPE history_type);
extern void com_df_history_close(VMUINT32 handle, COM_DF_HISTORY_TYPE history_type);

extern VMUSTR com_df_get_string(int id);
*/

extern void *com_system_mem_malloc_ext(int size);
extern void com_system_mem_free_ext(void *buf);
#ifdef __COM_MEM_DEBUG__
extern void* __com_system_mem_malloc(int size, char* file_p, long line_p);
extern void  __com_system_mem_free(void *ptr, char* file_p, long line_p);
#endif

#define com_system_mem_malloc(size)  com_system_mem_malloc_ext(size)
#define com_system_mem_free(buf)  com_system_mem_free_ext(buf)

VMUINT32 com_df_user_signin(IApplet *pIApplet, com_nw_http_cb callback);
VMUINT32 com_df_get_hot_video(IApplet *pIApplet, int page, com_nw_http_cb callback);
VMUINT32 com_df_download_pic(IApplet *pIApplet, char *itemId, char *url,  com_nw_http_cb callback, com_nw_http_progress_ind progress_ind);
VMUINT32 com_df_get_video_detail(IApplet *pIApplet, char *itemID,  char* origin, char *ishd, int search, com_nw_http_cb callback);
VMUINT32 com_df_hotword_search(IApplet *pIApplet, com_nw_http_cb callback);
VMUINT32 com_df_download_video(IApplet *pIApplet, char *itemID, char *url,  com_nw_http_cb callback, com_nw_http_progress_ind progress_ind);
VMUINT32 com_df_video_search(IApplet *pIApplet, char *kw, int page, int area, com_nw_http_cb callback);
char *com_df_get_file_ext_from_url(char * url);
VMUINT32 com_df_channel_type_search(IApplet *pIApplet, com_nw_http_cb callback);
VMUINT32 com_df_channel_list_search(IApplet *pIApplet, char *columnid, int page, com_nw_http_cb callback);
VMUINT32 com_df_parse_video_Channel_file(IApplet *pApplet);
VMUINT32 com_df_parse_video_ChannelInfo_file(IApplet *pApplet, char *columnid, int page);
void com_df_get_tmp_file_path(IApplet *pApplet, char *file_path, COM_DF_OP_TYPE type, com_url_param *param);

#ifdef TUDOU_APP_FEATURE_WAP
extern VMUINT32 com_df_parse_wap_link_video_file(IApplet *pApplet, int page);
extern void com_df_get_wapindex_data(IApplet *pApplet, VMUINT32 handle);
VMUINT32 com_df_get_wap_list(IApplet *pIApplet, int page, com_nw_http_cb callback);
int com_df_read_wapindex_data(IApplet *pApplet, int page);
void com_df_get_wap_data_by_rand(IApplet *pApplet);
VMUINT com_df_check_china_mobile_card(IApplet *pIApplet);
char* com_df_get_friendship_link_by_rand(IApplet *pApplet, int* index);

#endif

#ifdef __cplusplus
}
#endif

#endif
