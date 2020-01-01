#include "drv_isp.h"
#include "calibration_api.h"


#define MAX_PARM_NUMBRE 6


#define MV_WIN_NUM                 25
#define CAM20_AUTO_NUM             16
#define CAM20_SDC_CTRL_ITEM_NUMBER 2
#define AWB_LV_CT_TBL_NUM          18
#define AWB_CT_TBL_NUM             10

#define MS_GAMMA_TBL               256
#define MS_ALSC_TBL_W              61
#define MS_ALSC_TBL_H              69
#define MS_ALSC_TBL                4209
#define MS_SDC_TBL                 1024
#define MS_FPN_TBL                 2816
#define MS_YUVGAMA_Y_TBL           256
#define MS_YUVGAMA_VU_TBL          128
#define MS_WDR_LOC_TBL             88

typedef struct
{
    MS_U32 cmd_type;
    MS_U16 nAPIID;
    int (*callback)(char *param_ary[], int param_num);
} excute_isp_cmd_ary;

typedef enum
{
    IQSERVER_CAMERA_CMD_SET = 0,
    IQSERVER_CAMERA_CMD_GET,
    IQSERVER_CAMERA_CMD_SET_MODE ,
    IQSERVER_CAMERA_CMD_GET_MODE,
    IQSERVER_CAMERA_CMD_GET_PIC,
    IQSERVER_CAMERA_CMD_SET_API,
    IQSERVER_CAMERA_CMD_GET_API,
    IQSERVER_CAMERA_CMD_MAX = 0x7FFFFFFF
} IQSERVER_CAMERA_EXT_CMD_TYPE;

typedef struct
{
    IQSERVER_CAMERA_EXT_CMD_TYPE CmdType;
    int             CmdLen;
} IQSERVER_CMD_HEADER;

typedef struct
{
    MS_U32 nMagicKey;
    IQSERVER_CMD_HEADER cmdheader;
    MS_U16 nAPIID;
    MS_U16 nParamNum;
} Param_hdr;

typedef struct
{
    MS_U32 nFileID;
    MS_U32 nISPVer;
    MS_U32 nDataLen;
    MS_U32 nChecksum;
    MS_U32 nMagicKey;
    MS_U32 nReserved[3];
} APIBinFile_hdr;

typedef enum
{
    ID_ISP_SetContrast = 0,
    ID_ISP_SetBrightness,
    ID_ISP_SetLightness,
    ID_ISP_SetGamma,
    ID_ISP_SetYUVGammaLut,
    ID_ISP_SetColorToGray,
    ID_ISP_SetSaturation,
    ID_ISP_SetSharpness,
    ID_ISP_SetSharpness_EX,
    ID_ISP_SetDefog,
    ID_ISP_SetDRC,
    ID_ISP_SetCCM,
    ID_ISP_SetAntiFalseColor,
    ID_ISP_SetAntiFalseColor_EX,
    ID_ISP_SetNR3D,
    ID_ISP_SetNR2DBayer,
    ID_ISP_SetNRDeSpike,
    ID_ISP_SetNRLuma,
    ID_ISP_SetCrosstalk,
    ID_ISP_SetBlackLevel,
    ID_ISP_SetBlackLevel_P1,
    //ID_ISP_SetACM,
    ID_ISP_SetLSC,
    ID_ISP_SetWDR,
    ID_ISP_SetWDR_GBL,
    ID_ISP_SetHSV,
    ID_ISP_SetRGBIR,
    ID_ISP_SetDP,
    ID_ISP_SetFPN,
    ID_ISP_SetHDR16to12,
    ID_ISP_SetHDR,
    ID_ISP_SetAEHDR,
    MAX_ISP_ID
} APIID_e;

typedef enum MS_CAM_BOOL
{
    MS_FALSE = 0,
    MS_TRUE  = !MS_FALSE,
    MS_BOOL_MAX = 0x7FFFFFFF
} MS_CAM_BOOL;

typedef enum
{
    ERR_API_SUCCESS = 0,
    ERR_SAT_X_FAIL = 256,
} MS_IQ_ERR_CODE;

typedef struct _Size_t
{
    MS_U32 width;
    MS_U32 height;
} Size_t;

typedef struct
{
    MS_U16 u2BlkSize_x;
    MS_U16 u2BlkSize_y;
    MS_U16 u2BlkNum_x;
    MS_U16 u2BlkNum_y;
} MS_AE_WIN;

typedef struct
{
    MS_U8 uAvgR;
    MS_U8 uAvgG;
    MS_U8 uAvgB;
    MS_U8 uAvgY;
} MS_AE_AVGS;

typedef struct
{
    MS_AE_AVGS stats[128 * 90];
} MS_AE_STATS;

typedef struct
{
    MS_U16 u2BlkSize_x;
    MS_U16 u2BlkSize_y;
    MS_U16 u2BlkNum_x;
    MS_U16 u2BlkNum_y;
} MS_AWB_WIN;

typedef struct
{
    MS_U8 uAvgR;
    MS_U8 uAvgG;
    MS_U8 uAvgB;
} MS_AWB_AVGS;

typedef struct
{
    MS_AWB_AVGS stats[128 * 90];
} MS_AWB_STATS;

typedef struct
{
    MS_U8 pAeBuffer[46832];
} AEHWStats_t;

typedef struct
{
    MS_U8 pAwbBuffer[34560];
} AWBHWStats_t;

typedef struct
{
    MS_U8 r;
    MS_U8 g;
    MS_U8 b;
    MS_U8 y;
} __attribute__((packed, aligned(1))) AE_SAMPLE;

typedef struct
{
    AE_SAMPLE ae_data[128 * 90];
} __attribute__((packed, aligned(1))) MS_CAM_AE_STATIS;

typedef struct
{
    ul32 iir_1[10]; /*AF horizontal IIR filter statistic*/
    ul32 :32;
    ul32 :32;
    ul32 iir_2[10]; /*AF horizontal IIR filter statistic*/
    ul32 :32;
    ul32 :32;
    ul32 luma[10]; /*AF luma statistic*/
    ul32 :32;
    ul32 :32;
    ul32 FIR_v[10]; /*AF FIR vertical filter statistic*/
    ul32 :32;
    ul32 :32;
    ul32 FIR_h[10]; /*AF FIR horizontal filter statistic*/
    ul32 :32;
    ul32 :32;
} MS_CAM_AF_STATS;

typedef struct
{
    MS_U32 start_x; /*range : 0~1023*/
    MS_U32 start_y; /*range : 0~1023*/
    MS_U32 end_x;   /*range : 0~1023*/
    MS_U32 end_y;   /*range : 0~1023*/
} MS_CAM_AF_WIN;

typedef struct
{
    MS_CAM_AF_STATS af_stats;
} MS_CAM_AF_INFO;

typedef struct
{
    MS_CAM_BOOL af_statistic_en;

} MS_CAM_AF_ATTR;

typedef struct
{
    MS_U16 iir1_a0;
    MS_U16 iir1_a1;
    MS_U16 iir1_a2;
    MS_U16 iir1_b1;
    MS_U16 iir1_b2;
    MS_U16 iir1_1st_low_clip;
    MS_U16 iir1_1st_high_clip;
    MS_U16 iir1_2nd_low_clip;
    MS_U16 iir1_2nd_high_clip;
    MS_U16 iir2_a0;
    MS_U16 iir2_a1;
    MS_U16 iir2_a2;
    MS_U16 iir2_b1;
    MS_U16 iir2_b2;
    MS_U16 iir2_1st_low_clip;
    MS_U16 iir2_1st_high_clip;
    MS_U16 iir2_2nd_low_clip;
    MS_U16 iir2_2nd_high_clip;
} MS_CAM_AF_FILTER_ATTR;

typedef struct
{
    MS_U32 int_cnt;
    MS_U32 frame_interval;
} ISP_IOCTL_INFO;

typedef enum MS_CAM20_OP_TYPE_E
{
    OP_TYP_AUTO = 0,
    OP_TYP_MANUAL = !OP_TYP_AUTO,
    OP_TYP_MODMAX = 0x7FFFFFFF
} MS_CAM20_OP_TYPE_E;

typedef enum
{
    CTRL_TYP_AUTO = 0,
    CTRL_TYP_MANUAL = 1,
    CTRL_TYP_MODMAX
} MS_CAM20_CTRL_TYPE_E;            //parameter control type

typedef enum
{
    MS_FLICKER_TYPE_DISABLE = 0,
    MS_FLICKER_TYPE_60HZ = 1,
    MS_FLICKER_TYPE_50HZ = 2
} MS_FLICKER_TYPE;

typedef enum MS_CAM_ISP_OP_MODE
{
    MS_ISP_AUTO_MODE = 0,
    MS_ISP_MANUAL_MODE = 1
} MS_CAM_ISP_OP_MODE;

typedef enum MS_CAM_ISP_SM_STATE
{
    MS_ISP_STATE_NORMAL = 0,
    MS_ISP_STATE_PAUSE = 1
} MS_CAM_ISP_SM_STATE;

typedef struct MS_FRAMESIZETYPE
{
    MS_U32 nWidth;
    MS_U32 nHeight;
} MS_FRAMESIZETYPE;

/** @brief Sensor descriptor return from sensor driver*/
typedef struct MS_CAM_SENSOR_IDTYPE
{
    MS_U32 sensor_id; /** < sensor id*/
    MS_U8 strSensor_id[32];
} MS_CAM_SENSOR_IDTYPE;

typedef struct MS_CAM_SENSORMODETYPE
{
    MS_U32 nFrameRate;
    MS_CAM_BOOL bOneShot;
    MS_FRAMESIZETYPE sFrameSize;
} MS_CAM_SENSORMODETYPE;

typedef struct MS_CAM_COLORCONVERSIONTYPE
{
    MS_S32 xColorMatrix[3][3];
    MS_S32 xColorOffset[4];
} MS_CAM_COLORCONVERSIONTYPE;

typedef struct MS_CAM_SCALEFACTORTYPE
{
    /*in percentage*/
    MS_S32 xWidth;
    MS_S32 xHeight;
} MS_CAM_SCALEFACTORTYPE;

typedef struct MS_CAM_COLORENHANCEMENTTYPE
{
    MS_U16 nCustomizedU;
    MS_U16 nCustomizedV;
} MS_CAM_COLORENHANCEMENTTYPE;

typedef struct MS_CAM20_COLORTOGRAY_ATTR_S
{
    MS_CAM_BOOL nEn;    //0 ~ 1
} MS_CAM20_COLORTOGRAY_ATTR_S;

typedef struct
{
    MS_CAM20_COLORTOGRAY_ATTR_S paraAPI;
} COLORTOGRAY_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_COLORTOGRAY_ATTR_S paraAPI[CAM20_AUTO_NUM];
} COLORTOGRAY_AUTO_ATTR_S;

typedef struct MS_CAM20_COLORTOGRAY
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM_BOOL bWBCtrlEnable;
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    COLORTOGRAY_AUTO_ATTR_S stAuto;
    COLORTOGRAY_MANUAL_ATTR_S stManual;
} MS_CAM20_COLORTOGRAY;
typedef struct MS_CAM_FRAMESTABTYPE
{
    MS_CAM_BOOL bStab;
} MS_CAM_FRAMESTABTYPE;

typedef struct MS_CAM_ROTATIONTYPE
{
    MS_U32 nRotation;
} MS_CAM_ROTATIONTYPE;

typedef enum
{
    CAMSENSOR_NO_MIRROR_FLIP,       // mirror, flip
    CAMSENSOR_FLIP,
    CAMSENSOR_MIRROR,
    CAMSENSOR_MIRROR_FLIP,
} MS_MIRRORTYPE;

typedef struct MS_CAM_MIRRORTYPE
{
    MS_MIRRORTYPE eMirror;
    //CAMSENSOR_ORIT eMirror;
} MS_CAM_MIRRORTYPE;

typedef enum
{
    MS_CAM_BAYER_RG = 0,
    MS_CAM_BAYER_GR = 1,
    MS_CAM_BAYER_BG = 2,
    MS_CAM_BAYER_GB = 3
} MS_CAM_SEN_BAYER;

typedef enum
{
    MS_CAM_ISP_DATAPRECISION_8,
    MS_CAM_ISP_DATAPRECISION_10,
    MS_CAM_ISP_DATAPRECISION_12,
    MS_CAM_ISP_DATAPRECISION_16
} MS_CAM_ISP_DATAPRECISION;

typedef struct MS_CAM_SENSORINFO
{
    MS_U32 u4Width;
    MS_U32 u4Height;
    MS_CAM_SEN_BAYER BayerID;
    MS_CAM_ISP_DATAPRECISION Precision;
} MS_CAM_SENSORINFO;

typedef struct MS_CAM_POINTTYPE
{
    //the offset(point) to the original image
    MS_S32 nX;
    MS_S32 nY;
} MS_CAM_POINTTYPE;

typedef enum MS_AWB_CONTROL_MODE_
{
    MS_AWB_CONTROL_OFF = 0,
    MS_AWB_CONTROL_AUTO,
    MS_AWB_CONTROL_SUNLIGHT,        // Referenced in JSR-234
    MS_AWB_CONTROL_CLOUDY,
    MS_AWB_CONTROL_SHADE,
    MS_AWB_CONTROL_TUNGSTEN,
    MS_AWB_CONTROL_FLUORESCENT,
    MS_AWB_CONTROL_INCANDESCENT,
    MS_AWB_CONTROL_FLASH,           // Optimal for device's integrated flash
    MS_AWB_CONTROL_HORIZON,
    MS_AWB_CONTROL_NUM
} MS_WHITEBALCONTROLTYPE;

typedef struct MS_CAM_WHITEBALCONTROLTYPE
{
    MS_WHITEBALCONTROLTYPE eWhiteBalControl;
    //AWB_SCENE eWhiteBalControl;
} MS_CAM_WHITEBALCONTROLTYPE;

typedef struct MS_CAM_MWB_ATTR
{
    MS_U16 u2Rgain;         //RW, Multiplier for R  color channel, Range: [0x0, 0x2000]
    MS_U16 u2Grgain;        //RW, Multiplier for Gr color channel, Range: [0x0, 0x2000]
    MS_U16 u2Gbgain;        //RW, Multiplier for Gb color channel, Range: [0x0, 0x2000]
    MS_U16 u2Bgain;         //RW, Multiplier for B  color channel, Range: [0x0, 0x2000]
} MS_CAM_MWB_ATTR;

typedef struct MS_CAM_AWB_ATTR
{
    MS_U16 u2Speed;         //RW, AWB converging speed, Range: [0x1, 0x64]
} MS_CAM_AWB_ATTR;

typedef enum
{
    MS_ExposureControlOff = 0,
    MS_ExposureControlAuto,
    MS_ExposureControlNight,
    MS_ExposureControlBackLight,
    MS_ExposureControlSpotLight,
    MS_ExposureControlSports,
    MS_ExposureControlSnow,
    MS_ExposureControlBeach,
    MS_ExposureControlLargeAperture,
    MS_ExposureControlSmallApperture,
    MS_ExposureControlKhronosExtensions = 0x6F000000, /**< Reserved region for introducing Khronos Standard Extensions */
    MS_ExposureControlVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
    MS_ExposureControlMax = 0x7FFFFFFF
} MS_EXPOSURECONTROLTYPE;

typedef struct MS_CAM_EXPOSURECONTROLTYPE
{
    MS_EXPOSURECONTROLTYPE eExposureControl;
    //MS_U32 eExposureControl;
} MS_CAM_EXPOSURECONTROLTYPE;

typedef struct
{
    MS_U32 nlev;    //0 ~ 100
} MS_CAM20_LEV_ATTR_S;

typedef struct
{
    MS_CAM20_LEV_ATTR_S paraAPI;
} CONTRAST_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_LEV_ATTR_S paraAPI[CAM20_AUTO_NUM];
} CONTRAST_AUTO_ATTR_S;

typedef struct MS_CAM20_CONTRASTTYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    CONTRAST_AUTO_ATTR_S stAuto;
    CONTRAST_MANUAL_ATTR_S stManual;
} MS_CAM20_CONTRASTTYPE;

typedef struct
{
    MS_CAM20_LEV_ATTR_S paraAPI;
} BRIGHTNESS_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_LEV_ATTR_S paraAPI[CAM20_AUTO_NUM];
} BRIGHTNESS_AUTO_ATTR_S;

typedef struct MS_CAM20_BRIGHTNESSTYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    BRIGHTNESS_AUTO_ATTR_S stAuto;
    BRIGHTNESS_MANUAL_ATTR_S stManual;
} MS_CAM20_BRIGHTNESSTYPE;

typedef struct MS_CAM_GAMMA_LUT_TYPE
{
    MS_U16 nLutR[256];
    MS_U16 nLutG[256];
    MS_U16 nLutB[256];
} MS_CAM_GAMMA_LUT_TYPE;

typedef struct MS_CAM20_GAMMA_LUT_ATTR_S
{
    MS_U16 nLutR[256];  //0 ~ 1023
    MS_U16 nLutG[256];  //0 ~ 1023
    MS_U16 nLutB[256];  //0 ~ 1023
} MS_CAM20_GAMMA_LUT_ATTR_S;

typedef struct
{
    MS_CAM20_GAMMA_LUT_ATTR_S paraAPI;
} GAMMA_LUT_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_GAMMA_LUT_ATTR_S paraAPI[CAM20_AUTO_NUM];
} GAMMA_LUT_AUTO_ATTR_S;

typedef struct MS_CAM20_GAMMA_LUT_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    GAMMA_LUT_AUTO_ATTR_S stAuto;
    GAMMA_LUT_MANUAL_ATTR_S stManual;
} MS_CAM20_GAMMA_LUT_TYPE;

typedef struct MS_CAM20_YUVGAMMA_LUT_ATTR_S
{
    MS_U16 nLutY[256];  //0 ~ 1023
    MS_U16 nLutU[128];  //0 ~  511
    MS_U16 nLutV[128];  //0 ~  511
} MS_CAM20_YUVGAMMA_LUT_ATTR_S;

typedef struct
{
    MS_CAM20_YUVGAMMA_LUT_ATTR_S paraAPI;
} YUVGAMMA_LUT_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_YUVGAMMA_LUT_ATTR_S paraAPI[CAM20_AUTO_NUM];
} YUVGAMMA_LUT_AUTO_ATTR_S;

typedef struct MS_CAM20_YUVGAMMA_LUT_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    YUVGAMMA_LUT_AUTO_ATTR_S stAuto;
    YUVGAMMA_LUT_MANUAL_ATTR_S stManual;
} MS_CAM20_YUVGAMMA_LUT_TYPE;

typedef struct MS_CAM20_SHARPNESS2_LOCAL_ATTR_S
{
    MS_U8 u8OverShootGain;      //0 ~ 255, def: 128
    MS_U8 u8UnderShootGain;     //0 ~ 255, def: 128
    MS_U8 u8CorLUT[6];          //0 ~ 255, def: 0
    MS_U8 u8SclLUT[6];          //0 ~ 255, def: 0
} MS_CAM20_SHARPNESS2_LOCAL_ATTR_S;

typedef struct MS_CAM20_SHARPNESS2_ATTR_S
{
    MS_CAM20_SHARPNESS2_LOCAL_ATTR_S nEdgeCtrl;
    MS_CAM20_SHARPNESS2_LOCAL_ATTR_S nTextureCtrl;
    MS_U8 u8EdgeKillLUT[6];     //0 ~ 255,  def: 0
    MS_U8 u8CornerReduce;       //0 ~ 32,   def: 32
    MS_CAM_BOOL bDirEn;         //0 ~ 1,    def: 1
    MS_U16 u16SharpnessUD;      //0 ~ 1023
    MS_U16 u16SharpnessD;       //0 ~ 1023
} MS_CAM20_SHARPNESS2_ATTR_S;

typedef struct
{
    MS_CAM20_SHARPNESS2_ATTR_S paraAPI;
} SHARPNESS2_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_SHARPNESS2_ATTR_S paraAPI[CAM20_AUTO_NUM];
} SHARPNESS2_AUTO_ATTR_S;

typedef struct MS_CAM20_SHARPNESS2_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    SHARPNESS2_AUTO_ATTR_S stAuto;
    SHARPNESS2_MANUAL_ATTR_S stManual;
} MS_CAM20_SHARPNESS2_TYPE;

typedef struct MS_CAM20_WDR_ATTR_S
{
    MS_U8 nDarkGainLmtY;    //0 ~ 255
    MS_U8 nDarkGainLmtC;    //0 ~ 255
    MS_U8 nBrightGainLmtY;  //0 ~ 255
    MS_U8 nBrightGainLmtC;  //0 ~ 255
    MS_U8 nGlobalGainLmtY;  //0 ~ 255
    MS_U16 u16Strength;     //0 ~ 256
} MS_CAM20_WDR_ATTR_S;

typedef struct
{
    MS_CAM20_WDR_ATTR_S paraAPI;
} WDR_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_WDR_ATTR_S paraAPI[CAM20_AUTO_NUM];
} WDR_AUTO_ATTR_S;

typedef struct MS_CAM20_WDR_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    WDR_AUTO_ATTR_S stAuto;
    WDR_MANUAL_ATTR_S stManual;
} MS_CAM20_WDR_TYPE;

typedef struct MS_CAM20_WDR_GBL_ATTR_S
{
    MS_U32 u32StrNum;
    MS_S32 s32BVLut[CAM20_AUTO_NUM];
    MS_S32 s32StrLut[CAM20_AUTO_NUM];
    MS_U32 u32DarkIncLut[21];
} MS_CAM20_WDR_GBL_ATTR_S;

typedef struct
{
    MS_CAM20_WDR_GBL_ATTR_S paraAPI;
} WDR_GBL_AUTO_ATTR_S;

typedef struct
{
    MS_S32 s32BV;
    MS_U32 u32DarkIncLut[21];
} WDR_GBL_MANUAL_ATTR_S;

typedef struct MS_CAM20_WDR_GBL_TYPE
{
    MS_CAM_BOOL bEnable;            //0~1
    MS_CAM20_OP_TYPE_E enOpType;            //M_AUTO~(M_MODMAX-1)
    WDR_GBL_AUTO_ATTR_S stAuto;
    WDR_GBL_MANUAL_ATTR_S stManual;
} MS_CAM20_WDR_GBL_TYPE;

typedef struct MS_CAM20_SATURATION_ATTR_S
{
    MS_U8 nSatAllStr;           //0 ~ 127 (32 = 1X)
    MS_U8 nSatByYSFTAdv[5];     //0 ~ 8
    MS_U8 nSatByYLUTAdv[6];     //0 ~ 128
    MS_U8 nSatBySSFTAdv[5];     //0 ~ 8
    MS_U8 nSatBySLUTAdv[6];     //0 ~ 128
} MS_CAM20_SATURATION_ATTR_S;

typedef struct
{
    MS_CAM20_SATURATION_ATTR_S paraAPI;
} SATURATION_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_SATURATION_ATTR_S paraAPI[CAM20_AUTO_NUM];
} SATURATION_AUTO_ATTR_S;

typedef struct MS_CAM20_SATURATIONTYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    SATURATION_AUTO_ATTR_S stAuto;
    SATURATION_MANUAL_ATTR_S stManual;
} MS_CAM20_SATURATIONTYPE;

typedef struct MS_CAM20_EFFECT_ATTR_S
{
    MS_CAM_BOOL bEn;
    MS_U8 u8Level;
} MS_CAM20_EFFECT_ATTR_S;

typedef struct
{
    MS_CAM20_EFFECT_ATTR_S paraColorToGrey; //0 ~ 100
    MS_CAM20_EFFECT_ATTR_S paraSepia;       //0 ~ 100
    MS_CAM20_EFFECT_ATTR_S paraNegative;    //0 ~ 100
    MS_CAM20_EFFECT_ATTR_S paraSatOffset;   //0 ~ 100
    MS_CAM20_EFFECT_ATTR_S paraSatVivid;    //0 ~ 100
    MS_CAM20_EFFECT_ATTR_S paraSatPale;     //0 ~ 100
    MS_CAM20_EFFECT_ATTR_S paraSharpOffset; //0 ~ 100
    MS_CAM20_EFFECT_ATTR_S paraBrightness;      //0~100
    MS_CAM20_EFFECT_ATTR_S paraLightness;       //0~100
    MS_CAM20_EFFECT_ATTR_S paraContrast;        //0~100
} EFFECT_MANUAL_ATTR_S;

typedef struct MS_CAM20_EFFECT
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM_BOOL bResetFlag;         //0 ~ 1
    EFFECT_MANUAL_ATTR_S stManual;
} MS_CAM20_EFFECT;

typedef struct
{
    MS_CAM20_LEV_ATTR_S paraAPI;
} LIGHTNESS_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_LEV_ATTR_S paraAPI[CAM20_AUTO_NUM];
} LIGHTNESS_AUTO_ATTR_S;

typedef struct MS_CAM20_LIGHTNESSTYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    LIGHTNESS_AUTO_ATTR_S stAuto;
    LIGHTNESS_MANUAL_ATTR_S stManual;
} MS_CAM20_LIGHTNESSTYPE;

typedef struct MS_CAM20_DEFOG_ATTR_S
{
    MS_U16 u16ManualLevel;
    MS_U16 u16AutoLevel;
} MS_CAM20_DEFOG_ATTR_S;

typedef struct
{
    MS_CAM20_DEFOG_ATTR_S paraAPI;
} DEFOG_MANUAL_ATTR_S;

typedef enum
{
    MS_Hist = 0,
    MS_Manual = 1,
    MS_DEFOG_MAX = 0x7FFFFFFF
} MS_DEFOG_MODE;

typedef struct MS_CAM20_DEFOGTYPE
{
    MS_CAM_BOOL bEnable;
    MS_DEFOG_MODE  enOpType;
    DEFOG_MANUAL_ATTR_S stManual;
} MS_CAM20_DEFOGTYPE;

typedef struct MS_CAM20_DRC_ATTR_S
{
    MS_U32 u32WhiteLevel;
    MS_U32 u32BlackLevel;
    MS_U32 u32Asymmetry;
    MS_U32 u32BrigntEnhance;
    MS_U32 u32ManualLevel;
    MS_U32 u32AutoLevel;
} MS_CAM20_DRC_ATTR_S;

typedef struct
{
    MS_CAM20_DRC_ATTR_S paraAPI;
} DRC_MANUAL_ATTR_S;

typedef struct MS_CAM20_DRCTYPE
{
    MS_CAM_BOOL bEnable;
    MS_CAM20_OP_TYPE_E enOpType;
    DRC_MANUAL_ATTR_S stManual;
} MS_CAM20_DRCTYPE;

typedef struct MS_CAM20_YUVHISTOTYPE
{
    MS_U16 u16YUVHistogram[256];
} MS_CAM20_YUVHISTOTYPE;

typedef struct MS_CAM20_NR3D_ATTR_S
{
    MS_U8 nY_SF_STR;                //0 ~ 255(NLM??)
    MS_U8 nY_SF_ADAP_STR;           //0 ~ 255
    MS_U8 nY_TF_STR_Adv;            //0 ~ 255
    MS_U8 nY_TF_LUT_Adv[16];        //0 ~ 63
    MS_U8 nY_TF_STR_BY_LY_Adv[8];   //0 ~ 63
    MS_U8 nY_BLEND_LUT_Adv[16];     //0 ~ 31
    MS_U16 nY_PK_LUT_Adv[16];       //0 ~ 1023
    MS_U8 nC_SF_STR;                //0 ~ 255
    MS_U8 nC_TF_STR_Adv;            //0 ~ 255
    MS_U8 nC_TF_LUT_Adv[16];        //0 ~ 63
    MS_U8 nC_TF_STR_BY_LY_Adv[8];   //0 ~ 63
} MS_CAM20_NR3D_ATTR_S;

typedef struct
{
    MS_CAM20_NR3D_ATTR_S paraAPI;
} NR3D_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_NR3D_ATTR_S paraAPI[CAM20_AUTO_NUM];
} NR3D_AUTO_ATTR_S;

typedef struct MS_CAM20_NR3D_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    NR3D_AUTO_ATTR_S stAuto;
    NR3D_MANUAL_ATTR_S stManual;
} MS_CAM20_NR3D_TYPE;

typedef struct MS_CAM20_NRBayer_ATTR_S
{
    MS_U16 u16ThresholdR;   //0 ~ 255
    MS_U16 u16ThresholdG;   //0 ~ 255
    MS_U16 u16ThresholdB;   //0 ~ 255
    MS_U8 u8NRStrengthR;    //0 ~ 15
    MS_U8 u8NRStrengthG;    //0 ~ 15
    MS_U8 u8NRStrengthB;    //0 ~ 15
    MS_U8 u8NRSlopeR;       //0 ~ 7
    MS_U8 u8NRSlopeG;       //0 ~ 7
    MS_U8 u8NRSlopeB;       //0 ~ 7
} MS_CAM20_NRBayer_ATTR_S;

typedef struct
{
    MS_CAM20_NRBayer_ATTR_S paraAPI;
} NRBayer_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_NRBayer_ATTR_S paraAPI[CAM20_AUTO_NUM];
} NRBayer_AUTO_ATTR_S;

typedef struct MS_CAM20_NRBayer_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    NRBayer_AUTO_ATTR_S stAuto;
    NRBayer_MANUAL_ATTR_S stManual;
} MS_CAM20_NRBayer_TYPE;

typedef struct MS_CAM20_NRDeSpike_ATTR_S
{
    MS_U8  u8BlendRatio;                //0 ~ 15
    MS_U8  u8StrengthCenterNeighbor;    //0 ~ 5
    MS_U8  u8StrengthMeanStd;           //0 ~ 5
    MS_U8  u8StrengthCornerCross;       //0 ~ 5
    MS_U8  u8DiffGainMeanStd;           //0 ~ 31
    MS_U16 u16DiffGainCenterNeighbor;   //0 ~ 255
    MS_U16 u16DiffThdCornerCross;       //0 ~ 255
} MS_CAM20_NRDeSpike_ATTR_S;

typedef struct
{
    MS_CAM20_NRDeSpike_ATTR_S paraAPI;
} NRDeSpike_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_NRDeSpike_ATTR_S paraAPI[CAM20_AUTO_NUM];
} NRDeSpike_AUTO_ATTR_S;

typedef struct MS_CAM20_NRDeSpike_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    NRDeSpike_AUTO_ATTR_S stAuto;
    NRDeSpike_MANUAL_ATTR_S stManual;
} MS_CAM20_NRDeSpike_TYPE;

typedef struct MS_CAM20_NRLuma_ATTR_S
{
    MS_U8 u8BlendRatio;             //0 ~ 63
    MS_U8 u8FilterLevel;            //0 ~ 5
    MS_U8 u8StrengthByY[16];        //0 ~ 63
    MS_CAM_BOOL bEnLscReference;    //0 ~ 1
} MS_CAM20_NRLuma_ATTR_S;

typedef struct
{
    MS_CAM20_NRLuma_ATTR_S paraAPI;
} NRLuma_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_NRLuma_ATTR_S paraAPI[CAM20_AUTO_NUM];
} NRLuma_AUTO_ATTR_S;

typedef struct MS_CAM20_NRLuma_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    NRLuma_AUTO_ATTR_S stAuto;
    NRLuma_MANUAL_ATTR_S stManual;
} MS_CAM20_NRLuma_TYPE;

typedef struct MS_CAM_RECTTYPE
{
    MS_S32 nLeft;
    MS_S32 nTop;
    MS_U32 nWidth;
    MS_U32 nHeight;
} MS_CAM_RECTTYPE;

typedef struct MS_CAM_DITHERTYPE
{
    //MS_DITHERTYPE eDither;
    MS_U32 eDither;
} MS_CAM_DITHERTYPE;

typedef struct MS_CAM20_SHARPNESS_LOCAL_ATTR_S
{
    MS_U16  u16ShootGain;       //0 ~ 55
    MS_U8   u16ShootGainLevel;  //0 ~ 3
    MS_U16  u8OverShootLimit;   //0 ~ 255
    MS_U16  u8UnderShootLimit;  //0 ~ 255
    MS_U8   u8NoiseThd;         //0 ~ 15
} MS_CAM20_SHARPNESS_LOCAL_ATTR_S;

typedef struct MS_CAM20_SHARPNESS_ATTR_S
{
    MS_CAM20_SHARPNESS_LOCAL_ATTR_S nEdgeCtrl;
    MS_CAM20_SHARPNESS_LOCAL_ATTR_S nTextureCtrl;
    MS_U16 u16ShootGain;        //0 ~ 63
    MS_U8 u8NoiseThd;           //0 ~ 15
    MS_U8 u8NoiseThdLevel;      //0 ~ 3
    MS_U8 u8ShootGainLut[16];   //0 ~ 63
    MS_CAM_BOOL bEnLuma;        //0 ~ 1
    MS_U16 u16LumaBypassThd;    //0 ~ 255
    MS_U8 u8LumaGain;           //0 ~ 3
    MS_U8 u8LumaGainLut[8];     //0 ~ 63
} MS_CAM20_SHARPNESS_ATTR_S;

typedef struct
{
    MS_CAM20_SHARPNESS_ATTR_S paraAPI;
} SHARPNESS_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_SHARPNESS_ATTR_S paraAPI[CAM20_AUTO_NUM];
} SHARPNESS_AUTO_ATTR_S;

typedef struct MS_CAM20_SHARPNESS_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    SHARPNESS_AUTO_ATTR_S stAuto;
    SHARPNESS_MANUAL_ATTR_S stManual;
} MS_CAM20_SHARPNESS_TYPE;
typedef struct MS_CAM_COLOR_TONE_TYPE
{
    MS_S32 clorTonLevel[3];
} MS_CAM_COLOR_TONE_TYPE;

typedef struct MS_CAM20_RGBMARIX_ATTR_S
{
    MS_U16 u16CCTthr;
    MS_U16 au16CCM[9];
    MS_U8  u8CCMSat;    //0 ~ 100 0:Unit matrix, 100:User matrix
} MS_CAM20_RGBMARIX_ATTR_S;

typedef struct RGBMARIX_MANUAL_ATTR_S
{
    MS_U16 au16CCM[9];  //0 ~ 8191(1024 = 1X)
    MS_U8  u8CCMSat;    //0 ~ 100 0:Unit matrix, 100:User matrix
} RGBMARIX_MANUAL_ATTR_S;

typedef struct RGBMARIX_AUTO_ATTR_S
{
    MS_CAM_BOOL bISOActEn;          //0 ~ 1
    MS_CAM20_RGBMARIX_ATTR_S paraAPI[CAM20_AUTO_NUM];
} RGBMARIX_AUTO_ATTR_S;

typedef struct MS_CAM20_RGBMARIX_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    RGBMARIX_AUTO_ATTR_S stAuto;
    RGBMARIX_MANUAL_ATTR_S stManual;
} MS_CAM20_RGBMARIX_TYPE;

typedef struct MS_CAM20_FALSECOLOR_ATTR_S
{
    MS_U8 u8Strength;               //u8Strength:0 ~ 7
} MS_CAM20_FALSECOLOR_ATTR_S;

typedef struct
{
    MS_CAM20_FALSECOLOR_ATTR_S paraAPI;
} FALSECOLOR_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_FALSECOLOR_ATTR_S paraAPI[CAM20_AUTO_NUM];
} FALSECOLOR_AUTO_ATTR_S;

typedef struct MS_CAM20_FALSECOLOR_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //OP_TYP_AUTO ~ (OP_TPY_MODMAX-1)
    FALSECOLOR_AUTO_ATTR_S stAuto;
    FALSECOLOR_MANUAL_ATTR_S stManual;
} MS_CAM20_FALSECOLOR_TYPE;

typedef struct MS_CAM20_FALSECOLOR2_ATTR_S
{
    MS_U8 u8Strength;               //u8Strength:0 ~ 255
} MS_CAM20_FALSECOLOR2_ATTR_S;

typedef struct
{
    MS_CAM20_FALSECOLOR2_ATTR_S paraAPI;
} FALSECOLOR2_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_FALSECOLOR2_ATTR_S paraAPI[CAM20_AUTO_NUM];
} FALSECOLOR2_AUTO_ATTR_S;

typedef struct MS_CAM20_FALSECOLOR2_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //OP_TYP_AUTO ~ (OP_TPY_MODMAX-1)
    FALSECOLOR2_AUTO_ATTR_S stAuto;
    FALSECOLOR2_MANUAL_ATTR_S stManual;
} MS_CAM20_FALSECOLOR2_TYPE;

typedef struct MS_CAM20_CROSSTALK_ATTR_S
{
    MS_U8  u8StrengthLow;       //0 ~ 7
    MS_U16 u16ThresholdLow;     //0 ~ 255
    MS_U8  u8StrengthHigh;      //0 ~ 7
    MS_U16 u16ThresholdHigh;    //0 ~ 255
    MS_U8  u8StrengthV2;        //0 ~ 31
    MS_U16 u16ThresholdV2;      //0 ~ 255
} MS_CAM20_CROSSTALK_ATTR_S;

typedef struct
{
    MS_CAM20_CROSSTALK_ATTR_S paraAPI;
} CROSSTALK_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_CROSSTALK_ATTR_S paraAPI[CAM20_AUTO_NUM];
} CROSSTALK_AUTO_ATTR_S;

typedef struct MS_CAM20_CROSSTALK_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    MS_CAM_BOOL enV2;               //0 ~ 1
    CROSSTALK_AUTO_ATTR_S stAuto;
    CROSSTALK_MANUAL_ATTR_S stManual;
} MS_CAM20_CROSSTALK_TYPE;

typedef struct MS_CAM20_DYNAMIC_DP_ATTR_S
{
    MS_CAM_BOOL u8HotPixEn;         //0 ~ 1
    MS_U16 u16HotPixCompSlpoe;
    MS_CAM_BOOL u8DarkPixEn;        //0 ~ 1
    MS_U16 u16DakrPixCompSlpoe;
    MS_U16 u16DPCTH;
} MS_CAM20_DYNAMIC_DP_ATTR_S;

typedef struct
{
    MS_CAM20_DYNAMIC_DP_ATTR_S paraAPI;
} DYNAMIC_DP_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_DYNAMIC_DP_ATTR_S paraAPI[CAM20_AUTO_NUM];
} DYNAMIC_DP_AUTO_ATTR_S;

typedef struct MS_CAM20_DYNAMIC_DP_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    DYNAMIC_DP_AUTO_ATTR_S stAuto;
    DYNAMIC_DP_MANUAL_ATTR_S stManual;
} MS_CAM20_DYNAMIC_DP_TYPE;

typedef struct MS_CAM20_OBC_ATTR_S
{
    MS_U16 u16ValR;            //0 ~ 255
    MS_U16 u16ValGr;           //0 ~ 255
    MS_U16 u16ValGb;           //0 ~ 255
    MS_U16 u16ValB;            //0 ~ 255
} MS_CAM20_OBC_ATTR_S;

typedef struct
{
    MS_CAM20_OBC_ATTR_S paraAPI;
} OBC_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_OBC_ATTR_S paraAPI[CAM20_AUTO_NUM];
} OBC_AUTO_ATTR_S;

typedef struct MS_CAM20_OBC_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    OBC_AUTO_ATTR_S stAuto;
    OBC_MANUAL_ATTR_S stManual;
} MS_CAM20_OBC_TYPE;

typedef struct MS_CAM_OBC4Ch_TYPE
{
    MS_U16 nOBC4Ch[4];
} MS_CAM_OBC4Ch_TYPE;

typedef enum
{
    MS_CAM_CSA_MOD_BLUE = 0,
    MS_CAM_CSA_MOD_GREEN,
    MS_CAM_CSA_MOD_BG,
    MS_CAM_CSA_MOD_SKIN,
    MS_CAM_CSA_MOD_VIVID,
    //IQ_OMX_CSA_MODE_BUTT
    MS_CAM_CSA_MODEMAX
} MS_CAM_CSA_Mode;

typedef enum
{
    MS_CAM20_CSA_MOD_BLUE = 0,
    MS_CAM20_CSA_MOD_GREEN,
    MS_CAM20_CSA_MOD_BG,
    MS_CAM20_CSA_MOD_SKIN,
    MS_CAM20_CSA_MOD_VIVID,     //all ind
    MS_CAM20_CSA_MOD_MANUAL,    //selected ind
    MS_CAM20_CSA_MODEMAX
} MS_CAM20_CSA_Mode;

typedef struct MS_CAM20_CSA_ATTR_S
{
    MS_CAM20_CSA_Mode CSAmode;  //CSA_MOD_BLUE ~ (CSA_MOD_MAX-1)
    MS_U32 u32GainLuma;         //0 ~ 63  (32 = OFF)
    MS_U32 u32GainHue;          //0 ~ 127 (64 = OFF)
    MS_U32 u32GainSat;          //0 ~ 31  (16 = OFF)
    MS_U32 u32LumaLut[16];      //work under MS_CAM_CSA_MOD_MANUAL Mode //0 ~  63 (32 = OFF)
    MS_U32 u32HueLut[16];       //work under MS_CAM_CSA_MOD_MANUAL Mode //0 ~ 127 (64 = OFF)
    MS_U32 u32SatLut[16];       //work under MS_CAM_CSA_MOD_MANUAL Mode //0 ~  31 (16 = OFF)
} MS_CAM20_CSA_ATTR_S;

typedef struct
{
    MS_CAM20_CSA_ATTR_S paraAPI;
} CSA_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_CSA_ATTR_S paraAPI[CAM20_AUTO_NUM];
} CSA_AUTO_ATTR_S;

typedef struct MS_CAM20_CSA_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    CSA_AUTO_ATTR_S stAuto;
    CSA_MANUAL_ATTR_S stManual;
} MS_CAM20_CSA_TYPE;

typedef struct MS_CAM20_HSV_ATTR_S
{
    MS_S16 HueLut[24];              //-64 ~  64
    MS_U16 SatLut[24];              //  0 ~ 255 (64->1X)
    MS_S16 HueLut_ForUnitCCM[24];   //-64 ~  64
    MS_U16 SatLut_ForUnitCCM[24];   //  0 ~ 255 (64->1X)
    MS_U8  GlobalSat;               //  0 ~ 255 (64->1x)
} MS_CAM20_HSV_ATTR_S;

typedef struct
{
    MS_CAM20_HSV_ATTR_S paraAPI;
} HSV_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_HSV_ATTR_S paraAPI[CAM20_AUTO_NUM];
} HSV_AUTO_ATTR_S;

typedef struct MS_CAM20_HSV_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    HSV_AUTO_ATTR_S stAuto;
    HSV_MANUAL_ATTR_S stManual;
} MS_CAM20_HSV_TYPE;

typedef struct MS_CAM20_RGBIR_ATTR_S
{
    MS_U8 u8IrPosType;          //0 ~ 7, def : 0
    MS_CAM_BOOL bRemovelEn;     //0 ~ 1, def : 1
    MS_U16 Ratio_R[6];
    MS_U16 Ratio_G[6];
    MS_U16 Ratio_B[6];
} MS_CAM20_RGBIR_ATTR_S;

typedef struct
{
    MS_CAM20_RGBIR_ATTR_S paraAPI;
} RGBIR_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_RGBIR_ATTR_S paraAPI[CAM20_AUTO_NUM];
} RGBIR_AUTO_ATTR_S;

typedef struct MS_CAM20_RGBIR_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    RGBIR_AUTO_ATTR_S stAuto;
    RGBIR_MANUAL_ATTR_S stManual;
} MS_CAM20_RGBIR_TYPE;

typedef struct MS_CAM20_FPN_ATTR_S
{
    MS_U16 Start_X;         //0 ~ 4095
    MS_U16 Start_Y;         //0 ~ 4095
    MS_U16 Width;           //0 ~ 4095
    MS_U8  Height;          //1 ~ 31
    MS_U16 Pre_Offset;      //0 ~ 32767
    MS_U8  Pre_Offset_Sign; //0 ~ 1
    MS_U16 Diff_TH;         //0 ~ 65535
    MS_U16 Cmp_Ratio;       //0 ~ 4095
    MS_U8  Frame_Num;       //1 ~ 31
    MS_U8  SW_Offset_En;    //0 ~ 1
    MS_U16 SW_Cmp_Ratio;    //0 ~ 4095
} MS_CAM20_FPN_ATTR_S;

typedef struct
{
    MS_CAM20_FPN_ATTR_S paraAPI;
} FPN_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_FPN_ATTR_S paraAPI[CAM20_AUTO_NUM];
} FPN_AUTO_ATTR_S;

typedef struct MS_CAM20_FPN_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    FPN_AUTO_ATTR_S stAuto;
    FPN_MANUAL_ATTR_S stManual;
} MS_CAM20_FPN_TYPE;

typedef struct MS_CAM20_HDR16to12_ATTR_S
{
    MS_U16 R_OFST;  //0 ~ 65535
    MS_U16 G_OFST;  //0 ~ 65535
    MS_U16 B_OFST;  //0 ~ 65535
    MS_U16 CURVE_LUT[21];
} MS_CAM20_HDR16to12_ATTR_S;

typedef struct
{
    MS_CAM20_HDR16to12_ATTR_S paraAPI;
} HDR16to12_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_HDR16to12_ATTR_S paraAPI[CAM20_AUTO_NUM];
} HDR16to12_AUTO_ATTR_S;

typedef struct MS_CAM20_HDR16to12_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //M_AUTO ~ (M_MODMAX-1)
    HDR16to12_AUTO_ATTR_S stAuto;
    HDR16to12_MANUAL_ATTR_S stManual;
} MS_CAM20_HDR16to12_TYPE;

typedef struct MS_CAM20_COLORTRANS_ATTR_S
{
    MS_U16 Y_OFST;      //0 ~ 2047
    MS_U16 U_OFST;      //0 ~ 2047
    MS_U16 V_OFST;      //0 ~ 2047
    MS_U16 Matrix[9];   //0 ~ 1023
} MS_CAM20_COLORTRANS_ATTR_S;

typedef struct
{
    MS_CAM20_COLORTRANS_ATTR_S paraAPI;
} COLORTRANS_MANUAL_ATTR_S;

typedef struct MS_CAM20_COLORTRANS_TYPE
{
    MS_CAM_BOOL bEnable;    //0 ~ 1
    COLORTRANS_MANUAL_ATTR_S stManual;
} MS_CAM20_COLORTRANS_TYPE;

typedef struct MS_CAM20_HDR_ATTR_S
{
    MS_U16 RATIO_VS; // 0~65535
    MS_U16 TH1; // 0~1023
    MS_U16 TH2; // 0~1023
    MS_U8  UVTBL_X[8];
    MS_U16 UVTBL_Y[9];
    MS_U32 VS_NR_EN;
    MS_U16 EDGE_TH1;
    MS_U16 EDGE_TH2;
    MS_U32 DYN_RATIO_EN;
    MS_U8  GAMA_X[22];
    MS_U16 GAMA_Y[23];
} MS_CAM20_HDR_ATTR_S;

typedef struct
{
    MS_CAM20_HDR_ATTR_S paraAPI;
} HDR_MANUAL_ATTR_S;

typedef struct
{
    MS_CAM20_HDR_ATTR_S paraAPI[CAM20_AUTO_NUM];
} HDR_AUTO_ATTR_S;

typedef struct MS_CAM20_HDR_TYPE
{
    MS_CAM_BOOL bEnable;            //0 ~ 1
    MS_CAM20_OP_TYPE_E enOpType;    //OP_TYP_AUTO ~ (OP_TPY_MODMAX-1)
    HDR_AUTO_ATTR_S stAuto;
    HDR_MANUAL_ATTR_S stManual;
} MS_CAM20_HDR_TYPE;

typedef struct MS_CAM_CALI_LSC_TYPE
{
    MS_U8  tid;
    MS_U32 target;
    MS_U8  ratioTbl[32];
    MS_U16 ob;
} MS_CAM_CALI_LSC_TYPE;

typedef struct MS_CAM_CALI_MIN_GAIN_TYPE
{
    MS_U32 in_init_shutter;
    MS_U16 in_gain_base;
    MS_U8 in_gain_interval;
    MS_U16 out_min_gain;
} MS_CAM_CALI_MIN_GAIN_TYPE;

typedef struct MS_CAM_CALI_SHUTTER_LINEARITY_TYPE
{
    MS_U32 in_shutter_step[16];
    MS_U32 out_linearity_info[1280];
} MS_CAM_CALI_SHUTTER_LINEARITY_TYPE;

typedef struct MS_CAM_CALI_GAIN_LINEARITY_TYPE
{
    MS_U32 in_init_shutter;
    MS_U32 in_gain_step[16];
    MS_U16 in_linearity_thd;
    MS_U16 in_max_y;
    MS_U32 out_linearity_info[1280];
    MS_U16 out_gain_skip[32];
} MS_CAM_CALI_GAIN_LINEARITY_TYPE;

typedef struct MS_CAM_CALI_ISO100_TYPE
{
    MS_U16 in_shutter;
    MS_U16 in_iso;
    MS_U16 in_lv;
    MS_U16 in_luma;
    MS_U16 in_luma_thd;
    MS_S32 out_avoffset;
    MS_S32 out_bvoffset;
    MS_U32 out_iso100gain;
    MS_U32 out_miniso;
} MS_CAM_CALI_ISO100_TYPE;

typedef struct MS_CAM_CALI_OBC_TYPE
{
    MS_U16 in_target;
    MS_U16 in_wei[9];
    MS_U16 out_a;
    MS_U16 out_b;
} MS_CAM_CALI_OBC_TYPE;

typedef struct MS_CAM_LSC_TYPE
{
    MS_U32 enable;
    MS_U16 table_r[4210];
    MS_U16 table_g[4210];
    MS_U16 table_b[4210];
} MS_CAM_LSC_TYPE;

typedef struct
{
    unsigned short u2NumOfPoints;
    int i4Y[16];
    int i4X[16];
} MS_INTP_LUT;

typedef enum
{
    MS_IQ_PAMOD_NORMAL = 0,
    MS_IQ_PAMOD_NIGHT = 1,      //Night Mode
    MS_IQ_PAMOD_MAX,
} MS_CAM_IQ_PARA_MODE;

typedef enum
{
    MS_IQ_APIMOD_10 = 0,        //API1.0
    MS_IQ_APIMOD_20 = 1,        //API2.0
    MS_IQ_APIMOD_MAX,
} MS_CAM_IQ_API_MODE;

typedef enum __attribute__ ((aligned (4)))
{
    MS_API20_AUTO = 0,   //[00]
    //API2.0
    MS_API20_FPN,        //[01]
    MS_API20_NR_BAYER,   //[02]
    MS_API20_CCM,        //[03]
    MS_API20_SAT,        //[04]
    MS_API20_OBC,        //[05]
    MS_API20_FCOLOR,     //[06]
    MS_API20_FCOLOR2,    //[07]
    MS_API20_CR,         //[08]
    MS_API20_NR_DeSpike, //[09]
    MS_API20_SHP,        //[10] TwoDPK
    MS_API20_SHP2,       //[11] YEE, ALUT
    MS_API20_NR_3D,      //[12]
    MS_API20_BRI,        //[13]
    MS_API20_LIG,        //[14]
    MS_API20_CST,        //[15]
    MS_API20_GMA,        //[16]
    MS_API20_CTG,        //[17]
    MS_API20_CSA,        //[18]
    MS_API20_NR_NLM,     //[19]
    MS_API20_DEFOG,      //[20]
    MS_API20_DRC,        //[21]
    MS_API20_DPC,        //[22]
    MS_API20_HSV,        //[23]
    MS_API20_WDR_LOC,    //[24]
    MS_API20_RGBIR,      //[25]
    MS_API20_YUVGMA,     //[26]
    MS_API20_HDR16to12,  //[27]
    MS_API20_COLORTRANS, //[28]
    MS_API20_HDR,        //[29]
    MS_API20_EFFECT,     //[30]
    MS_API20_MAX,        //for para reset
} MS_CAM20_API_ID;

typedef enum __attribute__ ((aligned (4)))
{
    MS_Bypass_OFF = 0,
    MS_Bypass_ON
} MS_CAM20_BypassMode;

typedef enum
{
    MS_MeteringModeAverage,                     // Center-weighted average metering.
    MS_MeteringModeSpot,                        // Spot (partial) metering.
    MS_MeteringModeMatrix,                      // Matrix or evaluative metering.
    MS_MeteringKhronosExtensions = 0x6F000000,  /**< Reserved region for introducing Khronos Standard Extensions */
    MS_MeteringVendorStartUnused = 0x7F000000,  /**< Reserved region for introducing Vendor Extensions */
    MS_EVModeMax = 0x7fffffff
} MS_METERINGTYPE;

typedef enum
{
    MS_AE_MODE_A,   // auto
    MS_AE_MODE_AV,  // aperture priority
    MS_AE_MODE_SV,
    MS_AE_MODE_TV,  // shutter priority
    MS_AE_MODE_M    // manual mode
} MS_AEMODETYPE;

typedef struct MS_CONVSPEEDTYPE
{
    MS_U32 nSpeedX[4];
    MS_U32 nSpeedY[4];
} MS_CONVSPEEDTYPE;

typedef struct MS_CONVTHDTYPE
{
    MS_U32 nInThd;
    MS_U32 nOutThd;
} MS_CONVTHDTYPE;

typedef struct MS_AE_CONV_CONDITON
{
    MS_CONVTHDTYPE ConvThrd;
    MS_CONVSPEEDTYPE ConvSpeed;
} MS_AE_CONV_CONDITON;

typedef struct
{
    MS_U32 u4FNumx10;
    MS_U32 u4USec;
    MS_U32 u4TotalGain;
    MS_U32 u4SensorGain;
} MS_AE_EXPO_POINT;

typedef struct
{
    MS_U32 u4NumPoints;
    MS_AE_EXPO_POINT ExpoTbl[16];   // LV from High to Low
} MS_AE_EXPO_TBLTYPE;

typedef struct
{
    MS_INTP_LUT AeHdrRatio;
} MS_CAM_AE_HDR_TYPE;

typedef struct
{
    MS_U32 u4MinShutterUS;
    MS_U32 u4MaxShutterUS;
    MS_U32 u4MinFNx10;
    MS_U32 u4MaxFNx10;
    MS_U32 u4MinSensorGain;
    MS_U32 u4MinISPGain;
    MS_U32 u4MaxSensorGain;
    MS_U32 u4MaxISPGain;
}MS_AE_EXP_LIMIT_TYPE;

typedef struct
{
    MS_U32 nMinShutterUS;
    MS_U32 nMaxShutterUS;
} MS_MIN_MAX_SHUTTERTYPE;


typedef struct
{
    MS_U32 nLumY;
    MS_U32 nAvgY;
    MS_U32 nHits[128];
} MS_CAM_AE_HIST_WGHT_Y;

typedef struct
{
    MS_U32 *u4FNx10;
    MS_U32 *u4SensorGain;
    MS_U32 *u4ISPGain;
    MS_U32 *u4US;
} MS_CAM_GET_CUR_EXP_GAINTYPE;

typedef struct
{
    MS_U32 u4FNx10;
    MS_U32 u4SensorGain;
    MS_U32 u4ISPGain;
    MS_U32 u4US;
} MS_CAM_SET_EXP_GAINTYPE;

typedef enum
{
    MS_AE_AVERAGE = 0,
    MS_AE_CENTER_WGHT,
    MS_AE_SPOT,
    MS_AE_WGT_END
} MS_CAM_AE_WIN_WGT_TYPE;

typedef struct
{
    MS_CAM_AE_WIN_WGT_TYPE eTypeID;
    MS_U32 AverageTbl[32*32];
    MS_U32 CenterTbl[32*32];
    MS_U32 SpotTbl[32*32];
} MS_CAM_AE_WINWGT;

typedef struct MS_CAM_EXPOSUREVALUETYPE
{
    MS_AEMODETYPE nAeMode;
    MS_METERINGTYPE eMetering;
    MS_S32 xEVCompensation;
    MS_U32 nApertureFNumber;
    MS_U32 nShutterSpeedUsec;
    MS_U32 nSensitivity;
} MS_CAM_EXPOSUREVALUETYPE;

typedef struct MS_CAM_SHUTTER
{
    MS_U32 nShutterSpeedUsec;
} MS_CAM_SHUTTER;

typedef int (*MS_CAM_APERTURE_CB)(int, void *);

typedef enum
{
    MS_AE_16x24 = 0,
    MS_AE_32x24,
    MS_AE_64x48,
    MS_AE_64x45,
    MS_AE_128x80,
    MS_AE_128x90
} MS_CAM_AE_WIN_BLOCK_NUM;

typedef struct
{
    MS_U16 u2Stawin_x_offset;
    MS_U16 u2Stawin_x_size;
    MS_U16 u2Stawin_y_offset;
    MS_U16 u2Stawin_y_size;
} MS_CAM_HIST_WIN;

typedef struct MS_CAM_FOCUSREGIONTYPE
{
    MS_CAM_BOOL bCenter;
    MS_CAM_BOOL bLeft;
    MS_CAM_BOOL bRight;
    MS_CAM_BOOL bTop;
    MS_CAM_BOOL bBottom;
    MS_CAM_BOOL bTopLeft;
    MS_CAM_BOOL bTopRight;
    MS_CAM_BOOL bBottomLeft;
    MS_CAM_BOOL bBottomRight;
} MS_CAM_FOCUSREGIONTYPE;

typedef struct MS_CAM_FOCUSSTATUSTYPE
{
    MS_U32 eFocusStatus;
    MS_CAM_BOOL bCenterStatus;
    MS_CAM_BOOL bLeftStatus;
    MS_CAM_BOOL bRightStatus;
    MS_CAM_BOOL bTopStatus;
    MS_CAM_BOOL bBottomStatus;
    MS_CAM_BOOL bTopLeftStatus;
    MS_CAM_BOOL bTopRightStatus;
    MS_CAM_BOOL bBottomLeftStatus;
    MS_CAM_BOOL bBottomRightStatus;
} MS_CAM_FOCUSSTATUSTYPE;

typedef enum
{
    CAMERA_OK = 0,
    CAMERA_ERROR_OPEN_MEMMAP_FAIL,
    CAMERA_ERROR_REQUEST_PHYMEM_FAIL,
    CAMERA_ERROR_FREE_PHYMEM_FAIL,
    CAMERA_ERROR_SENSOR_NOT_FOUND,
    CAMERA_ERROR_NOT_SUPPORT,
    CAMERA_ERROR_NULL_POINTER,
    CAMERA_ERROR_3A_FAIL,
    CAMERA_ERROR_WDMA_TIMEOUT,
    CAMERA_ERROR_NO_SENSORVSYNC,
    CAMERA_ERROR_OUTOF_ARRAY,
    CAMERA_ERROR_BUFFER_TOO_SMALL,
    CAMERA_ERROR_EMPTY_VARIABLE,
    CAMERA_ERROR_CALIB_VERSION_FAIL,
} CAMERA_ERROR_t;

typedef enum
{
    CAMERA_OUTPUT_RAW,
    CAMERA_OUTPUT_YC,
    CAMERA_OUTPUT_STS,  //DEPRECATED
    CAMERA_OUTPUT_VDOS
} CAMERA_OUTPUT_TYPE_t;

//typedef enum
//{
//    CAMERA_CMD_SET,
//    CAMERA_CMD_GET
//} CAMERA_CMD_TYPE;

typedef struct
{
    MS_U32 u4CMDEnum;
    MS_U32 pData[8000];
} CAMERA_CMD_WRAPPER;

typedef struct
{
    unsigned int tag;           //'MSIQ'
    unsigned int fcount;        //the frame number this iq data apply for
    unsigned int header_len;    //this header size
    unsigned int data_len;      //iq data size
} iq_dbg_info_header;

typedef struct
{
    MS_U32 hdr_len;             //header length of camera_param in bytes.
    MS_U32 rot;
} camera_param;

//motion statistics
typedef struct
{
    MS_S32 i4XVector;
    MS_U32 u4XConf;
    MS_S32 i4YVector;
    MS_U32 u4YConf;
    MS_U32 u4SAD;
} ISP_MV_DATA;                  //isp motion data
typedef struct
{
    MS_U8 frame_id;
    ISP_MV_DATA mv[MV_WIN_NUM];
} MS_CAM_MOTION_STAT;

//af statistics
typedef struct
{
    MS_U8 frame_id;
    MS_U32 data;
} MS_CAM_AF_STAT;

typedef struct MS_CAM_ISP_MWB_ATTR
{
    MS_U16 u2Rgain;     //RW, Multiplier for R  color channel, Range: [0, 0x2000]
    MS_U16 u2Grgain;    //RW, Multiplier for Gr color channel, Range: [0, 0x2000]
    MS_U16 u2Gbgain;    //RW, Multiplier for Gb color channel, Range: [0, 0x2000]
    MS_U16 u2Bgain;     //RW, Multiplier for B  color channel, Range: [0, 0x2000]
} MS_CAM_ISP_MWB_ATTR;

typedef enum
{
    MS_CAM_AWB_ALG_DEFAULT = 0,
    MS_CAM_AWB_ALG_ADVANCE = 1
} MS_CAM_AWB_ALG_TYPE;

typedef struct MS_CAM_AWB_CT_LIMIT
{
    MS_U16 u2MaxRgain;  //RW, Maximum  RGain, Range: [0, 8191]
    MS_U16 u2MinRgain;  //RW, Miniimum RGain, Range: [0, 8191]
    MS_U16 u2MaxBgain;  //RW, Maximum  BGain, Range: [0, 8191]
    MS_U16 u2MinBgain;  //RW, Miniimum BGain, Range: [0, 8191]
} MS_CAM_AWB_CT_LIMIT;

typedef struct
{
    MS_U16 pWeight[10]; //RW, Light CT Weight, Range: [1, 255]
} MS_CAM_AWB_CT_WEIGHT;

typedef struct
{
    MS_U16 pRatio[10];  //RW, CT Prefer Ratio, Range: [1, 255]
} MS_CAM_AWB_CT_RATIO;

typedef struct MS_CAM_ISP_AWB_ATTR
{
    MS_U16 u2Speed;                                         //RW, AWB converging speed, Range: [0x1, 0x64]
    MS_U8 uTolerance;                                       //RW, AWB converging threshold, Range:[0, 255], Recommended: [64]
    MS_U16 u2RefColorTemp;                                  //RW, AWB calibration parameter, Color Temperature, Range:[1000, 10000]
    MS_U16 u2RefRgain;                                      //RW, AWB calibration parameter, RGain Value, Range:[256, 4095]
    MS_U16 u2RefBgain;                                      //RW, AWB calibration parameter, BGain Value, Range:[256, 4095]
    MS_U16 u2ZoneSel;                                       //RW, AWB Zone Selection, 0:Global, 1:Color Temperature Area
    MS_CAM_AWB_ALG_TYPE eAlgType;                           //RW, AWB algorithm type
    MS_U8 uRGStrength;                                      //RW, AWB adjust RG ratio, Range:[0, 255]
    MS_U8 uBGStrength;                                      //RW, AWB adjust BG ratio, Range:[0, 255]
    MS_CAM_AWB_CT_LIMIT sCTLimit;                           //RW, AWB limitation when envirnoment ct is out of boundary
    MS_CAM_AWB_CT_WEIGHT u2LvWeight[AWB_LV_CT_TBL_NUM];     //RW, AWB Lv Ct Weight, Range: [0, 255]
    MS_CAM_AWB_CT_RATIO u2PreferRRatio[AWB_LV_CT_TBL_NUM];  //RW, AWB prefer R gain, Range: [0, 255]
    MS_CAM_AWB_CT_RATIO u2PreferBRatio[AWB_LV_CT_TBL_NUM];  //RW, AWB prefer B gain, Range: [0, 255]
    MS_CAM_BOOL bWpWeightEnable;
    MS_U16 u2WpWeight[AWB_CT_TBL_NUM];
} MS_CAM_ISP_AWB_ATTR;

typedef struct MS_CAM_ISP_WB_ATTR_S
{
    MS_CAM_ISP_SM_STATE eState;
    MS_CAM_ISP_OP_MODE eMode;
    MS_CAM_ISP_MWB_ATTR sManual;
    MS_CAM_ISP_AWB_ATTR sAuto;
} MS_CAM_ISP_WB_ATTR_S;

typedef struct MS_CAM_ISP_AWB_MULTILS_ATTR_S
{
    MS_CAM_BOOL bEnable;
    MS_U8 uSensitive;
    MS_U8 uCaliStrength;
    MS_U16 u2CcmForLow[9];
    MS_U16 u2CcmForHigh[9];
} MS_CAM_ISP_AWB_MULTILS_ATTR_S;

typedef struct MS_CAM_AWB_EXTRA_LIGHTSOURCE
{
    MS_U16 u2WhiteRgain;    //RW, RGain of white Point Location , Range: [256, 4095]
    MS_U16 u2WhiteBgain;    //RW, RGain of white Point Location , Range: [256, 4095]
    MS_U8 uAreaSize;        //RW, Light Area Size , Range: [1, 32]
    MS_CAM_BOOL bExclude;   //RW, Include or exclude Uaer light Area, 0: include, 1:exclude
} MS_CAM_AWB_EXTRA_LIGHTSOURCE;

typedef struct MS_CAM_ISP_AWB_ATTR_EX_S
{
    MS_U8 uAreaScale;       //RW, Expand light area , Range: [0, 16], Default: 0
    MS_CAM_BOOL bExtraLightEn;
    MS_CAM_AWB_EXTRA_LIGHTSOURCE sLightInfo[4];
} MS_CAM_ISP_AWB_ATTR_EX_S;

typedef struct MS_CAM_ISP_AWB_INFO_S
{
    MS_U16 u2Rgain;
    MS_U16 u2Grgain;
    MS_U16 u2Gbgain;
    MS_U16 u2Bgain;
    MS_U16 u2ColorTemp;
    MS_U8  uWPInd;
    MS_CAM_BOOL bMultiLSDetected;
    MS_U8  uFirstLSInd;
    MS_U8  uSecondLSInd;
} MS_CAM_ISP_AWB_INFO_S;

typedef struct
{
    MS_U16 u2StartIdx;                //RW, Light area start index, Range: [0, u2EndIdx]
    MS_U16 u2EndIdx;                  //RW, Light area end index, Range: [u2StartIdx, 9]
    MS_U16 u2CtParams[40];            //RW, Color temperature of calibration paramters , Range: [1, 1000]
} MS_CAM_AWB_CT_CALI_ATTR;

typedef struct
{
    MS_U16 u2Width;                   //RW, Effective range
    MS_U16 u2Height;                  //RW, Effective range
    MS_U16 pStatisX[5760];            //RW, Color Temperature Curve Domain Statistics X, max is 64x90
    MS_U16 pStatisY[5760];            //RW, Color Temperature Curve Domain Statistics Y, max is 64x90
} MS_CAM_AWB_CT_STATISTICS;


typedef enum
{
    MS_AE_STGY_BRIGHTTONE,
    MS_AE_STGY_DARKTONE,
    MS_AE_STGY_AUTO
} MS_AE_STRATEGY_E;

typedef struct
{
    MS_AE_STRATEGY_E eAEStrategyMode;
    MS_U32      u4Weighting;
    MS_INTP_LUT u4UpperOffset;
    MS_INTP_LUT u4LowerOffset;
    MS_U32      u4BrightToneStrength;
    MS_U32      u4BrightToneSensitivity;
    MS_U32      u4DarkToneStrength;
    MS_U32      u4DarkToneSensitivity;
    MS_U32      u4AutoStrength;
    MS_U32      u4AutoSensitivity;
} MS_AE_STRATEGY_S;

typedef struct MS_ISP_EXP_INFO_S
{
    MS_CAM_BOOL bIsStable;
    MS_CAM_BOOL bIsReachBoundary;
    MS_CAM_SET_EXP_GAINTYPE sExpValue;
    MS_CAM_SET_EXP_GAINTYPE sExpValueShort;
    MS_CAM_AE_HIST_WGHT_Y sHist_Wght_Y;
    MS_U32 u4LVx10;
    MS_S32 u4BV_Value;
    MS_U32 u4SceneTarget;
} MS_ISP_EXP_INFO_S;

////////// calibration control ////////////////////
typedef enum
{
    eAE_CALI_BV,
    eAE_CALI_AV
} AE_CALI_CTRL_ITEM;

typedef enum
{
    eAE_CALI_OK,
    eAE_CALI_NG
} AE_CALI_ERROR;

typedef struct
{
    AE_CALI_ERROR eRet;
    AE_CALI_CTRL_ITEM eItem;
    MS_U32 u4LVx10;             //  0 ~ 200
    MS_U32 u4FNumx10;           // 10 ~ 200
    MS_U32 u4AvIdx;             //  0 ~  15
} AE_CALI_CTRL;

typedef enum
{
    geALSC_CALI_OK,
    geALSC_CALI_NG
} gALSC_CALI_ERROR;

typedef struct
{
    gALSC_CALI_ERROR eRet;
    MS_U8 uTid;             //0 ~ 2
    MS_U32 u4Target;        //0 ~ 255
    MS_U8 uRatioTbl[32];    //0 ~ 255
    MS_U16 u2OB;            //0 ~ 256
} gALSC_CALI_CTRL;

typedef enum
{
    eOB_CALI_OK,
    eOB_CALI_NG
} OB_CALI_ERROR;

typedef struct
{
    OB_CALI_ERROR eRet;
    MS_U16 in_Target;
    MS_U16 in_weight[9];
    MS_U32 in_CaliGain;
    MS_CAM_BOOL in_FullAuto;
} OB_CALI_CTRL;

typedef enum
{
    geSDC_CALI_WHITE = 0,
    geSDC_CALI_BLACK,
    geSDC_CALI_MIXER
} gSDC_CALI_CTRL_ITEM;

typedef enum
{
    geSDC_CALI_OK,
    geSDC_CALI_NO_SUPPORT_WHITL_AND_BLOCK_AT_THE_SAME_TIME,
    geSDC_CALI_SET_PARA_NG,
    geSDC_CALI_GET_PARA_NG,
    geSDC_CALI_CALC_SDC_NG,
    geSDC_CALI_CALC_SDC_GET_RAW_HIST_STATIST_NG,
    geSDC_CALI_CALC_SDC_GET_RAW_ADAP_THRESHOLD_NG,
    geSDC_CALI_CALC_SDC_GET_RAW_CALI_AMOUNTS_NG,
    geSDC_CALI_CALC_SDC_GET_RAW_CALI_CALLOC_EMORY_NG,
    geSDC_CALI_CALC_SDC_FIND_CLUSTER_POSITION_NG,
    geSDC_CALI_CALC_SDC_FIND_CLUSTER_CURRENT_WINDOW_NG,
    geSDC_CALI_CALC_SDC_FIND_CLUSTER_CURRENT_WINDOW_AVERAGE_NG,
    geSDC_CALI_CALC_SDC_CHECK_CURRENT_WINDOW_IS_CLUSTER_NG,
    geSDC_CALI_CALC_SDC_DATA_SORTING_INIT_NG,
    geSDC_CALI_CALC_SDC_DATA_SORTING_FIRST_NG,
    geSDC_CALI_CALC_SDC_DATA_SORTING_SECOND_NG,
    geSDC_CALI_GET_SDC_RESULT_NG,
    geSDC_CALI_SET_SDC_DATA_EQUAL_NULL,
    geSDC_CALI_SET_SDC_DATA_FROM_DRAM_TO_SRAM_NG,
    geSDC_CALI_SET_SDC_DATA_AND_MENULOAD_NON_EQUAL
} gSDC_CALI_ERROR;

typedef struct
{
    gSDC_CALI_ERROR eRet;
    gSDC_CALI_CTRL_ITEM eItem;
    MS_U8 uMixerRatio;                                      // Range: [0,  100]
    MS_U8 uCaliImgNum[CAM20_SDC_CTRL_ITEM_NUMBER];          // Range: [1,  255]
    MS_U8 uInvalidRatio[CAM20_SDC_CTRL_ITEM_NUMBER];        // Range: [0,  100]
    MS_U32 u4CaliFlag[CAM20_SDC_CTRL_ITEM_NUMBER];          // Range: [0,    1]
    MS_U16 u2ValidValue[CAM20_SDC_CTRL_ITEM_NUMBER];        // Range: [0, 4095]
    MS_U32 u4TotalAmount[CAM20_SDC_CTRL_ITEM_NUMBER];       // Range: [0, 1920*1080] (image size)
    MS_U32 u4ClusterAmount[CAM20_SDC_CTRL_ITEM_NUMBER];     // Range: [0, 1920*1080] (image size)
} gSDC_CALI_CTRL;

//////////// FPN //////////////

typedef enum
{
    geFPN_CALI_OK,
    geFPN_CALI_NG
} gFPN_CALI_ERROR;

typedef struct
{
    gFPN_CALI_ERROR eRet;
    MS_U32 caliNum;         //range: [1, 100]
    MS_U32 caliGain;        //range: [1024, 1048576]
    MS_U32 strX;            //range: [0, 3072]
    MS_U32 strY;            //range: [0, 3072]
    MS_U32 winWidth;        //range: [0, 3072]
    MS_U32 winHeight;       //range: [0, 3072]
    MS_U32 diffThd;         //range: [0, 65535]
    MS_U32 stdThd;          //range: [0, 65535]
} gFPN_CALI_CTRL;

typedef enum
{
    AWB_CALI_UNIT_GOLDEN_H = 0,
    AWB_CALI_UNIT_GOLDEN_L = 1,
    AWB_CALI_UNIT_H = 2,
    AWB_CALI_UNIT_L = 3,
    AWB_CALI_UNIT_VERIFY = 4,
    AWB_CALI_UNIT_NUM = 5,
} AWB_CALI_UNIT_STATE;


// define in calibration_api.h
#if 0
typedef enum
{
    eAWB_CALI_OK,
    eAWB_CALI_NG
} AWB_UNIT_CALI_ERROR;
#endif

typedef struct
{
    AWB_UNIT_CALI_ERROR eRet; // define in calibration_api.h
    AWB_CALI_UNIT_STATE eCaliState;         //RW, Calibration State
    MS_U32 u4HighCT;                        //RW, Color temperature of calibration lightsource , Range: [1000, 10000]
    MS_U32 u4LowCT;                         //RW, Color temperature of calibration lightsource , Range: [1000, 10000]
    MS_U32 u4CaliNum;                       //RW, Color temperature of calibration lightsource Number, Range: [1, 2]
    MS_U16 u2GoldenHighRg;                  //RW, RGain of high color temperature lightsource , Range: [64, 4095]
    MS_U16 u2GoldenHighBg;                  //RW, BGain of high color temperature lightsource , Range: [64, 4095]
    MS_U16 u2GoldenLowRg;                   //RW, RGain of low color temperature lightsource , Range: [64, 4095]
    MS_U16 u2GoldenLowBg;                   //RW, BGain of low color temperature lightsource , Range: [64, 4095]
} AWB_CALI_CTRL;

typedef enum
{
    CALI_MIN_GAIN_OK,
    CALI_MIN_GAIN_NG
} CALI_MIN_GAIN_ERROR;

typedef struct
{
    MS_U32 in_init_shutter;
    MS_U16 in_gain_base;
    MS_U8 in_gain_interval;
} CALI_MIN_GAIN_CTRL;

typedef enum
{
    CALI_SHUTTER_LINEARITY_OK,
    CALI_SHUTTER_LINEARITY_NG
} CALI_SHUTTER_LINEARITY_ERROR;

typedef struct
{
    MS_U32 in_shutter_step[16];
} CALI_SHUTTER_LINEARITY_CTRL;

typedef enum
{
    CALI_GAIN_LINEARITY_OK,
    CALI_GAIN_LINEARITY_NG
} CALI_GAIN_LINEARITY_ERROR;

typedef struct
{
    MS_U32 in_init_shutter;
    MS_U32 in_gain_step[16];
    MS_U16 in_linearity_thd;
    MS_U16 in_max_y;
} CALI_GAIN_LINEARITY_CTRL;

/*------AE/AWB interface--------*/
/*! @brief API error code*/
enum CUS_3A_ERR_CODE
{
    CUS_3A_SUCCESS = 0, /**< operation successful */
    CUS_3A_ERROR = -1, /**< unspecified failure */
};

#define _3A_ROW             (128)   /**< number of 3A statistic blocks in a row */
#define _3A_COL             (90)    /**< number of 3A statistic blocks in a column */
#define _3A_HIST_BIN0    (40)    /**< histogram type0 resolution*/
#define _3A_HIST_BINX    (128)   /**< histogram type1 resolution*/

// AWB statistic , one sample
typedef struct
{
    MS_U8 r;
    MS_U8 g;
    MS_U8 b;
} __attribute__((packed, aligned(1))) ISP_AWB_SAMPLE;

/*! @brief AWB HW statistics data*/
typedef struct
{
    //ISP_AWB_SAMPLE data[_3A_ROW*_3A_COL];
    MS_U32 AvgBlkX;
    MS_U32 AvgBlkY;
    ISP_AWB_SAMPLE *avgs;
} __attribute__((packed, aligned(1))) ISP_AWB_INFO;

/*! @brief AWB algorithm result*/
typedef struct isp_awb_result
{
    MS_U32 Size; /**< struct size*/
    MS_U32 Change; /**< if true, apply this result to hw register*/
    MS_U32 R_gain; /**< AWB gain for R channel*/
    MS_U32 G_gain; /**< AWB gain for G channel*/
    MS_U32 B_gain; /**< AWB gain for B channel*/
    MS_U32 ColorTmp; /**< Return color temperature*/
} ISP_AWB_RESULT;

// AE statistics data
typedef struct
{
    MS_U8 r;
    MS_U8 g;
    MS_U8 b;
    MS_U8 y;
} __attribute__((packed, aligned(1))) ISP_AE_SAMPLE;

typedef struct
{
    MS_U16 u2HistY[_3A_HIST_BINX];
} __attribute__((packed, aligned(1))) ISP_HISTX;

/*! @brief ISP report to AE, hardware statistic */
typedef struct
{
    MS_U32 Size; /**< struct size*/
    ISP_HISTX *hist1; /**< HW statistic histogram 1*/
    ISP_HISTX *hist2; /**< HW statistic histogram 2*/
    MS_U32 AvgBlkX; /**< HW statistic average block number*/
    MS_U32 AvgBlkY; /**< HW statistic average block number*/
    ISP_AE_SAMPLE *avgs; /**< HW statistic average data*/
    MS_U32 Shutter; /**< Current shutter in ns*/
    MS_U32 SensorGain; /**< Current Sensor gain, 1X = 1024 */
    MS_U32 IspGain; /**< Current ISP gain, 1X = 1024*/
} __attribute__((packed, aligned(1))) ISP_AE_INFO;

//AE algorithm result
/*! @brief ISP ae algorithm result*/
typedef struct
{
    MS_U32 Size; /**< struct size*/
    MS_U32 Change; /**< if true, apply this result to hw register*/
    MS_U32 Shutter; /**< Shutter in ns */
    MS_U32 SensorGain; /**< Sensor gain, 1X = 1024 */
    MS_U32 IspGain; /**< ISP gain, 1X = 1024 */
    MS_U32 u4BVx16384; /**< Bv * 16384 in APEX system, EV = Av + Tv = Sv + Bv */
    MS_U32 AvgY; /**< frame brightness */
} __attribute__((packed, aligned(1))) ISP_AE_RESULT;

/*! @brief ISP initial status*/
typedef struct _isp_ae_init_param
{
    MS_U32 Size; /**< struct size*/
    char sensor_id[32]; /**< sensor module id*/
    MS_U32 shutter; /**< shutter Shutter in us*/
    MS_U32 shutter_step; /**< shutter Shutter step us*/
    MS_U32 shutter_min; /**< shutter Shutter min us*/
    MS_U32 shutter_max; /**< shutter Shutter max us*/
    MS_U32 sensor_gain; /**< sensor_gain Sensor gain, 1X = 1024*/
    MS_U32 sensor_gain_max; /**< sensor_gain_max Maximum Sensor gain, 1X = 1024*/
    MS_U32 isp_gain; /**< isp_gain Isp digital gain , 1X = 1024 */
    MS_U32 isp_gain_max; /**< isp_gain Maximum Isp digital gain , 1X = 1024 */
    MS_U32 FNx10; /**< F number * 10*/
    MS_U32 fps; /**< initial frame per second*/
} ISP_AE_INIT_PARAM;

typedef enum
{
    ISP_AE_FPS_SET, /**< ISP notify AE sensor FPS has changed*/
} ISP_AE_CTRL_CMD;

/*! @brief ISP initial status*/
typedef struct _isp_af_init_param
{
    MS_U32 Size; /**< struct size*/
    MS_CAM_AF_WIN af_stats_win[10];

} ISP_AF_INIT_PARAM;

typedef enum
{
    ISP_AF_CMD_MAX,
} ISP_AF_CTRL_CMD;

/*! @brief ISP report to AF, hardware statistic */
typedef struct
{
    MS_U32 Size; /**< struct size*/
    MS_CAM_AF_STATS af_stats; /**< AF statistic*/

} __attribute__((packed, aligned(1))) ISP_AF_INFO;

typedef struct
{
    MS_U32 Change; /**< if true, apply this result to hw*/
    MS_U32 Focal_pos; /**< Focal position*/
} __attribute__((packed, aligned(1))) ISP_AF_RESULT;

/**@brief ISP AE interface*/
typedef struct isp_ae_interface
{
    void *pdata; /**< Private data for AE algorithm.*/

    /** @brief AE algorithm init callback
     @param[in] pdata AE algorithm private data
     @param[in] init_state ISP initial status.
     @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
     @remark ISP call this function when AE algorithm initialize.
     */
    int (*init)(void* pdata, ISP_AE_INIT_PARAM *init_state);

    /** @brief AE algorithm close
     @param[in] pdata AE algorithm private data
     @remark ISP call this function when AE close.
     */
    void (*release)(void* pdata);

    /** @brief AE algorithm run
     @param[in] pdata AE algorithm private data
     @param[in] info ISP HW statistics
     @param[out] result AE algorithm return calculated result.
     @remark ISP call this function when AE close.
     */
    void (*run)(void* pdata, const ISP_AE_INFO *info, ISP_AE_RESULT *result);

    /** @brief AE algorithm control
     @param[in] pdata AE algorithm private data
     @param[in] cmd Control ID
     @param[in out] param Control parameter.
     @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
     @remark ISP call this function to change parameter
     */
    int (*ctrl)(void* pdata, ISP_AE_CTRL_CMD cmd, void* param);
} ISP_AE_INTERFACE;

typedef enum
{
    ISP_AWB_MODE_SET,
} ISP_AWB_CTRL_CMD;
/**@brief ISP AWB interface*/
typedef struct isp_awb_interface
{
    void *pdata; /**< Private data for AE algorithm.*/

    /** @brief AWB algorithm init callback
     @param[in] pdata Algorithm private data
     @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
     @remark ISP call this function when AE algorithm initialize.
     */
    int (*init)(void *pdata);

    /** @brief AWB algorithm close
     @param[in] pdata Algorithm private data
     @remark ISP call this function when AE close.
     */
    void (*release)(void *pdata);

    /** @brief AWB algorithm run
     @param[in] pdata Algorithm private data
     @param[in] info ISP HW statistics
     @param[out] result AWB algorithm return calculated result.
     @remark ISP call this function when AE close.
     */
    void (*run)(void *pdata, const ISP_AWB_INFO *awb_info, const ISP_AE_INFO *ae_info, ISP_AWB_RESULT *result);

    /** @brief AWB algorithm control
     @param[in] pdata Algorithm private data
     @param[in] cmd Control ID
     @param[in out] param Control parameter.
     @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
     @remark ISP call this function to change parameter
     */
    int (*ctrl)(void *pdata, ISP_AWB_CTRL_CMD cmd, void* param);
} ISP_AWB_INTERFACE;

/**@brief ISP AF interface*/
typedef struct isp_af_interface
{
    void *pdata; /**< Private data for AF algorithm.*/

    /** @brief AF algorithm init callback
     @param[in] pdata Algorithm private data
     @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
     @remark ISP call this function when AF algorithm initialize.
     */
    int (*init)(void *pdata, ISP_AF_INIT_PARAM *param);

    /** @brief AF algorithm close
     @param[in] pdata Algorithm private data
     @remark ISP call this function when AF close.
     */
    void (*release)(void *pdata);

    /** @brief AF algorithm run
     @param[in] pdata Algorithm private data
     @param[in] info ISP HW statistics
     @param[out] result AF algorithm return calculated result.
     @remark ISP call this function when AF close.
     */
    void (*run)(void *pdata, const ISP_AF_INFO *af_info, ISP_AF_RESULT *result);

    /** @brief AF algorithm control
     @param[in] pdata Algorithm private data
     @param[in] cmd Control ID
     @param[in out] param Control parameter.
     @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
     @remark ISP call this function to change parameter
     */
    int (*ctrl)(void *pdata, ISP_AF_CTRL_CMD cmd, void* param);
} ISP_AF_INTERFACE;

/**@brief ISP user API to register 3rd party AWB algorithm*/
int MS_ISP_AwbLibRegInterface(MS_U32 nChannel, ISP_AWB_INTERFACE *awb);

/**@brief ISP user API to register 3rd party AE algorithm*/
int MS_ISP_AeLibRegInterface(MS_U32 nChannel, ISP_AE_INTERFACE *ae);

/**@brief ISP user API to register 3rd party AF algorithm*/
int MS_ISP_AfLibRegInterface(MS_U32 nChannel, ISP_AF_INTERFACE *af);
/** @} */            // end of ISP Customer 3A Interface

int MS_CAM_SetAeWin(MS_U32 nChannel, MS_AE_WIN ae_win);
int MS_CAM_AeStatsEnable(MS_U32 nChannel, bool enable);
int MS_CAM_GetAeStats(MS_U32 nChannel, MS_AE_AVGS *stats);
int MS_CAM_SetAwbWin(MS_U32 nChannel, MS_AWB_WIN awb_win);

int MS_CAM_AwbStatsEnable(MS_U32 nChannel, bool enable);
int MS_CAM_GetAwbStats(MS_U32 nChannel, MS_AWB_AVGS *stats);

int MS_CAM_SetRotate(MS_U32 nChannel, MS_CAM_ROTATIONTYPE* RotateType);
int MS_CAM_GetRotate(MS_U32 nChannel, MS_CAM_ROTATIONTYPE* RotateType);

int MS_CAM_GetSensorID(MS_U32 nChannel, MS_CAM_SENSOR_IDTYPE* SensorID);

int MS_CAM_SetMirrorFlip(MS_U32 nChannel, MS_CAM_MIRRORTYPE* MirrorType);
int MS_CAM_GetMirrorFlip(MS_U32 nChannel, MS_CAM_MIRRORTYPE* MirrorType);

int MS_CAM_WriteI2C(MS_U32 nChannel, MS_U32 SlaveAddr, MS_U32 AddrWidth, MS_U32 DataWidth, MS_U32 I2CSpeed, MS_U32 Addr, MS_U32 Data);
int MS_CAM_ReadI2C(MS_U32 nChannel, MS_U32 SlaveAddr, MS_U32 AddrWidth, MS_U32 DataWidth, MS_U32 I2CSpeed, MS_U32 Addr, MS_U32 *data);
int MS_CAM_ISP_QuerySensorInfo(MS_U32 nChannel, MS_CAM_SENSORINFO* SensorInfo);

/*---------AE------S----*/
int MS_CAM_ISP_QueryExposureInfo(MS_U32 nChannel, MS_ISP_EXP_INFO_S* sExpInfo);
int MS_CAM_ISP_SetEVComp(MS_U32 nChannel, MS_S32 i4EV, MS_U32 u4Grad);
int MS_CAM_ISP_GetEVComp(MS_U32 nChannel, MS_S32 *i4EV, MS_U32 *u4Grad);
int MS_CAM_ISP_SetExpMode(MS_U32 nChannel, MS_AEMODETYPE mode); //Auto,AV,SV,TV,M mode
int MS_CAM_ISP_GetExpMode(MS_U32 nChannel, MS_AEMODETYPE *mode);
int MS_CAM_ISP_SetManualExpo(MS_U32 nChannel, MS_U32 u4FNx10, MS_U32 u4SensorGain, MS_U32 u4ISPGain, MS_U32 u4US);
int MS_CAM_ISP_GetManualExpo(MS_U32 nChannel, MS_U32 *u4FNx10, MS_U32 *u4SensorGain, MS_U32 *u4ISPGain, MS_U32 *u4US);
int MS_CAM_ISP_SetAEState(MS_U32 nChannel, MS_CAM_ISP_SM_STATE eState);  // Pause, Resume
int MS_CAM_ISP_GetAEState(MS_U32 nChannel, MS_CAM_ISP_SM_STATE *eState);
int MS_CAM_ISP_SetAETarget(MS_U32 nChannel, MS_INTP_LUT *AeTarget);
int MS_CAM_ISP_GetAETarget(MS_U32 nChannel, MS_INTP_LUT *AETarget);
int MS_CAM_ISP_SetAEConverge(MS_U32 nChannel, MS_AE_CONV_CONDITON *sConvConditoin);
int MS_CAM_ISP_GetAEConverge(MS_U32 nChannel, MS_AE_CONV_CONDITON *sConvConditoin);
int MS_CAM_ISP_SetExposureLimit(MS_U32 nChannel, MS_AE_EXP_LIMIT_TYPE* sExpLimit);
int MS_CAM_ISP_GetExposureLimit(MS_U32 nChannel, MS_AE_EXP_LIMIT_TYPE* sExpLimit);
int MS_CAM_ISP_SetMinMaxShutterUS(MS_U32 nChannel, MS_MIN_MAX_SHUTTERTYPE* nSetMinMaxShutter);
int MS_CAM_ISP_SetPlainExpTbl(MS_U32 nChannel, MS_AE_EXPO_TBLTYPE *ePExpTbl);
int MS_CAM_ISP_GetPlainExpTbl(MS_U32 nChannel, MS_AE_EXPO_TBLTYPE *ePExpTbl);
int MS_CAM_ISP_SetPlainShortExpTbl(MS_U32 nChannel, MS_AE_EXPO_TBLTYPE *ePExpTbl);
int MS_CAM_ISP_GetPlainShortExpTbl(MS_U32 nChannel, MS_AE_EXPO_TBLTYPE *ePExpTbl);
int MS_CAM_ISP_SetAEHDR(MS_U32 nChannel, MS_CAM_AE_HDR_TYPE *AeHdr);
int MS_CAM_ISP_GetAEHDR(MS_U32 nChannel, MS_CAM_AE_HDR_TYPE *AeHdr);
int MS_CAM_ISP_SetAEWinWgt(MS_U32 nChannel, MS_CAM_AE_WINWGT *sAeWinWgt);
int MS_CAM_ISP_GetAEWinWgt(MS_U32 nChannel, MS_CAM_AE_WINWGT *sAeWinWgt);
int MS_CAM_SetFlicker(MS_U32 nChannel, MS_FLICKER_TYPE eFlicker);
int MS_CAM_GetFlicker(MS_U32 nChannel, MS_FLICKER_TYPE *eFlicker);
int MS_CAM_ISP_DoAutoFlickerFrequencyDetect(MS_U32 nChannel);
int MS_CAM_ISP_SetAEStrategy(MS_U32 nChannel, MS_AE_STRATEGY_S* eSetAeStrategy);
int MS_CAM_ISP_GetAEStrategy(MS_U32 nChannel, MS_AE_STRATEGY_S* eSetAeStrategy);

//for customer 3A
//int MS_CAM_ISP_GetAEHWStats(MS_U32 nChannel, void *pBuffer, MS_U32 u4BuffSize);
//int MS_CAM_SetAEWindowBlockNumber(MS_U32 nChannel, MS_CAM_AE_WIN_BLOCK_NUM eBlkNum);
//int MS_CAM_SetHistogramWindow(MS_U32 nChannel, const MS_CAM_HIST_WIN* HistWin, int WinIdx);
/*---------AE------E----*/

/*---------AWB----------*/
int MS_CAM_SetWhiteBalance(MS_U32 nChannel, MS_CAM_WHITEBALCONTROLTYPE* WBType);
int MS_CAM_GetWhiteBalance(MS_U32 nChannel, MS_CAM_WHITEBALCONTROLTYPE* WBType);
int MS_CAM_SetAwbSampling(MS_U32 nChannel, MS_U32 SizeX, MS_U32 SizeY);

/*---------AF----------*/
int MS_CAM_QueryAFInfo(MS_U32 nChannel, MS_CAM_AF_INFO* AFInfo);
int MS_CAM_SetAFWindow(MS_U32 nChannel, MS_CAM_AF_WIN AFWin, int Win_id);
int MS_CAM_GetAFWindow(MS_U32 nChannel, MS_CAM_AF_WIN* AFWin, int Win_id);
int MS_CAM_SetAFFilter(MS_U32 nChannel, MS_CAM_AF_FILTER_ATTR AFAttr);
int MS_CAM_GetAFFilter(MS_U32 nChannel, MS_CAM_AF_FILTER_ATTR *AFAttr);

/*---------API-IQ(S)----------*/
int MS_CAM20_GetIQVersionInfo(MS_U32 nChannel, MS_U32 *Major, MS_U32 *Minor);
int MS_CAM20_GetIQfileVersionInfo(MS_U32 nChannel, MS_U32 *IQfile_Vendor, MS_U32 *IQfile_Major, MS_U32 *IQfile_Minor);
int MS_CAM20_SetIQFastMdoe(MS_U32 nChannel, MS_CAM_BOOL FastMdoe);
int MS_CAM20_GetIQFastMdoe(MS_U32 nChannel, MS_CAM_BOOL *FastMdoe);
int MS_CAM20_GetIQParaInitStatus(MS_U32 nChannel, MS_U8 *Flag);
int MS_CAM20_SetColorToGray(MS_U32 nChannel, MS_CAM20_COLORTOGRAY* ColorToGray);
int MS_CAM20_GetColorToGray(MS_U32 nChannel, MS_CAM20_COLORTOGRAY* ColorToGray);
int MS_CAM20_SetLightness(MS_U32 nChannel, MS_CAM20_LIGHTNESSTYPE* LightnessType);
int MS_CAM20_GetLightness(MS_U32 nChannel, MS_CAM20_LIGHTNESSTYPE* LightnessType);
int MS_CAM20_SetContrast(MS_U32 nChannel, MS_CAM20_CONTRASTTYPE* ContrastType);
int MS_CAM20_GetContrast(MS_U32 nChannel, MS_CAM20_CONTRASTTYPE* ContrastType);
int MS_CAM20_SetBrightness(MS_U32 nChannel, MS_CAM20_BRIGHTNESSTYPE* BrightnessType);
int MS_CAM20_GetBrightness(MS_U32 nChannel, MS_CAM20_BRIGHTNESSTYPE* BrightnessType);
int MS_CAM20_SetGammaLUT(MS_U32 nChannel, MS_CAM20_GAMMA_LUT_TYPE* GamaLutType);
int MS_CAM20_GetGammaLUT(MS_U32 nChannel, MS_CAM20_GAMMA_LUT_TYPE* GamaLutType);
int MS_CAM20_SetYUVGammaLUT(MS_U32 nChannel, MS_CAM20_YUVGAMMA_LUT_TYPE *YUVGamaLutType);
int MS_CAM20_GetYUVGammaLUT(MS_U32 nChannel, MS_CAM20_YUVGAMMA_LUT_TYPE *YUVGamaLutType);
int MS_CAM20_SetSaturation(MS_U32 nChannel, MS_CAM20_SATURATIONTYPE* SaturationType);
int MS_CAM20_GetSaturation(MS_U32 nChannel, MS_CAM20_SATURATIONTYPE* SaturationType);
int MS_CAM20_SetDefog(MS_U32 nChannel, MS_CAM20_DEFOGTYPE *sDefog);
int MS_CAM20_GetDefog(MS_U32 nChannel, MS_CAM20_DEFOGTYPE *sDefog);
int MS_CAM20_SetDRC(MS_U32 nChannel, MS_CAM20_DRCTYPE *sDRC);
int MS_CAM20_GetDRC(MS_U32 nChannel, MS_CAM20_DRCTYPE *sDRC);
int MS_CAM20_SetRGBmatrix(MS_U32 nChannel, MS_CAM20_RGBMARIX_TYPE *sRGBMatrix);
int MS_CAM20_GetRGBmatrix(MS_U32 nChannel, MS_CAM20_RGBMARIX_TYPE *sRGBMatrix);
int MS_CAM20_SetFalseColor(MS_U32 nChannel, MS_CAM20_FALSECOLOR_TYPE *sFalseColor);
int MS_CAM20_GetFalseColor(MS_U32 nChannel, MS_CAM20_FALSECOLOR_TYPE *sFalseColor);
int MS_CAM20_SetFalseColor2(MS_U32 nChannel, MS_CAM20_FALSECOLOR2_TYPE *sFalseColor);
int MS_CAM20_GetFalseColor2(MS_U32 nChannel, MS_CAM20_FALSECOLOR2_TYPE *sFalseColor);
int MS_CAM20_SetNR3D(MS_U32 nChannel, MS_CAM20_NR3D_TYPE* sNR3D);
int MS_CAM20_GetNR3D(MS_U32 nChannel, MS_CAM20_NR3D_TYPE* sNR3D);
int MS_CAM20_SetNRBayer(MS_U32 nChannel, MS_CAM20_NRBayer_TYPE* sNRBayer);
int MS_CAM20_GetNRBayer(MS_U32 nChannel, MS_CAM20_NRBayer_TYPE* sNRBayer);
int MS_CAM20_SetNRDeSpike(MS_U32 nChannel, MS_CAM20_NRDeSpike_TYPE* sNRDeSpike);
int MS_CAM20_GetNRDeSpike(MS_U32 nChannel, MS_CAM20_NRDeSpike_TYPE* sNRDeSpike);
int MS_CAM20_SetNRLuma(MS_U32 nChannel, MS_CAM20_NRLuma_TYPE* sNRLuma);
int MS_CAM20_GetNRLuma(MS_U32 nChannel, MS_CAM20_NRLuma_TYPE* sNRLuma);
int MS_CAM20_SetSharpness(MS_U32 nChannel, MS_CAM20_SHARPNESS_TYPE* sSharpness);
int MS_CAM20_GetSharpness(MS_U32 nChannel, MS_CAM20_SHARPNESS_TYPE* sSharpness);
int MS_CAM20_SetSharpness2(MS_U32 nChannel, MS_CAM20_SHARPNESS2_TYPE* sSharpness2);
int MS_CAM20_GetSharpness2(MS_U32 nChannel, MS_CAM20_SHARPNESS2_TYPE* sSharpness2);
int MS_CAM20_SetCrossTalk(MS_U32 nChannel, MS_CAM20_CROSSTALK_TYPE *sCrossTalk);
int MS_CAM20_GetCrossTalk(MS_U32 nChannel, MS_CAM20_CROSSTALK_TYPE *sCrossTalk);
int MS_CAM20_SetOBC(MS_U32 nChannel, MS_CAM20_OBC_TYPE *sOBC);
int MS_CAM20_GetOBC(MS_U32 nChannel, MS_CAM20_OBC_TYPE *sOBC);
int MS_CAM20_SetOBC_P1(MS_U32 nChannel, MS_CAM20_OBC_TYPE *sOBC);
int MS_CAM20_GetOBC_P1(MS_U32 nChannel, MS_CAM20_OBC_TYPE *sOBC);
int MS_CAM20_SetCSA(MS_U32 nChannel, MS_CAM20_CSA_TYPE *sCSA);
int MS_CAM20_GetCSA(MS_U32 nChannel, MS_CAM20_CSA_TYPE *sCSA);
int MS_CAM20_SetWDR(MS_U32 nChannel, MS_CAM20_WDR_TYPE* sWdr);
int MS_CAM20_GetWDR(MS_U32 nChannel, MS_CAM20_WDR_TYPE* sWdr);
int MS_CAM20_SetWDRGbl(MS_U32 nChannel, MS_CAM20_WDR_GBL_TYPE* sWdr);
int MS_CAM20_GetWDRGbl(MS_U32 nChannel, MS_CAM20_WDR_GBL_TYPE* sWdr);
int MS_CAM20_SetDynamicDP(MS_U32 nChannel, MS_CAM20_DYNAMIC_DP_TYPE *sDynamicDP);
int MS_CAM20_GetDynamicDP(MS_U32 nChannel, MS_CAM20_DYNAMIC_DP_TYPE *sDynamicDP);
int MS_CAM20_SetHSV(MS_U32 nChannel, MS_CAM20_HSV_TYPE *sHsv);
int MS_CAM20_GetHSV(MS_U32 nChannel, MS_CAM20_HSV_TYPE *sHsv);
int MS_CAM20_SetRGBIR(MS_U32 nChannel, MS_CAM20_RGBIR_TYPE *sRGBIR);
int MS_CAM20_GetRGBIR(MS_U32 nChannel, MS_CAM20_RGBIR_TYPE *sRGBIR);
int MS_CAM20_SetFPN(MS_U32 nChannel, MS_CAM20_FPN_TYPE *sFPN);
int MS_CAM20_GetFPN(MS_U32 nChannel, MS_CAM20_FPN_TYPE *sFPN);
int MS_CAM20_SetHDR16to12(MS_U32 nChannel, MS_CAM20_HDR16to12_TYPE *sHDR16to12);
int MS_CAM20_GetHDR16to12(MS_U32 nChannel, MS_CAM20_HDR16to12_TYPE *sHDR16to12);
int MS_CAM20_SetCOLORTRANS(MS_U32 nChannel, MS_CAM20_COLORTRANS_TYPE *sCOLORTRANS);
int MS_CAM20_GetCOLORTRANS(MS_U32 nChannel, MS_CAM20_COLORTRANS_TYPE *sCOLORTRANS);
int MS_CAM20_SetHDR(MS_U32 nChannel, MS_CAM20_HDR_TYPE *sHDR);
int MS_CAM20_GetHDR(MS_U32 nChannel, MS_CAM20_HDR_TYPE *sHDR);
int MS_CAM20_SetEffect(MS_U32 nChannel, MS_CAM20_EFFECT* EffectType);
int MS_CAM20_GetEffect(MS_U32 nChannel, MS_CAM20_EFFECT* EffectType);
int MS_CAM20_SetEnSysMcnrMemory(MS_U32 nChannel, MS_U8 enable);
int MS_CAM20_GetEnSysMcnrMemory(MS_U32 nChannel, MS_U8 *enable);
int MS_CAM20_GetYUVHisto(MS_U32 nChannel, MS_CAM20_YUVHISTOTYPE *attr);
int MS_CAM20_SetAPIBypassMode(MS_U32 nChannel, MS_CAM20_API_ID APIind, MS_CAM20_BypassMode mode);
int MS_CAM20_GetAPIBypassMode(MS_U32 nChannel, MS_CAM20_API_ID APIind, MS_CAM20_BypassMode *mode);
int MS_CAM20_SysSetDualSensorMode(MS_U32 nChannel, MS_U8 enable);
int MS_CAM20_SysGetDualSensorMode(MS_U32 nChannel, MS_U8 *enable);
/*---------API-IQ(E)----------*/

int MS_CAM_GetLinearityLUT(MS_U32 nChannel, MS_CAM_GAMMA_LUT_TYPE* GamaLutType);
int MS_GetOBCCALIB(MS_U32 nChannel, MS_CAM_OBC4Ch_TYPE *sOBC);
int MS_CAM_SetLSC(MS_U32 nChannel, MS_CAM_LSC_TYPE *sLsc);
int MS_CAM_GetLSC(MS_U32 nChannel, MS_CAM_LSC_TYPE *sLsc);
int MS_CAM_SetIQMode(MS_U32 nChannel, MS_CAM_IQ_PARA_MODE ParaModInd);
int MS_CAM_GetIQMode(MS_U32 nChannel, MS_CAM_IQ_PARA_MODE *ParaModInd);
int MS_CAM_GetIQind(MS_U32 nChannel, MS_U8 *iqind);

/*---------SCL----------*/

/*---------HS----------*/
int MS_CAM_ISP_SetWBAttr(MS_U32 nChannel, MS_CAM_ISP_WB_ATTR_S* sWBAttr);
int MS_CAM_ISP_GetWBAttr(MS_U32 nChannel, MS_CAM_ISP_WB_ATTR_S* sWBAttr);
int MS_CAM_ISP_SetWBAttrEx(MS_U32 nChannel, MS_CAM_ISP_AWB_ATTR_EX_S* sWBAttrEx);
int MS_CAM_ISP_GetWBAttrEx(MS_U32 nChannel, MS_CAM_ISP_AWB_ATTR_EX_S* sWBAttrEx);
int MS_CAM_ISP_QueryWBInfo(MS_U32 nChannel, MS_CAM_ISP_AWB_INFO_S* sWBInfo);
int MS_CAM_ISP_SetWBCTCaliAttr(MS_U32 nChannel, MS_CAM_AWB_CT_CALI_ATTR* sCtAttr);
int MS_CAM_ISP_GetWBCTCaliAttr(MS_U32 nChannel, MS_CAM_AWB_CT_CALI_ATTR* sCtAttr);
int MS_CAM_ISP_SetWBCTWeight(MS_U32 nChannel, MS_U16 u2LvIndex, MS_CAM_AWB_CT_WEIGHT* sCtWeight);
int MS_CAM_ISP_GetWBCTWeight(MS_U32 nChannel, MS_U16 u2LvIndex, MS_CAM_AWB_CT_WEIGHT* sCtWeight);
int MS_CAM_ISP_GetAWBHWStats(MS_U32 nChannel, void *pBuffer, MS_U32 u4BuffSize);
int MS_CAM_ISP_GetAWBCTStats(MS_U32 nChannel, MS_CAM_AWB_CT_STATISTICS* pCtStatis);

/*****************************calibration***********************************************/

s32 SS_CALIv30_OB_CaliApply(u32 nChannel, void *pData);
s32 SS_CALIv30_AWB_CaliApply(u32 nChannel, void *pData);
s32 SS_CALIv30_ALSC_CaliApply(u32 nChannel, void *pData);
s32 SS_CALIv30_SDC_CaliApply(u32 nChannel, void *pData);


