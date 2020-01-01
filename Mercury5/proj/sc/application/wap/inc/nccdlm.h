
/**
 * @file nccdlm.h
 * Download Layer Manager Service Layer
 *
 * Service API exposed by the Download Layer Manager.
 *
 * <!-- #interface list begin -->
 * \section nccdlm Interface
 * - NCCBrw_dlm_checkSession()
 * - NCCBrw_dlm_openSession()
 * - NCCBrw_dlm_setSessionOption()
 * - NCCBrw_dlm_closeSession()
 * - NCCBrw_dlm_closeAllRequest()
 * - NCCBrw_dlm_openURI()
 * - NCCBrw_dlm_openRequest()
 * - NCCBrw_dlm_setRequstOption()
 * - NCCBrw_dlm_sendRequst()
 * - NCCBrw_dlm_read()
 * - NCCBrw_dlm_readOnce()
 * - NCCBrw_dlm_getStatus()
 * - NCCBrw_dlm_closeRequest()
 * - NCCBrw_dlm_getRecvLen()
 * - NCCBrw_dlm_getSendLen()
 * - NCCBrw_dlm_getRespHeaderPtr()
 * - NCCBrw_dlm_getRespHeaderInt()
 * <!-- #interface list end -->
 */

/**
 * @addtogroup DLM_MODULE
 *  download layer manager file
 * @{
 */

#ifndef __NCC_DLM_H__
#define __NCC_DLM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ncc_types.h>
#include <dlm_respheader.h>
#include <nccwhttp.h>
#include <nccport_time.h>
#include <nccwsp.h>
#include <wsp_sock2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* for test
#ifdef IS_RELEASE_VERSION
#define NO_CHECK_SESSION
#endif
 */

/**
 * \name DLM_CONSTANT_MACRO
 * constant define
 */
/*@{*/
/* max timeout of protocol handle in DLM: 10 second*/
//#define DLM_MAX_TIMEOUT         40
#define DLM_MAX_TIMEOUT         80
/* max timeout of the buffer conserved by DLM: 10 second*/
#define DLM_MAX_TIME_BUFHOLD        40
/* max requests(not avtive) that keepalived*/
#define DLM_MAX_KEEPALIVE_CONN      5
/* default MAX_BUFFERSIZE is 50K*/
#define DLM_DEFAULT_MAXBUFFERSZ     50*1024

/* default max port number*/
#define DLM_MAXPORTNUMBER       65535
/* max loop times,see NCCBrw_dlm_CheckSession in dlm.c*/
#define DLM_MAX_LOOPTIMES       5
/*@}*/

/**
 * \name DLM_PROTO_TYPE_MACRO
 * the protocol surpport
 */
/*@{*/
#define DLM_HTTP            0
#define DLM_WAP1DOT2            1
#define DLM_FILE            2
/*@}*/

/**
 * \name DLM_HTTP_METHOD_MACRO
 * METHOD of HTTP1.1
 */
/*@{*/
#define DLM_HTTP_GET            0
#define DLM_HTTP_POST           1
#define DLM_HTTP_PUT            2
#define DLM_HTTP_HEAD           3
#define DLM_HTTP_OPTIONS        4
#define DLM_HTTP_DELETE         5
#define DLM_HTTP_TRACE          6
#define DLM_HTTP_CONNECT        7
/*@}*/

#define DLM_OK              0
#define DLM_ERR             -1
#define DLM_PENDING         -2

/**
 * \name DLM_STATUS_MACRO
 * the status
 */
/*@{*/
#define DLM_WAITING         -1
#define DLM_QUERYIP         (DLM_WAITING - 2)/* status:query ip,careful: the value is -3,the following is same*/
#define DLM_CONNETING           (DLM_WAITING - 3)/* status:connection to host*/
#define DLM_SENDING         (DLM_WAITING - 4)/* status:send data*/
#define DLM_RECEIVINGHEADER     (DLM_WAITING - 5)/* status:receiving header data*/
#define DLM_RECEIVINGDATA       (DLM_WAITING - 6)/* status:receiving contend data*/
#define DLM_DATAOK          (DLM_WAITING - 7)/* status:receiving data ok*/
#define DLM_DATAREADED          (DLM_WAITING - 8)/* status: data have been read*/

#define DLM_ERR_QUERRYIP        (DLM_WAITING - 9)/* error status: error querying ip */
#define DLM_ERR_CONNET          (DLM_WAITING - 10)/* error status: error connecting to host*/
#define DLM_ERR_SEND            (DLM_WAITING - 11)/* error status: error sending data*/

#define DLM_ERR_RECEIVE         (DLM_WAITING - 12)/* error status: error recieving data*/
#define DLM_ERR_TIMEOUT         (DLM_WAITING - 13)/* error status: time out*/
#define DLM_ERR_OTHER           (DLM_WAITING - 14)/* error status: others,see the following*/

#define DLM_ERR_OVER_MAXBUFFERSZ    (DLM_ERR_OTHER - 1)/* error: overrun receive buffer*/
#define DLM_ERR_INVALID_PARAMETER   (DLM_ERR_OTHER - 2)/* error: invalid parameters*/
#define DLM_ERR_MALLOC_FAILED       (DLM_ERR_OTHER - 3)/* error: allocate memery failed*/
#define DLM_ERR_ALREADY_ACTIVE      (DLM_ERR_OTHER - 4)/* error: request have been active */
#define DLM_ERR_TYPE_WRONG      (DLM_ERR_OTHER - 5)/* error: read-mode type wrong when read data*/
#define DLM_ERR_NOT_SURPORT_TLS     (DLM_ERR_OTHER - 6)/* error: NOT support the TLS */
#define DLM_ERR_LAUNCH_APP     (DLM_ERR_OTHER - 7)/* error: launch other app to access specific file type */
/*@}*/

typedef struct T_DLM_queue T_DLM_Queue;

typedef struct T_DLM_Session *T_DLM_SessionHandle;
typedef struct T_DLM_ReqNode *T_DLM_ReqNodeHandle;
/**
 * structure of queue
 */
struct T_DLM_queue {
    T_DLM_Queue *pre;
    T_DLM_Queue *next;
};

/*session options*/
#define DLM_HTTP_PROXY_HOST     0
#define DLM_HTTP_PROXY_PORT     (DLM_HTTP_PROXY_HOST + 1)
#define DLM_WSP_PROXY_HOST      (DLM_HTTP_PROXY_HOST + 2)
#define DLM_WSP_PROXY_PORT      (DLM_HTTP_PROXY_HOST + 3)

#define DLM_CALLBACK_FUNC_GETAUTH   (DLM_HTTP_PROXY_HOST + 5)
#define DLM_CALLBACK_FUNC_ALERTHS   (DLM_HTTP_PROXY_HOST + 6)
#define DLM_COOKIE_LIST         (DLM_HTTP_PROXY_HOST + 7)
#define DLM_AUTH_LIST           (DLM_HTTP_PROXY_HOST + 8)

/* request options*/
#define DLM_KEEP_ALIVE 0
#define DLM_RECV_MAX_TIMEOUT        (DLM_KEEP_ALIVE + 1)
/*not  fit to wsp,so can't use when the protocol is wsp*/
#define DLM_MAX_RECVBUFFER_SIZE     (DLM_KEEP_ALIVE + 2)
#define DLM_NOTIFY_READ_ONCE        (DLM_KEEP_ALIVE + 3)

/**
 * request node structure of the DLM
 */
#define DLM_REQUEST_ISACTIVATE      0x1
#define DLM_REQUEST_KEEPALIVE       0x2
/*pre notify the DLM that the app will read data in whole buffer,
this will save time when the header have Content-length field*/
#define DLM_REQUEST_READONCE        0x4

#define DLM_ACTIVE_QUEUE        1
#define DLM_READY_QUEUE         2
#define DLM_FINISHED_QUEUE      3
#define DLM_KPIDLE_QUEUE        4

struct T_DLM_ReqNode {
    T_DLM_ReqNodeHandle pre;
    T_DLM_ReqNodeHandle next;
    T_DLM_SessionHandle sessionId;
    int32_t queueTag;
    int32_t status;
    int32_t flags;
    int32_t maxBufferSize;
    int32_t recvBufferAvailSize;
    int8_t *recvBuffer;
    int8_t *recvBufferCurr;
    int32_t sendLen;
    int32_t recvLen;
    int32_t recvTimeStamp;
    int32_t timeStamp;
    int32_t maxTimeOut;/* for connect(),send(),recv() timeout */
    int32_t proType;

    /* next fields  are lower protocol related: parameters */
    int32_t proContext;
    int32_t method;
    int8_t *uriAddr;
    int8_t *headers;
    int8_t *methodData;
    int32_t methodDataLen;
    int8_t *methodDataContentType;

    /*return messages:return headers */
    T_DLM_ResHeader *resHeader;
};

/**
 * session structure of the DLM
 */
struct T_DLM_Session {
    T_DLM_SessionHandle pre;
    T_DLM_SessionHandle next;
    void *hWsp;/**Wsp instance handle*/
    int32_t maxNumOfActiveRequest;
    int32_t numOfActiveRequest;
    int32_t numOfRequestIdle;
    int8_t *httpProxy;
    int32_t httpProxyPort;
    int8_t *wspProxy;
    int32_t wspProxyPort;
    CommonList *cookieList;
    CommonList *authList;
    htAuthGetFunc authGetFunc;
    htAlertHsFunc alertHttpsFunc;
    T_DLM_ReqNodeHandle activeReqLink;
    T_DLM_ReqNodeHandle readyReqLink;
    T_DLM_ReqNodeHandle finishedReqLink;
    T_DLM_ReqNodeHandle keepAliveIdleReqLink;
    int32_t appId;
};

#ifdef NO_CHECK_SESSION
/* check the DLM session*/
void NCCBrw_dlm_checkSession(void);
#endif

/**
 * Create the DLM session
 * \param   limitNumberOfReq    limit of the requests
 * \return <ul>
 *          <li>success: not NULL pointer
 *          <li>fail: NULL pointer
 *          </ul>
 */
T_DLM_SessionHandle NCCBrw_dlm_openSession(int32_t limitNumberOfReq, int32_t appId);

/**
 * set options of the DLM session
 * \param   sessionHandle   DLM session id
 * \param   option          options to set
 * \param   value           the value of the option
 * \return <ul>
 *          <li>success: DLM_OK
 *          <li>fail: other situations
 *          </ul>
 */
int32_t NCCBrw_dlm_setSessionOption(T_DLM_SessionHandle sessionHandle,
                               int32_t option, int32_t value);

/**
 *  Destroy the DLM session
 * \param   sessionId   DLM session id
 * \return NULL
 */
void NCCBrw_dlm_closeSession(T_DLM_SessionHandle sessionHandle);

/**
 *  Close all the requests of the session
 * \param   sessionHandle           DLM session id
 * \return NULL
 */
void NCCBrw_dlm_closeAllRequest(T_DLM_SessionHandle sessionHandle);

/**
 *  Open a simple request of the DLM session
 * the request of the HTTP is just the "GET"
 * the wsp can only use the NCCBrw_dlm_ReadOnce to read the buffer,
 * and must set the setoption:DLM_NOTIFY_READ_ONCE,and
 * DLM_MAX_RECVBUFFER_SIZE is not work.
 * \param   sessionHandle           DLM session handle
 * \param   proType                 the type of the protocol
 * \param   uriAddr                 url address or the FILE uri
 * \param   headers                 HTTP headers
 * \return <ul>
 *          <li>success: not NULL pointer
 *          <li>fail: NULL pointer
 *          </ul>
 */
T_DLM_ReqNodeHandle NCCBrw_dlm_openURI(T_DLM_SessionHandle sessionHandle,
                                  int32_t proType,
                                  const int8_t * uriAddr,
                                  const int8_t * headers);

/**
 *  Open a request of the DLM session
 * use this funciton with wsp is same as the NCCBrw_dlm_OpenURI
 * \param   sessionHandle           DLM session handle
 * \param   proType                 the type of the protocol
 * \param   uriAddr                 url address or the FILE uri
 * \param   headers                 HTTP headers
 * \param   method                  HTTP method
 * \param   methodData              HTTP method data if have
 * \param   methodDataLen           length of the HTTP method data
 * \param   methodDataContentType   ContentType of the HTTP method data
 * \return <ul>
 *          <li>success: not NULL pointer
 *          <li>fail: NULL pointer
 *          </ul>
 */
T_DLM_ReqNodeHandle NCCBrw_dlm_openRequest(T_DLM_SessionHandle sessionHandle,
                                      int32_t proType,
                                      const int8_t * uriAddr,
                                      const int8_t * headers,
                                      const int32_t method,
                                      const int8_t * methodData,
                                      const int32_t methodDataLen,
                                      const int8_t * methodDataContentType);

/**
 *  Set options of the DLM request
 * be carefule with wsp.
 * called before NCCBrw_dlm_SendRequst,or if the request is active,will can
 * not set options any more.
 * \param   requestHandle   DLM request handle
 * \param   option          options to set
 * \param   value           the value of the option
 * \return <ul>
 *          <li>success: DLM_OK
 *          <li>fail: other situations
 *          </ul>
 */
int32_t NCCBrw_dlm_setRequstOption(T_DLM_ReqNodeHandle requestHandle,
                              int32_t option, int32_t value);

/**
 * Trigger the request
 * but not really send the requst.only drive it when check session.
 * \param   requestHandle   DLM request handle
 * \return <ul>
 *          <li>success: DLM_OK
 *          <li>fail: other situations
 *          </ul>
 */
int32_t NCCBrw_dlm_sendRequst(T_DLM_ReqNodeHandle requestHandle);

/**
 *  Read data for the request of the DLM session.
 * the buffer is allocated by caller, and will return the length of
 * the data copied to buffer. or return the status codes when error.
 * \param   requestHandle   request handle
 * \param   buffer      buffer for data reading.
 * \param   len         buffer length want to read,and return the length read
 * \return <ul>
 *          <li>fail:the status of the request.
 *          </ul>
 */
int32_t NCCBrw_dlm_read(T_DLM_ReqNodeHandle requestHandle,
                   int8_t * buffer,
                   int32_t * len);

/**
 *  Read data for the request of the DLM session only once.
 * the buffer returned is allocated by recvData(),and will be freed by
 * closeRequest(),so DO NOT access the buffer any more after CloseRequest().
 * the received buffer only return once after received DATAOK.
 * \param   requestHandle       request id
 * \param   buffer              buffer for data reading.
 * \param   len                 return buffer data length.
 * \return <ul>
 *          <li>success reading data: >=0
 *          <li>fail: the status of the request
 *          </ul>
 */
int32_t NCCBrw_dlm_readOnce(T_DLM_ReqNodeHandle requestHandle,
                       int8_t ** buffer,
                       int32_t * len);

/**
 *  Get the status of the request
 * \param   requestHandle       request handle
 * \return <ul>
 *          <li>success or fail : DLM_STATUS
 *          </ul>
 */
int32_t NCCBrw_dlm_getStatus(T_DLM_ReqNodeHandle requestHandle);

/**
 *  Close the request of the session.
 * close the request, if the request is KeepAlive,the request node will
 * add to DLM_KPIDLE_QUEUE, and the received buffer will be freed,so don't
 * access the buffer any more when close the Request.
 * \param   requestHandle       request handle
 * \return NULL
 */
void NCCBrw_dlm_closeRequest(T_DLM_ReqNodeHandle *pRequestHandle);

/**
 *  Get the received data length of the request
 * \param   requestHandle       request handle
 * \return <ul>
 *          <li>success : >=0
 *          <li>fail: DLM_ERROR
 *          </ul>
 */
int32_t NCCBrw_dlm_getRecvLen(T_DLM_ReqNodeHandle requestHandle);

/**
 *  Get the length of the data sent
 * \param   requestHandle       request handle
 * \return <ul>
 *          <li>success : >=0
 *          <li>fail: -1
 *          </ul>
 */
int32_t NCCBrw_dlm_getSendLen(T_DLM_ReqNodeHandle requestHandle);

/**
 *  Get the response header data in char ptr
 * \param   requestHandle       request handle
 * \param   respType            DLM_RESP_TYPE:DLM_RESP_PTR_*
 * \return <ul>
 *          <li>success : not NULL pointer
 *          <li>fail: NULL
 *          </ul>
 */
int8_t *NCCBrw_dlm_getRespHeaderPtr(T_DLM_ReqNodeHandle requestHandle,
                                       DLM_RESP_TYPE respType);

/**
 *  Get the response header data in int
 * \param   requestHandle       request handle
 * \param   respType            DLM_RESP_TYPE:DLM_RESP_INT_*
 * \return <ul>
 *          <li>success : >=0
 *          <li>fail: -1
 *          </ul>
 */
int32_t NCCBrw_dlm_getRespHeaderInt(T_DLM_ReqNodeHandle requestHandle,
                               DLM_RESP_TYPE respType);

#ifdef __cplusplus
    extern "C" {
#endif

#endif /*__NCC_DLM_H__*/
/* @} */
