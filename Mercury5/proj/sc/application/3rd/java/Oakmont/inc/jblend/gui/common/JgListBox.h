/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying the listbox component properties.
 */

#ifndef ___GUI_COMMON_LISTBOX_H
#define ___GUI_COMMON_LISTBOX_H

#include <JkTypes.h>

#include <gui/common/JgList.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_ListBox
 * @{
 */

/**
 * @internal
 * The maximum GUI listbox event value.
 */
#define JG_GUI_LSTBX_EVT_END                    (JG_GUI_LST_EVT_END + 0x00)

/**
 * The listbox handle.
 * 
 * A listbox handle is data identifying the listbox.<br>
 * The listbox handle can be used as a component handle or list handle.
 * 
 * @see JGList
 */
typedef JGList      JGListBox;

/**
 *   Gets the focus position in the listbox.
 *   
 *   @param listbox
 *         The listbox handle.
 *
 *   @return
 *         Return the inner focus position, or -1 if no inner focus.
 *   
 *   The inner focus position in a listbox is returned with 0 being the topmost item.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listbox is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgListBoxGetFocusedIndex(JGListBox listbox);

/**
 *   Gets the listbox preferred height for the designated number of rows.
 *   
 *   @param listbox The listbox handle.
 *   @param rows 
 *          The number of rows.
 *   @return 
 *          The preferred height for the designated number of rows.
 *   
 *   The preferred height is calculated based on the following conditions.
 *   <ul>
 *     <li> The font currently set in the listbox is used. </li>
 *     <li> List items have only one line with no word wrapping. </li>
 *     <li> List items have only text; namely, no image is set. </li>
 *   </ul>
 *   
 *   This function issues a #JG_LSTBX_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS event and returns 
 *   the event handler return value as the return value of this function. 
 *   Accordingly, if the native system implements an event handler for the 
 *   #JG_LSTBX_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS event, 
 *   be careful not to call this function from that event handler. 
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listbox is an illegal handle.</li>
 *    <li>When rows is a negative value. 
 *   </ul>
 */
JKSint32 JgListBoxGetPrefHeightWithRespectToRows(JGListBox listbox, JKSint32 rows);


/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_LISTBOX_H */

