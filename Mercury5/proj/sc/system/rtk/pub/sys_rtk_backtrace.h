/**
 *
 * @file    sys_rtk_backtrace.h
 *
 * @brief   This module defines Enchaced Backtrace Interfaces
 *
 * @author  Xavier Fan
 * @version $Id: rtk_backtrace.h 14050 2008-09-11 11:34:44Z pauli.leong $
 *
 */
#ifndef __SYS_RTK_BACKTRACE_H__
#define __SYS_RTK_BACKTRACE_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "sys_vm_dbg.ho"
#include <stdarg.h>
#include "sys_rtk_config.h"
#include "sys_rtk_ho.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __RTK_BACKTRACE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#ifndef _BACKTRACE
#ifndef	__RTK_DIAGNOSE_ENHANCE__
#define _BACKTRACE(X)
#else
#define _BACKTRACE(X)						KER_BACKTRACE_DIAGNOSE X
#endif
#endif


#ifndef _DBGINFO
#ifndef	__RTK_DIAGNOSE_ENHANCE__
#define _DBGINFO(X)
#else
#define _DBGINFO(X)							KER_DBGINFO_DIAGNOSE X
#endif
#endif


#ifndef	_RECORD_MSG_HISTORY
#ifndef	__RTK_DIAGNOSE_ENHANCE__

DefExtern __inline rtk_ErrCode_e backtrace_ToolRecordMessageInline(void) \
{ return RTK_OK; }

#define	_RECORD_MSG_HISTORY(_OP_, _MBXID_, _MSGID_) 	backtrace_ToolRecordMessageInline()
#else
#define	_RECORD_MSG_HISTORY(_OP_, _MBXID_, _MSGID_)		\
	backtrace_ToolRecordMessage((event_e)_OP_, (u8)_MBXID_, (u32)_MSGID_, (u32)__return_address())
#endif	/*	__RTK_DIAGNOSE_ENHANCE__	*/
#endif



/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* LOCAL VARIABLE DEFINITION                                                */
/*--------------------------------------------------------------------------*/


#define ENHANCED_BACKTRACE_STACK_DUMP_ID								(0xFFFF0001)
#define ENHANCED_BACKTRACE_POOL_DUMP_ID									(0xFFFF0002)
#define ENHANCED_BACKTRACE_DETAILED_POOL_NUMBER_DUMP_ID	(0xFFFF0003)
#define ENHANCED_BACKTRACE_DETAILED_POOL_DUMP_ID				(0xFFFF0004)
#define ENHANCED_BACKTRACE_HISTOGRAM_DUMP_ID						(0xFFFF0005)
#define ENHANCED_BACKTRACE_HEAP_TOTAL_DUMP_ID						(0xFFFF0006)
#define ENHANCED_BACKTRACE_HEAP_DUMP_ID									(0xFFFF0007)
#define ENHANCED_BACKTRACE_HEAP_FREE_DUMP_ID						(0xFFFF0008)
#define ENHANCED_BACKTRACE_HEAP_USED_DUMP_ID						(0xFFFF0009)
#define ENHANCED_BACKTRACE_MSG_ID												(0xFFFF000A)
#define ENHANCED_BACKTRACE_TIMESTAMP_ID									(0xFFFF000B)
#define ENHANCED_BACKTRACE_MMI_RELEASE_ID								(0xFFFF000C)
#define ENHANCED_BACKTRACE_END_ID												(0xFFFF000D)
#define ENHANCED_BACKTRACE_POOL_DUMP_ID2								(0xFFFF000E)
#define ENHANCED_BACKTRACE_FORMAT_STR_ID								(0xFFFF000F)
#define ENHANCED_BACKTRACE_M2SRAM_DUMP_ID								(0xFFFF0020)
#define ENHANCED_BACKTRACE_MMK_ID_BEGIN									(0xFFFF0010)
#define ENHANCED_BACKTRACE_MMK_ID_END										(0xFFFF001F)
#define ENHANCED_BACKTRACE_QUEMSG_DST_ID								(0xFFFF0021)
#define ENHANCED_BACKTRACE_PRCMSG_DST_ID								(0xFFFF0022)
#define ENHANCED_BACKTRACE_MSG_DUMP_ID									(0xFFFF0023)
#define ENHANCED_BACKTRACE_SEM_DUMP_ID									(0xFFFF0024)
#define ENHANCED_BACKTRACE_POOL_SIMPLE_ID								(0xFFFF0025)
#define ENHANCED_BACKTRACE_CRASH_NOTIFY_ID         			(0xFFFF0026)
#define ENHANCED_BACKTRACE_RAW_STRING_ID						(0xFFFF0012)
#define ENHANCED_BACKTRACE_COMPRESS_ID									(0xFFFF0013)

extern u32	RtkBackTraceBufferSize;
#define MAX_SYS_BACKTRACE_BUFFER_SIZE 									(RtkBackTraceBufferSize)

#ifdef __RTK_DIAGNOSE_ENHANCE__
#define R13  																						(0)
#define R14  																						(1)
#define _PC  																						(2)
#define CPSR  																					(3)
#define CUR_STACK_TO_STORE 															(512)
#define TASK_STACK_TO_STORE 														(256)
#endif
#define MAX_COUNT 2

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef enum
{
	RTK_MEM_STATUS_NOT_RAM_ADDR,
	RTK_MEM_STATUS_DESTROYED_POOL,
	RTK_MEM_STATUS_DESTROYED_HEAP,
	RTK_MEM_STATUS_NOT_ALLOCATED_POOL,
	RTK_MEM_STATUS_NOT_ALLOCATED_HEAP,
	RTK_MEM_STATUS_ALLOCATED_POOL,
	RTK_MEM_STATUS_ALLOCATED_HEAP,
	RTK_MEM_STATUS_RAM_ADDR					/* Not Heap or Pool, It might be Customer Task Stack, Zero Initialized Data */
} rtk_memStatus_e;


typedef	enum
{
	NON_EVENT	=	0,	/*	Default value									*/
	INIT_MBOX,			/*	Initial mail box debug struct	*/
	MSG_SEND,				/*	Msg send											*/
	MSG_RECEIVE,		/*	Msg receive										*/
	MSG_SEND_TIMER,		/*	Timer send											*/
	MSG_RECEIVE_TIMER,	/*	Timer receive										*/
	MSG_CANCEL,			/*	Msg canceled, ex: stop timer	*/
	MSG_FAKE,				/*	Fake msg											*/
	MSG_FINISH,			/*	Finish a message processing		*/
	RESET_WD,				/*	Indicate the time to reset WD	*/

}	event_e;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/
/*
#ifdef __RTK_DIAGNOSE_ENHANCE__
DefExtern u32	RtkRegisters[4];														// R13, R14, PC
#endif
*/

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
/* ** Note **
 * Interface to generate backtrace content
 */
void KER_BACKTRACE_DIAGNOSE(u32, char *, ...);
void KER_VBACKTRACE_DIAGNOSE(u32, char *, va_list);

/* ** Note **
 * Interface to generate debug information content
 */
void KER_DBGINFO_DIAGNOSE(u32, char *, ...);


/* ** Note **
 * Interface to generate debug information
 */
void backtrace_MmkInfo(void);
void backtrace_TskInfo(void);
void backtrace_TskTaskMgr(void);
void backtrace_MemHeapUsageHistogram(void);
void backtrace_MemHeapUsageHistogramIram(void);
void backtrace_MemListHeapBlocks(void);
void backtrace_MemListHeapBlocksIram(void);
void backtrace_MemListPoolAllocatedBlocks(void);
void backtrace_MemListPoolAllocatedBlocks_light(void);
void backtrace_MemPoolUsageHistogram(void);
void backtrace_MemTaskMemoryUsage(void);
void backtrace_MemLookupMurder(void* pMem);
void backtrace_MemLookupHeapMurder(void* pMem);
void backtrace_MemLookupPoolMurder(void* pMem);
void backtrace_MemoryHandleDump(void* pMem);
void backtrace_ScanInvalidPoolCluster(u32 poolID);
void backtrace_ListInvalidPoolCluster(u32 memPtr);
bool backtrace_MboxStatus(rtk_MailboxId_t MboxNo, u32 *limit, u32 * max, u32 * current);
void backtrace_MboxUsage(void);
void backtrace_MboxMessageHistory(void);
void backtrace_ResMgrCmdHistoryInfo(void);
void backtrace_SemSemaphoreInfo(void);
void backtrace_SysDumpRegisters(void);
void backtrace_SysDumpRegistersCollectedInArmException(void);
void backtrace_SysDumpCurTaskStack(void);
void backtrace_SysToolVersionInformation(void);
void backtrace_SysSoftwareVersion(void);
void backtrace_SysCrashNotify(void);
void backtrace_SysDebugInfo(void);
void backtrace_HW_WatchDog(void);
bool backtrace_preprocess(u8 exceptionType);
void backtrace_entry_counter_add(void);
u32 backtrace_entry_counter_check(void);
/* ** Note **
 * Interface to update the debug data,
 * these interfaces should not be called casually
 */
bool						backtrace_ToolInitBackTrace(u8 exceptionType);
bool						backtrace_ToolFinalizeBackTrace(void);
bool						backtrace_ToolSetExceptionType(u8 exceptionType);
u8							backtrace_ToolGetExceptionType(void);
u32							backtrace_ToolGetBackTraceLength(u8* pBacktrace, u32 parsedLength);
void						backtrace_ToolCheckBranchZeroException(void);
void						backtrace_ToolInitTaskMgr(u32 timerID, u8 mboxID, u32 tick);
void						backtrace_ToolSetTaskMgrConfig(bool enable, bool hide);
void						backtrace_ToolGetTaskMgrConfig(bool* pEnable, bool* pHide);
void						backtrace_ToolResetTaskMgr(bool triggerTimer);
void						backtrace_ToolUpdateTaskMgr(u8 lastTask);
rtk_ErrCode_e				backtrace_ToolRecordMessage(event_e op, u8 dstMbx, u32 msgId, u32 caller);
void						backtrace_ToolDumpToMemoryCard(void);
void						backtrace_ToolDumpToTmt(void);
void						backtrace_ToolEncryptBacktrace(u8* pPlainBacktrace, u32 plainBacktraceSize, u8** ppCipherBacktrace, u32* pCipherBacktraceSize);
void						backtrace_ToolEncryptBacktrace_light(u8* pBacktrace, u32 backtraceSize, u8** ppCipherHeader, u32* pCipherHeaderSize);
void						backtrace_ToolDecryptBacktrace_light(u8* pBacktrace, u32 cipherBacktraceSize, u32* pPlainBacktraceSize);
u32							backtrace_ToolBackupTaskLoading(u32* pBuffer, u32 len);
bool						backtrace_ToolGetBackupBacktrace(u8* ppBackup[], u32* pBackupLength);
bool						backtrace_ToolClearBackupBacktrace(void);
u32						backtrace_ToolGetMaxBacktraceSize(void);
bool 						backtrace_ToolShutdownMmpFs(u32 waitTime);
void backtrace_ListEnvelope(void);
#endif //__SYS_RTK_BACKTRACE_H__


