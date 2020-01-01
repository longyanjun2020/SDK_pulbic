/*
 * TLSv1 credentials
 * Copyright (c) 2006-2007, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#ifndef AKM_CRED_H
#define AKM_CRED_H

#define WAPI_ECC_KEY_LEN            24

struct akm_credentials {
	struct x509_certificate *trusted_certs;
	struct x509_certificate *cert;
	u8 pri_key[WAPI_ECC_KEY_LEN];
};

#if 1 //kc
#define CERT_TIME_Z_LEN 15 //GeneralizedTime: YYYYMMDDHHMMSSZ

#define CERT_STS_X509_TIME_EXPIRED               (1 << 0)
#define CERT_STS_X509_FORMAT_ERROR               (1 << 1)
#define CERT_STS_X509_AS_CERT_PEM                (1 << 2)
#define CERT_STS_X509_CLIENT_CERT_PEM            (1 << 3)
#define CERT_STS_X509_CLIENT_PRIKEY_PEM          (1 << 4)
#define CERT_STS_X509_FILEOP_ERROR               (1 << 5)

#define CERT_STS_X509_V1                         (1 << 16)
#define CERT_STS_X509_V2                         (1 << 17)
#define CERT_STS_X509_V3                         (1 << 18)

struct akm_cert_info {
    /* 
     *  #define CERT_STS_X509_TIME_EXPIRED               (1 << 0)
     *  #define CERT_STS_X509_FORMAT_ERROR               (1 << 1)
     *  #define CERT_STS_X509_AS_CERT_PEM                (1 << 2)
     *  #define CERT_STS_X509_CLIENT_CERT_PEM            (1 << 3)
     *  #define CERT_STS_X509_CLIENT_PRIKEY_PEM          (1 << 4)
     *  #define CERT_STS_X509_FILEOP_ERROR               (1 << 5)
     *  #define CERT_STS_X509_V1                         (1 << 16)
     *  #define CERT_STS_X509_V2                         (1 << 17)
     *  #define CERT_STS_X509_V3                         (1 << 18)
     */
    unsigned long       status;
    struct x509_name    issuer;
    struct x509_name    subject;
    unsigned long       serial_number;
    u8                  not_before[CERT_TIME_Z_LEN];
    u8                  not_after[CERT_TIME_Z_LEN];
} STRUCT_PACKED;


#define CERT_STORE_IN_FILE          0x0000
#define CERT_STORE_IN_RAI           0x0001

typedef struct {
    u16 *wszFilePath;
    u16 nLen;
} cert_source_file_t;

typedef struct {
    u32 nRaiId;
    u32 nSize;
} cert_source_rai_t;

typedef struct {
    u32 type;
    union {
        cert_source_file_t tFile;
        cert_source_rai_t  tRai;
    } cert_source;
} cert_storage_t;

int  akm_cert_parser(cert_storage_t *fpath, struct akm_cert_info *cert_i);
void akm_cert_free(struct akm_cert_info *cert_i);
#endif

struct akm_credentials * akm_cred_alloc(void);
void akm_cred_free(struct akm_credentials *cred);
int akm_set_ca_cert(struct akm_credentials *cred, const char *cert,
		      const u8 *cert_blob, size_t cert_blob_len,
		      const char *path);
int akm_set_cert(struct akm_credentials *cred, const char *cert,
		   const u8 *cert_blob, size_t cert_blob_len);
int akm_set_private_key(struct akm_credentials *cred,
              const char *private_key,
              const char *private_key_passwd,
              const u8 *private_key_blob,
              size_t private_key_blob_len);


#endif /* TLSV1_CRED_H */
