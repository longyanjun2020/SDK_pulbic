#ifndef _RBUFFER_H_
#define _RBUFFER_H_

//#include "mdl_thread_mapping.h"
#include "mdl_vdr_mx_def.h"

struct ringbuffer {
    uint8_t         *data;
    int32_t         size;
    int32_t         pread;
    int32_t         pwrite;
    int16_t         pkt_cnt;
    int16_t         buf_eos;
    int32_t         free_size_needed;
    int             error;
    int8_t          rlock;
    int8_t          wlock;
	int32_t         packet_duration;

//	cyg_mutex_t     ring_mutex;
//	cyg_cond_t      ring_avail_cond;
//	cyg_cond_t      ring_free_cond;
};


/* initialize ring buffer, lock and queue */
extern void ringbuffer_init(struct ringbuffer *rbuf, void *data, uint32_t len);

/* delete ring buffer, lock and cond */
extern void ringbuffer_destroy(struct ringbuffer *rbuf);

/* close ring buffer, will set EOS */
extern void ringbuffer_close(struct ringbuffer *rbuf);

/* test whether buffer is empty */
extern int ringbuffer_empty(struct ringbuffer *rbuf);

/* return the number of free bytes in the buffer */
extern int32_t ringbuffer_free(struct ringbuffer *rbuf);

/* return the number of bytes available in the buffer */
extern int32_t ringbuffer_avail(struct ringbuffer *rbuf);

/* alloc the required size from buffer, would wait if not available */
extern int32_t ringbuffer_alloc(struct ringbuffer *rbuf, uint32_t alloc_len);

#if 0
/* release the number of bytes used in the buffer */
extern void ringbuffer_release(struct ringbuffer *rbuf);
#else
extern void ringbuffer_pktt_release(struct ringbuffer *rbuf, uint32_t release_len);
#endif

/* read routines & macros */
/* ---------------------- */
/* flush buffer */
extern void ringbuffer_flush(struct ringbuffer *rbuf);

/* peek at byte <offs> in the buffer */
#define RINGBUFFER_PEEK(rbuf,offs)  \
            (rbuf)->data[((rbuf)->pread+(offs))%(rbuf)->size]

/* advance read ptr by <num> bytes */
#define RINGBUFFER_SKIP(rbuf,num)   \
            (rbuf)->pread=((rbuf)->pread+(num))%(rbuf)->size

#if 0
/*
** read <len> bytes from ring buffer into <buf>
** <usermem> specifies whether <buf> resides in user space
** returns number of bytes transferred or -EFAULT
*/
extern int32_t ringbuffer_read(struct ringbuffer *rbuf, uint8_t *buf,
                   uint32_t len);

extern int32_t ringbuffer_pktt_read(struct ringbuffer *rbuf, uint8_t *buf, int32_t len,
                             uint8_t *pkt_buf, uint32_t pkt_len, uint8_t skip);
#else
extern int32_t ringbuffer_read_peek(struct ringbuffer *rbuf, uint8_t *buf, uint32_t len, uint32_t skip_len);

extern int32_t ringbuffer_pktt_read_peek(struct ringbuffer *rbuf, uint8_t *buf, int32_t len,
                             uint8_t *pkt_buf, uint32_t pkt_len);

#endif


/* write routines & macros */
/* ----------------------- */
/* write single byte to ring buffer */
#define RINGBUFFER_WRITE_BYTE(rbuf,byte)    \
            { (rbuf)->data[(rbuf)->pwrite]=(byte); \
            (rbuf)->pwrite=((rbuf)->pwrite+1)%(rbuf)->size; }
/*
** write <len> bytes to ring buffer
** <usermem> specifies whether <buf> resides in user space
** returns number of bytes transferred or -EFAULT
*/
extern int32_t ringbuffer_write(struct ringbuffer *rbuf, const uint8_t *buf,
                    uint32_t len);

extern int32_t ringbuffer_pktt_write(struct ringbuffer *rbuf, const uint8_t *buf, uint32_t len,
                              const uint8_t *pkt_buf, uint32_t pkt_len);

extern void ringbuffer_byte_release(struct ringbuffer *rbuf, uint32_t release_len);
extern int32_t ringbuffer_byte_read_peek(struct ringbuffer *rbuf, uint8_t *buf, uint32_t len);
extern int32_t ringbuffer_byte_read_peek_single_thread(struct ringbuffer *rbuf, uint8_t *buf, int32_t len);
extern int32_t ringbuffer_byte_write(struct ringbuffer *rbuf, const uint8_t *buf, uint32_t len);
extern void ringbuffer_reset(struct ringbuffer *rbuf);


#endif /* _RBUFFER_H_ */
