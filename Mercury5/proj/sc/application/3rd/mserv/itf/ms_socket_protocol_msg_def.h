#ifndef __MS_SOCKET_PROTOCOL_MSG_DEF_H__
#define __MS_SOCKET_PROTOCOL_MSG_DEF_H__

#include "vm_vml_socket.h" /* for vm_xxx_t */
#ifdef __3G_RIL_MMI__
#include "ip_prim.hc"/* IP layer defination */
#include "ip_msg.hi"
#include "vm_ip.h"
#endif // __3G_RIL_MMI__

#ifdef __3G_RIL_MMI__ /// for G1
#define MS_SOCKET_PROTOCOL_CMN_MSG_COL	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_CreateDataLinkReq_t, Ip_MslCreateDataLinkReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_CloseDataLinkReq_t, Ip_MslCloseDataLinkReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_SocketReq_t, Ip_MslCreateSocketReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_SocketClose_t, Ip_MslCloseSocketReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_DgramReq_t, Ip_MslSendReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_DgramRsp_t, Ip_MslReceiveRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_DnsQueryReq_t, Ip_MslDnsQueryReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_swl_SocketGetOptReq_t, Ip_MslGetSocketOptReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_swl_SocketSetOptReq_t, Ip_MslSetSocketOptReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_swl_SocketShutdownReq_t, Ip_MslShutdownSocketReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_CreateDataLinkCnf_t, Ip_MslCreateDataLinkRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_CloseDataLinkCnf_t, Ip_MslCloseDataLinkRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_SocketCnf_t, Ip_MslCreateSocketRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_CloseSocketCnf_t, Ip_MslCloseSocketRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_DgramInd_t, Ip_MslReceiveInd)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_DgramCnf_t, Ip_MslSendReadyInd)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_StatusInd_t, Ip_MslStatusInd)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_DnsQueryCnf_t, Ip_MslDnsQueryRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_SocketGetOptCnf_t, Ip_MslGetSocketOptRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_SocketSetOptCnf_t, Ip_MslSetSocketOptRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(ip_SocketShutdownCnf_t, Ip_MslShutdownSocketRsp)	\

#else /// for B3
#define MS_SOCKET_PROTOCOL_CMN_MSG_COL	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCreateDataLinkReq_t, Mserv_MslCreateDataLinkReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCloseDataLinkReq_t, Mserv_MslCloseDataLinkReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCreateSocketReq_t, Mserv_MslCreateSocketReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCloseSocketReq_t, Mserv_MslCloseSocketReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslSendReq_t, Mserv_MslSendReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslReceiveReadyReq_t, Mserv_MslReceiveReadyReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslDnsQueryReq_t, Mserv_MslDnsQueryReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslGetSocketOptReq_t, Mserv_MslGetSocketOptReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslSetSocketOptReq_t, Mserv_MslSetSocketOptReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslShutdownSocketReq_t, Mserv_MslShutdownSocketReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCreateDataLinkRsp_t, Mserv_MslCreateDataLinkRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCloseDataLinkRsp_t, Mserv_MslCloseDataLinkRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCreateSocketRsp_t, Mserv_MslCreateSocketRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslCloseSocketRsp_t, Mserv_MslCloseSocketRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslReceiveInd_t, Mserv_MslReceiveInd)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslSendReadyInd_t, Mserv_MslSendReadyInd)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslStatusInd_t, Mserv_MslStatusInd)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslDnsQueryRsp_t, Mserv_MslDnsQueryRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslGetSocketOptRsp_t, Mserv_MslGetSocketOptRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslSetSocketOptRsp_t, Mserv_MslSetSocketOptRsp)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslShutdownSocketRsp_t, Mserv_MslShutdownSocketRsp)	\

#endif/* __3G_RIL_MMI__ */

#define MS_SOCKET_PROTOCOL_WIFI_MSG_COL	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslPingReq_t, Mserv_MslPingReq)	\
	MS_SOCKET_PROTOCOL_MSG_DEF(vm_VmlMslPingRsp_t, Mserv_MslPingRsp)	\



#endif/* __MS_SOCKET_PROTOCOL_MSG_DEF_H__ */
