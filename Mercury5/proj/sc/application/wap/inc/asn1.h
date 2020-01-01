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

/* @(#) $Id: //depot/dev/base/libs/openssl/crypto/asn1/asn1.h#2 $*/

#ifndef _D_ASN1_H
#define _D_ASN1_H

#ifdef  __cplusplus
extern "C" {
#endif

/** asn.1 constructions define */
#define CERT_ASN1_SEQUENCE          0x30  /**< SEQUENCE */
#define CERT_ASN1_SET               0x31  /**< SET */

/** x.509 certificate versiion define */
#define CERT_ASN1_CONTEXT_0         0xa0  /**< illegal versiion */
#define CERT_ASN1_CONTEXT_1         0xa1  /**< version 1 */
#define CERT_ASN1_CONTEXT_2         0xa2  /**< version 2 */
#define CERT_ASN1_CONTEXT_3         0xa3  /**< version 3 */

/** asn.1 primitive objects define */
#define CERT_ASN1_BOOLEAN           1     /**< BOOLEAN */
#define CERT_ASN1_INTEGER           2     /**< INTEGER */
#define CERT_DSSLSt_ASN1_BIT_STRING 3     /**< BIT STRING */
#define CERT_ASN1_OCTET_STRING      4     /**< OCTET STRING */
#define CERT_ASN1_NULL              5     /**< NULL */
#define CERT_ASN1_OBJID             6     /**< OBJECT IDETIFIER */
#define CERT_ASN1_UTF8STRING        12    /**< UTF8Sring */
#define CERT_ASN1_NUMERICSTRING     18    /**< NumericSring */
#define CERT_ASN1_PRINTABLESTRING   19    /**< PrintableString */
#define CERT_ASN1_T61STRING         20    /**< T61String */
#define CERT_ASN1_TELETEXSTRING     20    /**< TeletexString */
#define CERT_ASN1_VIDEOTEXSTRING    21    /**< VideotexString */
#define CERT_ASN1_IA5STRING         22    /**< IA5String */
#define CERT_ASN1_GRAPHICSTRING     25    /**< GraphicString */
#define CERT_ASN1_ISO64STRING       26    /**< ISO64String */
#define CERT_ASN1_VISIBLESTRING     26    /**< VisibleString */
#define CERT_ASN1_GENERALSTRING     27    /**< GeneralString */
#define CERT_ASN1_UNIVERSALSTRING   28    /**< UniversalString */
#define CERT_ASN1_BMPSTRING         30    /**< BMPString */
#define CERT_ASN_LONG_LEN           0x80  /**< long len */
#define CERT_ASN1_BIG_TAG           0x1f  /**< big tag */

int certAsn1ParseHeader(unsigned char **pc,unsigned int *length,unsigned int *type, unsigned int *part_len);
int certAsn1ParseInt(unsigned char **pc,unsigned int *len,char *value,unsigned int *val_len);
int certAsn1ParseObjId(unsigned char **pc,unsigned int *len,char *objid,unsigned int *id_len);
int certAsn1ParseString(unsigned char **pc,unsigned int *len,char *value,unsigned int *val_len);
int certAsn1ParseBool(unsigned char **pc,unsigned int *len,char *value);
int certAsn1ParseAny(unsigned char **pc,unsigned int *len,char *value,unsigned int *val_len);
int certAsn1ParseBitString(unsigned char **pc,unsigned int *len,char *value,unsigned int *val_len,char *left);

#ifdef  __cplusplus
}
#endif


#endif /*_D_ASN1_H*/

