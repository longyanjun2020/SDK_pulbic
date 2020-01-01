/**
* @file mae_shell_priv.h
*
* This header file declares private functions, data structures and constants used
* in class CMAE_Shell_t.
*
* MAE_Shell is a special object which is the first created object when MAE system
* starts up and exists permanently. It can be considered as the parent of all
* objects. Utilization of any other object needs to be controlled by the shell.
*
* @version $Id: mae_shell_priv.h 1684 2009-08-29 16:28:08Z zinc.chen $
*/

#ifndef __MAE_SHELL_PRIV_H__
#define __MAE_SHELL_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#ifdef __arm__
// suppress warnings for unnamed structures and unions
#pragma anon_unions
#endif // __arm__

//
// definitions
//
// max allowed instances in CMAE_Shell_t
#define SH_MAX_INSTANCE 4096 //2048
// max allowed events in CMAE_Shell_t
#define SH_MAX_EVENT 256
// default table size of the reference information for recording the owner/owned objects
#define SH_REF_TABLE_SIZE 4
// max allowed contexts in CMAE_Shell_t
#define SH_MAX_CONTEXT 16
// max debug output in a row
#define SH_MAX_DEBUG_INFO 10
// size of the history pool to store shell's activities
#ifdef MAE_LARGE_HISTORY_LOG
#define SH_HISTORY_LOG_SIZE 320
#else
#define SH_HISTORY_LOG_SIZE 32
#endif // MAE_LARGE_HISTORY_LOG

///
/// The Design of Instance IDs
///
/// Using instance id instead of using address directly provides better protection from refering to
/// an invalid object address. So that inside the shell's implementation, the addresses information
/// are converted to their instance ids before stored. But the trade-off is shell needs an additional
/// array to store the address information corresponding to those ids. Once the memory on target is
/// very critical to hold these data, we may abandon this design and use only a magic number pattern
/// for the validation of object address to save the space of the instance array. Or even use nothing
/// but only the address itself. Using address directly can not detect problems at run time, but it
/// reduces the size of instance header and uses less memory.
///
/// The instance id is provided to identify different objects, even the object has been released, or
/// another new object uses the same address. And an instance id shall be able to be converted to
/// the address of the object it stands for.
///
/// According to these requirements, the instance id consists of a 16-bit index with a 16-bit sequence
/// number. The higher 16-bit is the index to the instance array, and the lower 16-bit is the sequence
/// id that identifies the address of a specific time.
///
/// In addition to the instance array, the id information is also stored in instance's header. The
/// header is prefixed to the object's structure when it is allocated and is invisible to others. It
/// provides a cross reference for instance validation. But MAE also has multi-inherited objects which
/// complicates the implementation. A multi-inherited object contains two or more interfaces (or says,
/// virtual function tables) in its structure. The structure will be allocated with only one instance
/// header, but we need header for each interface for shell's manipulation.
///
/// To accomplish the implementation of multi-inherited objects, the inherited interfaces except the
/// first one shall be declared using specific macro which also declares the instance header. The
/// instance id has also a variation for these inherited interfaces. A straightforward and clear way
/// is to assign a new id for each inherited interface when they are created, but this costs more
/// instance slots for an object. And it also needs to "release" those extra headers.
///
/// Another approach is to use dummy ids for these inherited interfaces. The first interface of the
/// object which is called the multi-inheritance base uses normal instance id. Other interfaces of the
/// object use the 16-bit index of the base but set the significant bit as their index. And the lower
/// 16-bit of their ids become the offset to the base in object's structure. The problem of dummy ids
/// is that it looks a little weird comprising offset in ids, and the offset is limited to 64K.
/// Although it's far enough for current object implementation. Also a wrong id might cause the offset
/// exceeds the valid address range. But since the id is wrong, it may not be a big problem that it's
/// shell to raise exception or the hardware system.
///

// macro defines the bits of the sequence number or structure offset of an instance
#define SH_INSTANCE_SID_BITS 16
// macro to compose the instance id
#define SH_COMPOSE_INSTID(_index_, _sid_) ((_index_ << SH_INSTANCE_SID_BITS) | _sid_)
// macro to decompose the instance id to index
#define SH_INSTID_TO_INDEX(_instid_) (_instid_ >> SH_INSTANCE_SID_BITS)
// macro defines the mask for inherited index
#define SH_INHERITED_INDEX_MASK ((u32)0x8000)
// macro to check whether it's an index for a multi-inherited interface
#define SH_IS_INHERITED_INDEX(_index_) (_index_ & SH_INHERITED_INDEX_MASK)
// macro to check whether it's an instance id of a multi-inherited interface
#define SH_IS_INHERITED_INSTID(_instid_) (_instid_ & (SH_INHERITED_INDEX_MASK << SH_INSTANCE_SID_BITS))
// macro converts an inherited index to its base index
#define SH_INHERITED_TO_BASE_INDEX(_index_) (_index_ & ~SH_INHERITED_INDEX_MASK)
// macro converts a base index to its inherited index
#define SH_BASE_TO_INHERITED_INDEX(_index_) (_index_ | SH_INHERITED_INDEX_MASK)
// macro defines the mask for the offset of a multi-inherited interface
#define SH_INHERITED_OFFSET_MASK 0xFFFF
// macro to decompose the instance id of a multi-inherited interface to its offset
#define SH_INSTID_TO_OFFSET(_instid_) (_instid_ & SH_INHERITED_OFFSET_MASK)
// macro defines the max offset of a multi-inherited interface to the address of its base interface
#define SH_MAX_INHERITED_OFFSET 0x1000
// MAE_Shell uses 16-bit index with 16-bit sequence number to identify the instances
// so that it can't support more than 65536 instances
#if SH_MAX_INSTANCE > (1 << (32 - SH_INSTANCE_SID_BITS))
#error MAE_Shell cannot support more than 65536 instances.
#endif
// special instance ids used in context handling
// these ids are invalid since slot 0 is always reserved for shell and it has a fixed sequence id
#define SH_CONSTRUCTING_INSTID 0x00000001

// bits of pending event counter in the instance header
// the number shall never be larger than 12 bits; otherwise, the instance header needs to be redefined
// and the size of sh_held counter may need to be increased also
#define SH_PENDING_EVENT_BITS 9
// the counter shall be able to store max possible number of pending events
#if (SH_MAX_EVENT >= (1 << SH_PENDING_EVENT_BITS)) || (SH_PENDING_EVENT_BITS > 12)
#error Pending events in queue might exceed the number that the counter in instance header can hold.
#endif

/// masks for event handling status
#define SH_ST_HANDLING_EVENT	0x0001


//
// private types and structures
//
// array for the allocated instances
typedef struct
{
    // address of allocated instances
    void* pInsts[SH_MAX_INSTANCE];
    // available slots in insts[]
    u16 nAvails[SH_MAX_INSTANCE];
    // index to the last available slot
    s16 nAvailIdx;
    // the sequence number of allocated instances
    u16 nSeqId;
} SHInstArray_t;

// structure of element in reference table for memory leak detection
typedef struct
{
    MAEInstId_t nId;
    u32 nCount;

} SHRefInfo_t;

// reference information (owner and owned objects) of an object for memory leak detection
typedef struct
{
    SHRefInfo_t *pList;
    u16 nSize;
    u16 nIndex;
} SHRefTable_t;


/// header of each instance
typedef struct
{
    MAEInstId_t nInstId;

    union
    {
        /// status of an object
        struct
        {
            /// counter of pending events in queue of this object
            u16 nPendingEvents: SH_PENDING_EVENT_BITS; // it shall be never larger than 16 bits
            /// indicates that it is a handler class
            u16 nHandlerClass: 1;
            /// indicates that it is handling an event
            u16 nHandlingEvent: 1;
            /// indicates that it is a multi-inherited object which shares its header with other inherited interfaces
            u16 nMultiInherited: 1;

            MAEClsId_t nClsId; ///< class id of this instance
        };

        /// the instance id of the multi-inheritance base of a multi-inherited interface
        /// a non-base inherited interface can not be an IHandler and it won't need the status above
        u32 nBaseId;
    };

#ifdef __MAE_LEAK_DETECTION__
    SHRefTable_t tOwner; ///< table contains the owners of this instance
    SHRefTable_t tOwned; ///< table contains the instances belong to this one
    u16 nShHeld; ///< reference counts held by shell for the queued callbacks or cleanup functions
#endif // __MAE_LEAK_DETECTION__
#ifdef 	__PC_SIMULATOR__
    char aFileName[100];
    u16	 nLine;
    MAEClsId_t nOwnerClsId;
#endif
} SHInstHeader_t;

// data for events
typedef struct
{
    u32 nEvt;
    MAEInstId_t nInstId;
    MAEInstId_t nIssuerId;
    u32 nLParam;
    u32 nDParam;

    union
    {
        PfnEventCleanup pfnClean;
        PfnResumeCallback pfnResume;
        PfnResumeCallbackEx pfnResumeex;
        void *ptr;
    };
} SHEventData_t;

// queue for posted events
typedef struct
{
    SHEventData_t tEvts[SH_MAX_EVENT];

    u16 nFirst; /// index to the first event waiting for processing
    u16 nLast; /// index to an empty slot for the next event

    u16 nStatus; /// status of event handling
} SHEventQueue_t;

// stack of context which are the instances in processing
typedef struct
{
    MAEInstId_t nIds[SH_MAX_CONTEXT];
    u16 nIndex;
} SHContext_t;

// the element of shell's history log
typedef struct
{
    union
    {
        // the instances may not exist after they are logged, so that only the class ids are stored
        struct
        {
            u32 nEvtId;
            MAEClsId_t nInst;
            MAEClsId_t nIssuer;
            u32 nParam[2];
        } evt;

        struct
        {
            u32 nMsgId;
            u32 nHandler;
        } msg;

        struct
        {
            u32 nFileId;
            u32 nLine;
            u32 nInfo[2];
        } status;

        struct
        {
            u32 nBtrace;
            u32 nParam[3];
        } exception;
    };
} SHHistoryItem_t;

// a log structure for storing the history of shell's activities
typedef struct
{
    s32 nIndex; ///< index to next log position
    u8 nType[SH_HISTORY_LOG_SIZE]; ///< type of the logged info

    u32 nTimeStamp[SH_HISTORY_LOG_SIZE]; ///< time stamp of logged item (in system tick, 4.615 ms)
    SHHistoryItem_t tItem[SH_HISTORY_LOG_SIZE];
} SHHistoryInfo_t;

// structure for the class info table of each class category
typedef struct
{
    const MAE_ClassInfo_t *tInfo; ///< class info array of the specific category
    u16 nCount; ///< total items of the class info array
} SHClassCategory_t;


// enums for logging encountered errors/warnings status in specific files
enum
{
    SH_FILE_SHELL,
    SH_FILE_APM,
    SH_FILE_MSGDISPATCHER
};

// commands for storing extra information in backtrace when shell triggers exceptions
enum
{
    SH_BTRACE_UNRELEASED_LIST,
    SH_BTRACE_OWNER_LIST,
    SH_BTRACE_OWNED_LIST
};


//
// private functions
//
// AddRef()
u32 MAE_Shell_AddRef(IShell*);
// Release()
u32 MAE_Shell_Release(IShell*);
// QueryInterface()
MAERet_t MAE_Shell_QueryInterface(IShell*, MAEIId_t, void**, IBase*);
// RegisterClassCategory()
MAERet_t MAE_Shell_RegisterClassCategory(IShell*, MAEClsId_t, const MAE_ClassInfo_t*, u16);
// CreateInstance()
#ifdef __PC_SIMULATOR__
MAERet_t MAE_Shell_CreateInstance(IShell*, MAEClsId_t, void**, IBase*, int, char*);
#else
MAERet_t MAE_Shell_CreateInstance(IShell*, MAEClsId_t, void**, IBase*);
#endif
// SendEvent()
MAERet_t MAE_Shell_SendEvent(IShell*, IHANDLER*, MAEEvent_t, u32, u32);
// PostEvent()
MAERet_t MAE_Shell_PostEvent(IShell*, IHANDLER*, MAEEvent_t, u32, u32);
// PostEventEx()
MAERet_t MAE_Shell_PostEventEx(IShell*, IHANDLER*, MAEEvent_t, u32, u32, u32, PfnEventCleanup);
// SubstSendEvent()
MAERet_t MAE_Shell_SubstSendEvent(IShell*, IBase*, IHANDLER*, MAEEvent_t, u32, u32);
// SubstPostEvent()
MAERet_t MAE_Shell_SubstPostEvent(IShell*, IBase*, IHANDLER*, MAEEvent_t, u32, u32);
// SubstPostEventEx()
MAERet_t MAE_Shell_SubstPostEventEx(IShell*, IBase*, IHANDLER*, MAEEvent_t, u32, u32, u32, PfnEventCleanup);
// Resume()
MAERet_t MAE_Shell_Resume(IShell*, IBase*, IBase*, PfnResumeCallback, u32);
// ResumeEx()
MAERet_t MAE_Shell_ResumeEx(IShell*, IBase*, IBase*, PfnResumeCallbackEx, u32);
// Cancel()
MAERet_t MAE_Shell_Cancel(IShell*, IBase*, IBase*, void*);
// CurrentContext()
IBase *MAE_Shell_CurrentContext(IShell*);
// SetDefaultHandler()
PfnDefEventHandler MAE_Shell_SetDefaultHandler(IShell*, PfnDefEventHandler);
// UpdateScreen()
MAERet_t MAE_Shell_UpdateScreen(IShell*);
// CreateTimer()
MAERet_t MAE_Shell_CreateTimer(IShell*, s32, PfnMAE_Notify, void*);
// CreateTimerEx()
MAERet_t MAE_Shell_CreateTimerEx(IShell*, s32, PfnTimerCallbackEx, void*,  void*);

MAERet_t MAE_Shell_CreatePeriodicTimer(IShell *pIShell, s32 mSecs, PfnTimerCallbackEx pFunc, void *pOwner, void* userData);

MAERet_t MAE_Shell_CreatePowerSaveTimer(IShell *pIShell, s32 mSecs, PfnTimerCallbackEx pFunc, void *pOwner, void* userData);
// CancelTimer()
MAERet_t MAE_Shell_CancelTimer(IShell*, PfnMAE_Notify, void*);
// CancelTimerEx()
MAERet_t MAE_Shell_CancelTimerEx(IShell*, PfnTimerCallbackEx, void*);
// IsTimerActive()
boolean MAE_Shell_IsTimerActive(IShell *pIShell, void* pFunc, void *pOwner);
// Shutdown()
void MAE_Shell_Shutdown(IShell*, boolean);
// Suspend Anim Timer
MAERet_t MAE_Shell_PausePowerSaveTimer(IShell *pIShell);
// Resume Anim Timer
MAERet_t MAE_Shell_ResumePowerSaveTimer(IShell *pIShell);

// RegisterMessage()
MAERet_t MAE_Shell_RegisterMessage(IShell*, IBase*, MAE_MsgBase_e, PfnInterface);
// DeregisterMessage()
MAERet_t MAE_Shell_DeregisterMessage(IShell*, IBase*, MAE_MsgBase_e, PfnInterface);
// HookMessage()
MAERet_t MAE_Shell_HookMessage(IShell*, IBase*, MAE_MsgBase_e, PfnHookHandler);
// UnhookMessage()
MAERet_t MAE_Shell_UnhookMessage(IShell*, IBase*, MAE_MsgBase_e, PfnHookHandler);
// Execallback()
static MAERet_t MAE_Shell_ExeCallBack(IShell*, IBase*, u32, PfnResumeCallback);
// PushContext()
static MAERet_t MAE_Shell_PushContext(IShell *pShell, IBase *pOwnr);
// PopContext() pair with PushContext()
static void MAE_Shell_PopContext(IShell *pShell);
// GetInstanceClsId()
static u16 MAE_Shell_GetInstanceClsId(IShell *pShell, IBase *pObj);

static u32 MAE_Shell_GetInstIdByAddress(IShell *pShell, IBase *pObj);

static IBase * MAE_Shell_GetAddressByInstId(IShell *pShell, u32 nInstId);

static MAE_Ret MAE_InstanceCheckValid(IShell *pShell, IBase *pObj, MAE_ClsId nClsId);

static void MAE_Shell_CloseEmbeddedApp(IShell *pShell, u32 nClsId);

static void MAE_Shell_SendToEmbeddedApp(IShell *pShell, u32 nParam1, u32 nParam2, PfnCleanup pfnCleanup);

// ZINC: function names to be modified...
// LoadResString()
u32 MAE_Shell_LoadResString(const u32, u16**);

u32 MAE_Shell_LoadResStringWithLangID(const u32, MAE_LANG_CODE_e, u16**);
// LoadPreDefinedResAsImage()
MAE_Ret MAE_Shell_LoadPreDefinedResAsImage(const u32, IIMAGE**, IBase*);
// LoadUserDefinedResAsImage()
MAE_Ret MAE_Shell_LoadUserDefinedResAsImage(u16*, IIMAGE**, IBase*);
// LoadPreDefinedResAsBitmap()
MAE_Ret MAE_Shell_LoadPreDefinedResAsBitmap(const u32, IBITMAP**, IBase*);
// LoadUserDefinedResAsBitmap()
MAE_Ret MAE_Shell_LoadUserDefinedResAsBitmap(u16*, IBITMAP**, IBase*);
// FreeRes()
MAE_Ret MAE_Shell_FreeRes(IBase*);
//LoadActivePreDefinedResAsImage()
MAE_Ret MAE_Shell_LoadActivePreDefinedResAsImage(const u32, IIMAGE**, IBase*);

//Query if the base object is applet based.
boolean MAE_Shell_IsAppletBased(IShell*, IBase*);

MAE_Ret MAE_Shell_AutoRotate(IShell *pShell, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);
u16 MAE_Shell_GetTopOrientation(IShell *pShell, IBase*);

// it verifies the address of an object and returns its header
SHInstHeader_t *MAE_VerifyAddress(void *pObj);
// it verifies the instance id and returns its header
SHInstHeader_t *MAE_VerifyInstId(MAEInstId_t nInstId);
// it converts instance id to object's address and returns its instance header
SHInstHeader_t *MAE_InstIdToAddress(MAEInstId_t nInstId, IBase **ppObj);
// it converts the instance header of a multi-inherited interface to the header of its base interface
SHInstHeader_t *MAE_GetBaseInstHeader(SHInstHeader_t *hd_inherited);

// initial and terminative functions of shell's components
MAERet_t MAE_Timer_Init(void);
MAERet_t MAE_Timer_Terminate(void);
void MAE_Shell_Timer_Backtrace(void);

MAERet_t MAE_MessageDispatcher_Init(void);
MAERet_t MAE_MessageDispatcher_Terminate(void);


//
// functions used only in files of shell components
//
// it pushes an instance into the context stack
boolean _sh_PushContext(MAEInstId_t id);
// it pops current context out of stack
boolean _sh_PopContext(void);
// it returns the instance id of current context
MAEInstId_t _sh_CurrentContext(void);
// it returns the instance id of shell context
MAEInstId_t _sh_ShellContext(void);
// it calls object's AddRef method directly and increase its sh_held count
void _sh_HoldInstance(SHInstHeader_t *hd_base, IBase *p_obj);
// it calls object's Release method directly and decrease its sh_held count
void _sh_UnholdInstance(SHInstHeader_t *hd_base, IBase *p_obj);
// it determines whether the event queue is empty
boolean _sh_QueueIsEmpty(void);
// it returns the table of class categories which stores the info of all classes
const SHClassCategory_t *_sh_GetClassCategoryTable(void);

// it returns the list of all the instances in MAE platform
const SHInstHeader_t * const *_sh_GetInstanceList(void);
// it dumps shell's state information and the activity history
void MAE_Shell_DumpInfo(void);
// it writes shell's state information and the activity history to backtrace buffer for exception output
void MAE_Shell_Backtrace(void);

#ifdef __MAE_CORE_DIAGNOSIS__

// it stores info of event activities to shell's history log
void _sh_LogEvent(MAEEvent_t nEvt, MAEClsId_t nInstId, MAEClsId_t nIssuerId, u32 nLParam, u32 nDParam);
// it stores info of incoming messages to shell's history log
void _sh_LogMessage(u32 nMsgId, u32 nHandler);
// it stores abnormal status encountered in shell components to history log
void _sh_LogStatus(u32 nFileId, u32 nLine, u32 nInfo1, u32 nInfo2);
// it stores additional parameters into history log before shell triggers exceptions
void _sh_LogException(u32 nTraceCmd, u32 nParam);

#define SH_LOG_EVENT(nEvt, nInstId, nIssuerId, nLParam, nDParam) _sh_LogEvent(nEvt, nInstId, nIssuerId, nLParam, nDParam)
#define SH_LOG_MESSAGE(nMsgId, nHandler) _sh_LogMessage(nMsgId, nHandler)
#define SH_LOG_STATUS(nFileId, nLine, nInfo1, nInfo2) _sh_LogStatus(nFileId, nLine, nInfo1, nInfo2)
#define SH_LOG_EXCEPTION(nTraceCmd, nParam) _sh_LogException(nTraceCmd, nParam)

#else

#define SH_LOG_EVENT(nEvt, nInstId, nIssuerId, nLParam, nDParam)
#define SH_LOG_MESSAGE(nMsgId, nHandler)
#define SH_LOG_STATUS(nFileId, nLine, nInfo1, nInfo2)
#define SH_LOG_EXCEPTION(nTraceCmd, nParam)

#endif // __MAE_CORE_DIAGNOSIS__
extern SHInstArray_t _g_tInstance;
#endif // __MAE_SHELL_PRIV_H__
