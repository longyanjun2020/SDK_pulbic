/**
 * @file mmi_mae_sm_debug.h
 *
 * This file defines the debugging/testing function for state machine engine
 *
 * @see mmi_mae_sm.h
 * @see mmi_mae_sm_defs.h
 *
 * @version $Id: mmi_mae_sm_debug.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
#ifndef __MMI_MAE_SM_DEBUG_H__
#define __MMI_MAE_SM_DEBUG_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_features.h"
#include "mmi_mae_sm_defs.h"
/**
 * Do nothing if __MAE_DEBUG__ not defined
 */
#define MAE_SM_ADDLOG(mode, nTrans, token, isNew)        do{ }while(0)
#define MAE_SM_DUMPLOG()                                do{ }while(0)

/**
 * Let the check fail if __MAE_DEBUG__ is not defined, because
 * There do not exist any log data for checking, if we let the checking passed.
 * User will not be notified that he may forget to turn on the __MAE_DEBUG__
 */
#define MAE_SM_CHECK(exp)                               (FALSE)
#define MAE_SM_CHECKEMPTY()                             (FALSE)
/*-------------------------------------------------------------------------*/
#ifdef __MAE_DEBUG__

#define LOG_MODE_MASK           0x00FF
#define LOG_TRANS_MASK          0x03FF
#define LOG_METHOD_MASK         0x000F
#define LOG_ISNEW_MASK          0x0001

#undef MAE_SM_ADDLOG
#undef MAE_SM_DUMPLOG
#undef MAE_SM_CHECK
#undef MAE_SM_CHECKEMPTY

#define MAE_SM_CHECKREC(nMode,transNo,method)            ((nMode)| ((transNo) << 8) | ((method) << 18))
#define MAE_SM_LOG_MKREC(nMode,transNo,method,isnew)     ((nMode)| ((transNo) << 8) | ((method) << 18) | ((isnew) << 22))
#define MAE_SM_LOG_GETMODE(rec)                         (SM_ModeId_t)((rec) & LOG_MODE_MASK)
#define MAE_SM_LOG_GETTRANS(rec)                        (SM_TransId_t)((rec) >> 8 & LOG_TRANS_MASK)
#define MAE_SM_LOG_GETMETHOD(rec)                       (SM_MethodType_e)((rec) >> 18 & LOG_METHOD_MASK)
#define MAE_SM_LOG_ISNEW(rec)                           (boolean)((rec) >> 22 & LOG_ISNEW_MASK)

/*-------------------------------------------------------------------------*/
/**
 * The following macro should be used instead of using the real function call.
 * So we can disable this functionality and not compile the related code easily.
 */
#define MAE_SM_DUMPLOG                                  SM_Debug_DumpLog
#define MAE_SM_CHECK(exp)                               SM_Debug_Check((exp))
#define MAE_SM_CHECKEMPTY                               SM_Debug_CheckEmpty
/*-------------------------------------------------------------------------*/

/**
 * Init global variables and reset log queue to empty
 *
 */
void SM_Debug_Init(void);

/**
 * Dump the current log using trace function
 *
 */
void SM_Debug_DumpLog(void);

/**
 * Check if the log is empty
 *
 */
boolean SM_Debug_CheckEmpty(void);

/**
 * Get and remove the oldest log record from log queue and check if the log record matches the expected value
 * Record mark for transition start will be skipped.
 * You may use MAE_SM_CHECKREC to get the expected rec parameter
 *
 * @param nExpectedRec the expected record to checking
 * @return TRUE if the log record match the expected value
 */
boolean SM_Debug_Check(u32 nExpectedRec);

void SM_Debug_OnEventProcess(SM_Mao_t* pApp, MAE_EventId nEventId, void* pData);
void SM_Debug_OnModeEntry(SM_Mao_t* pApp, SM_ModeId_t nMode, void* pData);
void SM_Debug_OnModeExit(SM_Mao_t* pApp, SM_ModeId_t nMode, void* pData);
void SM_Debug_OnAction(SM_Mao_t* pApp, SM_ModeId_t nMode, SM_TransId_t nTrans, void* pData);
void SM_Debug_OnConditinoChecking(SM_Mao_t* pApp, SM_ModeId_t nMode, SM_TransId_t nTrans, void* pData);
void SM_Debug_OnGettingDestMode(SM_Mao_t* pApp, SM_ModeId_t nMode, SM_TransId_t nTrans, void* pData);

#endif // __MAE_DEBUG__


#endif // __MAE_SM_DEBUG_H__


