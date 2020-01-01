#ifndef _zm_socket_h_
#define _zm_socket_h_

#include "zm_typedef.h"

typedef void(*zm_network_event_callback)(zm_net_handle lHandler, zm_net_state nState, zm_net_message* pMess);

/*
 * 连接服务器
 */
zm_extern zm_int zm_connect(const zm_int8* pszIp, zm_uint16 nPort, zm_gprs_type gprs_type, zm_network_event_callback pCallBack);

/*
 * 发送数据
 */
zm_extern zm_int zm_send(zm_net_handle lHandler, const zm_int8* pszBuffer, zm_int cbBuffer);

/*
 * 关闭socket
 */
zm_extern zm_bool zm_disconnect(zm_net_handle sock);

////////////////////////////////////////////////////////////////////////////////////////////
// socket 接口 2.0 版本
////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
   zm_sock_stream =0,
   zm_sock_dgram
}zm_socket_type_enum;

typedef struct
{
	//result=0	表示成功
	zm_uint16	result;
	zm_uint16	addr_len;
	zm_uint8	addr[16];
}zm_socket_get_host_by_name_ind;
typedef zm_void (*zm_socket_gethostbyname_resp)(zm_socket_get_host_by_name_ind* pInd);

typedef struct 
{
   zm_uint16 addr_len;
   zm_uint16 port;
   zm_uint8  addr[16];
}zm_sockaddr_struct;

typedef enum
{
	zm_socket_ex_ev_connect = 0x1,
	zm_socket_ex_ev_write = 0x2,
	zm_socket_ex_ev_read = 0x4,
	zm_socket_ex_ev_close = 0x8,
	zm_socket_ex_ev_network_inited = 0x10
}zm_socket_ex_event;

typedef zm_void (*zm_network_app_soc_notify)(zm_net_handle s, zm_socket_ex_event ev);

/**
 * 事件通知
 */
zm_extern zm_int zm_socket_notify_ind(zm_void* inMsg);

/**
 * 设置上网账号
 */
zm_extern zm_void zm_socket_network_init(zm_gprs_type type, zm_network_app_soc_notify ev_callback);

/**
 * 创建socket
 */
zm_extern zm_net_handle zm_socket_create(zm_socket_type_enum type,zm_gprs_type gprstype, zm_network_app_soc_notify ev_callback);

/**
 * 域名解析
 */
zm_extern zm_int8 zm_socket_gethostbyname(const zm_int8* host,zm_int8* addr, zm_int* addr_len, zm_socket_gethostbyname_resp cb);

/**
 * 绑定
 */
zm_extern zm_int8 zm_socket_bind(zm_net_handle s, zm_sockaddr_struct* addr);

/**
 * 监听
 */
zm_extern zm_int8 zm_socket_listen(zm_net_handle s, zm_int backlog);

/**
 * 连接
 */
zm_extern zm_int8 zm_socket_connect(zm_net_handle s, zm_sockaddr_struct* addr);

/**
 * 发送to addr
 */
zm_extern zm_int zm_socket_sendto(zm_net_handle s,zm_uint8*buf, zm_int len, zm_sockaddr_struct *addr);

/**
 * 发送
 */
zm_extern zm_int zm_socket_send(zm_net_handle s,zm_uint8*buf, zm_int len);

/**
 * 接收from fromaddr
 */
zm_extern zm_int zm_socket_recvfrom(zm_net_handle s, zm_uint8 *buf, zm_int len, zm_sockaddr_struct *fromaddr);

/**
 * 接收
 */
zm_extern zm_int zm_socket_recv(zm_net_handle s, zm_uint8 *buf, zm_int len);         

/**
 * 获取本地IP
 */
zm_extern zm_int8 zm_socket_getsockaddr(zm_net_handle s, zm_bool local, zm_sockaddr_struct* sock);

/**
 * 关闭socket
 */
zm_extern zm_void zm_socket_close(zm_net_handle s);

/**
 * 网络断开
 */
zm_extern zm_void zm_network_disconnect(zm_void);


//////////////////////////////////////////////////////////////////////////
// 在线挂QQ接口															//
//////////////////////////////////////////////////////////////////////////
#include "zm_ipqq_ptr.h"

#endif//_zm_socket_h_
