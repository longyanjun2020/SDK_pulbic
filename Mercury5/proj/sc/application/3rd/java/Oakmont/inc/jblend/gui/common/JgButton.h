/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying button component properties.
 */

#ifndef ___GUI_COMMON_BUTTON_H
#define ___GUI_COMMON_BUTTON_H

#include <JkTypes.h>

#include <JkImage.h>
#include <JkOffScreen.h>

#include <gui/common/JgGUIEvent.h>
#include <gui/common/JgString.h>
#include <gui/common/JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Button
 * @{
 */

/**
 * The button pressed state changed.
 * 
 * When the button pressed state has changed, notify the event using 
 * #JginGUIEventPostEvent().
 * The values of the param members in the JGT_GUIEvent structure passed as an 
 * argument of JginGUIEventPostEvent() are as indicated in the following parameters. 
 *
 * @param param1
 *        JKBool The new pressed state
 * @param param2
 *        JKBool The previous state
 * @param param3 -
 * @param param4 -
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_BTN_EVT_PUSHED           (JG_GUI_EVT_END + 0x01)

/**
 * @internal
 * The maximum GUI button event value.
 */
#define JG_GUI_BTN_EVT_END              (JG_GUI_EVT_END + 0x01)

/**
 * The button component type.
 * 
 * @see JgComGetComponentType
 */
#define JG_BUTTON   1

/**
 * The button handle.
 * 
 * A button handle is data identifying the button.<br>
 * The button handle can be used as a component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGButton;

/**
 *   The type of content set in the button: Character string.
 * 
 * @see JgButtonGetContentType
 */
#define JG_BTN_CONTENT_TYPE_TEXT            0

/**
 *   The type of content set in the button: Immutable image.
 * 
 * @see JgButtonGetContentType
 */
#define JG_BTN_CONTENT_TYPE_IMMUTABLE       1

/**
 *   The type of content set in the button: Off-screen image.
 * 
 * @see JgButtonGetContentType
 */
#define JG_BTN_CONTENT_TYPE_OFFSCREEN       2

/**
 * Gets the content set in the button.
 * 
 * @param button
 *        The button handle
 * @return
 *         One of the following values is returned indicating the content type.
 *         <br><br>
 *         <ul>
 *          <li> #JG_BTN_CONTENT_TYPE_TEXT
 *          <li> #JG_BTN_CONTENT_TYPE_IMMUTABLE
 *          <li> #JG_BTN_CONTENT_TYPE_OFFSCREEN
 *         </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When button is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgButtonGetContentType(JGButton button);

/**
 * Gets the button label text string.
 * 
 * @param button
 *        The button handle
 * @return
 *         A handle is returned indicating a string with the button text. If 
 *         none is set,  #JK_INVALID_HANDLE is returned.
 * 
 * Do not discard the text string obtained by this function. The GUI Toolkit handles 
 * string disposal.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When button is an illegal handle.</li>
 *   </ul>
 */
JGString JgButtonGetText(JGButton button);

/**
 * Gets the immutable image set for the button.
 * 
 * @param button
 *        The button handle
 * 
 * @return
 *         A handle is returned indicating the immutable image set for the 
 *         button. If none is set, #JK_INVALID_HANDLE is returned.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When button is an illegal handle.</li>
 *   </ul>
 */
JKImageHandle JgButtonGetImage(JGButton button);

/**
 * Gets the off-screen image set for the button.
 * 
 * @param button
 *        The button handle
 * @return
 *         A handle is returned indicating the off-screen image set for the 
 *         button. If none is set, JK_INVALID_HANDLE is returned.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When button is an illegal handle.</li>
 *   </ul>
 */
JKOffScreenHandle JgButtonGetOffScreenImage(JGButton button);

/**
 * Gets the button pressed state.
 * 
 * @param button
 *        The button handle
 * 
 * @return
 *         Return JK_TRUE if pressed, else JK_FALSE.
 * 
 * @see JginButtonSetPressed()
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When button is an illegal handle.</li>
 *   </ul>
 */
JKBool JgButtonIsPressed(JGButton button);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_BUTTON_H */

