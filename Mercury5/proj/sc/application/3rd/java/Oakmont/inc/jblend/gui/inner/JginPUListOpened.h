/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * The API for modifying the opened popup list component properties.
 */

#ifndef ___GUI_INNER_POPUPLISTOPENED_H
#define ___GUI_INNER_POPUPLISTOPENED_H

#include <JkTypes.h>

#include <JkGraphics.h>

#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>
#include <gui/inner/JginListBox.h>
#include <gui/common/JgPUListOpened.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_PopupListOpened
 * @{
 */

/**
 *   The color of the PUListOpened outside border.
 *   
 *   This is used for designating the attribute when PUListOpened default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginPUListOpenedSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The PUListOpened border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot outermost rectangle of the border.
 */
#define JG_PULSTOPENED_ATTR_OUTER_BORDER_COLOR      (0x01)

/**
 *   The color of the PUListOpened inside border.
 *   
 *   This is used for designating the attribute when PUListOpened default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginPUListOpenedSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The PUListOpened border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot innermost rectangle of the border.
 */
#define JG_PULSTOPENED_ATTR_INNER_BORDER_COLOR      (0x02)

/**
 *   The color of the PUListOpened scroll arrows.
 *   
 *   This is used for designating the attribute when PUListOpened default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginPUListOpenedSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_PULSTOPENED_ATTR_ARROW_COLOR      (0x03)

/**
 *   The position of the cancel soft key.
 *   
 *   This is used for designating the attribute when PUListOpened default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginPUListOpenedSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> when this constant
 *   is set in the <i>type</i> parameter of #JginPUListOpenedSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A not 1-3 value is designated for <i>value1</i></li>
 *   </ul>
 */
#define JG_PULSTOPENED_ATTR_CANCEL_SOFTKEY_LOCATION           (0x04)

/**
 *   The character string of the cancel soft key.
 *   
 *   This is used for designating the attribute when PUListOpened default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginPUListOpenedSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> and <i>value2</i> when this constant
 *   is set in the <i>type</i> parameter of #JginPUListOpenedSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A value of 0x7FFFFFFF or more is set for <i>value2</i></li>
 *     <li>#JK_NULL is designated for <i>value1</i> and a non-0 value is designated for <i>value2</i></li>
 *   </ul>
 */
#define JG_PULSTOPENED_ATTR_CANCEL_SOFTKEY_TXT           (0x05)

/**
 * A PUListOpened was created.
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
#define JG_PULSTOPENED_EVT_CREATED             (JG_LSTBX_EVT_END + 0x01)

/**
 * A PUListOpened is being deleted.
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
#define JG_PULSTOPENED_EVT_DELETING            (JG_LSTBX_EVT_END + 0x02)

/**
 * @internal
 * The maximum valid component event value for the PUListOpened.
 */
#define JG_PULSTOPENED_EVT_END                 (JG_LSTBX_EVT_END + 0x02)

/**
 *   Sets a PUListOpened element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all PUListOpened instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of a constant
 *   indicating GUI component attributes and a constant indicating GUI component state. 
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
 *            <dd> #JG_PULSTOPENED_ATTR_OUTER_BORDER_COLOR 
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ACTIVE
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
 *            <dd> #JG_PULSTOPENED_ATTR_INNER_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ACTIVE
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
 *            <dd> #JG_PULSTOPENED_ATTR_ARROW_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ACTIVE
 *           </dl>
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Position of cancel soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_PULSTOPENED_ATTR_CANCEL_SOFTKEY_LOCATION
 *       <td>Number indicating soft key position (1-3)
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Character string of cancel soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_PULSTOPENED_ATTR_CANCEL_SOFTKEY_TXT
 *       <td>A pointer to the buffer holding the text string to be set. <br>
 *           The string does not need termination ('\0').
 *           The pointer designated here must remain valid until the JVM terminates. 
 *       </td>
 *       <td>The number of elements in the character string (not the byte size).
 *           Values between 0 and 0x7FFFFFFF are valid.
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
void JginPUListOpenedSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Draws the inner content of a PUListOpened.
 *
 * @param implicit   The PUListOpened handle.
 * @param g          The graphics context handle.
 *
 * This function draws the inner content of the PUListOpened using the graphics
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
void JginPUListOpenedPaintContent(JGPopUpListOpened popuplist, JKGraphicsContext g);

/**
 * Sets the PUListOpened component event handler.
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
void JginPUListOpenedSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 * The PUListOpened default component event handler
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information.
 * @return
 *        The processing result is returned.
 * 
 * The PUListOpened default component event handler performs the following
 * event processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event
 * handler implemented for the native system.
 * <dl>
 *  <dt> #JG_PULSTOPENED_EVT_CREATED , #JG_PULSTOPENED_EVT_DELETING</dt>
 *  <dd> No operation</dd>
 *  
 *  <dt> #JG_LSTBX_EVT_FOCUS_CHANGED</dt>
 *  <dd>Adjusts the display position of items in the PUListOpened. 
 *      If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *    <dd>Returns the preferred height for the designated width. </dd>
 *  
 *  <dt> #JG_LST_EVT_SELECTION_CHANGED</dt>
 *  <dd>If the PUListOpened display state is Shown, notifies the GUI event
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_STATE_CHANGED</dt>
 *  <dd>
 *       If the state changed from Active to another state, changes parent PUList 
 *       state to Focused.</dd>
 *  
 *   <dt> #JG_COM_EVT_FONT_CHANGED, #JG_LST_EVT_ITEM_TEXT_CHANGED, #JG_LST_EVT_ITEM_IMAGE_CHANGED, 
 *        #JG_LST_EVT_ITEM_OFFSCREEN_CHANGED, 
 *        #JG_LST_EVT_ITEM_FONT_CHANGED, #JG_LST_EVT_WRAP_POLICY_CHANGED,
 *        #JG_LST_EVT_ITEM_INSERTED, #JG_LST_EVT_ITEM_REMOVED </dt>
 *   <dd>Changes the PUListOpened preferred size and minimum size.
 *       If the display state is Shown, notifies the GUI event 
 *       #JG_GUI_EVT_REPAINT to JBlend.<br>
 *       If the popup list is open, closes the popup list.
</dd>
 *  
 *   <dt> #JG_COM_EVT_MOVED , #JG_COM_EVT_SIZE_CHANGED</dt>
 *   <dd>Adjusts the display position of items in the PUListOpened.
 *       If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *   
 *   <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *   <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *   <dt> #JG_COM_EVT_PAINT</dt>
 *   <dd>Draws a PUListOpened.</dd>
 *  
 *   <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT </dt>
 *    <dd>Returns the preferred size (width) set for the PUListOpened.</dd>
 *  
 *  <dt> #JG_LSTBX_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS </dt>
 *    <dd>Returns the preferred height for the designated rows.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH,  #JG_COM_EVT_GET_PREF_HEIGHT</dt>
 *    <dd>Returns the preferred size of the PUListOpened default design.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_MIN_WIDTH,  #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *    <dd>Returns the minimum size of the PUListOpened default design.</dd>
 *  
 *  <dt> #JG_COM_EVT_FGCOLOR_CHANGED </dt>
 *    <dd>Changes the foreground color of the list items.</dd>
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
 *   <dt>Other events</dt>
 *   <dd>If the PUListOpened content has changed and the display state is Shown, 
 *       notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *   </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginPUListOpenedDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 * Sets the PUListOpened key event handler.
 * 
 * @param handler
 *        The key event handler to be set
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginPUListOpenedSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 * The PUListOpened default key event handler
 * 
 * @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated 
 *        event information
 * @return
 *        The processing result is returned.
 * 
 *   The default key event handler for the PUListOpened.
 *   
 *   @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated event 
 *        information.
 *   @return
 *        The processing result is returned.
 *   
 *   The PUListOpened default key event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *     <dt> #AM_KEYCODE_SELECT </dt>
 *       <dd>
 *         <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED </dt>
 *             <dd>If there is inner focus, puts the focus item in selected state 
 *                 regardless of the previous selection state and notifies the GUI event 
 *                 #JG_GUI_LST_EVT_SELECTION_CHANGED to JBlend.
 *                 After that, sets the PUListOpened state to Enabled state and issues the component event #JG_COM_EVT_STATE_CHANGED.</dd>
 *         </dl>
 *       </dd>
 *     <dt> #AM_KEYCODE_UP, #AM_KEYCODE_DOWN </dt>
 *       <dd>
 *         <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED, #AM_EVENT_KEY_REPEATED </dt>
 *             <dd>If inner focus can be moved in the direction of the pressed key, 
 *                 moves inner focus and scrolls the item display as necessary.
 *                 Returns 0 as the return value.</dd>
 *         </dl>
 *       </dd>
 *     <dt> #AM_KEYCODE_SOFT1 - #AM_KEYCODE_SOFT3 </dt>
 *     <dd>
 *       <dl>
 *        <dt> #AM_EVENT_KEY_CLICKED </dt>
 *         <dd>If the key is the one set by #JG_PULSTOPENED_ATTR_CANCEL_SOFTKEY_LOCATION,
 *             sets the PUListOpened in Focused state, and 
 *             issues a #JG_COM_EVT_STATE_CHANGED component event.</dd>
 *       </dl>
 *     </dd>
 *   </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_KeyEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginPUListOpenedDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the PUListOpened pointing device event handler.
 * 
 * @param handler
 *        The pointing device event handler to be set
 * 
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 */
void JginPUListOpenedSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 * The PUListOpened default pointing device event handler.
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
 *   The PUListOpened default pointing event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   
 *   <dl>
 *    <dt> #AM_EVENT_POINTER_PRESSED </dt>
 *    <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *        <dl>
 *          <dt>If the PUListOpened state is #JG_COM_STATE_FOCUSED, </dt>
 *          <dd>sets #JG_COM_STATE_ACTIVE as the state.</dd>
 *          <dt>If the PUListOpened state is #JG_COM_STATE_ACTIVE, </dt>
 *          <dd>moves the inner focus to the item that has been clicked by the pointing device.</dd>
 *        </dl>
 *    </dd>
 *    <dt> #AM_EVENT_POINTER_CLICKED </dt>
 *    <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *        <dl>
 *          <dt>If the PUListOpened state is #JG_COM_STATE_ACTIVE, </dt>
 *          <dd>If the pointing device pointer coordinates is in the item that has inner focus,
 *              changes the selection state and passes a GUI event #JG_GUI_LST_EVT_SELECTION_CHANGED to JBlend.</dd>
 *        </dl>
 *    </dd>
 *   </dl>
 */
JKUint32 JginPUListOpenedDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_POPUPLISTOPENED_H */

