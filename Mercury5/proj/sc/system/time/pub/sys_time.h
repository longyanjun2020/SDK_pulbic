////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file sys_time.h
 * @brief System time API
 */

#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_vm_rtc.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    SYS_TIME_SUCCESS = 0,
    SYS_TIME_FAILED,
    SYS_TIME_INVALID_PARAM
} SysTimeRetCode_e;

typedef enum
{
    UTC_MINUS_1100 = 0,
    UTC_MINUS_1000,
    UTC_MINUS_900,
    UTC_MINUS_900_DST, /* UTC/GMT -9 hours with Daylight saving time: +1 hour */
    UTC_MINUS_800,
    UTC_MINUS_700,
    UTC_MINUS_600,
    UTC_MINUS_600_DST, /* UTC/GMT -6 hours with Daylight saving time: +1 hour */
    UTC_MINUS_500,
    UTC_MINUS_430,
    UTC_MINUS_400,
    UTC_MINUS_330,
    UTC_MINUS_330_DST, /* UTC/GMT -3:30 hours with Daylight saving time: +1 hour */
    UTC_MINUS_300,
    UTC_MINUS_200,
    UTC_MINUS_100,
    UTC_MINUS_100_DST, /* UTC/GMT -1 hour hours with Daylight saving time: +1 hour */
    UTC_0,
    UTC_0_DST,         /* No UTC/GMT offset Daylight saving time: +1 hour */
    UTC_PLUS_100,
    UTC_PLUS_100_DST,  /* UTC/GMT +1 hours with Daylight saving time: +1 hour */
    UTC_PLUS_200,
    UTC_PLUS_200_DST,  /* UTC/GMT +2 hours with Daylight saving time: +1 hour */
    UTC_PLUS_300,
    UTC_PLUS_300_DST,  /* UTC/GMT +3 hours with Daylight saving time: +1 hour */
    UTC_PLUS_330,
    UTC_PLUS_330_DST,  /* UTC/GMT +3:30 hours with Daylight saving time: +1 hour */
    UTC_PLUS_400,
    UTC_PLUS_430,
    UTC_PLUS_500,
    UTC_PLUS_530,
    UTC_PLUS_545,
    UTC_PLUS_600,
    UTC_PLUS_700,
    UTC_PLUS_800,
    UTC_PLUS_900,
    UTC_PLUS_930,
    UTC_PLUS_1000,
    UTC_PLUS_1000_DST, /* UTC/GMT +10 hours with Daylight saving time: +1 hour */
    UTC_PLUS_1100,
    UTC_PLUS_1200,
    UTC_MINUS_300_DST, /* UTC/GMT -3 hours with Daylight saving time: +1 hour */
    UTC_MINUS_700_DST, /* UTC/GMT -7 hours with Daylight saving time: +1 hour */  
    UTC_MINUS_800_DST, /* UTC/GMT -8 hours with Daylight saving time: +1 hour */  
    UTC_PLUS_1200_DST, /* UTC/GMT +12 hours with Daylight saving time: +1 hour */
    UTC_MINUS_1200,
    UTC_MINUS_930,
    UTC_MINUS_230,
    UTC_PLUS_630,
    UTC_PLUS_845,
    UTC_PLUS_1030,
    UTC_PLUS_1130,
    UTC_PLUS_1245,
    UTC_PLUS_1300,
    UTC_PLUS_1345,
    UTC_PLUS_1400,
    /*========== Add new time zone before this line ==========*/
    UTC_TOTAL_NUM,     /* Boundary of the time zone */
    UTC_UNINIT = 0xFF,
    UTC_UNDEFINED = 0xFFFF
} SysTimeTZ_e;

/*=============================================================*/
// Global function prototype
/*=============================================================*/

SysTimeRetCode_e SysTimeGetSysDefaultTime(vm_rtcTimeFormat_t *pDefaultTime);

SysTimeRetCode_e SysTimeEnableDST(bool bEnable);

//MAE_Ret MAEClock_SetTimeZone (IClock *pIClock, MAE_TimeZone_e nTimeZone)
SysTimeRetCode_e SysTimeSetTZ(SysTimeTZ_e eTZ);

//MAE_Ret MAEClock_GetTimeZone (IClock *pIClock, MAE_TimeZone_e *nTimeZone)
SysTimeRetCode_e SysTimeGetTZ(SysTimeTZ_e *peTZ);

//u8 mmi_rtc_IsValidDateTime(MAE_DateTime_t *date)
SysTimeRetCode_e SysTimeIsVaild(vm_rtcTimeFormat_t *ptTime);

//u32 vm_VmlDateToSeconds (vm_rtcTimeFormat_t *Date)
SysTimeRetCode_e SysTimeDateToSeconds(vm_rtcTimeFormat_t *ptLocalTime, u32 *pSeconds);

//void vm_VmlSecondsToDate(u32 Time, vm_rtcTimeFormat_t *Date)
SysTimeRetCode_e SysTimeSecondsToDate(vm_rtcTimeFormat_t *ptLocalTime, u32 nSeconds);

//u8 mmi_rtc_ConvertWeekday(MAE_DateTime_t *date)
SysTimeRetCode_e SysTimeConvertWeekday(vm_rtcTimeFormat_t *ptTime);

//MAE_DateTime_t mmi_rtc_GetNumberedWeekDayOfMonth(u8 nYear, u8 nMonth, u8 number, u8 nDayOfWeek)
SysTimeRetCode_e SysTimeGetNumberedWeekDayOfMonth(vm_rtcTimeFormat_t *ptTime, u8 nYear, u8 nMonth, u8 nNumber, u8 nDayOfWeek);

//static s32 _CLOCKBASE_GetDstOffset(MAE_DateTime_t *pUTCTime, const TimeZoneRule_t *pTimeZone)
SysTimeRetCode_e SysTimeGetDSTOffset(vm_rtcTimeFormat_t *ptUTCTime, SysTimeTZ_e eTZ, bool bDSTEnable, s32 *pOffset);

SysTimeRetCode_e SysTimeGetTZOffset(SysTimeTZ_e eTZ, s32 *pOffset);

//MAE_Ret CLOCKBASE_ConvertToLocalTime(ClockBase_t *pClock, MAE_DateTime_t *pUTCTime, MAE_DateTime_t *pLocalTime)
SysTimeRetCode_e SysTimeUTCToLocal(vm_rtcTimeFormat_t *ptUTCTime, vm_rtcTimeFormat_t *ptLocalTime);

//MAE_Ret MAEClock_ConvertToUTCTime(IClock *pIClock, MAE_DateTime_t *pLocalTime, MAE_DateTime_t *pUTCTime)
SysTimeRetCode_e SysTimeLocalToUTC(vm_rtcTimeFormat_t *ptUTCTime, vm_rtcTimeFormat_t *ptLocalTime);

//MAE_Ret MAEClock_SetTime (IClock *pIClock, MAE_DateTime_t *pLocalTime)
SysTimeRetCode_e SysTimeSetTime(vm_rtcTimeFormat_t *ptLocalTime);

//MAE_Ret MAEClock_GetTime (IClock *pIClock, MAE_DateTime_t *pDateTime)
SysTimeRetCode_e SysTimeGetTime(vm_rtcTimeFormat_t *ptLocalTime);

//u32 vm_VmlCurrentTimeInSeconds ( void )
SysTimeRetCode_e SysTimeGetUTCSeconds(u32 *pSeconds);

SysTimeRetCode_e SysTimeGetRange(vm_rtcTimeFormat_t *ptMinTime, vm_rtcTimeFormat_t *ptMaxTime);

#endif

