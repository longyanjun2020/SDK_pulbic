//==============================================================================
//
//  File        : mmpf_avimux.h
//  Description : Header function of AVI muxer
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================
#ifndef _MMPF_AVIMUX_H_
#define _MMPF_AVIMUX_H_

#include "lib_retina.h"

#if (MGR_SUPPORT_AVI == 1)
//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================


//==============================================================================
//
//                              MARCOS
//
//==============================================================================
#define MAKE_FCC(c0, c1, c2, c3) \
                ((MMP_ULONG)c0 | ((MMP_ULONG)c1 << 8) | \
                ((MMP_ULONG)c2 << 16) | ((MMP_ULONG)c3 << 24))

#define SIZEOF_STD_INDEX_ENTRIES(entnum) \
                ((entnum) << 3)
#define SIZEOF_SUPER_INDEX_ENTRIES(entnum) \
                ((entnum) << 4)
#define SUPER_INDEX_ENTRIES_CNT(entsize) \
                ((entsize) >> 4)
//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
/**
 @brief bitwise flag in AVI headers
*/
// flags for ulFlags member of @ref AVI_MAIN_HEADER
#define AVIF_HASINDEX               0x00000010
#define AVIF_MUSTUSEINDEX           0x00000020
#define AVIF_ISINTERLEAVED          0x00000100
#define AVIF_TRUSTCKTYPE            0x00000800
#define AVIF_WASCAPTUREFILE         0x00010000
#define AVIF_COPYRIGHTED            0x00020000

// flags for ulFlags member of @ref AVI_STREAM_HEADER
#define AVISF_DISABLED              0x00000001
#define AVISF_VIDEO_PALCHANGES      0x00010000

// flags for ulFlags member of @ref AVI_STD_INDEX or @ref AVI_SUPER_INDEX
#define AVI_INDEX_OF_INDEXES        0x00
#define AVI_INDEX_OF_CHUNKS         0x01
#define AVI_INDEX_OF_TIMED_CHUNKS   0x02
#define AVI_INDEX_OF_SUB_2FIELD     0x03
#define AVI_INDEX_IS_DATA           0x80

#define AVI_INDEX_SUB_DEFAULT       0x00
#define AVI_INDEX_SUB_2FIELD        0x01

/**
 @brief constant size of AVI chunks, in unit of bytes
*/
#define AVI_RIFF_HEADER_SIZE        12 ///< ('RIFF' size formType)
#define AVI_LIST_CHUNK_SIZE         12 ///< ('LIST' size listType)
#define AVI_CHUNK_HEADER_SIZE        8 ///< (   ID  size)
#define AVI_MAIN_HEADER_SIZE        64 ///< see @ref AVI_MAIN_HEADER
#define AVI_STREAM_HEADER_SIZE      64 ///< see @ref AVI_STREAM_HEADER
#define AVI_VID_STREAM_FMT_SIZE     48 ///< see @ref AVI_BITMAP_FORMAT
#define AVI_AUD_WAVE_FMT_SIZE       26 ///< see @ref AVI_WAVE_FORMAT
#define AVI_AUD_ADPCM_FMT_SIZE      28 ///< see @ref AVI_WAVE_FORMAT
#define AVI_AUD_AACLC_FMT_SIZE      28 ///< AudioSpecificConfig() data additional
#define AVI_AUD_MP3_FMT_SIZE        38 ///< see @ref AVI_MP3_FORMAT 
#define AVI_INDEX2_0_SIZE           32 ///< see @ref AVI_STD_INDEX
#define AVI_STD_IDX_ENTRY_SIZE       8 ///< see @ref AVI_STD_INDEX_ENTRY
#define AVI_SUPER_IDX_ENTRY_SIZE    16 ///< see @ref AVI_SUPER_INDEX_ENTRY
#if (AVI_IDIT_CHUNK_EN == 1)
#define AVI_IDIT_CHUNK_SIZE         28 ///< (   ID  size YYYY-MM-DD hh:mm:ss)
#else
#define AVI_IDIT_CHUNK_SIZE          0
#endif
#if (AVI_ISFT_CHUNK_EN == 1)
#define AVI_ISFT_CHUNK_SIZE         (8 + sizeof(AVI_ISFT_DATA_STR))
#else
#define AVI_ISFT_CHUNK_SIZE          0
#endif
#if (AVI_ISFT_CHUNK_EN == 1)
#define AVI_INFO_CHUNK_SIZE        (12 + AVI_ISFT_CHUNK_SIZE)
#else
#define AVI_INFO_CHUNK_SIZE          0
#endif

/**
 @brief WAVE format tags
*/
#define WAVE_UNKNOWN_FORMAT         0x0000  ///< Microsoft Corporation
#define WAVE_PCM_FORMAT             0x0001  ///< Microsoft Corporation
#define WAVE_ADPCM_FORMAT           0x0002  ///< Microsoft Corporation
#define WAVE_ALAW_FORMAT            0x0006  ///< Microsoft Corporation
#define WAVE_MULAW_FORMAT           0x0007  ///< Microsoft Corporation
#define WAVE_IMA_ADPCM_FORMAT       0x0011  ///< Intel Corporation
#define WAVE_MPEGLAYER3_FORMAT      0x0055  ///< ISO/MPEG Layer3 Format Tag
#define WAVE_AAC_FORMAT             0x00FF
#define WAVE_FFMPEG_AAC_FORMAT      0x706D

/**
 @brief MP3 id & flag
*/
#define MP3_ID_UNKNOWN              0
#define MP3_ID_MPEG                 1
#define MP3_ID_CONSTANTFRAMESIZE    2

#define MP3_FLAG_PADDING_ISO        0x00000000  ///< insert padding to achieve the average bitrate
#define MP3_FLAG_PADDING_ON         0x00000001  ///< always insert padding
#define MP3_FLAG_PADDING_OFF        0x00000002  ///< never insert padding

/**
 @brief non-keyframe flag in the size field of index entries
*/
#define AVI_INDEX_DELTA_FRAME       (0x80000000)
#define AVI_INDEX_SIZE_MASK         (~0x80000000)


/**
 @brief total size for AVI header chunks
*/
#if (AVI_VERSION == AVI_1_0_MUXER)
#define AVI_NO_AUD_HEADERS_SIZE     (AVI_RIFF_HEADER_SIZE + AVI_LIST_CHUNK_SIZE + \
                                    AVI_MAIN_HEADER_SIZE + \
                                    AVI_LIST_CHUNK_SIZE + AVI_STREAM_HEADER_SIZE + \
                                    AVI_VID_STREAM_FMT_SIZE + \
                                    AVI_IDIT_CHUNK_SIZE + AVI_INFO_CHUNK_SIZE + \
                                    AVI_LIST_CHUNK_SIZE)
#define AVI_WAVE_HEADERS_SIZE       (AVI_NO_AUD_HEADERS_SIZE + AVI_LIST_CHUNK_SIZE + \
                                    AVI_STREAM_HEADER_SIZE + AVI_AUD_WAVE_FMT_SIZE)
#define AVI_AACLC_HEADERS_SIZE      (AVI_NO_AUD_HEADERS_SIZE + AVI_LIST_CHUNK_SIZE + \
                                    AVI_STREAM_HEADER_SIZE + AVI_AUD_AACLC_FMT_SIZE)
#define AVI_MP3_HEADERS_SIZE        (AVI_NO_AUD_HEADERS_SIZE + AVI_LIST_CHUNK_SIZE + \
                                    AVI_STREAM_HEADER_SIZE + AVI_AUD_MP3_FMT_SIZE)
#elif (AVI_VERSION == AVI_2_0_MUXER)
#define AVI_NO_AUD_HEADERS_SIZE     (AVI_RIFF_HEADER_SIZE + AVI_LIST_CHUNK_SIZE + \
                                    AVI_MAIN_HEADER_SIZE + \
                                    AVI_LIST_CHUNK_SIZE + AVI_STREAM_HEADER_SIZE + \
                                    AVI_VID_STREAM_FMT_SIZE + AVI_INDEX2_0_SIZE + \
                                    SIZEOF_SUPER_INDEX_ENTRIES(AVI_SUPER_INDEX_ENTRY_CNT) + \
                                    AVI_IDIT_CHUNK_SIZE + AVI_INFO_CHUNK_SIZE + \
                                    AVI_LIST_CHUNK_SIZE)
#define AVI_WAVE_HEADERS_SIZE       (AVI_NO_AUD_HEADERS_SIZE + \
                                    AVI_LIST_CHUNK_SIZE + AVI_STREAM_HEADER_SIZE + \
                                    AVI_AUD_WAVE_FMT_SIZE + AVI_INDEX2_0_SIZE + \
                                    SIZEOF_SUPER_INDEX_ENTRIES(AVI_SUPER_INDEX_ENTRY_CNT))
#define AVI_AACLC_HEADERS_SIZE      (AVI_NO_AUD_HEADERS_SIZE + \
                                    AVI_LIST_CHUNK_SIZE + AVI_STREAM_HEADER_SIZE + \
                                    AVI_AUD_AACLC_FMT_SIZE + AVI_INDEX2_0_SIZE + \
                                    SIZEOF_SUPER_INDEX_ENTRIES(AVI_SUPER_INDEX_ENTRY_CNT))
#define AVI_MP3_HEADERS_SIZE        (AVI_NO_AUD_HEADERS_SIZE + \
                                    AVI_LIST_CHUNK_SIZE + AVI_STREAM_HEADER_SIZE + \
                                    AVI_AUD_MP3_FMT_SIZE + AVI_INDEX2_0_SIZE + \
                                    SIZEOF_SUPER_INDEX_ENTRIES(AVI_SUPER_INDEX_ENTRY_CNT))
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
/**
 @brief 'RIFF' chunk header
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG ulFourCC;             ///< must be "RIFF"
    MMP_ULONG ulSize;               ///< chunk size, not including the initial 8 bytes
    MMP_ULONG ulFormType;           ///< specify the format of data, here must be "AVI "
} RIFF_CHUNK;
/**
 @brief list chunk header
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG ulFourCC;             ///< list chunk ID
    MMP_ULONG ulSize;               ///< chunk size, not including the initial 8 bytes
    MMP_ULONG ulListType;           ///< specify the content of list
} LIST_CHUNK;
/**
 @brief chunk header
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG ulFourCC;             ///< chunk ID
    MMP_ULONG ulSize;               ///< chunk size, not including the initial 8 bytes
    MMP_UBYTE ubData[56];           ///< chunk data
} SUB_CHUNK;
/**
 @brief AVI main header
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG ulFourCC;             ///< must be "avih"
    MMP_ULONG ulSize;               ///< chunk size, not including the initial 8 bytes
    MMP_ULONG ulMicroSecPerFrame;   ///< num of us between frames, overall timing for the file
    MMP_ULONG ulMaxBytesPerSec;     ///< the max. data rate
    MMP_ULONG ulPadGranularity;     ///< pad the data to multiples of this value
    MMP_ULONG ulFlags;              ///< bitwise combination flag
    MMP_ULONG ulTotalFrames;        ///< total num of video frames in the RIFF ��AVI�� chunk
    MMP_ULONG ulInitialFrames;      ///< should be zero for non-interleaved files
    MMP_ULONG ulStreams;            ///< num of streams in the file
    MMP_ULONG ulSuggestedBufSize;   ///< should be large enough to contain the largest chunk generally
    MMP_ULONG ulWidth;              ///< width in pixels
    MMP_ULONG ulHeight;             ///< height in pixels
    MMP_ULONG ulReserved[4];        ///< set to zero
} AVI_MAIN_HEADER;
/**
 @brief AVI stream header
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG  ulFourCC;            ///< must be "strh"
    MMP_ULONG  ulSize;              ///< chunk size, not including the initial 8 bytes
    MMP_ULONG  ulFourCCType;        ///< specifies the stream data type
    MMP_ULONG  ulFourCCHandler;     ///< specifies the codec
    MMP_ULONG  ulFlags;             ///< bitwise combination flag
    MMP_USHORT usPriority;          ///< priority of a stream tye
    MMP_USHORT usLanguage;          ///< language tag
    MMP_ULONG  ulInitialFrames;     ///< @ref AVI_MAIN_HEADER
    MMP_ULONG  ulScale;             ///< used with ulRate to specify the time scale used
    MMP_ULONG  ulRate;              ///< ulRate/ulScale gives frame rate(video) or sample rate(audio)
    MMP_ULONG  ulStart;             ///< the starting time for this stream (not concurrent with the file)
    MMP_ULONG  ulLength;            ///< the length of this stream, in unit of ulRate/ulScale
    MMP_ULONG  ulSuggestedBufSize;  ///< should be large enough to contain the largest chunk generally
    MMP_ULONG  ulQuality;           ///< number 0 to 10000, used by codec
    MMP_ULONG  ulSampleSize;        ///< size of single sample, set to zero if samples can vary in size

    struct __attribute__((packed))
    {
        MMP_USHORT usLeft;
        MMP_USHORT usTop;
        MMP_USHORT usRight;
        MMP_USHORT usBottom;
    } frameRect;
} AVI_STREAM_HEADER;
/**
 @brief AVI video stream format
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG  ulFourCC;            ///< must be "strf"
    MMP_ULONG  ulSize;              ///< chunk size, not including the initial 8 bytes
    MMP_ULONG  ulSizeOfBitmapInfo;  ///< num of bytes required by the structure
    MMP_ULONG  ulWidth;             ///< the width of the bitmap
    MMP_ULONG  ulHeight;            ///< the height of the bitmap
    MMP_USHORT usPlanes;            ///< num of planes for the target device, must be set to 1.
    MMP_USHORT usBitCount;          ///< bits per pixel
    MMP_ULONG  ulCompression;       ///< a FOURCC code
    MMP_ULONG  ulSizeImage;         ///< the size, in bytes, of the image
    MMP_ULONG  ulXPelsPerMeter;     ///< the horizontal resolution, in pixels per meter
    MMP_ULONG  ulYPelsPerMeter;     ///< the vertical resolution, in pixels per meter
    MMP_ULONG  ulClrUsed;           ///< num of color indices in the color table used
    MMP_ULONG  ulClrImportant;      ///< num of color indices that are considered important
} AVI_BITMAP_FORMAT;
/**
 @brief AVI audio wave stream format
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG  ulFourCC;            ///< must be "strf"
    MMP_ULONG  ulSize;              ///< chunk size, not including the initial 8 bytes
    MMP_USHORT usFormatTag;         ///< Waveform-audio format type
    MMP_USHORT usChannels;          ///< num of channels
    MMP_ULONG  ulSamplesPerSec;     ///< Sample rate
    MMP_ULONG  ulAvgBytesPerSec;    ///< average data-transfer rate, in bytes per second
    MMP_USHORT usBlockAlign;        ///< Block alignment, in bytes
    MMP_USHORT usBitsPerSample;     ///< Bits per sample
    MMP_USHORT usExtraSize;         ///< Size, in bytes, of extra format information
} AVI_WAVE_FORMAT;
/**
 @brief AVI audio adpcm stream format
*/
typedef struct __attribute__((packed))
{
    AVI_WAVE_FORMAT wavFmt;         ///< see @ref AVI_WAVE_FORMAT
    MMP_UBYTE ubExtraData[2];       ///< 2 bytes for AAC_LC
} AVI_ADPCM_FORMAT;
/**
 @brief AVI audio aac stream format
*/
typedef struct __attribute__((packed))
{
    AVI_WAVE_FORMAT wavFmt;         ///< see @ref AVI_WAVE_FORMAT
    MMP_UBYTE ubExtraData[2];       ///< 2 bytes for AAC_LC
} AVI_AAC_FORMAT;
/**
 @brief AVI audio mp3 stream format
*/
typedef struct __attribute__((packed))
{
    AVI_WAVE_FORMAT wavFmt;         ///< see @ref AVI_WAVE_FORMAT
    MMP_USHORT usID;                ///< set to 1 (MPEGLAYER3_ID_MPEG)
    MMP_ULONG  ulFlag;              ///< whether padding is used to adjust the average bitrate
    MMP_USHORT usBlkSize;           ///< frame length in bytes * usFramePerBlk
    MMP_USHORT usFramePerBlk;       ///< number of audio frames per block.
    MMP_USHORT usCodecDelay;        ///< encoder delay in samples.
} AVI_MP3_FORMAT;
/**
 @brief AVI OpenDML standard index
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG   ulFourCC;           ///< must be "ixnn"
    MMP_ULONG   ulSize;             ///< chunk size, not including the initial 8 bytes
    MMP_USHORT  usLongsPerEntry;    ///< must be 2
    MMP_UBYTE   ubIndexSubType;     ///< must be 0
    MMP_UBYTE   ubIndexType;        ///< must be AVI_INDEX_OF_CHUNKS
    MMP_ULONG   ulEntriesInUse;     ///< the number of valid index entries
    MMP_ULONG   ulChunkId;          ///< ex. 00dc, 01wb
    MMP_ULONG64 ullBaseOffset;      ///< the base offset for the index entries
    MMP_ULONG   ulReserved;         ///< set to zero
} AVI_STD_INDEX;

/**
 @brief AVI OpenDML super index
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG   ulFourCC;           ///< must be "indx"
    MMP_ULONG   ulSize;             ///< chunk size, not including the initial 8 bytes
    MMP_USHORT  usLongsPerEntry;    ///< must be 4
    MMP_UBYTE   ubIndexSubType;     ///< must be 0 here, only points to standard indexes
    MMP_UBYTE   ubIndexType;        ///< must be AVI_INDEX_OF_INDEXES
    MMP_ULONG   ulEntriesInUse;     ///< the number of valid index entries
    MMP_ULONG   ulChunkId;          ///< ex. 00dc, 01wb
    MMP_ULONG   ulReserved[3];      ///< set to zero
} AVI_SUPER_INDEX;

typedef union _MMPF_AVIMUX_CHUNK {
    RIFF_CHUNK              riffHdr;
    LIST_CHUNK              listHdr;
    SUB_CHUNK               subchunkHdr;
    AVI_MAIN_HEADER         avih;
    AVI_STREAM_HEADER       strh;
    AVI_BITMAP_FORMAT       videoFmt;
    AVI_WAVE_FORMAT         wavFmt;
    AVI_ADPCM_FORMAT        adpcmFmt;
    AVI_AAC_FORMAT          aacFmt;
    AVI_MP3_FORMAT          mp3Fmt;
    AVI_STD_INDEX           stdIndex;
    AVI_SUPER_INDEX         superIndex;
    AVI_STD_INDEX_ENTRY     stdIndexEntry;
    AVI_SUPER_INDEX_ENTRY   superIndexEntry;
} MMPF_AVIMUX_CHUNK;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_AVIMUX_PreProcessFile(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_AddChunkPrefix(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_AddChunkSuffix(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ULONG MMPF_AVIMUX_CalcChunkPrefixSize(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ULONG MMPF_AVIMUX_CalcChunkSuffixSize(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_KeepSubIndexEntry(MMP_UBYTE chunktype, MMP_ULONG framesize, VIDENC_FRAME_TYPE frametype, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_AddSubIndexChunk(MMPF_VID_MGR_INFO* pContainer);

MMP_ERR MMPF_AVIMUX_GetRecordingSize(MMP_ULONG *ulSize, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_PostProcessFile(MMP_UBYTE storagemode, MMP_UBYTE * tmp_buf, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_GetSavedSize(MMP_ULONG AVSize, MMP_ULONG VideoCount, MMP_ULONG AudioSampleCount, MMP_ULONG AudioChunkCount, MMP_ULONG64 *total_size, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_FillTail(MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_AVIMUX_InsertDupFrame(MMPF_VID_MGR_INFO* pContainer);

MMP_BOOL MMPF_AVIMUX_IsTimeInfoNeeded(void);
MMP_BOOL MMPF_AVIMUX_IsSizeInfoNeeded(void);

#endif //(MGR_SUPPORT_AVI == 1)
#endif //_MMPF_AVIMUX_H_
