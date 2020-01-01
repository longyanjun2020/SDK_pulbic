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


#ifndef MS_INPUT_H
#define MS_INPUT_H

#include <stdint.h>

typedef int32_t cb_fpos;

typedef enum cbio_error_e
{
    CBIO_OK,
    CBIO_OpenFailed,
    CBIO_MallocFailed
} cbio_error_et;

typedef enum cbio_open_mode_e
{
    CBIO_FO_RB,
    CBIO_FO_WB,
    CBIO_FO_AB,
} cbio_open_mode_et;

typedef enum
{
    MMP_FILE_UNKNOWN = 0,
    // image
    MMP_FILE_JPEG,
    MMP_FILE_BMP,
    MMP_FILE_GIF,
    MMP_FILE_PNG,
    MMP_FILE_QRCODE,
    // audio
    MMP_FILE_AAC,
    MMP_FILE_AMR,
    MMP_FILE_AWB,
    MMP_FILE_MIDI,
    MMP_FILE_MP3,
    MMP_FILE_PCM,
    MMP_FILE_WAV,
    MMP_FILE_WMA,
    MMP_FILE_AC3,
    MMP_FILE_DRA,
    // video
    MMP_FILE_ASF,
    MMP_FILE_AVI,
    MMP_FILE_FLV,
    MMP_FILE_MKV,
    MMP_FILE_MP4,
    MMP_FILE_MPG,
    MMP_FILE_RM,
    MMP_FILE_CMMB,
    MMP_FILE_TMP4, // TIVC
    MMP_FILE_TS,
    MMP_FILE_TINY,
    MMP_FILE_RTP,
    // raw video
    MMP_FILE_264,
    MMP_FILE_263,
    MMP_FILE_FLV1,
    MMP_FILE_M4V,
    MMP_FILE_RVC,
    MMP_FILE_YUV,
} MMP_FILE_TYPE;

typedef struct cb_io_s
{
    cb_fpos (* read)(struct cb_io_s *ctx, void *buf, cb_fpos size);
    cb_fpos (* write)(struct cb_io_s *ctx, void *buf, cb_fpos size);
    cb_fpos (* seek)(struct cb_io_s *ctx, cb_fpos offset, int whence); /* returns -1 if failed */
    cb_fpos (* tell)(struct cb_io_s *ctx);
    void    (* close)(struct cb_io_s **ctx);
    cb_fpos (* aread)(struct cb_io_s *ctx, void *buf, cb_fpos size);
    int     (* open_done)(struct cb_io_s *ctx, int a_bitrate, int v_bitrate, uint32_t file_duration);
    void    (* get_new_cmd)(struct cb_io_s *ctx);
    int     (* seek_time)(struct cb_io_s *ctx, int seek_time);
    int     (* stop_wait_input)(struct cb_io_s *ctx);

    int     block_size;
    uint8_t seekable;
    uint8_t streaming;
    uint8_t use_thread;
    uint8_t rbuf_mode;
    int     type_hint;
    int     file_type;
    int     programID;
    void   *context;
    const void *filename;
    cbio_open_mode_et open_mode;
    void    *parent;
    int      bitrate;
    int      input_size;
    void    *fcc_buf;
} cb_io_st;

#endif /* MS_INPUT_H */
