
/**
 * @file
 * Certificate Management Service Layer
 *
 * Service API exposed by the Certificate Management.
 *
 * <!-- #interface list begin -->
 * \section svc_cert_interface Interface
 * - NCCcert_openStore()
 * - NCCcert_addFileToCertStore()
 * - NCCcert_saveToRomStore()
 * - NCCcert_asn1TimeToSSLTime()
 * - NCCcert_refreshStore()
 * - NCCcert_closeStore()
 * - NCCcert_createChain()
 * - NCCcert_freeChain()
 * - NCCcert_verifyCertChain()
 * - NCCcert_getCertChainRootCA()
 * - NCCcert_export()
 * - NCCcert_importObjToStore()
 * - NCCcert_getFirstObjFromStore()
 * - NCCcert_getNextObjFromStore()
 * - NCCcert_deleteObjFromStore()
 * - NCCcert_enumObjInStore()
 * - NCCcert_freeObj()
 * - NCCcert_getObjEncodeLen()
 * - NCCcert_exportObj()
 * - NCCcert_getObjFormat()
 * - NCCcert_getSubjectnameLen()
 * - NCCcert_getSubjectname()
 * - NCCcert_getIssuernameLen()
 * - NCCcert_getIssuerName()
 * - NCCcert_crlGetIssuename()
 * - NCCcert_getSubjectAltNameType()
 * - NCCcert_getSubjectAltNameLen()
 * - NCCcert_getSubjectAltName()
 * - NCCcert_crlGetEffectivedate()
 * - NCCcert_getVersion()
 * - NCCcert_getSerialNumberLen()
 * - NCCcert_getSerialNumber()
 * - NCCcert_getSignAlg()
 * - NCCcert_getPublicKeyAlg()
 * - NCCcert_getPublicKeyLen()
 * - NCCcert_getPublicKey()
 * - NCCcert_crlGetVersion()
 * - NCCcert_crlGetSignAlg()
 * - NCCcert_crlFindObj()
 * - NCCcert_adjustUtcTime()
 * - NCCcert_adjustGenTime()
 * - NCCcert_getNotBefore()
 * - NCCcert_getNotAfter()
 * - NCCcert_crlExport()
 * - NCCcert_CreateObj()
 * - NCCcert_sigVerifyInit()
 * - NCCcert_sigVerifyUpdate()
 * - NCCcert_sigVerifyFinal()
 * - NCCcert_getKeyUseage()
 * - NCCcert_getExtendedKeyUseage()
 * - NCCcert_getBasicConstraintsLen()
 * - NCCcert_getBasicConstraints()
 * - NCCcert_dupPublicKey()
 * - NCCcert_getSubjectCNLen()
 * - NCCcert_getSubjectCN()
 * - NCCcert_VerifyTimeValid()
 * <!-- #interface list end -->
 */

#ifndef __NCCCERT_H__
#define __NCCCERT_H__

#include <bnst.h>
#include <alg_module.h>
#include <alg_enc.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
orgnize to threee certificate store:
    1.individual certificate store : for personal use and client verification (extern)
    2.trust root certificate store:  for server verification
    3.crl(certificate revoke list) certificate store : for crl check

all kinds of store include two memory area:
    1. ram store : in ram space ,for verify operation . parsed format
    2. rom store : in file system, asn.1 encode certificate format
*/

/** the certificate store information */
typedef enum
{
    CERT_SERVER_AUTH_ROOT_STORE = 0,
    CERT_CODE_SIGN_ROOT_STORE,
    CERT_CRL_STORE
}CERT_STORE_TYPE;

/** certificate type */
typedef enum
{
    CERT_X509_V3_CERTIFICATE = 1,
    CERT_X509_V2_CRL
}CERT_CERT_TYPE;

/** certificate encode format */
typedef enum
{
    CERT_X509_ASN1_ENCODED = 1,
    CERT_X509_BASE64_ENCODED
}CERT_CERT_FORMAT;

#define CERT_LIST_OF(x)    T_SSL_List  /**< the list for store certificate object */

/** the cert's error code */
#define CERT_OK                       0      /**< ok */
#define CERT_FAILED                   -101   /**< fail */
#define CERT_FOUND                    -102   /**< the certificate is found */
#define CERT_NOT_FOUND                -103   /**< the certificate isn't found */
#define CERT_CREATE_EMPTY_CONT_FAIL   -104   /**< create empty context failed */
#define CERT_STORE_CANNOT_OPEN        -105   /**< can't open the store */
#define CERT_CANNOT_LOAD              -106   /**< can't load the cert, can't parse or no enough buf */
#define CERT_STORE_CRACKED            -107   /**< store is cracked */
#define CERT_INVALID_CERTTYPE         -108   /**< invalid certificate type */
#define CERT_FILE_SIZE_DISMATCH       -109   /**< cert file size dismatch */
#define CERT_CSID_INVALID             -110   /**< cert store class id invalid */
#define CERT_CREAT_STORE_FAIL         -111   /**< creat cert store failed */
#define CERT_EXPORT_OBJ_FAIL          -112   /**< export cert obj failed */
#define CERT_GET_FILE_SIZE_FAIL       -113   /**< get cert file size failed */
#define CERT_CREAT_OBJ_FAIL           -114   /**< create cert obj failed */
#define CERT_GET_OBJ_ENC_TYPE_FAIL    -115   /**< get obj encode type failed */
#define CERT_CREAT_CONTEXT_FAIL       -116   /**< create context failed */
#define CERT_UNSUPPORT_ALG            -117   /**< unsupport algorithm */
#define CERT_INS_LIST_ERR             -118   /**< insert list error */
#define CERT_EMPTY_CHAIN              -119   /**< cert chain no cert */
#define CERT_GET_OBJ_FROM_STORE_FAIL  -120   /**< get cert obj from store failed */
#define CERT_CHAIN_BROKEN             -121   /**< no root ca for a cert chain */
#define CERT_PARSE_ERROR              -122   /**< parse certificate error */
#define CERT_UNSUPPORTED_OBJECT       -123   /**< unsupported certificate object */
#define CERT_UNSUPPORTED_ENCODE       -124   /**< unsupported encode format of certificate */
#define CERT_NO_BUF                   -125   /**< memory error */
#define CERT_INVALID_ARG              -126   /**< invalid argument */
#define CERT_INVALID_SIGNATURE        -127   /**< invalid signature */
#define CERT_INVALID_TIME             -128   /**< invalid time */
#define CERT_HAS_REVOKED              -129   /**< the certificate has revoked */
#define CERT_INVALID_VERSION          -130   /**< invalid version */
#define CERT_EXIST                    -131   /**< there is already the same cerification in the store*/
#define CERT_ASN1_OBJ_UNKNOW          -132   /**< unknown cert asn1 object */
#define CERT_MALLOC_FAILED            -133   /**< malloc failed */
#define CERT_STORE_NOT_EXIST          -134   /**< the sore have not exist */
#define CERT_UNKOWN_TYPE              -135   /**< unknown cert type */
#define CERT_PARSE_HEAD_ERROR         -136   /**< parse cert head error */
#define CERT_NULL_POINTER             -137   /**< null pointer */
#define CERT_NO_SUBJECT_ALT_NAME      -138   /**< no cert subject alt name */
#define CERT_NO_KEY_USAGE_EXT         -139   /**< no key usage extension */
#define CERT_NO_EXT_KEY_USAGE_EXT     -140   /**< no extended key usage extension */
#define CERT_NO_BASIC_CONSTRAINS      -141   /**< no basic constrains */
#define CERT_UNSPPORTED_TIME_TYPE     -142   /**< unsupported time type */
#define CERT_MONTH_MORE_THAN_12       -143   /**< month more than 12 */
#define CERT_ISSUER_NOT_MATCH         -144   /**< cert issuer not match */
#define CERT_RSA_DECRYPT_FAILED       -145   /**< RSA public decrypt failed */
#define CERT_VERIFY_MAC_FAILED        -147   /**< verify MAC failed */
#define CERT_NO_ROOT_CA               -148   /**< no root ca for a cert chain */
#define CERT_FREE_OBJ_FAIL            -149   /**< free obj from chain failed */
#define CERT_ROOT_CA_EXPIRED          -150   /**< root ca expired */
#define CERT_NO_STORE_FILE            -151   /**< no cert store file */
#define CERT_NO_COMMON_NAME           -152   /**< no commonn name in cert subject */

/** the certificate verify callback function */
typedef int32_t (*CERT_VERIFY_CALLBACK_FUNC)(int32_t session,T_CERT_Buf * cert_list, int32_t cert_count);

/** the certificate verify callback context */
typedef struct
{
    CERT_VERIFY_CALLBACK_FUNC callback_func; /**< the certificate verify callback function */
    int32_t callback_arg;                   /**< the arguments of callback_func */
}T_SSL_Cert_Verify_CallBack;

/** the certificate display callback function */
typedef int32_t (*CERT_DISPLAY_CALLBACK_FUNC)(T_CERT_Obj *cert_obj, int8_t err_code);

/** the certificate display callback context */
typedef struct
{
    CERT_DISPLAY_CALLBACK_FUNC callback_func; /**< the certificate display callback function */
    int32_t callback_arg;                     /**< the arguments of callback_func */
}T_SSL_Cert_Display_CallBack;

/** certificate store definition */
typedef struct
{
    CERT_CERT_TYPE cert_type;        /**< the type of certificate  */
    CERT_LIST_OF(T_CERT_Obj) store_objlist; /* the list for insert certificate object to it */
}T_CERT_Store;

typedef struct
{
    uint8_t *fd_name;
    int64_t load_time;
    int32_t store_id;
    CERT_CERT_TYPE cert_type;
    int32_t open_count;
}T_CERT_Config;

extern T_CERT_Config g_cert_Configs[];

/** the time format SSL uses */
typedef struct st_ssl_sys_time
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
}T_SSL_SysTime;

typedef struct
{
    CERT_Sig_Alg alg;  /* signature algorithm */
    uint8_t* sigData;
    int32_t sigLen;
    uint8_t* pub_key;
    int32_t keyLen;
    T_ALG_MdCtx md_ctx;
}T_CERT_sig_verify;

/** the type of certificate subjectAltName */
typedef enum
{
    CERT_SUBJECTALTNAME_OTHERNAEM,
    CERT_SUBJECTALTNAME_RFC822NAME,
    CERT_SUBJECTALTNAME_DNSNAME,
    CERT_SUBJECTALTNAME_X400ADDRESS,
    CERT_SUBJECTALTNAME_DIRECTORYNAEM,
    CERT_SUBJECTALTNAME_EDIPARTYNAME,
    CERT_SUBJECTALTNAME_URI,
    CERT_SUBJECTALTNAME_IPADDRESS,
    CERT_SUBJECTALTNAME_REGISTERID,
    CERT_SUBJECTALTNAME_NONE
}T_CERT_SubjectAltName_Type;

/** the cert verify chain handle */
typedef struct
{
    T_SSL_List *cert_chain; /**< the cert chain list head */
    T_CERT_Obj* root_ca;    /**< the CA which issuer this chain */
}T_CERT_VerifyChain;

/** cert manage functions */
/**
 * Open a certificate store
 * \param  csid(input)  the class of certificaate store
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      ALG_FAIL
 *      CERT_CSID_INVALID
 *      CERT_STORE_CANNOT_OPEN
 *      CERT_CREAT_STORE_FAIL
 *      CERT_CANNOT_LOAD
 *      CERT_STORE_CRACKED
 *      CERT_NO_STORE_FILE
 */
int32_t NCCcert_openStore(CERT_STORE_TYPE csid);

/**
 * Add a certificate file to both rom certificaate store and ram certificate store
 * \param  csid(input)     the class of certificaate store
 * \param  fd_name(input)  the name of certificate file to be added
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_CSID_INVALID
 *      CERT_STORE_NOT_EXIST
 *      CERT_GET_FILE_SIZE_FAIL
 *      CERT_STORE_CANNOT_OPEN
 *      CERT_MALLOC_FAILED
 *      CERT_FILE_SIZE_DISMATCH
 *      CERT_GET_OBJ_ENC_TYPE_FAIL
 *      CERT_UNKOWN_TYPE
 *      CERT_CREAT_OBJ_FAIL
 *      CERT_EXIST
 */
int32_t NCCcert_addFileToCertStore(CERT_STORE_TYPE csid,uint8_t *fd_name);

/**
 * Save ram certificate store to rom certificate store as *.cs file
 * \param  csid(input)    the class of certificate store
 * \param  fd_name(input) the rom store file's name
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_CSID_INVALID
 *      CERT_STORE_CANNOT_OPEN
 *      CERT_STORE_NOT_EXIST
 *      CERT_MALLOC_FAILED
 *      CERT_EXPORT_OBJ_FAIL
 */
int32_t NCCcert_saveToRomStore(CERT_STORE_TYPE csid,uint8_t *fd_name);

/**
 * Refresh ram certificate store based on rom certificate store as *.cs file
 * \param  csid(input)  the class of certificaate store
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_CSID_INVALID
 *      CERT_STORE_NOT_EXIST
 *      CERT_STORE_CANNOT_OPEN
 *      CERT_STORE_CRACKED
 *      CERT_CANNOT_LOAD
 */
int32_t NCCcert_refreshStore(CERT_STORE_TYPE csid);

/**
 * Close the ram certificate store
 * \param  csid(input) the class of certificaate store
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_CSID_INVALID
 *      CERT_STORE_NOT_EXIST
 */
int32_t NCCcert_closeStore(CERT_STORE_TYPE csid);

/** cert chain functions */
/**
 * Create a certicate chain
 * \param  certchain_encode(input)  certificates for create chain
 * \param  certchain_count(input)   the number of certificates
 * \return
 *  > 0   cert chain handle
 *  erroe code:
 *     CERT_MALLOC_FAILED
 *     CERT_CREAT_CONTEXT_FAIL
 *     CERT_INS_LIST_ERR
 */
int32_t NCCcert_createChain(T_CERT_Buf *certchain_encode,int32_t certchain_count);

/**
 * Free certificate chain
 * \param  cert_chain_handle(input)  cert chain handle returned by NCCcert_createChain
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *     CERT_FREE_OBJ_FAIL
 */
int32_t NCCcert_freeChain(int32_t cert_chain_handle);

/**
 * Verify the validity of certificates chain
 * \param  csid(input) the type of cert store
 * \param  cert_chain_handle(input)  certificates chain to be verified
 * \return
 *   > 0  the length of root CA which issuered this chain
 *   erroe code:
 *     CERT_EMPTY_CHAIN
 *     CERT_GET_OBJ_FROM_STORE_FAIL
 *     CERT_ROOT_CA_EXPIRED
 *     CERT_NO_ROOT_CA
 *     CERT_INVALID_TIME
 *     CERT_ISSUER_NOT_MATCH
 *     CERT_HAS_REVOKED
 *     CERT_INVALID_SIGNATURE
 *     CERT_INVALID_CERTTYPE
 */
int32_t NCCcert_verifyCertChain(CERT_STORE_TYPE csid,int32_t cert_chain_handle);

/**
 *  get the root ca which issuers the cert chain
 * \param  cert_chain_handle(input)  cert chain handle
 * \return
 *   asn.1 encoded root CA
 *   NULL  error code, which defined in NCCcert.h
 */
uint8_t* NCCcert_getCertChainRootCA(int32_t cert_chain_handle);

/**
 * Get the public key of a certificate
 * \param  cert(input)  the certificate from which get the public key
 * \return if succeed return the public key in certificate, else return NULL
 */
T_ALG_PubKey* NCCcert_getPublicKey(const T_CERT_Context *cert);

/** certificate functions */
/**
 * Export a certificate object based on appoint format
 * \param  cert(input)  the certificate object from which export certificate object
 * \param  cert_format(input)  the format of certificate object
 * \param  buf(output)  the certificate object exported
 * \param  len(output)  the length of export certificate object
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *     CERT_NO_BUF
 *     CERT_UNKOWN_TYPE
 *     CERT_UNSUPPORTED_ENCODE
 */
int32_t NCCcert_export(const T_CERT_Context *cert,CERT_CERT_FORMAT cert_format,uint8_t *buf,uint32_t *len);

/** cert obj functions */
/**
 * Import a certificate object to certificate store
 * \param  csid(input)     the class of certificaate store
 * \param  obj(input)           the certificated object
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 *      CERT_STORE_NOT_EXIST
 */
int32_t NCCcert_importObjToStore(CERT_STORE_TYPE csid,T_CERT_Obj *obj);

/**
 * Get the first certificate object in the appoint certificate store
 * \param  csid(input)     the class of certificaate store
 * \return
 *   certificate object   succeed
 *   NULL     error occured
 */
T_CERT_Obj *NCCcert_getFirstObjFromStore(CERT_STORE_TYPE csid);

/**
 * Get the next certificate object of cobj_before in the appoint certificate store
 * \param  csid(input)     the class of certificaate store
 * \param  cobj_before(input)  the certificate object from which get it's next certificate object
 * \return
 *   certificate object   succeed
 *   NULL     error occured
 */
T_CERT_Obj *NCCcert_getNextObjFromStore(CERT_STORE_TYPE csid,T_CERT_Obj *cobj_before);

/**
 * Delete a certificate object from certificate store
 * \param  csid(input)     the class of certificaate store
 * \param  cobj_tobedelete(input)  the certificate object to be deleted
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_INVALID_ARG
 */
int32_t NCCcert_deleteObjFromStore(CERT_STORE_TYPE csid,T_CERT_Obj *cobj_tobedelete);

/**
 * Get the number of certificate objects in a certificate store
 * \param   csid(input)     the class of certificaate store
 * \return
 *   the number of objects   succeed
 *   erroe code:
 *      CERT_STORE_NOT_EXIST
 */
int32_t NCCcert_enumObjInStore(CERT_STORE_TYPE csid);

/**
 * Free a certificate object
 * \param  obj_tobefree(input)  the certificate object to be freed
 * \param  cert_type(input)     the type of certificate object
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_UNKOWN_TYPE
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_freeObj(T_CERT_Obj *obj_tobefree,CERT_CERT_TYPE cert_type);

/**
 * Get the length of a certificate object based on appoint format
 * \param  obj(input)     the certificate object from which get it's length
 * \param  cert_type(input)    the type of certificate object
 * \param  cert_format(input) the format of certificate object
 * \return
 *   the length   succeed
 *   erroe code:
 *      CERT_UNKOWN_TYPE
 *      CERT_NULL_POINTER
 *      CERT_UNSUPPORTED_ENCODE
 */
int32_t NCCcert_getObjEncodeLen(const T_CERT_Obj *obj,CERT_CERT_TYPE cert_type,CERT_CERT_FORMAT cert_format);

/**
 * Export a certificate object based on appoint format
 * \param  obj(input)     the certificate object from which export certificate object
 * \param  len(input)     the length of obj
 * \param  cert_type(input)    the type of certificate object
 * \param  cert_format(input) the format of certificate object to be exported
 * \param  buf(output)    the certificate object exported
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_UNKOWN_TYPE
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_exportObj(const T_CERT_Obj *obj,CERT_CERT_TYPE cert_type,uint8_t *buf,uint32_t *len,CERT_CERT_FORMAT cert_format);

/**
 * Get the format of certificate
 * \param  buf(input)   the buffer which stores certificate
 * \param  cert_type(input) the type of certificate
 * \return
 *   encode type  succeed
 *   erroe code:
 *      CERT_UNSUPPORTED_ENCODE
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getObjFormat(const uint8_t *buf,CERT_CERT_TYPE cert_type);

/** cert info functions */
/**
 * Get the length of certificate subject
 * \param  cobj(input)  the certificate to be got
 * \return
 *   > 0   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getSubjectnameLen(const T_CERT_Obj *cobj);

/**
 * Get the subject of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \param  len(input)   the length of subject
 * \param  out(output)  the subject of certificate
 * \return
 *   the count of subject   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getSubjectname(const T_CERT_Obj *cobj,uint8_t *out,int32_t len);

/**
 * Get the length of certificate issuer
 * \param  cobj(input)  the certificate to be got
 * \return
 *   > 0   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getIssuernameLen(const T_CERT_Obj *cobj);

/**
 * Get the Issuer of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \param  len(input)   the length of subject
 * \param  out(output)  the subject of certificate
 * \return
 *   the count of subject   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getIssuerName(const T_CERT_Obj *cobj,uint8_t *out,int32_t len);

/**
 * Get the issur of CRL certificate
 * \param  cobj(input)  the certificate to be got
 * \param  in(output)   the issur of certificate
 * \return
 *   the count of issur   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_crlGetIssuename(const T_CERT_Obj *cobj,uint8_t **in);

/**
 * Get the Effective time of CRL certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *   the effective time  succeed
 *   NULL                failed
 */
T_SSL_SysTime* NCCcert_crlGetEffectivedate(const T_CERT_Obj *cobj);

/**
 * Get the version of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *   the version  succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getVersion(const T_CERT_Obj *cobj);

/**
 * Get the serial number of trust certificate
 * \param  cobj(input)  the certificate to be got
 *         sn(output)   the serial number of certificate
 * \return
 *   > 0   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getSerialNumberLen(const T_CERT_Obj *cobj);

/**
 * Get the serial number of trust certificate
 * \param  cobj(input)  the certificate to be got
 *         serial_len   the length of certificate serial number
 *         buffer(output)   the serial number of certificate
 * \return
 *   CERT_OK       succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getSerialNumber(const T_CERT_Obj *cobj,uint8_t *buffer,int32_t serial_len);

/**
 * Get the signature algorithm of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \param  sa(output)   the signature algorithm of certificate
 * \return   sig_alg_id
 */
CERT_Sig_Alg NCCcert_getSignAlg(const T_CERT_Obj *cobj);

/**
 * Get the public key algorithm of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \param  ca(output)   the public key algorithm of certificate
 * \return  public key alg
 */
CERT_Public_Key_Alg NCCcert_getPublicKeyAlg(const T_CERT_Obj *cobj);

/**
 * Get the public key len of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *   > 0  succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getPublicKeyLen(const T_CERT_Obj *cobj);

/**
 * Get the public key of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \param  len(input)   the length of public key
 * \param  buffer(output)   the public key of certificate
 * \return
 *   CERT_OK       succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
 int32_t NCCcert_dupPublicKey(const T_CERT_Obj *cobj,uint8_t *buffer,int32_t len);

/**
 * Get the version of CRL certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *   the version  succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_crlGetVersion(const T_CERT_Obj *cobj);

/**
 * Get the signature alogrithm of CRL certificate
 * \param  cobj(input)  the certificate to be got
 * \param  sa(output)   the signature alogrithm of certificate
 * \return
 *   the length of algorithm   succeed
 *   erroe code:
 *      CERT_UNSUPPORT_ALG
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_crlGetSignAlg(const T_CERT_Obj *cobj,uint8_t **sa);

/**
 * Find the appoint CRL certificate whether in ram certificate stroe
 * \param  content(input)  the certificate to be found
 * \return
 *   the cert obj   succeed
 *   NULL   error occured
 */
T_CERT_Obj *NCCcert_crlFindObj(uint8_t *content);

/**
 * Adjust UTC time
 * \param  utc_time(input)  the UTC time to be adjusted
 * \param  buf1(output)     the time adjusted
 * \return the lenth of adjusted time
 */
int32_t NCCcert_adjustUtcTime(const uint8_t *utc_time,uint8_t *buf1);

/**
 * Adjust general time
 * \param  gen_time(input)  the general time to be adjusted
 * \param  buf1(output)     the time adjusted
 * \return the lenth of adjusted time
 */
int32_t NCCcert_adjustGenTime(const uint8_t *utc_time,uint8_t *buf1);

/**
 * Get the start time of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *   CERT_OK       succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 *      CERT_UNSPPORTED_TIME_TYPE
 */
 int32_t NCCcert_getNotBefore(const T_CERT_Obj *cobj,T_SSL_SysTime* not_before);

/**
 * Get the end date of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *   CERT_OK       succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 *      CERT_UNSPPORTED_TIME_TYPE
 */
int32_t NCCcert_getNotAfter(const T_CERT_Obj *cobj,T_SSL_SysTime* not_after);

/**
 * Adjust asn1 time to SSL format time
 * \param  atime(input)   the asn1 time to be adjusted
 * \param  dtime(output)  the SSL format time
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 *      CERT_UNSPPORTED_TIME_TYPE
 *      CERT_MONTH_MORE_THAN_12
 */
int32_t NCCcert_asn1TimeToSSLTime(const T_CERT_Asn1Time *atime,T_SSL_SysTime *dtime);

/** crl functions */
/**
 * Export a certificate object based on appoint format
 * \param  crl(input)   the certificate object from which export certificate object
 * \param  type(input)  the format of certificate object
 * \param  buf(output)  the certificate object exported
 * \param  len(output)  the length of export certificate object
 * \return
 *   CERT_OK     succeed
 *   error code  which defined in NCCcert.h
 */
int32_t NCCcert_crlExport(const T_CERT_CrlContext *crl,int32_t type,uint8_t *buf,uint32_t *len);

/**
 * Create a certificate object
 * \param  cert(input)  the certificate from which certificate object to be created
 * \param  cert_format(input)  the format of certificate object to be created
 * \param  cert_len(input)   the length of cert
 * \param  cert_type(input)  the type of certificate object to be created
 * \return
 *   certificate object   succeed
 *   NULL     error occured
 */
T_CERT_Obj *NCCcert_CreateObj(uint8_t *cert,CERT_CERT_FORMAT cert_format,uint32_t cert_len,CERT_CERT_TYPE cert_type);

/**
 * Get the length of trust certificate basic constains
 * \param  cobj(input)  the certificate to be got
 * \return
 *  > 0  succeed
 *   erroe code:
 *      CERT_NO_BASIC_CONSTRAINS
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getBasicConstraintsLen(const T_CERT_Obj *cobj);

/**
 * Get the basic constains of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \param  len(input)   the length of basic constains
 * \param  buffer(output)   the basic constains of certificate
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_NO_BASIC_CONSTRAINS
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getBasicConstraints(const T_CERT_Obj *cobj,uint8_t *buffer,int32_t len);

/**
 * Get the type of a certificate subjectAltName
 * \param  cobj(input)  the certificate to be got
 * \return  Cert SubjectAltName Type
 */
T_CERT_SubjectAltName_Type NCCcert_getSubjectAltNameType(const T_CERT_Obj *cobj);

/**
 * Get the length of a certificate subjectAltName
 * \param  cobj(input)  the certificate to be got
 * \return
 *   > 0           succeed
 *   erroe code:
 *      CERT_NO_SUBJECT_ALT_NAME
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getSubjectAltNameLen(const T_CERT_Obj *cobj);

/**
 * Get the subjectAltName of a certificate
 * \param  cobj(input)  the certificate to be got
 * \param  len(input)   the length of subjectAltName
 * \param  buffer(output)  the subjectAltName
 * \return
 *   CERT_OK      succeed
 *   erroe code:
 *      CERT_NO_SUBJECT_ALT_NAME
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getSubjectAltName(const T_CERT_Obj *cobj, uint8_t *buffer, int32_t len);

/**
 * Get the key Useage of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *  > 0  succeed
 *   erroe code:
 *      CERT_NO_KEY_USAGE_EXT
 *      CERT_NULL_POINTER
 */
int32_t NCCcert_getKeyUseage(const T_CERT_Obj *cobj);

/**
 * Get the extended key useage of trust certificate
 * \param  cobj(input)  the certificate to be got
 * \return
 *  > 0  succeed
 *   erroe code:
 *      CERT_NO_EXT_KEY_USAGE_EXT
 *      CERT_NULL_POINTER
 */
 int32_t NCCcert_getExtendedKeyUseage(const T_CERT_Obj *cobj);

/**
  * alg: the algorithm string
  * key: the public key
  * keyLen: the length of public key
  * sigData: the pointer of the signature data buffer
  * sigLen: the length of the signature data buffer
  * return:
  *   the handle of this verification  succeed
  *   erroe code:
  *      CERT_MALLOC_FAILED
  *      CERT_UNSUPPORT_ALG
  *      ALG_FAIL
  */
 int32_t NCCcert_sigVerifyInit(CERT_Sig_Alg alg, uint8_t* pub_key, int32_t keyLen, uint8_t* sigData, int32_t sigLen);

/**
  * handle: the handle of this verification
  * data: the pointer of the data buffer
  * len: the length of the data buffer
  * \return  none
 */
void NCCcert_sigVerifyUpdate(int32_t handle, uint8_t* data,int32_t inLen);

/**
  * handle: the handle of this verification
  * data: the pointer of the data buffer
  * len: the length of the data buffer
  * \return
  *   CERT_OK      succeed
  *   erroe code:
  *      CERT_INVALID_SIGNATURE
  *      CERT_UNSUPPORTED_ENCODE
  *      ALG_FAIL
  *      CERT_VERIFY_MAC_FAILED
  */
int32_t NCCcert_sigVerifyFinal(int32_t handle, uint8_t* data, int32_t inLen);

/**
 * Get the common name length of subject
 * \param  cobj(input)  the certificate to be got
 * \return
 *   > 0   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 *      CERT_NO_COMMON_NAME
 */
int32_t NCCcert_getSubjectCNLen(const T_CERT_Obj *cobj);

/**
 * Get the common name of subject
 * \param  cobj(input)  the certificate to be got
 * \param  len(input) the length of comman name
 * \param  buffer(output) where to store the common name
 * \return
 *   CERT_OK   succeed
 *   erroe code:
 *      CERT_NULL_POINTER
 *      CERT_NO_COMMON_NAME
 */
int32_t NCCcert_getSubjectCN(const T_CERT_Obj *cobj,uint8_t *buffer, int32_t len);

/**
 * Verify one certificate validity date compare to current system time
 * \param  cert(input) the certificate to be verified
 * \param  time_format(input)  the time format in the certificaate
 * \param  time(input)  the current system time
 * \return
 *  CERT_OK      succeed
 *  error code   which defined in NCCcert.h
 */
int32_t NCCcert_VerifyTimeValid(const T_CERT_Context *cert,int32_t time_format,uint8_t *time);


#ifdef  __cplusplus
}
#endif

/*The meaning of __SLDPM_FREE etc are in mmi_common_def.h*/
#if defined(__TARGET__) && defined(__arm)
#define __SLDPM_FREE__  __attribute__((section(".sldpm_free")))
#define __SLDPM_WAP_SECTION__  __attribute__((section(".wap_section")))
#else
#define __SLDPM_FREE__
#define __SLDPM_WAP_SECTION__  
#endif

#endif /* __NCCCERT_H__ */
