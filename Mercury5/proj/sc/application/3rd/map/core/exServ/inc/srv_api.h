#ifndef _SRV_API_H_
#define _SRV_API_H_

#include "ven_handle.h"
#include "ven_socket.h"

typedef struct http_proxy_setting
{
    char    *url;
    char    *user;
    char    *password;
    int     port;
}http_proxy_setting_t;

typedef struct http_page_info
{
    char	*date;
    char	*server;
    char	*last_modified;
    char	*etag;
    char	*content_type;
    char 	*location;
    int	content_length;
    int 	header_length;
}http_page_info_t;

typedef enum http_status_codes
{
    HTTP_200_OK = 0, 
    HTTP_301_MOVED_PERMANENTLY,
    HTTP_302_FOUND,
    HTTP_303_SEE_OTHER,
    HTTP_403_FORBIDDEN,
    HTTP_404_NOT_FOUND,
    HTTP_ERROR_RESPONSE,
}http_status_codes_e;

typedef void (*srv_connect_cbfunc_t) (ven_socket_ret_t result);

http_status_codes_e http_parse_header(char *buf, http_page_info_t *page_info, s32 len);
void srv_register_recv_cb(ven_socket_recv_cbfunc_t register_recv_cbfunc);
void srv_register_connect_cb(srv_connect_cbfunc_t connect_cbfunc);
ven_socket_ret_t srv_init(u32 u32Handle, ven_common_sim_id_t SimID, 
                            ven_setting_network_profile_t *pNetworkProfile, ven_socket_create_datalink_cbfunc_t create_datalink_cb);
MBOOL srv_get(u32 u32Handle, u16* u16Http, http_proxy_setting_t *proxy_setting);
MBOOL srv_post(u32 u32Handle, u16 *u16Http, char *message, http_proxy_setting_t *proxy_setting);
void srv_cancel(void);
void srv_final(u32 u32Handle, ven_socket_close_datalink_cbfunc_t close_datalink_cb);

#endif
