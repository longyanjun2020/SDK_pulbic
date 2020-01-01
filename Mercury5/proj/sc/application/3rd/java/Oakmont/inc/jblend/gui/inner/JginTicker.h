/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying ticker properties.
 */

#ifndef ___GUI_INNER_TICKER_H
#define ___GUI_INNER_TICKER_H

#include <JkTypes.h>

#include <JkGraphics.h>
#include <JkVideoComponent.h>

#include <gui/common/JgString.h>
#include <gui/common/JgCom.h>
#include <gui/common/JgTicker.h>
#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Ticker
 * @{
 */

/**
 *   The color of the Ticker border.
 *   
 *   This is used for designating the attribute when Ticker default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginTickerSetStaticAttribute().
 */
#define JG_TKR_ATTR_BORDER_COLOR      (0x01)

/**
 * A ticker was created.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 Additional information about the ticker creation
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
#define JG_TKR_EVT_CREATED              (JG_COM_EVT_END + 0x01)

/**
 * A ticker is being deleted.
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
#define JG_TKR_EVT_DELETING             (JG_COM_EVT_END + 0x02)

/**
 * The ticker text was set.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        #JGString The text that was set
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
#define JG_TKR_EVT_TEXT_CHANGED         (JG_COM_EVT_END + 0x03)

/**
 * There is a ticker update request.
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
#define JG_TKR_EVT_REQUEST_UPDATE       (JG_COM_EVT_END + 0x04)

/**
 * The ticker was updated.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *               JKSint32 The new internal drawing position (component coordinates)
 * @param param2
 *               JKSint32 The old internal drawing position (component coordinates)
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
#define JG_TKR_EVT_POSITION_CHANGED     (JG_COM_EVT_END + 0x05)

/**
 *   The ticker scroll direction changed.
 *
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 #JKUint32
 *               The new scroll direction
 *   @param param2 #JKUint32
 *               The previous scroll direction
 *   @param param3 -
 *   @param param4 -
 *   @return
 *         Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_TKR_EVT_DIRECTION_CHANGED    (JG_COM_EVT_END + 0x06)

/**
 * @internal
 * The maximum valid component event value for the ticker.
 */
#define JG_TKR_EVT_END                  (JG_COM_EVT_END + 0x06)

/**
 *   Sets a Ticker element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all ticker instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter indicating GUI component attributes.
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
 *           Following constants indicating attribute.<br>
 *            #JG_TKR_ATTR_BORDER_COLOR 
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
void JginTickerSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 * Sets the ticker internal drawing position.
 * 
 * @param ticker
 *        The ticker handle.
 * @param position
 *        The internal drawing position to be set
 * 
 * The internal drawing position is the position for drawing text in the
 * ticker. It is given as the offset, in pixels, from the left edge of the
 * drawing area.
 * 
 * @see JgTickerGetPosition()
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When ticker is an illegal handle.</li>
 *   </ul>
 */
void JginTickerSetPosition(JGTicker ticker, JKSint32 position);

/**
 *   Sets the ticker scroll direction.
 * 
 *   @param ticker
 *        The ticker handle.
 *   @param direction
 *        The scroll direction. Designate either of the following values.
 * <br><br>
 * <ul>
 *  <li> #JG_TKR_SCROLL_RTL
 *  <li> #JG_TKR_SCROLL_LTR
 * </ul>
 * 
 * <p>
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When ticker is an illegal handle.</li>
 *    <li>When direction is an illegal value.</li>
 *   </ul>
 * 
 * @see JgTickerGetDirection()
 */
void JginTickerSetDirection(JGTicker ticker, JKUint32 direction);

/**
 * Draws the inner content of a ticker.
 *
 * @param ticker     The ticker handle.
 * @param g          The graphics context handle.
 * @param dx         The x-direction offset of inner content drawing position.
 * @param dy         The y-direction offset of inner content drawing position.
 * @param foreground The foreground color.
 *
 * This function draws the inner content of the ticker using the graphics
 * context designated in the g parameter.
 * This function usees a clip region which is the intersection of the graphics 
 * context clip region and the inner content.
 * The drawing position of the inner content is determined based on the 
 * ticker coordinates and the inset values.
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
void JginTickerPaintContent(JGTicker ticker, JKGraphicsContext g,
                            JKSint32 dx, JKSint32 dy, JKColor foreground);

/**
 * Sets the ticker component event handler.
 * 
 * @param type
 *        The corresponding event type
 * @param handler
 *        The component event handler
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When type is an illegal value.</li>
 *    <li>When handler is  #JK_NULL.</li>
 *   </ul>
 */
void JginTickerSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 * The default component event handler for the ticker.
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information.
 * 
 * @return
 *        The processing result is returned.
 * 
 * The ticker default component event handler performs the following event 
 * processing.
 * If this processing is to be performed when the corresponding event is
 * processed in the native system, pass the event to this function in the event 
 * handler implemented for the native system.
 * <dl>
 *  <dt> #JG_TKR_EVT_CREATED, #JG_TKR_EVT_DELETING</dt>
 *  <dd>No operation.</dd>
 * 
 *  <dt> #JG_TKR_EVT_TEXT_CHANGED , #JG_COM_EVT_FONT_CHANGED </dt>
 *  <dd>Resets the ticker internal drawing position and changes the preferred size and minimum size. 
 *      If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * 
 *  <dt> #JG_TKR_EVT_REQUEST_UPDATE</dt>
 *  <dd>Updates the ticker internal drawing position, and if the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * 
 *  <dt> #JG_TKR_EVT_POSITION_CHANGED</dt>
 *  <dd>If the ticker display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * 
 *  <dt> #JG_TKR_EVT_DIRECTION_CHANGED</dt>
 *  <dd>No operation.</dd>
 * 
 *  <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *  <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 * 
 *  <dt> #JG_COM_EVT_PAINT</dt>
 *  <dd>Draws the ticker.</dd>
 * 
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT,
 *       #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *  <dd>Return the preferred size (width, height) set in the ticker as the return value.</dd>
 * 
 *  <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *    <dd>Returns the preferred size of the ticker default design.</dd>
 * 
 *  <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *    <dd>Returns the minimum size of the ticker default design.</dd>
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
 *          <td>Ticker text flow </td>
 *          <td> #JG_TKR_SCROLL_RTL </td>
 *          <td> #JG_TKR_SCROLL_LTR </td>
 *        </tr>
 *      </table>
 *  </dd>
 *
 *  <dt>Other events</dt>
 *  <dd>If the ticker content changed and the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 * </dl>
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginTickerDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_TICKER_H */

