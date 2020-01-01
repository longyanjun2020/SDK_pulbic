
/**
 * @file nccwhttp.h
 * Wireless HTTP Service Layer
 *
 * Service API exposed by the Wireless HTTP .
 *
 * <!-- #interface list begin -->
 * \section nccwhttp Interface
 * - NCCWhttp_init()
 * - NCCWhttp_open()
 * - NCCWhttp_read()
 * - NCCWhttp_close()
 * - NCCWhttp_initCookieList()
 * - NCCWhttp_freeCookieList()
 * - NCCWhttp_freeAuthList()
 * - NCCWhttp_getCookieStr()
 * - NCCWhttp_setCookieStr()
 * - NCCWhttp_deleteFileCookies()
 * - NCCWhttp_addCookie()
 * - NCCWhttp_getCookieData()
 * - NCCWhttp_delCookieByHostName()
 * - NCCWhttp_addAuth()
 * - NCCWhttp_deleteAuth()
 * - NCCWhttp_getAuthData()
 * - NCCWhttp_getServerCertLen()
 * - NCCWhttp_TLSReadServerCertificate()
 * - NCCWhttp_TLSGetCipherSuiteName()
 * - NCCWhttp_TLSGetSecureProtocol()
 * <!-- #interface list end -->
 */

#ifndef __NCC_WHTTP_H__
#define __NCC_WHTTP_H__

#include "ncc_types.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "wap_config.h"
#include "ncccommon_list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**< File size limitation for downloading file: <2GB, maximum (signed) int32 value */
#define HTTP_MAX_DOWNLOAD_SIZE    (2147483647) 

/*debug msg*/
#define HTTP_TRACE(TYPE, FMT)

/* WHTTP AUTH  MEMORY CONFIG */
#define WHTTP_COOKIE_MALLOC     NCCCommon_malloc
#define WHTTP_COOKIE_FREE          NCCCommon_free

/* WHTTP AUTH  MEMORY CONFIG */
#define WHTTP_AUTH_MALLOC     NCCCommon_malloc
#define WHTTP_AUTH_FREE          NCCCommon_free

/* secure protocol */
#define HTTP_SECURE_SSL3    0
#define HTTP_SECURE_TLS1    1

/*whttp module macro definition*/
/*keep-alive macro*/
#define HTTP_NOTALIVE       0
#define HTTP_KEEPALIVE      1
#define HTTP_NANO_MAX_REDIR     10      /* The max count of redirection */
#ifdef NCC_WAP_SUPPORT_WIFI
#define HTTP_NANO_IN_BUFFER_CHU 102400    /* The receive chunk buffer length */
#define HTTP_NANO_CHUNK         1024*40     /* The little chunk length of HTTP*/
#else
#define HTTP_NANO_IN_BUFFER_CHU 10240    /* The receive chunk buffer length */
//#define HTTP_NANO_CHUNK         2048     /* The little chunk length of HTTP*/
#define HTTP_NANO_CHUNK         1024*4     /* The little chunk length of HTTP*/
#endif

/* request type */
#define HTTP_REQUEST        0
#define HTTPS_REQUEST       1
#define HTTP_REQUEST_TLS    2
#define HTTPS_RESPONSE      3
#define HTTPS_OK            4

/* returned value of http module*/
#define HTTP_PENDING        -2
#define HTTP_OK              0
#define HTTP_ERROR          -1
/*Error code returned from NCCWhttp_open*/
#define HTTP_ERR_BASE       100
#define HTTP_ERR_PARSEIP        (HTTP_ERR_BASE + 1) /*Error when Parser IP*/
#define HTTP_ERR_CONNECT        (HTTP_ERR_BASE + 2) /*Error when connect to host*/
#define HTTP_ERR_SEND           (HTTP_ERR_BASE + 3) /*Error when send data to host*/
#define HTTP_ERR_MORE_REDIR     (HTTP_ERR_BASE + 4) /*Count of the redirections is out of limit*/
#define HTTP_ERR_PARAMETER      (HTTP_ERR_BASE + 5) /*The parameter is wrong*/
#define HTTP_ERR_ABORT          (HTTP_ERR_BASE + 6) /*User abort the request*/
#define HTTP_ERR_NETNOTINITED   (HTTP_ERR_BASE + 7) /*Net has NOT initialed*/
#define HTTP_ERR_MALLOCFAIL     (HTTP_ERR_BASE + 8) /*Malloc memory fail*/
#define HTTP_ERR_PROTOCOL       (HTTP_ERR_BASE + 9) /*Protocol error,maybe not http or no hostname*/
#define HTTP_ERR_METHODNS       (HTTP_ERR_BASE + 10) /*The method not surpport*/
#define HTTP_ERR_NO_TLS         (HTTP_ERR_BASE + 11) /*Protocol error,NOT support the TLS*/
#define HTTP_ERR_LAUNCH_APP     (HTTP_ERR_BASE + 12) /*Launch external app to open specific file type*/

#define HTTP_STATUS_BASE_300       300
#define HTTP_STATUS_REDIRECT   (HTTP_STATUS_BASE_300 + 1) /*HTTP 302, 307 page redirection*/

/* http state in NCCWhttp_open*/
typedef enum{
    HTTP_STARTING = 0x0,    /*Waiting state,the begin state*/
    HTTP_QUERYIP,           /*Query proxy or host ip*/
    HTTP_CONNETING,         /*Connect to host*/
    HTTP_QSBUILD,           /*Build the query string*/
    HTTP_SENDING,           /*Send data to host*/
    HTTP_RECEIVING,         /*Receive HEAD data from host*/
}HTSTAT;

/*HTTP status codes*/
#define HTTP_SC_CONTINUE            100
#define HTTP_SC_SWITCHING_PROTOCOLS 101

#define HTTP_SC_OK                  200
#define HTTP_SC_CREATED             201
#define HTTP_SC_ACCEPTED            202
#define HTTP_SC_NON_AUTHORITATIVE   203
#define HTTP_SC_NO_CONTENT          204
#define HTTP_SC_RESET_CONTENT       205
#define HTTP_SC_PARTIAL_CONTENT     206

#define HTTP_SC_MULT_CHOICE         300
#define HTTP_SC_MOVED_PERM          301
#define HTTP_SC_FOUND               302
#define HTTP_SC_SEE_OTHER           303
#define HTTP_SC_NOT_MODIFIED        304
#define HTTP_SC_USE_PROXY           305
#define HTTP_SC_TEMP_REDIRECT       307

#define HTTP_SC_BAD_REQUEST         400
#define HTTP_SC_UNAUTHORIZED        401
#define HTTP_SC_PAYMENT_REQUIRED    402
#define HTTP_SC_FORBIDDEN           403
#define HTTP_SC_NOT_FOUND           404
#define HTTP_SC_BAD_METHOD          405
#define HTTP_SC_NOT_ACCEPTABLE      406
#define HTTP_SC_PROXY_AUTH          407
#define HTTP_SC_REQUEST_TIMEOUT     408
#define HTTP_SC_CONFLICT            409
#define HTTP_SC_GONE                410
#define HTTP_SC_LENGTH_REQUIRED     411
#define HTTP_SC_PRECON_FAILED       412
#define HTTP_SC_ENTITY_TOO_LARGE    413
#define HTTP_SC_REQURI_TOO_LONG     414
#define HTTP_SC_UNSUPPORTED_TYPE    415
#define HTTP_SC_UNSUPPORTED_RANGE   416
#define HTTP_SC_EXPECT_FAILED       417

#define HTTP_SC_INTERNAL_ERROR      500
#define HTTP_SC_NOT_IMPLEMENTED     501
#define HTTP_SC_BAD_GATEWAY         502
#define HTTP_SC_SRV_UNAVAILABLE     503
#define HTTP_SC_GATEWAY_TIMEOUT     504
#define HTTP_SC_UNSUPPORTED_VERSION 505

/************************ Structure Definition ****************************/

typedef void   *(*htMallocFunc)(uint32_t);

typedef void    (*htFreeFunc)(void *);

/**
 * \param param1 This parameter is realm.
 * \param param2 This parameter is user name.
 * \param param3 This parameter is password.
 * \return Return 1 if success and user not cancel; otherwise return 0.
 */
typedef int32_t    (*htAuthGetFunc)(int8_t *, int8_t **,int8_t **);

/**
 * \param param parameter for SSL/TLS. 1 for go to https domain,0 for out of the https domain
 * \return Return 1 if success and user not cancel; otherwise return 0.
 */
typedef int32_t    (*htAlertHsFunc)(int32_t);

typedef struct HTTPCtxt HTTPCTXT;

/// HTTP Context
struct HTTPCtxt
{
    int8_t *protocol;   /**< the protocol name */
    int8_t *hostname;/**<  the host name */
    uint32_t fpipaddr;  /**< fast peer ip address*/
    int8_t  *httpproxy;		/* http proxy name, added by will.wang*/
    int32_t httpproxyport;	/* http proxy port*, added by will.wang*/
    int32_t  fpport;    /**< fast peer port*/
    int16_t httpsf; /**< the flag of https,see request type upstair*/
    int16_t  keepalivef;/**< the flag means the connect is kept alive*/
    int32_t  port;      /**<  the port */
    int8_t *path;       /**<the path within the URL */
    int32_t  fd;        /**<the file descriptor for the socket */
    int32_t  state;     /**< WRITE / READ / CLOSED */
    int8_t *out;        /**< buffer sent (zero terminated) */
    int8_t *outptr;     /**<index within the buffer sent */
    int32_t outlen;     /**< the length of the outptr buffer*/
    int8_t *responseHeaders;     /**<the response headers from server */
    int8_t *in;     /**<the receiving buffer */
    int8_t *content;    /**< the start of the content */
    int8_t *inptr;          /**< the next byte to read from network */
    int8_t *inrptr; /**< the next byte to give back to the client */
    int32_t  inlen;     /**<len of the input buffer */
    int32_t  last;      /**<return code for last operation */
    int32_t  returnValue;   /**< the protocol return value */
    int32_t  ContentLength;/**< specified content length from HTTP header */
    int32_t  RecvLen;       /**< specified content length from HTTP header */
    int8_t *charset;        /**< charset of contenttype */
    int8_t *language;       /**< language header */
    int8_t *contentType;    /**< the MIME type for the input */
    int8_t *contentName;    /**< the file name for the download content */
    int8_t *location;       /**< the new URL in case of redirect */
    int8_t *authHeader; /**< contents of {WWW,Proxy}-Authenticate header */
    CommonList *auth_list;      /**< The authorization informations list*/
    CommonList *cookie_list;    /**< The cookie information list*/
    int8_t *EncodeType; /**< Encoding type */
    int32_t chunkedflag;    /**< Transfer-Encoding is chunked */
    int32_t chunkedlen; /**<The length of the chunked */
    int32_t needcleanflag;	/*whether need clean pre-connection data or not,*/ //will.wang
    int8_t *upgrade;        /**< tls Upgrade: header*/
    int32_t tlsCertLen;     /**< length of server certificate */
    int32_t tlsSecureProtocol;/**< server certificate */
    uint8_t *tlsCertificate;/**< cipher suite name */
    uint8_t *tlsCipherSuiteName;/**< secure protocol of current session */
    int32_t nbRedirects;    /**<Redirections. must be less than five(limitation) */
    int32_t cache_age;      /**< cache age,age header*/
    int32_t cache_date;     /**< date header*/
    int32_t cache_expires;  /**< cache expiration time*/
    int32_t cache_maxAge;   /**< cache max-age,Cache-control:max-age header*/
    int32_t cache_nocachef; /**< cache-control:no-cache without parameter*/
    int32_t cache_lmodify;  /**< cache last modify date*/
    int32_t cache_must_revalf; /**< flag of cache must-revalidate:1 means must,0 means not must*/
    int8_t *cache_etag;     /**< validator in validation model*/
    htMallocFunc    htmalloc;   /**<Callback function for memory malloc */
    htFreeFunc      htfree;     /**<Callbakc function for memory free */
    htAuthGetFunc   htAuthGet;  /**<Callback function for  get Authentication data*/
    htAlertHsFunc   htAlertHttps;/**<Alert function for SSL/TLS */
	
#ifdef HTTP_HEADER_REFERER
	int8_t *referer;			/*<referer>*///added by will.wang
#endif
    int32_t appId;
} ;

/**
 * Initialize HTTP context.
 * \param   cookie_list     cookie list
 * \param   auth_list       Auth list
 * \param   keepaliveflag   flag to KeepAlive
 * \param   pmalloc         mem allocate function passed to here
 * \param   pfree           mem free function passed to here
 * \param   pAuthGet        get Authorization information function
 * \param   pAlertHs        alert the HTTPS function
 * \return  Return a pointer to the context if success;otherwise return NULL.
 */
void *NCCWhttp_init(
    CommonList *cookie_list,
    CommonList *auth_list,
    int8_t keepaliveflag,
    htMallocFunc pmalloc,
    htFreeFunc pfree,
    htAuthGetFunc pAuthGet,
    htAlertHsFunc pAlertHs,
    int32_t appId);

/**
 * Open a HTTP instance.
 * \param   hc          HTTP context
 * \param   method      HTTP method
 * \param   url         url that HTTP to get
 * \param   methoddata  the data of the method passed to here
 * \param   contenttype content header type
 * \param   datalen     the length of the method data
 * \param   headers     the special headers the up app want to send.
 * \param   httpproxy   the HTTP proxy the app used
 * \param   httpproxyport   the HTTP proxy port the app used
 * \return  Return the status of the HTTP instance(See  NCCWhttp_open status definition for the details).
 */
int32_t NCCWhttp_open(
    void    *hc,
    const int8_t    *method,
    int8_t  *url,
    int8_t  *methoddata,
    int32_t datalen,
    int8_t *contenttype,
    int8_t  *headers,
    int8_t  *httpproxy,
    int32_t httpproxyport);

/**
 * Read the body data response from server.
 * \param hc        the http context.
 * \param buffer    the buffer for receive data.
 * \param len       the max length of the data want to receive.
 * \return
 *          <li>If process has not finished, return HTTP_PENDING;</li>
 *          <li>If open fail,return HTTP_ERROR;</li>
 *          <li>If receiving data is finished, return  HTTP_OK;</li>
 *          <li> > 0 the received data length.</li>
 */
int32_t NCCWhttp_read(void *hc, int8_t *buffer, int32_t len);

/**
 * Close the http context.
 * \param hc    the http context
 * \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWhttp_close(void    *hc);

/**
 * Raise flag to download HTTP streaming file other than launching video player.
 */
void NCCWhttp_setDownloadHttpStreamingFile(void);

/**
 * Get the flag of process type of HTTP streaming file.
 */
int32_t NCCWhttp_getDownloadHttpStreamingFile(void);

/**
 * Reset flag to download HTTP streaming file by querying user whether to launch video player.
 */
void NCCWhttp_reSetDownloadHttpStreamingFile(void);

/**
 * Check if need to download HTTP streaming file by querying user whether to launch video player.
 */
int32_t NCCWhttp_checkDownloadHttpStreamingFile(HTTPCTXT *hcp, HTTPCTXT *ctxt, int8_t  *httpproxy);

/**
 * Initialize the cookie list.
 * \return  Return a handle of cookie list if success;otherwise return NULL.
 */
void *NCCWhttp_initCookieList(void);

/**
 * Free the cookie list.
 * \param cookie_list   cookie list .
 * \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWhttp_freeCookieList(CommonList *cookie_list);

/**
 * Authorization List initialize
 * \return  Return a pointer to the authentication list if success;otherwise return NULL.
 */
void *NCCWhttp_initAuthList(void);

/**
 * Free the Authentication information.
 * \param auth_list     auth list.
 * \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWhttp_freeAuthList(CommonList *auth_list);

/**
 * Get a cookie value of specified host.
 * \param cookie_list   list of cookies
 * \param hostname  host name
 * \return   Return a pointer to the cookie data if success;otherwise return NULL.
 */
int8_t *NCCWhttp_getCookieStr(
    CommonList *cookie_list,
    int8_t *hostname);

/**
 * Set cookie value.
 * \param cookie_list   list of cookies
 * \param hostname  host's name
 * \param hostpath      host's path
 * \param value     the string which will be set in cookie
 * \return Return 0 if success;otherwise return -1.
 */
void NCCWhttp_setCookieStr(
    CommonList *cookie_list,
    const int8_t *hostname,
    const int8_t *hostpath,
    int8_t *value);

/**
 * Delete cookie.
 * \param cookie_list   list of cookies
 * \return  Return TRUE if success;otherwise return FALSE.
 * \attention now not support.
 */
int32_t NCCWhttp_deleteFileCookies(CommonList *cookie_list);

/**
 * Add a cookie.
 * \param cookie_list   cookie list .
 * \param hostname  cookie's hostname.
 * \param hostpath      cookie's hostpath.
 * \param value     cookie string.
 * \param cookietype    cookie's type(Set-Cookie:&Set-Cookie2).
 * \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWhttp_addCookie(
    CommonList *cookie_list,
    const int8_t *hostname,
    const int8_t *hostpath,
    int8_t *value,
    int32_t cookietype);

/**
 * Get the cookie string and add to header.
 * \param cookie_list   cookie list .
 * \param hostname  cookie's hostname.
 * \return   Return a pointer to the packeted cookie data if success;otherwise return NULL.
 */
int8_t *NCCWhttp_getCookieData(
    CommonList *cookie_list,
    int8_t *hostname);

/**
 * Get the cookie string need to send to server
 * \param cookie_list   cookie list .
 * \param hostname  cookie's hostname.
 * \param hostPath    cookie's hostpath
 * \return   Return a pointer to the packeted cookie data if success;otherwise return NULL.
 */ //added by will.wang
int8_t *NCCWhttp_GetCookieDataToSend(CommonList *cookie_list, int8_t *hostname, int8_t *hostPath);


/**
 * Delete the cookie by hostname.
 * \param cookie_list   cookie list .
 * \param hostname  cookie's hostname.
 * \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWhttp_delCookieByHostName(
    CommonList *cookie_list,
    int8_t *hostname);

/**
 * Add the Authentication information.
 * \param auth_list     auth list .
 * \param realm     the realm for Authentication
 * \param user          user name
 * \param pwd           password
 * \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWhttp_addAuth(CommonList *auth_list,
                      int8_t * realm,
                      int8_t * user,
                      int8_t *pwd);

/**
 * Delete the authorization information of the specified realm.
 * \param auth_list     auth list .
 * \param realm     the realm for Authentication
 * \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWhttp_deleteAuth(CommonList *auth_list,
                         int8_t * realm);

/**
 * Get the Authentication information of the specified realm. And the data will return in following format:
 *  "Basic + base64 string of user-password".
 * \param auth_list     auth list .
 * \param realm     the realm for Authentication.
 * \return  Return a pointer to the authentication data if success;otherwise return NULL.
 */
int8_t *NCCWhttp_getAuthData(CommonList *auth_list,
                           int8_t * realm);

/**
 * Get the length of server certificate
 * \param hc     http context.
 * \return  Return the length of the server certificate.
 */
int32_t NCCWhttp_getServerCertLen(void *hc);

/**
 * Read the server certificate
 * \param hc     http context.
 * \param buf    Buffer where the certificate to be copied.
 * \param len    Length of the buffer in bytes.
 * \return
 *  HTTP_OK     Successfully.
 *  HTTP_ERROR  Failed.
 */
int32_t NCCWhttp_TLSReadServerCertificate(void* hc,uint8_t *buf,int32_t len);

/**
 * Returns the cipher suite name of the HTTPS connection
 * \param hc     HTTP context.
 * \param buf    Buffer where the name is to be copied.
 * \param len    Length of the buffer in bytes.
 * \return
 *  HTTP_OK     success.
 *  HTTP_ERROR  failed.
 */
int32_t NCCWhttp_TLSGetCipherSuiteName(void* hc,uint8_t* buf,int32_t len);

/**
 * Get the secure protocol of current session
 * \param hc     http context.
 * \return  Return the constant value of secure protocol or error.
 */
int32_t NCCWhttp_TLSGetSecureProtocol(void* hc);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_WHTTP_H__ */
