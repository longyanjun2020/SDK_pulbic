/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkVideoPermissionDialog.h
 *   Native System Original Permission Dialog
 */
/**
 * @addtogroup Native_System_Original_Permission_Dialog_JSI
 * @{
 */

#ifndef ___SYS_JK_VIDEOPERMISSIONDIALOG_H
#define ___SYS_JK_VIDEOPERMISSIONDIALOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkGraphics.h"

/**
 *  Draws a native system original permission confirmation dialog.
 *  
 * @param g
 *        The handle of the graphics context.
 * @param index
 *        An index to a function for which permission is set. 
 *        The index is a zero-based number.
 * @param keyCode
 *        The key code. 
 *        A constant whose name starts with AM_KEYCODE_, which is defined 
 *        in @ref Device_Event_Notification_JBI "Device Event Notification JBI", 
 *        or a constant added originally by the device manufacturer (a value greater 
 *        than or equal to #AM_KEYCODE_USER_BASE). 
 *        -1 is passed when no key entry is detected.
 * @param titleStr
 *        A pointer to the memory area holding the title text.
 *        The string passed to JBlend by JkMidp20PermissionGetTitle() is designated.
 * @param titleSize
 *        The number of characters in the string indicated by <i>titleStr</i>.
 * @param messageStr
 *        A pointer to the memory area holding the message text.
 *        The string passed to JBlend by JkMidp20PermissionGetMessage() is designated.
 * @param messageSize
 *        The number of characters in the string indicated by <i>messageStr</i>.
 * @return
 *        When user has completed permission confirmation and allowed the use of 
 *        the feature by Java application, return #JK_MIDP20PERMISSION_RESULT_ALLOWED.<br>
 *        When user has refused to use the feature, return #JK_MIDP20PERMISSION_RESULT_DENIED.<br>
 *        When user is still interacting with the dialog, return 0.
 * 
 *  This function is called when the native system uses its own permission 
 *  confirmation dialog.
 *  If the native system does not use its own permission confirmation dialog, 
 *  this function can be implemented as an empty function.
 *  
 *  The following values are set in the graphics context passed in the <i>g</i> parameter. 
 *  <dl>
 *   <dt>Font &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 *   <dd> #JK_FONT_TYPE_DEFAULT
 *   <dt>Drawing color &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 *   <dd> 0x00FFFFFF
 *   <dt>Line style 
 *   <dd> #JK_GRAPHICS_LINE_STYLE_NORMAL
 *   <dt>Clip area 
 *   <dd>Entire virtual screen
 *  </dl>
 *  JBlend fills the virtual screen with the background color (0x00FFFFFF), then calls this function.
 *  In the native system, overwrite the graphics context freely as necessary and draw a
 *  permission confirmation dialog of any kind. 
 *
 *  JBlend calls this function when a custom permission confirmation 
 *  dialog has to be drawn.
 *  Until the user confirms the permission and makes a selection,
 *  JBlend calls this function each time the user inputs a key.
 *
 *  If the user has made selection, return the result.
 *  If the user has not yet completed the selection, return 0.
 *
 *  When this function returns 0, JBlend judges that the user has 
 *  not completed the selection yet and continues displaying of the 
 *  custom permission confirmation dialog.
 *  
 *  When a permission conflict results from the selection made by the user, 
 *  the native system should return 0, after drawing a dialog 
 *  that warns about the conflict and suggests that the user should choose a 
 *  different valid selection. In this way, the native system must continue 
 *  the user interaction until a valid selection is made by the user.
 *  
 *  For detail of the permission conflict, see the MIDP addendum on 
 *  "The Recommended Security Policy for GSM/UMTS Compliant Devices." 
 */
JKSint32 JkVideoDrawPermissionDialog(JKGraphicsContext g, JKSint32 index, JKUint32 keyCode,  
									 const JKWChar * titleStr, JKSint32 titleSize,
									 const JKWChar * messageStr, JKSint32 messageSize);


#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
