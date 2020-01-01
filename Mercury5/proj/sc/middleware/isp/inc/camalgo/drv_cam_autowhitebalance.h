#include "calibration_api.h"

#ifndef __CAMERA_AUTOWHITEBALANCE_H__
#define __CAMERA_AUTOWHITEBALANCE_H__

#define AWB_IN_KERNEL (0)

#ifdef __cplusplus
extern "C"
{
#endif
#define RTOS_PORTING                        (1)
#define RTOS_INPUT_AWB_STATIS               (1) //0 : I3 linux method, 1 : RTOS access parameters method
#define RTOS_UNUSE_SET_GET_PROPERTY         (1)

#if AWB_IN_KERNEL
#include <linux/string.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#endif

#if (!RTOS_PORTING)
#include "dbg_info.h"
#include "drv_ms_camera_sensor.h"
#include "../../../common/isp_sys_api.h"
#include "drv_ms_isp_hal.h"
#include "drv_ms_isp_general.h"
#include "drv_cam_autoexposure.h"
#else
    #include "isp_3a_if.h"
    #if AWB_IN_KERNEL
    #else
    #include "libcamera.h"
    #include <isp_sys_api.h>
    #include "sys_MsWrapper_cus_os_sem.h"
    MS_S8 UartSendTrace(const char *strFormat, ...);
    #endif
#endif

#ifndef WIN32
    #if AWB_IN_KERNEL
    #include <linux/time.h>
    #include <linux/timer.h>
    #include <drv_ms_rwcfg.h>
    #else
    #include <sys/time.h>
    #include "drv_ms_rwcfg.h"
    #endif

    #if (!RTOS_PORTING)
    #include "camlog.h"
    #include "algo_mgr.h"
    #include "drv_ms_ispcfg.h"
    #include <isp_file_mgr.h>
    #endif
#endif

#if AWB_IN_KERNEL
typedef void                        VOID;
#else
#endif

#if (RTOS_UNUSE_SET_GET_PROPERTY)
#define RTOS_AWB_DEBUG_TEST_API             (0)
#define RTOS_AWB_DEBUG_ENABLE_AWB           (1)
#define RTOS_AWB_DEBUG_MWB_ENABLE           (0)
#define RTOS_AWB_DEBUG_MWB_RGAIN            (1024)
#define RTOS_AWB_DEBUG_MWB_BGAIN            (1024)
#define RTOS_AWB_DEBUG_LEVEL                (0)
#define RTOS_AWB_DEBUG_PREFER_ENABLE        (0)
#define RTOS_AWB_DEBUG_PREFER_RGSTHR        (AWB_STRENGTH_BASE)
#define RTOS_AWB_DEBUG_PREFER_BGSTHR        (AWB_STRENGTH_BASE)
#endif

#define AWB_WIN_WIDTH                       (64)
#define AWB_WIN_HEIGHT                      (90)
#define AWB_WIN_NUM                         (AWB_WIN_WIDTH*AWB_WIN_HEIGHT)
#define AWB_GAIN_BASE                       (1024)
#define AWB_WEIGHT_BASE                     (100)
#define AWB_AREA_BASE                       (100)
#define AWB_AREA_RG_MAX                     (800)
#define AWB_AREA_BG_MAX                     (800)
#define AWB_AREA_SIZE_MAX                   (32)
#define AWB_AREA_SCALE_BASE                 (16)
#define AWB_AREA_SCALE_MAX                  (16)
#define AWB_LUM_MAX                         (224)
#define AWB_LUM_MIN                         (4)
#define AWB_LV_TBL_NUM                      (18)
#define AWB_WHITE_CNT_THD                   (50)
#define AWB_PREGAIN_NUM                     (8)
#define AWB_FRAME_DIFF_THD                  (20)
#define AWB_SPEED_FAST                      (100)
#define AWB_SPEED_NORMAL                    (30)
#define AWB_STRENGTH_BASE                   (128)
#define AWB_STRENGTH_MAX                    (255)
#define AWB_DEBUG_FRAME_GAP                 (900)
#define AWB_DEBUG_API_FRAME                 (100)
#define AWB_LIMIT_GAIN_MAX                  (8191)
#define AWB_LIMIT_GAIN_MIN                  (256)
#define AWB_LIMIT_CT_MAX                    (10000)
#define AWB_LIMIT_CT_MIN                    (1000)
#define AWB_MIX_THIRD_THD                   (20)
#define AWB_LOW_LUX_THD                     (20)    // LV2 x10

#define AWB_COLORTEMP_BASE                  (20000)

#define AWB_IR_OFF_Y_MIN                    (10)    // 8bit domain, rgb value under 10, ignore
#define AWB_IR_OFF_STABLE_THD               (10)    // unstable 60 frame, disable ir led
#define AWB_IR_OFF_RATIO                    (1280)  // 1x = 1024, rgb ratio
#define AWB_IR_OFF_CNT_THD                  (80)    // over 80% unsatble

#define AWB_CT_USER_NUM                     (4)
#define AWB_CT_UNIT                         (100)

#define AWB_CALIB_PARAM_NUM                 (4)
#define AWB_CALIB_TOTAL_NUM                 (40)
#define AWB_CALIB_GAIN_MAX                  (4095)
#define AWB_CALIB_GAIN_MIN                  (64)
#define AWB_LT_POINT_NUM                    (8)

#define AWB_BLK_VALID_X                     (4)
#define AWB_BLK_VALID_Y                     (2)
#define AWB_BLK_VALID_LOW_LUX_X             (10)
#define AWB_BLK_VALID_LOW_LUX_Y             (8)
#define BASE                                (16384)

struct __camsensor_handle_t;
struct __cam_awb_handle_t;
typedef enum
{
    AWB_SM_START,
    AWB_SM_CAL,
    AWB_SM_MANUAL,
    AWB_SM_NIGHT,
    AWB_SM_STOP,
    AWB_SM_PAUSE,
    AWB_SM_RESUME,
    AWB_SM_END
} AWB_SM;

typedef enum
{
    AWB_CT_HIGH_1 = 0,// 20000K
    AWB_CT_HIGH_2,    // 16000K
    AWB_CT_HIGH_3,    // 11000K
    AWB_CT_6500K,     // D65
    AWB_CT_5000K,     // D50
    AWB_CT_4000K,     // TL84
    AWB_CT_3000K,     // A
    AWB_CT_2300K,     // Horizon
    AWB_CT_1500K,
    AWB_CT_1000K,
    AWB_CT_NUM
} AWB_CT;

typedef enum
{
    AWB_CT_HIGHPRE_20000k = 0,
    AWB_CT_HIGHPRE_17500k,
    AWB_CT_HIGHPRE_15000k,
    AWB_CT_HIGHPRE_12500k,
    AWB_CT_HIGHPRE_10000k,
    AWB_CT_HIGHPRE_8250k,
    AWB_CT_HIGHPRE_6500K,
    AWB_CT_HIGHPRE_5750K,
    AWB_CT_HIGHPRE_5000K,
    AWB_CT_HIGHPRE_4500K,
    AWB_CT_HIGHPRE_4000K,
    AWB_CT_HIGHPRE_3500K,
    AWB_CT_HIGHPRE_3000K,
    AWB_CT_HIGHPRE_2650K,
    AWB_CT_HIGHPRE_2300K,
    AWB_CT_HIGHPRE_1900K,
    AWB_CT_HIGHPRE_1500K,
    AWB_CT_HIGHPRE_1250K,
    AWB_CT_HIGHPRE_1000K,
    AWB_CT_HIGHPRE_NUM
} AWB_CT_HighPre;

#define AWB_CT_START (AWB_CT_HIGH_3)
#define AWB_CT_END   (AWB_CT_2300K)

typedef enum
{
    AWB_CT_STATUS_CURRENT = 0,
    AWB_CT_STATUS_FINAL = 1,
    AWB_CT_STATUS_NUM
} AWB_CT_STATUS;

//Sensor relation
typedef enum
{
    AWB_MODE_AUTO,
    AWB_MODE_MANUAL,
    AWB_MODE_MODE_CALI,
    AWB_MODE_END
} AWB_MODE;

//Sensor relation
typedef enum
{
    AWB_SCENE_DAYLIGHT,       ///< Daylight
    AWB_SCENE_CLOUDY,         ///< Cloudy
    AWB_SCENE_SHADE,
    AWB_SCENE_TUNGSTEN,       ///< Tungsten
    AWB_SCENE_FLUORESCENT,    ///< Fluorescent
    AWB_SCENE_INCANDESCENT,
    AWB_SCENE_FLASH,
    AWB_SCENE_HORIZON,
    AWB_SCENE_BACKLIGHT,
    AWB_SCENE_BEACH,
    AWB_SCENE_FIREWORKS,
    AWB_SCENE_LANDSCAPE,
    AWB_SCENE_MACRO,
    AWB_SCENE_NIGHT,
    AWB_SCENE_PARTY,
    AWB_SCENE_PORTRAIT,
    AWB_SCENE_SPORTS,
    AWB_SCENE_SUNSET,
    AWB_SCENE_AQUARIUM,
    AWB_SCENE_FOLIAGE,
} AWB_SCENE;

//OpenMAX relation
typedef enum AWB_CONTROL_MODE_
{
    AWB_CONTROL_OFF = 0,
    AWB_CONTROL_AUTO,           // 1
    AWB_CONTROL_SUNLIGHT,       // 2 Referenced in JSR-234
    AWB_CONTROL_CLOUDY,         // 3
    AWB_CONTROL_SHADE,          // 4
    AWB_CONTROL_TUNGSTEN,       // 5
    AWB_CONTROL_FLUORESCENT,    // 6
    AWB_CONTROL_INCANDESCENT,   // 7
    AWB_CONTROL_FLASH,          // 8 Optimal for device's integrated flash
    AWB_CONTROL_HORIZON,        // 9
    AWB_CONTROL_MANUAL,         //10
    AWB_CONTROL_NUM
} AWB_CONTROL_MODE;

typedef struct AWB_GAIN_
{
    MS_U16 Rgain;
    MS_U16 Ggain;
    MS_U16 Bgain;
} AWB_GAIN;

typedef struct AWB_ISP_GAIN_
{
    MS_U32 Rgain;
    MS_U32 Grgain;
    MS_U32 Gbgain;
    MS_U32 Bgain;
} AWB_ISP_GAIN;

typedef struct AWB_RBGAIN_
{
    MS_U16 Rgain;
    MS_U16 Bgain;
} AWB_RBGAIN;

typedef struct AWB_AVG_GAIN_
{
    MS_U8 AvgRgain;
    MS_U8 AvgGgain;
    MS_U8 AvgBgain;
} AWB_AVG_GAIN;

//new algo
//////////////////////////////////////
typedef enum
{
    AWB_LIGHT_SHADE = 0,    // 7000k
    AWB_LIGHT_D65,          // 6500k
    AWB_LIGHT_D50,          // 5000k
    AWB_LIGHT_TL84,         // 4000k
    AWB_LIGHT_A,            // 3000k
    AWB_LIGHT_F,            // 2700k
    AWB_LIGHT_NUM
} AWB_LIGHT_INDEX;

typedef enum
{
    AWB_PRESET_SHADE = 0,   // 7000k
    AWB_PRESET_D65,         // 6500K
    AWB_PRESET_D50,         // 5000k
    AWB_PRESET_FLUORESENT,  // 4000k
    AWB_PRESET_TUNGSTEN,    // 3200k
    AWB_PRESET_INCANDESENT, // 2800k
    AWB_PRESET_HORIZON,     // 2300k
    AWB_PRESET_SUNLIGHT,    // 5600k
    AWB_PRESET_CLOUDY,      // 6000k
    //AWB_PRESET_FLASH,     // 5000k
    AWB_PRESET_NUM
} AWB_PRESET_INDEX;

#define AWB_LIGHT_NOFOUND   (AWB_CT_NUM)//(AWB_LIGHT_NUM)

typedef enum
{
    AWB_SPECIAL_GREEN1 = 0,
    AWB_SPECIAL_GREEN2,
    AWB_SPECIAL_DARKSKIN,
    AWB_SPECIAL_RED,
    AWB_SPECIAL_BLUE,
    AWB_SPECIAL_RESERVED1,
    AWB_SPECIAL_RESERVED2,
    AWB_SPECIAL_RESERVED3,
    AWB_SPECIAL_TOTAL
} AWB_LIGHT_SPCIAL;

#define AWB_SPECIAL_NUM     (AWB_SPECIAL_RESERVED1)

typedef enum
{
    AWB_OP_NORMAL,
    AWB_OP_SUM,
    AWB_OP_CALI,
    AWB_OP_TUNING
} AWB_OP_MODE;

typedef enum
{
    AWB_ALG_DEFAULT,
    AWB_ALG_ADVANCE,
    AWB_ALG_NUM
} AWB_ALG_MODE;

typedef enum
{
    AWB_DAYLIGHT_0 = 0,
    AWB_DAYLIGHT_1,
    AWB_DAYLIGHT_NUM
} AWB_DAYLIGHT_TYPE;

typedef enum
{
    AWB_GAIN_1 = 0,     // 0
    AWB_GAIN_2,         // 1
    AWB_GAIN_MIX_1,     // 2
    AWB_GAIN_MIX_2,     // 3
    AWB_GAIN_PREFER_1,  // 4
    AWB_GAIN_USER,      // 5
    AWB_GAIN_NORMAL,    // 6
    AWB_GAIN_COMP,      // 7
    AWB_GAIN_PRE,       // 8
    AWB_GAIN_TARGET,    // 9
    AWB_GAIN_TYPE_NUM
} AWB_GAIN_TYPE;

typedef enum
{
    AWB_CALI_DEFAULT_H = 0,
    AWB_CALI_CT_H,
    AWB_CALI_DEFAULT_L,
    AWB_CALI_CT_L,
    AWB_CALI_NUM
} AWB_CALI_TYPE;

typedef enum
{
    AWB_SPC_GREEN       = 0x0001,
    AWB_SPC_DARKSKIN    = 0x0002,
    AWB_SPC_BLUE        = 0x0004,
    AWB_SPC_RED         = 0x0008,
    AWB_SPC_YELLOW      = 0x0010,
} AWB_SPEIAL_CASE;

typedef enum
{
    AWB_AREA_SCALE_NONE,
    AWB_AREA_SCALE_X,
    AWB_AREA_SCALE_Y,
    AWB_AREA_SCALE_CORNER,
} AWB_AREA_SCALE;

typedef struct _AWB_LIGHT_AREA
{
    MS_S32 P0_X;
    MS_S32 P0_Y;
    MS_S32 P1_X;
    MS_S32 P1_Y;
    MS_S32 P2_X;
    MS_S32 P2_Y;
    MS_S32 P3_X;
    MS_S32 P3_Y;
} AWB_LIGHT_AREA;

typedef struct _AWB_LIGHT_USER
{
    MS_BOOL bEnable;
    MS_BOOL bExclude;
    MS_U16 LvValue;
} AWB_LIGHT_USER;

typedef struct _AWB_CT_CURVE
{
    MS_U16 ColorTemp;
    MS_U16 Rgain;
    MS_U16 Grgain;
    MS_U16 Gbgain;
    MS_U16 Bgain;
} AWB_CT_CURVE;

typedef struct _AWB_LIGHT_RECT
{
    MS_S32 CenterX;
    MS_S32 CenterY;
    MS_S32 Width;
    MS_S32 Height;
} AWB_LIGHT_RECT;

typedef struct
{
    MS_U16 u2LumMax;
    MS_U16 u2LumMin;
} AWB_USER_SETTING;

//ISP awb gain setting
typedef struct
{
    MS_U8 uDither;
    MS_U8 uBeforeNoise;
} AWB_GAIN_CONFIG;

typedef struct AWB_STATIS_BLOCK_
{
    MS_U32 LightSource;
    MS_U32 u4AvgR;
    MS_U32 u4AvgG;
    MS_U32 u4AvgB;
} AWB_STATIS_BLOCK;

typedef struct AWB_LIGHT_COUNT_
{
    MS_U32 u4Count;
    MS_U32 u4Weight;
    MS_U32 u4AvgR;
    MS_U32 u4AvgG;
    MS_U32 u4AvgB;
} AWB_LIGHT_COUNT;

typedef struct AWB_DEFAUT_GAIN_
{
    MS_U32 LvValue;
    MS_U32 Rgain;
    MS_U32 Bgain;
} AWB_DEFAUT_GAIN;

typedef struct AWB_DAYLIGHT_INDEX_
{
    MS_U32 LvValue;
    MS_U32 LightIndex;
} AWB_DAYLIGHT_INDEX;

typedef struct AWB_COMPENSATE_CFG_
{
    MS_U16 u2Threshold;
    MS_U16 u2Ratio;
} AWB_COMPENSATE_CFG;

typedef struct AWB_PURECOLOR_CFG_
{
    MS_U16 u2Enable;
    MS_U16 u2Threshold;
    MS_U16 u2Weight;
    MS_U16 u2GMin;
    MS_U16 u2GMax;
    MS_U16 u2LvMin;
    MS_U16 u2LvMax;
    MS_U16 u2TargetCT1;
    MS_U16 u2TargetCT2;
    MS_U16 u2CTindx;
    MS_U16 u2CTindx2;
    MS_U16 u2Reserve;
} AWB_PURECOLOR_CFG;

typedef struct AWB_GAIN_COMPENSATE_
{
    MS_U32 Rratio;
    MS_U32 Bratio;
} AWB_GAIN_COMPENSATE;

typedef struct AWB_PRE_GAIN_
{
    MS_U32 u4Confidence;
    MS_U32 u4FrameCnt;
    MS_U32 Rgain;
    MS_U32 Bgain;
} AWB_PRE_GAIN;

typedef enum
{
    AWB_DEBUG_AWBInfo     = 1,
    AWB_DEBUG_MultiLS     = 2,
    AWB_DEBUG_AWBParam_1  = 3,
    AWB_DEBUG_AWBParam_2  = 4,
    AWB_DEBUG_TIMING      = 5,
    AWB_DEBUG_IR_CUT      = 6

} AWB_DEBUG;

typedef enum
{
    AWB_DEBUG_SET_DISABLE = 0,
    AWB_DEBUG_SET_ENABLE = 1,
} AWB_DEBUG_SETTING;

typedef enum
{
    AWB_DEBUG_API_OFF = 0,
    AWB_DEBUG_API_ON = 1,
    AWB_DEBUG_API_MWB = 2,
    AWB_DEBUG_API_LIMIT = 3,
    AWB_DEBUG_API_CALIB = 4,
    AWB_DEBUG_API_USER_AREA = 5
} AWB_DEBUG_TEST_MODE;

//////////////////////////////////////
typedef enum AWB_API_STATE
{
    AWB_API_STATE_NORMAL = 0,
    AWB_API_STATE_PAUSE = 1
} AWB_API_STATE;

typedef enum AWB_API_MODE
{
    AWB_API_MODE_AUTO = 0,
    AWB_API_MODE_MANUAL = 1
} AWB_API_MODE;

typedef struct MWB_GAIN_
{
    MS_U16 u2Rgain;      //RW, Multiplier for R  color channel, Range: [0x0, 0x2000]
    MS_U16 u2Grgain;     //RW, Multiplier for Gr color channel, Range: [0x0, 0x2000]
    MS_U16 u2Gbgain;     //RW, Multiplier for Gb color channel, Range: [0x0, 0x2000]
    MS_U16 u2Bgain;      //RW, Multiplier for B  color channel, Range: [0x0, 0x2000]
} MWB_GAIN;

typedef struct _MWB_ATTR_S
{
    MS_U16 u2Rgain;      //RW, Multiplier for R  color channel, Range: [0x0, 0x2000]
    MS_U16 u2Grgain;     //RW, Multiplier for Gr color channel, Range: [0x0, 0x2000]
    MS_U16 u2Gbgain;     //RW, Multiplier for Gb color channel, Range: [0x0, 0x2000]
    MS_U16 u2Bgain;      //RW, Multiplier for B  color channel, Range: [0x0, 0x2000]
} MWB_ATTR_S;

typedef struct _AWB_ATTR_S
{
    MS_U16 u2Speed;                                     //RW, AWB converging speed, Range: [0x1, 0x64]
    MS_U16 u2LvWeightEn;                                //RW, AWB Lv Ct Weight enable
    MS_U16 u2LvWeight[AWB_CT_NUM][AWB_LV_TBL_NUM];      //RW, AWB Lv Ct Weight
    MS_U16 u2PreferRRatioEn;                            //RW, AWB prefer gain enable
    MS_U16 u2PreferRRatio[AWB_CT_NUM][AWB_LV_TBL_NUM];  //RW, AWB prefer R gain
    MS_U16 u2PreferBRatio[AWB_CT_NUM][AWB_LV_TBL_NUM];  //RW, AWB prefer B gain
} AWB_ATTR_S;

typedef struct _AWB_INFO_S
{
    MS_U16 u2Rgain;
    MS_U16 u2Grgain;
    MS_U16 u2Gbgain;
    MS_U16 u2Bgain;
    MS_U16 u2ColorTemp;
} AWB_INFO_S;

typedef enum
{
    AWB_CT_LIMIT_AUTO = 0,
    AWB_CT_LIMIT_MANUAL = 1,
    AWB_CT_LIMIT_NUM = 2,
} AWB_CT_LIMIT_TYPE;

typedef struct _AWB_CT_LIMIT_ATTR_S
{
    MS_U16 u2MaxRgain;           //RW, RGain of High color temperature in manual mode, Range: [0, 8191]
    MS_U16 u2MinRgain;           //RW, BGain of High color temperature in manual mode, Range: [0, 8191]
    MS_U16 u2MaxBgain;            //RW, RGain of Low color temperature in manual mode, Range: [0, 8191]
    MS_U16 u2MinBgain;            //RW, BGain of Low color temperature in manual mode, Range: [0, 8191]
} AWB_CT_LIMIT_ATTR_S;

typedef struct _AWB_WHITE_LT_S
{
    MS_U16 u2WhiteRgain;            //RW, RGain of white Point Location , Range: [256, 4095]
    MS_U16 u2WhiteBgain;            //RW, RGain of white Point Location , Range: [256, 4095]
    MS_U16 u2LvValue;               //RW, Environment LV , value=LV*10, Range: [0, 170]
    MS_U8 uAreaSize;                //RW, Light Area Size , Range: [1, 32]
    MS_BOOL bExclude;               //RW, Include or exclude Uaer light Area, 0: include, 1:exclude
} AWB_WHITE_LT_S;

typedef struct _AWB_EXTRA_LT_S
{
    MS_BOOL bEnable;                //RW, Enable User light Area
    AWB_WHITE_LT_S  pUserArea[AWB_CT_USER_NUM];
} AWB_EXTRA_LT_S;

typedef struct _AWB_CALIB_GLOBAL_S
{
    MS_U16 u2RefColorTemp;          //RW, Color temperature of calibration lightsource , Range: [1000, 10000]
    MS_U16 Rgain;                   //RW, RGain of lightsource , Range: [256, 4095]
    MS_U16 Bgain;                   //RW, RGain of lightsource , Range: [256, 4095]
} AWB_CALIB_GLOBAL_S;

typedef struct _AWB_LT_WEIGHT_S
{
    MS_U16 u2ColorTemp;             //RW, Color temperature of light weight , Range: [1000, 10000]
    MS_U8 uLvValue;                 //RW, Lv Value of light weight , Range: [0, 17]
    MS_U8 uWeight;                  //RW, Weight of lightsource , Range: [0, 255], Base: 100
} AWB_LT_WEIGHT_S;

typedef struct _AWB_CT_STATISTICS_S
{
    MS_U16 u2Width;                                   //RW, Effective range
    MS_U16 u2Height;                                  //RW, Effective range
    MS_U16 u2StatisX[AWB_WIN_HEIGHT][AWB_WIN_WIDTH];  //RW, Color Temperature Curve Domain Statistics X
    MS_U16 u2StatisY[AWB_WIN_HEIGHT][AWB_WIN_WIDTH];  //RW, Color Temperature Curve Domain Statistics Y
} AWB_CT_STATISTICS_S;

typedef struct _AWB_CT_CALIB_S
{
    MS_U16 u2StartIdx;                        //RW, Light area start index, Range: [0, 9]
    MS_U16 u2EndIdx;                          //RW, Light area end index, Range: [0, 9]
    MS_U16 u2CtParams[AWB_CALIB_TOTAL_NUM];   //RW, Color temperature of calibration paramters , Range: [1, 1000]
} AWB_CT_CALIB_S;

// define in calibration_api.h
#if 0
typedef enum
{
    AWB_UNIT_CALIB_GOLDEN_H = 0,
    AWB_UNIT_CALIB_GOLDEN_L = 1,
    AWB_UNIT_CALIB_H = 2,
    AWB_UNIT_CALIB_L = 3,
    AWB_UNIT_CALIB_VERIFY = 4,
    AWB_UNIT_CALIB_NUM = 5,
} AWB_UNIT_CALIB_STATE;
#endif

typedef struct _AWB_UNIT_CALIB_GAIN_S
{
    MS_U16 u2HighRg;        //RW, RGain of lightsource , Range: [64, 4095]
    MS_U16 u2HighBg;        //RW, BGain of lightsource , Range: [64, 4095]
    MS_U16 u2LowRg;         //RW, RGain of lightsource , Range: [64, 4095]
    MS_U16 u2LowBg;         //RW, BGain of lightsource , Range: [64, 4095]
} AWB_UNIT_CALIB_GAIN_S;

typedef struct _AWB_UNIT_CALIB_ATTR_S
{
    MS_U32 u4HighCT;        //RW, Color temperature of calibration lightsource , Range: [1000, 10000]
    MS_U32 u4LowCT;         //RW, Color temperature of calibration lightsource , Range: [1000, 10000]
    MS_U32 u4CaliNum;       //RW, Color temperature of calibration lightsource Number, Range: [1, 2]
    AWB_UNIT_CALIB_GAIN_S sGolden;
    AWB_UNIT_CALIB_GAIN_S sModule;
} AWB_UNIT_CALIB_ATTR_S;

typedef struct _AWB_MULTI_LS_ATTR_S
{
    bool bEnable;         //RW
    u8   uSensitive;      //RW,range:1-10
    u8   uCaliStrength;   //RW,range:0-100
    u16  u2CcmForLow[9];  //RW
    u16  u2CcmForHigh[9]; //RW
    bool bMultiLSDetected;//R
    bool bApiCcmUpdate;   //R
    u8   uFisrtLSInd;     //R
    u8   uSecondLSInd;    //R
    s8   Rratio_Target;   //R
    s8   Bratio_Target;   //R
    s8   Rratio_Current;  //R
    s8   Bratio_Current;  //R
    s8   Rratio_Previous; //R
    s8   Bratio_Previous; //R
} AWB_MULTI_LS_ATTR_S;

//////////////////////////////////////
struct __cam_awb_handle_t;

typedef VOID    (*AWB_TESTPIN)              (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_ProcessCMD)           (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_InitCaliParam)        (struct __cam_awb_handle_t*, MS_BOOL bLock);
typedef MS_S32  (*AWB_SetGain)              (struct __cam_awb_handle_t*, AWB_GAIN awb_gain);
typedef MS_S32  (*AWB_GetGain)              (struct __cam_awb_handle_t*, AWB_GAIN *awb_gain);
typedef MS_S32  (*AWB_SetApiState)          (struct __cam_awb_handle_t*, AWB_API_STATE eAwbApiState);
typedef MS_S32  (*AWB_GetApiState)          (struct __cam_awb_handle_t*, AWB_API_STATE *eAwbApiState);
typedef MS_S32  (*AWB_SetApiMode)           (struct __cam_awb_handle_t*, AWB_API_MODE eAwbApiMode);
typedef MS_S32  (*AWB_GetApiMode)           (struct __cam_awb_handle_t*, AWB_API_MODE *eAwbApiMode);
typedef MS_S32  (*AWB_SetMode)              (struct __cam_awb_handle_t*, AWB_MODE mode);
typedef MS_S32  (*AWB_GetOpMode)            (struct __cam_awb_handle_t*, MS_U16 *OpMode);
typedef MS_S32  (*AWB_SetOpMode)            (struct __cam_awb_handle_t*, AWB_OP_MODE mode);
typedef MS_S32  (*AWB_SetScene)             (struct __cam_awb_handle_t*, AWB_SCENE scene);
typedef MS_S32  (*AWB_SetFastMode)          (struct __cam_awb_handle_t*, MS_BOOL);

typedef MS_U8   (*AWB_WaitAWBStable)        (struct __cam_awb_handle_t*);
typedef MS_U8   (*AWB_IsStable)             (struct __cam_awb_handle_t*);
typedef MS_BOOL (*AWB_isConverged)          (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_Pause)                (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_Resume)               (struct __cam_awb_handle_t*);
typedef MS_BOOL (*AWB_GetLockStatus)        (struct __cam_awb_handle_t*);
typedef MS_BOOL (*AWB_GetLockSupport)       (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_SetConvergeSpeed)     (struct __cam_awb_handle_t*, MS_U16 speed);
typedef MS_S32  (*AWB_GetConvergeSpeed)     (struct __cam_awb_handle_t*, MS_U16 *speed);
typedef MS_S32  (*AWB_GetConvergeThd)       (struct __cam_awb_handle_t*, MS_U8 *threshold);
typedef MS_S32  (*AWB_SetConvergeThd)       (struct __cam_awb_handle_t*, MS_U8 threshold);
typedef MS_S32  (*AWB_SetControlMode)       (struct __cam_awb_handle_t*, MS_U16 mode);
typedef MS_S32  (*AWB_GetControlMode)       (struct __cam_awb_handle_t*, MS_U16 *mode);

typedef MS_S32  (*AWB_CalcSumGain)          (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_Process)              (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_SetCalibrationData)   (struct __cam_awb_handle_t*, MS_U32 *pData, MS_U16 data_length);
typedef MS_S32  (*AWB_GetDebugInfo)         (struct __cam_awb_handle_t*, void *pDbgInfo);
typedef MS_S32  (*AWB_SetDebugInfoByItem)   (struct __cam_awb_handle_t*, void *pDbgBuf, MS_U32 u4Item);
typedef MS_S32  (*AWB_GetDebugInfoByItem)   (struct __cam_awb_handle_t*, void *pDbgBuf, MS_U32 u4Item);
typedef MS_S32  (*AWB_GetParamFromCfg)      (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_SetParamToCfg)        (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_Enable)               (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_Disable)              (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_GetSMState)           (struct __cam_awb_handle_t*);
typedef VOID    (*AWB_GetDebugLevel)        (struct __cam_awb_handle_t*);
typedef VOID    (*AWB_SetDebugParam)        (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_SetCheckingIROff)     (struct __cam_awb_handle_t*, MS_BOOL enable);
typedef MS_S32  (*AWB_SetAllGain)           (struct __cam_awb_handle_t*, MWB_GAIN sAwbGain);
typedef MS_S32  (*AWB_GetAwbAlgType)        (struct __cam_awb_handle_t*, MS_U16 *eAwbAlgType);
typedef MS_S32  (*AWB_SetAwbAlgType)        (struct __cam_awb_handle_t*, MS_U16 eAwbAlgType);
typedef MS_S32  (*AWB_GetAwbAttr)           (struct __cam_awb_handle_t*, AWB_ATTR_S *pAwbAttr);
typedef MS_S32  (*AWB_SetAwbAttr)           (struct __cam_awb_handle_t*, AWB_ATTR_S *sAwbAttr);
typedef MS_S32  (*AWB_GetMwbAttr)           (struct __cam_awb_handle_t*, MWB_ATTR_S *pMwbAttr);
typedef MS_S32  (*AWB_SetMwbAttr)           (struct __cam_awb_handle_t*, MWB_ATTR_S *sMwbAttr);
typedef MS_S32  (*AWB_GetColorTemp)         (struct __cam_awb_handle_t*, MS_U16 *ColorTemp);
typedef MS_S32  (*AWB_GetWBIspGain)         (struct __cam_awb_handle_t*, AWB_ISP_GAIN *IspGain);
typedef MS_S32  (*AWB_GainStrength)         (struct __cam_awb_handle_t*);
typedef MS_S32  (*AWB_GetGainStrength)      (struct __cam_awb_handle_t*, MS_U8 *RGStreh, MS_U8 *BGstreh);
typedef MS_S32  (*AWB_SetGainStrength)      (struct __cam_awb_handle_t*, MS_U8 RGStreh, MS_U8 BGstreh);
typedef MS_S32  (*AWB_GetLightAreaScale)    (struct __cam_awb_handle_t*, MS_U8 *uAreaScale);
typedef MS_S32  (*AWB_SetLightAreaScale)    (struct __cam_awb_handle_t*, MS_U8 uAreaScale);
typedef MS_S32  (*AWB_GetCalibGlobalAttr)   (struct __cam_awb_handle_t*, AWB_CALIB_GLOBAL_S *pCalibAttr);
typedef MS_S32  (*AWB_SetCalibGlobalAttr)   (struct __cam_awb_handle_t*, AWB_CALIB_GLOBAL_S sCalibAttr);
typedef MS_S32  (*AWB_GetUserExtraArea)     (struct __cam_awb_handle_t*, AWB_EXTRA_LT_S *pExtraAttr);
typedef MS_S32  (*AWB_SetUserExtraArea)     (struct __cam_awb_handle_t*, AWB_EXTRA_LT_S pExtraAttr);
typedef MS_S32  (*AWB_GetAwbAlgType)        (struct __cam_awb_handle_t*, MS_U16 *eAwbAlgType);
typedef MS_S32  (*AWB_SetAwbAlgType)        (struct __cam_awb_handle_t*, MS_U16 eAwbAlgType);
typedef MS_S32  (*AWB_GetCtLimit)           (struct __cam_awb_handle_t*, AWB_CT_LIMIT_ATTR_S *sCtLimit);
typedef MS_S32  (*AWB_SetCtLimit)           (struct __cam_awb_handle_t*, AWB_CT_LIMIT_ATTR_S sCtLimit);
typedef MS_S32  (*AWB_GetCtWeight)          (struct __cam_awb_handle_t*, MS_U16 u2ColorTemp, MS_U8 uLvValue, MS_U8 *uWeight);
typedef MS_S32  (*AWB_SetCtWeight)          (struct __cam_awb_handle_t*, MS_U16 u2ColorTemp, MS_U8 uLvValue, MS_U8 uWeight);
typedef MS_S32  (*AWB_GetCTCalibParam)      (struct __cam_awb_handle_t*, AWB_CT_CALIB_S *pAwbCalib);
typedef MS_S32  (*AWB_SetCTCalibParam)      (struct __cam_awb_handle_t*, AWB_CT_CALIB_S *pAwbCalib);
typedef MS_S32  (*AWB_GetUnitCalibGain)     (struct __cam_awb_handle_t*, MS_U16 *Rgain, MS_U16 *Bgain);
typedef MS_S32  (*AWB_DoUnitCalibration)    (struct __cam_awb_handle_t*, AWB_UNIT_CALIB_STATE nCalibState, AWB_UNIT_CALIB_ATTR_S *sCalibData);
typedef MS_S32  (*AWB_ApplyUnitCalibration) (struct __cam_awb_handle_t*, AWB_UNIT_CALIB_ATTR_S *sCalibData);
typedef MS_S32  (*AWB_VerifyUnitCalibration)(struct __cam_awb_handle_t*, AWB_UNIT_CALIB_ATTR_S *sCalibData);
typedef MS_S32  (*AWB_GetCTStatistics)      (struct __cam_awb_handle_t*, MS_U16 *u2Width, MS_U16 *u2Height, MS_U16 *pStatisX, MS_U16 *pStatisY);
typedef MS_S32  (*AWB_GetLvColorTempWeight) (struct __cam_awb_handle_t*, MS_U16 uLvIndex, MS_U16 *pWeight);
typedef MS_S32  (*AWB_SetLvColorTempWeight) (struct __cam_awb_handle_t*, MS_U16 uLvIndex, MS_U16 *pWeight);
typedef MS_S32  (*AWB_GetPreferRRatio)      (struct __cam_awb_handle_t*, MS_U16 uLvIndex, MS_U16 *pRatio);
typedef MS_S32  (*AWB_SetPreferRRatio)      (struct __cam_awb_handle_t*, MS_U16 uLvIndex, MS_U16 *pRatio);
typedef MS_S32  (*AWB_GetPreferBRatio)      (struct __cam_awb_handle_t*, MS_U16 uLvIndex, MS_U16 *pRatio);
typedef MS_S32  (*AWB_SetPreferBRatio)      (struct __cam_awb_handle_t*, MS_U16 uLvIndex, MS_U16 *pRatio);
typedef MS_S32  (*AWB_GetWpWeight)          (struct __cam_awb_handle_t*, MS_U16 *pWeight);
typedef MS_S32  (*AWB_SetWpWeight)          (struct __cam_awb_handle_t*, MS_U16 *pWeight);

typedef struct __cam_awb_handle_t
{
    // user function
    AWB_TESTPIN                 pAWB_TESTPIN;
    AWB_SetApiState             pAWB_SetApiState;
    AWB_GetApiState             pAWB_GetApiState;
    AWB_SetApiMode              pAWB_SetApiMode;
    AWB_GetApiMode              pAWB_GetApiMode;
    AWB_SetMode                 pAWB_SetMode;
    AWB_GetOpMode               pAWB_GetOpMode;
    AWB_SetOpMode               pAWB_SetOpMode;
    AWB_SetScene                pAWB_SetScene;
    AWB_SetFastMode             pAWB_SetFastMode;
    AWB_SetConvergeSpeed        pAWB_SetConvergeSpeed;
    AWB_GetConvergeSpeed        pAWB_GetConvergeSpeed;
    AWB_WaitAWBStable           pAWB_WaitAWBStable;
    AWB_isConverged             pAWB_isConverged;
    AWB_IsStable                pAWB_IsStable;
    AWB_SetControlMode          pAWB_SetControlMode;
    AWB_GetControlMode          pAWB_GetControlMode;
    //Sensor SOC function
    AWB_GetLockStatus           pAWB_GetLockStatus;
    //Sensor SOC function
    AWB_GetLockSupport          pAWB_GetLockSupport;
    AWB_SetCheckingIROff        pAWB_SetCheckingIROff;

    AWB_Pause                   pAWB_Pause;
    AWB_Resume                  pAWB_Resume;
    AWB_Enable                  pAWB_Enable;
    AWB_Disable                 pAWB_Disable;
    AWB_GetSMState              pAWB_GetSMState;
    AWB_Process                 pAWB_Process;
    AWB_CalcSumGain             pAWB_CalcSumGain;

    // system
    AWB_InitCaliParam           pAWB_InitCaliParam;
    AWB_SetGain                 pAWB_SetGain;
    AWB_GetGain                 pAWB_GetGain;

    // calibration
    AWB_SetCalibrationData      pAWB_SetCalibrationData;

    // User
    AWB_GetConvergeThd          pAWB_GetConvergeThd;
    AWB_SetConvergeThd          pAWB_SetConvergeThd;
    AWB_SetAllGain              pAWB_SetAllGain;
    AWB_GetAwbAttr              pAWB_GetAwbAttr;
    AWB_SetAwbAttr              pAWB_SetAwbAttr;
    AWB_GetMwbAttr              pAWB_GetMwbAttr;
    AWB_SetMwbAttr              pAWB_SetMwbAttr;
    AWB_GetColorTemp            pAWB_GetColorTemp;
    AWB_GetGainStrength         pAWB_GetGainStrength;
    AWB_SetGainStrength         pAWB_SetGainStrength;
    AWB_GetWBIspGain            pAWB_GetWBIspGain;
    AWB_GetLightAreaScale       pAWB_GetLightAreaScale;
    AWB_SetLightAreaScale       pAWB_SetLightAreaScale;
    AWB_GetCalibGlobalAttr      pAWB_GetCalibGlobalAttr;
    AWB_SetCalibGlobalAttr      pAWB_SetCalibGlobalAttr;
    AWB_GetUserExtraArea        pAWB_GetUserExtraArea;
    AWB_SetUserExtraArea        pAWB_SetUserExtraArea;
    AWB_GetAwbAlgType           pAWB_GetAwbAlgType;
    AWB_SetAwbAlgType           pAWB_SetAwbAlgType;
    AWB_GetCtLimit              pAWB_GetCtLimit;
    AWB_SetCtLimit              pAWB_SetCtLimit;
    AWB_GetCtWeight             pAWB_GetCtWeight;
    AWB_SetCtWeight             pAWB_SetCtWeight;
    AWB_GetCTCalibParam         pAWB_GetCTCalibParam;
    AWB_SetCTCalibParam         pAWB_SetCTCalibParam;
    AWB_GetUnitCalibGain        pAWB_GetUnitCalibGain;
    AWB_DoUnitCalibration       pAWB_DoUnitCalibration;
    AWB_ApplyUnitCalibration    pAWB_ApplyUnitCalibration;
    AWB_VerifyUnitCalibration   pAWB_VerifyUnitCalibration;
    AWB_GetCTStatistics         pAWB_GetCTStatistics;
    AWB_GetLvColorTempWeight    pAWB_GetLvColorTempWeight;
    AWB_SetLvColorTempWeight    pAWB_SetLvColorTempWeight;
    AWB_GetPreferRRatio         pAWB_GetPreferRRatio;
    AWB_SetPreferRRatio         pAWB_SetPreferRRatio;
    AWB_GetPreferBRatio         pAWB_GetPreferBRatio;
    AWB_SetPreferBRatio         pAWB_SetPreferBRatio;
    AWB_GetWpWeight             pAWB_GetWpWeight;
    AWB_SetWpWeight             pAWB_SetWpWeight;

    //destructor
    MS_U32 (*release)(struct __cam_awb_handle_t* handle);

    // debug
    AWB_GetDebugInfo            pAWB_GetDebugInfo;
    AWB_SetDebugInfoByItem      pAWB_SetDebugInfoByItem;
    AWB_GetDebugInfoByItem      pAWB_GetDebugInfoByItem;
    AWB_GetParamFromCfg         pAWB_GetParamFromCfg;
    AWB_SetParamToCfg           pAWB_SetParamToCfg;
    AWB_GetDebugLevel           pAWB_GetDebugLevel;
    AWB_SetDebugParam           pAWB_SetDebugParam;

    AWB_SM                      eAwbState;
    AWB_PRE_GAIN                asPreGain[AWB_PREGAIN_NUM];
    AWB_RBGAIN                  asLightGain[AWB_GAIN_TYPE_NUM];
    AWB_GAIN                    sCurGain;
    AWB_GAIN                    sApplyGain;
    AWB_GAIN                    sCTGain;
    AWB_ISP_GAIN                sCurIspGain;

    // variable calibration
    MS_U16                      u2CaliLightNum;
    AWB_RBGAIN                  asCaliGain[AWB_CALI_NUM];

    AWB_LIGHT_AREA              *pLightArea;
    AWB_LIGHT_AREA              *pLightAreaHighPrecision;
    AWB_LIGHT_AREA              *pSpecialArea;
    //AWB_DEFAUT_GAIN           *pDefaultGain;
    AWB_RBGAIN                  *pPresetGain;
    //AWB_COMPENSATE_CFG        *pCompCfg;
    //MS_U16                    *pTemperature;
    AWB_CT_CURVE                *pCtCurve;

    MS_U32                      u4SyncFrameCnt;
    MS_U32                      u4FrameCntDiffThd;

    MS_U32                      u4ChkWpWeight[AWB_CT_NUM];
    AWB_LIGHT_COUNT             sLightCount[AWB_CT_NUM];
    AWB_LIGHT_COUNT             sLightCountHighPre[AWB_CT_HIGHPRE_NUM];
    AWB_LIGHT_COUNT             sSpecialCount[AWB_SPECIAL_NUM];
    MS_U32                      u4NoFoundCount;
    MS_U32                      u4TotalCount;
    MS_U8                       uRefWPInd;
    MS_U8                       uLightFirst;
    MS_U8                       uLightSecond;
    MS_U8                       uLightThird;
    MS_U8                       uPreLightFirst;
    MS_U8                       uPreLightSecond;
    MS_U8                       uLightNum;
    MS_U8                       uLightStart;
    MS_U8                       uLightEnd;
    MS_U16                      u2LumMax;
    MS_U16                      u2LumMin;
    MS_U16                      u2CnvgThd;                 //RW, Converge Threshold , Range: [0, 256], Recommended: 64
    MS_U16                      u2CnvgOutThd;              //RW, Converge Threshold , Range: [0, 256], Recommended: 64
    MS_U16                      u2CountThd;
    MS_U16                      u2Speed;
    MS_U32                      u4LvValue;
    MS_U16                      u2SpecialCase;
    MS_U16                      u2SpecialNum;
    MS_U16                      u2IROffYmin;
    MS_U16                      u2IROffRatio;
    MS_U16                      u2IROffCountThd;
    MS_U32                      u4IROffCount;
    MS_U32                      u4IROffTotalCount;
    MS_U16                      u2IROffStableThd;
    MS_U16                      u2IROffStableCnt;
    MS_BOOL                     IsIROff;
    MS_BOOL                     bCheckIROff;
    MS_U16                      u2SubSampleX;
    MS_U16                      u2SubSampleY;
    MS_U16                      u2StatisW;
    MS_U16                      u2StatisH;
    MS_U8                       uMixThirdThd;
    MS_BOOL                     bEnableAvgRGB;
    MS_U16                      u2LowLuxThd;
    MS_U16                      **pLtCoordinate;
    MS_U16                      u2LtCoordXMax;
    MS_U16                      u2LtCoordYMax;

    MS_U8                       uGainStableCount;
    MS_U8                       uRefWPStableCount;

    AWB_USER_SETTING            UserSetting;
    AWB_GAIN_CONFIG             sGainConfig;

    AWB_OP_MODE                 eAwbOpMode;
    AWB_MODE                    eAwbMode;         //Sensor relation
    AWB_ALG_MODE                eAwbAlgMode;
    AWB_SCENE                   eAwbSceneMode;    //Sensor relation
    AWB_CONTROL_MODE            eAwbCtrlMode;
    MS_U16                      u2PreGainIdx;
    MS_U8                       IsStable;
    MS_BOOL                     bFastMode;
    MS_U8                       uDbg_AWB_Enable;
    MS_U8                       uDbg_MWB_Enable;
    MS_U16                      u2Dbg_MWB_Rgain;
    MS_U16                      u2Dbg_MWB_Bgain;
    MS_U8                       uDbgLevel;

    MS_U8                       uDbgApi;
    MS_U8                       uDbgPrefer;
    MS_U8                       uRGStrength;
    MS_U8                       uBGStrength;

    //For Fast AWB
    MS_BOOL                     bDoInitFrameCnt;
    MS_U32                      u4InitFrameCnt;
    MS_U8                       uDoFastAWBThr;    // If current and initial frame count diff is samller than this thr, do fast AWB

    //User
    MS_BOOL                     bEnableUserArea;
    AWB_LIGHT_COUNT             sUserCount[AWB_CT_USER_NUM];
    AWB_WHITE_LT_S              sUserArea[AWB_CT_USER_NUM];
    MS_U8                       uUserLightFirst;
    AWB_API_STATE               eAwbApiState;
    AWB_API_MODE                eAwbApiMode;
    AWB_ATTR_S                  sAwbAttr;
    MWB_ATTR_S                  sMwbAttr;
    AWB_EXTRA_LT_S              sExtraAttr;
    AWB_CT_LIMIT_ATTR_S         sCtLimitAttr;
    AWB_CALIB_GLOBAL_S          sCalibGlobalAttr;
    AWB_MULTI_LS_ATTR_S         sMultiLSAttr;
    MS_U16                      u2ColorTemp;
    MS_U16                      u2ColorTempUnit;
    MS_U16                      u2AreaXMax;
    MS_U16                      u2AreaXMin;
    MS_U16                      u2AreaYMax;
    MS_U16                      u2AreaYMin;
    MS_U16                      u2AreaSizeMax;
    MS_U8                       uAreaScaleMax;
    MS_U8                       uAreaScale;                //RW, Expand light area , Range: [0, 16], Default: 0
    AWB_CT_CALIB_S              sCtCalibAttr;
    MS_BOOL                     bForceUpdate;
    MS_BOOL                     bWpWeightEnable;

    MS_U16                      u2StatisBlkValidX;
    MS_U16                      u2StatisBlkValidY;
    MS_U16                      u2StatisBlkValidLowLuxX;
    MS_U16                      u2StatisBlkValidLowLuxY;

    MS_U32                      u4ProcessFrameCount;
    MS_U32                      u4IntervalFrameCount;
    /* =================== internal variables =================== */
    ISP_DBGBUF_HANDLE           isp_dbg_buf_handle;

    AwbInput_t                  *AwbInputParameter;
    AwbOutput_t                 *AwbOutputParameter;
    /* ========================================================== */

} cam_awb_handle_t;

VOID    pAWB_InitFuncPtr(cam_awb_handle_t* handle);
MS_U32  pAWB_InitParameters(cam_awb_handle_t* handle);

#ifdef __cplusplus
}
#endif
#endif //__CAMERA_AUTOWHITEBALANCE_H__
