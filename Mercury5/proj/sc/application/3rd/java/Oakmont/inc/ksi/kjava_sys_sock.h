/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 *  @file kjava_sys_sock.h
 *  Socket KSI
 */

#ifndef KJAVA_SYS_SOCK_HEADER
#define KJAVA_SYS_SOCK_HEADER

#ifdef __cplusplus
extern "C"{
#endif



/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup Socket_KSI
 * An interface for performing socket communication processing.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread context.
 *
 * @par Include file
 * \#include kjava_sys_sock.h
 * @{
 */
/**
 * @name Socket Processing Event Code
 * @{
 */
/**
 * Socket connect result notification event.
 *
 * This is used for notifying of the result of kjava_sock_connect() processing.
 */
#define KJAVA_SOCKET_EVENT_TYPE_CONNECT     1
/**
 * Socket send result notification event.
 *
 * This is used for notifying of the result of kjava_sock_send() processing.
 */
#define KJAVA_SOCKET_EVENT_TYPE_SEND        2
/**
 * Socket receive result notification event.
 *
 * This is used for notifying of the result of kjava_sock_receive() processing.
 */
#define KJAVA_SOCKET_EVENT_TYPE_RECEIVE     3
/**
 * Socket shutdown result notification event.
 *
 * This is used for notifying of the result of kjava_sock_shutdown() processing.
 */
#define KJAVA_SOCKET_EVENT_TYPE_SHUTDOWN    4
/**
 * Socket close/destroy result notification event.
 *
 * This is used for notifying of the result of kjava_sock_close() processing.
 */
#define KJAVA_SOCKET_EVENT_TYPE_CLOSE       5
/**
 * @}
 */

/**
 * @name Socket Processing Error Code
 * @{
 */
/**
 * Socket operation succeeded.
 */
#define KJAVA_SOCKET_SUCCESS                                        0
/**
 * Socket operation interrupted due to a time out.
 */
#define KJAVA_SOCKET_ERROR_TIMEOUT                                  -20000
/**
 * An internal error occurred.
 */
#define KJAVA_SOCKET_ERROR_OTHER                                    -30000
/**
 * The certificate contains an unrecognized critical extension.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_BAD_EXTENSIONS               -101
/**
 * The server certificate chain exceeds the maximum depth specified by the issuer.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_CHAIN_TOO_LONG               -102
/**
 * The server certificate has expired (it is no longer valid).
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_EXPIRED                      -103
/**
 * An intermediate certificate in the chain has not been authorized by the Certificate Authority.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_UNAUTHORIZED_INTERMEDIATE_CA -104
/**
 * The certificate is unsigned.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_MISSING_SIGNATURE            -105
/**
 * The certificate is not yet valid.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_NOT_YET_VALID                -106
/**
 * The site name on the certificate is not correct.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_SITENAME_MISMATCH            -107
/**
 * The issuer of the certificate is unknown.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_UNRECOGNIZED_ISSUER          -108
/**
 * The certificate signature algorithm is not supported.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_UNSUPPORTED_SIGALG           -109
/**
 * The public key is used inappropriately by the certificate issuer.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_INAPPROPRIATE_KEY_USAGE      -110
/**
 * A certificate in the chain was not issued by the same Certificate
 * Authority as the next certificate in the chain.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_BROKEN_CHAIN                 -111
/**
 * The public key of the root certificate has expired.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_ROOT_CA_EXPIRED              -112
/**
 * The certificate public key type is not supported by the device.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_UNSUPPORTED_PUBLIC_KEY_TYPE  -113
/**
 * Certificate verification failed.
 */
#define KJAVA_SOCKET_SECURE_ERROR_CERT_VERIFICATION_FAILED          -114
/**
 * @}
 */

/**
 * @name Socket Shutdown Type
 * @{
 */
/**
 * Shutdown receiving direction only.
 */
#define KJAVA_SOCKET_SHUTDOWN_RECEIVE       1
/**
 * Shutdown sending direction only.
 */
#define KJAVA_SOCKET_SHUTDOWN_SEND          2
/**
 * Shutdown both sending and receiving directions.
 */
#define KJAVA_SOCKET_SHUTDOWN_BOTH          3
/**
 * @}
 */


/**
 * @name Socket Processing Option
 * @{
 */
/**
 * Socket option: Whether to use Nagle algorithm.
 */
#define KJAVA_SOCKET_OPTION_DELAY           1
/**
 * Socket option: Whether to send KEEPALIVE signal.
 */
#define KJAVA_SOCKET_OPTION_KEEPALIVE       2
/**
 * Socket option: Linger time (wait time before disconnecting socket).
 */
#define KJAVA_SOCKET_OPTION_LINGER          3
/**
 * Socket option: Receive buffer size in bytes.
 */
#define KJAVA_SOCKET_OPTION_RCVBUF          4
/**
 * Socket option: Send buffer size in bytes.
 */
#define KJAVA_SOCKET_OPTION_SNDBUF          5
/**
 * @}
 */

/**
 * @name Security Protocol Used in Secure Socket
 * @{
 */
/**
 * SSL Protocol Version 3.0.
 */
#define KJAVA_SECURITY_INFO_PROTOCOL_SSL    0
/**
 * TLS Protocol Version 1.0, or WAP TLS Profile and Tunneling.
 */
#define KJAVA_SECURITY_INFO_PROTOCOL_TLS    1
/**
 * Wireless Transport Layer Security.
 */
#define KJAVA_SECURITY_INFO_PROTOCOL_WTLS   2
/**
 * @}
 */

/**
 * @name Time Type of Certificate
 * @{
 */
/**
 * UTC Time type.
 */
#define KJAVA_CERT_TIME_UTC                 (int)0
/**
 * Generalized Time type.
 */
#define KJAVA_CERT_TIME_GENERALIZED         (int)1
/**
 * @}
 */

/**
 * The function type of the result notification callback for Socket KSI functions.
 * @param connectionID
 *        The ID of the connection.
 * @param type
 *        The type of event. Designate one of the following
 *        types based on the KSI function causing the event
 *        notification:
 *        - kjava_sock_connect()<br>
 *            #KJAVA_SOCKET_EVENT_TYPE_CONNECT
 *        - kjava_sock_send()<br>
 *            #KJAVA_SOCKET_EVENT_TYPE_SEND
 *        - kjava_sock_receive()<br>
 *            #KJAVA_SOCKET_EVENT_TYPE_RECEIVE
 *        - kjava_sock_shutdown()<br>
 *            #KJAVA_SOCKET_EVENT_TYPE_SHUTDOWN
 *        - kjava_sock_close()<br>
 *            #KJAVA_SOCKET_EVENT_TYPE_CLOSE
 *        .
 * @param result
 *        The result of this event type. Designate one of the
 *        following types based on the KSI function causing the
 *        event notification:
 *        - kjava_sock_connect()<br>
 *          Designate #KJAVA_SOCKET_SUCCESS if the operation succeeded.
 *          If the operation failed, designate one of the following values as appropriate.
 *          - #KJAVA_SOCKET_ERROR_TIMEOUT
 *          - #KJAVA_SOCKET_ERROR_OTHER
 *          - an appropriate error code of those named starting with KJAVA_SOCKET_SECURE_ERROR_CERT_.
 *        - kjava_sock_send()<br>
 *          Designate the size (in bytes) of data actually sent if the operation succeeded.
 *          If the operation failed, designate one of the following values as appropriate.
 *          - #KJAVA_SOCKET_ERROR_TIMEOUT
 *          - #KJAVA_SOCKET_ERROR_OTHER
 *        - kjava_sock_receive()<br>
 *          Designate the size (in bytes) of data actually received if the operation succeeded.
 *          If the operation failed, designate one of the following values as appropriate.
 *          - #KJAVA_SOCKET_ERROR_TIMEOUT
 *          - #KJAVA_SOCKET_ERROR_OTHER
 *        - kjava_sock_shutdown()<br>
 *          Designate #KJAVA_SOCKET_SUCCESS if the operation succeeded.
 *          If the operation failed, designate one of the following values as appropriate.
 *          - #KJAVA_SOCKET_ERROR_TIMEOUT
 *          - #KJAVA_SOCKET_ERROR_OTHER
 *        - kjava_sock_close()<br>
 *          Designate #KJAVA_SOCKET_SUCCESS if the operation succeeded.
 *          If the operation failed, designate one of the following values as appropriate.
 *          - #KJAVA_SOCKET_ERROR_TIMEOUT
 *          - #KJAVA_SOCKET_ERROR_OTHER
 *        .
 *
 */
typedef void (*KJavaNetworkCallbackProc) (int connectionID, int type, int result);

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
     * Refer to the JkSecureSocketGetCertSubject part in the document
     * <i>"JBlend [micro] Interface Reference: MIDP2.0 SecureConnection"</i> for detail.
     */
    char    certSubject[400];
    /**
     * The issuer of the server certificate, NUL-terminated UTF8 string.
     *
     * Refer to the JkSecureSocketGetCertIssuer part in the document
     * <i>"JBlend [micro] Interface Reference: MIDP2.0 SecureConnection"</i> for detail.
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
     * Store NULL if the valid term start time is not specified.
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
 * The structure type for containing local connection information.
 * Every field in this structure must be filled after a connection is established.
 */
typedef struct _KJavaLocalInfoTag
{
    /**
     * The local IP address of the connection. A NUL-terminated string.
     */
    char                localAddress[16];
    /**
     * The local port number of the connection.
     */
    int                 localPort;

    /**
     * Security related information for the secure connection.
     *
     * Set #AJ_NULL when the <i>secure</i> parameter passed to kjava_sock_open() is 0.
     */
    KJavaSecureInfo     *secureInfo;
}
KJavaLocalInfo;


/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/**
 * Gets the number of maximum concurrent connections.
 *
 * @return The number of the maximum concurrent connections.
 *
 * This function is called only once, at JVM startup.
 *
 * AJSC will not request the creation or connection of a socket if
 * it would exceed the limit returned by this function for simultaneous socket connections.
 */
int kjava_sock_getMaxSessions(void);

/**
 *        Opens a new connection handle.
 * @param addr
 *        A pointer to the NUL-terminated string indicating the address of a remote host.
 * @param port
 *        The port number of the remote host.
 * @param secure
 *        A flag indicating whether or not the socket is secure.
 *        #AJ_TRUE indicates secure socket; #AJ_FALSE, ordinary socket.
 *        When the AJSC built-in SSL option is enabled, only #AJ_FALSE is passed in this parameter.
 *        See @ref page_built_in_ssl for details of the built-in SSL.
 * @param connectionID_p
 *        A pointer to the buffer for putting the allocated connection ID.
 * @param callback
 *        The address of the callback function which notifies AJSC of
 *        socket-related processing results. The address remains valid
 *        until kjava_sock_close() is called for the specified socket
 *        if kjava_sock_open() returns #KJAVA_SOCKET_SUCCESS.
 * @return
 *        Return #KJAVA_SOCKET_SUCCESS if the operation succeeds, otherwise return an error code.
 *
 * The native system must create a socket with the passed parameters and
 * store the identifier assigned to the socket in the buffer indicated by
 * <i>connectionID_p</i>.
 *
 * The function address passed in <i>callback</i> must be held in the native
 * system to notify AJSC of results of other Socket KSI functions.
 * See description of #KJavaNetworkCallbackProc for details.
 *
 * When this function is called, make the necessary preparations in the native
 * system for socket communication. Note that processing likely to block AJSC
 * processing for an extended period must not be performed in this function.
 *
 * @see KJavaNetworkCallbackProc
 */
int kjava_sock_open(const unsigned char *addr, int port, int secure,
                    int *connectionID_p, KJavaNetworkCallbackProc callback);

/**
 *        Establishes a socket connection using a specified connection handle.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @param localInfo_p
 *        A pointer to the structure holding the local connection information.
 * @return
 *        Return #KJAVA_SOCKET_SUCCESS if the operation succeeds, otherwise return an error code.
 *
 *
 * In the native system, connect the socket designated in the
 * <i>connectionID</i> parameter to the remote end and establish a session,
 * enabling communication on that connection.
 *
 * In order to not block AJSC processing, after requesting connection processing by
 * the separate task, immediately return control to AJSC, passing #KJAVA_SOCKET_SUCCESS as the return value.
 * If an error occurs before connection processing by the separate task could
 * be requested, return one of the error codes below depending on the error cause.
 *   - #KJAVA_SOCKET_ERROR_TIMEOUT
 *   - #KJAVA_SOCKET_ERROR_OTHER
 *   .
 *
 * If #KJAVA_SOCKET_SUCCESS is passed as the return value, call
 * the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open()
 * at the time of any of the following occasions to notify AJSC of the result.
 * <dl>
 * <dt>Socket connection (and SSL session) establishment succeeded.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #KJAVA_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by kjava_sock_close().</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>:  #KJAVA_SOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #KJAVA_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>SSL session establishment failed because the server sent an invalid server certificate.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>:  #KJAVA_SOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: One of the following error codes as appropriate
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_BAD_EXTENSIONS
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_CHAIN_TOO_LONG
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_EXPIRED
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_UNAUTHORIZED_INTERMEDIATE_CA
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_MISSING_SIGNATURE
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_NOT_YET_VALID
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_SITENAME_MISMATCH
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_UNRECOGNIZED_ISSUER
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_UNSUPPORTED_SIGALG
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_INAPPROPRIATE_KEY_USAGE
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_BROKEN_CHAIN
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_ROOT_CA_EXPIRED
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_UNSUPPORTED_PUBLIC_KEY_TYPE
 *         - #KJAVA_SOCKET_SECURE_ERROR_CERT_VERIFICATION_FAILED
 *         .
 *      If there were multiple errors, pass the most noteworthy error code.
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>:  #KJAVA_SOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *         - #KJAVA_SOCKET_ERROR_TIMEOUT
 *         - #KJAVA_SOCKET_ERROR_OTHER
 *         .
 *   </ul>
 * </dd>
 * </dl>
 *
 * If a value other than #KJAVA_SOCKET_SUCCESS is returned, do not make event
 * notification by the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open().
 *
 * If the connection and SSL session establishment succeeded and
 * #KJAVA_SOCKET_SUCCESS is returned, AJSC assumes that the <code>SecureConnection</code>
 * security information and server certificate information can be acquired.
 * In the native system, enable acquisition of security information and
 * server certificate information using the kjava_http_get_secureinfo() function
 * after event notification to AJSC until kjava_sock_close() is called.
 *
 * If an event is passed because of a server certificate error, AJSC calls
 * kjava_http_get_secureinfo() to get information about the invalid server certificate.
 * The native system must pass the server certificate information to AJSC.
 *
 *
 * @see KJavaNetworkCallbackProc
 */
int kjava_sock_connect(int connectionID, KJavaLocalInfo *localInfo_p);

/**
 *        Sends data over a connection.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @param data
 *        A pointer to the buffer holding the data to be sent.
 * @param datalen
 *        The length in bytes of the data indicated by the <i>data</i> parameter.
 * @return
 *        Return #KJAVA_SOCKET_SUCCESS if the operation succeeds, otherwise return an error code.
 *
 *
 * In the native system, send the data indicated by the <i>data</i> parameter
 * to the secure socket connection remote end.
 *
 * In order to not block AJSC processing, after requesting transmission processing by
 * the separate task, immediately return control to AJSC, passing #KJAVA_SOCKET_SUCCESS
 * as the return value.
 * If an error occurs before send processing by the separate task could be
 * requested, return one of the error codes below depending on the error cause.
 *   - #KJAVA_SOCKET_ERROR_TIMEOUT
 *   - #KJAVA_SOCKET_ERROR_OTHER
 *   .
 *
 * If #KJAVA_SOCKET_SUCCESS is passed as the return value, call
 * the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open()
 * at the time of any of the following occasions to notify AJSC of the result.
 * <dl>
 * <dt>Send processing succeeded.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: The size of data actually sent
 *   </ul>
 * If the value passed in <i>result</i> is smaller than the send size requested by
 * kjava_sock_send(), AJSC repeats the cycle of calling this function and
 * waiting for an event, until all data sending is complete.
 * </dd>
 * <p>
 * <dt>The connection was closed by the peer, or was already closed.</dt>
 * <dt>The processing was canceled by kjava_sock_close().</dt>
 * <dt>kjava_sock_shutdown() was called passing #KJAVA_SOCKET_SHUTDOWN_SEND or #KJAVA_SOCKET_SHUTDOWN_BOTH
 * in the <i>method</i> parameter, canceling the processing. </dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: #KJAVA_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #KJAVA_SOCKET_ERROR_TIMEOUT
 *       - #KJAVA_SOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 *
 * If a value other than #KJAVA_SOCKET_SUCCESS is returned, do not make event
 * notification by the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open().
 *
 * This function is never called again for the same socket until its
 * result is returned. It may, however, be called for a different socket.
 *
 *
 * @see KJavaNetworkCallbackProc
 */
int kjava_sock_send(int connectionID, const unsigned char *data, int datalen);

/**
 *        Receives data from a connection.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @param data
 *        A pointer to the buffer for putting the received data.
 * @param datalen
 *        The size of the buffer indicated by the <i>data</i> parameter.
 * @return
 *        Return #KJAVA_SOCKET_SUCCESS if the operation succeeds, otherwise return an error code.
 *
 *
 * In the native system, put the data received from the secure socket connection
 * remote end to the buffer pointed to by the <i>data</i> parameter.
 *
 * In order to not block AJSC processing, after requesting receive processing by
 * a separate task, return control to AJSC, passing #KJAVA_SOCKET_SUCCESS
 * as the return value.
 * If an error occurs before receive processing by the separate task could
 * be requested, return one of the error codes below depending on the error cause.
 *   - #KJAVA_SOCKET_ERROR_TIMEOUT
 *   - #KJAVA_SOCKET_ERROR_OTHER
 *   .
 *
 * If #KJAVA_SOCKET_SUCCESS is passed as the return value, call
 * the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open()
 * at the time of any of the following occasions to notify AJSC of the result.
 * <dl>
 * <dt>Receive processing succeeded.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: The size of data actually received
 *   </ul>
 * It does not matter if the data size passed in the <i>result</i> parameter
 * is smaller than the receive data size requested by kjava_sock_receive().
 * </dd>
 * <p>
 * <dt>The connection was closed by the peer, or was already closed.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: #KJAVA_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <dt>kjava_sock_shutdown() was called passing
 * #KJAVA_SOCKET_SHUTDOWN_RECEIVE or #KJAVA_SOCKET_SHUTDOWN_BOTH in the <i>method</i> parameter, canceling the
 * processing. </dt>
 * <dt>The processing was canceled by kjava_sock_close().</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: #KJAVA_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #KJAVA_SOCKET_ERROR_TIMEOUT
 *       - #KJAVA_SOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 *
 * If a value other than #KJAVA_SOCKET_SUCCESS is returned, do not make event
 * notification by the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open().
 *
 * This function is never called again for the same socket until its result
 * is returned. It may, however, be called for a different socket.
 *
 *
 * @see KJavaNetworkCallbackProc
 */
int kjava_sock_receive(int connectionID, unsigned char *data, int datalen);

/**
 *        Gets the size of available data in the buffer of the protocol stack.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @return
 *        Return the size of received data that AJSC can acquire without I/O blocking.
 *        In case of error, return an error code.
 *
 * This function should return control to AJSC as quickly as possible, to
 * avoid blocking AJSC processing for an extended period.
 */
int kjava_sock_available(int connectionID);

/**
 *        Shuts down a connection.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @param method
 *        The direction for shutting down the connection.
 *        One of the following values is designated.
 *        - #KJAVA_SOCKET_SHUTDOWN_RECEIVE
 *        - #KJAVA_SOCKET_SHUTDOWN_SEND
 *        - #KJAVA_SOCKET_SHUTDOWN_BOTH
 *        .
 * @return
 *        Return #KJAVA_SOCKET_SUCCESS if the operation succeeds, otherwise return an error code.
 *
 * This function is called during the time after the calling of kjava_sock_connect()
 * and until kjava_sock_close() is called.
 *
 * In order to not block AJSC processing, after requesting shut down processing by
 * a separate task, immediately return control to AJSC, passing #KJAVA_SOCKET_SUCCESS
 * as the return value.
 * If an error occurs before shutdown processing by the separate task could be
 * requested, return one of the error codes below depending on the error cause.
 *   - #KJAVA_SOCKET_ERROR_TIMEOUT
 *   - #KJAVA_SOCKET_ERROR_OTHER
 *   .
 *
 * If #KJAVA_SOCKET_SUCCESS is passed as the return value, call
 * the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open()
 * at the time of any of the following occasions to notify AJSC of the result.
 * <dl>
 * <dt>Shutdown succeeded.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: #KJAVA_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by kjava_sock_close().</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: #KJAVA_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #KJAVA_SOCKET_ERROR_TIMEOUT
 *       - #KJAVA_SOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 *
 * If a value other than #KJAVA_SOCKET_SUCCESS is returned, do not make event
 * notification by the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open().
 *
 *
 * @see KJavaNetworkCallbackProc
 */
int kjava_sock_shutdown(int connectionID, int method);

/**
 *        Closes the connection.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @return
 *        Return #KJAVA_SOCKET_SUCCESS if the operation succeeds, otherwise return an error code.
 *
 * In the native system, disconnect the socket from the remote end, then
 * destroy the socket and free its resources.
 *
 * In order to not block AJSC processing, after requesting
 * disconnection and destruction processing by a separate task,
 * immediately return control to AJSC, passing #KJAVA_SOCKET_SUCCESS
 * as the return value.
 * If an error occurs before socket disconnect and destroy processing by the
 * separate task could be requested, return one of the error codes below depending
 * on the error cause.
 *   - #KJAVA_SOCKET_ERROR_TIMEOUT
 *   - #KJAVA_SOCKET_ERROR_OTHER
 *   .
 *
 * If #KJAVA_SOCKET_SUCCESS is passed as the return value, call
 * the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open()
 * at the time of any of the following occasions to notify AJSC of the result.
 * <dl>
 * <dt>Socket disconnect and destroy processing succeeded.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: #KJAVA_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed.</dt>
 * <dd>Pass parameter values to the <i>{@link #KJavaNetworkCallbackProc callback}</i> function as follows.
 *   <ul>
 *     <li><i>type</i>: #KJAVA_SOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #KJAVA_SOCKET_ERROR_TIMEOUT
 *       - #KJAVA_SOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 *
 * If a value other than #KJAVA_SOCKET_SUCCESS is returned, do not make event
 * notification by the #KJavaNetworkCallbackProc type callback function passed to kjava_sock_open().
 *
 * If communication (e.g., data sending/receipt) is in progress when this
 * function is called, cut off the communication with the remote end.
 *
 * If at the time this function is called, the processing result for the
 * functions indicated below has not yet been notified, make event
 * notification also for the result of processing requested by these
 * functions.
 * <ul>
 * <li>kjava_sock_connect()
 * <li>kjava_sock_send()
 * <li>kjava_sock_receive()
 * <li>kjava_sock_shutdown()
 * </ul>
 *
 *
 * When the native system has finished with the callback function passed to
 * kjava_sock_open() to notify AJSC of this kjava_sock_close() function result, the native
 * system should not call the callback address for the closed socket.
 *
 * @see KJavaNetworkCallbackProc
 */
int kjava_sock_close(int connectionID);

/**
 *        Sets a socket option of the connection.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @param option
 *        The type of option to set its value. One of the following is designated.
 *        - #KJAVA_SOCKET_OPTION_DELAY
 *        - #KJAVA_SOCKET_OPTION_KEEPALIVE
 *        - #KJAVA_SOCKET_OPTION_LINGER
 *        - #KJAVA_SOCKET_OPTION_RCVBUF
 *        - #KJAVA_SOCKET_OPTION_SNDBUF
 *        .
 * @param value
 *        The value of the option designated by the <i>option</i> parameter.
 * @return
 *        Return #KJAVA_SOCKET_SUCCESS if the operation succeeds, otherwise return an error code.
 *
 * In the native system, set the designated socket option for the socket
 * designated in the <i>connectionID</i> parameter. Set the <i>value</i> parameter
 * for the option indicated by the <i>option</i> parameter as follows.
 * <dl>
 *   <dt>#KJAVA_SOCKET_OPTION_DELAY
 *   <dd>Sets the Nagle algorithm to enabled (1) or disabled (0).</dd>
 *   <dt>#KJAVA_SOCKET_OPTION_KEEPALIVE
 *   <dd>Sets the KEEPALIVE function to enabled (1) or disabled (0).</dd>
 *   <dt>#KJAVA_SOCKET_OPTION_LINGER
 *   <dd>Sets linger time (in seconds).<br>
 *       If <i>value</i>=0, disable linger operation.</dd>
 *   <dt>#KJAVA_SOCKET_OPTION_RCVBUF
 *   <dd>Sets the data receive buffer size (in bytes).</dd>
 *   <dt>#KJAVA_SOCKET_OPTION_SNDBUF
 *   <dd>Sets the data send buffer size (in bytes).</dd>
 * </dl>
 *
 */
int kjava_sock_setoption(int connectionID, int option, int value);

/**
 *        Gets the socket option of a connection.
 * @param connectionID
 *        The ID of the socket connection.
 *        The value returned by kjava_sock_open() is designated.
 * @param option
 *        The type of option to obtain its value. One of the following is designated.
 *        - #KJAVA_SOCKET_OPTION_DELAY
 *        - #KJAVA_SOCKET_OPTION_KEEPALIVE
 *        - #KJAVA_SOCKET_OPTION_LINGER
 *        - #KJAVA_SOCKET_OPTION_RCVBUF
 *        - #KJAVA_SOCKET_OPTION_SNDBUF
 *        .
 * @return
 *        If the operation succeeds, return the current setting for
 *        the option designated by the <i>option</i> parameter.
 *        Return values for each of the options indicated in the <i>option</i>
 *        parameter as follows. <br><br>
 *         <dl>
 *         <dt> #KJAVA_SOCKET_OPTION_DELAY
 *           <dd>Return whether the Nagle algorithm is enabled (1) or
 *               disabled (0).
 *           </dd>
 *         <dt> #KJAVA_SOCKET_OPTION_KEEPALIVE
 *           <dd>Return whether the KEEPALIVE function is enabled (1)
 *               or disabled (0).
 *           </dd>
 *         <dt> #KJAVA_SOCKET_OPTION_LINGER
 *           <dd>Return the linger time (in seconds).
 *               If the linger operation is disabled, return 0.
 *           </dd>
 *         <dt> #KJAVA_SOCKET_OPTION_RCVBUF
 *           <dd>Return the data receive buffer size (in bytes).
 *           </dd>
 *         <dt> #KJAVA_SOCKET_OPTION_SNDBUF
 *           <dd>Return the data send buffer size (in bytes).
 *           </dd>
 *         </dl><br>
 *         In case of error, return #KJAVA_SOCKET_ERROR_OTHER.
 */
int kjava_sock_getoption(int connectionID, int option);


/**
 *        Semaphore for Opensocket and Opensocket CB
*/
void java_sockSemWait_Init(void);
void java_sockSemWait_Fini(void);
void java_sockSemWait_Consume(void);
void java_sockSemWait_Produce(void);
/**
 *        Reset TCP Table value
*/
void java_sockResetTCPTable(int nConnectionID);

/**
 *        Close valid socket when disconnected
*/
int java_sockCloseSocket(void);

/**
 *        Suspend all socket
*/

int java_sockSuspendAll(void);

/**
 *        Resume all socket
*/

int java_sockResumeAll(void);



/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* KJAVA_SYS_SOCK_HEADER */
