/* rvtm.h - rvtm header file */
/************************************************************************
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
/*$
{package:
	{name: Tm}
	{superpackage: CCore}
	{include: rvtm.h}
	{description:
		{p: This module provides functions for creating and manipulating calendar times.
			It is basically the same as the ANSI tm structure with the addition of
			nanoseconds, accessor functions, and more natural ranges for some parameters.}
	}
}
$*/
#ifndef RV_TM_H
#define RV_TM_H

#include "rvccore.h"
#include "rvtime.h"
#include "rvlog.h"
#if (RV_OS_TYPE != RV_OS_TYPE_WINCE) && \
    !((RV_OS_TYPE == RV_OS_TYPE_MOPI) && !defined(_WIN32))
#include <time.h>
#endif
#include <string.h>

#if ((RV_OS_TYPE == RV_OS_TYPE_WINCE) && (_WIN32_WCE >= 500))
#include <time.h>
#endif
#if !defined(RV_TM_TYPE) || ((RV_TM_TYPE != RV_TM_POSIX) && \
    (RV_TM_TYPE != RV_TM_VXWORKS) && (RV_TM_TYPE != RV_TM_PSOS) && \
    (RV_TM_TYPE != RV_TM_OSE) && (RV_TM_TYPE != RV_TM_NUCLEUS) && \
    (RV_TM_TYPE != RV_TM_WIN32) && (RV_TM_TYPE != RV_TM_WINCE) && \
    (RV_TM_TYPE != RV_TM_RTK) && (RV_TM_TYPE != RV_TM_MOPI) && (RV_TM_TYPE != RV_TM_OSA))
#error RV_TM_TYPE not set properly
#endif


#if ((RV_OS_TYPE == RV_OS_TYPE_WINCE) && (_WIN32_WCE < 500))|| \
    ((RV_OS_TYPE == RV_OS_TYPE_MOPI) && !defined(_WIN32))
/* No time.h - we need to declare struct tm ourselves */
struct tm {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
        int tm_isdst;   /* daylight savings time flag */
        };

/* Clock ticks macro - ANSI version */
#define CLOCKS_PER_SEC  1000

#endif

#if ((RV_OS_TYPE == RV_OS_TYPE_RTK))
/* No time.h - we need to declare struct tm ourselves */
struct rv_tm {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
        int tm_isdst;   /* daylight savings time flag */
        };

/* Clock ticks macro - ANSI version */
//#define CLOCKS_PER_SEC  1000
extern long VT_RV_localtime(long *sec);
#endif
/*$
{type:
	{name: RvTm}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: A calendar time object.}
	}
}
$*/
typedef struct {
#if ((RV_OS_TYPE == RV_OS_TYPE_RTK))
	struct rv_tm tm;    /* just use ANSI tm definition for simplicity */
#else
	struct tm tm;    /* just use ANSI tm definition for simplicity */
#endif
	RvInt32 nsec;
} RvTm;

/* minimum size of character buffer required by RvTimeAsctime */
#define RV_TM_ASCTIME_BUFSIZE 30

/* Constants for setting the isdst field for daylight savings time */
#define RV_TM_STANDARD 0 /* Standard time */
#define RV_TM_DST 1      /* Daylight Savings time */
#define RV_TM_UNKNOWN (-1) /* unknown (error or let library calculate) */

#if defined(__cplusplus)
extern "C" {
#endif

/* Prototypes and macros */

/********************************************************************************************
 * RvTmInit - Initializes the Tm module.
 *
 * Must be called once (and only once) before any other functions in the module are called.
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : Always RV_OK
 */
RvStatus RvTmInit(void);

/********************************************************************************************
 * RvTmEnd - Shuts down the Tm module.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : Always RV_OK
 */
RvStatus RvTmEnd(void);

/********************************************************************************************
 * RvTmSourceConstruct - Constructs Tm module log source.
 *
 * Constructs log source to be used by common core when printing log from the 
 * tm module. This function is applied per instance of log manager.
 * 
 * INPUT   : logMgr - log manager instance
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code. 
 */
RvStatus RvTmSourceConstruct(
	IN RvLogMgr	*logMgr);

/********************************************************************************************
 * RvTmConvertToTime - Converts a calendar time into a standard time (seconds and nanoseconds since 1970.
 *
 * This function will also normalize the values of the calendar object (which might even
 * be the sole purpose for calling it). For example, if the value of seconds is set to 65,
 * it will be normalized to a value of 5 and minutes will be incremented along with any
 * other values that might be affected by it.
 * note:	The date range of calendar times is larger than the range that can be
 *			represented by time. If the calendar time fall outside of this range
 *			then the time result will not be correct (but the calendar time will
 *			still be normalized properly).
 *
 * INPUT   : tm     - pointer to calendar time that is to be converted.
 *			 logMgr - log manager instance.
 * OUTPUT  : t      - pointer to time structure where the result will be stored.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvTmConvertToTime(
	IN  RvTm	    *tm,
	IN  RvLogMgr*   logMgr,
	OUT RvTime	    *t);

/********************************************************************************************
 * RvTmConstructUtc - Creates a calendar time object representing UTC time based on a standard time.
 *
 * note:	Some systems do not support time zones, thus UTC time may actually
 * 			be local time, depending on how the clock was set.
 *
 * INPUT   : t      - pointer to time structure containing the time.
 *			 logMgr - log manager instance.
 * OUTPUT  : tm     - pointer to a calendar time object to be constructed.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvTmConstructUtc(
	IN  RvTime*     t,
	IN  RvLogMgr*   logMgr,
	OUT RvTm*       tm);

/********************************************************************************************
 * RvTmConstructLocal
 * 
 * Creates a calendar time object representing local time based on a standard time.
 * note:	Some systems do not support time zones and local time will report the
 * 			same time as UTC time.
 * note:	Some systems do not support daylight savings time properly and will not
 *			automatically adjust for it.
 * 
 * INPUT   : t      - pointer to time structure containing the time.
 *			 logMgr - log manager instance.
 * OUTPUT  : tm     - pointer to a calendar time object to be constructed.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvTmConstructLocal(
	IN  RvTime*     t,
	IN  RvLogMgr*   logMgr,
	OUT RvTm*       tm);

/********************************************************************************************
 * RvTmAsctime
 * 
 * Creates a character string representation of calendar time. Equivalent to
 * ANSI asctime function.
 * 
 * INPUT   : tm		- pointer to a calendar time object to create the string from.
 *			 bufsize- size of buffer (must be at least size RV_TM_ASCTIME_BUFSIZE).
 *			 logMgr - log manager instance.
 * OUTPUT  : buf	- pointer to buffer where string should be copied.
 * RETURN  : A pointer to the string buffer.
 */
RVCOREAPI
RvChar * RVCALLCONV RvTmAsctime(
	IN  RvTm*       tm,
	IN  RvSize_t	bufsize,
	IN  RvLogMgr*   logMgr,
	OUT RvChar*     buf);

/********************************************************************************************
 * RvTmStrftime
 * 
 * Creates a custom character string representation of calendar time. Equivalent to
 * ANSI strftime function.
 * note:	Use only ANSI standard formats in the format string to insure compatability
 *			across different systems.
 * 
 * INPUT   : tm		- pointer to a calendar time object to create the string from.
 *			 format	- standard ANSI strftime formatting string.
 *			 bufsize- size of result buffer
 *			 logMgr - log manager instance.
 * OUTPUT  : result	- pointer to buffer where the resulting string should be copied.
 * RETURN  : The size of the string that was generated (0 if there was a problem).
 */
RVCOREAPI RvSize_t RVCALLCONV RvTmStrftime(
	IN  RvTm*       tm, 
	IN  RvChar*     format, 
	IN  RvSize_t	maxsize,
	IN  RvLogMgr*   logMgr,
	OUT RvChar*     result);

#define RvTmConstruct(_t) ((RvTm *)memset((_t), 0, sizeof(RvTm)))
#define RvTmDestruct(_t)
#define RvTmGetNsec(_t) ((_t)->nsec)
#define RvTmSetNsec(_t, _n) ((_t)->nsec = (_n))
#define RvTmGetSec(_t) ((_t)->tm.tm_sec)
#define RvTmSetSec(_t, _s) ((_t)->tm.tm_sec = (_s))
#define RvTmGetMin(_t) ((_t)->tm.tm_min)
#define RvTmSetMin(_t, _m) ((_t)->tm.tm_min = (_m))
#define RvTmGetHour(_t) ((_t)->tm.tm_hour)
#define RvTmSetHour(_t, _h) ((_t)->tm.tm_hour = (_h))
#define RvTmGetMday(_t) ((_t)->tm.tm_mday)
#define RvTmSetMday(_t, _m) ((_t)->tm.tm_mday = (_m))
#define RvTmGetMon(_t) ((_t)->tm.tm_mon + 1)
#define RvTmSetMon(_t, _m) ((_t)->tm.tm_mon = (_m) - 1)
#define RvTmGetYear(_t) ((_t)->tm.tm_year + 1900)
#define RvTmSetYear(_t, _y) ((_t)->tm.tm_year = (_y) - 1900)
#define RvTmGetWday(_t) ((_t)->tm.tm_wday)
#define RvTmSetWday(_t, _w) ((_t)->tm.tm_wday = (_w))
#define RvTmGetYday(_t) ((_t)->tm.tm_yday)
#define RvTmSetYday(_t, _y) ((_t)->tm.tm_yday = (_y))
#define RvTmGetIsdst(t) ((t)->tm.tm_isdst)
#define RvTmSetIsdst(_t, _i) ((_t)->tm.tm_isdst = (_i))

#if defined(__cplusplus)
}
#endif

/*$
{function:
	{name: RvTmConstruct}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Creates a blank calendar time object.}
	}
	{proto: RvTm *RvTmConstruct(RvTm *_t);}
	{params:
		{param: {n: _t}  {d: Pointer to calendar time object to be constructed.}}
	}
	{returns: A pointer to the calendar time object that was passed in.}
}
$*/
/*$
{function:
	{name: RvTmDestruct}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Destroys a calendar time object.}
	}
	{proto: void RvTmDestruct(RvTm *_t);}
	{params:
		{param: {n: _t}  {d: Pointer to a calendar time object to be destructed.}}
	}
}
$*/





/*$
{function:
	{name: RvTmGetNsec}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the nanseconds component of a calender time.}
	}
	{proto: RvInt32 RvTmGetNsec(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The nanoseconds component of the calendar time.}
}
$*/
/*$
{function:
	{name: RvTmSetNsec}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the nanseconds component of a calender time.}
	}
	{proto: RvInt32 RvTmSetNsec(RvTm *_t, RvInt32 _n);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _n} {d: number of nanoseconds.}}
	}
	{returns: The nanoseconds value that was set.}
}
$*/
/*$
{function:
	{name: RvTmGetSec}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the seconds component of a calender time.}
	}
	{proto: RvInt RvTmGetSec(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The seconds component of the calendar time.}
}
$*/
/*$
{function:
	{name: RvTmSetSec}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the seconds component of a calender time.}
	}
	{proto: RvInt RvTmSetSec(RvTm *_t, RvInt _s);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _s} {d: number of seconds.}}
	}
	{returns: The seconds value that was set.}
}
$*/
/*$
{function:
	{name: RvTmGetMin}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the minutes component of a calender time.}
	}
	{proto: RvInt RvTmGetMin(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The minutes component of the calendar time.}
}
$*/
/*$
{function:
	{name: RvTmSetMin}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the minutes component of a calender time.}
	}
	{proto: RvInt RvTmSetMin(RvTm *_t, RvInt _m);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _m} {d: number of minutes.}}
	}
	{returns: The minutes value that was set.}
}
$*/
/*$
{function:
	{name: RvTmGetHour}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the hour component of a calender time.}
	}
	{proto: RvInt RvTmGetHour(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The hour component of the calendar time.}
}
$*/
/*$
{function:
	{name: RvTmSetHour}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the hour component of a calender time.}
	}
	{proto: RvInt RvTmSetHour(RvTm *_t, RvInt _h);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _h} {d: number of hours.}}
	}
	{returns: The hour value that was set.}
}
$*/
/*$
{function:
	{name: RvTmGetMday}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the day of the month component of a calender time.}
	}
	{proto: RvInt RvTmGetMday(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The day of the month component of the calendar time.}
}
$*/
/*$
{function:
	{name: RvTmSetMday}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the day of the month component of a calender time.}
	}
	{proto: RvInt RvTmSetMday(RvTm *_t, RvInt _m);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _m} {d: day of the month.}}
	}
	{returns: The day of the month value that was set.}
}
$*/
/*$
{function:
	{name: RvTmGetMon}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the month of the year component of a calender time (1 = January, 12 = December).}
	}
	{proto: RvInt RvTmGetMon(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The month of the year component of the calendar time (1 = January, 12 = December).}
	{notes:
		{note:  This value is different then the standard ANSI tm format in that
				a month value of 1 is January whereas using the standard ANSI tm
				structure January would be a 0.}
	}
}
$*/
/*$
{function:
	{name: RvTmSetMon}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the month of the year component of a calender time (1 = January, 12 = December).}
	}
	{proto: RvInt RvTmSetMon(RvTm *_t, RvInt _m);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _m} {d: month of the year (1 = January, 12 = December).}}
	}
	{returns: The month of the year value that was set.}
	{notes:
		{note:  This value is different then the standard ANSI tm format in that
				a month value of 1 is January whereas using the standard ANSI tm
				structure January would be a 0.}
	}
}
$*/
/*$
{function:
	{name: RvTmGetYear}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the year component of a calender time.}
	}
	{proto: RvInt RvTmGetYear(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The year component of the calendar time.}
	{notes:
		{note:  This value is different then the standard ANSI tm format in that
				a year value of 2002 is year 2002 whereas using the standard
				ANSI tm structure year 2002 would be 202.}
		}
}
$*/
/*$
{function:
	{name: RvTmSetYear}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the year component of a calender time.}
	}
	{proto: RvInt RvTmSetYear(RvTm *_t, RvInt _y);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _y} {d: year.}}
	}
	{returns: The year value that was set.}
	{notes:
		{note:  This value is different then the standard ANSI tm format in that
				a year value of 2002 is year 2002 whereas using the standard
				ANSI tm structure year 2002 would be 202.}
		}
}
$*/
/*$
{function:
	{name: RvTmGetWday}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the day of the week component of a calender time (0 = Sunday, 6 = Saturday).}
	}
	{proto: RvInt RvTmGetWday(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The day of the week component of the calendar time (0 = Sunday, 6 = Saturday).}
}
$*/
/*$
{function:
	{name: RvTmSetWday}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the day of the week component of a calender time (0 = Sunday, 6 = Saturday).}
	}
	{proto: RvInt RvTmSetWday(RvTm *_t, RvInt _w);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _w} {d: day of the week (0 = Sunday, 6 = Saturday).}}
	}
	{returns: The day of the week value that was set.}
}
$*/
/*$
{function:
	{name: RvTmGetYday}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the day of the year component of a calender time (0 = January 1st)}
	}
	{proto: RvInt RvTmGetYday(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns: The day of the year component of the calendar time (0 = January 1st).}
}
$*/
/*$
{function:
	{name: RvTmSetYday}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the day of the year component of a calender time (0 = January 1st).}
	}
	{proto: RvInt RvTmSetYday(RvTm *_t, RvInt _y);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _y} {d: day of the year (0 = January 1st).}}
	}
	{returns: The day of the year value that was set.}
}
$*/
/*$
{function:
	{name: RvTmGetIsdst}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Gets the daylight savings time component of a calender time}
	}
	{proto: RvInt RvTmGetIsdst(RvTm *_t);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
	}
	{returns:	The daylight savings time component of the calendar time. Possible values
				RV_TM_STANDARD, RV_TM_DST, RV_TM_UNKNOWN.}
	{notes:
		{note:	All OS's do not handle daylight savings time properly so this value
				may not be accurate.}
	}
}
$*/
/*$
{function:
	{name: RvTmSetIsdst}
	{superpackage: Tm}
	{include: rvtm.h}
	{description:
		{p: Sets the daylight savings time component of a calender time.}
	}
	{proto: RvInt RvTmSetIsdst(RvTm *_t, RvInt _i);}
	{params:
		{param: {n: _t} {d: pointer to a calendar time object.}}
		{param: {n: _i} {d: daylight savings time. Possible values RV_TM_STANDARD, RV_TM_DST, RV_TM_UNKNOWN.}}
	}
	{returns: The daylight savings time value that was set.}
	{notes:
		{note:	All OS's do not handle daylight savings time properly so this value
				may be ignored.}
	}
}
$*/

#endif
