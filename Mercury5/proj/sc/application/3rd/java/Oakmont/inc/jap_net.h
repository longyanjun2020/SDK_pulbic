#ifndef __JAP_NET_DEFINE_H__
#define __JAP_NET_DEFINE_H__
/**
*
* @file    jap_net.c
* @brief   This file .
*
* @author  Kris.Wang
* @version $Id: jap_net.h 33887 2009-06-19 07:13:32Z kris.wang $
*
*/


/* Aplix header - begin */
#include "Kjava_sys_sock.h"
/* Aplix header - end */

/* Mstar header - begin */
#include "ven_socket.h"
/* Mstar header - end */

// Max number of UDP socket we can maintain at the same time
#define JAVA_MAX_UDP_SOCKET_NUM     1

// Max number of TCP socket we can maintain at the same time
#define JAVA_MAX_TCP_SOCKET_NUM		5 //PR133960   // PR66517

// Max size for packet storage (TcpDataStore())
#define JAVA_MAX_HEAP_SIZE_FOR_PACKET_STORE		300*1024 //PR0135316



// Max datagram size
#define JAVA_MAX_DATAGRAM_LENGTH    5120

#define SKT_bzero(addr,len)   ven_std_memset((addr),0,(len))

typedef enum
{
	JAP_LINK_NOT_EXIST = 0,
	JAP_LINK_ESTABLISHING,
	JAP_LINK_ESTABLISHED,

	JAP_TOTAL_LINK_STATUS

} jap_LinkStatusE;

typedef enum 
{
    JAP_TCPSOCKET_NOTUSED = 0,
	JAP_TCPSOCKET_ISUSED,
	JAP_TCPSOCKET_NEEDFREE,

	JAP_TOTAL_TCPSOCKET
}Jap_TcpSocketUsedE;

typedef struct 
{
    bool         used;
    u8           *hostname;
    u8           *ipaddr;
    ven_socket_t ven_socket;

} Jap_UdpSocketS;

typedef struct
{
	u8   *bufferPtr;
    s32  bufflen;
	u8   *from_addr;
    s32  addrlen;

} Jap_UdpReadDataTableS;

typedef struct 
{
    Jap_TcpSocketUsedE         used;
    bool         peerClose;
    bool         bEndOfPackage;
    bool         ConnectWaitDataLink;
    u8           ti; // for ven_socket_gethostbyname_async
    int          remotePort;

    KJavaLocalInfo *localInfo_p;

    int          sendbyte;  // keep the send byte in kjava_sock_send, because our SDK callbacl will not return the acutal send byte

    u8           *hostname;
    u8           *ipaddr;
    ven_socket_t ven_socket;

    KJavaNetworkCallbackProc    eventHandler;

} Jap_TcpSocketS;

typedef struct
{
    s32  bufflen;
	u8   *bufferPtr;

} Jap_TcpReadDataTableS;

typedef struct
{
	void          *next;
	unsigned int  len;
	unsigned int  curPos;
	unsigned char data;

} Jap_TcpReceiveDataEntryS;

/**
 *  jap_CheckLinkStatus
 *
 *  @brief  Get current Java network link status
 *
 *  @retval Java network link status
 *          
 */
int jap_CheckLinkStatus( void );
void jap_SetLinkStatus( jap_LinkStatusE eLinkStatus );

/**
 *  jap_MakeDataLink
 *
 *  @brief  Establish Java network link
 *
 *  @retval 1 if success
 *          0 if failed
 */
int jap_MakeDataLink( bool ifAsynch );

/**
 *  jap_RelDataLink
 *
 *  @brief  Release Java network link
 *
 *  @retval 1 if success
 *          0 if failed
 */
int jap_RelDataLink( void );

/**
 *  jap_ota_notify
 *
 *  @brief  Send ota result to ota server
 *
 *  @retval 1 if success
 *          0 if failed
 */
int jap_ota_notify(void);

/**
 *  jap_ota_download_file
 *
 *  @brief  Use VM network interface to download a file from internet
 *
 *  @param  u16Http         [in] the file's URL
 *  @param  u16FilePath     [in] the path to save the file
 *
 *  @retval 1 if success
 *          0 if failed
 */
int jap_ota_download_file(u16* u16Http, u16* u16FilePath);

/**
 *  jap_ota_abort
 *
 *  @brief  cancel OTA process
 *
 *  @retval 
 *          
 */
void jap_ota_abort(void);

/**
 *  jap_ota_abort
 *
 *  @brief  check if OTA is processing
 *
 *  @retval 
 *          
 */
bool jap_ota_isRunning(void);
/**
 *  jap_SetDefaultSimID
 *
 *  @brief  Set NetSimID if needed
 *
 *  @retval 
 *          
 */
void jap_SetDefaultSimID( ven_common_sim_id_t tSimID );

#endif /* __JAP_NET_DEFINE_H__ */

