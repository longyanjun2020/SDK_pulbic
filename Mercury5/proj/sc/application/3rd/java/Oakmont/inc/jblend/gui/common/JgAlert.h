/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   Common API functions for alert component.
 */

#ifndef ___GUI_COMMON_ALERT_H
#define ___GUI_COMMON_ALERT_H

#include <JkTypes.h>
#include <JkImage.h>
#include <JkOffScreen.h>

#include <gui/common/JgString.h>
#include <gui/common/JgTicker.h>
#include <gui/common/JgGauge.h>
#include <gui/common/JgContainer.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Alert
 * @{
 */

/**
 * @internal
 *   The maximum GUI alert event value.
 */
#define JG_GUI_ALT_EVT_END              (JG_GUI_CONT_EVT_END + 0x00)

/**
 *   The alert component type.
 * 
 * @see JgComGetComponentType
 */
#define JG_ALERT       20


/**
 *   The alert handle.
 *   
 *   An alert handle is data identifying the alert.<br>
 *   The alert handle can be used as a component handle or
 *   container handle.
 * 
 * @see JGCom
 * @see JGContainer
 */
typedef JGContainer     JGAlert;

/**
 *   Alert type: Type not set
 * 
 * @see JgAlertGetType
 */
#define JG_ALT_TYPE_NULL            0

/**
 *   Alert type: Information alert.
 * 
 * @see JgAlertGetType
 */
#define JG_ALT_TYPE_INFO            1

/**
 *   Alert type: Warning alert.
 * 
 * @see JgAlertGetType
 */
#define JG_ALT_TYPE_WARNING         2

/**
 *   Alert type: Error alert.
 * 
 * @see JgAlertGetType
 */
#define JG_ALT_TYPE_ERROR           3

/**
 *   Alert type: Alarm alert.
 * 
 * @see JgAlertGetType
 */
#define JG_ALT_TYPE_ALARM           4

/**
 *   Alert type: Confirmation alert.
 * 
 * @see JgAlertGetType
 */
#define JG_ALT_TYPE_CONFIRMATION    5

/**
 *   The alert image type: Immutable image
 */
#define JG_ALT_IMAGE_TYPE_IMMUTABLE     0

/**
 *   The alert image type: off-screen image.
 */
#define JG_ALT_IMAGE_TYPE_OFFSCREEN     1

/**
 *   Gets the type of the alert.
 *   
 *   @param alert The alert handle.
 *   @return The type of the alert.
 *           One of the following is returned.
 *           <ul>
 *            <li> #JG_ALT_TYPE_NULL
 *            <li> #JG_ALT_TYPE_INFO
 *            <li> #JG_ALT_TYPE_WARNING 
 *            <li> #JG_ALT_TYPE_ERROR 
 *            <li> #JG_ALT_TYPE_ALARM
 *            <li> #JG_ALT_TYPE_CONFIRMATION 
 *           </ul>
 *   <p>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 * @see JG_ALT_TYPE_INFO
 * @see JG_ALT_TYPE_WARNING
 * @see JG_ALT_TYPE_ERROR
 * @see JG_ALT_TYPE_ALARM
 * @see JG_ALT_TYPE_CONFIRMATION
 */
JKUint32 JgAlertGetType(JGAlert alert);

/**
 *   Gets the width of the alert client. 
 *   
 *   @param alert The alert handle.
 *   @return The width of the alert client is returned. 
 *   
 *   This function returns the width of the alert as deployed in logical space coordinates. 
 *   Calling this function raises a #JG_ALT_EVT_GET_CLIENT_WIDTH event.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 * @see JG_ALT_EVT_GET_CLIENT_WIDTH
 * @see JgAlertGetClientHeight()
 */
JKSint32 JgAlertGetClientWidth(JGAlert alert);

/**
 *   Gets the height of the alert client. 
 *   
 *   @param alert The alert handle.
 *   @return The height of the alert client is returned. 
 *   
 *   This function returns the height of the alert as deployed in logical space coordinates. 
 *   Calling this function raises a #JG_ALT_EVT_GET_CLIENT_HEIGHT event.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 * @see JG_ALT_EVT_GET_CLIENT_HEIGHT
 * @see JgAlertGetClientWidth()
 */
JKSint32 JgAlertGetClientHeight(JGAlert alert);

/**
 *   Gets the x coordinate of the alert view. 
 *   
 *   @param alert The alert handle.
 *   @return The x coordinate of the alert view is returned. 
 *   
 *   This function returns the x coordinate of the view on the client. 
 *   Calling this function raises a #JG_ALT_EVT_GET_VIEW_X event.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 * @see JG_ALT_EVT_GET_VIEW_X
 * @see JgAlertGetViewY()
 */
JKSint32 JgAlertGetViewX(JGAlert alert);

/**
 *   Gets the y coordinate of the alert view. 
 *   
 *   @param alert The alert handle.
 *   @return The y coordinate of the alert view is returned. 
 *   
 *   This function returns the y coordinate of the view on the client. 
 *   Calling this function raises a #JG_ALT_EVT_GET_VIEW_Y event.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 * @see JG_ALT_EVT_GET_VIEW_Y
 * @see JgAlertGetViewX()
 */
JKSint32 JgAlertGetViewY(JGAlert alert);

/**
 *   Gets the alert viewport width. 
 *   
 *   @param alert The alert handle.
 *   @return The alert viewport width is returned. 
 *   
 *   This function returns the width of the alert as actually displayed on the screen. 
 *   Calling this function raises a #JG_ALT_EVT_GET_VIEW_PORT_WIDTH event.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 * @see JG_ALT_EVT_GET_VIEW_PORT_WIDTH
 * @see JgAlertGetViewPortHeight()
 */
JKSint32 JgAlertGetViewPortWidth(JGAlert alert);

/**
 *   Gets the alert viewport height. 
 *   
 *   @param alert The alert handle.
 *   @return The alert viewport height is returned. 
 *   
 *   This function returns the height of the alert as actually displayed on the screen. 
 *   Calling this function raises a #JG_ALT_EVT_GET_VIEW_PORT_HEIGHT event.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 * @see JG_ALT_EVT_GET_VIEW_PORT_HEIGHT
 * @see JgAlertGetViewPortWidth()
 */
JKSint32 JgAlertGetViewPortHeight(JGAlert alert);

/**
 *   Gets the alert label text string.
 *   
 *   @param alert The alert handle
 *   @return A handle is returned indicating a string with the alert title text.
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   Do not discard the text string obtained by this function.
 *   The GUI Toolkit handles string disposal.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 */
JGString JgAlertGetTitleText(JGAlert alert);

/**
 *   Gets the ticker set in the alert. 
 *   
 *   @param alert The alert handle
 *   @return The handle indicating the ticker set in the alert is returned. 
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 */
JGTicker JgAlertGetTicker(JGAlert alert);

/**
 *   Gets the alert message text string.
 *   
 *   @param alert The alert handle
 *   @return A handle is returned indicating a string with the alert message text.
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   Do not discard the text string obtained by this function.
 *   The GUI Toolkit handles string disposal.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 */
JGString JgAlertGetMessage(JGAlert alert);

/**
 *   Gets the image type of the alert.
 *   
 *   @param  alert The alert handle.
 *   @return  One of the following is returned as the type of the image which has been set to the alert.
 *           <ul>
 *             <li> #JG_ALT_IMAGE_TYPE_IMMUTABLE </li>
 *             <li> #JG_ALT_IMAGE_TYPE_OFFSCREEN </li>
 *           </ul>
 *   <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgAlertGetImageType(JGAlert alert);

/**
 *   Gets the immutable image set in the alert.
 *   
 *   @param  alert The alert handle.
 *   @return A handle indicating the immutable image set in the alert is returned. 
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 */
JKImageHandle JgAlertGetImage(JGAlert alert);

/**
 *   Gets the off-screen image set in the alert.
 *   
 *   @param  alert The alert handle.
 *   @return A handle indicating the off-screen image set in the alert is returned. 
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 */
JKOffScreenHandle JgAlertGetOffScreenImage(JGAlert alert);

/**
 *   Gets the gauge set in the alert. 
 *   
 *   @param  alert The alert handle.
 *   @return The handle indicating the gauge set in the alert is returned. 
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>alert</i> is an illegal handle.</li>
 *   </ul>
 */
JGGauge JgAlertGetGauge(JGAlert alert);


/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_ALERT_H */

