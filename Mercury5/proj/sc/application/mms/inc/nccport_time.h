/**
 * @file
 * Time Porting Layer
 *
 * Basic support functions that are needed by time.
 *
 * <!-- #interface list begin -->
 * \section nccport_browser_time Interface
 * - NCCPort_time_localGMTDiff()
 * - NCCPort_time_nowTimeFrom1970()
 * - NCCPort_time_pLocalTime()
 * - NCCPort_time_strFtime()
 * - NCCPort_time_ascLocalTime()
 * - NCCPort_time_mkGMTTime()
 * - NCCPort_time_getElapsedSecondsFrom1970()
 * - NCCPort_time_getUnixTime()
 * - NCCPort_time_getUTCTimeStr()
 * - NCCPort_time_getElapsedMs()
 * - NCCPort_time_sleep()
 * - NCCPort_time_getSysTime()
 * - NCCPort_time_getGMTTimeStr()
 * - NCCPort_time_gmtime()
 * <!-- #interface list end -->
 */

#ifndef __NCCPort_TIME_H__
#define __NCCPort_TIME_H__

#include <time.h>
#ifndef _WIN32_WCE
//#include <sys/timeb.h>
#endif

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JS_StrFtime              strftime

typedef struct __db_milli_time__ {
    int32_t  seconds;       /**<seconds in integer*/
    int32_t  milliItem;     /**<millisecond in integer*/
} T_DB_Micro_Time;

/** the time format SSL uses */
typedef struct __db_system_time_
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
} T_DB_TIME_SysTime;

/**
 * Get the difference in seconds between this time zone and UTC (GMT).
 * \return the seconds difference with UTC
 */
int32_t NCCPort_time_localGMTDiff(void);

/**
 * Get elapsed time since midnight (00:00:00), January 1, 1970,
 * coordinated universal time (UTC).
 * \param nowTime pointer to T_DB_Micro_Time struct, which is used to store the elapsed time.
 *        (nowTime must not be NULL)
 */
void NCCPort_time_nowTimeFrom1970(T_DB_Micro_Time *nowTime);

/**
 * Convert elapsed time into local time(struct tm).
 * \param pLocal [IN]elapsed time by second
 *        (pLocal must not be NULL)
 * \param pTm [OUT]converted local time pointer
 *        (pTm must not be NULL)
 */
void NCCPort_time_pLocalTime(const time_t *pLocal, struct tm *pTm);

/** Translate the style of time stored in struct tm to string based on the format in MSDN. ref to strftime of MSDN when release it.
 * \param buf : Store string translated.
 * \param buflen : Max len of buf.
 * \param fmt : Format of string stored
 * \param jstm : Point to s tm struct.
 * \return Length of string stored.
 * \attention
 *    bur, fmt, jstm must not be NULL
 *    buflen must be greater than 0 and not greater than buf's really len.
 */
uint32_t NCCPort_time_strFtime(int8_t *buf, uint32_t buflen, const int8_t *fmt, const struct tm *jstm);

/**
 * Convert the elapsed time(seconds) to Local time string
 * \param pExpiration : Pointer to elapsed time(seconds).
 * \return returns a pointer to the Local Time string.
 */
int8_t *NCCPort_time_ascLocalTime(const size_t *pExpiration);

/**
 * Convert the elapsed time(seconds) to GMT time string
 * \param pExpiration : Pointer to elapsed time(seconds).
 * \return returns a pointer to the GMT Time string.
 */
int8_t *NCCPort_time_ascGmTime(int32_t *pExpiration);

/**
 * Convert the structure time to a calendar value.it's up to UTC
 * \param stm : Pointer to time structure.
 * \attention
 *    stm must not be NULL
 * \return returns the specified calendar time.
*/
int32_t NCCPort_time_mkGMTTime(struct tm stm);

/**
 * Get the system time.it's up to UTC
 * \return Return the time in elapsed seconds.
 */
uint32_t NCCPort_time_getElapsedSecondsFrom1970(void);

/**
 * function: get current time, the time format in UXIT 32 bits format
 * \param  time_ptr(output)  the unix time got
 * \attention
 *    time_ptr must not be NULL
 */
void NCCPort_time_getUnixTime(uint32_t *time_ptr);

/**
 * Get the UTC Time String by elapsed time at second.
 * \param nowTime elapsed time at second
 * \return UTC Time String
 * \attention
 *    nowTime must not be NULL
 */
int8_t *NCCPort_time_getUTCTimeStr(uint32_t *nowTime);

/**
 * Get the GMT Time String by elapsed time at second.
 * \param nowTime elapsed time at second
 * \return GMT Time String
 * \attention
 *    nowTime must not be NULL
 */
int8_t *NCCPort_time_getGMTTimeStr(uint32_t *nowTime);

/**
 * function: get the elapsed milliseconds from the system start
 * \return the elapsed milliseconds from the system start
 */
uint32_t NCCPort_time_getElapsedMs(void);

/**
 * Suspend the execution of the current thread for a specified interval
 * \param ms suspended time by millisecond
 */
void NCCPort_time_sleep(uint32_t ms);

/**
 * function: get current system time
 * \param  time_ptr[OUT]  the system time got
 * \attention
 *    time_ptr must not be NULL
 */
void NCCPort_time_getSysTime(T_DB_TIME_SysTime *time_ptr);

/**
 * Convert GMT time from seconds to struct tm.
 *
 * @param timer [in]
 *      Pointer to stored time. The time is represented as seconds elapsed since midnight (00:00:00),
 * January 1, 1970, coordinated universal time (UTC).
 *
 * @param result [out]
 *      a pointer to a structure of type tm. The fields of the returned structure hold the evaluated value of the timer argument in UTC rather than in local time.
 *
 * @return
 *      a pointer to structure of type tm.
 */
struct tm *NCCPort_time_gmtime(const time_t *timer, struct tm *result);


#ifdef __cplusplus
}
#endif

#endif /* __NCCPort_TIME_H__ */
