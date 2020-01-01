//==============================================================================
//
//  File        : aitu_calendar.h
//  Description : Header File of Calendar Utility
//  Author      : CZ
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AITU_CALENDAR_H_
#define _AITU_CALENDAR_H_

/** @addtogroup AIT_UTILITY
 *  @{
 */

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "mmpf_typedef.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define SEC_PER_DAY         (86400)
#define SEC_PER_HOUR        (60*60)
#define SEC_PER_MIN         (60)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

/* Date time format */
typedef struct _AUTL_DATETIME {
    MMP_USHORT  usYear;         ///< Year
    MMP_USHORT  usMonth;        ///< Month: 1 ~ 12
    MMP_USHORT  usDay;          ///< Day of month: 1 ~ 28/29/30/31
    MMP_USHORT  usDayInWeek;    ///< Sunday ~ Saturday
    MMP_USHORT  usHour;         ///< 0 ~ 11 for 12-hour, 0 ~ 23 for 24-hour
    MMP_USHORT  usMinute;       ///< 0 ~ 59
    MMP_USHORT  usSecond;       ///< 0 ~ 59
    MMP_UBYTE   ubAmOrPm;       ///< AM: 0; PM: 1 (for 12-hour only)
    MMP_BOOL    b_12FormatEn;   ///< 24-hour: 0; 12-hour: 1
} AUTL_DATETIME;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_BOOL AUTL_Calendar_ValidateTime(AUTL_DATETIME *pTime,
                                    AUTL_DATETIME *pBaseTime);
MMP_ULONG AUTL_Calendar_DateToSeconds(AUTL_DATETIME *pTime,
                                    AUTL_DATETIME *pBaseTime);
MMP_BOOL AUTL_Calendar_SecondsToDate(MMP_ULONG ulSeconds,
                                    AUTL_DATETIME *pTime,
                                    AUTL_DATETIME *pBaseTime);
MMP_LONG AUTL_Calendar_DateToDays(AUTL_DATETIME *pTime,
                                    AUTL_DATETIME *pBaseTime);
MMP_BOOL AUTL_Calendar_DaysToDate(MMP_LONG days,
                                    AUTL_DATETIME *pTime,
                                    AUTL_DATETIME *pBaseTime);

/// @}

#endif //_AITU_CALENDAR_H_
