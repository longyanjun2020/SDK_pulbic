/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Functions for modifying listbox component properties.
 */

#ifndef ___GUI_INNER_LISTBOX_H
#define ___GUI_INNER_LISTBOX_H

#include <JkTypes.h>

#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginList.h>
#include <gui/common/JgListBox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_ListBox
 * @{
 */

/**
 * Notifies that focus has moved inside the listbox.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKSint32 The current focus position
 * @param param2
 *        JKSint32 The previous focus position
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
#define JG_LSTBX_EVT_FOCUS_CHANGED          (JG_LST_EVT_END + 0x01)

/**
 *   Preferred height for a listbox rows was requested. 
 *   
 *   Return the preferred height for the designated rows under the
 *   following conditions.
 *   <ul>
 *     <li> The font currently set in the listbox is used. </li>
 *     <li> List items have only one line with no word wrapping. </li>
 *     <li> List items have only text; namely, no image is set. </li>
 *   </ul>
 *   
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *   
 *   @param param1 JKSint32 The designated rows.
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return JKSint32 Return the preferred height for the designated rows.
 *   
 *    This event is not generated for MIDP.
 * @see JGT_ComEvent::type
 */
#define JG_LSTBX_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS   (JG_LST_EVT_END + 0x02)



/**
 * @internal
 * The maximum valid component event value for the listbox.
 */
#define JG_LSTBX_EVT_END                    (JG_LST_EVT_END + 0x03)

/**
 *   Sets the focus position inside the listbox.
 *   
 *   @param listbox
 *        The listbox handle
 *   @param index
 *        The inner focus position
 *
 *   Designate the focus position in the listbox, with 0 as the topmost item.
 *   Designate -1 if focus is to be removed from the listbox.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listbox is an illegal handle.</li>
 *    <li>When index is an illegal value.</li>
 *   </ul>
 */
void JginListBoxSetFocusedIndex(JGListBox listbox, JKSint32 index);


/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_LISTBOX_H */

