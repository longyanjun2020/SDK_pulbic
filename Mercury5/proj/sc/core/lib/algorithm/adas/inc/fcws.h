
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

#ifndef FCWS_H
#define FCWS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _fcwsMyPOINT
{
	int x;
	int y;
} fcwsMyPOINT;

typedef struct _ldws_result_t
{
	fcwsMyPOINT left_lane[2];
	fcwsMyPOINT right_lane[2];
	int     state;
} ldws_result_t;

typedef enum fcws_err_e
{
	FCWS_ERR_NONE = 0x200,
	FCWS_ERR_NULL_PARAMETER,
	FCWS_ERR_NOT_READY,
	FCWS_ERR_NOT_INIT,
	FCWS_ERR_NOT_SUPPROT,
	FCWS_ERR_INVALID_PARAMETER,
	FCWS_ERR_OUT_OF_MEMORY,
	FCWS_ERR_IC_CHECK
}fcws_err;

typedef enum _fcws_car_position_e
{
	FCWS_CAR_POSITION_FORWARD = 0,
	FCWS_CAR_POSITION_RIGHT   = 1,
	FCWS_CAR_POSITION_LEFT    = 2
}fcws_car_position_e;

typedef enum _fcws_state_e
{
	FCWS_STATE_LOSE = 0,
	FCWS_STATE_FIND
}fcws_state_e;

typedef struct _fcws_info_t {
	fcws_state_e        state;
	fcws_car_position_e position;
	int car_x;
	int car_y;
	int car_width;
	int car_height;
	int distance;
} fcws_info_t;

typedef struct _fcws_params_t {
	unsigned short laneCalibrationImageWidth;
	unsigned short laneCalibrationImageHeight;
	unsigned short laneCalibrationUpPointX;
	unsigned short laneCalibrationUpPointY;
	unsigned short laneCalibrationLeftPointX;
	unsigned short laneCalibrationLeftPointY;
	unsigned short laneCalibrationRightPointX;
	unsigned short laneCalibrationRightPointY;

	int image_width;
	int image_height;
	int dz_N;
	int dz_M;
	
	int detect_upper;
	int detect_lower;
	float width_rate;
	
	int camera_focal;
	int camera_height;
	int sensor_cell_width;
} fcws_params_t;

typedef struct _fcws_debug_info_t
{
	int		iCarVld;
	int		iCarDist;
	int 	iMyCarX;
	int 	iMyCarY;
	int 	iMyCarW;
	int 	iMyCarLife;
	int		iLTX;
	int		iLBX;
	int 	iRTX;
	int		iRBX;
	int 	iTY;
	int		iBY;
} fcws_debug_info;

extern int fcws_get_buffer_info_with_flag(unsigned short width, unsigned short height, int flag);
extern int fcws_get_buffer_info(unsigned short width, unsigned short height);
extern fcws_err fcws_init(fcws_params_t *params, unsigned char* working_buf_ptr, int working_buf_len);
extern fcws_err fcws_deinit(void);
extern fcws_err fcws_set_roi(int  x, int y , int roi_width , int  roi_height);
extern fcws_err fcws_get_roi(int *x, int *y, int *roi_width, int *roi_height);
extern fcws_err fcws_set_params(fcws_params_t *params);
extern fcws_err fcws_get_params(fcws_params_t *params);
extern fcws_err fcws_get_result(fcws_info_t *info);
extern fcws_err fcws_process(void *src, const void *in_integral, ldws_result_t *ldws_result, int gps_speed, int day_or_night);
extern unsigned int fcws_GetLibVersion(unsigned int* ver);
extern void fcws_printk(char *fmt, ...);
extern void fcws_get_debug_info(fcws_debug_info *debug_info);
extern void FCWS_get_global_y_start(int *);
//#define fcws_printk printf

#ifdef __cplusplus
}
#endif

#endif
