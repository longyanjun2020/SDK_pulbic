////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
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


#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include "avp_ms_io.h"
#include "avp_mvc_decoder.h"

#ifdef _SUPPORT_2KX2K_
#define VIDEC_IBUF_SIZE   1024*1024*4
#elif defined(_SUPPORT_1080I_)
#define VIDEC_IBUF_SIZE   1024*1024*5/2
#elif defined(_SUPPORT_720P_)
#define VIDEC_IBUF_SIZE   1024*1024
#elif defined(_SUPPORT_CIF_)
#if (_PROCESSOR_NUMBER_ == 2) && (_PROCESSOR_ID_ == 1)
#define VIDEC_IBUF_SIZE   1024*128  // if supporting dual processors, 128K is required.
#else
#define VIDEC_IBUF_SIZE   1024*64 //1024*128  // if supporting dual processors, 128K is required.
#endif
#elif defined(_SUPPORT_QCIF_)
#define VIDEC_IBUF_SIZE   1024*16
#else
#define VIDEC_IBUF_SIZE   1024*256
#endif

#define IFRAME_MAX_SIZE (VIDEC_IBUF_SIZE / 2)   // for no_vop_header case

typedef struct video_param_s
{
    uint16_t width;
    uint16_t height;
    uint8_t  ts_type;       // 0: pts  1: dts
    uint8_t  wmv_simvophdr;
    uint8_t  divx_flag;
    int codec_type;
} video_param_st;

typedef struct io_s
{
#ifdef INPUT_FROM_FILE
    FILE    *infile;
    uint8_t *ibuf_fixed_read_pt;
#endif
    uint8_t *bits_ptr;
    int      bits_len;
    uint8_t *ibuf_mark;
    uint8_t  ibuf_eof;
    uint8_t ibuf[VIDEC_IBUF_SIZE * 2 + 3];  // +3 -> for ending bits
    int      is_ivf_format;
} io_st;

int input_open_file(const ms_fnchar *filename, video_param_st *param, int codec_type, io_st **pio);
int input_get_config(io_st *io, uint8_t **data, int *length, int codec_type);
int input_get_frame(io_st *io, uint8_t **data, int *length, int64_t *pts, int no_header_code, int interlaced, int codec_type
#ifdef WMV_SIM_VOP
                    , uint8_t wmv_simvophdr
#endif
                    );
int input_consume_bits(io_st *io, int length, int no_header_code, int interlaced);
int input_close_file(io_st *io);

#endif /* INPUT_H */
