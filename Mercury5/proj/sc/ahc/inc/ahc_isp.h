//==============================================================================
//
//  File        : ahc_isp.h
//  Description : INCLUDE File for the AHC ISP function porting.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_ISP_H_
#define _AHC_ISP_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum {
    AHC_AE_ISO_AUTO                 = 0,
    AHC_AE_ISO_100                  = 1,
    AHC_AE_ISO_200                  = 2,
    AHC_AE_ISO_400                  = 3,
    AHC_AE_ISO_800                  = 4,
    AHC_AE_ISO_1600                 = 5,
    AHC_AE_ISO_3200                 = 6,
    //
    AHC_AE_ISO_MAX
} AHC_AE_ISO;

typedef enum {
    AHC_AE_FLICKER_OFF              = 0,
    AHC_AE_FLICKER_AUTO             = 1,
    AHC_AE_FLICKER_60HZ             = 2,
    AHC_AE_FLICKER_50HZ             = 3
} AHC_AE_FLICKER;

typedef enum {
    AHC_AE_METERING_AVERAGE         = 0,
    AHC_AE_METERING_CENTER          = 1,
    AHC_AE_METERING_SPOT            = 2,
    AHC_AE_METERING_MATRIX          = 3,
    AHC_AE_METERING_LAND            = 4,
    AHC_AE_METERING_NUM
} AHC_AE_METERING;

typedef enum {
    AHC_AE_EV_BIAS_M200             =  0,   // -2.00
    AHC_AE_EV_BIAS_M166             =  1,   // -1.66
    AHC_AE_EV_BIAS_M133             =  2,   // -1.33
    AHC_AE_EV_BIAS_M100             =  3,   // -1.00
    AHC_AE_EV_BIAS_M066             =  4,   // -0.66
    AHC_AE_EV_BIAS_M033             =  5,   // -0.33
    AHC_AE_EV_BIAS_0000             =  6,   // +0.00
    AHC_AE_EV_BIAS_P033             =  7,   // +0.33
    AHC_AE_EV_BIAS_P066             =  8,   // +0.66
    AHC_AE_EV_BIAS_P100             =  9,   // +1.00
    AHC_AE_EV_BIAS_P133             = 10,   // +1.33
    AHC_AE_EV_BIAS_P166             = 11,   // +1.66
    AHC_AE_EV_BIAS_P200             = 12    // +2.00
} AHC_AE_EV_BIAS;

typedef enum {
    AHC_SCENE_AUTO                  = 0,    // scene mode
    AHC_SCENE_PORTRAIT              = 1,    // scene mode
    AHC_SCENE_LANDSCAPE             = 2,    // scene mode
    AHC_SCENE_SPORTS                = 3,    // scene mode
    AHC_SCENE_SUNSET                = 4,    // scene mode
    AHC_SCENE_DUSK                  = 5,    // scene mode
    AHC_SCENE_DAWN                  = 6,    // scene mode
    AHC_SCENE_NIGHT_SHOT            = 7,    // scene mode
    AHC_SCENE_AGAINST_LIGHT         = 8,    // scene mode
    AHC_SCENE_TEXT                  = 9,    // scene mode
    AHC_SCENE_MANUAL                = 10,   // scene mode
    AHC_SCENE_INDOOR                = 11,   // scene mode
    AHC_SCENE_SNOW                  = 12,   // scene mode
    AHC_SCENE_FALL                  = 13,   // scene mode
    AHC_SCENE_WAVE                  = 14,   // scene mode
    AHC_SCENE_FIREWORKS             = 15,   // scene mode
    AHC_SCENE_SHOW_WIN              = 16,   // scene mode
    AHC_SCENE_CANDLE                = 17,   // scene mode
    AHC_SCENE_NONE                  = 18,   // camera mode
    AHC_SCENE_MANUAL0               = 19,   // scene mode
    AHC_SCENE_MANUAL1               = 20,   // scene mode
    AHC_SCENE_MANUAL2               = 21,   // scene mode
    AHC_SCENE_MANUAL3               = 22,   // scene mode
    AHC_SCENE_MANUAL4               = 23,   // scene mode
    AHC_SCENE_MANUAL5               = 24,   // scene mode
    AHC_SCENE_MANUAL6               = 25,   // scene mode
    AHC_SCENE_MANUAL7               = 26,   // scene mode
    AHC_SCENE_MANUAL8               = 27,   // scene mode
    AHC_SCENE_MANUAL9               = 28,   // scene mode
    AHC_SCENE_NIGHT_PORTLAIT        = 29    // scene mode
} AHC_SCENE;

typedef enum {
    AHC_AF_MODE_AUTO                = 0,
    AHC_AF_MODE_MANUAL              = 1,
    AHC_AF_MODE_MACRO               = 2,
    AHC_AF_MODE_FULL                = 3,
    AHC_AF_MODE_PAN                 = 4,
    AHC_AF_MODE_NULL                = 5
} AHC_AF_MODE;

typedef enum {
    AHC_AWB_MODE_BYPASS                 = 0,
    AHC_AWB_MODE_AUTO                   = 1,
    AHC_AWB_MODE_DAYLIGHT               = 2,
    AHC_AWB_MODE_CLOUDY                 = 3,
    AHC_AWB_MODE_FLUORESCENT_WHITE      = 4,
    AHC_AWB_MODE_FLUORESCENT_NATURAL    = 5,
    AHC_AWB_MODE_FLUORESCENT_DAYLIGHT   = 6,
    AHC_AWB_MODE_INCANDESCENT           = 7,
    AHC_AWB_MODE_FLASH                  = 8,
    AHC_AWB_MODE_ONEPUSH                = 9,
    AHC_AWB_MODE_NUM
} AHC_AWB_MODE;

typedef enum {
    AHC_IMAGE_EFFECT_NORMAL         = 0,
    AHC_IMAGE_EFFECT_GREY           = 1,
    AHC_IMAGE_EFFECT_SEPIA          = 2,
    AHC_IMAGE_EFFECT_NEGATIVE       = 3,
    AHC_IMAGE_EFFECT_ANTIQUE        = 4,
    AHC_IMAGE_EFFECT_WATERCOLOR     = 5,
    AHC_IMAGE_EFFECT_PORTRAIT       = 6,
    AHC_IMAGE_EFFECT_LANDSCAPE      = 7,
    AHC_IMAGE_EFFECT_SUNSET         = 8,
    AHC_IMAGE_EFFECT_DUSK           = 9,
    AHC_IMAGE_EFFECT_DAWN           = 10,
    AHC_IMAGE_EFFECT_RED            = 11,
    AHC_IMAGE_EFFECT_GREEN          = 12,
    AHC_IMAGE_EFFECT_BLUE           = 13,
    AHC_IMAGE_EFFECT_YELLOW         = 14,
    AHC_IMAGE_EFFECT_EMBOSS         = 15,
    AHC_IMAGE_EFFECT_OIL            = 16,
    AHC_IMAGE_EFFECT_BW             = 17,
    AHC_IMAGE_EFFECT_SKETCH         = 18,
    AHC_IMAGE_EFFECT_CRAYONE        = 19,
    AHC_IMAGE_EFFECT_WHITEBOARD     = 20,
    AHC_IMAGE_EFFECT_BLACKBOARD     = 21,
    AHC_IMAGE_EFFECT_VIVID          = 22,
    AHC_IMAGE_EFFECT_PALE           = 23,
    AHC_IMAGE_EFFECT_NUM
} AHC_IMAGE_EFFECT;

typedef enum {
    AHC_AE_WDR_DSB              = 0,
    AHC_AE_WDR_ENB              = 1
} AHC_AE_WDR;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL        AHC_SetAwbFastMode(UINT8 ubSnrSel, UINT8 byEnable);
AHC_BOOL        AHC_SetAeFastMode(UINT8 ubSnrSel, UINT8 byEnable);
AHC_BOOL        AHC_SetAeIsoMode(UINT8 ubSnrSel, AHC_AE_ISO byMode);
AHC_BOOL        AHC_SetAeFlickerMode(UINT8 ubSnrSel, AHC_AE_FLICKER byMode);
AHC_BOOL        AHC_SetAeMeteringMode(UINT8 ubSnrSel, AHC_AE_METERING byMode);
AHC_BOOL        AHC_SetAeEvBiasMode(UINT8 ubSnrSel,AHC_AE_EV_BIAS byMode);
AHC_BOOL        AHC_SetAeSceneMode(AHC_SCENE byMode);
AHC_BOOL        AHC_SetAfMode(AHC_AF_MODE byMode);
AHC_BOOL        AHC_SetAwbMode(UINT8 ubSnrSel, AHC_AWB_MODE byMode);
AHC_BOOL        AHC_SetImageEffect(UINT8 ubSnrSel, AHC_IMAGE_EFFECT byMode);
AHC_BOOL        AHC_SetColorSaturateLevel(UINT8 ubSnrSel, INT16 iLvl);
AHC_BOOL        AHC_SetColorSharpnessLevel(UINT8 ubSnrSel, INT16 iLvl);
AHC_BOOL        AHC_SetColorGammaLevel(UINT8 ubSnrSel, INT16 iLvl);
AHC_BOOL        AHC_SetColorContrastLevel(UINT8 ubSnrSel, INT16 iLvl);

void            AHC_PostInitISP(void);
void            AHC_FirstInitISPCB( void );
void            AHC_FirstInitSensorCB( void );

AHC_BOOL        AHC_SetAeWDRMode(UINT8 ubSnrSel,AHC_AE_WDR byMode);
AHC_BOOL        AHC_SetColorSaturateCenter(INT16 byLev);

AHC_BOOL        AHC_GetISP_LS_CS_CalibData(UINT8 *buf, UINT16 bufsize, UINT16 color_temp, UINT16 index);
AHC_BOOL        AHC_GetISP_AWB_CalibData(UINT8 *buf, UINT8 sensorid);
AHC_BOOL        AHC_ReadISP_TmpData(void);
AHC_BOOL        AHC_ReadISP_AWBData(void);
UINT16          AHC_GetISPTmpDataSize(void);

#endif // _AHC_ISP_H_
