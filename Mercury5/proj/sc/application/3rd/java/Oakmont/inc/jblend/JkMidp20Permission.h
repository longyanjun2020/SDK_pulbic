/**
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMidp20Permission.h
 *   Permission Control JSI
 */
/**
 * @addtogroup Permission_Control_JSI
 * @{
 */

#ifndef ___SYS_JK_MIDP20PERMISSION_H
#define ___SYS_JK_MIDP20PERMISSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * Permission scope: Private
 *
 * Indicates that the permission name is not made public. 
 * If the permission name is made public, a Java application 
 * can find out the permission setting using the <code>javax.microedition.midlet.MIDlet</code> 
 * class <code>checkPermission</code> method. 
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_ISPRIVATE         (0x1000)

/**
 * Permission level: Allowed
 * 
 * The Java application is allowed to use the feature without confirming with the user. 
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 * 
 */
#define JK_MIDP20PERMISSION_STATE_ALLOWED     (0x100)

/**
 * Permission level: User
 *
 * Indicates that the user must be asked whether the Java application is allowed to use a feature.
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_STATE_USER        (0x200)

/**
 * Permission level: Not exist
 *
 * Indicates that the permission for use of the feature does not exist in the protection 
 * domain to which the Java application belongs.
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState().
 */
#define JK_MIDP20PERMISSION_STATE_NOT_EXIST   (0x400)

/**
 * Interaction result: Allowed
 * 
 * Indicates that the user allowed the Java application to use a requested feature. 
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_RESULT_ALLOWED    (0x10)

/**
 * Interaction result: Denied
 *
 * Indicates that the user refused to allow the Java application to use a requested feature. 
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_RESULT_DENIED     (0x20)

/**
 * Interaction mode: Blanket mode
 * 
 * Indicates that if the user allows use of a feature, 
 * the permission is valid while the Java application is running, 
 * and the permission applies thereafter.
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState() and 
 * JkMidp20PermissionGetInteractionModes().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_MODE_BLANKET      (0x1)

/**
 * Interaction mode: Session mode
 *
 * Indicates that if the user allows use of a feature, the permission is valid
 * during the current Java application session.
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState() and 
 * JkMidp20PermissionGetInteractionModes().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_MODE_SESSION      (0x2)

/**
 * Interaction mode: Oneshot mode
 * 
 * Indicates that if the user allows use of a feature, the permission is valid only this time.
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState() and 
 * JkMidp20PermissionGetInteractionModes().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_MODE_ONESHOT      (0x4)

/**
 * Interaction mode: No mode
 * 
 * Indicates that use of the feature is not permitted.
 * 
 * The native system uses this in a return value of JkMidp20PermissionGetState() and 
 * JkMidp20PermissionGetInteractionModes().
 * JBlend also uses this in a parameter passed to JkMidp20PermissionSetState().
 */
#define JK_MIDP20PERMISSION_MODE_NO           (0x8)

/**
 *  Permission conflict state: No conflict
 *
 * This is passed by JkMidp20PermissionSetState() as a return value.
 */
#define JK_MIDP20PERMISSION_CONFLICT_NORMAL      0

/**
 *  Permission conflict state: Alert message required
 *
 * This is passed by JkMidp20PermissionSetState() as a return value.
 */
#define JK_MIDP20PERMISSION_CONFLICT_ALERT       1

/**
 *  Permission conflict state: Mutual exclusion processing required
 *
 * This is passed by JkMidp20PermissionSetState() as a return value.
 */
#define JK_MIDP20PERMISSION_CONFLICT_EXCLUSIVE   2

/**
 *  Gets the total number of features for which permission is required. 
 *
 * @return
 *        Return the number of native system features for which 
 *        permission is required.
 *        Return a negative value if the function fails. 
 *        If a negative value is returned, the JVM terminates forcibly.
 */
JKSint32 JkMidp20PermissionGetNumPermissions(void);

/**
 *  Gets the permission name. 
 *
 * @param index
 *        The index to a feature whose permission name is acquired.
 *        The index is a zero-based number. 
 * @param retStr
 *        A pointer to the buffer for storing the permission name.
 * @return
 *        Return the permission name length in number of characters, 
 *        or a negative value if it fails.
 *        If a negative value is returned, the JVM terminates forcibly.
 *
 *  Store in the memory area indicated by <i>retStr</i> the permission name 
 *  of the feature corresponding to <i>index</i>.
 *
 *  The memory area indicated by <i>retStr</i> can hold a data length of up to 256 characters.
 *  
 *  A permission name is the name of a feature for which permission is required.
 */
JKSint32 JkMidp20PermissionGetPermissionName(JKSint32 index, JKWChar *retStr);

/**
 *  Gets the setting status of permission for use of the designated feature.
 * 
 * @param index
 *        The index to a feature whose permission setting is acquired.
 *        The index is a zero-based number. 
 * @return
 *        Return a value consisting of the bit-wise OR of a combination of 
 *        the constants below representing permission setting.
 *        <dl>
 *         <dt> #JK_MIDP20PERMISSION_ISPRIVATE
 *         <dd>Set this bit if the feature is not disclosed to Java applications. 
 *         <dt>A constant named starting with JK_MIDP20PERMISSION_STATE_
 *         <dd>The permission level to use the feature.
 *         <dt>A constant named starting with JK_MIDP20PERMISSION_RESULT_
 *         <dd>The result of querying the user.
 *             If the permission state is #JK_MIDP20PERMISSION_STATE_USER
 *             and the user has been queried before, designate the interaction result.
 *         <dt>A constant named starting with JK_MIDP20PERMISSION_MODE_
 *         <dd>The current interaction mode.
 *             If the permission state is #JK_MIDP20PERMISSION_STATE_USER,
 *             designate the interaction mode currently set for the Java application.
 *        </dl>
 *        <br>
 *        Return a negative value if the function fails. 
 *        If a negative value is returned, the JVM terminates forcibly.
 *  
 *  Read the permission state of the function corresponding to <i>index</i> from the memory 
 *  area where the previously finalized permission state is temporarily held, and pass it in 
 *  the return value.
 * 
 * If this function is called for a permission which does not exist in the protection 
 * domain to which the Java application belongs, return #JK_MIDP20PERMISSION_STATE_NOT_EXIST.
 */
JKSint32 JkMidp20PermissionGetState(JKSint32 index);

/**
 *  Gets the interaction mode for the designated feature. 
 *
 * @param index
 *        The index to a feature whose interaction mode is acquired.
 *        The index is a zero-based number. 
 * @return
 *        Return a value consisting of the bit-wise OR of a combination of 
 *        the constants below representing interaction modes.
 *        <ul>
 *         <li> #JK_MIDP20PERMISSION_MODE_BLANKET
 *         <li> #JK_MIDP20PERMISSION_MODE_SESSION
 *         <li> #JK_MIDP20PERMISSION_MODE_ONESHOT
 *         <li> #JK_MIDP20PERMISSION_MODE_NO
 *        </ul>
 *        Return a negative value if the function fails. 
 *        If a negative value is returned, the JVM terminates forcibly.
 *<p>
 * Return the combination of interaction modes corresponding to the choices on the
 * permission confirmation dialog when the user is queried about the permission
 * setting of the feature corresponding to <i>index</i>.
 * 
 * JBlend calls this function to determine which choices to offer when querying
 * the user about permission of the running Java application to use a feature. 
 * 
 * The choices displayed to the user correspond as follows to the user interaction mode. 
 * <dl>
 *  <dt> #JK_MIDP20PERMISSION_MODE_BLANKET
 *  <dd>1. Allow and don't ask again
 *  <dd>4. Not now
 *  <dt> #JK_MIDP20PERMISSION_MODE_SESSION
 *  <dd>2. Allow for this session
 *  <dd>4. Not now
 *  <dt> #JK_MIDP20PERMISSION_MODE_ONESHOT
 *  <dd>3. Allow and ask me next time
 *  <dd>4. Not now
 *  <dt> #JK_MIDP20PERMISSION_MODE_NO
 *  <dd>5. Never
 * </dl>
 * 
 * The strings indicating choices on the interaction dialog are 
 * those obtained by JBlend using JkOptionGetString().
 * 
 * MIDP specifies that if "User" is set as the permission level for use of a feature,
 * the user must be able to deny use of that feature at any time. 
 * Accordingly, #JK_MIDP20PERMISSION_MODE_NO must always be included as one of the 
 * choices regardless of the feature. 
 * 
 * This function is not called if the native system uses its own custom permission
 * confirmation dialog. 
 * This function is also not called for features not supported by the native system. 
 */
JKSint32 JkMidp20PermissionGetInteractionModes(JKSint32 index);

/**
 * Notifies the native system of the start of a permission state change operation.
 *
 * @return
 *   Return 0 if the function succeeds.
 *   Return a negative value if the function fails. 
 *   If a negative value is returned, the JVM terminates forcibly.
 *
 * This function is called when a user permission confirmation operation is started. 
 * When this function is called, in the native system copy the previously finalized 
 * permission state from the memory area where it is temporarily held to the memory 
 * area holding the state currently being confirmed. 
 * 
 * During the interval from invocation of this function until 
 * JkMidp20PermissionEndModifyStates() is called, an operation for
 * confirming permission with the user takes place. 
 * If the permission state changes as a result of the operation, 
 * in the native system update the memory area holding the state currently being confirmed,
 * but do not update the permanent setting saved in storage for the MIDlet suite
 * or the memory area temporarily holding the previously finalized state.
 * 
 * After the operation for confirming permission with the user ends and the
 * permission setting state is finalized, JkMidp20PermissionEndModifyStates() 
 * is called.
 * @see JkMidp20PermissionEndModifyStates()
 */
JKSint32 JkMidp20PermissionBeginModifyStates(void);

/**
 * Notifies the native system of completion of a permission state change operation.
 *
 * @return
 *   Return 0 if the function succeeds.
 *   Return a negative value if the function fails. 
 *   If a negative value is returned, the JVM terminates forcibly.
 *
 * This function is called when an operation for confirming permission with the 
 * user ends and the permission setting state is finalized.
 * When this function is called, in the native system write the permission
 * state currently being confirmed to the MIDlet suite permanent information
 * storage area, and at the same time write this state to the work area for
 * temporarily holding the previously finalized permission state.
 *
 * If the user cancels the permission confirmation operation before it is 
 * completed, JkMidp20PermissionBeginModifyStates() will be called again and 
 * the operation restarted. For this reason, JkMidp20PermissionBeginModifyStates()  
 * and JkMidp20PermissionEndModifyStates() will not necessarily be called for an 
 * equal number of times.
 * @see JkMidp20PermissionBeginModifyStates()
 */
JKSint32 JkMidp20PermissionEndModifyStates(void);

/**
 *  Sets the setting status of permission for use of the designated feature.
 *
 * @param index
 *        The index to a feature whose permission setting is updated.
 *        The index is a zero-based number. 
 * @param state
 *        A value consisting of the bit-wise OR of a combination of 
 *        the constants below representing permission setting.
 *        <dl>
 *         <dt> #JK_MIDP20PERMISSION_ISPRIVATE
 *         <dd>This bit is set if the feature is not disclosed to Java applications. 
 *             The value obtained by #JkMidp20PermissionGetState() is passed transparently.
 *         <dt>A constant named starting with JK_MIDP20PERMISSION_STATE_
 *         <dd>The permission level to use the feature.
 *         <dt>A constant named starting with JK_MIDP20PERMISSION_RESULT_
 *         <dd>The current interaction mode.
 *         <dt>A constant named starting with JK_MIDP20PERMISSION_MODE_
 *         <dd>The selected interaction mode.
 *        </dl>
 * @return
 *        Return one of the following constants indicating the conflict state 
 *        resulting from permission setting.  
 *        <ul>
 *         <li> #JK_MIDP20PERMISSION_CONFLICT_NORMAL
 *         <li> #JK_MIDP20PERMISSION_CONFLICT_ALERT
 *         <li> #JK_MIDP20PERMISSION_CONFLICT_EXCLUSIVE
 *        </ul>
 *        Return a negative value if the function fails. 
 *        If a negative value is returned, the JVM terminates forcibly.
 * <p>
 *  In this function, update the memory area holding the permission state currently being confirmed,
 *  but do not update the permanent information for the MIDlet suite saved in storage
 *  or the work area temporarily holding the previously finalized permission state.
 *  Update the MIDlet suite permanent information and the previously finalized state when
 *  JkMidp20PermissionEndModifyStates() is called.
 * 
 * JBlend displays a permission alert dialog or permission exclusion dialog
 * based on the return value of this function. 
 * 
 * This function is not called for features not supported by the native system. 
 * @see JkMidp20PermissionBeginModifyStates()
 * @see JkMidp20PermissionEndModifyStates()
 */
JKSint32 JkMidp20PermissionSetState(JKSint32 index, JKSint32 state);

/**
 *  Gets the title string displayed in the permission confirmation dialog.
 *
 * @param index
 *        The index to a feature for which the permission is confirmed.
 *        The index is a zero-based number. 
 * @param retStr
 *        A pointer to the memory area for putting the title string created by the native system.
 * @return
 *        Return the number of characters in the title string, 
 *        or a negative value if it fails.
 *        If a negative value is returned, the JVM terminates forcibly.
 *
 *  Create a string to be displayed as the title of the permission confirmation
 *  dialog when the user is queried about the permission of the feature corresponding to <i>index</i>,
 *  and put it in the memory area indicated by <i>retStr</i>.
 *  The memory area indicated by <i>retStr</i> can hold a data length of up to 256 characters.
 *  
 */
JKSint32 JkMidp20PermissionGetTitle(JKSint32 index, JKWChar *retStr);

/**
 *  Gets the message displayed in the permission confirmation dialog.
 *
 * @param index
 *        The index to a feature for which the permission is confirmed.
 *        The index is a zero-based number. 
 * @param argStr
 *        A pointer to the memory area holding the message parameter string(s) set in advance
 *        by JBlend for each feature.
 *        If multiple strings are stored, "@\0@\0" is used to delimit each string.
 * @param argSize
 *        The length (in characters) of the strings stored in the buffer 
 *        pointed to by the <i>argStr</i> parameter.
 *        If multiple strings are designated in <i>argStr</i>, the number of characters passed
 *        includes the string delimiters. 
 * @param retStr
 *        A pointer to the memory area for putting the message string created by the native system.
 * 
 * @return
 *        Return the number of characters in the message string, 
 *        or a negative value if it fails.
 *        If a negative value is returned, the JVM terminates forcibly.
 *  
 *  Using the parameter string(s) passed in <i>argStr</i>, construct the message
 *  to be displayed in the permission confirmation dialog when querying
 *  the user about the permission of the feature corresponding to <i>index</i>, and put the
 *  message in the memory area indicated by <i>retStr</i>.
 *  The memory area pointed to by the <i>retStr</i> parameter can hold a 
 *  data size of up to the one indicated by the <i>argSize</i> parameter 
 *  plus 256 characters. 
 *  
 *  For details of the parameter strings passed in <i>argStr</i>, see the page explaining permission
 *  control in the interface references for each of the features for which permission is required.
 * 
 * This function is not called if the native system uses its own custom permission
 * confirmation dialog. 
 */
JKSint32 JkMidp20PermissionGetMessage(JKSint32 index,
                                const JKWChar *argStr,
                                JKSint32 argSize,
                                JKWChar *retStr);

/**
 *  Gets the message displayed in the permission alert dialog or permission exclusion dialog. 
 *
 * @param retStr
 *        A pointer to the memory area for putting the message string created by the native system.
 * 
 * @return
 *        Return the number of characters in the message string,
 *        or a negative value if it fails.
 *        If a negative value is returned, the JVM terminates forcibly.
 *
 *  Create the message to be displayed by JBlend in the permission alert dialog or
 *  permission exclusion dialog when a permission conflict arises, and put it in the 
 *  memory area indicated by <i>retStr</i>.
 *  The memory area indicated by <i>retStr</i> can hold a data length of up to 256 characters.
 *  
 * This function is not called if the native system uses its own custom permission
 * confirmation dialog. 
 */
JKSint32 JkMidp20PermissionGetAlertMessage(JKWChar *retStr);

/**
 *  Gets the title string displayed in the permission alert dialog or permission exclusion dialog. 
 * 
 * @param retStr
 *        A pointer to the memory area for putting the title string created by the native system.
 * 
 * @return
 *        Return the number of characters in the title string,
 *        or a negative value if it fails.
 *        If a negative value is returned, the JVM terminates forcibly.
 *  
 *  Create the title string to be displayed by JBlend in the permission alert dialog or
 *  permission exclusion dialog when a permission conflict arises, and put it in the 
 *  memory area indicated by <i>retStr</i>.
 *  The memory area indicated by <i>retStr</i> can hold a data length of up to 256 characters.
 *  
 * This function is not called if the native system uses its own custom permission
 * confirmation dialog. 
 */
JKSint32 JkMidp20PermissionGetAlertTitle(JKWChar *retStr);

/**
 *  Gets the choices to be displayed in the permission exclusion dialog.
 *
 * @param choice0Str
 *        A pointer to the memory area for putting the first choice string created
 *        by the native system. 
 * @param choice0Size
 *        A pointer to the memory area for putting the length (number of characters)
 *        of the first choice string. 
 * @param choice1Str
 *        A pointer to the memory area for putting the second choice string created
 *        by the native system. 
 * @param choice1Size
 *        A pointer to the memory area for putting the length (number of characters)
 *        of the second choice string. 
 * @return
 *        Return positive value if the operation succeeds. Return negative value if it fails.
 *        If a negative value is returned, the JVM terminates forcibly.
 *
 *  Create the strings to be displayed as choices in the permission exclusion dialog, 
 *  and put the string and length (number of characters) of each choice string in
 *  the memory areas indicated by the respective parameters.
 *  The memory areas indicated by <i>choice0Str</i> and <i>choice0Str</i> can 
 *  hold a data length of up to 256 characters.
 *  
 *  A permission exclusion dialog is a dialog displayed by JBlend when a permission
 *  conflict arises and the user must be asked to make a choice between the conflicting
 *  settings. 
 *  A permission exclusion dialog consists of the title obtained by
 *  #JkMidp20PermissionGetAlertTitle(), the message string obtained by
 *  #JkMidp20PermissionGetAlertMessage(), and a radio button with the
 *  two choices obtained by this function.
 *  
 * This function is not called if the native system uses its own custom permission
 * confirmation dialog. 
 */
JKSint32 JkMidp20PermissionGetExclusiveChoices(JKWChar *choice0Str, JKSint32 *choice0Size, JKWChar *choice1Str, JKSint32 *choice1Size);

/**
 *  Sets the choice selected by the user in the permission exclusion dialog. 
 *
 * @param choice
 *        An index indicating the choice selected by the user. Either 0 or 1 is designated. 
 * @return
 *        Return #JK_MIDP20PERMISSION_CONFLICT_NORMAL if the setting succeeds without 
 *        resulting in a conflict. If the setting results in a conflict of which the user
 *        needs to be alerted, return #JK_MIDP20PERMISSION_CONFLICT_ALERT.
 *        Return negative value if it fails.
 *        If a negative value is returned, the JVM terminates forcibly.
 *  
 *  Change the permission settings of the two features, based on the choice selected by the user. 
 *  
 *  In this function, update the memory area holding the permission state currently being confirmed,
 *  but do not update the permanent information for the MIDlet suite saved in storage
 *  or the work area temporarily holding the previously finalized permission state.
 *  Update the MIDlet suite permanent information and the previously finalized state when
 *  JkMidp20PermissionEndModifyStates() is called.
 *  
 *  This function is called to notify the native system of the choice selected by the user
 *  in a permission exclusion dialog displayed when a permission conflict arises. 
 *  
 *  If this function returns #JK_MIDP20PERMISSION_CONFLICT_ALERT, JBlend calls
 *  JkMidp20PermissionGetAlertTitle() and JkMidp20PermissionGetAlertMessage() to get
 *  the title and message to be displayed in the permission alert dialog, then displays
 *  the permission alert dialog.
 *  
 * This function is not called if the native system uses its own custom permission
 * confirmation dialog. 
 * @see JkMidp20PermissionBeginModifyStates()
 * @see JkMidp20PermissionEndModifyStates()
 */
JKSint32 JkMidp20PermissionSetExclusiveChoice(JKSint32 choice);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
