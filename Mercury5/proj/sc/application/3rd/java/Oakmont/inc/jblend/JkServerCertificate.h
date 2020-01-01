/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkServerCertificate.h
 * Server Certificate JSI
 */

/**
 * @addtogroup Server_Certificate_JSI
 * @{
 */

#ifndef ___NET_JK_SERVERCERTIFICATE_H
#define ___NET_JK_SERVERCERTIFICATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesHttp.h"


/**
 * UTC Time type
 */
#define JK_SERVER_CERT_TIME_UTC             ((JKSint32)0)

/**
 * Generalized Time type
 */
#define JK_SERVER_CERT_TIME_GENERALIZED     ((JKSint32)1)



/**
 * Gets the server certificate type.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL is designated, put the server 
 *      certificate type string in the memory area indicated by the <i>data</i> 
 *      parameter.
 *      Do not append a termination code to the string.
 * @param length
 *      The maximum characters that fit in the certificate type area
 * @return
 *      If the certificate type is obtained successfully, 
 *      return a value as follows.
 *      <ul>
 *      <li>If the <i>data</i> parameter is JK_NULL:<br>
 *          Return the number of elements in the certificate type character 
 *          string (not including termination code).
 *      <li>If the <i>data</i> parameter is not JK_NULL:<br>
 *          Return 0 if the server certificate type is successfully stored.
 *          Return -1 if the server certificate type cannot be stored.
 *      </ul>
 *      If the certificate type cannot be obtained, return -1.
 * <p>This function is called to get the server certificate type for the 
 * designated HTTPS connection.
 * </p><p>
 * If, for example, the server certificate type used is an X.509 certificate, set 
 * the string "X.509" in the area passed in the parameter.<br>
 * </p><p>
 * A null character must not be set as the certificate type.
 * </p>
 *
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetType(JKHttpHandle connection, JKWChar* data, JKSint32 length);

/**
 * Gets the server certificate version.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @return
 *      Return the server certificate version. 
 *      If certificate version acquisition failed, return -1.
 *
 * <p>This function is called to get the server certificate version for the 
 * designated HTTPS connection. 
 * If, for example, it is an X.509 v3 certificate specified in RFC 3280, return 3.
 * </p>
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetVersion(JKHttpHandle connection);

/**
 * Gets the server certificate subject.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL is designated, put the subject string 
 *      in the memory area indicated by the <i>data</i> parameter.
 *      Do not append a termination code to the string.
 * @param length
 *      The maximum number of characters that fit in the subject area
 * @return
 *      If the subject is obtained successfully, return a value as follows.
 *      <ul>
 *      <li>If the <i>data</i> parameter is JK_NULL:<br>
 *          Return the number of elements in the subject character string
 *          (not including termination code).
 *      <li>If the <i>data</i> parameter is not JK_NULL:<br>
 *          Return 0 if the subject is successfully stored.
 *          Return -1 if the subject cannot be stored.
 *      </ul>
 *      If the subject cannot be obtained, return -1.
 * 
 
 * <p>This function is called to get the server certificate for the designated 
 * HTTPS connection.<br>
 * The subject field is as specified in RFC 3280 Section 4.1.2.6, "Subject."</p>
 * <p>In storing data, following the rules below to form a string consisting of DN attribute identifiers and their values arranged in a single line.</p>
 *
 * <ul>
 *  <li>The attributes must be in the same sequence as on the certificate, and must not be rearranged.
 *  <li>Attributes are separated by ";" with no spaces on either side of the ";".
 *  <li>Each attribute is indicated along with its value using "=" in the format "identifier=value". If the value is empty, use the format "identifier=".
 *  <li>If the value is not a character string, format it so that binary data can be displayed as a character string, as explained below under "Indicating binary data".
 *  <li>If the identifier is listed in the table below (DN identifiers and labels), use the string under "Label" as the identifier. If the identifier is not listed here, format the identifier binary data as explained under "Indicating binary data".
 * </ul>
 * 
 * <p>
 * <b>Indicating binary data</b><br>
 *     Express each byte of binary data as a two-digit hexadecimal number, separating each by ":".<br>
 *     0x25 0x43 0x7B  -> "25:43:7B"
 * </p>
 * <p></p>
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
 * <p>
 *
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetSubject(JKHttpHandle connection, JKWChar* data, JKSint32 length);

/**
 * Gets the server certificate issuer.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL is designated, put the server 
 *      certificate issuer string in the memory area indicated by the <i>data</i> 
 *      parameter.
 *      Do not append a termination code to the string.
 * @param length
 *      The maximum characters that fit in the server certificate issuer area
 * @return
 *      If the server certificate issuer is obtained successfully, 
 *      return a value as follows.
 *      <ul>
 *      <li>If the <i>data</i> parameter is JK_NULL:<br>
 *          Return the number of elements in the certificate issuer character
 *          string (not including termination code).
 *      <li>If the <i>data</i> parameter is not JK_NULL:<br>
 *          Return 0 if the server certificate issuer is successfully 
 *          stored.
 *          Return -1 if the server certificate issuer cannot be stored.
 *      </ul>
 *      If the server certificate issuer cannot be obtained, return -1.
 *
 * <p>This function is called to get the server certificate issuer for the 
 * designated HTTPS connection. <p>
 * The issuer field is as specified in RFC 3280 Section 4.1.2.4, "Issuer."
 * On the format in which data is to be stored, see the section on 
 * #JkServerCertGetSubject().
 *
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetIssuer(JKHttpHandle connection, JKWChar* data, JKSint32 length);

/**
 * Gets the server certificate signature algorithms.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL is designated, put the 
 *      signature algorithms string in the memory area indicated by the <i>data</i> parameter.
 *      Do not append a termination code to the string.
 * @param length
 *      The maximum characters that fit in the signature algorithms area
 * @return
 *      <ul>
 *      If the signature algorithms information is obtained successfully, 
 *      return a value as follows.
 *      <li>If the <i>data</i> parameter is JK_NULL:<br>
 *          Return the number of elements in the signature algoritms 
 *          character string (not including termination code).
 *      <li>If the <i>data</i> parameter is not JK_NULL:<br>
 *          Return 0 if the signature algorithms information is successfully 
 *          stored.
 *          Return -1 if the signature algorithms information cannot be 
 *          stored.
 *      </ul>
 *      If the signature algorithms information cannot be obtained, 
 *      return -1.
 * <p>This function is called to get the server certificate signature algorithms
 * for the designated HTTPS connection.<br>
 * The algorithm name format is a combination of the message digest algorithm and 
 * public key algorithm, based on the items specified in RFC 3279. <br>
 * If, for example, the SHA-1 message digest and RSA algorithm are used, the 
 * signature algorithm name becomes "SHA1withRSA".</p>
 *
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetSigAlgName(JKHttpHandle connection, JKWChar* data, JKSint32 length);

/**
 * Gets the start of the server certificate valid term (notBefore) and the format for time data.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL is designated, put the start 
 *      of the server certificate valid term in the memory area 
 *      indicated by the <i>data</i> parameter.
 *      Do not append a termination code to the string.
 * @param length
 *      The maximum bytes of the area holding the valid term start time
 * @param type
 *      As the format for time data, put either of the values below in the memory 
 *      area designated by the <i>type</i> parameter. <br>
 *      UTC Time type:<br>
 *      #JK_SERVER_CERT_TIME_UTC<br>
 *      Generalized Time type:<br>
 *      #JK_SERVER_CERT_TIME_GENERALIZED
 * @return
 *      If the start time is obtained successfully, return a value as follows.
 *      <ul>
 *      <li>If the <i>data</i> parameter is JK_NULL:<br>
 *          Return 0 if the valid term start time is not designated. 
 *          If the time is designated, return the size (in bytes)
 *          of the valid term start time.
 *      <li>If the <i>data</i> parameter is not JK_NULL:<br>
 *          Return 0 if the start time is successfully stored.
 *          Return -1 if the time cannot be stored.
 *      </ul>
 *      If the start time cannot be obtained, return -1.
 * <p>This function is called to get the start time of the server certificate 
 * valid term (notBefore) for the designated HTTPS connection.<br>
 * The format of time data used on a certificate is as follows. (See the items in  
 * RFC 3280 Section 4.1.2.5, "Validity," and following.)<br>
 * Set this time data and its format in the area passed in the parameter.</p>
 * <pre>
 * YYMMDDhhmm(ss)(Z|[+-]hhmm) : UTCTime
 * YYYYMMDDhhmm(ss)(Z|[+-]hhmm) : GeneralizedTime
 * </pre>
 *
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetNotBefore(JKHttpHandle connection, JKUint8* data, JKSint32 length, JKSint32* type);

/**
 * Gets the end of the server certificate valid term (notAfter) and the format for time data.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL is designated, put the end of 
 *      the server certificate valid term in the memory area indicated by the
 *      <i>data</i> parameter.
 *      Do not append a termination code to the string.
 * @param length
 *      The maximum bytes of the area holding the valid term end time
 * @param type
 *      As the format for time data, put either of the values below in the memory 
 *      area designated by the <i>type</i> parameter. <br>
 *      UTC Time type:<br>
 *      #JK_SERVER_CERT_TIME_UTC<br>
 *      Generalized Time type:<br>
 *      #JK_SERVER_CERT_TIME_GENERALIZED
 * @return
 *      If the end time is obtained successfully, return a value as follows.
 *      <ul>
 *      <li>If the <i>data</i> parameter is JK_NULL:<br>
 *          Return 0 if the valid term end time is not designated. 
 *          If the time is designated, return the size (in bytes)
 *          of the valid term end time.
 *      <li>If the <i>data</i> parameter is not JK_NULL:<br>
 *          Return 0 if the end time is successfully stored.
 *          Return -1 if the time cannot be stored.
 *      </ul>
 *      If the end time cannot be obtained, return -1.
 * <p>This function is called to get the end time of the server certificate 
 * valid term (notAfter) for the designated HTTPS connection.<br>
 * On the data to be stored, see the section on JkServerCertGetNotBefore().</p>
 *
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetNotAfter(JKHttpHandle connection, JKUint8* data, JKSint32 length, JKSint32* type);

/**
 * Gets the server certificate serial number.
 * @param connection
 *      The applicable HTTPS connection. The value returned by 
 *      #JkHttpOpen() is designated.
 * @param data
 *      If a value other than JK_NULL is designated, put the serial 
 *      number in the memory area indicated by the <i>data</i> parameter.
 * @param length
 *      The maximum bytes of the area holding the serial number
 * @return
 *      If the serial number is obtained successfully, return a value as follows.
 *      <ul>
 *      <li>If the <i>data</i> parameter is JK_NULL:<br>
 *          Return 0 if the valid term serial number is not designated. 
 *          Return the serial number size (in bytes).
 *      <li>If the <i>data</i> parameter is not JK_NULL: <br>
 *          Return 0 if the serial number is successfully stored.
 *          Return -1 if the serial number cannot be stored.
 *      </ul>
 *      If the serial number cannot be obtained, return -1.
 * <p>This function is called to get the server certificate serial number for
 * the designated HTTPS connection.</p>
 * <p>The certificate serial number is in binary format. Set the data still in binary 
 * format in the area passed in the parameter.</p>
 * The serial number field is as specified in RFC 3280 Section 4.1.2.2, "Serial number."</p>
 *
 * @see JkHttpOpen()
 */
JKSint32 JkServerCertGetSerialNumber(JKHttpHandle connection, JKUint8* data, JKSint32 length);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
