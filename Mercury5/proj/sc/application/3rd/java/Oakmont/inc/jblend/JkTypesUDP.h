/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 *@file JkTypesUDP.h
 *  UDP Datagram Connection data types and constants
 */

#ifndef ___JKTYPES_UDPEVENT_H
#define ___JKTYPES_UDPEVENT_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup UDP_Connection_Data_Types
 * @{
 */

/**
 *   Datagram socket handle type
 */
typedef JKHandle JKUdpHandle;


/**
 *  A setup result notification event.\
 *  This is used for notifying the result of #JkUdpConnect() processing.
 */
#define     JK_UDP_EVENT_TYPE_CONNECT       0

/**
 *  A send result notification event.\
 *  This is used for notifying the result of #JkUdpSendTo() processing.
 */
#define     JK_UDP_EVENT_TYPE_SENDTO        1

/**
 *  A close result notification event.\
 *  This is used for notifying the result of #JkUdpClose() processing.
 */
#define     JK_UDP_EVENT_TYPE_CLOSE         2

/**
 *  Values returned by the individual functions
 */
/**
 *  Succeeded.
 *
 *  Passed in the <i>result</i> parameter of #AmNotifyUdpEvent(), or as the
 *  return value of the following @ref UDP_Connection_JSI functions.
 * <ul>
 *  <li> #JkUdpConnect()
 *  <li> #JkUdpClose()
 *  <li> #JkUdpSendTo()
 *  <li> #JkUdpReceiveFrom()
 *  <li> #JkUdpQueryHostname()
 * </ul>
 */
#define JK_UDP_SUCCESS                  0

/**
 *  The invoked function is not supported.
 *
 *  Passed as the return value of #JkUdpQueryHostname().
 */
#define JK_UDP_UNSUPPORTED_FUNCTION     (-10000)

/**
 *  Error code: An internal error occurred 
 *
 *  Passed in the <i>result</i> parameter of #AmNotifyUdpEvent() and
 *  #AmNotifyUdpReceived(), or as the return value of the
 *  @ref UDP_Connection_JSI functions other than
 *  #JkUdpGetMaxSessions() and #JkUdpOpen().
 */
#define JK_UDP_ERROR_OTHER              (-30000)

/**
 * @} end of group
 */


#ifdef __cplusplus
}
#endif

#endif

