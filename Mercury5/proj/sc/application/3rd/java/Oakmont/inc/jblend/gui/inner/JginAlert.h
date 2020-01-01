/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file 
 *   Functions for modifying alert component properties.
 */

#ifndef ___GUI_INNER_ALERT_H
#define ___GUI_INNER_ALERT_H

#include <JkTypes.h>

#include <JkImage.h>
#include <JkOffScreen.h>
#include <JkGraphics.h>
#include <JkVideoComponent.h>

#include <gui/common/JgString.h>
#include <gui/common/JgGauge.h>
#include <gui/common/JgTicker.h>
#include <gui/common/JgContainer.h>
#include <gui/common/JgAlert.h>
#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>
#include <gui/inner/JginContainer.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Alert
 * @{
 */

/**
 *   An alert was created.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKUint32 Additional information about the alert creation
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_CREATED          (JG_CONT_EVT_END + 0x01)

/**
 *   An alert is being deleted.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_DELETING         (JG_CONT_EVT_END + 0x02)

/**
 *   The alert type was set.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return 
 *   @return Return 0 if it succeeds.
 *           Return -1 when memory is insufficient.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_TYPE_CHANGED     (JG_CONT_EVT_END + 0x03)

/**
 *   An alert message text string was set.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JGString The newly set message text string
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_MSG_CHANGED      (JG_CONT_EVT_END + 0x04)

/**
 *   An alert title was set.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JGString The newly set title
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_TITLE_TXT_CHANGED    (JG_CONT_EVT_END + 0x05)

/**
 *   An alert immutable image was set.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKImageHandle The handle indicating the newly set immutable image
 *   @param param2 #JKImageHandle The handle indicating the previous immutable image
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_IMAGE_CHANGED            (JG_CONT_EVT_END + 0x06)

/**
 *   An alert off-screen image was set.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKOffScreenHandle The handle indicating the newly set off-screen image 
 *   @param param2 #JKOffScreenHandle The handle indicating the previous off-screen image 
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_OFFSCREENIMAGE_CHANGED   (JG_CONT_EVT_END + 0x07)

/**
 *   An alert gauge was set. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JGGauge The handle of the newly set gauge
 *   @param param2 #JGGauge The handle of the previously set gauge
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_GAUGE_CHANGED        (JG_CONT_EVT_END + 0x08)

/**
 *   An alert ticker was set. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JGGauge The handle of the newly set ticker
 *   @param param2 #JGGauge The handle of the previously set ticker
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_ALT_EVT_TICKER_CHANGED       (JG_CONT_EVT_END + 0x09)

/**
 *   The alert viewport width was requested. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return the viewport width. 
 * 
 * @see JGT_ComEvent::type
 * @see JgAlertGetViewPortWidth()
 */
#define JG_ALT_EVT_GET_VIEW_PORT_WIDTH      (JG_CONT_EVT_END + 0x0a)

/**
 *   The alert viewport height was requested. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return the viewport height. 
 * 
 * @see JGT_ComEvent::type
 * @see JgAlertGetViewPortHeight()
 */
#define JG_ALT_EVT_GET_VIEW_PORT_HEIGHT     (JG_CONT_EVT_END + 0x0b)

/**
 *   The alert client width was requested. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return the client width. 
 * 
 * @see JGT_ComEvent::type
 * @see JgAlertGetClientWidth()
 */
#define JG_ALT_EVT_GET_CLIENT_WIDTH         (JG_CONT_EVT_END + 0x0c)

/**
 *   The alert client height was requested. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return the client height. 
 * 
 * @see JGT_ComEvent::type
 * @see JgAlertGetClientHeight()
 */
#define JG_ALT_EVT_GET_CLIENT_HEIGHT        (JG_CONT_EVT_END + 0x0d)

/**
 *   The x coordinate of the alert view was requested. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return the view x coordinate. 
 * 
 * @see JGT_ComEvent::type
 * @see JgAlertGetViewX()
 */
#define JG_ALT_EVT_GET_VIEW_X               (JG_CONT_EVT_END + 0x0e)

/**
 *   The y coordinate of the alert view was requested. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return the view y coordinate. 
 * 
 * @see JGT_ComEvent::type
 * @see JgAlertGetViewY()
 */
#define JG_ALT_EVT_GET_VIEW_Y               (JG_CONT_EVT_END + 0x0f)

/**
 * @internal
 *   The maximum value for component event definitions for the alert.
 */
#define JG_ALT_EVT_END                      (JG_CONT_EVT_END + 0x0f)

/**
 *   Draws the inner content of the alert.
 *
 *   @param alert     The alert handle.
 *   @param g          The graphics context handle.
 *
 *   This function draws the inner content of the alert using the graphics
 *   context designated in the <i>g</i> parameter.
 *   This function usees a clip region which is the intersection of the graphics 
 *   context clip region and the inner content.
 *   The drawing position of the inner content is determined based on the alert coordinates 
 *   and the inset values. 
 *   
 *   When calling this function, set the same clip region to the graphics 
 *   context as the clip region which has been set for the graphics context 
 *   when a #JG_COM_EVT_PAINT event was notified.
 * 
 * @see JginComSetInsets()
 * @see JgComGetInsetTop()
 * @see JgComGetInsetLeft()
 * @see JgComGetInsetRight()
 * @see JgComGetInsetBottom()
 */
void JginAlertPaintContent(JGAlert alert, JKGraphicsContext g);

/**
 *   Sets the alert component event handler.
 *   
 *   @param type The corresponding event type
 *   @param handler The component event handler to be set
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>type</i> is an illegal value.</li>
 *     <li>When <i>handler</i> is #JK_NULL.</li>
 *   </ul>
 */
void JginAlertSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 *   The alert default component event handler.
 *   
 *   @param comEvent pointer to the #JGT_ComEvent structure holding the generated event information.
 *   @return The processing result is returned.
 *   
 *   The alert default component event handler performs the following event processing. 
 *   If this processing is to be performed when the corresponding event is processed in the native system, 
 *   pass the event to this function in the event handler implemented for the native system. 
 
 *   <dl>
 *     <dt> #JG_ALT_EVT_CREATED, #JG_ALT_EVT_TITLE_TXT_CHANGED,
 *          #JG_ALT_EVT_DELETING, #JG_ALT_EVT_TYPE_CHANGED </dt>
 *       <dd>No operation. </dd>
 *  
 *     <dt> #JG_ALT_EVT_MSG_CHANGED </dt>
 *       <dd> Notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *     <dt> #JG_ALT_EVT_GET_VIEW_PORT_WIDTH, #JG_ALT_EVT_GET_VIEW_PORT_HEIGHT </dt>
 *       <dd> Returns the viewport size. </dd>
 *  
 *     <dt> #JG_ALT_EVT_GET_CLIENT_WIDTH, #JG_ALT_EVT_GET_CLIENT_HEIGHT </dt>
 *       <dd> Returns the client size. </dd>
 *  
 *     <dt> #JG_ALT_EVT_GET_VIEW_X, #JG_ALT_EVT_GET_VIEW_Y </dt>
 *       <dd> Returns the view coordinates.</dd>
 *  
 *     <dt> #JG_COM_EVT_MOVED </dt>
 *       <dd> Changes the position of the alert JGTicker, JGTitle or JGGauge. </dd>
 *  
 *     <dt> #JG_COM_EVT_SIZE_CHANGED </dt>
 *       <dd> Adjusts the screen layout and notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend. </dd>
 *  
 *     <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *       <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *     <dt> #JG_COM_EVT_PAINT </dt>
 *       <dd>Draws an alert. </dd>
 *  
 *     <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *       <dd>Returns the preferred height for the designated width. </dd>
 *  
 *     <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT </dt>
 *       <dd>Returns the preferred width for the designated height. </dd>
 *  
 *     <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT </dt>
 *       <dd>Returns the preferred size of the alert default design.  </dd>
 *  
 *     <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *       <dd>Returns the minimum size of the alert default design. </dd>
 *  
 *     <dt>Other events </dt>
 *       <dd>If the alert content has changed and the display state is Shown,
 *           notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend. </dd>
 *   </dl>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li> When the value set in <i>component</i> member of the #JGT_ComEvent structure is an illegal handle. </li>
 *   </ul>
 */
JKUint32 JginAlertDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 *   Sets the alert key event handler.
 *   
 *   @param handler The key event handler to be set.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>handler</i> is #JK_NULL.</li>
 *   </ul>
 */
void JginAlertSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 *   The default key event handler for the alert. 
 *   
 *   @param keyEvent A pointer to the #JGT_KeyEvent structure holding the generated event information.
 *   @return The processing result is returned.
 *   
 *   The alert default key event handler performs the following event processing. 
 *   If this processing is to be performed when the corresponding event is processed in the native system event handler,
 *   pass the event to this function in the event handler implemented for the native system. 
 *   
 *   <dl>
 *     <dt> #AM_KEYCODE_UP, #AM_KEYCODE_DOWN </dt>
 *     <dd>
 *        <dl>
 *           <dt> #AM_EVENT_KEY_CLICKED, #AM_EVENT_KEY_REPEATED </dt>
 *           <dd>Scrolls the alert. <br>
 *        </dl>
 *     </dd>
 *   </dl>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When the value set in <i>component</i> member of the #JGT_KeyEvent structure is an illegal handle</li>
 *   </ul>
 */
JKUint32 JginAlertDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 *   Sets the alert pointing device event handler.
 *   
 *   @param handler The pointing device event handler to be set.
 *   
 *    This is functional only when the target device and the JBlend JVM library support pointing device.
 *    Otherwise, this function does not perform any action.
 */
void JginAlertSetPointerEvtHandler(JGT_PointerEvtHandler handler);

/**
 *   The default pointing device handler for the alert.
 *   
 *   @param pointerEvent A pointer to the #JGT_PointerEvent structure
 *                       holding the generated event information
 *   @return The processing result is returned.
 *   
 *    This function is provided for future extension. 
 *    It does not perform any action currently.
 *    
 */
JKUint32 JginAlertDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);


/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_ALERT_H */

