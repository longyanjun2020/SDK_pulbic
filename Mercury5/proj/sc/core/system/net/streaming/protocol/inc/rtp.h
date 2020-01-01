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
#ifndef __RTP_H___
#define __RTP_H___

//*******************************************************************************************************
/* These should probably be an enum */
#define	RTP_TRANS_UDP	1
#define RTP_TRANS_INTER	2

#define DUMP_RTP 0
#if DUMP_RTP
int dump_rtp_packets(const struct msghdr *msg);
#else
#define dump_rtp_packets(msg)
#endif

//*******************************************************************************************************
struct rtp_endpoint;

//*******************************************************************************************************
typedef int (*rtp_media_get_sdp_func)( char *dest, int len, int payload, int port, void *d );
typedef int (*rtp_media_get_payload_func)( int payload, void *d );
typedef int (*rtp_media_get_time_func) (unsigned int* time, void *d );
typedef int (*rtp_media_frame_func)( struct ammo_frame *f, void *d );
typedef int (*rtp_media_send_func)( struct rtp_endpoint *ep, void *d );
typedef int (*rtp_media_close_func)( void *d );

struct rtp_media {
	rtp_media_get_sdp_func     get_sdp;
	rtp_media_get_payload_func get_payload;
	rtp_media_get_time_func    get_time;
	rtp_media_frame_func       proc_frame;
	rtp_media_send_func        send_frame;
	rtp_media_close_func       close_media;
	void *private;
};

struct rtp_endpoint {
	struct amn_session_t *session;
	int payload;
	int max_data_size;
	unsigned int ssrc;
	unsigned int start_timestamp;
	unsigned int last_timestamp;
	int seqnum;
	int packet_count;
	int octet_count;
	struct ammo_evmsg *rtcp_send_event;
	int force_rtcp;
	struct timeval last_rtcp_recv;
	int trans_type;
	union {
		struct {
			char sdp_addr[48];
			int sdp_port;
			int rtp_fd;
			struct ammo_evmsg *rtp_event;
			int rtcp_fd;
			struct ammo_evmsg *rtcp_event;
			struct in_addr dest_addr; //for r7770
		} udp;
		struct {
			struct resp_message_t *conn;
			int rtp_chan;
			int rtcp_chan;
		} inter;
	} trans;
};

//frame dropping simulation
struct FDS{
	int current_frame;
	int drop_this_frame;
};
extern struct FDS fds;
////////////////////////////////////////////////////////////////////////////////
struct rtp_media *new_rtp_media( rtp_media_get_sdp_func get_sdp,
	rtp_media_get_payload_func get_payload, rtp_media_get_time_func get_time,
	rtp_media_frame_func proc_frame,
	rtp_media_send_func send_frame, rtp_media_close_func close_media, void *private );
struct rtp_media *new_rtp_media_mpeg4(void);
struct rtp_media *new_rtp_media_mpv(void);
struct rtp_media *new_rtp_media_h263_stream( struct ammo_pipe *p );
struct rtp_media *new_rtp_media_jpeg_stream( struct ammo_pipe *p );
struct rtp_media *new_rtp_media_mpeg4gen_aachbr(void);
struct rtp_media *new_rtp_media_mpa(void);
struct rtp_media *new_rtp_media_h264(void);
struct rtp_media *new_rtp_media_rawaudio_stream( struct ammo_pipe *p );
////////////////////////////////////////////////////////////////////////////////

#endif
