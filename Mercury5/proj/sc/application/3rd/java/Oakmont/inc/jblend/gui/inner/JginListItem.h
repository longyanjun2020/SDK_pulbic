/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   Functions for modifying list item component properties.
 */

#ifndef ___GUI_INNER_LISTITEM_H
#define ___GUI_INNER_LISTITEM_H

#include <JkTypes.h>
#include <JkImage.h>
#include <JkOffScreen.h>
#include <JkGraphics.h>
#include <JkVideoComponent.h>

#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/common/JgCom.h>
#include <gui/inner/JginCom.h>
#include <gui/common/JgList.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_ListItem
 * @{
 */

/**
 *   The structure type for holding the information of list item bitmap icons.
 */
typedef struct JGT_ListItemBmpData {
    /**
     *   Version of the structure. 
     *   
     *   Designate 1.
     */
    JKUint32 version;
    
    /**
     *   The initial address of the array holding ARGB-format data of bitmap icons in unselected state.
     */
    const JKColor *bmp_unselected;
    
    /**
     *   The initial address of the array holding ARGB-format data of bitmap icons in selected state.
     */
    const JKColor *bmp_selected;
    
    /**
     *   The width of bitmap.
     */
    JKSint32 width;
    
    /**
     *   The height of bitmap.
     */
    JKSint32 height;
} JGT_ListItemBmpData;

/**
 *   The line type of the border indicating list item focus frame. 
 *   
 *   This is used for designating the attribute when list item default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_LSTITEM_ATTR_FOCUS_LINE     (0x01)

/**
 *   The color of the border indicating list item focus frame. 
 *   
 *   This is used for designating the attribute when list item default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_LSTITEM_ATTR_FOCUS_LINE_COLOR       (0x02)

/**
 *   The color of the foreground of the list item when the content is in focus.
 *   
 *   This is used for designating the attribute when list item default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_LSTITEM_ATTR_FOREGROUND     (0x03)

/**
 *   The color of the background of the list item when the content is in focus.
 *   
 *   This is used for designating the attribute when list item default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute() 
 *   as a bit-wise OR value.
 */
#define JG_LSTITEM_ATTR_BACKGROUND     (0x04)

/**
 *   The color of the foreground of the list item when the content is in selected.
 *   
 *   This is used for designating the attribute when list item default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   This attribute can be set only when the list item type is of 
 *   #JG_LSTITEM_TYPE_PLANE or #JG_LSTITEM_TYPE_NUMBERED.
 *   When the list item is in Focused state and in selected state, 
 *   the item is drawn in the color setting for Focused state. 
 */
#define JG_LSTITEM_ATTR_SEL_NOBMP_FG    (0x05)

/**
 *   The color of the background of the list item when the content is in selected.
 *   
 *   This is used for designating the attribute when list item default design is changed.
 *   This constant and the constant representing the GUI component state are 
 *   designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute() 
 *   as a bit-wise OR value.
 *   
 *   This attribute can be set only when the list item type is of 
 *   #JG_LSTITEM_TYPE_PLANE or #JG_LSTITEM_TYPE_NUMBERED.
 *   When the list item is in Focused state and in selected state, 
 *   the item is drawn in the color setting for Focused state. 
 */
#define JG_LSTITEM_ATTR_SEL_NOBMP_BG    (0x06)

/**
 *   The bitmap icon of the #JG_LSTITEM_TYPE_CHECKBOX type list item.
 *   
 *   This is used for designating the attribute when the list item default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute().
 */
#define JG_LSTITEM_ATTR_BMP_CKBX        (0x07)

/**
 *   The bitmap icon of the #JG_LSTITEM_TYPE_RADIOBUTTON type list item.
 *   
 *   This is used for designating the attribute when the list item default design is changed.
 *   This constant is designated in the <i>type</i> parameter of #JginListItemSetStaticAttribute().
 */
#define JG_LSTITEM_ATTR_BMP_RDBTN       (0x08)

/**
 *   A list item was created.
 *   
 *   When this event is processed by the event handler defined as 
 *    #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKUint32 Additional information about the list item creation
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *   
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_CREATED                  (JG_COM_EVT_END + 0x01)

/**
 *   A list item is being deleted.
 *   
 *   When this event is processed by the event handler defined as 
 *    #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_DELETING                 (JG_COM_EVT_END + 0x02)

/**
 *   A list item index was set.
 * 
 *   When this event is processed by the event handler defined as 
 *    #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *  
 *   @param param1 #JKSint32 The newly set index
 *   @param param2 #JKSint32 The previous index
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *   
 *   This event indicates that the list index assigned to this list item
 *   has been changed.
 *   
 *   The following are the causes of this event.
 *   <ul>
 *     <li>A list item is added to a list at initial state.</li>
 *     <li>A list item is inserted before this list item.</li>
 *     <li>A list item having a smaller index than this list item is removed.</li>
 *   </ul>
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_INDEX_CHANGED            (JG_COM_EVT_END + 0x03)

/**
 *   Text was set for a list item.
 *   
 *   When this event is processed by the event handler defined as 
 *    #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JGString The set text string
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_TEXT_CHANGED             (JG_COM_EVT_END + 0x04)

/**
 *   An immutable image was set for a list item.
 *   
 *   When this event is processed by the event handler defined as 
 *    #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKImageHandle A handle indicating the newly set immutable image
 *   @param param2 #JKImageHandle A handle indicating the previous immutable image
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *   
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_IMAGE_CHANGED            (JG_COM_EVT_END + 0x05)

/**
 *   An off-screen image was set for a list item.
 *   
 *   When this event is processed by the event handler defined as 
 *    #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKOffScreenHandle A handle indicating the newly set off-screen image
 *   @param param2 #JKOffScreenHandle A handle indicating the previous off-screen image
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *   
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_OFFSCREEN_CHANGED        (JG_COM_EVT_END + 0x06)

/**
 *   A list item selection state changed.
 *   
 *   When this event is processed by the event handler defined as 
 *    #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKBool The new selection state
 *   @param param2 #JKBool The previous selection state
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *   
 * 
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_SELECTION_CHANGED        (JG_COM_EVT_END + 0x07)

/**
 *   The list item word wrapping policy changed.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the 
 *   JGT_ComEvent structure passed to the event handler by JBlend are 
 *   as indicated in the following parameters. The event handler return value 
 *   should be as indicated below.
 *   
 *   @param param1 #JKUint32 The new wrapping policy
 *   @param param2 #JKUint32 The previous policy
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_LSTITEM_EVT_WRAP_POLICY_CHANGED      (JG_COM_EVT_END + 0x08)

/**
 *   Preferred height for a list item rows was requested. 
 *   
 *   Return the preferred height for the designated rows under the
 *   following conditions.
 *   <ul>
 *     <li> The font currently set in the list item is used. </li>
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
#define JG_LSTITEM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS     (JG_COM_EVT_END + 0x09)

/**
 * @internal
 */
#define JG_LSTITEM_EVT_END                      (JG_COM_EVT_END + 0x09)

/**
 *   Sets a list item element attribute.
 *   
 *   @param type The element attribute and GUI component state.
 *   @param value1 The value1 to be set.
 *   @param value2 The value2 to be set.
 *   
 *   The settings made with this function affect all list item instances.
 *   Be sure to call this function only from #JgurInit().
 *   
 *   The value passed in the <i>type</i> parameter consists of the bit-wise OR of a constant
 *   indicating GUI component attributes and a constant indicating GUI component state. 
 *   The constant indicating GUI component state may designate one state or a combination of states. 
 *   When a combination of states is designated, attributes for multiple states may be set at the
 *   same time. 
 *   Attribute values are passed in <i>value1</i> and <i>value2</i>.
 *   A list of the parameters passed to this function is given below. 
 *   
 *   <table>
 *     <tr> 
 *       <td><b><i>type</i></b>
 *       <td><b><i>value1</i></b>
 *       <td><b><i>value2</i></b>
 *     </tr>
 *     <tr> 
 *       <td>[Line type of the focus frame]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_FOCUS_LINE
 *       <td>The line type. Designate one of the following:<br>
 *            #JG_COM_VAL_LINE_DOTTED<br>
 *            #JG_COM_VAL_LINE_SOLID<br>
 *            #JG_COM_VAL_LINE_NONE
 *       </td>
 *       <td>-
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of the focus frame]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_FOCUS_LINE_COLOR
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND_SYNC
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Foreground color when the list item has focus]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_FOREGROUND
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND_SYNC<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND_SYNC<br>
 *            #JG_COM_VAL_COLOR_CONTAINER_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Background color when the list item has focus]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_BACKGROUND
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND_SYNC<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND_SYNC<br>
 *            #JG_COM_VAL_COLOR_CONTAINER_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of "foreground" element in selected state]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_SEL_NOBMP_FG
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND<br>
 *            #JG_COM_VAL_COLOR_CONTAINER_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Color of "background" element in selected state]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_SEL_NOBMP_BG
 *       <td>The color setting. Designate one of the following: <br>
 *            #JG_COM_VAL_COLOR_FIXED<br>
 *            #JG_COM_VAL_COLOR_FOREGROUND<br>
 *            #JG_COM_VAL_COLOR_BACKGROUND<br>
 *            #JG_COM_VAL_COLOR_CONTAINER_BACKGROUND
 *       </td>
 *       <td>If <i>value1</i> is #JG_COM_VAL_COLOR_FIXED, the color to be set is designated in 0xAARRGGBB format.
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Checkbox bitmap icon]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_BMP_CKBX
 *       <td>A pointer to the JGT_ListItemBmpData structure for holding the information of list item bitmap icons.
 *       </td>
 *       <td>0
 *       </td>
 *     </tr>
 *     <tr> 
 *       <td>[Radio button bitmap icon]<br>
 *           Following constants indicating attribute.<br>
 *            #JG_LSTITEM_ATTR_BMP_RDBTN
 *       <td>A pointer to the JGT_ListItemBmpData structure for holding the information of list item bitmap icons.
 *       </td>
 *       <td>0
 *       </td>
 *     </tr>
 *   </table>
 *   
 *   In case #JG_LSTITEM_ATTR_BMP_CKBX or #JG_LSTITEM_ATTR_BMP_RDBTN is designated in the 
 *   <i>type</i> parameter, the #JGT_ListItemBmpData structure passed in the <i>value1</i> 
 *   parameter needs not to be retained after the completion of this function.
 *   However, the pointer to the ARGB-format data set in the <i>bmp_unselected</i> member and 
 *   <i>bmp_selected</i> member of #JGT_PUListBmpData structure must remain valid until the JVM terminates.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When <i>type</i> is an illegal value.</li>
 *    <li>When <i>value1</i> is an illegal value.</li>
 *    <li>When <i>value2</i> is an illegal value.</li>
 *   </ul>
 *   In case #JG_LSTITEM_ATTR_BMP_CKBX or #JG_LSTITEM_ATTR_BMP_CKBX is designated in the 
 *   <i>type</i> parameter, 
 *   @ref page_gui_trouble_shooting "Error" occurs in the following cases.<br>
 *   <ul>
 *     <li>When <i>value1</i> is #JK_NULL. </li>
 *     <li>When <i>value2</i> is othe than 0.</li>
 *     <li>When the <i>version</i> member of #JGT_ListItemBmpData structure designated in the 
 *         <i>value1</i> parameter is other than 1.</li>
 *     <li>When the <i>bmp_unselected</i> member of #JGT_ListItemBmpData structure designated in the 
 *         <i>value1</i> parameter is #JK_NULL.</li>
 *     <li>When the <i>bmp_selected</i> member of #JGT_ListItemBmpData structure designated in the 
 *         <i>value1</i> parameter is #JK_NULL.</li>
 *     <li>When the <i>width</i> member of #JGT_ListItemBmpData structure designated in the 
 *         <i>value1</i> parameter is a negative value.</li>
 *     <li>When the <i>height</i> member of #JGT_ListItemBmpData structure designated in the 
 *         <i>value1</i> parameter is a negative value.</li>
 *   </ul>
 */
void JginListItemSetStaticAttribute(JKUint32 type, JKUint32 value1, JKUint32 value2);

/**
 *   Sets the selection state of the list item.
 *   
 *   @param listItem The list item handle
 *   @param selected Set #JK_TRUE if selected, #JK_FALSE if deselected.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *    <li>When selected is an illegal value.</li>
 *   </ul>
 */
void JginListItemSetSelected(JGListItem listItem, JKBool selected);

/**
 *   Sets the list item wrapping policy.
 *   
 *   @param policy Designate one of the following as the list item wrapping policy.
 *          <ul>
 *           <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_DEFAULT
 *           <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_ON
 *           <li> #JG_LIST_WRAP_POLICY_TEXT_WRAP_OFF
 *          </ul>
 *   <p>
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When listItem is an illegal handle.</li>
 *    <li>When policy is an illegal value.</li>
 *   </ul>
 */
void JginListItemSetWrapPolicy(JGListItem listItem, JKUint32 policy);

/**
 * @if NOT_READY
 *   Sets the horizontal alignment of text of the list item.
 *   
 *   @param listItem    The list item handle
 *   @param alignment   The alignment method. Designate one of the following.
 *                      <ul>
 *                        <li> #JG_COM_ALIGN_X_UNDEFINED </li>
 *                        <li> #JG_COM_ALIGN_X_LEFT </li>
 *                        <li> #JG_COM_ALIGN_X_RIGHT </li>
 *                      </ul>
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When listItem is an illegal handle.</li>
 *     <li>When alignment is an illegal value.</li>
 *   </ul>
 * @endif
 */
void JginListItemSetTextAlignX(JGListItem listItem, JKUint32 alignment);

/**
 *   Sets the listitem component event handler.
 *   
 *   @param type The corresponding event type
 *   @param handler The component event handler to be set
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When type is an illegal value.</li>
 *    <li>When handler is  #JK_NULL.</li>
 *   </ul>
 */
void JginListItemSetComEvtHandler(JKUint32 type, JGT_ComEvtHandler handler);

/**
 *   The default component event handler for the list item.
 *   
 *   @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event
 *        information.
 *   @return 
 *        The processing result is returned.
 *   
 *   The list item default component event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   
 *   <dl>
 *     <dt> #JG_LSTITEM_EVT_CREATED , #JG_LSTITEM_EVT_DELETING </dt>
 *       <dd>No operation</dd>
 *  
 *     <dt> #JG_LSTITEM_EVT_TEXT_CHANGED </dt>
 *       <dd>Changes the list item preferred size and the minimum size,
 *           and notifies the GUI event #JG_LST_EVT_ITEM_TEXT_CHANGED to the 
 *           list component which owns the list item. 
 *           If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.
 *          </dd>
 *  
 *     <dt> #JG_LSTITEM_EVT_IMAGE_CHANGED </dt>
 *       <dd>Changes the list item preferred size and the minimum size,
 *           and notifies the GUI event #JG_LST_EVT_ITEM_TEXT_CHANGED to the 
 *           list component which owns the list item. 
 *           If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *     <dt> #JG_LSTITEM_EVT_OFFSCREEN_CHANGED </dt>
 *       <dd>Changes the list item preferred size and the minimum size,
 *           and notifies the GUI event #JG_LST_EVT_ITEM_TEXT_CHANGED to the 
 *           list component which owns the list item. 
 *           If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *     <dt> #JG_LSTITEM_EVT_SELECTION_CHANGED </dt>
 *       <dd>Notifies the GUI event #JG_LST_EVT_ITEM_TEXT_CHANGED to the 
 *           list component which owns the list item. 
 *           If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *     <dt> #JG_LSTITEM_EVT_WRAP_POLICY_CHANGED </dt>
 *       <dd>If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *     <dt> #JG_COM_EVT_FONT_CHANGED </dt>
 *       <dd>Changes the list item preferred size and the minimum size,
 *           and notifies the GUI event #JG_LST_EVT_ITEM_TEXT_CHANGED to the 
 *           list component which owns the list item. 
 *           If the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend.</dd>
 *  
 *     <dt> #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT </dt>
 *       <dd>Returns the preferred width for the designated height.
 *           The list item word wrapping policy is taken into consideration
 *           in the determination of the width.</dd>
 *  
 *     <dt> #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH </dt>
 *       <dd>Returns the preferred height for the designated width.
 *           The list item word wrapping policy is taken into consideration
 *           in the determination of the height.</dd>
 *  
 *     <dt> #JG_LSTITEM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_ROWS </dt>
 *       <dd>Returns the preferred height for the designated rows.</dd>
 *  
 *     <dt> #JG_COM_EVT_GET_PREF_WIDTH, #JG_COM_EVT_GET_PREF_HEIGHT</dt>
 *       <dd>Returns the preferred size of the list item default design.</dd>
 *  
 *     <dt> #JG_COM_EVT_GET_MIN_WIDTH, #JG_COM_EVT_GET_MIN_HEIGHT </dt>
 *       <dd>Returns the minimum size of the list item default design.</dd>
 *  
 *     <dt> #JG_COM_EVT_PAINT_HIDDEN </dt>
 *       <dd>Issues the component event #JG_COM_EVT_PAINT.</dd>
 *  
 *     <dt> #JG_COM_EVT_PAINT </dt>
 *       <dd>Draws a list item</dd>
 *   
 *  <dt> #JG_COM_EVT_RELAYOUTING </dt>
 *  <dd>Updates the following settings based on the current dominant language direction
 *      <table>
 *        <tr>
 *          <td>Property</td>
 *          <td>LTR</td>
 *          <td>RTL</td>
 *        </tr>
 *        <tr>
 *          <td>Horizontal cutoff position</td>
 *          <td> #JG_COM_CUT_POLICY_X_RIGHT </td>
 *          <td> #JG_COM_CUT_POLICY_X_LEFT </td>
 *        </tr>
 *        <tr>
 *          <td>Inset value</td>
 *          <td>Icon display space is placed in the right side. </td>
 *          <td>Icon display space is placed in the left side. </td>
 *        </tr>
 *      </table>
 *  </dd>
 *  
 *     <dt>Other events</dt>
 *       <dd>If the list item content has changed and the display state is Shown, notifies the GUI event #JG_GUI_EVT_REPAINT to JBlend. </dd>
 *   </dl>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the JGT_ComEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginListItemDefaultComEvtHandler(const JGT_ComEvent *comEvent);

/**
 * Sets the list item key event handler.
 * 
 * @param handler
 *        The key event handler to be set
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When handler is #JK_NULL.</li>
 *   </ul>
 */
void JginListItemSetKeyEvtHandler(JGT_KeyEvtHandler handler);

/**
 *   The default key event handler for the list item.
 *   
 *   @param keyEvent
 *        A pointer to the JGT_KeyEvent structure holding the generated event information.
 *   @return 
 *        The processing result is returned.
 *   
 *   The list item default key event handler performs the following event processing.
 *   If this processing is to be performed when the corresponding event is
 *   processed in the native system event handler, pass the event to this function 
 *   in the event handler implemented for the native system.
 *   <dl>
 *   <dt> #AM_KEYCODE_SELECT </dt>
 *   <dd>
 *       <dl>
 *       <dt> #AM_EVENT_KEY_CLICKED </dt>
 *        <dd>Sets the list item state to #JG_COM_STATE_FOCUSED, 
 *            and notifies the GUI event #JG_GUI_EVT_RELEASE_INPUT_EVENT to
 *            release the user input event occupation. 
 *        </dd>
 *       </dl>
 *   </dd>
 *   </dl>
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When the value set in component member of the #JGT_KeyEvent structure is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JginListItemDefaultKeyEvtHandler(const JGT_KeyEvent *keyEvent);

/**
 *   The default pointing device handler for the list item.
 *   
 *   @param pointerEvent 
 *        A pointer to the #JGT_PointerEvent structure holding the generated 
 *        event information
 *   @return 
 *        The processing result is returned.
 *   
 *    This function is provided for future extension. 
 *    It does not perform any action currently.
 */
JKUint32 JginListItemDefaultPointerEvtHandler(const JGT_PointerEvent *pointerEvent);

/**
 * Draws the inner content of a list item.
 *
 * @param listItem   The list item handle.
 * @param g          The graphics context handle.
 * @param dx         The x-direction offset of inner content drawing position.
 * @param dy         The y-direction offset of inner content drawing position.
 * @param foreground The foreground color.
 *
 * This function draws the inner content of the list item using the graphics
 * context designated in the g parameter.
 * This function usees a clip region which is the intersection of the graphics 
 * context clip region and the inner content.
 * The drawing position of the inner content is determined based on the 
 * list item coordinates and the inset values.
 *   
 * When calling this function, set the same clip region to the graphics 
 * context as the clip region which has been set for the graphics context 
 * when a JG_COM_EVT_PAINT event was notified.
 * 
 * @see JginComSetInsets()
 * @see JgComGetInsetTop()
 * @see JgComGetInsetLeft()
 * @see JgComGetInsetRight()
 * @see JgComGetInsetBottom()
 */
void JginListItemPaintContent(JGListItem listItem, JKGraphicsContext g,
                              JKSint32 dx, JKSint32 dy, JKColor foreground);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_LISTITEM_H */

