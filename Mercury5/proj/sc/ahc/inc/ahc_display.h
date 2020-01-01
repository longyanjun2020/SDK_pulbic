/**
 @file ahc_display.h
 @brief Header File for the AHC display API.
 @author 
 @version 1.0
*/

#ifndef _AHC_DISPLAY_H_
#define _AHC_DISPLAY_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_common.h"
//#include "lcd_common.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define TV_NTSC_POWEROFF_IMG_W          (720)
#define TV_NTSC_POWEROFF_IMG_H          (480)
#define TV_PAL_POWEROFF_IMG_W           (720)
#define TV_PAL_POWEROFF_IMG_H           (576)

#define HDMI_480P_POWEROFF_IMG_W        (720)
#define HDMI_480P_POWEROFF_IMG_H        (480)
#define HDMI_720P_POWEROFF_IMG_W        (1280)
#define HDMI_720P_POWEROFF_IMG_H        (720)
#define HDMI_1080I_POWEROFF_IMG_W       (1920)
#define HDMI_1080I_POWEROFF_IMG_H       (1080)
#define HDMI_1080P_POWEROFF_IMG_W       (1920)
#define HDMI_1080P_POWEROFF_IMG_H       (1080)

/*===========================================================================
 * Enum define
 *===========================================================================*/ 
 
typedef enum _AHC_DISPLAY_MODE {
    DISPLAY_MODE_DISABLE = 0,
    DISPLAY_MODE_PIP_DISABLE,
    DISPLAY_MODE_PIP_ENABLE,
    DISPLAY_MODE_OSD_DISABLE,
    DISPLAY_MODE_OSD_ENABLE,
    DISPLAY_MODE_ENABLE
} AHC_DISPLAY_MODE;

typedef enum _AHC_DISPLAY_OUT_FORMAT{
    DISP_OUT_TV_NTSC = 0,
    DISP_OUT_TV_PAL,
    DISP_OUT_HDMI,
    DISP_OUT_LCD,
    DISP_OUT_CCIR656
} AHC_DISPLAY_OUT_FORMAT;

typedef enum _AHC_DISPLAY_FLAG{
    DISP_FLAG_WIN_KEEP_ASPRATIO = 0,
    DISP_FLAG_WIN_16X9,
    DISP_FLAG_WIN_4X3,
    DISP_FLAG_WIN_3X2,
    DISP_FLAG_WIN_FIT2SCREEN
} AHC_DISPLAY_FLAG;

typedef enum _AHC_DISPLAY_SYSMODE {
    DISPLAY_SYSMODE_STILLCAPTURE_PRM = 0,
    DISPLAY_SYSMODE_STILLCAPTURE_UVC,
    DISPLAY_SYSMODE_STILLCAPTURE_SCD,
    DISPLAY_SYSMODE_STILLPLAYBACK,
    DISPLAY_SYSMODE_VIDEOCAPTURE_PRM,
    DISPLAY_SYSMODE_VIDEOCAPTURE_UVC,
    DISPLAY_SYSMODE_VIDEOCAPTURE_SCD,
    DISPLAY_SYSMODE_VIDEOPLAYBACK
} AHC_DISPLAY_SYSMODE;

typedef enum _AHC_DISPLAY_OUTPUTPANEL {
    AHC_DISPLAY_NONE = 0,                   ///< Choose no output device
    AHC_DISPLAY_MAIN_LCD,                   ///< Choose MAIN LCD for output
    AHC_DISPLAY_SUB_LCD,                    ///< Choose SUB LCD for output
    AHC_DISPLAY_NTSC_TV,                    ///< Choose NTSC TV for output
    AHC_DISPLAY_PAL_TV,                     ///< Choose PAL TV for output
    AHC_DISPLAY_HDMI,                       ///< Choose HDMI for output
    AHC_DISPLAY_CCIR                        ///< Choose CCIR for output
} AHC_DISPLAY_OUTPUTPANEL;

// Sync with MMP_HDMI_OUTPUT_MODE
typedef enum _AHC_DISPLAY_HDMIOUTPUTMODE
{
    AHC_DISPLAY_HDMIOUTPUT_UNSUPPORT        = 0,
    AHC_DISPLAY_HDMIOUTPUT_USERDEF          = 0x7FFFFFFF,
    AHC_DISPLAY_HDMIOUTPUT_640X480P         = 0x00000001,
    AHC_DISPLAY_HDMIOUTPUT_720X480P         = 0x00000002,
    AHC_DISPLAY_HDMIOUTPUT_720X576P         = 0x00000004,
    AHC_DISPLAY_HDMIOUTPUT_1280X720P        = 0x00000008,
    AHC_DISPLAY_HDMIOUTPUT_1280X720P_50FPS  = 0x00000010,
    AHC_DISPLAY_HDMIOUTPUT_1280X720P_100FPS = 0x00000011,
    AHC_DISPLAY_HDMIOUTPUT_1280X720P_120FPS = 0x00000012,
    AHC_DISPLAY_HDMIOUTPUT_1920X1080P       = 0x00000020,
    AHC_DISPLAY_HDMIOUTPUT_1920X1080P_30FPS = 0x00000040,
    AHC_DISPLAY_HDMIOUTPUT_1920X1080P_50FPS = 0x00000050,
    AHC_DISPLAY_HDMIOUTPUT_1920X1080I       = 0x00000080
} AHC_DISPLAY_HDMIOUTPUTMODE;

typedef enum _AHC_DISPLAY_DUPLICATE {
    AHC_DISPLAY_DUPLICATE_1X = 0,
    AHC_DISPLAY_DUPLICATE_2X,
    AHC_DISPLAY_DUPLICATE_3X,
    AHC_DISPLAY_DUPLICATE_4X,
    AHC_DISPLAY_DUPLICATE_5X,
    AHC_DISPLAY_DUPLICATE_6X,
    AHC_DISPLAY_DUPLICATE_HALF,
    AHC_DISPLAY_DUPLICATE_4X_1X	    // AHC Only
} AHC_DISPLAY_DUPLICATE;

typedef enum _AHC_LCD_DIRECTION {
    AHC_LCD_UPLEFT_DOWNRIGHT = 0,
    AHC_LCD_DOWNLEFT_UPRIGHT,
    AHC_LCD_UPRIGHT_DOWNLEFT,
    AHC_LCD_DOWNRIGHT_UPLEFT
} AHC_LCD_DIRECTION;

typedef enum _AHC_LCD_STATUS {
    AHC_LCD_NORMAL = 0,
    AHC_LCD_REVERSE,
    AHC_LCD_NOFLIP
} AHC_LCD_STATUS;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
 
/** @addtogroup AHC_DISPLAY
@{
*/

UINT16  AIHC_GetWinDupMode(void);
void    AHC_SetCurrentDisplayEx(MMP_DISPLAY_OUTPUT_SEL kind);

AHC_BOOL AHC_SwitchDisplayOutputDevLCD(void);
#if (TVOUT_ENABLE)
AHC_BOOL AHC_SwitchDisplayOutputDevTVout(void);
#endif
#if (TVOUT_ENABLE)
AHC_BOOL AHC_SwitchDisplayOutputDevHDMI(void);
#endif
AHC_BOOL AHC_SetHDMIOutputMode(AHC_DISPLAY_HDMIOUTPUTMODE mode);
AHC_BOOL AHC_GetHDMIOutputMode(AHC_DISPLAY_HDMIOUTPUTMODE *mode);
AHC_BOOL AHC_GetHdmiDisplayWidthHeight(UINT16 *uwDisplayWidth, UINT16 *uwDisplayHeight);
AHC_BOOL AHC_GetNtscTvDisplayWidthHeight(UINT16 *uwDisplayWidth, UINT16 *uwDisplayHeight);
AHC_BOOL AHC_GetPalTvDisplayWidthHeight(UINT16 *uwDisplayWidth, UINT16 *uwDisplayHeight);
AHC_BOOL AHC_GetCCIR656DisplayWidthHeight(UINT16 *uwDisplayW, UINT16 *uwDisplayH);//#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)
AHC_BOOL AHC_Display_GetWidthHdight(UINT16 *uwDisplayW, UINT16 *uwDisplayH);
AHC_BOOL AHC_SetDisplayMode(UINT8 byMode);
AHC_BOOL AHC_SetDisplayOutputDev(AHC_DISPLAY_OUT_FORMAT byMode, AHC_DISPLAY_DUPLICATE byOSDDuplicate);
AHC_BOOL AHC_GetDisplayOutputDev(AHC_DISPLAY_OUTPUTPANEL *pDevice);
AHC_BOOL AHC_SetDisplayWindow(UINT8  bySysMode, AHC_BOOL bUse, AHC_BOOL bMirror, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwWidth, UINT16 uwHeight);
AHC_BOOL AHC_GetDisplayWindowAttr(UINT16 *uwStartX, UINT16 *uwStartY, UINT16 *uwWidth, UINT16 *uwHeight);

void AHC_HDMISendEventEnable(AHC_BOOL Enable);
AHC_BOOL AHC_CanSendHDMIEvent(void); 
AHC_BOOL AHC_IsHdmiConnect(void);
AHC_BOOL AHC_IsTVConnect(void);
AHC_BOOL AHC_IsTVConnectEx(void);

AHC_BOOL AHC_EnableWaitIcon(AHC_BOOL EnWaitIcon);
AHC_BOOL AHC_GetWaitIconState(void); 
AHC_BOOL AHC_DrawWaitIcon(void);

AHC_BOOL AHC_ResetChargingID(void);
AHC_BOOL AHC_SetChargingID(UINT8 ubID);
UINT8    AHC_GetChargingID(void);
AHC_BOOL AHC_EnableChargingIcon(AHC_BOOL EnChargingIcon); 
AHC_BOOL AHC_GetChargingIconState(void);
AHC_BOOL AHC_DrawBatteryIcon_HDMI(UINT8 ubID, UINT8 ubIconID, AHC_BOOL bFlag);
AHC_BOOL AHC_DrawBatteryIcon_TV(UINT8 ubID, UINT8 ubIconID, AHC_BOOL bFlag);
AHC_BOOL AHC_DrawBatteryIcon(UINT8 ubID, UINT8 ubIconID, AHC_BOOL bFlag);
AHC_BOOL AHC_DrawChargingIcon(void);
AHC_BOOL AHC_DrawChargingIcon_UsingTimer(UINT8 bID0);
AHC_BOOL AIHC_Display_SetTVGamma(MMP_DISPLAY_TV_GAMMA DSPY_TVGamma);
AHC_BOOL AIHC_Display_GetTVGamma(MMP_DISPLAY_TV_GAMMA *DSPY_TVGamma);
AHC_BOOL AHC_DrawPowerLowIcon(void);

//LCD Function
void AHC_LCD_SetBrightness(UINT8 brightness);
void AHC_LCD_SetContrast(UINT8 Contrast);
void AHC_LCD_SetContrast_R(UINT8 Contrast);
void AHC_LCD_SetBrightness_R(UINT8 brightness);
void AHC_LCD_SetContrast_B(UINT8 Contrast);
void AHC_LCD_SetBrightness_B(UINT8 brightness);
void AHC_LCD_Direction(AHC_LCD_DIRECTION dir);
void AHC_LCD_Write_Reg(UINT32 reg, UINT8 value);
void AHC_LCD_GetStatus(UINT8 *status);

void AHC_Display_AdjustContrast(UINT16 usPercent);
UINT8 AHC_Display_GetContrastValue(void);
void AHC_Display_AdjustBrightness(UINT16 usPercent);
UINT8 AHC_Display_GetBriValue(void);
void AHC_Display_AdjustSaturation(UINT16 usPercent);
void AHC_Display_AdjustColorTemp(INT16 sIndex);

#if (!OSD_SHOW_BATTERY_STATUS)||(!OSD_SHOW_BATLOW_WARNING)
#define CHARGE_ICON_ENABLE(bEn)
#else
#define CHARGE_ICON_ENABLE(bEn)             \
    do {                                    \
        if(AHC_TRUE == AHC_Charger_GetStatus()) \
            AHC_EnableChargingIcon(bEn);    \
    } while (0);

/// @}
#endif

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
#define LCD_ATTR_DISP_W RTNA_LCD_GetAttr()->usPanelH
#define LCD_ATTR_DISP_H RTNA_LCD_GetAttr()->usPanelW
#else
#define LCD_ATTR_DISP_W RTNA_LCD_GetAttr()->usPanelW
#define LCD_ATTR_DISP_H RTNA_LCD_GetAttr()->usPanelH
#endif

#endif //_AHC_DISPLAY_H_
