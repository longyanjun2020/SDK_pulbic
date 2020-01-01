/**
 * @file mmi_mae_sm.h
 *
 * This file defines the state machine engine API
 *
 * @see mmi_mae_sm_defs.h
 *
 * @version $Id: mmi_mae_sm.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
#ifndef __MMI_MAE_SM_H__
#define __MMI_MAE_SM_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_sm_debug.h"
#include "mmi_mae_sm_defs.h"

/**
 * Listener prototype,
 * This listener will be notified.
 */
typedef void (*PfnMAE_SM_OnEventProcess)(SM_Mao_t* pApp, MAE_EventId nEventId, void* pData);
typedef void (*PfnMAE_SM_OnModeEntry)(SM_Mao_t* pApp, SM_ModeId_t nMode, void* pData);
typedef void (*PfnMAE_SM_OnModeExit)(SM_Mao_t* pApp, SM_ModeId_t nMode, void* pData);
typedef void (*PfnMAE_SM_OnAction)(SM_Mao_t* pApp, SM_ModeId_t nMode, SM_TransId_t nTrans, void* pData);
typedef void (*PfnMAE_SM_OnConditinoChecking)(SM_Mao_t* pApp, SM_ModeId_t nMode, SM_TransId_t nTrans, void* pData);
typedef void (*PfnMAE_SM_OnGettingDestMode)(SM_Mao_t* pApp, SM_ModeId_t nMode, SM_TransId_t nTrans, void* pData);


/**
 * Use this function to register one set of event listener.
 * SM engine will notify these listener BEFORE the event happends.
 * SM only support one set of lisetner at one time, that is, if you
 * call this function multiple times to set the listener, the lastest one
 * will take effect.
 *
 * mae_sm_debug.c contains a sample implementation of these listener, these
 * listeners are used for unit testing logging purpose.
 * The following code is to register all listener using the sample implementation.
 * MAE_SM_SetListener(
 *	SM_Debug_OnEventProcess,
 *	SM_Debug_OnModeEntry,
 *	SM_Debug_OnModeExit,
 *	SM_Debug_OnAction,
 *	SM_Debug_OnConditinoChecking,
 *	SM_Debug_OnGettingDestMode,
 *	NULL
 *	);
 *
 * The function pointer can be NULL to disable the notify.
 *
 * @see mae_sm_debug.c
 * @param pOnEvtProcessFunc notified before processing one event (including internal and external event)
 * @param pOnModeEntryFunc notified before executing of mode entry activity
 * @param pOnModeExitFunc notified before executing of mode exit activity
 * @param pOnActionFunc notified before executing of transition action
 * @param pOnCondCheckingFunc notified before executing the condition checking
 * @param pOnGetDestMode notified before executing of selecting dynamic destination mode
 * @param pListenerData any user pData that will by pass to the call back functino when notifing.
 */
void MAE_SM_SetListener(
		PfnMAE_SM_OnEventProcess pOnEvtProcessFunc,
		PfnMAE_SM_OnModeEntry pOnModeEntryFunc,
		PfnMAE_SM_OnModeExit pOnModeExitFunc,
		PfnMAE_SM_OnAction pOnActionFunc,
		PfnMAE_SM_OnConditinoChecking pOnCondCheckingFunc,
		PfnMAE_SM_OnGettingDestMode pOnGetDestMode,
		void* pListenerData
		);

/**
 * Init global variables of SM
 */
void MAE_SM_Init(void);


/**
 * AP call this function to push state machine (only) by event.
 *
 * AP should use MAE_SM_Construct to init the mode tree structure before using this,
 * and should not call this during transition (inside action/activites functions)
 * The reentry of same ap is not allowed.
 *
 * If AP has triggered any internal events when processing the external event,
 * state machine engine will process these internal events before returning from
 * MAE_SM_ProcessEvent.
 *
 * Because this is a blocking function, AP should make the processing for one
 * external event as simple as possible, and should not trigger too much interal events
 * for one external event.
 *
 * @param   app pointer to pData structure of AP
 * @param   event Event ID the received event ID
 * @param   nParam1
 * @param   nParam2
 * @return  true if current event is listened and processed by current AP state;
 *          false otherwise.
 */
boolean MAE_SM_ProcessEvent(SM_Mao_t* pApp, MAE_EventId nEventID, u32 nParam1, u32 nParam2);

/**
 * Init MAO internal pData
 *
 * @param mao
 * @param self
 * @param dependencyNumbers
 * @param modeArray
 * @param transitionArray
 * @param eventDepArray
 * @param transForEventArray
 * @param lastActiveModeArray
 * @param currentMode
 * @return Always TRUE currently
 */
boolean MAE_SM_Construct(SM_Mao_t* mao,
                      void* self,
                      u8 modeNumbers,
                      u16 dependencyNumbers,
                      const SM_Mode_t* modeArray,
                      const SM_Transition_t* transitionArray,
                      const SM_EventDep_t* eventDepArray,
                      const SM_TransitionForEvent_t* transForEventArray,
                      SM_ModeId_t* lastActiveModeArray,
                      SM_ModeId_t* currentMode
                     );
/**
 * Init the app state machine and active the default Mode
 * This should be called after the app is created
 *
 * @param app ptr to State Machine Object
 * @return SM_ModeId_t current active mode
 */
SM_ModeId_t MAE_SM_Activate(SM_Mao_t* pApp);

/**
 * Inactive the app state machine and inactive the current active mode
 * The root mode exit activities will be executed finally.
 *
 * Note: all internal event triggered at this time will NOT be processed.
 * This should be called before the ap is released
 *
 * @param app ptr to State Machine Object
 */
void MAE_SM_InActivate(SM_Mao_t* pApp);

/**
 * Dump the status machine status including the current mode
 * and the latest 10 executed transition (only when __SM_TRANSITION_HISTORY__ is defined in mmi_mae_features.h)
 *
 * @param app ptr to State Machine Object
 * @return boolean
 */
void MAE_SM_PrintStatus(const SM_Mao_t* pApp);

/**
 * It writes information of the specified instance to the backtrace buffer.
 *
 * This function is used to dump current Mode and the transition history of a state-machine object
 * to the backtrace buffer for generating exception report.
 *
 * @param	pObj	Pointer to a state machine object
 */
void MAE_SM_Backtrace(const SM_Mao_t *pObj);

/**
 * You can use the macro generated in the _priv.h file to trigger internal Event instead of using this function.
 *
 * Send application internal Event to internal queue
 * The internal event can only be trigger during state mahcine Event handling (e.g. a transition)
 *
 * @param pSM       pointer to state machine object, ap just need to by pass this pointer from the parameter of action/activities function
 * @param event     internal Event id
 * @param nParam1    nParam1 of the Event
 * @param nParam2    nParam2 of the Event
 * @return boolean TRUE if the internal Event trigger successfully
 *                 FALSE others
 */
boolean MAE_TriggerEvent(void* pSM, MAE_EventId nEventID, u32 nParam1, u32 nParam2);

/**
 * Get current processing Event (internal/external) during transition
 * Note: this function only works during Event transition. If AP call this function ouside the transition
 * for example, in the Root mode entry (when AP is actived, root Mode entry will be executed by State Machine)
 * the result will be FALSE
 *
 * @param obj           [in] pointer to state machine object, ap just need to by pass this pointer from the parameter of action/activities function
 * @param pOutputEvt     [out] External/Internal Event ID
 * @param pOutputParam1  [out] nParam1 of this Event
 * @param pOutputParam2  [out] nParam2 of thie Event
 * @return boolean TRUE if get current processing Event successfully.
 *                 FALSE others
 */
boolean MAE_SM_GetCurrentEvent(void* pSM, MAE_EventId* pOutputEvt, u32* pOutputParam1, u32* pOutputParam2);

/**
 * Check if the giving mode of the app is activated currently.
 * Note: ROOT mode is always actived.
 *
 * @param app ptr to State Machine Object
 * @param mode
 * @return boolean TRUE if the giving mode is actived;
 *                 FALSE others
 */
boolean MAE_SM_IsModeActive(SM_Mao_t* pApp, SM_ModeId_t nMode);

/**
 * Get the active leaf mode id.
 *
 * @param app ptr to State Machine Object
 * @return mode mode id of current active leaf mode
 */
SM_ModeId_t MAE_SM_GetActiveLeafMode(SM_Mao_t* pApp);

/**
 * Check if state machine is processing an application (active/inactive mode tree or process app event)
 *
 * @return TRUE if MAE_SM_Active, MAE_SM_Active or MAE_SM_InActive is in call stack currently.
 *         FALSE others
 */
boolean MAE_SM_IsProcessing(void);


#ifdef __SM_ENABLE_STATISTICS__
/**
 * Get runtime statistic result.
 * The return value can be used to adject internal queue buffer size and for debugging.
 *
 * @param maxInternalEvt the max number of internal events appear in internal Event queue
 * @param notHandledExtEvt the total number of external Event that do not make a transition
 * @return notHandledIntEvt the total number of internal Event that do not make a transition
 */
void SM_GetStatisticResult(u32* maxInternalEvt, u32* notHandledExtEvt, u32* notHandledIntEvt);
#endif

#endif /* __MAE_SM_H__ */

