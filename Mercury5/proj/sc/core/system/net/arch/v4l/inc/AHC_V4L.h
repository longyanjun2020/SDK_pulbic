//==============================================================================
//
//  File        : AHC_V4L.h
//  Description : INCLUDE File for the AIHC USB function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_V4L_H_
#define _AHC_V4L_H_

#include "ahc_common.h"
//#include "ahc_os.h"
//#include "os_wrap.h"
//#include "AIT4Linux.h"
//#include "videodev2.h"
//#include "v4l2-ioctl.h"
//#include "v4l2-dev.h"
struct file;
//#include "mmps_3gprecd.h"
#include "mmp_media_def.h"

//#define AIT_MAX_DEVS		4
//#define AIT_MAX_OUT_BUFS	4

void INIT_AUDIO_MODULE(struct file* pHandler);
void INIT_VIDEO_MODULE(struct file* pHandler);
AHC_BOOL vidioc_notify(MMP_M_STREAMCB_ACTION cb_action, UINT32 framesize, MMP_M_STREAM_INFO* moveinfo);
int v4l_hack_is_audio(void* v4l_buf_data);
void V4L_Drop_H264_Frame(void);

#endif
