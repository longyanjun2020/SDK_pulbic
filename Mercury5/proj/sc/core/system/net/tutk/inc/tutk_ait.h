/*
 * TUTK_AIT
 */
#include "amnss_mmobjs.h"
//#include "protocol.h"
//#include "AVFRAMEINFO.h"
//#include "AVAPIs.h"
//#include "IOTCAPIs.h"

struct tutk_endpoint {
	void	*context;	// tutk session
};

char print_tutk_error(int ret);
void dbg_v_frame_get(void);
void dbg_v_frame_sent(unsigned int frm_len, int _smax);

typedef int (*tutk_media_get_sdp_func)( char *dest, int len, int payload, int port, void *d );
typedef int (*tutk_media_get_payload_func)( int payload, void *d );
typedef int (*tutk_media_frame_func)( struct ammo_frame *f, void *d );
typedef int (*tutk_media_send_func)( struct tutk_endpoint *ep, void *d );
typedef int (*tutk_media_open_func)( void *d );

struct tutk_media {
	//tutk_media_get_sdp_func     get_sdp;
	//tutk_media_get_payload_func get_payload;
	tutk_media_frame_func       proc_frame;
	tutk_media_send_func        send_frame;
	tutk_media_open_func        open_media;
	void *private;
};

struct tutk_media *new_tutk_media_h264_stream( struct ammo_pipe *p );
struct tutk_media *new_tutk_media_jpeg_stream( struct ammo_pipe *p );
struct tutk_media *new_tutk_media_pcm_stream( struct ammo_pipe *p );
struct tutk_media *new_tutk_media(tutk_media_get_sdp_func get_sdp,
								  tutk_media_get_payload_func get_payload,
								  tutk_media_frame_func proc_frame,
								  tutk_media_send_func send_frame,
								  tutk_media_open_func open_media,
								  void *private);

typedef	void*	STREAM_HANDLE;
STREAM_HANDLE tutk_stream_open(char *path, void *context);
void tutk_stream_close(STREAM_HANDLE handle);
int tutk_get_avidx(void *tcxt);
int tutk_detach_stream(void* tcxt);
int tutk_get_online_count(void);
int tutk_audio_enabled(void *tcxt, int avidx);
void* tutk_enum_avidx(void* tcxt, int *pidx);
//
struct amn_session_t *liveTUTK_open(char *path, void *n, void *context);
struct snkNode_liveTUTK;
int liveTUTK_describe( struct amn_session_t *sess, struct snkNode_liveTUTK *loc, char *path );
void liveTUTK_play( struct amn_session_t *s, float *start );
int liveTUTK_close(struct amn_session_t *session);
