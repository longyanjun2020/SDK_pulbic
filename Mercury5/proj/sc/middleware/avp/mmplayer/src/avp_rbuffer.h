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


#ifndef RBUFFER_H
#define RBUFFER_H

#include <stdint.h>
#include "avp_thread_mapping.h"
#include "avp_buf_element.h"

#define MAX_RB_PKT 120

struct ringbuffer {
    uint8_t        *data;
    int32_t         size;
    int32_t         pread;
    int32_t         used;
    int32_t         pkt_cnt;
    int16_t         buf_eos;
    int32_t         free_size_needed;
    int32_t         error;
    int8_t          rlock;
    int8_t          wlock;
    int32_t         pend;
    mmp_mutex_t     ring_mutex;
    mmp_cond_t      ring_avail_cond;
    mmp_cond_t      ring_free_cond;
    buf_element_t   header[MAX_RB_PKT];
    int             header_cnt;
    int             header_idx;
};


/* initialize ring buffer, lock and queue */
void mmp_ringbuffer_init(struct ringbuffer *rbuf, void *data, uint32_t len);

/* delete ring buffer, lock and cond */
void mmp_ringbuffer_destroy(struct ringbuffer *rbuf);

/* close ring buffer, will set EOS */
void mmp_ringbuffer_close(struct ringbuffer *rbuf);

/* test whether buffer is empty */
int mmp_ringbuffer_empty(struct ringbuffer *rbuf);

/* return the number of free bytes in the buffer */
int32_t mmp_ringbuffer_free(struct ringbuffer *rbuf);

/* return the number of bytes available in the buffer */
int32_t mmp_ringbuffer_avail(struct ringbuffer *rbuf);

/* flush buffer */
void mmp_ringbuffer_flush(struct ringbuffer *rbuf);

void mmp_ringbuffer_reset(struct ringbuffer *rbuf);

int mmp_ringbuffer_write_allocate(struct ringbuffer *rbuf, buf_element_t *packet);

int mmp_ringbuffer_write_commit(struct ringbuffer *rbuf, const buf_element_t *packet);

int mmp_ringbuffer_read_peek2(struct ringbuffer *rbuf, buf_element_t *packet);

int mmp_ringbuffer_read_release(struct ringbuffer *rbuf);

#endif /* RBUFFER_H */
