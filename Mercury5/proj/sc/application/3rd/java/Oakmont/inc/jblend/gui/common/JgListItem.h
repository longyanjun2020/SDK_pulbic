/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   Common API functions for list-item component.
 */

#ifndef ___GUI_COMMON_LISTITEM_H
#define ___GUI_COMMON_LISTITEM_H

#include <JkTypes.h>

#include <JkImage.h>
#include <JkOffScreen.h>

#include <gui/common/JgString.h>
#include <gui/common/JgList.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_ListItem
 * @{
 */

/**
 *   Normal list.\ (A type of list item without bitmap image)
 */
#define JG_LSTITEM_TYPE_PLANE           0

/**
 *   Checkbox.\ (A list item type)
 */
#define JG_LSTITEM_TYPE_CHECKBOX        1

/**
 *   Radio button.\ (A list item type)
 */
#define JG_LSTITEM_TYPE_RADIOBUTTON     2

/**
 *   Number ordered list.\ (A list item type)
 */
#define JG_LSTITEM_TYPE_NUMBERED        3

/**
 *   The list item component type.
 * @see JgComGetComponentType
 */
#define JG_LISTITEM     14

/**
 *   Gets the list item type.
 * 
 *   @param listItem The list item handle
 *   @return The list item type is returned as one of the following values.
 *           <ul>
 *            <li> #JG_LSTITEM_TYPE_PLANE
 *            <li> #JG_LSTITEM_TYPE_CHECKBOX
 *            <li> #JG_LSTITEM_TYPE_RADIOBUTTON
 *           </ul>
 *   <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgListItemGetType(JGListItem listItem);

/**
 *   Gets the list item index.
 *   
 *   @param listItem The list item handle
 *   @return Return the index of list component.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgListItemGetIndex(JGListItem listItem);

/**
 *   Gets the list item text.
 *   
 *   @param listItem The list item handle
 *   @return 
 *         The handle of the string holding the list item text is returned. If none is 
 *         set, #JK_INVALID_HANDLE is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JGString JgListItemGetText(JGListItem listItem);

/**
 *   Gets the image type of the list item.
 *   
 *   @param  listItem The list item handle.
 *   @return  One of the following is returned as the type of the image which has been set to the list item.
 *           <ul>
 *            <li> #JG_LISTITEM_IMAGE_TYPE_IMMUTABLE
 *            <li> #JG_LISTITEM_IMAGE_TYPE_OFFSCREEN
 *           </ul>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgListItemGetImageType(JGListItem listItem);

/**
 *   Gets the immutable image of the list item.
 *   
 *   @param listItem The list item handle
 *   @return The handle of the list item immutable image is returned.
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JKImageHandle JgListItemGetImage(JGListItem listItem);

/**
 *   Gets the off-screen image of the list item.
 *   
 *   @param listItem The list item handle
 *   @return The handle of the list item off-screen image is returned.
 *           If none is set, #JK_INVALID_HANDLE is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JKOffScreenHandle JgListItemGetOffScreenImage(JGListItem listItem);

/**
 *   Gets the selection state of the list item.
 *   
 *   @param listItem The list item handle
 *   @return Return #JK_TRUE if selected, else #JK_FALSE.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JKBool JgListItemIsSelected(JGListItem listItem);

/**
 *   Gets the list item word wrapping policy.
 *   
 *   @param listItem The list item handle
 *   @return The list item wrapping policy is returned as one of the following values.
 *           <ul>
 *            <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_DEFAULT
 *            <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_ON
 *            <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_OFF
 *           </ul>
 *   <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgListItemGetWrapPolicy(JGListItem listItem);

/**
 *   Gets the list item preferred height for the designated number of rows.
 *   
 *   @param listItem The list item handle.
 *   @param rows 
 *          The number of rows.
 *   @return 
 *          The preferred height for the designated number of rows.
 *   
 *   The preferred height is calculated based on the following conditions.
 *   <ul>
 *     <li> The font currently set in the list item is used. </li>
 *     <li> List items have only text; namely, no image is set. </li>
 *   </ul>
 *   
 *   This function issues a JG_LSTITEM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS event and returns 
 *   the event handler return value as the return value of this function. 
 *   Accordingly, if the native system implements an event handler for the 
 *   JG_LSTITEM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS event, 
 *   be careful not to call this function from that event handler. 
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *    <li>When rows is a negative value. 
 *   </ul>
 */
JKSint32 JgListItemGetPrefHeightWithRespectToRows(JGListItem listItem, JKSint32 rows);

/**
 * @if NOT_READY
 *   Gets the horizontal alignment of text of list item.
 *   
 *   @param listItem    The list item handle
 *   @return    The alignment method is returned as one of the following values.
 *              <ul>
 *                <li> #JG_COM_ALIGN_X_UNDEFINED </li>
 *                <li> #JG_COM_ALIGN_X_LEFT </li>
 *                <li> #JG_COM_ALIGN_X_RIGHT </li>
 *              </ul>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When listItem is an illegal handle.</li>
 *   </ul>
 * @endif
 */
JKUint32 JgListItemGetTextAlignX(JGListItem listItem);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_LISTITEM_H */

