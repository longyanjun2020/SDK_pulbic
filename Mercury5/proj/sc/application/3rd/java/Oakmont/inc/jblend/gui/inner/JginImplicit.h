/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * The API for modifying the IMPLICIT list component properties.
 */

#ifndef ___GUI_INNER_IMPLICITLIST_H
#define ___GUI_INNER_IMPLICITLIST_H

#include <JkTypes.h>

#include <JkGraphics.h>

#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>
#include <gui/inner/JginListBox.h>
#include <gui/common/JgImplicit.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_ImplicitList
 * @{
 */

/**
 *   The color of the implicit list outside border.
 *   
 *   This is used for designating the attribute when implicit list default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginImplicitSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The implicit list border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot outermost rectangle of the border.
 */
#define JG_IMPLICIT_ATTR_OUTER_BORDER_COLOR      (0x01)

/**
 *   The color of the implicit list inside border.
 *   
 *   This is used for designating the attribute when implicit list default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginImplicitSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The implicit list border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot innermost rectangle of the border.
 */
#define JG_IMPLICIT_ATTR_INNER_BORDER_COLOR      (0x02)

/**
 *   The color of the implicit list scroll arrows.
 *   
 *   This is used for designating the attribute when implicit list default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginImplicitSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_IMPLICIT_ATTR_ARROW_COLOR      (0x03)

/**
 * An IMPLICIT list was created.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *               JKUint32 Additional information about the list creation
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
#define JG_IMPLICIT_EVT_CREATED             (JG_LSTBX_EVT_END + 0x01)

/**
 * An IMPLICIT list is being deleted.
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
#define JG_IMPLICIT_EVT_DELETING            (JG_LSTBX_EVT_END + 0x02)

/**
 * @internal
 * The maximum valid component event value for the IMPLICIT list.
 */
#define JG_IMPLICIT_EVT_END                 (JG_LSTBX_EVT_END + 0x02)

/**
 *   Sets a implicit list element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all implicit list instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of a constant
 *   indicating GUI component attributes and a constant indicating GUI component state. 
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
 *       <td>[Color of the outside border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_IMPLICIT_ATTR_OUTER_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br> #JG_COM_ATTR_STATE_FOCUSED<br>
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
 *       <td>[Color of the inside border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_IMPLICIT_ATTR_INNER_BORDER_COLOR 
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br> #JG_COM_ATTR_STATE_FOCUSED<br>
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
 *       <td>[Color of the scroll arrows]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_IMPLICIT_ATTR_ARROW_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br> #JG_COM_ATTR_STATE_FOCUSED<br>
 *                 #JG_COM_ATTR_STATE_ACTIVE
 *           </dl>
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND
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
void JginImplicitSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Draws the inner content of a IMPLICIT list.
 *
 * @param implicit   The IMPLICIT list handle.
 * @param g          The graphics context handle.
 *
 * This function draws the inner content of the IMPLICIT list using the graphics
 * context designated in the g parameter.
 * This function usees a clip region which is the intersection of the graphics 
 * context clip region and the inner content.
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
void JginImplicitPaintContent(JGImplicitList implicit, JKGraphicsContext g);

/**
 * Sets the IMPLICIT list component event handler.
 * 
 * @param type
 *        The corresponding event type
 * @param handler
 *        The component event handler to be set
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When type is an illegal value.</li>
 *    <li>When handler is  #JK_NULL.</li>
 *   </ul>
 */
void JginImplicitSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 * The IMPLICIT list default component event handler
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information.
 * @return
 *        The processing result is returned.
 * 
 * The IMPLICIT list default component event handler performs the following 
 * event processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 *  <dt> #JG_IMPLICIT_EVT_CREATED, #JG_IMPLICIT_EVT_DELETING</dt>
 *  <dd>No operation.</dd>
 *  
 *  <dt> #JG_LSTBX_EVT_FOCUS_CHANGED</dt>
 *  <dd>Adjusts the display position of items in the implicit list.
 *      If the display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_LST_EVT_ITEM_INSERTED </dt>
 *  <dd>Changes the implicit list preferred size and minimum size, adjusting 
 *      the inner focus and item display position.
 *      If the display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_LST_EVT_ITEM_REMOVED </dt>
 *    <dd>Changes the implicit list preferred size and minimum size, adjusting 
 *        the item display position.
 *      If the display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *    <dd>Returns the preferred height for the designated width.</dd>
 *  
 *  <dt> #JG_LST_EVT_SELECTION_CHANGED</dt>
 *  <dd>If the implicit list display state is Shown, notifies the GUI event
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_STATE_CHANGED</dt>
 *  <dd>[When the focus policy is user input occupied type]<br>
 *      If the implicit list state has gone to Active state, notifies the GUI 
 *      event #JG_GUI_EVT_OCCUPY_INPUT_EVENT to JBlend and occupies the 
 *      user input event.<br>
 *      If the state has gone from Active to another state, notifies the GUI 
 *      event #JG_GUI_EVT_RELEASE_INPUT_EVENT to JBlend and releases the 
 *      user input event.<br><br>
 *      [When the focus policy is User input not occupied type]<br>
 *      If the implicit list newly acquired focus (went to Focused state from a 
 *      state other than Active), sets the implicit list state to Active 
 *      state.</dd>
 *  
 *  <dt> #JG_COM_EVT_FONT_CHANGED, #JG_LST_EVT_ITEM_TEXT_CHANGED,
 *       #JG_LST_EVT_ITEM_IMAGE_CHANGED, #JG_LST_EVT_ITEM_OFFSCREEN_CHANGED,
 *       #JG_LST_EVT_ITEM_FONT_CHANGED, #JG_LST_EVT_WRAP_POLICY_CHANGED </dt>
 *  <dd>Changes the implicit list preferred size and minimum size, adjusting
 *      inner focus and the item display position.
 *      If the display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_MOVED, #JG_COM_EVT_SIZE_CHANGED</dt>
 *  <dd>Adjusts the display position of items in the implicit list, and if the 
 *      display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to 
 *      JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *  <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT</dt>
 *  <dd>Draws an implicit list.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT</dt>
 *  <dd>Returns the preferred size (width) set for the implicit list.</dd>
 *  
 *  <dt> #JG_LSTBX_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS </dt>
 *  <dd>Returns the preferred height for the designated rows.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *  <dd>Returns the preferred size of the implicit list default design.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *  <dd>Returns the minimum size of the implicit list default design.</dd>
 *  
 *  <dt> #JG_COM_EVT_FGCOLOR_CHANGED </dt>
 *  <dd>Changes the foreground color of the list items.</dd>
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
 *  <dd>If the implicit list drawing content changed and the display state is 
 *      Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginImplicitDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 * Sets the IMPLICIT list key event handler.
 * 
 * @param handler
 *        The key event handler to be set
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginImplicitSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 * The IMPLICIT list default key event handler
 * 
 * @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated 
 *        event information
 * @return
 *        The processing result is returned.
 * 
 * The IMPLICIT list default key event handler performs the following event
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 * <dt> #AM_KEYCODE_SELECT </dt>
 *   <dd>
 *     <dl>
 *       <dt> #AM_EVENT_KEY_CLICKED </dt>
 *         <dd>If there is inner focus, puts the focus item in selected state regardless
 *             of the previous selection state and notifies the GUI event
 *             #JG_GUI_LST_EVT_SELECTION_CHANGED to JBlend.
 *             Thereafter the following processing is performed.<br>
 *             [When the focus policy is User input occupied type]<br>
 *             Sets the implicit list state to Focused state and issues the component event #JG_COM_EVT_STATE_CHANGED.<br><br>
 *             [When the focus policy is User input not occupied type]<br>
 *             No operation.
 *         </dd>
 *     </dl>
 *   </dd>
 * <dt> #AM_KEYCODE_UP , #AM_KEYCODE_DOWN </dt>
 *   <dd>
 *     <dl>
 *       <dt> #AM_EVENT_KEY_CLICKED , #AM_EVENT_KEY_REPEATED </dt>
 *         <dd>[When the focus policy is User input occupied type]<br>
 *             Returns 0 as the return value.<br><br>
 *             [When the focus policy is User input not occupied type]<br>
 *             If inner focus can be moved in the direction of the pressed key,
 *             moves inner focus and scrolls the item display as necessary.
 *             Returns #JG_KEY_RES_KEEP_FOCUS as the return value.<br>
 *             If inner focus cannot be moved in the direction of the pressed key, returns 0 as the return value.
 *         </dd>
 *     </dl>
 *   </dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_KeyEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginImplicitDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the IMPLICIT list pointing device event handler.
 * 
 * @param handler
 *        The pointing device event handler to be set
 * 
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 */
void JginImplicitSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 * The IMPLICIT list default pointing device event handler.
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
 *   The IMPLICIT list default pointing event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *    <dt> #AM_EVENT_POINTER_PRESSED </dt>
 *    <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *        <dl>
 *          <dt>If the IMPLICIT list is #JG_COM_STATE_FOCUSED, </dt>
 *          <dd>sets #JG_COM_STATE_ACTIVE as the state.</dd>
 *          <dt>If the IMPLICIT list is #JG_COM_STATE_ACTIVE, </dt>
 *          <dd>moves the inner focus to the item that has been clicked by the pointing device.</dd>
 *        </dl>
 *      </dd>
 *    <dt> #AM_EVENT_POINTER_CLICKED </dt>
 *    <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *        <dl>
 *          <dt>If the IMPLICIT list is #JG_COM_STATE_ACTIVE, </dt>
 *          <dd>If the pointing device pointer coordinates is in the item that has inner focus,
 *              changes the selection state and passes a GUI event #JG_GUI_LST_EVT_SELECTION_CHANGED to JBlend.</dd>
 *        </dl>
 *      </dd>
 *   </dl>
 */
JKUint32 JginImplicitDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_IMPLICITLIST_H */

