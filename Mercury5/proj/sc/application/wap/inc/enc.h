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

#ifndef _ENC_H
#define _ENC_H
//#include <stdio.h>
#include "bnst.h"
#include "alg_module.h"
#include "alg_enc.h"
#ifdef _cplusplus
extern "C"{
#endif

#define ALG_B64_EOLN        0xF0
#define ALG_B64_CR          0xF1
#define ALG_B64_EOF         0xF2
#define ALG_B64_WS          0xE0
#define ALG_B64_ERROR       0xFF
#define ALG_B64_NOT_BASE64(a)         (((a)|0x13) == 0xF3)
#define ALG_dENC_MD_CTX_FLAG_CLEANED  0x0002 /* context has already been cleaned */
#define ALG_MD_SIZE                   (16+20) /* The SSLv3 md5+sha1 type */
#define ENC_MAX_KEY_LENGTH            32
#define ALG_ENC_MAX_IV_LENGTH         16
#define ALG_ENC_MAX_BLOCK_LENGTH      32
#define ALG_dENC_PKEY_RSA             6
#define ALG_dENC_PKEY_RSA2           19
#define ALG_CIPHER_CTX_KEY_LEN(e)   ((e)->key_len)
#define ALG_CIPHER_CTX_IV_LEN(e)    ((e)->cipher->iv_len)
#define ALG_CIPHER_CTX_FLAGS(e)     ((e)->cipher->flags)
#define ALG_CIPHER_CTX_MODE(e)           ((e)->cipher->flags & 0x07)
#define ALG_MD_CTX_SET_FLAGS(ctx,flgs)   ((ctx)->flags|=(flgs))
#define ALG_MD_CTX_CLEAR_FLAGS(ctx,flgs) ((ctx)->flags&=~(flgs))
#define ALG_MD_CTX_TEST_FLAGS(ctx,flgs)   ((ctx)->flags&(flgs))
#define ALG_PKEY_RSA_method NULL,NULL, {ALG_dENC_PKEY_RSA,ALG_dENC_PKEY_RSA2,0,0}
#define ALG_ENC_RC4_KEY_SIZE    16
#define ALG_ENC_DES_KEY_SIZE    8 /*bytes*/

#ifndef T_CHARSET_EBCDIC
#define ALG_CONV_BIN2ASCII(a)   (dataBinToAscii[(a)&0x3f])
#define ALG_CONV_ASCII2BIN(a)   (dataAsciiToBin[(a)&0x7f])
#else
/* We assume that PEM encoded files are EBCDIC files
 * (i.e., printable text files). Convert them here while decoding.
 * When encoding, output is EBCDIC (text) format again.
 * (No need for conversion in the ALG_CONV_BIN2ASCII macro, as the
 * underlying textstring dataBinToAscii[] is already EBCDIC)
 */
#define ALG_CONV_BIN2ASCII(a)   (dataBinToAscii[(a)&0x3f])
#define ALG_CONV_ASCII2BIN(a)   (dataAsciiToBin[os_toascii[a]&0x7f])
#endif

T_ALG_Cipher *algGetCipher(unsigned int ID);
T_ALG_Md *algGetMd(unsigned int ID);
void algInitLinkTable(void);

#ifdef _cplusplus
}
#endif

#endif
