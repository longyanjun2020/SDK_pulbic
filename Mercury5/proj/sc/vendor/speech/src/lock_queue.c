#include "lock_queue.h"

int lock_queue_init(lock_queue_t *q, MMP_ULONG prio)
{
    q->pop = q->push = NULL;
    q->length = 0;

    //@retval 0xFF for create semaphore internal error from OS
    //      0xFE the system maximum semaphore counts exceed.
    q->lock = MMPF_OS_CreateMutex(prio);
    if (q->lock == MMPF_OS_ERR_SEM_ID_EXCEED_MAX || q->lock == MMPF_OS_ERR_CREATE_SEM_ERR) {
        printc("lock_queue_init error!!\r\n");
        return -1;
    } else {
        //MMPF_OS_ReleaseMutex(q->lock);
        return 0;
    }
}

int lock_queue_clean(lock_queue_t *q)
{
    return MMPF_OS_DeleteMutex(q->lock);
}

int lock_queue_push(lock_queue_t *q, queue_node_t *n)
{
    int ret;
    ret = MMPF_OS_AcquireMutex(q->lock, 0);
    if (ret == 0) {
        n->prev = q->push;
        if (q->push) {
            q->push->next = n;
        }
        n->next = 0;
        q->push = n;
        if (!q->pop) {
            q->pop = n;
        }
        ++q->length;
    }
    ret = MMPF_OS_ReleaseMutex(q->lock);
    return ret;
}

queue_node_t * lock_queue_pop(lock_queue_t *q)
{
    int ret;
    queue_node_t *n = 0;
    ret = MMPF_OS_AcquireMutex(q->lock, 0);
    if (ret == 0) {
        if (q->length <= 0) {
            goto end;
        }
        if (!q->pop) {
            goto end;
        }
        n = q->pop;
        q->pop = q->pop->next;
        if (q->pop) {
            q->pop->prev = 0;
        } else {
            q->push = 0;
        }
        --q->length;
    }
end:
    MMPF_OS_ReleaseMutex(q->lock);
    return n;
}

int lock_queue_query(lock_queue_t *q)
{
    int lenght;
    MMPF_OS_AcquireMutex(q->lock, 0);
    lenght = q->length;
    MMPF_OS_ReleaseMutex(q->lock);
    return lenght;
}