
#ifndef _DRV_MFE_H_
#define _DRV_MFE_H_

#include "vm_types.ht"

/** defining global declarations */
#define MAX_ROI_NUM 8
#define MAX_SEI_NUM 4

typedef enum
{
    DRV_VIDEO_FIXQP,                    /**<FIXQP*/
    DRV_VIDEO_CONTROLRATE,       /**<CONTROLRATE*/
} DrvVideoControlRateType_e;

typedef struct
{
    u32 nWidth;
    u32 nHeight;
    u32 nFps;
    u32 nGop;
    u32 nBitrate;
    u32 nQp;
    bool bEn;
} VideoBasicSettings_t;

typedef struct
{
    u32 nDeblockFilterControl;
    u32 nDisableDeblockingFilterIdc;
    u32 nSliceAlphaOffsetDiv2;
    u32 nSliceBetaOffsetDiv2;
    bool bEn;
} H264deblock_t;

typedef struct
{
    bool bDisposable;
    bool bEn;
} H264Disposable_t;

typedef struct
{
    u32 nPocType;
    bool bEn;
} H264Poc_t;

typedef struct
{
    bool bEntropyCodingCABAC;
    bool bEn;
} H264Entropy_t;

typedef struct
{
    DrvVideoControlRateType_e eControlRate;
    bool bEn;
} H264RC_t;

typedef struct
{
    bool bConstIpred;
    bool bEn;
} H264IntraP_t;

typedef struct
{
    u32 nDmv_X;/* dMV x-direction (8~16)*/
    u32 nDmv_Y;/* dMV y-direction (8/16)*/
    u32 nSubpel; /* subpel: 0-integral,1-half,2-quarter  */
    bool bInter4x4PredEn;
    bool bInter8x4PredEn;
    bool bInter4x8PredEn;
    bool bInter8x8PredEn;
    bool bInter16x8PredEn;
    bool bInter8x16PredEn;
    bool bInter16x16PredEn;
    bool bInterSKIPPredEn;
    bool bEn;
} H264InterP_t;

typedef struct
{
    u32 nRows;
    u32 nBits;
    bool bEn;
} H264SS_t;

typedef struct
{
    u32 nIdx;
    bool bEnable;
    u32 nDqp;
    u32 nMbX;
    u32 nMbY;
    u32 nMbW;
    u32 nMbH;
    bool bEn;
} H264ROI_t;

typedef struct
{
    u8 U8data[1024];
    u32 U32Len;
    bool bEn;
} H264SEI_t;

typedef struct
{
    u32 nWidth;
    u32 nHeight;
    u32 xFramerate;
    bool bEn;
} H264NewSeq_t;

typedef struct
{
    u32 nClkEn;
    u32 nClkSor;
    bool bEn;
} VideoClkSettings_t;

typedef struct
{
    VideoBasicSettings_t sBasic;
    H264deblock_t sDeblk;
    H264Disposable_t sDisposable;
    H264Poc_t sPoc;
    H264Entropy_t sEntropy;
    H264RC_t sRC;
    H264IntraP_t sIntraP;
    H264InterP_t sInterP;
    H264SS_t sMSlice;
    H264ROI_t sRoi[MAX_ROI_NUM];
    H264SEI_t sSEI[MAX_SEI_NUM];
    H264NewSeq_t sNewSeq;
    VideoClkSettings_t sClock;
} Mfe_param;

#endif/*_DRV_MFE_H_*/
