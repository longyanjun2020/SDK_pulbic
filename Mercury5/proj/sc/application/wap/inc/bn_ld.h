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

/* @(#) $Id: //depot/dev/base/libs/openssl/crypto/bn/bn_ld.h#2 $*/

#ifndef HEADER_BN_LCL_H
#define HEADER_BN_LCL_H

#ifdef  __cplusplus
extern "C" {
#endif

#define ALG_BN_CTX_NUM  32
#define ALG_BN_CTX_NUM_POS  12
#define ALG_BN_MULL_SIZE_NORMAL               (16)
#define ALG_BN_MUL_RECURSIVE_SIZE_NORMAL      (16)
#define ALG_BN_SQR_RECURSIVE_SIZE_NORMAL      (16)
#define ALG_LW(t)    (((unsigned int)(t))&ALG_BN_MASK2)
#define ALG_HW(t)    (((unsigned int)((t)>>ALG_BN_BITS2))&ALG_BN_MASK2)

#define ALG_BN_WINDOW_BITS_FOR_EXPPOENT_SIZE(b) \
        ((b) > 671 ? 6 : \
         (b) > 239 ? 5 : \
         (b) >  79 ? 4 : \
         (b) >  23 ? 3 : 1)

#ifdef BN_LLONG
#define ALG_MUL_ADD(r,a,w,c) { \
    BN_ULLONG t; \
    t=(BN_ULLONG)w * (a) + (r) + (c); \
    (r)= ALG_LW(t); \
    (c)= ALG_HW(t); \
    }

#define ALG_MUL(r,a,w,c) { \
    BN_ULLONG t; \
    t=(BN_ULLONG)w * (a) + (c); \
    (r)= ALG_LW(t); \
    (c)= ALG_HW(t); \
    }

#define ALG_SQR(r0,r1,a) { \
    BN_ULLONG t; \
    t=(BN_ULLONG)(a)*(a); \
    (r0)=ALG_LW(t); \
    (r1)=ALG_HW(t); \
    }

#elif defined(BN_UMULT_HIGH)
#define ALG_MUL_ADD(r,a,w,c) {      \
    unsigned int high,low,ret,tmp=(a);  \
    ret =  (r);         \
    high=  BN_UMULT_HIGH(w,tmp);    \
    ret += (c);         \
    low =  (w) * tmp;       \
    (c) =  (ret<(c))?1:0;       \
    (c) += high;            \
    ret += low;         \
    (c) += (ret<low)?1:0;       \
    (r) =  ret;         \
    }

#define ALG_MUL(r,a,w,c)    {       \
    unsigned int high,low,ret,ta=(a);   \
    low =  (w) * ta;        \
    high=  BN_UMULT_HIGH(w,ta); \
    ret =  low + (c);       \
    (c) =  high;            \
    (c) += (ret<low)?1:0;       \
    (r) =  ret;         \
    }

#define ALG_SQR(r0,r1,a)    {       \
    unsigned int tmp=(a);       \
    (r0) = tmp * tmp;       \
    (r1) = BN_UMULT_HIGH(tmp,tmp);  \
    }

#else
/*************************************************************
 * No int int type */
#define ALG_LBITS(a)    ((a)&ALG_BN_MASK2l)
#define ALG_HBITS(a)    (((a)>>ALG_BN_BITS4)&ALG_BN_MASK2l)
#define ALG_L2HBITS(a)  (((a)<<ALG_BN_BITS4)&ALG_BN_MASK2)

#define ALG_MUL64(l,h,bl,bh) \
    { \
    unsigned int m,m1,lt,ht; \
 \
    lt=l; \
    ht=h; \
    m =(bh)*(lt); \
    lt=(bl)*(lt); \
    m1=(bl)*(ht); \
    ht =(bh)*(ht); \
    m=(m+m1)&ALG_BN_MASK2; if (m < m1) ht+=ALG_L2HBITS((unsigned int)1); \
    ht+=ALG_HBITS(m); \
    m1=ALG_L2HBITS(m); \
    lt=(lt+m1)&ALG_BN_MASK2; if (lt < m1) ht++; \
    (l)=lt; \
    (h)=ht; \
    }

#define ALG_SQR64(lo,ho,in) \
    { \
    unsigned int l,h,m; \
 \
    h=(in); \
    l=ALG_LBITS(h); \
    h=ALG_HBITS(h); \
    m =(l)*(h); \
    l*=l; \
    h*=h; \
    h+=(m&ALG_BN_MASK2h1)>>(ALG_BN_BITS4-1); \
    m =(m&ALG_BN_MASK2l)<<(ALG_BN_BITS4+1); \
    l=(l+m)&ALG_BN_MASK2; if (l < m) h++; \
    (lo)=l; \
    (ho)=h; \
    }

#define ALG_MUL_ADD(r,a,bl,bh,c) { \
    unsigned int l,h; \
 \
    h= (a); \
    l=ALG_LBITS(h); \
    h=ALG_HBITS(h); \
    ALG_MUL64(l,h,(bl),(bh)); \
 \
    /* non-multiply part */ \
    l=(l+(c))&ALG_BN_MASK2; if (l < (c)) h++; \
    (c)=(r); \
    l=(l+(c))&ALG_BN_MASK2; if (l < (c)) h++; \
    (c)=h&ALG_BN_MASK2; \
    (r)=l; \
    }

#define ALG_MUL(r,a,bl,bh,c) { \
    unsigned int l,h; \
 \
    h= (a); \
    l=ALG_LBITS(h); \
    h=ALG_HBITS(h); \
    ALG_MUL64(l,h,(bl),(bh)); \
 \
    /* non-multiply part */ \
    l+=(c); if ((l&ALG_BN_MASK2) < (c)) h++; \
    (c)=h&ALG_BN_MASK2; \
    (r)=l&ALG_BN_MASK2; \
    }
#endif /* !BN_LLONG */


struct bignum_ctx
{
    int tos;
    T_ALG_BigNum bn[ALG_BN_CTX_NUM];
    int flags;
    int depth;
    int pos[ALG_BN_CTX_NUM_POS];
    int too_many;
} ;

void DSSLFn_BN_sqr_comba8(unsigned int *r,const unsigned int *a);
void DSSLFn_BN_sqr_comba4(unsigned int *r,const unsigned int *a);
int algBNCmpWords(const unsigned int *a,const unsigned int *b,int n);
void algBNSqrRecursive(unsigned int *r,const unsigned int *a, int n2, unsigned int *t);
void algBNSqrNormal(unsigned int *r, const unsigned int *a, int n, unsigned int *tmp);


#ifdef  __cplusplus
}
#endif

#endif
