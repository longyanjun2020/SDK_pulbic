/****************************************************************************/
/*  File    : drv_vm_rtc.h                                                     */
/*--------------------------------------------------------------------------*/
/*  Description: RTC API                                                  */
/*                                                                          */
/*  Contents: API prototypes for RTC                                        */
/*                                                                          */
/****************************************************************************/

#ifndef __DRV_VM_RTC_H__
#define __DRV_VM_RTC_H__

#include "vm_types.ht"
#include "vm_msgof.hc"

/****************************************************************************/
/*  RTC constants                                                           */
/****************************************************************************/
/****************************************************************************/

/*** Tick Types ***/
/*** Interrupt Status ***/
#define VM_RTC_ID_NOT   0x00
#define VM_RTC_ID_TICK  0x20
#define VM_RTC_ID_ALARM 0x80
#define VM_RTC_ID_LOST_TIME 0x01


/****************************************************************************/
/*  RTC Types                                                               */
/****************************************************************************/
/****************************************************************************/

typedef struct
{
  u8  Year;
  u8  Month;
  u8  Day;
  u8  DayOfWeek; ///< [1 = Monday, 7 = Sunday]
  u8  Hour;
  u8  Minute;
  u8  Second;
  u16 SecondFracPart;         /* Fractionnal part of the second */
}vm_rtcTimeFormat_t;

typedef enum
{
    VM_RTC_NO_TICK =    0,
    VM_RTC_SECOND_TICK = (1<<0),
    VM_RTC_MINUTE_TICK = (1<<1),
    VM_RTC_HOUR_TICK = (1<<2),
    VM_RTC_DAY_TICK =  (1<<3),
    VM_RTC_NOON_TICK =  (1<<4),
    VM_RTC_MIDNIGHT_TICK =(1<<5),
    VM_RTC_MONTH_TICK =(1<<6),
    VM_RTC_YEAR_TICK = (1<<7)
}vm_rtcTickType_t;

typedef enum
{
    VM_RTC_WEEKLY_EVENT=0, ///< event at 23:59:59 of Sunday
    VM_RTC_MONTHLY_EVENT, ///< event at 23:59:59 of last day of Month
    VM_RTC_YEARLY_EVENT, ///< event at 23:59:59 of last day of Year
    VM_RTC_NO_CAL_EVENT, ///< no calendar event
}vm_rtcCalendarEvent_t;

/****************************************************************************/
/*  RTC messages types                                                      */
/****************************************************************************/
/****************************************************************************/

typedef struct
{
  vm_rtcTimeFormat_t Time;
  vm_rtcTimeFormat_t Alarm;
}vm_rtcAlarmMsg_t;

typedef struct
{
  vm_rtcTimeFormat_t Tick;
}vm_rtcTickMsg_t;

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "drv_vm_rtc_message_define__.hi"
};

/****************************************************************************/
/*  RTC functions                                                           */
/****************************************************************************/
/****************************************************************************/

s8 vm_rtcSetTime(const vm_rtcTimeFormat_t *pTime);
s8 vm_rtcGetTime(vm_rtcTimeFormat_t *pTime);
u8 vm_rtcGetStatus(bool WakeUp);
s8 vm_rtcSetTick(vm_rtcTickType_t Tick);
s8 vm_rtcStopTick(void);
s8 vm_rtcSetAlarm(const vm_rtcTimeFormat_t *pAlarm);
s8 vm_rtcGetAlarm(vm_rtcTimeFormat_t *pAlarm);
s8 vm_rtcStopAlarm(void);
void vm_rtcSubscribe(u8 mailbox);
s16 vm_rtcGetCount(void);
s32 vm_rtcGetSecondCount(void);
void vm_rtcPowerOff(void);

#endif /* __DRV_VM_RTC_H__*/
