
#ifndef __WSP_SOCK_H__
#define __WSP_SOCK_H__

#include <ncc_types.h>
#include <wsp_conf.h>
#include <wsp.h>
#include <wsp_error.h>
#include <wsp_wtp.h>
#include <wsp_header.h>
#include <nccwsp.h>

#define WSP_CONNECT             9201
#define WSP_CONNECTLESS         9200
#define WSP_CONNECT_WTLS        9203
#define WSP_CONNECTLESS_PUSH    2948

#ifdef __cplusplus
extern  "C" {
#endif

#define WAP_SESSION_NULL    0   /**< WAP stack unloaded */
#define WAP_SESSION_IDLE    1   /**< WAP stack is idle */
#define WAP_SESSION_ACTIVE  2   /**< WAP stack is active */
#define WAP_SESSION_TIMEOUT 3   /**< WAP stack session timeout */

#define WAP_NULL_QUEUE      0
#define WAP_READY_QUEUE     1
#define WAP_ACTIVE_QUEUE    2

/* change this function to get user name and password at a same function */
typedef int32_t    (*fnWSP_AuthGetFunc)(int8_t *,int8_t **,int8_t **);/*The limit length of name(or password) is 128byte */
typedef int32_t    (*fnWSP_AuthAlertFunc)(int32_t);

typedef struct T_WapReq{
    int8_t  method;     /**< Request method.now only GET(0x40) and POST(0x60) is supported */
    uint8_t Boundary[3];/**< Boundary */
    int8_t *url;        /**< Request URL*/
    int8_t *body;       /**< Request body of POST method */
    int32_t body_len;   /**< Request body length of POST method */
    int8_t **header;    /**< Request header*/
    int32_t header_len; /**< String item's number in request header */
    int8_t *content_type;/**< Request body's content type in POST method */
}T_WapReq;

typedef struct T_TidPeer{
    int16_t tid;            /**< Transaction Id */
    int16_t stat;           /**< Tid statue tag.stat=0,unused;1,active;3 unactive */
    int32_t errnum;         /**< Error number */
    int32_t redirect;       /**< Redirect tag.if redirection occur set it to TRUE,else set to FALSE */

    int32_t BasicAuth;      /**< Tag for basic authentication.if needed, set it to 1.esle,set it to 0 */
    int8_t * realm;          /**< Realm */
    int8_t * User;          /**< User name */
    int8_t * Passwd;        /**< User password */
    int32_t RecvDataCount;  /**< Receiving data count of one request */
    int32_t SendDataCount;  /**< Sending data count of one request */

    T_WapReq *req;          /**< Request data */
    struct T_WAP_MSG * msg; /**< Response packet pointer */
    T_DLM_ResHeader *header;/**< Response header */
    struct T_TidPeer * next;/**< Next request */
}T_TidPeer;

extern  const struct T_WAP_EventArray gpWAP_Event[];

/**
 * Call this function to do some WAP stack initialization.
 *
 *   \param  hc  a wsp instance handle.
 *   \return
 */
 void fnWAP_Init(void *hc);

/**
 * Call this function to do some WAP stack clean .
 *
 *   \param  hc  a wsp instance handle.
 *   \return
 */
 void fnWAP_Clean(void *hc);

/**
 * Create a session.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  type  WAP session type .it can be  values defined
 *               as following.now this stack only support WSP_CONNECT and
 *               WSP_CONNECTLESS.
 *               #define WSP_CONNECT 9201
 *               #define WSP_CONNECTLESS 9200
 *               #define WSP_CONNECT_WTLS 9203
 *               #define WSP_CONNECTLESS_PUSH 2948
 *   \param  serverIP the IP of server.
 *   \return If WAP session type is  WSP_CONNECT or WSP_CONNECTLESS
 *             and no error occur,return TRUE;
 *             else return FALSE.
 */
 int32_t fnWAP_CreateSession(void *hc,int32_t type,int8_t * serverIP);

/**
 * Call this function to detroy a established WAP WSP session.
 *
 *   \param  hc  a wsp instance handle.
 *   \return Always return 0 .
 */
 int8_t  fnWAP_DestroySession(void *hc);

/**
 * Create a transaction.
 *
 *   \param  hc  a wsp instance handle.
 *   \return return TID of transaction.if no enough memory,retrun 0.
 *   \sa     fnWAP_WspAbortTransaction
 */
 int16_t fnWAP_Transaction(void *hc);

/**
 * Call this function to abort transaction.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  s_des   the session descriptor.
 *   \return
 *   \sa     fnWAP_Transaction
 */
 void fnWAP_WspAbortTransaction(void *hc,int16_t tid);

/**
 * MethodInvoke function.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  tid TID of transaction
 *   \param  url the URL
 *   \param  header the header
 *   \param  head_len    the length of the header
 *   \param  Content the Content
 *   \param  Content_type Content_type
 *   \return Return 0.
 *   \sa     fnWAP_UnitMethodInvoke
 */
 int8_t fnWAP_MethodInvoke(void *hc,uint16_t tid,int8_t method,int8_t * url,int8_t * baWSP_Header[],int32_t head_len,int8_t * Content,int32_t Content_len,int8_t* Content_type);

/**
 * MethodInvoke function.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  tid TID of transaction
 *   \param  url the URL
 *   \param  header the header
 *   \param  head_len    the length of the header
 *   \param  Content the Content
 *   \param  Content_type Content_type
 *   \return Return 0.
 *   \sa     fnWAP_UnitMethodInvoke
 */
 int8_t fnWAP_UnitMethodInvoke(void *hc,int16_t tid,int8_t method,int8_t * url,int8_t * baWSP_Header[],int32_t head_len,int8_t * Content,int32_t Content_len,int8_t* Content_type);

/**
 * Call this function to connect to WAP gateway.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  caps the WAP capabilities .
 *   \param  caps_size the number of capabilitis in WAP capability structure .
 *   \return Return 0 If sucssess;else return -1.
 */
 int8_t fnWAP_Connect(void *hc,T_WAP_Capability caps[],int16_t caps_size);

/**
 * Call this function to get data from the WAP buff.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  req     the request handler.
 *   \param  buf     the buffer pionter to save the base address of the received data.
 *   \return
 *       If no data receive,return0;
 *       else return the count of date which received.
 */
 int32_t fnWAP_ReadFrom(void *hc,void * req,int8_t ** buf);

 /* See nccwsp.h */
 void fnWSP_SetOption(void *hc,int32_t Csdu,int32_t Ssdu);

 /* See nccwsp.h */
 void fnWSP_SetMom(void *hc,int32_t Mom) ;

/**
 * Check whether the request queue isn't full.
 *
 * \param    hc  a wsp instance handle.
 *   \return If the queue is full,return FALSE;else return TRUE.
 */
 int32_t fnWAP_CheckMomStat(void *hc);

/**
 * Schedule tid/request queue.
 *
 *  \param    hc  a wsp instance handle.
 *   \return if found a request in the ready queue,return TRUE.else return FALSE .
 */
int32_t fnWAP_TidManager(void *hc);

/**
 * Find a request accoding to its TID number.
 *
 * \param    hc  a wsp instance handle.
 * \param    tid  tid number of the request .
 *   \return Return a request peer handle if find,else return NULL.
 */
 T_TidPeer * fnWAP_FindReq(void *hc,int16_t tid);
/**
 * Set the max Re-transmission Counter.
 *
 * \param    hc  a wsp instance handle.
 * \param    stat    the queue id.
 * \param    peer    a wsp request handle.
 *   \return If error occur,return FALSE;else return TRUE.
 */
 int32_t fnWAP_ReqAdd(void *hc,uint8_t stat,T_TidPeer *peer);

/**
 * Remove a request object from the request list.
 *
 * \param    hc  a wsp instance handle.
 * \param    hreq  a wsp reqeust handle.
 * \param    type  the request queue which the request object belong to.
 *   \return Return TRUE if success;else return FALSE.
 */
 T_TidPeer  *fnWAP_ReqDeleteFromList(void *hc,void * hreq,int32_t *type);

/**
 * Create a request structure.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  method method which defined in WSP_PduTypes.
 *   \param  url the URL
 *   \param  header the header
 *   \param  head_len the length of the header
 *   \param  content the Content
 *   \param  content_len the length of the content
 *   \param  content_type Content_type
 *   \return If no error occur,return a request handle.else return NULL.
 */
 T_TidPeer * fnWAP_ReqCreate(void *hc,int8_t method,int8_t * url,int8_t * header,int8_t * content,int32_t content_len,int8_t* content_type);

/**
 * Destroy the response structure in the request hanlder.
 *
 * \param    hc  a wsp instance handle.
 *   \return Return TRUE if success.else return FALSE.
 */
 int32_t fnWAP_ResDestroy(T_TidPeer  *peer);

/**
 * Free request structure.
 *
 * \param    hc  a wsp instance handle.
 *   \return Return TRUE if success.else return FALSE .
 */
 int32_t fnWAP_ReqDestroy(T_WapReq  *preq);

/**
 * Free request handler structure.
 *
 * \param    peer        a wsp request peer handle.
 *   \return Return TRUE if success.else return FALSE .
 */
 int32_t fnWAP_ReqHandlerDestroy(T_TidPeer  *peer);

#ifdef __cplusplus
}
#endif

#endif /* __WAP_SOCK_H__ */

