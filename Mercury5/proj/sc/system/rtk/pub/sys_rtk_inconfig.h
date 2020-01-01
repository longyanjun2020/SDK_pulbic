#ifndef __SYS_RTK_INCONFIG_H__
#define __SYS_RTK_INCONFIG_H__
/**!
 *   \file rtkinternalconfig.h
 *
 *   \brief defines constants that controls internal behaviour of RTK
 *
 ****/


//=======================================================================
//  SCHEDULER OPTIONS



//=======================================================================
//  TASKS OPTIONS
#define RTK_EQUAL_PRIORITY_TASK


//=======================================================================
//  MAILBOXS OPTIONS
#define RTK_MAILBOX_THRESHOLD_CHECK


//=======================================================================
// DEBUGGING - BENCHMARKING OPTIONS

/**!
 *    \brief define the following flag to activate benchmark on the time
 *           to choose a new task to schedule to
 ***/
//#define __MEASURE_SCHEDULING_TIME__


//=======================================================================
//  SYS PROFILE


#endif // __SYS_RTK_INCONFIG_H__

