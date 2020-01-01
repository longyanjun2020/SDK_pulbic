
#include "comdefs.hc"	/* Common define flags */
#include "rtkincl.h"
#include "sys_traces.ho"
#include "sys_sys_init.h"
#include "rtk_backtrace.h"

#include <stdlib.h>
#include <string.h>


#ifdef __RTK_DIAGNOSE_ENHANCE__
#define isValidTaskId(T)	((T < RTK_MAX_TASKS || T == RTK_MBOX_HISTORY_IRQ_SENT || T == RTK_MBOX_HISTORY_FIQ_SENT || T == RTK_MBOX_HISTORY_NOT_RECEIVED))
#else //__RTK_DIAGNOSE_ENHANCE__
#define isValidTaskId(T)	((T < RTK_MAX_TASKS))
#endif //__RTK_DIAGNOSE_ENHANCE__



#ifdef __GKI_HEAP__

typedef struct _KmHeapStatusInfo_t
{
	u32 freeDynamicMemory;
	u16 freeDynamicMemoryBlockCount;
	u32 maxFreeBlockSize;
	u32 totalDynamicMemoryAllocated;
	u32 maxTotalDynamicMemoryAllocated;
	u16 totalDynamicMemoryBlockCount;
	u32 l1AvailBitmap;
	u32 memoryPoolOverhead;
}KmHeapStatusInfo_t;

typedef struct GkiMemPtr_t
{
	bool bCanTruncate;
	bool bTruncated;
	u32 nAlignedHead;
	u32 nAlignedEnd;
	s32 nOffsetHead;
	s32 nOffsetEnd;
	u32 nAcutalSize;
} GkiMemPtr_s;

extern u32 GkiInitHeapMemory(u32 * start, u32 size);
extern u8 GkiIsHeapMemory(void *pMem, u32 * heapArea);
extern bool GkiCheckHeapMemory(void *pMem, u32 * heapArea);
extern u8 GkiGetHeapHeaderInfo(u32 * p, u8 * taskId, u32 * lr, u32 * heapArea);
extern void *GkiGetHeapMemoryAtEnd(u32 u32RequestedSize, u32 u32lr, u8 u8TaskId, u32 * heapArea);
extern u8 GkiReleaseHeapMemory(void *pMem, u32 * heapArea, void *lr);	/*release memory in heap*/
extern u8 GkiLinkHeapMemory(void *pMem, u32 * heapArea);    /*link heap memory*/
extern bool GkiHeapGlobalStatus(KmHeapStatusInfo_t*, u32 * heapArea);
extern bool GkiHeapWalk(bool Start, rtk_HeapInfo_t *Info, u32 * heapArea);
extern void *GkiGetAproxMemory(u32 *heapArea, u32 u32RequestedSize, u32 u32lr, u8 u8TaskId, GkiMemPtr_s *memPtr);


// fix the potential allocation problem
#define __GKI_ALLOC_FIX__

#endif //__GKI_HEAP__

