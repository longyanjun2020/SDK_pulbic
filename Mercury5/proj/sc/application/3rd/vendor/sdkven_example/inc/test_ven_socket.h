#ifndef __TEST_VEN_SOCKET_H__
#define __TEST_VEN_SOCKET_H__

// for the result field of test item
#define VEN_SOCKET_TEST_NORUN   0
#define VEN_SOCKET_TEST_OK      1
#define VEN_SOCKET_TEST_ERROR   2

#include "ven_socket.h"

typedef struct __VEN_Socket_Test_Item_t
{
  void (* TestItem ) (struct __VEN_Socket_Test_Item_t*);
  unsigned int index;
  unsigned int result;
} VEN_Socket_Test_Item_t;
//===========================================================
//===========================================================
static void VEN_Socket_Test_Socket_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Socket_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Socket_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Socket_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Socket_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Socket_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Socket_7(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Socket_8(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_Inet_aton_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Inet_aton_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Inet_aton_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Inet_aton_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Inet_aton_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Inet_aton_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_Inet_aton_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_getprotobyname_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getprotobyname_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getprotobyname_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getprotobyname_4(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_getprotobynumber_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getprotobynumber_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getprotobynumber_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getprotobynumber_4(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_getservbyname_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyname_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyname_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyname_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyname_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyname_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyname_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_getservbyport_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyport_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyport_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyport_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getservbyport_5(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_gethostbyaddr_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyaddr_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyaddr_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyaddr_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyaddr_5(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_gethostbyname_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_4(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_gethostname_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostname_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostname_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostname_4(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_connect_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_send_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_6(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_sendto_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_6(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_closesocket_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_closesocket_2(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_gethostbyname_async_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_async_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_async_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_async_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_async_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_async_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_gethostbyname_async_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_connect_async_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_7(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_8(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_9(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_connect_async_10(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_regRecvCB_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvCB_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvCB_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvCB_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvCB_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvCB_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvCB_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_regRecvFromCB_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvFromCB_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvFromCB_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvFromCB_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvFromCB_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_regRecvFromCB_6(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_send_async_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_7(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_8(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_9(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_10(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_send_async_11(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_sendto_async_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_7(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_8(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_9(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_sendto_async_10(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_closesocket_async_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_closesocket_async_2(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_multi_connect_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_multi_connect_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_multi_connect_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_callback_call_closesocket_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_callback_call_closesocket_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_callback_call_closesocket_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_callback_call_closesocket_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_callback_call_closesocket_5(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_recv_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recv_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recv_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recv_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recv_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recv_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recv_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_recvfrom_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recvfrom_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recvfrom_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recvfrom_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recvfrom_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recvfrom_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_recvfrom_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_setsockopt_0(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_setsockopt_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_setsockopt_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_setsockopt_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_setsockopt_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_setsockopt_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_setsockopt_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_setsockopt_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_getsockopt_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getsockopt_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getsockopt_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getsockopt_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getsockopt_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getsockopt_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_getsockopt_7(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_get_set_sockopt_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_get_set_sockopt_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_get_set_sockopt_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_get_set_sockopt_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_get_set_sockopt_5(VEN_Socket_Test_Item_t *item);

static void VEN_Socket_Test_shutdown_1(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_2(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_3(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_4(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_5(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_6(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_7(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_8(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_shutdown_9(VEN_Socket_Test_Item_t *item);

//===========================================================

#ifdef __SDK_MULTI_BEARER_TEST__
static void VEN_Socket_Test_RegStatusCb_Ex(VEN_Socket_Test_Item_t *item);
static void VEN_Socket_Test_DeRegStatusCb_Ex(VEN_Socket_Test_Item_t *item);
#endif/* __SDK_MULTI_BEARER_TEST__ */

//===========================================================

//===========================================================
#define __UDP_TEST__
static VEN_Socket_Test_Item_t VEN_Test_Item[]=
{
	/// 1- 10
    {VEN_Socket_Test_Socket_1,0,VEN_SOCKET_TEST_NORUN},

    {VEN_Socket_Test_Socket_2,1,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Socket_3,2,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Socket_4,3,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Socket_5,4,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Socket_6,5,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Socket_7,6,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Socket_8,7,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Inet_aton_1,8,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Inet_aton_2,9,VEN_SOCKET_TEST_NORUN},
    
	/// 11 - 20
	{VEN_Socket_Test_Inet_aton_3,10,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Inet_aton_4,11,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Inet_aton_5,12,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Inet_aton_6,13,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_Inet_aton_7,14,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getprotobyname_1,15,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getprotobyname_2,16,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getprotobyname_3,17,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getprotobyname_4,18,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getprotobynumber_1,19,VEN_SOCKET_TEST_NORUN},

	/// 21 - 30
	{VEN_Socket_Test_getprotobynumber_2,20,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getprotobynumber_3,21,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getprotobynumber_4,22,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyname_1,23,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyname_2,24,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyname_3,25,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyname_4,26,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyname_5,27,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyname_6,28,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyname_7,29,VEN_SOCKET_TEST_NORUN},

	/// 31 - 40
	{VEN_Socket_Test_getservbyport_1,30,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyport_2,31,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyport_3,32,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyport_4,33,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getservbyport_5,34,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyaddr_1,35,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyaddr_2,36,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyaddr_3,37,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyaddr_4,38,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyaddr_5,39,VEN_SOCKET_TEST_NORUN},

	/// 41 - 50
	{VEN_Socket_Test_gethostbyname_1,32,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_2,33,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_3,34,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_4,35,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostname_1,40,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostname_2,41,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostname_3,42,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostname_4,43,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_1,40,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_2,41,VEN_SOCKET_TEST_NORUN},

	/// 51 - 60
	{VEN_Socket_Test_connect_3,42,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_4,43,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_5,44,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_6,45,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_7,46,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvCB_1,47,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvCB_3,49,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvCB_4,50,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvCB_5,51,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvCB_6,52,VEN_SOCKET_TEST_NORUN},

    /// 61 - 70
    {VEN_Socket_Test_regRecvCB_7,53,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_1,59,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_2,60,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_3,61,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_4,62,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_5,63,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_6,71,VEN_SOCKET_TEST_NORUN},
#ifdef __UDP_TEST__
    {VEN_Socket_Test_regRecvFromCB_1,52,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvFromCB_3,54,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvFromCB_4,55,VEN_SOCKET_TEST_NORUN},

    /// 71 - 80
    {VEN_Socket_Test_regRecvFromCB_5,56,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvFromCB_6,57,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_1,64,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_2,65,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_3,66,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_4,67,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_5,68,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_6,69,VEN_SOCKET_TEST_NORUN},
#endif
/// async check parameter
    {VEN_Socket_Test_gethostbyname_async_3,72,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_async_4,73,VEN_SOCKET_TEST_NORUN},

    /// 81 - 90
    {VEN_Socket_Test_gethostbyname_async_7,76,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_1,44,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_2,45,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_3,46,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_4,47,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_5,48,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_6,49,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_9,52,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_10,53,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_1,60,VEN_SOCKET_TEST_NORUN},

    /// 91 - 100
    {VEN_Socket_Test_send_async_2,63,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_3,64,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_9,61,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_10,62,VEN_SOCKET_TEST_NORUN},
/// async
    {VEN_Socket_Test_closesocket_1,77,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_closesocket_2,78,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_1,64,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_2,65,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_3,66,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_5,68,VEN_SOCKET_TEST_NORUN},

    /// 101 - 110
    {VEN_Socket_Test_sendto_async_6,69,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_8,70,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_9,70,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_async_2,71,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_async_1,70,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_async_2,71,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_async_5,74,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_gethostbyname_async_6,75,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_connect_async_8,51,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_5,66,VEN_SOCKET_TEST_NORUN},

    /// 111 - 120
    {VEN_Socket_Test_send_async_6,67,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_7,68,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_8,69,VEN_SOCKET_TEST_NORUN},
#ifdef __UDP_TEST__
    {VEN_Socket_Test_sendto_async_7,70,VEN_SOCKET_TEST_NORUN},
#endif
    {VEN_Socket_Test_closesocket_async_1,77,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_11,62,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_10,70,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recv_1,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recv_2,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recv_3,0,VEN_SOCKET_TEST_NORUN},

    /// 121 - 130
    {VEN_Socket_Test_recv_4,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recv_5,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recv_6,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recv_7,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recvfrom_1,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recvfrom_2,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recvfrom_3,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recvfrom_4,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recvfrom_5,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_recvfrom_6,0,VEN_SOCKET_TEST_NORUN},

    /// 131 - 140
    {VEN_Socket_Test_recvfrom_7,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_0,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_1,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_2,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_3,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_4,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_5,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_6,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_setsockopt_7,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_get_set_sockopt_1,0,VEN_SOCKET_TEST_NORUN},

    /// 141 - 150
    {VEN_Socket_Test_get_set_sockopt_2,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_get_set_sockopt_3,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_get_set_sockopt_4,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_get_set_sockopt_5,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getsockopt_1,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getsockopt_2,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getsockopt_3,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getsockopt_4,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getsockopt_5,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_getsockopt_6,0,VEN_SOCKET_TEST_NORUN},

    /// 151 - 160
    {VEN_Socket_Test_getsockopt_7,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_1,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_2,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_3,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_4,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_5,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_6,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_7,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_8,0,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_shutdown_9,0,VEN_SOCKET_TEST_NORUN},

    /// 161 - 170
    {VEN_Socket_Test_callback_call_closesocket_1,79,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_callback_call_closesocket_2,79,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_callback_call_closesocket_3,79,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_callback_call_closesocket_4,79,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_callback_call_closesocket_5,79,VEN_SOCKET_TEST_NORUN},
/// callback function pointer is null
    {VEN_Socket_Test_connect_async_7,50,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvCB_2,48,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_regRecvFromCB_2,53,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_send_async_4,65,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_sendto_async_4,67,VEN_SOCKET_TEST_NORUN},

    /// 171 - 174
    {VEN_Socket_Test_closesocket_async_2,78,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_multi_connect_1,79,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_multi_connect_2,79,VEN_SOCKET_TEST_NORUN},
    {VEN_Socket_Test_multi_connect_3,79,VEN_SOCKET_TEST_NORUN},

};
#endif  /* _WINSOCK_TEST_H_ */

