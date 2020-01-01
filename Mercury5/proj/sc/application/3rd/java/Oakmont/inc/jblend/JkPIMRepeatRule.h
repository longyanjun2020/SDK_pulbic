/**
 * @file 
 */

/**
 * @addtogroup Module_PIM_Data_Types
 *
 * @{
 */

#ifndef ___JK_PIM_REPEATRULE_H
#define ___JK_PIM_REPEATRULE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "JkTypes.h"
#include "JkPIMCommon.h"


/**
 */

/**
 */

/** 
 *  @name Field ID of RepeatRule Class.
 *  Field identifiers defined in the PIM optional package specification as a field
 *  of repeat rule.
 *  See <code>javax.microedition.pim.RepeatRule</code> specification.
 */
/*@{*/ 

/**
 *  Field ID of RepeatRule: FREQUENCY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FREQUENCY</code>.
 */
#define JK_PIM_REPEAT_FREQUENCY			0x00000000

/**
 *  Field ID of RepeatRule: DAY_IN_MONTH
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.DAY_IN_MONTH</code>.
 */
#define JK_PIM_REPEAT_DAY_IN_MONTH		0x00000001

/**
 *  Field ID of RepeatRule: DAY_IN_WEEK
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.DAY_IN_WEEK</code>.
 */
#define JK_PIM_REPEAT_DAY_IN_WEEK		0x00000002

/**
 *  Field ID of RepeatRule: DAY_IN_YEAR
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.DAY_IN_YEAR</code>.
 */
#define JK_PIM_REPEAT_DAY_IN_YEAR		0x00000004

/**
 *  Field ID of RepeatRule: MONTH_IN_YEAR
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.MONTH_IN_YEAR</code>.
 */
#define JK_PIM_REPEAT_MONTH_IN_YEAR		0x00000008

/**
 *  Field ID of RepeatRule: WEEK_IN_MONTH
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.WEEK_IN_MONTH</code>.
 */
#define JK_PIM_REPEAT_WEEK_IN_MONTH		0x00000010

/**
 *  Field ID of RepeatRule: COUNT
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.COUNT</code>.
 */
#define JK_PIM_REPEAT_COUNT				0x00000020

/**
 *  Field ID of RepeatRule: END
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.END</code>.
 */
#define JK_PIM_REPEAT_END				0x00000040

/**
 *  Field ID of RepeatRule: INTERVAL
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.INTERVAL</code>.
 */
#define JK_PIM_REPEAT_INTERVAL			0x00000080

/*@}*/ 

 
/** 
 *  @name Frequency
 *  Values that can be set in a field whose field ID is #JK_PIM_REPEAT_FREQUENCY.
 *  See <code>javax.microedition.pim.RepeatRule</code> specification.
 */
/*@{*/ 

/**
 *  Frequency: DAILY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.DAILY</code>.
 */
#define JK_PIM_REPEAT_DAILY		16

/**
 *  Frequency: WEEKLY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.WEEKLY</code>.
 */
#define JK_PIM_REPEAT_WEEKLY	17

/**
 *  Frequency: MONTHLY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.MONTHLY</code>.
 */
#define JK_PIM_REPEAT_MONTHLY	18

/**
 *  Frequency: YEARLY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.YEARLY</code>.
 */
#define JK_PIM_REPEAT_YEARLY	19

/*@}*/ 


/** 
 *  @name Day of the Week
 *  
 *  Values that can be set in a field whose field ID is #JK_PIM_REPEAT_DAY_IN_WEEK.
 *  See <code>javax.microedition.pim.RepeatRule</code> specification.
 */
/*@{*/ 

/**
 *  Day of the Week: SATURDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.SATURDAY</code>.
 */
#define JK_PIM_REPEAT_SATURDAY		0x000400

/**
 *  Day of the Week: FRIDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FRIDAY</code>.
 */
#define JK_PIM_REPEAT_FRIDAY		0x000800

/**
 *  Day of the Week: THURSDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.THURSDAY</code>.
 */
#define JK_PIM_REPEAT_THURSDAY		0x001000

/**
 *  Day of the Week: WEDNESDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.WEDNESDAY</code>.
 */
#define JK_PIM_REPEAT_WEDNESDAY		0x002000

/**
 *  Day of the Week: TUESDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.TUESDAY</code>.
 */
#define JK_PIM_REPEAT_TUESDAY		0x004000

/**
 *  Day of the Week: MONDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.MONDAY</code>.
 */
#define JK_PIM_REPEAT_MONDAY		0x008000

/**
 *  Day of the Week: SUNDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.SUNDAY</code>.
 */
#define JK_PIM_REPEAT_SUNDAY		0x010000

/*@}*/ 


/** 
 *  @name Week
 *  
 *  Value that can be set in a field whose field ID is #JK_PIM_REPEAT_WEEK_IN_MONTH.
 *  See <code>javax.microedition.pim.RepeatRule</code> specification.
 */
/*@{*/ 

/**
 *  Week: FIRST
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FIRST</code>.
 */
#define JK_PIM_REPEAT_FIRST			0x0001

/**
 *  Week: SECOND
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.SECOND</code>.
 */
#define JK_PIM_REPEAT_SECOND		0x0002

/**
 *  Week: THIRD
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.THIRD</code>.
 */
#define JK_PIM_REPEAT_THIRD			0x0004

/**
 *  Week: FOURTH
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FOURTH</code>.
 */
#define JK_PIM_REPEAT_FOURTH		0x0008

/**
 *  Week: FIFTH
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FIFTH</code>.
 */
#define JK_PIM_REPEAT_FIFTH			0x0010

/**
 *  Week: LAST
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.LAST</code>.
 */
#define JK_PIM_REPEAT_LAST			0x0020

/**
 *  Week: SECONDLAST
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.SECONDLAST</code>.
 */
#define JK_PIM_REPEAT_SECONDLAST	0x0040

/**
 *  Week: THIRDLAST
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.THIRDLAST</code>.
 */
#define JK_PIM_REPEAT_THIRDLAST		0x0080

/**
 *  Week: FOURTHLAST
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FOURTHLAST</code>.
 */
#define JK_PIM_REPEAT_FOURTHLAST	0x0100

/**
 *  Week: FIFTHLAST
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FIFTHLAST</code>.
 */
#define JK_PIM_REPEAT_FIFTHLAST		0x0200

/*@}*/ 


/** 
 *  @name Month
 *  
 *  Values that can be set in a field whose field ID is #JK_PIM_REPEAT_MONTH_IN_YEAR.
 *  See <code>javax.microedition.pim.RepeatRule</code> specification.
 */
/*@{*/ 

/**
 *  Month: JANUARY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.JANUARY</code>.
 */
#define JK_PIM_REPEAT_JANUARY		0x00020000

/**
 *  Month: FEBRUARY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.FEBRUARY</code>.
 */
#define JK_PIM_REPEAT_FEBRUARY		0x00040000

/**
 *  Month: MARCH
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.MARCH</code>.
 */
#define JK_PIM_REPEAT_MARCH			0x00080000

/**
 *  Month: APRIL
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.APRIL</code>.
 */
#define JK_PIM_REPEAT_APRIL			0x00100000

/**
 *  Month: MAY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.MAY</code>.
 */
#define JK_PIM_REPEAT_MAY			0x00200000

/**
 *  Month: JUNE
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.JUNE</code>.
 */
#define JK_PIM_REPEAT_JUNE			0x00400000

/**
 *  Month: JULY
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.JULY</code>.
 */
#define JK_PIM_REPEAT_JULY			0x00800000

/**
 *  Month: AUGUST
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.AUGUST</code>.
 */
#define JK_PIM_REPEAT_AUGUST		0x01000000

/**
 *  Month: SEPTEMBER
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.SEPTEMBER</code>.
 */
#define JK_PIM_REPEAT_SEPTEMBER		0x02000000

/**
 *  Month: OCTOBER
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.OCTOBER</code>.
 */
#define JK_PIM_REPEAT_OCTOBER		0x04000000

/**
 *  Month: NOVEMBER
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.NOVEMBER</code>.
 */
#define JK_PIM_REPEAT_NOVEMBER		0x08000000

/**
 *  Month: DECEMBER
 *  
 *  Corresponds to <code>javax.microedition.pim.RepeatRule.DECEMBER</code>.
 */
#define JK_PIM_REPEAT_DECEMBER		0x10000000

/*@}*/ 


/**
 *  The data structure type representing a repeat rule.
 */
typedef struct {
    /**
     *   The number of iterations.
     */
	JKSint32			count;
	
    /**
     *   The value of JK_PIM_REPEAT_DAY_IN_MONTH field.
     */
	JKSint32			dayInMonth;
	
    /**
     *   The value of JK_PIM_REPEAT_DAY_IN_WEEK field.
     */
	JKSint32			dayInWeek;
	
    /**
     *   The value of JK_PIM_REPEAT_DAY_IN_YEAR field.
     */
	JKSint32			dayInYear;
	
    /**
     *   The value of JK_PIM_REPEAT_FREQUENCY field.
     */
	JKSint32			frequency;
	
    /**
     *   The value of JK_PIM_REPEAT_INTERVAL field.
     */
	JKSint32			interval;
	
    /**
     *   The value of JK_PIM_REPEAT_MONTH_IN_YEAR field.
     */
	JKSint32			monthInYear;
	
    /**
     *   The value of JK_PIM_REPEAT_WEEK_IN_MONTH field.
     */
	JKSint32			weekInMonth;
	
    /**
     *   The value of JK_PIM_REPEAT_END field.
     */
	JKPIMCalendar		end;
	
    /**
     *   An array of dates to be excluded from the rule.
     */
	JKPIMCalendarArray	exceptDates;
	
    /**
     *   Indicates whether or not each structure member holds a value. 
     *   
     *   Bit states indicate for each structure member whether or not the member
     *   holds a value. Bit mask values are defined for each member. A member is
     *   filled if the result of an "AND" operation with its mask value is 1.
     */
	JKSint32			filled;
} JKPIMRepeatRule;

 
/** 
 *  @name Value of Bit Mask
 *  
 *  Bit mask values held for each member by the <i>filled</i> member of the JKPIMRepeatRule structure.
 *  
 *  The native system does not use these constants.
 */
/*@{*/ 

/**
 *  The mask value for the <i>count</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_COUNT_MASK			0x0001

/**
 *  The mask value for the <i>dayInMonth</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_DAY_IN_MONTH_MASK		0x0002

/**
 *  The mask value for the <i>dayInWeek</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_DAY_IN_WEEK_MASK		0x0004

/**
 *  The mask value for the <i>dayInYear</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_DAY_IN_YEAR_MASK		0x0008

/**
 *  The mask value for the <i>frequency</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_FREQUENCY_MASK		0x0010

/**
 *  The mask value for the <i>interval</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_INTERVAL_MASK			0x0020

/**
 *  The mask value for the <i>monthInYear</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_MONTH_IN_YEAR_MASK	0x0040

/**
 *  The mask value for the <i>weekInMonth</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_WEEK_IN_MONTH_MASK	0x0080

/**
 *  The mask value for the <i>end</i> member of the JKPIMRepeatRule structure
 */
#define JK_PIM_REPEAT_END_MASK				0x0100

/*@}*/ 


/**
 *  The data structure type representing an event item data.
 *  
 *  A structure type extending the JKPIMItem structure to enable storing of repeat rules. 
 *  Note carefully that the first member is a JKPIMItem structure.
 */
typedef struct {
    /**
     *   The item data.
     */
	JKPIMItem			item;

    /**
     *   A pointer to the JKPIMRepeatRule structure.
     */
	JKPIMRepeatRule*	repeat;
} JKPIMEventItem;


/*	---------- ---------- ----------
	 @: Frequency definition
	---------- ---------- ---------- */

/**
 *  The data structure type for representing frequency definitions.
 *  
 *  This structure indicates the available combinations of fields corresponding to <code>RepeatRule</code> class <code>FREQUENCY</code> fields.
 *  The array elements set in each field hold bit-wise OR values representing field combinations.
 */
typedef struct {
    /**
     *   A yearly event.
     */
	JKPIMIntArray	yearly;

    /**
     *   A monthly event.
     */
	JKPIMIntArray	monthly;

    /**
     *   A weekly event.
     */
	JKPIMIntArray	weekly;

    /**
     *   A daily event.
     */
	JKPIMIntArray	daily;
} JKPIMFrequencyDef;



#ifdef __cplusplus
}
#endif

#endif /* ___JK_PIM_REPEATRULE_H */

/** @} end of group */
