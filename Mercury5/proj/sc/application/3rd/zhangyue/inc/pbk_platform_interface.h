#if defined(__ZYUE_ENGINE__)
#ifndef PBK_PLATFORM_INTERFACE_H
#define PBK_PLATFORM_INTERFACE_H

#include "pbk_platform_define.h"
//只包含接口声明

/***********************************************
//platform ex api 
//平台相关扩展
************************************************/
#ifdef PBK_PLATFORM_V6000
//注意str的数据会发生改变，部分空格会转换为字符结束符号'0'
c_uint32 pbk_name_value_parse(char* str, c_uint32 str_length, PBK_NAME_VALUE* pair_array, c_uint32 pair_num);
char* pbk_name_value_get_value(PBK_NAME_VALUE* pair_array, c_uint32 pair_num, char* name);
//将字符串按照制定的字符拆分到给定的数组
c_uint32 pbk_name_value_split(char* str, char c, char* array_addr, c_uint32 item_size, c_uint32 item_num);
c_int32 pbk_lz_decompress (c_uint8* src, c_int32 src_len, c_uint8* dst, c_int32* dst_len);
c_int32 pbk_app_update(c_wchar * filename, c_uint32 app_ver,c_uint32 is_run, char *arg, c_uint32 is_bg_update, PBK_APP_UPDATE_CALLBACK action_cb);
c_int32 pbk_sys_get_cpu_speed(void);

#endif

/***********************************************
//standard c 
//标准c库部分函数
************************************************/
#ifdef PBK_PLATFORM_V6000
#ifdef PBK_PLATFORM_LOAD
c_int32 atoi(const char* s);
c_int32 abs(c_int32 x);

c_int32 memcmp(const void* buf1, const void* buf2, c_uint32 count);
void* memcpy(void* dest, const void* src, c_uint32 count);
void* memmove(void* dest, const void* src, c_uint32 count);
void* memset(void* buffer, c_int32 c, c_uint32 count);

c_int32 strlen(char* s);
char* strcat(char* dest,char* src);
char* strncat(char* dest, const char* src, c_uint32 n);
char* strcpy(char* dest,char* src);
char* strncpy(char* dest, char* src, c_uint32 n);
char* strchr(char* s, char c);
char* strrchr(const char* s, char c);
char* strstr(char* s1, const char* s2);

c_int32 strcmp(char* s1, char*  s2);
c_int32 stricmp(char* s1, char*  s2);
c_int32 strncmp(char* s1, char*  s2,  c_uint32 n);
c_int32 strnicmp(char* s1, char*  s2, c_uint32 n);

char* strlwr(char* s);
char* strupr(char* s);

char* strpbrk(char* s1, char* s2);
char* strtok(char* s, char* delim);
char* strrev(char* s);

c_int32 isalnum(c_int32 c);
c_int32 isalpha(c_int32 c);
c_int32 iscntrl(c_int32 c);
c_int32 isdigit(c_int32 c);
c_int32 islower(c_int32 c);
c_int32 isascii(c_int32 c);
c_int32 isspace(c_int32 c);
c_int32 isupper(c_int32 c);
c_int32 isxdigit(c_int32 c);
c_int32 tolower(c_int32 c);
c_int32 toupper(c_int32 c);

c_int32 sprintf(char* buf, const char* fmt, ...);
c_int32 vsprintf(char* where, const char* fmt, va_list varg);
c_int32 vsnprintf(char *string,c_uint32 size, const char *fmt, va_list arglist);

c_uint32 strtoul(const char* nptr, char** endptr, c_int32 base);
c_uint32 strspn(const char* s1, const char* s2);

c_int32 srand(c_int32 seed);
c_int32 rand(void);
#endif

#if 0//(PBK_MTK_VERSION >= PBK_MTK_10A)
char* pbk_strtok(char* s, char* delim);
#endif
char* pbk_strlwr(char* s);
char* pbk_strupr(char* s);
char* pbk_strrev(char* s);
c_int32 pbk_isalnum(c_int32 c);	//
c_int32 pbk_isalpha(c_int32 c);
c_int32 pbk_iscntrl(c_int32 c);
c_int32 pbk_isdigit(c_int32 c);
c_int32 pbk_islower(c_int32 c);
c_int32 pbk_isascii(c_int32 c);
c_int32 pbk_isspace(c_int32 c);
c_int32 pbk_isupper(c_int32 c);
c_int32 pbk_isxdigit(c_int32 c);

c_int32 pbk_tolower(c_int32 c);	// 
c_int32 pbk_toupper(c_int32 c);
#endif


/***********************************************
//encoding unicode
//字符编码转换和unicode字符串操作
************************************************/
#ifdef PBK_PLATFORM_V6000
c_uint32 pbk_gb2312_to_unicode(c_uint8* gb_src, c_uint8* unicode_buf, c_uint32 unicode_buf_size);
c_uint32 pbk_unicode_to_gb2312(c_uint8* unicode_src, c_uint8* gb_buf, c_uint32 gb_buf_size);
c_uint32 pbk_utf8_to_unicode(c_uint8* utf8_src, c_uint8* unicode_buf, c_uint32 unicode_buf_size);
c_uint32 pbk_unicode_to_utf8(c_uint8* unicode_src, c_uint8* utf8_buf, c_uint32 utf8_buf_size);
c_uint32 pbk_utf8_to_gb2312(c_uint8* utf8_src, c_uint8* gb_buf, c_uint32 gb_buf_size);
c_uint32 pbk_gb2312_to_utf8(c_uint8* gb_src, c_uint8* utf8_buf, c_uint32 utf8_buf_size);

c_int32 pbk_unicode_strlen(const c_uint8* str);
c_uint8* pbk_unicode_strcpy(c_uint8* dest, const c_uint8* src);
c_uint8* pbk_unicode_strncpy(c_uint8* dest, const c_uint8* src, c_uint32 size);
c_int32 pbk_unicode_strcmp(const c_uint8* str1, const c_uint8* str2);
c_int32 pbk_unicode_stricmp(const c_uint8* str1, const c_uint8* str2);
c_int32 pbk_unicode_strncmp(const c_uint8* str1, const c_uint8* str2, c_uint32 size);
c_int32 pbk_unicode_strnicmp(const c_uint8* str1, const c_uint8* str2, c_uint32 size);
c_uint8* pbk_unicode_strcat(c_uint8* dest, const c_uint8* src);
c_uint8* pbk_unicode_strncat(c_uint8* dest, const c_uint8* src, c_uint32 size);
c_uint8* pbk_unicode_ascii_strcat(c_uint8* unicode_dest, const c_uint8* ascii_src);
c_uint8* pbk_unicode_ascii_strncat(c_uint8* unicode_dest, const c_uint8* ascii_src, c_uint32 size);
c_uint8* pbk_unicode_strchr(const c_uint8* src, c_uint16 c);
c_uint8* pbk_unicode_strrchr(const c_uint8* src, c_uint16 c);
c_uint8* pbk_unicode_strstr(const c_uint8* str1, const c_uint8* str2);
c_uint8* pbk_unicode_strupr(c_uint8* str);
c_uint8* pbk_unicode_strlwr(c_uint8* str);

c_int32 pbk_unicode_sprintf(c_uint8* unicode_buf, char* fmt, ...); //最多255ascii字符,unicode_buf长度需要为ascii可能长度的2倍
c_int32 pbk_unicode_vsprintf(c_uint8* unicode_buf, const char* fmt, va_list varg);
#endif


/***********************************************
//memory
//内存
************************************************/
#ifdef PBK_PLATFORM_V6000
void* pbk_mem_malloc(c_uint32 size);
void pbk_mem_free(void* p);
void* pbk_mem_pool_malloc(c_uint32 size);
void pbk_mem_pool_free(void* p, c_uint32 size);
void pbk_mem_pool_release(void);
c_uint32 pbk_mem_get_free_size(void);
void* pbk_mem_malloc_tmp(c_uint32 size);
void pbk_mem_free_tmp(void* p);
#endif


/***********************************************
//file
//文件系统
************************************************/
#ifdef PBK_PLATFORM_V6000
c_uint32 pbk_file_open(const c_wchar* file_name, const char* mode);
c_int32 pbk_file_close(c_uint32 file_id);
c_int32 pbk_file_seek(c_uint32 file_id, c_int32 offset, c_int32 where);
c_int32 pbk_file_tell(c_uint32 file_id);
c_int32 pbk_file_size(c_uint32 file_id);
c_int32 pbk_file_read(c_uint32 file_id, void* buf, c_uint32 read_size);
c_int32 pbk_file_write(c_uint32 file_id, void* buf, c_uint32 write_size);
c_int32 pbk_file_delete(const c_wchar* file_name);
c_uint32 pbk_file_is_exist(const c_wchar* file_name);
c_int32 pbk_file_rename(const c_wchar* src_name, const c_wchar* dest_name);
c_uint32 pbk_file_find_first(const c_wchar* find_str, PBK_FILE_FIND_INFO* find_info);
c_int32 pbk_file_find_next(c_uint32 file_id, PBK_FILE_FIND_INFO* find_info);
c_int32 pbk_file_find_end(c_uint32 file_id);
c_int32 pbk_file_create_dir(const c_wchar* dir_path);
c_int32 pbk_file_delete_dir(const c_wchar* dir_path);
c_int32 pbk_file_delete_all_file(const c_wchar* dir_path, const c_wchar* match_mode);

void  pbk_file_get_disk_info(PBK_DISK_INFO* disk_info);
c_uint32 pbk_file_get_disk_free_space(char disk_letter);
c_uint32 pbk_file_get_disk_total_space(char disk_letter);
c_int32 pbk_file_load_data_crc(c_wchar* file_name, void* buf, c_uint32 buf_size);
c_int32 pbk_file_save_data_crc(c_wchar* file_name, void* buf, c_uint32 buf_size);
#endif

/***********************************************
//timer
//定时器
************************************************/
#ifdef PBK_PLATFORM_V6000
c_uint16 pbk_timer_create(void);
void pbk_timer_release(c_uint16 timer_id);
void pbk_timer_start(c_uint16 timer_id, c_uint32 delay, PBK_TIMER_CALLBACK callback_func, void* param);
void pbk_timer_stop(c_uint16 timer_id);
#endif

/***********************************************
//gui
//图形图像
************************************************/
#ifdef PBK_PLATFORM_V6000
void pbk_gui_init(void);
PBK_FONT_INFO* pbk_gui_get_font_info(void);
c_int32 pbk_font_defaultfon_load(c_int32 font_size, c_uint8* file_name);
c_uint32 pbk_get_color_from_rgb(c_uint32 b, c_uint32 g, c_uint32 r);
c_int32 pbk_gui_get_screen_width(void);
c_int32 pbk_gui_get_screen_height(void);
c_int32 pbk_gui_get_screen_depth(void);

//基础绘制
void pbk_gui_draw_point(c_int32 x, c_int32 y, c_uint32 c);
void pbk_gui_draw_line(c_int32 x1, c_int32 y1, c_int32 x2, c_int32 y2, c_uint32 c);
void pbk_gui_draw_rect(c_int32 x1, c_int32 y1, c_int32 x2, c_int32 y2, c_uint32 c);
void pbk_gui_draw_solid_rect(c_int32 x1, c_int32 y1, c_int32 x2, c_int32 y2, c_uint32 c);
void pbk_gui_draw_circle(c_int32 x, c_int32 y, c_int32 r, c_uint32 c);
void pbk_gui_draw_solid_circle(c_int32 x, c_int32 y, c_int32 r, c_uint32 c);
///void pbk_gui_draw_image(c_int32 x, c_int32 y, c_uint8* data, c_uint32 data_size, c_uint32 img_type);
void pbk_gui_draw_image(c_int32 x, c_int32 y, PBK_IMAGE *img);

void pbk_gui_draw_image_ex(c_int32 x, c_int32 y, c_uint8* data, c_uint32 data_size, c_uint32 img_type);
///void pbk_gui_draw_image_ex(c_int32 x, c_int32 y, PBK_IMAGE *img);
///void pbk_gui_draw_image_resize(c_int32 x, c_int32 y, c_int32 w, c_int32 h, c_uint8* data, c_uint32 data_size, c_uint32 img_type);
void pbk_gui_draw_image_resize(c_int32 x, c_int32 y, PBK_IMAGE *img, c_int32 w, c_int32 h);

void pbk_gui_image_get_size(c_uint8* data, c_uint32 size, c_uint32 img_type, c_int32* w, c_int32* h);
c_int32 pbk_gui_image_decode(PBK_IMAGE *img);
//c_int32 pbk_gui_image_decode_lz(PBK_IMAGE *img);
//拷贝位图的部分到当前图层
///void pbk_gui_bitmap_copy(c_int32 x1, c_int32 y1, PBK_BITMAP* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h);
//逐像素绘制，跳过当前图层透明色
///void pbk_gui_bitmap_copy_pixel(c_int32 x1, c_int32 y1, PBK_BITMAP* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h);
//alpha
///void pbk_gui_bitmap_copy_pixel_alpha(c_int32 x1, c_int32 y1, PBK_BITMAP* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h, c_int32 alpha);
//transform
///void pbk_gui_bitmap_copy_pixel_trans(c_int32 x1, c_int32 y1, PBK_BITMAP* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h, c_int32 trans_type);
void pbk_gui_draw_image_region(c_int32 x1, c_int32 y1, PBK_IMAGE* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h);
void pbk_gui_draw_image_transparent(c_int32 x1, c_int32 y1, PBK_IMAGE* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h);
void pbk_gui_draw_image_alpha(c_int32 x1, c_int32 y1, PBK_IMAGE* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h, c_int32 alpha);
void pbk_gui_draw_image_transform(c_int32 x1, c_int32 y1, PBK_IMAGE* bitmap, c_int32 x2, c_int32 y2, c_int32 w, c_int32 h, c_int32 trans_type);

//图层相关
void pbk_gui_update_screen(void);
void pbk_gui_update_screen_region(c_int32 x, c_int32 y, c_int32 w, c_int32 h);

PBK_GUI_LAYER* pbk_gui_layer_create(c_int32 w, c_int32 h);
void pbk_gui_layer_release(PBK_GUI_LAYER* layer);
void pbk_gui_layer_set_clip(c_int32 x1, c_int32 y1, c_int32 x2, c_int32 y2);
PBK_GUI_LAYER* pbk_gui_layer_get_default(void);
PBK_GUI_LAYER* pbk_gui_layer_get_curr(void);
void pbk_gui_layer_set_curr(PBK_GUI_LAYER* layer);
void pbk_gui_layer_clear(c_uint32 c);
void pbk_gui_layer_set_color(c_uint32 c);
void pbk_gui_layer_set_trans_color(c_uint32 c);

//字符
c_int32 pbk_gui_get_char_width(c_wchar c);
c_int32 pbk_gui_get_cn_word_width(void);
c_int32 pbk_gui_get_char_height(void);
c_int32 pbk_gui_get_string_width(c_wchar* s);
c_int32 pbk_gui_get_string_width_n(c_wchar* s, c_uint32 length);
c_int32 pbk_gui_get_string_height(c_wchar* s, c_uint32 s_length, c_int32 w, c_int32 row_space);
c_uint32 pbk_gui_get_wchar_num(c_wchar* s, c_int32 width);
void pbk_gui_draw_char(c_int32 x, c_int32 y, c_wchar c, c_uint32 font_color);
void pbk_gui_draw_string(c_int32 x, c_int32 y, c_wchar* s, c_uint32 font_color);
c_wchar* pbk_gui_draw_string_ex(c_int32 x, c_int32 y, c_int32 w, c_int32 h, c_int32 x_offset, c_int32 y_offset, c_wchar* s, c_uint32 font_color, c_uint8 is_line_wrap, c_int32 row_space, c_uint32 is_under_line, c_uint32 line_color);
c_wchar* pbk_gui_draw_string_ex2(c_int32 x, c_int32 y, c_int32 w, c_int32 h, c_int32 x_offset, c_int32 y_offset, c_wchar* s, c_uint32 font_color, c_uint8 is_line_wrap, c_int32 row_space, c_uint32 is_under_line, c_uint32 line_color);
c_int32 pbk_gui_draw_string_n(c_int32 x, c_int32 y, c_wchar* s, c_uint32 font_color, c_uint32 n);

//设置字体，重新计算ascii字符宽度，汉字宽度，汉字高度等
void pbk_gui_set_font(c_int32 font_type);

//字体加载
c_uint8* pbk_font_data_get(c_wchar wch);/*新增接口获取字模数据 */
c_int32 pbk_font_load(c_int32 font_size, c_uint8* file_name);
void pbk_font_release(void);
c_uint32 pbk_font_get_curr_type(void);

void pbk_gui_draw_alpha_rect(c_int32 x1, c_int32 y1, c_int32 x2, c_int32 y2, c_uint32 c, c_int32 alpha);
//gif动画绘制

//旋转

#endif

/***********************************************
//socket
//网络通讯
************************************************/
#ifdef PBK_PLATFORM_V6000
c_uint32 pbk_soc_htonl(c_uint32 a);
c_uint16 pbk_soc_htons(c_uint16 a);

c_int32 pbk_soc_create(PBK_SOC_EVENT_CALLBACK soc_event_callback, c_uint32 l_param);
c_int32 pbk_soc_setsockopt(c_int32 soc_id, c_uint32 option, c_uint8 *val, c_uint32 val_size);
c_int32 pbk_soc_connect(c_int32 soc_id, c_uint32 addr, c_uint16 port);
c_int32 pbk_soc_close(c_int32 soc_id);
c_int32 pbk_soc_recv(c_int32 soc_id, c_uint8 *buf, c_int32 len);
c_int32 pbk_soc_send(c_int32 soc_id, c_uint8 *buf, c_int32 len);
c_int32 pbk_soc_gethostbyname(const char* name, c_uint8* addr, PBK_SOC_GET_HOST_CALLBACK get_host_callback, c_uint32 soc_id);

//gprs帐号相关
void pbk_gprs_open(void);
void pbk_gprs_close(void);
c_int32 pbk_gprs_account_init(void);
void pbk_gprs_account_get_by_index(PBK_GPRS_ACCOUNT* account_data, c_int32 index);
c_uint32 pbk_gprs_account_count(void);
void pbk_gprs_account_set(PBK_GPRS_ACCOUNT* account_data, c_int32 index);

//http包装
PBK_HTTP_DATA* pbk_http_create_data(c_uint32 send_buf_size, c_uint32 recv_buf_size, PBK_HTTP_EVENT_CALLBACK event_callback);
void pbk_http_release_data(PBK_HTTP_DATA * http_data);
void pbk_http_set_data(PBK_HTTP_DATA * http_data, c_uint32 net_type, c_uint32 net_sim_index, c_uint32 timeout_timer_id);
c_int32 pbk_http_head_assemble(PBK_HTTP_DATA* http_data, PBK_HTTP_REQ_INFO* req_info);
c_int32 pbk_http_send_req(PBK_HTTP_DATA* http_data);
void pbk_http_cancel(PBK_HTTP_DATA* http_data);

c_uint32 pbk_http_urlcoding_utf8(char* dest_buf, c_uint32 dest_buf_size, char* utf_buf);

#endif

/***********************************************
//device
//设备信息
************************************************/
#ifdef PBK_PLATFORM_V6000
c_uint32 pbk_sys_get_lcd_type(void);
c_uint32 pbk_sys_get_net_type(void);
void pbk_sys_set_net_type(c_uint32 net_type);
c_uint32 pbk_sys_get_active_sim(void);
void pbk_sys_set_active_sim(c_uint32 sim_index); //0:sim1 1:sim2
c_uint32 pbk_sys_get_sim_1_type(void);
c_uint32 pbk_sys_get_sim_2_type(void);
c_uint32 pbk_sys_get_sim_type(void);
c_uint32 pbk_sys_is_sim1_valid(void);
c_uint32 pbk_sys_is_sim2_valid(void);
c_uint32 pbk_sys_is_sim_valid(void);

char* pbk_sys_get_wap_ua(void);

char* pbk_sys_get_imei(void);
char* pbk_sys_get_imsi(c_uint32 sim_index);
char* pbk_sys_get_smsc(c_int32 sim_index); 
char* pbk_sys_get_iccid(c_int32 sim_index); 

c_uint32 pbk_sys_get_keyboard_type(void); //PBK_KEYBOARD_TYPE

char* pbk_sys_get_hw_info(void);
char* pbk_sys_get_release_verno(void);
char* pbk_sys_get_bb_chip(void);
char* pbk_sys_get_hw_ver(void);
char* pbk_sys_get_release_branch(void);
char* pbk_sys_get_build_date_time(void);
char* pbk_sys_get_release_build_no(void);

c_uint32 pbk_sys_get_curr_language(void); //PBK_LANGUAGE_TYPE 获取当前语言
c_int32 pbk_sys_get_str_encode_type(char* ss, c_int32 l);

c_int32 pbk_sys_get_func_value(c_int32  func_id);
void pbk_sys_set_func_value(c_int32 func_id, c_int32 value);

//c_uint32 pbk_is_touch_support(void);
//c_uint32 pbk_is_keyboard_support(void);
//c_uint32 pbk_is_dual_sim_support(void);
c_uint32 pbk_is_font_load_support(void);
//c_uint32 pbk_is_sensor_support(void);
//c_uint32 pbk_is_fm_support(void);
//c_uint32 pbk_is_tv_support(void);
//c_uint32 pbk_is_cmmb_support(void);
//c_uint32 pbk_is_gps_support(void);
c_uint32 pbk_is_device_support(c_uint32 device_id);

c_uint32 pbk_is_third_app_run(c_uint32 third_app_id);
c_uint32 pbk_is_usb_is_in_mass(void);
c_uint32 pbk_is_usb_webcam_active(void);
#endif

/***********************************************
//system
//系统相关功能调用
************************************************/
#ifdef PBK_PLATFORM_V6000
void pbk_log(const char* fmt, ...);//PBK_TRACE
void pbk_vlog(char* buf);
c_int32 pbk_zlib_decompress(c_uint8* src, c_uint32 src_length, c_uint8* dest, c_uint32 dest_length);
c_int32 pbk_zlib_compress(c_uint8* src, c_uint32 src_length, c_uint8* dest, c_uint32 dest_length);
c_uint16 pbk_sys_get_crc16_value(const c_uint8* data, c_uint32 len);
c_uint32 pbk_sys_get_str_hash(char* s); //pjw
void pbk_sys_get_datetime(PBK_TIME* t);
void pbk_sys_set_datetime(PBK_TIME t);

c_uint32 pbk_sys_get_tickcount(void);

//系统界面
c_int32 pbk_sys_open_input(c_uint8* title, c_uint8* buf, c_uint32 max_len, c_uint32 input_type, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_sms_editor(c_uint8* unicode_content, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_textviewer(c_uint8* title, c_uint8* text, c_uint32 text_size, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_popup(c_uint8* buf, c_int32 type, c_uint32 duration, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_confirm(c_uint8* buf, c_int32 type, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_phone_book(c_uint8* title, c_uint8* name_buf, c_uint32 namebuf_size, c_uint8* num_buf, c_uint32 numbuf_size, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_file_manager(c_uint8* title, c_uint8* filename_buf, c_uint32 buf_size, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_list(c_uint8* title, c_uint8** items, c_int32 num, c_int32 select, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_open_func(c_uint32 func_id, void* data, PBK_SYS_CALLBACK cb, void* cb_data);

c_int32 pbk_sys_send_sms(char* sms_content, char* sms_addr, PBK_SYS_CALLBACK cb, void* cb_data);
c_int32 pbk_sys_make_call(char* phone_num);
c_int32 pbk_sys_open_wap(char* url);

void pbk_sys_enable_keyboard_tone(void);
void pbk_sys_disable_keyboard_tone(void);

void pbk_sys_turn_on_backlight(c_int32 time_enum);
void pbk_sys_turn_off_backlight(void);

c_int32 pbk_sys_set_wallpaper(c_wchar* file_name);
c_int32 pbk_sys_set_phonetone(c_wchar* file_name,c_int32 tone_type);

c_int32 pbk_sys_data_encode(c_uint8* data, c_uint32 data_len, c_uint32 key);
c_int32 pbk_sys_data_decode(c_uint8* data, c_uint32 data_len, c_uint32 key);

//遍历通讯录
//???
#endif


/***********************************************
//media
//多媒体
************************************************/
#ifdef PBK_PLATFORM_V6000
void pbk_vibrator_start(c_int32 ms);
void pbk_vibrator_stop(void);

c_int32 pbk_audio_play(c_wchar* file_name, c_int32 playonce);
c_int32 pbk_audio_stop(void);

c_int32 pbk_audio_play_buf(c_uint8* audio_data, c_int32 data_size, c_int32 format, c_int32 playonce);
c_int32 pbk_audio_stop_buf(void);

c_int32 pbk_audio_pause(void);
c_int32 pbk_audio_resume(void);

void pbk_audio_set_volume(c_int32 volume);
void pbk_audio_set_path(c_int32 path);
c_int32 pbk_audio_get_progress_time(void);
c_int32 pbk_audio_set_progress_time(c_int32 progress_time);
c_int32 pbk_audio_get_duration(c_wchar* file_name);
c_int32 pbk_audio_get_duration_buf(c_uint8* audio_data, c_int32 data_size, c_int32 format);

c_int32 pbk_sensor_init(void);
c_int32 pbk_sensor_power_up(void);
c_int32 pbk_sensor_power_down(void);
c_int32 pbk_sensor_get_xyz(c_int32* x_adc, c_int32* y_adc, c_int32* z_adc);
c_int32 pbk_sensor_open(c_int32  open_mode, c_int32  value_range);
c_int32 pbk_sensor_regist_events(c_int32 event);
c_int32 pbk_sensor_start(void);
#endif

/***********************************************
//zpp
//加载运行
************************************************/
#ifdef PBK_PLATFORM_V6000
c_int32 pbk_app_run(c_wchar* app_file, char* arg); 
c_int32 pbk_app_run_from_buf(const c_uint8 * buf, char* arg);
void pbk_app_exit(void); 
void pbk_app_abort(c_uint32 app_id);
void pbk_app_exit_and_run(c_wchar* app_file, char* arg);
void pbk_app_run_change(c_uint32 app_id);
c_uint32 pbk_app_register(PBK_APP_MSG_PROCESS_FUNC msg_process); 
void pbk_app_post_msg(c_uint32 msg_id, c_uint32 recv_app_id, c_uint32 l_param, c_uint32 w_param); 
c_uint32 pbk_app_send_msg(c_uint32 msg_id, c_uint32 recv_app_id, c_uint32 l_param, c_uint32 w_param); 
c_uint32 pbk_app_get_current_app_id(void);
c_uint32 pbk_app_get_id_by_name(c_wchar* app_name);
c_int32 pbk_app_get_app_info(c_wchar* app_file, PBK_APP_INFO* app_info);

c_uint32 pbk_app_get_c_id(void);
c_uint32 pbk_app_get_c_id_2(void);
char* pbk_app_get_c_str(void);
c_uint32 pbk_app_get_platform_version(void);		//平台版本号
c_uint32 pbk_app_timer_get_interval(void);
void pbk_app_timer_set_interval(c_uint32 timer_interval);
c_uint32 pbk_app_is_run(c_wchar* app_name);

//资源数据获取
c_uint32 pbk_app_get_img_size(c_uint32 img_id); //获取资源大小
PBK_IMAGE* pbk_app_get_img(c_uint32 img_id); //获取具体信息
c_uint32 pbk_app_free_img(PBK_IMAGE* img);
c_uint8* pbk_app_get_str(c_uint32 str_id);
c_uint8* pbk_app_get_res_item(c_uint32 id, c_uint32* res_length);
c_uint32 pbk_app_free_res_item(c_uint8 *dat);
c_uint32 pbk_app_get_used_mem_size(void);
#endif


/***********************************************
//fee
//资费
************************************************/
#ifdef PBK_PLATFORM_V6000
c_int32 pbk_fee_start(char* fee_info);
void pbk_fee_abort(c_uint32 result);
void pbk_sms_filter_add(void* filter_item);
void pbk_sms_confirm_add(void* confirm_item);
void pbk_sms_set_filter_check(c_uint32 is_filter_check);
c_uint32 pbk_sms_filter_check(char* addr, c_uint8* content, void* process_result);
#endif

#define pbk_htonl(l)	((((l) & 0xff000000) >> 24) | \
						(((l) & 0x00ff0000) >>  8) | \
						(((l) & 0x0000ff00) <<  8) | \
						(((l) & 0x000000ff) << 24))
#define pbk_ntohl		pbk_htonl
#define pbk_htons(s)	((((s) >> 8) & 0xff) | \
						(((s) << 8) & 0xff00))
#define pbk_ntohs		pbk_htons


/***********************************************
//6100新增
************************************************/
#ifdef PBK_PLATFORM_V6100
char* pbk_app_get_uid(void);
char* pbk_app_get_phone_number(c_uint32 index);
void pbk_app_set_phone_number(c_uint32 index, char* number);
void pbk_sms_check_data_clear(void);
void* pbk_sms_get_check_data(void);
char* pbk_net_req_get_url_param(char* url);
void pbk_app_upload_info_add(char* info);
void pbk_app_upload_info_upload(void);
c_uint32 pbk_app_get_parent_app_id(void);
void pbk_fee_abort_as_server(c_uint32 result, c_uint32 server_app_id);
char* pbk_app_get_custom_str(void);
c_uint32 pbk_flip2_simple_left(c_int32 x, c_int32 xx, c_int32 w, c_int32 h, c_uint8* buf_1, c_uint8* buf_2, c_uint8* buf_3);
c_uint32 pbk_flip2_simple_right(c_int32 x, c_int32 xx, c_int32 w, c_int32 h, c_uint8* buf_1, c_uint8* buf_2, c_uint8* buf_3);
void pbk_fee_set_fail_type(c_int32 fail_type);
c_int32 pbk_fee_get_fail_type(void);

#endif

#endif
#endif

