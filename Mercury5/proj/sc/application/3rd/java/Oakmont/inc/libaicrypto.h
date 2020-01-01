/*
 * Copyright (C) 1998-2002
 * Akira Iwata & Takuto Okuno
 * Akira Iwata Laboratory,
 * Nagoya Institute of Technology in Japan.
 *
 * All rights reserved.
 *
 * This software is written by Takuto Okuno(usapato@anet.ne.jp)
 * And if you want to contact us, send an email to Kimitake Wakayama
 * (wakayama@elcom.nitech.ac.jp)
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *	this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *	this list of conditions and the following disclaimer in the documentation
 *	and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software must
 *	display the following acknowledgment:
 *	"This product includes software developed by Akira Iwata Laboratory,
 *	Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *	acknowledgment:
 *	"This product includes software developed by Akira Iwata Laboratory,
 *	 Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 *
 *   THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *   AKIRA IWATA LABORATORY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 *   SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 *   IN NO EVENT SHALL AKIRA IWATA LABORATORY BE LIABLE FOR ANY SPECIAL,
 *   INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 *   FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *   WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef _LIBAICRYPTO_H
#define _LIBAICRYPTO_H

#include <stdio.h>
#include <time.h>

#ifdef  __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------*/
/*                                                          */
/*----------------------------------------------------------*/
#ifdef NDEBUG
#define AI_ASSERT(e)	((void)0)
#else
#include <assert.h>
#define AI_ASSERT(e)	assert(e)
#endif

/*----------------------------------------------------------*/
/* aiconfig.h                                               */
/*----------------------------------------------------------*/
#define ULONG  unsigned long
#ifdef __GNUC__
#define ULLONG unsigned long long
#elif defined(__ARMCC_VERSION)
#define ULLONG unsigned __int64
#else
#define ULLONG unsigned _int64
#endif

/*
 * acpi_fs.h
 */

typedef void * ACPI_FS_FILEPTR;

/*----------------------------------------------------------*/
/* md_global.h                                              */
/*----------------------------------------------------------*/
/* aicrypto_UINT4 defines a four byte word */
typedef unsigned long int aicrypto_UINT4;


/*----------------------------------------------------------*/
/* ok_md5.h                                                 */
/*----------------------------------------------------------*/
/* MD5 context. */
typedef struct{
  aicrypto_UINT4 state[4];                                   /* state (ABCD) */
  aicrypto_UINT4 count[2];        /* number of aicrypto_bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} aicrypto_MD5_CTX;


/*----------------------------------------------------------*/
/* ok_sha1.h                                                */
/*----------------------------------------------------------*/
typedef struct aicrypto_sha1_context{
  ULONG H[5];
  
  unsigned char	dat[64];
  int 	len;
  int	mod;
}aicrypto_SHA1_CTX;

void aicrypto_SHA1init(aicrypto_SHA1_CTX *ctx);
void aicrypto_SHA1update(aicrypto_SHA1_CTX *ctx, unsigned char *in, int len);
void aicrypto_SHA1final(unsigned char *ret,aicrypto_SHA1_CTX *ctx);



/*----------------------------------------------------------*/
/* ok_x509.h                                                */
/*----------------------------------------------------------*/
/* public or private key struct 
 *    base structure 
 */
typedef struct aicrypto_crypt_key{
	int key_type; /* key identifier */
	int size;

	/* type field */
}aicrypto_Key;

/*
 * the X.509 digital certificate structures
 */
typedef struct aicrypto_validity{
	int       notBeforeType;   /* UTC/Generalized */
	struct tm notBefore;
	int       notAfterType;    /* UTC/Generalized */
	struct tm notAfter;
}aicrypto_Validity;

typedef struct aicrypto_certificate_extension aicrypto_CertExt;
struct aicrypto_certificate_extension{
	int extnID;
	int critical;	/* boolean default false */
	unsigned char *objid;	/* if extnID==0, this has byte string value */

	int dlen;
	unsigned char *der;

	aicrypto_CertExt *next;
};

#define AICRYPTO_RDN_MAX		16

typedef struct aicrypto_certificate_dir{
	int num;
	struct aicrypto_cert_rdn{
		int  derform;
		int  tagoid;
		char *tag;
	} rdn[AICRYPTO_RDN_MAX];
}aicrypto_CertDN,aicrypto_CertDIR;

typedef struct aicrypto_x509_certificate{
	int version;
	int serialNumber;
	unsigned char *long_sn;	/* long serial number (usually NULL) */

	int	signature_algo;
	char	*issuer;
	aicrypto_CertDN	issuer_dn;

	aicrypto_Validity	time;

	char	*subject;
	aicrypto_CertDN	subject_dn;

	int	pubkey_algo;
	aicrypto_Key	*pubkey;

	long	issuerUniqueID;
	long	subjectUniqueID;

	aicrypto_CertExt	*ext;

	int	siglen;
	unsigned char	*signature;

	/* DER encode strings */
	unsigned char	*der;
}aicrypto_Cert,aicrypto_Req;


/* define verify error */
#define AICRYPTO_X509_VFY_ERR			0x0100
#define AICRYPTO_X509_VFY_ERR_SIGNATURE		0x0200
#define AICRYPTO_X509_VFY_ERR_SIGNATURE_CRL	0x0300
#define AICRYPTO_X509_VFY_ERR_NOTBEFORE		0x0400
#define AICRYPTO_X509_VFY_ERR_NOTAFTER		0x0500
#define AICRYPTO_X509_VFY_ERR_LASTUPDATE		0x0600
#define AICRYPTO_X509_VFY_ERR_NEXTUPDATE 	0x0700
#define AICRYPTO_X509_VFY_ERR_REVOKED		0x0a00
#define AICRYPTO_X509_VFY_ERR_SELF_SIGN		0x0b00
#define AICRYPTO_X509_VFY_ERR_CA_CHAIN		0x0c00
#define AICRYPTO_X509_VFY_ERR_SYSTEMERR		0x0d00

#define AICRYPTO_X509_VFY_ERR_NOT_CACERT		0x1000
#define AICRYPTO_X509_VFY_ERR_ISSUER_CRL		0x1100
#define AICRYPTO_X509_VFY_ERR_NOT_IN_CERTLIST	0x1200
#define AICRYPTO_X509_VFY_ERR_UNKOWN_SIG_ALGO	0x1300

/* define verify check type */
#define AICRYPTO_DONT_VERIFY			0x0080	/* don't verify anything, just return 0 */


/* x509_time.c */
unsigned char *aicrypto_stm2UTC(struct tm *stm,unsigned char *buf,unsigned char tag);

/* cert_print.c */
void aicrypto_Cert_print(aicrypto_Cert *ct);

/* cert_vfy.c */
int aicrypto_Cert_validity_verify(aicrypto_Cert *ct);
int aicrypto_Cert_signature_verify(aicrypto_Cert *ca,aicrypto_Cert *user);

/* cert_tool.c */
int aicrypto_Cert_dncmp(aicrypto_CertDN *d1,aicrypto_CertDN *d2);
int aicrypto_Cert_is_root(aicrypto_Cert *ct);


/*----------------------------------------------------------*/
/* ok_pkcs12.h                                              */
/*----------------------------------------------------------*/
/*---- aicrypto_PKCS12 Structures ----*/
typedef struct aicrypto_pkcs12_Bag_list aicrypto_P12_Baggage;
struct aicrypto_pkcs12_Bag_list{
	int		type;
	aicrypto_P12_Baggage	*next;

	unsigned char	*friendlyName;
	unsigned char	localKeyID[4];
};

typedef struct aicrypto_pkcs12{
	int		version;
	aicrypto_P12_Baggage	*bag;
	long		reserve;	/* (= NULL) this is just dummy for aicrypto_PKCS7 */
}aicrypto_PKCS12;

typedef struct aicrypto_pkcs12_BagID_CERT{
	int		type;
	aicrypto_P12_Baggage	*next;

	char	*friendlyName;
	char	localKeyID[4];

	aicrypto_Cert	*cert;

}aicrypto_P12_CertBag;

/* p12_tool.c */
int aicrypto_P12_max_depth(aicrypto_PKCS12 *p12,int type);
int aicrypto_P12_check_chain(aicrypto_PKCS12 *p12,int print);
aicrypto_Cert *aicrypto_P12_get_usercert(aicrypto_PKCS12 *p12);


/*----------------------------------------------------------*/
/* ok_pkcs7.h                                               */
/*----------------------------------------------------------*/
/*---- aicrypto_PKCS7 Structures ----*/
typedef struct aicrypto_PKCS7ContentInfo aicrypto_P7_Content;
struct aicrypto_PKCS7ContentInfo{ /* nomal data type */
	int		p7type;		/* use ASN.1 object id */

	int		size;
	unsigned char	*data;
};

typedef struct aicrypto_pkcs7{
  int		version;	/* it's not used in aicrypto_pkcs7 */
  aicrypto_P12_Baggage	*bag;	/* Certificates and CRLs */

  aicrypto_P7_Content	*cont;
  unsigned char	*der;
}aicrypto_PKCS7;

/* aicrypto_pkcs7.c */
void aicrypto_P7_free(aicrypto_PKCS7 *p7);

/* p7_file.c */
void aicrypto_P7_print(aicrypto_PKCS7 *p12);


/*----------------------------------------------------------*/
/* ok_store.h                                               */
/*----------------------------------------------------------*/
/*
 * Store Bags
 */
typedef struct aicrypto_store_bag aicrypto_CSBag;
struct aicrypto_store_bag{
	int ctx_type; /* bag context : cert, crl, key... */
	char *unique_id;   /* bag name (must be unique in a store) */

	aicrypto_CSBag *next;
	aicrypto_CSBag *prev;

	int status;
	int use_flag;

	int serialNumber;
	char *issuer;
	char *subject;

	int hlen;
	unsigned char key_hash[32];

	unsigned char *der;	/* cache of raw der */
	void *cache;	/* on memory cache : aicrypto_Cert*, aicrypto_CRL*, aicrypto_Key*... */
	void *dev_info;	/* device specific access information */
};


/*----------------------------------------------------------*/
/* ok_ssl.h                                                 */
/*----------------------------------------------------------*/
/*
 * aicrypto_SSL Record Layer
 */
typedef struct aicrypto_protocol_version{
	unsigned char major,minor;
}aicrypto_ProtocolVersion;

/*** Plain Text Struct ***/
typedef struct aicrypto_ssl_plain_text{
	unsigned int	type;	/* ContentType */
	unsigned int	length;	/* < 2^14 */

	/* this fragment doesn't have allocated memory.
	 * usually it points current buffer of procedure's buffer value.
	 * (i.e. the case of aicrypto_SSL_write(aicrypto_SSL*,void*,size_t), void* is taken)
	 */
	unsigned char	*fragment;	/* opaque [aicrypto_SSLPlaintext.length] */

}aicrypto_SSLPlaintext;

/*** Compressed Data Struct ***/
typedef aicrypto_SSLPlaintext	aicrypto_SSLCompressed;	/* same format */


/*** Cipher Text Struct ***/
typedef struct aicrypto_ssl_ciphertext{
	unsigned int	type;	/* ContentType */
	unsigned int	length;
	
	unsigned char	*fragment;

	/* these are cipher-fragment content */
	unsigned char	*content;		/* opaque [aicrypto_SSLCompressed.length] */
	unsigned char	MAC[32];		/* opaque [CipherSpec.aicrypto_hash_size] */
	unsigned char	padding[32];	/* [GenericBlockCipher.padding_length] */
	unsigned char	padding_length;
}aicrypto_SSLCiphertext;


/*
 * Cipher Spec
 */
typedef struct aicrypto_ssl_cipher_spec{
	int		bulk_cipher_algorithm;	/* current cipher (use OBJ_CRYALGO_* in ok_asn1.h) */
	int		mac_algorithm;		/* current mac(hash) (use OBJ_HASH_* in ok_asn1.h) */
	int		cipher_type;		/* stream (=0), block (=1) */
	int		is_exportable;		/* if exportable, (=1) */
	int		comp_meth;		/* compression method (usually 0) (ok_ssl original) */
	unsigned char	aicrypto_hash_size;
	unsigned char	key_material;
	unsigned char	IV_size;
}aicrypto_SSLCipherSpec;


/*
 * Handshake Protocol 
 */

/* Client Hello */
typedef struct aicrypto_hs_client_hello{
	aicrypto_ProtocolVersion	version;
	unsigned char	random[32];	/* gmt_unix_time & random_byte */
	/* unsigned char	session_id[32];	same number aicrypto_as server hello */

	/* CipherSuite (3 bytes) cipher_suites<2..2^16-1> */
	unsigned char	cipher_suites[64];

	/* enum { null=0, 255} CompressionMethod; */
	unsigned char	compression_methods[32];
}aicrypto_SSLClientHello;

/* Server Hello */
typedef struct aicrypto_hs_server_hello{
	aicrypto_ProtocolVersion	version;
	unsigned char	random[32];	/* gmt_unix_time & random_byte */

	unsigned char	session_id[32];	/* SessionID<0..32> */
	unsigned char	cipher_suites[64];
	unsigned char	compression_methods[32];
}aicrypto_SSLServerHello;


/*
 * aicrypto_SSL Structure
 */
typedef struct aicrypto_ssl aicrypto_SSL;
typedef struct aicrypto_ssl_context aicrypto_SSLCTX;

typedef struct aicrypto_ssl_callback_func{    
	int	(*read_cb)(int sock,char* buf,int len);
	int	(*write_cb)(int sock,char* buf,int len);
	int	(*read_debug)(aicrypto_SSL *aicrypto_ssl,int data);
	int	(*write_debug)(aicrypto_SSL *aicrypto_ssl,int data);
	int	(*vfy_cb)(aicrypto_SSL *aicrypto_ssl,aicrypto_Cert *cert);
}aicrypto_SSLCB;

struct aicrypto_ssl_context{
	aicrypto_ProtocolVersion	version;

	/***** currnt state *****/
	int		state;	/* current handshake state */
	int		errnum;	/* if error occured, error number is set */
	int		serv;	/* server flag */
	int		recv_cspec;	/* change chipher spec flag */

	unsigned char wseq[8];	/* message write sequence number */
	unsigned char rseq[8];	/* message read sequence number */

	aicrypto_MD5_CTX		*hsmsg_md5;		/* handshake-messages */
	aicrypto_SHA1_CTX	*hsmsg_sha1;	/* handshake-messages */

	/***** aicrypto_SSL infos *****/
	aicrypto_SSLCipherSpec	*cspec;
	aicrypto_SSLClientHello	*chello;
	aicrypto_SSLServerHello	*shello;

	/* client certificates (and private key) */
	aicrypto_PKCS12		*cp12;
	/* server certificates (and private key)
	 * in the case of server, this one is just pointer except the master aicrypto_SSL
	 */
	aicrypto_PKCS12		*sp12;
	/* server key exchange (if the server doesn't have its certificate) */
	aicrypto_Key			*exkey;

	/***** aicrypto_SSL Buffers *****/
	aicrypto_SSLPlaintext	*ptxt;	/* fragment doesn't have allocated memory */
	aicrypto_SSLCompressed	*comp;	/* usually this pointer is NULL */
	aicrypto_SSLCiphertext	*ctxt;

	unsigned char	*rbuf;	/* read buffer [AICRYPTO_SSLMAXBUF+3072] */
	unsigned char	*wbuf;	/* write buffer [AICRYPTO_SSLMAXBUF+3072] */
	int			wbuflen;
	int			rbuflen;	/* vailed read buffer length */
	/* sometimes, receive data includes several handshake packets.
	 * so, this data indicates current packet's length.
	 */
	int			rpklen;

	/* int			rbuftop; -- not use this */

	/***** aicrypto_SSL keys *****/
	unsigned char	premaster[48];	/* version[2] & random[46] */
	unsigned char	master_secret[48];

	/* aicrypto_SSL Final keys */
	unsigned char	client_write_MAC_secret[32];
	unsigned char	server_write_MAC_secret[32];

	aicrypto_Key		*skey;	/* server write key & IV */
	aicrypto_Key		*ckey;	/* client write key & IV */

	/***** system parameters *****/
	/* the master aicrypto_SSL should has aicrypto_SSLCTX list for reconnection.
	 * the master aicrypto_SSL has NULL pointer with top (maybe listening socket)
	 * and all clients have it, either.
	 */
	time_t	contime;	/* latest connection time */
	int		list_max;	/* max number of list */
	int		list_num;
	aicrypto_SSLCTX	*top;		/* pointer to top (master) aicrypto_SSLCTX */
	aicrypto_SSLCTX	*next;		/* pointer to next aicrypto_SSLCTX */
	aicrypto_SSLCTX	*prev;		/* pointer to previous aicrypto_SSLCTX */

	aicrypto_SSL		*aicrypto_ssl;		/* its owner aicrypto_SSL pointer */

	/* user certificate will be verified with this */
	/*aicrypto_STManager*/void	*stm;		/* just pointer except the master aicrypto_SSL */
	int		vfy_type;	/* verification type */
	int		vfy_depth;	/* cert chain depth for verification (from bottom) */

	/* aicrypto_ssl call back functions */
	aicrypto_SSLCB	*cb;
};

struct aicrypto_ssl{
	/* socket & FILE */
	int		sock;
	ACPI_FS_FILEPTR	fp;
	
	/* aicrypto_SSL mode */
	int		mode;	/* current RecodeLayer ContentType (=0..no aicrypto_ssl) */
	int		opt;	/* aicrypto_ssl mode flag */

	/* aicrypto_SSL context */
	aicrypto_SSLCTX	*ctx;
};

/* aicrypto_SSL CipherSuite */
/* CipherSuite is usually 2 bytes, but listed definitions have
 * { 0x00,0x?? }, then first byte is just omitted.
 */
#define AICRYPTO_SSL_NULL_WITH_NULL_NULL					0x00
#define AICRYPTO_SSL_RSA_WITH_NULL_MD5					0x01
#define AICRYPTO_SSL_RSA_WITH_NULL_SHA					0x02
#define AICRYPTO_SSL_RSA_EXPORT_WITH_RC4_40_MD5			0x03
#define AICRYPTO_SSL_RSA_WITH_RC4_128_MD5				0x04
#define AICRYPTO_SSL_RSA_WITH_RC4_128_SHA				0x05
#define AICRYPTO_SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5		0x06
#define AICRYPTO_SSL_RSA_WITH_IDEA_CBC_SHA				0x07
#define AICRYPTO_SSL_RSA_EXPORT_WITH_DES40_CBC_SHA		0x08
#define AICRYPTO_SSL_RSA_WITH_DES_CBC_SHA				0x09
#define AICRYPTO_SSL_RSA_WITH_3DES_EDE_CBC_SHA			0x0A
#define AICRYPTO_SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA	0x0B
#define AICRYPTO_SSL_DH_DSS_WITH_DES_CBC_SHA				0x0C
#define AICRYPTO_SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA		0x0D
#define AICRYPTO_SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA	0x0E
#define AICRYPTO_SSL_DH_RSA_WITH_DES_CBC_SHA				0x0F
#define AICRYPTO_SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA		0x10
#define AICRYPTO_SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA	0x11
#define AICRYPTO_SSL_DHE_DSS_WITH_DES_CBC_SHA			0x12
#define AICRYPTO_SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA		0x13
#define AICRYPTO_SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA	0x14
#define AICRYPTO_SSL_DHE_RSA_WITH_DES_CBC_SHA			0x15
#define AICRYPTO_SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA		0x16
#define AICRYPTO_SSL_DH_anon_EXPORT_WITH_RC4_40_MD5		0x17
#define AICRYPTO_SSL_DH_anon_WITH_RC4_128_MD5			0x18
#define AICRYPTO_SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA	0x19
#define AICRYPTO_SSL_DH_anon_WITH_DES_CBC_SHA			0x1A
#define AICRYPTO_SSL_DH_anon_WITH_3DES_EDE_CBC_SHA		0x1B
#define AICRYPTO_SSL_FORTEZZA_KEA_WITH_NULL_SHA			0x1C
#define AICRYPTO_SSL_FORTEZZA_KEA_WITH_FORTEZZA_CBC_SHA	0x1D
#define AICRYPTO_SSL_FORTEZZA_KEA_WITH_RC4_128_SHA		0x1E

/* aicrypto_SSL Verification mode -- see ok_x509.h more details */
#define AICRYPTO_SSL_DONT_VERIFY			AICRYPTO_DONT_VERIFY

/* aicrypto_SSL Record Layer, ContentType */
#define AICRYPTO_SSL_HANDSHAKEv2			10
#define AICRYPTO_SSL_CHANGE_CIPHER_SPEC	20
#define AICRYPTO_SSL_ALERT				21
#define AICRYPTO_SSL_HANDSHAKE			22
#define AICRYPTO_SSL_APPLICATION_DATA	23
#define AICRYPTO_SSL_CONTENT_TYPE_NULL	255

/* aicrypto_SSL Alert Protocol, AlertLevel */
#define AICRYPTO_SSL_AL_WARNING	1
#define	AICRYPTO_SSL_AL_FATAL	2

/* aicrypto_SSL Alert Protocol, AlertDescription */
#define AICRYPTO_SSL_AD_CLOSE_NOTIFY			0
#define AICRYPTO_SSL_AD_UNEXPECTED_MESSAGE	10
#define AICRYPTO_SSL_AD_BAD_RECORD_MAC		20
#define AICRYPTO_SSL_AD_DECOMPRESSION_FAILURE	30
#define AICRYPTO_SSL_AD_HAND_SHAKE_FAILURE	40
#define AICRYPTO_SSL_AD_NO_CERTIFICATE		41
#define AICRYPTO_SSL_AD_BAD_CERTIFICATE		42
#define AICRYPTO_SSL_AD_UNSUPPORTED_CERTIFICATE	43
#define AICRYPTO_SSL_AD_CERTIFICATE_REVOKED	44
#define AICRYPTO_SSL_AD_CERTIFICATE_EXPIRED	45
#define AICRYPTO_SSL_AD_CERTIFICATE_UNKNOWN	46
#define AICRYPTO_SSL_AD_ILLEGAL_PARAMETER	47
#define AICRYPTO_SSL_AD_NULL					255

/* system flags */
#define AICRYPTO_SSL_SYS_RESERVED0		0x0100	/* reserved */
#define AICRYPTO_SSL_SYS_RESERVED1		0x0200	/* reserved */
#define AICRYPTO_SSL_SYS_RESERVED2		0x0400	/* reserved */
#define AICRYPTO_SSL_SYS_CTXLISTED		0x0800	/* aicrypto_SSLCTX is in the list of aicrypto_SSL connection (might be reused) */
#define AICRYPTO_SSL_SYS_GOT_CERTREQ		0x1000	/* client got certificate request */
#define AICRYPTO_SSL_SYS_SOCK_PARENT		0x2000	/* parent socket */
#define	AICRYPTO_SSL_SYS_RECONNECTION	0x4000	/* re-connection flag */
#define AICRYPTO_SSL_SYS_SERVER			0x8000	/* aicrypto_SSL server flag */

/* aicrypto_ssl.c */
aicrypto_SSL *aicrypto_SSL_new(void);
void aicrypto_SSL_free(aicrypto_SSL *aicrypto_ssl);


/* ssl_hs.c */
int aicrypto_SSL_handshake(aicrypto_SSL *aicrypto_ssl);


/* ssl_sock.c */
int aicrypto_SSL_shutdown(aicrypto_SSL *aicrypto_ssl, int how);
int aicrypto_SSL_close(aicrypto_SSL *aicrypto_ssl);
int aicrypto_SSL_setsockopt(aicrypto_SSL *aicrypto_ssl, int level, int optname, const void * optval, int optlen);
int aicrypto_SSL_getsockopt(aicrypto_SSL *aicrypto_ssl, int level, int optname, void  *optval, int *optlen);


/* ssl_write.c */
int aicrypto_SSL_write(aicrypto_SSL *aicrypto_ssl, void *buf, size_t nbyte);


/* ssl_read.c */
int aicrypto_SSL_read(aicrypto_SSL *aicrypto_ssl, void *buf, size_t nbyte);


/* ssl_tool.c */
aicrypto_Cert *aicrypto_SSL_get_scert(aicrypto_SSLCTX *ctx);


/* ssl_vfy.c */
int aicrypto_SSL_set_vfytype(aicrypto_SSL *aicrypto_ssl, int type);

/* ssl_cb.c */
int aicrypto_SSL_set_read_cb(aicrypto_SSL *aicrypto_ssl, int (*cb)(int,char*,int));
int aicrypto_SSL_set_vfy_cb(aicrypto_SSL *aicrypto_ssl, int (*cb)(aicrypto_SSL*,aicrypto_Cert*));


/* etc */
#define AICRYPTO_SSL_get_server_cert(aicrypto_ssl)	aicrypto_SSL_get_scert((aicrypto_ssl)->ctx)


/*----------------------------------------------------------*/
/* ok_asn1.h                                                */
/*----------------------------------------------------------*/
/* ASN.1 TAGS */
#define AICRYPTO_ASN1_UTCTIME		0x17

/* ASN.1 OBJECT IDENTIFIER : define int size */
#define AICRYPTO_OBJ_DIR_C		3000
#define AICRYPTO_OBJ_DIR_ST		3001
#define AICRYPTO_OBJ_DIR_L		3002
#define AICRYPTO_OBJ_DIR_O		3003
#define AICRYPTO_OBJ_DIR_OU		3004
#define AICRYPTO_OBJ_DIR_CN		3005
#define AICRYPTO_OBJ_DIR_EMAIL	9021		/* = AICRYPTO_OBJ_P9_EMAIL */

#define AICRYPTO_OBJ_SIGOIW_MD2RSA	5001
#define AICRYPTO_OBJ_SIGOIW_MD5RSA	5002
#define AICRYPTO_OBJ_SIGOIW_SHA1RSA	5003

#define	AICRYPTO_OBJ_SIG_MD2RSA		9002
#define AICRYPTO_OBJ_SIG_MD5RSA		9003
#define AICRYPTO_OBJ_SIG_SHA1RSA		9004
#define AICRYPTO_OBJ_SIG_SHA1DSA		7001
#define AICRYPTO_OBJ_SIG_SHA1ECDSA	7010

#define AICRYPTO_OBJ_P12v1Bag_CERT    	11003


/* asn1_obj.c */
int aicrypto_ASN1_int_2object(int obj, unsigned char *ret, int *ret_len);

/* asn1_p7sign.c */
aicrypto_PKCS7 *aicrypto_ASN1_read_p7s(unsigned char *der);




/*----------------------------------------------------------*/
/* key_type.h                                               */
/*----------------------------------------------------------*/

/* Public aicrypto_Key Type define
   use of struct aicrypto_Cert->pubkey */
#define	AICRYPTO_KEY_NULL	530

#define	AICRYPTO_KEY_DES		533
#define AICRYPTO_KEY_3DES	534
#define AICRYPTO_KEY_RC2		535
#define AICRYPTO_KEY_RC4		536

#define	AICRYPTO_KEY_RSA_PUB	531
#define	AICRYPTO_KEY_RSA_PRV	532
#define AICRYPTO_KEY_DSA_PUB	537
#define AICRYPTO_KEY_DSA_PRV	538
#define AICRYPTO_KEY_DH_PUB	539
#define AICRYPTO_KEY_DH_PRV	540
#define AICRYPTO_KEY_ECDSA_PUB	550
#define AICRYPTO_KEY_ECDSA_PRV	551

#define	AICRYPTO_KEY_P11RSA_PUB	561
#define	AICRYPTO_KEY_P11RSA_PRV	562
#define AICRYPTO_KEY_P11DSA_PUB	563
#define AICRYPTO_KEY_P11DSA_PRV	564
#define AICRYPTO_KEY_P11DH_PUB	565
#define AICRYPTO_KEY_P11DH_PRV	566
#define AICRYPTO_KEY_P11ECDSA_PUB	567
#define AICRYPTO_KEY_P11ECDSA_PRV	568


/*----------------------------------------------------------*/
/* aicrypto_large_num.h                                              */
/*----------------------------------------------------------*/
typedef struct aicrypto_large_num{
    ULONG *num;
    int  top;
    int  size;
    int  neg;       /* negative flag */
}aicrypto_LNm;

/***** large_sys.c *****/
aicrypto_LNm *aicrypto_LN_alloc(void);
void aicrypto_LN_free(aicrypto_LNm *a);

/* size is int(32bit) size */
aicrypto_LNm *aicrypto_LN_alloc_u32(int size,ULONG *l);
/* size is short[] size */
aicrypto_LNm *aicrypto_LN_alloc_s(int size,unsigned short *s);
/* byte is char[] size */
aicrypto_LNm *aicrypto_LN_alloc_c(int byte,unsigned char *c);


/*----------------------------------------------------------*/
/* ok_rsa.h                                                 */
/*----------------------------------------------------------*/
typedef struct aicrypto_Public_key_RSA{
  int   key_type; /* key identifier */
  int   size;

  aicrypto_LNm   *n; /* public module */
  aicrypto_LNm   *e; /* public exponent */
}aicrypto_Pubkey_RSA;

typedef struct aicrypto_Private_key_RSA{
  int   key_type; /* key identifier */
  int   size;

  int   version;
  aicrypto_LNm   *n; /* public module */
  aicrypto_LNm   *e; /* public exponent */
  aicrypto_LNm   *d; /* private exponent */
  aicrypto_LNm   *p; /* prime1 */
  aicrypto_LNm   *q; /* prime2 */
  aicrypto_LNm   *e1;    /* exponent1 -- d mod (p-1) */
  aicrypto_LNm   *e2;    /* exponent2 -- d mod (q-1) */
  aicrypto_LNm   *cof;   /* coefficient -- (q-1) mod p */

  /* DER encode strings */
  unsigned char *der;
}aicrypto_Prvkey_RSA;

/* rsa.c */
int aicrypto_RSApub_doCrypt(int len, unsigned char *from, unsigned char *to, aicrypto_Pubkey_RSA *key);
int aicrypto_RSAprv_doCrypt(int len, unsigned char *from, unsigned char *to, aicrypto_Prvkey_RSA *key);

void aicrypto_RSA_set_pubkey(aicrypto_Pubkey_RSA *key,aicrypto_LNm *n,aicrypto_LNm *e);
void aicrypto_RSA_set_prvkey(aicrypto_Prvkey_RSA *key,aicrypto_LNm *n,aicrypto_LNm *d);


/*----------------------------------------------------------*/
/* ok_des.h                                                 */
/*----------------------------------------------------------*/
typedef struct aicrypto_crypt_DES_key{
    int   key_type;     /* key identifier */
    int   size;

    ULLONG  list[16];
    ULLONG  iv;         /* current initialize vector */
    ULLONG  oiv;        /* original initialize vector */
}aicrypto_Key_DES;

typedef struct aicrypto_crypt_3DES_key{
    int   key_type;             /* key identifier */
    int   size;

    ULLONG  list1[16];
    ULLONG  list2[16];
    ULLONG  list3[16];
    ULLONG  iv;
    ULLONG  oiv;        /* original initialize vector */
}aicrypto_Key_3DES;


/* des_key.c */
aicrypto_Key_DES *aicrypto_DESkey_new_(void);
aicrypto_Key_DES *aicrypto_DESkey_new(int len,unsigned char *key);
aicrypto_Key_DES *aicrypto_DESkey_dup(aicrypto_Key_DES *org);
void aicrypto_DESkey_free(aicrypto_Key_DES *key);
int  aicrypto_DESkey_set(aicrypto_Key_DES *dk,int len,unsigned char *key);
void aicrypto_DES_set_iv(aicrypto_Key_DES *key,unsigned char *ivc);

aicrypto_Key_3DES *aicrypto_DES3key_new_(void);
aicrypto_Key_3DES *aicrypto_DES3key_new(aicrypto_Key_DES *key1,aicrypto_Key_DES *key2,aicrypto_Key_DES *key3);
aicrypto_Key_3DES *aicrypto_DES3key_new_c(int len,unsigned char *key);
aicrypto_Key_3DES *aicrypto_DES3key_dup(aicrypto_Key_3DES *org);
void aicrypto_DES3key_free(aicrypto_Key_3DES *key);
int aicrypto_DES3key_set(aicrypto_Key_3DES *dk,aicrypto_Key_DES *key1,aicrypto_Key_DES *key2,aicrypto_Key_DES *key3);
int aicrypto_DES3key_set_c(aicrypto_Key_3DES *dk,int len,unsigned char *key);
void aicrypto_DES3_set_iv(aicrypto_Key_3DES *key,unsigned char *ivc);

/*  DES (ECB mode) */
void aicrypto_DES_ecb_encrypt(aicrypto_Key_DES *key,int byte,unsigned char *in,unsigned char *out);
void aicrypto_DES_ecb_decrypt(aicrypto_Key_DES *key,int byte,unsigned char *in,unsigned char *out);

/*  DES (CBC mode) 
 *  iv .. initialization vector.
 */
void aicrypto_DES_cbc_encrypt(aicrypto_Key_DES *key,int byte,unsigned char *in,unsigned char *out);
void aicrypto_DES_cbc_decrypt(aicrypto_Key_DES *key,int byte,unsigned char *in, unsigned char *out);

/*  DES (EDE3 ECB mode) ... Triple DES
 */
void aicrypto_DES3_ecb_encrypt(aicrypto_Key_3DES *key,int byte,unsigned char *in,unsigned char *out);
void aicrypto_DES3_ecb_decrypt(aicrypto_Key_3DES *key,int byte,unsigned char *in,unsigned char *out);

/*  DES (EDE3 CBC mode) ... Triple DES
 *  iv .. initialization vector.
 */
void aicrypto_DES3_cbc_encrypt(aicrypto_Key_3DES *key,int byte,unsigned char *in,unsigned char *out);
void aicrypto_DES3_cbc_decrypt(aicrypto_Key_3DES *key,int byte,unsigned char *in,unsigned char *out);


/*----------------------------------------------------------*/
/* ok_tool.h                                                */
/*----------------------------------------------------------*/

/* signature.c */
int aicrypto_OK_do_signature(aicrypto_Key *prv, unsigned char *data, int data_len, unsigned char **signature,int *sig_len, int sig_algo);
int aicrypto_OK_do_verify(aicrypto_Key *pub, unsigned char *digest, unsigned char *sig, int sig_algo);

/* Jackey add for trusted midlet begin here                 */

/*----------------------------------------------------------*/
/* ok_asn1.h                                                */
/*----------------------------------------------------------*/

/* asn1_cert.c */
int aicrypto_ASN1_vfy_sig(aicrypto_Key *pub, unsigned char *der, unsigned char *sig, int sig_algo);
aicrypto_Cert *aicrypto_ASN1_read_cert(unsigned char *in);
int aicrypto_ASN1_vfy_sig(aicrypto_Key *pub, unsigned char *der, unsigned char *sig, int sig_algo);
unsigned char *aicrypto_ASN1_next_(unsigned char *in,int *mv);
unsigned char *aicrypto_ASN1_step_(unsigned char *in,int n,int *mv);
unsigned char *aicrypto_ASN1_skip_(unsigned char *in,int *mv);
#define AICRYPTO_ASN1_next(in)	aicrypto_ASN1_next_((in),NULL)
#define AICRYPTO_ASN1_step(in,n)	aicrypto_ASN1_step_((in),(n),NULL)
#define AICRYPTO_ASN1_skip(in)	aicrypto_ASN1_skip_((in),NULL)

/*----------------------------------------------------------*/
/* ok_tool.h                                                */
/*----------------------------------------------------------*/

/* digest.c */
unsigned char *aicrypto_OK_do_digest(int digest_algo,unsigned char *data,int data_len,
							unsigned char *ret,int *ret_len);

/*----------------------------------------------------------*/
/* ok_x509.h                                                */
/*----------------------------------------------------------*/

/* cert.c */
void aicrypto_Cert_free(aicrypto_Cert *ct);

/* Jackey add for trusted midlet end here                   */

#ifdef  __cplusplus
}
#endif

#endif /* _LIBAICRYPTO_H */

