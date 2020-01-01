/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Functions for modifying date field properties.
 */

#ifndef ___GUI_INNER_DATEFIELD_H
#define ___GUI_INNER_DATEFIELD_H

#include <JkTypes.h>

#include <JkGraphics.h>
#include <JkVideoComponent.h>

#include <JgString.h>
#include <JgCom.h>
#include <JgDateField.h>
#include <JginKeyEvent.h>
#include <JginPointerEvent.h>
#include <JginCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_DateField
 * @{
 */

/**
 *   The color of the date field border.
 *   
 *   This is used for designating the attribute when date field default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginDateFieldSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_DFIELD_ATTR_BORDER_COLOR      (0x01)

/**
 *   The line type of the border indicating date field inner focus.
 *   
 *   This is used for designating the attribute when date field default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginDateFieldSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_DFIELD_ATTR_INNER_FOCUS_LINE     (0x02)

/**
 *   The color of the date field inner focus frame.
 *   
 *   This is used for designating the attribute when date field default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginDateFieldSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_DFIELD_ATTR_INNER_FOCUS_LINE_COLOR       (0x03)

/**
 *   The color of the foreground of the date field inner content when the content is in focus.
 *   
 *   This is used for designating the attribute when date field default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginDateFieldSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_DFIELD_ATTR_INNER_ACTIVE_FOREGROUND     (0x04)

/**
 *   The color of the background of the date field inner content when the content is in focus.
 *   
 *   This is used for designating the attribute when date field default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginDateFieldSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_DFIELD_ATTR_INNER_ACTIVE_BACKGROUND     (0x05)

/**
 * A date field was created.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *               JKUint32 Additional information about the created date field
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_DFIELD_EVT_CREATED                (JG_COM_EVT_END + 0x01)

/**
 * The date field is being deleted.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1 -
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * @return
 *        Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_DFIELD_EVT_DELETING               (JG_COM_EVT_END + 0x02)

/**
 *   The date field time changed.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 #JKSint32 The year setting (Western calendar). 
 *                 A value of 0 or less indicates a year B.C. (0: 1 B.C.; 
 *                 -1: 2 B.C.) 
 *   @param param2 #JKUint32 The current month-day-hour-minute, expressed 
 *                 in the format 0xMMDDHHMM.
 *   @param param3 #JKBool Designates whether the date and time settings are 
 *                 valid or not. Not valid means the date and time are not set. 
 *                 If #JK_FALSE is designated indicating the settings are 
 *                 invalid, ignore param1 and param2.
 *   @param param4 -
 *   @return Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_DFIELD_EVT_TIME_CHANGED      (JG_COM_EVT_END + 0x03)

/**
 *   The date field input mode changed.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 #JKUint32 The newly set input mode
 *   @param param2 #JKUint32 The previous input mode
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_DFIELD_EVT_INPUTMODE_CHANGED     (JG_COM_EVT_END + 0x04)

/**
 *   The focus item in the date field changed.
 *
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1  #JKUint32 The current focus item
 *   @param param2  #JKUint32 The previous focus item
 *   @param param3 -
 *   @param param4 -
 *   @return 
 *          Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_DFIELD_EVT_FOCUS_CHANGED       (JG_COM_EVT_END + 0x05)

/**
 *  The date field component title was changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 #JGString The date field component title
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_DFIELD_EVT_TITLE_TEXT_CHANGED    (JG_COM_EVT_END + 0x06)

/**
 * @internal
 * The maximum valid component event value for the date field.
 */
#define JG_DFIELD_EVT_END                    (JG_COM_EVT_END + 0x06)

/**
 *   Sets a date field element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all date field instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of a constant
 *   indicating GUI component attribute and a constant indicating GUI component state. 
 *   The constant indicating GUI component state may designate one state or a combination of states. 
 *   When a combination of states is designated, attributes for multiple states may be set at
 *   the same time. 
 *   Attribute values are passed in <i>value1</i> and <i>value2</i>.
 *   A list of the parameters passed to this function is given below. 
 *   
 *   <table>
 *     <tr> 
 *       <td><b><i>type</i></b>
 *       <td><b><i>value1</i></b>
 *       <td><b><i>value2</i></b>
 *     </tr>
 *     <tr> 
 *       <td>[Color of Border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_DFIELD_ATTR_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br>
 *                 #JG_COM_ATTR_STATE_ACTIVE
 *           </dl>
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Line type of the inner focus frame]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_DFIELD_ATTR_INNER_FOCUS_LINE
 *       <td>The line type. Designate one of the following: <br>
 *            #JG_COM_VAL_LINE_DOTTED<br>
 *            #JG_COM_VAL_LINE_SOLID<br>
 *            #JG_COM_VAL_LINE_NONE
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of inner focus frame]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_DFIELD_ATTR_INNER_FOCUS_LINE_COLOR
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND_SYNC
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the foreground of the date field inner content when the content is in focus]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_DFIELD_ATTR_INNER_ACTIVE_FOREGROUND
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the background of the date field inner content when the content is in focus]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_DFIELD_ATTR_INNER_ACTIVE_BACKGROUND
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *   </table>
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When <i>type</i> is an illegal value.</li>
 *    <li>When <i>value1</i> is an illegal value.</li>
 *    <li>When <i>value2</i> is an illegal value.</li>
 *   </ul>
 */
void JginDateFieldSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 *   Nullifies the date field date and time settings.
 *
 *   @param datefield The date field handle
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *   </ul>
 *   
 */
void JginDateFieldInvalidate(JGDateField datefield);

/**
 *   Sets date and time in the date field.
 *
 *   @param datefield The date field handle
 *   @param year   The year (Western calendar). Designate a value of 0 or less indicates a year B.C. (0: 1 B.C.; 
 *                 -1: 2 B.C.) 
 *   @param month  The month. Designate a value from  0 (January) to 11 (December).
 *   @param day    The day. Designate a value from 1 to 31.
 *   @param hour   The hour. Designate a value from 0 to 24.
 *   @param minute The minute. Designate a value from 0 to 59.
 *   
 *   If this function completes normally, the date field goes from not set to 
 *   set state.
 *   
 *   To conform to the MIDP specification, the date initial value when the input mode is 
 *   #JG_DFIELD_INPUTMODE_TIME must be 1970/1/1.
 *   See the MIDP specification for details.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>When a value not in the range of 0 to 11 is designated in the month parameter.
 *    <li>When the value designated in the day parameter does not exist on the calendar.
 *    <li>When a value not in the range of 0 to 23 is designated in the hour parameter.
 *    <li>When a value not in the range of 0 to 59 is designated in the minute parameter.
 *   </ul>
 *   
 */
void JginDateFieldSetTimeR2(JGDateField datefield, JKSint32 year, JKSint month, JKSint day,
                            JKSint hour, JKSint minute);


/**
 *   Sets whether the date field is being edited or not.
 *
 *   @param datefield The date field handle
 *   @param editing Designate #JK_TRUE to set the date field to editing state, else #JK_FALSE.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>When a value other than #JK_TRUE or #JK_FALSE is designated in editing.</li>
 *   </ul>
 */
void JginDateFieldSetEditing(JGDateField datefield, JKBool editing);

/**
 *   Sets input focus on an item in the date field. 
 *
 *   @param datefield The date field handle
 *   @param part The item to be focused. Designate one of the following values.
 * <br><br>
 * <ul>
 *  <li> #JG_DFIELD_INPUTMODE_DATE
 *  <li> #JG_DFIELD_INPUTMODE_TIME
 * </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the datefield parameter is an illegal handle.</li>
 *    <li>
 *   </ul>
 * 
 * @see JG_DFIELD_INPUTMODE_DATE
 * @see JG_DFIELD_INPUTMODE_TIME
 */
void JginDateFieldSetFocusedPart(JGDateField datefield, JKUint32 part);

/**
 * Draws the inner content of a date field.
 *
 * @param datefield  The date field handle.
 * @param g          The graphics context handle.
 * @param dx         The x-direction offset of inner content drawing position.
 * @param dy         The y-direction offset of inner content drawing position.
 * @param foreground The foreground color.
 *
 * This function draws the inner content of the date field using the graphics
 * context designated in the g parameter.
 * This function usees a clip region which is the intersection of the graphics 
 * context clip region and the inner content.
 * The drawing position of the inner content is determined based on the 
 * date field coordinates and the inset values.
 *   
 * The inner content drawing position can be adjusted by setting non-zero values 
 * to the dx and dy parameters.
 *   
 * When calling this function, set the same clip region to the graphics 
 * context as the clip region which has been set for the graphics context 
 * when a #JG_COM_EVT_PAINT event was notified.
 * 
 * @see JginComSetInsets()
 * @see JgComGetInsetTop()
 * @see JgComGetInsetLeft()
 * @see JgComGetInsetRight()
 * @see JgComGetInsetBottom()
 */
void JginDateFieldPaintContent(JGDateField datefield, JKGraphicsContext g,
                               JKSint32 dx, JKSint32 dy, JKColor foreground);

/**
 * Sets a date field component event handler.
 * 
 * @param type
 *        The applicable event
 * @param handler
 *        The component event handler set for the event
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When type is an illegal value.</li>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginDateFieldSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 * The date field default component event handler
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event 
 *        information
 * @return
 *        The processing result is returned.
 * 
 * The date field default component event handler performs the following event 
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 *  <dt> #JG_DFIELD_EVT_CREATED, #JG_DFIELD_EVT_DELETING</dt>
 *  <dd>No operation</dd>
 *  
 *  <dt> #JG_DFIELD_EVT_TIME_CHANGED</dt>
 *  <dd>Calls #JgurDateFieldGetString() to get the string to be drawn, and if   
 *      the date field display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.
 *  </dd>
 *  
 *  <dt> #JG_DFIELD_EVT_INPUTMODE_CHANGED </dt>
 *  <dd> Changes the preferred size and minimum size of the date field. 
 *       If the date field display state is Shown, it then notifies
 *       the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_DFIELD_EVT_FOCUS_CHANGED </dt>
 *  <dd>If the date field display state is Shown, notifies the GUI event 
 *       #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_STATE_CHANGED</dt>
 *  <dd>If the date field newly obtained focus (went to Focused state from a state 
 *      other than Active), sets the date field state to Active state.<br>
 *      If the date field state changed from Active to another state, and if the 
 *      date field is being edited, terminates the date input module by calling 
 *      #JgurDateFieldCancelDateModule(), and then notifies the GUI events 
 *      #JG_GUI_EVT_RELEASE_INPUT_EVENT and #JG_GUI_EVT_RELEASE_SCREEN to 
 *      JBlend. 
 *      This releases occupation of user input event, screen occupation, and editing state 
 *      of the date field.
 *      Finally, it notifies the GUI event #JG_GUI_EVT_REPAINT_SCREEN to JBlend for 
 *      repainting.
 *     </dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *  <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT</dt>
 *  <dd>Draws a date field.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT, #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH</dt>
 *  <dd>Return the preferred size (width, height) set in the date field as the return value.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *  <dd>Returns the preferred size of the date field default design.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *  <dd>Returns the minimum size of the date field default design.</dd>
 *   
 *  <dt> #JG_COM_EVT_RELAYOUTING </dt>
 *  <dd>Updates the following settings based on the current dominant language direction
 *      <table>
 *        <tr>
 *          <td>Property</td>
 *          <td>LTR</td>
 *          <td>RTL</td>
 *        </tr>
 *        <tr>
 *          <td>Horizontal cutoff position</td>
 *          <td> #JG_COM_CUT_POLICY_X_RIGHT </td>
 *          <td> #JG_COM_CUT_POLICY_X_LEFT </td>
 *        </tr>
 *      </table>
 *  </dd>
 *  
 *  <dt>Other events</dt>
 *  <dd>If the date field drawing content changed and the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in the component member of JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginDateFieldDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 * Sets the date field key event handler.
 * 
 * @param handler
 *        The key event handler to be set
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginDateFieldSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 * The date field default key event handler.
 * 
 * @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated 
 *        event information
 * @return
 *        The processing result is returned.
 * 
 * The date field default key event handler performs the following event
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 * <dt> #AM_KEYCODE_SELECT</dt>
 * <dd>
 *     <dl>
 *     <dt> #AM_EVENT_KEY_CLICKED</dt>
 *     <dd>Sets the date field state to editing, and notifies the GUI events 
 *         #JG_GUI_EVT_OCCUPY_INPUT_EVENT and #JG_GUI_EVT_OCCUPY_SCREEN, 
 *         occupying user input events and the screen.<br>
 *         If the date field is in editing state when the response handler associated 
 *         with #JG_GUI_EVT_OCCUPY_SCREEN is called from JBlend, it calls 
 *         #JgurDateFieldLaunchDateModule().
 *      </dd>
 *     </dl>
 * </dd>
 * <dt> #AM_KEYCODE_UP, #AM_KEYCODE_DOWN</dt>
 * <dd>
 *     <dl>
 *     <dt> #AM_EVENT_KEY_CLICKED , #AM_EVENT_KEY_REPEATED </dt>
 *     <dd>If focus can be moved in the direction of the pressed key, moves focus 
 *         and scrolls the item display as necessary. 
 *         Returns  #JG_KEY_RES_KEEP_FOCUS as the return value.
 *         If focus cannot be moved in the direction of the pressed key, returns 0 
 *         as the return value. </dd>
 *     </dl>
 * </dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in the component member of JGT_KeyEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginDateFieldDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the date field pointing device event handler.
 * 
 * @param handler
 *        The pointing device event handler to be set
 * 
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 */
void JginDateFieldSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 * The date field default pointing device event handler.
 * 
 * @param pointerEvent
 *        A pointer to the JGT_PointerEvent structure holding the generated 
 *        event information
 * @return
 *        The processing result is returned.
 * 
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 *    
 *   The date field default pointing event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *     <dt> #AM_EVENT_POINTER_PRESSED </dt>
 *     <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *         <dl>
 *           <dt>If the date field state is #JG_COM_STATE_ACTIVE, </dt>
 *           <dd>moves the inner focus.</dd>
 *         </dl>
 *       </dd>
 *     <dt> #AM_EVENT_POINTER_CLICKED </dt>
 *     <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *         <dl>
 *           <dt>If the date field state is #JG_COM_STATE_ACTIVE, </dt>
 *           <dd>goes to an editing screen for the field that has inner focus.</dd>
 *         </dl>
 *     </dd>
 *   </dl>
 */
JKUint32 JginDateFieldDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_DATEFIELD_H */

