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
#ifndef __AMNSS_H__
#define __AMNSS_H__

//*******************************************************************************************************
#define AMMO_TYPE__NODE_SOURCE       0
#define AMMO_TYPE__NODE_FILTER       1
#define AMMO_TYPE__NODE_SINK         2
#define AMMO_TYPE__PIPELINE          3
#define AMMO_TYPE__LIST_COLLECTION   4
#define AMMO_TYPE__NODE_ANY          99

#define PLCFG__SET_RUNNING        1
#define PLCFG__RESTART_KEYFRAME   2   // request to regenerate I-frame, instead of reset encoder
#define PLCFG__SET_FRAMERATE      3
#define PLCFG__GET_FRAMERATE      4
#define PLCFG__SET_BITRATE        5
#define PLCFG__SET_RESOLUTION     6
#define PLCFG__GET_SDP_META       7   // get H264 SPS/IPS frames
#define PLCFG__SET_FRC            8   // Set frame rate conversion
#define PLCFG__GET_FRC            9   // Get frame rate conversion
#define PLCFG__PAUSE              10
#define PLCFG__RESUME             11
#define PLCFG__SET_POSITION       12
#define PLCFG__GET_POSITION       13
#define PLCFG__SET_AUDIO_FORMAT   20  // Set audio format
#define PLCFG__GET_AUDIO_FORMAT   21  // Get audio format

struct plcfg_framerate_t {
	int  fincr;
	int  fbase;
};

struct plcfg_frc_t {//set to 0 as don't care, auto or ignored.
    int inx1000; //input frame rate * 1000. e.g. 30000 == 30FPS, 29970 == 29.97FPS
    int outx1000; //output frame rate * 1000
};

struct ammo_node;
typedef struct ammo_node *ammo_node;
//*******************************************************************************************************
#ifndef __AMN_OS_LINUX__
// in amnss_ucos.c
u32_t random(void);
void avChurnRand(char *randData, u32_t randLen);
void aitstreamer_run(char *src_name);
int  aitstreamer_use(void);
int  aitstreamer_free(void);
bool aitstreamer_is_ready(void);
bool aitstreamer_has_stream_control(void);

//==== stream control features ====
//Turn off all SC_REPORT feature would turn off Stream Control features.

/** Report data transmission stress to UI for controlling streaming.
  Recommended value: 1 */
#define SC_REPORT_TX (1)
/** Report data congestion event to UI for controlling streaming.
  Recommended value: 0. Because in current implementation,
  the V4L OS queue and AQUE is not flexible enough for av4.
  Reporting congestion needs to change V4L_VideoBuf_GetFrames() to avoid overflows being too often.
  Changing V4L_VideoBuf_GetFrames() also cause OS MQUEUE overflows and makes corrupted streaming video.*/
#define SC_REPORT_CONGESTION (0)
/** This is still buggy along with SC_REPORT_CONGESTION option and is a experimental feature.
 *  Recommended value: 0
 */
#define SC_CHANGE_RES (0)

int aitstreamer_report_tx(short stress);
int aitstreamer_report_congestion(short congestion);
int aitstreamer_reset_report(short reset_type);

void aitupnp_init(void);

#include "mmpf_timer.h"
#define stopwatch_start(x) MMPF_Stopwatch_Start(x)
#define stopwatch_stop(x) MMPF_Stopwatch_Stop(x)
#define	SLOW_RATE	20
extern unsigned int	_sndavg;
extern MMPF_STOPWATCH_HANDLE stopwatch0;
extern MMPF_STOPWATCH_HANDLE stopwatch1;

#endif

//build the node graph and start tasks
void aitstreamer_start(void);
//init AIT streaming server infrastructure
int aitstreamer_init(void);

//void pipeline_ioctl_f( struct ammo_node *node, int ioc, void *arg );
//void pipeline_ioctl_r( struct ammo_pipe *p, int ioc, void *arg );

/** Find the node pointer of the node as handler for later usage.
 *
 * @param type The type of of target. AMMO_TYPE__NODE_xxxx are supported.
 * @param name The name of the node or pipeline. The name should be in the node config files.
 * @param len The length of the name. Set -1 to calculate the length inside.
 * @return The node pointer. NULL if the node is not found or something wrong inside.
 */
struct ammo_node* node_find_name( int type, char *name, int len );

typedef enum aitstramer_err {
    ASS_ERR_NONE,                ///<no error
    ASS_ERR_UNSUPPORTED_SETTING, ///<The setting is not supported in the source node
    ASS_ERR_PARAM,               ///<The parameter passing to the function is invalid
    ASS_ERR_TIME_OUT,
    ASS_ERR_MAX
}ass_err;

//set the single node attribute
ass_err node_set_attr(struct ammo_node* const node, int setting, void* param);

//set the whole pipeline attribute from the source node. (forwarding)
//Only report error if NO object in the pipeline that is unable to handle the request.
ass_err pipeline_set_node_attr(struct ammo_node* const node, int setting, void* param);

//set the whole pipeline attribute from the source node. (forwarding)
//Stop and report error if any object in the pipeline that is unable to handle the request.
ass_err pipeline_set_node_attr_all(struct ammo_node* const node, int setting, void* param);

//other proposed interfaces.
//ass_err pipeline_set_pipe_attr(struct ammo_pipe* const pipe, int setting, void* param);
//ass_err pipeline_set_pipe_attr_all(struct ammo_pipe* const pipe, int setting, void* param);

#endif
