/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   Functions for modifying command menu list properties.
 */

#ifndef ___GUI_INNER_COMMANDMENU_H
#define ___GUI_INNER_COMMANDMENU_H

#include <JkTypes.h>

#include <JkGraphics.h>

#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>
#include <gui/inner/JginListBox.h>
#include <gui/common/JgCommandMenu.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_CommandMenu
 * @{
 */

/**
 *   The title text of the command menu list.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *   
 *   If the following settings are made for value1 and value2 when this constant
 *   is set in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A value of 0x7FFFFFFF or more is set for <i>value2</i></li>
 *     <li>#JK_NULL is designated for <i>value1</i> and a non-0 value is designated for <i>value2</i></li>
 *   </ul>
 *   
 *   The title text is automatically centered.
 *   If the string does not fit in the available space, it is displayed flush-left. 
 */
#define JG_CMLST_ATTR_TITLE_TXT           (0x01)

/**
 *   The color of the command menu list title text.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 */
#define JG_CMLST_ATTR_TITLE_TXT_COLOR    (0x02)

/**
 *   The color of the command menu list title text underline.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 */
#define JG_CMLST_ATTR_TITLE_TXT_UNDERLINE_COLOR      (0x03)

/**
 *   The position of the cancel soft key.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> when this constant
 *   is set in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A not 1-3 value is designated for <i>value1</i></li>
 *   </ul>
 */
#define JG_CMLST_ATTR_CANCEL_SOFTKEY_LOCATION           (0x04)

/**
 *   The character string of the cancel soft key.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *
 *   In addition to inside of JgurInit(), this attribute can also be set during JVM suspension.
 *   In the latter case, JginCommandMenuSetStaticAttribute() can be called in the event handler which 
 *   has received the JVM event #JK_VMEVENT_VMSUSPENDED, or in a native system task during the period 
 *   after the #JK_VMEVENT_VMSUSPENDED event is passed until the native system requests JVM resumption.
 *   When setting the attribute during suspension, the change is reflected when the JVM resumes.
 *   
 *   If the following settings are made for <i>value1</i> and <i>value2</i> when this constant
 *   is set in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A value of 0x7FFFFFFF or more is set for <i>value2</i></li>
 *     <li>#JK_NULL is designated for <i>value1</i> and a non-0 value is designated for <i>value2</i></li>
 *   </ul>
 */
#define JG_CMLST_ATTR_CANCEL_SOFTKEY_TXT           (0x05)

/**
 *   List item string for canceling when no soft key.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> and <i>value2</i> when this constant
 *   is set in the type parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A value of 0x7FFFFFFF or more is set for <i>value2</i></li>
 *     <li>#JK_NULL is designated for <i>value1</i> and a non-0 value is designated for <i>value2</i></li>
 *   </ul>
 */
#define JG_CMLST_ATTR_CANCEL_ITEM_TXT           (0x06)

/**
 *   The color of the "foreground" element of the list item for canceling when no soft key.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *   
 *   This constant can be used to change an element attribute value so as to
 *   distinguish a list item for cancellation from the other items. 
 */
#define JG_CMLST_ATTR_CANCEL_ITEM_FOREGROUND      (0x07)

/**
 *   The color of the "background" element of the list item for canceling when no soft key.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *   
 *   This constant can be used to change an element attribute value so as to
 *   distinguish a list item for cancellation from the other items. 
 */
#define JG_CMLST_ATTR_CANCEL_ITEM_BACKGROUND      (0x08)

/**
 *   The position of the select soft key.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> when this constant
 *   is set in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A not 1-3 value is designated for <i>value1</i></li>
 *   </ul>
 */
#define JG_CMLST_ATTR_SELECT_SOFTKEY_LOCATION           (0x09)

/**
 *   The character string of the select soft key.
 *   
 *   This is used for designating the attribute when command menu list default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> and <i>value2</i> when this constant
 *   is set in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A value of 0x7FFFFFFF or more is set for <i>value2</i></li>
 *     <li>#JK_NULL is designated for <i>value1</i> and a non-0 value is designated for <i>value2</i></li>
 *   </ul>
 */
#define JG_CMLST_ATTR_SELECT_SOFTKEY_TXT           (0x0a)
  

/**
 *   A command menu list was created.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the 
 *   JGT_ComEvent structure passed to the event handler by JBlend are 
 *   indicated in the following parameters. The event handler return value 
 *   should be as indicated below.
 * 
 *   @param param1 JKUint32 Additional information about the created command 
 *                          menu list 
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_CMLST_EVT_CREATED            (JG_LSTBX_EVT_END + 0x01)

/**
 *   The command menu list is being deleted.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the 
 *   JGT_ComEvent structure passed to the event handler by JBlend are 
 *   indicated in the following parameters. The event handler return value 
 *   should be as indicated below.
 * 
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_CMLST_EVT_DELETING            (JG_LSTBX_EVT_END + 0x02)

/**
 * @internal
 * The maximum valid component event value for the command menu list.
 */
#define JG_CMLST_EVT_END                 (JG_LSTBX_EVT_END + 0x02)

/**
 *   Sets a command menu list element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all command menu list instances.
 *   Be sure to call this function only from #JgurInit().
 *   The value passed in the <i>type</i> parameter indicates a GUI component attribute. 
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
 *       <td>[Title text]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_TITLE_TXT
 *       <td>A pointer to the buffer holding the text string to be set. <br>
 *           The string does not need termination ('\0').
 *           The pointer designated here must remain valid until the JVM terminates. 
 *       </td>
 *       <td>The number of elements in the character string (not the byte size).
 *           Values between 0 and 0x7FFFFFFF are valid.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of title text]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_TITLE_TXT_COLOR
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of title text underline]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_TITLE_TXT_UNDERLINE_COLOR
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
 *            #JG_CMLST_ATTR_CANCEL_SOFTKEY_LOCATION
 *       <td>Number indicating soft key position (1-3)
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Character string of cancel soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_CANCEL_SOFTKEY_TXT
 *       <td>A pointer to the buffer holding the text string to be set. <br>
 *           The string does not need termination ('\0').
 *           The pointer designated here must remain valid until the JVM terminates. 
 *       </td>
 *       <td>The number of elements in the character string (not the byte size).
 *           Values between 0 and 0x7FFFFFFF are valid.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[List item string for canceling when no soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_CANCEL_ITEM_TXT
 *       <td>A pointer to the buffer holding the text string to be set. <br>
 *           The string does not need termination ('\0').
 *           The pointer designated here must remain valid until the JVM terminates. 
 *       </td>
 *       <td>The number of elements in the character string (not the byte size).
 *           Values between 0 and 0x7FFFFFFF are valid.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the "foreground" element of the list item for canceling when no soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_CANCEL_ITEM_FOREGROUND
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the "background" element of the list item for canceling when no soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_CANCEL_ITEM_BACKGROUND
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Position of select soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_SELECT_SOFTKEY_LOCATION
 *       <td>Number indicating soft key position (1-3)
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Character string of select soft key]<br>
 *           Following constants indicating attribute. <br>
 *            #JG_CMLST_ATTR_SELECT_SOFTKEY_TXT
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
 *   The select soft key does not exist at the initial state.
 *   If a select soft key is used for choosing an item on a command menu list, set its location and label string.
 *   In this case the location must be set before setting the string.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When <i>type</i> is an illegal value.</li>
 *    <li>When <i>value1</i> is an illegal value.</li>
 *    <li>When <i>value2</i> is an illegal value.</li>
 *   </ul>
 */
void JginCommandMenuSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Draws the inner content of a command menu list.
 *
 * @param commandmenu The command menu list handle.
 * @param g           The graphics context handle.
 *
 * This function draws the inner content of the command menu list using the graphics
 * context designated in the g parameter.
 * This function uses a clip region which is the intersection of the graphics 
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
void JginCommandMenuPaintContent(JGCommandMenu commandmenu, JKGraphicsContext g);

/**
 *   Sets the command menu list component event handler.
 *   
 *   @param type The corresponding event type
 *   @param handler The component event handler to be set
 */
void JginCommandMenuSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 *   The default component event handler for the command menu list.
 *   
 *   @param comEvent A pointer to the JGT_ComEvent structure holding the 
 *                   generated event information.
 *   @return The processing result is returned.
 *   
 *   The command menu list default component event handler performs the 
 *   following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this 
 *   function in the event handler implemented for the native system.
 *   
 *   <dl>
 *   <dt> #JG_CMLST_EVT_CREATED, #JG_CMLST_EVT_DELETING </dt>
 *   <dd>No operation.</dd>
 *   
 *   <dt> #JG_LSTBX_EVT_FOCUS_CHANGED</dt>
 *   <dd>Adjusts the display position of items on the command menu list, and if 
 *       the display state is Shown, draws the command menu list.</dd>
 *   
 *   <dt> #JG_LST_EVT_ITEM_INSERTED </dt>
 *     <dd>Changes the command menu list preferred size and minimum size, 
 *       adjusting the inner focus and item display position.
 *       If the command menu list display state is Shown, draws the command 
 *       menu list. </dd>
 *   
 *   <dt> #JG_LST_EVT_ITEM_REMOVED </dt>
 *     <dd>Changes the command menu list preferred size and minimum size, 
 *       adjusting the item display position.
 *       If the command menu list display state is Shown, draws the command 
 *       menu list. </dd>
 *   
 *   <dt> #JG_COM_EVT_FONT_CHANGED, #JG_LST_EVT_ITEM_TEXT_CHANGED ,
 *        #JG_LST_EVT_ITEM_IMAGE_CHANGED, #JG_LST_EVT_ITEM_OFFSCREEN_CHANGED,
 *        #JG_LST_EVT_ITEM_FONT_CHANGED, #JG_LST_EVT_WRAP_POLICY_CHANGED </dt>
 *     <dd>Changes the command menu list preferred size and minimum size, 
 *       adjusting the item display position.
 *       If the command menu list display state is Shown, draws the command 
 *       menu list. </dd>
 *   
 *   <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *     <dd>Returns the preferred height for the designated width. </dd>
 *   
 *   <dt> #JG_COM_EVT_MOVED, #JG_COM_EVT_SIZE_CHANGED </dt>
 *   <dd>Adjusts the display position of items on the command menu list, and if 
 *       the display state is Shown, draws the command menu list.</dd>
 *   
 *   <dt> #JG_LST_EVT_SELECTION_CHANGED </dt>
 *   <dd>If the command menu list display state is Shown, draws the command 
 *       menu list.</dd>
 *   
 *   <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *   <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *   
 *   <dt> #JG_COM_EVT_SHOW </dt>
 *   <dd>Sets the selection cancel soft key ("Back"), performs processing 
 *       necessary for drawing, and draws the command menu list.</dd>
 *   
 *   <dt> #JG_COM_EVT_HIDE </dt>
 *   <dd>Performs processing necessary after drawing ends. </dd>
 *   
 *   <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT </dt>
 *   <dd>Returns the preferred side (width) set for the command menu list. </dd>
 *   
 *   <dt> #JG_LSTBX_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS </dt>
 *   <dd>Returns the preferred height for the designated rows.</dd>
 *  
 *   <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *   <dd>Returns the preferred size of the command menu list default design.</dd>
 *  
 *   <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *   <dd>Returns the minimum size of the command menu list default design.</dd>
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
 *   <dt>Other events</dt>
 *   <dd>No operation.</dd>
 *   </dl>
 */
JKUint32 JginCommandMenuDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 *   Sets the command menu list key event handler.
 *   
 *   @param handler The key event handler to be set.
 */
void JginCommandMenuSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 *   The default key event handler for the command menu list.
 *   
 *   @param keyEvent 
 *        A pointer to the JGT_KeyEvent structure holding the generated event 
 *        information.
 *   @return 
 *        The processing result is returned.
 *   
 *   The command menu list default key event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *     <dt> #AM_KEYCODE_SELECT </dt>
 *       <dd>
 *         <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED </dt>
 *             <dd>Sets the focus item to selected state and notifies the GUI event 
 *                 #JG_GUI_LST_EVT_SELECTION_CHANGED to JBlend.</dd>
 *         </dl>
 *       </dd>
 *     <dt> #AM_KEYCODE_NUM0 - #AM_KEYCODE_NUM9 </dt>
 *       <dd>
 *         <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED </dt>
 *             <dd>If the number of registered items is 10 or fewer, puts in selected 
 *                 state the item corresponding to the pressed key, and notifies the 
 *                 GUI event #JG_GUI_LST_EVT_SELECTION_CHANGED to JBlend.
 *                 If there are more than 10 items, does nothing. </dd>
 *         </dl>
 *       </dd>
 *     <dt> #AM_KEYCODE_SOFT1 </dt>
 *       <dd>
 *         <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED </dt>
 *             <dd>Notifies the GUI event #JG_GUI_CMLST_EVT_CANCEL to 
 *                 JBlend.</dd>
 *         </dl>
 *       </dd>
 *     <dt> #AM_KEYCODE_UP, #AM_KEYCODE_DOWN </dt>
 *       <dd>
 *         <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED, #AM_EVENT_KEY_REPEATED </dt>
 *             <dd>If inner focus can be moved in the direction of the pressed key, 
 *                 moves inner focus and scrolls the item display as necessary.
 *                 If the display must be updated, draws the command menu list. </dd>
 *         </dl>
 *       </dd>
 *   </dl>
 */
JKUint32 JginCommandMenuDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 *   Sets the command menu list pointing device event handler.
 *   
 *   @param handler The pointing device event handler to be set.
 *   
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 * 
 */
void JginCommandMenuSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 *   The default pointing device handler for the command menu list.
 *   
 *   @param pointerEvent 
 *        A pointer to the JGT_PointerEvent structure holding the generated 
 *        event information
 *   @return 
 *        The processing result is returned.
 *   
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 *   
 *   The command menu list default pointing event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *     <dt> #AM_EVENT_POINTER_PRESSED </dt>
 *     <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, 
 *         moves the inner focus to the item that has been clicked by the pointing device.</dd>
 *     <dt> #AM_EVENT_POINTER_CLICKED </dt>
 *     <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, 
 *         the pointing device pointer coordinates is in the item that has inner focus,
 *         changes the selection state and passes a GUI event #JG_GUI_LST_EVT_SELECTION_CHANGED to JBlend.</dd>
 *   </dl>
 * 
 */
JKUint32 JginCommandMenuDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_COMMANDMENU_H */

