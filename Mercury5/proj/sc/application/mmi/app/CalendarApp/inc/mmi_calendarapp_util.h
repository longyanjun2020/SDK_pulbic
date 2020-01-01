
#ifndef MMI_CALENDARAPP_UTIL_H
#define MMI_CALENDARAPP_UTIL_H

#include "mmi_calendarapp.h"
#include "mmi_srv_header.h"
#include "sys_sys_wmh_sys.h"

#include "App_utility.h"

#define CAL_TIMESLOTSTR_MAX_LENGTH 3

enum
{
    WeekDayStartEnum_Sunday = 0, // (0=Sunday,1=Monday,...6=Saturday)
    WeekDayStartEnum_Monday,	 // (1=Monday,...6=Saturday,7=Sunday)
};
typedef u8 WeekDayStartEnum_e;

MAE_Ret _CalendarUtilGetCalendarTitle(MAE_DateTime_t *pFocusDate, MAE_WChar **ppDisplayStr, boolean bHasDay);
MAE_Ret _CalendarUtilSetTimeSlotList(SetPhoneTimeFormat_e eTimeFormat, ArrayClass_t *pITimeSlotListModel);
boolean _CalendarUtilSetWeekDayList(u32 nWeekStartDay, VectorClass_t *pIWeekDayListModel);
MAE_Ret _CalendarUtilConvertAlarmEnumToValue(CalendarAlarmMode_e eAlarmEnum, CalendarAlarmValue_e *pAlarmValue);
MAE_Ret _CalendarUtilConvertAlarmValueToEnum(CalendarAlarmValue_e eAlarmValue, CalendarAlarmMode_e *pAlarmEnum);
MAE_Ret _CalendarUtilGetLunarCalendar(IBase *pOwner, SetOnOff_e *pLunarCalendar);
MAE_Ret _CalendarUtilGetTimeFormat(IBase *pOwner, SetPhoneTimeFormat_e *pTimeFormat);
MAE_Ret _CalendarUtilGetDeleteDateRange(IBase *pOwner, CalendarDelEvtsType_e eDelEvtsType, MAE_DateTime_t stDelEvtsDate, DateRange_t *pDateRange);
MAE_Ret _CalendarUtilGetEventAsText(CalendarEvent_t *pCalendarEvent, MAE_WChar **ppText, IBase *pOwner);
MAE_Ret _CalendarUtilGetFreeSpace(u32 *pRemainSpace);
MAE_Ret _CalendarUtilGetDateRange(IBase *pOwner, CalendarViewType_e eCalViewType, MAE_DateTime_t *pFocusDate, DateRange_t *pDateRange);
u32 _CalendarUtilGetWeekDate(u32 nYear, u32 nMonth, u32 nDay);
u32 _CalendarUtilGetWeekDay(MAE_DateTime_t *pDate, WeekDayStartEnum_e eWeekDayStartEnum);
u32 _CalendarUtilConvertWeekDayToIndex(u32 nDay, u32 nWeekStartDay);
MAE_Ret _CalendarUtilGetWeekStartDay(IBase *pOwner, u32 *pWeekStartDay);
u32 _CalendarUtilGetMonthDaysNum(u32 nYear, u32 nMonth);
u32 _CalendarUtilGetDayOfYearNum(u32 nYear, u32 nMonth);
u32 _CalendarUtilGetRepeatCycleTextID(VCALFrequency_e eRepeatCycle);
u32 _CalendarUtilGetAlarmModeTextID(CalendarAlarmMode_e eAlarmMode);
boolean _CalendarUtilIsEventsOverlap(EvtTime_t tStartTimeA, EvtTime_t tEndTimeA, EvtTime_t tStartTimeB, EvtTime_t tEndTimeB);
boolean _CalendarUtilIsEventsOverlapInLayout(EvtTime_t tStartTimeA, EvtTime_t tEndTimeA, EvtTime_t tStartTimeB, EvtTime_t tEndTimeB);
MAE_Ret _CalendarUtilUTF8ToWSTR(u8 *pUTF8Str, MAE_WChar **ppWStr);
#ifdef __CALENDAR_SUPPORT_VCS_MMI__
MAE_Ret _CalendarUtilGetStringValue(IVPROPERTY *pIVPROPERTY, MAE_WChar **ppValue);
MAE_Ret _CalendarUtilGetPropertyValue(IVPROPERTY *pIVPROPERTY, void *pValue);
#ifdef __CALENDAR_IMPORT_VCS_MMI__
MAE_Ret _CalendarUtilImportObject(MAE_WChar *pURL, IBase *pOwner, EventExecResult_t *pResult);
MAE_Ret _CalendarUtilImportObjectEx(u8 *pBuffer, IBase *pOwner, EventExecResult_t *pResult);
MAE_Ret _CalendarUtilIsEventCanBeSaved(IBase *pOwner);
MAE_Ret _CalendarUtilGetMonthResTextByNumber(u8 nMonth, MAE_WChar **ppMonthText);
MAE_Ret _CalendarUtilImportObjectGetImportData(IVCALENDAR *pIVCALENDAR, u8 *pvCalendarStr, u32 nSize);
MAE_Ret _CalendarUtilImportObjectProcessEvent(IVCALENDAR *pIVCALENDAR, u32 nEventIdx, CalendarEvent_t **ppOutCalendarEvent);
#ifdef __APP_MMI_TODOLIST_VTODO__
MAE_Ret _CalendarUtilImportObjectProcessTodo(IBase *pOwner, IVCALENDAR *pIVCALENDAR, u32 nEventIdx, ToDoList_TaskData_t **ppOutCalendarTodo);
#endif // End of __APP_MMI_TODOLIST_VTODO__
#endif // End of __CALENDAR_IMPORT_VCS_MMI__
#endif // End of __CALENDAR_SUPPORT_VCS_MMI__

#endif /* MMI_CALENDARAPP_UTIL_H */
