/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying textbox component properties.
 */

#ifndef ___GUI_COMMON_TEXTBOX_H
#define ___GUI_COMMON_TEXTBOX_H

#include <JkTypes.h>

#include <gui/common/JgTextInput.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_TextBox
 * @{
 */

/**
 * @internal
 * The maximum value of GUI textbox events
 */
#define JG_GUI_TXTBX_EVT_END                 (JG_GUI_TXT_EVT_END + 0x00)

/**
 * The textbox component type
 * 
 * @see JgComGetComponentType()
 */
#define JG_TEXTBOX      8

/**
 * The textbox handle
 * 
 * A textbox handle is data identifying the textbox. <br>
 * The textbox handle can be used as a component handle or text input handle.
 * 
 * @see JGTextInput
 */
typedef JGTextInput       JGTextBox;

/**
 * @if NOT_READY
 * @else
 *  Gets the height necessary for drawing the textbox string.
 *
 *   @param textbox The textbox handle.
 *   @return Height in pixels.
 *
 *   This function returns the height necessary for drawing a character string in the designated 
 *   textbox. If the string does not fit on one line, it returns the height taking into account
 *   word wrapping of the text to fit the textbox width. 
 * 
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When textbox is an illegal handle.</li>
 *  </ul>
 * @endif
 */
JKSint32 JgTextBoxGetFormattedStringHeight(JGTextBox textbox);

/**
 * @if NOT_READY
 * @endif
 */
JKSint32 JgTextBoxGetFormattedStringHeightR2(JGTextBox textbox, JKSint32 limit);

/**
 *  Gets the textbox vertical scroll offset.
 *
 *   @param textbox The textbox handle.
 *   @return Scrolling offset in pixels.
 *   
 *   This function returns the vertical offset from the top of the textbox character string to the
 *   actual drawing position. 
 *   
 *   The value returned by this function varies as the textbox is scrolled by 
 *   #JginTextBoxScrollVertical().   
 *   The value returned by this function is indicated in the figure at #JginTextBoxScrollVertical().
 *
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When textbox is an illegal handle.</li>
 *  </ul>
 * @see JginTextBoxScrollVertical()
 */
JKSint32 JgTextBoxGetVerticalOffset(JGTextBox textbox);

/**
 *   @deprecated
 *   This function is due to be abolished, and has been replaced by #JgComGetTruncateMode().
 *   Use of this function is not recommended.
 */
JKBool JgTextBoxGetTruncateMode(JGTextBox textbox);




/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_TEXTBOX_H */

