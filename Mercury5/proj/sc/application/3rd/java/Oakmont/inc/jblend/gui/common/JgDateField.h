/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Functions for modifying date field properties.
 */

#ifndef ___GUI_COMMON_DATEFIELD_H
#define ___GUI_COMMON_DATEFIELD_H

#include <JkTypes.h>

#include <JgGUIEvent.h>
#include <JgString.h>
#include <JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_DateField
 * @{
 */

/**
 *   The date field time changed.
 *
 *   When the date field time was changed by a user operation, notify the event using  
 *   #JginGUIEventPostEvent().
 *   The values of the param members in the #JGT_GUIEvent structure passed as an 
 *   argument of JginGUIEventPostEvent() are as indicated in the following parameters. 
 * 
 *   @param param1 #JKSint32 Designate the current year (Western calendar). 
 *                 A value of 0 or less indicates a year B.C. (0: 1 B.C.; -1: 2 B.C.) 
 *   @param param2 #JKUint32 Designate the current month-day-hour-minute in the format 
 *                           0xMMDDHHMM.
 *   @param param3 #JKBool  Designate whether the date and time settings are 
 *                 valid or not. Not valid means the date and time are not set. 
 *                 If #JK_FALSE is designated indicating the settings are 
 *                 invalid, param1 and param2 are ignored.
 *   @param param4 -
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_DFIELD_EVT_TIME_CHANGED      (JG_GUI_EVT_END + 0x01)

/**
 * @internal
 * The maximum value of GUI date field events
 */
#define JG_GUI_DFIELD_EVT_END              (JG_GUI_EVT_END + 0x01)

/**
 * The date field component type
 * 
 * @see JgComGetComponentType
 */
#define JG_DATEFIELD   10

/**
 * The date field handle
 * 
 * A date field handle is data identifying the date field.<br>
 * The date field handle can be used as a component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGDateField;

/**
 *  The date field input mode: Date
 */
#define JG_DFIELD_INPUTMODE_DATE        1

/**
 *  The date field input mode: Time
 */
#define JG_DFIELD_INPUTMODE_TIME        2

/**
 *  The date field input mode: Date and time
 */
#define JG_DFIELD_INPUTMODE_DATETIME    3

/**
 *   Gets whether the date and time are set in the date field.
 *   
 *   @param datefield The date field handle
 *   @return #JK_TRUE is returned if they are set, or #JK_FALSE if not.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *   </ul>
 */
JKBool JgDateFieldIsValid(JGDateField datefield);

/**
 *   Gets the year set in the date field.
 *   
 *   @param datefield The date field handle
 *   @return The year (Western calendar) set in the date field is returned, as a 
 *           value of 0 or less indicates a year B.C. (0: 1 B.C.; -1: 2 B.C.)
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>When the date and time are not set.</li>
 *   </ul>
 */
JKSint32 JgDateFieldGetYear(JGDateField datefield);

/**
 *   Gets the month set in the date field.
 *   
 *   @param datefield The date field handle
 *   @return The month set in the date field is returned, as a value from 0 (January) 
 *           to 11 (December).
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>When the date and time are not set.</li>
 *   </ul>
 */
JKSint8 JgDateFieldGetMonth(JGDateField datefield);

/**
 *   Gets the day of the month set in the date field.
 *   
 *   @param datefield The date field handle
 *   @return The day set in the date field is returned, as a value from 1 to 31.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>When the date and time are not set.</li>
 *   </ul>
 */
JKSint8 JgDateFieldGetDay(JGDateField datefield);

/**
 *   Gets the hour set in the date field.
 *   
 *   @param datefield The date field handle
 *   @return The hour set in the date field is returned, as a value from 0 to 23.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>When the date and time are not set.</li>
 *   </ul>
 */
JKSint8 JgDateFieldGetHour(JGDateField datefield);

/**
 *   Gets the minute set in the date field.
 *   
 *   @param datefield The date field handle
 *   @return The minute set in the date field is returned, as a value from 0 to 59.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>When the date and time are not set.</li>
 *   </ul>
 */
JKSint8 JgDateFieldGetMinute(JGDateField datefield);

/**
 *   Gets the date field input mode.
 * 
 *   @param datefield
 *        The date field handle
 *   @return 
 *        The date field input mode is returned as one of the following values.
 * <ul>
 *  <li> #JG_DFIELD_INPUTMODE_DATE
 *  <li> #JG_DFIELD_INPUTMODE_TIME
 *  <li> #JG_DFIELD_INPUTMODE_DATETIME
 * </ul>
 * 
 * <p>
 * In the following case @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 * </ul>
 */
JKUint32 JgDateFieldGetInputMode(JGDateField datefield);

/**
 *   Gets whether the date field is being edited or not.
 *   
 *   @param datefield The date field handle
 *   @return #JK_TRUE is returned if the date field is in editing state, else #JK_FALSE.
 *
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *   </ul>
 */
JKBool JgDateFieldIsEditing(JGDateField datefield);

/**
 *   Gets the focused item in the date field.
 *
 *   @param datefield The date field handle
 *   @return The date field focused item is returned as one of the following values.
 * <ul>
 *  <li> #JG_DFIELD_INPUTMODE_DATE
 *  <li> #JG_DFIELD_INPUTMODE_TIME
 * </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *   </ul>
 * @see JG_DFIELD_INPUTMODE_DATE
 * @see JG_DFIELD_INPUTMODE_TIME
 */
JKUint32 JgDateFieldGetFocusedPart(JGDateField datefield);

/**
 *  Gets the title string of the date field component.
 *
 *  @param datefield The date field component handle
 *  @return The title string is returned, or #JK_INVALID_HANDLE if none was set.
 *
 *  This function returns the title string of the date field component.
 *
 *  The string this function returns corresponds to 
 *  the label of javax.microedition.lcdui.DateField class.
 *
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When datefield is an illegal handle.</li>
 *  </ul>
 */
JGString JgDateFieldGetTitleText(JGDateField datefield);

/**
 *  Gets the character string indicating the date (year-month-day, day 
 *  of the week) or time (hour-minute) set in the date field.
 *
 *   @param datefield The date field component handle
 *   @param part      The type of string to be acquired.
 *                    One of the following values is designated.
 *                    <ul>
 *                     <li>#JG_DFIELD_INPUTMODE_DATE
 *                     <li>#JG_DFIELD_INPUTMODE_TIME
 *                    </ul>
 *   @return The character string indicating the date or time
 *           set in the date field
 *
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When datefield is an illegal handle.</li>
 *   <li>When part is not ether
 *       #JG_DFIELD_INPUTMODE_DATE or #JG_DFIELD_INPUTMODE_TIME.</li>
 *  </ul>
 */
JGString JgDateFieldGetString(JGDateField datefield, JKUint32 part);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_DATEFIELD_H */

