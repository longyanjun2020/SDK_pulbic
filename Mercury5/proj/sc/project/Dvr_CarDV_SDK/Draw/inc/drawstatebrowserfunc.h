
//==============================================================================
//
//  File        : drawstatebrowserfunc.h
//  Description : INCLUDE File for the DrawStateVideoFunc function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#ifndef _DRAWSTATEBROWSERFUNC_H_
#define _DRAWSTATEBROWSERFUNC_H_

/*===========================================================================
 * Structure define
 *===========================================================================*/ 
#if (TVOUT_ENABLE) || (HDMI_ENABLE)
typedef struct {
    UINT16  guwBrowserCommonOffset;
    UINT16  guwBrowserRectUpLeftX;
    UINT16  guwBrowserRectUpLeftY;
    UINT16  guwBrowserRectLowRightX;
    UINT16  guwBrowserRectLowRightY;

    UINT16 guwBrowserOffsetPos1;
    UINT16 guwBrowserOffsetPos2;
    UINT16 guwBrowserDecY1;
    UINT16 guwBrowserDecY2;

    UINT16 guwBrowserLineStartX;
    UINT16 guwBrowserLineStartY;
    UINT16 guwBrowserLineEndX;
    UINT16 guwBrowserLineEndY;

    UINT16 guwBrowserIconX;
    UINT16 guwBrowserIconY;
    UINT16 guwBrowserIconOffsetX;
    UINT16 guwBrowserIconOffsetY;
    UINT8	gubBrowserMagSize;
    UINT8	gubBrowserBitmapMagSize;
} UI_DARW_BROWSER_PARAMETERS;
#endif

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

typedef void (*DRAW_BROWSER_INIT_HANDLER)(void);
typedef void (*DRAW_BROWSER_STATE_PAGE_HANDLER)(void);
typedef void (*DRAW_BROWSER_UPDATE_HANDLER)(UINT32 ubEvent);

void DrawBrowser_SwitchMode_Lcd(UINT8 ulID, OP_MODE_SETTING OpMode);
#if (HDMI_ENABLE)
void DrawBrowser_SwitchMode_Hdmi(UINT8 ulID, OP_MODE_SETTING OpMode);
#endif
#if (TVOUT_ENABLE)
void DrawBrowser_SwitchMode_Tv(UINT8 ulID, OP_MODE_SETTING OpMode);
#endif

void DrawStateBrowserInit_Lcd(void);
#if (HDMI_ENABLE)
void DrawStateBrowserInit_Hdmi(void);
#endif
#if (TVOUT_ENABLE)
void DrawStateBrowserInit_Tv(void);
#endif

void DrawStateBrowserSwitch_Lcd(void);
#if (HDMI_ENABLE)
void DrawStateBrowserSwitch_Hdmi(void);
#endif
#if (TVOUT_ENABLE)
void DrawStateBrowserSwitch_Tv(void);
#endif

void DrawBrowserStatePageUpdate_Lcd(void);
#if (HDMI_ENABLE)
void DrawBrowserStatePageUpdate_Hdmi(void);
#endif
#if (TVOUT_ENABLE)
void DrawBrowserStatePageUpdate_Tv(void);
#endif

void DrawStateLCDBrowserUpdate(UINT32 ubEvent);
#if (HDMI_ENABLE)
void DrawStateHdmiBrowserUpdate(UINT32 ulEvent);
#endif
#if (TVOUT_ENABLE)
void DrawStateTVBrowserUpdate(UINT32 ulEvent);
#endif

void DrawStateBrowserUpdate( UINT32 ubEvent);
void DrawBrowser_GetPageInfo(UINT16 *CurrPage, UINT16 *TotalPage);
void DrawBrowserStatePageUpdate(void);
void DrawBrowserStateSDMMC_In(void);
void DrawBrowserStateSDMMC_Out(void);

void DrawBrowser_NameInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawBrowser_DateInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawBrowser_TotalTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawBrowserStatePlaybackRearCam( AHC_BOOL bEnable );
void DrawBrowser_ResolutionInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawHdmiBrowser_NameDateInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);

void DrawBrowserStateFunctionSelectLCD(void);
#if (HDMI_ENABLE)
void DrawBrowserStateFunctionSelectHDMI(void);
#endif
#if (TVOUT_ENABLE)
void DrawBrowserStateFunctionSelectTv(void);
#endif

#endif   // _DRAWSTATEBROWSERFUNC_H_ 


