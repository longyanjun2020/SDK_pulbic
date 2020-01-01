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
///@file       mdl_vdr_muxer.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MUXER_H__
#define __MDL_VDR_MUXER_H__


//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include "mdl_vdr_video.h"
#include "mdl_vdr_audio.h"
//#include "Globalvar_pi.h"
#include "mdl_vdr.h"
//#include "mdl_vdr_mx_def.h"

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

// define threshold to flush data in memory to file
#define WRITE_AUDIO   1
#define WRITE_VIDEO    2
#define WRITE_ERROR     3

//#define MP4_REC_PLUGIN_M3_14496_12  		1  // mux on M3
#define MP4_REC_PLUGIN_B3_14496_12  1  // mux on B3

#define REC_VDR_DISK_FULL_THRESHOLD  (256+128) //1024 //512
//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

typedef     S32 fnMuxFileWriteProc(int file, void * data, U32 size, U32 mode);
struct mux_write_obj;
typedef struct mux_write_obj mux_write_obj_st;

/* muxer structures */
typedef struct avmux_s
{
    U32 state;
    const U16 *name;                   /* point to filename without allocating memory to store it */
    MediaFormat_et  media_id;
    CodecID_et video_id;
    CodecID_et audio_id;

    // internal function
    int (*write_open)(struct avmux_s *inst, encdata_st *pvdo, encdata_st *pado, dtlocatorbuf_st *pMuxBuf);
    int (*write_pause)(struct avmux_s *inst);
    int (*write_packet)(struct avmux_s *inst, av_packet_st packet);
    int (*write_buffer)(struct avmux_s *inst, U8 blockMode);
    int (*write_trailer)(struct avmux_s *inst);
    int (*write_resume)(struct avmux_s *inst);
    int (*write_close)(struct avmux_s *inst, U8 bDelVdo);

    U8   writenum;          /* the number of write objects */
    U8   is_append;         /* 1: cluster write 0:normal write */
    mux_write_obj_st   *pwrite_obj; /* the information list about write objects */
    U32 cached_size;         /* not written to output file */
    U32 atom_file_size;     /* cached atom files */

    U8  storageType;          /* storage type */
    U16 storageName[20];		/* storage name */
    U32 storageTotal;       /* Total Size */
    U32 storageFree;        /* Free space */
    U16 clusterSize;        /* cluster size */

    venc_st *pvenc;                 /* alias to video codec */
    aenc_st *paenc;                 /* alias to audio codec */
    avwrite_st *pwrite;             /* alias to write object to do asynchronization write */

    void *pusrdata;              /* encode structure, will different with various codec */
}avmux_st, *pavmux_st;


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------

S32 init_muxer_plugin(avmux_st *prec_mxint, av_info_st *pav_info);


#endif // __MDL_VDR_MUXER_H__


