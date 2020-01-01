/*
 * netapp.h
 */
#ifndef __NETAPP_H__
#define __NETAPP_H__

//#include "os_wrap.h"
//Because network module includes this file.
//Try not to use AHC files or even MMPS/MMPD files for better portability
//#include "AHC_WarningMSG.h"

//Status about Net
#define NETAPP_NET_STATUS_NONE              0
#define NETAPP_NET_STATUS_INIT              1
#define NETAPP_NET_STATUS_IDLE              2
#define NETAPP_NET_STATUS_READY             3
#define NETAPP_NET_STATUS_NOIP              4
#define NETAPP_NET_STATUS_DOWN              6

//Net error status, >= 128
#define NETAPP_NET_STATUS_INIT_FAIL         128

//Status about WIFI-streaming
#define NETAPP_STREAM_NONE                  0x00000000
#define NETAPP_STREAM_TEARDOWN              0x00000001
#define NETAPP_STREAM_PLAY                  0x00000002
#define NETAPP_STREAM_ERR_MASK              0xffff0000
#define NETAPP_STREAM_SOCKET_ERR            0x00010000
#define NETAPP_STREAM_MEM_ERR               0x00020000
#define NETAPP_STREAM_RTCP_ERR              0x00040000
#define NETAPP_STREAM_RTSP_ERR              0x00080000

#define IS_WIFI_STREAM_FAIL(s)              ((s & NETAPP_STREAM_ERR_MASK))

#define NETAPP_DONE (-1)    // finish job, not to do any more after return.
#define NETAPP_FAIL (-2)
#define NETAPP_CONT (0)

#define NETAPP_WIFI_AP_MODE         1
#define NETAPP_WIFI_STATION_MODE    2

/*===========================================================================
 * nui: Network UI. This typically with NUI_CALL that it would be project
 *      dependent and might not be implemented.
 *===========================================================================*/

/*
 * functions in AHC
 */
/*__weak*/ void AHC_DrawNetFwDownloadProgress( int uiDownloadPercentage ) __attribute__((weak));

/*
 * Get which SET for WiFi AP used.
 * return 0 or 1 for AP configuration set 0 or 1
 */
int ncam_get_ui_ap_setting(void);

#define FORMAT_SD_NONE  0
#define FORMAT_SD_DOING 1
#define FORMAT_SD_DONE  2
#define FORMAT_SD_ERROR 3


/*===========================================================================
 * nhw Network HardWare
 *===========================================================================*/

#undef  _NETAPP_DEBUG
#ifndef _NETAPP_DEBUG
int nhw_set_status(int status);
int nhw_get_status(void);
#else
int nhw_set_status_dbg(int status, char *file, int line);
#define nhw_set_status(s)   nhw_set_status_dbg(s, __FILE__, __LINE__)
int nhw_get_status(void);
#endif
int nhw_get_sys_mode(void);

int nhw_send_event(unsigned int event);
#define SEND_NETWORK_EVENT(e) nhw_send_event(e)


#define IS_CAMERA_IN_HDMI() ncam_is_hdmi_on()//(strcmp(ncgi_get_tv_status(), "NONE") != 0)

//==== declaration for lwip_main.c ====
typedef void *(*job_routine)(void *arg);
void* add_NetworkJob(job_routine routine, void *arg, /*MMP_BOOL*/unsigned char bneedlock);
void kick_NetworkJob(void);
int  network_init_done(void);
//==== end of lwip_main.c ====

#define NHW_PANA_RULE 0
//NHW_PANA_RULE is no longer needed since WLAN_STA_AutoSelectChannel is located in UI directory now
#if NHW_PANA_RULE
enum nhw_auto_chan_rule_t {
    NHW_AUTO_CHANNEL_AIT_RULE = 0,
    NHW_AUTO_CHANNEL_PANA_RULE
};
#endif

enum nhw_country_chan_t {
    NHW_COUNTRY_ALL = 0, //CH 1~14
    NHW_COUNTRY_TW       //CH 1~11
};

#if NHW_PANA_RULE
void nhw_set_auto_chan_rule(enum nhw_auto_chan_rule_t rule);
enum nhw_auto_chan_rule_t nhw_get_auto_chan_rule(void);
#endif

void nhw_set_country(enum nhw_country_chan_t country);
enum nhw_country_chan_t nhw_get_country(void);

int nhw_turn_on_wlan(void);
int nhw_turn_off_wlan(void);

void nhw_init_ap_check_assoc(void);
int nhw_add_connected_sta(unsigned char * mac);
void nhw_remove_disconnected_sta(unsigned char * mac);
int nhw_check_sta_leave(unsigned char * curmaclist ,unsigned char curlistcount, unsigned char * leavemaclist);
void nhw_set_streaming_mac(unsigned char * mac);
void nhw_get_streaming_mac(unsigned char * mac);
int nhw_cmp_streaming_mac(unsigned char * mac);
/* Wireless driver handle. */
typedef void* nhw_drv_hdl;
void nhw_set_handle(nhw_drv_hdl h);
nhw_drv_hdl* nhw_get_handle(void);

int nhw_wifi_link_report(int updown);//updown : 1 is up,0 is down
int nhw_init_network(void);
int nhw_stop_network(void);
int nhw_reset_network(void);
int nhw_cmd_network(void);

int nhw_start_sta_wps(void);
//int netapp_SetWifiMode(int mode);
int nhw_reset_wps_info(void);

int nhw_is_wps_paired(void);//use config, called from UI
int nhw_auto_join_ap(void);//use LWIP, called from UI
int nhw_get_sta_rssi(void);//use WLAN, called from CGI

int nhw_broadcast_ssid(int enable);


/*
 * return 1: AP mode
 *        2: STA mode
 */
int nhw_get_cur_wifi_mode(void);
/*
 * return 1: AP mode(NETAPP_WIFI_AP_MODE)
 *        2: STA mode(NETAPP_WIFI_STATION_MODE)
 */
int nhw_get_target_wifi_mode(void);

/*
 * mode     1: AP mode (NETAPP_WIFI_AP_MODE)
 *          2: STA mode (NETAPP_WIFI_STATION_MODE)
 */
int nhw_set_wifi_mode(int mode);

/*
 * return unsigned int (little endian) for ipv4
 *        ip: xxx.xxx.xxx.xxx = byte0.byte1.byte2.byte3
 */
unsigned int nhw_get_ip_addr(void);
void nhw_get_wifi_mac(unsigned char /*MMP_UBYTE*/ *addr);
void nhw_set_wifi_mfg(unsigned char enable);
unsigned char nhw_get_wifi_mfg(void);
/*===========================================================================
 * ncam: Network CAMera, called from other module to AHC or UI.
 *===========================================================================*/
int ncam_get_app_status(void);
int ncam_set_streaming(short enable);
int ncam_enable_ui_streaming_mode(unsigned int mode);
int ncam_set_streaming_mode(unsigned int mode);
int ncam_get_streaming_mode(void);

int ncam_is_recording(void);
int ncam_is_capturing(void);
int ncam_is_hdmi_on(void);
int ncam_is_h264_streaming_supported(void);
int ncam_get_rtc_year(void);
int ncam_get_rtc_month(void);
int ncam_get_rtc_day(void);
int ncam_get_rtc_hour(void);
int ncam_get_rtc_minute(void);
int ncam_get_rtc_second(void);

const char* ncam_get_fw_version(void);
int ncam_get_mjpeg_bitrate(void);
int ncfg_get_h264_bitrate(void);
int ncam_enable_h264_stream(int bEnabled);

int ncam_stop_transcoding(void);
int ncam_close_transcoding(void);

int ncam_get_rec_time_total(void);
int ncam_get_rec_time_start(void);
int ncam_get_rec_time_remaining(void);
int ncam_get_rec_time_available(void);
int ncam_get_ui_cap_remaining(void); //ncam_get_shots_remaining
unsigned long ncam_get_streaming_time(void);
int ncam_get_ui_power_level(void);
int ncam_is_streamable(int streamtype);
int ncam_is_flashable(void);
int ncam_upload_progress(unsigned int cursize, unsigned int total);
int ncam_get_audio_sampling_rate(void);
int ncam_update_audio_sampling_rate(int transcode);


//==== Camera Switching Controlling ====
int ncam_switch_cam(void);
int ncam_get_cam_src(unsigned int vMode);
int ncam_is_rear_cam_ready(void);
void ncam_set_rear_cam_ready(int state);

void ncam_parse_date_time(int* datetime, char* timestr);
unsigned int ncam_get_streaming_timer(void);
int ncam_parse_file(char *file_name, int video_format, int audio_format);
const char* ncam_get_sensor_status(void);
int ncam_get_mjpeg_res(unsigned short *w, unsigned short *h, char *name);
int ncam_del_file(char *path);
int ncam_check_filelock(char *path);
int ncam_get_h264_res(unsigned short *w, unsigned short *h, unsigned short *cropBottom, unsigned short *cropRight);

//==== Settings ====
enum VALUE_TYPE {
    VALUE_TYPE_INT, // 4 bytes integer
    VALUE_TYPE_STR, // c string
    VALUE_TYPE_PTR, // pointer
    VALUE_TYPE_2_INT, // 2 2-bytes integers. example use: resolution
    VALUE_TYPE_4_BYTES, // 4 1-byte integers. example use: RGBA
    VALUE_TYPE_UNDEFINED,
    VALUE_TYPE_MAX
};

// This structure is similar to struct amn_cfgspace_value_t in amn_sysobj.h
// But this does not link to .conf file. It could be access by any module because any module could use netapp
typedef struct {
    enum VALUE_TYPE type;
    union {
        int i32;
        void* ptr;
        char* str;
        short i16[2];
        char i8[4];
    } v;
} ncam_val_t;

//Net CAMera setting type
//NCS stands for Net Camera Setting
enum ncam_setting_t {
    NCS_AUDIO_SAMPLING_RATE, //VALUE_TYPE_INT
    NCS_AUDIO_PREVIEW,//VALUE_TYPE_INT, audio on or off in preview
    NCS_TRANSCODE_FILE_NAME,//VALUE_TYPE_STR
    NCS_FILE_DURATION, //VALUE_TYPE_INT, file duration in milli-seconds, (-1L) means undefined
        #define NCS_FILE_DURATION_UNDEFINED (-1L)
    NCS_MAX
};

int ncam_get_setting(enum ncam_setting_t setting, ncam_val_t* v);
int ncam_set_setting(enum ncam_setting_t setting, ncam_val_t* v);

/*===========================================================================
 * ns:  Network Server, typically streaming server
 *===========================================================================*/
enum NS_MEDIA_TYPE {
    NS_MEDIA_NONE,
    NS_MEDIA_H264,
    NS_MEDIA_MJPEG,
    NS_MEDIA_VMASK = 0x0F,
    NS_MEDIA_AMASK = 0xF0,
    NS_MEDIA_AUDIO = 0x10, //general audio
    NS_MEDIA_PCM   = 0x20,
    NS_MEDIA_AAC   = 0x30,
    NS_MEDIA_CMASK = 0xF00,//container mask
    NS_MEDIA_JPEG  = 0x100,
    NS_MEDIA_MOV   = 0x200,
    NS_MEDIA_MAX
};

typedef enum _NS_EVENT_HANDLER_TYPE {
    NS_EVENT_CONNECT, ///< Connect and disconnect
    NS_EVENT_DESCRIBE, ///< When a client is requesting the description of the stream
    NS_EVENT_BROADCAST_PROLOGUE,///< Use struct NS_ON_CGI_BUF_PARAM
    NS_EVENT_BROADCAST_EPILOGUE,///< Use struct NS_ON_CGI_BUF_PARAM
    NS_EVENT_QUERY_THUMB_STATE, ///< Query if UI state of thumbnail, Use NS_MEDIA_TYPE as parameter
    NS_EVENT_GET_STATUS, ///< Query the project-customized status. Use struct NS_ON_CGI_BUF_PARAM
    NS_EVENT_BROADCAST, ///< Triggers a Broadcast
    NS_EVENT_MAX
}NS_EVENT_HANDLER_TYPE;

struct NS_ON_CGI_BUF_PARAM {
    char* listBuf;//string of list buffer
    int maxlen;//max length of the string
    int *curLen; //pointer to current length of the string
};

struct NS_ON_CONNECT_PARAM {
    unsigned short num_viewers; ///< number of total viewers AFTER this event
    short diff;                 ///< the viewer difference between before event and after event
    enum NS_MEDIA_TYPE media_type;
};

typedef enum NS_EV_RET {
    NSE_CB_NOT_FOUND = -11,
    NSE_HANDLER_NOT_FOUND = -10,
    NSE_PARAM = -2,
    NSE_ERR = -1, //general err
    NSE_OK = 0,
    NSE_INFO ///< Other info that is not error
} NS_EV_RET;

#define ANY_NS_ERR(x) ((x) <= NSE_ERR)

/** Net streaming server event handler.
 *  @param param input parameter. Typically a pointer to a structure, such as NS_ON_CONNECT_PARAM
 *  @return <0 for any error. 0 for success.
 */
typedef NS_EV_RET (*NS_EVENT_CB)(void* eventData, void* userData);

typedef struct _NS_EVENT_HANDLER {
    NS_EVENT_CB callback;
    void* userData;
} *NS_EVENT_HANDLER;

NS_EV_RET ns_set_ev_handler(NS_EVENT_HANDLER_TYPE handler_type, NS_EVENT_CB callback, void* userData);
//NS_EVENT_HANDLER ns_get_event_handler(NS_EVENT_HANDLER_TYPE handler_type);
NS_EV_RET ns_handle_event(NS_EVENT_HANDLER_TYPE handler_type, void* eventData);

void ns_pump_streaming(void);
int ns_set_frc(int inx1000, int outx1000, char* name);
int ns_set_fps(int fps, char* name);
int ns_has_stream_control(void);
int ns_set_streaming_status(int status);
int ns_get_streaming_status(void);
/*===========================================================================
 * ncgi: Network CGI. CGI is complex which might use CGI, AHC or UI function
 *===========================================================================*/
// all error must < 0, while >= It would be a state.
// in obsolete code, hard-coded number, such as -4, is used. If enum is used everywhere,
// here could be possibly mapped to CGI_ERR__OK in amn_cgi.h directly later.
enum cgi_err_t {
    CGI_RET_UNASSIGNED = 3,
    CGI_RET_PARKING_SPACE = 2,
    CGI_RET_STOP = 1,
    CGI_ERR_NONE = 0,
    CGI_ERR_NO_CARD = -1,
    CGI_ERR_CARD_LOCK = -2,
    CGI_ERR_CARD_ERROR = -3,
    CGI_ERR_CARD_FULL = -4,
    CGI_ERR_SEAMLESS = -5,
    CGI_ERR_PERIPHERAL = -6, //external peripheral error, such as low voltage.
    CGI_ERR_INVALID_STATE = -7,
    CGI_ERR_INVALID_PARAM = -8,
    CGI_ERR_TIMEOUT = -10, //CGI_ERR__SYS_BUSY
    CGI_ERR_GENERAL = -100,
    CGI_ERR_NOT_IMPLEMENTED = -101
};
typedef int  (*PFN_WEBWAIT)(void* msg, void* time_out);
typedef void (*PFN_CGI_OP_CALLBACK)(void* msg, enum cgi_err_t result);
typedef struct ncgi_ret {
    int netapp;         //The return value for NETAPP module processing.
    enum cgi_err_t cgi; //The CGI return value reported from UI event handler.
}ncgi_ret;

//==== CGI MENU ====

typedef unsigned char NCGI_MENU_IDX;

typedef struct {
    char *cgi_val;
    NCGI_MENU_IDX    menu_id;
} CGI_MENU_MAP;

#define DIM_OF_COMBNATION (3) //front, rear and streaming.
//#define DIM_OF_COMBNATION (4) //front, rear and streaming 1, streaming 2
typedef NCGI_MENU_IDX NCAM_RES_COMB_ENTRY[DIM_OF_COMBNATION];
#define END_OF_INDEX (0xFF)
#define RES_NONE END_OF_INDEX

typedef struct {
    /** Index for verification. Used for double checking the index
     *  Because the table is maintained per project, likely by human, it would be safer to put an index here
     *  to prevent human error. It also make it easier while writing final NCAM_RES_COMB_MAP.
     */
    NCGI_MENU_IDX idx;
    CGI_MENU_MAP cgi_menu;
}CGI_MENU_MAP_ENTRY;


typedef struct NCAM_RESOLUTION_MAP {
    NCGI_MENU_IDX idx;//Used for human debugging
    char* name; //Used for human debugging
    CGI_MENU_MAP_ENTRY *cgi;
}NCAM_RES_MAP;
typedef struct NCAM_RESOLUTION_COMBINATION_MAP {
    int dimension;
    NCAM_RES_COMB_ENTRY *comb;
    NCAM_RES_MAP *map;
}NCAM_RES_COMB_MAP;


int ncgi_op_callback(PFN_CGI_OP_CALLBACK pfn);
ncgi_ret ncgi_send_ui_event(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
unsigned char ncgi_get_ui_state_id(void);
const char* ncgi_get_ui_state(void);
int ncgi_is_need_feedback(void);
//==== standard CGI processing functions ==== from webserver.c
void webwait_uisignal(void *handle, enum cgi_err_t arg);
int webwait_uiproc(void *handle, void *arg/*time out*/);

int wait_streaming_op_uiproc(void *handle, void *arg);
int nstreaming_op_feedback(void *handle, int result);

#define CGIOP_DBG (0) ///< Set 1 for debugging detail calling location

#if WIFI_PORT == 1
    #if CGIOP_DBG
        int ncgi_op_feedback_dbg(void *handle, enum cgi_err_t result, char *file, int line);
        #define ncgi_op_feedback(h, r) ncgi_op_feedback_dbg(h, r, __FUNCTION__, __LINE__)
    #else
        int ncgi_op_feedback(void *handle, enum cgi_err_t result);
    #endif
    extern signed int               gslCGIFeedbackStatus;
    extern unsigned int             gulCGIFeedbackEvent;
    #define CGI_SET_STATUS(e,s) {if(ncgi_is_need_feedback()) {gulCGIFeedbackEvent = (e); gslCGIFeedbackStatus = (s);}}
    #define CGI_FEEDBACK()      {if(ncgi_is_need_feedback()) {ncgi_op_feedback((void*)gulCGIFeedbackEvent, gslCGIFeedbackStatus);}}
#else
    #define ncgi_op_feedback(handle,result) 0 //always return OK
    #define CGI_SET_STATUS(e,s)
    #define CGI_FEEDBACK()
#endif

int ncgi_has_warning_msg(void);
int ncgi_get_warning_msg(void);
//m_WMSG_Info mapped to type WMSG_INFO
int ncgi_set_warning_msg(int m_WMSG_Info);
//
int ncgi_flash_fw(char *filename, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s);
//struct ncgi_ret ncgi_send_ui_msg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, void *arg);

void ncgi_send_camera_state(void);

//ncgi_notification_t
#define NOTIFY_NULL             0
#define NOTIFY_CAPTURE          1
#define NOTIFY_TIMELAPSE        2
#define NOTIFY_TIMELAPSE_STOP   3
#define NOTIFY_FWUPDATED        4
#define NOTIFY_CUSTOMIZE        100 //The user has to allocate and prepare the data to be sent

typedef struct _notify_reason_t notify_reason_t;
#define NCGI_DEF_REASON (0)
void ncgi_notify_set_len(notify_reason_t* notify, int datalen);
notify_reason_t* ncgi_notify_uiroll(int reason/*ncgi_notification_t*/, void *data);
#if WIFI_PORT == 1
int ncgi_notify_uichange(notify_reason_t*);
#else
#define ncgi_notify_uichange(ptr) 0 //return OK
#endif

#define NCGI_SHORT_FN 0
#define NCGI_EMER_FN 1
#define NCGI_DL_FN 2
#define NCGI_VR_CAP_FN 3
#define NCGI_MAX_FN_NUM 4
#define NCGI_ANY_FN (NCGI_MAX_FN_NUM + 1) //Any file name
int ncgi_notify_fn(int type, char* full_fn);
int ncgi_clr_notify_fn(int type, char* full_fn);
#define ncgi_notify_short_fn(full_fn) ncgi_notify_fn(NCGI_SHORT_FN, full_fn)

/*===========================================================================
 * ncfg: Network config. Functions that access network configuration
 *===========================================================================*/
int ncfg_get_h264_res(int *conf_w, int *conf_h);
int ncfg_get_v_res(const char *conf, int *w, int *h);
int ncfg_get(char* key, void* val);
int ncfg_set(char* key, void* val);
//int ncam_stabroadcast_receive_start(void);
//void ncam_hotspotbroadcast_routine_stop(void);
#if WIFI_PORT == 1
int ncam_save_net_conf(void);
#else
#define ncam_save_net_conf() 1
#endif

/*
*   @PAR1 : A pointer of the memory that is used to fill customized SSID by UI.
*   @PAR2 : A pointer of the memory that is used to fill customized PSWD by UI.
*   @PAR3 : The length of PAR1.
*   @PAR4 : The length of PAR2.
*/
typedef void (* CUSTOMIZED_SSIDPSWD_CB)(char *,char *,unsigned short,unsigned short);
typedef int (* NET_DID_ACCESS_CB)(int readorwrite ,void *par ,int inputlen);
void ncfg_register_customer_ssidpswd(CUSTOMIZED_SSIDPSWD_CB cb);
CUSTOMIZED_SSIDPSWD_CB ncfg_get_customized_ssid_cb(void);
void ncfg_register_didtoken_accessed(NET_DID_ACCESS_CB cb);
NET_DID_ACCESS_CB ncfg_get_didtoken_accessed_cb(void);
void ncfg_allow_APP_access(int alloworreject);
/*===========================================================================
 * netapp: Net APP for general system utilities
 *===========================================================================*/
// To protect between GET-VIDEO-TUMBNAIL and CAPTURE/BURST/TIMELAPSE to avoid system crashing.
#define LOCK_CAPTURE            1
#define UNLOCK_CAPTURE          0
#define LOCK_CAPTURE_TIMEOUT    8000
#define LOCK_DEBUG              0

#if WIFI_PORT == 1
    #if LOCK_DEBUG
        #define netapp_cap_lock(e, t)   netapp_cap_lock_dbg(e, t, __func__, __LINE__)
        int netapp_cap_lock_dbg(int enLock, unsigned int timeout, char *f, int l);
    #else
        int netapp_cap_lock(int enLock, unsigned int timeout);
    #endif
#else
    #define netapp_cap_lock(enLock, timeout) 0 //return OK
#endif

/*===========================================================================
 * Obsolete naming mapping
 *===========================================================================*/
#define OBSOLETE_NETAPP 0 //set 1 for the project to use old naming
#if OBSOLETE_NETAPP
//#define NUI_BlankLed                    nui_blank_led
#define set_NetAppStatus                nhw_set_status
#define get_NetAppStatus                nhw_get_status
#define netapp_SetAutoChannelRule       nhw_set_auto_chan_rule
#define netapp_GetAutoChannelRule       nhw_get_auto_chan_rule
#define netapp_SetWifiCountryCode       nhw_set_country
#define netapp_GetWifiCountryCode       nhw_get_country
#define TurnOnWiFiModule                nhw_turn_on_wlan
#define TurnOffWiFiModule               nhw_turn_off_wlan
#define netapp_setHwHandle              nhw_set_handle
#define netapp_getHwHandle              nhw_get_handle
#define netapp_WifiLinkReport           nhw_wifi_link_report
#define netapp_InitNetwork              nhw_init_network
#define netapp_StopNetwork              nhw_stop_network
#define netapp_ResetNetwork             nhw_reset_network
#define netapp_CmdNetwork               nhw_cmd_network
#define netapp_StartSTAModeWPS          nhw_start_sta_wps
#define netapp_ResetWPSInfo             nhw_reset_wps_info
#define netapp_IsWPSPaired              nhw_is_wps_paired
#define netapp_AutoJoinAP               nhw_auto_join_ap
#define netapp_Get_STA_Rssi             nhw_get_sta_rssi
#define netapp_BroadcastSSID            nhw_broadcast_ssid
#define netapp_getWiFiMacAddr           nhw_get_wifi_mac
#define netapp_GetWiFiCurMode           nhw_get_cur_wifi_mode
#define netapp_GetWiFiTargetMode        nhw_get_target_wifi_mode
#define netapp_SetWiFiMode              nhw_set_wifi_mode
#define netapp_GetIPAddress             nhw_get_ip_addr
#define netapp_GetWiFiMode              nhw_get_wifi_mode
#define get_CamAppStatus                ncam_get_app_status
#define NetApp_SetStreaming             ncam_set_streaming
//#define netapp_exe_Streaming_cb         ncam_run_streaming_cb
//#define netapp_set_Streaming_cb         ncam_set_streaming_cb
#define NetApp_GetRecordStatus          ncam_is_recording
#define NetApp_GetCaptureStatus         ncam_is_capturing
#define netapp_get_TimeStamp_year       ncam_get_rtc_year
#define netapp_get_TimeStamp_month      ncam_get_rtc_month
#define netapp_get_TimeStamp_day        ncam_get_rtc_day
#define netapp_get_TimeStamp_hour       ncam_get_rtc_hour
#define netapp_get_TimeStamp_minute     ncam_get_rtc_minute
#define netapp_get_TimeStamp_second     ncam_get_rtc_second
#define netapp_DateTime_Parser          ncam_parse_date_time
#define netapp_get_SD0Status            ncam_get_ui_sd0_status
#define netapp_set_SD0Status            ncam_set_ui_sd0_status
#define netapp_get_FW_Version           ncam_get_fw_version
#define netapp_get_MjpegBitrate         ncam_get_mjpeg_bitrate
#define netapp_get_H264Bitrate          ncam_get_h264_bitrate
#define netapp_Enableh264Stream         ncam_enable_h264_stream
#define netapp_SaveNetworkConf          ncam_save_net_conf
#define netapp_stopTranscoding          ncam_stop_transcoding
#define netapp_closeTranscoding         ncam_close_transcoding
#define netapp_get_RecordTimeTotal      ncam_get_rec_time_total
#define netapp_get_RecordTimeStart      ncam_get_rec_time_start
#define netapp_get_RecordTimeRemaining  ncam_get_rec_time_remaining
#define netapp_get_RecordTimeAvailable  ncam_get_rec_time_available
#define netapp_get_CaptureRemaining     ncam_get_ui_cap_remaining
//#define netapp_getStreaming_Timestamp   ncam_get_streaming_time
//#define netapp_stream_flush             ncam_flush_stream
//#define netapp_stream_enable            ncam_enable_stream
#define netapp_get_PowerLevel           ncam_get_ui_power_level
#define netapp_query_Streamable         ncam_is_streamable
#define netapp_query_Flashable          ncam_is_flashable
#define netapp_uploadprogress           ncam_upload_progress
#define netapp_getStreamingMode         ncam_get_streaming_mode
#define netapp_GetWiFi_AP_set           ncam_get_ui_ap_setting
#define netapp_update_AudioSamplingRate ncam_update_audio_sampling_rate
#define netapp_getAudioSampleRate       ncam_get_audio_sampling_rate
#define netapp_get_streaming_timer      ncam_get_streaming_timer
#define netapp_parsefile                ncam_parse_file
#define netapp_SensorStatus             ncam_get_sensor_status
#define netapp_get_MjpegResolution      ncam_get_mjpeg_res
#define netapp_DeleteFile               ncam_del_file
#define netapp_get_DeviceSetting        ncam_get_setting
#define netapp_set_DeviceSetting        ncam_set_setting
#define netapp_getCameraSrc             ncam_get_cam_src
#define netapp_switchCamera             ncam_switch_cam
#define netapp_getRearcamReady          ncam_is_rear_cam_ready
#define netapp_setRearcamReady          ncam_set_rear_cam_ready

#define netapp_Pump                     ns_pump_streaming
#define netapp_set_FRC                  ns_set_frc
#define netapp_set_framerate            ns_set_fps
#define netapp_CGIOpCallback            ncgi_op_callback
#define netapp_IsNeed_Feedback          ncgi_is_need_feedback
#define NetApp_SetKeyevent              ncgi_send_key_event
#define netapp_CGIOpFeedback            ncgi_op_feedback
#define netapp_warning_msg_state        ncgi_has_warning_msg
#define netapp_get_warning_msg_info     ncgi_get_warning_msg
#define set_netapp_WMSGInfo             ncgi_set_warning_msg
#define netapp_cfg_get                  ncgi_cfg_get
#define netapp_flashFW                  ncgi_flash_fw
#define Report2UIAndWaitFeedBack        ncgi_send_ui_msg
#define netapp_get_Video_Resolution     ncgi_get_video_res
#define netapp_get_VideoClipTime        ncgi_get_video_clip_time
#define netapp_get_Image_Resolution     ncgi_get_image_res
#define netapp_get_WB                   ncgi_get_wb
#define netapp_get_Flicker_Hz           ncgi_get_flicker_hz
#define netapp_get_MTD_Level            ncgi_get_mtd_level
#define netapp_get_EV_Level             ncgi_get_ev_level
#define netapp_get_PowerOffDelay        ncgi_get_power_off_delay
#define netapp_get_TVSystem             ncgi_get_tv_system
#define netapp_get_TVStatus             ncgi_get_tv_status
#define netapp_GetUIState               ncgi_get_ui_state
#define netapp_GetUIStateEx             ncgi_get_ui_state_by_id
#define netapp_GetDefMode               ncgi_get_def_ui_state
#define netapp_SendCameraState          ncgi_send_camera_state
#define netapp_UINotifyRoll             ncgi_notify_uiroll
#define netapp_UINotifyChanged          ncgi_notify_uichange
#define netapp_get_PhotoBurst           ncgi_get_photo_burst
#define netapp_get_Timelapse            ncgi_get_timelapse
#define netapp_get_Upsidedown           ncgi_get_up_side_down
#define netapp_get_HDR                  ncgi_get_hdr
#define netapp_get_LoopingVideo         ncgi_get_looping_video
#define netapp_get_SpotMeter            ncgi_get_spot_meter
#define netapp_get_Q_SHOT               ncgi_get_q_shot
#define netapp_get_StatusLights         ncgi_get_status_lights
#define netapp_get_SoundIndicator       ncgi_get_sound_indicator
#define netapp_get_PowerSaving          ncgi_get_power_saving
#define netapp_CaptureLock              netapp_cap_lock
#else //current mapping
    //#define ncgi_cfg_get netapp_cfg_get
    //#define ncam_update_audio_sampling_rate netapp_update_AudioSamplingRate
#endif
#endif  // __NETAPP_H__
