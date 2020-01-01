/**
*
* @file    ven_socket.h
* @brief   This file defines socket interface for multi-tasking
*
* @author  Edward.Yeh
* @version $Id: ven_socket.h 35894 2009-07-16 07:05:29Z edward.yeh $
*
*/
#ifndef __VEN_SOCKET_DEFINE_H_
#define __VEN_SOCKET_DEFINE_H_

#include "ven_sdk.h"
#include "winsocket.h"
#include "ven_setting.h"
#include "ms_socket_cmn.h"

/// For unit test
#define __SDK_MULTI_BEARER_TEST__

typedef enum
{
    VEN_SOCKET_RET_SUCCESS      = 0,                                                          ///< operation completed successfully
    VEN_SOCKET_RET_BAD_PARAM    = 1,                                                          ///< invalid input parameters
    VEN_SOCKET_RET_FAILED       = 2,                                                          ///< WHAT? every code here is failed
    VEN_SOCKET_RET_OUT_OF_MEMORY    = 3,                                                      ///< memory is not enough to complete the operation
    VEN_SOCKET_RET_DATA_LINK_ALREADY_ACTIVATED = 4,                                           ///< data link already activated
    VEN_SOCKET_RET_DATA_LINK_KO     = 5,                                                      ///< create data link failed
    VEN_SOCKET_RET_COM_CLOSE_BY_PEER = MSERV_NETWORK_STATUS_DATALINK_CLOSE_BY_PEER,           ///< com close by peer
    VEN_SOCKET_RET_CONTCP_NO_BUFFER_ERROR = 7,                                                ///< con tcp no buffer error
    VEN_SOCKET_RET_NOT_SUPPORT = 8,
} ven_socket_ret_t;

#define VEN_SOCKET_IP_BYTESIZE 4 /* 168.95.1.1 => a85f0101 */

enum
{
    VEN_SOL_SOCKET = MSERV_SOL_SOCKET,
    VEN_SOL_IP = MSERV_SOL_IP,
    VEN_SOL_TCP = MSERV_SOL_TCP,
    VEN_SOL_UDP = MSERV_SOL_UDP,
};

enum
{
    VEN_SO_KEEPALIVE = MSERV_SO_KEEPALIVE,
    VEN_SO_LINGER = MSERV_SO_LINGER,
    VEN_SO_SNDBUF = MSERV_SO_SNDBUF,
    VEN_SO_RCVBUF = MSERV_SO_RCVBUF,
    VEN_TCP_NODELAY = MSERV_TCP_NODELAY,
    VEN_SO_RCVMODE  = MSERV_SO_RCVMODE,
};

enum
{
    VEN_SD_RECV = MSERV_SD_RECV,
    VEN_SD_SEND = MSERV_SD_SEND,
    VEN_SD_BOTH = MSERV_SD_BOTH,
};

/// re-define struct
#define VEN_BEARER_GPRS    (BEARER_GPRS)
#define VEN_BEARER_WIFI    (BEARER_WIFI)
#define VEN_BEARER_NUM     (BEARER_NUM)
#define VEN_BEARER_INVALID (BEARER_INVALID)
typedef MservSocketBearer_e ven_socket_bearer_t;

/// re-define struct
#define VEN_SOCKET_BEARER_DATALINK_AVAILABLE  (BEARER_DATALINK_AVAILABLE)
#define VEN_SOCKET_BEARER_NO_CONNECTED_SOCKET (BEARER_NO_CONNECTED_SOCKET)
#define VEN_SOCKET_STATUS_NUM                 (BEARER_STATUS_NUM)
typedef Mserv_socket_bearer_status_e ven_socket_bearer_status_ex_t;

/// re-define struct
typedef Mserv_socket_linger_t ven_socket_linger_t;
/// re-define struct
typedef Mserv_socket_t ven_socket_t;
/// re-define struct
typedef Mserv_socket_datalink_status_rsp_info_t ven_socket_datalink_status_rsp_info_t;
/// re-define struct
typedef Mserv_socket_bearer_status_rsp_info_t ven_socket_bearer_status_rsp_info_t;
/// re-define struct
typedef Mserv_socket_status_rsp_info_t ven_socket_status_rsp_info_ex_t;
/// re-define struct
typedef MservBearerGprsProfile_t ven_socket_gprs_profile_ex_t;
/// re-define struct
typedef MservBearerWiFiProfile_t ven_socket_wifi_profile_ex_t;
/// re-define struct
typedef MservSocketNetworkProfile_t ven_socket_network_profile_ex_t;

#ifdef __cplusplus
extern "C"
{
#endif/* __cplusplus */

typedef void (*ven_socket_recv_cbfunc_t)(ven_socket_t *s, u8 *buf, s32 len);
typedef void (*ven_socket_recvfrom_cbfunc_t)(ven_socket_t *s, u8 *buf, s32 len, struct sockaddr *from, s32 fromlen);
typedef void (*ven_socket_connect_cbfunc_t)(ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_gethostbyname_cbfunc_t)(u8 ti, struct hostent *host);
typedef void (*ven_socket_send_cbfunc_t)(ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_sendto_cbfunc_t)(ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_closesocket_cbfunc_t)(ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_create_datalink_cbfunc_t)(ven_socket_ret_t result);
typedef void (*ven_socket_close_datalink_cbfunc_t)(ven_socket_ret_t result);
typedef void (*ven_socket_status_cbfunc_t)(ven_socket_ret_t result);
typedef void (*ven_socket_status_cbfunc_ex_t)(void *pvUserData, ven_socket_status_rsp_info_ex_t *pinfo);
typedef void (*ven_socket_close_all_datalinks_ex_cbfunc_t)(ven_socket_bearer_t bearer, void* pvUserData, ven_socket_ret_t result);
typedef void (*ven_socket_ping_cbfunc_t)(u8 ti, ven_socket_ret_t result);


//////////////////////////////////////////////////////////////////////////
///                 SDK for Multi-Bearer                               ///
//////////////////////////////////////////////////////////////////////////

/** ven_socket_create_datalink_ex   

@brief  The interface is used to create GPRS datalink synchronously.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.
@param   psProfile [in]
           The network profile used to create GPRS/WiFi datalink

@retval  VEN_SOCKET_RET_SUCCESS                       It means create datalink successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when creating datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
@retval  VEN_SOCKET_RET_DATA_LINK_ALREADY_ACTIVATED   It means the caller's has created one datalink.
@retval  VEN_SOCKET_RET_DATA_LINK_KO                  It means create datalink fail.
@retval  VEN_SOCKET_RET_NOT_SUPPORT                   The bearer is not supported.
*/
ven_socket_ret_t ven_socket_create_datalink_ex(u32 handle, ven_socket_network_profile_ex_t *psProfile);

/** ven_socket_create_datalink_async_ex  

@brief  The interface is used to create GPRS datalink asynchronously.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.
@param   profile [in]
           The network profile used to create GPRS datalink
@param   create_datalink_ex_cb [in]
           The callback function used to notify the result of creating datalink asynchronously.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified by callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when creating datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
@retval  VEN_SOCKET_RET_DATA_LINK_ALREADY_ACTIVATED   It means the caller's has created one datalink.
@retval  VEN_SOCKET_RET_DATA_LINK_KO                  It means create datalink fail.
@retval  VEN_SOCKET_RET_NOT_SUPPORT                   The bearer is not supported.
*/
/**  ven_socket_create_datalink_cbfunc_t create_datalink_ex_cb

@brief It's callback function for create datalink asynchronously.

@param   result
           The result to create datalink asynchronously.
*/
ven_socket_ret_t ven_socket_create_datalink_async_ex(u32 handle, ven_socket_network_profile_ex_t *psProfile, ven_socket_create_datalink_cbfunc_t create_datalink_ex_cb);

/** ven_socket_close_datalink_ex

@brief  The interface is used to close datalink synchronously.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.

@retval  VEN_SOCKET_RET_SUCCESS                       It means close datalink is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when closing datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_close_datalink_ex(u32 handle);

/** ven_socket_close_datalink_async_ex

@brief  The interface is used to close datalink asynchronously.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.
@param   close_datalink_cb  [in]
           The callback function is used to notify the result of closing a datalink asynchronously.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified by callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when closing datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_close_datalink_cbfunc_t close_datalink_ex_cb

@brief It's callback function for close datalink asynchronously.

@param   result
           The result to close datalink asynchronously.
*/
ven_socket_ret_t ven_socket_close_datalink_async_ex(u32 handle, ven_socket_close_datalink_cbfunc_t close_datalink_ex_cb);



ven_socket_ret_t ven_socket_close_all_datalinks_ex(u32 handle, ven_socket_bearer_t bearer);
ven_socket_ret_t ven_socket_close_all_datalinks_async_ex(u32 handle, ven_socket_bearer_t bearer, void *pvUserData, ven_socket_close_all_datalinks_ex_cbfunc_t close_all_datalinks_cb);

//////////////////////////////////////////////////////////////////////////
///         Status indication sdk for Multi-Bearer                     ///
//////////////////////////////////////////////////////////////////////////

ven_socket_ret_t ven_socket_reg_bearer_status_cb_ex(u32 handle, void *pvUserData, ven_socket_status_cbfunc_ex_t status_cb_ex);
ven_socket_ret_t ven_socket_dereg_bearer_status_cb_ex(u32 handle, ven_socket_status_cbfunc_ex_t status_cb_ex);

//////////////////////////////////////////////////////////////////////////
///                 Deprecated SDK for GPRS                            ///
//////////////////////////////////////////////////////////////////////////

/** ven_socket_data_link_exist   

@brief  The interface is used to check if GPRS datalink exists.

@retval  TRUE        If GPRS datalink exists.
@retval  FALSE       If GPRS datalink doesn't exist.
*/
bool ven_socket_data_link_exist(void);

/**     ven_socket_create_datalink   

@brief   The interface is used to create GPRS datalink synchronously.
         This synchronous call may cost 0 ~ 90s.
         Gprs supports 2 pdp context now.

@param   handle  [in]
          The vendor handle which is getting from ven_handle_open function.
@param   simid   [in]
           It means SIM id. SIM_ONE  means SIM1 and SIM_TWO means SIM2.
		   Otherwise, it's an invalid value.
@param   profile [in]
           The network profile used to create GPRS datalink.

@retval  VEN_SOCKET_RET_SUCCESS                       It means create datalink successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means create datalink fail due to out of system resource(s). 
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 It means current operation can't be executed due to out of memory.
@retval  VEN_SOCKET_RET_DATA_LINK_ALREADY_ACTIVATED   It means the caller's has created one datalink.
@retval  VEN_SOCKET_RET_DATA_LINK_KO                  It means create datalink fail.

@example f
*/
ven_socket_ret_t ven_socket_create_datalink(u32 handle, u8 simid, ven_setting_network_profile_t *profile);

/** ven_socket_create_datalink_async  

@brief  The interface is used to create GPRS datalink asynchronously.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.
@param   simid   [in]
           It means SIM id. 0 means SIM1 and 1 means SIM2.
           Otherwise, it's an invalid value.
@param   profile [in]
           The network profile used to create GPRS datalink
@param   create_datalink_cb [in]
           The callback function used to notify the result of creating datalink asynchronously.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified by callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when creating datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
@retval  VEN_SOCKET_RET_DATA_LINK_ALREADY_ACTIVATED   It means the caller's has created one datalink.
@retval  VEN_SOCKET_RET_DATA_LINK_KO                  It means create datalink fail.
*/
/**  ven_socket_create_datalink_cbfunc_t create_datalink_cb

@brief It's callback function for create datalink asynchronously.

@param   result
    The result to create datalink asynchronously.
*/
ven_socket_ret_t ven_socket_create_datalink_async(u32 handle, u8 simid, ven_setting_network_profile_t *profile, ven_socket_create_datalink_cbfunc_t create_datalink_cb);

/** ven_socket_query_datalink_available

@brief  The interface is used to query whether there is GPRS datalink available.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.
@param   profile [in]
           The network profile used to query GPRS datalink
@param   pModId  [in,out]
           It means SIM id. 0 means SIM1 and 1 means SIM2.
@param   pAvailable [in,out]
           It means the pModId is available or not

@retval  VEN_SOCKET_RET_SUCCESS                       It means the query operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when querying datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_query_datalink_available(u32 handle, ven_setting_network_profile_t *profile, u8 *pModId, bool *pAvailable);

/** ven_socket_close_datalink

@brief  The interface is used to close datalink synchronously.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.

@retval  VEN_SOCKET_RET_SUCCESS                       It means close datalink is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when closing datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_close_datalink(u32 handle);

/** ven_socket_close_datalink_async

@brief  The interface is used to close datalink asynchronously.

@param   handle  [in]
           The vendor handle which is getting from ven_handle_open function.
@param   close_datalink_cb  [in]
           The callback function is used to notify the result of closing a datalink asynchronously.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified by callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when closing datalink.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_close_datalink_cbfunc_t close_datalink_cb

@brief It's callback function for close datalink asynchronously.

@param   result
           The result to close datalink asynchronously.
*/
ven_socket_ret_t ven_socket_close_datalink_async(u32 handle, ven_socket_close_datalink_cbfunc_t close_datalink_cb);

/** ven_socket_createsocket

@brief  The interface is used to create socket.

@param   handle   [in]
           The vendor handle which is getting from ven_handle_open function.
@param   af       [in]
@param   type     [in]
@param   protocol [in]
@param   Output   [out]
           It's a socket handle(structure).

@retval  VEN_SOCKET_RET_SUCCESS                       It means create socket successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when creating socket.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_createsocket(u32 handle, s32 af, s32 type, s32 protocol, ven_socket_t *Output);

/** ven_socket_closesocket

@brief  The interface is used to close socket synchronously.

@param   s   [in]
           The socket which you want to close synchronously.

@retval  VEN_SOCKET_RET_SUCCESS                       It means close socket successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when closing socket.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_closesocket(ven_socket_t *s);

/** ven_socket_closesocket_async   

@brief  The interface is used to close socket asynchronously.

@param   s [in]
           The socket which you want to close asynchronously.
@param   close_cb [in]
           The callback function is used to notify the result of closing socket asynchronously.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified through callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when closing socket.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_closesocket_cbfunc_t close_cb

@brief It's callback function for close socket asynchronously.

@param   s
           The socket which you want to close asynchronously.
@param   result 
           It's the result to close socket asynchronously.
*/
ven_socket_ret_t ven_socket_closesocket_async(ven_socket_t *s, ven_socket_closesocket_cbfunc_t close_cb);

//////////////////////////////////////////////////////////////////////////
///         Deprecated status indication sdk for GPRS                  ///
//////////////////////////////////////////////////////////////////////////

/** ven_socket_regStatusCB

@brief  The interface is used to listen whether datalink is disconnection due to network disconnected.

@param   handle    [in]
           The vendor handle which is getting from ven_handle_open function.
@param   status_cb [in]
           The callback function you used to listen the status change of a datalink.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the registration is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when registering status callback function.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_status_cbfunc_t status_cb

@brief It's callback function for status change listener.

@param   result
           The result to change datalink status.
*/
ven_socket_ret_t ven_socket_regStatusCB(u32 handle, ven_socket_status_cbfunc_t status_cb);


/** ven_socket_deregStatusCB

@brief  The interface is used de-register the listener to listen whether datalink is disconnection due to network disconnected.

@param   handle    [in]
           The vendor handle which is getting from ven_handle_open function.
@param   status_cb [in]
           The callback function you want to de-register.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the de-registration is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when de-registering status callback function.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_deregStatusCB(u32 handle, ven_socket_status_cbfunc_t status_cb);

//////////////////////////////////////////////////////////////////////////
///                 Common SDK for GPRS/Multi-Bearer                   ///
//////////////////////////////////////////////////////////////////////////

/** ven_socket_connect

@brief  The interface is used to connect a socket synchronously, identified by its socket structure.

@param   s [in]
           A socket handle(struct) identifying an unconnected socket.
@param   name [in]
           A pointer to the sockaddr structure to which the connection should be established.
@param   namelen [in]
           The length, in bytes, of the sockaddr structure pointed to by the name parameter.

@retval  VEN_SOCKET_RET_SUCCESS                       It means socket connects successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when connecting socket.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_connect(ven_socket_t *s, const struct sockaddr  *name, s32 namelen);

/** ven_socket_connect_async   

@brief  The interface is used to connect a socket asynchronously, identified by its socket structure.

@param   s [in]
           A socket handle(struct) identifying an unconnected socket.
@param   name [in]
           A pointer to the sockaddr structure to which the connection should be established.
@param   namelen [in]
           The length, in bytes, of the sockaddr structure pointed to by the name parameter.
@param   connect_cb [in]
           The callback function used to notify the result of connection.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified through callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when connecting socket.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_connect_cbfunc_t connect_cb

@brief It's callback function for connect socket asynchronously.

@param   s
           The socket which connect asynchronously.
@param   result
           The result to connect.
*/
ven_socket_ret_t ven_socket_connect_async(ven_socket_t *s, const struct sockaddr  *name, s32 namelen, ven_socket_connect_cbfunc_t connect_cb);

/** ven_socket_recv

@brief  The interface is used to receive on specified TCP socket synchronously.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   buf [out]
           A pointer to the buffer to receive the incoming data.
@param   len [in]
           The length, in bytes, of the buffer pointed to by the buf parameter.
@param   flags [in]
           A set of flags that influences the behavior of this function.
@param   recvlen [in,out]
           It indicates the number of bytes received in buf.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the socket receives data successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when receiving data.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_recv(ven_socket_t *s, u8 *buf, s32 len, s32 flags, s32 *recvlen);

/** ven_socket_recvfrom

@brief  The interface is used to receive on specified UDP socket synchronously.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   buf [in,out]
           A pointer to the buffer to receive the incoming data.
@param   len [in]
           The length, in bytes, of the buffer pointed to by the buf parameter.
@param   flags [in]
           A set of flags that influences the behavior of this function.
@param   from [in,out]
           A pointer to a buffer in a sockaddr structure that will hold the source address upon return.
@param   fromlen [in]
           A pointer to the size, in bytes, of the buffer pointed to by the from parameter.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the socket receives data successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when receiving data.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_recvfrom(ven_socket_t *s, u8 *buf, s32 len, s32 flags, struct sockaddr *from, s32 *fromlen, s32 *recvlen);

/** ven_socket_send   

@brief  The interface is used to send data through a specified TCP socket synchronously.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   buf [in]
           A pointer to the buffer to receive the incoming data.
@param   len [in]
           The length, in bytes, of the buffer pointed to by the buf parameter.
@param   flags [in]
           A set of flags that influences the behavior of this function.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the socket sends data successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when sending data.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_send(ven_socket_t *s, const u8  *buf, s32 len, s32 flags);

/** ven_socket_send_async   

@brief  The interface is used to send data through a specified TCP socket asynchronously.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   buf [in]
           A pointer to the buffer to receive the incoming data.
@param   len [in]
           The length, in bytes, of the buffer pointed to by the buf parameter.
@param   send_cb [in]
           The callback function used to notify the result of the asynchronously send operation.
@param   flags [in]
           A set of flags that influences the behavior of this function.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified through callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when sending data.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_send_cbfunc_t send_cb

@brief It's callback function for sending data asynchronously.

@param   s
           The socket which send asynchronously.
@param   result
           The result to send.
*/
ven_socket_ret_t ven_socket_send_async(ven_socket_t *s, const u8  *buf, s32 len, ven_socket_send_cbfunc_t send_cb, s32 flags);

/** ven_socket_sendto   

@brief  The interface is used to send data through a specified UDP socket synchronously.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   buf [in]
           A pointer to the buffer to receive the incoming data.
@param   len [in]
           The length, in bytes, of the buffer pointed to by the buf parameter.
@param   flags [in]
           A set of flags that influences the behavior of this function.
@param   to [in]
           A pointer to a sockaddr structure that contains the address of the target socket.
@param   tolen [in]
            The size, in bytes, of the address pointed to by the to parameter.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the socket sends data successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when sending data.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_sendto(ven_socket_t *s, const u8  *buf, s32 len, s32 flags, const struct sockaddr  *to, s32 tolen);

/** ven_socket_sendto_async

@brief  The interface is used to send data through a specified UDP socket asynchronously.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   buf [in]
           A pointer to the buffer to receive the incoming data.
@param   len [in]
           The length, in bytes, of the buffer pointed to by the buf parameter.
@param   sendto_cb [in]
           The callback function used to notify the result of asynchronous send operation.
@param   flags [in]
           A set of flags that influences the behavior of this function.
@param   to [in]
           A pointer to a sockaddr structure that contains the address of the target socket.
@param   tolen [in]
           The size, in bytes, of the address pointed to by the to parameter.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified through callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when sending data.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_send_cbfunc_t send_cb

@brief It's callback function for sending data asynchronously.

@param   s
           The socket which send asynchronously.
@param   result
           The result to send.
*/
ven_socket_ret_t ven_socket_sendto_async(ven_socket_t *s, const u8  *buf, s32 len, ven_socket_sendto_cbfunc_t sendto_cb, s32 flags, const struct sockaddr *to, s32 tolen);

/** ven_socket_getsockopt

@brief  The interface is used to retrieve socket option.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   level [in]
           The level at which the option is defined. (ex: VEN_SOL_SOCKET)
@param   optname [in]
           The socket option for which the value is to be set. (ex: VEN_SO_KEEPALIVE)
@param   optval [out]
           A pointer to the buffer in which the value for the requested option is to be returned.
@param   optlen [in]
           The size, in bytes, of the buffer pointed to by the optval parameter.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when retrieving socket option.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_getsockopt(ven_socket_t *s, s32 level, s32 optname, s8* optval, s32* optlen);

/** ven_socket_setsockopt

@brief  The interface is used to set socket option.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   level [in]
           The level at which the option is defined. (ex: VEN_SOL_SOCKET)
@param   optname [in]
           The socket option for which the value is to be set. (ex: VEN_SO_KEEPALIVE)
@param   optval [in]
           A pointer to the buffer in which the value for the requested option is specified.
@param   optlen [in]
           The size, in bytes, of the buffer pointed to by the optval parameter.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when setting socket option.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_setsockopt(ven_socket_t *s, s32 level, s32 optname, s8* optval, s32 optlen);

/** ven_socket_shutdown

@brief  The interface is used to disable sends or receives on a specific socket.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.
@param   how [in]
           A flag that describes what types of operation will no longer to be allowed.
		   Possible values for this flag are listed in ven_socket.h.
		   Value: VEN_SD_RECV, VEN_SD_SEND, and VEN_SD_BOTH.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when executing the operation.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_shutdown(ven_socket_t *s, s32 how);

/** ven_socket_suspend

@brief  The interface is used to suspend the receive callback to receive data.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when executing the operation.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_suspend(ven_socket_t *s);

/** ven_socket_resume

@brief  The interface is used to resume the asynchronous receiving callback function to receive data.

@param   s [in]
           The socket handle(struct) that identifies a connected socket.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when executing the operation.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_resume(ven_socket_t *s);

/** ven_socket_regRecvCB

@brief  The interface is used to register asynchronous receiving callback function on a specific TCP socket.

@param   s [in]
           The socket handle(struct).
@param   recv_cb [in]
           The callback function used to notify the result of receiving data on specified TCP socket.
@param   flags [in]
           A set of flags that influences the behavior of this function.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when registering asynchronous receiving callback function.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_recv_cbfunc_t recv_cb

@brief It's callback function for receiving data asynchronously.

@param   s
           The socket which send asynchronously.
@param   buf
           The received buffer.
@param   len
           The received data length, in bytes.
*/
ven_socket_ret_t ven_socket_regRecvCB(ven_socket_t *s, ven_socket_recv_cbfunc_t recv_cb, s32 flags);

/** ven_socket_regRecvFromCB   

@brief  The interface is used to register asynchronous receiving callback function on a specific UDP socket.

@param   s [in]
           The socket handle(struct).
@param   recv_cb [in]
           The callback function used to notify the result of receiving data on specified UDP socket.
@param   flags [in]
           A set of flags that influences the behavior of this function.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when registering asynchronous receiving callback function.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_recvfrom_cbfunc_t recv_cb

@brief It's callback function for receiving data asynchronously.

@param   s
           The socket which send asynchronously.
@param   buf
           The received buffer.
@param   len
           The received data length, in bytes.
*/
ven_socket_ret_t ven_socket_regRecvFromCB(ven_socket_t *s, ven_socket_recvfrom_cbfunc_t recv_cb, s32 flags);

/** ven_socket_gethostbyname

@brief  The interface is used to query the domain name system synchronously.

@param   handle [in]
           The vendor handle which is getting from ven_handle_open function.
@param   name [in]
           A pointer to the null-terminated name of the host to resolve.
@param   host [in, out]
           If no error occurs, ven_socket_gethostbyname filled the result with hostent structure.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the operation is successfully.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when querying DNS.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
ven_socket_ret_t ven_socket_gethostbyname(u32 handle, const u8  *name, struct hostent *host);

/** ven_socket_gethostbyname_async

@brief  The interface is used to query the domain name system asynchronously.

@param   handle [in]
           The vendor handle which is getting from ven_handle_open function.
@param   name [in]
           A pointer to the null-terminated name of the host to resolve.
@param   ti [in]
           The transition id for the request.
@param   host [in, out]
           If no error occurs, ven_socket_gethostbyname filled the result with hostent structure.
@param   gethostbyname_cb [in]
           The callback function used to notify the DNS result.

@retval  VEN_SOCKET_RET_SUCCESS                       It means the asynchronous operation is executing, the result will be notified through callback.
@retval  VEN_SOCKET_RET_BAD_PARAM                     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED                        It means some error occurs when querying DNS.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY                 Current operation can't execute due to out of memory.
*/
/**  ven_socket_recvfrom_cbfunc_t recv_cb

@brief It's callback function for receiving data asynchronously.

@param   ti
           The transaction id for query DNS.
@param   host
           The query result.
*/
ven_socket_ret_t ven_socket_gethostbyname_async(u32 handle, const u8  *name, u8 *ti, struct hostent *host, ven_socket_gethostbyname_cbfunc_t gethostbyname_cb);


//////////////////////////////////////////////////////////////////////////
///                 Utility for ip convert                             ///
//////////////////////////////////////////////////////////////////////////

/** ven_socket_htonl

@brief  The interface is used to convert a u32 from host to TCP/IP network byte order (which is big-endian).

@param  hostlong [in]
          The u32 value you want to convert to TCP/IP network byte order (which is big-endian).

@retval The ven_socket_htonl function returns the value in TCP/IP's network byte order.
*/
u32 ven_socket_htonl(u32 hostlong);

/** ven_socket_htons   

@brief  The interface is used to convert a u16 from host to TCP/IP network byte order (which is big-endian).

@param  hostshort [in]
          The u16 value you want to convert to TCP/IP network byte order (which is big-endian).

@retval  The ven_socket_htons function returns the value in TCP/IP's network byte order.
*/
u16 ven_socket_htons(u16 hostshort);

/** ven_socket_inet_addr   

@brief  The interface is used to converts a string containing an IPv4 dotted-decimal address into proper address for u32.

@param  cp [in]
          An IPv4 dotted-decimal address.

@retval If no error occurs, the ven_socket_inet_addr function returns an u32 value containing a
        suitable binary representation of the Internet address given.
*/
u32 ven_socket_inet_addr(const s8 *cp);

/** ven_socket_inet_ntoa

@brief  The interface is used to convert an (IPv4) Internet network address into an ASCII string
        in Internet standard dotted-decimal format.

@param  in [in]
		  An in_addr structure that represents an Internet host address.
@param  ipstr [out]
		  If no error occurs, ven_socket_inet_ntoa will write the text address in standard "." notation in buffer ipstr.

*/
void ven_socket_inet_ntoa(struct in_addr in, s8 *ipstr);

/** ven_socket_inet_aton

@brief  The interface is used to convert an (IPv4) Internet network address into an ASCII string in Internet standard dotted-decimal format.

@param  s [in]
          A text address in standard "." notation.
@param  addr [out]
		  If no error occurs, ven_socket_inet_aton will convert s as an in_addr structure that represents an Internet host address.

@retval 0 means fail, 1 means success.
*/
s32 ven_socket_inet_aton(const s8 *s, struct in_addr *addr);

/** ven_socket_ntohl   

@brief  The interface is used to convert a u32 value from TCP/IP network order to host byte order(which is little-endian on Intel processors).

@param  netlong [in]
          A u32 value you want to convert to host byte order(which is little-endian on Intel processors).

@retval The ven_socket_ntohl function returns the value supplied in the netlong parameter with the byte order reversed.
        If netlong is already in host byte order, then this function will reverse it.
		It's up to the application to determine if the byte order must be reversed.
*/
u32 ven_socket_ntohl(u32 netlong);

/** ven_socket_ntohs

@brief  The interface is used to convert a u16 value from TCP/IP network byte order to host byte order(which is little-endian on Intel processors).

@param  netshort [in]
          A u16 value in TCP/IP network byte order.

@retval The ven_socket_ntohs function returns the value in host byte order.
        If the netshort parameter is already in host byte order, then the function will reverse it.
		It's up to the application to determine if the byte order must be reversed.
*/
u16 ven_socket_ntohs(u16 netshort);

//////////////////////////////////////////////////////////////////////////
///                Database function prototypes                        ///
//////////////////////////////////////////////////////////////////////////

/** ven_socket_gethostbyaddr

@brief  The interface is used to retrieve the host information corresponding to a network address.

@param  addr [in]
          A pointer to an address in network byte order.
@param  len  [in]
          The length, in bytes, of the address.
@param  type [in]
          
@retval If no error occurs, ven_socket_gethostbyaddr returns a pointer to the hostent structure.
        Otherwise, it returns a null pointer.
*/
struct hostent  *ven_socket_gethostbyaddr(const u8  *addr, s32 len, s32 type);

/** ven_socket_allocHostent   

@brief  The interface is used to allocate a hostent structure.

@retval If no error occurs, ven_socket_allocHostent returns a pointer to the hostent structure.
        Otherwise, it returns a null pointer.
*/
struct hostent *ven_socket_allocHostent(void);

/** ven_socket_freeHostent

@brief  The interface is used to release a hostent structure.

@param  host [in]
          A pointer to a hostent structure you want to release.

*/
void ven_socket_freeHostent(struct hostent *host);

/** ven_socket_gethostname

@brief  The interface is used to retrieve the standard host name for the local device.

@param  name [out]
          A pointer to a buffer that receives the local device name.
@param  namelen [in]
          The length, in bytes, of the buffer pointed to by the name parameter.

@retval VEN_SOCKET_RET_FAILED   If it's fail.
        VEN_SOCKET_RET_SUCCESS  It it's successful.
*/
ven_socket_ret_t ven_socket_gethostname(u8  *name, s32 namelen);

/** ven_socket_getservbyport

@brief  The interface is used to retrieve service information corresponding to a port and protocol.

@param  port  [in]
          Port for a service, in network byte order.
@param  proto [in]
          Optional pointer to a protocol name.
		  If it's NULL, ven_socket_getservbyport function returns NULL. 

@retval If no error occurs, it returns a pointer to the servent structure.
        Otherwise, it returns NULL.
*/
struct servent  *ven_socket_getservbyport(s32 port, const u8  *proto);

/** ven_socket_getservbyname

@brief  The interface is used to retrieve service information corresponding to a service name and protocol.

@param  name  [in]
          A pointer to a null-terminated service name.
@param  proto [in]
          A pointer to a null-terminated protocol name.
		  If the pointer is NULL, the ven_socket_getservbyname function return NULL.

@retval If no error occurs, it returns a pointer to the servent structure.
        Otherwise, it returns NULL.
*/
struct servent  *ven_socket_getservbyname(const u8  *name, const u8  *proto);

/** ven_socket_getprotobynumber

@brief  The interface is used to retrieve protocol information corresponding to a protocol number.

@param  proto  [in]
          Protocol number, in host byte order.

@retval If no error occurs, it returns a pointer to the servent structure.
        Otherwise, it returns NULL.
*/
struct protoent  *ven_socket_getprotobynumber(s32 proto);

/** ven_socket_getprotobyname

@brief  The interface is used to retrieve the protocol information corresponding to a protocol name.

@param  name  [in]
          Pointer to a null-terminated protocol name.

@retval If no error occurs, it returns a pointer to the servent structure.
        Otherwise, it returns NULL.
*/
struct protoent  *ven_socket_getprotobyname(const u8  *name);

/** ven_socket_bind (it only support UDP socket now)

@brief  The interface is used to bind socket with specific port

@param  s       [in]
a pointer to a vendor socket descriptor
@param  name    [in]
pointer to a socket address struct.
@param  namelen [in]
size of socket address struct

@retval  VEN_SOCKET_RET_SUCCESS        
@retval  VEN_SOCKET_RET_BAD_PARAM     It means you pass invalid parameter(s).                     
@retval  VEN_SOCKET_RET_FAILED        It means some error occurs when socket binds to specific port.
@retval  VEN_SOCKET_RET_OUT_OF_MEMORY Current operation can't execute due to out of memory.
@retval  VEN_SOCKET_RET_NOT_SUPPORT   It means the API doesn't support the operation in the software version.

*/

ven_socket_ret_t ven_socket_bind(ven_socket_t *s, const struct sockaddr *name, s32 namelen);

#ifdef __cplusplus
}
#endif/* __cplusplus */



#endif //__VEN_SOCKET_DEFINE_H_
