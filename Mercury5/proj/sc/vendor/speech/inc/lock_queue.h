#ifndef LOCK_QUEUE_H
#define LOCK_QUEUE_H
#include "os_wrap.h"

#define MSG_LENGTH 1024*4

typedef struct queue_node queue_node_t;
typedef struct lock_queue lock_queue_t;
typedef struct voice_msg voice_msg_t;

struct queue_node {
    queue_node_t *next;
    queue_node_t *prev;
};

struct lock_queue {
    queue_node_t *pop;
    queue_node_t *push;
//  void *data;
    int length;
    MMPF_OS_MUTEXID lock;
};

typedef enum {
    VOICE_MSG_DATA,
    VOICE_MSG_QUIT
} voice_msg_type_t;

typedef enum {
    WAKEUP_APPEND,
    WAKEUP_END
} wakeup_state_t;

struct voice_msg {
    queue_node_t n;
    voice_msg_type_t type;
    wakeup_state_t state;
    char data[MSG_LENGTH];
    int bytes;
};

int lock_queue_init(lock_queue_t *q, MMP_ULONG prio);
int lock_queue_clean(lock_queue_t *q);
int lock_queue_push(lock_queue_t *q, queue_node_t *n);
queue_node_t * lock_queue_pop(lock_queue_t *q);
int lock_queue_query(lock_queue_t *q);
#endif
