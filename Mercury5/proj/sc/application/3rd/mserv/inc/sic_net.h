/****************************************************************************/
/*  File    : sic.net.h                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : MIC network management                                        */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
* --------------------------------------------------------------------------
*  Date     | Author | Revision       | Description
* ----------+--------+----------------+-------------------------------------
*/

#ifndef __SIC_NET_H__
#define __SIC_NET_H__

#ifdef __MSERVICES__

#include "VmlAdaptor.h"
#include "ms_socket.h"     /// handle to socket
#include "ms_socket_fsm.h" /// error code for socket

/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*                            CONSTANTS                                     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*** Typedef enums ***/

#define MSERV_MIC_NET_MAX_SESSION            7
//#define MSERV_MIC_NET_MAX_SESSION            VM_VML_MSL_MAX_SOCKET_CTXT
///* maximum session; should be equal to max socket simultaneously opened */
#define MSERV_MIC_NET_INIT_ALL_SESSION       0xFF  /* initialize all net session contexts */
#define MSERV_MIC_NET_NO_SESSION_AVAILABLE   0xFF  /* no net session context available */
#define MSERV_MIC_NET_PROXYADDRESS_LEN       24
#define MSERV_MIC_NET_DOMAIN_NAME_LEN        0xFF
#define MSERV_MIC_NET_DOMAIN_NAME_QUEUE      MSERV_MIC_NET_MAX_SESSION
#define MSERV_MIC_NET_DOMAIN_NAME_TI_FIRST   0x01
#define MSERV_MIC_NET_DOMAIN_NAME_TI_MAX     0x20
#define MSERV_MIC_NET_NO_INDEX_SESSION       0xFF
#define MSERV_MIC_NET_DNS_QUERY_TI           0x00
#define MSERV_MIC_NET_FSCI_START             (MSERV_MIC_NET_DNS_QUERY_TI+1)
/* FreeSessionContextIndex */
#define MSERV_MIC_NET_DATA_LINK_RETRY_MAX    0x00
#define MSERV_MIC_NET_SOCKET_RETRY_MAX       (5)
#define MSERV_DATA_LINK_TI                   MSERV_MIC_NET_DNS_QUERY_TI

#define MSERV_MIC_NET_SOCKET_TYPE_UDP        (1)
#define MSERV_MIC_NET_SOCKET_TYPE_TCP        (2)
#define MSERV_MIC_NET_SOCKET_TYPE_UDP_SERVER (3)
#define MSERV_MIC_NET_SOCKET_TYPE_TCP_SERVER (4)

/*** return codes ***/
typedef enum
{
	MSERV_MIC_NET_OK,
	MSERV_MIC_NET_SWITCH_TO_CSD,
	MSERV_MIC_NET_LAST_NAPDEF
}Mserv_Mic_Net_ReturnCode_t;

typedef enum
{
    MSERV_MIC_NET_GPRS,
	MSERV_MIC_NET_WIFI,
}Mserv_Mic_Net_DataLinkType_t;

typedef void* Mserv_Mic_Net_DataBearer_t;
typedef void* Mserv_Mic_Net_DataTypeCall_t;

/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*                            STRUCTURES                                    */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

/* Structure of client information who use socket service (added by Mark.Yang) */
typedef struct
{
	u16 userMbx;
	void *pUser;
}Mserv_Mic_Net_UserInfo_t;

/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*                            FUNCTIONS                                     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*  Function  : Mserv_Mic_NetInitAllSessions()                              */
/*--------------------------------------------------------------------------*/
/*  Scope     : Initialize all the session contexts                         */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Index             | X |   |   | index of the net session context        */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetInit(void);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslCreateDataLinkRsp()                      */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process messages from MSL layer                             */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslCreateDataLinkRsp(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslCreateSocketRsp()                        */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

SocketErrorCode_e Mserv_Mic_NetRecMslCreateSocketRsp(const void *PtrMsgRec);
SocketErrorCode_e Mserv_Mic_NetRecMslCreateSocketErrRsp(const void *PtrMsgRec, MS_SocketHdl_t *phSocket);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslReceiveInd()                             */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslReceiveInd(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslSendReadyInd()                           */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslSendReadyInd(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslStatusInd()                              */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslStatusInd(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslCloseDataLinkRsp()                         */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslCloseDataLinkRsp(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslCloseSocketRsp()                         */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslCloseSocketRsp(const void *PtrMsgRec);
void Mserv_Mic_NetRecMslCloseAllDataLinksRsp(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecTimerCheckSocketExpired                     */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process internal message MS_MIC_TIMER_CHECK_SOCKET from MSERV*/
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecTimerCheckSocketExpired(void);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslDnsQueryRsp()                            */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslDnsQueryRsp(const void *PtrMsgRec);
void Mserv_Mic_NetRecMslPingQueryRsp(const void *PtrMsgRec);
void Mserv_Mic_NetRecMslStatisticQueryRsp(const void *PtrMsgRec);
void Mserv_Mic_NetRecMslStatisticResetAllRsp(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetProcessComEvt()                                */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process messages from MSL layer                             */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetProcessComEvt(const void * PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetCloseAllSessions()                             */
/*--------------------------------------------------------------------------*/
/*  Scope     : Close all the socket and then the data link                 */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetCloseAllSessions(void);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetCloseDatalink()                                */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send data link closing message to MSL                       */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

/*void Mserv_Mic_NetCloseDatalink(void);*/

/****************************************************************************/
/*  Function  : Mserv_Mic_NetCreateSocket()                                 */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send socket creation message to MSL                         */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetCreateSocket(MS_SocketHdl_t hSocket);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetCloseSocket()                                  */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send socket closing message to MSL                          */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetCloseSocket(MS_SocketHdl_t hSocket);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSendData()                                     */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send data to MSL                                            */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  socket_id         | X |   |   | Socket identifier                       */
/*--------------------+---+---+---+-----------------------------------------*/
/*  data              | X |   |   | Pointer to the data to send             */
/*--------------------+---+---+---+-----------------------------------------*/
/*  data_len          | X |   |   | length of data to send                  */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSendData(MS_SocketHdl_t hSocket, u8 *data, u16 data_len);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecvReady()                                    */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send RecvReadyReq to MSL                                    */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  socket_id         | X |   |   | Socket identifier                       */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecvReady(MS_SocketHdl_t hSocket);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetDnsQuery()                                     */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send a DNS query to MSL                                     */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetDnsQuery(u8 DnsTi, u16 DomainLen, u8 *Domain, void *pUserData);
void Mserv_Mic_NetPing(void *pPingData);
void Mserv_Mic_NetStatisticQuery(void *pStatisticQueryData);
void Mserv_Mic_NetStatisticReset(void *pStatisticResetData);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslCreateDataLinkReqEx()                 */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send create data link request to MSL                        */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* ClientId           | X |   |   | Mservices Client Id                     */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Ti                | X |   |   | Transaction identifier                  */
/*--------------------+---+---+---+-----------------------------------------*/
/*  DataLinkType      | X |   |   | Used bearer                             */
/*--------------------+---+---+---+-----------------------------------------*/
/*  DnsServer         | X |   |   | DNS server                              */
/*--------------------+---+---+---+-----------------------------------------*/
/*  DnsServer2        | X |   |   | DNS server2                             */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Ip                | X |   |   | Ip Address                              */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Subnet            | X |   |   | Subnet                                  */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Gateway           | X |   |   | Gateway                                 */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Apn               | X |   |   | Apn                                     */
/*--------------------+---+---+---+-----------------------------------------*/
/*  uVneApId          | X |   |   | Vendor Ap Id                            */
/*--------------------+---+---+---+-----------------------------------------*/
/*  pvVenCb           | X |   |   | Vendor's callback                       */
/*--------------------+---+---+---+-----------------------------------------*/
/*  pvVenUserData     | X |   |   | Vendor's user data                      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void Mserv_Mic_NetSndMmtMslCreateDataLinkReqEx
(
  u8 ClientId, 
  u8 Ti,
  u8 ModuleId,
  Mserv_Mic_Net_DataLinkType_t eDataLinkType,
  u8 *uUserName,
  u8 *uPassWd,
  u8 *uDns1Server,
  u8 *uDns2Server,
  u8 *uIp,
  u8 *uIpSubnet,
  u8 *uIpGateway,
  ascii *uApn, 
  u32 uResMgrApId,
  void *pvVenCb,
  void *pvVenUserData
);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslCreateDataLinkReq()                   */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send create data link request to MSL                        */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* ClientId           | X |   |   |  Mservices Client Id                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Ti                | X |   |   | Transaction identifier                  */
/*--------------------+---+---+---+-----------------------------------------*/
/*  number            | X |   |   | Gateway call number                     */
/*--------------------+---+---+---+-----------------------------------------*/
/*  DataBearer        | X |   |   | Used bearer                             */
/*--------------------+---+---+---+-----------------------------------------*/
/*  name              | X |   |   | Connecting name identifier              */
/*--------------------+---+---+---+-----------------------------------------*/
/*  passwd            | X |   |   | Connecting password identifier          */
/*--------------------+---+---+---+-----------------------------------------*/
/*  DnsServer         | X |   |   | DNS server                              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSndMmtMslCreateDataLinkReq
(
 u8 ClientId, 
 u8 Ti, 
 u8 ModuleId,
 ascii *number,
 Mserv_Mic_Net_DataBearer_t *psDataBearer,
 Mserv_Mic_Net_DataTypeCall_t *psDataTypeCall,
 ascii *name, 
 ascii *passwd, 
 u8 *DnsServer,
 ascii *apn, 
 u8 *MsIpAddress,
 Mserv_Mic_Net_DataLinkType_t eDataLinkType,
 u32 uVenApId,
 void *pvVenCb,
 void *pvVenUserData,
 bool bExtApi
);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslCloseDataLinkReq()                    */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send close data link request to MSL                         */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  ClientId          | X |   |   |  Mservices Client Id                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Ti                | X |   |   | Transaction identifier                  */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSndMmtMslCloseDataLinkReq(u8 Ti, u32 uResMgrApId, void *pvhConn, void *pvVenCb, void *pvVenUserData, u32 uVersion);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslCreateSocketReq()                     */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send create socket request to MSL                           */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  ClientId          | X |   |   |  Mservices Client Id                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Ti                | X |   |   | Transaction identifier                  */
/*--------------------+---+---+---+-----------------------------------------*/
/*  SocketType        | X |   |   | Used socket type                        */
/*--------------------+---+---+---+-----------------------------------------*/
/*  LocalPort         | X |   |   | Used local port                         */
/*--------------------+---+---+---+-----------------------------------------*/
/*  ServerPort        | X |   |   | Used server port                        */
/*--------------------+---+---+---+-----------------------------------------*/
/*  ServerAddress     | X |   |   | Used server IP address                  */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSndMmtMslCreateSocketReq
(
    MS_SocketHdl_t hSocket,
    u8 uMservMicNetSocketType
);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslCloseSocketReq()                      */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send close socket request to MSL                            */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* ClientId           | X |   |   |  Mservices Client Id                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Ti                | X |   |   | Transaction identifier                  */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSndMmtMslCloseSocketReq(MS_SocketHdl_t hSocket);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslSendReq()                             */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send data request to MSL                                    */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* ClientId           | X |   |   | Mservices Client Id                     */
/*--------------------+---+---+---+-----------------------------------------*/
/* SocketId           | X |   |   | Socket identifier                       */
/*--------------------+---+---+---+-----------------------------------------*/
/* ServerPort         | X |   |   | Used server port                        */
/*--------------------+---+---+---+-----------------------------------------*/
/* ServerAddress      | X |   |   | Used server IP address                  */
/*--------------------+---+---+---+-----------------------------------------*/
/* DataLen            | X |   |   | Length of data to send                  */
/*--------------------+---+---+---+-----------------------------------------*/
/* Data               | X |   |   | Data pointer                            */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSndMmtMslSendReq(MS_SocketHdl_t hSocket, u16 DataLen, u8 *Data);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslRecvReadyReq()                        */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send recvReady request to MSL                               */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* ClientId           | X |   |   | Mservices Client Id                     */
/*--------------------+---+---+---+-----------------------------------------*/
/* SocketId           | X |   |   | Socket identifier                       */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSndMmtMslRecvReadyReq(MS_SocketHdl_t hSocket);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetSndMmtMslDnsQueryReq()                         */
/*--------------------------------------------------------------------------*/
/*  Scope     : Send MslDnsQueryReq request to MSL                          */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* ClientId           | X |   |   | Mservices Client Id                     */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    | X |   |   |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetSndMmtMslDnsQueryReq(u8 DnsTi, u16 DomainLen, u8 *Domain, void* pUserData);
void Mserv_Mic_NetSndMmtMslPingReq(void *pPingData);
void Mserv_Mic_NetSndMmtMslStatisticQueryReq(void *pStatisticQueryData);
void Mserv_Mic_NetSndMmtMslStatisticResetReq(void *pStatisticResetData);

/****************************************************************************/
/*  Function : Mserv_Mic_ConvertIPAscii2Hex                                 */
/*--------------------------------------------------------------------------*/
/*  Scope    :  Convert an IP V4 address from ascii to an hexa value        */
/*              "160.92.122.122" ->  a0 5a 7c 7c                            */
/*                                                                          */
/*  Return   :  table of hexa value                                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  AddressAscii      | x |   |   |  String format "160.92.122.122"         */
/*--------------------+---+---+---+-----------------------------------------*/
/*  AddressHexa       |   | x |   | [0]= a0 / [1]=5a / [2]=7c / [3]=7c      */
/****************************************************************************/

void Mserv_Mic_ConvertIPAscii2Hex(const char *AddressAscii, u8 *AddressHexa);

/****************************************************************************/
/*  Function : Mserv_Mic_NetConvertHexToIPAscii                             */
/*--------------------------------------------------------------------------*/
/*  Scope    :  Convert an IP V4 address from an hexa value to ascii        */
/*              a0 5a 7c 7c ->  "160.92.122.122"                            */
/*                                                                          */
/*  Return   :  void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  HexaAddress       | x |   |   | [0]= a0 / [1]=5a / [2]=7c / [3]=7c      */
/*--------------------+---+---+---+-----------------------------------------*/
/*  AsciiAddress      |   | x |   |  String format "160.92.122.122"         */
/****************************************************************************/

void Mserv_Mic_NetConvertHexToIPAscii(u8 *HexaAddress, u8 *AsciiAddress);

/****************************************************************************/
/*  Function  : iMserv_Mic_SndStartTestReq()                                */
/*--------------------------------------------------------------------------*/
/*  Scope     : send test request message to MSERV                          */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/ 

void iMserv_Mic_SndStartTestReq(void);

/// sic_net.c

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslSetSocketOptRsp()                        */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslSetSocketOptRsp(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslGetSocketOptRsp()                        */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslGetSocketOptRsp(const void *PtrMsgRec);

/****************************************************************************/
/*  Function  : Mserv_Mic_NetRecMslShutdownSocketRsp()                      */
/*--------------------------------------------------------------------------*/
/*  Scope     : Process message from MSL layer                              */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*   PtrMsgRec        | X |   |   | message pointer                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void Mserv_Mic_NetRecMslShutdownSocketRsp(const void *PtrMsgRec);

#endif /* __MSERVICES__ */
#endif /* __SIC_NET_H__ */
