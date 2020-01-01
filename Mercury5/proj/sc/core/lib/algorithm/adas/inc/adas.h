/*
 * adas.h
 *
 *  Created on: 2015/3/16
 *      Author: chris
 */

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

#ifndef ADAS_H_
#define ADAS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ldws.h"
#include "fcws.h"
#include "SaG.h"

typedef enum ADAS_init_error_type_t
{
    ADAS_INIT_ERR_NONE = 0,
    ADAS_INIT_ERR_IC_CHECK,
    ADAS_INIT_ERR_BUFFER_SIZE,
    ADAS_INIT_ERR_CALIB_VALUE,
    ADAS_INIT_ERR_LDWS_FAIL,
    ADAS_INIT_ERR_FCWS_FAIL,
    ADAS_INIT_ERR_SAG_FAIL
} ADAS_init_error_type;

typedef enum ADAS_error_type_t
{
    ADAS_ERR_NONE = 0,
    ADAS_ERR_IC_CHECK,
    ADAS_ERR_NOT_INIT,
    ADAS_ERR_TERMINATED,
    ADAS_ERR_LDWS_ERR_IC_CHECK = LDWS_ERR_IC_CHECK,
    ADAS_ERR_LDWS_ERR_LINE_DETECT,
    ADAS_ERR_FCWS_ERR_IC_CHECK = FCWS_ERR_IC_CHECK,
    ADAS_ERR_SAG_ERR_IC_CHECK = SAG_ERR_IC_CHECK,
    ADAS_ERR_NUM
} ADAS_error_type;

//============================== ADAS init params =====================================//
typedef struct _ldws_input_t
{
    ldws_tuning_params  LDWS_params;
    LdwsSetupPosi       LDWS_pos;
} ldws_input_t;

typedef struct _adas_input_t
{
    int                 image_width;
    int                 image_height;
    int                 dz_N;
    int                 dz_M;
    int                 camera_focal;
    int                 sensor_cell_width;
} adas_input_t;

typedef struct _ADAS_init_params {
    unsigned int        user_calib_y_start;
    unsigned int        user_calib_y_end;
    unsigned int        user_calib_camera_height;

    ldws_input_t        LDWS_input_params;
    adas_input_t        ADAS_input_params;
    sag_user_info       SAG_user_params;
} ADAS_init_params;
//============================== ADAS init params =====================================//


//============================== ADAS process params ==================================//
typedef struct _LDWS_process_params {
    int                 left_sensitivity_factor_X256;
    int                 right_sensitivity_factor_X256;
} LDWS_process_params;

typedef struct _ADAS_process_params {
    LDWS_process_params LDWS_params;
} ADAS_process_params;
//============================== ADAS process params ==================================//


//============================== system info set to ADAS ==============================//
typedef struct _ADAS_set_info {
    gps_info            gps_params;
    int                 day_or_night;
} ADAS_set_info;
//============================== system info set to ADAS ==============================//

//============================== ADAS result ==========================================//
typedef struct _ldws_info_t
{
    ldws_params_t       ldws_params;
    int                 ldws_err_state;
} ldws_info_t;

typedef struct _ADAS_results {
    ldws_info_t*        LDWS_result;
    fcws_info_t*        FCWS_result;
    sag_result*         SAG_result;

    ldws_debug_info*    ldws_debug;
    fcws_debug_info*    fcws_debug;
    sag_debug_info*     sag_debug;
} ADAS_results;
//============================== ADAS result ==========================================//

extern int ADAS_get_buffer_info(unsigned short width, unsigned short height);
extern ADAS_init_error_type ADAS_init(unsigned short width, unsigned short height, unsigned char* working_buf_ptr, int working_buf_len, ADAS_init_params* params);
extern ADAS_error_type ADAS_process(const unsigned char *src, ADAS_set_info* params);
extern int ADAS_enable(int LDWS_enable, int FCWS_enable, int SAG_enable);
extern int ADAS_get_result(ADAS_results* result);
extern int ADAS_set_params(ADAS_process_params* params);
extern int ADAS_wait_process_done(void);
extern int ADAS_abort_process(void);
extern unsigned int ADAS_GetLibVersion(unsigned int* ver);

#ifdef __cplusplus
}
#endif

#endif /* ADAS_H_ */
