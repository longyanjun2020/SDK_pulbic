/*
 * iq_apiset.h
 *
 *  Created on: 2016/8/16
 *      Author: Elsa-cf.Lin
 */

#ifndef __iq_apiset__
#define __iq_apiset__

#include <isp_types.h>

#define IQ_MAX_ISO  16 // [ind0~15]


typedef enum
{
    M_Hist = 0,
    M_Manual = 1,
} DEFOG_MODE;

typedef enum
{
    M_AUTO = 0,
    M_MANUAL,
    M_MODMAX,
} API_MODE;

typedef enum
{
    OPR_AUTO = 0,
    OPR_MANUAL,
    OPR_MODMAX,
} OPR_MODE;

typedef struct
{
    MS_U16 u16THRR;
    MS_U16 u16THRG;
    MS_U16 u16THRB;
    MS_U8  u8STRR;
    MS_U8  u8STRG;
    MS_U8  u8STRB;
    MS_U8  u8STEPR;
    MS_U8  u8STEPG;
    MS_U8  u8STEPB;
} NR_BAYER_PARA;

typedef struct
{
    NR_BAYER_PARA paraAPI;
} NR_BAYER_M;

typedef struct
{
    NR_BAYER_PARA paraAPI[IQ_MAX_ISO];
} NR_BAYER_A;

typedef struct
{
    MS_BOOL    APIen;
    API_MODE   APImode;
    NR_BAYER_A paraAPI_A;
    NR_BAYER_M paraAPI_M;
} IQAPI20_NR_BAYER;

typedef struct
{
    MS_U8  u8BlendRatio;
    MS_U8  u8NBR_STR;
    MS_U8  u8MEAN_STR;
    MS_U8  u8CENCOR_STR;
    MS_U8  u8MEAN_GAIN;
    MS_U16 u16NBR_THR;
    MS_U16 u16CENCOR_THR;
} NR_DeSpike_PARA;

typedef struct
{
    NR_DeSpike_PARA paraAPI;
} NR_DeSpike_M;

typedef struct
{
    NR_DeSpike_PARA paraAPI[IQ_MAX_ISO];
} NR_DeSpike_A;

typedef struct
{
    MS_BOOL      APIen;
    API_MODE     APImode;
    NR_DeSpike_A paraAPI_A;
    NR_DeSpike_M paraAPI_M;
} IQAPI20_NR_DeSpike;

typedef struct
{
    MS_U8   u8STR;
    MS_U8   u8FilterLevel;
    MS_U8   u8StrengthByY[16]; //0~63
    MS_BOOL bLSCREF_EN;
} NR_NLM_PARA;

typedef struct
{
    NR_NLM_PARA paraAPI;
} NR_NLM_M;
typedef struct
{
    NR_NLM_PARA paraAPI[IQ_MAX_ISO];
} NR_NLM_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    NR_NLM_A paraAPI_A;
    NR_NLM_M paraAPI_M;
} IQAPI20_NR_NLM;

typedef struct
{
    MS_U8 u8Y_SF_STR; //0 ~ 255(NLM??)
    MS_U8 u8Y_SF_ADAP_STR; //0 ~ 255
    MS_U8 u8Y_TF_STR_Adv; //0 ~ 255
    MS_U8 u8Y_TF_LUT_Adv[16]; //0 ~ 63
    MS_U8 u8Y_TF_STR_BY_LY_Adv[8]; //0 ~ 63
    MS_U8 u8Y_BLEND_LUT_Adv[16]; //0~31
    MS_U16 u16Y_PK_LUT_Adv[16]; //0~1023
    MS_U8 u8C_SF_STR; //0 ~ 255;
    MS_U8 u8C_TF_STR_Adv; //0 ~ 255
    MS_U8 u8C_TF_LUT_Adv[16]; //0 ~ 63
    MS_U8 u8C_TF_STR_BY_LY_Adv[8]; //0 ~ 63
} NR_3D_PARA;

typedef struct
{
    NR_3D_PARA paraAPI;
} NR_3D_M;

typedef struct
{
    NR_3D_PARA paraAPI[IQ_MAX_ISO];
} NR_3D_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    NR_3D_A  paraAPI_A;
    NR_3D_M  paraAPI_M;
} IQAPI20_NR_3D;

typedef struct
{
    MS_U16 u16CCTthr;
    MS_U16 u16Coef[9];
    MS_U8  u8CCMSat;//0~100 0:Unit matrix, 100:User matrix
} CCM_PARA;

typedef struct
{
    MS_U16 u16Coef[9];
    MS_U8  u8CCMSat;//0~100 0:Unit matrix, 100:User matrix
} CCM_M;

typedef struct
{
    MS_BOOL ISO_BPen;
    CCM_PARA paraAPI[IQ_MAX_ISO];
} CCM_A;

typedef struct
{
    MS_BOOL APIen;
    API_MODE APImode;
    CCM_A paraAPI_A;
    CCM_M paraAPI_M;
} IQAPI20_CCM;

typedef struct
{
    MS_U8 u8SatAllStr;	       //0~127
    MS_U8 u8SatByY_SFT_Adv[5]; //0~8
    MS_U8 u8SatByY_LUT_Adv[6]; //0~128
    MS_U8 u8SatByS_SFT_Adv[5]; //0~8
    MS_U8 u8SatByS_LUT_Adv[6]; //0~128
} SAT_PARA;

typedef struct
{
    SAT_PARA paraAPI;
} SAT_M;

typedef struct
{
    SAT_PARA paraAPI[IQ_MAX_ISO];
} SAT_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    SAT_A    paraAPI_A;
    SAT_M    paraAPI_M;
} IQAPI20_SAT;

typedef struct
{
    MS_U16 u16ValR;
    MS_U16 u16ValGr;
    MS_U16 u16ValGb;
    MS_U16 u16ValB;
} OBC_PARA;

typedef struct
{
    OBC_PARA paraAPI;
} OBC_M;
typedef struct
{
    OBC_PARA paraAPI[IQ_MAX_ISO];
} OBC_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    OBC_A    paraAPI_A;
    OBC_M    paraAPI_M;
} IQAPI20_OBC;

typedef struct
{
    MS_U8 u8STR;
} FCOLOR_PARA;

typedef struct
{
    FCOLOR_PARA paraAPI;
} FCOLOR_M;

typedef struct
{
    FCOLOR_PARA paraAPI[IQ_MAX_ISO];
} FCOLOR_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    FCOLOR_A paraAPI_A;
    FCOLOR_M paraAPI_M;
} IQAPI20_FCOLOR;

typedef struct
{
    MS_U8 u8STR;
} FCOLOR2_PARA;

typedef struct
{
    FCOLOR2_PARA paraAPI;
} FCOLOR2_M;

typedef struct
{
    FCOLOR2_PARA paraAPI[IQ_MAX_ISO];
} FCOLOR2_A;

typedef struct
{
    MS_BOOL   APIen;
    API_MODE  APImode;
    FCOLOR2_A paraAPI_A; //I3
    FCOLOR2_M paraAPI_M; //I3
} IQAPI20_FCOLOR2;

typedef struct
{
    MS_U8  u8STR_L;
    MS_U16 u16THR_L;
    MS_U8  u8STR_H;
    MS_U16 u16THR_H;
    MS_U8  u8STR_V2;
    MS_U16 u16THR_V2;
} CR_PARA;

typedef struct
{
    CR_PARA paraAPI;
} CR_M;
typedef struct
{
    CR_PARA paraAPI[IQ_MAX_ISO];
} CR_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    MS_BOOL  V2En;
    CR_A     paraAPI_A;
    CR_M     paraAPI_M;
} IQAPI20_CR;

typedef struct
{
    MS_U16 u16GAIN;
    MS_U8  u8STR;
    MS_U16 u16OVER;
    MS_U16 u16UNDER;
    MS_U8  u8NOISE_THR;
} SHP_LOCAL_PARA;

typedef struct
{
    SHP_LOCAL_PARA EDGE;
    SHP_LOCAL_PARA TEXTURE;
    MS_U16  u16GAIN;
    MS_U8   u8NOISE_THR;
    MS_U8   u8NOISE_STR;
    MS_U8   u8GAIN_LUT[16];
    MS_BOOL bLUMA_EN;
    MS_U16  u16LUMA_BYPASS_THR;
    MS_U8   u8Luma_LUT_STR;
    MS_U8   u8LUMA_LUT[8];
} SHP_PARA;

typedef struct
{
    SHP_PARA paraAPI;
} SHP_M;
typedef struct
{
    SHP_PARA paraAPI[IQ_MAX_ISO];
} SHP_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    SHP_A    paraAPI_A;
    SHP_M    paraAPI_M;
} IQAPI20_SHP;

typedef struct
{
    MS_U8 u8OverShootGain;
    MS_U8 u8UnderShootGain;
    MS_U8 u8CorLUT[6];
    MS_U8 u8SclLUT[6];
} SHP2_LOCAL_PARA;

typedef struct
{
    SHP2_LOCAL_PARA nEdgeCtrl;//EYEE
    SHP2_LOCAL_PARA nTextureCtrl;//YEE
    MS_U8   u8EdgeKillLUT[6];
    MS_U8   u8CornerReduce;
    MS_BOOL bDirEn;
    MS_U16  u16SharpnessUD;
    MS_U16  u16SharpnessD;
} SHP2_PARA;

typedef struct
{
    SHP2_PARA paraAPI;
} SHP2_M;

typedef struct
{
    SHP2_PARA paraAPI[IQ_MAX_ISO];
} SHP2_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    SHP2_A   paraAPI_A;
    SHP2_M   paraAPI_M;
} IQAPI20_SHP2;

typedef struct
{
    MS_U32 u32level;
} LEV_PARA;

typedef struct
{
    LEV_PARA paraAPI;
} BRI_M;
typedef struct
{
    LEV_PARA paraAPI[IQ_MAX_ISO];
} BRI_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    BRI_A    paraAPI_A;
    BRI_M    paraAPI_M;
} IQAPI20_BRI;

typedef struct
{
    LEV_PARA paraAPI;
} LIG_M;
typedef struct
{
    LEV_PARA paraAPI[IQ_MAX_ISO];
} LIG_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    LIG_A    paraAPI_A;
    LIG_M    paraAPI_M;
} IQAPI20_LIG;

typedef struct
{
    LEV_PARA paraAPI;
} CST_M;
typedef struct
{
    LEV_PARA paraAPI[IQ_MAX_ISO];
} CST_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    CST_A    paraAPI_A;
    CST_M    paraAPI_M;
} IQAPI20_CST;

typedef struct
{
    MS_U16 u16LUTR[256];
    MS_U16 u16LUTG[256];
    MS_U16 u16LUTB[256];
} GMA_PARA;

typedef struct
{
    GMA_PARA paraAPI;
} GMA_M;
typedef struct
{
    GMA_PARA paraAPI[IQ_MAX_ISO];
} GMA_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    GMA_A    paraAPI_A;
    GMA_M    paraAPI_M;
} IQAPI20_GMA;

typedef struct
{
    MS_U16 u16LUTY[256]; //0-1023
    MS_U16 u16LUTU[128]; //(IN)-512-511 (OUT)0~511
    MS_U16 u16LUTV[128]; //(IN)-512-511 (OUT)0~511
} YUVGMA_PARA;

typedef struct
{
    YUVGMA_PARA paraAPI;
} YUVGMA_M;

typedef struct
{
    YUVGMA_PARA paraAPI[IQ_MAX_ISO];
} YUVGMA_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    YUVGMA_A paraAPI_A;
    YUVGMA_M paraAPI_M;
} IQAPI20_YUVGMA;

typedef struct
{
    MS_BOOL bEn;
} CTG_PARA;

typedef struct
{
    CTG_PARA paraAPI;
} CTG_M;
typedef struct
{
    CTG_PARA paraAPI[IQ_MAX_ISO];
} CTG_A;
typedef struct
{
    MS_BOOL  APIen;
    MS_BOOL  WBCtrlen;
    API_MODE APImode;
    CTG_A    paraAPI_A;
    CTG_M    paraAPI_M;
} IQAPI20_CTG;

typedef enum
{
    IND0_Gray = 0,
    IND1_R1,
    IND2_G1,
    IND3_B1,
    IND4_C1,
    IND5_M1,
    IND6_Y1,
    IND7_R2,
    IND8_G2,
    IND9_B2,
    IND10_C2,
    IND11_M2,
    IND12_Y2,
    IND13_Skin1,
    IND14_Skin2,
    IND15_Skin3,
    IND16_MAX,
} CSA_LUTIND;

typedef enum
{
    CSA_MOD_BLUE = 0,
    CSA_MOD_GREEN,
    CSA_MOD_BG,
    CSA_MOD_SKIN,
    CSA_MOD_VIVID, //all ind
    CSA_MOD_MANUAL, //selected ind
    //CSA_MODE_BUTT
    CSA_MOD_MAX,
} CSA_MODE;

typedef struct
{
    CSA_MODE CSAmode;
    MS_U32   u32GainLuma;
    MS_U32   u32GainHue;
    MS_U32   u32GainSat;
    MS_U32   u32LumaLut[16]; //work under Manual Mode
    MS_U32   u32HueLut[16]; //work under Manual Mode
    MS_U32   u32SatLut[16]; //work under Manual Mode
} CSA_PARA;

typedef struct
{
    CSA_PARA paraAPI;
} CSA_M;
typedef struct
{
    CSA_PARA paraAPI[IQ_MAX_ISO];
} CSA_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    CSA_A    paraAPI_A;
    CSA_M    paraAPI_M;
} IQAPI20_CSA;

typedef struct
{
    MS_BOOL u8HotPixEn;    //0~1, def:1
    MS_U16  u16HotPixCompSlpoe; //0~255, def:128
    MS_BOOL u8DarkPixEn;   //0~1, def:1
    MS_U16  u16DakrPixCompSlpoe; //0~255, def:128
    MS_U16  u16DPCTH; //0~255, def:128
} DPC_PARA;

typedef struct
{
    DPC_PARA paraAPI;
} DPC_M;
typedef struct
{
    DPC_PARA paraAPI[IQ_MAX_ISO];
} DPC_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    DPC_A    paraAPI_A;
    DPC_M    paraAPI_M;
} IQAPI20_DPC;

typedef struct
{
    MS_S16 Hue[24];                //-15~15, def: 0
    MS_U16 Sat[24];                //0~255, 64->1X
    MS_S16 Hue_ForUnitCCM[24];          //-15~15, def: 0
    MS_U16 Sat_ForUnitCCM[24];          //0~255, 64->1X
    MS_U8  GlobalSat;              //0~255, 64->1X
} HSV_PARA;

typedef struct
{
    HSV_PARA paraAPI;
} HSV_M;

typedef struct
{
    HSV_PARA paraAPI[IQ_MAX_ISO];
} HSV_A;

typedef struct
{
    MS_S16 Hue[24];                //-15~15, def: 0
    MS_U16 Sat[24];                //0~255, 64->1X
} HSV_UnitCCM;

typedef struct
{
    MS_BOOL APIen;
    API_MODE APImode;
    HSV_A paraAPI_A;
    HSV_M paraAPI_M;
} IQAPI20_HSV;

typedef struct
{
    MS_U8  u8DarkGainLmtY; //0~255
    MS_U8  u8DarkGainLmtC; //0~255
    MS_U8  u8BrightGainLmtY; //0~255
    MS_U8  u8BrightGainLmtC; //0~255
    MS_U8  u8GlobalGainLmtY; //0~255
    MS_U16 u16Strength; //0-256
} WDR_PARA;

typedef struct
{
    WDR_PARA paraAPI;
} WDR_M;
typedef struct
{
    WDR_PARA paraAPI[IQ_MAX_ISO];
} WDR_A;
typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    WDR_A    paraAPI_A;
    WDR_M    paraAPI_M;
} IQAPI20_WDR;

typedef struct
{
    MS_U32 u32StrNum;
    MS_S32 s32BVLut[IQ_MAX_ISO];
    MS_S32 s32StrLut[IQ_MAX_ISO];
    MS_U32 u32DarkIncLut[21];
} WDR_GBL_PARA;

typedef struct
{
    WDR_GBL_PARA paraAPI;
} WDR_GBL_A;

typedef struct
{
    MS_S32 s32BV;
    MS_U32 u32DarkIncLut[21];
} WDR_GBL_M;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
	WDR_GBL_A paraAPI_A;
	WDR_GBL_M paraAPI_M;
} IQAPI20_WDR_GBL;

typedef struct
{
    MS_U8   u8IrPosType; //0~7, def: 0
    MS_BOOL bRemovelEn;  //0~1, def:1
    MS_U16  Ratio_R[6];
    MS_U16  Ratio_G[6];
    MS_U16  Ratio_B[6];
} RGBIR_PARA;

typedef struct
{
    RGBIR_PARA paraAPI;
} RGBIR_M;

typedef struct
{
    RGBIR_PARA paraAPI[IQ_MAX_ISO];
} RGBIR_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    RGBIR_A  paraAPI_A;
    RGBIR_M  paraAPI_M;
} IQAPI20_RGBIR;

typedef struct
{
    MS_U16 u16Start_X;
    MS_U16 u16Start_Y;
    MS_U16 u16Width;
    MS_U8  u8Height;
    MS_U16 u16Pre_Offset;
    MS_U8  u8Pre_Offset_Sign;
    MS_U16 u16Diff_TH;
    MS_U16 u16Cmp_Ratio;
    MS_U8  u8Frame_Num;
    MS_U8  u8SW_Offset_En;
    MS_U16 u16SW_Cmp_Ratio;
} FPN_PARA;

typedef struct
{
    FPN_PARA paraAPI;
} FPN_M;

typedef struct
{
    FPN_PARA paraAPI[IQ_MAX_ISO];
} FPN_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    FPN_A    paraAPI_A;
    FPN_M    paraAPI_M;
} IQAPI20_FPN;

//[DRC/DEFOG]
typedef struct
{
    MS_U32 u32WhiteLevel;
    MS_U32 u32BlackLevel;
    MS_U32 u32Asymmetry;
    MS_U32 u32BrigntEnhance;
    MS_U32 u32ManualLevel;
    MS_U32 u32AutoLevel;
} DRC_PARA;

typedef struct
{
    DRC_PARA paraAPI;
} DRC_M;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    DRC_M    paraAPI_M;
} IQAPI20_DRC;

typedef struct
{
    MS_U16 u16ManualLevel;
    MS_U16 u16AutoLevel;
} DEFOG_PARA;

typedef struct
{
    DEFOG_PARA paraAPI;
} DEFOG_M;

typedef struct
{
    MS_BOOL  APIen;
    DEFOG_MODE APImode;
    DEFOG_M  paraAPI_M;
} IQAPI20_DEFOG;

typedef struct
{
    MS_U16 u16R_OFST;//0~65535
    MS_U16 u16G_OFST;//0~65535
    MS_U16 u16B_OFST;//0~65535
    MS_U16 u16CURVE_LUT[21];//0~100
} HDR16to12_PARA;

typedef struct
{
    HDR16to12_PARA paraAPI;
} HDR16to12_M;

typedef struct
{
    HDR16to12_PARA paraAPI[IQ_MAX_ISO];
} HDR16to12_A;

typedef struct
{
    MS_BOOL     APIen;
    API_MODE    APImode;
    HDR16to12_A paraAPI_A;
    HDR16to12_M paraAPI_M;
} IQAPI20_HDR16to12;

typedef struct
{
    MS_U16 u16Y_OFST;//0~2047
    MS_U16 u16U_OFST;//0~2047
    MS_U16 u16V_OFST;//0~2047
    MS_U16 u16Matrix[9];//0~1023
} COLORTRANS_PARA;

typedef struct
{
    COLORTRANS_PARA paraAPI;
} COLORTRANS_M;

typedef struct
{
    MS_BOOL  APIen;
    COLORTRANS_M paraAPI_M;
} IQAPI20_COLORTRANS;

typedef struct
{
	MS_U16 RATIO_VS; // 0~65535
	MS_U16 TH1;
	MS_U16 TH2;
	MS_U8  UVTBL_X[8];
	MS_U16 UVTBL_Y[9];
	MS_U32 VS_NR_EN;
	MS_U16 EDGE_TH1;
	MS_U16 EDGE_TH2;
	MS_U32 DYN_RATIO_EN;
	MS_U8  GAMA_X[22];
	MS_U16 GAMA_Y[23];
} HDR_PARA;

typedef struct
{
    HDR_PARA paraAPI;
} HDR_M;

typedef struct
{
    HDR_PARA paraAPI[IQ_MAX_ISO];
} HDR_A;

typedef struct
{
    MS_BOOL  APIen;
    API_MODE APImode;
    HDR_A paraAPI_A;
    HDR_M paraAPI_M;
} IQAPI20_HDR;

typedef struct
{
    MS_BOOL  bEn;
} IQAPI20_SYS_MCNR;

typedef struct
{
    MS_BOOL  bEn;
} IQAPI20_SYS_DualSensor;

typedef struct
{
    MS_BOOL bEn;
    MS_U8   u8Level;
} EFFECT_PARA;

typedef struct
{
    EFFECT_PARA paraColorToGrey;     //0~100
    EFFECT_PARA paraSepia;           //0~100
    EFFECT_PARA paraNegative;        //0~100
    EFFECT_PARA paraSatOffset;       //0~100
    EFFECT_PARA paraSatVivid;        //0~100
    EFFECT_PARA paraSatPale;         //0~100
    EFFECT_PARA paraSharpOffset;     //0~100
    EFFECT_PARA paraBrightness;      //0~100
	EFFECT_PARA paraLightness;       //0~100
	EFFECT_PARA paraContrast;        //0~100
} EFFECT_M;

typedef struct
{
    MS_BOOL  APIen;
    MS_BOOL  ResetFag;
    EFFECT_M paraAPI_M;
} IQAPI20_EFFECT;


/*==========API Bypass==========*/
typedef enum __attribute__ ((aligned (4)))
{
    APIID_AUTO = 0,   //[00]
    //API2.0
    APIID_FPN,        //[01]
    APIID_NR_BAYER,   //[02]
    APIID_CCM,        //[03]
    APIID_SAT,        //[04]
    APIID_OBC,        //[05]
	APIID_OBC_P1,	  //[06]
	APIID_FCOLOR,     //[07]
    APIID_FCOLOR2,    //[08]
    APIID_CR,         //[09]
    APIID_NR_DeSpike, //[10]
    APIID_SHP,        //[11] TwoDPK
    APIID_SHP2,       //[12] YEE, ALUT
    APIID_NR_3D,      //[13]
    APIID_BRI,        //[14]
    APIID_LIG,        //[15]
    APIID_CST,        //[16]
    APIID_GMA,        //[17]
    APIID_CTG,        //[18]
    APIID_CSA,        //[19]
    APIID_NR_NLM,     //[20]
    APIID_DEFOG,      //[21]
    APIID_DRC,        //[22]
    APIID_DPC,        //[23]
    APIID_HSV,        //[24]
    APIID_WDR_LOC,    //[25]
    APIID_RGBIR,      //[26]
    APIID_YUVGMA,     //[27]
    APIID_HDR16to12,  //[28]
    APIID_COLORTRANS, //[29]
    APIID_HDR,        //[30]
    APIID_EFFECT,     //[31]
    APIID_WDR_GBL,    //[32]
    APIID_MAX,        //for para reset
} IQAPI20_ENUM;

//---[API Bypass]
typedef struct
{
    MS_U32 BypassCHK[APIID_MAX];
} IQAPI_Bypass;

typedef enum __attribute__ ((aligned (4)))
{
    IQAPI_Bypass_OFF = 0,
    IQAPI_Bypass_ON
} IQAPI_BypassMode;


//---[API Trigger]
typedef struct
{
    MS_U32 APICHK[APIID_MAX];
} IQAPI20_Trigger;


struct __IQAPI20_t;

//API2.0

typedef int (*IQ_API20_SETNR_Bayer)(struct __IQAPI20_t *, IQAPI20_NR_BAYER*);
typedef int (*IQ_API20_GETNR_Bayer)(struct __IQAPI20_t *, IQAPI20_NR_BAYER*);
typedef int (*IQ_API20_SETNR_DeSpike)(struct __IQAPI20_t *, IQAPI20_NR_DeSpike*);
typedef int (*IQ_API20_GETNR_DeSpike)(struct __IQAPI20_t *, IQAPI20_NR_DeSpike*);
typedef int (*IQ_API20_SETNR_Luma)(struct __IQAPI20_t *, IQAPI20_NR_NLM*);
typedef int (*IQ_API20_GETNR_Luma)(struct __IQAPI20_t *, IQAPI20_NR_NLM*);
typedef int (*IQ_API20_SETNR_3D)(struct __IQAPI20_t *, IQAPI20_NR_3D*);
typedef int (*IQ_API20_GETNR_3D)(struct __IQAPI20_t *, IQAPI20_NR_3D*);
typedef int (*IQ_API20_SETCCM)(struct __IQAPI20_t *, IQAPI20_CCM*);
typedef int (*IQ_API20_GETCCM)(struct __IQAPI20_t *, IQAPI20_CCM*);
typedef int (*IQ_API20_SETSAT)(struct __IQAPI20_t *, IQAPI20_SAT*);
typedef int (*IQ_API20_GETSAT)(struct __IQAPI20_t *, IQAPI20_SAT*);
typedef int (*IQ_API20_SETOBC)(struct __IQAPI20_t *, IQAPI20_OBC*);
typedef int (*IQ_API20_GETOBC)(struct __IQAPI20_t *, IQAPI20_OBC*);
typedef int (*IQ_API20_SETOBC_P1)(struct __IQAPI20_t *, IQAPI20_OBC*);
typedef int (*IQ_API20_GETOBC_P1)(struct __IQAPI20_t *, IQAPI20_OBC*);
typedef int (*IQ_API20_SETFCOLOR)(struct __IQAPI20_t *, IQAPI20_FCOLOR*);
typedef int (*IQ_API20_GETFCOLOR)(struct __IQAPI20_t *, IQAPI20_FCOLOR*);
typedef int (*IQ_API20_SETFCOLOR2)(struct __IQAPI20_t *, IQAPI20_FCOLOR2*);
typedef int (*IQ_API20_GETFCOLOR2)(struct __IQAPI20_t *, IQAPI20_FCOLOR2*);
typedef int (*IQ_API20_SETCR)(struct __IQAPI20_t *, IQAPI20_CR*);
typedef int (*IQ_API20_GETCR)(struct __IQAPI20_t *, IQAPI20_CR*);
typedef int (*IQ_API20_SETSharpness)(struct __IQAPI20_t *, IQAPI20_SHP*);
typedef int (*IQ_API20_GETSharpness)(struct __IQAPI20_t *, IQAPI20_SHP*);
typedef int (*IQ_API20_SETSharpness2)(struct __IQAPI20_t *, IQAPI20_SHP2*);
typedef int (*IQ_API20_GETSharpness2)(struct __IQAPI20_t *, IQAPI20_SHP2*);
typedef int (*IQ_API20_SETBrightness)(struct __IQAPI20_t *, IQAPI20_BRI*);
typedef int (*IQ_API20_GETBrightness)(struct __IQAPI20_t *, IQAPI20_BRI*);
typedef int (*IQ_API20_SETLightness)(struct __IQAPI20_t *, IQAPI20_LIG*);
typedef int (*IQ_API20_GETLightness)(struct __IQAPI20_t *, IQAPI20_LIG*);
typedef int (*IQ_API20_SETContrast)(struct __IQAPI20_t *, IQAPI20_CST*);
typedef int (*IQ_API20_GETContrast)(struct __IQAPI20_t *, IQAPI20_CST*);
typedef int (*IQ_API20_SETGamma)(struct __IQAPI20_t *, IQAPI20_GMA*);
typedef int (*IQ_API20_GETGamma)(struct __IQAPI20_t *, IQAPI20_GMA*);
typedef int (*IQ_API20_SETYUVGamma)(struct __IQAPI20_t *, IQAPI20_YUVGMA*);
typedef int (*IQ_API20_GETYUVGamma)(struct __IQAPI20_t *, IQAPI20_YUVGMA*);
typedef int (*IQ_API20_SETColorToGray)(struct __IQAPI20_t *, IQAPI20_CTG*);
typedef int (*IQ_API20_GETColorToGray)(struct __IQAPI20_t *, IQAPI20_CTG*);
typedef int (*IQ_API20_SETColorStyleAdjust)(struct __IQAPI20_t *, IQAPI20_CSA*);
typedef int (*IQ_API20_GETColorStyleAdjust)(struct __IQAPI20_t *, IQAPI20_CSA*);
typedef int (*IQ_API20_SETDPC)(struct __IQAPI20_t *, IQAPI20_DPC*);
typedef int (*IQ_API20_GETDPC)(struct __IQAPI20_t *, IQAPI20_DPC*);
typedef int (*IQ_API20_SETHSV)(struct __IQAPI20_t *, IQAPI20_HSV*);
typedef int (*IQ_API20_GETHSV)(struct __IQAPI20_t *, IQAPI20_HSV*);
typedef int (*IQ_API20_SETWDR)(struct __IQAPI20_t *, IQAPI20_WDR*);
typedef int (*IQ_API20_GETWDR)(struct __IQAPI20_t *, IQAPI20_WDR*);
typedef int (*IQ_API20_SETWDRGBL)(struct __IQAPI20_t *, IQAPI20_WDR_GBL*);
typedef int (*IQ_API20_GETWDRGBL)(struct __IQAPI20_t *, IQAPI20_WDR_GBL*);
typedef int (*IQ_API20_SETRGBIR)(struct __IQAPI20_t *, IQAPI20_RGBIR*);
typedef int (*IQ_API20_GETRGBIR)(struct __IQAPI20_t *, IQAPI20_RGBIR*);
typedef int (*IQ_API20_SETFPN)(struct __IQAPI20_t *, IQAPI20_FPN*);
typedef int (*IQ_API20_GETFPN)(struct __IQAPI20_t *, IQAPI20_FPN*);

//[DRC/DEFOG]
typedef int (*IQ_API20_SETDRC)(struct __IQAPI20_t *, IQAPI20_DRC*);
typedef int (*IQ_API20_GETDRC)(struct __IQAPI20_t *, IQAPI20_DRC*);
typedef int (*IQ_API20_SETDEFOG)(struct __IQAPI20_t *, IQAPI20_DEFOG*);
typedef int (*IQ_API20_GETDEFOG)(struct __IQAPI20_t *, IQAPI20_DEFOG*);

typedef int (*IQ_API20_SETHDR16to12)(struct __IQAPI20_t *, IQAPI20_HDR16to12*);
typedef int (*IQ_API20_GETHDR16to12)(struct __IQAPI20_t *, IQAPI20_HDR16to12*);
typedef int (*IQ_API20_SETCOLORTRANS)(struct __IQAPI20_t *, IQAPI20_COLORTRANS*);
typedef int (*IQ_API20_GETCOLORTRANS)(struct __IQAPI20_t *, IQAPI20_COLORTRANS*);

//[HDR]
typedef int (*IQ_API20_SETHDR)(struct __IQAPI20_t *, IQAPI20_HDR*);
typedef int (*IQ_API20_GETHDR)(struct __IQAPI20_t *, IQAPI20_HDR*);

//[EFFECT]
typedef int (*IQ_API20_SETEFFECT)(struct __IQAPI20_t *, IQAPI20_EFFECT*);
typedef int (*IQ_API20_GETEFFECT)(struct __IQAPI20_t *, IQAPI20_EFFECT*);

//Bypass
typedef int (*IQ_API20_SETBypassMode)(struct __IQAPI20_t *,IQAPI20_ENUM, IQAPI_BypassMode);
typedef int (*IQ_API20_GETBypassMode)(struct __IQAPI20_t *,IQAPI20_ENUM, IQAPI_BypassMode *);

//Sys
typedef int (*IQ_API20_SetEnSysMcnrMemory)(struct __IQAPI20_t *, IQAPI20_SYS_MCNR*);
typedef int (*IQ_API20_GetEnSysMcnrMemory)(struct __IQAPI20_t *, IQAPI20_SYS_MCNR*);
typedef int (*IQ_API20_SysSetDualSensorMode)(struct __IQAPI20_t *, IQAPI20_SYS_MCNR*);
typedef int (*IQ_API20_SysGetDualSensorMode)(struct __IQAPI20_t *, IQAPI20_SYS_MCNR*);

typedef struct __IQAPI20_t
{
    //---[API PARA]
    IQAPI20_NR_BAYER   NRBayer;
    IQAPI20_NR_DeSpike NRDeSpike;
    IQAPI20_NR_NLM     NRNlm;
    IQAPI20_NR_3D      NR3D;
    IQAPI20_CCM        CCM;
    IQAPI20_SAT        SAT;
    IQAPI20_OBC        OBC;
    IQAPI20_OBC        OBC_P1;
	IQAPI20_FCOLOR     FCOLOR;
    IQAPI20_FCOLOR2    FCOLOR2;
    IQAPI20_CR         CR;
    IQAPI20_SHP        SHP;
    IQAPI20_SHP2       SHP2;
    IQAPI20_BRI        BRI;
    IQAPI20_LIG        LIG;
    IQAPI20_CST        CST;
    IQAPI20_GMA        GMA;
    IQAPI20_YUVGMA     YUVGMA;
    IQAPI20_CTG        CTG;
    IQAPI20_CSA        CSA;
    IQAPI20_DPC        DPC;
    IQAPI20_HSV        HSV;
    IQAPI20_WDR        WDR_LOC;
    IQAPI20_WDR_GBL    WDR_GBL;
    IQAPI20_RGBIR      RGBIR;
    IQAPI20_FPN        FPN;
    IQAPI20_HDR16to12  HDR16to12;
    IQAPI20_COLORTRANS COLORTRANS;
    IQAPI20_HDR        HDR;
    IQAPI20_SYS_MCNR   SYS_MCNR;
    IQAPI20_SYS_DualSensor SYS_DualSensor;

    //---[Effect]
    IQAPI20_EFFECT     EFFECT;

    //---[DRC/DEFOG]
    IQAPI20_DRC        DRC;
    IQAPI20_DEFOG      DEFOG;

    //---[API Trigger]
    IQAPI20_Trigger    APITrigger;

    //---[Bypass]
    IQAPI_Bypass       BYPASS;
    IQAPI_BypassMode   BYPASSMODE;

    //---[API2.0]
    IQ_API20_SETNR_Bayer         pIQ_API20_SETNR_Bayer;
    IQ_API20_GETNR_Bayer         pIQ_API20_GETNR_Bayer;
    IQ_API20_SETNR_DeSpike       pIQ_API20_SETNR_DeSpike;
    IQ_API20_GETNR_DeSpike       pIQ_API20_GETNR_DeSpike;
    IQ_API20_SETNR_Luma          pIQ_API20_SETNR_Luma;
    IQ_API20_GETNR_Luma          pIQ_API20_GETNR_Luma;
    IQ_API20_SETNR_3D            pIQ_API20_SETNR_3D;
    IQ_API20_GETNR_3D            pIQ_API20_GETNR_3D;
    IQ_API20_SETCCM              pIQ_API20_SETCCM;
    IQ_API20_GETCCM              pIQ_API20_GETCCM;
    IQ_API20_SETSAT              pIQ_API20_SETSAT;
    IQ_API20_GETSAT              pIQ_API20_GETSAT;
    IQ_API20_SETOBC              pIQ_API20_SETOBC;
    IQ_API20_GETOBC              pIQ_API20_GETOBC;
    IQ_API20_SETOBC_P1           pIQ_API20_SETOBC_P1;
    IQ_API20_GETOBC_P1           pIQ_API20_GETOBC_P1;
	IQ_API20_SETFCOLOR           pIQ_API20_SETFCOLOR;
    IQ_API20_GETFCOLOR           pIQ_API20_GETFCOLOR;
    IQ_API20_SETFCOLOR2          pIQ_API20_SETFCOLOR2;
    IQ_API20_GETFCOLOR2          pIQ_API20_GETFCOLOR2;
    IQ_API20_SETCR               pIQ_API20_SETCR;
    IQ_API20_GETCR               pIQ_API20_GETCR;
    IQ_API20_SETSharpness        pIQ_API20_SETSharpness;
    IQ_API20_GETSharpness        pIQ_API20_GETSharpness;
    IQ_API20_SETSharpness2       pIQ_API20_SETSharpness2;
    IQ_API20_GETSharpness2       pIQ_API20_GETSharpness2;
    IQ_API20_SETBrightness       pIQ_API20_SETBrightness;
    IQ_API20_GETBrightness       pIQ_API20_GETBrightness;
    IQ_API20_SETLightness        pIQ_API20_SETLightness;
    IQ_API20_GETLightness        pIQ_API20_GETLightness;
    IQ_API20_SETContrast         pIQ_API20_SETContrast;
    IQ_API20_GETContrast         pIQ_API20_GETContrast;
    IQ_API20_SETGamma            pIQ_API20_SETGamma;
    IQ_API20_GETGamma            pIQ_API20_GETGamma;
    IQ_API20_SETYUVGamma         pIQ_API20_SETYUVGamma;
    IQ_API20_GETYUVGamma         pIQ_API20_GETYUVGamma;
    IQ_API20_SETColorToGray      pIQ_API20_SETColorToGray;
    IQ_API20_GETColorToGray      pIQ_API20_GETColorToGray;
    IQ_API20_SETColorStyleAdjust pIQ_API20_SETColorStyleAdjust;
    IQ_API20_GETColorStyleAdjust pIQ_API20_GETColorStyleAdjust;
    IQ_API20_SETDPC              pIQ_API20_SETDPC;
    IQ_API20_GETDPC              pIQ_API20_GETDPC;
    IQ_API20_SETHSV              pIQ_API20_SETHSV;
    IQ_API20_GETHSV              pIQ_API20_GETHSV;
    IQ_API20_SETWDR              pIQ_API20_SETWDR;
    IQ_API20_GETWDR              pIQ_API20_GETWDR;
    IQ_API20_SETWDRGBL           pIQ_API20_SETWDRGBL;
    IQ_API20_GETWDRGBL           pIQ_API20_GETWDRGBL;
    IQ_API20_SETRGBIR            pIQ_API20_SETRGBIR;
    IQ_API20_GETRGBIR            pIQ_API20_GETRGBIR;
    IQ_API20_SETFPN              pIQ_API20_SETFPN;
    IQ_API20_GETFPN              pIQ_API20_GETFPN;
    IQ_API20_SETHDR16to12        pIQ_API20_SETHDR16to12;
    IQ_API20_GETHDR16to12        pIQ_API20_GETHDR16to12;
    IQ_API20_SETCOLORTRANS       pIQ_API20_SETCOLORTRANS;
    IQ_API20_GETCOLORTRANS       pIQ_API20_GETCOLORTRANS;
    IQ_API20_SETHDR              pIQ_API20_SETHDR;
    IQ_API20_GETHDR              pIQ_API20_GETHDR;

    //---[Effect]
    IQ_API20_SETEFFECT           pIQ_API20_SETEFFECT;
    IQ_API20_GETEFFECT           pIQ_API20_GETEFFECT;

    //---[DRC/DEFOG]
    IQ_API20_SETDRC              pIQ_API20_SETDRC;
    IQ_API20_GETDRC              pIQ_API20_GETDRC;
    IQ_API20_SETDEFOG            pIQ_API20_SETDEFOG;
    IQ_API20_GETDEFOG            pIQ_API20_GETDEFOG;

    //---[Bypass]
    IQ_API20_SETBypassMode       pIQ_API20_SETBypassMode;
    IQ_API20_GETBypassMode       pIQ_API20_GETBypassMode;

	//---[Sys]
	IQ_API20_SetEnSysMcnrMemory	 pIQ_API20_SETEnSysMcnrMemory;
	IQ_API20_GetEnSysMcnrMemory	 pIQ_API20_GETEnSysMcnrMemory;
    IQ_API20_SysSetDualSensorMode pIQ_API20_SysSetDualSensorMode;
    IQ_API20_SysGetDualSensorMode pIQ_API20_SysGetDualSensorMode;

} IQAPI20_t;

void pIQ_API20_InitFuncPtr(IQAPI20_t *handle);
void pIQ_API20_InitParameters(IQAPI20_t *handle);

#endif /* __iq_apiset__ */
