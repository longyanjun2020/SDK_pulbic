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

#ifndef ENC_H
#define ENC_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <alg_module.h>

#define ALG_ENC_MAX_IV_LENGTH       16  /**< max iv length in encryption*/
#define ALG_ENC_MAX_BLOCK_LENGTH    32  /**< max block len in encryption */

/** alogrithm id define */
#define ALG_ENC_EMPTY_ID            0       /**< the empty alogrithm id */
#define ALG_ENC_RC4_ID              500     /**< the id of 128 bit RC4 alogrithm */
#define ALG_ENC_MD2_ID              600     /**< the id of MD2 alogrithm */
#define ALG_ENC_MD5_ID              601     /**< the id of MD5 alogrithm */
#define ALG_ENC_SHA1_ID             602     /**< the id of SHA1 alogrithm */

/** public key type */
#define ALG_dENC_PKEY_RSA   6    /**< RSA */
#define ALG_dENC_PKEY_RSA2  19   /**< RSA2 */

/** encryption mode */
#define ALG_ENC_CIPH_STREAM_CIPHER      0x0  /**< stream mode */
#define ALG_ENC_CIPH_ECB_MODE           0x1  /**< ECB mode */
#define ALG_ENC_CIPH_CBC_MODE           0x2  /**< CBC mode */
#define ALG_ENC_CIPH_CFB_MODE           0x3  /**< CFB mode */
#define ALG_ENC_CIPH_OFB_MODE           0x4  /**< OFB mode */

#define ALG_ENC_CIPH_VARIABLE_LENGTH    0x8   /**< Set if variable length cipher */
#define ALG_ENC_CIPH_CUSTOM_IV          0x10  /**< Set if the iv handling should be done by the cipher itself */
#define ALG_ENC_CIPH_ALWAYS_CALL_INIT   0x20  /**< Set if the cipher's init() function should be called if key is NULL */

/** the symmetric cryptograpy context definition */
typedef struct
{
    const struct cipher_st *cipher;
    int encrypt;
    int buf_len;
    unsigned char oiv[ALG_ENC_MAX_IV_LENGTH];
    unsigned char iv[ALG_ENC_MAX_IV_LENGTH];
    unsigned char buf[ALG_ENC_MAX_BLOCK_LENGTH];
    int key_len;
    void *cipher_data;
    int final_used;
    int block_mask;
    unsigned char final[ALG_ENC_MAX_BLOCK_LENGTH];
}T_ALG_CipherCtx;

/* the symmetric method definition */
typedef struct cipher_st
{
    T_SSL_Node node;    /**< the node for insert to cipher list */
    unsigned int nid;       /**< the id of this cipher */
    unsigned int block_size; /**< the size of block data */
    int key_len;    /**< the length of key */
    int iv_len;     /**< the length of iv */
    unsigned int flags;     /**< the flag of this cipher */
    void (*init)(T_ALG_CipherCtx *ctx, const unsigned char *key);  /**< the function to init this struct */
    void (*do_cipher)(T_ALG_CipherCtx *ctx, unsigned char *out,const unsigned char *in, unsigned int inl);  /***< the function to encrypt data */
    int ctx_size;  /**< the size of this struct */
}T_ALG_Cipher;

/** the md cryptograpy context definition */
typedef struct
{
    const struct md_st *digest;  /**< the md struct */
    void *md_data;   /**< the md data */
}T_ALG_MdCtx ;

/** the md cryptograpy method definition */
typedef struct md_st
{
    T_SSL_Node node;   /**< the node for insert to md list */
    unsigned int md_type;  /**< the type of md */
    int md_size;   /**< the size of md */
    void (*init)(T_ALG_MdCtx *ctx); /**< the function to init this struct */
    void (*update)(T_ALG_MdCtx *ctx,const void *data,unsigned int count);  /**< the function to compute hash value of block data */
    void (*final)(T_ALG_MdCtx *ctx,unsigned char *md);  /**< the function to coumpute the hash value of laat block data */
    int block_size; /**< the size of block data */
    int ctx_size;   /**< the size of this struct */
}T_ALG_Md;

/** the asn.1 <--> base64 convert for certificate context */
typedef struct
{
    int num;
    int length;
    int line_num;
    int expect_nl;
    unsigned char enc_data[80];  /**< the data to be encoded */
}T_ALG_EncodeCtx;

/** the public key in server certificate definition */
typedef struct
{
    union
    {
       char    *ptr;  /**< the data of public key */
       T_ALG_RSA *rsa;  /**< RSA alogrithm */
    } pkey;
}T_ALG_PubKey;


int algEncCipherInit(T_ALG_CipherCtx *ctx, const unsigned int ID,const unsigned char *key, const unsigned char *iv, int enc);
int DSSLFn_ENC_EncryptInit(T_ALG_CipherCtx *ctx, unsigned int ID, unsigned char *key, unsigned char *iv);
int algEncryptUpdate(T_ALG_CipherCtx *ctx, unsigned char *out, int *outl, unsigned char *in, int inl);int algEncryptFinal(T_ALG_CipherCtx *ctx, unsigned char *out, int *outl);
int DSSLFn_ENC_DecryptInit(T_ALG_CipherCtx *ctx, unsigned int ID, unsigned char *key, unsigned char *iv);
int algDecryptUpdate(T_ALG_CipherCtx *ctx, unsigned char *out, int *outl, unsigned char *in, int inl);
int algDecryptFinal(T_ALG_CipherCtx *ctx, unsigned char *out, int *outl);
int algEncCipherCtxCleanup(T_ALG_CipherCtx *c);
int algMdCtxCopyEx(T_ALG_MdCtx *out, const T_ALG_MdCtx *in);
T_ALG_MdCtx *algMdCtxCreate(void);
int algDigestInit(T_ALG_MdCtx *ctx, unsigned int ID);
void algDigestUpdate(T_ALG_MdCtx *ctx, const void *data, unsigned int count);
int algDigestFinal(T_ALG_MdCtx *ctx, unsigned char *md,unsigned int *size);
void algMdCtxCleanup(T_ALG_MdCtx *ctx);
void algMdCtxDestroy(T_ALG_MdCtx *ctx);
void algEncodeInit(T_ALG_EncodeCtx *ctx);
void algEncodeUpdate (T_ALG_EncodeCtx *ctx,unsigned char *out,int *outl,unsigned char *in,int inl);
void algEncodeFinal(T_ALG_EncodeCtx *ctx,unsigned char *out,int *outl);
void algDecodeInit(T_ALG_EncodeCtx *ctx);
int algDecodeUpdate(T_ALG_EncodeCtx *ctx,unsigned char *out,int *outl,
unsigned char *in, int inl);
int algDecodeFinal(T_ALG_EncodeCtx *ctx, unsigned char *out, int *outl);
T_ALG_PubKey *algEncPkeyNew(void);
void algEncPkeyFree(T_ALG_PubKey *x);
int algEncPkeyAssign(T_ALG_PubKey *pkey,int type,char *key);
int algPubKEYEncrypt(unsigned char *ek,unsigned char *key,int key_len,T_ALG_PubKey *pubk);
void algEncCipherCtxInit(T_ALG_CipherCtx *ctx);


#ifdef  __cplusplus
}
#endif

#endif
