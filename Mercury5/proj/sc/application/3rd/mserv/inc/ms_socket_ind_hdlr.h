#ifndef __MS_SOCKET_IND_HDLR_H__
#define __MS_SOCKET_IND_HDLR_H__

void Mserv_socket_bearer_status_change_hdlr(void *pvMsg);
void Mserv_socket_data_traffic_periodic_check_hdlr(void *pvMsg);
void Mserv_socket_set_cmd_timeout_hdlr(void *pvMsg);

#endif/* __MS_SOCKET_IND_HDLR_H__ */
