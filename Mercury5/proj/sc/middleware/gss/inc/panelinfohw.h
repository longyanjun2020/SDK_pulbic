/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright VMTS S.A. (c) 2001
*/

#if 1
#include "panelinfohw_pub.h"
#else

#ifndef _PANEL_INFO_HW_H_
#define _PANEL_INFO_HW_H_

#include "vm_types.ht"
#include "gss_cisi_drv.h"
#include "msgdidef.h"

//#include "dev_lcd.ho"

#if defined (__LCM_QVGA_DRV__)
#define MAIN_PANEL_WIDTH                240
#define MAIN_PANEL_HEIGHT               320
#elif defined (__LCM_WQVGA_240_400_DRV__)
#define MAIN_PANEL_WIDTH                240
#define MAIN_PANEL_HEIGHT               400
#elif defined (__LCM_WQVGA_240_432_DRV__)
#define MAIN_PANEL_WIDTH                240
#define MAIN_PANEL_HEIGHT               432
#elif defined (__LCM_QCIF_PLUS_DRV__)
#define MAIN_PANEL_WIDTH                176
#define MAIN_PANEL_HEIGHT               220
#elif defined (__LCM_QQVGA_DRV__)
#define MAIN_PANEL_WIDTH                128
#define MAIN_PANEL_HEIGHT               160
#elif defined(__LCM_HVGA_DRV__)
#define MAIN_PANEL_WIDTH                320
#define MAIN_PANEL_HEIGHT               480
#elif defined(__LCM_LANDSCAPE_QVGA_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
#define MAIN_PANEL_WIDTH                240
#define MAIN_PANEL_HEIGHT               320
#else
#define MAIN_PANEL_WIDTH                320
#define MAIN_PANEL_HEIGHT               240
#endif
#elif defined(__LCM_LANDSCAPE_HVGA_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
#define MAIN_PANEL_WIDTH                320
#define MAIN_PANEL_HEIGHT               480
#else
#define MAIN_PANEL_WIDTH                480
#define MAIN_PANEL_HEIGHT               320
#endif
#elif defined(__LCM_LANDSCAPE_QCIF_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
#define MAIN_PANEL_WIDTH                176
#define MAIN_PANEL_HEIGHT               220
#else
#define MAIN_PANEL_WIDTH                220
#define MAIN_PANEL_HEIGHT               176
#endif
#else
#define MAIN_PANEL_WIDTH                176
#define MAIN_PANEL_HEIGHT               220
#endif
#define MAIN_PANEL_BITS_PER_PIXEL       16
#define MAIN_PANEL_COLORFORMAT          MSCOLORFORMAT_RGB16_565
#define MAIN_PANEL_TRANSPARENT_COLOR    0x00000000
/*
#define MAIN_PANEL_MAX_CONTRAST         CONTRAST_LEVEL_15
#define MAIN_PANEL_MIN_CONTRAST         CONTRAST_LEVEL_1
#define MAIN_PANEL_DEF_CONTRAST         ((MAIN_PANEL_MIN_CONTRAST+MAIN_PANEL_MAX_CONTRAST)/2)

#if _ENABLE_BACKLIGHT_IN_GDI_
  #define MAIN_PANEL_MAX_BACKLIGHT        BACKLIGHT_LEVEL_15
  #define MAIN_PANEL_MIN_BACKLIGHT        BACKLIGHT_LEVEL_1
  #define MAIN_PANEL_DEF_BACKLIGHT        ((MAIN_PANEL_MIN_BACKLIGHT+MAIN_PANEL_MAX_BACKLIGHT)/2)
#endif//_ENABLE_BACKLIGHT_IN_GDI_
*/
// LCD reg definitions
#define LCD_REG00_START_OSCILLATION     0x0000
#define LCD_REG01_DRIVER_OUTPUT_CONTROL 0x0001
#define LCD_REG02_DRIVE_WAV_CONTROL     0x0002
#define LCD_REG03_ENTRY_MODE            0x0003
#define LCD_REG04_RESIZE_CONTROL1       0x0004
#define LCD_REG05_RESIZE_CONTROL2       0x0005
#define LCD_REG07_DISPLAY_CONTROL1      0x0007
#define LCD_REG08_DISPLAY_CONTROL2      0x0008
#define LCD_REG09_DISPLAY_CONTROL3      0x0009
#define LCD_REG0B_DISPLAY_CONTROL4      0x000b
#define LCD_REG0C_EXT_DISPLAY_CTRL1     0x000c
#define LCD_REG0D_FRAME_CYCLE_CONTROL   0x000d
#define LCD_REG0E_EXT_DISPLAY_CTRL2     0x000e
#define LCD_REG0F_EXT_DISPLAY_CTRL3     0x000f
#define LCD_REG10_GATE_DRV_CTRL1        0x0010
#define LCD_REG11_GATE_DRV_CTRL2        0x0011
#define LCD_REG12_GATE_DRV_CTRL3        0x0012
#define LCD_REG13_GATE_DRV_CTRL4        0x0013
#define LCD_REG15_GATE_DRV_CTRL5        0x0015
#define LCD_REG16_GATE_DRV_CTRL6        0x0016
#define LCD_REG17_GATE_DRV_CTRL7        0x0017
#define LCD_REG18_GATE_DRV_CTRL8        0x0018
#define LCD_REG19_GATE_DRV_CTRL9        0x0019
#define LCD_REG1B_GATE_DRV_CTRL10       0x001B

#define LCD_REG100_POWER_CONTROL1       0x0100
#define LCD_REG110_POWER_SUPPLY_CTRL1   0x0110
#define LCD_REG111_POWER_SUPPLY_CTRL2   0x0111

#define LCD_REG200_H_RAM_ADDR_POS       0x0200
#define LCD_REG201_V_RAM_ADDR_POS       0x0201
#define LCD_REG202_GRAM_WRITE           0x0202
#define LCD_REG202_GRAM_READ            0x0202
#define LCD_REG203_WRITE_DATA_MSK1      0x0203
#define LCD_REG204_WRITE_DATA_MSK2      0x0204

#define LCD_REG210_WINDOW_HOR_START     0x0210
#define LCD_REG211_WINDOW_HOR_END       0x0211
#define LCD_REG212_WINDOW_VER_START     0x0212
#define LCD_REG213_WINDOW_VER_END       0x0213

#define LCD_REG300_CONTROL1             0x00300
#define LCD_REG301_CONTROL2             0x00301
#define LCD_REG302_CONTROL3             0x00302
#define LCD_REG303_CONTROL4             0x00303
#define LCD_REG304_CONTROL5             0x00304
#define LCD_REG305_CONTROL6             0x00305
#define LCD_REG306_CONTROL7             0x00306
#define LCD_REG307_CONTROL8             0x00307
#define LCD_REG308_CONTROL9             0x00308
#define LCD_REG309_CONTROL10            0x00309

#define LCD_REG400_LINE_NUMBER          0x00400
#define LCD_REG401_SCREEN_CONTROL       0x00401
#define LCD_REG402_BASE_PICT_RAM_START  0x00402
#define LCD_REG403_BASE_PICT_RAM_END    0x00403
#define LCD_REG404_VERT_SCROLL          0x00404
#define LCD_REG405_BASE_PICT_1RAM       0x00405
#define LCD_REG406_BASE_PICT_2RAM       0x00406


#ifdef _PANEL_INFO_HW_BODY_
    void PrePanelInitHW(void);
    void PostPanelInitHW(void);
		u32 UpdateScreenHW(u32 PanelID, PMSBLT_SRCCOPY pParam);
    s32 UpdateScreenMLHW(u32 uPanelID, PMSUPDATE pParam);

  #if _ENABLE_BACKLIGHT_IN_GDI_
    s8  SetBacklightHW(u32 PanelId, u8 uLevel);
  #endif

#else  //_PANEL_INFO_HW_BODY_
    extern void PrePanelInitHW(void);
    extern void PostPanelInitHW(void);
		extern u32 UpdateScreenHW(u32 PanelID, PMSBLT_SRCCOPY pParam);
		extern s32 UpdateScreenMLHW(u32 uPanelID, PMSUPDATE pParam);

  #if _ENABLE_BACKLIGHT_IN_GDI_
    extern s8  SetBacklightHW(u32 PanelId, u8 uLevel);
  #endif
#endif //_PANEL_INFO_HW_BODY_

#endif //_PANEL_INFO_HW_H_
#endif

