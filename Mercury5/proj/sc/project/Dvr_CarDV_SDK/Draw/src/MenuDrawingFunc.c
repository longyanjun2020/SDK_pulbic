/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_utility.h"
#include "ahc_macro.h"
#include "ahc_parameter.h"
#include "ahc_general.h"
#include "ahc_os.h"
#include "ahc_menu.h"
#include "ahc_display.h"
#include "ahc_version.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "IconDefine.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "MenuSetting.h"
#include "MenuDrawingFunc.h"
#include "MenuStateMenu.h"
#include "MenuDrawCommon.h"
#include "DrawStateMenuSetting.h"
#include "drawstatetvfunc.h"
#include "drawstatehdmifunc.h"
#include "ShowOSDFunc.h"
#include "statehdmifunc.h"
#include "statetvfunc.h"
#include "drawstatehdmifunc.h"
#include "drawstatetvfunc.h"
#include "ui_drawgeneral.h"
#include "stdio.h"
#include "lib_retina.h"
#include "MenuTouchButton.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define ICON_UP_WIDTH               (44)
#define TV_HDMI_DISP_BUF_WIDTH       320
#define TV_HDMI_DISP_BUF_HEIGHT      240

static UINT16   DispBufWidth = 0;
static UINT16   DispBufHeight = 0;
static UINT16   usShiftStringRight = 20;

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern AHC_BOOL AHC_Charger_GetStatus(void);

/*===========================================================================
 * Global variable
 *===========================================================================*/

static GUI_POINT    m_PointU[]          = { {  0, 0}, {-7,  10}, {7,  10} };
static GUI_POINT    m_PointD[]          = { {  0, 0}, {-7, -10}, {7, -10} };
static GUI_POINT    m_PointL[]          = { {  0, 0}, {10,  -7}, {10,  7} };
static GUI_POINT    m_PointR[]          = { {  0, 0}, {-10, -7}, {-10, 7} };
GUI_POINT*          m_PointDir[]        = {&m_PointU[0], &m_PointD[0], &m_PointL[0], &m_PointR[0]};


MENU_ATTR           m_MainMenuAttr;
MENU_ATTR           m_SubPageMenuAttr;
SIDEMENU_ATTR       m_SubIconTextMenuAttr;

UINT8               m_ubSubPageType     = SUBMENU_SUBPAGE ;
UINT32              m_ulSubItemNum      = SUB_MENU_PAGE_ITEM;
GUI_COLOR           m_SubTextClr        = MENU_TEXT_COLOR;
GUI_COLOR           m_SubLineClr        = MENU_LINE_COLOR;
GUI_COLOR           m_SubFocusClr       = MENU_FOCUS_COLOR;
UINT32              m_ulR2SepX          = 47;
UINT32              m_ulPenSize         = 2;


#if defined(FONT_LARGE)
PSMENUSTRUCT LongStringMenu[] = {
                NULL
            };

BAR_SET vBarSet[] = {
            {   &BMICON_SUBBAR_WHITE,
                &BMICON_SUBBAR_WHITE_DEFAULT,
                &BMICON_SUBBAR_YELLOW,
                &BMICON_SUBBAR_YELLOW_DEFAULT },
            {   &BMICON_SUBBAR_WHITE,
                &BMICON_SUBBAR_WHITE_DEFAULT,
                &BMICON_SUBBAR_YELLOW,
                &BMICON_SUBBAR_YELLOW_DEFAULT },
            {   &BMICON_SMALLBAR_WHITE,
                NULL,
                &BMICON_SMALLBAR_YELLOW,
                NULL }
};

#else   // FONT_LARGE

extern SMENUSTRUCT sSubProtect;
extern SMENUSTRUCT sSubDelete;
extern SMENUSTRUCT sSubProtectAll;
extern SMENUSTRUCT sSubUnProtectAll;
extern SMENUSTRUCT sSubDateTimeFormat;
extern SMENUSTRUCT sSubMovieMode;

PSMENUSTRUCT LongStringMenu[] = {
                &sSubProtect,
                &sSubDelete,
                &sSubProtectAll,
                &sSubUnProtectAll,
                &sSubDateTimeFormat,
                &sSubMovieMode,
                NULL
            };

BAR_SET vBarSet[] = {
            {   &BMICON_SUBBAR_WHITE,
                &BMICON_SUBBAR_WHITE_DEFAULT,
                &BMICON_SUBBAR_YELLOW,
                &BMICON_SUBBAR_YELLOW_DEFAULT },
            {   &BMICON_MENUBAR_WHITE,
                &BMICON_MENUBAR_WHITE_DEFAULT,
                &BMICON_MENUBAR_YELLOW,
                &BMICON_MENUBAR_YELLOW_DEFAULT },
            {   &BMICON_SMALLBAR_WHITE,
                NULL,
                &BMICON_SMALLBAR_YELLOW,
                NULL }
};

#endif  // FONT_LARGE

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern UINT16           m_ulVMDShotNum[];
extern UINT16           m_ulTimeLapseTime[];
extern UINT16           m_ulVolume[];
extern AHC_OS_SEMID     m_WMSGSemID;
extern AHC_BOOL         m_ubAtMenuTab;
extern UINT8            ubModeDrawStyle;
extern AHC_OSD_INSTANCE *m_OSD[];

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ________Common_Function_______(){ruturn;} //dummy
#endif

AHC_BOOL MenuDraw_GetMainMenuPageItem(UINT16 uwDispID, GUI_BITMAP barID, UINT32 *PageItemNum, UINT32 *ItemInterval)
{
    *PageItemNum = (AHC_GET_ATTR_OSD_H(uwDispID) + OSD_MENU_ITEM_INTERVAL -40-40)/(OSD_MENU_ITEM_INTERVAL+barID.YSize);
    *ItemInterval = (AHC_GET_ATTR_OSD_H(uwDispID) - 40 - 40)/(*PageItemNum);

    return 0;
}

void MenuDrawSetMenuAttribute( UINT32    MenuType,  UINT32    PageItemNum,
                               GUI_COLOR R1BkClr,   GUI_COLOR R2BkClr,
                               GUI_COLOR R3BkClr,   GUI_COLOR TextClr,      GUI_COLOR LineClr,
                               GUI_COLOR FocusClr,  UINT32    PenSize,      UINT32    R2SepX)
{
}

void MenuDrawSetIconTextSubAttribute(   UINT32    MenuType,    UINT32    PageType, UINT32    PageItemNum,
                                        GUI_COLOR L1BkClr,     GUI_COLOR L2BkClr,  GUI_COLOR TextClr,
                                        GUI_COLOR LineClr,     GUI_COLOR FocusClr, UINT32    PenSize)
{
}

void MenuDrawDirection(UINT16 uwDispID, UINT8 dir, UINT16 x, UINT16 y, GUI_COLOR FillClr)
{
}

void MenuDrawTab(UINT16 uwDispID, UINT16 x, UINT16 y, AHC_BOOL bFill, GUI_COLOR FillClr, GUI_COLOR LineClr)
{
}

void MenuDrawGridLine(UINT16 uwDispID, UINT16 x0, UINT16 x1, UINT16 y0, UINT16 iOffset,
                      UINT8 ubLineNum, UINT32 ulLineSize, GUI_COLOR LineClr)
{
}

void MenuDrawClearUnusedGrid(UINT16 uwDispID, PSMENUSTRUCT pMenu)
{
}

void MenuDrawClearRegion(UINT16 uwDispID, MENU_ATTR attr, UINT32 ulRegionNum)
{
}

void MenuDrawResetRegionSize(void)
{
}

void MenuDrawItemPosBar(UINT16 uwDispID, UINT32 item, MENU_ATTR attr, AHC_BOOL bClear)
{
}

void MenuDrawNaviOK(UINT16 uwDispID)
{
    RECT tempRECT = POS_MENU_EXIT;

    OSD_Draw_Icon(bmIcon_OK, tempRECT, uwDispID);
}

void MenuDrawPageInfo(UINT16 uwDispID, int uiCurPage, int uiTotalPage)
{
    #if defined(FONT_LARGE)
    AHC_OSDSetFont(uwDispID, &GUI_Font16B_1);
    AHC_OSDSetPenSize(uwDispID, 6);
    AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);
    AHC_OSDSetBkColor(uwDispID, OSD_COLOR_DARKGRAY);

    AHC_OSDDrawLine(uwDispID,
                    0, 0,
                    OSD_MENU_UP_Y, OSD_MENU_DOWN_Y + OSD_MENU_DOWN_W);
    AHC_OSDSetColor(uwDispID, OSD_COLOR_RED);
    AHC_OSDDrawLine(uwDispID,
                    0, 0,
                    OSD_MENU_UP_Y + ((OSD_MENU_DOWN_Y + OSD_MENU_DOWN_W) - OSD_MENU_UP_Y) * (uiCurPage - 1) / uiTotalPage,
                    OSD_MENU_UP_Y + ((OSD_MENU_DOWN_Y + OSD_MENU_DOWN_W) - OSD_MENU_UP_Y) * uiCurPage / uiTotalPage);
    #else   // FONT_LARGE
    UINT32 x, y;

    x = POS_MENU_PAGEINFO_X;
    y = POS_MENU_PAGEINFO_Y;

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        x += usShiftStringRight/2;
    }

    AHC_OSDSetFont(uwDispID, &GUI_Font16B_1);
    AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);
    AHC_OSDSetBkColor(uwDispID, OSD_COLOR_BACKGROUND);

    AHC_OSDDrawDec(uwDispID, uiCurPage,     x,    y, 1);
    AHC_OSDDrawText(uwDispID, (UINT8*)"/",  x+10, y, strlen("/"));
    AHC_OSDDrawDec(uwDispID, uiTotalPage,   x+18, y, 1 );
    #endif  // FONT_LARGE
}

void MenuDraw_UIMode(UINT16 uwDispID)
{
//    if(AHC_IsHdmiConnect())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_UI_MODE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else if(AHC_IsTVConnectEx())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_UI_MODE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else
    {
        UIDrawEx(uwDispID, VIDEO_GUI_UI_MODE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
    }   
}

void MenuDraw_ClearMediaType(UINT16 uwDispID)
{
//    if(HDMIFunc_IsInMenu())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else if(TVFunc_IsInMenu())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else
    {
        UIDrawEx(uwDispID, VIDEO_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
    }   
}

void MenuDraw_MediaType(UINT16 uwDispID)
{
//    if(AHC_IsHdmiConnect())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_SD_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else if(AHC_IsTVConnectEx())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else
    {
        UIDrawEx(uwDispID, VIDEO_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
    }   
}

void MenuDraw_SD_Status(void)
{
#ifndef CFG_DRAW_IGNORE_SD_STAUS //may be defined in config_xxx.h

    UINT8  bID0 = 0, bID1 = 0;

    CHARGE_ICON_ENABLE(AHC_FALSE);

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);
    MenuDraw_ClearMediaType(bID0);
    MenuDraw_MediaType(bID0);
    OSDDraw_ExitMenuDrawing(&bID0, &bID1);

    CHARGE_ICON_ENABLE(AHC_TRUE);
#endif
}

void MenuDraw_BatteryStatus(UINT16 uwDispID)
{
#ifndef CFG_DRAW_IGNORE_BATTERY  //may be defined in config_xxx.h
//    if(AHC_IsHdmiConnect())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else if(AHC_IsTVConnectEx())
//    {
//        UIDrawEx(uwDispID, VIDEO_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
//    }
//    else
    {
        UIDrawEx(uwDispID, VIDEO_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
    }
#endif
}

void MenuDraw_GetPageInfo(UINT32 *pCurPage, UINT32 *pTotalPage, UINT32 *pCurPos, UINT32 ulPageItemNum)
{
    PSMENUSTRUCT    pMenu = GetCurrentMenu();
    UINT32          iCurPage, iTotalPage;


    if((pMenu->iNumOfItems/ulPageItemNum != 0) && (pMenu->iNumOfItems%ulPageItemNum ==0))
    {
        iTotalPage = pMenu->iNumOfItems/ulPageItemNum;
    }
    else
    {
        iTotalPage = pMenu->iNumOfItems/ulPageItemNum + 1;
    }

    iCurPage = (pMenu->iCurrentPos/ulPageItemNum) + 1;

    if(pCurPage!=NULL)
        *pCurPage = iCurPage;

    if(pTotalPage!=NULL)
        *pTotalPage = iTotalPage;

    if(pCurPos!=NULL)
        *pCurPos = pMenu->iCurrentPos;
}

void MenuDraw_CatagoryIcon(UINT16 uwDispID, UINT32 iCata)
{
}

/*
 * Always display Select language page by English, because width of character is too wide
 * on some language (SimChinses and Tradition Chinese)
 */
UINT8 MenuDraw_GetDefaultLanguage(PSMENUSTRUCT pMenu)
{
    if (pMenu->iMenuId == MENUID_SUB_MENU_LANGUAGE)
        return SHOWOSD_LANG_ENG;

    return MenuSettingConfig()->uiLanguage;
}

#if 0
void ________PowerOff_Function_TV________(){ruturn;} //dummy
#endif

extern PSMENUITEM   sMenuListDeleteOne[];
extern AHC_BOOL     PowerOff_Option;
//extern UINT8        m_DelFile;

#if (POWER_OFF_CONFIRM_PAGE_EN)

#if (TVOUT_ENABLE)

void DrawSubItem_PowerOff_TV(UINT16 uwDispID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_BITMAP barID, GUI_COLOR clrFont, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{
    RECT    rc, tmpRECT;
    RECT    StrYesRECT      = RECT_TV_PWROFF_PLAY_STR_YES;
    RECT    StrNoRECT       = RECT_TV_PWROFF_PLAY_STR_NO;
    RECT    StrBrwYesRECT   = RECT_TV_PWROFF_BROW_STR_YES;
    RECT    StrBrwNoRECT    = RECT_TV_PWROFF_BROW_STR_NO;

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else      
    switch(TVFunc_Status())
    {
        case AHC_TV_VIDEO_PREVIEW_STATUS:
        case AHC_TV_DSC_PREVIEW_STATUS:
            rc.uiWidth  = barID.XSize;
            rc.uiHeight = barID.YSize;
            GetSubItemRect(uwDispID, iItem%CONFIRM_MENU_PAGE_ITEM, iTotalItems, &rc );
            rc.uiTop = rc.uiTop + 50;
        break;

        case AHC_TV_BROWSER_STATUS:
            rc = (iItem==CONFIRM_OPT_YES)?(StrBrwYesRECT):(StrBrwNoRECT);
        break;

        case AHC_TV_MOVIE_PB_STATUS:
        case AHC_TV_PHOTO_PB_STATUS:
        case AHC_TV_SLIDE_SHOW_STATUS:
            rc = (iItem==CONFIRM_OPT_YES)?(StrYesRECT):(StrNoRECT);
        break;
    }
#endif

    OSD_Draw_Icon(barID, rc, uwDispID);

    tmpRECT.uiLeft   = rc.uiLeft    + STR_RECT_OFFSET_X;
    tmpRECT.uiTop    = rc.uiTop     + STR_RECT_OFFSET_Y;
    tmpRECT.uiWidth  = rc.uiWidth   + STR_RECT_OFFSET_W;
    tmpRECT.uiHeight = rc.uiHeight  - 9;

    OSD_ShowStringPool(uwDispID, iStrID, tmpRECT, clrFont, clrBack, GUI_TA_HCENTER|GUI_TA_VCENTER);
}

void MenuDrawSubPage_PowerOffCancel_TV(void)
{
    UINT8   uwDispID;
    RECT    PlayOsdRect = RECT_TV_PWROFF_PLAY_REGION;
    RECT    BrwOsdRect  = POS_TV_PAL_BROWSER_OSD;

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else      
    switch(TVFunc_Status())
    {
        case AHC_TV_VIDEO_PREVIEW_STATUS:
        case AHC_TV_DSC_PREVIEW_STATUS:
            AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
            AHC_OSDDrawFillRect(MAIN_DISPLAY_BUFFER, 0, 0, TV_HDMI_DISP_BUF_WIDTH, TV_HDMI_DISP_BUF_HEIGHT);
            AHC_OSDSetActive(MAIN_DISPLAY_BUFFER, 0);
            AHC_OSDSetActive(TVFunc_GetUImodeOsdID(), 1);
        break;

        case AHC_TV_BROWSER_STATUS:
            OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
            AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
            AHC_OSDDrawFillRect2(uwDispID, &BrwOsdRect);
            DrawStateBrowserInit();
        break;

        case AHC_TV_MOVIE_PB_STATUS:
            if(!m_DelFile)
            {
                OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
                AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
                AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);
                DrawMovPb_Status(uwDispID, POS_TV_MOV_STATE_X, POS_TV_MOV_STATE_Y, LARGE_SIZE, MAG_2X, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            }
            else
                DrawStateHdmiMoviePBDel(m_DelFile);
        break;

        case AHC_TV_PHOTO_PB_STATUS:
            if(!m_DelFile)
            {
                OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
                AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
                AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);
                DrawStateTVPhotoPBChangeFile();
            }
            else
                DrawStateHdmiMoviePBDel(m_DelFile);
        break;

        case AHC_TV_SLIDE_SHOW_STATUS:
            if(!m_DelFile)
            {
                OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
                AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
                AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);
                DrawStateTVSlideShowChangeFile();
            }
            else
                DrawStateHdmiMoviePBDel(m_DelFile);
        break;
    }
#endif    
}

void MenuDrawSubPage_PowerOff_TV_Preview(void)
{
    UINT32      StartX   = 145;
    UINT32      StartY   = 50;
    UINT16      uwDispID  = MAIN_DISPLAY_BUFFER;
    UINT32      i;
    GUI_RECT    Rect;
    UINT32      iVal[2];
    UINT16      Width, Height;

    AHC_OSDSetActive(uwDispID, 0);

    switch(MenuSettingConfig()->uiTVSystem)
    {
        case TV_SYSTEM_NTSC:
            AHC_GetNtscTvDisplayWidthHeight(&Width, &Height);
        break;
        case TV_SYSTEM_PAL:
            AHC_GetPalTvDisplayWidthHeight(&Width, &Height);
        break;
    }

    iVal[0] = (Width - TV_HDMI_DISP_BUF_WIDTH)/2;
    iVal[1] = (Height - TV_HDMI_DISP_BUF_HEIGHT)/2;
    AHC_OSDSetDisplayAttr(uwDispID, AHC_OSD_ATTR_DISPLAY_OFFSET, iVal);

    OSDDraw_SetAlphaBlending(uwDispID, AHC_FALSE);

    AHC_OSDSetPenSize(uwDispID, 5);
    AHC_OSDSetColor(uwDispID, TV_MENU_BK_COLOR);
    AHC_OSDDrawFillRect(uwDispID, 0, 0, TV_HDMI_DISP_BUF_WIDTH, TV_HDMI_DISP_BUF_HEIGHT);

    AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);
    AHC_OSDSetBkColor(uwDispID, TV_MENU_BK_COLOR);

    Rect.x0 = 0;
    Rect.y0 = 110;
    Rect.x1 = 320;
    Rect.y1 = 140;

    ShowOSD_SetLanguage(uwDispID);
    AHC_OSDDrawTextInRect(uwDispID, (UINT8*)OSD_GetStringViaID(IDS_DS_MSG_SURE_TO_POWER_OFF), &Rect, GUI_TA_CENTER|GUI_TA_VCENTER);

    AHC_OSDDrawBitmap(uwDispID, &bmIcon_WMSG, StartX, StartY);

    for( i=0; i<2; i++ )
    {
        GUI_COLOR   colorBk = OSD_COLOR_TV_BACKGROUND;
        GUI_BITMAP  barID   = BMICON_SMALLBAR_WHITE;

        if(i == CONFIRM_OPT_YES)//Default
            barID = BMICON_SMALLBAR_YELLOW;

        DrawSubItem_PowerOff_TV(uwDispID, i, CONFIRM_MENU_PAGE_ITEM, sMenuListDeleteOne[i]->uiStringId, sMenuListDeleteOne[i]->bmpIcon, barID, MENU_TEXT_COLOR, colorBk, 0x0);
    }

    AHC_OSDSetCurrentDisplay(uwDispID);
    AHC_OSDSetActive(uwDispID, 1);

    PowerOff_Option  = CONFIRM_OPT_YES;
}

void MenuDrawSubPage_PowerOff_TV_Browser(UINT16 uwDispID)
{
    UINT8   i;
    RECT    OsdRect;
    RECT    StrDecideRECT = RECT_TV_PWROFF_BROW_STR_DECIDE;

    switch(MenuSettingConfig()->uiTVSystem)
    {
        case TV_SYSTEM_NTSC:
            OsdRect.uiLeft      = POS_TV_NTSC_BROWSER_OSD_X0;
            OsdRect.uiTop       = POS_TV_NTSC_BROWSER_OSD_Y0;
            OsdRect.uiWidth     = POS_TV_NTSC_BROWSER_OSD_W;
            OsdRect.uiHeight    = POS_TV_NTSC_BROWSER_OSD_H;
        break;

        case TV_SYSTEM_PAL:
            OsdRect.uiLeft      = POS_TV_PAL_BROWSER_OSD_X0;
            OsdRect.uiTop       = POS_TV_PAL_BROWSER_OSD_Y0;
            OsdRect.uiWidth     = POS_TV_PAL_BROWSER_OSD_W;
            OsdRect.uiHeight    = POS_TV_PAL_BROWSER_OSD_H;
        break;
    }

    AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect2(uwDispID, &OsdRect);

    ShowOSD_SetLanguage(uwDispID);
    OSD_ShowStringPool(uwDispID, IDS_DS_MSG_SURE_TO_POWER_OFF, StrDecideRECT, MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

    for( i=0; i<2; i++ )
    {
        GUI_COLOR   colorBackground = OSD_COLOR_TV_BACKGROUND;
        GUI_BITMAP  barID = BMICON_SUBBAR_WHITE;

        if(i == CONFIRM_OPT_YES)//Default
            barID = BMICON_SUBBAR_YELLOW;

        DrawSubItem_PowerOff_TV(uwDispID, i, 2, sMenuListDeleteOne[i]->uiStringId, sMenuListDeleteOne[i]->bmpIcon, barID, MENU_TEXT_COLOR, colorBackground, 0x0);
    }
}

void MenuDrawSubPage_PowerOff_TV_Play(UINT16 uwDispID)
{
    UINT8   i;
    RECT    PlayOsdRect     = RECT_TV_PWROFF_PLAY_REGION;
    RECT    StrDecideRECT   = RECT_TV_PWROFF_PLAY_STR_DECIDE;

    AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);

    ShowOSD_SetLanguage(uwDispID);
    OSD_ShowStringPool(uwDispID, IDS_DS_MSG_SURE_TO_POWER_OFF, StrDecideRECT, MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

    for( i=0; i<2; i++ )
    {
        GUI_COLOR   colorBk = OSD_COLOR_TV_BACKGROUND;
        GUI_BITMAP  barID   = BMICON_SUBBAR_WHITE;

        if(i == CONFIRM_OPT_YES)//Default
            barID = BMICON_SUBBAR_YELLOW;

        DrawSubItem_PowerOff_TV(uwDispID, i, 2, sMenuListDeleteOne[i]->uiStringId, sMenuListDeleteOne[i]->bmpIcon, barID, MENU_TEXT_COLOR, colorBk, 0x0);
    }
}

void MenuDrawSubPage_PowerOff_TV(void)
{
    UINT8   bID0 = 0, bID1 = 0;

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else      
    switch(TVFunc_Status())
    {
        case AHC_TV_VIDEO_PREVIEW_STATUS:
        case AHC_TV_DSC_PREVIEW_STATUS:
            MenuDrawSubPage_PowerOff_TV_Preview();
        break;

        case AHC_TV_BROWSER_STATUS:
            OSDDraw_EnterDrawing(&bID0, &bID1);
            MenuDrawSubPage_PowerOff_TV_Browser(bID0);
            OSDDraw_ExitDrawing(&bID0,&bID1);
        break;

        case AHC_TV_MOVIE_PB_STATUS:
        case AHC_TV_PHOTO_PB_STATUS:
        case AHC_TV_SLIDE_SHOW_STATUS:
            OSDDraw_GetLastOvlDrawBuffer(&bID0);
            MenuDrawSubPage_PowerOff_TV_Play(bID0);
        break;
    }
#endif

    PowerOff_Option  = CONFIRM_OPT_YES;
}

void MenuDrawChangeSubItem_PowerOff_TV(void)
{
    GUI_COLOR   colorFill       = OSD_COLOR_TV_BACKGROUND;
    UINT8       bID0            = 0;
    UINT8       bID1            = 0;
    UINT32      uiPrevItem      = CONFIRM_OPT_NO;
    UINT32      uiCurrItem      = CONFIRM_OPT_YES;

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else      
    switch(TVFunc_Status())
    {
        case AHC_TV_VIDEO_PREVIEW_STATUS:
        case AHC_TV_DSC_PREVIEW_STATUS:
            bID0 = MAIN_DISPLAY_BUFFER;
        break;

        case AHC_TV_BROWSER_STATUS:
            OSDDraw_EnterDrawing(&bID0, &bID1);
            OSDDraw_ClearOvlDrawOvlBufferAll();
        break;

        case AHC_TV_MOVIE_PB_STATUS:
        case AHC_TV_PHOTO_PB_STATUS:
        case AHC_TV_SLIDE_SHOW_STATUS:
            OSDDraw_GetLastOvlDrawBuffer(&bID0);
        break;
    }
#endif

    if(PowerOff_Option==CONFIRM_OPT_YES)
    {
        uiPrevItem = CONFIRM_OPT_NO;
        uiCurrItem = CONFIRM_OPT_YES;
    }
    else if(PowerOff_Option==CONFIRM_OPT_NO)
    {
        uiPrevItem = CONFIRM_OPT_YES;
        uiCurrItem = CONFIRM_OPT_NO;
    }

    DrawSubItem_PowerOff_TV(bID0, uiPrevItem%2, 2, sMenuListDeleteOne[uiPrevItem]->uiStringId, sMenuListDeleteOne[uiPrevItem]->bmpIcon, BMICON_SUBBAR_WHITE,  MENU_TEXT_COLOR, colorFill, 0x0);
    DrawSubItem_PowerOff_TV(bID0, uiCurrItem,   2, sMenuListDeleteOne[uiCurrItem]->uiStringId, sMenuListDeleteOne[uiCurrItem]->bmpIcon, BMICON_SUBBAR_YELLOW, MENU_TEXT_COLOR, colorFill, 0x0);

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else      
    if(TVFunc_Status()==AHC_TV_BROWSER_STATUS)
    {
        OSDDraw_ExitDrawing(&bID0, &bID1);
    }
#endif    
}

#endif

#if 0
void ________PowerOff_Function_HDMI________(){ruturn;} //dummy
#endif

#if (HDMI_ENABLE)

void DrawSubItem_PowerOff_HDMI(UINT16 uwDispID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID,  GUI_BITMAP barID, GUI_COLOR clrFont, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{
    RECT    rc, tmpRECT;
    RECT    StrYesRECT          = RECT_HDMI_PWOFF_PLAY_STR_YES;
    RECT    StrNoRECT           = RECT_HDMI_PWOFF_PLAY_STR_NO;
    RECT    StrBrwYesRECT_1080P = RECT_HDMI_1080P_PWOFF_BROW_YES;
    RECT    StrBrwNoRECT_1080P  = RECT_HDMI_1080P_PWOFF_BROW_NO;
    RECT    StrBrwYesRECT_1080I = RECT_HDMI_1080I_PWOFF_BROW_YES;
    RECT    StrBrwNoRECT_1080I  = RECT_HDMI_1080I_PWOFF_BROW_NO;
    RECT    StrBrwYesRECT_720P  = RECT_HDMI_720P_PWOFF_BROW_YES;
    RECT    StrBrwNoRECT_720P   = RECT_HDMI_720P_PWOFF_BROW_NO;
    RECT    StrBrwYesRECT_480P  = RECT_HDMI_480P_PWOFF_BROW_YES;    // TBD
    RECT    StrBrwNoRECT_480P   = RECT_HDMI_480P_PWOFF_BROW_NO;     // TBD

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else
    switch(HDMIFunc_Status())
    {
        case AHC_HDMI_VIDEO_PREVIEW_STATUS:
        case AHC_HDMI_DSC_PREVIEW_STATUS:
            rc.uiWidth  = barID.XSize;
            rc.uiHeight = barID.YSize;
            GetSubItemRect(uwDispID, iItem%CONFIRM_MENU_PAGE_ITEM, iTotalItems, &rc );
            rc.uiTop = rc.uiTop + 50;
        break;

        case AHC_HDMI_BROWSER_STATUS:
            if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_1080I)
                rc = (iItem==CONFIRM_OPT_YES)?(StrBrwYesRECT_1080I):(StrBrwNoRECT_1080I);
            else if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_720P)
                rc = (iItem==CONFIRM_OPT_YES)?(StrBrwYesRECT_720P):(StrBrwNoRECT_720P);
            else if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_480P)    // TBD
                rc = (iItem==CONFIRM_OPT_YES)?(StrBrwYesRECT_480P):(StrBrwNoRECT_480P);
            else //if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_1080P)     // TBD
                rc = (iItem==CONFIRM_OPT_YES)?(StrBrwYesRECT_1080P):(StrBrwNoRECT_1080P);
        break;

        case AHC_HDMI_MOVIE_PB_STATUS:
        case AHC_HDMI_PHOTO_PB_STATUS:
        case AHC_HDMI_SLIDE_SHOW_STATUS:
            rc = (iItem==CONFIRM_OPT_YES)?(StrYesRECT):(StrNoRECT);
        break;
    }
#endif

    OSD_Draw_Icon(barID, rc, uwDispID);

    tmpRECT.uiLeft   = rc.uiLeft    + STR_RECT_OFFSET_X;
    tmpRECT.uiTop    = rc.uiTop     + STR_RECT_OFFSET_Y;
    tmpRECT.uiWidth  = rc.uiWidth   + STR_RECT_OFFSET_W;
    tmpRECT.uiHeight = rc.uiHeight  - 9;
    OSD_ShowStringPool(uwDispID, iStrID, tmpRECT, clrFont, clrBack, GUI_TA_HCENTER|GUI_TA_VCENTER);
}

void MenuDrawSubPage_PowerOffCancel_HDMI(void)
{
    UINT8   uwDispID            = 0;
    RECT    PlayOsdRect         = RECT_HDMI_PWROFF_PLAY_REGION;
    RECT    BrwOsdRect          = {0, 0, 0 , 0};
    RECT    BrwOsdRect_1080P    = POS_HDMI_1080P_BROWSER_OSD;
    RECT    BrwOsdRect_1080I    = POS_HDMI_1080I_BROWSER_OSD;
    RECT    BrwOsdRect_720P     = POS_HDMI_720P_BROWSER_OSD;

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else
    switch(HDMIFunc_Status())
    {
        case AHC_HDMI_VIDEO_PREVIEW_STATUS:
        case AHC_HDMI_DSC_PREVIEW_STATUS:
            AHC_OSDSetColor(MAIN_DISPLAY_BUFFER, OSD_COLOR_TRANSPARENT);
            AHC_OSDDrawFillRect(MAIN_DISPLAY_BUFFER, 0, 0, TV_HDMI_DISP_BUF_WIDTH, TV_HDMI_DISP_BUF_HEIGHT);
            AHC_OSDSetActive(MAIN_DISPLAY_BUFFER, 0);
            AHC_OSDSetActive(HDMIFunc_GetUImodeOsdID(), 1);
        break;

        case AHC_HDMI_BROWSER_STATUS:

            OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
            AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);

            if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_1080I)
                BrwOsdRect = BrwOsdRect_1080I;
            else if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_720P)
                BrwOsdRect = BrwOsdRect_720P;
            else if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_480P)        // TBD
                BrwOsdRect = BrwOsdRect_480P;
            else    //if(MenuSettingConfig()->uiHDMIOutput==HDMI_OUTPUT_1080P)
                BrwOsdRect = BrwOsdRect_1080P;

            AHC_OSDDrawFillRect2(uwDispID, &BrwOsdRect);
            DrawStateBrowserInit();
        break;

        case AHC_HDMI_MOVIE_PB_STATUS:
            if(!m_DelFile)
            {
                OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
                AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
                AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);
                DrawHdmiMoviePB_Status(uwDispID, POS_HDMI_MOV_STATE_X, POS_HDMI_MOV_STATE_Y, LARGE_SIZE, MAG_2X, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            }
            else
                DrawStateHdmiMoviePBDel(m_DelFile);
        break;

        case AHC_HDMI_PHOTO_PB_STATUS:
            if(!m_DelFile)
            {
                OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
                AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
                AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);
                DrawStateHdmiPhotoPBChangeFile();
            }
            else
                DrawStateHdmiMoviePBDel(m_DelFile);
        break;

        case AHC_HDMI_SLIDE_SHOW_STATUS:
            if(!m_DelFile)
            {
                OSDDraw_GetLastOvlDrawBuffer(&uwDispID);
                AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
                AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);
                DrawStateHdmiSlideShowChangeFile();
            }
            else
                DrawStateHdmiMoviePBDel(m_DelFile);
        break;
    }
#endif    
}

void MenuDrawSubPage_PowerOff_HDMI_Preview(void)
{
    UINT32      StartX   = 145;
    UINT32      StartY   = 50;
    UINT16      uwDispID  = MAIN_DISPLAY_BUFFER;
    UINT32      i;
    GUI_RECT    Rect;
    UINT32      iVal[2];
    UINT16      Width, Height;

    AHC_OSDSetActive(uwDispID, 0);

    AHC_GetHdmiDisplayWidthHeight(&Width, &Height);

    iVal[0] = (Width - TV_HDMI_DISP_BUF_WIDTH)/2;
    iVal[1] = (Height - TV_HDMI_DISP_BUF_HEIGHT)/2;
    AHC_OSDSetDisplayAttr(uwDispID, AHC_OSD_ATTR_DISPLAY_OFFSET, iVal);

    OSDDraw_SetAlphaBlending(uwDispID, AHC_FALSE);

    AHC_OSDSetPenSize(uwDispID, 5);
    AHC_OSDSetColor(uwDispID, TV_MENU_BK_COLOR);
    AHC_OSDDrawFillRect(uwDispID, 0, 0, TV_HDMI_DISP_BUF_WIDTH, TV_HDMI_DISP_BUF_HEIGHT);

    AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);
    AHC_OSDSetBkColor(uwDispID, TV_MENU_BK_COLOR);

    Rect.x0 = 0;
    Rect.y0 = 110;
    Rect.x1 = 320;
    Rect.y1 = 140;

    ShowOSD_SetLanguage(uwDispID);
    AHC_OSDDrawTextInRect(uwDispID, (UINT8*)OSD_GetStringViaID(IDS_DS_MSG_SURE_TO_POWER_OFF), &Rect, GUI_TA_CENTER|GUI_TA_VCENTER);

    AHC_OSDDrawBitmap(uwDispID, &bmIcon_WMSG, StartX, StartY);

    for( i=0; i<2; i++ )
    {
        GUI_COLOR   colorBk = OSD_COLOR_TRANSPARENT;
        GUI_BITMAP  barID   = BMICON_SMALLBAR_WHITE;

        if(i == CONFIRM_OPT_YES)//Default
            barID = BMICON_SMALLBAR_YELLOW;

        DrawSubItem_PowerOff_HDMI(uwDispID, i, CONFIRM_MENU_PAGE_ITEM, sMenuListDeleteOne[i]->uiStringId, sMenuListDeleteOne[i]->bmpIcon, barID, MENU_TEXT_COLOR, colorBk, 0x0);
    }

    AHC_OSDSetCurrentDisplay(uwDispID);
    AHC_OSDSetActive(uwDispID, 1);

    PowerOff_Option  = CONFIRM_OPT_YES;
}

void MenuDrawSubPage_PowerOff_HDMI_Browser(UINT16 uwDispID)
{
    UINT8   i;
    RECT    OsdRect;
    RECT    StrDecideRECT;
    RECT    StrDecideRECT1080P = RECT_HDMI_1080P_PWOFF_BROW_DECIDE;
    RECT    StrDecideRECT1080I = RECT_HDMI_1080I_PWOFF_BROW_DECIDE;
    RECT    StrDecideRECT720P  = RECT_HDMI_720P_PWOFF_BROW_DECIDE;

    switch(MenuSettingConfig()->uiHDMIOutput)
    {
        case HDMI_OUTPUT_1080I:
            OsdRect.uiLeft          = POS_HDMI_1080I_BROWSER_OSD_X0;
            OsdRect.uiTop           = POS_HDMI_1080I_BROWSER_OSD_Y0;
            OsdRect.uiWidth         = POS_HDMI_1080I_BROWSER_OSD_W;
            OsdRect.uiHeight        = POS_HDMI_1080I_BROWSER_OSD_H;

            StrDecideRECT           = StrDecideRECT1080I;
            break;
        case HDMI_OUTPUT_720P:
            OsdRect.uiLeft          = POS_HDMI_720P_BROWSER_OSD_X0;
            OsdRect.uiTop           = POS_HDMI_720P_BROWSER_OSD_Y0;
            OsdRect.uiWidth         = POS_HDMI_720P_BROWSER_OSD_W;
            OsdRect.uiHeight        = POS_HDMI_720P_BROWSER_OSD_H;

            StrDecideRECT           = StrDecideRECT720P;
            break;
        case HDMI_OUTPUT_480P:      // TBD
            OsdRect.uiLeft          = POS_HDMI_480P_BROWSER_OSD_X0;
            OsdRect.uiTop           = POS_HDMI_480P_BROWSER_OSD_Y0;
            OsdRect.uiWidth         = POS_HDMI_480P_BROWSER_OSD_W;
            OsdRect.uiHeight        = POS_HDMI_480P_BROWSER_OSD_H;

            StrDecideRECT           = StrDecideRECT480P;
            break;
        default:
        case HDMI_OUTPUT_1080P:
            OsdRect.uiLeft          = POS_HDMI_1080P_BROWSER_OSD_X0;
            OsdRect.uiTop           = POS_HDMI_1080P_BROWSER_OSD_Y0;
            OsdRect.uiWidth         = POS_HDMI_1080P_BROWSER_OSD_W;
            OsdRect.uiHeight        = POS_HDMI_1080P_BROWSER_OSD_H;

            StrDecideRECT           = StrDecideRECT1080P;
            break;
    }

    AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect2(uwDispID, &OsdRect);

    ShowOSD_SetLanguage(uwDispID);
    OSD_ShowStringPool(uwDispID, IDS_DS_MSG_SURE_TO_POWER_OFF, StrDecideRECT, MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

    for( i=0; i<2; i++ )
    {
        GUI_COLOR   colorBk = OSD_COLOR_TV_BACKGROUND;
        GUI_BITMAP  barID   = BMICON_SUBBAR_WHITE;

        if(i == CONFIRM_OPT_YES)//Default
            barID = BMICON_SUBBAR_YELLOW;

        DrawSubItem_PowerOff_HDMI(uwDispID, i, 2, sMenuListDeleteOne[i]->uiStringId, sMenuListDeleteOne[i]->bmpIcon, barID, MENU_TEXT_COLOR, colorBk, 0x0);
    }
}

void MenuDrawSubPage_PowerOff_HDMI_Play(UINT16 uwDispID)
{
    UINT8   i;
    RECT    PlayOsdRect     = RECT_HDMI_PWROFF_PLAY_REGION;
    RECT    StrDecideRECT   = RECT_HDMI_PWROFF_PLAY_STR_DECIDE;

    AHC_OSDSetColor(uwDispID, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect2(uwDispID, &PlayOsdRect);

    ShowOSD_SetLanguage(uwDispID);
    OSD_ShowStringPool(uwDispID, IDS_DS_MSG_SURE_TO_POWER_OFF, StrDecideRECT, MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

    for( i=0; i<2; i++ )
    {
        GUI_COLOR   colorBk = OSD_COLOR_TV_BACKGROUND;
        GUI_BITMAP  barID   = BMICON_SUBBAR_WHITE;

        if(i == CONFIRM_OPT_YES)//Default
            barID = BMICON_SUBBAR_YELLOW;

        DrawSubItem_PowerOff_HDMI(uwDispID, i, 2, sMenuListDeleteOne[i]->uiStringId, sMenuListDeleteOne[i]->bmpIcon, barID, MENU_TEXT_COLOR, colorBk, 0x0);
    }
}

void MenuDrawSubPage_PowerOff_HDMI(void)
{
    UINT8   bID0 = 0, bID1 = 0;

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else
    switch(HDMIFunc_Status())
    {
        case AHC_HDMI_VIDEO_PREVIEW_STATUS:
        case AHC_HDMI_DSC_PREVIEW_STATUS:
            MenuDrawSubPage_PowerOff_HDMI_Preview();
        break;

        case AHC_HDMI_BROWSER_STATUS:
            OSDDraw_EnterDrawing(&bID0, &bID1);
            MenuDrawSubPage_PowerOff_HDMI_Browser(bID0);
            OSDDraw_ExitDrawing(&bID0, &bID1);
        break;

        case AHC_HDMI_MOVIE_PB_STATUS:
        case AHC_HDMI_PHOTO_PB_STATUS:
        case AHC_HDMI_SLIDE_SHOW_STATUS:
            OSDDraw_GetLastOvlDrawBuffer(&bID0);
            MenuDrawSubPage_PowerOff_HDMI_Play(bID0);
        break;
    }
#endif

    PowerOff_Option  = CONFIRM_OPT_YES;//Default
}

void MenuDrawChangeSubItem_PowerOff_HDMI(void)
{
    GUI_COLOR   colorFill       = OSD_COLOR_TV_BACKGROUND;
    UINT8       bID0            = 0;
    UINT8       bID1            = 0;
    UINT32      uiPrevItem      = CONFIRM_OPT_NO;
    UINT32      uiCurrItem      = CONFIRM_OPT_YES;

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else
    switch(HDMIFunc_Status())
    {
        case AHC_HDMI_VIDEO_PREVIEW_STATUS:
        case AHC_HDMI_DSC_PREVIEW_STATUS:
            bID0 = MAIN_DISPLAY_BUFFER;
        break;

        case AHC_HDMI_BROWSER_STATUS:
            OSDDraw_EnterDrawing(&bID0, &bID1);
            OSDDraw_ClearOvlDrawOvlBufferAll();
        break;

        case AHC_HDMI_MOVIE_PB_STATUS:
        case AHC_HDMI_PHOTO_PB_STATUS:
        case AHC_HDMI_SLIDE_SHOW_STATUS:
            OSDDraw_GetLastOvlDrawBuffer(&bID0);
        break;
    }
#endif

    if(PowerOff_Option==CONFIRM_OPT_YES)
    {
        uiPrevItem = CONFIRM_OPT_NO;
        uiCurrItem = CONFIRM_OPT_YES;
    }
    else if(PowerOff_Option==CONFIRM_OPT_NO)
    {
        uiPrevItem = CONFIRM_OPT_YES;
        uiCurrItem = CONFIRM_OPT_NO;
    }

    DrawSubItem_PowerOff_HDMI(bID0, uiPrevItem%2, 2, sMenuListDeleteOne[uiPrevItem]->uiStringId, sMenuListDeleteOne[uiPrevItem]->bmpIcon, BMICON_SUBBAR_WHITE,  MENU_TEXT_COLOR, colorFill, 0x0);
    DrawSubItem_PowerOff_HDMI(bID0, uiCurrItem,   2, sMenuListDeleteOne[uiCurrItem]->uiStringId, sMenuListDeleteOne[uiCurrItem]->bmpIcon, BMICON_SUBBAR_YELLOW, MENU_TEXT_COLOR, colorFill, 0x0);

#if 1 //Andy Liu TBD. 
    printc(FG_RED("\r\nPlease modify here!\r\n"));
    AHC_PRINT_RET_ERROR(0, 0);
#else
    if(HDMIFunc_Status()==AHC_HDMI_BROWSER_STATUS)
    {
        OSDDraw_ExitDrawing(&bID0, &bID1);
    }
#endif
}

#endif

#if 0
void ________PowerOff_Function_Normal________(){ruturn;} //dummy
#endif

void DrawSubItem_PowerOff(UINT16 uwDispID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_BITMAP barID, GUI_COLOR clrFont, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{
    RECT rc, tmpRECT;

    rc.uiWidth  = barID.XSize;
    rc.uiHeight = barID.YSize;
    GetSubItemRect(uwDispID, iItem%CONFIRM_MENU_PAGE_ITEM, iTotalItems, &rc );

    rc.uiTop = rc.uiTop + 50;

    OSD_Draw_Icon(barID, rc, uwDispID);

    tmpRECT.uiLeft   = rc.uiLeft    + STR_RECT_OFFSET_X;
    tmpRECT.uiTop    = rc.uiTop     + STR_RECT_OFFSET_Y;
    tmpRECT.uiWidth  = rc.uiWidth   + STR_RECT_OFFSET_W;
    tmpRECT.uiHeight = rc.uiHeight  + STR_RECT_OFFSET_H;
    OSD_ShowStringPool3(uwDispID, iStrID, tmpRECT, clrFont, clrBack, GUI_TA_HCENTER|GUI_TA_VCENTER);

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif
}

void MenuDrawSubPage_PowerOff(PSMENUSTRUCT pMenu)
{
    UINT32 StartX    = 145;
    UINT32 StartY    = 50;
    UINT16 uwDispID  = MAIN_DISPLAY_BUFFER;
    UINT32 i;
    GUI_RECT Rect;

#if (TVOUT_ENABLE)
    if(uiGetCurrentState()==UI_TVOUT_STATE)
    {
        MenuDrawSubPage_PowerOff_TV();
        return;
    }
#endif
#if (HDMI_ENABLE)
    if(uiGetCurrentState()==UI_HDMI_STATE)
    {
        MenuDrawSubPage_PowerOff_HDMI();
        return;
    }
#endif

    if(AHC_OS_AcquireSem(m_WMSGSemID, 0) != MMPF_OS_ERR_NONE)
        return;

    AHC_OSDSetActive(uwDispID, 0);

    OSDDraw_SetAlphaBlending(uwDispID, AHC_FALSE);
    OSDDraw_SetSemiTransparent(uwDispID, AHC_FALSE, AHC_OSD_SEMITP_AVG, 0);

    AHC_OSDSetPenSize(uwDispID, 5);
    AHC_OSDSetColor(uwDispID, MENU_BACKGROUND_COLOR);
    AHC_OSDSetBkColor(uwDispID, MENU_BACKGROUND_COLOR);
    AHC_OSDDrawFillRect(uwDispID, 0, 0, AHC_GET_ATTR_OSD_W(uwDispID), AHC_GET_ATTR_OSD_H(uwDispID));

    AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);
    AHC_OSDSetBkColor(uwDispID, MENU_BACKGROUND_COLOR);

    Rect.x0 = 0;
    Rect.y0 = 110;
    Rect.x1 = 320;
    Rect.y1 = 140;

    ShowOSD_SetLanguage(uwDispID);
    AHC_OSDDrawTextInRect(uwDispID, (UINT8*)OSD_GetStringViaID(IDS_DS_MSG_SURE_TO_POWER_OFF), &Rect, GUI_TA_CENTER|GUI_TA_VCENTER);

    AHC_OSDDrawBitmap(uwDispID, &bmIcon_WMSG, StartX, StartY);

    for( i=0; i<2; i++ )
    {
        GUI_COLOR   colorBk = MENU_BACKGROUND_COLOR;
        GUI_BITMAP  barID   = BMICON_SMALLBAR_WHITE;

        if(i == CONFIRM_OPT_YES)//Default
            barID = BMICON_SMALLBAR_YELLOW;

        DrawSubItem_PowerOff(uwDispID, i, CONFIRM_MENU_PAGE_ITEM, sMenuListDeleteOne[i]->uiStringId, sMenuListDeleteOne[i]->bmpIcon, barID, MENU_TEXT_COLOR, colorBk, 0x0);
    }

    AHC_OSDSetCurrentDisplay(uwDispID);
    AHC_OSDSetActive(uwDispID, 1);

    PowerOff_Option  = CONFIRM_OPT_YES;

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif

    AHC_OS_ReleaseSem(m_WMSGSemID);
}

void MenuDrawChangeSubItem_PowerOff(void)
{
    GUI_COLOR   colorFill       = MENU_BACKGROUND_COLOR;
    UINT16      uwDispID        = MAIN_DISPLAY_BUFFER;
    UINT32      uiPrevItem      = CONFIRM_OPT_NO;
    UINT32      uiCurrItem      = CONFIRM_OPT_YES;

#if (TVOUT_ENABLE)
    if(uiGetCurrentState()==UI_TVOUT_STATE)
    {
        MenuDrawChangeSubItem_PowerOff_TV();
        return;
    }
#endif
#if (HDMI_ENABLE)
    if(uiGetCurrentState()==UI_HDMI_STATE)
    {
        MenuDrawChangeSubItem_PowerOff_HDMI();
        return;
    }
#endif

    if(AHC_OS_AcquireSem(m_WMSGSemID, 0) != MMPF_OS_ERR_NONE)
        return;

    if(PowerOff_Option==CONFIRM_OPT_YES)
    {
        uiPrevItem = CONFIRM_OPT_NO;
        uiCurrItem = CONFIRM_OPT_YES;
    }
    else if(PowerOff_Option==CONFIRM_OPT_NO)
    {
        uiPrevItem = CONFIRM_OPT_YES;
        uiCurrItem = CONFIRM_OPT_NO;
    }

    DrawSubItem_PowerOff(uwDispID, uiPrevItem%SUB_MENU_PAGE_ITEM, 2, sMenuListDeleteOne[uiPrevItem]->uiStringId, sMenuListDeleteOne[uiPrevItem]->bmpIcon, BMICON_SMALLBAR_WHITE,  MENU_TEXT_COLOR, colorFill, 0x0);
    DrawSubItem_PowerOff(uwDispID, uiCurrItem,                    2, sMenuListDeleteOne[uiCurrItem]->uiStringId, sMenuListDeleteOne[uiCurrItem]->bmpIcon, BMICON_SMALLBAR_YELLOW, MENU_TEXT_COLOR, colorFill, 0x0);

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif

    AHC_OS_ReleaseSem(m_WMSGSemID);
}

#endif

#if 0
void ________ExitMenu_Function_________(){ruturn;} //dummy
#endif

#if (POWER_ON_MENU_SET_EN) || (EXIT_MENU_PAGE_EN)

void MenuDrawExitItem(UINT16 uwDispID, int iItem, UINT32 iStrID, GUI_BITMAP barID, GUI_COLOR clrFont, GUI_COLOR clrBack)
{
    RECT rc, tmpRECT;
    RECT tmpRECT1 = RECT_EXIT_MENU_STR;
    RECT tmpRECT2 = RECT_EXIT_MENU_ICON;

    rc.uiWidth  = barID.XSize;
    rc.uiHeight = barID.YSize;
    GetSubItemRect(uwDispID, iItem%CONFIRM_MENU_PAGE_ITEM, CONFIRM_MENU_PAGE_ITEM, &rc );

    AHC_OSDSetBkColor(uwDispID, clrBack);
    OSD_Draw_Icon(bmIcon_Exit, tmpRECT2, uwDispID);

    OSD_ShowStringPool(uwDispID, IDS_DS_EXITMENU, tmpRECT1, clrFont, clrBack, GUI_TA_HCENTER|GUI_TA_VCENTER);

    rc.uiTop += 45;

    OSD_Draw_Icon(barID, rc, uwDispID);

    AHC_OSDSetColor(uwDispID, clrBack);
    tmpRECT.uiLeft   = rc.uiLeft    + STR_RECT_OFFSET_X;
    tmpRECT.uiTop    = rc.uiTop     + STR_RECT_OFFSET_Y;
    tmpRECT.uiWidth  = rc.uiWidth   + STR_RECT_OFFSET_W;
    tmpRECT.uiHeight = rc.uiHeight  + STR_RECT_OFFSET_H;
    OSD_ShowStringPool(uwDispID, iStrID, tmpRECT, clrFont, clrBack, GUI_TA_HCENTER|GUI_TA_VCENTER);
}

void MenuDrawExitMainPage(PSMENUSTRUCT pMenu)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    UINT32 i;

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    OSDDraw_SetAlphaBlending(bID0, AHC_TRUE);
    OSDDraw_SetAlphaBlending(bID1, AHC_TRUE);

    OSDDraw_ClearOvlDrawBuffer(bID0);

    MenuMainDrawBackCurtain(bID0, OSD_COLOR_BLACK);

    MenuMainDrawCatagory(bID0, GetCatagoryMenuID(pMenu));

    if( pMenu->uiStringId != -1 )
    {
        MenuDrawTitle(bID0, pMenu->uiStringId);
    }

    for( i=0; i< pMenu->iNumOfItems; i++ )
    {
        GUI_BITMAP barID = BMICON_SMALLBAR_WHITE;

        if( i == pMenu->iCurrentPos )
        {
            barID = BMICON_SMALLBAR_YELLOW;
        }

        MenuDrawExitItem(bID0, i%CONFIRM_MENU_PAGE_ITEM, pMenu->pItemsList[i]->uiStringId, barID, MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT);
    }

    MenuDraw_BatteryStatus(bID0);

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

void MenuDrawChangeExitItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem)
{
    UINT8     bID0 = 0;
    UINT8     bID1 = 0;

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    MenuDrawExitItem(bID0, uiPrevItem%CONFIRM_MENU_PAGE_ITEM, pMenu->pItemsList[uiPrevItem]->uiStringId, BMICON_SMALLBAR_WHITE,  MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT);
    MenuDrawExitItem(bID0, uiCurrItem%CONFIRM_MENU_PAGE_ITEM, pMenu->pItemsList[uiCurrItem]->uiStringId, BMICON_SMALLBAR_YELLOW, MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT);

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

#endif

#if 0
void ________MainMenu_Function_________(){ruturn;} //dummy
#endif


#if (MENU_WIFI_PAGE_EN)
void DrawCatagoryMenuIcon(UINT16 uwDispID, AHC_BOOL ManualHL, AHC_BOOL MovieHL, AHC_BOOL StillHL, AHC_BOOL PlaybackHL, AHC_BOOL EditHL, AHC_BOOL MediaHL, AHC_BOOL GeneralHL, AHC_BOOL WifiHL)
#else
void DrawCatagoryMenuIcon(UINT16 uwDispID, AHC_BOOL ManualHL, AHC_BOOL MovieHL, AHC_BOOL StillHL, AHC_BOOL PlaybackHL, AHC_BOOL EditHL, AHC_BOOL MediaHL, AHC_BOOL GeneralHL)
#endif
{
    RECT        tmpRECT  = RECT_2NDMENU_CATAGORY;
    RECT        tmpRECT1 = RECT_2NDMENU_CATAGORY;
    GUI_BITMAP  IconBmp;
    int         g;

    #if (DISP_WIDTH == 480) && defined(STRETCH_X) && defined(STRETCH_Y)
    #define ICON_GAP(i)     (STRETCH_X(35) * i)
    #else
    #define ICON_GAP(i)     (35*i)
    #endif

    tmpRECT.uiTop = AHC_GET_ATTR_OSD_W(uwDispID)-34;
    tmpRECT1.uiTop = AHC_GET_ATTR_OSD_H(uwDispID)-34;

    g = 0;
    IconBmp = (MovieHL)?(BMICON_CATALOG_MOVIE_MENU_HL):(BMICON_CATALOG_MOVIE_MENU);
    OSD_Draw_Icon(IconBmp, tmpRECT1, uwDispID);

    tmpRECT1.uiLeft = tmpRECT.uiLeft-1 + ICON_GAP(++g);
#if (DSC_MODE_ENABLE)
    IconBmp = (StillHL)?(BMICON_CATALOG_CAMERA_MENU_HL):(BMICON_CATALOG_CAMERA_MENU);
    OSD_Draw_Icon(IconBmp, tmpRECT1, uwDispID);

    tmpRECT1.uiLeft = tmpRECT.uiLeft-1 + ICON_GAP(++g);
#endif
    IconBmp = (PlaybackHL)?(BMICON_CATALOG_PLAYBACK_MENU_HL):(BMICON_CATALOG_PLAYBACK_MENU);
    OSD_Draw_Icon(IconBmp, tmpRECT1, uwDispID);

    tmpRECT1.uiLeft = tmpRECT.uiLeft-1 + ICON_GAP(++g);

    IconBmp = (MediaHL)?(BMICON_CATALOG_MEDIA_MENU_HL):(BMICON_CATALOG_MEDIA_MENU);
    OSD_Draw_Icon(IconBmp, tmpRECT1, uwDispID);

    tmpRECT1.uiLeft = tmpRECT.uiLeft-1 + ICON_GAP(++g);

    IconBmp = (GeneralHL)?(BMICON_CATALOG_GENERAL_MENU_HL):(BMICON_CATALOG_GENERAL_MENU);
    OSD_Draw_Icon(IconBmp, tmpRECT1, uwDispID);

#if (MENU_WIFI_PAGE_EN)
    tmpRECT1.uiLeft = tmpRECT.uiLeft-1 + ICON_GAP(++g);

    IconBmp = (WifiHL)?(BMICON_CATALOG_GENERAL_MENU_HL):(BMICON_CATALOG_GENERAL_MENU);
    OSD_Draw_Icon(IconBmp, tmpRECT1, uwDispID);
#endif

}

void MenuMainDrawCatagory(UINT16 uwDispID, int  iCata)
{
    switch(iCata)
    {
#if (MENU_WIFI_PAGE_EN)
        case 0:
            DrawCatagoryMenuIcon(uwDispID, 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0);
        break;

        case 1:
            DrawCatagoryMenuIcon(uwDispID, 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0);
        break;

        case 2:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0);
        break;

        case 3:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0);
        break;

        case 4:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0);
        break;

        case 5:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0);
        break;

        case 6:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0);
        break;

        case 7:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0);
        break;

        case 8:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1);
        break;
#else
        case 0:
            DrawCatagoryMenuIcon(uwDispID, 1 , 0 , 0 , 0 , 0 , 0 , 0);
        break;

        case 1:
            DrawCatagoryMenuIcon(uwDispID, 0 , 1 , 0 , 0 , 0 , 0 , 0);
        break;

        case 2:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 1 , 0 , 0 , 0 , 0);
        break;

        case 3:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 1 , 0 , 0 , 0);
        break;

        case 4:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 1 , 0 , 0);
        break;

        case 5:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 0 , 1 , 0);
        break;

        case 6:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 0 , 0 , 1);
        break;

        case 7:
            DrawCatagoryMenuIcon(uwDispID, 0 , 0 , 0 , 0 , 0 , 0 , 0);
        break;
#endif
    }
}

void MenuMainDrawBackCurtain(UINT16 uwDispID, GUI_COLOR bkColor)
{
    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
        AHC_OSDSetColor(uwDispID, TV_MENU_BK_COLOR);
    else
        AHC_OSDSetColor(uwDispID, OSD_COLOR_TITLE);

#if (DISP_WIDTH == 480) && defined(STRETCH_X) && defined(STRETCH_Y)
    AHC_OSDDrawFillRect(uwDispID, 0, STRETCH_Y(  0), STRETCH_X(320), STRETCH_Y( 36));
    AHC_OSDDrawFillRect(uwDispID, 0, STRETCH_Y(204), STRETCH_X(320), STRETCH_Y(240));

    AHC_OSDSetColor(uwDispID, bkColor);
    AHC_OSDDrawFillRect(uwDispID, 0, STRETCH_Y(40),  STRETCH_X(320), STRETCH_Y(200));

    AHC_OSDSetPenSize(uwDispID, STRETCH_Y(5));
    AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);
    AHC_OSDDrawFillRect(uwDispID, 0, STRETCH_Y(36),  STRETCH_X(320), STRETCH_Y(40));
    AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);
    AHC_OSDDrawFillRect(uwDispID, 0, STRETCH_Y(200), STRETCH_X(320), STRETCH_Y(204));
#else
    DispBufWidth = AHC_GET_ATTR_OSD_W(uwDispID);
    DispBufHeight = AHC_GET_ATTR_OSD_H(uwDispID);
        
    AHC_OSDDrawFillRect(uwDispID, 0, 0  , DispBufWidth, 36 );
    AHC_OSDDrawFillRect(uwDispID, 0, DispBufHeight-36, DispBufWidth, DispBufHeight);

    AHC_OSDSetColor(uwDispID, bkColor);

    AHC_OSDDrawFillRect(uwDispID, 0, 40,  DispBufWidth, DispBufHeight-40);

    AHC_OSDSetPenSize(uwDispID, 5);
    AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);

    AHC_OSDDrawFillRect(uwDispID, 0, 36,  DispBufWidth, 40);

    AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);
    AHC_OSDDrawFillRect(uwDispID, 0, DispBufHeight-40, DispBufWidth, DispBufHeight-36);
#endif  
}

void MenuMainDrawButtons(UINT16 uwDispID)
{
    #if defined(FONT_LARGE)
    // NOP
    #else   // FONT_LARGE   
    GUI_BITMAP      barID   = bmIcon_D_Up;
    UINT32          PageItemNum, ItemInterval;
    
    RECT tempRECT2 = POS_MENU_UP;
    RECT tempRECT3 = POS_MENU_DOWN;

    MenuDraw_GetMainMenuPageItem(uwDispID, barID, &PageItemNum, &ItemInterval);

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        tempRECT2.uiLeft += usShiftStringRight;
        tempRECT3.uiLeft += usShiftStringRight;
    }   

    tempRECT2.uiTop     = 40 + (ItemInterval-barID.YSize)/2;
    OSD_Draw_Icon(barID,     tempRECT2, uwDispID);

    barID = bmIcon_D_Down;
    tempRECT3.uiTop     = 40 + ItemInterval*(PageItemNum-1) + (ItemInterval-barID.YSize)/2;
    OSD_Draw_Icon(barID, tempRECT3, uwDispID);
    #endif  // FONT_LARGE
}

void MenuDrawItem(UINT16 uwDispID, PSMENUITEM pCurItem, int iItem, UINT32 iStrID, GUI_BITMAP barID, GUI_COLOR clrFont, GUI_COLOR clrBack, AHC_BOOL bCustom)
{
    UINT32          iDefValue = 0;
    PSMENUSTRUCT    pSubMenu;
    UINT32          PageItemNum, ItemInterval;

    UINT32  iDefStrID = 0xFFFFFFFF;
    INT16   wTextAlign  = GUI_TA_HCENTER|GUI_TA_VCENTER;
    RECT    tmpRECT     = RECT_MENU_MAIN_ITEM;
    RECT    tmpRECT1;

    pSubMenu = pCurItem->pSubMenu;

    if(pSubMenu)
        iDefValue = pSubMenu->pfMenuGetDefaultVal(pSubMenu);

    if(pSubMenu && iDefValue < pSubMenu->iNumOfItems)
        iDefStrID = pSubMenu->pItemsList[iDefValue]->uiStringId;

    if (bCustom == 2 /* display at center of screen */)
    {
        tmpRECT.uiLeft = (AHC_GET_ATTR_OSD_W(uwDispID) - barID.XSize) / 2;
    }
    else
    {
        #if defined(FONT_LARGE)
        tmpRECT.uiLeft -= ICON_UP_WIDTH;
        #endif
    }

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        tmpRECT.uiLeft += usShiftStringRight;
    }   

    tmpRECT.uiWidth     = barID.XSize;
    
    MenuDraw_GetMainMenuPageItem(uwDispID, barID, &PageItemNum, &ItemInterval);
    
    tmpRECT.uiTop       = 40 + ItemInterval*iItem + (ItemInterval-barID.YSize)/2;

    // Draw Current Value String
    switch(pSubMenu->iMenuId)
    {
        case MENUID_SUB_MENU_VOLUME:
        case MENUID_SUB_MENU_FW_VERSION_INFO:
        case MENUID_SUB_MENU_VMD_SHOT_NUM:
        case MENUID_SUB_MENU_TIMELAPSE_TIME:
        case MENUID_SUB_MENU_CONTRAST:
        case MENUID_SUB_MENU_SATURATION:
        case MENUID_SUB_MENU_SHARPNESS:
        case MENUID_SUB_MENU_GAMMA:
            {
                char    szv[16];

                tmpRECT1.uiLeft     = tmpRECT.uiLeft + barID.XSize;
                tmpRECT1.uiTop      = tmpRECT.uiTop;
                tmpRECT1.uiWidth    = AHC_GET_ATTR_OSD_W(uwDispID) - tmpRECT1.uiLeft;
                tmpRECT1.uiHeight   = tmpRECT.uiHeight - 2;

                if((pSubMenu->iMenuId==MENUID_SUB_MENU_VOLUME)||(pSubMenu->iMenuId==MENUID_SUB_MENU_CONTRAST)||(pSubMenu->iMenuId==MENUID_SUB_MENU_SHARPNESS)
                        ||(pSubMenu->iMenuId==MENUID_SUB_MENU_SATURATION)||(pSubMenu->iMenuId==MENUID_SUB_MENU_GAMMA))
                    sprintf(szv, "%d", (INT32)iDefValue);
                else if(pSubMenu->iMenuId==MENUID_SUB_MENU_VMD_SHOT_NUM)
                    sprintf(szv, "%d %s", m_ulVMDShotNum[iDefValue],  (char*)OSD_GetStringViaID(iDefStrID));
                else if(pSubMenu->iMenuId==MENUID_SUB_MENU_TIMELAPSE_TIME)
                    sprintf(szv, "%d %s", m_ulTimeLapseTime[iDefValue],  (char*)OSD_GetStringViaID(iDefStrID));
                else if(pSubMenu->iMenuId==MENUID_SUB_MENU_FW_VERSION_INFO)
                {
                    sprintf(szv, "%04d", AHC_GetMinorVersion());
                }
                ShowOSD_SetLanguage(uwDispID);
                OSD_ShowString(uwDispID, szv, NULL, tmpRECT1, clrFont, MENU_BACKGROUND_COLOR, wTextAlign);
            }
        break;

        default:
            if(bCustom == AHC_FALSE)
            {
                if(iDefStrID != 0xFFFFFFFF) {
                    tmpRECT1.uiLeft   = tmpRECT.uiLeft +  barID.XSize - 8;
                    tmpRECT1.uiTop    = tmpRECT.uiTop;
                    tmpRECT1.uiWidth  = AHC_GET_ATTR_OSD_W(uwDispID) - tmpRECT1.uiLeft;
                    tmpRECT1.uiHeight = tmpRECT.uiHeight - 2;
                    
                    OSD_ShowStringPool(uwDispID, iDefStrID, tmpRECT1, clrFont, MENU_BACKGROUND_COLOR, wTextAlign);
                }
            }
        break;
    }

    tmpRECT1.uiLeft   = tmpRECT.uiLeft;
    tmpRECT1.uiTop    = tmpRECT.uiTop + 1 ;
    tmpRECT1.uiWidth  = tmpRECT.uiWidth ;
    tmpRECT1.uiHeight = tmpRECT.uiHeight;
    OSD_Draw_Icon(barID, tmpRECT1, uwDispID);

    AHC_OSDSetColor(uwDispID, clrBack);

    tmpRECT1.uiLeft   = tmpRECT.uiLeft   + STR_RECT_OFFSET_X;
    tmpRECT1.uiTop    = tmpRECT.uiTop    + STR_RECT_OFFSET_Y;
    tmpRECT1.uiWidth  = tmpRECT.uiWidth  + STR_RECT_OFFSET_W;
    tmpRECT1.uiHeight = tmpRECT.uiHeight + STR_RECT_OFFSET_H;

    #ifdef SLIDE_STRING
    if(!AHC_IsTVConnectEx() && !AHC_IsHdmiConnect())
    {
        #define SLIDE_FOCUSED_STRING (0)

        int     slide;

        #if (SLIDE_FOCUSED_STRING==1)
        if(memcmp(&barID , &BMICON_MENUBAR_YELLOW,sizeof(GUI_BITMAP)) ==0)
        #else
        if(1)
        #endif
        {
            slide = IsSlideSting(iStrID);

            OSD_ShowStringPoolSlide(uwDispID, iStrID, tmpRECT1, clrFont, clrBack, wTextAlign, &slide);

            if (slide < 0) //[slide] will less than 0 when string length is more then drawing rectangle
            {
                RECT    brc;

                brc.uiLeft   = tmpRECT.uiLeft;
                brc.uiTop    = tmpRECT.uiTop + 1 ;
                brc.uiWidth  = tmpRECT.uiWidth ;
                brc.uiHeight = tmpRECT.uiHeight;
                StartSlideString(uwDispID, iStrID, tmpRECT1, barID, brc, clrFont, clrBack, -slide);
            }
        }
        else
        {
            int idx = GetSlideStringIdx(iStrID);

            if(idx!=0xFF)
                StopSlideStringIdx(idx);

            slide = 0;

            OSD_ShowStringPoolSlide(uwDispID, iStrID, tmpRECT1, clrFont, clrBack, wTextAlign, &slide);

            if(slide < 0)
                OSD_ShowStringPool(uwDispID, iStrID, tmpRECT1, clrFont, clrBack, GUI_TA_LEFT|GUI_TA_VCENTER);
        }
    }
    else
    #endif  // SLIDE_STRING
    {
        OSD_ShowStringPool(uwDispID, iStrID, tmpRECT1, clrFont, clrBack, wTextAlign);
    }
}

static UINT32 ulCurMenuPageItem;
UINT32 ulGetCurMenuPageItem(void)
{
    return ulCurMenuPageItem;
}

void ulSetCurMenuPageItem(UINT32 value)
{
    ulCurMenuPageItem = value;
}

void MenuDrawItemEx(UINT16 uwDispID, PSMENUSTRUCT pMenu)
{
    UINT32          i, iBegin, iEnd;
    PSMENUITEM      pCurItem;
    PSMENUSTRUCT    pSubMenu;
    UINT32          PageItemNum, ItemInterval;
    GUI_COLOR       TextClr;
    GUI_BITMAP      barID   = BMICON_MENUBAR_WHITE;

    MenuDraw_GetMainMenuPageItem(uwDispID, barID, &PageItemNum, &ItemInterval);//MAIN_MENU_PAGE_ITEM;
    ulSetCurMenuPageItem(PageItemNum);
    
    TextClr     = MENU_TEXT_COLOR;

    iBegin = ALIGN_DOWN( pMenu->iCurrentPos, PageItemNum );
    iEnd   = MIN( iBegin+PageItemNum, pMenu->iNumOfItems );

    for( i=iBegin; i<iEnd; i++ )
    {
        GUI_COLOR  colorBk  = OSD_COLOR_TRANSPARENT;
        
        barID   = BMICON_MENUBAR_WHITE;

        if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
        {
            colorBk = OSD_COLOR_TV_BACKGROUND;
        }

#if defined(FONT_LARGE)
        #ifndef CFG_DRAW_FORCE_SMALL_MENU_BAR //may be defined in config_xxx.h
        if( pMenu->iMenuId==MENUID_MAIN_MENU_MEDIA)
        #else
        if (0)
        #endif
        {
            barID = BMICON_MENUBAR_WHITE_XL;

            if( i == pMenu->iCurrentPos )
            {
                barID = BMICON_MENUBAR_YELLOW_XL;
            }
        }
        else
        {
            barID = BMICON_MENUBAR_WHITE;

            if( i == pMenu->iCurrentPos )
            {
                barID = BMICON_MENUBAR_YELLOW;
            }
        }
#else   // FONT_LARGE
        if( i == pMenu->iCurrentPos )
        {
            barID = BMICON_MENUBAR_YELLOW;
        }
#endif  // FONT_LARGE

        pCurItem = pMenu->pItemsList[i];
        pSubMenu = pCurItem->pSubMenu;

        MenuDrawItem(uwDispID, pCurItem, i%PageItemNum,
                     pCurItem->uiStringId, barID,
                     TextClr, colorBk, pSubMenu->bCustom);
    }
}

void MenuDrawTitle(UINT16 uwDispID, UINT32 uiStrID)
{

    RECT        tmpRECT  = POS_MENU_TITLE;
    GUI_COLOR   bkColor;

    #if (SUPPORT_TOUCH_PANEL)
    RECT RECTExit = RECT_TOUCH_BUTTON_MENU_EXIT;

    OSD_Draw_Icon(bmIcon_Return, RECTExit, uwDispID);
    #else
    #if defined(_OEM_DRAW_DEV_DV178_)
    tmpRECT.uiLeft = 10;
    #else
    tmpRECT.uiLeft = 5;
    #endif
    #endif

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        tmpRECT.uiLeft += usShiftStringRight;       
        bkColor = TV_MENU_BK_COLOR;
    }   
    else
    {
        bkColor = OSD_COLOR_TITLE;
    }   

#ifdef SLIDE_STRING
    {
        int slide = IsSlideSting(uiStrID);

        OSD_ShowStringPoolSlide(uwDispID, uiStrID, tmpRECT, MENU_TEXT_COLOR, bkColor, GUI_TA_LEFT|GUI_TA_VCENTER, &slide);

        if (slide < 0) //[slide] will less than 0 when string length is more then drawing rectangle
        {
            RECT    brc;
            GUI_BITMAP barID;

            memset(&barID, 0, sizeof(GUI_BITMAP));
            brc.uiLeft   = tmpRECT.uiLeft;
            brc.uiTop    = tmpRECT.uiTop + 1 ;
            brc.uiWidth  = tmpRECT.uiWidth ;
            brc.uiHeight = tmpRECT.uiHeight;
            StartSlideString(uwDispID, uiStrID, tmpRECT, barID, brc, MENU_TEXT_COLOR, bkColor, -slide);
        }
    }
#else
    OSD_ShowStringPool(uwDispID, uiStrID, tmpRECT, MENU_TEXT_COLOR, bkColor, GUI_TA_LEFT|GUI_TA_VCENTER);
#endif

}

void MenuDrawMainPageR1(UINT8 uwDispID, PSMENUSTRUCT pMenu)
{
    if( pMenu->uiStringId != -1 )
    {
        MenuDrawTitle(uwDispID, pMenu->uiStringId);
    }

    MenuDraw_UIMode(uwDispID);

    MenuDraw_MediaType(uwDispID);

    MenuDraw_BatteryStatus(uwDispID);
}

void MenuDrawMainPageR2L(UINT8 uwDispID, PSMENUSTRUCT pMenu)
{
    UINT32          PageItemNum, ItemInterval;
    UINT32  iCurPage, iTotalPage;
    GUI_BITMAP      barID   = BMICON_MENUBAR_WHITE;

    MenuDraw_GetMainMenuPageItem(uwDispID, barID, &PageItemNum, &ItemInterval);//MAIN_MENU_PAGE_ITEM;
    ulSetCurMenuPageItem(PageItemNum);

    // Up/Down Icons
    MenuMainDrawButtons(uwDispID);

    MenuDraw_GetPageInfo(&iCurPage, &iTotalPage, NULL, ulGetCurMenuPageItem());

    MenuDrawPageInfo(uwDispID, iCurPage, iTotalPage);

}

void MenuDrawMainPageR3(UINT8 uwDispID, PSMENUSTRUCT pMenu)
{
    #if (SUPPORT_TOUCH_PANEL)
    RECT RECTLeft   = RECT_TOUCH_BUTTON_MENU_LEFT;
    RECT RECTRight  = RECT_TOUCH_BUTTON_MENU_RIGHT;

    OSD_Draw_Icon(bmIcon_D_Left,  RECTLeft  ,uwDispID);
    OSD_Draw_Icon(bmIcon_D_Right, RECTRight ,uwDispID);
    #endif

    MenuMainDrawCatagory(uwDispID, GetCatagoryMenuID(pMenu));
}

void MenuDrawMainPageEx(UINT16 uwDispID, PSMENUSTRUCT pMenu)
{

#ifdef SLIDE_STRING
    StopSlideString();
#endif

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        MenuMainDrawBackCurtain(uwDispID, TV_MENU_BK_COLOR);
    }
    else
    {
        OSDDraw_ClearOvlDrawBuffer(uwDispID);
        MenuMainDrawBackCurtain(uwDispID, MENU_BACKGROUND_COLOR);
    }

    // Draw title and Icons (UI Mode, Card State, Battery State)
    MenuDrawMainPageR1(uwDispID, pMenu);
    // Vertical scoll bar
    MenuDrawMainPageR2L(uwDispID, pMenu);

    MenuDrawItemEx(uwDispID, pMenu);

    MenuDrawMainPageR3(uwDispID, pMenu);
}

void MenuDrawMainPage(PSMENUSTRUCT pMenu)
{
    UINT8 bID0 = 0, bID1 = 0;
    UINT16 dummy;
    UINT32 addr;
    UINT16 color;

#ifdef FLM_GPIO_NUM
    AHC_OSDSetActive(0, 0);
    AHC_OS_SleepMs(100);
#endif

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    AHC_OSDGetBufferAttr(bID0, &dummy, &dummy, &color, &addr);
 

        OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);
        OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);


    MenuDrawMainPageEx(bID0, pMenu);

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

void MenuDrawChangeItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
    PSMENUITEM      pPrevItem;
    PSMENUITEM      pCurItem;
    UINT32          PageItemNum;
    GUI_COLOR       TextClr;

    PageItemNum = ulGetCurMenuPageItem();
    TextClr     = MENU_TEXT_COLOR;


    if( !IS_SAME_PAGE( uiCurrItem, uiPrevItem, PageItemNum ) )
    {
        MenuDrawMainPage(pMenu);
    }
    else
    {
        UINT8           bID0    = 0;
        UINT8           bID1    = 0;
        PSMENUSTRUCT    pSubMenu;
        GUI_COLOR       clrFill = OSD_COLOR_TRANSPARENT;

        UINT32  iCurPage, iTotalPage;

        if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
        {
            clrFill = OSD_COLOR_TV_BACKGROUND;
        }

        OSDDraw_EnterMenuDrawing(&bID0, &bID1);

        //Region R2-L

        MenuDraw_GetPageInfo(&iCurPage, &iTotalPage, NULL, PageItemNum);
        MenuDrawPageInfo(bID0, iCurPage, iTotalPage);

        //Region R2-R
        pPrevItem = pMenu->pItemsList[uiPrevItem];
        pSubMenu  = pPrevItem->pSubMenu;

        //Draw Previous
        #if defined(FONT_LARGE)
        {
            const GUI_BITMAP    *pBar;

            #ifndef CFG_DRAW_FORCE_SMALL_MENU_BAR //may be defined in config_xxx.h
            if( pMenu->iMenuId==MENUID_MAIN_MENU_MEDIA)
            #else
            if (0)
            #endif
            {
                pBar = &BMICON_MENUBAR_WHITE_XL;
            }
            else
            {
                pBar = &BMICON_MENUBAR_WHITE;
            }
            MenuDrawItem(   bID0, pPrevItem, uiPrevItem%PageItemNum,
                            pPrevItem->uiStringId,
                            *pBar,
                            TextClr, clrFill, pSubMenu->bCustom);
        }
        #else   // FONT_LARGE
        MenuDrawItem(bID0, pPrevItem, uiPrevItem%PageItemNum, pPrevItem->uiStringId,
                     BMICON_MENUBAR_WHITE, TextClr, clrFill, pSubMenu->bCustom);
        #endif  // FONT_LARGE

        pCurItem = pMenu->pItemsList[uiCurrItem];
        pSubMenu = pCurItem->pSubMenu;

        //Draw current
        #if defined(FONT_LARGE)
        {
            const GUI_BITMAP    *pBar;

            #ifndef CFG_DRAW_FORCE_SMALL_MENU_BAR //may be defined in config_xxx.h
            if( pMenu->iMenuId==MENUID_MAIN_MENU_MEDIA)
            #else
            if (0)
            #endif
            {
                pBar = &BMICON_MENUBAR_YELLOW_XL;
            }
            else
            {
                pBar = &BMICON_MENUBAR_YELLOW;
            }
            MenuDrawItem(   bID0, pCurItem, uiCurrItem%PageItemNum, pCurItem->uiStringId,
                            *pBar, TextClr, clrFill, pSubMenu->bCustom);
        }
        #else   // FONT_LARGE
        MenuDrawItem(bID0, pCurItem, uiCurrItem%PageItemNum, pCurItem->uiStringId,
                     BMICON_MENUBAR_YELLOW, TextClr, clrFill, pSubMenu->bCustom);
        #endif

        OSDDraw_ExitMenuDrawing(&bID0, &bID1);
    }
}

#if 0
void ________SubMenu_Function_________(){ruturn;} //dummy
#endif

UINT8 GetSubMenuType(void)
{
    return m_ubSubPageType;
}

void SetSubMenuType(UINT8 ubType)
{
    m_ubSubPageType = ubType;
}

void GetSubItemRect(UINT16 uwDispID, int i, int iItems, RECT* pRc)
{
    #define BAR_GAP     (24)    // Change for SELF TIMER ICON, it paints over left-side button
    UINT16  SubItemTotalWidth = 0;
    
    SubItemTotalWidth = AHC_GET_ATTR_OSD_W(uwDispID);

    if( iItems <= 2 )
    {
        switch(i)
        {
            case 0: {SET_SUBRECT(pRc, (SubItemTotalWidth - pRc->uiWidth * 2 - BAR_GAP) / 2, 105, pRc->uiWidth, pRc->uiHeight); break;}
            case 1: {SET_SUBRECT(pRc, (SubItemTotalWidth + BAR_GAP) / 2,                     105, pRc->uiWidth, pRc->uiHeight); break;}
            default:{SET_SUBRECT(pRc, (SubItemTotalWidth - pRc->uiWidth * 2 - BAR_GAP) / 2, 105, pRc->uiWidth, pRc->uiHeight); break;}
        }
    }
    else if( iItems <= 4 )
    {
        switch(i)
        {
            case 0: {SET_SUBRECT(pRc, (SubItemTotalWidth - pRc->uiWidth * 2 - BAR_GAP) / 2,  80,  pRc->uiWidth, pRc->uiHeight); break;}
            case 1: {SET_SUBRECT(pRc, (SubItemTotalWidth + BAR_GAP) / 2,                      80,  pRc->uiWidth, pRc->uiHeight); break;}
            case 2: {SET_SUBRECT(pRc, (SubItemTotalWidth - pRc->uiWidth * 2 - BAR_GAP) / 2,  140, pRc->uiWidth, pRc->uiHeight); break;}
            case 3: {SET_SUBRECT(pRc, (SubItemTotalWidth + BAR_GAP) / 2,                      140, pRc->uiWidth, pRc->uiHeight); break;}
            default:{SET_SUBRECT(pRc, (SubItemTotalWidth - pRc->uiWidth * 2 - BAR_GAP) / 2,  80,  pRc->uiWidth, pRc->uiHeight); break;}
        }
    }
    else
    {
        if(AHC_IsHdmiConnect())
        {
            if(MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_1080P)
            {
                switch(i)
                {
                    case 0: {SET_SUBRECT(pRc, 90,  52 , pRc->uiWidth, pRc->uiHeight);break;}
                    case 1: {SET_SUBRECT(pRc, 260, 52 , pRc->uiWidth, pRc->uiHeight);break;}
                    case 2: {SET_SUBRECT(pRc, 90,  115, pRc->uiWidth, pRc->uiHeight);break;}
                    case 3: {SET_SUBRECT(pRc, 260, 115, pRc->uiWidth, pRc->uiHeight);break;}
                    case 4: {SET_SUBRECT(pRc, 90,  180, pRc->uiWidth, pRc->uiHeight);break;}
                    case 5: {SET_SUBRECT(pRc, 260, 180, pRc->uiWidth, pRc->uiHeight);break;}
                    default:{SET_SUBRECT(pRc, 260, 170, pRc->uiWidth, pRc->uiHeight);break;}
                }                   
            }
            else
            {
                switch(i)
                {
                    case 0: {SET_SUBRECT(pRc, 90,  52 , pRc->uiWidth, pRc->uiHeight);break;}
                    case 1: {SET_SUBRECT(pRc, 260, 52 , pRc->uiWidth, pRc->uiHeight);break;}
                    case 2: {SET_SUBRECT(pRc, 90,  115, pRc->uiWidth, pRc->uiHeight);break;}
                    case 3: {SET_SUBRECT(pRc, 260, 115, pRc->uiWidth, pRc->uiHeight);break;}
                    case 4: {SET_SUBRECT(pRc, 90,  180, pRc->uiWidth, pRc->uiHeight);break;}
                    case 5: {SET_SUBRECT(pRc, 260, 180, pRc->uiWidth, pRc->uiHeight);break;}
                    default:{SET_SUBRECT(pRc, 260, 170, pRc->uiWidth, pRc->uiHeight);break;}
                }   
            }   
        }   
        else if(AHC_IsTVConnectEx())
        {
            int x0, x1;
            
            x0 =  (SubItemTotalWidth - pRc->uiWidth * 2 - BAR_GAP) / 2 + (28); //STRETCH_X(70);
            x1 =  (SubItemTotalWidth + BAR_GAP) / 2 + (28);//   STRETCH_X(x0 + 28 /* Icon Width */ + pRc->uiWidth);
            
            switch(i)
            {
                case 0: {SET_SUBRECT(pRc, x0, (50) , pRc->uiWidth, pRc->uiHeight);break;}
                case 1: {SET_SUBRECT(pRc, x1, (50) , pRc->uiWidth, pRc->uiHeight);break;}
                case 2: {SET_SUBRECT(pRc, x0, (103), pRc->uiWidth, pRc->uiHeight);break;}
                case 3: {SET_SUBRECT(pRc, x1, (103), pRc->uiWidth, pRc->uiHeight);break;}
                case 4: {SET_SUBRECT(pRc, x0, (156), pRc->uiWidth, pRc->uiHeight);break;}
                case 5: {SET_SUBRECT(pRc, x1, (156), pRc->uiWidth, pRc->uiHeight);break;}
                case 6: {SET_SUBRECT(pRc, x0, (208), pRc->uiWidth, pRc->uiHeight);break;}
                case 7: {SET_SUBRECT(pRc, x1, (208), pRc->uiWidth, pRc->uiHeight);break;}
                default:{SET_SUBRECT(pRc, x0, (210), pRc->uiWidth, pRc->uiHeight);break;}
            }

        }
        else
        {           
            int x0, x1;
            
            x0 =  (SubItemTotalWidth - pRc->uiWidth * 2 - BAR_GAP) / 2 + (28); //STRETCH_X(70);
            x1 =  (SubItemTotalWidth + BAR_GAP) / 2 + (28);//   STRETCH_X(x0 + 28 /* Icon Width */ + pRc->uiWidth);
            
            switch(i)
            {
                case 0: {SET_SUBRECT(pRc, x0, (50) , pRc->uiWidth, pRc->uiHeight);break;}
                case 1: {SET_SUBRECT(pRc, x1, (50) , pRc->uiWidth, pRc->uiHeight);break;}
                case 2: {SET_SUBRECT(pRc, x0, (103), pRc->uiWidth, pRc->uiHeight);break;}
                case 3: {SET_SUBRECT(pRc, x1, (103), pRc->uiWidth, pRc->uiHeight);break;}
                case 4: {SET_SUBRECT(pRc, x0, (156), pRc->uiWidth, pRc->uiHeight);break;}
                case 5: {SET_SUBRECT(pRc, x1, (156), pRc->uiWidth, pRc->uiHeight);break;}
                case 6: {SET_SUBRECT(pRc, x0, (208), pRc->uiWidth, pRc->uiHeight);break;}
                case 7: {SET_SUBRECT(pRc, x1, (208), pRc->uiWidth, pRc->uiHeight);break;}
                default:{SET_SUBRECT(pRc, x0, (210), pRc->uiWidth, pRc->uiHeight);break;}
            }
        }   
    }
}

void DrawSubItem(UINT16 uwDispID, int iItem, int iTotalItems, UINT8 uLang, UINT32 iStrID, const GUI_BITMAP* IconID, UINT32 barId, GUI_COLOR clrFont, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{
    #if defined(FONT_LARGE)

    RECT    rc = POS_MENU_ITEM;
    RECT    tmpRECT;

    if(AHC_TRUE == AHC_Charger_GetStatus())
    {
        AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);

        if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
            AHC_OSDSetBkColor(uwDispID, OSD_COLOR_TV_BACKGROUND);
        else
            AHC_OSDSetBkColor(uwDispID, MENU_BACKGROUND_COLOR);
    }

    MenuDrawPageInfo(uwDispID, iItem / SUB_MENU_PAGE_ITEM + 1,
                     (iTotalItems + SUB_MENU_PAGE_ITEM - 1) / SUB_MENU_PAGE_ITEM);

    rc.uiWidth   = vBarSet[0].bar[BAR_STATE_WHT]->XSize;
    rc.uiLeft    = (AHC_GET_ATTR_OSD_W(uwDispID) - rc.uiWidth) >> 1;
    rc.uiTop    += ((rc.uiHeight+OSD_MENU_ITEM_INTERVAL) * (iItem % SUB_MENU_PAGE_ITEM));

    if (IconID != NULL && IconID != &bmIcon_Dummy)
    {
        int     offset;

        if((iTotalItems == SUB_MENU_PAGE_ITEM-2) && ( IconID->XSize >= 50 ))
            rc.uiLeft = rc.uiLeft + 10;

        offset = (IconID->XSize >= 50)?(50):(32);

        AHC_OSDDrawBitmap(uwDispID, IconID, rc.uiLeft - offset, rc .uiTop);
        rc.uiLeft += (IconID->XSize - offset);
    }

    if( clrSelect != 0 )
    {
        AHC_OSDSetColor(uwDispID, clrSelect);
        AHC_OSDDrawFillRoundedRect(uwDispID, rc.uiLeft+2, rc.uiTop+rc.uiHeight-7, rc.uiLeft+rc.uiWidth-2, rc.uiTop+rc.uiHeight-2, RECT_ROUND_RADIUS );
    }

    OSD_Draw_Icon(BAR(barId), rc, uwDispID);

    tmpRECT.uiLeft   = rc.uiLeft + 2;
    tmpRECT.uiTop    = rc.uiTop;
    tmpRECT.uiWidth  = PBAR(barId)->XSize;
    tmpRECT.uiHeight = PBAR(barId)->YSize;

    ShowOSD_SetLanguageEx(uwDispID, uLang);
    OSD_ShowString( uwDispID, (char*)OSD_GetStringViaID(iStrID), NULL,
                    tmpRECT, clrFont, clrBack,
                    GUI_TA_HCENTER|GUI_TA_VCENTER);

    #else // defined(FONT_LARGE)

    RECT    rc, tmpRECT;
    UINT32  iMenuId = GetCurrentMenu()->iMenuId;

    if(AHC_TRUE == AHC_Charger_GetStatus())
    {
        AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);

        if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
            AHC_OSDSetBkColor(uwDispID, OSD_COLOR_TV_BACKGROUND);
        else
            AHC_OSDSetBkColor(uwDispID, MENU_BACKGROUND_COLOR);
    }

    rc.uiWidth  = BAR(barId).XSize;
    rc.uiHeight = BAR(barId).YSize;
    GetSubItemRect(uwDispID, iItem%SUB_MENU_PAGE_ITEM, iTotalItems, &rc );

    OSD_Draw_Icon(BAR(barId), rc, uwDispID);

    if(0/*AHC_IsTVConnectEx() || AHC_IsHdmiConnect()*/)
    {
        tmpRECT.uiLeft   = rc.uiLeft            + STR_RECT_OFFSET_X;
        tmpRECT.uiTop    = rc.uiTop             + 3;
        tmpRECT.uiWidth  = PBAR(barId)->XSize   + STR_RECT_OFFSET_W;
        tmpRECT.uiHeight = PBAR(barId)->YSize   + (-13);
    }
    else
    {
        tmpRECT.uiLeft   = rc.uiLeft;
        tmpRECT.uiTop    = rc.uiTop;
        tmpRECT.uiWidth  = PBAR(barId)->XSize;
        tmpRECT.uiHeight = PBAR(barId)->YSize;
    }

    ShowOSD_SetLanguageEx(uwDispID, uLang);

    switch(iMenuId)
    {
        case MENUID_SUB_MENU_VMD_SHOT_NUM:
        case MENUID_SUB_MENU_TIMELAPSE_TIME:
        {
            char sz[20]= {0};

            if(iMenuId==MENUID_SUB_MENU_TIMELAPSE_TIME)
                sprintf(sz, "%d %s", m_ulTimeLapseTime[iItem], (char*)OSD_GetStringViaID(iStrID));
            else if(iMenuId==MENUID_SUB_MENU_VMD_SHOT_NUM)
                sprintf(sz, "%d %s", m_ulVMDShotNum[iItem], (char*)OSD_GetStringViaID(iStrID));

            OSD_ShowString( uwDispID, sz, NULL,
                            tmpRECT, clrFont, clrBack,
                            GUI_TA_HCENTER|GUI_TA_VCENTER);
        }
        break;

        default:
        #ifdef __SLIDE_STRING__ // Under Coding
        if(!AHC_IsTVConnectEx() && !AHC_IsHdmiConnect())
        {
            #define SLIDE_FOCUSED_STRING (0)

            int     slide;
            RECT    tmpRECT1;
            INT16   wTextAlign  = GUI_TA_HCENTER|GUI_TA_VCENTER;

            tmpRECT1.uiLeft   = tmpRECT.uiLeft   + STR_RECT_OFFSET_X;
            tmpRECT1.uiTop    = tmpRECT.uiTop    + STR_RECT_OFFSET_Y;
            tmpRECT1.uiWidth  = tmpRECT.uiWidth  + STR_RECT_OFFSET_W;
            tmpRECT1.uiHeight = tmpRECT.uiHeight + STR_RECT_OFFSET_H;
            if(1)
            {
                slide = IsSlideSting(iStrID);

                OSD_ShowStringPoolSlide(uwDispID, iStrID, tmpRECT1, clrFont, clrBack, wTextAlign, &slide);
                slide = -20;
                if (slide < 0) //[slide] will less than 0 when string length is more then drawing rectangle
                {
                    StartSlideString(uwDispID, iStrID, tmpRECT1, BAR(barId), rc, clrFont, clrBack, -slide);
                }
            }
            else
            {
                int idx = GetSlideStringIdx(iStrID);

                if(idx!=0xFF)
                    StopSlideStringIdx(idx);

                slide = 0;

                OSD_ShowStringPoolSlide(uwDispID, iStrID, tmpRECT1, clrFont, clrBack, wTextAlign, &slide);

                if(slide < 0)
                    OSD_ShowStringPool(uwDispID, iStrID, tmpRECT1, clrFont, clrBack, GUI_TA_LEFT|GUI_TA_VCENTER);
            }
        }
        else
        #endif
            OSD_ShowString( uwDispID, (char*)OSD_GetStringViaID(iStrID), NULL,
                            tmpRECT, clrFont, clrBack,
                            GUI_TA_HCENTER|GUI_TA_VCENTER);
        break;
    }

    #endif  // FONT_LARGE
}

void DrawSubItemEx(UINT16 uwDispID, PSMENUSTRUCT pMenu)
{
    UINT32      i, iBegin, iEnd;
    UINT32      barType = BAR_NORMAL_TYPE;
    UINT32      uPageItemNum;
    GUI_COLOR   TextClr;
    UINT8       uLang;

    // To find some Submenu text is longer the width of default button
    // to use wide button
    #if !defined(FONT_LARGE)
    BAR_TYPE(barType, pMenu);
    #endif

    uPageItemNum = SUB_MENU_PAGE_ITEM;
    TextClr      = MENU_TEXT_COLOR;

    uLang  = MenuDraw_GetDefaultLanguage(pMenu);

    iBegin = ALIGN_DOWN( pMenu->iCurrentPos, uPageItemNum );
    iEnd   = MIN( iBegin + uPageItemNum, pMenu->iNumOfItems );

    for( i=iBegin; i<iEnd; i++ )
    {
        UINT32      barState;
        UINT8       idx = i;
        GUI_COLOR   bkColor = OSD_COLOR_TRANSPARENT;

        if(pMenu->iNumOfItems > 1)
        {
            if(( i == pMenu->iCurrentPos ) && ( i != pMenu->pfMenuGetDefaultVal(pMenu) ))
            {
                barState = BAR_STATE_YEL;
            }
            else if(( i == pMenu->iCurrentPos ) && ( i == pMenu->pfMenuGetDefaultVal(pMenu) ))
            {
                barState = BAR_STATE_YEL_DEF;
            }
            else if(( i != pMenu->iCurrentPos ) && ( i == pMenu->pfMenuGetDefaultVal(pMenu) ))
            {
                barState = BAR_STATE_WHT_DEF;
            }
            else
            {
                barState = BAR_STATE_WHT;
            }
        }
        else
        {
            barState = BAR_STATE_YEL;
        }


        DrawSubItem(uwDispID, idx, pMenu->iNumOfItems,
                    uLang, pMenu->pItemsList[i]->uiStringId,
                    pMenu->pItemsList[i]->bmpIcon,
                    MAKE_BAR_ID(barType, barState),
                    TextClr, bkColor, 0x0);
    }
}

void MenuDrawSubBackCurtain(UINT16 uwDispID, GUI_COLOR bkColor)
{
    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
        AHC_OSDSetColor(uwDispID, TV_MENU_BK_COLOR);
    else
        AHC_OSDSetColor(uwDispID, OSD_COLOR_TITLE);

    DispBufWidth = AHC_GET_ATTR_OSD_W(uwDispID);
    DispBufHeight = AHC_GET_ATTR_OSD_H(uwDispID);
        
    AHC_OSDDrawFillRect(uwDispID, 0, 0  , DispBufWidth, 36 );
    AHC_OSDDrawFillRect(uwDispID, 0, DispBufHeight-36, DispBufWidth, DispBufHeight);

    AHC_OSDSetColor(uwDispID, bkColor);

    AHC_OSDDrawFillRect(uwDispID, 0, 40,  DispBufWidth, DispBufHeight-40);

    AHC_OSDSetPenSize(uwDispID, 5);
    AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);

    AHC_OSDDrawFillRect(uwDispID, 0, 36,  DispBufWidth, 40);
    AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);
    AHC_OSDDrawFillRect(uwDispID, 0, DispBufHeight-40, DispBufWidth, DispBufHeight-36);

}

void MenuDrawSubBackCurtainGrid(UINT16 uwDispID)
{
}

void MenuDrawSubBackCurtainConfirm(UINT16 uwDispID)
{
}

void MenuDrawSubPageInfo(UINT16 uwDispID, int uiCurPage, int uiTotalPage)
{
}

void MenuDrawSubMenuDescription(UINT16 uwDispID, UINT32 iStrID)
{
    RECT    tempRECT   = RECT_MENU_SUB_DESC;
    INT16   wTextAlign = GUI_TA_LEFT|GUI_TA_VCENTER;

    GUI_COLOR bkColor;

    tempRECT.uiTop = AHC_GET_ATTR_OSD_W(uwDispID)-34;

    bkColor = (AHC_IsTVConnectEx() || AHC_IsHdmiConnect())?(TV_MENU_BK_COLOR):(OSD_COLOR_TITLE);

    #ifdef SLIDE_STRING
    {
        int slide = IsSlideSting(iStrID);

        OSD_ShowStringPoolSlide(uwDispID, iStrID, tempRECT, MENU_TEXT_COLOR, bkColor, wTextAlign, &slide);

        if (slide < 0) //[slide] will less than 0 when string length is more then drawing rectangle
        {
            RECT    brc;
            GUI_BITMAP barID;

            memset(&barID, 0, sizeof(GUI_BITMAP));
            brc.uiLeft   = tempRECT.uiLeft;
            brc.uiTop    = tempRECT.uiTop + 1 ;
            brc.uiWidth  = tempRECT.uiWidth ;
            brc.uiHeight = tempRECT.uiHeight;
            StartSlideString(uwDispID, iStrID, tempRECT, barID, brc, MENU_TEXT_COLOR, bkColor, -slide);
        }
    }
    #else
    OSD_ShowStringPool(uwDispID, iStrID, tempRECT, MENU_TEXT_COLOR, bkColor, wTextAlign);
    #endif
}

void MenuDrawSubButtons(UINT16 uwDispID)
{
    #if defined(FONT_LARGE)
    // NOP
    #else   // FONT_LARGE   
    GUI_BITMAP      barID   = bmIcon_D_Up;
    UINT32          PageItemNum, ItemInterval;
    
    RECT tempRECT2 = POS_MENU_UP;
    RECT tempRECT3 = POS_MENU_DOWN;

    MenuDraw_GetMainMenuPageItem(uwDispID, barID, &PageItemNum, &ItemInterval);

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        tempRECT2.uiLeft += usShiftStringRight;
        tempRECT3.uiLeft += usShiftStringRight;
    }   

    tempRECT2.uiTop     = 40 + (ItemInterval-barID.YSize)/2;
    OSD_Draw_Icon(barID,     tempRECT2, uwDispID);

    barID = bmIcon_D_Down;
    tempRECT3.uiTop     = 40 + ItemInterval*(PageItemNum-1) + (ItemInterval-barID.YSize)/2;
    OSD_Draw_Icon(barID, tempRECT3, uwDispID);
    #endif  // FONT_LARGE
}

void MenuDrawSubTitle(UINT16 uwDispID, UINT32 iStrID)
{
    RECT      tmpRECT = POS_MENU_TITLE;
    GUI_COLOR bkColor;

    #if (SUPPORT_TOUCH_PANEL)
    RECT RECTExit = RECT_TOUCH_BUTTON_MENU_EXIT;

    OSD_Draw_Icon(bmIcon_Return, RECTExit, uwDispID);
    #else       // #if (SUPPORT_TOUCH_PANEL)
    tmpRECT.uiLeft = 5;
    #endif      // #if (SUPPORT_TOUCH_PANEL)

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        tmpRECT.uiLeft += usShiftStringRight;       
        bkColor = TV_MENU_BK_COLOR;
    }   
    else
    {
        bkColor = OSD_COLOR_TITLE;
    }   

    #ifdef SLIDE_STRING
    {
        int slide = IsSlideSting(iStrID);

        OSD_ShowStringPoolSlide(uwDispID, iStrID, tmpRECT, MENU_TEXT_COLOR, bkColor, GUI_TA_LEFT|GUI_TA_VCENTER, &slide);

        if (slide < 0) //[slide] will less than 0 when string length is more then drawing rectangle
        {
            RECT    brc;
            GUI_BITMAP barID;

            memset(&barID, 0, sizeof(GUI_BITMAP));
            brc.uiLeft   = tmpRECT.uiLeft;
            brc.uiTop    = tmpRECT.uiTop + 1 ;
            brc.uiWidth  = tmpRECT.uiWidth ;
            brc.uiHeight = tmpRECT.uiHeight;
            StartSlideString(uwDispID, iStrID, tmpRECT, barID, brc, MENU_TEXT_COLOR, bkColor, -slide);
        }
    }
    #else
    OSD_ShowStringPool(uwDispID, iStrID, tmpRECT, MENU_TEXT_COLOR, bkColor, GUI_TA_LEFT|GUI_TA_VCENTER);
    #endif
}

void MenuDraw2ndSubPageInit(UINT16 uwDispID, PSMENUSTRUCT pMenu, UINT32 CurtainType)
{
}

void MenuDrawSubPageR1(UINT8 uwDispID, PSMENUSTRUCT pMenu)
{
    if (GetSubMenuType()==SUBMENU_SUBPAGE)
    {
        if( pMenu->uiStringId != -1 )
        {
            MenuDrawSubTitle(uwDispID, pMenu->uiStringId);
        }

        MenuDraw_MediaType(uwDispID);

        MenuDraw_BatteryStatus(uwDispID);
    }
}

void MenuDrawSubPageR2L(UINT8 uwDispID, PSMENUSTRUCT pMenu)
{
    UINT32  iCurPage, iTotalPage;

    if( pMenu->iNumOfItems > SUB_MENU_PAGE_ITEM - 2 )
    {
        // Up/Down Icons
        MenuDrawSubButtons(uwDispID);

        MenuDraw_GetPageInfo(&iCurPage, &iTotalPage, NULL, SUB_MENU_PAGE_ITEM);

        MenuDrawPageInfo(uwDispID, iCurPage, iTotalPage);
    }
}

void MenuDrawSubPageR3(UINT8 uwDispID, PSMENUSTRUCT pMenu)
{
    if (GetSubMenuType()==SUBMENU_SUBPAGE)
    {
        if(pMenu->uiStringDescription != NULL)
        {
            MenuDrawSubMenuDescription(uwDispID, pMenu->uiStringDescription);
        }
    }
}

void MenuDrawSubPage(PSMENUSTRUCT pMenu)
{
    UINT8   bID0 = 0, bID1 = 0;

#ifdef FLM_GPIO_NUM
    AHC_OSDSetActive(0, 0);
    AHC_OS_SleepMs(100);
#endif

#ifdef SLIDE_STRING
    StopSlideString();
#endif

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    OSDDraw_ClearOvlDrawBuffer(bID0);

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
        MenuDrawSubBackCurtain(bID0, TV_MENU_BK_COLOR);
    else
        MenuDrawSubBackCurtain(bID0, MENU_BACKGROUND_COLOR);

    // Title, Battery, Media Type
    MenuDrawSubPageR1(bID0, pMenu);
    // Up/Down Icons, Page Info.
    MenuDrawSubPageR2L(bID0, pMenu);

    DrawSubItemEx(bID0, pMenu);
    // Draw Sub-Menu Description
    MenuDrawSubPageR3(bID0, pMenu);

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

void MenuDrawChangeSubItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
    UINT8     bID0 = 0;
    UINT8     bID1 = 0;
    UINT8     SubPageItem = SUB_MENU_PAGE_ITEM;
    UINT8     uLang;

    #if defined(FONT_LARGE)
    SubPageItem = SUB_MENU_PAGE_ITEM;
    #else   // FONT_LARGE
    if ( pMenu->iNumOfItems <= 2 )
        SubPageItem = 2;
    else if ( pMenu->iNumOfItems <= 4 )
        SubPageItem = 4;
    else
        SubPageItem = SUB_MENU_PAGE_ITEM;
    #endif  // FONT_LARGE

    uLang = MenuDraw_GetDefaultLanguage(pMenu);

    if( !IS_SAME_PAGE( uiCurrItem, uiPrevItem, SubPageItem ) )
    {
        MenuDrawSubPage(pMenu);
    }
    else
    {
        GUI_COLOR   clrFill     = OSD_COLOR_TRANSPARENT;
        GUI_COLOR   clrSelect   = 0x0;
        GUI_COLOR   clrText     = MENU_TEXT_COLOR;
        UINT32      idx;
        UINT32      barState;
        UINT32      barType     = BAR_NORMAL_TYPE;

        OSDDraw_EnterMenuDrawing(&bID0, &bID1);


        BAR_TYPE(barType, pMenu); // Set BAR Type for Normal, Large or Small to show, the BAR TYPE is for different string length on it.

        //Draw Previous
        {
            if( pMenu->iSelected == uiPrevItem )
                clrSelect = OSD_COLOR_SELECTED;
            else
                clrSelect = 0;

            barState = BAR_STATE_WHT;

            if(( pMenu->uiStatus == MENU_STATUS_PRESSED ) || ( uiPrevItem != pMenu->pfMenuGetDefaultVal(pMenu)))
                barState = BAR_STATE_WHT;
            else if ( uiPrevItem == pMenu->pfMenuGetDefaultVal(pMenu))
                barState = BAR_STATE_WHT_DEF;

            idx = uiPrevItem;

            DrawSubItem(bID0, idx, pMenu->iNumOfItems,
                        uLang, pMenu->pItemsList[uiPrevItem]->uiStringId,
                        pMenu->pItemsList[uiPrevItem]->bmpIcon,
                        MAKE_BAR_ID(barType, barState),
                        clrText, clrFill, clrSelect);
        }

        //Draw Previous Selected
        if(uiPreSelected / SubPageItem == uiCurrItem / SubPageItem)
        {
            if( pMenu->iSelected == uiPreSelected )
                clrSelect = OSD_COLOR_SELECTED;
            else
                clrSelect = 0;

            idx = uiPreSelected;

            if(( pMenu->uiStatus == MENU_STATUS_PRESSED ) || ( uiPreSelected != pMenu->pfMenuGetDefaultVal(pMenu)))
                barState = BAR_STATE_WHT;
            else if( uiPreSelected == pMenu->pfMenuGetDefaultVal(pMenu))
                barState = BAR_STATE_WHT_DEF;

            DrawSubItem(bID0, idx, pMenu->iNumOfItems,
                        uLang, pMenu->pItemsList[uiPreSelected]->uiStringId,
                        pMenu->pItemsList[uiPreSelected]->bmpIcon,
                        MAKE_BAR_ID(barType, barState),
                        clrText, clrFill, clrSelect);
        }

        //Draw current
        {
            if( pMenu->iSelected == uiCurrItem )
                clrSelect = OSD_COLOR_SELECTED;
            else
                clrSelect = 0;

            idx = uiCurrItem;

            if( uiCurrItem == pMenu->pfMenuGetDefaultVal(pMenu))
                barState = BAR_STATE_YEL_DEF;
            else
                barState = BAR_STATE_YEL;

            DrawSubItem(bID0, idx, pMenu->iNumOfItems,
                        uLang, pMenu->pItemsList[uiCurrItem]->uiStringId,
                        pMenu->pItemsList[uiCurrItem]->bmpIcon,
                        MAKE_BAR_ID(barType, barState),
                        clrText, clrFill, clrSelect);
        }

        OSDDraw_ExitMenuDrawing(&bID0, &bID1);
    }
}

#if 0
void ________ConfirmMenu_Function_________(){ruturn;} //dummy
#endif

void DrawSubItem_ConfirmPage(UINT16 uwDispID, UINT16 uwMenuID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, int bid, GUI_COLOR clrFont, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{
    RECT        rc, tmpRECT;
    RECT        RECTStr     = POS_MENU_CONFIRM;
    INT16       wTextAlign  = GUI_TA_LEFT|GUI_TA_VCENTER;
    GUI_COLOR   TextBkColor;

    #define STR_GAP     (30)

    TextBkColor = OSD_COLOR_BLACK;

    rc.uiWidth  = BAR(bid).XSize;
    rc.uiHeight = BAR(bid).YSize;
    GetSubItemRect(uwDispID, iItem%CONFIRM_MENU_PAGE_ITEM, CONFIRM_MENU_PAGE_ITEM, &rc );

    RECTStr.uiWidth = AHC_GET_ATTR_OSD_W(uwDispID) - RECTStr.uiLeft;

    switch(uwMenuID)
    {
        case MENUID_SUB_MENU_RESET_SETUP:
            OSD_ShowStringPool(uwDispID,IDS_DS_RESET_SETUP_CONFIRM, RECTStr, clrFont, TextBkColor, wTextAlign);
            RECTStr.uiTop += STR_GAP;
            OSD_ShowStringPool(uwDispID,IDS_DS_RESET_INFO,          RECTStr, clrFont, TextBkColor, wTextAlign);
        break;

        case MENUID_SUB_MENU_FORMAT_SD_CARD:
            OSD_ShowStringPool(uwDispID,IDS_DS_FORMAT_CARD_CONFIRM, RECTStr, clrFont, TextBkColor, wTextAlign);
            RECTStr.uiTop += STR_GAP;
            OSD_ShowStringPool(uwDispID,IDS_DS_DATA_DELETED,        RECTStr, clrFont, TextBkColor, wTextAlign);
        break;

        #if (MENU_MEDIA_FORMAT_INT_MEM_EN)
        case MENUID_SUB_MENU_FORMAT_INTMEM:
            OSD_ShowStringPool(uwDispID,IDS_DS_FORMAT_INTMEM_CONFIRM, RECTStr, clrFont, TextBkColor, wTextAlign);
            RECTStr.uiTop += STR_GAP;
            OSD_ShowStringPool(uwDispID,IDS_DS_DATA_DELETED,          RECTStr, clrFont, TextBkColor, wTextAlign);
        break;
        #endif

        case MENUID_SUB_MENU_DELETE_ALL_VIDEO:
        case MENUID_SUB_MENU_DELETE_ALL_IMAGE:
            OSD_ShowStringPool(uwDispID,IDS_DS_DELETE_ALL_CONFIRM, RECTStr, clrFont, TextBkColor, wTextAlign);
        break;

        case MENUID_SUB_MENU_PROTECT_ALL_VIDEO:
        case MENUID_SUB_MENU_PROTECT_ALL_IMAGE:
            OSD_ShowStringPool(uwDispID,IDS_DS_PROTECT_ALL_CONFIRM, RECTStr, clrFont, TextBkColor, wTextAlign);
        break;

        case MENUID_SUB_MENU_UNPROTECT_ALL_VIDEO:
        case MENUID_SUB_MENU_UNPROTECT_ALL_IMAGE:
            OSD_ShowStringPool(uwDispID,IDS_DS_UNPROTECT_ALL, RECTStr, clrFont, TextBkColor, wTextAlign);
        break;
    }

    rc.uiTop = RECTStr.uiTop + 50;

    if( clrSelect != 0 )
    {
        AHC_OSDSetColor(uwDispID, clrSelect);
        AHC_OSDDrawFillRoundedRect(uwDispID, rc.uiLeft+2, rc.uiTop+rc.uiHeight-7, rc.uiLeft+rc.uiWidth-2, rc.uiTop+rc.uiHeight-2, RECT_ROUND_RADIUS);
    }

    OSD_Draw_Icon(BAR(bid), rc, uwDispID);

    tmpRECT.uiLeft   = rc.uiLeft    + STR_RECT_OFFSET_X;
    tmpRECT.uiTop    = rc.uiTop     + STR_RECT_OFFSET_Y;
    tmpRECT.uiWidth  = rc.uiWidth   + STR_RECT_OFFSET_W;
    tmpRECT.uiHeight = rc.uiHeight  + STR_RECT_OFFSET_H;
    OSD_ShowStringPool(uwDispID, iStrID, tmpRECT, clrFont, clrBack, GUI_TA_HCENTER|GUI_TA_VCENTER);
}

void MenuDrawSubPage_ConfirmPage(PSMENUSTRUCT pMenu)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    UINT32 i, iBegin, iEnd;

#ifdef SLIDE_STRING
    StopSlideString();
#endif

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    iBegin = ALIGN_DOWN( pMenu->iCurrentPos, CONFIRM_MENU_PAGE_ITEM );
    iEnd   = MIN( iBegin+CONFIRM_MENU_PAGE_ITEM, pMenu->iNumOfItems);

    OSDDraw_ClearOvlDrawBuffer(bID0);
    MenuDrawSubBackCurtain(bID0, OSD_COLOR_BLACK);

    MenuDrawSubPageR1(bID0, pMenu);

    for( i=iBegin; i<iEnd; i++ )
    {
        GUI_COLOR   colorBk = OSD_COLOR_TRANSPARENT;
        int         bid     = MAKE_BAR_ID(BAR_NARROW_TYPE, BAR_STATE_WHT);

        if( i == pMenu->iCurrentPos )
        {
            bid = MAKE_BAR_ID(BAR_NARROW_TYPE, BAR_STATE_YEL);
        }
        DrawSubItem_ConfirmPage(bID0, pMenu->iMenuId, i, pMenu->iNumOfItems, pMenu->pItemsList[i]->uiStringId, pMenu->pItemsList[i]->bmpIcon, bid, MENU_TEXT_COLOR, colorBk, 0x0);
    }

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

void MenuDrawChangeSubItem_ConfirmPage(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
    UINT8     bID0 = 0;
    UINT8     bID1 = 0;
    GUI_COLOR clrFill   = OSD_COLOR_TRANSPARENT;
    GUI_COLOR clrSelect = 0x0;

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    if( pMenu->iSelected == uiPrevItem )
        clrSelect = OSD_COLOR_SELECTED;
    else
        clrSelect = 0;

    //Draw Previous
    DrawSubItem_ConfirmPage(bID0, pMenu->iMenuId,
                            uiPrevItem, pMenu->iNumOfItems,
                            pMenu->pItemsList[uiPrevItem]->uiStringId,
                            pMenu->pItemsList[uiPrevItem]->bmpIcon,
                            MAKE_BAR_ID(BAR_NARROW_TYPE, BAR_STATE_WHT),
                            MENU_TEXT_COLOR, clrFill, clrSelect);

    if( pMenu->iSelected == uiCurrItem )
        clrSelect = OSD_COLOR_SELECTED;
    else
        clrSelect = 0;

    //Draw current
    DrawSubItem_ConfirmPage(bID0, pMenu->iMenuId,
                            uiCurrItem, pMenu->iNumOfItems,
                            pMenu->pItemsList[uiCurrItem]->uiStringId,
                            pMenu->pItemsList[uiCurrItem]->bmpIcon,
                            MAKE_BAR_ID(BAR_NARROW_TYPE, BAR_STATE_YEL),
                            MENU_TEXT_COLOR, clrFill, clrSelect);

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

#if 0
void ________ModeMenu_Function_________(){ruturn;} //dummy
#endif

#if (USB_MODE_SELECT_EN)  

void GetSubItemRect_ModeSelect(int i, int iItems, RECT* pRc, int drawStyle)
{
    if(drawStyle==0 /* Text */)
    {
        int x0 = 40;
        int w  = DISP_WIDTH - (x0*2);
        int h  = 30;
        int offset;

        if( iItems == 2 )
        {
            offset = 70;

            SET_SUBRECT(pRc, x0, 70+i*offset, w, h);
        }
        else if( iItems == 3 )
        {
            offset = 50;

            SET_SUBRECT(pRc, x0, 55+i*offset, w, h);
        }
        else if( iItems == 4 )
        {
            offset = 40;

            SET_SUBRECT(pRc, x0, 45+i*offset, w, h);
        }
        else
        {
            offset = 30;

            SET_SUBRECT(pRc, x0, 35+i*offset, w, h);
        }
    }
    else if(drawStyle==1 /* Icon */)
    {
        UINT32 IconGap = (DISP_WIDTH - (pRc->uiWidth * iItems))/(iItems+1);

        if( iItems <= 2 )
        {
            switch(i)
            {
                case 0: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 85, pRc->uiWidth, pRc->uiHeight); break;}
                case 1: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 1 - IconGap * 1), 85, pRc->uiWidth, pRc->uiHeight); break;}
                default:{SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 85, pRc->uiWidth, pRc->uiHeight); break;}
            }
        }
        else if( iItems <= 3 )
        {
            switch(i)
            {
                case 0: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 3 - IconGap * 3), 100,  pRc->uiWidth, pRc->uiHeight); break;}
                case 1: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 100,  pRc->uiWidth, pRc->uiHeight); break;}
                case 2: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 1 - IconGap * 1), 100,  pRc->uiWidth, pRc->uiHeight); break;}
                default:{SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 3), 100,  pRc->uiWidth, pRc->uiHeight); break;}
            }
        }
        else if( iItems <= 4 )
        {
            switch(i)
            {
                case 0: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 80,  pRc->uiWidth, pRc->uiHeight); break;}
                case 1: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 1 - IconGap * 2), 80,  pRc->uiWidth, pRc->uiHeight); break;}
                case 2: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 140, pRc->uiWidth, pRc->uiHeight); break;}
                case 3: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 1 - IconGap * 2), 140, pRc->uiWidth, pRc->uiHeight); break;}
                default:{SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 80,  pRc->uiWidth, pRc->uiHeight); break;}
            }
        }
        else
        {
            switch(i)
            {
                case 0: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 3 - IconGap * 3), 80,  pRc->uiWidth, pRc->uiHeight); break;}
                case 1: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 80,  pRc->uiWidth, pRc->uiHeight); break;}
                case 2: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 1 - IconGap * 1), 80,  pRc->uiWidth, pRc->uiHeight); break;}
                case 3: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 3 - IconGap * 3), 140, pRc->uiWidth, pRc->uiHeight); break;}
                case 4: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 2), 140, pRc->uiWidth, pRc->uiHeight); break;}
                case 5: {SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 1 - IconGap * 1), 140, pRc->uiWidth, pRc->uiHeight); break;}
                default:{SET_SUBRECT(pRc, (DISP_WIDTH - pRc->uiWidth * 2 - IconGap * 3), 80,  pRc->uiWidth, pRc->uiHeight); break;}
            }
        }
    }
}

void DrawSubItem_ModeSelect(UINT16 uwDispID, int iItem, int iTotalItems, int iCurPos, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_BITMAP barID, GUI_COLOR clrFont, GUI_COLOR clrBack, int drawStyle)
{
    RECT        rc;
    GUI_COLOR   bkClr;

    if(drawStyle==0 /* Text */)
    {
        GetSubItemRect_ModeSelect( iItem%SUB_MENU_PAGE_ITEM, iTotalItems, &rc, drawStyle);

        bkClr = (iItem == iCurPos)?(OSD_COLOR_DARKYELLOW):(OSD_COLOR_DARKGRAY2);

        AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);
        AHC_OSDSetPenSize(uwDispID, 2);
        AHC_OSDDrawRoundedRect(uwDispID, rc.uiLeft-1, rc.uiTop-1, rc.uiLeft+rc.uiWidth+1, rc.uiTop+rc.uiHeight+1, RECT_ROUND_RADIUS);

        AHC_OSDSetColor(uwDispID, bkClr);
        AHC_OSDDrawFillRoundedRect(uwDispID, rc.uiLeft, rc.uiTop+2, rc.uiLeft+rc.uiWidth, rc.uiTop+rc.uiHeight-2, RECT_ROUND_RADIUS);

        OSD_ShowStringPool(uwDispID, iStrID, rc, clrFont, bkClr, GUI_TA_HCENTER|GUI_TA_VCENTER);
    }
    else if(drawStyle==1 /* Icon */)
    {
        if(IconID != NULL)
        {
            rc.uiWidth  = IconID->XSize;
            rc.uiHeight = IconID->YSize;
            GetSubItemRect_ModeSelect( iItem%SUB_MENU_PAGE_ITEM, iTotalItems, &rc, drawStyle);

            if(iItem == iCurPos)
                AHC_OSDSetColor(uwDispID, OSD_COLOR_YELLOW);
            else
                AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);

            AHC_OSDDrawFillRoundedRect(uwDispID, rc.uiLeft-2, rc.uiTop-2, rc.uiLeft+IconID->XSize+2, rc.uiTop+IconID->YSize+2, 3);

            AHC_OSDSetColor(uwDispID, OSD_COLOR_WHITE);
            AHC_OSDSetBkColor(uwDispID, clrBack);
            AHC_OSDDrawBitmap(uwDispID, IconID, rc.uiLeft, rc.uiTop);

            rc.uiLeft   -= 25;
            rc.uiTop    += IconID->YSize;
            rc.uiWidth   = 25*2 + IconID->XSize;
            rc.uiHeight  = 30;
            OSD_ShowStringPool(uwDispID, iStrID, rc, clrFont, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
        }
    }
}

void MenuDrawMainPage_ModeSelect(PSMENUSTRUCT pMenu)
{
    UINT8  bID0 = 0 ,bID1 = 0;
    UINT32 i, iBegin, iEnd;

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    #if (USB_MODE_SELECT_EN) && (USB_MODE_SELECT_STYLE==MENU_ORIGINAL)
    if (pMenu->iMenuId==MENUID_USB_MODE_SELECT)
    {
    	
        //OSDDraw_SetAlphaBlending(bID0, AHC_TRUE);//m_OSD[uwDisplayID]->ColorFormat==RGB_D24BIT_RGB565 will not show.
        //OSDDraw_SetAlphaBlending(bID1, AHC_TRUE);

		OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);//
		OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);

        OSDDraw_ClearOvlDrawBuffer(bID0);

        MenuMainDrawBackCurtain(bID0, OSD_COLOR_BACKGROUND);

        iBegin = ALIGN_DOWN( pMenu->iCurrentPos, MAIN_MENU_PAGE_ITEM );
        iEnd   = MIN( iBegin+MAIN_MENU_PAGE_ITEM, pMenu->iNumOfItems);

        if (pMenu->iNumOfItems > MAIN_MENU_PAGE_ITEM)
        {
            MenuMainDrawButtons(bID0);
            MenuDrawPageInfo(bID0, 1, 1);
        }

        if( pMenu->uiStringId != -1 )
        {
            MenuDrawTitle(bID0, pMenu->uiStringId);
        }

        for( i=iBegin; i< iEnd; i++ )
        {
            GUI_BITMAP barID = BMICON_MENUBAR_WHITE;

            if( i == pMenu->iCurrentPos )
            {
                barID = BMICON_MENUBAR_YELLOW;
            }

            MenuDrawItem(bID0, pMenu->pItemsList[i],
                         i%MAIN_MENU_PAGE_ITEM,
                         pMenu->pItemsList[i]->uiStringId,
                         barID,
                         MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, pMenu->bCustom);
        }
    }
    else
    #endif
    {
        OSDDraw_SetAlphaBlending(bID0, AHC_FALSE);
        OSDDraw_SetAlphaBlending(bID1, AHC_FALSE);

        OSDDraw_ClearOvlDrawBuffer(bID0);


        iBegin = ALIGN_DOWN( pMenu->iCurrentPos, 6 );
        iEnd   = MIN( iBegin+6, pMenu->iNumOfItems);

        for( i=iBegin; i< iEnd; i++ )
        {
            GUI_COLOR   colorBk = OSD_COLOR_TRANSPARENT;
            GUI_BITMAP  barID   = BMICON_MENUBAR_WHITE;

            DrawSubItem_ModeSelect( bID0, i, pMenu->iNumOfItems, pMenu->iCurrentPos,
                                    pMenu->pItemsList[i]->uiStringId,
                                    pMenu->pItemsList[i]->bmpIcon,
                                    barID, MENU_TEXT_COLOR, colorBk,
                                    ubModeDrawStyle);
        }
    }

    MenuDraw_BatteryStatus(bID0);

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
	AHC_OSDSetActive(bID0, MMP_TRUE);
}

void MenuDrawChangeItem_ModeSelect(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
    UINT8   bID0 = 0 , bID1 = 0;

    #if (USB_MODE_SELECT_STYLE==MENU_ORIGINAL) && (USB_MODE_SELECT_EN)
    if (pMenu->iMenuId==MENUID_USB_MODE_SELECT)
    {
        PSMENUITEM      pPrevItem;
        PSMENUITEM      pCurItem;

        OSDDraw_EnterMenuDrawing(&bID0, &bID1);

        pPrevItem    = pMenu->pItemsList[uiPrevItem];
        pCurItem     = pMenu->pItemsList[uiCurrItem];

        MenuDrawItem(bID0, pPrevItem, uiPrevItem%MAIN_MENU_PAGE_ITEM, pPrevItem->uiStringId,
                    BMICON_MENUBAR_WHITE,  MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, pMenu->bCustom);

        MenuDrawItem(bID0, pCurItem,  uiCurrItem%MAIN_MENU_PAGE_ITEM, pCurItem->uiStringId,
                    BMICON_MENUBAR_YELLOW, MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, pMenu->bCustom);

        OSDDraw_ExitMenuDrawing(&bID0, &bID1);
    }
    else
    #endif
    {
        OSDDraw_EnterMenuDrawing(&bID0, &bID1);

        DrawSubItem_ModeSelect( bID0, uiPrevItem%SUB_MENU_PAGE_ITEM, pMenu->iNumOfItems, pMenu->iCurrentPos,
                                pMenu->pItemsList[uiPrevItem]->uiStringId,
                                pMenu->pItemsList[uiPrevItem]->bmpIcon,     BMICON_SUBBAR_WHITE_DEFAULT,
                                MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, ubModeDrawStyle);

        DrawSubItem_ModeSelect( bID0, uiPreSelected,                pMenu->iNumOfItems, pMenu->iCurrentPos,
                                pMenu->pItemsList[uiPreSelected]->uiStringId,
                                pMenu->pItemsList[uiPreSelected]->bmpIcon,  BMICON_SUBBAR_WHITE,
                                MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, ubModeDrawStyle);

        DrawSubItem_ModeSelect( bID0, uiCurrItem,                   pMenu->iNumOfItems, pMenu->iCurrentPos,
                                pMenu->pItemsList[uiCurrItem]->uiStringId,
                                pMenu->pItemsList[uiCurrItem]->bmpIcon,     BMICON_SUBBAR_YELLOW,
                                MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, ubModeDrawStyle);

        OSDDraw_ExitMenuDrawing(&bID0, &bID1);
    }
}

#endif

#if 0
void ________TopMenu_Function_________(){ruturn;} //dummy
#endif

#if (TOP_MENU_PAGE_EN)

#define XSPACE          (POS_TOP_MENU_W/pMenu->iNumOfItems)
#define XOFFEST(IconW)  (XSPACE-IconW)/2

void DrawTopCatagoryMenuIcon(UINT16 uwDispID, PSMENUSTRUCT pMenu, AHC_BOOL DVHL, AHC_BOOL GeneralHL, AHC_BOOL LangHL)
{
}

void MenuTopDrawCatagory(UINT16 uwDispID, PSMENUSTRUCT pMenu, int  iCata)
{
}

void DrawTopMenuItem(UINT16 uwDispID, PSMENUSTRUCT pMenu, int iItem, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR clrFont, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{

    UINT32  x, y;

    x = POS_TOP_MENU_X0 + iItem*XSPACE + XOFFEST(IconID->XSize);
    y = POS_TOP_MENU_Y0 + 80;

    if(clrSelect!=0)
    {
        AHC_OSDSetColor(uwDispID, clrSelect);
        AHC_OSDDrawFillRoundedRect(uwDispID, x-3 , y-3, x+IconID->XSize+3, y+IconID->YSize+3, RECT_ROUND_RADIUS);
    }

    if(IconID != NULL)
    {
        AHC_OSDDrawBitmap(uwDispID, IconID, x, y);
    }

    if(iStrID != -1)
    {
        RECT    StrRect = {POS_TOP_MENU_X0, 80, POS_TOP_MENU_W, 30};

        if(iItem == GetCurrentMenu()->iCurrentPos)
        {
            AHC_OSDSetColor(uwDispID, clrBack);
            AHC_OSDDrawFillRect2(uwDispID, &StrRect);

            OSD_ShowStringPool3(uwDispID, iStrID, StrRect,
                                OSD_COLOR_WHITE,  clrBack,
                                GUI_TA_HCENTER|GUI_TA_HCENTER);
        }
    }
}

void MenuDrawTopMenuPage(PSMENUSTRUCT pMenu)
{
    UINT8       bID0 = 0 ,bID1 = 0;
    UINT32      i ,iBegin, iEnd;
    GUI_COLOR   bkColor = TOP_MENU_BK_COLOR;

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        OSDDraw_SetAlphaBlending(bID0, AHC_FALSE);
        OSDDraw_SetAlphaBlending(bID1, AHC_FALSE);

        bkColor = TV_MENU_BK_COLOR;
    }
    else
    {
        //OSDDraw_SetAlphaBlending(bID0, AHC_TRUE);
        //OSDDraw_SetAlphaBlending(bID1, AHC_TRUE);
        OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);
        OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);
        bkColor = TOP_MENU_BK_COLOR;
    }

    OSDDraw_ClearOvlDrawBuffer(bID0);

    iBegin = ALIGN_DOWN( pMenu->iCurrentPos, pMenu->iNumOfItems/*m_ulTopMenuPageItem*/ );
    iEnd   = MIN( iBegin+pMenu->iNumOfItems/*m_ulTopMenuPageItem*/, pMenu->iNumOfItems);

    AHC_OSDSetColor(bID0, bkColor);
    AHC_OSDDrawFillRect(bID0, POS_TOP_MENU_X0, POS_TOP_MENU_Y0, POS_TOP_MENU_X1, POS_TOP_MENU_Y1);

    for( i=iBegin; i< iEnd; i++ )
    {
        GUI_COLOR clrSelect = TOP_MENU_BK_COLOR;

        if( i == pMenu->iCurrentPos )
        {
            clrSelect = OSD_COLOR_YELLOW;
        }

        DrawTopMenuItem(bID0,
                        pMenu,
                        i%pMenu->iNumOfItems,
                        pMenu->pItemsList[i]->uiStringId,
                        pMenu->pItemsList[i]->bmpIcon,
                        MENU_TEXT_COLOR, bkColor, clrSelect);

    }

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

void MenuDrawChangeTopMenuItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
    UINT8           bID0 = 0 , bID1 = 0;
    PSMENUITEM      pPrevItem;
    PSMENUITEM      pCurItem;
    GUI_COLOR       bkColor = TOP_MENU_BK_COLOR;

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
        bkColor = TV_MENU_BK_COLOR;
    }

    pPrevItem = pMenu->pItemsList[uiPrevItem];

    DrawTopMenuItem(bID0, pMenu,
                    uiPrevItem%pMenu->iNumOfItems,
                    pPrevItem->uiStringId,
                    pPrevItem->bmpIcon,
                    MENU_TEXT_COLOR, bkColor, bkColor);

    pCurItem  = pMenu->pItemsList[uiCurrItem];

    DrawTopMenuItem(bID0, pMenu,
                    uiCurrItem%pMenu->iNumOfItems,
                    pCurItem->uiStringId,
                    pCurItem->bmpIcon,
                    MENU_TEXT_COLOR, bkColor, OSD_COLOR_DARKYELLOW);


    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

/*
 * A gereral drawing touch menu page
 */
void MenuDrawMenuPage(PSMENUSTRUCT pMenu)
{
    UINT8       bID0 = 0 ,bID1 = 0;
    GUI_COLOR   bkColor = TOP_MENU_BK_COLOR;
    int         i;
    SMENUITEM           **pit;

    if(AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {   // TODO: need review TV/HDMI mode
        return;
    }
    printc(">>> Gereral draw touch menu page %d\r\n", pMenu->iMenuId);
    OSDDraw_EnterMenuDrawing(&bID0, &bID1);
    // Draw Icons on the Menu Page
    OSDDraw_SetAlphaBlending(bID0, AHC_FALSE);
    OSDDraw_SetAlphaBlending(bID1, AHC_FALSE);
    AHC_OSDClearBuffer(bID0);
    AHC_OSDSetColor(bID0, bkColor);//yining
    AHC_OSDDrawFillRect(bID0, 0, 0, AHC_GET_ATTR_OSD_W(bID0), AHC_GET_ATTR_OSD_H(bID0));
    pit = pMenu->pItemsList;
    for (i = 0; pit[i] != NULL && i < pMenu->iNumOfItems; i++) {
        SMENUTOUCHBUTTON    *pmb;

        pmb = pit[i]->ptp;
        /*
        printc("RECT %d %d %d %d\r\n", pmb->rcButton.uiLeft, pmb->rcButton.uiTop,
                                       pmb->rcButton.uiWidth,pmb->rcButton.uiHeight);
        printc("ItemID %d %x\r\n", pit[i]->iItemId, pit[i]->bmpIcon);
        */
        if (pit[i]->bmpIcon) {
            RECT    rc;
            OSD_Draw_IconXY(bID0, *(pit[i]->bmpIcon),
                                    pmb->rcButton.uiLeft,
                                    pmb->rcButton.uiTop);
            // Set Touch button size
            pmb->rcButton.uiWidth  = pit[i]->bmpIcon->XSize;
            pmb->rcButton.uiHeight = pit[i]->bmpIcon->YSize;
            if (pit[i]->uiStringId != (0 - 1)) {
                rc.uiLeft = pmb->rcButton.uiLeft - 10;
                rc.uiTop  = pmb->rcButton.uiTop + pit[i]->bmpIcon->YSize - 5;
                rc.uiWidth  = pmb->rcButton.uiWidth + 30;
                rc.uiHeight = 20;
                OSD_ShowStringPool(bID0, pit[i]->uiStringId,
                                    rc,
                                    MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT,
                                    GUI_TA_HCENTER|GUI_TA_VCENTER);
            }
        }
    }
    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}
#endif