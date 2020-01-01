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

#ifndef _X509_OBJ_H
#define _X509_OBJ_H
#include <stdio.h>
#include <string.h>
#include <bnst.h>
#include <alg_module.h>
#include <alg_enc.h>
#include <asn1.h>

#ifdef  __cplusplus
extern "C" {
#endif

/// distinguished name
#define CERT_X509_DN_countryName 1
#define CERT_X509_DN_organizationName 2
#define CERT_X509_DN_organizationalUnitName 3
#define CERT_X509_DN_dnQualifier 4
#define CERT_X509_DN_stateOrProvinceName 5
#define CERT_X509_DN_commonName 6
#define CERT_X509_DN_serialNumber 7
#define CERT_X509_DN_localityName 8
#define CERT_X509_DN_title 9
#define CERT_X509_DN_surname 10
#define CERT_X509_DN_givenName 11
#define CERT_X509_DN_initials 12
#define CERT_X509_DN_pseudonym 13
#define CERT_X509_DN_generationQualifier 14
#define CERT_X509_DN_emailAddress 15
#define CERT_X509_DN_unstructuredName 16
#define CERT_X509_DN_contentType 17
#define CERT_X509_DN_messageDigest 18
#define CERT_X509_DN_signingTime 19
#define CERT_X509_DN_countersignature 20
#define CERT_X509_DN_postalcode   21
#define CERT_X509_DN_streetname   22
#define CERT_X509_DN_domainComponet 23
#define CERT_X509_DN_country  24
#define CERT_X509_DN_state  25
#define CERT_X509_DN_city  26
#define CERT_X509_DN_businessCategory 27


/// public key
#define CERT_X509_PKEY_rsaEncryption 1

/// the x.509 object id context
typedef struct
{
    char *description;  /**< the object's description define in x.509 certificate */
    char *objid;        /**< the object id defined in x.509 certificate */
    int magic;        /**< the object id defined in SSL */
}T_CERT_X509ObjIdPf;

///  the x.509 signature algorithms SSL supports
extern const T_CERT_X509ObjIdPf gX509_SigObjidPfs[];

///  the x.509 distinguished name object SSL supports
extern const T_CERT_X509ObjIdPf gX509_DnObjidPfs[];

/// find objid in pfs
const T_CERT_X509ObjIdPf *certFindPf(const T_CERT_X509ObjIdPf *pfs,char *objid);

int certX509Asn1ParseAlgorId( unsigned char **encode,
                                  unsigned int *encode_len,
                                  T_CERT_AlgOrId *buf,
                                  unsigned int *len,
                                  char *ex_data);

#ifdef  __cplusplus
}
#endif

#endif /*_X509_OBJ_H*/
