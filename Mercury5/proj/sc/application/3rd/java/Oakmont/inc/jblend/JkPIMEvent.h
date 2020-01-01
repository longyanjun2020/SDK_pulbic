/**
 * @file 
 */

/**
 * @addtogroup Module_PIM_Data_Types
 *
 * @{
 */

#ifndef ___JK_PIM_EVENT_H
#define ___JK_PIM_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif



/**
 *  @name Field ID of Event Interface.
 *  Field identifiers defined in the PIM optional package specification for fields
 *  in lists of type #JK_PIM_EVENT.
 *  See <code>javax.microedition.pim.Event</code> specification.
 *  
 *  This is used as a value for the <i>fieldId</i> member of JKPIMFieldDef structure. 
 */
/*@{*/ 

/**
 *  Field ID of <code>Event</code>: ALARM
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.ALARM</code>.
 *  The data type for this field is #JK_PIM_INT.
 */
#define JK_PIM_EVENT_ALARM			100

/**
 *  Field ID of <code>Event</code>: CLASS
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.CLASS</code>.
 *  The data type for this field is #JK_PIM_INT.
 */
#define JK_PIM_EVENT_CLASS			101

/**
 *  Field ID of <code>Event</code>: END
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.END</code>.
 *  The data type for this field is #JK_PIM_CALENDAR.
 */
#define JK_PIM_EVENT_END			102

/**
 *  Field ID of <code>Event</code>: LOCATION
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.LOCATION</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_EVENT_LOCATION		103

/**
 *  Field ID of <code>Event</code>: NOTE
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.NOTE</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_EVENT_NOTE			104

/**
 *  Field ID of <code>Event</code>: REVISION
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.REVISION</code>.
 *  The data type for this field is #JK_PIM_DATE.
 */
#define JK_PIM_EVENT_REVISION		105

/**
 *  Field ID of <code>Event</code>: START
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.START</code>.
 *  The data type for this field is #JK_PIM_CALENDAR.
 */
#define JK_PIM_EVENT_START			106

/**
 *  Field ID of <code>Event</code>: SUMMARY
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.SUMMARY</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_EVENT_SUMMARY		107

/**
 *  Field ID of <code>Event</code>: UID
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.UID</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_EVENT_UID			108

/*@}*/ 


/** 
 *  @name Values for the JK_PIM_EVENT_CLASS Field
 *  Values that can be set in a field whose field ID is JK_PIM_EVENT_CLASS.
 *  See <code>javax.microedition.pim.Event</code> specification.
 */
/*@{*/ 

/**
 *  A value for the JK_PIM_EVENT_CLASS field: CONFIDENTIAL
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.CLASS_CONFIDENTIAL</code>.
 */
#define JK_PIM_EVENT_CLASS_CONFIDENTIAL	200

/**
 *  A value for the JK_PIM_EVENT_CLASS field: PRIVATE
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.CLASS_PRIVATE</code>.
 */
#define JK_PIM_EVENT_CLASS_PRIVATE		201

/**
 *  A value for the JK_PIM_EVENT_CLASS field: PUBLIC
 *  
 *  Corresponds to <code>javax.microedition.pim.Event.CLASS_PUBLIC</code>.
 */
#define JK_PIM_EVENT_CLASS_PUBLIC		202

/*@}*/ 


/**
 *  @name Search Type.
 *  Identifiers defined in the PIM optional package specification as 
 *  search types for items in an event list. 
 *  See <code>javax.microedition.pim.EventList</code> specification.
 *  
 *  JBlend also uses this in a <i>searchType</i> passed to #JkPIMGetResultSetForEvent().
 */
/*@{*/ 

/**
 *  Search type: STARTING
 *  
 *  Corresponds to <code>javax.microedition.pim.EventList.STARTING</code>.
 */
#define JK_PIM_EVENT_SEARCH_TYPE_STARTING	0

/**
 *  Search type: ENDING
 *  
 *  Corresponds to <code>javax.microedition.pim.EventList.ENDING</code>.
 */
#define JK_PIM_EVENT_SEARCH_TYPE_ENDING		1

/**
 *  Search type: OCCURRING
 *  
 *  Corresponds to <code>javax.microedition.pim.EventList.OCCURRING</code>.
 */
#define JK_PIM_EVENT_SEARCH_TYPE_OCCURRING	2

/*@}*/ 



#ifdef __cplusplus
}
#endif

#endif /* ___JK_PIM_EVENT_H */

/** @} end of group */
