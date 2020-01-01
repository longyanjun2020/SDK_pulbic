
/**
 * @file
 * NCC mms net Porting Layer
 *
 * NCC mms net Porting Layer Routines should be implemented
 *
 * <!-- #interface list begin -->
 * \section nccport_mms_net Interface
 * - NCCPort_mmsnet_createSession()
 * - NCCPort_mmsnet_createRequest()
 * - NCCPort_mmsnet_runRequest()
 * - NCCPort_mmsnet_destroyRequest()
 * - NCCPort_mmsnet_destroySession()
 * <!-- #interface list end -->
 */

#ifndef __NCCPort_MMS_NET_H__
#define __NCCPort_MMS_NET_H__

#include <ncc_types.h>
//#include <nccmms_trans.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
   *    \name Values for WAP/HTTP stack.
   */

/*@{*/

/**NCCPort_MMS_NET return value: success*/
#define NCCPort_MMS_NET_SUCCESS                                  0
/**NCCPort_MMS_NET return value: failed*/
#define NCCPort_MMS_NET_FAILED                                   -1
/**NCCPort_MMS_NET return value: invalid parameters*/
#define NCCPort_MMS_NET_INVALID                                  -2

/**define download MMS method*/
#define MPL_METHOD_GET                                       0x0
/**define send MMS data method*/
#define MPL_METHOD_POST                                      0x1

/**define NetSend go WAP stack*/
#define MPL_PROTOCOL_WAP                                     0x0
/**define NetSend go HTTP stack*/
#define MPL_PROTOCOL_HTTP                                    0x1

/**define 32 bit address declaration of NetSend session handle*/
#define T_NetSend_Session_Handle                             int32_t
/**define 32 bit address declaration of NetSend request handle*/
#define T_NetSend_Request_Handle                             int32_t

/*@}*/

/**
   *    \name Return Values for function netSend_status().
   */

/*@{*/

/**define NetSend state of continuing call run*/
#define MPL_NETSEND_TRYAGAIN                                 0x1
/**define NetSend state of task done*/
#define MPL_NETSEND_COMPLETE_SUCCESS                         0x2
/**define NetSend state of task failure(not resource unavailable)*/
#define MPL_NETSEND_COMPLETE_FAILED                          0x3
/**define NetSend state of task failure(resource unavailable)*/
#define MPL_NETSEND_URINOTFOUND                              0x4
/**define NetSend state of task failure(Other error)*/
#define MPL_NETSEND_OTHER_ERR                                0x5
/**define NetSend state of task failure (MMS size over) ******/
#define MPL_NETSEND_ERR_OVERSIZE                             0x6

/**define max MMSC addr length*/
#define MMS_NET_MMSC_ADDR_LEN                                    100
/**define max gateway length*/
#define MMS_NET_GATEWAY_LEN                                      100
/**define max proxy gateway addr length*/
#define MMS_NET_PROXY_LEN                                        40
/*@}*/

/*@{*/

/**
 * Structure of net porting layer
 */

/**
 * Structure that defines connect information for mms configure,it is used by Transmission Module
 */
typedef struct {
    int32_t protocol_mask;                  /**< used to select the suitable stack which is wap or http*/
    int8_t mmsc_addr[MMS_NET_MMSC_ADDR_LEN];    /**< used to save the address of mms center*/
    int8_t gateway[MMS_NET_GATEWAY_LEN];        /**< used to save the address of gateway*/
    int32_t gateway_port;                   /**< used to save the port number of gateway*/
    int8_t proxy[MMS_NET_PROXY_LEN];            /**< used to save the address of HTTP proxy when using http stack*/
    int32_t proxy_port;                     /**< used to save the port number of gateway when using http stack*/
    int32_t up_limit;                       /**< used to save the max transport bitrate*/
    int32_t low_limit;                      /**< used to save the min transport bitrate*/
} T_MMS_NET_Conn_Cfg;

typedef struct {
    T_NetSend_Session_Handle session;       /**< used to save 32 bit address of NetSend WAP/HTTP session handle*/
    T_NetSend_Request_Handle request;       /**< used to save 32 bit address of NetSend WAP/HTTP request handle*/

    T_MMS_NET_Conn_Cfg conn_cfg;        /**< used to save data info of NetSend connection*/

    int32_t method;                 /**< used to save mode of POST/GET*/
    int32_t methodDataLen;      /**< used to record the length of POST/GET method data */
    uint8_t *response;          /**< used to record the reponse text from gatway*/
    int32_t response_len;       /**< used to record the reponse text length*/

    int32_t netSend_status;     /**< used to record NetSend status such as tryAgain, workDone, workFailed*/
    int32_t protocol_status;    /**< used to save the WAP protocol status info*/
    int32_t stage;              /**< used to save the current task progress*/

    int8_t *MIME_Type;          /**< used to present the MIME type of media*/
    uint32_t recvMaxDataSize;    /**< used to save max download mms size*/
} T_NetSend_Handle;

/*@}*/

/**
 * Used to create one session for NetSend
 * \param  *netSend_handle     32 bit address of NetSend handle
 * \return <ul>
 *             <li>#NCCPort_MMS_NET_SUCCESS		if successful
 *             <li>#NCCPort_MMS_NET_FAILED		if failed
 *             <li>#NCCPort_MMS_NET_INVALID		if parameter invalid
 *         </ul>
 */
int32_t NCCPort_mmsnet_createSession(T_NetSend_Handle * netSend_handle);

/**
 * Used to create one session for NetSend after session created
 * \param  *netSend_handle     32 bit address of NetSend handle
 * \return <ul>
 *             <li>#NCCPort_MMS_NET_SUCCESS		if successful
 *             <li>#NCCPort_MMS_NET_FAILED		if failed
 *             <li>#NCCPort_MMS_NET_INVALID		if parameter invalid
 *         </ul>
 */
int32_t NCCPort_mmsnet_createRequest(T_NetSend_Handle * netSend_handle, uint8_t *pData, int32_t dataLen);

/**
 * Used to run with HTTP/WAP stack after session and request created
 * \param  *netSend_handle     32 bit address of NetSend handle
 * \return <ul>
 *             <li>#NCCPort_MMS_NET_SUCCESS		if successful
 *             <li>#NCCPort_MMS_NET_FAILED		if failed
 *             <li>#NCCPort_MMS_NET_INVALID		if parameter invalid
 *         </ul>
 */
int32_t NCCPort_mmsnet_runRequest(T_NetSend_Handle * netSend_handle);

/**
 * Used to destroy request after finishing the NetSend activity
 * \param  *netSend_handle     32 bit address of NetSend handle
 * \return <ul>
 *             <li>#NCCPort_MMS_NET_SUCCESS		if successful
 *             <li>#NCCPort_MMS_NET_INVALID		if parameter invalid
 *         </ul>
 */
int32_t NCCPort_mmsnet_destroyRequest(T_NetSend_Handle * netSend_handle);

/**
 * Used to destroy session after finishing the NetSend activity
 * \param  *netSend_handle     32 bit address of NetSend handle
 * \return <ul>
 *             <li>#NCCPort_MMS_NET_SUCCESS		if successful
 *             <li>#NCCPort_MMS_NET_INVALID		if parameter invalid
 *         </ul>
 */
int32_t NCCPort_mmsnet_destroySession(T_NetSend_Handle * netSend_handle);

#ifdef __cplusplus
}
#endif

#endif /* _MMSPL_NETSEND_H_ */
