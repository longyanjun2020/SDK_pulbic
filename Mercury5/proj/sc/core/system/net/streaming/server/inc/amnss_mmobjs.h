/*
*********************************************************************************************************
*                         AIT Multimedia Network Streaming Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: Definition of AIT Multimedia object (AMMO) classes for
*              Nodes, Pipeline and Frames
*
*/
#ifndef __AMNSS_MMOBJ_CLASSES_DEFINITIONS__
#define __AMNSS_MMOBJ_CLASSES_DEFINITIONS__

#include "amn_osal.h"
#include "amnss.h"

//sync with struct ait_queue_t::v_format
#define FORMAT_RAW_RGB24          1
#define FORMAT_RAW_UYVY           2
#define FORMAT_RAW_BGR24          3
#define FORMAT_PCM                64
#define FORMAT_ADPCM              65 //IMA ADPCM (DVI4)
#define FORMAT_MPEG4              100
#define FORMAT_MPV                102
#define FORMAT_H263               103
#define FORMAT_MPA                104
#define FORMAT_ALAW               105
//-------------------------------------
#define FORMAT_EMPTY              0
#define FORMAT_H264               201
#define FORMAT_MJPEG              202
#define FORMAT_AAC                203
#define FORMAT_MP3                204
#define FORMAT_G711               205
#define FORMAT_MJPEG2             206	//rear MJPEG

//-------------------------------------
#define RESO_1080P                100
#define RESO_720P                 101
#define RESO_VGA                  102
#define RESO_QVGA                 103

#define MAX_PIPELINE_SLOTS  8
#define MAX_NAME_LEN        64
#define MAX_NODE_INPUTS     4

//*******************************************************************************************************
#define PLCFG_SCHEDULE       0x1000   // task-scheduling for IOCTL's execution at the end-nodes
#define PLCFG_FLUSH_FRAMES   0x2000   // flush all the frames in this node's pipeline
#define PLCFG_NO_PROPAGATE   0x4000   // no traversing the IOCTL along the pipeline
#define PLCFG_ALL            0x8000   // all objects in the pipeline must server the request well
#define PLCFG_cmd(ioc)       ((ioc) & 0x0fff)
#define PLCFG_one(ioc)       ((ioc) | PLCFG_NO_PROPAGATE)    // this IOCTL will address to one node only
#define pipeline_set_running( p, running )   \
		pipeline_ioctl_r( p, PLCFG__SET_RUNNING | PLCFG_FLUSH_FRAMES | PLCFG_SCHEDULE, (void*) running )

#if 0
#define pipeline_set_running2( p, running )   \
		pipeline_ioctl_r2( p, PLCFG__SET_RUNNING | PLCFG_FLUSH_FRAMES | PLCFG_SCHEDULE, (void*) running )
#endif

ass_err node_ioctl_r( struct ammo_node *node, int ioc, void *arg );
#if 1//__inline is not supported
#define snk_set_running(node, running)\
	node_ioctl_r(node, PLCFG__SET_RUNNING | PLCFG_FLUSH_FRAMES | PLCFG_SCHEDULE, (void*) running );
#else
static ass_err snk_set_running(struct ammo_node *node, int running)
{
	return node_ioctl_r(node, PLCFG__SET_RUNNING | PLCFG_FLUSH_FRAMES | PLCFG_SCHEDULE, (void*) running );
}
#endif

#define pipeline_get_framerate( p, _fincr, _fbase )  do { \
		struct plcfg_framerate_t fr; \
		pipeline_ioctl_r( p, PLCFG_one(PLCFG__GET_FRAMERATE), &fr ); \
		_fincr = fr.fincr; \
		_fbase = fr.fbase; \
} while (0)

//*******************************************************************************************************
struct ammo_frame;
struct ammo_pipe;
struct ammo_node;
struct ammo_src_node;
struct ammo_flt_node;
struct ammo_snk_node;

typedef int (*frame_proc_ft)( struct ammo_frame *f, void *node, struct ammo_pipe *p_from );
typedef int (*frame_destroy_ft)( struct ammo_frame *f, struct ammo_src_node *node );
typedef int (*pipeline_ioctl_ft)( struct ammo_node *n, int ioc, void *arg );

// Definitions of AMMO Node: Source / Filter / Sink
//*******************************************************************************************************

#define AMMO_FLAG__RUNNING           0x1
#define AMMO_FLAG__LINK              0x2 ///< This is a link to other directory or file.
#define AMMO_FLAG__TRANSCODE         0x4
//#define AMMO_FLAG__xxx               2

#define is_node_running(n)      (cast_Node(n)->flags & AMMO_FLAG__RUNNING)
#define is_node_transcode(n)    (cast_Node(n)->flags & (AMMO_FLAG__LINK | AMMO_FLAG__TRANSCODE))
#if 0
#define STRUCT_AMMO_BASEOBJ                                                     \
	u8_t  ammo_type;                   /* AMMO_TYPE__NODE_xxx */                \

#endif

#define STRUCT_AMMO_NODE                                                        \
	struct list_head     link;                                                  \
	char   name[MAX_NAME_LEN];                                                  \
	struct ammo_pipeline *pl;                    /* Node's OUTPUT */            \
	struct ammo_pipe *inputs[MAX_NODE_INPUTS];   /* Node's INPUT */             \
	frame_proc_ft proc_frame;          /* process frames per NODE's function */ \
	pipeline_ioctl_ft pl_ioctl;        /* ioctl per NODE, along pipeline */     \
	u8_t  node_type;                   /* AMMO_TYPE__NODE_xxx */                \
	u8_t  n_inputs;                    /* number of INPUTs */                   \
	u8_t  flags;                       /* was: running */

// Virtual Base Class of AMMO Node
struct ammo_node { STRUCT_AMMO_NODE };

struct ammo_src_node {
	STRUCT_AMMO_NODE
	s8_t   device_id;    // the Hardware device's unique ID associating with this NODE

	u16_t  total_frames;     // total number of frames in this Node
	u16_t  nr_free_frames;   // current number of free-frames in this Node
	uint_t max_frame_size;   // maximum probable frame size from this Source Node
	struct list_head free_frame_list;
	frame_destroy_ft destroy_frame;
	osal_mutex_t lock_frames;
};

struct ammo_flt_node {
	STRUCT_AMMO_NODE
};

struct ammo_snk_node {
	STRUCT_AMMO_NODE
};

#define cast_Node(n)       ((struct ammo_node*)(n))
#define cast_SrcNode(n)    ((struct ammo_src_node*)(n))
#define cast_SnkNode(n)    ((struct ammo_snk_node*)(n))
#define cast_FltNode(n)    ((struct ammo_flt_node*)(n))
//#define cast_MyNode(n)   ((struct srcNode_XxxYyy *)(n))


// Definitions of AMMO Stream Pipe & Pipeline
//*******************************************************************************************************
#define AMMO_PIPE_FLAG__SDP_READY     1

struct ammo_pipe {
	struct list_head     link;
	struct ammo_node     *to_node;    // the NODE this stream pipe is connected to
	struct ammo_pipeline *from_pl;    // the PIPELINE this pipe is connected from
	void   *data;                     // used in RTSP to associate with <struct rtp_media>
	u8_t   index;
	u8_t   flags;
};

#define AMMO_PIPELINE_FLAG__SHORTCUT  1
struct ammo_pipeline {
	struct list_head link;

	u8_t   flags;
	u8_t   format;
	u8_t   n_TO_list;
	u8_t   slot_head;
	u8_t   slot_tail;

	struct ammo_node *from_node;     // the NODE from which this pipeline is connected
	struct list_head  pipe_TO_list;  // all the TO-stream-pipes connected to each destination Node
	struct ammo_frame *slots[MAX_PIPELINE_SLOTS];

	char name[MAX_NAME_LEN];         // the pipeline's name == Node's output-pin name
	osal_mutex_t mutex;
};

#define pipeline_slot_advance(s)  do { \
	if (++(s) >= MAX_PIPELINE_SLOTS) s = 0; \
} while(0)

#define pipeline_slot_is_full(pl)  \
	((pl->slot_tail + 1 - pl->slot_head + MAX_PIPELINE_SLOTS) % MAX_PIPELINE_SLOTS) == 0



//*******************************************************************************************************
#define AMMO_FRAME_BUF_UNUSED  0xffff

struct ammo_frame
{
	struct list_head link;             // linkage only applied when the Frame is free
	struct ammo_src_node *owner;       // the Source Node this frame belongs to
	osal_mutex_t mutex;                // only used to lock the ref_count
	struct ammo_pipeline *pl;          // the pipeline this Frame resides within

	u32_t  size; //size of d. if size == 0, d is a pointer, otherwise, d is the first byte of data. (piggyback)
	u32_t  length;
	u32_t  timestamp;
	u16_t  width;
	u16_t  height;
	u16_t  fps;
	u16_t  buf_idx;                    // struct v4l2_buffer::index
	u8_t   ref_count;
	u8_t   format;
	u8_t   key;
	u8_t   *d;
	u8_t   track;						// the track NO. is the order of Ass.SnkNode.?.Attr.Inputs
										// It should be like as Ass.SnkNode.?.Attr.Inputs = "VIDEO,AUDIO"
										// VIDEO is 0, AUDIO is 1
	void   *dbg;
};

//*******************************************************************************************************
#define ammo_set_resolution( _node, _reso ) do { \
		if (! strcasecmp( _reso, "1080P" )) { \
			cast_MyNode(_node)->width = 1920; \
			cast_MyNode(_node)->height = 1080; \
		} \
		else if (! strcasecmp( _reso, "720P" )) { \
			cast_MyNode(_node)->width = 1280; \
			cast_MyNode(_node)->height = 720; \
		} \
		else if (! strcasecmp( _reso, "VGA" )) { \
			cast_MyNode(_node)->width = 640; \
			cast_MyNode(_node)->height = 480; \
		} \
		else if (! strcasecmp( _reso, "QVGA" )) { \
			cast_MyNode(_node)->width = 160; \
			cast_MyNode(_node)->height = 120; \
		} \
		else { \
			osal_dprint(ERR, "SimFile: unsupported resolution: %s", _reso); \
			return -1; \
		} \
} while (0)

//*******************************************************************************************************
struct meter {
	int started;
	int downstream;
	struct timeval last_check;
	int rate;
	int ticks;
	double slip;
	double avg_slip;
	int precomp;
	int correction_rate;
	int corrected;
};

//debug time stamp
enum ammo_dbg_type {
    AMMO_DBG_AUDIO,
    AMMO_DBG_VIDEO,
    AMMO_DBG_MAX
};

#define AMMO_DEBUG_TS (0)//debug time stamp

#if AMMO_DEBUG_TS
void ammo_dbg_set_ts(enum ammo_dbg_type stream, unsigned int time_stamp);
int ammo_dbg_get_ts_diff(void);
void ammo_dbg_trace_ts(void);
#else
#define ammo_dbg_set_ts(stream, ts)
#define ammo_dbg_get_ts_diff() (-1)
#define ammo_dbg_trace_ts()
#endif

#endif
