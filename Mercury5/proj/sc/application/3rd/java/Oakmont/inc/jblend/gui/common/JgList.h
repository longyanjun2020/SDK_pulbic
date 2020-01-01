/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for the modifying list component properties.
 */

#ifndef ___GUI_COMMON_LIST_H
#define ___GUI_COMMON_LIST_H

#include <JkTypes.h>
#include <JkImage.h>
#include <JkOffScreen.h>

#include <gui/common/JgString.h>
#include <gui/common/JgGUIEvent.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_ListItem
 * @{
 */

/**
 *   List item handle.
 *   
 *   The list item handle is identifier of the list item.
 *   It can be used as the component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGListItem;

/** @} */

/**
 * @addtogroup GUI_List
 * @{
 */

/**
 *   The list selection state changed.
 * 
 *   When the list selection state has changed, notify the event using 
 *   #JginGUIEventPostEvent().
 *   The values of the param members in the JGT_GUIEvent structure passed as an 
 *   argument of JginGUIEventPostEvent() are as indicated in the following 
 *   parameters.
 * 
 *   @param param1 JKSint32
 *               Index of the item whose selection state changed
 *   @param param2 JKBool
 *               The new selection state
 *   @param param3 JKBool
 *               The previous selection state
 *   @param param4 -
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_LST_EVT_SELECTION_CHANGED    (JG_GUI_EVT_END + 0x01)

/**
 * @internal
 * The maximum GUI list event value
 */
#define JG_GUI_LST_EVT_END              (JG_GUI_EVT_END + 0x01)

/**
 * The list item image type: immutable image.
 * 
 * @see JGT_ListItem::imageType
 */
#define JG_LISTITEM_IMAGE_TYPE_IMMUTABLE    0

/**
 * The list item image type: off-screen image.
 * 
 * @see JGT_ListItem::imageType
 */
#define JG_LISTITEM_IMAGE_TYPE_OFFSCREEN    1

/**
 *  The list item word wrapping policy: Default
 *
 *  The native system is responsible for managing the default value for list item 
 *  word wrapping policy when a list is created.
 */
#define JG_LIST_WRAP_POLICY_TEXT_WRAP_DEFAULT   0

/**
 *  The list item word wrapping policy: Wrap on
 */
#define JG_LIST_WRAP_POLICY_TEXT_WRAP_ON        1

/**
 *  The list item word wrapping policy: Wrap off
 */
#define JG_LIST_WRAP_POLICY_TEXT_WRAP_OFF       2

/**
 * The list handle
 * 
 * A list handle is data identifying the list. <br>
 * The list handle can be used as a component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGList;

/**
 * Gets the numbmer of items registered for the list.
 * 
 * @param list
 *        The list handle
 * 
 * @return
 *         The number of registered items
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgListGetSize(JGList list);

/**
 *   Gets a list item in the list.
 *   
 *   @param list  The list handle.
 *   @param index The index of the list item.
 *   @return      The handle of the item indicated by the index parameter.
 *
 */
JGListItem JgListGetItem(JGList list, JKSint32 index);

/**
 * Gets the list item text at the designated position.
 * 
 * @param list
 *        The list handle
 * @param index
 *        The position of the item
 * 
 * @return
 *         The handle of the string holding the item text is returned. If none is 
 *         set, JK_INVALID_HANDLE is returned.
 * 
 * The obtained text must not be discarded. Discarding is done by the GUI Toolkit.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *   </ul>
 */
JGString JgListGetText(JGList list, JKSint32 index);

/**
 *   Gets the image type of the list item at the designated position.
 * 
 *   @param list
 *        The list handle
 *   @param index
 *        The designated position
 *   @return
 *        Return the image type.
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *    <li>When index is an illegal value.</li>
 *   </ul>
 * @see JG_LISTITEM_IMAGE_TYPE_IMMUTABLE
 * @see JG_LISTITEM_IMAGE_TYPE_OFFSCREEN
 * 
 */
JKUint32 JgListGetImageType(JGList list, JKSint32 index);

/**
 * Gets the immutable image of the item at the designated list position.
 * 
 * @param list
 *        The list handle
 * @param index
 *        The position of the item
 * 
 * @return
 *         The handle of the item immutable image is returned. If none is 
 *         set, JK_INVALID_HANDLE is returned.
 * 
 *     The immutable image obtained by this function must not be disposed of
 *     by the native system.
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *    <li>When index is an illegal value.</li>
 *   </ul>
 */
JKImageHandle JgListGetImage(JGList list, JKSint32 index);

/**
 * Gets the list item off-screen buffer image at the designated position.
 * 
 * @param list
 *        The list handle
 * @param index
 *        The position of the item
 * 
 * @return
 *         The handle of the item off-screen image is returned. If none is 
 *         set, JK_INVALID_HANDLE is returned.
 * 
 *     The off-screen image obtained by this function must not be disposed of
 *     by the native system.
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *    <li>When index is an illegal value.</li>
 *   </ul>
 */
JKOffScreenHandle JgListGetOffScreen(JGList list, JKSint32 index);

/**
 *   Gets the font of the list item at the designated position.
 *   
 *   @param list The list handle
 *   @param index The position of the item
 *   @return Return the handle of the font set for the item.
 * 
 *   If the font obtained by this function is one that was created newly in the 
 *   native system, the native system is responsible for font disposal. Otherwise the
 *   native system should not dispose of fonts.
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *    <li>When index is an illegal value.</li>
 *   </ul>
 */
JKFontHandle JgListGetFont(JGList list, JKSint32 index);

/**
 * Gets the selection state of the list item at the designated position.
 * 
 * @param list
 *        The list handle
 * @param index
 *        The position of the item
 * 
 * @return
 *         Return JK_TRUE if selected, else JK_FALSE.
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *    <li>When index is an illegal value.</li>
 *   </ul>
 */
JKBool JgListIsSelected(JGList list, JKSint32 index);

/**
 * Gets the list selected position.
 * 
 * @param list
 *        The list handle
 * 
 * @return
 *        The selected item position is returned, or -1 if no item is selected.
 * 
 * If the list is multi-select, the selected item with the smallest index number
 * is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgListGetSelectedIndex(JGList list);

/**
 *   Gets the list item word wrapping policy.
 *
 *   @return The item wrapping policy is returned as one of the following values.
 * <br><br>
 * <ul>
 *  <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_DEFAULT
 *  <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_ON
 *  <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_OFF
 * </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *   </ul>
 *
 * @see JginListSetWrapPolicy()
 */
JKUint32 JgListGetWrapPolicy(JGList list);

/**
 *   Gets the preferred width for images set in a list item.
 * 
 *   @return Return the preferred with.
 */
JKSint32 JgListGetPrefGlobalImageWidth(void);

/**
 *   Gets the preferred height for images set in a list item.
 * 
 *   @return Return the preferred height.
 */
JKSint32 JgListGetPrefGlobalImageHeight(void);

/**
 *  Gets the List label text
 * 
 *  @param list The list component handle
 *  @return 
 *         The lable text.
 *         If it is not set in the list component, #JK_INVALID_HANDLE is returned.
 *
 *  This function returns the text which is set as the label of the list.
 *
 *    The text returned by this function corresponds to the 
 *    title of <code>javax.microedition.lcdui.List</code> class or
 *    the lable of <code>javax.microedition.lcdui.ChoiceGroup</code> class.
 *
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When list is an illegal handle.</li>
 *  </ul>
 */
JGString JgListGetTitleText(JGList list);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_LIST_H */

