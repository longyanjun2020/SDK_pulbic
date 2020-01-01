#ifndef __NEMOMP_TIME_H__
#define __NEMOMP_TIME_H__

#include "nemomp.h"
// From j9time.c
/* Frequency is microseconds / second */ 
#define J9TIME_HIRES_CLOCK_FREQUENCY ((U_64) 1000000)

#define NEMOMP_TICKS_PER_SECOND 10000 

typedef enum {
    NM_CALENDAR_YEAR=0,
    NM_CALENDAR_MONTH,
    NM_CALENDAR_DAY,
    NM_CALENDAR_HOUR,
    NM_CALENDAR_MINUTE,
    NM_CALENDAR_SECOND,
    NM_CALENDAR_TOTAL
} nm_calender_enum;

// 20091120: Added
extern int gMinTimeBetweenSystemGC;
extern nm_uint64 gLastSystemGcTime;

extern void nemomp_initialize_systemTime(void);
extern nm_uint32 nemomp_get_current_tick(void);
extern nm_uint64 nemomp_current_time(void);

/**
 * Change tick to mill-second with X multiplier. (ex: X=10)
 *
 * @param n ¡V the number of tick. ex: 10
 *
 * @return mini-seconds for n tick number.
 *
 * @note Platform depended <<Porting>>.
 *
 */
//#define nemomp_tick_to_ms(T)	((u32)(((T)* 303955) >> 16)) //(nm_uint32)(tick*10) // 10 for Fake Implement: ToDo in the future
#define nemomp_tick_to_ms(T)	((u32)(((nm_uint64)(T)* 303955) >> 16))


extern nm_uint32 nemomp_time_get_julian_day(int year, int month, int day);

extern nm_uint64 nemomp_time_get_julian_time_ms(
    unsigned short year,
    unsigned char month,
    unsigned char day,
    unsigned char hour,
    unsigned char minute,
    unsigned char second,
    int milli);

extern void nemomp_get_calendar_time(nm_uint32* datetime);
extern float nemomp_get_timezone(void);
extern nm_wchar* nemomp_get_timezone_name(void); // 20091202: Added

#endif /* __NEMOMP_TIME_H__ */
