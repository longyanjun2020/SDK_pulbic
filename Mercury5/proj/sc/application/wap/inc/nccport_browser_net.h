
/**
 * @file
 * Net Porting Layer
 *
 * Basic support functions that are needed by networking.
 *
 * <!-- #interface list begin -->
 * \section nccport_browser_net Interface
 * - NCCPort_brwnet_socketClose()
 * - NCCPort_brwnet_recv()
 * - NCCPort_brwnet_send()
 * - NCCPort_brwnet_tcpConnect()
 * - NCCPort_brwnet_getHostByName()
 * - NCCPort_brwnet_clientSocket()
 * - NCCPort_brwnet_setNoBlock()
 * - NCCPort_brwnet_error()
 * - NCCPort_brwnet_socketStartup()
 * - NCCPort_brwnet_socketCleanup()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_BROWSER_NET_H__
#define __NCCPORT_BROWSER_NET_H__

#include "ven_os.h"
#include "ven_socket.h"

#define BRWNET_MAX_QUERYIP_NUM 10

#define FNDB_CPL_NET_OK         0
#define FNDB_CPL_NET_ERROR      -1
#define FNDB_CPL_NET_PENDING    -2
#define FNDB_CPL_NET_NOBUFF     -3
#define FNDB_CPL_TLS_AUTH_SERVER_FAILED	-4
struct Node;
typedef struct Node *PNode;

struct Node//struct node
{
    void* info;
    PNode link;
};

typedef struct
{
    int32_t sendLen;
    int32_t recvLen;
    int32_t socketId;
    int32_t appId;
    ven_socket_t *socket;
    uint8_t *recvBuf;
    void *next;
    uint8_t status;
    uint8_t status_recv;
    uint8_t needWait;
    uint8_t asyncResult;
    uint8_t suspendFlag;
} Nccport_brwnet_sockInfo;

typedef struct
{
    int8_t *name;
    struct hostent *hostent;
    uint32_t ip;
    u8 ti;
    uint8_t flag;
} Nccport_brwnet_queryInfo;

/**
 * Close socket
 * \param s Socket NO.
 * \return 0: success. SOCKET_ERROR: failed.
 */
int32_t NCCPort_brwnet_socketClose (int32_t s);

/**
 * Receive data.
 * \param s Socket NO.
 * \param buf Storage of received data.
 * \param len Length of received data.
 * \param flags Other feature, usually set to 0.
 * \return
 *   FNDB_NCCPort_NET_NOBUFF:No storage for received data.
 *   FNDB_NCCPort_NET_PENDING:Waiting.
 *   FNDB_NCCPort_NET_ERROR:Received failed.
 *   >0£ºReceived success and return the length of data received.
 */
int32_t NCCPort_brwnet_recv (int32_t s, int8_t *buf, int32_t len, int32_t flags);

/**
 * Send data.
* \param s Socket number.
* \param buf Point to data of send.
* \param len Length of send data.
* \param flags Other feature, usually set to 0.
* \return success: length of send data, failed:FNDB_NCCPort_NET_ERROR
*/
int32_t NCCPort_brwnet_send(int32_t s,
        const int8_t *buf,
        int32_t len,
        int32_t flags);

/**
 * Connect sever.
 * \param s Socket NO.
 * \param ipNumber IP address
 * \param port  IP port
 * \return  success:FNDB_NCCPort_NET_OK;        failed:FNDB_NCCPort_NET_ERROR;
 */
int32_t NCCPort_brwnet_tcpConnect(
                           int32_t s,
                           uint32_t ipNumber,
                           uint16_t port
                           );

/**
 * Analyse DNS.
 * \param name Host IP or DNS.
 * \return
 *  >0: success
 *  failed: FNDB_NCCPort_NET_ERROR
 *  waiting: FNDB_NCCPort_NET_PENDING
 */
int32_t NCCPort_brwnet_getHostByName(const int8_t *name, uint32_t *addr);
int32_t NCCPort_brwnet_getHostByName_ex(const int8_t *name, uint32_t *addr, int32_t appId);
int32_t NCCPort_brwnet_deleteTimeoutHostName(const int8_t *name);

/**
 * Create socket.
 * \param
 * \return success:>0       failed: FNDB_NCCPort_NET_ERROR
 */
int32_t NCCPort_brwnet_clientSocket(void);
int32_t NCCPort_brwnet_clientSocket_ex(int32_t appId);

/**
 * Set NOT  block.
 * \param s SOCKET NO.
 * \return
 *  success FNDB_NCCPort_NET_OK
 *  failed:FNDB_NCCPort_NET_ERROR
 */
int32_t NCCPort_brwnet_setNoBlock(int32_t s);

/**
 * Get error type of socket.
 * \param s Socket number
 * \return Error type, process when connect, send, receive
 */
int32_t NCCPort_brwnet_error(int32_t s);

/**
 * Initial socket.
 * \return FNDB_NCCPort_NET_ERROR:failed;FNDB_NCCPort_NET_OK:success
 */
int32_t NCCPort_brwnet_socketStartup(void);

/**
 * Clean up socket.
 * \return FNDB_NCCPort_NET_OK
 */
int32_t NCCPort_brwnet_socketCleanup(void);

#endif /* __NCCPORT_BROWSER_NET_H__ */
