#ifndef __VML_ADAPTOR_H__
#define __VML_ADAPTOR_H__

#ifdef  __3G_RIL_MMI__
#define __3G_PLATFORM__
#else
#define __2G_PLATFORM__
#endif /// __3G_PLATFORM__

#ifdef __SDK_API__
#define __VENDOR_API_SUPPORT__
#endif /// __SDK_API__

/// if system defines __MDL_EXT__, it stands for system having a vml3 task.
/// if system defines __WLAN_IP_SUPPORT__, it stands for system allowing user to use internet via Wi-Fi.
#if defined(__MDL_EXT__) && defined(__WLAN_IP_SUPPORT__)
#define __VML_WIFI_COMMEDIA__
#endif /// __MDL_EXT__ && __WLAN_IP_SUPPORT__

#if defined(__2G_PLATFORM__) /// used for B2/B3 Vml Layer
/// message structure
#define ProtocolResult_t                                             vm_VmlMslResult_t
#define ProtocolDataLinkType_t                                       vm_VmlMslDataLinkType_t
#define ProtocolStatusIndMsg_t                                       vm_VmlMslStatusInd_t
#define ProtocolCreateDatalinkReqMsg_t                               vm_VmlMslCreateDataLinkReq_t
#define ProtocolCreateDatalinkRspMsg_t                               vm_VmlMslCreateDataLinkRsp_t
#define ProtocolOpenSocketReqMsg_t                                   vm_VmlMslCreateSocketReq_t
#define ProtocolOpenSocketRspMsg_t                                   vm_VmlMslCreateSocketRsp_t
#define ProtocolCloseSocketReqMsg_t                                  vm_VmlMslCloseSocketReq_t                 
#define ProtocolCloseSocketRspMsg_t                                  vm_VmlMslCloseSocketRsp_t
#define ProtocolSendReq_t                                            vm_VmlMslSendReq_t
#define ProtocolSendReadyInd_t                                       vm_VmlMslSendReadyInd_t
#define ProtocolReceiveInd_t                                         vm_VmlMslReceiveInd_t
#define ProtocolReceiveReadyReq_t                                    vm_VmlMslReceiveReadyReq_t
#define ProtocolDestroyDatalinkReqMsg_t                              vm_VmlMslCloseDataLinkReq_t
#define ProtocolDestroyDatalinkRspMsg_t                              vm_VmlMslCloseDataLinkRsp_t
#define ProtocolDnsQueryReqMsg_t                                     vm_VmlMslDnsQueryReq_t          
#define ProtocolDnsQueryRspMsg_t                                     vm_VmlMslDnsQueryRsp_t
#define ProtocolSetSockOptReqMsg_t                                   vm_VmlMslSetSocketOptReq_t
#define ProtocolSetSockOptRspMsg_t                                   vm_VmlMslSetSocketOptRsp_t
#define ProtocolGetSockOptReqMsg_t                                   vm_VmlMslGetSocketOptReq_t
#define ProtocolGetSockOptRspMsg_t                                   vm_VmlMslGetSocketOptRsp_t
#define ProtocolShutdownSockReqMsg_t                                 vm_VmlMslShutdownSocketReq_t
#define ProtocolShutdownSockRspMsg_t                                 vm_VmlMslShutdownSocketRsp_t
#define ProtocolPingReqMsg_t                                         vm_VmlMslPingReq_t
#define ProtocolPingRspMsg_t                                         vm_VmlMslPingRsp_t
#define ProtocolSocketOptLevelType_t                                 vm_VmlMslSocketOptLevelType_t
#define ProtocolSocketOptNameType_t                                  vm_VmlMslSocketOptNameType_t
/// message getter/setter
#define ProtocolGetFieldResult(pMsg)                                 (pMsg->Result)
#define ProtocolGetFieldMsIpAddress(pMsg)                            (pMsg->MsIpAddress)
#define ProtocolGetFieldIpAddress(pMsg)                              (pMsg->LocalIpAddr)
#define ProtocolGetFieldSocketId(pMsg)                               (pMsg->SocketId)
#define ProtocolGetFieldLocalPort(pMsg)                              (pMsg->ClientPort)
#define ProtocolGetFieldGateWay(pMsg)                                (pMsg->GatewayAddress)
#define ProtocolGetFieldSubnetMask(pMsg)                             (pMsg->MsIpSubMask)
#define ProtocolGetFieldTiForOpenSocketRsp(pMsg)                     (pMsg->Ti)
#define ProtocolGetFieldServerAddressForOpenSocketReq(pMsg)          (pMsg->ServerAddress)
#define ProtocolGetFieldResultForOpenSocketRsp(pMsg)                 (pMsg->Result)
#define ProtocolGetFieldResultForCloseSocketRsp(pMsg)                (pMsg->Result)
#define ProtocolGetFieldServerAddressForSendReq(pMsg)                (pMsg->ServerAddress)
#define ProtocolGetFieldDataBufForSendReq(pMsg)                      (pMsg->Data)
#define ProtocolGetFieldDataBufForReceiveInd(pMsg)                   (pMsg->Data)
#define ProtocolGetFieldDataLenForReceiveInd(pMsg)                   (pMsg->DataLen)
#define ProtocolGetFieldIpAddressForDnsQueryReq(pMsg)                (pMsg->IPAddress)
#define ProtocolGetFieldIpAddressForDnsQueryRsp(pMsg)                (pMsg->IPAddress)
#define ProtocolGetFieldDnsTiForDnsQueryRsp(pMsg)                    (pMsg->DnsTi)
#define ProtocolSetFieldSocketId(pMsg, uSo)                          (pMsg->SocketId = uSo)
#define ProtocolSetFieldResult(pMsg, uResult)                        (pMsg->Result = uResult)
#define ProtocolSetFieldIpAddress(pMsg, uIpAddr)                     (pMsg->LocalIpAddr = uIpAddr)
#define ProtocolSetFieldPort(pMsg, uPort)                            (pMsg->ClientPort = uPort)
#define ProtocolSetFieldPppAuth(pMsg, bAuth)                         /* b3 doesn't use it */
#define ProtocolSetFieldDataLenForSendReq(pMsg, uDataLen)            (pMsg->DataLen = uDataLen)
#define ProtocolSetFieldServerPortForSendReq(pMsg, uPort)            (pMsg->ServerPort = uPort)
#define ProtocolSetFieldTiForOpenSocketReq(pMsg, uTi)                (pMsg->Ti = uTi)
#define ProtocolSetFieldResultForOpenSocketRsp(pMsg, uResult)        (pMsg->Result = uResult)
#define ProtocolSetFieldResultForCloseSocketRsp(pMsg, uResult)       (pMsg->Result = uResult)
#define ProtocolSetFieldIpAddressForOpenSocketReq(pMsg, uIpAddr)     (pMsg->LocalIpAddr = uIpAddr)
#define ProtocolSetFieldServerPortForOpenSocketReq(pMsg, uPort)      (pMsg->ServerPort = uPort)
#define ProtocolSetFieldTiForOpenSocketRsp(pMsg, uTi)                (pMsg->Ti = uTi)
#define ProtocolSetFieldIpAddressForCloseDatalinkReq(pMsg, uIpAddr)  /* b3 doesn't use it */
#define ProtocolSetFieldSocketTypeForOpenSocketReq(pMsg, uType)      (pMsg->SocketType = uType)
#define ProtocolSetFieldLocalIpAddressForDnsQueryReq(pMsg, uIpAddr)  (pMsg->LocalIpAddr = uIpAddr)
#define ProtocolSetFieldDnsTiForDnsQueryReq(pMsg, uDnsTi)            (pMsg->DnsTi = uDnsTi)
#define ProtocolSetFieldDnsTiForDnsQueryRsp(pMsg, uDnsTi)            (pMsg->DnsTi = uDnsTi)
#define ProtocolSetFieldDnsLenForDnsQueryReq(pMsg, uDnsLen)          (pMsg->DomainLen = uDnsLen)
#define ProtocolSetFieldDataLenForReceiveInd(pMsg, uDataLen)         (pMsg->DataLen = uDataLen)
#define ProtocolSetFieldUserDataForSetSockOptReq(pMsg, uUserData)    (pMsg->UserData = uUserData)
#define ProtocolSetFieldClientIdForSetSockOptReq(pMsg, uClientId)    (pMsg->ClientId = uClientId)
#define ProtocolSetFieldUserDataForGetSockOptReq(pMsg, uUserData)    (pMsg->UserData = uUserData)
#define ProtocolSetFieldClientIdForGetSockOptReq(pMsg, uClientId)    (pMsg->ClientId = uClientId)
#define ProtocolSetFieldUserDataForShutdownReq(pMsg, uUserData)      (pMsg->UserData = uUserData)
#define ProtocolSetFieldClientIdForShutdownReq(pMsg, uClientId)      (pMsg->ClientId = uClientId)
/// message define
#define PROTOCOL_MSG_CREATE_DATALINK_REQ                             (VM_VML_MSG_MSL_CREATE_DATA_LINK_REQ)
#define PROTOCOL_MSG_CREATE_DATALINK_RSP                             (VM_VML_MSG_MSL_CREATE_DATA_LINK_RSP) 
#define PROTOCOL_MSG_DESTROY_DATALINK_REQ                            (VM_VML_MSG_MSL_CLOSE_DATA_LINK_REQ)
#define PROTOCOL_MSG_DESTROY_DATALINK_RSP                            (VM_VML_MSG_MSL_CLOSE_DATA_LINK_RSP) 
#define PROTOCOL_MSG_OPEN_SOCKET_REQ                                 (VM_VML_MSG_MSL_CREATE_SOCKET_REQ)
#define PROTOCOL_MSG_OPEN_SOCKET_RSP                                 (VM_VML_MSG_MSL_CREATE_SOCKET_RSP)
#define PROTOCOL_MSG_CLOSE_SOCKET_REQ                                (VM_VML_MSG_MSL_CLOSE_SOCKET_REQ)
#define PROTOCOL_MSG_CLOSE_SOCKET_RSP                                (VM_VML_MSG_MSL_CLOSE_SOCKET_RSP)
#define PROTOCOL_MSG_SEND_REQ                                        (VM_VML_MSG_MSL_SEND_REQ)
#define PROTOCOL_MSG_SEND_READY_IND                                  (VM_VML_MSG_MSL_SEND_READY_IND)
#define PROTOCOL_MSG_RECEIVE_IND                                     (VM_VML_MSG_MSL_RECEIVE_IND)
#define PROTOCOL_MSG_RECEIVE_READY_REQ                               (VM_VML_MSG_MSL_RECEIVE_READY_REQ)
#define PROTOCOL_MSG_DNS_QUERY_REQ                                   (VM_VML_MSG_MSL_DNS_QUERY_REQ)
#define PROTOCOL_MSG_DNS_QUERY_RSP                                   (VM_VML_MSG_MSL_DNS_QUERY_RSP)
#define PROTOCOL_MSG_STATUS_IND                                      (VM_VML_MSG_MSL_STATUS_IND)
#define PROTOCOL_MSG_DGRAM_CNF                                       (VM_IP_SWL_DGRAM_CNF)
#define PROTOCOL_MSG_DGRAM_IND                                       (VM_IP_SWL_DGRAM_IND)
#define PROTOCOL_MSG_SET_SOCKET_OPT_REQ                              (VM_VML_MSG_MSL_SET_SOCKET_OPT_REQ)
#define PROTOCOL_MSG_SET_SOCKET_OPT_RSP                              (VM_VML_MSG_MSL_SET_SOCKET_OPT_RSP)
#define PROTOCOL_MSG_GET_SOCKET_OPT_REQ                              (VM_VML_MSG_MSL_GET_SOCKET_OPT_REQ)
#define PROTOCOL_MSG_GET_SOCKET_OPT_RSP                              (VM_VML_MSG_MSL_GET_SOCKET_OPT_RSP)
#define PROTOCOL_MSG_SHUTDOWN_SOCKET_REQ                             (VM_VML_MSG_MSL_SHUTDOWN_SOCKET_REQ)
#define PROTOCOL_MSG_SHUTDOWN_SOCKET_RSP                             (VM_VML_MSG_MSL_SHUTDOWN_SOCKET_RSP)
#define PROTOCOL_MSG_PING_REQ                                        (VM_VML_MSG_MSL_PING_REQ)
#define PROTOCOL_MSG_PING_RSP                                        (VM_VML_MSG_MSL_PING_RSP)
/// result code
#define PROTOCOL_RESULT_CODE_OK                                      (VM_VML_MSL_RESULT_OK)
#define PROTOCOL_RESULT_CODE_FAIL                                    (VM_VML_MSL_RESULT_DEFAULT)
#define PROTOCOL_RESULT_CODE_NB_MAX_CTXT_REACHED                     (VM_VML_MSL_RESULT_NB_MAX_CTXT_REACHED)
#define PROTOCOL_RESULT_CODE_DATA_LINK_ALREADY_ACTIVATED             (VM_VML_MSL_RESULT_DATA_LINK_ALREADY_ACTIVATED)
#define PROTOCOL_RESULT_CODE_DATALINK_CLOSE_BY_PEER                  (VM_VML_MSL_RESULT_COM_CLOSE_BY_PEER)
#define PROTOCOL_RESULT_CODE_IP_ERROR                                (VM_VML_MSL_RESULT_IP_ERROR)
#define PROTOCOL_RESULT_CODE_NO_MORE_SOCKET                          (VM_VML_MSL_RESULT_NO_MORE_SOCKET)
#define PROTOCOL_RESULT_CODE_BAD_SOCKET_ID                           (VM_VML_MSL_RESULT_BAD_SOCKET_ID)
#define PROTOCOL_RESULT_CODE_TCP_SOCKET_CLOSE_BY_SERVER              (VM_VML_MSL_RESULT_CONTCP_CLOSE)
#define PROTOCOL_RESULT_CODE_DNS_DHCP_ERROR                          (VM_VML_MSL_RESULT_DNS_ERROR)
#define PROTOCOL_RESULT_CODE_GPRS_NOT_PRESENT                        (VM_VML_MSL_RESULT_GPRS_NOT_PRESENT)
#define PROTOCOL_RESULT_CODE_KO_WRONG_STATE                          (VM_VML_MSL_RESULT_KO_WRONG_STATE)
#define PROTOCOL_RESULT_CODE_KO_NO_IP_CONTEXT_FOUND                  (VM_VML_MSL_RESULT_KO_NO_MSL_CONTEXT_FOUND)
#define PROTOCOL_RESULT_CODE_SET_SOCKET_OPTION_ERROR                 (VM_VML_MSL_RESULT_SET_SOCKET_OPTION_ERROR)
#define PROTOCOL_RESULT_CODE_GET_SOCKET_OPTION_ERROR                 (VM_VML_MSL_RESULT_GET_SOCKET_OPTION_ERROR)
#define PROTOCOL_RESULT_CODE_SHUTDOWN_SOCKET_ERROR                   (VM_VML_MSL_RESULT_SHUTDOWN_SOCKET_ERROR)
#define PROTOCOL_RESULT_CODE_CONTCP_SYN_TIMEOUT                      (VM_VML_MSL_RESULT_CONTCP_SYN_TIMEOUT)
#define PROTOCOL_RESULT_CODE_CONTCP_AGAIN                            (VM_VML_MSL_RESULT_CONTCP_AGAIN)
#define PROTOCOL_RESULT_CODE_IP_ADDRESS_EXPIRED                      (VM_VML_MSL_RESULT_WIFI_LEASE_TIMEOUT)
#define PROTOCOL_RESULT_CODE_CONTCP_NO_BUFFER_ERROR                  (VM_VML_MSL_RESULT_CONTCP_NO_BUFFER_ERROR)
#define PROTOCOL_RESULT_CODE_DATA_LINK_KO                            (VM_VML_MSL_RESULT_DATA_LINK_KO)
#define PROTOCOL_RESULT_CODE_PING_OK                                 (VM_VML_MSL_RESULT_PING_OK)
/// others
#define PROTOCOL_DATALINK_TYPE_GPRS                                  (VM_VML_MSL_DATA_LINK_GPRS)
#define PROTOCOL_DATALINK_TYPE_WIFI                                  (VM_VML_MSL_DATA_LINK_WIFI)
#define PROTOCOL_SOCKET_TYPE_TCP                                     (VM_VML_MSL_TCP_CLIENT)
#define PROTOCOL_SOCKET_TYPE_UDP                                     (VM_VML_MSL_UDP_CLIENT)
#define PROTOCOL_SOCKET_TYPE_TCP_SERVER                              (VM_VML_MSL_TCP_SERVER)
#define PROTOCOL_SOCKET_TYPE_UDP_SERVER                              (VM_VML_MSL_UDP_SERVER)

/// define for cmdadatpor.h
#define CMDADAPTOR_IP_ADDRESS_MAX_LEN                                (VM_VML_MSL_IP_ADDRESS_MAX_SIZE)
#define CMDADAPTOR_APN_MAX_LEN                                       (VM_VML_MSL_AUTH_STRING_LEN)
#define CMDADAPTOR_USER_NAME_MAX_LEN                                 (VM_VML_MSL_AUTH_STRING_LEN)
#define CMDADAPTOR_PASSWD_MAX_LEN                                    (VM_VML_MSL_AUTH_STRING_LEN)
#define CMDADAPTOR_PHONENO_MAX_LEN                                   (VM_VML_CALLED_NB_SIZE_MAX)
/// define for sockmgrplatformdefines.h
#define SOCKMGR_IP_ADDRESS_MAX_LEN	                                 (VM_VML_MSL_IP_ADDRESS_MAX_SIZE)
#define SOCKMGR_APN_MAX_LEN			                                 (VM_VML_MSL_AUTH_STRING_LEN)
#define SOCKMGR_USER_NAME_MAX_LEN	                                 (VM_VML_MSL_AUTH_STRING_LEN)
#define SOCKMGR_PASSWD_MAX_LEN		                                 (VM_VML_MSL_AUTH_STRING_LEN)
#define SOCKMGR_AUTH_STRING_LEN                                      (VM_VML_MSL_AUTH_STRING_LEN)
/// define for sic_net.h
#define MicDataBearer_t                                              vm_VmlMslDataBearer_t
#define MicDataTypeCall_t                                            vm_VmlMslDataTypeCall_t
#define MicDataLinkType_t                                            vm_VmlMslDataLinkType_t
#define MicSocketType_t                                              vm_VmlMslSocketType_t
#define MIC_ASCII_IP_ADDRESS_LEN                                     (3*VM_VML_MSL_IP_ADDRESS_MAX_SIZE+4)
/// task related information
#define VML1_MAILBOX                                                 (VM_MBX_MDL1)
#define VML2_MAILBOX                                                 (VM_MBX_MDL2)
#ifdef __WLAN_IP_SUPPORT__ /// support Wi-Fi
#ifndef __MDL_EXT__
#define VM_MBX_MDL_EXT                                               (VM_MBX_MDL2+1)
#endif /// __MDL_EXT__
#define VML_WIFI_MAILBOX                                             (VM_MBX_MDL_EXT)
#endif /// __WLAN_IP_SUPPORT__
#define PROTOCOL_BASE                                                (VM_MDL_BASE)
#else /// used for G1 IP Layer
/// message structure
#define ProtocolResult_t                                             status_t
#define ProtocolDataLinkType_t                                       ip_DataTypeCall_t
#define ProtocolStatusIndMsg_t                                       ip_StatusInd_t
#define ProtocolCreateDatalinkReqMsg_t                               ip_CreateDataLinkReq_t
#define ProtocolCreateDatalinkRspMsg_t                               ip_CreateDataLinkCnf_t
#define ProtocolDestroyDatalinkReqMsg_t                              ip_CloseDataLinkReq_t 
#define ProtocolDestroyDatalinkRspMsg_t                              ip_CloseDataLinkCnf_t
#define ProtocolOpenSocketReqMsg_t                                   ip_SocketReq_t
#define ProtocolOpenSocketRspMsg_t                                   ip_SocketCnf_t
#define ProtocolCloseSocketReqMsg_t                                  ip_SocketClose_t                
#define ProtocolCloseSocketRspMsg_t                                  ip_CloseSocketCnf_t
#define ProtocolSendReq_t                                            ip_DgramReq_t
#define ProtocolSendReadyInd_t                                       ip_DgramCnf_t
#define ProtocolReceiveInd_t                                         ip_DgramInd_t
#define ProtocolReceiveReadyReq_t                                    ip_DgramRsp_t
#define ProtocolDnsQueryReqMsg_t                                     ip_DnsQueryReq_t                
#define ProtocolDnsQueryRspMsg_t                                     ip_DnsQueryCnf_t
#define ProtocolSetSockOptReqMsg_t                                   ip_swl_SocketSetOptReq_t
#define ProtocolSetSockOptRspMsg_t                                   ip_SocketSetOptCnf_t
#define ProtocolGetSockOptReqMsg_t                                   ip_swl_SocketGetOptReq_t
#define ProtocolGetSockOptRspMsg_t                                   ip_SocketGetOptCnf_t
#define ProtocolShutdownSockReqMsg_t                                 ip_swl_SocketShutdownReq_t
#define ProtocolShutdownSockRspMsg_t                                 ip_SocketShutdownCnf_t
#define ProtocolPingReqMsg_t                                         ip_WifiPingReq_t
#define ProtocolPingRspMsg_t                                         ip_WifiPingCnf_t
#define ProtocolSocketOptLevelType_t                                 u32
#define ProtocolSocketOptNameType_t                                  u32
/// message getter/setter
#define ProtocolGetFieldResult(pMsg)                                 (pMsg->status)
#define ProtocolGetFieldMsIpAddress(pMsg)                            (pMsg->IpAddress)
#define ProtocolGetFieldIpAddress(pMsg)                              (pMsg->IpAddress)
#define ProtocolGetFieldSocketId(pMsg)                               (pMsg->So)
#define ProtocolGetFieldLocalPort(pMsg)                              (pMsg->LocalPort)
#define ProtocolGetFieldGateWay(pMsg)                                (pMsg->GwAddr)
#define ProtocolGetFieldSubnetMask(pMsg)                             (pMsg->SubMask)
#define ProtocolGetFieldTiForOpenSocketRsp(pMsg)                     (pMsg->TI)
#define ProtocolGetFieldServerAddressForOpenSocketReq(pMsg)          (pMsg->ServAddress)
#define ProtocolGetFieldResultForOpenSocketRsp(pMsg)                 (pMsg->Status)
#define ProtocolGetFieldResultForCloseSocketRsp(pMsg)                (pMsg->Status)
#define ProtocolGetFieldServerAddressForSendReq(pMsg)                (pMsg->DestAddr)
#define ProtocolGetFieldDataBufForSendReq(pMsg)                      (pMsg->DataBuf)
#define ProtocolGetFieldDataBufForReceiveInd(pMsg)                   (pMsg->DataBuf)
#define ProtocolGetFieldDataLenForReceiveInd(pMsg)                   (pMsg->Len)
#define ProtocolGetFieldIpAddressForDnsQueryReq(pMsg)                (pMsg->Address)
#define ProtocolGetFieldIpAddressForDnsQueryRsp(pMsg)                (pMsg->Address)
#define ProtocolGetFieldDnsTiForDnsQueryRsp(pMsg)                    (pMsg->DnsTI)
#define ProtocolSetFieldSocketId(pMsg, uSo)                          (pMsg->So = uSo)
#define ProtocolSetFieldResult(pMsg, uResult)                        (pMsg->status = uResult)
#define ProtocolSetFieldIpAddress(pMsg, uIpAddr)                     (pMsg->IpAddress = uIpAddr)
#define ProtocolSetFieldPort(pMsg, uPort)                            (pMsg->LocalPort = uPort)
#define ProtocolSetFieldPppAuth(pMsg, bAuth)                         (pMsg->PppAuthParams = bAuth)
#define ProtocolSetFieldDataLenForSendReq(pMsg, uDataLen)            (pMsg->Len = uDataLen)
#define ProtocolSetFieldServerPortForSendReq(pMsg, uPort)            (pMsg->DestPort = uPort)
#define ProtocolSetFieldTiForOpenSocketReq(pMsg, uTi)                (pMsg->TI = uTi)
#define ProtocolSetFieldResultForOpenSocketRsp(pMsg, uResult)        (pMsg->Status = uResult)
#define ProtocolSetFieldResultForCloseSocketRsp(pMsg, uResult)       (pMsg->Status = uResult)
#define ProtocolSetFieldIpAddressForOpenSocketReq(pMsg, uIpAddr)     (pMsg->LocalAddr = uIpAddr)
#define ProtocolSetFieldServerPortForOpenSocketReq(pMsg, uPort)      (pMsg->ServPort = uPort)
#define ProtocolSetFieldTiForOpenSocketRsp(pMsg, uTi)                (pMsg->TI = uTi)
#define ProtocolSetFieldIpAddressForCloseDatalinkReq(pMsg, uIpAddr)  (pMsg->IpAddress = uIpAddr)
#define ProtocolSetFieldSocketTypeForOpenSocketReq(pMsg, uType)      (pMsg->SockType = uType)
#define ProtocolSetFieldLocalIpAddressForDnsQueryReq(pMsg, uIpAddr)  (pMsg->Local_IP = uIpAddr)
#define ProtocolSetFieldDnsTiForDnsQueryReq(pMsg, uDnsTi)            (pMsg->DnsTI = uDnsTi)
#define ProtocolSetFieldDnsTiForDnsQueryRsp(pMsg, uDnsTi)            (pMsg->DnsTI = uDnsTi)
#define ProtocolSetFieldDnsLenForDnsQueryReq(pMsg, uDnsLen)          (pMsg->Len = uDnsLen)
#define ProtocolSetFieldDataLenForReceiveInd(pMsg, uDataLen)         (pMsg->Len = uDataLen)
#define ProtocolSetFieldUserDataForSetSockOptReq(pMsg, uUserData)    /* G1 doesn't use it */
#define ProtocolSetFieldClientIdForSetSockOptReq(pMsg, uClientId)    /* G1 doesn't use it */
#define ProtocolSetFieldUserDataForGetSockOptReq(pMsg, uUserData)    /* G1 doesn't use it */
#define ProtocolSetFieldClientIdForGetSockOptReq(pMsg, uClientId)    /* G1 doesn't use it */
#define ProtocolSetFieldUserDataForShutdownReq(pMsg, uUserData)      /* G1 doesn't use it */
#define ProtocolSetFieldClientIdForShutdownReq(pMsg, uClientId)      /* G1 doesn't use it */
/// message define
#define PROTOCOL_MSG_CREATE_DATALINK_REQ                             (SM_IP_CREATE_DATA_LINK_REQ)
#define PROTOCOL_MSG_CREATE_DATALINK_RSP                             (SM_IP_CREATE_DATA_LINK_CNF) 
#define PROTOCOL_MSG_DESTROY_DATALINK_REQ                            (SM_IP_CLOSE_DATA_LINK_REQ)
#define PROTOCOL_MSG_DESTROY_DATALINK_RSP                            (SM_IP_CLOSE_DATA_LINK_CNF)
#define PROTOCOL_MSG_OPEN_SOCKET_REQ                                 (SM_IP_SOCKET_REQ)
#define PROTOCOL_MSG_OPEN_SOCKET_RSP                                 (SM_IP_SOCKET_CNF)
#define PROTOCOL_MSG_CLOSE_SOCKET_REQ                                (SM_IP_SOCKET_CLOSE_REQ)
#define PROTOCOL_MSG_CLOSE_SOCKET_RSP                                (SM_IP_SOCKET_CLOSE_CNF)
#define PROTOCOL_MSG_SEND_REQ                                        (SM_IP_DGRAM_REQ)
#define PROTOCOL_MSG_SEND_READY_IND                                  (SM_IP_DGRAM_CNF)
#define PROTOCOL_MSG_RECEIVE_IND                                     (SM_IP_DGRAM_IND)
#define PROTOCOL_MSG_RECEIVE_READY_REQ                               (SM_IP_DGRAM_RSP)
#define PROTOCOL_MSG_DNS_QUERY_REQ                                   (SM_IP_DNS_QUERY_REQ)
#define PROTOCOL_MSG_DNS_QUERY_RSP                                   (SM_IP_DNSQUERY_CNF)
#define PROTOCOL_MSG_STATUS_IND                                      (SM_IP_STATUS_IND)
#define PROTOCOL_MSG_DGRAM_CNF                                       (VM_IP_SWL_DGRAM_CNF)
#define PROTOCOL_MSG_DGRAM_IND                                       (VM_IP_SWL_DGRAM_IND)
#define PROTOCOL_MSG_SET_SOCKET_OPT_REQ                              (IP_SWL_SOCKET_SET_OPT_REQ)
#define PROTOCOL_MSG_SET_SOCKET_OPT_RSP                              (VM_IP_SWL_SOCKET_SET_OPT_CNF)
#define PROTOCOL_MSG_GET_SOCKET_OPT_REQ                              (IP_SWL_SOCKET_GET_OPT_REQ)
#define PROTOCOL_MSG_GET_SOCKET_OPT_RSP                              (VM_IP_SWL_SOCKET_GET_OPT_CNF)
#define PROTOCOL_MSG_SHUTDOWN_SOCKET_REQ                             (IP_SWL_SOCKET_SHUTDOWN_REQ)
#define PROTOCOL_MSG_SHUTDOWN_SOCKET_RSP                             (VM_IP_SWL_SOCKET_SHUTDOWN_CNF)
#define PROTOCOL_MSG_PING_REQ                                        (SM_IP_WIFI_PING_REQ)
#define PROTOCOL_MSG_PING_RSP                                        (SM_IP_WIFI_PING_CNF)
/// result code
#define PROTOCOL_RESULT_CODE_OK                                      (RESULT_OK)
#define PROTOCOL_RESULT_CODE_FAIL                                    (RESULT_FAIL)
#define PROTOCOL_RESULT_CODE_NB_MAX_CTXT_REACHED                     (RESULT_NB_MAX_CTXT_REACHED)
#define PROTOCOL_RESULT_CODE_DATA_LINK_ALREADY_ACTIVATED             (RESULT_DATA_LINK_ALREADY_ACTIVATED)
#define PROTOCOL_RESULT_CODE_DATALINK_CLOSE_BY_PEER                  (RESULT_COM_CLOSE_BY_PEER)
#define PROTOCOL_RESULT_CODE_IP_ERROR                                (RESULT_IP_ERROR)
#define PROTOCOL_RESULT_CODE_NO_MORE_SOCKET                          (RESULT_NO_MORE_SOCKET)
#define PROTOCOL_RESULT_CODE_BAD_SOCKET_ID                           (RESULT_BAD_SOCKET_ID)
#define PROTOCOL_RESULT_CODE_TCP_SOCKET_CLOSE_BY_SERVER              (RESULT_CONTCP_CLOSE)
#define PROTOCOL_RESULT_CODE_DNS_DHCP_ERROR                          (RESULT_DNS_DHCP_ERROR)
#define PROTOCOL_RESULT_CODE_GPRS_NOT_PRESENT                        (RESULT_GPRS_NOT_PRESENT)
#define PROTOCOL_RESULT_CODE_KO_WRONG_STATE                          (RESULT_KO_WRONG_STATE)
#define PROTOCOL_RESULT_CODE_KO_NO_IP_CONTEXT_FOUND                  (RESULT_KO_NO_IP_CONTEXT_FOUND)
#define PROTOCOL_RESULT_CODE_SET_SOCKET_OPTION_ERROR                 (RESULT_SET_SOCKET_OPTION_ERROR)
#define PROTOCOL_RESULT_CODE_GET_SOCKET_OPTION_ERROR                 (RESULT_GET_SOCKET_OPTION_ERROR)
#define PROTOCOL_RESULT_CODE_SHUTDOWN_SOCKET_ERROR                   (RESULT_SHUTDOWN_SOCKET_ERROR)
#define PROTOCOL_RESULT_CODE_CONTCP_SYN_TIMEOUT                      (RESULT_CONTCP_SYN_TIMEOUT)
#define PROTOCOL_RESULT_CODE_CONTCP_AGAIN                            (RESULT_CONTCP_AGAIN)
#define PROTOCOL_RESULT_CODE_IP_ADDRESS_EXPIRED                      (RESULT_WIFI_LEASE_TIMEOUT)
#define PROTOCOL_RESULT_CODE_CONTCP_NO_BUFFER_ERROR                  (RESULT_CONTCP_NO_BUFFER_ERROR)
#define PROTOCOL_RESULT_CODE_DATA_LINK_KO                            (RESULT_DATA_LINK_KO)
#define PROTOCOL_RESULT_CODE_PING_OK                                 (RESULT_OK)
/// others
#define PROTOCOL_DATALINK_TYPE_GPRS                                  (ip_DATA_LINK_GPRS)
#define PROTOCOL_DATALINK_TYPE_WIFI                                  (ip_DATA_LINK_WIFI)
#define PROTOCOL_SOCKET_TYPE_TCP                                     (TCP_CLIENT)
#define PROTOCOL_SOCKET_TYPE_UDP                                     (UDP_CLIENT)
/// define for cmdadatpor
#define CMDADAPTOR_IP_ADDRESS_MAX_LEN                                (SOCKMGR_IP_ADDRESS_MAX_LEN)
#define CMDADAPTOR_APN_MAX_LEN                                       (SOCKMGR_APN_MAX_LEN)
#define CMDADAPTOR_USER_NAME_MAX_LEN                                 (SOCKMGR_USER_NAME_MAX_LEN)
#define CMDADAPTOR_PASSWD_MAX_LEN                                    (SOCKMGR_PASSWD_MAX_LEN)
#define CMDADAPTOR_AUTH_STRING_LEN                                   (SOCKMGR_AUTH_STRING_LEN)
#define CMDADAPTOR_PHONENO_MAX_LEN                                   (22/VM_VML_CALLED_NB_SIZE_MAX)
/// define for sockmgrplatformdefines
#define SOCKMGR_IP_ADDRESS_MAX_LEN	                                 4 /* VM_VML_MSL_IP_ADDRESS_MAX_SIZE */
#define SOCKMGR_APN_MAX_LEN			                                 32/* VM_VML_MSL_AUTH_STRING_LEN */
#define SOCKMGR_USER_NAME_MAX_LEN	                                 32/* VM_VML_MSL_AUTH_STRING_LEN */
#define SOCKMGR_PASSWD_MAX_LEN		                                 32/* VM_VML_MSL_AUTH_STRING_LEN */
#define SOCKMGR_AUTH_STRING_LEN                                      32/* VM_VML_MSL_AUTH_STRING_LEN */
/// define for sic_net.h
#define MicDataBearer_t                                              ip_DataBearer_t
#define MicDataTypeCall_t                                            ip_DataTypeCall_t
#define MicDataLinkType_t                                            ip_DataLinkType_t
#define MicSocketType_t                                              u8
#define MIC_ASCII_IP_ADDRESS_LEN                                     (3*sizeof(ptr_msg->Body.Ip_MslDnsQueryRsp.Address)+4)
/// task related information
#define VML1_MAILBOX                                                 (CUS_MBX_3G_IP)
#define VML2_MAILBOX                                                 (CUS_MBX_3G_IP) /* currently no SIM2 in G1 */
#ifdef __WLAN_IP_SUPPORT__ /// support Wi-Fi
#define VML_WIFI_MAILBOX                                             (CUS_MBX_3G_IP)
#endif /// __WLAN_IP_SUPPORT__
#define PROTOCOL_BASE                                                (IP_BASE)
#endif /// __2G_PLATFORM__
#endif /// __VML_ADAPTOR_H__
