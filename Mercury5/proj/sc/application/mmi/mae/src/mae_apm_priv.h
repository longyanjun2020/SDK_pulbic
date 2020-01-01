/**
* @file mae_apm_priv.h
*
* This header file declares APM's private functions, data structures and constants
* used in the APM module of shell.
*
* @version $Id: mae_apm_priv.h 1684 2009-08-29 16:28:08Z zinc.chen $
*/

#ifndef __MAE_APM_PRIV_H__
#define __MAE_APM_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_apm_forward.h"

#ifdef __arm__
// suppress warnings for unnamed structures and unions
#pragma anon_unions
#endif // __arm__

//
// definitions and macros
//
/// max allowed applet instances in stack; we use only 8-bit signed indexes for the applet list
#define APM_MAX_APPLET 16
/// max allowed pending actions in APM's action queue
#define APM_MAX_ACTION 16


//
// private types and structures
//
/**
* The bit-mask values which represent the status and properties associated with an applet object
* in APM stack.
*
* These bit-mask values are stored in "attribs" of an applet element in APM's applet list.
* The lower 16-bits are reserved for applet settings. The higher 16-bits are the applet status
* and informations updated in APM operations.
*/
enum
{
    APMF_EMBEDDED_APPLET		= 0x00010000, ///< it's an embedded applet
    APMF_SHUTDOWN_APPLET	= 0x00020000, ///< the applet handles shutdown procedures
    APMF_FLUSHED_APPLET		= 0x00040000, ///< the base applet is going to be resumed after a stack flush operation
    APMF_CLOSING				= 0x00100000, ///< the applet is being closed
    APMF_UNREVEALED			= 0x00200000, ///< the applet has never been activated
    APMF_HIDDEN				= 0x00400000 ///< it indicates that the applet fails to interrupt the first base (home)									///< applet and then has no chance to show up unless it is restarted again
};

/// states of an applet
enum
{
    APM_ST_INIT = 0,
    APM_ST_ACTIVE,
    APM_ST_SUSPENDING,
    APM_ST_SUSPENDED,
    APM_ST_STOPPING,
    APM_ST_STOPPED,
    APM_ST_CONFIRMING, ///< the applet is waiting user's confirmation for closing
    APM_ST_CONFIRMED, ///< user has confirmed to close the applet

    APM_ST_INVALID = 0xFFFF ///< the applet has been invalidated, ready to be released
};

/// the status of APM module
enum
{
    APMS_INVALIDATED	= 0x0001, ///< it indicates that some applets have been invalidated
    APMS_FORCED_UPDATE	= 0x0002, ///< it indicates that the whole screen shall be forced to update
    APMS_DISCLOSING		= 0x0004, ///< it indicates that APM is disclosing the hidden applets
    APMS_TERMINATING	= 0x0008 ///< it indicates that the system is shutting down
};

/// structure of an applet instance and its status
typedef struct
{
    /// pointer the applet object
    IAPPLET *pObj;
    /// applet specified attributes, and the status changed/updated during APM operations
    u32 nAttribs;

    MAEClsId_t nClsId; // class id of the applet
    u16 nState; // state of the applet

    /// indices to the applet's embedded applet and its parent applet
    s8 nChildIdx, nParentIdx;

	//Indicate the Applet's location how to cross between Fore/Back Stk.
	u8 nAppSwapTo;

    //s8 nPriority;//the priority of the applet.
} APM_AppletElem_t;

/// structure which contains all the information about the applet objects currently handled in APM
typedef struct
{
    /// the array to store the applet instances and their status
    APM_AppletElem_t tApplets[APM_MAX_APPLET];

    /// stacks of the running applets
    /// it excludes the applets which are being closed or are created but haven't been started yet
    /// we use indexed list for applet stack so that moving applets in stack is easier and consumes less memory
    s8 nForeStack[APM_MAX_APPLET];
    s8 nBackStack[APM_MAX_APPLET];

    /// available slots in applets[]
    s8 nAvails[APM_MAX_APPLET];

    s8 nForeTop; // the top element in forestack[]
    s8 nBackTop; // the top element in backstack[]
    s8 nAvailTop; // the top available slot in avails[]

    /// index points to the focused applet in applets[]; it may be unavailable during the APM operations
    s8 nFocusedIdx;

    /// flags of the status of APM module
    u32 nFlags;
} APM_AppletInfo_t;
#ifdef __MAE_DEBUG_APM__
enum{
    LOG_INIT,
    LOG_PROCESSING,
    LOG_FINAL,
};
typedef struct
{
    u16 nClsId;
    MAEEvent_t nEvt;

} APM_DriveAppInfo;

typedef struct{
    u8  nCmd;	
    u16 nIssuerClsId;	
    union{
        struct {
            u16 nDstClsId;
            u32 nMode;
        } start;

        struct{
            APM_AppletConfirm_e State;
        }confirm;

        struct{
            boolean bToHome;
        }close;

        struct{
            u32 nAttribs;
            boolean bEnable;
        }setattr;

        struct{
            u32 nPfnFluchCb;
        }flush;
    };
} APM_InitActInfo;

typedef struct
{	
    u16 nUniqueId;
    u32 nState;	
    u8 nType;
    u32 nApmTimeStamp;
    union
    {
        APM_InitActInfo  ActInfo;
        APM_DriveAppInfo DrvInfo;
    };
} APM_AppletLogElem_t;

typedef struct 
{
    APM_AppletLogElem_t Logs[APM_LOG_AMOUNT];
    u8 nPos;      
}  APM_AppletLogInfo_t;

#endif

typedef struct ApmLaterStartInfo_t_
{
    MAEInstId_t nCurrContext;
    MAEClsId_t nClsId;
    u32 nMode;
    IAPPLET **ppApplet;
    u32 Param;    
    PfnStartParamCleanup fnClean;
}ApmLaterStartInfo_t;

/// commands used in APM's action queue
enum
{
    APMCMD_NONE = 0,
    APMCMD_START,
    APMCMD_BACKGROUND,
    APMCMD_STOP,
    APMCMD_HOME,
    APMCMD_SETATTRIB,
    APMCMD_SHUTDOWN,
    // ZINC: to be modified; flush and home can be combined in a single command
    APMCMD_FLUSH,
    APMCMD_DISCLOSE,
    APMCMD_CONFIRM,
    APMCMD_FORCE_FLUSH,
    APMCMD_HOME_FLUSH,
};

/**
* Enums for the states of an action.
*
* Sequences for a START command:
* WAITING, SUSPENDING, START_ACTIVE, START_FINALIZING, ACCOMPLISHED
* WAITING, STOPPING, RELEASE, START_ACTIVE, START_FINALIZING, ACCOMPLISHED
* WAITING, START_SUSPENDED, START_FINALIZING, ACCOMPLISHED
* WAITING, START_BACKGROUND, START_FINALIZING, ACCOMPLISHED
* WAITING, START_HIDDEN, START_FINALIZING, ACCOMPLISHED
*
* Sequences for a BACKGROUND command:
* WAITING, SUSPENDING, BACKGROUND_PROCEED, ACCOMPLISHED
*
* Sequences for a STOP command:
* WAITING, [STOP_PROCEED], STOPPING, RELEASE, ACCOMPLISHED
* - a STOP command may handle multiple applets of an applet unit and back to previous steps
*
* Sequences for a HOME command:
* WAITING, [FLUSH_PROCEED, FLUSH_STOP, STOPPING, RELEASE |
* FLUSH_PROCEED, FLUSH_BACKGROUND, ... (obsolete; this feature will be implemented in flush command) |
* FLUSH_PROCEED, FLUSH_CONFIRMING, FLUSH_STOP, STOPPING, RELEASE |
* FLUSH_PROCEED, FLUSH_CONFIRMING, FLUSH_CANCEL], ACCOMPLISHED
* - a HOME command handles multiple applets and jumps between these steps; it also handles applets
*   in different ways in different phases
*
* Sequences for a SETATTRIBS command:
* WAITING, ACCOMPLISHED
*
* Sequences for a SHUTDOWN command:
* WAITING, [SUSPENDING], STOP_PROCEED, STOPPING, RELEASE, ACCOMPLISHED
* - it's similar to a STOP command but it closes all the applets and it will cancel the FLUSH/HOME command
*   if there is an applet waiting for confirmation
*
* Sequences for a FLUSH command:
* WAITING, [FLUSH_PROCEED, FLUSH_STOP, STOPPING, RELEASE |
* FLUSH_PROCEED, FLUSH_BACKGROUND, ... (not available now) |
* FLUSH_PROCEED, FLUSH_CONFIRMING, FLUSH_STOP, STOPPING, RELEASE |
* FLUSH_PROCEED, FLUSH_CONFIRMING, FLUSH_CANCEL], ACCOMPLISHED
* - it's similar to a HOME command but has slight differeces when dealing with the applets
* - ZINC: to be modified; flush and home can be combined in a single command
*
* Sequences for a DISCLOSE command:
* WAITING, DISCLOSE_PROCEED, SUSPENDING, ACCOMPLISHED
*/
enum
{
    APM_ACT_ACCOMPLISHED = 0x01,
    APM_ACT_WAITING = 0x02,
    APM_ACT_SUSPENDING = 0x03,
    APM_ACT_STOPPING = 0x04,
    APM_ACT_RELEASE = 0x05,
    APM_ACT_START_ACTIVE = 0x06,
    APM_ACT_START_SUSPENDED = 0x07,
    APM_ACT_START_BACKGROUND = 0x08,
    APM_ACT_START_HIDDEN = 0x09,
    APM_ACT_START_FINALIZING = 0x0a,
    APM_ACT_BACKGROUND_FINALIZING = 0x0b,
    APM_ACT_STOP_PROCEED = 0x0c,
    APM_ACT_DISCLOSE_PROCEED = 0x0d,
    APM_ACT_FLUSH_PROCEED = 0x0e,
    APM_ACT_FLUSH_STOP = 0x0f,
    APM_ACT_FLUSH_BACKGROUND = 0x10,
    APM_ACT_FLUSH_CONFIRMING = 0x11,
    APM_ACT_FLUSH_CANCEL = 0x12,
    APM_ACT_WAIT_ENQUEUE = 0x13,
    //APM_ACT_INQUEUE,
    APM_ACT_QUEUE_FULL = 0x14,
    APM_ACT_SYS_SHUT = 0x15,
    APM_ACT_CLSID_NOTSUPPORT = 0x16,
    APM_ACT_INVALID_CONTEXT = 0x17,
    APM_ACT_ILLEGAL_OPERATION = 0x18,
    APM_ACT_ILLEGAL_PARAM = 0x19,
    APM_ACT_APPLETS_FULL = 0x1a,
    APM_ACT_SUCCESS = 0x1b,
    APM_ACT_FAIL = 0x1c,
    APM_ACT_QUEUE_EMPTY = 0x1d



};

/// structure of an action item
typedef struct
{
    /// command of the action
    u8 nCmd;
    /// execution state of the action
    u8 nState;
    /// index to the target applet of the action
    s8 nTargetIdx;
    /// index to the applet which is executing a blocking command because of the action
    /// this index shall always point to the top applet of an applet unit
    s8 nPendingIdx;
#ifdef __MAE_DEBUG_APM__
    u16 nUniqueID;
#endif

    union // command dependent data
    {
        struct
        {
            MAEInstId_t tIssuerId; ///< id of the instance that starts this applet
            u32 nMode; ///< starting mode of this applet
            u32 nParam; ///< parameter for the started applet
            PfnStartParamCleanup pfnClean; ///< cleanup function of the start parameter
        } start; ///< extra data needed for a START command

        struct
        {
            u16 nPhase; ///< operation phase of HOME commnad
        } home; ///< extra data needed for a HOME command

        struct
        {
            u16 nNotified; ///< it indicats whether the main applet has been notified
        } background; ///< extra data needed for a BACKGROUND command

        struct
        {
            IBase *pIssuer; ///< the instance that issues the flush request
            PfnFlushCallback pfnResult; ///< the callback function of flush command
        } flush; ///< extra data needed for a FLUSH command

        struct
        {
            MAEInstId_t tInstId; ///< instance that changes its attributes
            u16 nValue; ///< specified applet attributes
            u16 nEnabled; ///< indicates to enable or disable the attributes
        } attribs; ///< extra data needed for a SETATTRIBS command

        struct
        {
            s16 nTarSidx;
            s16 nDestSidx;
        } disclose;

        struct
        {
            u32 aValue[4]; ///< for dumping information
        } data;
    };
} APM_ActionItem_t;

enum
{
    APM_AQ_UPDATED		= 0x0001, ///< indicates that the action queue has been updated
    APM_AQ_PROCESSING	= 0x0002, ///< indicates that APM is processing actions
    APM_AQ_AFFECTED		= 0x0004, ///< indicates that the action queue has been affected during processing

    /// actions or procedures which involves several applets will be postponed until all the events are digested
    /// - sending a start event which results in a new active applet
    /// - sending a resume event which results in a new active applet
    /// - sending stop events to the rest applets of an applet unit
    /// - releasing a stopped applet
    APM_AQ_POSTPONED	= 0x0008 ///< indicates that there are postponed actions
};

/// structure of the action queue which stores the commands to be executed
typedef struct
{
    /// the array to store the actions and their execution status
    APM_ActionItem_t tActions[APM_MAX_ACTION];
    u16 nFirst; // index to the first action waiting for processing
    u16 nLast; // index to an empty slot for next action
#ifdef __MAE_DEBUG_APM__
    u16 nUniqueID;
#endif
    /// flags and counters to indicate the status of action queue
    u16 nFlags;
    u16 nConfirmed;
} APM_ActionQueue_t;

/// enums of the execution phases of a Back-to-Home operation
enum
{
    /// closing phase stops every applet above the base applet until the operation is canceled
    APM_HOME_CLOSING = 0,
    // ZINC: obsolete phase; home and flush can be combined in a single flush command
    // and now the definition of close-back-to-home and flush commands is that home closes all
    // applets above the topmost base applet, and flush do back to home applet, close applets or
    // move them to background stack above the home applet
    /// reforming phase reforms the applet stack, and swaps important applets to background
    APM_HOME_REFORMING
};

/// enums for stack locations
enum
{
    APM_STACK_NOT_FOUND = 0,
    APM_STACK_FOREGROUND,
    APM_STACK_BACKGROUND
};

/// structure to retrieve the information of applet stack
typedef struct
{
    s8 nTargetLoc; // location of the specified applet
    s8 nTargetSidx; // stack position of the specified applet

    s8 nHomeSidx; // postion of the first base (home) applet in foreground stack
    s8 nBottomSidx; // postion of the bottom applet (the last applet above home) in foreground stack
} APM_StackInfo_t;

//
// private functions
//
// initial function of the APM module
MAERet_t MAE_APM_Init(void);
// terminative function of the APM module
MAERet_t MAE_APM_Terminate(void);
// the handler function which processes applet related requests
boolean MAE_APM_ProcessAction(void);
// the shutdown procedure which closes all the applets
MAERet_t MAE_APM_Shutdown(void);

// StartApplet() method of IShell
MAERet_t MAE_Shell_StartApplet(IShell*, MAEClsId_t, u32, IAPPLET**);
// StartAppletEx() method of IShell
MAERet_t MAE_Shell_StartAppletEx(IShell*, MAEClsId_t, u32, IAPPLET**, u32, PfnStartParamCleanup);
// CloseApplet() method of IShell
MAERet_t MAE_Shell_CloseApplet(IShell*, boolean);
// BackgroundApplet() method of IShell
MAERet_t MAE_Shell_BackgroundApplet(IShell*);
// SetAppletAttribs() method of IShell
MAERet_t MAE_Shell_SetAppletAttribs(IShell*, u32, boolean);
// ConfirmAppletState() method of IShell
MAERet_t MAE_Shell_ConfirmAppletState(IShell*, APM_AppletConfirm_e);
// FlushAppletStack() method of IShell
MAERet_t MAE_Shell_FlushAppletStack(IShell*, PfnFlushCallback);
MAERet_t MAE_Shell_FlushAppletStackEx(IShell*, PfnFlushCallback, u32);
// ActiveApplet() method of IShell
// IApplet *MAE_Shell_ActiveApplet(IShell*);
// QueryApplet() method of IShell
u32 MAE_Shell_QueryApplet(IShell*, MAEClsId_t);
//3D switch
//Update3DMode() method of IShell
void MAE_Shell_Update3DMode(IShell *);

// it returns the address of focused applet
IAPPLET* _apm_FocusedApplet(void);
// it returns the structure of APM informations
const APM_AppletInfo_t *_apm_GetAppletInfo(void);
// it resets the APMS_FORCED_UPDATE flag
void _apm_ScreenUpdated(void);

// it dumps APM's state information and applets' status
void MAE_APM_DumpInfo(void);
// it writes APM's state information and applets' status to backtrace buffer
void MAE_APM_Backtrace(void);

// private function for Shell to do some action with caller's embedded app
void _apm_EmbeddedAppAction(MAEEvent_t nEvt, u32 nParam1, u32 nParam2, PfnCleanup pfnCleanup);

void _apm_SetAPMFlag(u32);

void _apm_SetLockAP(boolean);

#endif // __MAE_APM_PRIV_H__
