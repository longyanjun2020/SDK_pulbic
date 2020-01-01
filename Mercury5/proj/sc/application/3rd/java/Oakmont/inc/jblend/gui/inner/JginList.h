/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying list properties.
 */

#ifndef ___GUI_INNER_LIST_H
#define ___GUI_INNER_LIST_H

#include <JkTypes.h>
#include <JkImage.h>
#include <JkOffScreen.h>

#include <gui/common/JgList.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_List
 * @{
 */

/**
 *   A new item was added to the list.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 JKSint32 The index of the item added
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *   
 *   When the item is added, it is in empty state with no text or image set.
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_ITEM_INSERTED                (JG_COM_EVT_END + 0x01)

/**
 * A list item is being deleted.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKSint32 Index of the item for deletion
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
#define JG_LST_EVT_ITEM_REMOVING                (JG_COM_EVT_END + 0x02)

/**
 *   Text was set for a list item.
 *   
 *  When this event is processed by the event handler defined as 
 *  #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *  structure passed to the event handler by JBlend are indicated in the 
 *  following parameters. The event handler return value should be as indicated 
 *  below.
 *   
 *   @param param1 #JKSint32 Index of the item
 *   @param param2 #JGString The newly set text
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_ITEM_TEXT_CHANGED            (JG_COM_EVT_END + 0x03)

/**
 *   An immutable image was set for a list item.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKSint32 Index of the item
 *   @param param2 #JKImageHandle The newly set immutable image
 *   @param param3 #JKImageHandle The previous immutable image
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_ITEM_IMAGE_CHANGED           (JG_COM_EVT_END + 0x04)

/**
 *   An off-screen image was set for a list item.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKSint32 Index of the item
 *   @param param2 #JKOffScreenHandle The newly set off-screen image
 *   @param param3 #JKOffScreenHandle The previous off-screen image
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_ITEM_OFFSCREEN_CHANGED       (JG_COM_EVT_END + 0x05)

/**
 *   A font was set for a list item.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKSint32 Index of the item
 *   @param param2 #JKFontHandle The newly set font
 *   @param param3 #JKFontHandle The previous font
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_ITEM_FONT_CHANGED            (JG_COM_EVT_END + 0x06)

/**
 * A list item selection state changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKSint32 Index of the item
 * @param param2
 *        JKBool The new selection state
 * @param param3
 *        JKBool The previous selection state
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
#define JG_LST_EVT_SELECTION_CHANGED            (JG_COM_EVT_END + 0x07)

/**
 *   The list item word wrapping policy changed.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the 
 *   JGT_ComEvent structure passed to the event handler by JBlend are 
 *   as indicated in the following parameters. The event handler return value 
 *   should be as indicated below.
 * 
 *   @param param1 JKSint32 Index of the item whose wrapping policy changed
 *   @param param2 JKBool The new wrapping policy
 *   @param param3 JKBool The previous policy
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_WRAP_POLICY_CHANGED          (JG_COM_EVT_END + 0x08)

/**
 *   A list item was deleted.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the 
 *   JGT_ComEvent structure passed to the event handler by JBlend are 
 *   as indicated in the following parameters. The event handler return value 
 *   should be as indicated below.
 *   
 *   @param param1 #JKSint32 Index of the deleted item.<br>
 *                 The current index either points to a different item than the
 *                 one that was deleted or becomes invalid.
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_ITEM_REMOVED                 (JG_COM_EVT_END + 0x09)

/**
 *  The title text of a list was changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 #JGString The new list component title.
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_LST_EVT_TITLE_TEXT_CHANGED    (JG_COM_EVT_END + 0x0a)

/**
 * @internal
 * The maximum valid component event value for the list.
 */
#define JG_LST_EVT_END                          (JG_COM_EVT_END + 0x0a)

/**
 * Sets the selection state of the list item at the designated position.
 * 
 * @param list
 *        The list handle
 * @param index
 *        The position of the item
 * @param selected
 *        Set JK_TRUE if selected, JK_FALSE if deselected.
 * 
 * On a single-select list, putting a new item in selected state causes a 
 * previously selected item, if any, to be deselected. In that case events 
 * occur in the following sequence.
 * <ol>
 * <li>The event deselecting the previously selected item</li>
 * <li>The event newly selecting an item</li>
 * </ol>
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *    <li>When index is an illegal value.</li>
 *   </ul>
 */
void JginListSetSelected(JGList list, JKSint32 index, JKBool selected);

/**
 *   Sets the list item wrapping policy.
 *
 *   @param policy  Designate one of the following as the item wrapping policy.
 * <ul>
 *  <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_DEFAULT
 *  <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_ON
 *  <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_OFF
 * </ul>
 * 
 * <p>
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When list is an illegal handle.</li>
 *    <li>When policy is an illegal value.</li>
 *   </ul>
 * 
 * @see JgListGetWrapPolicy()
 */
void JginListSetWrapPolicy(JGList list, JKUint32 policy);

/**
 *   Sets the preferred size of the image set for a list item.
 *   
 *   @param width The preferred width
 *   @param height The preferred height
 *   
 *   <b>Note</b> Call this function when the list component is newly created.
 *      It cannot be used to change the setting while the list is active.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When width or height is a negative value.</li>
 *   </ul>
 */
void JginListSetPrefGlobalImageSize(JKSint32 width, JKSint32 height);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_LIST_H */

