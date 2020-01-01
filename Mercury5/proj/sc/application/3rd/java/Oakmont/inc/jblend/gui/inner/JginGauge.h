/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Functions for modifying gauge properties.
 */

#ifndef ___GUI_INNER_GAUGE_H
#define ___GUI_INNER_GAUGE_H

#include <JkTypes.h>

#include <JkGraphics.h>
#include <JkVideoComponent.h>

#include <gui/common/JgString.h>
#include <gui/common/JgCom.h>
#include <gui/common/JgGauge.h>
#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Gauge
 * @{
 */

/**
 *   The color of the gauge outside border.
 *   
 *   This is used for designating the attribute when gauge default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginGaugeSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The gauge border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot outermost rectangle of the border.
 */
#define JG_GAUGE_ATTR_OUTER_BORDER_COLOR      (0x01)

/**
 *   The color of the gauge inside border.
 *   
 *   This is used for designating the attribute when gauge default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginGaugeSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The gauge border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot innermost rectangle of the border.
 */
#define JG_GAUGE_ATTR_INNER_BORDER_COLOR      (0x02)

/**
 *   The color of the gauge "foreground" element.
 *   
 *   This is used for designating the attribute when gauge default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginGaugeSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_GAUGE_ATTR_FOREGROUND     (0x03)

/**
 *   The color of the gauge "background" element.
 *   
 *   This is used for designating the attribute when gauge default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginGaugeSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_GAUGE_ATTR_BACKGROUND     (0x04)

/**
 * A gauge was created.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1 
 *               JKUint32 Additional information about the gauge creation.
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_CREATED                (JG_COM_EVT_END + 0x01)

/**
 * A gauge is being deleted.
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
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_DELETING               (JG_COM_EVT_END + 0x02)

/**
 *   The gauge mode changed.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 JKUint32 The newly set mode
 *   @param param2 JKUint32 The previous mode
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_MODE_CHANGED           (JG_COM_EVT_END + 0x03)

/**
 * The gauge value changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *               JKSint32 The current value.
 * @param param2
 *               JKSint32 The previous value.
 * @param param3 -
 * @param param4 -
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_VALUE_CHANGED          (JG_COM_EVT_END + 0x04)

/**
 * The gauge maximum value was changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *               JKSint32 The current maximum setting.
 * @param param2
 *               JKSint32 The previous setting.
 * @param param3 -
 * @param param4 -
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_MAX_VALUE_CHANGED      (JG_COM_EVT_END + 0x05)

/**
 *   Gauge value incrementation was requested
 *
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1
 *                 JKUint32 The current type of the gauge.
 *   @param param2
 *                 JKUint32 The previous type of the gauge.
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 *   The type of the gauge is either #JG_GAUGE_INDEFINITE_TYPE_CONTINUOUS or
 *   #JG_GAUGE_INDEFINITE_TYPE_INCREMENTAL.
 *   This event occurs only when the gauge mode is #JG_GAUGE_MODE_INDEFINITE.
 * 
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_REQUEST_INCREMENT      (JG_COM_EVT_END + 0x06)

/**
 *   Gauge value decrementation was requested
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1
 *                 JKUint32 The current type of the gauge.
 *   @param param2
 *                 JKUint32 The previous type of the gauge.
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 *   The type of the gauge is either #JG_GAUGE_INDEFINITE_TYPE_CONTINUOUS or
 *   #JG_GAUGE_INDEFINITE_TYPE_INCREMENTAL.
 *   This event occurs only when the gauge mode is #JG_GAUGE_MODE_INDEFINITE.
 *
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_REQUEST_DECREMENT      (JG_COM_EVT_END + 0x07)

/**
 *   Gauge mode transition to idle state was requested.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1
 *                 JKUint32 The current type of the gauge.
 *   @param param2
 *                 JKUint32 The previous type of the gauge.
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 *   The type of the gauge is either #JG_GAUGE_INDEFINITE_TYPE_CONTINUOUS or
 *   #JG_GAUGE_INDEFINITE_TYPE_INCREMENTAL.
 *   This event occurs only when the gauge mode is #JG_GAUGE_MODE_INDEFINITE.
 *
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_GAUGE_EVT_REQUEST_IDLE           (JG_COM_EVT_END + 0x08)

/**
 * @internal
 * The maximum valid component event value for the gauge.
 */
#define JG_GAUGE_EVT_END                    (JG_COM_EVT_END + 0x08)

/**
 *   Sets a gauge element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all gauge instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of a constant
 *   indicating GUI component attributes and a constant indicating GUI component state. 
 *   The constant indicating GUI component state may designate one state or a combination of states. 
 *   When a combination of states is designated, attributes for multiple states may be set at the
 *   same time.
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
 *       <td>[Color of the outside border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_GAUGE_ATTR_OUTER_BORDER_COLOR 
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_DISABLED<br>
 *                 #JG_COM_ATTR_STATE_ENABLED<br>
 *                 #JG_COM_ATTR_STATE_FOCUSED<br>
 *                 #JG_COM_ATTR_STATE_ACTIVE
 *           </dl>
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND_SYNC<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND_SYNC
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the inside border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_GAUGE_ATTR_INNER_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_DISABLED<br>
 *                 #JG_COM_ATTR_STATE_ENABLED<br>
 *                 #JG_COM_ATTR_STATE_FOCUSED<br>
 *                 #JG_COM_ATTR_STATE_ACTIVE
 *           </dl>
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND_SYNC<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND_SYNC
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the foreground]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_GAUGE_ATTR_FOREGROUND
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_DISABLED<br>
 *                 #JG_COM_ATTR_STATE_FOCUSED<br>
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
 *       <td>[Color of the background]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_GAUGE_ATTR_BACKGROUND 
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_DISABLED<br>
 *                 #JG_COM_ATTR_STATE_FOCUSED<br>
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
 *   </table>
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When <i>type</i> is an illegal value.</li>
 *    <li>When <i>value1</i> is an illegal value.</li>
 *    <li>When <i>value2</i> is an illegal value.</li>
 *   </ul>
 */
void JginGaugeSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Sets the gauge value.
 * 
 * @param gauge
 *        The handle identifying the gauge
 * @param value
 *        The value to be set
 * 
 *   If the value designated in the parameter value is larger than the maximum 
 *   value for the gauge, the maximum value is set.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When gauge is an illegal handle.</li>
 *    <li>When value is a negative value</li>
 *   </ul>
 */
void JginGaugeSetValue(JGGauge gauge, JKSint32 value);

/**
 * Sets the gauge maximum value.
 * 
 * @param gauge
 *        The handle identifying the gauge.
 * @param maxValue
 *        The maximum value to be set
 * 
 *   If the maximum value set in the parameter maxValue is larger than the 
 *   current value, the current value is set to the new maximum value. In this
 *   case a #JG_GAUGE_EVT_VALUE_CHANGED event is not generated.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When gauge is an illegal handle.</li>
 *    <li>When maxValue is a negative value</li>
 *   </ul>
 */
void JginGaugeSetMaxValue(JGGauge gauge, JKSint32 maxValue);

/**
 * Draws the inner content of a gauge.
 *
 * @param gauge      The gauge handle.
 * @param g          The graphics context handle.
 * @param dx         The x-direction offset of inner content drawing position.
 * @param dy         The y-direction offset of inner content drawing position.
 * @param foreground The foreground color.
 *
 * This function draws the inner content of the gauge using the graphics
 * context designated in the g parameter.
 * This function usees a clip region which is the intersection of the graphics 
 * context clip region and the inner content.
 * The drawing position of the inner content is determined based on the 
 * gauge coordinates and the inset values.
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
void JginGaugePaintContent(JGGauge gauge, JKGraphicsContext g,
                           JKSint32 dx, JKSint32 dy, JKColor foreground);

/**
 * Sets the gauge component event handler.
 * 
 * @param type
 *        The corresponding event type
 * @param handler
 *        The component event handler to be set
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When gauge is an illegal handle.</li>
 *    <li>When type is an illegal value</li>
 *    <li>When handler is  #JK_NULL</li>
 *   </ul>
 */
void JginGaugeSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 * The gauge default component event handler
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information
 * @return
 *        The processing result is returned.
 * 
 * The gauge default component event handler performs the following event 
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 *  <dt> #JG_GAUGE_EVT_CREATED, #JG_GAUGE_EVT_DELETING</dt>
 *  <dd>No operation.</dd>
 *  
 *  <dt> #JG_GAUGE_EVT_MODE_CHANGED</dt>
 *  <dd>Adjusts the gauge maximum setting, and if the display state is Shown, notifies 
 *      the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_GAUGE_EVT_VALUE_CHANGED</dt>
 *  <dd>If the gauge display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT
 *      to JBlend.</dd>
 *  
 *  <dt> #JG_GAUGE_EVT_MAX_VALUE_CHANGED</dt>
 *  <dd>Changes the gauge preferred size and minimum size. 
 *      If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_GAUGE_EVT_REQUEST_INCREMENT, #JG_GAUGE_EVT_REQUEST_DECREMENT</dt>
 *  <dd>Increments or decrements the gauge value.
 *      If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_STATE_CHANGED</dt>
 *  <dd>[When the focus policy is User input occupied type] <br>
 *      If the gauge state changed to Active, notifies the GUI event #JG_GUI_EVT_OCCUPY_INPUT_EVENT to JBlend and occupies the user input event.<br>
 *      If the state changed from Active to another state, notifies the GUI event #JG_GUI_EVT_RELEASE_INPUT_EVENT to JBlend and releases the user input event. <br><br>
 *      [When the focus policy is User input not occupied type]<br>
 *      If the gauge newly acquired focus (went to Focused state from a state other than Active), sets the gauge state to Active state. </dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *  <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT</dt>
 *  <dd>Draws a gauge.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT,  #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH</dt>
 *  <dd>Returns the preferred size (width, height) set in the gauge as return values. </dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *  <dd>Returns the preferred size of the gauge default design.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *  <dd>Returns the minimum size of the gauge default design.</dd>
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
 *  <dd>If the gauge content changed and the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginGaugeDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 *   Sets a key event handler for the gauge in Focused state.
 *
 *   @param handler The key event handler to be set
 *   
 *   This function sets the event handler that is to perform processing when
 *   a gauge in Focused state (#JG_COM_STATE_FOCUSED) receives a key event.
 *
 *   Based on the passed event, the handler should decide whether the 
 *   gauge needs to go to Active state (#JG_COM_STATE_ACTIVE).
 *   If a transition to Active state (#JG_COM_STATE_ACTIVE) is needed,
 *   return #JG_KEY_RES_SET_ACTIVE in the key event handler.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginGaugeSetPreKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 *   The default key event handler for a gauge in Focused state
 *   ( #JG_COM_STATE_FOCUSED ).
 *
 *   @param keyEvent A pointer to the #JGT_KeyEvent structure holding
 *                   the generated event information.
 *   @return         The processing result is returned.
 *   
 *   When a key event is notified to a gauge in Focused (#JG_COM_STATE_FOCUSED) state,
 *   this default key event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system, pass the event to this function
 *   in the event handler implemented for the native system.
 *   <dl>
 *     <dt> #AM_KEYCODE_SELECT </dt>
 *       <dd>
 *         <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED </dt>
 *             <dd>Returns #JG_KEY_RES_SET_ACTIVE as the return value</dd>
 *         </dl>
 *       </dd>
 *   </dl>
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When the value set in component member of the keyEvent is
 *         an illegal handle.</li>
 *   </ul>
 * 
 * @see JginGaugeSetPreKeyEvtHandler()
 * @see JG_KEY_RES_SET_ACTIVE
 */
JKUint32 JginGaugeDefaultPreKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the gauge key event handler.
 * 
 * @param handler
 *        The key event handler to be set
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginGaugeSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 * The gauge default key event handler
 * 
 * @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated 
 *        event information
 * @return
 *        The processing result is returned.
 * 
 * The gauge default key event handler performs the following event 
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 * <dt> #AM_KEYCODE_SELECT </dt>
 *   <dd>
 *     <dl>
 *       <dt> #AM_EVENT_KEY_CLICKED </dt>
 *         <dd>[When the focus policy is User input occupied type]<br>
 *             Sets the gauge state to Focused state and issues a component event 
 *             #JG_COM_EVT_STATE_CHANGED.<br><br>
 *             [When the focus policy is User input not occupied type]<br>
 *             No operation</dd>
 *     </dl>
 *   </dd>
 * <dt> #AM_KEYCODE_RIGHT , #AM_KEYCODE_LEFT </dt>
 *   <dd>
 *     <dl>
 *       <dt> #AM_EVENT_KEY_CLICKED , #AM_EVENT_KEY_REPEATED </dt>
 *         <dd>Increases or decreases the gauge value, and notifies the GUI event
 *             #JG_GUI_GAUGE_EVT_VALUE_CHANGED to JBlend.<br>
 *             Returns #JG_KEY_RES_KEEP_FOCUS as the return value.</dd>
 *     </dl>
 *   </dd>
 * <dt> #AM_KEYCODE_UP , #AM_KEYCODE_DOWN </dt>
 *   <dd>
 *     <dl>
 *       <dt> #AM_EVENT_KEY_CLICKED , #AM_EVENT_KEY_REPEATED </dt>
 *         <dd>Returns 0 as the return value. </dd>
 *     </dl>
 *   </dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_KeyEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginGaugeDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the gauge pointing device event handler.
 * 
 * @param handler
 *        The pointing device event handler to be set
 * 
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 * 
 */
void JginGaugeSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 * The gauge default pointing device event handler.
 * 
 * @param pointerEvent
 *        A pointer to the JGT_PointerEvent structure holding the generated 
 *        event information
 * @return
 *        The processing result is returned.
 * 
 *   This function is provided for future extension. 
 *   It does not perform any action currently.
 */
JKUint32 JginGaugeDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_GAUGE_H */

