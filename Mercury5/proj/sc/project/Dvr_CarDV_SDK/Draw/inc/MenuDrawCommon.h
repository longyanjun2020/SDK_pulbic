//==============================================================================
//
//  File        : MenuDrawCommon.h
//  Description : INCLUDE File for the Menu Draw function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MENUDRAWCOMMON_H_
#define _MENUDRAWCOMMON_H_

#include "ahc_common.h"
#include "MenuCommon.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define MAIN_DISPLAY_BUFFER     (0)  // warning msg layer id

#define OVL_BUFFER_INDEX        MENU_OSD_FIRST_ID//(16) // osd layer id
#define OVL_BUFFER_INDEX1       MENU_OSD_END_ID//(17)

#define OVL_DISPLAY_BUFFER      (OVL_BUFFER_INDEX)

#if (TVOUT_ENABLE)
#define TV_UI_OSD_ID            (17)
#define TV_MENU_OSD_ID          (18)
#define TV_MENU_OSD2_ID         (19)
#endif

#if (HDMI_ENABLE)
#define HDMI_UI_OSD_ID          (16)
#define HDMI_UI_OSD2_ID         (17)
#define HDMI_MENU_OSD_ID        (18)
#define HDMI_MENU_OSD2_ID       (19)
#endif

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void        OSDDraw_SetOvlDrawBuffer( UINT8 ulID );
void        OSDDraw_GetOvlDrawBuffer( UINT8* ulID );
void        OSDDraw_GetLastOvlDrawBuffer( UINT8* ulID);
void        OSDDraw_ClearOvlDrawBuffer( UINT8 ulID );
void        OSDDraw_ClearMainDrawBufferAll(void);
void        OSDDraw_ClearOvlDrawOvlBufferAll(void);
void        OSDDraw_GetDisplaySize(UINT8 bID, UINT16 *pw, UINT16* ph);
void        OSDDraw_EnterMenuDrawing( UINT8* pbID0, UINT8* pbID1 );
void        OSDDraw_ExitMenuDrawing( UINT8* pbID0, UINT8* pbID1 );
void        OSDDraw_EnterDrawing( UINT8* pbID0, UINT8* pbID1 );
void        OSDDraw_ExitDrawing( UINT8* pbID0, UINT8* pbID1 );

void        OSDDraw_ClearDotMatrixPanel(UINT8 ulID);
AHC_BOOL    OSDDraw_SetAlphaBlending( UINT8 ulID, AHC_BOOL bEnable );
AHC_BOOL    OSDDraw_SetSemiTransparent( UINT8 ulID, UINT8 ulEnable, UINT8 ulOsdSemiType, UINT8 ulSemiWeight );
AHC_BOOL    OSDDraw_EnableSemiTransparent(UINT8 id, AHC_BOOL enable);
void        OSD_Draw_Icon(const GUI_BITMAP Bmp, RECT Draw , UINT16 uiDisplayID);
void        OSD_Draw_IconXY(UINT16 ulID, const GUI_BITMAP Bmp, UINT16 x, UINT16 y);

UINT8       NumOfDigit(UINT32 num);
UINT8*      GetFileNameAddr(char* filepath);

void        OSDDraw_ResetBoundingRC(void);
GUI_RECT*   OSDDraw_ScanBoundingRc(const RECT* rc);
GUI_RECT*   OSDDraw_ScanTouchBoundingRc(const SMENUTOUCHBUTTON* touch, UINT16 num);
void        OSDDraw_ClearTouchButtons(UINT16 uwDisplayID, SMENUTOUCHBUTTON* touchButtons, UINT16 num);
AHC_BOOL    SwitchDrawOSDIDFunc(void);

#if (TVOUT_ENABLE)
UINT16      TVFunc_GetUImodeOsdID(void);
UINT16      TVFunc_GetMenuOsdID(void);
UINT16      TVFunc_GetMenuOsd2ID(void);
#endif
#if (HDMI_ENABLE)
UINT16      HDMIFunc_GetUImodeOsdID(void);
UINT16      HDMIFunc_GetUImodeOsd2ID(void);
UINT16      HDMIFunc_GetMenuOsdID(void);
UINT16      HDMIFunc_GetMenuOsd2ID(void);
#endif

#endif
