//==============================================================================
/**
 @file ahc_datetime.h
 @brief AHC Date time functions
 @author Caesar Chang
 @version 1.0
*/

#ifndef __AHC_DATE_TIME_H__
#define __AHC_DATE_TIME_H__

#include "ahc_rtc.h"

/*******************************************************************************
 *
 *   DEFINITIONS
 *
*******************************************************************************/

#define DATETIME_BEGIN_YEAR    	(2000)
#define DATETIME_BEGIN_MONTH  	(1)
#define DATETIME_BEGIN_DAY   	(1)

#define SECONDS_PER_DAY         (24*60*60)
#define SECONDS_PER_HOUR        (60*60)
#define SECONDS_PER_MIN         (60)

/*******************************************************************************
 *
 *   TYPE DEFINITIONS
 *
*******************************************************************************/

typedef unsigned int DATE_TIME;

/*******************************************************************************
 *
 *   FUNCTIONS
 *
*******************************************************************************/

AHC_BOOL AHC_DT_IsLeapYear(int year);
AHC_BOOL AHC_DT_IsDateValid(int year, int month, int day);
AHC_BOOL AHC_DT_IsTimeValid(int hour, int min, int second);
int AHC_DT_GetDayNumber(int year, int mon, int day);
AHC_BOOL AHC_DT_DaysToDate(int days, int* year, int* month, int* day);
AHC_BOOL AHC_DT_SecondsToDateTime(DATE_TIME nDateTime, AHC_RTC_TIME *pRtcTime);
DATE_TIME AHC_DT_GetSecondsOffset(int year, int mon, int day, int hour, int min, int sec);
AHC_BOOL AHC_DT_GetSecondsOffsetFromRtc(AHC_RTC_TIME* psRtcTime, DATE_TIME* pnDateTime);
AHC_BOOL AHC_DT_ShiftRtc(AHC_RTC_TIME* psRtcTime, int nSecondOffset);

#endif // __AHC_DATE_TIME_H__