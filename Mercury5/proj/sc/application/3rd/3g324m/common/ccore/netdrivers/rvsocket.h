/***********************************************************************
Filename   : rvsocket.h
Description: enables OS-independent BSD4.4 sockets operations.
************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVISION LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVISION LTD..

RADVISION LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
************************************************************************/

#ifndef RV_SOCKET_H
#define RV_SOCKET_H

#include "rvlog.h"
#include "rvaddress.h"
#include "rvportrange.h"


#if defined(__cplusplus)
extern "C" {
#endif

/* RvSocketInit, RvSocketEnd and RvSocketSourceConstruct function should be defined
 * always. The rest of socket API should be defined only when RV_NET_TYPE != RV_NET_NONE
 */

/********************************************************************************************
 * RvSocketInit
 * Open the Socket Module.
 * INPUT   : None
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RvSocketInit(void);


/********************************************************************************************
 * RvSocketEnd
 * Close the Socket module.
 * INPUT   : None
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RvSocketEnd(void);


/********************************************************************************************
 * RvSocketSourceConstruct
 * Create a log source for the socket module.
 * INPUT   : logMgr - log manager associated with the log source.
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RvSocketSourceConstruct(
    IN RvLogMgr* logMgr);


#if (RV_NET_TYPE != RV_NET_NONE)

/* Error checks to make sure configuration has been done properly */
#if !defined(RV_SOCKET_TYPE) || ((RV_SOCKET_TYPE != RV_SOCKET_BSD) && \
    (RV_SOCKET_TYPE != RV_SOCKET_WIN32_WSA) && (RV_SOCKET_TYPE != RV_SOCKET_PSOS) && \
    (RV_SOCKET_TYPE != RV_SOCKET_NUCLEUS) && (RV_SOCKET_TYPE != RV_SOCKET_NONE) && (RV_SOCKET_TYPE != RV_SOCKET_SYMBIAN))
#error RV_SOCKET_TYPE not set properly
#endif



/* Lets make error codes a little easier to type */
#define RvSocketErrorCode(_e) RvErrorCode(RV_ERROR_LIBCODE_CCORE, RV_CCORE_MODULE_SOCKET, (_e))
    
/* Socket specific error codes */
#define RV_SOCKET_ERROR_EOF RvSocketErrorCode(-513)


#if (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
#include <target.h>
#include <inc/tcp.h>
#include <externs.h>
#endif

#if (RV_OS_TYPE == RV_OS_TYPE_INTEGRITY)
#include <sys/socket.h>
#endif


/* Type declaration of sockets */
#if (RV_SOCKET_TYPE == RV_SOCKET_WIN32_WSA) || \
	((RV_OS_TYPE == RV_OS_TYPE_WINCE) && (_WIN32_WCE >= 400))

#pragma warning(push, 3)
#include <winsock2.h>
#pragma warning(pop)

typedef SOCKET RvSocket;

#elif ((RV_OS_TYPE == RV_OS_TYPE_WINCE) && (_WIN32_WCE < 400))

#pragma warning(push, 3)
#include <winsock.h>
#pragma warning(pop)

typedef SOCKET RvSocket;

#elif (RV_OS_TYPE == RV_OS_TYPE_MOPI)

#include "mmb_rv.h"

typedef T_Mmb_Socket RvSocket;

#define inet_ntoa   Mmb_BsdInetNtoa


/*#elif (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)

typedef void * RvSocket;
*/
#else
/* Other operating systems */
typedef int RvSocket;

#endif

#define RV_INVALID_SOCKET ((RvSocket)(-1))

/* Maximum size of sockaddr struct size we can handle */
#define RV_SOCKET_SOCKADDR4_SIZE sizeof(struct sockaddr_in)

#if (RV_NET_TYPE & RV_NET_IPV6)
#define RV_SOCKET_SOCKADDR_SIZE sizeof(struct sockaddr_in6)
#else
#if (RV_OS_TYPE == RV_OS_TYPE_RTK)
#define RV_SOCKET_SOCKADDR_SIZE sizeof(long)
#else
#define RV_SOCKET_SOCKADDR_SIZE sizeof(struct sockaddr_in)
#endif
#endif

typedef enum
{
    RvSocketProtocolUdp = 0,
    RvSocketProtocolTcp,
    RvSocketProtocolSctp,
    RvSocketProtocolRawIcmp,
    RvSocketProtocolRawSctp,
    RvSocketProtocolEND      /* must be the last value */
} RvSocketProtocol;






/* =========================== */
/* ==== General functions ==== */
/* =========================== */

#if (RV_OS_TYPE != RV_OS_TYPE_MOPI)
/********************************************************************************************
 * RvSocketConstruct
 * Construct a socket object. During construction time, the socket's type of address
 * and protocol must be supplied.
 * A call to RvSocketSetBlocking() must follow the call to this function to set
 * this socket as a blocking or a non-blocking socket.
 * This function is thread-safe.
 * INPUT   : addressType    - Address type of the created socket.
 *           protocolType   - The type of protocol to use (TCP, UDP, etc).
 *           logMgr         - log manager instance
 * OUTPUT:   sock           - Socket to construct
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketConstruct(
    IN  RvInt             addressType,
    IN  RvSocketProtocol  protocolType,
    IN  RvLogMgr*         logMgr,
    OUT RvSocket*         sock);
#endif

/********************************************************************************************
 * RvSocketBind
 * Bind a socket to a local address
 * This function is NOT thread-safe.
 * INPUT   : sock       - Socket to bind
 *           address    - Address to bind socket to
 *           portRange  - Port range to use if address states an ANY port.
 *                        NULL if this parameter should be ignored.
 *           logMgr         - log manager instance
 * RETURN  : RV_OK on success, other on failure.
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketBind(
    IN RvSocket*         sock,
    IN RvAddress*        address,
    IN RvPortRange*      portRange,
    IN RvLogMgr*         logMgr);


/********************************************************************************************
 * RvSocketSetBuffers
 * Sets the send and receive buffer sizes for the specified socket. The default sizes
 * of send and receive buffers are platform dependent. This function may be used
 * to increase the default sizes if larger packets are expected, such as video packets,
 * or to decrease the default size if smaller packets are expected.
 * This function is thread-safe.
 * INPUT   : socket     - Socket whose buffer sizes are to be changed.
 *           sendSize   - The new size of the send buffer. If the size is negative, the existing
 *                        value remains.
 *           recvSize   - The new size of the receive buffer. If the size is negative, the existing
 *                        value remains.
 *           logMgr         - log manager instance
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSetBuffers(
        IN RvSocket*    sock,
        IN RvInt32     sendSize,
        IN RvInt32     recvSize,
        IN RvLogMgr*    logMgr);

/********************************************************************************************
 * RvSocketSetLinger
 * Set the linger time after socket is closed.
 * This function can only be called only on UDP sockets.
 * This function is thread-safe.
 * INPUT   : sock       - Socket to modify
 *           lingerTime - Time to linger in seconds
 *                        Setting this parameter to -1 sets linger off for this socket
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSetLinger(
        IN  RvSocket*   sock,
        IN  RvInt32     lingerTime,
        IN  RvLogMgr*   logMgr);


/********************************************************************************************
 * RvSocketReuseAddr
 * Set the socket as a reusable one (in terms of its address)
 * This allows a TCP server socket and UDP multicast addresses to be used by
 * other processes on the same machine as well.
 * This function has to be called before RvSocketBind().
 * This function is thread-safe.
 * INPUT   : sock     - Socket to modify
 *           logMgr   - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketReuseAddr(
        IN  RvSocket*   sock,
        IN  RvLogMgr*   logMgr);


/********************************************************************************************
 * RvSocketSetBlocking
 * Set blocking/non-blocking mode on a socket.
 * This function must be called after calling RvSocketConstruct(), otherwise, the
 * socket's mode of operation will be determined by each operating system separately,
 * causing applications and stacks to be non-portable.
 * This function is thread-safe.
 * INPUT   : sock       - Socket to modify
 *           isBlocking - RV_TRUE for a blocking socket
 *                        RV_FALSE for a non-blocking socket
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSetBlocking(
        IN RvSocket*    sock,
        IN RvBool       isBlocking,
        IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketSetTypeOfService
 * Set the type of service (DiffServ Code Point) of the socket (IP_TOS)
 * This function is supported by few operating systems.
 * IPV6 does not support type of service.
 * This function is thread-safe.
 * INPUT   : sock           - Socket to modify
 *           typeOfService  - type of service to set
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
*/
RVCOREAPI
RvStatus RVCALLCONV RvSocketSetTypeOfService(
        IN RvSocket*    sock,
        IN RvInt        typeOfService,
        IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketGetTypeOfService
 * Get the type of service (DiffServ Code Point) of the socket (IP_TOS)
 * This function is supported by few operating systems.
 * IPV6 does not support type of service.
 * This function is thread-safe.
 * INPUT   : sock           - socket to modify
 *           logMgr         - log manager instance
 * OUTPUT  : typeOfService  - type of service to set
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketGetTypeOfService(
        IN  RvSocket*    sock,
        IN  RvLogMgr*    logMgr,
        OUT RvInt32*     typeOfService);


/********************************************************************************************
 * RvSocketSetBroadcast
 * Set permission for sending broadcast datagrams on a socket
 * This function is only needed if the stack being ported supports multicast sending.
 * This function is thread-safe.
 * INPUT   : sock           - Socket to modify
 *           canBroadcast   - RV_TRUE for permitting broadcast
 *                            RV_FALSE for not permitting broadcast
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSetBroadcast(
        IN RvSocket*    sock,
        IN RvBool       canBroadcast,
        IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketSetMulticastTtl
 * Set the TTL to use for multicast sockets (UDP)
 * This function is only needed if the stack being ported supports multicast sending.
 * This function is thread-safe.
 * INPUT   : sock       - Socket to modify
 *           ttl        - TTL to set
 *           logMgr     - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSetMulticastTtl(
        IN RvSocket*    sock,
        IN RvInt32      ttl,
        IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketSetMulticastInterface
 * Set the interface to use for multicast packets (UDP)
 * This function is only needed if the stack being ported supports multicast receiving.
 * This function is thread-safe.
 * INPUT   : sock       - Socket to modify
 *           address    - Local address to use for the interface
 *           logMgr     - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSetMulticastInterface(
        IN RvSocket*    sock,
        IN RvAddress*   address,
        IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketJoinMulticastGroup
 * Join a multicast group
 * This function is only needed if the stack being ported supports multicast receiving.
 * This function is thread-safe.
 * INPUT   : sock             - Socket to modify
 *           multicastAddress - Multicast address to join
 *           interfaceAddress - Interface address to use on the local host.
 *                              Setting this to NULL chooses an arbitrary interface
 *           logMgr           - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketJoinMulticastGroup(
    IN RvSocket*    sock,
    IN RvAddress*   multicastAddress,
    IN RvAddress*   interfaceAddress,
    IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketLeaveMulticastGroup
 * Leave a multicast group
 * This function is only needed if the stack being ported supports multicast receiving.
 * This function is thread-safe.
 * INPUT   : sock             - Socket to modify
 *           multicastAddress - Multicast address to leave
 *           interfaceAddress - Interface address to use on the local host.
 *                              Setting this to NULL chooses an arbitrary interface
 *           logMgr           - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketLeaveMulticastGroup(
    IN RvSocket*    sock,
    IN RvAddress*   multicastAddress,
    IN RvAddress*   interfaceAddress,
    IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketSockAddrToAddress
 * Convert a sockaddr struct into an RvAddress struct.
 * This function is thread-safe.
 * INPUT:
 *  sockaddr   - Socket address
 *  socklen    - Socket address length
 * OUTPUT:
 *  address    - Address constructed
 * RETURN:
 *  RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSockAddrToAddress(
    IN  RvUint8*    sockaddr,
    IN  int         socklen,
    OUT RvAddress*  address);


/********************************************************************************************
 * RvSocketAddressToSockAddr
 * Convert an RvAddress struct into a sockaddr struct.
 * This function is thread-safe.
 * INPUT:
 *  address    - Address to convert
 * OUTPUT:
 *  sockaddr   - Socket address constructed
 *  socklen    - Socket address length constructed
 * RETURN:
 *  RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketAddressToSockAddr(
    IN  RvAddress*      address,
    OUT void*           sockaddr,
    OUT int*            socklen);


/* =========================== */
/* ==== functions for TCP ==== */
/* =========================== */


/********************************************************************************************
 * RvSocketConnect
 * Starts a connection between the specified socket and the specified destination.
 * The destination must be running the RvSocketListen() function to receive the
 * incoming connection.
 * In blocking mode, this function returns only when the socket got connected, or
 * on a timeout with a failure return value.
 * In non-blocking mode, this function returns immediately, and when the remote side
 * accepts this connection, this socket will receive the RvSelectConnect event in the
 * select module.
 * This function needs to be ported only if TCP is used by the stack.
 * This function is thread-safe.
 * INPUT   : socket     - Socket to connect
 *           logMgr     - log manager instance
 * OUTPUT  : address    - Remote address to connect this socket to
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketConnect(
        IN RvSocket*    sock,
        IN RvAddress*   address,
        IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketAccept
 * Accept an incoming socket connect request, creating a new socket object.
 * In blocking mode, this function blocks until an incoming connect request to this
 * socket is made.
 * In non-blocking mode, this function will exit immediately and when an incoming
 * connection request to this socket is made, this socket will receive the
 * RvSocketAccept event in the select module.
 * The newSocket object should be regarded as if it was created using
 * RvSocketConstruct().
 * This function needs to be ported only if TCP is used by the stack.
 * This function is thread-safe.
 * INPUT   : socket         - Listening socket receiving the incoming connection
 *           logMgr         - log manager instance
 * OUTPUT  : newSocket      - Accepted socket information
 *           remoteAddress  - Address of remote side of connection
 *                            Can be passed as NULL if not needed
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketAccept(
    IN  RvSocket*    sock,
    IN  RvLogMgr*    logMgr,
    OUT RvSocket*    newSocket,
    OUT RvAddress*   remoteAddress);


/********************************************************************************************
 * RvSocketDontAccept
 *
 * Rejects an incoming socket connect request.
 * This function needs to be ported only if TCP is used by the stack.
 * This function is thread-safe.
 * INPUT   : socket         - Listening socket receiving the incoming connection
 *           logMgr         - log manager
 * OUTPUT  : none
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketDontAccept(
    IN  RvSocket*    sock,
    IN  RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketListen
 * Listens on the specified socket for connections from other locations.
 * In non-blocking mode, when a connection request is received, this socket will receive
 * the RvSocketAccept event in the select module.
 * This function needs to be ported only if TCP is used by the stack.
 * This function is thread-safe.
 * INPUT   : sock           - Listening socket receiving the incoming connection
 *           queuelen       - Length of queue of pending connections
 *           logMgr         - log manager instance
 * OUTPUT  : None.
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketListen(
        IN  RvSocket    *sock,
        IN  RvUint32    queuelen,
        IN  RvLogMgr*   logMgr);


/********************************************************************************************
 * RvSocketShutdown
 * Shutdown a TCP socket. This function should be called before calling
 * RvSocketDestruct() for TCP sockets.
 * In blocking mode, this function blocks until RvSocketDestruct() can be called in
 * a graceful manner to close the connection.
 * In non-blocking mode, when the remote side will close its connection, this socket
 * will receive the RvSocketClose event in the select module and RvSocketDestruct()
 * should be called at that point.
 * This function needs to be ported only if TCP is used by the stack.
 * This function is NOT thread-safe.
 * INPUT   : socket         - Socket to shutdown
 *           cleanSocket    - RV_TRUE if you want to clean the socket before shutting it down.
 *                            this will try to receive from the socket some buffers.
 *                            It is suggested to set this value to RV_TRUE for non-blocking
 *                            sockets.
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketShutdown(
    IN RvSocket*    sock,
    IN RvBool       cleanSocket,
    IN RvLogMgr*    logMgr);


/********************************************************************************************
 * RvSocketDestruct
 * Close a socket.
 * This function is NOT thread-safe.
 * INPUT   : sock           - Socket to shutdown
 *           cleanSocket    - RV_TRUE if you want to clean the socket before shutting it down.
 *                            this will try to receive from the socket some buffers.
 *                            It is suggested to set this value to RV_TRUE for TCP sockets.
 *                            It should be set to RV_FALSE for UDP sockets.
 *           portRange      - Port range to return this socket's port to. If NULL, the
 *                            socket's port will not be added to any port range object.
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketDestruct(
    IN RvSocket*    sock,
    IN RvBool       cleanSocket,
    IN RvPortRange* portRange,
    IN RvLogMgr*    logMgr);

/********************************************************************************************
 * RvSocketClean
 *
 * Read & drop all waiting on the socket data.
 *
 * INPUT   : sock           - Socket to shutdown
 *           logMgr         - log manager pointer
 * OUTPUT  : None
 * RETURN  : none
 */
RVCOREAPI
void RVCALLCONV RvSocketClean(
    IN RvSocket*    sock,
    IN RvLogMgr*    logMgr);

/* ================================ */
/* ==== Send/receive functions ==== */
/* ================================ */

/********************************************************************************************
 * RvSocketSendBuffer
 * Send a buffer on a socket.
 * This function actually copies the given buffer to the operating system's memory
 * for later sending.
 * In blocking mode, this function will block until the buffer is sent to the remote
 * side or upon failure.
 * In non-blocking mode, this function will return immediately, indicating the exact
 * amount of bytes the operating system has processed and sent.
 * This function handles both TCP and UDP sockets. You might need to port only parts
 * of this function if you need only one of these protocols.
 * This function is thread-safe.
 * INPUT   : socket         - Socket to send the buffer on
 *           buffer         - Buffer to send
 *           bytesToSend    - Number of bytes to send from buffer
 *           remoteAddress  - Address to send the buffer to.
 *                            Should be set to NULL on connection-oriented sockets (TCP).
 *           logMgr         - log manager instance
 * OUTPUT  : bytesSent      - Number of bytes we sent
 *                            If less than bytesToSend, then we would block if we tried on a
 *                            blocking socket. The application in this case should wait for the
 *                            RvSelectWrite event in the select module before trying to send
 *                            the buffer again.
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSendBuffer(
    IN  RvSocket*   sock,
    IN  RvUint8*    buffer,
    IN  RvSize_t    bytesToSend,
    IN  RvAddress*  remoteAddress,
    IN  RvLogMgr*   logMgr,
    OUT RvSize_t*   bytesSent);


/********************************************************************************************
 * RvSocketReceiveBuffer
 * Receive a buffer from a socket.
 * In blocking mode, this function will block until a buffer is received on the
 * socket.
 * In non-blocking mode, this function returns immediately, even if there is nothing
 * to be received on this socket at the moment. This function is usually called after
 * RvSelectRead event is received in the select module on this socket, indicating that
 * there is information to receive on this socket.
 * This function handles both TCP and UDP sockets. You might need to port only parts
 * of this function if you need only one of these protocols.
 * This function is thread-safe.
 * INPUT   : socket         - Socket to receive the buffer from
 *           buffer         - Buffer to use for received data
 *           bytesToReceive - Number of bytes available on the given buffer
 *                            For UDP sockets, this value must be higher than the incoming datagram.
 *           logMgr         - log manager instance
 * OUTPUT  : bytesReceived  - Number of bytes that were actually received
 *           remoteAddress  - Address buffer was received from
 *                            Should be given as NULL on connection-oriented sockets (TCP).
 *                            This address is constructed by this function and should be
 *                            destructed by the caller to this function
 * RETURN  : RV_OK on success, other on failure
 *
 * Notes:
 *   * Return value of RV_SOCKET_EOF_ERROR on TCP socket indicates that peer tries
 *     to close this connection. 'bytesReceived' in this case will be 0
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketReceiveBuffer(
    IN  RvSocket*   sock,
    IN  RvUint8*    buffer,
    IN  RvSize_t    bytesToReceive,
    IN  RvLogMgr*   logMgr,
    OUT RvSize_t*   bytesReceived,
    OUT RvAddress*  remoteAddress);


/******************************************************************************
 * rvSocketWasShutdownByPeer
 * Checks, if remote peer shutdown connection to the socket.
 * This function is meaningless for not connection oriented sockets.
 * It is responsibility of caller not to use this function for UDP sockets.
 * This function is thread-safe.
 * INPUT   : socket      - Socket to be checked
 *           logMgr      - log manager instance
 * OUTPUT  : wasShutdown - RV_TRUE, if remote peer shutdown connection
 * RETURN  : RV_OK on success, other on failure
 *
 * Notes:
 *   * Any error on socket except WOULD_BLOCK causes erroneous return value
 */
RvStatus RVCALLCONV rvSocketWasShutdownByPeer(
    IN  RvSocket*  sock,
    IN  RvLogMgr*  logMgr,
    OUT RvBool*    wasShutdown);

/* =========================== */
/* ==== Utility functions ==== */
/* =========================== */

/********************************************************************************************
 * RvSocketGetBytesAvailable
 * Get the number of bytes that are in the receive buffer of the socket.
 * This number might be larger than the return result of a single recv() operation.
 * This is important when dealing with data-gram types of connections (such as UDP).
 * This function is not available by some of the operating systems.
 * This function is NOT thread-safe.
 * INPUT   : socket         - Socket to check
 *           logMgr         - log manager instance
 * OUTPUT  : bytesAvailable - Number of bytes in the receive buffer of the socket
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketGetBytesAvailable(
    IN RvSocket*  sock,
    IN RvLogMgr*  logMgr,
    OUT RvSize_t* bytesAvailable);


/********************************************************************************************
 * RvSocketGetLastError
 * Get the last error that occured on a socket.
 * This function works for synchronous sockets only.
 * The return value is OS-specific. A value of 0 means no error occured.
 * This function is thread-safe.
 * INPUT   : sock     - Socket to check
 *           logMgr         - log manager instance
 * OUTPUT  : lastError  - Error that occured. 0 means no error.
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketGetLastError(
    IN RvSocket* sock,
    IN RvLogMgr* logMgr,
    OUT RvInt32* lastError);


/********************************************************************************************
 * RvSocketGetLocalAddress
 * Get the local address used by this socket.
 * This function is thread-safe.
 * INPUT   : sock     - Socket to check
 *           logMgr   - log manager instance
 * OUTPUT  : address    - Local address
 *                        Must be destructed by the caller to this function
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketGetLocalAddress(
    IN RvSocket  *sock,
    IN RvLogMgr  *logMgr,
    OUT RvAddress* address);


/********************************************************************************************
 * RvSocketGetRemoteAddress
 * Get the remote address used by this socket.
 * This function can only be called only on TCP sockets.
 * This function is thread-safe.
 * INPUT   : sock     - Socket to check
 *           logMgr   - log manager instance
 * OUTPUT  : address  - Remote address
 *                      Must be destructed by the caller to this function
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketGetRemoteAddress(
    IN RvSocket  *sock,
    IN RvLogMgr  *logMgr,
    OUT RvAddress* address);


#if (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)

void RvSocketNucleusTaskDelete(IN RvSocket* socket);

void RvSocketNucleusTaskClean(IN RvSocket* socket);

/********************************************************************************************
 * RvSocketSetSelectEngine
 * Update the socket database - associate a socket with it's select-engine.
 * This function is thread-safe.
 * INPUT   : socket       - Socket to check
 *           selectEngine - select-engine that probes the socket.
 * OUTPUT  : None.
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RvSocketSetSelectEngine(
    IN RvSocket *socket,
    IN void* selectEngine);

STATUS RvNuIsConnected(IN RvSocket socket);

#endif

/********************************************************************************************
* RvSocketSetUDPMaxLength
* Set For Symbian The UDP Maximum Send And receive Buffer Length
* INPUT   : Length Of The Buffers
* RETURN  : RV_OK on success, other on failure
*/
RVCOREAPI void RvSocketSetUDPMaxLength(RvInt numLength);



#if (RV_SOCKET_USE_SHARER == RV_YES)


/**********************************************************************************
 * RvSocketSharerShare
 * "share" a socket using the socket sharer module.
 * INPUT:
 *  sock   - Socket to share
 *  sharableSocket  - the counterpart shared socket
 * RETURN:
 *  RvStatus - RV_OK on success, other on failure.
 */
RvStatus RvSocketSharerShare(
    IN RvLogMgr* logMgr,
    IN RvSocket* sock,
    OUT RvSocket* sharableSocket);


/**********************************************************************************
 * RvSocketSharerMultiShare
 * "share" a set of sockets, using the socket sharer module. this is called right
 * before calling 'select()' function.
 * INPUT:
 *  sock   - a pointer to a set of sockets to share.
 *  width  - the length of the set.
 *  logMgr - the log manager
 * RETURN:
 *  RvStatus - RV_OK on success, other on failure.
 */
RvStatus RvSocketSharerMultiShare(
    IN OUT RvSocket* sock,
    IN int width,
    IN RvLogMgr* logMgr);

/**********************************************************************************
 * RvSocketSharerClose
 * close a socket in the socket sharer module.
 * INPUT:
 *  _sock   - Socket to close
 * RETURN:
 *  RvStatus - RV_OK on success, other on failure.
 */
void RvSocketSharerClose(IN RvSocket* sock);


#endif /* (RV_SOCKET_USE_SHARER == RV_YES) */


#if (RV_OS_TYPE == RV_OS_TYPE_MOPI)

RVCOREAPI
RvStatus RVCALLCONV RvSocketConstructWithCid(
    IN  RvInt             addressType,
    IN  RvSocketProtocol  protocolType,
    IN  RvLogMgr*         logMgr,
    IN  RvUint16     	  cid,
    OUT RvSocket*         sock);


int RvSocketMopiSetConnectionId(RvSocket socket, RvUint16 cid);
#if defined(_RV_SIP_USER_CONFIG)
/* since we may have difficulties determining the right context/stack that called the 
   'RvSocketConstruct' API, we differentiate the cases by the stack context. the way 
   to do it, is by the a macro defined solely per single stack.
   for SIP we use '_RV_SIP_USER_CONFIG' that is defined in RvSipUserConfig.h */
extern RvUint16 SipConnectionId;
#define RvSocketConstruct(a, b, c, d) RvSocketConstructWithCid((a), (b), (c), SipConnectionId, (d))

#else
/* There can also be calls for socketConstruct from within the common core, rather 
   than a direct call from a stack that were initiated by SIP stack, so we use here
   the SIP cid */
extern RvUint16 SipConnectionId;
#define RvSocketConstruct(a, b, c, d) RvSocketConstructWithCid((a), (b), (c), SipConnectionId, (d))

#endif
#endif


#if (RV_NET_TYPE & RV_NET_SCTP)

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/sctp.h>



/* ============================ */
/* ==== functions for SCTP ==== */
/* ============================ */


/* Data structure wrappers for the "Sockets API Extensions for SCTP" */


/* setsockopt option names */
#define RV_SCTP_INITMSG         SCTP_INITMSG
#define RV_SCTP_NODELAY         SCTP_NODELAY
#define RV_SCTP_PRIMARY_ADDR    SCTP_PRIMARY_ADDR
#define RV_SCTP_EVENTS          SCTP_EVENTS


/* --- sctp_initmsg structure --------------------------------*/
typedef struct sctp_initmsg RvSctpInitMessage;              /**/
                                                            /**/
#define RvSctpNumOstreams       sinit_num_ostreams          /**/
#define RvSctpMaxInstreams      sinit_max_instreams         /**/
#define RvSctpMaxAttempts       sinit_max_attempts          /**/
#define RvSctpMaxInitTimeout    sinit_max_init_timeo        /**/
/*------------------------------------------------------------*/


/* --- sctp_prim structure -----------------------------------*/
#ifdef  RV_SCTP_HAVE_SETPRIM
#define sctp_prim sctp_setprim
#endif

typedef struct sctp_prim RvSctpPrimaryAddr;
                                                            /**/
#define RvSctpSspAssocId        ssp_assoc_id                /**/
#define RvSctpSspAddr           ssp_addr                    /**/
/*------------------------------------------------------------*/


/* --- sctp_event_subscribe structure ------------------------*/
typedef struct sctp_event_subscribe RvSctpEventRegister;    /**/
                                                            /**/
#define RvSctpDataIoEvent       sctp_data_io_event          /**/
#define RvSctpAssocEvent        sctp_association_event      /**/
#define RvSctpAddressEvent      sctp_address_event          /**/
#define RvSctpSendFailEvent     sctp_send_failure_event     /**/
#define RvSctpPeerErrEvent      sctp_peer_error_event       /**/
#define RvSctpShutdownEvent     sctp_shutdown_event         /**/
/*------------------------------------------------------------*/


/* --- sctp_notification structure -------------------------------*/
typedef union sctp_notification RvSctpNotification;             /**/
                                                                /**/
/* notification header */                                       /**/
                                                                /**/
/* sn_type */                                                   /**/
#define RV_SCTP_ASSOC_CHANGE    SCTP_ASSOC_CHANGE               /**/
#define RV_SCTP_PADDR_CHANGE    SCTP_PEER_ADDR_CHANGE           /**/
#define RV_SCTP_REMOTE_ERROR    SCTP_REMOTE_ERROR               /**/
#define RV_SCTP_SEND_FAILED     SCTP_SEND_FAILED                /**/
#define RV_SCTP_SHUTDOWN_EVENT  SCTP_SHUTDOWN_EVENT             /**/
#define RV_SCTP_ADAPTION_IND    SCTP_ADAPTION_INDICATION        /**/
#define RvSctpSnType            sn_header.sn_type               /**/
                                                                /**/
/* notification elements */                                     /**/
                                                                /**/
/* sctp_assoc_change: sac_state */                              /**/
#define RV_SCTP_COMM_UP         SCTP_COMM_UP                    /**/
#define RV_SCTP_COMM_LOST       SCTP_COMM_LOST                  /**/
#define RV_SCTP_RESTART         SCTP_RESTART                    /**/
#define RV_SCTP_SHUTDOWN_COMP   SCTP_SHUTDOWN_COMP              /**/
#define RV_SCTP_CANT_STR_ASSOC  SCTP_CANT_STR_ASSOC             /**/
#define RvSctpSacState          sn_assoc_change.sac_state       /**/
                                                                /**/
/* sctp_assoc_change: sac_assoc_id */                           /**/
#define RvSctpSacAssocId        sn_assoc_change.sac_assoc_id    /**/
                                                                /**/
/* sctp_paddr_change: spc_aaddr */                              /**/
#define RvSctpSpcAaddr          sn_paddr_change.spc_aaddr       /**/
                                                                /**/
/* sctp_paddr_change: spc_state */                              /**/
#define RV_SCTP_ADR_AVAILABLE   SCTP_ADDR_AVAILABLE             /**/
#define RV_SCTP_ADR_UNREACHABLE SCTP_ADDR_UNREACHABLE           /**/
#define RV_SCTP_ADR_REMOVED     SCTP_ADDR_REMOVED               /**/
#define RV_SCTP_ADD_ADDED       SCTP_ADDR_ADDED                 /**/
#define RV_SCTP_ADR_MADE_PRIM   SCTP_ADDR_MADE_PRIM             /**/
#define RvSctpSpcState          sn_paddr_change.spc_state       /**/
                                                                /**/
/* sctp_paddr_change: sac_assoc_id */                           /**/
#define RvSctpSpcAssocId        sn_paddr_change.spc_assoc_id    /**/
/*----------------------------------------------------------------*/


/* values for RvSctpMessageInfo.flags */
#if RV_SCTP_HAS_DRAFT11_NAMES
#    define RV_SCTP_MSG_UNORDERED   SCTP_UNORDERED
#    define RV_SCTP_MSG_ADDR_OVER   SCTP_ADDR_OVER
#    define RV_SCTP_MSG_ABORT       SCTP_ABORT
#    define RV_SCTP_MSG_EOF         SCTP_EOF
#else
#    define RV_SCTP_MSG_UNORDERED   MSG_UNORDERED
#    define RV_SCTP_MSG_ADDR_OVER   MSG_ADDR_OVER
#    define RV_SCTP_MSG_ABORT       MSG_ABORT
#    define RV_SCTP_MSG_EOF         MSG_EOF
#endif


typedef enum
{
    RvSctpBindAdd = SCTP_BINDX_ADD_ADDR,
    RvSctpBindRemove = SCTP_BINDX_REM_ADDR,
    RvSctpBind
} RvSctpBindOp;


typedef enum
{
    RvSctpAssocLocal,
    RvSctpAssocPeer
} RvSctpAssocSide;


typedef enum
{
    RvSctpOptionGet,
    RvSctpOptionSet
} RvSctpOptionOper;


typedef enum
{
    RvSctpMsgNormal,
    RvSctpMsgNotification
} RvSctpMsgType;


typedef struct {
    RvUint8*        buffer;
    RvSize_t        bufferLength;
    RvAddress       remoteAddress;
    RvSctpMsgType   messageType;    /* for receive only */
    RvUint16        streamNum;
    RvUint16        flags;
} RvSctpMessageInfo;


/********************************************************************************************
 * RvSocketSctpBind
 * Bind a SCTP socket to a series of local IP/port addresses.
 * The port number must be the same to all addresses.
 * This function can be used also to remove some addresses from the socket list
 * INPUT   : sock       - Socket to bind
 *           addresses  - List of addresses to bind socket to
 *           nAddresses - Number of addresses in the list
 *           operation  - Must be either RvSctpBindAdd or RvSctpBindRemove
 *           logMgr     - log manager instance
 * RETURN  : RV_OK on success, other on failure.
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSctpBind(
    IN  RvSocket*           sock,
    IN  RvAddress*          addresses,
    IN  RvSize_t            nAddresses,
    IN  RvSctpBindOp        operation,
    IN  RvLogMgr*           logMgr);


RVCOREAPI
RvStatus RVCALLCONV RvSocketSctpAccept(
    IN  RvSocket*           sock,
    IN  RvLogMgr*           logMgr,
    OUT RvSocket*           newSocket,
    OUT RvAddress*          remoteAddress);


/********************************************************************************************
 * RvSocketSctpSend
 * Send a buffer on a SCTP socket.
 * This function actually copies the given buffer (pointed to by the messageInfo param)
 * to the operating system's memory for later sending.
 * In blocking mode, this function will block until the buffer is sent to the remote
 * side or upon failure.
 * In non-blocking mode, this function will return immediately, indicating the exact
 * amount of bytes the operating system has processed and sent.
 * INPUT   : socket         - Socket to send the buffer on
 *           messageInfo    - Of type RvSctpMessageInfo indicating the buffer to send,
 *                            its length, the stream number to use and flags
 *           logMgr         - log manager instance
 * OUTPUT  : bytesSent      - Number of bytes the have been sent
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSctpSend(
    IN  RvSocket*           sock,
    IN  RvSctpMessageInfo*  messageInfo,
    IN  RvLogMgr*           logMgr,
    OUT RvSize_t*           bytesSent);


/********************************************************************************************
 * RvSocketSctpReceive
 * Receive a buffer from a SCTP socket.
 * In blocking mode, this function will block until a buffer is received on the
 * socket.
 * In non-blocking mode, this function returns immediately, even if there is nothing
 * to be received on this socket at the moment. This function is usually called after
 * RvSelectRead event is received in the select module on this socket, indicating that
 * there is information to receive on this socket.
 * INPUT   : socket         - Socket to receive the buffer from
 *           messageInfo    - Of type RvSctpMessageInfo indicating the buffer to receive
 *                            the data and the buffer length.
 *                            Stream and flags will be filled in by the function
 *           logMgr         - log manager instance
 * OUTPUT  : bytesReceived  - Number of bytes that were actually received
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSctpReceive(
    IN  RvSocket*           sock,
    IN  RvSctpMessageInfo*  messageInfo,
    IN  RvLogMgr*           logMgr,
    OUT RvSize_t*           bytesReceived);


/**********************************************************************************
 * RvSocketSctpSetOpt
 * Change the options associated with a SCTP socket.
 * INPUT   : socket     - Socket to change its options
 *           optName    - Option id
 *           optVal     - Pointer to the option properties
 *           optLen     - Length of the data pointed to by optVal
 *           logMgr     - log manager instance
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSctpSockOpt(
    IN  RvSocket*           sock,
    IN  RvSctpOptionOper    operation,
    IN  RvInt               optName,
    IN  void*               optVal,
    IN  RvSize_t            optLen,
    IN  RvLogMgr*           logMgr);


/**********************************************************************************
 * RvSocketSctpGetAddresses
 * Get all the locally bound IP addresses on a SCTP socket or all the peer addresses
 * in an association represented by a socket.
 * INPUT   : socket     - Socket to get its associated addresses
 *           assocSide  - Which side of the connection is required:
 *                        RvSctpAssocLocal or RvSctpAssocPeer
 *           addresses  - Array of addresses to get the results
 *           logMgr     - log manager instance
 * INOUT   : nAddresses - Pointer to variable indicating the number of addresses in the array
 *                        Will be used to report the actual number of addresses
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSocketSctpGetAddresses(
    IN    RvSocket*          sock,
    IN    RvSctpAssocSide    assocSide,
    IN    RvAddress*         addresses,
    INOUT RvSize_t*          nAddresses,
    IN    RvLogMgr*          logMgr);

#endif /* RV_NET_TYPE & RV_NET_SCTP */


#endif /* (RV_NET_TYPE != RV_NET_NONE) */

#if defined(__cplusplus)
}
#endif

#endif /* RV_SOCKET_H */
