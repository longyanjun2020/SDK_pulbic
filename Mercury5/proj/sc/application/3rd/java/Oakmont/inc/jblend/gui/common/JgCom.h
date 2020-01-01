/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying component properties.
 */

#ifndef ___GUI_COMMON_COMPONENT_H
#define ___GUI_COMMON_COMPONENT_H

#include <JkTypes.h>
#include <JkGraphics.h>
#include <JkVideoComponent.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Component
 * @{
 */

/**
 * The component handle.
 * 
 * A component handle is data identifying the GUI component.
 */
typedef JKHandle    JGCom;

/**
 * The GUI component state: Disabled state.
 */
#define JG_COM_STATE_DISABLED    0

/**
 * The GUI component state: Enabled state.
 */
#define JG_COM_STATE_ENABLED       1

/**
 * The GUI component state: Focused state.
 */
#define JG_COM_STATE_FOCUSED       2

/**
 * The GUI component state: Active state.
 */
#define JG_COM_STATE_ACTIVE        3

/**
 *  The focus policy: User input occupied type.
 * 
 *   The GUI component state changes from Focused state (#JG_COM_STATE_FOCUSED) to 
 *   Active state (#JG_COM_STATE_ACTIVE) when the select key is pressed, and 
 *   user input becomes occupied.
 */
#define JG_COM_FOCUS_POLICY_OCCUPY      0x00000000

/**
 *  The focus policy: User input not occupied type.
 *
 *  When the GUI component state goes to Focused state (#JG_COM_STATE_FOCUSED), it 
 *  also goes directly to Active state (#JG_COM_STATE_ACTIVE) and user input 
 *  is not occupied.
 */
#define JG_COM_FOCUS_POLICY_SMOOTH      0x00000001

/**
 * Horizontal alignment of items in the GUI component: Center (default)
 */
#define JG_COM_ALIGN_X_CENTER       0x00000000

/**
 * Horizontal alignment of items in the GUI component: Left
 */
#define JG_COM_ALIGN_X_LEFT         0x00000001

/**
 * Horizontal alignment of items in the GUI component: Right
 */
#define JG_COM_ALIGN_X_RIGHT        0x00000002

/**
 * @if NOT_READY
 *   Horizontal alignment of items in the GUI component: Undefined
 * @endif
 */
#define JG_COM_ALIGN_X_UNDEFINED    (0x00000003)

/**
 * Vertical alignment of items in the GUI component: Center (default)
 */
#define JG_COM_ALIGN_Y_CENTER       0x00000000

/**
 * Vertical alignment of items in the GUI component: Top
 */
#define JG_COM_ALIGN_Y_TOP          0x00000001

/**
 * Vertical alignment of items in the GUI component: Bottom
 */
#define JG_COM_ALIGN_Y_BOTTOM       0x00000002

/**
 * The horizontal cutoff position for GUI component items when they do not fit in the 
 * component: Cut off at the right (default).
 */
#define JG_COM_CUT_POLICY_X_RIGHT    0x00000000

/**
 * The horizontal cutoff position for GUI component items when they do not fit in the 
 * component: Cut off at the left.
 */
#define JG_COM_CUT_POLICY_X_LEFT     0x00000001

/**
 * The horizontal cutoff position for GUI component items when they do not fit in the 
 * component: Center, cutting off at the right and left.
 */
#define JG_COM_CUT_POLICY_X_BOTH     0x00000002

/**
 * The vertical cutoff position for GUI component items when they do not fit in the 
 * component: Cut off at the bottom (default).
 */
#define JG_COM_CUT_POLICY_Y_BOTTOM   0x00000000

/**
 * The vertical cutoff position for GUI component items when they do not fit in the 
 * component: Cut off at the top.
 */
#define JG_COM_CUT_POLICY_Y_TOP      0x00000001

/**
 * The vertical cutoff position for GUI component items when they do not fit in the 
 * component: Center, cutting off at the top and bottom.
 */
#define JG_COM_CUT_POLICY_Y_BOTH     0x00000002

/**
 *   The preferred color for GUI component design: Background color
 */
#define JG_COM_PREF_GLOBAL_COLOR_BACKGROUND     0x00000000

/**
 *   The preferred color for GUI component design: Foreground color
 */
#define JG_COM_PREF_GLOBAL_COLOR_FOREGROUND     0x00000001

/**
 *   The preferred color for GUI component design: Background color when focused
 */
#define JG_COM_PREF_GLOBAL_COLOR_FOCUSED_BACKGROUND     0x00000002

/**
 *   The preferred color for GUI component design: Foreground color when focused
 */
#define JG_COM_PREF_GLOBAL_COLOR_FOCUSED_FOREGROUND     0x00000003

/**
 *   The preferred color for GUI component design: Border color
 */
#define JG_COM_PREF_GLOBAL_COLOR_BORDER     0x00000004

/**
 *   The preferred color for GUI component design: Border color when focused
 */
#define JG_COM_PREF_GLOBAL_COLOR_FOCUSED_BORDER     0x00000005

/**
 * @internal
 */
#define JG_COM_PREF_GLOBAL_COLOR_END        0x00000005

/**
 * @if SUPPORT_RTL
 *   GUI component orientation: Not set. 
 *
 * @endif
 */
#define JG_COM_ORIENTATION_UNKNOWN      0x0000

/**
 * @if SUPPORT_RTL
 *   GUI component orientation: Left to right.
 *
 * @endif
 */
#define JG_COM_ORIENTATION_LTR          0x0001

/**
 * @if SUPPORT_RTL
 *   GUI component orientation: Right to left.
 *
 * @endif
 */
#define JG_COM_ORIENTATION_RTL          0x0002

/**
 * Gets additional information about the GUI component creation.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         Extended information is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgComGetExtraData(JGCom component);

/**
 * Gets the component type.
 * 
 * @param component
 *        The GUI component handle
 * 
 * @return
 *        The component type is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgComGetComponentType(JGCom component);

/**
 *   Gets the GUI component focus policy.
 * 
 *   @param component The GUI component handle
 *   @return The GUI component focus policy is returned as one of the following values.
 * <br><br>
 * <ul>
 *  <li> #JG_COM_FOCUS_POLICY_OCCUPY
 *  <li> #JG_COM_FOCUS_POLICY_SMOOTH
 * </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetFocusPolicy()
 */
JKUint32 JgComGetFocusPolicy(JGCom component);

/**
 *   Gets the top inset value of a GUI component.
 *   
 *   @param component The GUI component handle
 *   @return The top inset value.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgComGetInsetTop(JGCom component);

/**
 *   Gets the left inset value of a GUI component.
 *   
 *   @param component The GUI component handle
 *   @return The left inset value.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgComGetInsetLeft(JGCom component);

/**
 *   Gets the right inset value of a GUI component.
 *   
 *   @param component The GUI component handle.
 *   @return The right inset value.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgComGetInsetRight(JGCom component);

/**
 *   Gets the bottom inset value of a GUI component.
 *   
 *   @param component The GUI component handle
 *   @return The bottom inset value.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgComGetInsetBottom(JGCom component);

/**
 *   Gets the parent component of a GUI component.
 *   
 *   @param component The GUI component handle
 *   @return The GUI component handle of the parent GUI component.
 *   
 *   This function gets the GUI component which owns the designated GUI component.
 *   For example, if a list item is designated in the component parameter,
 *   this function returns the handle of the parent list component.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JGCom JgComGetOwner(JGCom component);

/**
 * Gets the GUI component X coordinate.
 * 
 * @param component
 *        The GUI component handle
 * 
 * @return
 *         The x coordinate is returned.
 * 
 * Gets the coordinate position in the graphics context for drawing.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgComGetX(JGCom component);

/**
 * Gets the GUI component Y coordinate.
 * 
 * @param component
 *        The GUI component handle
 * 
 * @return
 *         The y coordinate is returned.
 * 
 * Gets the coordinate position in the graphics context for drawing.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgComGetY(JGCom component);

/**
 * Gets the GUI component width.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The width is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetSize()
 */
JKSint32 JgComGetWidth(JGCom component);

/**
 * Gets the GUI component height.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The height is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetSize()
 */
JKSint32 JgComGetHeight(JGCom component);

/**
 * Gets the GUI component foreground color.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The foreground color is returned in ARGB format.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetForeground()
 */
JKColor JgComGetForeground(JGCom component);

/**
 * Gets the GUI component background color.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The background color is returned in ARGB format.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKColor JgComGetBackground(JGCom component);

/**
 * @internal
 */
JKBool JgComIsVisible(JGCom component);

/**
 * Gets the GUI component state.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The GUI component state is returned as one of the following values.
 *     <br><br>
 *     <ul>
 *      <li> #JG_COM_STATE_DISABLED
 *      <li> #JG_COM_STATE_ENABLED
 *      <li> #JG_COM_STATE_FOCUSED
 *      <li> #JG_COM_STATE_ACTIVE
 *     </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetState()
 */
JKUint32 JgComGetState(JGCom component);

/**
 * Gets the font setting for the GUI component.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The font handle is returned.
 * 
 *  Do not discard the font set when the GUI component is initialized upon creation.
 *  Note, however, that when a font newly created in the native system is set using 
 *  #JginComSetFont(), it is necessary to dispose of a font created in the native system.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetFont()
 */
JKFontHandle JgComGetFont(JGCom component);

/**
 * Gets the horizontal alignment of items inside the GUI component.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The alignment method is returned as one of the following values.
 *     <br><br>
 *     <ul>
 *      <li> #JG_COM_ALIGN_X_CENTER
 *      <li> #JG_COM_ALIGN_X_LEFT
 *      <li> #JG_COM_ALIGN_X_RIGHT
 *     </ul>
 * 
 * <p>
 * Return the method of arranging items displayed in the GUI component
 * (differs depending on the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetAlignmentX()
 */
JKUint32 JgComGetAlignmentX(JGCom component);

/**
 * Gets the vertical alignment of items inside the GUI component.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The alignment method is returned as one of the following values.
 *     <br><br>
 *     <ul>
 *      <li> #JG_COM_ALIGN_Y_CENTER
 *      <li> #JG_COM_ALIGN_Y_TOP
 *      <li> #JG_COM_ALIGN_Y_BOTTOM
 *     </ul>
 * 
 * <p>
 * Return the method of arranging items displayed in the GUI component
 * (differs depending on the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetAlignmentY()
 */
JKUint32 JgComGetAlignmentY(JGCom component);

/**
 * Gets the horizontal cutoff position when the GUI component items do not fit 
 * inside the component.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The cutoff position is returned as one of the following values.
 *     <br><br>
 *     <ul>
 *      <li> #JG_COM_CUT_POLICY_X_RIGHT
 *      <li> #JG_COM_CUT_POLICY_X_LEFT
 *      <li> #JG_COM_CUT_POLICY_X_BOTH
 *     </ul>
 * 
 * <p>
 * Return the cutoff position when items do not fit inside a GUI component
 * (differs depending on the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetCutPolicyX()
 */
JKUint32 JgComGetCutPolicyX(JGCom component);

/**
 * Gets the vertical cutoff position when the GUI component items do not fit 
 * inside the component.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The cutoff position is returned as one of the following values.
 *     <br><br>
 *     <ul>
 *      <li> #JG_COM_CUT_POLICY_Y_BOTTOM
 *      <li> #JG_COM_CUT_POLICY_Y_TOP
 *      <li> #JG_COM_CUT_POLICY_Y_BOTH
 *     </ul>
 * 
 * <p>
 * Return the cutoff position when items do not fit inside a GUI component
 * (differs depending on the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetCutPolicyY()
 */
JKUint32 JgComGetCutPolicyY(JGCom component);

/**
 * Gets the GUI component preferred width.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The preferred width is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetPreferredSize()
 */
JKSint32 JgComGetPreferredWidth(JGCom component);

/**
 * Gets the GUI component preferred height.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The preferred height is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetPreferredSize()
 */
JKSint32 JgComGetPreferredHeight(JGCom component);

/**
 *   Gets the preferred GUI component width for the designated height.
 *   @param component The GUI component handle
 *   @param height The designated height
 *   @return Return the preferred width for the designated height.
 * 
 *   This function issues a #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT event
 *   and returns the event handler return value as the return value of this function.
 *   Accordingly, if the native system implements an event handler for the  
 *   #JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT event, be careful not to
 *   call this function from that event handler.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When height is a negative value.</li>
 *   </ul>
 */
JKSint32 JgComGetPrefWidthWithRespectToHeight(JGCom component, JKSint32 height);

/**
 *   Gets the preferred GUI component height for the designated width.
 *   @param component The GUI component handle
 *   @param width The designated width
 *   @return Return the preferred height for the designated width. 
 *   
 *   This function issues a #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH event
 *   and returns the event handler return value as the return value of this function.
 *   Accordingly, if the native system implements an event handler for the  
 *   #JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH event, be careful not to
 *   call this function from that event handler.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When width is a negative value.</li>
 *   </ul>
 */
JKSint32 JgComGetPrefHeightWithRespectToWidth(JGCom component, JKSint32 width);

/**
 * Gets the GUI component minimum width
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The minimum width is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetMinimumSize()
 */
JKSint32 JgComGetMinimumWidth(JGCom component);

/**
 * Gets the GUI component minimum height.
 * 
 * @param component
 *         The GUI component handle
 * 
 * @return
 *         The minimum height is returned.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetMinimumSize()
 */
JKSint32 JgComGetMinimumHeight(JGCom component);

/**
 *   Gets whether the GUI component is being displayed or not.
 * 
 *   @param component
 *        The GUI component handle
 *   @return
 *        Return JK_TRUE if the component is shown, else JK_FALSE.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 */
JKBool JgComIsShown(JGCom component);

/**
 *   Get the GUI component preferred color.
 *   
 *   @param type The type of preferred color to obtain
 *   @return Return the preferred color in ARGB format.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When type is an illegal value.</li>
 *   </ul>
 * 
 * @see JginComSetPrefGlobalColor()
 * @see JG_COM_PREF_GLOBAL_COLOR_BACKGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_FOREGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_FOCUSED_BACKGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_FOCUSED_FOREGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_BORDER
 * @see JG_COM_PREF_GLOBAL_COLOR_FOCUSED_BORDER
 * 
 */
JKColor JgComGetPrefGlobalColor(JKUint32 type);

/**
 *  Gets the truncate mode of the GUI component.
 *
 *   @param component The GUI component handle.
 *   @return The current truncate mode.
             If the string is longer than the width of one line:
 *          <ul>
 *           <li> #JK_TRUE, latter part of the string will be truncated
 *                        and shown in one line.</li>
 *           <li> #JK_FALSE, the string will be folded
 *                         and shown in multiple lines.</li>
 *          </ul>
 *  <p>
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When component is an illegal handle.</li>
 *  </ul>
 */
JKBool JgComGetTruncateMode(JGCom component);

/**
 * @if SUPPORT_RTL
 *   Gets the GUI component orientation.
 *   
 *   @param component
 *          The GUI component handle.
 *   @return
 *          One of the following is returned as the current orientation. 
 *          - #JG_COM_ORIENTATION_UNKNOWN
 *          - #JG_COM_ORIENTATION_LTR
 *          - #JG_COM_ORIENTATION_RTL
 *          .
 *
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When component is an illegal handle.</li>
 *  </ul>
 * @see JginComSetOrientation
 *
 * @endif
 */
JKUint JgComGetOrientation(JGCom component);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_COMPONENT_H */

