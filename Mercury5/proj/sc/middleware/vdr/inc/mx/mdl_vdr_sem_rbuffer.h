#ifndef _SEM_RBUFFER_H_
#define _SEM_RBUFFER_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include "mdl_thread_mapping.h"
#include "mdl_vdr_mx_def.h"

#ifdef __RTK_OS__
#include "sys_MsWrapper_cus_os_sem.h"
#endif

#define MAX_POOL_NUM 8

#undef TRUE
#define TRUE 1
#undef FALSE
#define FALSE 0

#ifndef MIN
#define MIN(a,b) (a<b? a : b)
#endif


struct ring_item_info {
	unsigned int item_size;
	int Reserved[11];
};

typedef struct {
    uint8_t in_use;
    uint8_t *start_ptr;
    unsigned int end_idx;
} sem_ringbuffer_pool_t;

struct sem_ringbuffer {
	//semaphore implementations
	SEM_INFO_T  sem_mutex;
	SEM_INFO_T  sem_items;
	SEM_INFO_T  sem_spaces;

	unsigned int item_count, item_chunk_size;
	unsigned int idx_put, idx_get;
	struct ring_item_info *items_info;
	uint8_t *items;
    unsigned int item_info_count;
	unsigned int sub_idx_put, sub_idx_get;
	unsigned char curr_pool_get, curr_pool_put;
    unsigned char num_pool_in_use;
    sem_ringbuffer_pool_t pool[MAX_POOL_NUM];
};


/* initialize ring buffer, lock and queue */
extern int sem_ringbuffer_init(struct sem_ringbuffer *rbuf, void *items_buf, int32_t items_buf_size,
							 void *items_info_buf, int32_t items_info_buf_size, int32_t chunk_size);

/* enlarge ringbuffer pool */
extern int sem_ringbuffer_attach_pool(struct sem_ringbuffer *rbuf, void *items_buf, uint32_t items_buf_size);

/* delete ring buffer, lock and cond */
extern void sem_ringbuffer_destroy(struct sem_ringbuffer *rbuf);

extern void sem_ringbuffer_put_item(struct sem_ringbuffer *rbuf, void *item, struct ring_item_info *item_info);
extern void sem_ringbuffer_get_item(struct sem_ringbuffer *rbuf, void *item, struct ring_item_info *item_info);
extern void *sem_ringbuffer_peek_item(struct sem_ringbuffer *rbuf, struct ring_item_info *item_info);

/* close ring buffer, will set EOS */
extern void sem_ringbuffer_close(struct sem_ringbuffer *rbuf);

/* return the number of free bytes in the buffer */
extern int32_t sem_ringbuffer_free(struct sem_ringbuffer *rbuf);

/* return the number of bytes available in the buffer */
extern int32_t sem_ringbuffer_avail(struct sem_ringbuffer *rbuf);


#if defined(__cplusplus)
}
#endif


#endif /* _SEM_RBUFFER_H_ */
