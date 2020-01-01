/*
*********************************************************************************************************
*                         AIT Multimedia Network Streaming Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: 
*
*/

#ifndef __AMNSS_NETWORK_PROTOCOL_DEFINITIONS__
#define __AMNSS_NETWORK_PROTOCOL_DEFINITIONS__

#define	MAX_TRACKS	              2    /* RTSP/RTP media channels */
#define MAX_INTERLEAVE_CHANNELS   8
#define MAX_HEADER_FIELDS         32
#define MAX_RTSP_PATH     64      // 256

#ifdef __AIT_DEPRECATE_OLD_PROTO_CODES__
#define CONN_PROTO_START	0
#define CONN_PROTO_RTSP		1
#define CONN_PROTO_HTTP		2
#define CONN_PROTO_SIP		3
#endif


/* There's probably a better place to put these... */
#define PUT_16(p,v)  ((p)[0]=((v)>>8)&0xff,(p)[1]=(v)&0xff)
#define PUT_32(p,v)  ((p)[0]=((v)>>24)&0xff,(p)[1]=((v)>>16)&0xff,(p)[2]=((v)>>8)&0xff,(p)[3]=(v)&0xff)
#define GET_16(p)   (((p)[0]<<8)|(p)[1])
#define GET_32(p)   (((p)[0]<<24)|((p)[1]<<16)|((p)[2]<<8)|(p)[3])

//*******************************************************************************************************
/* 802.1D priority defines */
#define PRIO_8021D_NONE         2       /* None = - */
#define PRIO_8021D_BK           1       /* BK - Background */
#define PRIO_8021D_BE           0       /* BE - Best-effort */
#define PRIO_8021D_EE           3       /* EE - Excellent-effort */
#define PRIO_8021D_CL           4       /* CL - Controlled Load */
#define PRIO_8021D_VI           5       /* Vi - Video */
#define PRIO_8021D_VO           6       /* Vo - Voice */
#define PRIO_8021D_NC           7       /* NC - Network Control */

#define IPV4_TOS_PREC_MASK      0xe0    /* Historical precedence mask */
#define IPV4_TOS_PREC_SHIFT     5       /* Historical precedence shift */

#define IPV4_TOS_LOWDELAY       0x10    /* Lowest delay requested */
#define IPV4_TOS_THROUGHPUT     0x8     /* Best throughput requested */
#define IPV4_TOS_RELIABILITY    0x4     /* Most reliable delivery requested */


//*******************************************************************************************************
struct conn;
struct resp_message_t;
struct pmsg;

//*******************************************************************************************************
typedef struct {
	int		b_rtsptcp; 
	int		b_keepalive;
	u32_t	i_starttime;
	u32_t	i_nexttime;
} KEEPALIVE;
int rtsp_keepalive(KEEPALIVE *pk);
int rtsp_keepalive_check(KEEPALIVE *pk);
void rtsp_keepalive_stop(KEEPALIVE *pk);

#define RTSP_SESS_FLAG__PLAYING   0x1
#define RTSP_SESS_FLAG__PAUSING   0x2
struct rtsp_session_t {
	u8_t  flags;
	char  addr[64];
	KEEPALIVE	kal;
	struct rtp_endpoint *ep[MAX_TRACKS];
};

struct udp_session_t {
	u8_t  flags;
	char  addr[64];
	KEEPALIVE	kal;
	struct udp_endpoint *ep[MAX_TRACKS];
};

//*******************************************************************************************************
//  PROTOCOL ATTRIBUTES IN AMMO
//*******************************************************************************************************
struct ammo_rtsp {
	char   realm[MAX_NAME_LEN];
	char   username[MAX_NAME_LEN];
	char   password[MAX_NAME_LEN];
};
struct snkNode_liveRTSP;
struct ammo_rtsp* get_ammo_rtsp(struct snkNode_liveRTSP *rtsp_node);

struct snkNode_liveHTTP;
struct http_stream_session_t {
	struct resp_message_t *resp;
};
struct snkNode_liveUDP;

//*******************************************************************************************************
#ifdef __AIT_DEPRECATE_OLD_PROTO_CODES__
struct req {
	struct conn *conn;
	struct pmsg *req;
	struct pmsg *resp;
};

struct conn {
	struct conn *next;
	struct conn *prev;
	int fd;
	int second_fd; /* QuickTime uses two TCP connections for tunneling */
	struct sockaddr_in client_addr;
	struct ammo_evmsg *read_event;
	struct ammo_evmsg *second_read_event; /* for second_fd */
	struct ammo_evmsg *write_event;
	int proto;
	char http_tunnel_cookie[128]; /* used to identify QuickTime tunnels */
	int base64_count; /* QuickTime uses base64 when tunneling over HTTP */
	char req_buf[4096];
	int req_len;
	struct req *req_list;
	char send_buf[65536];
	int send_buf_r;
	int send_buf_w;
	int drop_after;
	void *proto_state;
};

//*******************************************************************************************************
struct hdrf {
	char *name;
	char *value;
};

struct pmsg {
	char *msg;
	int max_len;
	int msg_len;
	struct hdrf fields[MAX_HEADER_FIELDS];
	int header_count;
	enum { PMSG_REQ, PMSG_RESP } type;
	char *proto_id;
	union {
		struct {
			char *method;
			char *uri;
		} req;
		struct {
			int code;
			char *reason;
		} stat;
	} sl;
};
#endif

//*******************************************************************************************************
#endif

