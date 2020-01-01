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
///@file       mdl_vdr_mx.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_H__
#define __MDL_VDR_MX_H__


#if defined(MP4REC_PLUGIN_EN)


//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

//#include "Mp4def.h"


//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Macro Definition
//-----------------------------------------------------------------------------

#define MP4_CODEC_ID_UNKNOWN	0
#define MP4_CODEC_ID_MP4		        0x01
#define MP4_CODEC_ID_H263		        0x02
#define MP4_CODEC_ID_AMR_NB		0x03
#define MP4_CODEC_ID_AMR_WB          0x04
#define MP4_CODEC_ID_AAC                0x05
#define MP4_CODEC_ID_MP3                0x06


#define MP4_CODEC_TYPE_VIDEO        0x01
#define MP4_CODEC_TYPE_AUDIO        0x02

#define MP4_MODE_MP4                        0x00
#define MP4_MODE_3GP                        0x01

#define MP4_PACKET_START                 0x01
#define MP4_PACKET_MORE                 0x02
#define MP4_PACKET_END                  0x03
#define MP4_PACKET_ERR                  0x04

#define MP4_RENDER_VIDEO    0x01
#define MP4_RENDER_AUDIO    0x02
#define MP4_RENDER_CACHE    0x03

// (VCC) 20091223 Start
#define CACHE_SIZE          0x1000 // Cache size
#define DEBUG_CACHE_WRITE(...)
// (VCC) 20091223 End


#define ATOMID(type) 	    (*(u32*)type)
#define ATOM_ID(a,b,c,d)    (((a)<<24)|((b)<<16)|((c)<<8)|(d))
#define CODEC_TYPE_4CC      ATOM_ID


//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

typedef struct tagMP4VInfo
{
    unsigned int type;	// MP4MDTYPE_M4V or MP4MDTYPE_H263

    unsigned int frameWidth;
    unsigned int frameHeight;
    unsigned int sampleDuration;
    unsigned int sampleSize;
    unsigned int profile;
    unsigned int level;
    unsigned int timeScale;
    unsigned int keyFrameInterval;
    unsigned char maceTag;
} MP4VInfo;

typedef struct tagMP4AInfo
{
    unsigned int type;	// MP4MDTYPE_AMR or MP4MDTYPE_UNKNOWN

    unsigned int sampleDuration;
    unsigned int sampleSize;
    unsigned int profile;
    unsigned int level;
    unsigned int timeScale;
} MP4AInfo;

typedef struct tagMP4AVPacket
{
    unsigned int   track_id;       // index to the stream
    unsigned char    *pBytes;        /* the address to the audio/video data */
    unsigned int   numBytes;
    unsigned int   duration;
    unsigned int   render_offset;  /* for B-VOP, pts is not identical to dts */
    unsigned char    isSyncSample;
    unsigned char    status;
    unsigned char reserved[2];
}MP4AVPacket;

typedef struct tagMP4AVStream
{
    unsigned int db;
    unsigned int maxBitrate;
    unsigned int avgBitrate;
    unsigned int extraSize;
    unsigned char *extraData;
}MP4AVStream;

typedef volatile struct tagMP4MuxerInst
{
    char *pOutputFileName;

    unsigned int    u32MdatPos;     /* start position of data of mdat */

    // for video information
    unsigned int    frameWidth;
    unsigned int    frameHeight;

    // for audio information
#define TRACK_VIDEO_INDEX 0
#define TRACK_AUDIO_INDEX 1
#define TRACK_MP4_NUM       2
    unsigned int  trackIds[TRACK_MP4_NUM];  /* video -> trackIds[0], audio -> tackIds[1] */

    unsigned int u32MuxErrRtl;  /* keep the error return code */

    void*  mp4File;
    void    *priv_data;
} MP4MuxerInst;


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------

#if 0 // put back
int MP4Muxer_Open(void **ppInstm, u8 format, void *pusrdata);
int MP4Muxer_Write_Header(void *pMuxInst);
int MP4Muxer_SetVInfo(void *pHandle, void *pInfo, int nInfoSize);
int MP4Muxer_SetAInfo(void *pHandle, void *pInfo, int nInfoSize);
int MP4Muxer_Write_Packet(void *pHandle, void *av_packet);
int MP4Muxer_Render2File(void *pHandle, U8 mode);
int MP4Muxer_Update_Info(void *pHandle, MP4TrackId trackId, void *info);
int MP4Muxer_Close(void *pHandle);
#endif

#endif // MP4REC_PLUGIN_EN

#endif // __MDL_VDR_MX_H__

