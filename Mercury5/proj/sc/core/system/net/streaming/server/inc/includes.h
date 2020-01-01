/*
*********************************************************************************************************
*                         AIT Multimedia Network Streaming Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: A common include header of all functions prototypes.
*
*/

#ifndef __AMNSS_FUNC_PROTOTYPE_INCLUDES__
#define __AMNSS_FUNC_PROTOTYPE_INCLUDES__

/////////////// CONFIG DEFINITIONS /////////////////////////
// #define __AMN_OS_LINUX__
// #define __AMNSS_DEBUG__

#define RTP_SEGMENT_MTU   1400


////////////////////////////////////////////////////////////////////////////////
#include "amn_osal.h"
#include "amn_event.h"
#include "amnss_mmobjs.h"
#include "protocol.h"
#include "net_serv.h"

// Functional prototypes
//*******************************************************************************************************
#if 0
INLINE void uyvy2yuy2 (unsigned char *src, unsigned char *dest, int NumPixels);
INLINE void yuv2yuy2 (unsigned char *src, unsigned char *dest, int NumPixels);
INLINE void y41p2yuyv (unsigned char *src, unsigned char *dest, int NumPixels);
INLINE void iyu12yuy2 (unsigned char *src, unsigned char *dest, int NumPixels);
INLINE void iyu22yuy2 (unsigned char *src, unsigned char *dest, int NumPixels);
INLINE void y2yuy2 (unsigned char *src, unsigned char *dest, int NumPixels);
INLINE void rgb2yuy2 (char *RGB, char *YUV, int NumPixels);
INLINE void uyvy2rgb (char *YUV, char *RGB, int NumPixels);
INLINE void yuy22rgb (char *YUV, char *RGB, int NumPixels);
INLINE void iyu12rgb (char *YUV, char *RGB, int NumPixels);
INLINE void iyu22rgb (char *YUV, char *RGB, int NumPixels);
INLINE void y2rgb (char *YUV, char *RGB, int NumPixels);
#endif


////////////////////////////////////////////////////////////////////////////////
u8_t *h264_scan_startcode(u8_t *buf, int len);

////////////////////////////////////////////////////////////////////////////////
#ifdef __AIT_DEPRECATE_OLD_PROTO_CODES__
char *get_header( struct pmsg *msg, char *name );
int add_header( struct pmsg *msg, char *name, char *value );
int add_header_printf( struct pmsg *msg, char *name, char *fmt, ... );
int copy_headers( struct pmsg *dest, struct pmsg *src, char *name );
int parse_pmsg( struct pmsg *msg );
struct pmsg *new_pmsg( int size );
void free_pmsg( struct pmsg *msg );
char *add_pmsg_string( struct pmsg *msg, char *s );
#endif

////////////////////////////////////////////////////////////////////////////////
int snkRTSP_is_transcode(struct snkNode_liveRTSP *snk_rtsp);
unsigned int snkRTSP_get_last_sent_time(struct amn_session_t *s);

////////////////////////////////////////////////////////////////////////////////
int liveRTSP_get_sdp( struct amn_session_t *s, char *dest, size_t *len, char *path, unsigned int duration );
int liveRTSP_describe( struct amn_session_t *sess, struct snkNode_liveRTSP *loc, char *path );
int liveRTSP_setup( struct amn_session_t *s, int t );
void liveRTSP_play( struct amn_session_t *s, float *start );
int liveRTSP_is_pausing(struct amn_session_t *s);
int liveRTSP_pause( struct amn_session_t *s );
int liveRTSP_resume( struct amn_session_t *s );
struct amn_session_t *liveRTSP_open( char *path, void *n, char* foreign_addr );

////////////////////////////////////////////////////////////////////////////////
int udp_handle_Play( struct resp_message_t *resp );
int udp_handle_TEARDOWN( struct resp_message_t *resp );

////////////////////////////////////////////////////////////////////////////////
void create_digest_nonce( char *nonce );
int check_digest_response( struct resp_message_t *resp, char *realm, char *username, char *password );

////////////////////////////////////////////////////////////////////////////////
struct rtp_endpoint *new_rtp_endpoint( int payload );
int connect_udp_endpoint( struct rtp_endpoint *ep,
		struct in_addr dest_ip, int dest_port, int *our_port );
int avail_send_buf( struct resp_message_t *c );
int send_data( struct resp_message_t *c, char *d, int len );
int tcp_send_pmsg( struct resp_message_t *c, struct pmsg *msg, int len );
void connect_interleaved_endpoint( struct rtp_endpoint *ep,
		struct resp_message_t *conn, int rtp_chan, int rtcp_chan );
void http_conn_disconnect( struct resp_message_t *c );
void interleave_recv_rtcp( struct rtp_endpoint *ep, char *d, int len );
void del_rtp_endpoint( struct rtp_endpoint *ep );
void update_rtp_timestamp( struct rtp_endpoint *ep, int time_increment );
int send_rtp_packet( struct rtp_endpoint *ep, struct iovec *v, int count,
			unsigned int timestamp, int marker );

void rtsp_conn_disconnect( struct resp_message_t *c );
void interleave_disconnect( struct resp_message_t *c, int chan );
int interleave_recv( struct resp_message_t *c, int chan, char *d, int len );
int interleave_send( struct resp_message_t *c, int chan, struct iovec *v, int count );

////////////////////////////////////////////////////////////////////////////////
void pipeline_pumper_start(struct ammo_evmsg *m, void *n);  // the Engine of PIPELINE
ass_err pipeline_ioctl_f( struct ammo_node *node, int ioc, void *arg );
ass_err pipeline_ioctl_r( struct ammo_pipe *p, int ioc, void *arg );
ass_err node_ioctl_r( struct ammo_node *node, int ioc, void *arg );
ass_err node_ioctl_f( struct ammo_node *node, int ioc, void *arg );
void node_create_framelist(struct ammo_src_node *node, int nFrames, uint_t szFrame, frame_destroy_ft destroy_frame );
struct ammo_pipe *node_add_input( struct ammo_node *node, char *name, int *formats, int format_count );
struct ammo_src_node *node_new_src( char *name, int szNode, frame_proc_ft f, pipeline_ioctl_ft ioctl_cb );
struct ammo_flt_node *node_new_flt( char *name, int szNode, frame_proc_ft f, pipeline_ioctl_ft ioctl_cb );
struct ammo_snk_node *node_new_snk( char *name, int szNode, frame_proc_ft f, pipeline_ioctl_ft ioctl_cb );
struct ammo_pipeline *pipeline_new( struct ammo_node *n, char *name, int format, int flags );
void dbg_dump_nodes(void);
void dbg_dump_pipelines(void);

////////////////////////////////////////////////////////////////////////////////
osal_thread_t thread_message_handler(void *arg);
osal_thread_t thread_select_loop(void *arg);

////////////////////////////////////////////////////////////////////////////////
void register_pipeline_graph_handlers( int ammo_type, char *type_name, void* (*graph_node)(), int (*graph_attr)() );
void start_pipeline_graph_parsing(void);
int config_rtprange( int rtp1, int rtp2 );

struct amn_session_t *liveUDP_open( char *path, void *n, char* foreign_addr );
void node_p00udp_init(void);
struct udp_media *new_udp_media_pjpeg_stream( struct ammo_pipe *p );
int connect_udp2_endpoint( struct udp_endpoint *ep,
		struct in_addr dest_ip, int dest_port, int *our_port );
int liveUDP_setup( struct amn_session_t *s, int t );
void liveUDP_play( struct amn_session_t *s, double *start );
void del_udp_endpoint( struct udp_endpoint *ep );
struct udp_endpoint *new_udp_endpoint( int payload );
//G711
struct udp_media *new_udp_media_g711_stream( struct ammo_pipe *p);
#endif
