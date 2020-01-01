/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file 
 * Functions for modifying button component properties.
 */

#ifndef ___GUI_INNER_BUTTON_H
#define ___GUI_INNER_BUTTON_H

#include <JkTypes.h>

#include <JkImage.h>
#include <JkOffScreen.h>
#include <JkGraphics.h>
#include <JkVideoComponent.h>

#include <gui/common/JgString.h>
#include <gui/common/JgCom.h>
#include <gui/common/JgButton.h>
#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Button
 * @{
 */

/**
 *   The button state designated when button default design is changed: Pressed and Active
 *   
 *   This is used for designating the button state when button default design is changed.
 *   This constant and the constant representing the GUI component attribute are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 *  
 *   This constant is used to designate pressed state along with active state. 
 *   #JG_COM_ATTR_STATE_ACTIVE is used to designate released state along with active state.
 */
#define JG_BTN_ATTR_STATE_PRESSED      (0x010000)

/**
 *   The line type of the border indicating button focus frame.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_FOCUS_LINE        (0x01)

/**
 *   The color of the border indicating button focus frame.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_FOCUS_LINE_COLOR          (0x02)

/**
 *   The color of the button "foreground" element.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_FOREGROUND     (0x03)

/**
 *   The color of the button "background" element.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_BACKGROUND     (0x04)

/**
 *   The color of the upper left of button border.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_LT_BORDER_COLOR     (0x05)

/**
 *   The color of the outside lower right of button border.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_OUTER_RB_BORDER_COLOR     (0x06)

/**
 *   The color of the inside lower right of button border.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_INNER_RB_BORDER_COLOR     (0x07)

/**
 *   The color of the outside upper left of button border.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_OUTER_LT_BORDER_COLOR     (0x08)

/**
 *   The color of the inside upper left of button border.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_INNER_LT_BORDER_COLOR     (0x09)

/**
 *   The color of the lower right of button border.
 *   
 *   This is used for designating the attribute when button default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginButtonSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_BTN_ATTR_RB_BORDER_COLOR     (0x0A)

/**
 * A button was created.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 Additional information about the button creation
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
#define JG_BTN_EVT_CREATED             (JG_COM_EVT_END + 0x01)

/**
 * A button is being deleted.
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
 *
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_BTN_EVT_DELETING             (JG_COM_EVT_END + 0x02)

/**
 * A button label text string was set.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *         JGString The set text string
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
#define JG_BTN_EVT_TEXT_CHANGED         (JG_COM_EVT_END + 0x03)

/**
 * The button immutable image changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        #JKImageHandle A handle indicating the newly set immutable image
 * @param param2
 *        #JKImageHandle A handle indicating the previous immutable image
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
#define JG_BTN_EVT_IMAGE_CHANGED        (JG_COM_EVT_END + 0x04)

/**
 * The button off-screen image changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        #JKOffScreenHandle A handle indicating the newly set off-screen image
 * @param param2
 *        #JKOffScreenHandle A handle indicating the previous off-screen image
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
#define JG_BTN_EVT_OFFSCREENIMAGE_CHANGED   (JG_COM_EVT_END + 0x05)

/**
 * The button pressed state changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *         JKBool The newly set pressed state
 * @param param2
 *         JKBool The previous pressed state
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
#define JG_BTN_EVT_PUSHED               (JG_COM_EVT_END + 0x06)

/**
 * @internal
 * The maximum value for component event definitions for the button.
 */
#define JG_BTN_EVT_END                  (JG_COM_EVT_END + 0x06)

/**
 *   Sets a button element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all button instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of 
 *   a constant indicating a GUI component attribute and a constant
 *   indicating button state. The constant indicating button state may
 *   designate one state or a combination of states. When a combination of
 *   states is designated, attributes for multiple states may be set at the
 *   same time.
 *   #JG_COM_ATTR_STATE_ACTIVE is used to designate released state along with active state.
 *   #JG_BTN_ATTR_STATE_PRESSED is used to designate pressed state along with active state.
 *   Attribute values are passed in <i>value1</i> and <i>value2</i>. A list of the
 *   parameters passed to this function is given below. 
 *   
 *   <table>
 *     <tr> 
 *       <td><b><i>type</i></b>
 *       <td><b><i>value1</i></b>
 *       <td><b><i>value2</i></b>
 *     </tr>
 *     <tr> 
 *       <td>[Line type of the focus frame]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_BTN_ATTR_FOCUS_LINE
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ACTIVE<br> #JG_BTN_ATTR_STATE_PRESSED
 *           </dl>
 *       <td>The line type. Designate one of the following: <br>
 *            #JG_COM_VAL_LINE_DOTTED<br>
 *            #JG_COM_VAL_LINE_SOLID<br>
 *            #JG_COM_VAL_LINE_NONE
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the focus frame]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_BTN_ATTR_FOCUS_LINE_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ACTIVE<br> #JG_BTN_ATTR_STATE_PRESSED
 *           </dl>
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND_SYNC
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the foreground]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_BTN_ATTR_FOREGROUND
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ACTIVE<br> #JG_BTN_ATTR_STATE_PRESSED
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
 *            <dd> #JG_BTN_ATTR_BACKGROUND
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ACTIVE<br> #JG_BTN_ATTR_STATE_PRESSED
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
 *            <dd> #JG_BTN_ATTR_LT_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br> #JG_COM_ATTR_STATE_ACTIVE
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
 *       <td>[Color of the outside lower right of border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_BTN_ATTR_OUTER_RB_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br> #JG_COM_ATTR_STATE_ACTIVE
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
 *       <td>[Color of the inside lower right of border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_BTN_ATTR_INNER_RB_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br> #JG_COM_ATTR_STATE_ACTIVE
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
 *            <dd> #JG_BTN_ATTR_OUTER_LT_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_BTN_ATTR_STATE_PRESSED
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
 *            <dd> #JG_BTN_ATTR_INNER_LT_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_BTN_ATTR_STATE_PRESSED
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
 *       <td>[Color of the lower right of border]<br>
 *           A combination of the following constants indicating attribute and state 
 *           <dl>
 *            <dt>Attribute
 *            <dd> #JG_BTN_ATTR_RB_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_BTN_ATTR_STATE_PRESSED
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
void JginButtonSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Sets the button pressed state.
 * 
 * @param button
 *        The button handle
 * @param pressed
 *        JK_TRUE for pressed state, else JK_FALSE
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When button is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgButtonIsPressed()
 */
void JginButtonSetPressed(JGButton button, JKBool pressed);

/**
 * Draws the inner content of a button.
 *
 * @param button     The button handle.
 * @param g          The graphics context handle.
 * @param dx         The x-direction offset of inner content drawing position.
 * @param dy         The y-direction offset of inner content drawing position.
 * @param foreground The foreground color.
 *
 * This function draws the inner content of the button using the graphics
 * context designated in the g parameter.
 * This function usees a clip region which is the intersection of the graphics 
 * context clip region and the inner content.
 * The drawing position of the inner content is determined based on the 
 * button coordinates and the inset values.
 *   
 * The inner content drawing position can be adjusted by setting non-zero values 
 * to the dx and dy parameters.
 *   
 * When calling this function, set the same clip region to the graphics 
 * context as the clip region which has been set for the graphics context 
 * when a JG_COM_EVT_PAINT event was notified.
 * 
 * @see JginComSetInsets()
 * @see JgComGetInsetTop()
 * @see JgComGetInsetLeft()
 * @see JgComGetInsetRight()
 * @see JgComGetInsetBottom()
 */
void JginButtonPaintContent(JGButton button, JKGraphicsContext g,
                            JKSint32 dx, JKSint32 dy, JKColor foreground);

/**
 * Sets the button component event handler.
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
void JginButtonSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 * The default component event handler for the button.
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information.
 *
 * @return
 *        The processing result is returned.
 * 
 * The button default component event handler performs the following event
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system event handler, pass the event to this function 
 * in the event handler implemented for the native system.
 * <dl>
 *  <dt> #JG_BTN_EVT_CREATED, #JG_BTN_EVT_DELETING </dt>
 *  <dd>No operation</dd>
 *  
 *  <dt> #JG_BTN_EVT_TEXT_CHANGED, #JG_BTN_EVT_IMAGE_CHANGED,
 *       #JG_BTN_EVT_OFFSCREENIMAGE_CHANGED</dt>
 *  <dd>Changes the button preferred size and minimum size, and if the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *  <dt> #JG_BTN_EVT_PUSHED </dt>
 *  <dd>If the button display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend. </dd>
 *  
 *  <dt> #JG_COM_EVT_STATE_CHANGED </dt>
 *  <dd>
 *      [When the focus policy is User input occupied type]<br>
 *      If the button state has gone to Active state, notifies the GUI event #JG_GUI_EVT_OCCUPY_INPUT_EVENT to JBlend and occupies the user input event.<br>
 *      If the state has gone from Active to some other state, notifies the GUI event #JG_GUI_EVT_RELEASE_INPUT_EVENT to JBlend and releases the user input event.<br><br>
 *      [When the focus policy is User input not occupied type]<br>
 *      If the button has newly obtained focus (gone to Focused state from a state other than Active), sets the button state to Active state.
 *      If focus has been lost and if the target device supports pointer event notification, clears the pointing device clicked state.
 *  </dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *  <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *  <dt> #JG_COM_EVT_PAINT </dt>
 *  <dd>Draws a button</dd>
 *  
 *  <dt> #JG_COM_EVT_FONT_CHANGED </dt>
 *  <dd>Changes the button preferred size and minimum size <br>
 *      If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend. </dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *  <dd>Returns the preferred height for the designated width.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT </dt>
 *  <dd>Returns the preferred size (width) set for the button.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *  <dd>Returns the preferred size of the button default design.</dd>
 *  
 *  <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *  <dd>Returns the minimum size of the button default design.</dd>
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
 *  <dd>If the button content has changed and the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend. </dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginButtonDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 * Sets the button key event handler.
 * 
 * @param handler
 *        The key event handler to be set.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginButtonSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 * The default key event handler for the button.
 * 
 * @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated event 
 *        information.
 *
 * @return
 *        The processing result is returned.
 * 
 * The button default key event handler performs the following event processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system event handler, pass the event to this function 
 * in the event handler implemented for the native system.
 * <dl>
 * <dt> #AM_KEYCODE_SELECT </dt>
 * <dd>
 *     <dl>
 *     <dt> #AM_EVENT_KEY_PRESSED </dt>
 *     <dd>Sets the button pressed state to Pressed, and notifies the GUI event 
 *         #JG_GUI_BTN_EVT_PUSHED to JBlend.<br>
 *     </dl>
 *     <dl>
 *     <dt> #AM_EVENT_KEY_RELEASED </dt>
 *     <dd>Sets the button pressed state to Released, and notifies the GUI 
 *        event #JG_GUI_BTN_EVT_PUSHED to JBlend.<br>
 *     </dl>
 * </dd>
 * <dt> #AM_KEYCODE_UP, #AM_KEYCODE_DOWN, #AM_KEYCODE_RIGHT, #AM_KEYCODE_LEFT </dt>
 * <dd>
 *     <dl>
 *     <dt> #AM_EVENT_KEY_CLICKED, #AM_EVENT_KEY_REPEATED </dt>
 *     <dd>If the button state is Pressed state, returns #JG_KEY_RES_KEEP_FOCUS as the return value.<br>
 *         If the button state is Released state, returns 0 as the return value.</dd>
 *     </dl>
 * </dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_KeyEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginButtonDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 * Sets the button pointing device event handler.
 * 
 * @param handler
 *        The pointing device event handler to be set.
 * 
 *    This is functional only when the target device and the JBlend JVM library support pointing device.
 *    Otherwise, this function does not perform any action.
 * 
 */
void JginButtonSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 * The default pointing device handler for the button.
 * 
 * @param pointerEvent
 *        A pointer to the JGT_PointerEvent structure holding the generated 
 *        event information
 *
 * @return
 *        The processing result is returned.
 * 
 *   This is functional only when the target device and the JBlend JVM library support pointing device.
 *   Otherwise, this function does not perform any action.
 *   
 *   The button default pointing event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *     <dt> #AM_EVENT_POINTER_PRESSED </dt>
 *      <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs a button press processing.</dd>
 *     <dt> #AM_EVENT_POINTER_RELEASED </dt>
 *      <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs a button release processing.</dd>
 *     <dt> #JG_POINTER_EVT_ENTER </dt>
 *       <dd>If the button is being dragged, performs a button press processing.</dd>
 *     <dt> #JG_POINTER_EVT_EXIT </dt>
 *       <dd>If the button is being dragged, performs a button release processing.</dd>
 *   </dl>
 */
JKUint32 JginButtonDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_BUTTON_H */

