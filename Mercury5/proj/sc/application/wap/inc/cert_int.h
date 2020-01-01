
#ifndef __CERT_INT_H__
#define __CERT_INT_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define MD5_HASH_LEN 16             /**< MD5 hash len */
#define CERT_INVALID_STORE_ID   -1   /**< invalid store id */

#define CERT_TRUST_CERT_BEGIN_LEN  27  /**< trust cert begin len */
#define CERT_TRUST_CERT_END_LEN    25  /**< trust cert end len */
#define CERT_CRL_CERT_BEGIN_LEN    24  /**< crl cert begin len */
#define CERT_CRL_CERT_END_LEN      22  /**< crl cert end len */

#define CERT_UTC_YEAR_LEN       2   /**< UTC time year<yy> length <bytes> */
#define CERT_GTC_YEAR_LEN       4   /**< GTC time year<yyyy> length <bytes> */
#define CERT_MONTH_LEN          2
#define CERT_DAY_LEN            2
#define CERT_HOUR_LEN           2
#define CERT_MINUTE_LEN         2
#define CERT_SECOND_LEN         2
#define CERT_TIME_LEN           14   /**< the length of time<yyyymmddhhmmss> (bytes) */

#define CERT_SERIAL_MAX_LEN            100   /**< serial max len in cert */
#define CERT_ISSUR_OR_SUBJECT_MAX_LEN  300   /**< issur or subject max len in cert */
#define CERT_PUBLIC_KEY_MAX_LEN        600   /**< public key max len in cert */

int32_t certX509v3Asn1Parse(T_CERT_Context*cert,uint8_t *encode,uint32_t length);
int32_t certX509CrlAsn1Parse(T_CERT_CrlContext*crl,uint8_t *encode,uint32_t length);

int32_t certCreateContext(T_CERT_Context **ppcert,uint8_t *pcert,CERT_CERT_FORMAT cert_format,uint32_t cert_len);
void certFreeContext(T_CERT_Context *cert_tobefree);
int32_t certOutport( uint8_t *asn1_code,uint32_t asn1_code_len,CERT_CERT_TYPE cert_type,CERT_CERT_FORMAT cert_format,uint8_t *cert_buf,uint32_t *cert_len);
int32_t certInport( CERT_CERT_TYPE cert_type,CERT_CERT_FORMAT cert_format,uint8_t *cert_buf,uint32_t cert_len,uint8_t *asn1_code, uint32_t *asn1_code_len);
int32_t certCreateStore(CERT_CERT_TYPE cert_type);
int32_t certAddToCertStore(CERT_STORE_TYPE csid,const T_CERT_Buf *certs,int32_t count,CERT_CERT_FORMAT cert_format);
int32_t certDestoryStore(int32_t store_id);
int32_t certClearStore(int32_t store_id);
int32_t certFreeObjChain(CERT_LIST_OF(T_CERT_Obj) *certchain_tobefree,CERT_CERT_TYPE cert_type);
int32_t certCrlCreateContext(T_CERT_CrlContext **pcrl,uint8_t *crl_encode,int32_t crl_encodetype,uint32_t);
void certCrlFreeContext(T_CERT_CrlContext *crl_tobefree);

#ifdef  __cplusplus
}
#endif

#endif /* __CERT_INT_H__ */

