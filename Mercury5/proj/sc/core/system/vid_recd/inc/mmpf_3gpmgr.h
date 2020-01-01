/**
 @file mmpf_3gpmgr.h
 @brief Header function of 3gp processor
 @author Will Tseng, Truman Yang
 @version 1.1 Add constant and struction section to sync with the host
 @version 1.0 Original Version
*/

#ifndef _MMPF_3GPMGR_H_
#define _MMPF_3GPMGR_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_err.h"
#include "mmp_media_def.h"
#include "mmp_vidrec_inc.h"
#include "vm_types.ht"

/** @addtogroup MMPF_3GPP
@{
*/

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

#define MGR_SUPPORT_AVI             (1)
#define MGR_SUPPORT_AVI_IDX1        (1)

#define MGR_AUDIO_DATA_FLAG         (0xFF000000)
#define MGR_AUDIO_DATA_MASK         (0x00FFFFFF)

// For Multi-Track
#define MGR_VIDEO_DATA_MASK_MULTI   (0x0FFFFFFF)
#define MGR_TRACK_FLAG_MULTI        (0x30000000)

#define MGR_VIDEO_DATA_MASK         (0x3FFFFFFF)
#define MGR_TRACK_FLAG              (0x30000000)

#define MGR_FRAME_TYPE_MASK         (0xC0000000)
#define MGR_FRAME_TYPE_I            (0x40000000)
#define MGR_FRAME_TYPE_P            (0x80000000)
#define MGR_FRAME_TYPE_B            (0xC0000000)

#define MGR_AUD_FRM_SIZE_BYTES      (2)
#define MGR_AUD_FRM_TIME_BYTES      (4)
#define MGR_AUD_FRM_HDR_SIZE        (MGR_AUD_FRM_SIZE_BYTES + MGR_AUD_FRM_TIME_BYTES)

#define CHUNK_VIDEO                 (0)
#define CHUNK_AUDIO                 (1)
#define CHUNK_VIDEO_2               (2)

#define UVC_VIDEO_FRAME             (0)
#define UVC_AUDIO_FRAME             (1)

#define FRAME_TABLE                 (0)
#define TIME_TABLE                  (1)
#define AUX_TABLE_NUM               (2)

#if (EMERGENTRECD_SUPPORT)
#define KEEP_CONTAINER_GAP          (10)
#endif

/* MIO player can't play the recording file for file has plenty of audio frames
 * in beginning file. Limit the audio frames to MAX_AUDIO_FRAMEBUF.
 */
#define MGR_AUDIO_SUPPORT_MIOPLAYER (1)
#define MAX_AUDIO_FRAMEBUF          (3)

#if (SUPPORT_VR_REFIX_TAILINFO)
#define FIXED_TAIL_SAVE_HEAD        (0)
#define FIXED_TAIL_SAVE_CONTAINER   (8)
#define FIXED_TAIL_SAVE_TAILSIZE    (8+sizeof(MMPF_VID_MGR_INFO))
#define FIXED_TAIL_SAVE_TAILDATA    (8+sizeof(MMPF_VID_MGR_INFO)+4)
#define FIXED_TAILINFO_FILESIZE     (4*1024*1024)
#define FIXED_TAIL_SAVED_AVNUM      (10)
#endif

/* During muxing audio frames, break muxing audio while the muxed audio time
 * will be longer than muxed video time
 */
#define MGR_AUD_FIT_VID_MUX_TIME    (0)

/*
 * Insert SPS and PPS as the dummy frame
 */
#define MGR_SPSPPS_AS_DUMMY_FRM     (0)

/**
 @brief Select AVI muxer version to use
*/
#define AVI_1_0_MUXER               (1)
#define AVI_2_0_MUXER               (2)

#if (VIDRECD_MULTI_TRACK == 1) // Currently only AVI 1.0 supports multi-tracks
#define AVI_VERSION                 AVI_1_0_MUXER   ///< supported AVI muxer version
#else
#define AVI_VERSION                 AVI_2_0_MUXER   ///< supported AVI muxer version
#endif

#if (AVI_VERSION == AVI_2_0_MUXER)
#define AVI_SEG_INDEXES             (1)   ///< several segmented sub-indexes to speed up post processing
#if (VIDENC_SEAMLESS == 1) && (AVI_SEG_INDEXES == 0)
    #error To support seamless video recording, segmented subindex feature must be enabled
#endif
#else
#define AVI_SEG_INDEXES             (0)   ///< only one sub-index for each stream
#endif

/**
 @brief predefined num of entries per sub-index & per super index
*/
#if (AVI_SEG_INDEXES == 1)
#define AVI_STD_INDEX_ENTRY_CNT     (900)   ///< 30fps * 30 sec
///< For 5-hr video, 600 * 30 sec, prefer size of super index entries is 512x for performance
#define AVI_SUPER_INDEX_ENTRY_CNT   (640)   ///< 640 * 16 byte per entry
#else
#define AVI_SUPER_INDEX_ENTRY_CNT   (1)     ///< 1 * 16 bytes per entry
#endif

/* Storage Range Type */
#if 0//(SUPPORT_SHARE_REC) // TBD
#define MMPF_3GPMGR_SAVE_AV_PART            (~(MMP_ULONG)0x3ffff)   ///< mask of moving 256K bytes AV data
#else
#define MMPF_3GPMGR_SAVE_AV_PART            (~(MMP_ULONG)0xffff)    ///< mask of moving 64K bytes AV data
#endif
#define MMPF_3GPMGR_SAVE_AV_FULL            ((MMP_ULONG)0xffffffff) ///< mask of moving all AV data
#define MMPF_3GPMGR_SAVE_FT_PART            (0)     ///< flag of moving 512 bytes frame table
#define MMPF_3GPMGR_SAVE_FT_FULL            (1)     ///< flag of moving all frame table

/* Frame Info Queue Size */
#define MMPF_MGR_FRAME_QUEUE_SIZE           (1023)  ///< queue of frame size for data transfer

/* Frame Marker */
#define MMPF_3GPMGR_EOF_MARKER              (0xFFFFFE0F)
#define MMPF_3GPMGR_TIMETBL_HDR_MARKER      (0xFFFFFFFF)

/* Misc */
#define MMPF_MGR_MAX_FILENAME_LEN           (256)
#define MMPF_MGR_MAX_USR_DATA_LEN           (128)
#define MMPF_MGR_INVALID_FILE_ID            (0)
#define MMPF_MGR_NAME_LEN                   (12)
#define MMPF_MGR_METADATA_MAX_LEN           (64)

#define MMPF_MGR_LONG_TIME_SIZE_LIMIT       (0xE0000000) // SIGNLE_FILE_SIZE_LIMIT_3_5G

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

// Video Merger TX Status
typedef enum _MMPF_VIDMGR_TX_STAT {
    MMPF_VIDMGR_TX_STAT_NONE = 0,
    MMPF_VIDMGR_TX_STAT_OPEN,
    MMPF_VIDMGR_TX_STAT_CLOSE
} MMPF_VIDMGR_TX_STAT;

// Video Callback Type
typedef enum _MMPF_3GPMGR_CB_TYPE {
    MMPF_3GPMGR_CB_NONE             = 0x0000,
    MMPF_3GPMGR_MEDIA_FULL          = 0x0001,
    MMPF_3GPMGR_RECDSTOP_CARDSLOW   = 0x0002,
    MMPF_3GPMGR_SLOW_MEDIA          = 0x0004,
    MMPF_3GPMGR_SEAMLESS            = 0x0008,
    MMPF_3GPMGR_MEDIA_ERROR         = 0x0010,
    MMPF_3GPMGR_APSTOP_VIDRECD      = 0x0020,
    MMPF_3GPMGR_SIZE_MEET           = 0x0040,
    MMPF_3GPMGR_PRMRECD_TIMEMEET    = 0x0080,
    MMPF_3GPMGR_SCDRECD_TIMEMEET    = 0x0100,
    MMPF_3GPMGR_TRDRECD_TIMEMEET    = 0x0200,
    MMPF_3GPMGR_UVCRECD_TIMEMEET    = 0x0400,
    MMPF_3GPMGR_EMERG_TIMEMEET      = 0x0800,
    MMPF_3GPMGR_LONG_TIME_SIZE_MEET = 0x1000,
    MMPF_3GPMGR_CB_NUM
} MMPF_3GPMGR_CB_TYPE;

// Stream Callback Type
typedef enum _MMPF_VIDRECD_STREAMCB_TYPE {
    MMPF_VIDRECD_STREAMCB_VIDMOVE = 0,      // move video stream
    MMPF_VIDRECD_STREAMCB_VIDUPDATE,        // update video stream
    MMPF_VIDRECD_STREAMCB_AUDMOVE,          // move audio stream
    MMPF_VIDRECD_STREAMCB_AUDUPDATE         // update audio stream
} MMPF_VIDRECD_STREAMCB_TYPE;

#if (UVC_VIDRECD_SUPPORT)
// UVC File Store Type
typedef enum _MMPF_UVCRECD_FILE_TYPE {
    MMPF_UVCRECD_MULFILE = 0,
    MMPF_UVCRECD_MULTRACK
} MMPF_UVCRECD_FILE_TYPE;
#endif

#if (SUPPORT_VUI_INFO)
typedef enum _MMPF_SEI_SHUTTER_TYPE {
    MMPF_SEI_SHUTTER_1920x1080_29d97 = 0,
    MMPF_SEI_SHUTTER_1280x720_59d94,
    MMPF_SEI_SHUTTER_1280x720_29d97,
    MMPF_SEI_SHUTTER_848x480_29d97,
    MMPF_SEI_SHUTTER_NONE
} MMPF_SEI_SHUTTER_TYPE;

typedef struct _MMPF_SEI_SHUTTER_TABLE {
    MMP_ULONG  ulShuSpd;
    MMP_USHORT usValue;
} MMPF_SEI_SHUTTER_TABLE;
#endif

#if (SUPPORT_VR_REFIX_TAILINFO)
typedef enum _MMPF_REFIXRECD_UPDATE {
    MMPF_REFIXRECD_UPDATE_VIDFRAME = 0,
    MMPF_REFIXRECD_UPDATE_AUDFRAME,
    MMPF_REFIXRECD_UPDATE_TAILINFOSIZE
} MMPF_REFIXRECD_UPDATE;
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/**
 @brief AVI OpenDML standard index entry
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG       ulOffset;           ///< offset is relative to ullBaseOffset of @ref AVI_STD_INDEX
    MMP_ULONG       ulsize;             ///< the size of the data
} AVI_STD_INDEX_ENTRY;

/**
 @brief AVI OpenDML super index entry
*/
typedef struct __attribute__((packed))
{
    MMP_ULONG64     ullOffset;          ///< from the start of the file to the sub-index
    MMP_ULONG       ulsize;             ///< size of the sub-index, in bytes
    MMP_ULONG       ulDuration;         ///< duration covered by the sub-index, in stream ticks.
} AVI_SUPER_INDEX_ENTRY;

typedef struct _MMPF_AVIMUX_HANDLER {
    MMP_ULONG       ulHdrlSize;
    MMP_ULONG       ulVidStrlSize;
    MMP_ULONG       ulVidStrhOffset;
    MMP_ULONG       ulVidStrfOffset;
    MMP_ULONG       ulVidStrfSize;
    MMP_ULONG       ulAudStrlSize;
    MMP_ULONG       ulAudStrhOffset;
    MMP_ULONG       ulAudStrfOffset;
    MMP_ULONG       ulAudStrfSize;
    MMP_ULONG       ulAudStrlJunkSize;
    #if (AVI_IDIT_CHUNK_EN)
    MMP_ULONG       ulIditOffset;
    #endif
    MMP_ULONG       ulMoviOffset;
    #if (AVI_VERSION == AVI_2_0_MUXER)
    MMP_ULONG       ulVidIndxOffset;
    MMP_ULONG       ulVidIndxSize;
    MMP_ULONG       ulAudIndxOffset;
    MMP_ULONG       ulAudIndxSize;
    #if (AVI_SEG_INDEXES == 0)
    MMP_ULONG64     ulVidCurIxOffset;               ///< file offset to current video sub-index
    MMP_ULONG64     ulAudCurIxOffset;               ///< file offset to current audio sub-index
    #else
    MMP_ULONG       ulVidIxCnt;                     ///< total number of video sub-indexes
    MMP_ULONG       ulAudIxCnt;                     ///< total number of audio sub-indexes
    MMP_ULONG       ulVidIxEntryCnt;                ///< total number of entries in current video sub-index
    MMP_ULONG       ulAudIxEntryCnt;                ///< total number of entries in current audio sub-index
    MMP_ULONG       ulIxRelativeOffset;             ///< relative offset to data chunk in sub-index entries
    MMP_ULONG64     ullIxBaseOffset;                ///< the base offset to the data chunk in sub-index
    #endif
    #endif
} MMPF_AVIMUX_HANDLER;

typedef struct _MMPF_VID_MGR_INFO {
    // Common Information
    MMP_UBYTE       ubName[MMPF_MGR_NAME_LEN];      ///< Container name
    MMP_USHORT      usStreamType;                   ///< Stream type
    MMP_USHORT      usPairStrmType;                 ///< Stream type of it's partner (normal <-> emergency)
    void            *pEncInfo;                      ///< Encoder information
    void            *pCompHandle;                   ///< Component handle
    void            *pEmergBaseMgr;                 ///< Base merger handle for emergency merger
    MMP_BOOL        bWaitKeyFrame;                  ///< Wait key frame or not
    MMP_BOOL        bRecdEn;                        ///< Merger enable
    MMP_BOOL        bRecdStart;                     ///< Record start status
    MMP_BOOL        bEmergRecd;                     ///< Is emergency record
    MMP_BOOL        bBitstreamDropped;              ///< Bitstream dropped or not
    MMPF_VIDMGR_TX_STAT eRecdTxStatus;              ///< Merger Tx status
    MMPF_VIDMGR_TX_STAT eRecdTxOp;                  ///< Merger Tx operation
    volatile MMP_BOOL   bEndOfFrame;                ///< End of frame status

    // GOP Information
    MMP_USHORT      usGOPSize;                      ///< GOP size
    MMP_USHORT      usPFrameCount;                  ///< P frames count in one GOP
    MMP_USHORT      usBFrameCount;                  ///< Number of consecutive B frames

    // Video Encode Parameters
    MMP_BOOL        bVideoTrackAvailable;           ///< Is there any video track
    MMP_USHORT      usVidEncFormat;                 ///< Video encode format
    MMP_ULONG       ulFrameWidth;                   ///< Video frame width
    MMP_ULONG       ulFrameHeight;                  ///< Video frame height
    VIDENC_FPS_CTL  stFrameRate;                    ///< Video frame rate
    VIDRECD_USEMODE eVidEncUseMode;                 ///< Encode use mode
    MMP_ULONG       ulPreEncDuration;               ///< Pre-encode duration
    MMP_ULONG       ulEndOfFrmTime;                 ///< End of frame time

    // Audio Encode Parameters
    MMP_BOOL        bAudioTrackAvailable;           ///< Is there any audio track
    MMP_USHORT      usAudioEncFormat;               ///< Audio encode format
    MMP_ULONG       ulAudioSampleFreq;              ///< Audio sample frequency. i.e. 22050.
    MMP_ULONG       ulAudioBitRate;                 ///< Audio bitrate
    MMP_UBYTE       ubAudioChannelNo;               ///< Audio record channel count. i.e. 1/2
    MMP_ULONG       ulAMRSampleSize;                ///< Audio AMR frame size base on sampling rate

    // Statistic Information
    MMP_ULONG       ulVidRecdFrmCount;              ///< Accumulated encoded frame count
    MMP_ULONG       ulVideoChunkCount;              ///< Video chunk count
    MMP_ULONG       ulVideoDataFetch;               ///< Data size that sent to repack buffer
    MMP_ULONG       ulAudioSampleCount;             ///< Audio sample count (for m_bOneAudioFramePerChunk is TRUE)
    MMP_ULONG       ulAudioChunkCount;              ///< Audio chunk count (for m_bOneAudioFramePerChunk is FALSE)
    MMP_ULONG       ulAudioFrameCount;              ///< Audio frame count
    MMP_ULONG       ulAudioDataFetch;               ///< Data size that sent to repack buffer
    MMP_ULONG       ulAVSizeProduced;               ///< AV data size that sent to repack buffer
    MMP_ULONG       ulMgrCurFileSize;               ///< Current encoded file size
    MMP_ULONG       ulMgrFinalFileSize;             ///< Final encoded file size
    MMP_ULONG       ulTotalSkipCount;               ///< Video skip setting
    MMP_ULONG       ulContiSkipCount;               ///< Video skip setting

    // Time Information
    MMP_ULONG       ulVideoTotalTime;               ///< Video total time, update every frame
    MMP_ULONG       ulAudioTotalTime;               ///< Audio total time duration
    MMP_ULONG       ul3GPCreateTime;                ///< File create time
    MMP_ULONG       ul3GPModifyTime;                ///< File modify time
    MMP_ULONG       ulVidRecdBaseTime;              ///< Time of start capture
    MMP_ULONG       ulVidMgrBaseTime;               ///< Time of start capture, for calculate video total time & fill tail

    // Video Speed Control Parameters
    MMP_UBYTE       ubVidSpeedMode;                 ///< Video speed mode
    MMP_UBYTE       ubVidSpeedRatio;                ///< Video speed ratio

    // Meta data
    MMP_ULONG       MetaDataLength[2];
    MMP_UBYTE       MetaData[2][MMPF_MGR_METADATA_MAX_LEN];
    MMP_USHORT      usProfile;
    MMP_USHORT      usLevel;

    // Video Frame Queue index Parameters
    MMP_ULONG       ulFrmQueueReadIdx;              ///< Read-out index of frame queue
    MMP_ULONG       ulFrmQueueWriteIdx;             ///< Write-in index of frame queue
    MMP_ULONG       ulFrmQueueReadWrap;             ///< Read wrap count for frame queue
    MMP_ULONG       ulFrmQueueWriteWrap;            ///< Write wrap count for frame queue
    MMP_ULONG       *pulFrameSizeQ;                 ///< Pointer to frame size queue
    MMP_ULONG       *pulFrameTimeQ;                 ///< Pointer to frame time queue
    VIDENC_FRAME_TYPE   *peFrameTypeQ;              ///< Pointer to frame type queue

    // Video Compress Buffer Parameters
    MMP_ULONG       ulVidCompBufAddr;               ///< Video recording buffer address
    MMP_ULONG       ulVidCompBufSize;               ///< Video recording buffer size
    MMP_ULONG       ulVidCompBufReadPtr;            ///< Read-out address of video encoded compressed buffer
    MMP_ULONG       ulVidCompBufWritePtr;           ///< Write-in address of video encoded compressed buffer
    MMP_ULONG       ulVidCompBufReadWrap;           ///< Wrap times of read pointer
    MMP_ULONG       ulVidCompBufWriteWrap;          ///< Wrap times of write pointer
    MMP_ULONG       ulVidCompBufFreeSize;           ///< Maximum free size for next frame
    MMP_ULONG       ulVidCompBufFreeSizeStatus;     ///< Compress buffer free size status
    MMP_ULONG       ulVidCompBufNearRingThd;        ///< Threshold for near ring buffer mode
    MMP_BOOL        bVidCompBufNearRingEn;          ///< Near ring buffer mode enable

    // Audio Compress Buffer Parameters
    MMP_ULONG       ulAudCompBufAddr;               ///< Audio recording buffer address
    MMP_ULONG       ulAudCompBufSize;               ///< Audio recording buffer size
    MMP_ULONG       ulAudCompReadPtr;               ///< Read-out pointer of audio compressed buffer
    MMP_ULONG       ulAudCompWritePtr;              ///< Write-in pointer of audio compressed buffer
    MMP_ULONG       ulAudCompReadWrap;              ///< Wrap times of read-out pointer
    MMP_ULONG       ulAudCompWriteWrap;             ///< Wrap times of write-in pointer
    MMP_ULONG       ulAudCompBufTotalRead;          ///< Total read-out size of audio encoded compressed buffer

    // Repack Buffer Parameters
    MMP_ULONG       ulAVRepackBufStart;             ///< Start address of AV repack buffer
    MMP_ULONG       ulAVRepackBufSize;              ///< Size of AV repack buffer
    MMP_ULONG       ulAVRepackReadPtr;              ///< Read-out pointer of AV repack buffer
    MMP_ULONG       ulAVRepackWritePtr;             ///< Write-in pointer of AV repack buffer
    MMP_ULONG       ulAVRepackReadWrap;             ///< Wrap times of read-out pointer
    MMP_ULONG       ulAVRepackWriteWrap;            ///< Wrap times of write-in pointer

    // Aux Table Parameters
    MMP_ULONG       ulAuxTableBufStart[AUX_TABLE_NUM];  ///< Start address of frame table/time table buffer
    MMP_USHORT      usAuxTableBufSize[AUX_TABLE_NUM];   ///< Size of frame table/time table buffer
    MMP_USHORT      usAuxTableReadPtr[AUX_TABLE_NUM];   ///< Read-out pointer of frame table/time table buffer
    MMP_USHORT      usAuxTableWritePtr[AUX_TABLE_NUM];  ///< Write-in pointer of frame table/time table buffer
    MMP_USHORT      usAuxTableReadWrap[AUX_TABLE_NUM];  ///< Wrap times of read-out pointer
    MMP_USHORT      usAuxTableWriteWrap[AUX_TABLE_NUM]; ///< Wrap times of write-in pointer

    // Tail Buffer Parameters
    MMP_ULONG       ulSpeedAuxTableBufStart[AUX_TABLE_NUM]; ///< Start address of frame table/time table buffer
    MMP_ULONG       ulSpeedAuxTableBufOffset;       ///< Current offset of frame table/time table buffer
    MMP_ULONG       ulVidTailAddr;
    MMP_ULONG       ulVidCurTailAddr;
    MMP_ULONG       ulVidTailSize;
    MMP_BOOL        bVidTailHighSpeedMode;

    // File Parameters
    MMP_BYTE        bRecdFileName[MMPF_MGR_MAX_FILENAME_LEN];
    MMP_ULONG       ulRecdFileID;
    MMP_BOOL        bKeep2NextFileEnabled;
    MMP_ULONG       ulKeep2NextFileTime;
    MMP_ERR         eFileStatus;                    ///< Merger file status
    MMP_BOOL        bFormatFree;                    ///< Format free enable

    // AVI-info Parameters
    #if (MGR_SUPPORT_AVI == 1)
    MMPF_AVIMUX_HANDLER      m_aviHandler;
    #endif
    #if (AVI_SEG_INDEXES == 1)
    AVI_STD_INDEX_ENTRY      m_vidStdIndexEntries[AVI_STD_INDEX_ENTRY_CNT];
    AVI_STD_INDEX_ENTRY      m_audStdIndexEntries[AVI_STD_INDEX_ENTRY_CNT];
    AVI_SUPER_INDEX_ENTRY    m_vidSuperIndexEntries[AVI_SUPER_INDEX_ENTRY_CNT];
    AVI_SUPER_INDEX_ENTRY    m_audSuperIndexEntries[AVI_SUPER_INDEX_ENTRY_CNT];
    #endif

    // User Data
    MMP_BYTE        bUserDataBuf[MMPF_MGR_MAX_USR_DATA_LEN];
    MMP_USHORT      usUserDataLength;

    // VR Thumbnail
    MMP_BOOL        bVRThumbEn;
    MMP_UBYTE       ubVRThumbRingType;
    MMP_UBYTE       ubVRThumbBufType;
    MMP_BYTE        ubHasKeep1stIdx;
    MMP_BYTE        ubInsPanaAtom;
    MMP_ULONG       ulSkipAtomSize;
    MMP_ULONG       ulThumbnailAddr;
    MMP_ULONG       ulThumbnailSize;
    MMP_ULONG       ulProgCnt;          // NO USE
    MMP_ULONG       ulThumbIdx;         // NO USE

    // Multiple Track
    MMP_ULONG       ulTrackNum;
    MMP_BOOL        bMultiTrackEn;                  ///< Be multi-track of primary record file. Use same repack and aux buffer and different AV compress buffer.
    MMP_BOOL        bMultiTrackMuxEn;               ///< Be multi-track of primary record file. For muxer use.
    void            *pMultiTrackBaseMgr;            ///< Base merger handle for multi-track
    void            *pNextTrackMgr;
} MMPF_VID_MGR_INFO;

#if (SUPPORT_VR_REFIX_TAILINFO)
typedef struct _MMPF_REFIXVIDREC_CTL {
    MMP_BYTE        bRecdFileName[MMPF_MGR_MAX_FILENAME_LEN];
    MMP_ULONG       ulRecdFileID;
    MMP_BYTE        bTailFileName[MMPF_MGR_MAX_FILENAME_LEN];
    MMP_ULONG       ulTailFileID;
    MMP_ULONG       ulTempBufAddr;
    MMP_ULONG       ulTempBufSize;
    MMP_ULONG       ulAVRepackBufStart;
    MMP_ULONG       ulAVRepackBufSize;
    MMP_ULONG       ulVidTailAddr;
    MMP_ULONG       ulVidTailSize;
    MMP_ULONG       ulSavedPtr;
    MMP_ULONG       ulTableReadPtr[2];
    MMP_ULONG       ulTableReadWrap[2];
} MMPF_REFIXVIDREC_CTL;
#endif

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

// Video record callback functions
typedef void        (MMPF_VIDMGR_NoArguCBFunc) (void);
typedef void        (MMPF_VIDMGR_1ArguCBFunc) (MMP_ULONG ulPara1);
typedef void        (MMPF_VIDMGR_2ArguCBFunc) (MMP_ULONG ulPara1, MMP_ULONG ulPara2);
typedef void        (MMPF_VIDMGR_4ArguCBFunc) (MMP_ULONG ulPara1, MMP_ULONG ulPara2, MMP_ULONG ulPara3, MMP_ULONG ulPara4);
typedef MMP_ULONG   (MMPF_VIDMGR_MuxCallback) (MMP_ERR (*VIDMUX_Write)(void *buf, MMP_ULONG size, MMP_ULONG *wr_size, MMP_ULONG ulFileID), MMP_ULONG ulFileID, MMP_USHORT usStreamType);
typedef MMP_BOOL    (MMPF_VIDMGR_StreamCallback) (MMP_M_STREAMCB_ACTION cbmode, MMP_ULONG framesize, MMP_M_STREAM_INFO* moveinfo);

// Muxer modulation functions
typedef MMP_ERR     (VIDMUX_PreProcessFile_Func)(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_PostProcessFile_Func)(MMP_UBYTE storagemode, MMP_UBYTE * tmp_buf, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_FillTail_Func)(MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_GetSavedSize_Func)(MMP_ULONG AVSize, MMP_ULONG VideoCount, MMP_ULONG AudioSampleCount, MMP_ULONG AudioChunkCount, MMP_ULONG64 *total_size, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_GetRecordingSize_Func)(MMP_ULONG *ulSize, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_AddChunkPrefix_Func)(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_AddChunkSuffix_Func)(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ULONG   (VIDMUX_CalcChunkPrefixSize_Func)(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ULONG   (VIDMUX_CalcChunkSuffixSize_Func)(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_InsertDupFrame_Func)(MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_KeepIndexEntry_Func)(MMP_UBYTE chunktype, MMP_ULONG framesize, VIDENC_FRAME_TYPE frametype, MMPF_VID_MGR_INFO* pMerger);
typedef MMP_ERR     (VIDMUX_AddIndexChunk_Func)(MMPF_VID_MGR_INFO* pMerger);
typedef MMP_BOOL    (VIDMUX_IsTimeInfoNeeded_Func)(void);
typedef MMP_BOOL    (VIDMUX_IsSizeInfoNeeded_Func)(void);
typedef MMP_BOOL    (VIDMUX_IsIndexInfoNeeded_Func)(void);

typedef void        (VIDMUX_SetAudEncOp_Func)(MMP_USHORT op);
typedef MMP_ULONG   (VIDMUX_GetAudEncFrameCnt_Func)(void);
typedef void        (VIDMUX_GetAudEncParam_Func)(MMP_ULONG *bitrate, MMP_ULONG *sampleRate);
#if (VR_AUD_TIME_ALWAYS_LONGER)||(VR_MIX_FPS_WITH_AUD)
typedef void        (VIDMUX_GetAudSilenceFrm_Func)(MMP_UBYTE **bs, MMP_ULONG *size);
#endif

/* Tx To Repack Buffer function */
typedef MMP_ERR     (*pfVIDMGR_TxData2Repack)(MMP_UBYTE ubStorageMode, MMPF_VID_MGR_INFO *pMerger);

//==============================================================================
//
//                              MODULATION
//
//==============================================================================

// Muxer modulation
typedef struct _MMPF_VIDMUX_FUNC
{
    /* Muxing functions */
    VIDMUX_PreProcessFile_Func      *VIDMUX_PreProcessFile;
    VIDMUX_PostProcessFile_Func     *VIDMUX_PostProcessFile;
    VIDMUX_FillTail_Func            *VIDMUX_FillTail;
    VIDMUX_GetSavedSize_Func        *VIDMUX_GetSavedSize;
    VIDMUX_GetRecordingSize_Func    *VIDMUX_GetRecordingSize;
    VIDMUX_AddChunkPrefix_Func      *VIDMUX_AddChunkPrefix;
    VIDMUX_AddChunkSuffix_Func      *VIDMUX_AddChunkSuffix;
    VIDMUX_CalcChunkPrefixSize_Func *VIDMUX_CalcChunkPrefixSize;
    VIDMUX_CalcChunkSuffixSize_Func *VIDMUX_CalcChunkSuffixSize;
    VIDMUX_InsertDupFrame_Func      *VIDMUX_InsertDupFrame;
    VIDMUX_KeepIndexEntry_Func      *VIDMUX_KeepIndexEntry;
    VIDMUX_AddIndexChunk_Func       *VIDMUX_AddIndexChunk;
    VIDMUX_IsTimeInfoNeeded_Func    *VIDMUX_IsTimeInfoNeeded;
    VIDMUX_IsSizeInfoNeeded_Func    *VIDMUX_IsSizeInfoNeeded;
    /* Audio encoder functions */
    VIDMUX_SetAudEncOp_Func         *VIDMUX_SetAudEncOp;
    VIDMUX_GetAudEncFrameCnt_Func   *VIDMUX_GetAudEncFrameCnt;
    VIDMUX_GetAudEncParam_Func      *VIDMUX_GetAudEncParam;
    #if (VR_AUD_TIME_ALWAYS_LONGER)||(VR_MIX_FPS_WITH_AUD)
    VIDMUX_GetAudSilenceFrm_Func    *VIDMUX_GetAudSilenceFrm;
    #endif
} MMPF_VIDMUX_FUNC;

typedef struct _MMPF_VIDMGR_DATA2REPACK_ACTION {
    MMPF_VID_MGR_INFO       *pCurMgr;
    MMP_ERR                 eVidStatus;
    MMP_ERR                 eAudStatus;
    pfVIDMGR_TxData2Repack  pfVidMgrTxVid2Repack;
    pfVIDMGR_TxData2Repack  pfVidMgrTxAud2Repack;
} MMPF_VIDMGR_DATA2REPACK_ACTION;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMPF_VID_MGR_INFO PrmRecdMgr;
extern MMPF_VID_MGR_INFO PrmEmergMgr;
extern MMPF_VID_MGR_INFO ScdRecdMgr;
extern MMPF_VID_MGR_INFO ScdEmergMgr;
extern MMPF_VID_MGR_INFO TrdRecdMgr;
extern MMPF_VID_MGR_INFO TrdEmergMgr;
extern MMPF_VID_MGR_INFO UvcRecdMgr;
extern MMPF_VID_MGR_INFO UvcEmergMgr;
#if (SUPPORT_H264_WIFI_STREAM)
extern MMPF_VID_MGR_INFO PrmStreamMgr;
extern MMPF_VID_MGR_INFO ScdStreamMgr;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/* Event Handle Function */
void        MMPF_VIDMGR_GetMergerErrStatus(MMP_ERR *peMgrStatus);
MMP_BOOL    MMPF_VIDMGR_IsCardWriteCorrect(void);
MMP_BOOL    MMPF_VIDMGR_IsCardSlowStop(void);
MMP_BOOL    MMPF_VIDMGR_IsCardSlowStopDone(void);
void        MMPF_VIDMGR_SetCardSlowStop(MMP_BOOL bStop);
void        MMPF_VIDMGR_SetSlowMediaDetected(MMP_BOOL bDetected);
void        MMPF_VIDMGR_ChkRecdStopEnable(MMP_USHORT usStreamType);
void        MMPF_VIDMGR_SetVidRecdCBType(MMPF_3GPMGR_CB_TYPE eType);
MMP_ERR     MMPF_VIDMGR_StorageErrStopProcess(void);

/* File Operation Function */
MMP_ULONG   MMPF_VIDMGR_GetFileID(MMP_USHORT usStreamType);
MMP_ERR     MMPF_VIDMGR_CloseFile(MMP_ULONG *pulFileID);
MMP_ERR     MMPF_VIDMGR_GetFilePos(MMP_ULONG64 *pu64Pos, MMP_ULONG ulFileID);
MMP_ERR     MMPF_VIDMGR_SeekFile(MMP_LONG64 llOffset, MMP_LONG lOrigin, MMP_ULONG ulFileID) ;
MMP_ERR     MMPF_VIDMGR_WriteFile(void *pvData, MMP_ULONG ulNumBytes, MMP_ULONG *pulWriteCount, MMP_ULONG ulFileID);
MMP_ERR     MMPF_VIDMGR_ReadFile(void *pvData, MMP_ULONG ulNumBytes, MMP_ULONG *pulReadCount, MMP_ULONG ulFileID);

/* Buffer Operation Function */
void        MMPF_VIDMGR_DmaMoveData(MMP_ULONG ulSrcAddr, MMP_ULONG ulDstAddr, MMP_ULONG ulCount);
void        MMPF_VIDMGR_SetBELong(MMP_UBYTE *ptr, MMP_ULONG ulVal);
void        MMPF_VIDMGR_SetLELong(MMP_UBYTE *ptr, MMP_ULONG ulVal);
MMP_ERR     MMPF_VIDMGR_InsertDupFrame(MMPF_VID_MGR_INFO* pMerger);

/* Audio Compress Buffer Operation Function */
MMP_ERR     MMPF_VIDMGR_GetAudioCompBufReadPtr(MMP_ULONG *pulReadPtr, MMP_ULONG *pulReadWrap);

/* Video Compress Buffer Operation Function */
void        MMPF_VIDMGR_DMAMove2VidCompBuf(MMP_ULONG ulSrcAddr, MMP_ULONG ulSize, MMPF_VID_MGR_INFO *pMerger);

/* Frame Queue Buffer Operation Function */
void        MMPF_VIDMGR_KeepSizeToFrameQueue(MMP_ULONG ulCurSize, MMP_ULONG ulCurTime, VIDENC_FRAME_TYPE eCurType, MMPF_VID_MGR_INFO* pMerger);
void        MMPF_VIDMGR_PutEofMarkToFrameQueue(MMPF_VID_MGR_INFO* pMerger);

/* Repack Buffer Operation Function */
MMP_ERR     MMPF_VIDMGR_CompressBuf2RepackBuf(MMP_ULONG ulSrcAddr, MMP_ULONG ulSize, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_DirectWriteRepackBuf(MMP_ULONG ulSrcAddr, MMP_ULONG ulSize, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_DirectWriteRepackBuf_PatFill(MMP_UBYTE ubPat, MMP_ULONG ulSize, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_EmitBEBytes2RepackBuf(MMP_UBYTE ubByteCnt, MMP_ULONG ulVal, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_EmitLEBytes2RepackBuf(MMP_UBYTE ubByteCnt, MMP_ULONG ulVal, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_GetFreeRepackSize(MMP_ULONG *pulFreeSpace, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_AVRepackBuf2Storage(MMP_ULONG ulSaveMask, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_SyncRepackAuxBufInfo(MMPF_VID_MGR_INFO *pSrcMgr, MMPF_VID_MGR_INFO *pDstMgr);

/* Tail AuxTable Operation Function */
MMP_ERR     MMPF_VIDMGR_GetFrameTableEntry(MMP_ULONG ulOffset, MMP_ULONG *pulRetSize, MMPF_VID_MGR_INFO *pMerger);
MMP_ERR     MMPF_VIDMGR_GetTimeTableEntry(MMP_ULONG ulOffset, MMP_ULONG *pulRetTime, MMPF_VID_MGR_INFO *pMerger);

/* Merger Time Tick Function */
void        MMPF_VIDMGR_SetBaseTime(MMP_ULONG ulTimeCnt, MMPF_VID_MGR_INFO *pMerger);
void        MMPF_VIDMGR_SetTimeCounter(MMP_ULONG ulTimeCnt);
MMP_ULONG   MMPF_VIDMGR_GetTimeCounter(void);

/* Common Merger Config Function */
MMPF_VID_MGR_INFO* MMPF_VIDMGR_GetContainer(MMP_USHORT usStreamType);
VIDENC_FRAME_TYPE MMPF_VIDMGR_GetVidRecdFrameType(MMP_USHORT usStreamType, MMP_ULONG ulEncFrameNum);
MMP_ULONG   MMPF_VIDMGR_GetInstIdFromStreamType(MMP_USHORT usStreamType);
MMP_ERR     MMPF_VIDMGR_GetMergerTxStatus(MMP_USHORT usStreamType, MMP_ULONG *pulTxStatus);
void        MMPF_VIDMGR_SetContainerType(MMP_UBYTE ubContainerType);
MMP_UBYTE   MMPF_VIDMGR_GetContainerType(void);
void        MMPF_VIDMGR_SetCompBufRingMode(MMP_USHORT usStreamType, MMP_BOOL bNearRingEn, MMP_ULONG ulThd);
void        MMPF_VIDMGR_SetAVRepackBufferEx(MMP_USHORT usStreamType, MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);
void        MMPF_VIDMGR_SetAuxTableBufferEx(MMP_USHORT usStreamType, MMP_UBYTE ubTableType, MMP_ULONG ulBufAddr, MMP_USHORT usBufSize);
void        MMPF_VIDMGR_SetTailBufferEx(MMP_USHORT usStreamType, MMP_BOOL bHighSpeedMode, MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);
void        MMPF_VIDMGR_SetAVCompBufEx( MMP_USHORT  usStreamType,
                                        MMP_ULONG   ulVidBufAddr,
                                        MMP_ULONG   ulVidBufSize,
                                        MMP_ULONG   ulAudBufAddr,
                                        MMP_ULONG   ulAudBufSize);
void        MMPF_VIDMGR_SetAudioSyncEncode(MMP_BOOL bSyncAudio);
MMP_BOOL    MMPF_VIDMGR_GetAudioSyncEncode(void);
void        MMPF_VIDMGR_SetAudioParam(MMP_ULONG ulSampleRate);
MMP_ERR     MMPF_VIDMGR_GetAudioParam(MMP_ULONG *pulAudSampleFreq);
MMP_ERR     MMPF_VIDMGR_SetAVFileSizeLimit(MMP_ULONG ulFileMax, MMP_ULONG ulRsvdSize, MMP_ULONG *pulRetSize);
void        MMPF_VIDMGR_SetAVFileTimeLimit(MMP_ULONG ulTimeLimit);
MMP_ULONG   MMPF_VIDMGR_GetAVFileTimeLimit(void);
void        MMPF_VIDMGR_SetEmergentFileTimeLimit(MMP_ULONG ulTimeLimit);
MMP_BOOL    MMPF_VIDMGR_ChangeCurAVFileTimeLimit(MMP_USHORT usStreamType, MMP_ULONG ulNewTimeLimit);
void        MMPF_VIDMGR_SetVideoEncodeSpeed(MMP_UBYTE ubSpeedMode, MMP_UBYTE ubSpeedRatio);
void        MMPF_VIDMGR_SetStoragePath(MMP_UBYTE ubPath);
MMP_UBYTE   MMPF_VIDMGR_GetStoragePath(void);
void        MMPF_VIDMGR_SetEncUseMode(MMP_USHORT usStreamType, MMP_ULONG ulEncUseMode);
MMP_ERR     MMPF_VIDMGR_SetFrameRate(MMP_USHORT usStreamType, MMP_ULONG ulTimeIncre, MMP_ULONG ulTimeResol);
void        MMPF_VIDMGR_SetFileName(MMP_USHORT usStreamType, MMP_ULONG ulFileNameBuf, MMP_USHORT usNameLength);
void        MMPF_VIDMGR_SetUserDataAtom(MMP_USHORT usStreamType, MMP_ULONG ulUserDataBuf, MMP_USHORT usUserDataLength);
void        MMPF_VIDMGR_SetSeamlessEnable(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_GetSeamlessEnable(void);
void        MMPF_VIDMGR_SetMuxConstFPS(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_GetMuxConstFPS(void);
void        MMPF_VIDMGR_SetMultiTrackEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_GetMultiTrackEn(void);
void        MMPF_VIDMGR_SetAVSyncMethod(MMP_UBYTE ubMethod);
MMP_UBYTE   MMPF_VIDMGR_GetAVSyncMethod(void);
void        MMPF_VIDMGR_SetGOP(MMP_USHORT usStreamType, MMP_USHORT usPFrame, MMP_USHORT usBFrame);
void        MMPF_VIDMGR_SetPreEncodeDuration(MMP_USHORT usStreamType, MMP_ULONG ulDurationMs);
MMP_ERR     MMPF_VIDMGR_Set3GPCreateModifyTimeInfo(MMP_USHORT usStreamType, MMP_ULONG ulCreateTime, MMP_ULONG ulModifyTime);
MMP_ERR     MMPF_VIDMGR_RegisterCallback(MMP_ULONG ulEvent, void *pCallback);
MMP_ERR     MMPF_VIDMGR_GetRegisteredCallback(MMP_ULONG ulEvent, void **ppvCallback);
MMP_ERR     MMPF_VIDMGR_GetRecordingTime(MMP_USHORT usStreamType, MMP_ULONG *pulTime);
MMP_ERR     MMPF_VIDMGR_GetRemainFrmTimeOffset(MMP_USHORT usStreamType, MMP_ULONG* pulTimeOfst);
MMP_ERR     MMPF_VIDMGR_SetClearCachePeriod(MMP_ULONG ulMilliSecond);
MMP_ERR     MMPF_VIDMGR_CheckRecord(MMPF_VID_MGR_INFO *pMerger);
/* UVC Merger Config Function */
void        MMPF_VIDMGR_SetUVCEncodeFormat(MMP_USHORT usStreamType, MMP_USHORT usFormat);
void        MMPF_VIDMGR_GetUVCEncodeResolution(MMP_USHORT *pusResolW, MMP_USHORT *pusResolH);
void        MMPF_VIDMGR_SetUVCEncodeResolution(MMP_USHORT usStreamType, MMP_USHORT usResolW, MMP_USHORT usResolH);
void        MMPF_VIDMGR_SetUVCEncodeSPSPPSHdr(  MMP_USHORT  usStreamType,
                                                MMP_ULONG   ulSPSAddr, MMP_ULONG ulSPSSize,
                                                MMP_ULONG   ulPPSAddr, MMP_ULONG ulPPSSize,
                                                MMP_USHORT  usProfileIDC, MMP_USHORT usLevelIDC);
void        MMPF_VIDMGR_SetUVCEncodeGOP(MMP_USHORT usStreamType, MMP_USHORT usPFrame, MMP_USHORT usBFrame);
void        MMPF_VIDMGR_SetUVCH264StreamingEnable(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_GetUVCH264StreamingEnable(void);

/* Reset Merger Function */
MMP_ERR     MMPF_VIDMGR_ResetErrFlag(void);
void        MMPF_VIDMGR_ResetMgrState(MMP_USHORT usStreamType);

/* Basic Merger Function */
MMP_ERR     MMPF_VIDMGR_GetVideoMetaData(MMPF_VID_MGR_INFO* pMerger);
MMP_ULONG   MMPF_VIDMGR_AutoCountAudioTime(MMPF_VID_MGR_INFO *pMerger);
void        MMPF_VIDMGR_SetEndOfFrameStatus(MMP_BOOL bEnable, MMP_USHORT usStrmType);
MMP_BOOL    MMPF_VIDMGR_GetEndOfFrameStatus(MMP_USHORT usStrmType);
MMP_BOOL    MMPF_VIDMGR_GetSkipFrameOption(MMP_ULONG ulThreshold, MMPF_VID_MGR_INFO* pMerger);

/* Primary Record Function */
MMP_BOOL    MMPF_VIDMGR_IsPrmRecdEn(void);
MMP_BOOL    MMPF_VIDMGR_IsPrmRecdStart(void);

/* Emergency Record Function */
void        MMPF_VIDMGR_SetPrmEmergEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsPrmEmergEn(void);
void        MMPF_VIDMGR_SetScdEmergEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsScdEmergEn(void);
void        MMPF_VIDMGR_SetTrdEmergEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsTrdEmergEn(void);
void        MMPF_VIDMGR_SetUvcEmergEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsUvcEmergEn(void);
void        MMPF_VIDMGR_SetEmergRecdStart(MMP_BOOL bStart);
MMP_BOOL    MMPF_VIDMGR_IsEmergRecdStart(void);
void        MMPF_VIDMGR_SetKeepEmergRecdOnly(MMP_BOOL bKeepEmgOnly);
MMP_BOOL    MMPF_VIDMGR_IsKeepEmergRecdOnly(void);
void        MMPF_VIDMGR_SetEmergPreEncDuration(MMP_ULONG ulDuration);

/* UVC Record Function */
void        MMPF_VIDMGR_SetUvcRecdEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsUvcRecdEn(void);
MMP_BOOL    MMPF_VIDMGR_IsUvcRecdStart(void);
void        MMPF_VIDMGR_SetUvcTimeReset(MMP_BOOL bReset);
MMP_BOOL    MMPF_VIDMGR_IsUvcTimeReset(void);
MMP_ERR     MMPF_VIDMGR_UVCOpenFile(MMP_USHORT usStreamType);
MMP_ERR     MMPF_VIDMGR_UVCRecdStart(MMP_UBYTE ubType);
void        MMPF_VIDMGR_UVCRegisterForceICallback(void *pCallback);
void        MMPF_VIDMGR_UVCRegisterSlowCardStopRecord(void *pCallback);
void        MMPF_VIDMGR_UVCTrigger2CloseCurFile(void);
void        MMPF_VIDMGR_UVCSlowCard2StopVidRecd(void);

/* Share Record Function */
void        MMPF_VIDMGR_SetShareRecdEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsShareRecdEn(void);
MMP_BOOL    MMPF_VIDMGR_IsShareRecdStart(void);
void        MMPF_VIDMGR_SetShareRecdPreEncDuration(MMP_ULONG ulDuration);
MMP_ULONG   MMPF_VIDMGR_GetShareRecdPreEncDuration(void);
void        MMPF_VIDMGR_SetShareRecdTimeLimit(MMP_ULONG ulTimeLimit);

/* Second Record Function */
void        MMPF_VIDMGR_SetScdRecdEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsScdRecdEn(void);

/* Third Record Function */
void        MMPF_VIDMGR_SetTrdRecdEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsTrdRecdEn(void);
void        MMPF_VIDMGR_SetTrdEmergEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsTrdEmergEn(void);

/* Streaming Function */
MMP_BOOL    MMPF_VIDMGR_PumpStream(void);
MMP_ERR     MMPF_VIDMGR_StreamingStartEnc(MMP_ULONG ulEncId, MMP_USHORT usStreamType);
MMP_ERR     MMPF_VIDMGR_StreamingStopEnc(MMP_ULONG ulEncId, MMP_USHORT usStreamType);

/* MTS Mux Function */
void        MMPF_VIDMGR_SetMtsMuxEn(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDMGR_IsMtsMuxEn(void);
MMP_BOOL    MMPF_VIDMGR_UpdateMtsPktIdx(MMP_ULONG val);
MMP_BOOL    MMPF_VIDMGR_SetMtsPktIdx(MMP_ULONG val);

/* Misc */
MMP_ERR     MMPF_AVIMUX_AddChunkPrefix(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);

#endif // _MMPF_3GPMGR_H_
