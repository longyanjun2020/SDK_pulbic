#ifndef __MMI_COMMON_QUEUE_H__
#define __MMI_COMMON_QUEUE_H__

#include "vm_types.ht"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Queue_tag
{
	u32 nStart;
	u32 nEnd;
	u32 nCount;
	u32 nPopCount;
	u32 nMaxSize;
	u32 *pDataArray;
	bool *pIsPopArray;
}Queue_t;

bool Queue_AddTail(Queue_t *pQueue, void *data);
void* Queue_GetByIndex(Queue_t *pQueue, u32 nIndex);
void* Queue_PopByIndex(Queue_t *pQueue, u32 nIndex);
bool Queue_IsEmpty(Queue_t *pQueue);
u32 Queue_GetSize(Queue_t *pQueue);
Queue_t *Queue_CreateQueue(u32 nQueueSize);
bool Queue_DestoryQueue(Queue_t *pQueue);
bool Queue_Enlarge(Queue_t *pQueue, u32 nType);

#ifdef __cplusplus
};
#endif

#endif// __MMI_COMMON_QUEUE_H__
