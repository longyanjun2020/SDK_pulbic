/*
 * Copyright 2005 Aplix Corporation. All rights reserved.
 */

/***************************************************************************
 * FILE: kjava_sys_push.h
 *
 * DESCRIPTION:
 *      The Push registry interface of KSI.
 *
 * UPDATED DATE:
 *      2005/01/11
 *
 * REVISION:
 *  2005/01/11, Jack Chung, First draft.
 *
 *
 ***************************************************************************/

#ifndef KJAVA_SYS_PUSH_HEADER
#define KJAVA_SYS_PUSH_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#include "jap_head.h" 

#include "Ajms_common.h"
/**
 * @file kjava_sys_push.h
 */
 
 
/**
 * @addtogroup Push_Registry_KSI
 * An interface for performing the MIDP Push Registry feature.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread context,
 *
 * @par Include file 
 * \#include kjava_sys_sock.h
 * @{
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/**
 *        Starts a timer for activating a MIDlet.
 * @param suiteId  
 *        The AJSC MIDlet suite identifier.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param midletId 
 *        The index of a MIDlet of the MIDlet suite indicated by <i>suiteId</i>.
 * @param high     
 *        The high 32 bit of the time information.
 * @param low      
 *        The low 32 bit of the time information.
 * @retval 1 if the operation succeeds.
 * @retval 0 if the operation fails.
 *
 * The function is called to request the native system to launch a MIDlet at the given time.
 * The time is passed via the <i>high</i> and <i>low</i> parameters as elapsed milliseconds from
 * 00:00:00.000 GMT, January 1, 1970.
 *
 * When the timer expires the native system should 
 * launch the MIDlet associated with the alarm by means of @ref Application_Runtime_Control_ACI functions.
 *
 * The AMS may need to interact with user before launching the MIDlet depending on permission settings.
 * See the specification of MIDP for details.
 */
int kjava_push_startAlarm(int suiteId, int midletId, unsigned long high, unsigned long low);

#ifdef SUPPORT_PUSH_REGISTRY_URL_REGISTRATION
/**
 * \brief Stop a push connection.
 *
 * The function informs the native system to stop the Push connection of the
 * given connUrl and port.
 *
 * @param connUrl       The connection url in utf-8 string with 
 *                       null-terminated character, such as 
 *                       <i>sms://:50000</i>, <i>socket://:79</i> or <i>datagram://:50000</i>.
 * @param pushPort       The local port number associated with the connUrl.
 *
 * @return If the operation is successful, return 1. Otherwise, return 0.
 */
int kjava_push_stopConn(unsigned char* connUrl, AJ_S32 pushPort);
#else
/**
 *        Stops a push connection.
 * @param protocol       
 *        A pointer to the UTF-8 NUL-terminated string representing the push connection protocol, such as 
 *        <code>sms://</code>, <code>socket://</code> or <code>datagram://</code>.
 * @param port           
 *        The local port number associated with the protocol.
 * @retval 1 if the operation succeeds.
 * @retval 0 if the operation fails.
 *
 * This function is called to remove the push connection registration indicated by the parameters. 
 */
int kjava_push_stopConn(unsigned char* protocol, int port);
#endif
#ifdef SUPPORT_PUSH_REGISTRY_URL_REGISTRATION
/**
 * \brief Bind a push connection with an installed midlet suite.
 *
 * The function informs the native system to start a Push connection
 * monitoring of the given connUrl and port number.
 *
 * The native system should be informed when an incoming connection is created
 * from the specified connUrl and port, and uses AJMS functions to launch 
 * the MIDlet associated with the connection.
 *
 * A filter string is also specified so native system could use it to filter
 * wanted inbound connections. The syntax and semantic is protocol depedent. 
 * But wildcard characters should be supported. Please refer to the
 * spec of <code>javax.microedition.io.PushRegistry</code> for detail
 * information.
 *
 * @param suiteId  The AJMS midlet suite identifier.
 * @param midletId The AJMS midlet index for the <i>suiteId</i>.
 * @param connUrl       The connection URL name in utf-8 string with 
 *                       null-terminated character, such as 
 *                       <i>sms://:50000</i>, <i>socket://:79</i> or <i>datagram://:50000</i>.
 * @param pushPort     The local port number associated with the connUrl.
 * @param filter   The URL filter string, in UTF-8 characters. 
 *
 * @return If the operation is successful, return 1.If  custom cancel push installnation ,return 2. Otherwise, return 0.
 */
int kjava_push_startConn(int            suiteId, 
                         int            midletId, 
                         unsigned char* connUrl, 
                         AJ_S32         pushPort, 
                         unsigned char* filter);
#else
/**
 *        Binds a push connection with an installed midlet suite.
 * @param suiteId  
 *        The AJSC MIDlet suite identifier.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param midletId 
 *        The index of a MIDlet of the MIDlet suite indicated by <i>suiteId</i>.
 * @param protocol       
 *        A pointer to the UTF-8 NUL-terminated string representing the push connection protocol, such as 
 *        <code>sms://</code>, <code>socket://</code> or <code>datagram://</code>.
 * @param port     
 *        The local port number associated with the protocol.
 * @param filter   
 *        A pointer to the UTF-8 NUL-terminated string containing the URL filter.
 * @retval 1 if the operation succeeds.
 * @retval 0 if the operation fails.
 *
 * This function is called to request the native system to start monitoring a Push connection
 * of the given protocol and port number.
 *
 * When an incoming connection is made to the specified protocol and port,
 * the native system should launch the MIDlet associated with the connection.
 *
 * The AMS may need to interact with user before launching the MIDlet depending on permission settings.
 * See the specification of MIDP for details.
 *
 * A filter string can be passed so native system can use it to filter desired inbound connections. 
 * The syntax and semantics of the filter string are protocol dependent. 
 * However, every syntax for protocols must support wild card characters. 
 * See the specification of <code>javax.microedition.io.PushRegistry</code> for details.
 */
int kjava_push_startConn(int            suiteId, 
                         int            midletId, 
                         unsigned char* protocol, 
                         int            port, 
                         unsigned char* filter);
#endif
#ifdef SUPPORT_PUSH_REGISTRY_URL_REGISTRATION
/**
 * \brief Check if the specified connUrl and port is allowed to be used by 
 *        connection.
 *
 * @param connUrl       The connection URL name in utf-8 string with 
 *                       null-terminated character, such as 
 *                       <i>sms://:50000</i>, <i>socket://:79</i> or <i>datagram://:50000</i>.
 * @param pushPort     The local port number associated with the connUrl 
 *
 * @return 1 for available and 0 for not allowed.
 */
int kjava_push_isAvailable(unsigned char* connUrl, AJ_S32  pushPort);
#else
/**
 *        Checks if the specified protocol and port is allowed to be used by a push connection.
 * @param protocol       
 *        A pointer to the UTF-8 NUL-terminated string representing the push connection protocol, such as 
 *        <code>sms://</code>, <code>socket://</code> or <code>datagram://</code>.
 * @param port
 *        The local port number associated with the protocol.
 * @retval 1 if the specified protocol and port is available
 * @retval 0 if the specified protocol and port is NOT available
 */
int kjava_push_isAvailable(unsigned char* protocol, unsigned int port);
#endif
/**
 * \brief Check if the push is started 
 *
 * @return 1 if push is started. Otherwise, return 0.
 */
#ifdef SUPPORT_PUSH_REGISTRY_URL_REGISTRATION
int kjava_push_isStarted(void);
#endif
/** @} */

#ifdef __cplusplus
}
#endif

#endif
