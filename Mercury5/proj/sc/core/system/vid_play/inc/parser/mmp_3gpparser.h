/**
 @file mmp_3gpparser.h
 @brief The header file of mmp_3gpparser_inc.h

 This is a common file used in firmware and the host side.

 @author Truman Yang
 @version 1.0 Original Version
*/

#ifndef _MMP_3GPPARSER_H_
#define _MMP_3GPPARSER_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define CUR_DEMUXED_VIDEO_FRAME     gVideoMedia[m_ubVideoCurTrack].ulFrameIndex

#define DEMUX_AUDIO                 (0x01)  // Demux the audio bitstream
#define DEMUX_VIDEO                 (0x02)  // Demux the video bitstream
#define DEMUX_STOP                  (0x04)  // Stop Demux
#define DEMUX_SPEED                 (0x08)  // Demux the Fast forward
#define DEMUX_SEEK                  (0x10)  // Seek the video
#define DEMUX_SEEK_FRAME            (0x20)  // Seek by frame
#define DEMUX_BS_DUMMY_SIZE         (0x20)  // Demux the A/V dummy bitstream

#define MMP_AVIPARSER_SUPPORT       1
#define MMP_TSPARSER_SUPPORT        1
#define MMP_MKVPARSER_SUPPORT       0
#define MMP_RMPARSER_SUPPORT        0
#define MMP_WMVPARSER_SUPPORT       0


#define ATOM_FTYP     MAKE_TAG_BE('f','t','y','p')  ///< QuickTime Prefs file types
#define ATOM_MDAT     MAKE_TAG_BE('m','d','a','t')  ///< Media Data Atom
#define ATOM_MVHD     MAKE_TAG_BE('m','v','h','d')  ///< Movie header Atom
#define ATOM_MOOV     MAKE_TAG_BE('m','o','o','v')  ///< Movie Atom
#define ATOM_TRAK     MAKE_TAG_BE('t','r','a','k')  ///< Track Atom
#define ATOM_UDTA     MAKE_TAG_BE('u','d','t','a')  ///< User Data Atom
#define ATOM_SKIP     MAKE_TAG_BE('s','k','i','p')  ///< Skip Atom
#define ATOM_PANA     MAKE_TAG_BE('P','A','N','A')  ///< PANA Atom

#define NALU_TYPE_SLICE    1
#define NALU_TYPE_DPA      2
#define NALU_TYPE_DPB      3
#define NALU_TYPE_DPC      4
#define NALU_TYPE_IDR      5
#define NALU_TYPE_SEI      6
#define NALU_TYPE_SPS      7
#define NALU_TYPE_PPS      8
#define NALU_TYPE_AUD      9
#define NALU_TYPE_EOSEQ    10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILL     12

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/* Buffer Access Type */
typedef enum _RINGBUF_ACCESS_TYPE {
    RING_READ   = 0,
    RING_WRITE  = 1
} RINGBUF_ACCESS_TYPE;

/* Seek Modes */
typedef enum _MMPF_M_SEEKMODE{
    MMPF_M_SEEK_NORMAL, ///< Normal mode to find the next frame
    MMPF_M_FF_KEY,      ///< Fast forward in I only based-seeking, without time-sync.
    MMPF_M_SEEK_NONE    ///< No seek at all. Used when FF to end of stream.
} MMPF_M_SEEKMODE;

/* Parser Type */
typedef enum _MMP_PSR_PARSERTYPE {
    MMP_PSR_NONE,
    MMP_PSR_3GPPARSER,
    MMP_PSR_AVIPARSER,
    MMP_PSR_MKVPARSER,
    MMP_PSR_WMVPARSER,
    MMP_PSR_RMPARSER,
    MMP_PSR_TSPARSER
} MMP_PSR_PARSERTYPE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/** Ring buffer Aligned Type */
typedef enum _MMPF_M_BS_ALIGN_TYPE{
    BS_ALIGN_NOT = 0,
    BS_ALIGN_256
} MMPF_M_BS_ALIGN_TYPE;

/** Ring buffer pointers */
typedef struct _MMPF_M_RINGBUF_PTR
{
    MMP_ULONG   ptr[2];                     ///< The read/write pointer in bytes of the buffer
    MMP_ULONG   lap[2];                     ///< The lap of the read/write pointer
    MMP_ULONG   Atoms;                      ///< The unread frame number in the buffer
} MMPF_M_RINGBUF_PTR;

/** @brief The bitstram buffer metadata
This buffer contained the compressed video frame data to feed into the video hardware.
*/
typedef struct _MMPF_M_BS_BUF_INFO
{
    MMP_ULONG               buftype;        ///< The buffer type
    MMP_ULONG               length;         ///< The total length available of the bitstream buffer
    MMP_UBYTE               *buf;           ///< The starting address of the bitstream buffer
    MMP_UBYTE               *bufend;        ///< The ending address of the bitstream buffer, used as precalculated value of buf + length
    MMPF_M_RINGBUF_PTR      ringData;       ///< The ring buffer pointers of the data
} MMPF_M_BS_BUF_INFO;

/** @brief The 3GP sample information after seeking.
Used for AV sync and demuxing.
*/
typedef struct _MMP_3GP_SAMPLE_INFO
{
    MMP_ULONG   ulOffset;                   ///< The offset in the file of the sample
    MMP_ULONG   ulSize;                     ///< The size of the sample
    MMP_LONG    lSampleTime;                ///< The tick of the sample
} MMP_3GP_SAMPLE_INFO;

/** @brief 3GP media information.
This records media track information
*/
typedef struct _MMP_3GP_MEDIA_INFO
{
    // overview
    MMP_ULONG   ulTrackID;                  ///< The track ID in 4 bytes
    MMP_ULONG   ulSTOffset[6];              ///< Offset of each sample table in the file
    MMP_ULONG   ulFrameIndex;               ///< Current frame index
    MMP_ULONG   ulFrameCount;               ///< Total frame number
    MMP_ULONG   ulLength;                   ///< The total media size in bytes
    MMP_ULONG   ulTimeScale;                ///< Time scale of current track
    MMP_LONG    lDelayTime;                 ///< The starting time within the media

    // audio stsd
    MMP_ULONG   ulSamplePerFrame;
    MMP_ULONG   ulBytesPerFrame;

    MMP_ULONG64 ulDecodingTime;             ///< The sample decoding time.
    MMP_ULONG64 ulTickPassTime;             ///< The tick passed in current 3GP file

    // elst
    MMP_LONG    lMediaTime;                 ///< The starting time within the media of this edit segment
    MMP_LONG    lMediaRate;                 ///< The relative rate to play the media

    // stsz
    MMP_ULONG   ulStszEntryCnt;             ///< The total number of sample size entries
    MMP_USHORT  usSampleSize;               ///< Sample size. Set 0 to use STSZ. Others to use the same size
    MMP_ULONG   ulPreFrameSize;             ///< Previous sample size

    // stco
    MMP_ULONG   ulStcoEntryCnt;             ///< The total number of stco atom entries
    MMP_ULONG   ulPreFrameOffset;           ///< Previous frame offset

    // stsc
    MMP_ULONG   ulStscEntryCnt;             ///< The total number of stsc atom entries
    MMP_ULONG   ulStscEntryIdx;             ///< Current stsc atom entry index
    MMP_ULONG   ulSamplePerChunk;           ///< The number of samples in this chunk
    MMP_ULONG   ulSampleIdxInChunk;         ///< Current sample index in the current chuck
    MMP_LONG    lFirstChunk;                ///< First chunk index in this stsc atom entry
    MMP_LONG    lCurChunk;                  ///< Current chunk index in this stsc atom entry
    MMP_LONG    lLastChunk;                 ///< Last chuck index in this stsc atom entry

    // stss
    MMP_ULONG   ulStssEntryCnt;             ///< The total number of stss atom entries

    // stts
    MMP_ULONG   ulSttsDuration;             ///< All samples have the same duration
    MMP_ULONG   ulSttsEntryCnt;             ///< The total number of stts atom entries
    MMP_ULONG   ulSttsEntryIdx;             ///< Current stts atom entry index
    MMP_ULONG   ulSampleIdxInSttsEntry;     ///< Current sample index in this stts atom entry
    MMP_ULONG   ulSamplesInSttsEntry;       ///< Number of samples in this stts atom entry
    MMP_LONG    lDTimeDelta;                ///< The decoding time delta in the time scale, DT(n+1) = DT(n) + STTS(n)

    // ctts
    MMP_BOOL    bCttsEnable;                ///< The ctts atom is exist or not
    MMP_ULONG   ulCttsEntryCnt;             ///< The total number of ctts atom entries
    MMP_ULONG   ulCttsEntryIdx;             ///< Current ctts atom entry index
    MMP_ULONG   ulSampleIdxInCttsEntry;     ///< Current sample index in this ctts atom entry
    MMP_ULONG   ulSamplesInCttsEntry;       ///< Number of samples in this ctts atom entry
    MMP_LONG    lCTimeOffset;               ///< The time offset between CTime and DTime, CT(n) = DT(n) + CTTS(n)
} MMP_3GP_MEDIA_INFO;

/** @brief Player seek status
*/
typedef struct _MMPF_3GPP_SEEKSTATUS {
    MMPF_M_SEEKMODE mode;                   ///< Current seek mode
    MMP_SHORT       sSpeed;                 ///< The play speed
    MMP_SHORT       sAdvance;               ///< Number of frames to be advanced
    MMP_LONG        ulFFIndex;              ///< Index of Fast forward search frame in the sample atom table. Used in FF and FW search
    MMP_ULONG       ulRequestFrame;         ///< It's used to reduce the FW seeking error.
    MMP_ULONG       ulTempFrame;            ///< The starting frame of the current chunk
    MMP_LONG        lChunkToLoad;           ///< The chuck to load in the next time. Used in seek only
    MMP_ULONG       ulTargetFrame;          ///< The target seek frame
    MMP_ULONG       play_duration;
} MMPF_3GPP_SEEKSTATUS;

#endif //_MMP_3GPPARSER_H_
