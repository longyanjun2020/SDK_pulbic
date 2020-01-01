#ifndef _NEMOMP_NETWORK_H
#define _NEMOMP_NETWORK_H

extern void nemomp_network_initialize(void);
extern void nemomp_network_finalize(void);
extern nm_int32 nemomp_network_errno(void);
extern nm_int32 nemomp_network_get_local_port(nm_int32 handle);
extern nm_int32 nemomp_network_get_remote_port(nm_int32 handle);
extern nm_char* nemomp_network_get_local_address(nm_int32 handle);
extern nm_char* nemomp_network_get_remote_address(nm_int32 handle);
///extern void nemomp_network_check_event(void); // 20081023: Removed
extern nm_int32 nemomp_network_getaddress_byname(nm_char *host, nm_int32 *handle); //20091015: Changed
extern nm_int32 nemomp_network_check_addressbyname_result(nm_char *host, nm_int32 *handle); //20090304: Changed, 20091015: Changed
extern nm_int32 nemomp_network_gethost_byaddress(nm_int32 ipnumber, nm_char *host);
extern nm_int32 nemomp_network_check_hostbyaddress_result(nm_int32 ipnumber); //20090304: Changed

extern nm_int32 nemomp_datagram_open(nm_int32 port, nm_char **exception);
extern void nemomp_datagram_set_nonblocking(nm_int32 handle);
extern nm_int32 nemomp_datagram_recv(nm_int32 handle, nm_int32 *ipnumber, nm_int32 *port, nm_char *buffer, nm_int32 length);
extern nm_int32 nemomp_datagram_send(nm_int32 handle, nm_int32 ipnumber, nm_int32 port, nm_char *buffer, nm_int32 length);
extern nm_int32 nemomp_datagram_get_max_size(nm_int32 handle);
extern nm_int32 nemomp_datagram_get_nominal_size(nm_int32 handle);

extern nm_int32 nemomp_socket_open(nm_char *name, nm_int32 port, nm_char **exception, nm_int32 *fd);
extern nm_int32 nemomp_socket_close(nm_int32 handle);
extern nm_int32 nemomp_socket_connect_polling(nm_char *name, nm_int32 port, nm_int32 *handle, nm_char **exception); //20091014: Changed
extern nm_int32 nemomp_socket_send(nm_int32 handle, nm_char *buffer, nm_int32 len);
extern nm_int32 nemomp_socket_recv(nm_int32 handle, nm_char *buffer, nm_int32 len);
extern nm_int32 nemomp_socket_available(nm_int32 handle);
extern void nemomp_socket_set_nonblocking(nm_int32 handle);
extern void nemomp_socket_shutdown_input(nm_int32 handle);
extern void nemomp_socket_shutdown_output(nm_int32 handle);
extern nemomp_socket_setsockoption(nm_int32 handle, nm_int32 flag, nm_int32 optval);
extern nm_int32 nemomp_socket_getsockoption(nm_int32 handle, nm_int32 flag, nm_int32 *optval);

#endif /* _NEMOMP_NETWORK_H */
