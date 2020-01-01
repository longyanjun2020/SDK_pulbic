/**
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkSoftkey.h
 * Soft Key JSI
 */
/**
 * @addtogroup Soft_Key_JSI
 * @{
 */

#ifndef ___JK_SOFTKEY_H
#define ___JK_SOFTKEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkVideoComponent.h"

/**
 * Scrolling not enabled
 */
#define JK_SOFTKEY_SCROLL_NONE          0

/**
 * Scroll up enabled
 */
#define JK_SOFTKEY_SCROLL_UP            1

/**
 * Scroll down enabled
 */
#define JK_SOFTKEY_SCROLL_DOWN          2

/**
 * Scroll right enabled
 */
#define JK_SOFTKEY_SCROLL_RIGHT         4

/**
 * Scroll left enabled
 */
#define JK_SOFTKEY_SCROLL_LEFT          8

/**
 * Focus movement not enabled
 */
#define JK_SOFTKEY_MOVE_FOCUS_NONE      0

/**
 * Focus movement up enabled
 */
#define JK_SOFTKEY_MOVE_FOCUS_UP        1

/**
 * Focus movement down enabled
 */
#define JK_SOFTKEY_MOVE_FOCUS_DOWN      2

/**
 * Focus movement right enabled
 */
#define JK_SOFTKEY_MOVE_FOCUS_RIGHT     4

/**
 * Focus movement left enabled
 */
#define JK_SOFTKEY_MOVE_FOCUS_LEFT      8

/**
 * Set the specified character string as soft key text.
 *
 * @param label
 *        A pointer to a character string for a soft key text, given as Unicode. (No '\0' termination)
 * @param length
 *        The number of characters in specified character string
 * @param location
 *        Soft key location (from 1 to the number of soft keys)
 *
 * If a string is already set, overwrite it.
 * This function only makes the setting; do the actual drawing when JkSoftkeyPaint()
 * is called.
 * 
 * The following illegal parameters designations are not to be made.
 * <ul>
 *  <li>Designating a NULL pointer in the label parameter.
 *  <li>Designating a value of 0 or less in the length parameter.
 * </ul>
 * 
 * @see JkSoftkeyPaint()
 */
void JkSoftkeySetLabel( const JKWChar *label, const JKSint32 length,
                                           JKSint32 location );

/**
 * Resets the soft keys.
 *
 * Delete all the settings. This does not affect scrolling or focus state.
 * This function only changes the setting; do the actual drawing when JkSoftkeyPaint()
 * is called.
 * 
 * @see JkSoftkeyPaint()
 */
void JkSoftkeyResetLabels( void );

/**
 * Sets the currently scrollable direction.
 *
 * @param state
 *        The scrollable direction. The logical OR of JK_SOFTKEY_SCROLL_XXXX is designated.
 *
 * This function is called when the screen scrollable direction changes. Display
 * to the user the scrollable direction.
 * This function only makes the setting; do the actual drawing when JkSoftkeyPaint()
 * is called.
 * 
 * Values other than the logical-OR of JK_SOFTKEY_SCROLL_XXXX are never designated in the state parameter.
 * 
 * @see JkSoftkeyPaint()
 */
void JkSoftkeySetScrollState( JKSint32 state );

/**
 * Sets the current viewport for whole of contents to be displayed.
 *
 * @param viewport
 *        The position and size (given as pixel) of the viewport (the area to be displayed).
 * @param contentWidth
 *        The width (given as pixel) of whole of the displaying contents
 * @param contentHeight
 *        The height (given as pixel) of whole of the displaying contents
 *
 * This function is called when the viewport position in whole of the displaying contents changes.
 * When a scroll bar needs to be displayed on a platform, 
 * display a scroll bar and a slider based on the display position and size 
 * which were specified with this function. 
 * When the value of all arguments is 0, it means that the size of display contents is 
 * the same as the viewport, or being contained in the viewport. 
 * This function only makes the setting if needed; do the actual drawing (scroll bar etc.) 
 * when #JkSoftkeyPaint() is called.
 * When not using the information directed with this function for some drawing etc., 
 * it is not necessary to do anything in this function (the contents of this function may be empty).
 * 
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the viewport parameter.
 *  <li>Designating a value less than 0 in the width member or height member of the JKT_Rect structure indicated by the viewport parameter.
 *  <li>Designating a value less than 0 in the contentWidth or contentHeight parameter.
 * </ul>
 * <br>
 * The example of arguments)<br>
 * - When the size of the screen which created by Java application is 120x200 and the size of 
 *   a virtual screen is 120x140 and it is displaying on the screen from the position of (0, 20). 
 * <center><table>
 *  <tr><td>viewport->x     </td><td>0</td></tr>
 *  <tr><td>viewport->y     </td><td>20</td></tr>
 *  <tr><td>viewport->width </td><td>120</td></tr>
 *  <tr><td>viewport->height</td><td>140</td></tr>
 *  <tr><td>contentWidth    </td><td>120</td></tr>
 *  <tr><td>contentHeight   </td><td>200</td></tr>
 * </table></center>
 * 
 * @see JkSoftkeyPaint()
 */
void JkSoftkeySetScrollPosition( const JKT_Rect *viewport, JKSint32 contentWidth, JKSint32 contentHeight );

/**
 * Sets the direction in which focus movement is currently possible.
 *
 * @param state
 *        The direction in which focus movement is possible. This is designated as the
 *        logical OR of JK_SOFTKEY_MOVE_FOCUS_XXXX.
 *
 * This function is called when the direction of possible focus movement in a
 * selectable GUI component changes. Display to the user the direction in which
 * movement is possible.
 * This function only makes the setting; do the actual drawing when JkSoftkeyPaint()
 * is called.
 * 
 * Values other than the logical-OR of JK_SOFTKEY_MOVE_FOCUS_XXXX are never designated in the state parameter.
 * 
 * @see JkSoftkeyPaint()
 */
void JkSoftkeySetFocusState( JKSint32 state );

/**
 *    <em>This function has been abolished but its definition is retained for the
 *        backward compatibility.\
 *        Currently this function is not used and there is no need to implement it. </em>
 */
JKSint32 JkSoftkeyGetFocusState( void );

/**
 * Performs soft key drawing.
 *
 * Draw the soft keys and indicators in accord with the settings made in the 
 * following functions. 
 *      <ul>
 *        <li> JkSoftkeySetLabel()
 *        <li> JkSoftkeyResetLabels()
 *        <li> JkSoftkeySetScrollState()
 *        <li> JkSoftkeySetFocusState()
 *      </ul>
 * If the platform adopts any of the following display specifications, they must 
 * be taken into account when deciding what is to be drawn on the screen.
 *      <ul>
 *        <li> Soft keys and indicators are displayed even in full-screen mode.
 *        <li> Even when the number of available soft keys is 0, an indicator is 
 *             displayed showing a Command instance is being used by a Java 
 *             application.
 *      </ul>
 * This function is called even if the number of available soft keys is 0.
 * 
 * @see JkSoftkeySetLabel()
 * @see JkSoftkeyResetLabels()
 * @see JkSoftkeySetScrollState()
 * @see JkSoftkeySetFocusState()
 */
void JkSoftkeyPaint( void );
JKBool JkGetSoftkeyUpdate( void );
JKSint32 JkSoftkeyGetScrollArrowState( void );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
