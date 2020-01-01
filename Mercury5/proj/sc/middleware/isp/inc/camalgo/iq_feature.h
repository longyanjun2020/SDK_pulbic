/*
 * mstar_iq.h
 *
 *  Created on: May 20, 2011
 *      Author: edwin.yang
 */

#ifndef __IQ_FECTURE_H__
#define __IQ_FECTURE_H__

//#include "drv_ms_isp_hal.h"

#include <isp_types.h>

#define DLC_INPUT_VAL_BIT		    10
#define DLC_INPUT_VAL_MAX		    1024
#define DLC_HISTOGRAM_VAL_BIT	  8
#define DLC_HISTOGRAM_VAL_MAX	  256
#define DLC_HISTOGRAM_BIN		    256
#define DLC_CURVE_TABLE_BIN		  64

typedef enum {
    FIQ_DBG_LV_WDR_ENTER_DEFOG     = 1,
    FIQ_DBG_LV_WDR_ENTER_DRC       = 2,
    FIQ_DBG_LV_WDR_SHOW_DRC_MSG    = 3,
    FIQ_DBG_LV_WDR_SHOW_DEFOG_MSG  = 4,
    FIQ_DBG_LV_WDR_SHOW_GBL_MSG    = 5,
    FIQ_DBG_LV_NUM
} FEATURE_IQ_DBG_LV;

typedef struct
{
  unsigned short LumaHistogram[DLC_HISTOGRAM_BIN];
  unsigned int   total_pixel_count_reg;
  unsigned int   total_pixel_weight_reg;
  unsigned int   ucYAvg;
}DLC32Histogram1;

typedef struct
{
  // Default luma curve
  MS_U8 ucCGCCGain_offset; // -31 ~ 31 (bit7 = minus, ex. 0x88 => -8)
  MS_U8 ucCGCChroma_GainLimitH; // 0x00~0x6F
  MS_U8 ucCGCChroma_GainLimitL; // 0x00~0x10
  MS_U8 ucCGCYCslope; // 0x01~0x20
  MS_U8 ucCGCYth; // 0x01
  MS_U8 ucDlcPureImageMode; // Compare difference of max and min bright
  MS_U8 ucDlcLevelLimit; // n = 0 ~ 4 => Limit n levels => ex. n=2, limit 2 level 0xF7, 0xE7
  MS_U8 ucDlcAvgDelta; // n = 0 ~ 50, default value: 12
  MS_U8 ucDlcAvgDeltaStill; // n = 0 ~ 15 => 0: disable still curve, 1 ~ 15 => 0.1 ~ 1.5 enable still curve
  MS_U8 ucDlcFastAlphaBlending; // min 17 ~ max 32
  MS_U8 ucDlcSlowEvent; // some event is triggered, DLC must do slowly // for PIP On/Off, msMultiPic.c
  MS_U8 ucDlcTimeOut; // for IsrApp.c
  MS_U8 ucDlcFlickAlphaStart; // for force to do fast DLC in a while
  MS_U8 ucDlcYAvgThresholdH; // default value: 128
  MS_U8 ucDlcYAvgThresholdL; // default value: 0
  MS_U8 ucDlcBLEPoint; // n = 24 ~ 64, default value: 48
  MS_U8 ucDlcWLEPoint; // n = 24 ~ 64, default value: 48
  MS_U8 bCGCCGainCtrl : 1; // 1: enable; 0: disable
  MS_U8 bEnableBLE : 1; // 1: enable; 0: disable
  MS_U8 bEnableWLE : 1; // 1: enable; 0: disable
  MS_U8 ucDlcYAvgThresholdM;
  MS_U8 ucDlcCurveMode;
  MS_U8 ucDlcCurveModeMixAlpha;
  MS_U8 ucDlcAlgorithmMode;
  MS_U8 ucDlcHistogramLimitCurve[DLC_CURVE_TABLE_BIN + 2];
  MS_U8 ucDlcSepPointH;
  MS_U8 ucDlcSepPointL;
  MS_U16 uwDlcBleStartPointTH;
  MS_U16 uwDlcBleEndPointTH;
  MS_U8 ucDlcCurveDiff_L_TH;
  MS_U8 ucDlcCurveDiff_H_TH;
  MS_U16 uwDlcBLESlopPoint_1;
  MS_U16 uwDlcBLESlopPoint_2;
  MS_U16 uwDlcBLESlopPoint_3;
  MS_U16 uwDlcBLESlopPoint_4;
  MS_U16 uwDlcBLESlopPoint_5;
  MS_U16 uwDlcDark_BLE_Slop_Min;
  MS_U8 ucDlcCurveDiffCoringTH;
  MS_U8 ucDlcAlphaBlendingMin;
  MS_U8 ucDlcAlphaBlendingMax;
  MS_U8 ucDlcFlicker_alpha;
  MS_U8 ucDlcYAVG_L_TH;
  MS_U8 ucDlcYAVG_H_TH;
  MS_U8 ucDlcDiffBase_L;
  MS_U8 ucDlcDiffBase_M;
  MS_U8 ucDlcDiffBase_H;
  MS_U16 ucLMaxThreshold;
  MS_U8 ucLMinThreshold;
  MS_U8 ucLMaxCorrection;
  MS_U8 ucLMinCorrection;
  MS_U8 ucRMaxThreshold;
  MS_U8 ucRMinThreshold;
  MS_U8 ucRMaxCorrection;
  MS_U8 ucRMinCorrection;
  MS_U8 ucAllowLoseContrast;
}StuDlc_FinetuneParamaters1;

typedef struct
{
  unsigned short in_LumaHistogram[DLC_HISTOGRAM_BIN];
  unsigned int   in_total_pixel_count_reg;
  unsigned int   in_total_pixel_weight_reg;
  unsigned int   out_ucYAvg;
  signed short   WDR_calc[DLC_CURVE_TABLE_BIN+2] ;
  signed short   WDR_Para[DLC_CURVE_TABLE_BIN+2] ;
}stuWDRIF_WDRPara;

typedef struct
{
    MS_U8  enable;
    MS_U32 mode;
    MS_U16 manual_level;
    MS_U16 auto_level;
}stuWDRIF_DefogAPI;

typedef struct
{
    MS_U8  bEnable;
    MS_U32 u32WhiteLevel;
    MS_U32 u32BlackLevel;
    MS_U32 u32Asymmetry;
    MS_U32 u32BrigntEnhance;
    MS_U32 eMode;
    MS_U32 u32ManualLevel;
    MS_U32 u32AutoLevel;
}stuWDRIF_DrcAPI;

struct __feature_iq;

typedef void (*WDR_INIT)(struct __feature_iq* handle);
typedef void (*WDR_IF_Curve_Gen)(struct __feature_iq* handle, stuWDRIF_WDRPara* hist, MS_U32 wdrRatio);
typedef void (*WDR_IF_Curve_Smooth)(struct __feature_iq* handle, stuWDRIF_WDRPara* hist);
typedef void (*WDR_IF_DRC_SetAPI)(struct __feature_iq* handle, stuWDRIF_DrcAPI* api);
typedef void (*WDR_IF_DRC_GetAPI)(struct __feature_iq* handle, stuWDRIF_DrcAPI* api);
typedef void (*WDR_IF_Defog_SetAPI)(struct __feature_iq* handle, stuWDRIF_DefogAPI* api);
typedef void (*WDR_IF_Defog_GetAPI)(struct __feature_iq* handle, stuWDRIF_DefogAPI* api);
typedef void (*WDR_IF_Set_YUV_Range)(struct __feature_iq* handle, MS_U8 range);

typedef struct __feature_iq_wdr{
    //WDR curve
    MS_BOOL  bLevelCtrlByAE;
    MS_U8    uLevelMinMax[2];
    MS_U8    WDR_enable;
    MS_U8    WDR_enable_pre_state;
    MS_U8    WDR_level;
    MS_U8    WDR_stable;
    MS_S16   WDR_UpCurve[DLC_CURVE_TABLE_BIN+2] ;
    MS_S16   WDR_LoCurve[DLC_CURVE_TABLE_BIN+2] ;
    MS_U8    u8DbgLev;
    MS_U8    YUVRange;
    stuWDRIF_WDRPara               para;
    StuDlc_FinetuneParamaters1     g_DlcParameters;

    WDR_INIT                f_init;

    //defog
    stuWDRIF_DefogAPI       defog_api;
    WDR_IF_Defog_SetAPI     if_defog_setapi;
    WDR_IF_Defog_GetAPI     if_defog_getapi;

    //drc
    stuWDRIF_DrcAPI         drc_api;
    WDR_IF_DRC_SetAPI       if_drc_setapi;
    WDR_IF_DRC_GetAPI       if_drc_getapi;

    WDR_IF_Curve_Gen        if_curve_gen;
    WDR_IF_Curve_Smooth     if_curve_smooth;
    WDR_IF_Set_YUV_Range    if_set_yuv_range;

}FEATURE_IQ_WDR;



//
typedef struct __feature_iq{
      FEATURE_IQ_WDR    wdr;
}FEATURE_IQ;

void feature_iq_init(FEATURE_IQ *handle);

//int WDR_Histogram_Comput_3Cut(iq_handle_t *handle, MS_U8 enable);
//void WDR_Apply_Curve(iq_handle_t *handle)
#endif //__IQ_FECTURE_H__
