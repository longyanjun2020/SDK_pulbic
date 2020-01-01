/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   Functions for modifying popup list properties.
 */

#ifndef ___GUI_INNER_POPUPLIST_H
#define ___GUI_INNER_POPUPLIST_H

#include <JkTypes.h>

#include <JkGraphics.h>

#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>
#include <gui/inner/JginList.h>
#include <gui/common/JgPUList.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_PopupList
 * @{
 */

/**
 *   The structure type for holding the information of PUList bitmap icons.
 */
typedef struct JGT_PUListBmpData {
    /**
     *   Version of the structure. 
     *   
     *   Designate 1.
     */
    JKUint32 version;
    
    /**
     *   The initial address of the array holding ARGB-format data of bitmap icons.
     */
    const JKColor *bmp;
    
    /**
     *   The width of bitmap.
     */
    JKSint32 width;
    
    /**
     *   The height of bitmap.
     */
    JKSint32 height;
} JGT_PUListBmpData;

/**
 *   The color of the PUList outside border.
 *   
 *   This is used for designating the attribute when PUList default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginPUListSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The PUList border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot outermost rectangle of the border.
 */
#define JG_PULST_ATTR_OUTER_BORDER_COLOR      (0x01)

/**
 *   The color of the PUList inside border.
 *   
 *   This is used for designating the attribute when PUList default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginPUListSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   The PUList border is drawn with a width of 2 dots.
 *   This constant represents the color of the one-dot innermost rectangle of the border.
 */
#define JG_PULST_ATTR_INNER_BORDER_COLOR      (0x02)

/**
 *   The bitmap icon of the PUList.
 *   
 *   This is used for designating the attribute when PUList default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginPUListSetStaticAttribute().
 */
#define JG_PULST_ATTR_BMP               (0x03)

/**
 *   A PUList was created.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 JKUint32 Additional information about the PUList creation
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_PULST_EVT_CREATED            (JG_LST_EVT_END + 0x01)

/**
 *   A PUList is being deleted.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_PULST_EVT_DELETING            (JG_LST_EVT_END + 0x02)

/**
 * @internal
 *   The maximum valid component event value for the PUList.
 */
#define JG_PULST_EVT_END                 (JG_LST_EVT_END + 0x02)

/**
 *   Sets a PUList element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all PUList instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of a constant
 *   indicating GUI component attributes and a constant indicating GUI component state. 
 *   The constant indicating GUI component state may designate one state or a combination of states. 
 *   When a combination of states is designated, attributes for multiple states may be set at the
 *   same time
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
 *            <dd> #JG_PULST_ATTR_OUTER_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br>
 *                 #JG_COM_ATTR_STATE_FOCUSED
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
 *            <dd> #JG_PULST_ATTR_INNER_BORDER_COLOR
 *            <dt>State
 *            <dd> #JG_COM_ATTR_STATE_ENABLED<br>
 *                 #JG_COM_ATTR_STATE_FOCUSED
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
 *       <td>[Bitmap icon]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_PULST_ATTR_BMP
 *       <td>A pointer to the JGT_PUListBmpData structure for holding the information of list item bitmap icons.
 *       </td>
 *       <td>0
 *       </td>
 *     </tr>
 *   </table>
 *   
 *   In case #JG_PULST_ATTR_BMP is designated in the <i>type</i> parameter,
 *   the #JGT_PUListBmpData structure passed in the <i>value1</i> parameter needs not to be 
 *   retained after the completion of this function.
 *   However, the pointer to the ARGB-format data set in the <i>bmp</i> member of 
 *   #JGT_PUListBmpData structure must remain valid until the JVM terminates.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When <i>type</i> is an illegal value.</li>
 *    <li>When <i>value1</i> is an illegal value.</li>
 *    <li>When <i>value2</i> is an illegal value.</li>
 *   </ul>
 *   In case #JG_PULST_ATTR_BMP is designated in the <i>type</i> parameter, 
 *   @ref page_gui_trouble_shooting "Error" occurs in the following cases.<br>
 *   <ul>
 *     <li>When <i>value1</i> is #JK_NULL. </li>
 *     <li>When <i>value2</i> is othe than 0.</li>
 *     <li>When the <i>version</i> member of #JGT_PUListBmpData structure designated in the 
 *         <i>value1</i> parameter is other than 1.</li>
 *     <li>When the <i>bmp</i> member of #JGT_PUListBmpData structure designated in the 
 *         <i>value1</i> parameter is #JK_NULL.</li>
 *     <li>When the <i>width</i> member of #JGT_PUListBmpData structure designated in the 
 *         <i>value1</i> parameter is a negative value.</li>
 *     <li>When the <i>height</i> member of #JGT_PUListBmpData structure designated in the 
 *         <i>value1</i> parameter is a negative value.</li>
 *   </ul>
 */
void JginPUListSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Draws the inner content of a PUList.
 *
 * @param popuplist  The PUList handle.
 * @param g          The graphics context handle.
 *
 * This function draws the inner content of the PUList using the graphics
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
void JginPUListPaintContent(JGPopUpList popuplist, JKGraphicsContext g);

/**
 *   Sets the PUList component event handler.
 *   
 *   @param type 
 *        The corresponding event type
 *   @param handler 
 *        The component event handler to be set
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When type is an illegal value.</li>
 *    <li>When handler is  #JK_NULL.</li>
 *   </ul>
 */
void JginPUListSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 *   The default component event handler for the PUList.
 *   
 *   @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information.
 *   @return
 *        The processing result is returned.
 *   
 *   The PUList default component event handler performs the following event
 *   processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this 
 *   function in the event handler implemented for the native system.
 *   <dl>
 *   <dt> #JG_PULST_EVT_CREATED, #JG_PULST_EVT_DELETING</dt>
 *   <dd>No operation.</dd>
 *   
 *   <dt> #JG_LST_EVT_SELECTION_CHANGED</dt>
 *   <dd>If the PUList display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *   
 *   <dt> #JG_COM_EVT_STATE_CHANGED</dt>
 *   <dd>
 *       If the PUList state has gone to Active state, notifies the GUI 
 *       events #JG_GUI_EVT_OCCUPY_INPUT_EVENT and #JG_GUI_EVT_OCCUPY_SCREEN to 
 *       JBlend, and occupies the user input event and screen.
 *       After that, changes child PUListOpened to Active state.<br>
 *       If the state changed from Active to another state, notifies the GUI 
 *       events #JG_GUI_EVT_RELEASE_INPUT_EVENT and #JG_GUI_EVT_RELEASE_SCREEN 
 *       to JBlend, and releases the user input event and screen.</dd>
 *   
 *   <dt> #JG_LST_EVT_ITEM_TEXT_CHANGED, #JG_LST_EVT_ITEM_IMAGE_CHANGED, 
 *        #JG_LST_EVT_ITEM_OFFSCREEN_CHANGED, 
 *        #JG_LST_EVT_ITEM_FONT_CHANGED, #JG_LST_EVT_WRAP_POLICY_CHANGED </dt>
 *   <dd>Changes the PUList preferred size and minimum size.
 *       If the display state is Shown, notifies the GUI event 
 *       #JG_GUI_EVT_REPAINT to JBlend.<br>
 *       If the PUList is open, closes the PUList.
</dd>
 *   
 *   <dt> #JG_LST_EVT_ITEM_INSERTED, #JG_LST_EVT_ITEM_REMOVING </dt>
 *   <dd>If the PUList is open, closes the PUList.</dd>
 *   
 *   <dt> #JG_COM_EVT_FGCOLOR_CHANGED </dt>
 *   <dd>Changes the foreground color of the list items.<br>
 *       Sets the foreground color of PUListOpened to the same color and 
 *       notifies JBlend of the GUI event #JG_GUI_EVT_REPAINT.</dd>
 *   
 *   <dt> #JG_COM_EVT_BGCOLOR_CHANGED </dt>
 *   <dd>Sets the background color of PUListOpened to the same color and 
 *       notifies JBlend of the GUI event #JG_GUI_EVT_REPAINT.</dd>
 *   
 *   <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *    <dd>Returns the preferred height for the designated width. </dd>
 *   
 *   <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *   <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *   
 *   <dt> #JG_COM_EVT_PAINT</dt>
 *   <dd>Draws a PUList.</dd>
 *   
 *   <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT </dt>
 *    <dd>Returns the preferred size (width) set for the PUList.</dd>
 *   
 *   <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT</dt>
 *    <dd>Returns the preferred size of the PUlist default design.</dd>
 *   
 *   <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *    <dd>Returns the minimum size of the PUlist default design.</dd>
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
 *        <tr>
 *          <td>Inset value</td>
 *          <td>Icon display space is placed in the right side. </td>
 *          <td>Icon display space is placed in the left side. </td>
 *        </tr>
 *      </table>
 *  </dd>
 *
 *   <dt>Other events</dt>
 *   <dd>If the PUList content has changed and the display state is Shown, 
 *       notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *   </dl>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure 
 *        is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginPUListDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 *   Sets a key event handler for the PUList in Focused state.
 *
 *   @param handler The key event handler to be set
 *   
 *   This function sets the event handler that is to perform processing when
 *   a PUList in Focused state (#JG_COM_STATE_FOCUSED) receives a key event.
 *
 *   Based on the passed event, the handler should decide whether the 
 *   PUList needs to go to Active state (#JG_COM_STATE_ACTIVE).
 *   If a transition to Active state (#JG_COM_STATE_ACTIVE) is needed,
 *   return #JG_KEY_RES_SET_ACTIVE in the key event handler.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginPUListSetPreKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 *   The default key event handler for a PUList in Focused state
 *   ( #JG_COM_STATE_FOCUSED ).
 *
 *   @param keyEvent A pointer to the #JGT_KeyEvent structure holding
 *                   the generated event information.
 *   @return         The processing result is returned.
 *   
 *   When a key event is notified to a PUList in Focused (#JG_COM_STATE_FOCUSED) state,
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
 * @see JginPUListSetPreKeyEvtHandler()
 * @see JG_KEY_RES_SET_ACTIVE
 */
JKUint32 JginPUListDefaultPreKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 *   Sets the PUList key event handler.
 *   
 *   @param handler
 *        The key event handler to be set.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 * 
 */
void JginPUListSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 *   The default key event handler for the PUList.
 *   
 *   @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated event 
 *        information.
 *   @return
 *        The processing result is returned.
 *   
 *   The PUList default key event handler performs nothing.
 */
JKUint32 JginPUListDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 *   Sets the PUList pointing device event handler.
 *   
 *   @param handler The pointing device event handler to be set.
 *   
 *    This is functional only when the target device and the JBlend JVM library support pointing device.
 *    Otherwise, this function does not perform any action.
 * 
 */
void JginPUListSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 *   The default pointing device handler for the PUList.
 *   
 *   @param pointerEvent
 *        A pointer to the JGT_PointerEvent structure holding the generated 
 *        event information
 *   @return
 *        The processing result is returned.
 *   
 *    This is functional only when the target device and the JBlend JVM library support pointing device.
 *    Otherwise, this function does not perform any action.
 *   
 *    The PUList default pointing event handler performs the following event processing.
 *    If this processing is to be performed when the corresponding event is
 *    processed in the native system event handler, pass the event to this function 
 *    in the event handler implemented for the native system.
 *    <dl>
 *     <dt> #AM_EVENT_POINTER_CLICKED </dt>
 *     <dd>If the JGT_PointerEvent structure <i>buttonNo</i> member is 0, performs the following processing.
 *        <dl>
 *          <dt>If the PUList state is #JG_COM_STATE_FOCUSED, </dt>
 *          <dd>sets #JG_COM_STATE_ACTIVE as the state.</dd>
 *        </dl>
 *     </dd>
 *    </dl>
 * 
 */
JKUint32 JginPUListDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_POPUPLIST_H */

