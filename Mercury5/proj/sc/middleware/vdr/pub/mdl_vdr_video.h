////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_video.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_VIDEO_H__
#define __MDL_VDR_VIDEO_H__


//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "mdl_vdr_common.h"
#include "mdl_vdr_api.h"
#if !defined(__SDK_SIMULATION__)
#include "mdl_camera_api_pub.h"
#include "drv_sensordriver_pub.h"
#endif
//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

#define VIDEOUNSPECIFIED        (0)

#define MP4_REC_PLUGIN_IP       1  // get video bitstream from IP codec
//#define MP4_REC_PLUGIN_VDO_FILE  1  // get video bitstream from file

#if defined(MP4_REC_PLUGIN_IP)

#if defined(__VT_3G324M__) && !defined(__SDK_SIMULATION__)
#define SW_H263I_RECORDER
#endif
#define H263I_RECORDER
//#define SW_H263I_RECORDER
//#endif

#endif

/* to turn on frame mode encode */
#if defined(VDR_WITH_15FPS_DISP_2_REC) || defined(VDR_WITH_15FPS_SEN_METHOD2) || defined(VDR_WITH_15FPS_REC_2_DISP)
#define EN_H263I_FRAME_MODE_ENCODE
#endif
#if defined(EN_H263I_FRAME_MODE_ENCODE)
/* generate frame data from display buffer in blanking time */
#if defined(VDR_WITH_15FPS_DISP_2_REC)
#define EN_DISP_2_REC_FRAME
#endif
#if defined(VDR_WITH_15FPS_REC_2_DISP)
#define EN_REC_2_DISP_FRAME
#define EN_REC_SW_BILINEAR
#endif
#endif

#if defined(__VT_3G324M__) && !defined(__SDK_SIMULATION__)
#ifdef VDR_WITH_15FPS_REC_2_DISP
#define EN_SW_REC_CHECK_BY_15FPS
#endif //VDR_WITH_15FPS_REC_2_DISP
#endif

// define fix resolutions
#define CIF_W   352
#define CIF_H   288
#define QCIF_W  176
#define QCIF_H  144
#define SUB_QCIF_W  128
#define SUB_QCIF_H  96
#define QVGA_W  320
#define QVGA_H  240

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
typedef enum
{
    MDLVDR_VIDEO_ERROR_CODE,
    MDLVDR_VIDEO_MESSAGE,
}MdlVideoRecoveryType_e;

typedef struct v_info_s {
    U32 width;                          /* frame horizontal resolution. */
    U32 height;                         /* frame vertical resolution */
    U32 frameRate;                  /* encoding rate in units of frames per second 16.16*/
    U32 qp;
    U32 db;
    U32 avgBitrate;                  /* encoding bitrate in units of bits per second, it's the average value */
    U32 maxBitrate;                  /* encoding bitrate in units of bits per second, it's the best quality value */
    U32 rateControl;                /* if it's variable, to adjust QP dynamically */
    U32 profileSetting;             /* profile to use for encoding */
    U32 levelSetting;               /* level to use for encoding */
    U32 keyFrameInterval;       /* number of frames between keyframes. A value of 0 indicates every frame is keyframe */
    U32 maxBytesPerFrame;   /* the limitation of encoded frame, assigned by encoder*/
    U32 timeScale;                  /* ticks for one second */
    U8  maceTag;
    U8  extradata_size;
    U8 *extradata;          /* some codecs generate extradata */
    void *pusrdata;
} v_info_st, *pv_info_st;

/* encoder structures */
typedef struct venc_s
{
    U32 state;
    CodecType_et codec_type;
    CodecID_et codec_id;

    //interface function
    int (*enc_open)(struct venc_s *inst, encdata_st *pin, encdata_st *pout, v_info_st *psetting, dtlocatorbuf_st *pheap);
    int (*enc_start)(struct venc_s *inst, void *pin, void *pout);
    int (*enc_pause)(struct venc_s *inst);
    int (*enc_encode)(struct venc_s *inst, av_packet_st *pencoded);
    int (*enc_resume)(struct venc_s *inst);
    int (*enc_stop)(struct venc_s *inst, av_packet_st *pencoded);
    int (*enc_close)(struct venc_s *inst, void *pin, void *pout);
    int (*enc_recovery)(struct venc_s *inst, MdlVideoRecoveryType_e type, int happen);

#if 0 // Modify
    //thread variables
    cyg_handle_t enc_thread_hdl; /* encoder thread handle */
    cyg_thread enc_thread_obj; /* encoder thread object */

    //state control flag
    cyg_sem_t start_sem; /* start semaphore */
    cyg_sem_t stop_sem; /* stop semaphore */
#endif

    U32 enc_frms;        /* encoded video frames number */
    U32 enc_skip_frms;  /* late to encode frames numbers */
    U32 enc_fail_frms;  /* failure to encode frames numbers */

    U32 totaltime;          /* summarize time of all frames */
    U32 totalsize;          /* summarize size of all frames */

    U32 duration_V_A;       /* before resume, V-totaltime - A-totaltime */

    U32 enc_stamp;      /* record time stamp of start point and it's identical to stop of last frame */

    vdr_extra_info_t enc_video_rotate_info;      /* record time stamp of start point and it's identical to stop of last frame */

     /* indicate the previous frame is skiped or not */
    U8 bprev_frm_skip;

    /*  this points to the data source */
    encdata_st enc_source;

    /*  this points to the destination */
    encdata_st enc_dest;

    v_info_st  enc_info; /* video encode structure, will different with various codec */
} venc_st, *pvenc_st;


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------

extern S32 init_video_plugin(venc_st *pInst, av_info_st *pav_info);
VideoSrcStyle_et MdlVdrGetRecordMode(u16 nMaxPreviewWidth, u16 nMaxPreviewHeight);


#endif // __MDL_VDR_VIDEO_H__

