/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkPushRegistry.h
 *  Push Connection Registration, Information Acquisition, and Activation Time Registration
 */
/**
 * @addtogroup Module_Push_Registration
 * @{
 */
#ifndef __PUSH_JK_PUSHREGISTRY_H
#define __PUSH_JK_PUSHREGISTRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 *  Values returned by the individual functions
 */
/**
 *  Succeeded.
 */
#define     JK_PUSH_OK                           (0)
/**
 *  The push connection string (URL) is invalid.
 */
#define     JK_PUSH_ERROR_INVALID_CONNECTION     (-1)
/**
 *  The filter string is invalid.
 */
#define     JK_PUSH_ERROR_INVALID_FILTER         (-2)
/**
 *  The protocol designated in the push connection information is 
 *  not supported for push delivery.
 */
#define     JK_PUSH_ERROR_UNSUPPORTED_PROTOCOL   (-3)
/**
 *  The designated push connection is already registered.
 */
#define     JK_PUSH_ERROR_ALREADY_REGISTERED     (-4)
/**
 *  Registration failed due to insufficient resources.
 */
#define     JK_PUSH_ERROR_INSUFFICIENT_RESOURCE  (-5)
/**
 *  The designated URL is not registered for push connection.
 */
#define     JK_PUSH_ERROR_CONNECTION_NOT_FOUND   (-6)
/**
 *  The invoked function is not supported.
 */
#define     JK_PUSH_UNSUPPORTED_FUNCTION         (-7)
/**
 *  The function for passing push connection information returned an error.
 */
#define     JK_PUSH_ERROR_CALLBACK_FAILED        (-8)
/**
 *  Internal error.
 */
#define     JK_PUSH_ERROR_INTERNAL               (-100)

/**
 *  A data structure indicating information identifying a MIDlet suite.
 */
typedef struct JKT_Push_SuiteInfo {
    /**
     *  A pointer to the memory location of the MIDlet suite name.\ This string is the same as the value registered with the MIDlet-Name attribute.
     */
    JKWChar*            name;
    /**
     *  The length (number of characters) of the MIDlet suite name.
     */
    JKSint32            nameLength;
    /**
     *  A pointer to the memory area holding the name of the organization providing the MIDlet suite.\ This string is the same as the value registered with the MIDlet-Vendor attribute.
     */
    JKWChar*            vendor;
    /**
     *  The length (number of characters) of the MIDlet suite vendor name.
     */
    JKSint32            vendorLength;
} JKT_Push_SuiteInfo;

/**
 *  A data structure indicating push connection information.
 */
typedef struct JKT_Push_ConnectionInfo {
    /**
     *  A pointer to the memory area holding the connection string (URL).
     */
    JKWChar*            connection;
    /**
     *  The length (number of characters) of the connection string (URL).
     */
    JKSint32            connectionLength;
    /**
     *  A pointer to the memory area holding the class name of the MIDlet to be invoked.\ The class name has the same format as that indicated in the MIDlet-Push-@<n@> attribute.
     */
    JKWChar*            midlet;
    /**
     *  The length (number of characters) of the class name of the MIDlet
     */
    JKSint32            midletLength;
    /**
     *  A filter string to restrict which senders are valid for push event launching.
     */
    JKWChar*            filter;
    /**
     *  The length (number of characters) of the filter string
     */
    JKSint32            filterLength;
    /**
     *  Information identifying the MIDlet suite that contains the MIDlet to be activated by a push connection.
     */
    JKT_Push_SuiteInfo  suite;

} JKT_Push_ConnectionInfo;

/**
 * @} end of group
 */
/**
 * @addtogroup Module_Alarm_Registration
 * @{
 */

/**
 *  A data structure indicating the time of MIDlet activation. 
 *
 *  The time is stored in the structure as elapsed milliseconds from 00:00:00.000 GMT, January 1, 1970.
 */
typedef struct JKT_Push_AlarmDate {
    /**
     *  The high 32 bits of the time information.
     */
    JKUint32            high;
    /**
     *  The low 32 bits of the time information.
     */
    JKUint32            low;
} JKT_Push_AlarmDate;

/**
 *  A data structure indicating information about a MIDlet to be activated by a timer-based alarm.
 */
typedef struct JKT_Push_AlarmInfo {
    /**
     *  A pointer to the memory area holding the class name of the MIDlet to be invoked.\ The class name has the same format as that indicated in the MIDlet-Push-<n> attribute. 
     */
    JKWChar*            midlet;
    /**
     *  The length (number of characters) of the class name of the MIDlet.
     */
    JKSint32            midletLength;
    /**
     *  The time of MIDlet activation.
     */
    JKT_Push_AlarmDate  date;
    /**
     *  Information identifying the MIDlet suite that contains the MIDlet.
     */
    JKT_Push_SuiteInfo  suite;
} JKT_Push_AlarmInfo;

/**
 * @} end of group
 */
/**
 * @addtogroup Module_Push_Registration
 * @{
 */


/**
 *  A data structure for containing identifiers used internally by JBlend.
 *
 *  The information included in this data structure is for private use by JBlend.
 *  The structure is defined here as an incomplete type only for declaring pointer variables.
 */
typedef struct JKT_Push_CallbackContext JKT_Push_CallbackContext;

/**
 *  Requests a list of push connections registered 
 *  for the currently running MIDlet suite.
 *  @param suite      A pointer to a data structure indicating information 
 *                    identifying the currently running MIDlet suite.
 *  @param available  The condition for getting push connection information. 
 *                    Designating #JK_TRUE means only information about 
 *                    connections that can be opened by the MIDlet is requested.
 *  @param context    Pass this value in the <i>context</i> parameter to 
 *                    #AmPushHandleListElement().
 *  @return
 *         \li Return #JK_PUSH_OK if the operation succeeds, or if no push 
 *             connection is registered for the currently running MIDlet suite.
 *         \li Return #JK_PUSH_UNSUPPORTED_FUNCTION if the native system does not support server push.
 *         \li Return #JK_PUSH_ERROR_CALLBACK_FAILED if #JK_FALSE was returned by #AmPushHandleListElement().
 *
 *  This function is called by JBlend when the currently running 
 *  MIDlet invokes the <code>PushRegistry</code> class <code>listConnections</code> method.
 *
 *  When this function is called, the native system should call #AmPushHandleListElement() in this 
 *  function for each URL registered for the MIDlet suite designated in the <i>suite</i> parameter. 
 *  If #JK_TRUE is designated in the <i>available</i> parameter, call #AmPushHandleListElement() only for 
 *  URLs of the connections that can be opened by the MIDlet.
 *  If a value other than #JK_TRUE is designated in <i>available</i>, call #AmPushHandleListElement() for 
 *  all URLs registered for the MIDlet suite designated in the <i>suite</i> parameter. 
 *
 *  If it is not possible to limit processing to the information for the MIDlet suite designated by
 *  the <i>suite</i> parameter, of all the push connection information managed by the native system, call 
 *  #AmPushHandleListElement() for all URLs meeting the condition designated in the <i>available</i> parameter.
 *
 *
 * @see AmPushHandleListElement()
 */
JKSint32 JkPushEnumerateConnections( const JKT_Push_SuiteInfo *suite, JKBool available, 
                                    JKT_Push_CallbackContext *context );

/**
 *              Registers a push connection for the currently running MIDlet suite.
 *  @param info A pointer to the data structure indicating the push connection information.
 *  @return
 *         \li Return #JK_PUSH_OK if the operation succeeds.
 *         \li Return #JK_PUSH_ERROR_INVALID_CONNECTION if the connection string format is invalid or no string was registered.
 *         \li Return #JK_PUSH_ERROR_INVALID_FILTER if the filter string format is invalid or no string was registered.
 *         \li Return #JK_PUSH_ERROR_UNSUPPORTED_PROTOCOL if the native system does not support push delivery by the designated protocol.
 *         \li Return #JK_PUSH_ERROR_ALREADY_REGISTERED if the same connection (URL) is already registered for push. 
 *         \li Return #JK_PUSH_ERROR_INSUFFICIENT_RESOURCE if registration is not possible due to insufficient resources. 
 *         \li Return #JK_PUSH_UNSUPPORTED_FUNCTION if the native system does not support the push functionality.
 *         \li Return #JK_PUSH_ERROR_INTERNAL if registration failed for a reason other than those above.
 *
 *  This function is called by JBlend when the currently running MIDlet invokes the 
 *  <code>PushRegistry</code> class <code>registerConnection</code> method.
 *
 *  Register the push connection for the MIDlet suite provided the following conditions are met:
 *  \li The connection string and the filter string are valid in the native system and in the protocol stack.
 *  \li The same push connection is not already registered.
 *
 *  The conditions checked by JBlend before invoking this function are:
 *  \li The running MIDlet has the necessary permission for registering a push connection.
 *  \li The class designated for the MIDlet is included in the currently running MIDlet suite. 
 *  \li The class name designated for the MIDlet is indicated in the JAD 
 *      file or the manifest file with one of the 'MIDlet-<n>' attributes.
 *  \li The scheme of the designated push connection (URL) is valid for the 
 *      <code>javax.microedition.io.Connector</code> class <code>open</code> method.
 *
 *
 * @see JkPushUnregisterConnection()
 */
JKSint32 JkPushRegisterConnection( const JKT_Push_ConnectionInfo *info );

/**
 *                    Unregister a push connection associated with the 
 *                    currently running MIDlet suite.
 *  @param connection A pointer to the memory area holding the connection 
 *                    string (URL) to be unregistered.
 *  @param connectionLength
 *                    The length (number of characters) of the connection string (URL).
 *  @return
 *         \li Return #JK_PUSH_OK if the operation succeeds.
 *         \li Return #JK_PUSH_ERROR_CONNECTION_NOT_FOUND if the designated connection is not registered.
 *         \li Return #JK_PUSH_UNSUPPORTED_FUNCTION if the native system does not support the push functionality.
 *         \li Return #JK_PUSH_ERROR_INTERNAL if the operation failed for a reason other than the above.
 *
 *  This function is called by JBlend when the currently running MIDlet invokes the 
 *  <code>PushRegistry</code> class <code>unregisterConnection</code> method.
 *
 *  Remove the connection registration indicated by the parameters.
 *
 *  Before invoking this function, JBlend checks the following condition:
 *  \li The connection is registered with the MIDlet in the currently running MIDlet suite.<br>
 *   (JBlend tests the condition above by invoking #JkPushQueryConnectionInfo().)
 *
 *
 * @see JkPushRegisterConnection()
 */
JKSint32 JkPushUnregisterConnection( const JKWChar *connection, JKSint32 connectionLength  );

/**
 * @} end of group
 */
/**
 * @addtogroup Module_Alarm_Registration
 * @{
 */

/**
 *                  Registers a time to launch the MIDlet in the currently 
 *                  running MIDlet suite.
 *  @param info     A pointer to the data structure holding the alarm-based 
 *                  activation setting for the MIDlet.
 *  @param previous A pointer to a data structure for storing the previous alarm-based 
 *                  activation setting.  If there is no previous setting, the high 
 *                  and low members of this structure must be zero.
 *  @return
 *         \li Return #JK_PUSH_OK if the operation succeeds.
 *         \li Return #JK_PUSH_ERROR_INSUFFICIENT_RESOURCE if registration failed due to insufficient resources.
 *         \li Return #JK_PUSH_UNSUPPORTED_FUNCTION if the native system does not support the push functionality or does not support alarm-based launching.
 *         \li Return #JK_PUSH_ERROR_INTERNAL if registration failed for a reason other than the above.
 *
 *  This function is called by JBlend when the currently running MIDlet invokes the 
 *  <code>PushRegistry</code> class <code>registerAlarm</code> method.
 *
 *  Register the designated time as the time to activate the MIDlet.
 *  
 *  The conditions checked by JBlend before invoking this function are:
 *  \li The running MIDlet has the necessary permission for registering an activation time. 
 *  \li The class designated for the MIDlet is included in the currently running MIDlet suite.
 *  \li The class name designated for the MIDlet is indicated in the JAD file or the manifest file with one of 
 *   the 'MIDlet-@<n@>' attributes.
 *
 *
 */
JKSint32 JkPushRegisterAlarm( const JKT_Push_AlarmInfo *info, JKT_Push_AlarmDate *previous );

/**
 * @} end of group
 */
/**
 * @addtogroup Module_Push_Registration
 * @{
 */

/**
 *                    Queries registration information about a push connection. 
 *  @param connection A pointer to the buffer holding the connection string (URL).
 *  @param connectionLength
 *                    The length (number of characters) of the connection string (URL).
 *  @param context    Pass this value in the <i>context</i> parameter to 
 *                    #AmPushHandleConnectionInfo().
 *  @return
 *         \li Return #JK_PUSH_OK if the operation succeeds.
 *         \li Return #JK_PUSH_ERROR_CONNECTION_NOT_FOUND if the designated connection is not registered for push.
 *         \li Return #JK_PUSH_ERROR_CALLBACK_FAILED if #AmPushHandleConnectionInfo() returned #JK_FALSE.
 *         \li Return #JK_PUSH_UNSUPPORTED_FUNCTION if the native system does not support the push functionality.
 *
 *  This function is called by JBlend to retrieve registration information when the following methods
 *  are invoked by the currently running MIDlet.
 *  \li <code>PushRegistry</code> class <code>getMIDlet</code> method
 *  \li <code>PushRegistry</code> class <code>getFilter</code> method
 *  \li <code>PushRegistry</code> class <code>unregisterConnection</code> method
 *  \li <code>PushRegistry</code> class <code>registerConnection</code> method
 *  \li <code>Connector</code> class <code>open</code> method
 *
 *  If the designated connection is registered for push, invoke #AmPushHandleConnectionInfo() in this function. 
 *
 * @see AmPushHandleConnectionInfo()
 */
JKSint32 JkPushQueryConnectionInfo( const JKWChar *connection, JKSint32 connectionLength, 
                                    JKT_Push_CallbackContext *context );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
