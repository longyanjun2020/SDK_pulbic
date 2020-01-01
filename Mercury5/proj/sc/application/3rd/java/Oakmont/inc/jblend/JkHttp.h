/**
 * Copyright 2002-2004,2006 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkHttp.h
 * HTTP/HTTPS Communication
 */
/**
 * @addtogroup HTTP_HTTPS_Communication_JSI 
 * @{
 */
#ifndef ___NET_JK_HTTP_H
#define ___NET_JK_HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesHttp.h"

/**
 * Opens an HTTP/HTTPS connection.
 *
 * @param url
 *      The URL string  (not terminated by '\0').
 *      This pointer remains valid until the request result event is notified to 
 *      JBlend.
 * @param urlLength
 *      The size (in octets) of the url parameter.
 * @param method
 *      The request method. 
 *      Either #JK_HTTP_METHOD_GET, #JK_HTTP_METHOD_HEAD, 
 *      or #JK_HTTP_METHOD_POST is designated.
 * @param param
 *      The value that must be passed as a parameter of the event when the event 
 *      is notified with AmNotifyHttpEvent(). 
 * @param timeout
 *      The flag which a MIDlet has designated to the <code>timeouts</code> parameter of 
 *      <code>javax.microedition.io.Connector.open(String name, int mode, boolean timeouts)</code> method.
 *
 * @return
 *      When an HTTP/HTTPS connection is created normally, return a handler 
 *      value indicating the created connection.
 *      If an HTTP/HTTPS connection could not be created, return #JK_INVALID_HANDLE.
 *
 * This function is called in order to create a connection to an HTTP server.
 * The timing for actually connecting to the HTTP server is an implementation 
 * dependent matter.
 * To enable other functions to perform various operations on the created 
 * HTTP/HTTPS connection, issue a handle value that uniquely identifies the 
 * connection and notify this handle as a return value. 
 * The created connection and the handle value issued for it should remain valid
 * until #JkHttpClose() is called.
 *
 * JBlend sets #JK_TRUE to the <i>timeout</i> parameter only when a MIDlet has designated <code>true</code> to the 
 * <code>timeouts</code> parameter of <code>javax.microedition.io.Connector.open(String name, int mode, boolean timeouts)</code> 
 * method, JBlend sets #JK_FALSE to the <i>timeout</i> parameter otherwize.
 * When the native system notifies a MIDlet of the #JK_HTTP_EVENT_ERROR event by #AmNotifyHttpEvent(),
 * if #JK_HTTP_ERROR_TIMEOUT or the value greater than or equal to #JK_HTTP_ERROR_CUSTOMER_SPEC_MIN is designated 
 * to the <i>option</i> parameter, the behavior of JBlend depends on the value JBlend has designated to 
 * the <i>timeout</i> parameter of JkHttpOpen(). 
 * For the details of this behavior, refer to the description of #JK_HTTP_EVENT_ERROR.
 *
 
 * In the native system, call #AmNotifyHttpEvent() to pass either of the 
 * following events to JBlend, depending on the processing result.
 * <dl>
 *   <dt>Connection or connection preparation succeeds.</dt>
 *   <dd> #JK_HTTP_EVENT_OPEN</dd>
 *   <p>
 *   <dt>An error occurred either in the native system or at the destination server.</dt>
 *   <dt>The processing was canceled by JkHttpClose().</dt>
 *   <dd> #JK_HTTP_EVENT_ERROR</dd>
 * </dl>
 * Even if JkHttpClose() is called before the processing result for this 
 * function is passed to JBlend (due to JVM suspension or a close request), 
 * it is still necessary to notify JBlend of the processing result 
 * for this function by passing an event.
 *
 * @see AmNotifyHttpEvent()
 * @see JkHttpClose()
 */
JKHttpHandle JkHttpOpen( const JKSint8* url, JKSint32 urlLength, JKSint32 method, JKSint32 param, JKBool timeout );

/**
 * Sends an HTTP/HTTPS request header.
 *
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param header
 *      A pointer to the array of JKT_Http_Header data structures holding the 
 *      HTTP/HTTPS requests.
 *      The termination of each header does not include a line break code (CR or LF). <br>
 *      This pointer remains valid until the request result event is notified to 
 *      JBlend.
 * @param headerCount
 *      The number of JKT_Http_Header data structures pointed to by the header 
 *      parameter.
 *
 * @return
 *      If the operation succeeds, return 0; if it fails (error), return -1.
 *
 * This function is called to send an HTTP/HTTPS header to an HTTP server. 
 * The actual send timing to the HTTP server is implementation dependent.
 *
 * In the native system, call #AmNotifyHttpEvent() to pass either of the 
 * following events to JBlend, depending on the processing result.
 * <dl>
 *   <dt>HTTP/HTTPS header sending or send preparation succeeds.</dt>
 *   <dd>#JK_HTTP_EVENT_WRITE_HEADER</dd>
 *   <p>
 *   <dt>An error occurred either in the native system or at the destination server.</dt>
 *   <dt>The processing was canceled by JkHttpClose().</dt>
 *   <dd> #JK_HTTP_EVENT_ERROR</dd>
 * </dl>
 * Even if JkHttpClose() is called before the processing result for this 
 * function is passed to JBlend (due to JVM suspension or a close request), 
 * it is still necessary to notify JBlend of the processing result 
 * for this function by passing an event.
 *
 * The sequence of the individual HTTP/HTTPS header pointers indicated by the 
 * header parameter may be changed for sorting or other editing, so long as it 
 * is still possible to free the memory allocated for the HTTP/HTTPS header.
 *
 * In the HTTP communication that is performed after a MIDlet calls 
 * <code>flush</code> method of an <code>OutputStream</code> object 
 * created from <code>javax.microedition.io.HttpConnection</code>,
 * JBlend calls #JkHttpOpen() to create an HTTP/HTTPS connection, 
 * then calls this function to pass to the native system the 
 * HTTP/HTTPS headers added by the MIDlet and the following header.
 * <pre>
 * transfer-encoding: chunked
 * </pre>
 *
 * @par For compliance with JTWI 1.0:
 * If the MIDlet currently being executed on a GSM/UMTS (W-CDMA) handset is an untrusted MIDlet,
 * JTWI-compliant JBlend calls this function appending the following header information 
 * to that designated by the MIDlet.
 *  <br><br>
 * <table border="1">
 * <tr><td><b> Member of JKT_Http_Header Structure </b></td>
 *   <td><b>Value Set </b></td></tr>
 * <tr><td>fieldName</td><td>User-Agent</td></tr>
 * <tr><td>fieldNameLength</td><td>10</td></tr>
 * <tr><td>fieldValue</td><td>UNTRUSTED/1.0</td></tr>
 * <tr><td>fieldValueLength</td><td>13</td></tr>
 * </table>
 *  <br>
 * An HTTP request must be sent containing this header information along with the User-Agent 
 * header designated by the MIDlet.
 *
 * @see AmNotifyHttpEvent()
 * @see JkHttpOpen()
 */
JKSint32 JkHttpWriteHeader( JKHttpHandle connection, JKT_Http_Header header[], JKSint32 headerCount );

/**
 * Sends an HTTP/HTTPS request body.
 *
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      A pointer to the HTTP/HTTPS request body to be sent.
 *      This pointer remains valid until the request result event is notified to 
 *      JBlend.
 * @param dataLength
 *      The parameter data size in octets
 *
 * @return
 *      If the operation succeeds, 0 is returned; if it fails (error), -1 is 
 *      returned.
 *
 * This function is called to send an HTTP/HTTPS request body to the HTTP server. 
 * The actual data send timing is implementation dependent.
 *
 * In the native system, call #AmNotifyHttpEvent() to pass either of the 
 * following events to JBlend, depending on the processing result.
 * <dl>
 *   <dt>Request body sending or send preparation succeeds.</dt>
 *   <dd> #JK_HTTP_EVENT_WRITE</dd>
 *   <p>
 *   <dt>An error occurred either in the native system or at the destination server.</dt>
 *   <dt>The processing was canceled by JkHttpClose().</dt>
 *   <dd> #JK_HTTP_EVENT_ERROR</dd>
 * </dl>
 * Even if JkHttpClose() is called before the processing result for this 
 * function is passed to JBlend (due to JVM suspension or a close request), 
 * it is still necessary to notify JBlend of the processing result 
 * for this function by passing an event.
 *
 * It is allowable to process only the amount of data that can be handled, 
 * without completing all the designated request body processing.
 * Designate the size of the processed request body in the option parameter 
 * with #AmNotifyHttpEvent().
 * JBlend looks at the processed data size as notified in the 
 * #JK_HTTP_EVENT_WRITE event and continues to call this function until the entire 
 * request body has been processed. 
 *
 * In the HTTP communication that is performed after a MIDlet calls 
 * <code>flush</code> method of an <code>OutputStream</code> object 
 * created from <code>javax.microedition.io.HttpConnection</code>,
 * JBlend performs chunked encoding, treating the data written to 
 * that <code>OutputStream</code> object as one chunk, then passes 
 * the chunk size and chunk data to the native system by this function.
 * See RFC2616 3.6.1, "Chunked Transfer Coding" for details of the encoding.
 *
 * @see AmNotifyHttpEvent()
 * @see JkHttpOpen()
 */
JKSint32 JkHttpWrite( JKHttpHandle connection, const JKUint8* data, JKSint32 dataLength );


/**
 * Sends request body data buffered in the native system to the HTTP/HTTPS server.
 *
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 *
 * @return
 *      Return 0 if the operation succeeds, or -1 in case of error.
 *
 * This function is called to complete the sending of HTTP/HTTPS request body 
 * data buffered in the native system. It applies to the HTTP/HTTPS connection 
 * designated by the connection parameter.
 * When this function is called, the native system should immediately send 
 * buffered HTTP/HTTPS request body data that has not yet been sent.
 * If request body sending is not yet possible because a connection to the 
 * HTTP/HTTPS server is not established or the HTTP/HTTPS headers have not been 
 * sent, first connect to the server and send the headers, then send the 
 * HTTP/HTTPS request body data.
 *
 * In the native system, call #AmNotifyHttpEvent() to pass either of the 
 * following events to JBlend, depending on the processing result.
 * <dl>
 *   <dt>Buffered HTTP/HTTPS request body sending is all completed.</dt>
 *   <dd> #JK_HTTP_EVENT_FLUSH</dd>
 *   <p>
 *   <dt>An error occurred either in the native system or at the destination server.</dt>
 *   <dt>The processing was canceled by JkHttpClose().</dt>
 *   <dd> #JK_HTTP_EVENT_ERROR</dd>
 * </dl>
 * Even if JkHttpClose() is called before the processing result for this 
 * function is passed to JBlend (due to JVM suspension or a close request), 
 * it is still necessary to notify JBlend of the processing result 
 * for this function by passing an event.
 *
 * In the HTTP communication that is performed after a MIDlet calls 
 * <code>flush</code> method of an <code>OutputStream</code> object 
 * created from <code>javax.microedition.io.HttpConnection</code>,
 * JBlend calls #JkHttpWrite() to pass to the native system the 
 * data written to that <code>OutputStream</code> object, then 
 * calls this function to request data transfer.
 *
 * @see AmNotifyHttpEvent()
 * @see JkHttpOpen()
 * @see JkHttpWrite()
 */
JKSint32 JkHttpFlush( JKHttpHandle connection );

/**
 * Notifies the completion of an HTTP/HTTPS request.
 *
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @return
 *      If the operation succeeds, 0 is returned; if it fails (error), -1 is 
 *      returned.
 *
 * This function is called to notify the HTTP server that the HTTP/HTTPS request has 
 * been completed. After this function is called, #JkHttpWriteHeader() and  
 * #JkHttpWrite() will not be called for the same HTTP/HTTPS connection.
 *
 * In the native system, call #AmNotifyHttpEvent() to pass either of the 
 * following events to JBlend, depending on the processing result.
 * <dl>
 *   <dt>The request was sent successfully. Preparation for response receipt may proceed.</dt>
 *   <dd> #JK_HTTP_EVENT_FINISH_REQUEST</dd>
 *   <p>
 *   <dt>An error occurred either in the native system or at the destination server.</dt>
 *   <dt>The processing was canceled by JkHttpClose().</dt>
 *   <dd> #JK_HTTP_EVENT_ERROR</dd>
 * </dl>
 * Even if JkHttpClose() is called before the processing result for this 
 * function is passed to JBlend (due to JVM suspension or a close request), 
 * it is still necessary to notify JBlend of the processing result 
 * for this function by passing an event.
 *
 * After the #JK_HTTP_EVENT_FINISH_REQUEST event is notified, #JkHttpRead() is called 
 * requesting receipt of the HTTP/HTTPS response.
 *
 * @see JkHttpWriteHeader()
 * @see JkHttpWrite()
 * @see JkHttpRead()
 */
JKSint32 JkHttpFinishRequest( JKHttpHandle connection );

/**
 * Gets the HTTP/HTTPS response received from the HTTP server.
 *
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      A pointer to the area holding data received from the HTTP server.
 *      This pointer remains valid until a request result event is notified to 
 *      JBlend.
 * @param dataLength
 *      The size (in octets) of the area designated by the data parameter.
 *
 * @return
 *      If the operation succeeds, 0 is returned; if it fails (error), -1 is 
 *      returned.
 *
 * This function is called to get the HTTP/HTTPS response received from the HTTP 
 * server. 
 * Note that no flow control of the receive data is performed in JBlend. 
 * If flow control is necessary, it must be implemented by the device manufacturer.
 *
 * In the native system, call #AmNotifyHttpEvent() to pass either of the 
 * following events to JBlend, depending on the processing result.
 * <dl>
 *   <dt>Received data has been stored in the memory space indicated by the data parameter.</dt>
 *   <dd> #JK_HTTP_EVENT_READ</dd>
 *   <p>
 *   <dt>An error occured either in the native system or at the destination server.</dt>
 *   <dt>The processing was canceled by JkHttpClose().</dt>
 *   <dd> #JK_HTTP_EVENT_ERROR</dd>
 * </dl>
 * Even if JkHttpClose() is called before the processing result for this 
 * function is passed to JBlend (due to JVM suspension or a close request), 
 * it is still necessary to notify JBlend of the processing result 
 * for this function by passing an event.
 *
 * The format of the HTTP response to be passed in the data parameter must 
 * conform to the format specified in RFC 2616.
 * Below is an example of an HTTP response that is in accordance with 
 * RFC 2616, Section 6, "Responce."
 *
 * <pre>
 * HTTP/1.1 200 OK
 * Date: Wed, 24 Mar 2004 08:00:25 GMT
 * Content-Length: 23
 * Connection: close
 * Content-Type: text/plain; charset=ISO-8859-1
 * 
 * HTTP response message
 * </pre>
 * 
 * Since HTTP responses whose status code starts with 1, such as HTTP/1.1 1xx, 
 * are temporary, do not pass them to JBlend.
 * Pass to JBlend only the eventual responses following them.
 *
 * @see AmNotifyHttpEvent()
 * @see JkHttpOpen()
 */
JKSint32 JkHttpRead( JKHttpHandle connection, JKUint8* data, JKSint32 dataLength );

/**
 * Gets the HTTP/HTTPS response size that can be obtained with no I/O blocking.
 *
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 *
 * @return
 *      Return the HTTP/HTTPS response size (in octets) that can be obtained without 
 *      I/O blocking, that is, the size buffered in the communication layer by the 
 *      manufacturer-implemented processing at the time this function is called.
 *      In case of error, return -1.
 *
 * Return the HTTP/HTTPS response size already received from the HTTP server, buffered 
 * in the communication layer and not yet passed to JBlend in response to 
 * #JkHttpRead().
 * 
 * In processing this function it is not necessary to pass an HTTP/HTTPS event to 
 * JBlend. Return control to JBlend as soon as possible so that JBlend
 * processsing will not be blocked by this function for too long.
 *
 * @see JkHttpOpen()
 */
JKSint32 JkHttpAvailable( JKHttpHandle connection );

/**
 * Closes an HTTP/HTTPS connection.
 *
 * @param connection
 *      The HTTP/HTTPS connection to be closed. The value returned by 
 *      #JkHttpOpen() is designated.
 *
 * @return
 *      If the close operation succeeds, return 0; if it fails (error), return -1. 
 *
 * This function is called to close the HTTP/HTTPS connection designated in 
 * the connection parameter. 
 * Stop processing of the designated HTTP/HTTPS connection and free resources allocated for it. 
 * Call #AmNotifyHttpEvent() passing either of the following events to JBlend, 
 * depending on the processing result.
 * <dl>
 *   <dt>The request to close the HTTP/HTTPS connection was accepted.</dt>
 *   <dd>#JK_HTTP_EVENT_CLOSE</dd>
 *   <p>
 *   <dt>An error occurred either in the native system or at the destination server.</dt>
 *   <dd> #JK_HTTP_EVENT_ERROR</dd>
 * </dl>
 *
 * It must be possible to call this function at any point while an HTTP/HTTPS
 * connection is created.
 *
 * If the processing result for any of the following functions has not been 
 * passed to JBlend at the time this function is called, 
 * notify JBlend of not only the result of JkHttpClose() but also the results of 
 * the processing requested with these functions, by passing events.
 * <ul>
 *   <li>JkHttpOpen()
 *   <li>JkHttpWriteHeader()
 *   <li>JkHttpWrite()
 *   <li>JkHttpFlush()
 *   <li>JkHttpFinishRequest()
 *   <li>JkHttpRead()
 * </ul>
 * After this function is called, no more processing requests will be made for the 
 * HTTP/HTTPS connection designated in the connection parameter.
 *
 * @see AmNotifyHttpEvent()
 * @see JkHttpOpen()
 */
JKSint32 JkHttpClose( JKHttpHandle connection );




#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
