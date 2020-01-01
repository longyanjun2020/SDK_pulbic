/**
 * @file    mmi_util_rtc.h
 *
 * @brief   This file defines the interface to access VML related to power off utilities.
 * @author	kenny.wu@mstatsemi.com
 *
 * @version $Id: mmi_util_rtc.h 28463 2009-04-15 11:12:09Z jorena.ku $
 */

#ifndef __MAE_UTIL_RTC_H__
#define __MAE_UTIL_RTC_H__

#include "mmi_mae_common_def.h"

#define MAE_DATETIME_OFFSET   100

#define MAX_RTC_TICK 32767
#define UNIT_TICK_FOR_SEC (MAX_RTC_TICK / 10)
#define UNIT_TICK_FOR_10_MILLI_SEC (MAX_RTC_TICK / 100)

/** mmi_rtc_GetOsQb()
 * @brief Return the OS Qb
 * @retval Qb counts after powering up.
 */
u32 mmi_rtc_GetOsQb(void);

/** mmi_rtc_GetOsTick()
 * @brief Return the OS tick
 * @retval Tick counts after powering up.
 */
u32 mmi_rtc_GetOsTick(void);

/**
  *    @fn mmi_rtc_ConvertQbToMilliSec
  *    @brief     Convert os Qb to Milliseconds
  *    @param  os Qb value
  *  @retval  milliseconds
  *
  */
u32 mmi_rtc_ConvertQbToMilliSec(u32 qb);
/**
  *    @fn mmi_rtc_ConvertTickToMilliSec
  *    @brief     Convert os tick to Milliseconds
  *    @param  os tick value
  *  @retval  milliseconds
  *
  */
u32 mmi_rtc_ConvertTickToMilliSec(u32 tick);

/**
  *    @fn mmi_rtc_ConvertTickToSec
  *    @brief     Convert os tick to Seconds
  *    @param  os tick value
  *  @retval  seconds
  *
  */
u32 mmi_rtc_ConvertTickToSec(u32 tick);

/**
 *	@fn mmi_rtc_IsValidDateTime
 *	@brief	Check if dateTime is in correct format.
 *	@param	date	Pointer to MAE_DateTime_t
 *  @retval	TRUE	Correct format;
 *  @retval	FALSE	Ex: month = 13, day = 32.

*/
u8 mmi_rtc_IsValidDateTime(MAE_DateTime_t *date);

/**
 *	@fn mmi_rtc_DateTimeCompare
 *	@brief	Compare two dateTime to see which is larger.
 *	@param	date1	Pointer to MAE_DateTime_t
 *	@param	date2	Pointer to MAE_DateTime_t
 *  @retval	>0		date1 is later than date2
 *  @retval	<0		date1 is sooner than date2
 *  @retval	0		date1 is equal date2

*/

s8 mmi_rtc_DateTimeCompare(MAE_DateTime_t *date1, MAE_DateTime_t* date2);


/**
 * @brief Convert date DD/MM/YYYY HH:MM:SS into time in seconds since 01/01/1970
 * @param [in] Date   Structure with date and hour
 * @return time in seconds between 01/01/1970 and date
 */

u32 mmi_rtc_DateToSeconds(MAE_DateTime_t *date);

/**
 * \brief Convert time since 01/01/1970 into DD/MM/YYYY HH:MM:SS
 * \param [in]  Time   Time in seconds since 01/01/1970
 * \param [out] Date   Structure with date and hour
 */
void mmi_rtc_SecondsToDate(u32 time, MAE_DateTime_t *date);

/**
 * \brief Get the time in seconds since 01/01/1970 at 00:00:00
 * \return the time in seconds
 */
u32 mmi_rtc_GetUTCTimeInSeconds(void);


/**
 * \brief Get the local time in seconds since 01/01/1970 at 00:00:00
 * \return the  local time in seconds
 */
u32 mmi_rtc_GetTimeInSeconds(void);

/**
 * @brief  Set the alarm with a place holder to MAE_DateTime_t
 * @param	date	Pointer to MAE_DateTime_t
 *  @retval MAE_RET_SUCCESS	Success.
 *  @retval MAE_RET_FAILED  Not success.
 */

MAE_Ret mmi_rtc_RtcSetAlarm(MAE_DateTime_t *date);

/**
 * @brief  Stop the alarm.
 * @param	date	Pointer to MAE_DateTime_t
 * @retval MAE_RET_SUCCESS	Success.
 * @retval MAE_RET_FAILED  Not success.
 */
MAE_Ret mmi_rtc_RtcStopAlarm(void);

/**
 * @brief  Calculate weekday from input date.
 * @param	date	Pointer to MAE_DateTime_t
 * @retval 0~6.	0= Sunday, 6 = Satruday.
 */

u8 mmi_rtc_ConvertWeekday(MAE_DateTime_t *date);

/** mae_initDevStr
 *	@brief Allocating a string with the format of DevString, which is defined in VML for the UCS2 format to Montage.
 *  @param size	    Character count of the string, ex: 0x0065 0x0041 0x0000, the size is 2.
 *  @param pDevStr
 */

/**
 * Sets the tick occurence configuration for time model.
 */

s8 mmi_rtc_SetTick(void);

/**
 * Disable tick count
 */
s8 mmi_rtc_StopTick(void);


/**
 * @brief  Get rtc tick.  The maximum tick value is 32767.  1 complete cycle is equivalent of 1000 ms, and each tick is about 0.03ms.
 * @retval 0~32767 tick value
 */
u16 mmi_rtc_GetTickCount(void);


/**
 * @brief  Get the second converted from hour/min/sec.  1 loop is equivalent of 1 day.
 * @retval second value converted from hour/min/sec
 */
u32 mmi_rtc_GetSecondCount(void);


/**
 * @brief  Calcuate the difference between two time period.  A time period consist of seconds and tick.
 * @param  startTimeInSec     initial time in second
 * @param  startTick          initial tick
 * @param  curTimeInSec       final time in second
 * @param  curTick            final tick
 * @param  elapsedTimeInSec   stored the elapsed time between initial and final
 * @param  elapsedTick        stored the elapsed tick between initial and final
 * @param  fractPart          stored the fractPart
 *
 */
void mmi_rtc_CalElapsedTime(u32 startTimeInSec, u16 startTick, u32 curTimeInSec, u16 curTick, u32* elapsedTimeInSec, u16* elapsedTick, u8* fractPart);


/**
 * @brief  Calcuate the difference between two time period.  A time period consist of seconds and tick.
 * @param  startTimeInSec     initial time in second
 * @param  startTick          initial tick
 * @param  curTimeInSec       final time in second
 * @param  curTick            final tick
 * @param  elapsedTimeInSec   stored the elapsed time between initial and final
 * @param  elapsedTick        stored the elapsed tick between initial and final
 * @param  fractPart          stored the fractPart (0~99 in 10 milli sec)
 *
 */
void mmi_rtc_CalElapsedTimeIn10MilliSec(u32 startTimeInSec, u16 startTick, u32 curTimeInSec, u16 curTick, u32* elapsedTimeInSec, u16* elapsedTick, u8* fractPart);



/**
 * @brief  Get numbered weekday of certain year month
 *		   If any input value is invalid, returned date would be undefined.
 * Ex: mmi_rtc_GetNumberedWeekDayOfMonth(2010, 3, 3, 6) means to get third Saturday of 2010/3
 *     the result will be 2010/3/20
 * @param  nYear         Year value after 1900, value range is 0~255.
 *						 It is only valid if the date is within 1970~2038
 * @param  nMonth        Month, value range is 1~12
 * @param  number        Value range is 1~5. 5 means the last one.
 *                       4 means to get one before the last, if there is only 4 Sunday in the month, 4 and 3 will get the same Sunday.
 *                       If inputting number is bigger than 5, result will be the last and if less than 1, result will be the first.
 * @param  nDayOfWeek    1 = Monday, 7 = Sunday
 */
MAE_DateTime_t mmi_rtc_GetNumberedWeekDayOfMonth(u8 year, u8 month, u8 number, u8 dayOfWeek);

#endif /* __MAE_UTIL_RTC_H__ */
