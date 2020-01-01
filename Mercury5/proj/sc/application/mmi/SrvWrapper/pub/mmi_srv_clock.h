/**
* @file    mmi_srv_clock.h
* @brief   
*          
*/

#ifndef __MMI_SRV_CLOCK_H__
#define __MMI_SRV_CLOCK_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_clock.h"

//Specific Service ListenerCallBack API
typedef void (*SrvClockSysTimeChangeCB)(void *pThis, MAE_DateTime_t *pLocalTime); //MAECLOCK_ID_SYSTIMECHANGE
typedef void (*SrvClockSysTimeZoneChangeCB)(void *pThis, MAE_TimeZone_e ePrimaryTimeZone); //MAECLOCK_ID_SYSTIMEZONECHANGE
typedef void (*SrvClockSecondTimeZoneChangeCB)(void *pThis, MAE_TimeZone_e eSecondaryTimeZone); //MAECLOCK_ID_SECONDTIMEZONECHANGE
typedef void (*SrvClockDateTickCB)(void *pThis); //MAECLOCK_ID_DATETICK
typedef void (*SrvClockMinuteTickCB)(void *pThis); //MAECLOCK_ID_MINUTETICK

/** SrvClockSetSysTimeChangeCB
@brief  The interface is use to Set CB which will trigger when system time change(MAE_DateTime_t).

@param[in]      pfnSysTimeChangeCB      SrvClockSysTimeChangeCB CB to info owner system time change data
*/
void SrvClockSetSysTimeChangeCB(SrvClockSysTimeChangeCB pfnSysTimeChangeCB);

/** SrvClockSetSysTimeZoneChangeCB
@brief  The interface is use to Set CB which will trigger when system time zone change(MAE_TimeZone_e).

@param[in]      pfnSysTimeZoneChangeCB  SrvClockSysTimeZoneChangeCB CB to info owner system time zone change data
*/
void SrvClockSetSysTimeZoneChangeCB(SrvClockSysTimeZoneChangeCB pfnSysTimeZoneChangeCB);

/** SrvClockSetSecondTimeZoneChangeCB
@brief  The interface is use to Set CB which will trigger when secone time zone change(MAE_DateTime_t).

@param[out]     pfnSecondTimeZoneChangeCB   SrvClockSecondTimeZoneChangeCB CB to info owner second time zone change data
*/
void SrvClockSetSecondTimeZoneChangeCB(SrvClockSecondTimeZoneChangeCB pfnSecondTimeZoneChangeCB);

/** SrvClockSetDateTickCB
@brief  The interface is use to Set CB which will trigger when date tick.

@param[out]     pfnDateTickCB           SrvClockDateTickCB CB to info owner date tick
*/
void SrvClockSetDateTickCB(SrvClockDateTickCB pfnDateTickCB);

/** SrvClockSetMinuteTickCB
@brief  The interface is use to Set CB which will trigger when minute tick.

@param[out]     pfnMinuteTickCB         SrvClockMinuteTickCB CB to info owner minute tick
*/
void SrvClockSetMinuteTickCB(SrvClockMinuteTickCB pfnMinuteTickCB);

/** SrvClockSetTime
@brief  Set current time. The time is the local time referring to the timezone.

@param[in]      pLocalTime              Datetime structure

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_BAD_PARAM               If The converted UTC time is invalid. 
*/
MAE_Ret SrvClockSetTime(MAE_DateTime_t *pLocalTime);

/** SrvClockGetTime
@brief  Get current time. The time is the local time referring to the timezone.

@param[out]     pDateTime               Datetime structure.

@return MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvClockGetTime(MAE_DateTime_t *pDateTime);

/** SrvClockGetTimeEx
@brief  Get current time of the gven timezone. The time is the local time referring to the timezone.

@param[in]      eTimeZone               Timezone
@param[out]     pDateTime               Datetime structure

@return MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvClockGetTimeEx(MAE_TimeZone_e eTimeZone, MAE_DateTime_t *pDateTime);

/** SrvClockGetTimeRange
@brief  Get current time range. The time is the local time referring to the timezone.

@param[out]     pMinDateTime               Datetime structure.
@param[out]     pMaxDateTime               Datetime structure.

@return MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvClockGetTimeRange(MAE_DateTime_t *pMinDateTime, MAE_DateTime_t *pMaxDateTime);

/** SrvClockGetTimeInSeconds
@brief  Get current time. The time is the local time referring to the timezone.

@return Get the time in seconds since 01/01/1970 at 00:00:00.
*/
u32 SrvClockGetTimeInSeconds(void);

/** SrvClockSetTimeZone
@brief  Set current timezone. Local time would be updated to keep UTC time unchanged.

@param[in]      eTimeZone               Timezone
*/
void SrvClockSetTimeZone(MAE_TimeZone_e eTimeZone);

/** SrvClockSetTimeZoneEx
@brief  Set current timezone to the given timezone field. Local time would be updated to keep UTC time unchanged.

@param[in]      eTimeZoneField          Primary/Secondary timezone field
@param[in]      eTimeZone               Timezone
*/
void SrvClockSetTimeZoneEx(MAE_TimeZone_Field_e eTimeZoneField, MAE_TimeZone_e eTimeZone);

/** SrvClockGetTimeZone
@brief  Get current timezone value.

@return Place holder to timezone.
*/
MAE_TimeZone_e SrvClockGetTimeZone(void);

/** SrvClockGetTimeZoneEx
@brief  Get current timezone value of the given timezone field.

@param[in]      eTimeZondField          Primary/Secondary timezone field

@return Place holder to timezone.
*/
MAE_TimeZone_e SrvClockGetTimeZoneEx(MAE_TimeZone_Field_e eTimeZondField);

/** SrvClockConvertToLocalTime
@brief  Convert UTC time to local time.

@param[in]      pUTCTime                UTC time.
@param[out]     pLocalTime              local time.

@return MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvClockConvertToLocalTime(MAE_DateTime_t *pUTCTime, MAE_DateTime_t *pLocalTime);

/** SrvClockConvertToUTCTime
@brief  Convert local time to UTC time.

@param[in]      pLocalTime              local time.
@param[out]     pUTCTime                UTC time.

@return MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvClockConvertToUTCTime(MAE_DateTime_t *pLocalTime, MAE_DateTime_t *pUTCTime);

/** SrvClockGetTimeOffset
@brief  Get the offset for a given time in UTC format at a particular time zone.

@param[in]      pUTCTime                UTC time.
@param[in]      eTimezone               Timezone.
@param[out]     pOffset                 offset in seconds.
@param[in]      pDst                    TRUE if daylight saving time is applied.

@return MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvClockGetTimeOffset(MAE_DateTime_t *pUTCTime, MAE_TimeZone_e eTimezone, s32 *pOffset, boolean *pDst);

/** SrvClockCheckFactoryTime
@brief  Check and set RTC to factory time.

@param     pLocalTime              Local factory time.
*/
void SrvClockCheckFactoryTime(MAE_DateTime_t *pLocalTime);

/** SrvClockSetDaylightSavingTime
@brief  Enable/Disable daylight saving time.

@param[out]     bOnOff                  TRUE/FALSE to enable/disable daylight saving time.
*/
void SrvClockSetDaylightSavingTime(boolean bOnOff);

#endif /*__MMI_SRV_CLOCK_H__*/
