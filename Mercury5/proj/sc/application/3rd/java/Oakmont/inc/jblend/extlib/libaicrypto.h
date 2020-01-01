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


/*----------------------------------------------------------*/
/* md_global.h                                              */
/*----------------------------------------------------------*/
/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;


/*----------------------------------------------------------*/
/* ok_md5.h                                                 */
/*----------------------------------------------------------*/
/* MD5 context. */
typedef struct{
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;


/*----------------------------------------------------------*/
/* ok_sha1.h                                                */
/*----------------------------------------------------------*/
typedef struct sha1_context{
  ULONG H[5];
  
  unsigned char	dat[64];
  int 	len;
  int	mod;
}SHA1_CTX;

void SHA1init(SHA1_CTX *ctx);
void SHA1update(SHA1_CTX *ctx, unsigned char *in, int len);
void SHA1final(unsigned char *ret,SHA1_CTX *ctx);



/*----------------------------------------------------------*/
/* ok_x509.h                                                */
/*----------------------------------------------------------*/
/* public or private key struct 
 *    base structure 
 */
typedef struct crypt_key{
	int key_type; /* key identifier */
	int size;

	/* type field */
}Key;

/*
 * the X.509 digital certificate structures
 */
typedef struct validity{
	int       notBeforeType;   /* UTC/Generalized */
	struct tm notBefore;
	int       notAfterType;    /* UTC/Generalized */
	struct tm notAfter;
}Validity;

typedef struct certificate_extension CertExt;
struct certificate_extension{
	int extnID;
	int critical;	/* boolean default false */
	unsigned char *objid;	/* if extnID==0, this has byte string value */

	int dlen;
	unsigned char *der;

	CertExt *next;
};

#define RDN_MAX		16

typedef struct certificate_dir{
	int num;
	struct cert_rdn{
		int  derform;
		int  tagoid;
		char *tag;
	} rdn[RDN_MAX];
}CertDN,CertDIR;

typedef struct x509_certificate{
	int version;
	int serialNumber;
	unsigned char *long_sn;	/* long serial number (usually NULL) */

	int	signature_algo;
	char	*issuer;
	CertDN	issuer_dn;

	Validity	time;

	char	*subject;
	CertDN	subject_dn;

	int	pubkey_algo;
	Key	*pubkey;

	long	issuerUniqueID;
	long	subjectUniqueID;

	CertExt	*ext;

	int	siglen;
	unsigned char	*signature;

	/* DER encode strings */
	unsigned char	*der;
}Cert,Req;


/* define verify error */
#define X509_VFY_ERR			0x0100
#define X509_VFY_ERR_SIGNATURE		0x0200
#define X509_VFY_ERR_SIGNATURE_CRL	0x0300
#define X509_VFY_ERR_NOTBEFORE		0x0400
#define X509_VFY_ERR_NOTAFTER		0x0500
#define X509_VFY_ERR_LASTUPDATE		0x0600
#define X509_VFY_ERR_NEXTUPDATE 	0x0700
#define X509_VFY_ERR_REVOKED		0x0a00
#define X509_VFY_ERR_SELF_SIGN		0x0b00
#define X509_VFY_ERR_CA_CHAIN		0x0c00
#define X509_VFY_ERR_SYSTEMERR		0x0d00

#define X509_VFY_ERR_NOT_CACERT		0x1000
#define X509_VFY_ERR_ISSUER_CRL		0x1100
#define X509_VFY_ERR_NOT_IN_CERTLIST	0x1200
#define X509_VFY_ERR_UNKOWN_SIG_ALGO	0x1300

/* define verify check type */
#define DONT_VERIFY			0x0080	/* don't verify anything, just return 0 */


/* x509_time.c */
unsigned char *stm2UTC(struct tm *stm,unsigned char *buf,unsigned char tag);

/* cert_print.c */
void Cert_print(Cert *ct);

/* cert_vfy.c */
int Cert_validity_verify(Cert *ct);
int Cert_signature_verify(Cert *ca,Cert *user);

/* cert_tool.c */
int Cert_dncmp(CertDN *d1,CertDN *d2);
int Cert_is_root(Cert *ct);


/*----------------------------------------------------------*/
/* ok_pkcs12.h                                              */
/*----------------------------------------------------------*/
/*---- PKCS12 Structures ----*/
typedef struct pkcs12_Bag_list P12_Baggage;
struct pkcs12_Bag_list{
	int		type;
	P12_Baggage	*next;

	unsigned char	*friendlyName;
	unsigned char	localKeyID[4];
};

typedef struct pkcs12{
	int		version;
	P12_Baggage	*bag;
	long		reserve;	/* (= NULL) this is just dummy for PKCS7 */
}PKCS12;

typedef struct pkcs12_BagID_CERT{
	int		type;
	P12_Baggage	*next;

	char	*friendlyName;
	char	localKeyID[4];

	Cert	*cert;

}P12_CertBag;

/* p12_tool.c */
int P12_max_depth(PKCS12 *p12,int type);
int P12_check_chain(PKCS12 *p12,int print);
Cert *P12_get_usercert(PKCS12 *p12);


/*----------------------------------------------------------*/
/* ok_pkcs7.h                                               */
/*----------------------------------------------------------*/
/*---- PKCS7 Structures ----*/
typedef struct PKCS7ContentInfo P7_Content;
struct PKCS7ContentInfo{ /* nomal data type */
	int		p7type;		/* use ASN.1 object id */

	int		size;
	unsigned char	*data;
};

typedef struct pkcs7{
  int		version;	/* it's not used in pkcs7 */
  P12_Baggage	*bag;	/* Certificates and CRLs */

  P7_Content	*cont;
  unsigned char	*der;
}PKCS7;

/* pkcs7.c */
void P7_free(PKCS7 *p7);

/* p7_file.c */
void P7_print(PKCS7 *p12);


/*----------------------------------------------------------*/
/* ok_store.h                                               */
/*----------------------------------------------------------*/
/*
 * Store Bags
 */
typedef struct store_bag CSBag;
struct store_bag{
	int ctx_type; /* bag context : cert, crl, key... */
	char *unique_id;   /* bag name (must be unique in a store) */

	CSBag *next;
	CSBag *prev;

	int status;
	int use_flag;

	int serialNumber;
	char *issuer;
	char *subject;

	int hlen;
	unsigned char key_hash[32];

	unsigned char *der;	/* cache of raw der */
	void *cache;	/* on memory cache : Cert*, CRL*, Key*... */
	void *dev_info;	/* device specific access information */
};


/*----------------------------------------------------------*/
/* ok_ssl.h                                                 */
/*----------------------------------------------------------*/
/*
 * SSL Record Layer
 */
typedef struct protocol_version{
	unsigned char major,minor;
}ProtocolVersion;

/*** Plain Text Struct ***/
typedef struct ssl_plain_text{
	unsigned int	type;	/* ContentType */
	unsigned int	length;	/* < 2^14 */

	/* this fragment doesn't have allocated memory.
	 * usually it points current buffer of procedure's buffer value.
	 * (i.e. the case of SSL_write(SSL*,void*,size_t), void* is taken)
	 */
	unsigned char	*fragment;	/* opaque [SSLPlaintext.length] */

}SSLPlaintext;

/*** Compressed Data Struct ***/
typedef SSLPlaintext	SSLCompressed;	/* same format */


/*** Cipher Text Struct ***/
typedef struct ssl_ciphertext{
	unsigned int	type;	/* ContentType */
	unsigned int	length;
	
	unsigned char	*fragment;

	/* these are cipher-fragment content */
	unsigned char	*content;		/* opaque [SSLCompressed.length] */
	unsigned char	MAC[32];		/* opaque [CipherSpec.hash_size] */
	unsigned char	padding[32];	/* [GenericBlockCipher.padding_length] */
	unsigned char	padding_length;
}SSLCiphertext;


/*
 * Cipher Spec
 */
typedef struct ssl_cipher_spec{
	int		bulk_cipher_algorithm;	/* current cipher (use OBJ_CRYALGO_* in ok_asn1.h) */
	int		mac_algorithm;		/* current mac(hash) (use OBJ_HASH_* in ok_asn1.h) */
	int		cipher_type;		/* stream (=0), block (=1) */
	int		is_exportable;		/* if exportable, (=1) */
	int		comp_meth;		/* compression method (usually 0) (ok_ssl original) */
	unsigned char	hash_size;
	unsigned char	key_material;
	unsigned char	IV_size;
}SSLCipherSpec;


/*
 * Handshake Protocol 
 */

/* Client Hello */
typedef struct hs_client_hello{
	ProtocolVersion	version;
	unsigned char	random[32];	/* gmt_unix_time & random_byte */
	/* unsigned char	session_id[32];	same number as server hello */

	/* CipherSuite (3 bytes) cipher_suites<2..2^16-1> */
	unsigned char	cipher_suites[64];

	/* enum { null=0, 255} CompressionMethod; */
	unsigned char	compression_methods[32];
}SSLClientHello;

/* Server Hello */
typedef struct hs_server_hello{
	ProtocolVersion	version;
	unsigned char	random[32];	/* gmt_unix_time & random_byte */

	unsigned char	session_id[32];	/* SessionID<0..32> */
	unsigned char	cipher_suites[64];
	unsigned char	compression_methods[32];
}SSLServerHello;


/*
 * SSL Structure
 */
typedef struct ssl SSL;
typedef struct ssl_context SSLCTX;

typedef struct ssl_callback_func{    
	int	(*read_cb)(int sock,char* buf,int len);
	int	(*write_cb)(int sock,char* buf,int len);
	int	(*read_debug)(SSL *ssl,int data);
	int	(*write_debug)(SSL *ssl,int data);
	int	(*vfy_cb)(SSL *ssl,Cert *cert);
}SSLCB;

struct ssl_context{
	ProtocolVersion	version;

	/***** currnt state *****/
	int		state;	/* current handshake state */
	int		errnum;	/* if error occured, error number is set */
	int		serv;	/* server flag */
	int		recv_cspec;	/* change chipher spec flag */

	unsigned char wseq[8];	/* message write sequence number */
	unsigned char rseq[8];	/* message read sequence number */

	MD5_CTX		*hsmsg_md5;		/* handshake-messages */
	SHA1_CTX	*hsmsg_sha1;	/* handshake-messages */

	/***** SSL infos *****/
	SSLCipherSpec	*cspec;
	SSLClientHello	*chello;
	SSLServerHello	*shello;

	/* client certificates (and private key) */
	PKCS12		*cp12;
	/* server certificates (and private key)
	 * in the case of server, this one is just pointer except the master SSL
	 */
	PKCS12		*sp12;
	/* server key exchange (if the server doesn't have its certificate) */
	Key			*exkey;

	/***** SSL Buffers *****/
	SSLPlaintext	*ptxt;	/* fragment doesn't have allocated memory */
	SSLCompressed	*comp;	/* usually this pointer is NULL */
	SSLCiphertext	*ctxt;

	unsigned char	*rbuf;	/* read buffer [SSLMAXBUF+3072] */
	unsigned char	*wbuf;	/* write buffer [SSLMAXBUF+3072] */
	int			wbuflen;
	int			rbuflen;	/* vailed read buffer length */
	/* sometimes, receive data includes several handshake packets.
	 * so, this data indicates current packet's length.
	 */
	int			rpklen;

	/* int			rbuftop; -- not use this */

	/***** SSL keys *****/
	unsigned char	premaster[48];	/* version[2] & random[46] */
	unsigned char	master_secret[48];

	/* SSL Final keys */
	unsigned char	client_write_MAC_secret[32];
	unsigned char	server_write_MAC_secret[32];

	Key		*skey;	/* server write key & IV */
	Key		*ckey;	/* client write key & IV */

	/***** system parameters *****/
	/* the master SSL should has SSLCTX list for reconnection.
	 * the master SSL has NULL pointer with top (maybe listening socket)
	 * and all clients have it, either.
	 */
	time_t	contime;	/* latest connection time */
	int		list_max;	/* max number of list */
	int		list_num;
	SSLCTX	*top;		/* pointer to top (master) SSLCTX */
	SSLCTX	*next;		/* pointer to next SSLCTX */
	SSLCTX	*prev;		/* pointer to previous SSLCTX */

	SSL		*ssl;		/* its owner SSL pointer */

	/* user certificate will be verified with this */
	/*STManager*/void	*stm;		/* just pointer except the master SSL */
	int		vfy_type;	/* verification type */
	int		vfy_depth;	/* cert chain depth for verification (from bottom) */

	/* ssl call back functions */
	SSLCB	*cb;
};

struct ssl{
	/* socket & FILE */
	int		sock;
	FILE	*fp;
	
	/* SSL mode */
	int		mode;	/* current RecodeLayer ContentType (=0..no ssl) */
	int		opt;	/* ssl mode flag */

	/* SSL context */
	SSLCTX	*ctx;
};

/* SSL CipherSuite */
/* CipherSuite is usually 2 bytes, but listed definitions have
 * { 0x00,0x?? }, then first byte is just omitted.
 */
#define SSL_NULL_WITH_NULL_NULL					0x00
#define SSL_RSA_WITH_NULL_MD5					0x01
#define SSL_RSA_WITH_NULL_SHA					0x02
#define SSL_RSA_EXPORT_WITH_RC4_40_MD5			0x03
#define SSL_RSA_WITH_RC4_128_MD5				0x04
#define SSL_RSA_WITH_RC4_128_SHA				0x05
#define SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5		0x06
#define SSL_RSA_WITH_IDEA_CBC_SHA				0x07
#define SSL_RSA_EXPORT_WITH_DES40_CBC_SHA		0x08
#define SSL_RSA_WITH_DES_CBC_SHA				0x09
#define SSL_RSA_WITH_3DES_EDE_CBC_SHA			0x0A
#define SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA	0x0B
#define SSL_DH_DSS_WITH_DES_CBC_SHA				0x0C
#define SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA		0x0D
#define SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA	0x0E
#define SSL_DH_RSA_WITH_DES_CBC_SHA				0x0F
#define SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA		0x10
#define SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA	0x11
#define SSL_DHE_DSS_WITH_DES_CBC_SHA			0x12
#define SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA		0x13
#define SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA	0x14
#define SSL_DHE_RSA_WITH_DES_CBC_SHA			0x15
#define SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA		0x16
#define SSL_DH_anon_EXPORT_WITH_RC4_40_MD5		0x17
#define SSL_DH_anon_WITH_RC4_128_MD5			0x18
#define SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA	0x19
#define SSL_DH_anon_WITH_DES_CBC_SHA			0x1A
#define SSL_DH_anon_WITH_3DES_EDE_CBC_SHA		0x1B
#define SSL_FORTEZZA_KEA_WITH_NULL_SHA			0x1C
#define SSL_FORTEZZA_KEA_WITH_FORTEZZA_CBC_SHA	0x1D
#define SSL_FORTEZZA_KEA_WITH_RC4_128_SHA		0x1E

/* SSL Verification mode -- see ok_x509.h more details */
#define SSL_DONT_VERIFY			DONT_VERIFY

/* SSL Record Layer, ContentType */
#define SSL_HANDSHAKEv2			10
#define SSL_CHANGE_CIPHER_SPEC	20
#define SSL_ALERT				21
#define SSL_HANDSHAKE			22
#define SSL_APPLICATION_DATA	23
#define SSL_CONTENT_TYPE_NULL	255

/* SSL Alert Protocol, AlertLevel */
#define SSL_AL_WARNING	1
#define	SSL_AL_FATAL	2

/* SSL Alert Protocol, AlertDescription */
#define SSL_AD_CLOSE_NOTIFY			0
#define SSL_AD_UNEXPECTED_MESSAGE	10
#define SSL_AD_BAD_RECORD_MAC		20
#define SSL_AD_DECOMPRESSION_FAILURE	30
#define SSL_AD_HAND_SHAKE_FAILURE	40
#define SSL_AD_NO_CERTIFICATE		41
#define SSL_AD_BAD_CERTIFICATE		42
#define SSL_AD_UNSUPPORTED_CERTIFICATE	43
#define SSL_AD_CERTIFICATE_REVOKED	44
#define SSL_AD_CERTIFICATE_EXPIRED	45
#define SSL_AD_CERTIFICATE_UNKNOWN	46
#define SSL_AD_ILLEGAL_PARAMETER	47
#define SSL_AD_NULL					255

/* system flags */
#define SSL_SYS_RESERVED0		0x0100	/* reserved */
#define SSL_SYS_RESERVED1		0x0200	/* reserved */
#define SSL_SYS_RESERVED2		0x0400	/* reserved */
#define SSL_SYS_CTXLISTED		0x0800	/* SSLCTX is in the list of SSL connection (might be reused) */
#define SSL_SYS_GOT_CERTREQ		0x1000	/* client got certificate request */
#define SSL_SYS_SOCK_PARENT		0x2000	/* parent socket */
#define	SSL_SYS_RECONNECTION	0x4000	/* re-connection flag */
#define SSL_SYS_SERVER			0x8000	/* SSL server flag */

/* ssl.c */
SSL *SSL_new(void);
void SSL_free(SSL *ssl);


/* ssl_hs.c */
int SSL_handshake(SSL *ssl);


/* ssl_sock.c */
int SSL_shutdown(SSL *ssl, int how);
int SSL_close(SSL *ssl);
int SSL_setsockopt(SSL *ssl, int level, int optname, const void * optval, int optlen);
int SSL_getsockopt(SSL *ssl, int level, int optname, void  *optval, int *optlen);


/* ssl_write.c */
int SSL_write(SSL *ssl, void *buf, size_t nbyte);


/* ssl_read.c */
int SSL_read(SSL *ssl, void *buf, size_t nbyte);


/* ssl_tool.c */
Cert *SSL_get_scert(SSLCTX *ctx);


/* ssl_vfy.c */
int SSL_set_vfytype(SSL *ssl, int type);

/* ssl_cb.c */
int SSL_set_read_cb(SSL *ssl, int (*cb)(int,char*,int));
int SSL_set_vfy_cb(SSL *ssl, int (*cb)(SSL*,Cert*));


/* etc */
#define SSL_get_server_cert(ssl)	SSL_get_scert((ssl)->ctx)


/*----------------------------------------------------------*/
/* ok_asn1.h                                                */
/*----------------------------------------------------------*/
/* ASN.1 TAGS */
#define ASN1_UTCTIME		0x17

/* ASN.1 OBJECT IDENTIFIER : define int size */
#define OBJ_DIR_C		3000
#define OBJ_DIR_ST		3001
#define OBJ_DIR_L		3002
#define OBJ_DIR_O		3003
#define OBJ_DIR_OU		3004
#define OBJ_DIR_CN		3005
#define OBJ_DIR_EMAIL	9021		/* = OBJ_P9_EMAIL */

#define OBJ_SIGOIW_MD2RSA	5001
#define OBJ_SIGOIW_MD5RSA	5002
#define OBJ_SIGOIW_SHA1RSA	5003

#define	OBJ_SIG_MD2RSA		9002
#define OBJ_SIG_MD5RSA		9003
#define OBJ_SIG_SHA1RSA		9004
#define OBJ_SIG_SHA1DSA		7001
#define OBJ_SIG_SHA1ECDSA	7010

#define OBJ_P12v1Bag_CERT    	11003


/* asn1_obj.c */
int ASN1_int_2object(int obj, unsigned char *ret, int *ret_len);

/* asn1_p7sign.c */
PKCS7 *ASN1_read_p7s(unsigned char *der);




/*----------------------------------------------------------*/
/* key_type.h                                               */
/*----------------------------------------------------------*/

/* Public Key Type define
   use of struct Cert->pubkey */
#define	KEY_NULL	530

#define	KEY_DES		533
#define KEY_3DES	534
#define KEY_RC2		535
#define KEY_RC4		536

#define	KEY_RSA_PUB	531
#define	KEY_RSA_PRV	532
#define KEY_DSA_PUB	537
#define KEY_DSA_PRV	538
#define KEY_DH_PUB	539
#define KEY_DH_PRV	540
#define KEY_ECDSA_PUB	550
#define KEY_ECDSA_PRV	551

#define	KEY_P11RSA_PUB	561
#define	KEY_P11RSA_PRV	562
#define KEY_P11DSA_PUB	563
#define KEY_P11DSA_PRV	564
#define KEY_P11DH_PUB	565
#define KEY_P11DH_PRV	566
#define KEY_P11ECDSA_PUB	567
#define KEY_P11ECDSA_PRV	568


/*----------------------------------------------------------*/
/* large_num.h                                              */
/*----------------------------------------------------------*/
typedef struct large_num{
    ULONG *num;
    int  top;
    int  size;
    int  neg;       /* negative flag */
}LNm;

/***** large_sys.c *****/
LNm *LN_alloc();
void LN_free(LNm *a);

/* size is int(32bit) size */
LNm *LN_alloc_u32(int size,ULONG *l);
/* size is short[] size */
LNm *LN_alloc_s(int size,unsigned short *s);
/* byte is char[] size */
LNm *LN_alloc_c(int byte,unsigned char *c);


/*----------------------------------------------------------*/
/* ok_rsa.h                                                 */
/*----------------------------------------------------------*/
typedef struct Public_key_RSA{
  int   key_type; /* key identifier */
  int   size;

  LNm   *n; /* public module */
  LNm   *e; /* public exponent */
}Pubkey_RSA;

typedef struct Private_key_RSA{
  int   key_type; /* key identifier */
  int   size;

  int   version;
  LNm   *n; /* public module */
  LNm   *e; /* public exponent */
  LNm   *d; /* private exponent */
  LNm   *p; /* prime1 */
  LNm   *q; /* prime2 */
  LNm   *e1;    /* exponent1 -- d mod (p-1) */
  LNm   *e2;    /* exponent2 -- d mod (q-1) */
  LNm   *cof;   /* coefficient -- (q-1) mod p */

  /* DER encode strings */
  unsigned char *der;
}Prvkey_RSA;

/* rsa.c */
int RSApub_doCrypt(int len, unsigned char *from, unsigned char *to, Pubkey_RSA *key);
int RSAprv_doCrypt(int len, unsigned char *from, unsigned char *to, Prvkey_RSA *key);

void RSA_set_pubkey(Pubkey_RSA *key,LNm *n,LNm *e);
void RSA_set_prvkey(Prvkey_RSA *key,LNm *n,LNm *d);


/*----------------------------------------------------------*/
/* ok_des.h                                                 */
/*----------------------------------------------------------*/
typedef struct crypt_DES_key{
    int   key_type;     /* key identifier */
    int   size;

    ULLONG  list[16];
    ULLONG  iv;         /* current initialize vector */
    ULLONG  oiv;        /* original initialize vector */
}Key_DES;

typedef struct crypt_3DES_key{
    int   key_type;             /* key identifier */
    int   size;

    ULLONG  list1[16];
    ULLONG  list2[16];
    ULLONG  list3[16];
    ULLONG  iv;
    ULLONG  oiv;        /* original initialize vector */
}Key_3DES;


/* des_key.c */
Key_DES *DESkey_new_();
Key_DES *DESkey_new(int len,unsigned char *key);
Key_DES *DESkey_dup(Key_DES *org);
void DESkey_free(Key_DES *key);
int  DESkey_set(Key_DES *dk,int len,unsigned char *key);
void DES_set_iv(Key_DES *key,unsigned char *ivc);

Key_3DES *DES3key_new_();
Key_3DES *DES3key_new(Key_DES *key1,Key_DES *key2,Key_DES *key3);
Key_3DES *DES3key_new_c(int len,unsigned char *key);
Key_3DES *DES3key_dup(Key_3DES *org);
void DES3key_free(Key_3DES *key);
int DES3key_set(Key_3DES *dk,Key_DES *key1,Key_DES *key2,Key_DES *key3);
int DES3key_set_c(Key_3DES *dk,int len,unsigned char *key);
void DES3_set_iv(Key_3DES *key,unsigned char *ivc);

/*  DES (ECB mode) */
void DES_ecb_encrypt(Key_DES *key,int byte,unsigned char *in,unsigned char *out);
void DES_ecb_decrypt(Key_DES *key,int byte,unsigned char *in,unsigned char *out);

/*  DES (CBC mode) 
 *  iv .. initialization vector.
 */
void DES_cbc_encrypt(Key_DES *key,int byte,unsigned char *in,unsigned char *out);
void DES_cbc_decrypt(Key_DES *key,int byte,unsigned char *in, unsigned char *out);

/*  DES (EDE3 ECB mode) ... Triple DES
 */
void DES3_ecb_encrypt(Key_3DES *key,int byte,unsigned char *in,unsigned char *out);
void DES3_ecb_decrypt(Key_3DES *key,int byte,unsigned char *in,unsigned char *out);

/*  DES (EDE3 CBC mode) ... Triple DES
 *  iv .. initialization vector.
 */
void DES3_cbc_encrypt(Key_3DES *key,int byte,unsigned char *in,unsigned char *out);
void DES3_cbc_decrypt(Key_3DES *key,int byte,unsigned char *in,unsigned char *out);


/*----------------------------------------------------------*/
/* ok_tool.h                                                */
/*----------------------------------------------------------*/

/* signature.c */
int OK_do_signature(Key *prv, unsigned char *data, int data_len, unsigned char **signature,int *sig_len, int sig_algo);
int OK_do_verify(Key *pub, unsigned char *digest, unsigned char *sig, int sig_algo);



#ifdef  __cplusplus
}
#endif

#endif /* _LIBAICRYPTO_H */

