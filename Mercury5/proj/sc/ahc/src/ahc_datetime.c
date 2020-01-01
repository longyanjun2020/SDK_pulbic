//==============================================================================
/**
 @file AHC_DateTime.c
 @brief AHC Date time functions
 @author Caesar Chang
 @version 1.0
*/
/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_datetime.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

// Constants for date time calculation.
static const int   days_of_mon[12]          = { 31,  28,  31,   30,   31,   30,   31,   31,   30,   31,  30,  31 };
static const int   acc_days_of_mon[12]      = { 31,  59,  90,  120,  151,  181,  212,  243,  273,  304, 334, 365 };
static const int   acc_days_of_leap_mon[12] = { 31,  60,  91,  121,  152,  182,  213,  244,  274,  305, 335, 366 };
static const char  mon_offset_acc[12]       = {  0,   0,   3,    3,    4,    4,    5,    5,    5,    6,   6,   7 };

/*===========================================================================
 * Main body
 *===========================================================================*/

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_IsLeapYear
 *
 *   DESCRIPTION
 *
 *      Check if the year is leap year.
 *
 *   ARGUMENTS
 *
 *      year		- The year of the date.
 *
 *   RETURN
 *   
 *      AHC_TRUE  - It's leap year.
 *      AHC_FALSE - It's NOT leap year.
 *
*******************************************************************************/
AHC_BOOL AHC_DT_IsLeapYear(int year)
{
    return (!(year % 4)) && ((year % 100) || (!(year % 400)));
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_IsDateValid
 *
 *   DESCRIPTION
 *
 *      Check if the date value is valid.
 *
 *   ARGUMENTS
 *
 *      year		- The year of the date.
 *      month		- The month of the date.
 *      day        -  The day of the date.
 *
 *   RETURN
 *   
 *      AHC_TRUE  - The Time value is valid.
 *      AHC_FALSE - The Time value is invalid.
 *
*******************************************************************************/
AHC_BOOL AHC_DT_IsDateValid(int year, int month, int day)
{
    AHC_BOOL bLeapYear;
    AHC_BOOL bIsValid = AHC_TRUE;
    int      nDaysInMonth;

    if (year < 0 || year > 99)
    {
        bIsValid = AHC_FALSE;
    }

    if (month < 1 || month > 12)
    {
        bIsValid = AHC_FALSE;
    }

    bLeapYear = AHC_DT_IsLeapYear(year);
	
	if(bIsValid != AHC_FALSE)
	{
    	nDaysInMonth = days_of_mon[month-1];
	}

    if (month == 2 && bLeapYear) 
    {
        nDaysInMonth++;
    }

    if (day < 1 || day > nDaysInMonth)
    {
        bIsValid = AHC_FALSE;
    }

    return bIsValid;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_IsTimeValid
 *
 *   DESCRIPTION
 *
 *      Check if the time value is valid.
 *
 *   ARGUMENTS
 *
 *      hour		- hour
 *      min			- minitues
 *      second      - seconds
 *
 *   RETURN
 *   
 *      AHC_TRUE  - The Time value is valid.
 *      AHC_FALSE - The Time value is invalid.
 *
*******************************************************************************/
AHC_BOOL AHC_DT_IsTimeValid(int hour, int min, int second)
{
    if (hour < 24 && min < 60 && second < 60)
    {
        return AHC_TRUE;
    }

    return AHC_FALSE;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_GetDayNumber
 *
 *   DESCRIPTION
 *
 *      DayNumber from A.D.1-1-1
 *
 *   ARGUMENTS
 *      year		- The year of the date.
 *      month		- The month of the date.
 *      day         - The day of the date.
 *
 *   RETURN
 *   
 *      The days from 1-1-1.
 *
*******************************************************************************/
int AHC_DT_GetDayNumber(int year, int mon, int day)
{
    int  leap;
    int  d;

    leap = (AHC_DT_IsLeapYear(year) && (mon > 2)) ? (1) : (0);

    year -= 1;

	d = (year*365)+(year/4)-(year/100)+(year/400) +  
        (((mon-1)*31) - mon_offset_acc[mon-1] + leap) + day;

    return d;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_GetDayOffset
 *
 *   DESCRIPTION
 *
 *      Get the days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY
 *
 *   ARGUMENTS
 *
 *
 *   RETURN
 *   
 *      The days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY
 *
*******************************************************************************/
int AHC_DT_GetDayOffset(int year, int mon, int day)
{
    int offset = AHC_DT_GetDayNumber(year, mon, day) - 
    			 AHC_DT_GetDayNumber(DATETIME_BEGIN_YEAR, DATETIME_BEGIN_MONTH, DATETIME_BEGIN_DAY);

    return offset;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_DaysToDate
 *
 *   DESCRIPTION
 *
 *      Get the days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY to Year-Month-Day
 *
 *   ARGUMENTS
 *
 *      days  - The days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY.
 *      Output:
 *           year, month, day
 *   RETURN
 *      AHC_TRUE  - Successful.
 *      AHC_FALSE - Failed.
 *      
 *
*******************************************************************************/
AHC_BOOL AHC_DT_DaysToDate(int days, int* year, int* month, int* day)
{
    int 		y = (days * 400 / 146097);
    int 		t,m,d;
    const int 	*ptr_day_of_mon;

    // Get the year
    while(1)
    {
        if (days < AHC_DT_GetDayOffset(y, 1, 1))
        {
            y -= 1;
        }
        else if (days > AHC_DT_GetDayOffset(y, 12, 31))
        {
            y+=1;
        }
        else 
        {
            break;
        }
    }

    t = days - AHC_DT_GetDayOffset(y, 1, 1);

    if (AHC_DT_IsLeapYear(y))
        ptr_day_of_mon = acc_days_of_leap_mon;
    else
        ptr_day_of_mon = acc_days_of_mon;

    for (m = t/31; m < 12; m++)
    {
        if (t < ptr_day_of_mon[m])
        {
            break;
        }
    }

    d = t - ((m > 0) ? (ptr_day_of_mon[m-1]) : 0);

    *year 	= y;
    *month	= m+1;
    *day  	= d+1;

    return AHC_TRUE;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_SecondsToDateTime
 *
 *   DESCRIPTION
 *		
 *      
 *   ARGUMENTS
 *
 *      year-mon-day
 *      hour-min-sec
 *
 *   RETURN
 *      AHC_TRUE  - Successful.
 *      AHC_FALSE - Failed.
 *
*******************************************************************************/
AHC_BOOL AHC_DT_SecondsToDateTime(DATE_TIME nDateTime, AHC_RTC_TIME *pRtcTime)
{
    int days = nDateTime / SECONDS_PER_DAY;
    int nSecondsInDay = (int)(nDateTime % SECONDS_PER_DAY);
    int year, month, day;
    int hour, min, second;

    if (AHC_DT_DaysToDate(days, &year, &month, &day))
    {
        hour    = (nSecondsInDay / SECONDS_PER_HOUR);
        min     = (nSecondsInDay % SECONDS_PER_HOUR)/SECONDS_PER_MIN;    
        second  = (nSecondsInDay % SECONDS_PER_MIN);

        pRtcTime->uwYear    = year;
        pRtcTime->uwMonth   = month;
        pRtcTime->uwDay     = day;
        pRtcTime->uwHour    = hour;
        pRtcTime->uwMinute  = min;
        pRtcTime->uwSecond  = second;

        return AHC_TRUE;        
    }
    else
    {
        return AHC_FALSE;
    }
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      SecondsNumberOffset
 *
 *   DESCRIPTION
 *
 *      Get the seconds from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY 00-00-00 
 *      to Year-Month-Day hour-min-sec.
 *
 *   ARGUMENTS
 *
 *      year-mon-day
 *      hour-min-sec
 *
 *   RETURN
 *      Seconds 
 *
*******************************************************************************/
DATE_TIME AHC_DT_GetSecondsOffset(int year, int mon, int day, int hour, int min, int sec)
{
    DATE_TIME offset_day = AHC_DT_GetDayNumber(year, mon, day) - AHC_DT_GetDayNumber(DATETIME_BEGIN_YEAR, DATETIME_BEGIN_MONTH, DATETIME_BEGIN_DAY);

    DATE_TIME offset_seconds = (offset_day*SECONDS_PER_DAY)+(hour*SECONDS_PER_HOUR)+(min*SECONDS_PER_MIN)+sec;

    return offset_seconds;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_GetSecondsOffsetFromRtc
 *
 *   DESCRIPTION
 *
 *      Get the seconds from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY 00-00-00 
 *      to Year-Month-Day hour-min-sec.
 *
 *   ARGUMENTS
 *      psRtcTime - the pointer of input date-time in RTC format.
 *
 *   RETURN
 *      Seconds 
 *
*******************************************************************************/
AHC_BOOL AHC_DT_GetSecondsOffsetFromRtc(AHC_RTC_TIME* psRtcTime, DATE_TIME* pnDateTime)
{
    int nHour   = psRtcTime->uwHour;
    int nMin    = psRtcTime->uwMinute;
    int nSecond = psRtcTime->uwSecond;

    DATE_TIME nRtcDays, nOrgDays;
    DATE_TIME offset_seconds;

    nRtcDays = AHC_DT_GetDayNumber(psRtcTime->uwYear, psRtcTime->uwMonth, psRtcTime->uwDay);
    nOrgDays = AHC_DT_GetDayNumber(DATETIME_BEGIN_YEAR, DATETIME_BEGIN_MONTH, DATETIME_BEGIN_DAY);

    if (nRtcDays < nOrgDays)
    {
        // datetime overflow
        return AHC_FALSE;
    }
    
    nRtcDays -= nOrgDays;

    offset_seconds = (nRtcDays*SECONDS_PER_DAY)+(nHour*SECONDS_PER_HOUR)+(nMin*SECONDS_PER_MIN)+nSecond;

    *pnDateTime = offset_seconds;

    return AHC_TRUE;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_DT_ShiftRtc
 *
 *   DESCRIPTION
 *
 *       
 *     
 *
 *   ARGUMENTS
 *      psRtcTime - the pointer of input date-time in RTC format.
 *
 *   RETURN
 *      AHC_TRUE  - Successful.
 *      AHC_FALSE - Failed.
 *
*******************************************************************************/
AHC_BOOL AHC_DT_ShiftRtc(AHC_RTC_TIME* psRtcTime, int nSecondOffset)
{
    DATE_TIME nDateTime = 0;

    if (nSecondOffset == 0) {
        return AHC_TRUE;
    }

    if (!AHC_DT_GetSecondsOffsetFromRtc(psRtcTime, &nDateTime)) {
        return AHC_FALSE;
    }

    if (nSecondOffset < 0) {
        nDateTime -= (-nSecondOffset);
    }
    else {
        nDateTime += nSecondOffset; 
    }

    AHC_DT_SecondsToDateTime(nDateTime, psRtcTime);

    return AHC_TRUE;
}
