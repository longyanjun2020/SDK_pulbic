#ifndef __TESTS_RTK_TIMERS__
#define __TESTS_RTK_TIMERS__

#include "rtkincl.h"

/**
 *      \fn  void testTimers_Init(u8 aMailBoxID,u32 aTraceID);
 *      \brief initialise the testTimers module
 *      \param aMailBoxID identifier of the mailbox used internally
 *      \param aTraceID   identifier of the trace module used for output
 *      \return void
 */
extern void testTimers_Init(u8 aMailBoxID,u32 aTraceID);

/**
 *      \fn void testTimers_DoTests (void);
 *      \brief apply the timers testsuite
 *      \param void
 *      \return void
 **/
extern void testTimers_DoTests (void);

/**
 *      \fn void testTimers_Notify(u16 TimerID );
 *      \brief called by TimerHandler to notify the expiration of a timer
 *      \param TimerID the identifier of the timer that expired
 *      \return void
 **/
extern void testTimers_Notify(u16 TimerID );

//
//    Defines the rtk timers agent for the tests
//    When tests are not active, it is an empty macro
//    When tests are active, it is a function call to
//    Notify the expiration of a timer.
//
#define TIMERHANDLER_NOTIFY_TESTTIMERS(TimerId)
#ifdef RTK_UNIT_TEST
#ifdef RTK_TIMERS_TEST 
#undef TIMERHANDLER_NOTIFY_TESTTIMERS
#define TIMERHANDLER_NOTIFY_TESTTIMERS(TimerId)  testTimers_Notify(TimerId)
#endif
#endif

#endif // __TESTS_RTK_TIMERS__
