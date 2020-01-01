/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      fw_timer.h
 *
 * DESCRIPTION
 *      This file implements the interface to support timer function.
 *
 * HISTORY
 *      2008.06.12       Lester Hsu         Initial Version
 *      2008.06.30       Kate Liu           Modified data types to fit new
 *                                          coding convention.                     
 *----------------------------------------------------------------------------- 
 */


#ifndef FW_TIMER_H
#define FW_TIMER_H

#include "fw_std.h"

#ifdef  __cplusplus
extern "C" 
{
#endif

#define MF_TIMER_INVALID    0           /* defines invalid timer ID */

/*
 *  Syntax:
 *      MVOID XXX(U32 u32TimerID, PMVOID pvClientData);
 *
 *  Purpose:
 *      Defines the callback function type MF_Timer_pfn for timer event.
 *
 *  Parameters:
 *      u32TimerID
 *          [in] specifies the timer ID.
 *      pvClientData
 *          [in] specifies the caller's client data 
 *
 */
typedef MVOID (*MF_Timer_pfn)(U32 u32TimerID, PMVOID pvClientData);

#ifdef XMMI

#elif defined(WIN32) || defined(WINCE)   /* For WIN32 Platform */
/* 
 *  Syntax:
 *      MBOOL mfInitTimerMgr(HINSTANCE hInstance);
 *
 *  Purpose:
 *      Initializes the timer management by applicaiton instance.
 *
 *  Parameters:
 *      hInstance
 *          [in] Specifies the instance of WIN32 application.
 *
 *  Return Values:
 *      If succeeds, returns MBOOL_TRUE.
 *      If fails, returns MBOOL_FALSE.
 */
MBOOL mfInitTimerMgr(HINSTANCE hInstance);

#else

/* 
 *  Syntax:
 *      MBOOL mfInitTimerMgr(PMVOID pvInstance);
 *
 *  Purpose:
 *      Initializes the timer management.
 *
 *  Parameters:
 *      pvInstance
 *          [in] Not used
 *
 *  Return Values:
 *      If succeeds, returns MBOOL_TRUE.
 *      If fails, returns MBOOL_FALSE.
 */
MBOOL mfInitTimerMgr(PMVOID pvInstance);

#endif

/* 
 *  Syntax:
 *      MVOID mfEndTimerMgr();
 *
 *  Purpose:
 *      Ends the timer management
 *
 */
MVOID mfEndTimerMgr(MVOID);


/* 
 *  Syntax:
 *      U32 mfCreateTimer(U32 u32Interval, MF_Timer_pfn pfnTimerCB, PMVOID pvClientData);
 *
 *  Purpose:
 *      Creates a new timer
 *
 *  Parameters:
 *      u32Interval
 *          [in] Specifies the instance of WIN32 application.
 *
 *      pfnTimerCB
 *          [in] Specifies the callback function of timer notification.
 *
 *      pvClientData
 *          [in] Specifies the client data for the callback function of timer notification. 
 *
 *  Return Values:
 *      If succeeds, returns the timer ID.
 *      If fails, returns MF_TIMER_INVALID.
 */
 #if defined(XMMI)
 U32 mfCreateTimer(U32 u32Interval, MF_Timer_pfn pfnTimerCB, PMVOID pOwner, PMVOID pvClientData);
 #else
U32 mfCreateTimer(U32 u32Interval, MF_Timer_pfn pfnTimerCB, PMVOID pvClientData);
 #endif



/* 
 *  Syntax:
 *      MVOID mfDeleteTimer(U32 u32TimerId);
 *
 *  Purpose:
 *      Deletes the timer.
 *
 *  Parameters:
 *      u32TimerId
 *          [in] Specifies the timer ID to delete.
 *
 */
#if defined(XMMI)
MVOID mfDeleteTimer(U32 u32TimerId, PMVOID pFunc, PMVOID pOwner);
#else
MVOID mfDeleteTimer(U32 u32TimerId);
#endif

/* ----------------------------------------------------------
   The Folllowing is for Irrlicht
   ----------------------------------------------------------   
*/


#if defined(XMMI)
U32 mfConvertTickToMilliSec(U32 tick);
U32 mfConvertTickToSec(U32 tick);

#elif defined(WIN32) || defined(WINCE)
/* 
 *  Syntax:
 *      MBOOL mfInitTimerMgrByWnd(HWIN hWin);
 *
 *  Purpose:
 *      Initializes the timer management by window handle.
 *
 *  Parameters:
 *      hWin
 *          [in] Specifies the windows handle of WIN32 application.
 *
 *  Return Values:
 *      If succeeds, returns MBOOL_TRUE.
 *      If fails, returns MBOOL_FALSE.
 */
MBOOL mfInitTimerMgrByWnd(HWIN hWin);
#endif

/* 
 *  Syntax:
 *      MVOID mfTimerNotify(U32 u32TimerID);
 *
 *  Purpose:
 *      Timer event notification by extenal.
 *
 *  Parameters:
 *      u32TimerID
 *          [in] Specifies the timer ID.
 *
 */
MVOID mfTimerNotify(U32 u32TimerID);



MVOID mfSleep(U32 u32milliSec);

U32 mfClock(MVOID);
#ifdef  __cplusplus
}
#endif


#endif
