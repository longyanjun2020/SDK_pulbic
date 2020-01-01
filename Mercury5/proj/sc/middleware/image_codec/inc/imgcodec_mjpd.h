#ifndef _IMGCODEC_MJPD_H_
#define _IMGCODEC_MJPD_H_

#include "mdl_imgcodec_mjpd.h"
#include "drv_scl.h"

MJPG_ERROR_CODE_e HW_MJPD_init(
    uint8_t *bitstream,
    int32_t sample_size,
    int32_t *stream_width,
    int32_t *stream_height
    );

MJPG_ERROR_CODE_e HW_MJPD_setOutput(
    uint16_t disp_width,
    uint16_t disp_height,
    uint16_t start_x,
    uint16_t start_y,
    uint16_t y_stride,
    SCLDST_FORMAT_e rotate_mode,
    int32_t buffer_width,
    int32_t buffer_height,
    uint8_t output_format
    );

MJPG_ERROR_CODE_e HW_MJPD_decode(
    uint8_t *pBitstream,
    int32_t sample_size,
    mjpg_frame_info_st *mjpg_info
    );

MJPG_ERROR_CODE_e HW_MJPD_reset(void);

MJPG_ERROR_CODE_e HW_MJPD_close(void);

MJPG_ERROR_CODE_e HW_MJPD_getFreeIdx(int *bufIdx);

void* HW_MJPD_getSurfInDisp(void);

void HW_MJPD_setDispBufferIndex(int bufIdx);

void* HW_MJPD_getDispSurface(int bufIdx);


MJPG_ERROR_CODE_e SW_MJPD_init(
    uint8_t *bitstream,
    int32_t sample_size,
    int32_t *stream_width,
    int32_t *stream_height
    );

MJPG_ERROR_CODE_e SW_MJPD_setOutput(
    uint16_t disp_width,
    uint16_t disp_height,
    uint16_t start_x,
    uint16_t start_y,
    uint16_t y_stride,
    SCLDST_FORMAT_e rotate_mode,
    int32_t buffer_width,
    int32_t buffer_height,
    uint8_t output_format
    );

MJPG_ERROR_CODE_e SW_MJPD_decode(
    uint8_t *pBitstream,
    int32_t sample_size,
    mjpg_frame_info_st *mjpg_info
    );

MJPG_ERROR_CODE_e SW_MJPD_reset(void);

MJPG_ERROR_CODE_e SW_MJPD_close(void);

MJPG_ERROR_CODE_e SW_MJPD_getFreeIdx(int *bufIdx);

void* SW_MJPD_getSurfInDisp(void);

void SW_MJPD_setDispBufferIndex(int bufIdx);

void* SW_MJPD_getDispSurface(int bufIdx);
#endif
