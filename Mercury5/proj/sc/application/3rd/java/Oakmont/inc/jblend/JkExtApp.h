/**
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkExtApp.h
 * External Application Control JSI
 */
/**
 * @addtogroup External_Application_Control_JSI
 * @{
 */


#ifndef ___MIDPSYS_JK_EXTAPP_H
#define ___MIDPSYS_JK_EXTAPP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * The scheme of the URL to which connection was requested is not supported.
 */
#define JK_EXTAPP_UNSUPPORTED_CONNECTION        0

/**
 * The URL connection request was accepted. The application is started
 * immediately in a task context separate from the JVM task.
 */
#define JK_EXTAPP_CONNECT_IMMEDIATE             1

/**
 * The URL connection request was accepted. The application is started
 * immediately after the Java execution environment terminates.
 */
#define JK_EXTAPP_CONNECT_LATER                2

/**
 * Requests a connection to the designated URL.
 *
 * @param url    The destination URL
 * @param length The length of the destination URL string
 * @return       Return one of the following.<br>
 *               #JK_EXTAPP_CONNECT_IMMEDIATE <br>
 *               #JK_EXTAPP_CONNECT_LATER <br>
 *               #JK_EXTAPP_UNSUPPORTED_CONNECTION
 *
 * Execute a native application for making connection to the URL designated in 
 * the <i>url</i> parameter.
 * This function corresponds to the <code>javax.microedition.midlet.MIDlet
 * </code> class
 * <code>platformRequest</code> method.
 * Of the processings to be performed in the <code>platformRequest</code> method, 
 * the ones mandated by the MIDP specification are as follows.
 * - If the URL specified refers to a MIDlet suite (either a JAD file or a JAR file), 
 *   the native application handling the request MUST interpret this as a request 
 *   for MIDlet installation.
 * - If the URL specified is of the form tel:<number>, as specified in RFC2806, 
 *   then the native application handling the request MUST interpret this as a 
 *   request to initiate a voice call. 
 * .
 * For details of processing for the URL given in the <i>url</i> parameter,
 * see the explanations of the <code>javax.microedition.midlet.MIDlet</code> 
 * class <code>platformRequest</code> method in the MIDP specification.
 * 
 * Implement so that when this function is called, the native application 
 * for connecting to the designated URL does one of the following:
 * 1) Runs immediately, 2) Runs after the MIDlet exits, or 3) Does not run.
 * These three options are explained below.
 * 
 * <ol>
 * <li>Run immediately. <br>
 *   If the following conditions are met, start the application for URL connection, running it
 *   in a task separate from the JVM task and displaying it in the foreground.
 *   <ul>
 *   <li> The designated URL scheme is supported.
 *   <li> The designated application can be run without terminating the JVM.
 *        Running the designated application concurrently with the JVM is 
 *        the basic implementation that conforms to the MIDP specification.
 *        As a special measure, however, performing the operation in JVM suspended 
 *        state may be allowed. This implementation is also in this category.
 *   </ul>
 *   In this case, return #JK_EXTAPP_CONNECT_IMMEDIATE.
 *   Implement this function only to request starting of the native application,
 *   returning control immediately to the caller.
 *   Do not employ an implementation that launches the application in this function
 *   and does not return to the caller of this function until the application terminates.
 *   </p><p>
 *   Consult Sun or the communication operator about whether or not performing 
 *   the processing in JVM suspended state is approved.
 *   </p><p>
 * Even after #JK_EXTAPP_CONNECT_IMMEDIATE is returned, the JVM task continues
 * to function normally.
 * 
 * <li> Run after the MIDlet exits. <br>
 *   Even though the designated URL scheme is supported,
 *   if the application to be newly launched cannnot run unless the JVM task is
 *   suspended first due to a conflict for screen or resources between the 
 *   JVM task and the application, start the native application as soon as 
 *   the MIDlet terminates, and connect to the designated URL. 
 *   </p><p>
 *   In this case, copy the passed destination URL string to a native system memory
 *   area and return #JK_EXTAPP_CONNECT_LATER.
 *   Discard any previously passed, unprocessed URL, saving only the last passed URL. 
 *   <p>
 *   When this function returns #JK_EXTAPP_CONNECT_LATER, the 
 *   <code>platformRequest</code> method returns "true" to let the MIDlet know
 *   that it must exit so a native application can be executed. 
 *   Whether the MIDlet actually exits as a result is dependent on the MIDlet.
 * 
 * <li> Do not run. <br>
 *   Return #JK_EXTAPP_UNSUPPORTED_CONNECTION in either of the following cases.
 *   <ul>
 *   <li> The designated URL scheme is not supported.
 *   <li> The designated string is not a proper URL string. 
 *   </ul>
 * </ol>
 * 
 * When #JK_EXTAPP_CONNECT_IMMEDIATE is returned and an application launched,
 * or when #JK_EXTAPP_UNSUPPORTED_CONNECTION is returned, discard the
 * requested destination URL remembered from the previous time this function
 * was called.
 * 
 * When #JK_EXTAPP_CONNECT_LATER is returned, depending on the MIDlet it is possible
 * that this function will be called again after the function returns to its caller
 * and before the MIDlet exits. In such a case, rather than launching a native 
 * application successively for each designated URL, start a native application only
 * for the last designated URL.
 * 
 * When JK_NULL was designated as the <i>url</i> parameter, discard any requested
 * destination URL remembered from the previous time this function was called, 
 * and return #JK_EXTAPP_CONNECT_IMMEDIATE.
 * 
 * If a native application launched by this function executes features that may incur
 * charges, such as voice callout or HTTP communication, user confirmation must first
 * be obtained by a dialog display or other means.
 * This confirmation is similar to the MIDP permission confirmation 
 * functionality because both of them check with the user for confirmation 
 * before allowing the use of the feature. 
 * However, the confirmation must be implemented by a means other than the 
 * MIDP security framework.
 * 
 * The MIDP states the following specification regarding the confirmation.
 * - The confirmation must be implemented by means other than the MIDP security framework.
 * - The confirmation detail is implementation-dependent.
 * .
 * 
 * The device manufacturer needs to implement an original user confirmation feature 
 * based on the specification of the <code>platformRequest</code> method.
 * 
 */
JKSint32 JkExtRequestConnection( const JKWChar *url, JKSint32 length );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
