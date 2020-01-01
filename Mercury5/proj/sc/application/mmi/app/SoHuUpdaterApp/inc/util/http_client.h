#ifndef _HTTP_CLIENT_H /* Prevent multiple inclusion */
#define _HTTP_CLIENT_H

#include "encrpty.h"
#include "publicFunc.h"

//#define TYM_WDPF_DEBUG 1
//#define HTTP_REQ_FILE  (L"http_req.txt")
#define SG_IS_DIGIT(a) (a >= '0' && a <= '9')
#define SG_IS_LHEX(a)  (SG_IS_DIGIT(a) || a >= 'a' && a <='f')
#define SG_IS_HEX(a)   (SG_IS_LHEX(a) || a >= 'A' && a <= 'F')
#define SG_IS_CHAR(a)  (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z')


#define SG_HTTP_MAX_ENTITY_LEN    5120//1460
#define SG_HTTP_MAX_REQ_LEN       1800//2048
#define SG_HTTP_MAX_HEAD          1024

#define SG_HTTP_MAX_SESSION       5
#define SG_HTTP_REQ_TIMEOUT       30000
#define SG_HTTP_REQ_INTERVAL      10
#define SG_HTTP_MAX_RETRY         0

#define SG_HTTP_MAX_SOC           5
#define SG_HTTP_MAX_RECV_LEN      (43800)
#define SG_HTTP_MAX_SEND_BUF      512
//#define WDPF_ACCOUNT_ID 10

#define SG_PROXY_PORT             80
#define SG_PROXY_ADDR             "10.0.0.172"//"input.shouji.sogou.com"//
#define SG_SERVER_ADDR             "http://input.shouji.sogou.com"//

#define SG_SOCKET_HANDLE          SG_UINT32 //ISocket *//

//#define SG_HOST_ADDR              AEEDNSResult

typedef enum
{
    HTTP_GET,
    HTTP_POST,
    HTTP_METHOD_NUM
} sg_http_method;

typedef enum
{
    PARSE_STATUS = 0,
    PARSE_HEAD,
    PARSE_ENTITY
} sg_http_parse_state;

typedef enum
{
    HTTP_CB_COMPLETE = 0,
    HTTP_CB_ERROR = 1,
    HTTP_CB_PARTIAL = 2,
    HTTP_CB_CONNECTED = 3,
} sg_http_cb_status;

typedef enum
{
    HTTP_SOC_CLOSE = 0,
    HTTP_SOC_CREATE,
    HTTP_SOC_CONNECTING,
    HTTP_SOC_CONNECTED,
} sg_soc_state;

typedef enum
{
    HTTP_SOC_BLOCK = -2,
    HTTP_SOC_ERR = -1,
    HTTP_SOC_SUCCESS = 0,
} sg_soc_err;

typedef enum
{
    HTTP_SOC_STREAM = 0,
    HTTP_SOC_DATAGRAM,
} sg_soc_type;

typedef enum
{
    HTTP_SOC_MSG_CONNECT = 0,
    HTTP_SOC_MSG_READ,
    HTTP_SOC_MSG_WRITE,
    HTTP_SOC_MSG_CLOSE
} sg_soc_msg_id;

typedef enum
{
    HTTP_SESSION_IDLE = 0,
    HTTP_SESSION_CONNECTED
} sg_session_state;

typedef void (*SgTPGetHostCbFunc) (void *msg);
typedef void (*SgHttpFuncPtr) (void *, void *, sg_http_cb_status);

typedef struct
{
    SG_UINT8 *str;
    SG_UINT32 len;
} sg_http_string;


typedef struct
{
    SG_UINT32 first_byte_pos;
    SG_UINT32 last_byte_pos;
    SG_UINT32 total_len;
} sg_content_range_struct;

typedef struct
{
    SG_UINT32 content_length;
    SG_UINT32 content_length_left;
    sg_content_range_struct *content_range;
} sg_entity_head_struct;

typedef struct
{
    sg_http_string fisrt_byte_pos;
    sg_http_string last_byte_pos;
} sg_range_struct;

typedef struct
{
    sg_http_method method;
    sg_http_string url;
    sg_range_struct *range;
    SG_UPDATE_INF *cookies;
    sg_entity_head_struct *entity_head;
    sg_http_string entity_body;
} sg_http_req_struct;

typedef struct
{
    sg_http_parse_state parse_state;
    SG_UINT16 status;
    SG_UINT8 chunked;
    SG_INT32 chunk_size;
    SG_UINT8 isSogou;
    sg_entity_head_struct *entity_head;
    sg_http_string entity_body;
} sg_http_res_struct;

typedef struct
{
    void *pUser;
    SgHttpFuncPtr http_callback;
    SG_UINT8 *data;
    SG_UINT32 len;
    SG_UINT8 retry;
    SG_UINT8 interval;
    sg_session_state state;
    sg_http_res_struct http_res;
    SG_UINT8 *hostname;
    SG_UINT16 port;
    SG_UINT8 *uri;
    void *http_client;
} sg_http_session_struct;

typedef struct
{
    sg_soc_state state;
    SG_SOCKET_HANDLE socket_id;
    SG_INT32 rcvd_data_len;
    SG_UINT8 rcvd_buffer[SG_HTTP_MAX_RECV_LEN];
    SG_UINT32 snd_counter;
    sg_http_session_struct *session;
    void *http_client;
    u8 *pdns_buffer;
    u8 dns_data_len;
    void *user_data;
} sg_soc_struct;

typedef struct
{
    sg_soc_msg_id msg_id;
    sg_soc_struct *soc_handle;
    sg_soc_err err;
} soc_msg_struct;

typedef struct
{
    sg_soc_struct  soc_table[SG_HTTP_MAX_SOC];
    sg_http_session_struct http_session_table[SG_HTTP_MAX_SESSION];
    //INetMgr     *pINetMgr;
} sg_http_client_struct;

extern SG_INT8 g_bHttpInit;

extern SG_UINT8 http_create_str(SG_UINT8 *data, sg_http_string *str);
extern SG_UINT8 http_create_payload(SG_UINT32 len, SG_UINT8 *data, sg_http_string *str);
extern void     sg_http_init(sg_http_client_struct* http_client);
extern void     sg_http_destory(sg_http_client_struct* http_client);
extern void     sg_http_destroy_session(sg_http_session_struct *http_session);
extern SG_UINT8 sg_http_session_send_req(sg_http_client_struct* http_client,
                                            void *pUser, SgHttpFuncPtr callback,
                                            sg_http_req_struct* http_req);
extern SG_UINT8 sg_http_session_send_req_ex(sg_http_client_struct *http_client,
                                            void *pUser, SgHttpFuncPtr callback,
                                            sg_http_req_struct *http_req,
                                            sg_http_session_struct **http_session);
extern void     sg_http_session_close(sg_http_session_struct *session);
extern void     sg_http_session_close_noretry(sg_http_session_struct *session);
extern void     sg_http_session_error(sg_http_session_struct *session);
extern void     sg_http_session_rev_res(sg_http_session_struct *session);
extern void     sg_http_session_rev_res_partial(sg_http_session_struct *session);
extern void     sg_http_session_rev_res_connected(sg_http_session_struct *session);

extern SG_UINT8 sg_http_soc_send_req(sg_http_session_struct *session);
extern void     sg_http_soc_shut_down(sg_http_session_struct *session);
extern void     sg_http_soc_shut_down_sync(sg_http_session_struct *session);

extern SG_UINT8 sg_http_parse_url(SG_UINT8 *url,
                                  SG_UINT8 **hostname,
                                  SG_UINT16 *port,
                                  SG_UINT8 **uri,
                                  SG_UINT8 use_proxy);
extern SG_UINT8 sg_http_parse_res(SG_UINT8 *buf, SG_INT32 *len, sg_http_res_struct* http_res);
extern SG_UINT8 sg_http_parse_server_close(SG_UINT8 *buf, SG_INT32* len, sg_http_res_struct* http_res);
//extern SG_UINT8 http_parse_buf_full(SG_UINT8 *buf, SG_UINT32* len, sg_http_res_struct* http_res);
extern SG_UINT8 sg_http_get_request(SG_UINT8 **msg,
                                     SG_UINT32 *len,
                                     sg_http_req_struct *http_req,
                                     SG_UINT8 *uri,
                                     SG_UINT8 *hostname,
                                     SG_UINT16 port);
extern SG_UINT8 sg_http_get_head(SG_UINT8 *msg, sg_http_req_struct *http_req, SG_UINT8 *hostname, SG_UINT16 port);
extern void     sg_http_free_str(sg_http_string *str);
extern void     sg_http_free_req(sg_http_req_struct *http_req);
extern void     sg_http_free_res(sg_http_res_struct* http_res);
extern void     sg_http_init_req(sg_http_req_struct *http_req);
extern void     sg_http_init_res(sg_http_res_struct* http_res);
extern void     sg_http_init_str(sg_http_string *str);
extern void     sg_http_init_range(sg_range_struct *range);

//extern void     http_log(SG_UINT8 *data, SG_UINT32 len);

extern int      sg_http_init_mem(void);
extern void     sg_http_deinit_mem(void);
extern void *   sg_http_malloc(SG_INT32  size);
extern void     sg_http_mfree(void *memblock);

#endif
