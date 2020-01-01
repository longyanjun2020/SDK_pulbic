//==============================================================================
//
//  File        : ahc_rtc.h
//  Description : INCLUDE File for the ahc_rtc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_RTC_H_
#define _AHC_RTC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

/* For RTC Use Case */
#define RTC_USE_CASE_STAMP              (0)
#define RTC_USE_CASE_PANEL              (1)
#define MAX_RTC_USE_CASE                (2)

/* For RTC Default Time */
#ifndef RTC_DEFAULT_YEAR //may be defined in config_xxx.h
#define RTC_DEFAULT_YEAR                (2015)
#endif
#ifndef RTC_DEFAULT_MONTH //may be defined in config_xxx.h
#define RTC_DEFAULT_MONTH               (1)
#endif
#ifndef RTC_DEFAULT_DAY //may be defined in config_xxx.h
#define RTC_DEFAULT_DAY                 (1)
#endif

#ifndef RTC_DEFAULT_HOUR 
#define RTC_DEFAULT_HOUR                (8)
#endif
#ifndef RTC_DEFAULT_MIN
#define RTC_DEFAULT_MIN                 (0)
#endif
#ifndef RTC_DEFAULT_SEC
#define RTC_DEFAULT_SEC                 (0)
#endif

#ifndef RTC_MAX_YEAR
#define RTC_MAX_YEAR                    (2089)
#endif
#ifndef RTC_MIN_YEAR
#define RTC_MIN_YEAR                    (RTC_DEFAULT_YEAR)
#endif
#define RTC_MAX_MONTH                   (12)
#define RTC_MIN_MONTH                   (1)
#define RTC_MAX_DAY_31                  (31)
#define RTC_MAX_DAY_30                  (30)
#define RTC_MAX_DAY_FEB_LEAP_YEAR       (29)
#define RTC_MAX_DAY_FEB_NONLEAP_YEAR    (28)
#define RTC_MIN_DAY                     (1)
#define RTC_MAX_HOUR                    (23)
#define RTC_MIN_HOUR                    (0)
#define RTC_MAX_MIN                     (59)
#define RTC_MIN_MIN                     (0)
#define RTC_MAX_SEC                     (59)
#define RTC_MIN_SEC                     (0)

/* For Clock Setting : YYYY/MM/DD HH/MM/SS */
#define IDX_YEAR                        (0)
#define IDX_MONTH                       (1)
#define IDX_DAY                         (2)
#define IDX_HOUR                        (3)
#define IDX_MIN                         (4)
#define IDX_SEC                         (5)
#define CHECK_PASS                      (0xFF)

#define CHECK_YEAR                      (0x01)
#define CHECK_MONTH                     (0x02)
#define CHECK_DAY                       (0x04)
#define CHECK_HOUR                      (0x08)
#define CHECK_MIN                       (0x10)
#define CHECK_SEC                       (0x20)
#define CHECK_ALL                       (CHECK_YEAR | CHECK_MONTH | CHECK_DAY | CHECK_HOUR | CHECK_MIN | CHECK_SEC)

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _AHC_RTC_TIME
{
    UINT16 uwYear;
    UINT16 uwMonth;
    UINT16 uwDay;       // The date of January is 1~31
    UINT16 uwDayInWeek; // Sunday ~ Saturday
    UINT16 uwHour;   
    UINT16 uwMinute;
    UINT16 uwSecond;
    UINT8 ubAmOrPm;     // am: 0, pm: 1, work only at b_12FormatEn = MMP_TURE
    UINT8 b_12FormatEn; // for set time, to indacate which format, 0 for 24 Hours,   //1 for 12 Hours format
} AHC_RTC_TIME; //Sync it with AUTL_DATETIME

typedef struct _AHC_TIME_STRING
{
    INT8 byYear[8];
    INT8 byMonth[8];
    INT8 byDay[8];
    INT8 byHour[8];
    INT8 byMinute[8];
    INT8 bySecond[8];
} AHC_TIME_STRING;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

// RTC Function
AHC_BOOL    AHC_RTC_UpdateTime(void);
void        AHC_RTC_GetTime(AHC_RTC_TIME *psAHC_RTC_Time);
void        AHC_RTC_GetTimeEx(AHC_RTC_TIME *psAHC_RTC_Time, AHC_BOOL bUpdateRelativeTime);
AHC_BOOL    AHC_SetClock(UINT16 uiYear, UINT16 uiMonth, UINT16 uiDay, UINT16 uiDayInWeek, UINT16 uiHour, UINT16 uiMinute, UINT16 uiSecond,  UINT8 ubAmOrPm, UINT8 b_12FormatEn);
AHC_BOOL    AHC_GetClock(UINT16* puwYear, UINT16* puwMonth, UINT16* puwDay, UINT16* puwDayInWeek, UINT16* puwHour, UINT16* puwMinute, UINT16* puwSecond, UINT8* ubAmOrPm, UINT8* b_12FormatEn);
AHC_BOOL    AHC_RtcSetWakeUpEn(AHC_BOOL bEnable, UINT16 uiYear, UINT16 uiMonth, UINT16 uiDay, UINT16 uiHour, UINT16 uiMinute, UINT16 uiSecond, void *phHandleFunc);

/* RTC Timer */
AHC_BOOL    AHC_Validate_Year(UINT16 year);
UINT8       AHC_Validate_ClockSetting(INT32 *pDatetime, UINT8 ubCheckType, AHC_BOOL bAutoRestore);
AHC_BOOL    AHC_RestoreDefaultTime(UINT16 *py, UINT16 *pm, UINT16 *pd, UINT16 *pd_in_week,UINT16 *ph, UINT16 *pmm, UINT16 *ps, UINT8 *pam_pm, UINT8 *p12format_en);
AHC_BOOL    AHC_RTC_CheckBaseTime(void);

#endif //_AHC_RTC_H_
