/**
 * @file    mmi_common_calendar.h
 * @brief
 *
 *
 * @author
 * @version $Id: mmi_common_calendar.h 31865 2009-05-25 17:04:57Z sho.ding $
 */

#ifndef __MMI_COMMON_CALENDAR_H__
#define __MMI_COMMON_CALENDAR_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_eventdb_forward.h"

#define CALENDAR_SECONDS_ONE_HOUR     (COMMON_SECONDS_PER_MINUTE * COMMON_MINUTES_PER_HOUR)
#define CALENDAR_SECONDS_ONE_DAY      (CALENDAR_SECONDS_ONE_HOUR * COMMON_HOURS_PER_DAY)
#define CALENDAR_SECONDS_ONE_WEEK     (CALENDAR_SECONDS_ONE_DAY * COMMON_DAYS_PER_WEEK)

/* Type of alarm mode. */
enum
{
    CALENDAR_ALARM_OFF,
    CALENDAR_ALARM_IMMEDIATE,
    CALENDAR_ALARM_FIVE_MIN_BEFORE,
    CALENDAR_ALARM_TEN_MIN_BEFORE,
    CALENDAR_ALARM_FIFTEEN_MIN_BEFORE,
    CALENDAR_ALARM_THIRTY_MIN_BEFORE,
    CALENDAR_ALARM_ONE_HOUR_BEFORE,
    CALENDAR_ALARM_ONE_DAY_BEFORE

};
typedef u8 CalendarAlarmMode_e;

/* Alarm values in minutes. */
enum
{
    CALENDAR_ALARMVAL_OFF = 7200,
    CALENDAR_ALARMVAL_IMMEDIATE = 0,
    CALENDAR_ALARMVAL_FIVE_MIN = 5,
    CALENDAR_ALARMVAL_TEN_MIN = 10,
    CALENDAR_ALARMVAL_FIFTEEN_MIN = 15,
    CALENDAR_ALARMVAL_THIRTY_MIN = 30,
    CALENDAR_ALARMVAL_ONE_HOUR = 60,
    CALENDAR_ALARMVAL_ONE_DAY = 1440

};
typedef u32  CalendarAlarmValue_e;


MAE_Ret _CalendarUtilGetEventAsText(CalendarEvent_t *pCalendarEvent, MAE_WChar **ppText, IBase *pOwner);
MAE_Ret _CalendarUtilExportPlainText(IVectorModel *pIDList, MAE_WChar **ppPlainText, IBase *pOwner);
#ifdef __CALENDAR_EXPORT_VCS_MMI__
MAE_Ret _CalendarUtilExportObject(IVectorModel *pIDList, MAE_WChar **ppURL, IBase *pOwner);
#endif // __CALENDAR_EXPORT_VCS_MMI__
#ifdef __CALENDAR_IMPORT_VCS_MMI__
MAE_WChar *_CalendarUtilGetResultString(u32 nTextID, u8 nEventNum, u8 nToDoNum);
#endif // __CALENDAR_IMPORT_VCS_MMI__
MAE_Ret _CalendarUtilFillRRule(CalendarEvent_t *pCalendarEvent);
MAE_Ret _CalendarUtilConvertAlarmEnumToValue_Common(CalendarAlarmMode_e eAlarmEnum, CalendarAlarmValue_e *pAlarmValue);
MAE_Ret _CalendarUtilUTF8ToWSTR_Common(u8 *pUTF8Str, MAE_WChar **ppWStr);


#endif /* __MMI_COMMON_CALENDAR_H__ */
