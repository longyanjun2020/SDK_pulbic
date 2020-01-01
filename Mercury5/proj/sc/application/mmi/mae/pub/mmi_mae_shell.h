/**
* @file mmi_mae_shell.h
*
* This header file defines the IShell interface, and exposes the global object
* MAE_Shell for all the components in MAE platform.
*
* @version $Id: mmi_mae_shell.h 1836 2009-09-25 06:35:26Z kenny.wu $
*/

#ifndef __MMI_MAE_SHELL_H__
#define __MMI_MAE_SHELL_H__

// verify the definitions
// __MAE_LEAK_DETECTION__ shall be defined only if __MAE_CORE_DIAGNOSIS__ is defined
#ifdef __MAE_LEAK_DETECTION__
#ifndef __MAE_CORE_DIAGNOSIS__
#error __MAE_LEAK_DETECTION shall be defined only if __MAE_CORE_DIAGNOSIS__ is also defined
#endif // __MAE_CORE_DIAGNOSIS__
#endif // __MAE_LEAK_DETECTION__

// __MAE_CYCLIC_DETECTION__ shall be defined only if __MAE_LEAK_DETECTION__ is defined
#ifdef __MAE_CYCLIC_DETECTION__
#ifndef __MAE_LEAK_DETECTION__
#error __MAE_CYCLIC_DETECTION__ shall be defined only if __MAE_LEAK_DETECTION__ is also defined
#endif // __MAE_LEAK_DETECTION__
#endif // __MAE_CYCLIC_DETECTION__

//
// header files
//
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell_forward.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_apm.h"
#include "mmi_mae_apm_forward.h"
#include "mmi_mae_apm_types.h"
#include "mmi_mae_msgdispatcher.h"
#include "mmi_mae_langcode.h"

#define ASSERT_IF_CROSS_TASK_CALL()   MAE_AvoidCrossTaskCall()

#ifdef __MAE_DEBUG_SHELL__
void log_add_MAEEvt(MAEClsId_t nSrcClsId,MAEClsId_t nDstClsId, MAEEvent_t nEvt, u32 nLParam, u32 nDParam, u8 nEvtType);
#define LOG_ADD_MAE_EVT(nSrcClsId, nDstClsId, nEvt, nLParam, nDParam, nEvtType)  log_add_MAEEvt(nSrcClsId, nDstClsId, nEvt, nLParam, nDParam, nEvtType)
typedef struct
{	
    u8 nType;
    MAEEvent_t nEvtId;
    MAEClsId_t nDstClsId;
    MAEClsId_t nSrcClsId;
    u32 nParam[2];
    u32 nShellTimeStamp;
} SHELL_EventLogElem_t;

typedef struct 
{
    SHELL_EventLogElem_t Logs[SHELL_LOG_AMOUNT];
    u8 nPos;      
}  SHELL_EventLogInfo_t;
#else
#define LOG_ADD_MAE_EVT(nSrcClsId, nDstClsId, nEvt, nLParam, nDParam, nEvtType)
#endif

enum
{
    SH_EMPTY_LOG = 0,
    SH_EVENT_LOG,
    SH_MESSAGE_LOG,
    SH_STATUS_LOG,
    SH_EXCEPTION_LOG
};

#ifdef __PC_SIMULATOR__
#define ELEAK_DUMPFILE
#endif
/**
* Type of the instance id for each object created in MAE platform.
*/
typedef u32 MAEInstId_t;

/**
* Prototype of the function to be passed as a parameter in PostEventEx(). It will be called
* after shell processes the posted event to clean up the allocated memory of that event.
*/
typedef void (*PfnEventCleanup)(IBase *pIssuer, u32 nLParam, u32 nDParam);

/**
* Prototype of the function for asynchronous procedure call. It is assigned to an object and
* scheduled to be executed under the object's context.
*/
typedef void (*PfnResumeCallback)(IBase *pObj, u32 nParam);

/**
* Prototype of the function for asynchronous procedure call. It provides additional pIssuer
* parameter so that the issuer can pass objects to the destination and release those objects
* in the callback function.
*/
typedef void (*PfnResumeCallbackEx)(IBase *pIssuer, IBase *pObj, u32 nParam);

/**
* Prototype of default event handler. The default handler in shell will be called when an event
* without specifying a destination is not handled.
*/
typedef boolean (*PfnDefEventHandler)(MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

/**
* Prototype of timer callback_Ex. The callback would pass two parameters including userdata comparing
* to PfnMAE_Notify
*/
typedef void (*PfnTimerCallbackEx)(void *pUser, void *pUserData);

/**
* Prototype of the function to be passed as a parameter in SendToEmbeddedApp(). It will be called
* after shell processes the posted event to clean up the allocated memory of that event.
*/
typedef void (*PfnCleanup)(IBase *pIssuer, u32 nLParam, u32 nDParam);



/*
// incomplete types to avoid mutually included headers
typedef struct IHandler_tag IHANDLER; ///< for handler related methods
typedef struct IApplet_tag IAPPLET; ///< for applet related methods
typedef struct IImage_tag IIMAGE; ///< for resource methods
typedef struct IBitmap_tag IBITMAP; ///< for resource methods
*/
#ifdef __PC_SIMULATOR__
#define CREATEINST(IName) \
    MAERet_t (*CreateInstance)(IName *pShell, MAEClsId_t nClsId, void **ppObj, IBase *pOwner, int line, char* filename)
#else
#define CREATEINST(IName) \
    MAERet_t (*CreateInstance)(IName *pShell, MAEClsId_t nClsId, void **ppObj, IBase *pOwner)
#endif


//
// IShell interface
//
// methods of IShell interface
#define INHERIT_IShell(IName) \
    INHERIT_IBase(IName); \
    MAERet_t (*RegisterClassCategory)(IName *pShell, MAEClsId_t nClsIdBase, const MAE_ClassInfo_t *pClsInfoTable, u16 nCount); \
    CREATEINST(IName);\
    MAERet_t (*SendEvent)(IName *pShell, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam); \
    MAERet_t (*PostEvent)(IName *pShell, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam); \
    MAERet_t (*PostEventEx)(IName *pShell, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam, u32 nMode, PfnEventCleanup pfnClean); \
    MAERet_t (*SubstSendEvent)(IName *pShell, IBase *pIssuer, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam); \
    MAERet_t (*SubstPostEvent)(IName *pShell, IBase *pIssuer, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam); \
    MAERet_t (*SubstPostEventEx)(IName *pShell, IBase *pIssuer, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam, u32 nMode, PfnEventCleanup pfnClean); \
    MAERet_t (*Resume)(IName *pShell, IBase *pIssuer, IBase *pDest, PfnResumeCallback pfnCb, u32 nParam); \
    MAERet_t (*ResumeEx)(IName *pShell, IBase *pIssuer, IBase *pDest, PfnResumeCallbackEx pfnCb, u32 nParam); \
    MAERet_t (*Cancel)(IName *pShell, IBase *pIssuer, IBase *pDest, void *pfnCb); \
    MAERet_t (*StartApplet)(IName *pShell, MAEClsId_t nClsId, u32 nMode, IAPPLET **ppApplet); \
    MAERet_t (*StartAppletEx)(IName *pShell, MAEClsId_t nClsId, u32 nMode, IAPPLET **ppApplet, u32 nParam, PfnStartParamCleanup pfnClean); \
    MAERet_t (*CloseApplet)(IName *pShell, boolean bBackToHome); \
    MAERet_t (*BackgroundApplet)(IName *pShell); \
    MAERet_t (*SetAppletAttribs)(IName *pShell, u32 nAttribs, boolean bEnabled); \
    MAERet_t (*ConfirmAppletState)(IName *pShell, APM_AppletConfirm_e eState); \
    MAERet_t (*FlushAppletStack)(IName *pShell, PfnFlushCallback pfnCallback); \
    MAERet_t (*FlushAppletStackEx)(IName *pShell, PfnFlushCallback pfnCallback, u32 nFlushType); \
    u32 (*QueryApplet)(IName *pShell, MAEClsId_t nClsId); \
    boolean (*IsAppletBased)(IName *pShell, IBase *pBaseObj); \
    IBase* (*CurrentContext)(IName *pShell); \
    PfnDefEventHandler (*SetDefaultHandler)(IName *pShell, PfnDefEventHandler pfnDefault); \
    MAERet_t (*UpdateScreen)(IName *pShell); \
    MAERet_t (*CreateTimer)(IName *pShell, s32 nMSecs, PfnMAE_Notify pfnCallback, void *pOwner); \
    MAERet_t (*CreateTimerEx)(IName *pShell, s32 nMSecs, PfnTimerCallbackEx pfnCallback, void *pOwner, void *pUserData); \
    MAERet_t (*CreatePeriodicTimer)(IName *pShell, s32 nMSecs, PfnTimerCallbackEx pfnCallback, void *pOwner, void *pUserData); \
    MAERet_t (*CreatePowerSaveTimer)(IName *pShell, s32 nMSecs, PfnTimerCallbackEx pfnCallback, void *pOwner, void *pUserData); \
    MAERet_t (*CancelTimer)(IName *pShell, PfnMAE_Notify pfnCallback, void *pOwner); \
    MAERet_t (*CancelTimerEx)(IName *pShell, PfnTimerCallbackEx pfnCallback, void *pOwner); \
    boolean (*IsTimerActive)(IName *pShell, void* pfnCallback, void *pOwner); \
    MAERet_t (*PausePowerSaveTimer)(IName *pShell); \
    MAERet_t (*ResumePowerSaveTimer)(IName *pShell); \
    void (*Shutdown)(IName* pShell, boolean bReset); \
    MAERet_t (*RegisterMessage)(IName *pShell, IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnInterface pfnHandler); \
    MAERet_t (*DeregisterMessage)(IName *pShell, IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnInterface pfnHandler); \
    MAERet_t (*HookMessage)(IName *pShell, IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnHookHandler pfnHandler); \
    MAERet_t (*UnhookMessage)(IName *pShell, IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnHookHandler pfnHandler); \
    MAERet_t (*ExeCallBack)(IName *pShell, IBase *pOwnr, u32 nParam, PfnResumeCallback pfnCb); \
    MAERet_t (*PushContext)(IName *pShell, IBase *pOwnr); \
    void (*PopContext)(IName *pShell); \
    u16 (*GetInstanceClsId)(IName *pShell, IBase *pObj); \
    u32 (*GetInstIdByAddress)(IName *pShell, IBase *pObj);\
    IBase* (*GetAddressByInstId)(IName *pShell, u32 InstId);\
    void (*CloseEmbeddedApp)(IName *pShell, u32 nClsId);\
    void (*SendToEmbeddedApp)(IName *pShell, u32 nParam1, u32 nParam2, PfnCleanup pfnCleanup);\
    void (*Update3DMode)(IName *pShell);\
    u32 (*LoadResString)(const u32, u16**); \
    u32 (*LoadResStringWithLangID)(const u32, const MAE_LANG_CODE_e, u16**); \
    MAE_Ret (*LoadPreDefinedResAsImage)(const u32, IIMAGE**, IBase*); \
    MAE_Ret (*LoadUserDefinedResAsImage)(u16*, IIMAGE**, IBase*); \
    MAE_Ret (*LoadPreDefinedResAsBitmap)(const u32, IBITMAP**, IBase*); \
    MAE_Ret (*LoadUserDefinedResAsBitmap)(u16*, IBITMAP**, IBase*); \
    MAE_Ret (*FreeRes)(IBase*); \
    MAE_Ret (*LoadActivePreDefinedResAsImage)(const u32, IIMAGE**, IBase*); \
    MAE_Ret (*InstanceCheckValid)(IName *pShell, IBase *pObj, MAE_ClsId nClsId);\
    MAE_Ret (*AutoRotate)(IName *pShell, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);\
    u16 (*GetTopOrientation)(IName *pShell, IBase *pObj)

// defines the base structure of an IShell object
DEFINE_INTERFACE(IShell);


//
// general functions related to shell but not included in the IShell interface
//
/**
* It allocates a memory block and resets it to zero for an object.
*
* This function allocates a memory block which is used for an interface object. The allocated
* block has been reset to zero, so that the caller can initialize only those non-zero fields.
*
* The block contains a header which is transparent to the caller and is only for shell's internal
* use. Any object that implements an interface shall be allocated by this function.
*
* @param Size		Size of the object structure.
*
* @return			The pointer to the allocated block. If it's null, the allocation fails.
*/
#ifdef __PC_SIMULATOR__
#define MAE_AllocObject(size) MAE_ShellAllocObject(size, 0, __LINE__, __MFILE__)
#else
#define MAE_AllocObject(size) MAE_ShellAllocObject(size, 0)
#endif /*__PC_SIMULATOR__*/

#ifdef __PC_SIMULATOR__
void *MAE_ShellAllocObject( u32 Size, u32 currentLr, int __nMline__, char *__nMfile__ );
#else
void *MAE_ShellAllocObject( u32 Size, u32 currentLr );
#endif /*__PC_SIMULATOR__*/

/**
* It allocates a memory block and resets it to zero using MAE_AllocObject(), then initialize the
* object's virtual function table.
*
* @param Size		Size of the object structure.
* @param pVtbl		Pointer to the virtual function table.
*
* @return			The pointer to the allocated block. If it's null, the allocation fails.
*/
#ifdef __PC_SIMULATOR__
#define MAE_AllocObjectEx(size, pVtbl) MAE_ShellAllocObjectEx(size, pVtbl, __LINE__, __MFILE__)
#else
#define MAE_AllocObjectEx(size, pVtbl) MAE_ShellAllocObjectEx(size, pVtbl)
#endif

#ifdef __PC_SIMULATOR__
void *MAE_ShellAllocObjectEx( u32 Size, IBase_Vtbl *pVtbl, int __nMline__, char *__nMfile__ );
#else
void *MAE_ShellAllocObjectEx( u32 Size, IBase_Vtbl *pVtbl );
#endif /*__PC_SIMULATOR__*/

/**
* If It Checks whether race condition exist, it's log fatal.
*/
void MAE_AvoidCrossTaskCall(void);

/**
* It frees an object which is allocated by MAE_AllocObject() or MAE_AllocObjectEx().
*
* @param pObj		Pointer of the object to be freed.
*
* @return			No return value.
*/

void MAE_FreeObject(void *pObj);

/**
* It is used only in IHandler objects' constructor functions to confirm that the instance has been
* allocated/identified, and instruct the shell to switch context to the IHandler object for further
* processing of its constructor.
*
* A better approach might be dividing current constructor function into new part and construct part.
* Then shell invokes these two functions in sequence, switch the context if needed and doesn't
* require to involve the objects in.
*
* @param pObj		Pointer to the allocated (or a singleton's existing instance) IHandler object.
*
* @return			No return value.
*/
void MAE_ConfirmObject(void *pObj);

/**
* It is used only in IHandler objects' constructor functions to assign the class Id to the object.
*
* @param pObj		Pointer to the allocated (or a singleton's existing instance) IHandler object.
* @param nClsId		The class Id.
*
* @return			No return value.
*/
void MAE_AssignClsId(void *pObj, MAE_ClsId nClsId);

/**
* It returns current shell of the system.
*
* This function returns current active shell object. In MAE platform it actually has only one
* shell object, MAE_Shell, and it exists permanently until the system shutdown.
* It is used only in MAE core components and it does nothing to the reference count of the shell object.
* The shell object returned from this function doesn't need to be released when it is not needed.
*/
#ifdef __MAE_CORE_DIAGNOSIS__

IShell *MAE_CurrentShell(void);

#else // __MAE_CORE_DIAGNOSIS__

IShell *MAE_CurrentShell(void);

#endif // __MAE_CORE_DIAGNOSIS__

/**
* It converts the address of a multi-inherited interface to the address of its base structure.
*/
IBase *MAE_GetBaseAddress(IBase *pObj);

// ZINC: it has not been implemented
// void *MAE_AllocDerObject(u32 Size);
// void MAE_FreeDerObject(IBase *pObj);

// ZINC: section to be modified
// these prototypes shall not be here...
enum
{
    MAE_SH_RUNNING = 0,
    MAE_SH_TERMINATE,
    MAE_SH_RESET
};

/**
* This function handles events posted in shell's event queue.
*
* The MMI task fetches messages from task's message queue and dispatches them to the registered
* handlers. This function is called after a message is handled to process the events generated by
* the message handlers. This function returns control to the task's message loop only after all
* the events, including subsequent generated events, are processed.
*
* A posted event and all of the generated subsequent events must not form an infinite event loop.
* It would make the object state unstable, and this function would never return. Besides, the
* handling procedures of events shall not be blocked for a significant time or consume too much
* computing power, since MAE is a single-threaded platform. Otherwise the user interface will be
* less or not responding, and the task queue may be flooded with system messages.
*/
u16 MAE_Shell_ProcessEvent(void);

/**
* This function dispatches system messages to the corresponding handlers of their groups.
*
* @param pMessage		Pointer to the structure of rtk message.
*/
MAERet_t MAE_Shell_DispatchMessage(void *pMessage);
// ZINC: end of section

//
// macros and functions to run the methods of an IShell object
// MAE platform has exactly one shell, so the SH series of functions omit the shell object
// parameter to simplify the programming
//
/**
* This function is used to register the class info table of all the classes of a specified category.
*
* @param nClsIdBase		The class base of specified class category.
* @param pClsInfoTable	The class info table for all classes of the category.
* @param nCount			Total number of classes in the class info table.
*/
MAERet_t SH_RegisterClassCategory(MAEClsId_t nClsIdBase, const MAE_ClassInfo_t *pClsInfoTable, u16 nCount);

/**
* It creates an object of the specified class id and returns the pointer to the object.
*
* @param nClsId		Class id of the object to be created.
* @param ppObj		Pointer to the variable to store the created object.
* @param pOwner	Pointer to the object instance which requests to create the object.
*/
#ifdef __PC_SIMULATOR__
MAERet_t MAE_Shell_CreateInstance(IShell *pShell, MAEClsId_t nClsId, void **ppObj, IBase *pOwner,int __nMline__,char *__nMfile__);

#define SH_CreateInstance(nClsId, ppObj, pOwner) \
    MAE_Shell_CreateInstance(MAE_CurrentShell(), nClsId, ppObj, pOwner, __LINE__,__MFILE__)

#else

MAERet_t SH_CreateInstance(MAEClsId_t nClsId, void **ppObj, IBase *pOwner);
#endif

/**
* It sends an event directly to the destination object and processes the event before it returns.
*
* @param pDest		Pointer to the destination IHandler object.
* @param nEvt		Event to be sent.
* @param nLParam	First 32-bit parameter of the event.
* @param nDParam	Second 32-bit parameter of the event.
*/

MAERet_t SH_SendEvent(IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

/**
* It posts an asynchronous event into the shell event queue for the destination object.
*
* @param pDest		Pointer to the destination IHandler object.
* @param nEvt		Asynchronous event to be posted.
* @param nLParam	First 32-bit parameter of the event.
* @param nDParam	Second 32-bit parameter of the event.
*/
MAERet_t SH_PostEvent(IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

/**
* It's equivalent to SH_PostEvent except that it has a cleanup function and addtional mode
* parameter for posting events.
*
* @param pDest		Pointer to the destination IHandler object.
* @param nEvt		Asynchronous event to be posted.
* @param nLParam	First 32-bit parameter of the event.
* @param nDParam	Second 32-bit parameter of the event.
* @param nMode		nMode to configure how the event is posted.
* @param pfnClean	The cleanup function which is called after this asynchronous event is handled.
*/
MAERet_t SH_PostEventEx(IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam,
                                 u32 nMode, PfnEventCleanup pfnClean);

/**
* It's the substitutive version of IShell SendEvent() method.
*
* This function can be used to specify the issuer instance instead of using current context while
* sending events. It is helpful in implementing service's interface methods or callback functions
* to send/post events to itself or the instances it holds.
*
* The event communication from one instance to an IHandler instance requires that these two instances
* are associated, i.e. one of them shall hold the other, otherwise the communication fails. Shell
* uses this constraint to ensure that the event issuer knows exactly what its destination instance
* is, and the event can be delivered correctly.
*
* However ensuring the validity of event communication by checking only single level association is
* sometimes improperly. A service implementation may want to trigger its state transitions in its
* interface methods or callback functions by issuing events to itself, but these functions are
* sometimes running under the context of other instances which have no association with the service's
* instance. Consider the case that an applet A is current context and it executes a service S1's
* method MS1 in its event handler. Moreover, MS1 executes another method MS2 of service S2, which
* issues an event to S2 itself for certain operation. Eventually Shell takes the event request as a
* communication between A and S2 because all of these function calls are running under A's context.
* But A does not necessarily need to hold S2 if it only uses S1's service, therefore S2's event
* request fails.
*
* Without directly specifying the issuer instance, the services need to switch executing context
* to themselves in those function implementations to ensure that their events are properly issued.
* Implementation like this is not straightforward, and switching context hierarchically at run-time
* also decreases overall performance. Thus the substitutive version should be adopted in these
* cases to bypass those intermediate works. But bear in mind that these substitutive event methods
* shall not be misued to specify issuer instance arbitrarily to avoid the rule of event communication.
* It shall be used only at the place where the issuer instance is known to exist, such as in the
* issuer's interface method.
*
* @param pIssuer	The issuer instance to send event.
* @param pDest		The destination instance to receive event.
* @param nEvt		Event to be sent.
* @param nLParam	First 32-bit parameter of the event.
* @param nDParam	Second 32-bit parameter of the event.
*/
MAERet_t SH_SubstSendEvent(IBase *pIssuer, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

/**
* It's the substitutive version of IShell PostEvent() method.
*
* @param pIssuer	The issuer instance to post event.
* @param pDest		The destination instance to receive event.
* @param nEvt		Asynchronous event to be posted.
* @param nLParam	First 32-bit parameter of the event.
* @param nDParam	Second 32-bit parameter of the event.
*/

MAERet_t SH_SubstPostEvent(IBase *pIssuer, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

/**
* It's the substitutive version of IShell PostEventEx() method.
*
* @param pIssuer	The issuer instance to post event.
* @param pDest		The destination instance to receive event.
* @param nEvt		Asynchronous event to be posted.
* @param nLParam	First 32-bit parameter of the event.
* @param nDParam	Second 32-bit parameter of the event.
* @param nMode		nMode to configure how the event is posted.
* @param pfnClean	The cleanup function which is called after this asynchronous event is handled.
*/

MAERet_t SH_SubstPostEventEx(IBase *pIssuer, IHANDLER *pDest, MAEEvent_t nEvt, u32 nLParam, u32 nDParam,
                             u32 nMode, PfnEventCleanup pfnClean);

/*Test Broadcast event to Applet*/
MAERet_t SH_SubstBroadcastPostEvent(IBase *pIssuer, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

/**
* It schedules an asynchronous procedure call into event queue for the destination object.
*
* This function schedules a callback function into shell's event queue for the destination object.
* The callback acts as an asynchronous procedure call and will be executed under the context of
* the destination object. Issuing a callback to an object which has no relationship to the calling
* object is not allowed.
*
* It's legal to use SendEvent() method in the callback function since the execution of callback is
* scheduled to the intervals of event processing. Implementing callback function which passes data
* or objects with it is responsible for freeing or releasing them after they are processed.
*
* The shell has no clue to how the callbacks' parameters are processed and released, therefore
* shell makes sure that all the callback functions can be executed correctly. Once a callback is
* issued, its destination object will be held by shell until the callback is processed. That is,
* a resume or resumeex callback function is always executed once it is issued successfully. Also
* note that the issuer object of a resumeex callback will be held by shell too since it is needed
* in later execution.
*
* @param pIssuer	Pointer to the object issues the callback.
* @param pDest		Pointer to the destination object.
* @param pfnCb		The callback function.
* @param nParam		32-bit parameter for the callback function.
*/
MAERet_t SH_Resume(IBase *pIssuer, IBase *pDest, PfnResumeCallback pfnCb, u32 nParam);

/**
* It schedules an asynchronous procedure call into event queue for the destination object,
* and provides additional pIssuer parameter to the callback function to handle the objects been
* passed.
*/
MAERet_t SH_ResumeEx(IBase *pIssuer, IBase *pDest, PfnResumeCallbackEx pfnCb, u32 nParam);

/**
* It instructs the shell to cancel the specified asynchronous procedure call.
*
* This function cancels the callback function formerly issued by pIssuer. It verifies queued
* callback functions and removed those which match to the specified parameters.
*
* A canceled callback function will not be executed. It means that if the function is implemented
* to send data to a specific object and release these data, they won't be released now. The issuer
* shall handle these data after the callback is successfully canceled, but shall not access these
* data if the callback is executed (either the callback is not found while trying to cancel it, or
* the issuer doesn't cancel the request).
*
* @param pIssuer	Pointer to the object issues the callback.
* @param pDest		Pointer to the destination object.
* @param pfnCb		The callback function.
*
* @retval MAE_RET_SUCCESS		The specified callback is successfully canceled.
* @retval MAE_RET_NOT_FOUND	The specified callback is not found.
* @retval MAE_RET_BAD_PARAM	Invalid input address.
*/
MAERet_t SH_Cancel(IBase *pIssuer, IBase *pDest, void *pfnCb);

/**
* It starts an applet of the specified class id.
*
* This function creates an applet instance of the specified class id and instructs APM to manage
* this applet. Presently the MAE platform doesn't support multiple applets of the same class id
* unless these applets are started with the APM_LAUNCH_EMBEDDED mode. An embedded applet is not
* considered as an independent applet but as a child which is bound to the applet that invokes it.
* Starting an existing applet (non-embedded) brings the applet to the top of applet stack.
*
* Generally an applet is started by another applet, a service, or by the shell due to user's
* operation or a specific event. So that the owner of created applet is assigned according to
* shell's current context.
*
* @param nClsId		The applet's class id.
* @param nMode		Applet launch options: APM_LAUNCH_NORMAL, APM_LAUNCH_INTERRUPTIVE, APM_LAUNCH_EMBEDDED,
*					and APM_LAUNCH_BACKGROUND.
*					It can be ORed with APML_ABORT_ON_INT_FAILED, APML_QUIET, and APML_AUTO_RELEASE options.
* @param ppApplet	Pointer to the variable to store the created applet.
*/
MAERet_t SH_StartApplet(MAEClsId_t nClsId, u32 nMode, IAPPLET **ppApplet);

/**
* It starts an applet of the specified class id and allows passing parameters to it.
*
* StartAppletEx() is similar to StartApplet() but provides additional parameters so that the
* creator can pass informations or instructions to the new applet.
*
* @param nClsId		The applet's class id.
* @param nMode		Applet launch options: APM_LAUNCH_NORMAL, APM_LAUNCH_INTERRUPTIVE, APM_LAUNCH_EMBEDDED,
*					and APM_LAUNCH_BACKGROUND.
*					It can be ORed with APML_ABORT_ON_INT_FAILED, APML_QUIET, and APML_AUTO_RELEASE options.
* @param ppApplet	Pointer to the variable to store the created applet.
* @param nParam		The parameter to be passed to the started applet.
* @param pfnClean	The cleanup function for the parameter.
*/
MAERet_t SH_StartAppletEx(MAEClsId_t nClsId, u32 nMode, IAPPLET **ppApplet,
                                   u32 nParam, PfnStartParamCleanup pfnClean);

/**
* It instructs the APM to close the calling applet, or close all applets and back to home screen.
*/
MAERet_t SH_CloseApplet(boolean bBackToHome);

/**
* It instructs the APM to suspend the calling applet.
*/
MAERet_t SH_BackgroundApplet(void);

/**
* It enables or disables the specified attributes of the calling applet.
*/
MAERet_t SH_SetAppletAttribs(u32 nAttribs, boolean bEnabled);

/**
* It confirms the asynchronous state of calling applet to APM.
*/
MAERet_t SH_ConfirmAppletState(APM_AppletConfirm_e eState);

/**
* It flushes the applets in stack, closes them or suspends them into background.
*
* This function instructs APM to flush the applet stack. Most applets will be closed, including
* the suspended onces, to release memory for subsequent operations. It is recommended to do so
* before launching other applets from task menu. The difference between the behaviours of
* CloseApplet-BackToHome and FlushAppletStack commands is that... hmm... no difference currently.
* The home command is to close every applet above the first base applet and return to it. But
* the flush command will keep the important applets and move them to background.
*
* This is an asynchronous operation. APM will resume the callback function to notify the issuer
* after the flush command is accomplished, or canceled by user or other interruptions.
*
* Designers can decide to keep their applets in stack by responding to the query of "KEEP-IN-STACK"
* property. It can prevent those applets from being closed by the flush command. Then the user can
* switch between applets through the task menu, but of course it cost more memory.
*
* For current project's memory size configuration, we don't have many choices. The flush command
* now closes all the applets in stack, including the unrevealed ones (which are failed to interrupt
* the focused applet and then are suspended in the applet stack).
*/
MAERet_t SH_FlushAppletStack(PfnFlushCallback pfnCallback);

/**
* It flushes the applets in stack, closes them or suspends them into background.
*
* MAE_FLUSH_APPLET : It will flush all applet if there is one home applet.
* This function instructs APM to flush the applet stack. Most applets will be closed, including
* the suspended onces, to release memory for subsequent operations.
*
* MAE_FLUSH_APPLET_TO_HOME : It will flush all applets until first home applet.
* If there are two home applets in applet stack. This process will close applet until first home applet.
* Under the first home applet that will be not close.
*
* MAE_FORCE_FLUSH_APPLET : It will flush applets until top of ap stack is home applet.
* This function instructs APM to flush the applet stack. Most applets will be closed, including
* the suspended onces, to release memory for subsequent operations.
* It will close applet form top to botton. 
*/
MAERet_t SH_FlushAppletStackEx(PfnFlushCallback pfnCallback, u32 eFlushAppletType);

/**
* It's the simplified version of applet info query function.
*
* This function returns only the existence information of the specified applet class id. A single
* applet class may have many instances in stacks, and each of them can have their own status.
* This function doesn't return all the statuses of specified applet class but simply answers the
* following questions:
*
* - does the applet class exist?
* - does the focused applet belong to this class?
* - does the applet class reside in foregraound or background stack?
* - does the applet class have multiple instances?
* - does the applet class have embedded instances?
* - is there any instance of the class being started or stopped?
*
* @param nClsId		The interested class id.
* @return			Bitwise flags to indicate the existence of specified class.
*/
u32 SH_QueryApplet(MAEClsId_t nClsId);

/**
* It returns the address of current context.
*
* The caller has to add reference to it if it is needed in later processing (the instance is not
* created, so that shell doesn't add the reference for the caller).
*/
IBase *SH_CurrentContext(void);

boolean SH_IsAppletBased(IBase *pBaseObj);

/**
* It sets a default event handler to shell, and returns the previous one.
*
* The default event handler in shell handles an event only if it has not been specified a
* destination, and the focused applet doesn't handle it. The context to execute the default
* handler will be shell itself.
*
* Do not use default event handler to handle events which have specific purpose. Events without
* a destination are considered as common, and unimportant. They will be posted to the focused
* applet. And if the focused applet is being changed, the events are discarded. The default
* handler takes over these kind of events only if the focused applet is available, but it doesn't
* handle them. An event with specific purpose shall be posted to its designated destination. The
* default event handler can not guarantee that it receive all the unhandled events.
*/
PfnDefEventHandler SH_SetDefaultHandler(PfnDefEventHandler pfnDefault);

/**
*
*/

MAERet_t SH_UpdateScreen(void);
MAERet_t SH_ForceRedrawWithoutUpdateScreen(void);

/**
*  This function return one IBitmap,  it's owner is MAE_CurrentShell();
*  Which contains the screen by given type,
*/
IBase *SH_GetSpecifiedScreen(MAE_DispId_t nDispId, MAE_SpecifiedScreenType_t nType);

/**
* It creates a timer which will invoke the callback function when the time's up.
*
* This function allocates a timer which will expire after MSec milli-seconds. Negative timeout values
* are treated as zero. Upon timeout, the callback function is called and the owner object is passed
* to it as parameter. Beware that each timer is identified by its pfnCallback and pOwner parameters.
* If a timer with the same callback and owner has already been created in shell, the newer one
* overwrites it.
*
* @param nMSecs			Timeout value in milliseconds. Negative values are treated as zero.
* @param pfnCallback	The function to be called when the timer expires.
* @param pOwner		The owner object which is passed as the only parameter to the callback function.
*
* @retval MAE_RET_SUCCESS			Timer is successfully set.
* @retval MAE_RET_OUT_OF_MEMORY	Cannot allocate more timers.
* @retval MAE_RET_BAD_PARAM		Invalid parameter.
*/
MAERet_t SH_CreateTimer(s32 nMSecs, PfnMAE_Notify pfnCallback, void *pOwner);

/*  @brief   Create a timer, while the ticks up, the callback function is involked
*  Store the timer tick, call backfuction, and the user data to timer list.
*  If a timer with same callback and userdata is already created by shell, this would overwrite it.
*
*  @param  pIShell         Pointer to the IShell interface
*  @param  mSecs           Timer tick in miliseconds which timer would be expired
*  @param  pFunc           Pointer of callback function.
*  @param  pOwner          The owner instance who intend to use timer
*  @param userData        user data
*  @retval MAE_RET_SUCCESS        SUCCESS.
*  @retval MAE_RET_OUT_OF_MEMORY       Cannot allocate more timer
*  @retval MAE_RET_BAD_PARAM        Invalid parameter
*/
MAERet_t SH_CreateTimerEx(s32 nMSecs, PfnTimerCallbackEx pfnCallback, void *pOwner, void *pUserData);

/**
*  @brief   Create a timer, while the ticks up, the callback function is involked
*  Store the timer tick, call backfuction, and the user data to timer list.
*  If a timer with same callback and userdata is already created by shell, this would overwrite it.
*  Be careful !!! create a periodic timer with short interval like 1 ms may cause MMI task's queue full.
*  Think again when you want to use this.
*
*  @param  pIShell          Pointer to the IShell interface
*  @param  mSecs           Timer tick in miliseconds which timer would be expired
*  @param  pFunc           Pointer of callback function.
*  @param  pOwner         The owner instance who intend to use timer
*  @param userData        user data
*  @retval MAE_RET_SUCCESS        SUCCESS.
*  @retval MAE_RET_OUT_OF_MEMORY       Cannot allocate more timer
*  @retval MAE_RET_BAD_PARAM        Invalid parameter
*/
MAERet_t SH_CreatePeriodicTimer(s32 nMSecs, PfnTimerCallbackEx pfnCallback, void *pOwner, void *pUserData);

/** MAE_Shell_CreatePowerSaveTimer
*  \brief   Create a timer, while the ticks up, the callback function is involked
*  Store the timer tick, call backfuction, and the user data to timer list.
*  If a timer with same callback and userdata is already created by shell, this would overwrite it.
*  The PowerSave timers could be paused by PausePowerSaveTimer().
*  \param  pIShell         Pointer to the IShell interface
*  \param  mSecs           Timer tick in miliseconds which timer would be expired
*  \param  pFunc           Pointer of callback function.
*	\param  pOwner          The owner instance who intend to use timer
*  \retval MAE_RET_SUCCESS        SUCCESS.
*  \retval MAE_RET_OUT_OF_MEMORY       Cannot allocate more timer
*  \retval MAE_RET_BAD_PARAM        Invalid parameter
*/
MAERet_t SH_CreatePowerSaveTimer(s32 nMSecs, PfnTimerCallbackEx pfnCallback, void *pOwner, void *pUserData);

/**
* It cancels the specified timer.
*
* This function cancels the timer associated with the callback and owner parameters. If the
* pfnCallback parameter is non-null, the specified timer is canceled. If pfnCallback is null, all
* timers associated with the same owner are canceled.
*
* Canceling a timer which has stopped or is not actually allocated has no effect.
*
* @param fnCallbak		The callback function associated with the timer.
* @param pOwner		The owner object which allocates the timer.
*
* @return				It returns MAE_RET_SUCCESS always.
*/
MAERet_t SH_CancelTimer(PfnMAE_Notify pfnCallback, void *pOwner);

/**
* It cancels the specified timer created by SH_CreateTimerEx.
*
* This function cancels the timer associated with the callback and owner parameters. If the
* pfnCallback parameter is non-null, the specified timer is canceled. If pfnCallback is null, all
* timers associated with the same owner are canceled.
*
* Canceling a timer which has stopped or is not actually allocated has no effect.
*
* @param fnCallbak		The callback function associated with the timer.
* @param pOwner		The owner object which allocates the timer.
*
* @return				It returns MAE_RET_SUCCESS always.
*/
MAERet_t SH_CancelTimerEx(PfnTimerCallbackEx pfnCallback, void *pOwner);

/**
* It cancels the specified timer created by SH_CreateAnimation
*
* This function cancels the timer associated with the callback and owner parameters. If the
* pfnCallback parameter is non-null, the specified timer is canceled. If pfnCallback is null, all
* timers associated with the same owner are canceled.
*
* Canceling a timer which has stopped or is not actually allocated has no effect.
*
* @param fnCallbak		The callback function associated with the timer.
* @param pOwner		The owner object which allocates the timer.
*
* @return				It returns MAE_RET_SUCCESS always.
*/
#define SH_CancelPowerSaveTimer SH_CancelTimerEx

/**
* It returns whether the specified timer is active or not.
*
* This function returns whether the timer, which is associated with the pfnCallback and
* pOwner parameters, is active or not.
*
* @param pfnCallback	The callback function associated with the timer.
* @param pOwner		The owner object which allocates the timer.
*
* @retval non-zero		The remaining time in milliseconds before the timer expires.
* @retval zero			The timer has expired, has been removed, or has not been created.
*/
boolean SH_IsTimerActive(void *pfnCallback, void *pOwner);

/** MAE_Shell_PausePowerSaveTimer
*  \brief   Pause all PowerSave timers
*  \retval MAE_RET_SUCCESS        SUCCESS.
*  \retval MAE_RET_FAILED           PowerSave timer is already suspended
*/
boolean SH_PausePowerSaveTimer(void);

/** MAE_Shell_ResumePowerSaveTimer
*  \brief   Resume all PowerSave timers
*  \retval MAE_RET_SUCCESS        SUCCESS.
*  \retval MAE_RET_FAILED           PowerSave timer is already resumed
*/
boolean SH_ResumePowerSaveTimer(void);

/**
* It instructs the shell to shut down the system.
*
* This function instructs shell to start shutdown procedure and issues a command to APM to close all the
* running applets. If the context issuing the shutdown request is the focused applet, the applet
* unit will be marked as shutdown applet and it will be the last one to be closed. Then the
* calling applet can execute routines for shutdown simultaneously and can also draw animations.
*
* The calling applet shall set ASYNC_STOP attribute and shall confirm the APM to close it after
* everything is done, in case APM closes the applet before it finishes its shutdown routines.
* Once all the applets are closed, shell will then break the main loop of MMI task to execute
* task's terminate procedure.
*
* The MMI task will re-initiate and enter the main loop again if the parameter bReset is true.
* Otherwise it will switch off system's power.
*
* @param bReset		If it is true, restart the MMI task. Otherwise power off the system.
*/
void SH_Shutdown(boolean bReset);

/**
* It registers the (recipient, message, handler) tuple to the dispatch table.
*
* Once a rtk message arrives, the corresponding handlers will be executed by the dispatcher. The recipient
* will be passed to the handler so that the handler can post events to it or access the content of it. All
* the messages of the same group will be passed to the handler registered to that group.
*
* Also it's allowed to register more than one handler to a message group. A message will be dispatched to
* all the registered handlers of its group according to their registration order, unless it is intercepted
* by a hook handler.
*
* The pRecipient parameter can be omitted if the handler doesn't require an instance to handle it. Once a
* handler is registered with null recipient pointer, it shall be able to handle the messages solely in its
* routines.
*
* @param pRecipient	The recipient instance which is interested to the specified message base.
* @param eMsgBase		The id of a message group.
* @param pfnHandler		The handler function which handles all the messages within this base.
*
* @retval MAE_RET_SUCCESS
* The handler is registered successfully.
*
* @retval MAE_RET_BAD_PARAM
* The parameters are invalid. Eg: the instance address is invalid, or the message base is out of range.
*
* @retval MAE_RET_DUPLICATE_HANDLER
* The message handler for registration already exists.
*
* @retval MAE_RET_OUT_OF_MEMORY
* Not enough memory for storing registration data.
*/
MAERet_t SH_RegisterMessage(IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnInterface pfnHandler);

/**
* It deregisters the (recipient, message, handler) tuple from the dispatch table.
*
* @param pRecipient	The recipient instance which is interested to the specified message base.
* @param eMsgBase		The id of a message group.
* @param pfnHandler		The handler function for the specified message base.
*
* @retval MAE_RET_SUCCESS
* The handler is deregistered successfully.
*
* @retval MAE_RET_BAD_PARAM
* The parameters are invalid.
*
* @retval MAE_RET_NOT_FOUND
* The specified handler is not found in the dispatch table.
*/
MAERet_t SH_DeregisterMessage(IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnInterface pfnHandler);

/**
* It registers the (recipient, message, handler) tuple to the hook table.
*
* This function is similar to SH_RegisterMessage() but registers a hook handler. A hook handler
* has higher priority and will be executed earlier than a dispatch handler when a rtk message of the
* specified group arrives.
*
* It's allowed to register many handlers to a message group. All the registered handlers of the same
* message group will be linked together to form a handler chain. A registered handler for dispatching
* message will be appended at the end of the chain, and a handler for hooking will be prepended at
* the start. So the latest registered hook handler will be executed first.
*
* A hook handler can decide to intercept the message by returning true. The message dispatcher tries
* all the handlers on the chain of the message's group. Once a hook handler returns true to intercept
* the message, all the later handlers are skipped.
*
* @param pRecipient	The recipient instance which is interested to the specified message base.
* @param eMsgBase		The id of a message group.
* @param pfnHandler		The handler function which handles all the messages within this base.
*
* @retval MAE_RET_SUCCESS
* The handler is registered successfully.
*
* @retval MAE_RET_BAD_PARAM
* The parameters are invalid. Eg: the instance address is invalid, or the message base is out of range.
*
* @retval MAE_RET_DUPLICATE_HANDLER
* The message handler for registration already exists.
*
* @retval MAE_RET_OUT_OF_MEMORY
* Not enough memory for storing registration data.
*/
MAERet_t SH_HookMessage(IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnHookHandler pfnHandler);

/**
* It deregisters the (recipient, message, handler) tuple from the hook table.
*
* @param pRecipient	The recipient instance which is interested to the specified message base.
* @param eMsgBase		The id of a message group.
* @param pfnHandler		The handler function for the specified message base.
*
* @retval MAE_RET_SUCCESS
* The handler is deregistered successfully.
*
* @retval MAE_RET_BAD_PARAM
* The parameters are invalid.
*
* @retval MAE_RET_NOT_FOUND
* The specified handler is not found in the hook table.
*/
MAERet_t SH_UnhookMessage(IBase *pRecipient, MAE_MsgBase_e eMsgBase, PfnHookHandler pfnHandler);

//
// ZINC: to be modified...
//
/**
*  SH_LoadResString
*  \brief  load the textlabel
*
*  \param  nTextID         id of the text label
*  \param  pBuff           buffer for the string (memory allocation occur inside the function)
*  \retval number of character
*  \retval 0 otherwise
*
*/
u32 SH_GetResString(const u32 nTextID, u16** pBuff);

/**
*
* SH_LoadResStringWithLangID
* \brief   load the textlabel for the specified language ID.  If the specified language ID is not available
*          in the pack, default language is used
*
* \param   nTextID        id of the text label
* \param   nLangID         language ID
* \param   pBuff          buffer for the string (memory allocation occur inside the function)
*
* \retval  number of character
* \retval  0 otherwise
*
*/
u32 SH_LoadResStringWithLangID(const u32 nTextID, const MAE_LANG_CODE_e nLangID, u16** pBuff);

/**
*  SH_LoadPredefinedResAsImage
*  \brief  load the textlabel
*
*  \param  pShell          the object pointer to shell.
*  \param  nImageID         id of the image .
*  \param  ppImage          the pointer of IImage object pointer to retrieve the output image.
*  \param  pOwner           a pointer to IBase object which is the owner of the output image.
*  \retval MAE_RET_SUCCESS  Successfully.
*  \retval Others           Failed.
*
*/
MAERet_t SH_LoadPreDefinedResAsImage(const u32 nImageID, IIMAGE **ppImage, IBase* pOwner);

/**
*  SH_LoadActivePreDefinedResAsImage
*  \brief  load the textlabel
*
*  \param  pShell           the object pointer to shell.
*  \param  nIndex           index of the image .
*  \param  ppImage          the pointer of IImage object pointer to retrieve the output image.
*  \param  pOwner           a pointer to IBase object which is the owner of the output image.
*  \retval MAE_RET_SUCCESS  Successfully.
*  \retval Others           Failed.
*
*/
MAERet_t SH_LoadActivePreDefinedResAsImage(const u32 nIndex, IIMAGE **ppImage, IBase* pOwner);

/**
*  SH_LoadUserDefinedResAsImage
*  \brief  load the textlabel of user defined
*
*  \param  pShell          the object pointer to shell.
*  \param  pPath            the image path
*  \param  ppImage          the pointer of IImage object pointer to retrieve the output image.
*  \param  pOwner           a pointer to IBase object which is the owner of the output image.
*  \retval MAE_RET_SUCCESS  Successfully.
*  \retval Others           Failed.
*
*/
MAERet_t SH_LoadUserDefinedResAsImage(u16* pPath, IIMAGE **ppImage, IBase* pOwner);

/**
*  SH_LoadPredefinedResAsImage
*  \brief  load the textlabel
*
*  \param  nImageID         id of the image
*  \retval image
*  \retval NULL
*
*/
MAERet_t SH_LoadPreDefinedResAsBitmap(const u32 nImageID, IBITMAP **ppBitmap, IBase* pOwner);

/**
*  SH_LoadPredefinedResAsImage
*  \brief  load the textlabel
*
*  \param  nImageID         id of the image
*  \retval image
*  \retval NULL
*
*/
MAERet_t SH_LoadUserDefinedResAsBitmap(const u32 nImageID, IBITMAP **ppBitmap, IBase* pOwner);


MAERet_t SH_FreeRes(IBase* pRes);

/**
* It shell push context to owner object context. Pair PopContext is need.
*
*
* @param pOwner		Pointer to the destination object.
*/
MAERet_t SH_PushContext(IBase *pOwner);

/**
* It shell Pop context previous context. Pair of PushContext is need.
*
*
*/
void SH_PopContext(void);

/**
* It shell provide function for get IBase Instance ClsID.
*
*
*/
u16 SH_GetInstanceClsId(IBase* pObj);

/**
* It shell provide function for getting Instance ID by IBase.
*
*
*/
u32 SH_GetInstIdByAddress(IBase* pObj);

/**
* It shell provide function for getting Instance ID by IBase.
*
*
*/
IBase * SH_GetAddressByInstId(u32 nInstId);

/**
* It shell provide function to check if the class id of instance to be used is equal to the ClsId that is declared
* MAE_RET_SUCCESS will be returned if they are equal, otherwise, return MAE_RET_FAILED
*/
MAE_Ret SH_InstanceCheckValid(IBase *pObj, MAE_ClsId nClsId);

/**
* It shell provide function for closing caller's embedded App.
*
*
*/
void SH_CloseEmbeddedApp(u32 nClsId);

/**
* It's provided for send data to caller's embedded App.
*
*
*/
void SH_SendToEmbeddedApp(u32 nParam1, u32 nParam2, PfnCleanup pfnCleanup);


//3Dswitch
/**
* Shell provide function to update 3d mode
*
*
*/
void SH_Update3DMode(void);

#ifdef __PC_SIMULATOR__
int _sh_getCurrentAP();
#endif


MAERet_t SH_AutoRotate(MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

u16 SH_GetTopOrientation(IBase *pObj);

#endif // __MAE_SHELL_H__
