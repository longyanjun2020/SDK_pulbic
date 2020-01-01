
/******************************************************************/
/*  File    : RTKSRTUC.HT                                         */
/*-------------------------------------------------------------   */
/*  Scope   :  Internal RTK Structures definitions                */
/*                                                                */
/*  Contents:                                                     */
/*                                                                */
/******************************************************************/

#ifndef __SYS_RTK_HT_H__
#define __SYS_RTK_HT_H__

#include "sys_rtk_inconfig.h"
#include "comdefs.hc"   /* Common define flags */

typedef struct CallbackTimer_t_
{
	u32 UserData;
	void (*pfCB)(u32 TimerID, u32 UserData);
} CallbackTimer_t;

typedef struct ObjDescEx_t_
{
  u8 TypeOfObj;      ///< type of object (\ref rtk_ObjectType_e)
  u8 bid;
  u32 TimerID;
  CallbackTimer_t cbtimer;
} ObjDescEx_t;

/******* Timer Structure context *******/

typedef struct TimerStructure
{
    struct TimerStructure *NextPtrTimer;
    u32    Counter;
    u32    sem;
    u32    TimerID;
    u8     MailBoxNo;
    u16     SemId;
    bool   m_bool_StrictTimer;
	void   *flag_obj; 
	u32    flag_timer;
#ifdef __RTK_SEND_SUSPENSION__
    void   *mailbox_obj; 
    u32    mailbox_timer;
#endif 
#ifdef __RTK_TIMER_PERIODIC__
    bool   bCyclic;
    u32    saveCounter;
#endif
	CallbackTimer_t cbtimer;
} rtk_Timer_t;

#define LEN_rtk_Timer_t sizeof (rtk_Timer_t)


/******* System register *******/
typedef struct RegStructure
{
    void           *SP;
    void           *PC;
    void           *TopOfStack;
    u16            StackSize;
} rtk_Register_t ;

#ifdef __RTK_SEND_SUSPENSION__
#define RTK_MAILBOX_TIMER (0x6C69616D) //"mail"
#endif 

#define RTK_FLAG_GUARD (0x47414C46) //"FLAG"
#define RTK_FLAG_INITIALIZED (0x54494E49) //"INIT"
#define RTK_FLAG_DESTROY (0x74656C64) //"dlet"
#define RTK_FLAG_TIMER (0x726D6974) //"timr"

typedef enum {
  RTK_FLAG_WAITMODE_AND = (1<<0),             ///< wake up if all bits specified in the mask are set in the flag.
  RTK_FLAG_WAITMODE_OR = (1<<1),              ///< wake up if any bits specified in the mask are set in the flag.
  RTK_FLAG_WAITMODE_CLR = (1<<2),             ///< clear all bits in the flag when the condition is met. Typically,only the bits that are set in the pattern parameter are cleared.
  RTK_FLAG_WAITMODE_CLR_SET = (1<<3)          ///< clear bits specified in the mask are set in the flag when the condition is met. Typically,only the bits that are set in the pattern parameter are cleared.
} _rtk_flag_mode_e;

typedef u8 rtk_flag_mode_t;
typedef s32 rtk_flag_value_t;
typedef u32 rtk_tick_count_t;

/******* Structure d'un flag *******/
typedef struct FlagStructure
{
	s32 FlagGuard;
    rtk_flag_value_t FlagValue;
    rtk_Envelop_t *PtrFirstTask;
	s32 FlagState;
	u8 FlagId;
} rtk_Flag_t ;

typedef struct FlagWaitInfoStructure
{
	rtk_Flag_t *wait_PtrFlag;
	u32 awaken_address;
	rtk_flag_value_t wait_pattern;
	rtk_flag_value_t flag_return_value;
	rtk_flag_mode_t wait_mode;
} RtkFlagWait_info_t ;

/******* Structure d'un Mutex *******/
typedef enum
{
    PRIO_INVR_NONE = 0,
    PRIO_INVR_INHERIT,
    PRIO_INVR_CEILING
}rtk_Prio_Invr_e;

typedef struct MutexStructure
{
    bool bLocked;
    u8 uMutexCount;
    struct TaskStructure* pTaskOwner;       // Owner
    rtk_Envelop_t* PtrTaskQueue;            // Queue
    rtk_Prio_Invr_e protocol;

    // Elements for priority inversion
    u8 original_priority;
    bool priority_inherited; 
} rtk_Mutex_t ;

/*****************************************************************/
/*        !!!!!!!!!!!!!!!!! BEWARE !!!!!!!!!!!!                  */
/*                                                               */
/* if the offset of MarkerSP, Marked or Id is changed, update it */
/* in rtk2util.asm the corresponding value                       */
/*                                                               */
/*****************************************************************/

#define HEAP_GUARD_PATTERN (0x1A1B1C1D)
//magic TAIL //this value will be assign to heap tail in allocation, and it's replaced with freer in release
#define HEAP_TAIL_PATTERN (0x4C494154)
#ifdef __RTK_MEMORY_ALIGN32__
/* |-RTK_header(16 bytes)-|-payload-|-magic TAIL(4 bytes)-|-tail2<same as first 4B of RTK_header>(4 bytes)-|*/
#define HEAP_RTK_INFO_SIZE (24) 
#else
#define HEAP_RTK_INFO_SIZE (16)
#endif
#define STACK_POOL_GUARD_PATTERN (0x78787878)
#define CUSTO_POOL_GUARD_PATTERN (0x56565656)
#define DEBUG_POOL_GUARD_PATTERN (0x34343434)
#define NB_POOLS_MONITORED (16)

#define RTK_TASK_NAME_CHAR_LEN	(16)

typedef struct TaskStructure
{
    u8             State;
    u8             Priority;
    u8             TypeOfObj;
    u8             Id;
    union
    {
        u32      ObjParameter;
        void     *PtrMessage;
    } PendingObj;
    rtk_Register_t Reg;
    struct TaskStructure *PtrNextPrio;
    rtk_Timer_t   *PtrTimer;
    u32    MarkerSP;
    bool   Marked;
#ifdef __SDK_SIMULATION__
    void*         StartAddress;
    void*         ThreadID;
    void*         ThreadHwnd;
    void*         Event;         // for Win32 priority trace
    u32           startRunning;  // record if it's started 	
    u32           bIsSuspend;    // record if it's started 
    u32           bIsThreadInit; // record if it's started 
#endif //__SDK_SIMULATION__
  u8 bitmapIndex;
  u8 bitmapMask;
#ifdef RTK_EQUAL_PRIORITY_TASK
  u8 IndexOfBitmapIdx2task;
#endif
#ifdef __RTK_SEND_SUSPENSION__
  u8 WaitSendMailBoxNo;
#endif
  rtk_SemId_t WaitSemID;
  bool   userOwnCallStack;
#if 0
	u16 poolNbBlock[NB_POOLS_MONITORED];			/* current allocated blocks in each pool */
	u16 poolMaxBlock[NB_POOLS_MONITORED];			/* maximum allocated blocks in each pool */
	u16 cusPoolNbBlock[NB_POOLS_MONITORED];		/* current allocated blocks in each pool */
	u16 cusPoolMaxBlock[NB_POOLS_MONITORED];	/* maximum allocated blocks in each pool */
	u16 heapCurBlocks;												/* current allocated blocks from heap */
	u16 heapMaxBlocks;												/* maximum allocated blocks from heap */
	u32 heapCurTotalSize;											/* current allocated size from heap */
	u32 heapMaxTotalSize;											/* maximum allocated size from heap */
	u32 heapMaxBlockSize;											/* maximum single block size from heap */
#endif //__RTK_DIAGNOSE_ENHANCE__
#ifdef __LOGIC_ANALYSER__
  u8 PreviousState;
#else
  //u8 padding1;
#endif /* __LOGIC_ANALYSER__ */    
	RtkFlagWait_info_t flag_wait_info; 
#ifdef RTK_EQUAL_PRIORITY_TASK
    struct TaskStructure *PtrNextSamePrio;
#endif

    rtk_Envelop_t* pOwnedMutex;
     rtk_Mutex_t  * pWaitMutex;

    u32 userData;

    char TaskName[RTK_TASK_NAME_CHAR_LEN];
    u32 scheduledOutTime;
    
#if defined(__TIME_SLICE_SCHEDULE__)
    u32 ScheduleInTime;
    u32 TimeSliceMax;
    u32 TimeSliceLeft;
#endif
} rtk_Task_t;

#define LEN_rtk_Task_t sizeof (rtk_Task_t)

/******* Structure d'un Semaphore *******/

typedef struct SemStructure
{
    s16         CurrentValue;
    s16         InitValue;
    rtk_Envelop_t *PtrFirstTask;
} rtk_Semaphor_t ;

#define LEN_rtk_Semaphor_t sizeof (rtk_Semaphor_t)

/******* Structure d'une BAL *******/

typedef struct MBoxStructure
{
    rtk_Envelop_t *PtrFirstTask;          /* first task which is waiting to receive this mailbox */
    rtk_Envelop_t *PtrLastTask;           /* last task which is waiting to receive this mailbox */
    rtk_Envelop_t *PtrLastObj;             /* last object which is hung on this mailbox */
    rtk_Envelop_t *PtrObjQue;              /* first object which is hung on this mailbox */
#ifdef __RTK_SEND_SUSPENSION__
    rtk_Envelop_t *PtrSendFirstTask;  /* as curMsgNum>=limitMsgNum of this mailbox, the first task which is waiting to send to it */
    rtk_Envelop_t *PtrSendLastTask;   /* as curMsgNum>=limitMsgNum of this mailbox, the last task which is waiting to send to it */
    u16             curMsgNum;		/* current number of unprocessed message */
    u16             maxMsgNum;		/* maximum number of unprocessed message in history */
    u16             limitMsgNum;	/* limitation of number of unprocessed message which will cause an exception raised */
    u16             padding;
#endif
#ifdef RTK_MAILBOX_THRESHOLD_CHECK
    u8              Threshold;  //a value of 1~99. it's used to determine msg can be sent or not if calling MsSendWithThreshold
    u8              padding1;
    u8              padding2;
    u8              padding3;
#endif
} rtk_Mailbox_t;

#define LEN_rtk_Mailbox_t sizeof (rtk_Mailbox_t)

/******* Structure d'un Pool de memoire *******/

typedef struct PoolStructure
{
    rtk_Envelop_t *PoolEnv;
    u16    ClusterLength;
#ifdef __RTK_DIAGNOSE__
    void   *ClusterStart;
    u16    NbCluster;
    u16    FreeCluster;
    u16    UsedCluster;
    u16    MaxUsed;
#endif
    u16 NeedProtect;
} rtk_Pool_t;

#define LEN_rtk_Pool_t sizeof (rtk_Pool_t)

/******* Structure d'un Cluster *******/

typedef struct MemOverhead
{
    u8  PoolStructNum;
    u8  Linkcounter;
#ifdef __RTK_DIAGNOSE__
    u16 RealSize;
    u32 Caller;
    u8  Owner;
    u8  HistIdx;
#endif
    u16 BaseAdr;
    u32 padding;    /*for 8 bytes alignment*/
} rtk_MemOverhead_t;

#ifdef __RTK_DIAGNOSE__
typedef struct HistArray
{
    u16  NbHeap;		// current usage of heap
    u16  NbAlloc;		// current usage of 'not total fit' pool 
    u16  NbBlock;		// current usage of pool ('not total fit' + 'total fit')
    u16  MaxBlock;	// max pool usage
} rtk_HistArray_t;
#endif

/******* Structure used for InitKernel *******/

typedef struct PoolInitStructure
{
    u16 ClusterLength;
    u16 NbOfCluster;
    u8  *PtrOfPool;
    u8 NeedProtect;
} rtk_PoolInit_t;

/******* Structure used for InitKernel *******/

typedef struct rtk_KernelInit
{
    u8                             *DataAreaPtr;
    u8                             rtkNbOfTask;
    u8                             rtkNbOfMailBox;
    u16                            rtkNbOfSemaphor;
    u8                             rtkNbOfTimer;
    u16                            rtkNbOfEnvelop;
    u16                            rtkNbOfPool;
    rtk_PoolInit_t                 *PtrPoolDesc;
    u16                            rtkNbOfCusPool;
    rtk_PoolInit_t                 *PtrCusPoolDesc;
} rtk_KernelInit_t;


/******* Structure used for InitTask *******/

typedef struct rtk_TaskInit
{
    u8  rtkTaskNumber;
    u8  rtkTaskPriority;
    void (*rtkStartAdress) _PROTO((void));
    u16  rtkTaskStackLength;
    void *rtkTaskStack;
    void *rtkTopOfStack;
    char rtkTaskName[16];
    u32 userData;
#if defined(__TIME_SLICE_SCHEDULE__)
    u32 TimeSliceLeft;
    u32 TimeSliceMax;
#endif
} rtk_TaskInit_t;

#define LEN_rtk_MemOverhead_t sizeof (rtk_MemOverhead_t)


/******* Structure used for heap *******/

/* to get info when walking the heap */
typedef struct {
    u32  Size;
    bool Free;
    u8   Id;
    u16 isVMA;
    u32  Lr;
    u32  Date;
    u32  Time;
    u32  Addr;
} rtk_HeapInfo_t;

/* Storage structure for heap statistics */

typedef struct
{
   u32   Free;
   u32   HeapTop;
   u16   NbFree;
   u16   NbAlloc;
} rtk_StatHeap_t;

#if defined (__GKI_HEAP__) && (defined( __GKI_MEM_PTR_CHECK__) || defined(__MEM_CHECK_TOOL___))
typedef struct {
	rtk_HeapInfo_t rtk_heapInfo;
	u32 gki_headAdd;
	u32 gki_userAdd;
	u32 gki_corrupt_add;
}gki_HeapInfo_t;
#endif

#ifdef __MEM_CHECK_TOOL___

/*!
 *  \brief memory type for memory check tool
 */
typedef enum {
  RTK_POOL = 0,                  // Pointer on a Pool memory
  RTK_HEAP,                      // Pointer on a Heap memory
} rtk_Mem_Type_e;


/*!
 *  \brief check info structure for memory check tool
 */
typedef struct{
	u32 memType;
	u32 addStart;
	u32 addEnd;
	u32 lr;
}rtk_mem_check_info_t;

/*!
 *  \brief return value for memory check tool
 */
 typedef enum {
  MEM_CHK_NA =    -2,  ///< the given mem pointer is not belong to pool nor heap
  MEM_CHK_FAIL,        ///< check function fail
  MEM_CHK_OK           ///< check function succsess
} rtk_Mem_Check_e;
#endif


/******* Memory context structure *******/
#ifdef __SDK_SIMULATION__
typedef struct rtk_memoryContext
#else //__SDK_SIMULATION__
typedef struct
#endif //__SDK_SIMULATION__
{
  /* Heap */
  u32 huge        *rtk_HeapTop;
  u32 huge        *rtk_HeapEnd;
  u32 huge        *rtk_HeapStart;
  
  /* Pool */
  u32             Rtk_MaxPoolSize;
  u8               Rtk_NbOfPool;
  u8 huge         *Rtk_Ptr1stPoolMem;
  u8 huge         *Rtk_PtrLastPoolMem;

  rtk_Pool_t      *Rtk_PtrPoolDesc;

#ifndef __GKI_HEAP__
  u8              rtk_HeapWalkIdx;
  u32 huge        *rtk_HeapWalkStack[16];
#endif

#ifdef __RTK_DIAGNOSE__
#ifndef __GKI_HEAP__
  /* Statistics */
  u32             rtk_HeapFree;
  u32             rtk_RemainingHeapSize;   /* same as rtk_HeapFree, BUT KEEP TEMPORARY THIS VAR FOR WAP_OS.C !!! */
  u32             rtk_LowestHeapSize;      /* same as rtk_LowestFree.Free, BUT KEEP TEMPORARY THIS VAR FOR WAP_OS.C !!! */

  /*
  ** Nb free blocks in heap memory between rtk_HeapStart and rtk_HeapTop
  */
  u16             rtk_HeapNbFree;

  /*
  ** Nb allocated blocks in heap memory between rtk_HeapStart and rtk_HeapTop
  */
  u16             rtk_HeapNbAlloc;
  
  /*
  ** Customer Heap Statistics
  */

  rtk_StatHeap_t  rtk_LowestFree;
  rtk_StatHeap_t  rtk_HighestNbFreeBelowTop;
  rtk_StatHeap_t  rtk_HighestTotalFreeBelowTop;
#endif

#if defined(__KERNEL_DEBUG__)
  rtk_HistArray_t Rtk_HistArray[255];
#endif

#endif  //__RTK_DIAGNOSE__
  
}rtk_memoryContext_t;  

#ifndef __RTK_DIAGNOSE_ENHANCE__
typedef struct {
   u16 MbxSrc;
   u16 MbxDst;
   u16 Length;
   u16 TypMsg;
   u32 FN;
} rtk_MessageSave_t;
#endif

typedef struct
{
	void*	TopOfStack;
 	u16		StackSize;
	u32		MaxUsage;
    char	TaskName[RTK_TASK_NAME_CHAR_LEN];
} rtk_StackInfo_t;

#define RTK_MBOX_HISTORY_NOT_RECEIVED		0xFF
#define RTK_MBOX_HISTORY_IRQ_SENT				0xFD
#define RTK_MBOX_HISTORY_FIQ_SENT				0xFC

#ifndef __RTK_DIAGNOSE_ENHANCE__
extern rtk_MessageSave_t MessageSave[];
extern u8 MessageSaveIndex;
#endif

#endif          /* __SYS_RTK_HT_H__ */

