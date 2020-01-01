/* rvtls.h - Common Core TLS functionality support module */

/************************************************************************
                Copyright (c) 2001 RADVISION Inc.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVISION LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVISION LTD..

RADVISION LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
************************************************************************/


#ifndef _RV_TLS_H
#define _RV_TLS_H
 

#if (RV_TLS_TYPE != RV_TLS_NONE)
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#endif
#include "rvccore.h"
#include "rvlog.h"
#include "rvsocket.h"
#include "rvselect.h"
#include "rvmutex.h"
#include "rvnettypes.h"


#if defined(__cplusplus)
extern "C" {
#endif

/* Module specific error codes (-512..-1023). See rverror.h for more details */
#define RV_TLS_ERROR_GEN		-512		/* general TLS error */
#define	RV_TLS_ERROR_WILL_BLOCK	-513		/* Will block error, specifies that 
											operation should be complete later */
#define	RV_TLS_ERROR_INCOMPLETE	-514		/* Specifies that operation remained incomplete
											but not because it may block caller. Currently
											used only in shutdown procedure */
#define RV_TLS_ERROR_SHUTDOWN	-515		/* Specifies that shutdown request
											was received */

	

#if (RV_TLS_TYPE != RV_TLS_NONE)


/*
 * RvCompareCertificateCB - defines stack callback that will be applied
 * when peer certificate will be received. The callback return code
 * specifies if stack finds received certificate valid or not.
 */
typedef RvInt ( * RvCompareCertificateCB )(
	IN int  prevErrro, 
	IN void *certCtx);


/* TLS module event type - bitmask of defined below TLS events */
typedef RvUint16 RvTLSEvents;
    
#define RV_TLS_NONE_EV      0x0

#define	RV_TLS_HANDSHAKE_EV 0x1 /*	TLS handshake event, notifies that 
									handshake procedure may be continue */
#define	RV_TLS_READ_EV		0x2	/* TLS read event, notifies that TLS read 
									may be applied */
#define	RV_TLS_WRITE_EV		0x4	/* TLS write event, notifies that TLS write 
									may be applied */
#define	RV_TLS_SHUTDOWN_EV	0x8	/* TLS shutdown event, notifies that TLS 
									shutdown procedure can be applied */


/*
 * RvTLSEngine - defines TLS module instance
 *----------------------------------------------------------------------
 * ctx				- OpenSSL context instance
 */
typedef struct {
	SSL_CTX						*ctx;
} RvTLSEngine;


/*
 *	RvTLSRenegState - renegotiation state of this session
 */
typedef enum {
    RV_TLS_RENEG_NONE,         /* No renegotiation process is in progress */
    RV_TLS_RENEG_NEEDED,       /* Renegotiation is pended due to blocked
                                  operation. It will be run upon completion
                                  of the blocked operation. */
    RV_TLS_RENEG_STARTED       /* Renegotiation is started on this session 
                                *  at least from RV wrappers point of view.
                                *  Actual renegotiation may be started later
                                */
} RvTLSRenegState;

/*
 * RvTLSSessionCfg - SSL session configuration used by RvTlsSessionConstructEx
 *----------------------------------------------------------------------
 */
typedef struct {
    RvBool bDisablePartialSend;
        /* If RV_TRUE, partial send / receive will be disabled.
           Default - RV_FALSE. */
} RvTLSSessionCfg;

/*
 * RvTLSSession - defines TLS/SSL session
 *----------------------------------------------------------------------
 * sslSession           - OpenSSL session object
 * bio                  - OpenSSL BIO object, used by session
 * sock                 - socket used by BIO object
 * requiredForHandshake	- lists RvSelect events required to continue handshake
 * requiredForTLSRead	- lists RvSelect events required to continue read
 * requiredForTLSWrite	- lists RvSelect events required to continue write
 * requiredForTLSShutdown - lists RvSelect events required to continue shutdown
 * pendingTlsEvents	    - list of TLS events that stack is interest to receive
 * renegState           - state of renegotiation run on session
 * bWaitingShutdownFinish - if RV_TRUE, shutdown was not completed.
 *                        In comparison to not completed write or read,
 *                        not completed shutdown doesn't block read/write
 *                        operations
 * counterWrites        - number of successful SendBuffer (SSL_write) calls,
 *                        made by application on handling single TLS_WRITE event
 *                          
 */


typedef struct {
	SSL             *sslSession;
	BIO             *bio;
    RvSocket        sock;
	RvSelectEvents  requiredForHandshake;
	RvSelectEvents  requiredForTLSRead;
	RvSelectEvents  requiredForTLSWrite;
	RvSelectEvents  requiredForTLSShutdown;
	RvTLSEvents     pendingTlsEvents;
    RvTLSRenegState renegState;
    RvBool          bWaitingShutdownFinish;
    RvUint32        counterWrites;
} RvTLSSession;

#endif


/**********************************************************************************
 * RvTLSInit - initiates OpenSSL library
 *
 * This function should be called only once in specific process. It initiates 
 * OpenSSL library.
 *
 * INPUT : none
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSInit(void);

/**********************************************************************************
 * RvTLSEnd - finalize OpenSSL library usage
 *
 * This function should be called only once in specific process.
 *
 * INPUT : none
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSEnd(void);


/**********************************************************************************
 * RvTLSSourceConstruct - initiates TLS module log source
 *
 * This function should be called only once in specific process. It initiates 
 * OpenSSL library.
 *
 * INPUT : none
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RvStatus RvTLSSourceConstruct(
	IN RvLogMgr* logMgr);


#if (RV_TLS_TYPE != RV_TLS_NONE)
/**********************************************************************************
 * RvTLSEngineConstruct - constructs TLS engine
 *
 * Constructs SSL context according to the input parameters and TLS module log source.
 * It fills output TLS engine structure with results.
 *
 * INPUT: 
 *	method		- SSL version. Can be SSL v1, SSL v2 or TLS v1
 *	logMgr		- log instance
 *	privKey		- private key
 *	privKeyType	- private key type
 *	privKeyLen	- private key length
 *  cert		- local side certificate
 *  certLen		- local side certificate length
 *	certDepth	- maximum allowed depth of certificates
 *  mtx			- mutex that protects this TLS 
 *				  engine memory
 * OUTPUT: tlsEngine	- TLS engine memory
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSEngineConstruct(
	IN  RvTLSMethod				method,
	IN  RvChar					*privKey,
	IN  RvPrivKeyType			privKeyType,
	IN  RvInt					privKeyLen,
	IN  RvChar					*cert,
	IN  RvInt					certLen,
	IN	RvInt					certDepth,
	IN  RvMutex					*mtx,
	IN  RvLogMgr				*logMgr,
	OUT RvTLSEngine				*tlsEngine);



/**********************************************************************************
 * RvTLSEngineDestruct - destructs TLS engine
 *
 * Destructs SSL context.
 *
 * INPUT: 
 *	tlsEngine	- engine to be destructed
 *  mtx			- mutex that protects this TLS 
 *				  engine memory
 *	logMgr		- log instance
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI RvStatus RvTLSEngineDestruct(
	IN RvTLSEngine	*tlsEngine,
	IN RvMutex		*mtx,
	IN RvLogMgr		*logMgr);



/**********************************************************************************
 * RvTLSSessionConstruct - Initiates TLS/SSL session
 *
 * Creates uninitialized SSL/TLS session that matches context defined by 
 * input TLS engine.
 *
 * INPUT: 
 *	tlsEngine	- TLS engine
 *  mtxEngine	- mutex that protects TLS 
 *				  engine memory
 *  mtxSession	- mutex that protects Session 
 *				  engine memory
 *  logMgr		- log instance
 * OUTPUT: tlsSession	- new TLS session
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionConstruct(
	IN  RvTLSEngine		*tlsEngine,
	IN  RvMutex			*mtxEngine,
	IN  RvMutex			*mtxSession,
	IN  RvLogMgr		*logMgr,
	OUT RvTLSSession	*tlsSession);

/**********************************************************************************
 * RvTLSSessionConstructEx - Initiates TLS/SSL session
 *
 * Creates uninitialized SSL/TLS session that matches context defined by 
 * input TLS engine.
 *
 * INPUT: 
 *	tlsEngine	- TLS engine
 *  mtxEngine	- mutex that protects TLS 
 *				  engine memory
 *  mtxSession	- mutex that protects Session 
 *				  engine memory
 *  cfg         - configuration of session.
 *                If NULL, default configuration will be used.
 *  logMgr		- log instance
 * OUTPUT: tlsSession	- new TLS session
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionConstructEx(
	IN  RvTLSEngine		*tlsEngine,
	IN  RvMutex			*mtxEngine,
	IN  RvMutex			*mtxSession,
	IN  RvTLSSessionCfg *cfg,
	IN  RvLogMgr		*logMgr,
	OUT RvTLSSession	*tlsSession);


/**********************************************************************************
 * RvTLSSessionDestruct - Destructs TLS/SSL session
 *
 * INPUT: 
 *	tlsSession	- new TLS session
 *	mtx			- Mutex that protects session 
 *				  structure
 *  logMgr		- log instance
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionDestruct(
	IN RvTLSSession		*tlsSession,
	IN RvMutex			*mtx,
	IN RvLogMgr			*logMgr);

/**********************************************************************************
 * RvTLSSessionClientHandshake - client side SSL/TLS handshake
 *
 * Initiates client connection to a remote TLS/SSL server.
 *
 * INPUT: 
 *	tlsSession	- created earlier TLS session
 *  certCB		- certificate callback. If is not NULL enables
 *				  certificate check by client. 
 *	tcpSock		- already connected to server TCP socket.
 *	mtx			- Mutex that protects session 
 *				  structure
 *  logMgr		- log instance
 * OUTPUT:
 * RETURN: RvStatus	- Success, WilllBlock or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionClientHandshake(
	IN  RvTLSSession			*tlsSession,
	IN  RvCompareCertificateCB	certCB,
	IN  RvSocket				tcpSock,
	IN  RvMutex					*mtx,
	IN  RvLogMgr				*logMgr);

/**********************************************************************************
 * RvTLSSessionServerHandshake - server side SSL/TLS handshake
 *
 * Responces to client handshake request.
 *
 * INPUT: 
 *	tlsSession			- created earlier TLS session
 *	tcpSock				- already accepted server TCP socket.
 *  certCB				- certification callback. If not NULL 
 *						  server requests client certification
 *	mtx			- Mutex that protects session 
 *				  structure
 *  logMgr		- log instance
 * OUTPUT:
 * RETURN: RvStatus	- Success, WilllBlock or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionServerHandshake(
	IN  RvTLSSession			*tlsSession,
	IN  RvCompareCertificateCB	certCB,
	IN  RvSocket				tcpSock,
	IN  RvMutex					*mtx,
	IN  RvLogMgr				*logMgr);


/**********************************************************************************
 * RvTLSSessionReceiveBuffer - retrieves SSL/TLS message
 *
 * Reads & decrypt SSL/TLS message. Saves retrieved message or it's part output
 * buffer
 *
 * INPUT:
 *  tlsSession       - Connected TLS session
 *  receiveBuf       - receive buffer
 *  mtx              - Mutex that protects session
 *                     structure
 *  logMgr           - log instance
 *  receiveBufLen    - receive buffer maximum length
 * OUTPUT:
 *  receiveBufLen    - length of received data
 * RETURN: RvStatus  - Success, WilllBlock, Pending or failure
 */
RVCOREAPI
RvStatus RvTLSSessionReceiveBuffer(
    IN    RvTLSSession  *tlsSession,
    IN    RvChar        *receiveBuf,
    IN    RvMutex       *mtx,
    IN    RvLogMgr      *logMgr,
    INOUT RvInt         *receiveBufLen);

/**********************************************************************************
 * RvTLSSessionReceiveBufferEx - retrieves SSL/TLS message
 *
 * Reads & decrypt SSL/TLS message. Saves retrieved message or it's part output
 * buffer
 *
 * INPUT:
 *  tlsSession       - Connected TLS session
 *  receiveBuf       - receive buffer
 *  mtx              - Mutex that protects session
 *                     structure
 *  logMgr           - log instance
 *  receiveBufLen    - receive buffer maximum length
 * OUTPUT:
 *  receiveBufLen    - length of received data
 *  pendingTlsEvents - TLS events requested by application that were blocked
 *                     early and can be processed now are added to this mask.
 * RETURN: RvStatus  - Success, WilllBlock, Pending or failure
 */
RVCOREAPI
RvStatus RvTLSSessionReceiveBufferEx(
    IN    RvTLSSession  *tlsSession,
    IN    RvChar        *receiveBuf,
    IN    RvMutex       *mtx,
    IN    RvLogMgr      *logMgr,
    INOUT RvInt         *receiveBufLen,
    OUT   RvTLSEvents   *pendingTlsEvents);

/**********************************************************************************
 * RvTLSSessionSendBuffer - sends stack message via SSL session
 *
 * Encrypts stack message and sends SSL/TLS message with encrypted stack data to
 * the SSL session peer.
 *
 * INPUT:
 *  tlsSession       - Connected TLS session
 *  sendBuf          - buffer to send
 *  sendBufLen       - length of stack data in the sendBuf
 *  mtx              - Mutex that protects session
 *                     structure
 *  logMgr           - log instance
 * OUTPUT: none
 * RETURN:
 *  RvStaus          - Success, WilllBlock or failure
 */
RVCOREAPI
RvStatus RvTLSSessionSendBuffer(
    IN  RvTLSSession    *tlsSession,
    IN  RvChar          *sendBuf,
    IN  RvInt           sendBufLen,
    IN  RvMutex         *mtx,
    IN  RvLogMgr        *logMgr);

/**********************************************************************************
 * RvTLSSessionSendBufferEx - sends stack message via SSL session
 *
 * Encrypts stack message and sends SSL/TLS message with encrypted stack data to
 * the SSL session peer.
 *
 * INPUT:
 *  tlsSession       - Connected TLS session
 *  sendBuf          - buffer to send
 *  sendBufLen       - length of stack data in the sendBuf
 *  mtx              - Mutex that protects session
 *                     structure
 *  logMgr           - log instance
 * OUTPUT:
 *  pendingTlsEvents - TLS events requested by application that were blocked
 *                     early and can be processed now are added to this mask.
 *  pSent            - how much bytes were sent
 * RETURN:
 *  RvStaus          - Success, WilllBlock or failure
 */
RVCOREAPI
RvStatus RvTLSSessionSendBufferEx(
    IN  RvTLSSession    *tlsSession,
    IN  RvChar          *sendBuf,
    IN  RvInt           sendBufLen,
    IN  RvMutex         *mtx,
    IN  RvLogMgr        *logMgr,
    OUT RvTLSEvents     *pendingTlsEvents,
    OUT RvSize_t        *pSent);

/**********************************************************************************
 * RvTLSShutdown - shutdown SSL/TLS session
 *
 * Sends shutdown request to the SSL/TLS connection peer
 *
 * INPUT: 
 *	tlsSession		- Connected TLS session
 *	mtx				- Mutex that protects session 
 *					  structure
 *  logMgr			- log instance
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionShutdown(
	IN  RvTLSSession	*tlsSession,
	IN  RvMutex			*mtx,
	IN  RvLogMgr		*logMgr);


/**********************************************************************************
 * RvTLSTranslateSelectEvents - Translates received select events to appropriate 
 * TLS event
 *
 * INPUT: 
 *	tlsSession		- Connected TLS session
 *  selEvents		- select events to be translated
 *	mtx				- Mutex that protects session 
 *					  structure
 *	logMgr			- log instance
 * OUTPUT:
 *	tlsEvents		- translated TLS events
 * RETURN: RvStatus	- Success, WilllBlock or failure
 */
RVCOREAPI 
RvStatus RvTLSTranslateSelectEvents(
	IN  RvTLSSession	*tlsSession,
	IN  RvSelectEvents	selEvents,
	IN  RvMutex			*mtx,
	IN  RvLogMgr		*logMgr,
	OUT RvTLSEvents		*tlsEvents);

/**********************************************************************************
 * RvTLSTranslateTLSEvents - Translates received TLS events to appropriate 
 * select event
 *
 * INPUT: 
 *	tlsSession		- Connected TLS session
 *  tlsEvents		- TLS event
 *	mtx				- Mutex that protects session 
 *					  structure
 *	logMgr			- log instance
 * OUTPUT: selEvents		- select events memory
 * RETURN: RvStatus	- Success, WilllBlock or failure
 */
RVCOREAPI 
RvStatus RvTLSTranslateTLSEvents(
	IN  RvTLSSession	*tlsSession,
	IN  RvTLSEvents		tlsEvents,
	IN  RvMutex			*mtx,
	IN  RvLogMgr		*logMgr,
	OUT RvSelectEvents	*selEvents);


/**********************************************************************************
 * RvTLSGetCertificateLength - retrieves ASN1 format certificate length 
 * from a certificate context received by a certificate verification callback.
 * This function used to specify stack how much memory should be allocated for 
 * the certificate.
 *
 * INPUT: 
 *	certCtx		- Certificate context
 * OUTPUT:
 *	certLen		- lenght of ASN1 certificate
 * RETURN: 
 *	RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSGetCertificateLength(
	IN	 void  *certCtx,
	OUT  RvInt *certLen);


/**********************************************************************************
 * RvTLSGetCertificate - retrieves ASN1 format certificate from a certificate 
 * context received by a certificate verification callback.
 *
 * INPUT: 
 *	certCtx		- Certificate context
 * OUTPUT:
 *  cert		- retrieved certificate. Note that user should provide 
 *                allocated memory space enought for keeping the ASN1
 *				  certificate
 * RETURN: 
 *	RvStatus	- Success or failure
 */
RVCOREAPI
RvStatus RvTLSGetCertificate(
	IN  void   *certCtx,
	OUT RvChar *cert);


/**********************************************************************************
 * RvTLSSessionGetCertificateLength - retrieves ASN1 format certificate length 
 * from a session that complete handshake
 * This function used to specify stack how much memory should be allocated for 
 * the certificate.
 *
 * INPUT: 
 *	tlsSession		- Connected TLS session
 *	mtx			- Mutex that protects session 
 *				  structure
 *  logMgr		- log instance
 * OUTPUT:
 *  certLen		- lenght of ASN1 certificate
 * RETURN: 
 *	RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionGetCertificateLength(
	IN  RvTLSSession	*tlsSession,
	IN  RvMutex			*mtx,
	IN  RvLogMgr		*logMgr,
	OUT RvInt			*certLen);

/**********************************************************************************
 * RvTLSSessionGetCertificate - retrieves ASN1 format certificate from a session 
 * after handshake is complete
 *
 * INPUT: 
 *	tlsSession	- Connected TLS session
 *	mtx			- Mutex that protects session 
 *				  structure
 *  logMgr		- log instance
 * OUTPUT:
 *  cert		- retrieved certificate. Note that user should provide 
 *                allocated memory space enought for keeping the ASN1
 *				  certificate
 * RETURN: 
 *	RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSSessionGetCertificate(
	IN  RvTLSSession	*tlsSession,
	IN  RvMutex			*mtx,
	IN  RvLogMgr		*logMgr,
	OUT RvChar			*cert);

/**********************************************************************************
 * RvTLSSessionExpose - exposes session's underlying SSL* pointer
 *
 * INPUT:
 *  tlsSession  - Connected TLS session
 *  mtx         - Mutex that protects session
 *                structure
 *  logMgr      - log instance
 * OUTPUT:
 *  underlying  - session's underlying SSL* pointer
 * RETURN:
 *  RvStatus    - Success or failure
 */
RVCOREAPI
RvStatus RvTLSSessionExpose(
    IN  RvTLSSession    *tlsSession,
    IN  RvMutex         *mtx,
    IN  RvLogMgr        *logMgr,
    OUT SSL            **underlying);

/**********************************************************************************
 * RvTLSEngineAddCertificate - adds certificate to the engine certificate chain
 *
 * INPUT: 
 *	tlsEngine	- TLS engine where certificate will be added
 *  cert		- local side certificate
 *  certLen		- local side certificate length
 *  mtx			- mutex that protects this TLS 
 *				  engine memory
 *	logMgr		- log instance
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSEngineAddCertificate(
	IN  RvTLSEngine				*tlsEngine,
	IN  RvChar					*cert,
	IN  RvInt					certLen,
	IN  RvMutex					*mtx,
	IN  RvLogMgr				*logMgr);



/**********************************************************************************
 * RvTLSEngineAddAutorityCertificate - adds certificate authority to the engine
 *
 * INPUT: 
 *	tlsEngine	- TLS engine where certificate will be added
 *  cert		- CA certificate
 *  certLen		- CA certificate length
 *  mtx			- mutex that protects this TLS 
 *				  engine memory
 *	logMgr		- log instance
 * OUTPUT: none
 * RETURN: RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSEngineAddAutorityCertificate(
	IN  RvTLSEngine				*tlsEngine,
	IN  RvChar					*cert,
	IN  RvInt					certLen,
	IN  RvMutex					*mtx,
	IN  RvLogMgr				*logMgr);

/**********************************************************************************
 * RvTLSEngineExpose - exposes underlying engine's SSL_CTX*
 *
 * INPUT:
 *  tlsEngine   - TLS engine where certificate will be added
 *  mtx         - mutex that protects this TLS
 *                engine memory
 *  logMgr      - log instance
 * OUTPUT:     
 *  underlying  - underlyingctx engine's underlying SSL_CTX* pointer
 * RETURN: RvStatus - Success or failure
 */
RVCOREAPI
RvStatus RvTLSEngineExpose(
    IN  RvTLSEngine             *tlsEngine,
    IN  RvMutex                 *mtx,
    IN  RvLogMgr                *logMgr,
    OUT SSL_CTX                **underlying);

/**********************************************************************************
 * RvTLSGetCertificateVerificationError - retrieves certificate verification error
 *
 * INPUT: 
 *	cert		- certificate context, received by vverification callback
 * OUTPUT:
 *  errString	- retrieved error string
 * RETURN: none
 */
RVCOREAPI 
void RvTLSGetCertificateVerificationError(
	IN  void	*cert,
	OUT RvChar	**errString);


/**********************************************************************************
 * RvTLSEngineCheckPrivateKey - checks the consistency of a private key with the 
 *                             corresponding certificate loaded into engine
 *
 * INPUT: 
 *	logMgr		- log instance
 *  cert		- local side certificate
 *  certLen		- local side certificate length
 *  mtx			- mutex that protects this TLS 
 *				  engine memory
 *	tlsEngine	- TLS engine where certificate will be added
 * OUTPUT: none
 * RETURN: _RvStatus	- Success or failure
 */
RVCOREAPI 
RvStatus RvTLSEngineCheckPrivateKey(
	IN  RvTLSEngine				*tlsEngine,
	IN  RvMutex					*mtx,
	IN  RvLogMgr			    *logMgr);


/**********************************************************************************
 * RvTLSSessionGetCertificate - retrieves ASN1 format certificate from a session 
 * after handshake is complete
 *
 * INPUT: 
 *	tlsSession	- Connected TLS session
 *	name		- domain name string
 *	mtx			- Mutex that protects session structure
 *  logMgr		- log instance
 * RETURN: 
 *	RvStatus	- Success or failure
 */
RVCOREAPI
RvStatus RvTLSSessionCheckCertAgainstName(
	IN  RvTLSSession	*tlsSession,
    IN  RvChar          *name,
	IN  RvMutex			*mtx,
	IN	RvChar			*memBuf,
	IN	RvInt32			memBufLen,
	IN  RvLogMgr		*logMgr);


/**********************************************************************************
 * RvTLSSessionGetSubjectAltDNS - retrieves dns names of the subject
 *
 * INPUT: 
 *	IN    sess	   - Connected TLS session
 *  IN    buf      - buffer that will contain zero-separated list of dns names
 *  INOUT pBufSize - pointer to the size of buffer. On return contains requested buffer size
 *  OUT   pNitems  - pointer to the size of the list
 *  logMgr		-    log instance
 * RETURN: 
 *	RV_OK - for success
 *  RV_ERROR_OUTOFRESOURCES - not enough buffer space. In this case *pbufSize will hold the requested
 *                            buffer size.
 *  
 */
RVCOREAPI
RvStatus RvTLSSessionGetSubjectAltDNS(RvTLSSession *sess, RvChar *buf, RvSize_t *pbufSize, RvSize_t *pNitems, RvLogMgr *logMgr);

RVCOREAPI
RvStatus RvX509GetSubjectAltDNS(X509 *cert, RvChar *buf, RvSize_t *pbufSize, RvSize_t *pNitems);

#if RV_TLS_ENABLE_RENEGOTIATION

/**********************************************************************************
 * RvTLSSessionRenegotiate - renegotiate TLS session
 *
 * INPUT: 
 *	tlsSession	- Connected TLS session
 *	forced		- if RV_FALSE - renegotiation process will be completed during 
 *                I/O operation. Currently unused
 *                if RV_TRUE - no applicationI/O is possible during renegotiation process,
 *                e.g. next message from the peer should be handshake protocol message
 *	mtx			- Mutex that protects session structure
 *  logMgr		- log instance
 * RETURN: 
 *	RvStatus	- Success, WilllBlock or failure
 *                  
 */ 
       
RVCOREAPI
RvStatus RvTLSSessionRenegotiate(RvTLSSession *rvSession, RvBool forced, RvMutex *mtx, RvLogMgr *logMgr);

/**********************************************************************************
 * RvTLSSessionRenegotiateEx - renegotiate TLS session
 *
 * INPUT: 
 *	tlsSession	- Connected TLS session
 *	mtx			- Mutex that protects session structure
 *  logMgr		- log instance
 * RETURN: 
 *	RvStatus	- Success, WilllBlock or failure
 *                  
 */ 
       
RVCOREAPI
RvStatus RvTLSSessionRenegotiateEx(RvTLSSession *tlsSession, RvMutex *mtx, RvLogMgr *logMgr);

/**********************************************************************************
 * RvTLSSessionRenegotiationInProgress - check if TLS session is beiung renegotiated
 *
 * INPUT: 
 *	tlsSession	- Connected TLS session
 *	mtx			- Mutex that protects session structure
 *  logMgr		- log instance
 * OUTPUT:
 *  pbInProgress - RV_TRUE if it is, RV_FALSE - otherwise
 * RETURN: 
 *	RvStatus	- Success, WilllBlock or failure
 *                  
 */ 

RVCOREAPI
RvStatus RvTLSSessionRenegotiationInProgress(
            RvTLSSession *tlsSession, RvMutex *mtx, RvLogMgr *logMgr,
            OUT RvBool *pbInProgress);

#endif /*#if RV_TLS_ENABLE_RENEGOTIATION*/

#if (RV_TLS_AUTO_SET_OS_CALLBACKS == RV_NO)    

/**********************************************************************************
 * RvTLSSetLockingCallback - sets/unsets TLS locking callback to RVSN function.
 *
 * INPUT: 
 *	set - if RV_TRUE the callback will be set to RadVision locking callback otherwise 
 *        the callback will be removed.
 * RETURN: 
 *	None.
 *                  
 */ 
RVCOREAPI
void RvTLSSetLockingCallback(RvBool set);

/**********************************************************************************
 * RvTLSSetThreadIdCallback - sets/unsets TLS thread ID callback to RVSN function.
 *
 * INPUT: 
 *	set - if RV_TRUE the callback will be set to RadVision thread id callback otherwise 
 *        the callback will be removed.
 * RETURN: 
 *	None.
 *                  
 */ 
RVCOREAPI
void RvTLSSetThreadIdCallback(RvBool set);


#endif /*(RV_TLS_AUTO_SET_OS_CALLBACKS == RV_YES)*/


#endif /*(RV_TLS_TYPE != RV_TLS_NONE) */

#if defined(__cplusplus)
}
#endif 

#endif

