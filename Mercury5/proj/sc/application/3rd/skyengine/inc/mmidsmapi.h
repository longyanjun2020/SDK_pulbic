#ifndef __MMI_DSM_API__
#define __MMI_DSM_API__
#include "mrporting.h"


#define DSM_MAINMENU_SUPPORT_SIZE             (36)
#define FMGR_MAX_PATH_LEN                      (256)
#define DSM_HIDE_ICON					(0)
#define DSM_SHOW_ICON					(1)
#define DSM_BLINK_ICON					(2)

typedef void (*MCB)(void);
typedef int32 gdi_handle;
typedef int32 GDI_RESULT;
typedef struct
{
	char *name;
	MCB func;
}T_MITEM;

typedef struct
{
	int32 num;
	int32 index;
	MCB exitFunc;
	MCB bookFunc;
	MCB gameFunc;
	T_MITEM item[DSM_MAINMENU_SUPPORT_SIZE];
}T_MAINMENU;

typedef struct
{
	int8	t_stamp [6];  /*t_stamp[0]年t_stamp[1]月t_stamp[2]日t_stamp[3]时t_stamp[4]分t_stamp[5]秒*/
	int8 num[21];		/*发送方号码*/  
	int8 sms_status;				/*Read or Unread ?*/
	int8 sms_storage;
}T_DSM_MSG_INFO;

typedef struct
{
	uint8 totalNum;             //sim numbers, max to 4
	int8 curActive;            //index of simId[] witch actived
	uint16 dummy;              //no use, just for align
	int32 simId[4];              //mapping to plat sim socket id
	char* simNamePtr[4];   //sim卡名字,unicode
	uint16 simNameLen[4]; //名字长度
}T_DSM_DUALSIM_SET;

typedef struct
{
	char *pNum;
	char *pContent;
}T_PLAT_SENDSMS_REQ;

typedef struct
{
    uint8 authentication_type;
    uint8 user_name[32];
    uint8 password[32];
    uint8 dns[4];
    uint8 apn[100];
}T_DSM_DATA_ACCOUNT;

typedef struct
{
	int32 handle;
	int32 w;
	int32 h;
	char *buffer;
}T_LAYER_INFO;

typedef struct
{
	int32 setType;
	U8 *filename;
}T_SET_IDLE_PAPER_REQ;


typedef struct
{
	uint32 preview_x;
	uint32 preview_y;
	uint32 preview_w;
	uint32 preview_h;
	uint32 img_w;
	uint32 img_h;
	uint32 img_qt;
}T_DSM_LAUNCH_CAMERA_REQ;

typedef struct
{
	T_DSM_LAUNCH_CAMERA_REQ pre_req;
	gdi_handle osd_layer;
	gdi_handle preview_layer;
	gdi_handle base_layer;
	void *osd_layer_buffer;
	void *pImg;
	int32 ImgSize;
	int32 state;
	int32 last_error;
	int32 camera_handler; /*照相机句柄*/
	int32 continue_capture;
	int16 zoom_max;
	int16 zoom_index;
}T_DSM_CAMERA_REQ;

typedef struct 
{
	char *src;
	int32 src_len;
	int32 src_type;
	int32 ox;
	int32 oy;
	int32 w;
	int32 h;
}T_DRAW_DIRECT_REQ;

typedef struct
{
	char *src;
	int32 src_len;
	int32 src_type;
	int32 format;
}T_DSM_VOICE_REC_REQ;

typedef struct
{
    int32 menu;
    char *text;
    int32 index;
    int32 selected;
}T_LISTBOXITEM;

typedef struct
{
    char *title;
    int16 itemNum;
    int16 listType;
}T_LISTBOXWIN;

typedef struct
{
	int32 flag;
	char *pNum;
	char *pContent;
}T_SEND_SMS,T_SAVE_SMS;

typedef struct
{
      char *addr;
      char *content;
}T_DSM_MMS;

typedef struct 
{	
	int32 dft_list;
	char  list_path[FMGR_MAX_PATH_LEN];
}MR_T_FMGR_REQ;

typedef struct 
{
	int32 fmgrAction;
	char dir[256];
}mr_fmgrAction;

typedef struct
{
	uint32 total;
	uint32 tUnit;
	uint32 account;
	uint32 unit;
}T_DSM_DISK_INFO;

typedef enum
{
    MR_MOTION_SENSITIVE_LOW,
    MR_MOTION_SENSITIVE_NORMAL,
    MR_MOTION_SENSITIVE_HIGH,
    MR_MOTION_SENSITIVE_MAX
} MR_MOTION_SENSITIVE_ENUM;

enum
{
	MR_MOTION_EVENT_SHAKE,
	MR_MOTION_EVENT_TILT
};

typedef struct
{
	int32 x;
	int32 y;
	int32 z;
}T_MOTION_ACC;

enum    //for A76   longchaofeng
{
    
    MR_START_QQ ,
    MR_START_COOKIE
};

int32 bgPlayClose(int32 code ,uint8 *input,int32 input_len);
int32 bgPlayStop(int32 code ,uint8 *input,int32 input_len);
int32 bgPlayPlay(int32 code ,uint8 *input,int32 input_len);
int32 bgPlayOpen(int32 code ,uint8 *input,int32 input_len);
void wap_dsm_dual_sim_restore_info(void);
void wap_dsm_dual_sim_backup_info(int curr_sim);

int32 dsm_get_zoom_max(void);
int32 dsm_init_camera(void);
int32 dsm_pause_camera(void);
int32 dsm_zoom_in(void);
int32 dsm_zoom_out(void);
int32 dsm_destory_camera(int32 param);
int32 dsm_resume_camera_ex(void);

int32 dsmGetCurLang(void);
int32 mrp_backstage_stopPic(void);
void dsm_goto_base_win(void);
void dsm_set_endkey_Func(int32 param);
int32 mr_check_connect(int32 param);
int32 dsm_check_screen_type(void);
int32 dsm_check_msdc_status(void);
int32 dsm_weather_exit(void);
int32 dsm_set_theme(int32 id,char *path);
int32 dsm_set_motion_param(uint8*input);
int32 dsm_motion_poweroff(void);
int32 dsm_motion_poweron(void);
int32 dsm_get_mainmenu_info(uint8**output,int32 *output_len,MR_PLAT_EX_CB *cb);
int32 dsm_create_layer(int32 x,int32 y,int32 w,int32 h,uint8*ptr,int32 len);
int32 dsm_get_base_layer(void);
int32 dsm_get_active_layer_info(T_LAYER_INFO *layer);
void dsm_set_blt_layer(int32 h1,int32 h2,int32 h3,int32 h4);
void dsm_layer_flatten(int32 h1,int32 h2,int32 h3,int32 h4);
int32 dsm_get_sms_info(T_DSM_GET_SMS_INFO_REQ *pReq);
int32 dsm_delete_sms(T_DSM_DELETE_SMS_REQ *pReq);
int32 dsm_read_sms(T_DSM_GET_SMS_INFO_REQ *pReq);
void dsm_get_net_id(uint8**output,int32 *output_len);
int32 dsm_set_wallpaper(T_SET_IDLE_PAPER_REQ *req);
int32 dsm_get_preview_data(T_LAYER_INFO *layer);
int32 dsm_create_camera(T_DSM_LAUNCH_CAMERA_REQ *pReq,int32 *handler,int32* osd_buffer);
int32 dsm_capture(uint8 flag,int32 *size,int32 *ptr);
int32 mrp_backstage_start(mr_backstage_st *pBackStag);
int32 mrp_backstage_showPic(mr_pic_req* pPicReq);
int32 dsm_get_applist_title(uint8**output,int32* output_len);
int32 mr_bind(mr_bind_st *d_bind);
int32 dsm_get_nes_dir(uint8**output,int32* output_len);
int32 dsm_get_font_info(void);
int32 dsm_get_base_layer_buffer(uint8**output,int32 *output_len);
int32 dsm_set_ring(T_DSM_RING_SET *ringSet);
void dsm_set_bgplay_vol(void);
int32 dsm_draw_anim_direct(T_DRAW_DIRECT_REQ* req,gdi_handle* handle);
int32 dsm_draw_Img_direct(T_DRAW_DIRECT_REQ* req);
int32 dsm_image_draw(int32 x,int32 y,uint8*ptr);
int32 dsm_anima_draw(int32 x,int32 y,uint8*ptr);
U16 dsmGetImgType(char *filename,char *pbuf,int32 len);
int32 dsm_image_png_get_dimension(U8 *png_src, U32 size, S32 *width, S32 *height);
int32 dsmFreeGifMem(int32 index);
int32 findSlotByID(int32 id);
int32 dsmGifDecode(T_DSM_IMG_DECODE *pDecInfo,uint8**output,int32 *output_len);
int32 dsm_get_phb_status(void);
int32 dsm_theme_restore(void);
int32 dsm_get_active_theme_id(void);
void dsm_draw_mainmenu_bg(void);
void dsm_get_sc_req(void);
int32 dsm_get_sms_status(void);
int32 dsm_get_sms_count(int32 param);
void dsm_get_sms_memory_size(void);
int32 dsm_set_lcd_rotate(int32 param);
int32 dsm_get_cur_scene(void);
int32 dsm_voice_record_req(T_DSM_VOICE_REC_REQ *req);
int32 dsm_voice_record_pause(void);
int32 dsm_voice_record_resume(void);
int32 dsm_voice_record_stop(void);
int32 dsmSetActiveSim(int32 simId);
void dsm_initBSID(void);
void dsm_unInitBSID(void);
int32 dsm_unInitSignal(void);
int32 dsm_InitSignal(void);
int32 dsmSetDataAccount(T_DSM_DATA_ACCOUNT *req);
int32 dsmSendSMSPlatUI(T_PLAT_SENDSMS_REQ *req);
int32 dsmGetCellInfo(void);
int32 dsmExtMsg(T_SEND_SMS *pSMS);
int32 dsm_getSignalLevel(uint8**output,int32 *output_len);
int32 dsmGetFreeSpace(uint8 *input,int32 input_len,T_DSM_DISK_INFO *spaceInfo);
int32 mr_menuCreateEx(const char * title, int16 num,int16 listtype);
int32 mr_menuSetItemEx(int32 menu, const char *text, int32 index,int32 select);
int32 dsmSwitchPath(uint8* input, int32 input_len, uint8** output, int32* output_len);
int32 dsm_send_mms(T_DSM_MMS *pMMS);
int32 dsmGetDataAccount(void);
void *dsm_malloc_int_mem(int32 size);
void dsm_free_int_mem(void *ptr);
void mr_getWeatherInfo(uint8* input);
void mr_getWeatherDstpInfo(uint8* input);
void mr_WeatherScreenRelease(void);
int32  EntryWeatherScreen(void );
void dsm_LCD_Display(void *adrs, uint16 w, uint16 h);
int32 dsmCheckBrowerExit(void);
void mr_fmgr_filter_fmgr(void);
void mr_fmgr_filter_set(int32 fmgr_type);
void mr_set_fmgr_req(MR_T_FMGR_REQ *fmgr_req);
U16 dsmGetImgType(char *filename,char *pbuf,int32 len);
void mmi_dsm_entry_fmgr_screen(void);
void mr_fmgr_exit(void);
GDI_RESULT dsmJpgDecodeReq(
						S32 ox, S32 oy, 
						S32 resized_width, S32 resized_height, 
						S32 output_clipx1, S32 output_clipy1, 
						S32 output_clipx2, S32 output_clipy2,
						U8 *src,U32 size,U8 is_file,U8 is_resized);
 GDI_RESULT dsmPngDecodeReq(
            S32 ox,
            S32 oy,
            S32 resized_width,
            S32 resized_height,
            U8 *src,
            U32 size,
            U8 *dest,
 	     U32 dest_size,
	     U32 dest_width,
	     U32 dest_height,
            U8 is_file,
            U8 is_blocking,
            void (*callback) (GDI_RESULT result));
 
int32 mr_set_nes_joypad_key(uint8**  output, int32* output_len);
int32 mr_start_nes_game(void);
int32 mr_exit_nes_game(void);
int32 dsmIsSlaveSimSelected(void);
int32 dsmInit(void);
int32 dsm_motion_stop_listen(void);
int32 dsm_motion_power_on(void);
int32 dsm_motion_poweroff(void);
int32 dsm_motion_listen_shake(int32 param);
int32 dsm_motion_listen_tilt(int32 param);
int32 dsm_motion_get_max_acc(void);
int32 mr_check_wifi_support(void);
int32  mr_set_wifi_switch(int32 s);

extern char *GetDsmWorkPath(void);
extern char* GetDsmWorkDrv(void);
extern void dsm_set_vol(int32 vol);
extern int32 mrp_backstage_stop(void);
extern char* get_filename(char * outputbuf,const char *filename);
extern char *ConvertString(char * str);

extern int32 wrapperKeyEvent(int16 ktype ,int32 param1,int32 param2);
extern int32 DsmGameEx(void);
extern int32 DsmQQ(void);
extern U8* getLcdBuffer(void);
extern void dsmSetLaunchDir(char* drv,char *path);

extern void mythroad_suspend(void);
extern void mythroad_resume(void);
int32 mr_suspendSGLDraw(void);
int32 mr_resumeSGLDraw(void);


int32 mrp_settings_getNetworkProfileReq(void);
int32 mrp_settings_setNetworkProfile(T_DSM_DATA_ACCOUNT* pDataAccount);
int32 mrp_settings_showNetworkProfileUI(void);

#endif


