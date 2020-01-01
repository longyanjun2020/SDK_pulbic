/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying textbox component properties.
 */

#ifndef ___GUI_INNER_TEXTBOX_H
#define ___GUI_INNER_TEXTBOX_H

#include <JkTypes.h>

#include <JkGraphics.h>
#include <JkVideoComponent.h>

#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>
#include <gui/inner/JginTextInput.h>
#include <gui/common/JgTextBox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_TextBox
 * @{
 */

/**
 *   The color of the border indicating textbox focus frame.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_TXTBX_ATTR_FOCUS_BORDER_COLOR      (0x01)

/**
 *   The color of the textbox "foreground" element.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_TXTBX_ATTR_FOREGROUND     (0x02)

/**
 *   The color of the textbox "background" element.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_TXTBX_ATTR_BACKGROUND     (0x03)

/**
 *   The color of the outside upper left of textbox border.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_TXTBX_ATTR_OUTER_LT_BORDER_COLOR     (0x04)

/**
 *   The color of the inside upper left of textbox border.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_TXTBX_ATTR_INNER_LT_BORDER_COLOR     (0x05)

/**
 *   The color of the lower right of textbox border.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_TXTBX_ATTR_RB_BORDER_COLOR     (0x06)

/**
 *   Visible state switching of the textbox focus frame.
 *   
 *   Indicates the switching of the textbox focus frame between visible and hidden. 
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute().
 * 
 *   When the value of this attribute is set to #JG_COM_VAL_FLG_OFF, the textbox display 
 *   size is increased in order to show the textbox to the full extent of the focus frame. 
 */
#define JG_TXTBX_ATTR_FOCUS_BORDER_MODE        (0x07)

/**
 *   String displayed in password mode textbox.
 *   
 *   Indicates whether word-wrapping is to be applied when text entered in password 
 *   mode includes a line feed code.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute().
 *   
 *   When the value of this attribute is set to #JG_COM_VAL_FLG_ON
 *   and the display text includes a line feed code, the text is wrapped. 
 *   When #JG_COM_VAL_FLG_OFF is set, text is not wrapped even if a line
 *   feed code is present.
 *   Line feed codes are displayed in password mode just like ordinary text.
 */
#define JG_TXTBX_ATTR_PASSWD_LINE_FEED        (0x08)

/**
 *   Use of the inline view mode
 *   
 *   Indicates whether an uneditable textbox should work in inline view mode 
 *   when the textbox enters in the #JG_COM_STATE_ACTIVE state. 
 *   
 *   The inline view mode is a textbox mode in which the textbox text
 *   can be viewd without activating an Input Method.
 *   Text scrolling etc. is available in the mode.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute().
 *   
 *   If the value of this attribute has been set to #JG_COM_VAL_FLG_ON, 
 *   textbox works in inline view mode when it enters in 
 *   #JG_COM_STATE_ACTIVE state.
 *   If the attribute has been set to #JG_COM_VAL_FLG_OFF, an Input Method is activated
 *   when the textbox enters in #JG_COM_STATE_ACTIVE state.
 */
#define JG_TXTBX_ATTR_INLINE_VIEW_MODE          (0x09)

/**
 *   Position of the End soft-key in inline view mode
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> when this constant
 *   is set in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A not 1-3 value is designated for <i>value1</i></li>
 *   </ul>
 *
 */
#define JG_TXTBX_ATTR_END_SOFTKEY_LOCATION      (0x0a)

/**
 *   Label text of the End soft-key in inline view mode
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute().
 *   
 *   If the following settings are made for <i>value1</i> and <i>value2</i> when this constant
 *   is set in the <i>type</i> parameter of #JginCommandMenuSetStaticAttribute(),
 *   @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>A value of 0x7FFFFFFF or more is set for <i>value2</i></li>
 *     <li>#JK_NULL is designated for <i>value1</i> and a non-0 value is designated for <i>value2</i></li>
 *   </ul>
 */
#define JG_TXTBX_ATTR_END_SOFTKEY_TXT           (0x0b)

/**
 *   Whether or not to occupy screen at the timing of launching the input method.
 *   
 *   This is used for designating the attribute when textbox default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginTextBoxSetStaticAttribute().
 *   
 *   When #JG_COM_VAL_FLG_OFF is set as the value of this attribute, 
 *   screen occupation does not take place at the timing of launching the input method.
 *   When #JG_COM_VAL_FLG_ON is set, it does.
 */
#define JG_TXTBX_ATTR_OCCUPY_SCREEN_WHEN_INPUT  (0x0c)

/**
 * A textbox was created.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *               JKUint32 Additional information about the textbox creation
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
#define JG_TXTBX_EVT_CREATED                (JG_TXT_EVT_END + 0x01)

/**
 * A textbox is being deleted.
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
#define JG_TXTBX_EVT_DELETING               (JG_TXT_EVT_END + 0x02)

/**
 *   @deprecated
 *   This constant is due to be abolished, and has been replaced by #JG_COM_EVT_TRUNCATE_MODE_CHANGED.
 *   Use of this constant is not recommended.
 */
#define JG_TXTBX_EVT_TRUNCATE_MODE_CHANGED      JG_COM_EVT_TRUNCATE_MODE_CHANGED



/**
 * @internal
 * The maximum valid component event value for the textbox.
 */
#define JG_TXTBX_EVT_END                    (JG_TXT_EVT_END + 0x05)

/**
 *   Sets a textbox element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all textbox instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of a constant
 *   indicating a GUI component attribute and a constant indicating GUI component state. 
 *   The constant indicating GUI component state may designate one state or a combination of states. 
 *   When a combination of states is designated, attributes for multiple states may be set at
 *   the same time. 
 *   Whether or not a focus frame is visible, and the string displayed in 
 *   password mode, are common settings regardless of state; accordingly, only 
 *   a constant indicating an attribute is passed. 
 *   Attribute values are passed in value1 and value2.
 *   A list of the parameters passed to this function is given below. 
 *   
 *   <table>
 *     <tr> 
 *       <td><b><i>type</i></b>
 *       <td><b><i>value1</i></b>
 *       <td><b><i>value2</i></b>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the focus frame]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_TXTBX_ATTR_FOCUS_BORDER_COLOR
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
 *       <td>[Visible state switching of the focus frame]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_TXTBX_ATTR_FOCUS_BORDER_MODE
 *       <td>Visible: #JG_COM_VAL_FLG_ON<br>
 *           Hidden: #JG_COM_VAL_FLG_OFF
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[String displayed in password mode]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_TXTBX_ATTR_PASSWD_LINE_FEED
 *       <td>Wrap: #JG_COM_VAL_FLG_ON<br>
 *           Not wrap: #JG_COM_VAL_FLG_OFF
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the foreground]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_TXTBX_ATTR_FOREGROUND 
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_FOCUSED<br> #JG_COM_ATTR_STATE_ACTIVE
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
 *            <dd> #JG_TXTBX_ATTR_BACKGROUND 
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_FOCUSED<br> #JG_COM_ATTR_STATE_ACTIVE
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
 *       <td>[Color of the upper left of border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_TXTBX_ATTR_OUTER_LT_BORDER_COLOR 
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
 *       <td>[Color of the outside upper left of border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_TXTBX_ATTR_INNER_LT_BORDER_COLOR
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
 *       <td>[Color of the inside upper left of border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_TXTBX_ATTR_RB_BORDER_COLOR
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
 *       <td>[Use of the inline view mode]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_TXTBX_ATTR_INLINE_VIEW_MODE
 *       <td>Use: #JG_COM_VAL_FLG_ON <br>
 *           Not use: #JG_COM_VAL_FLG_OFF
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Position of the End soft-key in inline view mode]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_TXTBX_ATTR_END_SOFTKEY_LOCATION
 *       <td>Number indicating soft key position (1-3)
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Character string of the End soft-key in inline view mode]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_TXTBX_ATTR_END_SOFTKEY_TXT
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
void JginTextBoxSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Draws the inner content of a textbox.
 *
 * @param textbox    The textbox handle.
 * @param g          The graphics context handle.
 * @param dx         The x-direction offset of inner content drawing position.
 * @param dy         The y-direction offset of inner content drawing position.
 * @param foreground The foreground color.
 *
 * This function draws the inner content of the textbox using the graphics
 * context designated in the g parameter.
 * This function usees a clip region which is the intersection of the graphics 
 * context clip region and the inner content.
 * The drawing position of the inner content is determined based on the 
 * textbox coordinates and the inset values.
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
void JginTextBoxPaintContent(JGTextBox textbox, JKGraphicsContext g,
                             JKSint32 dx, JKSint32 dy, JKColor foreground);

/**
 * Sets the textbox component event handler.
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
void JginTextBoxSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 * The textbox default component event handler
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information
 * @return
 *        The processing result is returned.
 * 
 * The textbox default component event handler performs the following event 
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 *  <dt> #JG_TXTBX_EVT_CREATED, #JG_TXTBX_EVT_DELETING</dt>
 *  <dd>No operation</dd>
 *  
 *  <dt> #JG_TXT_EVT_TEXT_CHANGED</dt>
 *  <dd>Changes the textbox preferred size and minimum size, also 
 *      adjusting the input position.<br>
 *      If the display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  
 *  
 *  <dt> #JG_TXT_EVT_PASSWORD_MODE_CHANGED </dt>
 *  <dd> When the attribute value indicated by #JG_TXTBX_ATTR_PASSWD_LINE_FEED is
 *      #JG_COM_VAL_FLG_OFF, the textbox preferred size is changed. <br>
 *      If the display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  <dt> #JG_COM_EVT_STATE_CHANGED</dt>
 *  
 *  <dd>
 *    <dl>
 *      <dt>[When the focus policy is User input occupied type]<br>
 *        <dd><dl>
 *          <dt>Editable</dt>
 *            <dd>If the textbox state changed to Active, notifies the GUI events
 *             #JG_GUI_EVT_OCCUPY_INPUT_EVENT and #JG_GUI_EVT_OCCUPY_SCREEN to 
 *             JBlend in order to occupy the user input event and screen.
 *             When processing of the GUI event #JG_GUI_EVT_OCCUPY_SCREEN 
 *             takes place, JBlend determines whether the textbox state 
 *             is editable, and processes as follows based on the result:
 *             -  Editable: Occupies the screen and calls 
 *                #JgurTextInputLaunchInputMethod().
 *             -  Not editable: Releases the screen occupation.
 *             .
 *             <br>
 *             If the state changed from Active to another state, calls 
 *             the function #JgurTextInputCancelInputMethod(), then 
 *             notifies the GUI events #JG_GUI_EVT_RELEASE_INPUT_EVENT 
 *             and #JG_GUI_EVT_RELEASE_SCREEN to JBlend in order to 
 *             release the user input event and screen. 
 *             Next it notifies the GUI event #JG_GUI_EVT_REPAINT_SCREEN to 
 *             JBlend in order to effect screen redrawing.</dd>
 *         <dt>Not editable</dt>
 *            <dd>If the textbox state changed to Active, notifies the GUI 
 *            event #JG_GUI_EVT_OCCUPY_INPUT_EVENT to JBlend in order 
 *            to occupy the user input event.<br>
 *            If the state changed from Active to another state, notifies 
 *            the GUI event #JG_GUI_EVT_RELEASE_INPUT_EVENT to JBlend
 *            in order to release the user input event and screen. Next it
 *            notifies the GUI event #JG_GUI_EVT_REPAINT_SCREEN to
 *            JBlend in order to effect screen redrawing.</dd>
 *        </dl></dd>
 *      <dt>[When the focus policy is User input not occupied type]<br>
 *       <dd>If the textbox newly acquired focus (went to Focused state from a state other than Active), sets the textbox state to Active state.</dd>
 *    </dl>
 *  </dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *  <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT</dt>
 *  <dd>Draws a textbox.</dd>
 *  
 *  <dt> #JG_COM_EVT_FONT_CHANGED</dt>
 *  <dd>Changes the textbox preferred size and minimum size.<br>
 *      If the display state is Shown, notifies the GUI event 
 *      #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *    <dd>Returns the preferred height for the designated width. </dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT </dt>
 *    <dd>Returns the preferred size (width) set for the textbox
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *    <dd>Returns the preferred size of the textbox default design. </dd>
 *  
 *  <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *    <dd>Returns the minimum size of the textbox default design.</dd>
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
 *  <dd>If the textbox content changed and the display state is Shown, notifies 
 *      the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginTextBoxDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 *   Sets a key event handler for the textbox in Focused state.
 *
 *   @param handler The key event handler to be set
 *   
 *   This function sets the event handler that is to perform processing when
 *   a textbox in Focused state (#JG_COM_STATE_FOCUSED) receives a key event.
 *
 *   Based on the passed event, the handler should decide whether the 
 *   textbox needs to go to Active state (#JG_COM_STATE_ACTIVE).
 *   If a transition to Active state (#JG_COM_STATE_ACTIVE) is needed,
 *   return #JG_KEY_RES_SET_ACTIVE in the key event handler.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginTextBoxSetPreKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 *   The default key event handler for a textbox in Focused state
 *   ( #JG_COM_STATE_FOCUSED ).
 *
 *   @param keyEvent A pointer to the #JGT_KeyEvent structure holding
 *                   the generated event information.
 *   @return         The processing result is returned.
 *   
 *   When a key event is notified to a textbox in Focused (#JG_COM_STATE_FOCUSED) state,
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
 * @see JginTextBoxSetPreKeyEvtHandler()
 * @see JG_KEY_RES_SET_ACTIVE
 */
JKUint32 JginTextBoxDefaultPreKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the textbox key event handler.
 * 
 * @param handler
 *        The key event handler to be set
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is  #JK_NULL.</li>
 *   </ul>
 */
void JginTextBoxSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 * The textbox default key event handler
 * 
 * @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated 
 *        event information
 * @return
 *        The processing result is returned.
 * 
 * The textbox default key event handler performs the following event 
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 * <dt> #AM_KEYCODE_SELECT </dt>
 * <dd>
 *     <dl>
 *     <dt> #AM_EVENT_KEY_CLICKED </dt>
 *     <dd>[When the focus policy is User input occupied type]<br>
 *         Sets the state to Focused state and issues a component event #JG_COM_EVT_STATE_CHANGED.<br><br>
 *         [When the focus policy is User input not occupied type]<br>
 *         No operation</dd>
 *     </dl>
 * </dd>
 * <dt>AM_KEYCODE_UP, AM_KEYCODE_DOWN</dt>
 * <dd>
 *     <dl>
 *     <dt> #AM_EVENT_KEY_CLICKED </dt>
 *     <dd>Returns 0 as the return value.</dd>
 *     </dl>
 * </dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_KeyEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginTextBoxDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the textbox pointing device event handler.
 * 
 * @param handler
 *        The pointing device event handler to be set
 * 
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 */
void JginTextBoxSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 * The textbox default pointing device event handler.
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
 *   The textbox default pointing event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *    <dt> #AM_EVENT_POINTER_CLICKED </dt>
 *    <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *      <dl>
 *        <dt>If the textbox state is #JG_COM_STATE_FOCUSED, </dt>
 *        <dd>If the pointing device pointer coordinates is in the textbox,
 *            sets #JG_COM_STATE_ACTIVE as the state. </dd>
 *      </dl>
 *    </dd>
 *   </dl>
 */
JKUint32 JginTextBoxDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/**
 *   @deprecated
 *   This function is due to be abolished, and has been replaced by #JginComSetTruncateMode().
 *   Use of this function is not recommended.
 */
void JginTextBoxSetTruncateMode(JGTextBox textbox, JKBool truncate);

/**
 *                Scrolls text vertically.
 * @param textbox The textbox handle.
 * @param offset  Scroll amount in pixels. 
 *                A positive value means scrolling downwards; 
 *                a negative value means scrolling upwards.
 * @return        #JK_TRUE, if scroll has been occured.
 *                #JK_FALSE, if the text display position has already reached 
 *                the begininng/end of text and scroll has not occured.
 *
 * This function draws the textbox after scrolling it from current position 
 * for the pixels designated in the offset parameter.
 * 
 * Scroll operation is available only when the truncate mode of the
 * textbox is #JK_FALSE
 * (the string needs to be folded and shown in multiple lines).
 * The figure below shows the scroll operation.
 *
 * @image html JginTextBoxScrollVertical_en.gif
 *
 * When this function is called in the key event handler for the textbox 
 * in Focused state, and the function has performed the scroll, the handler 
 * should return #JG_KEY_RES_KEEP_FOCUS to avoid focus movement between 
 * components.
 * If the text display position has already reached the begininng or end 
 * of text and scroll has not been perfromed, the handler should return 0.
 * This causes JBlend to perform focus movement to the next component.
 */
JKBool JginTextBoxScrollVertical(JGTextBox textbox, JKSint32 offset);


/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_TEXTBOX_H */

