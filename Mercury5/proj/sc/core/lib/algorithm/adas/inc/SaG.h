
/* -- DO NOT MODIFY ---- DO NOT MODIFY ----------- O NOT MODIFY ---------- DO NOT MODIFY DIFY -------------- */
/* -- DO NOT MODIFY ----- DO NOT MODIFY --------- O NOT MODIFY ---------- DO NOT MODIFY MODIFY ------------- */
/* -- DO NOT MODIFY ------ DO NOT MODIFY ------- O NOT MODIFY ---------- DO NOT MODIFY T MODIFY ------------ */
/* -- DO NOT MODIFY ------- DO NOT MODIFY ----- O NOT MODIFY ---------- DO NOT MODIFY NOT MODIFY ----------- */
/* -- DO NOT MODIFY -------- DO NOT MODIFY --- O NOT MODIFY ---------- DO NOT MODIFY O NOT MODIFY ---------- */
/* -- DO NOT MODIFY --------- DO NOT MODIFY - O NOT MODIFY ---------- DO NOT MODIFY - DO NOT MODIFY -------- */
/* -- DO NOT MODIFY ---------- DO NOT MODIFY O NOT MODIFY ---------- DO NOT MODIFY --- DO NOT MODIFY ------- */
/* -- DO NOT MODIFY ----------- DO NOT MODIFY NOT MODIFY ---------- DO NOT MODIFY ----- DO NOT MODIFY ------ */
/* -- DO NOT MODIFY ------------ DO NOT MODIFY T MODIFY ---------- DO NOT MODIFY --DONT- DO NOT MODIFY ----- */
/* -- DO NOT MODIFY ------------- DO NOT MODIFY MODIFY ---------- DO NOT MODIFY --------- DO NOT MODIFY ---- */
/* -- DO NOT MODIFY -------------- DO NOT MODIFY DIFY ---------- DO NOT MODIFY ----------- DO NOT MODIFY --- */
/* -- DO NOT MODIFY --------------- DO NOT MODIFY ------------- DO NOT MODIFY ------------- DO NOT MODIFY -- */

#ifndef SAG_H
#define SAG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum sag_err_e
{
	SAG_ERR_NONE              = 0x300,
	SAG_ERR_NOT_SUPPROT,
	SAG_ERR_INVALID_PARAMETER,
	SAG_ERR_IC_CHECK,
	SAG_ERR_OUT_OF_MEMORY
}sag_err;

typedef struct _sag_info_t
{
	int state;
	int distance;
} sag_info_t; 

typedef struct _sag_params
{
	int image_width  ;
	int image_height  ;
	int detect_lower;
} sag_params;  

typedef struct _sag_result
{
	int go_alarm;
	int true_state;
}sag_result;  

typedef struct _gps  //GPS¸ê°T
{
	short gps_state;
	short gps_speed;
	short g_sensor_z;
	unsigned short true_light;
} gps_info;

typedef struct _user_info
{
	char sensitivity;
}sag_user_info;

typedef struct _sag_debug_info_t
{
	short g_info_z;

	short g_diff_z;

	short g_thd_Start;

	short g_thd_Check;

	short g_thd_Move;

	int d_state;

	int check;

	int total;
	int t_medium;
	int t_low;

	int box_1;
	int box_2;
	int box_3;
	int box_4;
	int box_5;

	int low_1;
	int low_2;
	int low_3;
	int low_4;
	int low_5;

	int d_alarm;

	int distance;

	unsigned short d_light;
} sag_debug_info;

extern int sag_get_buffer_info_with_flag(int width, int height , unsigned char color, int flag);
extern int sag_get_buffer_info(int width, int height , unsigned char color);
//#define sag_get_buffer_info(a,b,c,...) sag_get_buffer_info_with_flag( a, b, c, (0, ##__VA_ARGS__) )

extern int sag_init(unsigned char* working_buf_ptr , int working_buf_len , int user_info);

extern int sag_get_params(sag_params *params);

extern int sag_get_result(sag_result *alarm_result);

extern void sag_get_debug_info(sag_debug_info *debug_info);

extern int sag_process(unsigned char *src , sag_info_t *sag_info , gps_info *true_gps);

extern void SAG_set_sobel_hor(unsigned char* hor, unsigned int* mean, unsigned int* mean_square);
extern void SAG_set_sobel_ver(unsigned char* ver, unsigned int* mean, unsigned int* mean_square);

extern int Sobel_mask_addr(unsigned long *edge_mask, unsigned long *grade_mask);

extern unsigned int sag_GetLibVersion(unsigned int* ver);

#ifdef __cplusplus
}
#endif

#endif
