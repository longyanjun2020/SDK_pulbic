//==============================================================================
//
//  File        : mmpf_eis.h
//  Description : INCLUDE File for the Firmware EIS driver function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_EIS_H_
#define _MMPF_EIS_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

//#define LOG_LONG_TIME

#define EIS_LOG_SIZE				(256)
#define GYRO_LOG_SIZE				(4000)

#define EIS_FLAG_GYRO_TASK			(0x00000001)
#define EIS_FLAG_EIS_TASK	        (0x00000002)

#define USE_RAW_PATH
#define EIS_SFT_BITS 				(8)
#define EIS_PI 						(3.14159265359)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _EIS_BUFFER_CATEGORY
{
	GYRO_RAW_X = 0,
	GYRO_RAW_Y,
	GYRO_RAW_T,
	SAMPLE_TIME,
	VIN_CNT,
	EIS_BUFFER_OFFSET_X_CHAN,
	EIS_BUFFER_OFFSET_Y_CHAN,
	EIS_BUFFER_AMV_X_CHAN,
	EIS_BUFFER_AMV_Y_CHAN,
	EIS_BUFFER_NUM_CHANNELS
} EIS_BUFFER_CATEGORY;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct eis_param_s {
	unsigned int    eis_scale_factor_num;
	unsigned int    eis_scale_factor_den_x;
	unsigned int    eis_scale_factor_den_y;
	unsigned int    sensor_cell_size_x;
	unsigned int    sensor_cell_size_y;
} eis_param_t;

typedef struct eis_move_s {
	int             mov_x;
	int             mov_y;
} eis_move_t;

typedef struct eis_s {
	unsigned char   enable;
	unsigned char   mc_en;
	unsigned char   rsc_en;
	unsigned char   me_en;
	unsigned char   samp_en;
	unsigned char   proc;
	unsigned char   enable_cmd;
	unsigned char   disable_cmd;
	unsigned char   sample_time;
	unsigned char   mc_en_pref;
	unsigned char   rsc_en_pref;
} eis_t;

typedef struct gyro_log_s {
	unsigned int    chan_num;
	struct {
		unsigned short *data;
	} chan[EIS_BUFFER_NUM_CHANNELS];
	unsigned int    ndata;
	unsigned int    head;
	unsigned int    tail;
} gyro_log_t;

typedef struct eis_log_s {
	unsigned int    chan_num;
	struct {
		int *data;
	} chan[EIS_BUFFER_NUM_CHANNELS];
	unsigned int    ndata;
	unsigned int    head;
	unsigned int    tail;
	unsigned int    frm_st;
	unsigned int    pre_frm_st;
} eis_log_t;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void MMPF_EIS_mode_init(void);
void MMPF_EIS_start_gyro_sample(void);
void MMPF_EIS_routine_2(void);
MMP_SLONG MMPF_EIS_start_gyro_log(MMP_UBYTE mode, gyro_log_t *log_ptr, MMP_BYTE *filename);
void MMPF_EIS_gyro_isr_callbackFunc(void);
MMP_SLONG MMPF_EIS_enable(MMP_ULONG en);
MMP_SLONG MMPF_EIS_update_range(void);

#endif //_MMPF_MMPF_EIS_H_