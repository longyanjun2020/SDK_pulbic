////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDL_IMGCODEC_MJPGLIB_H_
#define _MDL_IMGCODEC_MJPGLIB_H_

#include <stdint.h>

typedef enum
{
    MJPG_SUCCESS = 0,
    MJPG_HEADER_ERR,
    MJPG_TIMEOUT_ERR,
    MJPG_BITSTREAM_ERR,
    MJPG_JPD_ERR,
    MJPG_SCL_ERR,
    MJPG_MEM_ERR,
    MJPG_FULL_ERR,
} MJPG_ERROR_CODE_e;

typedef enum
{
    MJPD_INDEX_MODE,
    MJPD_BUFFER_MODE,
} MJPD_BUFFER_MODE_e;

typedef enum
{
    MJPD_ROTATE_0,
    MJPD_ROTATE_90,
    MJPD_ROTATE_180,
    MJPD_ROTATE_270,
} MJPD_ROTATE_MODE_e;

typedef struct mjpg_frame_info_s
{
    int                  index;
    uint8_t     *output_buffer;
    MJPD_BUFFER_MODE_e    mode;
    int                 inited;
    int32_t       output_width;
    int32_t      output_height;
    uint16_t           start_x;
    uint16_t           start_y;
    MJPD_ROTATE_MODE_e rotate_mode;
} mjpg_frame_info_st;

MJPG_ERROR_CODE_e MJPD_init(
    uint8_t *bitstream,
    int32_t sample_size,
    int32_t *stream_width,
    int32_t *stream_height
    );

MJPG_ERROR_CODE_e MJPD_setOutput(
    uint16_t disp_width,
    uint16_t disp_height,
    uint16_t start_x,
    uint16_t start_y,
    uint16_t y_stride,
    MJPD_ROTATE_MODE_e rotate_mode,
    int32_t buffer_width,
    int32_t buffer_height,
    uint8_t output_format
    );

MJPG_ERROR_CODE_e MJPD_decode(
    uint8_t *pBitstream,
    int32_t sample_size,
    mjpg_frame_info_st *mjpg_info
    );

MJPG_ERROR_CODE_e MJPD_reset(void);

MJPG_ERROR_CODE_e MJPD_close(void);

MJPG_ERROR_CODE_e MJPD_getFreeIdx(int *bufIdx);

void* MJPD_getSurfInDisp(void);

void MJPD_setDispBufferIndex(int bufIdx);

uint8_t* MJPD_getDispBuffer(int bufIdx);

void* MJPD_getDispSurface(int bufIdx);

uint8_t MJPD_isHardwareDecoder(void);

#endif
