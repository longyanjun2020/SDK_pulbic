/**
 * @file mmi_mae_eventdb.h
 * @brief   The document describes the interface of IEventDB
 * IEventDB represent event record(s) in calendar application.
 *
 * @author  nick.chou@mstarsemi.com
 * @version $Id: mmi_mae_eventdb.h 1684 2009-08-29 16:28:08Z zinc.chen $
 */
#ifndef __MMI_MAE_EVENTDB_TYPES_H__
#define __MMI_MAE_EVENTDB_TYPES_H__
/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_eventdb_forward.h"
/*-------------------------------------------------------------------------*/
#define ILLEGAL_EVENTCOUNT 0xFFFFFFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EVENTDB_CALENDAREVENT_NUID_SIZE												(sizeof(u32))
#define EVENTDB_CALENDAREVENT_NDTSTART_SIZE											(sizeof(u32))
#define EVENTDB_CALENDAREVENT_NDTEND_SIZE											(sizeof(u32))
#define EVENTDB_CALENDAREVENT_VCALRRULE_NCOUNT_SIZE									(sizeof(u32))
#define EVENTDB_CALENDAREVENT_VCALRRULE_NINTERVAL_SIZE								(sizeof(u32))
#define EVENTDB_CALENDAREVENT_VCALRRULE_VCALUTCDATE_BISUTC_SIZE						(sizeof(boolean))
#define EVENTDB_CALENDAREVENT_VCALRRULE_VCALUTCDATE_TDTUTCDATE_SIZE					(sizeof(MAE_DateTime_t))
#define EVENTDB_CALENDAREVENT_VCALRRULE_NMONTHINYEAR_SIZE							(sizeof(u32))
#define EVENTDB_CALENDAREVENT_VCALRRULE_NWEEKDAY_SIZE								((sizeof(u32))*10)
#define EVENTDB_CALENDAREVENT_VCALRRULE_NDAYINMONTH_SIZE							((sizeof(s32))*2)
#define EVENTDB_CALENDAREVENT_VCALRRULE_PDAYINYEAR_SIZE								((sizeof(u32))*20)
#define EVENTDB_CALENDAREVENT_VCALRRULE_NDWSIZE_SIZE								(sizeof(u32))
#define EVENTDB_CALENDAREVENT_VCALRRULE_NFREQUENCY_SIZE								(sizeof(u8))		
#define EVENTDB_CALENDAREVENT_VCALALARM_NRUNTIME_SIZE								(sizeof(u32))
#define EVENTDB_CALENDAREVENT_VCALALARM_TDTSNOOZETIME_SIZE							(sizeof(MAE_DateTime_t))
#define EVENTDB_CALENDAREVENT_VCALALARM_NREPEATCOUNT_SIZE							(sizeof(u32))			
#define EVENTDB_CALENDAREVENT_VCALALARM_PSTR1_SIZE									((sizeof(u8))*21)
#define EVENTDB_CALENDAREVENT_VCALALARM_PSTR2_SIZE									((sizeof(u8))*21)
#define EVENTDB_CALENDAREVENT_VCALALARM_NALARMMODE_SIZE								(sizeof(u8))
#define EVENTDB_CALENDAREVENT_PSUMMARY_SIZE											((sizeof(MAE_WChar))*51)
#define EVENTDB_CALENDAREVENT_PLOCATION_SIZE										((sizeof(MAE_WChar))*51)
#define EVENTDB_CALENDAREVENT_PDESCRIPTION_SIZE										((sizeof(MAE_WChar))*101)
#define EVENTDB_CALENDAREVENT_nCATEGORY_SIZE										(sizeof(u8))

#define EVENTDB_CALENDAREVENT_RECORD_SIZE		\
	(EVENTDB_CALENDAREVENT_NUID_SIZE+EVENTDB_CALENDAREVENT_NDTSTART_SIZE+EVENTDB_CALENDAREVENT_NDTEND_SIZE+\
	EVENTDB_CALENDAREVENT_VCALRRULE_NCOUNT_SIZE+EVENTDB_CALENDAREVENT_VCALRRULE_NINTERVAL_SIZE+\
	EVENTDB_CALENDAREVENT_VCALRRULE_VCALUTCDATE_BISUTC_SIZE+EVENTDB_CALENDAREVENT_VCALRRULE_VCALUTCDATE_TDTUTCDATE_SIZE+\
	EVENTDB_CALENDAREVENT_VCALRRULE_NMONTHINYEAR_SIZE+EVENTDB_CALENDAREVENT_VCALRRULE_NWEEKDAY_SIZE+\
	EVENTDB_CALENDAREVENT_VCALRRULE_NDAYINMONTH_SIZE+EVENTDB_CALENDAREVENT_VCALRRULE_PDAYINYEAR_SIZE+\
	EVENTDB_CALENDAREVENT_VCALRRULE_NDWSIZE_SIZE+EVENTDB_CALENDAREVENT_VCALRRULE_NFREQUENCY_SIZE+\
	EVENTDB_CALENDAREVENT_VCALALARM_NRUNTIME_SIZE+EVENTDB_CALENDAREVENT_VCALALARM_TDTSNOOZETIME_SIZE+\
	EVENTDB_CALENDAREVENT_VCALALARM_NREPEATCOUNT_SIZE+EVENTDB_CALENDAREVENT_VCALALARM_PSTR1_SIZE+\
	EVENTDB_CALENDAREVENT_VCALALARM_PSTR2_SIZE+EVENTDB_CALENDAREVENT_VCALALARM_NALARMMODE_SIZE+\
	EVENTDB_CALENDAREVENT_PSUMMARY_SIZE+EVENTDB_CALENDAREVENT_PLOCATION_SIZE+\
	EVENTDB_CALENDAREVENT_PDESCRIPTION_SIZE+EVENTDB_CALENDAREVENT_nCATEGORY_SIZE)

#define EVENTDB_CALENDAREVENT_COLUMN_NUM											23
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EVENTDB_EXCEPTION_EXCEPTIONUID_SIZE											(sizeof(u32))
#define EVENTDB_EXCEPTION_NUID_SIZE													(sizeof(u32))
#define EVENTDB_EXCEPTION_NDTSTART_SIZE												(sizeof(u32))
#define EVENTDB_EXCEPTION_NDTEND_SIZE												(sizeof(u32))

#define EVENTDB_EXCEPTION_RECORD_SIZE												(EVENTDB_EXCEPTION_EXCEPTIONUID_SIZE+EVENTDB_EXCEPTION_NUID_SIZE+EVENTDB_EXCEPTION_NDTSTART_SIZE+EVENTDB_EXCEPTION_NDTEND_SIZE)
#define EVENTDB_EXCEPTION_COLUMN_NUM												4
/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct VCALUTCDate_t_
{
	boolean bIsUTC;				/**< =1 UTC time else local time */
	MAE_DateTime_t tDtUTCDate;	/**< */
};

struct VCALAlarm_t_
{
	u32 nRunTime;					/**< RUN Time. */
	MAE_DateTime_t tDtSnoozeTime;	/**< Snooze Time.*/
	u32 nRepeatCount;				/**< Repeat Count. */
	u8* pStr1;						/**< For email name/display string/procedure name, MUST be NULL terminated. */ //Currently not useed.
	u8* pStr2;						/**< For display string, MUST be NULL terminated. */ //Currently not useed.
	u8 nAlarmMode;					/**< */
};

struct VCALRRule_t_
{
	u32 nCount;					/**< The number of times the repetition occurs. */
	u32 nInterval;				/**< Define how often the frequency repeats. 0 when not specified. */
	VCALUTCDate_t tEndDate;		/**< endDate.year, 0 when not specified. */
	u32 nMonthInYear;			/**< Month in the year, 0 when not specified. */
	u32 nWeekDay[10];			/**< The above defined Week In Month forms index into the array, and week
								     day can be set using Day In Week values. */
	s32 nDayInMonth[2];			/**< Pointer to an array containing Day in Month, NULL terminated. */
	u32* pDayInYear;			/**< Pointer to an array containing Day in Year, NULL terminated. */
	u32 nDwSize;					/**< Size of the structure, include size of pDayInMonth. */
	u8 nFrequency;				/**< The frequency of a repeat event. */

};

struct CalendarEvent_t_
{
	u32 nUID;					/**< unique id for this event */
	u32 nDTSTART;				/**< */
	u32 nDTEND;					/**< */
	VCALRRule_t* pRRULE;		/**< */
	VCALAlarm_t* pDALARM;		/**< */
	MAE_WChar* pSUMMARY;		/**< */
	MAE_WChar* pLOCATION;		/**< */
	MAE_WChar* pDESCRIPTION;	/**< */
	u8 nCATEGORY;			/**< */
};

opaque_enum(SortMode_e_)
{
    SORTBY_UID,
    SORTBY_DTSTART
};

struct VCALDateRange_t_
{
	u32 nStartDateTime;
	u32 nEndDateTime;
};

opaque_enum(MAE_EventDB_Notify_e_)
{
    MAE_EVENTDB_MASK_INSERTED = 0x01,
    MAE_EVENTDB_MASK_UPDATED = 0x02,
    MAE_EVENTDB_MASK_DELETED = 0x04,
    MAE_EVENTDB_MASK_ALL = (s32)0xFFFFFFFF
};

#endif /* __MMI_MAE_EVENTDB_TYPES_H__ */


