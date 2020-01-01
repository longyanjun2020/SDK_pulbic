/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesSecureSocket.h
 *  SecureConnection data types and constants
 */

#ifndef __SECURESOCKET_JK_TYPES_SECURE_SOCKET_H
#define __SECURESOCKET_JK_TYPES_SECURE_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"


/**
 * @addtogroup Secure_Connection_Data_Types
 * @{
 */

/**
 *   Socket handle type
 */
typedef JKHandle JKSecureSocketHandle;

/**
 *  Values returned by the individual functions
 */
/**
 * Succeeded.
 *
 *  Passed in the <i>result</i> parameter of #AmNotifySecureSocketEvent(), or
 *  as the return value of the following JSI functions. 
 * <ul>
 *  <li> #JkSecureSocketConnect()
 *  <li> #JkSecureSocketSend()
 *  <li> #JkSecureSocketReceive()
 *  <li> #JkSecureSocketShutdown()
 *  <li> #JkSecureSocketClose()
 *  <li> #JkSecureSocketSetOption()
 *  <li> #JkSecureSocketGetCipherSuite()
 *  <li> @ref Secure_Connection_Cert_JSI functions 
 *   other than #JkSecureSocketCertGetVersion()
 * </ul>
*/
#define JK_SECURESOCKET_SUCCESS       0


/**
 * The certificate contains an unrecognized critical extension.
 */
#define JK_SECURESOCKET_ERROR_CERT_BAD_EXTENSIONS       101

/**
 * The server certificate chain exceeds the maximum depth specified by the issuer.
 */
#define JK_SECURESOCKET_ERROR_CERT_CHAIN_TOO_LONG       102

/**
 * The server certificate has expired (it is no longer valid).
 */
#define JK_SECURESOCKET_ERROR_CERT_EXPIRED              103

/**
 * An intermediate certificate in the chain has not been authorized by the 
 * Certificate Authority.
 */
#define JK_SECURESOCKET_ERROR_CERT_UNAUTHORIZED_INTERMEDIATE_CA     104
    
/**
 * The certificate is unsigned.
 */
#define JK_SECURESOCKET_ERROR_CERT_MISSING_SIGNATURE    105

/**
 * The certificate is not yet valid.
 */
#define JK_SECURESOCKET_ERROR_CERT_NOT_YET_VALID        106

/**
 * The site name on the certificate is not correct.
 */
#define JK_SECURESOCKET_ERROR_CERT_SITENAME_MISMATCH    107

/**
 * The issuer of the certificate is unknown.
 */
#define JK_SECURESOCKET_ERROR_CERT_UNRECOGNIZED_ISSUER  108

/**
 * The certificate signature algorithm is not supported.
 */
#define JK_SECURESOCKET_ERROR_CERT_UNSUPPORTED_SIGALG   109

/**
 * The public key is used inappropriately by the certificate issuer.
 */
#define JK_SECURESOCKET_ERROR_CERT_INAPPROPRIATE_KEY_USAGE  110

/**
 * A certificate in the chain was not issued by the same Certificate Authority as the 
 * next certificate in the chain.
 */
#define JK_SECURESOCKET_ERROR_CERT_BROKEN_CHAIN         111

/**
 * The public key of the root certificate has expired.
 */
#define JK_SECURESOCKET_ERROR_CERT_ROOT_CA_EXPIRED      112

/**
 * The certificate public key type is not supported by the device.
 */
#define JK_SECURESOCKET_ERROR_CERT_UNSUPPORTED_PUBLIC_KEY_TYPE  113

/**
 * Certificate verification failed.
 */
#define JK_SECURESOCKET_ERROR_CERT_VERIFICATION_FAILED  114

/**
 * Canceled due to timeout.
 *
 *  Passed in the <i>result</i> parameter of #AmNotifySecureSocketEvent(), or as
 *  the return value of @ref Secure_Connection_JSI functions other than
 *  those indicated below.
 * <ul>
 *   <li> #JkSecureSocketGetMaxSessions()
 *   <li> #JkSecureSocketOpen()
 *   <li> #JkSecureSocketGetProtocol()
 *   <li> #JkSecureSocketGetCipherSuite()
 * </ul>
 */
#define JK_SECURESOCKET_ERROR_TIMEOUT         -20000

/**
 * An internal error occurred
 *
 *  Passed in the <i>result</i> parameter of #AmNotifySecureSocketEvent(), or as the
 *  return value of @ref Secure_Connection_JSI and @ref Secure_Connection_Cert_JSI 
 *  functions other than those indicated below.
 * <ul>
 *   <li> #JkSecureSocketGetMaxSessions()
 *   <li> #JkSecureSocketOpen()
 * </ul>
 */
#define JK_SECURESOCKET_ERROR_OTHER           -30000

/**
 * Shut down receive direction only.\ This is designated in the <i>how</i>
 * parameter of #JkSecureSocketShutdown().
*/
#define JK_SECURESOCKET_SHUTDOWN_RECEIVE      1

/**
 * Shut down send direction only.\ This is designated in the <i>how</i>
 * parameter of #JkSecureSocketShutdown().
*/
#define JK_SECURESOCKET_SHUTDOWN_SEND         2

/**
 * Shut down both send and receive directions.\ This is designated in the <i>how</i>
 * parameter of #JkSecureSocketShutdown().
*/
#define JK_SECURESOCKET_SHUTDOWN_BOTH         3

/**
 * Designate Nagle algorithm use as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSecureSocketGetOption() 
 * and #JkSecureSocketSetOption().
*/
#define JK_SECURESOCKET_OPTION_DELAY          1

/**
 * Designate whether to send a KEEPALIVE signal as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSecureSocketGetOption() 
 * and #JkSecureSocketSetOption().
*/
#define JK_SECURESOCKET_OPTION_KEEPALIVE      2

/**
 * Designate linger time (wait time before disconnecting socket) as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSecureSocketGetOption() 
 * and #JkSecureSocketSetOption().
*/
#define JK_SECURESOCKET_OPTION_LINGER         3

/**
 * Designate the receive buffer size as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSecureSocketGetOption() 
 * and #JkSecureSocketSetOption().
*/
#define JK_SECURESOCKET_OPTION_RCVBUF         4

/**
 * Designate the send buffer size as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSecureSocketGetOption() 
 * and #JkSecureSocketSetOption().
*/
#define JK_SECURESOCKET_OPTION_SNDBUF         5

/**
 *  A connection result notification event.\ This is used for notifying of the 
 *  result of #JkSecureSocketConnect() processing.
*/
#define JK_SECURESOCKET_EVENT_TYPE_CONNECT        0

/**
 *  A send result notification event.\ This is used for notifying of the 
 *  result of #JkSecureSocketSend() processing.
*/
#define JK_SECURESOCKET_EVENT_TYPE_SEND           1

/**
 *  A receive result notification event.\ This is used for notifying of the 
 *  result of #JkSecureSocketReceive() processing.
*/
#define JK_SECURESOCKET_EVENT_TYPE_RECEIVE        2

/**
 *  A shut down result notification event.\ This is used for notifying of the 
 *  result of #JkSecureSocketShutdown() processing.
*/
#define JK_SECURESOCKET_EVENT_TYPE_SHUTDOWN       3

/**
 *  A secure socket disconnect/destroy result notification event.\ This is used 
 *  for notifying of the result of #JkSecureSocketClose() processing. 
*/
#define JK_SECURESOCKET_EVENT_TYPE_CLOSE          4


/**
 * SSL Protocol Version 3.0
 */
#define JK_SECURITY_INFO_PROTOCOL_SSL   0

/**
 * TLS Protocol Version 1.0, or WAP TLS Profile and Tunneling
 */
#define JK_SECURITY_INFO_PROTOCOL_TLS   1


/**
 * UTC Time type
 */
#define JK_SERVER_CERT_TIME_UTC             ((JKSint32)0)

/**
 * Generalized Time type
 */
#define JK_SERVER_CERT_TIME_GENERALIZED     ((JKSint32)1)

#ifdef __cplusplus
}
#endif

#endif
/**
 * @}
 */
