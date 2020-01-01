/*
 * ae_types.h
 *
 *  Created on:
 *      Author:
 */

#include "MsTypes.h"
#include "ae_utility.h"

// [2017/07/17 Remove by JeffreyChou]
#define AE_WIN_NUM              (2)
//#define AE_WIN_MAX_WIDTH        (128)
//#define AE_WIN_MAX_HEIGHT       (90)
#define AE_HIST_NUM             (3)
//#define AE_HIST_WIN_MAX_WIDTH   (128)
//#define AE_HIST_WIN_MAX_HEIGHT  (90)
//#define AE_HIST_BIN0            (40)
//#define AE_HIST_BINX            (128)
//#define AE_IR_HIST_BIN          (256)
#define MAX_STS_WIDTH           (32)    //AE statistic size after down scale from ACC
#define MAX_STS_HEIGHT          (32)

#define AE_HIST_SEL             (1)

//pedef struct
//
//  MS_U16              u2HistR[AE_HIST_BIN0];
//  MS_U16              u2HistG[AE_HIST_BIN0];
//  MS_U16              u2HistB[AE_HIST_BIN0];
//ISP_AE_HIST0;

//pedef struct
//
//  MS_U16              u2HistY[AE_HIST_BINX];
//ISP_AE_HISTX;

//pedef struct
//
//  MS_U16              Rgbir_stats[AE_IR_HIST_BIN];
//ISP_RGBIR_STATS;

//pedef struct
//
//  MS_U8               uAvgR;
//  MS_U8               uAvgG;
//  MS_U8               uAvgB;
//  MS_U8               uAvgY;
//ISP_AE_AVGS;

//pedef struct
//
//  ISP_AE_HIST0        Hist0;
//  ISP_AE_HISTX        Hist1;
//  ISP_AE_HISTX        Hist2;
//  ISP_RGBIR_STATS     HistIR;
//  ISP_AE_AVGS         Avgs[AE_WIN_MAX_WIDTH*AE_WIN_MAX_HEIGHT];
//ISP_AE_STATIS;

typedef enum
{
    AE_TONE_BRIGHT,
    AE_TONE_DARK
} AE_TONE;

typedef enum
{
    AE_HIST_OP_ACC_PCENT,
    AE_HIST_OP_ACC_THD,
} AE_HIST_OP;

typedef struct
{
    MS_U32              u4AvgYx10;
    MS_U32              u4AvgYx40;
    MS_U32              u4MaxPcentY;
    MS_U32              u4MaxPcentx10;
    MS_U32              u4AccPcentx10;

    AE_HIST_OP          eHistOp;
    AE_TONE             eStartPoint;
    MS_BOOL             bSkip;
    MS_U32              u4TotalPcentx10;
    MS_U32              u4SkipPcentx10;
    MS_U32              u4TotalThd;
    MS_U32              u4SkipThd;

    MS_U32              u4FinalBin;
    MS_U32              u4OutputBins;
    MS_U32              u4InputBins;
    MS_U32              u4TotalPixelCnt;
    MS_U32              *pHist;
} AE_HIST_SPEC;

typedef struct
{
    AE_HIST_OP          eHistOp;
    AE_TONE             eStartPoint;
    MS_BOOL             bSkip;
    INTP_LUT            strTotalPcentByLUT;
    INTP_LUT            strTargetByLUT;
    MS_U32              u4SkipPcentx10;
    MS_U32              u4StsPcent;
    MS_U32              u4StsTargetx10;
    MS_U32              u4CurYx10;
} AE_HIST_METERING;

typedef struct
{
    INTP_LUT            strBrightPcentByLUT;
    MS_U32              u4BTSortBlockYWeighting;
    MS_U32              u4StsBrightPcent;
    MS_U32              u4StsBTYx10; //from Hist
    MS_U32              u4StsBTBlockYx10; //from ACC
    INTP_LUT            strDarkPcentByLUT;
    MS_U32              u4DTSortBlockYWeighting;
    MS_U32              u4StsDarkPcent;
    MS_U32              u4StsDTBlockYx10;
    MS_U32              u4StsDTYx10;
    MS_U32              u4DR;
} AE_SCENE_DR;

typedef struct
{
    MS_BOOL             bEnable;
    AE_HIST_METERING    strBrightTone;
    INTP_LUT            strBTTargetByBV;
    INTP_LUT            strBTBYWghtLUT;
    MS_U32              u4BTBlockYWeighting;
    MS_U32              u4StsBTBlockYx10;
    MS_U32              u4StsBTWghtYx10;
    MS_U32              u4StsBTBVProb;
    MS_U32              u4StsBTDRTargetx10;
    MS_U32              u4StsBTTargetx10;

    AE_HIST_METERING    strMidDarkToneLimit;
    MS_U32              u4StsMTDTTargetUpperx10;

    AE_HIST_METERING    strMidTone;
    MS_U32              u4StsMTTargetx10;

    AE_HIST_METERING    strDarkTone;
    MS_U32              u4StsNotSmoothedDTTargetx10;
    MS_U32              u4DTBlockYWeighting;
    MS_U32              u4StsDTBlockYx10;
    MS_U32              u4StsDTDarkWghtYx10;
    MS_U32              u4StsDTTargetx10;

    //RGBIR
    MS_U32              u4StsIRTop;
    MS_U32              u4StsRGBRawTop;

    //API
    MS_U32              u4Strength;
    MS_U32              u4Sensitivity;

    MS_U32              u4StsFinalTarget;
} AE_TONEBALANCE_TARGET;

typedef struct
{
    MS_U32              u4FNumx10;
    MS_U32              u4USec;
    MS_U32              u4TotalGain;
    MS_U32              u4SensorGain;
} AE_EXPO_POINT;

// turning point
typedef struct
{
    MS_U32              u4NumPoints;
    MS_U32              u4MinISPGain;
    MS_U32              u4MinSensorGain;
    MS_U32              u4MinUSec;
    MS_U32              u4MaxISPGain;
    MS_U32              u4MaxSensorGain;
    MS_U32              u4MaxUSec;
    AE_EXPO_POINT       ExpoTbl[16];  // LV from High to Low
} AE_EXPO_TBL;
