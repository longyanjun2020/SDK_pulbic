/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */


/**
 * @file JkSecureSocketCert.h
 * Server Certificate Acquisition JSI
 */

/**
 * @addtogroup Secure_Connection_Cert_JSI
 * @{
 */
#ifndef ___JKSECURESOCKETCERT_H
#define ___JKSECURESOCKETCERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypesSecureSocket.h"

/**
 *        Gets the server certificate type.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL is designated, put the server
 *        certificate type string in the memory area indicated by the <i>data</i>
 *        parameter.
 *        Do not append '\0' to the string.
 * @param length
 *        The maximum characters that fit in the certificate type area.
 * @return
 *        If the certificate type is obtained successfully,
 *        return a value as follows.
 *        - If the <i>data</i> parameter is #JK_NULL:<br>
 *          Return the number of characters in the certificate type character string
 *          (not including termination code).
 *        - If the <i>data</i> parameter is not #JK_NULL:<br>
 *          Return #JK_SECURESOCKET_SUCCESS if the server certificate type is
 *          successfully stored.
 *          Return #JK_SECURESOCKET_ERROR_OTHER if the server certificate type
 *          cannot be stored.
 *        .
 *        If the certificate type cannot be obtained, return
 *        #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the server certificate type for the
 * designated secure socket.
 *
 * If, for example, the server certificate type used is an X.509 certificate,
 * set the string "X.509" in the area passed in the parameter.
 *
 * A NUL character must not be set as the certificate type.
 *
 * When the MIDlet calls the <code>Certificate\#getType</code> method,
 * JBlend returns the character string acquired by this function without modification.
 *
 * @see JkSecureSocketOpen()
 */
JKSint32 JkSecureSocketCertGetType(JKSecureSocketHandle socket, JKWChar *data, JKSint32 length);

/**
 *        Gets the server certificate version.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @return
 *        Return the server certificate version.
 *        If certificate version acquisition failed, return
 *        #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the server certificate version for the
 * designated secure socket.
 * If, for example, it is an X.509 v3 certificate specified in RFC 3280,
 * return 3.
 *
 * When the MIDlet calls the <code>Certificate\#getVersion</code> method, 
 * JBlend returns a character string that is converted from the value 
 * acquired by this function. 
 *
 * @see JkSecureSocketOpen()
 */
JKSint32 JkSecureSocketCertGetVersion(JKSecureSocketHandle socket);

/**
 *        Gets the server certificate subject.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL is designated, put the subject string
 *        in the memory area indicated by the <i>data</i> parameter.
 *        Do not append '\0' to the string.
 * @param length
 *        The maximum number of characters that fit in the subject area
 * @return
 *        If the subject is obtained successfully, return a value as follows.
 *        - If the <i>data</i> parameter is #JK_NULL:<br>
 *          Return the number of characters in the subject character string
 *          (not including termination code).
 *        - If the <i>data</i> parameter is not #JK_NULL:<br>
 *          Return #JK_SECURESOCKET_SUCCESS if the subject is successfully stored.
 *          Return #JK_SECURESOCKET_ERROR_OTHER if the subject cannot be stored.
 *        .
 *        If the subject cannot be obtained, return #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the server certificate subject for the designated
 * secure socket.
 *
 * When the MIDlet calls the <code>Certificate\#getSubject</code> method,
 * JBlend returns the character string acquired by this function without modification.
 *
 * The subject field is as specified in RFC 3280 Section 4.1.2.6, "Subject."
 * In storing data, following the rules below to form a string consisting of
 * DN (Distinguished Name) attribute identifiers and their values arranged in
 *  a single line.
 *
 *  - The attributes must be in the same sequence as on the certificate, and must not be rearranged.
 *  - Attributes are separated by ";" with no spaces on either side of the ";".
 *  - Each attribute is indicated along with its value using "=" in the format "identifier=value".
 *    If the value is empty, use the format "identifier=".
 *  - If the value is not a character string, format it so that binary data can be displayed
 *    as a character string, as explained below under "Indicating binary data".
 *  - If the identifier is listed in the table below (DN identifiers and labels),
 *    use the string under "Label" as the identifier. If the identifier is not listed here,
 *    format the identifier binary data as explained under "Indicating binary data".
 * .
 *
 * <b>Indicating binary data</b><br>
 *     Express each byte of binary data as a two-digit hexadecimal number, separating each by ":".<br>
 *     0x25 0x43 0x7B  -> "25:43:7B"
 *
 * <table>
 * <caption>DN Identifiers and Labels</caption>
 * <tr>
 *   <td><b>Identifier</b></td><td><b>Binary data</b></td><td><b>Label</b></td>
 * </tr>
 * <tr>
 *   <td>id-at-commonName</td><td>55:04:03</td><td>CN</td>
 * </tr>
 * <tr>
 *   <td>id-at-surname</td><td>55:04:04</td><td>SN</td>
 * </tr>
 * <tr>
 *   <td>id-at-countryName</td><td>55:04:06</td><td>C</td>
 * </tr>
 * <tr>
 *   <td>id-at-localityName</td><td>55:04:07</td><td>L</td>
 * </tr>
 * <tr>
 *   <td>id-at-stateOrProvinceName</td><td>55:04:08</td><td>ST</td>
 * </tr>
 * <tr>
 *   <td>id-at-streetAddress</td><td>55:04:09</td><td>STREET</td>
 * </tr>
 * <tr>
 *   <td>id-at-organizationName</td><td>55:04:0A</td><td>O</td>
 * </tr>
 * <tr>
 *   <td>id-at-organizationUnitName</td><td>55:04:0B</td><td>OU</td>
 * </tr>
 * <tr>
 *   <td>emailAddress</td><td>2A:86:48:86:F7:0D:01:09:01</td><td>EmailAddress</td>
 * </tr>
 * </table>
 *
 *
 * @see JkSecureSocketOpen()
 */
JKSint32 JkSecureSocketCertGetSubject(JKSecureSocketHandle socket, JKWChar *data, JKSint32 length);

/**
 *        Gets the server certificate issuer.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL is designated, put the server
 *        certificate issuer string in the memory area indicated by the
 *        <i>data</i> parameter.
 *        Do not append '\0' to the string.
 * @param length
 *        The maximum characters that fit in the server certificate issuer area.
 * @return
 *        If the server certificate issuer is obtained successfully,
 *        return a value as follows.
 *        - If the <i>data</i> parameter is #JK_NULL:<br>
 *          Return the number of characters in the certificate issuer character
 *          string (not including termination code).
 *        - If the <i>data</i> parameter is not #JK_NULL:<br>
 *          Return #JK_SECURESOCKET_SUCCESS if the server certificate issuer is
 *          successfully stored.
 *          Return #JK_SECURESOCKET_ERROR_OTHER if the server certificate
 *          issuer cannot be stored.
 *        .
 *        If the server certificate issuer cannot be obtained, return
 *        #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the server certificate issuer for the
 * designated secure socket.
 *
 * When the MIDlet calls the <code>Certificate\#getIssuer</code> method,
 * JBlend returns the character string acquired by this function without modification.
 *
 * The issuer field is as specified in RFC 3280 Section 4.1.2.4, "Issuer."
 * On the format in which data is to be stored, see the section on
 * #JkSecureSocketCertGetSubject().
 *
 * @see JkSecureSocketOpen(), JkSecureSocketCertGetSubject()
 */
JKSint32 JkSecureSocketCertGetIssuer(JKSecureSocketHandle socket, JKWChar *data, JKSint32 length);

/**
 *        Gets the server certificate signature algorithms.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL is designated, put the
 *        signature algorithms string in the memory area indicated by the
 *        <i>data</i> parameter.
 *        Do not append '\0' to the string.
 * @param length
 *        The maximum characters that fit in the signature algorithms area.
 * @return
 *        If the signature algorithms information is obtained successfully,
 *        return a value as follows.
 *        - If the <i>data</i> parameter is #JK_NULL:<br>
 *          Return the number of characters in the signature algorithms
 *          character string (not including termination code).
 *        - If the <i>data</i> parameter is not #JK_NULL:<br>
 *          Return #JK_SECURESOCKET_SUCCESS if the signature algorithms
 *          information is successfully stored.
 *          Return #JK_SECURESOCKET_ERROR_OTHER if the signature algorithms
 *          information cannot be stored.
 *        .
 *        If the signature algorithms information cannot be obtained,
 *        return #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the server certificate signature algorithms
 * for the designated secure socket.
 *
 * The algorithm name format is a combination of the message digest algorithm
 *  and public key algorithm, based on the items specified in RFC 3279.<br>
 * If, for example, the SHA-1 message digest and RSA algorithm are used, the
 * signature algorithm name becomes "SHA1withRSA".
 *
 * When the MIDlet calls the <code>Certificate\#getSigAlgName</code> method,
 * JBlend returns the character string acquired by this function without modification.
 *
 * @see JkSecureSocketOpen()
 */
JKSint32 JkSecureSocketCertGetSigAlgName(JKSecureSocketHandle socket, JKWChar *data, JKSint32 length);

/**
 *        Gets the start time of the server certificate valid term
 *        (notBefore) and the format for time data.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL is designated, put the start
 *        of the server certificate valid term in the memory area
 *        indicated by the <i>data</i> parameter.
 *        Do not append '\0' to the string.
 * @param length
 *        The maximum bytes of the area holding the valid term start time
 * @param type
 *        As the format for time data, put either of the values below in the
 *        memory area designated by the <i>type</i> parameter. <br>
 *        UTC Time type:<br>
 *        #JK_SERVER_CERT_TIME_UTC<br>
 *        Generalized Time type:<br>
 *        #JK_SERVER_CERT_TIME_GENERALIZED
 * @return
 *        If the start time is obtained successfully, return a value as follows.
 *        - If the <i>data</i> parameter is #JK_NULL:<br>
 *          Return 0 if the valid term start time is not specified.
 *          If it is specified, return the size (in characters)
 *          of the start time.
 *        - If the <i>data</i> parameter is not #JK_NULL:<br>
 *          Return #JK_SECURESOCKET_SUCCESS if the start time is successfully
 *          stored.
 *          Return #JK_SECURESOCKET_ERROR_OTHER if the time cannot be stored.
 *        .
 *        If the start time cannot be obtained, return
 *        #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the start time of the server certificate
 * valid term (notBefore) and the format of the time data for the designated
 * secure socket. When the <i>data</i> parameter is not #JK_NULL, set these
 * data respectively in the memory areas indicated by the <i>data</i> and
 * <i>type</i> parameters.
 *
 * The format of time data used on a certificate is as follows. (See the items
 * in RFC 3280 Section 4.1.2.5, "Validity," and following.)
 *
 * <pre>
 * YYMMDDhhmm(ss)(Z|[+-]hhmm) : UTCTime
 * YYYYMMDDhhmm(ss)(Z|[+-]hhmm) : GeneralizedTime
 * </pre>
 *
 * @see JkSecureSocketOpen()
 */
JKSint32 JkSecureSocketCertGetNotBefore(JKSecureSocketHandle socket, JKUint8 *data, JKSint32 length, JKSint32 *type);

/**
 *        Gets the end time of the server certificate valid term
 *        (notAfter) and the format for time data.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL is designated, put the end of
 *        the server certificate valid term in the memory area indicated by the
 *        <i>data</i> parameter.
 *        Do not append '\0' to the string.
 * @param length
 *        The maximum bytes of the area holding the valid term end time
 * @param type
 *        As the format for time data, put either of the values below in the memory
 *        area designated by the <i>type</i> parameter. <br>
 *        UTC Time type:<br>
 *        #JK_SERVER_CERT_TIME_UTC<br>
 *        Generalized Time type:<br>
 *        #JK_SERVER_CERT_TIME_GENERALIZED
 * @return
 *        If the end time is obtained successfully, return a value as follows.
 *        - If the <i>data</i> parameter is #JK_NULL:<br>
 *          Return 0 if the valid term end time is not specified.
 *          If it is specified, return the size (in characters)
 *          of the end time.
 *        - If the <i>data</i> parameter is not #JK_NULL:<br>
 *          Return #JK_SECURESOCKET_SUCCESS if the end time is successfully
 *          stored.
 *          Return #JK_SECURESOCKET_ERROR_OTHER if the time cannot be stored.
 *        .
 *        If the end time cannot be obtained, return
 *        #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the end time of the server certificate
 * valid term (notAfter) and the format of the time for the designated secure socket.
 *
 * On the data to be stored, see the section on
 * #JkSecureSocketCertGetNotBefore().
 *
 * @see JkSecureSocketOpen(), JkSecureSocketCertGetNotBefore()
 */
JKSint32 JkSecureSocketCertGetNotAfter(JKSecureSocketHandle socket, JKUint8 *data, JKSint32 length, JKSint32 *type);

/**
 *        Gets the server certificate serial number.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL is designated, put the serial
 *        number in the memory area indicated by the <i>data</i> parameter.
 * @param length
 *        The maximum bytes of the area holding the serial number
 * @return
 *        If the serial number is obtained successfully, return a value as follows.
 *        - If the <i>data</i> parameter is #JK_NULL:<br>
 *          Return 0 if the serial number is not specified.
 *          If it is specified, return the size (in bytes) of the serial number .
 *        - If the <i>data</i> parameter is not #JK_NULL: <br>
 *          Return #JK_SECURESOCKET_SUCCESS if the serial number is successfully
 *          stored.
 *          Return #JK_SECURESOCKET_ERROR_OTHER if the serial number cannot be
 *          stored.
 *        .
 *        If the serial number cannot be obtained, return
 *        #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the server certificate serial number for
 * the designated secure socket.
 *
 * The certificate serial number is in binary format. Set the data still in
 * binary format in the area passed in the parameter.
 *
 * The serial number field is as specified in RFC 3280 Section 4.1.2.2, "Serial number."
 *
 * @see JkSecureSocketOpen()
 */
JKSint32 JkSecureSocketCertGetSerialNumber(JKSecureSocketHandle socket, JKUint8 *data, JKSint32 length);

#ifdef __cplusplus
}
#endif

#endif  /* ___JKSECURESOCKETCERT_H */

/**
 * @} end of group
 */
