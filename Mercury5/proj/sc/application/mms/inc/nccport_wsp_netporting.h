
/**
 * @file
 * Wireless Session Protocol Network Porting Layer
 *
 * Basic support functions that are needed by the Wireless Session Protocol.
 *
 * <!-- #interface list begin -->
 * \section cpl_wsp_netPorting Interface
 * - NCCPort_wsp_sockStartup()
 * - NCCPort_wsp_sockCleanup()
 * - NCCPort_wsp_socket()
 * - NCCPort_wsp_closeSocket()
 * - NCCPort_wsp_sockGetLastError()
 * - NCCPort_wsp_sendTo()
 * - NCCPort_wsp_recvFrom()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_WSP_NETPORTING_H__
#define __NCCPORT_WSP_NETPORTING_H__

#include <ncc_types.h>

#define WAPSOCKET int32_t
#define WAP_SOCK_SUCCESS    0
#define WAP_SOCK_ERROR      -1
#define WAP_SOCK_PENDING    -2

#ifdef __cplusplus
extern  "C" {
#endif

#ifdef NCC_WSP_TIMER_DRIVER
typedef void (*NCCPort_wsp_timerFunc) (void);
#endif //NCC_WSP_TIMER_DRIVER

/**
 * Initialize the networking module
 *   \return return WAP_SOCK_SUCCESS if success,else return WAP_SOCK_ERROR;
 *   \sa  NCCPort_wsp_sockCleanup
 */
int32_t NCCPort_wsp_sockStartup(void);

/**
 * Terminate and cleanup the networking module
 *       \return return WAP_SOCK_SUCCESS if success,else return WAP_SOCK_ERROR;
 *   \sa  NCCPort_wsp_sockCleanup
 */
int32_t NCCPort_wsp_sockCleanup( void );

int32_t NCCPORT_wsp_realShutdown( void );

/**
 * Create a UDP socket.
 *   \param ipNumber     Target ip address in host byte order .
 *   \param portNumber   Target port number in host byte order.
 *   \param sock         Socket description.
 *   \return return WAP_SOCK_SUCCESS if success,else return WAP_SOCK_ERROR;
 *   \sa  NCCPort_wsp_closeSocket
 */
int32_t NCCPort_wsp_socket(uint32_t  ipNumber, uint16_t portNumber,int32_t *sock);

/**
 * Close a UDP socket
 * \param s        Socket descriptor.
 * \return return WAP_SOCK_SUCCESS if success,else return WAP_SOCK_ERROR;
 *   \sa  NCCPort_wsp_socket
 */
int32_t NCCPort_wsp_closeSocket(WAPSOCKET s);

/**
 *  Get the error status for the last operation that failed.
 * \param s        Socket descriptor.
 * \return  return a value indicates the error state.
 */
int32_t NCCPort_wsp_sockGetLastError(WAPSOCKET s);

/**
 * Send data to a specific destination.
 *   \param s        Socket descriptor.
 *   \param buf  Buffer to store message.
 *   \param len  Maximum number of bytes to receive.
 *   \param  ipNumber the target IP address in host byte order.optional.
 *   \param  portNumber the target port number in host byte order.optional.
 *    \return    If no error occurs, returns the total number of bytes sent,
 *           which can be less than the number indicated by len. Otherwise,
 *           a value of WAP_SOCK_ERROR is returned.
 *   \sa     NCCPort_wsp_recvFrom
 */
int32_t NCCPort_wsp_sendTo(WAPSOCKET s,const int8_t *buf,int32_t len,uint32_t  ipNumber, uint16_t portNumber);

#ifdef NCC_WSP_TIMER_DRIVER
int32_t NCCPort_wsp_registerTimerFunc(WAPSOCKET s, NCCPort_wsp_timerFunc timerFunc);

int32_t NCCPort_wsp_getTimerFunc(WAPSOCKET s, NCCPort_wsp_timerFunc *timerFunc);

int32_t NCCPort_wsp_startTimerFunc(WAPSOCKET s);
#endif //NCC_WSP_TIMER_DRIVER

/**
 * Receive a network message
 *   \param s     Socket descriptor.
 *   \param buf  Buffer to store message.
 *   \param len  Maximum number of bytes to receive
 *   \param  ipNumber the target IP address in host byte order.optional.
 *   \param  portNumber the target port number in host byte order.optional.
 *    \return    If no error occurs, returns the number of bytes received. If the connection has been
 *           gracefully closed, the return value is WAP_SOCK_ERROR. Otherwise, a value of WAP_SOCK_PENDING is returned
 *   \sa     NCCPort_wsp_sendTo
 */
int32_t NCCPort_wsp_recvFrom(WAPSOCKET s,int8_t * buf,int32_t len,uint32_t  ipNumber, uint16_t portNumber);

int32_t NCCPort_wsp_getSockVersion(void);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPORT_WSP_NETPORTING_H__ */

