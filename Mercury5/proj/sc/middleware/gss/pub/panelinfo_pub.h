/*****************************************************************************\
    This software is protected by Copyright and the information
    contained herein is confidential. Distribution, reproduction
    as well as exploitation and transmission of its contents is
    not allowed except if expressly permitted. Infringments
    result in damage claims.
    Copyright : Morning Star 2006/11 ~ 2010

  File    : panelinfo.h

  Historical :
--------------------------------------------------------------------------
   Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
 16.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
/*
#include "vm_types.ht"
#include "gss_lcdc_drv.h"
*/
#include "functypes_pub.h" /* CR_1500: file name shall be in lower case */
//#include "panelinfohw_pub.h"
#include "dispbasicgrap_pub.h"

#ifndef _PANEL_INFOMATION_H_
#define _PANEL_INFOMATION_H_

//===============================================
//    Constant
//===============================================

#define PANEL_TYPE_RGB		    0x001
#define PANEL_TYPE_PARALLEL     0x002
#define PANEL_TYPE_SERIAL       0x004

#ifdef __DUAL_LCD__
  #define   TOTAL_PANELS    2
#else
  #define   TOTAL_PANELS    1
#endif//__DUAL_LCD__

/*#################################################################*\
                    hardware depeneded setion
\*#################################################################*/
//#define MAIN_PANEL_WIDTH                (GetScreenWidth(MAIN_PANEL))
//#define MAIN_PANEL_HEIGHT               (GetScreenHeight(MAIN_PANEL))

//#define SUB_PANEL_WIDTH                (GetScreenWidth(SUB_PANEL))
//#define SUB_PANEL_HEIGHT               (GetScreenHeight(SUB_PANEL))

#if 0
#ifndef MAIN_PANEL_WIDTH
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
#elif defined(__LCM_LANDSCAPE_QCIF_DRV__)
#if (defined(__LCM_ROTATE_DRV__)||defined(__LCM_ROTATE_MDL__) ) && !defined(__SDK_SIMULATION__)
#define MAIN_PANEL_WIDTH                176
#define MAIN_PANEL_HEIGHT               220
#else
#define MAIN_PANEL_WIDTH                220
#define MAIN_PANEL_HEIGHT               176
#endif
#elif defined (__LCM_QQVGA_DRV__)
#define MAIN_PANEL_WIDTH                128
#define MAIN_PANEL_HEIGHT               160
#else
  #define MAIN_PANEL_WIDTH                176
  #define MAIN_PANEL_HEIGHT               220
#endif
  #define MAIN_PANEL_BITS_PER_PIXEL       16
  #define MAIN_PANEL_COLORFORMAT          MSCOLORFORMAT_RGB16_565
  #define MAIN_PANEL_TRANSPARENT_COLOR    0x00000000
#endif
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

#ifdef __DUAL_LCD__
  #ifndef SUB_PANEL_WIDTH
    #define SUB_PANEL_WIDTH               128
    #define SUB_PANEL_HEIGHT              160
    #define SUB_PANEL_BITS_PER_PIXEL      16
    #define SUB_PANEL_COLORFORMAT         MSCOLORFORMAT_RGB16_565
    #define SUB_PANEL_TRANSPARENT_COLOR   0x00000000
  #endif
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
#endif //__DUAL_LCD__



#define PANEL_ATTRIBUTE_WIDTH           0x10000000
#define PANEL_ATTRIBUTE_HEIGHT          0x20000000
#define PANEL_ATTRIBUTE_COLORFORMAT     0x40000000
#define PANEL_ATTRIBUTE_COLORDEPTH      0x80000000
#define PANEL_ATTRIBUTE_PIXELCLK        0x01000000
#define PANEL_ATTRIBUTE_TYPE            0x02000000
#define PANEL_ATTRIBUTE_MAX_CONTRAST    0x04000000
#define PANEL_ATTRIBUTE_MIN_CONTRAST    0x08000000
#define PANEL_ATTRIBUTE_CUR_CONTRAST    0x00100000
#define PANEL_ATTRIBUTE_DEF_CONTRAST    0x00200000

#if _ENABLE_BACKLIGHT_IN_GDI_
  #define PANEL_ATTRIBUTE_MAX_BACKLIGHT   0x00400000
  #define PANEL_ATTRIBUTE_MIN_BACKLIGHT   0x00800000
  #define PANEL_ATTRIBUTE_CUR_BACKLIGHT   0x00010000
  #define PANEL_ATTRIBUTE_DEF_BACKLIGHT   0x00020000
#endif//_ENABLE_BACKLIGHT_IN_GDI_
#define PANEL_ATTRIBUTE_TRANPARENTCOLOR 0x00040000
#endif

//===============================================
//    Structures
//===============================================
//typedef void (*fnSetDisplayWindow)(u16 , u16 , u16 , u16 , bool );


typedef struct _st_panel_information_
{
    u32     capability;
	u16     width;
	u16     height;
	//u8      colordepth;
    //u32     colorformat;
    //u32     pixelclk;
    //u32     type;     //RGB, paralle or serial
    //u32     maxContrast;
    //u32     minContrast;
    //u32     curContrast;
    //u32     maxPowerState;
    //u32     minPowerState;
    //u32     curPowerState;
//#if _ENABLE_BACKLIGHT_IN_GDI_
    //u32     maxBacklight;
    //u32     minBacklight;
    //u32     curBacklight;
//#endif//_ENABLE_BACKLIGHT_IN_GDI_
    u16     transparentColor;
} PANELINFO, *PPANELINFO;

typedef struct _st_ms_panel_operation_
{
    //fnGetAttribution    GetPanelAttribution;
    //fnGetDWByIndex      GetScreenCaps;
    fnGetDWByIndex      GetScreenDotPerCentimeter;
    fnGetDWByIndex      GetScreenWidth;
    fnGetDWByIndex      GetScreenHeight;
    fnGetDWByIndex      GetScreenColorDepth;
    //fnGetDWByIndex      GetScreenColorFormat;
    //fnGetDWByIndex      GetScreenSize;
    fnGetWordByIndex    GetTransparencyColor;
    fnUpdateScreen      UpdateScreen;
    //fnUpdateScreen      UpdateScreenExt;
    fnUpdateScreenML    UpdateScreenML;
    fnUpdateScreen      UpdateScreenMdl;
    fnEnableMdlScreenLayer EnableMdlScreenLayer;
    fnSetMdlScreenCtrl SetMdlScreenCtrl;
    fnIsMdlScreenLayerEnable IsMdlScreenLayerEnable;
    //fnSetLevel          SetContrast;
    //fnGetLevel          GetContrast;
}PANELACTION;//, *PANELACTION;


//===============================================
//    functions
//===============================================
#ifdef _PANEL_INFOMATION_BODY_
    u32  GetScreenDPM(u32);
    //s32  GetPanelAttributionSW(PATTRIBUTION pQuery );
    //u32  GetScreenCapsSW(u32);
    u32  GetScreenWidth(u32);
    u32  GetScreenHeight(u32);
    u32  GetScreenColorDepth(u32);
    //u32  GetScreenSizeSW(u32 nPnaelID);
    //u32  GetScreenColorFormatSW(u32);
    u16  GetTransparencyColor(u32);

    s32  UpdateScreen(u32 PanelID, PMSUPDATELAYER pParam);
    //s32  UpdateScreenExt(u32 PanelID, PMSBLT_SRCCOPY pParam);
    s32  UpdateScreenML(u32 uPanelID, PMSUPDATE pParam);

    //void SetDisplayWindowSW(u16 x_pos, u16 y_pos, u16 width, u16 height, bool auto_transfer);
    u32  PrePanelInit(void);
    u32  PostPanelInit(void);
    //s8   SetContrastSW(u32 PanelID, u8  uLevel);
    //u8   GetContrastSW(u32 PanelID, u32 uAttri);
    s32  UpdateScreenMdl(u32 PanelID, PMSUPDATELAYER pParam);
    u32  EnableMdlScreenLayer(u32 PanelID, bool bEnable);
    u32  SetMdlScreenCtrl(u32 PanelID, bool bCtrlByMdl);
    bool  IsMdlScreenLayerEnable(u32 PanelID);

#else  //_PANEL_INFOMATION_BODY_

    //extern s32  GetPanelAttributionSW(PATTRIBUTION pQuery );
    //extern u32  GetScreenCapsSW(u32);
    extern u32  GetScreenDPM(u32);
    extern u32  GetScreenWidth(u32);
    extern u32  GetScreenHeight(u32);
    extern u32  GetScreenColorDepth(u32);
    //extern u32  GetScreenSizeSW(u32 nPnaelID);
    //extern u32  GetScreenColorFormatSW(u32);
    extern u16  GetTransparencyColor(u32);

    extern s32  UpdateScreen (u32 PanelID, PMSUPDATELAYER pParam);
    //extern s32  UpdateScreenExt (u32 PanelID, PMSBLT_SRCCOPY pParam);
    extern s32  UpdateScreenML(u32 uPanelID, PMSUPDATE pParam);

    //extern void SetDisplayWindowSW(u16 x_pos, u16 y_pos, u16 width, u16 height, bool auto_transfer);
    extern u32  PrePanelInit(void);
    extern u32  PostPanelInit(void);
    //extern s8   SetContrastSW(u32 PanelID, u8  uLevel);
    //extern u8   GetContrastSW(u32 PanelID, u32 uAttri);
    extern s32  UpdateScreenMdl(u32 PanelID, PMSUPDATELAYER pParam);
    extern u32  EnableMdlScreenLayer(u32 PanelID, bool bEnable);
    extern u32  SetMdlScreenCtrl(u32 PanelID, bool bCtrlByMdl);
    extern bool  IsMdlScreenLayerEnable(u32 PanelID);

#endif //_PANEL_INFOMATION_BODY_

#endif //_PANEL_INFOMATION_H_
