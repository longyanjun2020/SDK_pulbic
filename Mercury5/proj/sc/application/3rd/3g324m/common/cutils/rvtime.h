/***********************************************************************
Filename   : rvtime.h
Description: rvtime header file
************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/

/***********************************************************************
This module provides functions for creating and manipulating
time values. Each time value is stored in two parts, seconds
and nanoseconds. This is equivalent to the POSIX timespec structure
except that accessor functions are provided, instead of accessing
the structure directly.
This modules also provides some basic time constants:
    RV_TIME_NSECPERUSEC: Number of nanoseconds per microsecond (32 bit)
    RV_TIME_NSECPERMSEC: Number of nanoseconds per millisecond (32 bit)
    RV_TIME_NSECPERSEC: Number of nanoseconds per second (32 bit)
    RV_TIME64_NSECPERUSEC: Number of nanoseconds per microsecond (64 bit)
    RV_TIME64_NSECPERMSEC: Number of nanoseconds per millisecond (64 bit)
    RV_TIME64_NSECPERSEC: Number of nanoseconds per second (64 bit)

This module does no locking at all. Any locking of
a time object is the responsibility of the user.
***********************************************************************/

#ifndef RV_TIME_H
#define RV_TIME_H

#include "rvtypes.h"


/********************************************************************************************
 * RvTime
 * A time value in seconds and nanoseconds.
 ********************************************************************************************/
typedef struct {
	RvInt32 sec;
	RvInt32 nsec;
} RvTime;


/* Convenient constants */
#if 0//(RV_OS_TYPE == RV_OS_TYPE_RTK) // not support nanosec
#define RV_TIME_NSECPERUSEC RvInt32Const(1)
#define RV_TIME_NSECPERMSEC RvInt32Const(1000)
#define RV_TIME_NSECPERSEC RvInt32Const(1000000)
#else
#define RV_TIME_NSECPERUSEC RvInt32Const(1)
#define RV_TIME_NSECPERMSEC RvInt32Const(1000)
#define RV_TIME_NSECPERSEC RvInt32Const(1000000)
#endif

/* Set easy to use 64 bit equivalents */
#if 0//(RV_OS_TYPE == RV_OS_TYPE_RTK) // not support nanosec
#define RV_TIME64_NSECPERUSEC RvInt64Const(1,0,1)
#define RV_TIME64_NSECPERMSEC RvInt64Const(1,0,1000)
#define RV_TIME64_NSECPERSEC RvInt64Const(1,0,1000000)
#else
#define RV_TIME64_NSECPERUSEC RvInt64Const(1,0,1)
#define RV_TIME64_NSECPERMSEC RvInt64Const(1,0,1000)
#define RV_TIME64_NSECPERSEC RvInt64Const(1,0,1000000)
#endif

#if defined(__cplusplus)
extern "C" {
#endif 

/* Prototypes and macros */

/********************************************************************************************
* RvTimeConstruct
* Constructs a time.
* INPUT   : secs     - Initial value for seconds.
*           nanosecs - Initial value for nanoseconds. Valid range for this field depends
*                      on the sign of 'secs':
*                      secs > 0 :  0..999999999 
*                      secs == 0: -999999999..999999999
*                      secs < 0 : -999999999..0
* OUTPUT  : t - Pointer to time structure to construct.
* RETURN  : A pointer to the time structure or, if there is an error, NULL.
*/
RVCOREAPI 
RvTime * RVCALLCONV RvTimeConstruct( 
    IN RvInt32 secs, 
    IN RvInt32 nanosecs,
    OUT RvTime *t);

/********************************************************************************************
 * RvTimeConstructFrom64
 * Constructs a time from a 64 bit number of nanoseconds.
 * INPUT   : nanosecs - Initial time value in nanoseconds.
 * OUTPUT  : t - Pointer to time structure to construct.
 * RETURN  : A pointer to the time structure or, if there is an error, NULL.
 */
RVCOREAPI 
RvTime * RVCALLCONV RvTimeConstructFrom64(
    IN RvInt64 nanosecs,
    OUT RvTime *t);

/********************************************************************************************
 * RvTimeSubtract
 * Subracts two time values (result = newtime - oldtime).
 * INPUT   : newtime - Pointer to time structure to subract from.
 *           oldtime - Pointer to time structure with value to subract.
 * OUTPUT  : result - Pointer to time structure where result will be stored.
 * RETURN  : A pointer to the time structure or, if there is an error, NULL.
 */
RVCOREAPI 
RvTime * RVCALLCONV RvTimeSubtract(    
    IN const RvTime *newtime, 
    IN const RvTime *oldtime,
    OUT RvTime *result);

/********************************************************************************************
 * RvTimeAdd
 * Adds two time values (result = time1 + time2).
 * INPUT   : time1 - Pointer to first time.
 *           time2 - Pointer to second time structure.
 * OUTPUT  : result - Pointer to time structure where result will be stored.
 * RETURN  : A pointer to the time structure or, if there is an error, NULL.
 * NOTE    : Absolute time values wrap in the year 2038.
 */
RVCOREAPI 
RvTime * RVCALLCONV RvTimeAdd(    
    IN const RvTime *time1,     
    IN const RvTime *time2,     
    OUT RvTime *result);

/********************************************************************************************
 * RvTimeConvertTo64
 * Converts a time value to a 64 bit value in nanoseconds.
 * INPUT   : t - Pointer to time structure to be converted.
 * OUTPUT  : None.
 * RETURN  : A 64 bit nanoseconds value.
 */
RVCOREAPI 
RvInt64 RVCALLCONV RvTimeConvertTo64(    
    IN const RvTime *t);

/********************************************************************************************
 * RvTimeGetSecs
 * Get the seconds value from a time structure.
 * INPUT   : _t - Pointer to time structure to get information from.
 * RETURN  : Seconds.
 ********************************************************************************************/
#define RvTimeGetSecs(_t) ((_t)->sec)

/********************************************************************************************
 * RvTimeSetSecs
 * Sets the seconds value from a time structure.
 * INPUT   : _t - Pointer to time structure to set information in.
 *           _s - Seconds.
 * RETURN  : Seconds value that was set.
 ********************************************************************************************/
#define RvTimeSetSecs(_t, _s) ((_t)->sec = (_s))

/********************************************************************************************
 * RvTimeGetNsecs
 * Get the nanoseconds value from a time structure.
 * INPUT   : _t - Pointer to time structure to get information from.
 * RETURN  : Nanoseconds.
 ********************************************************************************************/
#define RvTimeGetNsecs(_t) ((_t)->nsec)

/********************************************************************************************
 * RvTimeSetNsecs
 * Sets the nanoseconds value of a time structure.
 * INPUT   : _t - Pointer to time structure to set information in.
 *           _s - Nanoseconds.
 * RETURN  : Nanoseconds value that was set.
 ********************************************************************************************/
#define RvTimeSetNsecs(_t, _n) ((_t)->nsec = (_n))

/********************************************************************************************
 * RvTimeDestruct
 * Destructs a time object.
 * INPUT   : _t - Pointer to time object to be destructed.
 ********************************************************************************************/
#define RvTimeDestruct(_t)

/********************************************************************************************
 * RvTimeCopy
 * Copies the value of one time structure to another.
 * INPUT   : _t - Pointer to time structure to copy information to.
 *           _s - Pointer to time structure to copy information from.
 * RETURN  : Nanoseconds value that was copied.
 ********************************************************************************************/
#define RvTimeCopy(_t, _s) ((_t)->sec = (_s)->sec,(_t)->nsec = (_s)->nsec)

#if defined(__cplusplus)
}
#endif 

#endif /* RV_TIME_H */
