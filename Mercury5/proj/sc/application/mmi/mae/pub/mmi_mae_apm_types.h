/**
 * @file mmi_mae_apm_types.h
 *
 * This header file defines APM enums and data types.
 *
 * @version $Id: mmi_mae_apm_types.h $
 */
#ifndef __MMI_MAE_APM_TYPES_H__
#define __MMI_MAE_APM_TYPES_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet_types.h"

/**
 * These applet attributes affect APM's behaviours when it handles the applets in stack.
 *
 * These attributes are independent and can be bitwise ORed to indicate an applet's characteristics.
 * Each applet will have default values for these attributes when it is created and put into APM's
 * applet stack. Applet can change its values by using SH_SetAppletAttribs(). APM keeps these
 * values for each applet, and adjust its processing modes when it handles the applets.
 *
 * APMF_ASYNC_SUSPEND and APMF_ASYNC_STOP indicate that the applet has to release its resources
 * or do something asynchronously before it is suspended or stopped. APM waits for the applet
 * while suspending or stopping it, until it confirms that it has already entered the correct
 * state. Applet which sets these attributes shall inform APM that its asynchronous processing has
 * completed by using SH_ConfirmAppletState().
 *
 * APMF_INTERACTIVE_STOP indicates that the applet needs user's confirmation whenever an external
 * close request (such as a Back-Home operation) tries to close it. Applet sets this attribute will
 * be resumed with APM_RESUME_STOPPING parameter when APM is processing the external close command,
 * and applet shall inform APM about user's decision after the user accpets or refuses to close
 * the applet.
 *
 * Applet enables the APMF_BASE_APPLET attribute means it's a base of the applets in stack. Usually
 * the power-on/off, security, home-screen (idle), call control applets... etc. are base applets.
 * The first base applet in foreground stack is also called the home applet. APM will not close a
 * base applet unless it requests to do so, or the system is shutting down. A Back-Home operation
 * tries to clear all the applets above the topmost base applet in foreground stack.
 */
enum
{
    APMF_ASYNC_SUSPEND		= 0x0001, ///< the applet can't be suspended immediately
    APMF_ASYNC_STOP			= 0x0002, ///< the applet can't be stopped immediately
    APMF_INTERACTIVE_STOP		= 0x0004, ///< the applet needs user's confirmation for an external close request

    APMF_BASE_APPLET			= 0x0010, ///< indicates it's a base applet in stack
    APMF_TASK_LIST				= 0x0020, ///< indicates the applet will be included in task list

    APMF_HOPPER_LOCK            = 0x0040, ///< indicates this applet will not be close in hopper test
    /// there are 16 attributes can be specified for an applet
    /// the higher 16 bits are reserved for APM's internal management
    APMF_USER_ATTRIBS			= 0xFFFF
};

/**
 * The confirmation enums used in SH_ConfirmAppletState().
 *
 * Applet confirms APM using these commands that its asynchronous operation has completed,
 * or user has made the decision, so that APM can take next step accordingly.
 */
opaque_enum(APM_AppletConfirm_e_)
{
    APM_CFM_SUSPENDED, ///< confirms APM that the applet is suspended
    APM_CFM_STOPPED, ///< confirms APM that the applet is stopped
    APM_CFM_CANCELED, ///< confirms APM that user cancels the close operation
    APM_CFM_PROCEEDING, ///< confirms APM that user accepts the close operation
    APM_CFM_BACKGROUND /// confirms APM that user want to background this applet
};

/**
 * APM queries applets about these properties by sending MAE_EVT_GET_PROPERTY event. Applets
 * shall respond to these queries so that APM can manage applets according to their status.
 */
enum
{
    /// query the applet whether it can be interruptped
    /// dParam: pointer to a APM_IntQuery_t structure
    APM_PROP_INTERRUPTIBLE = APM_PROP_BASE,

	/// query the applet whether it wants to stay in stack during a flush (or home) operation
	/// dParam: pointer to an u32 variable (TRUE or FALSE)
    APM_PROP_KEEP_IN_STACK
};

/**
 * Parameters used with applet's management events such as MAE_EVT_APP_START, MAE_EVT_APP_STOP
 * MAE_EVT_APP_SUSPEND, and MAE_EVT_APP_RESUME. APM passes these values to applets through lParam
 * to indicate the cause of the management events.
 *
 * It is possible that an applet receives MAE_EVT_APP_RESUME event when it is already active, or
 * receives MAE_EVT_APP_SUSPEND when it is in suspend state. APM doesn't allow multiple instances
 * of the same applet class unless they are started with APM_LAUNCH_EMBEDDED mode. Starting an
 * existing applet makes APM to move the applet to the topmost position in stack. It may already
 * be the current active applet, and it may fail to interrupt current active applet so that it
 * stays in suspend state. But in either situation the starting parameters will be still sent to
 * the applet to notify it of the restart condition.
 */
enum
{
    APM_START_NORMAL = 0, ///< the applet is started normally
    APM_SUSPEND_NORMAL = 0, ///< the applet is suspended normally when it starts another applet,
							    ///< or the applet is started quietly
    APM_RESUME_NORMAL = 0, ///< the applet is resumed when other applets above it are closed

    /// alternative parameters passed with MAE_EVT_APP_START event
    APM_START_EMBEDDED, ///< the applet is started in embedded mode
    // applet does not need to know that it interrupts another one
    // APM_START_INTERRUPTIVE, ///< the applet is started by interrupting another one

    /// alternative parameters passed with MAE_EVT_APP_SUSPEND event
    APM_SUSPEND_INTERRUPTED, ///< the applet is suspended becuase it is interrupted by another one

    APM_SUSPEND_INT_FAILED, ///< the applet is started but it fails to interrupt current active applet
    APM_RESTART_INT_FAILED, ///< the suspended applet is restarted by others but it fails to
							    ///< interrupt the active applet

    APM_SUSPEND_BACKGROUND, ///< the applet is started with APM_LAUNCH_BACKGROUND mode or it calls
							    ///< SH_BackgroundApplet to suspend itself
    APM_RESTART_BACKGROUND, ///< the applet is restarted with APM_LAUNCH_BACKGROUND mode

	    /// reserved options for __PREEMPTIVE_START__
	    // APM_SUSPEND_BLOCKED,
	    // APM_RESTART_BLOCKED,

	    /// alternative parameters passed with MAE_EVT_APP_RESUME event
    APM_RESUME_STOPPING, ///< the applet is resumed due to an external close request that requires
						    ///< user's confirmation to close the applet or cancel the operation
    APM_RESUME_FLUSHED, ///< the base applet is resumed after the execution of an applet stack flush
						    ///< command (including CloseApplet with BackToHome option);
						    ///< this parameter may be discarded if the applet is restarted, or moved
						    ///< to background before it is normally resumed

	    /// alternative parameters may be passed with MAE_EVT_APP_SUSPEND or MAE_EVT_APP_RESUME events
	    /// when the applet is successfully re-started; a successfully re-started applet may still
	    /// receive a SUSPEND event because it has embedded applets, or it is started quietly
    APM_RESTART_NORMAL ///< the applet is successfully re-started (either it's active or suspended)
	    // applet does not need to know that it interrupts another one
	    // APM_RESTART_INTERRUPTIVE
};

/// the launch mode and its addtional options of StartApplet() to start an applet
#define APM_LAUNCH_MODE_BITS 16
#define APM_LAUNCH_MODE(_mode_) (_mode_ & ((1 << APM_LAUNCH_MODE_BITS) - 1))
#define APM_LAUNCH_OPTION(_value_) (_value_ << APM_LAUNCH_MODE_BITS)

/**
 * The launch modes to start an applet.
 *
 * There are several launch modes to start an applet. Starting an applet with APM_LAUNCH_NORMAL
 * mode will suspend the caller applet and start a new one. But if the caller is not the active
 * applet, the starting procedure fails.
 *
 * Starting an applet with APM_LAUNCH_INTERRUPTIVE will first try to suspend current active
 * applet by querying its properties. If it refuses the interrupt request, the interrupt fails
 * and the starting applet will be put into suspend state directly.
 *
 * APM_LAUNCH_EMBEDDED indicates that the applet is to be started in embedded mode. An embedded
 * applet is considered as a child applet and will never be started individually. It is always
 * bound to its parent applet. The main applet and all of its embedded applets are grouped
 * and scheduled together in APM. Only the focused applet (either it's the main applet or an
 * embedded applet of current active applet) is allowed to start an embedded applet.
 *
 * APM_LAUNCH_BACKGROUND indicates that the applet is to be started in background. A background
 * applet will not be activated unless it's restarted normally. It's not allowed to restart an
 * existing and non-background applet into background. If an focused applet was restarted into
 * background, it looks like the applet suddenly disappears and it confuses the user.
 *
 * The launch modes can be combined with addtional options, but the options will be ignored if
 * they are not suitable to the launch mode.
 *
 * The APML_ABORT_ON_INT_FAILED option instructs APM to cancel the starting procedure when the
 * condition matches, and the applet instance is released (or left unaltered) as if it is not
 * started. The APML_QUIET option starts an applet without interrupting the active applet, unless
 * there is no other applets above the first base (home) applet. APML_ABORT_ON_INT_FAILED and
 * APML_QUIET are mutual exclusive.
 *
 * The APML_AUTO_RELEASE option instructs APM to close the caller applet instead of putting it
 * into suspend state. But a main applet can't be released when it starts an embedded applet.
 */
enum
{
    /// launch modes of an applet
    APM_LAUNCH_NORMAL = 0, ///< to start an applet normally
    APM_LAUNCH_INTERRUPTIVE, ///< to start an applet interruptively
    APM_LAUNCH_EMBEDDED, ///< to start an embedded applet
    APM_LAUNCH_BACKGROUND, ///< to start an applet into background

    /// additional options to start an applet
    /// abort the starting procedure when it can't interrupt the active applet
    /// this option can only be combined with APM_LAUNCH_INTERRUPTIVE mode, and it's incompatible
    /// with APML_QUIET option
    APML_ABORT_ON_INT_FAILED = APM_LAUNCH_OPTION(0x0001),

    /// the applet is started without interrupting the active applet, unless there is no other
    /// applets above the first base (home) applet
    /// this option can only be combined with APM_LAUNCH_INTERRUPTIVE mode, and it's incompatible
    /// with APML_ABORT_ON_INT_FAILED option
    APML_QUIET = APM_LAUNCH_OPTION(0x0002),

    /// release the caller applet instead of putting it into suspend state
    /// but a main applet can't be released when it is going to start an embedded applet
    /// this option can only be combined with APM_LAUNCH_NORMAL or APM_LAUNCH_EMBEDDED modes
    APML_AUTO_RELEASE = APM_LAUNCH_OPTION(0x0004)
};

/**
 * Results of the FlushAppletStack() method.
 */
enum
{
    APM_FLUSH_ACCOMPLISHED = 0,
    APM_FLUSH_MULTIPLE_BASE_APPLETS,
    APM_FLUSH_UNREVEALED_APPLETS,
    APM_FLUSH_CANCELED
};

/**
 * The existence information returned by QueryApplet() method.
 */
enum
{
    APM_EXIST_FOREGROUND		= 0x0001, ///< there are instances of the specified class in foreground stack
    APM_EXIST_BACKGROUND		= 0x0002, ///< there are instances of the specified class in background stack
    APM_EXIST_FOCUSED			= 0x0004, ///< the focused applet belongs to the specified class
    APM_EXIST_MULTIPLE			= 0x0008, ///< there are multiple instances of the specified class in stacks
    APM_EXIST_EMBEDDED			= 0x0010, ///< there are embedded instances of the specified class in stacks
    APM_EXIST_PENDING			= 0x0020 ///< one or more instances of the specified class is being started or stopped
};

/*
 *The Applet's location stack is changed between Foreground/Background Stack.
* Cowork with MAE_EVT_SWAP.
 */
enum{
    APM_APP_NOT_CHANGED = 0x0,  //It is not changed.
    APM_APP_BACK_TO_FORE,             //The Applet's location is moved from background to foreground.
    APM_APP_FORE_TO_BACK,             //The Applet's location is moved from foreground to background.
};


/**
 * The structure used in querying applet's APM_PROP_INTERRUPTIBLE property.
 *
 * Applet decides whether it can be interrupted by the applet of specified "ClsId", then fills
 * its answer in the "Allowed" parameter.
 */
struct APM_IntQuery_t_
{
	MAEClsId_t nClsId;
	u16 nAllowed;
};

/**
* enum for nFlushType in SH_FlushAppletStackEx
*/
enum
{
    APM_FLUSH_APPLET = 0,        ///< It will flush all applet only if there is one home applet.
    APM_FLUSH_APPLET_TO_HOME,    ///< It will flush all applet until first home applet.
    APM_FORCE_FLUSH_APPLET,      ///< It will flush all applet until only one home applet.
    APM_FLUSH_NUM
};
typedef u32 FlushAppletType_e;

#endif //__MMI_MAE_APM_TYPES_H__

