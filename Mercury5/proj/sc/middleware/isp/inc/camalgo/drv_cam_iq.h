/*
 * mstar_iq.h
 *
 *  Created on: May 20, 2011
 *      Author: edwin.yang
 */

#ifndef MSTAR_IQ_H_
#define MSTAR_IQ_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "iq_feature.h"
#include "iq_apiset.h"
#include "iq_struct.h"
#include "isp_3a_if.h"
#include <isp_types.h>
#include "sys_MsWrapper_cus_os_sem.h"


#define lInterp(T, m, n, a, b) (a + (b - a)*(T - m)/(n - m)) //Linear interpolation
#define CLAMP(x,a,b)           (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))
#define minmax(v,a,b)          (((v)<(a))? (a) : ((v)>(b)) ? (b) : (v))
//#define exp(a, b)              (pow(a, b))
#define max2(a, b)             (((a)>(b)) ? (a) : (b))
#define max3(a, b, c)          (((a) > (b)) ? (max2(a, c)) : (max2(b, c)))
#define abs(x)                 (((x) < 0) ? (-(x)) : (x))
//#define ev(a, b)               (log2((double)(a)/(double)(b)))
#define diff(a, b)             (((a) > (b)) ? (a-b) : (b-a))

int _exp(int a, int b);

MS_S8 UartSendTrace(const char *strFormat, ...);

//Daniel
// Add API Version information by Jeffrey Chou [2017/03/15]
//#define IQ_API_VERSION_MAJOR    (0) // range [0,65535]
//#define IQ_API_VERSION_MINOR    (0) // range [0,65535]

#define RTOS_PORTING        (1)

#define YC_DOMAIN_IQ        (0)

#define VIP_USER_COLOR_SIZE (16)

#define IQ_MAX_ISO          16  // [ind0~15]
#define IQ_MAX_TEM          16  // [ind0~15, tempture]
#define IQ_MAX_CCT          3   // [L M H]
#define IQ_MAX_IR           16  // [ind0~15]
#define IQ_INTERP_STEP      194 // gain step for trigger
#define WDR_LOC_WIN_NUM_X   16
#define WDR_LOC_WIN_NUM_Y   16

#define IQ_ANTICT_STR_MAX   31

//WDR Global
#define WDR_GLOBAL_BIN          256
#define WDR_GAIN_1X             0x1000
#define WDR_SMOOTH_STEP         0x100
#define WDR_GAIN_MIN            0x800    //0x10=1x
#define WDR_GAIN_MAX            0x4000
#define WDR_USER_DEFINE_BIN     21
#define WDR_MAX_OUTPUT_Y        1023

typedef struct
{
    MS_U16 min_arr_bound[WDR_USER_DEFINE_BIN+1];
    MS_U16 max_arr_bound[WDR_USER_DEFINE_BIN+1];
    MS_U32 dark_inc_arr[WDR_USER_DEFINE_BIN+1];

    MS_U16 min_arr[WDR_USER_DEFINE_BIN+1];
    MS_U16 max_arr[WDR_USER_DEFINE_BIN+1];
    MS_U32 hist_acc_buf[WDR_GLOBAL_BIN];

    MS_U16 wdr_x[WDR_GLOBAL_BIN+1];
    MS_U16 wdr_input_curve[WDR_GLOBAL_BIN+1];
    MS_U16 wdr_output_curve[WDR_GLOBAL_BIN+1];
    MS_U16 wdr_smooth_curve[WDR_USER_DEFINE_BIN+1];

    MS_S16 WDR_StableFlag;
}IQ_WDR_GBL_PARA;

typedef enum
{
    IQ_ORIT_M0F0,                  /**< mirror, flip unchanged */
    IQ_ORIT_M1F0,                  /**< mirror changed, flip unchanged */
    IQ_ORIT_M0F1,                  /**< mirror unchanged, flip changed */
    IQ_ORIT_M1F1,                  /**< mirror and flip changed */
} IQ_ORIT;

typedef struct
{
    MS_U8  OB_EN           :1;
    MS_U8  GAMAC2A_EN      :1;
    MS_U8  LSC_EN          :1;
    MS_U8  ALSC            :1;
    MS_U8  BDNR_EN         :1;
    MS_U8  SpikeNR_EN      :1;
    MS_U8  DP_EN           :1;
    MS_U8  GE_EN           :1;
    MS_U8  BSNR_EN         :1;
    MS_U8  NM_EN           :1;
    MS_U8  DM_EN           :1;
    MS_U8  PostDN_EN       :1;
    MS_U8  FalseColor_EN   :1;
    MS_U8  GAMAA2C_EN      :1;
    MS_U8  GAMA_EN         :1;
    MS_U8  CCM_EN          :1;
    MS_U8  UVCM_EN         :1;
    MS_U8  SNR_EN          :1;
    MS_U8  DNR_EN          :1;
    MS_U8  NLM_EN          :1;
    MS_U8  FCC             :1;
    MS_U8  IHC_EN          :1;
    MS_U8  ICC_EN          :1;
    MS_U8  IBC_EN          :1;
    MS_U8  ACK_EN          :1;
    MS_U8  UVC_EN          :1;
    MS_U8  LCE_EN          :1;
    MS_U8  DLC_EN          :1;
    MS_U8  TwoDPK_EN       :1;
    MS_U8                  :3;
} IQ_SWITCH;

typedef enum
{
    IQ_DBG_LV_STS               = 0,
    IQ_DBG_LV_ALGO_PARAM        = 1,
    IQ_DBG_LV_ALGO_STS          = 2,
    IQ_DBG_LV_ALGO_TIMING       = 3,
    IQ_DBG_LV_MV_STS            = 4,
    IQ_DBG_LV_ENTER_DEFOG       = 5,
    IQ_DBG_LV_ENTER_DRC         = 6,
    IQ_DBG_LV_SHOW_DRC_MSG      = 7,
    IQ_DBG_LV_SHOW_MV_STS_MSG   = 8,
    IQ_DBG_LV_SHOW_MV_MOVE_MSG  = 9,
    IQ_DBG_LV_SHOW_DEFOG_MSG    = 10,
    IQ_DBG_LV_NUM
} IQ_DBG_LV;

typedef enum
{
    IQ_DBG_PAR_CFG = 0,
    IQ_DBG_PAR_DBG = 1,
    IQ_DBG_PAR_HAL = 2,
    IQ_DBG_PAR_NUM
} IQ_DBG_PARA_LV;

enum
{
    ERR_IQ_SUCCESS =0,
    ERR_IQ_OUT_OF_MEM,
    ERR_IQ_NO_FILE,
    ERR_IQ_BAD_TABLE,
    ERR_IQ_BAD_FILENAME,
    ERR_IQ_MOD_STOP,  //Stop Mode won't do anything
    ERR_IQ_SET_REPEAT, //same parameters are set
    ERR_IQ_SENSOR_FAIL, //not support SOC sensor
    ERR_IQ_PPSHOW_CFGON,
    ERR_IQ_PPSHOW_CFGOFF,
    ERR_IQ_API_RESET_DONE,
    ERR_IQ_DO_CHROMA_CHECK,
} IQ_ERR_CODE;

typedef enum
{
    IQ_OP_RUN,      //IQ Normal Run
    IQ_OP_TUN,      //IQ Tuning (Tool-Link)
    IQ_OP_API10,    //IQ API 1.0 Control
    IQ_OP_API20,    //IQ API 2.0 Control
    IQ_OP_STOP,     //IQ Stop
} IQ_OP;

typedef enum
{
    IQ_ML_BP = 0, //MLoad Bypass
    IQ_ML_DO,     //MLoad do
} IQ_ML_OP;

typedef enum
{
    IQ_WDR_BP = 0, //MLoad Bypass
    IQ_WDR_DO,     //MLoad do
} IQ_WDR_OP;

typedef enum   //IQ Trigger:
{
    IQ_PA_KEEP,
    IQ_PA_ALL, //all blocks update
    IQ_PA_ISO, //blocks change by ISO
    IQ_PA_CCT, //blocks change by CCT
    IQ_PA_SEL, //single block update
    IQ_PA_API, //blocks change by API
    IQ_PA_INIT,//init blocks update
    IQ_PA_MISS,//CFG parse fail make IND missing
    IQ_PA_MAX,
} IQ_PARA_CODE;



typedef enum
{
    IQ_PMOD_NOR = 0, //Normal Mode
    IQ_PMOD_NIG = 1, //Night Mode
    IQ_PMOD_MAX,
} IQ_PARA_MODE;

typedef enum
{
    IQ_API_10 = 0, //API1.0
    IQ_API_20 = 1, //API2.0
    IQ_API_MAX,
} IQ_API_MODE;

typedef enum
{
    ISO_IND0 = 0,
    ISO_IND1,
    ISO_IND2,
    ISO_IND3,
    ISO_IND4,
    ISO_IND5,
    ISO_IND6,
    ISO_IND7,
    ISO_IND8,
    ISO_IND9,
    ISO_IND10,
    ISO_IND11,
    ISO_IND12,
    ISO_IND13,
    ISO_IND14,
    ISO_IND15,
    ISO_INDMAX,
} IQ_ISO;

typedef enum
{
    IQ_OFF = 0,
    IQ_ON  = 1,
    IQ_BP_NOR,  //bypass nromal ctrl
    IQ_BP_OMX,  //bypass omx ctrl
    IQ_FR_ICC,  //Force ICC when do IHC
} IQ_FUN_EN;

typedef enum
{
    IQ_API_SINGLE = 0,
    IQ_API_MIX    = 1,
} IQ_API_Status;

typedef enum
{
    IQ_Bypass_OFF = 0,
    IQ_Bypass_ON  = 1,
} IQ_Bypass_EN;

typedef enum
{
    OMXLEV_MAX   = 100,
    OMXLEV_MORE5 = 95,
    OMXLEV_MORE4 = 90,
    OMXLEV_MORE3 = 80,
    OMXLEV_MORE2 = 70,
    OMXLEV_MORE1 = 60,
    OMXLEV_OFF   = 50,  //0~100, 50:OFF
    OMXLEV_LESS1 = 40,
    OMXLEV_LESS2 = 30,
    OMXLEV_LESS3 = 20,
    OMXLEV_LESS4 = 10,
    OMXLEV_LESS5 = 05,
    OMXLEV_MIN   = 0,
} IQ_OMX_LEV;

typedef enum
{
    CCT_L = 0, //CCT: Low
    CCT_M,     //CCT: Med
    CCT_H,     //CCT: High
} IQ_CCT;

typedef enum
{
    ENU_ML_NORMAL = 0,
    ENU_ML_OMX_CST,
    ENU_ML_OMX_BRI,
    ENU_ML_OMX_LIG,
    ENU_ML_OMX_GMA,
    ENU_ML_OMX_GMALUT,
    ENU_ML_OMX_GMALUT_YUV,
} IQ_ML_Mode; //For Menuload

typedef enum
{
    ENU_DECOMP,         //[0]
    ENU_FPN,            //[1]
    ENU_FPN_P1,         //[2]
    ENU_OBC,            //[3]
    ENU_OBC_P1,         //[4]
    ENU_GAMA_16to16_ISP,//[5]
    ENU_GAMA_C2C_P1_ISP,//[6]
    ENU_LSC,            //[7]
    ENU_LSC_P1,         //[8]
    ENU_ALSC,           //[9]
    ENU_ALSC_P1,        //[10]
    ENU_HDR,            //[11]
    ENU_HDR_16to10,     //[12]
    ENU_DPC,            //[13]
    ENU_GE,             //[14]
    ENU_ANTICT,         //[15]
    ENU_RGBIR,          //[16]
    ENU_SpikeNR,        //[17]
    ENU_SDC,            //[18]
    ENU_BSNR,           //[19]
    ENU_NM,             //[20]
    ENU_DM,             //[21]
    ENU_PostDN,         //[22]
    ENU_FalseColor,     //[23]
    ENU_GAMA_A2A_ISP,   //[24]
    ENU_MCNR,           //[25]
    ENU_NLM,            //[26]
    ENU_XNR,            //[27]
    ENU_LDC,            //[28]
    ENU_GAMA_A2C_SC,    //[29]
    ENU_CCM,            //[30]
    ENU_HSV,            //[31]
    ENU_GAMA_C2A_SC,    //[32]
    ENU_R2Y,            //[33]
    ENU_TwoDPK,         //[34]
    ENU_LCE,            //[35]
    ENU_DLC,            //[36]
    ENU_UVC,            //[37]
    ENU_IHC,            //[38]
    ENU_ICC,            //[39]
    ENU_IBC,            //[40]
    ENU_IHCICC,         //[41]
    ENU_FCC,            //[42]
    ENU_ACK,            //[43]
    ENU_YEE,            //[44]
    ENU_ACLUT,          //[45]
    ENU_WDR_GBL,        //[46]
    ENU_WDR_LOC,        //[47]
    ENU_ADJUV,          //[48]
    ENU_MXNR,           //[49]
    ENU_YUVGAMA,        //[50]
    ENU_YCUVM10,        //[51]
    ENU_COLORTRANS,     //[52]
    ENU_ITP,            //[53]
    ENU_IQINFO,         //[54]
    ENU_SHOWLUT,        //[55]
    ENU_INDTBL,         //[56]
    ENU_TEMPTURE,       //[57]
    ENU_PARAINTER,      //[58]
    ENU_EFFECT,         //[59]
    ENU_BLKMAX,
} IQ_BLK_ENUM;

typedef enum
{
    API20_AUTO = 0,   //[00]
    //API2.0
    API20_FPN,        //[01]
    API20_NR_BAYER,   //[02]
    API20_CCM,        //[03]
    API20_SAT,        //[04]
    API20_OBC,        //[05]
    API20_OBC_P1,     //[06]
    API20_FCOLOR,     //[07]
    API20_FCOLOR2,    //[08]
    API20_CR,         //[09]
    API20_NR_DeSpike, //[10]
    API20_SHP,        //[11] TwoDPK
    API20_SHP2,       //[12] YEE, ALUT
    API20_NR_3D,      //[13]
    API20_BRI,        //[14]
    API20_LIG,        //[15]
    API20_CST,        //[16]
    API20_GMA,        //[17]
    API20_CTG,        //[18]
    API20_CSA,        //[19]
    API20_NR_NLM,     //[20]
    API20_DEFOG,      //[21]
    API20_DRC,        //[22]
    API20_DPC,        //[23]
    API20_HSV,        //[24]
    API20_WDR_LOC,    //[25]
    API20_RGBIR,      //[26]
    API20_YUVGMA,     //[27]
    API20_HDR16to12,  //[28]
    API20_COLORTRANS, //[29]
    API20_HDR,        //[30]
    API20_EFFECT,     //[31]
    API20_WDR_GBL,    //[32]
    API_MAX,          //for para reset
} IQ_OMX_ENUM;

typedef struct
{
    MS_U8 DECOMP;         // [0]
    MS_U8 FPN;            // [1]
    MS_U8 FPN_P1;         // [2]
    MS_U8 OBC;            // [3]
    MS_U8 OBC_P1;         // [4]
    MS_U8 GAMA_16to16_ISP;// [5]
    MS_U8 GAMA_C2C_P1_ISP;// [6]
    MS_U8 LSC;            // [7]
    MS_U8 LSC_P1;         // [8]
    MS_U8 ALSC;           // [9]
    MS_U8 ALSC_P1;        // [10]
    MS_U8 HDR;            // [11]
    MS_U8 HDR_16to10;     // [12]
    MS_U8 DPC;            // [13]
    MS_U8 GE;             // [14]
    MS_U8 ANTICT;         // [15]
    MS_U8 RGBIR;          // [16]
    MS_U8 SpikeNR;        // [17]
    MS_U8 SDC;            // [18]
    MS_U8 BSNR;           // [19]
    MS_U8 NM;             // [20]
    MS_U8 DM;             // [21]
    MS_U8 PostDN;         // [22]
    MS_U8 FalseColor;     // [23]
    MS_U8 GAMA_A2A_ISP;   // [24]
    MS_U8 MCNR;           // [25]
    MS_U8 NLM;            // [26]
    MS_U8 XNR;            // [27]
    MS_U8 LDC;            // [28]
    MS_U8 GAMA_A2C_SC;    // [29]
    MS_U8 CCM;            // [30]
    MS_U8 HSV;            // [31]
    MS_U8 GAMA_C2A_SC;    // [32]
    MS_U8 R2Y;            // [33]
    MS_U8 TwoDPK;         // [34]
    MS_U8 LCE;            // [35]
    MS_U8 DLC;            // [36]
    MS_U8 UVC;            // [37]
    MS_U8 IHC;            // [38]
    MS_U8 ICC;            // [39]
    MS_U8 IBC;            // [40]
    MS_U8 IHCICC;         // [41]
    MS_U8 FCC;            // [42]
    MS_U8 ACK;            // [43]
    MS_U8 YEE;            // [44]
    MS_U8 ACLUT;          // [45]
    MS_U8 WDR_GBL;        // [46]
    MS_U8 WDR_LOC;        // [47]
    MS_U8 ADJUV;          // [48]
    MS_U8 MXNR;           // [49]
    MS_U8 YUVGAMA;        // [50]
    MS_U8 YCUVM10;        // [51]
    MS_U8 COLORTRANS;     // [52]
} IQ2_BLK_List;  //for block index

typedef struct
{
    //tempture ctrl
    MS_BOOL bEnable;
    MS_U32  u32Gain;
    MS_U8   u8Tempture;
    MS_U8   u8sat;
    MS_U8   u8ob;
    MS_U8   u8ge;
    MS_U8   u8spike;
    MS_U8   u8nr3d;
    MS_U8   u8nr2d[2];
    MS_U8   u8sharpness[3];
    MS_U8   u8colortone[3];
} IQ2_TEMPTURE_CFG;

/*IQ param structure*/
typedef struct
{
    //MS_U8           iq_db_enable;
    MS_U16            chip_version;
    MS_U8             IRISOTbl[IQ_MAX_IR][IQ_MAX_ISO]; //ISO index for RGBIR sensor
    MS_U32            GainTbl0[IQ_MAX_ISO];  // gain unit 1x = 1024
    IQ2_BLK_List      BlockTbl0[IQ_MAX_ISO]; //Block index for each ISO (17 isp + 13 sc)
    MS_U32            GainTbl1[IQ_MAX_ISO];  // gain unit 1x = 1024
    IQ2_BLK_List      BlockTbl1[IQ_MAX_ISO]; //Block index for each ISO (17 isp + 13 sc)
    IQ_SWITCH         iqSwitch[IQ_MAX_ISO]; //Function swtich
    MS_U8             Use_extend_iso_ind; //for extra low lux, extend iso index to virtual iso index
    MS_U8             present_ind;

    /*TEMPTURE CTRL*/
    IQ2_TEMPTURE_CFG  IQ2_TEMPTURE[IQ_MAX_TEM];

    /*i3 ISP*/
    IQ_DECOMP_CFG          IQ_DECOMP;
    IQ_FPN_CFG             IQ_FPN[IQ_MAX_ISO];
    IQ_FPN_P1_CFG          IQ_FPN_P1[IQ_MAX_ISO];
    IQ_OBC_CFG             IQ_OBC[IQ_MAX_ISO];
    IQ_OBC_P1_CFG          IQ_OBC_P1[IQ_MAX_ISO];
    IQ_GAMA_16to16_ISP_CFG IQ_GAMA_16to16_ISP[IQ_MAX_ISO];
    IQ_GAMA_C2C_P1_ISP_CFG IQ_GAMA_C2C_P1_ISP[IQ_MAX_ISO];
    IQ_LSC_CFG             IQ_LSC[IQ_MAX_CCT];
    IQ_LSC_P1_CFG          IQ_LSC_P1[IQ_MAX_CCT];
    IQ_ALSC_CFG            IQ_ALSC[IQ_MAX_CCT];
    IQ_ALSC_P1_CFG         IQ_ALSC_P1[IQ_MAX_CCT];
    IQ_HDR_CFG             IQ_HDR[IQ_MAX_ISO];
    IQ_HDR_16to10_CFG      IQ_HDR_16to10[IQ_MAX_ISO];
    IQ_DPC_CFG             IQ_DPC[IQ_MAX_ISO];
    IQ_GE_CFG              IQ_GE[IQ_MAX_ISO];
    IQ_ANTICT_CFG          IQ_ANTICT[IQ_MAX_ISO];
    IQ_RGBIR_CFG           IQ_RGBIR[IQ_MAX_ISO];
    IQ_SpikeNR_CFG         IQ_SpikeNR[IQ_MAX_ISO];
    IQ_SDC_CFG             IQ_SDC[IQ_MAX_ISO];
    IQ_BSNR_CFG            IQ_BSNR[IQ_MAX_ISO];
    IQ_NM_CFG              IQ_NM[IQ_MAX_ISO];
    IQ_DM_CFG              IQ_DM[IQ_MAX_ISO];
    IQ_PostDN_CFG          IQ_PostDN[IQ_MAX_ISO];
    IQ_FalseColor_CFG      IQ_FalseColor[IQ_MAX_ISO];
    IQ_GAMA_A2A_ISP_CFG    IQ_GAMA_A2A_ISP;

    IQ_MCNR_CFG            IQ_MCNR[IQ_MAX_ISO];
    IQ_NLM_CFG             IQ_NLM[IQ_MAX_ISO];
    IQ_XNR_CFG             IQ_XNR[IQ_MAX_ISO];
    IQ_LDC_CFG             IQ_LDC;
    IQ_GAMA_A2C_SC_CFG     IQ_GAMA_A2C_SC;
    IQ_CCM_CFG             IQ_CCM[IQ_MAX_ISO];
    IQ_HSV_CFG             IQ_HSV[IQ_MAX_ISO];
    IQ_GAMA_C2A_SC_CFG     IQ_GAMA_C2A_SC[IQ_MAX_ISO];
    IQ_R2Y_CFG             IQ_R2Y;
    IQ_TwoDPK_CFG          IQ_TwoDPK[IQ_MAX_ISO];
    IQ_LCE_CFG             IQ_LCE;
    IQ_DLC_CFG             IQ_DLC;
    IQ_UVC_CFG             IQ_UVC[IQ_MAX_ISO];
    IQ_IHC_CFG             IQ_IHC[IQ_MAX_ISO];
    IQ_ICC_CFG             IQ_ICC[IQ_MAX_ISO];
    IQ_IBC_CFG             IQ_IBC[IQ_MAX_ISO];
    IQ_IHCICC_CFG          IQ_IHCICC[IQ_MAX_ISO];
    IQ_FCC_CFG             IQ_FCC[IQ_MAX_ISO];
    IQ_ACK_CFG             IQ_ACK[IQ_MAX_ISO];
    IQ_YEE_CFG             IQ_YEE[IQ_MAX_ISO];
    IQ_ACLUT_CFG           IQ_ACLUT[IQ_MAX_ISO];
    IQ_WDR_GBL_CFG         IQ_WDR_GBL;
    IQ_WDR_LOC_CFG         IQ_WDR_LOC;
    IQ_ADJUV_CFG           IQ_ADJUV[IQ_MAX_ISO];
    IQ_MXNR_CFG            IQ_MXNR[IQ_MAX_ISO];
    IQ_YUVGAMA_CFG         IQ_YUVGAMA[IQ_MAX_ISO];
    IQ_YCUVM10_CFG         IQ_YCUVM10[IQ_MAX_ISO];
    IQ_COLORTRANS_CFG      IQ_COLORTRANS;
} MSTAR_IQ;

typedef struct
{
    //one dimention of MSTAR_IQ
    MS_U16                 chip_version;
    MS_U32                 GainTbl;  // gain unit 1x = 1024
    IQ2_BLK_List           BlockTbl; //Block index for each ISO (17 isp + 13 sc)
    IQ_SWITCH              iqSwitch; //Function swtich
    //TEMPTURE CTRL
    IQ2_TEMPTURE_CFG       IQ2_TEMPTURE;
    //ISP
    IQ_DECOMP_CFG          IQ_DECOMP;
    IQ_FPN_CFG             IQ_FPN;
    IQ_FPN_P1_CFG          IQ_FPN_P1;
    IQ_OBC_CFG             IQ_OBC;
    IQ_OBC_P1_CFG          IQ_OBC_P1;
    IQ_GAMA_16to16_ISP_CFG IQ_GAMA_16to16_ISP;
    IQ_GAMA_C2C_P1_ISP_CFG IQ_GAMA_C2C_P1_ISP;
    IQ_LSC_CFG             IQ_LSC;
    IQ_LSC_P1_CFG          IQ_LSC_P1;
    IQ_ALSC_CFG            IQ_ALSC;
    IQ_ALSC_P1_CFG         IQ_ALSC_P1;
    IQ_HDR_CFG             IQ_HDR;
    IQ_HDR_16to10_CFG      IQ_HDR_16to10;
    IQ_DPC_CFG             IQ_DPC;
    IQ_GE_CFG              IQ_GE;
    IQ_ANTICT_CFG          IQ_ANTICT;
    IQ_RGBIR_CFG           IQ_RGBIR;
    IQ_SpikeNR_CFG         IQ_SpikeNR;
    IQ_SDC_CFG             IQ_SDC;
    IQ_BSNR_CFG            IQ_BSNR;
    IQ_NM_CFG              IQ_NM;
    IQ_DM_CFG              IQ_DM;
    IQ_PostDN_CFG          IQ_PostDN;
    IQ_FalseColor_CFG      IQ_FalseColor;
    IQ_GAMA_A2A_ISP_CFG    IQ_GAMA_A2A_ISP;
    //SCL
    IQ_MCNR_CFG            IQ_MCNR;
    IQ_NLM_CFG             IQ_NLM;
    IQ_XNR_CFG             IQ_XNR;
    IQ_LDC_CFG             IQ_LDC;
    IQ_GAMA_A2C_SC_CFG     IQ_GAMA_A2C_SC;
    IQ_CCM_CFG             IQ_CCM;
    IQ_HSV_CFG             IQ_HSV;
    IQ_GAMA_C2A_SC_CFG     IQ_GAMA_C2A_SC;
    IQ_R2Y_CFG             IQ_R2Y;
    IQ_TwoDPK_CFG          IQ_TwoDPK;
    IQ_LCE_CFG             IQ_LCE;
    IQ_DLC_CFG             IQ_DLC;
    IQ_UVC_CFG             IQ_UVC;
    IQ_IHC_CFG             IQ_IHC;
    IQ_ICC_CFG             IQ_ICC;
    IQ_IBC_CFG             IQ_IBC;
    IQ_IHCICC_CFG          IQ_IHCICC;
    IQ_FCC_CFG             IQ_FCC;
    IQ_ACK_CFG             IQ_ACK;
    IQ_YEE_CFG             IQ_YEE;
    IQ_ACLUT_CFG           IQ_ACLUT;
    IQ_WDR_GBL_CFG         IQ_WDR_GBL;
    IQ_WDR_LOC_CFG         IQ_WDR_LOC;
    IQ_ADJUV_CFG           IQ_ADJUV;
    IQ_MXNR_CFG            IQ_MXNR;
    IQ_YUVGAMA_CFG         IQ_YUVGAMA;
    IQ_YCUVM10_CFG         IQ_YCUVM10;
    IQ_COLORTRANS_CFG      IQ_COLORTRANS;
} MSTAR_IQ_SUB;

typedef struct
{
    MS_U8         IRISOTbl[IQ_MAX_IR][IQ_MAX_ISO];
    MS_U32        GainTbl[IQ_MAX_ISO];  //present gain table
    IQ2_BLK_List  BlockTbl[IQ_MAX_ISO]; //present block table
    MS_U32        iso;
    MS_U32        lv;
    MS_U32        iq_ind_now;
    MS_U32        iq_step_now;  //ind step
    MS_U32        iq_ind_past1; //Avoid AE hunting_previous frame
    MS_U32        iq_ind_past2; //Avoid AE hunting_previous previous frame
    MS_U32        iq_ind_past3;
    MS_U32        ir_ind_now;//For RGB sensor
    MS_U32        iso_ind_now;//For RGB sensor
    MS_U32        iriso_ind_now;//For RGBIR sensor
    MS_U32        iq_do_noise;
    MS_U32        iq_do_color;
    MS_U32        iq_do_lutload;
    MS_U32        iq_api_forceML; //force IQ in auto_sync
    MS_U32        temp_pre;
    MS_U32        temp_now;
    MS_U32        temp_ind_pre;
    MS_U32        temp_ind_now;
    MS_U32        cct_gainR;
    MS_U32        cct_gainB;
    MS_U32        cct_ind_pre;
    MS_U32        cct_ind_now;
    MS_U32        cct_ind_alsc_pre;
    MS_U32        cct_ind_alsc_now;
    MS_U32        cct_ind_alsc_P1_pre;
    MS_U32        cct_ind_alsc_P1_now;
    MS_U32        cct_pre;
    MS_U32        cct_smo;
    MS_U32        cct_now;
    MS_U32        cct_now_WB; //CCT from WB
    MS_U32        cct_thr[IQ_MAX_ISO]; //0:L, 1:M, 2:H, else:node
    MS_U32        cct_thr_alsc[IQ_MAX_CCT]; //0:L, 1:M, 2:H
    MS_U32        cct_indm[IQ_MAX_ISO];
    MS_U32        cct_newLow;
    MS_S32        cct_smooth[32];
    MS_BOOL       cct_doCheck;
    MS_BOOL       cct_CheckDn;
    MS_U32        Gain_previous;
    MS_U32        Gain_present;
    MS_U32        AEGain_past1; //Avoid AE hunting_previous frame
    MS_U32        AEGain_past2; //Avoid AE hunting_previous previous frame
    MS_U32        AEGain_now;  //For pIQ_ISOIndexGet
    MS_U16        IRRef;
    MS_U32        IQ_OpMode;   //IQ Operation mode
    MS_BOOL       IQ_FastMode;
    MS_U8         ForceISO;
    MS_U8         ForceISOind;
    MS_U8         ForceTrig; //Force Trigger for PQ Tool, IQMode: TUNING
    MS_U8         ForceTrigMod;
    MS_U8         ForceTrigId;
    MS_U32        WDRSmooth;
    IQ_ML_OP      doMLoad;
    IQ_FUN_EN     doUVCheck;
    IQ_ML_Mode    OMXmod;
    IQ_PARA_MODE  IQ_ParaMode; //BlockTbl set for different mode set (0:Day/1:Night)
    IQ_API_MODE   IQ_ApiMode;   //API mode switch
} IQ_AAA_INFO;


typedef enum
{
    TEMPTURE_INTER_EN = 0,
    TEMPTURE_EN,
    TEMPTURE_GAIN,
    TEMPTURE_TEMPTURE,
    TEMPTURE_SAT,
    TEMPTURE_OB,
    TEMPTURE_GE,
    TEMPTURE_SPIKE,
    TEMPTURE_NR3D,
    TEMPTURE_NR2D,
    TEMPTURE_SHARPNESS,
    TEMPTURE_COLORTONE,
    TEMPTURE_PARAMAX,
} IQPARA_TEMPTURE;

typedef struct
{
    IQ_ITP_CFG interEn;
    MS_U32     inter3a;
    MS_U32     inter3a_step;
} IQPARA_INTERP;

typedef struct
{
    IQ_FPN_CFG         FPN[IQ_MAX_ISO];
    IQ_BSNR_CFG        BSNR[IQ_MAX_ISO];
    IQ_MCNR_CFG        MCNR[IQ_MAX_ISO];
    IQ_CCM_CFG         CCM[IQ_MAX_ISO];
    IQ_YCUVM10_CFG     YCUVM10[IQ_MAX_ISO];
    IQ_ADJUV_CFG       ADJUV[IQ_MAX_ISO];
    IQ_OBC_CFG         OBC[IQ_MAX_ISO];
    IQ_OBC_P1_CFG      OBC_P1[IQ_MAX_ISO];
    IQ_FalseColor_CFG  FCOLOR_0[IQ_MAX_ISO];
    IQ_GE_CFG          GE_0[IQ_MAX_ISO];
    IQ_ANTICT_CFG      GE_1[IQ_MAX_ISO];
    IQ_SpikeNR_CFG     SpikeNR[IQ_MAX_ISO];
    IQ_TwoDPK_CFG      TwoDPK[IQ_MAX_ISO];
    IQ_YEE_CFG         YEE[IQ_MAX_ISO];
    IQ_ACLUT_CFG       ACLUT[IQ_MAX_ISO];
    IQ_GAMA_C2A_SC_CFG GAMA_C2A_SC[IQ_MAX_ISO];
    IQ_YUVGAMA_CFG     YUVGAMA[IQ_MAX_ISO];
    IQ_ACK_CFG         ACK[IQ_MAX_ISO];
    IQ_IHC_CFG         IHC[IQ_MAX_ISO];
    IQ_IHCICC_CFG      IHCICC[IQ_MAX_ISO];
    IQ_ICC_CFG         ICC[IQ_MAX_ISO];
    IQ_IBC_CFG         IBC[IQ_MAX_ISO];
    IQ_NLM_CFG         NLM[IQ_MAX_ISO];
    IQ_DPC_CFG         DPC[IQ_MAX_ISO];
    IQ_HSV_CFG         HSV[IQ_MAX_ISO];
    IQ_WDR_LOC_CFG     WDR_LOC[IQ_MAX_ISO];
    IQ_WDR_LOC_CFG     WDR_GBL[IQ_MAX_ISO];
    IQ_RGBIR_CFG       RGBIR[IQ_MAX_ISO];
    IQ_XNR_CFG         XNR[IQ_MAX_ISO];
    IQ_HDR_16to10_CFG  HDR_16to10[IQ_MAX_ISO];
    IQ_COLORTRANS_CFG  COLORTRANS;
    IQ_HDR_CFG         HDR[IQ_MAX_ISO];

    MS_U32 LEV_BRI[IQ_MAX_ISO];
    MS_U32 LEV_LIG[IQ_MAX_ISO];
    MS_U32 LEV_CST[IQ_MAX_ISO];

    MS_U8              CCM_CCMSat[IQ_MAX_ISO];
    IQ_HSV_CFG         HSV_UnitCCM[IQ_MAX_ISO];
} API20_IQ_CFG;

typedef enum
{
    LEVEL_0,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    LEVEL_6,
} USER_IQ_LEVEL;

#define DLC_INPUT_VAL_BIT     10
#define DLC_INPUT_VAL_MAX     1024
#define DLC_HISTOGRAM_VAL_BIT 8
#define DLC_HISTOGRAM_VAL_MAX 256
#define DLC_HISTOGRAM_BIN     256
#define DLC_CURVE_TABLE_BIN   64

typedef struct
{
    unsigned short LumaHistogram[DLC_HISTOGRAM_BIN];
    unsigned int   total_pixel_count_reg;
    unsigned int   total_pixel_weight_reg;
    unsigned int   ucYAvg;
} DLC32Histogram;

typedef struct
{
    // Default luma curve
    MS_U8   ucCGCCGain_offset; // -31 ~ 31 (bit7 = minus, ex. 0x88 => -8)
    MS_U8   ucCGCChroma_GainLimitH; // 0x00~0x6F
    MS_U8   ucCGCChroma_GainLimitL; // 0x00~0x10
    MS_U8   ucCGCYCslope; // 0x01~0x20
    MS_U8   ucCGCYth; // 0x01
    MS_U8   ucDlcPureImageMode; // Compare difference of max and min bright
    MS_U8   ucDlcLevelLimit; // n = 0 ~ 4 => Limit n levels => ex. n=2, limit 2 level 0xF7, 0xE7
    MS_U8   ucDlcAvgDelta; // n = 0 ~ 50, default value: 12
    MS_U8   ucDlcAvgDeltaStill; // n = 0 ~ 15 => 0: disable still curve, 1 ~ 15 => 0.1 ~ 1.5 enable still curve
    MS_U8   ucDlcFastAlphaBlending; // min 17 ~ max 32
    MS_U8   ucDlcSlowEvent; // some event is triggered, DLC must do slowly // for PIP On/Off, msMultiPic.c
    MS_U8   ucDlcTimeOut; // for IsrApp.c
    MS_U8   ucDlcFlickAlphaStart; // for force to do fast DLC in a while
    MS_U8   ucDlcYAvgThresholdH; // default value: 128
    MS_U8   ucDlcYAvgThresholdL; // default value: 0
    MS_U8   ucDlcBLEPoint; // n = 24 ~ 64, default value: 48
    MS_U8   ucDlcWLEPoint; // n = 24 ~ 64, default value: 48
    MS_U8   bCGCCGainCtrl : 1; // 1: enable; 0: disable
    MS_U8   bEnableBLE : 1; // 1: enable; 0: disable
    MS_U8   bEnableWLE : 1; // 1: enable; 0: disable
    MS_U8   ucDlcYAvgThresholdM;
    MS_U8   ucDlcCurveMode;
    MS_U8   ucDlcCurveModeMixAlpha;
    MS_U8   ucDlcAlgorithmMode;
    MS_U8   ucDlcHistogramLimitCurve[DLC_CURVE_TABLE_BIN + 2];
    MS_U8   ucDlcSepPointH;
    MS_U8   ucDlcSepPointL;
    MS_U16  uwDlcBleStartPointTH;
    MS_U16  uwDlcBleEndPointTH;
    MS_U8   ucDlcCurveDiff_L_TH;
    MS_U8   ucDlcCurveDiff_H_TH;
    MS_U16  uwDlcBLESlopPoint_1;
    MS_U16  uwDlcBLESlopPoint_2;
    MS_U16  uwDlcBLESlopPoint_3;
    MS_U16  uwDlcBLESlopPoint_4;
    MS_U16  uwDlcBLESlopPoint_5;
    MS_U16  uwDlcDark_BLE_Slop_Min;
    MS_U8   ucDlcCurveDiffCoringTH;
    MS_U8   ucDlcAlphaBlendingMin;
    MS_U8   ucDlcAlphaBlendingMax;
    MS_U8   ucDlcFlicker_alpha;
    MS_U8   ucDlcYAVG_L_TH;
    MS_U8   ucDlcYAVG_H_TH;
    MS_U8   ucDlcDiffBase_L;
    MS_U8   ucDlcDiffBase_M;
    MS_U8   ucDlcDiffBase_H;
    MS_U16  ucLMaxThreshold;
    MS_U8   ucLMinThreshold;
    MS_U8   ucLMaxCorrection;
    MS_U8   ucLMinCorrection;
    MS_U8   ucRMaxThreshold;
    MS_U8   ucRMinThreshold;
    MS_U8   ucRMaxCorrection;
    MS_U8   ucRMinCorrection;
    MS_U8   ucAllowLoseContrast;
} StuDlc_FinetuneParamaters;


struct __iq_handle_t;

typedef int (*IQ_GetOBCCALIB)(struct __iq_handle_t *, u16*); //For CCM calibration
typedef int (*IQ_SetDefog)(struct __iq_handle_t *, MS_U8, MS_U32, MS_U16, MS_U16);
typedef int (*IQ_GetDefog)(struct __iq_handle_t *, MS_U8*, MS_U32*, MS_U16*, MS_U16*);
typedef int (*IQ_SetDRC)(struct __iq_handle_t *, MS_U8, MS_U32, MS_U32, MS_U32, MS_U32, MS_U32, MS_U32, MS_U32);
typedef int (*IQ_GetDRC)(struct __iq_handle_t *, MS_U8*, MS_U32*, MS_U32*, MS_U32*, MS_U32*, MS_U32*, MS_U32*, MS_U32*);
typedef int (*IQ_SetALSC)(struct __iq_handle_t *, MS_U8, MS_U16*, MS_U16*, MS_U16*);
typedef int (*IQ_GetALSC)(struct __iq_handle_t *, MS_U8*, MS_U16*, MS_U16*, MS_U16*);
typedef int (*IQ_GetIQMode)(struct __iq_handle_t* handle, MS_U32*); //interface for API (same with getParaMode)
typedef int (*IQ_SetIQMode)(struct __iq_handle_t* handle, IQ_PARA_MODE); //interface for API (same with setParaMode)
typedef int (*IQ_doAPI20_CHK)(struct __iq_handle_t *, MS_U32);
typedef int (*IQ_ALSC_MirrorFlipTbl)(struct __iq_handle_t *, char);
typedef int (*IQ_SetMode)(struct __iq_handle_t*, int );

typedef int (*IQ_ISOIndexGet)(struct __iq_handle_t *);
typedef int (*IQ_GetIQVersion) (struct __iq_handle_t *, MS_U32*, MS_U32*);
typedef int (*IQ_GetIQfileVersion) (struct __iq_handle_t *, MS_U32*, MS_U32*, MS_U32*);

typedef int (*IQ_SetIQParaInitStatus) (struct __iq_handle_t *, MS_U8);
typedef int (*IQ_GetIQParaInitStatus) (struct __iq_handle_t *, MS_U8 *);

typedef int (*IQ_GetParamFromCfg)(struct __iq_handle_t* handle);
typedef int (*IQ_SetParamToCfg)(struct __iq_handle_t* handle);

typedef int (*IQ_GetIsoInd)(struct __iq_handle_t* handle, MS_U8*);
typedef int (*IQ_SetIsoInd)(struct __iq_handle_t* handle, MS_U8);

typedef int (*IQ_GetParaMode)(struct __iq_handle_t* handle, IQ_PARA_MODE*);
typedef int (*IQ_SetParaMode)(struct __iq_handle_t* handle, IQ_PARA_MODE); //interface for internal (same with setParaMode)
typedef int (*IQ_GetApiMode)(struct __iq_handle_t* handle, IQ_API_MODE*); //interface for internal (same with getApiMode)
typedef int (*IQ_SetApiMode)(struct __iq_handle_t* handle, IQ_API_MODE); //interface for internal (same with setApiMode)
typedef int (*IQ_GetFastMode)(struct __iq_handle_t* handle, MS_BOOL*);
typedef int (*IQ_SetFastMode)(struct __iq_handle_t* handle, MS_BOOL);
typedef int (*IQ_ApiReset)(struct __iq_handle_t*, MS_U8);
typedef int (*IQ_GetYUVHISTO)(struct __iq_handle_t *, MS_U16*);

//Param Switch
typedef int (*IQ_ParamSetSwitch)(struct __iq_handle_t* handle, MS_U8 mod, MS_U8 ip_ind);
typedef int (*IQ_ParamGetSwitch)(struct __iq_handle_t* handle, MS_U8 mod, MS_U8 ip_ind);

//IQ Trigger Point
typedef int (*IQ_IQTrigger)(struct __iq_handle_t* handle, MS_U8, MS_U8);
typedef int (*IQ_Trigger_INIT)(struct __iq_handle_t* handle, MS_U8);
typedef int (*IQ_Trigger_RUNTIME)(struct __iq_handle_t* handle, MS_U8, MS_U8, MS_U8, MS_U8*);
typedef int (*IQ_Trigger_API)(struct __iq_handle_t* handle, MS_U8);

int IQ_Property_Set(IqInput_t *IqInput, DBG_PROP dbg_ind, MS_U32 val);
int IQ_Property_Get(IqInput_t *IqInput, DBG_PROP dbg_ind, MS_U32 val);


typedef struct
{
    int prv_gain;
    int curr_gain_level;
} system_iq_adjust_t;

typedef struct
{
    MS_U16 *testG;
    MS_U16 *testG1;
    MS_U16 *u16GamaLut;
    MS_U16 *u16GamaLinI3;
    MS_U16 *CstMAXI3;
    MS_U16 *CstMINI3;
} GAMA_C2A_API_BUFFER;

typedef struct __iq_handle_t
{
    MSTAR_IQ                  iq;         //For configure file structure
    MSTAR_IQ_SUB              iq_sub;     //single gain structure (assigned gain of iq)
    API20_IQ_CFG              iq_api20;   //For API
    IQPARA_INTERP             iq_interp;  //For control interp or not
    IQ_AAA_INFO               iq_info3a;  //For 3A info

    MS_U8                     IQ_filename[128];

    //---[IQ input]
    IqInput_t                 *IqInput;
    //---[IQ register shadow]
    IspRegShd_t               *IspRegShd;
    //---[IqDbgBuf]
    ISP_DBGBUF_HANDLE         IqDbgBuf;

    IQ_OP                     iq_op;

    IQ_GetOBCCALIB            pIQ_GetOBCCALIB;
    IQ_SetDefog               pIQ_SetDefog;
    IQ_GetDefog               pIQ_GetDefog;
    IQ_SetALSC                pIQ_SetALSC;
    IQ_GetALSC                pIQ_GetALSC;
    IQ_SetDRC                 pIQ_SetDRC;
    IQ_GetDRC                 pIQ_GetDRC;

    IQ_SetMode                pIQ_SetMode;
    IQ_ISOIndexGet            pIQ_ISOIndexGet;
    IQ_GetIQVersion           pIQ_GetIQVersion;
    IQ_GetIQfileVersion       pIQ_GetIQfileVersion;

    IQ_SetIQParaInitStatus    pIQ_SetIQParaInitStatus;
    IQ_GetIQParaInitStatus    pIQ_GetIQParaInitStatus;

    IQ_ALSC_MirrorFlipTbl     pIQ_ALSC_MirrorFlipTbl;

    IQ_GetParamFromCfg        pIQ_GetParamFromCfg;
    IQ_SetParamToCfg          pIQ_SetParamToCfg;
    IQ_GetIsoInd              pIQ_GetIsoInd;
    IQ_SetIsoInd              pIQ_SetIsoInd;
    IQ_GetParaMode            pIQ_GetParaMode;
    IQ_SetParaMode            pIQ_SetParaMode;
    IQ_GetApiMode             pIQ_GetApiMode;
    IQ_SetApiMode             pIQ_SetApiMode;
    IQ_GetFastMode            pIQ_GetFastMode;
    IQ_SetFastMode            pIQ_SetFastMode;
    IQ_ApiReset               pIQ_ApiReset;
    IQ_GetYUVHISTO            pIQ_GetYUVHisto;

    //Param switch
    IQ_ParamSetSwitch         pIQ_ParamSetSwitch;
    IQ_ParamGetSwitch         pIQ_ParamGetSwitch;

    //IQ trigger point
    IQ_IQTrigger              pIQ_IQTrigger;
    IQ_Trigger_INIT           pIQ_Trigger_INIT;
    IQ_Trigger_RUNTIME        pIQ_Trigger_RUNTIME;
    IQ_Trigger_API            pIQ_Trigger_API;

    //MS_U8 uIQinitDone;
    MS_U8 uIQDbgLev;          //IQ debug level
    MS_U8 uIQPPShowAPI;       //IQ para show (API)
    MS_U8 uIQPPen;            //IQ para show enable
    MS_U8 uIQPPen_CFG;        //IQ para show (Ctrl by CFG)
    MS_U8 uIQPPen_PROP;       //IQ para show (Ctrl by setProp)
    MS_U8 uIQPPdo_BlkId;      //IQ para show
    MS_U8 uIQPPdo_BlkId_PROP; //IQ para show
    MS_U8 uIQPPdo_BlkId_CFG;  //IQ para show
    MS_U8 uIQPPara_lev;       //IQ para show by level
    MS_U8 uIQPPara_lev_PROP;  //IQ para show by level
    MS_U8 uIQapi_reset;       //api id for reset function
    MS_U8 uTblScale;          //scale for table dump

    //---[Sensor Orit]
    MS_U32 orit_cur;
    MS_U32 orit_pre;

    //---[Do chroma transformation (CbCrToUV)]
    MS_U8 doChromaTrans; //IHC[3]/ICC[2]/IBC[1]/ACK[0]

    //---[WDR(GBL, LOC, Defog)]
    stuWDRIF_WDRPara wdr_para;
    IQ_WDR_GBL_PARA  wdr_gbl_para;
    FEATURE_IQ       feature_iq;

    //---[API20]
    IQAPI20_t IQAPI20;

    //---[Frame Cnt]
    MS_U32 frameCnt;

    //---[Trigger By ISO/CCT]
    MS_U8  doIP[ENU_BLKMAX];
    MS_U8  doALL[ENU_BLKMAX];
    MS_U8  doISO[ENU_BLKMAX];
    MS_U8  doCCT[ENU_BLKMAX];

    MS_U8  doAPIen [API_MAX];

    MS_U8  doIPEn  [ENU_BLKMAX];
    MS_U8  doIPTrig[ENU_BLKMAX];
    MS_U8  doIPMode[ENU_BLKMAX];    //record each block update mode: iqfile or api

    MS_U8  doIPStatus[ENU_BLKMAX];    //each block update only once, use doStatus to record update status
    MS_U8  doALLCnt;
    MS_U8  doISOCnt;
    MS_U8  doCCTCnt;

    MS_U8  *pInter;       //---[pInter]
    MS_U16 *pMLTBL;       //---[Mload table]
    MS_U16 *pCfgdata;     //---[Cfg data]

    GAMA_C2A_API_BUFFER *GAMA_BUFF;

    MS_BOOL bCheckISPInit;    //---[Internal variables]

    MS_U8 trig_alsc;
} iq_handle_t;

#ifdef __cplusplus
}
#endif
#endif /* MSTAR_IQ_H_ */
