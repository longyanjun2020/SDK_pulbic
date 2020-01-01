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
///@file       mdl_vdr_mx_mov.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_MOV_H__
#define __MDL_VDR_MX_MOV_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "mm_types.h"
#include "mdl_vdr_mx_def.h"

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------
#if defined(__SDK_SIMULATION__)
#define ENABLE_2PHASE_META_WRITE            0
#else
#define ENABLE_2PHASE_META_WRITE            1
#endif
#define MDL_VDR_ATM_STSZ_AUDIO_EN


#define MP4_CODEC_ID_UNKNOWN	0
#define MP4_CODEC_ID_MP4		        0x01
#define MP4_CODEC_ID_H263		        0x02
#define MP4_CODEC_ID_AMR_NB		0x03
#define MP4_CODEC_ID_AMR_WB          0x04
#define MP4_CODEC_ID_AAC                0x05
#define MP4_CODEC_ID_MP3                0x06
#define MP4_CODEC_ID_WAV                0x07


#define MP4_CODEC_TYPE_VIDEO        0x01
#define MP4_CODEC_TYPE_AUDIO        0x02

#define MP4_MODE_MP4                        0x00
#define MP4_MODE_3GP                        0x01

#define MP4_PACKET_START                 0x01
#define MP4_PACKET_MORE                 0x02
#define MP4_PACKET_END                  0x03
#define MP4_PACKET_ERR                  0x04

#define MP4_RENDER_TYPE_MASK    0x7F
#define MP4_RENDER_VIDEO    0x01
#define MP4_RENDER_AUDIO    0x02
#define MP4_RENDER_CACHE    0x03
#define MP4_RENDER_ERROR    0x80
//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
/* define information about items to be written */
typedef struct mux_write_obj
{
	U16        *filename;
	FILE_HANDLE file;
    U32             mode;
    U32             prealloc_size;
    U32             write_size;
}mux_write_obj_st, *pmux_write_obj_st;

/* define object ID of ring buffer information */
typedef enum
{
    AV_WRT_OBJECT_VIDEO = 0,

    AV_WRT_OBJECT_ATOM_START,

    AV_WRT_OBJECT_V_STSZ = AV_WRT_OBJECT_ATOM_START,
    AV_WRT_OBJECT_V_STCO,
    AV_WRT_OBJECT_V_STTS,
    AV_WRT_OBJECT_V_STSS,

    AV_WRT_OBJECT_A_STCO,
#if defined(MDL_VDR_ATM_STSZ_AUDIO_EN)
    AV_WRT_OBJECT_A_STSZ,
#endif

#if ENABLE_2PHASE_META_WRITE
    AV_WRT_OBJECT_ATOM_ALL,
#endif // ENABLE_2PHASE_META_WRITE

    AV_WRT_OBJECT_ATOM_END,

    AV_WRT_OBJECT_NUM = AV_WRT_OBJECT_ATOM_END,              /* total number of objects */

    AV_WRT_OBJECT_INVALID
}WriteObjectID_e;

typedef struct tagMP4VInfo
{
	u32 type;	// MP4MDTYPE_M4V or MP4MDTYPE_H263

	u32 frameWidth;
	u32 frameHeight;
	u32 sampleDuration;
	u32 sampleSize;
	u32 profile;
	u32 level;
	u32 timeScale;
	u32 keyFrameInterval;
        u8 maceTag;
} MP4VInfo;

typedef struct tagMP4AInfo
{
	u32 type;	// MP4MDTYPE_AMR or MP4MDTYPE_UNKNOWN

	u32 sampleDuration;
	u32 sampleSize;
	u32 profile;
	u32 level;
	u32 timeScale;
} MP4AInfo;

typedef struct tagMP4AVPacket
{
	u32   track_id;       // index to the stream
    u8    *pBytes;        /* the address to the audio/video data */
	u32   numBytes;
	u32   duration;
	u32   render_offset;  /* for B-VOP, pts is not identical to dts */
	u8    isSyncSample;
	u8    status;
	u8 reserved[2];
}MP4AVPacket;

typedef struct tagMP4AVStream
{
	u32 db;
	u32 maxBitrate;
	u32 avgBitrate;
	u32 extraSize;
    u8 *extraData;
}MP4AVStream;

typedef volatile struct tagMP4MuxerInst
{
    u8 *pOutputFileName;

    u32    u32MdatPos;     /* start position of data of mdat */
    U32    u32CachedMeta;     /* The meta not be written to A/V file */
    U32    u32CachedPool;  /* Video, Audio, and Write Cache buffer */

    // for video information
    u32    frameWidth;
    u32    frameHeight;

    // for audio information
#define TRACK_VIDEO_INDEX 0
#define TRACK_AUDIO_INDEX 1
#define TRACK_MP4_NUM       2
    u32  trackIds[TRACK_MP4_NUM];  /* video -> trackIds[0], audio -> tackIds[1] */

    S32 s32MuxErrRtl;  /* keep the error return code */

    void*  mp4File;
    void    *priv_data;
} MP4MuxerInst;

//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------
int MP4Muxer_Open(void **ppInstm, uint8_t format, void *pusrdata);
int MP4Muxer_Write_Header(void *pMuxInst);
int MP4Muxer_SetVInfo(void *pHandle, void *pInfo, int nInfoSize);
int MP4Muxer_SetAInfo(void *pHandle, void *pInfo, int nInfoSize);
int MP4Muxer_Write_Packet(void *pHandle, void *av_packet);
int MP4Muxer_Render2File(void *pHandle, U8 mode);
int MP4Muxer_Update_Info(void *pHandle, MP4TrackId trackId, void *info);
int MP4Muxer_Stop(void *pHandle);
int MP4Muxer_Close(void *pHandle);
#endif

