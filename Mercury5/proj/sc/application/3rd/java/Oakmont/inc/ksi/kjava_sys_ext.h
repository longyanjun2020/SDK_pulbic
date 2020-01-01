/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */
/***************************************************************************
 * FILE: kjava_sys_ext.h
 *
 * DESCRIPTION:
 *      The module is one of KJava interface modules. It is for native file
 *      system handling.
 *
 * UPDATED DATE:
 *
 * REVISION:
 *
 ***************************************************************************/


#ifndef KJAVA_SYS_EXT_HEADER
#define KJAVA_SYS_EXT_HEADER

/**
 * @file kjava_sys_ext.h
 * OTA KSI
 */


#ifdef __cplusplus
extern "C"{
#endif

/** @addtogroup Application_Installation_and_Uninstallation
 *  @{
 */

/*
 *  Interfaces listed in the group are used for:
 *     - Verify one X509 chain certificate based on external or native root certificate
 *       authentication.
 *     - Verify the RSA-SHA1 based64 encoding digital signature using one
 *       external X509 certificate.
 *     .
 */

/** 
 * @addtogroup X509_Chain_Cert_KSI X509 Chain Certificate KSI
 * An interface for performing MIDlet suite authentication.
 * This interface must be implemented by the device manufacturer when supporting trusted MIDlet suite.
 * When not supporting trusted MIDlet suite, this interface need not exist in the native system.
 *
 * When supporting trusted MIDlet suites, if the AJSC built-in SSL is enabled and root certificates are ROMized using PIK, 
 * this interface is implemented in AJSC and therefore need not be implemented by the device manufacturer.
 *
 * By default, support of trusted MIDlet suite is enabled.
 * To disable the support, a library customization request needs to be submitted.
 *
 * @par Include file 
 * \#include kjava_sys_ext.h
 * @{
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/**
 * @name Protection Domain Identifier
 * @{
 */
/** 
 * Manufacturer protection domain.
 */ 
#define KJAVA_DOMAIN_MANUFACTURER  (1)
/** 
 * Operator protection domain.
 */ 
#define KJAVA_DOMAIN_OPERATOR      (2)
/** 
 * Third Party protection domain.
 */ 
#define KJAVA_DOMAIN_THIRD_PARTY   (3) 
/** 
 * Unspecified (Untrusted) protection domain.
 */ 
#define KJAVA_DOMAIN_UNSPECIFIED   (0)
/** @} */

/** 
 * The structure type for containing a certificate.
 */
typedef struct _KJavaCertChain
{
    /** 
     * A pointer to an X509 certificate in Base64 format. 
     */
    unsigned char *cert;
    /** 
     * The size in bytes of the string indicated by <i>cert</i>. 
     */
    int            certLen;
} KJavaCertChain;

/** 
 * The structure type for containing a root certificate.
 */
typedef struct _KJavaCaList
{
    /** 
     * The protection domain mapped for the root certificate. 
     *
     * This member indicates the certificate attribute field CKA_JAVA_MIDP_SECURITY_DOMAIN defined in PKCS#11. 
     *
     * One of the following values is set.
     * - #KJAVA_DOMAIN_MANUFACTURER
     * - #KJAVA_DOMAIN_OPERATOR
     * - #KJAVA_DOMAIN_THIRD_PARTY
     * - #KJAVA_DOMAIN_UNSPECIFIED
     * .
     */
    int             type;
    /** 
     * A pointer to an X509 certificate in DER format. 
     */
    unsigned char*  cert;
    /** 
     * The size in bytes of the string indicated by <i>cert</i>. 
     */
    int             certLen;
} KJavaCaList;
/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/** 
 *        Verifies an X509 chain certificate.
 * @param pCa         
 *        A pointer to a #KJavaCaList array containing the root certificates specified with the PIK tool.
 *        The certificates are in DER format.
 * @param iNumOfCa    
 *        The number of the elements of the array indicated by <i>pCa</i>.
 * @param pChain      
 *        A pointer to a #KJavaCertChain array containing the X509 certificate chain to be verified.
 *        The certificates are in Base64 format.
 * @param iNumOfCertInChain 
 *        The number of the elements of the array indicated by <i>pChain</i>.
 * @param iDomain     
 *        A pointer to the buffer for putting a value indicating the retrieved protection domain.
 *        One of the following values should be set when this function succeeds.
 *        - #KJAVA_DOMAIN_MANUFACTURER
 *        - #KJAVA_DOMAIN_OPERATOR
 *        - #KJAVA_DOMAIN_THIRD_PARTY
 *        - #KJAVA_DOMAIN_UNSPECIFIED
 *        .
 * @retval 0 if the function succeeds.
 * @retval 1 if the function fails.
 *
 * This function is called to verify an X509 chain certificate using an external or internal root certificate list. 
 * To support an external root certificate list, the device manufacturer needs to specify the root certificate list 
 * and their mapping protection domains with PIK (Preinstall Toolkit) at compilation time.
 * The specified root certificate list is passed to this function via <i>pCa</i> and <i>iNumOfCa</i>.
 *
 * If none root certificate is specified with PIK, #AJ_NULL will be passed in the <i>pCa</i> parameter. 
 * In such a case, the native system needs to use its own root certificate database 
 * to verify the chain and put the assigned protection domain in <i>*iDomain</i> when verification succeeds.
 *
 * Implementation of this function is necessary only when the support of trusted MIDlet suite is enabled. 
 * If, however, the AJSC built-in SSL is enabled and root certificates are ROMized using PIK, this function is 
 * implemented in AJSC and therefore need not be implemented by the device manufacturer.
 * If the device manufacturer chooses to use internal certificates, this function needs to be implemented 
 * by the device manufacturer.
 * For details of the AJSC built-in SSL, see @ref page_built_in_ssl.
 *
 * This function can be called in the KVE thread context during a trusted MIDlet suite verification and installation
 * in the following conditions.
 * - AMS calls ajms_ota_check() passing #AJMS_CHECK_TYPE_JAD in the <i>dataType</i> parameter.
 * - AMS calls ajms_ota_install().
 * - AMS calls ajms_ota_installEx() without passing in the <i>flag</i> parameter any protection domain identifier.
 * .
 */
int kjava_ext_verifyChainCert( KJavaCaList     *pCa,
                               int              iNumOfCa,
                               KJavaCertChain  *pChain,
                               int              iNumOfCertInChain,
                               int             *iDomain );

/** @} */

/** 
 * @addtogroup RSA_SHA1_Signature_KSI RSA SHA1 Digital Signature KSI
 * An interface for performing MIDlet suite JAR signature verification.
 * This interface must be implemented by the device manufacturer when supporting trusted MIDlet suite.
 * When not supporting trusted MIDlet suite, this interface need not exist in the native system.
 *
 * When supporting trusted MIDlet suites and the AJSC built-in SSL is enabled,
 * this interface is implemented in AJSC and therefore need not be implemented by the device manufacturer.
 *
 * By default, support of trusted MIDlet suite is enabled.
 * To disable the support, a library customization request needs to be submitted.
 *
 * @par Include file 
 * \#include kjava_sys_ext.h
 * @{
 */

/** 
 *        Verifies an RSA-SHA1 signature.
 * @param pCert    
 *        A pointer to an X509 certificate in Base64 format.
 * @param iCertLen 
 *        The size in bytes of the string indicated by <i>pCert</i>.
 * @param pJar     
 *        The JAR binary data to be verified.
 * @param iJarLen  
 *        The size in bytes of the data indicated by <i>pJar</i>.
 * @param pSign    
 *        A pointer to the string containing the BASE64-formatted signature for the data <i>pJar</i>.
 * @param iSignLen 
 *        The size in bytes of the string indicated by <i>pSign</i>.
 *
 * @retval 0 if the function succeeds.
 * @retval 1 if the function fails.
 * 
 * Implementation of this function is necessary only when the support of trusted MIDlet suite is enabled. 
 * If, however, the AJSC built-in SSL is enabled, this function is implemented in AJSC and therefore 
 * need not be implemented by the device manufacturer.
 * See @ref page_built_in_ssl for details of the AJSC built-in SSL.
 *
 * This function can be called in the KVE thread context during a trusted MIDlet suite installation started by 
 * the AMS by calling  ajms_ota_install() or ajms_ota_installEx() without passing in the <i>flag</i> 
 * parameter any protection domain identifier.
 */
int kjava_ext_verifySignature( 
                         unsigned char  *pCert,
                         int             iCertLen,
                         unsigned char  *pJar,
                         int             iJarLen,
                         unsigned char  *pSign,
                         int             iSignLen );

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_EXT_HEADER */
