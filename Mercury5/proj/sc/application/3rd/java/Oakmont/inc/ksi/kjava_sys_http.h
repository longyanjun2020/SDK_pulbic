/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 *  @file kjava_sys_http.h
 *  KSI function prototypes for HTTP and HTTPS communication
 */

#ifndef KJAVA_SYS_HTTP_HEADER
#define KJAVA_SYS_HTTP_HEADER

#ifdef __cplusplus
extern "C"{
#endif



/**
 * @addtogroup HTTP_Constant
 * Defines data types and constants for HTTP/HTTPS processing.
 * @par Include file 
 * \#include kjava_sys_http.h
 * @{
 */

/**
 * @name HTTP Processing Event Code
 * @{
 */
/**
 * An HTTP/HTTPS connection request by kjava_http_open() was accepted.
 *
 * When an HTTP/HTTPS connection to the destination server has been opened in response 
 * to a call to kjava_http_open(), or when preparations for connection opening have been completed, 
 * call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_OPEN
 * @param option 0
 */
#define     KJAVA_HTTP_EVENT_OPEN              1

/**
 * SSL session successfully established in HTTPS communication.
 *
 * When an SSL connection is successfully established in HTTPS communication, call
 * the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_ESTABLISH_SSL_SESSION
 * @param option 0
 */
#define     KJAVA_HTTP_EVENT_ESTABLISH_SSL_SESSION         2

/**
 * An HTTP/HTTPS header send request by #kjava_http_write_header was accepted.
 *
 * When header sending to the connected server was completed in response to 
 * kjava_http_write_header(), or when preparations for header sending have been completed,
 * call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_WRITE_HEADER
 * @param option 0
 */
#define     KJAVA_HTTP_EVENT_WRITE_HEADER      3

/**
 * An HTTP/HTTPS request body send request by kjava_http_write() was accepted.
 *
 * When request body sending to the connected server has been completed in response 
 * to kjava_http_write(), or when preparations for request body sending have been 
 * completed, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_WRITE
 * @param option The size (in octets) of the data sent or prepared for sending.
 */
#define     KJAVA_HTTP_EVENT_WRITE             4

/**
 * Send processing was completed in response to an HTTP/HTTPS request body send 
 * request by kjava_http_flush().
 *
 * Once all previously unsent HTTP/HTTPS request bodies have been sent in response 
 * to kjava_http_flush(), call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_FLUSH
 * @param option 0
 */
#define     KJAVA_HTTP_EVENT_FLUSH    5

/**
 * Notification of HTTP/HTTPS request completion by kjava_http_finish_request() was accepted.
 *
 * When receipt of a response from the connected server is possible as requested 
 * by kjava_http_finish_request(), call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_FINISH_REQUEST
 * @param option 0
 */
#define     KJAVA_HTTP_EVENT_FINISH_REQUEST    6

/**
 * An HTTP/HTTPS response requested by kjava_http_read() was received successfully.
 *
 * When received data has been put in the area designated by the data parameter as 
 * requested by kjava_http_read(), call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_READ
 * @param option The size (in octets) of receive data put in the buffer designated by the 
 *               kjava_http_read() <i>data</i> parameter.
 *               Put a value between 1 and the value of the kjava_http_read() <i>dataLength</i> parameter.
 *               When all the response data received from the connected server has been passed to
 *               AJSC, pass 0. 
 */
#define     KJAVA_HTTP_EVENT_READ              7

/**
 * An HTTP/HTTPS connection close request by kjava_http_close() was accepted.
 *
 * When the HTTP/HTTPS connection has been closed as requested by kjava_http_close(), or 
 * when preparations for closing have been completed, 
 * call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_CLOSE
 * @param option 0
 */
#define     KJAVA_HTTP_EVENT_CLOSE             8

/**
 * An error occurred.
 *
 * When an error occurs in HTTP/HTTPS communication processing, call 
 * the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() 
 * with the following parameters to make an event notification to AJSC.
 *
 * @param param  The value of the <i>param</i> parameter passed to kjava_http_open().
 * @param cause  #KJAVA_HTTP_EVENT_ERROR
 * @param option Pass an appropriate error code, named starting with KJAVA_HTTP_ERROR_, based on the type of error.
 *               If there is no such error code, set any value above #KJAVA_HTTP_ERROR_CUSTOMER_SPEC_MIN.
 *
 * If #KJAVA_HTTP_ERROR_TIMEOUT or the value greater than or equal to #KJAVA_HTTP_ERROR_CUSTOMER_SPEC_MIN 
 * is designated to the <i>option</i> parameter, 
 * the behavior of AJSC depends on the value AJSC has designated to the <i>timeout</i> parameter 
 * of kjava_http_open(). 
 *
 * When #KJAVA_HTTP_ERROR_TIMEOUT is designated:
 * @htmlonly
 * <table border=1 cellspacing=0 cellpadding=2 width="100%">
 *  <tr>
 *   <th>
 *   @endhtmlonly
 *   The <i>timeout</i> parameter to kjava_http_open()
 *   @htmlonly
 *   </th>
 *   <th>The behavior of AJSC after the event notification</th>
 *  </tr>
 *  <tr>
 *   <td>1</td>
 *   <td>Throws an <code>InterruptedIOException</code></td>
 *  </tr>
 *  <tr>
 *   <td>0</td>
 *   <td>Throws an <code>IOException</code></td>
 *  </tr>
 * </table>
 * @endhtmlonly
 *
 * When the value greater than or equal to #KJAVA_HTTP_ERROR_CUSTOMER_SPEC_MIN is designated:
 * @htmlonly
 * <table border=1 cellspacing=0 cellpadding=2 width="100%">
 *  <tr>
 *   <th>
 *   @endhtmlonly
 *   The <i>timeout</i> parameter to kjava_http_open()
 *   @htmlonly
 *   </th>
 *   <th>The behavior of AJSC after the event notification</th>
 *  </tr>
 *  <tr>
 *   <td>1<br>0</td>
 *   <td>Throws an <code>IOException</code></td>
 *  </tr>
 * </table>
 * @endhtmlonly
 *
 */
#define     KJAVA_HTTP_EVENT_ERROR             0
/**
 * @}
 */

/**
 * @name HTTP Processing Error Code 
 * @{
 */
/**
 * Connection timeout
 *
 * If a timeout error occurs, with no response from the server after a set period, call
 * the #KJavaHttpCallbackProc type callback function passed to kjava_http_open() setting the error code in the option parameter.
 */
#define     KJAVA_HTTP_ERROR_TIMEOUT                                1

/**
 * The certificate contains an unrecognized critical extension.
 */
#define     KJAVA_HTTP_ERROR_CERT_BAD_EXTENSIONS                    101

/**
 * The server certificate chain exceeds the maximum depth specified by the issuer.
 */
#define     KJAVA_HTTP_ERROR_CERT_CHAIN_TOO_LONG                    102

/**
 * The server certificate has expired (it is no longer valid).
 */
#define     KJAVA_HTTP_ERROR_CERT_EXPIRED                           103

/**
 * An intermediate certificate in the chain has not been authorized by the 
 * Certificate Authority.
 */
#define     KJAVA_HTTP_ERROR_CERT_UNAUTHORIZED_INTERMEDIATE_CA      104
    
/**
 * The certificate is unsigned.
 */
#define     KJAVA_HTTP_ERROR_CERT_MISSING_SIGNATURE                 105

/**
 * The certificate is not yet valid.
 */
#define     KJAVA_HTTP_ERROR_CERT_NOT_YET_VALID                     106

/**
 * The site name on the certificate is not correct.
 */
#define     KJAVA_HTTP_ERROR_CERT_SITENAME_MISMATCH                 107

/**
 * The issuer of the certificate is unknown.
 */
#define     KJAVA_HTTP_ERROR_CERT_UNRECOGNIZED_ISSUER               108

/**
 * The certificate signature algorithm is not supported.
 */
#define     KJAVA_HTTP_ERROR_CERT_UNSUPPORTED_SIGALG                109

/**
 * The public key is used inappropriately by the certificate issuer.
 */
#define     KJAVA_HTTP_ERROR_CERT_INAPPROPRIATE_KEY_USAGE           110

/**
 * A certificate in the chain was not issued by the same Certificate Authority as the 
 * next certificate in the chain.
 */
#define     KJAVA_HTTP_ERROR_CERT_BROKEN_CHAIN                      111

/**
 * The public key of the root certificate has expired.
 */
#define     KJAVA_HTTP_ERROR_CERT_ROOT_CA_EXPIRED                   112

/**
 * The certificate public key type is not supported by the device.
 */
#define     KJAVA_HTTP_ERROR_CERT_UNSUPPORTED_PUBLIC_KEY_TYPE       113

/**
 * Certificate verification failed.
 */
#define     KJAVA_HTTP_ERROR_CERT_VERIFICATION_FAILED               114

/**
 * The minimum value in the customer-specified area
 */
#define     KJAVA_HTTP_ERROR_CUSTOMER_SPEC_MIN                      10000
/**
 * @}
 */

/**
 * @name HTTP Request Method 
 * @{
 */
/**
 * HTTP/HTTPS request method GET
 */
#define     KJAVA_HTTP_METHOD_GET      1

/**
 * HTTP/HTTPS request method HEAD
 */
#define     KJAVA_HTTP_METHOD_HEAD     2

/**
 * HTTP/HTTPS request method POST
 */
#define     KJAVA_HTTP_METHOD_POST     3
/**
 * @}
 */


/**
 * Handle type for HTTP/HTTPS connection
 */
typedef const void* KJavaHttpHandle;

/** The handle value indicating an invalid handle. */
#define KJAVA_INVALID_HANDLE   ((KJavaHttpHandle)0xFFFFFFFF)

/**
 * The data structure type for storing an HTTP/HTTPS header
 */
typedef struct _KJava_Http_HeaderTag {
    /**
     * A pointer to the ASCII string indicating the field name.\ (Not NUL-terminated)
     */
    char*      fieldName;

    /**
     * The length in octets of the string indicated by <i>fieldName</i>.
     */
    int        fieldNameLength;

    /**
     * A pointer to the ASCII string indicating the field value.\ (Not NUL-terminated)
     */
    char*      fieldValue;

    /**
     * The length in octets of the string indicated by <i>fieldValue</i>.
     */
    int        fieldValueLength;
} KJava_Http_Header;

/**
 *  The structure type for storing security related information of a secure connection.
 *  Every field in this structure must be filled after a connection is established.
 */
typedef struct _KJavaSecureInfoTag
{
    /**
     * The security protocol used in this secure connection.
     *
     * Set one of following values:
     * - #KJAVA_SECURITY_INFO_PROTOCOL_SSL
     * - #KJAVA_SECURITY_INFO_PROTOCOL_TLS
     * - #KJAVA_SECURITY_INFO_PROTOCOL_WTLS
     * .
     */
    int     securityProtocol;
    /**
     * The cipher suite used in this secure connection.
     *
     * It must be stored in format of (key_exchange)_(cipher)_(hash).
     * Example: "EDH_RSA_SHA1"
     */
    char    cipherSuite[20];

    /**
     * The server certificate type, NUL-terminated UTF8 string.
     *
     * For example, if the certificate is a X.509 certificate, store "X.509" in this field.
     */
    char    certType[8];
    /**
     * The version number of the server certificate.
     *
     * For example, if the certificate is a X.509 v3 certification, store 3 in this field.
     */
    int     certVersion;
    /**
     *  The serial number of the server certificate, NUL-terminated string.
     *
     *  Refer to Section 4.1.2.2 in RFC3280 for the format of serial number.
     */
    char    certSN[21];
    /**
     * The subject of the server certificate, NUL-terminated UTF8 string.
     *
     * Refer to the JkSecureSocketGetCertSubject() part in the document
     * <i>"JBlend[micro] Interface Reference: MIDP2.0 SecureConnection"</i> for details.
     */
    char    certSubject[400];
    /**
     * The issuer of the server certificate, NUL-terminated UTF8 string.
     *
     * Refer to the JkSecureSocketGetCertIssuer() part in the document
     * <i>"JBlend[micro] Interface Reference: MIDP2.0 SecureConnection"</i> for details.
     */
    char    certIssuer[400];
    /**
     * The algorithm used in the server certificate signature, NUL-terminated UTF8 string.
     *
     * The algorithm name format is a combination of the message digest algorithm and
     * public key algorithm, based on the items specified in RFC 3279.
     *
     * For example, for a certificate uses SHA-1 message digest and RSA algorithm, 
     * the signature algorithm would be "SHA1withRSA".
     */
    char    certSigAlgName[20];
    /**
     * The NotBefore time for the server certificate, NUL-terminated string.
     *
     * Store NULL if the valid term start time is not specified.
     * Refer to Section 4.1.2.5 "Validity" in RFC3280 for proper time format.
     */
    char    certNotBefore[20];
    /**
     * The time format used in the NotBefore field.
     *
     * Set one of these values:
     * - #KJAVA_CERT_TIME_UTC
     * - #KJAVA_CERT_TIME_GENERALIZED
     * .
     */
    int     certNBTimeType;
    /**
     * The NotAfter time for the server certificate, NUL-terminated string.
     *
     * Store NUL if the valid term start time is not specified.
     * See Section 4.1.2.5 "Validity" in RFC3280 for proper time format.
     */
    char    certNotAfter[20];
    /** 
     * The time format used in the NotAfter field.
     *
     * Set one of these values:
     * - #KJAVA_CERT_TIME_UTC
     * - #KJAVA_CERT_TIME_GENERALIZED
     * .
     */
    int     certNATimeType;
}
KJavaSecureInfo;

/**
 * The type of the callback function for notifying AJSC of an HTTP/HTTPS event.
 * @param param
 *        Pass the <i>param</i> parameter passed when the HTTP/HTTPS connection for which the event 
 *        occurred was created by kjava_http_open().
 * @param cause
 *        Pass a value appropriate for the event.
 * @param option
 *        Event details.
 *        Pass a value appropriate for the event.
 * @retval 1 if notification succeeds.
 * @retval 0 if it fails.
 */
typedef int (* KJavaHttpCallbackProc) ( int param, int cause, int option );

/** @} */

/**
 * @addtogroup HTTP_KSI HTTP/HTTPS KSI
 * An interface for performing HTTP/HTTPS communication processing.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread context.
 *
 * @par Include file 
 * \#include kjava_sys_http.h
 *
 * @{
 */

/**
 *        Opens an HTTP/HTTPS connection.
 * @param url
 *        The URL string  (not NUL-terminated).
 *        This pointer remains valid until the request result event is passed to AJSC.
 * @param urlLength
 *        The size (in octets) of the <i>url</i> parameter.
 * @param method
 *        The request method. 
 *        Either #KJAVA_HTTP_METHOD_GET, #KJAVA_HTTP_METHOD_HEAD, or #KJAVA_HTTP_METHOD_POST is designated.
 * @param param
 *        The value that must be passed as a parameter of the event when an event 
 *        is passed with the #KJavaHttpCallbackProc type callback function indicated by the <i>callback</i> parameter. 
 * @param timeout
 *        The flag which a MIDlet has designated in the <code>timeouts</code> parameter of the
 *        <code>javax.microedition.io.Connector.open(String name, int mode, boolean timeouts)</code> method.
 * @param callback
 *        The address of the callback function for notifying AJSC of processing results.
 * @return
 *        When an HTTP/HTTPS connection is created normally, return a handler 
 *        value indicating the created connection.
 *        If an HTTP/HTTPS connection could not be created, return #KJAVA_INVALID_HANDLE.
 *
 * This function is called in order to create a connection to an HTTP server.
 * The timing for actually connecting to the HTTP server is an implementation 
 * dependent matter.
 * To enable other functions to perform various operations on the created 
 * HTTP/HTTPS connection, issue a handle value that uniquely identifies the 
 * connection and notify this handle as a return value. 
 * The created connection and the handle value issued for it should remain valid
 * until kjava_http_close() is called.
 *
 * In the native system, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * to pass either of the following events to AJSC, depending on the processing result.  
 * - #KJAVA_HTTP_EVENT_OPEN <br> 
 *   when establishing connection or connection preparation succeeds. 
 * - #KJAVA_HTTP_EVENT_ERROR <br> 
 *   - when an error occurs either in the native system or at the destination server,
 *   - or when the processing is canceled by kjava_http_close(). 
 * .
 *
 * Even if kjava_http_close() is called before the processing result for this function is passed to 
 * AJSC (due to JVM suspension or a close request), it is still necessary to notify AJSC of the 
 * processing result for this function by passing an event.
 *
 * AJSC sets 1 to the <i>timeout</i> parameter only when a MIDlet has designated <code>true</code> to the 
 * <code>timeouts</code> parameter of the <code>javax.microedition.io.Connector.open(String name, int mode, boolean timeouts)</code> 
 * method, AJSC sets 0 to the <i>timeout</i> parameter otherwise.
 * When the native system notifies AJSC of a #KJAVA_HTTP_EVENT_ERROR event by 
 * the callback function passed to kjava_http_open(),
 * if #KJAVA_HTTP_ERROR_TIMEOUT or the value greater than or equal to #KJAVA_HTTP_ERROR_CUSTOMER_SPEC_MIN is designated 
 * to the <i>option</i> parameter, the behavior of AJSC depends on the value AJSC has designated to 
 * the <i>timeout</i> parameter to kjava_http_open(). 
 * For the details of this behavior, refer to the description of #KJAVA_HTTP_EVENT_ERROR.
 *
 * @see KJavaHttpCallbackProc, kjava_http_close()
 */
KJavaHttpHandle kjava_http_open( const char* url, int urlLength, int method, int param, int timeout, KJavaHttpCallbackProc callback );


/**
 *        Sends an HTTP/HTTPS request header.
 * @param connection
 *        The applicable HTTP/HTTPS connection. The value returned by kjava_http_open() is designated.
 * @param header
 *        A pointer to the array of KJava_Http_Header data structures holding the HTTP/HTTPS requests.
 *        The termination of each header does not include a line break code (CR or LF). <br>
 *        This pointer remains valid until AJSC is notified of the request result.
 * @param headerCount
 *        The number of the #KJava_Http_Header data structures pointed to by the <i>header</i> parameter.
 * @retval  0 if the operation succeeds.
 * @retval -1 if it fails.
 *
 * This function is called to send an HTTP/HTTPS header to an HTTP server. 
 * The actual send timing to the HTTP server is implementation dependent.
 *
 * In the native system, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * to pass either of the following events to AJSC, depending on the processing result.  
 * - #KJAVA_HTTP_EVENT_WRITE_HEADER <br> 
 *   when sending or preparations for sending is complete.
 * - #KJAVA_HTTP_EVENT_ERROR <br> 
 *   - when an error occurs either in the native system or at the destination server, 
 *   - or when the processing is canceled by kjava_http_close(). 
 * .
 *
 * Even if kjava_http_close() is called before the processing result for this function is passed to 
 * AJSC (due to JVM suspension or a close request), it is still necessary to notify AJSC of the 
 * processing result for this function by passing an event.
 *
 * The sequence of the individual HTTP/HTTPS header pointers indicated by the 
 * header parameter may be changed for sorting or other editing, so long as it 
 * is still possible to free the memory allocated for the HTTP/HTTPS header.
 *
 * In the HTTP communication that is performed after a MIDlet calls 
 * <code>flush</code> method of an <code>OutputStream</code> object 
 * created from a <code>javax.microedition.io.HttpConnection</code>,
 * AJSC calls kjava_http_open() to create an HTTP/HTTPS connection, 
 * then calls this function to pass to the native system the 
 * HTTP/HTTPS headers added by the MIDlet and the following header.
 * <pre>
 * transfer-encoding: chunked
 * </pre>
 *
 * @if JTWI
 * @par For compliance with JTWI 1.0:
 * If the MIDlet currently being executed on a GSM/UMTS (W-CDMA) handset is an untrusted MIDlet,
 * JTWI-compliant AJSC calls this function appending the following header information 
 * to that designated by the MIDlet.
 * <br><br><br>
 * @htmlonly
 * <table border=1 cellspacing=0 cellpadding=2 width="100%">
 * <tr><td><b> Member of KJava_Http_Header Structure </b></td>
 *   <td><b>Value Set </b></td></tr>
 * <tr><td>fieldName</td><td>User-Agent</td></tr>
 * <tr><td>fieldNameLength</td><td>10</td></tr>
 * <tr><td>fieldValue</td><td>UNTRUSTED/1.0</td></tr>
 * <tr><td>fieldValueLength</td><td>13</td></tr>
 * </table>
 * @endhtmlonly
 * <br>
 * An HTTP request must be sent containing this header information along with the User-Agent 
 * header designated by the MIDlet.
 * @endif
 *
 *
 * @see KJavaHttpCallbackProc, kjava_http_open()
 */
int kjava_http_write_header( KJavaHttpHandle connection, KJava_Http_Header header[], int headerCount );


/**
 *        Sends an HTTP/HTTPS request body.
 * @param connection
 *        The applicable HTTP/HTTPS connection. The value returned by kjava_http_open() is designated.
 * @param data
 *        A pointer to the HTTP/HTTPS request body to be sent.
 *        This pointer remains valid until the request result event is notified to AJSC.
 * @param dataLength
 *        The parameter data size in octets.
 *
 * @retval  0 if the operation succeeds.
 * @retval -1 if it fails.
 *
 * This function is called to send an HTTP/HTTPS request body to the HTTP server. 
 * The actual data send timing is implementation dependent.
 *
 * In the native system, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * to pass either of the following events to AJSC, depending on the processing result.  
 * - #KJAVA_HTTP_EVENT_WRITE <br> 
 *   when request body sending or preparations for sending is complete.
 * - #KJAVA_HTTP_EVENT_ERROR <br> 
 *   - when an error occurs either in the native system or at the destination server, 
 *   - or when the processing is canceled by kjava_http_close(). 
 * .
 * Even if kjava_http_close() is called before the processing result for this function is passed to 
 * AJSC (due to JVM suspension or a close request), it is still necessary to notify AJSC of the 
 * processing result for this function by passing an event.
 *
 * It is allowable to process only the amount of data that can be handled, 
 * without completing all the designated request body processing.
 * Designate the size of the processed request body in the option parameter 
 * with the #KJavaHttpCallbackProc type callback function passed to kjava_http_open().
 * AJSC looks at the processed data size as notified in the 
 * #KJAVA_HTTP_EVENT_WRITE event and continues to call this function until the entire 
 * request body has been processed. 
 *
 * In the HTTP communication that is performed after a MIDlet calls 
 * <code>flush</code> method of an <code>OutputStream</code> object 
 * created from <code>javax.microedition.io.HttpConnection</code>,
 * AJSC performs chunked encoding, treating the data written to 
 * that <code>OutputStream</code> object as one chunk, then passes 
 * the chunk size and chunk data to the native system by this function.
 * See RFC2616 3.6.1, "Chunked Transfer Coding" for details of the encoding. 
 *
 *
 * @see KJavaHttpCallbackProc, kjava_http_open()
 */
int kjava_http_write( KJavaHttpHandle connection, const unsigned char* data, int dataLength );

/**
 *        Sends request body data buffered in the native system to the HTTP/HTTPS server.
 * @param connection
 *        The applicable HTTP/HTTPS connection. The value returned by kjava_http_open() is designated.
 * @retval  0 if the operation succeeds.
 * @retval -1 if it fails.
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
 * In the native system, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * to pass either of the following events to AJSC, depending on the processing result.  
 * - #KJAVA_HTTP_EVENT_FLUSH <br> 
 *   when buffered HTTP/HTTPS request body sending is all completed.
 * - #KJAVA_HTTP_EVENT_ERROR <br> 
 *   - when an error occurs either in the native system or at the destination server, 
 *   - or when the processing is canceled by kjava_http_close(). 
 * .
 * Even if kjava_http_close() is called before the processing result for this function is passed to 
 * AJSC (due to JVM suspension or a close request), it is still necessary to notify AJSC of the 
 * processing result for this function by passing an event. 
 *
 * In the HTTP communication that is performed after a MIDlet calls 
 * <code>flush</code> method of an <code>OutputStream</code> object 
 * created from <code>javax.microedition.io.HttpConnection</code>,
 * AJSC calls kjava_http_write() to pass to the native system the 
 * data written to that <code>OutputStream</code> object, then 
 * calls this function to request data transfer.
 *
 * @see KJavaHttpCallbackProc, kjava_http_open(), kjava_http_write()
 */
int kjava_http_flush( KJavaHttpHandle connection );


/**
 *        Notifies the completion of an HTTP/HTTPS request.
 * @param connection
 *        The applicable HTTP/HTTPS connection. 
 *        The value returned by kjava_http_open() is designated.
 * @retval  0 if the operation succeeds.
 * @retval -1 if it fails.
 *
 * This function is called to notify the HTTP server that the HTTP/HTTPS request has 
 * been completed. After this function is called, kjava_http_write_header() and  
 * kjava_http_write() will not be called for the same HTTP/HTTPS connection.
 *
 * In the native system, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * to pass either of the following events to AJSC, depending on the processing result.  
 * - #KJAVA_HTTP_EVENT_FINISH_REQUEST <br> 
 *   when the request was sent successfully. Preparation for response receipt may proceed
 * - #KJAVA_HTTP_EVENT_ERROR <br> 
 *   - when an error occurs either in the native system or at the destination server, 
 *   - or when the processing is canceled by kjava_http_close(). 
 * .
 * Even if kjava_http_close() is called before the processing result for this function is passed to 
 * AJSC (due to JVM suspension or a close request), it is still necessary to notify AJSC of the 
 * processing result for this function by passing an event. 
 *
 *
 * After the #KJAVA_HTTP_EVENT_FINISH_REQUEST event is passed, kjava_http_read() is called 
 * requesting receipt of the HTTP/HTTPS response.
 *
 * @see kjava_http_write_header(), kjava_http_write(), kjava_http_read()
 */
int kjava_http_finish_request( KJavaHttpHandle connection );


/**
 *        Gets the HTTP/HTTPS response received from the HTTP server.
 * @param connection
 *        The applicable HTTP/HTTPS connection. 
 *        The value returned by kjava_http_open() is designated.
 * @param data
 *        A pointer to the area for putting the data received from the HTTP server.
 *        This pointer remains valid until a request result event is notified to AJSC.
 * @param dataLength
 *        The size (in octets) of the area designated by the <i>data</i> parameter.
 * @retval  0 if the operation succeeds.
 * @retval -1 if it fails.
 *
 * This function is called to get the HTTP/HTTPS response received from the HTTP server. 
 * Note that no flow control of the receive data is performed in AJSC. 
 * If flow control is necessary, it must be implemented by the device manufacturer.
 *
 * In the native system, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * to pass either of the following events to AJSC, depending on the processing result.  
 * - #KJAVA_HTTP_EVENT_READ <br> 
 *   when the received data has been stored in the memory space indicated by the <i>data</i> parameter.
 * - #KJAVA_HTTP_EVENT_ERROR <br> 
 *   - when an error occurs either in the native system or at the destination server, 
 *   - or when the processing is canceled by kjava_http_close(). 
 * .
 * Even if kjava_http_close() is called before the processing result for this function is passed to 
 * AJSC (due to JVM suspension or a close request), it is still necessary to notify AJSC of the 
 * processing result for this function by passing an event. 
 *
 *
 * The format of the HTTP response to be passed in the data parameter must 
 * conform to the format specified in RFC 2616.
 * Below is an example of an HTTP response that is in accordance with 
 * RFC 2616, Section 6, "Response."
 *
 * @code
 * HTTP/1.1 200 OK
 * Date: Wed, 24 Mar 2004 08:00:25 GMT
 * Content-Length: 23
 * Connection: close
 * Content-Type: text/plain; charset=ISO-8859-1
 * 
 * HTTP response message
 * @endcode
 * 
 * Since HTTP responses whose status code starts with 1, such as HTTP/1.1 1xx, 
 * are temporary, do not pass them to AJSC.
 * Pass to AJSC only the eventual responses following them.
 *
 * @see KJavaHttpCallbackProc, kjava_http_open()
 */
int kjava_http_read( KJavaHttpHandle connection, unsigned char* data, int dataLength );

/**
 *        Gets the HTTP/HTTPS response size that can be obtained with no I/O blocking.
 * @param connection
 *        The applicable HTTP/HTTPS connection. 
 *        The value returned by kjava_http_open() is designated.
 * @return
 *        Return the HTTP/HTTPS response size (in octets) that can be obtained without 
 *        I/O blocking, that is, the size buffered in the communication layer by the 
 *        manufacturer-implemented processing at the time this function is called.
 *        In case of error, return -1.
 *
 * Return the HTTP/HTTPS response size already received from the HTTP server, buffered 
 * in the communication layer and not yet passed to AJSC in response to 
 * kjava_http_read().
 * 
 * In processing of this function it is not necessary to notify an HTTP/HTTPS event to AJSC. 
 * Return control to AJSC as soon as possible so that AJSC processing will not be blocked by this function for too long.
 *
 * @see kjava_http_open()
 */
int kjava_http_available( KJavaHttpHandle connection );

/**
 *        Closes an HTTP/HTTPS connection.
 * @param connection
 *        The HTTP/HTTPS connection to be closed. 
 *        The value returned by kjava_http_open() is designated.
 * @retval  0 if the close operation succeeds.
 * @retval -1 if it fails.
 *
 * This function is called to close the HTTP/HTTPS connection designated in 
 * the connection parameter. Free the resources allocated for the designated 
 * connection. After this function is called, the designated connection can no 
 * longer be used.
 *
 * In the native system, call the #KJavaHttpCallbackProc type callback function passed to kjava_http_open()
 * to pass either of the following events to AJSC, depending on the processing result.  
 * - #KJAVA_HTTP_EVENT_CLOSE <br> 
 *   when the request to close the HTTP/HTTPS connection is accepted.
 * - #KJAVA_HTTP_EVENT_ERROR <br> 
 *   when an error occurs either in the native system or at the destination server
 * .
 * It must be possible to call this function at any point while an HTTP/HTTPS connection is created.
 *
 * If the processing result for any of the following functions has not been 
 * passed to AJSC at the time this function is called, 
 * notify AJSC of not only the result of kjava_http_close() but also the results of 
 * the processing requested with these functions, by passing events.
 * <ul>
 *   <li>kjava_http_open()
 *   <li>kjava_http_write_header()
 *   <li>kjava_http_write()
 *   <li>kjava_http_flush()
 *   <li>kjava_http_finish_request()
 *   <li>kjava_http_read()
 * </ul>
 *
 * After this function is called, no more processing requests will be made for the 
 * HTTP/HTTPS connection designated in the <i>connection</i> parameter. 
 *
 * @see KJavaHttpCallbackProc, kjava_http_open()
 */
int kjava_http_close( KJavaHttpHandle connection );


/**
 *        Retrieves security related information for a HTTPS connection.
 * @param connection
 *        The HTTP/HTTPS connection. 
 *        The value returned by kjava_http_open() is designated.
 * @param secureInfo
 *        A pointer to the KJavaSecureInfo structure for putting store security related information. 
 * @retval  0 if all the security information is successfully stored in the structure.
 * @retval -1 if the operation fails.
 *
 * This function is called once after the #KJAVA_HTTP_EVENT_ESTABLISH_SSL_SESSION event is passed.
 */
int kjava_http_get_secureinfo( KJavaHttpHandle connection, KJavaSecureInfo *secureInfo );

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* KJAVA_SYS_HTTP_HEADER */
