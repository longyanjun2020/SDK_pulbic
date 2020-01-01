
// mstar hardware video encoder I/F (mhveif)

#ifndef _ARQC_OPS_H_
#define _ARQC_OPS_H_

#include "mmp_vidrec_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_NUM_TMP_LAYERS                  (2)
#define MAX_NUM_TMP_LAYERS_LBR              (2) // For H264ENC_LBR_EN
#define TEMPORAL_ID_MASK                    (0x03)

#define RC_MIN_VBV_FRM_NUM                  ((RC_MAX_WEIGHT_I + 2000) / 1000)
#define RC_PSEUDO_GOP_SIZE                  (1000)

/*
 * Low bitrate ratio for I layers for static or motion scene
 */
#if (H264ENC_LBR_EN)&&(H264ENC_LBR_FLOAT_RATIO)
// For static scene
#define LBR_STATIC_I_RATIO_30FPS            (80)
#define LBR_STATIC_I_RATIO_60FPS            (70)
#define LBR_STATIC_I_RATIO_90FPS            (65)
#define LBR_STATIC_I_RATIO_120FPS           (60)

// For motion scene
#define LBR_MOTION_I_RATIO_30FPS            (20)
#define LBR_MOTION_I_RATIO_60FPS            (15)
#define LBR_MOTION_I_RATIO_90FPS            (10)
#define LBR_MOTION_I_RATIO_120FPS           (5)
#endif

#if (H264ENC_LBR_EN)
#define RC_MAX_WEIGHT_I                     (2000)
#define RC_INIT_WEIGHT_I                    (1000)
#else
#define RC_MAX_WEIGHT_I                     (3500)
#define RC_INIT_WEIGHT_I                    (2500)
#endif

// Video Format
#ifndef VIDENC_FORMAT_OTHERS
#define VIDENC_FORMAT_OTHERS                (0x00)
#endif
#ifndef VIDENC_FORMAT_H264
#define VIDENC_FORMAT_H264                  (0x01)
#endif
#ifndef VIDENC_FORMAT_MJPEG
#define VIDENC_FORMAT_MJPEG                 (0x02)
#endif

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _VBV_PARAM {
    int         LayerBitRate[MAX_NUM_TMP_LAYERS];
    int         BitRate[MAX_NUM_TMP_LAYERS];
    int         LayerVBVSize[MAX_NUM_TMP_LAYERS];
    int         VBVSizeInByte[MAX_NUM_TMP_LAYERS];
    int         VBVCurFullness[MAX_NUM_TMP_LAYERS];
    int         TargetVBVInByte[MAX_NUM_TMP_LAYERS];
    int         TargetVBVInMS[MAX_NUM_TMP_LAYERS];
    int         VBVRatio[MAX_NUM_TMP_LAYERS];
} VBV_PARAM;

typedef struct _RC {
    // Global settings
    int         rc_mode;                    // CBR or VBR or Constant QP mode
    int         Bitrate;                    // Stream average bitrate
    int         TargetFrmSize;              // Target frame size

    int         nP;                         // Number of P frame within GOP
    int         nB;                         // Number of B frame within GOP
    int         IntraPeriod;                // The frame num of a GOP (I+P+B frames)

    int         MaxWeight[3];               // The max size ratio of I/P/B frame (Base:1024)
    int         MinWeight[3];               // The min size ratio of I/P/B frame (Base:1024)
    int         Alpha[3];                   // The current weighting of I/P/B frame for bit budget dispatch (Base:1024)
    int         MaxQPDelta[3];              // The QP delta max range within MB layer, Ex:-3 ~ +3
    int         QPLowBound[3];              // QP lower bound
    int         QPUpBound[3];               // QP upper bound
    int         bUseInitQP;                 // Use initial QP for 1st frame

    int         VideoFormat;                // Video format (H264/MJPEG)
    int         VidFormatIdx;               // Video format index
    int         LastFrmType;                // The last frame type (I/P/B)
    int         LastFrmQP;                  // The last frame QP value
    int         LastQP[3];                  // The last OP value of I/P/B frame
    int         LastX[3];                   // The last frame complexity of I/P/B frame
    unsigned long long Acc_X[3];            // The accumulation of frame complexity of I/P/B frame
    int         FrmCount[3];                // The frame count of I/P/B frame
    bool        bResetRC;                   // Reset RC module or not

    int         avg_QP[3];                  // The average QP of I/P/B frame (Base:1000)
    int         avg_XP[3];                  // The average complexity of I/P/B frame
    int         avg_FrameSize[3];           // The average frame size of I/P/B frame

    // VBV settings
    int         VBVCurFullness;             // The current fullness of VBV (Unit:Bytes)
    int         VBVSizeInByte;              // The size of VBV (Unit:Bytes)
    int         TargetVBVInMS;              // The target fullness of VBV (Unit:ms), Ex:250 ms
    int         TargetVBVInByte;            // The target fullness of VBV (Unit:Bytes)
    int         VBVRatio;                   // The ratio of VBV size (Unit:bit) and BitRate, use for reset bitrate or reset buffer size (Base:1000)

    // CBR/LBR settings
    int         cbr_RemainBudgetInRcPeriod; // [CBR mode] Remain bit budget in the RC GOP (Unit:Bytes)
    int         cbr_RemainFrmsInRcPeriod;   // [CBR mode] Left frame within the RC GOP
    int         cbr_TargetPSize;            // [CBR mode] Target P frame size

    // VBR settings
    int         vbr_RcPeriodBudget;         // [VBR mode] Total bit budget of VBR_RC_PERIOD (300) frames
    int         vbr_RemainBudgetInRcPeriod; // [VBR mode] The remain bit budget in the RC period (Unit:Bytes)
    int         vbr_RemainBudgetInRcGOP;    // [VBR mode] The remain bit budget within the vbr_RcGOP
    int         vbr_RemainFrmsInRcPeriod;   // [VBR mode] Remain total frames in the RC period
    int         vbr_TotalFrmsInRcPeriod;    // [VBR mode] Total RC period frame num. Ex:300 frames
    int         vbr_FrameCount;             // [VBR mode] The encoded frame count
    int         vbr_GOPNumPerIPeriod;       // [VBR mode] The frame num ratio of real GOP and vbr_RcGOP
    int         vbr_GOPCntWithinRealGOP;    // [VBR mode] The vbr_RcGOP counter between 0 ~ vbr_GOPNumPerIPeriod

    int         vbr_mode_start;             // [VBR mode] Start VBR mode
    int         vbr_TargetPSize;            // [VBR mode] The target P frame size
    int         vbr_RcGOP;                  // [VBR mode] Frame number within RC GOP
    int         vbr_RcGOP_QP[3];            // [VBR mode] The QP base of I/P/B frame within the vbr_RcGOP
    int         vbr_QPSumInRcGOP;           // [VBR mode] The QP summation
    int         vbr_FrameCntInRcGOP;        // [VBR mode] The frame count between (0 ~ vbr_RcGOP)
    int         vbr_LeftFrmInRcGOP[3];      // [VBR mode] The left frame num of I/P/B frame within the vbr_RcGOP
    int         vbr_RcGOPCount;             // [VBR mode] The GOP count (assume 15 frame as a vbr_RcGOP)

    // Skip Frame settings
    bool        bSkipPrevFrame;             // Skip previous frame or not
    int         SkipFrameThd;               // The skip frame threshold of the VBV (Base:1024)
    bool        bPreSkipFrmEn;              // Enable skip frame before encode
    bool        bPostSkipFrmEn;             // Enable skip frame after encode
    int         nBCount;
    int         nSCount;
    // Multi-Layer settings
    void*       pGlobalVBV;                 // Pointer to global VBV structure
    int         LayerRelated;               // Enable layer operation
    int         Layer;                      // Layer ID
} RC;

typedef struct _RC_CONFIG_PARAM {
    int         MaxIWeight;                 // The max size ratio of I/P frame (Base:1000), Ex:1.5 * 1000
    int         MinIWeight;                 // The min size ratio of I/P frame (Base:1000), Ex:1.0 * 1000
    int         MaxBWeight;                 // The max size ratio of B/P frame (Base:1000), Ex:1.0 * 1000
    int         MinBWeight;                 // The min size ratio of B/P frame (Base:1000), Ex:0.5 * 1000
    int         VBVSizeInBit;               // The size of VBV (Unit:bits)
    int         TargetVBVInMS;              // The target fullness of VBV (Unit:ms), Ex:250 ms
    int         InitWeight[3];              // The weighting of I/P/B frame for bit budget dispatch (Use P = 1000 as base)
    int         MaxQPDelta[3];              // The QP delta max range within MB layer, Ex:-3 ~ +3
    int         SkipFrameThd;               // The skip frame threshold of the VBV (Base:1000), Ex:700
    int         MBWidth;                    // Frame width (Unit:MB)
    int         MBHeight;                   // Frame height (Unit:MB)
    int         InitQP[3];                  // Initial QP value of I/P/B frame set by host
    int         rc_mode;                    // CBR or VBR or CONSTANT_QP mode
    int         bPreSkipFrmEn;              // Skip frame or not

    int         LayerRelated;               // Enable layer operation
    int         Layer;                      // Layer ID
    int         EncID;                      // Encode instance ID
} RC_CONFIG_PARAM;

typedef struct _STREAM_RC_INFO {
    VIDENC_BITRATE_CTL          stRcBr;
    VIDENC_GOP_CTL              stRcGop;
    VIDENC_FPS_CTL              stRcInFps;
    VIDENC_FPS_CTL              stRcEncFps;
    VIDENC_LEAKYBUCKET_CTL      stRcLeakyBuf;
    VIDENC_RC_SKIP_CTL          stRcSkip;

    int         stream_id;
    int         mb_w;
    int         mb_h;
    int         cur_frm_type;
    int         total_layers;

    /* RC Temporal Layers Configuration */
    int         layer_max_skip_frm_thd[MAX_NUM_TMP_LAYERS];
    int         layer_tgt_frm_size[MAX_NUM_TMP_LAYERS]; // Target frame size for each layer
    int         layer_frm_thr[MAX_NUM_TMP_LAYERS];      // Threshold to skip encoding
    int         layer_fps_ratio[MAX_NUM_TMP_LAYERS];    // Fps ratio for each layer
    #if (H264ENC_LBR_EN)
    int         layer_fps_ratio_low_br[MAX_NUM_TMP_LAYERS_LBR];
    #endif
    RC_CONFIG_PARAM rc_config[MAX_NUM_TMP_LAYERS];      // The RC temporal layers configuration
    void        *layer_rc_hdl[MAX_NUM_TMP_LAYERS];      // The RC handle

    /* QP Tune Configuration */
    int         MbQpBound[MAX_NUM_TMP_LAYERS][VIDENC_FRAME_TYPE_NUM][2];
    int         CurRcQP[MAX_NUM_TMP_LAYERS][VIDENC_FRAME_TYPE_NUM];

    /* Low Bitrate Configuration */
    #if (H264ENC_LBR_EN)
    int         ubAccResetLowBrRatioTimes;
    int         ubAccResetHighBrRatioTimes;
    bool        bResetLowBrRatio;   // Reset low bitrate (P-frame) ratio
    bool        bResetHighBrRatio;  // Reset high bitrate (I-frame) ratio
    int         intra_mb;           // Intra MB count
    int         decision_mode;      // Decide the intra/inter MB mode
    #endif
} STREAM_RC_INFO;

#endif //_ARQC_OPS_H_
