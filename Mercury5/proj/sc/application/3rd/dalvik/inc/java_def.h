/****************************************************************************/
/*  File    : java_defs.h                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : Constants, Macro and Prototypes for General Java              */
/*                                                                          */
/****************************************************************************/
/*
* --------------------------------------------------------------------------
*  Date     | Author | Revision       | Description
*20081021+-Jacky+-------------+----------------------------------------
*/
/****************************************************************************/

#ifndef __JAVA_DEFS_H__
#define __JAVA_DEFS_H__

#include "sys_vm_dbg.ho"
#include "ven_dbg.h"


#ifdef __SDK_SIMULATION__
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define JAVA_ASSERT(X)   assert(X);
#else
#define JAVA_ASSERT(X)
#endif /* __SDK_SIMULATION__ */


#define _JAVA     VEN_DBG_GROUP_0 // _CUS5

/* Define levels by fonctionality */
#define _JAVATASK  _JAVA | LEVEL_0  /* Task process / init           */
#define _JAVAMSG   _JAVA | LEVEL_1  /* Messages parsing / dump       */
#define _JAVAUTIL  _JAVA | LEVEL_2  /* Utility functions             */
#define _JAVAAMS   _JAVA | LEVEL_3  /* AMS                           */
#define _JAVAOTA   _JAVA | LEVEL_4  /* OTA                           */
#define _JAVAGRA   _JAVA | LEVEL_5  /*  GRAPHICS                     */
#define _JAVACORE  _JAVA | LEVEL_6  /* Core service                  */
#define _JAVAFILE  _JAVA | LEVEL_7  /* File API                      */
#define _JAVANET   _JAVA | LEVEL_8  /* Network API                   */
#define _JAVAPUSH  _JAVA | LEVEL_9  /* Push                          */
#define _JAVAMMAPI _JAVA | LEVEL_10 /* MMAPI                         */
#define _JAVAWMA   _JAVA | LEVEL_11 /* Display WMA                   */
#define _JAVAKBD   _JAVA | LEVEL_12 /* Keyboard                      */
#define _JAVAINIT  _JAVA | LEVEL_13 /* Initialization                */
#define _JPXYTASK  _JAVA | LEVEL_14  /* JPxy Task       */
#define _JAVAMEM   _JAVA | LEVEL_15  /* Memory checking       */



#define JAVA_DEBUG
//#define JAVA_MEMORY_DEBUG
//#define __JAVA_DELTA_TCK__ //for running TCK

#if defined(JAVA_DEBUG)


  extern void jprintf(int flag, const char* const fmt, ...);


  #define JLOG(y,x)  jprintf(y,x);
  #define JLOG2(y, x, x2) jprintf(y, x, x2);
  #define JLOG3(y, x, x2, x3) jprintf(y, x, x2, x3);
  #define JLOG4(y, x, x2, x3, x4) jprintf(y, x, x2, x3, x4);
  #define JLOG5(y, x, x2, x3, x4, x5) jprintf(y, x, x2, x3, x4, x5);
  #define JLOG6(y, x, x2, x3, x4, x5, x6) jprintf(y, x, x2, x3, x4, x5, x6);
  #define JLOG7(y, x, x2, x3, x4, x5, x6, x7) jprintf(y, x, x2, x3, x4, x5, x6, x7);
#else
  #define JLOG(y, x) {};
  #define JLOG2(y, x, x2) {};
  #define JLOG3(y, x, x2, x3) {};
  #define JLOG4(y, x, x2, x3, x4) {};
  #define JLOG5(y, x, x2, x3, x4, x5) {};
  #define JLOG6(y, x, x2, x3, x4, x5, x6) {};
  #define JLOG7(y, x, x2, x3, x4, x5, x6, x7) {};
#endif


/***********************************************************************/
/*                       TIME                                          */
/***********************************************************************/

#define _JAVA_MS(x)  VM_RTK_MS_TO_TICK(x)          /* Milli seconds     */
#define _JAVA_SEC(x) VM_RTK_S_TO_TICK(x)           /* Seconds           */
#define _JAVA_MN(x)  VM_RTK_MN_TO_TICK(x)          /* Minutes           */

#endif  /* __JAVA_DEFS_H__ */
