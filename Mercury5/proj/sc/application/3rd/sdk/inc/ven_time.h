#ifndef __VEN_TIME_DEFINE_H__
#define __VEN_TIME_DEFINE_H__
/**
 *
 * @file    ven_time.h
 * @brief   This file defines the graphics interface definition.
 *
 * @author  Code.Lin
 * @version $Id: ven_time.h 40108 2009-09-12 12:04:25Z code.lin $
 *
 */

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

enum
{
    VEN_TIME_RET_SUCCESS        = 0, ///< operation completed successfully
    VEN_TIME_RET_BAD_PARAM      = 1, ///< invalid input parameters
    VEN_TIME_RET_FAILED         = 2, ///< WHAT? every code here is failed
    VEN_TIME_RET_OUT_OF_MEMORY  = 3, ///< memory is not enough to complete the operation
};
typedef u32 ven_time_ret_t;

enum
{
    VEN_UTC_MINUS_1100 = 0,
    VEN_UTC_MINUS_1000,
    VEN_UTC_MINUS_900,
    VEN_UTC_MINUS_900_DST, /* UTC/GMT -9 hours with Daylight saving time: +1 hour */
    VEN_UTC_MINUS_800,
    VEN_UTC_MINUS_700,
    VEN_UTC_MINUS_600,
    VEN_UTC_MINUS_600_DST, /* UTC/GMT -6 hours with Daylight saving time: +1 hour */
    VEN_UTC_MINUS_500,
    VEN_UTC_MINUS_430,
    VEN_UTC_MINUS_400,
    VEN_UTC_MINUS_330,
    VEN_UTC_MINUS_330_DST, /* UTC/GMT -3:30 hours with Daylight saving time: +1 hour */
    VEN_UTC_MINUS_300,
    VEN_UTC_MINUS_200,
    VEN_UTC_MINUS_100,
    VEN_UTC_MINUS_100_DST, /* UTC/GMT -1 hour hours with Daylight saving time: +1 hour */
    VEN_UTC_0,
    VEN_UTC_0_DST,         /* No UTC/GMT offset Daylight saving time: +1 hour */
    VEN_UTC_PLUS_100,
    VEN_UTC_PLUS_100_DST,  /* UTC/GMT +1 hours with Daylight saving time: +1 hour */
    VEN_UTC_PLUS_200,
    VEN_UTC_PLUS_200_DST,  /* UTC/GMT +2 hours with Daylight saving time: +1 hour */
    VEN_UTC_PLUS_300,
    VEN_UTC_PLUS_300_DST,  /* UTC/GMT +3 hours with Daylight saving time: +1 hour */
    VEN_UTC_PLUS_330,
    VEN_UTC_PLUS_330_DST,  /* UTC/GMT +3:30 hours with Daylight saving time: +1 hour */
    VEN_UTC_PLUS_400,
    VEN_UTC_PLUS_430,
    VEN_UTC_PLUS_500,
    VEN_UTC_PLUS_530,
    VEN_UTC_PLUS_545,
    VEN_UTC_PLUS_600,
    VEN_UTC_PLUS_700,
    VEN_UTC_PLUS_800,
    VEN_UTC_PLUS_900,
    VEN_UTC_PLUS_930,
    VEN_UTC_PLUS_1000,
    VEN_UTC_PLUS_1000_DST, /* UTC/GMT +10 hours with Daylight saving time: +1 hour */
    VEN_UTC_PLUS_1100,
    VEN_UTC_PLUS_1200,
    VEN_UTC_MINUS_300_DST, /* UTC/GMT -3 hours with Daylight saving time: +1 hour */
    VEN_UTC_MINUS_700_DST, /* UTC/GMT -7 hours with Daylight saving time: +1 hour */  
    VEN_UTC_MINUS_800_DST, /* UTC/GMT -8 hours with Daylight saving time: +1 hour */  
    VEN_UTC_PLUS_1200_DST, /* UTC/GMT +12 hours with Daylight saving time: +1 hour */
    VEN_UTC_MINUS_1200,
    VEN_UTC_MINUS_930,
    VEN_UTC_MINUS_230,
    VEN_UTC_PLUS_630,
    VEN_UTC_PLUS_845,
    VEN_UTC_PLUS_1030,
    VEN_UTC_PLUS_1130,
    VEN_UTC_PLUS_1245,
    VEN_UTC_PLUS_1300,
    VEN_UTC_PLUS_1345,
    VEN_UTC_PLUS_1400,
     /*========== Add new time zone before this line ==========*/
    VEN_UTC_TOTAL_NUM,     /* Boundary of the time zone */
    VEN_UTC_UNDEFINED = 0xFFFF,
};
typedef u32 ven_timezone_e;

typedef struct
{
    u16 year;           ///< Year value after 1900, value range is 1900~2038
    u8  month;          ///< Month, value range is 1~12
    u8  day;            ///< Day, value range is 1~31
    u8  dayOfWeek;      ///< [1 = Monday, 7 = Sunday]
    u8  hour;           ///< Hour, value range is 0~23
    u8  minute;         ///< Minute, value range is 0~59
    u8  second;         ///< Second, value range is 0~59
    u16 secondFracPart; ///< Fractionnal part of the second, not used now
} ven_time_format_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_time_getTimeInSeconds
 *
 *  @brief  Get the time in seconds since 01/01/1970 at 00:00:00
 *
 *  @param  pTime      [in]Pointer to the input UTC time
 *  @param  pSeconds   [out]Time in seconds
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_getUTCTimeInSeconds(ven_time_format_t *pUTCTime, u32 *pSeconds);

/**
 *  ven_time_getUTCTimeFromSeconds
 *
 *  @brief  Get the UTC time by a given seconds since 01/01/1970 at 00:00:00
 *
 *  @param  pTime      [out]Pointer to the output UTC time
 *  @param  pSeconds   [in]Time in seconds to convert to UTC time
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_getUTCTimeFromSeconds(u32 seconds, ven_time_format_t *pUTCTime);

/**
 *  ven_time_setLocalTime
 *
 *  @brief  Set local time.
 *
 *  @param  pTime      [in]Pointer to the input time
 *  @param  ptVenReq   [in]The pointer of the vendor request data.
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_setLocalTime(ven_time_format_t *pTime, ven_req_data_t *ptVenReq);

/**
 *  ven_time_setTimeZone
 *
 *  @brief  Set current timezone. Local time would be updated
 *
 *  @param  ZoneId      [in]Time zone id from ven_timezone_e.
 *  @param  ptVenReq    [in]The pointer of the vendor request data.
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_setTimeZone(ven_timezone_e ZoneId, ven_req_data_t *ptVenReq);

typedef struct
{
    ven_time_ret_t  RetCode;
    u32 ZoneId;
} ven_time_setTimeZone_rsp_t;

/**
 *  ven_time_getTimeZone
 *
 *  @brief  Get current timezone.
 *
 *  @param  pSeconds   [out]Time zone id
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_getTimeZone(ven_timezone_e *pZoneId);

/**
 *  ven_time_getLocalTime
 *
 *  @brief  Get local time.
 *
 *  @param  pTime      [out]Pointer to the output time
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_getLocalTime(ven_time_format_t *pTime);

/**
 *  ven_time_getUTCTime
 *
 *  @brief  Get UTC time.
 *
 *  @param  pTime      [out]Pointer to the output time
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_getUTCTime(ven_time_format_t *pTime);

/**
 *  ven_time_convertToLocalTime
 *
 *  @brief  Convert UTC time to local time which is based on current time zone.
 *
 *  @param  pUTCTime   [in]Pointer to the input UTC time
 *  @param  pLocalTime [out]Pointer to the output local time
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_convertToLocalTime(ven_time_format_t *pUTCTime, ven_time_format_t *pLocalTime);

/**
 *  ven_time_convertToLocalTime
 *
 *  @brief  Convert local time of current time zone to UTC time
 *
 *  @param  pLocalTime [in]Pointer to the input local time
 *  @param  pUTCTime   [out]Pointer to the output UTC time
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_convertToUtcTime(ven_time_format_t *pLocalTime, ven_time_format_t *pUTCTime);

/**
 *  ven_time_getTimeOffset
 *
 *  @brief  Get time offset and day light saving
 *
 *  @param  pUTCTime   [in]Pointer to the UTC time
 *  @param  timezone [in] time zone
 *  @param  offset [in] pointer to the offset
 *  @param  pDst [in] pointer to the day light saving
 *
 *  @retval VEN_TIME_RET_SUCCESS if success
 *          VEN_TIME_RET_FAILED if failed
 *          VEN_TIME_RET_BAD_PARAM if input parameter is invalid
 */
ven_time_ret_t ven_time_getTimeOffset(ven_time_format_t *pUTCTime, ven_timezone_e timezone, s32 *pOffset, bool *pDst);

/**
*  ven_time_checkTimeRangeValid
*
*  @brief  Check time format Range is valid
*
 *  @param  pTime      [in]Pointer to the input time
*
*  @retval TRUE if success
*             FALSE if failed
*/
bool ven_time_checkTimeRangeValid(ven_time_format_t *pTime);

#endif // __VEN_TIME_DEFINE_H__

