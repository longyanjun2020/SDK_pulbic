/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesHttpEvent.h
 * HTTP/HTTPS Communication Event Types
 */
#ifndef ___JKTYPESHTTPEVENT_H
#define ___JKTYPESHTTPEVENT_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup HTTP_HTTPS_Communication_Event_Types
 * @{
 */

/**
 * An HTTP/HTTPS connection request by #JkHttpOpen() was accepted.
 *
 * When an HTTP/HTTPS connection to the destination server has been opened in response 
 * to #JkHttpOpen(), or when preparations for connection opening have been completed, 
 * call #AmNotifyHttpEvent() to make the following event notification to JBlend.
 * 
 * <table><caption>Event Notified when Succeeding in Required Processing in JkHttpOpen()</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters</b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> #JkHttpOpen() param value </td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td>#JK_HTTP_EVENT_OPEN</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td> 0</td>
 *  </tr>
 * </table>
 */
#define     JK_HTTP_EVENT_OPEN              1


/**
 *  SSL session successfully established in HTTPS communication.
 *
 * When an SSL connection is successfully established in HTTPS communication, call
 * #AmNotifyHttpEvent() to make the following event notification to JBlend.
 *
 * <table><caption>Event Notified when SSL Session Established</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters</b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> Value of param passed by #JkHttpOpen()</td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_ESTABLISH_SSL_SESSION</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td>0</td>
 *  </tr>
 * </table>
 *
 */
#define     JK_HTTP_EVENT_ESTABLISH_SSL_SESSION         2

/**
 *  An HTTP/HTTPS header send request by #JkHttpWriteHeader() was accepted.
 *
 * When header sending to the connected server was completed in response to 
 * #JkHttpWriteHeader(), or when preparations for header sending have been completed,
 * call #AmNotifyHttpEvent() to make the following event notification to JBlend.
 *
 * <table><caption>Event Notified when Succeeding in Required Processing in JkHttpWriteHeader().</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters </b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> #JkHttpOpen() param value</td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_WRITE_HEADER</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td> 0</td>
 *  </tr>
 * </table>
 *
 */
#define     JK_HTTP_EVENT_WRITE_HEADER      3

/**
 * An HTTP/HTTPS request body send request by #JkHttpWrite() was accepted.
 *
 * When request body sending to the connected server has been completed in response 
 * to #JkHttpWrite(), or when preparations for request body sending have been 
 * completed, call #AmNotifyHttpEvent() to make the following event notification to 
 * JBlend.
 *
 * <table><caption>Event Notified when Succeeding in Required Processing in JkHttpWrite().</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters</b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> #JkHttpOpen() param value</td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_WRITE</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td>Size (in octets) of data sent or prepared for sending.</td>
 *  </tr>
 * </table>
 *
 */
#define     JK_HTTP_EVENT_WRITE             4

/**
 *  Send processing was completed in response to an HTTP/HTTPS request body send 
 *  request by #JkHttpFlush().
 *
 *
 * Once all previously unsent HTTP/HTTPS request bodies have been sent in response 
 * to #JkHttpFlush(), call #AmNotifyHttpEvent() and notify the event indicated below
 * to JBlend.
 *
 * <table><caption>
 *    Event Notified when JkHttpFlush() Completes Required Processing
 *  </caption>
 *  <tr>
 *   <td><b>
 *    #AmNotifyHttpEvent() parameters
 *   </b></td>
 *   <td>
 *    Designated values
 *   </td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td>
 *    Value of param passed by #JkHttpOpen()
 *   </td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_FLUSH</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td>0</td>
 *  </tr>
 * </table>
 *
 */
#define     JK_HTTP_EVENT_FLUSH    5

/**
 *  Notification of HTTP/HTTPS request completion by #JkHttpFinishRequest() was accepted.
 *
 * When receipt of a response from the connected server is possible as requested 
 * by #JkHttpFinishRequest(), call #AmNotifyHttpEvent() to make the following event 
 * notification to JBlend.
 *
 * <table><caption>Event Notified when Succeeding in Required Processing in JkHttpFinishRequest().</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters</b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> Value of param passed by #JkHttpOpen()</td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_FINISH_REQUEST</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td>0</td>
 *  </tr>
 * </table>
 *
 */
#define     JK_HTTP_EVENT_FINISH_REQUEST    6

/**
 * An HTTP/HTTPS response requested by #JkHttpRead() was received successfully.
 *
 * When received data has been put in the area designated by the data parameter as 
 * requested by #JkHttpRead(), call #AmNotifyHttpEvent() to make the following event 
 * notification to JBlend.
 *
 * <table><caption>Event Notified when Succeeding in Required Processing in JkHttpRead().</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters</b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> Value of param passed by #JkHttpOpen()</td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_READ</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td>Size (in octets) of receive data put in the buffer designated by the 
 *       #JkHttpRead() data parameter.
 *       Put a value between 1 and the value of the #JkHttpRead() dataLength parameter.
 *       When all the response data received from the connected server has been passed to
 *       JBlend, set 0. </td>
 *  </tr>
 * </table>
 * 
 */
#define     JK_HTTP_EVENT_READ              7

/**
 *  An HTTP/HTTPS connection close request by #JkHttpClose() was accepted.
 *
 * When the HTTP/HTTPS connection has been closed as requested by #JkHttpClose(), or 
 * when preparations for closing have been completed, call #AmNotifyHttpEvent() to make 
 * the following event notification to JBlend.
 *
 * <table><caption>Event Notified when Succeeding in Required Processing in JkHttpClose().</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters</b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> Value of param passed by #JkHttpOpen()</td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_CLOSE</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td>0</td>
 *  </tr>
 * </table>
 *
 */
#define     JK_HTTP_EVENT_CLOSE             8

/**
 *  An error occurred.
 *
 * When an error occurs in HTTP/HTTPS communication processing, call 
 * #AmNotifyHttpEvent() to make the following event notification to JBlend.
 *
 * <table><caption>Event Notified when Error Occurs</caption>
 *  <tr>
 *   <td><b> #AmNotifyHttpEvent() parameters</b></td>
 *   <td>Designated values</td>
 *  </tr>
 *  <tr>
 *   <td><b>param</b></td>
 *   <td> Value of param passed by #JkHttpOpen()</td>
 *  </tr>
 *  <tr>
 *   <td><b>cause</b></td>
 *   <td> #JK_HTTP_EVENT_ERROR</td>
 *  </tr>
 *  <tr>
 *   <td><b>option</b></td>
 *   <td>Set an appropriate error code, starting with JK_HTTP_ERROR_, based on the type 
 *   of error.
 *   If there is no such error code, set any value above 
 *   #JK_HTTP_ERROR_CUSTOMER_SPEC_MIN.</td>
 *  </tr>
 * </table>
 *
 * If #JK_HTTP_ERROR_TIMEOUT or the value greater than or equal to #JK_HTTP_ERROR_CUSTOMER_SPEC_MIN 
 * is designated to the <i>option</i> parameter of #AmNotifyHttpEvent(), 
 * the behavior of JBlend depends on the value JBlend has designated to the <i>timeout</i> parameter 
 * of JkHttpOpen(). 
 *
 * When #JK_HTTP_ERROR_TIMEOUT is designated:
 * <table>
 *  <tr>
 *   <td><i><b>Timeout</i> Parameter of JkHttpOpen()</b></td>
 *   <td><b>The Behavior of JBlend After the Event Notification</b></td>
 *  </tr>
 *  <tr>
 *   <td>#JK_TRUE</td>
 *   <td>Throws an <code>InterruptedIOException</code></td>
 *  </tr>
 *  <tr>
 *   <td>#JK_FALSE</td>
 *   <td>Throws an <code>IOException</code></td>
 *  </tr>
 * </table>
 *
 * When the value greater than or equal to #JK_HTTP_ERROR_CUSTOMER_SPEC_MIN is designated:
 * <table>
 *  <tr>
 *   <td><i><b>Timeout</i> Parameter of JkHttpOpen()</b></td>
 *   <td><b>The Behavior of JBlend After the Event Notification</b></td>
 *  </tr>
 *  <tr>
 *   <td>#JK_TRUE<br>#JK_FALSE</td>
 *   <td>Throws an <code>IOException</code></td>
 *  </tr>
 * </table>
 *
 */
#define     JK_HTTP_EVENT_ERROR             0

/**
 * @} end of group
 */


/**
 * @addtogroup HTTP_HTTPS_Communication_Error_Codes
 * @{
 */

/**
 * Connection timeout
 *
 * If a timeout error occurs, with no response from the server after a set period, call
 * #AmNotifyHttpEvent() setting the error code in the option parameter.
 */
#define     JK_HTTP_ERROR_TIMEOUT      1

/**
 * The certificate contains an unrecognized critical extension.
 */
#define     JK_HTTP_ERROR_CERT_BAD_EXTENSIONS      101

/**
 * The server certificate chain exceeds the maximum depth specified by the issuer.
 */
#define     JK_HTTP_ERROR_CERT_CHAIN_TOO_LONG  102

/**
 * The server certificate has expired (it is no longer valid).
 */
#define     JK_HTTP_ERROR_CERT_EXPIRED     103

/**
 * An intermediate certificate in the chain has not been authorized by the 
 * Certificate Authority.
 */
#define     JK_HTTP_ERROR_CERT_UNAUTHORIZED_INTERMEDIATE_CA        104
    
/**
 * The certificate is unsigned.
 */
#define     JK_HTTP_ERROR_CERT_MISSING_SIGNATURE       105

/**
 * The certificate is not yet valid.
 */
#define     JK_HTTP_ERROR_CERT_NOT_YET_VALID       106

/**
 * The site name on the certificate is not correct.
 */
#define     JK_HTTP_ERROR_CERT_SITENAME_MISMATCH       107

/**
 * The issuer of the certificate is unknown.
 */
#define     JK_HTTP_ERROR_CERT_UNRECOGNIZED_ISSUER     108

/**
 * The certificate signature algorithm is not supported.
 */
#define     JK_HTTP_ERROR_CERT_UNSUPPORTED_SIGALG      109

/**
 * The public key is used inappropriately by the certificate issuer.
 */
#define     JK_HTTP_ERROR_CERT_INAPPROPRIATE_KEY_USAGE         110

/**
 * A certificate in the chain was not issued by the same Certificate Authority as the 
 * next certificate in the chain.
 */
#define     JK_HTTP_ERROR_CERT_BROKEN_CHAIN        111

/**
 * The public key of the root certificate has expired.
 */
#define     JK_HTTP_ERROR_CERT_ROOT_CA_EXPIRED         112

/**
 * The certificate public key type is not supported by the device.
 */
#define     JK_HTTP_ERROR_CERT_UNSUPPORTED_PUBLIC_KEY_TYPE     113

/**
 * Certificate verification failed.
 */
#define     JK_HTTP_ERROR_CERT_VERIFICATION_FAILED     114

/**
 * The minimum value in the customer-specified area
 */
#define     JK_HTTP_ERROR_CUSTOMER_SPEC_MIN     10000

/**
 * @} end of group
 */

#ifdef __cplusplus
}
#endif

#endif /* ___JKTYPESHTTPEVENT_H */
