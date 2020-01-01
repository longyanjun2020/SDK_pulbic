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

#ifndef _M32COMM_H_
#define _M32COMM_H_

#ifdef  _cplusplus
extern "C"{
#endif

/* big endian data */
#ifdef ALG_DATA_ORDER_IS_BIG_ENDIAN

#define ALG_HOST_C2l(c,l)   (l =(((unsigned int)(*((c)++)))<<24),       \
             l|=(((unsigned int)(*((c)++)))<<16),       \
             l|=(((unsigned int)(*((c)++)))<< 8),       \
             l|=(((unsigned int)(*((c)++)))    ))

/* n presents how many bytes in i */
#define ALG_HOST_P_C2l(c,l,n)   {                   \
            switch (n) {                    \
            case 0: l =((unsigned int)(*((c)++)))<<24;  \
            case 1: l|=((unsigned int)(*((c)++)))<<16;  \
            case 2: l|=((unsigned int)(*((c)++)))<< 8;  \
            case 3: l|=((unsigned int)(*((c)++)));      \
                } }

#define ALG_HOST_P_C2l_P(c,l,sc,len) {                  \
            switch (sc) {                   \
            case 0: l =((unsigned int)(*((c)++)))<<24;  \
                if (--len == 0) break;          \
            case 1: l|=((unsigned int)(*((c)++)))<<16;  \
                if (--len == 0) break;          \
            case 2: l|=((unsigned int)(*((c)++)))<< 8;  \
                } }

/* NOTE the pointer is not incremented at the end of this */
#define ALG_HOST_C2l_P(c,l,n)   {                   \
            l=0; (c)+=n;                    \
            switch (n) {                    \
            case 3: l =((unsigned int)(*(--(c))))<< 8;  \
            case 2: l|=((unsigned int)(*(--(c))))<<16;  \
            case 1: l|=((unsigned int)(*(--(c))))<<24;  \
                } }
#define ALG_HOST_L2C(l,c)   (*((c)++)=(unsigned char)(((l)>>24)&0xff),  \
             *((c)++)=(unsigned char)(((l)>>16)&0xff),  \
             *((c)++)=(unsigned char)(((l)>> 8)&0xff),  \
             *((c)++)=(unsigned char)(((l)    )&0xff))

#else
#ifdef ALG_DATA_ORDER_IS_LITTLE_ENDIAN /* little endian data */
#define ALG_HOST_C2l(c,l)   (l =(((unsigned int)(*((c)++)))    ),       \
             l|=(((unsigned int)(*((c)++)))<< 8),       \
             l|=(((unsigned int)(*((c)++)))<<16),       \
             l|=(((unsigned int)(*((c)++)))<<24))

#define ALG_HOST_P_C2l(c,l,n)   {                   \
            switch (n) {                    \
            case 0: l =((unsigned int)(*((c)++)));      \
            case 1: l|=((unsigned int)(*((c)++)))<< 8;  \
            case 2: l|=((unsigned int)(*((c)++)))<<16;  \
            case 3: l|=((unsigned int)(*((c)++)))<<24;  \
                } }

#define ALG_HOST_P_C2l_P(c,l,sc,len) {                  \
            switch (sc) {                   \
            case 0: l =((unsigned int)(*((c)++)));      \
                if (--len == 0) break;          \
            case 1: l|=((unsigned int)(*((c)++)))<< 8;  \
                if (--len == 0) break;          \
            case 2: l|=((unsigned int)(*((c)++)))<<16;  \
                } }

/* NOTE the pointer is not incremented at the end of this */
#define ALG_HOST_C2l_P(c,l,n)   {                   \
            l=0; (c)+=n;                    \
            switch (n) {                    \
            case 3: l =((unsigned int)(*(--(c))))<<16;  \
            case 2: l|=((unsigned int)(*(--(c))))<< 8;  \
            case 1: l|=((unsigned int)(*(--(c))));      \
                } }
#define ALG_HOST_L2C(l,c)   (*((c)++)=(unsigned char)(((l)    )&0xff),  \
             *((c)++)=(unsigned char)(((l)>> 8)&0xff),  \
             *((c)++)=(unsigned char)(((l)>>16)&0xff),  \
             *((c)++)=(unsigned char)(((l)>>24)&0xff))

#endif
#endif

#define ROTATE(a,n)     (((a)<<(n))|(((a)&0xffffffff)>>(32-(n))))

#ifdef _cplusplus
}
#endif

#endif/*_M32COMM_H_*/
