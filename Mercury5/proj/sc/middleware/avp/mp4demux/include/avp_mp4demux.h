////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


/*
 *  API Definition for MP4 Demux
 *
 */

#ifndef MP4DEMUX_H
#define MP4DEMUX_H

#include <stdint.h>
#include "avp_mvc_demuxer.h"

#ifdef SUPPORT_KMV
#include "avp_kmv_api.h"
int Enable_kmv_demux_plugin(kmv_func_st *hdr);
#endif

struct cb_io_s;

/*
 * open mp4 demux instance
 * return: 0: Okay, < 0: fail
 *
 */
typedef struct _MP4_TRACKINFO
{
    uint8_t track_exist;
    uint32_t data_fmt;
    uint8_t *m_decoderConfigDesc;
    uint32_t m_decoderConfigDesc_len;
} MP4_TRACKINFO;

#define MP4DMX_SEEK_TYPE_PREV_I     0
#define MP4DMX_SEEK_TYPE_NEXT_I     1

typedef struct demux_buffer_s
{
    void *baseptr; // the allocated buffer pointer for demuxer context
    unsigned short mdx_byteused;
    unsigned short mdx_maxbyte;
    unsigned char *mdx_ptr;
} demux_buffer_st;

int MP4DMX_Open(void **ppInst, unsigned char *heap, unsigned short heap_size,
                       const struct cb_io_s *cbio, void *video_track, void *audio_track, int *width, int *height,int ringbuf_size, void *mem_ctx);

/*
 * read video sample
 * input: pInst: instance,
 *        frameidx: the frame index want to read, 1 base
 *        pbuf: the read sample buffer (assigned from caller)
 *        pnSize: the size of read buffer
 *        pStart: playback start time (seconds * 1000)
 *        pDuration: playback duration (seconds * 1000)
 * return: 0: Okay, < 0: fail
 *
 */
int MP4DMX_ReadSample(void *pInst, uint32_t frameidx, void *pBuf, uint32_t *pnSize,
                            uint32_t *is_sync_sample, mvc_stream_type_et track_type);

int MP4DMX_ReadSampleInfo(void *pInst, uint32_t frameidx, uint32_t *pOffset, uint32_t *pnSize,
                               uint64_t *pStart, uint64_t *pDuration, uint32_t *is_sync_sample,
                               mvc_stream_type_et track_type);

/*
* read subtitle sample
* input: pInst: instance,
*        frameidx: the frame index want to read, 1 base
*        pbuf: the read sample buffer (assigned from caller)
*        pnSize: the size of read buffer
*        pStart: playback start time (seconds * 1000)
*        pDuration: playback duration (seconds * 1000)
* return: 0: Okay, < 0: fail
*
*/
int MP4DMX_ReadSubtitle(void *pInst, uint32_t frameidx, uint32_t *pOffset, unsigned int *pnSize,
                        unsigned long int *pStart, unsigned long int *pDuration);

/*
 * close mp4 demux instance
 * return: 0: Okay, < 0: fail
 *
 */
void MP4DMX_Close(void *pInst);

/*
 * Get total duration
 * return: ttotal duration (samples)
 *
 */
void MP4DMX_GetDuration(void *pInst, unsigned int *pU32TotalTime);
int MP4DMX_GetAudioIdx (void *pInst, uint32_t reftime, uint32_t *pframeidx);
int MP4DMX_GetAudioIdxGap (void *pInst, unsigned int sample_size);
int MP4DMX_GetSubtitleIdx (void *pInst, unsigned long int reftime, unsigned int *pframeidx);
//
// when we need to resync audio's idx due to seeking to I(key) frame
// the reftime will output the keyframe time
//
int MP4DMX_SeekVideoIdx (void *pInst,
                                uint32_t          *reftime,         //IN, OUT(when we need to resync audio's sample idx)
                                uint32_t *key_frameidx,         //OUT
                                uint32_t *prev_key_frameidx,    //OUT
                                int mode);

void MP4DMX_GetAvgBitrate(void *pInst, unsigned int *V_AveBitrate,
                                  unsigned int *A_AveBitrate, unsigned int *Max_V_Biterate);
// estimate average video bitrate with file size and video track duration
void MP4DMX_GetAvgBitrate2(void *pInst, unsigned int *V_AveBitrate);
int MP4DMX_GetNumberOfTrack(void *pInst, int type);
int MP4DMX_SetTrack(void *pInst, int track_type, int track_id);
void MP4DMX_GetAvgSyncSample(void *pInst, unsigned int *V_AveSyncSample);
void MP4DMX_GetFramerate(void *pInst, unsigned int *avg_framerate);
void MP4DMX_SetAllocator(void *pInst, const void *allocator, void* cbctx);
void *MP4DMX_GetAllocator(void *pInst);
void MP4DMX_GetVideoRotateAngle(void *pInst, int *rotate_angle);
void MP4DMX_GetVideoMace(void *pInst, int *mace);
void MP4DMX_QuerySeekable(void *pInst, int *seekable);
uint32_t MP4DMX_SeekToTargetHeader(void *pInst);
#endif /* MP4DEMUX_H */
