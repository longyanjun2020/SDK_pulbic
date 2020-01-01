
#if defined(__ZYUE_ENGINE__)
#ifndef PBK_OS_RES_H
#define PBK_OS_RES_H

#include "pbk_config.h"

/* 本文件主要用于适配平台的各种资源管理 */
///////////////////////////////////////////////////////////////////////
typedef enum __PBK_SCRN_ID
{
	PBK_SCREEN_ID_APP = 100,
	PBK_SCREEN_ID_APP_TIP,
	PBK_SCREEN_ID_SYSCONTRL
}PBK_SCRN_ID;

typedef struct __PBK_OS_TIMER_ITEM
{
    c_uint32 timer_id;
    void       (*user_callback)(void* data);
    void      *user_data;
}PBK_OS_TIMER_ITEM;

typedef enum __PBK_OS_TIMER_ID
{
	PBK_TIMER_ID_MAINLOOP = 0,
	PBK_TIMER_ID_UTILITY_1,
	PBK_TIMER_ID_UTILITY_2,
	PBK_TIMER_ID_UTILITY_TASK_1,
	PBK_TIMER_ID_UTILITY_TASK_2,
	PBK_TIMER_ID_MAX
}PBK_OS_TIMER_ID;

typedef struct __PBK_OS_TIMER
{
    PBK_OS_TIMER_ITEM timer[PBK_TIMER_ID_MAX];
    c_uint32 count;
}PBK_OS_TIMER;


///////////////////////////////////////////////////////////////////////
typedef enum __PBK_OS_DISK_VOL
{
	PBK_OS_DISK_VOL_DISK_V_FLASH = 0,
	PBK_OS_DISK_VOL_EXT_SD_1,
	PBK_OS_DISK_VOL_EXT_SD_2,
	PBK_OS_DISK_VOL_MAX
}PBK_OS_DISK_VOL;

typedef struct __PBK_OS_FS
{
    c_uint8* disk_vol[PBK_OS_DISK_VOL_MAX];
    c_uint32 count;
}PBK_OS_FS;
///////////////////////////////////////////////////////////////////////
typedef struct __PBK_OS_GDI
{
    c_uint32 canvas;
    c_uint16 width;
    c_uint16 height;
}PBK_OS_GDI;
///////////////////////////////////////////////////////////////////////
typedef struct __PBK_OS_FONT
{
    c_uint32 font_attr;
}PBK_OS_FONT;
///////////////////////////////////////////////////////////////////////
#define PBK_OS_NET_MAX_NUM   4
typedef struct __PBK_OS_NET_ITEM
{
    c_uint32 net_handler;/* 指向 PBK_OS_NET */
    c_uint32 w_param;//保留参数，供扩展使用
    c_uint32 l_param;//保留参数，供扩展使用
}PBK_OS_NET_ITEM;

typedef struct __PBK_OS_NET
{
    PBK_OS_NET_ITEM net_data[PBK_OS_NET_MAX_NUM];
    c_uint32 select_sim;
    c_uint32 select_type;
    c_uint32 count;
}PBK_OS_NET;
///////////////////////////////////////////////////////////////////////
typedef struct __PBK_OS_MEM
{
    c_uint32 mem;
    c_uint32 free_space;
}PBK_OS_MEM;
///////////////////////////////////////////////////////////////////////

#define PBK_OS_SIMNUM_MAX 4 /* 目前最多支持4 张卡 */
typedef struct __PBK_OS_SIM_ITEM
{
    c_uint8 sms_sc_addr[VEN_MSG_SMS_SERVICE_CENTER_MAX_CHAR + 1];
    c_uint8 iccid[(ICCID_LEN + 1)];
    c_uint8 imsi[32];
}PBK_OS_SIM_ITEM;

typedef struct __PBK_OS_SIM
{
    PBK_OS_SIM_ITEM sim_info[PBK_OS_SIMNUM_MAX];
    c_int32 count;
}PBK_OS_SIM;


typedef struct __PBK_OS_OTHER_DEV
{
    c_uint8 imei[32];
}PBK_OS_OTHER_DEV;

typedef struct __PBK_OS_RES
{
    PBK_OS_TIMER os_timer_res;
    PBK_OS_FS     os_fs_res;
    PBK_OS_GDI    os_gdi_res;
    PBK_OS_FONT os_font_res;
    PBK_OS_NET  os_net_res;
    PBK_OS_MEM os_mem_res;
    PBK_OS_SIM  os_sim_res;
    PBK_OS_OTHER_DEV os_other_dev_res;
}PBK_OS_RES;

/////////////////////////////////////////////////////////

c_uint32  pbk_os_timer_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_timer_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_timer_user_data_set(c_uint32 user_timer, void *user_data);
void*  pbk_os_timer_user_data_get(c_uint32 user_timer);
void pbk_os_timer_start(c_uint32 user_timer, c_uint32 interval, void (*user_callback)(void* data), void *user_data);
void pbk_os_timer_stop(c_uint32 user_timer);

c_uint32  pbk_os_fs_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_fs_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_uint8* pbk_os_fs_disk_vol_get(c_uint32 disk_vol_type);

c_uint32  pbk_os_gdi_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_gdi_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_gdi_scrn_width_get(void);
c_uint32  pbk_os_gdi_scrn_height_get(void);
c_uint32  pbk_os_gdi_canvas_handler_get(void);
c_uint8*  pbk_os_gdi_canvas_buffer_get(void);


c_uint32  pbk_os_font_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_font_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_font_attri_get(void);

c_uint32  pbk_os_net_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_net_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_int32    pbk_os_net_handler_add(c_uint32 net_handler);
void    pbk_os_net_handler_del(c_uint32 net_handler);
c_uint32  pbk_os_net_param_w_get(c_uint32 net_handler);
void  pbk_os_net_param_w_set(c_uint32 net_handler, c_uint32 w_param);
c_uint32  pbk_os_net_param_l_get(c_uint32 net_handler);
void  pbk_os_net_param_l_set(c_uint32 net_handler, c_uint32 l_param);
c_uint32  pbk_os_net_select_sim_get(void);
void  pbk_os_net_select_sim_set(c_uint32 select_sim);
c_uint32  pbk_os_net_select_type_get(void);
void  pbk_os_net_select_type_set(c_uint32 select_type);

c_uint32  pbk_os_mem_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_mem_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_mem_free_space_get(void);

c_uint32  pbk_os_sim_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_sim_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_uint8*  pbk_os_sim_iccid_get(c_int32 sim_index);
c_uint8*  pbk_os_sim_smsc_get(c_int32 sim_index);
c_uint8*  pbk_os_sim_imsi_get(c_int32 sim_index);

c_uint32  pbk_os_other_dev_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_other_dev_res_deinit(c_uint32 w_param, c_uint32 l_param);
c_uint8*  pbk_os_other_dev_phone_imei_get(void);

c_uint32  pbk_os_res_init(c_uint32 w_param, c_uint32 l_param);
c_uint32  pbk_os_res_deinit(c_uint32 w_param, c_uint32 l_param);

#endif
#endif

