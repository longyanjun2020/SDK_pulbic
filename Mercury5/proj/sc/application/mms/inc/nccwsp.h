/**
 * @file
 * Wireless Session Protocol Service Layer
 *
 * Service API exposed by the Wireless Session Protocol.
 *
 * <!-- #interface list begin -->
 * \section nccwsp Interface
 * - NCCWsp_setMaxRcr()
 * - NCCWsp_peekGetData()
 * - NCCWsp_setConnectHeader()
 * - NCCWsp_resetIntanceCount()
 * - NCCWsp_getInstanceSendCount()
 * - NCCWsp_getInstanceRecvCount()
 * - NCCWsp_getReqRecvCount()
 * - NCCWsp_getReqSendCount()
 * - NCCWsp_getLastError()
 * - NCCWsp_getSessionState()
 * - NCCWsp_setAuth()
 * - NCCWsp_setParam()
 * - NCCWsp_delRequest()
 * - NCCWsp_delAllRequest()
 * - NCCWsp_begin()
 * - NCCWsp_get()
 * - NCCWsp_post()
 * - NCCWsp_openRequest()
 * - NCCWsp_reopenRequest()
 * - NCCWsp_checkWspState()
 * - NCCWsp_exit()
 * - NCCWsp_ready()
 * - NCCWsp_peekReady()
 * - NCCWsp_createInstance()
 * - NCCWsp_destroyInstance()
 * - NCCWsp_decodeHeader()
 * - NCCWsp_encodeHeader()
 * - NCCWsp_decodeContentType()
 * - NCCWsp_encodeContentType()
 * - NCCWsp_decodeCharSet()
 * - NCCWsp_encodeCharSet()
 * - NCCWsp_decodeLanguage()
 * - NCCWsp_encodeLanguage()
 * - NCCWsp_decodeParameter()
 * - NCCWsp_encodeParameter()
 * - NCCWsp_decodeExtContentType()
 * - NCCWsp_decodeAppId()
 * - NCCWsp_decodeHttpParam()
 * - NCCWsp_freeParameter()
 * - NCCWsp_decodeHttpHeader()
 * - NCCWsp_decodeOneHeadField()
 * - NCCWsp_freeHeader()
 * - NCCWsp_parameterInit()
 * - NCCWsp_encodeUintvar()
 * - NCCWsp_decodeUintvar()
 * - NCCWsp_encodeTextString()
 * - NCCWsp_decodeTextString()
 * - NCCWsp_encodeTokenString()
 * - NCCWsp_decodeTokenString()
 * - NCCWsp_encodeShortInteger()
 * - NCCWsp_decodeShortInteger()
 * - NCCWsp_encodeLongInteger()
 * - NCCWsp_decodeLongInteger()
 * - NCCWsp_encodeIntegerValue()
 * - NCCWsp_decodeIntegerValue()
 * - NCCWsp_encodeValueLength()
 * - NCCWsp_decodeValueLength()
 * <!-- #interface list end -->
 */

#ifndef __NCC_WSP_H__
#define __NCC_WSP_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C"{
#endif

#define     WAP_SUCCESS      0       /**< WSP download success.*/
#define     WAP_RECEVINGDATA (-10)   /**< WSP download is in processing.*/
#define WAP_DISCONNECT       (-11)   /**< WSP session need to be disconnected.*/
#define WAP_NODATA           (-12)   /**< WSP download success and no data body included in the response*/


#define WSP_INPUT_PARAMETER_ERROR   -1
#define WSP_INIT_HEADER_ERROR       -2

//typedef int32_t (*htAuthGetFunc)(int8_t *, int8_t **,int8_t **);
//typedef int32_t  (*htAlertHsFunc)(int32_t);

/* The structure used to indicate parameter struct */
typedef struct T_HEADER_Param{
    uint8_t *name;          /* header name */
    uint8_t *value;         /* header value */
    struct T_HEADER_Param *next;
}T_HEADER_PARAM;

/* The structure used to indicate some information of http header */
typedef struct T_HEADER_Field{
    /**Header name*/
    uint8_t *name;
    /**Header value*/
    uint8_t *value;
    /**Header parameter list*/
    T_HEADER_PARAM *param;
    /**length of header name and header value*/
    int32_t length;
}T_HEADER_FIELD;

/**
 * Set max retransmit time
 *
 *   \param  hc  a wsp instance handle.
 *   \param  rcr max retransmit times.
 *   \return
 *   \sa     NCCWsp_setParam
 */
void NCCWsp_setMaxRcr(void *hc,int8_t rcr);

/**
 * Receive data in unblock way
 *
 *   \param  hc  a wsp instance handle.
 *   \param  tid a wsp request handle.
 *   \param  buf pointer to received data.
 *   \return
 *           <li> when successful, return the length of received data</li>
 *           <li> when data receiving has not finished and no error occur, return #WAP_RECEVING_DATA</li>
 *           <li> when error occur, return:</li>
 *           <ul>
 *               <li>#WAP_SUSPEND</li>
 *               <li>#WAP_METHODABORT</li>
 *               <li>#WAP_TIMEOUT</li>
 *               <li>#WAP_INVALIDURL</li>
 *               <li>#WAP_BIGGERTHANMOR</li>
 *           </ul>
 */
int32_t NCCWsp_peekGetData (void *hc,void * tid,int8_t * *buf);

/**
 * Set headers for connect
 *
 *   \param  hc      a wsp instance handle.
 *   \param  header  headers for wap connect.The parameter should be
 *     following format:
 *     "Accept:image/gif".
 *     "Accept:image/gif\r\nAccept-Charset:utf-8".
 *     "Accept:image/gif,image/vnd.wap.wbmp\r\nAccept-Charset:utf-8\r\nAccept-Language:en"
 *   \return If success return TRUE,else return FALSE.
 */
int32_t NCCWsp_setConnectHeader(void *hc,int8_t *header);

/**
 * Reset data counter of specified instance
 *
 *   \param  hc  a wsp instance handle.
 *   \return
 *   \sa  NCCWsp_getInstanceRecvCount,NCCWsp_getInstanceSendCount
 */
void NCCWsp_resetIntanceCount(void *hc);

/**
 * Get sent data size of specified instance
 *
 *   \param  hc  a wsp instance handle.
 *       \return Return the sent data size of specified instance
 *   \sa     NCCWsp_getInstanceRecvCount
 */
int32_t NCCWsp_getInstanceSendCount(void *hc);

/**
 * Get reveived data size of specified instance
 *
 *   \param  hc  a wsp instance handle.
 *    \return    Return the reveived data size of specified instance
 *   \sa     NCCWsp_getInstanceSendCount
 */
int32_t NCCWsp_getInstanceRecvCount(void *hc);

/**
 * Get reveived data size of specified request
 *
 *   \param  hc  a wsp instance handle.
 *   \param  hreq    a wsp request handle.
 *   \return Return the  reveived data size of specified request
 *   \sa     NCCWsp_getReqSendCount
 */
int32_t NCCWsp_getReqRecvCount(void *hc,void * hreq);

/**
 * Get sent data size of specified request
 *
 *   \param  hc  a wsp instance handle.
 *   \param  hreq    a wsp request handle.
 *   \return Return the sent data size of specified request
 *   \sa     NCCWsp_getReqRecvCount
 */
int32_t NCCWsp_getReqSendCount(void *hc,void * hreq);

/**
 * Call this function to get the error status for the last operation that failed..
 *
 * \param    hc  a wsp instance handle.
 * \param    peer the request handler.
 *   \return The return value indicates the error code for the last Sockets API routine
 *           performed by this thread.return 0 if no error.
 */
int32_t NCCWsp_getLastError(void *hc,void *peer);

/**
 * Set wap parameter
 *
 *   \param  hc  a wsp instance handle.
 *   \param  wapgateway  wap gateway ip address. If this parameter is NULL,
 *               a default value will be used.
 *   \param  wapport WSP session type. The possible value is 9200,9201,9203,2948. If this parameter
 *                is NULL, a default value(9201) will be used.
 *   \param  MaxCsdu Maximum Client SDU Size.If 0 is set, the default value will be used. If the value is bigger than the max value which protocal can support, the max value will be used.
 *   \param  MaxSsdu Maximum Server SDU Size.If 0 is set, the default value will be used. If the value is bigger than the max value which protocal can support, the max value will be used.
 *       \return return TRUE if no error occur;else return FALSE.
 *   \attention If error occur,default value will be seted.
 *   \sa     NCCWsp_setMaxRcr
 */
int32_t NCCWsp_setParam(void *hc,
                                   const int8_t * wapgateway,
                                   int32_t wapport,
                                   int32_t MaxCsdu,
                                   int32_t MaxSsdu);

/**
 * Set user name and password.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  hreq  The request peer handle.
 *   \param  realm  The realm.
 *   \param  user  The user name.
 *   \param  passwd The password.
 *   \return  Return TRUE if success;otherwise return FALSE.
 */
int32_t NCCWsp_setAuth(void * hc,void *hreq,int8_t *realm,int8_t *user,int8_t *passwd);

/**
 * Delete a request from request queue.
 *
 * \param    hc  a wsp instance handle.
 * \param    hreq    a wsp instance handle.
 *   \return Return TRUE if success;otherwise return FALSE .
 */
int32_t NCCWsp_delRequest(void *hc,void * hreq);

/**
 * Delete all request from request queue.
 *
 * \param    hc  a wsp instance handle.
 *   \return Return 0.
 */
 int16_t NCCWsp_delAllRequest(void *hc);

/**
  * Get response header structure.
  *
  * \param  hc  a wsp instance handle.
  * \param  tid  the WSP request handler .
  * \param  res the output pointer to save response structure.
  *   \return   Return TRUE if success.else return FALSE .
  */
int32_t  NCCWsp_getResHeader(void *hc,void * tid,void **res);

/**
 * Load wap stack
 *
 *   \param  hc  a wsp instance handle.
 *       \return If no error occur return TRUE,else return FALSE.
 *   \sa     NCCWsp_exit
 */
int32_t NCCWsp_begin(void *hc);

/**
 * Open a wsp GET request
 *
 *   \param  hc  a wsp instance handle.
 *   \param  url request url address
 *   \param  Header  header string.
 *   \return Return handler of WSP request if success;otherwise return NULL;
 *   \sa     NCCWsp_post
 */
void * NCCWsp_get(void *hc,
         int8_t * url,
         int8_t *Header);

/**
 * Open a wsp POST request
 *
 *   \param  hc  a wsp instance handle.
 *   \param  Url request url address
 *   \param  Body    data buffer of POST method.The WSP will not make a copy of
 *                         this buffer to save memory. So this buffer should not be free
 *                         or changed utill the request finish(return a success or error)
 *                         or canceled by the user.
 *   \param  Body_len    data length.
 *   \param  Header  header string.The parameter should be following format:
 *     "Accept:image/gif".
 *     "Accept:image/gif\r\nAccept-Charset:utf-8".
 *     "Accept:image/gif,image/vnd.wap.wbmp\r\nAccept-Charset:utf-8\r\nAccept-Language:en"
 *   \param  ContentType content type of POST data.
 *   \return return handler of WSP request if success.else return NULL.
 *   \attention See parameter Body for more details.
 *   \sa     NCCWsp_get
 */
void * NCCWsp_post(void *hc,
                     int8_t *Url,
                     int8_t * Body,
                     int32_t Body_len,
                     int8_t *Header,
                     int8_t *ContentType);

/**
 * Open a wsp request
 *
 *   \param  hc  a wsp instance handle.
 *   \param  method  method type.Now only GET(0x40),POST(0x60) is valid.
 *   \param  url request url address.must have value.
 *   \param  header  header string.The parameter should be following format:
 *     "Accept:image/gif".
 *     "Accept:image/gif\r\nAccept-Charset:utf-8".
 *     "Accept:image/gif,image/vnd.wap.wbmp\r\nAccept-Charset:utf-8\r\nAccept-Language:en"
 *   \param  body  data buffer of POST method. The WSP will not make a copy of
 *                         this buffer to save memory. So this buffer should not be free
 *                         or changed utill the request finish(return a success or error)
 *                         or canceled by the user.
 *   \param  body_len    data length.
 *   \param  contentType content type of POST data.
 *   \return return handler of WSP request if success.else return NULL.
 *   \attention See parameter body for more details.
 */
void * NCCWsp_openRequest(void *hc,
             int8_t method,
             int8_t *url,
             int8_t *header,
             int8_t * body,
             int32_t body_len,
             int8_t *contentType);

/**
 * Using this funciton to send a new request with the old wsp request handle.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  hreq the old request handle.
 *   \return return handler of WSP request if success.else return NULL.
 *   \attention The old request context will be inherited when this function is used. E.g. the authentication header.
 */
void * NCCWsp_reopenRequest(void *hc,void *hreq);


/**
 * Check wsp state
 *
 *   \param  hc  a wsp instance handle.
 *   \return
 *           <li>when parameter hc is NULL,return #WAP_OCCUR_ERROR</li>
 *           <li>when gateway has not connected,return #WAP_SESSION_NULL</li>
 *           <li>when gateway is connected and the queue is empty,return #WAP_SESSION_IDLE</li>
 *           <li>when gateway is connected and the queue isn't empty,return #WAP_SESSION_ACTIVE</li>
 *           <li>when wsp session time out,return #WAP_SESSION_TIMEOUT</li>
 */
int32_t NCCWsp_checkWspState(void *hc);

/**
 * Check wsp session state.
 *
 *   \param  hc  a wsp instance handle.
 *   \return  Return state of WSP session if session has start;otherwise return 0;
 *
 */
int8_t  NCCWsp_getSessionState(void *hc);

/**
 * Unload wap stack.
 *   \param  hc  a wsp instance handle.
 *     \return
 *   \sa     NCCWsp_begin
 */
void NCCWsp_exit(void *hc);

/**
 * Check wap gateway state in unblocked way.
 *
 *   \param  hc  a wsp instance handle.
 *       \return if success return 0,else return an error.
 *   \sa     NCCWsp_peekReady
 */
int32_t NCCWsp_ready(void *hc);

/**
 * Check wap gateway state in block way.
 *
 *   \param  hc  a wsp instance handle.
 *       \return If success return 0,else return an error.
 *   \attention   If WAP_RECEVING_DATA is returned,query should not be stoped.
 *   \sa     NCCWsp_ready
 */
int32_t  NCCWsp_peekReady(void *hc);

/**
 * Create a wsp instance.
 *
 *   \param  limitConn    valid active request number.the default value is 3.
            if 0 is setted,default will be used to create the session.
 *   \param  AuthGetFunc callback function to get authenticate parameters
 *           if authenticate is needed by the server.If no AuthGetFunc is
 *           defined,NULL is prefered.
 *   \param  AuthAlertFunc   callback alert function if authenticate is needed
 *           by the server.If no AuthAlertFunc is defined,NULL is prefered.
 *   \return If success,return a handler to the created wsp instance ;
 *           else return NULL.
 *   \sa     NCCWsp_destroyInstance
 */
void * NCCWsp_createInstance(uint8_t limitConn,void *AuthGetFunc,void *AuthAlertFunc);

/**
 * Destroy a wsp instance.
 *
 *   \param  hc  a wsp instance handle.
 *   \return when hc not NULL,return TRUE;else return FALSE.
 *   \attention   If this function is called, instance handle will be destroy. So parameter hc
 *                   should not be used by any WSP functions except that you using
 *                   NCCWsp_createInstance to create new one.
 *   \sa     NCCWsp_createInstance
 */
int32_t  NCCWsp_destroyInstance(void *hc);

/**
 * Decode http header Field.
 * \param number The Token of http header.
 * \return <ul>
 *      <li>If successful,then return#string pointer of http header.
 *      <li>If unsuccessful,then return#NULL.
 *          </ul>
 */
const int8_t * NCCWsp_decodeHeader(int32_t number);

/**
 * Encode a header string.
 * \param str pointer of the string
 * \return <ul>
 *      <li>encoded data when success
 *      <li>-1 when fail
 *          </ul>
 */
int32_t NCCWsp_encodeHeader(int8_t *str);

/**
 * Decode content type header to get the string of content type.
 * \param number The Token of content type.
 * \return <ul>
 *      <li>If successful,then return#string pointer of content type header.
 *      <li>If unsuccessful,then return#NULL.
 *          </ul>
 */
const int8_t * NCCWsp_decodeContentType(int32_t number);

/**
 * Encode a content-type's value string.
 * \param str pointer of the string
 * \return <ul>
 *      <li>encoded data when success
 *      <li>-1 when fail
 *          </ul>
 */
int32_t NCCWsp_encodeContentType(int8_t *str);

/**
 * Decode charset field.
 * \param Charset The Token of charset.
 * \return <ul>
 *      <li>If successful,then return#string pointer of charset header
 *      <li>If unsuccessful,then return#NULL.
 *          </ul>
 */
uint8_t * NCCWsp_decodeCharSet(int32_t Charset);

/**
 * Encode a charset string.
 * \param str pointer of the string
 * \return <ul>
 *      <li>encoded data when success
 *      <li>-1 when fail
 *          </ul>
 */
int32_t NCCWsp_encodeCharSet(int8_t *str);

/**
 * Decode Language field.
 * \param lang The Token of Language.
 * \return<ul>
 *      <li>If successful,then return#string pointer of Language header
 *      <li>If unsuccessful,then return#NULL.
 *          </ul>
 */
int8_t * NCCWsp_decodeLanguage(int32_t lang);

/**
 * Encode a language string.
 * \param str pointer of the string
 * \return <ul>
 *      <li>encoded data when success
 *      <li>-1 when fail
 *          </ul>
 */
int32_t NCCWsp_encodeLanguage(int8_t *str);

/**
 * Decode Parameter field.
 * \param Charset The Token of Parameter.
 * \return <ul>
 *      <li>If successful,then return#string pointer of Parameter header
 *      <li>If unsuccessful,then return#NULL.
 *          </ul>
 */
const int8_t * NCCWsp_decodeParameter(int32_t number);

/**
 * Encode a parameter string.
 * \param str pointer of the string
 * \return <ul>
 *      <li>encoded data when success
 *      <li>-1 when fail
 *          </ul>
 */
int32_t NCCWsp_encodeParameter(int8_t *str);

/**
 * Decode extension content type field.
 * \param number The Token of extension content type.
 *
 *  \return <ul>
 *              <li>If successful,then return#string pointer of extension content type header
 *              <li>If unsuccessful,then return#NULL.
 *          </ul>
 */
const int8_t * NCCWsp_decodeExtContentType(int32_t number);

/**
 * Encode URL.
 * \param  id the application number to decode.
 * \return If no error occur,return a pointer to a string,else return NULL.
 */
uint8_t *NCCWsp_decodeAppId(int32_t id);

/**
 * Parse parameters following the http header.
 * \param pPdu The pointer of message header.
 * \param pduLen The length of message header.
 * \param param The pointer of parameters.
 * \return <ul>
 *         <li>If successful,then return#TRUE.
 *         <li>If unsuccessful,then return#FALSE.
 *         </ul>
 */
uint8_t NCCWsp_decodeHttpParam(uint8_t **pPdu,uint32_t *pduLen,T_HEADER_PARAM **param);

/**
 * Free memory that allocated by WSP Module.
 * \param param The  pointer of parameter struct.
 * \return NONE
 */
void NCCWsp_freeParameter(T_HEADER_PARAM *param);

/**
 * Parse Http Header
 * \param pPdu The pointer of Message Header.
 * \param pduLen The length of *pPdu.
 * \param headField The pointer of header.
 * \return <ul>
 *         <li>If successful,then return#TRUE.
 *         <li>If unsuccessful,then return#FALSE.
 *         </ul>
 */
int32_t NCCWsp_decodeHttpHeader(uint8_t *pPdu, uint32_t pduLen, T_HEADER_FIELD **headField);

/**
 * Decode a http header.
 * \param pPdu The pointer of pPdu.
 * \param pduLen The length of pdu.
 * \param headField The pointer of header.
 * \param param The pointer of param pdu.
 * \param paramlen The length of parameter.
 * \return <ul>
 *         <li>If successful,then return#TRUE.
 *         <li>If unsuccessful,then return#FALSE.
 *         </ul>
 */
uint8_t NCCWsp_decodeOneHeadField(uint8_t *pPdu, uint32_t pduLen, T_HEADER_FIELD **headField,uint8_t **param,int32_t *paramlen);

/**
 * Free memory of http header that allocated by WSP Module.
 * \param header The pointer of http header.
 * \return NONE
 */
void NCCWsp_freeHeader(T_HEADER_FIELD *header);

/**
 * Init a parameter struct and allocated memory for parameter struct.
 * \param name_len The length of name Field.
 * \param value_len The length of value Field.
 * \return <ul>
 *         <li>If successful,then return#The pointer of parameter struct.
 *         <li>If unsuccessful,then return#NULL.
 *         </ul>
 */
T_HEADER_PARAM *NCCWsp_parameterInit(uint32_t name_len,int32_t value_len);

/**
 * Encode uintvar. (Variable Length Unsigned Integers, WSP specification 8.1.2 section)
 * \param uintvar [out]pointer of store space, make sure it's enough(at least five octets)
 * \param value the uintvar's value
 * \return
 *      -the length of uintvar when success, -1 when fail
 */
int32_t NCCWsp_encodeUintvar(uint8_t **uintvar, uint32_t value);

/**
 * Decode uintvar. (Variable Length Unsigned Integers, WSP specification 8.1.2 section)
 * \param uintvar pointer of pointer of uintvar
 * \param value [out]integer value
 * \return <ul>
 *         <li> TRUE when decode successfully </li>
 *         <li> FALSE when decode fail </li>
 *         </ul>
 */
int32_t NCCWsp_decodeUintvar(uint8_t **uintvar, uint32_t *value);

/**
 * Encode Text-String. (in wsp specification section 8.4.2.1)
 * \param pDest the destination buffer, make sure it is enough to
 *  store the string (string length + 2).
 * \param pSource the string's pointer
 * \return <ul>
 *         <li> TRUE when encode successfully </li>
 *         <li> FALSE when encode fail </li>
 *         </ul>
 */
int32_t NCCWsp_encodeTextString(uint8_t **pDest, uint8_t *pSource);

/**
 * Decode Text-String. (in wsp specification section 8.4.2.1)
 * \param pSource pointer of the Text-String, note: pSource will be changed
 * \param pStrlen [out]lenght of the string
 * \param malloc malloc function pointer
 * \return <ul>
 *         <li> the string get from the pdu's pointer </li>
 *         </ul>
 */
uint8_t *NCCWsp_decodeTextString(uint8_t **pSource, int32_t *pStrlen, void *(*malloc)(int32_t));

/**
 * Encode Token-text. (in wsp specification section 8.4.2.1)
 * \param pDest the destination buffer, make sure it is enough to
 *  store the string (string length + 2).
 * \param pSource the string's pointer
 * \return void
 */
int32_t NCCWsp_encodeTokenString(uint8_t **pDest, uint8_t *pSource);

/**
 * Decode Token-text. (in wsp specification section 8.4.2.1)
 * \param pSource pointer of the Token-text, note: pSource will be changed
 * \param pStrlen [out]lenght of the string
 * \param malloc malloc function pointer
 * \return <ul>
 *         <li> the string get from the pdu's pointer
 *         </ul>
 */
uint8_t *NCCWsp_decodeTokenString(uint8_t **pSource, int32_t *pStrlen, void *(*malloc)(int32_t));

/**
 * Encode short-integer. (in wsp specification section 8.4.2.1)
 * \param pDest the destination buffer, make sure it's enough to stroe the value (2 bytes)
 * \param value the integer value
 * \return <ul>
 *         <li> TRUE when encode successfully </li>
 *         <li> FALSE when encode fail </li>
 *         </ul>
 */
int32_t NCCWsp_encodeShortInteger(uint8_t **pDest, uint32_t value);

/**
 * Decode short-integer. (in wsp specification section 8.4.2.1)
 * \param pSource pointer of the integer value
 * \param value [out]the value of the  int32_t type
 * \return <ul>
 *         <li> TRUE when decode successfully </li>
 *         <li> FALSE when decode fail </li>
 *         </ul>
 */
int32_t NCCWsp_decodeShortInteger(uint8_t **pSource, uint32_t *value);

/**
 * Encode long-integer. (in wsp specification section 8.4.2.1)
 * \param pDest the destination buffer, make sure it's enough to stroe the value
 * \param value the integer value
 * \return <ul>
 *         <li> TRUE when encode successfully </li>
 *         <li> FALSE when encode fail </li>
 *         </ul>
 */
int32_t NCCWsp_encodeLongInteger(uint8_t **pDest, uint32_t value);

/**
 * Decode long-integer. (in wsp specification section 8.4.2.1)
 * \param pSource pointer of the integer value
 * \param value [out]the value of the  int32_t type
 * \return <ul>
 *         <li> TRUE when decode successfully </li>
 *         <li> FALSE when decode fail </li>
 *         </ul>
 */
int32_t NCCWsp_decodeLongInteger(uint8_t **pSource, uint32_t *value);

/**
 * Encode integer value. (Integer-Value = Short-integer | Long-integer)
 * \param pDest the destination buffer, make sure it's enough to stroe the value
 * \param value the integer value
 * \return void
 */
int32_t NCCWsp_encodeIntegerValue(uint8_t **pDest, uint32_t value);

/**
 * Decode integer value. (Integer-Value = Short-integer | Long-integer)
 * \param pSource pointer of the integer value
 * \param value [out]the value of the  int32_t type
 * \return <ul>
 *         <li> TRUE when decode successfully </li>
 *         <li> FALSE when decode fail </li>
 *         </ul>
 */
int32_t NCCWsp_decodeIntegerValue(uint8_t **pSource, uint32_t *value);

/**
 * Encode the value-length value. (in wsp specification section 8.4.2.2)
 * \param pDest the destination buffer, make sure it's enough to store the value
 * \param value the uint32_t value
 * \return <ul>
 *         <li> the number of octets when success
 *         <li> -1 when fail
 *         </ul>
 */
int32_t NCCWsp_encodeValueLength(uint8_t **pDest, uint32_t value);

/**
 * Decode the value-length value. (in wsp specification section 8.4.2.2)
 * \param pSource pointer of pointer of value-length
 * \param value [out]value in uint32_t type
 * \return <ul>
 *         <li> TRUE when decode successfully </li>
 *         <li> FALSE when decode fail </li>
 *         </ul>
 */
int32_t NCCWsp_decodeValueLength(uint8_t **pSource, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_WSP_H__ */
