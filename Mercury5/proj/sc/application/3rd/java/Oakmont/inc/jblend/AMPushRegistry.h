/*
 * Copyright 2003-2007 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMPushRegistry.h
 *   Push Connection Information Transfer
 */
/**
 * @addtogroup Module_AM_Push_Registration
 * @{
 */

#ifndef __AM_PUSHREGISTRY_H
#define __AM_PUSHREGISTRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include    "JkTypes.h"
#include	"JkPushRegistry.h"

/**
 *                   Passes a URL string to JBlend indicating a registered 
 *                   push connection.
 * @param context    Pass the same value as that passed to 
 *                   #JkPushEnumerateConnections() in the <i>context</i> parameter.
 * @param connection A pointer to the buffer holding the registered 
 *                   connection string (URL).
 * @param connectionLength  The length (number of characters) of the 
 *                          connection string (URL).
 * @param suite      A pointer to a structure with information identifying 
 *                   the MIDlet suite for which the connection is registered.
 * @return
 *         - #JK_TRUE: succeeded
 *         - #JK_FALSE: Any of the following cases (failed)
 *           - The context parameter is invalid.
 *           - The connection parameter is #JK_NULL or connectionLength 
 *             is zero or a negative value.
 *           - The name member of the structure pointed to by suite 
 *             is #JK_NULL, or nameLength is zero or a negative value.
 *           - The vendor member of the structure pointed to by suite 
 *             is #JK_NULL, or vendorLength is zero or a negative value.
 *
 * This function is defined as a function to be called from 
 * #JkPushEnumerateConnections(). 
 * 
 * The function must be invoked the same number of times as the number 
 * of connections enumurated by #JkPushEnumerateConnections().
 * 
 * If the MIDlet suite designated by the <i>suite</i> parameter is not 
 * the currently running MIDlet suite, JBlend ignores that push 
 * connection and returns #JK_TRUE.
 * 
 * When calling this function only for a URL registered for the 
 * currently running MIDlet suite, and not for all the other push 
 * connections enumerated in #JkPushEnumerateConnections(), designate 
 * #JK_NULL for the <i>suite</i> parameter. 
 *
 * If calls to this function are not limited to the currently running 
 * MIDlet suite,  valid MIDlet suite names (name member) and organization 
 * names (vendor member) must be designated in the structure pointed to 
 * by the <i>suite</i> parameter. 
 *
 * @see JkPushEnumerateConnections()
 */
JKBool AmPushHandleListElement( JKT_Push_CallbackContext *context, 
                                const JKWChar *connection, JKSint32 connectionLength, const JKT_Push_SuiteInfo *suite );

/**
 *                Passes push connection information to JBlend.
 * @param context Pass the same value as that passed to 
 *                #JkPushQueryConnectionInfo() in the <i>context</i> parameter.
 * @param info    A pointer to the structure with information about the 
 *                connection queried by #JkPushQueryConnectionInfo().
 * @return
 *        - #JK_TRUE: succeeded
 *        - #JK_FALSE: Any of the following cases (failed)
 *           - The context parameter is invalid.
 *           - This function was called more than once for the structure 
 *             pointed to by the context parameter.
 *           - The info parameter is #JK_NULL.
 *           - The connection member of the structure pointed to by info is 
 *             #JK_NULL, or connectionLength is zero or a negative value.
 *           - The midlet member of the structure pointed to by info is 
 *             #JK_NULL, or midletLength is zero or a negative value.
 *           - The <i>name</i> member of the JKT_Push_SuiteInfo structure 
 *             pointed to by the <i>suite</i> member of the structure pointed 
 *             to by <i>info</i> is JK_NULL, or the <i>nameLength</i> member 
 *             is zero or a negative value.
 *           - The <i>vendor</i> member of the JKT_Push_SuiteInfo structure 
 *             pointed to by the <i>suite</i> member of the structure pointed 
 *             to by <i>info</i> is #JK_NULL, or the <i>vendorLength</i> 
 *             member is zero or a negative value.
 *
 *  This function is defined as a function to be called from 
 *  #JkPushQueryConnectionInfo(). 
 *
 *  This function can be called only once in #JkPushQueryConnectionInfo().
 * 
 * @see JkPushQueryConnectionInfo()
 */
JKBool AmPushHandleConnectionInfo( JKT_Push_CallbackContext *context, const JKT_Push_ConnectionInfo *info );

/**
 * @} end of group
 */
/**
 * @addtogroup Push_Invocation
 * @{
 */

/**
 *  Checks whether or not the designated MIDlet is currently running.
 *  @param className
 *         A pointer to the memory area holding the MIDlet class name.
 *         The class name should be described in the same format of the MIDlet-Push-<n> attribute value.
 *  @param classNameLength
 *         The number of the characters in the string indicated by <i>className</i>.
 *  @return
 *         - #JK_TRUE: Running
 *         - #JK_FALSE: Not running 
 *
 * This function returns whether or not the MIDlet indicated by <i>className</i> is currently running.
 */

JKBool AmPushIsApplicationRunning(const JKWChar* className, JKSint32 classNameLength);

#ifdef __cplusplus
}
#endif
#endif

/**
 * @}
 */
