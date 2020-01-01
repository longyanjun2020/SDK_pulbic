/****************************************************************************/
/*  File    : ms_defs.h                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : Constants, Macro and Prototypes for General M-Services        */
/*                                                                          */
/****************************************************************************/
/*
* --------------------------------------------------------------------------
*  Date     | Author | Revision       | Description
* ----------+--------+----------------+-------------------------------------
*/

#ifndef __MS_DEFS_H__
#define __MS_DEFS_H__

#ifdef __SDK_SIMULATION__
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define MSERV_ASSERT(X)   assert(X);
#else
#define MSERV_ASSERT(X)
#endif /* __SDK_SIMULATION__ */

/* Do not use _CUS4 in the code : use _MSERVxxxx */
#define _MSERV      _CUS7           /* Actually MSERVICES is the customer task 4 */

/* Define levels by fonctionality */
#define _MSERVTASK  _MSERV | LEVEL_0  /* Task process / init           */
#define _MSERVMSG   _MSERV | LEVEL_1  /* Messages parsing / dump       */
#define _MSERVUTIL  _MSERV | LEVEL_2  /* Utility functions             */
#define _MSERVMIC   _MSERV | LEVEL_3  /* MIC (AU System)               */
#define _MSERVGLE   _MSERV | LEVEL_4  /* GLE (AU System)               */
#define _MSERVSECU  _MSERV | LEVEL_5  /* SECURITY PACK                 */
#define _MSERVCFG   _MSERV | LEVEL_6  /* Config / Provisioning         */
#define _MSERVFILE  _MSERV | LEVEL_7  /* File API                      */
#define _MSERVNET   _MSERV | LEVEL_8  /* Network API                   */
#define _MSERVPUSH  _MSERV | LEVEL_9  /* Push                          */
#define _MSERVWTAI  _MSERV | LEVEL_10 /* Wtai                          */
#define _MSERVDISP  _MSERV | LEVEL_11 /* Display (GLE in MServices)    */
#define _MSERVKBD   _MSERV | LEVEL_12 /* Keyboard                      */
#define _MSERVDWNL  _MSERV | LEVEL_13 /* Download                      */
#define _MSERV14    _MSERV | LEVEL_14 /* Debug Anim                    */
#define _MSERVMMS   _MSERV | LEVEL_15 /* MMS                           */
#define _MSERVMMSNET _MSERV | LEVEL_16 /* MMS NETWORK                  */
#define _MSERV_RAW _MSERV | LEVEL_17 /* raw data for send/receive    */
#define _MSERVSYNCML    _MSERV | LEVEL_18 /*                               */
#define _MSERV19    _MSERV | LEVEL_19 /*                               */
#define _MSERV20    _MSERV | LEVEL_20 /*                               */
#define _MSERVMEDIA _MSERV | LEVEL_21 /* for Media                     */
#define _MSERV_SET  _MSERV | LEVEL_22 /* for Settings                  */
#define _MSERV_NET  _MSERV | LEVEL_23 /*                               */
#define _MSERV24    _MSERV | LEVEL_24 /*                               */
#define _MSERV25    _MSERV | LEVEL_25 /*                               */
#define _MSERV26    _MSERV | LEVEL_26 /*                               */
#define _MSERV27    _MSERV | LEVEL_27 /*                               */
#define _MSERV28    _MSERV | LEVEL_28 /*                               */
#define _MSERV29    _MSERV | LEVEL_29 /*                               */
#define _MSERV30    _MSERV | LEVEL_30 /*                               */
#define _MSERV31    _MSERV | LEVEL_31 /*                               */

#define _MSERVIPTVVEN   _MSERV25
#define _MSERVIPTVVIDDUMP _MSERV26
#define _MSERVIPTVBUF _MSERV27
#define _MSERVIPTVPROFILE _MSERV28
#define _MSERVIPTVNET _MSERV29
#define _MSERVIPTVDATA _MSERV30
#define _MSERVIPTV   _MSERV31 /*                               */

/***********************************************************************/
/*                       TIME                                          */
/***********************************************************************/

#define _MSERV_MS(x)  VM_RTK_MS_TO_TICK(x)          /* Milli seconds     */
#define _MSERV_SEC(x) VM_RTK_S_TO_TICK(x)           /* Seconds           */
#define _MSERV_MN(x)  VM_RTK_MN_TO_TICK(x)          /* Minutes           */

#define MSERV_SAME_KEY 0xFE

#endif  /* __MS_DEFS_H__ */
