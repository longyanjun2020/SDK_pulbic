#ifndef __UT_UTILITY_H__
#define __UT_UTILITY_H__

#if defined(__SDK_SIMULATION__) && (_MSC_VER >= 1500)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VC_MEM_DBG
#include "memory.h"
#include "string.h"
#include "assert.h"
#define FILE_MGR_STANDALONE_DEBUG
#endif 


///#define __UT_MEMOTRY_LEAK_DUMP__	/// define it to print callstack when memory leak
#define __UT_CHECK_STATUS__      /// define it to check status flags

#undef MALLOC
#undef FREE
#undef FREEIF

#define STRLEN          strlen
#define MALLOC(size)    malloc(size)
#define MEMSET(a,v,n)   memset(a,v,n)
#define MEMCMP          memcmp
#define FREE(p)         free(p)


/// for protecting resource
void CreateSemaphores(void);
void DestroySemaphores(void);

/// for sync thread
void UT_WaitRequestThread(void);
void UT_WaitResponseThread(void);
void UT_TriggerTimerCbByIdx(u32 uCurIdx);
u32  UT_GetTimeOutCurIdx(void);


/// for memory tracking
void UT_InitTrackMem(void);
void UT_UnInitTrackMem(void);
void UT_TrackAddMem(void *pvMem);
void UT_TrackRemoveMem(void *pvMem);
void UT_DumpTrackMem(void);

/// for fake sending
u8 MsSend(u16 uDestId, void *pMsg);

#endif //__UT_UTILITY_H__
