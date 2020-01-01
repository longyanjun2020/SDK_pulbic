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

/* @(#) $Id: //depot/dev/base/libs/openssl/crypto/bn/bn.h#3 $*/

#ifndef HEADER_BN_H
#define HEADER_BN_H
#include <stdio.h>
#include <string.h>
#ifdef  __cplusplus
extern "C" {
#endif

#define ALG_BN_MUL_COMBA
#define ALG_BN_RECURSION

#ifdef DSSLFn_SSLSYS_WIN32
    #ifndef ALG_BN_DIV2W
        #define ALG_BN_DIV2W
    #endif
#endif

#ifdef T_ALG_BigNum
    #undef T_ALG_BigNum
#endif

#define ALG_BN_FLG_MALLOCED     0x01
#define ALG_BN_FLG_STATIC_DATA  0x02
#define ALG_BN_FLG_FREE         0x8000  /* used for debuging */
#define ALG_BN_GET_FLAGS(b,n)   ((b)->flags&(n))
#define ALG_BN_NUM_BYTES(a)     ((algBNNumBits(a)+7)/8)
#define ALG_BN_ABS_IS_WORD(a,w) (((a)->top == 1) && ((a)->d[0] == (unsigned int)(w)))
#define ALG_BN_IS_ZERO(a)       (((a)->top == 0) || ALG_BN_ABS_IS_WORD(a,0))
#define ALG_BN_IS_ONE(a)        (ALG_BN_ABS_IS_WORD((a),1) && !(a)->neg)
#define ALG_BN_IS_WORD(a,w)     ((w) ? ALG_BN_ABS_IS_WORD((a),(w)) && !(a)->neg : ALG_BN_IS_ZERO((a)))
#define ALG_BN_IS_ODD(a)        (((a)->top > 0) && ((a)->d[0] & 1))
#define ALG_BN_ONE(a)           (algBNSetWord((a),1))
#define ALG_BN_ZERO(a)          (algBNSetWord((a),0))
#define DSSLFn_BN_MOD(rem,m,d,ctx) algBNDiv(NULL,(rem),(m),(d),(ctx))
#define DSSLFn_BN_TO_MONTGOMERY(r,a,mont,ctx)   algBNModMulMontgomery((r),(a),&((mont)->RR),(mont),(ctx))
#define DSSLFn_BN_EXPAND(a,bits)   ((((((bits+ALG_BN_BITS2-1))/ALG_BN_BITS2)) <= (a)->dmax)?(a):algBNExpand2((a),(bits)/ALG_BN_BITS2+1))

#define ALG_DSSLFn_BN_FIX_TOP(a) \
 { \
        unsigned int *ftl; \
    if ((a)->top > 0) \
    { \
        for (ftl = &((a)->d[(a)->top-1]); (a)->top > 0; (a)->top--) \
        if (*(ftl--)) break; \
    } \
}

typedef struct bignum_ctx T_ALG_BN_CTX ;

T_ALG_BigNum *DSSLFn_BN_WEXPAND(T_ALG_BigNum *a,int words);
const T_ALG_BigNum *algBNValueOne(void);
T_ALG_BN_CTX *algBNCtxNew(void);
void    algBNCtxFree(T_ALG_BN_CTX *c);
void    algBNCtxStart(T_ALG_BN_CTX *ctx);
T_ALG_BigNum *algBNCtxGet(T_ALG_BN_CTX *ctx);
void    algBNCtxEnd(T_ALG_BN_CTX *ctx);
int algBNNumBits(const T_ALG_BigNum *a);
int algBNNumBitsWord(unsigned int);
T_ALG_BigNum *algBNNew(void);
void algBNInit(T_ALG_BigNum *);
void algBNClearFree(T_ALG_BigNum *a);
T_ALG_BigNum *algBNCopy(T_ALG_BigNum *a, const T_ALG_BigNum *b);
T_ALG_BigNum *algBNBinToBn(const unsigned char *s,int len,T_ALG_BigNum *ret);
int algBNBnToBin(const T_ALG_BigNum *a, unsigned char *to);
int algBNSub(T_ALG_BigNum *r, const T_ALG_BigNum *a, const T_ALG_BigNum *b);
int algBNUSub(T_ALG_BigNum *r, const T_ALG_BigNum *a, const T_ALG_BigNum *b);
int algBNUAdd(T_ALG_BigNum *r, const T_ALG_BigNum *a, const T_ALG_BigNum *b);
int algBNAdd(T_ALG_BigNum *r, const T_ALG_BigNum *a, const T_ALG_BigNum *b);
int algBNMul(T_ALG_BigNum *r, const T_ALG_BigNum *a, const T_ALG_BigNum *b, T_ALG_BN_CTX *ctx);
int algBNSqr(T_ALG_BigNum *r, const T_ALG_BigNum *a,T_ALG_BN_CTX *ctx);
int algBNDiv(T_ALG_BigNum *dv, T_ALG_BigNum *rem, const T_ALG_BigNum *m, const T_ALG_BigNum *d,T_ALG_BN_CTX *ctx);
int algBNNnMod(T_ALG_BigNum *r, const T_ALG_BigNum *m, const T_ALG_BigNum *d, T_ALG_BN_CTX *ctx);
unsigned int DSSLFn_BN_div_word(T_ALG_BigNum *a, unsigned int w);
int algBNMulWord(T_ALG_BigNum *a, unsigned int w);
int algBNSubWord(T_ALG_BigNum *a, unsigned int w);
int algBNSetWord(T_ALG_BigNum *a, unsigned int w);
void algBNFree(T_ALG_BigNum *a);
int algBNIsBitSet(const T_ALG_BigNum *a, int n);
int algBNLeftShift2(T_ALG_BigNum *r, const T_ALG_BigNum *a, int n);
int algBNLeftShift1(T_ALG_BigNum *r, const T_ALG_BigNum *a);
int algBNModExpMont(T_ALG_BigNum *r, const T_ALG_BigNum *a, const T_ALG_BigNum *p,const T_ALG_BigNum *m, T_ALG_BN_CTX *ctx, T_ALG_BnMontCtx *m_ctx);
int algBNMaskBits(T_ALG_BigNum *a,int n);
int DSSLFn_BN_reciprocal(T_ALG_BigNum *r, const T_ALG_BigNum *m, int len, T_ALG_BN_CTX *ctx);
int algBNRightShift(T_ALG_BigNum *r, const T_ALG_BigNum *a, int n);
int algBNRightShift1(T_ALG_BigNum *r, const T_ALG_BigNum *a);
int algBNUnsignCmp(const T_ALG_BigNum *a, const T_ALG_BigNum *b);
int algBNSetBit(T_ALG_BigNum *a, int n);
T_ALG_BnMontCtx *algBNMontCtxNew(void );
int algBNModMulMontgomery(T_ALG_BigNum *r,const T_ALG_BigNum *a,const T_ALG_BigNum *b,T_ALG_BnMontCtx *mont, T_ALG_BN_CTX *ctx);
int algBNFromMontgomery(T_ALG_BigNum *r,const T_ALG_BigNum *a,T_ALG_BnMontCtx *mont, T_ALG_BN_CTX *ctx);
void algBNMontCtxFree(T_ALG_BnMontCtx *mont);
int algBNMontCtxSet(T_ALG_BnMontCtx *mont,const T_ALG_BigNum *mod,T_ALG_BN_CTX *ctx);
T_ALG_BigNum *algBNExpand2(T_ALG_BigNum *a, int words);
/* big number API */
unsigned int algBNMulAddWords(unsigned int *rp, const unsigned int *ap, int num, unsigned int w);
unsigned int algBNMulWords(unsigned int *rp, const unsigned int *ap, int num, unsigned int w);
void algBNSqrWords(unsigned int *rp, const unsigned int *ap, int num);
unsigned int algBNAddWords(unsigned int *rp, const unsigned int *ap, const unsigned int *bp,int num);
unsigned int algBNSubWords(unsigned int *rp, const unsigned int *ap, const unsigned int *bp,int num);
void algBNMulComba8(unsigned int *r,unsigned int *a,unsigned int *b);
void algBNMulComba4(unsigned int *r,unsigned int *a,unsigned int *b);

#ifdef  __cplusplus
}
#endif

#endif
