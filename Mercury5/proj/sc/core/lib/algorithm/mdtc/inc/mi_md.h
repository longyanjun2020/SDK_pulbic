#ifndef __MI_MD_H__
#define __MI_MD_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum _MI_MD_RET_E
{
	MI_MD_RET_SUCCESS						= 0x00000000,	/*MD API execution success*/
	MI_MD_RET_INIT_ERROR                    = 0x10000401,   /*MD init error*/
    MI_MD_RET_IC_CHECK_ERROR                = 0x10000402,   /*Incorrect platform check for MD*/
    MI_MD_RET_INVALID_HANDLE                = 0x10000403,   /*Invalid MD handle*/
    MI_MD_RET_INVALID_PARAMETER             = 0x10000404,   /*Invalid MD parameter*/
    MI_MD_RET_MALLOC_ERROR                  = 0x10000405,   /*Allocate MD workiung buffer error*/
    MI_MD_RET_REGION_INIT_ERROR             = 0x10000406,   /*Multi region initial error*/
} MI_MD_RET;
typedef struct
{
    // (0: disable, 1: enable)
	uint8_t enable;
    //(0 ~ 99)
	uint8_t size_perct_thd_min;
    //(1 ~ 100), must be larger than size_perct_thd_min
	uint8_t size_perct_thd_max;
    //(10, 20, 30, ..., 100), 100 is the most sensitive
	uint8_t sensitivity;
    //(1000 ~ 30000)
	uint16_t learn_rate;
} MDParamsIn_t;

typedef struct
{
	uint8_t md_result;
    uint32_t obj_cnt;
} MDParamsOut_t;

typedef void* MD_HANDLE;

uint32_t MI_MD_GetLibVersion();
int32_t MI_MD_QueryBufferSize(uint16_t width, uint16_t height, uint8_t color, uint8_t w_div, uint8_t h_div);
MD_HANDLE MI_MD_Init(uint16_t width, uint16_t height, uint8_t color, uint8_t w_div, uint8_t h_div);
MD_HANDLE MI_MD_InitEx(uint8_t *work_buffer, int32_t buff_size, uint16_t width, uint16_t height, uint8_t color, uint8_t w_div, uint8_t h_div);
void MI_MD_Uninit(MD_HANDLE handle);
int32_t MI_MD_Run(MD_HANDLE handle, const uint8_t* pImage);
MI_MD_RET MI_MD_SetDetectWindow(MD_HANDLE handle, uint16_t lt_x, uint16_t lt_y, uint16_t rb_x, uint16_t rb_y, uint8_t w_div, uint8_t h_div);
MI_MD_RET MI_MD_GetDetectWindowSize(MD_HANDLE handle, uint16_t* st_x, uint16_t* st_y, uint16_t* div_w, uint16_t* div_h);
MI_MD_RET MI_MD_SetWindowParamsIn(MD_HANDLE handle, uint8_t w_num, uint8_t h_num, const MDParamsIn_t* param);
MI_MD_RET MI_MD_GetWindowParamsIn(MD_HANDLE handle, uint8_t w_num, uint8_t h_num, MDParamsIn_t* param);
MI_MD_RET MI_MD_GetWindowParamsOut(MD_HANDLE handle, uint8_t w_num, uint8_t h_num, MDParamsOut_t* param);
void MI_MD_SetTime(MD_HANDLE handle, uint32_t time_diff);
void MI_MD_GetYMean(MD_HANDLE handle, uint32_t* mean);

#ifdef __cplusplus
}
#endif

#endif /* __MI_MD_H__ */
