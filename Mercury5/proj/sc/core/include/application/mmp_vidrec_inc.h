//------------------------------------------------------------------------------
//
//  File        : mmp_vidrec_inc.h
//  Description : Header file of Video Record configuration
//  Author      :
//  Revision    : 1.0
//
//------------------------------------------------------------------------------

#ifndef _MMP_VIDREC_INC_H_
#define _MMP_VIDREC_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "config_fw.h"
#include "mmp_err.h"
#include "mmpf_typedef.h"

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

#define H264ENC_LBR_EN                      (1)
    #define H264ENC_LBR_FLOAT_RATIO (1)
    #define H264ENC_LBR_UNDERCHK    (1)

#ifndef MAX_NUM_TMP_LAYERS
#define MAX_NUM_TMP_LAYERS                  (2)
#endif

//==============================================================================
//
//                              MACRO DEFINE (Encoder)
//
//==============================================================================

// QP Boundary Index
#define BD_LOW                              (0)
#define BD_HIGH                             (1)

#define VIDENC_MAX_FRM_TYPE                 (VIDENC_FRAME_TYPE_NUM)

#define H264ENC_START_CODE_SIZE             (4) // Start Code : 0x00000001

#define VIDENC_MAX_B_FRAME_NUMS             (0)

#define VIDENC_MAX_QUEUE_SIZE               (30)
#define VIDENC_INVALID_QUEUE_SIZE           (0xFFFFFFFF)

// Video Record Flow Selection
#define VID_RECD_DISABLE                    (0x00)
#define VID_RECD_STORE_FILE                 (0x01)
#define VID_RECD_ENCODE_H264                (0x02)

// Video Format
#define VIDENC_FORMAT_OTHERS                (0x00)
#define VIDENC_FORMAT_H264                  (0x01)
#define VIDENC_FORMAT_MJPEG                 (0x02)

// Video Max Stream Num
#if (DUALENC_SUPPORT)
#define MAX_VIDEO_STREAM_NUM                (3)
#else
#define MAX_VIDEO_STREAM_NUM                (1)
#endif

#if (SUPPORT_H264_WIFI_STREAM)
#define MAX_WIFI_STREAM_NUM                 (2) // Front Cam + Rear Cam
#else
#define MAX_WIFI_STREAM_NUM                 (0)
#endif

#define VIDENC_MAX_STREAM_NUM               (MAX_VIDEO_STREAM_NUM + MAX_WIFI_STREAM_NUM)

// Video Parameter Set Max Num
#define VIDENC_MAX_PARAM_SET_NUM            (16)

// Video Instance ID
#define INVALID_ENC_ID                      (0xFFFFFFFF)

// Video Crop
#define H264_MB_SIZE                        (16)
#define H264_CROP_UNIT_X                    (2)
#define H264_CROP_UNIT_Y                    (2)

//==============================================================================
//
//                              MACRO DEFINE (Merger/Misc)
//
//==============================================================================

// Merger Relative
#define VIDENC_SPEED_CTL                    (1) ///< video speed control
#define VIDENC_SEAMLESS                     (1) ///< support seamless video encoding

// VR Thumbnail Relative
#define INVALID_THUMB_PROG_CNT              (0xFFFFFFFF)
#define VR_THUMB_MAX_BUF_NUM                (15)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef void VidEncEndCallBackFunc(void *);

// Video Camera Type (Sync With snr_cfg.h)
typedef enum _VIDENC_CAM_TYPE {
    VIDENC_CAM_BAYER_SNR,
    VIDENC_CAM_ANA_DECODER,
    VIDENC_CAM_YUV_SNR,
    VIDENC_CAM_USB_AIT,
    VIDENC_CAM_USB_SONIX_MJPEG,
    VIDENC_CAM_USB_SONIX_MJPEG2H264
} VIDENC_CAM_TYPE;

// Video Thumbnail Type
typedef enum _VIDENC_THUMB_TYPE {
    VIDENC_THUMB_PRM_RECD = 0,
    VIDENC_THUMB_PRM_EMERG,
    VIDENC_THUMB_SCD_RECD,
    VIDENC_THUMB_SCD_EMERG,
    VIDENC_THUMB_TRD_RECD,
    VIDENC_THUMB_TRD_EMERG,
    VIDENC_THUMB_UVC_RECD,
    VIDENC_THUMB_UVC_EMERG,
    /* Below are ring buffer type */
    VIDENC_THUMB_RING_BUF_PRM,
    VIDENC_THUMB_RING_BUF_SCD,
    VIDENC_THUMB_RING_BUF_TRD,
    VIDENC_THUMB_RING_BUF_UVC,
    VIDENC_THUMB_MAX_TYPE
} VIDENC_THUMB_TYPE;

// Video Record Speed Mode
typedef enum _VIDENC_SPEED_MODE {
    VIDENC_SPEED_NORMAL = 0,
    VIDENC_SPEED_SLOW,
    VIDENC_SPEED_FAST
} VIDENC_SPEED_MODE;

// Video Record Speed Ratio
typedef enum _VIDENC_SPEED_RATIO {
    VIDENC_SPEED_1X  = 0,
    VIDENC_SPEED_2X,
    VIDENC_SPEED_3X,
    VIDENC_SPEED_4X,
    VIDENC_SPEED_5X,
    VIDENC_SPEED_MAX
} VIDENC_SPEED_RATIO;

// Video FW Status
typedef enum _VIDENC_FW_STATUS {
    VIDENC_FW_STATUS_NONE       = 0x0000,
    VIDENC_FW_STATUS_START      = 0x0001,
    VIDENC_FW_STATUS_PAUSE      = 0x0002,
    VIDENC_FW_STATUS_RESUME     = 0x0003,
    VIDENC_FW_STATUS_STOP       = 0x0004,
    VIDENC_FW_STATUS_PREENCODE  = 0x0005
} VIDENC_FW_STATUS;

// Video Frame Type
typedef enum _VIDENC_FRAME_TYPE {
    VIDENC_I_FRAME = 0,
    VIDENC_P_FRAME,
    VIDENC_B_FRAME,
    VIDENC_FRAME_TYPE_NUM
} VIDENC_FRAME_TYPE;

// Video Output Mode
typedef enum _VIDENC_OUT_MODE {
    VIDENC_OUT_MODE_CARD = 0,
    VIDENC_OUT_MODE_STREAM
} VIDENC_OUT_MODE;

// Video Encode Attribute
typedef enum _VIDENC_ATTRIBUTE {
    VIDENC_ATTRIBUTE_PROFILE = 0,
    VIDENC_ATTRIBUTE_LEVEL,
    VIDENC_ATTRIBUTE_ENTROPY_MODE,
    VIDENC_ATTRIBUTE_FRM_QP,
    VIDENC_ATTRIBUTE_FRM_QP_BOUND,
    VIDENC_ATTRIBUTE_MB_QP_BOUND,
    VIDENC_ATTRIBUTE_CROPPING,
    VIDENC_ATTRIBUTE_RESOLUTION,
    VIDENC_ATTRIBUTE_BR,
    VIDENC_ATTRIBUTE_LB_SIZE,
    VIDENC_ATTRIBUTE_GOP_CTL,
    VIDENC_ATTRIBUTE_FORCE_I,
    VIDENC_ATTRIBUTE_MAX_PREENC_TIME,
    VIDENC_ATTRIBUTE_CAM_TYPE,

    // RC Control
    VIDENC_ATTRIBUTE_RC_MODE,
    VIDENC_ATTRIBUTE_RC_SKIPPABLE,
    VIDENC_ATTRIBUTE_RC_SKIPTYPE,
    VIDENC_ATTRIBUTE_RC_SKIP_FRM_THD,

    // Frame rate control
    VIDENC_ATTRIBUTE_MAX_FPS,
    VIDENC_ATTRIBUTE_ENC_FPS,
    VIDENC_ATTRIBUTE_SNR_FPS,

    // Add for MFE
    VIDENC_ATTRIBUTE_RESRC,
    VIDENC_ATTRIBUTE_MOTION,
    VIDENC_ATTRIBUTE_AVC,
    VIDENC_ATTRIBUTE_VUI,
    VIDENC_ATTRIBUTE_ROI,
    VIDENC_ATTRIBUTE_SPL
} VIDENC_ATTRIBUTE;

// H264 Entropy Coding
typedef enum _VIDENC_ENTROPY {
    H264ENC_ENTROPY_CAVLC = 0,
    H264ENC_ENTROPY_CABAC,
    H264ENC_ENTROPY_NONE
} VIDENC_ENTROPY;

// H264 Video Profile
typedef enum _VIDENC_PROFILE {
    H264ENC_PROFILE_NONE = 0,
    H264ENC_BASELINE_PROFILE,
    H264ENC_MAIN_PROFILE,
    H264ENC_HIGH_PROFILE,
    H264ENC_PROFILE_MAX
} VIDENC_PROFILE;

// Video Rate Control Mode
typedef enum _VIDENC_RC_MODE {
    VIDENC_RC_MODE_CBR = 0,
    VIDENC_RC_MODE_VBR,
    VIDENC_RC_MODE_CQP,
    VIDENC_RC_MODE_LOWBR,
    VIDENC_RC_MODE_MAX
} VIDENC_RC_MODE;

// RC Skip Type
typedef enum _VIDENC_RC_SKIPTYPE {
    VIDENC_RC_SKIP_DIRECT = 0,
    VIDENC_RC_SKIP_SMOOTH
} VIDENC_RC_SKIPTYPE;

// Encode Stream Type
typedef enum _VIDENC_STREAMTYPE {
    VIDENC_STREAM_PRM_RECD = 0,
    VIDENC_STREAM_PRM_EMERG,
    VIDENC_STREAM_UVC_RECD,
    VIDENC_STREAM_UVC_EMERG,
    VIDENC_STREAM_SCD_RECD,
    VIDENC_STREAM_SCD_EMERG,
    VIDENC_STREAM_TRD_RECD,
    VIDENC_STREAM_TRD_EMERG,
    VIDENC_STREAM_WIFI_PRM,
    VIDENC_STREAM_WIFI_SCD,
#if (SUPPORT_VR_REFIX_TAILINFO)
    VIDENC_STREAM_REFIXTAIL,
#endif
    VIDENC_STREAM_MAX
} VIDENC_STREAMTYPE;

// Video Event
typedef enum _VIDMGR_EVENT {
    VIDMGR_EVENT_NONE = 0,
    VIDMGR_EVENT_MEDIA_FULL,
    VIDMGR_EVENT_PRM_RECD_FILE_FULL,
    VIDMGR_EVENT_SCD_RECD_FILE_FULL,
    VIDMGR_EVENT_TRD_RECD_FILE_FULL,
    VIDMGR_EVENT_UVC_RECD_FILE_FULL,
    VIDMGR_EVENT_LONG_TIME_FILE_FULL,
    VIDMGR_EVENT_MEDIA_SLOW,
    VIDMGR_EVENT_SEAMLESS,
    VIDMGR_EVENT_MEDIA_ERROR,
    VIDMGR_EVENT_ENCODE_START,
    VIDMGR_EVENT_ENCODE_STOP,
    #if (SUPPORT_H264_WIFI_STREAM)
    VIDMGR_EVENT_WIFIENCODE_START,
    VIDMGR_EVENT_WIFIENCODE_STOP,
    #endif
    VIDMGR_EVENT_MUX_POSTPROCESS,
    VIDMGR_EVENT_BITSTREAM_DISCARD,
    VIDMGR_EVENT_MEDIA_WRITE,
    VIDMGR_EVENT_STREAMCB,
    VIDMGR_EVENT_EMERGFILE_FULL,
    VIDMGR_EVENT_RECDSTOP_CARDSLOW,
    VIDMGR_EVENT_APSTOPVIDRECD,
    VIDMGR_EVENT_PREGETTIME_CARDSLOW,
    VIDMGR_EVENT_COMPBUF_FREE_SPACE,
    VIDMGR_EVENT_APNEED_STOP_RECD,
    VIDMGR_EVENT_NUM
} VIDMGR_EVENT;

// Video Container Type
typedef enum _VIDMGR_CONTAINER_TYPE {
    VIDMGR_CONTAINER_3GP = 0,
    VIDMGR_CONTAINER_AVI,
    VIDMGR_CONTAINER_TS,
    VIDMGR_CONTAINER_NONE,
    VIDMGR_CONTAINER_UNKNOWN
} VIDMGR_CONTAINER_TYPE;

// AV sync method
typedef enum _VIDMGR_AVSYNC_METHOD {
    VIDMGR_AVSYNC_REF_AUD = 0,  // Use audio clock as reference clock
    VIDMGR_AVSYNC_REF_VID       // Use video clock as reference clock
} VIDMGR_AVSYNC_METHOD;

// Check compress buffer stage
typedef enum _VIDMGR_COMPBUF_FREESIZE_STAGE {
    VIDMGR_COMPBUF_LESS_1MB = 0,
    VIDMGR_COMPBUF_LESS_2MB,
    VIDMGR_COMPBUF_LESS_3MB,
    VIDMGR_COMPBUF_LESS_4MB,
    VIDMGR_COMPBUF_LESS_5MB,
    VIDMGR_COMPBUF_SAFE
} VIDMGR_COMPBUF_FREESIZE_STAGE;

// Video Encode Using Mode
typedef enum _VIDRECD_USEMODE {
    VIDRECD_USEMODE_RECD = 0,
    VIDRECD_USEMODE_CB2AP,
    VIDRECD_USEMODE_MAX
} VIDRECD_USEMODE;

// Video Pixel Format
typedef enum _VIDENC_PIXFMT {
    VIDENC_PIXFMT_NV12 = 0,
    VIDENC_PIXFMT_NV21,
    VIDENC_PIXFMT_YUYV,
    VIDENC_PIXFMT_YVYU,
    VIDENC_PIXFMT_NUM
} VIDENC_PIXFMT;

// Video Motion Search
typedef enum _VIDENC_SUBPEL {
    VIDENC_SUBPEL_INT = 0,
    VIDENC_SUBPEL_HALF,
    VIDENC_SUBPEL_QUATER
} VIDENC_SUBPEL;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _VIDENC_RESOLUTION {
    MMP_ULONG   ulEncW;
    MMP_ULONG   ulEncH;
    MMP_ULONG   ulEncBufW;
    MMP_ULONG   ulEncBufH;
} VIDENC_RESOLUTION;

typedef struct _VIDENC_RC_MODE_CTL {
    VIDENC_RC_MODE  RcMode;
    MMP_BOOL        bLayerGlobalRc;
} VIDENC_RC_MODE_CTL;

typedef struct _VIDENC_RC_SKIP_CTL {
    MMP_BOOL    bSkippable;                     ///< Rc can skip frames or not
    MMP_BOOL    bSkipType;                      ///< 0: direct skip, 1: smooth skip
    MMP_BOOL    bSkipBypass;                    ///< Bypass current frame RC skip
    MMP_UBYTE   ubSkipFrmThdInOneSec;           ///< Threshold of skip frames within 1 sec to send card slow event
    MMP_ULONG   ulTotalSkipFrmCntThd;
    MMP_ULONG   ulContiSkipFrmCntThd;
} VIDENC_RC_SKIP_CTL;

typedef struct _VIDENC_GOP_CTL {
    MMP_USHORT  usGopSize;
    MMP_USHORT  usPFrameNum;
    MMP_USHORT  usBFrameNum;
    MMP_BOOL    bReset;
} VIDENC_GOP_CTL;

typedef struct _VIDENC_CROPPING {
    MMP_USHORT  usTop;
    MMP_USHORT  usBottom;
    MMP_USHORT  usLeft;
    MMP_USHORT  usRight;
} VIDENC_CROPPING;

typedef struct _VIDENC_BITRATE_CTL {
    MMP_UBYTE   ubLayerBitMap;                  ///< 0'b111 means all temporal layers
    MMP_ULONG   ulStreamBitrate;                ///< The stream bitrate
    MMP_ULONG   ulLayerBitrate[MAX_NUM_TMP_LAYERS];  ///< bitrate, bits
} VIDENC_BITRATE_CTL;

typedef struct _VIDENC_LEAKYBUCKET_CTL {
    MMP_UBYTE   ubLayerBitMap;                  ///< 0'b111 means all temporal layers
    MMP_ULONG   ulLeakyBucketSzInMs[MAX_NUM_TMP_LAYERS];///< in ms
} VIDENC_LEAKYBUCKET_CTL;

typedef struct _VIDENC_QP_CTL {
    MMP_UBYTE   ubTypeBitMap;                   ///< 0: I, 1: P, 2: B
    MMP_UBYTE   ubQP[VIDENC_MAX_FRM_TYPE];
    MMP_LONG    CbrQpIdxOffset[VIDENC_MAX_FRM_TYPE];    ///< Chroma QP index offset
    MMP_LONG    CrQpIdxOffset[VIDENC_MAX_FRM_TYPE];     ///< 2nd chroma QP index offset
    MMP_ULONG   ulRqctRefQP;
} VIDENC_QP_CTL;

typedef struct _VIDENC_QP_BOUND_CTL {
    MMP_UBYTE   ubTypeBitMap;                   ///< 0: I, 1: P, 2: B
    MMP_UBYTE   ubQPBound[VIDENC_MAX_FRM_TYPE][2];
} VIDENC_QP_BOUND_CTL;

typedef struct _VIDENC_INPUT_ATTR {
    void*       pComp;
    MMP_USHORT  usStreamType;
    MMP_ULONG   ulInstId;
    MMP_ULONG   ulBufAddr;
    MMP_ULONG   ulBufWidth;
    MMP_ULONG   ulBufHeight;
    MMP_ULONG   ulBufFmt422;
    MMP_ULONG   ulBufTime;
    MMP_ULONG   ulBufWeight;
    MMP_USHORT  usLineBias;
    MMP_ULONG   ulGenBufAddr;
    MMP_ULONG   ulRefBufAddr;
} VIDENC_INPUT_ATTR;

typedef struct _VIDENC_DONE_ATTR {
    MMP_ULONG   ulFrmType;
    MMP_ULONG   ulFrmSize;
    MMP_ULONG   ulFrmTime;
    MMP_UBYTE   ubEncId;
    MMP_USHORT  usStreamType;
} VIDENC_DONE_ATTR;

typedef struct _VIDENC_FRAME_INFO {
    MMP_ULONG   ulYAddr;
    MMP_ULONG   ulUAddr;
    MMP_ULONG   ulVAddr;
    MMP_ULONG   ulYAddrEnd;
    MMP_ULONG   ulUAddrEnd;
    MMP_ULONG   ulVAddrEnd;
    MMP_ULONG   ulBufSize;
    MMP_ULONG   ulTimestamp;
    MMP_ULONG   ulLineBias;
} VIDENC_FRAME_INFO;

typedef struct _VIDENC_DUMMY_DROP_INFO {
    MMP_ULONG   ulDummyFrmCnt;                  ///< Specified how many video frames to be duplicated
    MMP_ULONG   ulDropFrmCnt;                   ///< Specified how many video frames to be dropped
    MMP_USHORT  usAccumSkipFrames;              ///< Number of skip frames within 1 sec
    MMP_ULONG   ulBeginSkipTimeInMS;            ///< The absolute timer counter of the beginning skip frame within 1 sec.
} VIDENC_DUMMY_DROP_INFO;

typedef struct _VIDENC_FPS_CTL {
    MMP_ULONG   ulResol;
    MMP_ULONG   ulIncr;
    MMP_ULONG   ulIncrx1000;
} VIDENC_FPS_CTL;

typedef struct _VIDENC_RESRC_CTL {
    MMP_ULONG   ulPictW;                        ///< Picture width.
    MMP_ULONG   ulPictH;                        ///< Picture height.
    MMP_ULONG   ulPixFmt;                       ///< Pixel format.
    MMP_LONG    lOutlen;                        ///< Output length: '<0' mmap-mode, '>=0' user-mode.
    MMP_LONG    lInlen;                         ///< Output length: '<0' plus-mode, '>=0' pure-mode.
    MMP_ULONG   ulFlags;                        ///< Flags.
    MMP_UBYTE   ubClkEn;
    MMP_UBYTE   ubClkSrc;
    MMP_ULONG   ulAlignW;
    MMP_ULONG   ulAlignH;
} VIDENC_RESRC_CTL;

typedef struct _VIDENC_MOT_CTL {
    MMP_ULONG   ulDmvX;                         ///< X-dir dmv.
    MMP_ULONG   ulDmvY;                         ///< Y-dir dmv.
    MMP_ULONG   ulSubPel;                       ///< Interpolation granularity.
    MMP_ULONG   ulMvBlks[2];                    ///< MV-partitions.
} VIDENC_MOT_CTL;

typedef struct _VIDENC_AVC_CTL {
    MMP_USHORT  usProfile;                      ///< Profile.
    MMP_USHORT  usLevel;                        ///< Level.
    MMP_UBYTE   ubNumRefFrames;                 ///< Ref.frames count.
    MMP_UBYTE   ubPocType;                      ///< Poc_type: support 0,2.
    MMP_UBYTE   ubCabac;                        ///< Entropy: cabac/cavlc.
    VIDENC_ENTROPY eEntropyMode;                ///< Entropy: cabac/cavlc.
    MMP_UBYTE   ubConstrainedIntraPred;         ///< Contrained intra pred.
    MMP_UBYTE   ubDeblockFilterControl;         ///< Deblock filter control.
    MMP_UBYTE   ubDisableDeblockingIdc;         ///< Disable deblocking idc.
    MMP_BYTE    sbAlphaC0Offset;                ///< Offset alpha div2.
    MMP_BYTE    sbBetaOffset;                   ///< Offset beta div2.
} VIDENC_AVC_CTL;

typedef struct _VIDENC_VUI_CTL {
    MMP_ULONG   ulSAR_W;
    MMP_ULONG   ulSAR_H;
    MMP_ULONG   ulVideoFullRange;
    MMP_ULONG   ulVideoSignalPres;
    MMP_ULONG   ulVideoFormat;
    MMP_ULONG   ulColourDescPres;
    MMP_ULONG   ulTimingInfoPres;
} VIDENC_VUI_CTL;

typedef struct _VIDENC_ROI_CTL {
    MMP_SSHORT  ssIndex;                        ///< ROI index.
    MMP_SSHORT  ssDqp;                          ///< ROI delta-qp: 0-disable ROI, negative value.
    MMP_USHORT  usMbX;                          ///< ROI rectangle position-X.
    MMP_USHORT  usMbY;                          ///< ROI rectangle position-Y.
    MMP_USHORT  usMbW;                          ///< ROI rectangle-W.
    MMP_USHORT  usMbH;                          ///< ROI rectangle-H.
} VIDENC_ROI_CTL;

typedef struct _VIDENC_SPL_CTL {
    MMP_ULONG   ulRows;                         ///< Slice split by mb-rows.
    MMP_ULONG   ulBits;                         ///< Slice split by bitcnt.
} VIDENC_SPL_CTL;

typedef union {
    VIDENC_BITRATE_CTL      Bitrate;
    VIDENC_RC_MODE_CTL      RcMode;
    VIDENC_RC_SKIP_CTL      RcSkip;
    VIDENC_LEAKYBUCKET_CTL  CpbSize;
    VIDENC_QP_CTL           Qp;
    VIDENC_GOP_CTL          Gop;
    VIDENC_FPS_CTL          Fps;
    VIDENC_RESRC_CTL        Resrc;
    VIDENC_MOT_CTL          Mot;
    VIDENC_AVC_CTL          Avc;
    VIDENC_VUI_CTL          Vui;
    VIDENC_ROI_CTL          Roi;
    VIDENC_SPL_CTL          Spl;
    MMP_ULONG               ConusI;             ///< Contiguous I-frame count
} VIDENC_CTL;

typedef struct _VIDENC_PARAM_CTL {
    VIDENC_ATTRIBUTE        Attrib;
    void (*CallBack)(MMP_ERR);
    VIDENC_CTL              Ctl;
} VIDENC_PARAM_CTL;

typedef struct _VIDENC_THUMB_ATTR {
    MMP_ULONG               ulAddr;             ///< Thumbnail store address
    MMP_ULONG               ulSize;             ///< Thumbnail size
    MMP_ULONG               ulProgCnt;          ///< Ring Buf Index
    MMP_ULONG               ulFrmQIdx;          ///< Frame Queue Write Index
} VIDENC_THUMB_ATTR;

typedef struct _VIDENC_THUMB_TARGET_CTL {
    MMP_ULONG               ulFrmQIdx;
    MMP_ULONG               ulMarked;
} VIDENC_THUMB_TARGET_CTL;

#endif // _MMP_VIDREC_INC_H_

