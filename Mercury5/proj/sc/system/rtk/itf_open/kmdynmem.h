/**************************************************************************
* TTPCom Software Copyright (c) 1997-2005 TTPCom Ltd
* Licensed to TTP_CLIENT_NAME
**************************************************************************
*	$Id: //t1/stack/mainline/tplgsm/sys/gki.mod/pub/src/kmdynmem.h#1 $
*	$Revision: #1 $
*	$DateTime: 2008/06/16 10:42:44 $
*************************************************************************/
/** \file
* GKI dynamic memory manager.
* This file defines the API to the GKI's own dynamic memory manager.
**************************************************************************/

#ifndef KMDYNMEM_H
#define KMDYNMEM_H

/****************************************************************************
* Include Files
****************************************************************************/

//#include <system.h>
//#include <kicfg.h>
#include "vm_types.ht"
#include "rtk.ho"

/****************************************************************************
* Macros
****************************************************************************/

/** Calculate the actual size of a dynamic memory pool
* This macro adds an overhead for the data needed to manage the pool. There
* is no easy way to do this accurately as the size of the storage needed
* to manage the pool is dependant on the highest bit set in the required user
* size. The pre-processor does not support any way to get the highest bit set
* in a value. So just use a hardcoded overhead value of 1536 bytes. This is
* roughly enough size to manage up to 256KBytes. Beyond this size the
* management data will be using a bit of user data. */
#define M_KmMemCalcRealPoolSize(uSERsIZE)  ((uSERsIZE) + 1536)

/** KmMemoryGet assert handling.
* This macro generates an apprioriate assert based on the error returned from
* KmMemoryGet() when it fails. */
#if defined (KI_CHECK_ASSERTIONS)
#define M_KmMemoryGetFail(eRRORcODE, mEMaREA, bYTEsIZE, mEMpTR, fILEnAME, lINEnUMBER) \
KmMemoryGetFail (eRRORcODE, mEMaREA, bYTEsIZE, mEMpTR, fILEnAME, lINEnUMBER)
#else
#define M_KmMemoryGetFail(eRRORcODE, mEMaREA, bYTEsIZE, mEMpTR, fILEnAME, lINEnUMBER)
#endif

/** Maximum number of dynamic memory caller addresses.
* This define limits the number of caller addresses that can be reported in a
* #KiDynamicMemUsageCnf signal. */
#define KI_REPORT_CALLER_ADDRESSES (0x100)

//#if !defined (KI_COMMS_TASK_ID)
//# define KI_COMMS_TASK_ID 	EMMI_LOW_PRI_TASK_ID
//#endif

/****************************************************************************
* Typedefs
****************************************************************************/

/****************************************************************************
* C++ Types
****************************************************************************/

/* These are C++ types used in upper layers and in some cases
* code that interfaces to C++ */
typedef s8		  TP_SInt8;
typedef s16 	  TP_SInt16;
typedef s32 	  TP_SInt32;
typedef u8		  TP_UInt8;
typedef u16 	  TP_UInt16;
typedef u32 	  TP_UInt32;
typedef bool	  TP_Boolean;
typedef char *		TP_String; /* There is no base-type of 'String' as this
							   * may conflict with definitions of String
* on other platforms (e.g. Windows) */
typedef char		TP_Char;   /**< \note This is SIGNED as opposed to #Char which is UNSIGNED */
typedef TP_UInt16	TP_WChar;  /**< A 16 bit unicode character (wide) */

typedef TP_WChar	TP_TChar;
#define TP_PNULL	((void *) 0)

#define KI_NUM_DYN_MEM_TASKS_IN_SIG  (0x100)

typedef rtk_TaskId_t TaskId;
typedef rtk_TaskId_t KiTaskId;

/** Error Codes.
* This enumeration defines all the error codes that are used by the dynamic
* memory manager. */
typedef enum KmErrorCodeTag
{
	/** No error (0). */
	KM_ERR_OK,
		/** Dynamic memory pool alignment error (1). */
		KM_ERR_ALIGNMENT,
		/** Dynamic memory pool is too small (2). */
		KM_ERR_MIN_SIZE_DYN_MEM_POOL,
		/** Could not allocate requested size (3). */
		KM_ERR_ALLOCATION_FAILED,
		/** Memory pool pointer is invalid (4). */
		KM_ERR_BAD_DYN_MEM_POINTER,
		/** Memory allocation before pool initialisation (5). */
		KM_ERR_DYN_MEM_NOT_INITIALISED,
		/** Resizing a block failed (6). */
		KM_ERR_RESIZE_FAILED,
		/** Invalid parameter to function (7). */
		KM_ERR_INVALID_PARAMETER,
		
		KM_ERR_UNKNOWN = 127
}
KmErrorCode;

/** Memory walk data structure.
* This structure is used to hold information about a used memory block
* when walking through a memory pool. */
typedef struct KmMemoryWalkDataTag
{
/** Address of header data.
	* This is the address of the header used by the memory manager. */
	void * headerAddr;
	/** Address of user data.
	* This is the address of the user data. */
	void * userAddr;
	/** Size of block.
	* This is the size of the block including the header and any tail. */
	u32  size;
	u8	 use;
	
} KmMemoryWalkData;


/** Union of all the basic system types.
* This can be used to ensure correct alignment of data arrays that could have
* these types cast onto it. This is normally achieved by unionising this
* union with the data array, this makes sure that the data array is suitably
* aligned to allow the use of any of these types. If a new basic type is added
* to the system (i.e. in system.h) then it should be added to this union.
*/
typedef union SysBasicTypesUnionTag
{
	u8		   int8Member;
	s8		   signedInt8Member;
	u16 	   int16Member;
	s16 	   signedInt16Member;
	u32 	   int32Member;
	s32 	   signedInt32Member;
	bool	   booleanMember;
	void		*pointerMember;
	
	TP_SInt8	 tp_SInt8Member;
	TP_SInt16	 tp_SInt16Member;
	TP_SInt32	 tp_SInt32Member;
	TP_UInt8	 tp_UInt8Member;
	TP_UInt16	 tp_UInt16Member;
	TP_UInt32	 tp_UInt32Member;
	TP_Boolean	 tp_BooleanMember;
	TP_String	 tp_StringMember;
	TP_Char 	 tp_CharMember;
	TP_WChar	 tp_WCharMember;
	TP_TChar	 tp_TCharMember;
} SysBasicTypesUnion;


/** Dynamic memory usage confirm.
* This signal is used to provide information on general dynamic memory usage as
* well as some task specific dynamic memory usage. */
typedef struct KiDynamicMemUsageCnfTag
{
/** Report valid.
* This indicates if the rest of the signal is valid or not.
* The report is generated by walking through the dynamic memory pool. If
* the integrity of the dynamic memory pool is modified because of invalid
* access, this field will be FALSE. If other higher priority task requests
* dynamic memory during generation of this report, this field may be set
* to FALSE. If this is FALSE the rest of the signal should be ignored.
	* If FALSE is returned issue the #KiDynamicMemUsageReq again. */
	bool		   validReport;
	
	/** Free dynamic memory.
	* This gives the current amount of dynamic memory that is free. */
	u32 			freeDynamicMemory;
	
	/** Free memory block count.
	* This is a field indicating fragmentation status of dynamic memory. The more blocks
	* that free memory is made up of the higher the fragmentation. The higher the
	* fragmentation the less likely that a large memory request can be successfully
	* completed (even if it is less than the available free memory). */
	u16 			freeDynamicMemoryBlockCount;
	
	/** Largest free block.
	* This gives the size of the largest contiguous free block of dynamic memory. */
	u32 			maxFreeBlockSize;
	
	/** Total dynamic memory allocated.
	* This gives the total dynamic memory currently allocated including any
	* GKI and OS overheads. This also includes requested memory. */
	u32 			totalDynamicMemoryAllocated;
	
	/** Maximum total dynamic memory allocated.
	* This gives the maximum total dynamic memory historically allocated including any
	* GKI and OS overheads. This also includes requested memory. */
	u32 			maxTotalDynamicMemoryAllocated;
	
	/** Total dynamic blocks allocated.
	* This gives the total number of dynamic memory blocks allocated. */
	u16 			totalDynamicMemoryBlockCount;
	
	/** Number of valid task entries.
	* This gives the number of valid entries in the following
	* taskDynamicMemoryId, taskDynamicMemoryAllocated and
	* taskDynamicMemoryBlockCount arrays. */
	u16 			taskDynamicMemoryNumEntries;
	
#if 0
	/** Task entry GKI task id.
	* This gives the GKI TaskId for the corresponding entry in the
	* taskDynamicMemoryAllocated and taskDynamicMemoryBlockCount arrays. */
	TaskId			  taskDynamicMemoryId[KI_NUM_DYN_MEM_TASKS_IN_SIG];
	
	/** Task dynamic memory allocated.
	* This gives the current allocated dynamic memory including OS and GKI
	* overheads for the corresponding task. */
	u32 			taskDynamicMemoryAllocated[KI_NUM_DYN_MEM_TASKS_IN_SIG];
	
	/** Task dynamic memory block count.
	* This gives the current allocated dynamic memory block count for the
	* corresponding task. */
	u16 			taskDynamicMemoryBlockCount[KI_NUM_DYN_MEM_TASKS_IN_SIG];
	
	/** Number of valid caller entries.
	* This gives the number of valid entries in the following callerAddress,
	* callerDynamicMemoryAllocated and callerDynamicMemoryBlockCount arrays.
	* These arrays give information specific to the queryTask given in the
	* #KiDynamicMemUsageReq. */
	u16 			callerAddressesNumEntries;
	
	/** Caller addresses for the corresponding allocations.
	* Only the first 32 callerAddress (defined by #KI_REPORT_CALLER_ADDRESS) will
	* be reported. This gives the address of the code that calls a GKI function
	* that results in the allocation of dynamic memory. If these addresses are
	* all 0 then the #M_KiGetCallerAddress macro has not be configured for
	* this processor/toolset. */
	u32 			callerAddresses[KI_REPORT_CALLER_ADDRESSES];
	
	/** Caller dynamic memory allocated.
	* This gives the amount of dynamic memory currently allocated via the
	* corresponding caller. */
	u32 			callerDynamicMemoryAllocated[KI_REPORT_CALLER_ADDRESSES];
	
	/** Caller dynamic memory block count.
	* This gives the number of dynamic memory blocks currently allocated via
	* the corresponding caller. */
	u16 			callerDynamicMemoryBlockCount[KI_REPORT_CALLER_ADDRESSES];
#endif
	
	/** Amount of memory lost to overheads.
	* This is the amount of memory currently used in overheads to maintain
	* the memory pool. This includes the main pool information block plus
	* headers on individual blocks. */
	u32 			memoryPoolOverhead;
	
	/** Task id for caller addresses.
	* This is the GKI task id of the caller addresses. This equates to the
	* queryTask given in the corresponding #KiDynamicMemUsageReq. */
	KiTaskId		  queryTask;
	
	u32  maxQb;
	u32  avgQb;
	u32  timesQb;
	u32  totalQb;
	u32  l1AvailBitmap;
	
} KiDynamicMemUsageCnf;

typedef struct KmMemoryPtr_t
{
	bool bCanTruncate;
	bool bTruncated;
	u32 nAlignedHead;
	u32 nAlignedEnd;
	s32 nOffsetHead;
	s32 nOffsetEnd;
	void *memPtr;
	u32 nAcutalSize;
} KmMemoryPtr_s;

/****************************************************************************
* Function Prototypes
****************************************************************************/

KmErrorCode KmMemoryCreatePool (void * memArea, u32 memByteSize);
KmErrorCode KmMemoryGetAprox(void * memArea, u32 allocSize, u32 *LastallocSize, KmMemoryPtr_s *kmptr);
KmErrorCode KmMemoryGetAtEnd(void *memArea, u32 allocSize, void **memPtr);
KmErrorCode KmMemoryFree (void * memArea, void *memoryToFree);
KmErrorCode KmMemoryReSize (void * memArea, void  *memoryToResize, u32 newSize);
KmErrorCode KmMemoryGetSize (void *memoryToSize, u32 *sizeOfMemory);
void		KmMemoryGetFail (KmErrorCode errorCode, void * memArea, u32 getByteSize, void **memPtr, const char * fileName, u32 lineNumber);

bool	 KmMemoryWalkStart (void * memArea, KmMemoryWalkData * walkData);
bool	 KmMemoryWalk	   (void * memArea, KmMemoryWalkData * walkData);

void KiReportDynamicMemUsage (KiDynamicMemUsageCnf *report_p, TaskId taskid, void * memoryPool_p);

void KmDevCheck(u8* ptr, u8* start, u8* end);
void *KmCheckPrevBlock(u8* ptr, u8* start, u8* end);
void *KmCheckNextBlock(u8* ptr, u8* start, u8* end);

#endif /* KMDYNMEM_H */
/* END OF FILE */
