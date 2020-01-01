/**
 * \file    mmi_mae_clock_types.h
 * \brief   
 *
 * @version
 */

#ifndef __MMI_MAE_CLOCK_TYPES_H__
#define __MMI_MAE_CLOCK_TYPES_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_clstbl.h"
#include "sys_time.h"

#define MAE_CLOCK_UPPERLIMIT_YEAR 2039

/* enum for MAEClkItemId_t */
enum MAEClkItemId_t_
{
    MAECLOCK_ID_MINUTETICK = (CLSID_CLOCK << 16 | 0),
    MAECLOCK_ID_DATETICK,
    MAECLOCK_ID_SYSTIMECHANGE,
    MAECLOCK_ID_SYSTIMEZONECHANGE,
    MAECLOCK_ID_SECONDTIMEZONECHANGE,
    MAECLOCK_ID_SECONDTICK,
    //========== Add ID before this line ===========//
    MAECLOCK_ID_SUM
};

enum MAE_TimeZone_Field_e_
{
    MAE_PRIMARY_TIMEZONE = 0,   // Primary timezone stored in config item
    MAE_SECONDARY_TIMEZONE,     // Secondary timezone stored in config item
};

//Do not change order and data type
//Mapping with mmi_setting_cfg.h SetPhoneTimeFormat_e
enum MAE_TimeFormat_e_
{
    MAE_TIMEFORMAT_12FORMAT = 0	,
    MAE_TIMEFORMAT_24FORMAT
};

struct ClockListener_t_
{
	PfnClkListener  pClkListener;  ///< a call back function with PfnClkListener prototype
	void            *pUsrData;       ///< a context data pointer to pass into callback function
	u32             nMask;            ///< the mask of the interested items
	ICLOCK          *pIClock;        ///< a IClock pointer to indicate which IClock this listener belongs to
	ClockListener_t *pNext;          ///< next listener structure
};

struct TimeZoneRule_t_
{
	MAE_TimeZone_e nMaeTzid; /* MAE timezone id */
	s32	nOffset; /* offset in minutes */
	boolean bUseDaylight;
	s32 nDstSavings;	/* A value indicating the amount of time saved during DST in minutes. Typically one hour; sometimes 30 minutes. */
	u8 nDsStartMonth;			//DST start month, value range is 1~12
	u8 nDsStartWeekDayNumber;	//DST start weekday number Value range is 1~5. 5 means the last one. 
	//4 means to get one before the last, if there is only 4 Sunday in the month, 4 and 3 will get the same Sunday.
	//If inputting number is bigger than 5, result will be the last and if less than 1, result will be the first.
	u8 nDsStartWeekDay;			//DST start weekday [1 = Monday, 7 = Sunday]

	u8 nDsEndMonth;				//DST end month, value range is 1~12
	u8 nDsEndWeekDayNumber;		//DST end weekday number Value range is 1~5. 5 means the last one. 
	//4 means to get one before the last, if there is only 4 Sunday in the month, 4 and 3 will get the same Sunday.
	//If inputting number is bigger than 5, result will be the last and if less than 1, result will be the first.
	u8 nDsEndWeekDay;			//DST end weekday [1 = Monday, 7 = Sunday]
};

struct _ClockBase_t_
{
	MAE_TimeZone_e   nPrimaryTimeZone;  /* Handset system time zone */
	MAE_TimeZone_e   nSecondaryTimeZone;/* Time zone for remote time */
    boolean          bDayLightSaving;   /* True if daylight saving is enabled */
};

#endif /* __MMI_MAE_CLOCK_TYPES_H__ */

