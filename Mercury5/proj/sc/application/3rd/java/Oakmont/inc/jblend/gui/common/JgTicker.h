/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Functions for modifying ticker component properties.
 */

#ifndef ___GUI_COMMON_TICKER_H
#define ___GUI_COMMON_TICKER_H

#include <JkTypes.h>

#include <gui/common/JgGUIEvent.h>
#include <gui/common/JgString.h>
#include <gui/common/JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Ticker
 * @{
 */

/**
 * @internal
 * The maximum GUI ticker event value
 */
#define JG_GUI_TKR_EVT_END              (JG_GUI_EVT_END + 0x00)

/**
 * The ticker component type
 * 
 * @see JgComGetComponentType
 */
#define JG_TICKER   4

/**
 * The ticker handle
 * 
 * A ticker handle is data identifying the ticker.<br>
 * The ticker handle can be used as a component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGTicker;

/**
 *   The ticker scroll direction: Right to left
 */
#define JG_TKR_SCROLL_RTL   0

/**
 *   The ticker scroll direction: Left to right
 */
#define JG_TKR_SCROLL_LTR   1

/**
 * Gets the ticker text.
 * 
 * @param ticker
 *        The ticker handle
 * 
 * @return
 *        A handle is returned indicating a string with the ticker text. If 
 *        none is set, JK_INVALID_HANDLE is returned.
 * 
 * The obtained text must not be discarded. It is disposed of by the 
 * GUI Toolkit.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When ticker is an illegal handle.</li>
 *   </ul>
 */
JGString JgTickerGetText(JGTicker ticker);

/**
 * Gets the drawing position inside the ticker.
 * 
 * @param ticker
 *        The ticker handle
 * @return
 *        The internal drawing position is returned.
 * 
 * The internal drawing position is the position for drawing text in the ticker. 
 * It is given as the offset, in pixels, from the left edge of the drawing area. 
 * 
 * @see JginTickerSetPosition()
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When ticker is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgTickerGetPosition(JGTicker ticker);

/**
 *   Gets the direction of text scrolling in the ticker.
 * 
 *   @param ticker
 *        The ticker handle
 *   @return
 *        Either of the following is returned as the scrolling direction.
 *        <br><br>
 *        <ul>
 *         <li> #JG_TKR_SCROLL_RTL
 *         <li> #JG_TKR_SCROLL_LTR
 *        </ul>
 * 
 *   <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When ticker is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginTickerSetDirection()
 */
JKUint32 JgTickerGetDirection(JGTicker ticker);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_TICKER_H */

