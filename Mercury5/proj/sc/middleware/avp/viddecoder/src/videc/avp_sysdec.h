////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
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


#ifndef SYSDEC_H
#define SYSDEC_H

#include <stdint.h>

//#define SUPPORT_TS2
//#define SUPPORT_PS2
//#define SUPPORT_AVI
//#define SUPPORT_MP4
//#define SUPPORT_FLV
//#define SUPPORT_RMF
//#define SUPPORT_MFS
//#define SUPPORT_ASF

#define SYSTYPE_NONE       0
#define SYSTYPE_AVI_FILE   1
#define SYSTYPE_TS2_FILE   2
#define SYSTYPE_PS2_FILE   3
#define SYSTYPE_MP4_FILE   4
#define SYSTYPE_ASF_FILE   5
#define SYSTYPE_FLV_FILE   6
#define SYSTYPE_RMF_FILE   7
#define SYSTYPE_MFS_FILE   8

#define SYS_OK   0
#define SYS_FAIL 1

#define AVIDMX_HEAP_BUFFER_SIZE (512 * 1024)

#if defined(SUPPORT_TS2) || defined(SUPPORT_PS2) || defined(SUPPORT_MP4) || defined(SUPPORT_ASF) || defined(SUPPORT_AVI) || defined(SUPPORT_FLV) || defined(SUPPORT_RMF) || defined(SUPPORT_MFS)
#define SUPPORT_SYSF

#include "avp_ms_io.h"
#include "avp_ms_input.h"
#include "avp_ms_thread.h"
#include "avp_buf_element.h"
#include "avp_mvc_demuxer.h"

struct es_video_property
{
    char valid;
    uint8_t fourcc[4];
    int width;
    int height;
};

struct es_audio_property
{
    char valid;
    uint8_t fourcc[4];
};

typedef struct au_packet_st
{
    uint32_t len;
    uint64_t pts;
} au_packet_s;

typedef struct sys_handle_s {
    int   sys_type;
    int   ts_type; // 0: pts 1: dts
    void *heap;
    int   heap_size;
    void                   *demuxer;
    ms_thread_st            thread;
    const mvc_dmx_func_st  *dmx_func;
    struct ringbuffer      *rbuf;
    buf_element_t           packet;
    cb_io_st                cbio;
    int (*sys_read_segment)(void *handle, uint8_t *buff, int buf_size, int *read_size);
} sys_handle_st;

int std_sys_file_open(const ms_fnchar *filename, sys_handle_st *handle,
                      struct es_video_property *vprop, struct es_audio_property *aprop,
                      uint8_t *rbuf_data, int rbuf_size,
                      struct ringbuffer *rbuf);
int std_sys_read_segment(sys_handle_st *handle, uint8_t **buff, int *size, int64_t *pts);
int std_sys_get_config(sys_handle_st *handle, uint8_t **buff, int *size);
int std_sys_file_close(sys_handle_st *handle);

#endif

#endif /* SYSDEC_H */
