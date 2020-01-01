////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
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


#ifndef RMVB_H
#define RMVB_H

#include <stdint.h>
#include "avp_streaming.h"
#include "avp_mvc_demuxer.h"

#define MAX_AUDIO_CHUNK    (16  * 1024)
#define MAX_RV_NUM_PACKETS 128
#define MAX_RA_NUM_AU      20
#define MAX_INDEX_NUM   30
#define RESYNC_CHUNK_SIZE   1010
#define RESYNC_PKT_HDR_SIZE  14
#define RESYNC_PER_CHUNK_SIZE (RESYNC_CHUNK_SIZE+RESYNC_PKT_HDR_SIZE)

#define CONVUINTXTOUINT32(x) (*(uint32_t*)(&(x)))
#define CONVPUINTXTOUINT32(x) (*(uint32_t*)(x))
#define CONVUINTXTOUINT16(x) (*(uint16_t*)(&(x)))
#define CONVPUINTXTOUINT16(x) (*(uint16_t*)(x))

//#define OUTPUT_RVCREF
#ifdef OUTPUT_RVCREF
#define RM_PACKET_INFO_SIZE 20
#else
#define RM_PACKET_INFO_SIZE 1
#endif

#ifdef _WIN32
#include <stdio.h>
#define ERR_MSG printf
#define DBG_RMVB    1 ? 0 :
#define DBG_DROP    1 ? 0 :
#elif 0
#define ERR_MSG(fmt, args...) diag_printf(fmt, ##args)
#else
#define ERR_MSG(x, args...) ((void)0)
#define DBG_RMVB(format, ...)     ((void) 0)
#define DBG_DROP(format, ...)     ((void) 0)
#endif

#define CONFORM_ASSERT(expr) ((void)0)//assert(expr)
#define OUT_AACFILE
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#define FACTOR_14(a) ((a)*14)
#define MUX(a, b, c) ((a)?(b):(c))

#define PARSE_RMVB_RMFFfailed      -1
#define MAX_READ_SIZE              (256 * 1024)
#define RM_PROPERTIES_OBJECT       0x50524F50
#define RM_MEDIA_PROPERTIES_OBJECT 0x4D445052
#define RM_CONTENT_OBJECT          0x434F4E54
#define RM_DATA_OBJECT             0x44415441
//#define RM_PARSER_LOGICAL_FILEINFO "logical-fileinfo"
//#define RM_PARSER_LOGICAL_PREFIX "logical-"
#define RA_CODEC_ID_SIPR           0x73697072      // sipr
#define RA_CODEC_ID_COOK           0x636F6F6B      // cook
#define RA_CODEC_ID_ATRC           0x61747263      // atrc
#define RA_CODEC_ID_RAAC           0x72616163      // raac
#define RA_CODEC_ID_RACP           0x72616370      // racp

#define RA_INTERLEAVE_ID_SIPR      0x73697072      // sipr
#define RA_INTERLEAVE_ID_GENR      0x67656E72      // genr

#define RA_MAX_SUBFRAME_SIZE       280
#define RA_MAX_FRAME_NUM           100

#define RM_RVTR_RV30_ID            0x52565432
#define RM_RV10VIDEO_ID            0x52563130
#define RM_RV20VIDEO_ID            0x52563230
#define RM_RV30VIDEO_ID            0x52563330
#define RM_RV40VIDEO_ID            0x52563430

#define RA_MAX_FRAME_SIZE          (7*4*1024)  // MAX: COOK superblock size = 25020
#define AOL_VOL_MAX_SIZE            80
#ifdef MIPSDEV
#include <mips/mips32.h>
#define SWAPBYTES(r1)           _mips32r2_bswapw(r1)
#define SWAPBYTES_UINT16(x)     _mips32r2_wsbh(x)
#else
#define SWAPBYTES_UINT16(a) (((a)&0x0ff)<<8) | (((a)>>8)&0x0ff)
#define SWAPBYTES(r1) ((((r1)&0x000000ff)<<24) | (((r1)&0x0000ff00)<<8) | (((r1)&0x00ff0000)>>8) | (((r1)>>24)&0x000000ff))
#endif

#define STORE_4BYTES_UAL_LE(ptr, val) \
    *(ptr) = (val)&0xff; \
    *((ptr)+1) = ((val)>>8)&0xff; \
    *((ptr)+2) = ((val)>>16)&0xff; \
    *((ptr)+3) = (val)>>24;

#define STORE_4BYTES_UAL(ptr, val) \
    *(ptr) = (val)>>24; \
    *((ptr)+1) = ((val)>>16)&0xff; \
    *((ptr)+2) = ((val)>>8)&0xff; \
    *((ptr)+3) = (val)&0xff;

#define GET_BYTES_UAL(ptr, bytes, val) \
{ \
    int i; \
    for (i=0; i<bytes; i++) \
        val |= (ptr)[i]<<((3-i)<<3); \
}

// defined for 'RMFF 1.0 Flags' rule_to_flag_map[]
#define HX_RELIABLE_FLAG        0x0001
#define HX_KEYFRAME_FLAG        0x0002
#define HX_LASTFRAME_FLAG       0x0004
#define HX_INTERFRAME_MODE_FLAG 0x0008

enum RM_STREAM_TYPE{ RM_UNKNOWN_STREAM = 0,
                     RM_AUDIO_SINGLE_STREAM,    RM_VIDEO_SINGLE_STREAM,     RM_AUDIO_MULTI_STREAM,
                     RM_VIDEO_MULTI_STREAM,     RM_AUDIO_LOGICAL_STREAM,    RM_VIDEO_LOGICAL_STREAM,
                     RM_LOGICAL_FILEINFO};

typedef enum
{
    STREAM_VIDEO = 0,
    STREAM_AUDIO,
    STREAM_END,
    STREAM_OTHER,
    STREAM_ERROR,
} EN_STREAM_TYPE;

typedef enum
{
    RVFrameTypePartial,
    RVFrameTypeWhole,
    RVFrameTypeLastPartial,
    RVFrameTypeMultiple
} RVFrameType;

typedef struct {
    uint32_t bIsValid;
    uint32_t ulOffset;
} rv_segment;

struct rm_props_hdr
{
    uint32_t index_offset;    //the start of the index header object
    uint32_t data_offset;     //the start of the first Data Chunk Header
    uint16_t num_streams;     //total number of media properties header
};

typedef struct rmff_ra_format_info_struct
{
    uint32_t  ulSampleRate;
    uint16_t  usBitsPerSample;
    uint16_t  usNumChannels;
    uint16_t  usAudioQuality;
    uint32_t  ulBitsPerFrame;
    uint32_t  ulGranularity;
    uint32_t  ulOpaqueDataSize;
} rmff_ra_format_info;

struct rmff_media_props_hdr
{
    uint32_t obj_id;              /* unique identifier for this header */
    uint32_t size;                /* size of header in file */
    uint16_t obj_ver;             /* struct version */
    uint16_t stream_num;          /* stream number */
    uint32_t max_bit_rate;        /* maximum bit rate of stream */
    uint32_t avg_bit_rate;        /* average bit rate of stream */
    uint32_t max_pkt_size;        /* max length of packet in stream (bytes) */
    uint32_t avg_pkt_size;        /* averge length of packet in stream (bytes) */
    uint32_t start_time;          /* start time of stream -- clip relative */
    uint32_t preroll;             /* preroll time (milliseconds) */
    uint32_t duration;            /* duration of stream (milliseconds) */
};

typedef struct
{
    uint16_t  version;
    EN_STREAM_TYPE stream_index;
    int32_t   st_addr;
    int32_t   valid_size;
    int32_t   flush_size;
    uint32_t  timestamp;
    uint8_t   pkt_group;
    uint8_t   HX_flags;
    uint16_t  asm_rule;
    uint8_t   audio_isFragmented;
    uint32_t  audio_ulNumAU;
} AVPacket;

typedef struct
{
    uint32_t timestamp;
    uint32_t offset;
    uint32_t packet_count_for_this_packet;
} IndexRecord;

typedef enum parse_mode_e
{
    PARSE_PKT_HEADER,
    PARSE_FRAME_DATA,
} parse_mode_et;

typedef struct VOPbuff_type
{
    int byte_offset;
    int size;
    int64_t pts;
    int no_parse_packet_header;
} VOP_BUF_TYPE;

typedef struct rm_format_context
{
    uint32_t  u32RVDataOffset;      // video data chunk begin
    uint32_t  u32RVDataEnd;         // video data chunk size
    int32_t   duration;
    AVPacket    pkt;
    int32_t  video_stream_id;
    int32_t  audio_stream_id;
    int32_t   video_codec;
    MVCAudioType   audio_codec;
    uint32_t  video_max_bit_rate;
    uint32_t  video_avg_bit_rate;
    uint32_t  audio_max_bit_rate;
    uint32_t  audio_avg_bit_rate;
    uint8_t   b_audioIsVBR;
    uint16_t  frame_width;
    uint16_t  frame_height;
    uint16_t  bit_count;
    uint16_t  pad_width;
    uint16_t  pad_height;
    //uint32_t  ulLastSentEndTime; //refsw audio usage
    uint32_t  blockduration;
    uint32_t  TotalPktNum;
    uint32_t  filesize; //whole rm file size
    int32_t   sample_rate;
    int32_t   channel_num;
    //0:video, 1:audio
    uint32_t  u32IdxOffset[2];  //the current video index (video_index[42]) offset, add 42*12 bytes to the next video index
    uint32_t  u32IdxEnd[2];      //End of video index chunk
    uint32_t  u32IdxStart[2];      //Start of video index chunk
    IndexRecord  minIdx_record[2];
    IndexRecord  maxIdx_record[2];
    IndexRecord  index_rec[2][MAX_INDEX_NUM]; //close to 512bytes
    uint32_t  index_num[2];    //number of video_index[]
    uint32_t  total_index_num[2];    //total video index records in the index chunk
    uint32_t  last_index_pts;
    uint32_t  video_fps;

    // for CBR clips
    uint16_t FlavorIdx;
    uint16_t InterleaveFactor;
    uint16_t InterleaveBlkSz;
    uint16_t CodecFrameSz;
    uint32_t InterleaveID;
    uint8_t  Flag_Interleave;
    uint8_t  Flag_HasInterlvPatn;
    uint16_t InterleavePatn[RA_MAX_FRAME_NUM];
    int32_t  AudKeyTimeStamp;
    uint16_t NumFramePerSuperBlk;
    uint32_t FramePerBlk;
    uint32_t FrameSzInBits;
    int32_t   audio_frame_num;
    int32_t   is_more_frame_hdr;
    int32_t   skip_one_video_frame;
    struct rm_props_hdr rm_properties_hdr;
    int32_t  prev_video_pts;
    int32_t  prev_audio_pts;
    int32_t     prev_IP_pts;
    parse_mode_et parse_mode;
    EN_STREAM_TYPE packet_type;
    int32_t     resync_chunk;

    uint32_t    curfile_pos;
    uint32_t    rv_out_frame_index;
    uint32_t    ra_out_frame_index;
    uint32_t    ra_vop_start_index;
    uint32_t    rm_VOL_size;
    uint32_t    rm_AOL_size;
    uint8_t     video_config[AOL_VOL_MAX_SIZE];
    uint8_t     audio_config[AOL_VOL_MAX_SIZE];
    uint8_t     *rv_out_frame;
    uint8_t     *ra_out_frame;
    uint8_t     *frame_info_ptr;
    VOP_BUF_TYPE *AVFrame;
    int32_t     AVFrame_end;
    int32_t     AVFrame_start;
    uint32_t    video_entire_frame_size;
} RM_FORMAT_CONTEXT; //rm_format_context;

int parse_rmff(cb_buffer_st *cbuffer, RM_FORMAT_CONTEXT *rm_cont);
EN_STREAM_TYPE parse_rm_packet_header(cb_buffer_st *cbuffer, RM_FORMAT_CONTEXT *rm_cont, uint32_t *ultimestamp, int *packet_offset);
uint32_t read_14or30_bits(cb_buffer_st *cbuffer, uint8_t frame_flag, uint32_t buf, uint32_t *hdr_size);
void pack_vop_header(uint32_t m_ulFrameSize, uint32_t m_ultimestamp, uint32_t m_ulNumPackets, uint8_t *ptr,
                     rv_segment *p_Segments);
int32_t parse_audio_vbr_packet(cb_buffer_st *cbuffer, RM_FORMAT_CONTEXT *rm_cont, uint32_t *ulNumAU, uint8_t *isFragmented
                             , uint32_t *ulAUSize, uint32_t *ulAUFragSize, uint32_t *ulAUDataLen);
void  pack_loss_packet(RM_FORMAT_CONTEXT *rm_cont, uint32_t FirstStartTime, uint32_t LastEndTime, uint8_t *pout, uint32_t blockduration);
int32_t pack_nonfrag_packet(cb_buffer_st *cbuffer, RM_FORMAT_CONTEXT *rm_cont, uint32_t ulNumAU, uint32_t *ulAUDataLen, uint8_t *pout);
int32_t pack_frag_packet(void);
int32_t reset_start_data_offset(RM_FORMAT_CONTEXT *rm_cont);
void get_index_record(cb_buffer_st *cbuffer, RM_FORMAT_CONTEXT *rm_cont, int32_t is_first_getidxrec
                      , int32_t stream_type, int mode); //stream_type: 0, 1
int32_t find_pts_in_indrecord(RM_FORMAT_CONTEXT *rm_cont, uint32_t timestamp, int32_t userseek, int32_t slow_get, int32_t stream_type, int32_t mode, int32_t dir);
#endif
