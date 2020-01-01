#ifndef __CAMERA_AUTOEXPOSURE_H__
#define __CAMERA_AUTOEXPOSURE_H__

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * drv_cam_autoexposure_RTOS.h
 *
 *  Created on:
 *      Author:
 */
#define IN_KERNEL_SPACE (0)

#if IN_KERNEL_SPACE
#include <linux/sort.h>
#include "libcamera_io.h"
#include <drv_ms_rwcfg.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#include "sys_MsWrapper_cus_os_sem.h"
#include "drv_ms_rwcfg.h"
#include "libcamera.h"

#endif

#include "ae_types.h"
#include "isp_3a_if.h"
#include <isp_sys_api.h>

#define AE_F_NUBER_MIN  (10)
#define AE_F_NUBER_MAX  (220)
#define AE_LV_VALUE_MIN (0)
#define AE_LV_VALUE_MAX (200)
#define AE_EV_COMP_GRAD_VALUE_MIN (1)
#define AE_EV_COMP_GRAD_VALUE_MAX (20)

#ifdef WIN32
#define MAX_OBJ_WIN     (1)
#else
#define MAX_OBJ_WIN     (0)
#endif

#ifdef min
#undef min
#endif
#define min(a,b)        (((a) >= (b))?(b):(a))

#ifdef max
#undef max
#endif
#define max(a,b)        (((a) >= (b))?(a):(b))

#ifdef minmax
#undef minmax
#endif
#define minmax(v,a,b)   (((v)<(a))? (a) : ((v)>(b)) ? (b) : (v))

#if IN_KERNEL_SPACE
#else
MS_S8 UartSendTrace(const char *strFormat, ...);
#endif

struct __cam_ae_handle_t;

typedef enum
{
    AE_CALI_BS_50, // base shutter
    AE_CALI_BS_60,
    AE_CALI_OB,
    AE_CALI_PREGAIN,
    AE_CALI_LSC,
    AE_CALI_NOISE,
    AE_CALI_APEX_SV,
    AE_CALI_APEX_TV,
    AE_CALI_ISO100,
    AE_CALI_DONOTHING,
} AE_CALI;

typedef enum
{
    AE_MODE_A,     // auto
    AE_MODE_AV,    // aperture priority
    AE_MODE_SV,
    AE_MODE_TV,    // shutter priority
    AE_MODE_M,     // manual mode
} AE_EXP_MODE;

typedef enum
{
    DBG_LV_STS        = (1<<0),
    DBG_LV_ALGO_PARAM = (1<<1),
    DBG_LV_ALGO_STS   = (1<<2),
    DBG_LV_ALGO_TIMING= (1<<3),
    DBG_LV_MV_STS     = (1<<4),
    DBG_LV_API_CALL   = (1<<5),
    DBG_LV_ERR        = (1<<7),
} DBG_LV;

typedef enum
{
    AE_STGY_BRIGHTTONE,
    AE_STGY_DARKTONE,
    AE_STGY_AUTO,
} AE_STRATEGY;

typedef enum
{
    AE_OP_NORMAL,
    AE_OP_CALI,
    AE_OP_TUNING,
    AE_OP_ENG
} AE_OP_MODE;

typedef enum
{
    BANDING_50HZ = 0,
    BANDING_60HZ
} AE_BANDING;

typedef enum
{
    AE_FLICKER_AUTO,
    AE_FLICKER_DISABLE,
    AE_FLICKER_MANUAL
} AE_FLICKER_MODE;

typedef enum
{
    SCENE_MODE_OFF,
    SCENE_MODE_AUTO,
    SCENE_MODE_MANUAL
} AE_SCENE_MODE;

typedef enum
{
    AE_SCENE_NONE,
    AE_SCENE_AUTO,
    AE_SCENE_BACKLIGHT,
    AE_SCENE_BEACH,
    AE_SCENE_FIREWORKS,
    AE_SCENE_LANDSCAPE,
    AE_SCENE_MACRO,
    AE_SCENE_NIGHT,
    AE_SCENE_PARTY,
    AE_SCENE_PORTRAIT,
    AE_SCENE_SPORTS,
    AE_SCENE_SUNSET,
    AE_SCENE_AQUARIUM,
    AE_SCENE_FOLIAGE,
    AE_SCENE_LARGE_APERTURE,
    AE_SCENE_SMALL_APERTURE,
    AE_SCENE_SPOTLIGHT
} AE_SCENE;

typedef enum
{
    AE_SM_START,
    AE_SM_CAL,      // calculate ae
    AE_SM_RESUME,
    AE_SM_PAUSE,    // do nothing
    AE_SM_STOP,
    AE_SM_EXIT
} AE_SM;

// AE
typedef struct
{
    MS_U32 BS50HZ; // number of line for 50Hz preview resolution
    MS_U32 BS60HZ; // number of line for 60Hz preview resolution
} AE_BS;

//////////////////// v2.0
typedef struct
{
    MS_U32 u4ISO100Gain;
    MS_U32 u4MinISO;
    MS_S32 i4BVOffset;
    MS_S32 i4AVOffset;
    MS_U32 u4ModuleFN;
} AE_CALIDATA;

typedef struct
{
    MS_S32 i4TVxBASE;
    MS_S32 i4SSVxBASE;
    MS_S32 i4DSVxBASE;
    MS_S32 i4AVxBASE;
    MS_S32 i4BVxBASE;
} AE_APEX_EXPO;

typedef struct
{
    MS_U32          u4NumPoints;
    AE_APEX_EXPO    Points[16];
    AE_APEX_EXPO    MaxBV;
    AE_APEX_EXPO    MinBV;
} AE_APEX_EXPOTBL;

typedef struct
{
    MS_U8           Upper;
    MS_U8           Lower;
    MS_S32          i4TargetBV;
    MS_S32          i4DeltaxBASE;
    AE_APEX_EXPO    strCurExpo;
    AE_APEX_EXPO    strOutputExpo;
} AE_CAL_EXPO;

typedef struct
{
    MS_U32 u4FNumx10;
    MS_U32 u4ExpoUSec;
    MS_U32 u4StdISO;
    MS_U32 u4LVx10;
} AE_PLAIN_EXPO;

typedef struct
{
    AE_PLAIN_EXPO   strPlainExpo;
    AE_APEX_EXPO    strApexExpo;
} AE_EV_CONVERSION;


typedef struct
{
    MS_U32          u4CurYx10;
    MS_U32          u4AvgYx10;
    MS_U32          u4PredCurYx10;
    MS_U32          u4PredAvgYx10;
    AE_APEX_EXPO    strExpo;
    AE_APEX_EXPO    strETExpo;
} AE_EXPO;

typedef struct
{
    INTP_LUT AeHdrRatio;
} AE_HDR_TYPE;

////////////////////////////////////////////////////

typedef struct
{
    // from sensor driver or flickering calibrated, before other calibrations
    MS_U32              max_shutter;            // get from sensor
    MS_U32              min_shutter;
    MS_U32              max_usec;               // get from sensor
    MS_U32              min_usec;
    MS_U32              max_gain;               // get from sensor, 1x=1024

    // calibrated
    // if no calibrated data, these value are set to '0' is ok.
    MS_U32              unit;                   // default: 1024
    MS_U32              pre_gain;               // default: 1x=1024, make sure the dynamic range covers 0~255
    MS_S32              iso_shift_val;          // default: 0, difference between  the defined ISO100 index with calibrated ISO100
    MS_U32              iso100_lv;              // default: 10, lv4~lv14
    MS_U32              iso100_target;          // default: 43, luminance value

    // from sensor or after ISO100 calibrated
    MS_U32              iso100_shutter_value;   // default: BS, shutter value of sensor for ISO100
    MS_U32              iso100_tv_idx;          // default: TV_1_32, TV index
    MS_U32              iso100_gain_value;      // default: 1024, gain value of sensor for ISO100
    MS_U32              iso100_sv_idx;          // default: SV_ISO_25, SV index
} AE_TBL;

typedef enum
{
    AE_HIST_RGB,
    AE_HIST_Y
} AE_HIST_TYPE;

typedef struct
{
    MS_U32 u4RatioX; //1x=1024, Width=AE_WIN_MAX_WIDTH*u4RatioX/1024
    MS_U32 u4RatioY; //1x=1024, Height=AE_WIN_MAX_HEIGHT*u4RatioY/1024
    MS_S32 i4CenterOffsetX;
    MS_S32 i4CenterOffsetY;
    MS_U16 u2NumX;
    MS_U16 u2NumY;
} AE_WIN;

typedef struct
{
    MS_U8 NumX;
    MS_U8 NumY;
    MS_U8 StartX;
    MS_U8 StartY;
    MS_U8 EndX;
    MS_U8 EndY;
    MS_U8 StepX[MAX_STS_WIDTH + 1];
    MS_U8 StepY[MAX_STS_HEIGHT + 1];

    MS_U32 u4WghtYx10;
    MS_U32 u4AvgYx10;
    MS_U32 u4BlockCnt[MAX_STS_WIDTH*MAX_STS_HEIGHT];
    MS_U32 u4LumYSum[MAX_STS_WIDTH*MAX_STS_HEIGHT];
    MS_U32 u4LumYx10[MAX_STS_WIDTH*MAX_STS_HEIGHT];
    //MS_U32 u4BlockHist[MAX_STS_WIDTH*MAX_STS_HEIGHT][MAX_BLOCK_BINS];
    MS_U32 u4SortedLumYx10[MAX_STS_WIDTH*MAX_STS_HEIGHT];
    MS_U32 u4R[MAX_STS_WIDTH*MAX_STS_HEIGHT];
    MS_U32 u4G[MAX_STS_WIDTH*MAX_STS_HEIGHT];
    MS_U32 u4B[MAX_STS_WIDTH*MAX_STS_HEIGHT];
} AE_WIN_CFG;

typedef enum
{
    AE_AVERAGE = 0,
    AE_CENTER_WGHT,
    AE_SPOT,
    AE_WGT_END
} AE_WIN_WGT;

typedef struct
{
    MS_U32      u4MaxLineNum;
    AE_WIN_WGT  eWinWght;
    AE_WIN_CFG  strWins[AE_WIN_NUM];
    AE_WIN_CFG  strObjWins[MAX_OBJ_WIN];
    MS_U32      u4FlareHist[3][AE_HIST_BIN0];
    MS_U32      u4Hist[AE_HIST_NUM][AE_HIST_BINX];
    MS_U32      u4IRHist[AE_IR_HIST_BIN];
    MS_U32      u4HistTotalPixel[AE_HIST_NUM];
    MS_U32      u4FlickerDetectACC[2][AE_WIN_MAX_HEIGHT];
    MS_U32      u4FlickerDetectAmp[AE_WIN_MAX_HEIGHT];
} AE_STAT;

typedef struct
{
    AE_STRATEGY eStrategy;
    MS_U32      u4Weighting;
    INTP_LUT    strUpperBound;
    INTP_LUT    strLowerBound;
    MS_U32      u4BrightToneStrength;
    MS_U32      u4BrightToneSensitivity;
    MS_U32      u4DarkToneStrength;
    MS_U32      u4DarkToneSensitivity;
    MS_U32      u4AutoStrength;
    MS_U32      u4AutoSensitivity;
} AE_STRATEGY_PARAM;

typedef struct
{
    AE_HIST_METERING    strBrightTone;
    MS_U32              u4BTFinalTarget;
    MS_U32              u4BTStrength;
    MS_U32              u4BTSensitivity;
    AE_HIST_METERING    strDarkTone;
    MS_U32              u4DTFinalTarget;
    MS_U32              u4DTStrength;
    MS_U32              u4DTSensitivity;
    MS_U32              u4StsFinalTarget;
} AE_STRATEGY_BTDT;

typedef enum
{
    AE_GEN_AV,
    AE_GEN_TV,
    AE_GEN_SV,
    AE_GEN_BV,
    AE_GEN_ALL
} AE_GEN_APEX;

typedef struct
{
    MS_BOOL         bRefLV;
    AE_PLAIN_EXPO   strPlainExpo;
    AE_GEN_APEX     eOption;
    AE_APEX_EXPO    strApexExpo;
} AE_EV_CONV;

typedef struct
{
    // gain and shutter value to be set
    MS_U32  u4SensorGain;
    MS_U32  u4PrevSensorGain;

    MS_U32  u4ISPGain;
    MS_U32  u4PrevISPGain;

    MS_U32  u4TotalGain;
    MS_U32  u4PrevTotalGain;

    MS_U32  u4SensorUSec;
    MS_U32  u4PrevSensorUSec;
    MS_U32  u4Fnx10;
    MS_U32  u4PrevFnx10;

    MS_U32  u4ShutterStepGain;

    MS_BOOL bLimited;
    MS_U32  u4MinISPGain;
    MS_U32  u4MinSensorGain;
    MS_U32  u4MinShutter;
    MS_U32  u4MaxISPGain;
    MS_U32  u4MaxSensorGain;
    MS_U32  u4MaxShutter;

    MS_U32  u4HWMaxAperture;
    MS_U32  u4HWMinAperture;

    // sensor info
    MS_U32  u4HWSensorMaxGain;
    MS_U32  u4HWSensorMinGain;
    MS_U32  u4HWSensorMaxUS;
    MS_U32  u4HWSensorMinUS;
    MS_U32  u4HWSensorShutterStepNS;
    MS_U32  u4HWISPMaxGain;
} AE_EXPOVAL;

typedef struct
{
    MS_S32  i4Max;
    MS_S32  i4Min;
} AE_MAXMIN_THD;

typedef struct
{
    MS_U32  u4FNx10;
    MS_U32  u4SensorGain;
    MS_U32  u4ISPGain;
    MS_U32  u4USec;
} AE_MANUAL_PLAIN_EXP;

typedef struct
{
    MS_U32              u4EVCompGrad;
    INTP_LUT            AeHdr;
    MS_S32              i4EVComp;
    MS_U16              u2ConvOutStableThd ;
    MS_U16              u2ConvIntoStableThd;
    INTP_LUT            strConvRatio;

    AE_STRATEGY_PARAM   strStrategyParam;
    AE_BANDING          eFlicker;
    AE_FLICKER_MODE     eFlickerMode;

    AE_EXPO_TBL         strPlainExpoTbl;
    AE_EXPO_TBL         strPlainShortExpoTbl;
    AE_MANUAL_PLAIN_EXP strPlainExpo;
    AE_APEX_EXPO        strApexExpo;

    AE_WIN_WGT          eWinWght;
    AE_WIN_WGT          eChangeWinWght;
    MS_U32              u4Wghts[AE_WGT_END][MAX_STS_WIDTH*MAX_STS_HEIGHT];
    AE_EXP_MODE         eExpMode;

    AE_SCENE_MODE       eSceneMode;
    AE_SCENE            eScene;

    // Night vision
    AE_MAXMIN_THD       strIrLED;
} AE_USER_SETTING;

typedef struct
{
    MS_BOOL bEnable;
    MS_U32  u4StableY;
    MS_U32  u4UnStableCount;

    MS_U32  u4BrightYDiffThd;
    MS_U32  u4UnStableBrightCountThd;

    MS_U32  u4DarkYDiffThd;
    MS_U32  u4UnStableDarkCountThd;
} AE_TimeBuffer; //for more stable, from dark to bright or bright to dark set a threshoukd and count frame avoid AE active frequently

typedef enum
{
    eFPS_FIX,
    eFPS_FLOAT_W_STEP,
    eFPS_FLOAT_WO_STEP
} AE_FPS_CTRL;

typedef enum
{
    COMP_BY_ISP_GAIN,
    COMP_BY_SENSOR_GAIN
} AE_SHUTTER_COMP_GAIN;

typedef struct
{
    MS_S32 startx;
    MS_S32 starty;
    MS_S32 endx;
    MS_S32 endy;
    MS_S32 wght;
} AE_WIN_SPEC;

// *********************************** Algorithm function - S ***********************************
typedef MS_S32  (*AE_CalLumY)               (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_GetBV)                 (struct __cam_ae_handle_t*, AE_APEX_EXPO strExpo, MS_U32 u4AvgYx10);
typedef MS_U32  (*AE_GetLV)                 (struct __cam_ae_handle_t*, AE_APEX_EXPO strExpo);
typedef MS_S32  (*AE_ProcessAE)             (struct __cam_ae_handle_t*);
typedef MS_U32  (*AE_GetSceneTarget)        (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_GetSceneDynamicRange)  (struct __cam_ae_handle_t*);
typedef MS_U32  (*AE_GetToneBalanceTarget)  (struct __cam_ae_handle_t*);
typedef MS_U32  (*AE_GetStrategyBTDT)       (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_CalHistogram)          (struct __cam_ae_handle_t*, AE_HIST_SPEC *pHistSpec);
typedef MS_U32  (*AE_CalSortYByPcent)       (struct __cam_ae_handle_t*, MS_U8 idx, MS_BOOL bFromHigh, MS_U32 u4Pcent);
typedef MS_S32  (*AE_CalPvExpo)             (struct __cam_ae_handle_t*, AE_APEX_EXPO *pCurExpo, AE_APEX_EXPO *pNextExpo, AE_APEX_EXPO *pNextExpoShort);
typedef MS_S32  (*AE_CalSmoothExpo)         (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_CalIntpApex)           (struct __cam_ae_handle_t*, MS_S32 i4BVxBASE, AE_CAL_EXPO *pCalExpo, AE_APEX_EXPO *pOutExpo);
typedef MS_S32  (*AE_CalIntpApexShort)      (struct __cam_ae_handle_t*, MS_S32 i4BVxBASE, AE_CAL_EXPO *pCalExpoShort, AE_APEX_EXPO *pOutExpoShort);
typedef MS_S32  (*AE_CalApexTblIdx)         (struct __cam_ae_handle_t*, AE_CAL_EXPO *pCalExpo);
typedef MS_S32  (*AE_CalApexTblIdxShort)    (struct __cam_ae_handle_t*, AE_CAL_EXPO *pCalExpoShort);
typedef MS_S32  (*AE_CalApexAuto2)          (struct __cam_ae_handle_t*, MS_U8 Lower, MS_U8 Upper, AE_APEX_EXPO *pOutExpo);
typedef MS_S32  (*AE_CalApexAV2)            (struct __cam_ae_handle_t*, MS_U8 Lower, MS_U8 Upper, AE_APEX_EXPO *pOutExpo);
typedef MS_S32  (*AE_CalApexSV2)            (struct __cam_ae_handle_t*, MS_U8 Lower, MS_U8 Upper, AE_APEX_EXPO *pOutExpo);
typedef MS_S32  (*AE_CalApexTV)             (struct __cam_ae_handle_t*, MS_U8 Lower, MS_U8 Upper, AE_APEX_EXPO *pOutExpo);
typedef MS_S32  (*AE_DoDeBanding)           (struct __cam_ae_handle_t*, AE_APEX_EXPO *pExpo, AE_EXPOVAL *strExpoVal);
typedef MS_BOOL (*AE_FurtherLimitOnAperture)(struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_FindClosestAV)         (struct __cam_ae_handle_t*, MS_S32 i4AV, MS_U8 Mode, MS_U8 Nth);
typedef MS_S32  (*AE_LimitMinMax)           (struct __cam_ae_handle_t*, AE_APEX_EXPO *strCurExpo, AE_EXPOVAL *strExpoVal);
typedef MS_S32  (*AE_SetExposure)           (struct __cam_ae_handle_t*, AE_APEX_EXPO strCurExpo, AE_EXPOVAL *strExpoVal);
typedef MS_U8   (*AE_GetExpTblMaxIdx)       (struct __cam_ae_handle_t*);
typedef MS_U8   (*AE_GetExpTblMaxIdxShort)  (struct __cam_ae_handle_t*);
typedef MS_BOOL (*AE_isConverged)           (struct __cam_ae_handle_t*);
typedef MS_BOOL (*AE_isReachBoundary)       (struct __cam_ae_handle_t*);
typedef MS_BOOL (*AE_isStable)              (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_CheckLinearity)        (struct __cam_ae_handle_t*, AE_APEX_EXPO strPreExpo, AE_APEX_EXPO strCurExpo, MS_U32 u4PreYx10, MS_U32 u4CurYx10);
typedef MS_BOOL (*AE_CheckTimeBuffer)       (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_SetNthWin)             (struct __cam_ae_handle_t*, MS_S32 idx, AE_WIN win);
// *********************************** Algorithm function - E ***********************************
// ************************************** API function - S **************************************
typedef MS_S32  (*AE_SetEVComp)             (struct __cam_ae_handle_t*, MS_S32  i4EV, MS_U32  u4Grad);
typedef MS_S32  (*AE_GetEVComp)             (struct __cam_ae_handle_t*, MS_S32 *i4EV, MS_U32 *u4Grad);
typedef MS_S32  (*AE_SetExpMode)            (struct __cam_ae_handle_t*, AE_EXP_MODE  mode);
typedef MS_S32  (*AE_GetExpMode)            (struct __cam_ae_handle_t*, AE_EXP_MODE *mode);
typedef MS_S32  (*AE_SetManualExpo)         (struct __cam_ae_handle_t*, MS_U32  u4FNx10, MS_U32  u4SensorGain, MS_U32  u4ISPGain, MS_U32  u4US);
typedef MS_S32  (*AE_GetManualExpo)         (struct __cam_ae_handle_t*, MS_U32 *u4FNx10, MS_U32 *u4SensorGain, MS_U32 *u4ISPGain, MS_U32 *u4US);
typedef MS_S32  (*AE_Pause)                 (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_Resume)                (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_GetSMState)            (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_SetTarget)             (struct __cam_ae_handle_t*, INTP_LUT *target);
typedef MS_S32  (*AE_GetTarget)             (struct __cam_ae_handle_t*, INTP_LUT *target);
typedef MS_S32  (*AE_SetConvergeThd)        (struct __cam_ae_handle_t*, MS_U32 Inthd, MS_U32 Outthd);
typedef MS_S32  (*AE_GetConvergeThd)        (struct __cam_ae_handle_t*, MS_U32 *Inthd, MS_U32 *Outthd);
typedef MS_S32  (*AE_SetConvergeSpeed)      (struct __cam_ae_handle_t*, MS_U32 speed_X[4], MS_U32 speed_Y[4]);
typedef MS_S32  (*AE_GetConvergeSpeed)      (struct __cam_ae_handle_t*, MS_U32 speed_X[4], MS_U32 speed_Y[4]);
typedef MS_S32  (*AE_SetMinMaxShutterUS)    (struct __cam_ae_handle_t*, MS_U32 u4MinShutterUS, MS_U32 u4MaxShutterUS);
typedef MS_S32  (*AE_GetMinMaxShutterUS)    (struct __cam_ae_handle_t*, MS_U32 *u4MinShutterUS, MS_U32 *u4MaxShutterUS);
typedef MS_S32  (*AE_SetMinMaxAperture)     (struct __cam_ae_handle_t*, MS_U32 u4MinAperture, MS_U32 u4MaxAperture);
typedef MS_S32  (*AE_GetMinMaxAperture)     (struct __cam_ae_handle_t*, MS_U32 *u4MinAperture, MS_U32 *u4MaxAperture);
typedef MS_S32  (*AE_SetMaxGains)           (struct __cam_ae_handle_t*, MS_U32 u4MaxISPGain, MS_U32 u4MaxSensorGain);
typedef MS_S32  (*AE_GetMaxGains)           (struct __cam_ae_handle_t*, MS_U32 *u4MaxISPGain, MS_U32 *u4MaxSensorGain);
typedef MS_S32  (*AE_SetMinGains)           (struct __cam_ae_handle_t*, MS_U32 u4MinISPGain, MS_U32 u4MinSensorGain);
typedef MS_S32  (*AE_GetMinGains)           (struct __cam_ae_handle_t*, MS_U32 *u4MinISPGain, MS_U32 *u4MinSensorGain);
typedef MS_S32  (*AE_SetPlainExpTbl)        (struct __cam_ae_handle_t*, AE_EXPO_TBL *);
typedef MS_S32  (*AE_GetPlainExpTbl)        (struct __cam_ae_handle_t*, AE_EXPO_TBL *);
typedef MS_S32  (*AE_SetPlainShortExpTbl)   (struct __cam_ae_handle_t*, AE_EXPO_TBL *);
typedef MS_S32  (*AE_GetPlainShortExpTbl)   (struct __cam_ae_handle_t*, AE_EXPO_TBL *);
typedef MS_S32  (*AE_SetAeHdrRatio)         (struct __cam_ae_handle_t*, AE_HDR_TYPE *AeHdr);
typedef MS_S32  (*AE_GetAeHdrRatio)         (struct __cam_ae_handle_t*, AE_HDR_TYPE *AeHdr);
typedef MS_S32  (*AE_SetAEWinWgtType)       (struct __cam_ae_handle_t*, AE_WIN_WGT wght);
typedef MS_S32  (*AE_GetAEWinWgtType)       (struct __cam_ae_handle_t*, AE_WIN_WGT *wght);
typedef MS_S32  (*AE_SetAEWinWgtTbl)        (struct __cam_ae_handle_t*, MS_U32 *pAverWghtTbl, MS_U32 *pCenWghtTbl, MS_U32 *pSpotWghtTbl);
typedef MS_S32  (*AE_GetAEWinWgtTbl)        (struct __cam_ae_handle_t*, MS_U32 *pAverWghtTbl, MS_U32 *pCenWghtTbl, MS_U32 *pSpotWghtTbl);
typedef MS_S32  (*AE_SetFlicker)            (struct __cam_ae_handle_t*, AE_BANDING bs);
typedef MS_S32  (*AE_GetFlicker)            (struct __cam_ae_handle_t*, AE_BANDING *bs);
typedef MS_S32  (*AE_SetFlickerMode)        (struct __cam_ae_handle_t*, AE_FLICKER_MODE mode);
typedef MS_S32  (*AE_GetFlickerMode)        (struct __cam_ae_handle_t*, AE_FLICKER_MODE *mode);
typedef MS_S32  (*AE_SetAEStrategy)         (struct __cam_ae_handle_t*, AE_STRATEGY_PARAM strParam);
typedef MS_S32  (*AE_GetAEStrategy)         (struct __cam_ae_handle_t*, AE_STRATEGY_PARAM *strParam);
typedef MS_U32  (*AE_GetLumY)               (struct __cam_ae_handle_t*);
typedef MS_U32  (*AE_GetAvgY)               (struct __cam_ae_handle_t*);
typedef MS_U32  (*AE_GetHist)               (struct __cam_ae_handle_t*, MS_U32 *pHist128);
typedef MS_U32  (*AE_GetCurLV)              (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_GetCurBV)              (struct __cam_ae_handle_t*);
typedef MS_S32  (*AE_GetCurExpo)            (struct __cam_ae_handle_t*, MS_U32 *u4FNx10, MS_U32 *u4SensorGain, MS_U32 *u4ISPGain, MS_U32 *u4US);
typedef MS_S32  (*AE_GetCurShortExpo)       (struct __cam_ae_handle_t*, MS_U32 *u4FNx10, MS_U32 *u4SensorGain, MS_U32 *u4ISPGain, MS_U32 *u4US);

#if 0
typedef MS_S32  (*AE_SetFastMode)           (struct __cam_ae_handle_t*, MS_BOOL enable);
typedef MS_S32  (*AE_SetNightVisionThd)     (struct __cam_ae_handle_t*, MS_S32 i4MinTurnOnBV, MS_S32 i4MaxTurnOffBV);
typedef MS_S32  (*AE_SetScene)              (struct __cam_ae_handle_t*, AE_SCENE scene);
typedef MS_S32  (*AE_GetScene)              (struct __cam_ae_handle_t*, AE_SCENE *scene);
typedef MS_S32  (*AE_SetOpMode)             (struct __cam_ae_handle_t*, AE_OP_MODE mode);
typedef MS_S32  (*AE_SetSV)                 (struct __cam_ae_handle_t*, MS_U32 u4ISO);
typedef MS_S32  (*AE_GetSV)                 (struct __cam_ae_handle_t*, MS_U32 *u4ISO);
typedef MS_S32  (*AE_SetTV)                 (struct __cam_ae_handle_t*, MS_U32 u4US);
typedef MS_S32  (*AE_GetTV)                 (struct __cam_ae_handle_t*, MS_U32 *u4US);
typedef MS_S32  (*AE_SetAV)                 (struct __cam_ae_handle_t*, MS_U32 u4FNx10);
typedef MS_S32  (*AE_GetAV)                 (struct __cam_ae_handle_t*, MS_U32 *u4FNx10);
typedef MS_S32  (*AE_SceneMode)             (struct __cam_ae_handle_t*, AE_SCENE_MODE mode);
typedef MS_S32  (*AE_SetISO)                (struct __cam_ae_handle_t*, MS_BOOL auto_en, MS_U32 iso);
typedef MS_S32  (*AE_GetISO)                (struct __cam_ae_handle_t*, MS_U32 *iso);
typedef MS_S32  (*AE_SetGain)               (struct __cam_ae_handle_t*, MS_U32 gain);
typedef MS_S32  (*AE_GetGain)               (struct __cam_ae_handle_t*, MS_U32 *gain);
#endif
// ************************************** API function - E **************************************

typedef struct __cam_ae_handle_t
{
    // **************** Algorithm function - S ****************
    AE_CalLumY                  pAE_CalLumY;
    AE_GetBV                    pAE_GetBV;
    AE_GetLV                    pAE_GetLV;
    AE_ProcessAE                pAE_ProcessAE;
    AE_GetSceneTarget           pAE_GetSceneTarget;
    AE_GetSceneDynamicRange     pAE_GetSceneDynamicRange;
    AE_GetToneBalanceTarget     pAE_GetToneBalanceTarget;
    AE_GetStrategyBTDT          pAE_GetStrategyBTDT;
    AE_CalHistogram             pAE_CalHistogram;
    AE_CalSortYByPcent          pAE_CalSortYByPcent;
    AE_CalPvExpo                pAE_CalPvExpo;
    AE_CalSmoothExpo            pAE_CalSmoothExpo;
    AE_CalIntpApex              pAE_CalIntpApex;
    AE_CalIntpApexShort         pAE_CalIntpApexShort;
    AE_CalApexTblIdx            pAE_CalApexTblIdx;
    AE_CalApexTblIdxShort       pAE_CalApexTblIdxShort;
    AE_CalApexAuto2             pAE_CalApexAuto2;
    AE_CalApexAV2               pAE_CalApexAV2;
    AE_CalApexSV2               pAE_CalApexSV2;
    AE_CalApexTV                pAE_CalApexTV;
    AE_DoDeBanding              pAE_DoDeBanding;
    AE_FurtherLimitOnAperture   pAE_FurtherLimitOnAperture;
    AE_FindClosestAV            pAE_FindClosestAV;
    AE_LimitMinMax              pAE_LimitMinMax;
    AE_SetExposure              pAE_SetExposure;
    AE_GetExpTblMaxIdx          pAE_GetExpTblMaxIdx;
    AE_GetExpTblMaxIdxShort     pAE_GetExpTblMaxIdxShort;
    AE_isConverged              pAE_isConverged;
    AE_isReachBoundary          pAE_isReachBoundary;
    AE_isStable                 pAE_isStable;
    AE_CheckLinearity           pAE_CheckLinearity;
    AE_CheckTimeBuffer          pAE_CheckTimeBuffer;
    AE_SetNthWin                pAE_SetNthWin;
    // **************** Algorithm function - E ****************

    // ******************* API function - S *******************
    AE_SetEVComp                pAE_SetEVComp;
    AE_GetEVComp                pAE_GetEVComp;
    AE_SetExpMode               pAE_SetExpMode;
    AE_GetExpMode               pAE_GetExpMode;
    AE_SetManualExpo            pAE_SetManualExpo;
    AE_GetManualExpo            pAE_GetManualExpo;
    AE_Pause                    pAE_Pause;
    AE_Resume                   pAE_Resume;
    AE_GetSMState               pAE_GetSMState;
    AE_SetTarget                pAE_SetTarget;
    AE_GetTarget                pAE_GetTarget;
    AE_SetConvergeThd           pAE_SetConvergeThd;
    AE_GetConvergeThd           pAE_GetConvergeThd;
    AE_SetConvergeSpeed         pAE_SetConvergeSpeed;
    AE_GetConvergeSpeed         pAE_GetConvergeSpeed;
    AE_SetMinMaxShutterUS       pAE_SetMinMaxShutterUS;
    AE_GetMinMaxShutterUS       pAE_GetMinMaxShutterUS;
    AE_SetMinMaxAperture        pAE_SetMinMaxAperture;
    AE_GetMinMaxAperture        pAE_GetMinMaxAperture;
    AE_SetMaxGains              pAE_SetMaxGains;
    AE_GetMaxGains              pAE_GetMaxGains;
    AE_SetMinGains              pAE_SetMinGains;
    AE_GetMinGains              pAE_GetMinGains;
    AE_SetPlainExpTbl           pAE_SetPlainExpTbl;
    AE_SetPlainExpTbl           pAE_SetPlainShortExpTbl;
    AE_GetPlainExpTbl           pAE_GetPlainExpTbl;
    AE_GetPlainExpTbl           pAE_GetPlainShortExpTbl;
    AE_SetAeHdrRatio            pAE_SetAeHdrRatio;
    AE_GetAeHdrRatio            pAE_GetAeHdrRatio;
    AE_SetAEWinWgtType          pAE_SetAEWinWgtType;
    AE_GetAEWinWgtType          pAE_GetAEWinWgtType;
    AE_SetAEWinWgtTbl           pAE_SetAEWinWgtTbl;
    AE_GetAEWinWgtTbl           pAE_GetAEWinWgtTbl;
    AE_SetFlicker               pAE_SetFlicker;
    AE_GetFlicker               pAE_GetFlicker;
    AE_SetFlickerMode           pAE_SetFlickerMode;
    AE_GetFlickerMode           pAE_GetFlickerMode;
    AE_SetAEStrategy            pAE_SetAEStrategy;
    AE_GetAEStrategy            pAE_GetAEStrategy;

    AE_GetLumY                  pAE_GetLumY;
    AE_GetAvgY                  pAE_GetAvgY;
    AE_GetHist                  pAE_GetHist;
    AE_GetCurBV                 pAE_GetCurBV;
    AE_GetCurLV                 pAE_GetCurLV;
    AE_GetCurExpo               pAE_GetCurExpo;
    AE_GetCurShortExpo          pAE_GetCurShortExpo;
#if 0
    AE_SetFastMode              pAE_SetFastMode;
    AE_SetNightVisionThd        pAE_SetNightVisionThd;
    AE_SetScene                 pAE_SetScene;
    AE_GetScene                 pAE_GetScene;
    AE_SetOpMode                pAE_SetOpMode;
    AE_SetSV                    pAE_SetSV;
    AE_GetSV                    pAE_GetSV;
    AE_SetTV                    pAE_SetTV;
    AE_GetTV                    pAE_GetTV;
    AE_SetAV                    pAE_SetAV;
    AE_GetAV                    pAE_GetAV;
    AE_SetManualExpoWGain       pAE_SetManualExpoWGain;
    AE_GetManualExpoWGain       pAE_GetManualExpoWGain;
    AE_SceneMode                pAE_SceneMode;
    AE_SetISO                   pAE_SetISO;
    AE_GetISO                   pAE_GetISO;
    AE_SetGain                  pAE_SetGain;
    AE_GetGain                  pAE_GetGain;
#endif
    // ******************* API function - E *******************

    ///////////// state machine variables ////////////////////////
    AE_SM                       state;
    AE_EXP_MODE                 eExpMode;
    AE_OP_MODE                  eOpMode;
    MS_U32                      SyncFrameCnt;
    MS_BOOL                     bForceReCal;
    MS_BOOL                     bAECalDone;
    MS_U8                       uDbgLevel;

    // global AE setting
    MS_U32                      u4Targetx10;       // 0~2550
    INTP_LUT                    strTargetLut;
    MS_U32                      u4SceneTargetx10;  // 0~2550
    MS_U32                      u4UpperTargetx10;
    MS_U32                      u4LowerTargetx10;

    INTP_LUT                    EVLUT;
    MS_U32                      u4EVTargetx10;       // 0~2550
    MS_U32                      u4EVCompGrad;
    MS_S32                      i4EVComp;
    MS_S32                      i4EVCompValue;

    MS_U16                      u2ConvIntoStableThd;
    MS_U16                      u2ConvOutStableThd;
    MS_U16                      u2CnvgRatio;
    INTP_LUT                    strConvRatio;
    MS_U32                      i4IRFeedBakckRatio;
    MS_U32                      i4IRFeedBakckRatioPre;

    AE_BANDING                  eFlicker;
    AE_FLICKER_MODE             eFlickerMode;

    // exposure table
    AE_EXPO_TBL                 strPlainExpoTbl;
    AE_EXPO_TBL                 strPlainShortExpoTbl;
    AE_APEX_EXPOTBL             strCurExpoTbl;
    AE_APEX_EXPOTBL             strCurExpoTblShort;

    // current setting
    MS_U8                       bStable;
    MS_U8                       bReachBoundary;
    MS_U32                      u4PredYx10;
    MS_U32                      u4PreYx10;
    MS_U32                      u4CurYx10;
    MS_U32                      u4PreAvgYx10;
    MS_U32                      u4AvgYx10;
    MS_U32                      u4AvgY_IR;
    MS_U16                      u2IR_idx;
    MS_U32                      u4ISO;
    MS_U32                      u4CurLVx10;
    MS_S32                      i4CurBV;
    MS_U32                      u4AppliedGain;
    AE_EXPOVAL                  strExpoVal;
    AE_EXPOVAL                  strExpoValShort;
    INTP_LUT                    AeHdr;
    MS_BOOL                     bDoFastAE;
    MS_U8                       uHistMaxY;

    MS_U32                      u4Wghts[AE_WGT_END][MAX_STS_WIDTH*MAX_STS_HEIGHT];
    //MS_U32                      u4LumY[MAX_STS_WIDTH*MAX_STS_HEIGHT];

    MS_S32                      i4DeltaEV;
    MS_U32                      u4InitShutter;
    MS_U32                      u4InitGain;
    MS_U32                      u4InitFNum;
    MS_U32                      u4LinearityDeltaEV;
    INTP_LUT                    strTargetWeightingByLinearityLUT;
    AE_CAL_EXPO                 strCalExpo;
    AE_APEX_EXPO                strPreExpo;
    AE_APEX_EXPO                strCurExpo;
    AE_APEX_EXPO                strNextExpo;
    AE_APEX_EXPO                strNextExpoShort;
    AE_APEX_EXPO                strManualExp;
    AE_TimeBuffer               strAETimeBuffer;

    AE_STAT                     strAEStat; // iNfinity

    //// metering setting
    AE_STRATEGY_PARAM           strStrategyParam;
    AE_STRATEGY_BTDT            strStrategyBTDT;

    AE_SCENE_DR                 strSceneDR;
    AE_TONEBALANCE_TARGET       strToneBalance;

    // calibration data
    AE_CALIDATA                 strCaliData;

    // statisitcs
    AE_HIST_TYPE                eHistType;
    ISP_AE_STATIS               *pAEStatis;
    MS_S32                      error_cnt;

    // safety shutter for specific scene
    MS_BOOL                     bEnableWDR;
    MS_BOOL                     bIrLedOn;
    MS_BOOL                     bFlashOn;
    MS_BOOL                     bOneShot;
    AE_FPS_CTRL                 eFPSCtrl;
    AE_SHUTTER_COMP_GAIN        eShutterCompGain;
    MS_U32                      u4CurFPS;
    MS_U32                      u4LongShutterLVx10Thd;
    MS_BOOL                     bUseDgain2CompBanding;
    MS_U32                      u4BandingGain;

    AE_SCENE_MODE               eSceneMode;
    AE_SCENE                    eScene;
    MS_U32                      u4NightSceneExtNum;

    // Night vision
    AE_MAXMIN_THD               strIrLED;

    MS_BOOL                     user_setting_changed;
    AE_USER_SETTING             user_setting;

    MS_BOOL                     bAutoFlickerFrequencyDetection;
    //AE_FLICKER_MODE             eAutoFlickerFrequencyDetectResult;

    ISP_DBGBUF_HANDLE           isp_dbg_buf_handle;
    AeInput_t                   *AeInputParameter;
    AeOutput_t                  *AeOutputParameter;
    ///////////// internal variables ///////////////


} cam_ae_handle_t;

void    AE_InitFuncPtr(cam_ae_handle_t* handle);
void    AE_InitParameters(cam_ae_handle_t* handle);
void    AE_InitBV(cam_ae_handle_t* handle);
void    AE_ShowLUT(char *name, INTP_LUT lut);
MS_S32  AE_GetParamFromCfg(cam_ae_handle_t* handle);
MS_S32  AE_Plain2Apex(AE_EV_CONVERSION *pConv);
MS_S32  AE_Apex2Plain(AE_EV_CONV *pConv);
MS_S32  AE_CreateWghtTbl(cam_ae_handle_t* handle);
MS_S32  AE_ConversionExpoTbl(AE_APEX_EXPOTBL *pApexTbl, AE_EXPO_TBL *pCusTbl);

MS_S32  AE_ProcessAPI(cam_ae_handle_t* handle);
MS_U32  AE_FindHistInfo(cam_ae_handle_t* handle);
MS_S32  AE_FlickerFrequencyDetect(cam_ae_handle_t* handle) ;

#ifdef __cplusplus
}
#endif
#endif //__CAMERA_AUTOEXPOSURE_H__