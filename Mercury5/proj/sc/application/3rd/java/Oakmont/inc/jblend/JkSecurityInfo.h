/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkSecurityInfo.h
 * Security Information JSI
 */

/**
 * @addtogroup Security_Information_JSI
 * @{
 */

#ifndef ___IO_JK_SECURITYINFO_H
#define ___IO_JK_SECURITYINFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesHttp.h"


/**
 * SSL Protocol Version 3.0
 */
#define JK_SECURITY_INFO_PROTOCOL_SSL   0

/**
 * TLS Protocol Version 1.0, or WAP TLS Profile and Tunneling
 */
#define JK_SECURITY_INFO_PROTOCOL_TLS   1

/**
 * Wireless Transport Layer Security
 */
#define JK_SECURITY_INFO_PROTOCOL_WTLS  2

/**
 * Gets the security information protocol name.
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @return
 *      Protocol name:<br>
 * SSL protocol Version 3.0 :<br>
 *      #JK_SECURITY_INFO_PROTOCOL_SSL<br>
 * TLS protocol Version 1.0 (RFC 2818) or
 * WAP TLS Profile and Tunneling Specification :<br>
 *      #JK_SECURITY_INFO_PROTOCOL_TLS<br>
 * Wireless Transport Layer Security (WAP-199)<br>
 *      #JK_SECURITY_INFO_PROTOCOL_WTLS<br>
 *      If the protocol name cannot be obtained, return -1.
 *
 * This function is called to get the name of the protocol used for the secure connection on the designated HTTP/HTTPS connection.
 *
 * @see JkHttpOpen()
 */
JKSint32 JkSecurityInfoGetProtocol(JKHttpHandle connection);

/**
 * Gets the CipherSuite used for communication.
 * @param connection
 *      The applicable HTTP/HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL (length=0) is designated, put the name of 
 *      the CipherSuite in the memory area indicated by the data parameter.
 * @param length
 *      The maximum number of characters that fit in the CipherSuite memory 
 *      area.
 * @return
 *      <ul>
 *      <li>If the data parameter is JK_NULL (length=0), return the number of 
 *          elements in the CipherSuite character string (not including 
 *          termination code).
 *      <li>If data is not JK_NULL (length=0), and the CipherSuite was 
 *          successfully obtained and stored, return 0; if the CipherSuite 
 *          could not be obtained, return -1.
 *      </ul>
 *
 *  <p>This function is called to get the security information CipherSuite used on
 * the designated HTTP/HTTPS connection. </p>
 *
 * As the CipherSuite, store a string defined in the CipherSuite definition 
 * table in Appendix C. CipherSuite definitions, in RFC 2246 The TLS Protocol 
 * Version 1.0.<br>
 * If a protocol other than TLS 1.0 is used, choose a CipherSuite from the 
 * CipherSuite definition table that corresponds to the combination of key 
 * exchange, cipher and hash used. <br>
 * If the combination of key exchange, cipher and hash is not found in the 
 * CipherSuite definition table, store a string consisting of upper-case 
 * letters and numerals in the format, "(key exchange)_(cipher)_(hash)."
<br>
 * 
 *
 * @see JkHttpOpen()
 */
JKSint32 JkSecurityInfoGetCipherSuite(JKHttpHandle connection, JKWChar* data, JKSint32 length);

#ifdef __cplusplus
}
#endif

#endif /* ___IO_JK_SECURITYINFO_H */

/**
 * @} end of group
 */
