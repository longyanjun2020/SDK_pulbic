#ifndef _WINSOCK_TEST_H_
#define _WINSOCK_TEST_H_
#ifdef __SDK_V1_TEST__

// for the result field of test item
#define NET_WINSOCK_TEST_NORUN   0
#define NET_WINSOCK_TEST_OK      1
#define NET_WINSOCK_TEST_ERROR   2

typedef struct __NET_Winsock_Test_Item_t
{
  void (* TestItem ) (struct __NET_Winsock_Test_Item_t*);
  u_int index;
  u_int result;
} NET_Winsock_Test_Item_t;
//===========================================================
//===========================================================
static void NET_Winsock_Test_Socket_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Socket_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Socket_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Socket_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Socket_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Socket_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Socket_7(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Socket_8(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_Inet_aton_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Inet_aton_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Inet_aton_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Inet_aton_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Inet_aton_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Inet_aton_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_Inet_aton_7(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_getprotobyname_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getprotobyname_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getprotobyname_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getprotobyname_4(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_getprotobynumber_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getprotobynumber_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getprotobynumber_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getprotobynumber_4(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_getservbyname_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyname_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyname_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyname_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyname_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyname_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyname_7(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_getservbyport_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyport_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyport_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyport_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_getservbyport_5(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_gethostbyaddr_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyaddr_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyaddr_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyaddr_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyaddr_5(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_gethostbyname_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_4(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_gethostbyname_cb_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_cb_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_cb_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_cb_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_cb_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_cb_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostbyname_cb_7(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_gethostname_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostname_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostname_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_gethostname_4(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_connect_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_7(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_connect_cb_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_7(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_8(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_9(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_connect_cb_10(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_recv_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_5(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_recv_cb_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_cb_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_cb_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_cb_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_cb_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_cb_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recv_cb_7(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_recvfrom_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_7(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_recvfrom_cb_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_cb_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_cb_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_cb_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_cb_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_cb_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_cb_7(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_recvfrom_cb_8(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_send_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_6(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_send_cb_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_7(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_8(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_9(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_10(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_send_cb_11(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_sendto_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_7(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_sendto_cb_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_2(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_3(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_4(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_5(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_6(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_7(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_8(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_9(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_10(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_sendto_cb_11(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_closesocket_cb_1(NET_Winsock_Test_Item_t *item);
static void NET_Winsock_Test_closesocket_cb_2(NET_Winsock_Test_Item_t *item);

static void NET_Winsock_Test_multi_connect_1(NET_Winsock_Test_Item_t *item);

static void user_recv_cb (SOCKET s, u8 *pdata, u32 len);
static void user_recvfrom_cb (SOCKET s, u8 *pdata, u32 len, struct sockaddr *from, s32 fromlen);
static void user_connect_cb (SOCKET s, u8 retval);
static void user_send_cb (SOCKET s, s8 retval);
static void user_sendto_cb (SOCKET s, s8 retval);
static void user_closesocket_cb (SOCKET s, u8 retval);

//===========================================================
//===========================================================
//===========================================================
#define __UDP_TEST__
static NET_Winsock_Test_Item_t NET_Test_Item[]=
{
    {NET_Winsock_Test_Socket_1,0,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Socket_2,1,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Socket_3,2,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Socket_4,3,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Socket_5,4,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Socket_6,5,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Socket_7,6,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Socket_8,7,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Inet_aton_1,8,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Inet_aton_2,9,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Inet_aton_3,10,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Inet_aton_4,11,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Inet_aton_5,12,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Inet_aton_6,13,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_Inet_aton_7,14,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobyname_1,15,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobyname_2,16,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobyname_3,17,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobyname_4,18,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobynumber_1,19,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobynumber_2,20,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobynumber_3,21,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getprotobynumber_4,22,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyname_1,23,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyname_2,24,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyname_3,25,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyname_4,26,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyname_5,27,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyname_6,28,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyname_7,29,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyport_1,30,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyport_2,31,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyport_3,32,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyport_4,33,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_getservbyport_5,34,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyaddr_1,35,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyaddr_2,36,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyaddr_3,37,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyaddr_4,38,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyaddr_5,39,NET_WINSOCK_TEST_NORUN},
/*    {NET_Winsock_Test_gethostbyname_1,32,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_2,33,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_3,34,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_4,35,NET_WINSOCK_TEST_NORUN},*/
    {NET_Winsock_Test_gethostbyname_cb_2,71,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_cb_1,70,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_cb_2,71,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_cb_3,72,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_cb_4,73,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_cb_5,74,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_cb_6,75,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostbyname_cb_7,76,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostname_1,40,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostname_2,41,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostname_3,42,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_gethostname_4,43,NET_WINSOCK_TEST_NORUN},
/*    {NET_Winsock_Test_connect_1,40,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_2,41,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_3,42,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_4,43,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_5,44,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_6,45,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_7,46,NET_WINSOCK_TEST_NORUN},*/
    {NET_Winsock_Test_connect_cb_1,44,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_2,45,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_3,46,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_4,47,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_5,48,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_6,49,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_7,50,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_8,51,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_9,52,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_connect_cb_10,53,NET_WINSOCK_TEST_NORUN},
/*    {NET_Winsock_Test_recv_1,47,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_2,48,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_3,49,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_4,50,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_5,51,NET_WINSOCK_TEST_NORUN},*/
    {NET_Winsock_Test_recv_cb_1,54,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_cb_2,55,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_cb_3,56,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_cb_4,57,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_cb_5,58,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_cb_6,59,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recv_cb_7,59,NET_WINSOCK_TEST_NORUN},
/*    {NET_Winsock_Test_recvfrom_1,52,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_2,53,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_3,54,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_4,55,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_5,56,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_6,57,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_7,58,NET_WINSOCK_TEST_NORUN},*/
#ifdef __UDP_TEST__
    {NET_Winsock_Test_recvfrom_cb_1,72,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_cb_2,73,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_cb_3,72,NET_WINSOCK_TEST_NORUN},
//    {NET_Winsock_Test_recvfrom_cb_4,73,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_cb_5,72,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_cb_6,72,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_cb_7,72,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_recvfrom_cb_8,72,NET_WINSOCK_TEST_NORUN},
#endif
/*    {NET_Winsock_Test_send_1,59,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_2,60,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_3,61,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_4,62,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_5,63,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_6,71,NET_WINSOCK_TEST_NORUN},*/
    {NET_Winsock_Test_send_cb_1,60,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_9,61,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_10,62,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_2,63,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_3,64,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_4,65,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_5,66,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_6,67,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_7,68,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_8,69,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_send_cb_11,62,NET_WINSOCK_TEST_NORUN},
/*    {NET_Winsock_Test_sendto_1,64,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_2,65,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_3,66,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_4,67,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_5,68,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_6,69,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_7,70,NET_WINSOCK_TEST_NORUN},*/
#ifdef __UDP_TEST__
    {NET_Winsock_Test_sendto_cb_1,64,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_2,65,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_3,66,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_4,67,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_5,68,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_6,69,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_7,70,NET_WINSOCK_TEST_NORUN},
//    {NET_Winsock_Test_sendto_cb_8,70,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_9,70,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_10,70,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_sendto_cb_11,70,NET_WINSOCK_TEST_NORUN},
#endif
    {NET_Winsock_Test_closesocket_cb_1,77,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_closesocket_cb_2,78,NET_WINSOCK_TEST_NORUN},
    {NET_Winsock_Test_multi_connect_1,79,NET_WINSOCK_TEST_NORUN},
    {NULL,65535,NET_WINSOCK_TEST_NORUN}
};

#endif /* __SDK_V1_TEST__ */
#endif /* _WINSOCK_TEST_H_ */
