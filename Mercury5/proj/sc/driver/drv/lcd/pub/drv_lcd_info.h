/****************************************************************************\
  @file     lcd_drv_table.h
  @brief    header file of LCD driver
  @date     2007/10/31
  @version  1.00
  @author
  @warning

--------------------------------------------------------------------------
  Historical :
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
----------+---------+------+-----------------------------------------------
\****************************************************************************/
#ifndef __DRV_LCD_INFO_H__
#define __DRV_LCD_INFO_H__

/*#################################################################*\
                    hardware depeneded setion
\*#################################################################*/

//#ifndef MAIN_PANEL_WIDTH
#if defined (__LCM_QVGA_DRV__)
  #define MAIN_PANEL_WIDTH                240
  #define MAIN_PANEL_HEIGHT               320
#elif defined(__LCM_WQVGA_240_400_DRV__)
  #define MAIN_PANEL_WIDTH                240
  #define MAIN_PANEL_HEIGHT               400
#elif defined(__LCM_WQVGA_240_432_DRV__)
  #define MAIN_PANEL_WIDTH                240
  #define MAIN_PANEL_HEIGHT               432
#elif defined(__LCM_HVGA_DRV__)
  #define MAIN_PANEL_WIDTH               320
  #define MAIN_PANEL_HEIGHT               480
#elif defined(__LCM_WVGA_DRV__)
  #define MAIN_PANEL_WIDTH               480
  #define MAIN_PANEL_HEIGHT               800
#elif defined(__LCM_LANDSCAPE_QVGA_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
  #define MAIN_PANEL_WIDTH               240
  #define MAIN_PANEL_HEIGHT               320
#else
  #define MAIN_PANEL_WIDTH               320
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
#elif defined(__LCM_LANDSCAPE_WVGA_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
#define MAIN_PANEL_WIDTH                480
#define MAIN_PANEL_HEIGHT               800
#else
#define MAIN_PANEL_WIDTH                800
#define MAIN_PANEL_HEIGHT               480
#endif
#elif defined(__LCM_LANDSCAPE_QCIF_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
#define MAIN_PANEL_WIDTH                176
#define MAIN_PANEL_HEIGHT               220
#else
#define MAIN_PANEL_WIDTH                220
#define MAIN_PANEL_HEIGHT               176
#endif
#elif defined(__LCM_LANDSCAPE_WQVGA_240_400_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
#define MAIN_PANEL_WIDTH                240
#define MAIN_PANEL_HEIGHT               400
#else
#define MAIN_PANEL_WIDTH                400
#define MAIN_PANEL_HEIGHT               240
#endif
#elif defined (__LCM_QQVGA_DRV__)
#define MAIN_PANEL_WIDTH                128
#define MAIN_PANEL_HEIGHT               160
#else
  #define MAIN_PANEL_WIDTH                176
  #define MAIN_PANEL_HEIGHT               220
#endif
  //#define MAIN_PANEL_BITS_PER_PIXEL       16
  //#define MAIN_PANEL_COLORFORMAT          MSCOLORFORMAT_RGB16_565
  //#define MAIN_PANEL_TRANSPARENT_COLOR    0x00000000
//#endif

#if 0
#ifndef MAIN_PANEL_MAX_CONTRAST
  #define MAIN_PANEL_MAX_CONTRAST         CONTRAST_LEVEL_6
  #define MAIN_PANEL_MIN_CONTRAST         CONTRAST_LEVEL_0
  #define MAIN_PANEL_DEF_CONTRAST         ((MAIN_PANEL_MIN_CONTRAST+MAIN_PANEL_MAX_CONTRAST)/2)
#endif
#ifndef MAIN_PANEL_MAX_POWERSTATE
  #define MAIN_PANEL_MAX_POWERSTATE       POWER_LEVEL_6
  #define MAIN_PANEL_MIN_POWERSTATE       POWER_LEVEL_0
  #define MAIN_PANEL_DEF_POWERSTATE       ((MAIN_PANEL_MIN_POWERSTATE+MAIN_PANEL_MAX_POWERSTATE)/2)
#endif
#if _ENABLE_BACKLIGHT_IN_GDI_
  #ifndef MAIN_PANEL_MAX_BACKLIGHT
    #define MAIN_PANEL_MAX_BACKLIGHT        BACKLIGHT_LEVEL_6
    #define MAIN_PANEL_MIN_BACKLIGHT        BACKLIGHT_LEVEL_0
    #define MAIN_PANEL_DEF_BACKLIGHT        ((MAIN_PANEL_MIN_BACKLIGHT+MAIN_PANEL_MAX_BACKLIGHT)/2)
  #endif
#endif//_ENABLE_BACKLIGHT_IN_GDI_
#endif

#ifdef __DUAL_LCD__
  #ifndef SUB_PANEL_WIDTH
    #define SUB_PANEL_WIDTH               128
    #define SUB_PANEL_HEIGHT              160
    #define SUB_PANEL_BITS_PER_PIXEL      16
    #define SUB_PANEL_COLORFORMAT         MSCOLORFORMAT_RGB16_565
    #define SUB_PANEL_TRANSPARENT_COLOR   0x00000000
  #endif

#if 0
  #ifndef SUB_PANEL_MAX_CONTRAST
    #define SUB_PANEL_MAX_CONTRAST         CONTRAST_LEVEL_6
    #define SUB_PANEL_MIN_CONTRAST         CONTRAST_LEVEL_0
    #define SUB_PANEL_DEF_CONTRAST         ((SUB_PANEL_MIN_CONTRAST+SUB_PANEL_MAX_CONTRAST)/2)
  #endif
  #ifndef SUB_PANEL_MAX_POWERSTATE
    #define SUB_PANEL_MAX_POWERSTATE       POWER_LEVEL_6
    #define SUB_PANEL_MIN_POWERSTATE       POWER_LEVEL_0
    #define SUB_PANEL_DEF_POWERSTATE       ((SUB_PANEL_MIN_POWERSTATE+SUB_PANEL_MAX_POWERSTATE)/2)
  #endif
  #if _ENABLE_BACKLIGHT_IN_GDI_
    #ifndef SUB_PANEL_MAX_BACKLIGHT
      #define SUB_PANEL_MAX_BACKLIGHT        BACKLIGHT_LEVEL_6
      #define SUB_PANEL_MIN_BACKLIGHT        BACKLIGHT_LEVEL_0
      #define SUB_PANEL_DEF_BACKLIGHT        ((SUB_PANEL_MIN_BACKLIGHT+SUB_PANEL_MAX_BACKLIGHT)/2)
    #endif
  #endif
#endif

#endif //__DUAL_LCD__





#endif
