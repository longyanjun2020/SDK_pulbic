/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#ifndef ALG_MODULE_H
#define ALG_MODULE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef  __cplusplus
extern "C" {
#endif

#include <bnst.h>
/** signature algorithm */
typedef enum
{
    CERT_UNKNOW_SIG_ALG = 0,
    CERT_X509_SIG_MD2WITHRSA,
    CERT_X509_SIG_MD5WITHRSA,
    CERT_X509_SIG_SHA1WITHRSA
}CERT_Sig_Alg;

/** public key algorithm */
typedef enum
{
    CERT_UNKNOW_PUBLIC_ALG = 0,
    CERT_X509_PUBLIC_RSA,
    CERT_X509_PUBLIC_DSA,
    CERT_X509_PUBLIC_DH
}CERT_Public_Key_Alg;

#define CERT_GET_EX_BUF_LEN(a) do{if((a) <= 0) return -25;}while(0)
#define CERT_EX_BUF_SUPPLEMENT 0x200
#define CERT_CRL_EX_BUF_SUPPLEMENT 0x10000

#define CERT_ASN1_UTCTIME           0x17  /**< universal time type */
#define CERT_ASN1_GENERALIZEDTIME   0x18  /**< generalized time type */

#define CERT_X509EXT_CRITICAL_FALSE 0

/** certificate version value */
#define CERT_X509_VERSION_1 0
#define CERT_509_VERSION_2 1
#define CERT_509_VERSION_3 2

/** data RSA encryption/decryption padding mode */
#define ALG_dRSA_PKCS1_PADDING  1  /**< PKCS1 padding */
#define ALG_dRSA_NO_PADDING     3  /**< No padding */

/** the return code of ALG operatiion */
#define ALG_SUCCEED         255  /**< succeed */
#define ALG_FAIL            0    /**< fail */
#define ALG_ERR_OCCUR       -1   /**< error occurs */

/** MD2 length infomation */
#define ALG_MD2_DIGEST_LEN  16   /**< the length of MD2 hash value */
#define ALG_MD2_BLOCK       16   /**< the length of MD2 int block */

/** MD5 length infomation */
#define ALG_MD5_DIGEST_LEN  16   /**< the length of MD5 hash value */
#define ALG_MD5_CBLOCK      64   /**< the length of MD5 char block */
#define ALG_MD5_LBLOCK      16   /**< the length of MD5 int block */

/** SHA length infomation */
#define ALG_SHA_DIGEST_LEN  20  /**< the length of SHA hash value */
#define ALG_SHA_CBLOCK      64  /**< the length of SHA char block */
#define ALG_SHA_LBLOCK      16  /**< the length of SHA int block */

#define ALG_RC4_LEN         256  /**< the length of RC4 data */

/*----------------------    Struct Definition   ------------------------*/
typedef struct node_st
{
    struct node_st *next;
    struct node_st *prev;
} T_SSL_Node;

typedef struct
{
    T_SSL_Node * pnode;
    int count;
} T_SSL_List;

/** certificate data buffer definition */
typedef struct
{
    char *data; /**< the data in the buffer */
    unsigned int len; /**< the length of data */
}T_CERT_Buf;

/**< certificate buffer block definition */
typedef struct
{
    unsigned char *buf;      /**< the data in the buffer */
    unsigned int offset;  /**< the offset of data in the buffer */
    unsigned int max_len; /**< the maximun length of data the buffer supports */
}T_CERT_DataBufBlock;

/**<  the algorithm id contained in the certificate */
typedef struct
{
    char        *objid;  /**< the id of algorithm, like "1.2.840.113549.1.1.4" */
    T_CERT_Buf    algVal;  /**< the vlaue of the alogrithm */
}T_CERT_AlgOrId;

/**< the asn.1 time in the certificate */
typedef struct
{
    unsigned int type;    /**< the type of the time */
    unsigned int length;  /**< the length of the time */
    char *data;     /**< the time */
}T_CERT_Asn1Time;

/** asn.1 bit string definitiion */
typedef struct
{
    unsigned int length;  /**< the length of bit string */
    char *data;     /**< the bit string */
    char left;      /**< the left length of bit string */
    char unUsed[3];
}T_CERT_Asn1BitStr;

/** the signature algorithm in the certificate */
typedef struct
{
    T_CERT_AlgOrId sigAlg;    /**< the signature alogrithm id */
    T_CERT_Asn1BitStr sigVal; /**< the value of the signature alogrithm */
}T_CERT_X509Sig;

/** the distinguished name contained in the certificate */
typedef struct
{
    char      *objid;  /**< the name's id like "2.5.4.6" */
    T_CERT_Buf    dnVal;   /**< the value of name */
}T_CERT_X501Dn;

/** the public key in the certificate */
typedef struct
{
    T_CERT_AlgOrId algid;  /**< the id of public key, like "1.2.840.113549.1.1.1" */
    T_CERT_Asn1BitStr key; /**< the value of public key */
}T_CERT_X509PubKey;

/** the extensiions in the certificate */
typedef struct
{
    char *ex_objid;     /**< the id of extensions */
    char critical;      /**< the critical of extensions */
    char  unUsed[3];
    T_CERT_Buf   value;   /**< the value of extensiions */
}T_CERT_X509Ext;

/** the validity time in the certificate */
typedef struct
{
    T_CERT_Asn1Time notbefore; /**< the start time of this certificate */
    T_CERT_Asn1Time notafter;  /**< the end time of this certificate */
}T_CERT_Time;

/** informations in certificate */
typedef struct
{
    unsigned int           version;       /**< the version of this certificate */
    T_CERT_Buf         serialNumber;  /**< the serial number of this certificate */
    T_CERT_AlgOrId     signature;     /**< the signature alogrithm of this certificate */
    T_CERT_X501Dn*     issuer;        /**< the issur of this certificate */
    unsigned int           issuer_count;  /**< the count of issur */
    T_CERT_Time        validity;      /**< the validity time of this certificate */
    T_CERT_X501Dn*     subject;       /**< the owner of this certificate */
    unsigned int           subject_count; /**< the count of subject */
    T_CERT_X509PubKey  public_key;    /**< the public key of this certificate */
    T_CERT_Asn1BitStr  issuerUID;     /**< the issur unique idetifier */
    T_CERT_Asn1BitStr  subjectUID;    /**< the subject unique idetifier */
    T_CERT_X509Ext*    extensions;    /**< the extensions of this certificate */
    unsigned int           ext_count;     /**< the count of extensions */
} T_CERT_Info;

/** certificate context definition */
typedef struct
{
    T_CERT_Info* cert_info;         /**< certificate base information */
    T_CERT_X509Sig cert_signature;  /**< the signature of this certificate */
    char* asn1_encoded;           /**< the asn.1 encoded format of this certificaate */
    unsigned int asn1_encoded_length;   /**< the length of this certificate in asn.1 encoded format */
    T_CERT_DataBufBlock ex_data;    /**< the extensions of this certificate */
} T_CERT_Context;

typedef struct
{
    T_CERT_Buf serialNumber;
    T_CERT_Asn1Time revocationDate;
    unsigned int extensions_count;
    T_CERT_X509Ext *extensions;/* optional */
}T_CERT_X509Revoked;

/** informations in CRL */
typedef struct
{
    unsigned int version;
    T_CERT_AlgOrId sig_alg;
    T_CERT_X501Dn *issuer;
    unsigned int issuer_count;
    T_CERT_Asn1Time thisUpdate;
    T_CERT_Asn1Time nextUpdate;
    unsigned int revoked_count;
    T_CERT_X509Revoked *revoked;
    unsigned int extensions_count;
    T_CERT_X509Ext *extensions;
} T_CERT_CrlInfo;

/** CRL context definition */
typedef struct
{
    T_CERT_CrlInfo *crl_info;
    T_CERT_X509Sig signature;
    char *asn1_encoded;
    unsigned int asn1_encoded_length;
    int references;
    T_CERT_DataBufBlock ex_data;
} T_CERT_CrlContext;

/** certificate object definition */
typedef struct
{
    T_SSL_Node node;   /**< the node for insert to certificate object list */
    union
    {
        T_CERT_Context * cert;   /**< trust certificate */
        T_CERT_CrlContext *crl;  /**< revoked certificate */
    }obj;
}T_CERT_Obj;

/** the symmetric cryptograpy RC4 definition */
typedef struct
{
    unsigned int rc4_x;
    unsigned int rc4_y;
    unsigned int rc4_data[ALG_RC4_LEN];
}T_ALG_RC4Key;

/** the hash cryptograpy MD2 definition */
typedef struct
{
    int num;
    unsigned char data[ALG_MD2_BLOCK];
    unsigned int cksm[ALG_MD2_BLOCK];
    unsigned int state[ALG_MD2_BLOCK];
} T_ALG_MD2Ctx;

/** the hash cryptograpy MD5 definition */
typedef struct
{
    unsigned int A,B,C,D;
    unsigned int Nl,Nh;
    unsigned int md5_data[ALG_MD5_LBLOCK];
    int num;
} T_ALG_MD5Ctx;

/** the hash cryptograpy SHA definitiion */
typedef struct
{
    unsigned int h0,h1,h2,h3,h4;
    unsigned int Nl,Nh;
    unsigned int sha_data[ALG_SHA_LBLOCK];
    int num;
} T_ALG_ShaCtx;

/** the asymmetric cryptograpy RSA definition */
typedef struct
{
    const void *meth;
    T_ALG_BigNum *n;
    T_ALG_BigNum *e;
    int flags;
    T_ALG_BnMontCtx *_method_mod_n;
}T_ALG_RSA;

void algMD2Init(T_ALG_MD2Ctx *c);
void algMD2Update(T_ALG_MD2Ctx *c, const unsigned char *data, unsigned int len);
void algMD2Final(unsigned char *md, T_ALG_MD2Ctx *c);
void algMD5Init(T_ALG_MD5Ctx *c);
void algMD5Update(T_ALG_MD5Ctx *c, const unsigned char*data_, unsigned int len);
void algMD5Final(unsigned char *md, T_ALG_MD5Ctx *c);
void algSHA1Init(T_ALG_ShaCtx *c);
void algSHA1Update(T_ALG_ShaCtx *c, const void*data_, unsigned int len);
void algSHA1Final(unsigned char *md, T_ALG_ShaCtx *c);
void algRC4SetKey(T_ALG_RC4Key *key, int len, const unsigned char *data);
void algRC4(T_ALG_RC4Key *key, unsigned int len, const unsigned char *indata,unsigned char *outdata);
T_ALG_RSA *algRSANewMethod(void);
int algRSASetPubkey(T_ALG_RSA *rsa, unsigned char *n,int nl,unsigned char * e,int el);
int algRSAPubEncrypt(int flen, const unsigned char *from,unsigned char *to, T_ALG_RSA *rsa,int padding);
int algRSAPubDecrypt(int flen, const unsigned char *from,unsigned char *to, T_ALG_RSA *rsa,int padding);
void algRSAFree (T_ALG_RSA *r);
int algRandBytes(unsigned char *buf,int num);
int  algRandPseudoBytes(unsigned char *buf,int num);
void algRandSeed(const void *buf,int num);
void algRandAdd(const void *buf,int num,double entropy);
int  sslInitAlgCritSection(void);
void algInitLinkTable(void);

/** the flag dicate SSL is inited or not */
extern int galg_initFlag;

/**
 * function: init algorithm module
 * \param  none
 * \return  if succeed return ALG_SUCCEED, else return ALG_FAIL
 */
int NCCalg_Init(void);

/**
 * Compute the MD-5 hash of data
 * \param d(input)  the data to be hashed
 * \param n(input)  the length of input data
 * \param md   Buffer where to store the hashed value.
 * \return
 *   if succeed return the hashed value, else return NULL
 */
unsigned char *MD5_FORWAP(const unsigned char *d, unsigned int n, unsigned char *md);

/**
 * Compute the SHA-1 hash of data
 * \param data(input)  the data to be hashed
 * \param len(input)   the length of input data
 * \param md  Buffer where to store the hashed value.
 * \return
 *   if succeed return the hashed value, else return NULL
 */
unsigned char *SHA1(const unsigned char *data, unsigned int len, unsigned char *md);

#ifdef  __cplusplus
}
#endif

#endif
