#ifndef MPEGDEMUX_H
#define MPEGDEMUX_H

#include <stdint.h>
#include "avp_ms_input.h"

#ifdef __cplusplus
 extern "C" {
#endif // __cplusplus

#define MPEG_NEW_PARSE_METHOD   (0)

#define MPEG_PC_TEST_MODE //Enable this define to write parsing result to a file.

#define MPEG_SUPPORT_MMP

#define MPEG_SUPPORT_DURATION   1

//packet_start_code_prefix+stream id
#define MPEG_STREAM_PROGRAM_STREAM_MAP              0x1BC    //program_stream_map
#define MPEG_STREAM_PRIVATE_STREAM_1                0x1BD    //private_stream_1
#define MPEG_STREAM_PADDING_STREAM                  0x1BE    //padding_stream
#define MPEG_STREAM_PRIVATE_STREAM_2                0x1BF    //private_stream_2
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_0       0x1C0    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_1       0x1C1    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_2       0x1C2    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_3       0x1C3    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_4       0x1C4    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_5       0x1C5    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_6       0x1C6    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_7       0x1C7    //ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream number x xxxx
#define MPEG_STREAM_AUDIO_ELEMENTARY_STREAM_31      0x1DF
#define MPEG_STREAM_VIDEO_ELEMENTARY_STREAM_0       0x1E0    //ITU-T Rec. H.262 | ISO/IEC 13818-2 or ISO/IEC 11172-2 video stream number xxxx
#define MPEG_STREAM_VIDEO_ELEMENTARY_STREAM_15      0x1EF    //ITU-T Rec. H.262 | ISO/IEC 13818-2 or ISO/IEC 11172-2 video stream number xxxx
#define MPEG_STREAM_ECM                             0x1F0    //ECM_stream
#define MPEG_STREAM_EMM                             0x1F1    //EMM_stream
#define MPEG_STREAM_DSMCC                           0x1F2    //ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex A or ISO/IEC 13818-6_DSMCC_stream
#define MPEG_STREAM_IEC_13522                       0x1F3    //ISO/IEC_13522_stream
#define MPEG_STREAM_H2221_A                         0x1F4    //ITU-T Rec. H.222.1 type A
#define MPEG_STREAM_H2221_B                         0x1F5    //ITU-T Rec. H.222.1 type B
#define MPEG_STREAM_H2221_C                         0x1F6    //ITU-T Rec. H.222.1 type C
#define MPEG_STREAM_H2221_D                         0x1F7    //ITU-T Rec. H.222.1 type D
#define MPEG_STREAM_H2221_E                         0x1F8    //ITU-T Rec. H.222.1 type E
#define MPEG_STREAM_ANCILLARY                       0x1F9    //ancillary_stream
#define MPEG_STREAM_RESERVED_1                      0x1FA    //reserved data stream
#define MPEG_STREAM_RESERVED_2                      0x1FB    //reserved data stream
#define MPEG_STREAM_RESERVED_3                      0x1FC    //reserved data stream
#define MPEG_STREAM_EXTENDED_STREAM                 0x1FD    //reserved data stream
#define MPEG_STREAM_RESERVED_5                      0x1FE    //reserved data stream
#define MPEG_STREAM_PROGRAM_STREAM_DIRECTORY        0x1FF    //program_stream_directory


#define MPEG_SEQUENCE_HEADER_CODE                   0x1B3
#define MPEG_EXTENSION_START_CODE                   0x1B5
#define MPEG_SEQUENCE_END_CODE                      0x1B7
#define MPEG_GROUP_START_CODE                       0x1B8
#define MPEG_PACK_START_CODE                        0x1BA
#define MPEG_SYSTEM_START_CODE                      0x1BB
#define MPEG_PICTURE_START_CODE                     0x100

#define MPEG_BUFFER_SIZE                            (2048)

//Define the stream type of MPEG 1/2
#define MPEG_STREAM_TYPE_MPEG1                      1
#define MPEG_STREAM_TYPE_MPEG2                      2

//Define the type of audio/video
#define MPEG_STREAM_TYPE_VIDEO                      0
#define MPEG_STREAM_TYPE_AUDIO                      1

//Define frame rate code mapping value
#define MPEG_FRAME_RATE_CODE_1                      (23976)
#define MPEG_FRAME_RATE_CODE_2                      (24000)
#define MPEG_FRAME_RATE_CODE_3                      (25000)
#define MPEG_FRAME_RATE_CODE_4                      (29970)
#define MPEG_FRAME_RATE_CODE_5                      (30000)
#define MPEG_FRAME_RATE_CODE_6                      (50000)
#define MPEG_FRAME_RATE_CODE_7                      (59940)
#define MPEG_FRAME_RATE_CODE_8                      (60000)

//Define audio ID
#define MPEG_AUDIO_ID_SUB_AC3                       0x80
#define MPEG_AUDIO_ID_SUB_PCM                       0xA0
#define MPEG_AUDIO_ID_SUB_DTS                       0x88
#define MPEG_AUDIO_ID_SUB_MP3                       0x??
#define MPEG_AUDIO_ID_SUB_PIC                       0x20

typedef struct tagMPEG_Info
{
    uint16_t u16FrameRate;
    uint16_t u16HorizontalSize;
    uint16_t u16VerticalSize;
    int32_t s32PTS[2];         // 0: video, 1: audio
//#if (MPEG_SUPPORT_DURATION == 1)
    int32_t s32FirstPTS;
    int32_t s32LastPTS;
//#endif //(MPEG_SUPPORT_DURATION == 1)
    int32_t file_size;
    int32_t file_start_offset;
    int32_t last_pts_size;
    int32_t AvgRate;
} MPEG_Info;

typedef struct tagMPEG
{
    uint8_t       u8Init;
    uint8_t       u8MPEGType;      //MPEG 1/2
    cb_io_st      cbio;
    uint32_t      u32FileOffset;
    uint8_t      *Data;
    uint32_t      u32DataSize;    // A/B buffer size for each buffer
    
    MPEG_Info MPEGInfo;

    mvc_allocator_st    allocator;
    void               *alloc_ctx;
} MPEG;

typedef struct tagMPEG_KEYFRAME
{
    uint32_t    u32FrameCount;          // packet index
    uint32_t    u32FileOffset;          // File offset to find the frame
    uint32_t u32FrameSize;              // Total size of the frame. Unit is "byte".
    uint32_t u32FileSize;               // The file size we need to read for the frame.
} MPEG_KEYFRAME;

/////////////////////////////////////////////////////////////////////////////////////////////////
int MPEGdemx_Init(const cb_io_st *cbio, MPEG *pMpeg, uint8_t *pBuf, int buf_size, uint8_t *demux_buf_A, uint8_t *demux_buf_B, int len);

int MPEGdemux_ParsePacket(MPEG *pMpeg);
void MPEGdemux_End(MPEG *pMpeg);

uint8_t MPEGdemux_Reset(MPEG *pMpeg, uint32_t u32FileOffset, uint32_t u32KeyFrameIndex, uint32_t u32VideoFrameCount);

#ifdef FS_ON_MCU51
void MPEGdemux_SetKeyFrameBuf(MPEG_KEYFRAME *pBufAddress);
U32 MPEGdemux_GetKeyFrameCount(void);
#endif //FS_ON_MCU51

#ifdef MPEG_SUPPORT_MMP

typedef enum
{
    MMP_AUDIO_TRACK,
    MMP_VIDEO_TRACK,
    MMP_SUBTITLE_TRACK,
} MMP_TRACK_TYPE;

int MPEGdemux_MMP_Reset(MPEG *pMpeg);
int MPEGdemux_MMP_read_data(MPEG *pMpeg, uint8_t *pBuffer, int nBufSize, int *len, uint32_t *pts);
int MPEGdemux_MMP_GetAudioType(MPEG *pMpeg);
int MPEGdemux_MMP_GetVideoType(MPEG *pMpeg);
int MPEGdemux_MMP_GetVideoWidth(MPEG *pMpeg);
int MPEGdemux_MMP_GetVideoHeight(MPEG *pMpeg);
int MPEGdemux_MMP_GetDuration(MPEG *pMpeg);
int MPEGdemux_MMP_GetFrameRate(MPEG *pMpeg);
int MPEGdemux_MMP_GetFileSize(MPEG *pMpeg);
int MPEGdemux_GetTrackNum(MPEG *pMpeg, int track_type);
int MPEGdemux_MMP_Set_Track(MPEG *pMpeg, int track_type, int track_id);

void MPEGdemux_MMP_init(MPEG *pMpeg);
uint32_t MPEGdemux_MMP_GetAvgRate(MPEG *pMpeg);

#endif //MPEG_SUPPORT_MMP
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MPEGDEMUX_H
